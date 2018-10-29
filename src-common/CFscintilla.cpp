// CFscintilla.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2018 John Horigan - john@glyphic.com
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

#include "CFscintilla.h"
#include <cctype>
#include <string>
#include <cstring>
#include <set>


std::vector<const char*> CFscintilla::AutoComplete = {
        "ARCREL", "ARCTO", "background", "bitand", "bitleft", "bitnot", "bitor", "bitright", "bitxor",
        "CF::Align", "CF::AllowOverlap", "CF::Alpha", "CF::ArcCW", "CF::ArcLarge", "CF::Background",
        "CF::BevelJoin", "CF::BorderDynamic", "CF::BorderFixed", "CF::ButtCap", "CF::cm", "CF::cmm", "CF::Color",
        "CF::ColorDepth", "CF::Continuous", "CF::Cyclic", "CF::Dihedral", "CF::EvenOdd", "CF::Frame",
        "CF::FrameTime", "CF::Impure", "CF::IsoWidth", "CF::MaxNatural", "CF::MaxShapes",
        "CF::MinimumSize", "CF::MiterJoin",
        "CF::p11g", "CF::p11m", "CF::p1m1", "CF::p2", "CF::p2mg", "CF::p2mm", "CF::p3", "CF::p3m1", "CF::p31m",
        "CF::p4", "CF::p4g", "CF::p4m", "CF::p6", "CF::p6m", "CF::pg", "CF::pgg", "CF::pm", "CF::pmg", "CF::pmm",
        "CF::RoundCap", "CF::RoundJoin", "CF::Size", "CF::SquareCap", "CF::StartShape", "CF::Symmetry", "CF::Tile", "CF::Time",
        "CIRCLE", "CLOSEPOLY", "CURVEREL", "CURVETO", "FILL", "import", "include", "LINEREL", "LINETO", "MOVEREL", "MOVETO", "SQUARE", "STROKE", "TRIANGLE",
        "rand", "rand::cauchy", "rand::chisquared", "rand::exponential", "rand::extremeV",
        "rand::fisherF", "rand::gamma", "rand::lognormal", "rand::normal", "rand::studentT", "rand::weibull",
        "randint", "randint::bernoulli", "randint::binomial", "randint::discrete",
        "randint::geometric", "randint::negbinomial", "randint::poisson", "rand_static", "startshape",
        "floor", "ceiling", "infinity", "factorial", "isNatural", "divides", "div",
        "dot", "cross", "hsb2rgb", "rgb2hsb"
    };

static size_t isUTF8op(const char* text)
{
    static const char* utf8ops[6] = {
        "\xe2\x80\xa6", "\xc2\xb1", "\xe2\x89\xa4", "\xe2\x89\xa5", "\xe2\x89\xa0", "\xe2\x88\x9e"
    };
    for (int op = 0; op < 6; ++op) {
        auto len = std::strlen(utf8ops[op]);
        if (std::strncmp(text, utf8ops[op], len) == 0)
            return len;
    }
    return 0;
}

CFscintilla::Style
CFscintilla::StyleLine(size_t length, const char* text, char* styles, Style initStyle)
{
    const unsigned char* utext = reinterpret_cast<const unsigned char*>(text);
    Style state = initStyle;
    size_t idStart = 0;
    bool afterColon = false;
    bool decimalPointFound = false;
    int digits = 0;
    for (size_t i = 0; i < length;) {
        switch (state) {
            // break == style current character and move on to next
            // continue == restart current character with a new state
            // It's always safe to read text[i+1] because of null termination
            case StyleDefault:
                if (std::isspace(utext[i])) {
                    styles[i] = StyleDefault;
                    break;
                }
                if (text[i] == '.' && text[i+1] == '.') {
                    styles[i] = styles[i+1] = StyleSymbol;
                    ++i;
                    break;
                }
                if ((text[i] == '.' && std::isdigit(utext[i+1])) || std::isdigit(utext[i])) {
                    decimalPointFound = false;
                    digits = 0;
                    state = StyleNumber;
                    continue;
                }
                if (size_t sz = isUTF8op(text + i)) {
                    for (size_t j = 0; j < sz; ++j)
                        styles[i+j] = StyleSymbol;
                    i += sz;
                    continue;   // don't break, i is already incremented
                }
                if ((utext[i] & 0x80) || std::isalpha(utext[i]) || text[i] == '_') {
                    idStart = i; afterColon = false;
                    state = StyleIdentifier;
                    continue;
                }
                if (text[i] == '#' || (text[i] == '/' && text[i+1] == '/')) {
                    // Style rest of line but leave EOL with default style
                    // to prevent wrapping of comment style
                    while (i < length && text[i] != '\n' && text[i] != '\r')
                        styles[i++] = StyleComment;
                    continue;
                }
                if (text[i] == '/' && text[i+1] == '*') {
                    state = StyleComment;
                    styles[i] = styles[i+1] = StyleComment;
                    ++i;
                    break;
                }
                if (text[i] == '"') {
                    state = StyleString;
                    styles[i] = StyleString;
                    break;
                }
                if (strchr("<>[]{}()+-*/|=^&@:;,!", utext[i])) {
                    styles[i] = StyleSymbol;
                    break;
                }
                styles[i] = StyleDefault;
                break;
            case StyleComment:
                styles[i] = StyleComment;
                if (text[i] == '*' && text[i+1] == '/') {
                    styles[++i] = StyleComment;
                    state = StyleDefault;
                }
                break;
            case StyleString:
                if (text[i] == '"') {
                    styles[i] = StyleString;
                    state = StyleDefault;
                    break;
                }
                if (text[i] == '\r' || text[i] == '\n') {
                    // EOL must be default styled to prevent string style wrapping
                    state = StyleDefault;
                    continue;
                }
                styles[i] = StyleString;
                break;
            case StyleNumber:
                if (std::isdigit(utext[i])) {
                    ++digits;
                    styles[i] = StyleNumber;
                    break;
                }
                if (text[i] == '.') {
                    if (decimalPointFound || text[i+1] == '.') {
                        // This is the start of another number or the .. operator
                        state = StyleDefault;
                        continue;
                    }
                    styles[i] = StyleNumber;
                    decimalPointFound = true;
                    break;
                }
                if ((text[i] == 'e' || text[i] == 'E') && (digits > 0)) {
                    if ((text[i+1] == '+' || text[i+1] == '-') && (i + 2 < length) &&
                        std::isdigit(utext[i+2]))
                    {
                        styles[i] = styles[i+1] = StyleNumber;
                        i += 2;     // style the e/E and +/-
                    } else if (std::isdigit(utext[i+1])) {
                        styles[i] = StyleNumber;
                        ++i;        // style the e/E
                    } else {
                        state = StyleDefault;
                        continue;   // e/E is not part of number
                    }
                    // style the exponent
                    while (i < length && std::isdigit(utext[i]))
                        styles[i++] = StyleNumber;
                    state = StyleDefault;
                    continue;       // don't break, i is already incremented
                }
                state = StyleDefault;
                continue;
            case StyleIdentifier:
                if (std::isdigit(utext[i]) && !afterColon) {
                    styles[i] = StyleIdentifier;
                    break;
                }
                if (text[i] == ':' && text[i+1] == ':') {
                    styles[i] = styles[i+1] = StyleIdentifier;
                    ++i;
                    afterColon = true;
                    break;
                }
                afterColon = false;
                if (((utext[i] & 0x80) && !isUTF8op(text + i)) ||
                    std::isalpha(utext[i]) || text[i] == '_')
                {
                    styles[i] = StyleIdentifier;
                    break;
                }
                if (i + 5 <= length && std::strncmp(text + i, ".cfdg", 5) == 0) {
                    // identifier will be restyled as a string
                    i += 5;
                }
                // Done with current identifier. Check if it is actually a
                // keyword, builtin, or cfdg file (string).
                StyleId(i - idStart, text + idStart, styles + idStart);
                state = StyleDefault;
                continue;
            default:
                // Should never happen, but the warnings are annoying
                styles[i] = state;
                break;
        }
        ++i;    // skipped if we continue
    }
    
    // If line ended w/o EOL and on an identifier then restyle the identifier
    if (state == StyleIdentifier)
        StyleId(length - idStart, text + idStart, styles + idStart);
    
    // Comment style is the only style that wraps
    return state == StyleComment ? StyleComment : StyleDefault;
}

void
CFscintilla::StyleId(size_t length, const char* text, char* styles)
{
    using stringSet = std::set<std::string>;
    static const stringSet keywords = {
        "a", "alpha",
        "b", "background", "brightness",
        "case", "clone",
        "else",
        "f", "finally", "flip",
        "h", "hue",
        "if", "import", "include",
        "let", "loop",
        "path",
        "r", "rotate", "rule",
        "s", "saturation", "sat", "size", "skew", "startshape", "shape",
        "tile", "time", "timescale", "trans", "transform",
        "x", "x1", "x2",
        "y", "y1", "y2",
        "z"
    };
    static const stringSet builtins = {
        "cos", "sin", "tan", "cot", "acos", "asin", "atan", "acot", "cosh", "sinh", "tanh", "acosh", "asinh", "atanh", "log", "log10",
        "sqrt", "exp", "abs", "floor", "ceiling", "infinity", "factorial", "sg", "isNatural", "bitnot", "bitor", "bitand", "bitxor",
        "bitleft", "bitright", "atan2", "mod", "divides", "div", "dot", "cross", "hsb2rgb", "rgb2hsb", "vec", "min", "max", "ftime",
        "frame", "rand_static", "rand", "rand::exponential", "rand::gamma", "rand::weibull", "rand::extremeV",
        "rand::normal", "rand::lognormal", "rand::chisquared", "rand::cauchy", "rand::fisherF",
        "rand::studentT", "randint", "randint::bernoulli", "randint::binomial", "randint::negbinomial",
        "randint::poisson", "randint::discrete", "randint::geometric",
        "CIRCLE", "SQUARE", "TRIANGLE", "FILL", "STROKE",
        "MOVETO", "LINETO", "ARCTO", "CURVETO", "MOVEREL", "LINEREL", "ARCREL", "CURVEREL", "CLOSEPOLY",
        "CF::None", "CF::MiterJoin", "CF::RoundJoin", "CF::BevelJoin", "CF::ButtCap", "CF::RoundCap",
        "CF::SquareCap", "CF::ArcCW", "CF::ArcLarge", "CF::Continuous", "CF::Align", "CF::EvenOdd",
        "CF::IsoWidth", "CF::Cyclic", "CF::Dihedral", "CF::p11g", "CF::p11m", "CF::p1m1", "CF::p2",
        "CF::p2mg", "CF::p2mm", "CF::pm", "CF::pg", "CF::cm", "CF::pmm", "CF::pmg", "CF::pgg", "CF::cmm",
        "CF::p4", "CF::p4m", "CF::p4g", "CF::p3", "CF::p3m1", "CF::p31m", "CF::p6", "CF::p6m",
        "CF::AllowOverlap", "CF::Alpha", "CF::Background", "CF::BorderDynamic", "CF::BorderFixed",
        "CF::Color", "CF::ColorDepth", "CF::Frame", "CF::FrameTime", "CF::Impure", "CF::MaxNatural",
        "CF::MaxShapes", "CF::MinimumSize", "CF::Size", "CF::StartShape", "CF::Symmetry",
        "CF::Tile", "CF::Time"
    };
    
    Style state = StyleIdentifier;
    std::string temp{text, length};
    if (length > 5 && std::strncmp(text + (length - 5), ".cfdg", 5) == 0)
        state = StyleString;
    else if (keywords.count(temp))
        state = StyleKeywords;
    else if (builtins.count(temp))
        state = StyleBuiltins;
    
    if (state != StyleIdentifier)
        for (size_t i = 0; i < length; ++i)
            styles[i] = state;
}

