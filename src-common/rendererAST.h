// rendererAST.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2013 John Horigan - john@glyphic.com
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

#ifndef INCLUDE_RENDERERAST_H
#define INCLUDE_RENDERERAST_H

#include "cfdg.h"
#include "CmdInfo.h"

class RendererAST : public Renderer {
public:
    // AST interface
        ~RendererAST();
        std::vector<StackType>  mCFstack;
        const StackType*  mLogicalStackTop;
        void initStack(const StackRule* p);
        void unwindStack(size_t oldsize, const std::vector<AST::ASTparameter>& params);
        const StackType* stackItem(int offset) const {
            return (offset < 0) ? (mLogicalStackTop + offset) : (mCFstack.data() + offset);
        }
        
        Rand64      mCurrentSeed;
        bool        mRandUsed;
    
        double      mMaxNatural;

        double      mCurrentTime;
        double      mCurrentFrame;
        
        agg::point_d mLastPoint;
        bool         mStop;
        bool         mClosed;
        bool         mWantMoveTo;
        bool         mWantCommand;
        bool         mOpsOnly;
        unsigned     mIndex;
        unsigned     mNextIndex;
        AST::ASTcompiledPath* mCurrentPath;
        AST::InfoCache::iterator mCurrentCommand;
    
        void init();
        static bool isNatural(RendererAST* r, double n);
        static void ColorConflict(RendererAST* r, const yy::location& w);
        virtual void storeParams(const StackRule* p) = 0;
        virtual void processPathCommand(const Shape& s, const AST::CommandInfo* attr) = 0;
        virtual void processShape(const Shape& s) = 0;
        virtual void processPrimShape(const Shape& s, const AST::ASTrule* attr = nullptr) = 0;
        virtual void processSubpath(const Shape& s, bool tr, int) = 0;
    
    protected:
        RendererAST(int w, int h) 
        : Renderer(w, h),
          mMaxNatural(1000.0),
          mCurrentTime(0.0), mCurrentFrame(0.0),
          mCurrentPath(nullptr)
     { }
        virtual void colorConflict(const yy::location& w) = 0;
};

#endif  // INCLUDE_RENDERERAST_H