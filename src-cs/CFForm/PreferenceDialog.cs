using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CFForm
{
    public partial class PreferenceDialog : Form
    {
        private int colorErrorBitfield;
        private Font originalFont;
        public Font? currentFont;
        private FontDialog fontdFontDialog;
        public bool styleChanged = false;
        public PreferenceDialog()
        {
            InitializeComponent();

            switch ((Form1.StartAction)Properties.Settings.Default.StartAction)
            {
                default:
                case Form1.StartAction.Welcome:
                    radioOpenWelcome.Checked = true;
                    break;
                case Form1.StartAction.New:
                    radioOpenNew.Checked = true;
                    break;
                case Form1.StartAction.Nothing:
                    radioOpenNothing.Checked = true; 
                    break;
            }
            checkOpenRender.Checked = Properties.Settings.Default.OpenRender;
            checkRenderUpdate.Checked = Properties.Settings.Default.ProgressiveRender;
            checkSaveWithVariation.Checked = Properties.Settings.Default.ImageAppendVariation;
            checkCropImage.Checked = Properties.Settings.Default.ImageCrop;
            int quality = Properties.Settings.Default.JPEGQuality;
            if (quality < 1 || quality > 100)
                quality = 90;
            editJPEGquality.Text = quality.ToString();
            double border = Properties.Settings.Default.BorderWidth;
            if (border < -1.0 || border > 2.0)
                border = 2.0;
            trackBarBorder.Value = (int)((border + 1.0) * 33.0);
            originalFont = Properties.Settings.Default.EditorFont;
            updateFontName(originalFont);
            fontdFontDialog = new FontDialog();
            fontdFontDialog.Font = originalFont;
            int tabwidth = Properties.Settings.Default.TabWidth;
            if (tabwidth < 1 || tabwidth > 8)
                tabwidth = 4;
            numericTabWidth.Value = tabwidth;

            defaultBold.Checked = Properties.Settings.Default.StyleDefaultBold;
            defaultItalic.Checked = Properties.Settings.Default.StyleDefaultItalic;
            defaultColor.Text = Properties.Settings.Default.StyleDefaultColor;

            commentBold.Checked = Properties.Settings.Default.StyleCommentsBold;
            commentItalic.Checked = Properties.Settings.Default.StyleCommentsItalic;
            commentColor.Text = Properties.Settings.Default.StyleCommentsColor;

            symbolBold.Checked = Properties.Settings.Default.StyleSymbolsBold;
            symbolItalic.Checked = Properties.Settings.Default.StyleSymbolsItalic;
            symbolColor.Text = Properties.Settings.Default.StyleSymbolsColor;

            identifierBold.Checked = Properties.Settings.Default.StyleIdentifiersBold;
            identifierItalic.Checked = Properties.Settings.Default.StyleIdentifiersItalic;
            identifierColor.Text = Properties.Settings.Default.StyleIdentifiersColor;

            keywordBold.Checked = Properties.Settings.Default.StyleKeywordsBold;
            keywordItalic.Checked = Properties.Settings.Default.StyleKeywordsItalic;
            keywordColor.Text = Properties.Settings.Default.StyleKeywordsColor;

            builtinBold.Checked = Properties.Settings.Default.StyleBuiltinsBold;
            builtinItalic.Checked = Properties.Settings.Default.StyleBuiltinsItalic;
            builtinColor.Text = Properties.Settings.Default.StyleBuiltinsColor;

            filenameBold.Checked = Properties.Settings.Default.StyleStringsBold;
            filenameItalic.Checked = Properties.Settings.Default.StyleStringsItalic;
            filenameColor.Text = Properties.Settings.Default.StyleStringsColor;

            numberBold.Checked = Properties.Settings.Default.StyleNumbersBold;
            numberItalic.Checked = Properties.Settings.Default.StyleNumbersItalic;
            numberColor.Text = Properties.Settings.Default.StyleNumbersColor;
        }

        private void updateFontName(Font font)
        {
            fontDisplay.Font = font;
            fontDisplay.Text = String.Format("{0} {1}", font.Name, font.SizeInPoints);
        }
        private void colorChanged(object sender, EventArgs e)
        {
            TextBox? colorBox = sender as TextBox;
            if (colorBox == null)
                return;
            string? colorMaskStr = colorBox.Tag as string;
            if (!int.TryParse(colorMaskStr, out int colorMask))
                return;
            Color backColor = Color.Transparent;
            try {
                Color c = ColorTranslator.FromHtml(colorBox.Text);
                styleChanged = true;
                colorErrorBitfield = colorErrorBitfield & ~colorMask;
            } catch {
                backColor = Color.DarkRed;
                colorErrorBitfield = colorErrorBitfield | colorMask;
            }

            switch (colorMask)
            {
                case 1:
                    defaultStyle.BackColor = backColor;
                    break;
                case 2:
                    commentStyle.BackColor = backColor;
                    break;
                case 4:
                    symbolStyle.BackColor = backColor;
                    break;
                case 8:
                    identifierStyle.BackColor = backColor;
                    break;
                case 16:
                    keywordStyle.BackColor = backColor;
                    break;
                case 32:
                    builtinStyle.BackColor = backColor;
                    break;
                case 64:
                    filenameStyle.BackColor = backColor;
                    break;
                case 128:
                    numberStyle.BackColor = backColor;
                    break;
                default:
                    break;
            }
            buttonOK.Enabled = colorErrorBitfield == 0;
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            if (radioOpenWelcome.Checked) Properties.Settings.Default.StartAction = 0;
            if (radioOpenNew.Checked) Properties.Settings.Default.StartAction = 1;
            if (radioOpenNothing.Checked) Properties.Settings.Default.StartAction = 2;
            Properties.Settings.Default.OpenRender = checkOpenRender.Checked;
            Properties.Settings.Default.ProgressiveRender = checkRenderUpdate.Checked;
            Properties.Settings.Default.ImageAppendVariation = checkSaveWithVariation.Checked;
            Properties.Settings.Default.ImageCrop = checkCropImage.Checked;
            try
            {
                int quality = Convert.ToInt32(editJPEGquality.Text);
                if (quality < 1 || quality > 100)
                    quality = 90;
                Properties.Settings.Default.JPEGQuality = quality;
            } catch { }
            Properties.Settings.Default.BorderWidth = (double)(trackBarBorder.Value) / 33.0 - 1.0;
            if (currentFont != null)
                Properties.Settings.Default.EditorFont = currentFont;
            try {
                Properties.Settings.Default.TabWidth = Decimal.ToInt32(numericTabWidth.Value);
            }
            catch { }

            Properties.Settings.Default.StyleDefaultBold = defaultBold.Checked;
            Properties.Settings.Default.StyleDefaultItalic = defaultItalic.Checked;
            Properties.Settings.Default.StyleDefaultColor = defaultColor.Text;

            Properties.Settings.Default.StyleCommentsBold = commentBold.Checked;
            Properties.Settings.Default.StyleCommentsItalic = commentItalic.Checked;
            Properties.Settings.Default.StyleCommentsColor = commentColor.Text;

            Properties.Settings.Default.StyleSymbolsBold = symbolBold.Checked;
            Properties.Settings.Default.StyleSymbolsItalic = symbolItalic.Checked;
            Properties.Settings.Default.StyleSymbolsColor = symbolColor.Text;

            Properties.Settings.Default.StyleIdentifiersBold = identifierBold.Checked;
            Properties.Settings.Default.StyleIdentifiersItalic = identifierItalic.Checked;
            Properties.Settings.Default.StyleIdentifiersColor = identifierColor.Text;

            Properties.Settings.Default.StyleKeywordsBold = keywordBold.Checked;
            Properties.Settings.Default.StyleKeywordsItalic = keywordItalic.Checked;
            Properties.Settings.Default.StyleKeywordsColor = keywordColor.Text;

            Properties.Settings.Default.StyleBuiltinsBold = builtinBold.Checked;
            Properties.Settings.Default.StyleBuiltinsItalic = builtinItalic.Checked;
            Properties.Settings.Default.StyleBuiltinsColor = builtinColor.Text;

            Properties.Settings.Default.StyleStringsBold = filenameBold.Checked;
            Properties.Settings.Default.StyleStringsItalic = filenameItalic.Checked;
            Properties.Settings.Default.StyleStringsColor = filenameColor.Text;

            Properties.Settings.Default.StyleNumbersBold = numberBold.Checked;
            Properties.Settings.Default.StyleNumbersItalic = numberItalic.Checked;
            Properties.Settings.Default.StyleNumbersColor = numberColor.Text;

            Properties.Settings.Default.Save();
            this.Close();
        }

        private void fontChange_Click(object sender, EventArgs e)
        {
            if (fontdFontDialog.ShowDialog(this) != DialogResult.Cancel)
            {
                currentFont = fontdFontDialog.Font;
                updateFontName(currentFont);
            }
        }

        private void editorStyleChanged(object sender, EventArgs e)
        {
            styleChanged = true;
        }
    }
}
