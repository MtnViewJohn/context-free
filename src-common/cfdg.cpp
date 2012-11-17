/*
 *

 Context Free Design Grammar - version 0.2

 Copyright (C) 2005 Chris Coyne - ccoyne77@gmail.com
 Copyright (C) 2005 Mark Lentczner - markl@glyphic.com
 Copyright (C) 2005 John Horigan - john@glyphic.com

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
#include <math.h>
#include "astexpression.h"
#include "scanner.h"
#include "cfdg.tab.hpp"
#include <limits>
#include "tiledCanvas.h"

using namespace std;


yy::location CfdgError::Default;
double Renderer::Infinity = numeric_limits<double>::infinity();      // Ignore the gcc warning

CfdgError::CfdgError(const yy::location& loc, const char* msg)
: what(msg), where(loc)
{
    where.begin.column -= Default.begin.column;
    where.end.column -= Default.end.column;
}

CfdgError::CfdgError(const char* msg)
: what(msg), where(Default)
{
    where.begin.column = 0;
    where.end.column = 0;
}


void
CfdgError::Error(const yy::location& errLoc, const char* msg)
{
    if (Builder::CurrentBuilder)
        Builder::CurrentBuilder->error(errLoc, msg);
    else
        throw CfdgError(errLoc, msg);
}

void
CfdgError::Warning(const yy::location& errLoc, const char* msg)
{
    if (Builder::CurrentBuilder)
        Builder::CurrentBuilder->warning(errLoc, msg);
}


AbstractSystem::~AbstractSystem() { }

void AbstractSystem::stats(const Stats&)
    { }

Canvas::~Canvas() { }

Renderer::~Renderer() { delete mCurrentPath; delete m_tiledCanvas; }



CFDG::~CFDG() { }


CFDG*
CFDG::ParseFile(const char* fname, AbstractSystem* system, int variation)
{
    CFDGImpl* pCfdg = NULL;
    for (int version = 2; version <= 4; ++version) {
        if (pCfdg == NULL)
            pCfdg = new CFDGImpl(system); 
        Builder b(pCfdg, variation);

        yy::Scanner lexer;
        b.lexer = &lexer;
        lexer.driver = &b;
        lexer.startToken = version == 2 ? yy::CfdgParser::token::CFDG2 : 
                                          yy::CfdgParser::token::CFDG3;
        b.mCompilePhase = version < 4 ? 1 : 2;
        b.mWant2ndPass = version == 3;
        
        yy::CfdgParser parser(b);
        istream* input = system->openFileForRead(fname);
        if (!input || !input->good()) {
            delete input;
            input = 0;
            system->error();
            system->message("Couldn't open rules file %s", fname);
            return 0;
        }
        
        pCfdg->fileNames.push_back(fname);
        b.m_currentPath = &(pCfdg->fileNames.back());
        b.m_basePath = b.m_currentPath;
        b.m_filesToLoad.push(b.m_currentPath);
        b.m_streamsToLoad.push(input);
        b.m_includeNamespace.push(false);
        
        if (version == 2)
            system->message("Reading rules file %s", fname);

        lexer.yyrestart(input);
        //parser.set_debug_level(1);
        
        int yyresult = 0;
        try {
            yyresult = parser.parse();
        } catch (CfdgError err) {
            system->syntaxError(err);
            return 0;
        }

        if (b.mErrorOccured)
            return 0;
        if (yyresult == 0) {
            pCfdg->rulesLoaded();
            if (b.mErrorOccured)
                return 0;
            if (b.mWant2ndPass) {
                pCfdg = new CFDGImpl(pCfdg);
                system->message("Compiling 2nd phase");
                continue;
            }
            b.m_CFDG = 0;
            break;
        }
        if (lexer.maybeVersion == 0 || 
            lexer.maybeVersion == (version == 2 ? yy::CfdgParser::token::CFDG2 : 
                                                  yy::CfdgParser::token::CFDG3))
            return 0;
        system->message("Restarting as a version 3 design");
        pCfdg = NULL;
    }
    
    system->message("%d rules loaded", pCfdg->numRules());
    
    return pCfdg;
}

void
Renderer::init()
{
    mLastPoint.x = mLastPoint.y = 0.0;
    mStop = false;
    mClosed = false;
    mWantMoveTo = true;
    mWantCommand = true;
    mIndex = mNextIndex = 0;
}

bool
Renderer::isNatural(Renderer* r, double n)
{
    return n >= 0 && n <= (r ? r->mMaxNatural : Builder::MaxNatural) && n == floor(n);
}

void
Renderer::initStack(const StackType* p)
{
    if (p && p->ruleHeader.mParamCount) {
        for (unsigned i = 0; i < p->ruleHeader.mParamCount; ++i)
            mCFstack.push_back(p[i + 2]);
    }
    if (!mCFstack.empty()) {
        mLogicalStackTop = &(mCFstack.back()) + 1;
    } else {
        mLogicalStackTop = NULL;
    }
}

void
Renderer::unwindStack(size_t oldsize, const std::vector<AST::ASTparameter>& params)
{
    if (oldsize == mCFstack.size())
        return;

    StackType* pos = &(mCFstack[oldsize]);
    for (std::vector<AST::ASTparameter>::const_iterator it = params.begin(), p_end = params.end();
         it != p_end; ++it)
    {
        if (it->isLoopIndex) continue;  // loop indices are unwound in ASTloop::traverse()
        if (it->mType == AST::ASTexpression::RuleType)
            pos->rule->release();
        pos += it->mTuplesize;
        if (pos > &(mCFstack.back()))
            break;                      // no guarantee entire frame was computed
    }
    mCFstack.resize(oldsize, mCFstack.back());
    if (oldsize)
        mLogicalStackTop = &(mCFstack[0]) + oldsize;
    else
        mLogicalStackTop = NULL;
}
