// astexpression.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2011-2014 John Horigan - john@glyphic.com
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
#include <initializer_list>

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
        virtual ~ASTexpression() = default;
        virtual int evaluate(double* , int, RendererAST* = nullptr) const
        { return 0; }
        virtual void evaluate(Modification&, bool, RendererAST*) const
        { CfdgError::Error(where, "Cannot convert this expression into an adjustment"); }
        virtual param_ptr evalArgs(RendererAST* = nullptr, const StackRule* = nullptr) const
        { CfdgError::Error(where, "Cannot convert this expression into a shape"); return nullptr; }
        virtual void entropy(std::string&) const {};
        virtual ASTexpression* simplify() { return this; }
        
        virtual const ASTexpression* getChild(size_t i) const;
        virtual size_t size() const { return 1; }
        virtual ASTexpression* append(ASTexpression* sib);
        virtual ASTexpression* compile(CompilePhase ph) { return nullptr; }
        // Always returns nullptr except during type check in the following cases:
        // * An ASTvariable bound to a constant returns a copy of the constant
        // * An ASTvariable bound to a rule spec returns an ASTruleSpec that
        //   acts as a stack variable
        // * A shape spec that was parsed as an ASTuserFunc because of grammar
        //   ambiguity will return the correct ASTruleSpec
        //
        // It is safe to ignore the return value if you can guarantee that none
        // of these conditions is possible. Otherwise you must replace the object
        // with the returned object. Using the original object after type check
        // will fail.
        static ASTexpression* Append(ASTexpression* l, ASTexpression* r);
    };
    class ASTfunction : public ASTexpression {
    public:
        enum FuncType { NotAFunction, 
            Cos, Sin, Tan, Cot, Acos, Asin, Atan, Acot, 
            Cosh, Sinh, Tanh, Acosh, Asinh, Atanh, Log, Log10,
            Sqrt, Exp, Abs, Floor, Ceiling, Infinity, Factorial, Sg, IsNatural,
            BitNot, BitOr, BitAnd, BitXOR, BitLeft, BitRight,
            Atan2, Mod, Divides, Div,
            Dot, Cross, Hsb2Rgb, Rgb2Hsb, Vec, 
            Min, Max, Ftime, Frame,
            Rand_Static, Rand, Rand2, RandExponential, RandGamma, RandWeibull,
            RandExtremeValue, RandNormal, RandLogNormal, RandChiSquared,
            RandCauchy, RandFisherF, RandStudentT,
            RandInt, RandBernoulli, RandBinomial, RandNegBinomial, RandPoisson,
            RandDiscrete, RandGeometric
        };
        static FuncType GetFuncType(const std::string& func);
        FuncType functype;
        exp_ptr arguments;
        double random;
        ASTfunction() = delete;
        ASTfunction(const std::string& func, exp_ptr args, Rand64& r,
                    const yy::location& nameLoc, const yy::location& argsLoc);
        ~ASTfunction() override = default;
        int evaluate(double* r, int size, RendererAST* rti = nullptr) const override;
        void entropy(std::string& e) const override;
        ASTexpression* compile(CompilePhase ph) override;
        ASTexpression* simplify() override;
    };
    class ASTselect : public ASTexpression {
        enum consts_t: size_t { NotCached = static_cast<size_t>(-1) };
    public:
        int              tupleSize;
        size_t           indexCache;
        std::string      ent;
        ASTexpArray      arguments;
        exp_ptr          selector;
        bool             ifSelect;
        
        ASTselect(exp_ptr args, const yy::location& loc, bool asIf);
        ~ASTselect() override;
        int evaluate(double* r, int size, RendererAST* = nullptr) const override;
        void evaluate(Modification& m, bool shapeDest, RendererAST* r) const override;
        param_ptr evalArgs(RendererAST* rti = nullptr, const StackRule* parent = nullptr) const override;
        void entropy(std::string& e) const override;
        ASTexpression* simplify() override;
        ASTexpression* compile(CompilePhase ph) override;
    private:
        //ASTselect(const yy::location& loc)
        //: ASTexpression(loc), tupleSize(-1), indexCache(0) {}
        size_t getIndex(RendererAST* rti = nullptr) const;
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
        param_ptr simpleRule;
        int mStackIndex;
        const ASTparameters* typeSignature;
        const ASTparameters* parentSignature;
        
        ASTruleSpecifier(int t, const std::string& name, exp_ptr args, const yy::location& loc, 
                         const ASTparameters* parent);
        ASTruleSpecifier(int t, const std::string& name, const yy::location& loc);
        ASTruleSpecifier(exp_ptr args, const yy::location& loc);
        ASTruleSpecifier(ASTruleSpecifier&& r);
        ASTruleSpecifier(const ASTruleSpecifier&) = delete;
        ASTruleSpecifier& operator=(const ASTruleSpecifier&) = delete;
        explicit ASTruleSpecifier()
        :   ASTexpression(CfdgError::Default, false, false, RuleType), shapeType(-1),
            argSize(0), argSource(NoArgs), arguments(nullptr),
            simpleRule(nullptr), mStackIndex(0), typeSignature(nullptr),
            parentSignature(nullptr) {};
        ~ASTruleSpecifier() override;
        int evaluate(double* r, int size, RendererAST* = nullptr) const override;
        param_ptr evalArgs(RendererAST* = nullptr, const StackRule* sr = nullptr) const override;
        void entropy(std::string& e) const override;
        ASTexpression* simplify() override;
        ASTexpression* compile(CompilePhase ph) override;
        void grab(const ASTruleSpecifier* src);
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
        void entropy(std::string& e) const override;
        ASTexpression* simplify() override;
        ASTexpression* compile(CompilePhase ph) override;
    };
    class ASTcons : public ASTexpression {
    public:
        ASTexpArray children;
        ASTcons() = delete;
        ASTcons(std::initializer_list<ASTexpression*> kids);
        ~ASTcons() override;
        int evaluate(double* r, int size, RendererAST* = nullptr) const override;
        void evaluate(Modification& m, bool shapeDest, RendererAST* r) const override;
        void entropy(std::string& e) const override;
        ASTexpression* simplify() override;
        ASTexpression* compile(CompilePhase ph) override;
        
        const ASTexpression* getChild(size_t i) const override;
        size_t size() const override { return children.size(); }
        ASTexpression* append(ASTexpression* sib) override;
    };
    class ASTreal : public ASTexpression {
    public:
        double value;
        std::string text;
        ASTreal() = delete;
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
        ~ASTreal() override = default;
        int evaluate(double* r, int size, RendererAST* = nullptr) const override;
        void entropy(std::string& e) const override;
    };
    class ASTvariable : public ASTexpression {
    public:
        int stringIndex;
        std::string text;
        int stackIndex;
        int count;
        bool isParameter;
        
        ASTvariable() = delete;
        ASTvariable(int stringNum, const std::string& str, const yy::location& loc);
        int evaluate(double* r, int size, RendererAST* = nullptr) const override;
        void evaluate(Modification& m, bool shapeDest, RendererAST* r) const override;
        void entropy(std::string& e) const override;
        ASTexpression* compile(CompilePhase ph) override;
    };
    class ASTuserFunction : public ASTexpression {
    public:
        int nameIndex;
        ASTdefine* definition;      // weak ptr
        exp_ptr arguments;
        bool isLet;
        
        ASTuserFunction(int name, ASTexpression* args, ASTdefine* func, const yy::location& nameLoc);
        ~ASTuserFunction() override = default;
        int evaluate(double* , int, RendererAST* = nullptr) const override;
        void evaluate(Modification& m, bool shapeDest, RendererAST* r) const override;
        param_ptr evalArgs(RendererAST* rti = nullptr, const StackRule* parent = nullptr) const override;
        void entropy(std::string&) const override;
        ASTexpression* simplify() override;
        ASTexpression* compile(CompilePhase ph) override;
    private:
        class StackSetup {
            friend class ASTuserFunction;
            StackSetup(const ASTuserFunction* func, RendererAST* rti);
            ~StackSetup();
            
            const ASTuserFunction*  mFunc;
            RendererAST*            mRTI;
            const StackType*        mOldTop;
            size_t                  mOldSize;
        };
    };
    class ASTlet : public ASTuserFunction {
        std::unique_ptr<ASTrepContainer> mDefinitions;
    public:
        ASTlet(cont_ptr args, def_ptr func, const yy::location& letLoc,
               const yy::location& defLoc);
        ~ASTlet() override;          // inherited definition ptr owns ASTdefine
        ASTexpression* simplify() override;
        ASTexpression* compile(CompilePhase ph) override;
    };
    class ASToperator : public ASTexpression {
    public:
        char op;
        int  tupleSize;
        exp_ptr left;
        exp_ptr right;
        ASToperator() = delete;
        ASToperator(char o, ASTexpression* l, ASTexpression* r);
        ~ASToperator() override = default;
        int evaluate(double* r, int size, RendererAST* = nullptr) const override;
        void entropy(std::string& e) const override;
        ASTexpression* simplify() override;
        ASTexpression* compile(CompilePhase ph) override;
    };
    class ASTparen : public ASTexpression {
    public:
        exp_ptr e;
        ASTparen() = delete;
        ASTparen(ASTexpression* e1) : ASTexpression(e1->where, e1->isConstant,
                                                    e1->isNatural,
                                                    e1->mType), e(e1)
        { };
        ~ASTparen() override = default;
        int evaluate(double* r, int size, RendererAST* = nullptr) const override;
        void evaluate(Modification& m, bool shapeDest, RendererAST* r) const override;
        param_ptr evalArgs(RendererAST* rti = nullptr, const StackRule* parent = nullptr) const override;
        void entropy(std::string& ent) const override;
        ASTexpression* simplify() override;
        ASTexpression* compile(CompilePhase ph) override;
    };

    class ASTmodTerm : public ASTexpression {
    public:
        enum modTypeEnum {  unknownType, x, y, z, xyz, transform, 
            size, sizexyz, rot, skew, flip, 
            zsize, hue, sat, bright, alpha, 
            hueTarg, satTarg, brightTarg, alphaTarg, 
            targHue, targSat, targBright, targAlpha,
            time, timescale, 
            stroke, param, x1, y1, x2, y2, xrad, yrad, modification };
        
        modTypeEnum modType;
        exp_ptr args;
        int argCount;
        
        ASTmodTerm(modTypeEnum t, ASTexpression* a, const yy::location& loc)
        : ASTexpression(loc, a->isConstant, false, ModType), modType(t), args(a), argCount(0) {};
        ASTmodTerm(modTypeEnum t, const std::string& ent, const yy::location& loc);
        ASTmodTerm(modTypeEnum t, const yy::location& loc)
        : ASTexpression(loc, true, false, ModType), modType(t), args(nullptr), argCount(0) {};
        ~ASTmodTerm() override = default;
        int evaluate(double* r, int size, RendererAST* = nullptr) const override;
        void evaluate(Modification& m, bool shapeDest, RendererAST*) const override;
        void entropy(std::string& e) const override;
        ASTexpression* simplify() override;
        ASTexpression* compile(CompilePhase ph) override;
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
        int             entropyIndex;
        bool            canonical;
        
        ASTmodification(const yy::location& loc)
        : ASTexpression(loc, true, false, ModType), modClass(NotAClass),
          entropyIndex(0), canonical(true) {}
        ASTmodification(const ASTmodification& m, const yy::location& loc);
        ASTmodification(mod_ptr m, const yy::location& loc);
        ~ASTmodification() override;
        int evaluate(double* r, int size, RendererAST* = nullptr) const override;
        void evaluate(Modification& m, bool shapeDest, RendererAST*) const override;
        ASTexpression* simplify() override;
        ASTexpression* compile(CompilePhase ph) override;
        void setVal(Modification& m, RendererAST* = nullptr) const;
        void addEntropy(const std::string& name);
        void evalConst();
        void makeCanonical();
        void grab(ASTmodification* m);
    };
    class ASTarray : public ASTexpression {
    public:
        int     mName;
        std::unique_ptr<double[]> mData;
        exp_ptr mArgs;
        int     mLength;
        int     mStride;
        int     mStackIndex;
        int     mCount;
        bool    isParameter;
        std::string entString;
        
        ASTarray(int nameIndex, exp_ptr args, const yy::location& loc, const std::string& name);
        ASTarray(const ASTarray&) = delete;
        ASTarray& operator=(const ASTarray&) = delete;
        ~ASTarray() override;
        int evaluate(double* r, int size, RendererAST* = nullptr) const override;
        void entropy(std::string& e) const override;
        ASTexpression* simplify() override;
        ASTexpression* compile(CompilePhase ph) override;
    };
    
    inline void Compile(exp_ptr& exp, CompilePhase ph)
    {
        if (!exp) return;
        ASTexpression* r = exp->compile(ph);
        if (r)
            exp.reset(r);
    }
    
    inline void Simplify(exp_ptr& exp)
    {
        if (!exp) return;
        ASTexpression* r = exp.release()->simplify();
        exp.reset(r);
    }
    
    inline ASTexpArray Extract(exp_ptr exp)
    // Extract children from exp, leaving it empty
    {
        if (ASTcons* c = dynamic_cast<ASTcons*>(exp.get())) {
            return std::move(c->children);
        } else {
            ASTexpArray ret;
            ret.emplace_back(std::move(exp));
            return ret;
        }
    }
}

#endif //INCLUDE_ASTEXPRESSION_H
