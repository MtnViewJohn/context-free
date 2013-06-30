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
#include <map>

class RendererAST;
class Builder;

namespace AST {
    
    class ASTdefine;
    class ASTrepContainer;

    class ASTexpression {
    public:
        bool isConstant;
        bool isNatural;
        Locality_t mLocality;
        expType mType;
        yy::location where;
        
        ASTexpression(const yy::location& loc) : isConstant(false), isNatural(false),
        mLocality(UnknownLocal), mType(NoType), where(loc) {};
        ASTexpression(const yy::location& loc, bool c, bool n, expType t = NoType) 
        : isConstant(c), isNatural(n), mLocality(UnknownLocal), mType(t), where(loc) {};
        virtual ~ASTexpression() {};
        virtual int evaluate(double* , int, RendererAST* = nullptr) const
        { return 0; }
        virtual void evaluate(Modification& , double* ,
                              bool , int& , bool ,
                              RendererAST*) const
        { CfdgError::Error(where, "Cannot convert this expression into an adjustment"); }
        virtual const StackRule* evalArgs(RendererAST* = nullptr, const StackRule* = nullptr) const
        { CfdgError::Error(where, "Cannot convert this expression into a shape"); return nullptr; }
        virtual void entropy(std::string&) const {};
        virtual ASTexpression* simplify() { return this; }
        
        virtual ASTexpression* operator[](size_t i);
        virtual const ASTexpression* operator[](size_t i) const;
        virtual int size() const { return 1; }
        virtual ASTexpression* append(ASTexpression* sib);
        virtual bool release(size_t = std::numeric_limits<size_t>::max()) { return false; }
        virtual ASTexpression* compile(CompilePhase ph) { return this; }
        static ASTexpression* Append(ASTexpression* l, ASTexpression* r);
        ASTexpression* constCopy(const ASTparameter* bound, const std::string& entropy) const;
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
        static FuncType GetFuncType(const std::string& func);
        FuncType functype;
        exp_ptr arguments;
        double random;
        ASTfunction(const std::string& func, exp_ptr args, Rand64& r,
                    const yy::location& nameLoc, const yy::location& argsLoc);
        virtual ~ASTfunction() { };
        virtual int evaluate(double* r, int size, RendererAST* rti = nullptr) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* compile(CompilePhase ph);
        virtual ASTexpression* simplify();
    private:
        ASTfunction() : ASTexpression(CfdgError::Default) {};
		static const std::map<std::string, FuncType> NameMap;
		static const std::map<FuncType, const char*> EntropyMap;
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
        virtual void evaluate(Modification& m, double* width, 
                              bool justCheck, int& seedIndex, bool shapeDest,
                              RendererAST* r) const;
        virtual const StackRule* evalArgs(RendererAST* rti = nullptr, const StackRule* parent = nullptr) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* simplify();
        virtual ASTexpression* compile(CompilePhase ph);
    private:
        ASTselect(const yy::location& loc)
        : ASTexpression(loc), tupleSize(-1), indexCache(0) {}
        unsigned getIndex(RendererAST* rti = nullptr) const;
    };
    class ASTruleSpecifier : public ASTexpression {
    public:
        enum ArgSource {
            NoArgs,             // shapeType has no arguments
            DynamicArgs,        // shapeType has non-constant arguments
            StackArgs,          // not shapeType, StackRule* pointer to shape
            SimpleArgs,         // shapeType has constant arguments
            ParentArgs,         // reusing parent args, child shape may be different
            SimpleParentArgs,   // reusing shape args, child shape same as parent
            ShapeArgs           // not shapeType, evalArgs arguments (non-constant) to get shape
        };
        int shapeType;
        int argSize;
        std::string entropyVal;
        ArgSource argSource;
        exp_ptr arguments;
        const StackRule* simpleRule;
        int mStackIndex;
        const ASTparameters* typeSignature;
        const ASTparameters* parentSignature;
        
        ASTruleSpecifier(int t, const std::string& name, exp_ptr args, const yy::location& loc, 
                         const ASTparameters* parent);
        ASTruleSpecifier(int t, const std::string& name, const yy::location& loc);
        ASTruleSpecifier(exp_ptr args, const yy::location& loc);
        ASTruleSpecifier(ASTruleSpecifier&& r);
#ifndef _WIN32
        ASTruleSpecifier(const ASTruleSpecifier&) = delete;
        ASTruleSpecifier& operator=(const ASTruleSpecifier&) = delete;
#endif
        explicit ASTruleSpecifier()
        :   ASTexpression(CfdgError::Default, false, false, RuleType), shapeType(-1),
            argSize(0), argSource(NoArgs), arguments(nullptr),
            simpleRule(nullptr), mStackIndex(0), typeSignature(nullptr),
            parentSignature(nullptr) {};
        virtual ~ASTruleSpecifier();
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual const StackRule* evalArgs(RendererAST* = nullptr, const StackRule* sr = nullptr) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* simplify();
        virtual ASTexpression* compile(CompilePhase ph);
#ifdef _WIN32
    private:
        ASTruleSpecifier(const ASTruleSpecifier&) :
            ASTexpression(CfdgError::Default) { };
        ASTruleSpecifier& operator=(const ASTruleSpecifier&) { return *this; };
#endif
    };
    class ASTstartSpecifier : public ASTruleSpecifier {
    public:
        mod_ptr mModification;
        ASTstartSpecifier(int t, const std::string& name, exp_ptr args,
                          const yy::location& loc, mod_ptr mod)
        : ASTruleSpecifier(t, name, std::move(args), loc, nullptr),
          mModification(std::move(mod)) { };
        ASTstartSpecifier(int nameIndex, const std::string& name,
                          const yy::location& loc, mod_ptr mod)
        : ASTruleSpecifier(nameIndex, name, loc), mModification(std::move(mod)) { };
        ASTstartSpecifier(exp_ptr args, const yy::location& loc, mod_ptr mod)
        : ASTruleSpecifier(std::move(args), loc), mModification(std::move(mod)) { };
        ASTstartSpecifier(ASTruleSpecifier&& r, mod_ptr m)
        : ASTruleSpecifier(std::move(r)), mModification(std::move(m)) { };
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* simplify();
        virtual ASTexpression* compile(CompilePhase ph);
    };
    class ASTcons : public ASTexpression {
    public:
        ASTexpArray children;
        ASTcons(ASTexpression* l, ASTexpression* r);
        virtual ~ASTcons();
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual void evaluate(Modification& m, double* width, 
                              bool justCheck, int& seedIndex, bool shapeDest,
                              RendererAST* r) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* simplify();
        virtual ASTexpression* compile(CompilePhase ph);
        
        virtual ASTexpression* operator[](size_t i);
        virtual const ASTexpression* operator[](size_t i) const;
        virtual int size() const { return static_cast<int>(children.size()); }
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
            mLocality = PureLocal;
        };
        ASTreal(double v, const yy::location& loc) 
        : ASTexpression(loc, true, 
                        floor(v) == v && v >= 0.0 && v < 9007199254740992.,
                        NumericType), value(v) { mLocality = PureLocal; };
        virtual ~ASTreal() {};
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* compile(CompilePhase ph);
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
        virtual void evaluate(Modification& m, double* width, 
                              bool justCheck, int& seedIndex, bool shapeDest,
                              RendererAST* r) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* compile(CompilePhase ph);
    private:
        ASTvariable() : ASTexpression(CfdgError::Default) {};
    };
    class ASTuserFunction : public ASTexpression {
    public:
        int nameIndex;
        ASTdefine* definition;      // weak ptr
        exp_ptr arguments;
        bool isLet;
        
        ASTuserFunction(int name, ASTexpression* args, ASTdefine* func, const yy::location& nameLoc);
        virtual ~ASTuserFunction() { }
        virtual int evaluate(double* , int, RendererAST* = nullptr) const;
        virtual void evaluate(Modification& m, double* width, 
                              bool justCheck, int& seedIndex, bool shapeDest,
                              RendererAST* r) const;
        virtual const StackRule* evalArgs(RendererAST* rti = nullptr, const StackRule* parent = nullptr) const;
        virtual void entropy(std::string&) const;
        virtual ASTexpression* simplify();
        virtual ASTexpression* compile(CompilePhase ph);
    };
    class ASTlet : public ASTuserFunction {
        std::unique_ptr<ASTrepContainer> mDefinitions;
    public:
        ASTlet(cont_ptr args, def_ptr func, const yy::location& letLoc,
               const yy::location& defLoc);
        virtual ~ASTlet();          // inherited definition ptr owns ASTdefine
        virtual ASTexpression* simplify();
        virtual ASTexpression* compile(CompilePhase ph);
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
        virtual ASTexpression* compile(CompilePhase ph);
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
        { };
        virtual ~ASTparen() { }
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual void evaluate(Modification& m, double* width,
                              bool justCheck, int& seedIndex, bool shapeDest,
                              RendererAST* r) const;
        virtual const StackRule* evalArgs(RendererAST* rti = nullptr, const StackRule* parent = nullptr) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* simplify();
        virtual ASTexpression* compile(CompilePhase ph);
    private:
        ASTparen() : ASTexpression(CfdgError::Default) {};
    };

    class ASTmodTerm : public ASTexpression {
    public:
        enum modTypeEnum {  unknownType, x, y, z, xyz, transform, 
            size, sizexyz, rot, skew, flip, 
            zsize, hue, sat, bright, alpha, 
            hueTarg, satTarg, brightTarg, alphaTarg, 
            targHue, targSat, targBright, targAlpha,
            time, timescale, 
            stroke, param, x1, y1, x2, y2, xrad, yrad, modification, lastModType };
        
        modTypeEnum modType;
        exp_ptr args;
        int argCount;
        std::string paramString;
        
        static void Eval(ASTexpression* mod, Modification& m, std::string* p = nullptr,
                         double* width = nullptr, Renderer* r = nullptr);
        
        ASTmodTerm(modTypeEnum t, ASTexpression* a, const yy::location& loc)
        : ASTexpression(loc, a->isConstant, false, ModType), modType(t), args(a), argCount(0) {};
        ASTmodTerm(modTypeEnum t, const std::string& ent, const yy::location& loc)
        : ASTexpression(loc, true, false, ModType), modType(t), args(nullptr), argCount(0), paramString(ent) {};
        ASTmodTerm(modTypeEnum t, const yy::location& loc)
        : ASTexpression(loc, true, false, ModType), modType(t), args(nullptr), argCount(0) {};
        virtual ~ASTmodTerm() { }
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual void evaluate(Modification& m, double* width, 
                              bool justCheck, int& seedIndex, bool shapeDest,
                              RendererAST*) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* simplify();
        virtual ASTexpression* compile(CompilePhase ph);
	private:
		static const std::map<modTypeEnum, const char*> EntropyMap;
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
        bool            canonical;
        
        ASTmodification(const yy::location& loc)
        : ASTexpression(loc, true, false, ModType), modClass(NotAClass),
          strokeWidth(0.1), flags(CF_MITER_JOIN + CF_BUTT_CAP + CF_FILL), 
          entropyIndex(0), canonical(true) {}
        ASTmodification(const ASTmodification& m, const yy::location& loc);
        ASTmodification(mod_ptr m, const yy::location& loc);
        virtual ~ASTmodification();
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual void evaluate(Modification& m, double* width, 
                              bool justCheck, int& seedIndex, bool shapeDest,
                              RendererAST*) const;
        virtual ASTexpression* simplify();
        virtual ASTexpression* compile(CompilePhase ph);
        void setVal(Modification& m, double* width,
                    bool justCheck, int& seedIndex, 
                    RendererAST* = nullptr) const;
        void addEntropy(const std::string& name);
        void evalConst();
        void makeCanonical();
        void grab(ASTmodification* m);
	private:
		static const std::map<ASTmodTerm::modTypeEnum, int> ClassMap;
	};
    class ASTarray : public ASTexpression {
    public:
        int     mName;
        double  mData[9];
        bool    mConstData;
        exp_ptr mArgs;
        int     mLength;
        int     mStride;
        int     mStackIndex;
        int     mCount;
        bool    isParameter;
        std::string entString;
        
        ASTarray(int nameIndex, exp_ptr args, const yy::location& loc, const std::string& name);
        virtual ~ASTarray();
        virtual int evaluate(double* r, int size, RendererAST* = nullptr) const;
        virtual void entropy(std::string& e) const;
        virtual ASTexpression* simplify();
        virtual ASTexpression* compile(CompilePhase ph);
    };
    
    inline void Compile(exp_ptr& exp, CompilePhase ph)
    {
        if (!exp) return;
        ASTexpression* r = exp->compile(ph);
        if (r != exp.get())
            exp.reset(r);
    }
    
    inline void Simplify(exp_ptr& exp)
    {
        if (!exp) return;
        ASTexpression* r = exp.release()->simplify();
        exp.reset(r);
    }
}

#endif //INCLUDE_ASTEXPRESSION_H
