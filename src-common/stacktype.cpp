// stacktype.cpp
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
#include "rendererAST.h"
#include <cassert>
#include "astexpression.h"
#include <cstring>
#include <iostream>

static_assert(sizeof(StackType) == sizeof(double), "StackType must be 8 bytes");
static_assert(sizeof(StackRule) == sizeof(double), "StackRule must be 8 bytes");
static_assert(offsetof(StackType, ruleHeader) == 0, "StackRule must align with StackType");

#ifdef EXTREME_PARAM_DEBUG
std::map<const StackRule*, int> StackRule::ParamMap;
int StackRule::ParamUID = 0;
int StackRule::ParamOfInterest = 3;
#endif

StackRule*
StackRule::alloc(int name, int size, const AST::ASTparameters* ti)
{
    ++Renderer::ParamCount;
    StackType* newrule = reinterpret_cast<StackType*>(new double[size ? size + HeaderSize : 1]);
    assert((reinterpret_cast<intptr_t>(newrule) & 3) == 0);   // confirm 32-bit alignment
    newrule[0].ruleHeader.mRuleName = static_cast<int16_t>(name);
    newrule[0].ruleHeader.mRefCount = 0;
    newrule[0].ruleHeader.mParamCount = static_cast<uint16_t>(size);
    if (size)
        newrule[1].typeInfo = ti;
#ifdef EXTREME_PARAM_DEBUG
    ParamMap[&(newrule->ruleHeader)] = ++ParamUID;
    if (ParamUID == ParamOfInterest)
        ParamMap[&(newrule->ruleHeader)] = ParamOfInterest;
#endif
    return &(newrule->ruleHeader);
}

StackRule*
StackRule::alloc(const StackRule* from)
{
    if (from == nullptr)
        return nullptr;
    const StackType* src = reinterpret_cast<const StackType*>(from);
    const AST::ASTparameters* ti = from->mParamCount ? src[1].typeInfo : nullptr;
    StackRule* ret = alloc(from->mRuleName, from->mParamCount, ti);
#ifdef EXTREME_PARAM_DEBUG
    ParamMap[ret] = ++ParamUID;
    if (ParamUID == ParamOfInterest)
        ParamMap[ret] = ParamOfInterest;
#endif
    if (ret->mParamCount) {
        StackType* data = reinterpret_cast<StackType*>(ret);
        data[1].typeInfo = ti;
        from->copyParams(data + HeaderSize);
    }
    return ret;
}

void
StackRule::copyParams(StackType* dest) const
{
    int current = 0;
    // Copy the POD and param_ptrs over
    for (const_iterator it = begin(), e = end(); it != e; ++it) {
        switch (it.type().mType) {
            case AST::NumericType:
            case AST::FlagType:
            case AST::ModType:
                // Copy over POD types
                memcpy(static_cast<void*>(dest + current),
                       static_cast<const void*>(&*it),
                       it.type().mTuplesize * sizeof(StackType));
                break;
            case AST::RuleType:
                // Placement copy ctor param_ptr
                new (&(dest[current].rule)) param_ptr(it->rule);
                break;
            default:
                break;
        }
        current += it.type().mTuplesize;
    }
}

// Release arguments on the heap
void
StackRule::release() const
{
#ifdef EXTREME_PARAM_DEBUG
    auto f = ParamMap.find(this);
    assert(f != ParamMap.end());
    int n = (*f).second;
    assert(n > 0);
    if (n == ParamOfInterest)
        (*f).second = ParamOfInterest;
#endif
    if (mRefCount == 0) {
        if (mParamCount) {
            const StackType* data = reinterpret_cast<const StackType*>(this);
            data[HeaderSize].release(data[1].typeInfo);
        }
#ifdef EXTREME_PARAM_DEBUG
        (*f).second = -n;
#endif
        --Renderer::ParamCount;
        delete[] this;
        return;
    }
    
    if (mRefCount < MaxRefCount)
        --mRefCount;
}

// Release arguments on the stack
void
StackType::release(const AST::ASTparameters* p) const
{
    for (const_iterator it = begin(p), e = end(); it != e; ++it)
        if (it.type().mType == AST::RuleType)
            it->rule.~param_ptr();
}

void
StackRule::retain() const
{
#ifdef EXTREME_PARAM_DEBUG
    auto f = ParamMap.find(this);
    assert(f != ParamMap.end());
    int n = (*f).second;
    assert(n > 0);
    if (n == ParamOfInterest)
        (*f).second = ParamOfInterest;
#endif
    if (mRefCount != MaxRefCount)
        ++mRefCount;                // After 4+ billion refs this causes a leak
}

bool
StackRule::operator==(const StackRule& o) const
{
    if (this == &o) return true;
    if (mParamCount != o.mParamCount) return false;
    return std::memcmp(reinterpret_cast<const void*>(this + HeaderSize),
                       reinterpret_cast<const void*>(&o + HeaderSize),
                       sizeof(StackType)*(mParamCount)) == 0;
}

bool
StackRule::Equal(const StackRule* a, const StackRule* b)
{
    if (a == nullptr && b == nullptr) return true;
    if (a == nullptr || b == nullptr) return false;
    return (*a) == (*b);
}

void
StackRule::read(std::istream& is)
{
    if (mParamCount == 0)
        return;
    StackType* st = reinterpret_cast<StackType*>(this);
    is.read(reinterpret_cast<char*>(&(st[1].typeInfo)), sizeof(AST::ASTparameters*));
    for (iterator it = begin(), e = end(); it != e; ++it) {
        switch (it.type().mType) {
        case AST::NumericType:
        case AST::ModType:
            is.read(reinterpret_cast<char*>(&*it), it.type().mTuplesize * sizeof(StackType));
            break;
        case AST::RuleType:
            new (&(it->rule)) param_ptr(Read(is));
            break;
        default:
            assert(false);
            break;
        }
    }
}

void
StackRule::write(std::ostream& os) const
{
    uint64_t head = static_cast<uint64_t>(mRuleName) << 24 |
                    static_cast<uint64_t>(mParamCount) << 8 |
                    0xff;
    os.write(reinterpret_cast<char*>(&head), sizeof(uint64_t));
    if (mParamCount == 0)
        return;
    const StackType* st = reinterpret_cast<const StackType*>(this);
    os.write(reinterpret_cast<const char*>(&(st[1].typeInfo)), sizeof(AST::ASTparameters*));
    for (const_iterator it = begin(), e = end(); it != e; ++it) {
        switch (it.type().mType) {
        case AST::NumericType:
        case AST::ModType:
            os.write(reinterpret_cast<const char*>(&*it), it.type().mTuplesize * sizeof(StackType));
            break;
        case AST::RuleType:
            Write(os, it->rule.get());
            break;
        default:
            assert(false);
            break;
        }
    }
}

param_ptr
StackRule::Read(std::istream& is)
{
    uint64_t size = 0;
    is.read(reinterpret_cast<char*>(&size), sizeof(uint64_t));
    if (size & 3) {
        // Don't know the typeInfo yet, get it during read
        StackRule* s = StackRule::alloc((size >> 24) & 0xffff, (size >> 8) & 0xffff, nullptr);
        s->read(is);
        return param_ptr(s);
    } else {
        return param_ptr(reinterpret_cast<StackRule*>(static_cast<intptr_t>(size)));
    }
}

void
StackRule::Write(std::ostream& os, const StackRule* s)
{
    if (s == nullptr || s->mRefCount == MaxRefCount) {
        uint64_t p = static_cast<uint64_t>(reinterpret_cast<intptr_t>(s));
        os.write(reinterpret_cast<const char*>(&p), sizeof(uint64_t));
    } else {
        s->write(os);
    }
}

static void
EvalArgs(RendererAST* rti, const StackRule* parent, StackType::iterator& dest,
         StackType::iterator& end, const AST::ASTexpression* arguments,
         bool onStack)
{
    for (size_t i = 0; i < arguments->size(); ++i, ++dest) {
        assert(dest != end);
        if (onStack)
            rti->mLogicalStackTop = &(*dest);
        const AST::ASTexpression* arg = arguments->getChild(i);
        switch (arg->mType) {
            case AST::NumericType: {
                int num = arg->evaluate(&(dest->number), dest.type().mTuplesize, rti);
                if (!AST::ASTparameter::Impure && dest.type().isNatural && !RendererAST::isNatural(rti, dest->number))
                    CfdgError::Error(arg->where, "Expression does not evaluate to a legal natural number");
                if (num != dest.type().mTuplesize)
                    CfdgError::Error(arg->where, "Expression does not evaluate to the correct size");
                break;
            }
            case AST::ModType: {
                static const Modification zeroMod;
                Modification& m = reinterpret_cast<Modification&> (dest->number);
                m = zeroMod;
                arg->evaluate(m, false, rti);
                break;
            }
            case AST::RuleType: {
                new (&(dest->rule)) param_ptr(arg->evalArgs(rti, parent));
                break;
            }
            default:
                break;
        }
    }
    assert(dest == end);
}

// Evaluate arguments on the heap
void
StackRule::evalArgs(RendererAST* rti, const AST::ASTexpression* arguments, 
                    const StackRule* parent)
{
    iterator dest = begin();
    iterator end_it = end();
    EvalArgs(rti, parent, dest, end_it, arguments, false);
}

// Evaluate arguments on the stack
void
StackType::evalArgs(RendererAST* rti, const AST::ASTexpression* arguments,
                    const AST::ASTparameters* p, bool sequential)
{
    iterator dest = begin(p);
    iterator end_it = end();
    EvalArgs(rti, nullptr, dest, end_it, arguments, sequential);
}


