// SaveImage.cpp
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
