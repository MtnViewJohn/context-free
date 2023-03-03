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
#include <ctime>
#include <vector>
#include "agg2/agg_trans_affine.h"
#include "agg2/agg_color_rgba.h"
#include "agg2/agg_path_storage.h"
#include "agg2/agg_pixfmt_rgba.h"
#include "location.hh"
#include "stacktype.h"
#include "Rand64.h"
#include "config.h"
#include <exception>
#include <memory>
#include <cstdint>
#include <cstddef>
#include <array>
#include <map>
#include <atomic>

#define _unused(x) ((void)(x))

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
    const char* what() const noexcept override;
};
class CfdgError : public std::exception {
public:
    const char* what() const noexcept override;
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
#if defined(_WIN64) || defined(__x86_64__) || defined(__aarch64__)
            MaximumMemory = 17179869184ULL,     // 16GB
            SystemIs64bit = 1
#else
            MaximumMemory = 2147483648ULL,      //  2GB
            SystemIs64bit = 0
#endif
        };

#ifdef _WIN32
        using FileChar = wchar_t;
#define FileFormat "%S"
#define FileStr(x) L##x
#else
        using FileChar = char;
#define FileFormat "%s"
#define FileStr(x) x
#endif

        using FileString = std::basic_string<FileChar>;
        using istr_ptr = std::unique_ptr<std::istream>;
        using ostr_ptr = std::unique_ptr<std::ostream>;
    
        int cfdgVersion = 3;
        bool mFirstCfdgRead = true;

        virtual void message(const char* fmt, ...) = 0;
        virtual void syntaxError(const CfdgError& err) = 0;
        virtual bool error(bool errorOccurred = true) { return errorOccurred; };
        virtual void catastrophicError(const char* what) = 0;
        virtual bool isGuiProgram() { return true; }
    
        virtual istr_ptr openFileForRead(const std::string& path);
        virtual istr_ptr tempFileForRead(const FileString& path);
        virtual ostr_ptr tempFileForWrite(TempType tt, FileString& nameOut) = 0;
        virtual const FileChar* tempFileDirectory() = 0;
            // caller must delete returned streams when done
        virtual std::vector<FileString> findTempFiles() = 0;
        virtual int deleteTempFile(const FileString& name) = 0;
        virtual std::size_t getPhysicalMemory() = 0;
    
        virtual std::string relativeFilePath(
            const std::string& base, const std::string& rel) = 0;
    
        virtual std::wstring normalize(const std::string&) = 0;
        
        struct Stats {
            int     shapeCount = 0;     // finished shapes in image
            int     toDoCount = 0;      // unfinished shapes still to expand
            
            bool    inOutput = false;       // true if we are in the output loop
            bool    fullOutput = false;     // not an incremental output
            bool    finalOutput = false;    // the last output
            bool    showProgress = false;
            int     outputCount = 0;    // number to be output
            int     outputDone = 0;     // number output so far
            std::clock_t outputTime = 0;

            bool    animating = false;      // inside the animation loop
            AbstractSystem* mSystem = nullptr;

            Stats() = default;
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
        static const std::map<std::string, std::pair<const char*, const char*>> ExamplesMap;
protected:
        static const std::array<const FileChar*, NumberofTempTypes> TempPrefixes;
        static const std::array<const FileChar*, NumberofTempTypes> TempSuffixes;
        static const FileChar* TempPrefixAll;
        virtual void clearAndCR() {};
};

class Canvas {
    public:
        virtual void start(bool , const agg::rgba& , int , int ) 
        { mTime = clock(); }
        virtual void end()
        { mTime = clock() - mTime; }

        virtual void primitive(int, RGBA8 , agg::trans_affine , agg::comp_op_e ) = 0;
        virtual void path(RGBA8, agg::trans_affine, const AST::CommandInfo& ) = 0;

        Canvas(int width, int height) 
        : mWidth(width), mHeight(height), mError(false) {}
        virtual ~Canvas();
        
        int mWidth;
        int mHeight;
        std::clock_t mTime = (std::clock_t)(-1);
        bool mError;
        std::string mFileName;
};

class Renderer;
class CFDG;

using cfdg_ptr = std::shared_ptr<CFDG>;
using renderer_ptr = std::unique_ptr<Renderer>;

class CFDG {
    public:
        enum frieze_t { no_frieze = 0, frieze_x, frieze_y };
        static cfdg_ptr ParseFile(const char* fname, AbstractSystem*,
                                  int variation, std::string defs = "");
        virtual ~CFDG();

        virtual renderer_ptr renderer(const cfdg_ptr& ptr,
                int width, int height, double minSize,
                int variation, double border = 2.0
            ) = 0;
            // caller must delete returned object

        bool usesColor = false;
        bool usesAlpha = false;
        bool uses16bitColor = false;
        bool usesBlendMode = false;
        bool usesTime = false;
        bool usesFrameTime = false;
        static const CfgArray<std::string>  ParamNames;
        static CFG lookupCfg(const std::string& name);
        static const std::string& getCfgName(int c);
        static std::string ShapeToString(int shape);
        static const AST::ASTparameters* ShapeToParams(int shape);
        virtual bool isTiled(agg::trans_affine* tr = nullptr, double* x = nullptr, double* y = nullptr) const = 0;
        virtual frieze_t isFrieze(agg::trans_affine* tr = nullptr, double* x = nullptr, double* y = nullptr) const = 0;
        virtual bool isTiledOrFrieze() const = 0;
        virtual bool isSized(double* x = nullptr, double* y = nullptr) const = 0;
        virtual bool isTimed(agg::trans_affine_time* t = nullptr) const = 0;
        virtual const agg::rgba& getBackgroundColor() = 0;
        virtual void serialize(std::ostream&) = 0;

    protected:
        CFDG() = default;
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

        std::atomic_bool requestStop;     // stop ASAP
        std::atomic_bool requestFinishUp; // stop expanding, and do final output
        std::atomic_bool requestUpdate;   // call stats() soon
        
        int m_width;
        int m_height;
        std::unique_ptr<tiledCanvas> m_tiledCanvas;
    
        static double Infinity;
        static std::atomic_bool   AbortEverything;
        static unsigned ParamCount;
    protected:
        Renderer(int w, int h);
};

#endif
