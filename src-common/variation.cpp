// variation.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2005-2015 John Horigan - john@glyphic.com
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
#include "Rand64.h"
#include <random>
#include <limits>
#include <cstdint>

int
Variation::fromString(const char* str)
{
    std::uint64_t value = 0;
    std::uint64_t offset = 0;
    std::uint64_t range = 1;
    
    while (char c = *str++) {
        if (range > std::numeric_limits<int>::max())
            return -1;
        
        offset += range;
        
        value *= 26;
        if      ('A' <= c && c <= 'Z') { value += c - 'A'; }
        else if ('a' <= c && c <= 'z') { value += c - 'a'; }
        else return -1;
        
        range *= 26;
    }
    
    return (offset + value > std::numeric_limits<int>::max()) ?
                    -1 : static_cast<int>(offset + value);
}


std::string
Variation::toString(int ivar, bool lowerCase)
{
    int length = 0;
    std::uint64_t range = 1;
    std::uint64_t var = ivar < 1 ? 1 : static_cast<std::uint64_t>(ivar);
    
    while (var >= range && range < std::numeric_limits<int>::max()) {
        length += 1;
        var -= range;
        range *= 26;
    }
    
    std::string str(length--, ' ');
    
    while (length >= 0) {
        char v = static_cast<char>(var % 26);
        var = (var - v) / 26;
        
        str[length--] = (lowerCase ? 'a' : 'A') + v;
    }
    
    return str;
}

int Variation::recommendedMin() { return 1; }
int Variation::recommendedMax(int letters) 
{
    int range = 0;
    int value = 1;
    if (letters < 1) letters = 1;
    if (letters > 6) letters = 6;
    for (int i = 0; i < letters; i++) {
        value *= 26;
        range += value;
    }
    return range;
}

int Variation::random(int letters)
{
    static bool seeded = false;
    if (!seeded) {
        std::random_device rd;
        Rand64::result_type seed = rd();
        if (sizeof(std::random_device::result_type) < sizeof(Rand64::result_type))
            seed = (seed << 32) | rd();
        Rand64::Seed(seed);
        seeded = true;
    }
    
    return static_cast<int>(Rand64::GetInt(recommendedMin(), recommendedMax(letters)));
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

