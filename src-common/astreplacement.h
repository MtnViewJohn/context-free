// astreplacement.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2011 John Horigan - john@glyphic.com
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
#include "shape.h"
#include "primShape.h"
#include <string>
#include <map>
#include "CmdInfo.h"
#include "agg_path_storage.h"

namespace agg {
    struct trans_affine;
}

struct StackRule;

namespace AST {
    class ASTreplacement {
    public:
        enum repElemListEnum { rule = 8, replacement = 4, mixed = 3, command = 2, op = 1, empty = 0 };
        ASTruleSpecifier mShapeSpec;
        int mRepType;
        pathOpEnum mPathOp;
        ASTmodification mChildChange;
        yy::location mLocation;
        void replace(Shape& s, Renderer* r, double* width = NULL) const;
        void replaceShape(Shape& s, Renderer* r) const;
        
        ASTreplacement(ASTruleSpecifier& shapeSpec, const std::string& name, mod_ptr mods, 
                       const yy::location& loc = CfdgError::Default,
                       repElemListEnum t = replacement);
        ASTreplacement(ASTruleSpecifier& shapeSpec, mod_ptr mods, 
                       const yy::location& loc = CfdgError::Default,
                       repElemListEnum t = replacement);
        virtual ~ASTreplacement();
        virtual void traverse(const Shape& parent, bool tr, Renderer* r) const;
    private:
        ASTreplacement(const ASTreplacement&);
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
        ~ASTrepContainer();
        void traverse(const Shape& parent, bool tr, Renderer* r,
                      bool getParams = false) const
        {
            size_t s = r->mCFstack.size();
            if (getParams && parent.mParameters)
                r->initStack(parent.mParameters);
            for (AST::ASTbody::const_iterator it = mBody.begin(); it != mBody.end(); ++it) {
                (*it)->traverse(parent, tr, r);
            }
            r->unwindStack(s, mParameters);
        }
        void addParameter(const std::string& type, int index, 
                          const yy::location& typeLoc, const yy::location& nameLoc);
        ASTparameter& addParameter(int index, ASTdefine* def,
                          const yy::location& nameLoc, const yy::location& expLoc);
        void move(ASTrepContainer& to);
    };
    class ASTloop: public ASTreplacement {
    public:
        ASTexpression* mLoopArgs;
        double  mLoopData[3];
        ASTrepContainer mLoopBody;
        ASTrepContainer mFinallyBody;
        
        static void setupLoop(double& start, double& end, double& step, 
                              ASTexpression* e, const yy::location& loc,
                              Renderer* rti = 0);
        
        ASTloop(int nameIndex, const std::string& name, const yy::location& nameLoc,
                exp_ptr args, const yy::location& argsLoc,
                mod_ptr mods);
        virtual ~ASTloop();
        virtual void traverse(const Shape& parent, bool tr, Renderer* r) const;
    };
    class ASTtransform: public ASTreplacement {
    public:
        ASTrepContainer mBody;
        
        ASTtransform(mod_ptr mods, const yy::location& loc);
        virtual void traverse(const Shape& parent, bool tr, Renderer* r) const;
    };
    class ASTif: public ASTreplacement {
    public:
        ASTexpression* mCondition;
        ASTrepContainer mThenBody;
        ASTrepContainer mElseBody;
        
        ASTif(exp_ptr ifCond, const yy::location& condLoc);
        virtual ~ASTif();
        virtual void traverse(const Shape& parent, bool tr, Renderer* r) const;
    };
    class ASTswitch: public ASTreplacement {
    public:
        typedef std::map<int, ASTrepContainer*> switchMap;
        
        ASTexpression* mSwitchExp;
        switchMap mCaseStatements;
        ASTrepContainer mElseBody;
        
        ASTswitch(exp_ptr switchExp, const yy::location& expLoc);
        virtual ~ASTswitch();
        virtual void traverse(const Shape& parent, bool tr, Renderer* r) const;
        
        void unify();
    };
    class ASTdefine : public ASTreplacement {
    public:
        ASTexpression* mExpression;
        int mTuplesize;
        ASTexpression::expType mType;
        bool isConstant;
        ASTparameters mParameters;
        unsigned mStackCount;
        std::string mName;
        bool isFunction;
        
        ASTdefine(const std::string& name, exp_ptr e, const yy::location& loc);
        ASTdefine(const std::string& name, mod_ptr m, const yy::location& loc);
        virtual void traverse(const Shape& parent, bool tr, Renderer* r) const;
        virtual ~ASTdefine() { delete mExpression; }
	private:
		ASTdefine& operator=(const ASTdefine&);
    };
    class ASTrule : public ASTreplacement {
    public:
        enum WeightTypes { NoWeight = 1, PercentWeight = 2, ExplicitWeight = 4};
        ASTrepContainer mRuleBody;
        mutable ASTcompiledPath* mCachedPath;
        double mWeight;
        bool isPath;
        int mNameIndex;
        WeightTypes weightType;
        
        static const ASTrule* PrimitivePaths[primShape::numTypes];
        static bool compareLT(const ASTrule* a, const ASTrule* b);
        
        ASTrule(int ruleIndex, double weight, bool percent, const yy::location& loc)
        : ASTreplacement(ASTruleSpecifier::Zero, mod_ptr(), loc, rule), mCachedPath(NULL),
        mWeight(weight <= 0.0 ? 1.0 : weight), isPath(false), mNameIndex(ruleIndex),
        weightType(percent ? PercentWeight : ExplicitWeight) { };
        ASTrule(int ruleIndex, const yy::location& loc)
        : ASTreplacement(ASTruleSpecifier::Zero, mod_ptr(), loc, rule), mCachedPath(NULL),
        mWeight(1.0), isPath(false), mNameIndex(ruleIndex), weightType(NoWeight) { };
        virtual ~ASTrule();
        void traversePath(const Shape& parent, Renderer* r) const;
        virtual void traverse(const Shape& parent, bool tr, Renderer* r) const;
    };
    class ASTshape : public ASTreplacement {
    public:
        ASTrepContainer mRules;
        bool isPath;
        int mNameIndex;
        
        ASTshape(ASTruleSpecifier& r, bool path, const yy::location& loc) 
        : ASTreplacement(r, mod_ptr(), loc, empty), isPath(path), mNameIndex(r.shapeType)
        { mRules.isGlobal = true; }
        virtual void traverse(const Shape& parent, bool tr, Renderer* r) const;
    };
    class ASTpathOp : public ASTreplacement {
    public:
        ASTexpression* mArguments[6];
        int mFlags;
        int mArgCount;
        
        static const char*  PathOpNames[9];
        
        ASTpathOp(const std::string& s, exp_ptr a, bool positional, 
                  const yy::location& loc);
        ~ASTpathOp();
        virtual void traverse(const Shape& parent, bool tr, Renderer* r) const;
    private:
        void pathData(double* data, Renderer* rti) const;
        void pathDataConst(ASTexpArray& result);
        void parseXY(ASTexpArray& result, ASTmodTerm* ax, ASTmodTerm* ay, 
                     double def, unsigned total);
        void makePositional(ASTexpArray& result, exp_ptr a);
        void checkArguments(ASTexpArray& result, exp_ptr a);
    };
    class ASTpathCommand : public ASTreplacement {
    public:
        double              mMiterLimit;
        
        // Empty constructor
        ASTpathCommand() :
        ASTreplacement(ASTruleSpecifier::Zero, mod_ptr()),
        mMiterLimit(4.0)
        {
        }
        
        ASTpathCommand(const std::string& s, mod_ptr mods, const yy::location& loc);
        ASTpathCommand(const std::string& s, mod_ptr mods, exp_ptr params, 
                       const yy::location& loc);
        
        virtual void traverse(const Shape& parent, bool tr, Renderer* r) const;
    private:
        mutable CommandInfo mInfoCache;
    };
    class ASTcompiledPath {
    public:
        bool mComplete;
        agg::path_storage mPath;
        InfoCache mCommandInfo;
        ASTpathCommand mTerminalCommand;
        bool mUseTerminal;
        const StackRule* mParameters;
        CommandInfo::UIDtype mPathUID;
        
        void finish(bool setAttr, Renderer* r);
        void addPathOp(const ASTpathOp* pop, double data[6], const Shape& s, 
                       bool tr, Renderer* r);
        
        ASTcompiledPath();
        static CommandInfo::UIDtype NextPathUID();
    private:
        static CommandInfo::UIDtype GlobalPathUID;
    };
}
#endif //INCLUDE_ASTREPLACEMENT_H
