// tempfile.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006-2008 Mark Lentczner - markl@glyphic.com
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
// Mark Lentczner can be contacted at markl@glyphic.com or at
// Mark Lentczner, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//


#include "tempfile.h"

#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <cstdio>

#include <iostream>
#include <cassert>

using namespace std;


std::ostream*
TempFile::forWrite()
{
    if (mWritten) {
        cerr << "TempFile::forWrite already wrote to " << mPath << endl;
    }
    mWritten = true;
    if (mNum > 0)
        mSystem->message("Writing %s temp file %d", type().c_str(), mNum);
    else
        mSystem->message("Writing %s temp file", type().c_str());
    return mSystem->tempFileForWrite(mType, mPath);
}

std::istream*
TempFile::forRead()
{
    if (!mWritten) {
        cerr << "TempFile::forRead temp file never written, " << mPath << endl;
    }
    mSystem->message("Reading %s temp file %d", type().c_str(), mNum);
    return mSystem->tempFileForRead(mPath);
}

const std::string&
TempFile::type() const
{
    static const std::string typeStrings[AbstractSystem::NumberofTempTypes] = {
        "shapes", "expansion", "merge", "movie"
    };
    
    assert(mType >= 0 && mType < AbstractSystem::NumberofTempTypes);
    return typeStrings[mType];
}

TempFile::TempFile(AbstractSystem* system, AbstractSystem::TempType type, int num)
    : mSystem(system), mType(type), mNum(num), mWritten(false)
    { }

TempFile::TempFile(TempFile&& from) noexcept
: mSystem(from.mSystem), mPath(std::move(from.mPath)), mType(std::move(from.mType)),
  mNum(from.mNum), mWritten(from.mWritten)
{
    // Prevent old TempFile from triggering an unlink
    from.mWritten = false;
    from.mPath.clear();
}

TempFile&
TempFile::operator=(TempFile&& from) noexcept
{
    if (this == &from) return *this;
    if (mWritten && mPath.length())
        erase();
    mSystem = from.mSystem;
    mPath = std::move(from.mPath);
    mType = from.mType;
    mNum = from.mNum;
    mWritten = from.mWritten;
    // Prevent old TempFile from triggering an unlink
    from.mWritten = false;
    from.mPath.clear();
    return *this;
}

TempFile::~TempFile()
{
    if (mWritten && mPath.length())
        erase();
}
        
void
TempFile::erase()
{
    if (mNum > 0)
        mSystem->message("Deleting %s temp file %d", type().c_str(), mNum);
    else
        mSystem->message("Deleting %s temp file", type().c_str());
    errno = 0;
    if (remove(mPath.c_str()))
        mSystem->message("Failed to delete %s, %d", mPath.c_str(), errno);
}

