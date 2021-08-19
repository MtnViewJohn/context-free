// cfdgimpl.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2006-2016 John Horigan - john@glyphic.com
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
// Mark Lentczner can be contacted at markl@glyphic.com or at
// Mark Lentczner, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//


#ifndef INCLUDE_CFDGIMPL_H
#define INCLUDE_CFDGIMPL_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <deque>
#include <type_traits>

#include "agg2/agg_color_rgba.h"
#include "cfdg.h"
#include "shape.h"
#include "astreplacement.h"
#include "config.h"
#include "stacktype.h"
class Builder;

class CFDGImpl : public CFDG {
    enum consts_t: int { NoParameter = std::numeric_limits<int>::max() };
    public:
        enum {newShape = 0, ruleType = 1, pathType = 2};
    private:
        struct PostDtorCleanup {
            AbstractSystem* msys;
            PostDtorCleanup(AbstractSystem* s) : msys(s) {}
            ~PostDtorCleanup() {
    #ifdef EXTREME_PARAM_DEBUG
                for (auto &p: StackRule::ParamMap) {
                    if (p.second > 0)
                        msys->message("Parameter at %p is still alive, it is param number %d\n", p.first, p.second);
                }
    #endif
            }
        };
    
        PostDtorCleanup mPostDtorCleanup;
        agg::rgba m_backgroundColor = {1, 1, 1, 1};
    
        int mStackSize = 0;
        int mDefaultShape = -1;

        struct ShapeType {
            std::string  name;
            std::wstring canonicalName;
            yy::location firstUse;
            bool    hasRules;
            bool    isShape;
            int    shapeType;
            // Heap allocated so that address survives vector reallocations
            std::unique_ptr<AST::ASTparameters> parameters;
            int     argSize;
            bool    shouldHaveNoParams;
            
            ShapeType(std::string s, std::wstring cname, const yy::location& where)
            : name(std::move(s)), canonicalName(std::move(cname)), firstUse(where), hasRules(false),
              isShape(false), shapeType(newShape), parameters(nullptr), argSize(0),
              shouldHaveNoParams(false) { }

            ShapeType(ShapeType&& from) noexcept = default;
            ShapeType& operator=(ShapeType&& from) noexcept(std::is_nothrow_move_assignable<std::string>::value)
            {
                name = std::move(from.name);
                canonicalName = std::move(from.canonicalName);
                firstUse = from.firstUse;
                hasRules = from.hasRules;
                isShape = from.isShape;
                parameters = std::move(from.parameters);
                argSize = from.argSize;
                shouldHaveNoParams = from.shouldHaveNoParams;
                return *this;
            }
            ShapeType(const ShapeType&) = delete;
            ShapeType& operator=(const ShapeType&) = delete;
        };
        
        std::vector<ShapeType> m_shapeTypes;
    
        void initVariables();
    
    public:
        AST::rep_ptr mInitShape;
        std::vector<AST::ASTrule*> mRules;
        std::map<int, AST::ASTdefine*> mFunctions;
    
        AbstractSystem* m_system = nullptr;
        Builder*        m_builder = nullptr;
        bool            m_impure = false;
    
        int m_Parameters = 0;
    
        CfgArray<int>                       ParamDepth = NoParameter;
        CfgArray<AST::exp_ptr>              ParamExp;
    
    

        Modification mTileMod;
        Modification mSizeMod;
        Modification mTimeMod;
        agg::point_d mTileOffset = {0, 0};
    
        AST::ASTrule needle = {0, CfdgError::Default};
        
    public:
        CFDGImpl(AbstractSystem*);
        ~CFDGImpl() override;
        
        renderer_ptr renderer(const cfdg_ptr& ptr,
                int width, int height, double minSize,
                int variation, double border = 2.0) override;
        
        bool isTiled(agg::trans_affine* tr = nullptr, double* x = nullptr, double* y = nullptr) const override;
        frieze_t isFrieze(agg::trans_affine* tr = nullptr, double* x = nullptr, double* y = nullptr) const override;
        bool isSized(double* x = nullptr, double* y = nullptr) const override;
        bool isTimed(agg::trans_affine_time* t = nullptr) const override;
        const agg::rgba& getBackgroundColor() override;
        void serialize(std::ostream&) override;
        void setBackgroundColor(RendererAST* r);
        void getSymmetry(AST::SymmList& syms, RendererAST* r);
    
        const AST::ASTexpression* hasParameter(CFG name) const;
        bool hasParameter(CFG name, double& value, RendererAST* r) const;
        bool hasParameter(CFG name, Modification& value, RendererAST* r) const;
        bool hasParameter(CFG name, AST::expType t, yy::location& where) const;

    public:
        AbstractSystem* system() { return m_system; }
        
        Shape getInitialShape(RendererAST* r);
    
        RGBA8 getColor(const HSBColor& hsb);
        
        bool addRule(AST::ASTrule* r);
        void rulesLoaded();
        int numRules();
        const AST::ASTrule* findRule(int shapetype, double r);
        const AST::ASTrule* findRule(int shapetype);

        std::string  decodeShapeName(int shapetype);
        const yy::location& decodeShapeLocation(int shapetype);
        int     encodeShapeName(const std::string& s, const yy::location& where);
        int     tryEncodeShapeName(const std::string& s) const;
        int     tryEncodeShapeName(const std::wstring& s) const;
        int     getShapeType(int shapetype);
        bool    shapeHasRules(int shapetype);
        const char* setShapeParams(int shapetype, AST::ASTrepContainer& p, int size, bool isPath);
        void    setShapeHasNoParams(int shapetype, const AST::ASTexpression* args);
        bool    getShapeHasNoParams(int shapetype);
        const AST::ASTparameters* getShapeParams(int shapetype) const;
        int getShapeParamSize(int shapetype);
        int reportStackDepth(int size = 0); 
        void resetCachedPaths();

        AST::ASTdefine* declareFunction(int nameIndex, AST::ASTdefine* def);
        AST::ASTdefine* findFunction(int nameIndex);

        enum Parameter {Color = 1, Alpha = 2, Time = 4, FrameTime = 8, Blend = 16};
        void addParameter(Parameter);
        void addParameter(CFG var, AST::exp_ptr e, int depth);

        AST::ASTrepContainer    mCFDGcontents;
    
        std::list<std::string> fileNames;
};

using cfdgi_ptr = std::shared_ptr<CFDGImpl>;

#endif // INCLUDE_CFDGIMPL_H
