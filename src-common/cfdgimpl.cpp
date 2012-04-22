// cfdgimpl.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2006-2008 John Horigan - john@glyphic.com
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


#define _USE_MATH_DEFINES 1
#include "cfdgimpl.h"
#include "builder.h"
#include "renderimpl.h"
#include "primShape.h"
#include <assert.h>
#include <algorithm>
#include "astreplacement.h"
#include <limits>
#include <cstring>
#include "agg_trans_affine_time.h"

#ifdef _WIN32
#pragma warning( disable : 4800 4189 )
#endif

#ifdef _WIN32
#include <float.h>
#define isfinite _finite
#endif
#include <math.h>

using namespace std;
using namespace AST;


CFDGImpl::CFDGImpl(AbstractSystem* m) 
: mInitShape(0), mInitShapeDepth(std::numeric_limits<unsigned>::max()), 
  m_backgroundColor(1, 1, 1, 1),
  mStackSize(0), m_system(m), m_secondPass(false), m_Parameters(0), 
  mTileOffset(0, 0), needle(0, CfdgError::Default)
{ 
    // These have to be encoded first so that their type number will fit
    // within an unsigned char
    string circle_name = "CIRCLE";
    string square_name = "SQUARE";
    string triangle_name = "TRIANGLE";
    string fill_name = "FILL";
    
    // ensure these four get the first four shape numbers
    int circle_num = encodeShapeName(circle_name);
    int square_num = encodeShapeName(square_name);
    int triangle_num = encodeShapeName(triangle_name);
    int fill_num = encodeShapeName(fill_name);

    // Make sure that the shape numbers correspond to the order of primShape::shapeMap[]
    assert(circle_num == primShape::circleType);
    assert(square_num == primShape::squareType);
    assert(triangle_num == primShape::triangleType);
    assert(fill_num == primShape::fillType);
    
    mCFDGcontents.isGlobal = true;
}

CFDGImpl::CFDGImpl(CFDGImpl* c)
: mInitShape(0), mInitShapeDepth(std::numeric_limits<unsigned>::max()), 
  m_backgroundColor(1, 1, 1, 1),
  mStackSize(0), m_system(c->m_system), m_secondPass(true), m_Parameters(0), 
  mTileOffset(0, 0), needle(0, CfdgError::Default)
{
    m_shapeTypes.swap(c->m_shapeTypes);
    mFunctions.swap(c->mFunctions);
    fileNames.swap(c->fileNames);
    for (std::vector<ShapeType>::iterator it = m_shapeTypes.begin(), eit = m_shapeTypes.end(); 
         it != eit; ++it)
        it->shapeType = newShape;
    mCFDGcontents.isGlobal = true;
}

void
CFDGImpl::deleteConfigParam(pair<const int, ConfigParam*>& p)
{
    delete p.second->second;
    delete p.second;
}

void
CFDGImpl::deleteFunction(pair<const int, ASTdefine*>& p)
{
    delete p.second;
}

void
CFDGImpl::deleteShapeParams(ShapeType& s)
{
    delete s.parameters;
}

CFDGImpl::~CFDGImpl()
{
    for_each(m_ConfigParameters.begin(), m_ConfigParameters.end(), deleteConfigParam);
    for_each(mFunctions.begin(), mFunctions.end(), deleteFunction);
    for_each(m_shapeTypes.begin(), m_shapeTypes.end(), deleteShapeParams);
}

void
CFDGImpl::setInitialShape(rep_ptr init, unsigned depth)
{
    if (depth < mInitShapeDepth) {
        mInitShape = init;
        m_initialShape.mShapeType = mInitShape->mShapeSpec.shapeType;
        mInitShapeDepth = depth;
    }
}

const Shape&
CFDGImpl::getInitialShape(Renderer* r)
{
    if (mInitShape->mShapeSpec.argSize == 0 &&
        getShapeParamSize(mInitShape->mShapeSpec.shapeType))
    {
        throw CfdgError(mInitShape->mLocation, "This shape takes parameters");
    }
    Shape init;
    init.mWorldState.m_Color = HSBColor(0.0, 0.0, 0.0, 1.0);
    init.mWorldState.m_ColorTarget = HSBColor(0.0, 0.0, 0.0, 1.0);
    init.mWorldState.m_time.tend = 1.0;
    mInitShape->replace(init, r);
    init.mWorldState.m_transform.tx += mTileOffset.x;
    init.mWorldState.m_transform.ty += mTileOffset.y;
    m_initialShape = init;
    return m_initialShape; 
}

const agg::rgba&
CFDGImpl::getBackgroundColor(Renderer* r)
{
    Modification white;
    white.m_Color = HSBColor(0.0, 0.0, 1.0, 1.0);
    if (r && hasParameter("CF::Background", white, r)) {
        white.m_Color.getRGBA(m_backgroundColor);
        if (!usesAlpha)
            m_backgroundColor.a = 1.0;
    }
    return m_backgroundColor;
}

const ASTrule*
CFDGImpl::findRule(int shapetype, double r)
{
    needle.mNameIndex = shapetype;
    needle.mWeight = r;
    
    vector<ASTrule*>::iterator first = lower_bound(mRules.begin(), mRules.end(), 
                                                   &needle, ASTrule::compareLT);
    if (first == mRules.end() || (*first)->mNameIndex != shapetype)
        throw CfdgError("Cannot find a rule for a shape (very helpful I know).");
    return *first;
}

// Search for a rule in the mRules list even before it is sorted
const ASTrule*
CFDGImpl::findRule(int shapetype)
{
    for (vector<ASTrule*>::iterator i = mRules.begin(); i != mRules.end(); ++i)
        if ((*i)->mNameIndex == shapetype)
            return *i;
    
    return NULL;
}

// Adds a new rule/path to the rule container. Updates information about the rule
// in the m_shapeTypes[] vector. If the rule is known to have parameters then
// they are copied into the new rule.
bool
CFDGImpl::addRule(ASTrule* r)
{
    mRules.push_back(r);
    
    ShapeType& shapeItem = m_shapeTypes[r->mNameIndex];
    if (shapeItem.shapeType == newShape)
        shapeItem.shapeType = (r->isPath) ? pathType : ruleType; 
    if (shapeItem.parameters && !shapeItem.parameters->empty())
        r->mRuleBody.mParameters = *(shapeItem.parameters);
    shapeItem.hasRules = true;
    return shapeItem.isShape;
}

void 
CFDGImpl::addParameter(Parameter p)
{
    m_Parameters |= p;
    usesColor = m_Parameters & Color;
    usesTime = m_Parameters & Time;
    usesFrameTime = m_Parameters & FrameTime;
}

RGBA8
CFDGImpl::getColor(const HSBColor& hsb)
{
    agg::rgba c;
    hsb.getRGBA(c);
    if (uses16bitColor) {
        return RGBA8(c);
    } else {
        agg::rgba8 c8 = agg::rgba8(c);
        return RGBA8(c8);
    }
}

bool
CFDGImpl::isTiled(agg::trans_affine* tr, double* x, double* y) const
{
    yy::location loc;
    if (!hasParameter("CF::Tile", ASTexpression::ModType, loc)) return false;
    if (mTileMod.m_transform.sx == 0.0 || mTileMod.m_transform.sy == 0.0) return false;
    if (tr) {
        *tr = mTileMod.m_transform;
        tr->tx = tr->ty = 0.0;
    }
    if (x && y) {
        double o_x = 0.0;
        double o_y = 0.0;
        double u_x = 1.0;
        double u_y = 0.0;
        double v_x = 0.0;
        double v_y = 1.0;
        
        mTileMod.m_transform.transform(&o_x, &o_y);
        mTileMod.m_transform.transform(&u_x, &u_y);
        mTileMod.m_transform.transform(&v_x, &v_y);
        
        if (fabs(u_y - o_y) >= 0.0001 && fabs(v_x - o_x) >= 0.0001) 
            CfdgError::Error(loc, "Tile must be aligned with the X or Y axis.");
        if ((u_x - o_x) < 0.0 || (v_y - o_y) < 0.0)
            CfdgError::Error(loc, "Tile must be in the positive X/Y quadrant.");
        
        *x = u_x - o_x;
        *y = v_y - o_y;
    }
    return true;
}

CFDG::frieze_t
CFDGImpl::isFrieze(agg::trans_affine* tr, double* x, double* y) const
{
    yy::location loc;
    if (!hasParameter("CF::Tile", ASTexpression::ModType, loc)) return no_frieze;
    if (mTileMod.m_transform.sx != 0.0 && mTileMod.m_transform.sy != 0.0) return no_frieze;
    if (mTileMod.m_transform.sx == 0.0 && mTileMod.m_transform.sy == 0.0) return no_frieze;
    if (tr) {
        *tr = mTileMod.m_transform;
        tr->tx = tr->ty = 0.0;
    }
    if (x && y) {
        double o_x = 0.0;
        double o_y = 0.0;
        double u_x = 1.0;
        double u_y = 0.0;
        double v_x = 0.0;
        double v_y = 1.0;
        
        mTileMod.m_transform.transform(&o_x, &o_y);
        mTileMod.m_transform.transform(&u_x, &u_y);
        mTileMod.m_transform.transform(&v_x, &v_y);
        
        if (fabs(u_y - o_y) >= 0.0001 || fabs(v_x - o_x) >= 0.0001) 
            CfdgError::Error(loc, "Frieze must be aligned with the X and Y axis.");
        if ((u_x - o_x) < 0.0 || (v_y - o_y) < 0.0)
            CfdgError::Error(loc, "Frieze must be in the positive X/Y quadrant.");
        
        *x = u_x - o_x;
        *y = v_y - o_y;
    }
    return mTileMod.m_transform.sx == 0.0 ? frieze_y : frieze_x;
}

bool
CFDGImpl::isSized(double* x, double* y) const
{
    yy::location loc;
    if (!hasParameter("CF::Size", ASTexpression::ModType, loc)) return false;
    if (x) *x = mSizeMod.m_transform.sx;
    if (y) *y = mSizeMod.m_transform.sy;
    if (mSizeMod.m_transform.shx != 0.0 || mSizeMod.m_transform.shy != 0.0)
        CfdgError::Error(loc, "Size specification must not be rotated or skewed.");
    return true;
}

bool
CFDGImpl::isTimed(agg::trans_affine_time* t) const
{
    yy::location loc;
    if (!hasParameter("CF::Time", ASTexpression::ModType, loc)) return false;
    if (t) *t = mTimeMod.m_time;
    if (mTimeMod.m_time.tbegin >= mTimeMod.m_time.tend)
        CfdgError::Error(loc, "Time specification must have positive duration.");
    return true;
}

static void
addUnique(CFDG::SymmList& syms, agg::trans_affine& tr)
{
    for (CFDG::SymmList::iterator it = syms.begin(), eit = syms.end(); it != eit; ++it) {
        if (*it == tr)
            return;
    }
    syms.push_back(tr);
}

static void
processDihedral(CFDG::SymmList& syms, double order, double x, double y,
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
static void
processSymmSpec(CFDG::SymmList& syms, agg::trans_affine& tile, bool tiled,
                std::vector<double>& data, const yy::location& where)
{
    if (data.empty()) return;
    AST::FlagTypes t = (AST::FlagTypes)((int)data[0]);
    bool frieze = (tile.sx != 0.0 || tile.sy != 0.0) && (tile.sx * tile.sy == 0.0);
    bool rhombic = tiled && ((fabs(tile.shy) <= 0.0000001 && fabs(tile.shx/tile.sx - 0.5) < 0.0000001) ||
                             (fabs(tile.shx) <= 0.0000001 && fabs(tile.shy/tile.sy - 0.5) < 0.0000001));
    bool hexagonal = false;
    if (rhombic) {
        double x1 = 1.0, y1 = 0.0;
        tile.transform(&x1, &y1);
        double dist10 = sqrt(x1 * x1 + y1 * y1);
        double x2 = 0.0, y2 = 1.0;
        tile.transform(&x2, &y2);
        double dist01 = sqrt(x2 * x2 + y2 * y2);
        hexagonal = fabs(dist10/dist01 - 1.0) < 0.0000001;
    }
    
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
            if (tile.shx != 0.0 || tile.shy != 0.0) {
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
            if (data[1]) {  // mirror on y axis
                tr.translate(-offset, 0);
                tr.flip_x();
                tr.translate(offset, 0);
            } else {        // mirror on x axis
                tr.translate(0, -offset);
                tr.flip_y();
                tr.translate(0, offset);
            }
            addUnique(syms, tr);
            break;
        }
        case AST::CF_PG: {
            if (tile.shx != 0.0 || tile.shy != 0.0) {
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
            if (data[1]) {  // glide on y axis
                tr.translate(-offset, 0);
                tr.flip_x();
                tr.translate(offset, tile.sy * 0.5);
            } else {        // glide on x axis
                tr.translate(0, -offset);
                tr.flip_y();
                tr.translate(tile.sx * 0.5, offset);
            }
            addUnique(syms, tr);
            break;
        }
        case AST::CF_CM: {
            if (!rhombic) {
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
            if (data[1]) {  // mirror on y axis
                tr.translate(-offset, 0);
                tr.flip_x();
                tr.translate(offset, 0.0);
            } else {        // mirror on x axis
                tr.translate(0, -offset);
                tr.flip_y();
                tr.translate(0.0, offset);
            }
            addUnique(syms, tr);
            break;
        }
        case AST::CF_PMM: {
            if (!tiled || tile.shx != 0.0 || tile.shy != 0.0) {
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
            processDihedral(syms, 2.0, centerx, centery, true, 0.0, where);
            break;
        }
        case AST::CF_PMG: {
            if (!tiled || tile.shx != 0.0 || tile.shy != 0.0) {
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
            if (data[1]) {  // mirror on y axis
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
            } else {        // mirror on x axis
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
            }
            break;
        }
        case AST::CF_PGG: {
            if (!tiled || tile.shx != 0.0 || tile.shy != 0.0) {
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
            if (!rhombic) {
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
            processDihedral(syms, 2.0, centerx, centery, true, 0.0, where);
            break;
        }
        case AST::CF_P4:
        case AST::CF_P4M: {
            if (!tiled || tile.shx != 0.0 || tile.shy != 0.0 || tile.sx != tile.sy) {
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
            processDihedral(syms, 4.0, x, y, t == AST::CF_P4M, M_PI * 0.25, where);
            break;
        }
        case AST::CF_P4G: {
            if (!tiled || tile.shx != 0.0 || tile.shy != 0.0 || tile.sx != tile.sy) {
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
            for (int i = 0; i < 4; ++i) {
                agg::trans_affine tr(reg);
                if (i) tr.rotate(i * M_PI * 0.5);
                tr.translate(centerx, centery);
                addUnique(syms, tr);
                agg::trans_affine tr2(reg);
                agg::trans_affine_reflection mirror(i * M_PI * 0.25);
                tr2 *= mirror;
                tr2.translate(tile.sx * 0.5 + centerx, tile.sy * 0.5 + centery);
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

void
CFDGImpl::getSymmetry(SymmList& syms, Renderer* r)
{
    syms.clear();
    const ASTexpression* e = hasParameter("CF::Symmetry");
    if (e == NULL) return;

    std::vector<double> symmSpec;
    yy::location where;
    bool tiled = isTiled();
    for (int i = 0; i < e->size(); ++i)
    {
        const ASTexpression* cit = (*e)[i];
        switch (cit->mType) {
            case ASTexpression::FlagType:
                processSymmSpec(syms, mTileMod.m_transform, tiled, symmSpec, where);
                where = cit->where;
            case ASTexpression::NumericType:
                if (symmSpec.empty() && cit->mType != ASTexpression::FlagType)
                    CfdgError::Error(cit->where, "Symmetry flag expected here");
                symmSpec.push_back(0.0);
                where = where + cit->where;
                if (cit->evaluate(&symmSpec.back(), 1, r) != 1)
                    CfdgError::Error(cit->where, "Could not evaluate this");
                break;
            case ASTexpression::ModType: {
                processSymmSpec(syms, mTileMod.m_transform, tiled, symmSpec, where);
                Modification mod;
                int dummy;
                cit->evaluate(mod, 0, 0, false, dummy, r);
                addUnique(syms, mod.m_transform);
                break;
            }
            default:
                CfdgError::Error(cit->where, "Wrong type");
                break;
        }
    }
    processSymmSpec(syms, mTileMod.m_transform, tiled, symmSpec, where);
}

bool
CFDGImpl::hasParameter(const char* name, double& value, Renderer* r) const
{
    string n = name;
    int varNum = tryEncodeShapeName(n);
    if (varNum < 0) return false;
    std::map<int, ConfigParam*>::const_iterator elem = m_ConfigParameters.find(varNum);
    if (elem == m_ConfigParameters.end() || 
        elem->second->second->mType != ASTexpression::NumericType) return false;
    if (!elem->second->second->isConstant && !r) {
        CfdgError::Error(elem->second->second->where, "This expression must be constant");
    } else {
        elem->second->second->evaluate(&value, 1, r);
    }
    return true;
}

bool
CFDGImpl::hasParameter(const char* name, Modification& value, Renderer* r) const
{
    string n = name;
    int varNum = tryEncodeShapeName(n);
    if (varNum < 0) return false;
    std::map<int, ConfigParam*>::const_iterator elem = m_ConfigParameters.find(varNum);
    if (elem == m_ConfigParameters.end() || 
        elem->second->second->mType != ASTexpression::ModType) return false;
    if (!elem->second->second->isConstant && !r) {
        CfdgError::Error(elem->second->second->where, "This expression must be constant");
    } else {
        elem->second->second->evaluate(value, 0, 0, false, varNum, r);
    }
    return true;
}

bool
CFDGImpl::hasParameter(const char* name, ASTexpression::expType t, yy::location& where) const
{
    string n = name;
    int varNum = tryEncodeShapeName(n);
    if (varNum < 0) return false;
    std::map<int, ConfigParam*>::const_iterator elem = m_ConfigParameters.find(varNum);
    if (elem == m_ConfigParameters.end() || 
        elem->second->second->mType != t) return false;
    where = elem->second->second->where;
    return true;
}

const ASTexpression*
CFDGImpl::hasParameter(const char* name) const
{
    string n = name;
    int varNum = tryEncodeShapeName(n);
    if (varNum < 0) return NULL;
    std::map<int, ConfigParam*>::const_iterator elem = m_ConfigParameters.find(varNum);
    if (elem == m_ConfigParameters.end()) return NULL;
    return elem->second->second;
}

static bool
stringcompare(const char *lhs, const char *rhs) {
    return std::strcmp(lhs, rhs) < 0;
}

bool
CFDGImpl::addParameter(std::string name, exp_ptr e, unsigned depth)
{
    static const char* const KnownParams[] = {
        "CF::AllowOverlap",
        "CF::Alpha",
        "CF::Background",
        "CF::BorderDynamic",
        "CF::BorderFixed",
        "CF::Color",
        "CF::ColorDepth",
        "CF::Frame",
        "CF::FrameTime",
        "CF::Impure",
        "CF::MinimumSize",
        "CF::Size",
        "CF::Symmetry",
        "CF::Tile",
        "CF::Time"
    };
    
    if (!std::binary_search(KnownParams, KnownParams + sizeof(KnownParams)/sizeof(KnownParams[0]), name.c_str(), stringcompare))
        return false;
    ASTmodification* m = dynamic_cast<ASTmodification*> (e.get());
    int varNum = encodeShapeName(name);
    std::map<int, ConfigParam*>::iterator elem = m_ConfigParameters.find(varNum);
    if (elem == m_ConfigParameters.end()) {
        m_ConfigParameters.insert(make_pair(varNum, new ConfigParam(depth, e.release()->simplify())));
    } else {
        if (depth < elem->second->first) {
            elem->second->first = depth;
            elem->second->second = e.release()->simplify();
        } else {
            return true;
        }

    }
    if (name == "CF::Background" && m)
        usesAlpha = m->flags & CF_USES_ALPHA;
    return true;
}

void
CFDGImpl::rulesLoaded()
{
    // thanks to by Brent Yorgey
    vector<double> weightsums( m_shapeTypes.size(), 0.0 );
    vector<double> percentweightsums( m_shapeTypes.size(), 0.0 );
    vector<double> unitweightsums( m_shapeTypes.size(), 0.0 );
    vector<int> rulecounts( m_shapeTypes.size(), 0 );
    vector<int> weightTypes( m_shapeTypes.size(), 0 );
    unsigned int i;

    // first pass: sum all the weights for each shape type
    for ( i = 0; i < mRules.size(); i++ ) {
        ASTrule* r = mRules[i];
        if (r->weightType == ASTrule::PercentWeight) {
            percentweightsums[ r->mNameIndex ] += r->mWeight;
            if (percentweightsums[ r->mNameIndex ] > 1.0001)
                CfdgError::Error(r->mLocation, "Percentages exceed 100%");
        } else {
            weightsums[ r->mNameIndex ] += r->mWeight;
        }
        rulecounts[ r->mNameIndex ]++;
        weightTypes[r->mNameIndex ] |= (int)(r->weightType);
    }

    // second pass: normalize each weight by dividing by the
    // total weight for that shape type
    for ( i = 0; i < mRules.size(); i++ ) {
        ASTrule* r = mRules[i];
        double weight = r->mWeight / weightsums[ r->mNameIndex ];   // may be infinity or NaN
        if (weightTypes[r->mNameIndex ] & (int)ASTrule::PercentWeight) {
            if (r->weightType == ASTrule::PercentWeight)
                weight = r->mWeight;
            else {
                weight *= 1.0 - percentweightsums[ r->mNameIndex ];
                if (percentweightsums[ r->mNameIndex ] > 0.9999)
                    CfdgError::Warning(r->mLocation, "Percentages sum to 100%, this rule has no weight");
            }
        }
        if (weightTypes[r->mNameIndex] == (int)ASTrule::PercentWeight &&
            fabs(percentweightsums[ r->mNameIndex ] - 1.0) > 0.0001)
        {
            CfdgError::Warning(r->mLocation, "Percentages do not sum to 100%");
        }
        if (!isfinite(weight)) weight = 0.0;
        unitweightsums[ r->mNameIndex ] += weight;
        if (--rulecounts[ r->mNameIndex ]) {
            r->mWeight = unitweightsums[ r->mNameIndex ];
        } else {
            // make sure that last rule of a type has a weightsum > 1.0
            r->mWeight = 1.1;
        }
    }
    
    // third pass: sort the rules by shape type, preserving the rule order
    // with respect to rules of the same shape type
    sort(mRules.begin(), mRules.end(), ASTrule::compareLT);
    
    // Wait until done and then update these members
    double value;
    uses16bitColor = hasParameter("CF::ColorDepth", value, NULL) && 
        floor(value) == 16.0;
    
    if (hasParameter("CF::Color", value, NULL))
        usesColor = value != 0.0;
    
    if (hasParameter("CF::Alpha", value, NULL))
        usesAlpha = value != 0.0;
}

int
CFDGImpl::numRules()
{
    return (int)mRules.size();
}

string
CFDGImpl::decodeShapeName(int shapetype)
{
    if (shapetype < int(m_shapeTypes.size()))
        return m_shapeTypes[shapetype].name;
    else
        return ("**unnamed shape**");
}

int
CFDGImpl::tryEncodeShapeName(const string& s) const
{
    for (unsigned int i = 0; i < m_shapeTypes.size(); i++) {
        if (s == m_shapeTypes[i].name) {
            return i;
        }
    }
    
    return -1;
}

int
CFDGImpl::encodeShapeName(const string& s)
{
    int i = tryEncodeShapeName(s);
    if (i >= 0) return i;

    m_shapeTypes.push_back(ShapeType(s));
    return (int)m_shapeTypes.size() - 1;
}

int
CFDGImpl::getShapeType(const string& s)
{
    for (unsigned int i = 0; i < m_shapeTypes.size(); i++) {
        if (s == m_shapeTypes[i].name) {
            return m_shapeTypes[i].shapeType;
        }
    }
    
    return newShape;
}

int
CFDGImpl::getShapeType(int shapetype)
{
    return m_shapeTypes[shapetype].shapeType;
}

bool
CFDGImpl::shapeHasRules(int shapetype)
{
    if (shapetype < int(m_shapeTypes.size()))
        return m_shapeTypes[shapetype].hasRules;
    else
        return false;
}

void
CFDGImpl::setShapeHasNoParams(int shapetype, const ASTexpression* args)
{
    if (shapetype < int(m_shapeTypes.size()) && args == NULL)
        m_shapeTypes[shapetype].shouldHaveNoParams = true;
}

bool
CFDGImpl::getShapeHasNoParams(int shapetype)
{
    if (shapetype < int(m_shapeTypes.size()))
        return m_shapeTypes[shapetype].shouldHaveNoParams;
    return false;
}

const char* 
CFDGImpl::setShapeParams(int shapetype, AST::ASTrepContainer& p, int argSize, bool isPath)
{
    if (m_secondPass)
        return 0;
    ShapeType& shape = m_shapeTypes[shapetype];
    if (shape.isShape) {
        // There has been a forward declaration, so this shape declaration
        // just introduces the shape elements
        if (!(p.mParameters.empty()))
            return  "Shape has already been declared. "
                    "Parameter declaration must be on the first shape declaration only.";
        if (shape.shapeType != newShape)
            return "Shape name already in use by another rule or path";
        if (isPath)
            return "Path name already in use by another rule or path";
        return 0;
    }
    if (shape.shapeType != newShape)
        return "Shape name already in use by another rule or path";
    
    shape.parameters = new AST::ASTparameters(p.mParameters);
    shape.isShape = true;
    shape.argSize = argSize;
    shape.shapeType = isPath ? pathType : newShape;
    return 0;
}

const AST::ASTparameters* 
CFDGImpl::getShapeParams(int shapetype)
{
    if (shapetype < 0 || shapetype >= int(m_shapeTypes.size()) ||
        !m_shapeTypes[shapetype].isShape)
        return 0;
    return m_shapeTypes[shapetype].parameters;
}

int 
CFDGImpl::getShapeParamSize(int shapetype)
{
    if (shapetype < 0 || shapetype >= int(m_shapeTypes.size()))
        return 0;
    return m_shapeTypes[shapetype].argSize;
}

int
CFDGImpl::reportStackDepth(int size) 
{
    if (size > mStackSize)
        mStackSize = size;
    return mStackSize;
}

void
CFDGImpl::resetCachedPaths()
{
    for (vector<AST::ASTrule*>::iterator it = mRules.begin(), eit = mRules.end();
         it != eit; ++it)
    {
        delete (*it)->mCachedPath;
        (*it)->mCachedPath = 0;
    }
}

AST::ASTdefine*
CFDGImpl::declareFunction(int nameIndex, AST::ASTdefine* def)
{
    AST::ASTdefine* prev = findFunction(nameIndex);
    if (prev)
        return prev;

    mFunctions[nameIndex] = def;
    return def;
    // I could write 
    // return findFunction(nameIndex) || (mFunctions[nameIndex] = def);
    // But I'm not gonna
}

AST::ASTdefine*
CFDGImpl::findFunction(int nameIndex)
{
    map<int,AST::ASTdefine*>::iterator fi = mFunctions.find(nameIndex);
    if (fi != mFunctions.end())
        return fi->second;
    return 0;
}

Renderer*
CFDGImpl::renderer(int width, int height, double minSize,
                    int variation, double border)
{
    if (mInitShape.get()) {
        if (mInitShape->mShapeSpec.argSize == 0 &&
            getShapeParamSize(mInitShape->mShapeSpec.shapeType))
        {
            CfdgError e(mInitShape->mLocation, "This shape takes parameters");
            m_system->syntaxError(e);
            return 0;
        }
    } else {
        m_system->message("No startshape found");
        m_system->error();
        return 0;
    }
    RendererImpl* r = NULL;
    try {
        r = new RendererImpl(this, width, height, minSize, variation, border);
        Modification tiled;
        Modification sized;
        Modification timed;
        if (hasParameter("CF::Tile", tiled, NULL)) {
            mTileMod = tiled;
            mTileOffset.x = mTileMod.m_transform.tx;
            mTileOffset.y = mTileMod.m_transform.ty;
            mTileMod.m_transform.tx = mTileMod.m_transform.ty = 0.0;
        }
        if (hasParameter("CF::Size", sized, NULL)) {
            mSizeMod = sized;
            mTileOffset.x = mSizeMod.m_transform.tx;
            mTileOffset.y = mSizeMod.m_transform.ty;
            mSizeMod.m_transform.tx = mSizeMod.m_transform.ty = 0.0;
        }
        if (hasParameter("CF::Time", timed, NULL)) {
            mTimeMod = timed;
        }
        r->initBounds();
    } catch (CfdgError e) {
        m_system->syntaxError(e);
        delete r;
        return 0;
    }
    return r;
}

