// bounds.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006-2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2006-2013 John Horigan - john@glyphic.com
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


#ifndef INCLUDE_BOUNDS_H
#define INCLUDE_BOUNDS_H

#include "agg_path_storage.h"
#include <limits>
#include <cmath>

#ifdef _WIN32
#include <float.h>
#define myfinite _finite
#else
#define myfinite std::isfinite
#endif

namespace agg { struct trans_affine; }
namespace AST { 
    class ASTpathCommand; 
    struct CommandInfo; 
}
class pathIterator; 

class Bounds {
    public:
        Bounds() : mMin_X(std::numeric_limits<double>::infinity()) {}

        Bounds(const agg::trans_affine& trans, pathIterator& helper, 
               double scale, const AST::CommandInfo& attr);
                // set bounds to be the bounds of this shape, transformed

        bool valid() const { return myfinite(mMin_X) && myfinite(mMax_X) &&
                                    myfinite(mMin_Y) && myfinite(mMax_Y); }
        void invalidate() { mMin_X = std::numeric_limits<double>::infinity(); }
    
        Bounds dilate(double dilation) const;

        void merge(const Bounds& b)
            // merge the other bounds into this bounds
        {
            if (valid() && b.valid()) {
                if (b.mMin_X < mMin_X) mMin_X = b.mMin_X;
                if (b.mMax_X > mMax_X) mMax_X = b.mMax_X;
                if (b.mMin_Y < mMin_Y) mMin_Y = b.mMin_Y;
                if (b.mMax_Y > mMax_Y) mMax_Y = b.mMax_Y;
            } else if (b.valid()) {
                *this = b;
            }
        }

        void merge(double x, double y)
        // merge a point into this bounds
        {
            if (valid()) {
                if (x < mMin_X) mMin_X = x;
                if (x > mMax_X) mMax_X = x;
                if (y < mMin_Y) mMin_Y = y;
                if (y > mMax_Y) mMax_Y = y;
            } else {
                mMin_X = mMax_X = x;
                mMin_Y = mMax_Y = y;
            }
        }
        
        void merge(const agg::point_d& p) { merge(p.x, p.y); }
        // merge a point into this bounds
    
        Bounds operator+(const Bounds& other) const
        { Bounds t(*this); t.merge(other); return t; }
        
        Bounds& operator+=(const Bounds& other)
        { merge(other); return *this; }
        
        Bounds operator+(const agg::point_d& p) const
        { Bounds t(*this); t.merge(p); return t; }
        
        Bounds& operator+=(const agg::point_d& p)
        { merge(p); return *this; }
        
        Bounds interpolate(const Bounds& other, double alpha) const;
        // compute the interpolation between this bounds and the other
        // an alpha of 0.0 has no effect, an alpha of 1.0 give the other
        Bounds slewCenter(const Bounds& other, double alpha) const;
        // compute a new bounds who's center is slewed alpha of the way
        // toward the other center, yet incorporates all of the current
        // bounds
        
        double computeScale(int& width, int& height, double borderX, double borderY,
                            bool modify = false, agg::trans_affine* trans = nullptr,
                            bool exact = false) const;
        // Computes the scale factor of fitting this bounds into a canvas
        // of the given width and height, with the provided fixed border.
        // If modify is true, width and height are reset to the scaled size.
        // If trans isn't null, it is set to the needed transformation.
        // If exact is true then the diensions are not bumped to preserve parity.
        
        void gather(const Bounds& other, double weight);
        
        void update(const agg::trans_affine& trns, pathIterator& helper, 
                    double scale, const AST::CommandInfo& attr);
    
        double  mMin_X, mMin_Y, mMax_X, mMax_Y;
};

#endif // INCLUDE_BOUNDS_H
