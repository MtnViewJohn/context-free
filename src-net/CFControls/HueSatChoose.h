// HueSatChoose.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 John Horigan - john@glyphic.com
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

namespace CFControls {

	/// <summary>
	/// Summary for HueSatChoose
	/// </summary>
	public ref class HueSatChoose : public System::Windows::Forms::Control
	{
	public:
		HueSatChoose(void) : myColor(0.0, 0.0, 0.0)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
            MoreInitialization();
		}

        event ColorChangeEventHandler^ ColorChange;

        property double Hue {
            double get() { return myColor.Hue; }
            void set(double v) { myColor.Hue = v; calcMarkerRect(); }
        }
        property double Sat {
            double get() { return myColor.Sat; }
            void set(double v) { myColor.Sat = v; calcMarkerRect(); }
        }
        property double Bright {
            double get() { return myColor.Bright; }
            void set(double v) { myColor.Bright = v; Invalidate(); }
        }
        property hsbColor CurrentColor {
            hsbColor get() { return myColor; }
            void set(hsbColor c) { 
                myColor = c; 
                calcMarkerRect(); 
                Invalidate(); 
            }
        }

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~HueSatChoose()
		{
			if (components)
			{
				delete components;
			}
		}

        void OnColorChange(ColorChangeEventArgs^ e);

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
        System::Drawing::Bitmap^ colorWheel;
        System::Drawing::Drawing2D::GraphicsPath^ clipPath;
        System::Drawing::Rectangle focusRect;
        System::Drawing::Point colorCenter;
        System::Drawing::Pen^ focusPen;
        System::Drawing::Rectangle markerRect;
        System::Drawing::Pen^ markerPen;
        static const int markerSize = 3;
		System::ComponentModel::Container ^components;
        double radius;
        hsbColor myColor;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->SuspendLayout();
            // 
            // HueSatChoose
            // 
            //this->AutoScaleDimensions = System::Drawing::SizeF(256, 256);
            //this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->Name = L"HueSatChoose";
            this->ResumeLayout(false);

        }
#pragma endregion
    protected:
        virtual bool IsInputKey (System::Windows::Forms::Keys keyData) override;

    private:
        System::Void resizeHandler(System::Object^ sender, System::EventArgs^ e);
        void initForSize();
        System::Void initForColors(System::Object^ sender, System::EventArgs^ e);
        double Distance(System::Drawing::Point pt1);
        double AngleFromPoint(System::Drawing::Point pt);
        System::Drawing::Point PointFromAngle(double angle, double sat);
        void calcMarkerRect();
        System::Void mouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
        System::Void mouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
        System::Void mouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
        System::Void paintMe(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
        System::Void focusHandler(System::Object^ sender, System::EventArgs^ e);
        System::Void arrowHandler(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
    private: void MoreInitialization();
	};
}
