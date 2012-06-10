// shape.cpp
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
            isfinite(m_transform.ty) &&
            isfinite(m_Z.sz) &&
            isfinite(m_Z.tz);
}

void
ShapeBase::write(std::ostream& os) const
{
    os.write((const char*)(this), sizeof(ShapeBase));
}

void
ShapeBase::read(std::istream& is)
{
    is.read((char *)(this), sizeof(ShapeBase));
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
    StackType::writeHeader(os, mParameters);
    releaseParams();
}

void
Shape::readParams(std::istream& is)
{
    mParameters = StackType::readHeader(is);
}

void
FinishedShape::write(std::ostream& os) const
{
    ShapeBase::write(os);
    os.write((const char*)(&mBounds), sizeof(Bounds));
    writeParams(os);
}

void
FinishedShape::read(std::istream& is)
{
    ShapeBase::read(is);
    is.read((char *)(&mBounds), sizeof(Bounds));
    readParams(is);
}

