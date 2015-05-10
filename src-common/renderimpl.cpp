// renderimpl.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2006-2014 John Horigan - john@glyphic.com
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
#include <functional>

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
unsigned int RendererImpl::MoveFinishedAt = 0;     // when this many, move to file
unsigned int RendererImpl::MoveUnfinishedAt = 0;   // when this many, move to files
unsigned int RendererImpl::MaxMergeFiles = 0;      // maximum number of files to merge at once

const double SHAPE_BORDER = 1.0; // multiplier of shape size when calculating bounding box
const double FIXED_BORDER = 8.0; // fixed extra border, in pixels

RendererImpl::RendererImpl(CFDGImpl* cfdg,
                            int width, int height, double minSize,
                            int variation, double border)
    : RendererAST(width, height), m_cfdg(cfdg), m_canvas(nullptr), mColorConflict(false), 
      m_maxShapes(500000000), mVariation(variation), m_border(border), 
      mScaleArea(0.0), mScale(0.0), m_currScale(0.0), m_currArea(0.0), 
      m_minSize(minSize), mFrameTimeBounds(1.0, -Renderer::Infinity, Renderer::Infinity),
      circleCopy(primShape::circle), squareCopy(primShape::square), triangleCopy(primShape::triangle),
      shapeMap{}
{
    if (MoveFinishedAt == 0) {
#ifndef DEBUG_SIZES
        size_t mem = m_cfdg->system()->getPhysicalMemory();
        if (mem == 0) {
            MoveFinishedAt = MoveUnfinishedAt = 2000000;
        } else {
            MoveFinishedAt = MoveUnfinishedAt = static_cast<unsigned int>(mem / (sizeof(FinishedShape) * 4));
        }
        MaxMergeFiles      =      200; // maximum number of files to merge at once
#else
        MoveFinishedAt     =    1000; // when this many, move to file
        MoveUnfinishedAt   =     200; // when this many, move to files
        MaxMergeFiles      =       4; // maximum number of files to merge at once
#endif
    }
    
    shapeMap = { { CommandInfo(&circleCopy), CommandInfo(&squareCopy), CommandInfo(&triangleCopy)} };

    m_cfdg->hasParameter(CFG::FrameTime, mCurrentTime, nullptr);
    m_cfdg->hasParameter(CFG::Frame, mCurrentFrame, nullptr);
}

void
RendererImpl::colorConflict(const yy::location& w)
{
    if (mColorConflict) return;
    CfdgError err(w, "Conflicting color change");
    system()->error();
    system()->syntaxError(err);
    mColorConflict = true;
}

void
RendererImpl::init()
{
    // Performs RendererImpl initializations that are needed before rendering
    // and before each frame of an animation
    
    mCurrentSeed.seed(static_cast<unsigned long long>(mVariation));
    mCurrentSeed();
    
    mLogicalStackTop = mCFstack.data();
    mStackSize = 0;
    
    Shape dummy;
    for (const rep_ptr& rep: m_cfdg->mCFDGcontents.mBody) {
        if (const ASTdefine* def = dynamic_cast<const ASTdefine*> (rep.get()))
            def->traverse(dummy, false, this);
    }
    
    mFinishedFileCount = 0;
    mUnfinishedFileCount = 0;
    
    mFixedBorderX = mFixedBorderY = 0.0;
    mShapeBorder = 1.0;
    mTotalArea = 0.0;
    
    m_minArea = 0.3; 
    m_outputSoFar = m_stats.shapeCount = m_stats.toDoCount = 0;
    double minSize = m_minSize;
    m_cfdg->hasParameter(CFG::MinimumSize, minSize, this);
    minSize = (minSize <= 0.0) ? 0.3 : minSize;
    m_minArea = minSize * minSize;

    mFixedBorderX = FIXED_BORDER * ((m_border <= 1.0) ? m_border : 1.0);
    mShapeBorder = SHAPE_BORDER * ((m_border <= 1.0) ? 1.0 : m_border);
    
    m_cfdg->hasParameter(CFG::BorderFixed, mFixedBorderX, this);
    m_cfdg->hasParameter(CFG::BorderDynamic, mShapeBorder, this);
    if (2 * static_cast<int>(fabs(mFixedBorderX)) >= min(m_width, m_height))
        mFixedBorderX = 0.0;
    if (mShapeBorder <= 0.0)
        mShapeBorder = 1.0;
    
    if (m_cfdg->hasParameter(CFG::MaxNatural, mMaxNatural, this) &&
        (mMaxNatural < 1.0 || (mMaxNatural - 1.0) == mMaxNatural))
    {
        const ASTexpression* max = m_cfdg->hasParameter(CFG::MaxNatural);
        throw CfdgError(max->where, (mMaxNatural < 1.0) ?
                            "CF::MaxNatural must be >= 1" :
                            "CF::MaxNatural must be < 9007199254740992");
    }
    
    mCurrentPath.reset(new AST::ASTcompiledPath());
    
    m_cfdg->getSymmetry(mSymmetryOps, this);
    m_cfdg->setBackgroundColor(this);
}

void
RendererImpl::initBounds()
{
    init();
    double tile_x, tile_y;
    m_tiled = m_cfdg->isTiled(nullptr, &tile_x, &tile_y);
    m_frieze = m_cfdg->isFrieze(nullptr, &tile_x, &tile_y);
    m_sized = m_cfdg->isSized(&tile_x, &tile_y);
    m_timed = m_cfdg->isTimed(&mTimeBounds);
    
    if (m_tiled || m_sized) {
        mFixedBorderX = mShapeBorder = 0.0;
        mBounds.mMin_X = -(mBounds.mMax_X = tile_x / 2.0);
        mBounds.mMin_Y = -(mBounds.mMax_Y = tile_y / 2.0);
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

RendererImpl::~RendererImpl()
{
    cleanup();
    if (AbortEverything)
        return;
#ifdef EXTREME_PARAM_DEBUG
    AbstractSystem* sys = system();
    for (auto &p: StackRule::ParamMap) {
        if (p.second > 0)
            sys->message("Parameter at %p is still alive, it is param number %d\n", p.first, p.second);
    }
#endif
}

class Stopped { };

void
RendererImpl::cleanup()
{
    // delete temp files before checking for abort
    m_finishedFiles.clear();
    m_unfinishedFiles.clear();

    try {
        std::function <void (const Shape& s)> checkStop([](const Shape& s) {
            if (Renderer::AbortEverything)
                throw Stopped();
        });
        for_each(mUnfinishedShapes.begin(), mUnfinishedShapes.end(), checkStop);
        for_each(mFinishedShapes.begin(), mFinishedShapes.end(), checkStop);
    } catch (Stopped&) {
        return;
    } catch (exception& e) {
        system()->catastrophicError(e.what());
        return;
    }
    mUnfinishedShapes.clear();
    mFinishedShapes.clear();
    
    unwindStack(0, m_cfdg->mCFDGcontents.mParameters);
    
    mCurrentPath.reset();
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
            m_tiledCanvas.reset(new tiledCanvas(canvas, tr, m_frieze));
            m_tiledCanvas->scale(m_currScale);
            m_canvas = m_tiledCanvas.get();
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

    {
        Shape initShape = m_cfdg->getInitialShape(this);
        initShape.mWorldState.mRand64Seed = mCurrentSeed;
        if (!m_timed)
            mTimeBounds = initShape.mWorldState.m_time;
        
        try {
            processShape(initShape);
        } catch (CfdgError& e) {
            requestStop = true;
            system()->error();
            system()->syntaxError(e);
        } catch (exception& e) {
            requestStop = true;
            system()->catastrophicError(e.what());
        }
    }
    
    for (;;) {
        fileIfNecessary();
        
        if (requestStop) break;
        if (requestFinishUp) break;
        
        if (mUnfinishedShapes.empty()) break;
        if ((m_stats.shapeCount + m_stats.toDoCount) > m_maxShapes)
            break;

        // Get the largest unfinished shape
        Shape s(std::move(mUnfinishedShapes.front()));
        pop_heap(mUnfinishedShapes.begin(), mUnfinishedShapes.end());
        mUnfinishedShapes.pop_back();
        m_stats.toDoCount--;
        
        try {
            const ASTrule* rule = m_cfdg->findRule(s.mShapeType, s.mWorldState.mRand64Seed.getDouble());
            m_drawingMode = false;      // shouldn't matter
            rule->traverse(s, false, this);
        } catch (CfdgError& e) {
            requestStop = true;
            system()->error();
            system()->syntaxError(e);
            break;
        } catch (exception& e) {
            requestStop = true;
            system()->catastrophicError(e.what());
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
        if (m_canvas)
            system()->message("Done.");
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

class OutputBounds
{
public:
    OutputBounds(int frames, const agg::trans_affine_time& timeBounds, 
                 int width, int height, RendererImpl& renderer);
    void apply(const FinishedShape&);

    const Bounds& frameBounds(int frame) { return mFrameBounds[frame]; }
    int           frameCount(int frame) { return mFrameCounts[frame]; }
    
    void finalAccumulate();
    // call after all the frames to compute the bounds at each frame
    
    void backwardFilter(double framesToHalf);
    void smooth(int window);
    
private:
    agg::trans_affine_time mTimeBounds;
    double          mFrameScale;
    vector<Bounds>  mFrameBounds;
    vector<int>     mFrameCounts;
    double          mScale;
    int             mWidth;
    int             mHeight;
    int             mFrames;
    RendererImpl&   mRenderer;

    OutputBounds& operator=(const OutputBounds&);   // not defined
};

OutputBounds::OutputBounds(int frames, const agg::trans_affine_time& timeBounds, 
                           int width, int height, RendererImpl& renderer)
: mTimeBounds(timeBounds), mScale(0.0),
  mWidth(width), mHeight(height), mFrames(frames), mRenderer(renderer)
{
    mFrameScale = static_cast<double>(frames) / (timeBounds.tend - timeBounds.tbegin);
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
    int begin = (frameTime.tbegin < mFrames) ? static_cast<int>(floor(frameTime.tbegin)) : (mFrames - 1);
    int end = (frameTime.tend < mFrames) ? static_cast<int>(floor(frameTime.tend)) : (mFrames - 1);
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
    size_t frames = mFrameBounds.size();
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
    
    mFrameBounds.resize(frames);
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
    
    m_canvas->start(true, m_cfdg->getBackgroundColor(),
        curr_width, curr_height);
    m_canvas->end();

    double frameInc = (mTimeBounds.tend - mTimeBounds.tbegin) / frames;
    
    OutputBounds outputBounds(frames, mTimeBounds, curr_width, curr_height, *this);
    if (zoom) {
        system()->message("Computing zoom");

        try {
            forEachShape(true, [&](const FinishedShape& s) {
                outputBounds.apply(s);
            });
            //outputBounds.finalAccumulate();
            outputBounds.backwardFilter(10.0);
            //outputBounds.smooth(3);
        } catch (Stopped&) {
            m_stats.animating = false;
            return;
        } catch (exception& e) {
            system()->catastrophicError(e.what());
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
            } catch (CfdgError& err) {
                system()->error();
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
        return;
    }
    
    if (s.mWorldState.m_time.tbegin > s.mWorldState.m_time.tend) {
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
        }
    } else if (m_cfdg->getShapeType(s.mShapeType) == CFDGImpl::pathType) {
        const ASTrule* rule = m_cfdg->findRule(s.mShapeType, 0.0);
        processPrimShape(s, rule);
    } else if (primShape::isPrimShape(s.mShapeType)) {
        processPrimShape(s);
    } else {
        requestStop = true;
        system()->error();
        system()->message("Shape with no rules encountered: %s.", 
            m_cfdg->decodeShapeName(s.mShapeType).c_str());
    }
}

void
RendererImpl::processPrimShape(const Shape& s, const ASTrule* path)
{
    size_t num = mSymmetryOps.size();
    if (num == 0 || s.mShapeType == primShape::fillType) {
        Shape copy(s);
        processPrimShapeSiblings(std::move(copy), path);
    } else {
        for (size_t i = 0; i < num; ++i) {
            Shape sym(s);
            sym.mWorldState.m_transform.multiply(mSymmetryOps[i]);
            processPrimShapeSiblings(std::move(sym), path);
        }
    }
}

void
RendererImpl::processPrimShapeSiblings(Shape&& s, const ASTrule* path)
{
    m_stats.shapeCount++;
    if (mScale == 0.0) {
        // If we don't know the approximate scale yet then just
        // make an educated guess.
        mScale = (m_width + m_height) / sqrt(fabs(s.mWorldState.m_transform.determinant()));
    }
    if (path || s.mShapeType != primShape::fillType) {
        mCurrentArea = 0.0;
        mPathBounds.invalidate();
        m_drawingMode = false;
        if (path) {
            mOpsOnly = false;
            path->traversePath(s, this);
        } else {
            CommandInfo* attr = nullptr;
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
        mCurrentArea = 1.0;
    }
    FinishedShape fs(std::move(s), m_stats.shapeCount, mPathBounds);
    fs.mWorldState.m_Z.sz = mCurrentArea;
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
    mFinishedShapes.push_back(fs);
}

void
RendererImpl::processSubpath(const Shape& s, bool tr, int expectedType)
{
    const ASTrule* rule = nullptr;
    if (m_cfdg->getShapeType(s.mShapeType) != CFDGImpl::pathType && 
        primShape::isPrimShape(s.mShapeType) && expectedType == ASTreplacement::op)
    {
        static const ASTrule PrimitivePaths[primShape::numTypes] = { { 0 }, { 1 }, { 2 }, { 3 } };
        rule = &PrimitivePaths[s.mShapeType];
    } else {
        rule = m_cfdg->findRule(s.mShapeType, 0.0);
    }
    if (static_cast<int>(rule->mRuleBody.mRepType) != expectedType)
        throw CfdgError(rule->mLocation, "Subpath is not of the expected type (path ops/commands)");
    bool saveOpsOnly = mOpsOnly;
    mOpsOnly = mOpsOnly || (expectedType == ASTreplacement::op);
    rule->mRuleBody.traverse(s, tr, this, true);
    mOpsOnly = saveOpsOnly;
}


//-------------------------------------------------------------------------////


void
RendererImpl::fileIfNecessary()
{
    if (mFinishedShapes.size() > MoveFinishedAt)
        moveFinishedToFile();

    if (mUnfinishedShapes.size() > MoveUnfinishedAt)
        moveUnfinishedToTwoFiles();
    else if (mUnfinishedShapes.empty())
        getUnfinishedFromFile();
}

void
RendererImpl::moveUnfinishedToTwoFiles()
{
    m_unfinishedFiles.emplace_back(system(), AbstractSystem::ExpensionTemp,
                                   "expansion", ++mUnfinishedFileCount);
    unique_ptr<ostream> f1(m_unfinishedFiles.back().forWrite());
    int num1 = m_unfinishedFiles.back().number();

    m_unfinishedFiles.emplace_back(system(), AbstractSystem::ExpensionTemp,
                                   "expansion", ++mUnfinishedFileCount);
    unique_ptr<ostream> f2(m_unfinishedFiles.back().forWrite());
    int num2 = m_unfinishedFiles.back().number();
    
    system()->message("Writing %s temp files %d & %d",
                      m_unfinishedFiles.back().type().c_str(), num1, num2);

    size_t count = mUnfinishedShapes.size() / 3;

    UnfinishedContainer::iterator usi = mUnfinishedShapes.begin(),
                                  use = mUnfinishedShapes.end();
    usi += count;
    
    if (f1 && f1->good() && f2 && f2->good()) {
        AbstractSystem::Stats outStats = m_stats;
        outStats.outputCount = static_cast<int>(count);
        outStats.outputDone = 0;
        *f1 << outStats.outputCount;
        *f2 << outStats.outputCount;
        outStats.outputCount = static_cast<int>(count * 2);
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
    assert(is_heap(mUnfinishedShapes.begin(), mUnfinishedShapes.end()));
}

void
RendererImpl::getUnfinishedFromFile()
{
    if (m_unfinishedFiles.empty()) return;
    
    TempFile t(std::move(m_unfinishedFiles.front()));
    m_unfinishedFiles.pop_front();
    
    unique_ptr<istream> f(t.forRead());

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
}

void
RendererImpl::fixupHeap()
{
    // Restore heap property to mUnfinishedShapes
    auto first = mUnfinishedShapes.begin();
    auto last = mUnfinishedShapes.end();
    typedef UnfinishedContainer::iterator::difference_type difference_type;
    difference_type n = last - first;
    if (n < 2)
        return;

    AbstractSystem::Stats outStats = m_stats;
    outStats.outputCount = static_cast<int>(n);
    outStats.outputDone = 0;
    outStats.showProgress = true;
    
    last = first;
    ++last;
    for (difference_type i = 1; i < n; ++i) {
        push_heap(first, ++last);
    
        ++outStats.outputDone;
        if (requestUpdate) {
            system()->stats(outStats);
            requestUpdate = false;
        }
        if (requestStop || requestFinishUp)
            return;
    }
    assert(is_heap(mUnfinishedShapes.begin(), mUnfinishedShapes.end()));
}

//-------------------------------------------------------------------------////

void
RendererImpl::moveFinishedToFile()
{
    m_finishedFiles.emplace_back(system(), AbstractSystem::ShapeTemp, "shapes", ++mFinishedFileCount);
    
    unique_ptr<ostream> f(m_finishedFiles.back().forWrite());

    if (f && f->good()) {
        if (mFinishedShapes.size() > 10000)
            system()->message("Sorting shapes...");
        std::sort(mFinishedShapes.begin(), mFinishedShapes.end());
        AbstractSystem::Stats outStats = m_stats;
        outStats.outputCount = static_cast<int>(mFinishedShapes.size());
        outStats.outputDone = 0;
        outStats.showProgress = true;
        for (const FinishedShape& fs: mFinishedShapes) {
            *f << fs;
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
    
    if (!mBounds.valid()) return;

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
RendererImpl::forEachShape(bool final, ShapeFunction op)
{
    if (!final || m_finishedFiles.empty()) {
        FinishedContainer::iterator start = mFinishedShapes.begin();
        FinishedContainer::iterator last  = mFinishedShapes.end();
        if (!final)
            start += m_outputSoFar;
        for_each(start, last, op);
        m_outputSoFar = static_cast<int>(mFinishedShapes.size());
    } else {
        deque<TempFile>::iterator begin, last, end;
        
        while (m_finishedFiles.size() > MaxMergeFiles) {
            TempFile t(system(), AbstractSystem::MergeTemp, "merge", ++mFinishedFileCount);
            
            {
                OutputMerge merger;
                
                begin = m_finishedFiles.begin();
                last = begin + (MaxMergeFiles - 1);
                end = last + 1;
                
                for (auto it = begin; it != end; ++it)
                    merger.addTempFile(*it);
                
                std::unique_ptr<ostream> f(t.forWrite());
                if (!f) {
                    system()->message("Cannot open temporary file for shapes");
                    requestStop = true;
                    return;
                }
                system()->message("Merging temp files %d through %d",
                                  begin->number(), last->number());
                
                merger.merge([&](const FinishedShape& s) {
                    *f << s;
                });
            }   // end scope for merger and f
            
            for (unsigned i = 0; i < MaxMergeFiles; ++i)
                m_finishedFiles.pop_front();
            m_finishedFiles.push_back(std::move(t));
        }
        
        OutputMerge merger;
        
        begin = m_finishedFiles.begin();
        end = m_finishedFiles.end();
        
        for (auto it = begin; it != end; ++it)
            merger.addTempFile(*it);
        
        merger.addShapes(mFinishedShapes.begin(), mFinishedShapes.end());
        merger.merge(op);
    }
}

void
RendererImpl::drawShape(const FinishedShape& s)
{
    if (requestStop) throw Stopped();
    if (!mFinal  &&  requestFinishUp) throw Stopped();
    
    if (requestUpdate)
        outputStats();

    if (!s.mWorldState.m_time.overlaps(mFrameTimeBounds))
        return;

    m_stats.outputDone += 1;

    agg::trans_affine tr = s.mWorldState.m_transform;
    tr *= m_currTrans;
    double a = s.mWorldState.m_Z.sz * m_currArea; //fabs(tr.determinant());
    if ((!isfinite(a) && s.mShapeType != primShape::fillType) || 
        a < m_minArea) return;
    
    if (m_tiledCanvas && s.mShapeType != primShape::fillType) {
        Bounds b = s.mBounds;
        m_currTrans.transform(&b.mMin_X, &b.mMin_Y);
        m_currTrans.transform(&b.mMax_X, &b.mMax_Y);
        m_tiledCanvas->tileTransform(b);
    }

    if (m_cfdg->getShapeType(s.mShapeType) == CFDGImpl::pathType) {
        //mRenderer.m_canvas->path(s.mColor, tr, *s.mAttributes);
        const ASTrule* rule = m_cfdg->findRule(s.mShapeType, 0.0);
        rule->traversePath(s, this);
    } else {
        RGBA8 color = m_cfdg->getColor(s.mWorldState.m_Color);
        switch(s.mShapeType) {
            case primShape::circleType:
                m_canvas->circle(color, tr);
                break;
            case primShape::squareType:
                m_canvas->square(color, tr);
                break;
            case primShape::triangleType:
                m_canvas->triangle(color, tr);
                break;
            case primShape::fillType:
                m_canvas->fill(color);
                break;
            default:
                system()->error();
                system()->message("Non drawable shape with no rules: %s",
                    m_cfdg->decodeShapeName(s.mShapeType).c_str());
                requestStop = true;
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
    mFinal = final;

    int curr_width = m_width;
    int curr_height = m_height;
    rescaleOutput(curr_width, curr_height, final);
    
    m_stats.outputDone = m_outputSoFar;
    
    if (final) {
        if (mFinishedShapes.size() > 10000)
            system()->message("Sorting shapes...");
        std::sort(mFinishedShapes.begin(), mFinishedShapes.end());
    }
    
    m_canvas->start(m_outputSoFar == 0, m_cfdg->getBackgroundColor(),
        curr_width, curr_height);

    m_drawingMode = true;
    //OutputDraw draw(*this, final);
    try {
        forEachShape(final, [=](const FinishedShape& s) {
            this->drawShape(s);
        });
    }
    catch (Stopped&) { }
    catch (exception& e) {
        system()->catastrophicError(e.what());
    }

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
            mPathBounds.update(s.mWorldState.m_transform, m_pathIter, mScale, *attr);
            mCurrentArea = fabs((mPathBounds.mMax_X - mPathBounds.mMin_X) *
                                (mPathBounds.mMax_Y - mPathBounds.mMin_Y));
        }
    }
}

void
RendererImpl::storeParams(const StackRule* p)
{
    p->mRefCount = StackRule::MaxRefCount;
    m_cfdg->mLongLivedParams.push_back(p);
}
