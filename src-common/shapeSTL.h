// shapeSTL.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006-2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2012-2013 John Horigan - john@glyphic.com
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


#ifndef INCLUDE_SHAPESTL_H
#define INCLUDE_SHAPESTL_H

#ifdef _WIN32
#pragma warning( disable : 4786 )
#endif

#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <set>
#include <memory>
#include "chunk_vector.h"

#include "cfdg.h"
#include "shape.h"
#include "tempfile.h"

class OutputMerge
{
public:
    OutputMerge() { }
    ~OutputMerge();
    OutputMerge& operator=(const OutputMerge&) = delete;
    
    typedef chunk_vector<FinishedShape, 10> ShapeSource;
    typedef ShapeSource::iterator           ShapeIter;
    
    void addShapes(ShapeIter begin, ShapeIter end);

    void addTempFile(TempFile&);


    void merge(ShapeFunction op)
    {
        while (!mSieve.empty()) {
            Sieve::iterator nextShape = mSieve.begin();
            
            op(nextShape->first);
            size_t i = nextShape->second;
        
            mSieve.erase(nextShape);
            insertNext(i);
        }
    }
    
    
private:
    typedef std::unique_ptr<std::istream>           file_ptr;
    typedef std::istream_iterator<FinishedShape>    FileIter;
    typedef std::vector<file_ptr>                   FileStreams;
    typedef std::vector<FileIter>                   FileIters;
    
    FileStreams mStreams;
    FileIters   mIters;
    FileIter    mFileEnd;
    
    
    ShapeIter   mShapesNext;
    ShapeIter   mShapesEnd;

    typedef std::map<FinishedShape, size_t> Sieve;
    typedef Sieve::value_type               SievePair;
    
    Sieve       mSieve;
    
    void insertNext(size_t i);
};

#endif // INCLUDE_SHAPESTL_H
