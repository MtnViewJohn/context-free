// Rand64.cpp
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


#include "Rand64.h"
#include <cmath>
#include <climits>


Rand64 Rand64::Common;

double Rand64::getDouble(bool doBump)
{
    if (doBump) bump();
	return  ldexp((double) (mSeed & 0xffffffffffffULL), -48);
}

long Rand64::getLong(bool doBump)
{
    if (doBump) bump();
    return (long) (mSeed & ULONG_MAX);
}

long Rand64::getPositive(bool doBump)
{
    if (doBump) bump();
    return (long) (mSeed & LONG_MAX);
}

unsigned long Rand64::getUnsigned(bool doBump)
{
    if (doBump) bump();
    return (unsigned long) (mSeed & ULONG_MAX);
}

void Rand64::seed(unsigned long long seed)
{
    mSeed = seed;
}

void Rand64::init()
{
    mSeed = RAND64_SEED;
}

void Rand64::xorChar(unsigned char c, unsigned i)
{
    mSeed ^= ((uint64_t)c) << (i * 8);
}

void Rand64::xorString(const char* t, int& i)
{
    for (; *t; ++t) {
        xorChar((unsigned char)(*t), (unsigned)i);
        bump();
        i = (i + 1) & 7;
    }
}


void Rand64::bump()
{
    mSeed = mSeed * RAND64_MULT + RAND64_ADD;
}

