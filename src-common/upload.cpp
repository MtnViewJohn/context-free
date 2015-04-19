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


namespace {
    const char mime_boundary[] = "a3c8dfd7-dce4-443c-ae3c-446df50f28c0";
    const char mime_endl[] = "\r\n";
    
    void generateMimeBoundary(std::ostream& out)
    {
        out << mime_endl << "--" << mime_boundary << mime_endl;
    }
    
    void generateMimeFooter(std::ostream& out)
    {
        out << mime_endl << "--" << mime_boundary << "--" << mime_endl;
    }
    
    void generateTextField(std::ostream& out, const char* field,
                           const std::string& value)
    {
        generateMimeBoundary(out);
        
        out << "Content-Disposition: form-data"
            << "; name=" << field       // shouldn't need quotes
            << mime_endl
            << "Content-Type: text/plain; charset=UTF-8" << mime_endl
            << mime_endl;
        
        out << value; 
    }
    
    void generateTextField(std::ostream& out, const char* field,
                           char value)
    {
        generateMimeBoundary(out);
        
        out << "Content-Disposition: form-data"
            << "; name=" << field       // shouldn't need quotes
            << mime_endl
            << "Content-Type: text/plain; charset=UTF-8" << mime_endl
            << mime_endl;
        
        out << value; 
    }
    
    void generateFileField(std::ostream& out, const char* field,
                           const char* data, size_t length, const std::string& fileName)
    {
        generateMimeBoundary(out);
        
        out << "Content-Disposition: form-data"
            << "; name=" << field       // shouldn't need quotes
            << "; filename=\"" << fileName << '"'
            << mime_endl
            << "Content-Type: application/octet-stream" << mime_endl
            << mime_endl;
        
        out.write(data, length);
    }
    
    std::string compressionName(Upload::Compression compression)
    {
        switch (compression) {
            default:
            case Upload::CompressJPEG:  return "JPEG";
            case Upload::CompressPNG8:  return "PNG-8";
        }
    }
    
    std::string variationName(int variation)
    {
        return Variation::toString(variation, false);
    }
}

std::string Upload::generateHeader()
{
    return std::string("Content-Type: multipart/form-data; boundary=") + 
        mime_boundary;
}

std::string Upload::generateContentType()
{
    return std::string("multipart/form-data; boundary=") + 
        mime_boundary;
}

void
Upload::generatePayload(std::ostream& out)
{
    generateTextField(out, "screenname", mUserName);
    generateTextField(out, "password", mPassword);
    
    generateTextField(out, "agent", "ContextFree");
    
    generateTextField(out, "title", mTitle);
    generateFileField(out, "cfdgfile", mText, mTextLen, mFileName);
    generateFileField(out, "imagefile", mImage, mImageLen, "image.png");
    generateTextField(out, "compression", compressionName(mCompression));
    generateTextField(out, "cc_js_result_uri", mccLicenseURI);
    generateTextField(out, "cc_js_result_name", mccLicenseName);
    generateTextField(out, "cc_js_result_img", mccLicenseImage);
    if (mccLicenseURI.length())
        generateTextField(out, "cc_js_want_cc_license", "sure");
    if (mTiled)
        generateTextField(out, "tiled", "on");
    generateTextField(out, "tiledtype", (char)(mTiled + '0'));
    generateTextField(out, "variation", variationName(mVariation));
    generateTextField(out, "notes", mNotes);
    
    // generateTextField(out, "submit", "Upload!");
    
    generateMimeFooter(out);
}
