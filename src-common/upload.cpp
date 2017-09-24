// upload.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2008-2012 John Horigan - john@glyphic.com
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
// Mark Lentczner can be contacted at markl@glyphic.com or at
// Mark Lentczner, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//

#include "upload.h"

#include <iostream>

#include "variation.h"
#include "cereal/archives/json.hpp"


std::string
Upload::compressionName() const
{
    switch (mCompression) {
        default:
        case Upload::CompressJPEG:  return "JPEG";
        case Upload::CompressPNG8:  return "PNG-8";
    }
}

std::string
Upload::variationName() const
{
    return Variation::toString(mVariation, false);
}

std::string
Upload::tiledName() const
{
    return std::string(1, (char)(mTiled + '0'));
}

std::string
Upload::generateJSON()
{
    std::ostringstream out;
    {
        cereal::JSONOutputArchive archive(out);
        save(archive);
    }
    return out.str();
}

Upload::Upload(const std::string& json)
: mId(0)
{
    try {
        std::istringstream in(json);
        cereal::JSONInputArchive archive(in);
        archive(cereal::make_nvp("design", *this));
    } catch (cereal::Exception&) {
        mId = 0;
    }
}
