// ast.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2012-2013 John Horigan - john@glyphic.com
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

#define _USE_MATH_DEFINES 1
#include "ast.h"
#include "astexpression.h"
#include <cmath>

namespace AST {

    double
    CFatof(const char* s)
    {
        double ret = atof(s);
        return strchr(s, '%') ? ret / 100.0 : ret;
    }
    
    void
    addUnique(SymmList& syms, agg::trans_affine& tr)
    {
        for (SymmList::iterator it = syms.begin(), eit = syms.end(); it != eit; ++it) {
            if (*it == tr)
                return;
        }
        syms.push_back(tr);
    }

    void
    processDihedral(SymmList& syms, double order, double x, double y,
                    bool dihedral, double angle, const yy::location& where)
    {
        if (order < 1.0)
            CfdgError::Error(where, "Rotational symmetry order must be one or larger");
        agg::trans_affine reg;
        agg::trans_affine_reflection mirror(angle);
        reg.translate(-x, -y);
        int num = (int)order;
        order = 2.0 * M_PI / order;
        for (int i = 0; i < num; ++i) {
            agg::trans_affine tr(reg);
            if (i) tr.rotate(i * order);
            agg::trans_affine tr2(tr);
            tr2 *= mirror;
            tr.translate(x, y);
            tr2.translate(x, y);
            addUnique(syms, tr);
            if (dihedral) addUnique(syms, tr2);
        }
    }

    // Analyze the symmetry spec accumulated in the data vector and add the 
    // appropriate affine transforms to the SymmList. Avoid adding the identity
    // transform if it is already present in the SymmList.
    void
    processSymmSpec(SymmList& syms, agg::trans_affine& tile, bool tiled,
                    std::vector<double>& data, const yy::location& where)
    {
        if (data.empty()) return;
        AST::FlagTypes t = (AST::FlagTypes)((int)data[0]);
        bool frieze = (tile.sx != 0.0 || tile.sy != 0.0) && (tile.sx * tile.sy == 0.0);
        bool rhombic = tiled && ((fabs(tile.shy) <= 0.0000001 && fabs(tile.shx/tile.sx - 0.5) < 0.0000001) ||
                                 (fabs(tile.shx) <= 0.0000001 && fabs(tile.shy/tile.sy - 0.5) < 0.0000001));
        bool rectangular = tiled && tile.shx == 0.0 && tile.shy == 0.0;
        bool square = rectangular && tile.sx == tile.sy;
        bool hexagonal = false;
        bool square45 = false;
        double size45 = tile.sx;
        if (rhombic) {
            double x1 = 1.0, y1 = 0.0;
            tile.transform(&x1, &y1);
            double dist10 = sqrt(x1 * x1 + y1 * y1);
            double x2 = 0.0, y2 = 1.0;
            tile.transform(&x2, &y2);
            double dist01 = sqrt(x2 * x2 + y2 * y2);
            hexagonal = fabs(dist10/dist01 - 1.0) < 0.0000001;
            square45 = fabs(dist01/dist10 - M_SQRT2) < 0.0000001 ||
            fabs(dist10/dist01 - M_SQRT2) < 0.0000001;
            size45 = fmin(dist01, dist10);
        }
        static const agg::trans_affine_reflection ref45(M_PI_4);
        static const agg::trans_affine_reflection ref135(-M_PI_4);
        
        if (t >= AST::CF_P11G && t <= AST::CF_P2MM && !frieze)
            CfdgError::Error(where, "Frieze symmetry only works in frieze designs");
        if (t >= AST::CF_PM && t <= AST::CF_P6M && !tiled)
            CfdgError::Error(where, "Wallpaper symmetry only works in tiled designs");
        if (t == AST::CF_P2 && !frieze && !tiled)
            CfdgError::Error(where, "p2 symmetry only works in frieze or tiled designs");
        switch (t) {
            case AST::CF_CYCLIC: {
                double order, x = 0.0, y = 0.0;
                switch (data.size()) {
                    case 4:
                        x = data[2];
                        y = data[3];
                    case 2:
                        order = data[1];
                        break;
                    default:
                        CfdgError::Error(where, "Cyclic symmetry requires an order argument and an optional center of rotation");
                        order = 1.0;    // suppress warning, never executed
                        break;  // never gets here
                }
                processDihedral(syms, order, x, y, false, 0.0, where);
                break;
            }
            case AST::CF_DIHEDRAL: {
                double order, angle = 0.0, x = 0.0, y = 0.0;
                switch (data.size()) {
                    case 5:
                        x = data[3];
                        y = data[4];
                    case 3:
                        order = data[1];
                        angle = data[2] * M_PI / 180.0;
                        break;
                    case 4:
                        x = data[2];
                        y = data[3];
                    case 2:
                        order = data[1];
                        break;
                    default:
                        CfdgError::Error(where, "Dihedral symmetry requires an order argument, an optional mirror angle, and an optional center of rotation");
                        order = 1.0;    // suppress warning, never executed
                        break;  // never gets here
                }
                processDihedral(syms, order, x, y, true, angle, where);
                break;
            }
            case AST::CF_P11G: {
                double mirrorx = 0.0, mirrory = 0.0;
                if (data.size() == 2) {
                    if (tile.sx != 0.0)
                        mirrory = data[1];
                    else
                        mirrorx = data[1];
                } else if (data.size() > 2) {
                    CfdgError::Error(where, "p11g symmetry takes no arguments or an optional glide axis position argument");
                }
                agg::trans_affine tr;
                addUnique(syms, tr);
                tr.translate(-mirrorx, -mirrory);
                if (tile.sx != 0.0)
                    tr.flip_y();
                else
                    tr.flip_x();
                tr.translate(tile.sx * 0.5 + mirrorx, tile.sy * 0.5 + mirrory);
                addUnique(syms, tr);
                break;
            }
            case AST::CF_P11M: {
                double mirrorx = 0.0, mirrory = 0.0;
                if (data.size() == 2) {
                    if (tile.sx != 0.0)
                        mirrory = data[1];
                    else
                        mirrorx = data[1];
                } else if (data.size() > 2) {
                    CfdgError::Error(where, "p11m symmetry takes no arguments or an optional mirror axis position argument");
                }
                agg::trans_affine tr;
                addUnique(syms, tr);
                tr.translate(-mirrorx, -mirrory);
                if (tile.sx != 0.0)
                    tr.flip_y();
                else
                    tr.flip_x();
                tr.translate(mirrorx, mirrory);
                addUnique(syms, tr);
                break;
            }
            case AST::CF_P1M1: {
                double mirrorx = 0.0, mirrory = 0.0;
                if (data.size() == 2) {
                    if (tile.sx != 0.0)
                        mirrorx = data[1];
                    else
                        mirrory = data[1];
                } else if (data.size() > 2) {
                    CfdgError::Error(where, "p1m1 symmetry takes no arguments or an optional mirror axis position argument");
                }
                agg::trans_affine tr;
                addUnique(syms, tr);
                tr.translate(-mirrorx, -mirrory);
                if (tile.sx != 0.0)
                    tr.flip_x();
                else
                    tr.flip_y();
                tr.translate(mirrorx, mirrory);
                addUnique(syms, tr);
                break;
            }
            case AST::CF_P2: {
                double mirrorx = 0.0, mirrory = 0.0;
                if (data.size() == 3) {
                    mirrorx = data[1];
                    mirrory = data[2];
                } else if (data.size() != 1) {
                    CfdgError::Error(where, "p2 symmetry takes no arguments or a center of rotation");
                }
                processDihedral(syms, 2.0, mirrorx, mirrory, false, 0.0, where);
                break;
            }
            case AST::CF_P2MG: {
                double mirrorx = 0.0, mirrory = 0.0;
                if (data.size() == 3) {
                    mirrorx = data[1];
                    mirrory = data[2];
                } else if (data.size() != 1) {
                    CfdgError::Error(where, "p2mg symmetry takes no arguments or a center of rotation");
                }
                agg::trans_affine tr1;
                agg::trans_affine_translation tr2(-mirrorx, -mirrory);
                agg::trans_affine_translation tr3(-mirrorx, -mirrory);
                agg::trans_affine_translation tr4(-mirrorx, -mirrory);
                tr2.flip_x();
                tr3.flip_x();
                tr3.flip_y();
                tr4.flip_y();
                tr2.translate(tile.sx * 0.5 + mirrorx, tile.sy * 0.5 + mirrory);
                tr3.translate(mirrorx, mirrory);
                tr4.translate(tile.sx * 0.5 + mirrorx, tile.sy * 0.5 + mirrory);
                addUnique(syms, tr1);
                addUnique(syms, tr2);
                addUnique(syms, tr3);
                addUnique(syms, tr4);
                break;
            }
            case AST::CF_P2MM: {
                double mirrorx = 0.0, mirrory = 0.0;
                if (data.size() == 3) {
                    mirrorx = data[1];
                    mirrory = data[2];
                } else if (data.size() != 1) {
                    CfdgError::Error(where, "p2mm symmetry takes no arguments or a center of relection");
                }
                processDihedral(syms, 2.0, mirrorx, mirrory, true, 0.0, where);
                break;
            }
            case AST::CF_PM: {
                if (!rectangular && !square45) {
                    CfdgError::Error(where, "pm symmetry requires rectangular tiling");
                }
                double offset = 0.0;
                switch (data.size()) {
                    case 2:
                        break;
                    case 3:
                        offset = data[2];
                        break;
                    default:
                        CfdgError::Error(where, "pm symmetry takes a mirror axis argument and an optional axis position argument");
                }
                agg::trans_affine tr;
                addUnique(syms, tr);
                int axis = (int)data[1];
                if (rectangular && (axis < 0 || axis > 1))
                    CfdgError(where, "pm symmetry mirror axis argument must be 0 or 1");
                else if (axis < 2 || axis > 3)
                    CfdgError::Error(where, "pm symmetry mirror axis argument must be 2 or 3");
                switch (axis) {
                    case 0:         // mirror on x axis
                        tr.translate(0, -offset);
                        tr.flip_y();
                        tr.translate(0, offset);
                        break;
                    case 1:         // mirror on y axis
                        tr.translate(-offset, 0);
                        tr.flip_x();
                        tr.translate(offset, 0);
                        break;
                    case 2:         // mirror on x=y axis
                        tr.translate(-offset * M_SQRT1_2,  offset * M_SQRT1_2);
                        tr *= ref45;
                        tr.translate( offset * M_SQRT1_2, -offset * M_SQRT1_2);
                        break;
                    case 3:         // mirror on x=-y axis
                        tr.translate(-offset * M_SQRT1_2, -offset * M_SQRT1_2);
                        tr *= ref135;
                        tr.translate( offset * M_SQRT1_2,  offset * M_SQRT1_2);
                        break;
                    default:
                        CfdgError::Error(where, "pm symmetry mirror axis argument must be 0, 1, 2, or 3");
                        break;
                }
                addUnique(syms, tr);
                break;
            }
            case AST::CF_PG: {
                if (!rectangular && !square45) {
                    CfdgError::Error(where, "pg symmetry requires rectangular tiling");
                }
                double offset = 0.0;
                switch (data.size()) {
                    case 2:
                        break;
                    case 3:
                        offset = data[2];
                        break;
                    default:
                        CfdgError::Error(where, "pg symmetry takes a glide axis argument and an optional axis position argument");
                }
                agg::trans_affine tr;
                addUnique(syms, tr);
                int axis = (int)data[1];
                if (rectangular && (axis < 0 || axis > 1))
                    CfdgError(where, "pg symmetry mirror axis argument must be 0 or 1");
                else if (axis < 2 || axis > 3)
                    CfdgError::Error(where, "pg symmetry mirror axis argument must be 2 or 3");
                switch (axis) {
                    case 0:         // mirror on x axis
                        tr.translate(0, -offset);
                        tr.flip_y();
                        tr.translate(tile.sx * 0.5, offset);
                        break;
                    case 1:         // mirror on y axis
                        tr.translate(-offset, 0);
                        tr.flip_x();
                        tr.translate(offset, tile.sy * 0.5);
                        break;
                    case 2:         // mirror on x=y axis
                        tr.translate(-offset * M_SQRT1_2,  offset * M_SQRT1_2);
                        tr *= ref45;
                        tr.translate(( offset + size45 * 0.5) * M_SQRT1_2, (-offset + size45 * 0.5) * M_SQRT1_2);
                        break;
                    case 3:         // mirror on x=-y axis
                        tr.translate(-offset * M_SQRT1_2, -offset * M_SQRT1_2);
                        tr *= ref135;
                        tr.translate(( offset - size45 * 0.5) * M_SQRT1_2, ( offset + size45 * 0.5) * M_SQRT1_2);
                        break;
                    default:
                        CfdgError::Error(where, "pg symmetry glide axis argument must be 0, 1, 2, or 3");
                        break;
                }
                addUnique(syms, tr);
                break;
            }
            case AST::CF_CM: {
                if (!rhombic && !square) {
                    CfdgError::Error(where, "cm symmetry requires diamond tiling");
                }
                double offset = 0.0;
                switch (data.size()) {
                    case 2:
                        break;
                    case 3:
                        offset = data[2];
                        break;
                    default:
                        CfdgError::Error(where, "cm symmetry takes a mirror axis argument and an optional axis position argument");
                }
                agg::trans_affine tr;
                addUnique(syms, tr);
                int axis = (int)data[1];
                if (rectangular && (axis < 0 || axis > 1))
                    CfdgError(where, "cm symmetry mirror axis argument must be 0 or 1");
                else if (axis < 2 || axis > 3)
                    CfdgError::Error(where, "cm symmetry mirror axis argument must be 2 or 3");
                switch (axis) {
                    case 0:         // mirror on x axis
                        tr.translate(0, -offset);
                        tr.flip_y();
                        tr.translate(0, offset);
                        break;
                    case 1:         // mirror on y axis
                        tr.translate(-offset, 0);
                        tr.flip_x();
                        tr.translate(offset, 0);
                        break;
                    case 2:         // mirror on x=y axis
                        tr.translate( offset * M_SQRT1_2, -offset * M_SQRT1_2);
                        tr *= ref45;
                        tr.translate(-offset * M_SQRT1_2,  offset * M_SQRT1_2);
                        break;
                    case 3:         // mirror on x=-y axis
                        tr.translate(-offset * M_SQRT1_2, -offset * M_SQRT1_2);
                        tr *= ref135;
                        tr.translate( offset * M_SQRT1_2,  offset * M_SQRT1_2);
                        break;
                    default:
                        CfdgError::Error(where, "cm symmetry mirror axis argument must be 0, 1, 2, or 3");
                        break;
                }
                addUnique(syms, tr);
                break;
            }
            case AST::CF_PMM: {
                if (!rectangular && !square45) {
                    CfdgError::Error(where, "pmm symmetry requires rectangular tiling");
                }
                double centerx = 0.0, centery = 0.0;
                switch (data.size()) {
                    case 1:
                        break;
                    case 3:
                        centerx = data[1];
                        centery = data[2];
                        break;
                    default:
                        CfdgError::Error(where, "pmm symmetry takes no arguments or a center of reflection");
                }
                processDihedral(syms, 2.0, centerx, centery, true, square45 ? M_PI_4 : 0.0, where);
                break;
            }
            case AST::CF_PMG: {
                if (!rectangular && !square45) {
                    CfdgError::Error(where, "pmg symmetry requires rectangular tiling");
                }
                double centerx = 0.0, centery = 0.0;
                switch (data.size()) {
                    case 2:
                        break;
                    case 4:
                        centerx = data[2];
                        centery = data[3];
                        break;
                    default:
                        CfdgError::Error(where, "pmg symmetry takes a mirror axis argument and an optional center of reflection");
                }
                agg::trans_affine tr, tr2;
                int axis = (int)data[1];
                if (rectangular && (axis < 0 || axis > 1))
                    CfdgError(where, "pmg symmetry mirror axis argument must be 0 or 1");
                else if (axis < 2 || axis > 3)
                    CfdgError::Error(where, "pmg symmetry mirror axis argument must be 2 or 3");
                switch (axis) {
                    case 0: {       // mirror on x axis
                        double cy = fabs(centery + 0.25 * tile.sy) < fabs(centery - 0.25 * tile.sy) ?
                        centery + 0.25 * tile.sy : centery - 0.25 * tile.sy;
                        processDihedral(syms, 2.0, centerx, cy, false, 0.0, where);
                        agg::trans_affine tr, tr2;
                        tr.translate(-centerx, 0.0);
                        tr.flip_x();
                        tr.translate(centerx, 0.5 * tile.sy);
                        addUnique(syms, tr);
                        tr2.translate(0.0, -centery);
                        tr2.flip_y();
                        tr2.translate(0.0, centery);
                        addUnique(syms, tr2);
                        break;
                    }
                    case 1: {       // mirror on y axis
                        double cx = fabs(centerx + 0.25 * tile.sx) < fabs(centerx - 0.25 * tile.sx) ?
                        centerx + 0.25 * tile.sx : centerx - 0.25 * tile.sx;
                        processDihedral(syms, 2.0, cx, centery, false, 0.0, where);
                        agg::trans_affine tr, tr2;
                        tr.translate(-centerx, 0.0);
                        tr.flip_x();
                        tr.translate(centerx, 0.0);
                        addUnique(syms, tr);
                        tr2.translate(0.0, -centery);
                        tr2.flip_y();
                        tr2.translate(0.5 * tile.sx, centery);
                        addUnique(syms, tr2);
                        break;
                    }
                    case 2: {       // mirror on x=y axis
                        double cx  = centerx - 0.25 * M_SQRT1_2 * size45;
                        double cy  = centery + 0.25 * M_SQRT1_2 * size45;
                        double cx2 = centerx + 0.25 * M_SQRT1_2 * size45;
                        double cy2 = centery - 0.25 * M_SQRT1_2 * size45;
                        if (cx2 * cx2 + cy2 * cy2 < cx * cx + cy * cy) {
                            cx = cx2;
                            cy = cy2;
                        }
                        processDihedral(syms, 2.0, cx, cy, false, 0.0, where);
                        agg::trans_affine tr, tr2;
                        tr.translate(-centerx, -centery);   // mirror on x=y
                        tr *= ref45;
                        tr.translate( centerx,  centery);
                        addUnique(syms, tr);
                        tr2.translate(-centerx, -centery);   // glide on x=-y
                        tr2 *= ref135;
                        tr2.translate(centerx - size45 * M_SQRT1_2 * 0.5, centery + size45 * M_SQRT1_2 * 0.5);
                        addUnique(syms, tr2);
                        break;
                    }
                    case 3: {       // mirror on x=-y axis
                        double cx  = centerx + 0.25 * M_SQRT1_2 * size45;
                        double cy  = centery + 0.25 * M_SQRT1_2 * size45;
                        double cx2 = centerx - 0.25 * M_SQRT1_2 * size45;
                        double cy2 = centery - 0.25 * M_SQRT1_2 * size45;
                        if (cx2 * cx2 + cy2 * cy2 < cx * cx + cy * cy) {
                            cx = cx2;
                            cy = cy2;
                        }
                        processDihedral(syms, 2.0, cx, cy, false, 0.0, where);
                        agg::trans_affine tr, tr2;
                        tr.translate(-centerx, -centery);   // mirror on x=-y
                        tr *= ref135;
                        tr.translate( centerx,  centery);
                        addUnique(syms, tr);
                        tr2.translate(-centerx, -centery);   // glide on x=y
                        tr2 *= ref45;
                        tr2.translate(centerx + size45 * M_SQRT1_2 * 0.5, centery + size45 * M_SQRT1_2 * 0.5);
                        addUnique(syms, tr2);
                        break;
                    }
                    default:
                        CfdgError::Error(where, "pmg symmetry mirror axis argument must be 0, 1, 2, or 3");
                        break;
                }
                break;
            }
            case AST::CF_PGG: {
                if (!rectangular && !square45) {
                    CfdgError::Error(where, "pgg symmetry requires rectangular tiling");
                }
                double centerx = 0.0, centery = 0.0;
                switch (data.size()) {
                    case 1:
                        break;
                    case 3:
                        centerx = data[1];
                        centery = data[2];
                        break;
                    default:
                        CfdgError::Error(where, "pgg symmetry takes no arguments or a center of glide axis intersection");
                }
                if (square45) {
                    double cx = centerx + 0.25 * M_SQRT2 * size45;
                    double cy = centery;
                    double cx2 = centerx - 0.25 * M_SQRT2 * size45;
                    double cy2 = centery;
                    if (cx2*cx2 + cy2*cy2 < cx*cx + cy*cy) {
                        cx = cx2;
                        cy = cy2;
                    }
                    cx2 = centerx;
                    cy2 = centery + 0.25 * M_SQRT2 * size45;
                    if (cx2*cx2 + cy2*cy2 < cx*cx + cy*cy) {
                        cx = cx2;
                        cy = cy2;
                    }
                    cx2 = centerx;
                    cy2 = centery - 0.25 * M_SQRT2 * size45;
                    if (cx2*cx2 + cy2*cy2 < cx*cx + cy*cy) {
                        cx = cx2;
                        cy = cy2;
                    }
                    processDihedral(syms, 2.0, cx, cy, false, 0.0, where);
                    agg::trans_affine tr, tr2;
                    tr.translate(-centerx, -centery);   // glide on x=y
                    tr *= ref45;
                    tr.translate(centerx + size45 * M_SQRT1_2 * 0.5, centery + size45 * M_SQRT1_2 * 0.5);
                    addUnique(syms, tr);
                    tr2.translate(-centerx, -centery);   // glide on x=-y
                    tr2 *= ref135;
                    tr2.translate(centerx - size45 * M_SQRT1_2 * 0.5, centery + size45 * M_SQRT1_2 * 0.5);
                    addUnique(syms, tr2);
                    break;
                }
                double cx = fabs(centerx + 0.25 * tile.sx) < fabs(centerx - 0.25 * tile.sx) ?
                centerx + 0.25 * tile.sx : centerx - 0.25 * tile.sx;
                double cy = fabs(centery + 0.25 * tile.sy) < fabs(centery - 0.25 * tile.sy) ?
                centery + 0.25 * tile.sy : centery - 0.25 * tile.sy;
                processDihedral(syms, 2.0, cx, cy, false, 0.0, where);
                agg::trans_affine tr, tr2;
                tr.translate(-centerx, 0.0);
                tr.flip_x();
                tr.translate(centerx, 0.5 * tile.sy);
                addUnique(syms, tr);
                tr2.translate(0.0, -centery);
                tr2.flip_y();
                tr2.translate(0.5 * tile.sx, centery);
                addUnique(syms, tr2);
                break;
            }
            case AST::CF_CMM: {
                if (!rhombic && !square) {
                    CfdgError::Error(where, "cmm symmetry requires diamond tiling");
                }
                double centerx = 0.0, centery = 0.0;
                switch (data.size()) {
                    case 1:
                        break;
                    case 3:
                        centerx = data[1];
                        centery = data[2];
                        break;
                    default:
                        CfdgError::Error(where, "cmm symmetry takes no arguments or a center of reflection");
                }
                processDihedral(syms, 2.0, centerx, centery, true, square45 ? M_PI_4 : 0.0, where);
                break;
            }
            case AST::CF_P4:
            case AST::CF_P4M: {
                if (!square && !square45) {
                    CfdgError::Error(where, "p4 & p4m symmetry requires square tiling");
                }
                double x = 0.0, y = 0.0;
                switch (data.size()) {
                    case 1:
                        break;
                    case 3:
                        x = data[1];
                        y = data[2];
                        break;
                    default:
                        CfdgError::Error(where, "p4 & p4m symmetry takes no arguments or a center of rotation");
                }
                processDihedral(syms, 4.0, x, y, t == AST::CF_P4M, square ? M_PI_4 : 0.0, where);
                break;
            }
            case AST::CF_P4G: {
                if (!square && !square45) {
                    CfdgError::Error(where, "p4g symmetry requires square tiling");
                }
                double centerx = 0.0, centery = 0.0;
                switch (data.size()) {
                    case 1:
                        break;
                    case 3:
                        centerx = data[1];
                        centery = data[2];
                        break;
                    default:
                        CfdgError::Error(where, "p4g symmetry takes no arguments or a center of rotation");
                }
                agg::trans_affine reg;
                reg.translate(-centerx, -centery);
                agg::trans_affine glide(reg);
                if (square45) {
                    glide.translate(-size45 * 0.25 * M_SQRT1_2, -size45 * 0.25 * M_SQRT1_2);
                    glide *= ref135;
                    glide.translate(-size45 * 0.25 * M_SQRT1_2,  size45 * 0.75 * M_SQRT1_2);
                } else {
                    glide.translate(tile.sx * 0.25, 0.0);
                    glide.flip_x();
                    glide.translate(-tile.sx * 0.25, tile.sy * 0.5);
                }
                for (int i = 0; i < 4; ++i) {
                    agg::trans_affine tr(reg), tr2(glide);
                    if (i) {
                        tr.rotate(i * M_PI_2);
                        tr2.rotate(i * M_PI_2);
                    }
                    tr.translate(centerx, centery);
                    tr2.translate(centerx, centery);
                    addUnique(syms, tr);
                    addUnique(syms, tr2);
                }
                break;
            }
            case AST::CF_P3: {
                if (!hexagonal) {
                    CfdgError::Error(where, "p3 symmetry requires hexagonal tiling");
                }
                double x = 0.0, y = 0.0;
                switch (data.size()) {
                    case 1:
                        break;
                    case 3:
                        x = data[1];
                        y = data[2];
                        break;
                    default:
                        CfdgError::Error(where, "p3 symmetry takes no arguments or a center of rotation");
                }
                processDihedral(syms, 3.0, x, y, false, 0.0, where);
                break;
            }
            case AST::CF_P3M1:
            case AST::CF_P31M: {
                if (!hexagonal) {
                    CfdgError::Error(where, "p3m1 & p31m symmetry requires hexagonal tiling");
                }
                double x = 0.0, y = 0.0;
                switch (data.size()) {
                    case 1:
                        break;
                    case 3:
                        x = data[1];
                        y = data[2];
                        break;
                    default:
                        CfdgError::Error(where, "p3m1 & p31m symmetry takes no arguments or a center of rotation");
                }
                bool deg30 = (fabs(tile.shx) <= 0.000001) != (t == AST::CF_P3M1);
                double angle = M_PI / (deg30 ? 6.0 : 3.0);
                processDihedral(syms, 3.0, x, y, true, angle, where);
                break;
            }
            case AST::CF_P6:
            case AST::CF_P6M: {
                if (!hexagonal) {
                    CfdgError::Error(where, "p6 & p6m symmetry requires hexagonal tiling");
                }
                double x = 0.0, y = 0.0;
                switch (data.size()) {
                    case 1:
                        break;
                    case 3:
                        x = data[1];
                        y = data[2];
                        break;
                    default:
                        CfdgError::Error(where, "p6 & p6m symmetry takes no arguments or a center of rotation");
                }
                processDihedral(syms, 6.0, x, y, t == AST::CF_P6M, 0.0, where);
                break;
            }
            default:
                CfdgError::Error(where, "Unknown symmetry type");
                break;  // never gets here
        }
        data.clear();
    }
    
    const ASTexpression*
    getTransforms(const ASTexpression* e, SymmList& syms, Renderer* r, 
                  bool tiled, agg::trans_affine& tile)
    {
        syms.clear();
        if (e == NULL) return NULL;
        ASTexpression* ret = 0;
        
        std::vector<double> symmSpec;
        yy::location where;
        for (int i = 0; i < e->size(); ++i)
        {
            const ASTexpression* cit = (*e)[i];
            switch (cit->mType) {
                case ASTexpression::FlagType:
                    processSymmSpec(syms, tile, tiled, symmSpec, where);
                    where = cit->where;
                case ASTexpression::NumericType: {
                    if (symmSpec.empty() && cit->mType != ASTexpression::FlagType)
                        CfdgError::Error(cit->where, "Symmetry flag expected here");
                    int sz = cit->evaluate(0, 0);
                    if (sz < 1) {
                        CfdgError::Error(cit->where, "Could not evaluate this");
                    } else {
                        size_t oldsize = symmSpec.size();
                        symmSpec.resize(oldsize + sz);
                        if (cit->evaluate(&(symmSpec[oldsize]), sz, r) != sz)
                            CfdgError::Error(cit->where, "Could not evaluate this");
                    }
                    where = where + cit->where;
                    break;
                }
                case ASTexpression::ModType: {
                    processSymmSpec(syms, tile, tiled, symmSpec, where);
                    const ASTmodification* m = dynamic_cast<const ASTmodification*>(&*cit);
                    if ((!r && !cit->isConstant) || !m || 
                        (m->modClass & (ASTmodification::GeomClass | ASTmodification::PathOpClass)) != 
                         m->modClass)
                    {
                        // const_cast is a little sleazy, but we never never modify
                        // it and we return it as const
                        ret = ASTexpression::Append(ret, const_cast<ASTexpression*>(cit));
                    } else {
                        Modification mod;
                        int dummy;
                        cit->evaluate(mod, 0, 0, false, dummy, false, r);
                        addUnique(syms, mod.m_transform);
                    }
                    break;
                }
                default:
                    CfdgError::Error(cit->where, "Wrong type");
                    break;
            }
        }
        processSymmSpec(syms, tile, tiled, symmSpec, where);
        return ret;
    }
}
