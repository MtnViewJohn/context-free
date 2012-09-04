// Rand64.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2008 John Horigan - john@glyphic.com
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


#ifndef INCLUDE_RAND48_H
#define INCLUDE_RAND48_H
#define RAND64_MULT  0x5851F42D4C957F2DULL
#define RAND64_ADD   0x14057B7EF767814FULL
#define RAND64_SEED  0x3DF41234ABCD330EULL

#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif

#include <stdint.h>

// This class  implements the 64-bit linear congruent PRNG from Knuth's MMIX architecture.
class Rand64 {
public:
    uint64_t mSeed;
    static Rand64   Common;
    
    Rand64() : mSeed(RAND64_SEED) { }
    Rand64(uint64_t seed) : mSeed(seed) { }
    
    double getDouble(bool bump = true);
    long getLong(bool bump = true);
    long getPositive(bool bump = true);
    unsigned long getUnsigned(bool bump = true);
    
    void seed(uint64_t seed);
    void init();
    
    Rand64& operator^=(const Rand64& r)
    {
        mSeed ^= r.mSeed;
        return *this;
    };
    bool operator==(const Rand64& r)
    {
        return mSeed == r.mSeed;
    };
    void xorString(const char* t, int& i);
    void xorChar(unsigned char c, unsigned i);
    void bump();
};

#endif  // INCLUDE_RAND48_H
    
    
