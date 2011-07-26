// shape.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2005-2008 John Horigan - john@glyphic.com
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
// Mark Lentczner can be contacted at markl@glyphic.com or at
// Mark Lentczner, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//


#ifndef INCLUDE_SHAPE_H
#define INCLUDE_SHAPE_H

#include <iostream>
#include <cmath>

#include "agg_math_stroke.h"
#include "agg_trans_affine.h"
#include "agg_trans_affine_1D.h"
#include "agg_trans_affine_time.h"
#include "agg_color_rgba.h"
#include "HSBColor.h"
#include "Rand64.h"
#include "bounds.h"
#include "stacktype.h"

// Contains all of the information about a change to a shape 
class Modification {
    public: 
        agg::trans_affine m_transform;
        agg::trans_affine_1D m_Z;
        agg::trans_affine_time m_time;
        
        HSBColor m_Color;
        HSBColor m_ColorTarget;

        Rand64 mRand64Seed;

        Modification()
        { }
        
        double area() const { return fabs(m_transform.determinant()); }
        bool isFinite() const;
        
        Modification operator*(const Modification& m) const
        {
            Modification n = *this;
            n *= m;
            return n;
        }
        Modification& operator*=(const Modification& m)
        {
            m_transform.premultiply(m.m_transform);
            m_Z.premultiply(m.m_Z);
            m_time.premultiply(m.m_time);
            
            if (m.m_ColorTarget.mUseTarget) {
                m_ColorTarget = m.m_ColorTarget;
                m_Color.adjustWith(m.m_Color, m_ColorTarget);
            } else {
                m_Color.adjustWith(m.m_Color, m_ColorTarget);
                m_ColorTarget.adjustWith(m.m_ColorTarget, m_ColorTarget);
            }
            
            mRand64Seed ^= m.mRand64Seed;
            return *this;
        }
};

class ShapeBase {
public: 
    int mShapeType;
    Modification mWorldState;
    
    double mAreaCache;
    double area() const { return mAreaCache; }
protected:
    ShapeBase() : mShapeType(-1) 
    { mAreaCache = mWorldState.area(); }
    
    void write(std::ostream& os) const;
    void read(std::istream& is);
};

// Contains all of the information about a shape that is used during parsing
// and executing a cfdg file
class Shape : public ShapeBase {
public:
    Shape() : ShapeBase(), mParameters(NULL) {}
    
    const StackType* mParameters;

    Shape operator*(const Modification& m) const {
        Shape s = *this;
        s.mWorldState *= m;
        s.mAreaCache = s.mWorldState.area();
        return s;
    }
    
    Shape& operator*=(const Modification& m) {
        mWorldState *= m;
        mAreaCache = mWorldState.area();
        return *this;
    }
    
    void releaseParams() const
    {
        if (mParameters)
            mParameters->release();
    }
    
    bool operator<(const Shape& b) const { return mAreaCache < b.mAreaCache; }
    
    void write(std::ostream& os) const;
    void read(std::istream& is);
protected:
    void writeParams(std::ostream& os) const;
    void readParams(std::istream& is);
};

class FinishedShape : public Shape {
public:
    Bounds mBounds;
    FinishedShape() : Shape() {}
    FinishedShape(const Shape& s, double totalArea, const Bounds& b)
    {
        mShapeType = s.mShapeType;
        mWorldState = s.mWorldState;
        mAreaCache = totalArea;
        mParameters = s.mParameters;
        mBounds = b;
    };

    bool operator<(const Shape& b) const
    {
        return (mWorldState.m_Z.tz == b.mWorldState.m_Z.tz) ?
        (mAreaCache < b.mAreaCache) :
        (mWorldState.m_Z.tz < b.mWorldState.m_Z.tz);
    }
    
    void write(std::ostream& os) const;
    void read(std::istream& is);
};

inline std::ostream& operator<<(std::ostream& os, const Shape& s) { s.write(os); return os; }
inline std::istream& operator>>(std::istream& is, Shape& s) { s.read(is); return is; }
inline std::ostream& operator<<(std::ostream& os, const FinishedShape& s) { s.write(os); return os; }
inline std::istream& operator>>(std::istream& is, FinishedShape& s) { s.read(is); return is; }


const double MY_PI =  3.14159265358979323846;
const int ModificationSize = (sizeof(Modification) + 7) >> 3;


#endif // INCLUDE_SHAPE_H
