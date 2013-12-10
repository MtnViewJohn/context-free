// HSBEdit.h
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

#pragma once

#include "hsbColor.h"
#include "ColorChangeEventArgs.h"

namespace CFControls {

	/// <summary>
	/// Summary for HSBEdit
	/// </summary>
	public ref class HSBEdit : public System::Windows::Forms::UserControl
	{
	public:
        HSBEdit(void) : myColor(0.0, 0.0, 0.0)
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
            void set(double v) { myColor.Hue = v; updateMe(1); }
        }
        property double Sat {
            double get() { return myColor.Sat; }
            void set(double v) { myColor.Sat = v; updateMe(2); }
        }
        property double Bright {
            double get() { return myColor.Bright; }
            void set(double v) { myColor.Bright = v; updateMe(4); }
        }
        property hsbColor CurrentColor {
            hsbColor get() { return myColor; }
            void set(hsbColor c) { myColor = c; updateMe(7); }
        }
        property bool ShowColor {
            bool get() { return colorBox->Visible; }
            void set(bool s) { colorBox->Visible = s; colorBox->Enabled = s; }
        }

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~HSBEdit()
		{
			if (components)
			{
				delete components;
			}
		}

        void OnColorChange(ColorChangeEventArgs^ e);

    private: System::Windows::Forms::TextBox^  hueBox;
    protected: 
    private: System::Windows::Forms::TextBox^  satBox;
    private: System::Windows::Forms::TextBox^  brightBox;


    private: System::Windows::Forms::TextBox^  hsbBox;
    private: System::Windows::Forms::PictureBox^  colorBox;
        hsbColor myColor;


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
            this->hueBox = (gcnew System::Windows::Forms::TextBox());
            this->satBox = (gcnew System::Windows::Forms::TextBox());
            this->brightBox = (gcnew System::Windows::Forms::TextBox());
            this->hsbBox = (gcnew System::Windows::Forms::TextBox());
            this->colorBox = (gcnew System::Windows::Forms::PictureBox());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->colorBox))->BeginInit();
            this->SuspendLayout();
            // 
            // hueBox
            // 
            this->hueBox->Location = System::Drawing::Point(4, 6);
            this->hueBox->MaxLength = 10;
            this->hueBox->Name = L"hueBox";
            this->hueBox->Size = System::Drawing::Size(60, 20);
            this->hueBox->TabIndex = 0;
            // 
            // satBox
            // 
            this->satBox->Location = System::Drawing::Point(70, 6);
            this->satBox->MaxLength = 10;
            this->satBox->Name = L"satBox";
            this->satBox->Size = System::Drawing::Size(60, 20);
            this->satBox->TabIndex = 1;
            // 
            // brightBox
            // 
            this->brightBox->Location = System::Drawing::Point(136, 6);
            this->brightBox->MaxLength = 10;
            this->brightBox->Name = L"brightBox";
            this->brightBox->Size = System::Drawing::Size(60, 20);
            this->brightBox->TabIndex = 2;
            // 
            // hsbBox
            // 
            this->hsbBox->Location = System::Drawing::Point(4, 32);
            this->hsbBox->Name = L"hsbBox";
            this->hsbBox->ReadOnly = true;
            this->hsbBox->Size = System::Drawing::Size(192, 20);
            this->hsbBox->TabIndex = 4;
            // 
            // colorBox
            // 
            this->colorBox->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->colorBox->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->colorBox->Location = System::Drawing::Point(202, 6);
            this->colorBox->Name = L"colorBox";
            this->colorBox->Size = System::Drawing::Size(52, 46);
            this->colorBox->TabIndex = 5;
            this->colorBox->TabStop = false;
            // 
            // HSBEdit
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->Controls->Add(this->colorBox);
            this->Controls->Add(this->hsbBox);
            this->Controls->Add(this->brightBox);
            this->Controls->Add(this->satBox);
            this->Controls->Add(this->hueBox);
            this->Name = L"HSBEdit";
            this->Size = System::Drawing::Size(258, 56);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->colorBox))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
        private:
            void MoreInitialization();
            System::Void textHandler(System::Object^ sender, System::EventArgs^ e);
            void updateMe(int which);
	};
}
