#pragma once


namespace CppWrapper {

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
            notFound->ForeColor = System::Drawing::Color::Red;
            System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FindReplaceForm::typeid));
            notFoundSound = gcnew System::Media::SoundPlayer(resources->GetStream(L"Speech Misrecognition"));
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
    public: System::Windows::Forms::Button^  nextButton;
    private:
        System::Media::SoundPlayer^ notFoundSound;
    private: 

    protected: 


    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::TextBox^  replaceText;
    private: System::Windows::Forms::Button^  replaceButton;
    private: System::Windows::Forms::Button^  replaceAllButton;

    private: System::Windows::Forms::CheckBox^  ignoreCaseCheck;
    private: System::Windows::Forms::Button^  replaceAllSelectionButton;



    private: System::Windows::Forms::CheckBox^  wrapAroundCheck;
    private: System::Windows::Forms::Label^  notFound;
    public: System::Windows::Forms::Button^  prevButton;
    private: System::Windows::Forms::RadioButton^  findContains;
    public:
    private: System::Windows::Forms::RadioButton^  findWhole;
    private: System::Windows::Forms::RadioButton^  findStarts;
    private: System::Windows::Forms::Label^  label3;
    private:








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
            System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FindReplaceForm::typeid));
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->findText = (gcnew System::Windows::Forms::TextBox());
            this->nextButton = (gcnew System::Windows::Forms::Button());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->replaceText = (gcnew System::Windows::Forms::TextBox());
            this->replaceButton = (gcnew System::Windows::Forms::Button());
            this->replaceAllButton = (gcnew System::Windows::Forms::Button());
            this->ignoreCaseCheck = (gcnew System::Windows::Forms::CheckBox());
            this->replaceAllSelectionButton = (gcnew System::Windows::Forms::Button());
            this->wrapAroundCheck = (gcnew System::Windows::Forms::CheckBox());
            this->notFound = (gcnew System::Windows::Forms::Label());
            this->prevButton = (gcnew System::Windows::Forms::Button());
            this->findContains = (gcnew System::Windows::Forms::RadioButton());
            this->findWhole = (gcnew System::Windows::Forms::RadioButton());
            this->findStarts = (gcnew System::Windows::Forms::RadioButton());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(12, 9);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(60, 26);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Find:";
            // 
            // findText
            // 
            this->findText->Location = System::Drawing::Point(78, 6);
            this->findText->Name = L"findText";
            this->findText->Size = System::Drawing::Size(216, 32);
            this->findText->TabIndex = 1;
            this->findText->TextChanged += gcnew System::EventHandler(this, &FindReplaceForm::findText_Changed);
            // 
            // nextButton
            // 
            this->nextButton->Enabled = false;
            this->nextButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->nextButton->Location = System::Drawing::Point(366, 4);
            this->nextButton->Name = L"nextButton";
            this->nextButton->Size = System::Drawing::Size(48, 40);
            this->nextButton->TabIndex = 3;
            this->nextButton->Text = L"▶";
            this->nextButton->UseVisualStyleBackColor = true;
            this->nextButton->Click += gcnew System::EventHandler(this, &FindReplaceForm::find_Click);
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(417, 9);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(98, 26);
            this->label2->TabIndex = 3;
            this->label2->Text = L"Replace:";
            // 
            // replaceText
            // 
            this->replaceText->Location = System::Drawing::Point(521, 4);
            this->replaceText->Name = L"replaceText";
            this->replaceText->Size = System::Drawing::Size(234, 32);
            this->replaceText->TabIndex = 4;
            // 
            // replaceButton
            // 
            this->replaceButton->Enabled = false;
            this->replaceButton->Location = System::Drawing::Point(774, 4);
            this->replaceButton->Name = L"replaceButton";
            this->replaceButton->Size = System::Drawing::Size(120, 40);
            this->replaceButton->TabIndex = 5;
            this->replaceButton->Text = L"&Replace";
            this->replaceButton->UseVisualStyleBackColor = true;
            this->replaceButton->Click += gcnew System::EventHandler(this, &FindReplaceForm::replace_Click);
            // 
            // replaceAllButton
            // 
            this->replaceAllButton->Enabled = false;
            this->replaceAllButton->Location = System::Drawing::Point(901, 4);
            this->replaceAllButton->Name = L"replaceAllButton";
            this->replaceAllButton->Size = System::Drawing::Size(61, 40);
            this->replaceAllButton->TabIndex = 6;
            this->replaceAllButton->Text = L"&All";
            this->replaceAllButton->UseVisualStyleBackColor = true;
            this->replaceAllButton->Click += gcnew System::EventHandler(this, &FindReplaceForm::replaceAll_Click);
            // 
            // ignoreCaseCheck
            // 
            this->ignoreCaseCheck->AutoSize = true;
            this->ignoreCaseCheck->Location = System::Drawing::Point(139, 56);
            this->ignoreCaseCheck->Name = L"ignoreCaseCheck";
            this->ignoreCaseCheck->Size = System::Drawing::Size(162, 30);
            this->ignoreCaseCheck->TabIndex = 8;
            this->ignoreCaseCheck->Text = L"&Ignore Case";
            this->ignoreCaseCheck->UseVisualStyleBackColor = true;
            // 
            // replaceAllSelectionButton
            // 
            this->replaceAllSelectionButton->Enabled = false;
            this->replaceAllSelectionButton->Location = System::Drawing::Point(970, 4);
            this->replaceAllSelectionButton->Name = L"replaceAllSelectionButton";
            this->replaceAllSelectionButton->Size = System::Drawing::Size(155, 40);
            this->replaceAllSelectionButton->TabIndex = 7;
            this->replaceAllSelectionButton->Text = L"in &Selection";
            this->replaceAllSelectionButton->UseVisualStyleBackColor = true;
            this->replaceAllSelectionButton->Click += gcnew System::EventHandler(this, &FindReplaceForm::replaceAllSelection_Click);
            // 
            // wrapAroundCheck
            // 
            this->wrapAroundCheck->AutoSize = true;
            this->wrapAroundCheck->Location = System::Drawing::Point(327, 56);
            this->wrapAroundCheck->Name = L"wrapAroundCheck";
            this->wrapAroundCheck->Size = System::Drawing::Size(172, 30);
            this->wrapAroundCheck->TabIndex = 11;
            this->wrapAroundCheck->Text = L"Wrap Around";
            this->wrapAroundCheck->UseVisualStyleBackColor = true;
            // 
            // notFound
            // 
            this->notFound->AutoSize = true;
            this->notFound->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->notFound->ForeColor = System::Drawing::SystemColors::Highlight;
            this->notFound->Location = System::Drawing::Point(12, 57);
            this->notFound->Name = L"notFound";
            this->notFound->Size = System::Drawing::Size(115, 26);
            this->notFound->TabIndex = 12;
            this->notFound->Text = L"Not found";
            this->notFound->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            this->notFound->Visible = false;
            // 
            // prevButton
            // 
            this->prevButton->Enabled = false;
            this->prevButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->prevButton->Location = System::Drawing::Point(312, 4);
            this->prevButton->Name = L"prevButton";
            this->prevButton->Size = System::Drawing::Size(48, 40);
            this->prevButton->TabIndex = 2;
            this->prevButton->Tag = L"prev";
            this->prevButton->Text = L"◀";
            this->prevButton->UseVisualStyleBackColor = true;
            this->prevButton->Click += gcnew System::EventHandler(this, &FindReplaceForm::prev_Click);
            // 
            // findContains
            // 
            this->findContains->AutoSize = true;
            this->findContains->Location = System::Drawing::Point(694, 56);
            this->findContains->Name = L"findContains";
            this->findContains->Size = System::Drawing::Size(129, 30);
            this->findContains->TabIndex = 14;
            this->findContains->TabStop = true;
            this->findContains->Text = L"Contains";
            this->findContains->UseVisualStyleBackColor = true;
            // 
            // findWhole
            // 
            this->findWhole->AutoSize = true;
            this->findWhole->Location = System::Drawing::Point(836, 56);
            this->findWhole->Name = L"findWhole";
            this->findWhole->Size = System::Drawing::Size(158, 30);
            this->findWhole->TabIndex = 15;
            this->findWhole->TabStop = true;
            this->findWhole->Text = L"Whole word";
            this->findWhole->UseVisualStyleBackColor = true;
            // 
            // findStarts
            // 
            this->findStarts->AutoSize = true;
            this->findStarts->Location = System::Drawing::Point(1006, 56);
            this->findStarts->Name = L"findStarts";
            this->findStarts->Size = System::Drawing::Size(145, 30);
            this->findStarts->TabIndex = 16;
            this->findStarts->TabStop = true;
            this->findStarts->Text = L"Starts with";
            this->findStarts->UseVisualStyleBackColor = true;
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(522, 58);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(159, 26);
            this->label3->TabIndex = 17;
            this->label3->Text = L"Search phrase:";
            // 
            // FindReplaceForm
            // 
            this->AllowEndUserDocking = false;
            this->AutoHidePortion = 75;
            this->AutoScaleDimensions = System::Drawing::SizeF(13, 26);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1177, 100);
            this->ControlBox = false;
            this->Controls->Add(this->findStarts);
            this->Controls->Add(this->findWhole);
            this->Controls->Add(this->findContains);
            this->Controls->Add(this->prevButton);
            this->Controls->Add(this->notFound);
            this->Controls->Add(this->replaceAllSelectionButton);
            this->Controls->Add(this->ignoreCaseCheck);
            this->Controls->Add(this->replaceAllButton);
            this->Controls->Add(this->replaceButton);
            this->Controls->Add(this->replaceText);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->nextButton);
            this->Controls->Add(this->findText);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->wrapAroundCheck);
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
private: enum class ReplaceType
{
    Once, All, Selection
};
private: System::Void findText_Changed(System::Object^  sender, System::EventArgs^  e);
private: System::Void find_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void replace_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void replaceAll_Click(System::Object^  sender, System::EventArgs^  e);
private: bool doFind(bool forward);
private: int foundStart = 0;
private: int foundEnd = 0;
private: void doReplace(ReplaceType rt);
public:  ScintillaNET::Scintilla^ currentScintilla = nullptr;
private: System::Void prev_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void replaceAllSelection_Click(System::Object^  sender, System::EventArgs^  e);

};
}
