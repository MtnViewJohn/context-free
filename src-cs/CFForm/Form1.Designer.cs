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
            this.menuFNew = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.recentToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.preferencesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.examplesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ciliasunToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.demo1ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.demo2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.funkyflowerToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.icurvesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ipixToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ipolygonsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.lessonToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.lesson2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mtreeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.octopiToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.quadcityToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.roseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.sierpinkyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.snowflakeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tangleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.triplesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.undergroundToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.weighteddemoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.welcomeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ziggyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.contextFreeSiteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.galleryToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.forumsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.writingCFDGFilesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.sendFeedbackToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutContextFreeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.examplesToolStripMenuItem,
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
            this.menuFNew,
            this.openToolStripMenuItem,
            this.recentToolStripMenuItem,
            this.toolStripSeparator1,
            this.preferencesToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(71, 38);
            this.fileToolStripMenuItem.Text = "&File";
            this.fileToolStripMenuItem.DropDownOpened += new System.EventHandler(this.menuFilePopup);
            // 
            // menuFNew
            // 
            this.menuFNew.Image = ((System.Drawing.Image)(resources.GetObject("menuFNew.Image")));
            this.menuFNew.Name = "menuFNew";
            this.menuFNew.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.menuFNew.Size = new System.Drawing.Size(359, 44);
            this.menuFNew.Text = "&New";
            this.menuFNew.Click += new System.EventHandler(this.openNewClick);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("openToolStripMenuItem.Image")));
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.openToolStripMenuItem.Size = new System.Drawing.Size(359, 44);
            this.openToolStripMenuItem.Text = "&Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.menuFOpenClick);
            // 
            // recentToolStripMenuItem
            // 
            this.recentToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("recentToolStripMenuItem.Image")));
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
            this.preferencesToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("preferencesToolStripMenuItem.Image")));
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
            this.examplesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ciliasunToolStripMenuItem,
            this.demo1ToolStripMenuItem,
            this.demo2ToolStripMenuItem,
            this.funkyflowerToolStripMenuItem,
            this.icurvesToolStripMenuItem,
            this.ipixToolStripMenuItem,
            this.ipolygonsToolStripMenuItem,
            this.lessonToolStripMenuItem,
            this.lesson2ToolStripMenuItem,
            this.mtreeToolStripMenuItem,
            this.octopiToolStripMenuItem,
            this.quadcityToolStripMenuItem,
            this.roseToolStripMenuItem,
            this.sierpinkyToolStripMenuItem,
            this.snowflakeToolStripMenuItem,
            this.tangleToolStripMenuItem,
            this.triplesToolStripMenuItem,
            this.undergroundToolStripMenuItem,
            this.weighteddemoToolStripMenuItem,
            this.welcomeToolStripMenuItem,
            this.ziggyToolStripMenuItem});
            this.examplesToolStripMenuItem.Name = "examplesToolStripMenuItem";
            this.examplesToolStripMenuItem.Size = new System.Drawing.Size(133, 38);
            this.examplesToolStripMenuItem.Text = "E&xamples";
            // 
            // ciliasunToolStripMenuItem
            // 
            this.ciliasunToolStripMenuItem.Name = "ciliasunToolStripMenuItem";
            this.ciliasunToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.ciliasunToolStripMenuItem.Text = "ciliasun";
            this.ciliasunToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // demo1ToolStripMenuItem
            // 
            this.demo1ToolStripMenuItem.Name = "demo1ToolStripMenuItem";
            this.demo1ToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.demo1ToolStripMenuItem.Text = "demo1";
            this.demo1ToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // demo2ToolStripMenuItem
            // 
            this.demo2ToolStripMenuItem.Name = "demo2ToolStripMenuItem";
            this.demo2ToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.demo2ToolStripMenuItem.Text = "demo2";
            this.demo2ToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // funkyflowerToolStripMenuItem
            // 
            this.funkyflowerToolStripMenuItem.Name = "funkyflowerToolStripMenuItem";
            this.funkyflowerToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.funkyflowerToolStripMenuItem.Text = "funky_flower";
            this.funkyflowerToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // icurvesToolStripMenuItem
            // 
            this.icurvesToolStripMenuItem.Name = "icurvesToolStripMenuItem";
            this.icurvesToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.icurvesToolStripMenuItem.Text = "i_curves";
            this.icurvesToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // ipixToolStripMenuItem
            // 
            this.ipixToolStripMenuItem.Name = "ipixToolStripMenuItem";
            this.ipixToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.ipixToolStripMenuItem.Text = "i_pix";
            this.ipixToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // ipolygonsToolStripMenuItem
            // 
            this.ipolygonsToolStripMenuItem.Name = "ipolygonsToolStripMenuItem";
            this.ipolygonsToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.ipolygonsToolStripMenuItem.Text = "i_polygons";
            this.ipolygonsToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // lessonToolStripMenuItem
            // 
            this.lessonToolStripMenuItem.Name = "lessonToolStripMenuItem";
            this.lessonToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.lessonToolStripMenuItem.Text = "lesson";
            this.lessonToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // lesson2ToolStripMenuItem
            // 
            this.lesson2ToolStripMenuItem.Name = "lesson2ToolStripMenuItem";
            this.lesson2ToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.lesson2ToolStripMenuItem.Text = "lesson2";
            this.lesson2ToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // mtreeToolStripMenuItem
            // 
            this.mtreeToolStripMenuItem.Name = "mtreeToolStripMenuItem";
            this.mtreeToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.mtreeToolStripMenuItem.Text = "mtree";
            this.mtreeToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // octopiToolStripMenuItem
            // 
            this.octopiToolStripMenuItem.Name = "octopiToolStripMenuItem";
            this.octopiToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.octopiToolStripMenuItem.Text = "octopi";
            this.octopiToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // quadcityToolStripMenuItem
            // 
            this.quadcityToolStripMenuItem.Name = "quadcityToolStripMenuItem";
            this.quadcityToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.quadcityToolStripMenuItem.Text = "quadcity";
            this.quadcityToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // roseToolStripMenuItem
            // 
            this.roseToolStripMenuItem.Name = "roseToolStripMenuItem";
            this.roseToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.roseToolStripMenuItem.Text = "rose";
            this.roseToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // sierpinkyToolStripMenuItem
            // 
            this.sierpinkyToolStripMenuItem.Name = "sierpinkyToolStripMenuItem";
            this.sierpinkyToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.sierpinkyToolStripMenuItem.Text = "sierpinski";
            this.sierpinkyToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // snowflakeToolStripMenuItem
            // 
            this.snowflakeToolStripMenuItem.Name = "snowflakeToolStripMenuItem";
            this.snowflakeToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.snowflakeToolStripMenuItem.Text = "snowflake";
            this.snowflakeToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // tangleToolStripMenuItem
            // 
            this.tangleToolStripMenuItem.Name = "tangleToolStripMenuItem";
            this.tangleToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.tangleToolStripMenuItem.Text = "tangle";
            this.tangleToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // triplesToolStripMenuItem
            // 
            this.triplesToolStripMenuItem.Name = "triplesToolStripMenuItem";
            this.triplesToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.triplesToolStripMenuItem.Text = "triples";
            this.triplesToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // undergroundToolStripMenuItem
            // 
            this.undergroundToolStripMenuItem.Name = "undergroundToolStripMenuItem";
            this.undergroundToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.undergroundToolStripMenuItem.Text = "underground";
            this.undergroundToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // weighteddemoToolStripMenuItem
            // 
            this.weighteddemoToolStripMenuItem.Name = "weighteddemoToolStripMenuItem";
            this.weighteddemoToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.weighteddemoToolStripMenuItem.Text = "weighting_demo";
            this.weighteddemoToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // welcomeToolStripMenuItem
            // 
            this.welcomeToolStripMenuItem.Name = "welcomeToolStripMenuItem";
            this.welcomeToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.welcomeToolStripMenuItem.Text = "welcome";
            this.welcomeToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
            // 
            // ziggyToolStripMenuItem
            // 
            this.ziggyToolStripMenuItem.Name = "ziggyToolStripMenuItem";
            this.ziggyToolStripMenuItem.Size = new System.Drawing.Size(325, 44);
            this.ziggyToolStripMenuItem.Text = "ziggy";
            this.ziggyToolStripMenuItem.Click += new System.EventHandler(this.openExampleClick);
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
            this.writingCFDGFilesToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("writingCFDGFilesToolStripMenuItem.Image")));
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
            this.sendFeedbackToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("sendFeedbackToolStripMenuItem.Image")));
            this.sendFeedbackToolStripMenuItem.Name = "sendFeedbackToolStripMenuItem";
            this.sendFeedbackToolStripMenuItem.Size = new System.Drawing.Size(357, 44);
            this.sendFeedbackToolStripMenuItem.Tag = "mailto:info@contextfreeart.org";
            this.sendFeedbackToolStripMenuItem.Text = "&Send feedback...";
            this.sendFeedbackToolStripMenuItem.Click += new System.EventHandler(this.urlToolStripMenuItem_Click);
            // 
            // aboutContextFreeToolStripMenuItem
            // 
            this.aboutContextFreeToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("aboutContextFreeToolStripMenuItem.Image")));
            this.aboutContextFreeToolStripMenuItem.Name = "aboutContextFreeToolStripMenuItem";
            this.aboutContextFreeToolStripMenuItem.Size = new System.Drawing.Size(357, 44);
            this.aboutContextFreeToolStripMenuItem.Text = "&About Context Free";
            this.aboutContextFreeToolStripMenuItem.Click += new System.EventHandler(this.aboutContextFreeToolStripMenuItem_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "CFDG Files|*.cfdg";
            this.openFileDialog.Title = "Select a CFDG File";
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.Filter = "CFDG Files|*.cfdg";
            this.saveFileDialog1.Title = "Select a CFDG File";
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
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.formIsClosing);
            this.Load += new System.EventHandler(this.loadInitialization);
            this.MdiChildActivate += new System.EventHandler(this.childActivate);
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
        private ToolStripMenuItem menuFNew;
        private ToolStripMenuItem openToolStripMenuItem;
        private ToolStripMenuItem recentToolStripMenuItem;
        private ToolStripSeparator toolStripSeparator1;
        private ToolStripMenuItem preferencesToolStripMenuItem;
        private ToolStripMenuItem exitToolStripMenuItem;
        private ToolStripMenuItem examplesToolStripMenuItem;
        private ToolStripMenuItem helpToolStripMenuItem;
        private ToolStripMenuItem contextFreeSiteToolStripMenuItem;
        private ToolStripMenuItem galleryToolStripMenuItem;
        private ToolStripMenuItem forumsToolStripMenuItem;
        private ToolStripMenuItem writingCFDGFilesToolStripMenuItem;
        private ToolStripSeparator toolStripSeparator2;
        private ToolStripMenuItem sendFeedbackToolStripMenuItem;
        private ToolStripMenuItem aboutContextFreeToolStripMenuItem;
        private OpenFileDialog openFileDialog;
        private ToolStripMenuItem ciliasunToolStripMenuItem;
        private ToolStripMenuItem demo1ToolStripMenuItem;
        private ToolStripMenuItem demo2ToolStripMenuItem;
        private ToolStripMenuItem funkyflowerToolStripMenuItem;
        private ToolStripMenuItem icurvesToolStripMenuItem;
        private ToolStripMenuItem ipixToolStripMenuItem;
        private ToolStripMenuItem ipolygonsToolStripMenuItem;
        private ToolStripMenuItem lessonToolStripMenuItem;
        private ToolStripMenuItem lesson2ToolStripMenuItem;
        private ToolStripMenuItem mtreeToolStripMenuItem;
        private ToolStripMenuItem octopiToolStripMenuItem;
        private ToolStripMenuItem quadcityToolStripMenuItem;
        private ToolStripMenuItem roseToolStripMenuItem;
        private ToolStripMenuItem sierpinkyToolStripMenuItem;
        private ToolStripMenuItem snowflakeToolStripMenuItem;
        private ToolStripMenuItem tangleToolStripMenuItem;
        private ToolStripMenuItem triplesToolStripMenuItem;
        private ToolStripMenuItem undergroundToolStripMenuItem;
        private ToolStripMenuItem weighteddemoToolStripMenuItem;
        private ToolStripMenuItem welcomeToolStripMenuItem;
        private ToolStripMenuItem ziggyToolStripMenuItem;
        public SaveFileDialog saveFileDialog1;
    }
}