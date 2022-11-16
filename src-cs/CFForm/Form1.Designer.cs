namespace CFForm
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.recentToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.preferencesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.examplesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.windowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.colorCalculatorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.contextFreeSiteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.galleryToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.forumsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.writingCFDGFilesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.sendFeedbackToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutContextFreeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.examplesToolStripMenuItem,
            this.windowToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1594, 42);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.recentToolStripMenuItem,
            this.toolStripSeparator1,
            this.preferencesToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(71, 38);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.newToolStripMenuItem.Size = new System.Drawing.Size(359, 44);
            this.newToolStripMenuItem.Text = "&New";
            this.newToolStripMenuItem.Click += new System.EventHandler(this.openNewClick);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.openToolStripMenuItem.Size = new System.Drawing.Size(359, 44);
            this.openToolStripMenuItem.Text = "&Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.menuFOpenClick);
            // 
            // recentToolStripMenuItem
            // 
            this.recentToolStripMenuItem.Name = "recentToolStripMenuItem";
            this.recentToolStripMenuItem.Size = new System.Drawing.Size(359, 44);
            this.recentToolStripMenuItem.Text = "Recent";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(356, 6);
            // 
            // preferencesToolStripMenuItem
            // 
            this.preferencesToolStripMenuItem.Name = "preferencesToolStripMenuItem";
            this.preferencesToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.P)));
            this.preferencesToolStripMenuItem.Size = new System.Drawing.Size(359, 44);
            this.preferencesToolStripMenuItem.Text = "&Preferences";
            this.preferencesToolStripMenuItem.Click += new System.EventHandler(this.preferencesToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(359, 44);
            this.exitToolStripMenuItem.Text = "E&xit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // examplesToolStripMenuItem
            // 
            this.examplesToolStripMenuItem.Name = "examplesToolStripMenuItem";
            this.examplesToolStripMenuItem.Size = new System.Drawing.Size(133, 38);
            this.examplesToolStripMenuItem.Text = "E&xamples";
            // 
            // windowToolStripMenuItem
            // 
            this.windowToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.colorCalculatorToolStripMenuItem});
            this.windowToolStripMenuItem.Name = "windowToolStripMenuItem";
            this.windowToolStripMenuItem.Size = new System.Drawing.Size(121, 38);
            this.windowToolStripMenuItem.Text = "&Window";
            // 
            // colorCalculatorToolStripMenuItem
            // 
            this.colorCalculatorToolStripMenuItem.Name = "colorCalculatorToolStripMenuItem";
            this.colorCalculatorToolStripMenuItem.Size = new System.Drawing.Size(317, 44);
            this.colorCalculatorToolStripMenuItem.Text = "&Color Calculator";
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.contextFreeSiteToolStripMenuItem,
            this.galleryToolStripMenuItem,
            this.forumsToolStripMenuItem,
            this.writingCFDGFilesToolStripMenuItem,
            this.toolStripSeparator2,
            this.sendFeedbackToolStripMenuItem,
            this.aboutContextFreeToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(84, 38);
            this.helpToolStripMenuItem.Text = "&Help";
            // 
            // contextFreeSiteToolStripMenuItem
            // 
            this.contextFreeSiteToolStripMenuItem.Name = "contextFreeSiteToolStripMenuItem";
            this.contextFreeSiteToolStripMenuItem.Size = new System.Drawing.Size(357, 44);
            this.contextFreeSiteToolStripMenuItem.Tag = "https://www.contextfreeart.org/index.html";
            this.contextFreeSiteToolStripMenuItem.Text = "&Context Free Site...";
            this.contextFreeSiteToolStripMenuItem.Click += new System.EventHandler(this.urlToolStripMenuItem_Click);
            // 
            // galleryToolStripMenuItem
            // 
            this.galleryToolStripMenuItem.Name = "galleryToolStripMenuItem";
            this.galleryToolStripMenuItem.Size = new System.Drawing.Size(357, 44);
            this.galleryToolStripMenuItem.Tag = "https://www.contextfreeart.org/gallery/";
            this.galleryToolStripMenuItem.Text = "&Gallery...";
            this.galleryToolStripMenuItem.Click += new System.EventHandler(this.urlToolStripMenuItem_Click);
            // 
            // forumsToolStripMenuItem
            // 
            this.forumsToolStripMenuItem.Name = "forumsToolStripMenuItem";
            this.forumsToolStripMenuItem.Size = new System.Drawing.Size(357, 44);
            this.forumsToolStripMenuItem.Tag = "https://www.contextfreeart.org/phpbb/index.php";
            this.forumsToolStripMenuItem.Text = "&Forums...";
            this.forumsToolStripMenuItem.Click += new System.EventHandler(this.urlToolStripMenuItem_Click);
            // 
            // writingCFDGFilesToolStripMenuItem
            // 
            this.writingCFDGFilesToolStripMenuItem.Name = "writingCFDGFilesToolStripMenuItem";
            this.writingCFDGFilesToolStripMenuItem.Size = new System.Drawing.Size(357, 44);
            this.writingCFDGFilesToolStripMenuItem.Tag = "https://github.com/MtnViewJohn/context-free/wiki";
            this.writingCFDGFilesToolStripMenuItem.Text = "&Writing CFDG files...";
            this.writingCFDGFilesToolStripMenuItem.Click += new System.EventHandler(this.urlToolStripMenuItem_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(354, 6);
            // 
            // sendFeedbackToolStripMenuItem
            // 
            this.sendFeedbackToolStripMenuItem.Name = "sendFeedbackToolStripMenuItem";
            this.sendFeedbackToolStripMenuItem.Size = new System.Drawing.Size(357, 44);
            this.sendFeedbackToolStripMenuItem.Tag = "mailto:info@contextfreeart.org";
            this.sendFeedbackToolStripMenuItem.Text = "&Send feedback...";
            this.sendFeedbackToolStripMenuItem.Click += new System.EventHandler(this.urlToolStripMenuItem_Click);
            // 
            // aboutContextFreeToolStripMenuItem
            // 
            this.aboutContextFreeToolStripMenuItem.Name = "aboutContextFreeToolStripMenuItem";
            this.aboutContextFreeToolStripMenuItem.Size = new System.Drawing.Size(357, 44);
            this.aboutContextFreeToolStripMenuItem.Text = "&About Context Free";
            this.aboutContextFreeToolStripMenuItem.Click += new System.EventHandler(this.aboutContextFreeToolStripMenuItem_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "openFileDialog1";
            this.openFileDialog.Filter = "CFDG Files|*.cfdg";
            this.openFileDialog.Title = "Select a CFDG File";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(13F, 32F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1594, 1202);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Context Free";
            this.ResizeBegin += new System.EventHandler(this.resizeBegin);
            this.ResizeEnd += new System.EventHandler(this.resizeEnd);
            this.Resize += new System.EventHandler(this.resized);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private MenuStrip menuStrip1;
        private ToolStripMenuItem fileToolStripMenuItem;
        private ToolStripMenuItem newToolStripMenuItem;
        private ToolStripMenuItem openToolStripMenuItem;
        private ToolStripMenuItem recentToolStripMenuItem;
        private ToolStripSeparator toolStripSeparator1;
        private ToolStripMenuItem preferencesToolStripMenuItem;
        private ToolStripMenuItem exitToolStripMenuItem;
        private ToolStripMenuItem examplesToolStripMenuItem;
        private ToolStripMenuItem windowToolStripMenuItem;
        private ToolStripMenuItem colorCalculatorToolStripMenuItem;
        private ToolStripMenuItem helpToolStripMenuItem;
        private ToolStripMenuItem contextFreeSiteToolStripMenuItem;
        private ToolStripMenuItem galleryToolStripMenuItem;
        private ToolStripMenuItem forumsToolStripMenuItem;
        private ToolStripMenuItem writingCFDGFilesToolStripMenuItem;
        private ToolStripSeparator toolStripSeparator2;
        private ToolStripMenuItem sendFeedbackToolStripMenuItem;
        private ToolStripMenuItem aboutContextFreeToolStripMenuItem;
        private OpenFileDialog openFileDialog;
    }
}