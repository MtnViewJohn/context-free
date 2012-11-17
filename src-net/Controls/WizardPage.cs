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
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using System.Windows.Forms.Design;
#endregion

namespace CristiPotlog.Controls
{

	#region Enums
	/// <summary>
	/// Represents possible styles of a wizard page.
	/// </summary>
	public enum WizardPageStyle
	{
		/// <summary>
		/// Represents a standard interior wizard page with a white banner at the top.
		/// </summary>
		Standard,
		/// <summary>
		/// Represents a welcome wizard page with white background and large logo on the left.
		/// </summary>
		Welcome,
		/// <summary>
		/// Represents a finish wizard page with white background,
		/// a large logo on the left and OK button.
		/// </summary>
		Finish,
		/// <summary>
		/// Represents a blank wizard page.
		/// </summary>
		Custom
	}
	#endregion

	/// <summary>
	/// Represents a wizard page control with basic layout functionality.
	/// </summary>
	[DefaultEvent("Click")]
	[Designer(typeof(WizardPage.WizardPageDesigner))]
	public class WizardPage : Panel
	{
		#region Consts
		private const int HEADER_AREA_HEIGHT = 64;
		private const int HEADER_GLYPH_SIZE = 48;
		private const int HEADER_TEXT_PADDING = 8;
		private const int WELCOME_GLYPH_WIDTH = 164;
		#endregion

		#region Fields
		private WizardPageStyle style = WizardPageStyle.Standard;
		private string title = String.Empty;
		private string description = String.Empty;
		#endregion

		#region Constructor
		/// <summary>
		/// Creates a new instance of the <see cref="WizardPage"/> class.
		/// </summary>
		public WizardPage()
		{
			// reset control style to improove rendering (reduce flicker)
			base.SetStyle(ControlStyles.AllPaintingInWmPaint, true); 
			base.SetStyle(ControlStyles.DoubleBuffer, true);
			base.SetStyle(ControlStyles.ResizeRedraw, true);
			base.SetStyle(ControlStyles.UserPaint, true);
		}
		#endregion

		#region Properties
		/// <summary>
		/// Gets or sets the style of the wizard page.
		/// </summary>
		[DefaultValue(WizardPageStyle.Standard)]
		[Category("Wizard")]
		[Description("Gets or sets the style of the wizard page.")]
		public WizardPageStyle Style
		{
			get
			{
				return this.style;
			}
			set
			{
				if (this.style != value)
				{
					this.style = value;
					// get the parent wizard control
					if (this.Parent != null && this.Parent is Wizard)
					{
						Wizard parentWizard = (Wizard)this.Parent;
						// check if page is selected
						if (parentWizard.SelectedPage == this)
						{
							// reactivate the selected page (performs redraw too)
							parentWizard.SelectedPage = this;
						}
					}
					else
					{
						// just redraw the page
						this.Invalidate();
					}
				}
			}
		}

		/// <summary>
		/// Gets or sets the title of the wizard page.
		/// </summary>
		[DefaultValue("")]
		[Category("Wizard")]
		[Description("Gets or sets the title of the wizard page.")]
		public string Title
		{
			get
			{
				return this.title;
			}
			set
			{
				if (value == null)
				{
					value = String.Empty;
				}
				if (this.title != value)
				{
					this.title = value;
					this.Invalidate();
				}
			}
		}
		
		/// <summary>
		/// Gets or sets the description of the wizard page.
		/// </summary>
		[DefaultValue("")]
		[Category("Wizard")]
		[Description("Gets or sets the description of the wizard page.")]
		public string Description
		{
			get
			{
				return this.description;
			}
			set
			{
				if (value == null)
				{
					value = String.Empty;
				}
				if (this.description != value)
				{
					this.description = value;
					this.Invalidate();
				}
			}
		}
		#endregion

		#region Methods
		/// <summary>
		/// Provides custom drawing to the wizard page.
		/// </summary>
		protected override void OnPaint(PaintEventArgs e)
		{
			// raise paint event
			base.OnPaint(e);

			// check if custom style
			if (this.style == WizardPageStyle.Custom)
			{
				// filter out
				return;
			}

			// init graphic resources
			Rectangle headerRect = this.ClientRectangle;
			Rectangle glyphRect = Rectangle.Empty;
			Rectangle titleRect = Rectangle.Empty;
			Rectangle descriptionRect = Rectangle.Empty;

			// determine text format
			StringFormat textFormat = StringFormat.GenericDefault;
			textFormat.LineAlignment = StringAlignment.Near;
			textFormat.Alignment = StringAlignment.Near;
			textFormat.Trimming = StringTrimming.EllipsisCharacter;

			switch (this.style)
			{
				case WizardPageStyle.Standard:
					// adjust height for header
					headerRect.Height = HEADER_AREA_HEIGHT;
					// draw header border
					ControlPaint.DrawBorder3D(e.Graphics, headerRect, Border3DStyle.Etched, Border3DSide.Bottom);
					// adjust header rect not to overwrite the border
					headerRect.Height -= SystemInformation.Border3DSize.Height;
					// fill header with window color
					e.Graphics.FillRectangle(SystemBrushes.Window, headerRect);

					// determine header image regtangle
					int headerPadding = (int)Math.Floor(((double)HEADER_AREA_HEIGHT - HEADER_GLYPH_SIZE) / 2);
					glyphRect.Location = new Point(this.Width - HEADER_GLYPH_SIZE - headerPadding, headerPadding);
					glyphRect.Size = new Size(HEADER_GLYPH_SIZE, HEADER_GLYPH_SIZE);

					// determine the header content
					Image headerImage = null;
					Font headerFont = this.Font;
					Font headerTitleFont = this.Font;
					if (this.Parent != null && this.Parent is Wizard)
					{
						// get content from parent wizard, if exists
						Wizard parentWizard = (Wizard)this.Parent;
						headerImage = parentWizard.HeaderImage;
						headerFont = parentWizard.HeaderFont;
						headerTitleFont = parentWizard.HeaderTitleFont;
					}

					// check if we have an image
					if (headerImage == null)
					{
						// display a focus rect as a place holder
						ControlPaint.DrawFocusRectangle(e.Graphics, glyphRect);
					}
					else
					{
						// draw header image
						e.Graphics.DrawImage(headerImage, glyphRect);
					}

					// determine title height
					int headerTitleHeight = (int)Math.Ceiling(e.Graphics.MeasureString(this.title, headerTitleFont, 0, textFormat).Height);

					// calculate text sizes
					titleRect.Location = new Point(HEADER_TEXT_PADDING,
													HEADER_TEXT_PADDING);
					titleRect.Size = new Size(glyphRect.Left - HEADER_TEXT_PADDING,
												headerTitleHeight);
					descriptionRect.Location = titleRect.Location;
					descriptionRect.Y += headerTitleHeight + HEADER_TEXT_PADDING / 2;
					descriptionRect.Size = new Size(titleRect.Width,
													HEADER_AREA_HEIGHT - descriptionRect.Y);

					// draw tilte text (single line, truncated with ellipsis)
					e.Graphics.DrawString(this.title,
											headerTitleFont,
											SystemBrushes.WindowText,
											titleRect,
											textFormat);
					// draw description text (multiple lines if needed)
					e.Graphics.DrawString(this.description,
											headerFont,
											SystemBrushes.WindowText,
											descriptionRect,
											textFormat);					
					break;
				case WizardPageStyle.Welcome:
				case WizardPageStyle.Finish:
					// fill whole page with window color
					e.Graphics.FillRectangle(SystemBrushes.Window, headerRect);

					// determine welcome image regtangle
					glyphRect.Location = Point.Empty;
					glyphRect.Size = new Size(WELCOME_GLYPH_WIDTH, this.Height);

					// determine the icon that should appear on the welcome page
					Image welcomeImage = null;
					Font welcomeFont = this.Font;
					Font welcomeTitleFont = this.Font;
					if (this.Parent != null && this.Parent is Wizard)
					{
						// get content from parent wizard, if exists
						Wizard parentWizard = (Wizard)this.Parent;
						welcomeImage = parentWizard.WelcomeImage;
						welcomeFont = parentWizard.WelcomeFont;
						welcomeTitleFont = parentWizard.WelcomeTitleFont;
					}

					// check if we have an image
					if (welcomeImage == null)
					{
						// display a focus rect as a place holder
						ControlPaint.DrawFocusRectangle(e.Graphics, glyphRect);
					}
					else
					{
						// draw welcome page image
						e.Graphics.DrawImage(welcomeImage, glyphRect);
					}

					// calculate text sizes
					titleRect.Location = new Point(WELCOME_GLYPH_WIDTH + HEADER_TEXT_PADDING,
													HEADER_TEXT_PADDING);
					titleRect.Width = this.Width - titleRect.Left - HEADER_TEXT_PADDING;
					// determine title height
					int welcomeTitleHeight = (int)Math.Ceiling(e.Graphics.MeasureString(this.title, welcomeTitleFont, titleRect.Width, textFormat).Height);
					descriptionRect.Location = titleRect.Location;
					descriptionRect.Y += welcomeTitleHeight + HEADER_TEXT_PADDING;
					descriptionRect.Size = new Size(this.Width - descriptionRect.Left - HEADER_TEXT_PADDING,
													this.Height - descriptionRect.Y);

					// draw tilte text (multiple lines if needed)
					e.Graphics.DrawString(this.title,
											welcomeTitleFont,
											SystemBrushes.WindowText,
											titleRect,
											textFormat);
					// draw description text (multiple lines if needed)
					e.Graphics.DrawString(this.description,
											welcomeFont,
											SystemBrushes.WindowText,
											descriptionRect,
											textFormat);
					break;
			}
		}
		#endregion

		#region Inner classes
		/// <summary>
		/// This is a designer for the Banner.
		/// This designer locks the control vertical sizing.
		/// </summary>
		internal class WizardPageDesigner : ParentControlDesigner 
		{
			/// <summary>
			/// Gets the selection rules that indicate the movement capabilities of a component.
			/// </summary>
			public override SelectionRules SelectionRules 
			{
				get
				{
					// lock the control
					return SelectionRules.Visible | SelectionRules.Locked;
				}
			}
		}
		#endregion
	}
}
