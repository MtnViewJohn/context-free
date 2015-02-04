// posixSystem.h
// Context Free
// ---------------------
// Copyright (C) 2005-2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2007-2012 John Horigan - john@glyphic.com
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

#ifndef INCLUDE_POSIX_SYSTEM
#define INCLUDE_POSIX_SYSTEM

#include "cfdg.h"

class PosixSystem : public AbstractSystem
{
protected:
    virtual void clearAndCR();
public:
    PosixSystem() = default;
    ~PosixSystem() override = default;
    
    void catastrophicError(const char* what) override;
    
    std::ostream* tempFileForWrite(TempType tt, std::string& nameOut) override;
    const char* tempFileDirectory() override;
    std::vector<std::string> findTempFiles() override;
    
    std::string relativeFilePath(
        const std::string& base, const std::string& rel) override;
    size_t getPhysicalMemory() override;
};

#endif // INCLUDE_POSIX_SYSTEM
