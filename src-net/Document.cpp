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
#include "variation.h"
#include "WinCanvas.h"
#include "WinSystem.h"
#include "Rand64.h"
#include "tiledCanvas.h"
#include "resource.h"
#include "SaveImage.h"
#include "SVGCanvas.h"
#include "SaveMovie.h"
#include "ffCanvas.h"
#include "UploadDesign.h"
#include "upload.h"

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
    // catch form closing to handle worker thread and saving cfdg file if it 
    // is modified
    FormClosing += gcnew FormClosingEventHandler(this, &Document::FormIsClosing);

    // Some initialization needs to be deferred until all the handles are made
    moreInitHandler = gcnew EventHandler(this, &Document::moreInitialization);
    this->Load += moreInitHandler;

    // keep track of when the cfdg file is modified
    cfdgText->ModifiedChanged += gcnew EventHandler(this, &Document::modifiedCFDG);

    // get resize events so that the status and message text fields can stay the
    // right size
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
    documentSplitter->SplitterDistance = (int)(documentSplitter->Size.Width * 
                                         Form1::prefs->DocumentSplitter);
    editorSplitter->SplitterDistance = (int)(editorSplitter->Size.Height *
                                       Form1::prefs->EditorSplitter);
    SplitterEventHandler^ splitterHandler = gcnew SplitterEventHandler(this, &Document::splitterMoved);
    documentSplitter->SplitterMoved += splitterHandler;
    editorSplitter->SplitterMoved += splitterHandler;

    // setup the render parameters and the render thread
    renderParams = new RenderParameters();
    lastRenderWasSized = false;
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
}

void Document::DestroyStuff()
{
    delete mCanvas;
    Form1::DeleteRenderer(mRenderer); mRenderer = nullptr; mEngine = nullptr;
    if (mSystem) mSystem->orphan();
    delete mSVGCanvas;
    delete mAnimationCanvas;
    delete renderParams;
}

System::Void Document::moreInitialization(System::Object^ sender, System::EventArgs^ e)
{
    // shrink the tabs to a reasonable size
    int tabs[1] = {12};
    IntPtr hr = cfdgText->Handle; 
    int ret = ::SendMessage(hr.ToInt32(), WinSystem::EM_SETTABSTOPS, 0, nullptr);
    ret = ::SendMessage(hr.ToInt32(), WinSystem::EM_SETTABSTOPS, 1, tabs);

    cfdgText->Font = ((Form1^)MdiParent)->TextFont;
    ((Form1^)MdiParent)->TextFontChanged += gcnew EventHandler(this, &Document::textFontHandler);

    cfdgText->Invalidate();

    // enable/disable File->Revert menu command
    ((Form1^)MdiParent)->menuFile->DropDownOpened += 
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
    toolStrip1->Items->Insert(toolStrip1->Items->IndexOf(toolStripVariation), 
                              gcnew ToolStripControlHost(variationEdit));
    toolStrip1->Items->Remove(toolStripVariation); 
    variationEdit->MaxLength = 6;
    variationEdit->Name = L"variationEdit";
    variationEdit->MinimumSize = System::Drawing::Size(75, 25);
    variationEdit->MaximumSize = System::Drawing::Size(75, 25);
    variationEdit->TextChanged += processVariationChange;
    --currentVariation;
    NextVar_Click(nullptr, nullptr);

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
            cfdgText->Modified = false;
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
        cfdgText->Modified = false;
        return;
    }

    int pos = Form1::exampleSet->IndexOfKey(this->Name);
    if (pos >= 0) {
        cfdgText->Text = (String^)Form1::exampleSet->GetByIndex(pos);
        cfdgText->Modified = false;
        return;
    }

    try {
        StreamReader sr(Name);
        cfdgText->Text = sr.ReadToEnd();
        cfdgText->Modified = false;
    } catch (Exception^) {
        ((Form1^)MdiParent)->mruManager->Remove(Name);
        cfdgText->Text = String::Empty;
        cfdgText->Modified = false;
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
}

System::Void Document::menuRRender_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (renderThread->IsBusy) {
        postAction = PostRenderAction::Render;
        return;
    }

    renderParams->initFromPrefs();
    renderParams->width = renderParams->height = 0;
    renderParams->periodicUpdate = true;
    renderParams->suppressDisplay = false;
    renderParams->action = RenderParameters::RenderActions::Render;
    lastRenderWasSized = false;
    DoRender();
}

System::Void Document::menuRRenderSize_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (renderThread->IsBusy) {
        postAction = PostRenderAction::RenderSize;
        return;
    }

    RenderSizeDialog rs(renderParams);

    if (sender != menuRRenderSize || rs.ShowDialog() == Windows::Forms::DialogResult::OK) {
        if (sender != menuRRenderSize) 
            renderParams->saveToPrefs();
        renderParams->action = RenderParameters::RenderActions::Render;
        lastRenderWasSized = true;
        DoRender();
    }
}

System::Void Document::menuRRenderAgain_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (renderThread->IsBusy) {
        postAction = PostRenderAction::RenderRepeat;
        renderParams->action = RenderParameters::RenderActions::Render;
        return;
    }

    if (!lastRenderWasSized) {
        renderParams->width = renderParams->height = 0;
    } else {
        NextVar_Click(nullptr, nullptr);
    }
    DoRender();
}

System::Void Document::menuRStop_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (mRenderer && renderThread->IsBusy) {
        mRenderer->requestStop = true;
        updateRenderButton();
    }
}

System::Void Document::menuRImage_Click(System::Object^ sender, System::EventArgs^ e)
{ 
    if (!mCanvas) {
        setMessageText("There is no image to save.");
        System::Console::Beep();
        return;
    }

    if (renderThread->IsBusy) {
        postAction = PostRenderAction::SaveImage;
        return;
    }

    SaveImage saveImageDlg(mEngine->isFrieze(), mTiled ? mOutputMultiplier : nullptr,
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


System::Void Document::menuRMovie_Click(System::Object^ sender, System::EventArgs^ e)
{ 
    if (!mCanvas || !mRenderer) {
        setMessageText("There is no movie to save.");
        System::Console::Beep();
        return;
    }

    if (renderThread->IsBusy) {
        postAction = PostRenderAction::SaveMovie;
        return;
    }

    SaveMovie saveMovieDlg(Path::GetFileNameWithoutExtension(Text) + ".mov",
                           ((Form1^)MdiParent)->saveDirectory);
    saveMovieDlg.checkZoom->Enabled = !mTiled;

    if (saveMovieDlg.ShowTheDialog(this) == System::Windows::Forms::DialogResult::OK) {
        ((Form1^)MdiParent)->saveDirectory = 
            Path::GetDirectoryName(saveMovieDlg.FileDlgFileName);

        String^ fileName = saveMovieDlg.FileDlgFileName;
        if (Form1::prefs->ImageAppendVariation) {
            fileName = Path::GetDirectoryName(fileName) + "\\" +
                Path::GetFileNameWithoutExtension(fileName) +
                "-" + variationEdit->Text->ToLower() +  
                Path::GetExtension(fileName);
        }

        setMessageText("Saving QuickTime movie.");

        renderParams->animateFrameCount = Form1::prefs->AnimateLength * Form1::prefs->AnimateFrameRate;
        renderParams->animateZoom = Form1::prefs->AnimateZoom;
        renderParams->action = RenderParameters::RenderActions::Animate;

        array<Byte>^ pathutf8 = System::Text::Encoding::UTF8->GetBytes(fileName);
        if (pathutf8->Length == 0) {
            setMessageText("Bad file name");
            return;
        }
        pin_ptr<Byte> pathutf8pin = &pathutf8[0];
        const char* path = reinterpret_cast<const char*>(pathutf8pin);

        mAnimationCanvas = new ffCanvas(path, WinCanvas::SuggestPixelFormat(mEngine),
                                        renderParams->width, renderParams->height,
                                        Form1::prefs->AnimateFrameRate);

        if (mAnimationCanvas->mError) {
            delete mAnimationCanvas;
            mAnimationCanvas = nullptr;
        } else {
            postAction = PostRenderAction::DoNothing;
            renderThread->RunWorkerAsync();
            statusTimer->Start();
            updateRenderButton();
        }
    }
}

System::Void Document::menuRUpload_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (!mCanvas) {
        setMessageText("Nothing to upload, try rendering first.");
        return;
    }

    Upload u;
    u.mCompression = mCanvas->colorCount256() ? Upload::CompressPNG8 : Upload::CompressJPEG;
    u.mTiled = mTiled;
    u.mVariation = currentVariation;

    array<Byte>^ encodedCfdg = System::Text::Encoding::UTF8->GetBytes(cfdgText->Text);
    pin_ptr<Byte> pinnedCfdg = &encodedCfdg[0];

    u.mText = reinterpret_cast<const char*>(pinnedCfdg);
    u.mTextLen = strlen(u.mText);

    UploadDesign uploadWiz(this, Path::GetFileNameWithoutExtension(Text), &u,
                           mEngine->isFrieze(), mTiled ? mOutputMultiplier : nullptr);

    uploadWiz.ShowDialog(this);
    u.mText = 0;
    u.mTextLen = 0;
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
    if (cfdgText->SelectionLength > 0)
        cfdgText->Cut();
}

System::Void Document::menuECopy_Click(System::Object^  sender, System::EventArgs^  e)
{
    if (cfdgText->SelectionLength > 0)
        cfdgText->Copy();
}

System::Void Document::menuEPaste_Click(System::Object^  sender, System::EventArgs^  e)
{
    if (Clipboard::GetDataObject()->GetDataPresent(DataFormats::Text))
        cfdgText->Paste();
}

System::Void Document::menuEDelete_Click(System::Object^  sender, System::EventArgs^  e)
{
    if (cfdgText->SelectionLength > 0)
        cfdgText->SelectedText = String::Empty;
}

System::Void Document::toolStripMenuUnicode_Click(System::Object^  sender, System::EventArgs^  e)
{
    ToolStripMenuItem^ i = dynamic_cast<ToolStripMenuItem^>(sender);
    if (i != nullptr)
        cfdgText->SelectedText = i->Text;
}

System::Void Document::textFontHandler(System::Object^ sender, System::EventArgs^ e)
{
    bool mod = cfdgText->Modified;
    cfdgText->Font = ((Form1^)MdiParent)->TextFont;
    if (mod != cfdgText->Modified)
        cfdgText->Modified = mod;
    setMessageText(String::Empty);
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
            int start = cfdgText->GetFirstCharIndexFromLine(b_line) + b_col;
            int end = cfdgText->GetFirstCharIndexFromLine(e_line) + e_col;
            cfdgText->Focus();
            cfdgText->SelectionStart = start;
            cfdgText->SelectionLength = end - start;
            cfdgText->ScrollToCaret();
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
    menuECopy->Enabled = cfdgText->SelectionLength > 0;
    menuECut->Enabled = cfdgText->SelectionLength > 0;
    menuEPaste->Enabled = Clipboard::GetDataObject()->GetDataPresent(DataFormats::Text);
    menuEDelete->Enabled = cfdgText->SelectionLength > 0;
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
        menuRRender_Click(sender, e);
    }
}

System::Void Document::PrevVar_Click(System::Object^ sender, System::EventArgs^ e)
{
    mUserChangedVariation = true;
    --currentVariation;
    if (currentVariation > maxVariation || currentVariation < minVariation)
        currentVariation = maxVariation;
    std::string vChars = Variation::toString(currentVariation, false);
    variationEdit->Text = gcnew String(vChars.c_str());
}

System::Void Document::NextVar_Click(System::Object^ sender, System::EventArgs^ e)
{
    mUserChangedVariation = true;
    ++currentVariation;
    if (currentVariation > maxVariation || currentVariation < minVariation)
        currentVariation = minVariation;
    std::string vChars = Variation::toString(currentVariation, false);
    variationEdit->Text = gcnew String(vChars.c_str());
}

void Document::WndProc( Message% m )
{
    // Listen for operating system messages.
    switch (m.Msg) {
        case WinSystem::WM_USER_MESSAGE_UPDATE: 
            {
                char* msg = (char*)m.WParam.ToPointer();
                String^ msgText = gcnew String(msg, 0, strlen(msg), System::Text::Encoding::UTF8);
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
    System::Drawing::Rectangle messageSize = toolStripStatus->Bounds;
    System::Drawing::Size stripSize = toolStrip1->Size;

    toolStripStatus->Width = stripSize.Width - messageSize.X - 6;
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
    Form1::prefs->DocumentSplitter = (double)(documentSplitter->SplitterDistance) /
                                     (double)(documentSplitter->Size.Width);
    Form1::prefs->EditorSplitter = (double)(editorSplitter->SplitterDistance) /
                                   (double)(editorSplitter->Size.Height);
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
        menuRRenderAgain_Click(sender, e);
    }
}

System::Void Document::variationChanged(System::Object^ sender, System::EventArgs^ e)
{
    if (variationEdit->Text == String::Empty) {
        variationEdit->Text = "A";
        System::Media::SystemSounds::Beep->Play();
        return;
    }

    mUserChangedVariation = true;
    array<Byte>^ encodedVar = System::Text::Encoding::UTF8->GetBytes(variationEdit->Text);
    if (encodedVar->Length == 0) {
        currentVariation = 0;
        return;
    }
    pin_ptr<Byte> pinnedVar = &encodedVar[0];
    currentVariation = Variation::fromString(reinterpret_cast<const char*>(pinnedVar));
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
        toolStripRenderButton->Text = "Render";
        mRenderButtonIndex = 0;
    }

    if (lastIndex != mRenderButtonIndex) {
        toolStripRenderButton->ImageIndex = mRenderButtonIndex + imageListBase;
    }
}

void Document::DoRender()
{
    Form1::DeleteRenderer(mRenderer); mRenderer = nullptr; mEngine = nullptr;
    setMessageText(nullptr);

    if (!mSystem)
        mSystem = new WinSystem(this->Handle.ToPointer());

    bool modifiedSinceRender = SyncToSystem();

    if (!modifiedSinceRender && !mUserChangedVariation && !lastRenderWasSized) {
        NextVar_Click(nullptr, nullptr);
    }
    mUserChangedVariation = false;

    mEngine = CFDG::ParseFile(mSystem->mName.c_str(), mSystem, currentVariation);
    if (!mEngine) {
        System::Media::SystemSounds::Beep->Play();
        return;
    }

    if (renderParams->width == 0 || renderParams->height == 0) {
        renderParams->width = renderBox->Size.Width;
        renderParams->height = renderBox->Size.Height;
        if (mEngine->isTiled()) {
            renderParams->width = (renderParams->width * 9) / 10;
            renderParams->height = (renderParams->height * 9) / 10;
        }
    }

    mRenderer = mEngine->renderer(renderParams->width, renderParams->height, 
        (float)renderParams->minimumSize, currentVariation, renderParams->borderSize);
    if (!mRenderer) return;

    renderParams->width = mRenderer->m_width;
    renderParams->height = mRenderer->m_height;

    mTiled = mEngine->isTiled() || mEngine->isFrieze();

    delete mCanvas;
    mCanvas = nullptr;

    if (renderParams->periodicUpdate)
        setupCanvas(mRenderer);

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
            {
                mRenderer->animate(mAnimationCanvas, renderParams->animateFrameCount, 
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
            setMessageText("Movie save complete.");
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
            this->menuRRenderAgain->PerformClick();
            break;
        case PostRenderAction::RenderSize:
            menuRRenderSize->PerformClick();
            break;
        case PostRenderAction::SaveImage:
            menuRImage->PerformClick();
            break;
        case PostRenderAction::SaveMovie:
            menuRMovie->PerformClick();
            break;
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
    char* data = canvas->mBM;
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
        mCanvas = new WinCanvas(mSystem, WinCanvas::SuggestPixelFormat(mEngine), 
            renderParams->width, renderParams->height, mEngine->getBackgroundColor());
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

    tileList points = mRenderer->m_tiledCanvas->getTesselation(dest->Width, dest->Height,
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
