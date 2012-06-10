// builder.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2005-2009 John Horigan - john@glyphic.com
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


#ifndef INCLUDE_BUILDER_H
#define INCLUDE_BUILDER_H

#ifdef _WIN32
#pragma warning( disable : 4786 )
#endif

#include <queue>
#include <stack>
#include <string>
#include <cstdlib>
#include <map>
#include "agg_basics.h"
#include "Rand64.h"

#include "shape.h"
#include "cfdg.h"
#include "astreplacement.h"

class CFDGImpl;
namespace yy {
    class location;
}

namespace yy {
    class Scanner;
}

class Builder {
public:
    static Builder* CurrentBuilder;

    CFDGImpl*       m_CFDG;
    std::stack<std::string*>   m_filesToLoad;
    std::stack<std::istream*> m_streamsToLoad;
    std::stack<bool>            m_includeNamespace;
    std::string*          m_currentPath;
    std::string*          m_basePath;
    int             m_pathCount;
    bool            mInPathContainer;
    
    std::string     mCurrentNameSpace;
    
	int				mCurrentShape;
    Rand64          mSeed;
    
    bool            mWant2ndPass;
    int             mCompilePhase;
    
    AST::ASTrepContainer mParamDecls;
    bool            isFunction;
    
    static std::map<std::string, int> FlagNames;
    
    int mLocalStackDepth;
    
    unsigned    mIncludeDepth;
    
    bool        mAllowOverlap;
    
    typedef std::deque<AST::ASTrepContainer*> ContainerStack_t;
    ContainerStack_t    mContainerStack;
    void                push_repContainer(AST::ASTrepContainer& c);
    void                pop_repContainer(AST::ASTreplacement* r);
    void                push_paramDecls(const std::string& name, 
                                        const yy::location& defLoc,
                                        const std::string & type);
    void                push_rep(AST::ASTreplacement* r, bool global = false);
    const char*         push_param();
    AST::ASTparameter*  findExpression(int nameIndex, bool& isGlobal);
    void                process_repContainer(AST::ASTrepContainer& c);
    
    std::stack<AST::ASTswitch*> switchStack;
    
    yy::Scanner*    lexer;
    void    warning(const yy::location& errLoc, const std::string& msg);
    void    error(const yy::location& errLoc, const std::string& msg);
    void    error(int line, const char* msg);
    bool    mErrorOccured;
    
    Builder(CFDGImpl* cfdg, int variation);
    ~Builder();
    
    int             StringToShape(const std::string& name, const yy::location& loc,
                                  bool colonsAllowed);
    void            PushNameSpace(AST::str_ptr n, const yy::location& loc);
    void            CheckName(const std::string& name, const yy::location& loc,
                              bool colonsAllowed);
    void            CheckVariableName(int index, const yy::location& loc);
    void            PopNameSpace();
    void            IncludeFile(const std::string& fname);
    bool            EndInclude();
    void            Initialize(AST::rep_ptr init);
    void            SetShape(AST::ASTshape* s, bool isPath = false);
    void            AddRule(AST::ASTrule* rule);
	void            NextParameterDecl(const std::string& type, const std::string& name,
                                      const yy::location& typeLoc, const yy::location& nameLoc);
	void            NextParameter(const std::string& name, AST::exp_ptr e,
                                  const yy::location& nameLoc, const yy::location& expLoc);
    AST::ASTexpression*  
                    MakeVariable(const std::string& name, const yy::location& loc);
    AST::ASTruleSpecifier*  
                    MakeRuleSpec(const std::string& name, AST::exp_ptr a, const yy::location& loc);
    void            MakeModTerm(AST::ASTtermArray& dest, AST::term_ptr t);
    AST::rep_ptr    MakeElement(const std::string& s, AST::mod_ptr mods, AST::exp_ptr params, 
                                const yy::location& loc, bool subPath);
    AST::ASTexpression*
                    MakeFunction(AST::str_ptr name, AST::exp_ptr args, const yy::location& nameLoc, 
                                 const yy::location& argsLoc, bool consAllowed);
    AST::ASTexpression*
                    MakeArray(AST::str_ptr name, AST::exp_ptr args, const yy::location& nameLoc, 
                                const yy::location& argsLoc);
    AST::ASTexpression*
                    MakeLet(const yy::location& letLoc, AST::exp_ptr exp);
    AST::ASTmodification*
                    MakeModification(AST::mod_ptr modExp, const yy::location& loc,
                                     bool canonical);
    void            inColor();
    void            timeWise();
};

#endif // INCLUDE_BUILDER_H
