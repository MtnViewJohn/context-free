// astexpression.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2011-2013 John Horigan - john@glyphic.com
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


#ifndef INCLUDE_ASTEXPRESSION_H
#define INCLUDE_ASTEXPRESSION_H

#include "ast.h"
#include "location.hh"
#include "cfdg.h"
#include "shape.h"
#include <string>
#include <limits>
#include "Rand64.h"

class RendererAST;

namespace AST {
    
    class ASTdefine;

    class ASTexpression {
    public:
        bool isConstant;
        bool isNatural;
        bool isLocal;
        expType mType;
        yy::location where;
        
        ASTexpression(const yy::location& loc) : isConstant(false), isNatural(false),
        isLocal(true), mType(NoType), where(loc) {};
        ASTexpression(const yy::location& loc, bool c, bool n, expType t = NoType) 
        : isConstant(c), isNatural(n), isLocal(true), mType(t), where(loc) {};
        virtual ~ASTexpression() {};
        virtual int evaluate(double* , int, RendererAST* = nullptr) const
        { return 0; }
        virtual void evaluate(Modification& , int* , double* ,
                              bool , int& , bool ,
                              RendererAST*) const
        { CfdgError::Error(where, "Cannot convert this expression into an adjustment"); }
        virtual const StackType* evalArgs(RendererAST* = nullptr, const StackType* = nullptr) const
        { CfdgError::Error(where, "Cannot convert this expression into a shape"); return nullptr; }
        virtual void entropy(std::string&) const {};
        virtual ASTexpression* simplify() { return this; }
        
        virtual ASTexpression* operator[](size_t i);
        virtual const ASTexpression* operator[](size_t i) const;
        virtual int size() const { return 1; }
        virtual ASTexpression* append(ASTexpression* sib);
        virtual bool release(size_t = std::numeric_limits<size_t>::max()) { return false; }
        static ASTexpression* Append(ASTexpression* l, ASTexpression* r);
    };
    class ASTfunction : public ASTexpression {
    public:
        enum FuncType { IllegalArguments = -2, NotAFunction = -1, 
            Cos, Sin, Tan, Cot, Acos, Asin, Atan, Acot, 
            Cosh, Sinh, Tanh, Acosh, Asinh, Atanh, Log, Log10,
            Sqrt, Exp, Abs, Floor, Infinity, Factorial, Sg, IsNatural,
            BitNot, BitOr, BitAnd, BitXOR, BitLeft, BitRight,
            Atan2, Mod, Divides, Div,
            Min, Max, Ftime, Frame,
            Rand_Static, Rand, Rand2, RandInt, LastOne
        };
        static const char* FuncNames[LastOne];
        static const char* Entropies[LastOne];
        static FuncType GetFuncType(const std::string& func);
        FuncType functype;
        exp_ptr arguments;
        double random;
        ASTfunction(const std::string& func, exp_ptr args, Rand64& r,
                    const yy::location& nameLoc, const yy::location& argsLoc);
        virtual ~ASTfunction() { };
        virtual int evaluate(double* r, int size, RendererAST* rti = nullptr) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* simplify();
    private:
        ASTfunction() : ASTexpression(CfdgError::Default) {};
    };
    class ASTselect : public ASTexpression {
    public:
        int              tupleSize;
        unsigned         indexCache;
        std::string      ent;
        exp_ptr          arguments;
        bool             ifSelect;
        
        ASTselect(exp_ptr args, const yy::location& loc, bool asIf);
        virtual ~ASTselect();
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual void evaluate(Modification& m, int* p, double* width, 
                              bool justCheck, int& seedIndex, bool shapeDest,
                              RendererAST* r) const;
        virtual const StackType* evalArgs(RendererAST* rti = nullptr, const StackType* parent = nullptr) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* simplify();
    private:
        ASTselect(const yy::location& loc)
        : ASTexpression(loc), tupleSize(-1), indexCache(0) {}
        unsigned getIndex(RendererAST* rti = nullptr) const;
    };
    class ASTruleSpecifier : public ASTexpression {
    public:
        enum ArgSource { NoArgs, DynamicArgs, StackArgs, SimpleArgs, ParentArgs, SimpleParentArgs, ShapeArgs };
        int shapeType;
        int argSize;
        std::string entropyVal;
        ArgSource argSource;
        exp_ptr arguments;
        const StackType* simpleRule;
        int mStackIndex;
        const ASTparameters* typeSignature;
        
        static ASTruleSpecifier Zero;
        
        ASTruleSpecifier(int t, const std::string& name, exp_ptr args, const yy::location& loc, 
                         const ASTparameters* types, const ASTparameters* parent);
        ASTruleSpecifier(const std::string& name, const yy::location& loc, 
                         int stackIndex);
        ASTruleSpecifier(const ASTruleSpecifier* r, const std::string& name, 
                         const yy::location& loc);
        ASTruleSpecifier(exp_ptr args, const yy::location& loc);
        ASTruleSpecifier(ASTruleSpecifier&& r);
#ifndef _WIN32
        ASTruleSpecifier(const ASTruleSpecifier&) = delete;
        ASTruleSpecifier& operator=(const ASTruleSpecifier&) = delete;
#endif
        explicit ASTruleSpecifier()
        :   ASTexpression(CfdgError::Default, false, false, RuleType), shapeType(-1),
            argSize(0), argSource(NoArgs), arguments(nullptr),
            simpleRule(nullptr), mStackIndex(0), typeSignature(nullptr) {};
        virtual ~ASTruleSpecifier();
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual const StackType* evalArgs(RendererAST* = nullptr, const StackType* parent = nullptr) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* simplify();
#ifdef _WIN32
    private:
        ASTruleSpecifier(const ASTruleSpecifier&) :
            ASTexpression(CfdgError::Default) { };
        ASTruleSpecifier& operator=(const ASTruleSpecifier&) { return *this; };
#endif
    };
    class ASTcons : public ASTexpression {
    public:
        ASTexpArray children;
        ASTcons(ASTexpression* l, ASTexpression* r);
        virtual ~ASTcons();
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual void evaluate(Modification& m, int* p, double* width, 
                              bool justCheck, int& seedIndex, bool shapeDest,
                              RendererAST* r) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* simplify();
        
        virtual ASTexpression* operator[](size_t i);
        virtual const ASTexpression* operator[](size_t i) const;
        virtual int size() const { return (int)(children.size()); }
        virtual ASTexpression* append(ASTexpression* sib);
        virtual bool release(size_t i = std::numeric_limits<size_t>::max());
        
    private:
        ASTcons() : ASTexpression(CfdgError::Default) {};
    };
    class ASTreal : public ASTexpression {
    public:
        double value;
        std::string text;
        ASTreal(const std::string& t, const yy::location& loc, bool negative = false) 
        : ASTexpression(loc, true, false, NumericType), text(t) 
        { 
            if (negative) text.insert(0, 1, '-');
            value = CFatof(text.c_str()); 
            isNatural = floor(value) == value && value >= 0.0 && value < 9007199254740992.;
        };
        ASTreal(double v, const yy::location& loc) 
        : ASTexpression(loc, true, 
                        floor(v) == v && v >= 0.0 && v < 9007199254740992.,
                        NumericType), value(v) {};
        virtual ~ASTreal() {};
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual void entropy(std::string& e) const;
    private:
        ASTreal() : ASTexpression(CfdgError::Default) {};
    };
    class ASTvariable : public ASTexpression {
    public:
        int stringIndex;
        std::string text;
        int stackIndex;
        int count;
        bool isParameter;
        
        ASTvariable(int stringNum, const std::string& str, const yy::location& loc); 
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual void evaluate(Modification& m, int* p, double* width, 
                              bool justCheck, int& seedIndex, bool shapeDest,
                              RendererAST* r) const;
        virtual void entropy(std::string& e) const;
    private:
        ASTvariable() : ASTexpression(CfdgError::Default) {};
    };
    class ASTuserFunction : public ASTexpression {
    public:
        ASTdefine* definition;      // weak ptr
        exp_ptr arguments;
        bool isLet;
        
        ASTuserFunction(ASTexpression* args, ASTdefine* func, const yy::location& nameLoc);
        virtual ~ASTuserFunction() { }
        virtual int evaluate(double* , int, RendererAST* = nullptr) const;
        virtual void evaluate(Modification& m, int* p, double* width, 
                              bool justCheck, int& seedIndex, bool shapeDest,
                              RendererAST* r) const;
        virtual const StackType* evalArgs(RendererAST* rti = nullptr, const StackType* parent = nullptr) const;
        virtual void entropy(std::string&) const;
        virtual ASTexpression* simplify();
    };
    class ASTlet : public ASTuserFunction {
    public:
        ASTlet(ASTexpression* args, ASTdefine* func, const yy::location& letLoc,
               const yy::location& defLoc);
        virtual ~ASTlet();          // inherited definition ptr owns ASTdefine
    };
    class ASToperator : public ASTexpression {
    public:
        char op;
        exp_ptr left;
        exp_ptr right;
        ASToperator(char o, ASTexpression* l, ASTexpression* r);
        virtual ~ASToperator() { }
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* simplify();
        static ASTexpression* Op(char o, ASTexpression* l, ASTexpression* r);
    private:
        ASToperator() : ASTexpression(CfdgError::Default) {};
    };
    class ASTparen : public ASTexpression {
    public:
        exp_ptr e;
        ASTparen(ASTexpression* e1) : ASTexpression(e1->where, e1->isConstant, 
                                                    e1->isNatural,
                                                    e1->mType), e(e1)
        { isLocal = e1->isLocal; };
        virtual ~ASTparen() { }
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual void evaluate(Modification& m, int* p, double* width,
                              bool justCheck, int& seedIndex, bool shapeDest,
                              RendererAST* r) const;
        virtual const StackType* evalArgs(RendererAST* rti = nullptr, const StackType* parent = nullptr) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* simplify();
    private:
        ASTparen() : ASTexpression(CfdgError::Default) {};
    };

    class ASTmodTerm : public ASTexpression {
    public:
        enum modTypeEnum {  unknownType, x, y, z, xyz, transform, 
            size, sizexyz, rot, skew, flip, 
            zsize, Entropy, hue, sat, bright, alpha, 
            hueTarg, satTarg, brightTarg, alphaTarg, 
            targHue, targSat, targBright, targAlpha,
            time, timescale, 
            stroke, param, x1, y1, x2, y2, xrad, yrad, modification, lastModType };
        
        modTypeEnum modType;
        exp_ptr args;
        std::string entString;
        
        static const char* Entropies[lastModType];
        
        static void Eval(ASTexpression* mod, Modification& m, std::string* p = nullptr,
                         double* width = nullptr, Renderer* r = nullptr);
        
        ASTmodTerm(modTypeEnum t, ASTexpression* a, const yy::location& loc);
        ASTmodTerm(modTypeEnum t, const std::string& ent, const yy::location& loc)
        : ASTexpression(loc, true, false, ModType), modType(t), args(nullptr), entString(ent) {};
        ASTmodTerm(modTypeEnum t, const yy::location& loc)
        : ASTexpression(loc, true, false, ModType), modType(t), args(nullptr) {};
        virtual ~ASTmodTerm() { }
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual void evaluate(Modification& m, int* p, double* width, 
                              bool justCheck, int& seedIndex, bool shapeDest,
                              RendererAST*) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* simplify();
    };
    class ASTmodification : public ASTexpression {
    public:
        enum modClassEnum {
            NotAClass = 0, GeomClass = 1, ZClass = 2, TimeClass = 4,
            HueClass = 8, SatClass = 16, BrightClass = 32, AlphaClass = 64,
            HueTargetClass = 128, SatTargetClass = 256, BrightTargetClass = 512, AlphaTargetClass = 1024,
            StrokeClass = 2048, ParamClass = 4096, PathOpClass = 8192
        };
        Modification    modData;
        ASTtermArray    modExp;
        int             modClass;
        double          strokeWidth;
        int             flags;
        int             entropyIndex;
        
        static int ModClass[ASTmodTerm::lastModType];
        
        ASTmodification(const yy::location& loc)
        : ASTexpression(loc, true, false, ModType), modClass(NotAClass),
          strokeWidth(0.1), flags(CF_MITER_JOIN + CF_BUTT_CAP + CF_FILL), 
          entropyIndex(0) {}
        ASTmodification(const ASTmodification& m, const yy::location& loc);
        ASTmodification(mod_ptr m, const yy::location& loc);
        virtual ~ASTmodification();
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual void evaluate(Modification& m, int* p, double* width, 
                              bool justCheck, int& seedIndex, bool shapeDest,
                              RendererAST*) const;
        void setVal(Modification& m, int* p, double* width, 
                    bool justCheck, int& seedIndex, 
                    RendererAST* = nullptr) const;
        void addEntropy(const std::string& name);
        void evalConst();
        void makeCanonical();
        void grab(ASTmodification* m);
    };
    class ASTarray : public ASTexpression {
    public:
        double  mData[9];
        bool    mConstData;
        exp_ptr mArgs;
        int     mLength;
        int     mStride;
        int     mStackIndex;
        int     mCount;
        bool    isParameter;
        std::string entString;
        
        ASTarray(const ASTparameter* bound, exp_ptr args, int stackOffset,
                 const yy::location& loc, const std::string& name);
        virtual ~ASTarray();
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* simplify();
    };
}

#endif //INCLUDE_ASTEXPRESSION_H
