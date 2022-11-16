// CFscintilla.h
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

#ifndef CFscintilla_h
#define CFscintilla_h

#include <vector>
#include <string.h>
#include <cstddef>
#include "Scintilla.h"

#ifdef _MSC_VER
#define strcasecmp _stricmp
#define strncasecmp _strincmp
#endif

class CFscintilla {
public:
    struct AutoCmp {
        inline bool operator()(const char* a, const char* b)
        {
            return strcasecmp(a, b) < 0;        // a POSIX function
        }
    };
    
    static std::vector<const char*> AutoComplete;
    
    enum Style {
        StyleDefault, StyleComment, StyleSymbol, StyleIdentifier,
        StyleKeywords, StyleBuiltins, StyleString, StyleNumber
    };
    
    static Style StyleLine(std::size_t length, const char* text, char* styles, Style initStyle);
    static void StyleLines(SciFnDirect directFunction, sptr_t sciptr, int startLine, int endLine);
private:
    static void StyleId(std::size_t length, const char* text, char* styles);
};

#endif /* CFscintilla_h */
