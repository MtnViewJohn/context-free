// stacktype.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2011 John Horigan - john@glyphic.com
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

// Parameter block layout in memory:
// param +   0: ruleHeader (shape name, parameter count, reference count)
// param +   8: typeinfo pointer
// param +  16: 1st parameter
// param + 8*n: 2nd parameter
// ...
// Numeric parameters use one 8-byte block
// Numeric vector parameters use n 8-bytes blocks
// Modification parameters use 22 8-byte blocks
// Rule parameters use one 8-byte block, which contains a pointer to the 
// ruleHeader of another parameter block
//
// If the rule header indicates that the parameter count is zero then there
// are no typeinfo or parameter blocks, just one block for the rule header.
// The parameter count is not the number of parameters, it is the number of
// 8-byte blocks required to contain the parameters

// Parameter block layout in files:
// The parameter block is the root of a tree of parameter blocks. This tree
// is traversed depth first. Rule parameters are encoded in the same manner as
// the root parameter token (except no zero): rule parameters that are owned by
// some other object are written out as memory pointers, otherwise the parameter
// block for the rule parameter is interpolated directly into the parent
// parameter block as a header token followed by the rest of the child parameter
// block. The remainder of the parameters continue after the child parameter block
// (which may itself have grandchild  parameter blocks).
//
// Note: only the root parameter token can be zero when there are no parameters.
// Non-root parameter token nodes will have be a header token with a parameter
// count of zero if they correspond to a rule with no parameters.


#include "stacktype.h"
#include "cfdg.h"
#include <cassert>
#include "astexpression.h"
#include <cstring>
#include <iostream>

class const_iterator {
public:
    const StackType* _Ptr;
    std::vector<AST::ASTparameter>::const_iterator _Iter;
    std::vector<AST::ASTparameter>::const_iterator _End;

    const_iterator() : _Ptr(0) {}
    const_iterator(const StackType* s)
    : _Ptr(s)
    {
        if (_Ptr && _Ptr->ruleHeader.mParamCount) {
            const AST::ASTparameters* p = (s + 1)->typeInfo;
            _Iter = p->begin();
            _End = p->end();
            _Ptr += 2;
        } else {
            _Ptr = 0;
        }
    }
    const_iterator(const StackType* s, const std::vector<AST::ASTparameter>* p)
    : _Ptr(s)
    {
        if (_Ptr) {
            _Iter = p->begin();
            _End = p->end();
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
                _Ptr = 0;
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

    static const_iterator begin(const StackType* s)
    {
        return const_iterator(s);
    }

    static const_iterator begin(const StackType* s, const std::vector<AST::ASTparameter>* p)
    {
        return const_iterator(s, p);
    }
    
    static const_iterator end()
    {
        return const_iterator();
    }
};

class iterator {
public:
    StackType* _Ptr;
    AST::ASTparameters::const_iterator _Iter;
    AST::ASTparameters::const_iterator _End;

    iterator() : _Ptr(0) {}
    iterator(StackType* s)
    : _Ptr(s)
    {
        if (_Ptr && _Ptr->ruleHeader.mParamCount) {
            const AST::ASTparameters* p = (s + 1)->typeInfo;
            _Iter = p->begin();
            _End = p->end();
            _Ptr += 2;
        } else {
            _Ptr = 0;
        }
    }
    iterator(StackType* s, const std::vector<AST::ASTparameter>* p)
    : _Ptr(s)
    {
        if (_Ptr) {
            _Iter = p->begin();
            _End = p->end();
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
                _Ptr = 0;
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

    static iterator begin(StackType* s)
    {
        return iterator(s);
    }

    static iterator begin(StackType* s, const std::vector<AST::ASTparameter>* p)
    {
        return iterator(s, p);
    }
    
    static iterator end()
    {
        return iterator();
    }
};


#define assert_static(e) \
do { \
enum { assert_static__ = 1/((int)(e)) }; \
} while (0)

StackType*
StackType::alloc(int name, int size, const std::vector<AST::ASTparameter>* ti)
{
    assert_static(sizeof(StackType) == sizeof(double));
    StackType* newrule = new StackType[size ? size + 2 : 1];
    assert((((size_t)newrule) & 3) == 0);   // confirm 32-bit alignment
    newrule[0].ruleHeader.mRuleName = name;
    newrule[0].ruleHeader.mRefCount = 0;
    newrule[0].ruleHeader.mParamCount = size;
    if (size)
        newrule[1].typeInfo = ti;
    return newrule;
}

// Release arguments on the heap
void
StackType::release() const
{
    if (ruleHeader.mRefCount == 0) {
        for (const_iterator it = const_iterator::begin(this), e = const_iterator::end(); it != e; ++it)
            if (it.type().mType == AST::ASTexpression::RuleType)
                it->rule->release();
        delete[] this;
        return;
    }
    
    if (ruleHeader.mRefCount < StackRule::MaxRefCount)
        --(ruleHeader.mRefCount);
}

// Release arguments on the stack
void
StackType::release(const std::vector<AST::ASTparameter>* p) const
{
    for (const_iterator it = const_iterator::begin(this, p), e = const_iterator::end(); it != e; ++it)
        if (it.type().mType == AST::ASTexpression::RuleType)
            it->rule->release();
}

void
StackType::retain(Renderer* r) const
{
    if (ruleHeader.mRefCount == StackRule::MaxRefCount)
        return;
    
    ++(ruleHeader.mRefCount);
    if (ruleHeader.mRefCount == StackRule::MaxRefCount) {
        r->storeParams(this);
    }
}

bool
StackRule::operator==(const StackRule& o) const
{
    if (this == &o) return true;
    if (mParamCount != o.mParamCount) return false;
    return std::memcmp((const void*)(this + 2), (const void*)(&o + 2), 
                       sizeof(StackType)*(mParamCount)) == 0;
}

bool
StackRule::Equal(const StackRule* a, const StackType* b)
{
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    return (*a) == (b->ruleHeader);
}

void
StackType::read(std::istream& is)
{
    if (ruleHeader.mParamCount == 0)
        return;
    is.read((char*)(&((this+1)->typeInfo)), sizeof(AST::ASTparameters*));
    for (iterator it = iterator::begin(this), e = iterator::end(); it != e; ++it) {
        switch (it.type().mType) {
        case AST::ASTexpression::NumericType:
        case AST::ASTexpression::ModType:
            is.read((char*)(&*it), it.type().mTuplesize * sizeof(StackType));
            break;
        case AST::ASTexpression::RuleType:
            it->rule = readHeader(is);
            break;
        default:
            assert(false);
            break;
        }
    }
}

void
StackType::write(std::ostream& os) const
{
    uint64_t head = ruleHeader.mRuleName << 24 | ruleHeader.mParamCount << 8 | 0xff;
    os.write((char*)(&head), sizeof(uint64_t));
    if (ruleHeader.mParamCount == 0)
        return;
    os.write((char*)(&((this+1)->typeInfo)), sizeof(AST::ASTparameters*));
    for (const_iterator it = const_iterator::begin(this), e = const_iterator::end(); 
        it != e; ++it)
    {
        switch (it.type().mType) {
        case AST::ASTexpression::NumericType:
        case AST::ASTexpression::ModType:
            os.write((char*)(&*it), it.type().mTuplesize * sizeof(StackType));
            break;
        case AST::ASTexpression::RuleType:
            writeHeader(os, it->rule);
            break;
        default:
            assert(false);
            break;
        }
    }
}

StackType*
StackType::readHeader(std::istream& is)
{
    uint64_t size = 0;
    is.read((char*)(&size), sizeof(uint64_t));
    if (size & 3) {
        // Don't know the typeInfo yet, get it during read
        StackType* s = StackType::alloc((size >> 24) & 0xffff, (size >> 8) & 0xffff, NULL);
        s->read(is);
        return s;
    } else {
        return (StackType*)size;
    }
}

void
StackType::writeHeader(std::ostream& os, const StackType* s)
{
    if (s == NULL || s->ruleHeader.mRefCount == StackRule::MaxRefCount) {
        uint64_t p = (uint64_t)(s);
        os.write((char*)(&p), sizeof(uint64_t));
    } else {
        s->write(os);
    }
}

static void
EvalArgs(Renderer* rti, const StackType* parent, 
         iterator& dest, const AST::ASTexpression* arguments)
{
    for (int i = 0; i < arguments->size(); ++i, ++dest) {
        const AST::ASTexpression* arg = (*arguments)[i];
        switch (arg->mType) {
            case AST::ASTexpression::NumericType: {
                arg->evaluate(&(dest->number), dest.type().mTuplesize, rti);
                break;
            }
            case AST::ASTexpression::ModType: {
                int dummy;
                static const Modification zeroMod;
                Modification& m = reinterpret_cast<Modification&> (dest->number);
                m = zeroMod;
                arg->evaluate(m, 0, 0, false, dummy, rti);
                break;
            }
            case AST::ASTexpression::RuleType: {
                dest->rule = arg->evalArgs(rti, parent);
                break;
            }
            default:
                break;
        }
    }
}

// Evaluate arguments on the heap
void
StackType::evalArgs(Renderer* rti, const AST::ASTexpression* arguments, 
                    const StackType* parent)
{
    iterator dest = iterator::begin(this);
    EvalArgs(rti, parent, dest, arguments);
}

// Evaluate arguments on the stack
void
StackType::evalArgs(Renderer* rti, const AST::ASTexpression* arguments,
                    const std::vector<AST::ASTparameter>* p)
{
    iterator dest = iterator::begin(this, p);
    EvalArgs(rti, NULL, dest, arguments);
}

