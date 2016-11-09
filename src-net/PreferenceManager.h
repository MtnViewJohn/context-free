// PreferenceManager.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2008-2016 John Horigan - john@glyphic.com
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


// PreferenceManager


namespace OzoneUtil {

    public ref class PreferenceManager
    {
    public:
        PreferenceManager(System::String^ keyBase, bool useHKLM)
        {
            if (useHKLM) {
                baseKey = Microsoft::Win32::Registry::LocalMachine->CreateSubKey(keyBase);
            } else {
                baseKey = Microsoft::Win32::Registry::CurrentUser->CreateSubKey(keyBase);
            }
        }

    protected:
        ~PreferenceManager()
        {
            if (baseKey != nullptr) 
                baseKey->Close();
        }

        Microsoft::Win32::RegistryKey^ baseKey;

    public:
        int     GetPrefInt(System::String^ name, int defValue);
        bool    GetPrefBool(System::String^ name, bool defValue);
        double  GetPrefDouble(System::String^ name, double defValue);
        System::String^ GetPrefString(System::String^ name, System::String^ defValue);
        System::String^ GetPrefProtectedString(System::String^ name, array<System::Byte>^ entropy, System::String^ defValue);
		array<System::Byte>^ GetPrefBinary(System::String^ name, array<System::Byte>^ defValue);
        void SetPrefInt(System::String^ name, int value);
        void SetPrefBool(System::String^ name, bool value);
        void SetPrefDouble(System::String^ name, double value);
        void SetPrefString(System::String^ name, System::String^ value);
        void SetPrefProtectedString(System::String^ name, array<System::Byte>^ entropy, System::String^ value);
		void SetPrefBinary(System::String^ name, array<System::Byte>^ defValue);
        void DeletePref(System::String^ name);
    };
}
