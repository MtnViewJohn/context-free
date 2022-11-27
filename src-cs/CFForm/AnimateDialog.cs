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
    public partial class AnimateDialog : Form
    {
        private double minSize = 0.3;
        private CppWrapper.RenderParameters prefs;
        public AnimateDialog(CppWrapper.RenderParameters rp)
        {
            InitializeComponent();
            errorMessage.ForeColor = Color.Red;
            this.prefs = rp;
            if (prefs.animateFrame) {
                Text = "Animate a Frame";
                formatComboBox.Visible = false;
                formatLabel.Visible = false;
                int frame = prefs.frame;
                if (frame > 0)
                    frameTextBox.Text = frame.ToString();
                else
                    frameTextBox.Text = "1";
            } else {
                frameLabel.Visible = false;
                frameTextBox.Visible = false;
                int codec = prefs.codec;
                if (codec >= 0 && codec < formatComboBox.Items.Count) {
                    formatComboBox.SelectedIndex = codec;
                } else {
                    formatComboBox.SelectedIndex = 0;
                }
            }
            widthTextBox.Text = prefs.animateWidth.ToString();
            heightTextBox.Text = prefs.animateHeight.ToString();
            minSize = prefs.minimumSize;
            if (minSize <= 0.0) minSize = 0.3;
            minSizeTextBox.Text = minSize.ToString();
            double border = prefs.borderSize;
            if (border < -1.0 || border > 2.0)
                border = 2.0;
            trackBarBorder.Value = (int)((border + 1.0) * 33.0);
            zoomCheckBox.Checked = prefs.animateZoom;
            int length = prefs.length;
            if (length < 1) length = 1;
            lengthTextBox.Text = length.ToString();
            double frameRate = prefs.frameRate;
            if (frameRate < 8.0) frameRate = 15.0;
            for (int i = 0; i < frameRateBox.Items.Count; i++) {
                if (double.Parse(frameRateBox.Items[i].ToString()) == frameRate) {
                    frameRateBox.SelectedIndex = i;
                    break;
                }
            }
            if (frameRateBox.SelectedIndex == -1)
                frameRateBox.SelectedIndex = 4;         // default to 15fps
        }

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

        private void okCLick(object sender, EventArgs e)
        {
            try {
                int width = int.Parse(widthTextBox.Text);
                if (width < 8) throw new ArgumentException("Width is too small.");
                prefs.animateWidth = width;

                int height = int.Parse(heightTextBox.Text);
                if (height < 8) throw new ArgumentException("Height is too small.");
                prefs.animateHeight = height;

                if ((width & 7) != 0 || (height & 7) != 0)
                    throw new ArgumentException("Dimensions must be multiple of 8.");

                minSize = double.Parse(minSizeTextBox.Text);
                if (minSize <= 0.0) minSize = 0.3;
                prefs.minimumSize = minSize;

                prefs.borderSize = (double)(trackBarBorder.Value) / 33.0 - 1.0;

                int length = int.Parse(lengthTextBox.Text);
                if (length < 1) throw new ArgumentException("Length must be positive number.");
                prefs.length = length;

                double frameRate = double.Parse(frameRateBox.Items[frameRateBox.SelectedIndex].ToString());
                prefs.frameRate = frameRate;

                int count = (int)(length * frameRate);
                if (prefs.animateFrame) {
                    int frame = int.Parse(frameTextBox.Text);
                    if (frame < 1 || frame > count) throw new ArgumentException("Frame number out of range.");
                    prefs.frame = frame;
                    prefs.animateFrameCount = count;
                } else {
                    prefs.codec = frameRateBox.SelectedIndex;
                    if (prefs.frame < 1 || prefs.frame > count)
                        prefs.frame = 1;
                }

                DialogResult = DialogResult.OK;
            } catch (ArgumentException ae) {
                errorMessage.Text = ae.Message;
                SystemSounds.Asterisk.Play();
            } catch (FormatException) {
                errorMessage.Text = "Incorrect numeric format.";
                SystemSounds.Asterisk.Play();
            } catch {
                DialogResult = DialogResult.Cancel;
                SystemSounds.Asterisk.Play();
            }
        }

        private void cancelClick(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
        }
    }
}
