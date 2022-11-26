using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Media;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CFForm
{
    public partial class RenderSizeDialog : Form
    {
        public RenderSizeDialog()
        {
            InitializeComponent();

            widthBox.Text = Properties.Settings.Default.RenderWidth.ToString();
            heightBox.Text = Properties.Settings.Default.RenderHeight.ToString();
            minSize = Properties.Settings.Default.MinimumSize;
            minimumSizeBox.Text = minSize.ToString();
            double border = Properties.Settings.Default.BorderWidth;
            if (border < -1.0 || border > 2.0)
                border = 2.0;
            trackBarBorder.Value = (int)((border + 1.0) * 33.0);
            noDisplayCheckBox.Checked = Properties.Settings.Default.SuppressDisplay;
        }

        private double minSize = 0.0;

        private void validFloat(object sender, CancelEventArgs e)
        {
            TextBox? box = sender as TextBox;
            if (box != null) {
                if (box.Text == String.Empty || box.Text == ".") {
                    minSize = 0.0;
                    return;
                }
                if (Double.TryParse(box.Text, out double m)) {
                    minSize = m;
                } else {
                    e.Cancel = true;
                    SystemSounds.Asterisk.Play();
                }
            }
        }

        private void OKbuttonClick(object sender, EventArgs e)
        {
            try {
                Properties.Settings.Default.RenderWidth = Int32.Parse(widthBox.Text);
                Properties.Settings.Default.RenderHeight = Int32.Parse(heightBox.Text);
                Properties.Settings.Default.BorderWidth = (double)(trackBarBorder.Value) / 33.0 - 1.0;
                if (minSize <= 0.0)
                    minSize = 0.3;
                Properties.Settings.Default.MinimumSize = minSize;
                Properties.Settings.Default.SuppressDisplay = noDisplayCheckBox.Checked;
                DialogResult = DialogResult.OK;
            } catch {
                DialogResult = DialogResult.Cancel;
                SystemSounds.Beep.Play();
            }
        }

        private void cancelButtonClick(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
        }
    }
}
