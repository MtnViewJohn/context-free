// AnimateDialog.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2017 John Horigan - john@glyphic.com
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

#include "RenderParameters.h"

namespace ContextFreeNet {


	/// <summary>
	/// Summary for AnimateDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class AnimateDialog : public System::Windows::Forms::Form
	{
	public:
		AnimateDialog(RenderParameters* rp)
        : renderParameters(rp)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
            this->Load += gcnew System::EventHandler(this, &AnimateDialog::setup_dialog);
		}
    private: System::Windows::Forms::TextBox^  widthBox;
    public: 
    private: System::Windows::Forms::TextBox^  heightBox;
    private: System::Windows::Forms::CheckBox^  zoom;
    private: System::Windows::Forms::TextBox^  lengthBox;
    private: System::Windows::Forms::ComboBox^  frameRate;
    private: System::Windows::Forms::Label^  label13;
    private: System::Windows::Forms::Label^  label14;
    private: System::Windows::Forms::Label^  label15;
    private: System::Windows::Forms::Label^  label16;
    public: System::Windows::Forms::TextBox^  frameNumber;
    private:

    private:

    private:

    private: System::Windows::Forms::Label^  frameLabel;
    private: System::Windows::Forms::Label^  codecLabel;
    private: System::Windows::Forms::ComboBox^  codec;
    private: System::Windows::Forms::CheckBox^  showPreview;


             RenderParameters* renderParameters;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AnimateDialog()
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
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->borderTrackBar = (gcnew System::Windows::Forms::TrackBar());
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
            this->zoom = (gcnew System::Windows::Forms::CheckBox());
            this->lengthBox = (gcnew System::Windows::Forms::TextBox());
            this->frameRate = (gcnew System::Windows::Forms::ComboBox());
            this->label13 = (gcnew System::Windows::Forms::Label());
            this->label14 = (gcnew System::Windows::Forms::Label());
            this->label15 = (gcnew System::Windows::Forms::Label());
            this->label16 = (gcnew System::Windows::Forms::Label());
            this->frameNumber = (gcnew System::Windows::Forms::TextBox());
            this->frameLabel = (gcnew System::Windows::Forms::Label());
            this->codecLabel = (gcnew System::Windows::Forms::Label());
            this->codec = (gcnew System::Windows::Forms::ComboBox());
            this->showPreview = (gcnew System::Windows::Forms::CheckBox());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->borderTrackBar))->BeginInit();
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(70, 172);
            this->label1->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(67, 25);
            this->label1->TabIndex = 3;
            this->label1->Text = L"Width";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(224, 172);
            this->label2->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(74, 25);
            this->label2->TabIndex = 4;
            this->label2->Text = L"Height";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(149, 262);
            this->label3->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(242, 25);
            this->label3->TabIndex = 10;
            this->label3->Text = L"size of smallest element";
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(312, 208);
            this->label4->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(91, 25);
            this->label4->TabIndex = 8;
            this->label4->Text = L"in pixels";
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Font = (gcnew System::Drawing::Font(L"Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(2)));
            this->label5->Location = System::Drawing::Point(148, 204);
            this->label5->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(30, 32);
            this->label5->TabIndex = 6;
            this->label5->Text = L"´";
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(24, 315);
            this->label6->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(189, 25);
            this->label6->TabIndex = 11;
            this->label6->Text = L"Image border size:";
            // 
            // borderTrackBar
            // 
            this->borderTrackBar->Location = System::Drawing::Point(30, 345);
            this->borderTrackBar->Margin = System::Windows::Forms::Padding(6);
            this->borderTrackBar->Maximum = 99;
            this->borderTrackBar->Name = L"borderTrackBar";
            this->borderTrackBar->Size = System::Drawing::Size(370, 90);
            this->borderTrackBar->TabIndex = 12;
            this->borderTrackBar->TickFrequency = 33;
            this->borderTrackBar->Value = 1;
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label7->Location = System::Drawing::Point(16, 407);
            this->label7->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(78, 22);
            this->label7->TabIndex = 13;
            this->label7->Text = L"negative";
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label8->Location = System::Drawing::Point(140, 409);
            this->label8->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(50, 22);
            this->label8->TabIndex = 14;
            this->label8->Text = L"none";
            // 
            // label9
            // 
            this->label9->AutoSize = true;
            this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label9->Location = System::Drawing::Point(246, 409);
            this->label9->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(48, 22);
            this->label9->TabIndex = 15;
            this->label9->Text = L"fixed";
            // 
            // label10
            // 
            this->label10->AutoSize = true;
            this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label10->Location = System::Drawing::Point(338, 407);
            this->label10->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(73, 22);
            this->label10->TabIndex = 16;
            this->label10->Text = L"variable";
            // 
            // label11
            // 
            this->label11->Location = System::Drawing::Point(24, 17);
            this->label11->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(464, 76);
            this->label11->TabIndex = 1;
            this->label11->Text = L"The image will be animated to the dimensions entered here, using the current vari"
                L"ation.";
            this->label11->Click += gcnew System::EventHandler(this, &AnimateDialog::label11_Click);
            // 
            // label12
            // 
            this->label12->Location = System::Drawing::Point(24, 88);
            this->label12->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(464, 79);
            this->label12->TabIndex = 2;
            this->label12->Text = L"When complete, the movie will be displayed scaled within the window";
            // 
            // OKbutton
            // 
            this->OKbutton->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->OKbutton->Location = System::Drawing::Point(180, 619);
            this->OKbutton->Margin = System::Windows::Forms::Padding(6);
            this->OKbutton->Name = L"OKbutton";
            this->OKbutton->Size = System::Drawing::Size(150, 44);
            this->OKbutton->TabIndex = 26;
            this->OKbutton->Text = L"OK";
            this->OKbutton->UseVisualStyleBackColor = true;
            this->OKbutton->Click += gcnew System::EventHandler(this, &AnimateDialog::OKbutton_Click);
            // 
            // cancelButton
            // 
            this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->cancelButton->Location = System::Drawing::Point(342, 619);
            this->cancelButton->Margin = System::Windows::Forms::Padding(6);
            this->cancelButton->Name = L"cancelButton";
            this->cancelButton->Size = System::Drawing::Size(150, 44);
            this->cancelButton->TabIndex = 27;
            this->cancelButton->Text = L"Cancel";
            this->cancelButton->UseVisualStyleBackColor = true;
            this->cancelButton->Click += gcnew System::EventHandler(this, &AnimateDialog::cancelButton_Click);
            // 
            // minimumSizeBox
            // 
            this->minimumSizeBox->Location = System::Drawing::Point(29, 256);
            this->minimumSizeBox->Margin = System::Windows::Forms::Padding(6);
            this->minimumSizeBox->Name = L"minimumSizeBox";
            this->minimumSizeBox->Size = System::Drawing::Size(106, 31);
            this->minimumSizeBox->TabIndex = 9;
            // 
            // widthBox
            // 
            this->widthBox->Location = System::Drawing::Point(30, 202);
            this->widthBox->Margin = System::Windows::Forms::Padding(6);
            this->widthBox->MaxLength = 5;
            this->widthBox->Name = L"widthBox";
            this->widthBox->Size = System::Drawing::Size(106, 31);
            this->widthBox->TabIndex = 5;
            this->widthBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // heightBox
            // 
            this->heightBox->Location = System::Drawing::Point(188, 202);
            this->heightBox->Margin = System::Windows::Forms::Padding(6);
            this->heightBox->MaxLength = 5;
            this->heightBox->Name = L"heightBox";
            this->heightBox->Size = System::Drawing::Size(106, 31);
            this->heightBox->TabIndex = 7;
            this->heightBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // zoom
            // 
            this->zoom->AutoSize = true;
            this->zoom->Location = System::Drawing::Point(30, 460);
            this->zoom->Name = L"zoom";
            this->zoom->Size = System::Drawing::Size(197, 29);
            this->zoom->TabIndex = 19;
            this->zoom->Text = L"Zoom animation";
            this->zoom->UseVisualStyleBackColor = true;
            // 
            // lengthBox
            // 
            this->lengthBox->Location = System::Drawing::Point(30, 554);
            this->lengthBox->MaxLength = 5;
            this->lengthBox->Name = L"lengthBox";
            this->lengthBox->Size = System::Drawing::Size(100, 31);
            this->lengthBox->TabIndex = 21;
            this->lengthBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // frameRate
            // 
            this->frameRate->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->frameRate->FormattingEnabled = true;
            this->frameRate->Items->AddRange(gcnew cli::array< System::Object^  >(7) { L"8", L"10", L"12", L"15", L"30", L"50", L"60" });
            this->frameRate->Location = System::Drawing::Point(188, 554);
            this->frameRate->Name = L"frameRate";
            this->frameRate->Size = System::Drawing::Size(121, 33);
            this->frameRate->TabIndex = 22;
            // 
            // label13
            // 
            this->label13->AutoSize = true;
            this->label13->Font = (gcnew System::Drawing::Font(L"Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(2)));
            this->label13->Location = System::Drawing::Point(145, 550);
            this->label13->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label13->Name = L"label13";
            this->label13->Size = System::Drawing::Size(30, 32);
            this->label13->TabIndex = 25;
            this->label13->Text = L"´";
            // 
            // label14
            // 
            this->label14->AutoSize = true;
            this->label14->Location = System::Drawing::Point(323, 554);
            this->label14->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label14->Name = L"label14";
            this->label14->Size = System::Drawing::Size(146, 25);
            this->label14->TabIndex = 26;
            this->label14->Text = L"seconds × fps";
            // 
            // label15
            // 
            this->label15->AutoSize = true;
            this->label15->Location = System::Drawing::Point(190, 518);
            this->label15->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label15->Name = L"label15";
            this->label15->Size = System::Drawing::Size(124, 25);
            this->label15->TabIndex = 24;
            this->label15->Text = L"Frame Rate";
            // 
            // label16
            // 
            this->label16->AutoSize = true;
            this->label16->Location = System::Drawing::Point(57, 518);
            this->label16->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label16->Name = L"label16";
            this->label16->Size = System::Drawing::Size(78, 25);
            this->label16->TabIndex = 23;
            this->label16->Text = L"Length";
            // 
            // frameNumber
            // 
            this->frameNumber->Location = System::Drawing::Point(342, 487);
            this->frameNumber->Margin = System::Windows::Forms::Padding(6);
            this->frameNumber->MaxLength = 5;
            this->frameNumber->Name = L"frameNumber";
            this->frameNumber->Size = System::Drawing::Size(106, 31);
            this->frameNumber->TabIndex = 24;
            this->frameNumber->Text = L"1";
            this->frameNumber->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // frameLabel
            // 
            this->frameLabel->AutoSize = true;
            this->frameLabel->Location = System::Drawing::Point(382, 457);
            this->frameLabel->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->frameLabel->Name = L"frameLabel";
            this->frameLabel->Size = System::Drawing::Size(73, 25);
            this->frameLabel->TabIndex = 27;
            this->frameLabel->Text = L"Frame";
            // 
            // codecLabel
            // 
            this->codecLabel->AutoSize = true;
            this->codecLabel->Location = System::Drawing::Point(375, 456);
            this->codecLabel->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->codecLabel->Name = L"codecLabel";
            this->codecLabel->Size = System::Drawing::Size(74, 25);
            this->codecLabel->TabIndex = 28;
            this->codecLabel->Text = L"Codec";
            // 
            // codec
            // 
            this->codec->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->codec->FormattingEnabled = true;
            this->codec->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"H.264", L"ProRes" });
            this->codec->Location = System::Drawing::Point(342, 485);
            this->codec->Name = L"codec";
            this->codec->Size = System::Drawing::Size(121, 33);
            this->codec->TabIndex = 23;
            // 
            // showPreview
            // 
            this->showPreview->AutoSize = true;
            this->showPreview->Location = System::Drawing::Point(30, 619);
            this->showPreview->Name = L"showPreview";
            this->showPreview->Size = System::Drawing::Size(120, 29);
            this->showPreview->TabIndex = 25;
            this->showPreview->Text = L"Preview";
            this->showPreview->UseVisualStyleBackColor = true;
            // 
            // AnimateDialog
            // 
            this->AcceptButton = this->OKbutton;
            this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->CancelButton = this->cancelButton;
            this->ClientSize = System::Drawing::Size(516, 687);
            this->Controls->Add(this->showPreview);
            this->Controls->Add(this->codec);
            this->Controls->Add(this->codecLabel);
            this->Controls->Add(this->frameNumber);
            this->Controls->Add(this->frameLabel);
            this->Controls->Add(this->label13);
            this->Controls->Add(this->label14);
            this->Controls->Add(this->label15);
            this->Controls->Add(this->label16);
            this->Controls->Add(this->frameRate);
            this->Controls->Add(this->lengthBox);
            this->Controls->Add(this->zoom);
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
            this->Controls->Add(this->borderTrackBar);
            this->Controls->Add(this->label6);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->Margin = System::Windows::Forms::Padding(6);
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"AnimateDialog";
            this->ShowInTaskbar = false;
            this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
            this->Text = L"Animate";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->borderTrackBar))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
private: 
    System::Void setup_dialog(System::Object^  sender, System::EventArgs^  e) 
    {
        renderParameters->initFromPrefs();
        widthBox->Text = renderParameters->animateWidth.ToString();
        heightBox->Text = renderParameters->animateHeight.ToString();
        borderTrackBar->Value = (int)((renderParameters->borderSize + 1.0) * 33.0);
        minimumSizeBox->Text = renderParameters->minimumSize.ToString();
        zoom->Checked = renderParameters->animateZoom;
        lengthBox->Text = renderParameters->length.ToString();
        int i = frameRate->FindStringExact(renderParameters->frameRate.ToString());
        frameRate->SelectedIndex = i < 0 ? 3 : i;
        if (renderParameters->animateFrame) {
            if (renderParameters->frame < 1)
                renderParameters->frame = 1;
            frameNumber->Text = renderParameters->frame.ToString();
            this->Text = L"Animate a Frame";
            frameNumber->Visible = true;
            frameLabel->Visible = true;
            showPreview->Visible = false;
            codecLabel->Visible = false;
            codec->Visible = false;
        } else {
            codec->SelectedIndex = renderParameters->codec;
            showPreview->Checked = renderParameters->preview;
            frameNumber->Visible = false;
            frameLabel->Visible = false;
            showPreview->Visible = true;
            codecLabel->Visible = true;
            codec->Visible = true;
        }
    }
private: 
    System::Void OKbutton_Click(System::Object^  sender, System::EventArgs^  e) 
    {
        try {
            renderParameters->animateWidth = System::Int32::Parse(widthBox->Text);
            renderParameters->animateHeight = System::Int32::Parse(heightBox->Text);
            renderParameters->borderSize = (double) (borderTrackBar->Value) / 33.0 - 1.0;
            renderParameters->minimumSize = System::Single::Parse(minimumSizeBox->Text);
            renderParameters->length = System::Int32::Parse(lengthBox->Text);
            renderParameters->frameRate = System::Int32::Parse(frameRate->Text);
            renderParameters->animateZoom = zoom->Checked;
            renderParameters->animateFrameCount = renderParameters->length * renderParameters->frameRate;
            if (renderParameters->animateFrame) {
                renderParameters->frame = System::Int32::Parse(frameNumber->Text);
                if (renderParameters->frame < 1 ||
                    renderParameters->frame > renderParameters->animateFrameCount)
                {
                    this->DialogResult = System::Windows::Forms::DialogResult::None;
                    this->Text = L"Illegal frame number";
                    System::Media::SystemSounds::Asterisk->Play();
                    return;
                }
            } else {
                renderParameters->codec = codec->SelectedIndex;
                renderParameters->preview = showPreview->Checked;
            }
            renderParameters->saveToPrefs();
        } catch (System::SystemException^) {
            this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            System::Media::SystemSounds::Asterisk->Play();
        }
        this->Close();
    }
private: 
    System::Void cancelButton_Click(System::Object^  sender, System::EventArgs^  e) 
    {
        this->Close();
    }
private: System::Void label11_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}
