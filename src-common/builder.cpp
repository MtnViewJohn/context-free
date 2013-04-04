// builder.cpp
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
Builder* Builder::CurrentBuilder = nullptr;
double Builder:: MaxNatural = 1000.0;

Builder::Builder(CFDGImpl* cfdg, int variation)
: m_CFDG(cfdg), m_currentPath(nullptr), m_basePath(nullptr), m_pathCount(1),
  mInPathContainer(false), mCurrentShape(-1),
  mWant2ndPass(false), mCompilePhase(1),
  mLocalStackDepth(0), mIncludeDepth(0), mAllowOverlap(false), lexer(nullptr),
  mErrorOccured(false)
{ 
    //CommandInfo::shapeMap[0].mArea = M_PI * 0.25;
    mSeed.seed((unsigned long long)variation); 
    if (FlagNames.empty()) {
        FlagNames["CF::None"] = AST::CF_NONE;
        FlagNames["CF::MiterJoin"] = AST::CF_MITER_JOIN | AST::CF_JOIN_PRESENT;
        FlagNames["CF::RoundJoin"] = AST::CF_ROUND_JOIN | AST::CF_JOIN_PRESENT;
        FlagNames["CF::BevelJoin"] = AST::CF_BEVEL_JOIN | AST::CF_JOIN_PRESENT;
        FlagNames["CF::ButtCap"] = AST::CF_BUTT_CAP | AST::CF_CAP_PRESENT;
        FlagNames["CF::RoundCap"] = AST::CF_ROUND_CAP | AST::CF_CAP_PRESENT;
        FlagNames["CF::SquareCap"] = AST::CF_SQUARE_CAP | AST::CF_CAP_PRESENT;
        FlagNames["CF::ArcCW"] = AST::CF_ARC_CW;
        FlagNames["CF::ArcLarge"] = AST::CF_ARC_LARGE;
        FlagNames["CF::Continuous"] = AST::CF_CONTINUOUS;
        FlagNames["CF::Align"] = AST::CF_ALIGN;
        FlagNames["CF::EvenOdd"] = AST::CF_EVEN_ODD;
        FlagNames["CF::IsoWidth"] = AST::CF_ISO_WIDTH;
        FlagNames["~~CF_FILL~~"] = AST::CF_FILL;
        FlagNames["CF::Cyclic"] = AST::CF_CYCLIC;
        FlagNames["CF::Dihedral"] = AST::CF_DIHEDRAL;
        FlagNames["CF::p11g"] = AST::CF_P11G;
        FlagNames["CF::p11m"] = AST::CF_P11M;
        FlagNames["CF::p1m1"] = AST::CF_P1M1;
        FlagNames["CF::p2"] = AST::CF_P2;
        FlagNames["CF::p2mg"] = AST::CF_P2MG;
        FlagNames["CF::p2mm"] = AST::CF_P2MM;
        FlagNames["CF::pm"] = AST::CF_PM;
        FlagNames["CF::pg"] = AST::CF_PG;
        FlagNames["CF::cm"] = AST::CF_CM;
        FlagNames["CF::pmm"] = AST::CF_PMM;
        FlagNames["CF::pmg"] = AST::CF_PMG;
        FlagNames["CF::pgg"] = AST::CF_PGG;
        FlagNames["CF::cmm"] = AST::CF_CMM;
        FlagNames["CF::p4"] = AST::CF_P4;
        FlagNames["CF::p4m"] = AST::CF_P4M;
        FlagNames["CF::p4g"] = AST::CF_P4G;
        FlagNames["CF::p3"] = AST::CF_P3;
        FlagNames["CF::p3m1"] = AST::CF_P3M1;
        FlagNames["CF::p31m"] = AST::CF_P31M;
        FlagNames["CF::p6"] = AST::CF_P6;
        FlagNames["CF::p6m"] = AST::CF_P6M;
    }
    assert(Builder::CurrentBuilder == nullptr);    // ensure singleton
    Builder::CurrentBuilder = this;
    MaxNatural = 1000.0;
    ASTparameter::Impure = false;
    mContainerStack.push_back(&(cfdg->mCFDGcontents));
    
    if (ASTrule::PrimitivePaths[primShape::circleType] == nullptr) {
        for (unsigned i = 0; i < primShape::numTypes; ++i) {
            // primShape statics are const because of thread safety issues.
            // But Builder is a singleton and preceeds any thread's access
            // to primShape statics. So this const_cast is ok.
            primShape* map = const_cast<primShape*>(primShape::shapeMap[i]);
            if (map) {
                ASTrule* r = new ASTrule(i, CfdgError::Default);
                ASTrule::PrimitivePaths[i] = r;
                static const std::string  move_op("MOVETO");
                static const std::string  line_op("LINETO");
                static const std::string   arc_op("ARCTO");
                static const std::string close_op("CLOSEPOLY");
                if (i != primShape::circleType) {
                    map->rewind(0);
                    double x = 0, y = 0;
                    unsigned cmd;
                    while (!agg::is_stop(cmd = map->vertex(&x, &y))) {
                        if (agg::is_vertex(cmd)) {
                            exp_ptr a(new ASTcons(new ASTreal(x, CfdgError::Default), 
                                                  new ASTreal(y, CfdgError::Default)));
                            ASTpathOp* op = new ASTpathOp(agg::is_move_to(cmd) ? move_op : line_op,
                                                          std::move(a), CfdgError::Default);
                            r->mRuleBody.mBody.emplace_back(op);
                        }
                    }
                } else {
                    exp_ptr a(new ASTcons(new ASTreal(0.5, CfdgError::Default), 
                                          new ASTreal(0.0, CfdgError::Default)));
                    ASTpathOp* op = new ASTpathOp(move_op, std::move(a), CfdgError::Default);
                    r->mRuleBody.mBody.emplace_back(op);
                    a.reset(new ASTcons(new ASTreal(-0.5, CfdgError::Default), 
                                        new ASTreal(0.0, CfdgError::Default)));
                    a.get()->append(new ASTreal(0.5, CfdgError::Default));
                    op = new ASTpathOp(arc_op, std::move(a), CfdgError::Default);
                    r->mRuleBody.mBody.emplace_back(op);
                    a.reset(new ASTcons(new ASTreal(0.5, CfdgError::Default), 
                                        new ASTreal(0.0, CfdgError::Default)));
                    a.get()->append(new ASTreal(0.5, CfdgError::Default));
                    op = new ASTpathOp(arc_op, std::move(a), CfdgError::Default);
                    r->mRuleBody.mBody.emplace_back(op);
                }
                r->mRuleBody.mBody.emplace_back(new ASTpathOp(close_op, exp_ptr(),
                                                           CfdgError::Default));
                r->mRuleBody.mRepType = ASTreplacement::op;
                r->mRuleBody.mPathOp = AST::MOVETO;
            }
        }
    }
}

Builder::~Builder()
{
    pop_repContainer(nullptr);
    delete m_CFDG;
    Builder::CurrentBuilder = nullptr;
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
        return nullptr;
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
        if (fname == nullptr) {
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
    if (fname == nullptr) {
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
        input = nullptr;
        m_CFDG->system()->error();
        mErrorOccured = true;
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
    SetShape(nullptr);
    
    m_CFDG->system()->message("Reading rules file %s", fname.c_str());
    
    lexer->yypush_buffer_state(lexer->yy_create_buffer(input, 16384));
    lexer->nextLocAction = yy::Scanner::pushLoc;
}

// Return parser input to previous file
bool
Builder::EndInclude()
{
    bool endOfInput = mIncludeDepth == 0;
    SetShape(nullptr);
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
    m_currentPath = m_filesToLoad.empty() ? nullptr : m_filesToLoad.top();
    return endOfInput;
}

// Store parsed contents of startshape lines
void
Builder::Initialize(rep_ptr init)
{
    m_CFDG->setInitialShape(std::move(init), mIncludeDepth);
}

void
Builder::SetShape(AST::ASTshape* s, bool isPath)
{
    if (s == nullptr) {
        mCurrentShape = -1;
        return;
    }
    if (m_CFDG->findFunction(s->mNameIndex))
        CfdgError::Warning(s->mLocation, "There is a function with the same name as this shape");
    mCurrentShape = s->mNameIndex;
    if (s->mShapeSpec.argSize && m_CFDG->getShapeHasNoParams(mCurrentShape))
        mWant2ndPass = true;
    const char* err = m_CFDG->setShapeParams(mCurrentShape, s->mRules, s->mShapeSpec.argSize, isPath);
    if (err) {
        mErrorOccured = true;
        warning(s->mLocation, err);
    }
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
    CheckVariableName(nameIndex, nameLoc, true);
    mParamDecls.addParameter(type, nameIndex, typeLoc, nameLoc);
}

void
Builder::NextParameter(const std::string& name, exp_ptr e,
                       const yy::location& nameLoc, const yy::location& expLoc) 
{
    bool isFunction = false;
    if (!mContainerStack.empty() && mContainerStack.back() == &mParamDecls) {
        pop_repContainer(nullptr);         // pop mParamDecls
        mParamDecls.mParameters.clear();
        mParamDecls.mStackCount = 0;
        isFunction = true;
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
        if (!m_CFDG->addParameter(name, std::move(e), mIncludeDepth))
            warning(nameLoc, "Unknown configuration parameter");
        if (name == "CF::MaxNatural") {
            const ASTexpression* max = m_CFDG->hasParameter("CF::MaxNatural");
            double v = -1.0;
            if (!max || !max->isConstant ||
                max->mType != AST::NumericType ||
                max->evaluate(&v, 1) != 1)
            {
                CfdgError::Error(max->where, "CF::MaxNatural requires a constant numeric expression");
            } else if (v < 1.0 || (v - 1.0) == v) {
                error(max->where, (v < 1.0) ? "CF::MaxNatural must be >= 1" :
                                              "CF::MaxNatural must be < 9007199254740992");
            } else {
                MaxNatural = v;
            }
        }
        return;
    }
 
    int nameIndex = StringToShape(name, nameLoc, false);
    ASTdefine* funcDef = m_CFDG->findFunction(nameIndex);
    yy::location defLoc = nameLoc + expLoc;
    if (isFunction) {
        assert(funcDef);
        if (mCompilePhase == 1) return;
        
        if (funcDef->mExpression->isNatural && !e->isNatural) {
            CfdgError::Error(expLoc, "Mismatch between declared natural and defined not-natural type of user function");
        }
        // Replace placeholder with actual expression
        funcDef->mExpression.reset(mWant2ndPass ? e.release() : e.release()->simplify());
        funcDef->isConstant = funcDef->mExpression->isConstant;
        funcDef->mLocation = defLoc;
        
        if (funcDef->mExpression->mType != funcDef->mType) {
            CfdgError::Error(expLoc, "Mismatch between declared and defined type of user function");
        } else {
            if (funcDef->mType == AST::NumericType &&
                funcDef->mTuplesize != funcDef->mExpression->evaluate(nullptr, 0))
            {
                CfdgError::Error(expLoc, "Mismatch between declared and defined vector length of user function");
            }
        }

        return;
    } else if (funcDef) {
        CfdgError::Error(nameLoc, "Definition with same name as user function");
        CfdgError::Error(funcDef->mLocation, "    user function definition is here.");
        funcDef = nullptr;
    }

    CheckVariableName(nameIndex, nameLoc, false);
    def_ptr def;
    if (ASTmodification* m = dynamic_cast<ASTmodification*> (e.get())) {
        mod_ptr mod(m); e.release();
        def.reset(new ASTdefine(name, std::move(mod), defLoc));
    } else {
        def.reset(new ASTdefine(name, std::move(e), defLoc));
    }
    ASTrepContainer* top = mContainerStack.back();
    ASTparameter& b = top->addDefParameter(nameIndex, def, nameLoc, expLoc);
 
    if (def) {
        b.mStackIndex = mLocalStackDepth;
        mContainerStack.back()->mStackCount += b.mTuplesize;
        mLocalStackDepth += b.mTuplesize;
        push_rep(def.release());
    }
} 

ASTexpression*
Builder::MakeVariable(const std::string& name, const yy::location& loc)
{
    auto flagItem = FlagNames.find(name);
    if (flagItem != FlagNames.end()) {
        ASTreal* flag = new ASTreal((double)(flagItem->second), loc);
        flag->mType = AST::FlagType;
        return flag;
    }
    
    if (strncmp(name.c_str(), "CF::", 4) == 0)
        CfdgError::Error(loc, "Configuration parameter names are reserved");
    int varNum = StringToShape(name, loc, true);
    bool isGlobal = false;
    const ASTparameter* bound = findExpression(varNum, isGlobal);
    if (bound == nullptr) {
        return new ASTruleSpecifier(varNum, name, nullptr, loc,
                                    m_CFDG->getShapeParams(varNum),
                                    m_CFDG->getShapeParams(mCurrentShape));
    }
    if (bound->mStackIndex == -1) {
        assert(bound->mDefinition);
        switch (bound->mType) {
            case AST::NumericType: {
                double data[9];
                bool natural = bound->isNatural;
                int valCount = bound->mDefinition->mExpression->evaluate(data, 9);
                if (valCount != bound->mTuplesize)
                    CfdgError::Error(loc, "Unexpected compile error.");                   // this also shouldn't happen
                
                // Create a new cons-list based on the evaluated variable's expression
                ASTreal* top = new ASTreal(data[0], bound->mDefinition->mExpression->where);
                top->text = name;                // use variable name for entropy
                ASTexpression* list = top;
                for (int i = 1; i < valCount; ++i) {
                    ASTreal* next = new ASTreal(data[i], 
                                                bound->mDefinition->mExpression->where);
                    list = list->append(next);
                }
                list->isNatural = natural;
                return list;
            }
            case AST::ModType:
                return new ASTmodification(bound->mDefinition->mChildChange, loc);
            case AST::RuleType: {
                // This must be bound to an ASTruleSpecifier, otherwise it would not be constant
                if (const ASTruleSpecifier* r = dynamic_cast<const ASTruleSpecifier*> (bound->mDefinition->mExpression.get())) {
                    return new ASTruleSpecifier(r->shapeType, name, nullptr, loc, nullptr, nullptr);
                } else {
                    CfdgError::Error(loc, "Internal error computing bound rule specifier");
                    return new ASTruleSpecifier(varNum, name, nullptr, loc, nullptr, nullptr);
                }
            }
            default:
                break;
        }
    } else {
        if (bound->mType == AST::RuleType) {
            return new ASTruleSpecifier(name, loc, bound->mStackIndex - mLocalStackDepth);
        }
        
        ASTvariable* v = new ASTvariable(varNum, name, loc);
        v->count = bound->mType == AST::NumericType ? bound->mTuplesize : 1;
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

ASTexpression*
Builder::MakeArray(AST::str_ptr name, AST::exp_ptr args, const yy::location& nameLoc, 
                   const yy::location& argsLoc)
{
    if (strncmp(name->c_str(), "CF::", 4) == 0)
        CfdgError::Error(nameLoc, "Configuration parameter names are reserved");
    int varNum = StringToShape(*name, nameLoc, true);
    bool isGlobal = false;
    const ASTparameter* bound = findExpression(varNum, isGlobal);
    if (bound == nullptr) {
        CfdgError::Error(nameLoc, "Cannot find variable or parameter with this name");
        return args.release();
    } else if (bound->mType != AST::NumericType) {
        CfdgError::Error(nameLoc, "This is not a numeric vector");
        return args.release();
    }
    ASTexpression* ret =  new ASTarray(bound, std::move(args), isGlobal ? 0 : mLocalStackDepth,
                                       nameLoc + argsLoc, *name);
    return mWant2ndPass ? ret : ret->simplify();
}

ASTexpression*
Builder::MakeLet(const yy::location& letLoc, exp_ptr exp)
{
    ASTexpression* args = nullptr;
    ASTrepContainer* lastContainer = mContainerStack.back();
    for (rep_ptr& rep: lastContainer->mBody) {
        if (const ASTdefine* cdef = dynamic_cast<const ASTdefine*>(rep.get())) {
            ASTdefine* def = const_cast<ASTdefine*>(cdef);
            args = ASTexpression::Append(args, def->mExpression.release());
        }
    }
    
    static const std::string name("let");
    yy::location defLoc = exp->where;
    ASTdefine* def = new ASTdefine(name, std::move(exp), defLoc);
    
    for (ASTparameter& param: lastContainer->mParameters) {
        // copy the non-constant definitions
        if (!(param.mDefinition))
            def->mParameters.push_back(param);
    }
    def->mStackCount = lastContainer->mStackCount;
    def->isFunction = true;
    pop_repContainer(nullptr);
    return new ASTlet(args, def, letLoc, defLoc);
}

ASTruleSpecifier*  
Builder::MakeRuleSpec(const std::string& name, exp_ptr args, const yy::location& loc)
{
    if (name == "if" || name == "let" || name == "select") {
        if (args->mType != AST::RuleType)
            CfdgError::Error(args->where, "Function does not return a shape");
        if (name == "select") {
            yy::location argsLoc = args->where;
            args.reset(new ASTselect(std::move(args), argsLoc, false));
        }
        ASTruleSpecifier* spec = new ASTruleSpecifier(std::move(args), loc);
        return mWant2ndPass ? spec : static_cast<ASTruleSpecifier*>(spec->simplify());
    }

    int nameIndex = StringToShape(name, loc, true);
    bool isGlobal = false;
    
    ASTdefine* def = m_CFDG->findFunction(nameIndex);
    if (def) {
        if (def->mType != AST::RuleType) {
            yy::location nameLoc = loc;
            if (args.get()) nameLoc.end = args->where.begin;
            CfdgError::Error(nameLoc, "Function does not return a shape");
        } else {
            args.reset(new ASTuserFunction(args.release(), def, loc));
        }
        ASTruleSpecifier* spec = new ASTruleSpecifier(std::move(args), loc);
        return mWant2ndPass ? spec : static_cast<ASTruleSpecifier*>(spec->simplify());
    }
    
    const ASTparameter* bound = findExpression(nameIndex, isGlobal);
    if (bound == nullptr || bound->mType != AST::RuleType) {
        m_CFDG->setShapeHasNoParams(nameIndex, args.get());
        ASTruleSpecifier* spec = new ASTruleSpecifier(nameIndex, name, std::move(args), loc,
                                                      m_CFDG->getShapeParams(nameIndex),
                                                      m_CFDG->getShapeParams(mCurrentShape));
        return mWant2ndPass ? spec : static_cast<ASTruleSpecifier*>(spec->simplify());
    }
    
    if (args)
        CfdgError::Error(loc, "Cannot bind parameters twice");
    
    if (bound->mStackIndex == -1) {
        // This must be bound to an ASTruleSpecifier, otherwise it would not be constant
        if (const ASTruleSpecifier* r = dynamic_cast<const ASTruleSpecifier*> (bound->mDefinition->mExpression.get())) {
            return new ASTruleSpecifier(r, name, loc);
        } else {
            CfdgError::Error(loc, "Internal error computing bound rule specifier");
            return new ASTruleSpecifier(nameIndex, name, std::move(args), loc, nullptr, nullptr);
        }
    }
    
    return new ASTruleSpecifier(name, loc, bound->mStackIndex - 
                                (isGlobal ? 0 : mLocalStackDepth));
}

void
Builder::MakeModTerm(ASTtermArray& dest, term_ptr t)
{
    if (!t) return;
    
    if (t->modType == ASTmodTerm::time)
        timeWise();
    if (t->modType == ASTmodTerm::sat || t->modType == ASTmodTerm::satTarg)
        inColor();
    
    if (mCompilePhase == 2 && t->modType >= ASTmodTerm::hueTarg && t->modType <= ASTmodTerm::targAlpha)
        CfdgError::Error(t->where, "Color target feature unavailable in v3 syntax");
    
    int argcount = 0;
    if (t->args && t->args->mType == AST::NumericType)
        argcount = t->args->evaluate(nullptr, 0);

    // Try to merge consecutive x and y adjustments
    if (argcount == 1 && t->modType == ASTmodTerm::y && !dest.empty()) {
        ASTmodTerm* last = dest.back().get();
        if (last->modType == ASTmodTerm::x && last->args->evaluate(nullptr, 0) == 1) {
            last->args.reset(last->args.release()->append(t->args.release()));
            return;     // delete ASTmodTerm t
        }
    }
    
    if (argcount != 3 || (t->modType != ASTmodTerm::size && t->modType != ASTmodTerm::x)) {
        dest.push_back(std::move(t));
        return;
    }
    
    // Try to split the XYZ term into an XY term and a Z term. Drop the XY term
    // if it is the identity. First try an all-constant route, then try to tease
    // apart the arguments.
    double d[3];
    if (t->args->isConstant && t->args->evaluate(d, 3) == 3) {
        t->args.reset(new ASTcons(new ASTreal(d[0], t->where), new ASTreal(d[1], t->where)));

        ASTmodTerm::modTypeEnum ztype = t->modType == ASTmodTerm::size ? ASTmodTerm::zsize :
                                                                         ASTmodTerm::z;
        ASTmodTerm* zmod = new ASTmodTerm(ztype, new ASTreal(d[2], t->where), t->where);
        
        // Check if xy part is the identity transform and only save it if it is not
        if (d[0] != 1.0 || d[1] != 1.0 || t->modType == ASTmodTerm::x)
            dest.push_back(std::move(t));
        dest.emplace_back(zmod);
        return;
    }
    
    if (t->args->size() > 1) {
        ASTexpression* xyargs = nullptr;
        int i = 0;
        for (; i < t->args->size(); ++i) {
            xyargs = ASTexpression::Append(xyargs, (*t->args)[i]);
            if (xyargs->evaluate(nullptr, 0) >= 2)
                break;
        }
        if (xyargs && xyargs->evaluate(nullptr, 0) == 2 && i == t->args->size() - 1) {
            // We have successfully split the 3-tuple into a 2-tuple and a scalar
            ASTexpression* zargs = (*t->args)[i];
            t->args->release();
            
            t->args.reset(xyargs);
            
            ASTmodTerm::modTypeEnum ztype = t->modType == ASTmodTerm::size ? ASTmodTerm::zsize :
                                                                             ASTmodTerm::z;
            ASTmodTerm* zmod = new ASTmodTerm(ztype, zargs, t->where);
            
            double d[2];
            if (t->modType != ASTmodTerm::size || !xyargs->isConstant || 
                xyargs->evaluate(d, 2) != 2 || d[0] != 1.0 || d[1] != 1.0)
            {
                // Check if xy part is the identity transform and only save it if it is not
                dest.push_back(std::move(t));
            }
            dest.emplace_back(zmod);
            return;
        }
    }
    
    t->modType = t->modType == ASTmodTerm::size ? ASTmodTerm::sizexyz :
                                                  ASTmodTerm::xyz;
    dest.push_back(std::move(t));
}

rep_ptr
Builder::MakeElement(const std::string& s, mod_ptr mods, exp_ptr params, 
                     const yy::location& loc, bool subPath)
{
    if (mInPathContainer && !subPath && (s == "FILL" || s == "STROKE")) 
        return rep_ptr(new ASTpathCommand(s, std::move(mods), std::move(params), loc));
    
    ruleSpec_ptr r(MakeRuleSpec(s, std::move(params), loc));
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
    return rep_ptr(new ASTreplacement(*r, r->entropyVal, std::move(mods), loc, t));
}

AST::ASTexpression*
Builder::MakeFunction(str_ptr name, exp_ptr args, const yy::location& nameLoc, 
                      const yy::location& argsLoc, bool consAllowed)
{
    int nameIndex = StringToShape(*name, nameLoc, true);
    AST::ASTdefine* func = m_CFDG->findFunction(nameIndex);
    if (func) {
        return new ASTuserFunction(args.release(), func, nameLoc);
    }

    bool dummy;
    const ASTparameter* bound = findExpression(nameIndex, dummy);
    
    if (bound) {
        if (!consAllowed)
            error(nameLoc + argsLoc, "Cannot bind expression to variable/parameter");
        return MakeVariable(*name, nameLoc)->append(args.release());
    }
    
    if (*name == "select" || *name == "if") {
        ASTselect* sel = new ASTselect(std::move(args), nameLoc + argsLoc, *name == "if");
        return mWant2ndPass ? sel : sel->simplify();
    }
    
    ASTfunction::FuncType t = ASTfunction::GetFuncType(*name);
    if (t == ASTfunction::Ftime || t == ASTfunction::Frame)
        m_CFDG->addParameter(CFDGImpl::FrameTime);
    if (t != ASTfunction::NotAFunction)
        return new ASTfunction(*name, std::move(args), mSeed, nameLoc, argsLoc);
    
    const ASTparameters* p = m_CFDG->getShapeParams(nameIndex);
    if (p) {
        if (!(p->empty())) {
            ASTruleSpecifier* spec = new ASTruleSpecifier(nameIndex, *name, std::move(args), nameLoc + argsLoc, p,
                                                          m_CFDG->getShapeParams(mCurrentShape));
            return mWant2ndPass ? spec : static_cast<ASTruleSpecifier*>(spec->simplify());
        }
        
        if (consAllowed) {
            ASTruleSpecifier* r = new ASTruleSpecifier(nameIndex, *name, nullptr, nameLoc, 
                                                       p, m_CFDG->getShapeParams(mCurrentShape));
            ASTexpression* ret = r->append(args.release());
            return mWant2ndPass ? ret : ret->simplify();
        }
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
    return new ASTruleSpecifier(nameIndex, *name, std::move(args), nameLoc + argsLoc, p,
                                m_CFDG->getShapeParams(mCurrentShape));
}

AST::ASTmodification*
Builder::MakeModification(mod_ptr mod, const yy::location& loc, bool canonical)
{
    for (term_ptr& term: mod->modExp) {
        std::string ent;
        term->entropy(ent);
        mod->addEntropy(ent);
        if (!mWant2ndPass)
            term.reset(static_cast<ASTmodTerm*>(term.release()->simplify()));
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
Builder::push_paramDecls(const std::string& name, const yy::location& defLoc,
                         const std::string& type)
{
    {
        for (ASTparameter& param: mParamDecls.mParameters)
            param.isLocal = true;
        push_repContainer(mParamDecls);
        if (mCompilePhase != 1) return;

        // Create the ASTdefine before the expression is known so that the
        // expression can use recursion. Create a placeholder expression
        // that will be deleted when the real expression is parsed.
        int nameIndex = StringToShape(name, defLoc, false);
        ASTparameter p;
        p.init(type, nameIndex);
        exp_ptr r;
        
        switch (p.mType) {
            case AST::NumericType: {
                ASTexpression* num = new ASTreal(p.isNatural ? 1.0 : 1.5, defLoc);
                num->isConstant = false;
                for (int i = 1; i < p.mTuplesize; ++i)
                    num = num->append(new ASTreal(1.5, defLoc));
                r.reset(num);
                break;
            }
            case AST::ModType:
                r.reset(new ASTmodification(defLoc));
                break;
            case AST::NoType:
            case AST::FlagType:
                CfdgError::Warning(defLoc, "Unsupported function type");
                // fall through
            case AST::RuleType:
                r.reset(new ASTruleSpecifier());
                break;
        }
        
        ASTdefine* def = new ASTdefine(name, std::move(r), defLoc);
        def->mParameters = mParamDecls.mParameters;
        def->mStackCount = mParamDecls.mStackCount;
        def->isFunction = true;
        AST::ASTdefine* prev = m_CFDG->declareFunction(nameIndex, def);
        if (prev != def) {
			assert(prev);
            mErrorOccured = true;
            warning(defLoc, "Redefinition of user functions is not allowed");
            warning(prev->mLocation, "Previous user function definition is here");
            delete def;
        }
        if (m_CFDG->getShapeParams(nameIndex))
            CfdgError::Warning(defLoc, "User function name matches a shape name");
    }
}

void
Builder::process_repContainer(ASTrepContainer& c)
{
    for (ASTparameter& param: c.mParameters) {
        if (param.isParameter || !param.mDefinition) {
            param.mStackIndex = mLocalStackDepth;
            c.mStackCount += param.mTuplesize;
            mLocalStackDepth += param.mTuplesize;
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
    if (r == nullptr) return;
    ASTrepContainer* container = mContainerStack.back();
    
    container->mBody.emplace_back(r);
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
    for (auto cit = mContainerStack.rbegin(); cit != mContainerStack.rend(); ++cit) {
        for (auto pit = (*cit)->mParameters.rbegin(); pit != (*cit)->mParameters.rend(); ++pit) {
            if (pit->mName == nameIndex) {
                isGlobal = (*cit)->isGlobal;
                return &(*pit);
            }
        }
    }
    return nullptr;
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
Builder::CheckVariableName(int index, const yy::location& loc, bool param)
{
    if (mAllowOverlap && !param) return;
    
    const ASTrepContainer* thisLevel = param ? &mParamDecls : mContainerStack.back();
    
    for (auto pit = thisLevel->mParameters.rbegin(),
         epit = thisLevel->mParameters.rend(); pit != epit; ++pit)
    {
        if (pit->mName == index) {
            warning(loc, "Scope of name overlaps variable/parameter with same name");
            warning(pit->mLocation, "previous variable/parameter declared here");
        }
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
