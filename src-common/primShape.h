// primShape.h
// Context Free
// ---------------------
// Copyright (C) 2006-2012 John Horigan
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

#ifndef INCLUDE_PRIMSHAPE_H
#define INCLUDE_PRIMSHAPE_H

#include "agg_path_storage.h"
#include <initializer_list>
#include <utility>
#include <cassert>

class primShape : public agg::path_storage
{
public:
    enum {circleType = 0, squareType = 1, triangleType = 2, fillType = 3,
    numTypes = 4};
    primShape(std::initializer_list<std::pair<double, double>> l)
    {
        auto p = l.begin();
        assert(p != l.end());
        move_to(p->first, p->second);
        for (++p; p != l.end(); ++p)
            line_to(p->first, p->second);
        end_poly(agg::path_flags_close);
    }
    primShape() = default;
    
    static const primShape circle;
    static const primShape square;
    static const primShape triangle;
    static const primShape* shapeMap[numTypes];
    static bool isPrimShape(unsigned v) { return v < numTypes; }
    static bool isPrimShape(agg::path_storage* p);
};

class primIter
{
public:
    primIter() : mData(nullptr), mIndex(0) {}
    primIter(const primShape* data) : mData(data), mIndex(0) {}
    unsigned vertex(double* x, double* y);
    void rewind(unsigned i);
    void init(const primShape* shape);
private:
    const primShape*    mData;
    unsigned            mIndex;
};
#endif // INCLUDE_PRIMSHAPE_H
