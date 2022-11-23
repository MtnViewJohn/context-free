#pragma once

#include "ColorChangeEventArgs.h"
#include "HSBChoose.h"
#include "RGBChoose.h"
#include "HSBEdit.h"

namespace CppWrapper {

    /// <summary>
    /// Summary for ColorCalculator
    ///
    /// WARNING: If you change the name of this class, you will need to change the
    ///          'Resource File Name' property for the managed resource compiler tool
    ///          associated with all .resx files this class depends on.  Otherwise,
    ///          the designers will not be able to interact properly with localized
    ///          resources associated with this form.
    /// </summary>
    public ref class ColorCalculator : public System::Windows::Forms::Form
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

    private: CppWrapper::HSBChoose^ hsbChooser;
    private: CppWrapper::RGBChoose^ rgbChooser;
    private: System::Windows::Forms::Button^ dropperButton;
    private: CppWrapper::HSBEdit^ startEditor;

    private: System::Windows::Forms::GroupBox^ groupBox1;
    private: System::Windows::Forms::GroupBox^ groupBox2;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::Label^ label4;
    private: CppWrapper::HSBEdit^ deltaEditor;

    private: System::Windows::Forms::Button^ startButton;

    private: System::Windows::Forms::Label^ label5;
    private: CppWrapper::HSBEdit^ endEditor;

    private: System::Windows::Forms::Button^ endButton;
    private: System::Windows::Forms::Label^ label6;
    private: System::Windows::Forms::Label^ label7;
    private: System::Windows::Forms::NumericUpDown^ stepCount;
    private: System::Windows::Forms::Button^ swapColors;



    protected:

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
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ColorCalculator::typeid));
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
            this->endEditor = (gcnew CppWrapper::HSBEdit());
            this->deltaEditor = (gcnew CppWrapper::HSBEdit());
            this->startEditor = (gcnew CppWrapper::HSBEdit());
            this->rgbChooser = (gcnew CppWrapper::RGBChoose());
            this->hsbChooser = (gcnew CppWrapper::HSBChoose());
            this->swapColors = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stepCount))->BeginInit();
            this->SuspendLayout();
            // 
            // dropperButton
            // 
            this->dropperButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"dropperButton.Image")));
            this->dropperButton->Location = System::Drawing::Point(24, 454);
            this->dropperButton->Margin = System::Windows::Forms::Padding(6);
            this->dropperButton->Name = L"dropperButton";
            this->dropperButton->Size = System::Drawing::Size(50, 48);
            this->dropperButton->TabIndex = 4;
            this->dropperButton->TabStop = false;
            this->dropperButton->UseVisualStyleBackColor = true;
            this->dropperButton->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &ColorCalculator::dropperMove);
            // 
            // groupBox1
            // 
            this->groupBox1->Location = System::Drawing::Point(26, 25);
            this->groupBox1->Margin = System::Windows::Forms::Padding(6);
            this->groupBox1->Name = L"groupBox1";
            this->groupBox1->Padding = System::Windows::Forms::Padding(6);
            this->groupBox1->Size = System::Drawing::Size(458, 419);
            this->groupBox1->TabIndex = 0;
            this->groupBox1->TabStop = false;
            this->groupBox1->Text = L"Hue, Saturation, Brightness";
            // 
            // groupBox2
            // 
            this->groupBox2->Location = System::Drawing::Point(496, 25);
            this->groupBox2->Margin = System::Windows::Forms::Padding(6);
            this->groupBox2->Name = L"groupBox2";
            this->groupBox2->Padding = System::Windows::Forms::Padding(6);
            this->groupBox2->Size = System::Drawing::Size(208, 469);
            this->groupBox2->TabIndex = 6;
            this->groupBox2->TabStop = false;
            this->groupBox2->Text = L"Red, Green, Blue";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(26, 521);
            this->label1->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(63, 25);
            this->label1->TabIndex = 7;
            this->label1->Text = L"Start:";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(104, 477);
            this->label2->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(51, 25);
            this->label2->TabIndex = 8;
            this->label2->Text = L"Hue";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(236, 477);
            this->label3->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(110, 25);
            this->label3->TabIndex = 9;
            this->label3->Text = L"Saturation";
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(368, 477);
            this->label4->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(114, 25);
            this->label4->TabIndex = 10;
            this->label4->Text = L"Brightness";
            // 
            // startButton
            // 
            this->startButton->Font = (gcnew System::Drawing::Font(L"Arial", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->startButton->Location = System::Drawing::Point(632, 508);
            this->startButton->Margin = System::Windows::Forms::Padding(6);
            this->startButton->Name = L"startButton";
            this->startButton->Size = System::Drawing::Size(74, 98);
            this->startButton->TabIndex = 11;
            this->startButton->Text = L"☚";
            this->startButton->UseVisualStyleBackColor = true;
            this->startButton->Click += gcnew System::EventHandler(this, &ColorCalculator::buttonHandler);
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(26, 640);
            this->label5->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(68, 25);
            this->label5->TabIndex = 13;
            this->label5->Text = L"Delta:";
            // 
            // endButton
            // 
            this->endButton->Font = (gcnew System::Drawing::Font(L"Arial", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->endButton->Location = System::Drawing::Point(632, 748);
            this->endButton->Margin = System::Windows::Forms::Padding(6);
            this->endButton->Name = L"endButton";
            this->endButton->Size = System::Drawing::Size(74, 98);
            this->endButton->TabIndex = 16;
            this->endButton->Text = L"☚";
            this->endButton->UseVisualStyleBackColor = true;
            this->endButton->Click += gcnew System::EventHandler(this, &ColorCalculator::buttonHandler);
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(26, 763);
            this->label6->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(76, 25);
            this->label6->TabIndex = 16;
            this->label6->Text = L"Finish:";
            // 
            // label7
            // 
            this->label7->Location = System::Drawing::Point(508, 622);
            this->label7->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(110, 53);
            this->label7->TabIndex = 17;
            this->label7->Text = L"Number of steps:";
            // 
            // stepCount
            // 
            this->stepCount->Location = System::Drawing::Point(508, 683);
            this->stepCount->Margin = System::Windows::Forms::Padding(6);
            this->stepCount->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
            this->stepCount->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            this->stepCount->Name = L"stepCount";
            this->stepCount->Size = System::Drawing::Size(122, 31);
            this->stepCount->TabIndex = 13;
            this->stepCount->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            this->stepCount->ValueChanged += gcnew System::EventHandler(this, &ColorCalculator::stepCount_ValueChanged);
            // 
            // endEditor
            // 
            this->endEditor->Bright = 0;
            this->endEditor->Hue = 0;
            this->endEditor->Location = System::Drawing::Point(102, 742);
            this->endEditor->Margin = System::Windows::Forms::Padding(12);
            this->endEditor->Name = L"endEditor";
            this->endEditor->Sat = 0;
            this->endEditor->ShowColor = true;
            this->endEditor->Size = System::Drawing::Size(516, 108);
            this->endEditor->TabIndex = 15;
            // 
            // deltaEditor
            // 
            this->deltaEditor->Bright = 0;
            this->deltaEditor->Hue = 0;
            this->deltaEditor->Location = System::Drawing::Point(102, 621);
            this->deltaEditor->Margin = System::Windows::Forms::Padding(12);
            this->deltaEditor->Name = L"deltaEditor";
            this->deltaEditor->Sat = 0;
            this->deltaEditor->ShowColor = false;
            this->deltaEditor->Size = System::Drawing::Size(396, 108);
            this->deltaEditor->TabIndex = 12;
            // 
            // startEditor
            // 
            this->startEditor->BackColor = System::Drawing::SystemColors::ControlLightLight;
            this->startEditor->Bright = 0;
            this->startEditor->Hue = 0;
            this->startEditor->Location = System::Drawing::Point(102, 502);
            this->startEditor->Margin = System::Windows::Forms::Padding(12);
            this->startEditor->Name = L"startEditor";
            this->startEditor->Sat = 0;
            this->startEditor->ShowColor = true;
            this->startEditor->Size = System::Drawing::Size(516, 108);
            this->startEditor->TabIndex = 5;
            // 
            // rgbChooser
            // 
            this->rgbChooser->Blue = 0;
            this->rgbChooser->CurrentColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
                static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
            this->rgbChooser->Green = 0;
            this->rgbChooser->Location = System::Drawing::Point(508, 62);
            this->rgbChooser->Margin = System::Windows::Forms::Padding(12);
            this->rgbChooser->Name = L"rgbChooser";
            this->rgbChooser->Red = 0;
            this->rgbChooser->Size = System::Drawing::Size(186, 429);
            this->rgbChooser->TabIndex = 3;
            // 
            // hsbChooser
            // 
            this->hsbChooser->Bright = 1;
            this->hsbChooser->Hue = 0;
            this->hsbChooser->Location = System::Drawing::Point(38, 73);
            this->hsbChooser->Margin = System::Windows::Forms::Padding(12);
            this->hsbChooser->Name = L"hsbChooser";
            this->hsbChooser->Sat = 0;
            this->hsbChooser->Size = System::Drawing::Size(444, 347);
            this->hsbChooser->TabIndex = 2;
            // 
            // swapColors
            // 
            this->swapColors->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->swapColors->Location = System::Drawing::Point(648, 631);
            this->swapColors->Name = L"swapColors";
            this->swapColors->Size = System::Drawing::Size(43, 88);
            this->swapColors->TabIndex = 14;
            this->swapColors->Text = L"⇵";
            this->swapColors->UseVisualStyleBackColor = true;
            this->swapColors->Click += gcnew System::EventHandler(this, &ColorCalculator::swapColorsClick);
            // 
            // ColorCalculator
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::ControlLightLight;
            this->ClientSize = System::Drawing::Size(730, 877);
            this->Controls->Add(this->swapColors);
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
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->Margin = System::Windows::Forms::Padding(6);
            this->MaximizeBox = false;
            this->Name = L"ColorCalculator";
            this->ShowInTaskbar = false;
            this->Text = L"Color Calculator";
            this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ColorCalculator::hideForm);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stepCount))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private:
        bool startSelected;
        void MoreInitialization();
        System::Void chooserHandler(System::Object^ sender, CppWrapper::ColorChangeEventArgs^ e);
        System::Void editorHandler(System::Object^ sender, CppWrapper::ColorChangeEventArgs^ e);
        System::Void buttonHandler(System::Object^ sender, System::EventArgs^ e);
        void calcDelta();
        void calcEnd();
        System::Void handleHandler(System::Object^ sender, System::EventArgs^ e);
        System::Void stepCount_ValueChanged(System::Object^ sender, System::EventArgs^ e);
        System::Void hideForm(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
        System::Void dropperMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
        System::Void swapColorsClick(System::Object^ sender, System::EventArgs^ e);
};
}
