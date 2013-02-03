// posixSystem.cpp
// Context Free
// ---------------------
// Copyright (C) 2005-2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2007-2008 John Horigan - john@glyphic.com
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

#include "posixSystem.h"

#include <cstdlib>
#include "stdarg.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;

const char* prettyInt(int);

void
PosixSystem::clearAndCR()
{
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO bufInfo;
    HANDLE cons = ::GetStdHandle(STD_OUTPUT_HANDLE);
    BOOL ret = ::GetConsoleScreenBufferInfo(cons, &bufInfo);
    for (int x = bufInfo.dwCursorPosition.X + 1; x < bufInfo.dwSize.X; ++x)
        cerr << ' ';
    bufInfo.dwCursorPosition.X = 0;
    ret = ::SetConsoleCursorPosition(cons, bufInfo.dwCursorPosition);
#else
    static const char* EraseEndofLine = "\x1b[K";
    cerr << EraseEndofLine << '\r';
#endif
}

const char*
PosixSystem::maybeLF()
{
    return mNeedEndl ? "\n" : "";
}
                          
void
PosixSystem::message(const char* fmt, ...)
{
    if (mQuiet && !mErrorMode) return;
    
    char buf[256];
    {
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, sizeof(buf), fmt, args);
        buf[sizeof(buf)-1] = '\0';
        va_end(args);
    }
    
    cerr << maybeLF() << buf << endl;
    mNeedEndl = false;
}

void
PosixSystem::syntaxError(const CfdgError& err)
{
    // this version doesn't high-light the line in error
    // the parser will have already called message() with
    // the syntax error information
    error();
    message("Error in %s at line %d - %s", 
            err.where.begin.filename->c_str(), err.where.begin.line, err.what);
}

bool
PosixSystem::error(bool errorOccurred)
{
    mErrorMode = mErrorMode || errorOccurred;
    return mErrorMode;
}

istream*
PosixSystem::openFileForRead(const string& path)
{
    if (path == "-") {
        if (!mInputBuffer) {
            mInputBuffer = new string(istreambuf_iterator<char>(cin), 
                                      istreambuf_iterator<char>());
        }
        return new istringstream(*mInputBuffer, ios::binary);
    }
    return new ifstream(path.c_str(), ios::binary);
}

istream*
PosixSystem::tempFileForRead(const string& path)
{
    return new ifstream(path.c_str(), ios::binary);
}

PosixSystem::~PosixSystem()
{
    delete mInputBuffer;
}

ostream*
PosixSystem::tempFileForWrite(string& prefixInNameOut)
{
#ifdef WIN32
    char* path = _tempnam(0, prefixInNameOut.c_str());
    prefixInNameOut = path;
    ofstream* f = new ofstream(path, ios::binary | ios::out | ios::trunc);
    free((void*)path);
    return f;
#else
    string t = "/tmp/" + prefixInNameOut + "XXXXXX";
    char* b = new char[t.size() + 1];
    strcpy(b, t.c_str());
    
    ofstream* f = 0;
    
    // Please ignore the warning about mktemp() being unsafe. There is no 
    // standard way to turn the descriptor returned by mkstemp() into an
    // ostream object. We could add the boost library to the project (NO!!!!)
    // or roll our own file descriptor ostream class (code exists on the
    // internet). But it just doesn't seem worth the bother. mktemp() is 
    // unsafe for some types of programs, but who cares if an attacker takes
    // down your Context Free.
    if (mktemp(b)) {
        f = new ofstream;
        f->open(b, ios::binary);
        prefixInNameOut = b;
    }
    delete b;
    
    return f;
#endif
}

string
PosixSystem::relativeFilePath(const string& base, const string& rel)
{
    string s = base;
    
    string::size_type i = s.rfind('/');
    if (i == string::npos) {
        return rel;
    }
    i += 1;
    s.replace(i, s.length() - i, rel);
    return s;
}

void
PosixSystem::stats(const Stats& s)
{
    if (mQuiet || mErrorMode) return;
    
    if (s.inOutput || s.showProgress) {
        double v = (double)s.outputDone / s.outputCount;
        static const char prog[] = "**************************************************";
        static const char todo[] = "..................................................";
        if (v < 0.0) v = 0.0;
        if (v > 1.0) v = 1.0;
        int progress = (int)(v * 50.0 + 0.5);
        cerr << '[';
        cerr << &(prog[50 - progress]);
        cerr << &(todo[progress]);
        cerr << ']';
    } else {
        cerr << "    " << prettyInt(s.shapeCount) << " shapes";
        
        if (s.toDoCount > 0)
            cerr << " - " << prettyInt(s.toDoCount) << " expansions to do";
    }

    clearAndCR();
    mNeedEndl = true;
    cerr.flush();
}


