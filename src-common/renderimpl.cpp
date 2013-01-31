// renderimpl.cpp
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


#include "renderimpl.h"

#include <iterator>
#include <string>
#include <algorithm>
#include <stack>
#include <cassert>

#ifdef _WIN32
#include <float.h>
#include <math.h>
#define isfinite _finite
#else
#include <math.h>
#endif

#include "shapeSTL.h"
#include "primShape.h"
#include "builder.h"
#include "astreplacement.h"
#include "CmdInfo.h"
#include "tiledCanvas.h"

using namespace std;
using namespace AST;

//#define DEBUG_SIZES
#ifndef DEBUG_SIZES
#if defined(_WIN64) || defined(__x86_64__)
const unsigned int MOVE_FINISHED_AT     = 10000000; // when this many, move to file
const unsigned int MOVE_UNFINISHED_AT   = 10000000; // when this many, move to files
#else
const unsigned int MOVE_FINISHED_AT     =  2000000; // when this many, move to file
const unsigned int MOVE_UNFINISHED_AT   =  2000000; // when this many, move to files
#endif
const unsigned int MAX_MERGE_FILES      =      200; // maximum number of files to merge at once
#else
const unsigned int MOVE_FINISHED_AT     =    1000; // when this many, move to file
const unsigned int MOVE_UNFINISHED_AT   =     200; // when this many, move to files
const unsigned int MAX_MERGE_FILES      =       2; // maximum number of files to merge at once
#endif
const double SHAPE_BORDER = 1.0; // multiplier of shape size when calculating bounding box
const double FIXED_BORDER = 8.0; // fixed extra border, in pixels



RendererImpl::RendererImpl(CFDGImpl* cfdg,
                            int width, int height, double minSize,
                            int variation, double border)
    : m_cfdg(cfdg), mVariation(variation), m_border(border), m_minSize(minSize),
      shape0(*primShape::shapeMap[0]), 
      shape1(*primShape::shapeMap[1]),
      shape2(*primShape::shapeMap[2])
{
    m_width = width;
    m_height = height;
    mCFstack.reserve(8000);
    mFrameTimeBounds.load_from(1.0, -Renderer::Infinity, Renderer::Infinity);

    m_canvas = 0;
    mColorConflict = false;
    m_maxShapes = 500000000;
    m_currScale = m_currArea = 0.0;
    mScaleArea = mScale = 0.0;
    shapeMap[0].mFlags = shapeMap[1].mFlags = shapeMap[2].mFlags = 
        CF_MITER_JOIN + CF_BUTT_CAP + CF_FILL;
    shapeMap[0].mPathUID = shapeMap[1].mPathUID = shapeMap[2].mPathUID = 0;
    shapeMap[0].mPath = &shape0;
    shapeMap[1].mPath = &shape1;
    shapeMap[2].mPath = &shape2;
    
    m_cfdg->hasParameter("CF::FrameTime", mCurrentTime, 0);
    m_cfdg->hasParameter("CF::Frame", mCurrentFrame, 0);
}

void
RendererImpl::colorConflict(const yy::location& w)
{
    if (mColorConflict) return;
    CfdgError err(w, "Conflicting color change");
    system()->syntaxError(err);
    mColorConflict = true;
}

void
RendererImpl::init()
{
    mCurrentSeed.seed((unsigned long long)mVariation);
    mCurrentSeed.bump();
    
    mFinishedFileCount = 0;
    mUnfinishedFileCount = 0;
    
    mFixedBorderX = mFixedBorderY = 0.0;
    mShapeBorder = 1.0;
    mTotalArea = 0.0;
    
    m_minArea = 0.3; 
    m_outputSoFar = m_stats.shapeCount = m_stats.toDoCount = 0;
    double minSize = m_minSize;
    m_cfdg->hasParameter("CF::MinimumSize", minSize, this);
    minSize = (minSize <= 0.0) ? 0.3 : minSize;
    m_minArea = minSize * minSize;

    mFixedBorderX = FIXED_BORDER * ((m_border <= 1.0) ? m_border : 1.0);
    mShapeBorder = SHAPE_BORDER * ((m_border <= 1.0) ? 1.0 : m_border);
    
    m_cfdg->hasParameter("CF::BorderFixed", mFixedBorderX, this);
    m_cfdg->hasParameter("CF::BorderDynamic", mShapeBorder, this);
    if (2 * (int)fabs(mFixedBorderX) >= min(m_width, m_height))
        mFixedBorderX = 0.0;
    if (mShapeBorder <= 0.0)
        mShapeBorder = 1.0;
    
    if (m_cfdg->hasParameter("CF::MaxNatural", mMaxNatural, this) &&
        (mMaxNatural < 1.0 || (mMaxNatural - 1.0) == mMaxNatural))
    {
        const ASTexpression* max = m_cfdg->hasParameter("CF::MaxNatural");
        throw CfdgError(max->where, (mMaxNatural < 1.0) ?
                            "CF::MaxNatural must be >= 1" :
                            "CF::MaxNatural must be < 9007199254740992");
    }
    
    mCurrentPath = new AST::ASTcompiledPath();
    
    m_cfdg->getSymmetry(mSymmetryOps, this);
    m_cfdg->getBackgroundColor(this);
}

void
RendererImpl::initBounds()
{
    init();
    double tile_x, tile_y;
    m_tiled = m_cfdg->isTiled(0, &tile_x, &tile_y);
    m_frieze = m_cfdg->isFrieze(0, &tile_x, &tile_y);
    m_sized = m_cfdg->isSized(&tile_x, &tile_y);
    m_timed = m_cfdg->isTimed(&mTimeBounds);
    
    if (m_tiled || m_sized) {
        mFixedBorderX = mShapeBorder = 0.0;
        mBounds.mMin_X = -(mBounds.mMax_X = tile_x / 2.0);
        mBounds.mMin_Y = -(mBounds.mMax_Y = tile_y / 2.0);
        mBounds.mValid = true;
        rescaleOutput(m_width, m_height, true);
        mScaleArea = m_currArea;
    }
    if (m_frieze == CFDG::frieze_x)
        m_frieze_size = tile_x / 2.0;
    if (m_frieze == CFDG::frieze_y)
        m_frieze_size = tile_y / 2.0;
    if (m_frieze != CFDG::frieze_y)
        mFixedBorderY = mFixedBorderX;
    if (m_frieze == CFDG::frieze_x)
        mFixedBorderX = 0.0;
}

void
RendererImpl::resetSize(int x, int y)
{
    m_width = x;
    m_height = y;
    if (m_tiled || m_sized) {
        m_currScale = m_currArea = 0.0;
        rescaleOutput(m_width, m_height, true);
        mScaleArea = m_currArea;
    }
}

class Stopped { };
    
static void releaser(const Shape& s)
{
    if (Renderer::AbortEverything)
        throw Stopped();
    s.releaseParams();
}

RendererImpl::~RendererImpl()
{
    cleanup();
    delete m_cfdg;
}

void
RendererImpl::cleanup()
{
    // delete temp files before checking for abort
    m_finishedFiles.clear();
    m_unfinishedFiles.clear();

    try {
        for_each(mUnfinishedShapes.begin(), mUnfinishedShapes.end(), releaser);
        for_each(mFinishedShapes.begin(), mFinishedShapes.end(), releaser);
    } catch (Stopped) {
        return;
    }
    for (std::deque<const StackType*>::const_iterator cit = mLongLivedParams.begin();
         cit != mLongLivedParams.end(); ++cit)
    {
        --Renderer::ParamCount;
        delete[] *cit;
        if (AbortEverything) return;
    }
    mUnfinishedShapes.clear();
    mFinishedShapes.clear();
    mLongLivedParams.clear();
    
    unsigned i = 0;
    for (ASTbody::const_iterator cit = m_cfdg->mCFDGcontents.mBody.begin(),
         endit = m_cfdg->mCFDGcontents.mBody.end(); cit != endit; ++cit)
    {
        if (AbortEverything) return;
        const ASTreplacement* rep = cit->get();
        if (const ASTdefine* def = dynamic_cast<const ASTdefine*> (rep)) {
            if (def->mType == AST::RuleType)
                mCFstack[i].rule->release();
            i += def->mTuplesize;
        }
    }
    mCFstack.clear();
    
    delete mCurrentPath; mCurrentPath = 0;
    m_cfdg->resetCachedPaths();
}

void
RendererImpl::setMaxShapes(int n)
{
    m_maxShapes = n ? n : 400000000;
}

void
RendererImpl::resetBounds()
{
    mBounds = Bounds();
}


void
RendererImpl::outputPrep(Canvas* canvas)
{
    m_canvas = canvas;

    if (canvas) {
        m_width = canvas->mWidth;
        m_height = canvas->mHeight;
        if (m_tiled || m_frieze) {
            agg::trans_affine tr;
            m_cfdg->isTiled(&tr);
            m_cfdg->isFrieze(&tr);
            delete m_tiledCanvas;
            m_tiledCanvas = new tiledCanvas(canvas, tr, m_frieze);
            m_tiledCanvas->scale(m_currScale);
            m_canvas = m_tiledCanvas;
        }

        mFrameTimeBounds.load_from(1.0, -Renderer::Infinity, Renderer::Infinity);
    }
    
    requestStop = false;
    requestFinishUp = false;
    requestUpdate = false;
    
    m_stats.inOutput = false;
    m_stats.animating = false;
    m_stats.finalOutput = false;
}


double
RendererImpl::run(Canvas * canvas, bool partialDraw)
{
    if (!m_stats.animating)
        outputPrep(canvas);
    
    int reportAt = 250;

    Shape dummy;
    for (ASTbody::const_iterator cit = m_cfdg->mCFDGcontents.mBody.begin(),
         endit = m_cfdg->mCFDGcontents.mBody.end(); cit != endit; ++cit)
    {
        const ASTreplacement* rep = cit->get();
        if (const ASTdefine* def = dynamic_cast<const ASTdefine*> (rep))
            def->traverse(dummy, false, this);
    }
    
    Shape initShape = m_cfdg->getInitialShape(this);
    initShape.mWorldState.mRand64Seed = mCurrentSeed;
    if (!m_timed)
        mTimeBounds = initShape.mWorldState.m_time;
    
    try {
        processShape(initShape);
    } catch (CfdgError e) {
        requestStop = true;
        system()->syntaxError(e);
    }
    
    for (;;) {
        fileIfNecessary();
        
        if (requestStop) break;
        if (requestFinishUp) break;
        
        if (mUnfinishedShapes.empty()) break;
        if ((m_stats.shapeCount + m_stats.toDoCount) > m_maxShapes)
            break;

        // Get the largest unfinished shape
        Shape s = mUnfinishedShapes.front();
        pop_heap(mUnfinishedShapes.begin(), mUnfinishedShapes.end());
        mUnfinishedShapes.pop_back();
        m_stats.toDoCount--;
        
        const ASTrule* rule = m_cfdg->findRule(s.mShapeType, s.mWorldState.mRand64Seed.getDouble());
        
        try {
            m_drawingMode = false;      // shouldn't matter
            rule->traverse(s, false, this);
        } catch (CfdgError e) {
            requestStop = true;
            system()->syntaxError(e);
            break;
        }
        
        if (requestUpdate || (m_stats.shapeCount > reportAt)) {
            if (partialDraw)
              outputPartial();
            outputStats();
            reportAt = 2 * m_stats.shapeCount;
        }
    }
    
    if (!m_cfdg->usesTime && !m_timed) 
        mTimeBounds.load_from(1.0, 0.0, mTotalArea);
    
    if (!requestStop) {
        outputFinal();
    }
    
    if (!requestStop) {
        outputStats();
    }
    
    if (!m_canvas && m_frieze)
        rescaleOutput(m_width, m_height, true);

    return m_currScale;
}

void
RendererImpl::draw(Canvas* canvas)
{
    mFrameTimeBounds.load_from(1.0, -Renderer::Infinity, Renderer::Infinity);
    outputPrep(canvas);
    outputFinal();
    outputStats();
}

class OutputBounds : public ShapeOp
{
public:
    OutputBounds(int frames, const agg::trans_affine_time& timeBounds, 
                 double shapeBorder, int width, int height, double fixedBorderX,
                 double fixedBorderY, RendererImpl& renderer);
    void apply(const FinishedShape&);

    const Bounds& frameBounds(int frame) { return mFrameBounds[frame]; }
    int           frameCount(int frame) { return mFrameCounts[frame]; }
    
    void finalAccumulate();
    // call after all the frames to compute the bounds at each frame
    
    void backwardFilter(double framesToHalf);
    void smooth(int window);
    class Stopped { }; 
    
private:
    agg::trans_affine_time mTimeBounds;
    double          mFrameScale;
    double          mShapeBorder;
    vector<Bounds>  mFrameBounds;
    vector<int>     mFrameCounts;
    double          mScale;
    int             mWidth;
    int             mHeight;
    int             mFrames;
    double          mFixedBorderX;
    double          mFixedBorderY;
    RendererImpl&   mRenderer;
};

OutputBounds::OutputBounds(int frames, const agg::trans_affine_time& timeBounds, 
                           double shapeBorder, int width, int height, double fixedBorderX,
                           double fixedBorderY, RendererImpl& renderer)
: mTimeBounds(timeBounds), mShapeBorder(shapeBorder), mScale(0.0),
  mWidth(width), mHeight(height), mFrames(frames), mFixedBorderX(fixedBorderX),
  mFixedBorderY(fixedBorderY), mRenderer(renderer)
{
    mFrameScale = (double)frames / (timeBounds.tend - timeBounds.tbegin);
    mFrameBounds.resize(frames);
    mFrameCounts.resize(frames, 0);
}

void
OutputBounds::apply(const FinishedShape& s)
{
    if (mRenderer.requestStop ||  mRenderer.requestFinishUp) throw Stopped();
    
    if (mScale == 0.0) {
        // If we don't know the approximate scale yet then just
        // make an educated guess.
        mScale = (mWidth + mHeight) / sqrt(fabs(s.mWorldState.m_transform.determinant()));
    }
    
    agg::trans_affine_time frameTime(s.mWorldState.m_time);
    frameTime.translate(-mTimeBounds.tbegin);
    frameTime.scale(mFrameScale);
    int begin = (frameTime.tbegin < mFrames) ? (int)floor(frameTime.tbegin) : (mFrames - 1);
    int end = (frameTime.tend < mFrames) ? (int)floor(frameTime.tend) : (mFrames - 1);
    if (begin < 0) begin = 0;
    if (end < 0) end = 0;
    for (int frame = begin; frame <= end; ++frame) {
        mFrameBounds[frame] += s.mBounds;
    }
    mFrameCounts[begin] += 1;
}

void
OutputBounds::finalAccumulate()
{
    return;
    // Accumulation is done in the apply method
#if 0
    vector<Bounds>::iterator prev, curr, end;
    prev = mFrameBounds.begin();
    end = mFrameBounds.end();
    if (prev == end) return;

    for (curr = prev + 1; curr != end; prev = curr, ++curr) {
        *curr += *prev;
    }
#endif
}

void
OutputBounds::backwardFilter(double framesToHalf)
{
    double alpha = pow(0.5, 1.0 / framesToHalf);
    
    vector<Bounds>::reverse_iterator prev, curr, end;
    prev = mFrameBounds.rbegin();
    end = mFrameBounds.rend();
    if (prev == end) return;
    
    for (curr = prev + 1; curr != end; prev = curr, ++curr) {
        *curr = curr->interpolate(*prev, alpha);
    }
} 

void
OutputBounds::smooth(int window)
{
    int frames = (int)mFrameBounds.size();
    if (frames == 0) return;
    
    mFrameBounds.resize(frames + window - 1, mFrameBounds.back());
    
    vector<Bounds>::iterator write, read, end;
    read = mFrameBounds.begin();
    
    double factor = 1.0 / window;
    
    Bounds accum;
    for (int i = 0; i < window; ++i)
        accum.gather(*read++, factor);
    
    write = mFrameBounds.begin();
    end = mFrameBounds.end();
    for (;;) {
        Bounds old = *write;
        *write++ = accum;
        accum.gather(old, -factor);
        
        if (read == end) break;
        
        accum.gather(*read++, factor);
    } 
    
    mFrameBounds.resize(frames, Bounds());
}


void
RendererImpl::animate(Canvas* canvas, int frames, bool zoom)
{
    outputPrep(canvas);
    
    const bool ftime = m_cfdg->usesFrameTime;
    zoom = zoom && !ftime;
    if (ftime)
        cleanup();

    // start with a blank frame
    
    int curr_width = m_width;
    int curr_height = m_height;
    rescaleOutput(curr_width, curr_height, true);
    
    m_canvas->start(true, m_cfdg->getBackgroundColor(0),
        curr_width, curr_height);
    m_canvas->end();

    double frameInc = (mTimeBounds.tend - mTimeBounds.tbegin) / frames;
    
    OutputBounds outputBounds(frames, mTimeBounds, mShapeBorder, 
                              curr_width, curr_height, mFixedBorderX, mFixedBorderY, 
                              *this);
    if (zoom) {
        system()->message("Computing zoom");

        try {
            forEachShape(true, outputBounds);
            //outputBounds.finalAccumulate();
            outputBounds.backwardFilter(10.0);
            //outputBounds.smooth(3);
        } catch (OutputBounds::Stopped) {
            m_stats.animating = false;
            return;
        }
    }

    m_stats.shapeCount = 0;
    m_stats.animating = true;
    mFrameTimeBounds.tend = mTimeBounds.tbegin;
    
    Bounds saveBounds = mBounds;

    for (int frameCount = 1; frameCount <= frames; ++frameCount)
    {
        system()->message("Generating frame %d of %d", frameCount, frames);
        
        if (zoom) mBounds = outputBounds.frameBounds(frameCount - 1);
        m_stats.shapeCount += outputBounds.frameCount(frameCount - 1);
        mFrameTimeBounds.tbegin = mFrameTimeBounds.tend;
        mFrameTimeBounds.tend = mTimeBounds.tbegin + frameInc * frameCount;
        
        if (ftime) {
            mCurrentTime = (mFrameTimeBounds.tbegin + mFrameTimeBounds.tend) * 0.5;
            mCurrentFrame = (frameCount - 1.0)/(frames - 1.0);
            try {
                init();
            } catch (CfdgError err) {
                system()->syntaxError(err);
                cleanup();
                mBounds = saveBounds;
                m_stats.animating = false;
                outputStats();
                return;
            }
            run(canvas, false);
            m_canvas = canvas;
        } else {
            outputFinal();
            outputStats();
        }
        
        if (ftime)
            cleanup();

        if (requestStop || requestFinishUp) break;
    }

    mBounds = saveBounds;
    m_stats.animating = false;
    outputStats();
    system()->message("Animation of %d frames complete", frames);
}

void
RendererImpl::processShape(const Shape& s)
{
    double area = s.area();
    if (!isfinite(area)) {
        requestStop = true;
        system()->error();
        system()->message("A shape got too big.");
        s.releaseParams();
        return;
    }
    
    if (s.mWorldState.m_time.tbegin > s.mWorldState.m_time.tend) {
        s.releaseParams();
        return;
    }
    
    if (m_cfdg->getShapeType(s.mShapeType) == CFDGImpl::ruleType &&
        m_cfdg->shapeHasRules(s.mShapeType)) 
    {
        // only add it if it's big enough (or if there are no finished shapes yet)
        if (!mBounds.valid() || (area * mScaleArea >= m_minArea)) {
            m_stats.toDoCount++;
            mUnfinishedShapes.push_back(s);
            push_heap(mUnfinishedShapes.begin(), mUnfinishedShapes.end());
        } else {
            s.releaseParams();
        }
    } else if (m_cfdg->getShapeType(s.mShapeType) == CFDGImpl::pathType) {
        const ASTrule* rule = m_cfdg->findRule(s.mShapeType, 0.0);
        processPrimShape(s, rule);
    } else if (primShape::isPrimShape(s.mShapeType)) {
        processPrimShape(s);
    } else {
        requestStop = true;
        s.releaseParams();
        system()->error();
        system()->message("Shape with no rules encountered: %s.", 
            m_cfdg->decodeShapeName(s.mShapeType).c_str());
    }
}

void
RendererImpl::processPrimShape(const Shape& s, const ASTrule* path)
{
    int num = (int)mSymmetryOps.size();
    if (num == 0 || s.mShapeType == primShape::fillType) {
        processPrimShapeSiblings(s, path);
    } else {
        for (int i = 0; i < num; ++i) {
            Shape sym(s);
            sym.mWorldState.m_transform.multiply(mSymmetryOps[i]);
            processPrimShapeSiblings(sym, path);
        }
    }
    s.releaseParams();
}

void
RendererImpl::processPrimShapeSiblings(const Shape& s, const ASTrule* path)
{
    m_stats.shapeCount++;
    if (mScale == 0.0) {
        // If we don't know the approximate scale yet then just
        // make an educated guess.
        mScale = (m_width + m_height) / sqrt(fabs(s.mWorldState.m_transform.determinant()));
    }
    double oldArea = mTotalArea;
    if (path || s.mShapeType != primShape::fillType) {
        mCurrentCentroid.x = mCurrentCentroid.y = mCurrentArea = 0.0;
        mPathBounds.mValid = false;
        m_drawingMode = false;
        if (path) {
            path->traversePath(s, this);
        } else {
            CommandInfo* attr = 0;
            if (s.mShapeType < 3) attr = &(shapeMap[s.mShapeType]);
            processPathCommand(s, attr);
        }
        mTotalArea += mCurrentArea;
        if (!m_tiled && !m_sized) {
            mBounds.merge(mPathBounds.dilate(mShapeBorder));
            if (m_frieze == CFDG::frieze_x)
                mBounds.mMin_X = -(mBounds.mMax_X = m_frieze_size);
            if (m_frieze == CFDG::frieze_y)
                mBounds.mMin_Y = -(mBounds.mMax_Y = m_frieze_size);
            mScale = mBounds.computeScale(m_width, m_height, 
                                          mFixedBorderX, mFixedBorderY, false);
            mScaleArea = mScale * mScale;
        }
    } else {
        mCurrentArea = Renderer::Infinity;
    }
    if (oldArea == mTotalArea)
#ifdef _WIN32
        mTotalArea = _nextafter(mTotalArea, DBL_MAX);
#else
        mTotalArea = nextafter(mTotalArea, DBL_MAX);
#endif
    FinishedShape fs(s, mTotalArea, mPathBounds);
    fs.mWorldState.m_ColorTarget.a = mCurrentArea;
    if (!m_cfdg->usesTime) {
        fs.mWorldState.m_time.tbegin = mTotalArea;
        fs.mWorldState.m_time.tend = Renderer::Infinity;
    }
    if (fs.mWorldState.m_time.tbegin < mTimeBounds.tbegin &&
        isfinite(fs.mWorldState.m_time.tbegin) && !m_timed)
    {
        mTimeBounds.tbegin = fs.mWorldState.m_time.tbegin;
    }
    if (fs.mWorldState.m_time.tbegin > mTimeBounds.tend &&
        isfinite(fs.mWorldState.m_time.tbegin) && !m_timed)
    {
        mTimeBounds.tend = fs.mWorldState.m_time.tbegin;
    }
    if (fs.mWorldState.m_time.tend > mTimeBounds.tend &&
        isfinite(fs.mWorldState.m_time.tend) && !m_timed)
    {
        mTimeBounds.tend = fs.mWorldState.m_time.tend;
    }
    if (fs.mWorldState.m_time.tend < mTimeBounds.tbegin &&
        isfinite(fs.mWorldState.m_time.tend) && !m_timed)
    {
        mTimeBounds.tbegin = fs.mWorldState.m_time.tend;
    }
    if (!fs.mWorldState.isFinite()) {
        requestStop = true;
        system()->error();
        system()->message("A shape got too big.");
        return;
    }
    mFinishedShapes.insert(fs);
    if (fs.mParameters)
        fs.mParameters->retain(this);
}

void
RendererImpl::processSubpath(const Shape& s, bool tr, int expectedType)
{
    const ASTrule* rule = 0;
    if (m_cfdg->getShapeType(s.mShapeType) != CFDGImpl::pathType && 
        primShape::isPrimShape(s.mShapeType) && expectedType == ASTreplacement::op)
    {
        rule = ASTrule::PrimitivePaths[s.mShapeType];
    } else {
        rule = m_cfdg->findRule(s.mShapeType, 0.0);
    }
    if ((int)(rule->mRuleBody.mRepType) != expectedType)
        throw CfdgError(rule->mLocation, "Subpath is not of the expected type (path ops/commands)");
    rule->mRuleBody.traverse(s, tr, this, true);
}


//-------------------------------------------------------------------------////


void
RendererImpl::fileIfNecessary()
{
    if (mFinishedShapes.size() > MOVE_FINISHED_AT)
        moveFinishedToFile();

    if (mUnfinishedShapes.size() > MOVE_UNFINISHED_AT) 
        moveUnfinishedToTwoFiles();
    else if (mUnfinishedShapes.empty())
        getUnfinishedFromFile();
}

void
RendererImpl::moveUnfinishedToTwoFiles()
{
    ref_ptr<TempFile> t1 = TempFile::build(system(), "cfdg-temp-unfin-",
                                            "expansion", ++mUnfinishedFileCount);
    ref_ptr<TempFile> t2 = TempFile::build(system(), "cfdg-temp-unfin-",
                                            "expansion", ++mUnfinishedFileCount);

    m_unfinishedFiles.push_back(t1);
    m_unfinishedFiles.push_back(t2);

    unique_ptr<ostream> f1(t1->forWrite());
    unique_ptr<ostream> f2(t2->forWrite());
    
    system()->message("Writing %s temp files %d & %d",
                        t1->type().c_str(), t1->number(), t2->number());

    int count = (int)mUnfinishedShapes.size() / 3;

    UnfinishedContainer::iterator usi = mUnfinishedShapes.begin(),
                                  use = mUnfinishedShapes.end();
    usi += count;
    
	if (f1->good() && f2->good()) {
        AbstractSystem::Stats outStats = m_stats;
        outStats.outputCount = count;
        outStats.outputDone = 0;
        *f1 << outStats.outputCount;
        *f2 << outStats.outputCount;
        outStats.outputCount = count * 2;
        outStats.showProgress = true;
		// Split the bottom 2/3 of the heap between the two files
		while (usi != use) {
			usi->write(*((m_unfinishedInFilesCount & 1) ? f1 : f2));
			++usi;
			++m_unfinishedInFilesCount;
            ++outStats.outputDone;
            if (requestUpdate) {
                system()->stats(outStats);
                requestUpdate = false;
            }
            if (requestStop || requestFinishUp)
                return;
		}
	} else {
		system()->message("Cannot open temporary file for expansions");
        requestStop = true;
        return;
	}

    // Remove the written shapes, heap property remains intact
    static const Shape neverActuallyUsed;
    mUnfinishedShapes.resize(count, neverActuallyUsed);
    assert(checkHeap());
}

void
RendererImpl::getUnfinishedFromFile()
{
    if (m_unfinishedFiles.empty()) return;
    
    ref_ptr<TempFile> t = m_unfinishedFiles.front();
    
    unique_ptr<istream> f(t->forRead());

    if (f->good()) {
        AbstractSystem::Stats outStats = m_stats;
        *f >> outStats.outputCount;
        outStats.outputDone = 0;
        outStats.showProgress = true;
        istream_iterator<Shape> it(*f);
        istream_iterator<Shape> eit;
        back_insert_iterator< UnfinishedContainer > sendto(mUnfinishedShapes);
        while (it != eit) {
            *sendto = *it;
            ++it;
            ++outStats.outputDone;
            if (requestUpdate) {
                system()->stats(outStats);
                requestUpdate = false;
            }
            if (requestStop || requestFinishUp)
                return;
        }
	} else {
		system()->message("Cannot open temporary file for expansions");
        requestStop = true;
        return;
    }
    system()->message("Resorting expansions");
    fixupHeap();

    m_unfinishedFiles.pop_front();
}

bool
RendererImpl::checkHeap()
{
    // Confirm that mUnfinishedShapes still has the heap property
    size_t parent = 0;
    size_t num = mUnfinishedShapes.size();
    for (size_t child = 1; child < num; ++child) {
        if (mUnfinishedShapes[parent] < mUnfinishedShapes[child])
            return false;
        if ((child & 1) == 0)
            ++parent;
	}
    return true;
}

void
RendererImpl::fixupHeap()
{
    // Restore heap property to mUnfinishedShapes
    size_t size = mUnfinishedShapes.size();
    if (size < 2) return;
    // Add a dummy entry to the end to guarantee that all nodes have two children
    Shape s;
    s.mAreaCache = DBL_MIN;
    s.mShapeType = -1;
    mUnfinishedShapes.push_back(s);
    size_t top = (size - 1) / 2;
    AbstractSystem::Stats outStats = m_stats;
    outStats.outputCount = (int)top;
    outStats.outputDone = 0;
    outStats.showProgress = true;
    for (;;--top) {
        s = mUnfinishedShapes[top];
        size_t child = top * 2;
        size_t hole = top;
        // Bubble up children until we find a place for the current node
        while (s < mUnfinishedShapes[child] || s < mUnfinishedShapes[child + 1])
        {
            // Bubble up the largest child
            if (mUnfinishedShapes[child] < mUnfinishedShapes[child + 1])
                ++child;
            mUnfinishedShapes[hole] = mUnfinishedShapes[child];
            hole = child;
            if (child * 2 >= size) break;
            child = child * 2;
        }
        // Copy down the node only if at least one child bubbled up
        if (hole > top)
            mUnfinishedShapes[hole] = s;
        if (top == 0)
            break;
        ++outStats.outputDone;
        if (requestUpdate) {
            system()->stats(outStats);
            requestUpdate = false;
        }
        if (requestStop || requestFinishUp)
            return;
    }
    // Dummy entry should still be at end, remove it
    assert(mUnfinishedShapes.back().mAreaCache == DBL_MIN);
    assert(mUnfinishedShapes.back().mShapeType == -1);
    mUnfinishedShapes.pop_back();
    assert(checkHeap());
}

//-------------------------------------------------------------------------////

void
RendererImpl::moveFinishedToFile()
{
    ref_ptr<TempFile> t = TempFile::build(system(), "cfdg-temp-fin-",
                                            "shapes", ++mFinishedFileCount);
    m_finishedFiles.push_back(t);
    
    unique_ptr<ostream> f(t->forWrite());

	if (f->good()) {
        AbstractSystem::Stats outStats = m_stats;
        outStats.outputCount = (int)mFinishedShapes.size();
        outStats.outputDone = 0;
        outStats.showProgress = true;
        for (multiset<FinishedShape>::iterator it = mFinishedShapes.begin(),
             eit = mFinishedShapes.end(); it != eit; ++it)
        {
            *f << *it;
            ++outStats.outputDone;
            if (requestUpdate) {
                system()->stats(outStats);
                requestUpdate = false;
            }
            if (requestStop)
                return;
        }
	} else {
		system()->message("Cannot open temporary file for shapes");
        requestStop = true;
        return;
	}

    mFinishedShapes.clear();
}

//-------------------------------------------------------------------------////

void RendererImpl::rescaleOutput(int& curr_width, int& curr_height, bool final)
{
    agg::trans_affine trans;
    double scale;
    
    if (!mBounds.mValid) return;

    scale = mBounds.computeScale(curr_width, curr_height,
                                 mFixedBorderX, mFixedBorderY, true, 
                                 &trans, m_tiled || m_sized || m_frieze);

    if (final                       // if final output
    || m_currScale == 0.0           // if first time, use this scale
    || (m_currScale * 0.90) > scale)// if grew by more than 10%
    {
        m_currScale = scale;
        m_currArea = scale * scale;
        if (m_tiledCanvas)
            m_tiledCanvas->scale(scale);
        m_currTrans = trans;
        m_outputSoFar = 0;
        m_stats.fullOutput = true;
    }
}


void
RendererImpl::forEachShape(bool final, ShapeOp& op)
{
    if (!final) {
        if (m_outputSoFar)
            m_outputPosition = ++m_outputPosition;
        else
            m_outputPosition = mFinishedShapes.begin();
        for_each(m_outputPosition, mFinishedShapes.end(), op.outputFunction());
        m_outputSoFar = (int)mFinishedShapes.size();
        if (m_outputSoFar)
            m_outputPosition = --(mFinishedShapes.end());
    } else if (m_finishedFiles.empty()) {
        for_each(mFinishedShapes.begin(), mFinishedShapes.end(),
                 op.outputFunction());
    } else {
        deque< ref_ptr<TempFile> >::iterator begin, last, end;
        
        while (m_finishedFiles.size() > MAX_MERGE_FILES) {
            OutputMerge merger(*system());
            
            begin = m_finishedFiles.begin();
            last = begin + (MAX_MERGE_FILES - 1);
            end = last + 1;
            
            for_each(begin, end, merger.tempFileAdder());
            
            ref_ptr<TempFile> t = TempFile::build(system(), "cfdg-temp-mrg-",
                                                  "merge", ++mFinishedFileCount);
            
            ostream* f = t->forWrite();
            system()->message("Merging temp files %d through %d",
            (*begin)->number(), (*last)->number());
            
            merger.merge(ostream_iterator<FinishedShape>(*f));
            
            delete f;
            
            m_finishedFiles.erase(begin, end);
            m_finishedFiles.push_back(t);
        }
        
        OutputMerge merger(*system());
        
        begin = m_finishedFiles.begin();
        end = m_finishedFiles.end();
        
        for_each(begin, end, merger.tempFileAdder());
        
        merger.addShapes(mFinishedShapes.begin(), mFinishedShapes.end());
        merger.merge(op.outputIterator());
    }
}


class OutputDraw : public ShapeOp
{
public:
    OutputDraw(RendererImpl& renderer, bool final);
    
    void apply(const FinishedShape&);

    class Stopped { }; 

private:
    RendererImpl& mRenderer;
    bool mFinal;
    tiledCanvas* tiler;
};

OutputDraw::OutputDraw(RendererImpl& renderer, bool final)
     : mRenderer(renderer), mFinal(final), tiler(renderer.m_tiledCanvas)
{
}

void
OutputDraw::apply(const FinishedShape& s)
{
    if (mRenderer.requestStop) throw Stopped();
    if (!mFinal  &&  mRenderer.requestFinishUp) throw Stopped();
    
    if (mRenderer.requestUpdate)
        mRenderer.outputStats();

    if (!s.mWorldState.m_time.overlaps(mRenderer.mFrameTimeBounds))
        return;

    mRenderer.m_stats.outputDone += 1;

    agg::trans_affine tr = s.mWorldState.m_transform;
    tr *= mRenderer.m_currTrans;
    double a = s.mWorldState.m_ColorTarget.a * mRenderer.m_currArea; //fabs(tr.determinant()); 
    if ((!isfinite(a) && s.mShapeType != primShape::fillType) || 
        a < mRenderer.m_minArea) return;
    
    if (tiler) {
        Bounds b = s.mBounds;
        mRenderer.m_currTrans.transform(&b.mMin_X, &b.mMin_Y);
        mRenderer.m_currTrans.transform(&b.mMax_X, &b.mMax_Y);
        tiler->tileTransform(b);
    }

    if (mRenderer.m_cfdg->getShapeType(s.mShapeType) == CFDGImpl::pathType) {
        //mRenderer.m_canvas->path(s.mColor, tr, *s.mAttributes);
        const ASTrule* rule = mRenderer.m_cfdg->findRule(s.mShapeType, 0.0);
        rule->traversePath(s, &mRenderer);
    } else {
        RGBA8 color = mRenderer.m_cfdg->getColor(s.mWorldState.m_Color);
        switch(s.mShapeType) {
            case primShape::circleType:
                mRenderer.m_canvas->circle(color, tr);
                break;
            case primShape::squareType:
                mRenderer.m_canvas->square(color, tr);
                break;
            case primShape::triangleType:
                mRenderer.m_canvas->triangle(color, tr);
                break;
            case primShape::fillType:
                mRenderer.m_canvas->fill(color);
                break;
            default:
                mRenderer.system()->error();
                mRenderer.system()->message("Non drawable shape with no rules: %s",
                    mRenderer.m_cfdg->decodeShapeName(s.mShapeType).c_str());
                mRenderer.requestStop = true;
                throw Stopped();
        }
    }
}


void RendererImpl::output(bool final)
{
    if (!m_canvas)
        return;
        
    if (!final &&  !m_finishedFiles.empty())
        return; // don't do updates once we have temp files
        
    m_stats.inOutput = true;
    m_stats.fullOutput = final;
    m_stats.finalOutput = final;
    m_stats.outputCount = m_stats.shapeCount;

    int curr_width = m_width;
    int curr_height = m_height;
    rescaleOutput(curr_width, curr_height, final);
    
    m_stats.outputDone = m_outputSoFar;
    
    m_canvas->start(m_outputSoFar == 0, m_cfdg->getBackgroundColor(0),
        curr_width, curr_height);

    m_drawingMode = true;
    OutputDraw draw(*this, final);
    try {
        forEachShape(final, draw);
    }
    catch (OutputDraw::Stopped) { }

    m_canvas->end();
    m_stats.inOutput = false;
    m_stats.outputTime = m_canvas->mTime;
}


void
RendererImpl::outputStats()
{
    system()->stats(m_stats);
    requestUpdate = false;
}

void
RendererImpl::processPathCommand(const Shape& s, const AST::CommandInfo* attr)
{
    if (m_drawingMode) {
        if (m_canvas && attr) {
            RGBA8 color = m_cfdg->getColor(s.mWorldState.m_Color);
            agg::trans_affine tr = s.mWorldState.m_transform;
            tr *= m_currTrans;
            m_canvas->path(color, tr, *attr);
        }
    } else {
        if (attr) {
            double area = 0.0;
            agg::point_d cent(0.0, 0.0);
            mPathBounds.update(s.mWorldState.m_transform, m_pathIter, mScale, *attr, 
                               &cent, &area);
            mCurrentCentroid.x = (mCurrentCentroid.x * mCurrentArea + cent.x * area) /
                                  (mCurrentArea + area);
            mCurrentCentroid.y = (mCurrentCentroid.x * mCurrentArea + cent.y * area) /
                                  (mCurrentArea + area);
            mCurrentArea = mCurrentArea + area;
        }
    }
}

void
RendererImpl::storeParams(const StackType* p)
{
    mLongLivedParams.push_back(p);
}
