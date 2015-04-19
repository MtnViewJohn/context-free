// UploadDesign.h
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
#include "Document.h"
#include "upload.h"
#include "Variation.h"

class Upload;

namespace ContextFreeNet {

	/// <summary>
	/// Summary for UploadDesign
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class UploadDesign : public System::Windows::Forms::Form
	{
	public:
        UploadDesign(Document^ doc, System::String^ name, Upload* u,
                     CFDG::frieze_t fr, array<double>^ mult) 
            : mDoc(doc), mUpload(u)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
            nextText = wizard1->NextText;
            gotoDesignPage = Form1::prefs->SkipAccount;
            checkSkipAcct->Checked = Form1::prefs->SkipAccount;
            usernameBox->Text = Form1::prefs->GalUsername;
            passwordBox->Text = Form1::prefs->GalPassword;
            checkCrop->Checked = Form1::prefs->ImageCrop;
            if (u->mCompression == Upload::CompressJPEG) {
                radioJPEG->Checked = true;
            } else {
                radioPNG8->Checked = true;
            }
            if (mult) {
                if (fr == CFDG::frieze_x)
                    mult[0] = 1.0;
                if (fr == CFDG::frieze_y)
                    mult[1] = 1.0;
                checkCrop->Visible = false;
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
            outputMultiplier = mult;
            checkTiled->Checked = u->mTiled;
            titleBox->Text = name;
            fileNameBox->Text = name;
            std::string vChars = Variation::toString(u->mVariation, false);
            this->labelVariation->Text = gcnew System::String(vChars.c_str());

            wizard1->BeforeSwitchPages += gcnew CristiPotlog::Controls::Wizard::BeforeSwitchPagesEventHandler(this, &UploadDesign::wizardPage_beforeChange);
            wizard1->AfterSwitchPages += gcnew CristiPotlog::Controls::Wizard::AfterSwitchPagesEventHandler(this, &UploadDesign::wizardPage_afterChange);
            this->Load += gcnew System::EventHandler(this, &UploadDesign::uploadDesignLoaded);
            this->CancelButton = wizard1->buttonCancel;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UploadDesign()
		{
			if (components)
			{
				delete components;
			}
		}
    private: CristiPotlog::Controls::Wizard^  wizard1;
    private: Document^ mDoc;
    private: Upload* mUpload;
    private: System::Windows::Forms::Timer^ uploadPoll;
    private: bool gotoDesignPage;
    private: System::String^ nextText;
    private: int imageListBase;
    private: int statusIndex;
    private: CristiPotlog::Controls::WizardPage^  licensePage;
    protected: 

    private: CristiPotlog::Controls::WizardPage^  designPage;
    private: CristiPotlog::Controls::WizardPage^  accountPage;
    private: System::Windows::Forms::TextBox^  passwordBox;
    private: System::Windows::Forms::TextBox^  usernameBox;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::Label^  label1;
    private: CristiPotlog::Controls::WizardPage^  uploadPage;
    private: System::Windows::Forms::Button^  accountButton;
    private: System::Windows::Forms::Label^  label3;
    private: System::Windows::Forms::CheckBox^  checkSkipAcct;
    private: System::Windows::Forms::Label^  label4;
    private: System::Windows::Forms::TextBox^  fileNameBox;

    private: System::Windows::Forms::TextBox^  notesBox;
    private: System::Windows::Forms::TextBox^  titleBox;
    private: System::Windows::Forms::WebBrowser^  ccLicenseBrowser;
    private: System::Windows::Forms::WebBrowser^  uploadBrowser;
    private: System::Windows::Forms::RadioButton^  radioPNG8;
    private: System::Windows::Forms::RadioButton^  radioJPEG;
    private: System::Windows::Forms::CheckBox^  checkCrop;
    private: System::Windows::Forms::Label^  labelVariation;

    private: System::Windows::Forms::Label^  label10;
    private: System::Windows::Forms::Label^  label9;
    private: System::Windows::Forms::Label^  label8;
    private: System::Windows::Forms::Label^  label7;
    private: System::Windows::Forms::Label^  label6;
    private: System::Windows::Forms::Label^  labelDesignError;
    private: System::Windows::Forms::Label^  labelAcctError;
    private: System::Windows::Forms::CheckBox^  checkTiled;

    private: System::Windows::Forms::StatusStrip^  statusStripUpload;
    private: System::Windows::Forms::ToolStripStatusLabel^  statusIconUpload;
    private: System::Windows::Forms::ToolStripStatusLabel^  statusLabelUpload;
private: System::Windows::Forms::TextBox^  saveHeight;

private: System::Windows::Forms::Label^  heightLabel;
private: System::Windows::Forms::Label^  widthLabel;
private: System::Windows::Forms::TextBox^  saveWidth;





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
            System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(UploadDesign::typeid));
            this->wizard1 = (gcnew CristiPotlog::Controls::Wizard());
            this->designPage = (gcnew CristiPotlog::Controls::WizardPage());
            this->checkTiled = (gcnew System::Windows::Forms::CheckBox());
            this->labelDesignError = (gcnew System::Windows::Forms::Label());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->radioPNG8 = (gcnew System::Windows::Forms::RadioButton());
            this->radioJPEG = (gcnew System::Windows::Forms::RadioButton());
            this->checkCrop = (gcnew System::Windows::Forms::CheckBox());
            this->labelVariation = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->fileNameBox = (gcnew System::Windows::Forms::TextBox());
            this->notesBox = (gcnew System::Windows::Forms::TextBox());
            this->titleBox = (gcnew System::Windows::Forms::TextBox());
            this->licensePage = (gcnew CristiPotlog::Controls::WizardPage());
            this->ccLicenseBrowser = (gcnew System::Windows::Forms::WebBrowser());
            this->uploadPage = (gcnew CristiPotlog::Controls::WizardPage());
            this->statusStripUpload = (gcnew System::Windows::Forms::StatusStrip());
            this->statusIconUpload = (gcnew System::Windows::Forms::ToolStripStatusLabel());
            this->statusLabelUpload = (gcnew System::Windows::Forms::ToolStripStatusLabel());
            this->uploadBrowser = (gcnew System::Windows::Forms::WebBrowser());
            this->accountPage = (gcnew CristiPotlog::Controls::WizardPage());
            this->labelAcctError = (gcnew System::Windows::Forms::Label());
            this->accountButton = (gcnew System::Windows::Forms::Button());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->checkSkipAcct = (gcnew System::Windows::Forms::CheckBox());
            this->passwordBox = (gcnew System::Windows::Forms::TextBox());
            this->usernameBox = (gcnew System::Windows::Forms::TextBox());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->widthLabel = (gcnew System::Windows::Forms::Label());
            this->heightLabel = (gcnew System::Windows::Forms::Label());
            this->saveHeight = (gcnew System::Windows::Forms::TextBox());
            this->saveWidth = (gcnew System::Windows::Forms::TextBox());
            this->wizard1->SuspendLayout();
            this->designPage->SuspendLayout();
            this->licensePage->SuspendLayout();
            this->uploadPage->SuspendLayout();
            this->statusStripUpload->SuspendLayout();
            this->accountPage->SuspendLayout();
            this->SuspendLayout();
            // 
            // wizard1
            // 
            this->wizard1->Controls->Add(this->designPage);
            this->wizard1->Controls->Add(this->accountPage);
            this->wizard1->Controls->Add(this->uploadPage);
            this->wizard1->Controls->Add(this->licensePage);
            this->wizard1->HeaderImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"wizard1.HeaderImage")));
            this->wizard1->HeaderTitleFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->wizard1->Location = System::Drawing::Point(0, 0);
            this->wizard1->Name = L"wizard1";
            this->wizard1->Pages->AddRange(gcnew cli::array< CristiPotlog::Controls::WizardPage^  >(4) {this->accountPage, this->designPage, 
                this->licensePage, this->uploadPage});
            this->wizard1->Size = System::Drawing::Size(440, 377);
            this->wizard1->TabIndex = 0;
            // 
            // designPage
            // 
            this->designPage->Controls->Add(this->saveWidth);
            this->designPage->Controls->Add(this->saveHeight);
            this->designPage->Controls->Add(this->heightLabel);
            this->designPage->Controls->Add(this->widthLabel);
            this->designPage->Controls->Add(this->checkTiled);
            this->designPage->Controls->Add(this->labelDesignError);
            this->designPage->Controls->Add(this->label10);
            this->designPage->Controls->Add(this->label9);
            this->designPage->Controls->Add(this->label8);
            this->designPage->Controls->Add(this->label7);
            this->designPage->Controls->Add(this->label6);
            this->designPage->Controls->Add(this->radioPNG8);
            this->designPage->Controls->Add(this->radioJPEG);
            this->designPage->Controls->Add(this->checkCrop);
            this->designPage->Controls->Add(this->labelVariation);
            this->designPage->Controls->Add(this->label4);
            this->designPage->Controls->Add(this->fileNameBox);
            this->designPage->Controls->Add(this->notesBox);
            this->designPage->Controls->Add(this->titleBox);
            this->designPage->Location = System::Drawing::Point(0, 0);
            this->designPage->Name = L"designPage";
            this->designPage->Size = System::Drawing::Size(440, 329);
            this->designPage->TabIndex = 11;
            this->designPage->Title = L"Design Information";
            // 
            // checkTiled
            // 
            this->checkTiled->AutoSize = true;
            this->checkTiled->Location = System::Drawing::Point(115, 252);
            this->checkTiled->Name = L"checkTiled";
            this->checkTiled->Size = System::Drawing::Size(91, 17);
            this->checkTiled->TabIndex = 14;
            this->checkTiled->Text = L"Design is tiled";
            this->checkTiled->UseVisualStyleBackColor = true;
            // 
            // labelDesignError
            // 
            this->labelDesignError->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->labelDesignError->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
                static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
            this->labelDesignError->Location = System::Drawing::Point(303, 154);
            this->labelDesignError->Name = L"labelDesignError";
            this->labelDesignError->Size = System::Drawing::Size(121, 54);
            this->labelDesignError->TabIndex = 13;
            this->labelDesignError->Text = L"You must provide a title and a file name.";
            this->labelDesignError->Visible = false;
            // 
            // label10
            // 
            this->label10->Location = System::Drawing::Point(32, 276);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(74, 37);
            this->label10->TabIndex = 12;
            this->label10->Text = L"Gallery image compression:";
            this->label10->TextAlign = System::Drawing::ContentAlignment::TopRight;
            // 
            // label9
            // 
            this->label9->AutoSize = true;
            this->label9->Location = System::Drawing::Point(55, 228);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(51, 13);
            this->label9->TabIndex = 11;
            this->label9->Text = L"Variation:";
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->Location = System::Drawing::Point(51, 204);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(55, 13);
            this->label8->TabIndex = 10;
            this->label8->Text = L"File name:";
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Location = System::Drawing::Point(68, 108);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(38, 13);
            this->label7->TabIndex = 9;
            this->label7->Text = L"Notes:";
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(76, 84);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(30, 13);
            this->label6->TabIndex = 8;
            this->label6->Text = L"Title:";
            // 
            // radioPNG8
            // 
            this->radioPNG8->AutoSize = true;
            this->radioPNG8->Location = System::Drawing::Point(115, 296);
            this->radioPNG8->Name = L"radioPNG8";
            this->radioPNG8->Size = System::Drawing::Size(57, 17);
            this->radioPNG8->TabIndex = 7;
            this->radioPNG8->TabStop = true;
            this->radioPNG8->Text = L"PNG-8";
            this->radioPNG8->UseVisualStyleBackColor = true;
            // 
            // radioJPEG
            // 
            this->radioJPEG->AutoSize = true;
            this->radioJPEG->Location = System::Drawing::Point(115, 276);
            this->radioJPEG->Name = L"radioJPEG";
            this->radioJPEG->Size = System::Drawing::Size(52, 17);
            this->radioJPEG->TabIndex = 6;
            this->radioJPEG->TabStop = true;
            this->radioJPEG->Text = L"JPEG";
            this->radioJPEG->UseVisualStyleBackColor = true;
            // 
            // checkCrop
            // 
            this->checkCrop->AutoSize = true;
            this->checkCrop->Location = System::Drawing::Point(209, 252);
            this->checkCrop->Name = L"checkCrop";
            this->checkCrop->Size = System::Drawing::Size(79, 17);
            this->checkCrop->TabIndex = 5;
            this->checkCrop->Text = L"Crop image";
            this->checkCrop->UseVisualStyleBackColor = true;
            // 
            // labelVariation
            // 
            this->labelVariation->Location = System::Drawing::Point(112, 228);
            this->labelVariation->Name = L"labelVariation";
            this->labelVariation->Size = System::Drawing::Size(75, 20);
            this->labelVariation->TabIndex = 4;
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(257, 207);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(31, 13);
            this->label4->TabIndex = 3;
            this->label4->Text = L".cfdg";
            // 
            // fileNameBox
            // 
            this->fileNameBox->Location = System::Drawing::Point(112, 201);
            this->fileNameBox->MaxLength = 256;
            this->fileNameBox->Name = L"fileNameBox";
            this->fileNameBox->Size = System::Drawing::Size(145, 20);
            this->fileNameBox->TabIndex = 2;
            this->fileNameBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // notesBox
            // 
            this->notesBox->Location = System::Drawing::Point(112, 108);
            this->notesBox->MaxLength = 32768;
            this->notesBox->Multiline = true;
            this->notesBox->Name = L"notesBox";
            this->notesBox->Size = System::Drawing::Size(176, 86);
            this->notesBox->TabIndex = 1;
            // 
            // titleBox
            // 
            this->titleBox->Location = System::Drawing::Point(112, 81);
            this->titleBox->MaxLength = 256;
            this->titleBox->Name = L"titleBox";
            this->titleBox->Size = System::Drawing::Size(176, 20);
            this->titleBox->TabIndex = 0;
            // 
            // licensePage
            // 
            this->licensePage->Controls->Add(this->ccLicenseBrowser);
            this->licensePage->Location = System::Drawing::Point(0, 0);
            this->licensePage->Name = L"licensePage";
            this->licensePage->Size = System::Drawing::Size(428, 208);
            this->licensePage->TabIndex = 12;
            this->licensePage->Title = L"Creative Commons License";
            // 
            // ccLicenseBrowser
            // 
            this->ccLicenseBrowser->AllowWebBrowserDrop = false;
            this->ccLicenseBrowser->Location = System::Drawing::Point(0, 64);
            this->ccLicenseBrowser->MinimumSize = System::Drawing::Size(20, 20);
            this->ccLicenseBrowser->Name = L"ccLicenseBrowser";
            this->ccLicenseBrowser->Size = System::Drawing::Size(440, 265);
            this->ccLicenseBrowser->TabIndex = 0;
            // 
            // uploadPage
            // 
            this->uploadPage->Controls->Add(this->statusStripUpload);
            this->uploadPage->Controls->Add(this->uploadBrowser);
            this->uploadPage->Location = System::Drawing::Point(0, 0);
            this->uploadPage->Name = L"uploadPage";
            this->uploadPage->Size = System::Drawing::Size(440, 329);
            this->uploadPage->TabIndex = 13;
            this->uploadPage->Title = L"Upload Design";
            // 
            // statusStripUpload
            // 
            this->statusStripUpload->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->statusIconUpload, 
                this->statusLabelUpload});
            this->statusStripUpload->Location = System::Drawing::Point(0, 307);
            this->statusStripUpload->Name = L"statusStripUpload";
            this->statusStripUpload->Size = System::Drawing::Size(440, 22);
            this->statusStripUpload->TabIndex = 1;
            this->statusStripUpload->Text = L"statusStrip1";
            this->statusStripUpload->Visible = false;
            // 
            // statusIconUpload
            // 
            this->statusIconUpload->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
            this->statusIconUpload->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"statusIconUpload.Image")));
            this->statusIconUpload->Name = L"statusIconUpload";
            this->statusIconUpload->Size = System::Drawing::Size(16, 17);
            // 
            // statusLabelUpload
            // 
            this->statusLabelUpload->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
            this->statusLabelUpload->Name = L"statusLabelUpload";
            this->statusLabelUpload->Size = System::Drawing::Size(409, 17);
            this->statusLabelUpload->Spring = true;
            this->statusLabelUpload->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // uploadBrowser
            // 
            this->uploadBrowser->AllowWebBrowserDrop = false;
            this->uploadBrowser->Location = System::Drawing::Point(0, 64);
            this->uploadBrowser->MinimumSize = System::Drawing::Size(20, 20);
            this->uploadBrowser->Name = L"uploadBrowser";
            this->uploadBrowser->Size = System::Drawing::Size(440, 240);
            this->uploadBrowser->TabIndex = 0;
            // 
            // accountPage
            // 
            this->accountPage->Controls->Add(this->labelAcctError);
            this->accountPage->Controls->Add(this->accountButton);
            this->accountPage->Controls->Add(this->label3);
            this->accountPage->Controls->Add(this->checkSkipAcct);
            this->accountPage->Controls->Add(this->passwordBox);
            this->accountPage->Controls->Add(this->usernameBox);
            this->accountPage->Controls->Add(this->label2);
            this->accountPage->Controls->Add(this->label1);
            this->accountPage->Location = System::Drawing::Point(0, 0);
            this->accountPage->Name = L"accountPage";
            this->accountPage->Size = System::Drawing::Size(440, 329);
            this->accountPage->TabIndex = 10;
            this->accountPage->Title = L"Account Information";
            // 
            // labelAcctError
            // 
            this->labelAcctError->AutoSize = true;
            this->labelAcctError->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->labelAcctError->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
                static_cast<System::Int32>(static_cast<System::Byte>(0)));
            this->labelAcctError->Location = System::Drawing::Point(18, 205);
            this->labelAcctError->Name = L"labelAcctError";
            this->labelAcctError->Size = System::Drawing::Size(327, 16);
            this->labelAcctError->TabIndex = 7;
            this->labelAcctError->Text = L"You must provide a username and a password";
            this->labelAcctError->Visible = false;
            // 
            // accountButton
            // 
            this->accountButton->Location = System::Drawing::Point(237, 101);
            this->accountButton->Name = L"accountButton";
            this->accountButton->Size = System::Drawing::Size(75, 23);
            this->accountButton->TabIndex = 6;
            this->accountButton->Text = L"Create One";
            this->accountButton->UseVisualStyleBackColor = true;
            this->accountButton->Click += gcnew System::EventHandler(this, &UploadDesign::accountButton_Click);
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(234, 81);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(122, 13);
            this->label3->TabIndex = 5;
            this->label3->Text = L"Don\'t have an account\?";
            // 
            // checkSkipAcct
            // 
            this->checkSkipAcct->AutoSize = true;
            this->checkSkipAcct->Location = System::Drawing::Point(18, 148);
            this->checkSkipAcct->Name = L"checkSkipAcct";
            this->checkSkipAcct->Size = System::Drawing::Size(152, 17);
            this->checkSkipAcct->TabIndex = 4;
            this->checkSkipAcct->Text = L"Skip this page in the future";
            this->checkSkipAcct->UseVisualStyleBackColor = true;
            // 
            // passwordBox
            // 
            this->passwordBox->Location = System::Drawing::Point(77, 104);
            this->passwordBox->Name = L"passwordBox";
            this->passwordBox->PasswordChar = '*';
            this->passwordBox->Size = System::Drawing::Size(100, 20);
            this->passwordBox->TabIndex = 3;
            // 
            // usernameBox
            // 
            this->usernameBox->Location = System::Drawing::Point(77, 78);
            this->usernameBox->MaxLength = 256;
            this->usernameBox->Name = L"usernameBox";
            this->usernameBox->Size = System::Drawing::Size(100, 20);
            this->usernameBox->TabIndex = 2;
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(15, 107);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(56, 13);
            this->label2->TabIndex = 1;
            this->label2->Text = L"Password:";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(13, 81);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(58, 13);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Username:";
            // 
            // widthLabel
            // 
            this->widthLabel->AutoSize = true;
            this->widthLabel->Location = System::Drawing::Point(217, 253);
            this->widthLabel->Name = L"widthLabel";
            this->widthLabel->Size = System::Drawing::Size(82, 13);
            this->widthLabel->TabIndex = 15;
            this->widthLabel->Text = L"Width Multiplier:";
            // 
            // heightLabel
            // 
            this->heightLabel->AutoSize = true;
            this->heightLabel->Location = System::Drawing::Point(217, 276);
            this->heightLabel->Name = L"heightLabel";
            this->heightLabel->Size = System::Drawing::Size(85, 13);
            this->heightLabel->TabIndex = 16;
            this->heightLabel->Text = L"Height Multiplier:";
            // 
            // saveHeight
            // 
            this->saveHeight->Location = System::Drawing::Point(311, 273);
            this->saveHeight->Name = L"saveHeight";
            this->saveHeight->Size = System::Drawing::Size(67, 20);
            this->saveHeight->TabIndex = 18;
            // 
            // saveWidth
            // 
            this->saveWidth->Location = System::Drawing::Point(311, 247);
            this->saveWidth->Name = L"saveWidth";
            this->saveWidth->Size = System::Drawing::Size(67, 20);
            this->saveWidth->TabIndex = 17;
            // 
            // UploadDesign
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(440, 377);
            this->Controls->Add(this->wizard1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
            this->Name = L"UploadDesign";
            this->ShowInTaskbar = false;
            this->Text = L"Upload to Context Free Gallery";
            this->wizard1->ResumeLayout(false);
            this->designPage->ResumeLayout(false);
            this->designPage->PerformLayout();
            this->licensePage->ResumeLayout(false);
            this->uploadPage->ResumeLayout(false);
            this->uploadPage->PerformLayout();
            this->statusStripUpload->ResumeLayout(false);
            this->statusStripUpload->PerformLayout();
            this->accountPage->ResumeLayout(false);
            this->accountPage->PerformLayout();
            this->ResumeLayout(false);

        }
#pragma endregion
    private: System::Void uploadPoll_Tick(System::Object^  sender, System::EventArgs^  e);
    private: System::Void accountButton_Click(System::Object^  sender, System::EventArgs^  e);
    private: System::Void uploadDesignLoaded(System::Object^  sender, System::EventArgs^  e);
    private: System::Void bounceNavigation(System::Object^ sender, 
                          System::Windows::Forms::WebBrowserNavigatingEventArgs^ e);
    private: System::Windows::Forms::WebBrowserNavigatingEventHandler^ bouncer;
             array<double>^ outputMultiplier;

             System::Void wizardPage_beforeChange(System::Object^ sender, 
                 CristiPotlog::Controls::Wizard::BeforeSwitchPagesEventArgs^ e);
             System::Void wizardPage_afterChange(System::Object^ sender, 
                 CristiPotlog::Controls::Wizard::AfterSwitchPagesEventArgs^ e);
};
}
