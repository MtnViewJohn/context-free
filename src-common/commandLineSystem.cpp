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
#include <stdarg.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "bounds.h"

#include <streambuf>
#include <istream>

struct membuf: std::streambuf {
    membuf(char const* base, size_t size) {
        char* p(const_cast<char*>(base));
        this->setg(p, p, p + size);
    }
};
struct imemstream: virtual membuf, std::istream {
    imemstream(char const* base, size_t size)
    : membuf(base, size)
    , std::istream(static_cast<std::streambuf*>(this)) {
    }
};

using std::cin;
using std::cerr;
using std::endl;

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

std::istream*
CommandLineSystem::openFileForRead(const std::string& path)
{
    if (path == "-") {
        if (!mInputBuffer) {
            std::ostringstream ss;
            ss << cin.rdbuf();
            mInputBuffer = std::make_unique<std::string>(ss.str());
        }
        return new imemstream(mInputBuffer->data(), mInputBuffer->length());
    }
    
    char dirchar =
#ifdef _WIN32
        '\\';
#else
        '/';
#endif
    auto dirloc = path.rfind(dirchar);
    auto exfile = path.substr(dirloc == std::string::npos ? 0 : dirloc + 1);
    
    if (cfdgVersion == 2)
        exfile.replace(exfile.end() - 5, exfile.end(), "_v2.cfdg");
    auto example = ExamplesMap.find(exfile);
    if (example != ExamplesMap.end())
        return new imemstream(example->second, strlen(example->second));

    std::unique_ptr<std::istream> f = std::make_unique<std::ifstream>(path.c_str(), std::ios::binary);
    if (f && (bool)(*f))
        return f.release();

    return nullptr;
}

void
CommandLineSystem::stats(const Stats& s)
{
    if (mQuiet || mErrorMode) return;
    
    if (s.inOutput || s.showProgress) {
        double v = s.outputCount ? static_cast<double>(s.outputDone) / s.outputCount : 1.0;
        static const char prog[] = "**************************************************";
        static const char todo[] = "..................................................";
        if (v < 0.0) v = 0.0;
        if (v > 1.0 || !std::isfinite(v)) v = 1.0;
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

#include "examples.h"
