#region Copyright ©2005, Cristi Potlog - All Rights Reserved
/* ------------------------------------------------------------------- *
*                            Cristi Potlog                             *
*                  Copyright ©2005 - All Rights reserved               *
*                                                                      *
* THIS SOURCE CODE IS PROVIDED "AS IS" WITH NO WARRANTIES OF ANY KIND, *
* EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE        *
* WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR   *
* PURPOSE, NONINFRINGEMENT, OR ARISING FROM A COURSE OF DEALING,       *
* USAGE OR TRADE PRACTICE.                                             *
*                                                                      *
* THIS COPYRIGHT NOTICE MAY NOT BE REMOVED FROM THIS FILE.             *
* ------------------------------------------------------------------- */
#endregion Copyright ©2005, Cristi Potlog - All Rights Reserved

#region References
using System;
using System.Collections;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Windows.Forms;
using System.Windows.Forms.Design;
using System.ComponentModel.Design;
#endregion

namespace CristiPotlog.Controls
{
	/// <summary>
	/// Represents an extentable wizard control with basic page navigation functionality.
	/// </summary>
	[Designer(typeof(Wizard.WizardDesigner))]
	public class Wizard : System.Windows.Forms.UserControl
	{

		#region Consts
		private const int FOOTER_AREA_HEIGHT = 48;
		private readonly Point offsetCancel = new Point(84, 36);
		private readonly Point offsetNext = new Point(168, 36);
		private readonly Point offsetBack = new Point(244, 36);
		#endregion

		#region Fields
		private WizardPage selectedPage = null;
		private WizardPagesCollection pages = null;
		private Image headerImage = null;
		private Image welcomeImage = null;
		private Font headerFont = null;
		private Font headerTitleFont = null;
		private Font welcomeFont = null;
		private Font welcomeTitleFont = null;
		#endregion
        public Button buttonCancel;

		#region Designer generated code

        private System.Windows.Forms.Button buttonNext;
		private System.Windows.Forms.Button buttonBack;
		private System.Windows.Forms.Button buttonHelp;
		/// <summary> 
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
		#endregion

		#region Constructor&Dispose
		/// <summary>
		/// Creates a new instance of the <see cref="Wizard"/> class.
		/// </summary>
		public Wizard()
		{
			// call required by designer
			this.InitializeComponent();

			// reset control style to improove rendering (reduce flicker)
			base.SetStyle(ControlStyles.AllPaintingInWmPaint, true); 
			base.SetStyle(ControlStyles.DoubleBuffer, true);
			base.SetStyle(ControlStyles.ResizeRedraw, true);
			base.SetStyle(ControlStyles.UserPaint, true);

			// reset dock style
			base.Dock = DockStyle.Fill;

			// init pages collection
			this.pages = new WizardPagesCollection(this);
		}

		/// <summary> 
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				if (this.components != null)
				{
					this.components.Dispose();
				}
			}
			base.Dispose(disposing);
		}

		#endregion

		#region Designer generated code
		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
            this.buttonCancel = new System.Windows.Forms.Button();
            this.buttonNext = new System.Windows.Forms.Button();
            this.buttonBack = new System.Windows.Forms.Button();
            this.buttonHelp = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonCancel
            // 
            this.buttonCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.buttonCancel.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.buttonCancel.Location = new System.Drawing.Point(344, 224);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 8;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // buttonNext
            // 
            this.buttonNext.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonNext.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.buttonNext.Location = new System.Drawing.Point(260, 224);
            this.buttonNext.Name = "buttonNext";
            this.buttonNext.Size = new System.Drawing.Size(75, 23);
            this.buttonNext.TabIndex = 7;
            this.buttonNext.Text = "&Next >";
            this.buttonNext.Click += new System.EventHandler(this.buttonNext_Click);
            // 
            // buttonBack
            // 
            this.buttonBack.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonBack.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.buttonBack.Location = new System.Drawing.Point(184, 224);
            this.buttonBack.Name = "buttonBack";
            this.buttonBack.Size = new System.Drawing.Size(75, 23);
            this.buttonBack.TabIndex = 6;
            this.buttonBack.Text = "< &Back";
            this.buttonBack.Click += new System.EventHandler(this.buttonBack_Click);
            // 
            // buttonHelp
            // 
            this.buttonHelp.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonHelp.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.buttonHelp.Location = new System.Drawing.Point(8, 224);
            this.buttonHelp.Name = "buttonHelp";
            this.buttonHelp.Size = new System.Drawing.Size(75, 23);
            this.buttonHelp.TabIndex = 9;
            this.buttonHelp.Text = "&Help";
            this.buttonHelp.Visible = false;
            this.buttonHelp.Click += new System.EventHandler(this.buttonHelp_Click);
            // 
            // Wizard
            // 
            this.Controls.Add(this.buttonHelp);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonNext);
            this.Controls.Add(this.buttonBack);
            this.Name = "Wizard";
            this.Size = new System.Drawing.Size(428, 256);
            this.ResumeLayout(false);

        }
		#endregion

		#region Properties
		/// <summary>
		/// Gets or sets which edge of the parent container a control is docked to.
		/// </summary>
		[DefaultValue(DockStyle.Fill)]
		[Category("Layout")]
		[Description("Gets or sets which edge of the parent container a control is docked to.")]
		public new DockStyle Dock
		{
			get
			{
				return base.Dock;
			}
			set
			{
				base.Dock = value;
			}
		}

		/// <summary>
		/// Gets the collection of wizard pages in this tab control.
		/// </summary>
		[Category("Wizard")]
		[DesignerSerializationVisibility(DesignerSerializationVisibility.Content)]
		[Description("Gets the collection of wizard pages in this tab control.")]
		public WizardPagesCollection Pages
		{
			get
			{
				return this.pages;
			}
		}

		/// <summary>
		/// Gets or sets the currently-selected wizard page.
		/// </summary>
		[Browsable(false)]
		[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
		public WizardPage SelectedPage
		{
			get
			{
				return this.selectedPage;
			}
			set
			{
				// select new page
				this.ActivatePage(value);
			}
		}

		/// <summary>
		/// Gets or sets the currently-selected wizard page by index.
		/// </summary>
		[Browsable(false)]
		[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
		internal int SelectedIndex
		{
			get
			{
				return this.pages.IndexOf(this.selectedPage);
			}
			set
			{
				// check if there are any pages
				if(this.pages.Count == 0)
				{
					// reset invalid index
					this.ActivatePage(-1);
					return;
				}

				// validate page index
				if (value < -1 || value >= this.pages.Count)
				{
					throw new ArgumentOutOfRangeException("SelectedIndex",
														value,
														"The page index must be between 0 and " + Convert.ToString(this.pages.Count - 1));
				}

				// select new page
				this.ActivatePage(value);
			}
		}

		/// <summary>
		/// Gets or sets the image displayed on the header of the standard pages.
		/// </summary>
		[DefaultValue(null)]
		[Category("Wizard")]
		[Description("Gets or sets the image displayed on the header of the standard pages.")]
		public Image HeaderImage
		{
			get
			{
				return this.headerImage;
			}
			set
			{
				if (this.headerImage != value)
				{
					this.headerImage = value;
					this.Invalidate();
				}
			}
		}

		/// <summary>
		/// Gets or sets the image displayed on the welcome and finish pages.
		/// </summary>
		[DefaultValue(null)]
		[Category("Wizard")]
		[Description("Gets or sets the image displayed on the welcome and finish pages.")]
		public Image WelcomeImage
		{
			get
			{
				return this.welcomeImage;
			}
			set
			{
				if (this.welcomeImage != value)
				{
					this.welcomeImage = value;
					this.Invalidate();
				}
			}
		}

		/// <summary>
		/// Gets or sets the font used to display the description of a standard page.
		/// </summary>
		[Category("Appearance")]
		[Description("Gets or sets the font used to display the description of a standard page.")]
		public Font HeaderFont
		{
			get
			{
				if (this.headerFont == null)
				{
					return this.Font;
				}
				else
				{
					return this.headerFont;
				}
			}
			set
			{
				if (this.headerFont != value)
				{
					this.headerFont = value;
					this.Invalidate();
				}
			}
		}
		protected bool ShouldSerializeHeaderFont()
		{
			return this.headerFont != null;
		}

		/// <summary>
		/// Gets or sets the font used to display the title of a standard page.
		/// </summary>
		[Category("Appearance")]
		[Description("Gets or sets the font used to display the title of a standard page.")]
		public Font HeaderTitleFont
		{
			get
			{
				if (this.headerTitleFont == null)
				{
					return new Font(this.Font.FontFamily, this.Font.Size + 2, FontStyle.Bold);
				}
				else
				{
					return this.headerTitleFont;
				}
			}
			set
			{
				if (this.headerTitleFont != value)
				{
					this.headerTitleFont = value;
					this.Invalidate();
				}
			}
		}
		protected bool ShouldSerializeHeaderTitleFont()
		{
			return this.headerTitleFont != null;
		}

		/// <summary>
		/// Gets or sets the font used to display the description of a welcome of finish page.
		/// </summary>
		[Category("Appearance")]
		[Description("Gets or sets the font used to display the description of a welcome of finish page.")]
		public Font WelcomeFont
		{
			get
			{
				if (this.welcomeFont == null)
				{
					return this.Font;
				}
				else
				{
					return this.welcomeFont;
				}
			}
			set
			{
				if (this.welcomeFont != value)
				{
					this.welcomeFont = value;
					this.Invalidate();
				}
			}
		}
		protected bool ShouldSerializeWelcomeFont()
		{
			return this.welcomeFont != null;
		}

		/// <summary>
		/// Gets or sets the font used to display the title of a welcome of finish page.
		/// </summary>
		[Category("Appearance")]
		[Description("Gets or sets the font used to display the title of a welcome of finish page.")]
		public Font WelcomeTitleFont
		{
			get
			{
				if (this.welcomeTitleFont == null)
				{
					return new Font(this.Font.FontFamily, this.Font.Size + 10, FontStyle.Bold);
				}
				else
				{
					return this.welcomeTitleFont;
				}
			}
			set
			{
				if (this.welcomeTitleFont != value)
				{
					this.welcomeTitleFont = value;
					this.Invalidate();
				}
			}
		}
		protected bool ShouldSerializeWelcomeTitleFont()
		{
			return this.welcomeTitleFont != null;
		}

		/// <summary>
		/// Gets or sets the enabled state of the Next button. 
		/// </summary>
		[Browsable(false)]
		[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
		public bool NextEnabled
		{
			get
			{
				return this.buttonNext.Enabled;
			}
			set
			{
				this.buttonNext.Enabled = value;
			}
		}

		/// <summary>
		/// Gets or sets the enabled state of the back button. 
		/// </summary>
		[Browsable(false)]
		[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
		public bool BackEnabled
		{
			get
			{
				return this.buttonBack.Enabled;
			}
			set
			{
				this.buttonBack.Enabled = value;
			}
		}

		/// <summary>
		/// Gets or sets the enabled state of the cancel button. 
		/// </summary>
		[Browsable(false)]
		[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
		public bool CancelEnabled
		{
			get
			{
				return this.buttonCancel.Enabled;
			}
			set
			{
		
				this.buttonCancel.Enabled = value;
			}
		}

		/// <summary>
		/// Gets or sets the visible state of the help button. 
		/// </summary>
		[Category("Behavior")]
		[DefaultValue(false)]
		[Description("Gets or sets the visible state of the help button. ")]
		public bool HelpVisible
		{
			get
			{
				return this.buttonHelp.Visible;
			}
			set
			{
		
				this.buttonHelp.Visible = value;
			}
		}

		/// <summary>
		/// Gets or sets the text displayed by the Next button. 
		/// </summary>
		[Browsable(false)]
		[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
		public string NextText
		{
			get
			{
				return this.buttonNext.Text;
			}
			set
			{
				this.buttonNext.Text = value;
			}
		}

		/// <summary>
		/// Gets or sets the text displayed by the back button. 
		/// </summary>
		[Browsable(false)]
		[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
		public string BackText
		{
			get
			{
				return this.buttonBack.Text;
			}
			set
			{
				this.buttonBack.Text = value;
			}
		}

		/// <summary>
		/// Gets or sets the text displayed by the cancel button. 
		/// </summary>
		[Browsable(false)]
		[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
		public string CancelText
		{
			get
			{
				return this.buttonCancel.Text;
			}
			set
			{
		
				this.buttonCancel.Text = value;
			}
		}

		/// <summary>
		/// Gets or sets the text displayed by the cancel button. 
		/// </summary>
		[Browsable(false)]
		[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
		public string HelpText
		{
			get
			{
				return this.buttonHelp.Text;
			}
			set
			{
		
				this.buttonHelp.Text = value;
			}
		}

		#endregion

		#region Methods
		/// <summary>
		/// Swithes forward to next wizard page.
		/// </summary>
		public void Next()
		{
			// check if we're on the last page (finish)
			if (this.SelectedIndex == this.pages.Count - 1)
			{
				this.buttonNext.Enabled = false;
			}
			else
			{
				// handle page switch
				this.OnBeforeSwitchPages(new BeforeSwitchPagesEventArgs(this.SelectedIndex, this.SelectedIndex + 1));
			}
		}

		/// <summary>
		/// Swithes backward to previous wizard page.
		/// </summary>
		public void Back()
		{
			if (this.SelectedIndex == 0)
			{
				this.buttonBack.Enabled = false;
			}
			else
			{
				// handle page switch
				this.OnBeforeSwitchPages(new BeforeSwitchPagesEventArgs(this.SelectedIndex, this.SelectedIndex - 1));
			}
		}

		/// <summary>
		/// Activates the specified wizard bage.
		/// </summary>
		/// <param name="index">An Integer value representing the zero-based index of the page to be activated.</param>
		private void ActivatePage(int index)
		{
			// check if new page is invalid
			if (index < 0 || index >= this.pages.Count)
			{
				// filter out
				return;
			}
		
			// get new page
			WizardPage page = (WizardPage)this.pages[index];

			// activate page
			this.ActivatePage(page);
		}

		/// <summary>
		/// Activates the specified wizard bage.
		/// </summary>
		/// <param name="page">A WizardPage object representing the page to be activated.</param>
		private void ActivatePage(WizardPage page)
		{
			// validate given page
			if (this.pages.Contains(page) == false)
			{
				// filter out
				return;
			}

			// deactivate current page
			if (this.selectedPage != null)
			{
				this.selectedPage.Visible = false;
			}

			// activate new page
			this.selectedPage = page;

			if (this.selectedPage != null)
			{
				//Ensure that this panel displays inside the wizard
				this.selectedPage.Parent = this;
				if (this.Contains(this.selectedPage) == false)
				{	
					this.Container.Add(this.selectedPage);
				}
				if (this.selectedPage.Style == WizardPageStyle.Finish)
				{
					this.buttonCancel.Text = "OK";
					this.buttonCancel.DialogResult = DialogResult.OK;
				}
				else
				{
					this.buttonCancel.Text = "Cancel";
					this.buttonCancel.DialogResult = DialogResult.Cancel;
				}

				//Make it fill the space
				this.selectedPage.SetBounds(0, 0, this.Width, this.Height - FOOTER_AREA_HEIGHT);
				this.selectedPage.Visible = true;
				this.selectedPage.BringToFront();
				this.FocusFirstTabIndex(this.selectedPage);
			}
			
			//What should the back button say
			if (this.SelectedIndex > 0)
			{
				buttonBack.Enabled = true;
			}
			else
			{
				buttonBack.Enabled = false;
			}

			//What should the Next button say
			if (this.SelectedIndex < this.pages.Count - 1)
			{
				this.buttonNext.Enabled = true;
			}
			else
			{
				if (this.DesignMode == false)
				{
					// at runtime disable back button (we finished; there's no point going back)
					buttonBack.Enabled = false;
				}
				this.buttonNext.Enabled = false;
			}
			
			// refresh
			if (this.selectedPage != null)
			{
				this.selectedPage.Invalidate();
			}
			else
			{
				this.Invalidate();
			}
		}

		/// <summary>
		/// Focus the control with a lowest tab index in the given container.
		/// </summary>
		/// <param name="container">A Control object to pe processed.</param>
		private void FocusFirstTabIndex(Control container)
		{
			// init search result varialble
			Control searchResult = null;

			// find the control with the lowest tab index
			foreach (Control control in container.Controls)
			{
				if (control.CanFocus && (searchResult == null || control.TabIndex < searchResult.TabIndex))
				{
					searchResult = control;
				}
			}

			// check if anything searchResult
			if (searchResult != null)
			{
				// focus found control
				searchResult.Focus();
			}
			else
			{
				// focus the container
				container.Focus();
			}
		}

		/// <summary>
		/// Raises the SwitchPages event.
		/// </summary>
		/// <param name="e">A WizardPageEventArgs object that holds event data.</param>
		protected virtual void OnBeforeSwitchPages(BeforeSwitchPagesEventArgs e)
		{
			// check if there are subscribers
			if (this.BeforeSwitchPages != null)
			{
				// raise BeforeSwitchPages event
				this.BeforeSwitchPages(this, e);
			}

			// check if user canceled
			if (e.Cancel)
			{
				// filter
				return;
			}

			// activate new page
			this.ActivatePage(e.NewIndex);

			// raise the after event
			this.OnAfterSwitchPages(e as AfterSwitchPagesEventArgs);
		}

		/// <summary>
		/// Raises the SwitchPages event.
		/// </summary>
		/// <param name="e">A WizardPageEventArgs object that holds event data.</param>
		protected virtual void OnAfterSwitchPages(AfterSwitchPagesEventArgs e)
		{
			// check if there are subscribers
			if (this.AfterSwitchPages != null)
			{
				// raise AfterSwitchPages event
				this.AfterSwitchPages(this, e);
			}
		}

		/// <summary>
		/// Raises the Cancel event.
		/// </summary>
		/// <param name="e">A CancelEventArgs object that holds event data.</param>
		protected virtual void OnCancel(CancelEventArgs e)
		{
			// check if there are subscribers
			if (this.Cancel != null)
			{
				// raise Cancel event
				this.Cancel(this, e);
			}

			// check if user canceled
			if (e.Cancel)
			{
				// cancel closing (when ShowDialog is used)
				this.ParentForm.DialogResult = DialogResult.None;
			}
			else
			{
				// ensure parent form is closed (even when ShowDialog is not used)
				this.ParentForm.Close();
			}
		}

		/// <summary>
		/// Raises the Finish event.
		/// </summary>
		/// <param name="e">A EventArgs object that holds event data.</param>
		protected virtual void OnFinish(EventArgs e)
		{
			// check if there are subscribers
			if (this.Finish != null)
			{
				// raise Finish event
				this.Finish(this, e);
			}

			// ensure parent form is closed (even when ShowDialog is not used)
			this.ParentForm.Close();
		}

		/// <summary>
		/// Raises the Help event.
		/// </summary>
		/// <param name="e">A EventArgs object that holds event data.</param>
		protected virtual void OnHelp(EventArgs e)
		{
			// check if there are subscribers
			if (this.Help != null)
			{
				// raise Help event
				this.Help(this, e);
			}
		}

		/// <summary>
		/// Raises the Load event.
		/// </summary>
		protected override void OnLoad(EventArgs e)
		{
			// raise the Load event
			base.OnLoad(e);
			
			// activate first page, if exists
			if (this.pages.Count > 0)
			{
                this.OnBeforeSwitchPages(new BeforeSwitchPagesEventArgs(-1, 0));
                //this.ActivatePage(0);
			}
		}

		/// <summary>
		/// Raises the Resize event.
		/// </summary>
		protected override void OnResize(EventArgs e)
		{
			// raise the Resize event
			base.OnResize(e);

			// resize the selected page to fit the wizard
			if (this.selectedPage != null)
			{
				this.selectedPage.SetBounds(0, 0, this.Width, this.Height - FOOTER_AREA_HEIGHT);
			}

			// position navigation buttons
			this.buttonCancel.Location = new Point(this.Width - this.offsetCancel.X,
													this.Height - this.offsetCancel.Y);
			this.buttonNext.Location = new Point(this.Width - this.offsetNext.X,
												this.Height - this.offsetNext.Y);
			this.buttonBack.Location = new Point(this.Width - this.offsetBack.X,
												this.Height - this.offsetBack.Y);
			this.buttonHelp.Location = new Point(this.buttonHelp.Location.X,
												this.Height - this.offsetBack.Y);
		}

		/// <summary>
		/// Raises the Paint event.
		/// </summary>
		protected override void OnPaint(PaintEventArgs e)
		{
			// raise the Paint event
			base.OnPaint(e);
			
			Rectangle bottomRect = this.ClientRectangle;
			bottomRect.Y = this.Height - FOOTER_AREA_HEIGHT;
			bottomRect.Height = FOOTER_AREA_HEIGHT;
			ControlPaint.DrawBorder3D(e.Graphics, bottomRect, Border3DStyle.Etched, Border3DSide.Top);
		}

		/// <summary>
		/// Raises the ControlAdded event.
		/// </summary>
		protected override void OnControlAdded(ControlEventArgs e) 
		{
			// prevent other controls from being added directly to the wizard
			if (e.Control is WizardPage == false &&
				e.Control != this.buttonCancel &&
				e.Control != this.buttonNext &&
				e.Control != this.buttonBack)
			{
				// add the control to the selected page
				if (this.selectedPage != null)
				{
					this.selectedPage.Controls.Add(e.Control);
				}
			}
			else
			{
				// raise the ControlAdded event
				base.OnControlAdded(e);
			}
		}

		#endregion

		#region Events
		/// <summary>
		/// Occurs before the wizard pages are switched, giving the user a chance to validate.
		/// </summary>
		[Category("Wizard")]
		[Description("Occurs before the wizard pages are switched, giving the user a chance to validate.")]
		public event BeforeSwitchPagesEventHandler BeforeSwitchPages;
		/// <summary>
		/// Occurs after the wizard pages are switched, giving the user a chance to setup the new page.
		/// </summary>
		[Category("Wizard")]
		[Description("Occurs after the wizard pages are switched, giving the user a chance to setup the new page.")]
		public event AfterSwitchPagesEventHandler AfterSwitchPages;
		/// <summary>
		/// Occurs when wizard is canceled, giving the user a chance to validate.
		/// </summary>
		[Category("Wizard")]
		[Description("Occurs when wizard is canceled, giving the user a chance to validate.")]
		public event CancelEventHandler Cancel;
		/// <summary>
		/// Occurs when wizard is finished, giving the user a chance to do extra stuff.
		/// </summary>
		[Category("Wizard")]
		[Description("Occurs when wizard is finished, giving the user a chance to do extra stuff.")]
		public event EventHandler Finish;
		/// <summary>
		/// Occurs when the user clicks the help button.
		/// </summary>
		[Category("Wizard")]
		[Description("Occurs when the user clicks the help button.")]
		public event EventHandler Help;
		/// <summary>
		/// Represents the method that will handle the BeforeSwitchPages event of the Wizard control.
		/// </summary>
		public delegate void BeforeSwitchPagesEventHandler(object sender, BeforeSwitchPagesEventArgs e);
		/// <summary>
		/// Represents the method that will handle the AfterSwitchPages event of the Wizard control.
		/// </summary>
		public delegate void AfterSwitchPagesEventHandler(object sender, AfterSwitchPagesEventArgs e);
		#endregion

		#region Events handlers
		/// <summary>
		/// Handles the Click event of buttonNext.
		/// </summary>
		private void buttonNext_Click(object sender, System.EventArgs e)
		{
			this.Next();
		}

		/// <summary>
		/// Handles the Click event of buttonBack.
		/// </summary>
		private void buttonBack_Click(object sender, System.EventArgs e)
		{
			this.Back();
		}
		
		/// <summary>
		/// Handles the Click event of buttonCancel.
		/// </summary>
		private void buttonCancel_Click(object sender, System.EventArgs e)
		{
			// check if button is cancel mode
			if (this.buttonCancel.DialogResult == DialogResult.Cancel)
			{
				this.OnCancel(new CancelEventArgs());
			}
			// check if button is finish mode
			else if (this.buttonCancel.DialogResult == DialogResult.OK)
			{
				this.OnFinish(EventArgs.Empty);
			}
		}
		
		/// <summary>
		/// Handles the Click event of buttonHelp.
		/// </summary>
        private void buttonHelp_Click(object sender, System.EventArgs e)
        {
			this.OnHelp(EventArgs.Empty);
        }
		#endregion

		#region Inner classes
		/// <summary>
		/// Represents a designer for the wizard control.
		/// </summary>
		internal class WizardDesigner : ParentControlDesigner
		{

			#region Methods
			/// <summary>
			/// Overrides the handling of Mouse clicks to allow back-next to work in the designer.
			/// </summary>
			/// <param name="msg">A Message value.</param>
			protected override void WndProc(ref Message msg)
			{
				// declare PInvoke constants
				const int WM_LBUTTONDOWN = 0x0201;
				const int WM_LBUTTONDBLCLK = 0x0203;

				// check message
				if (msg.Msg == WM_LBUTTONDOWN || msg.Msg == WM_LBUTTONDBLCLK)
				{
					// get the control under the mouse
					ISelectionService ss = (ISelectionService)GetService(typeof(ISelectionService));
					
					if (ss.PrimarySelection is Wizard)
					{
						Wizard wizard = (Wizard)ss.PrimarySelection;

						// extract the mouse position
						int xPos = (short)((uint)msg.LParam & 0x0000FFFF);
						int yPos = (short)(((uint)msg.LParam & 0xFFFF0000) >> 16);
						Point mousePos =  new Point(xPos, yPos);
						
						if (msg.HWnd == wizard.buttonNext.Handle)
						{
							if (wizard.buttonNext.Enabled && 
								wizard.buttonNext.ClientRectangle.Contains(mousePos))
							{
								//Press the button
								wizard.Next();
							}
						}
						else if (msg.HWnd == wizard.buttonBack.Handle)
						{
							if (wizard.buttonBack.Enabled && 
								wizard.buttonBack.ClientRectangle.Contains(mousePos))
							{
								//Press the button
								wizard.Back();
							}
						}
						
						// filter message
						return;
					}
				}

				// forward message
				base.WndProc(ref msg);
			}

			/// <summary>
			/// Prevents the grid from being drawn on the Wizard.
			/// </summary>
			protected override bool DrawGrid
			{
				get
				{
					return false;
				}
			}
			#endregion

		}

		/// <summary>
		/// Provides data for the AfterSwitchPages event of the Wizard control.
		/// </summary>
		public class AfterSwitchPagesEventArgs : EventArgs
		{

			#region Fields
			private int oldIndex;
			protected int newIndex;
			#endregion

			#region Constructor
			/// <summary>
			/// Creates a new instance of the <see cref="WizardPageEventArgs"/> class.
			/// </summary>
			/// <param name="oldIndex">An integer value representing the index of the old page.</param>
			/// <param name="newIndex">An integer value representing the index of the new page.</param>
			internal AfterSwitchPagesEventArgs(int oldIndex, int newIndex)
			{
				this.oldIndex = oldIndex;
				this.newIndex = newIndex;
			}

			#endregion

			#region Properties
			/// <summary>
			/// Gets the index of the old page.
			/// </summary>
			public int OldIndex
			{
				get
				{
					return this.oldIndex;
				}
			}

			/// <summary>
			/// Gets or sets the index of the new page.
			/// </summary>
			public int NewIndex
			{
				get
				{
					return this.newIndex;
				}
			}
			#endregion

		}

		/// <summary>
		/// Provides data for the BeforeSwitchPages event of the Wizard control.
		/// </summary>
		public class BeforeSwitchPagesEventArgs : AfterSwitchPagesEventArgs
		{

			#region Fields
			private bool cancel = false;
			#endregion

			#region Constructor
			/// <summary>
			/// Creates a new instance of the <see cref="WizardPageEventArgs"/> class.
			/// </summary>
			/// <param name="oldIndex">An integer value representing the index of the old page.</param>
			/// <param name="newIndex">An integer value representing the index of the new page.</param>
			internal BeforeSwitchPagesEventArgs(int oldIndex, int newIndex) : base(oldIndex, newIndex)
			{
				// nothing
			}

			#endregion

			#region Properties
			/// <summary>
			/// Indicates whether the page switch should be canceled.
			/// </summary>
			public bool Cancel
			{
				get
				{
					return this.cancel;
				}
				set
				{
					this.cancel = value;
				}
			}

			/// <summary>
			/// Gets or sets the index of the new page.
			/// </summary>
			public new int NewIndex
			{
				get
				{
					return base.newIndex;
				}
				set
				{
					base.newIndex = value;
				}
			}
			#endregion


		}
		#endregion

	}
}
