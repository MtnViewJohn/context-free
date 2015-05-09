// tiledCanvas.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006-2012 John Horigan - john@glyphic.com
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

#ifndef INCLUDE_TILEDCANVAS_H
#define INCLUDE_TILEDCANVAS_H

#include "agg_trans_affine.h"
#include "agg_color_rgba.h"
#include "cfdg.h"
#include "bounds.h"
#include "shape.h"
#include <vector>
#include "pathIterator.h"

typedef std::vector<agg::point_i> tileList;

class tiledCanvas : public Canvas {
public:
    void start(bool clear, const agg::rgba& bk, int width, int height) override;
    void end() override;
    
    void circle(RGBA8 c, agg::trans_affine tr) override;
    void square(RGBA8 c, agg::trans_affine tr) override;
    void triangle(RGBA8 c, agg::trans_affine tr) override;
    void fill(RGBA8 c) override;
    void path(RGBA8 c, agg::trans_affine tr, const AST::CommandInfo& attr) override;
    
    tiledCanvas(Canvas* tile, const agg::trans_affine& tr, CFDG::frieze_t f); 
    ~tiledCanvas() override = default;
    tiledCanvas& operator=(const tiledCanvas&) = delete;
    
    void scale(double scaleFactor);
    
    tileList getTesselation(int width, int height, int x, int y, bool flipY = false);
    void tileTransform(const Bounds& b);
    
private:
    Canvas* mTile;
    const agg::trans_affine mTileTransform;
    CFDG::frieze_t mFrieze;
    agg::trans_affine mOffset;
    agg::trans_affine mInvert;
    std::vector<agg::point_d> mTileList;
};

#endif  // INCLUDE_TILEDCANVAS_H
