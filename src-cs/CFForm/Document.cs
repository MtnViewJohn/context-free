// Document.cs
// this file is part of Context Free
// ---------------------
// Copyright (C) 2022 John Horigan - john@glyphic.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//


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
using System.IO;
using System.Net;
using System.Web;

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
        internal bool ReuseVariation
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
        private readonly String[] renderActionName = new String[] {"Render", "Sized", "Animate", "Frame"};
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
                    RenderCompleted(null, new RunWorkerCompletedEventArgs(null, null, false));
                }
            }
        }
        private RenderAction renderAction = RenderAction.Render;

        private CppWrapper.RenderHelper renderHelper = new RenderHelper();

        private Bitmap? mDisplayImage = null;

        internal Bitmap DisplayImage
        {
            get {
                Size newSize = renderBox.Size;

                if (mDisplayImage != null) {
                    if (newSize == mDisplayImage.Size)
                        return mDisplayImage;
                    mDisplayImage.Dispose();
                    mDisplayImage = null;
                }

                if (newSize.Width <= 0 || newSize.Height <= 0) 
                    newSize = new Size(10, 10);

                try {
                    mDisplayImage = new Bitmap(newSize.Width, newSize.Height,
                        System.Drawing.Imaging.PixelFormat.Format32bppArgb);
                    Graphics g = Graphics.FromImage(mDisplayImage);
                    g.Clear(Color.White);
                    renderBox.Image = mDisplayImage;
                } catch {
                    mDisplayImage = new Bitmap(10, 10,
                        System.Drawing.Imaging.PixelFormat.Format32bppArgb);
                    SetMessage("Error creating new screen bitmap.");
                }
                return mDisplayImage;
            }
        }

        internal Size DisplayImageSize
        {
            get
            {
                if (mDisplayImage == null) return new Size(0, 0);
                return mDisplayImage.Size;
            }
        }

        private bool isTiled = false;

        private String? movieFile = null;
        private System.Diagnostics.Process? moviePlayer = null;

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
            renderBox.AllowDrop = true;
        }

        private void LoadInitialization(object sender, EventArgs e)
        {
            UpdateRenderButton();

            Form1? form1 = MdiParent as Form1;
            if (form1 != null) {
                var findHandler = new EventHandler(form1.menuEFindClick);
                menuEFind.Click += findHandler;
                menuEFindPrev.Click += findHandler;
            }

            cfdgText.StyleClearAll();
            cfdgText.Margins[0].Type = ScintillaNET.MarginType.Number;
            EditorFontChanged(Properties.Settings.Default.EditorFont);
            EditorStyleChanged();     // grab tab width and styles
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

            unsafe {
                renderHelper = new RenderHelper(cfdgText.Handle.ToPointer(), this.Handle.ToPointer());
            }
            renderParameters = RenderParameters;

            bool canAnimate = renderHelper.CanAnimate();
            menuRAnimate.Enabled = canAnimate;
            animateToolStripMenuItem.Enabled = canAnimate;

            renderThread.RunWorkerCompleted += new RunWorkerCompletedEventHandler(RenderCompleted);
            renderThread.DoWork += new DoWorkEventHandler(RunRenderThread);
        }

        private void ShownInitialization(object sender, EventArgs e)
        {
            documentSplitter.SplitterDistance = Properties.Settings.Default.DocumentSplitter;
            editorSplitter.SplitterDistance = Properties.Settings.Default.EditorSplitter;

            if (reloadWhenReady) {
                if (Reload() && Properties.Settings.Default.OpenRender)
                    menuRRender.PerformClick();
            } else {
                cfdgText.Text = String.Empty;
                cfdgText.EmptyUndoBuffer();
            }
        }

        protected override void WndProc(ref System.Windows.Forms.Message m)
        {
            switch ((RenderHelper.WM_USER)m.Msg) {
                case RenderHelper.WM_USER.MESSAGE_UPDATE: {
                        SetMessage(RenderHelper.GetMessage(m.WParam));
                        break;
                    }
                case RenderHelper.WM_USER.STATUS_UPDATE: 
                    {
                        CppWrapper.RenderStats stat = RenderHelper.GetStats(m.WParam);
                        if (stat.updateRender) {
                            renderHelper.UpdateRenderBox(renderBox, DisplayImage, 
                                renderParameters.suppressDisplay);
                        } else {
                            if ((stat.toDoCount > 0 && !stat.finalOutput) ||
                                !renderHelper.Canvas) 
                            {
                                statusLabel.Text = String.Format("{0:N0} shapes and {1:N0} expansions to do",
                                    stat.shapeCount, stat.toDoCount);
                            } else {
                                String endText = renderHelper.Tiled ? ", tiled" : "";
                                statusLabel.Text =
                                    String.Format("{0:N0} shapes, {1:N0} x {2:N0} pixels{3}",
                                    stat.shapeCount, renderHelper.Width, renderHelper.Height, endText);
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

        private bool Reload()
        {
            String exampleText = renderHelper.GetExample(Name);
            if (exampleText != null) {
                isExample = true;
                cfdgText.Text = exampleText;
                cfdgText.EmptyUndoBuffer();
                return true;
            }

            if (Name.StartsWith("http://") || Name.StartsWith("https://") || Name.StartsWith("file://")) {
                try {
                    SetMessage("Downloading the design&hellip;");
                    Uri url = new Uri(Name);
                    WebClient req = new WebClient();
                    req.DownloadStringCompleted += new DownloadStringCompletedEventHandler(DownLoaded);
                    req.DownloadStringAsync(url);
                } catch {
                    SetMessage("The design could not be downloaded.");
                }
                return false;
            }

            int comma = Name.IndexOf(",");
            if (Name.StartsWith("data:") && comma >= 0) {
                try {
                    if (Name.IndexOf(";base64,") == comma - 7) {
                        Byte[] utf8bytes = Convert.FromBase64String(Name[(comma + 1)..]);
                        cfdgText.Text = Encoding.UTF8.GetString(utf8bytes);
                    } else {
                        cfdgText.Text = HttpUtility.UrlDecode(Name[(comma + 1)..], Encoding.UTF8);
                    }
                    cfdgText.EmptyUndoBuffer();
                    Name = TabText;
                    return true;
                } catch {
                    SetMessage("Could not decode the text data.");
                    return false;
                }
            }

            try {
                using (StreamReader sr = new StreamReader(Name)) {
                    cfdgText.Text = sr.ReadToEnd();
                    cfdgText.EmptyUndoBuffer();
                }
            } catch {
                ((Form1)MdiParent).mruManager.RemoveFile(Name);
                cfdgText.Text = String.Empty;
                cfdgText.EmptyUndoBuffer();
                SetMessage("The file could not be read.");
                return false;
            }
            return true;
        }

        private void DownLoaded(Object sender, DownloadStringCompletedEventArgs e)
        {
            if (e.Cancelled || e.Error != null) {
                SetMessage("The design could not be downloaded.");
            } else {
                SetMessage("Download complete.");
                if (Name.EndsWith(".cfdg")) {
                    cfdgText.Text = e.Result;
                    Uri uri = new Uri(Name);
                    TabText = WebUtility.UrlDecode(Path.GetFileName(uri.AbsolutePath));
                    Name = TabText;
                    Text = TabText;
                    cfdgText.EmptyUndoBuffer();
                    if (Properties.Settings.Default.OpenRender)
                        menuRRender.PerformClick();
                } else {
                    var download = RenderHelper.DownloadDesign(e.Result);
                    if (download != null) {
                        cfdgText.Text = download.CfdgText;
                        currentVariation = download.Variation - 1;
                        NextVariationClick(sender, e);
                        Name = download.CfdgName;
                        TabText = Name;
                        Text = TabText;
                        cfdgText.EmptyUndoBuffer();
                        if (Properties.Settings.Default.OpenRender)
                            menuRRender.PerformClick();
                    } else {
                        SetMessage("Failed to extract cfdg data!");
                    }
                }
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
                    animateFrameCount = Properties.Settings.Default.AnimateLength *
                                        Properties.Settings.Default.AnimateFrameRate
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

        private static Byte[] CFentropy = {
            210, 61, 229, 177, 254, 52, 150, 62, 81, 246, 248, 185, 59, 89, 93, 117,
            142, 120, 64, 79, 229, 71, 195, 27, 181, 140, 195, 78, 123, 167, 45,
            224, 108, 172, 164, 130, 68, 64, 103, 98, 136, 132, 14, 3, 240, 232,
            152, 220, 29, 154, 78, 181, 92, 109, 92, 176, 46, 128, 13, 79, 108, 144,
            83, 219, 42, 161, 158, 81, 213, 120, 13, 198, 163, 40, 14, 135, 30, 13,
            117, 128, 172, 184, 61, 69, 50, 233, 116, 202, 161, 204, 223, 52, 126,
            151, 223, 14, 123, 12, 29, 100, 71, 22, 247, 41, 231, 97, 116, 58, 168,
            125, 92, 26, 4, 3, 228, 182, 204, 43, 185, 79, 118, 137, 173, 163, 215,
            111, 60, 253
        };

        private CppWrapper.UploadPrefs UploadPrefs {
            get
            {
                var prefs = new CppWrapper.UploadPrefs
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
                try {
                    Byte[] protectedBlob = Convert.FromBase64String(prefs.Password);
                    Byte[] unprotectedBlob = ProtectedData.Unprotect(protectedBlob,
                        CFentropy, DataProtectionScope.CurrentUser);
                    prefs.Password = Encoding.UTF8.GetString(unprotectedBlob);
                } catch {
                    prefs.Password = "";
                }
                return prefs;
            }
            set
            {
                Properties.Settings.Default.ImageAppendVariation = value.ImageAppendVariation;
                Properties.Settings.Default.JPEGQuality = value.JPEGQuality;
                Properties.Settings.Default.MultiplyWidth = (int)(value.OutputMultiplier[0]);
                Properties.Settings.Default.MultiplyHeight = (int)(value.OutputMultiplier[1]);
                Properties.Settings.Default.GalleryUsername = value.Username;
                if (value.Password.Length > 0) {
                    Byte[] unprotectedBlob = Encoding.UTF8.GetBytes(value.Password);
                    Byte[] protectedBlob = ProtectedData.Protect(unprotectedBlob,
                        CFentropy, DataProtectionScope.CurrentUser);
                    Properties.Settings.Default.GalleryPassword = Convert.ToBase64String(protectedBlob);
                }
                Properties.Settings.Default.ImageCrop = value.ImageCrop;
                Properties.Settings.Default.ccLicense = value.ccLicense;
                Properties.Settings.Default.ccImage = value.ccImage;
                Properties.Settings.Default.ccName = value.ccName;
                Properties.Settings.Default.Save();
            }
        }

        private void RenderCompleted(object? sender, RunWorkerCompletedEventArgs e)
        {
            statusTimer.Stop();

            if (renderParameters.action == RenderParameters.RenderActions.SaveSVG)
                SetMessage("Done");

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

            UpdateRenderButton();

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

            if (nextAction == (int)PostRenderAction.DoNothing &&
                renderParameters.action == RenderParameters.RenderActions.Animate &&
                !renderParameters.animateFrame &&
                renderParameters.preview)
            {
                moviePlayer = new System.Diagnostics.Process();

                try {
                    moviePlayer.StartInfo = new System.Diagnostics.ProcessStartInfo
                    {
                        UseShellExecute = false,
                        FileName = "ffplay.exe",
                        CreateNoWindow = true,
                        Arguments = renderParameters.loop ? "-loop 0 " + movieFile : movieFile
                    };
                    moviePlayer.Start();
                    moviePlayer.EnableRaisingEvents = true;
                } catch (Exception ex) {
                    SetMessage(ex.Message);
                    moviePlayer.Dispose();
                    moviePlayer = null;
                }
            }
        }

        private void RunRenderThread(object? sender, DoWorkEventArgs e)
        {
            progressDelay = 0;
            renderHelper?.RunRenderThread(renderParameters);
        }
        private void RenderButtonChange(object sender, EventArgs e)
        {
            ReuseVariation = true;
            ToolStripMenuItem menu = (ToolStripMenuItem)sender;
            if (int.TryParse(menu.Tag.ToString(), out int tagnum)) {
                renderAction = (RenderAction)tagnum;
                UpdateRenderButton();
            }
        }

        private void UpdateRenderButton()
        {
            int lastIndex = renderButtonIndex;

            if (renderHelper.Renderer && renderThread.IsBusy) {
                ++renderButtonIndex;
                if (renderButtonIndex > 8) renderButtonIndex = 1;
                if (renderHelper.RequestFinishUp)
                    renderButton.Text = "Stop Now";
                else
                    renderButton.Text = "Stop";
            } else {
                renderButton.Text = renderActionName[(int)renderAction];
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

        private void RenderButtonClick(object sender, EventArgs e)
        {
            if (renderHelper.Renderer &&  renderThread.IsBusy) {
                if (renderHelper.RequestFinishUp) {
                    renderHelper.RequestStop = true;
                } else {
                    renderHelper.RequestFinishUp = true;
                    UpdateRenderButton();
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

        private bool SyncToSystem()
        {
            return renderHelper.SyncToSystem(Name, cfdgText.Text);
        }

        private void SplitterMoved(object sender, SplitterEventArgs e)
        {
            Form1? parent = MdiParent as Form1;
            if (parent != null) {
                if (parent.isResizing || parent.ActiveMdiChild != (Form)this)
                    return;
            }
            Properties.Settings.Default.EditorSplitter = editorSplitter.SplitterDistance;
            Properties.Settings.Default.DocumentSplitter = documentSplitter.SplitterDistance;
            Properties.Settings.Default.Save();
        }

        private void PictureDragEnter(object sender, DragEventArgs e)
        {
            if (e.Data == null) {
                e.Effect = DragDropEffects.None;
            } else {
                if (e.Data.GetDataPresent(DataFormats.FileDrop) || e.Data.GetDataPresent(DataFormats.Text))
                    e.Effect = DragDropEffects.Copy;
                else
                    e.Effect = DragDropEffects.None;
            }
        }

        private void PictureDragDrop(object sender, DragEventArgs e)
        {
            Form1? form1 = MdiParent as Form1;
            form1?.FormDragDrop(sender, e);
        }

        private void ErrorNavigation(object sender, WebBrowserNavigatingEventArgs e)
        {
            String frag = e.Url.Fragment;
            if (!String.IsNullOrEmpty(frag)) {
                e.Cancel = true;
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

        private void MessageWindowReady(object sender, WebBrowserDocumentCompletedEventArgs e)
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

        private void SetMessage(String? txt)
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

        private void ModifiedCFDG(object sender, EventArgs e)
        {
            TabText = cfdgText.Modified ? ("*" + Text) : Text;
            if (cfdgText.Modified)
                variationTextBox.ForeColor = Color.Blue;
        }

        private void StyleCfdg(object sender, ScintillaNET.StyleNeededEventArgs e)
        {
            int startPos = cfdgText.GetEndStyled();
            int startLine = cfdgText.LineFromPosition(startPos);
            int endPos = e.Position;
            int endLine = cfdgText.LineFromPosition(endPos);
            renderHelper?.StyleLines(startLine, endLine);
        }

        private void InsertionCheck(object sender, ScintillaNET.InsertCheckEventArgs e)
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

        private void CharAdded(object sender, ScintillaNET.CharAddedEventArgs e)
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
            CheckAutoC();
        }

        void CheckAutoC()
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
        private void UpdateUI(object sender, ScintillaNET.UpdateUIEventArgs e)
        {
            int caretPos = cfdgText.CurrentPosition;
            if (caretPos == lastCaretPosition) return;
            lastCaretPosition = caretPos;
            int bracepos1 = -1;
            int bracepos2 = -1;
            if ("()[]{}".Contains(SafeChar(cfdgText, caretPos - 1)))
                bracepos1 = caretPos - 1;
            else if ("()[]{}".Contains(SafeChar(cfdgText, caretPos)))
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

        private void EditorTextChanged(object sender, ScintillaNET.ModificationEventArgs e)
        {
            if (cfdgText.AutoCActive && ((int)(e.Source) & 0x60) != 0)
                CheckAutoC();
        }

        private void autoCCharDeleted(object sender, EventArgs e)
        {
            CheckAutoC();
        }

        public void EditorStyleChanged()
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

        public void EditorFontChanged(Font f)
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
            SetMessage(null);
        }

        private void VariationKeyDown(object sender, KeyEventArgs e)
        {
            nonAlphaInVariation = false;
            if (e.KeyCode >= Keys.A && e.KeyCode <= Keys.Z) return;
            if (e.KeyCode == Keys.Back) return;
            if (e.KeyCode == Keys.Return) return;
            nonAlphaInVariation = true;
        }

        private void VariationKeyPress(object sender, KeyPressEventArgs e)
        {
            if (nonAlphaInVariation) {
                e.Handled= true;
                System.Media.SystemSounds.Beep.Play();
            } else if (e.KeyChar == '\r') {
                e.Handled = true;
                RenderButtonClick(sender, e);
            }
        }

        private void VariationChanged(object sender, EventArgs e)
        {
            ReuseVariation = true;
            if (variationTextBox.Text.Length == 0 ) {
                variationTextBox.Text = "A";
                System.Media.SystemSounds.Beep.Play();
            }

            currentVariation = RenderHelper.VariationFromString(variationTextBox.Text);
        }

        private void FrameKeyPressed(object sender, KeyPressEventArgs e)
        {
            if (!Char.IsControl(e.KeyChar) && !Char.IsDigit(e.KeyChar))
                e.Handled = true;
        }

        private void FrameChanged(object sender, EventArgs e)
        {
            ReuseVariation = true;
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

        private void RenderSizeChanged(object sender, EventArgs e)
        {
            ReuseVariation = true;
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
                    SetMessage("The file could not be written.");
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
                    form1.mruManager.AddFile(Name);
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
                Reload();
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

        private void menuESelectAllClick(object sender, EventArgs e)
        {
            cfdgText.SelectAll();
        }

        private void menuEIndentClick(object sender, EventArgs e)
        {
            bool didIndent = false;
            ToolStripMenuItem? ctrl = sender as ToolStripMenuItem;
            String? tag = ctrl?.Tag as String;
            if (int.TryParse(tag, out int tagint)) {
                int delta = tagint * Properties.Settings.Default.TabWidth;
                var startPos = Math.Min(cfdgText.AnchorPosition, cfdgText.CurrentPosition);
                var endPos = Math.Max(cfdgText.AnchorPosition, cfdgText.CurrentPosition);
                var start = cfdgText.LineFromPosition(startPos);
                var end = cfdgText.LineFromPosition(endPos);

                // When a whole line is selected the position is at the start
                // of the next line. We don't want to include that line.
                if (start < end && cfdgText.GetColumn(endPos) == 0)
                    end--;

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
                UpdateRenderButton();
            }

            if (renderThread.IsBusy) {
                postAction = PostRenderAction.Render;
                return;
            }

            renderParameters = RenderParameters;
            renderParameters.width = renderBox.Size.Width;
            renderParameters.height = renderBox.Size.Height;
            renderParameters.action = RenderParameters.RenderActions.Render;

            DoRender(true);
        }

        private void menuRSizeClick(object sender, EventArgs e)
        {
            if (renderAction != RenderAction.RenderSized) {
                renderAction = RenderAction.RenderSized;
                UpdateRenderButton();
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

            DoRender(false);
        }

        private void menuRAnimateClick(object sender, EventArgs e)
        {
            if (renderAction != RenderAction.Animate) {
                renderAction = RenderAction.Animate;
                UpdateRenderButton();
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

            DoRender(false);
        }

        private void menuRFrameClick(object sender, EventArgs e)
        {
            if (renderAction != RenderAction.AnimateFrame) {
                renderAction = RenderAction.AnimateFrame;
                UpdateRenderButton();
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

            DoRender(false);
        }

        private void DoRender(bool shrinkTiled)
        {
            SetMessage(null);
            bool modifiedSinceRender = SyncToSystem();
            if (!modifiedSinceRender && !ReuseVariation && renderParameters.action != RenderParameters.RenderActions.Animate)
                NextVariationClick(this, EventArgs.Empty);
            ReuseVariation = false;

            MovieCleaner.Clean(moviePlayer, movieFile);
            moviePlayer = null; movieFile = null;

            bool useAnimateSize = renderParameters.action == RenderParameters.RenderActions.Animate;
            int width = useAnimateSize ? renderParameters.animateWidth : renderParameters.width;
            int height = useAnimateSize ? renderParameters.animateHeight : renderParameters.height;

            renderHelper.PrepareForRender(width, height, renderParameters.minimumSize,
                renderParameters.borderSize, currentVariation, shrinkTiled);
            if (!renderHelper.Renderer) {
                SystemSounds.Beep.Play();
                return;
            }

            isTiled = renderHelper.Tiled;

            if (renderParameters.action  == RenderParameters.RenderActions.Render) {
                renderParameters.width = renderHelper.Width;
                renderParameters.height = renderHelper.Height;
            }

            if (renderParameters.action == RenderParameters.RenderActions.Animate ?
                renderParameters.animateFrame : renderParameters.periodicUpdate) 
            {
                SetupCanvas(width, height);
            }

            if (renderParameters.action == RenderParameters.RenderActions.Animate &&
                !renderParameters.animateFrame)
            {
                String ffReturn = renderHelper.MakeAnimationCanvas(renderParameters);
                if (Path.IsPathRooted(ffReturn)) {
                    movieFile = ffReturn;
                } else {
                    SystemSounds.Beep.Play();
                    MessageBox.Show(MdiParent, ffReturn);
                    SetMessage(ffReturn);
                    return;
                }
            }

            postAction = PostRenderAction.DoNothing;
            if (renderHelper.PerformRender(renderThread)) {
                statusTimer.Start();
                UpdateRenderButton();
            }
        }

        private void DoSVGSave(String path, UploadPrefs prefs)
        {
            SetMessage(null);
            if (!renderHelper.Renderer) {
                SystemSounds.Beep.Play();
                SetMessage("There is no SVG data to save.");
                return;
            }
            if (path.Length == 0) {
                SystemSounds.Beep.Play();
                SetMessage("Bad file name.");
                return;
            }

            if (!renderHelper.MakeSVGCanvas(path, renderParameters.width, renderParameters.height, prefs)) 
            {
                SystemSounds.Beep.Play();
                SetMessage("An error occurred while saving the SVG file.");
                return;
            }

            SetMessage("Saving SVG file...");
            renderParameters.action = RenderParameters.RenderActions.SaveSVG;
            postAction = PostRenderAction.DoNothing;
            if (renderHelper.PerformRender(renderThread)) {
                statusTimer.Start();
                UpdateRenderButton();
            }
        }

        private void SetupCanvas(int width, int height)
        {
            renderHelper.MakeCanvas(width, height);
        }

        private void menuRStopClick(object sender, EventArgs e)
        {
            if (renderHelper.Renderer && renderThread.IsBusy) {
                if (renderHelper.RequestFinishUp) {
                    renderHelper.RequestStop = true;
                } else {
                    renderHelper.RequestFinishUp = true;
                    UpdateRenderButton();
                }
            }
        }

        private void menuROutputClick(object sender, EventArgs e)
        {
            if (moviePlayer != null && !moviePlayer.HasExited) {
                // Should close and release temp file before save dialog shows
                moviePlayer.CloseMainWindow();
            }
            moviePlayer = null;

            if (!renderHelper.Canvas && movieFile == null) {
                SetMessage("There is nothing to save.");
                SystemSounds.Asterisk.Play();
                return;
            }

            if (renderThread.IsBusy) {
                postAction = PostRenderAction.SaveOutput;
                return;
            }

            if (movieFile != null) {
                using (var saveMovieDlg = new SaveFileDialog {
                    Filter = "MOV files (*.mov)|*.mov|All files (*.*)|*.*",
                    FileName = Path.GetFileNameWithoutExtension(Text) + ".mov",
                    OverwritePrompt = true
                }) 
                {
                    if (saveMovieDlg.ShowDialog() == DialogResult.OK) {
                        if (File.Exists(saveMovieDlg.FileName)) {
                            try {
                                File.Delete(saveMovieDlg.FileName);
                            } catch {
                                SetMessage("Cannot overwrite destination.");
                                SystemSounds.Asterisk.Play();
                                return;
                            }
                        }
                        try {
                            File.Move(movieFile, saveMovieDlg.FileName);
                            movieFile = null;
                            SetMessage("Movie saved.");
                        } catch {
                            SetMessage("Movie save failed.");
                            SystemSounds.Asterisk.Play();
                            return;
                        }
                    }
                }
                return;
            }

            using (var saveImageDlg = new CppWrapper.SaveImage(renderHelper.Frieze, renderHelper.Tiled,
                Path.GetFileNameWithoutExtension(Text) + ".png", Path.GetDirectoryName(Text))) 
            {
                var prefs = UploadPrefs;
                if (saveImageDlg.ShowTheDialog(MdiParent, prefs) == DialogResult.OK) {
                    UploadPrefs = prefs;
                    switch (saveImageDlg.FileDlgFilterIndex) {
                        case 1: // PNG
                            renderHelper.SaveToPNGorJPEG(prefs, saveImageDlg.FileDlgFileName, false);
                            break;
                        case 2: // JPEG
                            renderHelper.SaveToPNGorJPEG(prefs, saveImageDlg.FileDlgFileName, true);
                            break;
                        case 3: // SVG
                            DoSVGSave(saveImageDlg.FileDlgFileName, prefs);
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

            renderHelper.UploadDesign(this, prefs);

            if (prefs.Updated)
                UploadPrefs = prefs;
        }

        private void NextVariationClick(object sender, EventArgs e)
        {
            ReuseVariation = true;
            ++currentVariation;
            if (currentVariation > RenderHelper.MaxVariation || currentVariation < RenderHelper.MinVariation)
                currentVariation = RenderHelper.MaxVariation;
            variationTextBox.Text = RenderHelper.VariationToString(currentVariation);
        }

        private void PrevVariationClick(object sender, EventArgs e)
        {
            ReuseVariation = true;
            --currentVariation;
            if (currentVariation > RenderHelper.MaxVariation || currentVariation < RenderHelper.MinVariation)
                currentVariation = RenderHelper.MinVariation;
            variationTextBox.Text = RenderHelper.VariationToString(currentVariation);
        }

        private void FormIsClosing(object sender, FormClosingEventArgs e)
        {
            canceledByUser = false;

            // we can't close the window while the worker thread is running, so stop it
            if (renderThread.IsBusy) {
                // remember to close the window when the thread ends
                postAction = PostRenderAction.Close;
                renderHelper.RequestStop = true;
                e.Cancel = true;
                return;
            }

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

        private void StatusTick(object sender, EventArgs e)
        {
            if (renderHelper.Renderer && renderThread.IsBusy) {
                UpdateRenderButton();
                renderHelper.RequestUpdate();
            }
        }

        private void RenderBoxSizeChanged(object sender, EventArgs e)
        {
            if (renderBox.Size != DisplayImageSize)
                mDisplayImage = null;
        }

        private void FormHasClosed(object sender, FormClosedEventArgs e)
        {
            MovieCleaner.Clean(moviePlayer, movieFile);
            moviePlayer = null; movieFile = null;

            renderHelper.Dispose();
        }
    }
}
