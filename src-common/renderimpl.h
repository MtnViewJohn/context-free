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
#include <type_traits>

#include "agg2/agg_trans_affine.h"
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

class RendererImpl final : public RendererAST {
    public:
        RendererImpl(const cfdg_ptr& cfdg,
                     int width, int height, double minSize,
                     int variation, double border);
        ~RendererImpl() override;
    
        void setMaxShapes(int n) final;
        void resetBounds() final;
        void resetSize(int x, int y) final;
        void initBounds();
        
        double run(Canvas* canvas, bool partialDraw) final;
        void draw(Canvas* canvas) final;
        void animate(Canvas* canvas, int frames, int frame, bool zoom) final;
        void processPathCommand(const Shape& s, const AST::CommandInfo* attr) final;
        void processShape(Shape& s) final;
        void processPrimShape(Shape& s, const AST::ASTrule* path = nullptr) final;
        void processSubpath(const Shape& s, bool tr, int) final;
        
    private:
        void outputPrep(Canvas*);
        void rescaleOutput(int& curr_width, int& curr_height, bool final);
        void forEachShape(bool final, ShapeFunction op);
        void processPrimShapeSiblings(Shape&& s, const AST::ASTrule* path);
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
        Canvas*     m_canvas = nullptr;
        pathIterator m_pathIter;
    
        bool        mColorConflict = false;

        int m_maxShapes;
        bool m_tiled = false;
        bool m_sized = false;
        bool m_timed = false;
        CFDG::frieze_t m_frieze = CFDG::frieze_t::no_frieze;
        double m_frieze_size = 0;
        bool m_drawingMode = false;
        bool mFinal = false;

        using FinishedContainer = chunk_vector<FinishedShape, 10>;
        FinishedContainer mFinishedShapes;
        using UnfinishedContainer = chunk_vector<Shape, 10>;
        UnfinishedContainer mUnfinishedShapes;

        std::deque<TempFile> m_finishedFiles;
        std::deque<TempFile> m_unfinishedFiles;
        int mFinishedFileCount = 0;
        int mUnfinishedFileCount = 0;

        int mVariation = 0;
        double m_border;
        
        double mScaleArea = 0;
        double mScale = 0;
        double mFixedBorderX = 0;
        double mFixedBorderY = 0;
        double mShapeBorder = 0;
        double mTotalArea = 0;
    
        double mCurrentArea = 0;
        Bounds mPathBounds;

        double m_currScale = 0;
        double m_currArea = 0;
        double m_minArea = 0;
        double m_minSize = 0.3;
        Bounds mBounds;
        agg::trans_affine_time mTimeBounds;
        agg::trans_affine_time mFrameTimeBounds;
        agg::trans_affine m_currTrans;
        unsigned int m_outputSoFar = 0;
    
        std::vector<agg::trans_affine> mSymmetryOps;

        AbstractSystem::Stats m_stats;
        int m_unfinishedInFilesCount = 0;
    
        primShape::primShapes_t shapeCopies;
        std::array<AST::CommandInfo, primShape::numTypes> shapeMap;
    
        static unsigned int MoveFinishedAt;     // when this many, move to file
        static unsigned int MoveUnfinishedAt;   // when this many, move to files
        static unsigned int MaxMergeFiles;      // maximum number of files to merge at once
    
    protected:
        void colorConflict(const yy::location& w) final;
};


#endif // INCLUDE_RENDERIMPL_H
