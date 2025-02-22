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
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <shlwapi.h>
#include <array>

using std::cerr;
using std::endl;

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
    std::exit(33);
}

const AbstractSystem::FileChar*
Win32System::tempFileDirectory()
{
    static std::array<wchar_t, 32768> tempPathBufferW;

    GetTempPathW((DWORD)tempPathBufferW.size(), tempPathBufferW.data());
    return tempPathBufferW.data();
}

AbstractSystem::istr_ptr
Win32System::tempFileForRead(const FileString& path)
{
    return std::make_unique<std::ifstream>(path.c_str(), std::ios::binary);
}

namespace {
    struct MallocDeleter {
        void operator()(void* ptr) const {
            free(ptr);
        }
    };
}

AbstractSystem::ostr_ptr
Win32System::tempFileForWrite(AbstractSystem::TempType tt, FileString& nameOut)
{    
    const FileChar* wtempdir = tempFileDirectory();

    std::unique_ptr<wchar_t, MallocDeleter> b{ _wtempnam(wtempdir, TempPrefixes[tt]) };
    if (!b)
        return nullptr;
    FileString bcopy = b.get();
    bcopy.append(TempSuffixes[tt]);
    ostr_ptr f = std::make_unique<std::ofstream>(bcopy, 
        std::ios::binary | std::ios::trunc | std::ios::out);
    nameOut.assign(bcopy);
    
    return f;
}

std::string
Win32System::relativeFilePath(const std::string& base, const std::string& rel)
{
    std::wstring wbase = Utf8ToUtf16(base.c_str());
    std::wstring wrel = Utf8ToUtf16(rel.c_str());

    ::PathRemoveFileSpecW(wbase.data());        // modify wbase in-situ
    wbase.resize(wcslen(wbase.data()), L' ');   // update wbase to shunken size

    // Perform PathCombineW w/o the weird canonicalization behavior
    if (!wbase.empty() && wbase.back() != L'\\')
        wbase.append(L"\\");
    wbase.append(wrel);

    if (::PathFileExistsW(wbase.c_str())) {
        return Utf16ToUtf8(wbase.data());
    } else {
        return rel;
    }
}

namespace {
    struct FindCloser {
        void operator()(void* ptr) const {
            FindClose(ptr);
        }
    };
}

std::vector<AbstractSystem::FileString>
Win32System::findTempFiles()
{
    std::vector<FileString> ret;
    const FileChar* tempdir = tempFileDirectory();

    std::vector<wchar_t> wtempdir(32768, L' ');
    if (wcscpy_s(wtempdir.data(), wtempdir.size(), tempFileDirectory()) ||
        !::PathAppendW(wtempdir.data(), TempPrefixAll) || 
        wcsncat_s(wtempdir.data(), wtempdir.size(), L"*", 1))
        return ret;

    ::WIN32_FIND_DATAW ffd;
    std::unique_ptr<void, FindCloser> fff(::FindFirstFileW(wtempdir.data(), &ffd));
    if (fff.get() == INVALID_HANDLE_VALUE) {
        fff.release();  // Don't call FindClose() if invalid
        return ret;     // Return empty
    }

    do {
        ret.emplace_back(tempdir);
        if (ret.back().back() != L'\\')
            ret.back().append(L"\\");
        ret.back().append(ffd.cFileName);
    } while (::FindNextFileW(fff.get(), &ffd));
    return ret;
}

int
Win32System::deleteTempFile(const FileString& name)
{
    return _wremove(name.c_str());
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

std::wstring
Win32System::normalize(const std::string& u8name)
{
    if (u8name.empty())
        return std::wstring();

    // Convert from utf-8 to utf-16
    std::wstring u16name = Utf8ToUtf16(u8name.c_str());

    // normalize the utf-16 string
    int normLen = ::NormalizeString(NormalizationKC, u16name.c_str(), -1, NULL, 0);
    if (normLen == 0 && ::GetLastError() != ERROR_SUCCESS)
        return std::wstring();
    std::wstring ret(normLen - 1, L' ');
    int len2 = ::NormalizeString(NormalizationKC, u16name.c_str(), -1, ret.data(), normLen);
    if (len2 == 0 && ::GetLastError() != ERROR_SUCCESS)
        return std::wstring();
    if (len2 != normLen)
        ret.resize(len2 - 1, L' ');
    return ret;
}