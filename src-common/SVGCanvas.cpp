// SVGCanvas.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006-2011 John Horigan - john@glyphic.com
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


#include "SVGCanvas.h"
#include <cassert>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <sstream>
#include "primShape.h"
#include "ast.h"
#include <map>
#include "CmdInfo.h"
#ifdef _WIN32
#include <Windows.h>
#include <cstdio>
#else
#include "fdostream.h"
#endif


void SVGCanvas::start(bool clear, const agg::rgba& bk, int width, int height)
{
    Canvas::start(clear, bk, width, height);
    //assert(clear);

    if (mCropped) {
        mWidth = width;
        mHeight = height;
    }

    agg::trans_affine_translation off((mWidth - width) / 2.0, (mHeight - height) / 2.0);
    mOffset = off.premultiply(agg::trans_affine(1.0, 0.0, 0.0, -1.0, 0.0, static_cast<double>(mHeight)));

    mOutput << "<?xml version=\"1.0\" standalone=\"no\"?>" << mEndline;
    mOutput << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" " << mEndline;
    mOutput << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << mEndline;
    mOutput << "<svg width=\"" << mWidth << "px\" height=\"" << mHeight << "px\" version=\"1.1\"";
    indent(5);
    mOutput << mEndline << "xmlns=\"http://www.w3.org/2000/svg\"  xmlns:xlink=\"http://www.w3.org/1999/xlink\">";
    indent(-3);
    mOutput << mEndline << "<defs>" << mEndline << 
        "  <polygon id=\"TRIANGLE\" points=\"0,0.57735 -0.5,-0.288675 0.5,-0.288675\"/>" << mEndline << "</defs>";

    if (mDescription) {
        mOutput << mEndline << "<desc>";
        indent(2);
        mOutput << mEndline;
        mOutput.write(mDescription, mLength);
        indent(-2);
        mOutput << mEndline << "</desc>";
    }
}

void SVGCanvas::end() {
    indent(-2);
    mOutput << mEndline << "</svg>" << mEndline;

    mError = mError || !(mOutputFile.is_open() && mOutputFile.good());
    if (mOutputFile.is_open()) mOutputFile.close();
    Canvas::end();
}

void SVGCanvas::complete(RGBA8 c, agg::trans_affine tr, int padding, 
                         const AST::CommandInfo& attr, bool g)
{
    int rgb = (c.r >> (RGBA8::base_shift - 8)) * 65536 + 
              (c.g >> (RGBA8::base_shift - 8)) * 256 + 
              (c.b >> (RGBA8::base_shift - 8));
    const char* ending = g ? ">" : "/>";
    
    indent(padding);
    if (!g) mOutput << mEndline;

    if (attr.mFlags & AST::CF_FILL) {
        mOutput << "stroke=\"none\" fill=\"#" << std::hex << std::setw(6)
                << std::setfill('0') << rgb << std::dec << "\"" << std::setfill(' ');
        
        if (c.a < RGBA8::base_mask) mOutput <<  " fill-opacity=\"" << c.opacity() << "\"";
        if (attr.mFlags & AST::CF_EVEN_ODD)
            mOutput << " fill-rule=\"evenodd\"";
        else
            mOutput << " fill-rule=\"nonzero\"";
    } else {
        mOutput << "fill=\"none\" stroke=\"#" << std::hex << std::setw(6)
                << std::setfill('0') << rgb << std::dec << "\"" << std::setfill(' ');
        
        if (c.a < RGBA8::base_mask) mOutput <<  " stroke-opacity=\"" << c.opacity() << "\"";
        
        if (attr.mFlags & AST::CF_ISO_WIDTH) {
            double scaledWidth = attr.mStrokeWidth * sqrt(fabs(tr.determinant()));
            mOutput << mEndline << "stroke-width=\"" << scaledWidth << "\"";
        } else {
            mOutput << mEndline << "stroke-width=\"" << attr.mStrokeWidth << "\"";
        }
        
        mOutput << " stroke-linecap=\"";
        switch ((attr.mFlags >> 4) & 15) {
            case agg::square_cap:
                mOutput << "butt";
                break;
            case agg::round_cap:
                mOutput << "circle";
                break;
            default:
                mOutput << "miter";
                break;
        }
        
        mOutput << "\" stroke-linejoin=\"";
        switch (attr.mFlags & 15) {
            case agg::bevel_join:
                mOutput << "bevel";
                break;
            case agg::round_join:
                mOutput << "round";
                break;
            default:
                mOutput << "miter";
                break;
        }
        
        mOutput << "\" stroke-miterlimit=\"" << attr.mMiterLimit << "\"";
    }
        
    if (attr.mFlags & AST::CF_ISO_WIDTH) {
        mOutput << ' ' << ending;
    } else {
        mOutput << mEndline << std::setprecision(8);
        mOutput << "transform=\"matrix(" << std::setw(10) << tr.sx << " " << std::setw(10)
        << tr.shy << " " << std::setw(10) << tr.shx << " " << std::setw(10) << tr.sy
        << " " << std::setw(10) << tr.tx << " " << std::setw(10) << tr.ty << ")\""
        << ending;
    }
    indent(-padding); 
}

void SVGCanvas::primitive(int shape, RGBA8 c, agg::trans_affine tr, agg::comp_op_e)
{
    tr *= mOffset;
    static const int padding[3] = { 8, 6, 5 };
    
    switch (shape) {
        case primShape::circleType:
            mOutput << mEndline << "<circle r=\"0.5\"";
            break;
        case primShape::squareType:
            mOutput << mEndline << "<rect x=\"-0.5\" y=\"-0.5\" width=\"1\" height=\"1\" " ;
            break;
        case primShape::triangleType:
            mOutput << mEndline << "<use xlink:href=\"#TRIANGLE\"";
            break;
            
        default:
            return;
    }
    complete(c, tr, padding[shape], AST::CommandInfo::Default);
}

void SVGCanvas::path(RGBA8 c, agg::trans_affine tr, const AST::CommandInfo& attr)
{
    tr *= mOffset;
    mOutput << mEndline << "<g ";
    complete(c, tr, 3, attr, true);
    indent(2);
    uniquePath attrPath(attr.mPathUID.load(), attr.mIndex);
    unsigned id = mPathIDMap[attrPath];
    if (id) {
        mOutput << mEndline << "<use xlink:href=\"#path" << id << "\" />";
    } else {
        id = mNextPathID++;
        mPathIDMap[attrPath] = id;
        mOutput << mEndline << "<path id=\"path" << id << "\" d=";
        attr.mPath->rewind(attr.mIndex);
        unsigned cmd;
        char sep = '"';
        double x, y;
        while (!agg::is_stop(cmd = attr.mPath->vertex(&x, &y))) {
            if (attr.mFlags & AST::CF_ISO_WIDTH) 
                tr.transform(&x, &y);
            
            switch (cmd & agg::path_cmd_mask) {
                case agg::path_cmd_move_to:
                    mOutput << sep << "M " << x << ',' << y;
                    break;
                case agg::path_cmd_line_to:
                    mOutput << sep << "L " << x << ',' << y;
                    break;
                case agg::path_cmd_curve3:
                    mOutput << sep << "Q " << x << ',' << y;
                    attr.mPath->vertex(&x, &y);
                    if (attr.mFlags & AST::CF_ISO_WIDTH) 
                        tr.transform(&x, &y);
                    mOutput << ' ' << x << ',' << y;
                    break;
                case agg::path_cmd_curve4:
                    mOutput << sep << "C " << x << ',' << y;
                    attr.mPath->vertex(&x, &y);
                    if (attr.mFlags & AST::CF_ISO_WIDTH) 
                        tr.transform(&x, &y);
                    mOutput << ' ' << x << ',' << y;
                    attr.mPath->vertex(&x, &y);
                    if (attr.mFlags & AST::CF_ISO_WIDTH) 
                        tr.transform(&x, &y);
                    mOutput << ' ' << x << ',' << y;
                    break;
                case agg::path_cmd_end_poly:
                    if (cmd & agg::path_flags_close)
                        mOutput << sep << 'Z';
                    break;
                default:
                    break;
            }
            sep = ' ';
        }
        if (sep == '"') mOutput << '"';
        mOutput << "\"/>";
    }
    indent(-2);
    mOutput << mEndline << "</g>";
}

void SVGCanvas::indent(int change)
{
    mEndline.resize(mEndline.size() + change, ' ');
}


SVGCanvas::SVGCanvas(const char* opath, int width, int height, bool crop, 
                     const char* desc, int length, bool temp)
:   Canvas(width, height),
    mCropped(crop),
    mOutputFile(),
#ifdef _WIN32
    mOutput(*opath ? mOutputFile : std::cout),
#else
    mOutput(temp ? mOutputTempFile : (*opath ? mOutputFile : std::cout)),
#endif
    mDescription(desc),
    mLength(length)
{
    if (temp) {
#ifdef _WIN32
#else
        mFileName = "/tmp/cfdg_temp_image_XXXXXX.svg";
        int fd = mkstemps(&mFileName[0], 4);
        if (fd != -1)
            mOutputTempFile.setfd(fd);
#endif
    }
    if (*opath) {
        mFileName = opath;
#ifdef _WIN32
        std::wstring wpath = Utf8ToUtf16(opath);
        mOutputFile.open(wpath.c_str(), std::ios::binary | std::ios::trunc | std::ios::out);
#else
        mOutputFile.open(opath, std::ios::binary | std::ios::trunc | std::ios::out);
#endif
    }
    mError = !((temp || mOutputFile.is_open()) && mOutput.good());
    if (mLength == -1 && mDescription)
        mLength = static_cast<int>(std::strlen(mDescription));
}



