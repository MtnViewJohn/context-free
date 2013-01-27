#pragma once


namespace ContextFreeNet {

	/// <summary>
	/// Summary for FindReplaceForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class FindReplaceForm : public WeifenLuo::WinFormsUI::Docking::DockContent
	{
	public:
		FindReplaceForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FindReplaceForm()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::TextBox^  findText;
    public: System::Windows::Forms::Button^  findButton;
    private: 

    protected: 


    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::TextBox^  replaceText;
    private: System::Windows::Forms::Button^  replaceButton;
    private: System::Windows::Forms::Button^  replaceAllButton;

    private: System::Windows::Forms::CheckBox^  ignoreCaseCheck;
    private: System::Windows::Forms::CheckBox^  wholeCheck;
    private: System::Windows::Forms::CheckBox^  upwardCheck;
    private: System::Windows::Forms::Button^  replaceFindButton;
    private: System::Windows::Forms::CheckBox^  wrapAroundCheck;
    private: System::Windows::Forms::Label^  notFound;








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
            this->findText = (gcnew System::Windows::Forms::TextBox());
            this->findButton = (gcnew System::Windows::Forms::Button());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->replaceText = (gcnew System::Windows::Forms::TextBox());
            this->replaceButton = (gcnew System::Windows::Forms::Button());
            this->replaceAllButton = (gcnew System::Windows::Forms::Button());
            this->ignoreCaseCheck = (gcnew System::Windows::Forms::CheckBox());
            this->wholeCheck = (gcnew System::Windows::Forms::CheckBox());
            this->upwardCheck = (gcnew System::Windows::Forms::CheckBox());
            this->replaceFindButton = (gcnew System::Windows::Forms::Button());
            this->wrapAroundCheck = (gcnew System::Windows::Forms::CheckBox());
            this->notFound = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(12, 9);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(30, 13);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Find:";
            // 
            // findText
            // 
            this->findText->Location = System::Drawing::Point(48, 6);
            this->findText->Name = L"findText";
            this->findText->Size = System::Drawing::Size(100, 20);
            this->findText->TabIndex = 1;
            this->findText->TextChanged += gcnew System::EventHandler(this, &FindReplaceForm::findText_Changed);
            // 
            // findButton
            // 
            this->findButton->Enabled = false;
            this->findButton->Location = System::Drawing::Point(154, 4);
            this->findButton->Name = L"findButton";
            this->findButton->Size = System::Drawing::Size(75, 23);
            this->findButton->TabIndex = 2;
            this->findButton->Text = L"&Find";
            this->findButton->UseVisualStyleBackColor = true;
            this->findButton->Click += gcnew System::EventHandler(this, &FindReplaceForm::find_Click);
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(236, 9);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(50, 13);
            this->label2->TabIndex = 3;
            this->label2->Text = L"Replace:";
            // 
            // replaceText
            // 
            this->replaceText->Location = System::Drawing::Point(292, 6);
            this->replaceText->Name = L"replaceText";
            this->replaceText->Size = System::Drawing::Size(100, 20);
            this->replaceText->TabIndex = 4;
            // 
            // replaceButton
            // 
            this->replaceButton->Enabled = false;
            this->replaceButton->Location = System::Drawing::Point(398, 4);
            this->replaceButton->Name = L"replaceButton";
            this->replaceButton->Size = System::Drawing::Size(75, 23);
            this->replaceButton->TabIndex = 5;
            this->replaceButton->Text = L"&Replace";
            this->replaceButton->UseVisualStyleBackColor = true;
            this->replaceButton->Click += gcnew System::EventHandler(this, &FindReplaceForm::replace_Click);
            // 
            // replaceAllButton
            // 
            this->replaceAllButton->Enabled = false;
            this->replaceAllButton->Location = System::Drawing::Point(479, 33);
            this->replaceAllButton->Name = L"replaceAllButton";
            this->replaceAllButton->Size = System::Drawing::Size(91, 23);
            this->replaceAllButton->TabIndex = 7;
            this->replaceAllButton->Text = L"Replace &All";
            this->replaceAllButton->UseVisualStyleBackColor = true;
            this->replaceAllButton->Click += gcnew System::EventHandler(this, &FindReplaceForm::replaceAll_Click);
            // 
            // ignoreCaseCheck
            // 
            this->ignoreCaseCheck->AutoSize = true;
            this->ignoreCaseCheck->Location = System::Drawing::Point(104, 33);
            this->ignoreCaseCheck->Name = L"ignoreCaseCheck";
            this->ignoreCaseCheck->Size = System::Drawing::Size(83, 17);
            this->ignoreCaseCheck->TabIndex = 8;
            this->ignoreCaseCheck->Text = L"&Ignore Case";
            this->ignoreCaseCheck->UseVisualStyleBackColor = true;
            // 
            // wholeCheck
            // 
            this->wholeCheck->AutoSize = true;
            this->wholeCheck->Location = System::Drawing::Point(194, 34);
            this->wholeCheck->Name = L"wholeCheck";
            this->wholeCheck->Size = System::Drawing::Size(91, 17);
            this->wholeCheck->TabIndex = 9;
            this->wholeCheck->Text = L"&Whole Words";
            this->wholeCheck->UseVisualStyleBackColor = true;
            // 
            // upwardCheck
            // 
            this->upwardCheck->AutoSize = true;
            this->upwardCheck->Location = System::Drawing::Point(292, 33);
            this->upwardCheck->Name = L"upwardCheck";
            this->upwardCheck->Size = System::Drawing::Size(86, 17);
            this->upwardCheck->TabIndex = 10;
            this->upwardCheck->Text = L"Find &Upward";
            this->upwardCheck->UseVisualStyleBackColor = true;
            // 
            // replaceFindButton
            // 
            this->replaceFindButton->Location = System::Drawing::Point(479, 4);
            this->replaceFindButton->Name = L"replaceFindButton";
            this->replaceFindButton->Size = System::Drawing::Size(91, 23);
            this->replaceFindButton->TabIndex = 6;
            this->replaceFindButton->Text = L"Replace && Find";
            this->replaceFindButton->UseVisualStyleBackColor = true;
            this->replaceFindButton->Click += gcnew System::EventHandler(this, &FindReplaceForm::replaceFind_Click);
            // 
            // wrapAroundCheck
            // 
            this->wrapAroundCheck->AutoSize = true;
            this->wrapAroundCheck->Location = System::Drawing::Point(385, 33);
            this->wrapAroundCheck->Name = L"wrapAroundCheck";
            this->wrapAroundCheck->Size = System::Drawing::Size(89, 17);
            this->wrapAroundCheck->TabIndex = 11;
            this->wrapAroundCheck->Text = L"Wrap Around";
            this->wrapAroundCheck->UseVisualStyleBackColor = true;
            // 
            // notFound
            // 
            this->notFound->AutoSize = true;
            this->notFound->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->notFound->ForeColor = System::Drawing::SystemColors::GrayText;
            this->notFound->Location = System::Drawing::Point(13, 34);
            this->notFound->Name = L"notFound";
            this->notFound->Size = System::Drawing::Size(54, 13);
            this->notFound->TabIndex = 12;
            this->notFound->Text = L"Not found";
            this->notFound->Visible = false;
            // 
            // FindReplaceForm
            // 
            this->AllowEndUserDocking = false;
            this->AutoHidePortion = 75;
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(607, 60);
            this->ControlBox = false;
            this->Controls->Add(this->notFound);
            this->Controls->Add(this->wrapAroundCheck);
            this->Controls->Add(this->replaceFindButton);
            this->Controls->Add(this->upwardCheck);
            this->Controls->Add(this->wholeCheck);
            this->Controls->Add(this->ignoreCaseCheck);
            this->Controls->Add(this->replaceAllButton);
            this->Controls->Add(this->replaceButton);
            this->Controls->Add(this->replaceText);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->findButton);
            this->Controls->Add(this->findText);
            this->Controls->Add(this->label1);
            this->DockAreas = WeifenLuo::WinFormsUI::Docking::DockAreas::DockBottom;
            this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->HideOnClose = true;
            this->Name = L"FindReplaceForm";
            this->Text = L"Find/Replace";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
private: System::Void findText_Changed(System::Object^  sender, System::EventArgs^  e);
private: System::Void find_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void replace_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void replaceAll_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void replaceFind_Click(System::Object^  sender, System::EventArgs^  e);
private: bool doFind(System::Windows::Forms::RichTextBox^ rtb, bool allMode);
private: System::Windows::Forms::RichTextBox^ doReplace(System::Windows::Forms::RichTextBox^ rtb);
private: System::Windows::Forms::RichTextBox^ getRTB();
};
}
