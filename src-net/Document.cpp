// Document.cpp
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

#include "StdAfx.h"
#include "Document.h"
#include "Form1.h"
#include "RenderSizeDialog.h"
#include "AnimateDialog.h"
#include "variation.h"
#include "WinCanvas.h"
#include "WinSystem.h"
#include "Rand64.h"
#include "tiledCanvas.h"
#include "resource.h"
#include "SaveImage.h"
#include "SVGCanvas.h"
#include "ffCanvas.h"
#include "GalleryUploader.h"
#include "upload.h"
#include "tempfile.h"
#include "TempFileDeleter.h"
#include "CFscintilla.h"

using namespace ContextFreeNet;
using namespace System;
using namespace System::Data;
using namespace System::IO;
using namespace System::Drawing;
using namespace System::ComponentModel;
using namespace Microsoft::Win32;
using namespace System::Runtime::InteropServices;
using namespace System::Collections;
using namespace System::Windows::Forms;

[DllImport("user32", CharSet = CharSet::Auto, SetLastError = false)]
extern "C" int SendMessage(int hWnd, unsigned int Msg, int wParam, int* lParam);

void Document::InitializeStuff()
{
    lastCaretPosition = -1;

    // catch form closing to handle worker thread and saving cfdg file if it 
    // is modified
    FormClosing += gcnew FormClosingEventHandler(this, &Document::FormIsClosing);

    // Some initialization needs to be deferred until all the handles are made
    moreInitHandler = gcnew EventHandler(this, &Document::moreInitialization);
    this->Load += moreInitHandler;

    // get resize events so that the status and message text fields can stay the
    // right size
    rightSeparator = toolStripVariationSeparator;
    toolStrip1->SizeChanged += gcnew EventHandler(this, &Document::stripSizeChanged);

    // get renderbox resize events so that its backing store can be remad
    mResizeDelay = 0;
    resizeTimer = gcnew System::Windows::Forms::Timer();
    resizeTimer->Interval = 100;
    resizeTimer->Tick += gcnew EventHandler(this, &Document::resizeTick);
    renderBox->Layout += gcnew LayoutEventHandler(this, &Document::renderSizeChanging);

    // enable/disable the cut/copy/past/etc menu commands
    menuEdit->DropDownOpened += gcnew EventHandler(this, &Document::menuEdit_Popup);

    // initialize the variation to a random value
    currentVariation = Variation::random(3);
    maxVariation = Variation::recommendedMax(6);
    minVariation = Variation::recommendedMin();

    // Setup splitters
    SplitterEventHandler^ splitterHandler = gcnew SplitterEventHandler(this, &Document::splitterMoved);
    documentSplitter->SplitterMoved += splitterHandler;
    editorSplitter->SplitterMoved += splitterHandler;

    // setup the render parameters and the render thread
    renderParams = new RenderParameters();
    renderParams->initFromPrefs();
    renderParams->frame = 1;
    renderParams->animateFrameCount = renderParams->length * renderParams->frameRate;
    renderThread = gcnew BackgroundWorker();
    renderThread->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler(this, &Document::RenderCompleted);
    renderThread->DoWork += gcnew DoWorkEventHandler(this, &Document::RunRenderThread);

    // setup the timer for status update events
    statusTimer = gcnew System::Windows::Forms::Timer();
    statusTimer->Interval = 100;
    statusTimer->Tick += gcnew EventHandler(this, &Document::statusTick);

    deferredHtml = gcnew System::Text::StringBuilder();
    messageWindowUnready = false;

    mOutputMultiplier = gcnew array<double>(2);
    mOutputMultiplier[0] = 1.0;
    mOutputMultiplier[1] = 1.0;

	mRenderButtonAction = RenderButtonAction::Render;

    menuRAnimate->Enabled = ffCanvas::Available();
    if (!menuRAnimate->Enabled)
        menuRAnimate->ToolTipText = "Install FFmpeg subsystem to enable";

    mMoviePlayer = nullptr;
}

void Document::DestroyStuff()
{
    delete mCanvas;
    Form1::DeleteRenderer(mRenderer); mRenderer = nullptr; mEngine->reset();
    if (mSystem) mSystem->orphan();
    delete mSVGCanvas;
    delete mAnimationCanvas;
    delete renderParams;
    if (mMovieFile || mMoviePlayer) {
        TempFileDeleter^ killit = gcnew TempFileDeleter(tempfile_ptr(mMovieFile), mMoviePlayer);
    }
    mMoviePlayer = nullptr;
    mMovieFile = nullptr;
}

System::Void Document::moreInitialization(System::Object^ sender, System::EventArgs^ e)
{
    // keep track of when the cfdg file is modified
    EventHandler<EventArgs^>^ changed = gcnew EventHandler<EventArgs^>(this, &Document::modifiedCFDG);
    cfdgText->SavePointLeft += changed;
    cfdgText->SavePointReached += changed;

    cfdgText->StyleNeeded += gcnew EventHandler<ScintillaNET::StyleNeededEventArgs^>(this, &Document::Style_Cfdg);

    cfdgText->InsertCheck += gcnew EventHandler<ScintillaNET::InsertCheckEventArgs^>(this, &Document::InsertionCheck);
    cfdgText->CharAdded += gcnew EventHandler<ScintillaNET::CharAddedEventArgs^>(this, &Document::CharAdded);

    cfdgText->UpdateUI += gcnew EventHandler<ScintillaNET::UpdateUIEventArgs^>(this, &Document::UpdateUI);

    EventHandler<ScintillaNET::ModificationEventArgs^>^ mod = gcnew EventHandler<ScintillaNET::ModificationEventArgs^>(this, &Document::Text_Changed);
    cfdgText->Insert += mod;
    cfdgText->Delete += mod;

    cfdgText->AutoCCharDeleted += gcnew EventHandler<EventArgs^>(this, &Document::AutoCCharDeleted);

    Form1^ appForm = (Form1^)MdiParent;
    appForm->TextFontChanged += gcnew EventHandler(this, &Document::textFontHandler);
    appForm->StyleChanged += gcnew EventHandler(this, &Document::StyleChanged);
    System::Drawing::Font^ f = appForm->TextFont;
    cfdgMessage->Font = f;

    cfdgText->IndentationGuides = ScintillaNET::IndentView::LookBoth;

    cfdgText->Styles[ScintillaNET::Style::Default]->Font = f->Name;
    cfdgText->Styles[ScintillaNET::Style::Default]->SizeF = f->SizeInPoints;
    cfdgText->StyleClearAll();
    cfdgText->SetSelectionBackColor(true, ColorTranslator::FromHtml("#114D9C"));
    cfdgText->SetSelectionForeColor(true, ColorTranslator::FromHtml("#FFFFFF"));

    this->StyleChanged(nullptr, nullptr);       // grab tab width and styles from prefs

    cfdgText->Styles[ScintillaNET::Style::BraceLight]->ForeColor = ColorTranslator::FromHtml("#8a2be2");
    cfdgText->Styles[ScintillaNET::Style::BraceLight]->BackColor = ColorTranslator::FromHtml("#e6e6fa");
    cfdgText->Styles[ScintillaNET::Style::BraceBad]->ForeColor = ColorTranslator::FromHtml("#ff0000");
    cfdgText->Styles[ScintillaNET::Style::BraceBad]->Bold = true;

    cfdgText->Margins[0]->Type = ScintillaNET::MarginType::Number;
    auto w = cfdgText->CreateGraphics()->MeasureString("8888", f);
    cfdgText->Margins[0]->Width = static_cast<int>(w.Width + 0.9);

    cfdgText->Margins[1]->Width = 0;

    cfdgText->TabDrawMode = ScintillaNET::TabDrawMode::LongArrow;
    cfdgText->UseTabs = false;
    cfdgText->IndentWidth = 0;
    cfdgText->DirectMessage(2260, IntPtr(1), IntPtr(0));    // SCI_SETTABINDENTS = 2260
    cfdgText->DirectMessage(2262, IntPtr(1), IntPtr(0));    // SCI_SETBACKSPACEUNINDENTS = 2262

    cfdgText->AutoCIgnoreCase = true;
    cfdgText->AutoCStops("[]{}<>,1234567890()/*+-|=!&^ \t.\r\n");
    cfdgText->WordChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:";

    cfdgText->Lexer = ScintillaNET::Lexer::Container;

    // Render menu shortcuts
    cfdgText->ClearCmdKey(Keys::Control | Keys::R);
    cfdgText->ClearCmdKey(Keys::Control | Keys::Shift | Keys::R);
    cfdgText->ClearCmdKey(Keys::Control | Keys::Alt | Keys::R);
    cfdgText->ClearCmdKey(Keys::Control | Keys::Alt | Keys::A);
    cfdgText->ClearCmdKey(Keys::Control | Keys::Alt | Keys::F);
    cfdgText->ClearCmdKey(Keys::Control | Keys::O);
    cfdgText->ClearCmdKey(Keys::Control | Keys::U);
    // indent/unindent shortcuts
    cfdgText->ClearCmdKey(Keys::Control | Keys::OemOpenBrackets);
    cfdgText->ClearCmdKey(Keys::Control | Keys::OemCloseBrackets);

    cfdgText->Invalidate();

    // enable/disable File->Revert menu command
    appForm->menuFile->DropDownOpened +=
        gcnew EventHandler(this, &Document::menuFile_Popup);

    // load the bitmaps used in the render button
    ImageList^ iList = toolStrip1->ImageList;
    if (iList == nullptr)
        iList = gcnew ImageList();
    imageListBase = iList->Images->Count;
    iList->Images->AddRange(Form1::busyList);
    toolStrip1->ImageList = iList;

    // get key events in the variation edit field to make sure that only valid
    // variations are entered
    variationEdit = gcnew TextBox();
    variationEdit->KeyDown += gcnew KeyEventHandler(this, &Document::variationKeyDown);
    variationEdit->KeyPress += gcnew KeyPressEventHandler(this, &Document::variationKeyPress);
    processVariationChange = gcnew EventHandler(this, &Document::variationChanged);

    // Replace the placeholder ToolStripTextBox with an encapsulated TextBox.
    // This is done to fix a .Net bug with the ToolStripTextBox::Textchanged
    // event not firing reliably.
    toolStrip1->SuspendLayout();
    toolStrip1->Items->Insert(toolStrip1->Items->IndexOf(toolStripVariation), 
                              gcnew ToolStripControlHost(variationEdit));
    toolStrip1->Items->Remove(toolStripVariation); 
    variationEdit->MaxLength = 6;
    variationEdit->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
    variationEdit->Name = L"variationEdit";
    variationEdit->MinimumSize = System::Drawing::Size(80, 25);
    variationEdit->MaximumSize = System::Drawing::Size(80, 25);
    variationEdit->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
    variationEdit->TextChanged += processVariationChange;
    --currentVariation;
    NextVar_Click(nullptr, nullptr);

    // Same bug fix for toolStripFrameTextBox
    frameEdit = gcnew TextBox();
    toolStrip1->Items->Insert(toolStrip1->Items->IndexOf(toolStripFrameTextBox),
                              gcnew ToolStripControlHost(frameEdit));
    toolStrip1->Items->Remove(toolStripFrameTextBox);
    frameEdit->MaxLength = 4;
    frameEdit->Text = System::Convert::ToString(renderParams->frame);
    frameEdit->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
    frameEdit->MinimumSize = System::Drawing::Size(50, 25);
    frameEdit->MaximumSize = System::Drawing::Size(50, 25);
    frameEdit->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
    frameEdit->KeyPress += gcnew KeyPressEventHandler(this, &Document::Frame_KeyPress);
    frameEdit->TextChanged += gcnew EventHandler(this, &Document::Frame_Changed);
    frameEdit->Visible = false;

    // Same bug fix for toolStripWidthBox
    widthEdit = gcnew TextBox();
    toolStrip1->Items->Insert(toolStrip1->Items->IndexOf(toolStripWidthBox),
        gcnew ToolStripControlHost(widthEdit));
    toolStrip1->Items->Remove(toolStripWidthBox);
    widthEdit->MaxLength = 5;
    widthEdit->Text = System::Convert::ToString(renderParams->width);
    widthEdit->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
    widthEdit->MinimumSize = System::Drawing::Size(50, 25);
    widthEdit->MaximumSize = System::Drawing::Size(50, 25);
    widthEdit->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
    widthEdit->KeyPress += gcnew KeyPressEventHandler(this, &Document::Frame_KeyPress);
    widthEdit->TextChanged += gcnew EventHandler(this, &Document::Size_Changed);
    widthEdit->Visible = false;

    // Same bug fix for toolStripHeightBox
    heightEdit = gcnew TextBox();
    toolStrip1->Items->Insert(toolStrip1->Items->IndexOf(toolStripHeightBox),
        gcnew ToolStripControlHost(heightEdit));
    toolStrip1->Items->Remove(toolStripHeightBox);
    heightEdit->MaxLength = 5;
    heightEdit->Text = System::Convert::ToString(renderParams->height);
    heightEdit->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
    heightEdit->MinimumSize = System::Drawing::Size(50, 25);
    heightEdit->MaximumSize = System::Drawing::Size(50, 25);
    heightEdit->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
    heightEdit->KeyPress += gcnew KeyPressEventHandler(this, &Document::Frame_KeyPress);
    heightEdit->TextChanged += gcnew EventHandler(this, &Document::Size_Changed);
    heightEdit->Visible = false;
    toolStrip1->ResumeLayout();

    // Prepare the error message pane
    cfdgMessage->Navigating += gcnew WebBrowserNavigatingEventHandler(this, &Document::errorNavigation);

    // For some reason this is too soon to initialize the cfdg edit box or 
    // trigger a render if the Render-On-Open setting is true. So instead
    // we will ask the application idle handler to initialize the cfdg edit
    // box and render its contents in a very lazy fashion.
    if (reloadWhenReady) {
        idleAction = Form1::prefs->RenderOnOpen ? 
            Form1::IdleAction::LoadAndRender : Form1::IdleAction::Load;
    } else {
        idleAction = Form1::IdleAction::Clear;
    }

    menuEFind->Click += gcnew EventHandler((Form1^)MdiParent, &Form1::FindReplace_Click);
    menuEFindPrev->Click += gcnew EventHandler((Form1^)MdiParent, &Form1::FindReplace_Click);

    cfdgMessage->DocumentCompleted += 
        gcnew WebBrowserDocumentCompletedEventHandler(this, &Document::messageWindowReady);
    setMessageText(nullptr);
}

System::Void Document::menuFSave_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (isNamed) {
        try {
            StreamWriter sw(Name);
            sw.Write(cfdgText->Text);
            cfdgText->SetSavePoint();
        } catch (Exception^) {
            setMessageText("The file could not be written." );
        }
    } else {
        menuFSaveAs_Click(sender, e);
    }
}

System::Void Document::menuFSaveAs_Click(System::Object^ sender, System::EventArgs^ e)
{
    ((Form1^)MdiParent)->saveFileDialog1->Filter = "CFDG Files|*.cfdg";
    ((Form1^)MdiParent)->saveFileDialog1->Title = "Select a CFDG File";
    ((Form1^)MdiParent)->saveFileDialog1->FileName = Text;

    if (((Form1^)MdiParent)->saveFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK) {
        String^ oldName = Name;
        Name = ((Form1^)MdiParent)->saveFileDialog1->FileName;
        TabText = Path::GetFileName(((Form1^)MdiParent)->saveFileDialog1->FileName);
        Text = TabText;
        isNamed = true;
        ((Form1^)MdiParent)->mruManager->Add(Name);
        Form1::changeDocumentFile(oldName, Name, this);
        menuFSave_Click(sender, e);
    }
}

System::Void Document::FormIsClosing(Object^ sender, FormClosingEventArgs^ e)
{
    canceledByUser = false;

    // we can't close the window while the worker thread is running, so stop it
    if (renderThread->IsBusy) {
        // remember to close the window when the thread ends
        postAction = PostRenderAction::Close;
        if (mRenderer) mRenderer->requestStop = true;
        e->Cancel = true;
        return;
    }

    if (mMovieFile || mMoviePlayer) {
        TempFileDeleter^ killit = gcnew TempFileDeleter(tempfile_ptr(mMovieFile), mMoviePlayer);
    }
    mMoviePlayer = nullptr;
    mMovieFile = nullptr;

    // If the thread is stopped and the cfdg file is up-to-date then close
    if (!cfdgText->Modified) return;

    // See if the user wants to close (lose changes), save changes and close,
    // or cancel the close.
    String^ msg = "Save changes in " + Text + "?";
    Windows::Forms::DialogResult r = Windows::Forms::MessageBox::Show(this, 
        msg, "Context Free", Windows::Forms::MessageBoxButtons::YesNoCancel);

    if (r == Windows::Forms::DialogResult::Cancel) {
        e->Cancel = true;
        // if the close was from an application exit and the user cancels it
        // then set this flag to cancel the exit
        canceledByUser = true;
        return;
    }

    if (r == Windows::Forms::DialogResult::Yes) {
        // save the file and then close
        menuFSave_Click(this, e);
    }
}

System::Void Document::menuFClose_Click(System::Object^ sender, System::EventArgs^ e)
{
    this->Close();
}

System::Void Document::menuFRevert_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (!isNamed || !cfdgText->Modified) return;

    Windows::Forms::DialogResult r = Windows::Forms::MessageBox::Show(this, 
        "Do you wish to revert and lose your changes?", "Context Free", 
        Windows::Forms::MessageBoxButtons::YesNo);

    if (r == Windows::Forms::DialogResult::Yes) {
        reload(false);
    }
}

// Load or reload the cfdg edit box from the documents named source, which
// is either a file path or the name of an example.
void Document::reload(bool justClear)
{
    if (justClear) {
        cfdgText->Text = String::Empty;
        cfdgText->SetSavePoint();
        return;
    }

    int pos = Form1::exampleSet->IndexOfKey(this->Name);
    if (pos >= 0) {
        cfdgText->Text = (String^)Form1::exampleSet->GetByIndex(pos);
        cfdgText->SetSavePoint();
        return;
    }

    try {
        StreamReader sr(Name);
        cfdgText->Text = sr.ReadToEnd();
        cfdgText->SetSavePoint();
    } catch (Exception^) {
        ((Form1^)MdiParent)->mruManager->Remove(Name);
        cfdgText->Text = String::Empty;
        cfdgText->SetSavePoint();
        setMessageText("The file could not be read." );
    }
}

void Document::setMessageText(String^ txt)
{
    if (txt == nullptr) {
        cfdgMessage->Navigate("about:blank");
        messageWindowUnready = true;
    } else if (txt->Length > 0) {
        String^ htmlFrag = String::Format("  <p>{0}</p>\n", txt);
        if (messageWindowUnready) {
            deferredHtml->Append(htmlFrag);
            return;
        }

        cfdgMessage->Document->Write(htmlFrag);
        cfdgMessage->Document->Body->ScrollIntoView(false);
        ((Form1^)MdiParent)->AddMessage(Text, txt);
    }
}

System::Void Document::messageWindowReady(System::Object^ sender, 
    System::Windows::Forms::WebBrowserDocumentCompletedEventArgs^ e)
{
    System::Drawing::Font^ editFont = ((Form1^)MdiParent)->TextFont;
    String^ html = String::Format("\
<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">\n\
<html>\n\
 <head>\n\
  <title>Context Free Messages</title>\n\
  <style type=\"text/css\">\n\
   p {{padding:0; margin:0; font-family:{0}; font-size:{1:f}pt;}}\n\
   body {{padding:0; margin:0;}}\n\
  </style>\n\
 </head>\n\
 <body>\n{2}\
 </body>\n\
</html>\n", editFont->Name, editFont->SizeInPoints, deferredHtml->ToString());
    cfdgMessage->Document->Write(html);
    deferredHtml->Clear();
    messageWindowUnready = false;
}

void Document::setStatusText(String^ txt, bool sendToPane)
{
    toolStripStatus->Text = txt;
    if (sendToPane)
        ((Form1^)MdiParent)->AddMessage(Text, txt);
}

// Receive the Modify-flag-changed event from the cfdg edit box and merge the updated
// flag into the three local modify flags.
System::Void Document::modifiedCFDG(System::Object^ sender, System::EventArgs^ e)
{
    TabText = cfdgText->Modified ? (Text + "*") : Text;
    if (cfdgText->Modified)
        variationEdit->ForeColor = Color::Blue;
}

System::Void Document::menuRRender_Click(System::Object^ sender, System::EventArgs^ e)
{
    RenderButtonAction oldAction = mRenderButtonAction;
    mRenderButtonAction = RenderButtonAction::Render;
    if (oldAction != mRenderButtonAction)
        updateRenderButton();

	if (renderThread->IsBusy) {
        postAction = PostRenderAction::Render;
        return;
    }

    renderParams->initFromPrefs();
    renderParams->width = renderParams->height = 0;
    renderParams->periodicUpdate = true;
    renderParams->suppressDisplay = false;
    renderParams->action = RenderParameters::RenderActions::Render;
    DoRender();
}

System::Void Document::menuRRenderSize_Click(System::Object^ sender, System::EventArgs^ e)
{
	RenderButtonAction oldAction = mRenderButtonAction;
	mRenderButtonAction = RenderButtonAction::RenderSized;
    if (oldAction != mRenderButtonAction)
        updateRenderButton();

    if (renderThread->IsBusy) {
        postAction = PostRenderAction::RenderSize;
        return;
    }

    renderParams->initFromPrefs();
    if (sender == menuRRenderSize) {
        RenderSizeDialog rs(renderParams);
        if (rs.ShowDialog() == Windows::Forms::DialogResult::OK)
            renderParams->saveToPrefs();
        else
            return;
    }

    renderParams->action = RenderParameters::RenderActions::Render;
    DoRender();
}

System::Void Document::menuRAnimate_Click(System::Object^ sender, System::EventArgs^ e)
{
	RenderButtonAction oldAction = mRenderButtonAction;
	mRenderButtonAction = RenderButtonAction::Animate;
    if (oldAction != mRenderButtonAction)
        updateRenderButton();

	if (renderThread->IsBusy) {
        postAction = PostRenderAction::Animate;
        return;
    }

    renderParams->initFromPrefs();
    renderParams->animateFrame = false;
    if (sender == menuRAnimate) {
        AnimateDialog an(renderParams);
        if (an.ShowDialog() == Windows::Forms::DialogResult::OK)
            renderParams->saveToPrefs();
        else
            return;
    } else {
        renderParams->animateFrameCount = renderParams->length * renderParams->frameRate;
    }

    renderParams->action = RenderParameters::RenderActions::Animate;
    DoRender();
}

System::Void Document::menuRAnimateFrame_Click(System::Object^ sender, System::EventArgs^ e)
{
	RenderButtonAction oldAction = mRenderButtonAction;
	mRenderButtonAction = RenderButtonAction::AnimateFrame;
    if (oldAction != mRenderButtonAction)
        updateRenderButton();

	if (renderThread->IsBusy) {
        postAction = PostRenderAction::AnimateFrame;
        return;
    }

    renderParams->initFromPrefs();
    renderParams->animateFrame = true;
    if (sender == menuRAnimateFrame) {
        AnimateDialog an(renderParams);
        if (an.ShowDialog() != Windows::Forms::DialogResult::OK)
            return;
        renderParams->saveToPrefs();
        frameEdit->Text = System::Convert::ToString(renderParams->frame);
    } else {
        renderParams->animateFrameCount = renderParams->length * renderParams->frameRate;
    }

    renderParams->action = RenderParameters::RenderActions::Animate;
    DoRender();
}

System::Void Document::menuRStop_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (mRenderer && renderThread->IsBusy) {
        mRenderer->requestStop = true;
        updateRenderButton();
    }
}

System::Void Document::menuRSaveOutput_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (mMoviePlayer) {
        // Should close and release temp file before save dialog shows
        mMoviePlayer->CloseMainWindow();
        mMoviePlayer = nullptr;
    }

    if (!mCanvas && !mMovieFile) {
        setMessageText("There is nothing to save.");
        System::Console::Beep();
        return;
    }

    if (renderThread->IsBusy) {
        postAction = PostRenderAction::SaveOutput;
        return;
    }

    if (mMovieFile) {
        if (!mMovieFile->written()) {
            setMessageText("Movie file already saved.");
            System::Console::Beep();
            return;
        }

        SaveFileDialog^ saveMovieDlg = gcnew SaveFileDialog();
        saveMovieDlg->Filter = "MOV files (*.mov)|*.mov|All files (*.*)|*.*";
        if (saveMovieDlg->ShowDialog() == ::DialogResult::OK) {
            String^ oldPath = gcnew String(mMovieFile->name().c_str());
            if (File::Exists(saveMovieDlg->FileName)) {
                try {
                    File::Delete(saveMovieDlg->FileName);
                } catch (Exception^) {
                    setMessageText("Cannot overwrite destination.");
                    System::Console::Beep();
                    return;
                }
            }
            try {
                File::Move(oldPath, saveMovieDlg->FileName);
                mMovieFile->release();
                setMessageText("Movie saved.");
            } catch (Exception^) {
                setMessageText("Movie save failed.");
                System::Console::Beep();
                return;
            }
        }
        return;
    }       // end of Saving movie

    // Saving image
    SaveImage saveImageDlg((*mEngine)->isFrieze(), mTiled ? mOutputMultiplier : nullptr,
        Path::GetFileNameWithoutExtension(Text) + ".png",
        ((Form1^)MdiParent)->saveDirectory);

    if (saveImageDlg.ShowTheDialog(this) == System::Windows::Forms::DialogResult::OK) {
        ((Form1^)MdiParent)->saveDirectory = 
            Path::GetDirectoryName(saveImageDlg.FileDlgFileName);
        switch (saveImageDlg.FileDlgFilterIndex) {
            case 1: // PNG
                saveToPNGorJPEG(saveImageDlg.FileDlgFileName, nullptr, false);
                break;
            case 2: // JPEG
                saveToPNGorJPEG(saveImageDlg.FileDlgFileName, nullptr, true);
                break;
            case 3: // SVG
                saveToSVG(saveImageDlg.FileDlgFileName);
                break;
            default:
                break;
        }
    }
}

bool Document::saveToPNGorJPEG(String^ path, System::IO::Stream^ str, bool JPEG)
{
    bool success = true;

    setMessageText("Saving image...");

    array<Imaging::ImageCodecInfo^>^ codecs = Imaging::ImageCodecInfo::GetImageEncoders();
    Imaging::ImageCodecInfo^ jpegCodec = nullptr;
    for each (Imaging::ImageCodecInfo^ codec in codecs) {
        if (codec->MimeType->Equals("image/jpeg"))
            jpegCodec = codec;
    }

    if (jpegCodec == nullptr) {
        setMessageText("Can't seem to find an image encoder.");
        return false;
    }

    Imaging::EncoderParameters^ iParams = gcnew Imaging::EncoderParameters(1);
    long long qual = (long long)(Form1::prefs->JPEGQuality);
    iParams->Param[0] = gcnew Imaging::EncoderParameter(Imaging::Encoder::Quality, qual);

    try {
        Bitmap^ bm = MakeBitmap(mTiled || Form1::prefs->ImageCrop, mCanvas);
        if (bm == nullptr)
            throw gcnew ArgumentNullException();

        if (mTiled && (mOutputMultiplier[0] != 1.0 || mOutputMultiplier[1] != 1.0)) {
            Imaging::PixelFormat fmt = bm->PixelFormat;
            if (fmt == Imaging::PixelFormat::Format8bppIndexed)
                fmt = Imaging::PixelFormat::Format24bppRgb;

            int w = (int)(bm->Width  * mOutputMultiplier[0] + 0.5);
            int h = (int)(bm->Height * mOutputMultiplier[1] + 0.5);

            Bitmap^ newBM = gcnew Bitmap(w, h, fmt);
            Graphics^ g = Graphics::FromImage(newBM);
            g->Clear(Color::White);
            drawTiled(bm, newBM, g, nullptr, 0, 0);

            delete g;
            delete bm;
            bm = newBM;
        }

        if (path != nullptr) {
            String^ fileName = path;
            if (Form1::prefs->ImageAppendVariation) {
                fileName = Path::GetDirectoryName(path) + "\\" +
                    Path::GetFileNameWithoutExtension(path) +
                    "-" + variationEdit->Text->ToLower() +  
                    Path::GetExtension(path);
            }

            if (JPEG) 
                bm->Save(fileName, jpegCodec, iParams);
            else
                bm->Save(fileName, Imaging::ImageFormat::Png);
        } else if (str != nullptr) {
            if (JPEG)
                bm->Save(str, jpegCodec, iParams);
            else
                bm->Save(str, Imaging::ImageFormat::Png);
        } else {
            setMessageText("Nowhere to save the image.");
            System::Console::Beep();
        }
        delete bm;
        setMessageText("Image save complete.");
    } catch (Exception^) {
        setMessageText("Image save failed.");
        System::Console::Beep();
        success = false;
    }
    delete mTempCanvas;
    mTempCanvas = nullptr;
    return success;
}

void Document::saveToSVG(String^ path)
{
    if (!mRenderer) {
        setMessageText("There is no SVG data to save.");
        System::Console::Beep();
        return;
    }

    setMessageText("Saving SVG file...");

    renderParams->action = RenderParameters::RenderActions::SaveSVG;

    array<Byte>^ pathutf8 = System::Text::Encoding::UTF8->GetBytes(path);
    if (pathutf8->Length == 0) {
        setMessageText("Bad file name");
        System::Console::Beep();
        return;
    }
    pin_ptr<Byte> pathutf8pin = &pathutf8[0];

    mSVGCanvas = new SVGCanvas(reinterpret_cast<const char*>(pathutf8pin), 
        renderParams->width, renderParams->height, Form1::prefs->ImageCrop);

    if (mSVGCanvas->mError) {
        setMessageText("An error occurred while saving the SVG file.");
        System::Console::Beep();
        return;
    }

    postAction = PostRenderAction::DoNothing;
    renderThread->RunWorkerAsync();
    statusTimer->Start();
    updateRenderButton();
}


System::Void Document::menuRUpload_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (!mCanvas) {
        setMessageText("Nothing to upload, try rendering first.");
        return;
    }

    bool compression = mCanvas->colorCount256() ? Upload::CompressPNG8 : Upload::CompressJPEG;

    array<Byte>^ encodedCfdg = System::Text::Encoding::UTF8->GetBytes(cfdgText->Text);
    pin_ptr<Byte> pinnedCfdg = &encodedCfdg[0];

    GalleryUploader toGal(this, Path::GetFileNameWithoutExtension(Text),
        (*mEngine)->isFrieze(), mTiled, compression, currentVariation,
        reinterpret_cast<const char*>(pinnedCfdg), mTiled ? mOutputMultiplier : nullptr);

    toGal.ShowDialog(this);

}

System::Void Document::menuEUndo_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (cfdgText->CanUndo)
        cfdgText->Undo();
}

System::Void Document::menuERedo_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (cfdgText->CanRedo)
        cfdgText->Redo();
}

System::Void Document::menuECut_Click(System::Object^  sender, System::EventArgs^  e)
{
    if (cfdgText->SelectionStart != cfdgText->SelectionEnd)
        cfdgText->Cut();
}

System::Void Document::menuECopy_Click(System::Object^  sender, System::EventArgs^  e)
{
    if (cfdgText->SelectionStart != cfdgText->SelectionEnd)
        cfdgText->Copy();
}

System::Void Document::menuEPaste_Click(System::Object^  sender, System::EventArgs^  e)
{
    if (Clipboard::GetDataObject()->GetDataPresent(DataFormats::Text))
        cfdgText->Paste();
}

System::Void Document::menuEDelete_Click(System::Object^  sender, System::EventArgs^  e)
{
    if (cfdgText->SelectionStart != cfdgText->SelectionEnd)
        cfdgText->ReplaceSelection(nullptr);
}

System::Void Document::toolStripMenuUnicode_Click(System::Object^  sender, System::EventArgs^  e)
{
    ToolStripMenuItem^ i = dynamic_cast<ToolStripMenuItem^>(sender);
    if (i != nullptr)
        cfdgText->ReplaceSelection(i->Text);
}

System::Void Document::textFontHandler(System::Object^ sender, System::EventArgs^ e)
{
    System::Drawing::Font^ f = ((Form1^)MdiParent)->TextFont;
    cfdgText->Styles[ScintillaNET::Style::Default]->Font = f->Name;
    cfdgText->Styles[ScintillaNET::Style::Default]->SizeF = f->SizeInPoints;
    for (int i = CFscintilla::StyleDefault; i <= CFscintilla::StyleNumber; ++i) {
        cfdgText->Styles[i]->Font = f->Name;
        cfdgText->Styles[i]->SizeF = f->SizeInPoints;
    }
    cfdgText->Styles[ScintillaNET::Style::LineNumber]->Font = f->Name;
    cfdgText->Styles[ScintillaNET::Style::LineNumber]->SizeF = f->SizeInPoints;
    auto w = cfdgText->CreateGraphics()->MeasureString("8888", f);
    cfdgText->Margins[0]->Width = static_cast<int>(w.Width + 0.9);
    cfdgMessage->Font = f;
    setMessageText(nullptr);
}

System::Void Document::StyleChanged(System::Object ^ sender, System::EventArgs ^ e)
{
    cfdgText->TabWidth = Form1::prefs->TabWidth;

    cfdgText->Styles[CFscintilla::StyleDefault]->Bold = Form1::prefs->StyleDefaultBold;
    cfdgText->Styles[CFscintilla::StyleComment]->Bold = Form1::prefs->StyleCommentsBold;
    cfdgText->Styles[CFscintilla::StyleSymbol]->Bold = Form1::prefs->StyleSymbolsBold;
    cfdgText->Styles[CFscintilla::StyleIdentifier]->Bold = Form1::prefs->StyleIdentifiersBold;
    cfdgText->Styles[CFscintilla::StyleKeywords]->Bold = Form1::prefs->StyleKeywordsBold;
    cfdgText->Styles[CFscintilla::StyleBuiltins]->Bold = Form1::prefs->StyleBuiltinsBold;
    cfdgText->Styles[CFscintilla::StyleString]->Bold = Form1::prefs->StyleStringsBold;
    cfdgText->Styles[CFscintilla::StyleNumber]->Bold = Form1::prefs->StyleNumbersBold;

    cfdgText->Styles[CFscintilla::StyleDefault]->Italic = Form1::prefs->StyleDefaultItalic;
    cfdgText->Styles[CFscintilla::StyleComment]->Italic = Form1::prefs->StyleCommentsItalic;
    cfdgText->Styles[CFscintilla::StyleSymbol]->Italic = Form1::prefs->StyleSymbolsItalic;
    cfdgText->Styles[CFscintilla::StyleIdentifier]->Italic = Form1::prefs->StyleIdentifiersItalic;
    cfdgText->Styles[CFscintilla::StyleKeywords]->Italic = Form1::prefs->StyleKeywordsItalic;
    cfdgText->Styles[CFscintilla::StyleBuiltins]->Italic = Form1::prefs->StyleBuiltinsItalic;
    cfdgText->Styles[CFscintilla::StyleString]->Italic = Form1::prefs->StyleStringsItalic;
    cfdgText->Styles[CFscintilla::StyleNumber]->Italic = Form1::prefs->StyleNumbersItalic;

    cfdgText->Styles[CFscintilla::StyleDefault]->ForeColor = ColorTranslator::FromHtml(Form1::prefs->StyleDefaultColor);
    cfdgText->Styles[CFscintilla::StyleComment]->ForeColor = ColorTranslator::FromHtml(Form1::prefs->StyleCommentsColor);
    cfdgText->Styles[CFscintilla::StyleSymbol]->ForeColor = ColorTranslator::FromHtml(Form1::prefs->StyleSymbolsColor);
    cfdgText->Styles[CFscintilla::StyleIdentifier]->ForeColor = ColorTranslator::FromHtml(Form1::prefs->StyleIdentifiersColor);
    cfdgText->Styles[CFscintilla::StyleKeywords]->ForeColor = ColorTranslator::FromHtml(Form1::prefs->StyleKeywordsColor);
    cfdgText->Styles[CFscintilla::StyleBuiltins]->ForeColor = ColorTranslator::FromHtml(Form1::prefs->StyleBuiltinsColor);
    cfdgText->Styles[CFscintilla::StyleString]->ForeColor = ColorTranslator::FromHtml(Form1::prefs->StyleStringsColor);
    cfdgText->Styles[CFscintilla::StyleNumber]->ForeColor = ColorTranslator::FromHtml(Form1::prefs->StyleNumbersColor);
}

System::Void Document::errorNavigation(System::Object^ sender, System::Windows::Forms::WebBrowserNavigatingEventArgs^ e)
{
    String^ frag = e->Url->Fragment;
    if (!String::IsNullOrEmpty(frag)) {
        e->Cancel = true;
        try {
            array<Char>^ colon = { ':' };
            array<String^>^ split = frag->Split(colon);
            int b_line = Convert::ToInt32(split[1]) - 1;
            int b_col = Convert::ToInt32(split[2]);
            int e_line = Convert::ToInt32(split[3]) - 1;
            int e_col = Convert::ToInt32(split[4]);
            int start = cfdgText->Lines[b_line]->Position + b_col;
            int end = cfdgText->Lines[e_line]->Position + e_col;
            cfdgText->Focus();
            cfdgText->SelectionStart = start;
            cfdgText->SelectionEnd = end;
            cfdgText->ScrollCaret();
        } catch (...) {
        }
    }
}

System::Void Document::menuFile_Popup(System::Object^  sender, System::EventArgs^  e)
{
    menuFRevert->Enabled = isNamed && cfdgText->Modified;
}

System::Void Document::menuEdit_Popup(System::Object^  sender, System::EventArgs^  e)
{
    menuECopy->Enabled = cfdgText->SelectionStart != cfdgText->SelectionEnd;
    menuECut->Enabled = cfdgText->SelectionStart != cfdgText->SelectionEnd;
    menuEPaste->Enabled = Clipboard::GetDataObject()->GetDataPresent(DataFormats::Text);
    menuEDelete->Enabled = cfdgText->SelectionStart != cfdgText->SelectionEnd;
    menuEUndo->Enabled = cfdgText->CanUndo;
    menuERedo->Enabled = cfdgText->CanRedo;
}

System::Void Document::RenderButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (mRenderer && renderThread->IsBusy) {
        if (mRenderer->requestFinishUp) {
            mRenderer->requestStop = true;
        } else {
            mRenderer->requestFinishUp = true;
            updateRenderButton();
        }
    } else {
		switch (mRenderButtonAction) {
		case RenderButtonAction::Render:
			menuRRender_Click(sender, e);
			break;
        case RenderButtonAction::RenderSized:
            menuRRenderSize_Click(sender, e);
            break;
		case RenderButtonAction::Animate:
			menuRAnimate_Click(sender, e);
			break;
		case RenderButtonAction::AnimateFrame:
			menuRAnimateFrame_Click(sender, e);
			break;
		}
    }
}

System::Void Document::actionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    ToolStripMenuItem^ menu = cli::safe_cast<ToolStripMenuItem^>(sender);
    String^ tag = menu->Tag->ToString();
    int tagnum = Int32::Parse(tag);
    mRenderButtonAction = (RenderButtonAction)tagnum;
    updateRenderButton();
}

System::Void Document::PrevVar_Click(System::Object^ sender, System::EventArgs^ e)
{
    mReuseVariation = true;
    variationEdit->ForeColor = Color::Blue;
    --currentVariation;
    if (currentVariation > maxVariation || currentVariation < minVariation)
        currentVariation = maxVariation;
    std::string vChars = Variation::toString(currentVariation, false);
    variationEdit->Text = gcnew String(vChars.c_str());
}

System::Void Document::NextVar_Click(System::Object^ sender, System::EventArgs^ e)
{
    mReuseVariation = true;
    variationEdit->ForeColor = Color::Blue;
    ++currentVariation;
    if (currentVariation > maxVariation || currentVariation < minVariation)
        currentVariation = minVariation;
    std::string vChars = Variation::toString(currentVariation, false);
    variationEdit->Text = gcnew String(vChars.c_str());
}

System::Void Document::PrevFrame_Click(System::Object^ sender, System::EventArgs^ e)
{
    mReuseVariation = true;
    variationEdit->ForeColor = Color::Blue;
    if (renderParams->frame <= 1)
        return;
    --renderParams->frame;
    frameEdit->Text = System::Convert::ToString(renderParams->frame);
}

System::Void Document::NextFrame_Click(System::Object^ sender, System::EventArgs^ e)
{
    mReuseVariation = true;
    variationEdit->ForeColor = Color::Blue;
    if (renderParams->frame >= renderParams->animateFrameCount)
        return;
    ++renderParams->frame;
    frameEdit->Text = System::Convert::ToString(renderParams->frame);
}

void Document::WndProc( Message% m )
{
    // Listen for operating system messages.
    switch (m.Msg) {
        case WinSystem::WM_USER_MESSAGE_UPDATE: 
            {
                char* msg = (char*)m.WParam.ToPointer();
                String^ msgText = gcnew String(msg, 0, static_cast<int>(strlen(msg)), System::Text::Encoding::UTF8);
                delete[] msg;
                setMessageText(msgText);
                break;
            }
        case WinSystem::WM_USER_STATUS_UPDATE:
            {
                WinSystem::Stats* stat = (WinSystem::Stats*)m.WParam.ToPointer();
                bool show = m.LParam.ToInt32() != 0;
                if (stat) {
                    String^ preText = show ? "rescaling - " : "";
                    if ((stat->toDoCount > 0 && !stat->finalOutput) || !mCanvas) {
                        setStatusText(preText + 
                            String::Format("{0:N0} shapes and {1:N0} expansions to do", 
                            stat->shapeCount, stat->toDoCount), false);
                    } else {
                        String^ endText = mTiled ? ", tiled" : "";
                        setStatusText(preText +
                            String::Format("{0:N0} shapes, {1:N0} x {2:N0} pixels", 
                            stat->shapeCount, mCanvas->mWidth, mCanvas->mHeight)
                            + endText, !stat->inOutput);
                    }

                    if (stat->inOutput || stat->showProgress) {
                        if (mProgressDelay > 2) {
                            int bar = 0;
                            if (stat->outputCount)
                                bar = (int)((100.0 * (double)stat->outputDone) / stat->outputCount);
                            if (bar >= 0 && bar <= 100)
                                toolStripProgressBar->Value = bar;
                        } else {
                            ++mProgressDelay;
                            toolStripProgressBar->Value = 0;
                        }
                    } else {
                        mProgressDelay = 0;
                        toolStripProgressBar->Value = 0;
                    }
                } else {
                    updateRenderBox();
                }
                break;
            }
    }
    WeifenLuo::WinFormsUI::Docking::DockContent::WndProc(m);
}

System::Void Document::stripSizeChanged(System::Object^ sender, System::EventArgs^ e)
{
    System::Drawing::Size stripSize = toolStrip1->Size;
    System::Drawing::Rectangle sepRect = rightSeparator->Bounds;
    System::Drawing::Rectangle messageBox = toolStripStatus->Bounds;

    int w = stripSize.Width - sepRect.Right - 6;
    if (w < 75) w = 75;
    toolStripStatus->Width = w;

    toolStrip1->PerformLayout();
}

System::Void Document::renderSizeChanging(System::Object^ sender, System::Windows::Forms::LayoutEventArgs^ e)
{
    mResizeDelay = 0;
    resizeTimer->Enabled = true;
}

System::Void Document::resizeTick(Object^ sender, EventArgs^ e)
{
    ++mResizeDelay;
    if (mResizeDelay > 5) {
        resizeTimer->Stop();
        renderSizeChanged();
    }
}

void Document::renderSizeChanged()
{
    Bitmap^ oldImage = displayImage;
    System::Drawing::Size newSize = renderBox->Size;
    if (newSize.Width <= 0 || newSize.Height <= 0) return;
    try {
        if (renderBox->Image != nullptr && renderBox->Image->Size == newSize)
            return;
        displayImage = gcnew Bitmap(newSize.Width, newSize.Height, 
            System::Drawing::Imaging::PixelFormat::Format32bppArgb);
        Graphics^ g = Graphics::FromImage(displayImage);
        g->Clear(Color::White);
        renderBox->Image = displayImage;
        updateRenderBox();
        delete oldImage;
    } catch (ArgumentException^) {
        setMessageText("Error creating new screen bitmap." );
    }
}

System::Void Document::splitterMoved(Object^ sender, SplitterEventArgs^ e)
{
    Form1^ parent = (Form1^)MdiParent;

    if (parent->isResizing || parent->ActiveMdiChild != static_cast<Form^>(this))
        return;

    Form1::prefs->DocumentSplitter = documentSplitter->SplitterDistance;
    Form1::prefs->EditorSplitter = editorSplitter->SplitterDistance;
}

System::Void Document::variationKeyDown(Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
    nonAlphaInVariation = false;

    if (e->KeyCode >= Keys::A && e->KeyCode <= Keys::Z) return;
    if (e->KeyCode == Keys::Back) return;
    if (e->KeyCode == Keys::Return) return;

    nonAlphaInVariation = true;
}

System::Void Document::variationKeyPress(Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
    if (nonAlphaInVariation) {
        e->Handled = true;
        //Console::Beep();
        System::Media::SystemSounds::Beep->Play();
    } else if (e->KeyChar == '\r') {
        e->Handled = true;
        RenderButton_Click(sender, e);
    }
}

System::Void Document::Frame_KeyPress(Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
    if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar))
        e->Handled = true;
}

System::Void Document::variationChanged(System::Object^ sender, System::EventArgs^ e)
{
    mReuseVariation = true;
    variationEdit->ForeColor = Color::Blue;
    if (variationEdit->Text == String::Empty) {
        variationEdit->Text = "A";
        currentVariation = Variation::fromString("A");
        System::Media::SystemSounds::Beep->Play();
        return;
    }

    array<Byte>^ encodedVar = System::Text::Encoding::UTF8->GetBytes(variationEdit->Text);
    if (encodedVar->Length == 0) {
        variationEdit->Text = "A";
        currentVariation = Variation::fromString("A");
        return;
    }
    pin_ptr<Byte> pinnedVar = &encodedVar[0];
    currentVariation = Variation::fromString(reinterpret_cast<const char*>(pinnedVar));
}

System::Void Document::Frame_Changed(System::Object^ sender, System::EventArgs^ e)
{
    mReuseVariation = true;
    variationEdit->ForeColor = Color::Blue;
    if (frameEdit->Text == String::Empty) {
        frameEdit->Text = "1";
        renderParams->frame = 1;
        return;
    }

    try {
        renderParams->frame = System::Int32::Parse(frameEdit->Text);
        if (renderParams->frame >= 1 && renderParams->frame <= renderParams->animateFrameCount)
            return;
    }
    catch (System::SystemException^) {}
    // Bad parse or out-of-range frame
    frameEdit->Text = "1";
    renderParams->frame = 1;
    System::Media::SystemSounds::Asterisk->Play();
}

System::Void Document::Size_Changed(System::Object^ sender, System::EventArgs^ e)
{
    mReuseVariation = true;
    variationEdit->ForeColor = Color::Blue;
    int s = 0;
    TextBox^ box = (TextBox^)sender;
    if (!System::Int32::TryParse(box->Text, s) || s < 1) {
        box->Text = "1000";
        s = 1000;
    }
    if (box == widthEdit)
        renderParams->width = s;
    else
        renderParams->height = s;
    renderParams->saveToPrefs();
}

System::Void Document::Style_Cfdg(System::Object ^ sender, ScintillaNET::StyleNeededEventArgs ^ e)
{
    auto startPos = cfdgText->GetEndStyled();
    auto startLine = cfdgText->LineFromPosition(startPos);
    startPos = cfdgText->Lines[startLine]->Position;
    long endPos = e->Position;
    auto endLine = cfdgText->LineFromPosition(endPos);

    CFscintilla::Style state = CFscintilla::StyleDefault;
    if (startLine > 0 && static_cast<CFscintilla::Style>(cfdgText->GetStyleAt(startPos - 1)) == CFscintilla::StyleComment)
        state = CFscintilla::StyleComment;

    std::vector<char> text, styles;

    cfdgText->StartStyling(startPos);
    for (auto i = startLine; i <= endLine; ++i) {
        int length = static_cast<int>(cfdgText->DirectMessage(2350, IntPtr(i), IntPtr(0)));    // SCI_LINELENGTH = 2350
        if (static_cast<long>(text.size()) < length + 1)
            text.resize(length + 1);
        if (static_cast<long>(styles.size()) < length)
            styles.resize(length);
        cfdgText->DirectMessage(2153, IntPtr(i), IntPtr(text.data()));  // SCI_GETLINE = 2153
        text[length] = '\0';
        state = CFscintilla::StyleLine(length, text.data(), styles.data(), state);
        cfdgText->DirectMessage(2073, IntPtr(length), IntPtr(styles.data()));   // SCI_SETSTYLINGEX = 2073
    }
}

System::Void Document::Text_Changed(System::Object ^ sender, ScintillaNET::ModificationEventArgs ^ e)
{
    if (cfdgText->AutoCActive && (static_cast<int>(e->Source) & 0x60))
        CheckAutoC();
}

System::Void Document::InsertionCheck(System::Object ^ sender, ScintillaNET::InsertCheckEventArgs ^ e)
{
    // auto indent
    if (e->Text->Equals("\r\n") || e->Text->Equals("\r") || e->Text->Equals("\n")) {
        auto lineno = cfdgText->LineFromPosition(e->Position);
        String^ line = cfdgText->Lines[lineno]->Text;
        auto indent = cfdgText->Lines[lineno]->Indentation;
        int tabWidth = ((Form1^)MdiParent)->prefs->TabWidth;
        bool white = true;
        for each (Char c in line) {
            if (c == L'{')
                indent += tabWidth;
            if (c == L'}' && !white)
                indent -= tabWidth;
            if (c <= 0 || c >= 0x80 || !isspace(c))
                white = false;
        }
        if (indent > 0) {
            String^ nextline = e->Text->PadRight(e->Text->Length + indent);
            e->Text = nextline;
        }
    }
}

System::Void Document::AutoCCharDeleted(System::Object ^ sender, System::EventArgs ^ e)
{
    CheckAutoC();
}

System::Void Document::CharAdded(System::Object ^ sender, ScintillaNET::CharAddedEventArgs ^ e)
{
    // auto unindent
    if (e->Char == '}') {
        auto pos = cfdgText->CurrentPosition;
        auto lineno = cfdgText->LineFromPosition(pos);
        int indentPos = cfdgText->DirectMessage(2128, IntPtr(lineno), IntPtr(0)).ToInt32(); // SCI_GETLINEINDENTPOSITION = 2128
        if (indentPos + 1 == pos) {
            auto indent = cfdgText->Lines[lineno]->Indentation;
            indent -= ((Form1^)MdiParent)->prefs->TabWidth;
            if (indent < 0)
                indent = 0;
            cfdgText->Lines[lineno]->Indentation = indent;
        }
    }

    // autocomplete
    CheckAutoC();
}

System::Void Document::CheckAutoC()
{
    auto pos = cfdgText->CurrentPosition;
    auto wordPos = cfdgText->WordStartPosition(pos, true);
    auto len = pos - wordPos;
    if (len > 1) {
        String^ frag = cfdgText->GetTextRange(wordPos, len);
        System::Text::StringBuilder^ list = gcnew System::Text::StringBuilder(1500);
        for each (String^ word in ((Form1^)MdiParent)->AutoComplete)
            if (word->StartsWith(frag, System::StringComparison::OrdinalIgnoreCase)) {
                if (list->Length > 0)
                    list->Append(" ");
                list->Append(word);
            }
        if (list->Length > 0) {
            cfdgText->AutoCShow(len, list->ToString());
            return;
        }
    }
    if (cfdgText->AutoCActive)
        cfdgText->AutoCCancel();
}

static char safechar(ScintillaNET::Scintilla^ editor, int pos)
{
    if (!editor || pos < 0) return 'A';
    auto c = editor->GetCharAt(pos);
    if (c < 1 || c > 255) return 'B';
    return (char)c;
}

System::Void Document::UpdateUI(System::Object ^ sender, ScintillaNET::UpdateUIEventArgs ^ e)
{
    auto caretPos = cfdgText->CurrentPosition;
    if (caretPos == lastCaretPosition) return;
    lastCaretPosition = caretPos;
    int bracePos1 = -1;
    int bracePos2 = -1;
    if (strchr("[]{}()", safechar(cfdgText, caretPos - 1)))
        bracePos1 = caretPos - 1;
    else if (strchr("[]{}()", safechar(cfdgText, caretPos)))
        bracePos1 = caretPos;
    if (bracePos1 >= 0) {
        bracePos2 = cfdgText->BraceMatch(bracePos1);
        if (bracePos2 == cfdgText->InvalidPosition)
            cfdgText->BraceBadLight(bracePos1);
        else
            cfdgText->BraceHighlight(bracePos1, bracePos2);
    } else {
        cfdgText->BraceHighlight(cfdgText->InvalidPosition, cfdgText->InvalidPosition);
    }
}

System::Void Document::Indent_Click(System::Object ^ sender, System::EventArgs ^ e)
{
    bool didIndent = false;
    try {
        ToolStripMenuItem^ ctrl = dynamic_cast<ToolStripMenuItem^>(sender);
        String^ tag = dynamic_cast<String^>(ctrl->Tag);
        int delta = ((Form1^)MdiParent)->prefs->TabWidth * Int32::Parse(tag);
        auto start = cfdgText->AnchorPosition;
        auto end = cfdgText->CurrentPosition;
        start = cfdgText->LineFromPosition(start);
        end = cfdgText->LineFromPosition(end);
        if (end < start) {
            auto t = start; start = end; end = t;
        }
        for (; start <= end; ++start) {
            auto indent = cfdgText->Lines[start]->Indentation;
            auto newIndent = indent  +delta;
            if (newIndent < 0) newIndent = 0;
            if (indent != newIndent) {
                if (!didIndent)
                    cfdgText->BeginUndoAction();
                didIndent = true;
                cfdgText->Lines[start]->Indentation = newIndent;
            }
        }
    } catch (...) { }
    if (didIndent)
        cfdgText->EndUndoAction();
}

void Document::updateRenderButton()
{
    int lastIndex = mRenderButtonIndex;

    if (mRenderer && renderThread->IsBusy) {
        ++mRenderButtonIndex;
        if (mRenderButtonIndex > 8) mRenderButtonIndex = 1;
        if (mRenderer->requestFinishUp) {
            toolStripRenderButton->Text = "Stop Now";
        } else {
            toolStripRenderButton->Text = "Stop";
        }
    } else {
		switch (mRenderButtonAction) {
		case RenderButtonAction::Render:
			toolStripRenderButton->Text = "Render";
			break;
        case RenderButtonAction::RenderSized:
            toolStripRenderButton->Text = "Sized";
            break;
        case RenderButtonAction::Animate:
			toolStripRenderButton->Text = "Animate";
			break;
		case RenderButtonAction::AnimateFrame:
			toolStripRenderButton->Text = "Frame";
			break;
		}
        mRenderButtonIndex = 0;

        bool visFrame = mRenderButtonAction == RenderButtonAction::AnimateFrame;
        bool visSize = mRenderButtonAction == RenderButtonAction::RenderSized;
        if (frameEdit->Visible != visFrame || widthEdit->Visible != visSize) {
            rightSeparator = toolStripVariationSeparator;
            if (visFrame) rightSeparator = toolStripFrameSeparator;
            if (visSize) rightSeparator = toolStripSizeSeparator;
            toolStrip1->SuspendLayout();

            frameEdit->Visible = visFrame;
            toolStripFrameLabel->Visible = visFrame;
            toolStripFrameSeparator->Visible = visFrame;
            toolStripPrevFrame->Visible = visFrame;
            toolStripNextFrame->Visible = visFrame;

            toolStripSizeLabel1->Visible = visSize;
            toolStripSizeLabel2->Visible = visSize;
            widthEdit->Visible = visSize;
            heightEdit->Visible = visSize;
            toolStripSizeSeparator->Visible = visSize;

            toolStrip1->ResumeLayout();
            stripSizeChanged(nullptr, nullptr);
        }
    }

    if (lastIndex != mRenderButtonIndex) {
        toolStripRenderButton->ImageIndex = mRenderButtonIndex + imageListBase;
    }
}

void Document::DoRender()
{
    Form1::DeleteRenderer(mRenderer); mRenderer = nullptr; 
	mEngine->reset();
    setMessageText(nullptr);

    if (mMovieFile || mMoviePlayer) {
        TempFileDeleter^ killit = gcnew TempFileDeleter(tempfile_ptr(mMovieFile), mMoviePlayer);
    }
    mMoviePlayer = nullptr;
    mMovieFile = nullptr;

    if (!mSystem)
        mSystem = new WinSystem(this->Handle.ToPointer());

    bool modifiedSinceRender = SyncToSystem();

    if (!modifiedSinceRender && !mReuseVariation) {
        NextVar_Click(nullptr, nullptr);
    }
    mReuseVariation = false;
    variationEdit->ForeColor = Color::Black;

    *mEngine = CFDG::ParseFile(mSystem->mName.c_str(), mSystem, currentVariation);
    if (!(*mEngine)) {
        System::Media::SystemSounds::Beep->Play();
        return;
    }

    if (renderParams->action == RenderParameters::RenderActions::Render && 
        (renderParams->width == 0 || renderParams->height == 0))
    {
        renderParams->width = renderBox->Size.Width;
        renderParams->height = renderBox->Size.Height;
        if ((*mEngine)->isTiled()) {
            renderParams->width = (renderParams->width * 9) / 10;
            renderParams->height = (renderParams->height * 9) / 10;
        }
    }

    int width = renderParams->width;
    int height = renderParams->height;
    if (renderParams->action == RenderParameters::RenderActions::Animate) {
        width = renderParams->animateWidth;
        height = renderParams->animateHeight;
    }

    mRenderer = (*mEngine)->renderer(*mEngine, width, height,
        (float)renderParams->minimumSize, currentVariation, renderParams->borderSize).release();
	if (!mRenderer) {
		mEngine->reset();
		return;
	}

    if (renderParams->action == RenderParameters::RenderActions::Render) {
        renderParams->width = mRenderer->m_width;
        renderParams->height = mRenderer->m_height;
    }

    mTiled = (*mEngine)->isTiled() || (*mEngine)->isFrieze();

    delete mCanvas;
    mCanvas = nullptr;

    if ((renderParams->action == RenderParameters::RenderActions::Animate) ? 
            renderParams->animateFrame : renderParams->periodicUpdate)
    {
        setupCanvas(mRenderer);
    }

    if (renderParams->action == RenderParameters::RenderActions::Animate &&
        !renderParams->animateFrame)
    {
        mMovieFile = new TempFile(mSystem, AbstractSystem::MovieTemp, 0);
        auto stream = mMovieFile->forWrite();
        stream.reset();

        String^ tname = gcnew String(mMovieFile->name().c_str());
        array<Byte>^ bytes = System::Text::Encoding::UTF8->GetBytes(tname);
        std::string str;
        str.resize(bytes->Length);
        Marshal::Copy(bytes, 0, IntPtr(&str[0]), bytes->Length);

        mAnimationCanvas = new ffCanvas(str.c_str(), WinCanvas::SuggestPixelFormat(mEngine->get()),
            renderParams->animateWidth, renderParams->animateHeight,
            renderParams->frameRate, (ffCanvas::QTcodec)renderParams->codec);

        if (mAnimationCanvas->mError) {
            String^ message = gcnew String(mAnimationCanvas->mErrorMsg);
            System::Media::SystemSounds::Beep->Play();
            System::Windows::Forms::MessageBox::Show(MdiParent, message);
            setMessageText(message);
            delete mAnimationCanvas;
            mAnimationCanvas = nullptr;
            return;
        }
    }

    if (!mCanvas || mCanvas->mWidth) {
        postAction = PostRenderAction::DoNothing;
        renderThread->RunWorkerAsync();
        statusTimer->Start();
        updateRenderButton();
    } else {
        delete mCanvas;
        mCanvas = nullptr;
    }
}

bool Document::SyncToSystem()
{
    // Encode the text as UTF8
    array<Byte>^ encodedCfdg = System::Text::Encoding::UTF8->GetBytes(cfdgText->Text);
    array<Byte>^ encodedName = System::Text::Encoding::UTF8->GetBytes(this->Name);
    array<Byte>^ zero = { '\0' };
    if (encodedCfdg->Length == 0) encodedCfdg = zero;
    if (encodedName->Length == 0) encodedName = zero;

    // prevent GC moving the bytes around while this variable is on the stack
    pin_ptr<Byte> pinnedCfdg = &encodedCfdg[0];
    pin_ptr<Byte> pinnedName = &encodedName[0];

    return mSystem->updateInfo(reinterpret_cast<const char*>(pinnedName), 
                               reinterpret_cast<const char*>(pinnedCfdg));
}

void Document::RunRenderThread(Object^ sender, DoWorkEventArgs^ e)
{
    mProgressDelay = 0;
    switch (renderParams->action) {
        case RenderParameters::RenderActions::Animate: 
            if (renderParams->animateFrame) {
                mRenderer->animate(mCanvas, renderParams->animateFrameCount,
                    renderParams->frame, renderParams->animateZoom && !mTiled);
            } else {
                mRenderer->animate(mAnimationCanvas, renderParams->animateFrameCount, 0,
                    renderParams->animateZoom && !mTiled);

                delete mAnimationCanvas;
                mAnimationCanvas = nullptr;
            }
            break;
        case RenderParameters::RenderActions::SaveSVG:
            mRenderer->draw(mSVGCanvas);
            delete mSVGCanvas;
            mSVGCanvas = nullptr;
            break;
        case RenderParameters::RenderActions::Render:
            {
                mRenderer->run(mCanvas, renderParams->periodicUpdate);
                if (!mCanvas && !mRenderer->requestStop) {
                    setupCanvas(mRenderer);
                    mRenderer->draw(mCanvas);
                }
            }
            break;
    }
}

void Document::RenderCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e)
{
    statusTimer->Stop();

    if (postAction == PostRenderAction::Exit) {
        MdiParent->Close();
        return;
    }

    if (postAction == PostRenderAction::Close) {
        this->Close();
        return;
    }

    updateRenderButton();

    switch (renderParams->action) {
        case RenderParameters::RenderActions::Render:
            if (renderParams->suppressDisplay)
                setMessageText("Done!");
            break;
        case RenderParameters::RenderActions::Animate:
            setMessageText(renderParams->animateFrame ? "Done!" : "Movie complete.");
            break;
        case RenderParameters::RenderActions::SaveSVG:
            setMessageText("SVG save complete.");
            break;
    }

    PostRenderAction nextAction = postAction;
    postAction = PostRenderAction::DoNothing;

    switch (nextAction) {
        case PostRenderAction::DoNothing:
            break;
        case PostRenderAction::Render:
            menuRRender->PerformClick();
            break;
        case PostRenderAction::RenderRepeat:
            menuRRenderAgain->PerformClick();
            break;
        case PostRenderAction::RenderSize:
            menuRRenderSize->PerformClick();
            break;
        case PostRenderAction::Animate:
            menuRAnimate->PerformClick();
            break;
        case PostRenderAction::AnimateFrame:
            menuRAnimateFrame->PerformClick();
            break;
        case PostRenderAction::SaveOutput:
            menuROutput->PerformClick();
            break;
    }

    if (nextAction == PostRenderAction::DoNothing &&
        renderParams->action == RenderParameters::RenderActions::Animate &&
        !renderParams->animateFrame && renderParams->preview)
    {
        mMoviePlayer = gcnew System::Diagnostics::Process;

        try {
            mMoviePlayer->StartInfo->UseShellExecute = false;
            mMoviePlayer->StartInfo->FileName = "ffplay.exe";
            mMoviePlayer->StartInfo->CreateNoWindow = true;
            mMoviePlayer->StartInfo->Arguments = gcnew String(mMovieFile->name().c_str());
            mMoviePlayer->Start();
            mMoviePlayer->EnableRaisingEvents = true;
        } catch (Exception^ e) {
            setMessageText(e->Message);
        }
    }
}

System::Void Document::statusTick(Object^ sender, EventArgs^ e)
{
    if (renderThread->IsBusy && mRenderer) {
        updateRenderButton();
        mRenderer->requestUpdate = true;
    }
}

Bitmap^ Document::MakeBitmap(bool cropped, WinCanvas *canvas)
{
    if (canvas->mPixelFormat & aggCanvas::Has_16bit_Color) {
        delete mTempCanvas;
        mTempCanvas = canvas->Make8bitCopy();
        canvas = mTempCanvas;
    }

    Bitmap^ bm;
    char* data = (char*)(canvas->bitmap());
    int width = canvas->mWidth;
    int height = canvas->mHeight;
    if (cropped) {
        width = canvas->cropWidth();
        height = canvas->cropHeight();
        data += canvas->mStride * canvas->cropY() + 
                aggCanvas::BytesPerPixel.at(canvas->mPixelFormat) * canvas->cropX();
    }

    IntPtr pixelStore = IntPtr((void*)data);

    try {
    switch (canvas->mPixelFormat) {
        case aggCanvas::Gray8_Blend: {
                bm = gcnew Bitmap(width, height, canvas->mStride,Imaging::PixelFormat::Format8bppIndexed, pixelStore);
                Imaging::ColorPalette^ gray = bm->Palette;
                for (int i = 0; i < 256; ++i) {
                    gray->Entries[i] = Color::FromArgb(255, i, i, i);
                }
                bm->Palette = gray;
                break;
            }
        case aggCanvas::RGB8_Blend:
            bm = gcnew Bitmap(width, height, canvas->mStride, Imaging::PixelFormat::Format24bppRgb, pixelStore);
            break;
        case aggCanvas::RGBA8_Blend:
            bm = gcnew Bitmap(width, height, canvas->mStride, Imaging::PixelFormat::Format32bppPArgb, pixelStore);
            break;
        default:
            bm = nullptr;
            break;
    }
    } catch (ArgumentException^) {
        return nullptr;
    }

    return bm;
}

void Document::setupCanvas(Renderer* r)
{
    if (displayImage == nullptr)
        renderSizeChanged();

    if (!mCanvas) {
        int width = renderParams->action == RenderParameters::RenderActions::Render ?
            renderParams->width : renderParams->animateWidth;
        int height = renderParams->action == RenderParameters::RenderActions::Render ?
            renderParams->height : renderParams->animateHeight;
        mCanvas = new WinCanvas(mSystem, WinCanvas::SuggestPixelFormat(mEngine->get()), 
            width, height, (*mEngine)->getBackgroundColor());
    }
}

void Document::updateRenderBox()
{
    Graphics^ g = Graphics::FromImage(displayImage);

    if (!mCanvas) {
        g->Clear(Color::White);
        renderBox->Invalidate();
        delete g;
        return;
    }

    System::Drawing::Size destSize = displayImage->Size;
    System::Drawing::Size srcSize = mTiled ? System::Drawing::Size(mCanvas->cropWidth(), mCanvas->cropHeight())
                                           : System::Drawing::Size(mCanvas->mWidth, mCanvas->mHeight);

    double scale = 1.0;
    SolidBrush^ grayBrush = gcnew SolidBrush(Color::LightGray);
    agg::rgba8 bk(mCanvas->mBackground);
    Color back = Color::FromArgb(bk.a, bk.r, bk.g, bk.b);
    SolidBrush^ backBrush = nullptr;
    if (mCanvas->mBackground.a < 1.0)
        backBrush = gcnew SolidBrush(back);

    // check if the bitmap is too big and shrink it to fit
    if (srcSize.Width > destSize.Width || srcSize.Height > destSize.Height) {
        double widthScale = (double)destSize.Width / srcSize.Width;
        double heightScale = (double)destSize.Height / srcSize.Height;
        scale = (widthScale < heightScale) ? widthScale : heightScale;
    }

    // scale the bitmap if it is too big
    int scaledWidth = (int)(srcSize.Width * scale);
    int scaledHeight = (int)(srcSize.Height * scale);

    // center the scaled bitmap
    int originX = (destSize.Width - scaledWidth)/ 2;
    int originY = (destSize.Height - scaledHeight)/ 2;

    // Draw the bitmap scaled
    System::Drawing::Rectangle destRect(originX, originY, scaledWidth, scaledHeight);
    if (backBrush) {
        Rectangle fullRect(0, 0, destSize.Width, destSize.Height);
        drawCheckerBoard(g, grayBrush, fullRect);
        g->FillRectangle(backBrush, fullRect);
    } else {
        g->Clear(back);
    }

    if (renderParams->suppressDisplay) {
        renderBox->Invalidate();
        delete g;
        return;
    }

    Bitmap^ newBitmap = MakeBitmap(mTiled, mCanvas);
    if (newBitmap == nullptr) {
        delete g;
        delete mTempCanvas;
        mTempCanvas = nullptr;
        return;
    }

    g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::HighQualityBicubic;

    if (mTiled && scale == 1.0) {
        drawTiled(newBitmap, displayImage, g, grayBrush, originX, originY);
    } else {
        if (mCanvas->mBackground.a < 1.0)
            drawCheckerBoard(g, grayBrush, destRect);
        if (scale == 1.0) {
            g->DrawImageUnscaled(newBitmap, originX, originY);
        } else {
            g->DrawImage(newBitmap, destRect, 
                0, 0, srcSize.Width, srcSize.Height, 
                System::Drawing::GraphicsUnit::Pixel);
        }
    }

    System::Drawing::Pen^ p2 = gcnew System::Drawing::Pen(Color::Black, 1.0);
    p2->DashStyle = System::Drawing::Drawing2D::DashStyle::Dot;
    g->DrawRectangle(p2, originX - 1, originY - 1, scaledWidth + 1, scaledHeight + 1);

    delete newBitmap;
    delete g;
    delete mTempCanvas;
    mTempCanvas = nullptr;

    renderBox->Invalidate();
}

void Document::drawCheckerBoard(Graphics^ g, SolidBrush^ grayBrush, Rectangle destRect)
{
    g->SetClip(destRect, System::Drawing::Drawing2D::CombineMode::Replace);
    g->Clear(Color::White);
    for (int y = destRect.Y & ~7; y <= destRect.Y + destRect.Height; y += 8)
        for (int x = destRect.X & ~7; x <= destRect.X + destRect.Width; x += 8)
            if ((x ^ y) & 8) {
                g->FillRectangle(grayBrush, x, y, 8, 8);
            }
    g->ResetClip();
}

void Document::drawTiled(Bitmap^ src, Bitmap^ dest, Graphics^ g, 
                         SolidBrush^ grayBrush, int x, int y)
{
    if (!mRenderer || !mRenderer->m_tiledCanvas)
        return;

    tileList points = mRenderer->m_tiledCanvas->getTessellation(dest->Width, dest->Height,
                                                                x, y, true);

    for (tileList::reverse_iterator pt = points.rbegin(), ept = points.rend();
        pt != ept; ++pt)
    {
        if (grayBrush) {
            Rectangle tileRect(pt->x, pt->y, src->Width, src->Height);
            drawCheckerBoard(g, grayBrush, tileRect);
        }
        g->DrawImageUnscaled(src, pt->x, pt->y);
    }
}
