// SaveMovie.cpp
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
#include "SaveMovie.h"
#include "Form1.h"

using namespace ContextFreeNet;
using namespace System;
using namespace System::Data;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;

DialogResult SaveMovie::ShowTheDialog(IWin32Window^ owner)
{
    lengthBox->Text = Form1::prefs->AnimateLength.ToString();
    int i = frameRate->FindStringExact(Form1::prefs->AnimateFrameRate.ToString());
    frameRate->SelectedIndex = i < 0 ? 3 : i;
    checkZoom->Checked = Form1::prefs->AnimateZoom;
    DialogResult res = DialogResult::Cancel;

    try {
        res = ShowDialog(owner);
        if (res == DialogResult::OK) {
            Form1::prefs->AnimateZoom = checkZoom->Checked;
            Form1::prefs->AnimateFrameRate = Int32::Parse(frameRate->Text);
            Form1::prefs->AnimateLength = Int32::Parse(lengthBox->Text);
        }
    } catch (Exception^) {
        res = DialogResult::Cancel;
    }

    return res;
}

void SaveMovie::OnPrepareMSDialog()
{
    FileDlgFileName = fileName;
    FileDlgInitialDirectory = fileDir;
    FileDialogExtenders::FileDialogControlBase::OnPrepareMSDialog();
}
