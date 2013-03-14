// rendererAST.cpp
// this file is part of Context Free
// ---------------------
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
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//

#include "rendererAST.h"
#include "builder.h"

RendererAST::~RendererAST() { delete mCurrentPath; }

void
RendererAST::ColorConflict(RendererAST* r, const yy::location& w)
{
    if (r)
        r->colorConflict(w);
    else
        CfdgError::Warning(w, "Conflicting color change");
}


void
RendererAST::init()
{
    mLastPoint.x = mLastPoint.y = 0.0;
    mStop = false;
    mClosed = false;
    mWantMoveTo = true;
    mWantCommand = true;
    mIndex = mNextIndex = 0;
}

bool
RendererAST::isNatural(RendererAST* r, double n)
{
    return n >= 0 && n <= (r ? r->mMaxNatural : Builder::MaxNatural) && n == floor(n);
}

void
RendererAST::initStack(const StackRule* p)
{
    if (p && p->mParamCount) {
        for (StackRule::const_iterator  it = p->begin(), eit = p->end();
             it != eit; ++it)
        {
            for (int i = 0; i < it.type().mTuplesize; ++i)
                mCFstack.push_back(*(&*it + i));
            // Retain any shape params to balance the releases in unwindStack()
            if (it.type().mType == AST::RuleType)
                it->rule->retain(this);
        }
    }
    if (!mCFstack.empty()) {
        mLogicalStackTop = &(mCFstack.back()) + 1;
    } else {
        mLogicalStackTop = nullptr;
    }
}

void
RendererAST::unwindStack(size_t oldsize, const std::vector<AST::ASTparameter>& params)
{
    if (oldsize == mCFstack.size())
        return;

    StackType* pos = &(mCFstack[oldsize]);
    for (const AST::ASTparameter& param: params) {
        if (param.isLoopIndex) continue;  // loop indices are unwound in ASTloop::traverse()
        if (param.mType == AST::RuleType)
            pos->rule->release();
        pos += param.mTuplesize;
        if (pos > &(mCFstack.back()))
            break;                      // no guarantee entire frame was computed
    }
    mCFstack.resize(oldsize);
    if (oldsize)
        mLogicalStackTop = &(mCFstack[0]) + oldsize;
    else
        mLogicalStackTop = nullptr;
}
