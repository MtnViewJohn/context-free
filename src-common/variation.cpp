// variation.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2005-2008 John Horigan - john@glyphic.com
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
        if      ((T)'A' <= c && c <= (T)'Z') { value += c - (T)'A'; }
        else if ((T)'a' <= c && c <= (T)'z') { value += c - (T)'a'; }
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
    
    str[length--] = (T)'\0';
    while (length >= 0) {
        T v = (T)(var % 26);
        var = (var - v) / 26;
        
        str[length--] = (T)(lowerCase ? 'a' : 'A') + v;
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
#ifdef WIN32
		HCRYPTPROV csphandle;
		unsigned long long randomSeed = 0ULL;
		CryptAcquireContext(&csphandle, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
		CryptGenRandom(csphandle, 8, (BYTE*)randomSeed);
		CryptReleaseContext(csphandle, 0);
        Rand64::Common.seed(randomSeed);
#else
        /* [AMS] 2/13/2007 -- Added seeding from /dev/urandom */
        unsigned long long urandomSeed = 0ULL;
        std::ifstream urand("/dev/urandom", std::ios::in | std::ios::binary);
        if (urand.is_open()) {
            urand.read((char*)(&urandomSeed), sizeof(unsigned long long));
            urand.close();
            Rand64::Common.seed(urandomSeed);
        } else {
            Rand64::Common.seed((unsigned long long)time(0));
        }
#endif
        seeded = true;
    }

    int min = recommendedMin();
    int max = recommendedMax(letters);
    return min + Rand64::Common.getUnsigned() % (max - min + 1);
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

