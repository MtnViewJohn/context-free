// HSBChoose.h
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

#include "HueSatChoose.h"
#include "ColorComponentChoose.h"
#include "ColorChangeEventArgs.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace CFControls {

	/// <summary>
	/// Summary for HSBChoose
	/// </summary>
	public ref class HSBChoose : public System::Windows::Forms::UserControl
	{
	public:
		HSBChoose(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
            MoreInitialization();
		}

        event ColorChangeEventHandler^ ColorChange;

        property double Hue {
            double get() { return hueSatChooser->Hue; }
            void set(double v) { hueSatChooser->Hue = v; brightChooser->Hue = v; }
        }
        property double Sat {
            double get() { return hueSatChooser->Sat; }
            void set(double v) { hueSatChooser->Sat = v; brightChooser->Sat = v; }
        }
        property double Bright {
            double get() { return hueSatChooser->Bright; }
            void set(double v) { hueSatChooser->Bright = v; brightChooser->Bright = v; }
        }
        property hsbColor CurrentColor {
            hsbColor get() { return hueSatChooser->CurrentColor; }
            void set(hsbColor c) { hueSatChooser->CurrentColor = c; brightChooser->CurrentColor = c; }
        }

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~HSBChoose()
		{
			if (components)
			{
				delete components;
			}
		}

        void OnColorChange(ColorChangeEventArgs^ e);

    private: CFControls::HueSatChoose^  hueSatChooser;
    protected: 
    private: CFControls::ColorComponentChoose^  brightChooser;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->brightChooser = (gcnew CFControls::ColorComponentChoose());
            this->hueSatChooser = (gcnew CFControls::HueSatChoose());
            this->SuspendLayout();
            // 
            // brightChooser
            // 
            this->brightChooser->Bright = 0;
            this->brightChooser->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
            this->brightChooser->Hue = 0;
            this->brightChooser->Location = System::Drawing::Point(192, 3);
            this->brightChooser->Name = L"brightChooser";
            this->brightChooser->Sat = 0;
            this->brightChooser->Size = System::Drawing::Size(29, 183);
            this->brightChooser->TabIndex = 1;
            this->brightChooser->Text = L"colorComponentChoose1";
            // 
            // hueSatChooser
            // 
            this->hueSatChooser->Bright = 1;
            this->hueSatChooser->Hue = 0;
            this->hueSatChooser->Location = System::Drawing::Point(3, 3);
            this->hueSatChooser->Name = L"hueSatChooser";
            this->hueSatChooser->Sat = 0;
            this->hueSatChooser->Size = System::Drawing::Size(183, 183);
            this->hueSatChooser->TabIndex = 0;
            this->hueSatChooser->Text = L"hueSatChooser";
            // 
            // HSBChoose
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->Controls->Add(this->brightChooser);
            this->Controls->Add(this->hueSatChooser);
            this->Name = L"HSBChoose";
            this->Size = System::Drawing::Size(224, 189);
            this->ResumeLayout(false);

        }
#pragma endregion
        System::Void resizeHandler(System::Object^ sender, System::EventArgs^ e);
        void MoreInitialization();
        System::Void colorHandler(System::Object^ sender, ColorChangeEventArgs^ e);
	};
}
