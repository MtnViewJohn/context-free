// ContextFreeNet.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2008 John Horigan - john@glyphic.com
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


#include "stdafx.h"
#include "Form1.h"
#include "SingletonController.h"

using namespace ContextFreeNet;
using namespace System;
using namespace System::Windows::Forms;

[System::STAThreadAttribute]
int main(array<System::String ^> ^args)
{
    // Enabling Windows XP visual effects before any controls are created
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false); 

    // Create the main window and run it
    if (SingletonController::IamFirst()) {
        Form1^ mainApp = gcnew Form1(args);
        SingletonController::Receiver += gcnew SingletonController::ReceiveDelegate(mainApp, &Form1::processArgs);
        Application::Run(mainApp);
    } else {
        SingletonController::Send(args);
    }
    SingletonController::Cleanup();
    return 0;
}

int __stdcall WinMain(int hInstance, int hPrevInstance, char *lpCmdLine, int nShowCmd)
{
    return main(Environment::GetCommandLineArgs());
}
