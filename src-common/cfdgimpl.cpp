// cfdgimpl.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006-2008 Mark Lentczner - markl@glyphic.com
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
: mCleanupLLP(this), m_backgroundColor(1, 1, 1, 1), mStackSize(0),
  mInitShape(nullptr), m_system(m), m_Parameters(0),
  ParamDepth({NoParameter}),
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

CFDGImpl::~CFDGImpl()
{
    // Release everything owned by the long-lived params
    for (auto&& param: mLongLivedParams) {
        for (auto it = param[0].begin(), e = param[0].end(); it != e; ++it) {
            if (it.type().mType == AST::RuleType)
                it->rule.~param_ptr();
        }
        if (Renderer::AbortEverything) return;
    }
#ifdef EXTREME_PARAM_DEBUG
    StackRule::ParamMap.clear();
    StackRule::ParamUID = 0;
#endif
}

const Shape&
CFDGImpl::getInitialShape(RendererAST* r)
{
    Shape init;
    init.mWorldState.m_Color = HSBColor(0.0, 0.0, 0.0, 1.0);
    init.mWorldState.m_ColorTarget = HSBColor(0.0, 0.0, 0.0, 1.0);
    init.mWorldState.m_time.tend = 1.0;
    mInitShape->replace(init, r);
    init.mWorldState.m_transform.tx += mTileOffset.x;
    init.mWorldState.m_transform.ty += mTileOffset.y;
    m_initialShape = std::move(init);
    return m_initialShape; 
}

const agg::rgba&
CFDGImpl::getBackgroundColor()
{
    return m_backgroundColor;
}

void
CFDGImpl::setBackgroundColor(RendererAST* r)
{
    Modification white;
    white.m_Color = HSBColor(0.0, 0.0, 1.0, 1.0);
    if (hasParameter(CFG::Background, white, r)) {
        white.m_Color.getRGBA(m_backgroundColor);
        if (!usesAlpha)
            m_backgroundColor.a = 1.0;
    }
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
    auto rule = std::find_if(mRules.begin(), mRules.end(),
                             [=](ASTrule* r){return r->mNameIndex == shapetype;});
    return rule == mRules.end() ? nullptr : *rule;
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
    if (!hasParameter(CFG::Tile, AST::ModType, loc)) return false;
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
    if (!hasParameter(CFG::Tile, AST::ModType, loc)) return no_frieze;
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
    if (!hasParameter(CFG::Size, AST::ModType, loc)) return false;
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
    if (!hasParameter(CFG::Time, AST::ModType, loc)) return false;
    if (t) *t = mTimeMod.m_time;
    if (mTimeMod.m_time.tbegin >= mTimeMod.m_time.tend)
        CfdgError::Error(loc, "Time specification must have positive duration.");
    return true;
}

void
CFDGImpl::getSymmetry(SymmList& syms, RendererAST* r)
{
    syms.clear();
    const ASTexpression* e = hasParameter(CFG::Symmetry);
    std::vector<const ASTmodification*> left = getTransforms(e, syms, r, isTiled(), mTileMod.m_transform);
    
    if (!left.empty()) {
        CfdgError(left.front()->where, "At least one term was invalid");
    }
}

bool
CFDGImpl::hasParameter(CFG name, double& value, RendererAST* r) const
{
    const ASTexpression* exp = hasParameter(name);
    if (!exp || exp->mType != AST::NumericType)
        return false;
    
    if (!exp->isConstant && !r) {
        CfdgError::Error(exp->where, "This expression must be constant");
        return false;
    } else {
        exp->evaluate(&value, 1, r);
    }
    return true;
}

bool
CFDGImpl::hasParameter(CFG name, Modification& value, RendererAST* r) const
{
    const ASTexpression* exp = hasParameter(name);
    if (!exp || exp->mType != AST::ModType)
        return false;
    
    if (!exp->isConstant && !r) {
        CfdgError::Error(exp->where, "This expression must be constant");
        return false;
    } else {
        exp->evaluate(value, true, r);
    }
    return true;
}

bool
CFDGImpl::hasParameter(CFG name, AST::expType t, yy::location& where) const
{
    const ASTexpression* exp = hasParameter(name);
    if (!exp || exp->mType != t)
        return false;

    where = exp->where;
    return true;
}

const ASTexpression*
CFDGImpl::hasParameter(CFG name) const
{
    assert(static_cast<size_t>(name) < static_cast<size_t>(CFG::_NumberOf));
    
    if (ParamDepth[name] == NoParameter)
        return nullptr;
    
    return ParamExp[name].get();
}

bool
CFDGImpl::addParameter(std::string name, exp_ptr e, unsigned depth)
{
    size_t varNum = 0;
    for (; varNum < ParamNames.size(); ++varNum)
        if (name == ParamNames[varNum])
            break;
    if (varNum >= ParamNames.size())
        return false;
    
    CFG var = static_cast<CFG>(varNum);

    if (depth < ParamDepth[var]) {
        ParamDepth[var] = depth;
        ParamExp[var] = std::move(e);
    }
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
        weightTypes[r->mNameIndex ] |= static_cast<int>(r->weightType);
    }

    // second pass: normalize each weight by dividing by the
    // total weight for that shape type
    for ( i = 0; i < mRules.size(); i++ ) {
        ASTrule* r = mRules[i];
        double weight = r->mWeight / weightsums[ r->mNameIndex ];   // may be infinity or NaN
        if (weightTypes[r->mNameIndex ] & static_cast<int>(ASTrule::PercentWeight)) {
            if (r->weightType == ASTrule::PercentWeight)
                weight = r->mWeight;
            else {
                weight *= 1.0 - percentweightsums[ r->mNameIndex ];
                if (percentweightsums[ r->mNameIndex ] > 0.9999)
                    CfdgError::Warning(r->mLocation, "Percentages sum to 100%, this rule has no weight");
            }
        }
        if (weightTypes[r->mNameIndex] == static_cast<int>(ASTrule::PercentWeight) &&
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
    
    Builder::CurrentBuilder->mLocalStackDepth = 0;
    mCFDGcontents.compile(CompilePhase::TypeCheck);
    if (!Builder::CurrentBuilder->mErrorOccured)
        mCFDGcontents.compile(CompilePhase::Simplify);
    
    // Wait until done and then update these members
    double value;
    uses16bitColor = hasParameter(CFG::ColorDepth, value, nullptr) &&
        floor(value) == 16.0;
    
    if (hasParameter(CFG::Color, value, nullptr))
        usesColor = value != 0.0;
    
    if (hasParameter(CFG::Alpha, value, nullptr))
        usesAlpha = value != 0.0;
    
    if (const ASTexpression* e = hasParameter(CFG::Background))
        if (const ASTmodification* m = dynamic_cast<const ASTmodification*>(e)) {
            usesAlpha = m->modData.m_Color.a != 1.0;
            for (auto& term: m->modExp)
                if (term->modType == ASTmodTerm::alpha || term->modType == ASTmodTerm::alphaTarg)
                    usesAlpha = true;
        }
}

int
CFDGImpl::numRules()
{
    return static_cast<int>(mRules.size());
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

    m_shapeTypes.emplace_back(s);
    return static_cast<int>(m_shapeTypes.size()) - 1;
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
    if (shapetype < int(m_shapeTypes.size()) && args == nullptr)
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
    ShapeType& shape = m_shapeTypes[shapetype];
    if (shape.isShape) {
        // There has been a forward declaration, so this shape declaration
        // just introduces the shape elements
        if (!(p.mParameters.empty()))
            return  "Shape has already been declared. "
                    "Parameter declaration must be on the first shape declaration only.";
        if (shape.shapeType == pathType && !isPath)
            return "Shape name already in use by another rule or path";
        if (isPath)
            return "Path name already in use by another rule or path";
        return nullptr;
    }
    if (shape.shapeType != newShape)
        return "Shape name already in use by another rule or path";
    
    shape.parameters.reset(new AST::ASTparameters(p.mParameters));
    shape.isShape = true;
    shape.argSize = argSize;
    shape.shapeType = isPath ? pathType : newShape;
    return nullptr;
}

const AST::ASTparameters* 
CFDGImpl::getShapeParams(int shapetype) const
{
    if (shapetype < 0 || shapetype >= int(m_shapeTypes.size()) ||
        !m_shapeTypes[shapetype].isShape)
        return nullptr;
    return m_shapeTypes[shapetype].parameters.get();
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
    for (ASTrule* rule: mRules)
        rule->mCachedPath.reset();
}

AST::ASTdefine*
CFDGImpl::declareFunction(int nameIndex, AST::ASTdefine* def)
{
    AST::ASTdefine* prev = findFunction(nameIndex);
    if (prev)
        return prev;

    mFunctions[nameIndex] = def;
    return def;
}

AST::ASTdefine*
CFDGImpl::findFunction(int nameIndex)
{
    auto fi = mFunctions.find(nameIndex);
    if (fi != mFunctions.end())
        return fi->second;
    return nullptr;
}

Renderer*
CFDGImpl::renderer(int width, int height, double minSize,
                    int variation, double border)
{
    ASTexpression* startExp = ParamExp[CFG::StartShape].get();
    
    if (!startExp) {
        m_system->message("No startshape found");
        m_system->error();
        return nullptr;
    }

    if (ASTstartSpecifier* startSpec = dynamic_cast<ASTstartSpecifier*>(startExp)) {
        ParamExp[CFG::StartShape].release();
        mInitShape.reset(new ASTreplacement(std::move(*startSpec), std::move(startSpec->mModification)));
        mInitShape->mChildChange.addEntropy(mInitShape->mShapeSpec.entropyVal);
    } else {
        CfdgError err(startExp->where, "Type error in startshape");
        m_system->error();
        m_system->syntaxError(err);
        return nullptr;
    }

    std::unique_ptr<RendererImpl> r;
    try {
        r.reset(new RendererImpl(this, width, height, minSize, variation, border));
        Modification tiled;
        Modification sized;
        Modification timed;
        double       maxShape;
        if (hasParameter(CFG::Tile, tiled, nullptr)) {
            mTileMod = tiled;
            mTileOffset.x = mTileMod.m_transform.tx;
            mTileOffset.y = mTileMod.m_transform.ty;
            mTileMod.m_transform.tx = mTileMod.m_transform.ty = 0.0;
        }
        if (hasParameter(CFG::Size, sized, nullptr)) {
            mSizeMod = sized;
            mTileOffset.x = mSizeMod.m_transform.tx;
            mTileOffset.y = mSizeMod.m_transform.ty;
            mSizeMod.m_transform.tx = mSizeMod.m_transform.ty = 0.0;
        }
        if (hasParameter(CFG::Time, timed, nullptr)) {
            mTimeMod = timed;
        }
        if (hasParameter(CFG::MaxShapes, maxShape, r.get())) {
            if (maxShape > 1)
                r->setMaxShapes(static_cast<int>(maxShape));
        }
        r->initBounds();
    } catch (CfdgError& e) {
        m_system->error();
        m_system->syntaxError(e);
        return nullptr;     // deletes this
    }
    return r.release();
}

