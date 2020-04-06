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

#ifndef INCLUDE_FDOSTREAM_H
#define INCLUDE_FDOSTREAM_H

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
    public:
        int fd;    // file descriptor
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
        fdostream () : std::ostream(0), buf(-1) {
        }
        fdostream (int fd) : std::ostream(0), buf(fd) {
            rdbuf(&buf);
        }
        void setfd (int _fd) {
            buf.fd = _fd;
            rdbuf(&buf);
        }
    };

}

#endif   // INCLUDE_FDOSTREAM_H
// End of Nicolai M. Josuttis code
