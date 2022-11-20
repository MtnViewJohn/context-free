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
    std::array<wchar_t, 32768> wbase, wrel;
    std::array<char, 32768> buf;

    if (!::MultiByteToWideChar(CP_UTF8, 0, base.c_str(), -1, wbase.data(), (int)wbase.size()) ||
        !::MultiByteToWideChar(CP_UTF8, 0, rel.c_str(), -1, wrel.data(), (int)wrel.size()))
    {
        message("Cannot find %s relative to %s", rel.c_str(), base.c_str());
        return std::string();
    }
    PathRemoveFileSpecW(wbase.data());
    // Perform PathCombineW w/o the weird canonicalization behavior
    if (wbase[0] && wbase[wcslen(wbase.data()) - 1] != L'\\')
        wcscat_s(wbase.data(), wbase.size(), L"\\");
    wcscat_s(wbase.data(), wbase.size(), wrel.data());
    if (PathFileExistsW(wbase.data()) && 
        ::WideCharToMultiByte(CP_UTF8, 0, wbase.data(), -1, buf.data(), (int)buf.size(), nullptr, nullptr))
    {
        return std::string(buf.data());
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

    std::array<wchar_t, 32768> wtempdir;
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
    std::wstring u16name(u8name.length(), L' ');
    for (;;) {
		wchar_t* wbuf = &u16name[0];	// can't use uname16.data() pre-C++17
        // Null termination is neither passed in nor returned
        auto sz = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS,
            u8name.data(), static_cast<int>(u8name.length()), 
            wbuf, static_cast<int>(u16name.length()));
        if (sz) {
            u16name.resize(sz);
            break;
        } else if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
            u16name.resize(u16name.length() * 2, L' ');
        } else {
            return std::wstring();
        }
    }

    // normalize the utf-16 string
    std::wstring ret(u16name.length() + 20, L' ');
    for (;;) {
		wchar_t* retbuf = &ret[0];
        // Null termination is neither passed in nor returned
        auto sz = ::NormalizeString(NormalizationKC,
            u16name.data(), static_cast<int>(u16name.length()), 
            retbuf, static_cast<int>(ret.length()));
        if (sz > 0) {
            ret.resize(sz);
            return ret;
        } else if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
            ret.resize(ret.length() * 2, L' ');
        } else {
            return std::wstring();
        }
    }
}