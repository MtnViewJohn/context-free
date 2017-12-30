// upload.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2008-2017 John Horigan - john@glyphic.com
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

#include "variation.h"
#include "json3.hpp"
using json = nlohmann::json;

// Base64 Encoder (MIT License)
// Copyright (C) 2013 Tomas Kislan
// Copyright (C) 2013 Adam Rudd

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

static inline void
a3_to_a4(unsigned char* a4, unsigned char* a3)
{
    a4[0] = (a3[0] & 0xfc) >> 2;
    a4[1] = ((a3[0] & 0x03) << 4) | ((a3[1] & 0xf0) >> 4);
    a4[2] = ((a3[1] & 0x0f) << 2) | ((a3[2] & 0xc0) >> 6);
    a4[3] = (a3[2] & 0x3f);
}

static std::string
Encode64(const char* in, size_t input_len)
{
    static const char kBase64Alphabet[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    int i = 0, j = 0;
    size_t enc_len = 0;
    unsigned char a3[3];
    unsigned char a4[4];
    
    size_t expected_len = (input_len + 2 - ((input_len + 2) % 3)) / 3 * 4;
    std::string out(expected_len, ' ');
    
    auto input = in;
    
    while (input_len--) {
        a3[i++] = *(input++);
        if (i == 3) {
            a3_to_a4(a4, a3);
            
            for (j = 0; j < 4; j++)
                out[enc_len++] = kBase64Alphabet[a4[j]];
            
            i = 0;
        }
    }
    
    if (i) {
        for (j = i; j < 3; j++)
            a3[j] = '\0';
        
        a3_to_a4(a4, a3);
        
        for (j = 0; j < i + 1; j++)
            out[enc_len++] = kBase64Alphabet[a4[j]];
        
        while ((i++ < 3))
            out[enc_len++] = '=';
    }
    
    return (enc_len == expected_len) ? out : std::string();
}
// end of Base64 encoder

class FileObject {
public:
    FileObject(const char* name, const char* content, std::size_t length)
    : mName(name), mContent(content), mLength(length)
    {}
    
    std::string mName;
    const char* mContent;
    std::size_t mLength;
};

static void
to_json(json& j, const FileObject& fo)
{
    auto contents64 = Encode64(fo.mContent, fo.mLength);
    j = json{{"filename", fo.mName}, {"contents", contents64}};
}

static void
to_json(json& j, const Upload& u)
{
    j = json{
        {"agent", "ContextFree"},
        {"screenname", u.mUserName},
        {"password", u.mPassword},
        {"designid", u.mId},
        {"title", u.mTitle},
        {"notes", u.mNotes},
        {"variation", u.variationName()},
        {"tiledtype", u.tiledName()},
        {"compression", u.compressionName()},
        {"ccURI", u.mccLicenseURI},
        {"ccImage", u.mccLicenseImage},
        {"ccName", u.mccLicenseName},
        {"cfdgfile", FileObject(u.mFileName.c_str(), u.mText, u.mTextLen)},
        {"imagefile", FileObject("image.png", u.mImage, u.mImageLen)}
    };
}

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
    json j;
    to_json(j, *this);
    return j.dump();
}

Upload::Upload(const std::string& json)
: mId(0)
{
    try {
        auto j = json::parse(json);
        mId = j.at("design").at("designid").get<int>();
    } catch (...) {
        mId = 0;
    }
}
