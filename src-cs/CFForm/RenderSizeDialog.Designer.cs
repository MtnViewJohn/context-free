namespace CFForm
{
    partial class RenderSizeDialog
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(RenderSizeDialog));
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.minimumSizeBox = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.trackBarBorder = new System.Windows.Forms.TrackBar();
            this.label9 = new System.Windows.Forms.Label();
            this.noDisplayCheckBox = new System.Windows.Forms.CheckBox();
            this.widthBox = new System.Windows.Forms.TextBox();
            this.heightBox = new System.Windows.Forms.TextBox();
            this.OKbutton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarBorder)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(17, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 32);
            this.label1.TabIndex = 0;
            this.label1.Text = "Size:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(235, 15);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(30, 32);
            this.label2.TabIndex = 2;
            this.label2.Text = "×";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(421, 15);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(101, 32);
            this.label3.TabIndex = 4;
            this.label3.Text = "in pixels";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(17, 80);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(274, 32);
            this.label4.TabIndex = 5;
            this.label4.Text = "Size of smallest element";
            // 
            // minimumSizeBox
            // 
            this.minimumSizeBox.Location = new System.Drawing.Point(297, 77);
            this.minimumSizeBox.Name = "minimumSizeBox";
            this.minimumSizeBox.Size = new System.Drawing.Size(148, 39);
            this.minimumSizeBox.TabIndex = 6;
            this.minimumSizeBox.Validating += new System.ComponentModel.CancelEventHandler(this.validFloat);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Segoe UI", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label8.Location = new System.Drawing.Point(669, 190);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(79, 25);
            this.label8.TabIndex = 19;
            this.label8.Text = "variable";
            this.label8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Segoe UI", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label7.Location = new System.Drawing.Point(534, 190);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 25);
            this.label7.TabIndex = 18;
            this.label7.Text = "fixed";
            this.label7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Segoe UI", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label6.Location = new System.Drawing.Point(381, 190);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(55, 25);
            this.label6.TabIndex = 17;
            this.label6.Text = "none";
            this.label6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Segoe UI", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.label5.Location = new System.Drawing.Point(216, 190);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(84, 25);
            this.label5.TabIndex = 16;
            this.label5.Text = "negative";
            this.label5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // trackBarBorder
            // 
            this.trackBarBorder.BackColor = System.Drawing.SystemColors.Control;
            this.trackBarBorder.Location = new System.Drawing.Point(235, 134);
            this.trackBarBorder.Maximum = 99;
            this.trackBarBorder.Name = "trackBarBorder";
            this.trackBarBorder.Size = new System.Drawing.Size(500, 90);
            this.trackBarBorder.TabIndex = 20;
            this.trackBarBorder.TickFrequency = 33;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(19, 134);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(210, 32);
            this.label9.TabIndex = 15;
            this.label9.Text = "Image border size:";
            this.label9.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // noDisplayCheckBox
            // 
            this.noDisplayCheckBox.AutoSize = true;
            this.noDisplayCheckBox.Location = new System.Drawing.Point(19, 238);
            this.noDisplayCheckBox.Name = "noDisplayCheckBox";
            this.noDisplayCheckBox.Size = new System.Drawing.Size(305, 36);
            this.noDisplayCheckBox.TabIndex = 21;
            this.noDisplayCheckBox.Text = "Don\'t display final result";
            this.noDisplayCheckBox.UseVisualStyleBackColor = true;
            // 
            // widthBox
            // 
            this.widthBox.Location = new System.Drawing.Point(85, 12);
            this.widthBox.Name = "widthBox";
            this.widthBox.Size = new System.Drawing.Size(144, 39);
            this.widthBox.TabIndex = 1;
            this.widthBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.numberKeyPress);
            // 
            // heightBox
            // 
            this.heightBox.Location = new System.Drawing.Point(271, 12);
            this.heightBox.Name = "heightBox";
            this.heightBox.Size = new System.Drawing.Size(144, 39);
            this.heightBox.TabIndex = 3;
            this.heightBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.numberKeyPress);
            // 
            // OKbutton
            // 
            this.OKbutton.Location = new System.Drawing.Point(482, 280);
            this.OKbutton.Name = "OKbutton";
            this.OKbutton.Size = new System.Drawing.Size(150, 46);
            this.OKbutton.TabIndex = 22;
            this.OKbutton.Text = "OK";
            this.OKbutton.UseVisualStyleBackColor = true;
            this.OKbutton.Click += new System.EventHandler(this.OKbuttonClick);
            // 
            // cancelButton
            // 
            this.cancelButton.Location = new System.Drawing.Point(638, 280);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(150, 46);
            this.cancelButton.TabIndex = 23;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.cancelButtonClick);
            // 
            // RenderSizeDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(13F, 32F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 338);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.OKbutton);
            this.Controls.Add(this.heightBox);
            this.Controls.Add(this.widthBox);
            this.Controls.Add(this.noDisplayCheckBox);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.trackBarBorder);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.minimumSizeBox);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "RenderSizeDialog";
            this.Text = "Render to Size";
            ((System.ComponentModel.ISupportInitialize)(this.trackBarBorder)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;
        private TextBox minimumSizeBox;
        private Label label8;
        private Label label7;
        private Label label6;
        private Label label5;
        private TrackBar trackBarBorder;
        private Label label9;
        private CheckBox noDisplayCheckBox;
        private TextBox widthBox;
        private TextBox heightBox;
        private Button OKbutton;
        private Button cancelButton;
    }
}