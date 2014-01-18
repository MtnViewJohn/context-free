// RenderSizeDialog.h
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

#include "Form1.h"

namespace ContextFreeNet {

    public value class RenderParameters
    {
    public:
        enum class RenderActions { Render, Animate, SaveSVG };
        RenderActions action;
        bool    periodicUpdate;
        bool	animateZoom;
        bool    suppressDisplay;
        int		animateFrameCount;
        int     width;
        int     height;
        double  minimumSize;
        double  borderSize;

        void initFromPrefs()
        {
            periodicUpdate = Form1::prefs->ProgressiveRender;
            suppressDisplay = Form1::prefs->DontDisplay;
            animateZoom = Form1::prefs->AnimateZoom;
            width = Form1::prefs->RenderWidth;
            height = Form1::prefs->RenderHeight;
            borderSize = Form1::prefs->BorderWidth;
            minimumSize = Form1::prefs->MinimumSize;
        }

        void saveToPrefs()
        {
            Form1::prefs->ProgressiveRender = periodicUpdate;
            Form1::prefs->DontDisplay = suppressDisplay;
            Form1::prefs->AnimateZoom = animateZoom;
            Form1::prefs->RenderWidth = width;
            Form1::prefs->RenderHeight = height;
            Form1::prefs->BorderWidth = borderSize;
            Form1::prefs->MinimumSize = minimumSize;
        }
    };

	/// <summary>
	/// Summary for RenderSizeDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class RenderSizeDialog : public System::Windows::Forms::Form
	{
	public:
		RenderSizeDialog(RenderParameters* rsp)
        : renderSizeParameters(rsp)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
            this->Activated += gcnew System::EventHandler(this, &RenderSizeDialog::setup_dialog);
		}
    private: System::Windows::Forms::TextBox^  widthBox;
    public: 
    private: System::Windows::Forms::TextBox^  heightBox;

        RenderParameters* renderSizeParameters;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~RenderSizeDialog()
		{
			if (components)
			{
				delete components;
			}
		}


    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::Label^  label3;

    private: System::Windows::Forms::Label^  label4;
    private: System::Windows::Forms::Label^  label5;
    private: System::Windows::Forms::Label^  label6;
    private: System::Windows::Forms::TrackBar^  borderTrackBar;
    private: System::Windows::Forms::CheckBox^  noDisplayCheckBox;
    private: System::Windows::Forms::Label^  label7;
    private: System::Windows::Forms::Label^  label8;
    private: System::Windows::Forms::Label^  label9;
    private: System::Windows::Forms::Label^  label10;
    private: System::Windows::Forms::Label^  label11;
    private: System::Windows::Forms::Label^  label12;
    private: System::Windows::Forms::Button^  OKbutton;
    private: System::Windows::Forms::Button^  cancelButton;
    private: System::Windows::Forms::TextBox^  minimumSizeBox;
    protected: 

    protected: 

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
            System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(RenderSizeDialog::typeid));
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->borderTrackBar = (gcnew System::Windows::Forms::TrackBar());
            this->noDisplayCheckBox = (gcnew System::Windows::Forms::CheckBox());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->OKbutton = (gcnew System::Windows::Forms::Button());
            this->cancelButton = (gcnew System::Windows::Forms::Button());
            this->minimumSizeBox = (gcnew System::Windows::Forms::TextBox());
            this->widthBox = (gcnew System::Windows::Forms::TextBox());
            this->heightBox = (gcnew System::Windows::Forms::TextBox());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->borderTrackBar))->BeginInit();
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(35, 96);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(35, 13);
            this->label1->TabIndex = 3;
            this->label1->Text = L"Width";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(112, 96);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(38, 13);
            this->label2->TabIndex = 4;
            this->label2->Text = L"Height";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(76, 159);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(117, 13);
            this->label3->TabIndex = 10;
            this->label3->Text = L"size of smallest element";
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(156, 115);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(44, 13);
            this->label4->TabIndex = 8;
            this->label4->Text = L"in pixels";
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Font = (gcnew System::Drawing::Font(L"Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(2)));
            this->label5->Location = System::Drawing::Point(74, 113);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(17, 16);
            this->label5->TabIndex = 6;
            this->label5->Text = L"´";
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(12, 200);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(93, 13);
            this->label6->TabIndex = 11;
            this->label6->Text = L"Image border size:";
            // 
            // borderTrackBar
            // 
            this->borderTrackBar->Location = System::Drawing::Point(15, 216);
            this->borderTrackBar->Maximum = 99;
            this->borderTrackBar->Name = L"borderTrackBar";
            this->borderTrackBar->Size = System::Drawing::Size(185, 45);
            this->borderTrackBar->TabIndex = 12;
            this->borderTrackBar->TickFrequency = 33;
            this->borderTrackBar->Value = 1;
            // 
            // noDisplayCheckBox
            // 
            this->noDisplayCheckBox->AutoSize = true;
            this->noDisplayCheckBox->Location = System::Drawing::Point(15, 280);
            this->noDisplayCheckBox->Name = L"noDisplayCheckBox";
            this->noDisplayCheckBox->Size = System::Drawing::Size(136, 17);
            this->noDisplayCheckBox->TabIndex = 17;
            this->noDisplayCheckBox->Text = L"Don\'t display final result";
            this->noDisplayCheckBox->UseVisualStyleBackColor = true;
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->label7->Location = System::Drawing::Point(8, 248);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(41, 12);
            this->label7->TabIndex = 13;
            this->label7->Text = L"negative";
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->label8->Location = System::Drawing::Point(70, 249);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(25, 12);
            this->label8->TabIndex = 14;
            this->label8->Text = L"none";
            // 
            // label9
            // 
            this->label9->AutoSize = true;
            this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->label9->Location = System::Drawing::Point(123, 249);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(25, 12);
            this->label9->TabIndex = 15;
            this->label9->Text = L"fixed";
            // 
            // label10
            // 
            this->label10->AutoSize = true;
            this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->label10->Location = System::Drawing::Point(169, 248);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(38, 12);
            this->label10->TabIndex = 16;
            this->label10->Text = L"variable";
            // 
            // label11
            // 
            this->label11->Location = System::Drawing::Point(12, 9);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(232, 32);
            this->label11->TabIndex = 1;
            this->label11->Text = L"The image will be rendered to fit the dimensions entered here, using the current " 
                L"variation.";
            // 
            // label12
            // 
            this->label12->Location = System::Drawing::Point(12, 46);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(232, 41);
            this->label12->TabIndex = 2;
            this->label12->Text = L"When complete, the image will be displayed scaled within the window, unless displ" 
                L"ay is disabled";
            // 
            // OKbutton
            // 
            this->OKbutton->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->OKbutton->Location = System::Drawing::Point(90, 322);
            this->OKbutton->Name = L"OKbutton";
            this->OKbutton->Size = System::Drawing::Size(75, 23);
            this->OKbutton->TabIndex = 18;
            this->OKbutton->Text = L"OK";
            this->OKbutton->UseVisualStyleBackColor = true;
            this->OKbutton->Click += gcnew System::EventHandler(this, &RenderSizeDialog::OKbutton_Click);
            // 
            // cancelButton
            // 
            this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->cancelButton->Location = System::Drawing::Point(171, 322);
            this->cancelButton->Name = L"cancelButton";
            this->cancelButton->Size = System::Drawing::Size(75, 23);
            this->cancelButton->TabIndex = 19;
            this->cancelButton->Text = L"Cancel";
            this->cancelButton->UseVisualStyleBackColor = true;
            this->cancelButton->Click += gcnew System::EventHandler(this, &RenderSizeDialog::cancelButton_Click);
            // 
            // minimumSizeBox
            // 
            this->minimumSizeBox->Location = System::Drawing::Point(15, 156);
            this->minimumSizeBox->Name = L"minimumSizeBox";
            this->minimumSizeBox->Size = System::Drawing::Size(55, 20);
            this->minimumSizeBox->TabIndex = 9;
            // 
            // widthBox
            // 
            this->widthBox->Location = System::Drawing::Point(15, 112);
            this->widthBox->MaxLength = 5;
            this->widthBox->Name = L"widthBox";
            this->widthBox->Size = System::Drawing::Size(55, 20);
            this->widthBox->TabIndex = 5;
            // 
            // heightBox
            // 
            this->heightBox->Location = System::Drawing::Point(94, 112);
            this->heightBox->MaxLength = 5;
            this->heightBox->Name = L"heightBox";
            this->heightBox->Size = System::Drawing::Size(55, 20);
            this->heightBox->TabIndex = 7;
            // 
            // RenderSizeDialog
            // 
            this->AcceptButton = this->OKbutton;
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->CancelButton = this->cancelButton;
            this->ClientSize = System::Drawing::Size(258, 357);
            this->Controls->Add(this->heightBox);
            this->Controls->Add(this->widthBox);
            this->Controls->Add(this->minimumSizeBox);
            this->Controls->Add(this->cancelButton);
            this->Controls->Add(this->OKbutton);
            this->Controls->Add(this->label12);
            this->Controls->Add(this->label11);
            this->Controls->Add(this->label10);
            this->Controls->Add(this->label9);
            this->Controls->Add(this->label8);
            this->Controls->Add(this->label7);
            this->Controls->Add(this->noDisplayCheckBox);
            this->Controls->Add(this->borderTrackBar);
            this->Controls->Add(this->label6);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"RenderSizeDialog";
            this->ShowInTaskbar = false;
            this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
            this->Text = L"Render to Size";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->borderTrackBar))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
private: 
    System::Void setup_dialog(System::Object^  sender, System::EventArgs^  e) 
    {
        renderSizeParameters->initFromPrefs();
        widthBox->Text = renderSizeParameters->width.ToString();
        heightBox->Text = renderSizeParameters->height.ToString();
        borderTrackBar->Value = (int)((renderSizeParameters->borderSize + 1.0) * 33.0);
        minimumSizeBox->Text = renderSizeParameters->minimumSize.ToString();
        noDisplayCheckBox->Checked = renderSizeParameters->suppressDisplay;
    }
private: 
    System::Void OKbutton_Click(System::Object^  sender, System::EventArgs^  e) 
    {
        try {
            renderSizeParameters->width = System::Int32::Parse(widthBox->Text);
            renderSizeParameters->height = System::Int32::Parse(heightBox->Text);
            renderSizeParameters->borderSize = (double) (borderTrackBar->Value) / 33.0 - 1.0;
            renderSizeParameters->minimumSize = System::Single::Parse(minimumSizeBox->Text);
            renderSizeParameters->suppressDisplay = noDisplayCheckBox->Checked;
            renderSizeParameters->saveToPrefs();
        } catch (System::SystemException^) {
            this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            System::Media::SystemSounds::Beep->Play();
        }
        this->Close();
    }
private: 
    System::Void cancelButton_Click(System::Object^  sender, System::EventArgs^  e) 
    {
        this->Close();
    }
};
}
