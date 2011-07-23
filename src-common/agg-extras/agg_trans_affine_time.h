//----------------------------------------------------------------------------
// Anti-Grain Geometry - Version 2.4
// Copyright (C) 2002-2005 Maxim Shemanarev (http://www.antigrain.com)
// Copyright (C) 2009 John Horigan ( john@glyphic.com )
//
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
//----------------------------------------------------------------------------
// Contact: john@glyphic.com
//          mcseem@antigrain.com
//          mcseemagg@yahoo.com
//          http://www.antigrain.com
//          
//----------------------------------------------------------------------------
//
// Affine transformation classes for time ranges.
//
//----------------------------------------------------------------------------
#ifndef AGG_TRANS_AFFINE_TIME_INCLUDED
#define AGG_TRANS_AFFINE_TIME_INCLUDED

#include <math.h>
#include "agg_basics.h"
#include <cfloat>

namespace agg
{
    const double affine_time_epsilon = 1e-14; 
    
    //============================================================trans_affine_time
    //
    // Affine transformation are linear transformations in Cartesian coordinates
    // (strictly speaking not only in Cartesian, but for the beginning we will 
    // think so). In one dimension, they are scaling and translation.  
    //
    //----------------------------------------------------------------------
    struct trans_affine_time
    {
        double st, tbegin, tend;
        
        //------------------------------------------ Construction
        // Identity matrix
        trans_affine_time() :
        st(1.0), tbegin(0.0), tend(0.0)
        {}
        
        // Custom matrix. Usually used in derived classes
        trans_affine_time(double v0, double v1, double v2) :
        st(v0), tbegin(v1), tend(v2)
        {}
        
        // Custom matrix from m[3]
        explicit trans_affine_time(const double* m) :
        st(m[0]), tbegin(m[1]), tend(m[2])
        {}
        
        //------------------------------------------ Operations
        // Reset - load an identity matrix
        const trans_affine_time& reset();
        
        // Direct transformations operations
        const trans_affine_time& translate(double x, double y);
        const trans_affine_time& translate(double x);
        const trans_affine_time& scale(double s);
        
        // Multiply matrix to another one
        const trans_affine_time& multiply(const trans_affine_time& m);
        
        // Multiply "m" to "this" and assign the result to "this"
        const trans_affine_time& premultiply(const trans_affine_time& m);

        // Check if transform is valid
        bool is_valid(double epsilon = affine_time_epsilon) const;
        
        //------------------------------------------- Load/Store
        // Store matrix to an array [3] of double
        void store_to(double* m) const
        {
            *m++ = st; *m++ = tbegin; *m++ = tend;
        }
        
        // Load matrix from an array [3] of double
        const trans_affine_time& load_from(const double* m)
        {
            st = *m++; tbegin = *m++; tend = *m++;
            return *this;
        }
        
        // Load matrix from 3 doubles
        const trans_affine_time& load_from(double v0, double v1, double v2)
        {
            st = v0; tbegin = v1; tend = v2;
            return *this;
        }
        
        //------------------------------------------- Operators
        
        // Multiply the matrix by another one
        const trans_affine_time& operator *= (const trans_affine_time& m)
        {
            return multiply(m);
        }
        
        // Multiply the matrix by another one and return
        // the result in a separete matrix.
        trans_affine_time operator * (const trans_affine_time& m) const
        {
            return trans_affine_time(*this).multiply(m);
        }
        
        // Equal operator with default epsilon
        bool operator == (const trans_affine_time& m) const
        {
            return is_equal(m, affine_time_epsilon);
        }
        
        // Not Equal operator with default epsilon
        bool operator != (const trans_affine_time& m) const
        {
            return !is_equal(m, affine_time_epsilon);
        }
        
        // Check to see if it's an identity matrix
        bool is_identity(double epsilon = affine_time_epsilon) const;
        
        // Check to see if two matrices are equal
        bool is_equal(const trans_affine_time& m, double epsilon = affine_time_epsilon) const;
        
        // Check to see if two time ranges overlap
        bool overlaps(const trans_affine_time& m) const;
        
        // Determine the major parameters. Use with caution considering 
        // possible degenerate cases.
        void   translation(double* begin, double* end) const;
    };
    
    //------------------------------------------------------------------------
    inline const trans_affine_time& trans_affine_time::premultiply(const trans_affine_time& m)
    {
        trans_affine_time t = m;
        return *this = t.multiply(*this);
    }
    
    //====================================================trans_affine_time_scaling
    // Scaling matrix. x, y - scale coefficients by X and Y respectively
    class trans_affine_time_scaling : public trans_affine_time
        {
        public:
            trans_affine_time_scaling(double s) : 
            trans_affine_time(s, 0.0, 0.0)
            {}
        };
    
    //================================================trans_affine_time_translation
    // Translation matrix
    class trans_affine_time_translation : public trans_affine_time
        {
        public:
            trans_affine_time_translation(double begin, double end) : 
            trans_affine_time(1.0, begin, end)
            {}
        };
        
    //------------------------------------------------------------------------
    inline const trans_affine_time& trans_affine_time::multiply(const trans_affine_time& m)
    {
        st = st * m.st;
        tbegin = tbegin * m.st + m.tbegin;
        tend = tend * m.st + m.tend;
        
        return *this;
    }
    
    //------------------------------------------------------------------------
    inline const trans_affine_time& trans_affine_time::reset()
    {
        st = 1.0; 
        tbegin = 0.0;
        tend = 0.0;
        return *this;
    }
    
    static inline double sign(double a)
    {
        return (a < -affine_time_epsilon) ? -1.0 :
              ((a >  affine_time_epsilon) ? 1.0 : 0.0);
    }
    
    //------------------------------------------------------------------------
    inline const trans_affine_time& trans_affine_time::scale(double s) 
    {
        st *= s;
        tbegin *= s;
        tend *= s;
        return *this;
    }
    
    //------------------------------------------------------------------------
    inline const trans_affine_time& trans_affine_time::translate(double x, double y) 
    {
        tbegin += x;
        tend += y;
        return *this;
    }
    
    //------------------------------------------------------------------------
    inline const trans_affine_time& trans_affine_time::translate(double x) 
    {
        tbegin += x;
        tend += x;
        return *this;
    }
    
    //------------------------------------------------------------------------
    inline bool trans_affine_time::is_identity(double epsilon) const
    {
        return  is_equal_eps(st, 1.0, epsilon) &&
                is_equal_eps(tbegin, 0.0, epsilon) &&
                is_equal_eps(tend, 0.0, epsilon);
    }
    
    //------------------------------------------------------------------------
    inline bool trans_affine_time::is_valid(double epsilon) const
    {
        return fabs(st) > epsilon && tbegin <= tend;
    }
    
    //------------------------------------------------------------------------
    inline bool trans_affine_time::is_equal(const trans_affine_time& m, double epsilon) const
    {
        return  is_equal_eps(st, m.st, epsilon) &&
                is_equal_eps(tbegin, m.tbegin, epsilon) &&
                is_equal_eps(tend, m.tend, epsilon);
    }
    
    //------------------------------------------------------------------------
    inline bool trans_affine_time::overlaps(const trans_affine_time& m) const
    {
        return !(m.tbegin > tend || m.tend < tbegin);
    }
    
    //------------------------------------------------------------------------
    inline void trans_affine_time::translation(double* begin, double* end) const
    {
        *begin = tbegin;
        *end = tend;
    }
    
    
}


#endif

