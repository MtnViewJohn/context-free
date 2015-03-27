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

using namespace std;

//map<const string, WinSystem*> WinSystem::PathMap;
map<const string, string> WinSystem::ExampleMap;

WinSystem::WinSystem(void* h)
:   mWindow(h)
{
}

WinSystem::~WinSystem()
{
}

void WinSystem::AddExample(const char* newName, const char* newText)
{
    ExampleMap[newName] = newText;
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
        message("Error - <a href='#e:%d:%d:%d:%d'>%s</a>",
                errLoc.where.begin.line, errLoc.where.begin.column,
                errLoc.where.end.line, errLoc.where.end.column, errLoc.what());
    } else {
        message("Error in file %s at line %d:%d - %d:%d - %s", errLoc.where.end.filename->c_str(), 
                errLoc.where.begin.line, errLoc.where.begin.column, 
                errLoc.where.end.line, errLoc.where.end.column, errLoc.what());
    }
}


bool WinSystem::error(bool errorOccurred)
{
    mErrorMode = mErrorMode || errorOccurred;
    return mErrorMode;
}

void WinSystem::catastrophicError(const char* what)
{
    wchar_t wbuf[32768];
    if (::MultiByteToWideChar(CP_UTF8, 0, what, -1, wbuf, 32768))
        (void)::MessageBoxW(NULL, wbuf, L"Unexpected error", MB_OK);
}

std::istream* WinSystem::openFileForRead(const std::string& path)
{
    map<const string, string>::iterator exText = ExampleMap.find(path);

    if (path == mName) {
        return new stringstream(mText);
    } else if (exText != ExampleMap.end()) {
        return new stringstream(exText->second, ios_base::in);
    } else {
        return tempFileForRead(path);
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
