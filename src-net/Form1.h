// Form1.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2008-2012 John Horigan - john@glyphic.com
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

#include "MRUManager.h"
#include "CFPrefs.h"
#include "ColorCalculator.h"
#include "MessageCtrl.h"
#include "PreferenceDialog.h"
#include "FindReplaceForm.h"

class Renderer;

//using namespace WeifenLuo::WinFormsUI::Docking;

namespace ContextFreeNet {


	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
        Form1(array<System::String^>^ args) : StartArgs(args)
        {
            InitializeComponent();
            //
            //TODO: Add the constructor code here
            //
            MoreInitialization();
        }
        static Form1(void)
        {
            StaticInitialization();
        }

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
			delete mruManager;
		}

    public: OzoneUtil::MRUManager^ mruManager;
            bool overrideMenuColor;
    public: FindReplaceForm^ findForm;
    public: System::String^ saveDirectory;
    public: static CFPrefs^ prefs;
    private: PreferenceDialog^ prefsDialog;
    public: static System::String^ widgetHTML;
    private: ColorCalculator^ colorCalc;
    private: MessageCtrl^ messagePane;
    private: array<System::String^>^ StartArgs;
    public: static System::Windows::Forms::Cursor^ dropperCursor;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
    private: System::Windows::Forms::ToolStripMenuItem^  menuWindow;

    public: System::Windows::Forms::ToolStripMenuItem^  menuFile;
    public: static array<System::Drawing::Bitmap^>^ busyList;
    public: static System::Collections::SortedList^ exampleSet;
    public: static System::Collections::Generic::Dictionary<System::String^, System::Windows::Forms::Form^>^ openFiles;
    private: System::Windows::Forms::ToolStripMenuItem^  menuWelcome;
    public: enum class IdleAction { Nothing, Render, Clear, Load, LoadAndRender };


    private: System::Windows::Forms::ToolStripMenuItem^  menuFNew;
    private: System::Windows::Forms::ToolStripMenuItem^  menuFOpen;
    private: System::Windows::Forms::ToolStripMenuItem^  menuFExit;

    public:  static void DeleteRenderer(Renderer* r);
    private: static void RunDeleteThread(System::Object^ data);

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;

    private: System::Drawing::Font^ textFont;
    public: event System::EventHandler^ TextFontChanged;
    public: property System::Drawing::Font^ TextFont {
                System::Drawing::Font^ get()
                {
                    if (textFont == nullptr)
                        textFont = prefs->TextFont;
                    return textFont;
                }
                void set(System::Drawing::Font^ v) 
                {
                    textFont = v;
                    prefs->TextFont = v;
                    TextFontChanged(this, gcnew System::EventArgs());
                }
            }


    private: System::Windows::Forms::ToolStripMenuItem^  menuFPrefs;
    private: System::Windows::Forms::ToolStripMenuItem^  menuFRecent;
    private: System::Windows::Forms::ToolStripSeparator^  menuFmruSeparator;
    private: System::Windows::Forms::ToolStripMenuItem^  menuExamples;
    public: WeifenLuo::WinFormsUI::Docking::DockPanel^  dockPanel;
    public: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
    private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
    public: 
    private: System::Windows::Forms::ToolStripMenuItem^  contextFreeSiteToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  galleryToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  forumsToolStripMenuItem;
    private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
    private: System::Windows::Forms::ToolStripMenuItem^  sendFeedbackToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  aboutContextFreeToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  writingCFDGFilesToolStripMenuItem;
    private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
    private: System::Windows::Forms::ToolStripMenuItem^  menuRColor;
    private: System::Windows::Forms::ToolStripMenuItem^  menuWMsgConsole;


    protected: 
    virtual void WndProc(System::Windows::Forms::Message% m) override;

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
            System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
            WeifenLuo::WinFormsUI::Docking::DockPanelSkin^  dockPanelSkin1 = (gcnew WeifenLuo::WinFormsUI::Docking::DockPanelSkin());
            WeifenLuo::WinFormsUI::Docking::AutoHideStripSkin^  autoHideStripSkin1 = (gcnew WeifenLuo::WinFormsUI::Docking::AutoHideStripSkin());
            WeifenLuo::WinFormsUI::Docking::DockPanelGradient^  dockPanelGradient1 = (gcnew WeifenLuo::WinFormsUI::Docking::DockPanelGradient());
            WeifenLuo::WinFormsUI::Docking::TabGradient^  tabGradient1 = (gcnew WeifenLuo::WinFormsUI::Docking::TabGradient());
            WeifenLuo::WinFormsUI::Docking::DockPaneStripSkin^  dockPaneStripSkin1 = (gcnew WeifenLuo::WinFormsUI::Docking::DockPaneStripSkin());
            WeifenLuo::WinFormsUI::Docking::DockPaneStripGradient^  dockPaneStripGradient1 = (gcnew WeifenLuo::WinFormsUI::Docking::DockPaneStripGradient());
            WeifenLuo::WinFormsUI::Docking::TabGradient^  tabGradient2 = (gcnew WeifenLuo::WinFormsUI::Docking::TabGradient());
            WeifenLuo::WinFormsUI::Docking::DockPanelGradient^  dockPanelGradient2 = (gcnew WeifenLuo::WinFormsUI::Docking::DockPanelGradient());
            WeifenLuo::WinFormsUI::Docking::TabGradient^  tabGradient3 = (gcnew WeifenLuo::WinFormsUI::Docking::TabGradient());
            WeifenLuo::WinFormsUI::Docking::DockPaneStripToolWindowGradient^  dockPaneStripToolWindowGradient1 = (gcnew WeifenLuo::WinFormsUI::Docking::DockPaneStripToolWindowGradient());
            WeifenLuo::WinFormsUI::Docking::TabGradient^  tabGradient4 = (gcnew WeifenLuo::WinFormsUI::Docking::TabGradient());
            WeifenLuo::WinFormsUI::Docking::TabGradient^  tabGradient5 = (gcnew WeifenLuo::WinFormsUI::Docking::TabGradient());
            WeifenLuo::WinFormsUI::Docking::DockPanelGradient^  dockPanelGradient3 = (gcnew WeifenLuo::WinFormsUI::Docking::DockPanelGradient());
            WeifenLuo::WinFormsUI::Docking::TabGradient^  tabGradient6 = (gcnew WeifenLuo::WinFormsUI::Docking::TabGradient());
            WeifenLuo::WinFormsUI::Docking::TabGradient^  tabGradient7 = (gcnew WeifenLuo::WinFormsUI::Docking::TabGradient());
            this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
            this->menuFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuFNew = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuFOpen = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuFRecent = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuFmruSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->menuFPrefs = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuFExit = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuExamples = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuWindow = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuRColor = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menuWMsgConsole = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->contextFreeSiteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->galleryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->forumsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->writingCFDGFilesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->sendFeedbackToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->aboutContextFreeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
            this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
            this->dockPanel = (gcnew WeifenLuo::WinFormsUI::Docking::DockPanel());
            this->menuStrip1->SuspendLayout();
            this->SuspendLayout();
            // 
            // menuStrip1
            // 
            this->menuStrip1->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
            this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->menuFile, this->menuExamples, 
                this->menuWindow, this->helpToolStripMenuItem});
            this->menuStrip1->Location = System::Drawing::Point(0, 0);
            this->menuStrip1->MdiWindowListItem = this->menuWindow;
            this->menuStrip1->Name = L"menuStrip1";
            this->menuStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
            this->menuStrip1->Size = System::Drawing::Size(1100, 24);
            this->menuStrip1->TabIndex = 1;
            this->menuStrip1->Text = L"menuStrip1";
            // 
            // menuFile
            // 
            this->menuFile->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->menuFNew, this->menuFOpen, 
                this->menuFRecent, this->menuFmruSeparator, this->menuFPrefs, this->menuFExit});
            this->menuFile->MergeAction = System::Windows::Forms::MergeAction::Insert;
            this->menuFile->Name = L"menuFile";
            this->menuFile->Size = System::Drawing::Size(37, 20);
            this->menuFile->Text = L"&File";
            // 
            // menuFNew
            // 
            this->menuFNew->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuFNew.Image")));
            this->menuFNew->Name = L"menuFNew";
            this->menuFNew->ShortcutKeyDisplayString = L"Ctrl-N";
            this->menuFNew->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
            this->menuFNew->Size = System::Drawing::Size(173, 22);
            this->menuFNew->Text = L"&New";
            this->menuFNew->Click += gcnew System::EventHandler(this, &Form1::menuFNew_Click);
            // 
            // menuFOpen
            // 
            this->menuFOpen->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuFOpen.Image")));
            this->menuFOpen->Name = L"menuFOpen";
            this->menuFOpen->ShortcutKeyDisplayString = L"Ctrl-O";
            this->menuFOpen->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
            this->menuFOpen->Size = System::Drawing::Size(173, 22);
            this->menuFOpen->Text = L"&Open";
            this->menuFOpen->Click += gcnew System::EventHandler(this, &Form1::menuFOpen_Click);
            // 
            // menuFRecent
            // 
            this->menuFRecent->Name = L"menuFRecent";
            this->menuFRecent->Size = System::Drawing::Size(173, 22);
            this->menuFRecent->Text = L"Recent files";
            this->menuFRecent->Visible = false;
            // 
            // menuFmruSeparator
            // 
            this->menuFmruSeparator->Name = L"menuFmruSeparator";
            this->menuFmruSeparator->Size = System::Drawing::Size(170, 6);
            // 
            // menuFPrefs
            // 
            this->menuFPrefs->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuFPrefs.Image")));
            this->menuFPrefs->Name = L"menuFPrefs";
            this->menuFPrefs->ShortcutKeyDisplayString = L"Ctrl-P";
            this->menuFPrefs->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::P));
            this->menuFPrefs->Size = System::Drawing::Size(173, 22);
            this->menuFPrefs->Text = L"Preferences";
            this->menuFPrefs->Click += gcnew System::EventHandler(this, &Form1::menuFPrefs_Click);
            // 
            // menuFExit
            // 
            this->menuFExit->Name = L"menuFExit";
            this->menuFExit->Size = System::Drawing::Size(173, 22);
            this->menuFExit->Text = L"E&xit";
            this->menuFExit->Click += gcnew System::EventHandler(this, &Form1::menuFExit_Click);
            // 
            // menuExamples
            // 
            this->menuExamples->Name = L"menuExamples";
            this->menuExamples->Size = System::Drawing::Size(68, 20);
            this->menuExamples->Text = L"E&xamples";
            // 
            // menuWindow
            // 
            this->menuWindow->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->menuRColor, 
                this->menuWMsgConsole, this->toolStripSeparator2});
            this->menuWindow->Name = L"menuWindow";
            this->menuWindow->Size = System::Drawing::Size(63, 20);
            this->menuWindow->Text = L"&Window";
            // 
            // menuRColor
            // 
            this->menuRColor->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuRColor.Image")));
            this->menuRColor->Name = L"menuRColor";
            this->menuRColor->Size = System::Drawing::Size(164, 22);
            this->menuRColor->Text = L"&Color calculator";
            this->menuRColor->Click += gcnew System::EventHandler(this, &Form1::menuRColor_Click);
            // 
            // menuWMsgConsole
            // 
            this->menuWMsgConsole->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuWMsgConsole.Image")));
            this->menuWMsgConsole->Name = L"menuWMsgConsole";
            this->menuWMsgConsole->Size = System::Drawing::Size(164, 22);
            this->menuWMsgConsole->Text = L"&Message console";
            this->menuWMsgConsole->Click += gcnew System::EventHandler(this, &Form1::menuWMsgConsole_Click);
            // 
            // toolStripSeparator2
            // 
            this->toolStripSeparator2->Name = L"toolStripSeparator2";
            this->toolStripSeparator2->Size = System::Drawing::Size(161, 6);
            // 
            // helpToolStripMenuItem
            // 
            this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->contextFreeSiteToolStripMenuItem, 
                this->galleryToolStripMenuItem, this->forumsToolStripMenuItem, this->writingCFDGFilesToolStripMenuItem, this->toolStripSeparator1, 
                this->sendFeedbackToolStripMenuItem, this->aboutContextFreeToolStripMenuItem});
            this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
            this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
            this->helpToolStripMenuItem->Text = L"&Help";
            // 
            // contextFreeSiteToolStripMenuItem
            // 
            this->contextFreeSiteToolStripMenuItem->Name = L"contextFreeSiteToolStripMenuItem";
            this->contextFreeSiteToolStripMenuItem->Size = System::Drawing::Size(179, 22);
            this->contextFreeSiteToolStripMenuItem->Tag = L"http://www.contextfreeart.org/index.html";
            this->contextFreeSiteToolStripMenuItem->Text = L"&Context Free Site...";
            // 
            // galleryToolStripMenuItem
            // 
            this->galleryToolStripMenuItem->Name = L"galleryToolStripMenuItem";
            this->galleryToolStripMenuItem->Size = System::Drawing::Size(179, 22);
            this->galleryToolStripMenuItem->Tag = L"http://www.contextfreeart.org/gallery/";
            this->galleryToolStripMenuItem->Text = L"&Gallery...";
            // 
            // forumsToolStripMenuItem
            // 
            this->forumsToolStripMenuItem->Name = L"forumsToolStripMenuItem";
            this->forumsToolStripMenuItem->Size = System::Drawing::Size(179, 22);
            this->forumsToolStripMenuItem->Tag = L"http://www.contextfreeart.org/phpbb/index.php";
            this->forumsToolStripMenuItem->Text = L"&Forums...";
            // 
            // writingCFDGFilesToolStripMenuItem
            // 
            this->writingCFDGFilesToolStripMenuItem->Name = L"writingCFDGFilesToolStripMenuItem";
            this->writingCFDGFilesToolStripMenuItem->Size = System::Drawing::Size(179, 22);
            this->writingCFDGFilesToolStripMenuItem->Tag = L"http://www.contextfreeart.org/mediawiki/index.php/CFDG_HOWTO";
            this->writingCFDGFilesToolStripMenuItem->Text = L"&Writing CFDG files...";
            // 
            // toolStripSeparator1
            // 
            this->toolStripSeparator1->Name = L"toolStripSeparator1";
            this->toolStripSeparator1->Size = System::Drawing::Size(176, 6);
            // 
            // sendFeedbackToolStripMenuItem
            // 
            this->sendFeedbackToolStripMenuItem->Name = L"sendFeedbackToolStripMenuItem";
            this->sendFeedbackToolStripMenuItem->Size = System::Drawing::Size(179, 22);
            this->sendFeedbackToolStripMenuItem->Tag = L"mailto:info@contextfreeart.org";
            this->sendFeedbackToolStripMenuItem->Text = L"&Send feedback...";
            // 
            // aboutContextFreeToolStripMenuItem
            // 
            this->aboutContextFreeToolStripMenuItem->Name = L"aboutContextFreeToolStripMenuItem";
            this->aboutContextFreeToolStripMenuItem->Size = System::Drawing::Size(179, 22);
            this->aboutContextFreeToolStripMenuItem->Text = L"&About Context Free";
            this->aboutContextFreeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::aboutContextFreeToolStripMenuItem_Click);
            // 
            // saveFileDialog1
            // 
            this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::saveFileDialog1_FileOk);
            // 
            // dockPanel
            // 
            this->dockPanel->ActiveAutoHideContent = nullptr;
            this->dockPanel->AllowEndUserNestedDocking = false;
            this->dockPanel->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
            this->dockPanel->Dock = System::Windows::Forms::DockStyle::Fill;
            this->dockPanel->DockBackColor = System::Drawing::SystemColors::GradientInactiveCaption;
            this->dockPanel->DockBottomPortion = 85;
            this->dockPanel->DockLeftPortion = 100;
            this->dockPanel->DockRightPortion = 365;
            this->dockPanel->Location = System::Drawing::Point(0, 24);
            this->dockPanel->Name = L"dockPanel";
            this->dockPanel->Size = System::Drawing::Size(1100, 691);
            dockPanelGradient1->EndColor = System::Drawing::SystemColors::ControlLight;
            dockPanelGradient1->StartColor = System::Drawing::SystemColors::ControlLight;
            autoHideStripSkin1->DockStripGradient = dockPanelGradient1;
            tabGradient1->EndColor = System::Drawing::SystemColors::Control;
            tabGradient1->StartColor = System::Drawing::SystemColors::Control;
            tabGradient1->TextColor = System::Drawing::SystemColors::ControlDarkDark;
            autoHideStripSkin1->TabGradient = tabGradient1;
            autoHideStripSkin1->TextFont = (gcnew System::Drawing::Font(L"Segoe UI", 9));
            dockPanelSkin1->AutoHideStripSkin = autoHideStripSkin1;
            tabGradient2->EndColor = System::Drawing::SystemColors::ControlLightLight;
            tabGradient2->StartColor = System::Drawing::SystemColors::ControlLightLight;
            tabGradient2->TextColor = System::Drawing::SystemColors::ControlText;
            dockPaneStripGradient1->ActiveTabGradient = tabGradient2;
            dockPanelGradient2->EndColor = System::Drawing::SystemColors::Control;
            dockPanelGradient2->StartColor = System::Drawing::SystemColors::Control;
            dockPaneStripGradient1->DockStripGradient = dockPanelGradient2;
            tabGradient3->EndColor = System::Drawing::SystemColors::ControlLight;
            tabGradient3->StartColor = System::Drawing::SystemColors::ControlLight;
            tabGradient3->TextColor = System::Drawing::SystemColors::ControlText;
            dockPaneStripGradient1->InactiveTabGradient = tabGradient3;
            dockPaneStripSkin1->DocumentGradient = dockPaneStripGradient1;
            dockPaneStripSkin1->TextFont = (gcnew System::Drawing::Font(L"Segoe UI", 9));
            tabGradient4->EndColor = System::Drawing::SystemColors::ActiveCaption;
            tabGradient4->LinearGradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
            tabGradient4->StartColor = System::Drawing::SystemColors::GradientActiveCaption;
            tabGradient4->TextColor = System::Drawing::SystemColors::ActiveCaptionText;
            dockPaneStripToolWindowGradient1->ActiveCaptionGradient = tabGradient4;
            tabGradient5->EndColor = System::Drawing::SystemColors::Control;
            tabGradient5->StartColor = System::Drawing::SystemColors::Control;
            tabGradient5->TextColor = System::Drawing::SystemColors::ControlText;
            dockPaneStripToolWindowGradient1->ActiveTabGradient = tabGradient5;
            dockPanelGradient3->EndColor = System::Drawing::SystemColors::ControlLight;
            dockPanelGradient3->StartColor = System::Drawing::SystemColors::ControlLight;
            dockPaneStripToolWindowGradient1->DockStripGradient = dockPanelGradient3;
            tabGradient6->EndColor = System::Drawing::SystemColors::GradientInactiveCaption;
            tabGradient6->LinearGradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
            tabGradient6->StartColor = System::Drawing::SystemColors::GradientInactiveCaption;
            tabGradient6->TextColor = System::Drawing::SystemColors::ControlText;
            dockPaneStripToolWindowGradient1->InactiveCaptionGradient = tabGradient6;
            tabGradient7->EndColor = System::Drawing::Color::Transparent;
            tabGradient7->StartColor = System::Drawing::Color::Transparent;
            tabGradient7->TextColor = System::Drawing::SystemColors::ControlDarkDark;
            dockPaneStripToolWindowGradient1->InactiveTabGradient = tabGradient7;
            dockPaneStripSkin1->ToolWindowGradient = dockPaneStripToolWindowGradient1;
            dockPanelSkin1->DockPaneStripSkin = dockPaneStripSkin1;
            this->dockPanel->Skin = dockPanelSkin1;
            this->dockPanel->TabIndex = 3;
            // 
            // Form1
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1100, 715);
            this->Controls->Add(this->dockPanel);
            this->Controls->Add(this->menuStrip1);
            this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
            this->IsMdiContainer = true;
            this->MainMenuStrip = this->menuStrip1;
            this->Name = L"Form1";
            this->Text = L"Context Free";
            this->menuStrip1->ResumeLayout(false);
            this->menuStrip1->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
private: System::Void menuFNew_Click(System::Object^  sender, System::EventArgs^  e); 

private: System::Void menuFExit_Click(System::Object^  sender, System::EventArgs^  e); 

private: System::Void menuFOpen_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void menuFPrefs_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void MRU_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void Example_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void Font_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void Form_Loaded(System::Object^  sender, System::EventArgs^  e);

private: void MoreInitialization();
private: static void StaticInitialization();

public: static void addDocumentFile(System::String^ filename, System::Windows::Forms::Form^ doc);
public: static void changeDocumentFile(System::String^ oldname, System::String^ newname, System::Windows::Forms::Form^ doc);
private: static bool fileAlreadyOpen(System::String^ filename);
private: System::Void File_Closed(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
protected: 
System::Void FormIsClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
private: System::EventHandler^ idleHandler;
         System::Void appIsIdle(System::Object^  sender, System::EventArgs^  e);
         System::Void appIsExiting(System::Object^  sender, System::EventArgs^  e);
private: System::Void urlMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void aboutContextFreeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) ;
private: System::Void menuRColor_Click(System::Object^  sender, System::EventArgs^  e);
public: void AddMessage(System::String^ sender, System::String^ msg);
private: System::Void menuWMsgConsole_Click(System::Object^  sender, System::EventArgs^  e);
private: void OpenDoc(System::String^ name);
public: System::Void processArgs(array<System::String^>^ args);
private: void updateFontDisplay();
private: System::Void saveFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
         }
public:  System::Void FindReplace_Click(System::Object^  sender, System::EventArgs^  e);
};
}