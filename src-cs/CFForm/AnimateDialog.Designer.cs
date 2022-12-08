namespace CFForm
{
    partial class AnimateDialog
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
            if (disposing && (components != null)) {
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AnimateDialog));
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.widthTextBox = new System.Windows.Forms.TextBox();
            this.heightTextBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.minSizeTextBox = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.trackBarBorder = new System.Windows.Forms.TrackBar();
            this.label10 = new System.Windows.Forms.Label();
            this.zoomCheckBox = new System.Windows.Forms.CheckBox();
            this.label11 = new System.Windows.Forms.Label();
            this.lengthTextBox = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.frameRateBox = new System.Windows.Forms.ComboBox();
            this.frameLabel = new System.Windows.Forms.Label();
            this.frameTextBox = new System.Windows.Forms.TextBox();
            this.formatLabel = new System.Windows.Forms.Label();
            this.formatComboBox = new System.Windows.Forms.ComboBox();
            this.okButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.errorMessage = new System.Windows.Forms.Label();
            this.previewCheckBox = new System.Windows.Forms.CheckBox();
            this.loopCheckBox = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarBorder)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(552, 136);
            this.label1.TabIndex = 0;
            this.label1.Text = "The image will be animated to fit the dimensions entered here, using the current " +
    "variation.  When complete, the movie or frame will be displayed scaled within th" +
    "e window.";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(28, 147);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(78, 32);
            this.label2.TabIndex = 1;
            this.label2.Text = "Width";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(176, 147);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(86, 32);
            this.label3.TabIndex = 2;
            this.label3.Text = "Height";
            // 
            // widthTextBox
            // 
            this.widthTextBox.Location = new System.Drawing.Point(12, 182);
            this.widthTextBox.Name = "widthTextBox";
            this.widthTextBox.Size = new System.Drawing.Size(110, 39);
            this.widthTextBox.TabIndex = 3;
            this.widthTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.numberKeyPress);
            // 
            // heightTextBox
            // 
            this.heightTextBox.Location = new System.Drawing.Point(164, 182);
            this.heightTextBox.Name = "heightTextBox";
            this.heightTextBox.Size = new System.Drawing.Size(110, 39);
            this.heightTextBox.TabIndex = 4;
            this.heightTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.numberKeyPress);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(128, 185);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(30, 32);
            this.label4.TabIndex = 5;
            this.label4.Text = "×";
            // 
            // minSizeTextBox
            // 
            this.minSizeTextBox.Location = new System.Drawing.Point(12, 239);
            this.minSizeTextBox.Name = "minSizeTextBox";
            this.minSizeTextBox.Size = new System.Drawing.Size(110, 39);
            this.minSizeTextBox.TabIndex = 6;
            this.minSizeTextBox.Validating += new System.ComponentModel.CancelEventHandler(this.validFloat);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(128, 242);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(271, 32);
            this.label5.TabIndex = 7;
            this.label5.Text = "size of smallest element";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Segoe UI", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label8.Location = new System.Drawing.Point(462, 389);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(79, 25);
            this.label8.TabIndex = 25;
            this.label8.Text = "variable";
            this.label8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Segoe UI", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label7.Location = new System.Drawing.Point(327, 389);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 25);
            this.label7.TabIndex = 24;
            this.label7.Text = "fixed";
            this.label7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Segoe UI", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label6.Location = new System.Drawing.Point(174, 389);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(55, 25);
            this.label6.TabIndex = 23;
            this.label6.Text = "none";
            this.label6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Segoe UI", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label9.Location = new System.Drawing.Point(9, 389);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(84, 25);
            this.label9.TabIndex = 22;
            this.label9.Text = "negative";
            this.label9.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // trackBarBorder
            // 
            this.trackBarBorder.BackColor = System.Drawing.SystemColors.Control;
            this.trackBarBorder.Location = new System.Drawing.Point(28, 333);
            this.trackBarBorder.Maximum = 99;
            this.trackBarBorder.Name = "trackBarBorder";
            this.trackBarBorder.Size = new System.Drawing.Size(500, 90);
            this.trackBarBorder.TabIndex = 26;
            this.trackBarBorder.TickFrequency = 33;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(12, 289);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(210, 32);
            this.label10.TabIndex = 21;
            this.label10.Text = "Image border size:";
            this.label10.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // zoomCheckBox
            // 
            this.zoomCheckBox.AutoSize = true;
            this.zoomCheckBox.Location = new System.Drawing.Point(12, 443);
            this.zoomCheckBox.Name = "zoomCheckBox";
            this.zoomCheckBox.Size = new System.Drawing.Size(226, 36);
            this.zoomCheckBox.TabIndex = 27;
            this.zoomCheckBox.Text = "Zoom Animation";
            this.zoomCheckBox.UseVisualStyleBackColor = true;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(19, 547);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(216, 32);
            this.label11.TabIndex = 28;
            this.label11.Text = "Length in Seconds:";
            // 
            // lengthTextBox
            // 
            this.lengthTextBox.Location = new System.Drawing.Point(243, 544);
            this.lengthTextBox.Name = "lengthTextBox";
            this.lengthTextBox.Size = new System.Drawing.Size(182, 39);
            this.lengthTextBox.TabIndex = 29;
            this.lengthTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.numberKeyPress);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(12, 592);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(223, 32);
            this.label12.TabIndex = 30;
            this.label12.Text = "Frames per Second:";
            // 
            // frameRateBox
            // 
            this.frameRateBox.FormattingEnabled = true;
            this.frameRateBox.Items.AddRange(new object[] {
            "8",
            "10",
            "12",
            "15",
            "24",
            "25",
            "30",
            "50",
            "60"});
            this.frameRateBox.Location = new System.Drawing.Point(243, 589);
            this.frameRateBox.Name = "frameRateBox";
            this.frameRateBox.Size = new System.Drawing.Size(182, 40);
            this.frameRateBox.TabIndex = 31;
            // 
            // frameLabel
            // 
            this.frameLabel.AutoSize = true;
            this.frameLabel.Location = new System.Drawing.Point(25, 638);
            this.frameLabel.Name = "frameLabel";
            this.frameLabel.Size = new System.Drawing.Size(210, 32);
            this.frameLabel.TabIndex = 32;
            this.frameLabel.Text = "Frame to Animate:";
            // 
            // frameTextBox
            // 
            this.frameTextBox.Location = new System.Drawing.Point(243, 635);
            this.frameTextBox.Name = "frameTextBox";
            this.frameTextBox.Size = new System.Drawing.Size(182, 39);
            this.frameTextBox.TabIndex = 33;
            this.frameTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.numberKeyPress);
            // 
            // formatLabel
            // 
            this.formatLabel.AutoSize = true;
            this.formatLabel.Location = new System.Drawing.Point(141, 638);
            this.formatLabel.Name = "formatLabel";
            this.formatLabel.Size = new System.Drawing.Size(94, 32);
            this.formatLabel.TabIndex = 34;
            this.formatLabel.Text = "Format:";
            // 
            // formatComboBox
            // 
            this.formatComboBox.FormattingEnabled = true;
            this.formatComboBox.Items.AddRange(new object[] {
            "H.264",
            "ProRes 422",
            "ProRes 4444"});
            this.formatComboBox.Location = new System.Drawing.Point(243, 635);
            this.formatComboBox.Name = "formatComboBox";
            this.formatComboBox.Size = new System.Drawing.Size(182, 40);
            this.formatComboBox.TabIndex = 35;
            // 
            // okButton
            // 
            this.okButton.Location = new System.Drawing.Point(243, 694);
            this.okButton.Name = "okButton";
            this.okButton.Size = new System.Drawing.Size(150, 46);
            this.okButton.TabIndex = 36;
            this.okButton.Text = "OK";
            this.okButton.UseVisualStyleBackColor = true;
            this.okButton.Click += new System.EventHandler(this.okCLick);
            // 
            // cancelButton
            // 
            this.cancelButton.Location = new System.Drawing.Point(400, 694);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(150, 46);
            this.cancelButton.TabIndex = 37;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.cancelClick);
            // 
            // errorMessage
            // 
            this.errorMessage.Location = new System.Drawing.Point(12, 679);
            this.errorMessage.Name = "errorMessage";
            this.errorMessage.Size = new System.Drawing.Size(217, 64);
            this.errorMessage.TabIndex = 38;
            // 
            // previewCheckBox
            // 
            this.previewCheckBox.AutoSize = true;
            this.previewCheckBox.Location = new System.Drawing.Point(12, 485);
            this.previewCheckBox.Name = "previewCheckBox";
            this.previewCheckBox.Size = new System.Drawing.Size(194, 36);
            this.previewCheckBox.TabIndex = 39;
            this.previewCheckBox.Text = "Show preview";
            this.previewCheckBox.UseVisualStyleBackColor = true;
            // 
            // loopCheckBox
            // 
            this.loopCheckBox.AutoSize = true;
            this.loopCheckBox.Location = new System.Drawing.Point(212, 485);
            this.loopCheckBox.Name = "loopCheckBox";
            this.loopCheckBox.Size = new System.Drawing.Size(180, 36);
            this.loopCheckBox.TabIndex = 40;
            this.loopCheckBox.Text = "with looping";
            this.loopCheckBox.UseVisualStyleBackColor = true;
            // 
            // AnimateDialog
            // 
            this.AcceptButton = this.okButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(13F, 32F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(562, 752);
            this.Controls.Add(this.loopCheckBox);
            this.Controls.Add(this.previewCheckBox);
            this.Controls.Add(this.errorMessage);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.okButton);
            this.Controls.Add(this.formatComboBox);
            this.Controls.Add(this.formatLabel);
            this.Controls.Add(this.frameTextBox);
            this.Controls.Add(this.frameLabel);
            this.Controls.Add(this.frameRateBox);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.lengthTextBox);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.zoomCheckBox);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.trackBarBorder);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.minSizeTextBox);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.heightTextBox);
            this.Controls.Add(this.widthTextBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AnimateDialog";
            this.Text = "Start Animation";
            ((System.ComponentModel.ISupportInitialize)(this.trackBarBorder)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Label label1;
        private Label label2;
        private Label label3;
        private TextBox widthTextBox;
        private TextBox heightTextBox;
        private Label label4;
        private TextBox minSizeTextBox;
        private Label label5;
        private Label label8;
        private Label label7;
        private Label label6;
        private Label label9;
        private TrackBar trackBarBorder;
        private Label label10;
        private CheckBox zoomCheckBox;
        private Label label11;
        private TextBox lengthTextBox;
        private Label label12;
        private ComboBox frameRateBox;
        private Label frameLabel;
        private Label formatLabel;
        private ComboBox formatComboBox;
        private Button okButton;
        private Button cancelButton;
        public TextBox frameTextBox;
        private Label errorMessage;
        private CheckBox previewCheckBox;
        private CheckBox loopCheckBox;
    }
}