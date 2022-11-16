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

namespace CFForm
{
    public partial class Document : WeifenLuo.WinFormsUI.Docking.DockContent
    {
        public bool isNamed = false;
        public bool reloadWhenReady = false;
        private bool reuseVariation = false;
        private bool nonAlphaInVariation;
        private int currentVariation;

        private bool messageWindowUnready = false;
        private System.Text.StringBuilder deferredHtml = new StringBuilder();

        private String[]? AutoComplete = null;
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
        private RenderParameters renderParameters = new RenderParameters();
        private BackgroundWorker renderThread = new BackgroundWorker();
        private enum RenderAction
        {
            Render = 0, RenderSized = 1, Animate = 2, AnimateFrame = 3
        }
        private RenderAction renderAction = RenderAction.Render;

        private CppWrapper.RenderHelper? renderHelper = null;

        public Document()
        {
            InitializeComponent();
            AutoComplete = RenderHelper.GetAutoC();
        }

        private void loadInitialization(object sender, EventArgs e)
        {
            updateRenderButton();

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
            // indent/unindent shortcuts
            cfdgText.ClearCmdKey(Keys.Control | Keys.OemOpenBrackets);
            cfdgText.ClearCmdKey(Keys.Control | Keys.OemCloseBrackets);

            cfdgText.Invalidate();

            setMessage(null);

            renderHelper = new RenderHelper(cfdgText.Handle.ToInt64());
            initRenderFromSettings();
            renderParameters.frame = 1;
            renderParameters.animateFrameCount = renderParameters.length * renderParameters.frameRate;

            renderThread.RunWorkerCompleted += new RunWorkerCompletedEventHandler(renderCompleted);
            renderThread.DoWork += new DoWorkEventHandler(runRenderThread);

            if (reloadWhenReady) {
                try {
                    using (StreamReader sr = new StreamReader(Name)) {
                        cfdgText.Text = sr.ReadToEnd();
                        cfdgText.SetSavePoint();
                    }
                } catch {
                    cfdgText.Text = String.Empty;
                    cfdgText.SetSavePoint();
                    setMessage("The file could not be read.");
                }
            } else {
                cfdgText.Text = String.Empty;
                cfdgText.SetSavePoint();
            }
        }

        private void initRenderFromSettings()
        {
            renderParameters.periodicUpdate = Properties.Settings.Default.ProgressiveRender;
            renderParameters.suppressDisplay = Properties.Settings.Default.SuppressDisplay;
            renderParameters.animateZoom = Properties.Settings.Default.AnimateZoom;
            renderParameters.frameRate = Properties.Settings.Default.AnimateFrameRate;
            renderParameters.animateWidth = Properties.Settings.Default.AnimateWidth;
            renderParameters.animateHeight = Properties.Settings.Default.AnimateHeight;
            renderParameters.length = Properties.Settings.Default.AnimateLength;
            renderParameters.codec = Properties.Settings.Default.AnimateCodec;
            renderParameters.preview = Properties.Settings.Default.AnimatePreview;
            renderParameters.loop = Properties.Settings.Default.AnimatePreviewLoop;
            renderParameters.width = Properties.Settings.Default.RenderWidth;
            renderParameters.height = Properties.Settings.Default.RenderHeight;
            renderParameters.borderSize = Properties.Settings.Default.BorderWidth;
            renderParameters.minimumSize = Properties.Settings.Default.MinimumSize;
        }

        private void saveRenderToSettings()
        {
            Properties.Settings.Default.ProgressiveRender = renderParameters.periodicUpdate;
            Properties.Settings.Default.SuppressDisplay = renderParameters.suppressDisplay;
            Properties.Settings.Default.AnimateZoom = renderParameters.animateZoom;
            Properties.Settings.Default.AnimateFrameRate = renderParameters.frameRate;
            Properties.Settings.Default.AnimateWidth = renderParameters.animateWidth;
            Properties.Settings.Default.AnimateHeight = renderParameters.animateHeight;
            Properties.Settings.Default.AnimateLength = renderParameters.length;
            Properties.Settings.Default.AnimateCodec = renderParameters.codec;
            Properties.Settings.Default.AnimatePreview = renderParameters.preview;
            Properties.Settings.Default.AnimatePreviewLoop = renderParameters.loop;
            Properties.Settings.Default.RenderWidth = renderParameters.width;
            Properties.Settings.Default.RenderHeight = renderParameters.height;
            Properties.Settings.Default.BorderWidth = renderParameters.borderSize;
            Properties.Settings.Default.MinimumSize = renderParameters.minimumSize;
        }

        private void renderCompleted(object? sender, RunWorkerCompletedEventArgs e)
        {

        }

        private void runRenderThread(object? sender, DoWorkEventArgs e)
        {
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
            switch(renderAction)
            {
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

            bool visSize = renderAction == RenderAction.RenderSized;
            bool visFrame = renderAction == RenderAction.AnimateFrame;
            if (frameSeparator.Visible != visFrame || sizeSeparator.Visible != visSize)
            {
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

        private void renderButtonClick(object sender, EventArgs e)
        {
            return;
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
            TabText = cfdgText.Modified ? (Text + "*") : Text;
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

        }

        private void charAdded(object sender, ScintillaNET.CharAddedEventArgs e)
        {

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

        }

        private void autoCCharDeleted(object sender, EventArgs e)
        {

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
            variationTextBox.ForeColor = Color.Blue;
            if (variationTextBox.Text.Length == 0 ) {
                variationTextBox.Text = "A";
                System.Media.SystemSounds.Beep.Play();
            }

            // currentVariation = RenderHelper.Variation(variationTextBox.Text);
        }

        private void frameKeyPressed(object sender, KeyPressEventArgs e)
        {
            if (!Char.IsControl(e.KeyChar) && !Char.IsDigit(e.KeyChar))
                e.Handled = true;
        }

        private void frameChanged(object sender, EventArgs e)
        {
            reuseVariation = true;
            variationTextBox.ForeColor = Color.Blue;
            if (frameTextBox.Text.Length == 0 ) {
                frameTextBox.Text = "1";
                //renderParams.frame = 1;
                return;
            }
            try {
                //renderParams->frame = System::Int32::Parse(frameEdit->Text);
                //if (renderParams->frame >= 1 && renderParams->frame <= renderParams->animateFrameCount)
                //    return;
            } catch {
            }
            frameTextBox.Text = "1";
            //renderParams.frame = 1;
            System.Media.SystemSounds.Asterisk.Play();
        }

        private void sizeChanged(object sender, EventArgs e)
        {
            reuseVariation = true;
            variationTextBox.ForeColor = Color.Blue;
            ToolStripTextBox? sizebox = sender as ToolStripTextBox;
            if (sizebox != null) {
                if (!int.TryParse(sizebox.Text, out int s) || s < 1) {
                    sizebox.Text = "1000";
                    s = 1000;
                    System.Media.SystemSounds.Beep.Play();
                }
                if (sizebox == sizeWidthBox) {
                    // renderParams.width = s;
                } else {
                    // renderParams.height = s;
                }
                //     renderParams->saveToPrefs();
            }
        }

        private void menuFSaveClick(object sender, EventArgs e)
        {

        }

        private void menuFSaveAsClick(object sender, EventArgs e)
        {

        }

        private void menuFCloseClick(object sender, EventArgs e)
        {

        }

        private void menuFRevertClick(object sender, EventArgs e)
        {

        }

        private void menuEUndoClick(object sender, EventArgs e)
        {

        }

        private void menuERedoClick(object sender, EventArgs e)
        {

        }

        private void menuECutClick(object sender, EventArgs e)
        {

        }

        private void menuECopyClick(object sender, EventArgs e)
        {

        }

        private void menuEPasteClick(object sender, EventArgs e)
        {

        }

        private void menuEDeleteClick(object sender, EventArgs e)
        {

        }

        private void menuEFindClick(object sender, EventArgs e)
        {

        }

        private void menuEIndentClick(object sender, EventArgs e)
        {

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

        }

        private void menuRSizeClick(object sender, EventArgs e)
        {

        }

        private void menuRAgainClick(object sender, EventArgs e)
        {

        }

        private void menuRAnimateClick(object sender, EventArgs e)
        {

        }

        private void menuRFrameClick(object sender, EventArgs e)
        {

        }

        private void menuRStopClick(object sender, EventArgs e)
        {

        }

        private void menuROutputClick(object sender, EventArgs e)
        {

        }

        private void menuRGalleryClick(object sender, EventArgs e)
        {

        }
    }
}
