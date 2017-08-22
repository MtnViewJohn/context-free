// -*- C++ -*-
//===--------------------------- random -----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

/****************************** LICENSE.TXT ***********************************
 ==============================================================================
 libc++ License
 ==============================================================================
 
 The libc++ library is dual licensed under both the University of Illinois
 "BSD-Like" license and the MIT license.  As a user of this code you may choose
 to use it under either license.  As a contributor, you agree to allow your code
 to be used under both.
 
 Full text of the relevant licenses is included below.
 
 ==============================================================================
 
 University of Illinois/NCSA
 Open Source License
 
 Copyright (c) 2009-2015 by the contributors listed in CREDITS.TXT
 
 All rights reserved.
 
 Developed by:
 
 LLVM Team
 
 University of Illinois at Urbana-Champaign
 
 http://llvm.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal with
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 * Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimers.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimers in the
 documentation and/or other materials provided with the distribution.
 
 * Neither the names of the LLVM Team, University of Illinois at
 Urbana-Champaign, nor the names of its contributors may be used to
 endorse or promote products derived from this Software without specific
 prior written permission.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS WITH THE
 SOFTWARE.
 
 ==============================================================================
 
 Copyright (c) 2009-2014 by the contributors listed in CREDITS.TXT
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************** LICENSE.TXT ***********************************/

#ifndef Context_Free_myrandom_h
#define Context_Free_myrandom_h

#if defined(_MSC_VER) && _MSC_VER < 1900
#define CF_CONSTEXPR
#define CF_HAS_NO_CONSTEXPR
#else
#define CF_CONSTEXPR constexpr
#endif

#include <cstddef>
#include <type_traits>
#include <initializer_list>
#include <cstdint>
#include <limits>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>
#include <cassert>

namespace CF {
    template <unsigned long long _Xp, size_t _Rp>
    struct __log2_imp
    {
        static const size_t value = _Xp & ((unsigned long long)(1) << _Rp) ? _Rp
        : __log2_imp<_Xp, _Rp - 1>::value;
    };
    
    template <unsigned long long _Xp>
    struct __log2_imp<_Xp, 0>
    {
        static const size_t value = 0;
    };
    
    template <size_t _Rp>
    struct __log2_imp<0, _Rp>
    {
        static const size_t value = _Rp + 1;
    };
    
    template <class _UI, _UI _Xp>
    struct __log2
    {
        static const size_t value = __log2_imp<_Xp, sizeof(_UI) * 8 - 1>::value;
    };
    
    
    // generate_canonical
    
    template<class _RealType, std::size_t __bits, class _URNG>
    _RealType
    generate_canonical(_URNG& __g)
    {
        const std::size_t _Dt = std::numeric_limits<_RealType>::digits;
        const std::size_t __b = _Dt < __bits ? _Dt : __bits;
#ifdef CF_HAS_NO_CONSTEXPR
        const std::size_t __logR = __log2<std::uint64_t, _URNG::_Max - _URNG::_Min + std::uint64_t(1)>::value;
#else
        const std::size_t __logR = __log2<std::uint64_t, _URNG::max() - _URNG::min() + std::uint64_t(1)>::value;
#endif
        const std::size_t __k = __b / __logR + (__b % __logR != 0) + (__b == 0);
        const _RealType _Rp = _URNG::max() - _URNG::min() + _RealType(1);
        _RealType __base = _Rp;
        _RealType _Sp = __g() - _URNG::min();
        for (std::size_t __i = 1; __i < __k; ++__i, __base *= _Rp)
            _Sp += (__g() - _URNG::min()) * __base;
        return _Sp / __base;
    }
    
    // uniform_real_distribution
    
    template<class _RealType = double>
    class uniform_real_distribution
    {
    public:
        // types
        typedef _RealType result_type;
        
        class param_type
        {
            result_type __a_;
            result_type __b_;
        public:
            typedef uniform_real_distribution distribution_type;
            
            explicit param_type(result_type __a = 0,
                                result_type __b = 1)
            : __a_(__a), __b_(__b) {}
            
            result_type a() const {return __a_;}
            result_type b() const {return __b_;}
            
            friend
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__a_ == __y.__a_ && __x.__b_ == __y.__b_;}
            friend
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
        };
        
    private:
        param_type __p_;
        
    public:
        // constructors and reset functions
        explicit uniform_real_distribution(result_type __a = 0, result_type __b = 1)
        : __p_(param_type(__a, __b)) {}
        explicit uniform_real_distribution(const param_type& __p) : __p_(__p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);
        
        // property functions
        result_type a() const {return __p_.a();}
        result_type b() const {return __p_.b();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return a();}
        result_type max() const {return b();}
        
        friend
        bool operator==(const uniform_real_distribution& __x,
                        const uniform_real_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend
        bool operator!=(const uniform_real_distribution& __x,
                        const uniform_real_distribution& __y)
        {return !(__x == __y);}
    };
    
    template<class _RealType>
    template<class _URNG>
    inline
    typename uniform_real_distribution<_RealType>::result_type
    uniform_real_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
    {
        return (__p.b() - __p.a())
        * generate_canonical<_RealType, std::numeric_limits<_RealType>::digits>(__g)
        + __p.a();
    }
    
    // uniform_int_distribution
    
    template<class _IntType = int>
    class uniform_int_distribution
    {
    public:
        // types
        typedef _IntType result_type;
        
        class param_type
        {
            result_type __a_;
            result_type __b_;
        public:
            typedef uniform_int_distribution distribution_type;
            
            explicit param_type(result_type __a = 0,
                                result_type __b = std::numeric_limits<result_type>::max())
            : __a_(__a), __b_(__b) {}
            
            result_type a() const {return __a_;}
            result_type b() const {return __b_;}
            
            friend bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__a_ == __y.__a_ && __x.__b_ == __y.__b_;}
            friend bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
        };
        
    private:
        param_type __p_;
        
    public:
        // constructors and reset functions
        explicit uniform_int_distribution(result_type __a = 0,
                                          result_type __b = std::numeric_limits<result_type>::max())
        : __p_(param_type(__a, __b)) {}
        explicit uniform_int_distribution(const param_type& __p) : __p_(__p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG> result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);
        
        // property functions
        result_type a() const {return __p_.a();}
        result_type b() const {return __p_.b();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return a();}
        result_type max() const {return b();}
        
        friend bool operator==(const uniform_int_distribution& __x,
                               const uniform_int_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend bool operator!=(const uniform_int_distribution& __x,
                               const uniform_int_distribution& __y)
        {return !(__x == __y);}
    };
    
    template<class _IntType>
    template<class _URNG>
    typename uniform_int_distribution<_IntType>::result_type
    uniform_int_distribution<_IntType>::operator()(_URNG& __g, const param_type& __p)
    {
        typedef typename _URNG::result_type eng_type;
        static_assert(sizeof(eng_type) >= sizeof(result_type),
                      "quick & dirty int distribution won't work");
        
        typename _URNG::result_type diff = static_cast<eng_type>(__p.b()) -
                                           static_cast<eng_type>(__p.a()) + 1;
        if (diff == 0)
            return static_cast<result_type>(__g() - __g.min());
        
        eng_type tooBig = __g.max() - __g.min();
        tooBig -= tooBig % diff;
        
        for(;;) {
            eng_type gen = __g() - __g.min();
            
            if (gen < tooBig)
                return static_cast<result_type>(gen % diff) + __p.a();
        }
    }
    
        
    // binomial_distribution
    
    template<class _IntType = int>
    class binomial_distribution
    {
    public:
        // types
        typedef _IntType result_type;
        
        class param_type
        {
            result_type __t_;
            double __p_;
            double __pr_;
            double __odds_ratio_;
            result_type __r0_;
        public:
            typedef binomial_distribution distribution_type;
            
            explicit param_type(result_type __t = 1, double __p = 0.5);
            
            inline
            result_type t() const {return __t_;}
            inline
            double p() const {return __p_;}
            
            friend inline
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__t_ == __y.__t_ && __x.__p_ == __y.__p_;}
            friend inline
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
            
            friend class binomial_distribution;
        };
        
    private:
        param_type __p_;
        
    public:
        // constructors and reset functions
        explicit binomial_distribution(result_type __t = 1, double __p = 0.5)
        : __p_(param_type(__t, __p)) {}
        explicit binomial_distribution(const param_type& __p) : __p_(__p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);
        
        // property functions
        result_type t() const {return __p_.t();}
        double p() const {return __p_.p();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return 0;}
        result_type max() const {return t();}
        
        friend inline
        bool operator==(const binomial_distribution& __x,
                        const binomial_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend inline
        bool operator!=(const binomial_distribution& __x,
                        const binomial_distribution& __y)
        {return !(__x == __y);}
    };
    
    template<class _IntType>
    binomial_distribution<_IntType>::param_type::param_type(result_type __t, double __p)
    : __t_(__t), __p_(__p)
    {
        if (0 < __p_ && __p_ < 1)
        {
            __r0_ = static_cast<result_type>((__t_ + 1) * __p_);
            __pr_ = std::exp(std::lgamma(__t_ + 1.) - std::lgamma(__r0_ + 1.) -
                               std::lgamma(__t_ - __r0_ + 1.) + __r0_ * std::log(__p_) +
                               (__t_ - __r0_) * std::log(1 - __p_));
            __odds_ratio_ = __p_ / (1 - __p_);
        }
	else
	{
	    __r0_ = __pr_ = __odds_ratio_ = 0;
	}
    }
    
    template<class _IntType>
    template<class _URNG>
    _IntType
    binomial_distribution<_IntType>::operator()(_URNG& __g, const param_type& __pr)
    {
        if (__pr.__t_ == 0 || __pr.__p_ == 0)
            return 0;
        if (__pr.__p_ == 1)
            return __pr.__t_;
        uniform_real_distribution<double> __gen;
        double __u = __gen(__g) - __pr.__pr_;
        if (__u < 0)
            return __pr.__r0_;
        double __pu = __pr.__pr_;
        double __pd = __pu;
        result_type __ru = __pr.__r0_;
        result_type __rd = __ru;
        while (true)
        {
            if (__rd >= 1)
            {
                __pd *= __rd / (__pr.__odds_ratio_ * (__pr.__t_ - __rd + 1));
                __u -= __pd;
                if (__u < 0)
                    return __rd - 1;
            }
            --__rd;
            ++__ru;
            if (__ru <= __pr.__t_)
            {
                __pu *= (__pr.__t_ - __ru + 1) * __pr.__odds_ratio_ / __ru;
                __u -= __pu;
                if (__u < 0)
                    return __ru;
            }
        }
    }
        
        
    // bernoulli_distribution
    
    class bernoulli_distribution
    {
    public:
        // types
        typedef bool result_type;
        
        class param_type
        {
            double __p_;
        public:
            typedef bernoulli_distribution distribution_type;
            
            explicit param_type(double __p = 0.5) : __p_(__p) {}
            
            double p() const {return __p_;}
            
            friend
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__p_ == __y.__p_;}
            friend
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
        };
        
    private:
        param_type __p_;
        
    public:
        // constructors and reset functions
        explicit bernoulli_distribution(double __p = 0.5)
        : __p_(param_type(__p)) {}
        explicit bernoulli_distribution(const param_type& __p) : __p_(__p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);
        
        // property functions
        double p() const {return __p_.p();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return false;}
        result_type max() const {return true;}
        
        friend
        bool operator==(const bernoulli_distribution& __x,
                        const bernoulli_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend
        bool operator!=(const bernoulli_distribution& __x,
                        const bernoulli_distribution& __y)
        {return !(__x == __y);}
    };
    
    template<class _URNG>
    inline
    bernoulli_distribution::result_type
    bernoulli_distribution::operator()(_URNG& __g, const param_type& __p)
    {
        CF::uniform_real_distribution<double> __gen;
        return __gen(__g) < __p.p();
    }
        
    // exponential_distribution
    
    template<class _RealType = double>
    class exponential_distribution
    {
    public:
        // types
        typedef _RealType result_type;
        
        class param_type
        {
            result_type __lambda_;
        public:
            typedef exponential_distribution distribution_type;
            
            explicit param_type(result_type __lambda = 1) : __lambda_(__lambda) {}
            
            result_type lambda() const {return __lambda_;}
            
            friend
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__lambda_ == __y.__lambda_;}
            friend
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
        };
        
    private:
        param_type __p_;
        
    public:
        // constructors and reset functions
        explicit exponential_distribution(result_type __lambda = 1)
        : __p_(param_type(__lambda)) {}
        explicit exponential_distribution(const param_type& __p) : __p_(__p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);
        
        // property functions
        result_type lambda() const {return __p_.lambda();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const exponential_distribution& __x,
                        const exponential_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend
        bool operator!=(const exponential_distribution& __x,
                        const exponential_distribution& __y)
        {return !(__x == __y);}
    };
    
    template <class _RealType>
    template<class _URNG>
    _RealType
    exponential_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
    {
        return -std::log
        (
         result_type(1) -
         CF::generate_canonical<result_type, std::numeric_limits<result_type>::digits>(__g)
         )
        / __p.lambda();
    }
    
    
        
    // normal_distribution
    
    template<class _RealType = double>
    class normal_distribution
    {
    public:
        // types
        typedef _RealType result_type;
        
        class param_type
        {
            result_type __mean_;
            result_type __stddev_;
        public:
            typedef normal_distribution distribution_type;
            
            explicit param_type(result_type __mean = 0, result_type __stddev = 1)
            : __mean_(__mean), __stddev_(__stddev) {}
            
            result_type mean() const {return __mean_;}
            result_type stddev() const {return __stddev_;}
            
            friend
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__mean_ == __y.__mean_ && __x.__stddev_ == __y.__stddev_;}
            friend
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
        };
        
    private:
        param_type __p_;
        result_type _V_;
        bool _V_hot_;
        
    public:
        // constructors and reset functions
        explicit normal_distribution(result_type __mean = 0, result_type __stddev = 1)
        : __p_(param_type(__mean, __stddev)), _V_hot_(false) {}
        explicit normal_distribution(const param_type& __p)
        : __p_(__p), _V_hot_(false) {}
        void reset() {_V_hot_ = false;}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);
        
        // property functions
        result_type mean() const {return __p_.mean();}
        result_type stddev() const {return __p_.stddev();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return -std::numeric_limits<result_type>::infinity();}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const normal_distribution& __x,
                        const normal_distribution& __y)
        {return __x.__p_ == __y.__p_ && __x._V_hot_ == __y._V_hot_ &&
            (!__x._V_hot_ || __x._V_ == __y._V_);}
        friend
        bool operator!=(const normal_distribution& __x,
                        const normal_distribution& __y)
        {return !(__x == __y);}
    };
    
    template <class _RealType>
    template<class _URNG>
    _RealType
    normal_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
    {
        result_type _Up;
        if (_V_hot_)
        {
            _V_hot_ = false;
            _Up = _V_;
        }
        else
        {
            CF::uniform_real_distribution<result_type> _Uni(-1, 1);
            result_type __u;
            result_type __v;
            result_type __s;
            do
            {
                __u = _Uni(__g);
                __v = _Uni(__g);
                __s = __u * __u + __v * __v;
            } while (__s > 1 || __s == 0);
            result_type _Fp = std::sqrt(-2 * std::log(__s) / __s);
            _V_ = __v * _Fp;
            _V_hot_ = true;
            _Up = __u * _Fp;
        }
        return _Up * __p.stddev() + __p.mean();
    }
    
    
        
    // poisson_distribution
    
    template<class _IntType = int>
    class poisson_distribution
    {
    public:
        // types
        typedef _IntType result_type;
        
        class param_type
        {
            double __mean_;
            double __s_;
            double __d_;
            double __l_;
            double __omega_;
            double __c0_;
            double __c1_;
            double __c2_;
            double __c3_;
            double __c_;
            
        public:
            typedef poisson_distribution distribution_type;
            
            explicit param_type(double __mean = 1.0);
            
            double mean() const {return __mean_;}
            
            friend
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__mean_ == __y.__mean_;}
            friend
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
            
            friend class poisson_distribution;
        };
        
    private:
        param_type __p_;
        
    public:
        // constructors and reset functions
        explicit poisson_distribution(double __mean = 1.0) : __p_(__mean) {}
        explicit poisson_distribution(const param_type& __p) : __p_(__p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);
        
        // property functions
        double mean() const {return __p_.mean();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::max();}
        
        friend
        bool operator==(const poisson_distribution& __x,
                        const poisson_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend
        bool operator!=(const poisson_distribution& __x,
                        const poisson_distribution& __y)
        {return !(__x == __y);}
    };
    
    template<class _IntType>
    poisson_distribution<_IntType>::param_type::param_type(double __mean)
    : __mean_(__mean)
    {
        if (__mean_ < 10)
        {
            __s_ = 0;
            __d_ = 0;
            __l_ = std::exp(-__mean_);
            __omega_ = 0;
            __c3_ = 0;
            __c2_ = 0;
            __c1_ = 0;
            __c0_ = 0;
            __c_ = 0;
        }
        else
        {
            __s_ = std::sqrt(__mean_);
            __d_ = 6 * __mean_ * __mean_;
            __l_ = static_cast<result_type>(__mean_ - 1.1484);
            __omega_ = .3989423 / __s_;
            double __b1_ = .4166667E-1 / __mean_;
            double __b2_ = .3 * __b1_ * __b1_;
            __c3_ = .1428571 * __b1_ * __b2_;
            __c2_ = __b2_ - 15. * __c3_;
            __c1_ = __b1_ - 6. * __b2_ + 45. * __c3_;
            __c0_ = 1. - __b1_ + 3. * __b2_ - 15. * __c3_;
            __c_ = .1069 / __mean_;
        }
    }
    
    template <class _IntType>
    template<class _URNG>
    _IntType
    poisson_distribution<_IntType>::operator()(_URNG& __urng, const param_type& __pr)
    {
        result_type __x;
        CF::uniform_real_distribution<double> __urd;
        if (__pr.__mean_ < 10)
        {
            __x = 0;
            for (double __p = __urd(__urng); __p > __pr.__l_; ++__x)
                __p *= __urd(__urng);
        }
        else
        {
            double __difmuk;
            double __g = __pr.__mean_ + __pr.__s_ * CF::normal_distribution<double>()(__urng);
            double __u;
            if (__g >= 0)
            {
                __x = static_cast<result_type>(__g);
                if (__x >= __pr.__l_)
                    return __x;
                __difmuk = __pr.__mean_ - __x;
                __u = __urd(__urng);
                if (__pr.__d_ * __u >= __difmuk * __difmuk * __difmuk)
                    return __x;
            }
            CF::exponential_distribution<double> __edist;
            for (bool __using_exp_dist = false; true; __using_exp_dist = true)
            {
                double __e;
                if (__using_exp_dist || __g < 0)
                {
                    double __t;
                    do
                    {
                        __e = __edist(__urng);
                        __u = __urd(__urng);
                        __u += __u - 1;
                        __t = 1.8 + (__u < 0 ? -__e : __e);
                    } while (__t <= -.6744);
                    __x = __pr.__mean_ + __pr.__s_ * __t;
                    __difmuk = __pr.__mean_ - __x;
                    __using_exp_dist = true;
                }
                double __px;
                double __py;
                if (__x < 10)
                {
                    const result_type __fac[] = {1, 1, 2, 6, 24, 120, 720, 5040,
                        40320, 362880};
                    __px = -__pr.__mean_;
                    __py = std::pow(__pr.__mean_, (double)__x) / __fac[__x];
                }
                else
                {
                    double __del = .8333333E-1 / __x;
                    __del -= 4.8 * __del * __del * __del;
                    double __v = __difmuk / __x;
                    if (std::abs(__v) > 0.25)
                        __px = __x * std::log(1 + __v) - __difmuk - __del;
                    else
                        __px = __x * __v * __v * (((((((.1250060 * __v + -.1384794) *
                                                       __v + .1421878) * __v + -.1661269) * __v + .2000118) *
                                                    __v + -.2500068) * __v + .3333333) * __v + -.5) - __del;
                    __py = .3989423 / std::sqrt(__x);
                }
                double __r = (0.5 - __difmuk) / __pr.__s_;
                double __r2 = __r * __r;
                double __fx = -0.5 * __r2;
                double __fy = __pr.__omega_ * (((__pr.__c3_ * __r2 + __pr.__c2_) *
                                                __r2 + __pr.__c1_) * __r2 + __pr.__c0_);
                if (__using_exp_dist)
                {
                    if (__pr.__c_ * std::abs(__u) <= __py * std::exp(__px + __e) -
                        __fy * std::exp(__fx + __e))
                        break;
                }
                else
                {
                    if (__fy - __u * __fy <= __py * std::exp(__px - __fx))
                        break;
                }
            }
        }
        return __x;
    }
        
        
#ifdef __alpha
#undef __alpha
#endif

    // gamma_distribution
    
    template<class _RealType = double>
    class gamma_distribution
    {
    public:
        // types
        typedef _RealType result_type;
        
        class param_type
        {
            result_type __alpha_;
            result_type __beta_;
        public:
            typedef gamma_distribution distribution_type;
            
            explicit param_type(result_type __alpha = 1, result_type __beta = 1)
            : __alpha_(__alpha), __beta_(__beta) {}
            
            result_type alpha() const {return __alpha_;}
            result_type beta() const {return __beta_;}
            
            friend
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__alpha_ == __y.__alpha_ && __x.__beta_ == __y.__beta_;}
            friend
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
        };
        
    private:
        param_type __p_;
        
    public:
        // constructors and reset functions
        explicit gamma_distribution(result_type __alpha = 1, result_type __beta = 1)
        : __p_(param_type(__alpha, __beta)) {}
        explicit gamma_distribution(const param_type& __p)
        : __p_(__p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);
        
        // property functions
        result_type alpha() const {return __p_.alpha();}
        result_type beta() const {return __p_.beta();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const gamma_distribution& __x,
                        const gamma_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend
        bool operator!=(const gamma_distribution& __x,
                        const gamma_distribution& __y)
        {return !(__x == __y);}
    };
    
    template <class _RealType>
    template<class _URNG>
    _RealType
    gamma_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
    {
        result_type __a = __p.alpha();
        CF::uniform_real_distribution<result_type> __gen(0, 1);
        CF::exponential_distribution<result_type> __egen;
        result_type __x;
        if (__a == 1)
            __x = __egen(__g);
        else if (__a > 1)
        {
            const result_type __b = __a - 1;
            const result_type __c = 3 * __a - result_type(0.75);
            while (true)
            {
                const result_type __u = __gen(__g);
                const result_type __v = __gen(__g);
                const result_type __w = __u * (1 - __u);
                if (__w != 0)
                {
                    const result_type __y = std::sqrt(__c / __w) *
                    (__u - result_type(0.5));
                    __x = __b + __y;
                    if (__x >= 0)
                    {
                        const result_type __z = 64 * __w * __w * __w * __v * __v;
                        if (__z <= 1 - 2 * __y * __y / __x)
                            break;
                        if (std::log(__z) <= 2 * (__b * std::log(__x / __b) - __y))
                            break;
                    }
                }
            }
        }
        else  // __a < 1
        {
            while (true)
            {
                const result_type __u = __gen(__g);
                const result_type __es = __egen(__g);
                if (__u <= 1 - __a)
                {
                    __x = std::pow(__u, 1 / __a);
                    if (__x <= __es)
                        break;
                }
                else
                {
                    const result_type __e = -std::log((1-__u)/__a);
                    __x = std::pow(1 - __a + __a * __e, 1 / __a);
                    if (__x <= __e + __es)
                        break;
                }
            }
        }
        return __x * __p.beta();
    }
    
    
    // negative_binomial_distribution
    
    template<class _IntType = int>
    class negative_binomial_distribution
    {
    public:
        // types
        typedef _IntType result_type;
        
        class param_type
        {
            result_type __k_;
            double __p_;
        public:
            typedef negative_binomial_distribution distribution_type;
            
            explicit param_type(result_type __k = 1, double __p = 0.5)
            : __k_(__k), __p_(__p) {}
            
            result_type k() const {return __k_;}
            double p() const {return __p_;}
            
            friend
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__k_ == __y.__k_ && __x.__p_ == __y.__p_;}
            friend
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
        };
        
    private:
        param_type __p_;
        
    public:
        // constructor and reset functions
        explicit negative_binomial_distribution(result_type __k = 1, double __p = 0.5)
        : __p_(__k, __p) {}
        explicit negative_binomial_distribution(const param_type& __p) : __p_(__p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);
        
        // property functions
        result_type k() const {return __p_.k();}
        double p() const {return __p_.p();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::max();}
        
        friend
        bool operator==(const negative_binomial_distribution& __x,
                        const negative_binomial_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend
        bool operator!=(const negative_binomial_distribution& __x,
                        const negative_binomial_distribution& __y)
        {return !(__x == __y);}
    };
    
    template <class _IntType>
    template<class _URNG>
    _IntType
    negative_binomial_distribution<_IntType>::operator()(_URNG& __urng, const param_type& __pr)
    {
        result_type __k = __pr.k();
        double __p = __pr.p();
        if (__k <= 21 * __p)
        {
            bernoulli_distribution __gen(__p);
            result_type __f = 0;
            result_type __s = 0;
            while (__s < __k)
            {
                if (__gen(__urng))
                    ++__s;
                else
                    ++__f;
            }
            return __f;
        }
        return CF::poisson_distribution<result_type>(CF::gamma_distribution<double>
                                                 (__k, (1-__p)/__p)(__urng))(__urng);
    }
    
    // geometric_distribution
    
    template<class _IntType = int>
    class geometric_distribution
    {
    public:
        // types
        typedef _IntType result_type;
        
        class param_type
        {
            double __p_;
        public:
            typedef geometric_distribution distribution_type;
            
            explicit param_type(double __p = 0.5) : __p_(__p) {}
            
            double p() const {return __p_;}
            
            friend
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__p_ == __y.__p_;}
            friend
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
        };
        
    private:
        param_type __p_;
        
    public:
        // constructors and reset functions
        explicit geometric_distribution(double __p = 0.5) : __p_(__p) {}
        explicit geometric_distribution(const param_type& __p) : __p_(__p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG>
        result_type operator()(_URNG& __g, const param_type& __p)
        {return CF::negative_binomial_distribution<result_type>(1, __p.p())(__g);}
        
        // property functions
        double p() const {return __p_.p();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::max();}
        
        friend
        bool operator==(const geometric_distribution& __x,
                        const geometric_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend
        bool operator!=(const geometric_distribution& __x,
                        const geometric_distribution& __y)
        {return !(__x == __y);}
    };
    
        
    // weibull_distribution
    
    template<class _RealType = double>
    class weibull_distribution
    {
    public:
        // types
        typedef _RealType result_type;
        
        class param_type
        {
            result_type __a_;
            result_type __b_;
        public:
            typedef weibull_distribution distribution_type;
            
            explicit param_type(result_type __a = 1, result_type __b = 1)
            : __a_(__a), __b_(__b) {}
            
            result_type a() const {return __a_;}
            result_type b() const {return __b_;}
            
            friend
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__a_ == __y.__a_ && __x.__b_ == __y.__b_;}
            friend
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
        };
        
    private:
        param_type __p_;
        
    public:
        // constructor and reset functions
        explicit weibull_distribution(result_type __a = 1, result_type __b = 1)
        : __p_(param_type(__a, __b)) {}
        explicit weibull_distribution(const param_type& __p)
        : __p_(__p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG>
        result_type operator()(_URNG& __g, const param_type& __p)
        {return __p.b() *
            std::pow(CF::exponential_distribution<result_type>()(__g), 1/__p.a());}
        
        // property functions
        result_type a() const {return __p_.a();}
        result_type b() const {return __p_.b();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const weibull_distribution& __x,
                        const weibull_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend
        bool operator!=(const weibull_distribution& __x,
                        const weibull_distribution& __y)
        {return !(__x == __y);}
    };
    
    // extreme_value_distribution
    
    template<class _RealType = double>
    class extreme_value_distribution
    {
    public:
        // types
        typedef _RealType result_type;
        
        class param_type
        {
            result_type __a_;
            result_type __b_;
        public:
            typedef extreme_value_distribution distribution_type;
            
            explicit param_type(result_type __a = 0, result_type __b = 1)
            : __a_(__a), __b_(__b) {}
            
            result_type a() const {return __a_;}
            result_type b() const {return __b_;}
            
            friend
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__a_ == __y.__a_ && __x.__b_ == __y.__b_;}
            friend
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
        };
        
    private:
        param_type __p_;
        
    public:
        // constructor and reset functions
        explicit extreme_value_distribution(result_type __a = 0, result_type __b = 1)
        : __p_(param_type(__a, __b)) {}
        explicit extreme_value_distribution(const param_type& __p)
        : __p_(__p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);
        
        // property functions
        result_type a() const {return __p_.a();}
        result_type b() const {return __p_.b();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return -std::numeric_limits<result_type>::infinity();}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const extreme_value_distribution& __x,
                        const extreme_value_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend
        bool operator!=(const extreme_value_distribution& __x,
                        const extreme_value_distribution& __y)
        {return !(__x == __y);}
    };
    
    template<class _RealType>
    template<class _URNG>
    _RealType
    extreme_value_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
    {
        return __p.a() - __p.b() *
        std::log(-std::log(1-CF::uniform_real_distribution<result_type>()(__g)));
    }
    
        
    // lognormal_distribution
    
    template<class _RealType = double>
    class lognormal_distribution
    {
    public:
        // types
        typedef _RealType result_type;
        
        class param_type
        {
            CF::normal_distribution<result_type> __nd_;
        public:
            typedef lognormal_distribution distribution_type;
            
            explicit param_type(result_type __m = 0, result_type __s = 1)
            : __nd_(__m, __s) {}
            
            result_type m() const {return __nd_.mean();}
            result_type s() const {return __nd_.stddev();}
            
            friend
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__nd_ == __y.__nd_;}
            friend
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
            friend class lognormal_distribution;
        };
        
    private:
        param_type __p_;
        
    public:
        // constructor and reset functions
        explicit lognormal_distribution(result_type __m = 0, result_type __s = 1)
        : __p_(param_type(__m, __s)) {}
        explicit lognormal_distribution(const param_type& __p)
        : __p_(__p) {}
        void reset() {__p_.__nd_.reset();}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG>
        result_type operator()(_URNG& __g, const param_type& __p)
        {return std::exp(const_cast<CF::normal_distribution<result_type>&>(__p.__nd_)(__g));}
        
        // property functions
        result_type m() const {return __p_.m();}
        result_type s() const {return __p_.s();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const lognormal_distribution& __x,
                        const lognormal_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend
        bool operator!=(const lognormal_distribution& __x,
                        const lognormal_distribution& __y)
        {return !(__x == __y);}
    };
    
        
    // chi_squared_distribution
    
    template<class _RealType = double>
    class chi_squared_distribution
    {
    public:
        // types
        typedef _RealType result_type;
        
        class param_type
        {
            result_type __n_;
        public:
            typedef chi_squared_distribution distribution_type;
            
            explicit param_type(result_type __n = 1) : __n_(__n) {}
            
            result_type n() const {return __n_;}
            
            friend
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__n_ == __y.__n_;}
            friend
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
        };
        
    private:
        param_type __p_;
        
    public:
        // constructor and reset functions
        explicit chi_squared_distribution(result_type __n = 1)
        : __p_(param_type(__n)) {}
        explicit chi_squared_distribution(const param_type& __p)
        : __p_(__p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG>
        result_type operator()(_URNG& __g, const param_type& __p)
        {return CF::gamma_distribution<result_type>(__p.n() / 2, 2)(__g);}
        
        // property functions
        result_type n() const {return __p_.n();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const chi_squared_distribution& __x,
                        const chi_squared_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend
        bool operator!=(const chi_squared_distribution& __x,
                        const chi_squared_distribution& __y)
        {return !(__x == __y);}
    };
    
        
    // cauchy_distribution
    
    template<class _RealType = double>
    class cauchy_distribution
    {
    public:
        // types
        typedef _RealType result_type;
        
        class param_type
        {
            result_type __a_;
            result_type __b_;
        public:
            typedef cauchy_distribution distribution_type;
            
            explicit param_type(result_type __a = 0, result_type __b = 1)
            : __a_(__a), __b_(__b) {}
            
            result_type a() const {return __a_;}
            result_type b() const {return __b_;}
            
            friend
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__a_ == __y.__a_ && __x.__b_ == __y.__b_;}
            friend
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
        };
        
    private:
        param_type __p_;
        
    public:
        // constructor and reset functions
        explicit cauchy_distribution(result_type __a = 0, result_type __b = 1)
        : __p_(param_type(__a, __b)) {}
        explicit cauchy_distribution(const param_type& __p)
        : __p_(__p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);
        
        // property functions
        result_type a() const {return __p_.a();}
        result_type b() const {return __p_.b();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return -std::numeric_limits<result_type>::infinity();}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const cauchy_distribution& __x,
                        const cauchy_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend
        bool operator!=(const cauchy_distribution& __x,
                        const cauchy_distribution& __y)
        {return !(__x == __y);}
    };
    
    template <class _RealType>
    template<class _URNG>
    inline
    _RealType
    cauchy_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
    {
        CF::uniform_real_distribution<result_type> __gen;
        // purposefully let tan arg get as close to pi/2 as it wants, tan will return a finite
        return __p.a() + __p.b() * std::tan(3.1415926535897932384626433832795 * __gen(__g));
    }
    
        
    // fisher_f_distribution
    
    template<class _RealType = double>
    class fisher_f_distribution
    {
    public:
        // types
        typedef _RealType result_type;
        
        class param_type
        {
            result_type __m_;
            result_type __n_;
        public:
            typedef fisher_f_distribution distribution_type;
            
            explicit param_type(result_type __m = 1, result_type __n = 1)
            : __m_(__m), __n_(__n) {}
            
            result_type m() const {return __m_;}
            result_type n() const {return __n_;}
            
            friend
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__m_ == __y.__m_ && __x.__n_ == __y.__n_;}
            friend
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
        };
        
    private:
        param_type __p_;
        
    public:
        // constructor and reset functions
        explicit fisher_f_distribution(result_type __m = 1, result_type __n = 1)
        : __p_(param_type(__m, __n)) {}
        explicit fisher_f_distribution(const param_type& __p)
        : __p_(__p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);
        
        // property functions
        result_type m() const {return __p_.m();}
        result_type n() const {return __p_.n();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const fisher_f_distribution& __x,
                        const fisher_f_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend
        bool operator!=(const fisher_f_distribution& __x,
                        const fisher_f_distribution& __y)
        {return !(__x == __y);}
    };
    
    template <class _RealType>
    template<class _URNG>
    _RealType
    fisher_f_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
    {
        CF::gamma_distribution<result_type> __gdm(__p.m() * result_type(.5));
        CF::gamma_distribution<result_type> __gdn(__p.n() * result_type(.5));
        return __p.n() * __gdm(__g) / (__p.m() * __gdn(__g));
    }
    
        
    // student_t_distribution
    
    template<class _RealType = double>
    class student_t_distribution
    {
    public:
        // types
        typedef _RealType result_type;
        
        class param_type
        {
            result_type __n_;
        public:
            typedef student_t_distribution distribution_type;
            
            explicit param_type(result_type __n = 1) : __n_(__n) {}
            
            result_type n() const {return __n_;}
            
            friend
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__n_ == __y.__n_;}
            friend
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
        };
        
    private:
        param_type __p_;
        normal_distribution<result_type> __nd_;
        
    public:
        // constructor and reset functions
        explicit student_t_distribution(result_type __n = 1)
        : __p_(param_type(__n)) {}
        explicit student_t_distribution(const param_type& __p)
        : __p_(__p) {}
        void reset() {__nd_.reset();}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);
        
        // property functions
        result_type n() const {return __p_.n();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return -std::numeric_limits<result_type>::infinity();}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const student_t_distribution& __x,
                        const student_t_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend
        bool operator!=(const student_t_distribution& __x,
                        const student_t_distribution& __y)
        {return !(__x == __y);}
    };
    
    template <class _RealType>
    template<class _URNG>
    _RealType
    student_t_distribution<_RealType>::operator()(_URNG& __g, const param_type& __p)
    {
        CF::gamma_distribution<result_type> __gd(__p.n() * .5, 2);
        return __nd_(__g) * std::sqrt(__p.n()/__gd(__g));
    }
    
        
    // discrete_distribution
    
    template<class _IntType = int>
    class discrete_distribution
    {
    public:
        // types
        typedef _IntType result_type;
        
        class param_type
        {
            std::vector<double> __p_;
        public:
            typedef discrete_distribution distribution_type;
            
            param_type() {}
            template<class _InputIterator>
            param_type(_InputIterator __f, _InputIterator __l)
            : __p_(__f, __l) {__init();}
            param_type(std::initializer_list<double> __wl)
            : __p_(__wl.begin(), __wl.end()) {__init();}
            template<class _UnaryOperation>
            param_type(size_t __nw, double __xmin, double __xmax,
                       _UnaryOperation __fw);
            
            std::vector<double> probabilities() const;
            
            friend
            bool operator==(const param_type& __x, const param_type& __y)
            {return __x.__p_ == __y.__p_;}
            friend
            bool operator!=(const param_type& __x, const param_type& __y)
            {return !(__x == __y);}
            
        private:
            void __init();
            
            friend class discrete_distribution;
        };
        
    private:
        param_type __p_;
        
    public:
        // constructor and reset functions
        discrete_distribution() {}
        template<class _InputIterator>
        discrete_distribution(_InputIterator __f, _InputIterator __l)
        : __p_(__f, __l) {}
        discrete_distribution(std::initializer_list<double> __wl)
        : __p_(__wl) {}
        template<class _UnaryOperation>
        discrete_distribution(size_t __nw, double __xmin, double __xmax,
                              _UnaryOperation __fw)
        : __p_(__nw, __xmin, __xmax, __fw) {}
        explicit discrete_distribution(const param_type& __p)
        : __p_(__p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& __g)
        {return (*this)(__g, __p_);}
        template<class _URNG> result_type operator()(_URNG& __g, const param_type& __p);
        
        // property functions
        std::vector<double> probabilities() const {return __p_.probabilities();}
        
        param_type param() const {return __p_;}
        void param(const param_type& __p) {__p_ = __p;}
        
        result_type min() const {return 0;}
        result_type max() const {return __p_.__p_.size();}
        
        friend
        bool operator==(const discrete_distribution& __x,
                        const discrete_distribution& __y)
        {return __x.__p_ == __y.__p_;}
        friend
        bool operator!=(const discrete_distribution& __x,
                        const discrete_distribution& __y)
        {return !(__x == __y);}
    };
    
    template<class _IntType>
    template<class _UnaryOperation>
    discrete_distribution<_IntType>::param_type::param_type(size_t __nw,
                                                            double __xmin,
                                                            double __xmax,
                                                            _UnaryOperation __fw)
    {
        if (__nw > 1)
        {
            __p_.reserve(__nw - 1);
            double __d = (__xmax - __xmin) / __nw;
            double __d2 = __d / 2;
            for (size_t __k = 0; __k < __nw; ++__k)
                __p_.push_back(__fw(__xmin + __k * __d + __d2));
            __init();
        }
    }
    
    template<class _IntType>
    void
    discrete_distribution<_IntType>::param_type::__init()
    {
        if (!__p_.empty())
        {
            if (__p_.size() > 1)
            {
                double __s = std::accumulate(__p_.begin(), __p_.end(), 0.0);
                for (std::vector<double>::iterator __i = __p_.begin(), __e = __p_.end();
                     __i < __e; ++__i)
                    *__i /= __s;
                std::vector<double> __t(__p_.size() - 1);
                std::partial_sum(__p_.begin(), __p_.end() - 1, __t.begin());
                std::swap(__p_, __t);
            }
            else
            {
                __p_.clear();
                __p_.shrink_to_fit();
            }
        }
    }
    
    template<class _IntType>
    std::vector<double>
    discrete_distribution<_IntType>::param_type::probabilities() const
    {
        std::size_t __n = __p_.size();
        std::vector<double> __p(__n+1);
        std::adjacent_difference(__p_.begin(), __p_.end(), __p.begin());
        if (__n > 0)
            __p[__n] = 1 - __p_[__n-1];
        else
            __p[0] = 1;
        return __p;
    }
    
    template<class _IntType>
    template<class _URNG>
    _IntType
    discrete_distribution<_IntType>::operator()(_URNG& __g, const param_type& __p)
    {
        CF::uniform_real_distribution<double> __gen;
        return static_cast<_IntType>(
                                     std::upper_bound(__p.__p_.begin(), __p.__p_.end(), __gen(__g)) -
                                     __p.__p_.begin());
    }
    
}

#endif
