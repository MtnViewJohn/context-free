// WinSystem.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2012 John Horigan - john@glyphic.com
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

#ifndef INCLUDE_WINSYSTEM_H
#define INCLUDE_WINSYSTEM_H
#include <iostream>
#include <string>
#include <map>
#include "Win32System.h"

#define myWM_USER (0x400)
class WinSystem : public Win32System 
{
public:
    enum {  WM_USER_MESSAGE_UPDATE  = myWM_USER + 100, 
            WM_USER_STATUS_UPDATE   = myWM_USER + 101,
            WM_USER_SYNTAX_ERROR    = myWM_USER + 102,
            WM_ACTIVATE = 0x0006, 
            WA_ACTIVE = 1,
            WM_DDE_INITIATE = 0x03E0,
            WM_DDE_EXECUTE = 0x03E8,
            WM_DDE_ACK = 0x3E4,
            SW_SHOWNORMAL = 1,
            EM_SETTABSTOPS          = 0x00CB};
    WinSystem(void*);
    ~WinSystem();
    virtual void message(const char* fmt, ...);
    virtual void syntaxError(const CfdgError& err);
    virtual bool error(bool errorOccurred = true);
    virtual void catastrophicError(const char* what);

    virtual std::istream* openFileForRead(const std::string& path);
    // caller must delete returned streams when done
    
    virtual void orphan();

    virtual void stats(const Stats&);
    void statusUpdate();

    bool updateInfo(const char* name, const char* text);

    static std::map<const std::string, std::string> ExampleMap;
    static void AddExample(const char* name, const char* text);
    std::string mName;
    std::string mText;
private:
    void* mWindow;
    bool mErrorMode;
};

#endif  // INCLUDE_WINSYSTEM_H