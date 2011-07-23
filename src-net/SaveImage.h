// SaveImage.h
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

#include "CFPrefs.h"

namespace ContextFreeNet {

	/// <summary>
	/// Summary for SaveImage
	/// </summary>
    public ref class SaveImage : public FileDialogExtenders::FileDialogControlBase
	{
	public:
        SaveImage(bool tiled, bool rect, System::String^ file, System::String^ dir) 
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
            checkCropImage->Visible = !tiled;
            checkRectangular->Visible = tiled;
            checkRectangular->Enabled = rect;
            fileName = file;
            fileDir = dir;
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


    public: System::Windows::Forms::CheckBox^  checkRectangular;
    private: System::Windows::Forms::TextBox^  JPEGQuality;
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
            this->checkRectangular = (gcnew System::Windows::Forms::CheckBox());
            this->JPEGQuality = (gcnew System::Windows::Forms::TextBox());
            this->SuspendLayout();
            // 
            // checkCropImage
            // 
            this->checkCropImage->AutoSize = true;
            this->checkCropImage->Location = System::Drawing::Point(135, 8);
            this->checkCropImage->Name = L"checkCropImage";
            this->checkCropImage->Size = System::Drawing::Size(79, 17);
            this->checkCropImage->TabIndex = 0;
            this->checkCropImage->Text = L"Crop image";
            this->checkCropImage->UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(240, 9);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(72, 13);
            this->label1->TabIndex = 3;
            this->label1->Text = L"JPEG Quality:";
            // 
            // checkRectangular
            // 
            this->checkRectangular->AutoSize = true;
            this->checkRectangular->Location = System::Drawing::Point(135, 8);
            this->checkRectangular->Name = L"checkRectangular";
            this->checkRectangular->Size = System::Drawing::Size(109, 17);
            this->checkRectangular->TabIndex = 6;
            this->checkRectangular->Text = L"Make rectangular";
            this->checkRectangular->UseVisualStyleBackColor = true;
            // 
            // JPEGQuality
            // 
            this->JPEGQuality->Location = System::Drawing::Point(318, 6);
            this->JPEGQuality->MaxLength = 3;
            this->JPEGQuality->Name = L"JPEGQuality";
            this->JPEGQuality->Size = System::Drawing::Size(35, 20);
            this->JPEGQuality->TabIndex = 7;
            // 
            // SaveImage
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->Controls->Add(this->JPEGQuality);
            this->Controls->Add(this->checkRectangular);
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
	};
}
