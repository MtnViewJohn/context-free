/*
 *

 Context Free Design Grammar - version 0.2

 Copyright (C) 2005 Chris Coyne - ccoyne77@gmail.com
 Copyright (C) 2005-2008 Mark Lentczner - markl@glyphic.com
 Copyright (C) 2005-2013 John Horigan - john@glyphic.com

 [Send me anything cool you make with it or of it.]

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License as published
 by the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 02111-1307  USA

 *
 */


#include "cfdg.h"

#include <string>
#include <cstring>

#include "builder.h"
#include "cfdgimpl.h"
#include <cmath>
#include "astexpression.h"
#include "scanner.h"
#include "cfdg.tab.hpp"
#include <limits>
#include "tiledCanvas.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <streambuf>
#include <istream>


yy::location CfdgError::Default;
double Renderer::Infinity = std::numeric_limits<double>::infinity();      // Ignore the gcc warning
std::atomic_bool Renderer::AbortEverything{false};
unsigned Renderer::ParamCount = 0;
const CfgArray<std::string> CFDG::ParamNames = {
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
    "CF::MaxNatural",
    "CF::MaxShapes",
    "CF::MinimumSize",
    "CF::Size",
    "CF::StartShape",
    "CF::Symmetry",
    "CF::Tile",
    "CF::Time"
};

CFG
CFDG::lookupCfg(const std::string& name)
{
    auto nameIt = std::find(ParamNames.begin(), ParamNames.end(), name);
    if (nameIt == ParamNames.end())
        return CFG::Unknown;
    
    return static_cast<CFG>(nameIt - ParamNames.begin());
}

const std::string&
CFDG::getCfgName(int c)
{
    static const std::string unknown = "unknown configuration variable";
    if (c >= 0 && c < static_cast<int>(CFG::_NumberOf))
        return ParamNames[c];
    return unknown;
}

static CFDGImpl* LatestCFDGimpl = nullptr;

std::string
CFDG::ShapeToString(int shape)
{
    if (LatestCFDGimpl)
        return LatestCFDGimpl->decodeShapeName(shape);
    else
        return "unknown";
}

const AST::ASTparameters*
CFDG::ShapeToParams(int shape)
{
    if (LatestCFDGimpl)
        return LatestCFDGimpl->getShapeParams(shape);
    else
        return nullptr;
}

CfdgError::CfdgError(const yy::location& loc, const char* msg)
: where(loc), mMsg(msg)
{
    where.begin.column -= Default.begin.column;
    where.end.column -= Default.end.column;
}

CfdgError::CfdgError(const char* msg)
: where(Default), mMsg(msg)
{
    where.begin.column = 0;
    where.end.column = 0;
}

const char*
CfdgError::what() const noexcept
{
    return mMsg;
}

const char*
DeferUntilRuntime::what() const noexcept
{
    return "Compile time action should be deferred to run time.";
}

void
CfdgError::Error(const yy::location& errLoc, const char* msg, Builder* b)
{
    if (b) {
        b->error(errLoc, msg);
        return;
    }
    
    std::lock_guard<std::recursive_mutex> lock(Builder::BuilderMutex);
    
    if (Builder::CurrentBuilder && Builder::CurrentBuilder->isMyBuilder())
        Builder::CurrentBuilder->error(errLoc, msg);
    else
        throw CfdgError(errLoc, msg);
}

void
CfdgError::Warning(const yy::location& errLoc, const char* msg)
{
    std::lock_guard<std::recursive_mutex> lock(Builder::BuilderMutex);
    
    if (Builder::CurrentBuilder && Builder::CurrentBuilder->isMyBuilder())
        Builder::CurrentBuilder->warning(errLoc, msg);
}

const std::array<const AbstractSystem::FileChar*, AbstractSystem::NumberofTempTypes> AbstractSystem::TempPrefixes = {
    FileStr("cfdg-temp-fin-"),
    FileStr("cfdg-temp-unfin-"),
    FileStr("cfdg-temp-mrg-"),
    FileStr("cfdg-temp-movie-")
};
const std::array<const AbstractSystem::FileChar*, AbstractSystem::NumberofTempTypes> AbstractSystem::TempSuffixes = {
    FileStr(""), FileStr(""), FileStr(""), FileStr(".mov")
};
const AbstractSystem::FileChar* AbstractSystem::TempPrefixAll = FileStr("cfdg-temp-");

AbstractSystem::~AbstractSystem() = default;

void AbstractSystem::stats(const Stats&)
    { }

AbstractSystem::istr_ptr
AbstractSystem::tempFileForRead(const FileString& path)
{
    return std::make_unique<std::ifstream>(path.c_str(), std::ios::binary);
}

struct membuf : std::streambuf {
    membuf(char const* base, std::size_t size) {
        char* p(const_cast<char*>(base));
        this->setg(p, p, p + size);
    }
};
struct imemstream : virtual membuf, std::istream {
    imemstream(char const* base, std::size_t size)
        : membuf(base, size)
        , std::istream(static_cast<std::streambuf*>(this)) {
    }
};

AbstractSystem::istr_ptr
AbstractSystem::openFileForRead(const std::string& path)
{
    if (!mFirstCfdgRead) {
        char dirchar =
#ifdef _WIN32
            '\\';
#else
            '/';
#endif
        auto dirloc = path.rfind(dirchar);
        auto exfile = path.substr(dirloc == std::string::npos ? 0 : dirloc + 1);

        auto example = ExamplesMap.find(exfile);
        if (example != ExamplesMap.end()) {
            auto [v3cfdg, v2cfdg] = example->second;
            auto cfdg = cfdgVersion == 2 ? v2cfdg : v3cfdg;
            return std::make_unique<imemstream>(cfdg, std::strlen(cfdg));
        }
    } else {
        mFirstCfdgRead = false;
    }

    istr_ptr f = std::make_unique<std::ifstream>(path.c_str(), std::ios::binary);
    if (f && !f->good())
        f.reset();

    return f;
}

Canvas::~Canvas() = default;

Renderer::Renderer(int w, int h)
: requestStop(false),
  requestFinishUp(false),
  requestUpdate(false),
  m_width(w), m_height(h)
{ }

Renderer::~Renderer() = default;



CFDG::~CFDG() = default;


cfdg_ptr
CFDG::ParseFile(const char* fname, AbstractSystem* system, int variation,
                std::string defs)
{
    cfdgi_ptr pCfdg;
    for (int version = 2; version <= 3; ++version) {
        if (!defs.empty() && version == 2) {
            system->message("Pre-definitions found, assuming version 3 syntax.");
            continue;       // Predefines are only allowed with v3 syntax
        }
        system->cfdgVersion = version;
        system->mFirstCfdgRead = true;
        if (!pCfdg)
            pCfdg = std::make_unique<CFDGImpl>(system);
        Builder b(pCfdg, variation);
        pCfdg->m_builder = &b;
        LatestCFDGimpl = pCfdg.get();

        yy::Scanner lexer;
        b.lexer = &lexer;
        lexer.driver = &b;
        lexer.startToken = version == 2 ? yy::CfdgParser::token::CFDG2 : 
                                          yy::CfdgParser::token::CFDG3;
        
        yy::CfdgParser parser(b);
        AbstractSystem::istr_ptr input;
        if (defs.empty()) {
            input = system->openFileForRead(fname);
        } else {
            defs.append("import \"");
            defs.append(fname);
            defs += '"';
            fname = "pre-defines buffer";
            input = std::make_unique<std::istringstream>(defs.c_str());
            b.mIncludeDepth = -1;   // pre-defs buffer is at level -1
        }
        if (!input || !input->good()) {
            system->error();
            system->message("Couldn't open rules file %s", fname);
            return nullptr;
        }
        
        b.m_CFDG->fileNames.push_back(fname);
        b.m_currentPath = &(b.m_CFDG->fileNames.back());
#ifdef _MSC_VER
            static char dirchar = '\\';
#else
            static char dirchar = '/';
#endif
        {
            auto dirptr = b.m_currentPath->find_last_of(dirchar);
            if (dirptr == std::string::npos)
                b.m_basePath = std::make_unique<std::string>(*b.m_currentPath);
            else
                b.m_basePath = std::make_unique<std::string>(*b.m_currentPath, 0, dirptr+1);
        }
        b.m_filesToLoad.push(b.m_currentPath);
        b.m_streamsToLoad.push(std::move(input));
        b.m_includeNamespace.push(false);
        b.push_repContainer(b.m_CFDG->mCFDGcontents);
        
        if (version == 2) {
            const char* miniName = std::strrchr(fname, dirchar);
            if (!miniName)
                miniName = fname;
            if (miniName != fname)
                --miniName;
            while (miniName != fname && *miniName != dirchar)
                --miniName;
            if (miniName != fname)
                system->message("Reading rules file ...%s", miniName);
            else
                system->message("Reading rules file %s", fname);
        }

        lexer.yyrestart(b.m_streamsToLoad.top().get());
        //parser.set_debug_level(1);
        
        int yyresult = 0;
        try {
            yyresult = parser.parse();
        } catch (CfdgError& err) {
            system->syntaxError(err);
            LatestCFDGimpl = nullptr;
            return nullptr;
        }
        
        b.pop_repContainer(nullptr);    // pCfdg->mCFDGcontents

        if (b.mErrorOccured)
            return nullptr;
        if (yyresult == 0) {
            b.m_CFDG->rulesLoaded();
            if (b.mErrorOccured)
                return nullptr;
            break;
        }
        if (lexer.maybeVersion == 0 || 
            lexer.maybeVersion == (version == 2 ? yy::CfdgParser::token::CFDG2 : 
                                                  yy::CfdgParser::token::CFDG3))
            return nullptr;
        system->message("Restarting as a version 3 design");
        pCfdg.reset();
        LatestCFDGimpl = nullptr;
    }
    
    if (pCfdg) {
        pCfdg->m_builder = nullptr;
        system->message("%d rules loaded", pCfdg->numRules());
    }
    
    return cfdg_ptr(pCfdg);
}

// Sketchy as fuck, I know
#include "examples.h"
