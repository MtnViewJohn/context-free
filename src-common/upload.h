// upload.h
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

#ifndef INCLUDE_UPLOAD_H
#define INCLUDE_UPLOAD_H

#include <iosfwd>
#include <string>

class Upload {
public:
    Upload() : mVariation(0), mCompression(CompressJPEG), mTiled(false) {}
    enum Compression {
        CompressJPEG = 0,
        CompressPNG8 = 1
    };
    
    std::string     mUserName;
    std::string     mPassword;
    
    std::string     mTitle;
    std::string     mNotes;
    
    std::string     mFileName;         // include .cfdg ending here
    int             mVariation;
    Compression     mCompression;
    int             mTiled;
    
    std::string     mccLicenseURI;
    std::string     mccLicenseName;
    std::string     mccLicenseImage;
    
    const char*         mText;         // cfdg file, utf-8 text
    size_t              mTextLen;
    
    const char*         mImage;        // png data
    size_t              mImageLen;
    
    void generatePayload(std::ostream&);
    
    static std::string generateHeader();
    static std::string generateContentType();
};

#endif // INCLUDE_UPLOAD_H
