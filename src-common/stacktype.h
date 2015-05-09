// stacktype.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2011-2015 John Horigan - john@glyphic.com
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

#ifndef INCLUDE_STACKTYPE_H
#define INCLUDE_STACKTYPE_H

#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif
#include <stdint.h>               // Use the C99 official header
#include <vector>
#include <iosfwd>
#include "ast.h"
#include "mynoexcept.h"

//#define EXTREME_PARAM_DEBUG

#ifdef EXTREME_PARAM_DEBUG
#include <map>
#endif

namespace AST { class ASTparameter; class ASTexpression; }

union StackType;
struct StackRule;
class RendererAST;

template <class _stack>
class StackTypeIterator {
public:
    _stack* _Ptr;
    AST::ASTparameters::const_iterator _Iter;
    AST::ASTparameters::const_iterator _End;
    
    StackTypeIterator() : _Ptr(nullptr) {}
    StackTypeIterator(const StackTypeIterator& o)
    : _Ptr(o._Ptr), _Iter(o._Iter), _End(o._End) {}
    StackTypeIterator(_stack* s, const AST::ASTparameters* p)
    : _Ptr(s)
    {
        if (_Ptr && p) {
            _Iter = p->begin();
            _End = p->end();
            if (_Iter == _End)
                _Ptr = nullptr;           // Should never happen
        }
    }
    
    _stack& operator*() { return *_Ptr; }
    _stack* operator->() { return _Ptr; }
    
    StackTypeIterator& operator++()
    {
        if (_Ptr) {
            _Ptr += _Iter->mTuplesize;
            ++_Iter;
            if (_Iter == _End)
                _Ptr = nullptr;
        }
        return *this;
    }
    
    StackTypeIterator& operator++(int)
    {
        StackTypeIterator tmp = *this;
        ++(*this);
        return tmp;
    }
    
    bool operator==(const StackTypeIterator& o) const NOEXCEPT { return _Ptr == o._Ptr; }
    bool operator!=(const StackTypeIterator& o) const NOEXCEPT { return _Ptr != o._Ptr; }
    
    StackTypeIterator& operator=(const StackTypeIterator& o)
    {
        if (this == &o) return *this;
        _Ptr = o._Ptr;
        _Iter = o._Iter;
        _End = o._End;
        return *this;
    }
    
    const AST::ASTparameter& type() const { return *_Iter; }
};


class param_ptr {
    const StackRule*  mPtr = nullptr;
public:
    param_ptr() = default;
    param_ptr(std::nullptr_t) { }
    param_ptr(const StackRule* r) : mPtr(r) { }
    param_ptr(const param_ptr& o);
    param_ptr(param_ptr&& o) : mPtr(o.mPtr)
    { o.mPtr = nullptr; }
    ~param_ptr();
    
    param_ptr& operator=(const param_ptr& o);
    param_ptr& operator=(param_ptr&& o);
    param_ptr& operator=(std::nullptr_t);
    
    explicit operator bool() const
    { return mPtr != nullptr; }
    
    void reset(StackRule* r = nullptr);
    const StackRule* release()
    {
        const StackRule* ret = mPtr;
        mPtr = nullptr;
        return ret;
    }
    void swap(param_ptr& o)
    {
        auto temp = mPtr;
        mPtr = o.mPtr;
        o.mPtr = temp;
    }
    
    const StackRule* get() const
    { return mPtr; }
    
    const StackRule& operator*() const
    { return *mPtr; }
    
    const StackRule* operator->() const
    { return mPtr; }
};


struct StackRule {
    enum const_t : uint32_t { MaxRefCount = UINT32_MAX, HeaderSize = 2 };

    typedef StackTypeIterator<StackType> iterator;
    typedef StackTypeIterator<const StackType> const_iterator;
    
    int16_t     mRuleName;
    uint16_t    mParamCount;
    mutable uint32_t    mRefCount;
    
    bool operator==(const StackRule& o) const;
    static bool Equal(const StackRule* a, const StackRule* b);
    
    static StackRule*  alloc(int name, int size, const AST::ASTparameters* ti);
    static StackRule*  alloc(const StackRule* from);
    void        release() const;
    void        retain() const;
    void        copyParams(StackType* dest) const;
    
    
    static param_ptr   Read(std::istream& is);
    static void        Write(std::ostream& os, const StackRule* s);
    
    void        evalArgs(RendererAST* rti, const AST::ASTexpression* arguments,
                         const StackRule* parent);
    
#ifdef EXTREME_PARAM_DEBUG
    static std::map<const StackRule*, int> ParamMap;
    static int ParamUID;
    static int ParamOfInterest;
#endif

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin();
    iterator end()
    { return iterator(); }
    const_iterator cend()
    { return const_iterator(); }
    const_iterator end() const
    { return const_iterator(); }

private:
    void        read(std::istream& is);
    void        write(std::ostream& os) const;
};

#ifdef _MSC_VER
#pragma warning(disable:4582 4583)
#endif

union StackType {
    typedef StackTypeIterator<StackType> iterator;
    typedef StackTypeIterator<const StackType> const_iterator;
    
    StackType() { }
    ~StackType() { }
    
    double      number;
    param_ptr   rule;
    StackRule   ruleHeader;
    const AST::ASTparameters* typeInfo;

    void        release(const AST::ASTparameters* p) const;

    void        evalArgs(RendererAST* rti, const AST::ASTexpression* arguments,
                         const AST::ASTparameters* p, bool sequential);
    
    iterator begin(const AST::ASTparameters* p)
    { return iterator(this, p); }
    const_iterator cbegin(const AST::ASTparameters* p)
    { return const_iterator(this, p); }
    const_iterator begin(const AST::ASTparameters* p) const
    { return const_iterator(this, p); }
    iterator end()
    { return iterator(); }
    const_iterator cend()
    { return const_iterator(); }
    const_iterator end() const
    { return const_iterator(); }
};

inline StackRule::iterator
StackRule::begin()
{
    if (mParamCount) {
        StackType* st = reinterpret_cast<StackType*>(this);
        return iterator(st + HeaderSize, st[1].typeInfo);
    }
    return iterator();
}

inline StackRule::const_iterator
StackRule::begin() const
{
    if (mParamCount) {
        const StackType* st = reinterpret_cast<const StackType*>(this);
        return const_iterator(st + HeaderSize, st[1].typeInfo);
    }
    return const_iterator();
}

inline StackRule::const_iterator
StackRule::cbegin()
{
    if (mParamCount) {
        const StackType* st = reinterpret_cast<const StackType*>(this);
        return const_iterator(st + HeaderSize, st[1].typeInfo);
    }
    return const_iterator();
}

inline param_ptr::param_ptr(const param_ptr& o) : mPtr(o.mPtr)
{
    if (mPtr)
        mPtr->retain();
}

inline param_ptr::~param_ptr()
{
    if (mPtr)
        mPtr->release();
}

inline param_ptr& param_ptr::operator=(const param_ptr& o)
{
    if (this == &o || mPtr == o.mPtr)
        return *this;
    if (mPtr)
        mPtr->release();
    mPtr = o.mPtr;
    if (mPtr)
        mPtr->retain();
    return *this;
}

inline param_ptr& param_ptr::operator=(param_ptr&& o)
{
    if (this == &o || mPtr == o.mPtr)
        return *this;
    if (mPtr)
        mPtr->release();
    mPtr = o.mPtr;
    o.mPtr = nullptr;
    return *this;
}

inline param_ptr& param_ptr::operator=(std::nullptr_t)
{
    if (mPtr)
        mPtr->release();
    mPtr = nullptr;
    return *this;
}

inline void param_ptr::reset(StackRule* r)
{
    if (mPtr)
        mPtr->release();
    mPtr = r;
    if (mPtr)
        mPtr->retain();
}

#endif // INCLUDE_STACKTYPE_H
