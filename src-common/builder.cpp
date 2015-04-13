// builder.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2005-2014 John Horigan - john@glyphic.com
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
#include <cassert>
#include <limits>
#include "scanner.h"
#include <cstring>
#include <typeinfo>

using namespace AST;

const std::map<std::string, int> Builder::FlagNames = {
    {"CF::None",        AST::CF_NONE},
    {"CF::MiterJoin",   AST::CF_MITER_JOIN | AST::CF_JOIN_PRESENT},
    {"CF::RoundJoin",   AST::CF_ROUND_JOIN | AST::CF_JOIN_PRESENT},
    {"CF::BevelJoin",   AST::CF_BEVEL_JOIN | AST::CF_JOIN_PRESENT},
    {"CF::ButtCap",     AST::CF_BUTT_CAP | AST::CF_CAP_PRESENT},
    {"CF::RoundCap",    AST::CF_ROUND_CAP | AST::CF_CAP_PRESENT},
    {"CF::SquareCap",   AST::CF_SQUARE_CAP | AST::CF_CAP_PRESENT},
    {"CF::ArcCW",       AST::CF_ARC_CW},
    {"CF::ArcLarge",    AST::CF_ARC_LARGE},
    {"CF::Continuous",  AST::CF_CONTINUOUS},
    {"CF::Align",       AST::CF_ALIGN},
    {"CF::EvenOdd",     AST::CF_EVEN_ODD},
    {"CF::IsoWidth",    AST::CF_ISO_WIDTH},
    {"~~CF_FILL~~",     AST::CF_FILL},
    {"CF::Cyclic",      AST::CF_CYCLIC},
    {"CF::Dihedral",    AST::CF_DIHEDRAL},
    {"CF::p11g",        AST::CF_P11G},
    {"CF::p11m",        AST::CF_P11M},
    {"CF::p1m1",        AST::CF_P1M1},
    {"CF::p2",          AST::CF_P2},
    {"CF::p2mg",        AST::CF_P2MG},
    {"CF::p2mm",        AST::CF_P2MM},
    {"CF::pm",          AST::CF_PM},
    {"CF::pg",          AST::CF_PG},
    {"CF::cm",          AST::CF_CM},
    {"CF::pmm",         AST::CF_PMM},
    {"CF::pmg",         AST::CF_PMG},
    {"CF::pgg",         AST::CF_PGG},
    {"CF::cmm",         AST::CF_CMM},
    {"CF::p4",          AST::CF_P4},
    {"CF::p4m",         AST::CF_P4M},
    {"CF::p4g",         AST::CF_P4G},
    {"CF::p3",          AST::CF_P3},
    {"CF::p3m1",        AST::CF_P3M1},
    {"CF::p31m",        AST::CF_P31M},
    {"CF::p6",          AST::CF_P6},
    {"CF::p6m",         AST::CF_P6M}
};
Builder* Builder::CurrentBuilder = nullptr;
double Builder:: MaxNatural = 1000.0;

Builder::Builder(cfdgi_ptr cfdg, int variation)
: m_CFDG(std::move(cfdg)), m_currentPath(nullptr), m_pathCount(1),
  mInPathContainer(false), mCurrentShape(-1),
  mLocalStackDepth(0), mIncludeDepth(0), mAllowOverlap(false), lexer(nullptr),
  mErrorOccured(false)
{ 
    //CommandInfo::shapeMap[0].mArea = M_PI * 0.25;
    mSeed.seed(static_cast<unsigned long long>(variation));
    assert(Builder::CurrentBuilder == nullptr);    // ensure singleton
    Builder::CurrentBuilder = this;
    MaxNatural = 1000.0;
    ASTparameter::Impure = false;
}

Builder::~Builder()
{
    Builder::CurrentBuilder = nullptr;
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
    if (*b == '\0' && *f != '\0')
        return f;
    if (*b == '\0' && *f == '\0')
        return nullptr;
    return file->c_str();
}


void
Builder::error(const yy::location& l, const std::string& msg)
{
    mErrorOccured = true;
    m_CFDG->system()->error();
    warning(l, msg);
}

void
Builder::warning(const yy::location& l, const std::string& msg)
{
    CfdgError err(l, msg.c_str());
    
    // Create user-friendly file name and put it in err.where.end.filename
    const char* fname = nullptr;
    if (l.begin.filename) {
        fname = getUniqueFile(m_basePath.get(), l.begin.filename);
        if (!fname)
            fname = l.begin.filename->c_str();
    }
    m_CFDG->fileNames.emplace_back((fname && *fname) ? fname : "input");
    err.where.end.filename = &(m_CFDG->fileNames.back());;
    
    m_CFDG->system()->syntaxError(err);
}

void Builder::error(int line, const char* msg)
{
    yy::location loc;
    loc.initialize(m_currentPath);
    loc.begin.line = line;
    loc.end.line = line + 1;
    CfdgError err(loc, msg);
    const char* fname = getUniqueFile(m_basePath.get(), loc.begin.filename);
    mErrorOccured = true;
    m_CFDG->system()->error();
    if (fname == nullptr) {
        m_CFDG->system()->syntaxError(err);
    } else {
        m_CFDG->system()->message("Error in %s at line %d - %s", 
                                  fname, loc.begin.line, msg);
    }
}

AbstractSystem*
Builder::system()
{
    return m_CFDG->system();
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

std::string
Builder::ShapeToString(int shape)
{
    return m_CFDG->decodeShapeName(shape);
}

// Switch parser input to a new file
void
Builder::IncludeFile(const std::string& fname)
{
    std::string path =
        m_CFDG->system()->relativeFilePath(*m_currentPath, fname.c_str());
    std::unique_ptr<std::istream> input(m_CFDG->system()->openFileForRead(path));
    if (!input || !input->good()) {
        m_CFDG->system()->error();
        mErrorOccured = true;
        m_CFDG->system()->message("Couldn't open rules file %s", path.c_str());
        return;
    }
    
    m_CFDG->fileNames.push_back(path);
    m_currentPath = &(m_CFDG->fileNames.back());
    m_filesToLoad.push(m_currentPath);
    m_streamsToLoad.push(std::move(input));
    m_includeNamespace.push(false);
    ++m_pathCount;
    ++mIncludeDepth;
    mCurrentShape = -1;
    SetShape(nullptr);
    
    m_CFDG->system()->message("Reading rules file %s", fname.c_str());
    
    lexer->yypush_buffer_state(lexer->yy_create_buffer(m_streamsToLoad.top().get(), 16384));
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
    m_streamsToLoad.pop();
    m_filesToLoad.pop();
    m_includeNamespace.pop();
    m_currentPath = m_filesToLoad.empty() ? nullptr : m_filesToLoad.top();
    return endOfInput;
}

void
Builder::SetShape(std::string* name, const yy::location& nameLoc, bool isPath)
{
    if (name == nullptr) {
        mCurrentShape = -1;
        return;
    }
    mCurrentShape = StringToShape(*name, nameLoc, false);
    if (ASTdefine* def = m_CFDG->findFunction(mCurrentShape)) {
        CfdgError::Error(nameLoc, "There is a function with the same name as this shape");
        CfdgError::Error(def->mLocation, "    the function is here");
        return;
    }
    const char* err = m_CFDG->setShapeParams(mCurrentShape, mParamDecls, mParamDecls.mStackCount, isPath);
    if (err) {
        mErrorOccured = true;
        warning(nameLoc, err);
    }
    mLocalStackDepth -= mParamDecls.mStackCount;
    mParamDecls.mParameters.clear();
    mParamDecls.mStackCount = 0;
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
    ASTparameter& param = mParamDecls.mParameters.back();
    param.mStackIndex = mLocalStackDepth;
    mParamDecls.mStackCount += param.mTuplesize;
    mLocalStackDepth += param.mTuplesize;
}

ASTdefine*
Builder::MakeDefinition(const std::string& name, const yy::location& nameLoc,
                        bool isFunction)
{
    if (strncmp(name.c_str(), "CF::", 4) == 0) {
        if (isFunction) {
            CfdgError::Error(nameLoc, "Configuration parameters cannot be functions");
            return nullptr;
        }
        if (!mContainerStack.back()->isGlobal) {
            CfdgError::Error(nameLoc, "Configuration parameters must be at global scope");
            return nullptr;
        }
        ASTdefine* cfg = new ASTdefine(name, nameLoc);
        cfg->mConfigDepth = static_cast<int>(mIncludeDepth);
        cfg->mDefineType = ASTdefine::ConfigDefine;
        return cfg;
    }
    
    if (ASTfunction::GetFuncType(name) != ASTfunction::NotAFunction) {
        CfdgError::Error(nameLoc, "Internal function names are reserved");
        return nullptr;
    }
    
    int nameIndex = StringToShape(name, nameLoc, false);
    if (ASTdefine* funcDef = m_CFDG->findFunction(nameIndex)) {
        CfdgError::Error(nameLoc, "Definition with same name as user function");
        CfdgError::Error(funcDef->mLocation, "    user function definition is here.");
        return nullptr;
    }

    CheckVariableName(nameIndex, nameLoc, false);
    ASTdefine* def = new ASTdefine(name, nameLoc);
    def->mShapeSpec.shapeType = nameIndex;
    if (isFunction) {
        for (ASTparameter& param: mParamDecls.mParameters)
            param.mLocality = PureNonlocal;
        def->mParameters = mParamDecls.mParameters;     // copy
        def->mStackCount = mParamDecls.mStackCount;
        def->mDefineType = ASTdefine::FunctionDefine;
        mLocalStackDepth -= mParamDecls.mStackCount;
        mParamDecls.mStackCount = 0;
        
        AST::ASTdefine* prev = m_CFDG->declareFunction(nameIndex, def);
        assert(prev == def);    // since findFunction() didn't find it
    } else {
        // Add parameters during parse even though the type info is unknown. At least
        // we know the name of parameters and we can use this info to help distinguish
        // function applications from variables followed by an expression
        mContainerStack.back()->addDefParameter(nameIndex, def, nameLoc, CfdgError::Default);
    }
    return def;
}

void
Builder::MakeConfig(ASTdefine* cfg)
{
    yy::location expLoc = cfg->mExpression ? cfg->mExpression->where : cfg->mLocation;
    if (cfg->mName == "CF::Impure") {
        double v = 0.0;
        if (!cfg->mExpression || !cfg->mExpression->isConstant || cfg->mExpression->evaluate(&v, 1) != 1) {
            CfdgError::Error(expLoc, "CF::Impure requires a constant numeric expression");
        } else {
            ASTparameter::Impure = v != 0.0;
        }
    }
    if (cfg->mName == "CF::AllowOverlap") {
        double v = 0.0;
        if (!cfg->mExpression || !cfg->mExpression->isConstant || cfg->mExpression->evaluate(&v, 1) != 1) {
            CfdgError::Error(expLoc, "CF::AllowOverlap requires a constant numeric expression");
        } else {
            mAllowOverlap = v != 0.0;
        }
    }
    if (cfg->mName == "CF::StartShape" && cfg->mExpression &&
        typeid(*(cfg->mExpression)) != typeid(ASTstartSpecifier))
    {
        // This code supports setting the startshape with a config statement:
        //    CF::StartShape = foo(foo params), [mods]
        // It converts the ASTruleSpec and optional ASTmod to a single ASTstartSpec
        
        ASTruleSpecifier* rule = nullptr;
        mod_ptr mod;
        ASTexpArray specAndMod = Extract(std::move(cfg->mExpression));
        switch (specAndMod.size()) {
            case 2:
                mod.reset(dynamic_cast<ASTmodification*>(specAndMod[1].get()));
                if (!mod) {
                    CfdgError::Error(specAndMod[1]->where, "CF::StartShape second term must be a modification");
                    return;
                }
                specAndMod[1].release();
                // fall through
            case 1:
                rule = dynamic_cast<ASTruleSpecifier*>(specAndMod[0].get());
                if (!rule) {
                    CfdgError::Error(specAndMod[0]->where, "CF::StartShape must start with a shape specification");
                    return;
                }
                specAndMod[0].release();
                break;
            default:
                CfdgError::Error(expLoc, "CF::StartShape expression must have the form shape_spec or shape_spec, modification]");
                return;
        }
        
        if (!mod)
            mod.reset(new ASTmodification(expLoc));
        
        cfg->mExpression.reset(new ASTstartSpecifier(std::move(*rule), std::move(mod)));
    }
    ASTexpression* current = cfg->mExpression.get();
    if (!m_CFDG->addParameter(cfg->mName, std::move(cfg->mExpression), static_cast<unsigned>(cfg->mConfigDepth)))
        warning(cfg->mLocation, "Unknown configuration parameter");
    if (cfg->mName == "CF::MaxNatural") {
        const ASTexpression* max = m_CFDG->hasParameter(CFG::MaxNatural);
        if (max != current || !max)
            return;                             // only process if we are changing it
        double v = -1.0;
        if (!max->isConstant ||
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
}

ASTexpression*
Builder::MakeVariable(const std::string& name, const yy::location& loc)
{
    auto flagItem = FlagNames.find(name);
    if (flagItem != FlagNames.end()) {
        ASTreal* flag = new ASTreal(static_cast<double>(flagItem->second), loc);
        flag->mType = AST::FlagType;
        return flag;
    }
    
    if (strncmp(name.c_str(), "CF::", 4) == 0) {
        CfdgError::Error(loc, "Configuration parameter names are reserved");
        return new ASTexpression(loc);
    }
    
    if (ASTfunction::GetFuncType(name) != ASTfunction::NotAFunction) {
        CfdgError::Error(loc, "Internal function names are reserved");
        return new ASTexpression(loc);
    }
    
    int varNum = StringToShape(name, loc, true);
    bool isGlobal = false;
    const ASTparameter* bound = findExpression(varNum, isGlobal);
    if (bound == nullptr) {
        return new ASTruleSpecifier(varNum, name, nullptr, loc,
                                    m_CFDG->getShapeParams(mCurrentShape));
    }
    
    ASTvariable* v = new ASTvariable(varNum, name, loc);
    return v;
}

ASTexpression*
Builder::MakeArray(AST::str_ptr name, AST::exp_ptr args, const yy::location& nameLoc, 
                   const yy::location& argsLoc)
{
    if (strncmp(name->c_str(), "CF::", 4) == 0) {
        CfdgError::Error(nameLoc, "Configuration parameter names are reserved");
        return args.release();
    }
    int varNum = StringToShape(*name, nameLoc, true);
    bool isGlobal = false;
    const ASTparameter* bound = findExpression(varNum, isGlobal);
    if (bound == nullptr) {
        CfdgError::Error(nameLoc, "Cannot find variable or parameter with this name");
        return args.release();
    }
    return new ASTarray(varNum, std::move(args), nameLoc + argsLoc, *name);
}

ASTexpression*
Builder::MakeLet(const yy::location& letLoc, AST::cont_ptr vars, exp_ptr exp)
{
    static const std::string name("let");
    int nameIndex = StringToShape(name, letLoc, false);
    yy::location defLoc = exp->where;
    def_ptr def(new ASTdefine(name, defLoc));
    def->mShapeSpec.shapeType = nameIndex;
    def->mExpression = std::move(exp);
    def->mDefineType = ASTdefine::LetDefine;
    return new ASTlet(std::move(vars), std::move(def), letLoc, defLoc);
}

ASTruleSpecifier*  
Builder::MakeRuleSpec(const std::string& name, exp_ptr args,
                      const yy::location& loc, mod_ptr mod, bool makeStart)
{
    if (name == "if" || name == "let" || name == "select") {
        // if and let are handled by the parser, select is handled here
        if (name == "select") {
            yy::location argsLoc = args->where;
            args.reset(new ASTselect(std::move(args), argsLoc, false));
        }
        if (makeStart)
            return new ASTstartSpecifier(std::move(args), loc, std::move(mod));
        else
            return new ASTruleSpecifier(std::move(args), loc);
    }

    int nameIndex = StringToShape(name, loc, true);
    bool isGlobal = false;
    const ASTparameter* bound = findExpression(nameIndex, isGlobal);
    
    if (bound && args && args->mType == ReuseType && !makeStart && isGlobal && nameIndex == mCurrentShape)
        warning(loc, "Shape name binds to global variable and current shape, using current shape");
    
    if (bound && bound->isParameter && bound->mType == RuleType)
        return new ASTruleSpecifier(nameIndex, name, loc);
    
    ASTruleSpecifier* ret = nullptr;
    m_CFDG->setShapeHasNoParams(nameIndex, args.get());
    if (makeStart)
        ret = new ASTstartSpecifier(nameIndex, name, std::move(args), loc,
                                    std::move(mod));
    else
        ret = new ASTruleSpecifier(nameIndex, name, std::move(args), loc,
                                   m_CFDG->getShapeParams(mCurrentShape));
    if (ret->arguments && ret->arguments->mType == ReuseType) {
        if (makeStart)
            CfdgError::Error(loc, "Startshape cannot reuse parameters");
        else if (nameIndex == mCurrentShape) {
            ret->argSource = ASTruleSpecifier::SimpleParentArgs;
            ret->typeSignature = ret->parentSignature;
        }
    }
    return ret;
}

void
Builder::MakeModTerm(ASTtermArray& dest, term_ptr t)
{
    if (!t) return;
    
    if (t->modType == ASTmodTerm::time)
        timeWise();
    if (t->modType == ASTmodTerm::sat || t->modType == ASTmodTerm::satTarg)
        inColor();
    
    if (lexer->startToken == yy::CfdgParser::token_type::CFDG3 &&
        t->modType >= ASTmodTerm::hueTarg && t->modType <= ASTmodTerm::targAlpha)
        CfdgError::Error(t->where, "Color target feature unavailable in v3 syntax");
    
    dest.push_back(std::move(t));
}

ASTreplacement*
Builder::MakeElement(const std::string& s, mod_ptr mods, exp_ptr params, 
                     const yy::location& loc, bool subPath)
{
    if (mInPathContainer && !subPath && (s == "FILL" || s == "STROKE")) 
        return new ASTpathCommand(s, std::move(mods), std::move(params), loc);
    
    ruleSpec_ptr r(MakeRuleSpec(s, std::move(params), loc));
    ASTreplacement::repElemListEnum t = ASTreplacement::replacement;
    if (r->argSource == ASTruleSpecifier::ParentArgs)
        r->argSource = ASTruleSpecifier::SimpleParentArgs;
    if (mInPathContainer) {
        bool isGlobal = false;
        const ASTparameter* bound = findExpression(r->shapeType, isGlobal);
        
        if (!subPath) {
            error(loc, "Replacements are not allowed in paths");
        } else if (r->argSource == ASTruleSpecifier::StackArgs ||
                   r->argSource == ASTruleSpecifier::ShapeArgs)
        {
            // Parameter subpaths must be all ops, but we must check at runtime
            t = ASTreplacement::op;
        } else if (m_CFDG->getShapeType(r->shapeType) == CFDGImpl::pathType) {
            const ASTrule* rule = m_CFDG->findRule(r->shapeType);
            if (rule && rule->mRuleBody.mRepType) {
                t = static_cast<ASTreplacement::repElemListEnum>(rule->mRuleBody.mRepType);
            } else {
                // Recursive calls must be all ops, check at runtime
                t = ASTreplacement::op;
            }
        } else if (bound) {
            // Variable subpaths must be all ops, but we must check at runtime
            t = ASTreplacement::op;
        } else if (primShape::isPrimShape(r->shapeType)){
            t = ASTreplacement::op;
        } else {
            // Forward calls must be all ops, check at runtime
            t = ASTreplacement::op;
        }
    }
    return new ASTreplacement(std::move(*r), std::move(mods), loc, t);
}

AST::ASTexpression*
Builder::MakeFunction(str_ptr name, exp_ptr args, const yy::location& nameLoc, 
                      const yy::location& argsLoc, bool consAllowed)
{
    int nameIndex = StringToShape(*name, nameLoc, true);

    bool dummy;
    const ASTparameter* bound = findExpression(nameIndex, dummy);
    
    if (bound) {
        if (!consAllowed)
            error(nameLoc + argsLoc, "Cannot bind expression to variable/parameter");
        return MakeVariable(*name, nameLoc)->append(args.release());
    }
    
    if (*name == "select" || *name == "if")
        return new ASTselect(std::move(args), nameLoc + argsLoc, *name == "if");
    
    ASTfunction::FuncType t = ASTfunction::GetFuncType(*name);
    if (t == ASTfunction::Ftime || t == ASTfunction::Frame)
        m_CFDG->addParameter(CFDGImpl::FrameTime);
    if (t != ASTfunction::NotAFunction)
        return new ASTfunction(*name, std::move(args), mSeed, nameLoc, argsLoc);
    
    // If args are parameter reuse args then it must be a rule spec
    if (args && args->mType == ReuseType)
        return MakeRuleSpec(*name, std::move(args), nameLoc + argsLoc);
    
    // At this point we don't know if this is a typo or a to-be-defined shape or
    // user function. Return an ASTuserFunction and fix it up during type check.
    return new ASTuserFunction(nameIndex, args.release(), nullptr, nameLoc);
}

AST::ASTmodification*
Builder::MakeModification(mod_ptr mod, const yy::location& loc, bool canonical)
{
    mod->isConstant = mod->modExp.empty();
    mod->where = loc;
    mod->canonical = canonical;
    
    return mod.release();
}

std::string
Builder::GetTypeInfo(int name, AST::ASTdefine*& func, const AST::ASTparameters*& p)
{
    func = m_CFDG->findFunction(name);
    p = m_CFDG->getShapeParams(name);
    return m_CFDG->decodeShapeName(name);
}

const AST::ASTrule*
Builder::GetRule(int name)
{
    return m_CFDG->findRule(name);
}

void
Builder::push_repContainer(ASTrepContainer& c)
{
    mContainerStack.push_back(&c);
    process_repContainer(c);
}

void
Builder::process_repContainer(ASTrepContainer& c)
{
    c.mStackCount = 0;
    for (ASTparameter& param: c.mParameters) {
        if (param.isParameter || param.isLoopIndex) {
            param.mStackIndex = mLocalStackDepth;
            c.mStackCount += param.mTuplesize;
            mLocalStackDepth += param.mTuplesize;
        } else {
            break;  // the parameters are all in front
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

void
Builder::storeParams(const StackRule* p)
{
    p->mRefCount = StackRule::MaxRefCount;
    m_CFDG->mLongLivedParams.push_back(p);
}
