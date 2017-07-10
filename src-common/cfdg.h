// cfdg.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2005-2013 John Horigan - john@glyphic.com
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
#include "agg2/agg_trans_affine.h"
#include "agg2/agg_color_rgba.h"
#include "agg2/agg_path_storage.h"
#include "location.hh"
#include "stacktype.h"
#include "Rand64.h"
#include "config.h"
#include <exception>
#include <memory>
#include <cstdint>

using RGBA8 = agg::rgba16;

namespace AST { class ASTcompiledPath; class ASTrule; class ASTparameter;
    using SymmList = std::vector<agg::trans_affine>;
    struct CommandInfo;
}
namespace agg { struct trans_affine_time; }
class Shape;
class tiledCanvas;
class Builder;

class DeferUntilRuntime : public std::exception {
public:
    virtual const char* what() const noexcept;
};
class CfdgError : public std::exception {
public:
    virtual const char* what() const noexcept;
    CfdgError& operator=(const CfdgError& e) noexcept;
    yy::location    where;
    static yy::location Default;
    
    static void     Error(const yy::location& errLoc, const char* msg, Builder* b = nullptr);
    static void     Warning(const yy::location& errLoc, const char* msg);
    
    CfdgError(const yy::location& loc, const char* msg);
    CfdgError(const char* msg);
private:
    const char* mMsg;
};

class AbstractSystem {
    public:
        enum TempType { ShapeTemp = 0, ExpansionTemp = 1, MergeTemp = 2, MovieTemp = 3, NumberofTempTypes = 4 };
        enum SystemSize : std::uint64_t {
#if defined(_WIN64) || defined(__x86_64__)
            MaximumMemory = 17179869184ULL,     // 16GB
            SystemIs64bit = 1
#else
            MaximumMemory = 2147483648ULL,      //  2GB
            SystemIs64bit = 0
#endif
        };

#ifdef _WIN32
        using FileChar = wchar_t;
        using FileString = std::wstring;
#define FileFormat "%S"
#else
        using FileChar = char;
        using FileString = std::string;
#define FileFormat "%s"
#endif
        int cfdgVersion = 2;

        virtual void message(const char* fmt, ...) = 0;
        virtual void syntaxError(const CfdgError& err) = 0;
        virtual bool error(bool errorOccurred = true) { return errorOccurred; };
        virtual void catastrophicError(const char* what) = 0;
    
        virtual std::istream* openFileForRead(const std::string& path) = 0;
        virtual std::istream* tempFileForRead(const FileString& path);
        virtual std::ostream* tempFileForWrite(TempType tt, FileString& nameOut) = 0;
        virtual const FileChar* tempFileDirectory() = 0;
            // caller must delete returned streams when done
        virtual std::vector<FileString> findTempFiles() = 0;
        virtual int deleteTempFile(const FileString& name) = 0;
        virtual size_t getPhysicalMemory() = 0;
    
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
            AbstractSystem* mSystem;

            Stats()
                : shapeCount(0), toDoCount(0), inOutput(false),
                  fullOutput(false), finalOutput(false), showProgress(false),
                  outputCount(0), outputDone(0), outputTime(0), animating(false),
                  mSystem(nullptr) {}
            ~Stats()
            {
                // Cancel system progress bar if it is being displayed
                if (mSystem && (showProgress || inOutput)) {
                    showProgress = inOutput = false;
                    mSystem->stats(*this);
                }
            }
        };

        virtual void orphan() = 0;

        virtual void stats(const Stats&);
        
        virtual ~AbstractSystem();
    protected:
        static const char* TempPrefixes[NumberofTempTypes];
        static const char* TempSuffixes[NumberofTempTypes];
        static const char* TempPrefixAll;
        static const wchar_t* TempPrefixes_w[NumberofTempTypes];
        static const wchar_t* TempSuffixes_w[NumberofTempTypes];
        static const wchar_t* TempPrefixAll_w;
        virtual void clearAndCR() {};
};

class Canvas {
    public:
        virtual void start(bool , const agg::rgba& , int , int ) 
        { mTime = clock(); }
        virtual void end()
        { mTime = clock() - mTime; }

        virtual void primitive(int, RGBA8 , agg::trans_affine ) = 0;
        virtual void path(RGBA8, agg::trans_affine, const AST::CommandInfo& ) = 0;

        Canvas(int width, int height) 
        : mWidth(width), mHeight(height), mError(false) {}
        virtual ~Canvas();
        
        int mWidth;
        int mHeight;
        clock_t mTime;
        bool mError;
};

class Renderer;
class CFDG;

using cfdg_ptr = std::shared_ptr<CFDG>;

class CFDG {
    public:
        enum frieze_t { no_frieze = 0, frieze_x, frieze_y };
        static cfdg_ptr ParseFile(const char* fname, AbstractSystem*, int variation);
        virtual ~CFDG();

        virtual Renderer* renderer(const cfdg_ptr& ptr,
                int width, int height, double minSize,
                int variation, double border = 2.0
            ) = 0;
            // caller must delete returned object

        bool usesColor;
        bool usesAlpha;
        bool uses16bitColor;
        bool usesTime;
        bool usesFrameTime;
        static const CfgArray<std::string>  ParamNames;
        static CFG lookupCfg(const std::string& name);
        virtual bool isTiled(agg::trans_affine* tr = nullptr, double* x = nullptr, double* y = nullptr) const = 0;
        virtual frieze_t isFrieze(agg::trans_affine* tr = nullptr, double* x = nullptr, double* y = nullptr) const = 0;
        virtual bool isSized(double* x = nullptr, double* y = nullptr) const = 0;
        virtual bool isTimed(agg::trans_affine_time* t = nullptr) const = 0;
        virtual const agg::rgba& getBackgroundColor() = 0;

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
        virtual void animate(Canvas* canvas, int frames, int frame, bool zoom) = 0;

        volatile bool requestStop;     // stop ASAP
        volatile bool requestFinishUp; // stop expanding, and do final output
        volatile bool requestUpdate;   // call stats() soon
        
        int m_width;
        int m_height;
        std::unique_ptr<tiledCanvas> m_tiledCanvas;
    
        static double Infinity;
        static bool   AbortEverything;
        static unsigned ParamCount;
    protected:
        Renderer(int w, int h);
};

#endif
