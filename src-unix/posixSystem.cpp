// posixSystem.cpp
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

#include "posixSystem.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

using namespace std;

void
PosixSystem::clearAndCR()
{
    static const char* EraseEndofLine = "\x1b[K";
    cerr << EraseEndofLine << '\r';
}

const char*
PosixSystem::tempFileDirectory()
{
    struct stat sb;
    const char *                                              tmpenv = getenv("TMPDIR");
    if (!tmpenv || stat(tmpenv, &sb) || !S_ISDIR(sb.st_mode)) tmpenv = getenv("TEMP");
    if (!tmpenv || stat(tmpenv, &sb) || !S_ISDIR(sb.st_mode)) tmpenv = getenv("TMP");
    return (!tmpenv || stat(tmpenv, &sb) || !S_ISDIR(sb.st_mode)) ? "/tmp/" : tmpenv;
}

ostream*
PosixSystem::tempFileForWrite(AbstractSystem::TempType tt, string& nameOut)
{
    string t(tempFileDirectory());
    if (t.back() != '/')
        t.push_back('/');
    t.append(TempPrefixes[tt]);
    t.append("XXXXXX");
    
    ofstream* f = 0;
    
    char* b = strdup(t.c_str());
    if (mktemp(b)) {
        f = new ofstream;
        f->open(b, ios::binary | ios::trunc | ios::out);
        nameOut.assign(b);
    }
    free(b);
    
    return f;
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

vector<string>
PosixSystem::findTempFiles()
{
    vector<string> ret;
    const char* dir = tempFileDirectory();
    size_t len = strlen(TempPrefixAll);
    DIR* dirp = opendir(dir);
    dirent de;
    dirent* der = nullptr;
    for(;;) {
        if (readdir_r(dirp, &de, &der) || der == nullptr)
            break;
        if (strncmp(TempPrefixAll, de.d_name, len) == 0) {
            ret.emplace_back(dir);
            if (ret.back().back() != '/')
                ret.back().push_back('/');
            ret.back().append(de.d_name);
        }
    }
    
    return ret;
}

