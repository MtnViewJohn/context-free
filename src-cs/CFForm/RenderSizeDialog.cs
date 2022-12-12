// RenderSizeDialog.cs
// this file is part of Context Free
// ---------------------
// Copyright (C) 2022 John Horigan - john@glyphic.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//


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

        private void ValidFloat(object sender, CancelEventArgs e)
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

        private void CancelButtonClick(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
        }

        private void NumberKeyPress(object sender, KeyPressEventArgs e)
        {
            if (!Char.IsControl(e.KeyChar) && !Char.IsDigit(e.KeyChar))
                e.Handled = true;
        }
    }
}
