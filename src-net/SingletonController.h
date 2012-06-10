// SingletonController.h
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

#pragma once
#using <System.Runtime.Remoting.Dll>

namespace ContextFreeNet {
    [System::Serializable]
    public ref class SingletonController : public System::MarshalByRefObject
    {

    public: 
        delegate System::Void ReceiveDelegate(array<System::String^>^ args);

    private:
        static System::Runtime::Remoting::Channels::Ipc::IpcChannel^ m_IPCChannel = nullptr;
        static System::Threading::Mutex^ m_Mutex = nullptr;

        static ReceiveDelegate^ m_Receive = nullptr;
    public:

        static property ReceiveDelegate^ Receiver {
            ReceiveDelegate^ get() {
                return m_Receive;
            }
            void set(ReceiveDelegate^ value) {
                m_Receive = value;
            }
        }

        static bool IamFirst(ReceiveDelegate^ r);

        static bool IamFirst();

    private:
        static void CreateInstanceChannel();

    public: 
        static void Cleanup();

        static void Send(array<System::String^>^ s);

        void Receive(array<System::String^>^ s);
    };
}
