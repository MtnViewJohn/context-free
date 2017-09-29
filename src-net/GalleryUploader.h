#pragma once
#include "cfdg.h"

namespace ContextFreeNet {
    ref class Document;

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
		GalleryUploader(Document^ doc, String^ name, CFDG::frieze_t fr, int tiled, 
            bool png, int var_, const char* cfdg, array<double>^ mult)
            : design_id(0), document(doc), cfdgtext(cfdg), outputMultiplier(mult),
              var(var_)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
            MoreInitialzation(name, fr, tiled, png);
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
    private: System::Windows::Forms::Label^  label1;
    protected:
    private: System::Windows::Forms::GroupBox^  groupBox1;
    private: System::Windows::Forms::LinkLabel^  account;
    private: System::Windows::Forms::Label^  label3;
    private: System::Windows::Forms::TextBox^  password;
    private: System::Windows::Forms::TextBox^  username;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::GroupBox^  groupBox2;
    private: System::Windows::Forms::ComboBox^  cc_change;
    private: System::Windows::Forms::Label^  ccname;
    private: System::Windows::Forms::PictureBox^  ccicon;
    private: System::Windows::Forms::Label^  label11;
    private: System::Windows::Forms::RadioButton^  radioPNG8;
    private: System::Windows::Forms::RadioButton^  radioJPEG;
    private: System::Windows::Forms::Label^  label10;
    private: System::Windows::Forms::Label^  label9;
    private: System::Windows::Forms::Label^  multlabel3;
    private: System::Windows::Forms::NumericUpDown^  multheight;
    private: System::Windows::Forms::Label^  multlabel2;
    private: System::Windows::Forms::NumericUpDown^  multwidth;
    private: System::Windows::Forms::Label^  multlabel1;
    private: System::Windows::Forms::CheckBox^  uptiled;
    private: System::Windows::Forms::CheckBox^  crop;
    private: System::Windows::Forms::Label^  variation;
    private: System::Windows::Forms::Label^  label8;
    private: System::Windows::Forms::Label^  label6;
    private: System::Windows::Forms::TextBox^  filename;
    private: System::Windows::Forms::TextBox^  title;
    private: System::Windows::Forms::TextBox^  notes;
    private: System::Windows::Forms::Label^  label5;
    private: System::Windows::Forms::Label^  label7;
    private: System::Windows::Forms::Label^  message;
    private: System::Windows::Forms::Button^  cancel;
    private: System::Windows::Forms::Button^  upload;

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
            System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(GalleryUploader::typeid));
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->username = (gcnew System::Windows::Forms::TextBox());
            this->password = (gcnew System::Windows::Forms::TextBox());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->account = (gcnew System::Windows::Forms::LinkLabel());
            this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->notes = (gcnew System::Windows::Forms::TextBox());
            this->title = (gcnew System::Windows::Forms::TextBox());
            this->filename = (gcnew System::Windows::Forms::TextBox());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->variation = (gcnew System::Windows::Forms::Label());
            this->crop = (gcnew System::Windows::Forms::CheckBox());
            this->uptiled = (gcnew System::Windows::Forms::CheckBox());
            this->multlabel1 = (gcnew System::Windows::Forms::Label());
            this->multwidth = (gcnew System::Windows::Forms::NumericUpDown());
            this->multlabel2 = (gcnew System::Windows::Forms::Label());
            this->multheight = (gcnew System::Windows::Forms::NumericUpDown());
            this->multlabel3 = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->radioJPEG = (gcnew System::Windows::Forms::RadioButton());
            this->radioPNG8 = (gcnew System::Windows::Forms::RadioButton());
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->ccicon = (gcnew System::Windows::Forms::PictureBox());
            this->ccname = (gcnew System::Windows::Forms::Label());
            this->cc_change = (gcnew System::Windows::Forms::ComboBox());
            this->message = (gcnew System::Windows::Forms::Label());
            this->cancel = (gcnew System::Windows::Forms::Button());
            this->upload = (gcnew System::Windows::Forms::Button());
            this->groupBox1->SuspendLayout();
            this->groupBox2->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->multwidth))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->multheight))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ccicon))->BeginInit();
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->Location = System::Drawing::Point(13, 13);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(589, 135);
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
            this->groupBox1->Location = System::Drawing::Point(18, 151);
            this->groupBox1->Name = L"groupBox1";
            this->groupBox1->Size = System::Drawing::Size(584, 131);
            this->groupBox1->TabIndex = 1;
            this->groupBox1->TabStop = false;
            this->groupBox1->Text = L"Account";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(6, 37);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(116, 25);
            this->label2->TabIndex = 0;
            this->label2->Text = L"Username:";
            // 
            // username
            // 
            this->username->Location = System::Drawing::Point(129, 30);
            this->username->Name = L"username";
            this->username->Size = System::Drawing::Size(250, 31);
            this->username->TabIndex = 1;
            // 
            // password
            // 
            this->password->Location = System::Drawing::Point(129, 78);
            this->password->Name = L"password";
            this->password->PasswordChar = '*';
            this->password->Size = System::Drawing::Size(250, 31);
            this->password->TabIndex = 2;
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(6, 76);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(112, 25);
            this->label3->TabIndex = 3;
            this->label3->Text = L"Password:";
            // 
            // account
            // 
            this->account->Location = System::Drawing::Point(405, 37);
            this->account->Name = L"account";
            this->account->Size = System::Drawing::Size(158, 62);
            this->account->TabIndex = 4;
            this->account->TabStop = true;
            this->account->Text = L"Click here to get an account";
            this->account->Click += gcnew System::EventHandler(this, &GalleryUploader::needaccount_Click);
            // 
            // groupBox2
            // 
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
            this->groupBox2->Location = System::Drawing::Point(18, 289);
            this->groupBox2->Name = L"groupBox2";
            this->groupBox2->Size = System::Drawing::Size(584, 647);
            this->groupBox2->TabIndex = 2;
            this->groupBox2->TabStop = false;
            this->groupBox2->Text = L"Design";
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(6, 89);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(74, 25);
            this->label5->TabIndex = 1;
            this->label5->Text = L"Notes:";
            // 
            // notes
            // 
            this->notes->Location = System::Drawing::Point(86, 89);
            this->notes->Multiline = true;
            this->notes->Name = L"notes";
            this->notes->Size = System::Drawing::Size(477, 163);
            this->notes->TabIndex = 4;
            // 
            // title
            // 
            this->title->Location = System::Drawing::Point(86, 41);
            this->title->Name = L"title";
            this->title->Size = System::Drawing::Size(477, 31);
            this->title->TabIndex = 3;
            // 
            // filename
            // 
            this->filename->Location = System::Drawing::Point(86, 269);
            this->filename->Name = L"filename";
            this->filename->Size = System::Drawing::Size(200, 31);
            this->filename->TabIndex = 5;
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(6, 274);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(53, 25);
            this->label6->TabIndex = 6;
            this->label6->Text = L"File:";
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Location = System::Drawing::Point(285, 274);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(59, 25);
            this->label7->TabIndex = 7;
            this->label7->Text = L".cfdg";
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->Location = System::Drawing::Point(6, 313);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(103, 25);
            this->label8->TabIndex = 8;
            this->label8->Text = L"Variation:";
            // 
            // variation
            // 
            this->variation->AutoSize = true;
            this->variation->Location = System::Drawing::Point(116, 317);
            this->variation->Name = L"variation";
            this->variation->Size = System::Drawing::Size(132, 25);
            this->variation->TabIndex = 9;
            this->variation->Text = L"WWWWWW";
            // 
            // crop
            // 
            this->crop->AutoSize = true;
            this->crop->Location = System::Drawing::Point(11, 352);
            this->crop->Name = L"crop";
            this->crop->Size = System::Drawing::Size(186, 29);
            this->crop->TabIndex = 10;
            this->crop->Text = L"crop the image";
            this->crop->UseVisualStyleBackColor = true;
            // 
            // uptiled
            // 
            this->uptiled->AutoSize = true;
            this->uptiled->Location = System::Drawing::Point(11, 388);
            this->uptiled->Name = L"uptiled";
            this->uptiled->Size = System::Drawing::Size(184, 29);
            this->uptiled->TabIndex = 11;
            this->uptiled->Text = L"upload as tiled";
            this->uptiled->UseVisualStyleBackColor = true;
            // 
            // multlabel1
            // 
            this->multlabel1->AutoSize = true;
            this->multlabel1->Location = System::Drawing::Point(6, 434);
            this->multlabel1->Name = L"multlabel1";
            this->multlabel1->Size = System::Drawing::Size(137, 25);
            this->multlabel1->TabIndex = 12;
            this->multlabel1->Text = L"Multiply size:";
            // 
            // multwidth
            // 
            this->multwidth->Location = System::Drawing::Point(150, 430);
            this->multwidth->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            this->multwidth->Name = L"multwidth";
            this->multwidth->Size = System::Drawing::Size(120, 31);
            this->multwidth->TabIndex = 13;
            this->multwidth->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            // 
            // multlabel2
            // 
            this->multlabel2->AutoSize = true;
            this->multlabel2->Location = System::Drawing::Point(277, 434);
            this->multlabel2->Name = L"multlabel2";
            this->multlabel2->Size = System::Drawing::Size(85, 25);
            this->multlabel2->TabIndex = 14;
            this->multlabel2->Text = L"wide by";
            // 
            // multheight
            // 
            this->multheight->Location = System::Drawing::Point(369, 430);
            this->multheight->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            this->multheight->Name = L"multheight";
            this->multheight->Size = System::Drawing::Size(120, 31);
            this->multheight->TabIndex = 15;
            this->multheight->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            // 
            // multlabel3
            // 
            this->multlabel3->AutoSize = true;
            this->multlabel3->Location = System::Drawing::Point(496, 434);
            this->multlabel3->Name = L"multlabel3";
            this->multlabel3->Size = System::Drawing::Size(53, 25);
            this->multlabel3->TabIndex = 16;
            this->multlabel3->Text = L"high";
            // 
            // label9
            // 
            this->label9->AutoSize = true;
            this->label9->Location = System::Drawing::Point(6, 41);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(70, 25);
            this->label9->TabIndex = 17;
            this->label9->Text = L"Title:";
            // 
            // label10
            // 
            this->label10->Location = System::Drawing::Point(365, 274);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(144, 50);
            this->label10->TabIndex = 18;
            this->label10->Text = L"Gallery image compression:";
            // 
            // radioJPEG
            // 
            this->radioJPEG->AutoSize = true;
            this->radioJPEG->Location = System::Drawing::Point(370, 332);
            this->radioJPEG->Name = L"radioJPEG";
            this->radioJPEG->Size = System::Drawing::Size(98, 29);
            this->radioJPEG->TabIndex = 19;
            this->radioJPEG->TabStop = true;
            this->radioJPEG->Text = L"JPEG";
            this->radioJPEG->UseVisualStyleBackColor = true;
            // 
            // radioPNG8
            // 
            this->radioPNG8->AutoSize = true;
            this->radioPNG8->Location = System::Drawing::Point(475, 332);
            this->radioPNG8->Name = L"radioPNG8";
            this->radioPNG8->Size = System::Drawing::Size(100, 29);
            this->radioPNG8->TabIndex = 20;
            this->radioPNG8->TabStop = true;
            this->radioPNG8->Text = L"PNG8";
            this->radioPNG8->UseVisualStyleBackColor = true;
            // 
            // label11
            // 
            this->label11->AutoSize = true;
            this->label11->Location = System::Drawing::Point(8, 475);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(93, 25);
            this->label11->TabIndex = 21;
            this->label11->Text = L"License:";
            // 
            // ccicon
            // 
            this->ccicon->Location = System::Drawing::Point(108, 475);
            this->ccicon->Name = L"ccicon";
            this->ccicon->Size = System::Drawing::Size(176, 62);
            this->ccicon->TabIndex = 22;
            this->ccicon->TabStop = false;
            this->ccicon->Click += gcnew System::EventHandler(this, &GalleryUploader::navLicense);
            // 
            // ccname
            // 
            this->ccname->Location = System::Drawing::Point(291, 475);
            this->ccname->Name = L"ccname";
            this->ccname->Size = System::Drawing::Size(272, 110); // was 93
            this->ccname->TabIndex = 23;
            // 
            // cc_change
            // 
            this->cc_change->FormattingEnabled = true;
            this->cc_change->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
                L"no change", L"Public Domain: CC Zero", L"CC Attribution",
                    L"CC Attribution-ShareAlike", L"CC Attribution-NoDerivatives", L"CC Attribution-NonCommercial", L"CC Attribution-NonCommercial-ShareAlike",
                    L"CC Attribution-NonCommercial-NoDerivatives", L"No CC license, full copyright"
            });
            this->cc_change->Location = System::Drawing::Point(108, 585);
            this->cc_change->Name = L"cc_change";
            this->cc_change->Size = System::Drawing::Size(455, 33);
            this->cc_change->TabIndex = 24;
            this->cc_change->SelectedIndexChanged += gcnew System::EventHandler(this, &GalleryUploader::cc_change_select);
            // 
            // message
            // 
            this->message->Location = System::Drawing::Point(18, 943);
            this->message->Name = L"message";
            this->message->Size = System::Drawing::Size(344, 50);
            this->message->TabIndex = 3;
            // 
            // cancel
            // 
            this->cancel->Location = System::Drawing::Point(386, 943);
            this->cancel->Name = L"cancel";
            this->cancel->Size = System::Drawing::Size(100, 50);
            this->cancel->TabIndex = 4;
            this->cancel->Text = L"Cancel";
            this->cancel->UseVisualStyleBackColor = true;
            this->cancel->Click += gcnew System::EventHandler(this, &GalleryUploader::cancel_click);
            // 
            // upload
            // 
            this->upload->Location = System::Drawing::Point(502, 943);
            this->upload->Name = L"upload";
            this->upload->Size = System::Drawing::Size(100, 50);
            this->upload->TabIndex = 5;
            this->upload->Text = L"Upload";
            this->upload->UseVisualStyleBackColor = true;
            this->upload->Click += gcnew System::EventHandler(this, &GalleryUploader::upload_click);
            // 
            // GalleryUploader
            // 
            this->AcceptButton = this->upload;
            this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->CancelButton = this->cancel;
            this->ClientSize = System::Drawing::Size(614, 1010);
            this->Controls->Add(this->upload);
            this->Controls->Add(this->cancel);
            this->Controls->Add(this->message);
            this->Controls->Add(this->groupBox2);
            this->Controls->Add(this->groupBox1);
            this->Controls->Add(this->label1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"GalleryUploader";
            this->Shown += gcnew System::EventHandler(this, &GalleryUploader::OnShown);
            this->Text = L"Upload to the Online Gallery";
            this->groupBox1->ResumeLayout(false);
            this->groupBox1->PerformLayout();
            this->groupBox2->ResumeLayout(false);
            this->groupBox2->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->multwidth))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->multheight))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ccicon))->EndInit();
            this->ResumeLayout(false);

        }
#pragma endregion
        private:
            unsigned design_id;
            Document^ document;
            const char* cfdgtext;
            array<double>^ outputMultiplier;
            int var;
            String^ ccurl;
            String^ ccimageurl;
            bool cc_changed;
            String^ origUsername;
            String^ origPassword;
            System::Drawing::Image^ copyrightSymbol;
            System::ComponentModel::BackgroundWorker^ uploadThread;
            void MoreInitialzation(String^ name, CFDG::frieze_t fr, int tiled, bool png);
            void RunUploadThread(Object^ sender, DoWorkEventArgs^ e);
            void UploadCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e);
private: System::Void needaccount_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void cancel_click(System::Object^  sender, System::EventArgs^  e);
private: System::Void upload_click(System::Object^  sender, System::EventArgs^  e);
private: System::Void cc_change_select(System::Object^  sender, System::EventArgs^  e);
private: System::Void navLicense(System::Object^  sender, System::EventArgs^  e);	
         void OnShown(System::Object ^sender, System::EventArgs ^e);
};
}
