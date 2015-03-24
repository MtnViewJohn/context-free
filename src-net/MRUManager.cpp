// MRUManager.cpp
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

#include "stdafx.h"
#include "MRUManager.h"

using namespace OzoneUtil;
using namespace System;
using namespace System::IO;
using namespace Microsoft::Win32;
using namespace System::Runtime::InteropServices;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;

void MRUManager::Initialize(Form^ owner, EventHandler^ handler, 
                            ToolStripItem^ mruItem, String^ regPath)
{
    ownerForm = owner;
    clickHandler = handler;

    menuItemMRU = mruItem;

    isInlineList = mruItem->GetType() == lowerSeparator->GetType();

    menuItemParent = dynamic_cast<ToolStripMenuItem^>(mruItem->OwnerItem);
    if (menuItemParent == nullptr) {
        throw gcnew Exception("MRUManager: Cannot find parent of MRU menu item");
    }

    // keep Registry path adding MRU key to it
    registryPath = regPath;
    if (registryPath->EndsWith("\\") )
        registryPath += "MRU";
    else
        registryPath += "\\MRU";

    // keep current directory in the time of initialization
    currentDirectory = Directory::GetCurrentDirectory();

    if (!isInlineList) {
        // subscribe to MRU parent Popup event
        menuItemParent->DropDownOpened += 
            gcnew System::EventHandler(this, &MRUManager::OnMRUParentPopup);
    }

    // subscribe to owner form Closing event
    ownerForm->Closing += gcnew 
        System::ComponentModel::CancelEventHandler(this, 
        &MRUManager::OnOwnerClosing);

    // load MRU list from Registry
    LoadMRU();

    // Update the menu with the MRU list (is MRU list is inline)
    UpdateMenu();
}

// Add a file to the MRU list. If the file is already in the list then
// it is moved to the first entry. 
void MRUManager::Add(String^ file)
{
    Remove(file, false);

    // if array has maximum length, remove last element
    while ( mruList.Count >= maxNumberOfFiles )
        mruList.RemoveAt(maxNumberOfFiles - 1);

    // add new file name to the start of array
    mruList.Insert(0, file);

    // update currentDirectory if autoDirectory
    if (autoDirectory)
        currentDirectory = Path::GetDirectoryName(file);

    UpdateMenu();
}

// Remove a file from the list if it is in the list.
void MRUManager::Remove(String^ file, bool update)
{
    IEnumerator^ myEnumerator = mruList.GetEnumerator();

    for (int i = 0; myEnumerator->MoveNext(); ++i) {
        if ((String^)myEnumerator->Current == file ) {
            mruList.RemoveAt(i);
            if (update) UpdateMenu();
            return;
        }
    }
}

// If the MRU list is inline then update the parent menu with the current MRU list.
void MRUManager::UpdateMenu()
{
    if (!isInlineList) return;
    if (inlineListIsEmpty && mruList.Count == 0) return;

    ToolStripItemCollection^ allItems = menuItemParent->DropDownItems;
    int start = allItems->IndexOf(menuItemMRU);

    if (!inlineListIsEmpty) {
        int end = allItems->IndexOf(lowerSeparator);

        if (start == -1 || end == -1 || start > end) {
            System::Diagnostics::Trace::WriteLine("Error while updating inline menu list.");
            return;
        }

        for (; end > start; --end) {
            allItems->RemoveAt(end);
        }

        inlineListIsEmpty = true;
    }

    if (mruList.Count > 0) {
        // We know at this point that there is no MRU list or lower ToolStripSeparatorItem
        // in the parent menu
        int end = start + 1;
        allItems->Insert(end, lowerSeparator);

        for each (String^ mruItem in mruList) {
            ToolStripMenuItem^ item = 
                gcnew ToolStripMenuItem(GetDisplayName(mruItem, end - start));

            // save the full path in the item's tag
            item->Tag = mruItem;

            // subscribe to item's Click event
            item->Click += clickHandler;

            // insert above the lower separator
            allItems->Insert(end++, item);
        }

        inlineListIsEmpty = false;
    }
}

// If the MRU list in a popup list (i.e., not inline) then regenerate it every time the 
// parent menu pops up.
System::Void MRUManager::OnMRUParentPopup(System::Object^ sender, System::EventArgs^ e)
{
    ToolStripMenuItem^ popupMenu = cli::safe_cast<ToolStripMenuItem^>(menuItemMRU);

    // remove all children
    if (popupMenu->HasDropDownItems) {
        popupMenu->DropDownItems->Clear();
    }

    // Disable menu item if MRU list is empty
    if (mruList.Count == 0) {
        popupMenu->Enabled = false;
        return;
    }

    // enable menu item and add child items
    popupMenu->Enabled = true;

    int i = 1;

    for each (String^ mruItem in mruList) {
        ToolStripMenuItem^ item = 
            gcnew ToolStripMenuItem(GetDisplayName(mruItem, i++));

        // save the full path in the item's tag
        item->Tag = mruItem;

        // subscribe to item's Click event
        item->Click += clickHandler;

        popupMenu->DropDownItems->Add(item);
    }
}

// This is a public utility method that the MRU item click handler in the owner 
// form uses to find out the filename associated with the MRU click event that 
// it received.
//
// This method has the side-effect of moving the item that was the source of the
// event to the first entry in the MRU list.
String^ MRUManager::OnMRUClicked(System::Object^ sender, System::EventArgs^ e)
{
    try {
        // cast sender object to ToolStripMenuItem
        ToolStripMenuItem^ item = cli::safe_cast<ToolStripMenuItem^>(sender);

        if (item != nullptr) {
            // get the full path from the menu item's tag property
            String^ s = cli::safe_cast<String^>(item->Tag);

            // return it if it exists
            if (s != nullptr && s->Length > 0 ) {
                Add(s);
                return s;
            }
        }
    } catch (Exception^ ex) {
        System::Diagnostics::Trace::WriteLine("Exception in OnMRUClicked: " + ex->Message);
    }

    return String::Empty;
}

// Save the MRU list to the registry when the parent form closes.
System::Void MRUManager::OnOwnerClosing(System::Object^ sender, 
                                        System::ComponentModel::CancelEventArgs^ e)
{
    Int32 i, n;

    try {
        RegistryKey^ key = Registry::CurrentUser->CreateSubKey(registryPath);

        if (key != nullptr) {
            array<String^>^ valueNames = key->GetValueNames();
            for each (String^ name in valueNames) {
                if (name != String::Empty)
                    key->DeleteValue(name, false);
            }

            n = mruList.Count;
            for (i = 0; i < n; ++i) {
				key->SetValue(String::Concat(regEntryName, i), mruList[i]);
            }

            key->SetValue(nullptr, currentDirectory);
            key->Close();
        }
    } catch (Exception^ ex) {
        System::Diagnostics::Trace::WriteLine("Saving MRU to Registry failed: " + ex->Message);
    }
}

// Private utility method that loads the MRU list from the registry
void MRUManager::LoadMRU()
{
    String^ sKey;
    String^ s;

    try {
        mruList.Clear();

        RegistryKey^ key = Registry::CurrentUser->OpenSubKey(registryPath);

        if (key != nullptr) {
			for (Int32 i = 0; i < maxNumberOfFiles; ++i) {
                sKey = String::Concat(regEntryName, i);

                s = (String^)key->GetValue(sKey, String::Empty);

                if (s->Length == 0)
                    break;

                mruList.Add(s);
            }

            s = (String^)key->GetValue("", String::Empty);
            if (s != String::Empty) currentDirectory = s;

            key->Close();
        }
    } catch (Exception^ ex) {
        System::Diagnostics::Trace::WriteLine("Loading MRU from Registry failed: " + ex->Message);
    }
}

// Private utility method that determines the display name to give to the MRU menu
// item key.
String^ MRUManager::GetDisplayName(String^ fullName, int index)
{
    // if file is in current directory, show only file name
    FileInfo^ fileInfo = gcnew FileInfo(fullName);

    // Create the keyboard shortcut
    String^ shortcut = "&" + index.ToString() + " ";
    if (index == 10) shortcut = "1&0 ";

    if (fileInfo->DirectoryName == currentDirectory)
        return shortcut + GetShortDisplayName(fileInfo->Name, maxDisplayLength);

    if (fileInfo->DirectoryName->StartsWith(currentDirectory)) {
        return shortcut + GetShortDisplayName(fullName->Substring(currentDirectory->Length + 1), 
                                   maxDisplayLength);
    }

    return shortcut + GetShortDisplayName(fullName, maxDisplayLength);
}


// BOOL PathCompactPathEx(          
//    LPTSTR pszOut,
//    LPCTSTR pszSrc,
//    UINT cchMax,
//    DWORD dwFlags
//    );
[DllImport("shlwapi.dll", CharSet = CharSet::Auto)]    
extern "C" bool PathCompactPathEx(
    System::Text::StringBuilder^ pszOut, 
    String^ pszPath,
    int cchMax, 
    int reserved); 

// Private utility wrapper for Win32 PathCompactPathEx, a very useful function
String^ MRUManager::GetShortDisplayName(String^ fullName, int maxLen)
{
    System::Text::StringBuilder^ pszOut = gcnew System::Text::StringBuilder(maxLen + maxLen + 2);  // for safety

    if (PathCompactPathEx(pszOut, fullName, maxLen, 0)) {
        return pszOut->ToString();
    } else {
        return fullName;
    }
}


