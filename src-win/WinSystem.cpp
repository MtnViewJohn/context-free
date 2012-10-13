// WinSystem.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 John Horigan - john@glyphic.com
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
    va_list args;
    va_start(args, fmt);
    char cbuf[256];
    _vsnprintf(cbuf, 255, fmt, args);
    cbuf[255] = '\0';
    va_end(args);
    
    char* buf = new char[strlen(cbuf) + 1];
    strcpy(buf, cbuf);

    if (!::PostMessage((HWND)mWindow, WM_USER_MESSAGE_UPDATE,(WPARAM)buf, NULL))
        delete[] buf;
}

void WinSystem::syntaxError(const CfdgError& errLoc)
{
    if (mName.compare(*(errLoc.where.begin.filename)) == 0) {
        message("Error - <a href='#e:%d:%d:%d:%d'>%s</a>",
                errLoc.where.begin.line, errLoc.where.begin.column,
                errLoc.where.end.line, errLoc.where.end.column, errLoc.what);
    } else {
        message("Error in file %s - %s", 
        ::PathFindFileNameA(errLoc.where.begin.filename->c_str()), errLoc.what);
    }
}


bool WinSystem::error(bool errorOccurred)
{
    mErrorMode = mErrorMode || errorOccurred;
    return mErrorMode;
}

std::istream* WinSystem::openFileForRead(const std::string& path)
{
    map<const string, string>::iterator exText = ExampleMap.find(path);

    if (path == mName) {
        return new stringstream(mText);
    } else if (exText != ExampleMap.end()) {
        return new stringstream(exText->second);
    } else {
        return new ifstream(path.c_str(), ios::binary);
    }
}

std::istream* WinSystem::tempFileForRead(const std::string& path)
{
    return new ifstream(path.c_str(), ios::binary);
}

std::ostream* WinSystem::tempFileForWrite(std::string& prefixInNameOut)
{
    char* path = _tempnam(0, prefixInNameOut.c_str());
    prefixInNameOut = path;
    ofstream* f = new ofstream(path, ios::binary | ios::out | ios::trunc);
    free((void*)path);
    return f;
}

std::string WinSystem::relativeFilePath(const std::string& base, const std::string& rel)
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

void WinSystem::stats(const Stats& s)
{
    Stats* stat = new Stats(s);
    if (!::PostMessage((HWND)mWindow, WM_USER_STATUS_UPDATE,(WPARAM)stat, NULL))
        delete stat;
}

void WinSystem::statusUpdate()
{
    ::PostMessage((HWND)mWindow, WM_USER_STATUS_UPDATE, NULL, NULL);
}

