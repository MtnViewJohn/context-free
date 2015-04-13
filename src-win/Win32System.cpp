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
#include <sstream>
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

void
Win32System::catastrophicError(const char* what)
{
    cerr << "\n\nUnexpected error: " << what << endl;
}

const char*
Win32System::tempFileDirectory()
{
    static wchar_t tempPathBufferW[32768];
    static char tempPathBuffer[32768];

    GetTempPathW(32768, tempPathBufferW);
    if (::WideCharToMultiByte(CP_UTF8, 0, tempPathBufferW, -1, tempPathBuffer, 32768, NULL, NULL))
        return tempPathBuffer;
    else
        return "";
}

istream*
Win32System::tempFileForRead(const string& path)
{
    wchar_t wpath[32768];
    if (::MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, wpath, 32768))
        return new ifstream(wpath, ios::binary);
    message("Could not open this file: %s", path.c_str());
    return new stringstream(ios_base::in);
}

ostream*
Win32System::tempFileForWrite(AbstractSystem::TempType tt, string& nameOut)
{    
    ofstream* f = nullptr;
    
    wchar_t wtempdir[32768];
    if (!::MultiByteToWideChar(CP_UTF8, 0, tempFileDirectory(), -1, wtempdir, 32768))
        return nullptr;

    wchar_t* b = _wtempnam(wtempdir, TempPrefixes_w[tt]);
    if (b) {
        char buf[32768];
        f = new ofstream;
        f->open(b, ios::binary | ios::trunc | ios::out);
        if (::WideCharToMultiByte(CP_UTF8, 0, b, -1, buf, 32768, NULL, NULL))
            nameOut.assign(buf);
    }
    free(b);
    
    return f;
}

std::string
Win32System::relativeFilePath(const std::string& base, const std::string& rel)
{
    wchar_t wbase[32768], wrel[32768];
    char buf[32768];
    if (!::MultiByteToWideChar(CP_UTF8, 0, base.c_str(), -1, wbase, 32768) ||
        !::MultiByteToWideChar(CP_UTF8, 0, rel.c_str(), -1, wrel, 32768))
    {
        message("Cannot find %s relative to %s", rel.c_str(), base.c_str());
        return string();
    }
    PathRemoveFileSpecW(wbase);
    PathAppendW(wbase, wrel);
    if (PathFileExistsW(wbase) && ::WideCharToMultiByte(CP_UTF8, 0, wbase, -1, buf, 32768, NULL, NULL)) {
        return string(buf);
    } else {
        return rel;
    }
}

vector<string>
Win32System::findTempFiles()
{
    vector<string> ret;
    const char* tempdir = tempFileDirectory();

    wchar_t wtempdir[32768];
    char buf[32768];
    if (!::MultiByteToWideChar(CP_UTF8, 0, tempdir, -1, wtempdir, 32768) ||
        !::PathAppendW(wtempdir, TempPrefixAll_w) || 
        wcsncat_s(wtempdir, 32768, L"*", 1))
        return ret;

    ::WIN32_FIND_DATAW ffd;
    unique_ptr<void, decltype(&FindClose)> fff(::FindFirstFileW(wtempdir, &ffd), &FindClose);
    if (fff.get() == INVALID_HANDLE_VALUE) {
        fff.release();  // Don't call FindClose() if invalid
        return ret;     // Return empty
    }

    do {
        if (::WideCharToMultiByte(CP_UTF8, 0, ffd.cFileName, -1, buf, 32768, NULL, NULL)) {
            std::string name(tempdir);
            if (name.back() != '\\')
                name.push_back('\\');
            name.append(buf);
            ret.push_back(std::move(name));
        }
    } while (::FindNextFileW(fff.get(), &ffd));
    return ret;
}

size_t
Win32System::getPhysicalMemory()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    if (!SystemIs64bit && status.ullTotalPhys > 2147483648ULL)
        return (size_t)2147483648ULL;
    return (size_t)status.ullTotalPhys;
}
