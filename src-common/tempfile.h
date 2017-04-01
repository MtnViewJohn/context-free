// tempfile.h
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


#ifndef INCLUDE_TEMPFILE_H
#define INCLUDE_TEMPFILE_H

#include "cfdg.h"

class TempFile
{
public:
    std::ostream* forWrite();
    std::istream* forRead();

    const std::string& type() const;
    const std::string& name() const { return mPath; }
    int         number() const { return mNum; }
    void        release() { mWritten = false; }
    bool        written() const { return mWritten; }
    
    TempFile(AbstractSystem*, AbstractSystem::TempType type, int num);
    TempFile(TempFile&&) noexcept;
    TempFile& operator=(TempFile&&) noexcept;
    TempFile(const TempFile&) = delete;
    TempFile& operator=(const TempFile&) = delete;
    ~TempFile();

private:
    AbstractSystem*     mSystem;
    std::string mPath;
    AbstractSystem::TempType mType;
    int         mNum;
    bool        mWritten;
    void        erase();
};

#endif // INCLUDE_TEMPFILE_H
