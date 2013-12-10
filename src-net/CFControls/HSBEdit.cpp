// HSBEdit.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2008-2013 John Horigan - john@glyphic.com
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

#include "StdAfx.h"
#include "HSBEdit.h"

using namespace CFControls;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

void HSBEdit::MoreInitialization()
{
    EventHandler^ texter = gcnew EventHandler(this, &HSBEdit::textHandler);
    hueBox->TextChanged += texter;
    satBox->TextChanged += texter;
    brightBox->TextChanged += texter;
}

System::Void HSBEdit::textHandler(System::Object^ sender, System::EventArgs^ e)
{
    TextBox^ box = cli::safe_cast<TextBox^>(sender);
    if (box == nullptr) return;

    String^ numberT = box->Text;
    double number;
    bool accept = true;
    try {
        number = System::Double::Parse(numberT, System::Globalization::NumberStyles::Float);
    } catch (FormatException^) {
        accept = false;
        number = 0.0;
    }

    if (Object::ReferenceEquals(sender, hueBox)) {
        if (accept) {
            myColor.Hue = number;
        } else {
            updateMe(1);
        }
    }

    double lowerBound = colorBox->Visible ? 0.0 : -1.0;
    // The delta HSB editor allows a -1 lower bound and is distinguished
    // by not having a visible colorBox.

    if (Object::ReferenceEquals(sender, satBox)) {
        if (accept && number >= lowerBound && number <= 1.0) {
            myColor.Sat = number;
        } else {
            accept = false;
            updateMe(2);
        }
    }

    if (Object::ReferenceEquals(sender, brightBox)) {
        if (accept && number >= lowerBound && number <= 1.0) {
            myColor.Bright = number;
        } else {
            accept = false;
            updateMe(4);
        }
    }

    if (accept) {
        // If the textBox has focus then it is the originator of the color change,
        // so it must propagate it to the rest of the color system. If it doesn't
        // have focus then some other color component originated the change, so
        // just accept it.
        if (box->Focused)
            OnColorChange(gcnew ColorChangeEventArgs(myColor));

        hsbBox->Text = "h " + hueBox->Text->Replace(',', '.') + 
                       " sat " + satBox->Text->Replace(',', '.') + 
                       " b " + brightBox->Text->Replace(',', '.');

        if (colorBox->Enabled) {
            colorBox->BackColor = myColor.GetColor();
        }
    }
}

void HSBEdit::updateMe(int which)
{
    if (which & 1) {
        hueBox->Text = myColor.Hue.ToString("F2");
    }

    if (which & 2) {
        satBox->Text = myColor.Sat.ToString("F4");
    }

    if (which & 4) {
        brightBox->Text = myColor.Bright.ToString("F4");
    }

    if (colorBox->Enabled) {
        colorBox->BackColor = myColor.GetColor();
    }
}

void HSBEdit::OnColorChange(ColorChangeEventArgs^ e)
{
    ColorChange(this, e);
}

