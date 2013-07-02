// primShape.cpp
// Context Free
// ---------------------
// Copyright (C) 2006-2011 John Horigan
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

#include "primShape.h"
#include <math.h>
#include "agg_basics.h"

using namespace agg;

#ifndef M_PI
#define M_PI        3.14159265358979323846
#endif

static const double h = 0.5 / cos(M_PI/6.0);
static const double hp = h;
static const double hn = -h / 2.0;
static const double t = sqrt(2.0) / 4.0;

const primShape primShape::square = {
    {  0.5,  0.5 },
    { -0.5,  0.5 },
    { -0.5, -0.5 },
    {  0.5, -0.5 }
};

const primShape primShape::triangle = {
    { 0.0, hp },
    {-0.5, hn },
    { 0.5, hn }
};

const primShape primShape::circle = {
    { 0.5,  0.0 },
    {   t,    t },
    { 0.0,  0.5 },
    {  -t,    t },
    {-0.5,  0.0 },
    {  -t,   -t },
    { 0.0, -0.5 },
    {   t,   -t }
};
const primShape* primShape::shapeMap[numTypes] = { 
    &primShape::circle, 
    &primShape::square, 
    &primShape::triangle,
    0
};

bool primShape::isPrimShape(agg::path_storage* p)
{
    return (p == &circle) || (p == &square) || (p == &triangle);
}

unsigned
primIter::vertex(double* x, double* y)
{
    if (mData && mIndex < mData->total_vertices()) {
        return mData->vertex(mIndex++, x, y);
    } else {
        *x = *y = 0.0;
        return agg::path_cmd_stop;
    }
}

void
primIter::rewind(unsigned i)
{
    mIndex = i;
}

void
primIter::init(const primShape* shape)
{
    mData = shape;
    mIndex = 0;
}
