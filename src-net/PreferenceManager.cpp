// PreferenceManager.cpp
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

#include "StdAfx.h"
#include "PreferenceManager.h"
#using <System.Security.dll>

using namespace OzoneUtil;
using namespace System;
//using namespace System::IO;
using namespace Microsoft::Win32;
//using namespace System::Runtime::InteropServices;
//using namespace System::ComponentModel;
using namespace System::Collections;
//using namespace System::Windows::Forms;
using namespace System::Security::Cryptography;

int PreferenceManager::GetPrefInt(String^ name, int defValue)
{
    Object^ obj = baseKey->GetValue(name);
    if (obj == nullptr || 
        baseKey->GetValueKind(name) != RegistryValueKind::DWord)
    {
        SetPrefInt(name, defValue);
        return defValue;
    }
    return (int)obj;
}

bool PreferenceManager::GetPrefBool(String^ name, bool defValue)
{
    Object^ obj = baseKey->GetValue(name);
    if (obj == nullptr || 
        baseKey->GetValueKind(name) != RegistryValueKind::DWord)
    {
        SetPrefBool(name, defValue);
        return defValue;
    }
    return (int)obj != 0;
}

double PreferenceManager::GetPrefDouble(String^ name, double defValue)
{
    Object^ obj = baseKey->GetValue(name);
    if (obj == nullptr || 
        baseKey->GetValueKind(name) != RegistryValueKind::String)
    {
        SetPrefDouble(name, defValue);
        return defValue;
    }
    double ret = defValue;
    try { ret = System::Double::Parse((String^) obj); }
    catch (SystemException^) {}
    return ret;
}

String^ PreferenceManager::GetPrefString(String^ name, String^ defValue)
{
    Object^ obj = baseKey->GetValue(name);
    if (obj == nullptr || 
        baseKey->GetValueKind(name) != RegistryValueKind::String)
    {
        if (defValue != nullptr) SetPrefString(name, defValue);
        return defValue;
    }
    return (String^)obj;
}

String^ PreferenceManager::GetPrefProtectedString(String^ name, array<Byte>^ entropy, String^ defValue)
{
    Object^ obj = baseKey->GetValue(name);
    if (obj == nullptr ||
        baseKey->GetValueKind(name) != RegistryValueKind::Binary)
    {
        if (defValue != nullptr) SetPrefProtectedString(name, entropy, defValue);
        return defValue;
    }
    try {
        array<Byte>^ unprotectedblob = ProtectedData::Unprotect((array<System::Byte>^)obj,
            entropy, DataProtectionScope::CurrentUser);
        return System::Text::Encoding::UTF8->GetString(unprotectedblob);
    } catch (Exception^) {
        if (defValue != nullptr) SetPrefProtectedString(name, entropy, defValue);
        return defValue;
    }
}

array<System::Byte>^ PreferenceManager::GetPrefBinary(System::String^ name,
                                                      array<System::Byte>^ defValue)
{
    Object^ obj = baseKey->GetValue(name);
    if (obj == nullptr || 
        baseKey->GetValueKind(name) != RegistryValueKind::Binary)
    {
        if (defValue != nullptr) SetPrefBinary(name, defValue);
        return defValue;
    }
    return (array<System::Byte>^)obj;
}

void PreferenceManager::SetPrefInt(String^ name, int value)
{
    baseKey->SetValue(name, value, RegistryValueKind::DWord);
}

void PreferenceManager::SetPrefBool(String^ name, bool value)
{
    SetPrefInt(name, value ? 1 : 0);
}

void PreferenceManager::SetPrefDouble(String^ name, double value)
{
    baseKey->SetValue(name, value.ToString("R"), RegistryValueKind::String);
}

void PreferenceManager::SetPrefString(String^ name, String^ value)
{
    baseKey->SetValue(name, value, RegistryValueKind::String);
}

void PreferenceManager::SetPrefProtectedString(String^ name, array<Byte>^ entropy, String^ value)
{
    try {
        array<Byte>^ blob = System::Text::Encoding::UTF8->GetBytes(value);
        array<Byte>^ protectedblob = ProtectedData::Protect(blob, entropy,
            DataProtectionScope::CurrentUser);
        baseKey->SetValue(name, protectedblob, RegistryValueKind::Binary);
    } catch (Exception^)
    {}
}

void PreferenceManager::SetPrefBinary(String^ name, array<System::Byte>^ value)
{
    baseKey->SetValue(name, value, RegistryValueKind::Binary);
}

void PreferenceManager::DeletePref(String^ name)
{
    baseKey->DeleteValue(name);
}
