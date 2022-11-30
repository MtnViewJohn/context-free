using ScintillaNET;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography;
using System.Security.Permissions;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static ScintillaNET.Style;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Tab;
using CppWrapper;
using System.Media;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using static System.Net.Mime.MediaTypeNames;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.StartPanel;
using System.Xml.Linq;

namespace CFForm
{
    public partial class Document : WeifenLuo.WinFormsUI.Docking.DockContent
    {
        public bool isNamed = false;
        public bool isExample = false;
        public bool reloadWhenReady = false;
        public bool canceledByUser = false;
        private bool mReuseVariation = false;
        private bool nonAlphaInVariation;
        private int currentVariation;
        internal bool reuseVariation
        {
            get { return mReuseVariation; }
            set
            {
                mReuseVariation = value;
                variationTextBox.ForeColor = value ? Color.Blue : Color.Black;
            }
        }

        private bool messageWindowUnready = false;
        private System.Text.StringBuilder deferredHtml = new StringBuilder();

        private String[] AutoComplete;
        private int lastCaretPosition = -1;
        private enum CFstyles {
            StyleDefault, StyleComment, StyleSymbol, StyleIdentifier,
            StyleKeywords, StyleBuiltins, StyleString, StyleNumber
        }
        private const int StyleDefault = 0;
        private const int StyleComment = 1;
        private const int StyleSymbol = 2;
        private const int StyleIdentifier = 3;
        private const int StyleKeywords = 4;
        private const int StyleBuiltins = 5;
        private const int StyleString = 6;
        private const int StyleNumber = 7;
        private RenderParameters renderParameters;
        public BackgroundWorker renderThread = new BackgroundWorker();
        private enum RenderAction
        {
            Render = 0, RenderSized = 1, Animate = 2, AnimateFrame = 3
        }
        private int renderButtonIndex = 0;
        private int progressDelay = 0;
        public enum PostRenderAction
        {
            DoNothing = 0, Render = 1, RenderSize = 2, RenderRepeat = 3, 
            Animate = 4, AnimateFrame = 5, SaveOutput = 8, Close = 16, Exit = 32
        };
        private int mPostRenderAction;
        internal PostRenderAction postAction
        {
            get { return (PostRenderAction)mPostRenderAction; }
            set {
                if (value == PostRenderAction.DoNothing) {      // reset action
                    mPostRenderAction = 0;
                } else if ((int)value < 8) {                    // render actions are mutually exclusive
                    mPostRenderAction = (mPostRenderAction & ~7) | (int)value;
                } else {                                        // otherwise, accumulate actions
                    mPostRenderAction |= (int)value;
                }
                if (!renderThread.IsBusy && mPostRenderAction != 0) {
                    renderCompleted(null, new RunWorkerCompletedEventArgs(null, null, false));
                }
            }
        }
        private RenderAction renderAction = RenderAction.Render;

        private CppWrapper.RenderHelper renderHelper = new RenderHelper();

        private Bitmap? displayImage = null;
        private bool isTiled = false;

        public Document()
        {
            InitializeComponent();
            AutoComplete = RenderHelper.GetAutoC();
            currentVariation = RenderHelper.RandomVariation(3);
            variationTextBox.Text = RenderHelper.VariationToString(currentVariation);
            toolStrip1.ImageList = imageList1;
            renderParameters = RenderParameters;
            sizeWidthBox.Text = renderParameters.width.ToString();
            sizeHeightBox.Text = renderParameters.height.ToString();
            frameTextBox.Text = renderParameters.frame.ToString();
        }

        private void loadInitialization(object sender, EventArgs e)
        {
            updateRenderButton();

            Form1? form1 = MdiParent as Form1;
            if (form1 != null) {
                var findHandler = new EventHandler(form1.menuEFindClick);
                menuEFind.Click += findHandler;
                menuEFindPrev.Click += findHandler;
            }

            cfdgText.StyleClearAll();
            cfdgText.Margins[0].Type = ScintillaNET.MarginType.Number;
            fontChanged(Properties.Settings.Default.EditorFont);
            styleChanged();     // grab tab width and styles
            cfdgText.SetSelectionBackColor(true, ColorTranslator.FromHtml("#114D9C"));
            cfdgText.SetSelectionForeColor(true, ColorTranslator.FromHtml("#FFFFFF"));

            cfdgText.Styles[ScintillaNET.Style.BraceLight].ForeColor = ColorTranslator.FromHtml("#8a2be2");
            cfdgText.Styles[ScintillaNET.Style.BraceLight].BackColor = ColorTranslator.FromHtml("#e6e6fa");
            cfdgText.Styles[ScintillaNET.Style.BraceBad].ForeColor = ColorTranslator.FromHtml("#ff0000");
            cfdgText.Styles[ScintillaNET.Style.BraceBad].Bold = true;

            cfdgText.DirectMessage(2260, (IntPtr)1, (IntPtr)0);     // SCI_SETTABINDENTS = 2260
            cfdgText.DirectMessage(2262, (IntPtr)1, (IntPtr)0);     // SCI_SETBACKSPACEUNINDENTS = 2262

            cfdgText.AutoCStops("[]{}<>,1234567890()/*+-|=!&^ \t.\r\n");
            cfdgText.WordChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:";

            // Render menu shortcuts
            cfdgText.ClearCmdKey(Keys.Control | Keys.R);
            cfdgText.ClearCmdKey(Keys.Control | Keys.Shift | Keys.R);
            cfdgText.ClearCmdKey(Keys.Control | Keys.Alt | Keys.R);
            cfdgText.ClearCmdKey(Keys.Control | Keys.Alt | Keys.A);
            cfdgText.ClearCmdKey(Keys.Control | Keys.Alt | Keys.F);
            cfdgText.ClearCmdKey(Keys.Control | Keys.O);
            cfdgText.ClearCmdKey(Keys.Control | Keys.U);
            cfdgText.ClearCmdKey(Keys.Control | Keys.End);
            // indent/unindent shortcuts
            cfdgText.ClearCmdKey(Keys.Control | Keys.OemOpenBrackets);
            cfdgText.ClearCmdKey(Keys.Control | Keys.OemCloseBrackets);

            cfdgText.Invalidate();

            setMessage(null);

            renderHelper = new RenderHelper(cfdgText.Handle.ToInt64(), this.Handle.ToInt64());
            renderParameters = RenderParameters;

            renderThread.RunWorkerCompleted += new RunWorkerCompletedEventHandler(renderCompleted);
            renderThread.DoWork += new DoWorkEventHandler(runRenderThread);
        }

        private void shownInitialization(object sender, EventArgs e)
        {
            if (reloadWhenReady) {
                reload();
                if (Properties.Settings.Default.OpenRender)
                    menuRRender.PerformClick();
            } else {
                cfdgText.Text = String.Empty;
                cfdgText.SetSavePoint();
            }
        }

        protected override void WndProc(ref System.Windows.Forms.Message m)
        {
            switch ((RenderHelper.WM_USER)m.Msg) {
                case RenderHelper.WM_USER.MESSAGE_UPDATE: {
                        setMessage(RenderHelper.getMessage(m.WParam));
                        break;
                    }
                case RenderHelper.WM_USER.STATUS_UPDATE: 
                    {
                        CppWrapper.RenderStats stat = RenderHelper.getStats(m.WParam);
                        if (stat.updateRender) {
                            renderHelper.updateRenderBox(renderBox, displayImage, 
                                renderParameters.suppressDisplay);
                        } else {
                            if ((stat.toDoCount > 0 && !stat.finalOutput) ||
                                !renderHelper.canvas) 
                            {
                                statusLabel.Text = String.Format("{0:N0} shapes and {1:N0} expansions to do",
                                    stat.shapeCount, stat.toDoCount);
                            } else {
                                String endText = renderHelper.tiled ? ", tiled" : "";
                                statusLabel.Text =
                                    String.Format("{0:N0} shapes, {1:N0} x {2:N0} pixels{3}",
                                    stat.shapeCount, renderHelper.width, renderHelper.height, endText);
                            }
                            if ((stat.inOutput && stat.fullOutput) || stat.showProgress) {
                                if (progressDelay > 2) {
                                    int bar = 0;
                                    if(stat.outputCount > 0)
                                        bar = (int)((100.0 * (double)stat.outputDone) / stat.outputCount);
                                    if (bar >= 0 && bar <= 100)
                                        progressBar.Value = bar;
                                } else {
                                    progressDelay++;
                                    progressBar.Value = 0;
                                }
                            } else {
                                progressDelay = 0;
                                progressBar.Value = 0;
                            }
                        }
                        break;
                    }
            }
            base.WndProc(ref m);
        }
        private void reload()
        {
            String exampleText = renderHelper.getExample(Name);
            if (exampleText != null) {
                isExample = true;
                cfdgText.Text = exampleText;
                cfdgText.SetSavePoint();
                return;
            }
            try {
                using (StreamReader sr = new StreamReader(Name)) {
                    cfdgText.Text = sr.ReadToEnd();
                    cfdgText.SetSavePoint();
                }
            } catch {
                ((Form1)MdiParent).manager.RemoveFile(Name);
                cfdgText.Text = String.Empty;
                cfdgText.SetSavePoint();
                setMessage("The file could not be read.");
            }
        }

        private CppWrapper.RenderParameters RenderParameters { 
            get
            {
                return new CppWrapper.RenderParameters
                {
                    periodicUpdate = Properties.Settings.Default.ProgressiveRender,
                    suppressDisplay = Properties.Settings.Default.SuppressDisplay,
                    animateZoom = Properties.Settings.Default.AnimateZoom,
                    frameRate = Properties.Settings.Default.AnimateFrameRate,
                    frame = Properties.Settings.Default.AnimateFrame,
                    animateWidth = Properties.Settings.Default.AnimateWidth,
                    animateHeight = Properties.Settings.Default.AnimateHeight,
                    length = Properties.Settings.Default.AnimateLength,
                    codec = Properties.Settings.Default.AnimateCodec,
                    preview = Properties.Settings.Default.AnimatePreview,
                    loop = Properties.Settings.Default.AnimatePreviewLoop,
                    width = Properties.Settings.Default.RenderWidth,
                    height = Properties.Settings.Default.RenderHeight,
                    borderSize = Properties.Settings.Default.BorderWidth,
                    minimumSize = Properties.Settings.Default.MinimumSize,
                    animateFrameCount = (int)(Properties.Settings.Default.AnimateLength *
                                              Properties.Settings.Default.AnimateFrameRate)
                };
            } 
            set
            {
                Properties.Settings.Default.ProgressiveRender = value.periodicUpdate;
                Properties.Settings.Default.SuppressDisplay = value.suppressDisplay;
                Properties.Settings.Default.AnimateZoom = value.animateZoom;
                Properties.Settings.Default.AnimateFrameRate = value.frameRate;
                Properties.Settings.Default.AnimateFrame = value.frame;
                Properties.Settings.Default.AnimateWidth = value.animateWidth;
                Properties.Settings.Default.AnimateHeight = value.animateHeight;
                Properties.Settings.Default.AnimateLength = value.length;
                Properties.Settings.Default.AnimateCodec = value.codec;
                Properties.Settings.Default.AnimatePreview = value.preview;
                Properties.Settings.Default.AnimatePreviewLoop = value.loop;
                Properties.Settings.Default.RenderWidth = value.width;
                Properties.Settings.Default.RenderHeight = value.height;
                Properties.Settings.Default.BorderWidth = value.borderSize;
                Properties.Settings.Default.MinimumSize = value.minimumSize;
                Properties.Settings.Default.Save();
            }
        }
        private CppWrapper.UploadPrefs UploadPrefs {
            get
            {
                return new CppWrapper.UploadPrefs
                {
                    CfdgName = Path.GetFileNameWithoutExtension(Text),
                    CfdgText = cfdgText.Text,
                    Variation = currentVariation,
                    VariationText = variationTextBox.Text,
                    ImageAppendVariation = Properties.Settings.Default.ImageAppendVariation,
                    JPEGQuality = Properties.Settings.Default.JPEGQuality,
                    OutputMultiplier = new double[]
                    {
                        (double)Properties.Settings.Default.MultiplyWidth,
                        (double)Properties.Settings.Default.MultiplyHeight
                    },
                    Username = Properties.Settings.Default.GalleryUsername,
                    Password = Properties.Settings.Default.GalleryPassword,
                    ImageCrop = Properties.Settings.Default.ImageCrop,
                    ccLicense = Properties.Settings.Default.ccLicense,
                    ccImage = Properties.Settings.Default.ccImage,
                    ccName = Properties.Settings.Default.ccName,
                    Updated = false
                };
            }
            set
            {
                Properties.Settings.Default.ImageAppendVariation = value.ImageAppendVariation;
                Properties.Settings.Default.JPEGQuality = (int)(value.JPEGQuality);
                Properties.Settings.Default.MultiplyWidth = (int)(value.OutputMultiplier[0]);
                Properties.Settings.Default.MultiplyHeight = (int)(value.OutputMultiplier[1]);
                Properties.Settings.Default.GalleryUsername = value.Username;
                Properties.Settings.Default.GalleryPassword = value.Password;
                Properties.Settings.Default.ImageCrop = value.ImageCrop;
                Properties.Settings.Default.ccLicense = value.ccLicense;
                Properties.Settings.Default.ccImage = value.ccImage;
                Properties.Settings.Default.ccName = value.ccName;
                Properties.Settings.Default.Save();
            }
        }

        private void renderCompleted(object? sender, RunWorkerCompletedEventArgs e)
        {
            statusTimer.Stop();

            if (renderParameters.action == RenderParameters.RenderActions.SaveSVG)
                setMessage("Done");

            int nextAction = (int)postAction;
            postAction = PostRenderAction.DoNothing;

            if ((nextAction & (int)PostRenderAction.Exit) != 0) {
                MdiParent.Close();
                return;
            }
            if ((nextAction & (int)PostRenderAction.Close) != 0) {
                Close();
                return;
            }

            updateRenderButton();

            if ((nextAction & (int)PostRenderAction.SaveOutput) != 0)
                menuROutput.PerformClick();

            switch ((PostRenderAction)(nextAction & 7)) {
                case PostRenderAction.Render:
                    menuRRender.PerformClick();
                    break;
                case PostRenderAction.RenderRepeat:
                    menuRAgain.PerformClick();
                    break;
                case PostRenderAction.RenderSize:
                    menuRRenderSize.PerformClick();
                    break;
                case PostRenderAction.Animate:
                    menuRAnimate.PerformClick();
                    break;
                case PostRenderAction.AnimateFrame:
                    menuRFrame.PerformClick();
                    break;
            }

            // TBD code to launch movie player
        }

        private void runRenderThread(object? sender, DoWorkEventArgs e)
        {
            progressDelay = 0;
            renderHelper?.runRenderThread(renderParameters);
        }
        private void renderButtonChange(object sender, EventArgs e)
        {
            reuseVariation = true;
            ToolStripMenuItem menu = (ToolStripMenuItem)sender;
            if (int.TryParse(menu.Tag.ToString(), out int tagnum)) {
                renderAction = (RenderAction)tagnum;
                updateRenderButton();
            }
        }

        private void updateRenderButton()
        {
            int lastIndex = renderButtonIndex;

            if (renderHelper.renderer != 0 && renderThread.IsBusy) {
                ++renderButtonIndex;
                if (renderButtonIndex > 8) renderButtonIndex = 1;
                if (renderHelper.requestFinishUp)
                    renderButton.Text = "Stop Now";
                else
                    renderButton.Text = "Stop";
            } else {
                switch (renderAction) {
                    case RenderAction.Render:
                        renderButton.Text = "Render";
                        break;
                    case RenderAction.RenderSized:
                        renderButton.Text = "Sized";
                        break;
                    case RenderAction.Animate:
                        renderButton.Text = "Animate";
                        break;
                    case RenderAction.AnimateFrame:
                        renderButton.Text = "Frame";
                        break;
                }
                renderButtonIndex = 0;

                bool visSize = renderAction == RenderAction.RenderSized;
                bool visFrame = renderAction == RenderAction.AnimateFrame;
                if (frameSeparator.Visible != visFrame || sizeSeparator.Visible != visSize) {
                    toolStrip1.SuspendLayout();

                    frameSeparator.Visible = visFrame;
                    frameLabel.Visible = visFrame;
                    frameTextBox.Visible = visFrame;
                    framePrev.Visible = visFrame;
                    frameNext.Visible = visFrame;

                    sizeSeparator.Visible = visSize;
                    sizeLabel1.Visible = visSize;
                    sizeLabel2.Visible = visSize;
                    sizeWidthBox.Visible = visSize;
                    sizeHeightBox.Visible = visSize;

                    toolStrip1.ResumeLayout();
                }
            }

            if (lastIndex != renderButtonIndex)
                renderButton.ImageIndex = renderButtonIndex;
        }

        private void renderButtonClick(object sender, EventArgs e)
        {
            if (renderHelper.renderer != 0 &&  renderThread.IsBusy) {
                if (renderHelper.requestFinishUp) {
                    renderHelper.requestStop = true;
                } else {
                    renderHelper.requestFinishUp = true;
                    updateRenderButton();
                }
            } else {
                switch (renderAction) {
                    case RenderAction.Render:
                        menuRRenderClick(sender, e); break;
                    case RenderAction.RenderSized:
                        menuRSizeClick(sender, e); break;
                    case RenderAction.Animate: 
                        menuRAnimateClick(sender, e); break;
                    case RenderAction.AnimateFrame: 
                        menuRFrameClick(sender, e); break;
                }
            }
        }

        private bool syncToSystem()
        {
            return renderHelper.syncToSystem(Name, cfdgText.Text);
        }

        private void splitterMoved(object sender, SplitterEventArgs e)
        {
            Form1? parent = MdiParent as Form1;
            if (parent != null) {
                if (parent.isResizing || parent.ActiveMdiChild != (Form)this)
                    return;
            }
            Properties.Settings.Default.EditorSplitter = editorSplitter.SplitterDistance;
            Properties.Settings.Default.DocumentSplitter = documentSplitter.SplitterDistance;
        }

        private void pictureDragEnter(object sender, DragEventArgs e)
        {

        }

        private void pictureDragDrop(object sender, DragEventArgs e)
        {

        }

        private void errorNavigation(object sender, WebBrowserNavigatingEventArgs e)
        {
            String frag = e.Url.Fragment;
            if (!String.IsNullOrEmpty(frag)) {
                try {
                    String[] split = frag.Split(':');
                    int b_line = Convert.ToInt32(split[1]) - 1;
                    int b_col = Convert.ToInt32(split[2]);
                    int e_line = Convert.ToInt32(split[3]) - 1;
                    int e_col = Convert.ToInt32(split[4]);
                    int start = cfdgText.Lines[b_line].Position + b_col;
                    int end = cfdgText.Lines[e_line].Position + e_col;
                    cfdgText.Focus();
                    cfdgText.SelectionStart = start;
                    cfdgText.SelectionEnd = end;
                    cfdgText.ScrollCaret();
                } catch { }
            }
        }

        private void messageWindowReady(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            Font f = Properties.Settings.Default.EditorFont;
            String html = String.Format(
@"<!DOCTYPE html PUBLIC ""-//W3C//DTD HTML 4.01//EN"" ""http://www.w3.org/TR/html4/strict.dtd"">
<html>
 <head>
  <title>Context Free Messages</title>
  <style type=""text/css"">
    p {{padding:0; margin:0; font-family:{0}; font-size:{1:f}pt;}}
    body {{padding:0; margin:0;}}
   </style>
 </head>
 <body>{2}
 </body>
</html>", f.Name, f.SizeInPoints, deferredHtml.ToString());
            cfdgMessage.Document.Write(html);
            deferredHtml.Clear();
            messageWindowUnready = false;
        }

        private void renderSizeChanged()
        {
            Size newSize = renderBox.Size;
            if (newSize.Width <= 0 || newSize.Height <= 0) return;
            if (displayImage != null && newSize.Width == displayImage.Width && 
                                        newSize.Height == displayImage.Height) return;
            try {
                using (Bitmap? oldImage = displayImage) {
                    displayImage = new Bitmap(newSize.Width, newSize.Height,
                        System.Drawing.Imaging.PixelFormat.Format32bppArgb);
                    Graphics g = Graphics.FromImage(displayImage);
                    g.Clear(Color.White);
                    renderBox.Image = displayImage;
                }
            } catch {
                setMessage("Error creating new screen bitmap.");
            }
        }

        private void setMessage(String? txt)
        {
            if (txt == null) {
                cfdgMessage.Navigate("about:blank");
                messageWindowUnready = true;
            } else if (txt.Length > 0) {
                String htmlFrag = $"  <p>{txt}</p>\n";
                if (messageWindowUnready) {
                    deferredHtml.Append(htmlFrag);
                    return;
                }
                cfdgMessage.Document.Write(htmlFrag);
                cfdgMessage.Document.Body.ScrollIntoView(false);
            }
        }

        private void modifiedCFDG(object sender, EventArgs e)
        {
            TabText = cfdgText.Modified ? ("*" + Text) : Text;
            if (cfdgText.Modified)
                variationTextBox.ForeColor = Color.Blue;
        }

        private void styleCfdg(object sender, ScintillaNET.StyleNeededEventArgs e)
        {
            int startPos = cfdgText.GetEndStyled();
            int startLine = cfdgText.LineFromPosition(startPos);
            startPos = cfdgText.Lines[startLine].Position;
            int endPos = e.Position;
            int endLine = cfdgText.LineFromPosition(endPos);
            renderHelper?.StyleLines(startLine, endLine);
        }

        private void insertionCheck(object sender, ScintillaNET.InsertCheckEventArgs e)
        {
            // auto indent
            if (e.Text.Equals("\r\n") || e.Text.Equals("\r") || e.Text.Equals("\n")) {
                var lineno = cfdgText.LineFromPosition(e.Position);
                String line = cfdgText.Lines[lineno].Text;
                var indent = cfdgText.Lines[lineno].Indentation;
                int tabWidth = Properties.Settings.Default.TabWidth;
                bool white = true;
                foreach (Char c in line) {
                    if (c == '{')
                        indent += tabWidth;
                    if (c == '}' && !white)
                        indent -= tabWidth;
                    if (c <= 0 || c >= 0x80 || !Char.IsWhiteSpace(c))
                        white = false;
                }
                if (indent > 0) {
                    String nextline = e.Text.PadRight(e.Text.Length + indent);
                    e.Text = nextline;
                }
            }
        }

        private void charAdded(object sender, ScintillaNET.CharAddedEventArgs e)
        {
            // auto unindent
            if (e.Char == '}') {
                var pos = cfdgText.CurrentPosition;
                var lineno = cfdgText.LineFromPosition(pos);
                int indentPos = cfdgText.DirectMessage(2128, (IntPtr)lineno, IntPtr.Zero).ToInt32(); // SCI_GETLINEINDENTPOSITION = 2128
                if (indentPos + 1 == pos) {
                    var indent = cfdgText.Lines[lineno].Indentation;
                    indent -= Properties.Settings.Default.TabWidth;
                    if (indent < 0)
                        indent = 0;
                    cfdgText.Lines[lineno].Indentation = indent;
                }
            }

            // autocomplete
            checkAutoC();
        }

        void checkAutoC()
        {
            var pos = cfdgText.CurrentPosition;
            var wordPos = cfdgText.WordStartPosition(pos, true);
            var len = pos - wordPos;
            if (len > 1) {
                String frag = cfdgText.GetTextRange(wordPos, len);
                System.Text.StringBuilder list = new System.Text.StringBuilder(1500);
                foreach (String word in AutoComplete)
                    if (word.StartsWith(frag, System.StringComparison.OrdinalIgnoreCase)) {
                        if (list.Length > 0)
                            list.Append(" ");
                        list.Append(word);
                    }
                if (list.Length > 0) {
                    cfdgText.AutoCShow(len, list.ToString());
                    return;
                }
            }
            if (cfdgText.AutoCActive)
                cfdgText.AutoCCancel();
        }

        private static Char SafeChar(Scintilla editor, int pos)
        {
            if (editor == null || pos < 1)
                return 'A';
            int c = editor.GetCharAt(pos);
            if (c < 1 || c > 127)
                return 'B';
            return Char.ConvertFromUtf32(c)[0];
        }
        private void updateUI(object sender, ScintillaNET.UpdateUIEventArgs e)
        {
            int caretPos = cfdgText.CurrentPosition;
            if (caretPos == lastCaretPosition) return;
            lastCaretPosition = caretPos;
            int bracepos1 = -1;
            int bracepos2 = -1;
            if ("()[]{}".IndexOf(SafeChar(cfdgText, caretPos - 1)) >= 0)
                bracepos1 = caretPos - 1;
            else if ("()[]{}".IndexOf(SafeChar(cfdgText, caretPos)) >= 0)
                bracepos1 = caretPos;
            if (bracepos1 >= 0) {
                bracepos2 = cfdgText.BraceMatch(bracepos1);
                if (bracepos2 == Scintilla.InvalidPosition)
                    cfdgText.BraceBadLight(bracepos1);
                else
                    cfdgText.BraceHighlight(bracepos1, bracepos2);
            } else {
                cfdgText.BraceHighlight(Scintilla.InvalidPosition, Scintilla.InvalidPosition);
            }
        }

        private void textChanged(object sender, ScintillaNET.ModificationEventArgs e)
        {
            if (cfdgText.AutoCActive && ((int)(e.Source) & 0x60) != 0)
                checkAutoC();
        }

        private void autoCCharDeleted(object sender, EventArgs e)
        {
            checkAutoC();
        }

        public void styleChanged()
        {
            cfdgText.TabWidth = Properties.Settings.Default.TabWidth;

            cfdgText.Styles[StyleDefault].Bold = Properties.Settings.Default.StyleDefaultBold;
            cfdgText.Styles[StyleComment].Bold = Properties.Settings.Default.StyleCommentsBold;
            cfdgText.Styles[StyleSymbol].Bold = Properties.Settings.Default.StyleSymbolsBold;
            cfdgText.Styles[StyleIdentifier].Bold = Properties.Settings.Default.StyleIdentifiersBold;
            cfdgText.Styles[StyleKeywords].Bold = Properties.Settings.Default.StyleKeywordsBold;
            cfdgText.Styles[StyleBuiltins].Bold = Properties.Settings.Default.StyleBuiltinsBold;
            cfdgText.Styles[StyleString].Bold = Properties.Settings.Default.StyleStringsBold;
            cfdgText.Styles[StyleNumber].Bold = Properties.Settings.Default.StyleNumbersBold;

            cfdgText.Styles[StyleDefault].Italic = Properties.Settings.Default.StyleDefaultItalic;
            cfdgText.Styles[StyleComment].Italic = Properties.Settings.Default.StyleCommentsItalic;
            cfdgText.Styles[StyleSymbol].Italic = Properties.Settings.Default.StyleSymbolsItalic;
            cfdgText.Styles[StyleIdentifier].Italic = Properties.Settings.Default.StyleIdentifiersItalic;
            cfdgText.Styles[StyleKeywords].Italic = Properties.Settings.Default.StyleKeywordsItalic;
            cfdgText.Styles[StyleBuiltins].Italic = Properties.Settings.Default.StyleBuiltinsItalic;
            cfdgText.Styles[StyleString].Italic = Properties.Settings.Default.StyleStringsItalic;
            cfdgText.Styles[StyleNumber].Italic = Properties.Settings.Default.StyleNumbersItalic;

            cfdgText.Styles[StyleDefault].ForeColor = ColorTranslator.FromHtml(Properties.Settings.Default.StyleDefaultColor);
            cfdgText.Styles[StyleComment].ForeColor = ColorTranslator.FromHtml(Properties.Settings.Default.StyleCommentsColor);
            cfdgText.Styles[StyleSymbol].ForeColor = ColorTranslator.FromHtml(Properties.Settings.Default.StyleSymbolsColor);
            cfdgText.Styles[StyleIdentifier].ForeColor = ColorTranslator.FromHtml(Properties.Settings.Default.StyleIdentifiersColor);
            cfdgText.Styles[StyleKeywords].ForeColor = ColorTranslator.FromHtml(Properties.Settings.Default.StyleKeywordsColor);
            cfdgText.Styles[StyleBuiltins].ForeColor = ColorTranslator.FromHtml(Properties.Settings.Default.StyleBuiltinsColor);
            cfdgText.Styles[StyleString].ForeColor = ColorTranslator.FromHtml(Properties.Settings.Default.StyleStringsColor);
            cfdgText.Styles[StyleNumber].ForeColor = ColorTranslator.FromHtml(Properties.Settings.Default.StyleNumbersColor);
        }

        public void fontChanged(Font f)
        {
            cfdgText.Styles[ScintillaNET.Style.Default].Font = f.Name;
            cfdgText.Styles[ScintillaNET.Style.Default].SizeF = f.SizeInPoints;
            for (int i = StyleDefault; i <= StyleNumber; i++) {
                cfdgText.Styles[i].Font = f.Name;
                cfdgText.Styles[i].SizeF = f.SizeInPoints;
            }
            cfdgText.Styles[ScintillaNET.Style.LineNumber].Font = f.Name;
            cfdgText.Styles[ScintillaNET.Style.LineNumber].SizeF = f.SizeInPoints;
            var w = cfdgText.CreateGraphics().MeasureString("8888", f);
            cfdgText.Margins[0].Width = (int)(w.Width + 0.9);
            cfdgMessage.Font = f;
            setMessage(null);
        }

        private void variationKeyDown(object sender, KeyEventArgs e)
        {
            nonAlphaInVariation = false;
            if (e.KeyCode >= Keys.A && e.KeyCode <= Keys.Z) return;
            if (e.KeyCode == Keys.Back) return;
            if (e.KeyCode == Keys.Return) return;
            nonAlphaInVariation = true;
        }

        private void variationKeyPress(object sender, KeyPressEventArgs e)
        {
            if (nonAlphaInVariation) {
                e.Handled= true;
                System.Media.SystemSounds.Beep.Play();
            } else if (e.KeyChar == '\r') {
                e.Handled = true;
                renderButtonClick(sender, e);
            }
        }

        private void variationChanged(object sender, EventArgs e)
        {
            reuseVariation = true;
            if (variationTextBox.Text.Length == 0 ) {
                variationTextBox.Text = "A";
                System.Media.SystemSounds.Beep.Play();
            }

            currentVariation = RenderHelper.VariationFromString(variationTextBox.Text);
        }

        private void frameKeyPressed(object sender, KeyPressEventArgs e)
        {
            if (!Char.IsControl(e.KeyChar) && !Char.IsDigit(e.KeyChar))
                e.Handled = true;
        }

        private void frameChanged(object sender, EventArgs e)
        {
            reuseVariation = true;
            if (frameTextBox.Text.Length == 0 ) {
                frameTextBox.Text = "1";
                renderParameters.frame = 1;
                return;
            }
            try {
                renderParameters.frame = int.Parse(frameTextBox.Text);
                if (renderParameters.frame >= 1 && renderParameters.frame <= renderParameters.animateFrameCount) {
                    RenderParameters = renderParameters;
                    return;
                }
            } catch {
            }
            frameTextBox.Text = "1";
            renderParameters.frame = 1;
            System.Media.SystemSounds.Asterisk.Play();
        }

        private void sizeChanged(object sender, EventArgs e)
        {
            reuseVariation = true;
            ToolStripTextBox? sizebox = sender as ToolStripTextBox;
            if (sizebox != null) {
                if (!int.TryParse(sizebox.Text, out int s) || s < 1) {
                    sizebox.Text = "1000";
                    s = 1000;
                    System.Media.SystemSounds.Beep.Play();
                } else {
                    if (sizebox == sizeWidthBox) {
                        renderParameters.width = s;
                    } else {
                        renderParameters.height = s;
                    }
                }
                RenderParameters = renderParameters;
            }
        }

        public void menuFilePopup(object sender, EventArgs e)
        {
            menuFRevert.Enabled = cfdgText.Modified;
        }

        private void menuFSaveClick(object sender, EventArgs e)
        {
            if (isNamed) {
                try {
                    using (var sw = new StreamWriter(Name)) {
                        sw.Write(cfdgText.Text);
                        cfdgText.SetSavePoint();
                    }
                } catch {
                    setMessage("The file could not be written.");
                }
            } else {
                menuFSaveAsClick(sender, e);
            }
        }

        private void menuFSaveAsClick(object sender, EventArgs e)
        {
            Form1? form1 = MdiParent as Form1;
            if (form1 != null) {
                form1.saveFileDialog1.FileName = Text;
                if (form1.saveFileDialog1.ShowDialog() == DialogResult.OK) {
                    Name = form1.saveFileDialog1.FileName;
                    TabText = Path.GetFileName(Name);
                    Text = TabText;
                    isNamed = true;
                    menuFSaveClick(sender, e);
                    form1.manager.AddFile(Name);
                }
            }
        }

        private void menuFCloseClick(object sender, EventArgs e)
        {
            Close();
        }

        private void menuFRevertClick(object sender, EventArgs e)
        {
            if (!(isNamed || isExample) || !cfdgText.Modified)
                return;

            var res = MessageBox.Show(this, "Do you wish to revert and lose your changes?",
                "Context Free", MessageBoxButtons.YesNo, MessageBoxIcon.Question);

            if (res == DialogResult.Yes)
                reload();
        }

        private void menuEditPopup(object sender, EventArgs e)
        {
            bool selectionExists = cfdgText.SelectionStart != cfdgText.SelectionEnd;
            menuECopy.Enabled = selectionExists;
            menuECut.Enabled = selectionExists;
            menuEPaste.Enabled = Clipboard.GetDataObject().GetDataPresent(DataFormats.Text);
            menuEDelete.Enabled = selectionExists;
            menuEUndo.Enabled = cfdgText.CanUndo;
            menuERedo.Enabled = cfdgText.CanRedo;
        }

        private void menuEUndoClick(object sender, EventArgs e)
        {
            if (cfdgText.CanUndo)
                cfdgText.Undo();
        }

        private void menuERedoClick(object sender, EventArgs e)
        {
            if (cfdgText.CanRedo)
                cfdgText.Redo();
        }

        private void menuECutClick(object sender, EventArgs e)
        {
            if (cfdgText.SelectionStart != cfdgText.SelectionEnd)
                cfdgText.Cut();
        }

        private void menuECopyClick(object sender, EventArgs e)
        {
            if (cfdgText.SelectionStart != cfdgText.SelectionEnd)
                cfdgText.Copy();
        }

        private void menuEPasteClick(object sender, EventArgs e)
        {
            if (Clipboard.GetDataObject().GetDataPresent(DataFormats.Text))
                cfdgText.Paste();
        }

        private void menuEDeleteClick(object sender, EventArgs e)
        {
            if (cfdgText.SelectionStart != cfdgText.SelectionEnd)
                cfdgText.ReplaceSelection(String.Empty);
        }

        private void menuEIndentClick(object sender, EventArgs e)
        {
            bool didIndent = false;
            ToolStripMenuItem? ctrl = sender as ToolStripMenuItem;
            String? tag = ctrl?.Tag as String;
            if (int.TryParse(tag, out int tagint)) {
                int delta = tagint * Properties.Settings.Default.TabWidth;
                var start = cfdgText.LineFromPosition(cfdgText.AnchorPosition);
                var end = cfdgText.LineFromPosition(cfdgText.CurrentPosition);
                if (end < start) {
                    var t = start; start = end; end = t;
                }
                for (; start <= end; ++start) {
                    var indent = cfdgText.Lines[start].Indentation;
                    var newIndent = indent + delta;
                    if (newIndent < 0) newIndent = 0;
                    if (indent != newIndent) {
                        if (!didIndent)
                            cfdgText.BeginUndoAction();
                        didIndent = true;
                        cfdgText.Lines[start].Indentation = newIndent;
                    }
                }
            }
            if (didIndent)
                cfdgText.EndUndoAction();
        }

            private void menuEUnicode(object sender, EventArgs e)
        {
            ToolStripMenuItem? menu = sender as ToolStripMenuItem;
            if (menu != null) {
                cfdgText.ReplaceSelection(menu.Text);
            }
        }

        private void menuRRenderClick(object sender, EventArgs e)
        {
            if (renderAction != RenderAction.Render) {
                renderAction = RenderAction.Render;
                updateRenderButton();
            }

            if (renderThread.IsBusy) {
                postAction = PostRenderAction.Render;
                return;
            }

            renderParameters = RenderParameters;
            renderParameters.width = renderBox.Size.Width;
            renderParameters.height = renderBox.Size.Height;
            renderParameters.action = RenderParameters.RenderActions.Render;

            doRender(true);
        }

        private void menuRSizeClick(object sender, EventArgs e)
        {
            if (renderAction != RenderAction.RenderSized) {
                renderAction = RenderAction.RenderSized;
                updateRenderButton();
            }

            if (renderThread.IsBusy) {
                postAction = PostRenderAction.RenderSize;
                return;
            }

            renderParameters = RenderParameters;
            renderParameters.action = RenderParameters.RenderActions.Render;
            if (sender == menuRRenderSize) {
                using (var rsd = new RenderSizeDialog(renderParameters)) {
                    if (rsd.ShowDialog() != DialogResult.OK)
                        return;
                    sizeWidthBox.Text = renderParameters.width.ToString();
                    sizeHeightBox.Text = renderParameters.height.ToString();
                    RenderParameters = renderParameters;
                }
            }

            doRender(false);
        }

        private void menuRAnimateClick(object sender, EventArgs e)
        {
            if (renderAction != RenderAction.Animate) {
                renderAction = RenderAction.Animate;
                updateRenderButton();
            }

            if (renderThread.IsBusy) {
                postAction = PostRenderAction.Animate;
                return;
            }

            renderParameters = RenderParameters;
            renderParameters.animateFrame = false;
            renderParameters.action = RenderParameters.RenderActions.Animate;
            if (sender == menuRAnimate) {
                using (var ad = new AnimateDialog(renderParameters)) {
                    if (ad.ShowDialog() != DialogResult.OK)
                        return;
                    RenderParameters = renderParameters;
                }
            }

            doRender(false);
        }

        private void menuRFrameClick(object sender, EventArgs e)
        {
            if (renderAction != RenderAction.AnimateFrame) {
                renderAction = RenderAction.AnimateFrame;
                updateRenderButton();
            }

            if (renderThread.IsBusy) {
                postAction = PostRenderAction.AnimateFrame;
                return;
            }

            renderParameters = RenderParameters;
            renderParameters.animateFrame = true;
            renderParameters.action = RenderParameters.RenderActions.Animate;
            if (sender == menuRFrame) {
                using (var afd = new AnimateDialog(renderParameters)) {
                    if (afd.ShowDialog() != DialogResult.OK)
                        return;
                    frameTextBox.Text = afd.frameTextBox.Text;
                    RenderParameters = renderParameters;
                }
            }

            doRender(false);
        }

        private void doRender(bool shrinkTiled)
        {
            setMessage(null);
            bool modifiedSinceRender = syncToSystem();
            if (!modifiedSinceRender && !reuseVariation)
                nextVariationClick(this, EventArgs.Empty);
            reuseVariation = false;

            bool useAnimateSize = renderParameters.action == RenderParameters.RenderActions.Animate;
            int width = useAnimateSize ? renderParameters.animateWidth : renderParameters.width;
            int height = useAnimateSize ? renderParameters.animateHeight : renderParameters.height;

            renderHelper.prepareForRender(width, height, renderParameters.minimumSize,
                renderParameters.borderSize, currentVariation, shrinkTiled);
            if (renderHelper.renderer == 0) {
                SystemSounds.Beep.Play();
                return;
            }

            isTiled = renderHelper.tiled;

            if (renderParameters.action  == RenderParameters.RenderActions.Render) {
                renderParameters.width = renderHelper.width;
                renderParameters.height = renderHelper.height;
            }

            if (renderParameters.action == RenderParameters.RenderActions.Animate ?
                renderParameters.animateFrame : renderParameters.periodicUpdate) 
            {
                setupCanvas(width, height);
            }

            if (renderParameters.action != RenderParameters.RenderActions.Animate &&
                !renderParameters.animateFrame)
            {
                // animation code here
            }

            if (renderParameters.action == RenderParameters.RenderActions.Render && displayImage == null)
                renderSizeChanged();

            postAction = PostRenderAction.DoNothing;
            if (renderHelper.performRender(renderThread)) {
                statusTimer.Start();
                updateRenderButton();
            }
        }

        private void doSVGSave(String path, UploadPrefs prefs)
        {
            setMessage(null);
            if (renderHelper.renderer == 0) {
                SystemSounds.Beep.Play();
                setMessage("There is no SVG data to save.");
                return;
            }
            if (path.Length == 0) {
                SystemSounds.Beep.Play();
                setMessage("Bad file name.");
                return;
            }

            if (!renderHelper.makeSVGCanvas(path, renderParameters.width, renderParameters.height, prefs)) 
            {
                SystemSounds.Beep.Play();
                setMessage("An error occurred while saving the SVG file.");
                return;
            }

            setMessage("Saving SVG file...");
            renderParameters.action = RenderParameters.RenderActions.SaveSVG;
            postAction = PostRenderAction.DoNothing;
            if (renderHelper.performRender(renderThread)) {
                statusTimer.Start();
                updateRenderButton();
            }
        }

        private void setupCanvas(int width, int height)
        {
            if (displayImage == null)
                renderSizeChanged();
            renderHelper.makeCanvas(width, height);
        }

        private void menuRStopClick(object sender, EventArgs e)
        {
            if (renderHelper.renderer != 0 && renderThread.IsBusy) {
                if (renderHelper.requestFinishUp) {
                    renderHelper.requestStop = true;
                } else {
                    renderHelper.requestFinishUp = true;
                    updateRenderButton();
                }
            }
        }

        private void menuROutputClick(object sender, EventArgs e)
        {
            // TODO: movie save code
            if (!renderHelper.canvas) {
                setMessage("There is nothing to save.");
                SystemSounds.Asterisk.Play();
                return;
            }

            if (renderThread.IsBusy) {
                PostRenderAction postAction = PostRenderAction.SaveOutput;
                return;
            }

            using (var saveImageDlg = new CppWrapper.SaveImage(renderHelper.frieze, renderHelper.tiled,
                Path.GetFileNameWithoutExtension(Text) + ".png", Path.GetDirectoryName(Text))) 
            {
                var prefs = UploadPrefs;
                if (saveImageDlg.ShowTheDialog(this, prefs) == DialogResult.OK) {
                    UploadPrefs = prefs;
                    switch (saveImageDlg.FileDlgFilterIndex) {
                        case 1: // PNG
                            renderHelper.saveToPNGorJPEG(prefs, saveImageDlg.FileDlgFileName, null, false);
                            break;
                        case 2: // JPEG
                            renderHelper.saveToPNGorJPEG(prefs, saveImageDlg.FileDlgFileName, null, true);
                            break;
                        case 3: // SVG
                            doSVGSave(saveImageDlg.FileDlgFileName, prefs);
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        private void menuRGalleryClick(object sender, EventArgs e)
        {
            CppWrapper.UploadPrefs prefs = UploadPrefs;

            renderHelper.uploadDesign(this, prefs);

            if (prefs.Updated)
                UploadPrefs = prefs;
        }

        private void nextVariationClick(object sender, EventArgs e)
        {
            reuseVariation = true;
            ++currentVariation;
            if (currentVariation > RenderHelper.MaxVariation || currentVariation < RenderHelper.MinVariation)
                currentVariation = RenderHelper.MaxVariation;
            variationTextBox.Text = RenderHelper.VariationToString(currentVariation);
        }

        private void prevVariationClick(object sender, EventArgs e)
        {
            reuseVariation = true;
            --currentVariation;
            if (currentVariation > RenderHelper.MaxVariation || currentVariation < RenderHelper.MinVariation)
                currentVariation = RenderHelper.MinVariation;
            variationTextBox.Text = RenderHelper.VariationToString(currentVariation);
        }

        private void formIsClosing(object sender, FormClosingEventArgs e)
        {
            canceledByUser = false;

            // we can't close the window while the worker thread is running, so stop it
            if (renderThread.IsBusy) {
                // remember to close the window when the thread ends
                postAction = PostRenderAction.Close;
                renderHelper.requestStop = true;
                e.Cancel = true;
                return;
            }

            // cleanup movie player

            // If the thread is stopped and the cfdg file is up-to-date then close
            if (!cfdgText.Modified) return;

            // See if the user wants to close (lose changes), save changes and close,
            // or cancel the close.
            String msg = "Save changes in " + Text + "?";
            DialogResult r = MessageBox.Show(this, msg, "Context Free", 
                MessageBoxButtons.YesNoCancel);

            switch (r) {
                case DialogResult.Yes:
                    menuFSaveClick(this, e);
                    break;
                case DialogResult.Cancel:
                    e.Cancel = true;
                    // if the close was from an application exit and the user cancels it
                    // then set this flag to cancel the exit
                    canceledByUser = true;
                    break;
                default:
                    break;
            }
        }

        private void menuRColorClick(object sender, EventArgs e)
        {
            ColorCalculator colorCalc = ((Form1)MdiParent).colorCalc;
            if (colorCalc.Visible) {
                colorCalc.WindowState = FormWindowState.Normal;
                colorCalc.Activate();
            } else {
                colorCalc.Show();
            }
        }

        private void statusTick(object sender, EventArgs e)
        {
            if (renderHelper.renderer != 0 && renderThread.IsBusy) {
                updateRenderButton();
                renderHelper.requestUpdate();
            }
        }

        private void renderBoxSizeChanged(object sender, EventArgs e)
        {
            Size newSize = renderBox.Size;
            if (newSize.Width <= 0 || newSize.Height <= 0) return;
            if (displayImage != null && (newSize.Width  != displayImage.Width ||
                                         newSize.Height != displayImage.Height)) displayImage = null;
        }
    }
}
