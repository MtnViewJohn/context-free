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
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarBorder))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarTab))->BeginInit();
            this->SuspendLayout();
            // 
            // radioOpenWelcome
            // 
            this->radioOpenWelcome->AutoSize = true;
            this->radioOpenWelcome->Location = System::Drawing::Point(334, 25);
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
            this->radioOpenNew->Location = System::Drawing::Point(334, 71);
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
            this->radioOpenNothing->Location = System::Drawing::Point(334, 117);
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
            this->checkOpenRender->Location = System::Drawing::Point(334, 188);
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
            this->checkRenderUpdate->Location = System::Drawing::Point(334, 260);
            this->checkRenderUpdate->Margin = System::Windows::Forms::Padding(6);
            this->checkRenderUpdate->Name = L"checkRenderUpdate";
            this->checkRenderUpdate->Size = System::Drawing::Size(346, 29);
            this->checkRenderUpdate->TabIndex = 4;
            this->checkRenderUpdate->Text = L"Progressively update the image";
            this->checkRenderUpdate->UseVisualStyleBackColor = true;
            // 
            // trackBarBorder
            // 
            this->trackBarBorder->Location = System::Drawing::Point(334, 323);
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
            this->checkSaveWithVariation->Location = System::Drawing::Point(334, 423);
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
            this->checkCropImage->Location = System::Drawing::Point(334, 469);
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
            this->label10->Location = System::Drawing::Point(734, 388);
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
            this->label9->Location = System::Drawing::Point(610, 388);
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
            this->label8->Location = System::Drawing::Point(474, 388);
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
            this->label7->Location = System::Drawing::Point(322, 388);
            this->label7->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(78, 22);
            this->label7->TabIndex = 17;
            this->label7->Text = L"negative";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(54, 29);
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
            this->label2->Location = System::Drawing::Point(28, 190);
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
            this->label3->Location = System::Drawing::Point(154, 262);
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
            this->label4->Location = System::Drawing::Point(136, 340);
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
            this->label5->Location = System::Drawing::Point(84, 425);
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
            this->label6->Location = System::Drawing::Point(448, 521);
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
            this->buttonOK->Location = System::Drawing::Point(488, 703);
            this->buttonOK->Margin = System::Windows::Forms::Padding(6);
            this->buttonOK->Name = L"buttonOK";
            this->buttonOK->Size = System::Drawing::Size(150, 44);
            this->buttonOK->TabIndex = 31;
            this->buttonOK->Text = L"OK";
            this->buttonOK->UseVisualStyleBackColor = true;
            this->buttonOK->Click += gcnew System::EventHandler(this, &PreferenceDialog::buttonOK_Click);
            // 
            // buttonCancel
            // 
            this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->buttonCancel->Location = System::Drawing::Point(650, 703);
            this->buttonCancel->Margin = System::Windows::Forms::Padding(6);
            this->buttonCancel->Name = L"buttonCancel";
            this->buttonCancel->Size = System::Drawing::Size(150, 44);
            this->buttonCancel->TabIndex = 32;
            this->buttonCancel->Text = L"Cancel";
            this->buttonCancel->UseVisualStyleBackColor = true;
            this->buttonCancel->Click += gcnew System::EventHandler(this, &PreferenceDialog::buttonCancel_Click);
            // 
            // editJPEGquality
            // 
            this->editJPEGquality->BeepOnError = true;
            this->editJPEGquality->HidePromptOnLeave = true;
            this->editJPEGquality->Location = System::Drawing::Point(334, 513);
            this->editJPEGquality->Margin = System::Windows::Forms::Padding(6);
            this->editJPEGquality->Mask = L"###";
            this->editJPEGquality->Name = L"editJPEGquality";
            this->editJPEGquality->Size = System::Drawing::Size(98, 31);
            this->editJPEGquality->TabIndex = 9;
            // 
            // label11
            // 
            this->label11->AutoSize = true;
            this->label11->Location = System::Drawing::Point(206, 581);
            this->label11->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(116, 25);
            this->label11->TabIndex = 27;
            this->label11->Text = L"Editor font:";
            this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // fontDisplay
            // 
            this->fontDisplay->Location = System::Drawing::Point(334, 575);
            this->fontDisplay->Margin = System::Windows::Forms::Padding(6);
            this->fontDisplay->Name = L"fontDisplay";
            this->fontDisplay->ReadOnly = true;
            this->fontDisplay->Size = System::Drawing::Size(300, 31);
            this->fontDisplay->TabIndex = 28;
            this->fontDisplay->TabStop = false;
            // 
            // fontChange
            // 
            this->fontChange->Location = System::Drawing::Point(650, 571);
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
            this->label12->Location = System::Drawing::Point(154, 637);
            this->label12->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(166, 25);
            this->label12->TabIndex = 32;
            this->label12->Text = L"Editor tab width:";
            this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // trackBarTab
            // 
            this->trackBarTab->Location = System::Drawing::Point(334, 637);
            this->trackBarTab->Maximum = 8;
            this->trackBarTab->Minimum = 1;
            this->trackBarTab->Name = L"trackBarTab";
            this->trackBarTab->Size = System::Drawing::Size(300, 90);
            this->trackBarTab->TabIndex = 30;
            this->trackBarTab->Value = 4;
            this->trackBarTab->Scroll += gcnew System::EventHandler(this, &PreferenceDialog::tabWidth_scroll);
            // 
            // PreferenceDialog
            // 
            this->AcceptButton = this->buttonOK;
            this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->CancelButton = this->buttonCancel;
            this->ClientSize = System::Drawing::Size(824, 776);
            this->Controls->Add(this->buttonCancel);
            this->Controls->Add(this->buttonOK);
            this->Controls->Add(this->trackBarTab);
            this->Controls->Add(this->label12);
            this->Controls->Add(this->fontChange);
            this->Controls->Add(this->fontDisplay);
            this->Controls->Add(this->label11);
            this->Controls->Add(this->editJPEGquality);
            this->Controls->Add(this->label6);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->label10);
            this->Controls->Add(this->label9);
            this->Controls->Add(this->label8);
            this->Controls->Add(this->label7);
            this->Controls->Add(this->checkCropImage);
            this->Controls->Add(this->checkSaveWithVariation);
            this->Controls->Add(this->trackBarBorder);
            this->Controls->Add(this->checkRenderUpdate);
            this->Controls->Add(this->checkOpenRender);
            this->Controls->Add(this->radioOpenNothing);
            this->Controls->Add(this->radioOpenNew);
            this->Controls->Add(this->radioOpenWelcome);
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
            this->ResumeLayout(false);
            this->PerformLayout();

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
};
}
