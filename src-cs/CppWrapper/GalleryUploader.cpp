// GalleryUploader.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2022 John Horigan - john@glyphic.com
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


#include "pch.h"
#include "GalleryUploader.h"
#include "variation.h"
#include <string>
#include <string.h>
#include "upload.h"
#include <sstream>

using namespace System;
using namespace System::IO;
using namespace System::Data;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;
using namespace System::Net;
using namespace System::Diagnostics;

#define UseProductionServer 1

namespace {
    struct iccomp {
        bool operator()(const std::string& a, const std::string& b)
        {
            return  _stricmp(a.c_str(), b.c_str()) < 0;
        }
    };
}

namespace CppWrapper {
    void GalleryUploader::MoreInitialzation(CFDG::frieze_t fr, int tiled, bool png)
    {
        origUsername = uploadPrefs->Username;
        username->Text = origUsername;
        if (System::String^ pword = uploadPrefs->Password) {
            origPassword = pword;
            password->Text = pword;
        }
        else {
            origPassword = "";
        }
        std::string vChars = Variation::toString(uploadPrefs->Variation, false);
        variation->Text = gcnew System::String(vChars.c_str());
        crop->Checked = uploadPrefs->ImageCrop && !tiled;
        crop->Visible = tiled == 0;
        if (png)
            radioPNG8->Checked = true;
        else
            radioJPEG->Checked = true;
        if (tiled || fr != CFDG::no_frieze) {
            if (fr == CFDG::frieze_x)
                uploadPrefs->OutputMultiplier[0] = 1.0;
            if (fr == CFDG::frieze_y)
                uploadPrefs->OutputMultiplier[1] = 1.0;
            crop->Visible = false;
            multwidth->Value = static_cast<int>(uploadPrefs->OutputMultiplier[0]);
            multheight->Value = static_cast<int>(uploadPrefs->OutputMultiplier[1]);
            multwidth->Enabled = fr != CFDG::frieze_y;
            multheight->Enabled = fr != CFDG::frieze_x;
        }
        else {
            multwidth->Visible = false;
            multheight->Visible = false;
            multlabel1->Visible = false;
            multlabel2->Visible = false;
            multlabel3->Visible = false;
        }
        this->uptiled->Checked = tiled != 0;
        this->uptiled->Visible = tiled != 0;
        filename->Text = uploadPrefs->CfdgName;
        title->Text = Globalization::CultureInfo::CurrentCulture->TextInfo->ToTitleCase(filename->Text->ToLower());

        System::ComponentModel::ComponentResourceManager^ resources = (gcnew
            System::ComponentModel::ComponentResourceManager(GalleryUploader::typeid));
        copyrightSymbol = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"copyright")));
        cc_change->SelectedIndex = 0;   // Load license info from the preferences

        addTag->Click += gcnew EventHandler(this, &GalleryUploader::tag_click);
        tagBox->GotFocus += gcnew EventHandler(this, &GalleryUploader::tag_focus);
        tagsList->SelectedIndexChanged += gcnew EventHandler(this, &GalleryUploader::tag_select);
        tagBox->PreviewKeyDown += gcnew PreviewKeyDownEventHandler(this, &GalleryUploader::tag_previewkey);
        tagBox->KeyPress += gcnew KeyPressEventHandler(this, &GalleryUploader::tag_keypress);
        tagBox->KeyDown += gcnew KeyEventHandler(this, &GalleryUploader::tag_keydown);

        addTag->ImageIndex = 0;
        ignore_next_selection = false;

        WebClient^ req = gcnew WebClient();
        req->DownloadDataCompleted += gcnew DownloadDataCompletedEventHandler(this, &GalleryUploader::OnTags);
        req->DownloadDataAsync(gcnew Uri(
#ifdef UseProductionServer
            "https://www.contextfreeart.org/gallery/tags.php?t=tags"
#else
            "http://localmac//~john/cfa2/gallery/tags.php?t=tags"
#endif
        ));

        uploadThread = gcnew BackgroundWorker();
        uploadThread->WorkerSupportsCancellation = true;
        uploadThread->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler(this, &GalleryUploader::UploadCompleted);
        uploadThread->DoWork += gcnew DoWorkEventHandler(this, &GalleryUploader::RunUploadThread);
    }

    void GalleryUploader::OnShown(System::Object^ sender, System::EventArgs^ e)
    {
        this->title->Focus();
    }

    void GalleryUploader::OnTags(System::Object^ sender, System::Net::DownloadDataCompletedEventArgs^ e)
    {
        if (e->Error || e->Cancelled) {
            tagBox->AutoCompleteMode = AutoCompleteMode::None;
            return;
        }

        pin_ptr<Byte> utf8arraypin = &e->Result[0];
        auto tagvector = Upload::AllTags(reinterpret_cast<const char*>(utf8arraypin), e->Result->Length);

        if (tagvector.empty()) {
            tagBox->AutoCompleteMode = AutoCompleteMode::None;
            return;
        }

        std::sort(tagvector.begin(), tagvector.end(), iccomp());

        AutoCompleteStringCollection^ tagC = gcnew AutoCompleteStringCollection();
        for (auto&& tag : tagvector)
            tagC->Add(gcnew String(tag.c_str(), 0, static_cast<int>(tag.length()), System::Text::Encoding::UTF8));

        tagBox->AutoCompleteMode = AutoCompleteMode::Suggest;
        tagBox->AutoCompleteSource = AutoCompleteSource::CustomSource;
        tagBox->AutoCompleteCustomSource = tagC;
    }

    void GalleryUploader::tag_click(System::Object^ sender, System::EventArgs^ e)
    {
        if (addTag->ImageIndex == 0) {
            String^ newTag = tagBox->Text->Trim();
            if (newTag->Length == 0)
                return;

            tagBox->Text = String::Empty;

            for each (Object ^ otag in tagsList->Items)
                if (String^ tag = dynamic_cast<String^>(otag))
                    if (tag->Equals(newTag))
                        return;

            ignore_next_selection = true;
            tagsList->SelectedIndex = tagsList->Items->Add(newTag);
        }
        else {
            auto i = tagsList->SelectedIndex;
            if (i >= 0) {
                tagsList->Items->RemoveAt(i);
                addTag->ImageIndex = 0;
            }
        }
    }

    void GalleryUploader::tag_focus(System::Object^ sender, System::EventArgs^ e)
    {
        addTag->ImageIndex = 0;
        toolTip1->SetToolTip(addTag, "Save tag to tag list");
    }

    void GalleryUploader::tag_select(System::Object^ sender, System::EventArgs^ e)
    {
        if (ignore_next_selection) {
            ignore_next_selection = false;
        }
        else {
            addTag->ImageIndex = 1;
            toolTip1->SetToolTip(addTag, "Delete tag from tag list");
        }
    }

    void GalleryUploader::tag_previewkey(System::Object^ sender, System::Windows::Forms::PreviewKeyDownEventArgs^ e)
    {
        if (e->KeyCode == Keys::Return || e->KeyCode == Keys::Tab)
            e->IsInputKey = true;
    }

    void GalleryUploader::tag_keypress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
    {
        if (e->KeyChar == (char)13 || e->KeyChar == ' ') {
            e->Handled = true;
        }
    }

    void GalleryUploader::tag_keydown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
    {
        if (e->KeyCode == Keys::Return || e->KeyCode == Keys::Tab || e->KeyCode == Keys::Space) {
            addTag->PerformClick();
            e->Handled = true;
        }
    }

    void GalleryUploader::LaunchUrl(String^ url)
    {
        auto psi = gcnew ProcessStartInfo("cmd", "/c start " + url);
        psi->CreateNoWindow = true;

        Process::Start(psi);
    }

    System::Void GalleryUploader::needaccount_Click(System::Object^ sender, System::EventArgs^ e) {
        LaunchUrl("https://www.contextfreeart.org/phpbb/ucp.php?mode=register");
    }

    System::Void GalleryUploader::navLicense(System::Object^ sender, System::EventArgs^ e) {
        if (ccurl->Length > 0)
            LaunchUrl(ccurl);
    }

    System::Void GalleryUploader::cancel_click(System::Object^ sender, System::EventArgs^ e) {
        if (uploadThread->IsBusy) {
            uploadThread->CancelAsync();
            return;
        }
        if (design_id == 0) {
            this->DialogResult = ::DialogResult::Cancel;
        }
        else {
#ifdef UseProductionServer
            String^ url = String::Format("https://www.contextfreeart.org/gallery/view.php?id={0}", design_id);
#else
            String^ url = String::Format("http://localmac//~john/cfa2/gallery/view.php?id={0}", design_id);
#endif
            LaunchUrl(url);
            this->DialogResult = ::DialogResult::OK;
        }
    }

    System::Void GalleryUploader::upload_click(System::Object^ sender, System::EventArgs^ e) {
        if (design_id != 0) {
            this->DialogResult = design_id > 0 ? ::DialogResult::OK : ::DialogResult::Cancel;
            return;
        }

        if (password->TextLength == 0 || username->TextLength == 0) {
            message->Text = "A username and password is required.";
            System::Media::SystemSounds::Beep->Play();
            return;
        }
        if (title->TextLength < 3 || title->TextLength > 30) {
            message->Text = "The title must be between 3 and 30 characters.";
            System::Media::SystemSounds::Beep->Play();
            return;
        }
        if (filename->TextLength == 0) {
            message->Text = "A filename must be provided.";
            System::Media::SystemSounds::Beep->Play();
            return;
        }

        if (tagBox->Text->Length > 0)
            addTag->PerformClick();

        if (!origUsername->Equals(username->Text))
            uploadPrefs->Username = username->Text;
        if (!origPassword->Equals(password->Text))
            uploadPrefs->Password = password->Text;

        uploadPrefs->OutputMultiplier[0] = Convert::ToDouble(multwidth->Value);
        uploadPrefs->OutputMultiplier[1] = Convert::ToDouble(multheight->Value);

        if (crop->Visible)
            uploadPrefs->ImageCrop = crop->Checked;

        uploadPrefs->Updated = true;

        Upload upload;
        System::Text::Encoding^ encodeutf8 = System::Text::Encoding::UTF8;

        array<Byte>^ utf8array = encodeutf8->GetBytes(username->Text);
        pin_ptr<Byte> utf8arraypin = &utf8array[0];
        upload.mUserName = reinterpret_cast<const char*>(utf8arraypin);

        utf8array = encodeutf8->GetBytes(password->Text);
        utf8arraypin = &utf8array[0];
        upload.mPassword = reinterpret_cast<const char*>(utf8arraypin);

        utf8array = encodeutf8->GetBytes(title->Text);
        utf8arraypin = &utf8array[0];
        upload.mTitle = reinterpret_cast<const char*>(utf8arraypin);

        if (notes->Text->Length > 0) {
            utf8array = encodeutf8->GetBytes(notes->Text);
            utf8arraypin = &utf8array[0];
            upload.mNotes = reinterpret_cast<const char*>(utf8arraypin);
        }

        if (auto count = tagsList->Items->Count) {
            array<String^>^ tagarray = gcnew array<String^>(count);
            for (int i = 0; i < count; ++i)
                if (String^ tag = dynamic_cast<String^>(tagsList->Items[i]))
                    tagarray[i] = tag;
            String^ tags = String::Join(" ", tagarray);
            utf8array = encodeutf8->GetBytes(tags);
            utf8arraypin = &utf8array[0];
            upload.mTags = reinterpret_cast<const char*>(utf8arraypin);
        }

        utf8array = encodeutf8->GetBytes(filename->Text + ".cfdg");
        utf8arraypin = &utf8array[0];
        upload.mFileName = reinterpret_cast<const char*>(utf8arraypin);

        upload.mVariation = uploadPrefs->Variation;
        upload.mCompression = radioJPEG->Checked ? Upload::CompressJPEG : Upload::CompressPNG8;
        upload.mTiled = uptiled->Checked;

        if (cc_changed) {
            uploadPrefs->ccLicense = ccurl;
            uploadPrefs->ccImage = ccimageurl;
            uploadPrefs->ccName = ccname->Text;
        }

        utf8array = encodeutf8->GetBytes(uploadPrefs->ccLicense);
        if (utf8array->Length) {
            utf8arraypin = &utf8array[0];
            upload.mccLicenseURI = reinterpret_cast<const char*>(utf8arraypin);
        }

        utf8array = encodeutf8->GetBytes(uploadPrefs->ccName);
        if (utf8array->Length) {
            utf8arraypin = &utf8array[0];
            upload.mccLicenseName = reinterpret_cast<const char*>(utf8arraypin);
        }

        utf8array = encodeutf8->GetBytes(uploadPrefs->ccImage);
        if (utf8array->Length) {
            utf8arraypin = &utf8array[0];
            upload.mccLicenseImage = reinterpret_cast<const char*>(utf8arraypin);
        }

        array<Byte>^ encodedCfdg = System::Text::Encoding::UTF8->GetBytes(uploadPrefs->CfdgText);
        pin_ptr<Byte> pinnedCfdg = &encodedCfdg[0];

        upload.mText = reinterpret_cast<const char*>(pinnedCfdg);
        upload.mTextLen = std::strlen(reinterpret_cast<const char*>(pinnedCfdg));

        utf8arraypin = nullptr;

        array<Byte>^ imageDataArray = bitmapStream->GetBuffer();
        pin_ptr<Byte> imageData = &imageDataArray[0];
        upload.mImage = reinterpret_cast<const char*>(imageData);
        upload.mImageLen = imageDataArray->Length;

        std::ostringstream design;
        upload.generatePayload(design);

        imageData = nullptr;

        std::string designstr = design.str();
        array<Byte>^ postbody = gcnew array<Byte>(static_cast<int>(designstr.length()));
        Marshal::Copy(static_cast<System::IntPtr>(&designstr[0]),
            postbody, 0, static_cast<int>(design.str().length()));
        uploadThread->RunWorkerAsync(postbody);
        this->upload->Enabled = false;
        message->Visible = false;
        uploadProgress->Visible = true;
    }

    void GalleryUploader::RunUploadThread(Object^ sender, DoWorkEventArgs^ e)
    {
        array<Byte>^ postbody = dynamic_cast<array<Byte>^>(e->Argument);
        BackgroundWorker^ bw = dynamic_cast<BackgroundWorker^>(sender);
        if (postbody == nullptr || bw == nullptr) {
            e->Cancel = true;
            e->Result = (Object^)0;
            return;
        }
        String^ header = gcnew String(Upload::generateContentType().c_str());

        auto len = postbody->Length;

        HttpWebRequest^ req = dynamic_cast<HttpWebRequest^>(WebRequest::Create(
#ifdef UseProductionServer
            "https://www.contextfreeart.org/gallery/upload.php"
#else
            "http://localmac//~john/cfa2/gallery/upload.php"
#endif
        ));
        req->Method = "POST";
        req->ContentType = header;
        req->ContentLength = len;
        req->ProtocolVersion = HttpVersion::Version11;
        req->KeepAlive = false;
        ServicePointManager::SecurityProtocol = SecurityProtocolType::Tls11 | SecurityProtocolType::Tls12;

        try {
            Stream^ newStream = req->GetRequestStream();
            newStream->Write(postbody, 0, len);
            newStream->Close();
        }
        catch (Exception^) {
            String^ msg = "A network error occured.";
            e->Result = msg;
            return;
        }

        if (bw->CancellationPending) {
            e->Cancel = true;
            return;
        }

        try {
            HttpWebResponse^ resp = dynamic_cast<HttpWebResponse^>(req->GetResponse());
            String^ respbody = nullptr;
            {
                StreamReader reader(resp->GetResponseStream());
                respbody = reader.ReadToEnd();
            }

            if (bw->CancellationPending) {
                e->Cancel = true;
                return;
            }

            System::Text::Encoding^ encodeutf8 = System::Text::Encoding::UTF8;
            array<Byte>^ utf8array = encodeutf8->GetBytes(respbody);
            pin_ptr<Byte> utf8arraypin = &utf8array[0];

            Upload upload(reinterpret_cast<const char*>(utf8arraypin), utf8array->Length);
            e->Result = upload.mId;
        }
        catch (WebException^ we) {
            HttpWebResponse^ resp = dynamic_cast<HttpWebResponse^>(we->Response);
            String^ respbody = nullptr;
            if (Stream^ respStream = resp ? resp->GetResponseStream() : nullptr) {
                StreamReader reader(respStream);
                respbody = reader.ReadToEnd();
            }
            else {
                respbody = "";
            }
            int pstart = respbody ? respbody->IndexOf("<p>") : -1;
            int pend = pstart >= 0 ? respbody->IndexOf("</p>", pstart) : -1;
            if (pstart >= 0 && pend >= 0) {
                e->Result = respbody->Substring(pstart + 3, pend - (pstart + 3));
            }
            else {
                String^ msg = "The gallery rejected the upload.";
                e->Result = msg;
            }
        }
        catch (Exception^) {
            String^ msg = "An error occurred during the upload.";
            e->Result = msg;
        }
    }

    void GalleryUploader::UploadCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e)
    {
        message->Visible = true;
        uploadProgress->Visible = false;
        if (e->Cancelled) {
            this->DialogResult = ::DialogResult::Cancel;
            return;
        }
        String^ msg = dynamic_cast<String^>(e->Result);
        if (msg) {
            message->Text = msg;
        }
        else {
            try {
                design_id = safe_cast<unsigned>(e->Result);
            }
            catch (Exception^) {
                message->Text = "An error occurred during the upload.";
            }
        }

        if (design_id > 0) {
            message->Text = "Upload completed. Click View to see design in gallery.";
            cancel->Text = "View";
            upload->Text = "Done";
            upload->Enabled = true;
        }
        else if (!msg) {
            message->Text = "An unknown error occurred.";
            System::Media::SystemSounds::Beep->Play();
            upload->Text = "Done";
            upload->Enabled = false;
        }
        else {
            System::Media::SystemSounds::Beep->Play();
            upload->Text = "Retry";
            upload->Enabled = true;
        }
    }

    System::Void GalleryUploader::cc_change_select(System::Object^ sender, System::EventArgs^ e) {
        String^ url = "";
        String^ icon = "";
        String^ name = "No license chosen";
        cc_changed = true;
        switch (cc_change->SelectedIndex) {
        case 0:
            url = uploadPrefs->ccLicense;
            icon = uploadPrefs->ccImage;
            name = uploadPrefs->ccName;
            cc_changed = false;
            break;
        case 1:
            url = "https://creativecommons.org/publicdomain/zero/1.0/";
            icon = "https://licensebuttons.net/p/zero/1.0/88x31.png";
            name = "CC0 1.0 Universal (CC0 1.0) Public Domain Dedication";
            break;
        case 2:
            url = "https://creativecommons.org/licenses/by/4.0/";
            icon = "https://licensebuttons.net/l/by/4.0/88x31.png";
            name = "Creative Commons Attribution 4.0 International";
            break;
        case 3:
            url = "https://creativecommons.org/licenses/by-sa/4.0/";
            icon = "https://licensebuttons.net/l/by-sa/4.0/88x31.png";
            name = "Creative Commons Attribution-ShareAlike 4.0 International";
            break;
        case 4:
            url = "https://creativecommons.org/licenses/by-nd/4.0/";
            icon = "https://licensebuttons.net/l/by-nd/4.0/88x31.png";
            name = "Creative Commons Attribution-NoDerivatives 4.0 International";
            break;
        case 5:
            url = "https://creativecommons.org/licenses/by-nc/4.0/";
            icon = "https://licensebuttons.net/l/by-nc/4.0/88x31.png";
            name = "Creative Commons Attribution-NonCommercial 4.0 International";
            break;
        case 6:
            url = "https://creativecommons.org/licenses/by-nc-sa/4.0/";
            icon = "https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png";
            name = "Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International";
            break;
        case 7:
            url = "https://creativecommons.org/licenses/by-nc-nd/4.0/";
            icon = "https://licensebuttons.net/l/by-nc-nd/4.0/88x31.png";
            name = "Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International";
            break;
        default:
            break;
        }
        ccname->Text = name;
        if (icon->Length > 0) {
            try {
                ccicon->Load(icon);
            }
            catch (Exception^) {}
        }
        else {
            ccicon->Image = copyrightSymbol;
        }
        ccimageurl = icon;
        ccurl = url;
        if (ccurl->Length > 0)
            ccicon->Cursor = Cursors::Hand;
        else
            ccicon->Cursor = Cursors::Default;
    }
}