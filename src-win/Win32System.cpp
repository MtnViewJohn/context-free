// posixSystem.cpp
// Context Free
// ---------------------
// Copyright (C) 2005-2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2007-2013 John Horigan - john@glyphic.com
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
// Mark Lentczner can be contacted at markl@glyphic.com or at
// Mark Lentczner, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//

#include "Win32System.h"

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <shlwapi.h>

using namespace std;

void
Win32System::clearAndCR()
{
    CONSOLE_SCREEN_BUFFER_INFO bufInfo;
    HANDLE cons = ::GetStdHandle(STD_OUTPUT_HANDLE);
    BOOL ret = ::GetConsoleScreenBufferInfo(cons, &bufInfo);
    for (int x = bufInfo.dwCursorPosition.X + 1; x < bufInfo.dwSize.X; ++x)
        cerr << ' ';
    bufInfo.dwCursorPosition.X = 0;
    ret = ::SetConsoleCursorPosition(cons, bufInfo.dwCursorPosition);
}

const char*
Win32System::tempFileDirectory()
{
    static char tempPathBuffer[MAX_PATH];
    
    GetTempPathA(MAX_PATH, tempPathBuffer);
    return tempPathBuffer;
}

ostream*
Win32System::tempFileForWrite(AbstractSystem::TempType tt, string& nameOut)
{    
    ofstream* f = 0;
    
    char* b = _tempnam(tempFileDirectory(), TempPrefixes[tt]);
    if (b) {
        f = new ofstream;
        f->open(b, ios::binary | ios::trunc | ios::out);
        nameOut.assign(b);
    }
    free(b);
    
    return f;
}

std::string
Win32System::relativeFilePath(const std::string& base, const std::string& rel)
{
    char buf[MAX_PATH+1];
    strcpy(buf, base.c_str());
    PathRemoveFileSpecA(buf);
    PathAppendA(buf, rel.c_str());
    if (PathFileExistsA(buf))
        return string(buf);
    else
        return rel;
}


