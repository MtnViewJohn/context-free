// astreplacement.cpp
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


#include "astreplacement.h"

#include "agg_basics.h"
#include "pathIterator.h"

#ifdef _MSC_VER
#include <intrin.h>
#pragma intrinsic(_InterlockedCompareExchange64)
#endif

namespace AST {
    
    const char* ASTpathOp::PathOpNames[9] = {
        "MOVETO",  "MOVEREL", 
        "LINETO",  "LINEREL", 
        "ARCTO",   "ARCREL", 
        "CURVETO", "CURVEREL", 
        "CLOSEPOLY"
    };
    
    CommandInfo::UIDtype ASTcompiledPath::GlobalPathUID = 1;
    
    static const ASTparameter zeroParam;
    
    const ASTrule* ASTrule::PrimitivePaths[primShape::numTypes] = { 0 };

    
    void
    ASTrepContainer::addParameter(const std::string& type, int index,
                                  const yy::location& typeLoc, const yy::location& nameLoc) 
    {
        mParameters.push_back(zeroParam);
        mParameters.back().mLocation = typeLoc + nameLoc;
        mParameters.back().init(type, index);
        mParameters.back().isParameter = true;
        mParameters.back().check(typeLoc, nameLoc);
    }
    
    ASTparameter&
    ASTrepContainer::addParameter(int index, ASTdefine* def,
                                  const yy::location& nameLoc, const yy::location& expLoc) 
    {
        mParameters.push_back(zeroParam);
        ASTparameter& b = mParameters.back();
        b.mLocation = nameLoc + expLoc;
        b.init(index, def);
        b.check(nameLoc, nameLoc);
        return b;
    }
    
    void
    ASTrepContainer::move(ASTrepContainer& to)
    {
        to.mPathOp = mPathOp;
        to.mRepType = mRepType;
        mBody.swap(to.mBody);
        mParameters.swap(to.mParameters);
        to.isGlobal = isGlobal;
        to.mStackCount = mStackCount;
    }
    
    ASTreplacement::ASTreplacement(ASTruleSpecifier& shapeSpec, const std::string& name, mod_ptr mods,
                                   const yy::location& loc, repElemListEnum t)
    : mShapeSpec(shapeSpec), mRepType(t), mPathOp(unknownPathop), 
      mChildChange(mods, loc), mLocation(loc)
    {
        mChildChange.addEntropy(name);
    }
    
    ASTreplacement::ASTreplacement(ASTruleSpecifier& shapeSpec, mod_ptr mods, 
                                   const yy::location& loc, repElemListEnum t)
    : mShapeSpec(shapeSpec), mRepType(t), mPathOp(unknownPathop), 
      mChildChange(mods, loc), mLocation(loc)
    {
    }
    
    ASTloop::ASTloop(int nameIndex, const std::string& name, const yy::location& nameLoc,
                     exp_ptr args, const yy::location& argsLoc,  
                     mod_ptr mods)
    : ASTreplacement(ASTruleSpecifier::Zero, mods, nameLoc + argsLoc, empty),
      mLoopArgs(NULL)
    {
        std::string ent(name);
        args->entropy(ent);
        mChildChange.addEntropy(ent);
        bool bodyNatural = false;
        bool finallyNatural = false;
        bool local = args->isLocal;
        
        if (args->isConstant) {
            setupLoop(mLoopData[0], mLoopData[1], mLoopData[2], args.get(), argsLoc);
            bodyNatural = mLoopData[0] == floor(mLoopData[0]) &&
                          mLoopData[1] == floor(mLoopData[1]) &&
                          mLoopData[2] == floor(mLoopData[2]) &&
                          mLoopData[0] >= 0.0 && mLoopData[1] >= 0.0 &&
                          mLoopData[0] < 9007199254740992. && 
                          mLoopData[1] < 9007199254740992.;
            finallyNatural = bodyNatural && mLoopData[1] + mLoopData[2] >= -1.0 &&
                mLoopData[1] + mLoopData[2] < 9007199254740992.;
        } else {
            int c = args->evaluate(0, 0);
            if (c < 1 || c > 3) {
                CfdgError::Error(argsLoc, "A loop must have one to three index parameters.");
            }
            
            mLoopArgs = args.release()->simplify();
            
            ASTexpression::iterator argi = mLoopArgs->begin();
            for (int i = 0; argi != mLoopArgs->end(); ++i, ++argi) {
                if (argi->evaluate(0, 0) != 1) {
                    bodyNatural = finallyNatural = false;
                    break;
                }
                
                switch (i) {
                    case 0:
                        if (argi->isNatural) {
                            bodyNatural = finallyNatural = true;
                        }
                        break;
                    case 2: {
                        // Special case: if 1st & 2nd args are natural and 3rd
                        // is -1 then that is ok
                        double step;
                        if (argi->isConstant && argi->evaluate(&step, 1) == 1 &&
                            step == -1)
                        {
                            break;
                        }
                    }   // else fall through
                    default:
                        if (!(argi->isNatural)) {
                            bodyNatural = finallyNatural = false;
                        }
                        break;
                }
            }
        }
        
        ASTexpression loopVar(nameLoc, false, bodyNatural, ASTexpression::NumericType);
        ASTdefine loopDef(name, exp_ptr(&loopVar), nameLoc);
        ASTparameter& bodyParam = mLoopBody.addParameter(nameIndex, &loopDef, 
                                                         nameLoc, nameLoc);
        bodyParam.isLoopIndex = true;
        bodyParam.isNatural = bodyNatural;
        bodyParam.isLocal = local;
        ASTparameter& finallyParam = mFinallyBody.addParameter(nameIndex, &loopDef, 
                                                               nameLoc, nameLoc);
        finallyParam.isLoopIndex = true;
        finallyParam.isNatural = finallyNatural;
        finallyParam.isLocal = local;
        loopDef.mExpression = 0;
    }
    
    ASTtransform::ASTtransform(const yy::location& loc)
    : ASTreplacement(ASTruleSpecifier::Zero, mod_ptr(), loc, empty), mClone(false)
    {
    }
    
    ASTdefine::ASTdefine(const std::string& name, exp_ptr e, const yy::location& loc) 
    : ASTreplacement(ASTruleSpecifier::Zero, mod_ptr(), loc, empty),
      mType(e->mType), isConstant(e->isConstant), mStackCount(0), mName(name),
      isFunction(false)
    {
        mTuplesize = e->mType == ASTexpression::NumericType ? e->evaluate(0, 0) : 1;
        mExpression = e.release()->simplify();
        // Set the Modification entropy to parameter name, not its own contents
        int i = 0;
        mChildChange.modData.mRand64Seed.init();
        mChildChange.modData.mRand64Seed.xorString(name.c_str(), i);
    }
    
    ASTdefine::ASTdefine(const std::string& name, mod_ptr e, const yy::location& loc) 
    : ASTreplacement(ASTruleSpecifier::Zero, e, loc, empty), mExpression(0), 
      mTuplesize(ModificationSize), mType(ASTexpression::ModType), 
      isConstant(mChildChange.modExp.empty()), mStackCount(0), mName(name),
      isFunction(false)
    {
        // Set the Modification entropy to parameter name, not its own contents
        int i = 0;
        mChildChange.modData.mRand64Seed.init();
        mChildChange.modData.mRand64Seed.xorString(name.c_str(), i);
    }
    
    void
    ASTloop::setupLoop(double& start, double& end, double& step, ASTexpression* e, 
                       const yy::location& loc, Renderer* rti)
    {
        double data[3];
        switch (e->evaluate(data, 3, rti)) {
        case 1:
            data[1] = data[0];
            data[0] = 0.0;
        case 2:
            data[2] = 1.0;
        case 3:
            break;
        default:
            CfdgError::Error(loc, "A loop must have one to three index parameters.");
            break;
        }
        start = data[0];
        end = data[1];
        step = data[2];
    }
    
    ASTif::ASTif(exp_ptr ifCond, const yy::location& condLoc)
    : ASTreplacement(ASTruleSpecifier::Zero, mod_ptr(), condLoc, empty), 
      mCondition(ifCond.release()->simplify())
    {
    }

    ASTswitch::ASTswitch(exp_ptr switchExp, const yy::location& expLoc)
    : ASTreplacement(ASTruleSpecifier::Zero, mod_ptr(), expLoc, empty), 
      mSwitchExp(switchExp.release()->simplify())
    {
    }
    
    void
    ASTswitch::unify()
    {
        if (mElseBody.mPathOp != mPathOp) mPathOp = unknownPathop;
        for (switchMap::iterator it = mCaseStatements.begin();
             it != mCaseStatements.end(); ++it)
        {
            if ((*it).second->mPathOp != mPathOp) mPathOp = unknownPathop;
        }
    }

    ASTrepContainer::~ASTrepContainer() 
    {
        for (ASTbody::iterator it = mBody.begin(); it != mBody.end(); ++it)
            delete *it;
        mBody.clear();
    }
    
    ASTcompiledPath::ASTcompiledPath()
    : mComplete(false), mUseTerminal(false), mParameters(NULL)
    {
        mPathUID = NextPathUID();
    }
    
    ASTpathOp::ASTpathOp(const std::string& s, exp_ptr a, const yy::location& loc)
    : ASTreplacement(ASTruleSpecifier::Zero, mod_ptr(), loc, op), mArguments(0), 
      mFlags(0), mArgCount(0)
    {
        for (int i = MOVETO; i <= CLOSEPOLY; ++i) {
            if (!(s.compare(PathOpNames[i]))) {
                mPathOp = (pathOpEnum)i;
                break;
            }
        }
        if (mPathOp == unknownPathop) {
            CfdgError::Error(loc, "Unknown path operation type");
        }
        
        checkArguments(a);
        pathDataConst();
    }
    
    ASTpathOp::ASTpathOp(const std::string& s, mod_ptr a, const yy::location& loc)
    : ASTreplacement(ASTruleSpecifier::Zero, mod_ptr(), loc, op), mArguments(0),
      mFlags(0), mArgCount(0)
    {
        for (int i = MOVETO; i <= CLOSEPOLY; ++i) {
            if (!(s.compare(PathOpNames[i]))) {
                mPathOp = (pathOpEnum)i;
                break;
            }
        }
        if (mPathOp == unknownPathop) {
            CfdgError::Error(loc, "Unknown path operation type");
        }
        
        makePositional(a);
        pathDataConst();
    }
    
    ASTpathCommand::ASTpathCommand(const std::string& s, mod_ptr mods, const yy::location& loc)
    :   ASTreplacement(ASTruleSpecifier::Zero, mods, loc, command), 
        mMiterLimit(4.0)
    {
        mChildChange.addEntropy(s);
        
        if (!(s.compare("FILL"))) {
            mChildChange.flags |= CF_FILL;
        } else if (!s.compare("STROKE")) {
            mChildChange.flags &= ~CF_FILL;
        } else {
            CfdgError::Error(loc, "Unknown path command/operation");
        }
        
        check4z();
    }
    
    ASTpathCommand::ASTpathCommand(const std::string& s, mod_ptr mods, 
                                   exp_ptr params, const yy::location& loc)
    :   ASTreplacement(ASTruleSpecifier::Zero, mods, loc, command), 
        mMiterLimit(4.0)
    {
        mChildChange.addEntropy(s);
        
        if (!(s.compare("FILL"))) {
            mChildChange.flags |= CF_FILL;
        } else if (!s.compare("STROKE")) {
            mChildChange.flags &= ~CF_FILL;
        } else {
            CfdgError::Error(loc, "Unknown path command/operation");
        }
        
        check4z();
        
        if (params.get() == NULL)
            return;
        
        ASTcons* c = dynamic_cast<ASTcons*>(params.get());
        
        if (params->current()->mType == ASTexpression::NumericType) {
            if (mChildChange.flags & CF_FILL)
                CfdgError::Warning(params->current()->where, "Stroke width only useful for STROKE commands");
            if (!params->current()->isConstant ||
                params->current()->evaluate(&(mChildChange.strokeWidth), 1) != 1)
            {
                ASTmodTerm* w = new ASTmodTerm(ASTmodTerm::stroke, params->current()->simplify(), loc);
                mChildChange.modExp.push_back(w);
                if (c) {
                    c->left = NULL;
                } else {
                    params.release();
                    return;
                }
            } else {
                if (!c)
                    return;     // deleting params
            }
        }
        
        if (c) {
            params.release();
            params.reset(c->right);
            c->right = NULL;
            delete c; c = NULL;
        }
        
        if (params->mType == ASTexpression::FlagType) {
            ASTreal* r = dynamic_cast<ASTreal*> (params.get());
            if (r) {
                int f = (int)(r->value);
                if (f & CF_JOIN_PRESENT)
                    mChildChange.flags &= ~CF_JOIN_MASK;
                if (f & CF_CAP_PRESENT)
                    mChildChange.flags &= ~CF_CAP_MASK;
                mChildChange.flags |= f;
                if ((mChildChange.flags & CF_FILL) && (f & (CF_JOIN_PRESENT | CF_CAP_PRESENT)))
                    CfdgError::Warning(params->where, "Stroke flags only useful for STROKE commands");
            } else {
                CfdgError::Error(params->where, "Flag expressions must be constant");
            }
        } else {
            CfdgError::Error(params->where, "Unexpected argument in path command");
        }
    }
    
    ASTreplacement::~ASTreplacement()
    {
    }
    
    ASTloop::~ASTloop()
    {
        delete mLoopArgs;
    }
    
    ASTif::~ASTif()
    {
        delete mCondition;
    }
    
    ASTswitch::~ASTswitch()
    {
        delete mSwitchExp;
        for (switchMap::iterator it = mCaseStatements.begin();
             it != mCaseStatements.end(); ++it)
        {
            delete (*it).second;
        }
        mCaseStatements.clear();
    }
    
    ASTrule::~ASTrule()
    {
        delete mCachedPath; mCachedPath = 0;
    }
    
    ASTtransform::~ASTtransform()
    {
        ClearMods(mModifications);
    }
    
    ASTpathOp::~ASTpathOp()
    {
        delete mArguments;
    }
    
    void 
    ASTreplacement::replaceShape(Shape& s, Renderer* r) const
    {
        if (mShapeSpec.argSource == ASTruleSpecifier::NoArgs) {
            s.mShapeType = mShapeSpec.shapeType;
            s.mParameters = NULL;
        } else {
            s.mParameters = mShapeSpec.evalArgs(r, s.mParameters);
            if (mShapeSpec.argSource == ASTruleSpecifier::SimpleParentArgs)
                s.mShapeType = mShapeSpec.shapeType;
            else
                s.mShapeType = s.mParameters->ruleHeader.mRuleName;
            if (s.mParameters->ruleHeader.mParamCount == 0)
                s.mParameters = NULL;
        }
    }
    
    void 
    ASTreplacement::replace(Shape& s, Renderer* r, double* width) const
    {
        int dummy;
        replaceShape(s, r);
        r->mCurrentSeed ^= mChildChange.modData.mRand64Seed;
        r->mCurrentSeed.bump();
        mChildChange.evaluate(s.mWorldState, 0, width, false, dummy, r);
        s.mAreaCache = s.mWorldState.area();
    }
    
    void
    ASTreplacement::traverse(const Shape& parent, bool tr, Renderer* r) const
    {
        Shape child = parent;
        switch (mRepType) {
            case replacement:
                replace(child, r);
                child.mWorldState.mRand64Seed = r->mCurrentSeed;
                child.mWorldState.mRand64Seed.bump();
                r->processShape(child);
                break;
            case op:
                if (!tr)
                    child.mWorldState.m_transform.reset();
            case mixed:
            case command:
                replace(child, r);
                r->processSubpath(child, tr || (mRepType == op), mRepType);
                break;
            default:
                throw CfdgError("Subpaths must be all path operation or all path command");
        }
    }
    
    void
    ASTloop::traverse(const Shape& parent, bool tr, Renderer* r) const
    {
        Shape loopChild = parent;
        bool opsOnly = (mLoopBody.mRepType | mFinallyBody.mRepType) == op;
        if (opsOnly && !tr)
            loopChild.mWorldState.m_transform.reset();
        double start, end, step;
        
        if (mLoopArgs) {
            r->mCurrentSeed ^= mChildChange.modData.mRand64Seed;
            setupLoop(start, end, step, mLoopArgs, mLocation, r);
        } else {
            start = mLoopData[0];
            end = mLoopData[1];
            step = mLoopData[2];
        }
        int dummy;
        StackType t = {start};
        const StackType* oldTop = r->mLogicalStackTop;
        r->mCFstack.push_back(t);
        StackType& index = r->mCFstack.back();
        r->mLogicalStackTop = &index + 1;
        for (;;) {
            if (step > 0.0) {
                if (index.number >= end)
                    break;
            } else {
                if (index.number <= end)
                    break;
            }
            mLoopBody.traverse(loopChild, tr || opsOnly, r);
            mChildChange.evaluate(loopChild.mWorldState, 0, 0, false, dummy, r);
            index.number += step;
        }
        mFinallyBody.traverse(loopChild, tr || opsOnly, r);
        r->mCFstack.pop_back();
        r->mLogicalStackTop = oldTop;
    }
    
    void
    ASTtransform::traverse(const Shape& parent, bool tr, Renderer* r) const
    {
        const Shape* saveClone = r->mCloneShape;
        if (mClone)
            r->mCloneShape = &parent;
        Shape transChild = parent;
        bool opsOnly = mBody.mRepType == op;
        if (opsOnly && !tr)
            transChild.mWorldState.m_transform.reset();
        
        int dummy;
        ModList::const_iterator it  = mModifications.begin(), 
                                eit = mModifications.end();
        for(; it != eit; ++it) {
            Shape child = transChild;
            (*it)->evaluate(child.mWorldState, 0, 0, false, dummy, r);
            mBody.traverse(child, opsOnly || tr, r);            
        }
        r->mCloneShape = saveClone;
    }
    
    void
    ASTif::traverse(const Shape& parent, bool tr, Renderer* r) const
    {
        double cond = 0.0;
        if (mCondition->evaluate(&cond, 1, r) != 1) {
            CfdgError::Error(mLocation, "Error evaluating if condition");
            return;
        }
        if (cond) mThenBody.traverse(parent, tr, r);
        else mElseBody.traverse(parent, tr, r);
    }
    
    void
    ASTswitch::traverse(const Shape& parent, bool tr, Renderer* r) const
    {
        double caseValue = 0.0;
        if (mSwitchExp->evaluate(&caseValue, 1, r) != 1) {
            CfdgError::Error(mLocation, "Error evaluating if condition");
            return;
        }
        
        switchMap::const_iterator it = mCaseStatements.find((int)floor(caseValue));
        if (it != mCaseStatements.end()) (*it).second->traverse(parent, tr, r);
        else mElseBody.traverse(parent, tr, r);
    }
    
    void
    ASTdefine::traverse(const Shape& p, bool tr, Renderer* r) const
    {
        static const StackType zero = {0.0};
        int s = (int)r->mCFstack.size();
        r->mCFstack.resize(s + mTuplesize, zero);
        r->mCurrentSeed ^= mChildChange.modData.mRand64Seed;
        StackType* dest = &(r->mCFstack[s]);
        
        switch (mType) {
            case ASTexpression::NumericType:
                if (mExpression->evaluate(&dest->number, mTuplesize, r) != mTuplesize)
                    CfdgError::Error(mExpression->where, 
                                   "Error evaluating parameters (too many or not enough).");
                break;
            case ASTexpression::ModType: {
                int dummy;
                Modification* smod = reinterpret_cast<Modification*> (dest);
                mChildChange.setVal(*smod, 0, 0, false, dummy, r);
                break;
            }
            case ASTexpression::RuleType:
                dest->rule = mExpression->evalArgs(r, p.mParameters);
                break;
            default:
                CfdgError::Error(mExpression->where, "Unimplemented parameter type.");
                break;
        }
        
        if (!(r->mCFstack.empty()))
            r->mLogicalStackTop = &(r->mCFstack.back()) + 1;
    }
    
    void
    ASTrule::traverse(const Shape& parent, bool tr, Renderer* r) const
    {
        r->mCurrentSeed = parent.mWorldState.mRand64Seed;
        
        if (isPath) {
            r->processPrimShape(parent, this);
        } else {
            mRuleBody.traverse(parent, tr, r, true);
            parent.releaseParams();
        }
    }
    
    void
    ASTshape::traverse(const Shape&, bool, Renderer*) const
    {
        CfdgError::Error(mLocation, "Tried to traverse ASTshape.");
    }
    
    void ASTpathOp::traverse(const Shape& s, bool tr, Renderer* r) const
    {
        if (r->mCurrentPath->mComplete) 
            return;
        double opData[6];
        pathData(opData, r);
        r->mCurrentPath->addPathOp(this, opData, s, tr, r);
    }
    
    void
    ASTpathCommand::traverse(const Shape& s, bool tr, Renderer* r) const
    {
        Shape child = s;
        double width = mChildChange.strokeWidth;
        replace(child, r, &width);
        
        CommandInfo* info = NULL;
        
        if (r->mCurrentPath->mComplete) {
            if (r->mCurrentCommand == r->mCurrentPath->mCommandInfo.end())
                CfdgError::Error(mLocation, "Not enough path commands in cache");
            info = &(*(r->mCurrentCommand++));
        } else {
            if (r->mCurrentPath->mPath.total_vertices() == 0)
                CfdgError::Error(mLocation, "Path commands must be preceeded by at least one path operation");
            
            r->mWantCommand = false;
            r->mCurrentPath->finish(false, r);

            mInfoCache.tryInit(r->mIndex, r->mCurrentPath, width, this);
            if (mInfoCache.mPathUID == r->mCurrentPath->mPathUID && 
                mInfoCache.mIndex   == r->mIndex) 
            {
                r->mCurrentPath->mCommandInfo.push_back(mInfoCache);
            } else {
                CommandInfo newCmd(r->mIndex, r->mCurrentPath, width, this);
                r->mCurrentPath->mCommandInfo.push_back(newCmd);
            }
            info = &(r->mCurrentPath->mCommandInfo.back());
        }

        r->processPathCommand(child, info);
    }
    
    void
    ASTrule::traversePath(const Shape& parent, Renderer* r) const
    {
        r->init();
        r->mCurrentSeed = parent.mWorldState.mRand64Seed;
        r->mRandUsed = false;
        
        ASTcompiledPath* savedPath = NULL;
        
        if (mCachedPath && StackRule::Equal(mCachedPath->mParameters, parent.mParameters)) {
            savedPath = r->mCurrentPath;
            r->mCurrentPath = mCachedPath;
            r->mCurrentCommand = mCachedPath->mCommandInfo.begin();
        }
        
        mRuleBody.traverse(parent, false, r, true);
        if (!r->mCurrentPath->mComplete)
            r->mCurrentPath->finish(true, r);
        if (r->mCurrentPath->mUseTerminal) 
            r->mCurrentPath->mTerminalCommand.traverse(parent, false, r);
        
        if (savedPath) {
            r->mCurrentPath = savedPath;
        } else {
            if (!(r->mRandUsed) && mCachedPath == NULL) {
                mCachedPath = r->mCurrentPath;
                mCachedPath->mComplete = true;
                if (parent.mParameters)
                    mCachedPath->mParameters = &(parent.mParameters->ruleHeader);
                r->mCurrentPath = new ASTcompiledPath();
            } else {
                r->mCurrentPath->mPath.remove_all();
                r->mCurrentPath->mCommandInfo.clear();
                r->mCurrentPath->mUseTerminal = false;
                r->mCurrentPath->mPathUID = ASTcompiledPath::NextPathUID();
            }
        }
    }
    
    void
    ASTcompiledPath::addPathOp(const ASTpathOp* pop, double data[6], const Shape& s, 
                               bool tr, Renderer* r)
    {
        // Process the parameters for ARCTO/ARCREL
        double radius_x = 0.0, radius_y = 0.0, angle = 0.0;
        bool sweep = (pop->mFlags & CF_ARC_CW) == 0;
        bool largeArc = (pop->mFlags & CF_ARC_LARGE) != 0;
        if (pop->mPathOp == ARCTO || pop->mPathOp == ARCREL) {
            if (pop->mArgCount == 5) {
                // If the radii are specified then use the ellipse ARCxx form
                radius_x = data[2];
                radius_y = data[3];
                angle = data[4] * 0.0174532925199;
            } else {
                // Otherwise use the circle ARCxx form
                radius_x = radius_y = data[2];
                angle = 0.0;
            }
            if (radius_x < 0.0 || radius_y < 0.0) {
                radius_x = fabs(radius_x);
                radius_y = fabs(radius_y);
                sweep = !sweep;
            }
        } else if (tr) {
            s.mWorldState.m_transform.transform(data + 0, data + 1);
            s.mWorldState.m_transform.transform(data + 2, data + 3);
            s.mWorldState.m_transform.transform(data + 4, data + 5);
        }
        
        // If this is the first path operation following a path command then set the 
        // path index used by subsequent path commands to the path sequence that the
        // current path operation is part of. 
        // If this is not the first path operation following a path command then this
        // line does nothing.
        r->mIndex = r->mNextIndex;
        
        // If the op is anything other than a CLOSEPOLY then we are opening up a 
        // new path sequence.
        r->mClosed = false;
        r->mStop = false;
        
        // This new path op needs to be covered by a command, either from the cfdg
        // file or default.
        r->mWantCommand = true;
        
        if (pop->mPathOp == CLOSEPOLY) {
            if (mPath.total_vertices() > 1 && 
                agg::is_drawing(mPath.vertices().last_command()))
            {
                // Find the MOVETO/MOVEREL that is the start of the current path sequence
                // and reset LastPoint to that.
                unsigned last = mPath.total_vertices() - 1;
                unsigned cmd = agg::path_cmd_stop;
                for (unsigned i = last - 1; 
                     i < last && agg::is_vertex(cmd = mPath.command(i)); 
                     --i) 
                {
                    if (agg::is_move_to(cmd)) {
                        mPath.vertex(i, &(r->mLastPoint.x), &(r->mLastPoint.y));
                        break;
                    }
                }
                
                if (!agg::is_move_to(cmd))
                    CfdgError::Error(pop->mLocation, "CLOSEPOLY: Unable to find a MOVETO/MOVEREL for start of path.");
                
                // If this is an aligning CLOSEPOLY then change the last vertex to
                // exactly match the first vertex in the path sequence
                if (pop->mFlags & CF_ALIGN) {
                    mPath.modify_vertex(last, r->mLastPoint.x, r->mLastPoint.y);
                }
            } else if (pop->mFlags & CF_ALIGN) {
                CfdgError::Error(pop->mLocation, "Nothing to align to.");
            }
            mPath.close_polygon();
            r->mClosed = true;
            r->mWantMoveTo = true;
            return;
        }
        
        // Insert an implicit MOVETO unless the pathOp is a MOVETO/MOVEREL
        if (r->mWantMoveTo && pop->mPathOp > MOVEREL) {
            r->mWantMoveTo = false;
            mPath.move_to(r->mLastPoint.x, r->mLastPoint.y);
        }
        
        switch (pop->mPathOp) {
            case MOVEREL:
                mPath.rel_to_abs(data + 0, data + 1);
            case MOVETO:
                mPath.move_to(data[0], data[1]);
                r->mWantMoveTo = false;
                break;
            case LINEREL:
                mPath.rel_to_abs(data + 0, data + 1);
            case LINETO:
                mPath.line_to(data[0], data[1]);
                break;
            case ARCREL:
                mPath.rel_to_abs(data + 0, data + 1);
            case ARCTO: {
                if (!agg::is_vertex(mPath.last_vertex(data + 2, data + 3)) ||
                    (tr && s.mWorldState.m_transform.determinant() < 1e-10))
                {
                    break;
                }
                
                // Transforming an arc as they are parameterized by AGG is VERY HARD.
                // So instead we insert the arc and then transform the bezier curves
                // that are used to approximate the arc. But first we have to inverse
                // transform the starting point to match the untransformed arc. 
                // Afterwards the starting point is restored to its original value.
                if (tr) {
                    unsigned start = mPath.total_vertices() - 1;
                    agg::trans_affine inverseTr = ~s.mWorldState.m_transform;
                    mPath.transform(inverseTr, start);
                    mPath.arc_to(radius_x, radius_y, angle, largeArc, sweep, data[0], data[1]);
                    mPath.modify_vertex(start, data[2], data[3]);
                    mPath.transform(s.mWorldState.m_transform, start + 1);
                } else {
                    mPath.arc_to(radius_x, radius_y, angle, largeArc, sweep, data[0], data[1]);
                }
                break;
            }
            case CURVEREL:
                mPath.rel_to_abs(data + 0, data + 1);
                mPath.rel_to_abs(data + 2, data + 3);
                mPath.rel_to_abs(data + 4, data + 5);
            case CURVETO:
                if ((pop->mFlags & CF_CONTINUOUS) &&
                    !agg::is_curve(mPath.last_vertex(data + 4, data + 5)))
                {
                    CfdgError::Error(pop->mLocation, "Smooth curve operations must be preceded by another curve operation.");
                    break;
                }
                switch (pop->mArgCount) {
                    case 2:
                        mPath.curve3(data[0], data[1]);
                        break;
                    case 4:
                        if (pop->mFlags & CF_CONTINUOUS)
                            mPath.curve4(data[2], data[3], data[0], data[1]);
                        else
                            mPath.curve3(data[2], data[3], data[0], data[1]);
                        break;
                    case 6:
                        mPath.curve4(data[2], data[3], data[4], data[5], data[0], data[1]);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        
        mPath.last_vertex(&(r->mLastPoint.x), &(r->mLastPoint.y));
    }
    
    void
    ASTcompiledPath::finish(bool setAttr, Renderer* r)
    {
        // Close and end the last path sequence if it wasn't already closed and ended
        if (!r->mClosed) {
            mPath.end_poly(0);
            r->mClosed = true;
        }
        
        if (!r->mStop) {
            mPath.start_new_path();
            r->mStop = true;
        }
        
        r->mWantMoveTo = true;
        r->mNextIndex = mPath.total_vertices();
        
        // If setAttr is true then make sure that the last path sequence has a path
        // attribute associated with it. 
        if (setAttr && r->mWantCommand) {
            mUseTerminal = true;
            r->mWantCommand = false;
        }
    }
    
    CommandInfo::UIDtype
    ASTcompiledPath::NextPathUID()
    {
#ifdef _MSC_VER
        do {
            __int64 from = (__int64)GlobalPathUID;
            __int64 next = from + 1;
            if (_InterlockedCompareExchange64((__int64*)(&GlobalPathUID), next, from) == from)
                return (uint64_t)next;
        } while (true);
#else
        return __sync_fetch_and_add(&GlobalPathUID, (CommandInfo::UIDtype)1);
#endif
    }
    
    bool
    ASTrule::compareLT(const ASTrule* a, const ASTrule* b)
    {
        return  (a->mNameIndex == b->mNameIndex) ? 
        (a->mWeight < b->mWeight) : (a->mNameIndex < b->mNameIndex);
    }
    
    void
    ASTpathOp::pathData(double* data, Renderer* rti) const
    {
        if (mArguments) {
            if (mArguments->evaluate(data, 7, rti) < 0)
                CfdgError::Error(mArguments->where, "Cannot evaluate arguments");
        } else {
            const double* cdata = reinterpret_cast<const double*> (&mChildChange);
            for (int i = 0; i < mArgCount; ++i)
                data[i] = cdata[i];
        }
    }
    
    void
    ASTpathOp::pathDataConst()
    {
        if (mArguments && mArguments->isConstant) {
            double* data = reinterpret_cast<double*> (&mChildChange);
            if (mArguments->evaluate(data, 7) < 0)
                CfdgError::Error(mArguments->where, "Cannot evaluate arguments");
            delete mArguments;
            mArguments = NULL;
        }
    }

    void
    ASTpathOp::checkArguments(exp_ptr a)
    {
        if (a.get()) {
            mArguments = a.release()->simplify();
            mArgCount = mArguments->evaluate(0, 0);
        }

        for (ASTexpression* temp = mArguments; temp; temp = temp->next())
            switch (temp->current()->mType) {
                case ASTexpression::FlagType: {
                    if (temp->next())
                        CfdgError::Error(temp->current()->where, "Flags must be the last argument");
                    ASTreal* rf = dynamic_cast<ASTreal*> (temp->current());
                    if (rf)
                        mFlags = (int)(rf->value);
                    else
                        CfdgError::Error(temp->current()->where, "Flag expressions must be constant");
                    --mArgCount;
                    break;
                }
                case ASTexpression::NumericType:
                    break;
                default:
                    CfdgError::Error(temp->current()->where, "Path operation arguments must be numeric expressions or flags");
                    break;
            }
        
        switch (mPathOp) {
            case LINETO:
            case LINEREL:
            case MOVETO:
            case MOVEREL:
                if (mArgCount != 2)
                    CfdgError::Error(mLocation, "Move/line path operation requires two arguments");
                break;
            case ARCTO:
            case ARCREL:
                if (mArgCount != 3 && mArgCount != 5)
                    CfdgError::Error(mLocation, "Arc path operations require three or five arguments");
                break;
            case CURVETO:
            case CURVEREL:
                if (mFlags & CF_CONTINUOUS) {
                    if (mArgCount != 2 && mArgCount != 4)
                        CfdgError::Error(mLocation, "Continuous curve path operations require two or four arguments");
                } else {
                    if (mArgCount != 4 && mArgCount != 6)
                        CfdgError::Error(mLocation, "Non-continuous curve path operations require four or six arguments");
                }
                break;
            case CLOSEPOLY:
                if (mArgCount)
                    CfdgError::Error(mLocation, "CLOSEPOLY takes no arguments, only flags");
                break;
            default:
                break;
        }
    }
    
    static ASTexpression*
    parseXY(exp_ptr ax, exp_ptr ay, double def, const yy::location& loc)
    {
        if (!ax.get())
            ax.reset(new ASTreal(def, loc));
        int sz = ax->evaluate(0, 0);
        
        if (sz == 1 && !ay.get())
            ay.reset(new ASTreal(def, loc));
        
        if (ay.get())
            sz += ay->evaluate(0, 0);
        
        if (sz != 2)
            CfdgError::Error(loc, "Error parsing path operation arguments");
        
        if (ay.get())
            return new ASTcons(ax.release(), ay.release());
        return ax.release();
    }
    
    static void
    rejectTerm(exp_ptr term)
    {
        if (term.get())
            CfdgError::Error(term->where, "Illegal argument");
        // and delete it
    }
    
    void
    ASTpathOp::makePositional(mod_ptr a)
    {
        exp_ptr ax;
        exp_ptr ay;
        exp_ptr ax1;
        exp_ptr ay1;
        exp_ptr ax2;
        exp_ptr ay2;
        exp_ptr arx;
        exp_ptr ary;
        exp_ptr ar;
        
        for (ASTexpArray::iterator it = a->modExp.begin(); it != a->modExp.end(); ++it) {
            ASTmodTerm* mod = dynamic_cast<ASTmodTerm*> (*it);
            
            switch (mod ? mod->modType : ASTmodTerm::unknownType) {
                case ASTmodTerm::x:
                    ax.reset(mod->args->simplify());
                    mod->args = NULL;
                    break;
                case ASTmodTerm::y:
                    ay.reset(mod->args->simplify());
                    mod->args = NULL;
                    break;
                case ASTmodTerm::x1:
                    ax1.reset(mod->args->simplify());
                    mod->args = NULL;
                    break;
                case ASTmodTerm::y1:
                    ay1.reset(mod->args->simplify());
                    mod->args = NULL;
                    break;
                case ASTmodTerm::x2:
                    ax2.reset(mod->args->simplify());
                    mod->args = NULL;
                    break;
                case ASTmodTerm::y2:
                    ay2.reset(mod->args->simplify());
                    mod->args = NULL;
                    break;
                case ASTmodTerm::xrad:
                    arx.reset(mod->args->simplify());
                    mod->args = NULL;
                    break;
                case ASTmodTerm::yrad:
                    ary.reset(mod->args->simplify());
                    mod->args = NULL;
                    break;
                case ASTmodTerm::rot:
                    ar.reset(mod->args->simplify());
                    mod->args = NULL;
                    break;
                case ASTmodTerm::param:
                    if (mod->entString.find("large") != std::string::npos)  mFlags |= CF_ARC_LARGE;
                    if (mod->entString.find("cw") != std::string::npos)     mFlags |= CF_ARC_CW;
                    if (mod->entString.find("align") != std::string::npos)  mFlags |= CF_ALIGN;
                    break;
                case ASTmodTerm::Entropy:
                    break;
                case ASTmodTerm::unknownType:
                    CfdgError::Error((*it)->where, "Unrecognized element in a path operation");
                    break;
                default:
                    CfdgError::Error(mod->where, "Unrecognized element in a path operation");
                    break;
            }
        }
        
        ASTexpression* xy = 0;
        if (mPathOp != CLOSEPOLY) {
            xy = parseXY(ax, ay, 0.0, mLocation);
        } 
        
        switch (mPathOp) {
            case LINETO:
            case LINEREL:
            case MOVETO:
            case MOVEREL:
                rejectTerm(ar);
                rejectTerm(arx);
                rejectTerm(ary);
                rejectTerm(ax1);
                rejectTerm(ay1);
                rejectTerm(ax2);
                rejectTerm(ay2);
                
                mArguments = xy;
                break;
            case ARCTO:
            case ARCREL:
                rejectTerm(ax1);
                rejectTerm(ay1);
                rejectTerm(ax2);
                rejectTerm(ay2);
                
                if (arx.get() || ary.get()) {
                    ASTexpression* rxy = parseXY(arx, ary, 1, mLocation);
                    ASTexpression* angle = ar.release();
                    if (!angle)
                        angle = new ASTreal(0.0, mLocation);
                    
                    if (angle->evaluate(0, 0) != 1)
                        CfdgError(angle->where, "Arc angle must be a scalar value");
                    
                    mArguments = new ASTcons(xy, new ASTcons(rxy, angle));
                } else {
                    ASTexpression* radius = ar.release();
                    if (!radius)
                        radius = new ASTreal(1.0, mLocation);
                    
                    if (radius->evaluate(0, 0) != 1)
                        CfdgError::Error(radius->where, "Arc radius must be a scalar value");
                    
                    mArguments = new ASTcons(xy, radius);
                } 
                break;
            case CURVETO:
            case CURVEREL: {
                rejectTerm(ar);
                rejectTerm(arx);
                rejectTerm(ary);
                
                ASTexpression *xy1 = 0, *xy2 = 0;
                if (ax1.get() || ay1.get()) {
                    xy1 = parseXY(ax1, ay1, 0.0, mLocation);
                } else {
                    mFlags |= CF_CONTINUOUS;
                }
                if (ax2.get() || ay2.get()) {
                    xy2 = parseXY(ax2, ay2, 0.0, mLocation);
                }
                
                if (xy1 || xy2)
                    xy1 = ASTcons::Cons(xy1, xy2);
                mArguments = ASTcons::Cons(xy, xy1);
                break;
            }
            case CLOSEPOLY:
                rejectTerm(ax);
                rejectTerm(ay);
                rejectTerm(ar);
                rejectTerm(arx);
                rejectTerm(ary);
                rejectTerm(ax1);
                rejectTerm(ay1);
                rejectTerm(ax2);
                rejectTerm(ay2);
                break;
            default:
                break;
        } 
        
        mArgCount = mArguments ? mArguments->evaluate(0, 0) : 0;
    }
    
    void
    ASTtransform::ClearMods(ModList &m)
    {
        ModList::iterator it = m.begin(), eit = m.end();
        for (; it != eit; ++it)
            delete *it;
        m.clear();
    }
    
    void
    ASTpathCommand::check4z() const
    {
        if (mChildChange.modData.m_Z.tz != 0.0) {
            CfdgError::Warning(mLocation, "Z changes are not supported within paths");
            return;
        }
        for (ASTexpArray::const_iterator it = mChildChange.modExp.begin(), 
             eit = mChildChange.modExp.end(); it != eit; ++it)
        {
            ASTmodTerm* m = dynamic_cast<ASTmodTerm*>(*it);
            if (m && m->modType == ASTmodTerm::z) {
                CfdgError::Warning((*it)->where, "Z changes are not supported within paths");
                return;
            }
        }
    }
}
