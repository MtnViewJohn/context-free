// astexpression.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2009-2013 John Horigan - john@glyphic.com
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
#include <typeinfo>
#include <cassert>

namespace AST {
    
    ASTexpression*
    ASTexpression::constCopy(const ASTparameter* bound, const std::string& entropy) const
    {
        switch (bound->mType) {
            case AST::NumericType: {
                double data[9];
                bool natural = bound->isNatural;
                int valCount = bound->mDefinition->mExpression->evaluate(data, 9);
                if (valCount != bound->mTuplesize)
                    CfdgError::Error(where, "Unexpected compile error.");                   // this also shouldn't happen
                
                // Create a new cons-list based on the evaluated variable's expression
                ASTreal* top = new ASTreal(data[0], bound->mDefinition->mExpression->where);
                top->text = entropy;                // use variable name for entropy
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
                return new ASTmodification(bound->mDefinition->mChildChange, where);
            case AST::RuleType: {
                // This must be bound to an ASTruleSpecifier, otherwise it would not be constant
                if (const ASTruleSpecifier* r = dynamic_cast<const ASTruleSpecifier*> (bound->mDefinition->mExpression.get())) {
                    return new ASTruleSpecifier(r->shapeType, entropy, nullptr, where, nullptr);
                } else {
                    CfdgError::Error(where, "Internal error computing bound rule specifier");
                }
                break;
            }
            default:
                break;
        }
        return nullptr;
    }
    
    ASTfunction::ASTfunction(const std::string& func, exp_ptr args, Rand64& r,
                             const yy::location& nameLoc, const yy::location& argsLoc)
    : ASTexpression(nameLoc + argsLoc, true, false, NumericType),
      functype(NotAFunction), arguments(std::move(args))
    {
        if (&func == nullptr || func.empty()) {
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
        const std::map<std::string, ASTfunction::FuncType> NameMap = {
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
            { "min",        ASTfunction::Min },
            { "max",        ASTfunction::Max },
            { "ftime",      ASTfunction::Ftime },
            { "frame",      ASTfunction::Frame },
            { "rand_static", ASTfunction::Rand_Static },
            { "rand",       ASTfunction::Rand },
            { "rand+/-",    ASTfunction::Rand2 },
            { "randint",    ASTfunction::RandInt }
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
      arguments(std::move(r.arguments)), simpleRule(r.simpleRule), mStackIndex(r.mStackIndex),
      typeSignature(r.typeSignature), parentSignature(r.parentSignature)
    {
        r.simpleRule = nullptr;    // move semantics
    }
    
    ASTruleSpecifier::ASTruleSpecifier(exp_ptr args, const yy::location& loc)
    : ASTexpression(loc, false, false, RuleType), shapeType(-1),
      argSize(0), argSource(ShapeArgs), arguments(std::move(args)),
      simpleRule(nullptr), mStackIndex(0), typeSignature(nullptr),
      parentSignature(nullptr)
    {
        assert(arguments);
    }
    
    const StackRule*
    ASTruleSpecifier::evalArgs(RendererAST* rti, const StackRule* parent) const
    {
        switch (argSource) {
        case NoArgs:
        case SimpleArgs:
            return simpleRule;
        case StackArgs: {
            const StackType* stackItem = (mStackIndex < 0) ? rti->mLogicalStackTop + mStackIndex :
                                                             rti->mCFstack.data() + mStackIndex;
            stackItem->rule->retain(rti);
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
                ret->mRuleName = shapeType;
                return ret;
            }
        case SimpleParentArgs:
            assert(parent);
            assert(rti);
            parent->retain(rti);
            return parent;
        case DynamicArgs: {
            StackRule* ret = StackRule::alloc(shapeType, argSize, typeSignature);
            ret->evalArgs(rti, arguments.get(), parent);
            return ret;
        }
        case ShapeArgs:
            return arguments->evalArgs(rti, parent);
        default:
            assert(false);
            return nullptr;
        }
    }
    
    const StackRule*
    ASTparen::evalArgs(RendererAST* rti, const StackRule* parent) const
    {
        if (mType != RuleType) {
            CfdgError::Error(where, "Evaluation of a non-shape expression in a shape context");
            return nullptr;
        }
        
        return e->evalArgs(rti, parent);
    }
    
    const StackRule*
    ASTselect::evalArgs(RendererAST* rti, const StackRule* parent) const
    {
        if (mType != RuleType) {
            CfdgError::Error(where, "Evaluation of a non-shape select() in a shape context");
            return nullptr;
        }
        
        return (*arguments)[getIndex(rti)]->evalArgs(rti, parent);
    }
    
    const StackRule*
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
        
        const StackRule* ret = nullptr;
        
        if (definition->mStackCount) {
            size_t size = rti->mCFstack.size();
            if (size + definition->mStackCount > rti->mCFstack.capacity())
                CfdgError::Error(where, "Maximum stack size exceeded");
            const StackType*  oldLogicalStackTop = rti->mLogicalStackTop;
            rti->mCFstack.resize(size + definition->mStackCount);
            rti->mCFstack[size].evalArgs(rti, arguments.get(), &(definition->mParameters), isLet);
            rti->mLogicalStackTop = rti->mCFstack.data() + rti->mCFstack.size();
            ret = definition->mExpression->evalArgs(rti, parent);
            rti->mCFstack.resize(size);
            rti->mLogicalStackTop = oldLogicalStackTop;
        } else {
            ret = definition->mExpression->evalArgs(rti, parent);
        }
        return ret;
    }
    
    ASTcons::ASTcons(ASTexpression* l, ASTexpression* r)
    : ASTexpression(l->where, l->isConstant, l->isNatural, l->mType)
    {
        mLocality = l->mLocality;
        children.emplace_back(l);
        append(r);
    };

    ASTexpression*
    ASToperator::Op(char op, ASTexpression* l, ASTexpression* r)
    {
        if (l && r) return new ASToperator(op, l, r);
        return l ? l : r;
    }
    
    ASToperator::ASToperator(char o, ASTexpression* l, ASTexpression* r)
    : ASTexpression(r ? (l->where + r->where) : l->where), op(o), left(l), right(r) 
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
    
    ASTmodification::ASTmodification(const ASTmodification& m, const yy::location& loc)
    : ASTexpression(loc, true, false, ModType), modData(m.modData), 
      modClass(m.modClass), strokeWidth(m.strokeWidth), flags(m.flags), 
      entropyIndex(m.entropyIndex), canonical(m.canonical)
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
            strokeWidth = 0.1;
            flags = CF_MITER_JOIN + CF_BUTT_CAP + CF_FILL;
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
        strokeWidth = m->strokeWidth;
        flags = m->flags;
        entropyIndex = (entropyIndex + m->entropyIndex) & 7;
        isConstant = modExp.empty();
        canonical = m->canonical;
    }
    
    ASTselect::ASTselect(exp_ptr args, const yy::location& loc, bool asIf)
    : ASTexpression(loc), tupleSize(-1), indexCache(0), arguments(std::move(args)),
      ifSelect(asIf)
    {
        isConstant = false;
        
        if (!arguments || arguments->size() < 3) {
            CfdgError::Error(loc, "select()/if() function requires arguments");
            return;
        }
    }
    
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
      mConstData(false), mArgs(std::move(args)), mLength(1), mStride(1),
      mStackIndex(-1), mCount(0), isParameter(false), entString(name)
    {
    }

    ASTruleSpecifier::~ASTruleSpecifier()
    {
        // simpleRule is deleted along with the long-lived params
    };
    
    ASTcons::~ASTcons()
    {
    }
    
    ASTselect::~ASTselect()
    {
    }
    
    ASTmodification::~ASTmodification()
    {
    }
    
    ASTarray::~ASTarray()
    {
    }
    
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
        return sib ? new ASTcons(this, sib) : this;
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
        for (int i = 0; i < sib->size(); ++i)
            children.emplace_back((*sib)[i]);
        if (sib->release())
            delete sib;
        return this;
    }
    
    bool
    ASTcons::release(size_t i)
    {
        if (i == std::numeric_limits<size_t>::max()) {
            for (exp_ptr& child: children) {
                child.release();
            }
            children.clear();
        } else if (i < children.size()) {
            children[i].release();
        } else {
            CfdgError::Error(where, "Expression list bounds exceeded");
        }
        return true;
    }
    
    ASTexpression*
    ASTexpression::operator[](size_t i)
    {
        if (i)
            CfdgError::Error(where, "Expression list bounds exceeded");
        return this;
    }
    
    const ASTexpression*
    ASTexpression::operator[](size_t i) const
    {
        if (i)
            CfdgError::Error(where, "Expression list bounds exceeded");
        return this;
    }
    
    ASTexpression*
    ASTcons::operator[](size_t i)
    {
        if (i >= children.size()) {
            CfdgError::Error(where, "Expression list bounds exceeded");
            return this;
        }
        return children[i].get();
    }
    
    const ASTexpression*
    ASTcons::operator[](size_t i) const
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
            const StackType* stackItem = (stackIndex < 0) ? rti->mLogicalStackTop + stackIndex :
                                                            rti->mCFstack.data() + stackIndex;
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
        
        if (definition->mStackCount) {
            size_t size = rti->mCFstack.size();
            if (size + definition->mStackCount > rti->mCFstack.capacity())
                CfdgError::Error(where, "Maximum stack size exceeded");
            const StackType*  oldLogicalStackTop = rti->mLogicalStackTop;
            rti->mCFstack.resize(size + definition->mStackCount);
            rti->mCFstack[size].evalArgs(rti, arguments.get(), &(definition->mParameters), isLet);
            rti->mLogicalStackTop = rti->mCFstack.data() + rti->mCFstack.size();
            definition->mExpression->evaluate(res, length, rti);
            rti->mCFstack.resize(size);
            rti->mLogicalStackTop = oldLogicalStackTop;
        } else {
            definition->mExpression->evaluate(res, length, rti);
        }
        return definition->mTuplesize;
    }
    
    int
    ASToperator::evaluate(double* res, int length, RendererAST* rti) const
    {
        double l = 0.0;
        double r = 0.0;
        
        if (res && length < 1)
            return -1;
        
        if (mType == FlagType && op == '+') {
            if (left->evaluate(res ? &l : nullptr, 1, rti) != 1)
                return -1;
            if (!right || right->evaluate(res ? &r : nullptr, 1, rti) != 1)
                return -1;
            int f = static_cast<int>(l) | static_cast<int>(r);
            if (res)
                *res = static_cast<double>(f);
            return 1;
        }
        
        if (mType != NumericType) {
            CfdgError::Error(where, "Non-numeric expression in a numeric context");
            return -1;
        }
        
        if (left->evaluate(res ? &l : nullptr, 1, rti) != 1) {
            CfdgError::Error(left->where, "illegal operand");
            return -1;
        }
        
        // short-circuit evaluate && and ||
        if (res && (op == '&' || op == '|')) {
            if (l != 0.0 && op == '|') {
                *res = l;
                return 1;
            }
            if (l == 0.0 && op == '&') {
                *res = 0.0;
                return 1;
            }
        }
        
        int rightnum = right ? right->evaluate(res ? &r : nullptr, 1, rti) : 0;
        
        if (rightnum == 0 && (op == 'N' || op == 'P' || op == '!')) {
            if (res) {
                switch (op) {
                    case 'P':
                        *res = l;
                        break;
                    case 'N':
                        *res = -l;
                        break;
                    case '!':
                        *res = (l == 0.0) ? 1.0 : 0.0;
                        break;
                    default:
                        return -1;
                }
            }
            return 1;
        }
        
        if (rightnum != 1) {
            CfdgError::Error(left->where, "illegal operand");
            return -1;
        }
        
        
        if (res) {
            switch(op) {
                case '+':
                    *res = l + r;
                    break;
                case '-':
                    *res = l - r;
                    break;
                case '_':
                    *res = l - r > 0.0 ? l - r : 0.0;
                    break;
                case '*':
                    *res = l * r;
                    break;
                case '/':
                    *res = l / r;
                    break;
                case '<':
                    *res = (l < r) ? 1.0 : 0.0;
                    break;
                case 'L':
                    *res = (l <= r) ? 1.0 : 0.0;
                    break;
                case '>':
                    *res = (l > r) ? 1.0 : 0.0;
                    break;
                case 'G':
                    *res = (l >= r) ? 1.0 : 0.0;
                    break;
                case '=':
                    *res = (l == r) ? 1.0 : 0.0;
                    break;
                case 'n':
                    *res = (l != r) ? 1.0 : 0.0;
                    break;
                case '&':
                case '|':
                    *res = r;
                    break;
                case 'X':
                    *res = ((l && !r) || (!l && r)) ? 1.0 : 0.0;
                    break;
                case '^':
                    *res = pow(l, r);
                    if (isNatural && *res < 9007199254740992.) {
                        uint64_t pow = 1;
                        uint64_t il = static_cast<uint64_t>(l);
                        uint64_t ir = static_cast<uint64_t>(r);
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
        
        return 1;
    }
    
    static double MinMax(const ASTexpression* e, RendererAST* rti, bool isMin)
    {
        double res = 0.0;
        if ((*e)[0]->evaluate(&res, 1, rti) != 1)
            CfdgError::Error((*e)[0]->where, "Error computing min/max here.");
        for (int i = 1; i < e->size(); ++i) {
            double v;
            if ((*e)[i]->evaluate(&v, 1, rti) != 1)
                CfdgError::Error((*e)[i]->where, "Error computing min/max here.");
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
        if ((res && length < 1) || (functype <= NotAFunction) || (functype >= LastOne))
            return -1;
        
        if (!res)
            return 1;
        
        if (functype == Min || functype == Max) {
            *res = MinMax(arguments.get(), rti, functype == Min);
            return 1;
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
            case RandInt: 
                if (rti == nullptr) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = floor(rti->mCurrentSeed.getDouble() * fabs(a[1] - a[0]) + fmin(a[0], a[1]));
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
        
        return (*arguments)[getIndex(rti)]->evaluate(res, length, rti);
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
            if (rti == nullptr && !mConstData) throw DeferUntilRuntime();
            
            double i;
            if (mArgs->evaluate(&i, 1, rti) != 1) {
                CfdgError::Error(mArgs->where, "Cannot evaluate array index");
                return -1;
            }
            int index = static_cast<int>(i);
            if ((mLength - 1) * mStride + index >= mCount || index < 0) {
                CfdgError::Error(where, "array index exceeds bounds");
                return -1;
            }
            
            const double* source = mData;
            if (!mConstData)
                source = (mStackIndex < 0) ? &(rti->mLogicalStackTop[mStackIndex].number) :
                                             &(rti->mCFstack[mStackIndex].number);
            
            for (int i = 0; i < mLength; ++i)
                res[i] = source[i * mStride + index];
        }
        
        return mLength;
    }
    
    void
    ASTselect::evaluate(Modification& m, double* width, 
                        bool justCheck, int& seedIndex, bool shapeDest,
                        RendererAST* rti) const
    {
        if (mType != ModType) {
            CfdgError::Error(where, "Evaluation of a non-adjustment select() in an adjustment context");
            return;
        }
        
        (*arguments)[getIndex(rti)]->evaluate(m, width, justCheck, seedIndex, shapeDest, rti);
    }
    
    void
    ASTvariable::evaluate(Modification& m, double*, 
                          bool justCheck, int&, bool shapeDest,
                          RendererAST* rti) const
    {
        if (mType != ModType)
            CfdgError::Error(where, "Non-adjustment variable referenced in an adjustment context");
        
        if (rti == nullptr) throw DeferUntilRuntime();
        if (justCheck) return;
        const StackType* stackItem = (stackIndex < 0) ? rti->mLogicalStackTop + stackIndex :
                                                        rti->mCFstack.data() + stackIndex;
        const Modification* smod = reinterpret_cast<const Modification*> (stackItem);
        if (shapeDest) {
            m *= *smod;
        } else {
            if (m.merge(*smod))
                RendererAST::ColorConflict(rti, where);
        }
    }
    
    void
    ASTcons::evaluate(Modification& m, double* width, 
                      bool justCheck, int& seedIndex, bool shapeDest,
                      RendererAST* rti) const
    {
        for (size_t i = 0; i < children.size(); ++i)
            children[i]->evaluate(m, width, justCheck, seedIndex, shapeDest, rti);
    }
    
    void
    ASTuserFunction::evaluate(Modification &m, double *width, 
                              bool justCheck, int &seedIndex, bool shapeDest,
                              RendererAST* rti) const
    {
        if (mType != ModType) {
            CfdgError::Error(where, "Function does not evaluate to an adjustment");
            return;
        }
        
        if (!rti)
            throw DeferUntilRuntime();
        
        if (rti->requestStop || Renderer::AbortEverything)
            throw CfdgError(where, "Stopping");
        
        if (definition->mStackCount) {
            size_t size = rti->mCFstack.size();
            if (size + definition->mStackCount > rti->mCFstack.capacity())
                CfdgError::Error(where, "Maximum stack size exceeded");
            const StackType*  oldLogicalStackTop = rti->mLogicalStackTop;
            rti->mCFstack.resize(size + definition->mStackCount);
            rti->mCFstack[size].evalArgs(rti, arguments.get(), &(definition->mParameters), isLet);
            rti->mLogicalStackTop = rti->mCFstack.data() + rti->mCFstack.size();
            definition->mExpression->evaluate(m, width, justCheck, seedIndex, shapeDest, rti);
            rti->mCFstack.resize(size);
            rti->mLogicalStackTop = oldLogicalStackTop;
        } else {
            definition->mExpression->evaluate(m, width, justCheck, seedIndex, shapeDest, rti);
        }
    }
    
    void
    ASTmodification::evaluate(Modification& m, double* width, 
                              bool justCheck, int& seedIndex, bool shapeDest,
                              RendererAST* rti) const
    {
        if (shapeDest) {
            m *= modData;
        } else {
            if (m.merge(modData))
                RendererAST::ColorConflict(rti, where);
        }
        
        for (const term_ptr& term: modExp)
            term->evaluate(m, width, justCheck, seedIndex, shapeDest, rti);
    }
    
    void
    ASTmodification::setVal(Modification& m, double* width, 
                            bool justCheck, int& seedIndex, 
                            RendererAST* rti) const
    {
        m = modData;
        for (const term_ptr& term: modExp)
            term->evaluate(m, width, justCheck, seedIndex, false, rti);
    }
    
    void
    ASTparen::evaluate(Modification& m, double* width,
                       bool justCheck, int& seedIndex, bool shapeDest,
                       RendererAST* rti) const
    {
        if (mType != ModType) {
            CfdgError::Error(where, "Expression does not evaluate to an adjustment");
            return;
        }
        
        e->evaluate(m, width, justCheck, seedIndex, shapeDest, rti);
    }
    
    void
    ASTmodTerm::evaluate(Modification& m, double* width,
                        bool justCheck, int& seedIndex, bool shapeDest,
                        RendererAST* rti) const
    {
        double modArgs[6] = {0.0};
        int argcount = 0;
        
        if (args) {
            if (modType != modification && args->mType == NumericType) {
                if (justCheck)
                    argcount = args->evaluate(nullptr, 0);
                else 
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
        
        switch (modType) {
            case ASTmodTerm::x: {
                if (justCheck) break;
                if (argcount == 1) 
                    modArgs[1] = 0.0;
                agg::trans_affine_translation trx(modArgs[0], modArgs[1]);
                m.m_transform.premultiply(trx);
                break;
            }
            case ASTmodTerm::y: {
                if (justCheck) break;
                agg::trans_affine_translation tr(0.0, modArgs[0]);
                m.m_transform.premultiply(tr);
                break;
            }
            case ASTmodTerm::z: {
                if (justCheck) break;
                agg::trans_affine_1D_translation tr(modArgs[0]);
                m.m_Z.premultiply(tr);
                break;
            }
            case ASTmodTerm::xyz: {
                if (justCheck) break;
                agg::trans_affine_translation trx(modArgs[0], modArgs[1]);
                m.m_transform.premultiply(trx);
                agg::trans_affine_1D_translation trz(modArgs[2]);
                m.m_Z.premultiply(trz);
                break;
            }
            case ASTmodTerm::time: {
                if (justCheck) break;
                agg::trans_affine_time_translation tr(modArgs[0], modArgs[1]);
                m.m_time.premultiply(tr);
                break;
            }
            case ASTmodTerm::timescale: {
                if (justCheck) break;
                agg::trans_affine_time_scaling sc(modArgs[0]);
                m.m_time.premultiply(sc);
                break;
            }
            case ASTmodTerm::transform: {
                if (argcount != 1 && argcount != 2 && argcount != 4 && argcount != 6)
                    CfdgError::Error(where, "transform adjustment takes 1, 2, 4, or 6 parameters");
                if (justCheck) break;
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
                if (justCheck) break;
                if (argcount == 1) 
                    modArgs[1] = modArgs[0];
                agg::trans_affine_scaling sc(modArgs[0], modArgs[1]);
                m.m_transform.premultiply(sc);
                break;
            }
            case ASTmodTerm::sizexyz: {
                if (justCheck) break;
                agg::trans_affine_scaling sc(modArgs[0], modArgs[1]);
                m.m_transform.premultiply(sc);
                agg::trans_affine_1D_scaling scz(modArgs[2]);
                m.m_Z.premultiply(scz);
                break;
            }
            case ASTmodTerm::zsize: {
                if (justCheck) break;
                agg::trans_affine_1D_scaling sc(modArgs[0]);
                m.m_Z.premultiply(sc);
                break;
            }
            case ASTmodTerm::rot: {
                if (justCheck) break;
                agg::trans_affine_rotation rot(modArgs[0] * MY_PI / 180.0);
                m.m_transform.premultiply(rot);
                break;
            }
            case ASTmodTerm::skew: {
                if (justCheck) break;
                agg::trans_affine_skewing sk(modArgs[0] * MY_PI / 180.0, 
                                             modArgs[1] * MY_PI / 180.0);
                m.m_transform.premultiply(sk);
                break;
            }
            case ASTmodTerm::flip: {
                if (justCheck) break;
                agg::trans_affine_reflection ref(modArgs[0] * MY_PI / 180.0);
                m.m_transform.premultiply(ref);
                break;
            }
            case ASTmodTerm::hue: {
                if (justCheck) break;
                if (argcount == 1) {
                    if (m.m_ColorAssignment & HSBColor::HueMask) {
                        if (rti == nullptr)
                            throw DeferUntilRuntime();
                        if (!shapeDest)
                            RendererAST::ColorConflict(rti, where);
                    }
                    if (shapeDest)
                        m.m_Color.h = HSBColor::adjustHue(m.m_Color.h, modArgs[0]);
                    else
                        m.m_Color.h += modArgs[0];
                } else {
                    if ((m.m_ColorAssignment & HSBColor::HueMask ||
                         m.m_Color.h != 0.0))
                    {
                        if (rti == nullptr)
                            throw DeferUntilRuntime();
                        if (!shapeDest)
                            RendererAST::ColorConflict(rti, where);
                    }
                    if (shapeDest) {
                        m.m_Color.h = HSBColor::adjustHue(m.m_Color.h, arg[0],
                                                          HSBColor::HueTarget,
                                                          modArgs[1]);
                    } else {
                        m.m_Color.h = arg[0];
                        m.m_ColorTarget.h = modArgs[1];
                        m.m_ColorAssignment |= HSBColor::Hue2Value;
                    }
                }
                break;
            }
            case ASTmodTerm::sat: {
                if (justCheck) break;
                if (argcount == 1) {
                    if ((m.m_ColorAssignment & HSBColor::SaturationMask) ||
                         m.m_Color.s != 0.0)
                    {
                        if (rti == nullptr)
                            throw DeferUntilRuntime();
                        if (!shapeDest)
                            RendererAST::ColorConflict(rti, where);
                    }
                    if (shapeDest)
                        m.m_Color.s = HSBColor::adjust(m.m_Color.s, arg[0]);
                    else
                        m.m_Color.s = arg[0];
                } else {
                    if ((m.m_ColorAssignment & HSBColor::SaturationMask) ||
                         m.m_Color.s != 0.0 || m.m_ColorTarget.s != 0.0)
                    {
                        if (rti == nullptr)
                            throw DeferUntilRuntime();
                        if (!shapeDest)
                            RendererAST::ColorConflict(rti, where);
                    }
                    if (shapeDest) {
                        m.m_Color.s = HSBColor::adjust(m.m_Color.s, arg[0], 1, arg[1]);
                    } else {
                        m.m_Color.s = arg[0];
                        m.m_ColorTarget.s = arg[1];
                        m.m_ColorAssignment |= HSBColor::Saturation2Value;
                    }
                }
                break;
            }
            case ASTmodTerm::bright: {
                if (justCheck) break;
                if (argcount == 1) {
                    if ((m.m_ColorAssignment & HSBColor::BrightnessMask ||
                         m.m_Color.b != 0.0))
                    {
                        if (rti == nullptr)
                            throw DeferUntilRuntime();
                        if (!shapeDest)
                            RendererAST::ColorConflict(rti, where);
                    }
                    if (shapeDest)
                        m.m_Color.b = HSBColor::adjust(m.m_Color.b, arg[0]);
                    else
                        m.m_Color.b = arg[0];
                } else {
                    if ((m.m_ColorAssignment & HSBColor::BrightnessMask) ||
                         m.m_Color.b != 0.0 || m.m_ColorTarget.b != 0.0)
                    {
                        if (rti == nullptr)
                            throw DeferUntilRuntime();
                        if (!shapeDest)
                            RendererAST::ColorConflict(rti, where);
                    }
                    if (shapeDest) {
                        m.m_Color.b = HSBColor::adjust(m.m_Color.b, arg[0], 1, arg[1]);
                    } else {
                        m.m_Color.b = arg[0];
                        m.m_ColorTarget.b = arg[1];
                        m.m_ColorAssignment |= HSBColor::Brightness2Value;
                    }
                }
                break;
            }
            case ASTmodTerm::alpha: {
                if (justCheck) break;
                if (argcount == 1) {
                    if ((m.m_ColorAssignment & HSBColor::AlphaMask ||
                         m.m_Color.a != 0.0))
                    {
                        if (rti == nullptr)
                            throw DeferUntilRuntime();
                        if (!shapeDest)
                            RendererAST::ColorConflict(rti, where);
                    }
                    if (shapeDest)
                        m.m_Color.a = HSBColor::adjust(m.m_Color.a, arg[0]);
                    else
                        m.m_Color.a = arg[0];
                } else {
                    if ((m.m_ColorAssignment & HSBColor::AlphaMask) ||
                         m.m_Color.a != 0.0 || m.m_ColorTarget.a != 0.0)
                    {
                        if (rti == nullptr)
                            throw DeferUntilRuntime();
                        if (!shapeDest)
                            RendererAST::ColorConflict(rti, where);
                    }
                    if (shapeDest) {
                        m.m_Color.a = HSBColor::adjust(m.m_Color.a, arg[0], 1, arg[1]);
                    } else {
                        m.m_Color.a = arg[0];
                        m.m_ColorTarget.a = arg[1];
                        m.m_ColorAssignment |= HSBColor::Alpha2Value;
                    }
                }
                break;
            }
            case ASTmodTerm::hueTarg: {
                if (justCheck) break;
                if ((m.m_ColorAssignment & HSBColor::HueMask) ||
                     m.m_Color.h != 0.0)
                {
                    if (rti == nullptr)
                        throw DeferUntilRuntime();
                    if (!shapeDest)
                        RendererAST::ColorConflict(rti, where);
                }
                if (shapeDest) {
                    m.m_Color.h = HSBColor::adjustHue(m.m_Color.h, arg[0],
                                                      HSBColor::HueTarget,
                                                      m.m_ColorTarget.h);
                } else {
                    m.m_Color.h = arg[0];
                    m.m_ColorAssignment |= HSBColor::HueTarget;
                }
                break;
            }
            case ASTmodTerm::satTarg: {
                if (justCheck) break;
                if ((m.m_ColorAssignment & HSBColor::SaturationMask) ||
                     m.m_Color.s != 0.0)
                {
                    if (rti == nullptr)
                        throw DeferUntilRuntime();
                    if (!shapeDest)
                        RendererAST::ColorConflict(rti, where);
                }
                if (shapeDest) {
                    m.m_Color.s = HSBColor::adjust(m.m_Color.s, arg[0], 1,
                                                   m.m_ColorTarget.s);
                } else {
                    m.m_Color.s = arg[0];
                    m.m_ColorAssignment |= HSBColor::SaturationTarget;
                }
                break;
            }
            case ASTmodTerm::brightTarg: {
                if (justCheck) break;
                if ((m.m_ColorAssignment & HSBColor::BrightnessMask) ||
                     m.m_Color.b != 0.0)
                {
                    if (rti == nullptr)
                        throw DeferUntilRuntime();
                    if (!shapeDest)
                        RendererAST::ColorConflict(rti, where);
                }
                if (shapeDest) {
                    m.m_Color.b = HSBColor::adjust(m.m_Color.b, arg[0], 1,
                                                   m.m_ColorTarget.b);
                } else {
                    m.m_Color.b = arg[0];
                    m.m_ColorAssignment |= HSBColor::BrightnessTarget;
                }
                break;
            }
            case ASTmodTerm::alphaTarg: {
                if (justCheck) break;
                if ((m.m_ColorAssignment & HSBColor::AlphaMask) ||
                     m.m_Color.a != 0.0)
                {
                    if (rti == nullptr)
                        throw DeferUntilRuntime();
                    if (!shapeDest)
                        RendererAST::ColorConflict(rti, where);
                }
                if (shapeDest) {
                    m.m_Color.a = HSBColor::adjust(m.m_Color.a, arg[0], 1,
                                                   m.m_ColorTarget.a);
                } else {
                    m.m_Color.a = arg[0];
                    m.m_ColorAssignment |= HSBColor::AlphaTarget;
                }
                break;
            }
            case ASTmodTerm::targHue: {
                if (justCheck) break;
                m.m_ColorTarget.h += modArgs[0];
                break;
            }
            case ASTmodTerm::targSat: {
                if (justCheck) break;
                if (m.m_ColorTarget.s != 0.0) {
                    if (rti == nullptr)
                        throw DeferUntilRuntime();
                    if (!shapeDest)
                        RendererAST::ColorConflict(rti, where);
                }
                if (shapeDest)
                    m.m_ColorTarget.s = HSBColor::adjust(m.m_ColorTarget.s, arg[0]);
                else
                    m.m_ColorTarget.s = arg[0];
                break;
            }
            case ASTmodTerm::targBright: {
                if (justCheck) break;
                if (m.m_ColorTarget.b != 0.0) {
                    if (rti == nullptr)
                        throw DeferUntilRuntime();
                    if (!shapeDest)
                        RendererAST::ColorConflict(rti, where);
                }
                if (shapeDest)
                    m.m_ColorTarget.b = HSBColor::adjust(m.m_ColorTarget.b, arg[0]);
                else
                    m.m_ColorTarget.b = arg[0];
                break;
            }
            case ASTmodTerm::targAlpha: {
                if (justCheck) break;
                if (m.m_ColorTarget.a != 0.0) {
                    if (rti == nullptr)
                        throw DeferUntilRuntime();
                    if (!shapeDest)
                        RendererAST::ColorConflict(rti, where);
                }
                if (shapeDest)
                    m.m_ColorTarget.a = HSBColor::adjust(m.m_ColorTarget.a, arg[0]);
                else
                    m.m_ColorTarget.a = arg[0];
                break;
            }
            case ASTmodTerm::stroke: {
                if (!width) {
                    CfdgError::Error(where, "Cannot provide a stroke width in this context");
                    break;
                }
                if (justCheck) break;
                *width = modArgs[0];
                break;
            }
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
                args->evaluate(m, width, justCheck, seedIndex, shapeDest, rti);
                break;
            }
            default:
                break;
        }
    }
    
    void
    ASTfunction::entropy(std::string& ent) const
    {
        // These random strings are courtesy of http://www.fourmilab.ch/hotbits/
        const std::map<ASTfunction::FuncType, const char*> EntropyMap = {
            {ASTfunction::Cos,          "\xA1\xE7\x9C\x1A\xAF\x7D"},
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
            { ASTfunction::Mod,         "\x0F\xE3\xFE\x5F\xBF\xBF" },
            { ASTfunction::Min,         "\xA2\x42\xA3\x49\xB1\x19" },
            { ASTfunction::Max,         "\xD3\x55\x5C\x0D\xD8\x51" },
            { ASTfunction::Ftime,       "\x4F\xBE\xA1\x06\x80\x06" },
            { ASTfunction::Frame,       "\x90\x70\x6A\xBB\xBA\xB0" },
            { ASTfunction::Rand_Static, "\xC8\xF7\xE5\x3E\x05\xA3" },
            { ASTfunction::Rand,        "\xDA\x18\x5B\xE2\xDB\x79" },
            { ASTfunction::Rand2,       "\xDC\x8D\x09\x15\x8A\xC4" },
            { ASTfunction::RandInt,     "\x48\x14\x4E\x27\x35\x2E" }
        };
        
		if (functype <= NotAFunction || functype >= LastOne) return;

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
        ent.append(definition->mName);
    }
    
    void
    ASToperator::entropy(std::string& ent) const
    {
        left->entropy(ent);
        if (right) right->entropy(ent);
        
        // These random strings are courtesy of http://www.fourmilab.ch/hotbits/
        switch (op) {
            case '*':
                ent.append("\x2E\x32\xD9\x2C\x41\xFE");
                break;
            case '/':
                ent.append("\x6B\x15\x23\x41\x9E\xEB");
                break;
            case '+':
                ent.append("\xD7\xB1\xB0\x39\x33\xC8");
                break;
            case '-':
                ent.append("\x5D\xE7\xF0\x94\xC4\x13");
                break;
            case '^':
                ent.append("\x02\x3C\x68\x36\xC5\xA0");
                break;
            case 'N':
                ent.append("\x55\x89\x51\x46\xDB\x84");
                break;
            case 'P':
                ent.append("\x8E\xAC\x29\x4B\x0E\xDC");
                break;
            case '!':
                ent.append("\x19\x3A\x3E\x53\x14\xEA");
                break;
            case '<':
                ent.append("\xBE\xDB\xC4\xA6\x4E\xAD");
                break;
            case '>':
                ent.append("\xC7\xD9\x57\x32\xD6\x87");
                break;
            case 'L':
                ent.append("\xE3\x56\x7E\x44\x57\x80");
                break;
            case 'G':
                ent.append("\xB1\x2D\x2A\xCC\x2C\x40");
                break;
            case '=':
                ent.append("\x78\x48\xC2\x95\xA9\xE2");
                break;
            case 'n':
                ent.append("\x36\xCC\x01\x3B\x2F\xAD");
                break;
            case '&':
                ent.append("\x28\x9B\xFB\x7F\xDB\x9C");
                break;
            case '|':
                ent.append("\x2E\x40\x1B\x44\x15\x7C");
                break;
            case 'X':
                ent.append("\xA7\x2B\x92\xFA\xFC\xF9");
                break;
            default:
                ent.append("\x60\x2F\x10\xAD\x10\xFF");
                break;
        }
    }
    
    void
    ASTparen::entropy(std::string& ent) const
    {
        e->entropy(ent);
        ent.append("\xE8\xE9\xF6\x7E\x1A\xF1");
    }
    
    void
    ASTmodTerm::entropy(std::string& ent) const
    {
        // These random strings are courtesy of http://www.fourmilab.ch/hotbits/
        const std::map<ASTmodTerm::modTypeEnum, const char*> EntropyMap = {
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
    
    ASTexpression*
    ASTfunction::simplify()
    {
        if (isConstant) {
            double result;
            if (evaluate(&result, 1) != 1) {
                return this;
            }
            
            ASTreal* r = new ASTreal(result, where);
            r->isNatural = isNatural;
            
            delete this;
            return r;
        } else {
            Simplify(arguments);
        }
        
        return this;
    }
    
    ASTexpression*
    ASTselect::simplify()
    {
        if (!indexCache) {
            Simplify(arguments);
            return this;
        }
        
        ASTexpression* chosenOne = (*arguments)[indexCache];
        if (!arguments->release(indexCache))
            return this;
        
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
            ASTexpression* ret = definition->mExpression ?
                definition->mExpression->constCopy(&p, ent) :
                definition->mChildChange.constCopy(&p, ent);
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
            double result;
            if (evaluate(&result, 1) != 1) {
                return nullptr;
            }
            
            ASTreal* r = new ASTreal(result, where);
            r->mType = mType;
            r->isNatural = isNatural;
            
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
    
    ASTvariable::ASTvariable(int stringNum, const std::string& str, const yy::location& loc) 
    : ASTexpression(loc), stringIndex(stringNum), text(str), stackIndex(0),
      isParameter(false) { };
    
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
        if (!isConstant) {
            Simplify(mArgs);
            return this;
        }
        
        double i;
        if (mArgs->evaluate(&i, 1) != 1) {
            CfdgError::Error(mArgs->where, "Cannot evaluate array index");
            return this;
        }
        int index = static_cast<int>(i);
        if ((mLength - 1) * mStride + index >= mCount || index < 0) {
            CfdgError::Error(where, "Array index exceeds bounds");
            return this;
        }
        
        // Create a new cons-list based on the evaluated variable's expression
        ASTreal* top = new ASTreal(mData[index], where);
        top->text = entString;                // use variable name for entropy
        ASTexpression* list = top;
        for (int i = 1; i < mLength; ++i)
            list = list->append(new ASTreal(mData[i * mStride + index], where));
        list->isNatural = isNatural;
        delete this;
        return list;
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
                if (arguments) {
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
                
                if (functype == ASTfunction::Infinity && argcount == 0) {
                    arguments.reset(new ASTreal(1.0, argsLoc));
                    return this;
                }
                
                if (functype == Ftime) {
                    if (arguments)
                        CfdgError::Error(argsLoc, "ftime() function takes no arguments");
                    isConstant = false;
                    arguments.reset(new ASTreal(1.0, argsLoc));
                    return this;
                }
                
                if (functype == Frame) {
                    if (arguments)
                        CfdgError::Error(argsLoc, "frame() functions takes no arguments");
                    isConstant = false;
                    arguments.reset(new ASTreal(1.0, argsLoc));
                    return this;
                }
                
                if (functype >= Rand_Static && functype <= RandInt) {
                    if (functype != Rand_Static)
                        isConstant = false;
                    
                    switch (argcount) {
                        case 0:
                            arguments.reset(new ASTcons(new ASTreal(0.0, argsLoc),
                                                        new ASTreal(functype == RandInt ? 2.0 : 1.0, argsLoc)));
                            break;
                        case 1:
                            arguments.reset(new ASTcons(new ASTreal(0.0, argsLoc), arguments.release()));
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
                    
                    if (functype == RandInt && arguments)
                        isNatural = arguments->isNatural;
                    return this;
                }
                
                if (functype == Abs) {
                    if (argcount < 1 || argcount > 2) {
                        CfdgError::Error(argsLoc, "function takes one or two arguments");
                    }
                } else if (functype < BitOr) {
                    if (argcount != 1) {
                        CfdgError::Error(argsLoc, functype == ASTfunction::Infinity ?
                                         "function takes zero or one arguments" :
                                         "function takes one argument");
                    }
                } else if (functype < Min) {
                    if (argcount != 2) {
                        CfdgError::Error(argsLoc, "function takes two arguments");
                    }
                } else {
                    if (argcount < 2) {
                        CfdgError::Error(argsLoc, "function takes at least two arguments");
                    }
                }

                if (functype == Mod || functype == Abs || functype == Min ||
                    functype == Max || (functype >= BitNot && functype <= BitRight))
                {
                    isNatural = arguments ? arguments->isNatural : true;
                }
                if (functype == Factorial || functype == Sg || functype == IsNatural ||
                    functype == Div || functype == Divides)
                {
                    if (arguments && !arguments->isNatural)
                        CfdgError::Error(arguments->where, "function is defined over natural numbers only");
                    isNatural = true;
                }
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return this;
    }
    
    ASTexpression*
    ASTselect::compile(AST::CompilePhase ph)
    {
        if (!arguments)
            return this;
        Compile(arguments, ph);
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                arguments->entropy(ent);
                ent.append("\xB5\xA2\x4A\x74\xA9\xDF");
                
                if ((*arguments)[0]->mType != NumericType ||
                    (*arguments)[0]->evaluate(nullptr, 0) != 1)
                {
                    CfdgError::Error((*arguments)[0]->where, "is()/select() selector must be a numeric scalar");
                    return this;
                }
                
                mType = (*arguments)[1]->mType;
                mLocality = arguments->mLocality;
                isNatural = (*arguments)[1]->isNatural;
                tupleSize = (mType == NumericType) ? (*arguments)[1]->evaluate(nullptr, 0) : 1;
                if (tupleSize > 1) isNatural = false;
                if (tupleSize == -1)
                    CfdgError::Error((*arguments)[1]->where, "Error determining tuple size");
                
                for (int i = 2; i < arguments->size(); ++i) {
                    if (mType != (*arguments)[i]->mType) {
                        CfdgError::Error((*arguments)[i]->where, "select()/if() choices must be of same type");
                    } else if (mType == NumericType && tupleSize != -1 &&
                               (*arguments)[i]->evaluate(nullptr, 0) != tupleSize)
                    {
                        CfdgError::Error((*arguments)[i]->where, "select()/if() choices must be of same length");
                    }
                    isNatural = isNatural && (*arguments)[i]->isNatural;
                }
                
                if (ifSelect && arguments->size() != 3) {
                    CfdgError::Error(arguments->where, "if() function requires two arguments");
                }
                
                if ((*arguments)[0]->isConstant) {
                    indexCache = getIndex();
                    isConstant = (*arguments)[indexCache]->isConstant;
                    mLocality = (*arguments)[indexCache]->mLocality;
                    isNatural = (*arguments)[indexCache]->isNatural;
                }
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return this;
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
                        return this;
                    case SimpleParentArgs:
                        assert(typeSignature == parentSignature);
                        assert(arguments && arguments->mType == ReuseType);
                        isConstant = true;
                        mLocality = PureLocal;
                        return this;
                    case StackArgs: {
                        bool isGlobal;
                        const ASTparameter* bound = Builder::CurrentBuilder->findExpression(shapeType, isGlobal);
                        assert(bound);
                        if (bound->mType != RuleType) {
                            CfdgError::Error(where, "Shape name does not bind to a rule variable");
                            CfdgError::Error(bound->mLocation, "   this is what it binds to");
                        }
                        if (bound->mStackIndex == -1) {
                            if (!bound->mDefinition) {
                                CfdgError::Error(where, "Error processing shape variable.");
                                return this;
                            }
                            mLocality = PureLocal;
                        } else {
                            mStackIndex = bound->mStackIndex -
                                (isGlobal ? 0 : Builder::CurrentBuilder->mLocalStackDepth);
                            isConstant = false;
                            mLocality = bound->mLocality;
                        }
                        if (arguments && arguments->mType != AST::NoType)
                            CfdgError::Error(arguments->where, "Cannot bind parameters twice");
                        return this;
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
                            
                            return this;
                        }
                        
                        bool isGlobal;
                        const ASTparameter* bound = Builder::CurrentBuilder->findExpression(shapeType, isGlobal);
                        if (bound && bound->mType == RuleType) {
                            argSource = StackArgs;
                            return compile(ph);
                        }
                        
                        if (arguments && arguments->mType == AST::ReuseType) {
                            argSource = ParentArgs;
                            if (typeSignature != parentSignature) {
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
                            return this;
                        }
                        
                        argSize = ASTparameter::CheckType(typeSignature, arguments.get(), where, true);
                        if (argSize < 0) {
                            argSource = NoArgs;
                            return this;
                        }
                        
                        if (arguments && arguments->mType != AST::NoType) {
                            if (arguments->isConstant) {
                                simpleRule = evalArgs();
                                argSource = SimpleArgs;
                                Builder::CurrentBuilder->storeParams(simpleRule);
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
                            Builder::CurrentBuilder->storeParams(simpleRule);
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
        return this;
    }
    
    ASTexpression*
    ASTstartSpecifier::compile(AST::CompilePhase ph)
    {
        std::string name(entropyVal);
        ASTexpression* ret = ASTruleSpecifier::compile(ph);
        entropyVal = std::move(name);   // StartShape only uses name for entropy (grrr)
        assert(ret == this);
        if (mModification) {
            ret = mModification->compile(ph);
            assert(ret == mModification.get());
        }
        return this;
    }
    
    ASTexpression*
    ASTcons::compile(AST::CompilePhase ph)
    {
        switch (ph) {
            case CompilePhase::TypeCheck: {
                bool first = true;
                for (auto& child : children) {
                    Compile(child, ph);
                    if (first) {
                        isConstant = child->isConstant;
                        isNatural = child->isNatural;
                        mLocality = child->mLocality;
                        mType = child->mType;
                    } else {
                        isConstant = isConstant && child->isConstant;
                        isNatural = isNatural && child->isNatural;
                        mLocality = CombineLocality(mLocality, child->mLocality);
                        mType = static_cast<expType>(mType | child->mType);
                    }
                    first = false;
                }
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return this;
    }
    
    ASTexpression*
    ASTreal::compile(AST::CompilePhase ph)
    {
        return this;
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
                    return this;
                }
                
                std::string name = Builder::CurrentBuilder->ShapeToString(stringIndex);

                if (bound->mStackIndex == -1) {
                    assert(bound->mDefinition);
                    ASTexpression* ret = bound->mDefinition->mExpression ?
                        bound->mDefinition->mExpression->constCopy(bound, name) :
                        bound->mDefinition->mChildChange.constCopy(bound, name);
                    if (ret) {
                        ret->compile(ph);
                        return ret;
                    } else {
                        CfdgError::Error(where, "internal error.");
                    }
                } else {
                    if (bound->mType == AST::RuleType) {
                        ASTruleSpecifier* ret = new ASTruleSpecifier(stringIndex, name, where);
                        return ret->compile(ph);
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
        return this;
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
                    return this;
                }
                if (!def && !p) {
                    CfdgError::Error(where, "Name does not match shape name or function name");
                    return this;
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
                    return this;
                }
                
                // if (!def && p)
                ASTruleSpecifier* r = new ASTruleSpecifier(nameIndex, name,
                                                           std::move(arguments),
                                                           where, nullptr);
                return r->compile(CompilePhase::TypeCheck);
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return this;
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
                        if (!def->isConstant) {
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
                
                isConstant = !arguments && definition->isConstant;
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
        return this;
    }
    
    ASTexpression*
    ASToperator::compile(AST::CompilePhase ph)
    {
        Compile(left, ph);
        Compile(right, ph);
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                isConstant = left->isConstant && (right ? right->isConstant : true);
                mLocality = right ? CombineLocality(left->mLocality, right->mLocality) : left->mLocality;
                if (mLocality == PureNonlocal)
                    mLocality = ImpureNonlocal;
                mType = right ? static_cast<expType>(left->mType | right->mType) : left->mType;
                if (strchr("+_*<>LG=n&|X^!", op))
                    isNatural = left->isNatural && (right ? right->isNatural : true);
                
                if (op == '+') {
                    if (mType != FlagType && mType != NumericType)
                        CfdgError::Error(where, "Operands must be numeric or flags");
                } else {
                    if (mType != NumericType)
                        CfdgError::Error(where, "Operand(s) must be numeric");
                }
                if (op == '_' && !isNatural)
                    CfdgError::Error(where, "Proper subtraction operands must be natural");
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return this;
    }
    
    ASTexpression*
    ASTparen::compile(AST::CompilePhase ph)
    {
        if (!e) return this;
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
        return this;
    }
    
    ASTexpression*
    ASTmodTerm::compile(AST::CompilePhase ph)
    {
        Compile(args, ph);
        if (!args) {
            if (modType != param)
                CfdgError::Error(where, "Illegal expression in shape adjustment");
            return this;
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
                            case ASTmodTerm::x:
                            case ASTmodTerm::size:
                            case ASTmodTerm::hue:
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
        return this;
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
                    if ((*term)->modType == ASTmodTerm::alpha ||
                        (*term)->modType == ASTmodTerm::alphaTarg)
                    {
                        flags |= CF_USES_ALPHA;
                    }
                    if ((*term)->modType == ASTmodTerm::param) {
                        if ((*term)->paramString.find("evenodd") != std::string::npos)
                            flags |= CF_EVEN_ODD;
                        if ((*term)->paramString.find("iso") != std::string::npos)
                            flags |= CF_ISO_WIDTH;
                        if ((*term)->paramString.find("join") != std::string::npos)
                            flags &= ~CF_JOIN_MASK;
                        if ((*term)->paramString.find("miterjoin") != std::string::npos)
                            flags |= CF_MITER_JOIN | CF_JOIN_PRESENT;
                        if ((*term)->paramString.find("roundjoin") != std::string::npos)
                            flags |= CF_ROUND_JOIN | CF_JOIN_PRESENT;
                        if ((*term)->paramString.find("beveljoin") != std::string::npos)
                            flags |= CF_BEVEL_JOIN | CF_JOIN_PRESENT;
                        if ((*term)->paramString.find("cap") != std::string::npos)
                            flags &= ~CF_CAP_MASK;
                        if ((*term)->paramString.find("buttcap") != std::string::npos)
                            flags |= CF_BUTT_CAP | CF_CAP_PRESENT;
                        if ((*term)->paramString.find("squarecap") != std::string::npos)
                            flags |= CF_SQUARE_CAP | CF_CAP_PRESENT;
                        if ((*term)->paramString.find("roundcap") != std::string::npos)
                            flags |= CF_ROUND_CAP | CF_CAP_PRESENT;
                        if ((*term)->paramString.find("large") != std::string::npos)
                            flags |= CF_ARC_LARGE;
                        if ((*term)->paramString.find("cw") != std::string::npos)
                            flags |= CF_ARC_CW;
                        if ((*term)->paramString.find("align") != std::string::npos)
                            flags |= CF_ALIGN;
                        continue;
                    }
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
                                (*term)->args.reset(new ASTcons(new ASTreal(d[0], (*term)->where), new ASTreal(d[1], (*term)->where)));
                                (*term)->modType = (*term)->modType == ASTmodTerm::xyz ?
                                ASTmodTerm::x : ASTmodTerm::size;
                                (*term)->argCount = 2;
                                
                                ASTmodTerm::modTypeEnum ztype = (*term)->modType == ASTmodTerm::size ?
                                ASTmodTerm::zsize : ASTmodTerm::z;
                                ASTmodTerm* zmod = new ASTmodTerm(ztype, new ASTreal(d[2], (*term)->where), (*term)->where);
                                zmod->argCount = 1;
                                
                                // Check if xy part is the identity transform and only save it if it is not
                                if (d[0] != 1.0 || d[1] != 1.0 || (*term)->modType == ASTmodTerm::x)
                                    modExp.emplace_back(std::move(*term));
                                modExp.emplace_back(zmod);
                                continue;
                            }
                            
                            if ((*term)->args->size() > 1) {
                                ASTexpression* xyargs = nullptr;
                                int i = 0;
                                for (; i < (*term)->args->size(); ++i) {
                                    xyargs = ASTexpression::Append(xyargs, (*(*term)->args)[i]);
                                    if (xyargs->evaluate(nullptr, 0) >= 2)
                                        break;
                                }
                                if (xyargs && xyargs->evaluate(nullptr, 0) == 2 && i == (*term)->args->size() - 1) {
                                    // We have successfully split the 3-tuple into a 2-tuple and a scalar
                                    ASTexpression* zargs = (*(*term)->args)[i];
                                    (*term)->args->release();
                                    
                                    (*term)->args.reset(xyargs);
                                    (*term)->modType = (*term)->modType == ASTmodTerm::xyz ?
                                    ASTmodTerm::x : ASTmodTerm::size;
                                    (*term)->argCount = 2;
                                    
                                    ASTmodTerm::modTypeEnum ztype = (*term)->modType == ASTmodTerm::size ?
                                    ASTmodTerm::zsize : ASTmodTerm::z;
                                    ASTmodTerm* zmod = new ASTmodTerm(ztype, zargs, (*term)->where);
                                    zmod->argCount = 1;
                                    
                                    double d[2];
                                    if ((*term)->modType != ASTmodTerm::size || !xyargs->isConstant ||
                                        xyargs->evaluate(d, 2) != 2 || d[0] != 1.0 || d[1] != 1.0)
                                    {
                                        // Check if xy part is the identity transform and only save it if it is not
                                        modExp.emplace_back(std::move(*term));
                                    }
                                    modExp.emplace_back(zmod);
                                    continue;
                                }
                            }
                            break;
                        }
                        default:
                            break;
                    }
                    modExp.emplace_back(std::move(*term));
                }

                isConstant = true;
                mLocality = modExp.empty() ? PureLocal : modExp.front()->mLocality;
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
        return this;
    }
    
    ASTexpression*
    ASTarray::compile(AST::CompilePhase ph)
    {
        Compile(mArgs, ph);
        if (!mArgs) {
            CfdgError::Error(where, "Illegal expression in array accessor");
            return this;
        }
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                if (!mArgs || mArgs->mType != AST::NumericType) {
                    CfdgError::Error(where, "Array arguments must be numeric");
                    isConstant = mConstData = false;
                    return this;
                }
                
                bool isGlobal;
                const ASTparameter* bound = Builder::CurrentBuilder->findExpression(mName, isGlobal);
                assert(bound);
                
                isConstant = bound->mStackIndex == -1;
                isNatural = bound->isNatural;
                mType = bound->mType;
                mConstData = isConstant;
                mStackIndex = bound->mStackIndex -
                    (isGlobal ? 0 : Builder::CurrentBuilder->mLocalStackDepth);
                mCount = mType == NumericType ? bound->mTuplesize : 1;
                isParameter = bound->isParameter;
                
                mLocality = CombineLocality(bound->mLocality, mArgs->mLocality);
                mArgs->entropy(entString);
                mConstData = mConstData && bound->mDefinition->mExpression->evaluate(mData, 9) > 0;
                
                if ((*mArgs)[0]->evaluate(nullptr, 0) == 1) {
                    exp_ptr args(std::move(mArgs));
                    mArgs.reset((*args)[0]);
                    if (!args->release(0)) {
                        args.release();
                        args.reset(new ASTexpression(mArgs->where)); // replace with dummy
                    }
                    double data[2];
                    int count = 0;
                    for (int i = 1; i < args->size(); ++i) {
                        if (!(*args)[i]->isConstant) {
                            CfdgError::Error((*args)[i]->where, "Array argument is not constant");
                            break;
                        }
                        int num = (*args)[i]->evaluate(data + count, 2 - count);
                        if (num <= 0) {
                            CfdgError::Error((*args)[i]->where, "Error evaluating array arguments");
                            break;
                        }
                        count += num;
                    }
                    switch (count) {
                        case 2:
                            mStride = static_cast<int>(data[1]);  // fall through
                        case 1:
                            mLength = static_cast<int>(data[0]);  // fall through
                        case 0:
                            break;
                            
                        default:
                            CfdgError::Error(args->where, "Unexpected number of array arguments");
                            break;
                    }
                } else if (mArgs->isConstant) {
                    double data[3];
                    switch (mArgs->evaluate(data, 3)) {
                        case 3:
                            mStride = static_cast<int>(data[2]);
                            // fall through
                        case 2:
                            mLength = static_cast<int>(data[1]);
                            // fall through
                        case 1:
                            mArgs.reset(new ASTreal(data[0], mArgs->where));
                            break;
                            
                        default:
                            CfdgError::Error(mArgs->where, "Error evaluating array arguments");
                            break;
                    }
                } else {
                    if (mArgs->evaluate(nullptr, 0) != 1)
                        CfdgError::Error(mArgs->where, "Array length & stride arguments must be contant");
                }
                if (mStride < 0 || mLength < 0)
                    CfdgError::Error(mArgs->where, "Array length & stride arguments must be positive");
                if (mStride * (mLength - 1) >= mCount)
                    CfdgError::Error(mArgs->where, "Array length & stride arguments too large for source");
                
                isConstant = isConstant && mArgs->isConstant;
                mLocality = CombineLocality(mLocality, mArgs->mLocality);
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
        return this;
    }
    
    void
    ASTmodification::evalConst() 
    {
        const std::map<ASTmodTerm::modTypeEnum, int> ClassMap = {
            {ASTmodTerm::unknownType,   ASTmodification::NotAClass},
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
            bool keepThisOne = false;
            if (!mod) {
                CfdgError::Error(where, "Unknown term in shape adjustment");
                continue;
            }
            
            // Put in code for separating color changes and target color changes
                        
			int mc = ClassMap.at(mod->modType);
			modClass |= mc;
            if (!mod->isConstant)
                nonConstant |= mc;
            bool justCheck = (mc & nonConstant) != 0;
            
            try {
                mod->evaluate(modData, &strokeWidth, justCheck, entropyIndex, false, nullptr);
            } catch (DeferUntilRuntime&) {
                keepThisOne = true;
            }
            
            if (justCheck || keepThisOne) {
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
    
    unsigned
    ASTselect::getIndex(RendererAST* rti) const
    {
        if (indexCache)
            return indexCache;

        double select = 0.0;
        (*arguments)[0]->evaluate(&select, 1, rti);

        if (ifSelect)
            return select ? 1 : 2;

        int i = static_cast<int>(select) + 1;

        if (i <= 0)
            return 1;
        if (i > arguments->size())
            return arguments->size() - 1;
        return i;
    }
}

