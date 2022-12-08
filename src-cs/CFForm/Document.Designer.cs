namespace CFForm
{
    partial class Document
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);

            MovieCleaner.Clean(moviePlayer, movieFile);
            moviePlayer = null; movieFile = null;
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Document));
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.renderButton = new System.Windows.Forms.ToolStripSplitButton();
            this.renderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.sizedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.animateToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.frameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveButton = new System.Windows.Forms.ToolStripButton();
            this.progressBar = new System.Windows.Forms.ToolStripProgressBar();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.variationTextBox = new System.Windows.Forms.ToolStripTextBox();
            this.prevVariation = new System.Windows.Forms.ToolStripButton();
            this.nextVariation = new System.Windows.Forms.ToolStripButton();
            this.frameSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.frameLabel = new System.Windows.Forms.ToolStripLabel();
            this.frameTextBox = new System.Windows.Forms.ToolStripTextBox();
            this.framePrev = new System.Windows.Forms.ToolStripButton();
            this.frameNext = new System.Windows.Forms.ToolStripButton();
            this.sizeSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.sizeLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.sizeWidthBox = new System.Windows.Forms.ToolStripTextBox();
            this.sizeLabel2 = new System.Windows.Forms.ToolStripLabel();
            this.sizeHeightBox = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.statusLabel = new System.Windows.Forms.ToolStripLabel();
            this.documentSplitter = new System.Windows.Forms.SplitContainer();
            this.editorSplitter = new System.Windows.Forms.SplitContainer();
            this.cfdgText = new ScintillaNET.Scintilla();
            this.cfdgMessage = new System.Windows.Forms.WebBrowser();
            this.renderBox = new System.Windows.Forms.PictureBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.menuFile = new System.Windows.Forms.ToolStripMenuItem();
            this.menuFSave = new System.Windows.Forms.ToolStripMenuItem();
            this.menuFSaveAs = new System.Windows.Forms.ToolStripMenuItem();
            this.menuFClose = new System.Windows.Forms.ToolStripMenuItem();
            this.menuFRevert = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEdit = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEUndo = new System.Windows.Forms.ToolStripMenuItem();
            this.menuERedo = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.menuECut = new System.Windows.Forms.ToolStripMenuItem();
            this.menuECopy = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEPaste = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEDelete = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.menuEInsertChar = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsLE = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsGE = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsNE = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsEllipsis = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsPlusMinus = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsInf = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsPi = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsertSymm = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsCyclic = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsDihedral = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem5 = new System.Windows.Forms.ToolStripSeparator();
            this.menuEInsp11g = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsp11m = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsp1m1 = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsp2 = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsp2mg = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsp2mm = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem12 = new System.Windows.Forms.ToolStripSeparator();
            this.menuEInsP2also = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInspm = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInspg = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInscm = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInspmm = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInspmg = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInspgg = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInscmm = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsp4 = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsp4m = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsp4g = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsp3 = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsp3m1 = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsp31m = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsp6 = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsp6m = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsertBlend = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsnormal = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsclear = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsxor = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsplus = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsmultiply = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsscreen = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsoverlay = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsdarken = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInslighten = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsdodge = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsburn = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInshard = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInssoft = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsdiff = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsexc = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsertVar = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsoverlap = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsalpha = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsbackgr = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsdynamic = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsfixed = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInscolor = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsrgb16 = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsframe = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsftime = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsimpure = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsnatural = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsshapes = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsminsize = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInssize = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsstartshape = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInssymm = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInstile = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInstime = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEInsertFlag = new System.Windows.Forms.ToolStripMenuItem();
            this.meniEInsmiterjoin = new System.Windows.Forms.ToolStripMenuItem();
            this.meniEInsroundjoin = new System.Windows.Forms.ToolStripMenuItem();
            this.meniEInsbeveljoin = new System.Windows.Forms.ToolStripMenuItem();
            this.meniEInsbuttcap = new System.Windows.Forms.ToolStripMenuItem();
            this.meniEInsroundcap = new System.Windows.Forms.ToolStripMenuItem();
            this.meniEInssquarecap = new System.Windows.Forms.ToolStripMenuItem();
            this.meniEInsarccw = new System.Windows.Forms.ToolStripMenuItem();
            this.meniEInsarclarge = new System.Windows.Forms.ToolStripMenuItem();
            this.meniEInscont = new System.Windows.Forms.ToolStripMenuItem();
            this.meniEInsalign = new System.Windows.Forms.ToolStripMenuItem();
            this.meniEInsevenodd = new System.Windows.Forms.ToolStripMenuItem();
            this.meniEInsiso = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
            this.menuEFind = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEFindPrev = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem4 = new System.Windows.Forms.ToolStripSeparator();
            this.menuEUndent = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEIndent = new System.Windows.Forms.ToolStripMenuItem();
            this.renderToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.menuRRender = new System.Windows.Forms.ToolStripMenuItem();
            this.menuRRenderSize = new System.Windows.Forms.ToolStripMenuItem();
            this.menuRAgain = new System.Windows.Forms.ToolStripMenuItem();
            this.menuRAnimate = new System.Windows.Forms.ToolStripMenuItem();
            this.menuRFrame = new System.Windows.Forms.ToolStripMenuItem();
            this.menuRStop = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem6 = new System.Windows.Forms.ToolStripSeparator();
            this.menuROutput = new System.Windows.Forms.ToolStripMenuItem();
            this.menuRGallery = new System.Windows.Forms.ToolStripMenuItem();
            this.colorCalculatorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.statusTimer = new System.Windows.Forms.Timer(this.components);
            this.toolStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.documentSplitter)).BeginInit();
            this.documentSplitter.Panel1.SuspendLayout();
            this.documentSplitter.Panel2.SuspendLayout();
            this.documentSplitter.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.editorSplitter)).BeginInit();
            this.editorSplitter.Panel1.SuspendLayout();
            this.editorSplitter.Panel2.SuspendLayout();
            this.editorSplitter.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.renderBox)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStrip1
            // 
            this.toolStrip1.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.renderButton,
            this.saveButton,
            this.progressBar,
            this.toolStripSeparator1,
            this.toolStripLabel1,
            this.variationTextBox,
            this.prevVariation,
            this.nextVariation,
            this.frameSeparator,
            this.frameLabel,
            this.frameTextBox,
            this.framePrev,
            this.frameNext,
            this.sizeSeparator,
            this.sizeLabel1,
            this.sizeWidthBox,
            this.sizeLabel2,
            this.sizeHeightBox,
            this.toolStripSeparator3,
            this.statusLabel});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(1688, 42);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // renderButton
            // 
            this.renderButton.AutoSize = false;
            this.renderButton.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.renderToolStripMenuItem,
            this.sizedToolStripMenuItem,
            this.animateToolStripMenuItem,
            this.frameToolStripMenuItem});
            this.renderButton.Image = ((System.Drawing.Image)(resources.GetObject("renderButton.Image")));
            this.renderButton.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.renderButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.renderButton.Name = "renderButton";
            this.renderButton.Size = new System.Drawing.Size(177, 36);
            this.renderButton.Text = "Render";
            this.renderButton.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.renderButton.ButtonClick += new System.EventHandler(this.renderButtonClick);
            // 
            // renderToolStripMenuItem
            // 
            this.renderToolStripMenuItem.Name = "renderToolStripMenuItem";
            this.renderToolStripMenuItem.Size = new System.Drawing.Size(328, 44);
            this.renderToolStripMenuItem.Tag = "0";
            this.renderToolStripMenuItem.Text = "Render";
            this.renderToolStripMenuItem.Click += new System.EventHandler(this.renderButtonChange);
            // 
            // sizedToolStripMenuItem
            // 
            this.sizedToolStripMenuItem.Name = "sizedToolStripMenuItem";
            this.sizedToolStripMenuItem.Size = new System.Drawing.Size(328, 44);
            this.sizedToolStripMenuItem.Tag = "1";
            this.sizedToolStripMenuItem.Text = "Render to Size";
            this.sizedToolStripMenuItem.Click += new System.EventHandler(this.renderButtonChange);
            // 
            // animateToolStripMenuItem
            // 
            this.animateToolStripMenuItem.Name = "animateToolStripMenuItem";
            this.animateToolStripMenuItem.Size = new System.Drawing.Size(328, 44);
            this.animateToolStripMenuItem.Tag = "2";
            this.animateToolStripMenuItem.Text = "Animate";
            this.animateToolStripMenuItem.Click += new System.EventHandler(this.renderButtonChange);
            // 
            // frameToolStripMenuItem
            // 
            this.frameToolStripMenuItem.Name = "frameToolStripMenuItem";
            this.frameToolStripMenuItem.Size = new System.Drawing.Size(328, 44);
            this.frameToolStripMenuItem.Tag = "3";
            this.frameToolStripMenuItem.Text = "Animate a Frame";
            this.frameToolStripMenuItem.Click += new System.EventHandler(this.renderButtonChange);
            // 
            // saveButton
            // 
            this.saveButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.saveButton.Image = ((System.Drawing.Image)(resources.GetObject("saveButton.Image")));
            this.saveButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(68, 36);
            this.saveButton.Text = "Save";
            // 
            // progressBar
            // 
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(100, 36);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 42);
            // 
            // toolStripLabel1
            // 
            this.toolStripLabel1.Name = "toolStripLabel1";
            this.toolStripLabel1.Size = new System.Drawing.Size(107, 36);
            this.toolStripLabel1.Text = "Variation";
            // 
            // variationTextBox
            // 
            this.variationTextBox.AutoSize = false;
            this.variationTextBox.Name = "variationTextBox";
            this.variationTextBox.Size = new System.Drawing.Size(140, 42);
            this.variationTextBox.Text = "WWWWWW";
            this.variationTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.variationKeyDown);
            this.variationTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.variationKeyPress);
            this.variationTextBox.TextChanged += new System.EventHandler(this.variationChanged);
            // 
            // prevVariation
            // 
            this.prevVariation.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.prevVariation.Image = ((System.Drawing.Image)(resources.GetObject("prevVariation.Image")));
            this.prevVariation.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.prevVariation.Name = "prevVariation";
            this.prevVariation.Size = new System.Drawing.Size(46, 36);
            this.prevVariation.Text = "◀";
            this.prevVariation.Click += new System.EventHandler(this.prevVariationClick);
            // 
            // nextVariation
            // 
            this.nextVariation.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.nextVariation.Image = ((System.Drawing.Image)(resources.GetObject("nextVariation.Image")));
            this.nextVariation.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.nextVariation.Name = "nextVariation";
            this.nextVariation.Size = new System.Drawing.Size(46, 36);
            this.nextVariation.Text = "▶";
            this.nextVariation.Click += new System.EventHandler(this.nextVariationClick);
            // 
            // frameSeparator
            // 
            this.frameSeparator.Name = "frameSeparator";
            this.frameSeparator.Size = new System.Drawing.Size(6, 42);
            this.frameSeparator.Visible = false;
            // 
            // frameLabel
            // 
            this.frameLabel.Name = "frameLabel";
            this.frameLabel.Size = new System.Drawing.Size(85, 36);
            this.frameLabel.Text = "Frame:";
            this.frameLabel.Visible = false;
            // 
            // frameTextBox
            // 
            this.frameTextBox.Name = "frameTextBox";
            this.frameTextBox.Size = new System.Drawing.Size(100, 42);
            this.frameTextBox.Text = "1";
            this.frameTextBox.Visible = false;
            this.frameTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.frameKeyPressed);
            this.frameTextBox.TextChanged += new System.EventHandler(this.frameChanged);
            // 
            // framePrev
            // 
            this.framePrev.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.framePrev.Image = ((System.Drawing.Image)(resources.GetObject("framePrev.Image")));
            this.framePrev.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.framePrev.Name = "framePrev";
            this.framePrev.Size = new System.Drawing.Size(46, 36);
            this.framePrev.Text = "◀";
            this.framePrev.Visible = false;
            // 
            // frameNext
            // 
            this.frameNext.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.frameNext.Image = ((System.Drawing.Image)(resources.GetObject("frameNext.Image")));
            this.frameNext.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.frameNext.Name = "frameNext";
            this.frameNext.Size = new System.Drawing.Size(46, 36);
            this.frameNext.Text = "▶";
            this.frameNext.Visible = false;
            // 
            // sizeSeparator
            // 
            this.sizeSeparator.Name = "sizeSeparator";
            this.sizeSeparator.Size = new System.Drawing.Size(6, 42);
            this.sizeSeparator.Visible = false;
            // 
            // sizeLabel1
            // 
            this.sizeLabel1.Name = "sizeLabel1";
            this.sizeLabel1.Size = new System.Drawing.Size(62, 36);
            this.sizeLabel1.Text = "Size:";
            this.sizeLabel1.Visible = false;
            // 
            // sizeWidthBox
            // 
            this.sizeWidthBox.Name = "sizeWidthBox";
            this.sizeWidthBox.Size = new System.Drawing.Size(100, 42);
            this.sizeWidthBox.Text = "1000";
            this.sizeWidthBox.Visible = false;
            this.sizeWidthBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.frameKeyPressed);
            this.sizeWidthBox.TextChanged += new System.EventHandler(this.sizeChanged);
            // 
            // sizeLabel2
            // 
            this.sizeLabel2.Name = "sizeLabel2";
            this.sizeLabel2.Size = new System.Drawing.Size(30, 36);
            this.sizeLabel2.Text = "×";
            this.sizeLabel2.Visible = false;
            // 
            // sizeHeightBox
            // 
            this.sizeHeightBox.Name = "sizeHeightBox";
            this.sizeHeightBox.Size = new System.Drawing.Size(100, 42);
            this.sizeHeightBox.Text = "1000";
            this.sizeHeightBox.Visible = false;
            this.sizeHeightBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.frameKeyPressed);
            this.sizeHeightBox.TextChanged += new System.EventHandler(this.sizeChanged);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 42);
            // 
            // statusLabel
            // 
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Overflow = System.Windows.Forms.ToolStripItemOverflow.Never;
            this.statusLabel.Size = new System.Drawing.Size(76, 36);
            this.statusLabel.Text = "status";
            // 
            // documentSplitter
            // 
            this.documentSplitter.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.documentSplitter.Dock = System.Windows.Forms.DockStyle.Fill;
            this.documentSplitter.Location = new System.Drawing.Point(0, 42);
            this.documentSplitter.Name = "documentSplitter";
            // 
            // documentSplitter.Panel1
            // 
            this.documentSplitter.Panel1.Controls.Add(this.editorSplitter);
            // 
            // documentSplitter.Panel2
            // 
            this.documentSplitter.Panel2.Controls.Add(this.renderBox);
            this.documentSplitter.Size = new System.Drawing.Size(1688, 1040);
            this.documentSplitter.SplitterDistance = 562;
            this.documentSplitter.SplitterWidth = 8;
            this.documentSplitter.TabIndex = 1;
            this.documentSplitter.SplitterMoved += new System.Windows.Forms.SplitterEventHandler(this.splitterMoved);
            // 
            // editorSplitter
            // 
            this.editorSplitter.AllowDrop = true;
            this.editorSplitter.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.editorSplitter.Dock = System.Windows.Forms.DockStyle.Fill;
            this.editorSplitter.Location = new System.Drawing.Point(0, 0);
            this.editorSplitter.Name = "editorSplitter";
            this.editorSplitter.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // editorSplitter.Panel1
            // 
            this.editorSplitter.Panel1.Controls.Add(this.cfdgText);
            // 
            // editorSplitter.Panel2
            // 
            this.editorSplitter.Panel2.Controls.Add(this.cfdgMessage);
            this.editorSplitter.Size = new System.Drawing.Size(562, 1040);
            this.editorSplitter.SplitterDistance = 689;
            this.editorSplitter.SplitterWidth = 8;
            this.editorSplitter.TabIndex = 0;
            this.editorSplitter.SplitterMoved += new System.Windows.Forms.SplitterEventHandler(this.splitterMoved);
            // 
            // cfdgText
            // 
            this.cfdgText.AutoCIgnoreCase = true;
            this.cfdgText.AutoCMaxHeight = 9;
            this.cfdgText.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cfdgText.IndentationGuides = ScintillaNET.IndentView.LookBoth;
            this.cfdgText.Location = new System.Drawing.Point(0, 0);
            this.cfdgText.Name = "cfdgText";
            this.cfdgText.Size = new System.Drawing.Size(558, 685);
            this.cfdgText.TabIndex = 0;
            this.cfdgText.Text = "scintilla1";
            this.cfdgText.AutoCCharDeleted += new System.EventHandler<System.EventArgs>(this.autoCCharDeleted);
            this.cfdgText.CharAdded += new System.EventHandler<ScintillaNET.CharAddedEventArgs>(this.charAdded);
            this.cfdgText.Delete += new System.EventHandler<ScintillaNET.ModificationEventArgs>(this.textChanged);
            this.cfdgText.Insert += new System.EventHandler<ScintillaNET.ModificationEventArgs>(this.textChanged);
            this.cfdgText.InsertCheck += new System.EventHandler<ScintillaNET.InsertCheckEventArgs>(this.insertionCheck);
            this.cfdgText.SavePointLeft += new System.EventHandler<System.EventArgs>(this.modifiedCFDG);
            this.cfdgText.SavePointReached += new System.EventHandler<System.EventArgs>(this.modifiedCFDG);
            this.cfdgText.StyleNeeded += new System.EventHandler<ScintillaNET.StyleNeededEventArgs>(this.styleCfdg);
            this.cfdgText.UpdateUI += new System.EventHandler<ScintillaNET.UpdateUIEventArgs>(this.updateUI);
            // 
            // cfdgMessage
            // 
            this.cfdgMessage.AllowWebBrowserDrop = false;
            this.cfdgMessage.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cfdgMessage.IsWebBrowserContextMenuEnabled = false;
            this.cfdgMessage.Location = new System.Drawing.Point(0, 0);
            this.cfdgMessage.MinimumSize = new System.Drawing.Size(20, 20);
            this.cfdgMessage.Name = "cfdgMessage";
            this.cfdgMessage.Size = new System.Drawing.Size(558, 339);
            this.cfdgMessage.TabIndex = 0;
            this.cfdgMessage.DocumentCompleted += new System.Windows.Forms.WebBrowserDocumentCompletedEventHandler(this.messageWindowReady);
            this.cfdgMessage.Navigating += new System.Windows.Forms.WebBrowserNavigatingEventHandler(this.errorNavigation);
            // 
            // renderBox
            // 
            this.renderBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.renderBox.Location = new System.Drawing.Point(0, 0);
            this.renderBox.Name = "renderBox";
            this.renderBox.Size = new System.Drawing.Size(1114, 1036);
            this.renderBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.renderBox.TabIndex = 0;
            this.renderBox.TabStop = false;
            this.renderBox.SizeChanged += new System.EventHandler(this.renderBoxSizeChanged);
            this.renderBox.DragDrop += new System.Windows.Forms.DragEventHandler(this.pictureDragDrop);
            this.renderBox.DragEnter += new System.Windows.Forms.DragEventHandler(this.pictureDragEnter);
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuFile,
            this.menuEdit,
            this.renderToolStripMenuItem1});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1688, 42);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            this.menuStrip1.Visible = false;
            // 
            // menuFile
            // 
            this.menuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuFSave,
            this.menuFSaveAs,
            this.menuFClose,
            this.menuFRevert});
            this.menuFile.MergeAction = System.Windows.Forms.MergeAction.MatchOnly;
            this.menuFile.Name = "menuFile";
            this.menuFile.Size = new System.Drawing.Size(71, 38);
            this.menuFile.Text = "&File";
            // 
            // menuFSave
            // 
            this.menuFSave.Image = ((System.Drawing.Image)(resources.GetObject("menuFSave.Image")));
            this.menuFSave.MergeAction = System.Windows.Forms.MergeAction.Insert;
            this.menuFSave.MergeIndex = 2;
            this.menuFSave.Name = "menuFSave";
            this.menuFSave.ShortcutKeyDisplayString = "Ctrl-S";
            this.menuFSave.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.menuFSave.Size = new System.Drawing.Size(271, 44);
            this.menuFSave.Text = "&Save";
            this.menuFSave.Click += new System.EventHandler(this.menuFSaveClick);
            // 
            // menuFSaveAs
            // 
            this.menuFSaveAs.Image = ((System.Drawing.Image)(resources.GetObject("menuFSaveAs.Image")));
            this.menuFSaveAs.MergeAction = System.Windows.Forms.MergeAction.Insert;
            this.menuFSaveAs.MergeIndex = 3;
            this.menuFSaveAs.Name = "menuFSaveAs";
            this.menuFSaveAs.Size = new System.Drawing.Size(271, 44);
            this.menuFSaveAs.Text = "Save &As";
            this.menuFSaveAs.Click += new System.EventHandler(this.menuFSaveAsClick);
            // 
            // menuFClose
            // 
            this.menuFClose.Image = ((System.Drawing.Image)(resources.GetObject("menuFClose.Image")));
            this.menuFClose.MergeAction = System.Windows.Forms.MergeAction.Insert;
            this.menuFClose.MergeIndex = 4;
            this.menuFClose.Name = "menuFClose";
            this.menuFClose.Size = new System.Drawing.Size(271, 44);
            this.menuFClose.Text = "&Close";
            this.menuFClose.Click += new System.EventHandler(this.menuFCloseClick);
            // 
            // menuFRevert
            // 
            this.menuFRevert.Image = ((System.Drawing.Image)(resources.GetObject("menuFRevert.Image")));
            this.menuFRevert.MergeAction = System.Windows.Forms.MergeAction.Insert;
            this.menuFRevert.MergeIndex = 5;
            this.menuFRevert.Name = "menuFRevert";
            this.menuFRevert.Size = new System.Drawing.Size(271, 44);
            this.menuFRevert.Text = "Re&vert";
            this.menuFRevert.Click += new System.EventHandler(this.menuFRevertClick);
            // 
            // menuEdit
            // 
            this.menuEdit.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuEUndo,
            this.menuERedo,
            this.toolStripMenuItem1,
            this.menuECut,
            this.menuECopy,
            this.menuEPaste,
            this.menuEDelete,
            this.toolStripMenuItem2,
            this.menuEInsertChar,
            this.menuEInsertSymm,
            this.menuEInsertBlend,
            this.menuEInsertVar,
            this.menuEInsertFlag,
            this.toolStripMenuItem3,
            this.menuEFind,
            this.menuEFindPrev,
            this.toolStripMenuItem4,
            this.menuEUndent,
            this.menuEIndent});
            this.menuEdit.MergeAction = System.Windows.Forms.MergeAction.Insert;
            this.menuEdit.MergeIndex = 1;
            this.menuEdit.Name = "menuEdit";
            this.menuEdit.Size = new System.Drawing.Size(74, 38);
            this.menuEdit.Text = "&Edit";
            this.menuEdit.DropDownOpened += new System.EventHandler(this.menuEditPopup);
            // 
            // menuEUndo
            // 
            this.menuEUndo.Image = ((System.Drawing.Image)(resources.GetObject("menuEUndo.Image")));
            this.menuEUndo.Name = "menuEUndo";
            this.menuEUndo.ShortcutKeyDisplayString = "Ctrl-Z";
            this.menuEUndo.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Z)));
            this.menuEUndo.Size = new System.Drawing.Size(437, 44);
            this.menuEUndo.Text = "&Undo";
            this.menuEUndo.Click += new System.EventHandler(this.menuEUndoClick);
            // 
            // menuERedo
            // 
            this.menuERedo.Image = ((System.Drawing.Image)(resources.GetObject("menuERedo.Image")));
            this.menuERedo.Name = "menuERedo";
            this.menuERedo.ShortcutKeyDisplayString = "Ctrl-Y";
            this.menuERedo.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Y)));
            this.menuERedo.Size = new System.Drawing.Size(437, 44);
            this.menuERedo.Text = "&Redo";
            this.menuERedo.Click += new System.EventHandler(this.menuERedoClick);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(434, 6);
            // 
            // menuECut
            // 
            this.menuECut.Image = ((System.Drawing.Image)(resources.GetObject("menuECut.Image")));
            this.menuECut.Name = "menuECut";
            this.menuECut.ShortcutKeyDisplayString = "Ctrl-X";
            this.menuECut.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.X)));
            this.menuECut.Size = new System.Drawing.Size(437, 44);
            this.menuECut.Text = "Cu&t";
            this.menuECut.Click += new System.EventHandler(this.menuECutClick);
            // 
            // menuECopy
            // 
            this.menuECopy.Image = ((System.Drawing.Image)(resources.GetObject("menuECopy.Image")));
            this.menuECopy.Name = "menuECopy";
            this.menuECopy.ShortcutKeyDisplayString = "Ctrl-C";
            this.menuECopy.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
            this.menuECopy.Size = new System.Drawing.Size(437, 44);
            this.menuECopy.Text = "&Copy";
            this.menuECopy.Click += new System.EventHandler(this.menuECopyClick);
            // 
            // menuEPaste
            // 
            this.menuEPaste.Image = ((System.Drawing.Image)(resources.GetObject("menuEPaste.Image")));
            this.menuEPaste.Name = "menuEPaste";
            this.menuEPaste.ShortcutKeyDisplayString = "Ctrl-V";
            this.menuEPaste.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.V)));
            this.menuEPaste.Size = new System.Drawing.Size(437, 44);
            this.menuEPaste.Text = "&Paste";
            this.menuEPaste.Click += new System.EventHandler(this.menuEPasteClick);
            // 
            // menuEDelete
            // 
            this.menuEDelete.Image = ((System.Drawing.Image)(resources.GetObject("menuEDelete.Image")));
            this.menuEDelete.Name = "menuEDelete";
            this.menuEDelete.ShortcutKeyDisplayString = "DEL";
            this.menuEDelete.ShortcutKeys = System.Windows.Forms.Keys.Delete;
            this.menuEDelete.Size = new System.Drawing.Size(437, 44);
            this.menuEDelete.Text = "&Delete";
            this.menuEDelete.Click += new System.EventHandler(this.menuEDeleteClick);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(434, 6);
            // 
            // menuEInsertChar
            // 
            this.menuEInsertChar.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuEInsLE,
            this.menuEInsGE,
            this.menuEInsNE,
            this.menuEInsEllipsis,
            this.menuEInsPlusMinus,
            this.menuEInsInf,
            this.menuEInsPi});
            this.menuEInsertChar.Name = "menuEInsertChar";
            this.menuEInsertChar.Size = new System.Drawing.Size(437, 44);
            this.menuEInsertChar.Text = "Insert Character";
            // 
            // menuEInsLE
            // 
            this.menuEInsLE.Name = "menuEInsLE";
            this.menuEInsLE.Size = new System.Drawing.Size(167, 44);
            this.menuEInsLE.Text = "≤";
            this.menuEInsLE.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsGE
            // 
            this.menuEInsGE.Name = "menuEInsGE";
            this.menuEInsGE.Size = new System.Drawing.Size(167, 44);
            this.menuEInsGE.Text = "≥";
            this.menuEInsGE.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsNE
            // 
            this.menuEInsNE.Name = "menuEInsNE";
            this.menuEInsNE.Size = new System.Drawing.Size(167, 44);
            this.menuEInsNE.Text = "≠";
            this.menuEInsNE.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsEllipsis
            // 
            this.menuEInsEllipsis.Name = "menuEInsEllipsis";
            this.menuEInsEllipsis.Size = new System.Drawing.Size(167, 44);
            this.menuEInsEllipsis.Text = "…";
            this.menuEInsEllipsis.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsPlusMinus
            // 
            this.menuEInsPlusMinus.Name = "menuEInsPlusMinus";
            this.menuEInsPlusMinus.Size = new System.Drawing.Size(167, 44);
            this.menuEInsPlusMinus.Text = "±";
            this.menuEInsPlusMinus.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsInf
            // 
            this.menuEInsInf.Name = "menuEInsInf";
            this.menuEInsInf.Size = new System.Drawing.Size(167, 44);
            this.menuEInsInf.Text = "∞";
            this.menuEInsInf.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsPi
            // 
            this.menuEInsPi.Name = "menuEInsPi";
            this.menuEInsPi.Size = new System.Drawing.Size(167, 44);
            this.menuEInsPi.Text = "π";
            this.menuEInsPi.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsertSymm
            // 
            this.menuEInsertSymm.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuEInsCyclic,
            this.menuEInsDihedral,
            this.toolStripMenuItem5,
            this.menuEInsp11g,
            this.menuEInsp11m,
            this.menuEInsp1m1,
            this.menuEInsp2,
            this.menuEInsp2mg,
            this.menuEInsp2mm,
            this.toolStripMenuItem12,
            this.menuEInsP2also,
            this.menuEInspm,
            this.menuEInspg,
            this.menuEInscm,
            this.menuEInspmm,
            this.menuEInspmg,
            this.menuEInspgg,
            this.menuEInscmm,
            this.menuEInsp4,
            this.menuEInsp4m,
            this.menuEInsp4g,
            this.menuEInsp3,
            this.menuEInsp3m1,
            this.menuEInsp31m,
            this.menuEInsp6,
            this.menuEInsp6m});
            this.menuEInsertSymm.Name = "menuEInsertSymm";
            this.menuEInsertSymm.Size = new System.Drawing.Size(437, 44);
            this.menuEInsertSymm.Text = "Insert Symmetry";
            this.menuEInsertSymm.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsCyclic
            // 
            this.menuEInsCyclic.Name = "menuEInsCyclic";
            this.menuEInsCyclic.Size = new System.Drawing.Size(274, 44);
            this.menuEInsCyclic.Text = "CF::Cyclic";
            // 
            // menuEInsDihedral
            // 
            this.menuEInsDihedral.Name = "menuEInsDihedral";
            this.menuEInsDihedral.Size = new System.Drawing.Size(274, 44);
            this.menuEInsDihedral.Text = "CF::Dihedral";
            this.menuEInsDihedral.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // toolStripMenuItem5
            // 
            this.toolStripMenuItem5.Name = "toolStripMenuItem5";
            this.toolStripMenuItem5.Size = new System.Drawing.Size(271, 6);
            // 
            // menuEInsp11g
            // 
            this.menuEInsp11g.Name = "menuEInsp11g";
            this.menuEInsp11g.Size = new System.Drawing.Size(274, 44);
            this.menuEInsp11g.Text = "CF::p11g";
            this.menuEInsp11g.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsp11m
            // 
            this.menuEInsp11m.Name = "menuEInsp11m";
            this.menuEInsp11m.Size = new System.Drawing.Size(274, 44);
            this.menuEInsp11m.Text = "CF::p11m";
            this.menuEInsp11m.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsp1m1
            // 
            this.menuEInsp1m1.Name = "menuEInsp1m1";
            this.menuEInsp1m1.Size = new System.Drawing.Size(274, 44);
            this.menuEInsp1m1.Text = "CF::p1m1";
            this.menuEInsp1m1.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsp2
            // 
            this.menuEInsp2.Name = "menuEInsp2";
            this.menuEInsp2.Size = new System.Drawing.Size(274, 44);
            this.menuEInsp2.Text = "CF::p2";
            this.menuEInsp2.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsp2mg
            // 
            this.menuEInsp2mg.Name = "menuEInsp2mg";
            this.menuEInsp2mg.Size = new System.Drawing.Size(274, 44);
            this.menuEInsp2mg.Text = "CF::p2mg";
            this.menuEInsp2mg.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsp2mm
            // 
            this.menuEInsp2mm.Name = "menuEInsp2mm";
            this.menuEInsp2mm.Size = new System.Drawing.Size(274, 44);
            this.menuEInsp2mm.Text = "CF::p2mm";
            this.menuEInsp2mm.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // toolStripMenuItem12
            // 
            this.toolStripMenuItem12.Name = "toolStripMenuItem12";
            this.toolStripMenuItem12.Size = new System.Drawing.Size(271, 6);
            // 
            // menuEInsP2also
            // 
            this.menuEInsP2also.Name = "menuEInsP2also";
            this.menuEInsP2also.Size = new System.Drawing.Size(274, 44);
            this.menuEInsP2also.Text = "CF::p2";
            this.menuEInsP2also.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInspm
            // 
            this.menuEInspm.Name = "menuEInspm";
            this.menuEInspm.Size = new System.Drawing.Size(274, 44);
            this.menuEInspm.Text = "CF::pm";
            this.menuEInspm.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInspg
            // 
            this.menuEInspg.Name = "menuEInspg";
            this.menuEInspg.Size = new System.Drawing.Size(274, 44);
            this.menuEInspg.Text = "CF::pg";
            this.menuEInspg.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInscm
            // 
            this.menuEInscm.Name = "menuEInscm";
            this.menuEInscm.Size = new System.Drawing.Size(274, 44);
            this.menuEInscm.Text = "CF::cm";
            this.menuEInscm.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInspmm
            // 
            this.menuEInspmm.Name = "menuEInspmm";
            this.menuEInspmm.Size = new System.Drawing.Size(274, 44);
            this.menuEInspmm.Text = "CF::pmm";
            this.menuEInspmm.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInspmg
            // 
            this.menuEInspmg.Name = "menuEInspmg";
            this.menuEInspmg.Size = new System.Drawing.Size(274, 44);
            this.menuEInspmg.Text = "CF::pmg";
            this.menuEInspmg.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInspgg
            // 
            this.menuEInspgg.Name = "menuEInspgg";
            this.menuEInspgg.Size = new System.Drawing.Size(274, 44);
            this.menuEInspgg.Text = "CF::pgg";
            this.menuEInspgg.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInscmm
            // 
            this.menuEInscmm.Name = "menuEInscmm";
            this.menuEInscmm.Size = new System.Drawing.Size(274, 44);
            this.menuEInscmm.Text = "CF::cmm";
            this.menuEInscmm.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsp4
            // 
            this.menuEInsp4.Name = "menuEInsp4";
            this.menuEInsp4.Size = new System.Drawing.Size(274, 44);
            this.menuEInsp4.Text = "CF::p4";
            this.menuEInsp4.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsp4m
            // 
            this.menuEInsp4m.Name = "menuEInsp4m";
            this.menuEInsp4m.Size = new System.Drawing.Size(274, 44);
            this.menuEInsp4m.Text = "CF::p4m";
            this.menuEInsp4m.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsp4g
            // 
            this.menuEInsp4g.Name = "menuEInsp4g";
            this.menuEInsp4g.Size = new System.Drawing.Size(274, 44);
            this.menuEInsp4g.Text = "CF::p4g";
            this.menuEInsp4g.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsp3
            // 
            this.menuEInsp3.Name = "menuEInsp3";
            this.menuEInsp3.Size = new System.Drawing.Size(274, 44);
            this.menuEInsp3.Text = "CF::p3";
            this.menuEInsp3.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsp3m1
            // 
            this.menuEInsp3m1.Name = "menuEInsp3m1";
            this.menuEInsp3m1.Size = new System.Drawing.Size(274, 44);
            this.menuEInsp3m1.Text = "CF::p3m1";
            this.menuEInsp3m1.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsp31m
            // 
            this.menuEInsp31m.Name = "menuEInsp31m";
            this.menuEInsp31m.Size = new System.Drawing.Size(274, 44);
            this.menuEInsp31m.Text = "CF::p31m";
            this.menuEInsp31m.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsp6
            // 
            this.menuEInsp6.Name = "menuEInsp6";
            this.menuEInsp6.Size = new System.Drawing.Size(274, 44);
            this.menuEInsp6.Text = "CF::p6";
            this.menuEInsp6.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsp6m
            // 
            this.menuEInsp6m.Name = "menuEInsp6m";
            this.menuEInsp6m.Size = new System.Drawing.Size(274, 44);
            this.menuEInsp6m.Text = "CF::p6m";
            this.menuEInsp6m.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsertBlend
            // 
            this.menuEInsertBlend.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuEInsnormal,
            this.menuEInsclear,
            this.menuEInsxor,
            this.menuEInsplus,
            this.menuEInsmultiply,
            this.menuEInsscreen,
            this.menuEInsoverlay,
            this.menuEInsdarken,
            this.menuEInslighten,
            this.menuEInsdodge,
            this.menuEInsburn,
            this.menuEInshard,
            this.menuEInssoft,
            this.menuEInsdiff,
            this.menuEInsexc});
            this.menuEInsertBlend.Name = "menuEInsertBlend";
            this.menuEInsertBlend.Size = new System.Drawing.Size(437, 44);
            this.menuEInsertBlend.Text = "Insert Blend";
            // 
            // menuEInsnormal
            // 
            this.menuEInsnormal.Name = "menuEInsnormal";
            this.menuEInsnormal.Size = new System.Drawing.Size(313, 44);
            this.menuEInsnormal.Text = "CF::Normal";
            this.menuEInsnormal.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsclear
            // 
            this.menuEInsclear.Name = "menuEInsclear";
            this.menuEInsclear.Size = new System.Drawing.Size(313, 44);
            this.menuEInsclear.Text = "CF::Clear";
            this.menuEInsclear.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsxor
            // 
            this.menuEInsxor.Name = "menuEInsxor";
            this.menuEInsxor.Size = new System.Drawing.Size(313, 44);
            this.menuEInsxor.Text = "CF::Xor";
            this.menuEInsxor.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsplus
            // 
            this.menuEInsplus.Name = "menuEInsplus";
            this.menuEInsplus.Size = new System.Drawing.Size(313, 44);
            this.menuEInsplus.Text = "CF::Plus";
            this.menuEInsplus.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsmultiply
            // 
            this.menuEInsmultiply.Name = "menuEInsmultiply";
            this.menuEInsmultiply.Size = new System.Drawing.Size(313, 44);
            this.menuEInsmultiply.Text = "CF::Multiply";
            this.menuEInsmultiply.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsscreen
            // 
            this.menuEInsscreen.Name = "menuEInsscreen";
            this.menuEInsscreen.Size = new System.Drawing.Size(313, 44);
            this.menuEInsscreen.Text = "CF::Screen";
            this.menuEInsscreen.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsoverlay
            // 
            this.menuEInsoverlay.Name = "menuEInsoverlay";
            this.menuEInsoverlay.Size = new System.Drawing.Size(313, 44);
            this.menuEInsoverlay.Text = "CF::Overlay";
            this.menuEInsoverlay.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsdarken
            // 
            this.menuEInsdarken.Name = "menuEInsdarken";
            this.menuEInsdarken.Size = new System.Drawing.Size(313, 44);
            this.menuEInsdarken.Text = "CF::Darken";
            this.menuEInsdarken.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInslighten
            // 
            this.menuEInslighten.Name = "menuEInslighten";
            this.menuEInslighten.Size = new System.Drawing.Size(313, 44);
            this.menuEInslighten.Text = "CF::Lighten";
            this.menuEInslighten.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsdodge
            // 
            this.menuEInsdodge.Name = "menuEInsdodge";
            this.menuEInsdodge.Size = new System.Drawing.Size(313, 44);
            this.menuEInsdodge.Text = "CF::ColorDodge";
            this.menuEInsdodge.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsburn
            // 
            this.menuEInsburn.Name = "menuEInsburn";
            this.menuEInsburn.Size = new System.Drawing.Size(313, 44);
            this.menuEInsburn.Text = "CF::ColorBurn";
            this.menuEInsburn.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInshard
            // 
            this.menuEInshard.Name = "menuEInshard";
            this.menuEInshard.Size = new System.Drawing.Size(313, 44);
            this.menuEInshard.Text = "CF::HardLight";
            this.menuEInshard.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInssoft
            // 
            this.menuEInssoft.Name = "menuEInssoft";
            this.menuEInssoft.Size = new System.Drawing.Size(313, 44);
            this.menuEInssoft.Text = "CF::SoftLight";
            this.menuEInssoft.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsdiff
            // 
            this.menuEInsdiff.Name = "menuEInsdiff";
            this.menuEInsdiff.Size = new System.Drawing.Size(313, 44);
            this.menuEInsdiff.Text = "CF::Difference";
            this.menuEInsdiff.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsexc
            // 
            this.menuEInsexc.Name = "menuEInsexc";
            this.menuEInsexc.Size = new System.Drawing.Size(313, 44);
            this.menuEInsexc.Text = "CF::Exclusion";
            this.menuEInsexc.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsertVar
            // 
            this.menuEInsertVar.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuEInsoverlap,
            this.menuEInsalpha,
            this.menuEInsbackgr,
            this.menuEInsdynamic,
            this.menuEInsfixed,
            this.menuEInscolor,
            this.menuEInsrgb16,
            this.menuEInsframe,
            this.menuEInsftime,
            this.menuEInsimpure,
            this.menuEInsnatural,
            this.menuEInsshapes,
            this.menuEInsminsize,
            this.menuEInssize,
            this.menuEInsstartshape,
            this.menuEInssymm,
            this.menuEInstile,
            this.menuEInstime});
            this.menuEInsertVar.Name = "menuEInsertVar";
            this.menuEInsertVar.Size = new System.Drawing.Size(437, 44);
            this.menuEInsertVar.Text = "Insert Variable";
            // 
            // menuEInsoverlap
            // 
            this.menuEInsoverlap.Name = "menuEInsoverlap";
            this.menuEInsoverlap.Size = new System.Drawing.Size(528, 44);
            this.menuEInsoverlap.Text = "CF::AllowOverlap = 1";
            this.menuEInsoverlap.ToolTipText = "Allow variables with same name";
            this.menuEInsoverlap.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsalpha
            // 
            this.menuEInsalpha.Name = "menuEInsalpha";
            this.menuEInsalpha.Size = new System.Drawing.Size(528, 44);
            this.menuEInsalpha.Text = "CF::Alpha = 1";
            this.menuEInsalpha.ToolTipText = "Force alpha channel";
            this.menuEInsalpha.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsbackgr
            // 
            this.menuEInsbackgr.Name = "menuEInsbackgr";
            this.menuEInsbackgr.Size = new System.Drawing.Size(528, 44);
            this.menuEInsbackgr.Text = "CF::Background = [b 1]";
            this.menuEInsbackgr.ToolTipText = "Set background color";
            this.menuEInsbackgr.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsdynamic
            // 
            this.menuEInsdynamic.Name = "menuEInsdynamic";
            this.menuEInsdynamic.Size = new System.Drawing.Size(528, 44);
            this.menuEInsdynamic.Text = "CF::BorderDynamic = 0";
            this.menuEInsdynamic.ToolTipText = "Set dynamic border";
            this.menuEInsdynamic.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsfixed
            // 
            this.menuEInsfixed.Name = "menuEInsfixed";
            this.menuEInsfixed.Size = new System.Drawing.Size(528, 44);
            this.menuEInsfixed.Text = "CF::BorderFixed = 0";
            this.menuEInsfixed.ToolTipText = "Set fixed border";
            this.menuEInsfixed.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInscolor
            // 
            this.menuEInscolor.Name = "menuEInscolor";
            this.menuEInscolor.Size = new System.Drawing.Size(528, 44);
            this.menuEInscolor.Text = "CF::Color = 1";
            this.menuEInscolor.ToolTipText = "Force color channels";
            this.menuEInscolor.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsrgb16
            // 
            this.menuEInsrgb16.Name = "menuEInsrgb16";
            this.menuEInsrgb16.Size = new System.Drawing.Size(528, 44);
            this.menuEInsrgb16.Text = "CF::ColorDepth = 16";
            this.menuEInsrgb16.ToolTipText = "16bit color channels";
            this.menuEInsrgb16.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsframe
            // 
            this.menuEInsframe.Name = "menuEInsframe";
            this.menuEInsframe.Size = new System.Drawing.Size(528, 44);
            this.menuEInsframe.Text = "CF::Frame = 60";
            this.menuEInsframe.ToolTipText = "Set frame number";
            this.menuEInsframe.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsftime
            // 
            this.menuEInsftime.Name = "menuEInsftime";
            this.menuEInsftime.Size = new System.Drawing.Size(528, 44);
            this.menuEInsftime.Text = "CF::FrameTime = 0.2";
            this.menuEInsftime.ToolTipText = "Set frame time";
            this.menuEInsftime.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsimpure
            // 
            this.menuEInsimpure.Name = "menuEInsimpure";
            this.menuEInsimpure.Size = new System.Drawing.Size(528, 44);
            this.menuEInsimpure.Text = "CF::Impure = 1";
            this.menuEInsimpure.ToolTipText = "Disable purity restrictions";
            this.menuEInsimpure.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsnatural
            // 
            this.menuEInsnatural.Name = "menuEInsnatural";
            this.menuEInsnatural.Size = new System.Drawing.Size(528, 44);
            this.menuEInsnatural.Text = "CF::MaxNatural = 10000";
            this.menuEInsnatural.ToolTipText = "Largest natural number";
            this.menuEInsnatural.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsshapes
            // 
            this.menuEInsshapes.Name = "menuEInsshapes";
            this.menuEInsshapes.Size = new System.Drawing.Size(528, 44);
            this.menuEInsshapes.Text = "CF::MaxShapes = 1000000";
            this.menuEInsshapes.ToolTipText = "Maximum shapes rendered";
            this.menuEInsshapes.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsminsize
            // 
            this.menuEInsminsize.Name = "menuEInsminsize";
            this.menuEInsminsize.Size = new System.Drawing.Size(528, 44);
            this.menuEInsminsize.Text = "CF::MinimumSize = 0.1";
            this.menuEInsminsize.ToolTipText = "Smallest shape rendered";
            this.menuEInsminsize.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInssize
            // 
            this.menuEInssize.Name = "menuEInssize";
            this.menuEInssize.Size = new System.Drawing.Size(528, 44);
            this.menuEInssize.Text = "CF::Size = [s 4 5]";
            this.menuEInssize.ToolTipText = "Force canvas size";
            this.menuEInssize.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsstartshape
            // 
            this.menuEInsstartshape.Name = "menuEInsstartshape";
            this.menuEInsstartshape.Size = new System.Drawing.Size(528, 44);
            this.menuEInsstartshape.Text = "CF::StartShape = foo,[b 1]";
            this.menuEInsstartshape.ToolTipText = "Alternate startshape setting";
            this.menuEInsstartshape.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInssymm
            // 
            this.menuEInssymm.Name = "menuEInssymm";
            this.menuEInssymm.Size = new System.Drawing.Size(528, 44);
            this.menuEInssymm.Text = "CF::Symmetry = CF::pmg, 1, 0.2, -0.5";
            this.menuEInssymm.ToolTipText = "Apply symmetry to design";
            this.menuEInssymm.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInstile
            // 
            this.menuEInstile.Name = "menuEInstile";
            this.menuEInstile.Size = new System.Drawing.Size(528, 44);
            this.menuEInstile.Text = "CF::Tile = [skew 15 15 r 15]";
            this.menuEInstile.ToolTipText = "Enable tiled rendering";
            this.menuEInstile.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInstime
            // 
            this.menuEInstime.Name = "menuEInstime";
            this.menuEInstime.Size = new System.Drawing.Size(528, 44);
            this.menuEInstime.Text = "CF::Time = [time 0 1]";
            this.menuEInstime.ToolTipText = "Force animation time span";
            this.menuEInstime.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // menuEInsertFlag
            // 
            this.menuEInsertFlag.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.meniEInsmiterjoin,
            this.meniEInsroundjoin,
            this.meniEInsbeveljoin,
            this.meniEInsbuttcap,
            this.meniEInsroundcap,
            this.meniEInssquarecap,
            this.meniEInsarccw,
            this.meniEInsarclarge,
            this.meniEInscont,
            this.meniEInsalign,
            this.meniEInsevenodd,
            this.meniEInsiso});
            this.menuEInsertFlag.Name = "menuEInsertFlag";
            this.menuEInsertFlag.Size = new System.Drawing.Size(437, 44);
            this.menuEInsertFlag.Text = "Insert Flag";
            // 
            // meniEInsmiterjoin
            // 
            this.meniEInsmiterjoin.Name = "meniEInsmiterjoin";
            this.meniEInsmiterjoin.Size = new System.Drawing.Size(307, 44);
            this.meniEInsmiterjoin.Text = "CF::MiterJoin";
            this.meniEInsmiterjoin.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // meniEInsroundjoin
            // 
            this.meniEInsroundjoin.Name = "meniEInsroundjoin";
            this.meniEInsroundjoin.Size = new System.Drawing.Size(307, 44);
            this.meniEInsroundjoin.Text = "CF::RoundJoin";
            this.meniEInsroundjoin.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // meniEInsbeveljoin
            // 
            this.meniEInsbeveljoin.Name = "meniEInsbeveljoin";
            this.meniEInsbeveljoin.Size = new System.Drawing.Size(307, 44);
            this.meniEInsbeveljoin.Text = "CF::BevelJoin";
            this.meniEInsbeveljoin.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // meniEInsbuttcap
            // 
            this.meniEInsbuttcap.Name = "meniEInsbuttcap";
            this.meniEInsbuttcap.Size = new System.Drawing.Size(307, 44);
            this.meniEInsbuttcap.Text = "CF::ButtCap";
            this.meniEInsbuttcap.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // meniEInsroundcap
            // 
            this.meniEInsroundcap.Name = "meniEInsroundcap";
            this.meniEInsroundcap.Size = new System.Drawing.Size(307, 44);
            this.meniEInsroundcap.Text = "CF::RoundCap";
            this.meniEInsroundcap.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // meniEInssquarecap
            // 
            this.meniEInssquarecap.Name = "meniEInssquarecap";
            this.meniEInssquarecap.Size = new System.Drawing.Size(307, 44);
            this.meniEInssquarecap.Text = "CF::SquareCap";
            this.meniEInssquarecap.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // meniEInsarccw
            // 
            this.meniEInsarccw.Name = "meniEInsarccw";
            this.meniEInsarccw.Size = new System.Drawing.Size(307, 44);
            this.meniEInsarccw.Text = "CF::ArcCW";
            this.meniEInsarccw.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // meniEInsarclarge
            // 
            this.meniEInsarclarge.Name = "meniEInsarclarge";
            this.meniEInsarclarge.Size = new System.Drawing.Size(307, 44);
            this.meniEInsarclarge.Text = "CF::ArcLarge";
            this.meniEInsarclarge.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // meniEInscont
            // 
            this.meniEInscont.Name = "meniEInscont";
            this.meniEInscont.Size = new System.Drawing.Size(307, 44);
            this.meniEInscont.Text = "CF::Continuous";
            this.meniEInscont.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // meniEInsalign
            // 
            this.meniEInsalign.Name = "meniEInsalign";
            this.meniEInsalign.Size = new System.Drawing.Size(307, 44);
            this.meniEInsalign.Text = "CF::Align";
            this.meniEInsalign.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // meniEInsevenodd
            // 
            this.meniEInsevenodd.Name = "meniEInsevenodd";
            this.meniEInsevenodd.Size = new System.Drawing.Size(307, 44);
            this.meniEInsevenodd.Text = "CF::EvenOdd";
            this.meniEInsevenodd.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // meniEInsiso
            // 
            this.meniEInsiso.Name = "meniEInsiso";
            this.meniEInsiso.Size = new System.Drawing.Size(307, 44);
            this.meniEInsiso.Text = "CF::IsoWidth";
            this.meniEInsiso.Click += new System.EventHandler(this.menuEUnicode);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(434, 6);
            // 
            // menuEFind
            // 
            this.menuEFind.Image = ((System.Drawing.Image)(resources.GetObject("menuEFind.Image")));
            this.menuEFind.Name = "menuEFind";
            this.menuEFind.ShortcutKeyDisplayString = "Ctrl-F";
            this.menuEFind.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.F)));
            this.menuEFind.Size = new System.Drawing.Size(437, 44);
            this.menuEFind.Text = "Find/Replace...";
            // 
            // menuEFindPrev
            // 
            this.menuEFindPrev.Image = ((System.Drawing.Image)(resources.GetObject("menuEFindPrev.Image")));
            this.menuEFindPrev.Name = "menuEFindPrev";
            this.menuEFindPrev.ShortcutKeyDisplayString = "Shift-Ctrl-F";
            this.menuEFindPrev.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
            | System.Windows.Forms.Keys.F)));
            this.menuEFindPrev.Size = new System.Drawing.Size(437, 44);
            this.menuEFindPrev.Tag = "prev";
            this.menuEFindPrev.Text = "Find Previous...";
            // 
            // toolStripMenuItem4
            // 
            this.toolStripMenuItem4.Name = "toolStripMenuItem4";
            this.toolStripMenuItem4.Size = new System.Drawing.Size(434, 6);
            // 
            // menuEUndent
            // 
            this.menuEUndent.Image = ((System.Drawing.Image)(resources.GetObject("menuEUndent.Image")));
            this.menuEUndent.Name = "menuEUndent";
            this.menuEUndent.ShortcutKeyDisplayString = "Ctrl-[";
            this.menuEUndent.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.OemOpenBrackets)));
            this.menuEUndent.Size = new System.Drawing.Size(437, 44);
            this.menuEUndent.Tag = "-1";
            this.menuEUndent.Text = "Remove Indent";
            this.menuEUndent.Click += new System.EventHandler(this.menuEIndentClick);
            // 
            // menuEIndent
            // 
            this.menuEIndent.Image = ((System.Drawing.Image)(resources.GetObject("menuEIndent.Image")));
            this.menuEIndent.Name = "menuEIndent";
            this.menuEIndent.ShortcutKeyDisplayString = "Ctrl-]";
            this.menuEIndent.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Oem6)));
            this.menuEIndent.Size = new System.Drawing.Size(437, 44);
            this.menuEIndent.Tag = "1";
            this.menuEIndent.Text = "Add Indent";
            this.menuEIndent.Click += new System.EventHandler(this.menuEIndentClick);
            // 
            // renderToolStripMenuItem1
            // 
            this.renderToolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuRRender,
            this.menuRRenderSize,
            this.menuRAgain,
            this.menuRAnimate,
            this.menuRFrame,
            this.menuRStop,
            this.toolStripMenuItem6,
            this.menuROutput,
            this.menuRGallery,
            this.colorCalculatorToolStripMenuItem});
            this.renderToolStripMenuItem1.MergeAction = System.Windows.Forms.MergeAction.Insert;
            this.renderToolStripMenuItem1.MergeIndex = 2;
            this.renderToolStripMenuItem1.Name = "renderToolStripMenuItem1";
            this.renderToolStripMenuItem1.Size = new System.Drawing.Size(109, 38);
            this.renderToolStripMenuItem1.Text = "&Render";
            // 
            // menuRRender
            // 
            this.menuRRender.Image = ((System.Drawing.Image)(resources.GetObject("menuRRender.Image")));
            this.menuRRender.Name = "menuRRender";
            this.menuRRender.ShortcutKeyDisplayString = "Ctrl-R";
            this.menuRRender.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.R)));
            this.menuRRender.Size = new System.Drawing.Size(464, 44);
            this.menuRRender.Text = "&Render";
            this.menuRRender.Click += new System.EventHandler(this.menuRRenderClick);
            // 
            // menuRRenderSize
            // 
            this.menuRRenderSize.Image = ((System.Drawing.Image)(resources.GetObject("menuRRenderSize.Image")));
            this.menuRRenderSize.Name = "menuRRenderSize";
            this.menuRRenderSize.ShortcutKeyDisplayString = "Shift-Ctrl-R";
            this.menuRRenderSize.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
            | System.Windows.Forms.Keys.R)));
            this.menuRRenderSize.Size = new System.Drawing.Size(464, 44);
            this.menuRRenderSize.Text = "Render to si&ze...";
            this.menuRRenderSize.Click += new System.EventHandler(this.menuRSizeClick);
            // 
            // menuRAgain
            // 
            this.menuRAgain.Image = ((System.Drawing.Image)(resources.GetObject("menuRAgain.Image")));
            this.menuRAgain.Name = "menuRAgain";
            this.menuRAgain.ShortcutKeyDisplayString = "Alt-Ctrl-R";
            this.menuRAgain.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Alt) 
            | System.Windows.Forms.Keys.R)));
            this.menuRAgain.Size = new System.Drawing.Size(464, 44);
            this.menuRAgain.Text = "Repea&t Last Render";
            this.menuRAgain.Click += new System.EventHandler(this.renderButtonClick);
            // 
            // menuRAnimate
            // 
            this.menuRAnimate.Image = ((System.Drawing.Image)(resources.GetObject("menuRAnimate.Image")));
            this.menuRAnimate.Name = "menuRAnimate";
            this.menuRAnimate.ShortcutKeyDisplayString = "Alt-Ctrl-A";
            this.menuRAnimate.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Alt) 
            | System.Windows.Forms.Keys.A)));
            this.menuRAnimate.Size = new System.Drawing.Size(464, 44);
            this.menuRAnimate.Text = "&Animate...";
            this.menuRAnimate.Click += new System.EventHandler(this.menuRAnimateClick);
            // 
            // menuRFrame
            // 
            this.menuRFrame.Name = "menuRFrame";
            this.menuRFrame.ShortcutKeyDisplayString = "Alt-Ctrl-F";
            this.menuRFrame.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Alt) 
            | System.Windows.Forms.Keys.F)));
            this.menuRFrame.Size = new System.Drawing.Size(464, 44);
            this.menuRFrame.Text = "Animate &Frame...";
            this.menuRFrame.Click += new System.EventHandler(this.menuRFrameClick);
            // 
            // menuRStop
            // 
            this.menuRStop.Name = "menuRStop";
            this.menuRStop.ShortcutKeyDisplayString = "Ctrl-END";
            this.menuRStop.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.End)));
            this.menuRStop.Size = new System.Drawing.Size(464, 44);
            this.menuRStop.Text = "&Stop";
            this.menuRStop.Click += new System.EventHandler(this.menuRStopClick);
            // 
            // toolStripMenuItem6
            // 
            this.toolStripMenuItem6.Name = "toolStripMenuItem6";
            this.toolStripMenuItem6.Size = new System.Drawing.Size(461, 6);
            // 
            // menuROutput
            // 
            this.menuROutput.Name = "menuROutput";
            this.menuROutput.ShortcutKeyDisplayString = "Ctrl-O";
            this.menuROutput.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.menuROutput.Size = new System.Drawing.Size(464, 44);
            this.menuROutput.Text = "Save &Output..";
            this.menuROutput.Click += new System.EventHandler(this.menuROutputClick);
            // 
            // menuRGallery
            // 
            this.menuRGallery.Name = "menuRGallery";
            this.menuRGallery.ShortcutKeyDisplayString = "Ctrl-U";
            this.menuRGallery.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.U)));
            this.menuRGallery.Size = new System.Drawing.Size(464, 44);
            this.menuRGallery.Text = "&Upload to Gallery...";
            this.menuRGallery.Click += new System.EventHandler(this.menuRGalleryClick);
            // 
            // colorCalculatorToolStripMenuItem
            // 
            this.colorCalculatorToolStripMenuItem.Name = "colorCalculatorToolStripMenuItem";
            this.colorCalculatorToolStripMenuItem.Size = new System.Drawing.Size(464, 44);
            this.colorCalculatorToolStripMenuItem.Text = "&Color Calculator";
            this.colorCalculatorToolStripMenuItem.Click += new System.EventHandler(this.menuRColorClick);
            // 
            // imageList1
            // 
            this.imageList1.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "busy_f01.ico");
            this.imageList1.Images.SetKeyName(1, "busy_f02.ico");
            this.imageList1.Images.SetKeyName(2, "busy_f03.ico");
            this.imageList1.Images.SetKeyName(3, "busy_f04.ico");
            this.imageList1.Images.SetKeyName(4, "busy_f05.ico");
            this.imageList1.Images.SetKeyName(5, "busy_f06.ico");
            this.imageList1.Images.SetKeyName(6, "busy_f07.ico");
            this.imageList1.Images.SetKeyName(7, "busy_f08.ico");
            this.imageList1.Images.SetKeyName(8, "busy_f09.ico");
            // 
            // statusTimer
            // 
            this.statusTimer.Tick += new System.EventHandler(this.statusTick);
            // 
            // Document
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(13F, 32F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1688, 1082);
            this.Controls.Add(this.documentSplitter);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Document";
            this.Text = "Document";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.formIsClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.formHasClosed);
            this.Load += new System.EventHandler(this.loadInitialization);
            this.Shown += new System.EventHandler(this.shownInitialization);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.documentSplitter.Panel1.ResumeLayout(false);
            this.documentSplitter.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.documentSplitter)).EndInit();
            this.documentSplitter.ResumeLayout(false);
            this.editorSplitter.Panel1.ResumeLayout(false);
            this.editorSplitter.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.editorSplitter)).EndInit();
            this.editorSplitter.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.renderBox)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private WebBrowser cfdgMessage;
        private ToolStrip toolStrip1;
        private ToolStripSplitButton renderButton;
        private ToolStripMenuItem renderToolStripMenuItem;
        private ToolStripMenuItem sizedToolStripMenuItem;
        private ToolStripMenuItem animateToolStripMenuItem;
        private ToolStripMenuItem frameToolStripMenuItem;
        private ToolStripButton saveButton;
        private ToolStripProgressBar progressBar;
        private ToolStripSeparator toolStripSeparator1;
        private ToolStripLabel toolStripLabel1;
        private ToolStripTextBox variationTextBox;
        private ToolStripButton prevVariation;
        private ToolStripButton nextVariation;
        private ToolStripSeparator frameSeparator;
        private ToolStripLabel frameLabel;
        private ToolStripTextBox frameTextBox;
        private ToolStripButton framePrev;
        private ToolStripButton frameNext;
        private ToolStripSeparator sizeSeparator;
        private ToolStripLabel sizeLabel1;
        private ToolStripTextBox sizeWidthBox;
        private ToolStripLabel sizeLabel2;
        private ToolStripTextBox sizeHeightBox;
        private ToolStripSeparator toolStripSeparator3;
        private ToolStripLabel statusLabel;
        private PictureBox renderBox;
        public SplitContainer documentSplitter;
        public SplitContainer editorSplitter;
        private MenuStrip menuStrip1;
        private ToolStripMenuItem menuFile;
        private ToolStripMenuItem menuFSave;
        private ToolStripMenuItem menuFSaveAs;
        private ToolStripMenuItem menuFClose;
        private ToolStripMenuItem menuFRevert;
        private ToolStripMenuItem menuEdit;
        private ToolStripMenuItem menuEUndo;
        private ToolStripMenuItem menuERedo;
        private ToolStripSeparator toolStripMenuItem1;
        private ToolStripMenuItem menuECut;
        private ToolStripMenuItem menuECopy;
        private ToolStripMenuItem menuEPaste;
        private ToolStripMenuItem menuEDelete;
        private ToolStripSeparator toolStripMenuItem2;
        private ToolStripMenuItem menuEInsertChar;
        private ToolStripMenuItem menuEInsertSymm;
        private ToolStripMenuItem menuEInsertBlend;
        private ToolStripMenuItem menuEInsertVar;
        private ToolStripMenuItem menuEInsertFlag;
        private ToolStripSeparator toolStripMenuItem3;
        private ToolStripMenuItem menuEFind;
        private ToolStripMenuItem menuEFindPrev;
        private ToolStripSeparator toolStripMenuItem4;
        private ToolStripMenuItem menuEUndent;
        private ToolStripMenuItem menuEIndent;
        private ToolStripMenuItem renderToolStripMenuItem1;
        private ToolStripMenuItem menuEInsLE;
        private ToolStripMenuItem menuEInsGE;
        private ToolStripMenuItem menuEInsNE;
        private ToolStripMenuItem menuEInsEllipsis;
        private ToolStripMenuItem menuEInsPlusMinus;
        private ToolStripMenuItem menuEInsInf;
        private ToolStripMenuItem menuEInsPi;
        private ToolStripMenuItem menuEInsCyclic;
        private ToolStripMenuItem menuEInsDihedral;
        private ToolStripSeparator toolStripMenuItem5;
        private ToolStripMenuItem menuEInsp11g;
        private ToolStripMenuItem menuEInsp11m;
        private ToolStripMenuItem menuEInsp1m1;
        private ToolStripMenuItem menuEInsp2;
        private ToolStripMenuItem menuEInsp2mg;
        private ToolStripMenuItem menuEInsp2mm;
        private ToolStripSeparator toolStripMenuItem12;
        private ToolStripMenuItem menuEInsP2also;
        private ToolStripMenuItem menuEInspm;
        private ToolStripMenuItem menuEInspg;
        private ToolStripMenuItem menuEInscm;
        private ToolStripMenuItem menuEInspmm;
        private ToolStripMenuItem menuEInspmg;
        private ToolStripMenuItem menuEInspgg;
        private ToolStripMenuItem menuEInscmm;
        private ToolStripMenuItem menuEInsp4;
        private ToolStripMenuItem menuEInsp4m;
        private ToolStripMenuItem menuEInsp4g;
        private ToolStripMenuItem menuEInsp3;
        private ToolStripMenuItem menuEInsp3m1;
        private ToolStripMenuItem menuEInsp31m;
        private ToolStripMenuItem menuEInsp6;
        private ToolStripMenuItem menuEInsp6m;
        private ToolStripMenuItem menuEInsnormal;
        private ToolStripMenuItem menuEInsclear;
        private ToolStripMenuItem menuEInsxor;
        private ToolStripMenuItem menuEInsplus;
        private ToolStripMenuItem menuEInsmultiply;
        private ToolStripMenuItem menuEInsscreen;
        private ToolStripMenuItem menuEInsoverlay;
        private ToolStripMenuItem menuEInsdarken;
        private ToolStripMenuItem menuEInslighten;
        private ToolStripMenuItem menuEInsdodge;
        private ToolStripMenuItem menuEInsburn;
        private ToolStripMenuItem menuEInshard;
        private ToolStripMenuItem menuEInssoft;
        private ToolStripMenuItem menuEInsdiff;
        private ToolStripMenuItem menuEInsexc;
        private ToolStripMenuItem menuEInsoverlap;
        private ToolStripMenuItem menuEInsalpha;
        private ToolStripMenuItem menuEInsbackgr;
        private ToolStripMenuItem menuEInsdynamic;
        private ToolStripMenuItem menuEInsfixed;
        private ToolStripMenuItem menuEInscolor;
        private ToolStripMenuItem menuEInsrgb16;
        private ToolStripMenuItem menuEInsframe;
        private ToolStripMenuItem menuEInsftime;
        private ToolStripMenuItem menuEInsimpure;
        private ToolStripMenuItem menuEInsnatural;
        private ToolStripMenuItem menuEInsshapes;
        private ToolStripMenuItem menuEInsminsize;
        private ToolStripMenuItem menuEInssize;
        private ToolStripMenuItem menuEInssymm;
        private ToolStripMenuItem menuEInstile;
        private ToolStripMenuItem menuEInstime;
        private ToolStripMenuItem meniEInsmiterjoin;
        private ToolStripMenuItem meniEInsroundjoin;
        private ToolStripMenuItem meniEInsbeveljoin;
        private ToolStripMenuItem meniEInsbuttcap;
        private ToolStripMenuItem meniEInsroundcap;
        private ToolStripMenuItem meniEInssquarecap;
        private ToolStripMenuItem meniEInsarccw;
        private ToolStripMenuItem meniEInsarclarge;
        private ToolStripMenuItem meniEInscont;
        private ToolStripMenuItem meniEInsalign;
        private ToolStripMenuItem meniEInsevenodd;
        private ToolStripMenuItem meniEInsiso;
        private ToolStripMenuItem menuEInsstartshape;
        private ToolStripMenuItem menuRRender;
        private ToolStripMenuItem menuRRenderSize;
        private ToolStripMenuItem menuRAgain;
        private ToolStripMenuItem menuRAnimate;
        private ToolStripMenuItem menuRFrame;
        private ToolStripMenuItem menuRStop;
        private ToolStripSeparator toolStripMenuItem6;
        private ToolStripMenuItem menuROutput;
        private ToolStripMenuItem menuRGallery;
        public ScintillaNET.Scintilla cfdgText;
        private ToolStripMenuItem colorCalculatorToolStripMenuItem;
        private ImageList imageList1;
        private System.Windows.Forms.Timer statusTimer;
    }
}