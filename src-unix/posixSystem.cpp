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

#if defined(__GNU__) || (defined(__ILP32__) && defined(__x86_64__))
  #define NOSYSCTL
#else
  #include <sys/sysctl.h>
#endif
#include <sys/types.h>
#include <unistd.h>
#include <cstdint>

using std::cerr;
using std::endl;

/* The following code declares classes to read from and write to
 * file descriptore or file handles.
 *
 * See
 *      http://www.josuttis.com/cppcode
 * for details and the latest version.
 *
 * - open:
 *      - integrating BUFSIZ on some systems?
 *      - optimized reading of multiple characters
 *      - stream for reading AND writing
 *      - i18n
 *
 * (C) Copyright Nicolai M. Josuttis 2001.
 * Permission to copy, use, modify, sell and distribute this software
 * is granted provided this copyright notice appears in all copies.
 * This software is provided "as is" without express or implied
 * warranty, and with no claim as to its suitability for any purpose.
 *
 * Version: Jul 28, 2002
 * History:
 *  Jul 28, 2002: bugfix memcpy() => memmove()
 *                fdinbuf::underflow(): cast for return statements
 *  Aug 05, 2001: first public version
 */
#include <ostream>
#include <streambuf>
// for EOF:
#include <cstdio>


// low-level read and write functions
#include <unistd.h>


// BEGIN namespace BOOST
namespace boost {
    
    
    /************************************************************
     * fdostream
     * - a stream that writes on a file descriptor
     ************************************************************/
    
    
    class fdoutbuf : public std::streambuf {
    protected:
        int fd;    // file descriptor
    public:
        // constructor
        fdoutbuf (int _fd) : fd(_fd) {
        }
    protected:
        // write one character
        virtual int_type overflow (int_type c) {
            if (c != EOF) {
                char z = c;
                if (write (fd, &z, 1) != 1) {
                    return EOF;
                }
            }
            return c;
        }
        // write multiple characters
        virtual
        std::streamsize xsputn (const char* s,
                                std::streamsize num) {
            return write(fd,s,num);
        }
    };
    
    class fdostream : public std::ostream {
    protected:
        fdoutbuf buf;
    public:
        fdostream (int fd) : std::ostream(0), buf(fd) {
            rdbuf(&buf);
        }
    };

}

// End of Nicolai M. Josuttis code

void
PosixSystem::clearAndCR()
{
    static const char* EraseEndofLine = "\x1b[K";
    cerr << EraseEndofLine << '\r';
}

void
PosixSystem::catastrophicError(const char* what)
{
    cerr << "\n\nUnexpected error: " << what << endl;
}

const AbstractSystem::FileChar*
PosixSystem::tempFileDirectory()
{
    struct stat sb;
    const char *                                              tmpenv = getenv("TMPDIR");
    if (!tmpenv || stat(tmpenv, &sb) || !S_ISDIR(sb.st_mode)) tmpenv = getenv("TEMP");
    if (!tmpenv || stat(tmpenv, &sb) || !S_ISDIR(sb.st_mode)) tmpenv = getenv("TMP");
    if (!tmpenv || stat(tmpenv, &sb) || !S_ISDIR(sb.st_mode)) tmpenv = "/tmp/"; // give up
    return tmpenv;
}

namespace {
    struct MallocDeleter {
        void operator()(void* ptr) const {
            free(ptr);
        }
    };
    struct DirCloser {
        void operator()(DIR* ptr) const {
            (void)closedir(ptr);    // not called if nullptr
        }
    };
}

std::ostream*
PosixSystem::tempFileForWrite(AbstractSystem::TempType tt, FileString& nameOut)
{
    std::string t(tempFileDirectory());
    if (t.back() != '/')
        t.push_back('/');
    t.append(TempPrefixes[tt]);
    t.append("XXXXXX");
    t.append(TempSuffixes[tt]);
    
    std::unique_ptr<std::ostream> f;
    
    std::unique_ptr<char, MallocDeleter> b(strdup(t.c_str()));
    int tfd = mkstemps(b.get(), (int)strlen(TempSuffixes[tt]));
    if (tfd != -1) {
        f = std::make_unique<boost::fdostream>(tfd);
        nameOut.assign(b.get());
    }
    
    return f.release();
}

std::string
PosixSystem::relativeFilePath(const std::string& base, const std::string& rel)
{
    std::string s = base;
    
    std::string::size_type i = s.rfind('/');
    if (i == std::string::npos) {
        return rel;
    }
    i += 1;
    s.replace(i, s.length() - i, rel);
    return s;
}

int
PosixSystem::deleteTempFile(const FileString& name)
{
    return remove(name.c_str());
}

std::vector<AbstractSystem::FileString>
PosixSystem::findTempFiles()
{
    std::vector<FileString> ret;
    const char* dirname = tempFileDirectory();
    size_t len = strlen(TempPrefixAll);
    std::unique_ptr<DIR, DirCloser> dirp(opendir(dirname));
    if (!dirp) return ret;
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
#ifdef NOSYSCTL
    return 0;
#elif defined(__linux__)
  #if defined(_SC_PHYS_PAGES) && defined(_SC_PAGESIZE)
    uint64_t size = sysconf(_SC_PHYS_PAGES) * static_cast<uint64_t>(sysconf(_SC_PAGESIZE));
    if (size > MaximumMemory)
        size = MaximumMemory;
    return static_cast<size_t>(size);
  #else
    return 0;
  #endif
#else // not __linux__ and not NOSYSCTL
    int mib[2];
  #ifdef CTL_HW
    mib[0] = CTL_HW;
  #else
    return 0;
  #endif
  #if defined(HW_MEMSIZE)
    mib[1] = HW_MEMSIZE;    // OSX
    uint64_t size = 0;      // 64-bit
  #elif defined(HW_PHYSMEM64)
    mib[1] = HW_PHYSMEM64;  // NetBSD, OpenBSD
    uint64_t size = 0;      // 64-bit
  #elif defined(HW_REALMEM)
    mib[1] = HW_REALMEM;    // FreeBSD
    unsigned int size = 0;  // 32-bit
  #elif defined(HW_PHYSMEM)
    mib[1] = HW_PHYSMEM;    // DragonFly BSD
    unsigned int size = 0;  // 32-bit
  #else
    uint64_t size = 0;      // need to define this anyway
    return 0;
  #endif
    size_t len = sizeof(size);
    if (sysctl(mib, 2, &size, &len, NULL, 0) == 0) {
        if (size > MaximumMemory)
            size = MaximumMemory;
        return static_cast<size_t>(size);
    }
    return 0;
#endif // __linux__ || NOSYSCTL
}

