// astexpression.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2009-2014 John Horigan - john@glyphic.com
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
//


#include "astexpression.h"
#include "builder.h"
#include "rendererAST.h"

#include <math.h>
#include <cassert>

namespace AST {
    
    ASTfunction::ASTfunction(const std::string& func, exp_ptr args, Rand64& r,
                             const yy::location& nameLoc, const yy::location& argsLoc)
    : ASTexpression(nameLoc + argsLoc, true, false, NumericType),
      functype(NotAFunction), arguments(std::move(args))
    {
        if (func.empty()) {
            CfdgError::Error(nameLoc, "bad function call");
            return;
        }
        
        functype = GetFuncType(func);
        
        if (functype == NotAFunction) {
            CfdgError::Error(nameLoc, "Unknown function");
            return;
        }
        
        if (functype == Rand_Static)
            random = r.getDouble();
    }
    
    ASTfunction::FuncType
    ASTfunction::GetFuncType(const std::string& func) 
    {
        static const std::map<std::string, ASTfunction::FuncType> NameMap = {
            { "cos",        ASTfunction::Cos},
            { "sin",        ASTfunction::Sin },
            { "tan",        ASTfunction::Tan },
            { "cot",        ASTfunction::Cot },
            { "acos",       ASTfunction::Acos },
            { "asin",       ASTfunction::Asin },
            { "atan",       ASTfunction::Atan },
            { "acot",       ASTfunction::Acot },
            { "cosh",       ASTfunction::Cosh },
            { "sinh",       ASTfunction::Sinh },
            { "tanh",       ASTfunction::Tanh },
            { "acosh",      ASTfunction::Acosh },
            { "asinh",      ASTfunction::Asinh },
            { "atanh",      ASTfunction::Atanh },
            { "log",        ASTfunction::Log },
            { "log10",      ASTfunction::Log10 },
            { "sqrt",       ASTfunction::Sqrt },
            { "exp",        ASTfunction::Exp },
            { "abs",        ASTfunction::Abs },
            { "floor",      ASTfunction::Floor },
            { "ceiling",    ASTfunction::Ceiling },
            { "infinity",   ASTfunction::Infinity },
            { "factorial",  ASTfunction::Factorial },
            { "sg",         ASTfunction::Sg },
            { "isNatural",  ASTfunction::IsNatural },
            { "bitnot",     ASTfunction::BitNot },
            { "bitor",      ASTfunction::BitOr },
            { "bitand",     ASTfunction::BitAnd },
            { "bitxor",     ASTfunction::BitXOR },
            { "bitleft",    ASTfunction::BitLeft },
            { "bitright",   ASTfunction::BitRight },
            { "atan2",      ASTfunction::Atan2 },
            { "mod",        ASTfunction::Mod },
            { "divides",    ASTfunction::Divides },
            { "div",        ASTfunction::Div },
            { "dot",        ASTfunction::Dot },
            { "cross",      ASTfunction::Cross },
            { "hsb2rgb",    ASTfunction::Hsb2Rgb },
            { "rgb2hsb",    ASTfunction::Rgb2Hsb },
            { "vec",        ASTfunction::Vec },
            { "min",        ASTfunction::Min },
            { "max",        ASTfunction::Max },
            { "ftime",      ASTfunction::Ftime },
            { "frame",      ASTfunction::Frame },
            { "rand_static",        ASTfunction::Rand_Static },
            { "rand",               ASTfunction::Rand },
            { "rand+/-",            ASTfunction::Rand2 },
            { "rand::exponential",  ASTfunction::RandExponential },
            { "rand::gamma",        ASTfunction::RandGamma },
            { "rand::weibull",      ASTfunction::RandWeibull },
            { "rand::extremeV",     ASTfunction::RandExtremeValue },
            { "rand::normal",       ASTfunction::RandNormal },
            { "rand::lognormal",    ASTfunction::RandLogNormal },
            { "rand::chisquared",   ASTfunction::RandChiSquared },
            { "rand::cauchy",       ASTfunction::RandCauchy },
            { "rand::fisherF",      ASTfunction::RandFisherF },
            { "rand::studentT",     ASTfunction::RandStudentT },
            { "randint",            ASTfunction::RandInt },
            { "randint::bernoulli", ASTfunction::RandBernoulli },
            { "randint::binomial",  ASTfunction::RandBinomial },
            { "randint::negbinomial", ASTfunction::RandNegBinomial },
            { "randint::poisson",   ASTfunction::RandPoisson },
            { "randint::discrete",  ASTfunction::RandDiscrete },
            { "randint::geometric", ASTfunction::RandGeometric }
        };
        
        auto nameItem = NameMap.find(func);
        if (nameItem == NameMap.end())
            return NotAFunction;
        return (*nameItem).second;
    }
    
    ASTruleSpecifier::ASTruleSpecifier(int t, const std::string& name, exp_ptr args, 
                                       const yy::location& loc, const ASTparameters* parent)
    : ASTexpression(loc, !args || args->isConstant, false, RuleType),
      shapeType(t), entropyVal(name), argSource(DynamicArgs),
      arguments(args.release()), simpleRule(nullptr), mStackIndex(0),
      typeSignature(nullptr), parentSignature(parent)
    {
        if (parentSignature && parentSignature->empty())
            parentSignature = nullptr;
    }
    
    ASTruleSpecifier::ASTruleSpecifier(int t, const std::string& name, const yy::location& loc)
    : ASTexpression(loc, false, false, RuleType), shapeType(t), argSize(0),
      entropyVal(name), argSource(StackArgs),
      arguments(nullptr), simpleRule(nullptr), mStackIndex(0), typeSignature(nullptr),
      parentSignature(nullptr)
    {
    }
    
    ASTruleSpecifier::ASTruleSpecifier(ASTruleSpecifier&& r)
    : ASTexpression(r.where, r.isConstant, false, r.mType), shapeType(r.shapeType),
      argSize(r.argSize), entropyVal(r.entropyVal), argSource(r.argSource),
      arguments(std::move(r.arguments)), simpleRule(std::move(r.simpleRule)),
      mStackIndex(r.mStackIndex), typeSignature(r.typeSignature),
      parentSignature(r.parentSignature)
    {
    }
    
    ASTruleSpecifier::ASTruleSpecifier(exp_ptr args, const yy::location& loc)
    : ASTexpression(loc, false, false, RuleType), shapeType(-1),
      argSize(0), argSource(ShapeArgs), arguments(std::move(args)),
      simpleRule(nullptr), mStackIndex(0), typeSignature(nullptr),
      parentSignature(nullptr)
    {
        assert(arguments);
    }
    
    void
    ASTruleSpecifier::grab(const ASTruleSpecifier* src)
    {
        assert(src);
        assert(src->isConstant);
        assert(src->argSource != DynamicArgs && src->argSource != ShapeArgs);
        assert(src->argSource != SimpleArgs || src->simpleRule);
        isConstant = true;
        shapeType = src->shapeType;
        argSize = 0;
        argSource = src->argSource;
        arguments.reset();
        simpleRule = std::move(src->simpleRule);
        mStackIndex = 0;
        typeSignature = src->typeSignature;
        parentSignature = src->parentSignature;
    }

    
    param_ptr
    ASTruleSpecifier::evalArgs(RendererAST* rti, const StackRule* parent) const
    {
        switch (argSource) {
        case NoArgs:
        case SimpleArgs:
            return simpleRule;
        case StackArgs: {
            assert(rti);
            const StackType* stackItem = rti->stackItem(mStackIndex);
            return stackItem->rule;
        }
        case ParentArgs:
            assert(parent);
            assert(rti);
            if (shapeType != parent->mRuleName) {
                // Child shape is different from parent, even though parameters are reused,
                // and we can't finesse it in ASTreplacement::traverse(). Just
                // copy the parameters with the correct shape type.
                StackRule* ret = StackRule::alloc(parent);
                ret->mRuleName = static_cast<int16_t>(shapeType);
                return param_ptr(ret);
            }
        case SimpleParentArgs:
            assert(parent);
            assert(rti);
            parent->retain();
            return param_ptr(parent);
        case DynamicArgs: {
            StackRule* ret = StackRule::alloc(shapeType, argSize, typeSignature);
            ret->evalArgs(rti, arguments.get(), parent);
            return param_ptr(ret);
        }
        case ShapeArgs:
            return arguments->evalArgs(rti, parent);
        default:
            assert(false);
            return nullptr;
        }
    }
    
    param_ptr
    ASTparen::evalArgs(RendererAST* rti, const StackRule* parent) const
    {
        if (mType != RuleType) {
            CfdgError::Error(where, "Evaluation of a non-shape expression in a shape context");
            return nullptr;
        }
        
        return e->evalArgs(rti, parent);
    }
    
    param_ptr
    ASTselect::evalArgs(RendererAST* rti, const StackRule* parent) const
    {
        if (mType != RuleType) {
            CfdgError::Error(where, "Evaluation of a non-shape select() in a shape context");
            return nullptr;
        }
        
        return arguments[getIndex(rti)]->evalArgs(rti, parent);
    }
    
    ASTuserFunction::StackSetup::StackSetup(const ASTuserFunction* func, RendererAST* rti)
    : mFunc(func), mRTI(rti),
      mOldTop(rti->mLogicalStackTop), mOldSize(rti->mStackSize)
    {
        if (mFunc->definition->mStackCount) {
            if (mOldSize + mFunc->definition->mStackCount > mRTI->mCFstack.size())
                CfdgError::Error(mFunc->where, "Maximum stack size exceeded");
            mRTI->mStackSize += mFunc->definition->mStackCount;
            mRTI->mCFstack[mOldSize].evalArgs(mRTI, mFunc->arguments.get(), &(mFunc->definition->mParameters), mFunc->isLet);
            mRTI->mLogicalStackTop = mRTI->mCFstack.data() + mRTI->mStackSize;
        }
    }
    
    ASTuserFunction::StackSetup::~StackSetup()
    {
        if (mFunc->definition->mStackCount) {
            mRTI->mCFstack[mOldSize].release(&(mFunc->definition->mParameters));
            mRTI->mStackSize = mOldSize;
            mRTI->mLogicalStackTop = mOldTop;
        }
    }
    
    param_ptr
    ASTuserFunction::evalArgs(RendererAST* rti, const StackRule* parent) const
    {
        if (mType != RuleType) {
            CfdgError::Error(where, "Function does not evaluate to a shape");
            return nullptr;
        }
        
        if (!rti)
            throw DeferUntilRuntime();
        
        if (rti->requestStop || Renderer::AbortEverything)
            throw CfdgError(where, "Stopping");
        
        StackSetup saveIt(this, rti);
        return definition->mExpression->evalArgs(rti, parent);
    }   // saveIt dtor cleans up the stack
    
    ASTcons::ASTcons(std::initializer_list<ASTexpression*> kids)
    : ASTexpression((*(kids.begin()))->where, true, true, NoType)
    // Must have at least one kid or else undefined behavior
    {
        mLocality = PureLocal;
        children.reserve(kids.size());
        for (ASTexpression* kid : kids)
            append(kid);
    };

    ASToperator::ASToperator(char o, ASTexpression* l, ASTexpression* r)
    : ASTexpression(r ? (l->where + r->where) : l->where), op(o), tupleSize(1),
      left(l), right(r)
    {
        static const std::string Ops("NP!+-*/^_<>LG=n&|X");
        size_t pos = Ops.find(op);

        if (pos == std::string::npos) {
            CfdgError::Error(where, "Unknown operator");
        } else if (pos < 3) {
            if (right)
                CfdgError::Error(where, "Operator takes only one operand");
        } else {
            if (!right)
                CfdgError::Error(where, "Operator takes two operands");
        }
    }

    ASTmodTerm::ASTmodTerm(modTypeEnum t, const std::string& paramString, const yy::location& loc)
    : ASTexpression(loc, true, false, ModType), modType(t), args(nullptr), argCount(0)
    {
        static const std::vector<std::pair<std::string, int>> paramStrings = {
            { "evenodd",    CF_EVEN_ODD },
            { "iso",        CF_ISO_WIDTH },
            { "miterjoin",  CF_MITER_JOIN | CF_JOIN_PRESENT },
            { "roundjoin",  CF_ROUND_JOIN | CF_JOIN_PRESENT },
            { "beveljoin",  CF_BEVEL_JOIN | CF_JOIN_PRESENT },
            { "buttcap",    CF_BUTT_CAP   | CF_CAP_PRESENT },
            { "squarecap",  CF_SQUARE_CAP | CF_CAP_PRESENT },
            { "roundcap",   CF_ROUND_CAP  | CF_CAP_PRESENT },
            { "large",      CF_ARC_LARGE },
            { "cw",         CF_ARC_CW },
            { "align",      CF_ALIGN }
        };
        
        for (const auto& pp: paramStrings)
            if (paramString.find(pp.first) != std::string::npos)
                argCount |= pp.second;
    }

    ASTmodification::ASTmodification(const ASTmodification& m, const yy::location& loc)
    : ASTexpression(loc, true, false, ModType), modData(m.modData), 
      modClass(m.modClass), entropyIndex(m.entropyIndex), canonical(m.canonical)
    {
        assert(m.modExp.empty());
    }
    
    ASTmodification::ASTmodification(mod_ptr m, const yy::location& loc)
    : ASTexpression(loc, true, false, ModType), entropyIndex(0), canonical(true)
    {
        if (m) {
            modData.mRand64Seed.seed(0);
            grab(m.get());
        } else {
            modClass = 0;
        }
    }
    
    void
    ASTmodification::grab(AST::ASTmodification* m)
    {
        Rand64 oldEntropy = modData.mRand64Seed;
        modData = m->modData;
        modData.mRand64Seed ^= oldEntropy;
        modExp.swap(m->modExp);
        modClass = m->modClass;
        entropyIndex = (entropyIndex + m->entropyIndex) & 7;
        isConstant = modExp.empty();
        canonical = m->canonical;
    }
    
    ASTselect::ASTselect(exp_ptr args, const yy::location& loc, bool asIf)
    : ASTexpression(loc), tupleSize(-1), indexCache(NotCached),
      selector(std::move(args)), ifSelect(asIf)
    {
        isConstant = false;
        
        if (!selector || selector->size() < 3) {
            CfdgError::Error(loc, "select()/if() function requires arguments");
            return;
        }
    }
    
    ASTvariable::ASTvariable(int stringNum, const std::string& str, const yy::location& loc)
    : ASTexpression(loc), stringIndex(stringNum), text(str), stackIndex(0),
      isParameter(false) { };
    
    ASTuserFunction::ASTuserFunction(int name, ASTexpression* args, ASTdefine* func,
                                     const yy::location& nameLoc)
    : ASTexpression(args ? (nameLoc + args->where) : nameLoc, 
                    false, false, NoType),
      nameIndex(name), definition(func), arguments(args), isLet(false)
    {
    }
    
    ASTlet::ASTlet(cont_ptr args, def_ptr func, const yy::location& letLoc,
                   const yy::location& defLoc)
    : AST::ASTuserFunction(-1, nullptr, func.release(), letLoc), mDefinitions(std::move(args))
    {
        where = where + defLoc;
        isLet = true;
    }
    
    ASTarray::ASTarray(int nameIndex, exp_ptr args,
                       const yy::location& loc, const std::string& name)
    : ASTexpression(loc, false, false, NumericType), mName(nameIndex),
      mArgs(std::move(args)), mLength(1), mStride(1),
      mStackIndex(-1), mCount(0), isParameter(false), entString(name)
    {
    }

    ASTruleSpecifier::~ASTruleSpecifier() = default;
        // simpleRule is deleted along with the long-lived params
    
    ASTcons::~ASTcons() = default;
    
    ASTselect::~ASTselect() = default;
    
    ASTmodification::~ASTmodification() = default;
    
    ASTarray::~ASTarray() = default;
    
    ASTlet::~ASTlet()
    {
        delete definition;
    }

    static void
    Setmod(term_ptr& mod, term_ptr& newmod)
    {
        if (mod)
            CfdgError::Warning(mod->where, "Warning: this term is being dropped");
        mod = std::move(newmod);
    }
    
    void
    ASTmodification::makeCanonical()
    // Receive a vector of modification terms and return an ASTexpression with
    // those terms rearranged into TRSSF canonical order. Duplicate terms are
    // deleted with a warning.
    {
        ASTtermArray temp;
        temp.swap(modExp);
        
        {   // no need for try/catch block to clean up temp array
            term_ptr x;
            term_ptr y;
            term_ptr z;
            term_ptr rot;
            term_ptr skew;
            term_ptr size;
            term_ptr zsize;
            term_ptr flip;
            term_ptr xform;
            
            for (term_ptr& mod: temp) {
                assert(mod);
                
                switch (mod->modType) {
                    case ASTmodTerm::x:
                        Setmod(x, mod);
                        break;
                    case ASTmodTerm::y:
                        Setmod(y, mod);
                        break;
                    case ASTmodTerm::z:
                        Setmod(z, mod);
                        break;
                    case ASTmodTerm::modification:
                    case ASTmodTerm::transform:
                        Setmod(xform, mod);
                        break;
                    case ASTmodTerm::rot:
                        Setmod(rot, mod);
                        break;
                    case ASTmodTerm::size:
                        Setmod(size, mod);
                        break;
                    case ASTmodTerm::zsize:
                        Setmod(zsize, mod);
                        break;
                    case ASTmodTerm::skew:
                        Setmod(skew, mod);
                        break;
                    case ASTmodTerm::flip:
                        Setmod(flip, mod);
                        break;
                    default:
                        modExp.push_back(std::move(mod));
                        break;
                }
            }
            
            temp.clear();
            
            if (    x) modExp.push_back(std::move(x));
            if (    y) modExp.push_back(std::move(y));
            if (    z) modExp.push_back(std::move(z));
            if (  rot) modExp.push_back(std::move(rot));
            if ( size) modExp.push_back(std::move(size));
            if (zsize) modExp.push_back(std::move(zsize));
            if ( skew) modExp.push_back(std::move(skew));
            if ( flip) modExp.push_back(std::move(flip));
            if (xform) modExp.push_back(std::move(xform));
        }
    }
    
    ASTexpression*
    ASTexpression::Append(ASTexpression* l, ASTexpression* r)
    {
        if (l && r) return l->append(r);
        return l ? l : r;
    }
    
    ASTexpression*
    ASTexpression::append(AST::ASTexpression *sib)
    {
        return sib ? new ASTcons{ this, sib } : this;
    }
    
    ASTexpression*
    ASTcons::append(AST::ASTexpression *sib)
    {
        if (!sib) return this;
        where = where + sib->where;
        isConstant = isConstant && sib->isConstant;
        isNatural = isNatural && sib->isNatural;
        mLocality = CombineLocality(mLocality, sib->mLocality);
        mType = static_cast<expType>(mType | sib->mType);
        
        // Cannot insert an ASTcons into children, it will be flattened away.
        // You must wrap the ASTcons in an ASTparen in order to insert it whole.
        
        if (ASTcons* c = dynamic_cast<ASTcons*>(sib)) {
            children.reserve(children.size() + c->children.size());
            std::move(c->children.begin(), c->children.end(), std::back_inserter(children));
            delete sib;
        } else {
            children.emplace_back(sib);
        }
        return this;
    }
    
    const ASTexpression*
    ASTexpression::getChild(size_t i) const
    {
        if (i)
            CfdgError::Error(where, "Expression list bounds exceeded");
        return this;
    }
    
    const ASTexpression*
    ASTcons::getChild(size_t i) const
    {
        if (i >= children.size()) {
            CfdgError::Error(where, "Expression list bounds exceeded");
            return this;
        }
        return children[i].get();
    }
    
    // Evaluate a cons tree to see how many reals it has and optionally
    // copy them to an array
    int
    ASTcons::evaluate(double* res, int length, RendererAST* rti) const
    {
        if ((static_cast<int>(mType) & (NumericType | FlagType)) == 0 ||
            (static_cast<int>(mType) & (ModType | RuleType)))
        {
            CfdgError::Error(where, "Non-numeric expression in a numeric context");
            return -1;
        }
        
        int count = 0;
        for (size_t i = 0; i < children.size(); ++i) {
            int num = children[i]->evaluate(res, length, rti);
            if (num <= 0)
                return -1;
            count += num;
            if (res) {
                res += num;
                length -= num;
            }
        }
        
        return count;
    }
    
    int
    ASTreal::evaluate(double* res, int length, RendererAST*) const
    {
        if (res && length < 1)
            return -1;
        if (res) 
            *res = value;
        return 1;
    }
    
    int
    ASTvariable::evaluate(double* res, int length, RendererAST* rti) const
    {
        if (mType != NumericType) {
            CfdgError::Error(where, "Non-numeric variable in a numeric context");
            return -1;
        }
        if (res && (length < count))
            return -1;
        if (res) {
            if (rti == nullptr) throw DeferUntilRuntime();
            const StackType* stackItem = rti->stackItem(stackIndex);
            for (int i = 0; i < count; ++i)
                res[i] = stackItem[i].number;
        }
        
        return count;
    }
    
    int
    ASTuserFunction::evaluate(double* res, int length, RendererAST* rti) const
    {
        if (mType != NumericType) {
            CfdgError::Error(where, "Function does not evaluate to a number");
            return -1;
        }
        if (res && length < definition->mTuplesize)
            return -1;
        if (!res)
            return definition->mTuplesize;
        if (!rti)
            throw DeferUntilRuntime();
        
        if (rti->requestStop || Renderer::AbortEverything)
            throw CfdgError(where, "Stopping");
        
        StackSetup saveIt(this, rti);
        if (definition->mExpression->evaluate(res, length, rti) != definition->mTuplesize)
            CfdgError::Error(where, "Error evaluating function");
        return definition->mTuplesize;
    }   // saveIt dtor cleans up stack
    
    int
    ASToperator::evaluate(double* res, int length, RendererAST* rti) const
    {
        double l[AST::MaxVectorSize];
        double r[AST::MaxVectorSize];
        
        if (res && length < 1)
            return -1;
        
        if (mType == FlagType && op == '+') {
            if (left->evaluate(res ? l : nullptr, 1, rti) != 1)
                return -1;
            if (!right || right->evaluate(res ? r : nullptr, 1, rti) != 1)
                return -1;
            int f = static_cast<int>(l[0]) | static_cast<int>(r[0]);
            if (res)
                *res = static_cast<double>(f);
            return 1;
        }
        
        if (mType != NumericType) {
            CfdgError::Error(where, "Non-numeric expression in a numeric context");
            return -1;
        }
        
        int leftnum = left->evaluate(res ? l : nullptr, AST::MaxVectorSize, rti);
        if (leftnum == -1) {
            CfdgError::Error(left->where, "illegal operand");
            return -1;
        }
        
        // short-circuit evaluate && and ||
        if (res && (op == '&' || op == '|')) {
            if (l[0] != 0.0 && op == '|') {
                *res = l[0];
                return 1;
            }
            if (l[0] == 0.0 && op == '&') {
                *res = 0.0;
                return 1;
            }
        }
        
        int rightnum = right ? right->evaluate(res ? r : nullptr, AST::MaxVectorSize, rti) : 0;
        if (right && rightnum == -1) {
            CfdgError::Error(right->where, "illegal operand");
            return -1;
        }
        
        if (rightnum == 0 && (op == 'N' || op == 'P' || op == '!')) {
            if (res) {
                switch (op) {
                    case 'P':
                        for (int i = 0 ; i < tupleSize; ++i)
                            res[i] = l[i];
                        break;
                    case 'N':
                        for (int i = 0 ; i < tupleSize; ++i)
                            res[i] = -l[i];
                        break;
                    case '!':
                        *res = (l[0] == 0.0) ? 1.0 : 0.0;
                        break;
                    default:
                        return -1;
                }
            }
            return 1;
        }
        
        if (res) {
            switch(op) {
                case '+':
                    for (int i = 0 ; i < tupleSize; ++i)
                        res[i] = l[i] + r[i];
                    break;
                case '-':
                    for (int i = 0 ; i < tupleSize; ++i)
                        res[i] = l[i] - r[i];
                    break;
                case '_':
                    for (int i = 0 ; i < tupleSize; ++i)
                        res[i] = ((l[i] - r[i]) > 0.0) ? (l[i] - r[i]) : 0.0;
                    break;
                case '*':
                    for (int i = 0 ; i < tupleSize; ++i)
                        res[i] = l[i] * r[i];
                    break;
                case '/':
                    for (int i = 0 ; i < tupleSize; ++i)
                        res[i] = l[i] / r[i];
                    break;
                case '<':
                    *res = (l[0] < r[0]) ? 1.0 : 0.0;
                    break;
                case 'L':
                    *res = (l[0] <= r[0]) ? 1.0 : 0.0;
                    break;
                case '>':
                    *res = (l[0] > r[0]) ? 1.0 : 0.0;
                    break;
                case 'G':
                    *res = (l[0] >= r[0]) ? 1.0 : 0.0;
                    break;
                case '=':
                    *res = 0.0;
                    for (int i = 0; i < tupleSize; ++i)
                        if (l[i] != r[i])
                            return 1;
                    *res = 1.0;
                    break;
                case 'n':
                    *res = 1.0;
                    for (int i = 0; i < tupleSize; ++i)
                        if (l[i] != r[i])
                            return 1;
                    *res = 0.0;
                    break;
                case '&':
                case '|':
                    *res = r[0];
                    break;
                case 'X':
                    *res = ((l[0] != 0.0 && r[0] == 0.0) || (l[0] == 0.0 && r[0] != 0.0)) ? 1.0 : 0.0;
                    break;
                case '^':
                    *res = pow(l[0], r[0]);
                    if (isNatural && *res < 9007199254740992.) {
                        uint64_t pow = 1;
                        uint64_t il = static_cast<uint64_t>(l[0]);
                        uint64_t ir = static_cast<uint64_t>(r[0]);
                        while (ir) {
                            if (ir & 1) pow *= il;
                            il *= il;
                            ir >>= 1;
                        }
                        *res = static_cast<double>(pow);
                    }
                    break;
                default:
                    return -1;
            }
        } else {
            if (strchr("+-*/^_<>LG=n&|X", op) == nullptr)
                return -1;
        }
        
        return tupleSize;
    }
    
    static double MinMax(const ASTexpression* e, RendererAST* rti, bool isMin)
    {
        double res = 0.0;
        if (e->getChild(0)->evaluate(&res, 1, rti) != 1)
            CfdgError::Error(e->getChild(0)->where, "Error computing min/max here.");
        for (size_t i = 1; i < e->size(); ++i) {
            double v;
            if (e->getChild(i)->evaluate(&v, 1, rti) != 1)
                CfdgError::Error(e->getChild(i)->where, "Error computing min/max here.");
            bool leftMin = res < v;
            res = ((isMin && leftMin) || (!isMin && !leftMin)) ? res : v;
        }
        return res;
    }
    
    int 
    ASTfunction::evaluate(double* res, int length, RendererAST* rti) const
    {
        if (mType != NumericType) {
            CfdgError::Error(where, "Non-numeric expression in a numeric context");
            return -1;
        }
        
        const int destLength = functype >= Cross && functype <= Rgb2Hsb ? 3
                             : functype == Vec   ? static_cast<int>(floor(random))
                             : 1;
        
        if (!res)
            return destLength;
        
        if (length < destLength)
            return -1;
        
        switch (functype) {
            case Min:
            case Max:
                *res = MinMax(arguments.get(), rti, functype == Min);
                return 1;
            case Dot: {
                double l[AST::MaxVectorSize];
                double r[AST::MaxVectorSize];
                int lc = arguments->getChild(0)->evaluate(l, AST::MaxVectorSize, rti);
                int rc = arguments->getChild(1)->evaluate(r, AST::MaxVectorSize, rti);
                if (lc == rc && lc > 1) {
                    *res = 0.0;
                    for (int i = 0; i < lc; ++i)
                        *res += l[i] * r[i];
                }
                return 1;
            }
            case Cross: {
                double l[3];
                double r[3];
                if (arguments->getChild(0)->evaluate(l, 3, rti) == 3 &&
                    arguments->getChild(1)->evaluate(r, 3, rti) == 3)
                {
                    res[0] = l[1]*r[2] - l[2]*r[1];
                    res[1] = l[2]*r[0] - l[0]*r[2];
                    res[2] = l[0]*r[1] - l[1]*r[0];
                }
                return 3;
            }
            case Vec: {
                double l[AST::MaxVectorSize];
                int lc = arguments->getChild(0)->evaluate(l, AST::MaxVectorSize, rti);
                if (lc >= 1)
                    for (int i = 0; i < destLength; ++i)
                        res[i] = l[i % lc];
                return destLength;
            }
            case Hsb2Rgb: {
                double c[3];
                if (arguments->evaluate(c, 3, rti) == 3) {
                    agg::rgba rgb;
                    HSBColor hsb(c[0], c[1], c[2], 1.0);
                    hsb.getRGBA(rgb);
                    res[0] = rgb.r; res[1] = rgb.g; res[2] = rgb.b;
                }
                return 3;
            }
            case Rgb2Hsb: {
                double c[3];
                if (arguments->evaluate(c, 3, rti) == 3) {
                    agg::rgba rgb(c[0], c[1], c[2], 1.0);
                    HSBColor hsb(rgb);
                    res[0] = hsb.h; res[1] = hsb.s; res[2] = hsb.b;
                }
                return 3;
            }
            case RandDiscrete: {
                double w[AST::MaxVectorSize];
                int wc = arguments->evaluate(w, AST::MaxVectorSize, rti);
                if (wc >= 1)
                    *res = static_cast<double>(rti->mCurrentSeed.getDiscrete(wc, w));
                return 1;
            }
            default:
                break;
        }
        
        double a[2];
        int count = arguments->evaluate(a, 2, rti);
        // no need to check the argument count, the constructor already checked it
        
        // But check it anyway to make valgrind happy
        if (count < 0) return 1;

        switch (functype) {
            case  Cos:  
                *res = cos(a[0] * 0.0174532925199);
                break;
            case  Sin:  
                *res = sin(a[0] * 0.0174532925199);
                break;
            case  Tan:  
                *res = tan(a[0] * 0.0174532925199);
                break;
            case  Cot:  
                *res = 1.0 / tan(a[0] * 0.0174532925199);
                break;
            case  Acos:  
                *res = acos(a[0]) * 57.29577951308;
                break;
            case  Asin:  
                *res = asin(a[0]) * 57.29577951308;
                break;
            case  Atan:  
                *res = atan(a[0]) * 57.29577951308;
                break;
            case  Acot:  
                *res = atan(1.0 / a[0]) * 57.29577951308;
                break;
            case  Cosh:  
                *res = cosh(a[0]);
                break;
            case  Sinh:  
                *res = sinh(a[0]);
                break;
            case Tanh:  
                *res = tanh(a[0]);
                break;
            case Acosh:  
                *res = acosh(a[0]);
                break;
            case Asinh:  
                *res = asinh(a[0]);
                break;
            case Atanh:  
                *res = atanh(a[0]);
                break;
            case Log:  
                *res = log(a[0]);
                break;
            case Log10:  
                *res = log10(a[0]);
                break;
            case Sqrt:  
                *res = sqrt(a[0]);
                break;
            case Exp:  
                *res = exp(a[0]);
                break;
            case Abs:  
                if (count == 1)
                    *res = fabs(a[0]);
                else 
                    *res = fabs(a[0] - a[1]);
                break;
            case Infinity:
                *res = (a[0] < 0.0) ? (-Renderer::Infinity) : (Renderer::Infinity);
                break;
            case Factorial:
                if (a[0] < 0.0 || a[0] > 18.0 ||a[0] != floor(a[0]))
                    CfdgError::Error(this->where, "Illegal argument for factorial");
                *res = 1.0;
                for (double v = 1.0; v <= a[0]; v += 1.0) *res *= v;
                break;
            case Sg:
                *res = a[0] == 0.0 ? 0.0 : 1.0;
                break;
            case IsNatural:
                *res = RendererAST::isNatural(rti, a[0]);
                break;
            case BitNot:
                *res = static_cast<double>(~static_cast<uint64_t>(a[0]) & 0xfffffffffffffull);
                break;
            case BitOr:
                *res = static_cast<double>((static_cast<uint64_t>(a[0]) | static_cast<uint64_t>(a[1])) & 0xfffffffffffffull);
                break;
            case BitAnd:
                *res = static_cast<double>((static_cast<uint64_t>(a[0]) & static_cast<uint64_t>(a[1])) & 0xfffffffffffffull);
                break;
            case BitXOR:
                *res = static_cast<double>((static_cast<uint64_t>(a[0]) ^ static_cast<uint64_t>(a[1])) & 0xfffffffffffffull);
                break;
            case BitLeft:
                *res = static_cast<double>((static_cast<uint64_t>(a[0]) << static_cast<uint64_t>(a[1])) & 0xfffffffffffffull);
                break;
            case BitRight:
                *res = static_cast<double>((static_cast<uint64_t>(a[0]) >> static_cast<uint64_t>(a[1])) & 0xfffffffffffffull);
                break;
            case Atan2: 
                *res = atan2(a[0], a[1]) * 57.29577951308;
                break;
            case Mod: 
                if (arguments->isNatural)
                    *res = static_cast<double>(static_cast<uint64_t>(a[0]) % static_cast<uint64_t>(a[1]));
                else
                    *res = fmod(a[0], a[1]);
                break;
            case Divides:
                *res = (static_cast<uint64_t>(a[0]) % static_cast<uint64_t>(a[1]) == 0ULL) ? 1.0 : 0.0;
                break;
            case Div:
                *res = static_cast<double>(static_cast<uint64_t>(a[0]) / static_cast<uint64_t>(a[1]));
                break;
            case Floor:
                *res = floor(a[0]);
                break;
            case Ceiling:
                *res = ceil(a[0]);
                break;
            case Ftime:
                if (rti == nullptr) throw DeferUntilRuntime();
                *res = rti->mCurrentTime;
                break;
            case Frame:
                if (rti == nullptr) throw DeferUntilRuntime();
                *res = rti->mCurrentFrame;
                break;
            case Rand_Static: 
                *res = random * fabs(a[1] - a[0]) + fmin(a[0], a[1]);
                break;
            case Rand: 
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = rti->mCurrentSeed.getDouble() * fabs(a[1] - a[0]) + fmin(a[0], a[1]);
                break;
            case Rand2: 
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = (rti->mCurrentSeed.getDouble() * 2.0 - 1.0) * a[1] + a[0];
                break;
            case RandExponential:
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = rti->mCurrentSeed.getExponential(a[0]);
                break;
            case RandGamma:
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = rti->mCurrentSeed.getGamma(a[0], a[1]);
                break;
            case RandWeibull:
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = rti->mCurrentSeed.getWeibull(a[0], a[1]);
                break;
            case RandExtremeValue:
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = rti->mCurrentSeed.getExtremeValue(a[0], a[1]);
                break;
            case RandNormal:
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = rti->mCurrentSeed.getNormal(a[0], a[1]);
                break;
            case RandLogNormal:
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = rti->mCurrentSeed.getLogNormal(a[0], a[1]);
                break;
            case RandChiSquared:
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = rti->mCurrentSeed.getChiSquared(a[0]);
                break;
            case RandCauchy:
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = rti->mCurrentSeed.getCauchy(a[0], a[1]);
                break;
            case RandFisherF:
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = rti->mCurrentSeed.getFisherF(a[0], a[1]);
                break;
            case RandStudentT:
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = rti->mCurrentSeed.getStudentT(a[0]);
                break;
            case RandInt:
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = floor(rti->mCurrentSeed.getDouble() * fabs(a[1] - a[0]) + fmin(a[0], a[1]));
                break;
            case RandBernoulli:
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = rti->mCurrentSeed.getBernoulli(a[0]) ? 1.0 : 0.0;
                break;
            case RandBinomial:
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = floor(static_cast<double>(rti->mCurrentSeed.getBinomial(static_cast<Rand64::result_type>(a[0]), a[1])));
                break;
            case RandNegBinomial:
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = floor(static_cast<double>(rti->mCurrentSeed.getNegativeBinomial(static_cast<Rand64::result_type>(a[0]), a[1])));
                break;
            case RandPoisson:
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = floor(rti->mCurrentSeed.getPoisson(a[0]));
                break;
            case RandGeometric:
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = floor(rti->mCurrentSeed.getGeometric(a[0]));
                break;
            default:
                return -1;
        }
        
        return 1;
    }
    
    int 
    ASTselect::evaluate(double* res, int length, RendererAST* rti) const
    {
        if (mType != NumericType) {
            CfdgError::Error(where, "Evaluation of a non-numeric select() in a numeric context");
            return -1;
        }
        
        if (res == nullptr)
            return tupleSize;
        
        return arguments[getIndex(rti)]->evaluate(res, length, rti);
    }
    
    int
    ASTruleSpecifier::evaluate(double* , int , RendererAST* ) const
    {
        CfdgError::Error(where, "Improper evaluation of a rule specifier");
        return -1;
    }
    
    int 
    ASTparen::evaluate(double* res, int length, RendererAST* rti) const
    {
        if (mType != NumericType) {
            CfdgError::Error(where, "Non-numeric/flag expression in a numeric/flag context");
            return -1;
        }
        return e->evaluate(res, length, rti);
    }
    
    int
    ASTmodTerm::evaluate(double* , int , RendererAST* ) const
    {
        CfdgError::Error(where, "Improper evaluation of an adjustment expression");
        return -1;
    }
    
    int
    ASTmodification::evaluate(double* , int , RendererAST* ) const
    {
        CfdgError::Error(where, "Improper evaluation of an adjustment expression");
        return -1;
    }
    
    int
    ASTarray::evaluate(double* res, int length, RendererAST* rti) const
    {
        if (mType != NumericType) {
            CfdgError::Error(where, "Non-numeric/flag expression in a numeric/flag context");
            return -1;
        }
        if (res && (length < mLength))
            return -1;
        
        if (res) {
            if (rti == nullptr && (!mData || !mArgs->isConstant)) throw DeferUntilRuntime();
            
            double index_d;
            if (mArgs->evaluate(&index_d, 1, rti) != 1) {
                CfdgError::Error(mArgs->where, "Cannot evaluate vector index");
                return -1;
            }
            int index = static_cast<int>(index_d);
            if ((mLength - 1) * mStride + index >= mCount || index < 0) {
                CfdgError::Error(where, "Vector index exceeds bounds");
                return -1;
            }
            
            const double* source = mData.get();
            if (!source)
                source = &(rti->stackItem(mStackIndex)->number);
            
            for (int i = 0; i < mLength; ++i)
                res[i] = source[i * mStride + index];
        }
        
        return mLength;
    }
    
    void
    ASTselect::evaluate(Modification& m, bool shapeDest, RendererAST* rti) const
    {
        if (mType != ModType) {
            CfdgError::Error(where, "Evaluation of a non-adjustment select() in an adjustment context");
            return;
        }
        
        arguments[getIndex(rti)]->evaluate(m, shapeDest, rti);
    }
    
    void
    ASTvariable::evaluate(Modification& m, bool shapeDest, RendererAST* rti) const
    {
        if (mType != ModType)
            CfdgError::Error(where, "Non-adjustment variable referenced in an adjustment context");
        
        if (rti == nullptr) throw DeferUntilRuntime();
        const StackType* stackItem = rti->stackItem(stackIndex);
        const Modification* smod = reinterpret_cast<const Modification*> (stackItem);
        if (shapeDest) {
            m *= *smod;
        } else {
            if (m.merge(*smod))
                RendererAST::ColorConflict(rti, where);
        }
    }
    
    void
    ASTcons::evaluate(Modification& m, bool shapeDest, RendererAST* rti) const
    {
        for (size_t i = 0; i < children.size(); ++i)
            children[i]->evaluate(m, shapeDest, rti);
    }
    
    void
    ASTuserFunction::evaluate(Modification &m, bool shapeDest, RendererAST* rti) const
    {
        if (mType != ModType) {
            CfdgError::Error(where, "Function does not evaluate to an adjustment");
            return;
        }
        
        if (!rti)
            throw DeferUntilRuntime();
        
        if (rti->requestStop || Renderer::AbortEverything)
            throw CfdgError(where, "Stopping");
        
        StackSetup saveIt(this, rti);
        definition->mExpression->evaluate(m, shapeDest, rti);
    }   // saveIt dtor cleans up stack
    
    void
    ASTmodification::evaluate(Modification& m, bool shapeDest, RendererAST* rti) const
    {
        if (shapeDest) {
            m *= modData;
        } else {
            if (m.merge(modData))
                RendererAST::ColorConflict(rti, where);
        }
        
        for (const term_ptr& term: modExp)
            term->evaluate(m, shapeDest, rti);
    }
    
    void
    ASTmodification::setVal(Modification& m, RendererAST* rti) const
    {
        m = modData;
        for (const term_ptr& term: modExp)
            term->evaluate(m, false, rti);
    }
    
    void
    ASTparen::evaluate(Modification& m, bool shapeDest, RendererAST* rti) const
    {
        if (mType != ModType) {
            CfdgError::Error(where, "Expression does not evaluate to an adjustment");
            return;
        }
        
        e->evaluate(m, shapeDest, rti);
    }
    
    void
    ASTmodTerm::evaluate(Modification& m, bool shapeDest, RendererAST* rti) const
    {
        double modArgs[6] = {0.0};
        int argcount = 0;
        static_assert(offsetof(HSBColor, s) - offsetof(HSBColor, h) == sizeof(double) * (ASTmodTerm::sat - ASTmodTerm::hue), "Unexpected HSBcolor layout");
        static_assert(offsetof(HSBColor, b) - offsetof(HSBColor, h) == sizeof(double) * (ASTmodTerm::bright - ASTmodTerm::hue), "Unexpected HSBcolor layout");
        static_assert(offsetof(HSBColor, a) - offsetof(HSBColor, h) == sizeof(double) * (ASTmodTerm::alpha - ASTmodTerm::hue), "Unexpected HSBcolor layout");
        static_assert(offsetof(HSBColor, s) - offsetof(HSBColor, h) == sizeof(double) * (ASTmodTerm::satTarg - ASTmodTerm::hueTarg), "Unexpected HSBcolor layout");
        static_assert(offsetof(HSBColor, b) - offsetof(HSBColor, h) == sizeof(double) * (ASTmodTerm::brightTarg - ASTmodTerm::hueTarg), "Unexpected HSBcolor layout");
        static_assert(offsetof(HSBColor, a) - offsetof(HSBColor, h) == sizeof(double) * (ASTmodTerm::alphaTarg - ASTmodTerm::hueTarg), "Unexpected HSBcolor layout");
        static_assert(offsetof(HSBColor, s) - offsetof(HSBColor, h) == sizeof(double) * (ASTmodTerm::targSat - ASTmodTerm::targHue), "Unexpected HSBcolor layout");
        static_assert(offsetof(HSBColor, b) - offsetof(HSBColor, h) == sizeof(double) * (ASTmodTerm::targBright - ASTmodTerm::targHue), "Unexpected HSBcolor layout");
        static_assert(offsetof(HSBColor, a) - offsetof(HSBColor, h) == sizeof(double) * (ASTmodTerm::targAlpha - ASTmodTerm::targHue), "Unexpected HSBcolor layout");
        
        if (args) {
            if (modType != modification && args->mType == NumericType) {
                argcount = args->evaluate(modArgs, 6, rti);
            } else if (modType == modification && args->mType != ModType){
                CfdgError::Error(where, "Adjustments require numeric arguments");
                return;
            }
        }
        
        if (argcount != argCount) {
            CfdgError::Error(where, "Error evaluating arguments");
            return;
        }
        
        double arg[6] = {0.0};
        for (int i = 0; i < argcount; ++i)
            arg[i] = fmax(-1.0, fmin(1.0, modArgs[i]));
        
        double *color = &m.m_Color.h, *target = &m.m_ColorTarget.h;
        bool hue = true;
        int mask = HSBColor::HueMask;
        
        switch (modType) {
            case ASTmodTerm::x: {
                if (argcount == 1)
                    modArgs[1] = 0.0;
                agg::trans_affine_translation trx(modArgs[0], modArgs[1]);
                m.m_transform.premultiply(trx);
                break;
            }
            case ASTmodTerm::y: {
                agg::trans_affine_translation tr(0.0, modArgs[0]);
                m.m_transform.premultiply(tr);
                break;
            }
            case ASTmodTerm::z: {
                agg::trans_affine_1D_translation tr(modArgs[0]);
                m.m_Z.premultiply(tr);
                break;
            }
            case ASTmodTerm::xyz: {
                agg::trans_affine_translation trx(modArgs[0], modArgs[1]);
                m.m_transform.premultiply(trx);
                agg::trans_affine_1D_translation trz(modArgs[2]);
                m.m_Z.premultiply(trz);
                break;
            }
            case ASTmodTerm::time: {
                agg::trans_affine_time_translation tr(modArgs[0], modArgs[1]);
                m.m_time.premultiply(tr);
                break;
            }
            case ASTmodTerm::timescale: {
                agg::trans_affine_time_scaling sc(modArgs[0]);
                m.m_time.premultiply(sc);
                break;
            }
            case ASTmodTerm::transform: {
                switch (argcount) {
                    case 2:
                    case 1: {
                        if (argcount == 1) 
                            modArgs[1] = 0.0;
                        agg::trans_affine_translation trx(modArgs[0], modArgs[1]);
                        m.m_transform.premultiply(trx);
                        break;
                    }
                    case 4: {
                        agg::trans_affine sq;
                        double dx = modArgs[2] - modArgs[0];
                        double dy = modArgs[3] - modArgs[1];
                        sq.scale(sqrt(dx * dx + dy * dy));
                        sq.rotate(atan2(dy, dx));
                        sq.translate(modArgs[0], modArgs[1]);
                        m.m_transform.premultiply(sq);
                        break;
                    }
                    case 6: {
                        agg::trans_affine par;
                        par.rect_to_parl(0.0, 0.0, 1.0, 1.0, modArgs);
                        m.m_transform.premultiply(par);
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case ASTmodTerm::size: {
                if (argcount == 1)
                    modArgs[1] = modArgs[0];
                agg::trans_affine_scaling sc(modArgs[0], modArgs[1]);
                m.m_transform.premultiply(sc);
                break;
            }
            case ASTmodTerm::sizexyz: {
                agg::trans_affine_scaling sc(modArgs[0], modArgs[1]);
                m.m_transform.premultiply(sc);
                agg::trans_affine_1D_scaling scz(modArgs[2]);
                m.m_Z.premultiply(scz);
                break;
            }
            case ASTmodTerm::zsize: {
                agg::trans_affine_1D_scaling sc(modArgs[0]);
                m.m_Z.premultiply(sc);
                break;
            }
            case ASTmodTerm::rot: {
                agg::trans_affine_rotation rot(modArgs[0] * MY_PI / 180.0);
                m.m_transform.premultiply(rot);
                break;
            }
            case ASTmodTerm::skew: {
                agg::trans_affine_skewing sk(modArgs[0] * MY_PI / 180.0,
                                             modArgs[1] * MY_PI / 180.0);
                m.m_transform.premultiply(sk);
                break;
            }
            case ASTmodTerm::flip: {
                agg::trans_affine_reflection ref(modArgs[0] * MY_PI / 180.0);
                m.m_transform.premultiply(ref);
                break;
            }
            case ASTmodTerm::alpha:
            case ASTmodTerm::bright:
            case ASTmodTerm::sat:
                color += modType - ASTmodTerm::hue;
                target += modType - ASTmodTerm::hue;
                mask <<= 2 * (modType - ASTmodTerm::hue);
                hue = false;
            case ASTmodTerm::hue: {
                if (argcount != 2) {
                    // One argument changes hue, 3 changes hsb, 4 changes hsba
                    for (int i = 0; i < argcount; ++i) {
                        if ((m.m_ColorAssignment & mask) || (!hue && *color != 0.0)) {
                            if (rti == nullptr)
                                throw DeferUntilRuntime();
                            if (!shapeDest)
                                RendererAST::ColorConflict(rti, where);
                        }
                        if (shapeDest)
                            *color = hue ? HSBColor::adjustHue(*color, modArgs[i])
                                         : HSBColor::adjust(*color, arg[i]);
                        else
                            *color = hue ? *color + modArgs[i] : arg[i];
                        ++color; mask <<= 2; hue = false;
                    }
                } else {
                    if ((m.m_ColorAssignment & mask) || *color != 0.0 ||
                        (!hue && *target != 0.0))
                    {
                        if (rti == nullptr)
                            throw DeferUntilRuntime();
                        if (!shapeDest)
                            RendererAST::ColorConflict(rti, where);
                    }
                    if (shapeDest) {
                        *color = hue ? HSBColor::adjustHue(*color, arg[0],
                                                           HSBColor::HueTarget,
                                                           modArgs[1])
                                     : HSBColor::adjust(*color, arg[0], 1, arg[1]);
                    } else {
                        *color = arg[0];
                        *target = hue ? modArgs[1] : arg[1];
                        m.m_ColorAssignment |= HSBColor::HSBA2Value & mask;
                    }
                }
                break;
            }
            case ASTmodTerm::alphaTarg:
            case ASTmodTerm::brightTarg:
            case ASTmodTerm::satTarg:
                color += modType - ASTmodTerm::hueTarg;
                target += modType - ASTmodTerm::hueTarg;
                mask <<= 2 * (modType - ASTmodTerm::hueTarg);
                hue = false;
            case ASTmodTerm::hueTarg: {
                if ((m.m_ColorAssignment & mask) || *color != 0.0) {
                    if (rti == nullptr)
                        throw DeferUntilRuntime();
                    if (!shapeDest)
                        RendererAST::ColorConflict(rti, where);
                }
                if (shapeDest) {
                    *color = hue ? HSBColor::adjustHue(*color, arg[0],
                                                       HSBColor::HueTarget,
                                                       *target)
                                 : HSBColor::adjust(*color, arg[0], 1, *target);
                } else {
                    *color = arg[0];
                    m.m_ColorAssignment |= HSBColor::HSBATarget & mask;
                }
                break;
            }
            case ASTmodTerm::targAlpha:
            case ASTmodTerm::targBright:
            case ASTmodTerm::targSat: {
                target += modType - ASTmodTerm::targHue;
                if (*target != 0.0) {
                    if (rti == nullptr)
                        throw DeferUntilRuntime();
                    if (!shapeDest)
                        RendererAST::ColorConflict(rti, where);
                }
                if (shapeDest)
                    *target = HSBColor::adjust(*target, arg[0]);
                else
                    *target = arg[0];
                break;
            }
            case ASTmodTerm::targHue: {
                m.m_ColorTarget.h += modArgs[0];
                break;
            }
            case ASTmodTerm::stroke: {
                CfdgError::Error(where, "Cannot provide a stroke width in this context");
                break;
            }
            case ASTmodTerm::x1:
            case ASTmodTerm::y1:
            case ASTmodTerm::x2:
            case ASTmodTerm::y2:
            case ASTmodTerm::xrad:
            case ASTmodTerm::yrad:
                CfdgError::Error(where, "Cannot provide a path operation term in this context");
                break;
            case ASTmodTerm::param:
                CfdgError::Error(where, "Cannot provide a parameter in this context");
                break;
            case ASTmodTerm::unknownType:
                CfdgError::Error(where, "Unrecognized adjustment type");
                break;
            case ASTmodTerm::modification: {
                if (rti == nullptr) {
                    const ASTmodification* mod = dynamic_cast<const ASTmodification*>(args.get());
                    if (!mod || (mod->modClass & (ASTmodification::HueClass |
                                                  ASTmodification::HueTargetClass |
                                                  ASTmodification::BrightClass |
                                                  ASTmodification::BrightTargetClass |
                                                  ASTmodification::SatClass |
                                                  ASTmodification::SatTargetClass |
                                                  ASTmodification::AlphaClass |
                                                  ASTmodification::AlphaTargetClass)))
                    {
                        throw DeferUntilRuntime();
                    }
                }
                args->evaluate(m, shapeDest, rti);
                break;
            }
        }
    }
    
    void
    ASTfunction::entropy(std::string& ent) const
    {
        // These random strings are courtesy of http://www.fourmilab.ch/hotbits/
        static const std::map<ASTfunction::FuncType, const char*> EntropyMap = {
            { ASTfunction::Cos,         "\xA1\xE7\x9C\x1A\xAF\x7D" },
            { ASTfunction::Sin,         "\xAF\x58\xFE\x2C\xD4\x53" },
            { ASTfunction::Tan,         "\x95\xFF\x59\x11\x03\x02" },
            { ASTfunction::Cot,         "\x77\xF5\xB6\x35\x8C\xF0" },
            { ASTfunction::Acos,        "\x3A\xCD\x79\x3E\xAD\xB4" },
            { ASTfunction::Asin,        "\x1D\x75\x0B\xBC\x5F\x52" },
            { ASTfunction::Atan,        "\x0B\xC8\x89\xAB\xF8\xB7" },
            { ASTfunction::Acot,        "\x69\x7C\xC7\x1A\xF6\x7B" },
            { ASTfunction::Cosh,        "\x48\x43\x43\x35\x62\x81" },
            { ASTfunction::Sinh,        "\x51\x62\xFB\x76\xED\x9C" },
            { ASTfunction::Tanh,        "\xBB\x91\x54\xA9\x63\x84" },
            { ASTfunction::Acosh,       "\x4F\x28\x48\x20\xB7\x5C" },
            { ASTfunction::Asinh,       "\x6C\x9B\x32\xAA\x4C\xD0" },
            { ASTfunction::Atanh,       "\x58\xEC\xBB\x25\xF8\xB6" },
            { ASTfunction::Log,         "\x8E\xB8\x62\xA1\x75\x0F" },
            { ASTfunction::Log10,       "\x4A\x6C\xA3\x02\x8B\x80" },
            { ASTfunction::Sqrt,        "\x86\x7C\xFC\x20\xCB\x97" },
            { ASTfunction::Exp,         "\x88\xA8\x65\xF0\xC1\x06" },
            { ASTfunction::Abs,         "\x41\x89\x18\xD1\xAD\x82" },
            { ASTfunction::Floor,       "\xB7\x28\xD7\xD7\xA3\xCC" },
            { ASTfunction::Ceiling,     "\xF7\x96\x02\x7C\x27\xE4" },
            { ASTfunction::Infinity,    "\x2C\x28\x50\xCC\xDE\x44" },
            { ASTfunction::Factorial,   "\x19\xD7\x83\x29\x47\x99" },
            { ASTfunction::Sg,          "\xB7\x05\x28\xBA\xCD\x2E" },
            { ASTfunction::IsNatural,   "\x49\xD6\xF8\x5B\x45\x59" },
            { ASTfunction::BitNot,      "\x79\x19\x1A\x9F\x4D\xA0" },
            { ASTfunction::BitOr,       "\xF2\x77\xAB\x5C\x33\x43" },
            { ASTfunction::BitAnd,      "\xC3\x56\x9E\x75\xE0\x44" },
            { ASTfunction::BitXOR,      "\xBB\xFA\x2B\xD2\x91\x55" },
            { ASTfunction::BitLeft,     "\x91\x47\xE5\xE5\x0D\xAA" },
            { ASTfunction::BitRight,    "\xF1\xAB\x17\x00\xFA\xA5" },
            { ASTfunction::Atan2,       "\x99\x1B\xC9\xE0\x3F\xA4" },
            { ASTfunction::Divides,     "\x78\x8E\xC8\x2C\x1C\x96" },
            { ASTfunction::Div,         "\x64\xEC\x5B\x4B\xEE\x2B" },
            { ASTfunction::Dot,         "\x60\xAA\xB7\xE1\xB9\x06" },
            { ASTfunction::Cross,       "\x39\x38\x40\xE5\x93\xF8" },
            { ASTfunction::Hsb2Rgb,     "\xC3\xD4\x57\x04\xAF\x9F" },
            { ASTfunction::Rgb2Hsb,     "\xD0\x2A\x55\x7A\x53\x97" },
            { ASTfunction::Vec,         "\xE1\x75\x95\xC9\x80\xCF" },
            { ASTfunction::Mod,         "\x0F\xE3\xFE\x5F\xBF\xBF" },
            { ASTfunction::Min,         "\xA2\x42\xA3\x49\xB1\x19" },
            { ASTfunction::Max,         "\xD3\x55\x5C\x0D\xD8\x51" },
            { ASTfunction::Ftime,       "\x4F\xBE\xA1\x06\x80\x06" },
            { ASTfunction::Frame,       "\x90\x70\x6A\xBB\xBA\xB0" },
            { ASTfunction::Rand_Static, "\xC8\xF7\xE5\x3E\x05\xA3" },
            { ASTfunction::Rand,        "\xDA\x18\x5B\xE2\xDB\x79" },
            { ASTfunction::Rand2,       "\xDC\x8D\x09\x15\x8A\xC4" },
            { ASTfunction::RandExponential, "\x32\xDF\x4A\xFD\x00\x1F" },
            { ASTfunction::RandGamma,       "\xC9\xD5\x57\x4F\xE6\x77" },
            { ASTfunction::RandWeibull,     "\xE7\xCF\xA2\x01\xCD\x02" },
            { ASTfunction::RandExtremeValue,"\xE8\xCF\x86\x0B\xFD\x8E" },
            { ASTfunction::RandNormal,      "\xCF\xAC\xD4\x12\x09\xCC" },
            { ASTfunction::RandLogNormal,   "\x36\x65\x08\x5C\x49\xAA" },
            { ASTfunction::RandChiSquared,  "\x6D\x4B\x49\xA8\x83\xAD" },
            { ASTfunction::RandCauchy,      "\x22\x6C\x9E\x77\x79\x89" },
            { ASTfunction::RandFisherF,     "\x9B\x76\x1B\x51\xCD\xAE" },
            { ASTfunction::RandStudentT,    "\xF9\x41\x44\xF2\x63\xA7" },
            { ASTfunction::RandInt,         "\x48\x14\x4E\x27\x35\x2E" },
            { ASTfunction::RandBernoulli,   "\xBE\xD1\x55\x04\xD4\x54" },
            { ASTfunction::RandBinomial,    "\x6A\x69\x9A\x94\x36\x6C" },
            { ASTfunction::RandNegBinomial, "\xED\x31\x46\x9C\xA6\xAD" },
            { ASTfunction::RandPoisson,     "\x09\x89\xF3\x77\xAE\x67" },
            { ASTfunction::RandDiscrete,    "\x17\x69\x8D\x61\xFF\x2A" },
            { ASTfunction::RandGeometric,   "\xD5\x10\x2E\xA5\x03\xB4" }
        };
        
        if (arguments)
            arguments->entropy(ent);
        ent.append(EntropyMap.at(functype));
    }
    
    void
    ASTselect::entropy(std::string& e) const
    {
        e.append(ent);
    }
    
    void
    ASTruleSpecifier::entropy(std::string& ent) const
    {
        ent.append(entropyVal);
    }
    
    void
    ASTstartSpecifier::entropy(std::string& ent) const
    {
        ent.append(entropyVal);
        if (mModification)
            mModification->entropy(ent);
    }
    
    void
    ASTcons::entropy(std::string& ent) const
    {
        for (size_t i = 0; i < children.size(); ++i)
            children[i]->entropy(ent);
        ent.append("\xC5\x60\xA5\xC5\xC8\x74");
    }
    
    void
    ASTreal::entropy(std::string& ent) const
    {
        ent.append(text);
    }
    
    void
    ASTvariable::entropy(std::string& ent) const
    {
        ent.append(text);
    }
    
    void
    ASTuserFunction::entropy(std::string& ent) const
    {
        if (arguments)
            arguments->entropy(ent);
        if (definition)
            ent.append(definition->mName);
    }
    
    void
    ASToperator::entropy(std::string& ent) const
    {
        // These random strings are courtesy of http://www.fourmilab.ch/hotbits/
        static const std::map<char, const char*> EntropyMap = {
            { '*', "\x2E\x32\xD9\x2C\x41\xFE" },
            { '/', "\x6B\x15\x23\x41\x9E\xEB" },
            { '+', "\xD7\xB1\xB0\x39\x33\xC8" },
            { '-', "\x5D\xE7\xF0\x94\xC4\x13" },
            { '^', "\x02\x3C\x68\x36\xC5\xA0" },
            { 'N', "\x55\x89\x51\x46\xDB\x84" },
            { 'P', "\x8E\xAC\x29\x4B\x0E\xDC" },
            { '!', "\x19\x3A\x3E\x53\x14\xEA" },
            { '<', "\xBE\xDB\xC4\xA6\x4E\xAD" },
            { '>', "\xC7\xD9\x57\x32\xD6\x87" },
            { 'L', "\xE3\x56\x7E\x44\x57\x80" },
            { 'G', "\xB1\x2D\x2A\xCC\x2C\x40" },
            { '=', "\x78\x48\xC2\x95\xA9\xE2" },
            { 'n', "\x36\xCC\x01\x3B\x2F\xAD" },
            { '&', "\x28\x9B\xFB\x7F\xDB\x9C" },
            { '|', "\x2E\x40\x1B\x44\x15\x7C" },
            { 'X', "\xA7\x2B\x92\xFA\xFC\xF9" },
            { '_', "\x60\x2F\x10\xAD\x10\xFF" },
        };
        
        if (left)  left->entropy(ent);
        if (right) right->entropy(ent);
        ent.append(EntropyMap.at(op));
    }
    
    void
    ASTparen::entropy(std::string& ent) const
    {
        if (e) e->entropy(ent);
        ent.append("\xE8\xE9\xF6\x7E\x1A\xF1");
    }
    
    void
    ASTmodTerm::entropy(std::string& ent) const
    {
        // These random strings are courtesy of http://www.fourmilab.ch/hotbits/
        static const std::map<ASTmodTerm::modTypeEnum, const char*> EntropyMap = {
            {ASTmodTerm::unknownType,   ""},
            { ASTmodTerm::x,            "\x95\xE7\x48\x5E\xCC\x06" },
            { ASTmodTerm::y,            "\x84\x2B\xF3\xBB\x93\x59" },
            { ASTmodTerm::z,            "\xC8\x3A\x12\x32\x36\x71" },
            { ASTmodTerm::xyz,          "\x6C\x31\xCA\xBF\x8D\x89" },
            { ASTmodTerm::transform,    "\x88\x90\x54\xC5\xD3\x20" },
            { ASTmodTerm::size,         "\x64\xEC\x5B\x4B\xEE\x2B" },
            { ASTmodTerm::sizexyz,      "\xB0\x31\xD5\x1E\x7A\x5A" },
            { ASTmodTerm::rot,          "\x84\xB0\x92\x26\x59\xE2" },
            { ASTmodTerm::skew,         "\xFF\x2D\x84\x01\xA0\x0A" },
            { ASTmodTerm::flip,         "\x43\x5A\x17\xEA\x12\x05" },
            { ASTmodTerm::zsize,        "\x64\xEC\x5B\x4B\xEE\x2B" },
            { ASTmodTerm::hue,          "\x02\xDE\x2B\x2C\x25\xA1" },
            { ASTmodTerm::sat,          "\x18\x4F\xCF\x04\x3F\xE5" },
            { ASTmodTerm::bright,       "\x1F\x3F\xEB\xA2\xA2\x7E" },
            { ASTmodTerm::alpha,        "\xB4\xFF\x9E\x45\xEE\x7E" },
            { ASTmodTerm::hueTarg,      "\xAF\xE5\x58\x33\x20\xF8" },
            { ASTmodTerm::satTarg,      "\x98\x80\xED\x44\x2F\xF2" },
            { ASTmodTerm::brightTarg,   "\x68\xD6\xCB\x8A\x96\x20" },
            { ASTmodTerm::alphaTarg,    "\x24\x4C\xCC\x41\x09\xC7" },
            { ASTmodTerm::targHue,      "\xDB\x3F\xA1\xDA\xE7\x45" },
            { ASTmodTerm::targSat,      "\xDA\x75\x13\xD3\x30\xEA" },
            { ASTmodTerm::targBright,   "\x8F\x01\x2B\x75\xC3\x25" },
            { ASTmodTerm::targAlpha,    "\xE7\xCD\x5E\xE3\x88\xF4" },
            { ASTmodTerm::time,         "\x20\xC6\xE8\x02\xED\x27" },
            { ASTmodTerm::timescale,    "\x78\x8E\xC8\x2C\x1C\x96" },
            { ASTmodTerm::stroke,       "" },
            { ASTmodTerm::param,        "" },
            { ASTmodTerm::x1,           "" },
            { ASTmodTerm::y1,           "" },
            { ASTmodTerm::x2,           "" },
            { ASTmodTerm::y2,           "" },
            { ASTmodTerm::xrad,         "" },
            { ASTmodTerm::yrad,         "" },
            { ASTmodTerm::modification, "\x88\x90\x54\xC5\xD3\x20" },
        };
        
        if (args) args->entropy(ent);
        ent.append(EntropyMap.at(modType));
    }
    
    void
    ASTarray::entropy(std::string& e) const
    {
        e.append(entString);
    }
    
    static ASTexpression*
    MakeResult(const double* result, int length, const ASTexpression* from)
    {
        ASTreal* r = new ASTreal(result[0], from->where);
        r->mType = from->mType;
        r->isNatural = from->isNatural;
        
        if (length > 1) {
            ASTcons* l = new ASTcons{r};
            for (int i = 1; i < length; ++i) {
                r = new ASTreal(result[i], from->where);
                r->mType = from->mType;
                r->isNatural = from->isNatural;
                l->append(r);
            }
            return l;
        }
        
        return r;
    }
    
    ASTexpression*
    ASTfunction::simplify()
    {
        Simplify(arguments);
        
        if (isConstant) {
            double result[AST::MaxVectorSize];
            int len = evaluate(result, AST::MaxVectorSize);
            if (len < 0) {
                return this;
            }
            
            ASTexpression* r = MakeResult(result, len, this);
            delete this;
            return r;
        }
        
        return this;
    }
    
    ASTexpression*
    ASTselect::simplify()
    {
        if (indexCache == NotCached) {
            for (auto& arg: arguments)
                Simplify(arg);
            Simplify(selector);
            return this;
        }
        
        ASTexpression* chosenOne = arguments[indexCache].release();
        
        delete this;
        return chosenOne->simplify();
    }
    
    ASTexpression*
    ASTruleSpecifier::simplify()
    {
        if (arguments) {
            if (ASTcons* carg = dynamic_cast<ASTcons*>(arguments.get())) {
                for (size_t i = 0; i < carg->children.size(); ++i)
                    Simplify(carg->children[i]);
            } else {
                Simplify(arguments);
            }
        }
        if (argSource == StackArgs) {
            bool isGlobal;
            const ASTparameter* bound = Builder::CurrentBuilder->findExpression(shapeType, isGlobal);
            assert(bound);
            if (bound->mType != RuleType)
                return this;
            if (bound->mStackIndex == -1) {
                assert(bound->mDefinition);
                if (ASTruleSpecifier* r = dynamic_cast<ASTruleSpecifier*>(bound->mDefinition->mExpression.get())) {
                    // The source ASTruleSpec must already be type-checked
                    // because it is lexically earlier
                    shapeType = r->shapeType;
                    argSize = r->argSize;
                    argSource = r->argSource;
                    arguments.reset();
                    assert(!r->arguments || r->arguments->isConstant);
                    simpleRule = r->simpleRule;
                    typeSignature = r->typeSignature;
                    parentSignature = r->parentSignature;
                    isConstant = true;
                    mLocality = PureLocal;
                    assert(argSource != DynamicArgs && argSource != ShapeArgs);
                } else {
                    CfdgError::Error(where, "Error processing shape variable.");
                }
            }
        }
        return this;
    }
    
    ASTexpression*
    ASTstartSpecifier::simplify()
    {
        ASTruleSpecifier::simplify();
        if (mModification) {
            ASTexpression* m = mModification->simplify();
            assert(m == mModification.get());
        }
        return this;
    }
    
    ASTexpression*
    ASTcons::simplify()
    {
        if (children.size() == 1) {
            ASTexpression* ret = children[0].release()->simplify();
            delete this;
            return ret;
        }
        for (size_t i = 0; i < children.size(); ++i)
            Simplify(children[i]);
        return this;
    }
    
    ASTexpression*
    ASTuserFunction::simplify()
    {
        if (arguments) {
            if (ASTcons* carg = dynamic_cast<ASTcons*>(arguments.get())) {
                // Can't use ASTcons::simplify() because it will collapse the
                // ASTcons if it only has one child and that will break the
                // function arguments.
                for (size_t i = 0; i < carg->children.size(); ++i)
                    Simplify(carg->children[i]);
            } else {
                Simplify(arguments);
            }
        }
        return this;
    }
    
    ASTexpression*
    ASTlet::simplify()
    {
        assert(definition);
        definition->compile(CompilePhase::Simplify);
        if (isConstant) {
            std::string ent;
            entropy(ent);
            ASTparameter p(-1, definition, where);
            p.mDefinition = definition;     // ctor won't do this
            ASTexpression* ret = p.constCopy(where, ent);
            if (ret) {
                delete this;
                return ret;
            }
        } else if (!arguments) {
            ASTexpression* ret = definition->mExpression.release();
            delete this;
            return ret;
        }
        return ASTuserFunction::simplify();
    }
    
    ASTexpression*
    ASToperator::simplify()
    {
        Simplify(left);
        Simplify(right);
        
        if (isConstant && (mType == NumericType || mType == FlagType)) {
            double result[AST::MaxVectorSize];
            if (evaluate(result, tupleSize) != tupleSize) {
                return this;
            }
            
            ASTexpression* r = MakeResult(result, tupleSize, this);
            delete this;
            return r;
        }
        
        return this;
    }
    
    ASTexpression*
    ASTparen::simplify()
    {
        ASTexpression* e2 = e.release()->simplify();
        
        delete this;
        return e2;
    }
    
    ASTexpression*
    ASTmodTerm::simplify()
    {
        Simplify(args);
        return this;
    }
    
    ASTexpression*
    ASTmodification::simplify()
    {
        evalConst();
        return this;
    }
    
    ASTexpression*
    ASTarray::simplify()
    {
        if (!mData || !isConstant || mLength > 1) {
            Simplify(mArgs);
            return this;
        }
        
        double i;
        if (mArgs->evaluate(&i, 1) != 1) {
            CfdgError::Error(mArgs->where, "Cannot evaluate array index");
            return this;
        }
        int index = static_cast<int>(i);
        if (index >= mCount || index < 0) {
            CfdgError::Error(where, "Array index exceeds bounds");
            return this;
        }
        
        ASTreal* top = new ASTreal(mData[index], where);
        top->text = entString;                // use variable name for entropy
        top->isNatural = isNatural;
        delete this;
        return top;
    }

    ASTexpression*
    ASTfunction::compile(AST::CompilePhase ph)
    {
        Compile(arguments, ph);
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                yy::location argsLoc = where;
                isConstant = true;
                mLocality = PureLocal;
                int argcount = 0;
                size_t argnum = 0;
                if (arguments) {
                    argnum = arguments->size();
                    argsLoc = arguments->where;
                    isConstant = arguments->isConstant;
                    mLocality = arguments->mLocality;
                    if (mLocality == PureNonlocal)
                        mLocality = ImpureNonlocal;
                    if (arguments->mType == NumericType)
                        argcount = arguments->evaluate(nullptr, 0);
                    else
                        CfdgError::Error(argsLoc, "function arguments must be numeric");
                }
                
                switch (functype) {
                    case Abs:
                        if (argcount < 1 || argcount > 2)
                            CfdgError::Error(argsLoc, "function takes one or two arguments");
                        break;
                    case Infinity:
                        if (argcount == 0) {
                            arguments.reset(new ASTreal(1.0, argsLoc));
                            argcount = 1;
                        }   // fall through
                    case Cos:
                    case Sin:
                    case Tan:
                    case Cot:
                    case Acos:
                    case Asin:
                    case Atan:
                    case Acot:
                    case Cosh:
                    case Sinh:
                    case Tanh:
                    case Acosh:
                    case Asinh:
                    case Atanh:
                    case Log:
                    case Log10:
                    case Sqrt:
                    case Exp:
                    case Floor:
                    case Ceiling:
                    case BitNot:
                    case Factorial:
                    case Sg:
                    case IsNatural:
                        if (argcount != 1)
                            CfdgError::Error(argsLoc, "Function takes one argument");
                        break;
                    case BitOr:
                    case BitAnd:
                    case BitXOR:
                    case BitLeft:
                    case BitRight:
                    case Atan2:
                    case Mod:
                    case Divides:
                    case Div:
                        if (argcount != 2)
                            CfdgError::Error(argsLoc, "Function takes two arguments");
                        break;
                    case Dot:
                    case Cross:
                        if (argnum != 2) {
                            CfdgError::Error(argsLoc, "Dot/cross product takes two vectors");
                        } else {
                            int l = arguments->getChild(0)->evaluate(nullptr, 0);
                            int r = arguments->getChild(1)->evaluate(nullptr, 0);
                            if (functype == Dot && (l != r || l < 2))
                                CfdgError::Error(argsLoc, "Dot product takes two vectors of the same length");
                            if (functype == Cross && (l != 3 || r != 3))
                                CfdgError::Error(argsLoc, "Cross product takes two vector3s");
                        }
                        break;
                    case Hsb2Rgb:
                    case Rgb2Hsb:
                        if (argcount != 3)
                            CfdgError::Error(argsLoc, "RGB/HSB conversion function takes 3 arguments");
                        break;
                    case Vec:
                        if (argnum != 2) {
                            CfdgError::Error(argsLoc, "vec() function takes two arguments");
                        } else if (!arguments->getChild(1)->isConstant ||
                                   !arguments->getChild(1)->isNatural ||
                                    arguments->getChild(1)->evaluate(&random, 1) != 1)
                        {
                            CfdgError::Error(arguments->getChild(1)->where, "vec() function length argument must be a scalar constant");
                        } else if (static_cast<int>(floor(random)) < 2 ||
                                   static_cast<int>(floor(random)) > AST::MaxVectorSize)
                        {
                            CfdgError::Error(arguments->getChild(1)->where, "vec() function length argument must be >= 2 and <= 99");
                        }
                        break;
                    case Ftime:
                    case Frame:
                        if (arguments)
                            CfdgError::Error(argsLoc, "ftime()/frame() functions takes no arguments");
                        isConstant = false;
                        arguments.reset(new ASTreal(1.0, argsLoc));
                        break;
                    case Rand:
                    case Rand2:
                    case RandInt:
                        isConstant = false;
                    case Rand_Static:
                        switch (argcount) {
                            case 0:
                                arguments.reset(new ASTcons{ new ASTreal(0.0, argsLoc),
                                                             new ASTreal(functype == RandInt ? 2.0 : 1.0, argsLoc) });
                                break;
                            case 1:
                                arguments.reset(new ASTcons{ new ASTreal(0.0, argsLoc), arguments.release() });
                                break;
                            case 2:
                                break;
                            default:
                                CfdgError::Error(argsLoc, "Illegal argument(s) for random function");
                                break;
                        }
                        if (!isConstant && functype == Rand_Static) {
                            CfdgError::Error(argsLoc, "Argument(s) for rand_static() must be constant");
                        }
                        break;
                    case RandDiscrete:
                        isConstant = false;
                        isNatural = RendererAST::isNatural(nullptr, static_cast<double>(argcount));
                        if (argcount < 1)
                            CfdgError::Error(argsLoc, "Function takes at least one arguments");
                        break;
                    case RandBernoulli:
                    case RandGeometric:
                    case RandPoisson:
                    case RandExponential:
                    case RandChiSquared:
                    case RandStudentT:
                        isConstant = false;
                        if (argcount != 1)
                            CfdgError::Error(argsLoc, "Function takes one argument");
                        break;
                    case RandBinomial:
                    case RandNegBinomial:
                        isNatural = arguments &&  arguments->size() == 2 &&
                                    arguments->getChild(0)->isNatural;
                    case RandCauchy:
                    case RandExtremeValue:
                    case RandFisherF:
                    case RandGamma:
                    case RandLogNormal:
                    case RandNormal:
                    case RandWeibull:
                        isConstant = false;
                        if (argcount != 2)
                            CfdgError::Error(argsLoc, "Function takes two arguments");
                        break;
                    case Min:
                    case Max:
                        if (argcount < 2)
                            CfdgError::Error(argsLoc, "Function takes at least two arguments");
                        break;
                    case NotAFunction:
                        CfdgError::Error(where, "Unknown function");
                        break;
                }
                
                static FuncType mightBeNatural[] =
                {
                    Mod, Abs, Min, Max, BitNot, BitOr, BitAnd, BitXOR, BitLeft,
                    BitRight, RandInt
                };
                
                if (std::find(std::begin(mightBeNatural), std::end(mightBeNatural), functype) != std::end(mightBeNatural)) {
                    isNatural = !arguments || arguments->isNatural;
                }
                
                static FuncType mustBeNatural[] = {Factorial, Sg, IsNatural, Div, Divides};
                
                if (std::find(std::begin(mustBeNatural), std::end(mustBeNatural), functype) != std::end(mustBeNatural)) {
                    if (arguments && !arguments->isNatural && !ASTparameter::Impure)
                        CfdgError::Error(arguments->where, "function is defined over natural numbers only");
                    isNatural = true;
                }

                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return nullptr;
    }
    
    ASTexpression*
    ASTselect::compile(AST::CompilePhase ph)
    {
        if (!selector)
            return nullptr;
        for (auto& arg: arguments)
            Compile(arg, ph);
        Compile(selector, ph);
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                selector->entropy(ent);
                ent.append("\xB5\xA2\x4A\x74\xA9\xDF");
                mLocality = selector->mLocality;

                // Move arguments to their vector
                arguments = Extract(std::move(selector));
                selector = std::move(arguments[0]);
                arguments.erase(arguments.begin());
                
                if (selector->mType != NumericType || selector->evaluate(nullptr, 0) != 1) {
                    CfdgError::Error(selector->where, "if()/select() selector must be a numeric scalar");
                    return nullptr;
                }
                if (arguments.size() < 2) {
                    CfdgError::Error(selector->where, "if()/select() selector must have at least two arguments");
                    return nullptr;
                }
                
                mType = arguments[0]->mType;
                isNatural = arguments[0]->isNatural;
                tupleSize = (mType == NumericType) ? arguments[0]->evaluate(nullptr, 0) : 1;
                for (size_t i = 1; i < arguments.size(); ++i) {
                    if (mType != arguments[i]->mType) {
                        CfdgError::Error(arguments[i]->where, "select()/if() choices must be of same type");
                    } else if (mType == NumericType && tupleSize != -1 &&
                               arguments[i]->evaluate(nullptr, 0) != tupleSize)
                    {
                        CfdgError::Error(arguments[i]->where, "select()/if() choices must be of same length");
                        tupleSize = -1;
                    }
                    isNatural = isNatural && arguments[i]->isNatural;
                }
                
                if (ifSelect && arguments.size() != 2) {
                    CfdgError::Error(where, "if() function requires two arguments");
                }
                
                if (selector->isConstant) {
                    indexCache = getIndex();
                    isConstant = arguments[indexCache]->isConstant;
                    mLocality = arguments[indexCache]->mLocality;
                    isNatural = arguments[indexCache]->isNatural;
                }
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return nullptr;
    }
    
    ASTexpression*
    ASTruleSpecifier::compile(AST::CompilePhase ph)
    {
        Compile(arguments, ph);
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                switch (argSource) {
                    case ShapeArgs:
                        assert(arguments);
                        if (arguments->mType != AST::RuleType)
                            CfdgError::Error(arguments->where, "Expression does not return a shape");
                        isConstant = false;
                        mLocality = arguments->mLocality;
                        arguments->entropy(entropyVal);
                        return nullptr;
                    case SimpleParentArgs:
                        assert(typeSignature == parentSignature);
                        assert(arguments && arguments->mType == ReuseType);
                        isConstant = true;
                        mLocality = PureLocal;
                        return nullptr;
                    case StackArgs: {
                        bool isGlobal;
                        const ASTparameter* bound = Builder::CurrentBuilder->findExpression(shapeType, isGlobal);
                        assert(bound);
                        if (bound->mType != RuleType) {
                            CfdgError::Error(where, "Shape name does not bind to a rule variable");
                            CfdgError::Error(bound->mLocation, "   this is what it binds to");
                        }
                        if (bound->mStackIndex == -1) {
                            if (!bound->mDefinition || !bound->mDefinition->mExpression) {
                                CfdgError::Error(where, "Error processing shape variable.");
                                return nullptr;
                            }
                            const ASTruleSpecifier* r = dynamic_cast<const ASTruleSpecifier*>(bound->mDefinition->mExpression.get());
                            if (r == nullptr) {
                                CfdgError::Error(where, "Error processing shape variable.");
                                return nullptr;
                            }
                            grab(r);
                            mLocality = PureLocal;
                        } else {
                            mStackIndex = bound->mStackIndex -
                                (isGlobal ? 0 : Builder::CurrentBuilder->mLocalStackDepth);
                            isConstant = false;
                            mLocality = bound->mLocality;
                        }
                        if (arguments && arguments->mType != AST::NoType)
                            CfdgError::Error(arguments->where, "Cannot bind parameters twice");
                        return nullptr;
                    }
                    case NoArgs:
                        assert(!arguments || arguments->mType == NoType);
                        isConstant = true;
                        mLocality = PureLocal;
                        break;
                    case ParentArgs:
                    case SimpleArgs:
                        assert(false);
                        break;
                    case DynamicArgs: {
                        ASTdefine* func = nullptr;
                        std::string name = Builder::CurrentBuilder->GetTypeInfo(shapeType, func, typeSignature);
                        if (typeSignature && typeSignature->empty())
                            typeSignature = nullptr;
                        
                        if (func) {
                            if (func->mType == RuleType) {
                                argSource = ShapeArgs;
                                arguments.reset(new ASTuserFunction(shapeType, arguments.release(), func, where));
                                Compile(arguments, ph);
                                isConstant = false;
                                mLocality = arguments->mLocality;
                            } else {
                                CfdgError::Error(arguments->where, "Function does not return a shape");
                            }
                            
                            if (arguments)
                                arguments->entropy(entropyVal);
                            
                            return nullptr;
                        }
                        
                        bool isGlobal;
                        const ASTparameter* bound = Builder::CurrentBuilder->findExpression(shapeType, isGlobal);
                        if (bound && bound->mType == RuleType) {
                            // Shape was a stack variable but the variable type
                            // was not known to be a ruleSpec until now. Convert
                            // to a StackArgs and recompile as such.
                            argSource = StackArgs;
                            compile(ph);    // always return nullptr
                            return nullptr;
                        }
                        
                        if (arguments && arguments->mType == AST::ReuseType) {
                            argSource = ParentArgs;
                            if (!typeSignature) {
                                CfdgError::Error(where, "Parameter reuse only allowed when shape has parameters to reuse.");
                            } else if (typeSignature != parentSignature) {
                                ASTparameters::const_iterator param_it = typeSignature->begin();
                                ASTparameters::const_iterator parent_it = parentSignature->begin();
                                while (param_it != typeSignature->end() && parent_it != parentSignature->end()) {
                                    if (*param_it != *parent_it) {
                                        CfdgError::Error(where, "Parameter reuse only allowed when type signature is identical.");
                                        CfdgError::Error(param_it->mLocation, "    target shape parameter type");
                                        CfdgError::Error(parent_it->mLocation, "    does not equal source shape parameter type");
                                        break;
                                    }
                                    ++param_it;
                                    ++parent_it;
                                }
                                if (param_it == typeSignature->end() && parent_it != parentSignature->end()) {
                                    CfdgError::Error(where, "Source shape has more parameters than target shape.");
                                    CfdgError::Error(parent_it->mLocation, "    extra source parameters start here");
                                }
                                if (param_it != typeSignature->end() && parent_it == parentSignature->end()) {
                                    CfdgError::Error(where, "Target shape has more parameters than source shape.");
                                    CfdgError::Error(param_it->mLocation, "    extra target parameters start here");
                                }
                            }
                            isConstant = true;
                            mLocality = PureNonlocal;
                            return nullptr;
                        }
                        
                        argSize = ASTparameter::CheckType(typeSignature, arguments.get(), where, true);
                        if (argSize < 0) {
                            argSource = NoArgs;
                            return nullptr;
                        }
                        
                        if (arguments && arguments->mType != AST::NoType) {
                            if (arguments->isConstant) {
                                simpleRule = evalArgs();
                                argSource = SimpleArgs;
                                Builder::CurrentBuilder->storeParams(simpleRule.get());
                                isConstant = true;
                                mLocality = PureLocal;
                            } else {
                                isConstant = false;
                                mLocality = arguments->mLocality;
                            }
                            arguments->entropy(entropyVal);
                        } else {
                            argSource = NoArgs;
                            simpleRule = StackRule::alloc(shapeType, 0, typeSignature);
                            isConstant = true;
                            mLocality = PureLocal;
                            Builder::CurrentBuilder->storeParams(simpleRule.get());
                        }
                        break;
                    }
                }
                break;
            }
            case CompilePhase::Simplify: {
                break;
            }
        }
        return nullptr;
    }
    
    ASTexpression*
    ASTstartSpecifier::compile(AST::CompilePhase ph)
    {
        std::string name(entropyVal);
        ASTruleSpecifier::compile(ph);      // always return nullptr
        entropyVal = std::move(name);       // StartShape only uses name for entropy (grrr)
        if (mModification) {
            mModification->compile(ph);     // always returns nullptr
        }
        return nullptr;
    }
    
    ASTexpression*
    ASTcons::compile(AST::CompilePhase ph)
    {
        switch (ph) {
            case CompilePhase::TypeCheck: {
                isConstant = isNatural = true;
                mLocality = PureLocal;
                mType = NoType;
                for (auto& child : children) {
                    Compile(child, ph);
                    isConstant = isConstant && child->isConstant;
                    isNatural = isNatural && child->isNatural;
                    mLocality = CombineLocality(mLocality, child->mLocality);
                    mType = static_cast<expType>(mType | child->mType);
                }
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return nullptr;
    }
    
    ASTexpression*
    ASTvariable::compile(AST::CompilePhase ph)
    {
        switch (ph) {
            case CompilePhase::TypeCheck: {
                bool isGlobal = false;
                const ASTparameter* bound = Builder::CurrentBuilder->findExpression(stringIndex, isGlobal);
                if (bound == nullptr) {
                    CfdgError::Error(where, "internal error.");
                    return nullptr;
                }
                
                std::string name = Builder::CurrentBuilder->ShapeToString(stringIndex);

                if (bound->mStackIndex == -1) {
                    assert(bound->mDefinition);
                    ASTexpression* ret = bound->constCopy(where, name);
                    if (!ret)
                        CfdgError::Error(where, "internal error.");
                    return ret;
                } else {
                    if (bound->mType == AST::RuleType) {
                        ASTruleSpecifier* ret = new ASTruleSpecifier(stringIndex, name, where);
                        ret->compile(ph);       // always return nullptr
                        return ret;
                    }
                    
                    count = bound->mType == AST::NumericType ? bound->mTuplesize : 1;
                    stackIndex = bound->mStackIndex - (isGlobal ? 0 : Builder::CurrentBuilder->mLocalStackDepth);
                    mType = bound->mType;
                    isNatural = bound->isNatural;
                    mLocality = bound->mLocality;
                    isParameter = bound->isParameter;
                }
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return nullptr;
    }
    
    ASTexpression*
    ASTuserFunction::compile(AST::CompilePhase ph)
    {
        switch (ph) {
            case CompilePhase::TypeCheck: {
                // Function calls and shape specifications are ambiguous at parse
                // time so the parser always chooses a function call. During
                // type check we may need to convert to a shape spec.
                ASTdefine* def = nullptr;
                const ASTparameters* p = nullptr;
                std::string name = Builder::CurrentBuilder->GetTypeInfo(nameIndex, def, p);
                
                if (def && p) {
                    CfdgError::Error(where, "Name matches both a function and a shape");
                    return nullptr;
                }
                if (!def && !p) {
                    CfdgError::Error(where, "Name does not match shape name or function name");
                    return nullptr;
                }
                
                if (def) {  // && !p
                    Compile(arguments, ph);
                    
                    definition = def;
                    ASTparameter::CheckType(&(def->mParameters), arguments.get(), where, false);
                    isConstant = false;
                    isNatural = def->isNatural;
                    mType = def->mType;
                    mLocality = arguments ? arguments->mLocality : PureLocal;
                    if (def->mExpression && def->mExpression->mLocality == ImpureNonlocal &&
                        mLocality == PureNonlocal)
                    {
                        mLocality = ImpureNonlocal;
                    }
                    return nullptr;
                }
                
                // if (!def && p)
                ASTruleSpecifier* r = new ASTruleSpecifier(nameIndex, name,
                                                           std::move(arguments),
                                                           where, nullptr);
                r->compile(CompilePhase::TypeCheck);    // always returns nullptr
                return r;
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return nullptr;
    }
    
    ASTexpression*
    ASTlet::compile(AST::CompilePhase ph)
    {
        switch (ph) {
            case CompilePhase::TypeCheck: {
                mDefinitions->compile(ph, nullptr, definition);
                
                // transfer non-const definitions to arguments
                ASTexpression* args = nullptr;
                for (auto& rep: mDefinitions->mBody) {
                    if (ASTdefine* def = dynamic_cast<ASTdefine*>(rep.get()))
                        if (def->mDefineType == ASTdefine::StackDefine) {
                            definition->mStackCount += def->mTuplesize;
                            args = ASTexpression::Append(args, def->mExpression.release());
                        }
                }
                mDefinitions->mParameters.pop_back();       // remove the definition parameter
                for (auto& param: mDefinitions->mParameters) {
                    if (!param.mDefinition)
                        definition->mParameters.push_back(param);
                }
                mDefinitions.reset();   // we're done with these
                arguments.reset(args);
                
                isConstant = !arguments && definition->mExpression->isConstant;
                isNatural = definition->isNatural;
                mLocality = definition->mExpression ?
                    definition->mExpression->mLocality :
                    definition->mChildChange.mLocality;
                mType = definition->mType;
                
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return nullptr;
    }
    
    ASTexpression*
    ASToperator::compile(AST::CompilePhase ph)
    {
        Compile(left, ph);
        Compile(right, ph);
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                isConstant = left->isConstant && (!right || right->isConstant);
                mLocality = right ? CombineLocality(left->mLocality, right->mLocality) : left->mLocality;
                if (mLocality == PureNonlocal)
                    mLocality = ImpureNonlocal;
                mType = right ? static_cast<expType>(left->mType | right->mType) : left->mType;
                if (mType == NumericType) {
                    int ls = left ? left->evaluate(nullptr, 0) : 0;
                    int rs = right ? right->evaluate(nullptr, 0) : 0;
                    switch (op) {
                        case 'N':
                        case 'P':
                            tupleSize = ls;
                            if (rs != 0)
                                CfdgError::Error(where, "Unitary operators must have only one operand");
                            break;
                        case '!':
                            if (rs != 0 || ls != 1)
                                CfdgError::Error(where, "Unitary operators must have only one scalar operand");
                            break;
                        case '+':
                        case '-':
                        case '_':
                        case '/':
                        case '*':
                            tupleSize = ls;
                        case '=':
                        case 'n':
                            if (ls != rs)
                                CfdgError::Error(where, "Operands must have the same length");
                            if (ls < 1 || rs < 1)
                                CfdgError::Error(where, "Binary operators must have two operands");
                            break;
                        default:
                            if (ls != 1 || rs != 1)
                                CfdgError::Error(where, "Binary operators must have two scalar operands");
                            break;
                    }
                }
                if (strchr("+_*<>LG=n&|X^!", op))
                    isNatural = left->isNatural && (!right || right->isNatural);
                
                if (op == '+') {
                    if (mType != FlagType && mType != NumericType)
                        CfdgError::Error(where, "Operands must be numeric or flags");
                } else {
                    if (mType != NumericType)
                        CfdgError::Error(where, "Operand(s) must be numeric");
                }
                if (op == '_' && !isNatural &&!ASTparameter::Impure)
                    CfdgError::Error(where, "Proper subtraction operands must be natural");
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return nullptr;
    }
    
    ASTexpression*
    ASTparen::compile(AST::CompilePhase ph)
    {
        if (!e) return nullptr;
        Compile(e, ph);
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                isConstant = e->isConstant;
                isNatural = e->isNatural;
                mLocality = e->mLocality;
                mType = e->mType;
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return nullptr;
    }
    
    ASTexpression*
    ASTmodTerm::compile(AST::CompilePhase ph)
    {
        Compile(args, ph);
        if (!args) {
            if (modType != param)
                CfdgError::Error(where, "Illegal expression in shape adjustment");
            return nullptr;
        }
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                isConstant = args->isConstant;
                mLocality = args->mLocality;
                switch (args->mType) {
                    case NumericType: {
                        argCount = args->evaluate(nullptr, 0);
                        int minCount = 1;
                        int maxCount = 1;
                        
                        if (argCount == 3 && modType == ASTmodTerm::x)
                            modType = ASTmodTerm::xyz;
                        if (argCount == 3 && modType == ASTmodTerm::size)
                            modType = ASTmodTerm::sizexyz;
                        
                        switch (modType) {
                            case ASTmodTerm::hue:
                                maxCount = 4;
                                break;
                            case ASTmodTerm::x:
                            case ASTmodTerm::size:
                            case ASTmodTerm::sat:
                            case ASTmodTerm::bright:
                            case ASTmodTerm::alpha:
                                maxCount = 2;
                                break;
                            case ASTmodTerm::y:
                            case ASTmodTerm::z:
                            case ASTmodTerm::timescale:
                            case ASTmodTerm::zsize:
                            case ASTmodTerm::rot:
                            case ASTmodTerm::flip:
                            case ASTmodTerm::hueTarg:
                            case ASTmodTerm::satTarg:
                            case ASTmodTerm::brightTarg:
                            case ASTmodTerm::alphaTarg:
                            case ASTmodTerm::targHue:
                            case ASTmodTerm::targSat:
                            case ASTmodTerm::targBright:
                            case ASTmodTerm::targAlpha:
                            case ASTmodTerm::stroke:
                                break;
                            case ASTmodTerm::xyz:
                            case ASTmodTerm::sizexyz:
                                minCount = maxCount = 3;
                                break;
                            case ASTmodTerm::time:
                            case ASTmodTerm::skew:
                                minCount = maxCount = 2;
                                break;
                            case ASTmodTerm::transform:
                                maxCount = 6;
                                if (argCount != 1 && argCount != 2 && argCount != 4 && argCount != 6)
                                    CfdgError::Error(where, "transform adjustment takes 1, 2, 4, or 6 parameters");
                                break;
                            case ASTmodTerm::param:
                                minCount = maxCount = 0;
                                break;
                            case ASTmodTerm::modification:
                            default:
                                break;
                        }
                        
                        if (argCount < minCount)
                            CfdgError::Error(where, "Not enough adjustment parameters");
                        if (argCount > maxCount)
                            CfdgError::Error(where, "Too many adjustment parameters");
                        break;
                    }
                    case ModType:
                        if (modType != ASTmodTerm::transform)
                            CfdgError::Error(args->where, "Cannot accept a transform expression here");
                        else
                            modType = ASTmodTerm::modification;
                        break;
                    default:
                        CfdgError::Error(args->where, "Illegal expression in shape adjustment");
                        break;
                }
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return nullptr;
    }
    
    ASTexpression*
    ASTmodification::compile(AST::CompilePhase ph)
    {
        for (auto& term: modExp)
            term->compile(ph);          // ASTterm always return this
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                ASTtermArray temp;
                temp.swap(modExp);
                for (auto term = temp.begin(); term != temp.end(); ++term) {
                    if (!(*term)->args || (*term)->args->mType != NumericType) {
                        modExp.emplace_back(std::move(*term));
                        continue;
                    }
                    int argcount = (*term)->args->evaluate(nullptr, 0);
                    switch ((*term)->modType) {
                            // Try to merge consecutive x and y adjustments
                        case ASTmodTerm::x:
                        case ASTmodTerm::y: {
                            auto next = term + 1;
                            if (next == temp.end())
                                break;
                            if ((*term)->modType == ASTmodTerm::x &&
                                (*next)->modType == ASTmodTerm::y &&
                                argcount == 1)
                            {
                                (*term)->args.reset((*term)->args.release()->append((*next)->args.release()));
                                (*term)->argCount = 2;
                                modExp.emplace_back(std::move(*term));
                                term = next;
                                continue;
                            }               // next stays in temp
                            /* if ((*term)->modType == ASTmodTerm::y &&
                                (*next)->modType == ASTmodTerm::x &&
                                (*next)->args->evaluate(nullptr, 0) == 1)
                            {
                                (*next)->args.reset((*next)->args.release()->append((*term)->args.release()));
                                (*term)->argCount = 2;
                                modExp.emplace_back(std::move(*next));
                                term = next;
                                continue;   // term stays in temp
                            } Don't merge y & x because 3.0.5 didn't and it changes variations */
                            break;
                        }
                            // Try to split the XYZ term into an XY term and a Z term. Drop the XY term
                            // if it is the identity. First try an all-constant route, then try to tease
                            // apart the arguments.
                        case ASTmodTerm::xyz:
                        case ASTmodTerm::sizexyz: {
                            double d[3];
                            if ((*term)->args->isConstant && (*term)->args->evaluate(d, 3) == 3) {
                                (*term)->args.reset(new ASTcons{ new ASTreal(d[0], (*term)->where), new ASTreal(d[1], (*term)->where) });
                                (*term)->modType = (*term)->modType == ASTmodTerm::xyz ?
                                    ASTmodTerm::x : ASTmodTerm::size;
                                (*term)->argCount = 2;
                                
                                ASTmodTerm::modTypeEnum ztype = (*term)->modType == ASTmodTerm::size ?
                                    ASTmodTerm::zsize : ASTmodTerm::z;
                                ASTmodTerm* zmod = new ASTmodTerm(ztype, new ASTreal(d[2], (*term)->where), (*term)->where);
                                zmod->argCount = 1;
                                
                                // Check if xy part is the identity transform and only save it if it is not
                                if (d[0] == 1.0 && d[1] == 1.0 && (*term)->modType == ASTmodTerm::size)
                                {
                                    // Drop xy term and just save z term if xy term
                                    // is the identity transform
                                    (*term).reset(zmod);
                                } else {
                                    modExp.emplace_back(zmod);
                                }
                                modExp.emplace_back(std::move(*term));
                                continue;
                            }
                            
                            ASTexpArray xyzargs = Extract(std::move((*term)->args));
                            ASTexpression* xyargs = nullptr;
                            ASTexpression* zargs = nullptr;
                            for (exp_ptr& arg: xyzargs) {
                                if (!xyargs || xyargs->evaluate(nullptr, 0) < 2) {
                                    xyargs = Append(xyargs, arg.release());
                                } else {
                                    zargs = Append(zargs, arg.release());
                                }
                            }
                            if (xyargs && zargs && xyargs->evaluate(nullptr, 0) == 2) {
                                // We have successfully split the 3-tuple into a 2-tuple and a scalar
                                (*term)->args.reset(xyargs);
                                (*term)->modType = (*term)->modType == ASTmodTerm::xyz ?
                                    ASTmodTerm::x : ASTmodTerm::size;
                                (*term)->argCount = 2;
                                
                                ASTmodTerm::modTypeEnum ztype = (*term)->modType == ASTmodTerm::size ?
                                    ASTmodTerm::zsize : ASTmodTerm::z;
                                ASTmodTerm* zmod = new ASTmodTerm(ztype, zargs, (*term)->where);
                                zmod->argCount = 1;
                                
                                if ((*term)->modType == ASTmodTerm::size && xyargs->isConstant &&
                                    xyargs->evaluate(d, 2) == 2 && d[0] == 1.0 && d[1] == 1.0)
                                {
                                    // Drop xy term and just save z term if xy term
                                    // is the identity transform
                                    (*term).reset(zmod);
                                } else {
                                    modExp.emplace_back(zmod);
                                }
                            } else {    // No dice, put it all back
                                xyargs = Append(xyargs, zargs);
                                (*term)->args.reset(xyargs);
                            }
                            modExp.emplace_back(std::move(*term));
                            continue;
                        }
                        default:
                            break;
                    }
                    modExp.emplace_back(std::move(*term));
                }

                isConstant = true;
                mLocality = PureLocal;
                for (auto& term : modExp) {
                    isConstant = isConstant && term->isConstant;
                    mLocality = CombineLocality(mLocality, term->mLocality);
                    std::string ent;
                    term->entropy(ent);
                    addEntropy(ent);
                }
                if (canonical)
                    makeCanonical();
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return nullptr;
    }
    
    ASTexpression*
    ASTarray::compile(AST::CompilePhase ph)
    {
        Compile(mArgs, ph);
        if (!mArgs) {
            CfdgError::Error(where, "Illegal expression in vector index");
            return nullptr;
        }
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                bool isGlobal;
                const ASTparameter* bound = Builder::CurrentBuilder->findExpression(mName, isGlobal);
                assert(bound);
                if (bound ->mType != NumericType) {
                    CfdgError::Error(where, "Vectors can only have numeric components");
                    return nullptr;
                }
                
                isNatural = bound->isNatural;
                mStackIndex = bound->mStackIndex -
                    (isGlobal ? 0 : Builder::CurrentBuilder->mLocalStackDepth);
                mCount = bound->mTuplesize;
                isParameter = bound->isParameter;
                mLocality = bound->mLocality;
                
                mArgs->entropy(entString);
                if (bound->mStackIndex == -1) {
                    mData.reset(new double[mCount]);
                    if (bound->mDefinition->mExpression->evaluate(mData.get(), mCount) != mCount) {
                        CfdgError::Error(where, "Error computing vector data");
                        isConstant = false;
                        return nullptr;
                    }
                }
                
                ASTexpArray indices = Extract(std::move(mArgs));
                mArgs = std::move(indices[0]);
                
                for (size_t i = indices.size() - 1; i; --i) {
                    double data;
                    if ( indices[i]->mType != NumericType ||
                        !indices[i]->isConstant ||
                         indices[i]->evaluate(&data, 1) != 1)
                    {
                        CfdgError::Error(indices[i]->where, "Vector stride/length must be a scalar numeric constant");
                        break;
                    }
                    mStride = mLength;
                    mLength = static_cast<int>(data);
                }
                
                if (mArgs->mType != NumericType || mArgs->evaluate(nullptr, 0) != 1)
                    CfdgError::Error(mArgs->where, "Vector index must be a scalar numeric expression");

                if (mStride < 0 || mLength < 0)
                    CfdgError::Error(mArgs->where, "Vector length & stride arguments must be positive");
                if (mStride * (mLength - 1) >= mCount)
                    CfdgError::Error(mArgs->where, "Vector length & stride arguments too large for source");
                
                isConstant = mData && mArgs->isConstant;
                mLocality = CombineLocality(mLocality, mArgs->mLocality);
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return nullptr;
    }
    
    void
    ASTmodification::evalConst()
    {
        static const std::map<ASTmodTerm::modTypeEnum, int> ClassMap = {
            { ASTmodTerm::unknownType,  ASTmodification::NotAClass },
            { ASTmodTerm::x,            ASTmodification::GeomClass | ASTmodification::PathOpClass },
            { ASTmodTerm::y,            ASTmodification::GeomClass | ASTmodification::PathOpClass },
            { ASTmodTerm::z,            ASTmodification::ZClass },
            { ASTmodTerm::xyz,          ASTmodification::GeomClass | ASTmodification::ZClass },
            { ASTmodTerm::transform,    ASTmodification::GeomClass },
            { ASTmodTerm::size,         ASTmodification::GeomClass },
            { ASTmodTerm::sizexyz,      ASTmodification::GeomClass | ASTmodification::ZClass },
            { ASTmodTerm::rot,          ASTmodification::GeomClass | ASTmodification::PathOpClass },
            { ASTmodTerm::skew,         ASTmodification::GeomClass },
            { ASTmodTerm::flip,         ASTmodification::GeomClass },
            { ASTmodTerm::zsize,        ASTmodification::ZClass },
            { ASTmodTerm::hue,          ASTmodification::HueClass },
            { ASTmodTerm::sat,          ASTmodification::SatClass },
            { ASTmodTerm::bright,       ASTmodification::BrightClass },
            { ASTmodTerm::alpha,        ASTmodification::AlphaClass },
            { ASTmodTerm::hueTarg,      ASTmodification::HueClass },
            { ASTmodTerm::satTarg,      ASTmodification::SatClass },
            { ASTmodTerm::brightTarg,   ASTmodification::BrightClass },
            { ASTmodTerm::alphaTarg,    ASTmodification::AlphaClass },
            { ASTmodTerm::targHue,      ASTmodification::HueTargetClass },
            { ASTmodTerm::targSat,      ASTmodification::SatTargetClass },
            { ASTmodTerm::targBright,   ASTmodification::BrightTargetClass },
            { ASTmodTerm::targAlpha,    ASTmodification::AlphaTargetClass },
            { ASTmodTerm::time,         ASTmodification::TimeClass },
            { ASTmodTerm::timescale,    ASTmodification::TimeClass },
            { ASTmodTerm::stroke,       ASTmodification::StrokeClass },
            { ASTmodTerm::param,        ASTmodification::ParamClass },
            { ASTmodTerm::x1,           ASTmodification::PathOpClass },
            { ASTmodTerm::y1,           ASTmodification::PathOpClass },
            { ASTmodTerm::x2,           ASTmodification::PathOpClass },
            { ASTmodTerm::y2,           ASTmodification::PathOpClass },
            { ASTmodTerm::xrad,         ASTmodification::PathOpClass },
            { ASTmodTerm::yrad,         ASTmodification::PathOpClass },
            { ASTmodTerm::modification, -1 }
        };
        
        int nonConstant = 0;
        
        ASTtermArray temp;
        temp.swap(modExp);

        for (term_ptr& mod: temp) {
            if (!mod) {
                CfdgError::Error(where, "Unknown term in shape adjustment");
                continue;
            }
            
            // Put in code for separating color changes and target color changes
                        
            int mc = ClassMap.at(mod->modType);
            modClass |= mc;
            if (!mod->isConstant)
                nonConstant |= mc;
            bool keepThisOne = (mc & nonConstant) != 0;
            
            if (Builder::CurrentBuilder->mInPathContainer && (mc & ZClass))
                CfdgError::Warning(mod->where, "Z changes are not supported within paths");
            if (Builder::CurrentBuilder->mInPathContainer && (mc & TimeClass))
                CfdgError::Warning(mod->where, "Time changes are not supported within paths");
            
            try {
                if (!keepThisOne)
                    mod->evaluate(modData, false, nullptr);
            } catch (DeferUntilRuntime&) {
                keepThisOne = true;
            }
            
            if (keepThisOne) {
                assert(mod->modType != ASTmodTerm::param);
                Simplify(mod->args);
                modExp.push_back(std::move(mod));
            }
        }
    }
    
    void
    ASTmodification::addEntropy(const std::string& s)
    {
        modData.mRand64Seed.xorString(s.c_str(), entropyIndex);
    }
    
    size_t
    ASTselect::getIndex(RendererAST* rti) const
    {
        if (indexCache != NotCached)
            return indexCache;

        double select = 0.0;
        selector->evaluate(&select, 1, rti);

        if (ifSelect)
            return (select != 0.0) ? 0 : 1;
        
        if (select < 0.0)
            return 0;

        size_t i = static_cast<size_t>(select);

        if (i >= arguments.size())
            return arguments.size() - 1;
        return i;
    }
}

