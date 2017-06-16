// pathIterator.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2011 John Horigan - john@glyphic.com
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


#ifndef INCLUDE_PATHITERATOR_H
#define INCLUDE_PATHITERATOR_H

#include "agg2/agg_bounding_rect.h"
#include "agg2/agg_rasterizer_scanline_aa.h"
#include "agg2/agg_conv_stroke.h"
#include "agg2/agg_conv_curve.h"
#include "agg2/agg_trans_affine.h"
#include "agg2/agg_path_storage.h"

namespace AST {
    struct CommandInfo;
}

class pathIterator {
public:
    using CurvedPath         = agg::conv_curve<agg::path_storage>;
    using CurvedStroked      = agg::conv_stroke<CurvedPath>;
    using CurvedStrokedTrans = agg::conv_transform<CurvedStroked, const agg::trans_affine>;
    using CurvedTrans        = agg::conv_transform<CurvedPath, const agg::trans_affine>;
    using CurvedTransStroked = agg::conv_stroke<CurvedTrans>;
    
    agg::trans_affine   unitTrans;
    CurvedPath          curved;
    CurvedStroked       curvedStroked;
    CurvedStrokedTrans  curvedStrokedTrans;
    CurvedTrans         curvedTrans;
    CurvedTransStroked  curvedTransStroked;
    
    pathIterator();
    ~pathIterator() = default;
    
    void apply(const AST::CommandInfo& attr, const agg::trans_affine& tr, 
               double accuracy);
    template <class Rasterizer>
    void addPath(Rasterizer& ras, const agg::trans_affine& tr, 
                 const AST::CommandInfo& attr);
    bool boundingRect(const agg::trans_affine& tr, const AST::CommandInfo& attr,
                      double& minx, double& miny, double& maxx, double& maxy,
                      double scale);
};

#endif

