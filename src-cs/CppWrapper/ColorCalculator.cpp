// ColorCalculator.cpp
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

#include "pch.h"
#include "ColorCalculator.h"
#include "TrackPoint.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Reflection;

namespace CppWrapper {
    void ColorCalculator::MoreInitialization()
    {
        ColorChangeEventHandler^ chooser =
            gcnew ColorChangeEventHandler(this, &ColorCalculator::chooserHandler);
        rgbChooser->ColorChange += chooser;
        hsbChooser->ColorChange += chooser;

        ColorChangeEventHandler^ editor =
            gcnew ColorChangeEventHandler(this, &ColorCalculator::editorHandler);
        startEditor->ColorChange += editor;
        deltaEditor->ColorChange += editor;
        endEditor->ColorChange += editor;

        this->HandleCreated += gcnew EventHandler(this, &ColorCalculator::handleHandler);

        dropperButton->Cursor = gcnew System::Windows::Forms::Cursor(
            Assembly::GetExecutingAssembly()->GetManifestResourceStream("dropper.cur"));
    }

    System::Void ColorCalculator::handleHandler(System::Object^ sender, System::EventArgs^ e)
    {
        startEditor->CurrentColor = CppWrapper::hsbColorClr(Color::Black);
        endEditor->CurrentColor = CppWrapper::hsbColorClr(Color::White);
        calcDelta();

        buttonHandler(endButton, nullptr);
    }

    System::Void ColorCalculator::chooserHandler(System::Object^ sender, CppWrapper::ColorChangeEventArgs^ e)
    {
        if (e->changedColorSpace == ColorChangeEventArgs::ColorSpace::HSB) {
            e->newRGBColor = e->newHSBColor.GetColor();
        }
        else {
            e->newHSBColor = CppWrapper::hsbColorClr(e->newRGBColor);
        }

        if (!Object::ReferenceEquals(sender, hsbChooser)) {
            hsbChooser->CurrentColor = e->newHSBColor;
        }

        if (!Object::ReferenceEquals(sender, rgbChooser)) {
            rgbChooser->CurrentColor = e->newRGBColor;
        }

        if (startSelected) {
            startEditor->CurrentColor = e->newHSBColor;
        }
        else {
            endEditor->CurrentColor = e->newHSBColor;
        }
        calcDelta();
    }

    System::Void ColorCalculator::editorHandler(Object^ sender, ColorChangeEventArgs^ e)
    {
        CppWrapper::hsbColorClr newColor;
        bool changeChooser = false;

        if (Object::ReferenceEquals(sender, startEditor)) {
            calcDelta();
            if (startSelected) {
                newColor = e->newHSBColor;
                changeChooser = true;
            }
        }

        if (Object::ReferenceEquals(sender, endEditor)) {
            calcDelta();
            if (!startSelected) {
                newColor = e->newHSBColor;
                changeChooser = true;
            }
        }

        if (Object::ReferenceEquals(sender, deltaEditor)) {
            calcEnd();
            if (!startSelected) {
                newColor = endEditor->CurrentColor;
                changeChooser = true;
            }
        }

        if (changeChooser) {
            hsbChooser->CurrentColor = newColor;
            rgbChooser->CurrentColor = newColor.GetColor();
        }
    }

    System::Void ColorCalculator::stepCount_ValueChanged(System::Object^ sender, System::EventArgs^ e)
    {
        calcDelta();
    }

    System::Void ColorCalculator::buttonHandler(Object^ sender, EventArgs^ e)
    {
        CppWrapper::hsbColorClr newColor;
        hsbChooser->Focus();

        if (Object::ReferenceEquals(sender, startButton)) {
            startEditor->BackColor = SystemColors::Control;
            endEditor->BackColor = SystemColors::ControlLightLight;
            newColor = startEditor->CurrentColor;
            startSelected = true;
        } else {
            endEditor->BackColor = SystemColors::Control;
            startEditor->BackColor = SystemColors::ControlLightLight;
            newColor = endEditor->CurrentColor;
            startSelected = false;
        }

        hsbChooser->CurrentColor = newColor;
        rgbChooser->CurrentColor = newColor.GetColor();
    }

    void ColorCalculator::calcDelta()
    {
        deltaEditor->CurrentColor =
            endEditor->CurrentColor.getAdjustmentFrom(startEditor->CurrentColor,
                Decimal::ToUInt32(stepCount->Value));
    }

    void ColorCalculator::calcEnd()
    {
        endEditor->CurrentColor = startEditor->CurrentColor;
        unsigned int n = Decimal::ToUInt32(stepCount->Value);
        for (unsigned int i = 0; i < n; ++i)
            endEditor->CurrentColor.adjustWith(deltaEditor->CurrentColor);
    }

    System::Void ColorCalculator::dropperMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        if (dropperButton->Capture) {
            unsigned int argb = ::TrackPoint();
            Color c = Color::FromArgb(argb);
            chooserHandler(dropperButton, gcnew ColorChangeEventArgs(c));
        }
    }

    System::Void ColorCalculator::hideForm(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
    {
        if (e->CloseReason == CloseReason::UserClosing) {
            e->Cancel = true;
            this->Hide();
        }
    }

    System::Void ColorCalculator::swapColorsClick(System::Object^ sender, System::EventArgs^ e)
    {
        auto t = startEditor->CurrentColor;
        startEditor->CurrentColor = endEditor->CurrentColor;
        endEditor->CurrentColor = t;

        hsbColorClr newColor = startSelected ? startEditor->CurrentColor : endEditor->CurrentColor;
        hsbChooser->CurrentColor = newColor;
        rgbChooser->CurrentColor = newColor.GetColor();
    }
}
