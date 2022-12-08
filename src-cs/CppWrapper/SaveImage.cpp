#include "pch.h"
#include "SaveImage.h"

using namespace CppWrapper;
using namespace System;
using namespace System::Data;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;

DialogResult SaveImage::ShowTheDialog(IWin32Window^ owner, UploadPrefs^ prefs)
{
    checkCropImage->Checked = prefs->ImageCrop;
    JPEGQuality->Text = prefs->JPEGQuality.ToString();
    if (saveWidth->Enabled) saveWidth->Text = prefs->OutputMultiplier[0].ToString();
    if (saveHeight->Enabled) saveHeight->Text = prefs->OutputMultiplier[1].ToString();
    DialogResult res = DialogResult::Cancel;

    try {
        res = ShowDialog(owner);
        if (res == DialogResult::OK) {
            prefs->ImageCrop = checkCropImage->Checked;
            prefs->JPEGQuality = double::Parse(JPEGQuality->Text);
            if (saveWidth->Enabled) prefs->OutputMultiplier[0] = double::Parse(saveWidth->Text);
            if (saveHeight->Enabled) prefs->OutputMultiplier[1] = double::Parse(saveHeight->Text);
        }
    }
    catch (Exception^) {
        res = DialogResult::Cancel;
        System::Media::SystemSounds::Beep->Play();
    }

    return res;
}

void SaveImage::OnPrepareMSDialog()
{
    FileDlgFileName = fileName;
    FileDlgInitialDirectory = fileDir;
    FileDialogExtenders::FileDialogControlBase::OnPrepareMSDialog();
}

System::Void SaveImage::fileTypeChanged(System::Windows::Forms::IWin32Window^ sender, System::Int32 index)
{
    JPEGQuality->Enabled = index == 2;
    JPEGlabel->ForeColor = (index == 2) ? SystemColors::ControlText : SystemColors::GrayText;
}
