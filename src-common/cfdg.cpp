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

#include "builder.h"
#include "cfdgimpl.h"
#include <string.h>
#include <cmath>
#include "astexpression.h"
#include "scanner.h"
#include "cfdg.tab.hpp"
#include <limits>
#include "tiledCanvas.h"
#include <fstream>


yy::location CfdgError::Default;
double Renderer::Infinity = std::numeric_limits<double>::infinity();      // Ignore the gcc warning
bool Renderer::AbortEverything = false;
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

CfdgError&
CfdgError::operator=(const CfdgError& e) noexcept
{
    if (this == &e) return *this;
    mMsg = e.mMsg;
    where = e.where;
    return *this;
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

const char* AbstractSystem::TempPrefixes[AbstractSystem::NumberofTempTypes] = {
    "cfdg-temp-fin-", "cfdg-temp-unfin-", "cfdg-temp-mrg-", "cfdg-temp-movie-"
};
const char* AbstractSystem::TempSuffixes[AbstractSystem::NumberofTempTypes] = {
    "", "", "", ".mov"
};
const char* AbstractSystem::TempPrefixAll = "cfdg-temp-";
const wchar_t* AbstractSystem::TempPrefixes_w[AbstractSystem::NumberofTempTypes] = {
    L"cfdg-temp-fin-", L"cfdg-temp-unfin-", L"cfdg-temp-mrg-", L"cfdg-temp-movie"
};
const wchar_t* AbstractSystem::TempSuffixes_w[AbstractSystem::NumberofTempTypes] = {
    L"", L"", L"", L".mov"
};
const wchar_t* AbstractSystem::TempPrefixAll_w = L"cfdg-temp-";

AbstractSystem::~AbstractSystem() = default;

void AbstractSystem::stats(const Stats&)
    { }

std::istream*
AbstractSystem::tempFileForRead(const FileString& path)
{
    return new std::ifstream(path.c_str(), std::ios::binary);
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
CFDG::ParseFile(const char* fname, AbstractSystem* system, int variation)
{
    cfdgi_ptr pCfdg;
    for (int version = 2; version <= 3; ++version) {
        system->cfdgVersion = version;
        if (!pCfdg)
            pCfdg = std::make_unique<CFDGImpl>(system);
        Builder b(pCfdg, variation);
        pCfdg->m_builder = &b;

        yy::Scanner lexer;
        b.lexer = &lexer;
        lexer.driver = &b;
        lexer.startToken = version == 2 ? yy::CfdgParser::token::CFDG2 : 
                                          yy::CfdgParser::token::CFDG3;
        
        yy::CfdgParser parser(b);
        std::unique_ptr<std::istream> input(system->openFileForRead(fname));
        if (!input || !input->good()) {
            system->error();
            system->message("Couldn't open rules file %s", fname);
            return nullptr;
        }
        
        b.m_CFDG->fileNames.push_back(fname);
        b.m_currentPath = &(b.m_CFDG->fileNames.back());
        {
#ifdef _MSC_VER
            static char dirchar = '\\';
#else
            static char dirchar = '/';
#endif
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
        
        if (version == 2)
            system->message("Reading rules file %s", fname);

        lexer.yyrestart(b.m_streamsToLoad.top().get());
        //parser.set_debug_level(1);
        
        int yyresult = 0;
        try {
            yyresult = parser.parse();
        } catch (CfdgError& err) {
            system->syntaxError(err);
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
    }
    
    if (pCfdg) {
        pCfdg->m_builder = nullptr;
        system->message("%d rules loaded", pCfdg->numRules());
    }
    
    return cfdg_ptr(pCfdg);
}
