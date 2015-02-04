// SVGCanvas.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006-2013 John Horigan - john@glyphic.com
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


#include <iostream>
#include <fstream>
#include <string>
#include "agg_trans_affine.h"
#include "agg_color_rgba.h"
#include "cfdg.h"
#include "ast.h"
#include <map>

class SVGCanvas : public Canvas {
public:
    void start(bool clear, const agg::rgba& bk, int width, int height) override;
    void end() override;

    void complete(RGBA8 c, agg::trans_affine tr, int padding, 
                  const AST::CommandInfo& attr,
                  bool g = false);
    void circle(RGBA8 c, agg::trans_affine tr) override;
    void square(RGBA8 c, agg::trans_affine tr) override;
    void triangle(RGBA8 c, agg::trans_affine tr) override;
    void fill(RGBA8 c) override;
    void path(RGBA8 c, agg::trans_affine tr, const AST::CommandInfo& attr) override;

    SVGCanvas(const char* opath, int width, int height, bool crop, const char* desc = nullptr, int length = -1);
    ~SVGCanvas() override = default;

private:
    typedef std::pair<AST::UIDdatatype, unsigned> uniquePath;
    
    int mPadding;
    char mEndline[82];
    std::map<uniquePath, unsigned> mPathIDMap;
    unsigned mNextPathID;
    agg::trans_affine mOffset;
    bool mCropped;
    std::ofstream mOutputFile;
    std::ostream& mOutput;
    const char* mDescription;
    int mLength;
    void indent(int);
};

