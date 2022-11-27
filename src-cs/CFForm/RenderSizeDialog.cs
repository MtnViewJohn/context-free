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
using CppWrapper;

namespace CFForm
{
    public partial class RenderSizeDialog : Form
    {
        public RenderSizeDialog(CppWrapper.RenderParameters rp)
        {
            InitializeComponent();

            prefs = rp;
            widthBox.Text = prefs.width.ToString();
            heightBox.Text = prefs.height.ToString();
            minSize = prefs.minimumSize;
            minimumSizeBox.Text = minSize.ToString();
            double border = prefs.borderSize; ;
            if (border < -1.0 || border > 2.0)
                border = 2.0;
            trackBarBorder.Value = (int)((border + 1.0) * 33.0);
            noDisplayCheckBox.Checked = prefs.suppressDisplay;
        }

        private double minSize = 0.0;
        private CppWrapper.RenderParameters prefs;

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
                prefs.width = Int32.Parse(widthBox.Text);
                prefs.height = Int32.Parse(heightBox.Text);
                prefs.borderSize = (double)(trackBarBorder.Value) / 33.0 - 1.0;
                if (minSize <= 0.0)
                    minSize = 0.3;
                prefs.minimumSize = minSize;
                prefs.suppressDisplay = noDisplayCheckBox.Checked;
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
