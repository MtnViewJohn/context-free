// SingletonController.cpp
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

#include "StdAfx.h"
#include "SingletonController.h"

using namespace ContextFreeNet;
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Runtime::Remoting;
using namespace System::Runtime::Remoting::Channels;
using namespace System::Runtime::Remoting::Channels::Ipc;
using namespace System::Windows::Forms;

bool SingletonController::IamFirst(ReceiveDelegate^ r)
{
    if (IamFirst()) {
        Receiver += r;
        return true;
    } else {
        return false;
    }
}

bool SingletonController::IamFirst()
{
    String^ m_UniqueIdentifier;
    String^ assemblyName = System::Reflection::Assembly::GetExecutingAssembly()->GetName(false)->CodeBase;
    m_UniqueIdentifier = assemblyName->Replace("\\", "_")->ToLower();

    m_Mutex = gcnew Mutex(false, m_UniqueIdentifier);

    if (m_Mutex->WaitOne(1, true)) {
        //We locked it! We are the first instance!!!    
        CreateInstanceChannel();
        return true;
    } else {
        //Not the first instance!!!
        m_Mutex->Close();
        m_Mutex = nullptr;
        return false;
    }
}

void SingletonController::CreateInstanceChannel()
{
    m_IPCChannel = gcnew IpcChannel("localhost:1234");
    ChannelServices::RegisterChannel(m_IPCChannel, false);
    RemotingConfiguration::RegisterWellKnownServiceType(
        Type::GetType("ContextFreeNet.SingletonController"),
        "SingletonController",
        WellKnownObjectMode::SingleCall);
}

void SingletonController::Cleanup()
{
    if (m_Mutex != nullptr) {
        m_Mutex->Close();
    }

    if (m_IPCChannel != nullptr) {
        m_IPCChannel->StopListening(nullptr);
    }

    m_Mutex = nullptr;
    m_IPCChannel = nullptr;
}

void SingletonController::Send(array<String^>^ s)
{
    SingletonController^ ctrl;
    IpcChannel^ channel = gcnew IpcChannel();
    ChannelServices::RegisterChannel(channel, false);
    try {
        ctrl = (SingletonController^)Activator::GetObject(SingletonController::typeid, "ipc://localhost:1234/SingletonController");
    } catch (Exception^ e) {
        Console::WriteLine("Exception: " + e->Message);
        throw;
    }
    ctrl->Receive(s);
}

void SingletonController::Receive(array<String^>^ s)
{
    if (m_Receive != nullptr) {
        array<Delegate^>^ recvrs = m_Receive->GetInvocationList();
        array<Object^>^ args = { s };
        for each (Delegate^ dlgt in recvrs) {
            ReceiveDelegate^ rcvr = cli::safe_cast<ReceiveDelegate^>(dlgt);
            try {
                Control^ ctrl = cli::safe_cast<Control^>(rcvr->Target);
                ctrl->BeginInvoke(rcvr, args);
            } catch (Exception^) {
                rcvr(s);
            }
        }
    }
}
