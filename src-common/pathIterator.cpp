// pathIterator.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2011-2012 John Horigan - john@glyphic.com
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


#include "pathIterator.h"
#include "ast.h"
#include "CmdInfo.h"
#include "primShape.h"

static primShape dummy;

pathIterator::pathIterator() 
: curved(dummy), 
  curvedStroked(curved), curvedStrokedTrans(curvedStroked, unitTrans),
  curvedTrans(curved, unitTrans), curvedTransStroked(curvedTrans)
{ }

void
pathIterator::apply(const AST::CommandInfo& attr, 
                    const agg::trans_affine& tr, 
                    double accuracy)
{
    double scale = sqrt(fabs(tr.determinant()));
    
    if (attr.mFlags & AST::CF_FILL) {
        curved.attach(*attr.mPath);
        curvedTrans.transformer(tr);
        curved.approximation_scale(accuracy * scale);
    } else {
        if (attr.mFlags & AST::CF_ISO_WIDTH) {
            curved.attach(*attr.mPath);
            curvedTrans.transformer(tr);
            curvedTransStroked.width(attr.mStrokeWidth * scale);
            curvedTransStroked.line_join(static_cast<agg::line_join_e>(attr.mFlags & 7));
            curvedTransStroked.line_cap(static_cast<agg::line_cap_e>((attr.mFlags >> 4) & 7));
            curvedTransStroked.miter_limit(attr.mMiterLimit);
            curvedTransStroked.inner_join(agg::inner_round);
            curvedTransStroked.approximation_scale(accuracy);
            curved.approximation_scale(accuracy * scale);
            
            // If the *visual* line width is considerable we 
            // turn on processing of curve cusps.
            //---------------------
            if (attr.mStrokeWidth * scale > 1.0) {
                curved.angle_tolerance(0.2);
            } else {
                curved.angle_tolerance(0.0);
            }
        } else {
            curved.attach(*attr.mPath);
            curvedStrokedTrans.transformer(tr);
            curvedStroked.width(attr.mStrokeWidth);
            curvedStroked.line_join(static_cast<agg::line_join_e>(attr.mFlags & 7));
            curvedStroked.line_cap(static_cast<agg::line_cap_e>((attr.mFlags >> 4) & 7));
            curvedStroked.miter_limit(attr.mMiterLimit);
            curvedStroked.inner_join(agg::inner_round);
            curvedStroked.approximation_scale(accuracy * scale);
            curved.approximation_scale(accuracy * scale);
            
            // If the *visual* line width is considerable we 
            // turn on processing of curve cusps.
            //---------------------
            if (attr.mStrokeWidth * scale > 1.0) {
                curved.angle_tolerance(0.2);
            } else {
                curved.angle_tolerance(0.0);
            }
        }
    }
}

template <>
void 
pathIterator::addPath<agg::rasterizer_scanline_aa<> >(agg::rasterizer_scanline_aa<>& ras,
                                                      const agg::trans_affine& tr,
                                                      const AST::CommandInfo& attr)
{
    apply(attr, tr, 1.0);
    
    if (attr.mFlags & AST::CF_FILL) {
        ras.add_path(curvedTrans, attr.mIndex);
    } else {
        if (attr.mFlags & AST::CF_ISO_WIDTH) {
            ras.add_path(curvedTransStroked, attr.mIndex);
        } else {
            ras.add_path(curvedStrokedTrans, attr.mIndex);
        }
    }
}

bool
pathIterator::boundingRect(const agg::trans_affine& tr, 
                           const AST::CommandInfo& attr,
                           double& minx, double& miny, 
                           double& maxx, double& maxy,
                           double scale)
{
    apply(attr, tr, scale * 0.1);
    
    bool ret;
    
    if (attr.mFlags & AST::CF_FILL) {
        ret = agg::bounding_rect_single(curvedTrans, attr.mIndex, &minx, &miny, &maxx, &maxy);
    } else {
        if (attr.mFlags & AST::CF_ISO_WIDTH) {
            ret = agg::bounding_rect_single(curvedTransStroked, attr.mIndex, &minx, &miny, &maxx, &maxy);
        } else {
            ret = agg::bounding_rect_single(curvedStrokedTrans, attr.mIndex, &minx, &miny, &maxx, &maxy);
        }
    }
    return ret;
}

