//----------------------------------------------------------------------------
// Anti-Grain Geometry - Version 2.4
// Copyright (C) 2002-2005 Maxim Shemanarev (http://www.antigrain.com)
//
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
//----------------------------------------------------------------------------
//
// Adaptation for high precision colors has been sponsored by 
// Liberty Technology Systems, Inc., visit http://lib-sys.com
//
// Liberty Technology Systems, Inc. is the provider of
// PostScript and PDF technology for software developers.
// 
//----------------------------------------------------------------------------
// Contact: mcseem@antigrain.com
//          mcseemagg@yahoo.com
//          http://www.antigrain.com
//----------------------------------------------------------------------------

#ifndef AGG_COLOR_RGBA_INCLUDED
#define AGG_COLOR_RGBA_INCLUDED

#include <math.h>
#include "agg_basics.h"

namespace agg
{
    struct gray8;
    struct gray16;
    
    // Supported byte orders for RGB and RGBA pixel formats
    //=======================================================================
    struct order_rgb  { enum rgb_e  { R=0, G=1, B=2, rgb_tag, hasAlpha=false }; };       //----order_rgb
    struct order_bgr  { enum bgr_e  { B=0, G=1, R=2, rgb_tag, hasAlpha=false }; };       //----order_bgr
    struct order_rgba { enum rgba_e { R=0, G=1, B=2, A=3, rgba_tag, hasAlpha=true }; }; //----order_rgba
    struct order_argb { enum argb_e { A=0, R=1, G=2, B=3, rgba_tag, hasAlpha=true }; }; //----order_argb
    struct order_abgr { enum abgr_e { A=0, B=1, G=2, R=3, rgba_tag, hasAlpha=true }; }; //----order_abgr
    struct order_bgra { enum bgra_e { B=0, G=1, R=2, A=3, rgba_tag, hasAlpha=true }; }; //----order_bgra

    //====================================================================rgba
    struct rgba
    {
        typedef double value_type;

        double r;
        double g;
        double b;
        double a;

        //--------------------------------------------------------------------
        rgba() {}

        //--------------------------------------------------------------------
        rgba(double r_, double g_, double b_, double a_=1.0) :
            r(r_), g(g_), b(b_), a(a_) {}

        //--------------------------------------------------------------------
        rgba(const rgba& c, double a_) : r(c.r), g(c.g), b(c.b), a(a_) {}

        //--------------------------------------------------------------------
        void clear()
        {
            r = g = b = a = 0;
        }

        //--------------------------------------------------------------------
        const rgba& transparent()
        {
            a = 0.0;
            return *this;
        }

        //--------------------------------------------------------------------
        const rgba& opacity(double a_)
        {
            if(a_ < 0.0) a_ = 0.0;
            if(a_ > 1.0) a_ = 1.0;
            a = a_;
            return *this;
        }

        //--------------------------------------------------------------------
        double opacity() const
        {
            return a;
        }

        //--------------------------------------------------------------------
        const rgba& premultiply()
        {
            r *= a;
            g *= a;
            b *= a;
            return *this;
        }

        //--------------------------------------------------------------------
        const rgba& premultiply(double a_)
        {
            if(a <= 0.0 || a_ <= 0.0)
            {
                r = g = b = a = 0.0;
                return *this;
            }
            a_ /= a;
            r *= a_;
            g *= a_;
            b *= a_;
            a  = a_;
            return *this;
        }

        //--------------------------------------------------------------------
        const rgba& demultiply()
        {
            if(a == 0)
            {
                r = g = b = 0;
                return *this;
            }
            double a_ = 1.0 / a;
            r *= a_;
            g *= a_;
            b *= a_;
            return *this;
        }


        //--------------------------------------------------------------------
        rgba gradient(rgba c, double k) const
        {
            rgba ret;
            ret.r = r + (c.r - r) * k;
            ret.g = g + (c.g - g) * k;
            ret.b = b + (c.b - b) * k;
            ret.a = a + (c.a - a) * k;
            return ret;
        }

        //--------------------------------------------------------------------
        static rgba no_color() { return rgba(0,0,0,0); }

        //--------------------------------------------------------------------
        static rgba from_wavelength(double wl, double gamma = 1.0);
	
        //--------------------------------------------------------------------
        explicit rgba(double wavelen, double gamma=1.0)
        {
            *this = from_wavelength(wavelen, gamma);
        }

    };

    //----------------------------------------------------------------rgba_pre
    inline rgba rgba_pre(double r, double g, double b, double a=1.0)
    {
        return rgba(r, g, b, a).premultiply();
    }
    inline rgba rgba_pre(const rgba& c)
    {
        return rgba(c).premultiply();
    }
    inline rgba rgba_pre(const rgba& c, double a)
    {
        return rgba(c, a).premultiply();
    }

    //------------------------------------------------------------------------
    inline rgba rgba::from_wavelength(double wl, double gamma)
    {
        rgba t(0.0, 0.0, 0.0);

        if(wl >= 380.0 && wl <= 440.0)
        {
            t.r = -1.0 * (wl - 440.0) / (440.0 - 380.0);
            t.b = 1.0;
        }
        else 
        if(wl >= 440.0 && wl <= 490.0)
        {
            t.g = (wl - 440.0) / (490.0 - 440.0);
            t.b = 1.0;
        }
        else
        if(wl >= 490.0 && wl <= 510.0)
        {
            t.g = 1.0;
            t.b = -1.0 * (wl - 510.0) / (510.0 - 490.0);
        }
        else
        if(wl >= 510.0 && wl <= 580.0)
        {
            t.r = (wl - 510.0) / (580.0 - 510.0);
            t.g = 1.0;
        }
        else
        if(wl >= 580.0 && wl <= 645.0)
        {
            t.r = 1.0;
            t.g = -1.0 * (wl - 645.0) / (645.0 - 580.0);
        }
        else
        if(wl >= 645.0 && wl <= 780.0)
        {
            t.r = 1.0;
        }

        double s = 1.0;
        if(wl > 700.0)       s = 0.3 + 0.7 * (780.0 - wl) / (780.0 - 700.0);
        else if(wl <  420.0) s = 0.3 + 0.7 * (wl - 380.0) / (420.0 - 380.0);

        t.r = pow(t.r * s, gamma);
        t.g = pow(t.g * s, gamma);
        t.b = pow(t.b * s, gamma);
        return t;
    }



    
    //===================================================================rgba8
    struct rgba8
    {
        typedef int8u  value_type;
        typedef int32u calc_type;
        typedef int32  long_type;
        enum base_scale_e
        {
            base_shift = 8,
            base_scale = 1 << base_shift,
            base_mask  = base_scale - 1,
            base_MSB = 1 << (base_shift - 1)
        };
        typedef rgba8 self_type;


        value_type r;
        value_type g;
        value_type b;
        value_type a;

        //--------------------------------------------------------------------
        rgba8() {}

        //--------------------------------------------------------------------
        rgba8(unsigned r_, unsigned g_, unsigned b_, unsigned a_=base_mask) :
            r(value_type(r_)), 
            g(value_type(g_)), 
            b(value_type(b_)), 
            a(value_type(a_)) {}

        //--------------------------------------------------------------------
        rgba8(const rgba& c, double a_) :
            r((value_type)uround(c.r * double(base_mask))), 
            g((value_type)uround(c.g * double(base_mask))), 
            b((value_type)uround(c.b * double(base_mask))), 
            a((value_type)uround(a_  * double(base_mask))) {}

        //--------------------------------------------------------------------
        rgba8(const self_type& c, unsigned a_) :
            r(c.r), g(c.g), b(c.b), a(value_type(a_)) {}

        //--------------------------------------------------------------------
        rgba8(const rgba& c) :
            r((value_type)uround(c.r * double(base_mask))), 
            g((value_type)uround(c.g * double(base_mask))), 
            b((value_type)uround(c.b * double(base_mask))), 
            a((value_type)uround(c.a * double(base_mask))) {}

        //--------------------------------------------------------------------
        rgba8(const gray8& c);

        //--------------------------------------------------------------------
        // fixed-point multiply, exact over uint8
        static AGG_INLINE calc_type int_mult(calc_type a, calc_type b) 
        {
            calc_type t = a * b + base_MSB;
            return ((t >> base_shift) + t) >> base_shift;
        }
        
        //--------------------------------------------------------------------
        // fixed-point multiply, exact over uint8
        // specifically for multiplying a color component by a cover
        static AGG_INLINE calc_type int_mult_cover(calc_type a, calc_type b) 
        {
            return int_mult(a, b);
        }
        
        //--------------------------------------------------------------------
        // linear interpolate q over p by a, assuming q is pre-muliplied by a
        static AGG_INLINE calc_type int_prelerp(calc_type p, calc_type q, calc_type a) 
        {
            return p + q - int_mult(p, a);
        }
        
        //--------------------------------------------------------------------
        // linear interpolate q over p by a
        static AGG_INLINE calc_type int_lerp(calc_type p, calc_type q, calc_type a) 
        {
            return p + int_mult(q - p, a);
        }
        
        //--------------------------------------------------------------------
        void clear()
        {
            r = g = b = a = 0;
        }
        
        //--------------------------------------------------------------------
        const self_type& transparent()
        {
            a = 0;
            return *this;
        }

        //--------------------------------------------------------------------
        const self_type& opacity(double a_)
        {
            if(a_ < 0.0) a_ = 0.0;
            if(a_ > 1.0) a_ = 1.0;
            a = (value_type)uround(a_ * double(base_mask));
            return *this;
        }

        //--------------------------------------------------------------------
        double opacity() const
        {
            return double(a) / double(base_mask);
        }

        //--------------------------------------------------------------------
        AGG_INLINE const self_type& premultiply()
        {
            if(a == base_mask) return *this;
            if(a == 0)
            {
                r = g = b = 0;
                return *this;
            }
            r = (value_type)int_mult(r, a);
            g = (value_type)int_mult(g, a);
            b = (value_type)int_mult(b, a);
            return *this;
        }

        //--------------------------------------------------------------------
        AGG_INLINE const self_type& premultiply(unsigned a_)
        {
            if(a == base_mask && a_ >= base_mask) return *this;
            if(a == 0 || a_ == 0)
            {
                r = g = b = a = 0;
                return *this;
            }
            calc_type r_ = (calc_type(r) * a_) / a;
            calc_type g_ = (calc_type(g) * a_) / a;
            calc_type b_ = (calc_type(b) * a_) / a;
            r = value_type((r_ > a_) ? a_ : r_);
            g = value_type((g_ > a_) ? a_ : g_);
            b = value_type((b_ > a_) ? a_ : b_);
            a = value_type(a_);
            return *this;
        }

        //--------------------------------------------------------------------
        AGG_INLINE const self_type& demultiply()
        {
            if(a == base_mask) return *this;
            if(a == 0)
            {
                r = g = b = 0;
                return *this;
            }
            calc_type r_ = (calc_type(r) * base_mask) / a;
            calc_type g_ = (calc_type(g) * base_mask) / a;
            calc_type b_ = (calc_type(b) * base_mask) / a;
            r = value_type((r_ > calc_type(base_mask)) ? calc_type(base_mask) : r_);
            g = value_type((g_ > calc_type(base_mask)) ? calc_type(base_mask) : g_);
            b = value_type((b_ > calc_type(base_mask)) ? calc_type(base_mask) : b_);
            return *this;
        }

        //--------------------------------------------------------------------
        AGG_INLINE self_type gradient(const self_type& c, double k) const
        {
            self_type ret;
            calc_type ik = uround(k * base_mask);
            ret.r = (value_type)int_lerp(r, c.r, ik);
            ret.g = (value_type)int_lerp(g, c.g, ik);
            ret.b = (value_type)int_lerp(b, c.b, ik);
            ret.a = (value_type)int_lerp(a, c.a, ik);
            return ret;
        }

        //--------------------------------------------------------------------
        AGG_INLINE void add(const self_type& c, unsigned cover)
        {
            calc_type cr, cg, cb, ca;
            if(cover == cover_mask)
            {
                if(c.a == base_mask) 
                {
                    *this = c;
                    return;
                }
                else
                {
                    cr = r + c.r; 
                    cg = g + c.g; 
                    cb = b + c.b; 
                    ca = a + c.a; 
                }
            }
            else
            {
                cr = r + int_mult_cover(c.r, cover);
                cg = g + int_mult_cover(c.g, cover);
                cb = b + int_mult_cover(c.b, cover);
                ca = a + int_mult_cover(c.a, cover);
            }
            r = (value_type)((cr > calc_type(base_mask)) ? calc_type(base_mask) : cr);
            g = (value_type)((cg > calc_type(base_mask)) ? calc_type(base_mask) : cg);
            b = (value_type)((cb > calc_type(base_mask)) ? calc_type(base_mask) : cb);
            a = (value_type)((ca > calc_type(base_mask)) ? calc_type(base_mask) : ca);
        }

        //--------------------------------------------------------------------
        template<class GammaLUT>
        AGG_INLINE void apply_gamma_dir(const GammaLUT& gamma)
        {
            r = gamma.dir(r);
            g = gamma.dir(g);
            b = gamma.dir(b);
        }

        //--------------------------------------------------------------------
        template<class GammaLUT>
        AGG_INLINE void apply_gamma_inv(const GammaLUT& gamma)
        {
            r = gamma.inv(r);
            g = gamma.inv(g);
            b = gamma.inv(b);
        }

        //--------------------------------------------------------------------
        static self_type no_color() { return self_type(0,0,0,0); }

        //--------------------------------------------------------------------
        static self_type from_wavelength(double wl, double gamma = 1.0)
        {
            return self_type(rgba::from_wavelength(wl, gamma));
        }
    };


    //-------------------------------------------------------------rgba8_pre
    inline rgba8 rgba8_pre(unsigned r, unsigned g, unsigned b, 
                           unsigned a = rgba8::base_mask)
    {
        return rgba8(r,g,b,a).premultiply();
    }
    inline rgba8 rgba8_pre(const rgba8& c)
    {
        return rgba8(c).premultiply();
    }
    inline rgba8 rgba8_pre(const rgba8& c, unsigned a)
    {
        return rgba8(c,a).premultiply();
    }
    inline rgba8 rgba8_pre(const rgba& c)
    {
        return rgba8(c).premultiply();
    }
    inline rgba8 rgba8_pre(const rgba& c, double a)
    {
        return rgba8(c,a).premultiply();
    }


    //-------------------------------------------------------------rgb8_packed
    inline rgba8 rgb8_packed(unsigned v)
    {
        return rgba8((v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF);
    }

    //-------------------------------------------------------------bgr8_packed
    inline rgba8 bgr8_packed(unsigned v)
    {
        return rgba8(v & 0xFF, (v >> 8) & 0xFF, (v >> 16) & 0xFF);
    }

    //------------------------------------------------------------argb8_packed
    inline rgba8 argb8_packed(unsigned v)
    {
        return rgba8((v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF, v >> 24);
    }

    //---------------------------------------------------------rgba8_gamma_dir
    template<class GammaLUT>
    rgba8 rgba8_gamma_dir(rgba8 c, const GammaLUT& gamma)
    {
        return rgba8(gamma.dir(c.r), gamma.dir(c.g), gamma.dir(c.b), c.a);
    }

    //---------------------------------------------------------rgba8_gamma_inv
    template<class GammaLUT>
    rgba8 rgba8_gamma_inv(rgba8 c, const GammaLUT& gamma)
    {
        return rgba8(gamma.inv(c.r), gamma.inv(c.g), gamma.inv(c.b), c.a);
    }





    //==================================================================rgba16
    struct rgba16
    {
        typedef int16u value_type;
        typedef int32u calc_type;
        typedef int64  long_type;
        enum base_scale_e
        {
            base_shift = 16,
            base_scale = 1 << base_shift,
            base_mask  = base_scale - 1,
            base_MSB = 1 << (base_shift - 1)
        };
        typedef rgba16 self_type;

        value_type r;
        value_type g;
        value_type b;
        value_type a;

        //--------------------------------------------------------------------
        rgba16() {}

        //--------------------------------------------------------------------
        rgba16(unsigned r_, unsigned g_, unsigned b_, unsigned a_=base_mask) :
            r(value_type(r_)), 
            g(value_type(g_)), 
            b(value_type(b_)), 
            a(value_type(a_)) {}

        //--------------------------------------------------------------------
        rgba16(const self_type& c, unsigned a_) :
            r(c.r), g(c.g), b(c.b), a(value_type(a_)) {}

        //--------------------------------------------------------------------
        rgba16(const rgba& c) :
            r((value_type)uround(c.r * double(base_mask))), 
            g((value_type)uround(c.g * double(base_mask))), 
            b((value_type)uround(c.b * double(base_mask))), 
            a((value_type)uround(c.a * double(base_mask))) {}

        //--------------------------------------------------------------------
        rgba16(const rgba& c, double a_) :
            r((value_type)uround(c.r * double(base_mask))), 
            g((value_type)uround(c.g * double(base_mask))), 
            b((value_type)uround(c.b * double(base_mask))), 
            a((value_type)uround(a_  * double(base_mask))) {}

        //--------------------------------------------------------------------
        rgba16(const rgba8& c) :
            r(value_type((value_type(c.r) << 8) | c.r)), 
            g(value_type((value_type(c.g) << 8) | c.g)), 
            b(value_type((value_type(c.b) << 8) | c.b)), 
            a(value_type((value_type(c.a) << 8) | c.a)) {}

        //--------------------------------------------------------------------
        rgba16(const rgba8& c, unsigned a_) :
            r(value_type((value_type(c.r) << 8) | c.r)), 
            g(value_type((value_type(c.g) << 8) | c.g)), 
            b(value_type((value_type(c.b) << 8) | c.b)), 
            a(value_type((             a_ << 8) | c.a)) {}

        //--------------------------------------------------------------------
        rgba16(const gray16& c);

        //--------------------------------------------------------------------
        // fixed-point multiply, exact over uint16
        static AGG_INLINE calc_type int_mult(calc_type a, calc_type b) 
        {
            calc_type t = a * b + base_MSB;
            return ((t >> base_shift) + t) >> base_shift;
        }
        
        //--------------------------------------------------------------------
        // fixed-point multiply, almost exact over uint16
        // specifically for multiplying a color component by a cover
        static AGG_INLINE calc_type int_mult_cover(calc_type a, calc_type b) 
        {
            return int_mult(a, (b << 8) | b);
        }
        
        //--------------------------------------------------------------------
        // linear interpolate q over p by a, assuming q is pre-muliplied by a
        static AGG_INLINE calc_type int_prelerp(calc_type p, calc_type q, calc_type a) 
        {
            return p + q - int_mult(p, a);
        }
        
        //--------------------------------------------------------------------
        // linear interpolate q over p by a
        static AGG_INLINE calc_type int_lerp(calc_type p, calc_type q, calc_type a) 
        {
            return p + int_mult(q - p, a);
        }
        
        //--------------------------------------------------------------------
        void clear()
        {
            r = g = b = a = 0;
        }
        
        //--------------------------------------------------------------------
        const self_type& transparent()
        {
            a = 0;
            return *this;
        }

        //--------------------------------------------------------------------
        AGG_INLINE const self_type& opacity(double a_)
        {
            if(a_ < 0.0) a_ = 0.0;
            if(a_ > 1.0) a_ = 1.0;
            a = (value_type)uround(a_ * double(base_mask));
            return *this;
        }

        //--------------------------------------------------------------------
        double opacity() const
        {
            return double(a) / double(base_mask);
        }

        //--------------------------------------------------------------------
        AGG_INLINE const self_type& premultiply()
        {
            if(a == base_mask) return *this;
            if(a == 0)
            {
                r = g = b = 0;
                return *this;
            }
            r = (value_type)int_mult(r, a);
            g = (value_type)int_mult(g, a);
            b = (value_type)int_mult(b, a);
            return *this;
        }

        //--------------------------------------------------------------------
        AGG_INLINE const self_type& premultiply(unsigned a_)
        {
            if(a == base_mask && a_ >= base_mask) return *this;
            if(a == 0 || a_ == 0)
            {
                r = g = b = a = 0;
                return *this;
            }
            calc_type r_ = (calc_type(r) * a_) / a;
            calc_type g_ = (calc_type(g) * a_) / a;
            calc_type b_ = (calc_type(b) * a_) / a;
            r = value_type((r_ > a_) ? a_ : r_);
            g = value_type((g_ > a_) ? a_ : g_);
            b = value_type((b_ > a_) ? a_ : b_);
            a = value_type(a_);
            return *this;
        }

        //--------------------------------------------------------------------
        AGG_INLINE const self_type& demultiply()
        {
            if(a == base_mask) return *this;
            if(a == 0)
            {
                r = g = b = 0;
                return *this;
            }
            calc_type r_ = (calc_type(r) * base_mask) / a;
            calc_type g_ = (calc_type(g) * base_mask) / a;
            calc_type b_ = (calc_type(b) * base_mask) / a;
            r = value_type((r_ > calc_type(base_mask)) ? calc_type(base_mask) : r_);
            g = value_type((g_ > calc_type(base_mask)) ? calc_type(base_mask) : g_);
            b = value_type((b_ > calc_type(base_mask)) ? calc_type(base_mask) : b_);
            return *this;
        }

        //--------------------------------------------------------------------
        AGG_INLINE self_type gradient(const self_type& c, double k) const
        {
            self_type ret;
            calc_type ik = uround(k * base_mask);
            ret.r = (value_type)int_lerp(r, c.r, ik);
            ret.g = (value_type)int_lerp(g, c.g, ik);
            ret.b = (value_type)int_lerp(b, c.b, ik);
            ret.a = (value_type)int_lerp(a, c.a, ik);
            return ret;
        }

        //--------------------------------------------------------------------
        AGG_INLINE void add(const self_type& c, unsigned cover)
        {
            calc_type cr, cg, cb, ca;
            if(cover == cover_mask)
            {
                if(c.a == base_mask) 
                {
                    *this = c;
                    return;
                }
                else
                {
                    cr = r + c.r; 
                    cg = g + c.g; 
                    cb = b + c.b; 
                    ca = a + c.a; 
                }
            }
            else
            {
                cr = r + int_mult_cover(c.r, cover);
                cg = g + int_mult_cover(c.g, cover);
                cb = b + int_mult_cover(c.b, cover);
                ca = a + int_mult_cover(c.a, cover);
            }
            r = (value_type)((cr > calc_type(base_mask)) ? calc_type(base_mask) : cr);
            g = (value_type)((cg > calc_type(base_mask)) ? calc_type(base_mask) : cg);
            b = (value_type)((cb > calc_type(base_mask)) ? calc_type(base_mask) : cb);
            a = (value_type)((ca > calc_type(base_mask)) ? calc_type(base_mask) : ca);
        }

        //--------------------------------------------------------------------
        template<class GammaLUT>
        AGG_INLINE void apply_gamma_dir(const GammaLUT& gamma)
        {
            r = gamma.dir(r);
            g = gamma.dir(g);
            b = gamma.dir(b);
        }

        //--------------------------------------------------------------------
        template<class GammaLUT>
        AGG_INLINE void apply_gamma_inv(const GammaLUT& gamma)
        {
            r = gamma.inv(r);
            g = gamma.inv(g);
            b = gamma.inv(b);
        }

        //--------------------------------------------------------------------
        static self_type no_color() { return self_type(0,0,0,0); }

        //--------------------------------------------------------------------
        static self_type from_wavelength(double wl, double gamma = 1.0)
        {
            return self_type(rgba::from_wavelength(wl, gamma));
        }
    };



    //--------------------------------------------------------------rgba16_pre
    inline rgba16 rgba16_pre(unsigned r, unsigned g, unsigned b, 
                             unsigned a = rgba16::base_mask)
    {
        return rgba16(r,g,b,a).premultiply();
    }
    inline rgba16 rgba16_pre(const rgba16& c, unsigned a)
    {
        return rgba16(c,a).premultiply();
    }
    inline rgba16 rgba16_pre(const rgba& c)
    {
        return rgba16(c).premultiply();
    }
    inline rgba16 rgba16_pre(const rgba& c, double a)
    {
        return rgba16(c,a).premultiply();
    }
    inline rgba16 rgba16_pre(const rgba8& c)
    {
        return rgba16(c).premultiply();
    }
    inline rgba16 rgba16_pre(const rgba8& c, unsigned a)
    {
        return rgba16(c,a).premultiply();
    }


    //------------------------------------------------------rgba16_gamma_dir
    template<class GammaLUT>
    rgba16 rgba16_gamma_dir(rgba16 c, const GammaLUT& gamma)
    {
        return rgba16(gamma.dir(c.r), gamma.dir(c.g), gamma.dir(c.b), c.a);
    }

    //------------------------------------------------------rgba16_gamma_inv
    template<class GammaLUT>
    rgba16 rgba16_gamma_inv(rgba16 c, const GammaLUT& gamma)
    {
        return rgba16(gamma.inv(c.r), gamma.inv(c.g), gamma.inv(c.b), c.a);
    }


}



#endif
