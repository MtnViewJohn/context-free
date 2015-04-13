// Rand64.cpp
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


#include "Rand64.h"
#include "myrandom.h"

Rand64 Rand64::Common;

// Return int in [l,u]
int64_t Rand64::getInt(int64_t l, int64_t u)
{
    CF::uniform_int_distribution<int64_t> intRand(l,u);
    return intRand(mSeed);
}

// Return int in [0,trials]
int64_t Rand64::getBinomial(int64_t trials, double p)
{
    CF::binomial_distribution<int64_t> bd(nat(trials), prob(p));
    return bd(mSeed);
}

// Return int in [0,trials]
int64_t Rand64::getNegativeBinomial(int64_t trials, double p)
{
    CF::negative_binomial_distribution<int64_t> nbd(nat(trials), prob(p));
    return nbd(mSeed);
}

bool Rand64::getBernoulli(double p)
{
    CF::bernoulli_distribution bd(prob(p));
    return bd(mSeed);
}

int64_t Rand64::getGeometric(double p)
{
    CF::geometric_distribution<int64_t> gd(prob(p));
    return gd(mSeed);
}

int64_t Rand64::getPoisson(double mean)
{
    CF::poisson_distribution<int64_t> pd(pos(mean));
    return pd(mSeed);
}

double Rand64::getExponential(double lambda)
{
    CF::exponential_distribution<double> ed(pos(lambda));
    return ed(mSeed);
}

double Rand64::getGamma(double alpha, double beta)
{
    CF::gamma_distribution<double> gd(pos(alpha), pos(beta));
    return gd(mSeed);
}

double Rand64::getWeibull(double a, double b)
{
    CF::weibull_distribution<double> wd(pos(a), pos(b));
    return wd(mSeed);
}

double Rand64::getExtremeValue(double location, double scale)
{
    CF::extreme_value_distribution<double> evd(location, pos(scale));
    return evd(mSeed);
}

double Rand64::getNormal(double mean, double stddev)
{
    CF::normal_distribution<double> nd(mean, stddev);
    return nd(mSeed);
}

double Rand64::getLogNormal(double scale, double shape)
{
    CF::lognormal_distribution<double> lnd(scale, shape);
    return lnd(mSeed);
}

double Rand64::getChiSquared(double freedom)
{
    CF::chi_squared_distribution<double> csd(degree(freedom));
    return csd(mSeed);
}

double Rand64::getCauchy(double location, double scale)
{
    CF::cauchy_distribution<double> cd(location, pos(scale));
    return cd(mSeed);
}

double Rand64::getFisherF(double mfree, double nfree)
{
    CF::fisher_f_distribution<double> ffd(degree(mfree), degree(nfree));
    return ffd(mSeed);
}

double Rand64::getStudentT(double freedom)
{
    CF::student_t_distribution<double> sttd(degree(freedom));
    return sttd(mSeed);
}

int64_t Rand64::getDiscrete(unsigned count, const double* weights)
{
    if (count == 0)
        return 0;

    std::vector<double> w(count);
    for (unsigned i = 0; i < count; ++i)
        w[i] = fabs(weights[i]);

    std::size_t i(0);
    CF::discrete_distribution<int64_t> sd(count, 0, 1,
        [&w, &i](double)
        {
            auto weight = w[i];
            ++i;
            return weight;
        });
    return sd(mSeed);
}


void Rand64::xorChar(unsigned char c, unsigned i)
{
    mSeed.mSeed ^= (static_cast<result_type>(c)) << (i * 8);
}

void Rand64::xorString(const char* t, int& i)
{
    for (; *t; ++t) {
        xorChar(static_cast<unsigned char>(*t), static_cast<unsigned>(i));
        mSeed.discard(1);
        i = (i + 1) & 7;
    }
}

