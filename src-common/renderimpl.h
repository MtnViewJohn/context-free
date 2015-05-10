// renderimpl.h
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


#ifndef INCLUDE_RENDERIMPL_H
#define INCLUDE_RENDERIMPL_H

#ifdef _WIN32
#pragma warning( disable : 4786 )
#endif

#include <deque>
#include <set>
#include <array>

#include "agg_trans_affine.h"
#include "agg_trans_affine_time.h"
#include "bounds.h"
#include "rendererAST.h"
#include "cfdgimpl.h"
#include "shape.h"
#include "tempfile.h"
#include "shape.h"
#include "CmdInfo.h"
#include "pathIterator.h"
#include "chunk_vector.h"

class ShapeOp;
namespace AST {
    class ASTbodyContainer;
    class ASTrule;
    class ASTpathCommand;
    class ASTcompiledPath;
}

class RendererImpl : public RendererAST {
    public:
        RendererImpl(CFDGImpl* cfdg,    // takes ownership w/o move semantics
                        int width, int height, double minSize,
                        int variation, double border);
        ~RendererImpl();
    
        virtual void storeParams(const StackRule* p);
    
        void setMaxShapes(int n);
        void resetBounds();
        void resetSize(int x, int y);
        void initBounds();
        
        double run(Canvas* canvas, bool partialDraw);
        void draw(Canvas* canvas);
        void animate(Canvas* canvas, int frames, bool zoom);
        void processPathCommand(const Shape& s, const AST::CommandInfo* attr) override;
        void processShape(const Shape& s) override;
        void processPrimShape(const Shape& s, const AST::ASTrule* attr = nullptr) override;
        void processSubpath(const Shape& s, bool tr, int) override;
        
    private:
        void outputPrep(Canvas*);
        void rescaleOutput(int& curr_width, int& curr_height, bool final);
        void forEachShape(bool final, ShapeFunction op);
        void processPrimShapeSiblings(Shape&& s, const AST::ASTrule* attr);
        void drawShape(const FinishedShape& s);

        void output(bool final);
        void outputPartial() { output(false); }
        void outputFinal() { output(true); }
        void outputStats();

        friend class OutputDraw;
        friend class OutputMerge;
        friend class OutputBounds;
        
        bool isDone();
        void fileIfNecessary();
        void moveFinishedToFile();
        void moveUnfinishedToTwoFiles();
        void getUnfinishedFromFile();
        AbstractSystem* system() { return m_cfdg->system(); }
        void fixupHeap();
    
        void init();
        void cleanup();

    private:
        cfdgi_ptr   m_cfdg;
        Canvas*     m_canvas;
        pathIterator m_pathIter;
    
        bool        mColorConflict;

        int m_maxShapes;
        bool m_tiled;
        bool m_sized;
        bool m_timed;
        CFDG::frieze_t m_frieze;
        double m_frieze_size;
        bool m_drawingMode;
        bool mFinal;

        typedef chunk_vector<FinishedShape, 10> FinishedContainer;
        FinishedContainer mFinishedShapes;
        typedef chunk_vector<Shape, 10> UnfinishedContainer;
        UnfinishedContainer mUnfinishedShapes;

        std::deque<TempFile> m_finishedFiles;
        std::deque<TempFile> m_unfinishedFiles;
        int mFinishedFileCount;
        int mUnfinishedFileCount;

        int mVariation;
        double m_border;
        
        double mScaleArea;
        double mScale;
        double mFixedBorderX;
        double mFixedBorderY;
        double mShapeBorder;
        double mTotalArea;
    
        double mCurrentArea;
        Bounds mPathBounds;

        double m_currScale;
        double m_currArea;
        double m_minArea;
        double m_minSize;
        Bounds mBounds;
        agg::trans_affine_time mTimeBounds;
        agg::trans_affine_time mFrameTimeBounds;
        agg::trans_affine m_currTrans;
        unsigned int m_outputSoFar;
    
        std::vector<agg::trans_affine> mSymmetryOps;

        AbstractSystem::Stats m_stats;
        int m_unfinishedInFilesCount;
    
        primShape        circleCopy;
        primShape        squareCopy;
        primShape        triangleCopy;
        std::array<AST::CommandInfo, 3> shapeMap;
    
        static unsigned int MoveFinishedAt;     // when this many, move to file
        static unsigned int MoveUnfinishedAt;   // when this many, move to files
        static unsigned int MaxMergeFiles;      // maximum number of files to merge at once
    
    protected:
        void colorConflict(const yy::location& w) override;
};


#endif // INCLUDE_RENDERIMPL_H
