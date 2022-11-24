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
	/// Summary for GalleryUploader
	/// </summary>
    public ref class GalleryUploader : public System::Windows::Forms::Form
    {
    public:
        GalleryUploader(UploadPrefs^ prefs,  System::IO::MemoryStream^ bms, 
            CFDG::frieze_t fr, int tiled, bool png)
            : design_id(0), uploadPrefs(prefs), bitmapStream(bms)
        {
            InitializeComponent();
            //
            //TODO: Add the constructor code here
            //
            MoreInitialzation(fr, tiled, png);
        }

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~GalleryUploader()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::Label^ label1;
    protected:
    private: System::Windows::Forms::GroupBox^ groupBox1;
    private: System::Windows::Forms::LinkLabel^ account;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::TextBox^ password;
    private: System::Windows::Forms::TextBox^ username;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::GroupBox^ groupBox2;
    private: System::Windows::Forms::ComboBox^ cc_change;
    private: System::Windows::Forms::Label^ ccname;
    private: System::Windows::Forms::PictureBox^ ccicon;
    private: System::Windows::Forms::Label^ label11;
    private: System::Windows::Forms::RadioButton^ radioPNG8;
    private: System::Windows::Forms::RadioButton^ radioJPEG;
    private: System::Windows::Forms::Label^ label10;
    private: System::Windows::Forms::Label^ label9;
    private: System::Windows::Forms::Label^ multlabel3;
    private: System::Windows::Forms::NumericUpDown^ multheight;
    private: System::Windows::Forms::Label^ multlabel2;
    private: System::Windows::Forms::NumericUpDown^ multwidth;
    private: System::Windows::Forms::Label^ multlabel1;
    private: System::Windows::Forms::CheckBox^ uptiled;
    private: System::Windows::Forms::CheckBox^ crop;
    private: System::Windows::Forms::Label^ variation;
    private: System::Windows::Forms::Label^ label8;
    private: System::Windows::Forms::Label^ label6;
    private: System::Windows::Forms::TextBox^ filename;
    private: System::Windows::Forms::TextBox^ title;
    private: System::Windows::Forms::TextBox^ notes;
    private: System::Windows::Forms::Label^ label5;
    private: System::Windows::Forms::Label^ label7;
    private: System::Windows::Forms::Label^ message;
    private: System::Windows::Forms::Button^ cancel;
    private: System::Windows::Forms::Button^ upload;
    private: System::Windows::Forms::Label^ label4;
    private: System::Windows::Forms::TextBox^ tagBox;
    private: System::Windows::Forms::ComboBox^ tagsList;

    private: System::Windows::Forms::Button^ addTag;
    private: System::Windows::Forms::ToolTip^ toolTip1;
    private: System::Windows::Forms::ProgressBar^ uploadProgress;
    private: System::Windows::Forms::ImageList^ imageList1;
    private: System::ComponentModel::IContainer^ components;


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
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(GalleryUploader::typeid));
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
            this->account = (gcnew System::Windows::Forms::LinkLabel());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->password = (gcnew System::Windows::Forms::TextBox());
            this->username = (gcnew System::Windows::Forms::TextBox());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
            this->tagsList = (gcnew System::Windows::Forms::ComboBox());
            this->addTag = (gcnew System::Windows::Forms::Button());
            this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->tagBox = (gcnew System::Windows::Forms::TextBox());
            this->cc_change = (gcnew System::Windows::Forms::ComboBox());
            this->ccname = (gcnew System::Windows::Forms::Label());
            this->ccicon = (gcnew System::Windows::Forms::PictureBox());
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->radioPNG8 = (gcnew System::Windows::Forms::RadioButton());
            this->radioJPEG = (gcnew System::Windows::Forms::RadioButton());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->multlabel3 = (gcnew System::Windows::Forms::Label());
            this->multheight = (gcnew System::Windows::Forms::NumericUpDown());
            this->multlabel2 = (gcnew System::Windows::Forms::Label());
            this->multwidth = (gcnew System::Windows::Forms::NumericUpDown());
            this->multlabel1 = (gcnew System::Windows::Forms::Label());
            this->uptiled = (gcnew System::Windows::Forms::CheckBox());
            this->crop = (gcnew System::Windows::Forms::CheckBox());
            this->variation = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->filename = (gcnew System::Windows::Forms::TextBox());
            this->title = (gcnew System::Windows::Forms::TextBox());
            this->notes = (gcnew System::Windows::Forms::TextBox());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->message = (gcnew System::Windows::Forms::Label());
            this->cancel = (gcnew System::Windows::Forms::Button());
            this->upload = (gcnew System::Windows::Forms::Button());
            this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
            this->uploadProgress = (gcnew System::Windows::Forms::ProgressBar());
            this->groupBox1->SuspendLayout();
            this->groupBox2->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ccicon))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->multheight))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->multwidth))->BeginInit();
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label1->Location = System::Drawing::Point(12, 12);
            this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(588, 136);
            this->label1->TabIndex = 0;
            this->label1->Text = resources->GetString(L"label1.Text");
            // 
            // groupBox1
            // 
            this->groupBox1->Controls->Add(this->account);
            this->groupBox1->Controls->Add(this->label3);
            this->groupBox1->Controls->Add(this->password);
            this->groupBox1->Controls->Add(this->username);
            this->groupBox1->Controls->Add(this->label2);
            this->groupBox1->Location = System::Drawing::Point(18, 152);
            this->groupBox1->Margin = System::Windows::Forms::Padding(4);
            this->groupBox1->Name = L"groupBox1";
            this->groupBox1->Padding = System::Windows::Forms::Padding(4);
            this->groupBox1->Size = System::Drawing::Size(584, 132);
            this->groupBox1->TabIndex = 1;
            this->groupBox1->TabStop = false;
            this->groupBox1->Text = L"Account";
            // 
            // account
            // 
            this->account->Location = System::Drawing::Point(392, 28);
            this->account->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->account->Name = L"account";
            this->account->Size = System::Drawing::Size(184, 81);
            this->account->TabIndex = 4;
            this->account->TabStop = true;
            this->account->Text = L"Click here to get an account";
            this->account->Click += gcnew System::EventHandler(this, &GalleryUploader::needaccount_Click);
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(6, 76);
            this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(112, 25);
            this->label3->TabIndex = 3;
            this->label3->Text = L"Password:";
            // 
            // password
            // 
            this->password->Location = System::Drawing::Point(128, 78);
            this->password->Margin = System::Windows::Forms::Padding(4);
            this->password->Name = L"password";
            this->password->PasswordChar = '*';
            this->password->Size = System::Drawing::Size(250, 31);
            this->password->TabIndex = 2;
            // 
            // username
            // 
            this->username->Location = System::Drawing::Point(128, 30);
            this->username->Margin = System::Windows::Forms::Padding(4);
            this->username->Name = L"username";
            this->username->Size = System::Drawing::Size(250, 31);
            this->username->TabIndex = 1;
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(6, 36);
            this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(116, 25);
            this->label2->TabIndex = 0;
            this->label2->Text = L"Username:";
            // 
            // groupBox2
            // 
            this->groupBox2->Controls->Add(this->tagsList);
            this->groupBox2->Controls->Add(this->addTag);
            this->groupBox2->Controls->Add(this->label4);
            this->groupBox2->Controls->Add(this->tagBox);
            this->groupBox2->Controls->Add(this->cc_change);
            this->groupBox2->Controls->Add(this->ccname);
            this->groupBox2->Controls->Add(this->ccicon);
            this->groupBox2->Controls->Add(this->label11);
            this->groupBox2->Controls->Add(this->radioPNG8);
            this->groupBox2->Controls->Add(this->radioJPEG);
            this->groupBox2->Controls->Add(this->label10);
            this->groupBox2->Controls->Add(this->label9);
            this->groupBox2->Controls->Add(this->multlabel3);
            this->groupBox2->Controls->Add(this->multheight);
            this->groupBox2->Controls->Add(this->multlabel2);
            this->groupBox2->Controls->Add(this->multwidth);
            this->groupBox2->Controls->Add(this->multlabel1);
            this->groupBox2->Controls->Add(this->uptiled);
            this->groupBox2->Controls->Add(this->crop);
            this->groupBox2->Controls->Add(this->variation);
            this->groupBox2->Controls->Add(this->label8);
            this->groupBox2->Controls->Add(this->label6);
            this->groupBox2->Controls->Add(this->filename);
            this->groupBox2->Controls->Add(this->title);
            this->groupBox2->Controls->Add(this->notes);
            this->groupBox2->Controls->Add(this->label5);
            this->groupBox2->Controls->Add(this->label7);
            this->groupBox2->Location = System::Drawing::Point(18, 288);
            this->groupBox2->Margin = System::Windows::Forms::Padding(4);
            this->groupBox2->Name = L"groupBox2";
            this->groupBox2->Padding = System::Windows::Forms::Padding(4);
            this->groupBox2->Size = System::Drawing::Size(584, 716);
            this->groupBox2->TabIndex = 2;
            this->groupBox2->TabStop = false;
            this->groupBox2->Text = L"Design";
            // 
            // tagsList
            // 
            this->tagsList->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->tagsList->FormattingEnabled = true;
            this->tagsList->Location = System::Drawing::Point(356, 268);
            this->tagsList->Margin = System::Windows::Forms::Padding(4);
            this->tagsList->Name = L"tagsList";
            this->tagsList->Size = System::Drawing::Size(208, 33);
            this->tagsList->TabIndex = 28;
            // 
            // addTag
            // 
            this->addTag->ImageList = this->imageList1;
            this->addTag->Location = System::Drawing::Point(298, 266);
            this->addTag->Margin = System::Windows::Forms::Padding(4);
            this->addTag->Name = L"addTag";
            this->addTag->Size = System::Drawing::Size(40, 40);
            this->addTag->TabIndex = 27;
            this->toolTip1->SetToolTip(this->addTag, L"Save tag to list");
            this->addTag->UseVisualStyleBackColor = true;
            // 
            // imageList1
            // 
            this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList1.ImageStream")));
            this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
            this->imageList1->Images->SetKeyName(0, L"rightpointing_double_angle_quotation_mark.png");
            this->imageList1->Images->SetKeyName(1, L"heavy_x.png");
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(12, 268);
            this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(66, 25);
            this->label4->TabIndex = 26;
            this->label4->Text = L"Tags:";
            // 
            // tagBox
            // 
            this->tagBox->AcceptsReturn = true;
            this->tagBox->Location = System::Drawing::Point(86, 270);
            this->tagBox->Margin = System::Windows::Forms::Padding(4);
            this->tagBox->Name = L"tagBox";
            this->tagBox->Size = System::Drawing::Size(200, 31);
            this->tagBox->TabIndex = 25;
            // 
            // cc_change
            // 
            this->cc_change->FormattingEnabled = true;
            this->cc_change->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
                L"no change", L"Public Domain: CC Zero", L"CC Attribution",
                    L"CC Attribution-ShareAlike", L"CC Attribution-NoDerivatives", L"CC Attribution-NonCommercial", L"CC Attribution-NonCommercial-ShareAlike",
                    L"CC Attribution-NonCommercial-NoDerivatives", L"No CC license, full copyright"
            });
            this->cc_change->Location = System::Drawing::Point(108, 658);
            this->cc_change->Margin = System::Windows::Forms::Padding(4);
            this->cc_change->Name = L"cc_change";
            this->cc_change->Size = System::Drawing::Size(456, 33);
            this->cc_change->TabIndex = 24;
            this->cc_change->SelectedIndexChanged += gcnew System::EventHandler(this, &GalleryUploader::cc_change_select);
            // 
            // ccname
            // 
            this->ccname->Location = System::Drawing::Point(18, 542);
            this->ccname->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->ccname->Name = L"ccname";
            this->ccname->Size = System::Drawing::Size(348, 102);
            this->ccname->TabIndex = 23;
            // 
            // ccicon
            // 
            this->ccicon->Location = System::Drawing::Point(392, 504);
            this->ccicon->Margin = System::Windows::Forms::Padding(4);
            this->ccicon->Name = L"ccicon";
            this->ccicon->Size = System::Drawing::Size(176, 62);
            this->ccicon->TabIndex = 22;
            this->ccicon->TabStop = false;
            this->ccicon->Click += gcnew System::EventHandler(this, &GalleryUploader::navLicense);
            // 
            // label11
            // 
            this->label11->AutoSize = true;
            this->label11->Location = System::Drawing::Point(8, 504);
            this->label11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(93, 25);
            this->label11->TabIndex = 21;
            this->label11->Text = L"License:";
            // 
            // radioPNG8
            // 
            this->radioPNG8->AutoSize = true;
            this->radioPNG8->Location = System::Drawing::Point(476, 388);
            this->radioPNG8->Margin = System::Windows::Forms::Padding(4);
            this->radioPNG8->Name = L"radioPNG8";
            this->radioPNG8->Size = System::Drawing::Size(100, 29);
            this->radioPNG8->TabIndex = 20;
            this->radioPNG8->TabStop = true;
            this->radioPNG8->Text = L"PNG8";
            this->radioPNG8->UseVisualStyleBackColor = true;
            // 
            // radioJPEG
            // 
            this->radioJPEG->AutoSize = true;
            this->radioJPEG->Location = System::Drawing::Point(370, 388);
            this->radioJPEG->Margin = System::Windows::Forms::Padding(4);
            this->radioJPEG->Name = L"radioJPEG";
            this->radioJPEG->Size = System::Drawing::Size(98, 29);
            this->radioJPEG->TabIndex = 19;
            this->radioJPEG->TabStop = true;
            this->radioJPEG->Text = L"JPEG";
            this->radioJPEG->UseVisualStyleBackColor = true;
            // 
            // label10
            // 
            this->label10->Location = System::Drawing::Point(364, 330);
            this->label10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(198, 50);
            this->label10->TabIndex = 18;
            this->label10->Text = L"Gallery image compression:";
            // 
            // label9
            // 
            this->label9->AutoSize = true;
            this->label9->Location = System::Drawing::Point(6, 40);
            this->label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(59, 25);
            this->label9->TabIndex = 17;
            this->label9->Text = L"Title:";
            // 
            // multlabel3
            // 
            this->multlabel3->AutoSize = true;
            this->multlabel3->Location = System::Drawing::Point(496, 454);
            this->multlabel3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->multlabel3->Name = L"multlabel3";
            this->multlabel3->Size = System::Drawing::Size(53, 25);
            this->multlabel3->TabIndex = 16;
            this->multlabel3->Text = L"high";
            // 
            // multheight
            // 
            this->multheight->Location = System::Drawing::Point(368, 450);
            this->multheight->Margin = System::Windows::Forms::Padding(4);
            this->multheight->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            this->multheight->Name = L"multheight";
            this->multheight->Size = System::Drawing::Size(120, 31);
            this->multheight->TabIndex = 15;
            this->multheight->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            // 
            // multlabel2
            // 
            this->multlabel2->AutoSize = true;
            this->multlabel2->Location = System::Drawing::Point(276, 454);
            this->multlabel2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->multlabel2->Name = L"multlabel2";
            this->multlabel2->Size = System::Drawing::Size(85, 25);
            this->multlabel2->TabIndex = 14;
            this->multlabel2->Text = L"wide by";
            // 
            // multwidth
            // 
            this->multwidth->Location = System::Drawing::Point(150, 450);
            this->multwidth->Margin = System::Windows::Forms::Padding(4);
            this->multwidth->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            this->multwidth->Name = L"multwidth";
            this->multwidth->Size = System::Drawing::Size(120, 31);
            this->multwidth->TabIndex = 13;
            this->multwidth->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            // 
            // multlabel1
            // 
            this->multlabel1->AutoSize = true;
            this->multlabel1->Location = System::Drawing::Point(6, 454);
            this->multlabel1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->multlabel1->Name = L"multlabel1";
            this->multlabel1->Size = System::Drawing::Size(137, 25);
            this->multlabel1->TabIndex = 12;
            this->multlabel1->Text = L"Multiply size:";
            // 
            // uptiled
            // 
            this->uptiled->AutoSize = true;
            this->uptiled->Location = System::Drawing::Point(12, 408);
            this->uptiled->Margin = System::Windows::Forms::Padding(4);
            this->uptiled->Name = L"uptiled";
            this->uptiled->Size = System::Drawing::Size(184, 29);
            this->uptiled->TabIndex = 11;
            this->uptiled->Text = L"upload as tiled";
            this->uptiled->UseVisualStyleBackColor = true;
            // 
            // crop
            // 
            this->crop->AutoSize = true;
            this->crop->Location = System::Drawing::Point(12, 408);
            this->crop->Margin = System::Windows::Forms::Padding(4);
            this->crop->Name = L"crop";
            this->crop->Size = System::Drawing::Size(186, 29);
            this->crop->TabIndex = 10;
            this->crop->Text = L"crop the image";
            this->crop->UseVisualStyleBackColor = true;
            // 
            // variation
            // 
            this->variation->AutoSize = true;
            this->variation->Location = System::Drawing::Point(116, 372);
            this->variation->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->variation->Name = L"variation";
            this->variation->Size = System::Drawing::Size(132, 25);
            this->variation->TabIndex = 9;
            this->variation->Text = L"WWWWWW";
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->Location = System::Drawing::Point(6, 368);
            this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(103, 25);
            this->label8->TabIndex = 8;
            this->label8->Text = L"Variation:";
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(6, 330);
            this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(53, 25);
            this->label6->TabIndex = 6;
            this->label6->Text = L"File:";
            // 
            // filename
            // 
            this->filename->Location = System::Drawing::Point(86, 324);
            this->filename->Margin = System::Windows::Forms::Padding(4);
            this->filename->Name = L"filename";
            this->filename->Size = System::Drawing::Size(200, 31);
            this->filename->TabIndex = 5;
            // 
            // title
            // 
            this->title->Location = System::Drawing::Point(86, 40);
            this->title->Margin = System::Windows::Forms::Padding(4);
            this->title->Name = L"title";
            this->title->Size = System::Drawing::Size(476, 31);
            this->title->TabIndex = 3;
            // 
            // notes
            // 
            this->notes->Location = System::Drawing::Point(86, 88);
            this->notes->Margin = System::Windows::Forms::Padding(4);
            this->notes->Multiline = true;
            this->notes->Name = L"notes";
            this->notes->Size = System::Drawing::Size(476, 164);
            this->notes->TabIndex = 4;
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(6, 88);
            this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(74, 25);
            this->label5->TabIndex = 1;
            this->label5->Text = L"Notes:";
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Location = System::Drawing::Point(290, 330);
            this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(59, 25);
            this->label7->TabIndex = 7;
            this->label7->Text = L".cfdg";
            // 
            // message
            // 
            this->message->Location = System::Drawing::Point(18, 1014);
            this->message->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->message->Name = L"message";
            this->message->Size = System::Drawing::Size(344, 77);
            this->message->TabIndex = 3;
            // 
            // cancel
            // 
            this->cancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->cancel->Location = System::Drawing::Point(386, 1012);
            this->cancel->Margin = System::Windows::Forms::Padding(4);
            this->cancel->Name = L"cancel";
            this->cancel->Size = System::Drawing::Size(100, 50);
            this->cancel->TabIndex = 4;
            this->cancel->Text = L"Cancel";
            this->cancel->UseVisualStyleBackColor = true;
            this->cancel->Click += gcnew System::EventHandler(this, &GalleryUploader::cancel_click);
            // 
            // upload
            // 
            this->upload->Location = System::Drawing::Point(502, 1012);
            this->upload->Margin = System::Windows::Forms::Padding(4);
            this->upload->Name = L"upload";
            this->upload->Size = System::Drawing::Size(100, 50);
            this->upload->TabIndex = 5;
            this->upload->Text = L"Upload";
            this->upload->UseVisualStyleBackColor = true;
            this->upload->Click += gcnew System::EventHandler(this, &GalleryUploader::upload_click);
            // 
            // uploadProgress
            // 
            this->uploadProgress->Location = System::Drawing::Point(18, 1016);
            this->uploadProgress->Margin = System::Windows::Forms::Padding(6);
            this->uploadProgress->Name = L"uploadProgress";
            this->uploadProgress->Size = System::Drawing::Size(358, 46);
            this->uploadProgress->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
            this->uploadProgress->TabIndex = 6;
            this->uploadProgress->Visible = false;
            // 
            // GalleryUploader
            // 
            this->AcceptButton = this->upload;
            this->AutoScaleDimensions = System::Drawing::SizeF(192, 192);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
            this->AutoSize = true;
            this->CancelButton = this->cancel;
            this->ClientSize = System::Drawing::Size(614, 1100);
            this->Controls->Add(this->uploadProgress);
            this->Controls->Add(this->upload);
            this->Controls->Add(this->cancel);
            this->Controls->Add(this->message);
            this->Controls->Add(this->groupBox2);
            this->Controls->Add(this->groupBox1);
            this->Controls->Add(this->label1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->Margin = System::Windows::Forms::Padding(4);
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"GalleryUploader";
            this->Text = L"Upload to the Online Gallery";
            this->Shown += gcnew System::EventHandler(this, &GalleryUploader::OnShown);
            this->groupBox1->ResumeLayout(false);
            this->groupBox1->PerformLayout();
            this->groupBox2->ResumeLayout(false);
            this->groupBox2->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ccicon))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->multheight))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->multwidth))->EndInit();
            this->ResumeLayout(false);

        }
#pragma endregion
    private:
        unsigned design_id;
        UploadPrefs^ uploadPrefs;
        System::IO::MemoryStream^ bitmapStream;
        String^ ccurl;
        String^ ccimageurl;
        bool cc_changed;
        bool ignore_next_selection;
        String^ origUsername;
        String^ origPassword;
        System::Drawing::Image^ copyrightSymbol;
        System::ComponentModel::BackgroundWorker^ uploadThread;
        void MoreInitialzation(CFDG::frieze_t fr, int tiled, bool png);
        void RunUploadThread(Object^ sender, DoWorkEventArgs^ e);
        void UploadCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e);
    private: System::Void needaccount_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void cancel_click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void upload_click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void cc_change_select(System::Object^ sender, System::EventArgs^ e);
    private: System::Void navLicense(System::Object^ sender, System::EventArgs^ e);
           void OnShown(System::Object^ sender, System::EventArgs^ e);
           void OnTags(System::Object^ sender, System::Net::DownloadDataCompletedEventArgs^ e);
           void tag_click(System::Object^ sender, System::EventArgs^ e);
           void tag_select(System::Object^ sender, System::EventArgs^ e);
           void tag_focus(System::Object^ sender, System::EventArgs^ e);
           void tag_previewkey(System::Object^ sender, System::Windows::Forms::PreviewKeyDownEventArgs^ e);
           void tag_keypress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
           void tag_keydown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
    };
}
