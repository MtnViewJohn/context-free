// CmdInfo.cpp
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


#include "CmdInfo.h"
#include "astreplacement.h"
#include "primShape.h"
#include <atomic>

namespace AST {

    const CommandInfo CommandInfo::Default(0, nullptr);
    UIDdatatype CommandInfo::PathUIDDefault = std::numeric_limits<UIDdatatype>::max();

    CommandInfo::CommandInfo(unsigned i, ASTcompiledPath* path, double w, const ASTpathCommand* c)
    : mIndex(0), mPathUID(PathUIDDefault)
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
        if (mPathUID.compare_exchange_strong(PathUIDDefault, 0ULL))
            init(i, path, w, c);
    }

    void
    CommandInfo::init(unsigned i, ASTcompiledPath* path, double w, const ASTpathCommand* c)
    {
        if (mPathUID != path->mPathUID || mIndex != i) {
            if (c) {
                mFlags = c->mFlags;
                mMiterLimit = c->mMiterLimit;
            } else {
                mFlags = CF_MITER_JOIN + CF_BUTT_CAP + CF_FILL;
                mMiterLimit = 4.0;
            }

            mIndex = i;
            mPath = &(path->mPath);
            mPathUID = path->mPathUID.load();              // this step must be last
            mStrokeWidth = w;
        }
    }
    
    CommandInfo::CommandInfo(CommandInfo&& from) NOEXCEPT
    : mFlags(from.mFlags), mMiterLimit(from.mMiterLimit),
      mStrokeWidth(from.mStrokeWidth), mIndex(from.mIndex), mPath(from.mPath),
      mPathUID(from.mPathUID.load())
    { }

    CommandInfo::CommandInfo(const CommandInfo& from)
    : mFlags(from.mFlags), mMiterLimit(from.mMiterLimit),
      mStrokeWidth(from.mStrokeWidth), mIndex(from.mIndex), mPath(from.mPath),
      mPathUID(from.mPathUID.load())
    { }
    
    CommandInfo&
    CommandInfo::operator=(CommandInfo&& from) NOEXCEPT
    {
        if (this == &from) return *this;
        mFlags = from.mFlags;
        mMiterLimit = from.mMiterLimit;
        mStrokeWidth = from.mStrokeWidth;
        mIndex = from.mIndex;
        mPath = from.mPath;
        mPathUID = from.mPathUID.load();
        return *this;
    }
    
    CommandInfo&
    CommandInfo::operator=(const CommandInfo& from)
    {
        if (this == &from) return *this;
        mFlags = from.mFlags;
        mMiterLimit = from.mMiterLimit;
        mStrokeWidth = from.mStrokeWidth;
        mIndex = from.mIndex;
        mPath = from.mPath;
        mPathUID = from.mPathUID.load();
        return *this;
    }
    
}
