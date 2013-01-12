// MRUManager.h
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

#pragma once


// MRU list manager.
//
// Written by: John Horigan <john@glyphic.com>
// in Managed C++ targeting the .NET 2.0 framework
// and the ToolStripMenuItem class therein
//
// based on a MRU list manager
// Written by: Alex Farber <alexm@cmt.co.il>
// in C#, targeting .NET 1.1 framework

/*******************************************************************************

How to use it:

1) Add menu item Recent Files (or any name you want) to a main application menu.
   This item is used by MRUManager as popup menu for MRU list.

   -- OR --

   Add a menu item separator to a main application menu. This is used by MRUManager
   to indicate where to insert the MRU list in the menu.

2) Implement MRU click event handler in the form class:

System::Void Form1::MRU_Click(System::Object^ sender, System::EventArgs^ e)
{
    String^ filename = mruManager->OnMRUClicked(sender, e);

    // open file here
}

3) Add MRUManager member to the form class and initialize it:

    private: OzoneUtil::MRUManager^ mruManager;

	public:
        Form1(void)
        {
            InitializeComponent();
            //
            //TODO: Add the constructor code here
            //
            mruManager = gcnew MRUManager();
            mruManager->Initialize(
                this,                              // owner form
                gcnew System::EventHandler(this, &Form1::MRU_Click),
                                                   // MRU click event handler
                mnuFileMRU,                        // Recent Files menu item or separator
                "Software\\MyCompany\\MyProgram"); // Registry path to keep MRU list
            mruManager->autoDirectory = true;      // or false, as you wish
            mruManager->CurrentDir = ".....";      // default is current directory, or the most
                                                   // recently used directory if autoDirectory is true
            mruManager->MaxMRULength = ?;          // default is 10
            mruManager->MaxDisplayNameLength = ?;  // default is 40
        }


     NOTES:
     - If Registry path is, for example, "Software\MyCompany\MyProgram",
       MRU list is kept in
       HKEY_CURRENT_USER\Software\MyCompany\MyProgram\MRU Registry entry.

     - CurrentDir is used to show file names in the menu. If file is in
       this directory, only file name is shown. If the file is in a sub-
       directory then the relative path is shown.

4) Call MRUManager Add and Remove functions when necessary:

       mruManager.Add(fileName);          // when file is successfully opened
                                          // or in a successful SaveAs

       mruManager.Remove(fileName);       // when Open File operation failed

*******************************************************************************/

namespace OzoneUtil {

    public ref class MRUManager
    {
    public:
        MRUManager()
            :   maxNumberOfFiles(10),
                maxDisplayLength(40),
                autoDirectory(false),
                inlineListIsEmpty(true)
        {
            lowerSeparator = gcnew System::Windows::Forms::ToolStripSeparator();
        }

    protected:
        ~MRUManager()
        {
			delete lowerSeparator;
        }

    public:
        int             maxNumberOfFiles;
        int             maxDisplayLength;
        System::String^ currentDirectory;
        bool            autoDirectory;

        void Initialize(System::Windows::Forms::Form^ owner, 
            System::EventHandler^ handler, 
            System::Windows::Forms::ToolStripItem^ mruItem, 
            System::String^ regPath);
        void Add(System::String^ file);
        void Remove(System::String^ file) { Remove(file, true); }
        System::String^ OnMRUClicked(System::Object^ sender, System::EventArgs^ e);

    private:
        System::Collections::ArrayList              mruList;
        System::Windows::Forms::Form^               ownerForm;
        System::Windows::Forms::ToolStripItem^      menuItemMRU;
        System::Windows::Forms::ToolStripMenuItem^  menuItemParent;
        System::String^                             registryPath;
        System::EventHandler^                       clickHandler;
        static System::String^						regEntryName = "file";

        bool                                        isInlineList;
        System::Windows::Forms::ToolStripSeparator^ lowerSeparator;
        bool                                        inlineListIsEmpty;

        System::Void OnMRUParentPopup(System::Object^ sender, System::EventArgs^ e);

        System::Void OnOwnerClosing(System::Object^ sender, 
            System::ComponentModel::CancelEventArgs^ e);

        void LoadMRU();
        void UpdateMenu();
        void Remove(System::String^ file, bool update);

        System::String^ GetDisplayName(System::String^ fullName, int index);
        System::String^ GetShortDisplayName(System::String^ fullName, int maxLen);
    };
}



