// cfdg.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2005-2008 John Horigan - john@glyphic.com
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


#ifndef INCLUDE_CFDG_H
#define INCLUDE_CFDG_H

#include <iosfwd>
#include <string>
#include <time.h>
#include <vector>
#include "agg_trans_affine.h"
#include "agg_color_rgba.h"
#include "agg_path_storage.h"
#include "location.hh"
#include "CmdInfo.h"
#include "stacktype.h"
#include "Rand64.h"

typedef agg::rgba16 RGBA8;

namespace AST { class ASTcompiledPath; class ASTrule; class ASTparameter; 
    typedef std::vector<agg::trans_affine> SymmList;
}
namespace agg { struct trans_affine_time; }
class Shape;
class tiledCanvas;

class DeferUntilRuntime {};
class CfdgError {
public:
    const char*     what;
    yy::location    where;
    static yy::location Default;
    
    static void     Error(const yy::location& errLoc, const char* msg);
    static void     Warning(const yy::location& errLoc, const char* msg);
    
    CfdgError(const yy::location& loc, const char* msg);
    CfdgError(const char* msg);
};

class AbstractSystem {
    public:
        virtual void message(const char* fmt, ...) = 0;
        virtual void syntaxError(const CfdgError& err) = 0;
        virtual bool error(bool errorOccurred = true) { return errorOccurred; };
        
        virtual std::istream* openFileForRead(const std::string& path) = 0;
        virtual std::istream* tempFileForRead(const std::string& path) = 0;
        virtual std::ostream* tempFileForWrite(std::string& prefixInNameOut) = 0;
            // caller must delete returned streams when done
            
        virtual std::string relativeFilePath(
            const std::string& base, const std::string& rel) = 0;
        
        struct Stats {
            int     shapeCount;     // finished shapes in image
            int     toDoCount;      // unfinished shapes still to expand
            
            bool    inOutput;       // true if we are in the output loop
            bool    fullOutput;     // not an incremental output
            bool    finalOutput;    // the last output
            bool    showProgress;
            int     outputCount;    // number to be output
            int     outputDone;     // number output so far
            clock_t outputTime;

            bool    animating;      // inside the animation loop

            Stats()
                : shapeCount(0), toDoCount(0), inOutput(false),
                  fullOutput(false), finalOutput(false), showProgress(false),
                  outputCount(0), outputDone(0), outputTime(0), animating(false) {}
        };

        virtual void stats(const Stats&);
        
        virtual ~AbstractSystem();
};

class Canvas {
    public:
        virtual void start(bool , const agg::rgba& , int , int ) 
        { mTime = clock(); }
        virtual void end()
        { mTime = clock() - mTime; }

        virtual void circle(RGBA8 , agg::trans_affine ) = 0;
        virtual void square(RGBA8 , agg::trans_affine ) = 0;
        virtual void triangle(RGBA8 , agg::trans_affine ) = 0;
        virtual void fill(RGBA8) = 0;
        virtual void path(RGBA8 , agg::trans_affine, const AST::CommandInfo& ) = 0;

        Canvas(int width, int height) 
        : mWidth(width), mHeight(height) {}
        virtual ~Canvas();
        
        int mWidth;
        int mHeight;
        clock_t mTime;
};

class Renderer;

class CFDG {
    public:
        enum frieze_t { no_frieze = 0, frieze_x, frieze_y };
        static CFDG* ParseFile(const char* fname, AbstractSystem*, int variation);
        virtual ~CFDG();

        virtual Renderer* renderer(
                int width, int height, double minSize,
                int variation, double border = 2.0
            ) = 0;
            // caller must delete returned object

        bool usesColor;
        bool usesAlpha;
        bool uses16bitColor;
        bool usesTime;
        bool usesFrameTime;
        virtual bool isTiled(agg::trans_affine* tr = 0, double* x = 0, double* y = 0) const = 0;
        virtual frieze_t isFrieze(agg::trans_affine* tr = 0, double* x = 0, double* y = 0) const = 0;
        virtual bool isSized(double* x = 0, double* y = 0) const = 0;
        virtual bool isTimed(agg::trans_affine_time* t = 0) const = 0;
        virtual const agg::rgba& getBackgroundColor(Renderer* r) = 0;
        virtual void getSymmetry(AST::SymmList& syms, Renderer* r) = 0;

    protected:
        CFDG()
        : usesColor(false), usesAlpha(false), uses16bitColor(false), 
          usesTime(false), usesFrameTime(false)
        { }
};


class Renderer {
    public:
    // OS interface
        virtual ~Renderer();
        
        virtual void setMaxShapes(int n) = 0;        
        virtual void resetBounds() = 0;
        virtual void resetSize(int x, int y) = 0;

        virtual double run(Canvas* canvas, bool partialDraw) = 0;
        virtual void draw(Canvas* canvas) = 0;
        virtual void animate(Canvas* canvas, int frames, bool zoom) = 0;

        volatile bool requestStop;     // stop ASAP
        volatile bool requestFinishUp; // stop expanding, and do final output
        volatile bool requestUpdate;   // call stats() soon
        
        int m_width;
        int m_height;
        tiledCanvas* m_tiledCanvas;
    
        static double Infinity;
        static bool   AbortEverything;
    
    // AST interface
        std::vector<StackType>  mCFstack;
        const StackType*  mLogicalStackTop;
        void initStack(const StackType* p);
        void unwindStack(size_t oldsize, const std::vector<AST::ASTparameter>& params);
        
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
        unsigned     mIndex;
        unsigned     mNextIndex;
        AST::ASTcompiledPath* mCurrentPath;
        AST::InfoCache::iterator mCurrentCommand;
    
        void init();
        static bool isNatural(Renderer* r, double n);
        virtual void storeParams(const StackType* p) = 0;
        virtual void processPathCommand(const Shape& s, const AST::CommandInfo* attr) = 0;
        virtual void processShape(const Shape& s) = 0;
        virtual void processPrimShape(const Shape& s, const AST::ASTrule* attr = 0) = 0;
        virtual void processSubpath(const Shape& s, bool tr, int) = 0;
    
    protected:
        Renderer() 
        : requestStop(false),
          requestFinishUp(false),
          requestUpdate(false),
          m_tiledCanvas(0),
          mMaxNatural(1000.0),
          mCurrentTime(0.0), mCurrentFrame(0.0),
          mCurrentPath(0)
     { }
};

#endif
