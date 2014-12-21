// variation.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2005-2012 John Horigan - john@glyphic.com
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
// Mark Lentczner can be contacted at markl@glyphic.com or at
// Mark Lentczner, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//


#include "variation.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "Rand64.h"
#ifdef _WIN32
#include <windows.h>
#include <Wincrypt.h>
#endif

template<class T> static int
fromString(T* str)
{
    int value = 0;
    int offset = 0;
    int range = 1;
    
    while (T c = *str++) {
        offset += range;
        
        value *= 26;
        if      (static_cast<T>('A') <= c && c <= static_cast<T>('Z')) { value += c - static_cast<T>('A'); }
        else if (static_cast<T>('a') <= c && c <= static_cast<T>('z')) { value += c - static_cast<T>('a'); }
        else return -1;
        
        range *= 26;
    }
    
    return offset + value;
}


template<class T> static void
toString(int var, T* str, bool lowerCase)
{
    int length = 0;
    int range = 1;
    
    while (var >= range) {
        length += 1;
        var -= range;
        range *= 26;
    }
    
    str[length--] = static_cast<T>('\0');
    while (length >= 0) {
        T v = static_cast<T>(var % 26);
        var = (var - v) / 26;
        
        str[length--] = static_cast<T>(lowerCase ? 'a' : 'A') + v;
    }
}

int Variation::fromString(const char* str) { return ::fromString(str); }
int Variation::fromString(const WinTcharType* str) { return ::fromString(str); }
void Variation::toString(int var, char* str, bool lowerCase) { ::toString(var, str, lowerCase); }
void Variation::toString(int var, WinTcharType* str, bool lowerCase) { ::toString(var, str, lowerCase); }

int Variation::recommendedMin() { return 1; }
int Variation::recommendedMax(int letters) 
{
    int range = 0;
    int value = 26;
    for (int i = 0; i < letters; i++) {
        range += value;
        value *= 26;
    }
    return range;
}

int Variation::random(int letters)
{
    static bool seeded = false;
    if (!seeded) {
        Rand64::seed_t randomSeed = static_cast<Rand64::seed_t>(time(0));
#ifdef WIN32
        HMODULE hLib = LoadLibrary(TEXT("ADVAPI32.DLL"));
        if (hLib) {
            BOOLEAN (APIENTRY *pfn)(void*, ULONG) = 
                (BOOLEAN (APIENTRY *)(void*, ULONG))GetProcAddress(hLib, "SystemFunction036");
            if (pfn)
                pfn(&randomSeed, (ULONG)sizeof(randomSeed));

            FreeLibrary(hLib);
        }
#else
        /* [AMS] 2/13/2007 -- Added seeding from /dev/urandom */
        std::ifstream urand("/dev/urandom", std::ios::in | std::ios::binary);
        if (urand.is_open()) {
            urand.read(reinterpret_cast<char*>(&randomSeed), sizeof(randomSeed));
            urand.close();
        }
#endif
        Rand64::Seed(randomSeed);
        seeded = true;
    }

    int min = recommendedMin();
    int max = recommendedMax(letters);
    for (;;) {
        unsigned long rnd = Rand64::GetUnsigned();
        if (rnd + max > rnd)
            return min + rnd % (max - min + 1);
    }
}

#ifdef TEST_MAIN
#include <iostream>
using namespace std;

int
main(int argc, char* argv[])
{
  cout << "Variation recommended range: "
       << Variation::recommendedMin() << ","
       << Variation::recommendedMax() << endl;

  char buf[100];
  
  while (!cin.bad()) {
    cin.getline(buf, sizeof(buf)/sizeof(buf[0]));
    
    char c = buf[0];
    if (c == '.') {
      int v = Variation::random();
      char codeUpper[Variation::maxStringLength];
      char codeLower[Variation::maxStringLength];
      Variation::toString(v, codeUpper, false);
      Variation::toString(v, codeLower, true);

      cout << "random picked " << v << endl;
      cout << "    or >" << codeUpper << "<" << endl;
      cout << "    or >" << codeLower << "<" << endl;
    }
    else if ('0' <= c && c <= '9') {
      int v = atoi(buf);
      char code[Variation::maxStringLength];
      Variation::toString(v, code, false);
      int v2 = Variation::fromString(code);

      cout << v << " converted to >" << code << "<" << endl;
      cout << "    which converted back to " << v2 << endl;
    }
    else {
      int v = Variation::fromString(buf);
      char code[Variation::maxStringLength];
      Variation::toString(v, code, false);
      cout << ">" << buf << "< converted to " << v << endl;
      cout << "    which converted back to >" << code << "<" << endl;
    }
  }

  return 0;
}

#endif

