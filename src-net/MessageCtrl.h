// MessageCtrl.h
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
	/// Summary for MessageCtrl
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class MessageCtrl : public WeifenLuo::WinFormsUI::Docking::DockContent
	{
	public:
		MessageCtrl(void) : lastSender(System::String::Empty)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

        void AddMessage(System::String^ sender, System::String^ message);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MessageCtrl()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::TextBox^  messageBox;
        System::String^ lastSender;
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
            System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MessageCtrl::typeid));
            this->messageBox = (gcnew System::Windows::Forms::TextBox());
            this->SuspendLayout();
            // 
            // messageBox
            // 
            this->messageBox->BackColor = System::Drawing::SystemColors::ControlLightLight;
            this->messageBox->Dock = System::Windows::Forms::DockStyle::Fill;
            this->messageBox->Location = System::Drawing::Point(0, 0);
            this->messageBox->MaxLength = 1000000;
            this->messageBox->Multiline = true;
            this->messageBox->Name = L"messageBox";
            this->messageBox->ReadOnly = true;
            this->messageBox->Size = System::Drawing::Size(292, 266);
            this->messageBox->TabIndex = 0;
            this->messageBox->TabStop = false;
            // 
            // MessageCtrl
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(292, 266);
            this->Controls->Add(this->messageBox);
            this->DockAreas = static_cast<WeifenLuo::WinFormsUI::Docking::DockAreas>((WeifenLuo::WinFormsUI::Docking::DockAreas::DockRight | WeifenLuo::WinFormsUI::Docking::DockAreas::Document));
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->HideOnClose = true;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
            this->Name = L"MessageCtrl";
            this->TabText = L"Message Console";
            this->Text = L"MessageCtrl";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
	};
}
