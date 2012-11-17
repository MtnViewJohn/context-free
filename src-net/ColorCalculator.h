// ColorCalculator.h
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


namespace ContextFreeNet {

	/// <summary>
	/// Summary for ColorCalculator
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class ColorCalculator : public WeifenLuo::WinFormsUI::Docking::DockContent
	{
	public:
		ColorCalculator(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
            MoreInitialization();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ColorCalculator()
		{
			if (components)
			{
				delete components;
			}
		}

    private: CFControls::HSBChoose^  hsbChooser;
    private: CFControls::RGBChoose^  rgbChooser;
    private: System::Windows::Forms::Button^  dropperButton;
    private: CFControls::HSBEdit^  startEditor;

    private: System::Windows::Forms::GroupBox^  groupBox1;
    private: System::Windows::Forms::GroupBox^  groupBox2;
    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::Label^  label3;
    private: System::Windows::Forms::Label^  label4;
    private: CFControls::HSBEdit^  deltaEditor;

    private: System::Windows::Forms::Button^  startButton;

    private: System::Windows::Forms::Label^  label5;
    private: CFControls::HSBEdit^  endEditor;

    private: System::Windows::Forms::Button^  endButton;
    private: System::Windows::Forms::Label^  label6;
    private: System::Windows::Forms::Label^  label7;
    private: System::Windows::Forms::NumericUpDown^  stepCount;



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
            System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ColorCalculator::typeid));
            this->dropperButton = (gcnew System::Windows::Forms::Button());
            this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
            this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->startButton = (gcnew System::Windows::Forms::Button());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->endButton = (gcnew System::Windows::Forms::Button());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->stepCount = (gcnew System::Windows::Forms::NumericUpDown());
            this->endEditor = (gcnew CFControls::HSBEdit());
            this->deltaEditor = (gcnew CFControls::HSBEdit());
            this->startEditor = (gcnew CFControls::HSBEdit());
            this->rgbChooser = (gcnew CFControls::RGBChoose());
            this->hsbChooser = (gcnew CFControls::HSBChoose());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stepCount))->BeginInit();
            this->SuspendLayout();
            // 
            // dropperButton
            // 
            this->dropperButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"dropperButton.Image")));
            this->dropperButton->Location = System::Drawing::Point(12, 236);
            this->dropperButton->Name = L"dropperButton";
            this->dropperButton->Size = System::Drawing::Size(25, 25);
            this->dropperButton->TabIndex = 4;
            this->dropperButton->TabStop = false;
            this->dropperButton->UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this->groupBox1->Location = System::Drawing::Point(13, 13);
            this->groupBox1->Name = L"groupBox1";
            this->groupBox1->Size = System::Drawing::Size(229, 218);
            this->groupBox1->TabIndex = 0;
            this->groupBox1->TabStop = false;
            this->groupBox1->Text = L"Hue, Saturation, Brightness";
            // 
            // groupBox2
            // 
            this->groupBox2->Location = System::Drawing::Point(248, 13);
            this->groupBox2->Name = L"groupBox2";
            this->groupBox2->Size = System::Drawing::Size(104, 244);
            this->groupBox2->TabIndex = 6;
            this->groupBox2->TabStop = false;
            this->groupBox2->Text = L"Red, Green, Blue";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(13, 271);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(32, 13);
            this->label1->TabIndex = 7;
            this->label1->Text = L"Start:";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(52, 248);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(27, 13);
            this->label2->TabIndex = 8;
            this->label2->Text = L"Hue";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(118, 248);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(55, 13);
            this->label3->TabIndex = 9;
            this->label3->Text = L"Saturation";
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(184, 248);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(56, 13);
            this->label4->TabIndex = 10;
            this->label4->Text = L"Brightness";
            // 
            // startButton
            // 
            this->startButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"startButton.Image")));
            this->startButton->Location = System::Drawing::Point(316, 264);
            this->startButton->Name = L"startButton";
            this->startButton->Size = System::Drawing::Size(37, 51);
            this->startButton->TabIndex = 11;
            this->startButton->UseVisualStyleBackColor = true;
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(13, 333);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(35, 13);
            this->label5->TabIndex = 13;
            this->label5->Text = L"Delta:";
            // 
            // endButton
            // 
            this->endButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"endButton.Image")));
            this->endButton->Location = System::Drawing::Point(316, 389);
            this->endButton->Name = L"endButton";
            this->endButton->Size = System::Drawing::Size(37, 51);
            this->endButton->TabIndex = 15;
            this->endButton->UseVisualStyleBackColor = true;
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(13, 397);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(37, 13);
            this->label6->TabIndex = 16;
            this->label6->Text = L"Finish:";
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Location = System::Drawing::Point(254, 333);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(87, 13);
            this->label7->TabIndex = 17;
            this->label7->Text = L"Number of steps:";
            // 
            // stepCount
            // 
            this->stepCount->Location = System::Drawing::Point(254, 355);
            this->stepCount->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000, 0, 0, 0});
            this->stepCount->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
            this->stepCount->Name = L"stepCount";
            this->stepCount->Size = System::Drawing::Size(98, 20);
            this->stepCount->TabIndex = 13;
            this->stepCount->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
            this->stepCount->ValueChanged += gcnew System::EventHandler(this, &ColorCalculator::stepCount_ValueChanged);
            // 
            // endEditor
            // 
            this->endEditor->Bright = 0;
            this->endEditor->Hue = 0;
            this->endEditor->Location = System::Drawing::Point(51, 386);
            this->endEditor->Name = L"endEditor";
            this->endEditor->Sat = 0;
            this->endEditor->ShowColor = true;
            this->endEditor->Size = System::Drawing::Size(258, 56);
            this->endEditor->TabIndex = 14;
            // 
            // deltaEditor
            // 
            this->deltaEditor->Bright = 0;
            this->deltaEditor->Hue = 0;
            this->deltaEditor->Location = System::Drawing::Point(51, 323);
            this->deltaEditor->Name = L"deltaEditor";
            this->deltaEditor->Sat = 0;
            this->deltaEditor->ShowColor = false;
            this->deltaEditor->Size = System::Drawing::Size(198, 56);
            this->deltaEditor->TabIndex = 12;
            // 
            // startEditor
            // 
            this->startEditor->BackColor = System::Drawing::SystemColors::ControlLightLight;
            this->startEditor->Bright = 0;
            this->startEditor->Hue = 0;
            this->startEditor->Location = System::Drawing::Point(51, 261);
            this->startEditor->Name = L"startEditor";
            this->startEditor->Sat = 0;
            this->startEditor->ShowColor = true;
            this->startEditor->Size = System::Drawing::Size(258, 56);
            this->startEditor->TabIndex = 5;
            // 
            // rgbChooser
            // 
            this->rgbChooser->Blue = 0;
            this->rgbChooser->CurrentColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
                static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
            this->rgbChooser->Green = 0;
            this->rgbChooser->Location = System::Drawing::Point(254, 32);
            this->rgbChooser->Name = L"rgbChooser";
            this->rgbChooser->Red = 0;
            this->rgbChooser->Size = System::Drawing::Size(93, 223);
            this->rgbChooser->TabIndex = 3;
            // 
            // hsbChooser
            // 
            this->hsbChooser->Bright = 1;
            this->hsbChooser->Hue = 0;
            this->hsbChooser->Location = System::Drawing::Point(19, 32);
            this->hsbChooser->Name = L"hsbChooser";
            this->hsbChooser->Sat = 0;
            this->hsbChooser->Size = System::Drawing::Size(222, 197);
            this->hsbChooser->TabIndex = 2;
            // 
            // ColorCalculator
            // 
            this->AutoHidePortion = 365;
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::ControlLightLight;
            this->ClientSize = System::Drawing::Size(365, 456);
            this->Controls->Add(this->stepCount);
            this->Controls->Add(this->label7);
            this->Controls->Add(this->label6);
            this->Controls->Add(this->endButton);
            this->Controls->Add(this->endEditor);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->startButton);
            this->Controls->Add(this->deltaEditor);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->startEditor);
            this->Controls->Add(this->dropperButton);
            this->Controls->Add(this->rgbChooser);
            this->Controls->Add(this->hsbChooser);
            this->Controls->Add(this->groupBox1);
            this->Controls->Add(this->groupBox2);
            this->DockAreas = static_cast<WeifenLuo::WinFormsUI::Docking::DockAreas>((WeifenLuo::WinFormsUI::Docking::DockAreas::DockRight | WeifenLuo::WinFormsUI::Docking::DockAreas::Document));
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->HideOnClose = true;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
            this->Name = L"ColorCalculator";
            this->ShowInTaskbar = false;
            this->TabText = L"Color Calculator";
            this->Text = L"Color Calculator";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stepCount))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private:
        bool startSelected;
        void MoreInitialization();
        System::Void chooserHandler(System::Object^ sender, CFControls::ColorChangeEventArgs^ e);
        System::Void editorHandler(System::Object^ sender, CFControls::ColorChangeEventArgs^ e);
        System::Void buttonHandler(System::Object^ sender, System::EventArgs^ e);
        void calcDelta();
        void calcEnd();
        System::Void handleHandler(System::Object^ sender, System::EventArgs^ e);
        System::Void dropperHandler(System::Object^ sender, System::EventArgs^ e);
        System::Void mouseHandler(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
        System::Void stepCount_ValueChanged(System::Object^  sender, System::EventArgs^  e);
};
}
