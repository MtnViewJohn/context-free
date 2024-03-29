// astreplacement.h
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


#ifndef INCLUDE_ASTREPLACEMENT_H
#define INCLUDE_ASTREPLACEMENT_H

#include "ast.h"
#include "astexpression.h"
#include "location.hh"
#include "cfdg.h"
#include "rendererAST.h"
#include "shape.h"
#include "primShape.h"
#include <string>
#include <map>
#include <list>
#include <cstddef>
#include "CmdInfo.h"
#include "agg2/agg_path_storage.h"

#include "json_fwd.hpp"
using json = nlohmann::json;

namespace agg {
    struct trans_affine;
}

struct StackRule;
class Builder;

namespace AST {
    void to_json(json& j, const ASTparameter& m);
    
    class ASTreplacement {
    public:
        enum repElemListEnum { rule = 8, replacement = 4, mixed = 3, command = 2, op = 1, empty = 0 };
        ASTruleSpecifier mShapeSpec;
        int mRepType;
        pathOpEnum mPathOp;
        ASTmodification mChildChange;
        yy::location mLocation;
        void replace(Shape& s, RendererAST* r) const;
        
        ASTreplacement(const ASTreplacement&) = delete;
        ASTreplacement(ruleSpec_ptr shapeSpec, mod_ptr mods,
                       const yy::location& loc = CfdgError::Default,
                       repElemListEnum t = replacement) noexcept;
        ASTreplacement(mod_ptr mods, const yy::location& loc = CfdgError::Default,
                       repElemListEnum t = replacement);
        ASTreplacement(const std::string& s, const yy::location& loc);
        virtual ~ASTreplacement();
        virtual void traverse(const Shape& parent, bool tr, RendererAST* r) const;
        virtual void compile(CompilePhase ph, Builder* b);
        virtual void to_json(json& j) const;
    };

    void to_json(json& j, const ASTreplacement& p);
    
    class ASTrepContainer {
    public:
        pathOpEnum mPathOp = unknownPathop;
        int mRepType = ASTreplacement::empty;
        ASTbody mBody;
        ASTparameters mParameters;
        bool isGlobal = false;
        
        ASTrepContainer() = default;
        ASTrepContainer(const ASTrepContainer&) = delete;
        ASTrepContainer& operator=(const ASTrepContainer&) = delete;
        ASTrepContainer(ASTrepContainer&&) = delete;
        ~ASTrepContainer();
        void traverse(const Shape& parent, bool tr, RendererAST* r,
                      bool getParams = false) const
        {
            std::size_t s = r->mStackSize;
            if (getParams && parent.mParameters)
                r->initStack(parent.mParameters.get());
            for (const rep_ptr& rep: mBody)
                rep->traverse(parent, tr, r);
            r->unwindStack(s, mParameters);
        }
        void compile(CompilePhase ph, Builder* b, ASTloop* loop = nullptr, ASTdefine* def = nullptr);
        void addParameter(const std::string& type, int index,
                          const yy::location& typeLoc, const yy::location& nameLoc);
        ASTparameter& addDefParameter(int index, ASTdefine* def,
                          const yy::location& nameLoc, const yy::location& expLoc);
        void addLoopParameter(int index, const yy::location& nameLoc);
    };

    void to_json(json& j, const ASTrepContainer& p);
    
    class ASTloop final: public ASTreplacement {
    public:
        exp_ptr mLoopArgs;
        mod_ptr mLoopModHolder;
        std::array<double,3> mLoopData;
        ASTrepContainer mLoopBody;
        ASTrepContainer mFinallyBody;
        int mLoopIndexName;
        std::string mLoopName;
        
        static void setupLoop(double& start, double& end, double& step, 
                              const ASTexpression* e, RendererAST* rti = nullptr);
        
        ASTloop(int nameIndex, const std::string& name, const yy::location& nameLoc,
                exp_ptr args, const yy::location& argsLoc,
                mod_ptr mods);
        ~ASTloop() final;
        void traverse(const Shape& parent, bool tr, RendererAST* r) const final;
        void compile(CompilePhase ph, Builder* b) final;
        void compileLoopMod(Builder* b);
        void to_json(json& j) const final;
    };
    class ASTtransform final: public ASTreplacement {
    public:
        ASTrepContainer mBody;
        exp_ptr mExpHolder;              // strong pointer
        bool mClone;
        
        ASTtransform(const yy::location& loc, exp_ptr mods);
        ~ASTtransform() final;
        void traverse(const Shape& parent, bool tr, RendererAST* r) const final;
        void compile(CompilePhase ph, Builder* b) final;
        void to_json(json& j) const final;
    };
    class ASTif final: public ASTreplacement {
    public:
        exp_ptr mCondition;
        ASTrepContainer mThenBody;
        ASTrepContainer mElseBody;
        
        ASTif(exp_ptr ifCond, const yy::location& condLoc);
        ~ASTif() final;
        void traverse(const Shape& parent, bool tr, RendererAST* r) const final;
        void compile(CompilePhase ph, Builder* b) final;
        void to_json(json& j) const final;
    };

    class ASTswitch final: public ASTreplacement {
    public:
        using caseType = std::int64_t;
        using caseRange = std::pair<caseType, caseType>;
        struct compareRange {
            bool operator()(const caseRange& a, const caseRange& b) const {
                return a.second < b.first;
            }
        };
        using switchMap = std::map<caseRange, const ASTrepContainer*, compareRange>;
        
        exp_ptr mSwitchExp;
        switchMap mCaseMap;
        std::vector<std::pair<exp_ptr, cont_ptr>> mCases;
        ASTrepContainer mElseBody;
        
        ASTswitch(exp_ptr switchExp, const yy::location& expLoc);
        ~ASTswitch() final;
        void traverse(const Shape& parent, bool tr, RendererAST* r) const final;
        void compile(CompilePhase ph, Builder* b) final;
        
        void unify();
        void to_json(json& j) const final;
    };
    class ASTdefine final : public ASTreplacement {
    public:
        enum define_t { StackDefine, ConstDefine, ConfigDefine, FunctionDefine, LetDefine };
        define_t mDefineType;
        exp_ptr mExpression;
        int mTuplesize;
        AST::expType mType;
        bool isNatural;
        ASTparameters mParameters;
        unsigned mParamSize;
        std::string mName;
        int mConfigDepth;
        
        ASTdefine(std::string& name, const yy::location& loc);
        void traverse(const Shape& parent, bool tr, RendererAST* r) const final;
        void compile(CompilePhase ph, Builder* b) final;
        ~ASTdefine() final = default;
        ASTdefine& operator=(const ASTdefine&) = delete;
        void to_json(json& j) const final;
    };
    class ASTrule final : public ASTreplacement {
    public:
        enum WeightTypes { NoWeight = 1, PercentWeight = 2, ExplicitWeight = 4};
        ASTrepContainer mRuleBody;
        mutable cpath_ptr mCachedPath;
        double mWeight;
        bool isPath;
        int mNameIndex;
        WeightTypes weightType;
        
        static bool compareLT(const ASTrule* a, const ASTrule* b);
        
        ASTrule(int ruleIndex, double weight, bool percent, const yy::location& loc)
        : ASTreplacement(nullptr, loc, rule), mCachedPath(nullptr),
          mWeight(weight <= 0.0 ? 1.0 : weight), isPath(false), mNameIndex(ruleIndex),
          weightType(percent ? PercentWeight : ExplicitWeight) {
              if (weight <= 0.0)
                  CfdgError::Warning(loc, "Rule weight coerced to 1.0");
          };
        ASTrule(int ruleIndex, const yy::location& loc)
        : ASTreplacement(nullptr, loc, rule), mCachedPath(nullptr),
          mWeight(1.0), isPath(false), mNameIndex(ruleIndex), weightType(NoWeight) { };
        ASTrule(int i);
        ~ASTrule() final;
        void traversePath(const Shape& parent, RendererAST* r) const;
        void traverseRule(Shape& parent, RendererAST* r) const;
        void traverse(const Shape& parent, bool tr, RendererAST* r) const final;
        void compile(CompilePhase ph, Builder* b) final;
        void to_json(json& j) const final;
    };
    class ASTpathOp final : public ASTreplacement {
    public:
        using pathOpData = std::array<double, 6>;
        exp_ptr mArguments;
        mod_ptr mOldStyleArguments;
        int mArgCount;
        int mFlags;
        
        ASTpathOp(const std::string& s, mod_ptr a, const yy::location& loc);
        ASTpathOp(const std::string& s, exp_ptr a, const yy::location& loc);
        ~ASTpathOp() final;
        void traverse(const Shape& s, bool tr, RendererAST* r) const final;
        void compile(CompilePhase ph, Builder* b) final;
    private:
        void pathData(pathOpData& data, RendererAST* rti) const;
        void pathDataConst(Builder* b);
        void makePositional(Builder* b);
        void checkArguments(Builder* b);
    public:
        void to_json(json& j) const final;
    };
    class ASTpathCommand final : public ASTreplacement {
    public:
        double  mMiterLimit = DefaultMiterLimit;
        double  mStrokeWidth = DefaultStrokeWidth;
        exp_ptr mParameters;
        int     mFlags = CF_MITER_JOIN + CF_BUTT_CAP + CF_FILL;
        
        // Empty constructor
        ASTpathCommand() :
        ASTreplacement(nullptr)
        {
        }
        
        ASTpathCommand(const std::string& s, mod_ptr mods, exp_ptr params,
                       const yy::location& loc);
        
        void traverse(const Shape& s, bool tr, RendererAST* r) const final;
        void compile(CompilePhase ph, Builder* b) final;
        ~ASTpathCommand() final = default;
        void to_json(json& j) const final;
    private:
        mutable CommandInfo mInfoCache;
    };
    class ASTcompiledPath {
    public:
        bool mCached = false;
        agg::path_storage mPath;
        InfoCache mCommandInfo;
        ASTpathCommand mTerminalCommand;
        bool mUseTerminal = false;
        param_ptr mParameters;
        CommandInfo::UIDtype mPathUID;
        
        void finish(bool setAttr, RendererAST* r);
        void addPathOp(const ASTpathOp* pop, ASTpathOp::pathOpData& data, const Shape& s, 
                       bool tr, RendererAST* r);
        
        ASTcompiledPath();
        ~ASTcompiledPath();
        static UIDdatatype NextPathUID();
    private:
        static CommandInfo::UIDtype GlobalPathUID;
    };
}

#endif //INCLUDE_ASTREPLACEMENT_H
