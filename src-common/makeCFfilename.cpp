// makeCFfilename.cpp
// Context Free
// ---------------------
// Copyright (C) 2008-2012 John Horigan
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

#include "makeCFfilename.h"
#include <sstream>
#include <iomanip>
#include <string>
#include "variation.h"
#include <cstring>
#include <string.h>


std::string makeCFfilename(const char* fmt, int frame, int frameCount, int variation)
{
    std::stringstream namestream(std::stringstream::out);
    
    if (strcmp(fmt, "-") == 0)
        return namestream.str();        // empty string becomes stdout
    
    int numLength = 0;
    for (int c = frameCount; c > 0; c /= 10)
        ++numLength;

    const char* p = fmt;
    while (*p) {
        const char* perc = strchr(p, '%');
        
        if (perc) {
            namestream.write(p, perc - p);
        } else {
            namestream << p;
            break;
        }
        
        bool lower = true;

        switch (*(perc + 1)) {
            case 'V':
                lower = false;
                [[fallthrough]];
            case 'v':
                namestream << Variation::toString(variation, lower);
                break;
            case 'f':
                namestream << std::setfill('0') << std::setw(numLength) << frame;
                break;
            case '%':
                namestream << '%';
                break;
            default:
                namestream << "_Unknown_format_code_" << *(perc + 1) << '_';
                break;
        }
        
        p = perc + 2;
    }
    
    return namestream.str();
}

    
    
