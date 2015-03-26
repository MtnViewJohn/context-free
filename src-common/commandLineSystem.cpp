// commandLineSystem.cpp
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

#include "commandLineSystem.h"

#include <cstdlib>
#include "stdarg.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

const char* prettyInt(unsigned long);

const char*
CommandLineSystem::maybeLF()
{
    return mNeedEndl ? "\n" : "";
}
                          
void
CommandLineSystem::message(const char* fmt, ...)
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
CommandLineSystem::syntaxError(const CfdgError& err)
{
    // this version doesn't high-light the line in error
    // the parser will have already called message() with
    // the syntax error information
    message("Error in %s at line %d:%d-%d:%d - %s",
            err.where.end.filename->c_str(), err.where.begin.line, err.where.begin.column,
            err.where.end.line, err.where.end.column, err.what());
}

bool
CommandLineSystem::error(bool errorOccurred)
{
    mErrorMode = mErrorMode || errorOccurred;
    return mErrorMode;
}

istream*
CommandLineSystem::openFileForRead(const string& path)
{
    if (path == "-") {
        if (!mInputBuffer) {
            std::ostringstream ss;
            ss << cin.rdbuf();
            mInputBuffer.reset(new string(ss.str()));
        }
        return new istringstream(*mInputBuffer, ios::binary);
    }
    return tempFileForRead(path);
}

void
CommandLineSystem::stats(const Stats& s)
{
    if (mQuiet || mErrorMode) return;
    
    if (s.inOutput || s.showProgress) {
        double v = static_cast<double>(s.outputDone) / s.outputCount;
        static const char prog[] = "**************************************************";
        static const char todo[] = "..................................................";
        if (v < 0.0) v = 0.0;
        if (v > 1.0) v = 1.0;
        int progress = static_cast<int>(v * 50.0 + 0.5);
        cerr << '[';
        cerr << &(prog[50 - progress]);
        cerr << &(todo[progress]);
        cerr << ']';
    } else {
        cerr << "    " << prettyInt(static_cast<unsigned long>(s.shapeCount)) << " shapes";
        
        if (s.toDoCount > 0)
            cerr << " - " << prettyInt(static_cast<unsigned long>(s.toDoCount)) << " expansions to do";
    }

    clearAndCR();
    mNeedEndl = true;
    cerr.flush();
}


