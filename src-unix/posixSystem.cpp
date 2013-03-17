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

#include <sys/sysctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdint>
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
    
    ofstream* f = nullptr;
    
    unique_ptr<char, decltype(&free)> b(strdup(t.c_str()), &free);
    if (mktemp(b.get())) {
        f = new ofstream;
        f->open(b.get(), ios::binary | ios::trunc | ios::out);
        nameOut.assign(b.get());
    }
    
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
    const char* dirname = tempFileDirectory();
    size_t len = strlen(TempPrefixAll);
    unique_ptr<DIR, decltype(&closedir)> dirp(opendir(dirname), &closedir);
    while (dirent* der = readdir(dirp.get())) {
        if (strncmp(TempPrefixAll, der->d_name, len) == 0) {
            ret.emplace_back(dirname);
            if (ret.back().back() != '/')
                ret.back().push_back('/');
            ret.back().append(der->d_name);
        }
    }
    
    return ret;
}

size_t
PosixSystem::getPhysicalMemory()
{
#ifdef __linux
#if defined(_SC_PHYS_PAGES) && defined(_SC_PAGESIZE)
    uint64_t size = sysconf(_SC_PHYS_PAGES) * (uint64_t)sysconf(_SC_PAGESIZE);
    if (!SystemIs64bit && size > 2147483648UL)
        size = 2147483648UL;
    return (size_t)size;
#else
    return 0;
#endif
#else // __linux
    int mib[2];
	mib[0] = CTL_HW;
#if defined(HW_MEMSIZE)
	mib[1] = HW_MEMSIZE;		// OSX
	int64_t size = 0;		// 64-bit
#elif defined(HW_PHYSMEM64)
	mib[1] = HW_PHYSMEM64;  // NetBSD, OpenBSD
	int64_t size = 0;		// 64-bit
#elif defined(HW_REALMEM)
	mib[1] = HW_REALMEM;		// FreeBSD
	unsigned int size = 0;	// 32-bit
#elif defined(HW_PHYSMEM)
	mib[1] = HW_PHYSMEM;		// DragonFly BSD
	unsigned int size = 0;	// 32-bit
#endif
	size_t len = sizeof(size);
	if (sysctl(mib, 2, &size, &len, NULL, 0) == 0) {
        if (!SystemIs64bit && len > 4 && size > 2147483648UL)
            size = 2147483648UL;
		return (size_t)size;
    }
	return 0;
#endif // __linux
}

