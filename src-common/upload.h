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

#include <string>
#include "cereal/cereal.hpp"
#include <cstdlib>

class Upload {
public:
    class FileObject {
    public:
        FileObject(const char* name, const char* content, std::size_t length)
        : mName(name), mContent(content), mLength(length)
        {}
        
        template<class Archive>
        void save(Archive & archive) const
        {
            archive(cereal::make_nvp("filename", mName));
            archive.saveBinaryValue(static_cast<const void *>(mContent), mLength, "contents");
        }
    private:
        std::string mName;
        const char* mContent;
        std::size_t mLength;
    };
    Upload() : mId(0), mVariation(0), mCompression(CompressJPEG), mTiled(false) {}
    Upload(const std::string&);
    enum Compression {
        CompressJPEG = 0,
        CompressPNG8 = 1
    };
    
    std::string     mUserName;
    std::string     mPassword;
    
    unsigned        mId = 0;
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
    std::size_t         mTextLen;
    
    const char*         mImage;        // png data
    std::size_t         mImageLen;
    
    std::string generateJSON();
    
    template<class Archive>
    void save(Archive & archive) const
    {
        archive(
            cereal::make_nvp("agent", std::string("ContextFree")),
            cereal::make_nvp("screenname", mUserName),
            cereal::make_nvp("password", mPassword),
            cereal::make_nvp("designid", mId),
            cereal::make_nvp("title", mTitle),
            cereal::make_nvp("notes", mNotes),
            cereal::make_nvp("variation", variationName()),
            cereal::make_nvp("tiledtype", tiledName()),
            cereal::make_nvp("compression", compressionName()),
            cereal::make_nvp("ccURI", mccLicenseURI),
            cereal::make_nvp("ccImage", mccLicenseImage),
            cereal::make_nvp("ccName", mccLicenseName),
            cereal::make_nvp("cfdgfile", FileObject(mFileName.c_str(), mText, mTextLen)),
            cereal::make_nvp("imagefile", FileObject("image.png", mImage, mImageLen))
        );
    }
    
    template<class Archive>
    void load(Archive & archive)
    {
        archive(
                cereal::make_nvp("designid", mId),
                cereal::make_nvp("title", mTitle)
        );
    }
    
private:
    std::string compressionName() const;
    std::string variationName() const;
    std::string tiledName() const;
};

#endif // INCLUDE_UPLOAD_H
