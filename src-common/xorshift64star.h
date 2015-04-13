// xorshift64star.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2015 John Horigan - john@glyphic.com
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


#ifndef INCLUDE_XORSHIFT64STAR_H
#define INCLUDE_XORSHIFT64STAR_H

#include <cstdint>
#include <limits>
#include <random>
#include <istream>
#include <ostream>

#if defined(_MSC_VER) && _MSC_VER < 1900
#define myConstExpr
#else
#define myConstExpr constexpr
#endif

// This class  implements the xorshift64* PRNG.
class XORshift64star {
public:
    typedef std::uint64_t result_type;
    
    enum e_consts : result_type {
        RAND64_MULT = 2685821657736338717ULL,
        RAND64_SEED = 0x3DF41234ABCD330EULL
    };
    
    result_type mSeed;
    
    explicit XORshift64star(result_type _s = RAND64_SEED) : mSeed(_s ? _s : RAND64_SEED) { }
    template <class SSeq>
    explicit XORshift64star(SSeq& q) { seed(q); }
    
    void seed(result_type _s = RAND64_SEED) { mSeed = _s ? _s : RAND64_SEED; }
    template <class SSeq>
    void seed(SSeq& q)
    {
        std::uint32_t seeds[2];
        q.generate(seeds, seeds+2);
        mSeed = static_cast<result_type>(seeds[0]) << 32 |
                static_cast<result_type>(seeds[1]);
        if (mSeed == 0)
            mSeed = RAND64_SEED;
    }
    
    void discard(unsigned long long z)
    {
        for (unsigned long long i = 0; i < z; ++i) {
            // This is the xorshift64* PRNG.
            mSeed ^= mSeed >> 12;
            mSeed ^= mSeed << 25;
            mSeed ^= mSeed >> 27;
            mSeed *= RAND64_MULT;
        }
    }
    
    result_type operator()()
    {
        discard(1);
        return mSeed;
    }
    
    static myConstExpr result_type min() { return 1; }
    static myConstExpr result_type max() { return static_cast<result_type>(-1LL); }
    
    bool operator==(const XORshift64star& rhs) const { return mSeed == rhs.mSeed; }
    bool operator!=(const XORshift64star& rhs) const { return mSeed != rhs.mSeed; }
    
    
    template <class CharT, class Traits>
    friend std::basic_ostream<CharT,Traits>& operator<<(std::basic_ostream<CharT,Traits>& ost, const XORshift64star& rhs);
    template <class CharT, class Traits>
    friend std::basic_istream<CharT,Traits>& operator>>(std::basic_istream<CharT,Traits>& ist, XORshift64star& rhs);
    
private:
    template <class _CharT, class _Traits>
    class __save_flags
    {
        typedef std::basic_ios<_CharT, _Traits> __stream_type;
        typedef typename __stream_type::fmtflags fmtflags;
        
        __stream_type& __stream_;
        fmtflags       __fmtflags_;
        _CharT         __fill_;
        
        __save_flags(const __save_flags&);
        __save_flags& operator=(const __save_flags&);
    public:
        explicit __save_flags(__stream_type& __stream)
        : __stream_(__stream),
        __fmtflags_(__stream.flags()),
        __fill_(__stream.fill())
        {}
        ~__save_flags()
        {
            __stream_.flags(__fmtflags_);
            __stream_.fill(__fill_);
        }
    };
};

template <class CharT, class Traits>
std::basic_ostream<CharT,Traits>& operator<<(std::basic_ostream<CharT,Traits>& ost, const XORshift64star& rhs)
{
    XORshift64star::__save_flags<CharT, Traits> lx(ost);
    ost.flags(std::ios_base::dec | std::ios_base::left);
    ost.fill(ost.widen(' '));
    return ost << rhs.mSeed;
}

template <class CharT, class Traits>
std::basic_istream<CharT,Traits>& operator>>(std::basic_istream<CharT,Traits>& ist, XORshift64star& rhs)
{
    XORshift64star::__save_flags<CharT, Traits> lx(ist);
    ist.flags(std::ios_base::dec | std::ios_base::skipws);
    XORshift64star::result_type tmp;
    ist >> tmp;
    if (!ist.fail())
        rhs.mSeed = tmp;
    return ist;
}

#endif  // INCLUDE_XORSHIFT64STAR_H


