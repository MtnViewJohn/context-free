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
#include <cstdarg>
#include <cstring>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "bounds.h"
#include "prettyint.h"
#include <streambuf>
#include <istream>
#include "builder.h"

struct membuf: std::streambuf {
    membuf(char const* base, std::size_t size) {
        char* p(const_cast<char*>(base));
        this->setg(p, p, p + size);
    }
};
struct imemstream: virtual membuf, std::istream {
    imemstream(char const* base, std::size_t size)
    : membuf(base, size)
    , std::istream(static_cast<std::streambuf*>(this)) {
    }
};

using std::cin;
using std::cerr;
using std::endl;

const char*
CommandLineSystem::maybeLF()
{
    return mNeedEndl ? "\n" : "";
}
                          
void
CommandLineSystem::message(const char* fmt, ...)
{
    if (mQuiet && !mErrorMode) return;
    
    std::va_list args1;
    va_start(args1, fmt);
    std::va_list args2;
    va_copy(args2, args1);
    std::size_t sz = 1 + std::vsnprintf(nullptr, 0, fmt, args1);
    if (sz > buf.size())
        buf.resize(2 * sz);
    va_end(args1);
    std::vsnprintf(buf.data(), buf.size(), fmt, args2);
    va_end(args2);
        
    cerr << maybeLF() << buf.data() << endl;
    mNeedEndl = false;
}

void
CommandLineSystem::syntaxError(const CfdgError& err)
{
    // this version doesn't high-light the line in error
    // the parser will have already called message() with
    // the syntax error information
    auto filename = err.where.end.filename && !err.where.end.filename->empty()
                    ? err.where.end.filename->c_str() : "cfdg text";
    message("\n%s:%d:%d: error: %s\n", filename, err.where.begin.line, 
            err.where.begin.column, err.what());
}

bool
CommandLineSystem::error(bool errorOccurred)
{
    mErrorMode = mErrorMode || errorOccurred;
    return mErrorMode;
}

AbstractSystem::istr_ptr
CommandLineSystem::openFileForRead(const std::string& path)
{
    if (path == "-") {
        if (!mInputBuffer) {
            std::ostringstream ss;
            ss << cin.rdbuf();
            mInputBuffer = std::make_unique<std::string>(ss.str());
        }
        mFirstCfdgRead = false;
        return std::make_unique<imemstream>(mInputBuffer->data(), mInputBuffer->length());
    }
    
    if (!mFirstCfdgRead) {
        char dirchar =
#ifdef _WIN32
            '\\';
#else
            '/';
#endif
        auto dirloc = path.rfind(dirchar);
        auto exfile = path.substr(dirloc == std::string::npos ? 0 : dirloc + 1);
    
        auto example = ExamplesMap.find(exfile);
        if (example != ExamplesMap.end()) {
            auto cfdg = cfdgVersion == 2 ? example->second.second : example->second.first;
            return std::make_unique<imemstream>(cfdg, std::strlen(cfdg));
        }
    } else {
        mFirstCfdgRead = false;
    }
    
    istr_ptr f = std::make_unique<std::ifstream>(path.c_str(), std::ios::binary);
    if (f && !f->good())
        f.reset();

    return f;
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
