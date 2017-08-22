// Rand64.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2008-2015 John Horigan - john@glyphic.com
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


#ifndef INCLUDE_RAND64_H
#define INCLUDE_RAND64_H

#include "xorshift64star.h"
#include <cmath>

class Rand64 {
public:
    using result_type = XORshift64star::result_type;
    Rand64(result_type seed = XORshift64star::RAND64_SEED) : mSeed(seed) { }
    Rand64(const Rand64& r) : mSeed(r.mSeed) { }
    // Return double in [0,1)
    double getDouble()
    {
        auto next = mSeed();
        return  std::ldexp(static_cast<double>(next & 0xfffffffffffffULL), -52);
    }
    
    // Return int in [l,u]
    int64_t getInt(int64_t l, int64_t u);
    
    // Return int in [0,trials]
    int64_t getBinomial(int64_t trials, double prob);
    
    // Return int in [0,trials]
    int64_t getNegativeBinomial(int64_t trials, double prob);
    
    bool getBernoulli(double prob);
    
    int64_t getGeometric(double p);
    
    int64_t getPoisson(double mean);
    
    double getExponential(double lambda);
    
    double getGamma(double alpha, double beta);
    
    double getWeibull(double a, double b);
    
    double getExtremeValue(double a, double b);
    
    double getNormal(double mean, double stddev);
    
    double getLogNormal(double scale, double shape);
    
    double getChiSquared(double freedom);
    
    double getCauchy(double location, double scale);
    
    double getFisherF(double mfree, double nfree);
    
    double getStudentT(double freedom);
    
    int64_t getDiscrete(unsigned count, const double* weights);
    
    Rand64& operator^=(const Rand64& r)
    {
        mSeed.mSeed ^= r.mSeed.mSeed;
        return *this;
    };
    
    void seed(result_type _s = XORshift64star::RAND64_SEED)
    { mSeed.seed(_s); }
    result_type operator()() { return mSeed(); }

    
    void xorString(const char* t, int& i);
    void xorChar(unsigned char c, unsigned i);
    static double GetDouble()
    { return Common.getDouble(); }
    static int64_t GetInt(int64_t l, int64_t u)
    { return Common.getInt(l,u); }
    static void Seed(result_type s = XORshift64star::RAND64_SEED)
    { Common.seed(s); }
    static void XorString(const char* t, int& i)
    { Common.xorString(t, i); }
    static void XorChar(unsigned char c, unsigned i)
    { Common.xorChar(c, i); }

private:
    XORshift64star  mSeed;
    static Rand64   Common;
    double prob(double p) { return p < 0.0 ? 0.0 : (p > 1.0 ? 1.0 : p); };
    double pos(double p) { return p > 0.0 ? p : std::numeric_limits<double>::epsilon(); }
    double degree(double n) { return n >= 1.0 ? floor(n) : 1.0; }
    int64_t nat(int64_t i) { return i < 1 ? 1 : i; }
};

#endif  // INCLUDE_RAND64_H
    
    
