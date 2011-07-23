// astexpression.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2009 John Horigan - john@glyphic.com
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

#include <math.h>
#include <typeinfo>
#include <cassert>

namespace AST {
    
    
    
    // Make sure that this stays in sync with the FuncType enum!
    const char* ASTfunction::FuncNames[ASTfunction::LastOne] = 
    {
        "cos", "sin", "tan", "cot", 
        "acos", "asin", "atan", "acot", 
        "cosh", "sinh", "tanh", 
        "acosh", "asinh", "atanh", 
        "log", "log10", "sqrt", "exp", "abs", "floor", "infinity", 
        "factorial", "sg",
        "atan2", "mod", "divides", "div", "min", "max", "ftime", "frame",
        "rand_static", "rand", "rand+/-", "randint"
    };
    
    int ASTmodification::ModClass[ASTmodTerm::lastModType] = {  
        ASTmodification::NotAClass,                                 // unknown
        ASTmodification::GeomClass | ASTmodification::PathOpClass,  // x
        ASTmodification::GeomClass | ASTmodification::PathOpClass,  // y
        ASTmodification::ZClass,                                    // z
        ASTmodification::GeomClass,                                 // transform
        ASTmodification::GeomClass,                                 // size
        ASTmodification::GeomClass | ASTmodification::PathOpClass,  // rot
        ASTmodification::GeomClass,                                 // skew
        ASTmodification::GeomClass, ASTmodification::ZClass,        // flip, zsize
        ASTmodification::NotAClass,                                 // Entropy
        ASTmodification::HueClass, ASTmodification::SatClass,       // hue, ...
        ASTmodification::BrightClass, ASTmodification::AlphaClass, 
        ASTmodification::HueClass, ASTmodification::SatClass,       // hue|, ...
        ASTmodification::BrightClass, ASTmodification::AlphaClass, 
        ASTmodification::HueTargetClass, ASTmodification::SatTargetClass, // |hue, ...
        ASTmodification::BrightTargetClass, ASTmodification::AlphaTargetClass,
        ASTmodification::TimeClass, ASTmodification::TimeClass,     // time, timescale
        ASTmodification::StrokeClass, ASTmodification::ParamClass,  // stroke, param
        ASTmodification::PathOpClass, ASTmodification::PathOpClass, // x1, y1
        ASTmodification::PathOpClass, ASTmodification::PathOpClass, // x2, y2
        ASTmodification::PathOpClass, ASTmodification::PathOpClass, // xrad, yrad
        -1                                                          // modification
    };
    
    // These random strings are courtesy of http://www.fourmilab.ch/hotbits/
    const char* ASTmodTerm::Entropies[ASTmodTerm::lastModType] = {
        "",                                                     // unknown
        "\x95\xE7\x48\x5E\xCC\x06",                             // x
        "\x84\x2B\xF3\xBB\x93\x59",                             // y
        "\xC8\x3A\x12\x32\x36\x71",                             // z
        "\x88\x90\x54\xC5\xD3\x20",                             // transform
        "\x64\xEC\x5B\x4B\xEE\x2B",                             // size
        "\x84\xB0\x92\x26\x59\xE2",                             // rot
        "\xFF\x2D\x84\x01\xA0\x0A",                             // skew
        "\x43\x5A\x17\xEA\x12\x05", "\x64\xEC\x5B\x4B\xEE\x2B", // flip, zsize
        "",                                                     // Entropy
        "\x02\xDE\x2B\x2C\x25\xA1", "\x18\x4F\xCF\x04\x3F\xE5", // hue, ...
        "\x1F\x3F\xEB\xA2\xA2\x7E", "\xB4\xFF\x9E\x45\xEE\x7E",
        "\xAF\xE5\x58\x33\x20\xF8", "\x98\x80\xED\x44\x2F\xF2", // hue|, ...
        "\x68\xD6\xCB\x8A\x96\x20", "\x24\x4C\xCC\x41\x09\xC7",
        "\xDB\x3F\xA1\xDA\xE7\x45", "\xDA\x75\x13\xD3\x30\xEA", // |hue, ...
        "\x8F\x01\x2B\x75\xC3\x25", "\xE7\xCD\x5E\xE3\x88\xF4",
        "\x20\xC6\xE8\x02\xED\x27", "\x78\x8E\xC8\x2C\x1C\x96", // time, timescale
        "", "",                                                 // stroke, param
        "", "",                                                 // x1, y1
        "", "",                                                 // x2, y2
        "", "",                                                 // xrad, yrad
        "\x88\x90\x54\xC5\xD3\x20"                              // modification
    };
    
    const char* ASTfunction::Entropies[ASTfunction::LastOne] = {
        "\xA1\xE7\x9C\x1A\xAF\x7D",     // Cos
        "\xAF\x58\xFE\x2C\xD4\x53",     // Sin
        "\x95\xFF\x59\x11\x03\x02",     // Tan
        "\x77\xF5\xB6\x35\x8C\xF0",     // Cot
        "\x3A\xCD\x79\x3E\xAD\xB4",     // Acos
        "\x1D\x75\x0B\xBC\x5F\x52",     // Asin
        "\x0B\xC8\x89\xAB\xF8\xB7",     // Atan
        "\x69\x7C\xC7\x1A\xF6\x7B",     // Acot
        "\x48\x43\x43\x35\x62\x81",     // Cosh
        "\x51\x62\xFB\x76\xED\x9C",     // Sinh
        "\xBB\x91\x54\xA9\x63\x84",     // Tanh
        "\x4F\x28\x48\x20\xB7\x5C",     // Acosh
        "\x6C\x9B\x32\xAA\x4C\xD0",     // Asinh
        "\x58\xEC\xBB\x25\xF8\xB6",     // Atanh
        "\x8E\xB8\x62\xA1\x75\x0F",     // Log
        "\x4A\x6C\xA3\x02\x8B\x80",     // Log10
        "\x86\x7C\xFC\x20\xCB\x97",     // Sqrt
        "\x88\xA8\x65\xF0\xC1\x06",     // Exp
        "\x41\x89\x18\xD1\xAD\x82",     // Abs
        "\xB7\x28\xD7\xD7\xA3\xCC",     // Floor
        "\x2C\x28\x50\xCC\xDE\x44",     // Infinity
        "\x19\xD7\x83\x29\x47\x99",     // Factorial
        "\xB7\x05\x28\xBA\xCD\x2E",     // Sg
        "\x99\x1B\xC9\xE0\x3F\xA4",     // Atan2
        "\x78\x8E\xC8\x2C\x1C\x96",     // Divides
        "\x64\xEC\x5B\x4B\xEE\x2B",     // Div
        "\x0F\xE3\xFE\x5F\xBF\xBF",     // Mod
        "\xA2\x42\xA3\x49\xB1\x19",     // Min
        "\xD3\x55\x5C\x0D\xD8\x51",     // Max
        "\x4F\xBE\xA1\x06\x80\x06",     // Ftime
        "\x90\x70\x6A\xBB\xBA\xB0",     // Frame
        "\xC8\xF7\xE5\x3E\x05\xA3",     // Rand_Static
        "\xDA\x18\x5B\xE2\xDB\x79",     // Rand
        "\xDC\x8D\x09\x15\x8A\xC4",     // Rand2
        "\x48\x14\x4E\x27\x35\x2E"      // RandInt
    };
    
    ASTruleSpecifier ASTruleSpecifier::Zero;
    
    bool ASTparameter::Impure = false;
    
    double CFatof(const char* s)
    {
        double ret = atof(s);
        return strchr(s, '%') ? ret / 100.0 : ret;
    }
    
    void
    ASTparameter::init(int nameIndex, ASTdefine* def)
    {
        mType = def->mType;
        isLocal = !def->mExpression || def->mExpression->isLocal;
        mTuplesize = def->mTuplesize;
        
        if (mType == ASTexpression::NumericType) {
            isNatural = def->mExpression->isNatural && mTuplesize == 1;
            if (mTuplesize == 0) mTuplesize = 1;    // loop index
            if (mTuplesize < 1 || mTuplesize > 8)
                CfdgError::Error(mLocation, "Illegal vector size (<1 or >8)");
        }
        
        mName = nameIndex;
        mDefinition = def->isConstant ? def : 0;
    }
    
    void
    ASTparameter::init(const std::string& typeName, int nameIndex)
    {
        isLocal = false;
        if (typeName == "number") {
            mType = ASTexpression::NumericType;
        } else if (typeName == "natural") {
            mType = ASTexpression::NumericType;
            isNatural = true;
        } else if (typeName == "adjustment") {
            mTuplesize = ModificationSize;
            mType = ASTexpression::ModType;
        } else if (typeName == "shape") {
            mType = ASTexpression::RuleType;
            mTuplesize = 1;
        } else if (strncmp(typeName.data(), "vector", 6) == 0 && 
                   typeName.length() == 7 &&
                   isdigit(typeName[6]))
        {
            mType = ASTexpression::NumericType;
            mTuplesize = typeName[6] - '0';
            if (mTuplesize < 1 || mTuplesize > 8)
                CfdgError::Error(mLocation, "Illegal vector size (<1 or >8)");
        } else mType = ASTexpression::NoType;
        
        mName = nameIndex;
        mDefinition = 0;
    }
    
    void
    ASTparameter::check(const yy::location& typeLoc, const yy::location& nameLoc) 
    { 
        if (mType == ASTexpression::NoType)
            CfdgError::Error(typeLoc, "Unknown parameter type");
        if (mName == -1)
            CfdgError::Error(nameLoc, "Reserved keyword used for parameter name");
    }
    
    bool
    ASTparameter::operator!=(const ASTparameter& p) const
    {
        if (mType != p.mType) return true;
        if (mType == ASTexpression::NumericType && 
            mTuplesize != p.mTuplesize) return true;
        return false;
    }
    
    bool
    ASTparameter::operator!=(const ASTexpression& e) const
    {
        if (mType != e.mType) return true;
        if (mType == ASTexpression::NumericType && 
            mTuplesize != e.evaluate(0, 0)) return true;
        return false;
    }
    
    int
    ASTparameter::CheckType(const ASTparameters* types, const ASTparameters* parent, 
                            const ASTexpression* args, const yy::location& where)
    {
        // Walks down the right edge of an expression tree checking that the types
        // of the children match the specified argument types
        if ((types == NULL || types->empty()) && (args == NULL)) return 0;
        if (types == NULL && args && Builder::CurrentBuilder->mCompilePhase == 1) {
            Builder::CurrentBuilder->mWant2ndPass = true;
            return -1;
        }
        if (types == NULL || types->empty()) {
            CfdgError::Error(args->where, "Arguments are not expected.");
            return -1;
        }
        if (args == NULL) {
            CfdgError::Error(where, "Arguments are expected.");
            return -1;
        }
        bool justCount = args == NULL || args->mType == ASTexpression::NoType;
        
        int count = 0;
        ASTexpression::const_iterator arg = args->begin(), arg_end = args->end();
        ASTparameters::const_iterator param_it = types->begin(), 
        param_end = types->end();
        
        while (param_it != param_end) {
            if (!justCount && arg == arg_end) {
                CfdgError::Error(args->where, args ? "Not enough arguments" : "arguments expected");
                return -1;
            }
            if (!justCount && param_it->mType != arg->mType) {
                CfdgError::Error(arg->where, "Incorrect argument type.");
                CfdgError::Error(param_it->mLocation, "This is the expected type.");
                return -1;
            }
            if (!justCount && param_it->isNatural && !arg->isNatural && !ASTparameter::Impure) {
                CfdgError::Error(arg->where, "this expression does not satisfy the natural number requirement");
                return -1;
            }
            while (!justCount && param_it->mType == ASTexpression::NumericType &&
                   !param_it->isNatural && !ASTparameter::Impure)
            {
                if (arg->isLocal) break;
                const ASTvariable* v = dynamic_cast<const ASTvariable*> (&*arg);
                if (v && v->isParameter)
                    break;
                CfdgError::Error(arg->where, "this expression does not satisfy the number parameter requirement");
                return -1;
            }
            count += param_it->mTuplesize;
            
            ++arg;
            ++param_it;
        }
        
        if (arg != arg_end) {
            CfdgError::Error(arg._Ptr->where, "Too many arguments.");
            return -1;
        }
        
        if (justCount && types != parent) {
            if (parent == NULL) {
                CfdgError::Error(where, "Parameter reuse not allowed in this context.");
                return -1;
            }
            param_it = types->begin();
            ASTparameters::const_iterator parent_it = parent->begin();
            while (param_it != types->end()) {
                if (parent_it == parent->end() || *param_it != *parent_it) {
                    CfdgError::Error(where, "Parameter reuse only allowed when type signature is identical.");
                    return -1;
                }
                ++param_it;
                ++parent_it;
            }
        }
        
        return count;
    }
    
    ASTfunction::ASTfunction(const std::string& func, exp_ptr args, Rand64& r,
                             const yy::location& nameLoc, const yy::location& argsLoc)
    : ASTexpression(nameLoc + argsLoc, true, false, NumericType), 
      functype(NotAFunction), arguments(NULL)
    {
        if (&func == 0 || func.empty()) {
            CfdgError::Error(nameLoc, "bad function call");
            return;
        }
        
        isConstant = args.get() ? args->isConstant : true;
        isLocal = args.get() && args->isLocal;
        int argcount = args.get() ? args->evaluate(0, 0) : 0;
        
        functype = GetFuncType(func);
        
        if (functype == NotAFunction) {
            CfdgError::Error(nameLoc, "Unknown function");
            return;
        }
        
        if (functype == ASTfunction::Infinity && argcount == 0) {
            arguments = new ASTreal(1.0, argsLoc);
            return;
        }
        
        if (functype == Ftime) {
            if (args.get())
                CfdgError::Error(argsLoc, "ftime() function takes no arguments");
            isConstant = false;
            isLocal = true;
            arguments = new ASTreal(1.0, argsLoc);
            return;
        }
        
        if (functype == Frame) {
            if (args.get())
                CfdgError::Error(argsLoc, "frame() functions takes no arguments");
            isConstant = false;
            isLocal = false;
            arguments = new ASTreal(1.0, argsLoc);
            return;
        }
        
        if (functype >= Rand_Static && functype <= RandInt) {
            if (functype == Rand_Static) {
                random = r.getDouble();
            } else {
                isConstant = false;
            }
            
            switch (argcount) {
                case 0:
                    args.reset(new ASTcons(new ASTreal(0.0, argsLoc), new ASTreal(1.0, argsLoc)));
                    break;
                case 1:
                    args.reset(new ASTcons(new ASTreal(0.0, argsLoc), args.release()));
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

            arguments = args.release();
            if (functype == RandInt)
                isNatural = arguments->isNatural;
            return;
        }
        
        if (functype == Abs) {
            if (argcount < 1 || argcount > 2) {
                CfdgError::Error(argsLoc, "function takes one or two arguments");
            }
        } else if (functype < Atan2) {
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
        arguments = args.release();
        if (functype == Mod || functype == Abs || functype == Min || functype == Max)
            isNatural = arguments->isNatural;
        if (functype == Factorial || functype == Sg || functype == Div || functype == Divides) {
            if (!arguments->isNatural)
                CfdgError(arguments->where, "function is defined over natural numbers only");
            isNatural = true;
        }
    }
    
    ASTfunction::FuncType
    ASTfunction::GetFuncType(const std::string& func) 
    {
        for (int i = 0; i < LastOne; ++i)
            if (func.compare(FuncNames[i]) == 0) {
                return (FuncType)i;
            }
        
        return NotAFunction;
    }
    
    ASTruleSpecifier::ASTruleSpecifier(int t, const std::string& name, exp_ptr args, 
                                       const yy::location& loc, const ASTparameters* types,
                                       const ASTparameters* parent)
    : ASTexpression(loc, args.get() == NULL || args->isConstant, false, RuleType), 
      shapeType(t), entropyVal(name), argSource(DynamicArgs),
      arguments(args.release()), simpleRule(0), mStackIndex(0), typeSignature(types)
    {
        if (types && types->empty()) {
            types = NULL;
            typeSignature = NULL;
        }
        if (parent && parent->empty())
            parent = NULL;
        argSize = ASTparameter::CheckType(types, parent, arguments, loc);
        if (argSize < 0) return;
            
        if (arguments && arguments->mType != ASTexpression::NoType) {
            arguments->entropy(entropyVal);
            if (arguments->isConstant) {
                const StackType* simp = evalArgs();
                simp[0].ruleHeader.mRefCount = StackRule::MaxRefCount;
                simpleRule = simp;
                argSource = SimpleArgs;
            } else {
                arguments = arguments->simplify();
            }
        } else if (arguments && arguments->mType == ASTexpression::NoType) {
            argSource = ParentArgs;
        } else {
            argSource = NoArgs;
            simpleRule = StackType::alloc(shapeType, 0, types);
            simpleRule[0].ruleHeader.mRefCount = StackRule::MaxRefCount;
        }
    }
    
    ASTruleSpecifier::ASTruleSpecifier(const std::string& name, const yy::location& loc, 
                                       int stackIndex)
    : ASTexpression(loc, false, false, RuleType), shapeType(0), argSize(0), 
      entropyVal(name), argSource(StackArgs),
      arguments(0), simpleRule(0), mStackIndex(stackIndex), typeSignature(0)
    {
    }
    
    ASTruleSpecifier::ASTruleSpecifier(const ASTruleSpecifier* r, 
                                       const std::string& name, 
                                       const yy::location& loc)
    : ASTexpression(loc, false, false, RuleType), shapeType(r->shapeType), argSize(r->argSize), 
      entropyVal(name), argSource(NoArgs), arguments(0), simpleRule(0), mStackIndex(0),
      typeSignature(r->typeSignature)
    {
        if (r->argSource == SimpleArgs) {
            StackType* simp = StackType::alloc(shapeType, argSize, 0);
            argSource = SimpleArgs;
            simpleRule = simp;
            if (argSize)
                for (int i = 1; i < argSize + 2; ++i)
                    simp[i] = r->simpleRule[i];
            return;
        }
        assert(r->argSource == NoArgs);   // only duplicate constant rule specs
    }
    
    ASTruleSpecifier::ASTruleSpecifier(ASTruleSpecifier& r)
    : ASTexpression(r.where, r.isConstant, false, r.mType), shapeType(r.shapeType),
      argSize(r.argSize), entropyVal(r.entropyVal), argSource(r.argSource),
      arguments(r.arguments), simpleRule(r.simpleRule), mStackIndex(r.mStackIndex),
      typeSignature(r.typeSignature)
    {
        r.arguments = NULL;     // move semantics
        r.simpleRule = NULL;
    }
    
    const StackType*
    ASTruleSpecifier::evalArgs(Renderer* rti, const StackType* parent) const
    {
        switch (argSource) {
        case NoArgs:
        case SimpleArgs:
            return simpleRule;
        case StackArgs: {
            const StackType* stackItem = (mStackIndex < 0) ? rti->mLogicalStackTop + mStackIndex :
                &(rti->mCFstack[mStackIndex]);
            stackItem->rule->retain(rti);
            return stackItem->rule;
        }
        case ParentArgs:
            assert(parent);
            assert(rti);
            parent->retain(rti);
            return parent;
        case DynamicArgs: {
            StackType* ret = StackType::alloc(shapeType, argSize, typeSignature);
            ret->evalArgs(rti, arguments, parent);
            return ret;
        }
        default:
            assert(false);
            return NULL;
        }
    }
    
    const StackType*
    ASTselect::evalArgs(Renderer* rti, const StackType* parent) const
    {
        if (mType != RuleType) {
            CfdgError::Error(where, "Evaluation of a non-shape select() in a shape context");
            return NULL;
        }
        
        return choices[getIndex(rti)]->evalArgs(rti, parent);
    }
    
    ASTexpression*
    ASTcons::Cons(ASTexpression* l, ASTexpression* r)
    {
        if (l && r) return new ASTcons(l, r);
        return l ? l : r;
    }
    
    ASTexpression*
    ASToperator::Op(char op, ASTexpression* l, ASTexpression* r)
    {
        if (l && r) return new ASToperator(op, l, r);
        return l ? l : r;
    }
    
    ASToperator::ASToperator(char o, ASTexpression* l, ASTexpression* r)
    : ASTexpression(r ? (l->where + r->where) : l->where), op(o), left(l), right(r) 
    {
        isConstant = r ? r->isConstant && l->isConstant : l->isConstant;
        isLocal = r ? r->isLocal && l->isLocal : l->isLocal;
        mType = r ? (expType)(l->mType | r->mType) : l->mType;
        if (strchr("+_*<>LG=n&|X^", o))
            isNatural = r ? (l->isNatural && r->isNatural) : l->isNatural;
    }
    
    ASTmodTerm::ASTmodTerm(ASTmodTerm::modTypeEnum t, ASTexpression* a, const yy::location& loc)
    : ASTexpression(loc, a->isConstant, false, ModType), modType(t), args(a)
    {
        if (a->mType == ASTexpression::RuleType)
            CfdgError::Error(loc, "Illegal expression in shape adjustment");
        
        if (a->mType == ASTexpression::ModType) {
            if (t != ASTmodTerm::transform)
                CfdgError::Error(loc, "Cannot accept a transform expression here");

            modType = ASTmodTerm::modification;
        }
    }
    
    ASTmodification::ASTmodification(const ASTmodification& m, const yy::location& loc)
    : ASTexpression(loc, true, false, ModType), modData(m.modData), modExp(0), 
      modClass(m.modClass)
    {
        assert(m.modExp.empty());
    };
    
    ASTselect::ASTselect(exp_ptr args, const yy::location& loc)
    : ASTexpression(loc), selector(NULL), tupleSize(-1), weakPointer(NULL),
      indexCache(0), arguments(NULL)
    {
        isNatural = args->mType == NumericType;
        isLocal = args->isLocal;
        args->entropy(ent);
        ent.append("\xB5\xA2\x4A\x74\xA9\xDF");
        
        arguments = args.release()->simplify();
        ASTexpression::iterator arg = arguments->begin(), arg_end = arguments->end();
        
        if (arg == arg_end) {
            CfdgError::Error(loc, "select() function requires at least two arguments");
            return;
        }
        
        if (arg->mType != NumericType || arg->evaluate(0, 0) != 1) {
            CfdgError::Error(arg->where, "select() selector must be a numeric 1-tuple");
            return;
        }
        
        selector = &*arg;
        ++arg;
        if (selector->isConstant) {
            indexCache = getIndex();
            selector = NULL;
        }
        
        bool firstOne = true;
        while (arg != arg_end) {
            choices.push_back(&*arg);
            
            if (firstOne) {
                mType = arg->mType;
                tupleSize = (mType == NumericType) ? arg->evaluate(0, 0) : 1;
                if (tupleSize > 1) isNatural = false;
                firstOne = false;
                if (tupleSize == -1)
                    CfdgError::Error(arg->where, "Error determining tuple size");
            } else {
                if (mType != arg->mType)
                    CfdgError::Error(arg->where, "select() choices must be of same type");
                else if (mType == NumericType && tupleSize != -1 && 
                         arg->evaluate(0, 0) != tupleSize)
                    CfdgError::Error(arg->where, "select() choices must be of same length");
            }
            isNatural = isNatural && arg->isNatural;
            ++arg;
        }
        
        if (firstOne) {
            CfdgError::Error(loc, "select() function requires at least two arguments");
        }
        
        if (selector->isConstant) {
            isConstant = choices[getIndex()]->isConstant;
            isLocal = choices[getIndex()]->isLocal;
        }
    }
    
    ASTruleSpecifier::~ASTruleSpecifier()
    {
        delete[] simpleRule;
        delete arguments;
    };
    
    ASTselect::~ASTselect()
    {
        selector = NULL;
        choices.clear();
        delete arguments;
    }
    
    ASTmodification::~ASTmodification()
    {
        for (ASTexpArray::iterator it = modExp.begin(); it != modExp.end(); ++it)
            delete (*it);
        modExp.clear();
    }
    
    void
    ASTmodification::init(exp_ptr mods, const std::string& name,
                          std::string* p, double* width) throw (CfdgError)
    {
        std::string entString;
        if (mods.get())
            mods->entropy(entString);
        entString.append(name);
        ASTexpression* ent = new ASTmodTerm(ASTmodTerm::Entropy, entString, where);

        if (mods.get()) {
            mods.reset(new ASTcons(mods.release()->simplify(), ent));
        } else {
            mods.reset(ent);
        }
        evalConst(mods, p, width);
    }
    
    void
    ASTmodification::init(exp_ptr mods, std::string* p, double* width) throw (CfdgError)
    {
        static const std::string defaultEntropy("it doesn't matter");
        init(mods, defaultEntropy, p, width);
    }
    
    static void Addmod(exp_ptr& var, ASTexpression* mod)
    {
        if (mod == NULL) return;
        if (var.get()) {
            ASToperator* e = new ASToperator('+', var.release(), mod);
            var.reset(e);
        } else {
            var.reset(mod);
        }
    }
    
    static void Setmod(term_ptr& mod, ASTmodTerm* newmod, ASTexpArray& dropped)
    {
        if (mod.get()) dropped.push_back(mod.release());
        mod.reset(newmod);
    }
    
    ASTexpression*
    ASToperator::MakeCanonical(ASTexpArray& temp)
    // Receive a vector of modification terms and return an ASTexpression with
    // those terms rearranged into TRSSF canonical order. Duplicate terms are left
    // in the input vector.
    {
        ASTexpArray dropped;
        
        try {
            exp_ptr var;
            exp_ptr result;
            
            term_ptr x;
            term_ptr y;
            term_ptr z;
            term_ptr rot;
            term_ptr skew;
            term_ptr size;
            term_ptr zsize;
            term_ptr flip;
            term_ptr transform;
            
            for (ASTexpArray::iterator it = temp.begin(); it != temp.end(); ++it) {
                if ((*it)->mType != ModType) {
                    CfdgError::Error((*it)->where, "Non-adjustment in shape adjustment context");
                    delete (*it);
                    *it = 0;
                    continue;
                }
                
                ASTmodTerm* mod = dynamic_cast<ASTmodTerm*> (*it);
                if (mod == 0) {
                    CfdgError::Error((*it)->where, "Unknown term in shape adjustment");
                    delete (*it);
                    *it = 0;
                    continue;
                }
                *it = 0;
                
                int argcount = 0;
                if (mod->args && mod->args->mType == NumericType)
                    argcount = mod->args->evaluate(0, 0);
                
                switch (mod->modType) {
                    case ASTmodTerm::x:
                        Setmod(x, mod, dropped);
                        if (argcount > 1) {
                            y.reset();
                        }
                        break;
                    case ASTmodTerm::y:
                        Setmod(y, mod, dropped);
                        break;
                    case ASTmodTerm::z:
                        Setmod(z, mod, dropped);
                        break;
                    case ASTmodTerm::modification:
                    case ASTmodTerm::transform:
                        Setmod(transform, mod, dropped);
                        break;
                    case ASTmodTerm::rot:
                        Setmod(rot, mod, dropped);
                        break;
                    case ASTmodTerm::size:
                        Setmod(size, mod, dropped);
                        break;
                    case ASTmodTerm::zsize:
                        Setmod(zsize, mod, dropped);
                        break;
                    case ASTmodTerm::skew:
                        Setmod(skew, mod, dropped);
                        break;
                    case ASTmodTerm::flip:
                        Setmod(flip, mod, dropped);
                        break;
                    default:
                        Addmod(var, mod);
                        break;
                }
            }
            
            temp.clear();
            temp.swap(dropped);
            
            // If x and y are provided then merge them into a single (x,y) modification
            if (x.get() && y.get() && x->args->evaluate(0, 0) == 1 && y->args->evaluate(0, 0) == 1) {
                x->args = new ASTcons(x->args, y->args);
                y->args = 0;
                y.reset();
            }
            
            Addmod(result, x.release());
            Addmod(result, y.release());
            Addmod(result, z.release());
            Addmod(result, rot.release());
            Addmod(result, size.release());
            Addmod(result, zsize.release());
            Addmod(result, skew.release());
            Addmod(result, flip.release());
            Addmod(result, transform.release());
            Addmod(result, var.release());
            
            return result.release();
        } catch (...) {
            for (ASTexpArray::iterator it = temp.begin(); it != temp.end(); ++it) 
                delete (*it);
            for (ASTexpArray::iterator it = dropped.begin(); it != dropped.end(); ++it) 
                delete (*it);
            temp.clear();
            dropped.clear();
            throw;
        }
    }
    
    // Evaluate a cons tree to see how many reals it has and optionally
    // copy them to an array
    int
    ASTcons::evaluate(double* res, int length, Renderer* rti) const
    {
        if (mType != NumericType) {
            CfdgError::Error(where, "Non-numeric expression in a numeric context");
            return -1;
        }
        int leftnum = left->evaluate(res, length, rti);
        if (leftnum <= 0) 
            return -1;
        
        if (res) 
            res += leftnum;
        
        int rightnum = right ? (right->evaluate(res, length - leftnum, rti)) : 0;
        if (rightnum <= 0) 
            return -1;
        
        return leftnum + rightnum;
    }
    
    int
    ASTreal::evaluate(double* res, int length, Renderer*) const
    {
        if (res && length < 1)
            return -1;
        if (res) 
            *res = value;
        return 1;
    }
    
    int
    ASTvariable::evaluate(double* res, int length, Renderer* rti) const
    {
        if (mType != NumericType) {
            CfdgError::Error(where, "Non-numeric variable in a numeric context");
            return -1;
        }
        if (res && (length < count))
            return -1;
        if (res) {
            if (rti == NULL) throw DeferUntilRuntime();
            const StackType* stackItem = (stackIndex < 0) ? rti->mLogicalStackTop + stackIndex :
                &(rti->mCFstack[stackIndex]);
            for (int i = 0; i < count; ++i)
                res[i] = stackItem[i].number;
        }
        
        return count;
    }
    
    int
    ASToperator::evaluate(double* res, int length, Renderer* rti) const
    {
        double l = 0.0;
        double r = 0.0;
        
        if (res && length < 1)
            return -1;
        
        if (mType == FlagType && op == '+') {
            if (left->evaluate(res ? &l : 0, 1, rti) != 1)
                return -1;
            if (!right || right->evaluate(res ? &r : 0, 1, rti) != 1)
                return -1;
            int f = (int)l | (int)r;
            if (res)
                *res = (double)f;
            return 1;
        }
        
        if (mType != NumericType) {
            CfdgError::Error(where, "Non-numeric expression in a numeric context");
            return -1;
        }
        
        if (left->evaluate(res ? &l : 0, 1, rti) != 1) {
            CfdgError::Error(left->where, "illegal operand");
            return -1;
        }
        
        int rightnum = right ? right->evaluate(res ? &r : 0, 1, rti) : 0; 
        
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
                    *res = (l && r) ? 1.0 : 0.0;
                    break;
                case '|':
                    *res = (l || r) ? 1.0 : 0.0;
                    break;
                case 'X':
                    *res = (l && !r || !l && r) ? 1.0 : 0.0;
                    break;
                case '^':
                    *res = pow(l, r);
                    if (isNatural && *res < 9007199254740992.) {
                        uint64_t pow = 1;
                        uint64_t il = (uint64_t)l;
                        uint64_t ir = (uint64_t)r;
                        while (ir) {
                            if (ir & 1) pow *= il;
                            il *= il;
                            ir >>= 1;
                        }
                        *res = (double)pow;
                    }
                    break;
                default:
                    return -1;
            }
        } else {
            if (strchr("+-*/^_<>LG=n&|X", op) == 0)
                return -1;
        }
        
        return 1;
    }
    
    static double MinMax(const ASTexpression* e, Renderer* rti, bool isMin)
    {
        const ASTcons* c = dynamic_cast<const ASTcons*> (e);
        if (c) {
            double l = MinMax(c->left, rti, isMin);
            double r = MinMax(c->right, rti, isMin);
            bool leftMin = l < r;
            return ((isMin && leftMin) || (!isMin && !leftMin)) ? l : r;
        }
        double v = 0.0;
        e->evaluate(&v, 1, rti);
        return v;
    }
    
    int 
    ASTfunction::evaluate(double* res, int length, Renderer* rti) const
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
            *res = MinMax(arguments, rti, functype == Min);
            return 1;
        }
        
        double a[2];
        int count = arguments->evaluate(a, 2, rti);
        // no need to check the argument count, the constructor already checked it
        
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
            case Atan2: 
                *res = atan2(a[0], a[1]) * 57.29577951308;
                break;
            case Mod: 
                if (arguments->isNatural)
                    *res = (double)((uint64_t)a[0] % (uint64_t)a[1]);
                else
                    *res = fmod(a[0], a[1]);
                break;
            case Divides:
                *res = ((uint64_t)a[0] % (uint64_t)a[1]) == (uint64_t)0 ? 1.0 : 0.0;
                break;
            case Div:
                *res = (double)((uint64_t)a[0] / (uint64_t)a[1]);
                break;
            case Floor:
                *res = floor(a[0]);
                break;
            case Ftime:
                if (rti == NULL) throw DeferUntilRuntime();
                *res = rti->mCurrentTime;
                break;
            case Frame:
                if (rti == NULL) throw DeferUntilRuntime();
                *res = rti->mCurrentFrame;
                break;
            case Rand_Static: 
                *res = random * fabs(a[1] - a[0]) + fmin(a[0], a[1]);
                break;
            case Rand: 
                if (rti == NULL) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = rti->mCurrentSeed.getDouble() * fabs(a[1] - a[0]) + fmin(a[0], a[1]);
                break;
            case Rand2: 
                if (rti == NULL) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = (rti->mCurrentSeed.getDouble() * 2.0 - 1.0) * a[1] + a[0];
                break;
            case RandInt: 
                if (rti == NULL) throw DeferUntilRuntime();
                rti->mRandUsed = true;
                *res = floor(rti->mCurrentSeed.getDouble() * fabs(a[1] - a[0]) + fmin(a[0], a[1]));
                break;
            default:
                return -1;
        }
        
        return 1;
    }
    
    int 
    ASTselect::evaluate(double* res, int length, Renderer* rti) const
    {
        if (mType != NumericType) {
            CfdgError::Error(where, "Evaluation of a non-numeric select() in a numeric context");
            return -1;
        }
        
        if (res == NULL)
            return tupleSize;
        
        return choices[getIndex(rti)]->evaluate(res, length, rti);
    }
    
    int
    ASTruleSpecifier::evaluate(double* , int , Renderer* ) const
    {
        CfdgError::Error(where, "Improper evaluation of a rule specifier");
        return -1;
    }
    
    int 
    ASTparen::evaluate(double* res, int length, Renderer* rti) const
    {
        if (mType != NumericType) {
            CfdgError::Error(where, "Non-numeric/flag expression in a numeric/flag context");
            return -1;
        }
        return e->evaluate(res, length, rti);
    }
    
    int
    ASTmodTerm::evaluate(double* , int , Renderer* ) const
    {
        CfdgError::Error(where, "Improper evaluation of an adjustment expression");
        return -1;
    }
    
    int
    ASTmodification::evaluate(double* , int , Renderer* ) const
    {
        CfdgError::Error(where, "Improper evaluation of an adjustment expression");
        return -1;
    }
    
    void
    ASTselect::evaluate(Modification& m, std::string* p, double* width, 
                        bool justCheck, int& seedIndex, 
                        Renderer* rti) const
    {
        if (mType != ModType) {
            CfdgError::Error(where, "Evaluation of a non-adjustment select() in an adjustment context");
            return;
        }
        
        choices[getIndex(rti)]->evaluate(m, p, width, justCheck, seedIndex, rti);
    }
    
    void
    ASTvariable::evaluate(Modification& m, std::string*, double*, 
                          bool justCheck, int&, 
                          Renderer* rti) const
    {
        if (mType != ModType)
            CfdgError::Error(where, "Non-adjustment variable referenced in an adjustment context");
        
        if (rti == NULL) throw DeferUntilRuntime();
        if (justCheck) return;
        const StackType* stackItem = (stackIndex < 0) ? rti->mLogicalStackTop + stackIndex :
            &(rti->mCFstack[stackIndex]);
        const Modification* smod = reinterpret_cast<const Modification*> (stackItem);
        m *= *smod;
    }
    
    void
    ASTcons::evaluate(Modification& m, std::string* p, double* width, 
                      bool justCheck, int& seedIndex, 
                      Renderer* rti) const
    {
        left->evaluate(m, p, width, justCheck, seedIndex, rti);
        right->evaluate(m, p, width, justCheck, seedIndex, rti);
    }
    
    void
    ASTmodification::evaluate(Modification& m, std::string* p, double* width, 
                              bool justCheck, int& seedIndex, 
                              Renderer* rti) const
    {
        if (modExp.empty()) {
            m *= modData;
        } else {
            Modification mod;
            setVal(mod, p, width, justCheck, seedIndex, rti);
            m *= mod;
        }
    }
    
    void
    ASTmodification::setVal(Modification& m, std::string* p, double* width, 
                            bool justCheck, int& seedIndex, 
                            Renderer* rti) const
    {
        m = modData;
        for (ASTexpArray::const_iterator it = modExp.begin(); it != modExp.end(); ++it)
            (*it)->evaluate(m, p, width, justCheck, seedIndex, rti);
    }
    
    void
    ASTmodTerm::evaluate(Modification& m, std::string* p, double* width, 
                        bool justCheck, int& seedIndex, 
                        Renderer* rti) const
    {
        double modArgs[6];
        int argcount = 0;
        
        if (args) {
            if (args->mType == ASTexpression::NumericType) {
                if (justCheck)
                    argcount = args->evaluate(0, 0);
                else 
                    argcount = args->evaluate(modArgs, 6, rti);
            } else {
                CfdgError::Error(where, "Adjustments require numeric arguments");
                return;
            }
        }
        
        int minCount = 1;
        int maxCount = 1;
        double arg[6];
        for (int i = 0; i < argcount; ++i)
            arg[i] = fmax(-1.0, fmin(1.0, modArgs[i]));
        
        switch (modType) {
            case ASTmodTerm::x: {
                maxCount = 2;
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
            case ASTmodTerm::time: {
                minCount = maxCount = 2;
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
                maxCount = 6;
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
                maxCount = 2;
                if (justCheck) break;
                if (argcount == 1) 
                    modArgs[1] = modArgs[0];
                agg::trans_affine_scaling sc(modArgs[0], modArgs[1]);
                m.m_transform.premultiply(sc);
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
                minCount = maxCount = 2;
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
            case ASTmodTerm::Entropy: {
                //ent.append(mod->parameter);
                minCount = maxCount = 0;
                //if (justCheck) break;
                m.mRand64Seed.xorString(entString.c_str(), seedIndex);
                break;
            }
            case ASTmodTerm::hue: {
                maxCount = 2;
                if (justCheck) break;
                if (argcount == 1) {
                    if (rti == 0 && m.m_Color.mUseTarget & HSBColor::HueTarget)
                        throw DeferUntilRuntime();
                    m.m_Color.h += modArgs[0];
                } else {
                    if (rti == 0 && (m.m_Color.mUseTarget & HSBColor::HueTarget || 
                                     m.m_Color.h != 0.0))
                        throw DeferUntilRuntime();
                    m.m_Color.h = arg[0];
                    m.m_Color.mUseTarget |= HSBColor::HueTarget;
                    m.m_ColorTarget.h = modArgs[1];
                    m.m_ColorTarget.mUseTarget |= HSBColor::HueTarget;
                }
                break;
            }
            case ASTmodTerm::sat: {
                maxCount = 2;
                if (justCheck) break;
                if (argcount == 1) {
                    if (rti == 0 && (m.m_Color.mUseTarget & HSBColor::SaturationTarget || 
                                     m.m_Color.s != 0.0))
                        throw DeferUntilRuntime();
                    m.m_Color.s = arg[0];
                } else {
                    if (rti == 0 && (m.m_Color.mUseTarget & HSBColor::SaturationTarget || 
                                     m.m_Color.s != 0.0))
                        throw DeferUntilRuntime();
                    m.m_Color.s = arg[0];
                    m.m_Color.mUseTarget |= HSBColor::SaturationTarget;
                    if (rti == 0 && m.m_ColorTarget.s != 0.0)
                        throw DeferUntilRuntime();
                    m.m_ColorTarget.s = arg[1];
                    m.m_ColorTarget.mUseTarget |= HSBColor::SaturationTarget;
                }
                break;
            }
            case ASTmodTerm::bright: {
                maxCount = 2;
                if (justCheck) break;
                if (argcount == 1) {
                    if (rti == 0 && (m.m_Color.mUseTarget & HSBColor::BrightnessTarget || 
                                     m.m_Color.b != 0.0))
                        throw DeferUntilRuntime();
                    m.m_Color.b = arg[0];
                } else {
                    if (rti == 0 && (m.m_Color.mUseTarget & HSBColor::BrightnessTarget || 
                                     m.m_Color.b != 0.0))
                        throw DeferUntilRuntime();
                    m.m_Color.b = arg[0];
                    m.m_Color.mUseTarget |= HSBColor::BrightnessTarget;
                    if (rti == 0 && m.m_ColorTarget.b != 0.0)
                        throw DeferUntilRuntime();
                    m.m_ColorTarget.b = arg[1];
                    m.m_ColorTarget.mUseTarget |= HSBColor::BrightnessTarget;
                }
                break;
            }
            case ASTmodTerm::alpha: {
                maxCount = 2;
                if (justCheck) break;
                if (argcount == 1) {
                    if (rti == 0 && (m.m_Color.mUseTarget & HSBColor::AlphaTarget || 
                                     m.m_Color.a != 0.0))
                        throw DeferUntilRuntime();
                    m.m_Color.a = arg[0];
                } else {
                    if (rti == 0 && (m.m_Color.mUseTarget & HSBColor::AlphaTarget || 
                                     m.m_Color.a != 0.0))
                        throw DeferUntilRuntime();
                    m.m_Color.a = arg[0];
                    m.m_Color.mUseTarget |= HSBColor::AlphaTarget;
                    if (rti == 0 && m.m_ColorTarget.a != 0.0)
                        throw DeferUntilRuntime();
                    m.m_ColorTarget.a = arg[1];
                    m.m_ColorTarget.mUseTarget |= HSBColor::AlphaTarget;
                }
                break;
            }
            case ASTmodTerm::hueTarg: {
                if (justCheck) break;
                if (rti == 0 && (m.m_Color.mUseTarget & HSBColor::HueTarget || 
                                 m.m_Color.h != 0.0))
                    throw DeferUntilRuntime();
                m.m_Color.h = arg[0];
                m.m_Color.mUseTarget |= HSBColor::HueTarget;
                break;
            }
            case ASTmodTerm::satTarg: {
                if (justCheck) break;
                if (rti == 0 && (m.m_Color.mUseTarget & HSBColor::SaturationTarget || 
                                 m.m_Color.s != 0.0))
                    throw DeferUntilRuntime();
                m.m_Color.s = arg[0];
                m.m_Color.mUseTarget |= HSBColor::SaturationTarget;
                break;
            }
            case ASTmodTerm::brightTarg: {
                if (justCheck) break;
                if (rti == 0 && (m.m_Color.mUseTarget & HSBColor::BrightnessTarget || 
                                 m.m_Color.b != 0.0))
                    throw DeferUntilRuntime();
                m.m_Color.b = arg[0];
                m.m_Color.mUseTarget |= HSBColor::BrightnessTarget;
                break;
            }
            case ASTmodTerm::alphaTarg: {
                if (justCheck) break;
                if (rti == 0 && (m.m_Color.mUseTarget & HSBColor::AlphaTarget || 
                                 m.m_Color.a != 0.0))
                    throw DeferUntilRuntime();
                m.m_Color.a = arg[0];
                m.m_Color.mUseTarget |= HSBColor::AlphaTarget;
                break;
            }
            case ASTmodTerm::targHue: {
                if (justCheck) break;
                m.m_ColorTarget.h += modArgs[0];
                break;
            }
            case ASTmodTerm::targSat: {
                if (justCheck) break;
                if (rti == 0 && m.m_ColorTarget.s != 0.0)
                    throw DeferUntilRuntime();
                m.m_ColorTarget.s = arg[0];
                break;
            }
            case ASTmodTerm::targBright: {
                if (justCheck) break;
                if (rti == 0 && m.m_ColorTarget.b != 0.0)
                    throw DeferUntilRuntime();
                m.m_ColorTarget.b = arg[0];
                break;
            }
            case ASTmodTerm::targAlpha: {
                if (justCheck) break;
                if (rti == 0 && m.m_ColorTarget.a != 0.0)
                    throw DeferUntilRuntime();
                m.m_ColorTarget.a = arg[0];
                break;
            }
            case ASTmodTerm::param: {
                minCount = maxCount = 0;
                if (!p) {
                    CfdgError::Error(where, "Cannot provide a parameter in this context");
                    break;
                }
                if (justCheck) break;
                p->assign(entString);
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
                minCount = maxCount = 0;
                args->evaluate(m, p, width, justCheck, seedIndex, rti);
                break;
            }
            default:
                break;
        }
        
        if (argcount < minCount)
            CfdgError::Error(where, "Not enough adjustment parameters");
        if (argcount > maxCount)
            CfdgError::Error(where, "Too many adjustment parameters");
    }
    
    int 
    ASTexpression::flatten(ASTexpArray& dest)
    {
        dest.push_back(this);
        return 1;
    }
    
    int 
    ASTcons::flatten(ASTexpArray& dest)
    {
        int leftnum = 0;
        if (left)
            leftnum = left->flatten(dest);
        
        int rightnum = 0;
        if (right)
            rightnum = right->flatten(dest);
        
        left = right = 0;
        delete this;
        
        return leftnum + rightnum;
    }
    
    int
    ASTvariable::flatten(ASTexpArray& dest)
    {
        int c = count;
        count = 1;
        dest.push_back(this);
        for (int i = 1; i < c; ++i) {
            ASTvariable* next = new ASTvariable(*this);
            next->stackIndex += i;
            dest.push_back(next);
        }
        return c;
    }
    
    int
    ASTselect::flatten(ASTexpArray& dest)
    {
        if (mType != NumericType || tupleSize < 2) {
            dest.push_back(this);
            return 1;
        }
        
        unsigned tups = (unsigned)tupleSize;
        
        {       // deleted an if, but keep the indent
            // Flatten a select() of n-tuples into n selects() of 1-tuples
            // The selector expression for the n selects() must only be evaluated
            // once, since it may be random. So the first one gets the selector
            // and the rest get weak pointers to the first one. This assumes that
            // the first select() is always evaluated first and that if the first
            // select() is deleted then the rest will not be evaluated. I am
            // certain that these are both true. simplify() will never delete the
            // first one because it only deletes when the selector is constant and
            // we know that it isn't.
            std::vector<ASTselect*> tempSel(tupleSize);
            for (unsigned i = 0; i < tups; ++i) {
                tempSel[i] = new ASTselect(where);
                tempSel[i]->selector = i ? NULL : selector;
                tempSel[i]->weakPointer = i  && selector ? tempSel[0] : NULL;
                tempSel[i]->tupleSize = 1;
                tempSel[i]->mType = NumericType;
                tempSel[i]->ent = ent;
                tempSel[i]->indexCache = indexCache;
                tempSel[i]->arguments = i ? NULL : arguments;
                tempSel[i]->choices.reserve(choices.size());
            }
            arguments = NULL;
            
            ASTexpArray temp;
            for (ASTexpArray::iterator it = choices.begin(); it != choices.end(); ++it) {
                (*it)->flatten(temp);
                for (unsigned i = 0; i < tups; ++i)
                    tempSel[i]->choices.push_back(temp[i]);
                temp.clear();
            }
            choices.clear();
            
            for (unsigned i = 0; i < tups; ++i)
                dest.push_back(tempSel[i]);
            tempSel.clear();
        }
        delete this;
        return tups;
    }
    
    int 
    ASToperator::flatten(ASTexpArray& dest)
    {
        if (mType != ModType) {
            dest.push_back(this);
            return 1;
        }
            
        int leftnum = 0;
        if (left)
            leftnum = left->flatten(dest);
        
        int rightnum = 0;
        if (right)
            rightnum = right->flatten(dest);
        
        left = right = 0;
        delete this;
        
        return leftnum + rightnum;
    }
    
    int 
    ASTmodTerm::flatten(ASTexpArray& dest)
    {
        // This code merges adjacent x and y adjustments into a single xy
        // adjustment
        ASTmodTerm* last = 0;
        if (dest.size())
            last = dynamic_cast<ASTmodTerm*> (dest.back());
        if (last == 0) {
            dest.push_back(this);
            return 1;
        }
        
        if (modType == ASTmodTerm::x && last->modType == ASTmodTerm::y && 
            args->evaluate(0, 0) == 1)
        {
            last->modType = ASTmodTerm::x;
            last->args = new ASTcons(args, last->args);
            args = 0;
            last->where = last->where + where;
            last->entString.append(entString);
            delete this;
            return 0;
        } else if (modType == ASTmodTerm::y && last->modType == ASTmodTerm::x && 
                   last->args->evaluate(0, 0) == 1)
        {
            last->args = new ASTcons(last->args, args);
            args = 0;
            last->where = last->where + where;
            last->entString.append(entString);
            delete this;
            return 0;
        }
        
        dest.push_back(this);
        return 1;
    }
    
    void
    ASTfunction::entropy(std::string& ent) const
    {
        if (functype <= NotAFunction) return;
        
        arguments->entropy(ent);
        ent.append(Entropies[functype]);
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
    ASTcons::entropy(std::string& ent) const
    {
        left->entropy(ent);
        if (right) right->entropy(ent);
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
        if (args) args->entropy(ent);
        ent.append(ASTmodTerm::Entropies[modType]);
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
            r->isLocal = isLocal;
            
            delete this;
            return r;
        } else {
            arguments = arguments->simplify();
        }
        
        return this;
    }
    
    ASTexpression*
    ASTselect::simplify()
    {
        // NB: ASTselect::flatten() depends on ASTselect::simplify() never
        // deleting the first select() in a flattened list.
        if (selector == NULL && weakPointer == NULL)
        {
            unsigned s = getIndex();
            ASTexpression* ret = choices[s]->simplify();
            choices[s] = NULL;
            delete this;
            return ret;
        }
        return this;
    }
    
    ASTexpression*
    ASTruleSpecifier::simplify()
    {
        if (arguments) 
            arguments = arguments->simplify();
        return this;
    }
    
    ASTexpression*
    ASTcons::simplify()
    {
        left = left->simplify();
        if (right) right = right->simplify();
        return this;
    }
    
    ASTexpression*
    ASToperator::simplify()
    {
        left = left->simplify();
        if (right) right = right->simplify();
        
        if (isConstant && (mType == NumericType || mType == FlagType)) {
            double result;
            if (evaluate(&result, 1) != 1) {
                return 0;
            }
            
            ASTreal* r = new ASTreal(result, where);
            r->mType = mType;
            r->isNatural = isNatural;
            r->isLocal = isLocal;
            
            delete this;
            return r;
        }
        
        return this;
    }
    
    ASTexpression*
    ASTparen::simplify()
    {
        ASTexpression* e2 = e->simplify();
        
        e = 0;
        delete this;
        return e2;
    }
    
    ASTvariable::ASTvariable(int stringNum, const std::string& str, const yy::location& loc) 
    : ASTexpression(loc), stringIndex(stringNum), text(str), stackIndex(0),
      isParameter(false) { };
    
    ASTexpression*
    ASTmodTerm::simplify()
    {
        if (args) {
            args = args->simplify();
        }
        return this;
    }

    void
    ASTmodification::evalConst(exp_ptr mod, std::string* p, double* width) 
        throw(CfdgError)
    {
        int nonConstant = 0;
        int seedIndex = 0;
        
        ASTexpArray temp;
        mod.release()->flatten(temp);
        
        for (ASTexpArray::iterator it = temp.begin(); it != temp.end(); ++it) {
            bool keepThisOne = false;
            ASTmodTerm* mod = dynamic_cast<ASTmodTerm*> (*it);
            if (mod == 0) {
                CfdgError::Error((*it)->where, "Unknown term in shape adjustment");
                delete *it;
                continue;
            }
            
            // Put in code for separating color changes and target color changes
                        
            int mc = ASTmodification::ModClass[mod->modType];
            modClass |= mc;
            if (!mod->isConstant)
                nonConstant |= mc;
            bool justCheck = (mc & nonConstant) != 0;
            
            try {
                mod->evaluate(modData, p, width, justCheck, seedIndex);
            } catch (CfdgError) {
                for (; it != temp.end(); ++it) {
                    delete *it;
                }
                for (it = modExp.begin(); it != modExp.end(); ++it) {
                    delete *it;
                }
                throw;
            } catch (DeferUntilRuntime) {
                keepThisOne = true;
            }
            
            if (justCheck || keepThisOne) {
                modExp.push_back(*it);
            } else {
                delete *it;
            }
        }
    }
    
    unsigned
    ASTselect::getIndex(Renderer* rti) const
    {
        if (selector) {
            double select = 0.0;
            selector->evaluate(&select, 1, rti);
            if (select < 0.0)
                indexCache = 0;
            else if ((size_t)select >= choices.size())
                indexCache = (unsigned)choices.size() - 1;
            else
                indexCache = (unsigned)select;
            
            return indexCache;
        } else if (weakPointer) {
            return weakPointer->indexCache;
        } else {
            return indexCache;
        }
    }
}

