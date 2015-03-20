// shape.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2005-2013 John Horigan - john@glyphic.com
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

// Shape layout in files:
// Shapebase (shape type and world state)
// Shape bounds if this is a finished shape
// Parameter token (8 bytes):
//   zero if there are no parameters
//   a memory pointer if the parameters are owned by some other object
//   a header token if the parameters are owned by the shape
//   (this is shapeName << 24 | paramCount << 8 | 0xff)
// The parameter block starting with the typeInfo block (2nd block)
// A header token can be distinguished from a pointer by the lower two bits:
// 00b for a pointer and 11b for a header token. See shapetype.cpp for
// information on parameter block file layout.
//

#include "shape.h"
#include <cassert>
#include <stdint.h>
#include "stacktype.h"
#include <iostream>

#ifdef _WIN32
#include <float.h>
#define isfinite _finite
#else
#include <cmath>
using std::isfinite;
#endif

bool
Modification::isFinite() const
{
    return  isfinite(m_transform.sx) &&
            isfinite(m_transform.shy) &&
            isfinite(m_transform.shx) &&
            isfinite(m_transform.sy) &&
            isfinite(m_transform.tx) &&
            isfinite(m_transform.ty);
}

bool
Modification::merge(const Modification& m)
{
    m_transform.premultiply(m.m_transform);
    m_Z.premultiply(m.m_Z);
    m_time.premultiply(m.m_time);
    mRand64Seed ^= m.mRand64Seed;
    
    bool conflict = (m_ColorAssignment & m.m_ColorAssignment) ||
                    ((m.m_ColorAssignment & HSBColor::HueMask) &&   m_Color.h != 0.0) ||
                    ((  m_ColorAssignment & HSBColor::HueMask) && m.m_Color.h != 0.0) ||
                    (m_Color.b != 0.0 && m.m_Color.b != 0.0) ||
                    (m_Color.s != 0.0 && m.m_Color.s != 0.0) ||
                    (m_Color.a != 0.0 && m.m_Color.a != 0.0);

    m_ColorTarget.h += m.m_ColorTarget.h;
    m_ColorTarget.b += m.m_ColorTarget.b;
    m_ColorTarget.s += m.m_ColorTarget.s;
    m_ColorTarget.a += m.m_ColorTarget.a;
    m_Color.h += m.m_Color.h;
    m_Color.b += m.m_Color.b;
    m_Color.s += m.m_Color.s;
    m_Color.a += m.m_Color.a;
    m_ColorAssignment |= m.m_ColorAssignment;
    
    return conflict;
}

void
ShapeBase::write(std::ostream& os) const
{
    os.write(reinterpret_cast<const char*>(this), offsetof(ShapeBase, mAreaCache));
}

void
ShapeBase::read(std::istream& is)
{
    is.read(reinterpret_cast<char *>(this), offsetof(ShapeBase, mAreaCache));
    mAreaCache = mWorldState.area();
}

void
Shape::write(std::ostream& os) const
{
    ShapeBase::write(os);
    writeParams(os);
}

void
Shape::read(std::istream& is)
{
    ShapeBase::read(is);
    readParams(is);
}

void
Shape::writeParams(std::ostream& os) const
{
    StackRule::Write(os, mParameters.get());
}

void
Shape::readParams(std::istream& is)
{
    mParameters = StackRule::Read(is);
}

void
FinishedShape::write(std::ostream& os) const
{
    ShapeBase::write(os);
    os.write(reinterpret_cast<const char*>(&mBounds), sizeof(Bounds));
    writeParams(os);
}

void
FinishedShape::read(std::istream& is)
{
    ShapeBase::read(is);
    is.read(reinterpret_cast<char *>(&mBounds), sizeof(Bounds));
    readParams(is);
}

