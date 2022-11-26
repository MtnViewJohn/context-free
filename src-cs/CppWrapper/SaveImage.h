#pragma once

#include "cfdg.h"
#include "UploadPrefs.h"

namespace CppWrapper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SaveImage
	/// </summary>
    public ref class SaveImage : public FileDialogExtenders::FileDialogControlBase
    {
    public:
        SaveImage(int fr, bool tiledOrFrieze, System::String^ file, System::String^ dir)
        {
            InitializeComponent();
            //
            //TODO: Add the constructor code here
            //
            if (tiledOrFrieze) {
                switch ((CFDG::frieze_t)fr) {
                case CFDG::frieze_x:
                    saveWidth->Text = "1";
                    saveWidth->Enabled = false;
                    break;
                case CFDG::frieze_y:
                    saveHeight->Text = "1";
                    saveHeight->Enabled = false;
                    break;
                default:
                    break;
                }
                checkCropImage->Visible = false;
            }
            else {
                saveWidth->Enabled = false;
                saveHeight->Enabled = false;
                saveWidth->Visible = false;
                saveHeight->Visible = false;
                widthLabel->Visible = false;
                heightLabel->Visible = false;
            }
            fileName = file;
            fileDir = dir;
        }

    public:
        System::Windows::Forms::DialogResult ShowTheDialog(System::Windows::Forms::IWin32Window^ owner,
            UploadPrefs^ prefs);


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
    private: System::Windows::Forms::CheckBox^ checkCropImage;

    protected:


    private: System::Windows::Forms::Label^ label1;



    private: System::Windows::Forms::TextBox^ JPEGQuality;
    private: System::Windows::Forms::TextBox^ saveWidth;
    private: System::Windows::Forms::Label^ heightLabel;

    private: System::Windows::Forms::Label^ widthLabel;


    private: System::Windows::Forms::TextBox^ saveHeight;
    public:

    public:

    public:

    private:
        /// <summary>
        /// Required designer variable.
        /// </summary>
        System::ComponentModel::Container^ components;

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
            this->saveWidth->TabIndex = 11;
            // 
            // heightLabel
            // 
            this->heightLabel->AutoSize = true;
            this->heightLabel->Location = System::Drawing::Point(121, 9);
            this->heightLabel->Name = L"heightLabel";
            this->heightLabel->Size = System::Drawing::Size(66, 13);
            this->heightLabel->TabIndex = 14;
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
            this->saveHeight->TabIndex = 13;
            // 
            // SaveImage
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->Controls->Add(this->saveWidth);
            this->Controls->Add(this->saveHeight);
            this->Controls->Add(this->widthLabel);
            this->Controls->Add(this->heightLabel);
            this->Controls->Add(this->checkCropImage);
            this->Controls->Add(this->JPEGQuality);
            this->Controls->Add(this->label1);
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
