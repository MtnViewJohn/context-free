// astreplacement.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2009-2014 John Horigan - john@glyphic.com
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
#include <typeinfo>

namespace AST {
    
    CommandInfo::UIDtype ASTcompiledPath::GlobalPathUID(1);
    
    void
    ASTrepContainer::addParameter(const std::string& type, int index,
                                  const yy::location& typeLoc, const yy::location& nameLoc) 
    {
        mParameters.emplace_back(type, index, typeLoc + nameLoc);
        ASTparameter& param = mParameters.back();
        param.isParameter = true;
        param.checkParam(typeLoc, nameLoc);
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
            loop->compileLoopMod();
        for (auto& rep: mBody)
            rep->compile(ph);
        if (def)
            def->compile(ph);
        Builder::CurrentBuilder->pop_repContainer(nullptr);
    }

    
    ASTreplacement::ASTreplacement(ASTruleSpecifier&& shapeSpec, mod_ptr mods,
                                   const yy::location& loc, repElemListEnum t)
    : mShapeSpec(std::move(shapeSpec)), mRepType(t), mPathOp(unknownPathop),
      mChildChange(std::move(mods), loc), mLocation(loc)
    {
    }
    
    ASTreplacement::ASTreplacement(mod_ptr mods, const yy::location& loc,
                                   repElemListEnum t)
    : mShapeSpec(), mRepType(t), mPathOp(unknownPathop),
      mChildChange(std::move(mods), loc), mLocation(loc)
    {
    }

    ASTreplacement::ASTreplacement(const std::string& s, const yy::location& loc)
    : mShapeSpec(), mRepType(op), mPathOp(unknownPathop),
      mChildChange(loc), mLocation(loc)
    {
        static const std::map<std::string, pathOpEnum> PathOpNames = {
            { "MOVETO",     MOVETO },
            { "MOVEREL",    MOVEREL },
            { "LINETO",     LINETO },
            { "LINEREL",    LINEREL },
            { "ARCTO",      ARCTO },
            { "ARCREL",     ARCREL },
            { "CURVETO",    CURVETO },
            { "CURVEREL",   CURVEREL },
            { "CLOSEPOLY",  CLOSEPOLY }
        };
        
        auto opname = PathOpNames.find(s);
        if (opname == PathOpNames.end())
            CfdgError::Error(loc, "Unknown path operation type");
        else
            mPathOp = opname->second;
    }

    ASTloop::ASTloop(int nameIndex, const std::string& name, const yy::location& nameLoc,
                     exp_ptr args, const yy::location& argsLoc,  
                     mod_ptr mods)
    : ASTreplacement(std::move(mods), nameLoc + argsLoc, empty), mLoopArgs(std::move(args)),
      mLoopModHolder(nullptr), mLoopIndexName(nameIndex), mLoopName(name)
    {
        mLoopBody.addLoopParameter(mLoopIndexName, false, false, mLocation);
        mFinallyBody.addLoopParameter(mLoopIndexName, false, false, mLocation);
    }
    
    ASTtransform::ASTtransform(const yy::location& loc, exp_ptr mods)
    : ASTreplacement(nullptr, loc, empty), mExpHolder(std::move(mods)), mClone(false)
    {
    }
    
    ASTdefine::ASTdefine(const std::string& name, const yy::location& loc)
    : ASTreplacement(nullptr, loc, empty), mDefineType(StackDefine),
      mType(NoType), isNatural(false), mStackCount(0), mName(std::move(name)),
      mConfigDepth(-1)
    {
        // Set the Modification entropy to parameter name, not its own contents
        int i = 0;
        mChildChange.modData.mRand64Seed.seed();
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
    : ASTreplacement(nullptr, condLoc, empty),
      mCondition(std::move(ifCond))
    {
    }

    ASTswitch::ASTswitch(exp_ptr switchExp, const yy::location& expLoc)
    : ASTreplacement(nullptr, expLoc, empty),
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

    ASTrule::ASTrule(int i)
    : ASTreplacement(nullptr, CfdgError::Default, rule), mCachedPath(nullptr),
      mWeight(1.0), isPath(true), mNameIndex(i), weightType(NoWeight)
    {
        if (primShape::shapeMap[i]) {
            static const std::string  move_op("MOVETO");
            static const std::string  line_op("LINETO");
            static const std::string   arc_op("ARCTO");
            static const std::string close_op("CLOSEPOLY");
            if (i != primShape::circleType) {
                primIter shape(primShape::shapeMap[i]);
                double x = 0, y = 0;
                unsigned cmd;
                while (!agg::is_stop(cmd = shape.vertex(&x, &y))) {
                    if (agg::is_vertex(cmd)) {
                        exp_ptr a(new ASTcons{ new ASTreal(x, CfdgError::Default),
                                               new ASTreal(y, CfdgError::Default) });
                        ASTpathOp* op = new ASTpathOp(agg::is_move_to(cmd) ? move_op : line_op,
                            std::move(a), CfdgError::Default);
                        mRuleBody.mBody.emplace_back(op);
                    }
                }
            } else {
                exp_ptr a(new ASTcons{ new ASTreal(0.5, CfdgError::Default),
                                       new ASTreal(0.0, CfdgError::Default) });
                ASTpathOp* op = new ASTpathOp(move_op, std::move(a), CfdgError::Default);
                mRuleBody.mBody.emplace_back(op);
                a.reset(new ASTcons{ new ASTreal(-0.5, CfdgError::Default),
                                     new ASTreal( 0.0, CfdgError::Default),
                                     new ASTreal( 0.5, CfdgError::Default) });
                op = new ASTpathOp(arc_op, std::move(a), CfdgError::Default);
                mRuleBody.mBody.emplace_back(op);
                a.reset(new ASTcons{ new ASTreal( 0.5, CfdgError::Default),
                                     new ASTreal( 0.0, CfdgError::Default),
                                     new ASTreal( 0.5, CfdgError::Default) });
                op = new ASTpathOp(arc_op, std::move(a), CfdgError::Default);
                mRuleBody.mBody.emplace_back(op);
            }
            mRuleBody.mBody.emplace_back(new ASTpathOp(close_op, exp_ptr(),
                CfdgError::Default));
            mRuleBody.mRepType = ASTreplacement::op;
            mRuleBody.mPathOp = AST::MOVETO;
        }
    }

    ASTrepContainer::~ASTrepContainer() 
    {
    }
    
    ASTcompiledPath::ASTcompiledPath()
    : mCached(false), mUseTerminal(false), mParameters(nullptr)
    {
        mPathUID = NextPathUID();
    }
    
    ASTpathOp::ASTpathOp(const std::string& s, exp_ptr a, const yy::location& loc)
    : ASTreplacement(s, loc), mArguments(std::move(a)),
      mOldStyleArguments(nullptr), mArgCount(0), mFlags(0)
    {
    }
    
    ASTpathOp::ASTpathOp(const std::string& s, mod_ptr a, const yy::location& loc)
    : ASTreplacement(s, loc), mArguments(nullptr),
      mOldStyleArguments(std::move(a)), mArgCount(0), mFlags(0)
    {
    }
    
    ASTpathCommand::ASTpathCommand(const std::string& s, mod_ptr mods, 
                                   exp_ptr params, const yy::location& loc)
    :   ASTreplacement(std::move(mods), loc, command),
        mMiterLimit(4.0), mStrokeWidth(0.1), mParameters(std::move(params)),
        mFlags(CF_MITER_JOIN + CF_BUTT_CAP)
    {
        if (s == "FILL") {
            mFlags |= CF_FILL;
        } else if (s != "STROKE") {
            CfdgError::Error(loc, "Unknown path command/operation");
        }
    }
    
    ASTreplacement::~ASTreplacement() = default;
    
    ASTloop::~ASTloop() = default;
    
    ASTif::~ASTif() = default;
    
    ASTswitch::~ASTswitch() = default;
    
    ASTrule::~ASTrule() = default;
    
    ASTcompiledPath::~ASTcompiledPath() = default;
    
    ASTtransform::~ASTtransform() = default;
    
    ASTpathOp::~ASTpathOp() = default;
    
    void 
    ASTreplacement::replace(Shape& s, RendererAST* r) const
    {
        if (mShapeSpec.argSource == ASTruleSpecifier::NoArgs) {
            s.mShapeType = mShapeSpec.shapeType;
            s.mParameters = nullptr;
        } else {
            s.mParameters = mShapeSpec.evalArgs(r, s.mParameters.get());
            if (mShapeSpec.argSource == ASTruleSpecifier::SimpleParentArgs)
                s.mShapeType = mShapeSpec.shapeType;
            else
                s.mShapeType = s.mParameters->mRuleName;
            if (s.mParameters && s.mParameters->mParamCount == 0)
                s.mParameters.reset();
        }
        r->mCurrentSeed ^= mChildChange.modData.mRand64Seed;
        r->mCurrentSeed();
        mChildChange.evaluate(s.mWorldState, true, r);
        s.mAreaCache = s.mWorldState.area();
    }
    
    void
    ASTreplacement::traverse(const Shape& parent, bool tr, RendererAST* r) const
    {
        Shape child(parent);
        switch (mRepType) {
            case replacement:
                replace(child, r);
                child.mWorldState.mRand64Seed = r->mCurrentSeed;
                child.mWorldState.mRand64Seed();
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
        Shape loopChild(parent);
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
        const StackType* oldTop = r->mLogicalStackTop;
        if (r->mStackSize + 1 > r->mCFstack.size())
            CfdgError::Error(mLocation, "Maximum stack depth exceeded");
        StackType& index = r->mCFstack[r->mStackSize];
        index.number = start;
        ++r->mStackSize;
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
            mChildChange.evaluate(loopChild.mWorldState, true, r);
            index.number += step;
        }
        mFinallyBody.traverse(loopChild, tr || opsOnly, r);
        --r->mStackSize;
        r->mLogicalStackTop = oldTop;
    }
    
    void
    ASTtransform::traverse(const Shape& parent, bool tr, RendererAST* r) const
    {
        static agg::trans_affine Dummy;
        SymmList transforms;
        std::vector<const ASTmodification*> mods = getTransforms(mExpHolder.get(), transforms, r, false, Dummy);
        
        Rand64 cloneSeed = r->mCurrentSeed;
        Shape transChild(parent);
        bool opsOnly = mBody.mRepType == op;
        if (opsOnly && !tr)
            transChild.mWorldState.m_transform.reset();
        
        size_t modsLength = mods.size();
        size_t totalLength = modsLength + transforms.size();
        for(size_t i = 0; i < totalLength; ++i) {
            Shape child(transChild);
            if (i < modsLength) {
                mods[i]->evaluate(child.mWorldState, true, r);
            } else {
                child.mWorldState.m_transform.premultiply(transforms[i - modsLength]);
            }
            r->mCurrentSeed();

            // Specialized mBody.traverse() with cloning behavior
            size_t s = r->mStackSize;
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
        if (cond != 0.0) mThenBody.traverse(parent, tr, r);
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
        if (mDefineType != StackDefine)
            return;
        if (r->mStackSize + mTuplesize > r->mCFstack.size())
            CfdgError::Error(mLocation, "Maximum stack depth exceeded");
        size_t s = r->mStackSize;
        r->mStackSize += mTuplesize;
        r->mCurrentSeed ^= mChildChange.modData.mRand64Seed;
        StackType* dest = r->mCFstack.data() + s;
        
        switch (mType) {
            case NumericType:
                if (mExpression->evaluate(&dest->number, mTuplesize, r) != mTuplesize)
                    CfdgError::Error(mExpression->where, 
                                   "Error evaluating parameters (too many or not enough).");
                break;
            case ModType: {
                Modification* smod = reinterpret_cast<Modification*> (dest);
                mChildChange.setVal(*smod, r);
                break;
            }
            case RuleType:
                new (&(dest->rule)) param_ptr(mExpression->evalArgs(r, p.mParameters.get()));
                break;
            default:
                CfdgError::Error(mExpression->where, "Unimplemented parameter type.");
                break;
        }
        
        r->mLogicalStackTop = r->mCFstack.data() + r->mStackSize;
    }
    
    void
    ASTrule::traverse(const Shape& parent, bool tr, RendererAST* r) const
    {
        r->mCurrentSeed = parent.mWorldState.mRand64Seed;
        
        if (isPath) {
            r->processPrimShape(parent, this);
        } else {
            mRuleBody.traverse(parent, tr, r, true);
        }
    }
    
    void ASTpathOp::traverse(const Shape& s, bool tr, RendererAST* r) const
    {
        if (r->mCurrentPath->mCached)
            return;
        double opData[7];
        pathData(opData, r);
        r->mCurrentPath->addPathOp(this, opData, s, tr, r);
    }
    
    void
    ASTpathCommand::traverse(const Shape& s, bool, RendererAST* r) const
    {
        if (r->mOpsOnly)
            CfdgError::Error(mLocation, "Path commands not allowed at this point");

        Shape child(s);
        double width = mStrokeWidth;
        replace(child, r);
        if (mParameters && mParameters->evaluate(&width, 1, r) != 1)
            CfdgError::Error(mParameters->where, "Error computing stroke width");
        
        CommandInfo* info = nullptr;
        
        if (r->mCurrentPath->mCached) {
            if (r->mCurrentCommand == r->mCurrentPath->mCommandInfo.end())
                CfdgError::Error(mLocation, "Not enough path commands in cache");
            info = &(*(r->mCurrentCommand++));
        } else {
            if (r->mCurrentPath->mPath.total_vertices() == 0)
                CfdgError::Error(mLocation, "Path commands must be preceeded by at least one path operation");
            
            r->mWantCommand = false;
            r->mCurrentPath->finish(false, r);

            mInfoCache.tryInit(r->mIndex, r->mCurrentPath.get(), width, this);
            if (mInfoCache.mPathUID == r->mCurrentPath->mPathUID && 
                mInfoCache.mIndex   == r->mIndex) 
            {
                r->mCurrentPath->mCommandInfo.push_back(mInfoCache);
            } else {
                r->mCurrentPath->mCommandInfo.emplace_back(r->mIndex, r->mCurrentPath.get(), width, this);
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
        
        cpath_ptr savedPath;
        
        if (mCachedPath && StackRule::Equal(mCachedPath->mParameters.get(), parent.mParameters.get())) {
            savedPath = std::move(r->mCurrentPath);
            r->mCurrentPath = std::move(mCachedPath);
            r->mCurrentCommand = r->mCurrentPath->mCommandInfo.begin();
        } else {
            r->mCurrentPath->mTerminalCommand.mLocation = mLocation;
        }
        
        mRuleBody.traverse(parent, false, r, true);
        if (!r->mCurrentPath->mCached)
            r->mCurrentPath->finish(true, r);
        if (r->mCurrentPath->mUseTerminal) 
            r->mCurrentPath->mTerminalCommand.traverse(parent, false, r);
        
        if (savedPath) {
            mCachedPath = std::move(r->mCurrentPath);
            r->mCurrentPath = std::move(savedPath);
        } else {
            if (!(r->mRandUsed) && !mCachedPath) {
                mCachedPath = std::move(r->mCurrentPath);
                mCachedPath->mCached = true;
                mCachedPath->mParameters = parent.mParameters;
                r->mCurrentPath.reset(new ASTcompiledPath());
            } else {
                r->mCurrentPath->mPath.remove_all();
                r->mCurrentPath->mCommandInfo.clear();
                r->mCurrentPath->mUseTerminal = false;
                r->mCurrentPath->mPathUID = ASTcompiledPath::NextPathUID();
                r->mCurrentPath->mParameters.reset();
            }
        }
    }
    
    void
    ASTreplacement::compile(AST::CompilePhase ph)
    {
        ASTexpression* r;
        r = mShapeSpec.compile(ph);             // always returns nullptr
        assert(r == nullptr);
        r = mChildChange.compile(ph);           // ditto
        assert(r == nullptr);

        switch (ph) {
            case CompilePhase::TypeCheck:
                mChildChange.addEntropy(mShapeSpec.entropyVal);
                if (typeid(ASTreplacement) == typeid(*this) && Builder::CurrentBuilder->mInPathContainer) {
                    // This is a subpath
                    if (mShapeSpec.argSource == ASTruleSpecifier::ShapeArgs ||
                        mShapeSpec.argSource == ASTruleSpecifier::StackArgs ||
                        primShape::isPrimShape(mShapeSpec.shapeType))
                    {
                        if (mRepType != op)
                            CfdgError::Error(mShapeSpec.where, "Error in subpath specification");
                    } else {
                        const ASTrule* rule = Builder::CurrentBuilder->GetRule(mShapeSpec.shapeType);
                        if (!rule || !rule->isPath)
                            CfdgError::Error(mShapeSpec.where, "Subpath can only refer to a path");
                        else if (rule->mRuleBody.mRepType != mRepType)
                            CfdgError::Error(mShapeSpec.where, "Subpath type mismatch error");
                    }
                }
                break;
            case CompilePhase::Simplify:
                r = mShapeSpec.simplify();          // always returns this
                assert(r == &mShapeSpec);
                r = mChildChange.simplify();        // ditto
                assert(r == &mChildChange);
                break;
        }
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
                
                std::string ent(mLoopName);
                mLoopArgs->entropy(ent);
                if (mLoopModHolder)
                    mChildChange.addEntropy(ent);
                
                bool bodyNatural = false;
                bool finallyNatural = false;
                Locality_t locality = mLoopArgs->mLocality;
                
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
                    
                    for (size_t i = 0, count = 0; i < mLoopArgs->size(); ++i) {
                        const ASTexpression* loopArg = mLoopArgs->getChild(i);
                        int num = loopArg->evaluate(nullptr, 0);
                        switch (count) {
                            case 0:
                                if (loopArg->isNatural)
                                    bodyNatural = finallyNatural = true;
                                break;
                            case 2: {
                                // Special case: if 1st & 2nd args are natural and 3rd
                                // is -1 then that is ok
                                double step;
                                if (loopArg->isConstant &&
                                    loopArg->evaluate(&step, 1) == 1 &&
                                    step == -1.0)
                                {
                                    break;
                                }
                            }   // else fall through
                            case 1:
                                if (!loopArg->isNatural)
                                    bodyNatural = finallyNatural = false;
                                break;
                            default:
                                break;
                        }
                        count += num;
                    }
                }
                
                mLoopBody.mParameters.front().isNatural = bodyNatural;
                mLoopBody.mParameters.front().mLocality = locality;
                mLoopBody.compile(ph, this, nullptr);
                mFinallyBody.mParameters.front().isNatural = finallyNatural;
                mFinallyBody.mParameters.front().mLocality = locality;
                mFinallyBody.compile(ph);
                
                if (!mLoopModHolder)
                    mChildChange.addEntropy(ent);
                break;
            }
            case CompilePhase::Simplify:
                Simplify(mLoopArgs);
                mLoopBody.compile(ph);
                mFinallyBody.compile(ph);
                break;
        }
    }
    
    void
    ASTloop::compileLoopMod()
    {
        if (mLoopModHolder) {
            mLoopModHolder->compile(CompilePhase::TypeCheck);
            mChildChange.grab(mLoopModHolder.get());
        } else {
            mChildChange.compile(CompilePhase::TypeCheck);
        }
    }
    
    void
    ASTtransform::compile(AST::CompilePhase ph)
    {
        ASTreplacement::compile(ph);
        ASTexpression* ret = nullptr;
        if (mExpHolder)
            ret = mExpHolder->compile(ph);        // always returns nullptr
        if (ret != nullptr)
            CfdgError::Error(mLocation, "Error analyzing transform list");
        mBody.compile(ph);

        switch (ph) {
            case CompilePhase::TypeCheck:
                if (mClone && !ASTparameter::Impure)
                    CfdgError::Error(mLocation, "Shape cloning only permitted in impure mode");
                break;
            case CompilePhase::Simplify:
                Simplify(mExpHolder);
                break;
        }
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
                Simplify(mCondition);
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
                Simplify(mSwitchExp);
                break;
        }
    }
    
    void
    ASTdefine::compile(AST::CompilePhase ph)
    {
        if (mDefineType == FunctionDefine || mDefineType == LetDefine) {
            ASTrepContainer tempCont;
            tempCont.mParameters = mParameters;     // copy
            tempCont.mStackCount = mStackCount;
            Builder::CurrentBuilder->push_repContainer(tempCont);
            ASTreplacement::compile(ph);
            Compile(mExpression, ph);
            if (ph == CompilePhase::Simplify)
                Simplify(mExpression);
            Builder::CurrentBuilder->pop_repContainer(nullptr);
        } else {
            ASTreplacement::compile(ph);
            Compile(mExpression, ph);
            if (ph == CompilePhase::Simplify)
                Simplify(mExpression);
        }
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                if (mDefineType == ConfigDefine) {
                    Builder::CurrentBuilder->MakeConfig(this);
                    return;
                }

                // Set the Modification entropy to parameter name, not its own contents
                mChildChange.modData.mRand64Seed.seed();
                mChildChange.entropyIndex = 0;
                mChildChange.addEntropy(mName);
                
                expType t = mExpression ? mExpression->mType : ModType;
                int sz = 1;
                if (t == NumericType)
                    sz = mExpression->evaluate(nullptr, 0);
                if (t == ModType)
                    sz = ModificationSize;
                if (mDefineType == FunctionDefine) {
                    if (t != mType)
                        CfdgError::Error(mLocation, "Mismatch between declared and defined type of user function");
                    if (mType == NumericType && t == NumericType && sz != mTuplesize)
                        CfdgError::Error(mLocation, "Mismatch between declared and defined vector length of user function");
                    if (isNatural && (!mExpression || !mExpression->isNatural) && !ASTparameter::Impure)
                        CfdgError::Error(mLocation, "Mismatch between declared natural and defined not-natural type of user function");
                } else {
                    if (mShapeSpec.shapeType >= 0) {
                        ASTdefine* func = nullptr;
                        const ASTparameters* shapeParams = nullptr;
                        Builder::CurrentBuilder->GetTypeInfo(mShapeSpec.shapeType, func, shapeParams);
                        if (func) {
                            CfdgError::Error(mLocation, "Variable name is also the name of a function");
                            CfdgError::Error(func->mLocation, "   function definition is here");
                        }
                        if (shapeParams)
                            CfdgError::Error(mLocation, "Variable name is also the name of a shape");
                    }
                    
                    mTuplesize = sz;
                    mType = t;
                    if (t != (t & (-t)) || !t)
                        CfdgError::Error(mLocation, "Expression can only have one type");
                    if (mDefineType == StackDefine && (mExpression ? mExpression->isConstant : mChildChange.modExp.empty()))
                        mDefineType = ConstDefine;
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
        Builder::CurrentBuilder->mInPathContainer = isPath;
        ASTreplacement::compile(ph);
        mRuleBody.compile(ph);
    }
    
    void
    ASTpathOp::compile(AST::CompilePhase ph)
    {
        ASTreplacement::compile(ph);
        Compile(mArguments, ph);
        if (mOldStyleArguments)
            mOldStyleArguments->compile(ph);        // always return nullptr
        
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
                Simplify(mArguments);
                break;
        }
    }
    
    static exp_ptr GetFlagsAndStroke(ASTtermArray& terms, int& flags)
    {
        ASTtermArray temp(std::move(terms));
        exp_ptr ret;
        
        for (term_ptr& term: temp) {
            switch (term->modType) {
                case AST::ASTmodTerm::param:
                    flags |= term->argCount;    // ctor stashes parsed params here and
                    break;                      // ASTmodTerm::compile() does not overwrite them
                case AST::ASTmodTerm::stroke:
                    if (ret)
                        CfdgError::Error(term->where, "Only one stroke width term is allowed");
                    ret = std::move(term->args);
                    break;
                default:
                    terms.emplace_back(std::move(term));
                    break;
            }
        }
        
        return ret;
    }
    
    void
    ASTpathCommand::compile(AST::CompilePhase ph)
    {
        ASTreplacement::compile(ph);
        Compile(mParameters, ph);
        
        switch (ph) {
            case CompilePhase::TypeCheck: {
                mChildChange.addEntropy((mFlags & CF_FILL) ? "FILL" : "STROKE");
                
                // Extract any stroke adjustments
                exp_ptr w = GetFlagsAndStroke(mChildChange.modExp, mFlags);
                if (w) {
                    if (mParameters)
                        CfdgError::Error(w->where, "Cannot have a stroke adjustment in a v3 path command");
                    else if (w->size() != 1 || w->mType != NumericType || w->evaluate(nullptr, 0) != 1)
                        CfdgError::Error(w->where, "Stroke adjustment is ill-formed");
                    else
                        mParameters = std::move(w);
                }
                
                if (!mParameters)
                    return;
                
                exp_ptr stroke, flags;
                yy::location loc = mParameters->where;
                ASTexpArray pcmdParams = Extract(std::move(mParameters));
                switch (pcmdParams.size()) {
                    case 2:
                        stroke = std::move(pcmdParams[0]);
                        flags = std::move(pcmdParams[1]);
                        break;
                    case 1:
                        switch (pcmdParams[0]->mType) {
                            case NumericType:
                                stroke = std::move(pcmdParams[0]);
                                break;
                            case FlagType:
                                flags = std::move(pcmdParams[0]);
                                break;
                            default:
                                CfdgError::Error(loc, "Bad expression type in path command parameters");
                                break;
                        }
                        break;
                    case 0:
                        return;
                    default:
                        CfdgError::Error(loc, "Path commands can have zero, one, or two parameters");
                        return;
                }
                
                if (stroke) {
                    if (mFlags & CF_FILL)
                        CfdgError::Warning(stroke->where, "Stroke width only useful for STROKE commands");
                    if (stroke->mType != NumericType || stroke->evaluate(nullptr, 0) != 1) {
                        CfdgError::Error(stroke->where, "Stroke width expression must be numeric scalar");
                    } else if (!stroke->isConstant ||
                               stroke->evaluate(&mStrokeWidth, 1) != 1)
                    {
                        mParameters = std::move(stroke);
                    }
                }
                
                if (flags) {
                    if (flags->mType != FlagType) {
                        CfdgError::Error(flags->where, "Unexpected argument in path command");
                        return;
                    }
                    Simplify(flags);
                    if (ASTreal* r = dynamic_cast<ASTreal*> (flags.get())) {
                        int f = static_cast<int>(r->value);
                        if (f & CF_JOIN_PRESENT)
                            mFlags &= ~CF_JOIN_MASK;
                        if (f & CF_CAP_PRESENT)
                            mFlags &= ~CF_CAP_MASK;
                        mFlags |= f;
                        if ((mFlags & CF_FILL) && (f & (CF_JOIN_PRESENT | CF_CAP_PRESENT)))
                            CfdgError::Warning(flags->where, "Stroke flags only useful for STROKE commands");
                    } else {
                        CfdgError::Error(flags->where, "Flag expressions must be constant");
                    }
                }
                break;
            }
            case CompilePhase::Simplify:
                Simplify(mParameters);
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

        for (size_t i = 0; mArguments && i < mArguments->size(); ++i) {
            const ASTexpression* temp = mArguments->getChild(i);
            assert(temp);
            switch (temp->mType) {
                case FlagType: {
                    if (i != mArguments->size() - 1)
                        CfdgError::Error(temp->where, "Flags must be the last argument");
                    if (const ASTreal* rf = dynamic_cast<const ASTreal*> (temp))
                        mFlags |= rf ? static_cast<int>(rf->value) : 0;
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
        int sz = 0;
        if (ax->mType == NumericType)
            sz = ax->evaluate(nullptr, 0);
        else
            CfdgError::Error(ax->where, "Path argument must be a scalar value");
        
        if (sz == 1 && !ay)
            ay.reset(new ASTreal(def, loc));
        
        if (ay && sz >= 0) {
            if (ay->mType == NumericType)
                sz += ay->evaluate(nullptr, 0);
            else
                CfdgError::Error(ay->where, "Path argument must be a scalar value");
        }
        
        if (sz != 2)
            CfdgError::Error(loc, "Error parsing path operation arguments");
        
        return ax.release()->append(ay.release());
    }
    
    static void
    rejectTerm(exp_ptr& term)
    {
        if (term)
            CfdgError::Error(term->where, "Illegal argument");
    }
    
    static void
    acquireTerm(exp_ptr& exp, term_ptr& term)
    {
        if (exp) {
            CfdgError::Error(exp->where, "Duplicate argument");
            CfdgError::Error(term->where, "    conflicts with this argument");
        }
        exp = std::move(term->args);
    }
    
    void
    ASTpathOp::makePositional()
    {
        exp_ptr w = GetFlagsAndStroke(mOldStyleArguments->modExp, mFlags);
        if (w)
            CfdgError::Error(w->where, "Stroke width not allowed in a path operation");
        
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
            if (!mod)
                continue;
            switch (mod->modType) {
                case ASTmodTerm::x:
                    acquireTerm(ax, mod);
                    break;
                case ASTmodTerm::y:
                    acquireTerm(ay, mod);
                    break;
                case ASTmodTerm::x1:
                    acquireTerm(ax1, mod);
                    break;
                case ASTmodTerm::y1:
                    acquireTerm(ay1, mod);
                    break;
                case ASTmodTerm::x2:
                    acquireTerm(ax2, mod);
                    break;
                case ASTmodTerm::y2:
                    acquireTerm(ay2, mod);
                    break;
                case ASTmodTerm::xrad:
                    acquireTerm(arx, mod);
                    break;
                case ASTmodTerm::yrad:
                    acquireTerm(ary, mod);
                    break;
                case ASTmodTerm::rot:
                    acquireTerm(ar, mod);
                    break;
                case ASTmodTerm::z:
                case ASTmodTerm::zsize:
                    CfdgError::Error(mod->where, "Z changes are not permitted in paths");
                    break;
                case ASTmodTerm::unknownType:
                default:
                    CfdgError::Error(mod->where, "Unrecognized element in a path operation");
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
                mArguments.reset(xy);
                break;
            case ARCTO:
            case ARCREL:
                if (arx || ary) {
                    ASTexpression* rxy = parseXY(std::move(arx), std::move(ary), 1.0, mLocation);
                    ASTexpression* angle = ar.release();
                    if (!angle)
                        angle = new ASTreal(0.0, mLocation);
                    
                    if (angle->mType != NumericType || angle->evaluate(nullptr, 0) != 1)
                        CfdgError(angle->where, "Arc angle must be a scalar value");
                    
                    mArguments.reset(xy->append(rxy)->append(angle));
                } else {
                    ASTexpression* radius = ar.release();
                    if (!radius)
                        radius = new ASTreal(1.0, mLocation);
                    
                    if (radius->mType != NumericType || radius->evaluate(nullptr, 0) != 1)
                        CfdgError::Error(radius->where, "Arc radius must be a scalar value");
                    
                    mArguments.reset(xy->append(radius));
                } 
                break;
            case CURVETO:
            case CURVEREL: {
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
                break;
            default:
                break;
        }
        
        rejectTerm(ax);
        rejectTerm(ay);
        rejectTerm(ar);
        rejectTerm(arx);
        rejectTerm(ary);
        rejectTerm(ax1);
        rejectTerm(ay1);
        rejectTerm(ax2);
        rejectTerm(ay2);
        
        mArgCount = mArguments ? mArguments->evaluate(nullptr, 0) : 0;
        mOldStyleArguments.reset();
    }
}
