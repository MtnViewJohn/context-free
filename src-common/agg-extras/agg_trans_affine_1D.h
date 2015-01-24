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
// Affine transformation classes in one dimension.
//
//----------------------------------------------------------------------------
#ifndef AGG_TRANS_AFFINE_1D_INCLUDED
#define AGG_TRANS_AFFINE_1D_INCLUDED

#include <math.h>
#include "agg_basics.h"

namespace agg
{
    const double affine_1D_epsilon = 1e-14; 
    
    //============================================================trans_affine_1D
    //
    // Affine transformation are linear transformations in Cartesian coordinates
    // (strictly speaking not only in Cartesian, but for the beginning we will 
    // think so). In one dimension, they are rotation and translation.  
    //
    //----------------------------------------------------------------------
    struct trans_affine_1D
    {
        double sz, tz;
        
        //------------------------------------------ Construction
        // Identity matrix
        trans_affine_1D() :
        sz(1.0), tz(0.0)
        {}
        
        // Custom matrix. Usually used in derived classes
        trans_affine_1D(double v0, double v1) :
        sz(v0), tz(v1)
        {}
        
        // Custom matrix from m[2]
        explicit trans_affine_1D(const double* m) :
        sz(m[0]), tz(m[1])
        {}
        
        //------------------------------------------ Operations
        // Reset - load an identity matrix
        const trans_affine_1D& reset();
        
        // Direct transformations operations
        const trans_affine_1D& translate(double z);
        const trans_affine_1D& scale(double s);
        
        // Multiply matrix to another one
        const trans_affine_1D& multiply(const trans_affine_1D& m);
        
        // Multiply "m" to "this" and assign the result to "this"
        const trans_affine_1D& premultiply(const trans_affine_1D& m);
        
        // Multiply matrix to inverse of another one
        const trans_affine_1D& multiply_inv(const trans_affine_1D& m);
        
        // Multiply inverse of "m" to "this" and assign the result to "this"
        const trans_affine_1D& premultiply_inv(const trans_affine_1D& m);
        
        // Invert matrix. Do not try to invert degenerate matrices, 
        // there's no check for validity. If you set scale to 0 and 
        // then try to invert matrix, expect unpredictable result.
        const trans_affine_1D& invert();
        
        //------------------------------------------- Load/Store
        // Store matrix to an array [6] of double
        void store_to(double* m) const
        {
            *m++ = sz; *m++ = tz; 
        }
        
        // Load matrix from an array [6] of double
        const trans_affine_1D& load_from(const double* m)
        {
            sz = *m++; tz = *m++; 
            return *this;
        }
        
        //------------------------------------------- Operators
        
        // Multiply the matrix by another one
        const trans_affine_1D& operator *= (const trans_affine_1D& m)
        {
            return multiply(m);
        }
        
        // Multiply the matrix by inverse of another one
        const trans_affine_1D& operator /= (const trans_affine_1D& m)
        {
            return multiply_inv(m);
        }
        
        // Multiply the matrix by another one and return
        // the result in a separete matrix.
        trans_affine_1D operator * (const trans_affine_1D& m) const
        {
            return trans_affine_1D(*this).multiply(m);
        }
        
        // Multiply the matrix by inverse of another one 
        // and return the result in a separete matrix.
        trans_affine_1D operator / (const trans_affine_1D& m) const
        {
            return trans_affine_1D(*this).multiply_inv(m);
        }
        
        // Calculate and return the inverse matrix
        trans_affine_1D operator ~ () const
        {
            trans_affine_1D ret = *this;
            return ret.invert();
        }
        
        // Equal operator with default epsilon
        bool operator == (const trans_affine_1D& m) const
        {
            return is_equal(m, affine_1D_epsilon);
        }
        
        // Not Equal operator with default epsilon
        bool operator != (const trans_affine_1D& m) const
        {
            return !is_equal(m, affine_1D_epsilon);
        }
        
        //-------------------------------------------- Transformations
        // Direct transformation of z
        void transform(double* z) const;
        
        // Inverse transformation of z. It works slower than the 
        // direct transformation. For massive operations it's better to 
        // invert() the matrix and then use direct transformations. 
        void inverse_transform(double* z) const;
        
        //-------------------------------------------- Auxiliary
        // Calculate the determinant of matrix
        double determinant() const
        {
            return sz;
        }
        
        // Calculate the reciprocal of the determinant
        double determinant_reciprocal() const
        {
            return 1.0 / (sz);
        }
        
        double scale() const;
        
        // Check to see if the matrix is not degenerate
        bool is_valid(double epsilon = affine_1D_epsilon) const;
        
        // Check to see if it's an identity matrix
        bool is_identity(double epsilon = affine_1D_epsilon) const;
        
        // Check to see if two matrices are equal
        bool is_equal(const trans_affine_1D& m, double epsilon = affine_1D_epsilon) const;
        
        // Determine the major parameters. Use with caution considering 
        // possible degenerate cases.
        void   translation(double* dz) const;
    };
    
    //------------------------------------------------------------------------
    inline void trans_affine_1D::transform(double* z) const
    {
        *z = *z * sz + tz;
    }
    
    //------------------------------------------------------------------------
    inline void trans_affine_1D::inverse_transform(double* z) const
    {
        double d = determinant_reciprocal();
        *z = (*z - tz) * d;
    }
    
    //------------------------------------------------------------------------
    inline double trans_affine_1D::scale() const
    {
        return fabs(sz);
    }
    
    //------------------------------------------------------------------------
    inline const trans_affine_1D& trans_affine_1D::translate(double z) 
    { 
        tz += z;
        return *this;
    }
    
    //------------------------------------------------------------------------
    inline const trans_affine_1D& trans_affine_1D::scale(double s) 
    {
        double m = s; // Possible hint for the optimizer
        sz  *= m;
        tz  *= m;
        return *this;
    }
    
    //------------------------------------------------------------------------
    inline const trans_affine_1D& trans_affine_1D::premultiply(const trans_affine_1D& m)
    {
        trans_affine_1D t = m;
        return *this = t.multiply(*this);
    }
    
    //------------------------------------------------------------------------
    inline const trans_affine_1D& trans_affine_1D::multiply_inv(const trans_affine_1D& m)
    {
        trans_affine_1D t = m;
        t.invert();
        return multiply(t);
    }
    
    //------------------------------------------------------------------------
    inline const trans_affine_1D& trans_affine_1D::premultiply_inv(const trans_affine_1D& m)
    {
        trans_affine_1D t = m;
        t.invert();
        return *this = t.multiply(*this);
    }
    
    //====================================================trans_affine_1D_scaling
    // Scaling matrix. x, y - scale coefficients by X and Y respectively
    class trans_affine_1D_scaling : public trans_affine_1D
        {
        public:
            trans_affine_1D_scaling(double s) : 
            trans_affine_1D(s, 0.0)
            {}
        };
    
    //================================================trans_affine_1D_translation
    // Translation matrix
    class trans_affine_1D_translation : public trans_affine_1D
        {
        public:
            trans_affine_1D_translation(double z) : 
            trans_affine_1D(1.0, z)
            {}
        };
        
    //------------------------------------------------------------------------
    inline const trans_affine_1D& trans_affine_1D::invert()
    {
        double d  = determinant_reciprocal();

        sz = d;
        tz = -tz * d;
        return *this;
    }
    
    
    //------------------------------------------------------------------------
    inline const trans_affine_1D& trans_affine_1D::multiply(const trans_affine_1D& m)
    {
        sz = sz * m.sz;
        tz = tz * m.sz + m.tz;
        
        return *this;
    }
    
    //------------------------------------------------------------------------
    inline const trans_affine_1D& trans_affine_1D::reset()
    {
        sz = 1.0; 
        tz = 0.0;
        return *this;
    }
    
    //------------------------------------------------------------------------
    inline bool trans_affine_1D::is_identity(double epsilon) const
    {
        return  is_equal_eps(sz, 1.0, epsilon) &&
                is_equal_eps(tz, 0.0, epsilon);
    }
    
    //------------------------------------------------------------------------
    inline bool trans_affine_1D::is_valid(double epsilon) const
    {
        return fabs(sz) > epsilon;
    }
    
    //------------------------------------------------------------------------
    inline bool trans_affine_1D::is_equal(const trans_affine_1D& m, double epsilon) const
    {
        return  is_equal_eps(sz, m.sz, epsilon) &&
                is_equal_eps(tz, m.tz, epsilon);
    }
    
    //------------------------------------------------------------------------
    inline void trans_affine_1D::translation(double* dz) const
    {
        *dz = tz;
    }
    
    
}


#endif

