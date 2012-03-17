// builder.cpp
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


#include "builder.h"
#include "astreplacement.h"

#define _USE_MATH_DEFINES

#include "agg_trans_affine.h"
#include "agg_path_storage.h"
#include "agg_basics.h"
#include "cfdgimpl.h"
#include "primShape.h"
#include <string.h>
#include <math.h>
#include <typeinfo>
#include <cassert>
#include <limits>
#include "scanner.h"
#include <cstring>

using namespace AST;

std::map<std::string, int> Builder::FlagNames;
Builder* Builder::CurrentBuilder = 0;

Builder::Builder(CFDGImpl* cfdg, int variation)
: m_CFDG(cfdg), m_currentPath(0), m_basePath(0), m_pathCount(1), 
  mInPathContainer(false), mCurrentShape(-1),
  mWant2ndPass(false), mCompilePhase(1), isFunction(false),
  mLocalStackDepth(0), mIncludeDepth(0), mAllowOverlap(false), lexer(0), 
  mErrorOccured(false)
{ 
    //CommandInfo::shapeMap[0].mArea = M_PI * 0.25;
    mSeed.seed((unsigned long long)variation); 
    if (FlagNames.empty()) {
        FlagNames.insert(std::pair<std::string, int>("CF::None", AST::CF_NONE));
        FlagNames.insert(std::pair<std::string, int>("CF::MiterJoin", AST::CF_MITER_JOIN | AST::CF_JOIN_PRESENT));
        FlagNames.insert(std::pair<std::string, int>("CF::RoundJoin", AST::CF_ROUND_JOIN | AST::CF_JOIN_PRESENT));
        FlagNames.insert(std::pair<std::string, int>("CF::BevelJoin", AST::CF_BEVEL_JOIN | AST::CF_JOIN_PRESENT));
        FlagNames.insert(std::pair<std::string, int>("CF::ButtCap", AST::CF_BUTT_CAP | AST::CF_CAP_PRESENT));
        FlagNames.insert(std::pair<std::string, int>("CF::RoundCap", AST::CF_ROUND_CAP | AST::CF_CAP_PRESENT));
        FlagNames.insert(std::pair<std::string, int>("CF::SquareCap", AST::CF_SQUARE_CAP | AST::CF_CAP_PRESENT));
        FlagNames.insert(std::pair<std::string, int>("CF::ArcCW", AST::CF_ARC_CW));
        FlagNames.insert(std::pair<std::string, int>("CF::ArcLarge", AST::CF_ARC_LARGE));
        FlagNames.insert(std::pair<std::string, int>("CF::Continuous", AST::CF_CONTINUOUS));
        FlagNames.insert(std::pair<std::string, int>("CF::Align", AST::CF_ALIGN));
        FlagNames.insert(std::pair<std::string, int>("CF::EvenOdd", AST::CF_EVEN_ODD));
        FlagNames.insert(std::pair<std::string, int>("CF::IsoWidth", AST::CF_ISO_WIDTH));
        FlagNames.insert(std::pair<std::string, int>("~~CF_FILL~~", AST::CF_FILL));
        FlagNames.insert(std::pair<std::string, int>("CF::Cyclic", AST::CF_CYCLIC));
        FlagNames.insert(std::pair<std::string, int>("CF::Dihedral", AST::CF_DIHEDRAL));
        FlagNames.insert(std::pair<std::string, int>("CF::p11g", AST::CF_P11G));
        FlagNames.insert(std::pair<std::string, int>("CF::p11m", AST::CF_P11M));
        FlagNames.insert(std::pair<std::string, int>("CF::p1m1", AST::CF_P1M1));
        FlagNames.insert(std::pair<std::string, int>("CF::p2", AST::CF_P2));
        FlagNames.insert(std::pair<std::string, int>("CF::p2mg", AST::CF_P2MG));
        FlagNames.insert(std::pair<std::string, int>("CF::p2mm", AST::CF_P2MM));
        FlagNames.insert(std::pair<std::string, int>("CF::pm", AST::CF_PM));
        FlagNames.insert(std::pair<std::string, int>("CF::pg", AST::CF_PG));
        FlagNames.insert(std::pair<std::string, int>("CF::cm", AST::CF_CM));
        FlagNames.insert(std::pair<std::string, int>("CF::pmm", AST::CF_PMM));
        FlagNames.insert(std::pair<std::string, int>("CF::pmg", AST::CF_PMG));
        FlagNames.insert(std::pair<std::string, int>("CF::pgg", AST::CF_PGG));
        FlagNames.insert(std::pair<std::string, int>("CF::cmm", AST::CF_CMM));
        FlagNames.insert(std::pair<std::string, int>("CF::p4", AST::CF_P4));
        FlagNames.insert(std::pair<std::string, int>("CF::p4m", AST::CF_P4M));
        FlagNames.insert(std::pair<std::string, int>("CF::p4g", AST::CF_P4G));
        FlagNames.insert(std::pair<std::string, int>("CF::p3", AST::CF_P3));
        FlagNames.insert(std::pair<std::string, int>("CF::p3m1", AST::CF_P3M1));
        FlagNames.insert(std::pair<std::string, int>("CF::p31m", AST::CF_P31M));
        FlagNames.insert(std::pair<std::string, int>("CF::p6", AST::CF_P6));
        FlagNames.insert(std::pair<std::string, int>("CF::p6m", AST::CF_P6M));
    }
    assert(Builder::CurrentBuilder == NULL);    // ensure singleton
    Builder::CurrentBuilder = this;
    ASTparameter::Impure = false;
    mContainerStack.push_back(&(cfdg->mCFDGcontents));
    
    if (ASTrule::PrimitivePaths[primShape::circleType] == 0) {
        for (unsigned i = 0; i < primShape::numTypes; ++i) {
            // primShape statics are const because of thread safety issues.
            // But Builder is a singleton and preceeds any thread's access
            // to primShape statics. So this const_cast is ok.
            primShape* map = const_cast<primShape*>(primShape::shapeMap[i]);
            if (map) {
                ASTrule* r = new ASTrule(i, CfdgError::Default);
                ASTrule::PrimitivePaths[i] = r;
                static const std::string  move("MOVETO");
                static const std::string  line("LINETO");
                static const std::string   arc("ARCTO");
                static const std::string close("CLOSEPOLY");
                if (i != primShape::circleType) {
                    map->rewind(0);
                    double x = 0, y = 0;
                    unsigned cmd;
                    while (!agg::is_stop(cmd = map->vertex(&x, &y))) {
                        if (agg::is_vertex(cmd)) {
                            exp_ptr a(new ASTcons(new ASTreal(x, CfdgError::Default), 
                                                  new ASTreal(y, CfdgError::Default)));
                            ASTpathOp* op = new ASTpathOp(agg::is_move_to(cmd) ? move : line,
                                                          a, CfdgError::Default);
                            r->mRuleBody.mBody.push_back(op);
                        }
                    }
                } else {
                    exp_ptr a(new ASTcons(new ASTreal(0.5, CfdgError::Default), 
                                          new ASTreal(0.0, CfdgError::Default)));
                    ASTpathOp* op = new ASTpathOp(move, a, CfdgError::Default);
                    r->mRuleBody.mBody.push_back(op);
                    a.reset(new ASTcons(new ASTreal(-0.5, CfdgError::Default), 
                                        new ASTcons(new ASTreal(0.0, CfdgError::Default), 
                                                    new ASTreal(0.5, CfdgError::Default))));
                    op = new ASTpathOp(arc, a, CfdgError::Default);
                    r->mRuleBody.mBody.push_back(op);
                    a.reset(new ASTcons(new ASTreal(0.5, CfdgError::Default), 
                                        new ASTcons(new ASTreal(0.0, CfdgError::Default), 
                                                    new ASTreal(0.5, CfdgError::Default))));
                    op = new ASTpathOp(arc, a, CfdgError::Default);
                    r->mRuleBody.mBody.push_back(op);
                }
                r->mRuleBody.mBody.push_back(new ASTpathOp(close, exp_ptr(),
                                                           CfdgError::Default));
                r->mRuleBody.mRepType = ASTreplacement::op;
                r->mRuleBody.mPathOp = AST::MOVETO;
            }
        }
    }
}

Builder::~Builder()
{
    pop_repContainer(NULL);
    delete m_CFDG;
    Builder::CurrentBuilder = 0;
    while (!m_streamsToLoad.empty()) {
        delete m_streamsToLoad.top();
        m_streamsToLoad.pop();
    }
}

static const char*
getUniqueFile(const std::string* base, const std::string* file)
{
    const char* b = base->c_str();
    const char* f = file->c_str();
    for (; *b && *f; ++b, ++f) {
        if (*b != *f)
            return f;
    }
    if (*b == '\0' && *f == '\0')
        return NULL;
    return file->c_str();
}


void
Builder::error(const yy::location& l, const std::string& msg)
{
    if (mWant2ndPass) return;
    mErrorOccured = true;
    warning(l, msg);
}

void
Builder::warning(const yy::location& l, const std::string& msg)
{
    CfdgError err(l, msg.c_str());
    if (l.begin.filename) {
        const char* fname = getUniqueFile(m_basePath, l.begin.filename);
        if (fname == 0) {
            m_CFDG->system()->syntaxError(err);
        } else {
            m_CFDG->system()->error();
            m_CFDG->system()->message("Error in %s at line %d - %s", 
                                      fname, err.where.begin.line, msg.c_str());
        }
    } else {
        m_CFDG->system()->error();
        m_CFDG->system()->message("Error - %s", msg.c_str());
    }
}

void Builder::error(int line, const char* msg)
{
    yy::location loc;
    loc.initialize(m_currentPath);
    loc.begin.line = line;
    loc.end.line = line + 1;
    CfdgError err(loc, msg);
    const char* fname = getUniqueFile(m_basePath, loc.begin.filename);
    mErrorOccured = true;
    if (fname == 0) {
        m_CFDG->system()->syntaxError(err);
    } else {
        m_CFDG->system()->message("Error in %s at line %d - %s", 
                                  fname, loc.begin.line, msg);
    }
}

static bool
stringcompare(const char *lhs, const char *rhs) {
    return std::strcmp(lhs, rhs) < 0;
}

int
Builder::StringToShape(const std::string& name, const yy::location& loc,
                       bool colonsAllowed)
{
    CheckName(name, loc, colonsAllowed);
    if (mCurrentNameSpace.length() == 0) {
        return m_CFDG->encodeShapeName(name);
    } else {
        static const char* const Globals[] = {
            "CIRCLE", "FILL", "SQUARE", "TRIANGLE"
        };
        bool maybeGlobal = std::binary_search(Globals, Globals + 4, name.c_str(), stringcompare);
        std::string n(mCurrentNameSpace);
        n.append(name);
        if (maybeGlobal && m_CFDG->tryEncodeShapeName(n) == -1)
            return m_CFDG->encodeShapeName(name);
        else
            return m_CFDG->encodeShapeName(n);
    }
}

// Switch parser input to a new file
void
Builder::IncludeFile(const std::string& fname)
{
    std::string path =
        m_CFDG->system()->relativeFilePath(*m_currentPath, fname.c_str());
    std::istream* input = m_CFDG->system()->openFileForRead(path);
    if (!input || !input->good()) {
        delete input;
        input = 0;
        m_CFDG->system()->error();
        m_CFDG->system()->message("Couldn't open rules file %s", path.c_str());
        return;
    }
    
    m_CFDG->fileNames.push_back(path);
    m_currentPath = &(m_CFDG->fileNames.back());
    m_filesToLoad.push(m_currentPath);
    m_streamsToLoad.push(input);
    m_includeNamespace.push(false);
    ++m_pathCount;
    ++mIncludeDepth;
    mCurrentShape = -1;
    SetShape(NULL);
    
    m_CFDG->system()->message("Reading rules file %s", fname.c_str());
    
    lexer->yypush_buffer_state(lexer->yy_create_buffer(input, 16384));
    lexer->nextLocAction = yy::Scanner::pushLoc;
}

// Return parser input to previous file
bool
Builder::EndInclude()
{
    bool endOfInput = mIncludeDepth == 0;
    SetShape(NULL);
    lexer->yypop_buffer_state();
    lexer->nextLocAction = yy::Scanner::popLoc;
    --mIncludeDepth;
    
    if (m_streamsToLoad.empty())
        return endOfInput;
    
    if (m_includeNamespace.top())
        PopNameSpace();
    delete m_streamsToLoad.top();
    m_streamsToLoad.pop();
    m_filesToLoad.pop();
    m_includeNamespace.pop();
    m_currentPath = m_filesToLoad.empty() ? NULL : m_filesToLoad.top();
    return endOfInput;
}

// Store parsed contents of startshape lines
void
Builder::Initialize(rep_ptr init)
{
    m_CFDG->setInitialShape(init, mIncludeDepth);
}

void
Builder::SetShape(AST::ASTshape* s)
{
    if (s == NULL) {
        mCurrentShape = -1;
        return;
    }
    if (m_CFDG->findFunction(s->mNameIndex))
        CfdgError::Warning(s->mLocation, "There is a function with the same name as this shape");
	mCurrentShape = s->mNameIndex;
    if (s->mShapeSpec.argSize && m_CFDG->getShapeHasNoParams(mCurrentShape))
        mWant2ndPass = true;
    const char* err = m_CFDG->setShapeParams(mCurrentShape, s->mRules, s->mShapeSpec.argSize);
    if (err)
        CfdgError::Error(s->mLocation, err);
}

void
Builder::AddRule(ASTrule* rule)
{
    bool isShapeItem = rule->mNameIndex == -1;
    
    if (isShapeItem)
        rule->mNameIndex = mCurrentShape;
    else
        mCurrentShape = -1;
    
    if (rule->mNameIndex == -1) {
        CfdgError::Error(rule->mLocation, "Shape rules/paths must follow a shape declaration");
        return;
    }

    int type = m_CFDG->getShapeType(rule->mNameIndex);
    if ((rule->isPath &&  type == CFDGImpl::ruleType) ||
        (!rule->isPath && type == CFDGImpl::pathType))
        CfdgError::Error(rule->mLocation, "Cannot mix rules and shapes with the same name.");
    if (rule->isPath && type != CFDGImpl::newShape)
        CfdgError::Error(rule->mLocation, "A given path can only be defined once");
    
    bool matchesShape = m_CFDG->addRule(rule);
    
    if (!isShapeItem && matchesShape)
        CfdgError::Error(rule->mLocation, "Rule/path name matches existing shape name");
}

void
Builder::NextParameterDecl(const std::string& type, const std::string& name,
                           const yy::location& typeLoc, const yy::location& nameLoc) 
{
    int nameIndex = StringToShape(name, nameLoc, false);
    mParamDecls.addParameter(type, nameIndex, typeLoc, nameLoc);
    CheckVariableName(nameIndex, nameLoc);
}

void
Builder::NextParameter(const std::string& name, exp_ptr e,
                       const yy::location& nameLoc, const yy::location& expLoc) 
{
    if (isFunction) {
        pop_repContainer(NULL);         // pop mParamDecls
        mParamDecls.mParameters.clear();
        mParamDecls.mStackCount = 0;
    }
    if (strncmp(name.c_str(), "CF::", 4) == 0) {
        if (isFunction)
            CfdgError::Error(nameLoc, "Configuration parameters cannot be functions");
        if (!mContainerStack.back()->isGlobal)
            CfdgError::Error(nameLoc, "Configuration parameters must be at global scope");
        if (name == "CF::Impure") {
            double v = 0.0;
            if (!e->isConstant || e->evaluate(&v, 1) != 1) {
                CfdgError::Error(expLoc, "CF::Impure requires a constant numeric expression");
            } else {
                ASTparameter::Impure = v != 0.0;
            }
            return;
        }
        if (name == "CF::AllowOverlap") {
            double v = 0.0;
            if (!e->isConstant || e->evaluate(&v, 1) != 1) {
                CfdgError::Error(expLoc, "CF::AllowOverlap requires a constant numeric expression");
            } else {
                mAllowOverlap = v != 0.0;
            }
            return;
        }
        e.reset(e.release()->simplify());
        if (!m_CFDG->addParameter(name, e, mIncludeDepth))
            warning(nameLoc, "Unknown configuration parameter");
        return;
    } 
 
    int nameIndex = StringToShape(name, nameLoc, false);
    ASTdefine* def = m_CFDG->findFunction(nameIndex);
    yy::location defLoc = nameLoc + expLoc;
    if (isFunction) {
        assert(def);
        delete def->mExpression;                        // Replace placeholder with actual expression
        def->mExpression = e.release()->simplify();
        def->isConstant = def->mExpression->isConstant;
        def->mLocation = defLoc;

        if (def->mExpression->mType != ASTexpression::NumericType) {
            CfdgError::Error(expLoc, "User functions must have numeric type only");
        } else {
            def->mTuplesize = def->mExpression->evaluate(0, 0);
        }
        isFunction = false;
        return;
    } else if (def) {
        CfdgError::Error(nameLoc, "Definition with same name as user function");
        CfdgError::Error(def->mLocation, "    user function definition is here.");
        def = 0;
    }

    CheckVariableName(nameIndex, nameLoc);
    ASTmodification* m = dynamic_cast<ASTmodification*> (e.get());
    if (m) {
        mod_ptr mod(m); e.release();
        def = new ASTdefine(name, mod, defLoc);
    } else {
        def = new ASTdefine(name, e, defLoc);
    }
    ASTrepContainer* top = mContainerStack.back();
    ASTparameter& b = top->addParameter(nameIndex, def, nameLoc, expLoc);
 
    if (!b.mDefinition) { 
        b.mStackIndex = mLocalStackDepth;
        mContainerStack.back()->mStackCount += b.mTuplesize;
        mLocalStackDepth += b.mTuplesize;
        push_rep(def);
    }
} 

ASTexpression*
Builder::MakeVariable(const std::string& name, const yy::location& loc)
{
    std::map<std::string,int>::iterator flagItem = FlagNames.find(name);
    if (flagItem != FlagNames.end()) {
        ASTreal* flag = new ASTreal((double)(flagItem->second), loc);
        flag->mType = ASTexpression::FlagType;
        return flag;
    }
    
    if (strncmp(name.c_str(), "CF::", 4) == 0)
        CfdgError::Error(loc, "Configuration parameter names are reserved");
    int varNum = StringToShape(name, loc, true);
    bool isGlobal = false;
    const ASTparameter* bound = findExpression(varNum, isGlobal);
    if (bound == 0) {
        return new ASTruleSpecifier(varNum, name, exp_ptr(), loc, 
                                    m_CFDG->getShapeParams(varNum),
                                    m_CFDG->getShapeParams(mCurrentShape));
    }
    if (bound->mStackIndex == -1) {
        assert(bound->mDefinition);
        switch (bound->mType) {
            case ASTexpression::NumericType: {
                double data[8];
                bool natural = bound->isNatural;
                int valCount = bound->mDefinition->mExpression->evaluate(data, 8);
                if (valCount != bound->mTuplesize)
                    CfdgError::Error(loc, "Unexpected compile error.");                   // this also shouldn't happen
                
                // Create a new cons-tree based on the evaluated variable's expression
                ASTexpression* top = new ASTreal(data[valCount - 1], 
                                                 bound->mDefinition->mExpression->where);
                static_cast<ASTreal*>(top)->text = name;                // use variable name for entropy
                for (int i = valCount - 2; i >= 0; --i) {
                    ASTreal* left = new ASTreal(data[i], 
                                                bound->mDefinition->mExpression->where);
                    top = new ASTcons(left, top);
                }
                top->isNatural = natural;
                return top;
            }
            case ASTexpression::ModType:
                return new ASTmodification(bound->mDefinition->mChildChange, loc);
            case ASTexpression::RuleType: {
                // This must be bound to an ASTruleSpecifier, otherwise it would not be constant
                const ASTruleSpecifier* r = dynamic_cast<const ASTruleSpecifier*> (bound->mDefinition->mExpression);
                if (r == 0) {
                    CfdgError::Error(loc, "Internal error computing bound rule specifier");
                    return new ASTruleSpecifier(varNum, name, exp_ptr(), loc, NULL, NULL);
                }
                return new ASTruleSpecifier(r->shapeType, name, exp_ptr(), loc, NULL, NULL);
            }
            default:
                break;
        }
    } else {
        if (bound->mType == ASTexpression::RuleType) {
            return new ASTruleSpecifier(name, loc, bound->mStackIndex - mLocalStackDepth);
        }
        
        ASTvariable* v = new ASTvariable(varNum, name, loc);
        v->count = bound->mType == ASTexpression::NumericType ? bound->mTuplesize : 1;
        v->stackIndex = bound->mStackIndex - (isGlobal ? 0 : mLocalStackDepth);
        v->mType = bound->mType;
        v->isNatural = bound->isNatural;
        v->isLocal = bound->isLocal;
        v->isParameter = bound->isParameter;
        return v;
    }
    CfdgError::Error(loc, "Cannot determine what to do with this variable.");
    return new ASTexpression(loc);
}

ASTruleSpecifier*  
Builder::MakeRuleSpec(const std::string& name, exp_ptr args, const yy::location& loc)
{
    int nameIndex = StringToShape(name, loc, true);
    bool isGlobal = false;
    const ASTparameter* bound = findExpression(nameIndex, isGlobal);
    if (bound == 0 || bound->mType != ASTexpression::RuleType) {
        m_CFDG->setShapeHasNoParams(nameIndex, args.get());
        return new ASTruleSpecifier(nameIndex, name, args, loc, 
                                    m_CFDG->getShapeParams(nameIndex),
                                    m_CFDG->getShapeParams(mCurrentShape));
    }
    
    if (args.get() != NULL)
        CfdgError::Error(loc, "Cannot bind parameters twice");
    
    if (bound->mStackIndex == -1) {
        // This must be bound to an ASTruleSpecifier, otherwise it would not be constant
        const ASTruleSpecifier* r = dynamic_cast<const ASTruleSpecifier*> (bound->mDefinition->mExpression);
        if (r == 0) {
            CfdgError::Error(loc, "Internal error computing bound rule specifier");
            return new ASTruleSpecifier(nameIndex, name, args, loc, NULL, NULL);
        }
        return new ASTruleSpecifier(r, name, loc);
    }
    
    return new ASTruleSpecifier(name, loc, bound->mStackIndex - 
                                (isGlobal ? 0 : mLocalStackDepth));
}

void
Builder::MakeModTerm(ASTexpArray& dest, term_ptr t)
{
    if (t.get() == NULL) return;
    
    if (t->modType == ASTmodTerm::time)
        timeWise();
    if (t->modType == ASTmodTerm::sat || t->modType == ASTmodTerm::satTarg)
        inColor();
    
    if (mCompilePhase == 2 && t->modType >= ASTmodTerm::hueTarg && t->modType <= ASTmodTerm::targAlpha)
        CfdgError::Error(t->where, "Color target feature unavailable in v3 syntax");
    
    int argcount = 0;
    if (t->args && t->args->mType == ASTexpression::NumericType)
        argcount = t->args->evaluate(0, 0);

    // Try to merge consecutive x and y adjustments
    if (argcount == 1 && t->modType == ASTmodTerm::y && !dest.empty()) {
        ASTmodTerm* last = dynamic_cast<ASTmodTerm*>(dest.back());
        if (last && last->modType == ASTmodTerm::x && last->args->evaluate(0, 0) == 1) {
            last->args = new ASTcons(last->args, t->args);
            t->args = NULL;
            return;     // delete ASTmodTerm t
        }
    }
    
    if (argcount != 3 || (t->modType != ASTmodTerm::size && t->modType != ASTmodTerm::x)) {
        dest.push_back(t.release());
        return;
    }
    
    double d[3];
    if (t->args->isConstant && t->args->evaluate(d, 3) == 3) {
        delete t->args;
        t->args = new ASTcons(new ASTreal(d[0], t->where), new ASTreal(d[1], t->where));

        ASTmodTerm::modTypeEnum ztype = t->modType == ASTmodTerm::size ? ASTmodTerm::zsize :
                                                                         ASTmodTerm::z;
        ASTmodTerm* zmod = new ASTmodTerm(ztype, new ASTreal(d[2], t->where), t->where);
        
        // Check if xy part is the identity transform and only save it if it is not
        if (d[0] != 1.0 || d[1] != 1.0)
            dest.push_back(t.release());
        dest.push_back(zmod);
        return;
    }
    
    ASTexpression* xyargs = t->args->current();
    ASTexpression* zargs = t->args->next();
    if (xyargs && xyargs->evaluate(0, 0) == 2 && 
        zargs  && zargs->evaluate(0, 0) == 1)
    {
        ASTcons* c = dynamic_cast<ASTcons*>(t->args);
        assert(c);
        t->args = xyargs;
        
        ASTmodTerm::modTypeEnum ztype = t->modType == ASTmodTerm::size ? ASTmodTerm::zsize :
                                                                         ASTmodTerm::z;
        ASTmodTerm* zmod = new ASTmodTerm(ztype, zargs, t->where);
        
        double d[2];
        if (t->modType != ASTmodTerm::size || !xyargs->isConstant || 
            xyargs->evaluate(d, 2) != 2 || 
            d[0] != 1.0 || d[1] != 1.0)
        {
            // Check if xy part is the identity transform and only save it if it is not
            dest.push_back(t.release());
        }
        dest.push_back(zmod);
        c->left = c->right = NULL;
        delete c;
        return;
    }
    
    t->modType = t->modType == ASTmodTerm::size ? ASTmodTerm::sizexyz :
                                                  ASTmodTerm::xyz;
    dest.push_back(t.release());
}

rep_ptr
Builder::MakeElement(const std::string& s, mod_ptr mods, exp_ptr params, 
                     const yy::location& loc, bool subPath)
{
    if (mInPathContainer && !subPath && (s == "FILL" || s == "STROKE")) 
        return rep_ptr(new ASTpathCommand(s, mods, params, loc));
    
    ruleSpec_ptr r(MakeRuleSpec(s, params, loc));
    ASTreplacement::repElemListEnum t = ASTreplacement::replacement;
    if (r->argSource == ASTruleSpecifier::ParentArgs)
        r->argSource = ASTruleSpecifier::SimpleParentArgs;
    if (mInPathContainer) {
        if (!subPath) {
            error(loc, "Replacements are not allowed in paths");
        } else if (r->argSource == ASTruleSpecifier::StackArgs) {
            // Parameter subpaths must be all ops, but we must check at runtime
            t = ASTreplacement::op;
        } else if (m_CFDG->getShapeType(r->shapeType) == CFDGImpl::pathType) {
            const ASTrule* rule = m_CFDG->findRule(r->shapeType);
            if (rule) {
                t = (ASTreplacement::repElemListEnum)rule->mRuleBody.mRepType;
            } else {
                error(loc, "Subpath references must be to previously declared paths");
            }
        } else if (primShape::isPrimShape(r->shapeType)){
            t = ASTreplacement::op;
        } else {
            error(loc, "Subpath references must be to previously declared paths");
        }
    }
    return rep_ptr(new ASTreplacement(*r, r->entropyVal, mods, loc, t));
}

AST::ASTexpression*
Builder::MakeFunction(str_ptr name, exp_ptr args, const yy::location& nameLoc, 
                      const yy::location& argsLoc, bool consAllowed)
{
    int nameIndex = StringToShape(*name, nameLoc, true);
    AST::ASTdefine* func = m_CFDG->findFunction(nameIndex);
    if (func) {
        if (!args.get() && func->mStackCount)
            error(nameLoc, "This function requires arguments");
        return new ASTuserFunction(args.release(), func, nameLoc);
    }

    bool dummy;
    const ASTparameter* bound = findExpression(nameIndex, dummy);
    
    if (bound) {
        if (!consAllowed)
            error(nameLoc + argsLoc, "Cannot bind expression to variable/parameter");
        return new ASTcons(MakeVariable(*name, nameLoc), args.release());
    }
    
    if (*name == "select")
        return new ASTselect(args, nameLoc + argsLoc, false);
    if (*name == "if")
        return new ASTselect(args, nameLoc + argsLoc, true);
    
    ASTfunction::FuncType t = ASTfunction::GetFuncType(*name);
    if (t == ASTfunction::Ftime || t == ASTfunction::Frame)
        m_CFDG->addParameter(CFDGImpl::FrameTime);
    if (t != ASTfunction::NotAFunction)
        return new ASTfunction(*name, args, mSeed, nameLoc, argsLoc);
    
    const ASTparameters* p = m_CFDG->getShapeParams(nameIndex);
    if (p) {
        if (!(p->empty()))
            return new ASTruleSpecifier(nameIndex, *name, args, nameLoc + argsLoc, p,
                                        m_CFDG->getShapeParams(mCurrentShape));
        
        if (consAllowed)
            return new ASTcons(new ASTruleSpecifier(nameIndex, *name, exp_ptr(), nameLoc, 
                                                    p, m_CFDG->getShapeParams(mCurrentShape)), 
                               args.release());
        error(nameLoc + argsLoc, "Shape takes no arguments");
    }
    
    // At this point we don't know if this is a typo or a to-be-defined shape or 
    // user function
    
    if (mCompilePhase == 1) {
        mWant2ndPass = true;
    } else {
        error(nameLoc + argsLoc, "Doesn't match a known shape or user function");
    }

    // Just return this, it will get dropped eventually
    return new ASTruleSpecifier(nameIndex, *name, args, nameLoc + argsLoc, p,
                                m_CFDG->getShapeParams(mCurrentShape));
}

AST::ASTmodification*
Builder::MakeModification(mod_ptr mod, const yy::location& loc, bool canonical)
{
    for (ASTexpArray::iterator it = mod->modExp.begin(), eit = mod->modExp.end(); 
         it != eit; ++it)
    {
        std::string ent;
        (*it)->entropy(ent);
        mod->addEntropy(ent);
    }
    if (canonical)
        mod->makeCanonical();
    mod->evalConst();
    mod->isConstant = mod->modExp.empty();
    mod->where = loc;
    
    return mod.release();
}

void
Builder::push_repContainer(ASTrepContainer& c)
{
    mContainerStack.push_back(&c);
    process_repContainer(c);
}

void
Builder::push_paramDecls(const std::string& name, const yy::location& defLoc)
{
    if (isFunction) {
        for (ASTparameters::iterator it = mParamDecls.mParameters.begin(),
             eit = mParamDecls.mParameters.end(); it != eit; ++it)
        {
            it->isLocal = true;
        }
        push_repContainer(mParamDecls);

        // Create the ASTdefine before the expression is known so that the
        // expression can use recursion. Create a placeholder expression
        // that will be deleted when the real expression is parsed.
        int nameIndex = StringToShape(name, defLoc, false);
        exp_ptr r(new ASTreal(1.5, defLoc));
        r->isConstant = false;
        ASTdefine* def = new ASTdefine(name, r, defLoc);
        def->mParameters = mParamDecls.mParameters;
        def->mStackCount = mParamDecls.mStackCount;
        def->isFunction = true;
        AST::ASTdefine* prev = m_CFDG->declareFunction(nameIndex, def);
        if (prev != def) {
            if (mCompilePhase == 1) {
                CfdgError::Error(defLoc, "Redefinition of user functions is not allowed");
                CfdgError::Error(prev->mLocation, "Previous user function definition is here");
            }
            delete def;
        }
        if (m_CFDG->getShapeParams(nameIndex))
            CfdgError::Warning(defLoc, "User function name matches a shape name");
    }
}

void
Builder::process_repContainer(ASTrepContainer& c)
{
    for (ASTparameters::iterator it = c.mParameters.begin(),
         eit= c.mParameters.end(); it != eit; ++it)
    {
        if (it->isParameter || !it->mDefinition) {
            it->mStackIndex = mLocalStackDepth;
            c.mStackCount += it->mTuplesize;
            mLocalStackDepth += it->mTuplesize;
        }
    }
}

void
Builder::pop_repContainer(ASTreplacement* r)
{
    if (m_CFDG) m_CFDG->reportStackDepth(mLocalStackDepth);
    assert(!mContainerStack.empty());
    ASTrepContainer* lastContainer = mContainerStack.back();
    mLocalStackDepth -= lastContainer->mStackCount;
    if (r) {
        r->mRepType |= lastContainer->mRepType;
        if (r->mPathOp == unknownPathop)
            r->mPathOp = lastContainer->mPathOp;
    }
    for (ASTparameters::iterator it = lastContainer->mParameters.begin(),
         eit = lastContainer->mParameters.end(); it != eit; ++it)
    {
        // delete the constant definitions, but not functions
        if (it->mDefinition && !it->mDefinition->isFunction) {
            delete it->mDefinition;
            it->mDefinition = 0;
        }
    }
    mContainerStack.pop_back();
}

static bool badContainer(int containerType)
{
    return (containerType & (ASTreplacement::op | ASTreplacement::replacement)) == 
            (ASTreplacement::op | ASTreplacement::replacement);
}

void
Builder::push_rep(ASTreplacement* r, bool global)
{
    if (r == 0) return;
    ASTrepContainer* container = mContainerStack.back();
    
    container->mBody.push_back(r);
    if (container->mPathOp == unknownPathop)
        container->mPathOp = r->mPathOp;
    int oldType = container->mRepType;
    container->mRepType = oldType | r->mRepType;
    
    if (badContainer(container->mRepType) && !badContainer(oldType) && !global)
        error(r->mLocation, "Cannot mix path elements and replacements in the same container");
}

ASTparameter*
Builder::findExpression(int nameIndex, bool& isGlobal)
{
    for (ContainerStack_t::reverse_iterator cit = mContainerStack.rbegin();
         cit != mContainerStack.rend(); ++cit)
    {
        for (ASTparameters::reverse_iterator pit = (*cit)->mParameters.rbegin();
             pit != (*cit)->mParameters.rend(); ++pit)
        {
            if (pit->mName == nameIndex) {
                isGlobal = (*cit)->isGlobal;
                return &(*pit);
            }
        }
    }
    return 0;
}

void
Builder::PushNameSpace(AST::str_ptr n, const yy::location& loc)
{
    if (n->compare("CF") == 0) {
        error(loc, "CF namespace is reserved");
        return;
    }
    if (n->length() == 0) {
        error(loc, "zero-length namespace");
        return;
    }
    CheckName(*n, loc, false);
    m_includeNamespace.top() = true;
    mCurrentNameSpace.append(*n);
    mCurrentNameSpace.append("::");
}   // delete n

void
Builder::PopNameSpace()
{
    mCurrentNameSpace.resize(mCurrentNameSpace.length() - 2);
    size_t end = mCurrentNameSpace.find_last_of(':');
    if (end == std::string::npos) {
        mCurrentNameSpace.clear();
    } else {
        mCurrentNameSpace.resize(end + 1);
    }
}

void
Builder::CheckVariableName(int index, const yy::location& loc)
{
    if (mAllowOverlap) return;
    bool dummy;
    ASTparameter* p = findExpression(index, dummy);
    if (p) {
        warning(loc, "Scope of name overlaps variable/parameter with same name");
        warning(p->mLocation, "previous variable/parameter declared here");
    }
}

void
Builder::CheckName(const std::string& name, const yy::location& loc,
                   bool colonsAllowed)
{
    size_t pos = name.find_first_of(':');
    if (pos == std::string::npos) return;
    if (!colonsAllowed) {
        error(loc, "namespace specification not allowed in this context");
        return;
    }
    if (pos == 0) {
        error(loc, "improper namespace specification");
        return;
    }
    for(;;) {
        if (pos == name.length() - 1 || name[pos + 1] != ':') break;
        size_t next = name.find_first_of(':', pos + 2);
        if (next == std::string::npos) return;
        if (next == pos + 2) break;
        pos = next;
    }
    error(loc, "improper namespace specification");
}

void
Builder::inColor()
{
    m_CFDG->addParameter(CFDGImpl::Color);
}

void
Builder::timeWise()
{
    m_CFDG->addParameter(CFDGImpl::Time);
}
