// UploadDesign.cpp
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
#include "UploadDesign.h"
#include "Form1.h"
#include <sstream>

using namespace ContextFreeNet;
using namespace System;
using namespace System::IO;
using namespace System::Data;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;


System::Void UploadDesign::accountButton_Click(System::Object^  sender, System::EventArgs^  e)
{
    System::Diagnostics::Process::Start("http://www.contextfreeart.org/phpbb/profile.php?mode=register");
}

System::Void UploadDesign::uploadDesignLoaded(System::Object^  sender, System::EventArgs^  e)
{
    String^ ccUri = Form1::prefs->ccLicense;
    String^ option = String::Empty;
    if (ccUri->Length == 0) option = "&want_a_license=no_license_by_default";

    String^ html = String::Format(Form1::widgetHTML, ccUri, option);

    ccLicenseBrowser->DocumentText = html;

    // load the bitmaps used in the render button
    ImageList^ iList = statusStripUpload->ImageList;
    if (iList == nullptr)
        iList = gcnew ImageList();
    imageListBase = iList->Images->Count;
    iList->Images->AddRange(Form1::busyList);
    statusStripUpload->ImageList = iList;

    bouncer = gcnew WebBrowserNavigatingEventHandler(this, &UploadDesign::bounceNavigation);
    ccLicenseBrowser->Navigating += bouncer;

    uploadPoll = gcnew System::Windows::Forms::Timer();
    uploadPoll->Interval = 100;
    uploadPoll->Tick += gcnew EventHandler(this, &UploadDesign::uploadPoll_Tick);
}

System::Void UploadDesign::wizardPage_beforeChange(System::Object^ sender, 
                 CristiPotlog::Controls::Wizard::BeforeSwitchPagesEventArgs^ e)
{
    switch (e->OldIndex) {
        case -1:
            if (gotoDesignPage) {
                e->NewIndex = 1;
                gotoDesignPage = false;
            }
            break;
        case 0:
            if (usernameBox->Text->Length == 0 || passwordBox->Text->Length == 0) {
                e->Cancel = true;
                labelAcctError->Visible = true;
                System::Media::SystemSounds::Asterisk->Play();
                return;
            }
            labelAcctError->Visible = false;
            Form1::prefs->SkipAccount = checkSkipAcct->Checked;
            Form1::prefs->GalUsername = usernameBox->Text;
            Form1::prefs->GalPassword = passwordBox->Text;
            break;
        case 1:
            if (titleBox->Text->Length == 0 || fileNameBox->Text->Length == 0) {
                e->Cancel = true;
                labelDesignError->Text = L"You must provide a title and a file name.";
                labelDesignError->Visible = true;
                System::Media::SystemSounds::Asterisk->Play();
                return;
            }
            Form1::prefs->ImageCrop = checkCrop->Checked;
            if (outputMultiplier)  try {
                outputMultiplier[0] = System::Double::Parse(saveWidth->Text);
                outputMultiplier[1] = System::Double::Parse(saveHeight->Text);
            } catch (SystemException^) {
                e->Cancel = true;
                labelDesignError->Text = L"Output multipliers are invalid.";
                labelDesignError->Visible = true;
                System::Media::SystemSounds::Asterisk->Play();
                return;
            }
            labelDesignError->Visible = false;
            break;
        case 2:
            {
                try {
                    HtmlDocument^ dom = ccLicenseBrowser->Document;
                    HtmlElement^ elem = dom->GetElementById("cc_js_result_uri");
                    Form1::prefs->ccLicense = elem->GetAttribute("value");

                    elem = dom->GetElementById("cc_js_result_name");
                    Form1::prefs->ccName = elem->GetAttribute("value");

                    elem = dom->GetElementById("cc_js_result_img");
                    Form1::prefs->ccImage = elem->GetAttribute("value");
                } catch (Exception^) {
                    Form1::prefs->ccLicense = String::Empty;
                    Form1::prefs->ccName = String::Empty;
                    Form1::prefs->ccImage = String::Empty;
                }
                break;
            }
        case 3:
            uploadBrowser->Navigating -= bouncer;
            uploadBrowser->Navigate("about:blank");
            statusLabelUpload->Text = String::Empty;
            break;
    }
}

System::Void UploadDesign::wizardPage_afterChange(System::Object^ sender, 
                 CristiPotlog::Controls::Wizard::AfterSwitchPagesEventArgs^ e)
{
    if (e->NewIndex == 2) {
        wizard1->NextText = "Upload!";
    } else {
        wizard1->NextText = nextText;
    }
    if (e->NewIndex == 3) {
        wizard1->CancelText = "OK";

        System::Text::Encoding^ encodeutf8 = System::Text::Encoding::UTF8;

        if (usernameBox->Text->Length == 0) {
            statusLabelUpload->Text = "You must provide a username.";
            uploadBrowser->Navigate("about:NavigationFailure");
            return;
        }
        array<Byte>^ utf8array = encodeutf8->GetBytes(usernameBox->Text);
        pin_ptr<Byte> utf8arraypin = &utf8array[0];
        mUpload->mUserName = reinterpret_cast<const char*>(utf8arraypin);

        if (passwordBox->Text->Length == 0) {
            statusLabelUpload->Text = "You must provide a password.";
            uploadBrowser->Navigate("about:NavigationFailure");
            return;
        }
        utf8array = encodeutf8->GetBytes(passwordBox->Text);
        utf8arraypin = &utf8array[0];
        mUpload->mPassword = reinterpret_cast<const char*>(utf8arraypin);

        if (titleBox->Text->Length == 0) {
            statusLabelUpload->Text = "You must provide a title.";
            uploadBrowser->Navigate("about:NavigationFailure");
            return;
        }
        utf8array = encodeutf8->GetBytes(titleBox->Text);
        utf8arraypin = &utf8array[0];
        mUpload->mTitle = reinterpret_cast<const char*>(utf8arraypin);

        if (notesBox->Text->Length > 0) {
            utf8array = encodeutf8->GetBytes(notesBox->Text);
            utf8arraypin = &utf8array[0];
            mUpload->mNotes = reinterpret_cast<const char*>(utf8arraypin);
        }

        if (fileNameBox->Text->Length == 0) {
            statusLabelUpload->Text = "You must provide a file name.";
            uploadBrowser->Navigate("about:NavigationFailure");
            return;
        }
        utf8array = encodeutf8->GetBytes(fileNameBox->Text + ".cfdg");
        utf8arraypin = &utf8array[0];
        mUpload->mFileName = reinterpret_cast<const char*>(utf8arraypin);

        mUpload->mCompression = radioJPEG->Checked ? 
            Upload::CompressJPEG : Upload::CompressPNG8;

        mUpload->mTiled = checkTiled->Checked;

        if (Form1::prefs->ccLicense->Length > 0) {
            utf8array = encodeutf8->GetBytes(Form1::prefs->ccLicense);
            utf8arraypin = &utf8array[0];
            mUpload->mccLicenseURI = reinterpret_cast<const char*>(utf8arraypin);
        }

        if (Form1::prefs->ccName->Length > 0) {
            utf8array = encodeutf8->GetBytes(Form1::prefs->ccName);
            utf8arraypin = &utf8array[0];
            mUpload->mccLicenseName = reinterpret_cast<const char*>(utf8arraypin);
        }

        if (Form1::prefs->ccImage->Length > 0) {
            utf8array = encodeutf8->GetBytes(Form1::prefs->ccImage);
            utf8arraypin = &utf8array[0];
            mUpload->mccLicenseImage = reinterpret_cast<const char*>(utf8arraypin);
        }

        utf8arraypin = nullptr;

        MemoryStream^ bitmapStream = gcnew MemoryStream();
        if (!mDoc->saveToPNGorJPEG(nullptr, bitmapStream, false) || bitmapStream->Length == 0)
        {
            statusLabelUpload->Text = "Upload failed because of image problems.";
            uploadBrowser->Navigate("about:NavigationFailure");
            return;
        }
        array<Byte>^ imageDataArray = bitmapStream->GetBuffer();
        pin_ptr<Byte> imageData = &imageDataArray[0];
        mUpload->mImage = reinterpret_cast<const char*>(imageData);
        mUpload->mImageLen = imageDataArray->Length;

        std::ostringstream payload;
        mUpload->generatePayload(payload);
        std::string hdr = mUpload->generateHeader();
        String^ header = gcnew String(hdr.c_str());
        int payloadLength = (int)payload.str().length();
        array<Byte>^ postData = gcnew array<Byte>(payloadLength);
        pin_ptr<Byte> postDataPin = &postData[0];
        char* postBuf = reinterpret_cast<char*>(postDataPin);
        const std::string payloadstr = payload.str();
        const char* payloadbuf = payloadstr.c_str();
        memcpy(postBuf, payloadbuf, payloadLength);
        postDataPin = nullptr;

        uploadPoll->Enabled = true;
        statusLabelUpload->Text = "Upload in progress.";
        wizard1->CancelEnabled = false;

        uploadBrowser->Navigate("http://www.contextfreeart.org/gallery/upload.php", 
            String::Empty, postData, header);
    }
}

System::Void UploadDesign::uploadPoll_Tick(System::Object^  sender, System::EventArgs^  e)
{
    if (uploadBrowser->ReadyState == WebBrowserReadyState::Complete) {
        wizard1->CancelEnabled = true;
        uploadBrowser->Navigating += bouncer;
        statusIconUpload->ImageIndex = imageListBase;
        if (uploadBrowser->DocumentText->Contains("AFD8D2F0-B6EB-4569-9D89-954604507F3B")) {
            statusLabelUpload->Text = "Upload failed.";
            wizard1->BackEnabled = true;
        } else {
            statusLabelUpload->Text = "Upload complete.";
        }
        uploadPoll->Enabled = false;
    } else {
        ++statusIndex;
        if (statusIndex > 8) statusIndex = 1;
        statusIconUpload->ImageIndex = statusIndex + imageListBase;
    }
}

System::Void UploadDesign::bounceNavigation(System::Object^ sender, 
                          System::Windows::Forms::WebBrowserNavigatingEventArgs^ e)
{
    e->Cancel = true;
    System::Diagnostics::Process::Start(e->Url->AbsoluteUri);
}