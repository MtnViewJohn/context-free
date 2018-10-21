// PreferenceDialog.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2008-2009 John Horigan - john@glyphic.com
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
	/// Summary for PreferenceDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class PreferenceDialog : public System::Windows::Forms::Form
	{
	public:
		PreferenceDialog(CFPrefs^ p)
            : prefs(p)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
            Activated += gcnew System::EventHandler(this, &PreferenceDialog::setup_dialog);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PreferenceDialog()
		{
			if (components)
			{
				delete components;
			}
		}

        bool ProcessDialogKey(System::Windows::Forms::Keys keyData) override
        {
            if (keyData == System::Windows::Forms::Keys::Escape)
                this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            return System::Windows::Forms::Form::ProcessDialogKey(keyData);
        }

    private: CFPrefs^ prefs;
             System::Windows::Forms::ToolTip^       toolTip1;
    private: System::Windows::Forms::RadioButton^  radioOpenWelcome;
    protected: 
    private: System::Windows::Forms::RadioButton^  radioOpenNew;
    private: System::Windows::Forms::RadioButton^  radioOpenNothing;
    private: System::Windows::Forms::CheckBox^  checkOpenRender;
    private: System::Windows::Forms::CheckBox^  checkRenderUpdate;
    private: System::Windows::Forms::TrackBar^  trackBarBorder;

    private: System::Windows::Forms::CheckBox^  checkSaveWithVariation;
    private: System::Windows::Forms::CheckBox^  checkCropImage;


    private: System::Windows::Forms::Label^  label10;
    private: System::Windows::Forms::Label^  label9;
    private: System::Windows::Forms::Label^  label8;
    private: System::Windows::Forms::Label^  label7;
    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::Label^  label3;
    private: System::Windows::Forms::Label^  label4;
    private: System::Windows::Forms::Label^  label5;
    private: System::Windows::Forms::Label^  label6;
    public: System::Windows::Forms::Button^  buttonOK;
    private:

    private: System::Windows::Forms::Button^  buttonCancel;
    private: System::Windows::Forms::MaskedTextBox^  editJPEGquality;
    private: System::Windows::Forms::Label^  label11;
    public: System::Windows::Forms::TextBox^  fontDisplay;
    private: 

    public: System::Windows::Forms::Button^  fontChange;
    private: System::Windows::Forms::Label^  label12;
    private: System::Windows::Forms::TrackBar^  trackBarTab;
    private: System::Windows::Forms::TabControl^  tabControl1;
    private: System::Windows::Forms::TabPage^  tabPage1;
    private: System::Windows::Forms::TabPage^  tabPage2;
    private: System::Windows::Forms::TextBox^  identifiersColor;

    private: System::Windows::Forms::CheckBox^  identifiersItalic;

    private: System::Windows::Forms::CheckBox^  identifiersBold;

    private: System::Windows::Forms::Label^  label16;
    private: System::Windows::Forms::TextBox^  symbolsColor;

    private: System::Windows::Forms::CheckBox^  symbolsItalic;

    private: System::Windows::Forms::CheckBox^  symbolsBold;

    private: System::Windows::Forms::Label^  label15;
    private: System::Windows::Forms::TextBox^  commentsColor;

    private: System::Windows::Forms::CheckBox^  commentsItalic;

    private: System::Windows::Forms::CheckBox^  commentsBold;

    private: System::Windows::Forms::Label^  label14;
    private: System::Windows::Forms::TextBox^  defaultColor;

    private: System::Windows::Forms::CheckBox^  defaultItalic;

    private: System::Windows::Forms::CheckBox^  defaultBold;

    private: System::Windows::Forms::Label^  label13;

    private: System::Windows::Forms::TextBox^  numbersColor;
    private: System::Windows::Forms::CheckBox^  numbersItalic;
    private: System::Windows::Forms::CheckBox^  numbersBold;
    private: System::Windows::Forms::Label^  label21;
    private: System::Windows::Forms::TextBox^  stringsColor;
    private: System::Windows::Forms::CheckBox^  stringsItalic;
    private: System::Windows::Forms::CheckBox^  stringsBold;
    private: System::Windows::Forms::Label^  label22;
    private: System::Windows::Forms::TextBox^  builtinsColor;
    private: System::Windows::Forms::CheckBox^  builtinsItalic;
    private: System::Windows::Forms::CheckBox^  builtinsBold;
    private: System::Windows::Forms::Label^  label23;
    private: System::Windows::Forms::TextBox^  keywordsColor;
    private: System::Windows::Forms::CheckBox^  keywordsItalic;
    private: System::Windows::Forms::CheckBox^  keywordsBold;
    private: System::Windows::Forms::Label^  label24;
    private: System::Windows::Forms::Label^  label20;
    private: System::Windows::Forms::Label^  label19;
    private: System::Windows::Forms::Label^  label18;
    private: System::Windows::Forms::Label^  label17;
private: System::Windows::Forms::ToolTip^  toolTip2;

    private: System::ComponentModel::IContainer^  components;
    public:
    private:



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->components = (gcnew System::ComponentModel::Container());
            System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(PreferenceDialog::typeid));
            this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
            this->radioOpenWelcome = (gcnew System::Windows::Forms::RadioButton());
            this->radioOpenNew = (gcnew System::Windows::Forms::RadioButton());
            this->radioOpenNothing = (gcnew System::Windows::Forms::RadioButton());
            this->checkOpenRender = (gcnew System::Windows::Forms::CheckBox());
            this->checkRenderUpdate = (gcnew System::Windows::Forms::CheckBox());
            this->trackBarBorder = (gcnew System::Windows::Forms::TrackBar());
            this->checkSaveWithVariation = (gcnew System::Windows::Forms::CheckBox());
            this->checkCropImage = (gcnew System::Windows::Forms::CheckBox());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->buttonOK = (gcnew System::Windows::Forms::Button());
            this->buttonCancel = (gcnew System::Windows::Forms::Button());
            this->editJPEGquality = (gcnew System::Windows::Forms::MaskedTextBox());
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->fontDisplay = (gcnew System::Windows::Forms::TextBox());
            this->fontChange = (gcnew System::Windows::Forms::Button());
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->trackBarTab = (gcnew System::Windows::Forms::TrackBar());
            this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
            this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
            this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
            this->numbersColor = (gcnew System::Windows::Forms::TextBox());
            this->numbersItalic = (gcnew System::Windows::Forms::CheckBox());
            this->numbersBold = (gcnew System::Windows::Forms::CheckBox());
            this->label21 = (gcnew System::Windows::Forms::Label());
            this->stringsColor = (gcnew System::Windows::Forms::TextBox());
            this->stringsItalic = (gcnew System::Windows::Forms::CheckBox());
            this->stringsBold = (gcnew System::Windows::Forms::CheckBox());
            this->label22 = (gcnew System::Windows::Forms::Label());
            this->builtinsColor = (gcnew System::Windows::Forms::TextBox());
            this->builtinsItalic = (gcnew System::Windows::Forms::CheckBox());
            this->builtinsBold = (gcnew System::Windows::Forms::CheckBox());
            this->label23 = (gcnew System::Windows::Forms::Label());
            this->keywordsColor = (gcnew System::Windows::Forms::TextBox());
            this->keywordsItalic = (gcnew System::Windows::Forms::CheckBox());
            this->keywordsBold = (gcnew System::Windows::Forms::CheckBox());
            this->label24 = (gcnew System::Windows::Forms::Label());
            this->label20 = (gcnew System::Windows::Forms::Label());
            this->label19 = (gcnew System::Windows::Forms::Label());
            this->label18 = (gcnew System::Windows::Forms::Label());
            this->label17 = (gcnew System::Windows::Forms::Label());
            this->identifiersColor = (gcnew System::Windows::Forms::TextBox());
            this->identifiersItalic = (gcnew System::Windows::Forms::CheckBox());
            this->identifiersBold = (gcnew System::Windows::Forms::CheckBox());
            this->label16 = (gcnew System::Windows::Forms::Label());
            this->symbolsColor = (gcnew System::Windows::Forms::TextBox());
            this->symbolsItalic = (gcnew System::Windows::Forms::CheckBox());
            this->symbolsBold = (gcnew System::Windows::Forms::CheckBox());
            this->label15 = (gcnew System::Windows::Forms::Label());
            this->commentsColor = (gcnew System::Windows::Forms::TextBox());
            this->commentsItalic = (gcnew System::Windows::Forms::CheckBox());
            this->commentsBold = (gcnew System::Windows::Forms::CheckBox());
            this->label14 = (gcnew System::Windows::Forms::Label());
            this->defaultColor = (gcnew System::Windows::Forms::TextBox());
            this->defaultItalic = (gcnew System::Windows::Forms::CheckBox());
            this->defaultBold = (gcnew System::Windows::Forms::CheckBox());
            this->label13 = (gcnew System::Windows::Forms::Label());
            this->toolTip2 = (gcnew System::Windows::Forms::ToolTip(this->components));
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarBorder))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarTab))->BeginInit();
            this->tabControl1->SuspendLayout();
            this->tabPage1->SuspendLayout();
            this->tabPage2->SuspendLayout();
            this->SuspendLayout();
            // 
            // radioOpenWelcome
            // 
            this->radioOpenWelcome->AutoSize = true;
            this->radioOpenWelcome->Location = System::Drawing::Point(315, 22);
            this->radioOpenWelcome->Margin = System::Windows::Forms::Padding(6);
            this->radioOpenWelcome->Name = L"radioOpenWelcome";
            this->radioOpenWelcome->Size = System::Drawing::Size(290, 29);
            this->radioOpenWelcome->TabIndex = 0;
            this->radioOpenWelcome->TabStop = true;
            this->radioOpenWelcome->Text = L"Open Welcome document";
            this->radioOpenWelcome->UseVisualStyleBackColor = true;
            // 
            // radioOpenNew
            // 
            this->radioOpenNew->AutoSize = true;
            this->radioOpenNew->Location = System::Drawing::Point(315, 68);
            this->radioOpenNew->Margin = System::Windows::Forms::Padding(6);
            this->radioOpenNew->Name = L"radioOpenNew";
            this->radioOpenNew->Size = System::Drawing::Size(240, 29);
            this->radioOpenNew->TabIndex = 1;
            this->radioOpenNew->TabStop = true;
            this->radioOpenNew->Text = L"Open new document";
            this->radioOpenNew->UseVisualStyleBackColor = true;
            // 
            // radioOpenNothing
            // 
            this->radioOpenNothing->AutoSize = true;
            this->radioOpenNothing->Location = System::Drawing::Point(315, 114);
            this->radioOpenNothing->Margin = System::Windows::Forms::Padding(6);
            this->radioOpenNothing->Name = L"radioOpenNothing";
            this->radioOpenNothing->Size = System::Drawing::Size(147, 29);
            this->radioOpenNothing->TabIndex = 2;
            this->radioOpenNothing->TabStop = true;
            this->radioOpenNothing->Text = L"Do nothing";
            this->radioOpenNothing->UseVisualStyleBackColor = true;
            // 
            // checkOpenRender
            // 
            this->checkOpenRender->AutoSize = true;
            this->checkOpenRender->Location = System::Drawing::Point(315, 185);
            this->checkOpenRender->Margin = System::Windows::Forms::Padding(6);
            this->checkOpenRender->Name = L"checkOpenRender";
            this->checkOpenRender->Size = System::Drawing::Size(186, 29);
            this->checkOpenRender->TabIndex = 3;
            this->checkOpenRender->Text = L"Start rendering";
            this->checkOpenRender->UseVisualStyleBackColor = true;
            // 
            // checkRenderUpdate
            // 
            this->checkRenderUpdate->AutoSize = true;
            this->checkRenderUpdate->Location = System::Drawing::Point(315, 257);
            this->checkRenderUpdate->Margin = System::Windows::Forms::Padding(6);
            this->checkRenderUpdate->Name = L"checkRenderUpdate";
            this->checkRenderUpdate->Size = System::Drawing::Size(346, 29);
            this->checkRenderUpdate->TabIndex = 4;
            this->checkRenderUpdate->Text = L"Progressively update the image";
            this->checkRenderUpdate->UseVisualStyleBackColor = true;
            // 
            // trackBarBorder
            // 
            this->trackBarBorder->BackColor = System::Drawing::SystemColors::ControlLightLight;
            this->trackBarBorder->Location = System::Drawing::Point(315, 320);
            this->trackBarBorder->Margin = System::Windows::Forms::Padding(6);
            this->trackBarBorder->Maximum = 99;
            this->trackBarBorder->Name = L"trackBarBorder";
            this->trackBarBorder->Size = System::Drawing::Size(466, 90);
            this->trackBarBorder->TabIndex = 5;
            this->trackBarBorder->TickFrequency = 33;
            // 
            // checkSaveWithVariation
            // 
            this->checkSaveWithVariation->AutoSize = true;
            this->checkSaveWithVariation->Location = System::Drawing::Point(315, 420);
            this->checkSaveWithVariation->Margin = System::Windows::Forms::Padding(6);
            this->checkSaveWithVariation->Name = L"checkSaveWithVariation";
            this->checkSaveWithVariation->Size = System::Drawing::Size(442, 29);
            this->checkSaveWithVariation->TabIndex = 6;
            this->checkSaveWithVariation->Text = L"Include the variation code in the file name";
            this->checkSaveWithVariation->UseVisualStyleBackColor = true;
            // 
            // checkCropImage
            // 
            this->checkCropImage->AutoSize = true;
            this->checkCropImage->Location = System::Drawing::Point(315, 466);
            this->checkCropImage->Margin = System::Windows::Forms::Padding(6);
            this->checkCropImage->Name = L"checkCropImage";
            this->checkCropImage->Size = System::Drawing::Size(190, 29);
            this->checkCropImage->TabIndex = 7;
            this->checkCropImage->Text = L"Crop the image";
            this->checkCropImage->UseVisualStyleBackColor = true;
            // 
            // label10
            // 
            this->label10->AutoSize = true;
            this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label10->Location = System::Drawing::Point(711, 385);
            this->label10->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(73, 22);
            this->label10->TabIndex = 20;
            this->label10->Text = L"variable";
            // 
            // label9
            // 
            this->label9->AutoSize = true;
            this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label9->Location = System::Drawing::Point(591, 385);
            this->label9->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(48, 22);
            this->label9->TabIndex = 19;
            this->label9->Text = L"fixed";
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label8->Location = System::Drawing::Point(455, 385);
            this->label8->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(50, 22);
            this->label8->TabIndex = 18;
            this->label8->Text = L"none";
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label7->Location = System::Drawing::Point(312, 385);
            this->label7->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(78, 22);
            this->label7->TabIndex = 17;
            this->label7->Text = L"negative";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(35, 26);
            this->label1->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(269, 25);
            this->label1->TabIndex = 21;
            this->label1->Text = L"When Context Free opens:";
            this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(9, 187);
            this->label2->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(292, 25);
            this->label2->TabIndex = 22;
            this->label2->Text = L"When a document is opened:";
            this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(135, 259);
            this->label3->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(169, 25);
            this->label3->TabIndex = 23;
            this->label3->Text = L"While rendering:";
            this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(117, 337);
            this->label4->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(189, 25);
            this->label4->TabIndex = 24;
            this->label4->Text = L"Image border size:";
            this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(65, 422);
            this->label5->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(237, 25);
            this->label5->TabIndex = 25;
            this->label5->Text = L"When saving an image:";
            this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(429, 518);
            this->label6->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(136, 25);
            this->label6->TabIndex = 26;
            this->label6->Text = L"JPEG quality";
            this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // buttonOK
            // 
            this->buttonOK->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->buttonOK->Location = System::Drawing::Point(488, 644);
            this->buttonOK->Margin = System::Windows::Forms::Padding(6);
            this->buttonOK->Name = L"buttonOK";
            this->buttonOK->Size = System::Drawing::Size(150, 44);
            this->buttonOK->TabIndex = 100;
            this->buttonOK->Text = L"OK";
            this->buttonOK->UseVisualStyleBackColor = true;
            this->buttonOK->Click += gcnew System::EventHandler(this, &PreferenceDialog::buttonOK_Click);
            // 
            // buttonCancel
            // 
            this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->buttonCancel->Location = System::Drawing::Point(650, 644);
            this->buttonCancel->Margin = System::Windows::Forms::Padding(6);
            this->buttonCancel->Name = L"buttonCancel";
            this->buttonCancel->Size = System::Drawing::Size(150, 44);
            this->buttonCancel->TabIndex = 101;
            this->buttonCancel->Text = L"Cancel";
            this->buttonCancel->UseVisualStyleBackColor = true;
            this->buttonCancel->Click += gcnew System::EventHandler(this, &PreferenceDialog::buttonCancel_Click);
            // 
            // editJPEGquality
            // 
            this->editJPEGquality->BeepOnError = true;
            this->editJPEGquality->HidePromptOnLeave = true;
            this->editJPEGquality->Location = System::Drawing::Point(315, 510);
            this->editJPEGquality->Margin = System::Windows::Forms::Padding(6);
            this->editJPEGquality->Mask = L"###";
            this->editJPEGquality->Name = L"editJPEGquality";
            this->editJPEGquality->Size = System::Drawing::Size(98, 31);
            this->editJPEGquality->TabIndex = 9;
            // 
            // label11
            // 
            this->label11->AutoSize = true;
            this->label11->Location = System::Drawing::Point(75, 30);
            this->label11->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(116, 25);
            this->label11->TabIndex = 27;
            this->label11->Text = L"Editor font:";
            this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // fontDisplay
            // 
            this->fontDisplay->Location = System::Drawing::Point(203, 24);
            this->fontDisplay->Margin = System::Windows::Forms::Padding(6);
            this->fontDisplay->Name = L"fontDisplay";
            this->fontDisplay->ReadOnly = true;
            this->fontDisplay->Size = System::Drawing::Size(300, 31);
            this->fontDisplay->TabIndex = 28;
            this->fontDisplay->TabStop = false;
            // 
            // fontChange
            // 
            this->fontChange->Location = System::Drawing::Point(519, 20);
            this->fontChange->Margin = System::Windows::Forms::Padding(6);
            this->fontChange->Name = L"fontChange";
            this->fontChange->Size = System::Drawing::Size(150, 44);
            this->fontChange->TabIndex = 29;
            this->fontChange->Text = L"Change";
            this->fontChange->UseVisualStyleBackColor = true;
            // 
            // label12
            // 
            this->label12->AutoSize = true;
            this->label12->Location = System::Drawing::Point(23, 86);
            this->label12->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(166, 25);
            this->label12->TabIndex = 32;
            this->label12->Text = L"Editor tab width:";
            this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // trackBarTab
            // 
            this->trackBarTab->BackColor = System::Drawing::SystemColors::ControlLightLight;
            this->trackBarTab->Location = System::Drawing::Point(203, 86);
            this->trackBarTab->Maximum = 8;
            this->trackBarTab->Minimum = 1;
            this->trackBarTab->Name = L"trackBarTab";
            this->trackBarTab->Size = System::Drawing::Size(300, 90);
            this->trackBarTab->TabIndex = 30;
            this->trackBarTab->Value = 4;
            this->trackBarTab->Scroll += gcnew System::EventHandler(this, &PreferenceDialog::tabWidth_scroll);
            // 
            // tabControl1
            // 
            this->tabControl1->Controls->Add(this->tabPage1);
            this->tabControl1->Controls->Add(this->tabPage2);
            this->tabControl1->Location = System::Drawing::Point(12, 12);
            this->tabControl1->Name = L"tabControl1";
            this->tabControl1->SelectedIndex = 0;
            this->tabControl1->Size = System::Drawing::Size(803, 612);
            this->tabControl1->TabIndex = 33;
            // 
            // tabPage1
            // 
            this->tabPage1->Controls->Add(this->label1);
            this->tabPage1->Controls->Add(this->radioOpenWelcome);
            this->tabPage1->Controls->Add(this->radioOpenNew);
            this->tabPage1->Controls->Add(this->editJPEGquality);
            this->tabPage1->Controls->Add(this->radioOpenNothing);
            this->tabPage1->Controls->Add(this->label6);
            this->tabPage1->Controls->Add(this->checkOpenRender);
            this->tabPage1->Controls->Add(this->label5);
            this->tabPage1->Controls->Add(this->checkRenderUpdate);
            this->tabPage1->Controls->Add(this->label4);
            this->tabPage1->Controls->Add(this->label3);
            this->tabPage1->Controls->Add(this->checkSaveWithVariation);
            this->tabPage1->Controls->Add(this->label2);
            this->tabPage1->Controls->Add(this->checkCropImage);
            this->tabPage1->Controls->Add(this->label7);
            this->tabPage1->Controls->Add(this->label10);
            this->tabPage1->Controls->Add(this->label8);
            this->tabPage1->Controls->Add(this->label9);
            this->tabPage1->Controls->Add(this->trackBarBorder);
            this->tabPage1->Location = System::Drawing::Point(8, 39);
            this->tabPage1->Name = L"tabPage1";
            this->tabPage1->Padding = System::Windows::Forms::Padding(3);
            this->tabPage1->Size = System::Drawing::Size(787, 565);
            this->tabPage1->TabIndex = 0;
            this->tabPage1->Text = L"General";
            this->tabPage1->UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this->tabPage2->Controls->Add(this->numbersColor);
            this->tabPage2->Controls->Add(this->numbersItalic);
            this->tabPage2->Controls->Add(this->numbersBold);
            this->tabPage2->Controls->Add(this->label21);
            this->tabPage2->Controls->Add(this->stringsColor);
            this->tabPage2->Controls->Add(this->stringsItalic);
            this->tabPage2->Controls->Add(this->stringsBold);
            this->tabPage2->Controls->Add(this->label22);
            this->tabPage2->Controls->Add(this->builtinsColor);
            this->tabPage2->Controls->Add(this->builtinsItalic);
            this->tabPage2->Controls->Add(this->builtinsBold);
            this->tabPage2->Controls->Add(this->label23);
            this->tabPage2->Controls->Add(this->keywordsColor);
            this->tabPage2->Controls->Add(this->keywordsItalic);
            this->tabPage2->Controls->Add(this->keywordsBold);
            this->tabPage2->Controls->Add(this->label24);
            this->tabPage2->Controls->Add(this->label20);
            this->tabPage2->Controls->Add(this->label19);
            this->tabPage2->Controls->Add(this->label18);
            this->tabPage2->Controls->Add(this->label17);
            this->tabPage2->Controls->Add(this->identifiersColor);
            this->tabPage2->Controls->Add(this->identifiersItalic);
            this->tabPage2->Controls->Add(this->identifiersBold);
            this->tabPage2->Controls->Add(this->label16);
            this->tabPage2->Controls->Add(this->symbolsColor);
            this->tabPage2->Controls->Add(this->symbolsItalic);
            this->tabPage2->Controls->Add(this->symbolsBold);
            this->tabPage2->Controls->Add(this->label15);
            this->tabPage2->Controls->Add(this->commentsColor);
            this->tabPage2->Controls->Add(this->commentsItalic);
            this->tabPage2->Controls->Add(this->commentsBold);
            this->tabPage2->Controls->Add(this->label14);
            this->tabPage2->Controls->Add(this->defaultColor);
            this->tabPage2->Controls->Add(this->defaultItalic);
            this->tabPage2->Controls->Add(this->defaultBold);
            this->tabPage2->Controls->Add(this->label13);
            this->tabPage2->Controls->Add(this->fontChange);
            this->tabPage2->Controls->Add(this->label11);
            this->tabPage2->Controls->Add(this->fontDisplay);
            this->tabPage2->Controls->Add(this->trackBarTab);
            this->tabPage2->Controls->Add(this->label12);
            this->tabPage2->Location = System::Drawing::Point(8, 39);
            this->tabPage2->Name = L"tabPage2";
            this->tabPage2->Padding = System::Windows::Forms::Padding(3);
            this->tabPage2->Size = System::Drawing::Size(787, 565);
            this->tabPage2->TabIndex = 1;
            this->tabPage2->Text = L"Editor";
            this->tabPage2->UseVisualStyleBackColor = true;
            // 
            // numbersColor
            // 
            this->numbersColor->Location = System::Drawing::Point(219, 508);
            this->numbersColor->Name = L"numbersColor";
            this->numbersColor->Size = System::Drawing::Size(100, 31);
            this->numbersColor->TabIndex = 68;
            this->numbersColor->Text = L"#FFFFFF";
            this->numbersColor->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &PreferenceDialog::ValidateColor);
            // 
            // numbersItalic
            // 
            this->numbersItalic->AutoSize = true;
            this->numbersItalic->Location = System::Drawing::Point(184, 510);
            this->numbersItalic->Name = L"numbersItalic";
            this->numbersItalic->Size = System::Drawing::Size(28, 27);
            this->numbersItalic->TabIndex = 67;
            this->numbersItalic->UseVisualStyleBackColor = true;
            this->numbersItalic->Enter += gcnew System::EventHandler(this, &PreferenceDialog::FocusCheck);
            this->numbersItalic->Leave += gcnew System::EventHandler(this, &PreferenceDialog::BlurCheck);
            // 
            // numbersBold
            // 
            this->numbersBold->AutoSize = true;
            this->numbersBold->Location = System::Drawing::Point(150, 510);
            this->numbersBold->Name = L"numbersBold";
            this->numbersBold->Size = System::Drawing::Size(28, 27);
            this->numbersBold->TabIndex = 66;
            this->numbersBold->UseVisualStyleBackColor = true;
            this->numbersBold->Enter += gcnew System::EventHandler(this, &PreferenceDialog::FocusCheck);
            this->numbersBold->Leave += gcnew System::EventHandler(this, &PreferenceDialog::BlurCheck);
            // 
            // label21
            // 
            this->label21->AutoSize = true;
            this->label21->Location = System::Drawing::Point(47, 510);
            this->label21->Name = L"label21";
            this->label21->Size = System::Drawing::Size(98, 25);
            this->label21->TabIndex = 65;
            this->label21->Text = L"Numbers";
            // 
            // stringsColor
            // 
            this->stringsColor->Location = System::Drawing::Point(219, 471);
            this->stringsColor->Name = L"stringsColor";
            this->stringsColor->Size = System::Drawing::Size(100, 31);
            this->stringsColor->TabIndex = 64;
            this->stringsColor->Text = L"#FFFFFF";
            this->stringsColor->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &PreferenceDialog::ValidateColor);
            // 
            // stringsItalic
            // 
            this->stringsItalic->AutoSize = true;
            this->stringsItalic->Location = System::Drawing::Point(184, 473);
            this->stringsItalic->Name = L"stringsItalic";
            this->stringsItalic->Size = System::Drawing::Size(28, 27);
            this->stringsItalic->TabIndex = 63;
            this->stringsItalic->UseVisualStyleBackColor = true;
            this->stringsItalic->Enter += gcnew System::EventHandler(this, &PreferenceDialog::FocusCheck);
            this->stringsItalic->Leave += gcnew System::EventHandler(this, &PreferenceDialog::BlurCheck);
            // 
            // stringsBold
            // 
            this->stringsBold->AutoSize = true;
            this->stringsBold->Location = System::Drawing::Point(150, 473);
            this->stringsBold->Name = L"stringsBold";
            this->stringsBold->Size = System::Drawing::Size(28, 27);
            this->stringsBold->TabIndex = 62;
            this->stringsBold->UseVisualStyleBackColor = true;
            this->stringsBold->Enter += gcnew System::EventHandler(this, &PreferenceDialog::FocusCheck);
            this->stringsBold->Leave += gcnew System::EventHandler(this, &PreferenceDialog::BlurCheck);
            // 
            // label22
            // 
            this->label22->AutoSize = true;
            this->label22->Location = System::Drawing::Point(27, 473);
            this->label22->Name = L"label22";
            this->label22->Size = System::Drawing::Size(117, 25);
            this->label22->TabIndex = 61;
            this->label22->Text = L"File names";
            // 
            // builtinsColor
            // 
            this->builtinsColor->Location = System::Drawing::Point(219, 434);
            this->builtinsColor->Name = L"builtinsColor";
            this->builtinsColor->Size = System::Drawing::Size(100, 31);
            this->builtinsColor->TabIndex = 60;
            this->builtinsColor->Text = L"#FFFFFF";
            this->builtinsColor->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &PreferenceDialog::ValidateColor);
            // 
            // builtinsItalic
            // 
            this->builtinsItalic->AutoSize = true;
            this->builtinsItalic->Location = System::Drawing::Point(184, 436);
            this->builtinsItalic->Name = L"builtinsItalic";
            this->builtinsItalic->Size = System::Drawing::Size(28, 27);
            this->builtinsItalic->TabIndex = 59;
            this->builtinsItalic->UseVisualStyleBackColor = true;
            this->builtinsItalic->Enter += gcnew System::EventHandler(this, &PreferenceDialog::FocusCheck);
            this->builtinsItalic->Leave += gcnew System::EventHandler(this, &PreferenceDialog::BlurCheck);
            // 
            // builtinsBold
            // 
            this->builtinsBold->AutoSize = true;
            this->builtinsBold->Location = System::Drawing::Point(150, 436);
            this->builtinsBold->Name = L"builtinsBold";
            this->builtinsBold->Size = System::Drawing::Size(28, 27);
            this->builtinsBold->TabIndex = 58;
            this->builtinsBold->UseVisualStyleBackColor = true;
            this->builtinsBold->Enter += gcnew System::EventHandler(this, &PreferenceDialog::FocusCheck);
            this->builtinsBold->Leave += gcnew System::EventHandler(this, &PreferenceDialog::BlurCheck);
            // 
            // label23
            // 
            this->label23->AutoSize = true;
            this->label23->Location = System::Drawing::Point(55, 436);
            this->label23->Name = L"label23";
            this->label23->Size = System::Drawing::Size(89, 25);
            this->label23->TabIndex = 57;
            this->label23->Text = L"Built-ins";
            // 
            // keywordsColor
            // 
            this->keywordsColor->Location = System::Drawing::Point(219, 397);
            this->keywordsColor->Name = L"keywordsColor";
            this->keywordsColor->Size = System::Drawing::Size(100, 31);
            this->keywordsColor->TabIndex = 56;
            this->keywordsColor->Text = L"#FFFFFF";
            this->keywordsColor->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &PreferenceDialog::ValidateColor);
            // 
            // keywordsItalic
            // 
            this->keywordsItalic->AutoSize = true;
            this->keywordsItalic->Location = System::Drawing::Point(184, 399);
            this->keywordsItalic->Name = L"keywordsItalic";
            this->keywordsItalic->Size = System::Drawing::Size(28, 27);
            this->keywordsItalic->TabIndex = 55;
            this->keywordsItalic->UseVisualStyleBackColor = true;
            this->keywordsItalic->Enter += gcnew System::EventHandler(this, &PreferenceDialog::FocusCheck);
            this->keywordsItalic->Leave += gcnew System::EventHandler(this, &PreferenceDialog::BlurCheck);
            // 
            // keywordsBold
            // 
            this->keywordsBold->AutoSize = true;
            this->keywordsBold->Location = System::Drawing::Point(150, 399);
            this->keywordsBold->Name = L"keywordsBold";
            this->keywordsBold->Size = System::Drawing::Size(28, 27);
            this->keywordsBold->TabIndex = 54;
            this->keywordsBold->UseVisualStyleBackColor = true;
            this->keywordsBold->Enter += gcnew System::EventHandler(this, &PreferenceDialog::FocusCheck);
            this->keywordsBold->Leave += gcnew System::EventHandler(this, &PreferenceDialog::BlurCheck);
            // 
            // label24
            // 
            this->label24->AutoSize = true;
            this->label24->Location = System::Drawing::Point(39, 399);
            this->label24->Name = L"label24";
            this->label24->Size = System::Drawing::Size(106, 25);
            this->label24->TabIndex = 53;
            this->label24->Text = L"Keywords";
            // 
            // label20
            // 
            this->label20->AutoSize = true;
            this->label20->Location = System::Drawing::Point(219, 207);
            this->label20->Name = L"label20";
            this->label20->Size = System::Drawing::Size(63, 25);
            this->label20->TabIndex = 52;
            this->label20->Text = L"Color";
            // 
            // label19
            // 
            this->label19->AutoSize = true;
            this->label19->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10.125F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label19->Location = System::Drawing::Point(181, 204);
            this->label19->Name = L"label19";
            this->label19->Size = System::Drawing::Size(23, 31);
            this->label19->TabIndex = 51;
            this->label19->Text = L"I";
            // 
            // label18
            // 
            this->label18->AutoSize = true;
            this->label18->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10.125F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label18->Location = System::Drawing::Point(147, 204);
            this->label18->Name = L"label18";
            this->label18->Size = System::Drawing::Size(32, 31);
            this->label18->TabIndex = 50;
            this->label18->Text = L"B";
            // 
            // label17
            // 
            this->label17->AutoSize = true;
            this->label17->Location = System::Drawing::Point(84, 207);
            this->label17->Name = L"label17";
            this->label17->Size = System::Drawing::Size(60, 25);
            this->label17->TabIndex = 49;
            this->label17->Text = L"Style";
            // 
            // identifiersColor
            // 
            this->identifiersColor->Location = System::Drawing::Point(219, 360);
            this->identifiersColor->Name = L"identifiersColor";
            this->identifiersColor->Size = System::Drawing::Size(100, 31);
            this->identifiersColor->TabIndex = 48;
            this->identifiersColor->Text = L"#FFFFFF";
            this->identifiersColor->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &PreferenceDialog::ValidateColor);
            // 
            // identifiersItalic
            // 
            this->identifiersItalic->AutoSize = true;
            this->identifiersItalic->Location = System::Drawing::Point(184, 362);
            this->identifiersItalic->Name = L"identifiersItalic";
            this->identifiersItalic->Size = System::Drawing::Size(28, 27);
            this->identifiersItalic->TabIndex = 47;
            this->identifiersItalic->UseVisualStyleBackColor = true;
            this->identifiersItalic->Enter += gcnew System::EventHandler(this, &PreferenceDialog::FocusCheck);
            this->identifiersItalic->Leave += gcnew System::EventHandler(this, &PreferenceDialog::BlurCheck);
            // 
            // identifiersBold
            // 
            this->identifiersBold->AutoSize = true;
            this->identifiersBold->Location = System::Drawing::Point(150, 362);
            this->identifiersBold->Name = L"identifiersBold";
            this->identifiersBold->Size = System::Drawing::Size(28, 27);
            this->identifiersBold->TabIndex = 46;
            this->identifiersBold->UseVisualStyleBackColor = true;
            this->identifiersBold->Enter += gcnew System::EventHandler(this, &PreferenceDialog::FocusCheck);
            this->identifiersBold->Leave += gcnew System::EventHandler(this, &PreferenceDialog::BlurCheck);
            // 
            // label16
            // 
            this->label16->AutoSize = true;
            this->label16->Location = System::Drawing::Point(51, 362);
            this->label16->Name = L"label16";
            this->label16->Size = System::Drawing::Size(94, 25);
            this->label16->TabIndex = 45;
            this->label16->Text = L"Identiers";
            // 
            // symbolsColor
            // 
            this->symbolsColor->Location = System::Drawing::Point(219, 323);
            this->symbolsColor->Name = L"symbolsColor";
            this->symbolsColor->Size = System::Drawing::Size(100, 31);
            this->symbolsColor->TabIndex = 44;
            this->symbolsColor->Text = L"#FFFFFF";
            this->symbolsColor->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &PreferenceDialog::ValidateColor);
            // 
            // symbolsItalic
            // 
            this->symbolsItalic->AutoSize = true;
            this->symbolsItalic->Location = System::Drawing::Point(184, 325);
            this->symbolsItalic->Name = L"symbolsItalic";
            this->symbolsItalic->Size = System::Drawing::Size(28, 27);
            this->symbolsItalic->TabIndex = 43;
            this->symbolsItalic->UseVisualStyleBackColor = true;
            this->symbolsItalic->Enter += gcnew System::EventHandler(this, &PreferenceDialog::FocusCheck);
            this->symbolsItalic->Leave += gcnew System::EventHandler(this, &PreferenceDialog::BlurCheck);
            // 
            // symbolsBold
            // 
            this->symbolsBold->AutoSize = true;
            this->symbolsBold->Location = System::Drawing::Point(150, 325);
            this->symbolsBold->Name = L"symbolsBold";
            this->symbolsBold->Size = System::Drawing::Size(28, 27);
            this->symbolsBold->TabIndex = 42;
            this->symbolsBold->UseVisualStyleBackColor = true;
            this->symbolsBold->Enter += gcnew System::EventHandler(this, &PreferenceDialog::FocusCheck);
            this->symbolsBold->Leave += gcnew System::EventHandler(this, &PreferenceDialog::BlurCheck);
            // 
            // label15
            // 
            this->label15->AutoSize = true;
            this->label15->Location = System::Drawing::Point(51, 325);
            this->label15->Name = L"label15";
            this->label15->Size = System::Drawing::Size(94, 25);
            this->label15->TabIndex = 41;
            this->label15->Text = L"Symbols";
            // 
            // commentsColor
            // 
            this->commentsColor->Location = System::Drawing::Point(219, 286);
            this->commentsColor->Name = L"commentsColor";
            this->commentsColor->Size = System::Drawing::Size(100, 31);
            this->commentsColor->TabIndex = 40;
            this->commentsColor->Text = L"#FFFFFF";
            this->commentsColor->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &PreferenceDialog::ValidateColor);
            // 
            // commentsItalic
            // 
            this->commentsItalic->AutoSize = true;
            this->commentsItalic->Location = System::Drawing::Point(184, 288);
            this->commentsItalic->Name = L"commentsItalic";
            this->commentsItalic->Size = System::Drawing::Size(28, 27);
            this->commentsItalic->TabIndex = 39;
            this->commentsItalic->UseVisualStyleBackColor = true;
            this->commentsItalic->Enter += gcnew System::EventHandler(this, &PreferenceDialog::FocusCheck);
            this->commentsItalic->Leave += gcnew System::EventHandler(this, &PreferenceDialog::BlurCheck);
            // 
            // commentsBold
            // 
            this->commentsBold->AutoSize = true;
            this->commentsBold->Location = System::Drawing::Point(150, 288);
            this->commentsBold->Name = L"commentsBold";
            this->commentsBold->Size = System::Drawing::Size(28, 27);
            this->commentsBold->TabIndex = 38;
            this->commentsBold->UseVisualStyleBackColor = true;
            this->commentsBold->Enter += gcnew System::EventHandler(this, &PreferenceDialog::FocusCheck);
            this->commentsBold->Leave += gcnew System::EventHandler(this, &PreferenceDialog::BlurCheck);
            // 
            // label14
            // 
            this->label14->AutoSize = true;
            this->label14->Location = System::Drawing::Point(31, 288);
            this->label14->Name = L"label14";
            this->label14->Size = System::Drawing::Size(114, 25);
            this->label14->TabIndex = 37;
            this->label14->Text = L"Comments";
            // 
            // defaultColor
            // 
            this->defaultColor->Location = System::Drawing::Point(219, 249);
            this->defaultColor->Name = L"defaultColor";
            this->defaultColor->Size = System::Drawing::Size(100, 31);
            this->defaultColor->TabIndex = 36;
            this->defaultColor->Text = L"#FFFFFF";
            this->defaultColor->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &PreferenceDialog::ValidateColor);
            // 
            // defaultItalic
            // 
            this->defaultItalic->AutoSize = true;
            this->defaultItalic->Location = System::Drawing::Point(184, 251);
            this->defaultItalic->Name = L"defaultItalic";
            this->defaultItalic->Size = System::Drawing::Size(28, 27);
            this->defaultItalic->TabIndex = 35;
            this->defaultItalic->UseVisualStyleBackColor = true;
            this->defaultItalic->Enter += gcnew System::EventHandler(this, &PreferenceDialog::FocusCheck);
            this->defaultItalic->Leave += gcnew System::EventHandler(this, &PreferenceDialog::BlurCheck);
            // 
            // defaultBold
            // 
            this->defaultBold->AutoSize = true;
            this->defaultBold->BackColor = System::Drawing::Color::Transparent;
            this->defaultBold->ForeColor = System::Drawing::SystemColors::ControlText;
            this->defaultBold->Location = System::Drawing::Point(150, 251);
            this->defaultBold->Name = L"defaultBold";
            this->defaultBold->Size = System::Drawing::Size(28, 27);
            this->defaultBold->TabIndex = 34;
            this->defaultBold->UseVisualStyleBackColor = false;
            this->defaultBold->Enter += gcnew System::EventHandler(this, &PreferenceDialog::FocusCheck);
            this->defaultBold->Leave += gcnew System::EventHandler(this, &PreferenceDialog::BlurCheck);
            // 
            // label13
            // 
            this->label13->AutoSize = true;
            this->label13->Location = System::Drawing::Point(64, 251);
            this->label13->Name = L"label13";
            this->label13->Size = System::Drawing::Size(80, 25);
            this->label13->TabIndex = 33;
            this->label13->Text = L"Default";
            // 
            // PreferenceDialog
            // 
            this->AcceptButton = this->buttonOK;
            this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->CancelButton = this->buttonCancel;
            this->ClientSize = System::Drawing::Size(824, 714);
            this->Controls->Add(this->tabControl1);
            this->Controls->Add(this->buttonCancel);
            this->Controls->Add(this->buttonOK);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->Margin = System::Windows::Forms::Padding(6);
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"PreferenceDialog";
            this->ShowInTaskbar = false;
            this->Text = L"Context Free Preferences";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarBorder))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarTab))->EndInit();
            this->tabControl1->ResumeLayout(false);
            this->tabPage1->ResumeLayout(false);
            this->tabPage1->PerformLayout();
            this->tabPage2->ResumeLayout(false);
            this->tabPage2->PerformLayout();
            this->ResumeLayout(false);

        }
#pragma endregion
private: 
    System::Void setup_dialog(System::Object^  sender, System::EventArgs^  e) 
    {
        radioOpenWelcome->Checked = prefs->StartupDocument == CFPrefs::OpenAction::Welcome;
        radioOpenNew->Checked = prefs->StartupDocument == CFPrefs::OpenAction::New;
        radioOpenNothing->Checked = prefs->StartupDocument == CFPrefs::OpenAction::Nothing;
        checkOpenRender->Checked = prefs->RenderOnOpen;
        checkRenderUpdate->Checked = prefs->ProgressiveRender;
        trackBarBorder->Value = (int)((prefs->BorderWidth + 1.0) * 33.0);
        checkSaveWithVariation->Checked = prefs->ImageAppendVariation;
        checkCropImage->Checked = prefs->ImageCrop;
        editJPEGquality->Text = prefs->JPEGQuality.ToString();
        trackBarTab->Value = prefs->TabWidth;

        defaultBold->Checked = prefs->StyleDefaultBold;
        commentsBold->Checked = prefs->StyleCommentsBold;
        symbolsBold->Checked = prefs->StyleSymbolsBold;
        identifiersBold->Checked = prefs->StyleIdentifiersBold;
        keywordsBold->Checked = prefs->StyleKeywordsBold;
        builtinsBold->Checked = prefs->StyleBuiltinsBold;
        stringsBold->Checked = prefs->StyleStringsBold;
        numbersBold->Checked = prefs->StyleNumbersBold;

        defaultItalic->Checked = prefs->StyleDefaultItalic;
        commentsItalic->Checked = prefs->StyleCommentsItalic;
        symbolsItalic->Checked = prefs->StyleSymbolsItalic;
        identifiersItalic->Checked = prefs->StyleIdentifiersItalic;
        keywordsItalic->Checked = prefs->StyleKeywordsItalic;
        builtinsItalic->Checked = prefs->StyleBuiltinsItalic;
        stringsItalic->Checked = prefs->StyleStringsItalic;
        numbersItalic->Checked = prefs->StyleNumbersItalic;

        defaultColor->Text = prefs->StyleDefaultColor;
        commentsColor->Text = prefs->StyleCommentsColor;
        symbolsColor->Text = prefs->StyleSymbolsColor;
        identifiersColor->Text = prefs->StyleIdentifiersColor;
        keywordsColor->Text = prefs->StyleKeywordsColor;
        builtinsColor->Text = prefs->StyleBuiltinsColor;
        stringsColor->Text = prefs->StyleStringsColor;
        numbersColor->Text = prefs->StyleNumbersColor;
    }

private: 
    System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e) 
    {
        if (radioOpenWelcome->Checked) prefs->StartupDocument = CFPrefs::OpenAction::Welcome;
        if (radioOpenNew->Checked) prefs->StartupDocument = CFPrefs::OpenAction::New;
        if (radioOpenNothing->Checked) prefs->StartupDocument = CFPrefs::OpenAction::Nothing;
        prefs->RenderOnOpen = checkOpenRender->Checked;
        prefs->ProgressiveRender = checkRenderUpdate->Checked;
        prefs->BorderWidth = (double)(trackBarBorder->Value) / 33.0 - 1.0;
        prefs->ImageAppendVariation = checkSaveWithVariation->Checked;
        prefs->ImageCrop = checkCropImage->Checked;
        prefs->TabWidth = trackBarTab->Value;
        try {
            prefs->JPEGQuality = System::Int32::Parse(editJPEGquality->Text);
        } catch (System::SystemException^) { }

        prefs->StyleDefaultBold = defaultBold->Checked;
        prefs->StyleCommentsBold = commentsBold->Checked;
        prefs->StyleSymbolsBold = symbolsBold->Checked;
        prefs->StyleIdentifiersBold = identifiersBold->Checked;
        prefs->StyleKeywordsBold = keywordsBold->Checked;
        prefs->StyleBuiltinsBold = builtinsBold->Checked;
        prefs->StyleStringsBold = stringsBold->Checked;
        prefs->StyleNumbersBold = numbersBold->Checked;

        prefs->StyleDefaultItalic = defaultItalic->Checked;
        prefs->StyleCommentsItalic = commentsItalic->Checked;
        prefs->StyleSymbolsItalic = symbolsItalic->Checked;
        prefs->StyleIdentifiersItalic = identifiersItalic->Checked;
        prefs->StyleKeywordsItalic = keywordsItalic->Checked;
        prefs->StyleBuiltinsItalic = builtinsItalic->Checked;
        prefs->StyleStringsItalic = stringsItalic->Checked;
        prefs->StyleNumbersItalic = numbersItalic->Checked;

        prefs->StyleDefaultColor = defaultColor->Text;
        prefs->StyleCommentsColor = commentsColor->Text;
        prefs->StyleSymbolsColor = symbolsColor->Text;
        prefs->StyleIdentifiersColor = identifiersColor->Text;
        prefs->StyleKeywordsColor = keywordsColor->Text;
        prefs->StyleBuiltinsColor = builtinsColor->Text;
        prefs->StyleStringsColor = stringsColor->Text;
        prefs->StyleNumbersColor = numbersColor->Text;

        this->Close();
    }
private: 
    System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e) 
    {
        this->Close();
    }
private: System::Void tabWidth_scroll(System::Object^  sender, System::EventArgs^  e) {
    this->toolTip1->SetToolTip(trackBarTab, trackBarTab->Value.ToString());
}


private: System::Void ValidateColor(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
    if (this->DialogResult != System::Windows::Forms::DialogResult::None)
        return;
    if (System::Windows::Forms::TextBox^ tb = 
        dynamic_cast<System::Windows::Forms::TextBox^>(sender))
    {
        try {
            System::Drawing::Color c = System::Drawing::ColorTranslator::FromHtml(tb->Text);
            System::Console::WriteLine(c.ToString());
        } catch (System::Exception^) {
            e->Cancel = true;
            toolTip2->Show("This is not a valid HTML color", tb, -30, 30, 5000);
        }
    }
}
private: System::Void FocusCheck(System::Object^  sender, System::EventArgs^  e) {
    if (System::Windows::Forms::CheckBox^ box =
        dynamic_cast<System::Windows::Forms::CheckBox^>(sender))
    {
        box->BackColor = System::Drawing::Color::Blue;
    }
}
private: System::Void BlurCheck(System::Object^  sender, System::EventArgs^  e) {
    if (System::Windows::Forms::CheckBox^ box =
        dynamic_cast<System::Windows::Forms::CheckBox^>(sender))
    {
        box->BackColor = System::Drawing::Color::Transparent;
    }
}
};
}
