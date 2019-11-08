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
    struct _mr_log2_imp
    {
        static const size_t value = _Xp & ((unsigned long long)(1) << _Rp) ? _Rp
        : _mr_log2_imp<_Xp, _Rp - 1>::value;
    };
    
    template <unsigned long long _Xp>
    struct _mr_log2_imp<_Xp, 0>
    {
        static const size_t value = 0;
    };
    
    template <size_t _Rp>
    struct _mr_log2_imp<0, _Rp>
    {
        static const size_t value = _Rp + 1;
    };
    
    template <class _UI, _UI _Xp>
    struct _mr_log2
    {
        static const size_t value = _mr_log2_imp<_Xp, sizeof(_UI) * 8 - 1>::value;
    };
    
    
    // generate_canonical
    
    template<class _RealType, std::size_t _mr_bits, class _URNG>
    _RealType
    generate_canonical(_URNG& _mr_g)
    {
        const std::size_t _Dt = std::numeric_limits<_RealType>::digits;
        const std::size_t _mr_b = _Dt < _mr_bits ? _Dt : _mr_bits;
#ifdef CF_HAS_NO_CONSTEXPR
        const std::size_t _mr_logR = _mr_log2<std::uint64_t, _URNG::_Max - _URNG::_Min + std::uint64_t(1)>::value;
#else
        const std::size_t _mr_logR = _mr_log2<std::uint64_t, _URNG::max() - _URNG::min() + std::uint64_t(1)>::value;
#endif
        const std::size_t _mr_k = _mr_b / _mr_logR + (_mr_b % _mr_logR != 0) + (_mr_b == 0);
        const _RealType _Rp = _URNG::max() - _URNG::min() + _RealType(1);
        _RealType _mr_base = _Rp;
        _RealType _Sp = _mr_g() - _URNG::min();
        for (std::size_t _mr_i = 1; _mr_i < _mr_k; ++_mr_i, _mr_base *= _Rp)
            _Sp += (_mr_g() - _URNG::min()) * _mr_base;
        return _Sp / _mr_base;
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
            result_type _mr_a_;
            result_type _mr_b_;
        public:
            typedef uniform_real_distribution distribution_type;
            
            explicit param_type(result_type _mr_a = 0,
                                result_type _mr_b = 1)
            : _mr_a_(_mr_a), _mr_b_(_mr_b) {}
            
            result_type a() const {return _mr_a_;}
            result_type b() const {return _mr_b_;}
            
            friend
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_a_ == _mr_y._mr_a_ && _mr_x._mr_b_ == _mr_y._mr_b_;}
            friend
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
        };
        
    private:
        param_type _mr_p_;
        
    public:
        // constructors and reset functions
        explicit uniform_real_distribution(result_type _mr_a = 0, result_type _mr_b = 1)
        : _mr_p_(param_type(_mr_a, _mr_b)) {}
        explicit uniform_real_distribution(const param_type& _mr_p) : _mr_p_(_mr_p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG> result_type operator()(_URNG& _mr_g, const param_type& _mr_p);
        
        // property functions
        result_type a() const {return _mr_p_.a();}
        result_type b() const {return _mr_p_.b();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return a();}
        result_type max() const {return b();}
        
        friend
        bool operator==(const uniform_real_distribution& _mr_x,
                        const uniform_real_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend
        bool operator!=(const uniform_real_distribution& _mr_x,
                        const uniform_real_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
    };
    
    template<class _RealType>
    template<class _URNG>
    inline
    typename uniform_real_distribution<_RealType>::result_type
    uniform_real_distribution<_RealType>::operator()(_URNG& _mr_g, const param_type& _mr_p)
    {
        return (_mr_p.b() - _mr_p.a())
        * generate_canonical<_RealType, std::numeric_limits<_RealType>::digits>(_mr_g)
        + _mr_p.a();
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
            result_type _mr_a_;
            result_type _mr_b_;
        public:
            typedef uniform_int_distribution distribution_type;
            
            explicit param_type(result_type _mr_a = 0,
                                result_type _mr_b = std::numeric_limits<result_type>::max())
            : _mr_a_(_mr_a), _mr_b_(_mr_b) {}
            
            result_type a() const {return _mr_a_;}
            result_type b() const {return _mr_b_;}
            
            friend bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_a_ == _mr_y._mr_a_ && _mr_x._mr_b_ == _mr_y._mr_b_;}
            friend bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
        };
        
    private:
        param_type _mr_p_;
        
    public:
        // constructors and reset functions
        explicit uniform_int_distribution(result_type _mr_a = 0,
                                          result_type _mr_b = std::numeric_limits<result_type>::max())
        : _mr_p_(param_type(_mr_a, _mr_b)) {}
        explicit uniform_int_distribution(const param_type& _mr_p) : _mr_p_(_mr_p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG> result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG> result_type operator()(_URNG& _mr_g, const param_type& _mr_p);
        
        // property functions
        result_type a() const {return _mr_p_.a();}
        result_type b() const {return _mr_p_.b();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return a();}
        result_type max() const {return b();}
        
        friend bool operator==(const uniform_int_distribution& _mr_x,
                               const uniform_int_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend bool operator!=(const uniform_int_distribution& _mr_x,
                               const uniform_int_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
    };
    
    template<class _IntType>
    template<class _URNG>
    typename uniform_int_distribution<_IntType>::result_type
    uniform_int_distribution<_IntType>::operator()(_URNG& _mr_g, const param_type& _mr_p)
    {
        typedef typename _URNG::result_type eng_type;
        static_assert(sizeof(eng_type) >= sizeof(result_type),
                      "quick & dirty int distribution won't work");
        
        typename _URNG::result_type diff = static_cast<eng_type>(_mr_p.b()) -
                                           static_cast<eng_type>(_mr_p.a()) + 1;
        if (diff == 0)
            return static_cast<result_type>(_mr_g() - _mr_g.min());
        
        eng_type tooBig = _mr_g.max() - _mr_g.min();
        tooBig -= tooBig % diff;
        
        for(;;) {
            eng_type gen = _mr_g() - _mr_g.min();
            
            if (gen < tooBig)
                return static_cast<result_type>(gen % diff) + _mr_p.a();
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
            result_type _mr_t_;
            double _mr_p_;
            double _mr_pr_;
            double _mr_odds_ratio_;
            result_type _mr_r0_;
        public:
            typedef binomial_distribution distribution_type;
            
            explicit param_type(result_type _mr_t = 1, double _mr_p = 0.5);
            
            inline
            result_type t() const {return _mr_t_;}
            inline
            double p() const {return _mr_p_;}
            
            friend inline
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_t_ == _mr_y._mr_t_ && _mr_x._mr_p_ == _mr_y._mr_p_;}
            friend inline
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
            
            friend class binomial_distribution;
        };
        
    private:
        param_type _mr_p_;
        
    public:
        // constructors and reset functions
        explicit binomial_distribution(result_type _mr_t = 1, double _mr_p = 0.5)
        : _mr_p_(param_type(_mr_t, _mr_p)) {}
        explicit binomial_distribution(const param_type& _mr_p) : _mr_p_(_mr_p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG> result_type operator()(_URNG& _mr_g, const param_type& _mr_p);
        
        // property functions
        result_type t() const {return _mr_p_.t();}
        double p() const {return _mr_p_.p();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return 0;}
        result_type max() const {return t();}
        
        friend inline
        bool operator==(const binomial_distribution& _mr_x,
                        const binomial_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend inline
        bool operator!=(const binomial_distribution& _mr_x,
                        const binomial_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
    };
    
    template<class _IntType>
    binomial_distribution<_IntType>::param_type::param_type(result_type _mr_t, double _mr_p)
    : _mr_t_(_mr_t), _mr_p_(_mr_p)
    {
        if (0 < _mr_p_ && _mr_p_ < 1)
        {
            _mr_r0_ = static_cast<result_type>((_mr_t_ + 1) * _mr_p_);
            _mr_pr_ = std::exp(std::lgamma(_mr_t_ + 1.) - std::lgamma(_mr_r0_ + 1.) -
                               std::lgamma(_mr_t_ - _mr_r0_ + 1.) + _mr_r0_ * std::log(_mr_p_) +
                               (_mr_t_ - _mr_r0_) * std::log(1 - _mr_p_));
            _mr_odds_ratio_ = _mr_p_ / (1 - _mr_p_);
        }
        else
        {
            _mr_r0_ = _mr_pr_ = _mr_odds_ratio_ = 0;
        }
    }
    
    template<class _IntType>
    template<class _URNG>
    _IntType
    binomial_distribution<_IntType>::operator()(_URNG& _mr_g, const param_type& _mr_pr)
    {
        if (_mr_pr._mr_t_ == 0 || _mr_pr._mr_p_ == 0)
            return 0;
        if (_mr_pr._mr_p_ == 1)
            return _mr_pr._mr_t_;
        uniform_real_distribution<double> _mr_gen;
        double _mr_u = _mr_gen(_mr_g) - _mr_pr._mr_pr_;
        if (_mr_u < 0)
            return _mr_pr._mr_r0_;
        double _mr_pu = _mr_pr._mr_pr_;
        double _mr_pd = _mr_pu;
        result_type _mr_ru = _mr_pr._mr_r0_;
        result_type _mr_rd = _mr_ru;
        while (true)
        {
            if (_mr_rd >= 1)
            {
                _mr_pd *= _mr_rd / (_mr_pr._mr_odds_ratio_ * (_mr_pr._mr_t_ - _mr_rd + 1));
                _mr_u -= _mr_pd;
                if (_mr_u < 0)
                    return _mr_rd - 1;
            }
            --_mr_rd;
            ++_mr_ru;
            if (_mr_ru <= _mr_pr._mr_t_)
            {
                _mr_pu *= (_mr_pr._mr_t_ - _mr_ru + 1) * _mr_pr._mr_odds_ratio_ / _mr_ru;
                _mr_u -= _mr_pu;
                if (_mr_u < 0)
                    return _mr_ru;
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
            double _mr_p_;
        public:
            typedef bernoulli_distribution distribution_type;
            
            explicit param_type(double _mr_p = 0.5) : _mr_p_(_mr_p) {}
            
            double p() const {return _mr_p_;}
            
            friend
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_p_ == _mr_y._mr_p_;}
            friend
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
        };
        
    private:
        param_type _mr_p_;
        
    public:
        // constructors and reset functions
        explicit bernoulli_distribution(double _mr_p = 0.5)
        : _mr_p_(param_type(_mr_p)) {}
        explicit bernoulli_distribution(const param_type& _mr_p) : _mr_p_(_mr_p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG> result_type operator()(_URNG& _mr_g, const param_type& _mr_p);
        
        // property functions
        double p() const {return _mr_p_.p();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return false;}
        result_type max() const {return true;}
        
        friend
        bool operator==(const bernoulli_distribution& _mr_x,
                        const bernoulli_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend
        bool operator!=(const bernoulli_distribution& _mr_x,
                        const bernoulli_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
    };
    
    template<class _URNG>
    inline
    bernoulli_distribution::result_type
    bernoulli_distribution::operator()(_URNG& _mr_g, const param_type& _mr_p)
    {
        CF::uniform_real_distribution<double> _mr_gen;
        return _mr_gen(_mr_g) < _mr_p.p();
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
            result_type _mr_lambda_;
        public:
            typedef exponential_distribution distribution_type;
            
            explicit param_type(result_type _mr_lambda = 1) : _mr_lambda_(_mr_lambda) {}
            
            result_type lambda() const {return _mr_lambda_;}
            
            friend
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_lambda_ == _mr_y._mr_lambda_;}
            friend
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
        };
        
    private:
        param_type _mr_p_;
        
    public:
        // constructors and reset functions
        explicit exponential_distribution(result_type _mr_lambda = 1)
        : _mr_p_(param_type(_mr_lambda)) {}
        explicit exponential_distribution(const param_type& _mr_p) : _mr_p_(_mr_p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG> result_type operator()(_URNG& _mr_g, const param_type& _mr_p);
        
        // property functions
        result_type lambda() const {return _mr_p_.lambda();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const exponential_distribution& _mr_x,
                        const exponential_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend
        bool operator!=(const exponential_distribution& _mr_x,
                        const exponential_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
    };
    
    template <class _RealType>
    template<class _URNG>
    _RealType
    exponential_distribution<_RealType>::operator()(_URNG& _mr_g, const param_type& _mr_p)
    {
        return -std::log
        (
         result_type(1) -
         CF::generate_canonical<result_type, std::numeric_limits<result_type>::digits>(_mr_g)
         )
        / _mr_p.lambda();
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
            result_type _mr_mean_;
            result_type _mr_stddev_;
        public:
            typedef normal_distribution distribution_type;
            
            explicit param_type(result_type _mr_mean = 0, result_type _mr_stddev = 1)
            : _mr_mean_(_mr_mean), _mr_stddev_(_mr_stddev) {}
            
            result_type mean() const {return _mr_mean_;}
            result_type stddev() const {return _mr_stddev_;}
            
            friend
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_mean_ == _mr_y._mr_mean_ && _mr_x._mr_stddev_ == _mr_y._mr_stddev_;}
            friend
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
        };
        
    private:
        param_type _mr_p_;
        result_type _V_;
        bool _V_hot_;
        
    public:
        // constructors and reset functions
        explicit normal_distribution(result_type _mr_mean = 0, result_type _mr_stddev = 1)
        : _mr_p_(param_type(_mr_mean, _mr_stddev)), _V_hot_(false) {}
        explicit normal_distribution(const param_type& _mr_p)
        : _mr_p_(_mr_p), _V_hot_(false) {}
        void reset() {_V_hot_ = false;}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG> result_type operator()(_URNG& _mr_g, const param_type& _mr_p);
        
        // property functions
        result_type mean() const {return _mr_p_.mean();}
        result_type stddev() const {return _mr_p_.stddev();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return -std::numeric_limits<result_type>::infinity();}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const normal_distribution& _mr_x,
                        const normal_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_ && _mr_x._V_hot_ == _mr_y._V_hot_ &&
            (!_mr_x._V_hot_ || _mr_x._V_ == _mr_y._V_);}
        friend
        bool operator!=(const normal_distribution& _mr_x,
                        const normal_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
    };
    
    template <class _RealType>
    template<class _URNG>
    _RealType
    normal_distribution<_RealType>::operator()(_URNG& _mr_g, const param_type& _mr_p)
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
            result_type _mr_u;
            result_type _mr_v;
            result_type _mr_s;
            do
            {
                _mr_u = _Uni(_mr_g);
                _mr_v = _Uni(_mr_g);
                _mr_s = _mr_u * _mr_u + _mr_v * _mr_v;
            } while (_mr_s > 1 || _mr_s == 0);
            result_type _Fp = std::sqrt(-2 * std::log(_mr_s) / _mr_s);
            _V_ = _mr_v * _Fp;
            _V_hot_ = true;
            _Up = _mr_u * _Fp;
        }
        return _Up * _mr_p.stddev() + _mr_p.mean();
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
            double _mr_mean_;
            double _mr_s_;
            double _mr_d_;
            double _mr_l_;
            double _mr_omega_;
            double _mr_c0_;
            double _mr_c1_;
            double _mr_c2_;
            double _mr_c3_;
            double _mr_c_;
            
        public:
            typedef poisson_distribution distribution_type;
            
            explicit param_type(double _mr_mean = 1.0);
            
            double mean() const {return _mr_mean_;}
            
            friend
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_mean_ == _mr_y._mr_mean_;}
            friend
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
            
            friend class poisson_distribution;
        };
        
    private:
        param_type _mr_p_;
        
    public:
        // constructors and reset functions
        explicit poisson_distribution(double _mr_mean = 1.0) : _mr_p_(_mr_mean) {}
        explicit poisson_distribution(const param_type& _mr_p) : _mr_p_(_mr_p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG> result_type operator()(_URNG& _mr_g, const param_type& _mr_p);
        
        // property functions
        double mean() const {return _mr_p_.mean();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::max();}
        
        friend
        bool operator==(const poisson_distribution& _mr_x,
                        const poisson_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend
        bool operator!=(const poisson_distribution& _mr_x,
                        const poisson_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
    };
    
    template<class _IntType>
    poisson_distribution<_IntType>::param_type::param_type(double _mr_mean)
    : _mr_mean_(_mr_mean)
    {
        if (_mr_mean_ < 10)
        {
            _mr_s_ = 0;
            _mr_d_ = 0;
            _mr_l_ = std::exp(-_mr_mean_);
            _mr_omega_ = 0;
            _mr_c3_ = 0;
            _mr_c2_ = 0;
            _mr_c1_ = 0;
            _mr_c0_ = 0;
            _mr_c_ = 0;
        }
        else
        {
            _mr_s_ = std::sqrt(_mr_mean_);
            _mr_d_ = 6 * _mr_mean_ * _mr_mean_;
            _mr_l_ = static_cast<result_type>(_mr_mean_ - 1.1484);
            _mr_omega_ = .3989423 / _mr_s_;
            double _mr_b1_ = .4166667E-1 / _mr_mean_;
            double _mr_b2_ = .3 * _mr_b1_ * _mr_b1_;
            _mr_c3_ = .1428571 * _mr_b1_ * _mr_b2_;
            _mr_c2_ = _mr_b2_ - 15. * _mr_c3_;
            _mr_c1_ = _mr_b1_ - 6. * _mr_b2_ + 45. * _mr_c3_;
            _mr_c0_ = 1. - _mr_b1_ + 3. * _mr_b2_ - 15. * _mr_c3_;
            _mr_c_ = .1069 / _mr_mean_;
        }
    }
    
    template <class _IntType>
    template<class _URNG>
    _IntType
    poisson_distribution<_IntType>::operator()(_URNG& _mr_urng, const param_type& _mr_pr)
    {
        result_type _mr_x = 0;
        CF::uniform_real_distribution<double> _mr_urd;
        if (_mr_pr._mr_mean_ < 10)
        {
            _mr_x = 0;
            for (double _mr_p = _mr_urd(_mr_urng); _mr_p > _mr_pr._mr_l_; ++_mr_x)
                _mr_p *= _mr_urd(_mr_urng);
        }
        else
        {
            double _mr_difmuk = 0;
            double _mr_g = _mr_pr._mr_mean_ + _mr_pr._mr_s_ * CF::normal_distribution<double>()(_mr_urng);
            double _mr_u = 0;
            if (_mr_g >= 0)
            {
                _mr_x = static_cast<result_type>(_mr_g);
                if (_mr_x >= _mr_pr._mr_l_)
                    return _mr_x;
                _mr_difmuk = _mr_pr._mr_mean_ - _mr_x;
                _mr_u = _mr_urd(_mr_urng);
                if (_mr_pr._mr_d_ * _mr_u >= _mr_difmuk * _mr_difmuk * _mr_difmuk)
                    return _mr_x;
            }
            CF::exponential_distribution<double> _mr_edist;
            for (bool _mr_using_exp_dist = false; true; _mr_using_exp_dist = true)
            {
                double _mr_e;
                if (_mr_using_exp_dist || _mr_g < 0)
                {
                    double _mr_t;
                    do
                    {
                        _mr_e = _mr_edist(_mr_urng);
                        _mr_u = _mr_urd(_mr_urng);
                        _mr_u += _mr_u - 1;
                        _mr_t = 1.8 + (_mr_u < 0 ? -_mr_e : _mr_e);
                    } while (_mr_t <= -.6744);
                    _mr_x = _mr_pr._mr_mean_ + _mr_pr._mr_s_ * _mr_t;
                    _mr_difmuk = _mr_pr._mr_mean_ - _mr_x;
                    _mr_using_exp_dist = true;
                }
                double _mr_px;
                double _mr_py;
                if (_mr_x < 10)
                {
                    const result_type _mr_fac[] = {1, 1, 2, 6, 24, 120, 720, 5040,
                        40320, 362880};
                    _mr_px = -_mr_pr._mr_mean_;
                    _mr_py = std::pow(_mr_pr._mr_mean_, (double)_mr_x) / _mr_fac[_mr_x];
                }
                else
                {
                    double _mr_del = .8333333E-1 / _mr_x;
                    _mr_del -= 4.8 * _mr_del * _mr_del * _mr_del;
                    double _mr_v = _mr_difmuk / _mr_x;
                    if (std::abs(_mr_v) > 0.25)
                        _mr_px = _mr_x * std::log(1 + _mr_v) - _mr_difmuk - _mr_del;
                    else
                        _mr_px = _mr_x * _mr_v * _mr_v * (((((((.1250060 * _mr_v + -.1384794) *
                                                       _mr_v + .1421878) * _mr_v + -.1661269) * _mr_v + .2000118) *
                                                    _mr_v + -.2500068) * _mr_v + .3333333) * _mr_v + -.5) - _mr_del;
                    _mr_py = .3989423 / std::sqrt(_mr_x);
                }
                double _mr_r = (0.5 - _mr_difmuk) / _mr_pr._mr_s_;
                double _mr_r2 = _mr_r * _mr_r;
                double _mr_fx = -0.5 * _mr_r2;
                double _mr_fy = _mr_pr._mr_omega_ * (((_mr_pr._mr_c3_ * _mr_r2 + _mr_pr._mr_c2_) *
                                                _mr_r2 + _mr_pr._mr_c1_) * _mr_r2 + _mr_pr._mr_c0_);
                if (_mr_using_exp_dist)
                {
                    if (_mr_pr._mr_c_ * std::abs(_mr_u) <= _mr_py * std::exp(_mr_px + _mr_e) -
                        _mr_fy * std::exp(_mr_fx + _mr_e))
                        break;
                }
                else
                {
                    if (_mr_fy - _mr_u * _mr_fy <= _mr_py * std::exp(_mr_px - _mr_fx))
                        break;
                }
            }
        }
        return _mr_x;
    }
        
        
#ifdef _mr_alpha
#undef _mr_alpha
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
            result_type _mr_alpha_;
            result_type _mr_beta_;
        public:
            typedef gamma_distribution distribution_type;
            
            explicit param_type(result_type _mr_alpha = 1, result_type _mr_beta = 1)
            : _mr_alpha_(_mr_alpha), _mr_beta_(_mr_beta) {}
            
            result_type alpha() const {return _mr_alpha_;}
            result_type beta() const {return _mr_beta_;}
            
            friend
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_alpha_ == _mr_y._mr_alpha_ && _mr_x._mr_beta_ == _mr_y._mr_beta_;}
            friend
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
        };
        
    private:
        param_type _mr_p_;
        
    public:
        // constructors and reset functions
        explicit gamma_distribution(result_type _mr_alpha = 1, result_type _mr_beta = 1)
        : _mr_p_(param_type(_mr_alpha, _mr_beta)) {}
        explicit gamma_distribution(const param_type& _mr_p)
        : _mr_p_(_mr_p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG> result_type operator()(_URNG& _mr_g, const param_type& _mr_p);
        
        // property functions
        result_type alpha() const {return _mr_p_.alpha();}
        result_type beta() const {return _mr_p_.beta();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const gamma_distribution& _mr_x,
                        const gamma_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend
        bool operator!=(const gamma_distribution& _mr_x,
                        const gamma_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
    };
    
    template <class _RealType>
    template<class _URNG>
    _RealType
    gamma_distribution<_RealType>::operator()(_URNG& _mr_g, const param_type& _mr_p)
    {
        result_type _mr_a = _mr_p.alpha();
        CF::uniform_real_distribution<result_type> _mr_gen(0, 1);
        CF::exponential_distribution<result_type> _mr_egen;
        result_type _mr_x;
        if (_mr_a == 1)
            _mr_x = _mr_egen(_mr_g);
        else if (_mr_a > 1)
        {
            const result_type _mr_b = _mr_a - 1;
            const result_type _mr_c = 3 * _mr_a - result_type(0.75);
            while (true)
            {
                const result_type _mr_u = _mr_gen(_mr_g);
                const result_type _mr_v = _mr_gen(_mr_g);
                const result_type _mr_w = _mr_u * (1 - _mr_u);
                if (_mr_w != 0)
                {
                    const result_type _mr_y = std::sqrt(_mr_c / _mr_w) *
                    (_mr_u - result_type(0.5));
                    _mr_x = _mr_b + _mr_y;
                    if (_mr_x >= 0)
                    {
                        const result_type _mr_z = 64 * _mr_w * _mr_w * _mr_w * _mr_v * _mr_v;
                        if (_mr_z <= 1 - 2 * _mr_y * _mr_y / _mr_x)
                            break;
                        if (std::log(_mr_z) <= 2 * (_mr_b * std::log(_mr_x / _mr_b) - _mr_y))
                            break;
                    }
                }
            }
        }
        else  // _mr_a < 1
        {
            while (true)
            {
                const result_type _mr_u = _mr_gen(_mr_g);
                const result_type _mr_es = _mr_egen(_mr_g);
                if (_mr_u <= 1 - _mr_a)
                {
                    _mr_x = std::pow(_mr_u, 1 / _mr_a);
                    if (_mr_x <= _mr_es)
                        break;
                }
                else
                {
                    const result_type _mr_e = -std::log((1-_mr_u)/_mr_a);
                    _mr_x = std::pow(1 - _mr_a + _mr_a * _mr_e, 1 / _mr_a);
                    if (_mr_x <= _mr_e + _mr_es)
                        break;
                }
            }
        }
        return _mr_x * _mr_p.beta();
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
            result_type _mr_k_;
            double _mr_p_;
        public:
            typedef negative_binomial_distribution distribution_type;
            
            explicit param_type(result_type _mr_k = 1, double _mr_p = 0.5)
            : _mr_k_(_mr_k), _mr_p_(_mr_p) {}
            
            result_type k() const {return _mr_k_;}
            double p() const {return _mr_p_;}
            
            friend
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_k_ == _mr_y._mr_k_ && _mr_x._mr_p_ == _mr_y._mr_p_;}
            friend
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
        };
        
    private:
        param_type _mr_p_;
        
    public:
        // constructor and reset functions
        explicit negative_binomial_distribution(result_type _mr_k = 1, double _mr_p = 0.5)
        : _mr_p_(_mr_k, _mr_p) {}
        explicit negative_binomial_distribution(const param_type& _mr_p) : _mr_p_(_mr_p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG> result_type operator()(_URNG& _mr_g, const param_type& _mr_p);
        
        // property functions
        result_type k() const {return _mr_p_.k();}
        double p() const {return _mr_p_.p();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::max();}
        
        friend
        bool operator==(const negative_binomial_distribution& _mr_x,
                        const negative_binomial_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend
        bool operator!=(const negative_binomial_distribution& _mr_x,
                        const negative_binomial_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
    };
    
    template <class _IntType>
    template<class _URNG>
    _IntType
    negative_binomial_distribution<_IntType>::operator()(_URNG& _mr_urng, const param_type& _mr_pr)
    {
        result_type _mr_k = _mr_pr.k();
        double _mr_p = _mr_pr.p();
        if (_mr_k <= 21 * _mr_p)
        {
            bernoulli_distribution _mr_gen(_mr_p);
            result_type _mr_f = 0;
            result_type _mr_s = 0;
            while (_mr_s < _mr_k)
            {
                if (_mr_gen(_mr_urng))
                    ++_mr_s;
                else
                    ++_mr_f;
            }
            return _mr_f;
        }
        return CF::poisson_distribution<result_type>(CF::gamma_distribution<double>
                                                 (_mr_k, (1-_mr_p)/_mr_p)(_mr_urng))(_mr_urng);
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
            double _mr_p_;
        public:
            typedef geometric_distribution distribution_type;
            
            explicit param_type(double _mr_p = 0.5) : _mr_p_(_mr_p) {}
            
            double p() const {return _mr_p_;}
            
            friend
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_p_ == _mr_y._mr_p_;}
            friend
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
        };
        
    private:
        param_type _mr_p_;
        
    public:
        // constructors and reset functions
        explicit geometric_distribution(double _mr_p = 0.5) : _mr_p_(_mr_p) {}
        explicit geometric_distribution(const param_type& _mr_p) : _mr_p_(_mr_p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG>
        result_type operator()(_URNG& _mr_g, const param_type& _mr_p)
        {return CF::negative_binomial_distribution<result_type>(1, _mr_p.p())(_mr_g);}
        
        // property functions
        double p() const {return _mr_p_.p();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::max();}
        
        friend
        bool operator==(const geometric_distribution& _mr_x,
                        const geometric_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend
        bool operator!=(const geometric_distribution& _mr_x,
                        const geometric_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
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
            result_type _mr_a_;
            result_type _mr_b_;
        public:
            typedef weibull_distribution distribution_type;
            
            explicit param_type(result_type _mr_a = 1, result_type _mr_b = 1)
            : _mr_a_(_mr_a), _mr_b_(_mr_b) {}
            
            result_type a() const {return _mr_a_;}
            result_type b() const {return _mr_b_;}
            
            friend
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_a_ == _mr_y._mr_a_ && _mr_x._mr_b_ == _mr_y._mr_b_;}
            friend
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
        };
        
    private:
        param_type _mr_p_;
        
    public:
        // constructor and reset functions
        explicit weibull_distribution(result_type _mr_a = 1, result_type _mr_b = 1)
        : _mr_p_(param_type(_mr_a, _mr_b)) {}
        explicit weibull_distribution(const param_type& _mr_p)
        : _mr_p_(_mr_p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG>
        result_type operator()(_URNG& _mr_g, const param_type& _mr_p)
        {return _mr_p.b() *
            std::pow(CF::exponential_distribution<result_type>()(_mr_g), 1/_mr_p.a());}
        
        // property functions
        result_type a() const {return _mr_p_.a();}
        result_type b() const {return _mr_p_.b();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const weibull_distribution& _mr_x,
                        const weibull_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend
        bool operator!=(const weibull_distribution& _mr_x,
                        const weibull_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
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
            result_type _mr_a_;
            result_type _mr_b_;
        public:
            typedef extreme_value_distribution distribution_type;
            
            explicit param_type(result_type _mr_a = 0, result_type _mr_b = 1)
            : _mr_a_(_mr_a), _mr_b_(_mr_b) {}
            
            result_type a() const {return _mr_a_;}
            result_type b() const {return _mr_b_;}
            
            friend
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_a_ == _mr_y._mr_a_ && _mr_x._mr_b_ == _mr_y._mr_b_;}
            friend
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
        };
        
    private:
        param_type _mr_p_;
        
    public:
        // constructor and reset functions
        explicit extreme_value_distribution(result_type _mr_a = 0, result_type _mr_b = 1)
        : _mr_p_(param_type(_mr_a, _mr_b)) {}
        explicit extreme_value_distribution(const param_type& _mr_p)
        : _mr_p_(_mr_p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG> result_type operator()(_URNG& _mr_g, const param_type& _mr_p);
        
        // property functions
        result_type a() const {return _mr_p_.a();}
        result_type b() const {return _mr_p_.b();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return -std::numeric_limits<result_type>::infinity();}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const extreme_value_distribution& _mr_x,
                        const extreme_value_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend
        bool operator!=(const extreme_value_distribution& _mr_x,
                        const extreme_value_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
    };
    
    template<class _RealType>
    template<class _URNG>
    _RealType
    extreme_value_distribution<_RealType>::operator()(_URNG& _mr_g, const param_type& _mr_p)
    {
        return _mr_p.a() - _mr_p.b() *
        std::log(-std::log(1-CF::uniform_real_distribution<result_type>()(_mr_g)));
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
            CF::normal_distribution<result_type> _mr_nd_;
        public:
            typedef lognormal_distribution distribution_type;
            
            explicit param_type(result_type _mr_m = 0, result_type _mr_s = 1)
            : _mr_nd_(_mr_m, _mr_s) {}
            
            result_type m() const {return _mr_nd_.mean();}
            result_type s() const {return _mr_nd_.stddev();}
            
            friend
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_nd_ == _mr_y._mr_nd_;}
            friend
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
            friend class lognormal_distribution;
        };
        
    private:
        param_type _mr_p_;
        
    public:
        // constructor and reset functions
        explicit lognormal_distribution(result_type _mr_m = 0, result_type _mr_s = 1)
        : _mr_p_(param_type(_mr_m, _mr_s)) {}
        explicit lognormal_distribution(const param_type& _mr_p)
        : _mr_p_(_mr_p) {}
        void reset() {_mr_p_._mr_nd_.reset();}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG>
        result_type operator()(_URNG& _mr_g, const param_type& _mr_p)
        {return std::exp(const_cast<CF::normal_distribution<result_type>&>(_mr_p._mr_nd_)(_mr_g));}
        
        // property functions
        result_type m() const {return _mr_p_.m();}
        result_type s() const {return _mr_p_.s();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const lognormal_distribution& _mr_x,
                        const lognormal_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend
        bool operator!=(const lognormal_distribution& _mr_x,
                        const lognormal_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
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
            result_type _mr_n_;
        public:
            typedef chi_squared_distribution distribution_type;
            
            explicit param_type(result_type _mr_n = 1) : _mr_n_(_mr_n) {}
            
            result_type n() const {return _mr_n_;}
            
            friend
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_n_ == _mr_y._mr_n_;}
            friend
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
        };
        
    private:
        param_type _mr_p_;
        
    public:
        // constructor and reset functions
        explicit chi_squared_distribution(result_type _mr_n = 1)
        : _mr_p_(param_type(_mr_n)) {}
        explicit chi_squared_distribution(const param_type& _mr_p)
        : _mr_p_(_mr_p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG>
        result_type operator()(_URNG& _mr_g, const param_type& _mr_p)
        {return CF::gamma_distribution<result_type>(_mr_p.n() / 2, 2)(_mr_g);}
        
        // property functions
        result_type n() const {return _mr_p_.n();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const chi_squared_distribution& _mr_x,
                        const chi_squared_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend
        bool operator!=(const chi_squared_distribution& _mr_x,
                        const chi_squared_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
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
            result_type _mr_a_;
            result_type _mr_b_;
        public:
            typedef cauchy_distribution distribution_type;
            
            explicit param_type(result_type _mr_a = 0, result_type _mr_b = 1)
            : _mr_a_(_mr_a), _mr_b_(_mr_b) {}
            
            result_type a() const {return _mr_a_;}
            result_type b() const {return _mr_b_;}
            
            friend
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_a_ == _mr_y._mr_a_ && _mr_x._mr_b_ == _mr_y._mr_b_;}
            friend
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
        };
        
    private:
        param_type _mr_p_;
        
    public:
        // constructor and reset functions
        explicit cauchy_distribution(result_type _mr_a = 0, result_type _mr_b = 1)
        : _mr_p_(param_type(_mr_a, _mr_b)) {}
        explicit cauchy_distribution(const param_type& _mr_p)
        : _mr_p_(_mr_p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG> result_type operator()(_URNG& _mr_g, const param_type& _mr_p);
        
        // property functions
        result_type a() const {return _mr_p_.a();}
        result_type b() const {return _mr_p_.b();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return -std::numeric_limits<result_type>::infinity();}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const cauchy_distribution& _mr_x,
                        const cauchy_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend
        bool operator!=(const cauchy_distribution& _mr_x,
                        const cauchy_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
    };
    
    template <class _RealType>
    template<class _URNG>
    inline
    _RealType
    cauchy_distribution<_RealType>::operator()(_URNG& _mr_g, const param_type& _mr_p)
    {
        CF::uniform_real_distribution<result_type> _mr_gen;
        // purposefully let tan arg get as close to pi/2 as it wants, tan will return a finite
        return _mr_p.a() + _mr_p.b() * std::tan(3.1415926535897932384626433832795 * _mr_gen(_mr_g));
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
            result_type _mr_m_;
            result_type _mr_n_;
        public:
            typedef fisher_f_distribution distribution_type;
            
            explicit param_type(result_type _mr_m = 1, result_type _mr_n = 1)
            : _mr_m_(_mr_m), _mr_n_(_mr_n) {}
            
            result_type m() const {return _mr_m_;}
            result_type n() const {return _mr_n_;}
            
            friend
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_m_ == _mr_y._mr_m_ && _mr_x._mr_n_ == _mr_y._mr_n_;}
            friend
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
        };
        
    private:
        param_type _mr_p_;
        
    public:
        // constructor and reset functions
        explicit fisher_f_distribution(result_type _mr_m = 1, result_type _mr_n = 1)
        : _mr_p_(param_type(_mr_m, _mr_n)) {}
        explicit fisher_f_distribution(const param_type& _mr_p)
        : _mr_p_(_mr_p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG> result_type operator()(_URNG& _mr_g, const param_type& _mr_p);
        
        // property functions
        result_type m() const {return _mr_p_.m();}
        result_type n() const {return _mr_p_.n();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return 0;}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const fisher_f_distribution& _mr_x,
                        const fisher_f_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend
        bool operator!=(const fisher_f_distribution& _mr_x,
                        const fisher_f_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
    };
    
    template <class _RealType>
    template<class _URNG>
    _RealType
    fisher_f_distribution<_RealType>::operator()(_URNG& _mr_g, const param_type& _mr_p)
    {
        CF::gamma_distribution<result_type> _mr_gdm(_mr_p.m() * result_type(.5));
        CF::gamma_distribution<result_type> _mr_gdn(_mr_p.n() * result_type(.5));
        return _mr_p.n() * _mr_gdm(_mr_g) / (_mr_p.m() * _mr_gdn(_mr_g));
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
            result_type _mr_n_;
        public:
            typedef student_t_distribution distribution_type;
            
            explicit param_type(result_type _mr_n = 1) : _mr_n_(_mr_n) {}
            
            result_type n() const {return _mr_n_;}
            
            friend
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_n_ == _mr_y._mr_n_;}
            friend
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
        };
        
    private:
        param_type _mr_p_;
        normal_distribution<result_type> _mr_nd_;
        
    public:
        // constructor and reset functions
        explicit student_t_distribution(result_type _mr_n = 1)
        : _mr_p_(param_type(_mr_n)) {}
        explicit student_t_distribution(const param_type& _mr_p)
        : _mr_p_(_mr_p) {}
        void reset() {_mr_nd_.reset();}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG> result_type operator()(_URNG& _mr_g, const param_type& _mr_p);
        
        // property functions
        result_type n() const {return _mr_p_.n();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return -std::numeric_limits<result_type>::infinity();}
        result_type max() const {return std::numeric_limits<result_type>::infinity();}
        
        friend
        bool operator==(const student_t_distribution& _mr_x,
                        const student_t_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend
        bool operator!=(const student_t_distribution& _mr_x,
                        const student_t_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
    };
    
    template <class _RealType>
    template<class _URNG>
    _RealType
    student_t_distribution<_RealType>::operator()(_URNG& _mr_g, const param_type& _mr_p)
    {
        CF::gamma_distribution<result_type> _mr_gd(_mr_p.n() * .5, 2);
        return _mr_nd_(_mr_g) * std::sqrt(_mr_p.n()/_mr_gd(_mr_g));
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
            std::vector<double> _mr_p_;
        public:
            typedef discrete_distribution distribution_type;
            
            param_type() {}
            template<class _InputIterator>
            param_type(_InputIterator _mr_f, _InputIterator _mr_l)
            : _mr_p_(_mr_f, _mr_l) {_mr_init();}
            param_type(std::initializer_list<double> _mr_wl)
            : _mr_p_(_mr_wl.begin(), _mr_wl.end()) {_mr_init();}
            template<class _UnaryOperation>
            param_type(size_t _mr_nw, double _mr_xmin, double _mr_xmax,
                       _UnaryOperation _mr_fw);
            
            std::vector<double> probabilities() const;
            
            friend
            bool operator==(const param_type& _mr_x, const param_type& _mr_y)
            {return _mr_x._mr_p_ == _mr_y._mr_p_;}
            friend
            bool operator!=(const param_type& _mr_x, const param_type& _mr_y)
            {return !(_mr_x == _mr_y);}
            
        private:
            void _mr_init();
            
            friend class discrete_distribution;
        };
        
    private:
        param_type _mr_p_;
        
    public:
        // constructor and reset functions
        discrete_distribution() {}
        template<class _InputIterator>
        discrete_distribution(_InputIterator _mr_f, _InputIterator _mr_l)
        : _mr_p_(_mr_f, _mr_l) {}
        discrete_distribution(std::initializer_list<double> _mr_wl)
        : _mr_p_(_mr_wl) {}
        template<class _UnaryOperation>
        discrete_distribution(size_t _mr_nw, double _mr_xmin, double _mr_xmax,
                              _UnaryOperation _mr_fw)
        : _mr_p_(_mr_nw, _mr_xmin, _mr_xmax, _mr_fw) {}
        explicit discrete_distribution(const param_type& _mr_p)
        : _mr_p_(_mr_p) {}
        void reset() {}
        
        // generating functions
        template<class _URNG>
        result_type operator()(_URNG& _mr_g)
        {return (*this)(_mr_g, _mr_p_);}
        template<class _URNG> result_type operator()(_URNG& _mr_g, const param_type& _mr_p);
        
        // property functions
        std::vector<double> probabilities() const {return _mr_p_.probabilities();}
        
        param_type param() const {return _mr_p_;}
        void param(const param_type& _mr_p) {_mr_p_ = _mr_p;}
        
        result_type min() const {return 0;}
        result_type max() const {return _mr_p_._mr_p_.size();}
        
        friend
        bool operator==(const discrete_distribution& _mr_x,
                        const discrete_distribution& _mr_y)
        {return _mr_x._mr_p_ == _mr_y._mr_p_;}
        friend
        bool operator!=(const discrete_distribution& _mr_x,
                        const discrete_distribution& _mr_y)
        {return !(_mr_x == _mr_y);}
    };
    
    template<class _IntType>
    template<class _UnaryOperation>
    discrete_distribution<_IntType>::param_type::param_type(size_t _mr_nw,
                                                            double _mr_xmin,
                                                            double _mr_xmax,
                                                            _UnaryOperation _mr_fw)
    {
        if (_mr_nw > 1)
        {
            _mr_p_.reserve(_mr_nw - 1);
            double _mr_d = (_mr_xmax - _mr_xmin) / _mr_nw;
            double _mr_d2 = _mr_d / 2;
            for (size_t _mr_k = 0; _mr_k < _mr_nw; ++_mr_k)
                _mr_p_.push_back(_mr_fw(_mr_xmin + _mr_k * _mr_d + _mr_d2));
            _mr_init();
        }
    }
    
    template<class _IntType>
    void
    discrete_distribution<_IntType>::param_type::_mr_init()
    {
        if (!_mr_p_.empty())
        {
            if (_mr_p_.size() > 1)
            {
                double _mr_s = std::accumulate(_mr_p_.begin(), _mr_p_.end(), 0.0);
                for (std::vector<double>::iterator _mr_i = _mr_p_.begin(), _mr_e = _mr_p_.end();
                     _mr_i < _mr_e; ++_mr_i)
                    *_mr_i /= _mr_s;
                std::vector<double> _mr_t(_mr_p_.size() - 1);
                std::partial_sum(_mr_p_.begin(), _mr_p_.end() - 1, _mr_t.begin());
                std::swap(_mr_p_, _mr_t);
            }
            else
            {
                _mr_p_.clear();
                _mr_p_.shrink_to_fit();
            }
        }
    }
    
    template<class _IntType>
    std::vector<double>
    discrete_distribution<_IntType>::param_type::probabilities() const
    {
        std::size_t _mr_n = _mr_p_.size();
        std::vector<double> _mr_p(_mr_n+1);
        std::adjacent_difference(_mr_p_.begin(), _mr_p_.end(), _mr_p.begin());
        if (_mr_n > 0)
            _mr_p[_mr_n] = 1 - _mr_p_[_mr_n-1];
        else
            _mr_p[0] = 1;
        return _mr_p;
    }
    
    template<class _IntType>
    template<class _URNG>
    _IntType
    discrete_distribution<_IntType>::operator()(_URNG& _mr_g, const param_type& _mr_p)
    {
        CF::uniform_real_distribution<double> _mr_gen;
        return static_cast<_IntType>(
                                     std::upper_bound(_mr_p._mr_p_.begin(), _mr_p._mr_p_.end(), _mr_gen(_mr_g)) -
                                     _mr_p._mr_p_.begin());
    }
    
}

#endif
