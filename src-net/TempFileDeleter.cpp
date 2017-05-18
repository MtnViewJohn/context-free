// TempFileDeleter.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2017 John Horigan - john@glyphic.com
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
#include "TempFileDeleter.h"
#include "tempfile.h"

TempFileDeleter::TempFileDeleter(tempfile_ptr file, System::Diagnostics::Process^ viewer)
    : mTempFile(nullptr), mViewer(viewer)
{
    if (viewer && !viewer->HasExited && file && file->written()) {
        mTempFile = gcnew System::String(file->name().c_str());
        file->release();    // this object owns the file now
        TempFiles->Add(this);
        viewer->Exited += gcnew System::EventHandler(this, &TempFileDeleter::DeleteIt);
    }
    if (viewer && !viewer->HasExited)
        viewer->CloseMainWindow();
    // tempfile_ptr file goes out of scope and is deleted, temp file is deleted
    // too unless this object takes over ownership of the file
}

void
TempFileDeleter::DeleteIt(Object^ sender, System::EventArgs^ e)
{
    try {
        System::IO::File::Delete(mTempFile);
        System::Diagnostics::Debugger::Log(3, "Delete success: ", mTempFile);
    } catch (System::Exception^) {
        System::Diagnostics::Debugger::Log(1, "Delete failed: ", mTempFile);
    }
    mViewer = nullptr;
    TempFiles->Remove(this);
}
