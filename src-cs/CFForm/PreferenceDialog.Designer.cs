namespace CFForm
{
    partial class PreferenceDialog
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
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PreferenceDialog));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.radioOpenNothing = new System.Windows.Forms.RadioButton();
            this.radioOpenNew = new System.Windows.Forms.RadioButton();
            this.radioOpenWelcome = new System.Windows.Forms.RadioButton();
            this.checkOpenRender = new System.Windows.Forms.CheckBox();
            this.checkRenderUpdate = new System.Windows.Forms.CheckBox();
            this.checkSaveWithVariation = new System.Windows.Forms.CheckBox();
            this.checkCropImage = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.trackBarBorder = new System.Windows.Forms.TrackBar();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.editJPEGquality = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.numberColor = new System.Windows.Forms.TextBox();
            this.numberItalic = new System.Windows.Forms.CheckBox();
            this.numberBold = new System.Windows.Forms.CheckBox();
            this.numberStyle = new System.Windows.Forms.Label();
            this.filenameColor = new System.Windows.Forms.TextBox();
            this.filenameItalic = new System.Windows.Forms.CheckBox();
            this.filenameBold = new System.Windows.Forms.CheckBox();
            this.filenameStyle = new System.Windows.Forms.Label();
            this.builtinColor = new System.Windows.Forms.TextBox();
            this.builtinItalic = new System.Windows.Forms.CheckBox();
            this.builtinBold = new System.Windows.Forms.CheckBox();
            this.builtinStyle = new System.Windows.Forms.Label();
            this.keywordColor = new System.Windows.Forms.TextBox();
            this.keywordItalic = new System.Windows.Forms.CheckBox();
            this.keywordBold = new System.Windows.Forms.CheckBox();
            this.keywordStyle = new System.Windows.Forms.Label();
            this.identifierColor = new System.Windows.Forms.TextBox();
            this.identifierItalic = new System.Windows.Forms.CheckBox();
            this.identifierBold = new System.Windows.Forms.CheckBox();
            this.identifierStyle = new System.Windows.Forms.Label();
            this.symbolColor = new System.Windows.Forms.TextBox();
            this.symbolItalic = new System.Windows.Forms.CheckBox();
            this.symbolBold = new System.Windows.Forms.CheckBox();
            this.symbolStyle = new System.Windows.Forms.Label();
            this.commentColor = new System.Windows.Forms.TextBox();
            this.commentItalic = new System.Windows.Forms.CheckBox();
            this.commentBold = new System.Windows.Forms.CheckBox();
            this.commentStyle = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.defaultColor = new System.Windows.Forms.TextBox();
            this.defaultItalic = new System.Windows.Forms.CheckBox();
            this.defaultBold = new System.Windows.Forms.CheckBox();
            this.defaultStyle = new System.Windows.Forms.Label();
            this.numericTabWidth = new System.Windows.Forms.NumericUpDown();
            this.label11 = new System.Windows.Forms.Label();
            this.fontChange = new System.Windows.Forms.Button();
            this.fontDisplay = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.buttonOK = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarBorder)).BeginInit();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericTabWidth)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.radioOpenNothing);
            this.groupBox1.Controls.Add(this.radioOpenNew);
            this.groupBox1.Controls.Add(this.radioOpenWelcome);
            this.groupBox1.Location = new System.Drawing.Point(6, 6);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(400, 200);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "When Context Free opens:";
            // 
            // radioOpenNothing
            // 
            this.radioOpenNothing.AutoSize = true;
            this.radioOpenNothing.Location = new System.Drawing.Point(21, 152);
            this.radioOpenNothing.Name = "radioOpenNothing";
            this.radioOpenNothing.Size = new System.Drawing.Size(167, 36);
            this.radioOpenNothing.TabIndex = 2;
            this.radioOpenNothing.TabStop = true;
            this.radioOpenNothing.Text = "Do nothing";
            this.radioOpenNothing.UseVisualStyleBackColor = true;
            // 
            // radioOpenNew
            // 
            this.radioOpenNew.AutoSize = true;
            this.radioOpenNew.Location = new System.Drawing.Point(21, 104);
            this.radioOpenNew.Name = "radioOpenNew";
            this.radioOpenNew.Size = new System.Drawing.Size(271, 36);
            this.radioOpenNew.TabIndex = 1;
            this.radioOpenNew.TabStop = true;
            this.radioOpenNew.Text = "Open new document";
            this.radioOpenNew.UseVisualStyleBackColor = true;
            // 
            // radioOpenWelcome
            // 
            this.radioOpenWelcome.AutoSize = true;
            this.radioOpenWelcome.Location = new System.Drawing.Point(21, 56);
            this.radioOpenWelcome.Name = "radioOpenWelcome";
            this.radioOpenWelcome.Size = new System.Drawing.Size(326, 36);
            this.radioOpenWelcome.TabIndex = 0;
            this.radioOpenWelcome.TabStop = true;
            this.radioOpenWelcome.Text = "Open Welcome document";
            this.radioOpenWelcome.UseVisualStyleBackColor = true;
            // 
            // checkOpenRender
            // 
            this.checkOpenRender.AutoSize = true;
            this.checkOpenRender.Location = new System.Drawing.Point(341, 222);
            this.checkOpenRender.Name = "checkOpenRender";
            this.checkOpenRender.Size = new System.Drawing.Size(205, 36);
            this.checkOpenRender.TabIndex = 1;
            this.checkOpenRender.Text = "Start rendering";
            this.checkOpenRender.UseVisualStyleBackColor = true;
            // 
            // checkRenderUpdate
            // 
            this.checkRenderUpdate.AutoSize = true;
            this.checkRenderUpdate.Location = new System.Drawing.Point(341, 264);
            this.checkRenderUpdate.Name = "checkRenderUpdate";
            this.checkRenderUpdate.Size = new System.Drawing.Size(382, 36);
            this.checkRenderUpdate.TabIndex = 2;
            this.checkRenderUpdate.Text = "Progressively update the image";
            this.checkRenderUpdate.UseVisualStyleBackColor = true;
            // 
            // checkSaveWithVariation
            // 
            this.checkSaveWithVariation.AutoSize = true;
            this.checkSaveWithVariation.Location = new System.Drawing.Point(341, 306);
            this.checkSaveWithVariation.Name = "checkSaveWithVariation";
            this.checkSaveWithVariation.Size = new System.Drawing.Size(500, 36);
            this.checkSaveWithVariation.TabIndex = 3;
            this.checkSaveWithVariation.Text = "Include the variation code in the file name";
            this.checkSaveWithVariation.UseVisualStyleBackColor = true;
            // 
            // checkCropImage
            // 
            this.checkCropImage.AutoSize = true;
            this.checkCropImage.Location = new System.Drawing.Point(341, 348);
            this.checkCropImage.Name = "checkCropImage";
            this.checkCropImage.Size = new System.Drawing.Size(212, 36);
            this.checkCropImage.TabIndex = 4;
            this.checkCropImage.Text = "Crop the image";
            this.checkCropImage.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 222);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(329, 32);
            this.label1.TabIndex = 5;
            this.label1.Text = "When a document is opened:";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(144, 264);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(191, 32);
            this.label2.TabIndex = 6;
            this.label2.Text = "While rendering:";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(72, 306);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(263, 32);
            this.label3.TabIndex = 7;
            this.label3.Text = "When saving an image:";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(125, 444);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(210, 32);
            this.label4.TabIndex = 8;
            this.label4.Text = "Image border size:";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // trackBarBorder
            // 
            this.trackBarBorder.BackColor = System.Drawing.SystemColors.Control;
            this.trackBarBorder.Location = new System.Drawing.Point(341, 444);
            this.trackBarBorder.Maximum = 99;
            this.trackBarBorder.Name = "trackBarBorder";
            this.trackBarBorder.Size = new System.Drawing.Size(500, 90);
            this.trackBarBorder.TabIndex = 14;
            this.trackBarBorder.TickFrequency = 33;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Segoe UI", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label5.Location = new System.Drawing.Point(322, 500);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(84, 25);
            this.label5.TabIndex = 10;
            this.label5.Text = "negative";
            this.label5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Segoe UI", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label6.Location = new System.Drawing.Point(487, 500);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(55, 25);
            this.label6.TabIndex = 11;
            this.label6.Text = "none";
            this.label6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Segoe UI", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label7.Location = new System.Drawing.Point(640, 500);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 25);
            this.label7.TabIndex = 12;
            this.label7.Text = "fixed";
            this.label7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Segoe UI", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label8.Location = new System.Drawing.Point(775, 500);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(79, 25);
            this.label8.TabIndex = 13;
            this.label8.Text = "variable";
            this.label8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // editJPEGquality
            // 
            this.editJPEGquality.Location = new System.Drawing.Point(341, 390);
            this.editJPEGquality.Name = "editJPEGquality";
            this.editJPEGquality.Size = new System.Drawing.Size(100, 39);
            this.editJPEGquality.TabIndex = 9;
            this.editJPEGquality.Text = "90";
            this.editJPEGquality.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.numberKeyPress);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(447, 392);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(143, 32);
            this.label9.TabIndex = 15;
            this.label9.Text = "JPEG quality";
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Location = new System.Drawing.Point(12, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(884, 624);
            this.tabControl1.TabIndex = 16;
            // 
            // tabPage1
            // 
            this.tabPage1.BackColor = System.Drawing.Color.Transparent;
            this.tabPage1.Controls.Add(this.groupBox1);
            this.tabPage1.Controls.Add(this.label9);
            this.tabPage1.Controls.Add(this.label1);
            this.tabPage1.Controls.Add(this.editJPEGquality);
            this.tabPage1.Controls.Add(this.checkOpenRender);
            this.tabPage1.Controls.Add(this.label8);
            this.tabPage1.Controls.Add(this.checkRenderUpdate);
            this.tabPage1.Controls.Add(this.label7);
            this.tabPage1.Controls.Add(this.checkSaveWithVariation);
            this.tabPage1.Controls.Add(this.label6);
            this.tabPage1.Controls.Add(this.checkCropImage);
            this.tabPage1.Controls.Add(this.label5);
            this.tabPage1.Controls.Add(this.label2);
            this.tabPage1.Controls.Add(this.trackBarBorder);
            this.tabPage1.Controls.Add(this.label3);
            this.tabPage1.Controls.Add(this.label4);
            this.tabPage1.Location = new System.Drawing.Point(8, 46);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(868, 570);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "General";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.numberColor);
            this.tabPage2.Controls.Add(this.numberItalic);
            this.tabPage2.Controls.Add(this.numberBold);
            this.tabPage2.Controls.Add(this.numberStyle);
            this.tabPage2.Controls.Add(this.filenameColor);
            this.tabPage2.Controls.Add(this.filenameItalic);
            this.tabPage2.Controls.Add(this.filenameBold);
            this.tabPage2.Controls.Add(this.filenameStyle);
            this.tabPage2.Controls.Add(this.builtinColor);
            this.tabPage2.Controls.Add(this.builtinItalic);
            this.tabPage2.Controls.Add(this.builtinBold);
            this.tabPage2.Controls.Add(this.builtinStyle);
            this.tabPage2.Controls.Add(this.keywordColor);
            this.tabPage2.Controls.Add(this.keywordItalic);
            this.tabPage2.Controls.Add(this.keywordBold);
            this.tabPage2.Controls.Add(this.keywordStyle);
            this.tabPage2.Controls.Add(this.identifierColor);
            this.tabPage2.Controls.Add(this.identifierItalic);
            this.tabPage2.Controls.Add(this.identifierBold);
            this.tabPage2.Controls.Add(this.identifierStyle);
            this.tabPage2.Controls.Add(this.symbolColor);
            this.tabPage2.Controls.Add(this.symbolItalic);
            this.tabPage2.Controls.Add(this.symbolBold);
            this.tabPage2.Controls.Add(this.symbolStyle);
            this.tabPage2.Controls.Add(this.commentColor);
            this.tabPage2.Controls.Add(this.commentItalic);
            this.tabPage2.Controls.Add(this.commentBold);
            this.tabPage2.Controls.Add(this.commentStyle);
            this.tabPage2.Controls.Add(this.label16);
            this.tabPage2.Controls.Add(this.label15);
            this.tabPage2.Controls.Add(this.label14);
            this.tabPage2.Controls.Add(this.label13);
            this.tabPage2.Controls.Add(this.defaultColor);
            this.tabPage2.Controls.Add(this.defaultItalic);
            this.tabPage2.Controls.Add(this.defaultBold);
            this.tabPage2.Controls.Add(this.defaultStyle);
            this.tabPage2.Controls.Add(this.numericTabWidth);
            this.tabPage2.Controls.Add(this.label11);
            this.tabPage2.Controls.Add(this.fontChange);
            this.tabPage2.Controls.Add(this.fontDisplay);
            this.tabPage2.Controls.Add(this.label10);
            this.tabPage2.Location = new System.Drawing.Point(8, 46);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(868, 570);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Editor";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // numberColor
            // 
            this.numberColor.Location = new System.Drawing.Point(283, 504);
            this.numberColor.Name = "numberColor";
            this.numberColor.Size = new System.Drawing.Size(200, 39);
            this.numberColor.TabIndex = 40;
            this.numberColor.Tag = "128";
            this.numberColor.Text = "#000";
            this.numberColor.TextChanged += new System.EventHandler(this.colorChanged);
            // 
            // numberItalic
            // 
            this.numberItalic.AutoSize = true;
            this.numberItalic.Location = new System.Drawing.Point(231, 509);
            this.numberItalic.Name = "numberItalic";
            this.numberItalic.Size = new System.Drawing.Size(28, 27);
            this.numberItalic.TabIndex = 39;
            this.numberItalic.UseVisualStyleBackColor = true;
            this.numberItalic.CheckedChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // numberBold
            // 
            this.numberBold.AutoSize = true;
            this.numberBold.Location = new System.Drawing.Point(174, 509);
            this.numberBold.Name = "numberBold";
            this.numberBold.Size = new System.Drawing.Size(28, 27);
            this.numberBold.TabIndex = 38;
            this.numberBold.UseVisualStyleBackColor = true;
            this.numberBold.CheckedChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // numberStyle
            // 
            this.numberStyle.AutoSize = true;
            this.numberStyle.Location = new System.Drawing.Point(42, 507);
            this.numberStyle.Name = "numberStyle";
            this.numberStyle.Size = new System.Drawing.Size(117, 32);
            this.numberStyle.TabIndex = 37;
            this.numberStyle.Text = "Numbers:";
            this.numberStyle.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // filenameColor
            // 
            this.filenameColor.Location = new System.Drawing.Point(283, 459);
            this.filenameColor.Name = "filenameColor";
            this.filenameColor.Size = new System.Drawing.Size(200, 39);
            this.filenameColor.TabIndex = 36;
            this.filenameColor.Tag = "64";
            this.filenameColor.Text = "#000";
            this.filenameColor.TextChanged += new System.EventHandler(this.colorChanged);
            // 
            // filenameItalic
            // 
            this.filenameItalic.AutoSize = true;
            this.filenameItalic.Location = new System.Drawing.Point(231, 464);
            this.filenameItalic.Name = "filenameItalic";
            this.filenameItalic.Size = new System.Drawing.Size(28, 27);
            this.filenameItalic.TabIndex = 35;
            this.filenameItalic.UseVisualStyleBackColor = true;
            this.filenameItalic.CheckedChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // filenameBold
            // 
            this.filenameBold.AutoSize = true;
            this.filenameBold.Location = new System.Drawing.Point(174, 464);
            this.filenameBold.Name = "filenameBold";
            this.filenameBold.Size = new System.Drawing.Size(28, 27);
            this.filenameBold.TabIndex = 34;
            this.filenameBold.UseVisualStyleBackColor = true;
            this.filenameBold.CheckedChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // filenameStyle
            // 
            this.filenameStyle.AutoSize = true;
            this.filenameStyle.Location = new System.Drawing.Point(33, 462);
            this.filenameStyle.Name = "filenameStyle";
            this.filenameStyle.Size = new System.Drawing.Size(126, 32);
            this.filenameStyle.TabIndex = 33;
            this.filenameStyle.Text = "Filenames:";
            this.filenameStyle.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // builtinColor
            // 
            this.builtinColor.Location = new System.Drawing.Point(283, 414);
            this.builtinColor.Name = "builtinColor";
            this.builtinColor.Size = new System.Drawing.Size(200, 39);
            this.builtinColor.TabIndex = 32;
            this.builtinColor.Tag = "32";
            this.builtinColor.Text = "#000";
            this.builtinColor.TextChanged += new System.EventHandler(this.colorChanged);
            // 
            // builtinItalic
            // 
            this.builtinItalic.AutoSize = true;
            this.builtinItalic.Location = new System.Drawing.Point(231, 419);
            this.builtinItalic.Name = "builtinItalic";
            this.builtinItalic.Size = new System.Drawing.Size(28, 27);
            this.builtinItalic.TabIndex = 31;
            this.builtinItalic.UseVisualStyleBackColor = true;
            this.builtinItalic.CheckedChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // builtinBold
            // 
            this.builtinBold.AutoSize = true;
            this.builtinBold.Location = new System.Drawing.Point(174, 419);
            this.builtinBold.Name = "builtinBold";
            this.builtinBold.Size = new System.Drawing.Size(28, 27);
            this.builtinBold.TabIndex = 30;
            this.builtinBold.UseVisualStyleBackColor = true;
            this.builtinBold.CheckedChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // builtinStyle
            // 
            this.builtinStyle.AutoSize = true;
            this.builtinStyle.Location = new System.Drawing.Point(52, 417);
            this.builtinStyle.Name = "builtinStyle";
            this.builtinStyle.Size = new System.Drawing.Size(107, 32);
            this.builtinStyle.TabIndex = 29;
            this.builtinStyle.Text = "Built-ins:";
            this.builtinStyle.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // keywordColor
            // 
            this.keywordColor.Location = new System.Drawing.Point(283, 369);
            this.keywordColor.Name = "keywordColor";
            this.keywordColor.Size = new System.Drawing.Size(200, 39);
            this.keywordColor.TabIndex = 28;
            this.keywordColor.Tag = "16";
            this.keywordColor.Text = "#000";
            this.keywordColor.TextChanged += new System.EventHandler(this.colorChanged);
            // 
            // keywordItalic
            // 
            this.keywordItalic.AutoSize = true;
            this.keywordItalic.Location = new System.Drawing.Point(231, 374);
            this.keywordItalic.Name = "keywordItalic";
            this.keywordItalic.Size = new System.Drawing.Size(28, 27);
            this.keywordItalic.TabIndex = 27;
            this.keywordItalic.UseVisualStyleBackColor = true;
            this.keywordItalic.CheckedChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // keywordBold
            // 
            this.keywordBold.AutoSize = true;
            this.keywordBold.Location = new System.Drawing.Point(174, 374);
            this.keywordBold.Name = "keywordBold";
            this.keywordBold.Size = new System.Drawing.Size(28, 27);
            this.keywordBold.TabIndex = 26;
            this.keywordBold.UseVisualStyleBackColor = true;
            this.keywordBold.CheckedChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // keywordStyle
            // 
            this.keywordStyle.AutoSize = true;
            this.keywordStyle.Location = new System.Drawing.Point(38, 372);
            this.keywordStyle.Name = "keywordStyle";
            this.keywordStyle.Size = new System.Drawing.Size(121, 32);
            this.keywordStyle.TabIndex = 25;
            this.keywordStyle.Text = "Keywords:";
            this.keywordStyle.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // identifierColor
            // 
            this.identifierColor.Location = new System.Drawing.Point(283, 324);
            this.identifierColor.Name = "identifierColor";
            this.identifierColor.Size = new System.Drawing.Size(200, 39);
            this.identifierColor.TabIndex = 24;
            this.identifierColor.Tag = "8";
            this.identifierColor.Text = "#000";
            this.identifierColor.TextChanged += new System.EventHandler(this.colorChanged);
            // 
            // identifierItalic
            // 
            this.identifierItalic.AutoSize = true;
            this.identifierItalic.Location = new System.Drawing.Point(231, 329);
            this.identifierItalic.Name = "identifierItalic";
            this.identifierItalic.Size = new System.Drawing.Size(28, 27);
            this.identifierItalic.TabIndex = 23;
            this.identifierItalic.UseVisualStyleBackColor = true;
            this.identifierItalic.CheckedChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // identifierBold
            // 
            this.identifierBold.AutoSize = true;
            this.identifierBold.Location = new System.Drawing.Point(174, 329);
            this.identifierBold.Name = "identifierBold";
            this.identifierBold.Size = new System.Drawing.Size(28, 27);
            this.identifierBold.TabIndex = 22;
            this.identifierBold.UseVisualStyleBackColor = true;
            this.identifierBold.CheckedChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // identifierStyle
            // 
            this.identifierStyle.AutoSize = true;
            this.identifierStyle.Location = new System.Drawing.Point(34, 327);
            this.identifierStyle.Name = "identifierStyle";
            this.identifierStyle.Size = new System.Drawing.Size(125, 32);
            this.identifierStyle.TabIndex = 21;
            this.identifierStyle.Text = "Identifiers:";
            this.identifierStyle.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // symbolColor
            // 
            this.symbolColor.Location = new System.Drawing.Point(283, 279);
            this.symbolColor.Name = "symbolColor";
            this.symbolColor.Size = new System.Drawing.Size(200, 39);
            this.symbolColor.TabIndex = 20;
            this.symbolColor.Tag = "4";
            this.symbolColor.Text = "#000";
            this.symbolColor.TextChanged += new System.EventHandler(this.colorChanged);
            // 
            // symbolItalic
            // 
            this.symbolItalic.AutoSize = true;
            this.symbolItalic.Location = new System.Drawing.Point(231, 284);
            this.symbolItalic.Name = "symbolItalic";
            this.symbolItalic.Size = new System.Drawing.Size(28, 27);
            this.symbolItalic.TabIndex = 19;
            this.symbolItalic.UseVisualStyleBackColor = true;
            this.symbolItalic.CheckedChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // symbolBold
            // 
            this.symbolBold.AutoSize = true;
            this.symbolBold.Location = new System.Drawing.Point(174, 284);
            this.symbolBold.Name = "symbolBold";
            this.symbolBold.Size = new System.Drawing.Size(28, 27);
            this.symbolBold.TabIndex = 18;
            this.symbolBold.UseVisualStyleBackColor = true;
            this.symbolBold.CheckedChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // symbolStyle
            // 
            this.symbolStyle.AutoSize = true;
            this.symbolStyle.Location = new System.Drawing.Point(51, 282);
            this.symbolStyle.Name = "symbolStyle";
            this.symbolStyle.Size = new System.Drawing.Size(108, 32);
            this.symbolStyle.TabIndex = 17;
            this.symbolStyle.Text = "Symbols:";
            this.symbolStyle.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // commentColor
            // 
            this.commentColor.Location = new System.Drawing.Point(283, 234);
            this.commentColor.Name = "commentColor";
            this.commentColor.Size = new System.Drawing.Size(200, 39);
            this.commentColor.TabIndex = 16;
            this.commentColor.Tag = "2";
            this.commentColor.Text = "#000";
            this.commentColor.TextChanged += new System.EventHandler(this.colorChanged);
            // 
            // commentItalic
            // 
            this.commentItalic.AutoSize = true;
            this.commentItalic.Location = new System.Drawing.Point(231, 239);
            this.commentItalic.Name = "commentItalic";
            this.commentItalic.Size = new System.Drawing.Size(28, 27);
            this.commentItalic.TabIndex = 15;
            this.commentItalic.UseVisualStyleBackColor = true;
            this.commentItalic.CheckedChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // commentBold
            // 
            this.commentBold.AutoSize = true;
            this.commentBold.Location = new System.Drawing.Point(174, 239);
            this.commentBold.Name = "commentBold";
            this.commentBold.Size = new System.Drawing.Size(28, 27);
            this.commentBold.TabIndex = 14;
            this.commentBold.UseVisualStyleBackColor = true;
            this.commentBold.CheckedChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // commentStyle
            // 
            this.commentStyle.AutoSize = true;
            this.commentStyle.Location = new System.Drawing.Point(29, 237);
            this.commentStyle.Name = "commentStyle";
            this.commentStyle.Size = new System.Drawing.Size(130, 32);
            this.commentStyle.TabIndex = 13;
            this.commentStyle.Text = "Comments";
            this.commentStyle.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Font = new System.Drawing.Font("Segoe UI", 7F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label16.Location = new System.Drawing.Point(165, 146);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(53, 25);
            this.label16.TabIndex = 12;
            this.label16.Text = "Bold";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("Segoe UI", 7F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label15.Location = new System.Drawing.Point(221, 146);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(54, 25);
            this.label15.TabIndex = 11;
            this.label15.Text = "Italic";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("Segoe UI", 7F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label14.Location = new System.Drawing.Point(279, 146);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(61, 25);
            this.label14.TabIndex = 10;
            this.label14.Text = "Color";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("Segoe UI", 7F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label13.Location = new System.Drawing.Point(79, 146);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(63, 25);
            this.label13.TabIndex = 9;
            this.label13.Text = "Styles";
            // 
            // defaultColor
            // 
            this.defaultColor.Location = new System.Drawing.Point(283, 189);
            this.defaultColor.Name = "defaultColor";
            this.defaultColor.Size = new System.Drawing.Size(200, 39);
            this.defaultColor.TabIndex = 8;
            this.defaultColor.Tag = "1";
            this.defaultColor.Text = "#000";
            this.defaultColor.TextChanged += new System.EventHandler(this.colorChanged);
            // 
            // defaultItalic
            // 
            this.defaultItalic.AutoSize = true;
            this.defaultItalic.Location = new System.Drawing.Point(231, 194);
            this.defaultItalic.Name = "defaultItalic";
            this.defaultItalic.Size = new System.Drawing.Size(28, 27);
            this.defaultItalic.TabIndex = 7;
            this.defaultItalic.UseVisualStyleBackColor = true;
            this.defaultItalic.CheckedChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // defaultBold
            // 
            this.defaultBold.AutoSize = true;
            this.defaultBold.Location = new System.Drawing.Point(174, 194);
            this.defaultBold.Name = "defaultBold";
            this.defaultBold.Size = new System.Drawing.Size(28, 27);
            this.defaultBold.TabIndex = 6;
            this.defaultBold.UseVisualStyleBackColor = true;
            this.defaultBold.CheckedChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // defaultStyle
            // 
            this.defaultStyle.AutoSize = true;
            this.defaultStyle.BackColor = System.Drawing.Color.Transparent;
            this.defaultStyle.Location = new System.Drawing.Point(62, 192);
            this.defaultStyle.Name = "defaultStyle";
            this.defaultStyle.Size = new System.Drawing.Size(97, 32);
            this.defaultStyle.TabIndex = 5;
            this.defaultStyle.Text = "Default:";
            this.defaultStyle.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // numericTabWidth
            // 
            this.numericTabWidth.Location = new System.Drawing.Point(210, 69);
            this.numericTabWidth.Maximum = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.numericTabWidth.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericTabWidth.Name = "numericTabWidth";
            this.numericTabWidth.Size = new System.Drawing.Size(92, 39);
            this.numericTabWidth.TabIndex = 4;
            this.numericTabWidth.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.numericTabWidth.ValueChanged += new System.EventHandler(this.editorStyleChanged);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(6, 71);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(188, 32);
            this.label11.TabIndex = 3;
            this.label11.Text = "Editor tab width:";
            this.label11.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // fontChange
            // 
            this.fontChange.Location = new System.Drawing.Point(534, 17);
            this.fontChange.Name = "fontChange";
            this.fontChange.Size = new System.Drawing.Size(150, 46);
            this.fontChange.TabIndex = 2;
            this.fontChange.Text = "Change";
            this.fontChange.UseVisualStyleBackColor = true;
            this.fontChange.Click += new System.EventHandler(this.fontChange_Click);
            // 
            // fontDisplay
            // 
            this.fontDisplay.Location = new System.Drawing.Point(210, 20);
            this.fontDisplay.Name = "fontDisplay";
            this.fontDisplay.ReadOnly = true;
            this.fontDisplay.Size = new System.Drawing.Size(318, 39);
            this.fontDisplay.TabIndex = 1;
            this.fontDisplay.TabStop = false;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(62, 24);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(132, 32);
            this.label10.TabIndex = 0;
            this.label10.Text = "Editor font:";
            this.label10.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // buttonOK
            // 
            this.buttonOK.Location = new System.Drawing.Point(746, 642);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(150, 46);
            this.buttonOK.TabIndex = 51;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // buttonCancel
            // 
            this.buttonCancel.Location = new System.Drawing.Point(590, 642);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(150, 46);
            this.buttonCancel.TabIndex = 50;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // PreferenceDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(13F, 32F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(908, 700);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.tabControl1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "PreferenceDialog";
            this.Text = "Context Free Preferences";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarBorder)).EndInit();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericTabWidth)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private GroupBox groupBox1;
        private RadioButton radioOpenNothing;
        private RadioButton radioOpenNew;
        private CheckBox checkOpenRender;
        private CheckBox checkRenderUpdate;
        private CheckBox checkSaveWithVariation;
        private CheckBox checkCropImage;
        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;
        private TrackBar trackBarBorder;
        private Label label5;
        private Label label6;
        private Label label7;
        private Label label8;
        private RadioButton radioOpenWelcome;
        private TextBox editJPEGquality;
        private Label label9;
        private TabControl tabControl1;
        private TabPage tabPage1;
        private TabPage tabPage2;
        private TextBox numberColor;
        private CheckBox numberItalic;
        private CheckBox numberBold;
        private Label numberStyle;
        private TextBox filenameColor;
        private CheckBox filenameItalic;
        private CheckBox filenameBold;
        private Label filenameStyle;
        private TextBox builtinColor;
        private CheckBox builtinItalic;
        private CheckBox builtinBold;
        private Label builtinStyle;
        private TextBox keywordColor;
        private CheckBox keywordItalic;
        private CheckBox keywordBold;
        private Label keywordStyle;
        private TextBox identifierColor;
        private CheckBox identifierItalic;
        private CheckBox identifierBold;
        private Label identifierStyle;
        private TextBox symbolColor;
        private CheckBox symbolItalic;
        private CheckBox symbolBold;
        private Label symbolStyle;
        private TextBox commentColor;
        private CheckBox commentItalic;
        private CheckBox commentBold;
        private Label commentStyle;
        private Label label16;
        private Label label15;
        private Label label14;
        private Label label13;
        private TextBox defaultColor;
        private CheckBox defaultItalic;
        private CheckBox defaultBold;
        private Label defaultStyle;
        private NumericUpDown numericTabWidth;
        private Label label11;
        private Button fontChange;
        private TextBox fontDisplay;
        private Label label10;
        private Button buttonOK;
        private Button buttonCancel;
    }
}