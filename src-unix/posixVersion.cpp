// posixVersion.cpp
// Context Free
// ---------------------
// Copyright (C) 2008-2013 John Horigan
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

#include "version.h"
#include <string.h>

const char* APP_NAME(const char* argv0)
{
    if (argv0 == nullptr || *argv0 == '\0') return "cfdg";
    
    const char* dir = strrchr(argv0, '/');
    
    if (dir) 
        return dir + 1;

    return argv0;
}

const char* APP_VERSION()
{ 
    return "3.0.11.5";
}
int APP_BUILD()
{ 
    return 30;
}
const char* APP_OPTCHAR()
{ 
    return "-";
}

const char* APP_OPTLONG()
{
    return "--";
}

const char* APP_OPTSEP()
{
    return "=";
}

char APP_DIRCHAR()
{
    return '/';
}
