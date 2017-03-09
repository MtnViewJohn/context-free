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
            mInputBuffer = std::make_unique<string>(ss.str());
        }
        return new imemstream(mInputBuffer->data(), mInputBuffer->length());
    }
    
    auto example = ExamplesMap.find(path);
    if (example != ExamplesMap.end())
        return new imemstream(example->second, strlen(example->second));

    return tempFileForRead(path);
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
        if (v > 1.0 || !myfinite(v)) v = 1.0;
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

const std::map<std::string, const char*>
CommandLineSystem::ExamplesMap{
    { "ciliasun.cfdg", R"&&&(startshape SUN

shape SUN
{
    loop 72 [r 5]
    LINER(-3…3) [y 5 sat 1 b 0.3]
}

shape LINER(number angle)
rule {
    UTRIANGLE [y 0.5 s 0.86 r 0.5]
    LINER(=) [r angle b 0.1 hue 0.1 60
              y 0.75 x 0.4330125 s 0.97]
}
rule .1 {
    LINER(-3…3) []
}

path UTRIANGLE {
    MOVETO(0, -0.5)
    loop 3 [r 120] {
        CURVEREL(
                 0.25, sqrt(3)/4,
                 -0.05, 0.025,
                 0, sqrt(3)/8
                 )
        CURVEREL(
                 0.25, sqrt(3)/4,
                 0.25 + 0.025, sqrt(3)/4 - 0.025,
                 CF::Continuous
                 )
    }
    CLOSEPOLY(CF::Align)
    FILL[]
}
)&&&" },
    { "demo1.cfdg", R"&&&(startshape FOREST

shape FOREST
{
    SEED []
    SEED [x -20]
    SEED [x -40]
}

shape SEED
rule {BRANCH []}
rule {BRANCH [rotate 1]}
rule {BRANCH [rotate -1]}
rule {BRANCH [rotate 2]}
rule {BRANCH [rotate -2]}
rule {FORK []}

shape BRANCH
rule {LEFTBRANCH [flip 90]}
rule {LEFTBRANCH []}

shape LEFTBRANCH
rule 4 {BLOCK [] LEFTBRANCH [y 0.885 rotate 0.1 size 0.99]}
rule 4 {BLOCK [] LEFTBRANCH [y 0.885 rotate 0.2 size 0.99]}
rule {BLOCK [] LEFTBRANCH [y 0.885 rotate 4 size 0.99]}
rule {BLOCK [] FORK []}


shape BLOCK
{
    SQUARE [rotate 1]
    SQUARE [rotate -1]
    SQUARE []
}

shape FORK
rule {
    BRANCH [ ]
    BRANCH [size 0.5 rotate 40]
}
rule {
    BRANCH [ ]
    BRANCH [size 0.5 rotate -40]
}
rule {
    BRANCH [size 0.5 rotate -20]
    BRANCH [ ]
}
rule {
    BRANCH [size 0.7 y 0.1 rotate 20]
    BRANCH [size 0.7 y 0.1 rotate -20]
}
)&&&" },
    { "demo2.cfdg", R"&&&(#
# An example, showing how to include another file.
# Note that the include path has to be absolute OR
# relative to the directory you run .cfdg in
#

startshape thingy
import i_pix.cfdg

shape thingy
{
    point [y -1 rotate 180]
    point []
}

shape point
{
    C_5by5 []
    F_5by5 [x 1.2]
    D_5by5 [y -1.2]
    G_5by5 [y -1.2 x 1.2]
    point [y 2.0 x -2.5 rotate 20 size 0.6]
    point [y 2.0 x 2.5 rotate -20 size 0.6]
}
)&&&" },
    { "funky_flower.cfdg", R"&&&(startshape GARDEN
import i_curves.cfdg

shape GARDEN
rule {
    SEED []
}

shape SEED
rule {
    curveleft_0_98_3 [x -2]
    curveleft_0_98_2 []
    curveleft_0_98_1 [x 2]
    LEFT_OR_RIGHT [x 4 size 4 y 1.3]
    curveright_0_98_1 [x 6]
    curveright_0_98_2 [x 8]
    curveright_0_98_3 [x 10]
}

shape LEFT_OR_RIGHT
rule {  LEFT_FLOWER [] }
rule {  LEFT_FLOWER [flip 90] }

shape LEFT_FLOWER
rule {
    curveleft_0_97_1 []
    FLOWER [x -13 y 25.3 size 1]
}

shape FLOWER
rule {
    CIRCLE [size 2]
    loop 6 [r 60] NEW_SEED []
}

shape NEW_SEED
rule {
    SEED [size 0.1 y 3]
}

)&&&" },
    { "i_curves.cfdg", R"&&&(// This is a library file that is included in other files
// It offers a family of curves

startshape test_i_curves

shape curveright_0_9_5
rule {
    SQUARE [ ]
    curveright_0_9_5 [ rotate -5 size 0.9 x -0.0124921 y 0.909067 ]
}

shape curveright_0_9_4
rule {
    SQUARE [ ]
    curveright_0_9_4 [ rotate -4 size 0.9 x -0.0197055 y 0.917513 ]
}

shape curveright_0_9_3
rule {
    SQUARE [ ]
    curveright_0_9_3 [ rotate -3 size 0.9 x -0.0270653 y 0.925832 ]
}

shape curveright_0_9_2
rule {
    SQUARE [ ]
    curveright_0_9_2 [ rotate -2 size 0.9 x -0.0345691 y 0.934021 ]
}

shape curveright_0_9_1
rule {
    SQUARE [ ]
    curveright_0_9_1 [ rotate -1 size 0.9 x -0.0422147 y 0.942078 ]
}

shape curveleft_0_9_0
rule {
    SQUARE [ ]
    curveleft_0_9_0 [ rotate 0 size 0.9 x 0.0500008 y 0.950001 ]
}

shape curveleft_0_9_1
rule {
    SQUARE [ ]
    curveleft_0_9_1 [ rotate 1 size 0.9 x 0.0422158 y 0.942079 ]
}

shape curveleft_0_9_2
rule {
    SQUARE [ ]
    curveleft_0_9_2 [ rotate 2 size 0.9 x 0.0345701 y 0.934022 ]
}

shape curveleft_0_9_3
rule {
    SQUARE [ ]
    curveleft_0_9_3 [ rotate 3 size 0.9 x 0.0270664 y 0.925833 ]
}

shape curveleft_0_9_4
rule {
    SQUARE [ ]
    curveleft_0_9_4 [ rotate 4 size 0.9 x 0.0197066 y 0.917514 ]
}

shape curveleft_0_9_5
rule {
    SQUARE [ ]
    curveleft_0_9_5 [ rotate 5 size 0.9 x 0.0124931 y 0.909068 ]
}

shape curveright_0_91_5
rule {
    SQUARE [ ]
    curveright_0_91_5 [ rotate -5 size 0.91 x -0.00707531 y 0.913612 ]
}

shape curveright_0_91_4
rule {
    SQUARE [ ]
    curveright_0_91_4 [ rotate -4 size 0.91 x -0.0143689 y 0.922152 ]
}

shape curveright_0_91_3
rule {
    SQUARE [ ]
    curveright_0_91_3 [ rotate -3 size 0.91 x -0.0218104 y 0.930563 ]
}

shape curveright_0_91_2
rule {
    SQUARE [ ]
    curveright_0_91_2 [ rotate -2 size 0.91 x -0.0293976 y 0.938843 ]
}

shape curveright_0_91_1
rule {
    SQUARE [ ]
    curveright_0_91_1 [ rotate -1 size 0.91 x -0.0371282 y 0.94699 ]
}

shape curveleft_0_91_0
rule {
    SQUARE [ ]
    curveleft_0_91_0 [ rotate 0 size 0.91 x 0.0450008 y 0.955001 ]
}

shape curveleft_0_91_1
rule {
    SQUARE [ ]
    curveleft_0_91_1 [ rotate 1 size 0.91 x 0.0371293 y 0.946991 ]
}

shape curveleft_0_91_2
rule {
    SQUARE [ ]
    curveleft_0_91_2 [ rotate 2 size 0.91 x 0.0293987 y 0.938844 ]
}

shape curveleft_0_91_3
rule {
    SQUARE [ ]
    curveleft_0_91_3 [ rotate 3 size 0.91 x 0.0218115 y 0.930565 ]
}

shape curveleft_0_91_4
rule {
    SQUARE [ ]
    curveleft_0_91_4 [ rotate 4 size 0.91 x 0.01437 y 0.922153 ]
}

shape curveleft_0_91_5
rule {
    SQUARE [ ]
    curveleft_0_91_5 [ rotate 5 size 0.91 x 0.00707635 y 0.913614 ]
}

shape curveright_0_92_5
rule {
    SQUARE [ ]
    curveright_0_92_5 [ rotate -5 size 0.92 x -0.00165855 y 0.918158 ]
}

shape curveright_0_92_4
rule {
    SQUARE [ ]
    curveright_0_92_4 [ rotate -4 size 0.92 x -0.00903229 y 0.926791 ]
}

shape curveright_0_92_3
rule {
    SQUARE [ ]
    curveright_0_92_3 [ rotate -3 size 0.92 x -0.0165556 y 0.935295 ]
}

shape curveright_0_92_2
rule {
    SQUARE [ ]
    curveright_0_92_2 [ rotate -2 size 0.92 x -0.0242262 y 0.943666 ]
}

shape curveright_0_92_1
rule {
    SQUARE [ ]
    curveright_0_92_1 [ rotate -1 size 0.92 x -0.0320417 y 0.951902 ]
}

shape curveleft_0_92_0
rule {
    SQUARE [ ]
    curveleft_0_92_0 [ rotate 0 size 0.92 x 0.0400008 y 0.960001 ]
}

shape curveleft_0_92_1
rule {
    SQUARE [ ]
    curveleft_0_92_1 [ rotate 1 size 0.92 x 0.0320428 y 0.951903 ]
}

shape curveleft_0_92_2
rule {
    SQUARE [ ]
    curveleft_0_92_2 [ rotate 2 size 0.92 x 0.0242272 y 0.943667 ]
}

shape curveleft_0_92_3
rule {
    SQUARE [ ]
    curveleft_0_92_3 [ rotate 3 size 0.92 x 0.0165567 y 0.935296 ]
}

shape curveleft_0_92_4
rule {
    SQUARE [ ]
    curveleft_0_92_4 [ rotate 4 size 0.92 x 0.00903342 y 0.926793 ]
}

shape curveleft_0_92_5
rule {
    SQUARE [ ]
    curveleft_0_92_5 [ rotate 5 size 0.92 x 0.00165959 y 0.918159 ]
}

shape curveright_0_93_5
rule {
    SQUARE [ ]
    curveright_0_93_5 [ rotate -5 size 0.93 x 0.00375817 y 0.922703 ]
}

shape curveright_0_93_4
rule {
    SQUARE [ ]
    curveright_0_93_4 [ rotate -4 size 0.93 x -0.00369572 y 0.93143 ]
}

shape curveright_0_93_3
rule {
    SQUARE [ ]
    curveright_0_93_3 [ rotate -3 size 0.93 x -0.0113008 y 0.940026 ]
}

shape curveright_0_93_2
rule {
    SQUARE [ ]
    curveright_0_93_2 [ rotate -2 size 0.93 x -0.0190547 y 0.948488 ]
}

shape curveright_0_93_1
rule {
    SQUARE [ ]
    curveright_0_93_1 [ rotate -1 size 0.93 x -0.0269552 y 0.956814 ]
}

shape curveleft_0_93_0
rule {
    SQUARE [ ]
    curveleft_0_93_0 [ rotate 0 size 0.93 x 0.0350009 y 0.965001 ]
}

shape curveleft_0_93_1
rule {
    SQUARE [ ]
    curveleft_0_93_1 [ rotate 1 size 0.93 x 0.0269564 y 0.956815 ]
}

shape curveleft_0_93_2
rule {
    SQUARE [ ]
    curveleft_0_93_2 [ rotate 2 size 0.93 x 0.0190558 y 0.948489 ]
}

shape curveleft_0_93_3
rule {
    SQUARE [ ]
    curveleft_0_93_3 [ rotate 3 size 0.93 x 0.0113019 y 0.940027 ]
}

shape curveleft_0_93_4
rule {
    SQUARE [ ]
    curveleft_0_93_4 [ rotate 4 size 0.93 x 0.00369686 y 0.931432 ]
}

shape curveleft_0_93_5
rule {
    SQUARE [ ]
    curveleft_0_93_5 [ rotate 5 size 0.93 x -0.00375711 y 0.922704 ]
}

shape curveright_0_94_5
rule {
    SQUARE [ ]
    curveright_0_94_5 [ rotate -5 size 0.94 x 0.00917493 y 0.927248 ]
}

shape curveright_0_94_4
rule {
    SQUARE [ ]
    curveright_0_94_4 [ rotate -4 size 0.94 x 0.00164089 y 0.936069 ]
}

shape curveright_0_94_3
rule {
    SQUARE [ ]
    curveright_0_94_3 [ rotate -3 size 0.94 x -0.00604596 y 0.944758 ]
}

shape curveright_0_94_2
rule {
    SQUARE [ ]
    curveright_0_94_2 [ rotate -2 size 0.94 x -0.0138833 y 0.953311 ]
}

shape curveright_0_94_1
rule {
    SQUARE [ ]
    curveright_0_94_1 [ rotate -1 size 0.94 x -0.0218687 y 0.961725 ]
}

shape curveleft_0_94_0
rule {
    SQUARE [ ]
    curveleft_0_94_0 [ rotate 0 size 0.94 x 0.0300009 y 0.970001 ]
}

shape curveleft_0_94_1
rule {
    SQUARE [ ]
    curveleft_0_94_1 [ rotate 1 size 0.94 x 0.0218699 y 0.961727 ]
}

shape curveleft_0_94_2
rule {
    SQUARE [ ]
    curveleft_0_94_2 [ rotate 2 size 0.94 x 0.0138844 y 0.953312 ]
}

shape curveleft_0_94_3
rule {
    SQUARE [ ]
    curveleft_0_94_3 [ rotate 3 size 0.94 x 0.00604711 y 0.944759 ]
}

shape curveleft_0_94_4
rule {
    SQUARE [ ]
    curveleft_0_94_4 [ rotate 4 size 0.94 x -0.00163974 y 0.936071 ]
}

shape curveleft_0_94_5
rule {
    SQUARE [ ]
    curveleft_0_94_5 [ rotate 5 size 0.94 x -0.00917386 y 0.927249 ]
}

shape curveright_0_95_5
rule {
    SQUARE [ ]
    curveright_0_95_5 [ rotate -5 size 0.95 x 0.0145917 y 0.931793 ]
}

shape curveright_0_95_4
rule {
    SQUARE [ ]
    curveright_0_95_4 [ rotate -4 size 0.95 x 0.0069775 y 0.940708 ]
}

shape curveright_0_95_3
rule {
    SQUARE [ ]
    curveright_0_95_3 [ rotate -3 size 0.95 x 0 y 0.949489 ]
}

shape curveright_0_95_2
rule {
    SQUARE [ ]
    curveright_0_95_2 [ rotate -2 size 0.95 x -0.00871182 y 0.958133 ]
}

shape curveright_0_95_1
rule {
    SQUARE [ ]
    curveright_0_95_1 [ rotate -1 size 0.95 x -0.0167822 y 0.966637 ]
}

shape curveleft_0_95_0
rule {
    SQUARE [ ]
    curveleft_0_95_0 [ rotate 0 size 0.95 x 0.0250009 y 0.975001 ]
}

shape curveleft_0_95_1
rule {
    SQUARE [ ]
    curveleft_0_95_1 [ rotate 1 size 0.95 x 0.0167834 y 0.966639 ]
}

shape curveleft_0_95_2
rule {
    SQUARE [ ]
    curveleft_0_95_2 [ rotate 2 size 0.95 x 0.00871294 y 0.958134 ]
}

shape curveleft_0_95_3
rule {
    SQUARE [ ]
    curveleft_0_95_3 [ rotate 3 size 0.95 x 0 y 0.94949 ]
}

shape curveleft_0_95_4
rule {
    SQUARE [ ]
    curveleft_0_95_4 [ rotate 4 size 0.95 x -0.00697634 y 0.94071 ]
}

shape curveleft_0_95_5
rule {
    SQUARE [ ]
    curveleft_0_95_5 [ rotate 5 size 0.95 x -0.0145906 y 0.931794 ]
}

shape curveright_0_96_5
rule {
    SQUARE [ ]
    curveright_0_96_5 [ rotate -5 size 0.96 x 0.0200085 y 0.936338 ]
}

shape curveright_0_96_4
rule {
    SQUARE [ ]
    curveright_0_96_4 [ rotate -4 size 0.96 x 0.0123141 y 0.945347 ]
}

shape curveright_0_96_3
rule {
    SQUARE [ ]
    curveright_0_96_3 [ rotate -3 size 0.96 x 0.00446371 y 0.954221 ]
}

shape curveright_0_96_2
rule {
    SQUARE [ ]
    curveright_0_96_2 [ rotate -2 size 0.96 x -0.00354036 y 0.962956 ]
}

shape curveright_0_96_1
rule {
    SQUARE [ ]
    curveright_0_96_1 [ rotate -1 size 0.96 x -0.0116957 y 0.971549 ]
}

shape curveleft_0_96_0
rule {
    SQUARE [ ]
    curveleft_0_96_0 [ rotate 0 size 0.96 x 0.0200009 y 0.980001 ]
}

shape curveleft_0_96_1
rule {
    SQUARE [ ]
    curveleft_0_96_1 [ rotate 1 size 0.96 x 0.0116969 y 0.971551 ]
}

shape curveleft_0_96_2
rule {
    SQUARE [ ]
    curveleft_0_96_2 [ rotate 2 size 0.96 x 0.00354149 y 0.962957 ]
}

shape curveleft_0_96_3
rule {
    SQUARE [ ]
    curveleft_0_96_3 [ rotate 3 size 0.96 x -0.00446254 y 0.954222 ]
}

shape curveleft_0_96_4
rule {
    SQUARE [ ]
    curveleft_0_96_4 [ rotate 4 size 0.96 x -0.0123129 y 0.945349 ]
}

shape curveleft_0_96_5
rule {
    SQUARE [ ]
    curveleft_0_96_5 [ rotate 5 size 0.96 x -0.0200074 y 0.93634 ]
}

shape curveright_0_97_5
rule {
    SQUARE [ ]
    curveright_0_97_5 [ rotate -5 size 0.97 x 0.0254252 y 0.940884 ]
}

shape curveright_0_97_4
rule {
    SQUARE [ ]
    curveright_0_97_4 [ rotate -4 size 0.97 x 0.0176507 y 0.949986 ]
}

shape curveright_0_97_3
rule {
    SQUARE [ ]
    curveright_0_97_3 [ rotate -3 size 0.97 x 0.00971855 y 0.958952 ]
}

shape curveright_0_97_2
rule {
    SQUARE [ ]
    curveright_0_97_2 [ rotate -2 size 0.97 x 0.0016311 y 0.967778 ]
}

shape curveright_0_97_1
rule {
    SQUARE [ ]
    curveright_0_97_1 [ rotate -1 size 0.97 x -0.00660916 y 0.976461 ]
}

shape curveleft_0_97_0
rule {
    SQUARE [ ]
    curveleft_0_97_0 [ rotate 0 size 0.97 x 0.0150009 y 0.985001 ]
}

shape curveleft_0_97_1
rule {
    SQUARE [ ]
    curveleft_0_97_1 [ rotate 1 size 0.97 x 0.00661039 y 0.976463 ]
}

shape curveleft_0_97_2
rule {
    SQUARE [ ]
    curveleft_0_97_2 [ rotate 2 size 0.97 x -0.00162996 y 0.967779 ]
}

shape curveleft_0_97_3
rule {
    SQUARE [ ]
    curveleft_0_97_3 [ rotate 3 size 0.97 x -0.00971737 y 0.958953 ]
}

shape curveleft_0_97_4
rule {
    SQUARE [ ]
    curveleft_0_97_4 [ rotate 4 size 0.97 x -0.0176495 y 0.949988 ]
}

shape curveleft_0_97_5
rule {
    SQUARE [ ]
    curveleft_0_97_5 [ rotate 5 size 0.97 x -0.0254241 y 0.940885 ]
}

shape curveright_0_98_5
rule {
    SQUARE [ ]
    curveright_0_98_5 [ rotate -5 size 0.98 x 0.030842 y 0.945429 ]
}

shape curveright_0_98_4
rule {
    SQUARE [ ]
    curveright_0_98_4 [ rotate -4 size 0.98 x 0.0229873 y 0.954625 ]
}

shape curveright_0_98_3
rule {
    SQUARE [ ]
    curveright_0_98_3 [ rotate -3 size 0.98 x 0.0149734 y 0.963684 ]
}

shape curveright_0_98_2
rule {
    SQUARE [ ]
    curveright_0_98_2 [ rotate -2 size 0.98 x 0.00680257 y 0.9726 ]
}

shape curveright_0_98_1
rule {
    SQUARE [ ]
    curveright_0_98_1 [ rotate -1 size 0.98 x -0.00152265 y 0.981373 ]
}

shape curveleft_0_98_0
rule {
    SQUARE [ ]
    curveleft_0_98_0 [ rotate 0 size 0.98 x 0.0100009 y 0.990001 ]
}

shape curveleft_0_98_1
rule {
    SQUARE [ ]
    curveleft_0_98_1 [ rotate 1 size 0.98 x 0.00152389 y 0.981375 ]
}

shape curveleft_0_98_2
rule {
    SQUARE [ ]
    curveleft_0_98_2 [ rotate 2 size 0.98 x -0.00680141 y 0.972602 ]
}

shape curveleft_0_98_3
rule {
    SQUARE [ ]
    curveleft_0_98_3 [ rotate 3 size 0.98 x -0.0149722 y 0.963685 ]
}

shape curveleft_0_98_4
rule {
    SQUARE [ ]
    curveleft_0_98_4 [ rotate 4 size 0.98 x -0.0229861 y 0.954627 ]
}

shape curveleft_0_98_5
rule {
    SQUARE [ ]
    curveleft_0_98_5 [ rotate 5 size 0.98 x -0.0308409 y 0.94543 ]
}

shape curveright_0_99_5
rule {
    SQUARE [ ]
    curveright_0_99_5 [ rotate -5 size 0.99 x 0.0362587 y 0.949974 ]
}

shape curveright_0_99_4
rule {
    SQUARE [ ]
    curveright_0_99_4 [ rotate -4 size 0.99 x 0.028324 y 0.959264 ]
}

shape curveright_0_99_3
rule {
    SQUARE [ ]
    curveright_0_99_3 [ rotate -3 size 0.99 x 0.0202282 y 0.968415 ]
}

shape curveright_0_99_2
rule {
    SQUARE [ ]
    curveright_0_99_2 [ rotate -2 size 0.99 x 0.011974 y 0.977423 ]
}

shape curveright_0_99_1
rule {
    SQUARE [ ]
    curveright_0_99_1 [ rotate -1 size 0.99 x 0.00356386 y 0.986285 ]
}

shape curveleft_0_99_0
rule {
    SQUARE [ ]
    curveleft_0_99_0 [ rotate 0 size 0.99 x 0.0050009 y 0.995001 ]
}

shape curveleft_0_99_1
rule {
    SQUARE [ ]
    curveleft_0_99_1 [ rotate 1 size 0.99 x -0.00356261 y 0.986287 ]
}

shape curveleft_0_99_2
rule {
    SQUARE [ ]
    curveleft_0_99_2 [ rotate 2 size 0.99 x -0.0119729 y 0.977424 ]
}

shape curveleft_0_99_3
rule {
    SQUARE [ ]
    curveleft_0_99_3 [ rotate 3 size 0.99 x -0.020227 y 0.968416 ]
}

shape curveleft_0_99_4
rule {
    SQUARE [ ]
    curveleft_0_99_4 [ rotate 4 size 0.99 x -0.0283227 y 0.959266 ]
}

shape curveleft_0_99_5
rule {
    SQUARE [ ]
    curveleft_0_99_5 [ rotate 5 size 0.99 x -0.0362576 y 0.949975 ]
}

shape curveright_1_5
rule {
    SQUARE [ ]
    curveright_1_5 [ rotate -5 size 1 x 0.0416755 y 0.954519 ]
}

shape curveright_1_4
rule {
    SQUARE [ ]
    curveright_1_4 [ rotate -4 size 1 x 0.0336605 y 0.963903 ]
}

shape curveright_1_3
rule {
    SQUARE [ ]
    curveright_1_3 [ rotate -3 size 1 x 0.025483 y 0.973146 ]
}

shape curveright_1_2
rule {
    SQUARE [ ]
    curveright_1_2 [ rotate -2 size 1 x 0.0171454 y 0.982245 ]
}

shape curveright_1_1
rule {
    SQUARE [ ]
    curveright_1_1 [ rotate -1 size 1 x 0.00865033 y 0.991197 ]
}

shape curveleft_1_0
rule {
    SQUARE [ ]
    curveleft_1_0 [ rotate 0 size 1 x 0 y 1 ]
}

shape curveleft_1_1
rule {
    SQUARE [ ]
    curveleft_1_1 [ rotate 1 size 1 x -0.00864906 y 0.991199 ]
}

shape curveleft_1_2
rule {
    SQUARE [ ]
    curveleft_1_2 [ rotate 2 size 1 x -0.0171443 y 0.982247 ]
}

shape curveleft_1_3
rule {
    SQUARE [ ]
    curveleft_1_3 [ rotate 3 size 1 x -0.0254818 y 0.973148 ]
}

shape curveleft_1_4
rule {
    SQUARE [ ]
    curveleft_1_4 [ rotate 4 size 1 x -0.0336593 y 0.963905 ]
}

shape curveleft_1_5
rule {
    SQUARE [ ]
    curveleft_1_5 [ rotate 5 size 1 x -0.0416743 y 0.954521 ]
}

shape curveright_1_01_5
rule {
    SQUARE [ ]
    curveright_1_01_5 [ rotate -5 size 1.01 x 0.0470922 y 0.959064 ]
}

shape curveright_1_01_4
rule {
    SQUARE [ ]
    curveright_1_01_4 [ rotate -4 size 1.01 x 0.0389971 y 0.968542 ]
}

shape curveright_1_01_3
rule {
    SQUARE [ ]
    curveright_1_01_3 [ rotate -3 size 1.01 x 0.0307379 y 0.977878 ]
}

shape curveright_1_01_2
rule {
    SQUARE [ ]
    curveright_1_01_2 [ rotate -2 size 1.01 x 0.0223169 y 0.987068 ]
}

shape curveright_1_01_1
rule {
    SQUARE [ ]
    curveright_1_01_1 [ rotate -1 size 1.01 x 0.0137368 y 0.996109 ]
}

shape curveleft_1_01_0
rule {
    SQUARE [ ]
    curveleft_1_01_0 [ rotate 0 size 1.01 x -0.00499905 y 1.005 ]
}

shape curveleft_1_01_1
rule {
    SQUARE [ ]
    curveleft_1_01_1 [ rotate 1 size 1.01 x -0.0137356 y 0.996111 ]
}

shape curveleft_1_01_2
rule {
    SQUARE [ ]
    curveleft_1_01_2 [ rotate 2 size 1.01 x -0.0223157 y 0.987069 ]
}

shape curveleft_1_01_3
rule {
    SQUARE [ ]
    curveleft_1_01_3 [ rotate 3 size 1.01 x -0.0307366 y 0.977879 ]
}

shape curveleft_1_01_4
rule {
    SQUARE [ ]
    curveleft_1_01_4 [ rotate 4 size 1.01 x -0.0389959 y 0.968544 ]
}

shape curveleft_1_01_5
rule {
    SQUARE [ ]
    curveleft_1_01_5 [ rotate 5 size 1.01 x -0.0470911 y 0.959066 ]
}

shape curveright_1_02_5
rule {
    SQUARE [ ]
    curveright_1_02_5 [ rotate -5 size 1.02 x 0.0525089 y 0.96361 ]
}

shape curveright_1_02_4
rule {
    SQUARE [ ]
    curveright_1_02_4 [ rotate -4 size 1.02 x 0.0443337 y 0.973181 ]
}

shape curveright_1_02_3
rule {
    SQUARE [ ]
    curveright_1_02_3 [ rotate -3 size 1.02 x 0.0359927 y 0.982609 ]
}

shape curveright_1_02_2
rule {
    SQUARE [ ]
    curveright_1_02_2 [ rotate -2 size 1.02 x 0.0274883 y 0.99189 ]
}

shape curveright_1_02_1
rule {
    SQUARE [ ]
    curveright_1_02_1 [ rotate -1 size 1.02 x 0.0188233 y 1.00102 ]
}

shape curveleft_1_02_0
rule {
    SQUARE [ ]
    curveleft_1_02_0 [ rotate 0 size 1.02 x -0.00999901 y 1.01 ]
}

shape curveleft_1_02_1
rule {
    SQUARE [ ]
    curveleft_1_02_1 [ rotate 1 size 1.02 x -0.018822 y 1.00102 ]
}

shape curveleft_1_02_2
rule {
    SQUARE [ ]
    curveleft_1_02_2 [ rotate 2 size 1.02 x -0.0274871 y 0.991892 ]
}
)&&&"
R"&&&(
shape curveleft_1_02_3
rule {
    SQUARE [ ]
    curveleft_1_02_3 [ rotate 3 size 1.02 x -0.0359914 y 0.982611 ]
}

shape curveleft_1_02_4
rule {
    SQUARE [ ]
    curveleft_1_02_4 [ rotate 4 size 1.02 x -0.0443325 y 0.973183 ]
}

shape curveleft_1_02_5
rule {
    SQUARE [ ]
    curveleft_1_02_5 [ rotate 5 size 1.02 x -0.0525078 y 0.963611 ]
}

shape curveright_1_03_5
rule {
    SQUARE [ ]
    curveright_1_03_5 [ rotate -5 size 1.03 x 0.0579257 y 0.968155 ]
}

shape curveright_1_03_4
rule {
    SQUARE [ ]
    curveright_1_03_4 [ rotate -4 size 1.03 x 0.0496704 y 0.977821 ]
}

shape curveright_1_03_3
rule {
    SQUARE [ ]
    curveright_1_03_3 [ rotate -3 size 1.03 x 0.0412475 y 0.987341 ]
}

shape curveright_1_03_2
rule {
    SQUARE [ ]
    curveright_1_03_2 [ rotate -2 size 1.03 x 0.0326598 y 0.996713 ]
}

shape curveright_1_03_1
rule {
    SQUARE [ ]
    curveright_1_03_1 [ rotate -1 size 1.03 x 0.0239099 y 1.00593 ]
}

shape curveleft_1_03_0
rule {
    SQUARE [ ]
    curveleft_1_03_0 [ rotate 0 size 1.03 x -0.014999 y 1.015 ]
}

shape curveleft_1_03_1
rule {
    SQUARE [ ]
    curveleft_1_03_1 [ rotate 1 size 1.03 x -0.0239086 y 1.00593 ]
}

shape curveleft_1_03_2
rule {
    SQUARE [ ]
    curveleft_1_03_2 [ rotate 2 size 1.03 x -0.0326586 y 0.996714 ]
}

shape curveleft_1_03_3
rule {
    SQUARE [ ]
    curveleft_1_03_3 [ rotate 3 size 1.03 x -0.0412463 y 0.987342 ]
}

shape curveleft_1_03_4
rule {
    SQUARE [ ]
    curveleft_1_03_4 [ rotate 4 size 1.03 x -0.0496691 y 0.977822 ]
}

shape curveleft_1_03_5
rule {
    SQUARE [ ]
    curveleft_1_03_5 [ rotate 5 size 1.03 x -0.0579246 y 0.968156 ]
}

shape curveright_1_04_5
rule {
    SQUARE [ ]
    curveright_1_04_5 [ rotate -5 size 1.04 x 0.0633425 y 0.9727 ]
}

shape curveright_1_04_4
rule {
    SQUARE [ ]
    curveright_1_04_4 [ rotate -4 size 1.04 x 0.0550069 y 0.98246 ]
}

shape curveright_1_04_3
rule {
    SQUARE [ ]
    curveright_1_04_3 [ rotate -3 size 1.04 x 0.0465023 y 0.992072 ]
}

shape curveright_1_04_2
rule {
    SQUARE [ ]
    curveright_1_04_2 [ rotate -2 size 1.04 x 0.0378313 y 1.00154 ]
}

shape curveright_1_04_1
rule {
    SQUARE [ ]
    curveright_1_04_1 [ rotate -1 size 1.04 x 0.0289963 y 1.01085 ]
}

shape curveleft_1_04_0
rule {
    SQUARE [ ]
    curveleft_1_04_0 [ rotate 0 size 1.04 x -0.019999 y 1.02 ]
}

shape curveleft_1_04_1
rule {
    SQUARE [ ]
    curveleft_1_04_1 [ rotate 1 size 1.04 x -0.028995 y 1.01085 ]
}

shape curveleft_1_04_2
rule {
    SQUARE [ ]
    curveleft_1_04_2 [ rotate 2 size 1.04 x -0.03783 y 1.00154 ]
}

shape curveleft_1_04_3
rule {
    SQUARE [ ]
    curveleft_1_04_3 [ rotate 3 size 1.04 x -0.0465011 y 0.992074 ]
}

shape curveleft_1_04_4
rule {
    SQUARE [ ]
    curveleft_1_04_4 [ rotate 4 size 1.04 x -0.0550057 y 0.982461 ]
}

shape curveleft_1_04_5
rule {
    SQUARE [ ]
    curveleft_1_04_5 [ rotate 5 size 1.04 x -0.0633413 y 0.972701 ]
}

shape curveright_1_05_5
rule {
    SQUARE [ ]
    curveright_1_05_5 [ rotate -5 size 1.05 x 0.0687592 y 0.977245 ]
}

shape curveright_1_05_4
rule {
    SQUARE [ ]
    curveright_1_05_4 [ rotate -4 size 1.05 x 0.0603435 y 0.987099 ]
}

shape curveright_1_05_3
rule {
    SQUARE [ ]
    curveright_1_05_3 [ rotate -3 size 1.05 x 0.0517571 y 0.996804 ]
}

shape curveright_1_05_2
rule {
    SQUARE [ ]
    curveright_1_05_2 [ rotate -2 size 1.05 x 0.0430027 y 1.00636 ]
}

shape curveright_1_05_1
rule {
    SQUARE [ ]
    curveright_1_05_1 [ rotate -1 size 1.05 x 0.0340828 y 1.01576 ]
}

shape curveleft_1_05_0
rule {
    SQUARE [ ]
    curveleft_1_05_0 [ rotate 0 size 1.05 x -0.024999 y 1.025 ]
}

shape curveleft_1_05_1
rule {
    SQUARE [ ]
    curveleft_1_05_1 [ rotate 1 size 1.05 x -0.0340815 y 1.01576 ]
}

shape curveleft_1_05_2
rule {
    SQUARE [ ]
    curveleft_1_05_2 [ rotate 2 size 1.05 x -0.0430014 y 1.00636 ]
}

shape curveleft_1_05_3
rule {
    SQUARE [ ]
    curveleft_1_05_3 [ rotate 3 size 1.05 x -0.0517558 y 0.996805 ]
}

shape curveleft_1_05_4
rule {
    SQUARE [ ]
    curveleft_1_05_4 [ rotate 4 size 1.05 x -0.0603422 y 0.9871 ]
}

shape curveleft_1_05_5
rule {
    SQUARE [ ]
    curveleft_1_05_5 [ rotate 5 size 1.05 x -0.068758 y 0.977246 ]
}

shape curveright_1_06_5
rule {
    SQUARE [ ]
    curveright_1_06_5 [ rotate -5 size 1.06 x 0.074176 y 0.98179 ]
}

shape curveright_1_06_4
rule {
    SQUARE [ ]
    curveright_1_06_4 [ rotate -4 size 1.06 x 0.0656802 y 0.991738 ]
}

shape curveright_1_06_3
rule {
    SQUARE [ ]
    curveright_1_06_3 [ rotate -3 size 1.06 x 0.057012 y 1.00154 ]
}

shape curveright_1_06_2
rule {
    SQUARE [ ]
    curveright_1_06_2 [ rotate -2 size 1.06 x 0.0481742 y 1.01118 ]
}

shape curveright_1_06_1
rule {
    SQUARE [ ]
    curveright_1_06_1 [ rotate -1 size 1.06 x 0.0391693 y 1.02067 ]
}

shape curveleft_1_06_0
rule {
    SQUARE [ ]
    curveleft_1_06_0 [ rotate 0 size 1.06 x -0.029999 y 1.03 ]
}

shape curveleft_1_06_1
rule {
    SQUARE [ ]
    curveleft_1_06_1 [ rotate 1 size 1.06 x -0.039168 y 1.02067 ]
}

shape curveleft_1_06_2
rule {
    SQUARE [ ]
    curveleft_1_06_2 [ rotate 2 size 1.06 x -0.0481729 y 1.01118 ]
}

shape curveleft_1_06_3
rule {
    SQUARE [ ]
    curveleft_1_06_3 [ rotate 3 size 1.06 x -0.0570107 y 1.00154 ]
}

shape curveleft_1_06_4
rule {
    SQUARE [ ]
    curveleft_1_06_4 [ rotate 4 size 1.06 x -0.0656789 y 0.991739 ]
}

shape curveleft_1_06_5
rule {
    SQUARE [ ]
    curveleft_1_06_5 [ rotate 5 size 1.06 x -0.0741748 y 0.981792 ]
}

shape curveright_1_07_5
rule {
    SQUARE [ ]
    curveright_1_07_5 [ rotate -5 size 1.07 x 0.0795927 y 0.986336 ]
}

shape curveright_1_07_4
rule {
    SQUARE [ ]
    curveright_1_07_4 [ rotate -4 size 1.07 x 0.0710168 y 0.996377 ]
}

shape curveright_1_07_3
rule {
    SQUARE [ ]
    curveright_1_07_3 [ rotate -3 size 1.07 x 0.0622668 y 1.00627 ]
}

shape curveright_1_07_2
rule {
    SQUARE [ ]
    curveright_1_07_2 [ rotate -2 size 1.07 x 0.0533456 y 1.016 ]
}

shape curveright_1_07_1
rule {
    SQUARE [ ]
    curveright_1_07_1 [ rotate -1 size 1.07 x 0.0442559 y 1.02558 ]
}

shape curveleft_1_07_0
rule {
    SQUARE [ ]
    curveleft_1_07_0 [ rotate 0 size 1.07 x -0.034999 y 1.035 ]
}

shape curveleft_1_07_1
rule {
    SQUARE [ ]
    curveleft_1_07_1 [ rotate 1 size 1.07 x -0.0442545 y 1.02558 ]
}

shape curveleft_1_07_2
rule {
    SQUARE [ ]
    curveleft_1_07_2 [ rotate 2 size 1.07 x -0.0533444 y 1.016 ]
}

shape curveleft_1_07_3
rule {
    SQUARE [ ]
    curveleft_1_07_3 [ rotate 3 size 1.07 x -0.0622655 y 1.00627 ]
}

shape curveleft_1_07_4
rule {
    SQUARE [ ]
    curveleft_1_07_4 [ rotate 4 size 1.07 x -0.0710155 y 0.996378 ]
}

shape curveleft_1_07_5
rule {
    SQUARE [ ]
    curveleft_1_07_5 [ rotate 5 size 1.07 x -0.0795915 y 0.986337 ]
}

shape curveright_1_08_5
rule {
    SQUARE [ ]
    curveright_1_08_5 [ rotate -5 size 1.08 x 0.0850095 y 0.990881 ]
}

shape curveright_1_08_4
rule {
    SQUARE [ ]
    curveright_1_08_4 [ rotate -4 size 1.08 x 0.0763534 y 1.00102 ]
}

shape curveright_1_08_3
rule {
    SQUARE [ ]
    curveright_1_08_3 [ rotate -3 size 1.08 x 0.0675217 y 1.011 ]
}

shape curveright_1_08_2
rule {
    SQUARE [ ]
    curveright_1_08_2 [ rotate -2 size 1.08 x 0.0585171 y 1.02083 ]
}

shape curveright_1_08_1
rule {
    SQUARE [ ]
    curveright_1_08_1 [ rotate -1 size 1.08 x 0.0493424 y 1.03049 ]
}

shape curveleft_1_08_0
rule {
    SQUARE [ ]
    curveleft_1_08_0 [ rotate 0 size 1.08 x -0.039999 y 1.04 ]
}

shape curveleft_1_08_1
rule {
    SQUARE [ ]
    curveleft_1_08_1 [ rotate 1 size 1.08 x -0.049341 y 1.03049 ]
}

shape curveleft_1_08_2
rule {
    SQUARE [ ]
    curveleft_1_08_2 [ rotate 2 size 1.08 x -0.0585158 y 1.02083 ]
}

shape curveleft_1_08_3
rule {
    SQUARE [ ]
    curveleft_1_08_3 [ rotate 3 size 1.08 x -0.0675204 y 1.011 ]
}

shape curveleft_1_08_4
rule {
    SQUARE [ ]
    curveleft_1_08_4 [ rotate 4 size 1.08 x -0.0763521 y 1.00102 ]
}

shape curveleft_1_08_5
rule {
    SQUARE [ ]
    curveleft_1_08_5 [ rotate 5 size 1.08 x -0.0850083 y 0.990882 ]
}

shape curveright_1_09_5
rule {
    SQUARE [ ]
    curveright_1_09_5 [ rotate -5 size 1.09 x 0.0904263 y 0.995426 ]
}

shape curveright_1_09_4
rule {
    SQUARE [ ]
    curveright_1_09_4 [ rotate -4 size 1.09 x 0.08169 y 1.00565 ]
}

shape curveright_1_09_3
rule {
    SQUARE [ ]
    curveright_1_09_3 [ rotate -3 size 1.09 x 0.0727765 y 1.01573 ]
}

shape curveright_1_09_2
rule {
    SQUARE [ ]
    curveright_1_09_2 [ rotate -2 size 1.09 x 0.0636886 y 1.02565 ]
}

shape curveright_1_09_1
rule {
    SQUARE [ ]
    curveright_1_09_1 [ rotate -1 size 1.09 x 0.0544289 y 1.03541 ]
}

shape curveleft_1_09_0
rule {
    SQUARE [ ]
    curveleft_1_09_0 [ rotate 0 size 1.09 x -0.044999 y 1.045 ]
}

shape curveleft_1_09_1
rule {
    SQUARE [ ]
    curveleft_1_09_1 [ rotate 1 size 1.09 x -0.0544275 y 1.03541 ]
}

shape curveleft_1_09_2
rule {
    SQUARE [ ]
    curveleft_1_09_2 [ rotate 2 size 1.09 x -0.0636873 y 1.02565 ]
}

shape curveleft_1_09_3
rule {
    SQUARE [ ]
    curveleft_1_09_3 [ rotate 3 size 1.09 x -0.0727752 y 1.01573 ]
}

shape curveleft_1_09_4
rule {
    SQUARE [ ]
    curveleft_1_09_4 [ rotate 4 size 1.09 x -0.0816887 y 1.00566 ]
}

shape curveleft_1_09_5
rule {
    SQUARE [ ]
    curveleft_1_09_5 [ rotate 5 size 1.09 x -0.090425 y 0.995427 ]
}

shape curveright_1_1_5
rule {
    SQUARE [ ]
    curveright_1_1_5 [ rotate -5 size 1.1 x 0.095843 y 0.999971 ]
}

shape curveright_1_1_4
rule {
    SQUARE [ ]
    curveright_1_1_4 [ rotate -4 size 1.1 x 0.0870266 y 1.01029 ]
}

shape curveright_1_1_3
rule {
    SQUARE [ ]
    curveright_1_1_3 [ rotate -3 size 1.1 x 0.0780314 y 1.02046 ]
}

shape curveright_1_1_2
rule {
    SQUARE [ ]
    curveright_1_1_2 [ rotate -2 size 1.1 x 0.06886 y 1.03047 ]
}

shape curveright_1_1_1
rule {
    SQUARE [ ]
    curveright_1_1_1 [ rotate -1 size 1.1 x 0.0595154 y 1.04032 ]
}

shape curveleft_1_1_0
rule {
    SQUARE [ ]
    curveleft_1_1_0 [ rotate 0 size 1.1 x -0.049999 y 1.05 ]
}

shape curveleft_1_1_1
rule {
    SQUARE [ ]
    curveleft_1_1_1 [ rotate 1 size 1.1 x -0.059514 y 1.04032 ]
}

shape curveleft_1_1_2
rule {
    SQUARE [ ]
    curveleft_1_1_2 [ rotate 2 size 1.1 x -0.0688587 y 1.03047 ]
}

shape curveleft_1_1_3
rule {
    SQUARE [ ]
    curveleft_1_1_3 [ rotate 3 size 1.1 x -0.07803 y 1.02046 ]
}

shape curveleft_1_1_4
rule {
    SQUARE [ ]
    curveleft_1_1_4 [ rotate 4 size 1.1 x -0.0870253 y 1.0103 ]
}

shape curveleft_1_1_5
rule {
    SQUARE [ ]
    curveleft_1_1_5 [ rotate 5 size 1.1 x -0.0958418 y 0.999973 ]
}


shape test_i_curves
rule {
    test_i_curves_0_9  [ x -35 y -40 ]
    test_i_curves_0_91 [ x   0 y -40 ]
    test_i_curves_0_92 [ x  35 y -40 ]
    test_i_curves_0_93 [ x -40 y -20 ]
    test_i_curves_0_94 [ x   0 y -20 ]
    test_i_curves_0_95 [ x  40 y -20 ]
    test_i_curves_0_96 [ x -55 y   0 ]
    test_i_curves_0_97 [ x   0 y   0 ]
    test_i_curves_0_98 [ x  55 y   0 ]
    test_i_curves_0_99 [ x   0 y  40 ]
}

shape test_i_curves_0_9
rule {
    curveright_0_9_5 [ x 10 ]
    curveright_0_9_4 [ x 8 ]
    curveright_0_9_3 [ x 6 ]
    curveright_0_9_2 [ x 4 ]
    curveright_0_9_1 [ x 2 ]
    curveleft_0_9_0 [ ]
    curveleft_0_9_1 [ x -2 ]
    curveleft_0_9_2 [ x -4 ]
    curveleft_0_9_3 [ x -6 ]
    curveleft_0_9_4 [ x -8 ]
    curveleft_0_9_5 [ x -10 ]
}

shape test_i_curves_0_91
rule {
    curveright_0_91_5 [ x 10 ]
    curveright_0_91_4 [ x 8 ]
    curveright_0_91_3 [ x 6 ]
    curveright_0_91_2 [ x 4 ]
    curveright_0_91_1 [ x 2 ]
    curveleft_0_91_0 [ ]
    curveleft_0_91_1 [ x -2 ]
    curveleft_0_91_2 [ x -4 ]
    curveleft_0_91_3 [ x -6 ]
    curveleft_0_91_4 [ x -8 ]
    curveleft_0_91_5 [ x -10 ]
}

shape test_i_curves_0_92
rule {
    curveright_0_92_5 [ x 10 ]
    curveright_0_92_4 [ x 8 ]
    curveright_0_92_3 [ x 6 ]
    curveright_0_92_2 [ x 4 ]
    curveright_0_92_1 [ x 2 ]
    curveleft_0_92_0 [ ]
    curveleft_0_92_1 [ x -2 ]
    curveleft_0_92_2 [ x -4 ]
    curveleft_0_92_3 [ x -6 ]
    curveleft_0_92_4 [ x -8 ]
    curveleft_0_92_5 [ x -10 ]
}

shape test_i_curves_0_93
rule {
    curveright_0_93_5 [ x 10 ]
    curveright_0_93_4 [ x 8 ]
    curveright_0_93_3 [ x 6 ]
    curveright_0_93_2 [ x 4 ]
    curveright_0_93_1 [ x 2 ]
    curveleft_0_93_0 [ ]
    curveleft_0_93_1 [ x -2 ]
    curveleft_0_93_2 [ x -4 ]
    curveleft_0_93_3 [ x -6 ]
    curveleft_0_93_4 [ x -8 ]
    curveleft_0_93_5 [ x -10 ]
}

shape test_i_curves_0_94
rule {
    curveright_0_94_5 [ x 10 ]
    curveright_0_94_4 [ x 8 ]
    curveright_0_94_3 [ x 6 ]
    curveright_0_94_2 [ x 4 ]
    curveright_0_94_1 [ x 2 ]
    curveleft_0_94_0 [ ]
    curveleft_0_94_1 [ x -2 ]
    curveleft_0_94_2 [ x -4 ]
    curveleft_0_94_3 [ x -6 ]
    curveleft_0_94_4 [ x -8 ]
    curveleft_0_94_5 [ x -10 ]
}

shape test_i_curves_0_95
rule {
    curveright_0_95_5 [ x 10 ]
    curveright_0_95_4 [ x 8 ]
    curveright_0_95_3 [ x 6 ]
    curveright_0_95_2 [ x 4 ]
    curveright_0_95_1 [ x 2 ]
    curveleft_0_95_0 [ ]
    curveleft_0_95_1 [ x -2 ]
    curveleft_0_95_2 [ x -4 ]
    curveleft_0_95_3 [ x -6 ]
    curveleft_0_95_4 [ x -8 ]
    curveleft_0_95_5 [ x -10 ]
}

shape test_i_curves_0_96
rule {
    curveright_0_96_5 [ x 10 ]
    curveright_0_96_4 [ x 8 ]
    curveright_0_96_3 [ x 6 ]
    curveright_0_96_2 [ x 4 ]
    curveright_0_96_1 [ x 2 ]
    curveleft_0_96_0 [ ]
    curveleft_0_96_1 [ x -2 ]
    curveleft_0_96_2 [ x -4 ]
    curveleft_0_96_3 [ x -6 ]
    curveleft_0_96_4 [ x -8 ]
    curveleft_0_96_5 [ x -10 ]
}

shape test_i_curves_0_97
rule {
    curveright_0_97_5 [ x 10 ]
    curveright_0_97_4 [ x 8 ]
    curveright_0_97_3 [ x 6 ]
    curveright_0_97_2 [ x 4 ]
    curveright_0_97_1 [ x 2 ]
    curveleft_0_97_0 [ ]
    curveleft_0_97_1 [ x -2 ]
    curveleft_0_97_2 [ x -4 ]
    curveleft_0_97_3 [ x -6 ]
    curveleft_0_97_4 [ x -8 ]
    curveleft_0_97_5 [ x -10 ]
}

shape test_i_curves_0_98
rule {
    curveright_0_98_5 [ x 10 ]
    curveright_0_98_4 [ x 8 ]
    curveright_0_98_3 [ x 6 ]
    curveright_0_98_2 [ x 4 ]
    curveright_0_98_1 [ x 2 ]
    curveleft_0_98_0 [ ]
    curveleft_0_98_1 [ x -2 ]
    curveleft_0_98_2 [ x -4 ]
    curveleft_0_98_3 [ x -6 ]
    curveleft_0_98_4 [ x -8 ]
    curveleft_0_98_5 [ x -10 ]
}

shape test_i_curves_0_99
rule {
    curveright_0_99_5 [ x 10 ]
    curveright_0_99_4 [ x 8 ]
    curveright_0_99_3 [ x 6 ]
    curveright_0_99_2 [ x 4 ]
    curveright_0_99_1 [ x 2 ]
    curveleft_0_99_0 [ ]
    curveleft_0_99_1 [ x -2 ]
    curveleft_0_99_2 [ x -4 ]
    curveleft_0_99_3 [ x -6 ]
    curveleft_0_99_4 [ x -8 ]
    curveleft_0_99_5 [ x -10 ]
}

)&&&" },
    { "i_pix.cfdg", R"&&&(// This is a library file that is included in other files
// It offers a dot-matix like alphabet based on a 5 by 5 grid

startshape the5by5_test

shape the5by5_test
{
    random_test []
    the5by5_line []
}

shape random_test
{
    loop 5 [y 1.2] random_test_row [x 24.0 y -21.0]
}

shape random_test_row
{
    loop 5 [x 1.2] RANDOM_ALNUM_5by5 []
}


shape the5by5_line
{
    A_5by5 [x 0]
    B_5by5 [x 1.2 ]
    C_5by5 [x 2.4]
    D_5by5 [x 3.6]
    E_5by5 [x 4.8]
    F_5by5 [x 6.0]
    G_5by5 [x 7.2]
    H_5by5 [x 8.4]
    I_5by5 [x 9.6]
    J_5by5 [x 10.8]
    K_5by5 [x 12.0]
    L_5by5 [x 13.2]
    M_5by5 [x 14.4]
    N_5by5 [x 15.6]
    O_5by5 [x 16.8]
    P_5by5 [x 18.0]
    Q_5by5 [x 19.2]
    R_5by5 [x 20.4]
    S_5by5 [x 21.6]
    T_5by5 [x 22.8]
    U_5by5 [x 24.0]
    V_5by5 [x 25.2]
    W_5by5 [x 26.4]
    X_5by5 [x 27.6]
    Y_5by5 [x 28.8]
    Z_5by5 [x 30.0]
    the5by5_line [y -2.4 size 0.90 x 0.2]
    NUM_0_5by5 [y -1.2 x 0]
    NUM_1_5by5 [y -1.2 x 1.2]
    NUM_2_5by5 [y -1.2 x 2.4]
    NUM_3_5by5 [y -1.2 x 3.6]
    NUM_4_5by5 [y -1.2 x 4.8]
    NUM_5_5by5 [y -1.2 x 6.0]
    NUM_6_5by5 [y -1.2 x 7.2]
    NUM_7_5by5 [y -1.2 x 8.4]
    NUM_8_5by5 [y -1.2 x 9.6]
    NUM_9_5by5 [y -1.2 x 10.8]
}

shape pix_5by5_00
{ block_5by5 [size 0.20 x -0.4 y 0.4] }
shape pix_5by5_10
{ block_5by5 [size 0.20 x -0.2 y 0.4] }
shape pix_5by5_20
{ block_5by5 [size 0.20 x 0.0 y 0.4] }
shape pix_5by5_30
{ block_5by5 [size 0.20 x 0.2 y 0.4] }
shape pix_5by5_40
{ block_5by5 [size 0.20 x 0.4 y 0.4] }
shape pix_5by5_01
{ block_5by5 [size 0.20 x -0.4 y 0.2] }
shape pix_5by5_11
{ block_5by5 [size 0.20 x -0.2 y 0.2] }
shape pix_5by5_21
{ block_5by5 [size 0.20 x 0.0 y 0.2] }
shape pix_5by5_31
{ block_5by5 [size 0.20 x 0.2 y 0.2] }
shape pix_5by5_41
{ block_5by5 [size 0.20 x 0.4 y 0.2] }
shape pix_5by5_02
{ block_5by5 [size 0.20 x -0.4 y 0.0] }
shape pix_5by5_12
{ block_5by5 [size 0.20 x -0.2 y 0.0] }
shape pix_5by5_22
{ block_5by5 [size 0.20 x 0.0 y 0.0] }
shape pix_5by5_32
{ block_5by5 [size 0.20 x 0.2 y 0.0] }
shape pix_5by5_42
{ block_5by5 [size 0.20 x 0.4 y 0.0] }
shape pix_5by5_03
{ block_5by5 [size 0.20 x -0.4 y -0.2] }
shape pix_5by5_13
{ block_5by5 [size 0.20 x -0.2 y -0.2] }
shape pix_5by5_23
{ block_5by5 [size 0.20 x 0.0 y -0.2] }
shape pix_5by5_33
{ block_5by5 [size 0.20 x 0.2 y -0.2] }
shape pix_5by5_43
{ block_5by5 [size 0.20 x 0.4 y -0.2] }
shape pix_5by5_04
{ block_5by5 [size 0.20 x -0.4 y -0.4] }
shape pix_5by5_14
{ block_5by5 [size 0.20 x -0.2 y -0.4] }
shape pix_5by5_24
{ block_5by5 [size 0.20 x 0.0 y -0.4] }
shape pix_5by5_34
{ block_5by5 [size 0.20 x 0.2 y -0.4] }
shape pix_5by5_44
{ block_5by5 [size 0.20 x 0.4 y -0.4] }

shape block_5by5
{
    SQUARE [size 0.7]
}

shape A_5by5
{
    pix_5by5_04 []
    pix_5by5_44 []
    pix_5by5_03 []
    pix_5by5_43 []
    pix_5by5_02 []
    pix_5by5_42 []
    pix_5by5_11 []
    pix_5by5_31 []
    pix_5by5_20 []
    pix_5by5_20 []
    pix_5by5_13 []
    pix_5by5_23 []
    pix_5by5_33 []
    
}
shape B_5by5
{
    pix_5by5_04 []
    pix_5by5_03 []
    pix_5by5_02 []
    pix_5by5_01 []
    pix_5by5_00 []
    pix_5by5_10 []
    pix_5by5_12 []
    pix_5by5_14 []
    pix_5by5_20 []
    pix_5by5_22 []
    pix_5by5_24 []
    pix_5by5_31 []
    pix_5by5_32 []
    pix_5by5_34 []
    pix_5by5_43 []
}

shape C_5by5
{
    pix_5by5_03 []
    pix_5by5_02 []
    pix_5by5_01 []
    pix_5by5_10 []
    pix_5by5_14 []
    pix_5by5_20 []
    pix_5by5_24 []
    pix_5by5_30 []
    pix_5by5_34 []
    pix_5by5_40 []
    pix_5by5_44 []
}
shape D_5by5
{
    pix_5by5_04 []
    pix_5by5_03 []
    pix_5by5_02 []
    pix_5by5_01 []
    pix_5by5_00 []
    pix_5by5_10 []
    pix_5by5_14 []
    pix_5by5_20 []
    pix_5by5_24 []
    pix_5by5_30 []
    pix_5by5_34 []
    pix_5by5_41 []
    pix_5by5_42 []
    pix_5by5_43 []
}
shape E_5by5
{
    pix_5by5_04 []
    pix_5by5_03 []
    pix_5by5_02 []
    pix_5by5_01 []
    pix_5by5_00 []
    pix_5by5_10 []
    pix_5by5_12 []
    pix_5by5_14 []
    pix_5by5_20 []
    pix_5by5_22 []
    pix_5by5_24 []
    pix_5by5_30 []
    pix_5by5_34 []
    pix_5by5_40 []
    pix_5by5_44 []
}

shape F_5by5
{
    pix_5by5_04 []
    pix_5by5_03 []
    pix_5by5_02 []
    pix_5by5_01 []
    pix_5by5_00 []
    pix_5by5_10 []
    pix_5by5_12 []
    pix_5by5_20 []
    pix_5by5_22 []
    pix_5by5_30 []
    pix_5by5_40 []
}

shape G_5by5
{
    pix_5by5_03 []
    pix_5by5_02 []
    pix_5by5_01 []
    pix_5by5_10 []
    pix_5by5_14 []
    pix_5by5_20 []
    pix_5by5_22 []
    pix_5by5_24 []
    pix_5by5_30 []
    pix_5by5_32 []
    pix_5by5_34 []
    pix_5by5_40 []
    pix_5by5_42 []
    pix_5by5_43 []
}

shape H_5by5
{
    pix_5by5_00 []
    pix_5by5_04 []
    pix_5by5_03 []
    pix_5by5_02 []
    pix_5by5_01 []
    pix_5by5_12 []
    pix_5by5_22 []
    pix_5by5_32 []
    pix_5by5_40 []
    pix_5by5_41 []
    pix_5by5_42 []
    pix_5by5_43 []
    pix_5by5_44 []
}

shape I_5by5
{
    H_5by5 [rotate 90]
}


shape J_5by5
{
    pix_5by5_00 []
    pix_5by5_03 []
    pix_5by5_10 []
    pix_5by5_14 []
    pix_5by5_20 []
    pix_5by5_24 []
    pix_5by5_30 []
    pix_5by5_31 []
    pix_5by5_32 []
    pix_5by5_33 []
    pix_5by5_40 []
}

shape K_5by5
{
    pix_5by5_00 []
    pix_5by5_01 []
    pix_5by5_02 []
    pix_5by5_03 []
    pix_5by5_04 []
    pix_5by5_12 []
    pix_5by5_23 []
    pix_5by5_21 []
    pix_5by5_34 []
    pix_5by5_30 []
    pix_5by5_44 []
    pix_5by5_44 []
}

shape L_5by5
{
    pix_5by5_00 []
    pix_5by5_01 []
    pix_5by5_02 []
    pix_5by5_03 []
    pix_5by5_04 []
    pix_5by5_14 []
    pix_5by5_24 []
    pix_5by5_34 []
    pix_5by5_44 []
    
}

shape M_5by5
{
    pix_5by5_00 []
    pix_5by5_01 []
    pix_5by5_02 []
    pix_5by5_03 []
    pix_5by5_04 []
    pix_5by5_40 []
    pix_5by5_41 []
    pix_5by5_42 []
    pix_5by5_43 []
    pix_5by5_44 []
    pix_5by5_10 []
    pix_5by5_21 []
    pix_5by5_30 []
}

shape N_5by5
{
    pix_5by5_00 []
    pix_5by5_01 []
    pix_5by5_02 []
    pix_5by5_03 []
    pix_5by5_04 []
    pix_5by5_40 []
    pix_5by5_41 []
    pix_5by5_42 []
    pix_5by5_43 []
    pix_5by5_44 []
    pix_5by5_11 []
    pix_5by5_22 []
    pix_5by5_33 []
}


shape O_5by5
{
    pix_5by5_01 []
    pix_5by5_02 []
    pix_5by5_03 []
    pix_5by5_41 []
    pix_5by5_42 []
    pix_5by5_43 []
    pix_5by5_10 []
    pix_5by5_20 []
    pix_5by5_30 []
    pix_5by5_14 []
    pix_5by5_24 []
    pix_5by5_34 []
}

shape P_5by5
{
    pix_5by5_01 []
    pix_5by5_02 []
    pix_5by5_03 []
    pix_5by5_04 []
    pix_5by5_00 []
    pix_5by5_10 []
    pix_5by5_12 []
    pix_5by5_20 []
    pix_5by5_22 []
    pix_5by5_30 []
    pix_5by5_32 []
    pix_5by5_41 []
}

shape Q_5by5
{
    pix_5by5_01 []
    pix_5by5_02 []
    pix_5by5_03 []
    pix_5by5_10 []
    pix_5by5_14 []
    pix_5by5_20 []
    pix_5by5_24 []
    pix_5by5_22 []
    pix_5by5_30 []
    pix_5by5_33 []
    pix_5by5_41 []
    pix_5by5_42 []
    pix_5by5_44 []
    
}

shape R_5by5
{
    P_5by5[]
    pix_5by5_33 []
    pix_5by5_44 []
}

shape S_5by5
{
    pix_5by5_01 []
    pix_5by5_04 []
    pix_5by5_10 []
    pix_5by5_12 []
    pix_5by5_14 []
    pix_5by5_20 []
    pix_5by5_24 []
    pix_5by5_22 []
    pix_5by5_30 []
    pix_5by5_34 []
    pix_5by5_32 []
    pix_5by5_40 []
    pix_5by5_43 []
    
}

shape T_5by5
{
    pix_5by5_00 []
    pix_5by5_10 []
    pix_5by5_20 []
    pix_5by5_30 []
    pix_5by5_40 []
    pix_5by5_21 []
    pix_5by5_22 []
    pix_5by5_23 []
    pix_5by5_24 []
}

shape U_5by5
{
    pix_5by5_00 []
    pix_5by5_01 []
    pix_5by5_02 []
    pix_5by5_03 []
    pix_5by5_14 []
    pix_5by5_24 []
    pix_5by5_34 []
    pix_5by5_40 []
    pix_5by5_41 []
    pix_5by5_42 []
    pix_5by5_43 []
}

shape V_5by5
{
    pix_5by5_00 []
    pix_5by5_01 []
    pix_5by5_02 []
    pix_5by5_13 []
    pix_5by5_24 []
    pix_5by5_33 []
    pix_5by5_40 []
    pix_5by5_41 []
    pix_5by5_42 []
}

shape W_5by5
{
    M_5by5 [rotate 180]
}

shape X_5by5
{
    pix_5by5_00 []
    pix_5by5_04 []
    pix_5by5_11 []
    pix_5by5_13 []
    pix_5by5_22 []
    pix_5by5_31 []
    pix_5by5_33 []
    pix_5by5_40 []
    pix_5by5_44 []
}

shape Y_5by5
{
    pix_5by5_00 []
    pix_5by5_11 []
    pix_5by5_22 []
    pix_5by5_31 []
    pix_5by5_23 []
    pix_5by5_24 []
    pix_5by5_40 []
}

shape Z_5by5
{
    N_5by5 [rotate 90]
}

shape RANDOM_LETTER_5by5
rule { A_5by5 []}
rule { B_5by5 []}
rule { C_5by5 []}
rule { D_5by5 []}
rule { E_5by5 []}
rule { F_5by5 []}
rule { G_5by5 []}
rule { H_5by5 []}
rule { I_5by5 []}
rule { J_5by5 []}
rule { K_5by5 []}
rule { L_5by5 []}
rule { M_5by5 []}
rule { N_5by5 []}
rule { O_5by5 []}
rule { P_5by5 []}
rule { Q_5by5 []}
rule { R_5by5 []}
rule { S_5by5 []}
rule { T_5by5 []}
rule { U_5by5 []}
rule { V_5by5 []}
rule { W_5by5 []}
rule { X_5by5 []}
rule { Y_5by5 []}
rule { Z_5by5 []}

//generate numbers randomly
shape RANDOM_NUMBER_5by5
rule { NUM_0_5by5 [] }
rule { NUM_1_5by5 [] }
rule { NUM_2_5by5 [] }
rule { NUM_3_5by5 [] }
rule { NUM_4_5by5 [] }
rule { NUM_5_5by5 [] }
rule { NUM_6_5by5 [] }
rule { NUM_7_5by5 [] }
rule { NUM_8_5by5 [] }
rule { NUM_9_5by5 [] }

shape RANDOM_ALNUM_5by5
rule 26 { RANDOM_LETTER_5by5 [] }
rule 10 { RANDOM_NUMBER_5by5 [] }


shape NUM_0_5by5
{
    //make 0
    
    pix_5by5_10 []
    pix_5by5_20 []
    pix_5by5_30 []
    pix_5by5_01 []
    pix_5by5_02 []
    pix_5by5_03 []
    pix_5by5_41 []
    pix_5by5_42 []
    pix_5by5_43 []
    pix_5by5_14 []
    pix_5by5_24 []
    pix_5by5_34 []
    pix_5by5_31 []
    pix_5by5_22 []
    pix_5by5_13 []
}

shape NUM_1_5by5
{
    //make 1
    
    pix_5by5_20 []
    pix_5by5_21 []
    pix_5by5_22 []
    pix_5by5_23 []
    pix_5by5_24 []
    pix_5by5_04 []
    pix_5by5_14 []
    pix_5by5_34 []
    pix_5by5_44 []
    pix_5by5_01 []
    pix_5by5_10 []
}

shape NUM_2_5by5
{
    //make 2
    pix_5by5_20 []
    pix_5by5_30 []
    pix_5by5_41 []
    pix_5by5_32 []
    pix_5by5_22 []
    pix_5by5_22 []
    pix_5by5_04 []
    pix_5by5_14 []
    pix_5by5_24 []
    pix_5by5_34 []
    pix_5by5_44 []
    pix_5by5_13 []
    pix_5by5_01 []
    pix_5by5_10 []
}

shape NUM_3_5by5
{
    //make 3
    pix_5by5_20 []
    pix_5by5_30 []
    pix_5by5_41 []
    pix_5by5_32 []
    pix_5by5_22 []
    pix_5by5_22 []
    pix_5by5_03 []
    pix_5by5_14 []
    pix_5by5_24 []
    pix_5by5_34 []
    pix_5by5_43 []
    pix_5by5_01 []
    pix_5by5_10 []
}

shape NUM_4_5by5
{
    //make 4
    pix_5by5_01 []
    pix_5by5_02 []
    pix_5by5_03 []
    pix_5by5_10 []
    pix_5by5_13 []
    pix_5by5_23 []
    pix_5by5_30 []
    pix_5by5_31 []
    pix_5by5_32 []
    pix_5by5_33 []
    pix_5by5_34 []
    pix_5by5_43 []
}

shape NUM_5_5by5
{
    //make 5
    
    pix_5by5_00 []
    pix_5by5_01 []
    pix_5by5_02 []
    pix_5by5_04 []
    pix_5by5_10 []
    pix_5by5_12 []
    pix_5by5_14 []
    pix_5by5_20 []
    pix_5by5_22 []
    pix_5by5_24 []
    pix_5by5_30 []
    pix_5by5_32 []
    pix_5by5_34 []
    pix_5by5_43 []
}

shape NUM_6_5by5
{
    //make 6
    pix_5by5_01 []
    pix_5by5_02 []
    pix_5by5_03 []
    pix_5by5_10 []
    pix_5by5_12 []
    pix_5by5_14 []
    pix_5by5_20 []
    pix_5by5_22 []
    pix_5by5_24 []
    pix_5by5_30 []
    pix_5by5_32 []
    pix_5by5_34 []
    pix_5by5_43 []
}

shape NUM_7_5by5
{
    //make 7
    
    pix_5by5_00 []
    pix_5by5_10 []
    pix_5by5_20 []
    pix_5by5_23 []
    pix_5by5_24 []
    pix_5by5_32 []
    pix_5by5_30 []
    pix_5by5_40 []
    pix_5by5_41 []
}

shape NUM_8_5by5
{
    //make 8
    pix_5by5_01 []
    pix_5by5_03 []
    pix_5by5_10 []
    pix_5by5_12 []
    pix_5by5_14 []
    pix_5by5_20 []
    pix_5by5_22 []
    pix_5by5_24 []
    pix_5by5_30 []
    pix_5by5_32 []
    pix_5by5_34 []
    pix_5by5_43 []
    pix_5by5_41 []
}

shape NUM_9_5by5
rule {
    //make 9
    pix_5by5_01 []
    pix_5by5_04 []
    pix_5by5_10 []
    pix_5by5_12 []
    pix_5by5_14 []
    pix_5by5_20 []
    pix_5by5_22 []
    pix_5by5_24 []
    pix_5by5_30 []
    pix_5by5_32 []
    pix_5by5_34 []
    pix_5by5_41 []
    pix_5by5_42 []
    pix_5by5_43 []
}
)&&&" },
    { "i_polygons.cfdg", R"&&&(startshape polygontest

// This is kind of a dumb way to define a general regular polygon path.
// But it matches the existing polygon shapes.
path polygon(number sides) {
    MOVETO(	 0.5*cos(180/sides),
           -0.5*sin(180/sides))
    loop sides - 1 [r (360/sides)]
    LINETO(	0.5*cos(180/sides),
           0.5*sin(180/sides))
    CLOSEPOLY()
    FILL[]
}

shape polygontest
{
    polygonRightTriangle []
    CIRCLE [x 2]
    SQUARE [size 1.0 0.1 x 4 rotate 45]
    TRIANGLE [x 6]
    SQUARE [x 8]
    polygon5sided [x 0 y 2]
    polygon6sided [x 2 y 2]
    polygon7sided [x 4 y 2]
    polygon8sided [x 6 y 2]
    polygon9sided [x 8 y 2]
    polygon10sided [x 0 y 4]
    polygon11sided [x 2 y 4]
    polygon12sided [x 4 y 4]
    polygon13sided [x 6 y 4]
    polygon14sided [x 8 y 4]
    polygon15sided [x 0 y 6]
    polygon16sided [x 2 y 6]
    polygon17sided [x 4 y 6]
    polygon18sided [x 6 y 6]
    polygon19sided [x 8 y 6]
    polygon20sided [x 0 y 8]
    polygon21sided [x 2 y 8]
    polygon22sided [x 4 y 8]
    polygon23sided [x 6 y 8]
    polygon24sided [x 8 y 8]
}

// This is a unit right triangle
shape polygonRightTriangle
{
    TRIANGLE [[ size 1 1.155 x 0.165 y -0.144 skew 30 0 ]]
}


shape polygon5sided
{
    polygon(5)[]
    loop 5 [r 72] SQUARE [[rotate 0 size 0.404509 0.587785 x 0.5]]
}

shape polygon6sided
{
    loop 3 [r 60] SQUARE [[rotate 0 size 0.866025 0.5]]
}

shape polygon7sided
{
    loop 7 [r 51.4286] SQUARE [[rotate 0 size 0.450484 0.433884 x 0.5]]
}

shape polygon8sided
{
    loop 4 [r 45] SQUARE [[rotate 0 size 0.92388 0.382683]]
}

shape polygon9sided
{
    loop 9 [r 40] SQUARE [[rotate 0 size 0.469846 0.34202 x 0.5]]
}

shape polygon10sided
{
    loop 5 [r 36] SQUARE [[rotate 0 size 0.951057 0.309017]]
}

shape polygon11sided
{
    loop 11 [r 32.7273] SQUARE [[rotate 0 size 0.479746 0.281733 x 0.5]]
}

shape polygon12sided
{
    loop 6 [r 30] SQUARE [[rotate 0 size 0.965926 0.258819]]
}

shape polygon13sided
{
    loop 13 [r 27.6923] SQUARE [[rotate 0 size 0.485471 0.239316 x 0.5]]
}

shape polygon14sided
{
    loop 7 [r 25.7143] SQUARE [[rotate 0 size 0.974928 0.222521]]
}

shape polygon15sided
{
    loop 15 [r 24] SQUARE [[rotate 0 size 0.489074 0.207912 x 0.5]]
}

shape polygon16sided
{
    loop 8 [r 22.5] SQUARE [[rotate 0 size 0.980785 0.19509]]
}

shape polygon17sided
{
    loop 17 [r 21.1765] SQUARE [[rotate 0 size 0.491487 0.18375 x 0.5]]
}

shape polygon18sided
{
    loop 9 [r 20] SQUARE [[rotate 0 size 0.984808 0.173648]]
}

shape polygon19sided
{
    loop 19 [r 18.9474] SQUARE [[rotate 0 size 0.493181 0.164595 x 0.5]]
}

shape polygon20sided
{
    loop 10 [r 18] SQUARE [[rotate 0 size 0.987688 0.156434]]
}

shape polygon21sided
{
    loop 21 [r 17.1429] SQUARE [[rotate 0 size 0.494415 0.149042 x 0.5]]
}

shape polygon22sided
{
    loop 11 [r 16.3636] SQUARE [[rotate 0 size 0.989821 0.142315]]
}

shape polygon23sided
{
    loop 23 [r 15.6522] SQUARE [[rotate 0 size 0.495343 0.136167 x 0.5]]
}

shape polygon24sided
{
    loop 12 [r 15] SQUARE [[rotate 0 size 0.991445 0.130526]]
}
)&&&" },
    { "lesson.cfdg", R"&&&(/* CFDG Lesson */

startshape TOC
// each grammar file must
// have a "startshape"
// statement to say which
// shape to begin with

shape TOC
{
    // a "rule" statement says how
    // to compose a shape out of
    // other shapes
    
    CHAPTER1 [ x 0 y 0 ]
    CHAPTER2 [ x 10 y 0 ]
    CHAPTER3 [ x 0 y -10 ]
    CHAPTER4 [ x 10 y -10 ]
    // each entry in the rule
    // names a shape to draw and
    // some "adjustments" in curly
    // braces
    
    TITLES [ ]
}

shape CHAPTER1
{
## BASIC SHAPES ##
    SQUARE [ x 2 y 5 size 3 ]
    CIRCLE [ x 6 y 5 size 3 ]
    TRIANGLE [ x 4 y 2 size 3 ]
    // these shapes are special:
    // they draw a shape into the
    // image, centered at the
    // current location
    SHAPES [ y 1 size 3 ]
    // This tells you the relative
    // sizes and positions of each
    // basic shape.
}

shape SHAPES
{
    SQUARE []
    CIRCLE [b 0.3]
    TRIANGLE [b 0.5]
    TRIANGLE [r 60 b 0.7]
}

shape CHAPTER2
{
## BASIC ADJUSTMENTS ##
    SQUARE [ ]
    // empty adjustments
    // this is the lone square in
    // chapter 2's area
    
    SQUARE [ x 3 y 7 ]
    // adjust location
    
    // even though adjustments
    // are written after the shape
    // they are applied before!
    
    SQUARE [ x 5 y 7 rotate 30 ]
    // adjust rotation
    SQUARE [ x 3 y 5 size 0.75 ]
    // adjust size
    
    // notice that rotaion and size
    // are adjusted after location
    
    SQUARE [ x 5 y 5
            brightness 0.5 ]
    // adjust brightness
    
    SQUARE [ x 7 y 6
            // shorthands:
            r 45 // for rotate
            s 0.7 // for size
            b 0.7 // for brightness
            ]
    
    FOURSQUARE [ x 5 y 1
                size 0.2 rotate 10 ]
    // adjustments are cumulative
}
shape FOURSQUARE
{
    SQUARE [ x 0 y 0 size 5  3]
    SQUARE [ x 0 y 5 size 2 4 ]
    SQUARE [ x 5 y 5 size 3 ]
    SQUARE [ x 5 y 0 size 2 ]
    // even though these are
    // at locations and sizes
    // that seem big, they have
    // all been relocated, scaled
    // and rotated when the rule
    // for CHAPTER2 used
    // FOURSQUARE
    // Two SQUAREs have been
    // have been turned into
    // rectangles
}

shape CHAPTER3
{
## RECURSION ##
    SPIRAL [ x 0 y 3 ]
}
shape SPIRAL
{
    CIRCLE [ size 0.5 ]
    SPIRAL [ y 0.2
            rotate -3
            size 0.995 ]
    // a shape can use itself so
    // long as it keeps getting
    // smaller
    
    // the system will stop the
    // recursion when the shapes
    // get to small to see
}

shape CHAPTER4
{
## RANDOMNESS ##
    TREE [ x 1 y 0 ]
    TREE [ x 6 y 0 ]
    TREE [ x 1 y 4 ]
    TREE [ x 6 y 4 ]
    // even though these are the
    // same shape used four
    // times, each looks different
}
shape TREE
rule 20 {
    // first rule for TREE
    CIRCLE [ size 0.25 ]
    TREE [ y 0.1 size 0.97 ]
}
rule 1.5 {
    // second rule for TREE
    BRANCH [  ]
}
// When expanding a TREE, a
// rule is picked randomly.
// The first rule has been given a
// weight of 20, the second of 1.5,
// so the first will be picked
// proportionally more often

shape BRANCH
{
    BRANCH_LEFT [ ]
    BRANCH_RIGHT [ ]
}
shape BRANCH_LEFT
rule {
    TREE [ rotate 20 ]
}
rule {
    TREE [ rotate 30 ]
}
rule {
    TREE [ rotate 40 ]
}
rule {
    // empty rules are okay
}
// If no weight is given for a rule
// the weight is 1.  Hence, the
// above four rules are picked
// equally randomly

shape BRANCH_RIGHT
rule {
    TREE [ rotate -20 ]
}
rule {
    TREE [ rotate -30 ]
}
rule {
    TREE [ rotate -40 ]
}
rule {
    // empty rules are okay
}



## Utilities ##
import i_pix.cfdg
// The "include" statement reads
// in all the rules from another file.
// Any "startshape" in the included
// file is ignored.

shape TITLES
{
    TITLE1 [ x 0 y 8.5 ]
    TITLE2 [ x 10 y 8.5 ]
    TITLE3 [ x 0 y -1.5 ]
    TITLE4 [ x 10 y -1.5 ]
}
shape TITLE1
{
    O_5by5 [ x 0 ]
    N_5by5 [ x 1.2 ]
    E_5by5 [ x 2.4 ]
}
shape TITLE2
{
    T_5by5 [ x 0 ]
    W_5by5 [ x 1.2 ]
    O_5by5 [ x 2.4 ]
}
shape TITLE3
{
    T_5by5 [ x 0 ]
    H_5by5 [ x 1.2 ]
    R_5by5 [ x 2.4 ]
    E_5by5 [ x 3.6 ]
    E_5by5 [ x 4.8 ]
}
shape TITLE4
{
    F_5by5 [ x 0 ]
    O_5by5 [ x 1.2 ]
    U_5by5 [ x 2.4 ]
    R_5by5 [ x 3.6 ]
}
)&&&" },
    { "lesson2.cfdg", R"&&&(/* CFDG Lesson */

startshape TOC

shape TOC
{
    CHAPTER5 [ x 0 y 0 ]
    CHAPTER6 [ x 10 y 0 ]
    CHAPTER7 [ x 0 y -10 ]
    CHAPTER8 [ x 10 y -10 ]
    
    TITLES [ ]
}

shape CHAPTER5
{
## SKEW TRANSFORM ##
    SierpinskiTri [ x 2 y 4 size 6.0 ]
    SQUARE [ x 0.5 y 5.5 skew 15 15 size 2 ]
    // a skew transform (also called
    // a shear) pushes a shape parallel
    // to the x axis or y axis or both.
    // The two numbers following
}

shape SierpinskiTri
{
    polygonRightTriangle [ ]
    hole [ b 1 ]
}

shape hole
{
    polygonRightTriangle [ size -0.495 x 0.25 y -0.25 ]
    hole [ b -0.2 size 0.5 x -0.25 y -0.25 ]
    hole [ b -0.2 size 0.5 x  0.25 y -0.25 ]
    hole [ b -0.2 size 0.5 x  0.25 y  0.25 ]
}

shape polygonRightTriangle
{
    TRIANGLE [[ size 1 1.155 x 0.165 y -0.144 skew 30 0 ]]
}

shape CHAPTER6
{
## FLIP TRANSFORM ##
    HEART [ x 2 y 1 size 0.12 0.1]
    // A flip transform reflects a
    // shape across a line at the
    // specified angle.
}

import i_curves.cfdg

shape HEART
{
    curveright_0_99_1 [ r 64 ]
    curveright_0_99_1 [ flip 90 r -64 ]
    HEART [ s 0.9 y 2.5 ]
}

shape CHAPTER7
{
## TRANSFORM ORDERING ##
    TranSquare [ s 0.5 x 1 y 5 ]
    TranCircle [ s 0.5 x 1 y 3 ]
    TranTriangle [ s 0.5 x -1 y 1 ]
    SquareLine [ x -1 y 7 ]
    // When transforms are in curly
    // braces then they are applied
    // in a fixed order:
    // 1) Translate
    // 2) Rotate
    // 3) Scale
    // 4) Skew
    // 5) Reflect
    // Only one transform of each
    // type is allowed (all but the
    // last are ignored).
    
    // When transforms are in square
    // braces then they are applied
    // in the order they are found
    // and there can be multiple
    // occurances of a given type
    // of transform.
}

shape TranSquare
{
    SQUARE [[ r 45 x 4 s 3 ]]
    SQUARE [[ b 0.2 x 4 s 3 ]]
    SQUARE [[ b 0.4 x 4 ]]
    SQUARE [[ b 0.7 ]]
    // Ordering a rotate before a
    // translate (x or y) causes the
    // translate to be rotated. This
    // saves
}
shape TranCircle
{
    Ellipse [[ x 4 r 45 s 3 ]]
    Ellipse [[ b 0.2 r 45 s 3 ]]
    Ellipse [[ b 0.4 s 3  ]]
    Ellipse [[ b 0.7 ]]
    // This happens to be the order
    // that CF uses when the transforms
    // are enclosed in curly braces.
}
shape TranTriangle
{
    TRIANGLE [[ s 3 x 4 r 45 ]]
    TRIANGLE [[ b 0.2 x 4 r 45 ]]
    TRIANGLE [[ b 0.4 r 45 ]]
    TRIANGLE [[ b 0.7 ]]
    // Putting the scale before the
    // translate scales the translate
    // as well
}
shape SquareLine
{
    SQUARE []
    SquareLine [[ y -0.5 s 0.75 y -0.5 ]]
    // Transforms can be specified
    // more than once and subsequent
    // transforms are modifed by the
    // ones before them. In the above
    // idiom the squares are always
    // just touching, even when you
    // change the scale amount.
}
shape Ellipse
{
    CIRCLE [ s 1 0.5 ]
}



shape CHAPTER8
{
## COLOR ##
    // Coming soon.
}



## Utilities ##
import i_pix.cfdg
// The "include" statement reads
// in all the rules from another file.
// Any "startshape" in the included
// file is ignored.

shape TITLES
{
    TITLE5 [ x 0 y 8.5 ]
    TITLE6 [ x 10 y 8.5 ]
    TITLE7 [ x 0 y -1.5 ]
    TITLE8 [ x 10 y -1.5 ]
}
shape TITLE5
{
    F_5by5 [ x 0 ]
    I_5by5 [ x 1.2 ]
    V_5by5 [ x 2.4 ]
    E_5by5 [ x 3.6 ]
}
shape TITLE6
{
    S_5by5 [ x 0 ]
    I_5by5 [ x 1.2 ]
    X_5by5 [ x 2.4 ]
}
shape TITLE7
{
    S_5by5 [ x 0 ]
    E_5by5 [ x 1.2 ]
    V_5by5 [ x 2.4 ]
    E_5by5 [ x 3.6 ]
    N_5by5 [ x 4.8 ]
}
shape TITLE8
{
    E_5by5 [ x 0 ]
    I_5by5 [ x 1.2 ]
    G_5by5 [ x 2.4 ]
    H_5by5 [ x 3.6 ]
    T_5by5 [ x 4.8 ]
}
)&&&" },
    { "mtree.cfdg", R"&&&(startshape PLANT

shape PLANT
{
    EITHER [x -2]
    EITHER [x 2]
}

shape BOTH
{
    BL [rotate 30]
    BL [rotate -30 flip 90]
}

shape EITHER
rule {BL[]}
rule {BL[flip 90]}

shape BL
{
    CIRCLE []
    WL [size 0.95 y 1.6]
}

shape WL
rule 10 {BL [rotate randint(3, 8)]}
rule {BOTH []}
rule {BL [rotate -10 flip 90]}

)&&&" },
    { "octopi.cfdg", R"&&&(startshape family

shape family
{
    octopus []
    family [x 10 y 2 s 0.3 r -10]
    family [x 0 y 10 s 0.3 r 10]
    
}

shape octopus
{
    octopus_leg1 [r 90 s 0.7]
    octopus_leg1 [r 100]
    octopus_leg1 [r 80]
    octopus_leg1 [r 110]
    octopus_leg1 [r 180 s 0.7 flip 90]
    octopus_leg1 [r 190 flip 90]
    octopus_leg1 [r 170 flip 90]
    octopus_leg1 [r 200 flip 90]
    CIRCLE [s 5 x 2 y 2]
    CIRCLE [s 5 x 2.5 y 2.5]
    CIRCLE [s 5 x 3 y 3]
    CIRCLE [b 1 x 1 y 3]
    CIRCLE [b 1 x 3 y 2]
    CIRCLE [s 0.7 x 1.1 y 2.9]
    CIRCLE [s 0.7 x 2.9 y 1.9]
}

shape octopus_leg1
{
    unit []
    octopus_leg1 [x 1 y 1 r 10 s 0.95]
    octopus_leg1 [s 0.2 x 1 y 1 r 90]
}

shape unit
{
    seed []
    seed [r 90]
}

shape seed
{
    CIRCLE [x -0.5]
    SQUARE []
    CIRCLE [x 0.5]
}
)&&&" },
    { "quadcity.cfdg", R"&&&(startshape WHOLE

shape WHOLE
{
    QUAD [ x -0.5 y -0.5 ]
    QUAD [ x  0.5 y -0.5 ]
    QUAD [ x  0.5 y  0.5 ]
    QUAD [ x -0.5 y  0.5 ]
}

shape QUAD
rule {
    FILLIT [ ]
}
rule 5 {
    WHOLE [ size 0.45 r 2 ]
}
rule 0.5 {
    // nothing
}

shape FILLIT
{
    SQUARE [
            size 0.8
            ]
}
)&&&" },
    { "rose.cfdg", R"&&&(startshape plant

shape rose1
{
    loop 4 [r 90] petal [r -15…15 x 0.9 s 0.9 1.8]
    rose1 [ r 14 s 0.92 hue 0.12 60  ]
}


shape petal
{
    CIRCLE []
    CIRCLE [ s 0.975 x -0.025 hue 0.1 60  ]
    CIRCLE [ s 0.95 x -0.05 hue 0.2 60  ]
    CIRCLE [ s 0.925 x -0.075 hue 0.3 60  ]
    CIRCLE [ s 0.90 x -0.10 hue 0.4 60  ]
}

shape stem
{
    CIRCLE [s 2 6 r -15 y -3 x -.5]
    CIRCLE [s 2 6 r -15 y -3 x -0.35 sat -1 b 1]
    leaf [[ y -4 x -1.625 r 30 s 0.15 ]]
    leaf [[ y -4 x -1.625 flip 80 r 30 s 0.15 ]]
}

shape plant
{
    rose1 [ b 1 sat 1]
    stem [ b 0.4 sat 1 hue 120 z -1]
}

shape leaf
{
    loop 4 [[y 0.5 s 0.95 y 0.5 r 1]]
    SQUARE []
    finally {
        CIRCLE [[r 7 s 7.5 15 y 0.5]]
        CIRCLE [[r 7 s 7.5 15 b 0.2 y 0.5 s 0.80 0.90]]
        leaf []
    }
}
)&&&" },
    { "sierpinski.cfdg", R"&&&(startshape Top

shape Top
{
    Sierpinski [ r -13.5 b 0.5 ]
}

shape SierpinskiOrig
{
    Shape [ ]
    Sierpinski [ s 0.5 r 5
                y -1 x 0  ]
    Sierpinski [  s 0.5 r 5
                y 0.5 x -0.866025  ]
    Sierpinski [ s 0.5 r 5
                y 0.5 x 0.866025  ]
}
shape Sierpinski
{
    Shape [ ]
    Sierpinski [ s 0.6 r 5 b 0.2
                y -1.5 x 0  ]
    Sierpinski [  s 0.6 r 5 b -0.2
                y 0.75 x -1.2990375  ]
    Sierpinski [ s 0.6 r 5
                y 0.75 x 1.2990375  ]
}

# comment out all but one of these rules for Shape:
shape Shape
{ CIRCLE [ ] }
#rule Shape { Triangle { s 0.5 } }
#rule Shape { Triangle { } }
// this last one fills the image

shape Triangle
{
    Arm [ r 0 ]
    Arm [ r 120 ]
    Arm [ r -120 ]
}

shape Arm
{
    CIRCLE [ ]
    Arm [ y 0.1 s 0.9 ]
}
)&&&" },
    { "snowflake.cfdg", R"&&&(startshape SPIKE

CF::Symmetry = CF::Dihedral, 6

shape SPIKE
rule {
    SQUARE []
    SPIKE [y 0.95 s 0.97]
}
rule 0.03 {
    SQUARE []
    SPIKE [r 60]
    SPIKE [r -60]
    SPIKE [y 0.95 s 0.97]
}
)&&&" },
    { "tangle.cfdg", R"&&&(startshape SPIKES

shape SPIKES
{
    loop 4 [r 90] SPIKE []
}

shape SPIKE
rule {
    LSPIKE []
}
rule {
    LSPIKE [ flip 90 ]
}

shape LSPIKE
rule {
    SQUARE []
    LSPIKE [ y 0.98 s 0.99 r 1]
}
rule 0.01 {
    SPIKE [ r 90 ]
    SPIKE [ r -90 ]
    LSPIKE [ y 0.98 s 0.99  r 1]
}
)&&&" },
    { "triples.cfdg", R"&&&(startshape TRIPLES

shape TRIPLES
{
    LINES [ r 0 ]
    LINES [ r 120 ]
    LINES [ r -120 ]
}	

shape LINES
{
    UTRIANGLE [ y 0.5 ]
    LINES [ r 20 b 0.15 y 0.75 x -0.4330125  s 0.754877 ]
    LINER [ r -60 b 0.15 y 0.75 x 0.4330125  s 0.754877 ]
}

shape LINER
{
    UTRIANGLE [ y 0.5 ]
    LINER [ r -15…-6 b 0.02
           y 0.75 x 0.4330125  s 0.754877 ]
}

// 0.754877 is the solution to
// x^2 + x^3 = 1
// this allows double backed
// triangles to exactly line up!


shape TESTU
{
    TESTU_background [ ]
    UTRIANGLE [ ]
    UTRIANGLE [ y 0.5 x -0.866025 b 0.5 r 60 ]
    UTRIANGLE [ y 0.5 x +0.866025 b 0.5 r 60 ]
}
shape TESTU_background
{
    CIRCLE [  b 0.5 ]
    CIRCLE  [ y -1 ]
    CIRCLE [ y -0.5 x -0.866025 ]
    CIRCLE [ y -0.5 x 0.866025 ]
    CIRCLE [ y 0.5 x -0.866025 ]
    CIRCLE [ y 0.5 x 0.866025 ]
    CIRCLE  [ y 1 ]
}

shape UTRIANGLE
{
    transform [ r 42.5 s 0.525 ] {
        ARM [ r 0 ]
        ARM [ r 120 ]
        ARM [ r -120 ]
    }
}

shape ARM
{
    CIRCLE [ ]
    ARM [ y 0.1 s 0.9 r 2 ]
}
)&&&" },
    { "underground.cfdg", R"&&&(startshape MAP

shape MAP
{
    LOGO [ ]
    ROUTE [ x 80 y 80 rotate 90 ]
}

shape ROUTE
rule {
    LINES [ brightness 0.2 ]
}
rule {
    LINES [ brightness -0.2 ]
}
shape LINES
{
    LINE [ ]
    LINE [ rotate 180 ]
}

shape LINE
rule 1000 {
    CIRCLE [ ]
    LINE [ y 0.1 ]
}
// turns
rule 1 { LINE [ rotate 45 ] }
rule 1 { LINE [ rotate -45 ] }
rule 1 { LINE [ rotate 90 ] }
rule 1 { LINE [ rotate -90 ] }

// station
rule 4 {
    SQUARE [
            size 3
            rotate 45
            ]
    LINE [ ]
}

// interchange
rule 0.5 {
    LINE [ ]
    ROUTE [ rotate 90 ]
}

// terminus
rule 1 {
    CIRCLE [ size 3 ]
    CIRCLE [ size 1
            brightness 1 ]
}

shape LOGO
{
    CIRCLE [
            size 5
            brightness 0.5
            ]
    CIRCLE [
            size 3.5
            brightness 1.0
            ]
    SQUARE [ s 6 1 ]
}
)&&&" },
    { "weighting_demo.cfdg", R"&&&(startshape SEED1

shape SEED1
rule {
    SQUARE[]
    SEED1 [y 1.2 size 0.99 rotate 1.5 brightness 0.03]
}

rule 0.05 {SEED1 [flip 90]}

rule 0.05 {
    SQUARE[]
    SEED1 [y 1.2 s 0.99 r 1.5 b -0.5 flip 90]
    SEED1 [y 1.2 x 1.2 s 0.6 r -60 b -0.5]
    SEED1 [y 1.2 x -1.2 s 0.5 r 60 b -0.5 flip 90]
}

)&&&" },
    { "welcome.cfdg", R"&&&(startshape WELCOME

shape WELCOME
{
    MESSAGE [ hue 225 sat 0.7 b 0.6 ]
    VINEL [ sat 1 hue 120
           x 3 y -55
           r 0 b 0.5 s 10
           ]
    VINEL [ flip 90
           sat 1 hue 120
           x 85 y -55
           r 0 b 0.5 s 10
           ]
}

shape MESSAGE
{
    W [ x 0 ]
    E [ x 12 ]
    L [ x 24 ]
    C [ x 34 ]
    O [ x 46 ]
    M [ x 64 ]
    E [ x 80 ]
}

shape W
{
    LINE [ r -7 ]
    LINE [ r 7 ]
    LINE [ x 6 r -7 ]
    LINE [ x 6 r 7 ]
}

shape E
{
    LINE [ s 0.9 ]
    LINE [ s 0.9 -1 y 24 ]
    LINE [ s 0.4 r -90 y 0 ]
    LINE [ s 0.4 r -90 y 12 ]
    LINE [ s 0.4 r -90 y 24 ]
}

shape L
{
    LINE [ ]
    LINE [ s 0.4 x 0.4 r -90 y 0 ]
}

shape C
{
    ARCL [ y 12 flip 90 ]
    ARCL [ y 12 r 180 ]
}

shape O
{
    ARCL [ y 12 flip 90]
    ARCL [ y 12 r 180 ]
    ARCL [ y 12 x 14 r 180 flip 90]
    ARCL [ y 12 x 14 ]
}

shape M
{
    LINE [ y 24 r 180 ]
    LINE [ y 24 r  -160 s 0.75 ]
    LINE [ y 24 x 12 r 160 s 0.75 ]
    LINE [ y 24 x 12 r 180 ]
}

shape LINE
{
    TRIANGLE [[ s 1 30 y 0.26 ]]
    //MARK { }
    //LINE { size 0.98 y 0.5 }
}

shape ARCL
{
    MARK [ ]
    ARCL [ size 0.97 y 0.55 r 1.5 ]
}

shape MARK
{
    SQUARE [ ]
}


shape VINEL
{
    STEML [ ]
    STEML [ x 1 r 5 flip 0 ]
    VINEL [ x 2 size 0.9 r 10 ]
}

shape STEML
{
    GOL [ r 20 s 0.1 ]
    END [ s 0.2 r 120 hue 150
         x 1.3 y -0.6 b -0.3]
}
shape GOL
{
    CIRCLE [ ]
    GOL [ x 0.3 r -1 s 0.985 ]
}


shape END
{
    CIRCLE [ x -0.5 y 0.0 s 1.0 ]
    CIRCLE [ x 0.45 y 0.6 s 0.9 ]
    CIRCLE [ x -0.4 y 1.2 s 0.8 ]
    CIRCLE [ x 0.35 y 1.8 s 0.7 ]
    CIRCLE [ x -0.3 y 2.4 s 0.6 ]
}

)&&&" },
    { "ziggy.cfdg", R"&&&(startshape Trident

shape Trident
{
    ZigL [ x 0 b 0.02 ]
    Zig [ ]
    ZagL [ x 0 b 0.02 flip 90]
    CIRCLE [ x 10 y 10 s 6 b 0.75 ]
    CIRCLE [ x -10 y 10 s 6 b 0.75 ]
    //	CIRCLE { x 17 y 15 s 4 b 0.75 }
    //	CIRCLE { x -17 y 15 s 4 b 0.75 }
}

shape Zig
{
    Seg [ x -0.5 r -45 ]
    Zag [ y 1 s 0.97 ]
}
shape Zag
{
    Seg [ x 0.5 r 45 ]
    Zig [ y 1 s 0.97 ]
}

shape ZigL
{
    Seg [ x -0.5 r -45 ]
    ZagL [ y 1 s 0.97 r 2 ]
}
shape ZagL
{
    Seg [ x 0.5 r 45 ]
    ZigL [ y 1 s 0.97 r 2 ]
}

shape ZigL
rule 0.1 { Trident [ ] }

shape Seg
{
    SQUARE [ y 0.6925 s 0.5 1.885 ]
}
)&&&" }
};
