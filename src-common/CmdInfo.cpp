// CmdInfo.cpp
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


#include "CmdInfo.h"
#include "astreplacement.h"
#include "primShape.h"

#ifdef _MSC_VER
#include <intrin.h>
#pragma intrinsic(_InterlockedCompareExchange64)
#endif

namespace AST {

    const CommandInfo CommandInfo::Default(0, 0);
    
    CommandInfo::CommandInfo(unsigned i, ASTcompiledPath* path, double w, const ASTpathCommand* c)
    : mIndex(0), mPathUID(std::numeric_limits<UIDtype>::max())
    {
        init(i, path, w, c);
    }
    
    CommandInfo::CommandInfo(unsigned i, agg::path_storage* path)
    : mFlags(CF_MITER_JOIN + CF_BUTT_CAP + CF_FILL), mMiterLimit(4.0), 
      mStrokeWidth(0.1), mIndex(i), mPath(path), mPathUID(0)
    {
    }
    
    void
    CommandInfo::tryInit(unsigned i, ASTcompiledPath* path, double w, const ASTpathCommand* c)
    {
        // Try to change the path UID from the default value to a value that is 
        // guaranteed to not be in use. If successful then perform initialization
#ifdef _MSC_VER
        if (_InterlockedCompareExchange64((__int64*)(&mPathUID), 
                                          (__int64)(std::numeric_limits<uint64_t>::max()), 
                                          (__int64)0) == (__int64)(std::numeric_limits<uint64_t>::max()))
#else
        if (__sync_bool_compare_and_swap(&mPathUID, std::numeric_limits<UIDtype>::max(), (UIDtype)0))
#endif
            init(i, path, w, c);
    }

    void
    CommandInfo::init(unsigned i, ASTcompiledPath* path, double w, const ASTpathCommand* c)
    {
        if (mPathUID != path->mPathUID || mIndex != i) {
            if (c) {
                mFlags = c->mChildChange.flags;
                mMiterLimit = c->mMiterLimit;
            } else {
                mFlags = CF_MITER_JOIN + CF_BUTT_CAP + CF_FILL;
                mMiterLimit = 4.0;
            }

            mIndex = i;
            mPath = &(path->mPath);
            mPathUID = path->mPathUID;              // this step must be last
            mStrokeWidth = w;
        }
    }
    
}
