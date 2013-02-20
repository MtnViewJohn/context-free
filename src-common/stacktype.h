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

namespace AST { class ASTparameter; class ASTexpression; }

union StackType;
class RendererAST;

struct StackRule {
    int16_t     mRuleName;
    uint16_t    mParamCount;
    mutable uint32_t    mRefCount;
    
    bool operator==(const StackRule& o) const;
    static bool Equal(const StackRule* a, const StackType* b);
};

union StackType {
    class const_iterator {
    public:
        const StackType* _Ptr;
        AST::ASTparameters::const_iterator _Iter;
        AST::ASTparameters::const_iterator _End;
        
        const_iterator() : _Ptr(nullptr) {}
        const_iterator(const StackType* s)
        : _Ptr(s)
        {
            if (_Ptr && _Ptr->ruleHeader.mParamCount) {
                const AST::ASTparameters* p = (s + 1)->typeInfo;
                _Iter = p->begin();
                _End = p->end();
                _Ptr += 2;
            } else {
                _Ptr = nullptr;
            }
        }
        const_iterator(const StackType* s, const AST::ASTparameters* p)
        : _Ptr(s)
        {
            if (_Ptr) {
                _Iter = p->begin();
                _End = p->end();
                if (_Iter == _End)
                    _Ptr = nullptr;           // Should never happen
            }
        }
        
        const StackType& operator*() const { return *_Ptr; }
        const StackType* operator->() const { return _Ptr; }
        const StackType& operator++()
        {
            if (_Ptr) {
                _Ptr += _Iter->mTuplesize;
                ++_Iter;
                if (_Iter == _End)
                    _Ptr = nullptr;
            }
            return *_Ptr;
        }
        const StackType& operator++(int)
        {
            const StackType* tmp = _Ptr;
            ++(*this);
            return *tmp;
        }
        bool operator==(const const_iterator& o) const { return _Ptr == o._Ptr; }
        bool operator!=(const const_iterator& o) const { return _Ptr != o._Ptr; }
        const AST::ASTparameter& type() const { return *_Iter; }
    };
    
    class iterator {
    public:
        StackType* _Ptr;
        AST::ASTparameters::const_iterator _Iter;
        AST::ASTparameters::const_iterator _End;
        
        iterator() : _Ptr(nullptr) {}
        iterator(StackType* s)
        : _Ptr(s)
        {
            if (_Ptr && _Ptr->ruleHeader.mParamCount) {
                const AST::ASTparameters* p = (s + 1)->typeInfo;
                _Iter = p->begin();
                _End = p->end();
                _Ptr += 2;
            } else {
                _Ptr = nullptr;
            }
        }
        iterator(StackType* s, const AST::ASTparameters* p)
        : _Ptr(s)
        {
            if (_Ptr) {
                _Iter = p->begin();
                _End = p->end();
                if (_Iter == _End)
                    _Ptr = nullptr;           // Should never happen
            }
        }
        
        StackType& operator*() { return *_Ptr; }
        StackType* operator->() { return _Ptr; }
        StackType& operator++()
        {
            if (_Ptr) {
                _Ptr += _Iter->mTuplesize;
                ++_Iter;
                if (_Iter == _End)
                    _Ptr = nullptr;
            }
            return *_Ptr;
        }
        
        StackType& operator++(int)
        {
            StackType* tmp = _Ptr;
            ++(*this);
            return *tmp;
        }
        bool operator==(const iterator& o) const { return _Ptr == o._Ptr; }
        bool operator!=(const iterator& o) const { return _Ptr != o._Ptr; }
        const AST::ASTparameter& type() const { return *_Iter; }
    };
    
    double      number;
    const StackType*  rule;
    StackRule   ruleHeader;
    const AST::ASTparameters* typeInfo;

    static StackType*  alloc(int name, int size, const AST::ASTparameters* ti);
    void        release() const;
    void        release(const AST::ASTparameters* p) const;
    void        retain(RendererAST* r) const;

    void        read(std::istream& is);
    void        write(std::ostream& os) const;
    static StackType*  readHeader(std::istream& is);
    static void        writeHeader(std::ostream& os, const StackType* s);
    
    void        evalArgs(RendererAST* rti, const AST::ASTexpression* arguments, 
                         const StackType* parent);
    void        evalArgs(RendererAST* rti, const AST::ASTexpression* arguments,
                         const AST::ASTparameters* p, bool sequential);
    
    iterator begin()
    {
        return iterator(this);
    }
    iterator begin(const AST::ASTparameters* p)
    {
        return iterator(this, p);
    }
    iterator end()
    {
        return iterator();
    }
    const_iterator cbegin()
    {
        return const_iterator(this);
    }
    const_iterator cbegin(const AST::ASTparameters* p)
    {
        return const_iterator(this, p);
    }
    const_iterator cend()
    {
        return const_iterator();
    }
    const_iterator begin() const
    {
        return const_iterator(this);
    }
    const_iterator begin(const AST::ASTparameters* p) const
    {
        return const_iterator(this, p);
    }
    const_iterator end() const
    {
        return const_iterator();
    }
};

#endif // INCLUDE_STACKTYPE_H
