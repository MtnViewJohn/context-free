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
#include "CmdInfo.h"
#include "agg_path_storage.h"

namespace agg {
    struct trans_affine;
}

struct StackRule;
class Builder;

namespace AST {
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
        ASTreplacement(ASTruleSpecifier&& shapeSpec, mod_ptr mods,
                       const yy::location& loc = CfdgError::Default,
                       repElemListEnum t = replacement);
        ASTreplacement(mod_ptr mods, const yy::location& loc = CfdgError::Default,
                       repElemListEnum t = replacement);
        ASTreplacement(const std::string& s, const yy::location& loc);
        virtual ~ASTreplacement();
        virtual void traverse(const Shape& parent, bool tr, RendererAST* r) const;
        virtual void compile(CompilePhase ph);
    };
    class ASTrepContainer {
    public:
        pathOpEnum mPathOp;
        int mRepType;
        ASTbody mBody;
        ASTparameters mParameters;
        bool isGlobal;
        unsigned mStackCount;
        
        ASTrepContainer() 
        : mPathOp(unknownPathop), mRepType(ASTreplacement::empty),
          isGlobal(false), mStackCount(0) {};
        ASTrepContainer(const ASTrepContainer&) = delete;
        ASTrepContainer& operator=(const ASTrepContainer&) = delete;
        ASTrepContainer(ASTrepContainer&&) = delete;
        ~ASTrepContainer();
        void traverse(const Shape& parent, bool tr, RendererAST* r,
                      bool getParams = false) const
        {
            size_t s = r->mStackSize;
            if (getParams && parent.mParameters)
                r->initStack(parent.mParameters.get());
            for (const rep_ptr& rep: mBody)
                rep->traverse(parent, tr, r);
            r->unwindStack(s, mParameters);
        }
        void compile(CompilePhase ph, ASTloop* loop = nullptr, ASTdefine* def = nullptr);
        void addParameter(const std::string& type, int index,
                          const yy::location& typeLoc, const yy::location& nameLoc);
        ASTparameter& addDefParameter(int index, ASTdefine* def,
                          const yy::location& nameLoc, const yy::location& expLoc);
        void addLoopParameter(int index, bool natural, bool local,
                              const yy::location& nameLoc);
    };
    class ASTloop: public ASTreplacement {
    public:
        exp_ptr mLoopArgs;
        mod_ptr mLoopModHolder;
        double  mLoopData[3];
        ASTrepContainer mLoopBody;
        ASTrepContainer mFinallyBody;
        int mLoopIndexName;
        std::string mLoopName;
        
        static void setupLoop(double& start, double& end, double& step, 
                              const ASTexpression* e, const yy::location& loc,
                              RendererAST* rti = nullptr);
        
        ASTloop(int nameIndex, const std::string& name, const yy::location& nameLoc,
                exp_ptr args, const yy::location& argsLoc,
                mod_ptr mods);
        ~ASTloop() override;
        void traverse(const Shape& parent, bool tr, RendererAST* r) const override;
        void compile(CompilePhase ph) override;
        void compileLoopMod();
    };
    class ASTtransform: public ASTreplacement {
    public:
        ASTrepContainer mBody;
        exp_ptr mExpHolder;              // strong pointer
        bool mClone;
        
        ASTtransform(const yy::location& loc, exp_ptr mods);
        ~ASTtransform() override;
        void traverse(const Shape& parent, bool tr, RendererAST* r) const override;
        void compile(CompilePhase ph) override;
    };
    class ASTif: public ASTreplacement {
    public:
        exp_ptr mCondition;
        ASTrepContainer mThenBody;
        ASTrepContainer mElseBody;
        
        ASTif(exp_ptr ifCond, const yy::location& condLoc);
        ~ASTif() override;
        void traverse(const Shape& parent, bool tr, RendererAST* r) const override;
        void compile(CompilePhase ph) override;
    };
    class ASTswitch: public ASTreplacement {
    public:
        typedef std::map<int, cont_ptr> switchMap;
        
        exp_ptr mSwitchExp;
        switchMap mCaseStatements;
        ASTrepContainer mElseBody;
        
        ASTswitch(exp_ptr switchExp, const yy::location& expLoc);
        ~ASTswitch() override;
        void traverse(const Shape& parent, bool tr, RendererAST* r) const override;
        void compile(CompilePhase ph) override;
        
        void unify();
    };
    class ASTdefine : public ASTreplacement {
    public:
        enum define_t { StackDefine, ConstDefine, ConfigDefine, FunctionDefine, LetDefine };
        define_t mDefineType;
        exp_ptr mExpression;
        int mTuplesize;
        AST::expType mType;
        bool isNatural;
        ASTparameters mParameters;
        unsigned mStackCount;
        std::string mName;
        int mConfigDepth;
        
        ASTdefine(const std::string& name, const yy::location& loc);
        void traverse(const Shape& parent, bool tr, RendererAST* r) const override;
        void compile(CompilePhase ph) override;
        ~ASTdefine() override = default;
        ASTdefine& operator=(const ASTdefine&) = delete;
    };
    class ASTrule : public ASTreplacement {
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
        ~ASTrule() override;
        void traversePath(const Shape& parent, RendererAST* r) const;
        void traverse(const Shape& parent, bool tr, RendererAST* r) const override;
        void compile(CompilePhase ph) override;
    };
    class ASTpathOp : public ASTreplacement {
    public:
        exp_ptr mArguments;
        mod_ptr mOldStyleArguments;
        int mArgCount;
        int mFlags;
        
        ASTpathOp(const std::string& s, mod_ptr a, const yy::location& loc);
        ASTpathOp(const std::string& s, exp_ptr a, const yy::location& loc);
        ~ASTpathOp() override;
        void traverse(const Shape& parent, bool tr, RendererAST* r) const override;
        void compile(CompilePhase ph) override;
    private:
        void pathData(double* data, RendererAST* rti) const;
        void pathDataConst();
        void makePositional();
        void checkArguments();
    };
    class ASTpathCommand : public ASTreplacement {
    public:
        double  mMiterLimit;
        double  mStrokeWidth;
        exp_ptr mParameters;
        int     mFlags;
        
        // Empty constructor
        ASTpathCommand() :
        ASTreplacement(nullptr),
        mMiterLimit(4.0), mStrokeWidth(0.1), mParameters(nullptr),
        mFlags(CF_MITER_JOIN + CF_BUTT_CAP + CF_FILL)
        {
        }
        
        ASTpathCommand(const std::string& s, mod_ptr mods, exp_ptr params,
                       const yy::location& loc);
        
        void traverse(const Shape& parent, bool tr, RendererAST* r) const override;
        void compile(CompilePhase ph) override;
        ~ASTpathCommand() override = default;
    private:
        mutable CommandInfo mInfoCache;
    };
    class ASTcompiledPath {
    public:
        bool mCached;
        agg::path_storage mPath;
        InfoCache mCommandInfo;
        ASTpathCommand mTerminalCommand;
        bool mUseTerminal;
        param_ptr mParameters;
        CommandInfo::UIDtype mPathUID;
        
        void finish(bool setAttr, RendererAST* r);
        void addPathOp(const ASTpathOp* pop, double data[6], const Shape& s, 
                       bool tr, RendererAST* r);
        
        ASTcompiledPath();
        ~ASTcompiledPath();
        static UIDdatatype NextPathUID();
    private:
        static CommandInfo::UIDtype GlobalPathUID;
    };
}
#endif //INCLUDE_ASTREPLACEMENT_H
