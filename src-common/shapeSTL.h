// shapeSTL.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006-2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2012 John Horigan - john@glyphic.com
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

#include "cfdg.h"
#include "shape.h"
#include "tempfile.h"

class ShapeOp
{
public:
    ShapeOp() { };
    virtual ~ShapeOp();
    
    virtual void apply(const FinishedShape&) = 0;


    class iterator
    {
    public:
        iterator(const iterator& i) : mOp(i.mOp) { }
        
        iterator& operator++()      { return *this; }
        iterator& operator++(int)   { return *this; }
        iterator& operator*()       { return *this; }
        
        iterator& operator=(const FinishedShape& s)
            { mOp.apply(s); return *this; }
    
    private:
        friend class ShapeOp;
        
        iterator(ShapeOp& op) : mOp(op) { }
        
        void operator=(const iterator&);        // not defined: can't be assigned
        
        ShapeOp& mOp;
    };
    
    iterator outputIterator() { return iterator(*this); }


    class function : public std::unary_function<const FinishedShape&, void>
    {
    public:
        function(const function& f) : mOp(f.mOp) { }

        void operator()(const FinishedShape& s) const
            { mOp.apply(s); }

    private:
        friend class ShapeOp;
        
        function(ShapeOp& op) : mOp(op) { }
        
        void operator=(const function&);        // not defined: can't be assigned
        
        ShapeOp& mOp;
    };

    function outputFunction() { return function(*this); }


private:
    ShapeOp(const ShapeOp&);
    ShapeOp& operator=(const ShapeOp&);
        // not implemented, not copyable
};


class OutputMerge
{
public:
    OutputMerge() { }
    ~OutputMerge();
    
    typedef std::multiset<FinishedShape> ShapeSource;
    typedef ShapeSource::iterator        ShapeIter;
    
    void addShapes(ShapeIter begin, ShapeIter end);

    
    typedef std::unary_function<TempFile&, void > TempFileAdderBase;
    class TempFileAdder: public TempFileAdderBase
    {
    public:
        void operator()(TempFile& t) { mOM.addTempFile(t); }
    private:
        TempFileAdder(OutputMerge& om) : mOM(om) { }
        TempFileAdder& operator=(const TempFileAdder&) { return *this; }
        OutputMerge& mOM;
        friend class OutputMerge;
    };
    
    TempFileAdder tempFileAdder() { return TempFileAdder(*this); }
    
    void addTempFile(TempFile&);


    template < typename O >
    void merge(O output)
    {
        while (!mSieve.empty()) {
            Sieve::iterator nextShape = mSieve.begin();
        
            *output++ = nextShape->first;
            int i = nextShape->second;
        
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

    typedef std::map<FinishedShape, int>    Sieve;
    typedef Sieve::value_type               SievePair;
    
    Sieve       mSieve;
    
    void insertNext(int i);
    OutputMerge& operator=(const OutputMerge&) { return *this; }
};

#endif // INCLUDE_SHAPESTL_H
