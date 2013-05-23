// astreplacement.cpp
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


#include "astreplacement.h"

#include "agg_basics.h"
#include "pathIterator.h"
#include <cassert>
#include <atomic>
#include "rendererAST.h"
#include "builder.h"

namespace AST {
    
    const char* ASTpathOp::PathOpNames[9] = {
        "MOVETO",  "MOVEREL", 
        "LINETO",  "LINEREL", 
        "ARCTO",   "ARCREL", 
        "CURVETO", "CURVEREL", 
        "CLOSEPOLY"
    };
    
    CommandInfo::UIDtype ASTcompiledPath::GlobalPathUID(1);
    
    const ASTrule* ASTrule::PrimitivePaths[primShape::numTypes] = { nullptr };
    
    agg::trans_affine ASTtransform::Dummy;

    
    void
    ASTrepContainer::addParameter(const std::string& type, int index,
                                  const yy::location& typeLoc, const yy::location& nameLoc) 
    {
        mParameters.emplace_back(type, index, typeLoc + nameLoc);
        mParameters.back().isParameter = true;
        mParameters.back().checkParam(typeLoc, nameLoc);
        mStackCount += mParameters.back().mTuplesize;
    }
    
    ASTparameter&
    ASTrepContainer::addDefParameter(int index, ASTdefine* def,
                                     const yy::location& nameLoc,
                                     const yy::location& expLoc)
    {
        mParameters.emplace_back(index, def, nameLoc + expLoc);
        ASTparameter& b = mParameters.back();
        b.checkParam(nameLoc, nameLoc);
        return b;
    }
    
    void
    ASTrepContainer::addLoopParameter(int index, bool natural, bool local,
                                      const yy::location& nameLoc)
    {
        mParameters.emplace_back(index, natural, local, nameLoc);
        mParameters.back().checkParam(nameLoc, nameLoc);
        mStackCount += mParameters.back().mTuplesize;
    }
    
    void
    ASTrepContainer::compile(CompilePhase ph, ASTloop* loop, ASTdefine* def)
    {
        // Delete all of the incomplete parameters inserted during parse
        if (ph == CompilePhase::TypeCheck) {
            mStackCount = 0;
            for (size_t i = 0; i < mParameters.size(); ++i)
                if (mParameters[i].isParameter  || mParameters[i].isLoopIndex) {
                    mStackCount += mParameters[i].mTuplesize;
                } else {
                    mParameters.resize(i);
                    break;
                }
        }
        
        Builder::CurrentBuilder->push_repContainer(*this);
        if (loop)
            loop->compileBase(ph);
        for (auto& rep: mBody)
            rep->compile(ph);
        if (def)
            def->compile(ph);
        Builder::CurrentBuilder->pop_repContainer(nullptr);
    }

    
    ASTreplacement::ASTreplacement(ASTruleSpecifier& shapeSpec, const std::string& name, mod_ptr mods,
                                   const yy::location& loc, repElemListEnum t)
    : mShapeSpec(std::move(shapeSpec)), mRepType(t), mPathOp(unknownPathop),
      mChildChange(std::move(mods), loc), mLocation(loc)
    {
        mChildChange.addEntropy(name);
    }
    
    ASTreplacement::ASTreplacement(ASTruleSpecifier& shapeSpec, mod_ptr mods, 
                                   const yy::location& loc, repElemListEnum t)
    : mShapeSpec(std::move(shapeSpec)), mRepType(t), mPathOp(unknownPathop),
      mChildChange(std::move(mods), loc), mLocation(loc)
    {
    }
    
    ASTloop::ASTloop(int nameIndex, const std::string& name, const yy::location& nameLoc,
                     exp_ptr args, const yy::location& argsLoc,  
                     mod_ptr mods)
    : ASTreplacement(ASTruleSpecifier::Zero, std::move(mods), nameLoc + argsLoc, empty),
      mLoopArgs(std::move(args)), mLoopIndexName(nameIndex)
    {
        std::string ent(name);
        mLoopArgs->entropy(ent);
        mChildChange.addEntropy(ent);
        mLoopBody.addLoopParameter(mLoopIndexName, false, false, mLocation);
        mFinallyBody.addLoopParameter(mLoopIndexName, false, false, mLocation);
    }
    
    ASTtransform::ASTtransform(const yy::location& loc, exp_ptr mods)
    : ASTreplacement(ASTruleSpecifier::Zero, nullptr, loc, empty), mTransforms(),
      mModifications(getTransforms(mods.get(), mTransforms, nullptr, false, Dummy)),
      mExpHolder(std::move(mods)), mClone(false)
    {
    }
    
    ASTdefine::ASTdefine(const std::string& name, const yy::location& loc)
    : ASTreplacement(ASTruleSpecifier::Zero, nullptr, loc, empty),
      mType(NoType), isConstant(false), isNatural(false), mStackCount(0),
      mName(std::move(name)), isFunction(false), mConfigDepth(-1)
    {
        // Set the Modification entropy to parameter name, not its own contents
        int i = 0;
        mChildChange.modData.mRand64Seed.init();
        mChildChange.modData.mRand64Seed.xorString(name.c_str(), i);
    }
    
    void
    ASTloop::setupLoop(double& start, double& end, double& step, const ASTexpression* e,
                       const yy::location& loc, RendererAST* rti)
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
    : ASTreplacement(ASTruleSpecifier::Zero, nullptr, condLoc, empty),
      mCondition(std::move(ifCond))
    {
    }

    ASTswitch::ASTswitch(exp_ptr switchExp, const yy::location& expLoc)
    : ASTreplacement(ASTruleSpecifier::Zero, nullptr, expLoc, empty),
      mSwitchExp(std::move(switchExp))
    {
    }
    
    void
    ASTswitch::unify()
    {
        if (mElseBody.mPathOp != mPathOp) mPathOp = unknownPathop;
        for (switchMap::value_type& caseEntry: mCaseStatements)
            if (caseEntry.second->mPathOp != mPathOp)
                mPathOp = unknownPathop;
    }

    ASTrepContainer::~ASTrepContainer() 
    {
    }
    
    ASTcompiledPath::ASTcompiledPath()
    : mComplete(false), mUseTerminal(false), mParameters(nullptr)
    {
        mPathUID = NextPathUID();
    }
    
    ASTpathOp::ASTpathOp(const std::string& s, exp_ptr a, const yy::location& loc)
    : ASTreplacement(ASTruleSpecifier::Zero, nullptr, loc, op), mArguments(std::move(a)),
      mOldStyleArguments(nullptr), mFlags(0), mArgCount(0)
    {
        for (int i = MOVETO; i <= CLOSEPOLY; ++i) {
            if (!(s.compare(PathOpNames[i]))) {
                mPathOp = static_cast<pathOpEnum>(i);
                break;
            }
        }
        if (mPathOp == unknownPathop) {
            CfdgError::Error(loc, "Unknown path operation type");
        }
    }
    
    ASTpathOp::ASTpathOp(const std::string& s, mod_ptr a, const yy::location& loc)
    : ASTreplacement(ASTruleSpecifier::Zero, nullptr, loc, op), mArguments(nullptr),
      mOldStyleArguments(std::move(a)), mFlags(0), mArgCount(0)
    {
        for (int i = MOVETO; i <= CLOSEPOLY; ++i) {
            if (!(s.compare(PathOpNames[i]))) {
                mPathOp = static_cast<pathOpEnum>(i);
                break;
            }
        }
        if (mPathOp == unknownPathop) {
            CfdgError::Error(loc, "Unknown path operation type");
        }
    }
    
    ASTpathCommand::ASTpathCommand(const std::string& s, mod_ptr mods, 
                                   exp_ptr params, const yy::location& loc)
    :   ASTreplacement(ASTruleSpecifier::Zero, std::move(mods), loc, command),
        mMiterLimit(4.0), mParameters(std::move(params))
    {
        mChildChange.addEntropy(s);
        
        if (!(s.compare("FILL"))) {
            mChildChange.flags |= CF_FILL;
        } else if (!s.compare("STROKE")) {
            mChildChange.flags &= ~CF_FILL;
        } else {
            CfdgError::Error(loc, "Unknown path command/operation");
        }
    }
    
    ASTreplacement::~ASTreplacement()
    {
    }
    
    ASTloop::~ASTloop()
    {
    }
    
    ASTif::~ASTif()
    {
    }
    
    ASTswitch::~ASTswitch()
    {
    }
    
    ASTrule::~ASTrule()
    {
    }
    
    ASTcompiledPath::~ASTcompiledPath()
    {
        if (mParameters)
            mParameters->release();
    }
    
    ASTtransform::~ASTtransform()
    {
        ASTexpression* m = const_cast<ASTexpression*>(mModifications);
        if (m && m->release())
            delete mModifications;
    }
    
    ASTpathOp::~ASTpathOp()
    {
    }
    
    void 
    ASTreplacement::replaceShape(Shape& s, RendererAST* r) const
    {
        if (mShapeSpec.argSource == ASTruleSpecifier::NoArgs) {
            s.mShapeType = mShapeSpec.shapeType;
            s.mParameters = nullptr;
        } else {
            s.mParameters = mShapeSpec.evalArgs(r, s.mParameters);
            if (mShapeSpec.argSource == ASTruleSpecifier::SimpleParentArgs)
                s.mShapeType = mShapeSpec.shapeType;
            else
                s.mShapeType = s.mParameters->mRuleName;
            if (s.mParameters->mParamCount == 0)
                s.mParameters = nullptr;    // TODO: release?
        }
    }
    
    void 
    ASTreplacement::replace(Shape& s, RendererAST* r, double* width) const
    {
        int dummy;
        replaceShape(s, r);
        r->mCurrentSeed ^= mChildChange.modData.mRand64Seed;
        r->mCurrentSeed.bump();
        mChildChange.evaluate(s.mWorldState, nullptr, width, false, dummy, true, r);
        s.mAreaCache = s.mWorldState.area();
    }
    
    void
    ASTreplacement::traverse(const Shape& parent, bool tr, RendererAST* r) const
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
    ASTloop::traverse(const Shape& parent, bool tr, RendererAST* r) const
    {
        Shape loopChild = parent;
        bool opsOnly = (mLoopBody.mRepType | mFinallyBody.mRepType) == op;
        if (opsOnly && !tr)
            loopChild.mWorldState.m_transform.reset();
        double start, end, step;
        
        r->mCurrentSeed ^= mChildChange.modData.mRand64Seed;
        if (mLoopArgs) {
            setupLoop(start, end, step, mLoopArgs.get(), mLocation, r);
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
            if (r->requestStop || Renderer::AbortEverything)
                throw CfdgError(mLocation, "Stopping");
            
            if (step > 0.0) {
                if (index.number >= end)
                    break;
            } else {
                if (index.number <= end)
                    break;
            }
            mLoopBody.traverse(loopChild, tr || opsOnly, r);
            mChildChange.evaluate(loopChild.mWorldState, nullptr, nullptr, false, dummy, true, r);
            index.number += step;
        }
        mFinallyBody.traverse(loopChild, tr || opsOnly, r);
        r->mCFstack.pop_back();
        r->mLogicalStackTop = oldTop;
    }
    
    void
    ASTtransform::traverse(const Shape& parent, bool tr, RendererAST* r) const
    {
        Rand64 cloneSeed = r->mCurrentSeed;
        Shape transChild = parent;
        bool opsOnly = mBody.mRepType == op;
        if (opsOnly && !tr)
            transChild.mWorldState.m_transform.reset();
        
        int dummy;
        
        int modsLength = mModifications ? static_cast<int>(mModifications->size()) : 0;
        int totalLength = modsLength + static_cast<int>(mTransforms.size());
        for(int i = 0; i < totalLength; ++i) {
            Shape child = transChild;
            if (i < modsLength) {
                if (const ASTmodification* m = dynamic_cast<const ASTmodification*>((*mModifications)[i])) {
                    r->mCurrentSeed ^= m->modData.mRand64Seed;
                    m->evaluate(child.mWorldState, nullptr, nullptr, false, dummy, true, r);
                } else {
                    continue;
                }
            } else {
                child.mWorldState.m_transform.premultiply(mTransforms[i - modsLength]);
            }
            r->mCurrentSeed.bump();

            // Specialized mBody.traverse() with cloning behavior
            size_t s = r->mCFstack.size();
            for (const rep_ptr& rep: mBody.mBody) {
                if (mClone)
                    r->mCurrentSeed = cloneSeed;
                rep->traverse(child, opsOnly || tr, r);
            }
            r->unwindStack(s, mBody.mParameters);
        }
    }
    
    void
    ASTif::traverse(const Shape& parent, bool tr, RendererAST* r) const
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
    ASTswitch::traverse(const Shape& parent, bool tr, RendererAST* r) const
    {
        double caseValue = 0.0;
        if (mSwitchExp->evaluate(&caseValue, 1, r) != 1) {
            CfdgError::Error(mLocation, "Error evaluating switch selector");
            return;
        }
        
        switchMap::const_iterator it = mCaseStatements.find(static_cast<int>(floor(caseValue)));
        if (it != mCaseStatements.end()) (*it).second->traverse(parent, tr, r);
        else mElseBody.traverse(parent, tr, r);
    }
    
    void
    ASTdefine::traverse(const Shape& p, bool, RendererAST* r) const
    {
        if (isConstant || isFunction || mConfigDepth >= 0)
            return;
        size_t s = r->mCFstack.size();
        r->mCFstack.resize(s + mTuplesize);
        r->mCurrentSeed ^= mChildChange.modData.mRand64Seed;
        StackType* dest = r->mCFstack.data() + s;
        
        switch (mType) {
            case NumericType:
                if (mExpression->evaluate(&dest->number, mTuplesize, r) != mTuplesize)
                    CfdgError::Error(mExpression->where, 
                                   "Error evaluating parameters (too many or not enough).");
                break;
            case ModType: {
                int dummy;
                Modification* smod = reinterpret_cast<Modification*> (dest);
                mChildChange.setVal(*smod, nullptr, nullptr, false, dummy, r);
                break;
            }
            case RuleType:
                dest->rule = mExpression->evalArgs(r, p.mParameters);
                break;
            default:
                CfdgError::Error(mExpression->where, "Unimplemented parameter type.");
                break;
        }
        
        if (!(r->mCFstack.empty()))
            r->mLogicalStackTop = r->mCFstack.data() + r->mCFstack.size();
    }
    
    void
    ASTrule::traverse(const Shape& parent, bool tr, RendererAST* r) const
    {
        r->mCurrentSeed = parent.mWorldState.mRand64Seed;
        
        if (isPath) {
            r->processPrimShape(parent, this);
        } else {
            mRuleBody.traverse(parent, tr, r, true);
            parent.releaseParams();
        }
    }
    
    void ASTpathOp::traverse(const Shape& s, bool tr, RendererAST* r) const
    {
        if (r->mCurrentPath->mComplete) 
            return;
        double opData[7];
        pathData(opData, r);
        r->mCurrentPath->addPathOp(this, opData, s, tr, r);
    }
    
    void
    ASTpathCommand::traverse(const Shape& s, bool, RendererAST* r) const
    {
        Shape child = s;
        double width = mChildChange.strokeWidth;
        replace(child, r, &width);
        
        CommandInfo* info = nullptr;
        
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
                r->mCurrentPath->mCommandInfo.emplace_back(r->mIndex, r->mCurrentPath, width, this);
            }
            info = &(r->mCurrentPath->mCommandInfo.back());
        }

        r->processPathCommand(child, info);
    }
    
    void
    ASTrule::traversePath(const Shape& parent, RendererAST* r) const
    {
        r->init();
        r->mCurrentSeed = parent.mWorldState.mRand64Seed;
        r->mRandUsed = false;
        
        ASTcompiledPath* savedPath = nullptr;
        
        if (mCachedPath && StackRule::Equal(mCachedPath->mParameters, parent.mParameters)) {
            savedPath = r->mCurrentPath;
            r->mCurrentPath = mCachedPath.get();
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
            if (!(r->mRandUsed) && !mCachedPath) {
                mCachedPath.reset(r->mCurrentPath);
                mCachedPath->mComplete = true;
                mCachedPath->mParameters = StackRule::alloc(parent.mParameters);
                r->mCurrentPath = new ASTcompiledPath();
            } else {
                r->mCurrentPath->mPath.remove_all();
                r->mCurrentPath->mCommandInfo.clear();
                r->mCurrentPath->mUseTerminal = false;
                r->mCurrentPath->mPathUID = ASTcompiledPath::NextPathUID();
                if (r->mCurrentPath->mParameters) {
                    r->mCurrentPath->mParameters->release();
                    r->mCurrentPath->mParameters = nullptr;
                }
            }
        }
    }
    
    void
    ASTreplacement::compile(AST::CompilePhase ph)
    {
        ASTexpression* r;
        r = mShapeSpec.compile(ph);             // always returns this
        assert(r == &mShapeSpec);
        r = mChildChange.compile(ph);           // ditto
        assert(r == &mChildChange);
    }
    
    void
    ASTloop::compile(AST::CompilePhase ph)
    {
        Compile(mLoopArgs, ph);
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                if (!mLoopArgs) {
                    CfdgError::Error(mLocation, "A loop must have one to three index parameters.");
                    return;
                }
                bool bodyNatural = false;
                bool finallyNatural = false;
                bool local = mLoopArgs->isLocal;
                
                if (mLoopArgs->isConstant) {
                    setupLoop(mLoopData[0], mLoopData[1], mLoopData[2], mLoopArgs.get(), mLoopArgs->where);
                    bodyNatural = mLoopData[0] == floor(mLoopData[0]) &&
                    mLoopData[1] == floor(mLoopData[1]) &&
                    mLoopData[2] == floor(mLoopData[2]) &&
                    mLoopData[0] >= 0.0 && mLoopData[1] >= 0.0 &&
                    mLoopData[0] < 9007199254740992. &&
                    mLoopData[1] < 9007199254740992.;
                    finallyNatural = bodyNatural && mLoopData[1] + mLoopData[2] >= -1.0 &&
                    mLoopData[1] + mLoopData[2] < 9007199254740992.;
                    mLoopArgs.reset();
                } else {
                    int c = mLoopArgs->evaluate(nullptr, 0);
                    if (c < 1 || c > 3) {
                        CfdgError::Error(mLoopArgs->where, "A loop must have one to three index parameters.");
                    }
                    
                    for (int i = 0, count = 0; i < mLoopArgs->size(); ++i) {
                        int num = (*mLoopArgs)[i]->evaluate(nullptr, 0);
                        switch (count) {
                            case 0:
                                if ((*mLoopArgs)[i]->isNatural)
                                    bodyNatural = finallyNatural = true;
                                break;
                            case 2: {
                                // Special case: if 1st & 2nd args are natural and 3rd
                                // is -1 then that is ok
                                double step;
                                if ((*mLoopArgs)[i]->isConstant &&
                                    (*mLoopArgs)[i]->evaluate(&step, 1) == 1 &&
                                    step == -1.0)
                                {
                                    break;
                                }
                            }   // else fall through
                            case 1:
                                if (!((*mLoopArgs)[i]->isNatural))
                                    bodyNatural = finallyNatural = false;
                                break;
                            default:
                                break;
                        }
                        count += num;
                    }
                }
                
                mLoopBody.mParameters.front().isNatural = bodyNatural;
                mLoopBody.mParameters.front().isLocal = local;
                mLoopBody.compile(ph, this, nullptr);
                mFinallyBody.mParameters.front().isNatural = finallyNatural;
                mFinallyBody.mParameters.front().isLocal = local;
                mFinallyBody.compile(ph);
                break;
            }
            case CompilePhase::Simplify:
                if (mLoopArgs)
                    mLoopArgs.reset(mLoopArgs.release()->simplify());
                mLoopBody.compile(ph);
                mFinallyBody.compile(ph);
                break;
        }
    }
    
    void
    ASTtransform::compile(AST::CompilePhase ph)
    {
        ASTreplacement::compile(ph);
        if (mExpHolder)
            mExpHolder->compile(ph);        // always returns this
        mBody.compile(ph);
    }
    
    void
    ASTif::compile(AST::CompilePhase ph)
    {
        ASTreplacement::compile(ph);
        Compile(mCondition, ph);
        mThenBody.compile(ph);
        mElseBody.compile(ph);
        
        switch (ph) {
            case CompilePhase::TypeCheck:
                if (mCondition->mType != NumericType || mCondition->evaluate(nullptr, 0) != 1)
                    CfdgError::Error(mCondition->where, "If condition must be a numeric scalar");
                break;
            case CompilePhase::Simplify:
                if (mCondition)
                    mCondition.reset(mCondition.release()->simplify());
                break;
        }
    }
    
    void
    ASTswitch::compile(AST::CompilePhase ph)
    {
        ASTreplacement::compile(ph);
        Compile(mSwitchExp, ph);
        for (auto& casepair: mCaseStatements)
            casepair.second->compile(ph);
        mElseBody.compile(ph);
        
        switch (ph) {
            case CompilePhase::TypeCheck:
                if (mSwitchExp->mType != NumericType || mSwitchExp->evaluate(nullptr, 0) != 1)
                    CfdgError::Error(mSwitchExp->where, "Switch selector must be a numeric scalar");
                break;
            case CompilePhase::Simplify:
                if (mSwitchExp)
                    mSwitchExp.reset(mSwitchExp.release()->simplify());
                break;
        }
    }
    
    void
    ASTdefine::compile(AST::CompilePhase ph)
    {
        ASTrepContainer tempCont;
        tempCont.mParameters = mParameters;     // copy
        tempCont.mStackCount = mStackCount;
        Builder::CurrentBuilder->push_repContainer(tempCont);
        ASTreplacement::compile(ph);
        Compile(mExpression, ph);
        Builder::CurrentBuilder->pop_repContainer(nullptr);
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                if (mConfigDepth >= 0) {
                    Builder::CurrentBuilder->MakeConfig(this);
                    return;
                }
                expType t = mExpression ? mExpression->mType : ModType;
                int sz = 1;
                if (t == NumericType)
                    sz = mExpression->evaluate(nullptr, 0);
                if (t == ModType)
                    sz = ModificationSize;
                if (isFunction) {
                    if (t != mType)
                        CfdgError::Error(mLocation, "Mismatch between declared and defined type of user function");
                    if (mType == NumericType && t == NumericType && sz != mTuplesize)
                        CfdgError::Error(mLocation, "Mismatch between declared and defined vector length of user function");
                    if (isNatural && (!mExpression || !mExpression->isNatural))
                        CfdgError::Error(mLocation, "Mismatch between declared natural and defined not-natural type of user function");
                    isConstant = false;
                } else {
                    // TODO: check that name doesn't collide with user function name
                    mTuplesize = sz;
                    mType = t;
                    if (t != (t & (-t)) || !t)
                        CfdgError::Error(mLocation, "Expression can only have one type");
                    isConstant = mExpression ? mExpression->isConstant : mChildChange.modExp.empty();
                    isNatural = mExpression && mExpression->isNatural && mType == NumericType;
                    ASTparameter& param = Builder::CurrentBuilder->
                        mContainerStack.back()->
                        addDefParameter(mShapeSpec.shapeType, this, mLocation, mLocation);
                    if (param.isParameter || !param.mDefinition) {
                        param.mStackIndex = Builder::CurrentBuilder->mLocalStackDepth;
                        Builder::CurrentBuilder->mContainerStack.back()->mStackCount += param.mTuplesize;
                        Builder::CurrentBuilder->mLocalStackDepth += param.mTuplesize;
                    }
                }
                break;
            }
            case CompilePhase::Simplify:
                break;
        }
    }
    
    void
    ASTrule::compile(AST::CompilePhase ph)
    {
        ASTreplacement::compile(ph);
        mRuleBody.compile(ph);
    }
    
    void
    ASTpathOp::compile(AST::CompilePhase ph)
    {
        ASTreplacement::compile(ph);
        Compile(mArguments, ph);
        if (mOldStyleArguments)
            mOldStyleArguments->compile(ph);        // always return this
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                if (mOldStyleArguments)
                    makePositional();
                else
                    checkArguments();
                break;
            }
            case CompilePhase::Simplify:
                pathDataConst();
                if (mArguments)
                    mArguments.reset(mArguments.release()->simplify());
                break;
        }
    }
    
    void
    ASTpathCommand::compile(AST::CompilePhase ph)
    {
        ASTreplacement::compile(ph);
        Compile(mParameters, ph);
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                check4z();
                if (!mParameters)
                    return;
                
                exp_ptr stroke, flags;
                switch (mParameters->size()) {
                    case 2:
                        stroke.reset((*mParameters)[0]);
                        flags.reset((*mParameters)[1]);
                        if (!mParameters->release()) {
                            CfdgError::Error(mParameters->where, "Path commands can have zero, one, or two parameters");
                            stroke.release();
                            flags.release();
                            return;
                        }
                        break;
                    case 1:
                        switch (mParameters->mType) {
                            case NumericType:
                                stroke = std::move(mParameters);
                                break;
                            case FlagType:
                                flags = std::move(mParameters);
                                break;
                            default:
                                CfdgError::Error(mParameters->where, "Bad expression type in path command parameters");
                                break;
                        }
                        break;
                    case 0:
                        return;
                    default:
                        CfdgError::Error(mParameters->where, "Path commands can have zero, one, or two parameters");
                        return;
                }
                
                if (stroke) {
                    if (mChildChange.flags & CF_FILL)
                        CfdgError::Warning(stroke->where, "Stroke width only useful for STROKE commands");
                    if (stroke->mType != NumericType || stroke->evaluate(nullptr, 0) != 1) {
                        CfdgError::Error(stroke->where, "Stroke width expression must be numeric scalar");
                    } else if (!stroke->isConstant ||
                               stroke->evaluate(&(mChildChange.strokeWidth), 1) != 1)
                    {
                        ASTmodTerm* w = new ASTmodTerm(ASTmodTerm::stroke, stroke.release()->simplify(), mLocation);
                        mChildChange.modExp.emplace_back(w);
                    }
                }
                
                if (flags) {
                    if (flags->mType != FlagType) {
                        CfdgError::Error(flags->where, "Unexpected argument in path command");
                        return;
                    }
                    flags.reset(flags.release()->simplify());
                    if (ASTreal* r = dynamic_cast<ASTreal*> (flags.get())) {
                        int f = static_cast<int>(r->value);
                        if (f & CF_JOIN_PRESENT)
                            mChildChange.flags &= ~CF_JOIN_MASK;
                        if (f & CF_CAP_PRESENT)
                            mChildChange.flags &= ~CF_CAP_MASK;
                        mChildChange.flags |= f;
                        if ((mChildChange.flags & CF_FILL) && (f & (CF_JOIN_PRESENT | CF_CAP_PRESENT)))
                            CfdgError::Warning(flags->where, "Stroke flags only useful for STROKE commands");
                    } else {
                        CfdgError::Error(flags->where, "Flag expressions must be constant");
                    }
                }
                break;
            }
            case CompilePhase::Simplify:
                if (mParameters)
                    mParameters.reset(mParameters.release()->simplify());
                break;
        }
    }
    
    void
    ASTcompiledPath::addPathOp(const ASTpathOp* pop, double data[6], const Shape& s, 
                               bool tr, RendererAST* r)
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
    ASTcompiledPath::finish(bool setAttr, RendererAST* r)
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
    
    UIDdatatype
    ASTcompiledPath::NextPathUID()
    {
        return ++GlobalPathUID;
    }
    
    bool
    ASTrule::compareLT(const ASTrule* a, const ASTrule* b)
    {
        return  (a->mNameIndex == b->mNameIndex) ? 
        (a->mWeight < b->mWeight) : (a->mNameIndex < b->mNameIndex);
    }
    
    void
    ASTpathOp::pathData(double* data, RendererAST* rti) const
    {
        if (mArguments) {
            if (mArguments->evaluate(data, 7, rti) < 0)
                CfdgError::Error(mArguments->where, "Cannot evaluate arguments");
        } else {
            mChildChange.modData.m_transform.store_to(data);
        }
    }
    
    void
    ASTpathOp::pathDataConst()
    {
        if (mArguments && mArguments->isConstant) {
            double data[7];
            if (mArguments->evaluate(data, 7) < 0)
                CfdgError::Error(mArguments->where, "Cannot evaluate arguments");
            mArguments.reset();
            mChildChange.modData.m_transform.load_from(data);
        }
    }

    void
    ASTpathOp::checkArguments()
    {
        if (mArguments)
            mArgCount = mArguments->evaluate(nullptr, 0);

        for (int i = 0; mArguments && i < mArguments->size(); ++i) {
            ASTexpression* temp = (*mArguments)[i];
			assert(temp);
            switch (temp->mType) {
                case FlagType: {
                    if (i != mArguments->size() - 1)
                        CfdgError::Error(temp->where, "Flags must be the last argument");
                    if (ASTreal* rf = dynamic_cast<ASTreal*> (temp))
                        mFlags = rf ? static_cast<int>(rf->value) : 0;
                    else
                        CfdgError::Error(temp->where, "Flag expressions must be constant");
                    --mArgCount;
                    break;
                }
                case NumericType:
                    break;
                default:
                    CfdgError::Error(temp->where, "Path operation arguments must be numeric expressions or flags");
                    break;
            }
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
        if (!ax)
            ax.reset(new ASTreal(def, loc));
        int sz = ax->evaluate(nullptr, 0);
        
        if (sz == 1 && !ay)
            ay.reset(new ASTreal(def, loc));
        
        if (ay)
            sz += ay->evaluate(nullptr, 0);
        
        if (sz != 2)
            CfdgError::Error(loc, "Error parsing path operation arguments");
        
        return ax.release()->append(ay.release());
    }
    
    static void
    rejectTerm(exp_ptr term)
    {
        if (term)
            CfdgError::Error(term->where, "Illegal argument");
        // and delete it
    }
    
    void
    ASTpathOp::makePositional()
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
        
        for (term_ptr& mod: mOldStyleArguments->modExp) {
            switch (mod ? mod->modType : ASTmodTerm::unknownType) {
                case ASTmodTerm::x:
                    ax = std::move(mod->args);
                    break;
                case ASTmodTerm::y:
                    ay = std::move(mod->args);
                    break;
                case ASTmodTerm::x1:
                    ax1 = std::move(mod->args);
                    break;
                case ASTmodTerm::y1:
                    ay1 = std::move(mod->args);
                    break;
                case ASTmodTerm::x2:
                    ax2 = std::move(mod->args);
                    break;
                case ASTmodTerm::y2:
                    ay2 = std::move(mod->args);
                    break;
                case ASTmodTerm::xrad:
                    arx = std::move(mod->args);
                    break;
                case ASTmodTerm::yrad:
                    ary = std::move(mod->args);
                    break;
                case ASTmodTerm::rot:
                    ar = std::move(mod->args);
                    break;
                case ASTmodTerm::param:
                    if (mod->paramString.find("large") != std::string::npos)  mFlags |= CF_ARC_LARGE;
                    if (mod->paramString.find("cw") != std::string::npos)     mFlags |= CF_ARC_CW;
                    if (mod->paramString.find("align") != std::string::npos)  mFlags |= CF_ALIGN;
                    break;
                case ASTmodTerm::z:
                case ASTmodTerm::zsize:
                    CfdgError::Error(mod->where, "Z changes are not permitted in paths");
                    break;
                case ASTmodTerm::unknownType:
                    CfdgError::Error(mLocation, "Unrecognized element in a path operation");
                    break;
                default:
                    CfdgError::Error(mLocation, "Unrecognized element in a path operation");
                    break;
            }
        }
        
        ASTexpression* xy = nullptr;
        if (mPathOp != CLOSEPOLY) {
            xy = parseXY(std::move(ax), std::move(ay), 0.0, mLocation);
        } 
        
        switch (mPathOp) {
            case LINETO:
            case LINEREL:
            case MOVETO:
            case MOVEREL:
                rejectTerm(std::move(ar));
                rejectTerm(std::move(arx));
                rejectTerm(std::move(ary));
                rejectTerm(std::move(ax1));
                rejectTerm(std::move(ay1));
                rejectTerm(std::move(ax2));
                rejectTerm(std::move(ay2));
                
                mArguments.reset(xy);
                break;
            case ARCTO:
            case ARCREL:
                rejectTerm(std::move(ax1));
                rejectTerm(std::move(ay1));
                rejectTerm(std::move(ax2));
                rejectTerm(std::move(ay2));
                
                if (arx || ary) {
                    ASTexpression* rxy = parseXY(std::move(arx), std::move(ary), 1.0, mLocation);
                    ASTexpression* angle = ar.release();
                    if (!angle)
                        angle = new ASTreal(0.0, mLocation);
                    
                    if (angle->evaluate(nullptr, 0) != 1)
                        CfdgError(angle->where, "Arc angle must be a scalar value");
                    
                    mArguments.reset(xy->append(rxy)->append(angle));
                } else {
                    ASTexpression* radius = ar.release();
                    if (!radius)
                        radius = new ASTreal(1.0, mLocation);
                    
                    if (radius->evaluate(nullptr, 0) != 1)
                        CfdgError::Error(radius->where, "Arc radius must be a scalar value");
                    
                    mArguments.reset(xy->append(radius));
                } 
                break;
            case CURVETO:
            case CURVEREL: {
                rejectTerm(std::move(ar));
                rejectTerm(std::move(arx));
                rejectTerm(std::move(ary));
                
                ASTexpression *xy1 = nullptr, *xy2 = nullptr;
                if (ax1 || ay1) {
                    xy1 = parseXY(std::move(ax1), std::move(ay1), 0.0, mLocation);
                } else {
                    mFlags |= CF_CONTINUOUS;
                }
                if (ax2 || ay2) {
                    xy2 = parseXY(std::move(ax2), std::move(ay2), 0.0, mLocation);
                }
                
                mArguments.reset(xy->append(xy1)->append(xy2));
                break;
            }
            case CLOSEPOLY:
                rejectTerm(std::move(ax));
                rejectTerm(std::move(ay));
                rejectTerm(std::move(ar));
                rejectTerm(std::move(arx));
                rejectTerm(std::move(ary));
                rejectTerm(std::move(ax1));
                rejectTerm(std::move(ay1));
                rejectTerm(std::move(ax2));
                rejectTerm(std::move(ay2));
                break;
            default:
                break;
        } 
        
        mArgCount = mArguments ? mArguments->evaluate(nullptr, 0) : 0;
        mOldStyleArguments.reset();
    }
    
    void
    ASTpathCommand::check4z() const
    {
        static const agg::trans_affine_1D unitZ;
        if (mChildChange.modData.m_Z != unitZ) {
            CfdgError::Warning(mLocation, "Z changes are not supported within paths");
            return;
        }
        static const agg::trans_affine_time unitTime;
        if (mChildChange.modData.m_time != unitTime) {
            CfdgError::Warning(mLocation, "Time changes are not supported within paths");
            return;
        }
        for (const term_ptr& term: mChildChange.modExp) {
            if (term->modType == ASTmodTerm::z ||
                term->modType == ASTmodTerm::xyz ||
                term->modType == ASTmodTerm::sizexyz ||
                term->modType == ASTmodTerm::zsize)
            {
                CfdgError::Warning(term->where, "Z changes are not supported within paths");
                return;
            }
            if (term->modType == ASTmodTerm::time ||
                term->modType == ASTmodTerm::timescale)
            {
                CfdgError::Warning(term->where, "Time changes are not supported within paths");
                return;
            }
        }
    }
}
