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
    private: System::Windows::Forms::Label^ JPEGlabel;

    protected:






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
            this->JPEGlabel = (gcnew System::Windows::Forms::Label());
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
            this->checkCropImage->Location = System::Drawing::Point(270, 15);
            this->checkCropImage->Margin = System::Windows::Forms::Padding(6);
            this->checkCropImage->Name = L"checkCropImage";
            this->checkCropImage->Size = System::Drawing::Size(154, 29);
            this->checkCropImage->TabIndex = 15;
            this->checkCropImage->Text = L"Crop image";
            this->checkCropImage->UseVisualStyleBackColor = true;
            // 
            // JPEGlabel
            // 
            this->JPEGlabel->AutoSize = true;
            this->JPEGlabel->ForeColor = System::Drawing::SystemColors::GrayText;
            this->JPEGlabel->Location = System::Drawing::Point(480, 17);
            this->JPEGlabel->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->JPEGlabel->Name = L"JPEGlabel";
            this->JPEGlabel->Size = System::Drawing::Size(146, 25);
            this->JPEGlabel->TabIndex = 12;
            this->JPEGlabel->Text = L"JPEG Quality:";
            // 
            // JPEGQuality
            // 
            this->JPEGQuality->Enabled = false;
            this->JPEGQuality->Location = System::Drawing::Point(636, 15);
            this->JPEGQuality->Margin = System::Windows::Forms::Padding(6);
            this->JPEGQuality->MaxLength = 3;
            this->JPEGQuality->Name = L"JPEGQuality";
            this->JPEGQuality->Size = System::Drawing::Size(66, 31);
            this->JPEGQuality->TabIndex = 16;
            this->JPEGQuality->Text = L"90";
            // 
            // saveWidth
            // 
            this->saveWidth->Location = System::Drawing::Point(144, 15);
            this->saveWidth->Margin = System::Windows::Forms::Padding(6);
            this->saveWidth->Name = L"saveWidth";
            this->saveWidth->Size = System::Drawing::Size(78, 31);
            this->saveWidth->TabIndex = 11;
            // 
            // heightLabel
            // 
            this->heightLabel->AutoSize = true;
            this->heightLabel->Location = System::Drawing::Point(242, 17);
            this->heightLabel->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->heightLabel->Name = L"heightLabel";
            this->heightLabel->Size = System::Drawing::Size(132, 25);
            this->heightLabel->TabIndex = 14;
            this->heightLabel->Text = L" Height mult:";
            // 
            // widthLabel
            // 
            this->widthLabel->AutoSize = true;
            this->widthLabel->Location = System::Drawing::Point(6, 17);
            this->widthLabel->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->widthLabel->Name = L"widthLabel";
            this->widthLabel->Size = System::Drawing::Size(125, 25);
            this->widthLabel->TabIndex = 10;
            this->widthLabel->Text = L" Width mult:";
            // 
            // saveHeight
            // 
            this->saveHeight->Location = System::Drawing::Point(386, 15);
            this->saveHeight->Margin = System::Windows::Forms::Padding(6);
            this->saveHeight->Name = L"saveHeight";
            this->saveHeight->Size = System::Drawing::Size(78, 31);
            this->saveHeight->TabIndex = 13;
            // 
            // SaveImage
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->Controls->Add(this->saveWidth);
            this->Controls->Add(this->saveHeight);
            this->Controls->Add(this->widthLabel);
            this->Controls->Add(this->heightLabel);
            this->Controls->Add(this->checkCropImage);
            this->Controls->Add(this->JPEGQuality);
            this->Controls->Add(this->JPEGlabel);
            this->FileDlgCaption = L"Save Image";
            this->FileDlgCheckFileExists = false;
            this->FileDlgDefaultExt = L"png";
            this->FileDlgFilter = L"PNG files (*.png)|*.png|JPEG files (*.jpg)|*.jpg|SVG files (*.svg)|*.svg";
            this->FileDlgOkCaption = L"&Save";
            this->FileDlgStartLocation = FileDialogExtenders::AddonWindowLocation::Bottom;
            this->FileDlgType = Win32Types::FileDialogType::SaveFileDlg;
            this->Margin = System::Windows::Forms::Padding(6);
            this->Name = L"SaveImage";
            this->Size = System::Drawing::Size(756, 73);
            this->EventFilterChanged += gcnew FileDialogExtenders::FileDialogControlBase::FilterChangedEventHandler(this, &SaveImage::fileTypeChanged);
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private:
        System::String^ fileName;
        System::String^ fileDir;
        System::Void fileTypeChanged(System::Windows::Forms::IWin32Window^ sender, System::Int32 index);
};
}
