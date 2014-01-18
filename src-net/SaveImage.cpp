// SaveImage.cpp
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
#include "SaveImage.h"
#include "Form1.h"

using namespace ContextFreeNet;
using namespace System;
using namespace System::Data;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;

DialogResult SaveImage::ShowTheDialog(IWin32Window^ owner)
{
    checkCropImage->Checked = Form1::prefs->ImageCrop;
    JPEGQuality->Text = Form1::prefs->JPEGQuality.ToString();
    DialogResult res = DialogResult::Cancel;

    try {
        res = ShowDialog(owner);
        if (res == DialogResult::OK) {
            Form1::prefs->ImageCrop = checkCropImage->Checked;
            Form1::prefs->JPEGQuality = System::Int32::Parse(JPEGQuality->Text);
            if (multiplier) {
                multiplier[0] = System::Double::Parse(saveWidth->Text);
                multiplier[1] = System::Double::Parse(saveHeight->Text);
            }
        }
    } catch (Exception^) {
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