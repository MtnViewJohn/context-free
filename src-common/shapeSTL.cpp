// shapeSTL.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006-2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2013 John Horigan - john@glyphic.com
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
// Mark Lentczner can be contacted at markl@glyphic.com or at
// Mark Lentczner, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//


#include "shapeSTL.h"
#include <limits>
using namespace std;


void
OutputMerge::addTempFile(TempFile& t)
{
    istream* f = t.forRead();
    mStreams.emplace_back(f);
    mIters.push_back(FileIter(*f));
    
    insertNext(mIters.size() - 1);
}

void
OutputMerge::addShapes(ShapeIter begin, ShapeIter end)
{
    mShapesNext = begin;
    mShapesEnd = end;
    
    insertNext(numeric_limits<size_t>::max());
}

OutputMerge::~OutputMerge()
{
}

void
OutputMerge::insertNext(size_t i)
{
    if (i == numeric_limits<size_t>::max()) {
        if (mShapesNext != mShapesEnd) {
            mSieve.insert(SievePair(*mShapesNext++, i));
        }
    }
    else {
        FileIter& input = mIters[i];
        if (input != mFileEnd) {
            mSieve.insert(SievePair(*input++, i));
        }
    }
}
