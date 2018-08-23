// CFApp.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2018 John Horigan - john@glyphic.com
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

#pragma once

#include "Form1.h"

public ref class CFApp : Microsoft::VisualBasic::ApplicationServices::WindowsFormsApplicationBase
{
public:
    CFApp()
    {
        this->EnableVisualStyles = true;
        this->IsSingleInstance = true;
        this->ShutdownStyle = Microsoft::VisualBasic::ApplicationServices::ShutdownMode::AfterMainFormCloses;
        this->StartupNextInstance += gcnew Microsoft::VisualBasic::ApplicationServices::StartupNextInstanceEventHandler(this, &CFApp::SIApp_StartupNextInstance);
    }

protected:
    virtual void OnCreateMainForm() override
    {
        array<System::String^>^ args = gcnew array<System::String^>(this->CommandLineArgs->Count);
        this->CommandLineArgs->CopyTo(args, 0);
        this->MainForm = gcnew ContextFreeNet::Form1(args);
    }

    void SIApp_StartupNextInstance(Object^ sender, Microsoft::VisualBasic::ApplicationServices::StartupNextInstanceEventArgs^ eventArgs)
    {
        array<System::String^>^ args = gcnew array<System::String^>(eventArgs->CommandLine->Count);
        eventArgs->CommandLine->CopyTo(args, 0);

        ContextFreeNet::Form1^ f1 = (ContextFreeNet::Form1^)this->MainForm;

        ContextFreeNet::Form1::ProcessParametersDelegate^ d = gcnew ContextFreeNet::Form1::ProcessParametersDelegate(f1, &ContextFreeNet::Form1::processArgs);
        f1->Invoke(d, gcnew array<System::Object^> { args });
    }
};