// ffmpegshim.c
// this file is part of Context Free
// ---------------------
// Copyright (C) 2012 John Horigan - john@glyphic.com
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

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>

int __cdecl __mingw_vsnprintf(
     char *buffer,
     size_t count,
     const char *format,
     va_list argptr 
)
{
    return vsnprintf_s(buffer, count, _TRUNCATE, format, argptr);
}

int __cdecl __mingw_vfprintf(
     FILE *stream,
     const char *format,
     va_list argptr 
)
{
    return vfprintf_s(stream, format, argptr);
}

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
 
struct timezone 
{
    int  tz_minuteswest; /* minutes W of Greenwich */
    int  tz_dsttime;     /* type of dst correction */
};
struct timeval {
    long tv_sec;
    long tv_usec;
};

int __cdecl gettimeofday(
     struct timeval  *tv, 
     struct timezone *tz
)
{
    FILETIME ft;
    unsigned __int64 tmpres = 0;
    static int tzflag;

    if (NULL != tv) {
        GetSystemTimeAsFileTime(&ft);

        tmpres |= ft.dwHighDateTime;
        tmpres <<= 32;
        tmpres |= ft.dwLowDateTime;

        /*converting file time to unix epoch*/
        tmpres -= DELTA_EPOCH_IN_MICROSECS; 
        tmpres /= 10;  /*convert into microseconds*/
        tv->tv_sec = (long)(tmpres / 1000000UL);
        tv->tv_usec = (long)(tmpres % 1000000UL);
    }

    if (NULL != tz) {
        int i;
        if (!tzflag) {
            _tzset();
            tzflag++;
        }
        _get_timezone(&i);
        tz->tz_minuteswest = i / 60;
        _get_daylight(&i);
        tz->tz_dsttime = i;
    }

    return 0;
}

int __cdecl usleep(
     unsigned int useconds
)
{
    if(useconds == 0)
        return 0;

    if(useconds >= 1000000)
        return EINVAL;

    Sleep((useconds + 999) / 1000);

    return 0;
}

double __cdecl __strtod(
     const char *nptr,
     char **endptr 
)
{
    return strtod(nptr, endptr);
}

double __cdecl trunc(
     double n
)
{
    return n > 0.0 ? floor(n) : ceil(n);
}

int __cdecl __mingw_vsscanf(
     const char *s, 
     const char *fmt, 
     va_list ap
)
{
    void *a[5];
    int i;
    for (i=0; i < sizeof(a)/sizeof(a[0]); i++)
        a[i] = va_arg(ap, void *);
    return sscanf(s, fmt, a[0], a[1], a[2], a[3], a[4]);
}