// ColorComponentChoose.h
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


#pragma once

#include "ColorChangeEventArgs.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace CppWrapper {

	/// <summary>
	/// Summary for ColorComponentChoose
	/// </summary>
    public ref class ColorComponentChoose : public System::Windows::Forms::Control
    {
    public:
        ColorComponentChoose(void) : myColor(0.0, 0.0, 0.0)
        {
            MoreInitialization();
        }

        event ColorChangeEventHandler^ ColorChange;

        property double Hue {
            double get() { return myColor.Hue; }
            void set(double v) { myColor.Hue = v; redrawChannel(); }
        }
        property double Sat {
            double get() { return myColor.Sat; }
            void set(double v) { myColor.Sat = v; redrawChannel(); }
        }
        property double Bright {
            double get() { return myColor.Bright; }
            void set(double v) { myColor.Bright = v; calcMarkerRect(); }
        }
        property hsbColorClr CurrentColor {
            hsbColorClr get() { return myColor; }
            void set(hsbColorClr c) { myColor = c; redrawChannel(); calcMarkerRect(); }
        }
        static const int minimumWidth = 15;

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~ColorComponentChoose()
        {
        }

        void OnColorChange(ColorChangeEventArgs^ e);

    private:
        System::Drawing::Bitmap^ colorChannel;
        System::Drawing::Rectangle colorRect;
        System::Drawing::Rectangle focusRect;
        System::Drawing::Pen^ focusPen;
        System::Drawing::Rectangle markerRect;
        System::Drawing::Pen^ markerPen;
        static const int markerSize = 3;
        hsbColorClr myColor;

    protected:
        virtual bool IsInputKey(System::Windows::Forms::Keys keyData) override;

    private:
        System::Void resizeHandler(System::Object^ sender, System::EventArgs^ e);
        void initForSize();
        System::Void initForColors(System::Object^ sender, System::EventArgs^ e);
        void calcMarkerRect();
        System::Void mouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
        System::Void mouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
        System::Void mouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
        System::Void paintMe(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
        System::Void focusHandler(System::Object^ sender, System::EventArgs^ e);
        System::Void arrowHandler(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
        void MoreInitialization();
        void redrawChannel();
    };
}
