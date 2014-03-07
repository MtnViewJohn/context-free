// Form1.cpp
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

#include "stdafx.h"
#include "Form1.h"
#include "Document.h"
#include "MRUManager.h"
#include "WinSystem.h"
#include "PreferenceDialog.h"
#include "AboutBox.h"
#include "ColorCalculator.h"

using namespace ContextFreeNet;
using namespace System;
using namespace System::IO;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Microsoft::Win32;
using namespace System::Runtime::InteropServices;

void Form1::StaticInitialization()
{
    prefs = gcnew CFPrefs();

    busyList = gcnew cli::array<Bitmap^>(9);
    exampleSet = gcnew System::Collections::SortedList();
    widgetHTML = String::Empty;

    Stream^ resStream = Reflection::Assembly::GetExecutingAssembly()->GetManifestResourceStream("ContextFreeNet.CFresources.resources");
    Resources::ResourceReader^ CFres = gcnew Resources::ResourceReader(resStream);
    IDictionaryEnumerator^ resItems = CFres->GetEnumerator();
    System::Text::Encoding^ encoding = System::Text::Encoding::UTF8;
    while (resItems->MoveNext()) {
        String^ resName = (String^)(resItems->Key);
        Type^ resType = resItems->Value->GetType();

        if (resName->StartsWith("busy_f0") && resType == System::Drawing::Icon::typeid) {
            System::Drawing::Icon^ busyIcon = (System::Drawing::Icon^)(resItems->Value);
            int index = Int32::Parse(resName->Substring(7)) - 1;
            busyList[index] = busyIcon->ToBitmap();
            continue;
        }

        if (resName == "dropper") {
            MemoryStream^ ms = gcnew MemoryStream((array<Byte>^)(resItems->Value));
            dropperCursor = gcnew System::Windows::Forms::Cursor(ms);
            continue;
        }

        if (resType == array<Byte>::typeid) {
            array<Byte>^ cfdgBytes = (array<Byte>^)(resItems->Value);
            String^ cfdgText = encoding->GetString(cfdgBytes);
            String^ cfdgName = resName + ".cfdg";
            array<Byte>^ encodedName = encoding->GetBytes(cfdgName);

            pin_ptr<Byte> pinnedCfdg = &cfdgBytes[0];
            pin_ptr<Byte> pinnedName = &encodedName[0];

            WinSystem::AddExample(reinterpret_cast<const char*>(pinnedName), 
                reinterpret_cast<const char*>(pinnedCfdg));

            exampleSet->Add(cfdgName, cfdgText);
        }

        if (resType == String::typeid) {
            widgetHTML = (String^)(resItems->Value);
        }
    }
    CFres->Close();

    exampleSet->TrimToSize();

    openFiles = gcnew System::Collections::Generic::Dictionary<String^, Form^>();
}

void Form1::MoreInitialization()
{
    findForm = gcnew FindReplaceForm();
    mruManager = gcnew OzoneUtil::MRUManager();
    mruManager->Initialize(this, gcnew System::EventHandler(this, &Form1::MRU_Click), 
        this->menuFmruSeparator, "Software\\OzoneSoft\\ContextFree");
    mruManager->autoDirectory = true;

    openFileDialog1->InitialDirectory = mruManager->currentDirectory;
    saveFileDialog1->InitialDirectory = mruManager->currentDirectory;
    saveDirectory = mruManager->currentDirectory;

    EventHandler^ exampleHandler = gcnew EventHandler(this, &Form1::Example_Click);
    IDictionaryEnumerator^ exampleEnum = exampleSet->GetEnumerator();
    while (exampleEnum->MoveNext()) {
        String^ name = Path::GetFileNameWithoutExtension((String^)exampleEnum->Key);
        System::Windows::Forms::ToolStripMenuItem^ example = 
            gcnew System::Windows::Forms::ToolStripMenuItem(name);
        example->Name = "menuE" + name;
        example->Click += exampleHandler;
        menuExamples->DropDownItems->Add(example);
        if (name == "welcome") menuWelcome = example;
    }

    if (SystemColors::MenuBar.GetBrightness() - SystemColors::GradientActiveCaption.GetBrightness() > 0.2) {
        this->menuStrip1->BackColor = System::Drawing::SystemColors::MenuBar;
        overrideMenuColor = false;
    } else {
        overrideMenuColor = true;
    }

    Load += gcnew EventHandler(this, &Form1::Form_Loaded);

    idleHandler = gcnew EventHandler(this, &Form1::appIsIdle);
    Application::Idle += idleHandler;
    Application::ApplicationExit += gcnew EventHandler(this, &Form1::appIsExiting);
    
    // Setup click events for the Help menu
    EventHandler^ urlHandler = gcnew System::EventHandler(this, &Form1::urlMenuItem_Click);
    contextFreeSiteToolStripMenuItem->Click += urlHandler;
    galleryToolStripMenuItem->Click += urlHandler;
    forumsToolStripMenuItem->Click += urlHandler;
    sendFeedbackToolStripMenuItem->Click += urlHandler;
    writingCFDGFilesToolStripMenuItem->Click += urlHandler;

    messagePane = gcnew MessageCtrl();
    colorCalc = gcnew ColorCalculator();

    FormClosing += gcnew FormClosingEventHandler(this, &Form1::FormIsClosing);

    ClientSize = System::Drawing::Size(prefs->FormWidth, prefs->FormHeight);

    bool updateKeys = false;
    try { 
        RegistryKey^ key;
        key = Registry::CurrentUser->OpenSubKey("Software\\Classes\\.cfdg");
        RegistryKey^ key2 = key->OpenSubKey("ShellNew");
        String^ newCmd = safe_cast<String^>(key2->GetValue("Command"));
        updateKeys = newCmd->IndexOf(Application::ExecutablePath) == -1;
        key2->Close();
        key->Close();
        key = Registry::CurrentUser->OpenSubKey("Software\\Classes\\ContextFree.Document");
        key->Close();
    } catch (Exception^) {
        updateKeys = true;
    }

    if (!updateKeys) return;
    try {
        RegistryKey^ classKey = Registry::CurrentUser->CreateSubKey("Software\\Classes\\.cfdg");
        classKey->SetValue(String::Empty, "ContextFree.Document");
        RegistryKey^ newKey = classKey->CreateSubKey("ShellNew");
        newKey->SetValue("Command", String::Format("\"{0}\" /new \"%1\"", 
            Application::ExecutablePath));
        newKey->Close();
        classKey->Close();

        String^ appPath = Application::ExecutablePath;

        classKey = Registry::CurrentUser->CreateSubKey("Software\\Classes\\ContextFree.Document");
        classKey->SetValue(String::Empty, "Context Free file");
        newKey = classKey->CreateSubKey("DefaultIcon");
        newKey->SetValue(String::Empty, String::Format("\"{0}\",1", appPath));
        newKey->Close();
        newKey = classKey->CreateSubKey("shell");
        RegistryKey^ newKey2 = newKey->CreateSubKey("open");
        RegistryKey^ newKey3 = newKey2->CreateSubKey("command");
        newKey3->SetValue(String::Empty, String::Format("\"{0}\" \"%1\"",  appPath));
        newKey3->Close();
        newKey2->Close();
        newKey->Close();
        classKey->Close();
    } catch (Exception^) {}
}

System::Void Form1::menuFNew_Click(System::Object^  sender, System::EventArgs^  e) 
{
    OpenDoc(String::Empty);
}

System::Void Form1::menuFExit_Click(System::Object^  sender, System::EventArgs^  e) 
{
    this->Close();
}

System::Void Form1::FindReplace_Click(System::Object^  sender, System::EventArgs^  e)
{
    if (findForm->DockState != WeifenLuo::WinFormsUI::Docking::DockState::DockBottom) {
        dockPanel->DockBottomPortion = 85;
        findForm->Show(dockPanel, WeifenLuo::WinFormsUI::Docking::DockState::DockBottom);
    } else {
        if (findForm->findButton->Enabled)
            findForm->findButton->PerformClick();
        else
            System::Media::SystemSounds::Beep->Play();
    }
}

System::Void Form1::menuFOpen_Click(System::Object^  sender, System::EventArgs^  ev)
{
    openFileDialog1->Filter = "CFDG Files|*.cfdg";
    openFileDialog1->Title = "Select a CFDG File";
    openFileDialog1->CheckFileExists = true;

    if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK) {
        mruManager->Add(openFileDialog1->FileName);
        if (fileAlreadyOpen(openFileDialog1->FileName))
            return;

        OpenDoc(openFileDialog1->FileName);
    }
}

System::Void Form1::MRU_Click(System::Object^ sender, System::EventArgs^ e)
{
    String^ name = mruManager->OnMRUClicked(sender, e);

    if (name->Length > 0) {
        if (fileAlreadyOpen(name)) 
            return;

        OpenDoc(name);
    }
}

System::Void Form1::Example_Click(System::Object^  sender, System::EventArgs^  e)
{
    System::Windows::Forms::ToolStripMenuItem^ example = 
        (System::Windows::Forms::ToolStripMenuItem^)sender;

    OpenDoc(example->Text + ".cfdg");
}

void Form1::OpenDoc(String^ name)
{
    Document^ newMDIchild = gcnew Document();

    if (name->Length == 0) {
        newMDIchild->TabText += ".cfdg";
        newMDIchild->Name = name;
        newMDIchild->isNamed = false;
        newMDIchild->reloadWhenReady = false;
    } else {
        newMDIchild->TabText = Path::GetFileName(name);
        newMDIchild->Name = name;
        newMDIchild->isNamed = Path::IsPathRooted(name);
        newMDIchild->reloadWhenReady = true;
        if (newMDIchild->isNamed ? !File::Exists(name) : 
                         (exampleSet->IndexOfKey(name) == -1))
        {
            mruManager->Remove(name);
            MessageBox::Show("The file may have been moved or deleted.", "File not found.",
                MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
            return;
        }
    }

    newMDIchild->Text = newMDIchild->TabText;
    newMDIchild->MdiParent = this;
    newMDIchild->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::File_Closed);
    newMDIchild->Show(dockPanel);

    if (newMDIchild->isNamed && File::Exists(name)) {
        mruManager->currentDirectory = Path::GetDirectoryName(name);
        openFiles->Add(name, newMDIchild);
    }
}

System::Void Form1::Form_Loaded(System::Object^  sender, System::EventArgs^  e)
{
    messagePane->Show(dockPanel, WeifenLuo::WinFormsUI::Docking::DockState::DockRightAutoHide);
    colorCalc->Show(dockPanel, WeifenLuo::WinFormsUI::Docking::DockState::DockRightAutoHide);
    dockPanel->ActiveAutoHideContent = nullptr;

    // Change the color of the autohide strip to match the color of the menu bar
    if (overrideMenuColor) {
        dockPanel->Skin->AutoHideStripSkin->DockStripGradient->StartColor = SystemColors::GradientActiveCaption;
        dockPanel->Skin->AutoHideStripSkin->DockStripGradient->EndColor = SystemColors::GradientActiveCaption;
    } else {
        dockPanel->Skin->AutoHideStripSkin->DockStripGradient->StartColor = SystemColors::MenuBar;
        dockPanel->Skin->AutoHideStripSkin->DockStripGradient->EndColor = SystemColors::MenuBar;
    }

    if (StartArgs != nullptr && StartArgs->Length > 1) {
        processArgs(StartArgs);
        return;
    }

    switch (prefs->StartupDocument) {
        case CFPrefs::OpenAction::Welcome:
            if (menuWelcome != nullptr) Example_Click(menuWelcome, nullptr);
            break;
        case CFPrefs::OpenAction::New:
            menuFNew_Click(nullptr, nullptr);
            break;
    }

    WinSystem* sys = new WinSystem(nullptr);
    std::vector<std::string> temps = sys->findTempFiles();
    delete sys;
    if (!temps.empty()) {
        cli::array<String^>^ names = gcnew  cli::array<String^>(temps.size());
        int i = 0;
        for (std::string& temp: temps) {
            String^ name = gcnew String(temp.c_str(), 0, temp.length(), System::Text::Encoding::UTF8);
            names[i++] = name;
        }
        ::DialogResult dlgr = MessageBox::Show(this, "Should they be deleted?", 
            "Old temporary files found", 
            MessageBoxButtons::YesNo, MessageBoxIcon::Question, 
            MessageBoxDefaultButton::Button1);
        if (dlgr == ::DialogResult::Yes) {
            for each (String^ file in names) {
                try {
                    File::Delete(file);
                } catch (Exception^) { } 
            }
        }
    }
}

Void Form1::processArgs(array<System::String^>^ args)
{
    if (this->InvokeRequired) 
        return;

    if (args == nullptr || args->Length == 1) return;

    if (args->Length == 2) {
        OpenDoc(args[1]);
    } else if (args[1] == "/new" && args->Length == 3) {
        String^ name = Path::GetDirectoryName(args[2]) + "\\Document.cfdg";
        OpenDoc(name);
    }
    Activate();
    BringToFront();
}

System::Void Form1::menuFPrefs_Click(System::Object^  sender, System::EventArgs^  e)
{
    if (prefsDialog == nullptr) {
        prefsDialog = gcnew PreferenceDialog(prefs);
        prefsDialog->fontChange->Click += gcnew System::EventHandler(this, &Form1::Font_Click);
        updateFontDisplay();
    }

    prefsDialog->ShowDialog(this);
}

void Form1::updateFontDisplay()
{
    String^ display = nullptr;
    float size = TextFont->SizeInPoints;

    if (fabs(size - floor(size + 0.5)) >= 0.05) {
        display = String::Format("{0} {1:F2}", TextFont->Name, size);
    } else {
        display = String::Format("{0} {1:D}", TextFont->Name, (int)size);
    }

    prefsDialog->fontDisplay->Text = display;
    prefsDialog->fontDisplay->Font = TextFont;
}

void Form1::addDocumentFile(System::String^ filename, System::Windows::Forms::Form^ doc)
{
    openFiles->Remove(filename);
    openFiles->Add(filename, doc);
}

void Form1::changeDocumentFile(System::String^ oldname, System::String^ newname, System::Windows::Forms::Form^ doc)
{
    openFiles->Remove(oldname);
    openFiles->Remove(newname);
    openFiles->Add(newname, doc);
}

System::Void Form1::File_Closed(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
    Document^ doc = dynamic_cast<Document^>(sender);
    System::Windows::Forms::Form^ dictDoc;
    if (doc != nullptr) {
        if (openFiles->TryGetValue(doc->Name, dictDoc)) {
            if (Object::ReferenceEquals(doc, dictDoc)) {
                openFiles->Remove(doc->Name);
            }
        }
    }
}

bool Form1::fileAlreadyOpen(String^ filename)
{
    Form^ doc;
    bool ret = openFiles->TryGetValue(filename, doc);
    if (ret && doc != nullptr)
        doc->BringToFront();
    return ret;
}

void Form1::FormIsClosing(Object^ sender, FormClosingEventArgs^ e)
{
    prefs->FormWidth = ClientSize.Width;
    prefs->FormHeight = ClientSize.Height;

    if (e->Cancel) {
        bool userAction = false;
        for each (Form^ kid in MdiChildren) {
            Document^ doc = dynamic_cast<Document^>(kid);
            if (doc != nullptr)
                userAction = userAction || doc->canceledByUser;
        }
        if (userAction)
            return;
        for each (Form^ kid in MdiChildren) {
            Document^ doc = dynamic_cast<Document^>(kid);
            if (doc != nullptr)
                doc->postAction = Document::PostRenderAction::Exit;
        }
    }
}


void Form1::appIsIdle(System::Object^  sender, System::EventArgs^  e)
{
    for each (Form^ kid in MdiChildren) {
        Document^ doc = dynamic_cast<Document^>(kid); 
        if (doc == nullptr) continue;

        switch (doc->idleAction) {
            case IdleAction::LoadAndRender:
                doc->idleAction = IdleAction::Render;
                doc->reload(false);
                return;
            case IdleAction::Load:
                doc->idleAction = IdleAction::Nothing;
                doc->reload(false);
                return;
            case IdleAction::Clear:
                doc->idleAction = IdleAction::Nothing;
                doc->reload(true);
                return;
            case IdleAction::Render:
                doc->idleAction = IdleAction::Nothing;
                doc->menuRRender->PerformClick();
                return;
        }
    }
}

void Form1::appIsExiting(System::Object^  sender, System::EventArgs^  e)
{
    Renderer::AbortEverything = true;
    if (idleHandler != nullptr)
        Application::Idle -= idleHandler;
}

void Form1::RunDeleteThread(Object^ data)
{
    // Force application to wait for thread to terminate. This prevents
    // temp files from clogging the disk. Renderer::AbortEverything
    // will cause the rest of deletion to bypass
    Threading::Thread::CurrentThread->IsBackground = false;

    IntPtr^ rp = safe_cast<IntPtr^>(data);
    Renderer* r = (Renderer*)(rp->ToPointer());
    delete r;
}

void Form1::DeleteRenderer(Renderer* r)
{
    if (r) {
        IntPtr^ rp = gcnew IntPtr((void*)r);
        Threading::ThreadPool::QueueUserWorkItem(gcnew Threading::WaitCallback(Form1::RunDeleteThread), rp);
    }
}

System::Void Form1::urlMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
    String^ url = (String^)(((ToolStripItem^)sender)->Tag);
    System::Diagnostics::Process::Start(url);
}

System::Void Form1::aboutContextFreeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
    AboutBox^ about = gcnew AboutBox();
    about->ShowDialog();
}

System::Void Form1::menuRColor_Click(System::Object^  sender, System::EventArgs^  e)
{
    if (colorCalc == nullptr) { // || colorCalc->DockState == WeifenLuo::WinFormsUI::Docking::DockState::Unknown) {
        colorCalc = gcnew ColorCalculator();
    }
    colorCalc->Show(dockPanel, 
        WeifenLuo::WinFormsUI::Docking::DockState::DockRightAutoHide);
}

System::Void Form1::menuWMsgConsole_Click(System::Object^  sender, System::EventArgs^  e) 
{
    messagePane->Show();
    messagePane->Activate();
}

void Form1::AddMessage(System::String^ sender, System::String^ msg) 
{
    messagePane->AddMessage(sender, msg);
}

System::Void Form1::Font_Click(System::Object^  sender, System::EventArgs^  e)
{
    FontDialog fd;
    fd.AllowVerticalFonts = false;
    fd.FontMustExist = true;
    fd.ShowApply = false;
    fd.ShowColor = false;
    fd.ShowEffects = false;
    fd.ShowHelp = false;
    fd.Font = TextFont;
    if (fd.ShowDialog() == System::Windows::Forms::DialogResult::OK) {
        TextFont = fd.Font;
        updateFontDisplay();
    }
}

void Form1::WndProc(Message% m)
{
    static const Int32 WM_NCACTIVATE = 0x86;
    // Listen for operating system messages.
    if (m.Msg == WM_NCACTIVATE && overrideMenuColor) {
        if (m.WParam.ToInt32()) {
            dockPanel->Skin->AutoHideStripSkin->DockStripGradient->StartColor = SystemColors::GradientActiveCaption;
            dockPanel->Skin->AutoHideStripSkin->DockStripGradient->EndColor = SystemColors::GradientActiveCaption;
            menuStrip1->BackColor = SystemColors::GradientActiveCaption;
        } else {
            dockPanel->Skin->AutoHideStripSkin->DockStripGradient->StartColor = SystemColors::GradientInactiveCaption;
            dockPanel->Skin->AutoHideStripSkin->DockStripGradient->EndColor = SystemColors::GradientInactiveCaption;
            menuStrip1->BackColor = SystemColors::GradientInactiveCaption;
        }
        dockPanel->AutoHideStripControl->Invalidate();
    }
    Form::WndProc(m);
}