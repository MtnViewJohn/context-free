// RGBChoose.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2008 John Horigan - john@glyphic.com
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
#include "RGBChoose.h"

using namespace CFControls;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

void RGBChoose::MoreInitialization()
{
    validNumber = gcnew System::Text::RegularExpressions::Regex("\\d*");

    EventHandler^ texter = gcnew EventHandler(this, &RGBChoose::textHandler);
    redBox->TextChanged += texter;
    greenBox->TextChanged += texter;
    blueBox->TextChanged += texter;

    ColorChangeEventHandler^ colorer = gcnew ColorChangeEventHandler(this, &RGBChoose::colorHandler);
    redBar->ColorChange += colorer;
    greenBar->ColorChange += colorer;
    blueBar->ColorChange += colorer;

    heightToBoxPos = this->Size.Height - redBox->Location.Y;
    heightToBarHeight = this->Size.Height - redBar->Size.Height;
    lockedWidth = this->Size.Width;

    SizeChanged += gcnew EventHandler(this, &RGBChoose::resizeHandler);
}

void RGBChoose::OnColorChange(ColorChangeEventArgs^ e)
{
    ColorChange(this, e);
}

void RGBChoose::updateMe(int which)
{
    if (which & 1) {
        redBar->Bright = (double)myColor.R / 255.0;
        redBox->Text = myColor.R.ToString();
    }

    if (which & 2) {
        greenBar->Bright = (double)myColor.G / 255.0;
        greenBox->Text = myColor.G.ToString();
    }

    if (which & 4) {
        blueBar->Bright = (double)myColor.B / 255.0;
        blueBox->Text = myColor.B.ToString();
    }
}

System::Void RGBChoose::resizeHandler(System::Object^ sender, System::EventArgs^ e)
{
    Control^ control = dynamic_cast<Control^>(sender);

    System::Drawing::Size newSize = control->Size;
    bool accept = true;

    if (newSize.Width != lockedWidth) {
        accept = false;
        newSize.Width = lockedWidth;
    }

    int barHeight = newSize.Height - heightToBarHeight;
    int boxPos = newSize.Height - heightToBoxPos;
    if (barHeight < 70) {
        accept = false;
        newSize.Height = 70 + heightToBarHeight;
    }

    if (accept) {
        SuspendLayout();
        redBox->Location = Point(redBox->Location.X, boxPos);
        redBar->Size = System::Drawing::Size(25, barHeight);
        greenBox->Location = Point(greenBox->Location.X, boxPos);
        greenBar->Size = System::Drawing::Size(25, barHeight);
        blueBox->Location = Point(blueBox->Location.X, boxPos);
        blueBar->Size = System::Drawing::Size(25, barHeight);
        ResumeLayout();
    } else {
        control->Size = newSize;    // generates another SizeChanged event
    }
}

System::Void RGBChoose::colorHandler(Object^ sender, ColorChangeEventArgs^ e)
{
    int number = (int)(e->newHSBColor.Bright * 255.0 + 0.5);
    String^ numberT = number.ToString();

    if (Object::ReferenceEquals(sender, redBar)) {
        myColor = System::Drawing::Color::FromArgb(myColor.A, 
            number, myColor.G, myColor.B); 
        redBox->Text = numberT;
    }

    if (Object::ReferenceEquals(sender, greenBar)) {
        myColor = System::Drawing::Color::FromArgb(myColor.A, 
            myColor.R, number, myColor.B); 
        greenBox->Text = numberT;
    }

    if (Object::ReferenceEquals(sender, blueBar)) {
        myColor = System::Drawing::Color::FromArgb(myColor.A, 
            myColor.R, myColor.G, number); 
        blueBox->Text = numberT;
    }

    OnColorChange(gcnew ColorChangeEventArgs(myColor));
}

System::Void RGBChoose::textHandler(System::Object^ sender, System::EventArgs^ e)
{
    TextBox^ box = cli::safe_cast<TextBox^>(sender);

    if (box == nullptr || !box->Focused) return;

    String^ numberT = box->Text;
    int number = 0;
    try {
        number = System::Int32::Parse(numberT, Globalization::NumberStyles::AllowLeadingWhite | Globalization::NumberStyles::AllowTrailingWhite);
    } catch (SystemException^) {
        number = 0;
        box->Text = L"0";
    }
    double numberD = (double)number / 255.0;
    bool accept = validNumber->IsMatch(numberT) && number >= 0 && number < 256;

    if (Object::ReferenceEquals(box, redBox)) {
        if (accept) {
            redBar->Bright = numberD;
            myColor = System::Drawing::Color::FromArgb(myColor.A, 
                number, myColor.G, myColor.B); 
        } else {
            redBox->Text = myColor.R.ToString();
        }
    }

    if (Object::ReferenceEquals(box, greenBox)) {
        if (accept) {
            greenBar->Bright = numberD;
            myColor = System::Drawing::Color::FromArgb(myColor.A, 
                myColor.R, number, myColor.B); 
        } else {
            greenBox->Text = myColor.G.ToString();
        }
    }

    if (Object::ReferenceEquals(box, blueBox)) {
        if (accept) {
            blueBar->Bright = numberD;
            myColor = System::Drawing::Color::FromArgb(myColor.A, 
                myColor.R, myColor.G, number); 
        } else {
            blueBox->Text = myColor.B.ToString();
        }
    }

    if (accept) {
        OnColorChange(gcnew ColorChangeEventArgs(myColor));
    } else {
        System::Media::SystemSounds::Beep->Play();
    }
}

