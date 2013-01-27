// SaveImage.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2008-2012 John Horigan - john@glyphic.com
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

#include "CFPrefs.h"
#include "cfdg.h"

namespace ContextFreeNet {

	/// <summary>
	/// Summary for SaveImage
	/// </summary>
    public ref class SaveImage : public FileDialogExtenders::FileDialogControlBase
	{
	public:
        SaveImage(CFDG::frieze_t fr, array<double>^ mult, System::String^ file, System::String^ dir) 
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
            if (mult) {
                if (fr == CFDG::frieze_x)
                    mult[0] = 1.0;
                if (fr == CFDG::frieze_y)
                    mult[1] = 1.0;
                checkCropImage->Visible = false;
                saveWidth->Text = mult[0].ToString();
                saveHeight->Text = mult[1].ToString();
                saveWidth->Enabled = fr != CFDG::frieze_y;
                saveHeight->Enabled = fr != CFDG::frieze_x;
            } else {
                saveWidth->Visible = false;
                saveHeight->Visible = false;
                widthLabel->Visible = false;
                heightLabel->Visible = false;
            }
            fileName = file;
            fileDir = dir;
            multiplier = mult;
		}

    public:
        System::Windows::Forms::DialogResult ShowTheDialog(System::Windows::Forms::IWin32Window^ owner);
        

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
        virtual void OnPrepareMSDialog() override;		
        ~SaveImage()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::CheckBox^  checkCropImage;

    protected: 


    private: System::Windows::Forms::Label^  label1;



    private: System::Windows::Forms::TextBox^  JPEGQuality;
    private: System::Windows::Forms::TextBox^  saveWidth;
    private: System::Windows::Forms::Label^  heightLabel;

    private: System::Windows::Forms::Label^  widthLabel;


    private: System::Windows::Forms::TextBox^  saveHeight;
    public: 

    public: 

    public: 

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
            this->checkCropImage = (gcnew System::Windows::Forms::CheckBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->JPEGQuality = (gcnew System::Windows::Forms::TextBox());
            this->saveWidth = (gcnew System::Windows::Forms::TextBox());
            this->heightLabel = (gcnew System::Windows::Forms::Label());
            this->widthLabel = (gcnew System::Windows::Forms::Label());
            this->saveHeight = (gcnew System::Windows::Forms::TextBox());
            this->SuspendLayout();
            // 
            // checkCropImage
            // 
            this->checkCropImage->AutoSize = true;
            this->checkCropImage->Location = System::Drawing::Point(135, 8);
            this->checkCropImage->Name = L"checkCropImage";
            this->checkCropImage->Size = System::Drawing::Size(79, 17);
            this->checkCropImage->TabIndex = 15;
            this->checkCropImage->Text = L"Crop image";
            this->checkCropImage->UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(240, 9);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(72, 13);
            this->label1->TabIndex = 12;
            this->label1->Text = L"JPEG Quality:";
            // 
            // JPEGQuality
            // 
            this->JPEGQuality->Location = System::Drawing::Point(318, 6);
            this->JPEGQuality->MaxLength = 3;
            this->JPEGQuality->Name = L"JPEGQuality";
            this->JPEGQuality->Size = System::Drawing::Size(35, 20);
            this->JPEGQuality->TabIndex = 16;
            // 
            // saveWidth
            // 
            this->saveWidth->Location = System::Drawing::Point(72, 6);
            this->saveWidth->Name = L"saveWidth";
            this->saveWidth->Size = System::Drawing::Size(41, 20);
            this->saveWidth->TabIndex = 13;
            // 
            // heightLabel
            // 
            this->heightLabel->AutoSize = true;
            this->heightLabel->Location = System::Drawing::Point(121, 9);
            this->heightLabel->Name = L"heightLabel";
            this->heightLabel->Size = System::Drawing::Size(66, 13);
            this->heightLabel->TabIndex = 11;
            this->heightLabel->Text = L" Height mult:";
            // 
            // widthLabel
            // 
            this->widthLabel->AutoSize = true;
            this->widthLabel->Location = System::Drawing::Point(3, 9);
            this->widthLabel->Name = L"widthLabel";
            this->widthLabel->Size = System::Drawing::Size(63, 13);
            this->widthLabel->TabIndex = 10;
            this->widthLabel->Text = L" Width mult:";
            // 
            // saveHeight
            // 
            this->saveHeight->Location = System::Drawing::Point(193, 6);
            this->saveHeight->Name = L"saveHeight";
            this->saveHeight->Size = System::Drawing::Size(41, 20);
            this->saveHeight->TabIndex = 14;
            // 
            // SaveImage
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->Controls->Add(this->saveHeight);
            this->Controls->Add(this->widthLabel);
            this->Controls->Add(this->heightLabel);
            this->Controls->Add(this->saveWidth);
            this->Controls->Add(this->JPEGQuality);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->checkCropImage);
            this->FileDlgCaption = L"Save Image";
            this->FileDlgCheckFileExists = false;
            this->FileDlgDefaultExt = L"png";
            this->FileDlgFilter = L"PNG files (*.png)|*.png|JPEG files (*.jpg)|*.jpg|SVG files (*.svg)|*.svg";
            this->FileDlgOkCaption = L"&Save";
            this->FileDlgStartLocation = FileDialogExtenders::AddonWindowLocation::Bottom;
            this->FileDlgType = Win32Types::FileDialogType::SaveFileDlg;
            this->Name = L"SaveImage";
            this->Size = System::Drawing::Size(378, 38);
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
        private:
            System::String^ fileName;
            System::String^ fileDir;
            array<double>^ multiplier;
	};
}
