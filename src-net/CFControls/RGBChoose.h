// RGBChoose.h
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
#include "ColorComponentChoose.h"

namespace CFControls {

	/// <summary>
	/// Summary for RGBChoose
	/// </summary>
	public ref class RGBChoose : public System::Windows::Forms::UserControl
	{
	public:
        RGBChoose(void) : myColor(System::Drawing::Color::Black)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
            MoreInitialization();
		}

        event ColorChangeEventHandler^ ColorChange;

        property int Red {
            int get() { return myColor.R; }
            void set(int v) { 
                myColor = System::Drawing::Color::FromArgb(myColor.A, 
                    v, 
                    myColor.G, 
                    myColor.B); 
                updateMe(1); 
            }
        }
        property int Green {
            int get() { return myColor.G; }
            void set(int v) { 
                myColor = System::Drawing::Color::FromArgb(myColor.A, 
                    myColor.R, 
                    v, 
                    myColor.B); 
                updateMe(2); 
            }
        }
        property int Blue {
            int get() { return myColor.B; }
            void set(int v) { 
                myColor = System::Drawing::Color::FromArgb(myColor.A, 
                    myColor.R, 
                    myColor.G, 
                    v); 
                updateMe(4); 
            }
        }
        property System::Drawing::Color CurrentColor {
            System::Drawing::Color get() { return myColor; }
            void set(System::Drawing::Color c) { 
                myColor = c; 
                updateMe(7); 
            }
        }

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~RGBChoose()
		{
			if (components)
			{
				delete components;
			}
		}



    private: System::Windows::Forms::TextBox^  redBox;
    private: System::Windows::Forms::TextBox^  greenBox;
    private: System::Windows::Forms::TextBox^  blueBox;
    private: CFControls::ColorComponentChoose^  redBar;
    private: CFControls::ColorComponentChoose^  greenBar;
    private: CFControls::ColorComponentChoose^  blueBar;

    protected: 
        System::Drawing::Color myColor;



    protected: 
        System::Text::RegularExpressions::Regex^ validNumber;

        void OnColorChange(ColorChangeEventArgs^ e);

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
            this->redBox = (gcnew System::Windows::Forms::TextBox());
            this->greenBox = (gcnew System::Windows::Forms::TextBox());
            this->blueBox = (gcnew System::Windows::Forms::TextBox());
            this->redBar = (gcnew CFControls::ColorComponentChoose());
            this->greenBar = (gcnew CFControls::ColorComponentChoose());
            this->blueBar = (gcnew CFControls::ColorComponentChoose());
            this->SuspendLayout();
            // 
            // redBox
            // 
            this->redBox->Location = System::Drawing::Point(3, 166);
            this->redBox->MaxLength = 3;
            this->redBox->Name = L"redBox";
            this->redBox->Size = System::Drawing::Size(25, 20);
            this->redBox->TabIndex = 3;
            this->redBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // greenBox
            // 
            this->greenBox->Location = System::Drawing::Point(34, 166);
            this->greenBox->MaxLength = 3;
            this->greenBox->Name = L"greenBox";
            this->greenBox->Size = System::Drawing::Size(25, 20);
            this->greenBox->TabIndex = 4;
            this->greenBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // blueBox
            // 
            this->blueBox->Location = System::Drawing::Point(65, 166);
            this->blueBox->MaxLength = 3;
            this->blueBox->Name = L"blueBox";
            this->blueBox->Size = System::Drawing::Size(25, 20);
            this->blueBox->TabIndex = 5;
            this->blueBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // redBar
            // 
            this->redBar->Bright = 0;
            this->redBar->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
            this->redBar->Hue = 0;
            this->redBar->Location = System::Drawing::Point(3, 3);
            this->redBar->Name = L"redBar";
            this->redBar->Sat = 1;
            this->redBar->Size = System::Drawing::Size(25, 157);
            this->redBar->TabIndex = 0;
            this->redBar->Text = L"colorComponentChoose1";
            // 
            // greenBar
            // 
            this->greenBar->Bright = 0;
            this->greenBar->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
            this->greenBar->Hue = 120;
            this->greenBar->Location = System::Drawing::Point(34, 3);
            this->greenBar->Name = L"greenBar";
            this->greenBar->Sat = 1;
            this->greenBar->Size = System::Drawing::Size(25, 157);
            this->greenBar->TabIndex = 1;
            this->greenBar->Text = L"colorComponentChoose1";
            // 
            // blueBar
            // 
            this->blueBar->Bright = 0;
            this->blueBar->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
            this->blueBar->Hue = 240;
            this->blueBar->Location = System::Drawing::Point(65, 3);
            this->blueBar->Name = L"blueBar";
            this->blueBar->Sat = 1;
            this->blueBar->Size = System::Drawing::Size(25, 157);
            this->blueBar->TabIndex = 2;
            this->blueBar->Text = L"colorComponentChoose1";
            // 
            // RGBChoose
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->Controls->Add(this->blueBar);
            this->Controls->Add(this->greenBar);
            this->Controls->Add(this->redBar);
            this->Controls->Add(this->blueBox);
            this->Controls->Add(this->greenBox);
            this->Controls->Add(this->redBox);
            this->Name = L"RGBChoose";
            this->Size = System::Drawing::Size(93, 189);
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
        private:
            int heightToBoxPos;
            int heightToBarHeight;
            int lockedWidth;
            System::Void resizeHandler(System::Object^ sender, System::EventArgs^ e);
            void MoreInitialization();
            void updateMe(int which);
            System::Void colorHandler(Object^ sender, CFControls::ColorChangeEventArgs^ e);
            System::Void textHandler(System::Object^ sender, System::EventArgs^ e);
	};
}
