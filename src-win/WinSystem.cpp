// WinSystem.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2013 John Horigan - john@glyphic.com
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

#define _CRT_SECURE_NO_WARNINGS 1

#include "WinSystem.h"
#include "cfdg.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <shlwapi.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

std::string  Utf16ToUtf8(const wchar_t* wstr)
{
    std::string str;
    int wlen = ::WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, NULL, NULL);
    if (wlen == 0)
        return str;
    str.resize(wlen - 1, ' ');
    int len = ::WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str.data(), wlen, NULL, NULL);
    if (len == 0) {
        str.clear();
        return str;
    }
    if (len != wlen)
        str.resize(len - 1, ' ');
    return str;
}

std::wstring Utf8ToUtf16(const char* str)
{
    std::wstring wstr;
    int len = ::MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
    if (len == 0)
        return wstr;
    wstr.resize(len - 1, L' ');
    int wlen = ::MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr.data(), len);
    if (wlen == 0) {
        wstr.clear();
        return wstr;
    }
    if (len != wlen)
        wstr.resize(wlen - 1, L' ');
    return wstr;
}

void* WinSystem::MainWindow = nullptr;

WinSystem::WinSystem(void* h)
:   mWindow(h)
{
}

WinSystem::~WinSystem()
{
}


bool WinSystem::updateInfo(const char* newName, const char* newText)
{
    mName = newName;

    if (!strcmp(newText, mText.c_str()))
        return false;

    mText = newText;
    return true;
}

void WinSystem::message(const char* fmt, ...)
{
    if (!mWindow) return;
    va_list args;
    va_start(args, fmt);
    char cbuf[256];
    _vsnprintf(cbuf, 255, fmt, args);
    cbuf[255] = '\0';
    va_end(args);
    
    char* buf = new char[strlen(cbuf) + 1];
    strcpy(buf, cbuf);

    if (!::PostMessageW((HWND)mWindow, WM_USER_MESSAGE_UPDATE,(WPARAM)buf, NULL))
        delete[] buf;
}

void WinSystem::syntaxError(const CfdgError& errLoc)
{
    if (!mWindow) return;
    if (!errLoc.where.begin.filename || mName.compare(*(errLoc.where.begin.filename)) == 0) {
        message(
            R"({\rtf1 Error - 
{\field{\*\fldinst {HYPERLINK "#e:%d:%d:%d:%d" }}{\fldrslt {%s}}}})",
                errLoc.where.begin.line, errLoc.where.begin.column,
                errLoc.where.end.line, errLoc.where.end.column, errLoc.what());
    } else {
        message("Error in file %s at line %d:%d to line %d:%d - %s", errLoc.where.end.filename->c_str(), 
                errLoc.where.begin.line, errLoc.where.begin.column + 1, 
                errLoc.where.end.line, errLoc.where.end.column + 1, errLoc.what());
    }
}


bool WinSystem::error(bool errorOccurred)
{
    mErrorMode = mErrorMode || errorOccurred;
    return mErrorMode;
}

void WinSystem::catastrophicError(const char* what)
{
    if (!MainWindow)
        return;

    std::wstring wwhat = Utf8ToUtf16(what);

    (void)::MessageBoxW(NULL, wwhat.c_str(), L"Unexpected error", MB_OK | MB_ICONEXCLAMATION);
    ::PostMessageW((HWND)MainWindow, WM_CLOSE, NULL, NULL);
    MainWindow = nullptr;   // Only do this once
}

AbstractSystem::istr_ptr WinSystem::openFileForRead(const std::string& path)
{
    auto filepos = path.rfind('\\');
    filepos = filepos == std::string::npos ? 0 : filepos + 1;
    std::string exname{ path, filepos };
    auto exText = ExamplesMap.find(exname);

    if (path == mName) {
        return std::make_unique<std::stringstream>(mText);
    } else if (exText != ExamplesMap.end()) {
        auto cfdg = cfdgVersion == 2 ? exText->second.second : exText->second.first;
        return std::make_unique<std::stringstream>(cfdg, std::ios_base::in);
    } else {
        return std::make_unique<std::ifstream>(path.c_str(), std::ios::binary);
    }
}

void WinSystem::stats(const Stats& s)
{
    if (!mWindow) return;
    Stats* stat = new Stats(s);
    if (!::PostMessageW((HWND)mWindow, WM_USER_STATUS_UPDATE,(WPARAM)stat, NULL))
        delete stat;
}

void WinSystem::statusUpdate()
{
    if (mWindow)
        ::PostMessageW((HWND)mWindow, WM_USER_STATUS_UPDATE, NULL, NULL);
}

void WinSystem::orphan()
{
    mWindow = nullptr;
    mName.clear();
    mText.clear();
}
