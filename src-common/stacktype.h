// stacktype.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2011-2013 John Horigan - john@glyphic.com
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

//#define EXTREME_PARAM_DEBUG

#ifdef EXTREME_PARAM_DEBUG
#include <map>
#endif

#if defined(_MSC_VER) && !defined(noexcept)
#define noexcept throw()
#endif

namespace AST { class ASTparameter; class ASTexpression; }

union StackType;
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
    
    bool operator==(const StackTypeIterator& o) const noexcept { return _Ptr == o._Ptr; }
    bool operator!=(const StackTypeIterator& o) const noexcept { return _Ptr != o._Ptr; }
    
    StackTypeIterator& operator=(const StackTypeIterator& o)
    {
        _Ptr = o._Ptr;
        _Iter = o._Iter;
        _End = o._End;
        return *this;
    }
    
    const AST::ASTparameter& type() const { return *_Iter; }
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
    void        retain(RendererAST* r) const;
    
    static StackRule*  Read(std::istream& is);
    static void        Write(std::ostream& os, const StackRule* s);
    
    void        evalArgs(RendererAST* rti, const AST::ASTexpression* arguments,
                         const StackRule* parent);
    
#ifdef EXTREME_PARAM_DEBUG
    static std::map<const StackRule*, int> ParamMap;
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

union StackType {
    typedef StackTypeIterator<StackType> iterator;
    typedef StackTypeIterator<const StackType> const_iterator;
    
    double      number;
    const StackRule*  rule;
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
        return iterator(st + 2, st[1].typeInfo);
    }
    return iterator();
}

inline StackRule::const_iterator
StackRule::begin() const
{
    if (mParamCount) {
        const StackType* st = reinterpret_cast<const StackType*>(this);
        return const_iterator(st + 2, st[1].typeInfo);
    }
    return const_iterator();
}

inline StackRule::const_iterator
StackRule::cbegin()
{
    if (mParamCount) {
        const StackType* st = reinterpret_cast<const StackType*>(this);
        return const_iterator(st + 2, st[1].typeInfo);
    }
    return const_iterator();
}

#endif // INCLUDE_STACKTYPE_H
