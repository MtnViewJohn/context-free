// cfdgimpl.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2006-2013 John Horigan - john@glyphic.com
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

#include "agg_color_rgba.h"
#include "cfdg.h"
#include "shape.h"
#include "astreplacement.h"
#include "config.h"

class CFDGImpl : public CFDG {
    enum consts_t: unsigned { NoParameter = static_cast<unsigned>(-1) };
    public:
        enum {newShape = 0, ruleType = 1, pathType = 2};
        std::deque<const StackRule*>  mLongLivedParams;
    private:
        class LLPdeleter {
            friend CFDGImpl;
            CFDGImpl* parent;
            
            LLPdeleter(CFDGImpl* p) : parent(p) { }
            ~LLPdeleter() {
                for (auto&& param : parent->mLongLivedParams) {
                    delete[] param;
                    --Renderer::ParamCount;
                }
            }
        };
        LLPdeleter                      mCleanupLLP;
    
        agg::rgba m_backgroundColor;
    
        int mStackSize;

        struct ShapeType {
            std::string  name;
            bool    hasRules;
            bool    isShape;
            int    shapeType;
            std::unique_ptr<AST::ASTparameters> parameters;
            int     argSize;
            bool    shouldHaveNoParams;
            
            ShapeType(const std::string& s) 
            : name(s), hasRules(false), isShape(false), shapeType(newShape), 
              parameters(nullptr), argSize(0), shouldHaveNoParams(false) { }

            ShapeType(ShapeType&& from) NOEXCEPT
                : name(std::move(from.name)), hasRules(from.hasRules), isShape(from.isShape),
                  shapeType(from.shapeType), parameters(std::move(from.parameters)), 
                  argSize(from.argSize), shouldHaveNoParams(from.shouldHaveNoParams) { }

            ShapeType& operator=(ShapeType&& from) NOEXCEPT {
                if (this == &from) return *this;
                name = std::move(from.name); hasRules = from.hasRules; isShape = from.isShape;
                shapeType = from.shapeType; parameters = std::move(from.parameters); 
                argSize = from.argSize; shouldHaveNoParams = from.shouldHaveNoParams;
                return *this;
            }
            ShapeType(const ShapeType&) = delete;
            ShapeType& operator=(const ShapeType&) = delete;
        };
        
        std::vector<ShapeType> m_shapeTypes;
    
        Shape m_initialShape;

    public:
        AST::rep_ptr mInitShape;
        std::vector<AST::ASTrule*> mRules;
        std::map<int, AST::ASTdefine*> mFunctions;
    
        AbstractSystem* m_system;
    
        int m_Parameters;
    
        CfgArray<unsigned>                  ParamDepth;
        CfgArray<AST::exp_ptr>              ParamExp;
    
    

        Modification mTileMod;
        Modification mSizeMod;
        Modification mTimeMod;
        agg::point_d mTileOffset;
    
        AST::ASTrule needle;
        
    public:
        CFDGImpl(AbstractSystem*);
        ~CFDGImpl() override;
        
        Renderer* renderer(
                int width, int height, double minSize,
                int variation, double border = 2.0) override;
        
        bool isTiled(agg::trans_affine* tr = nullptr, double* x = nullptr, double* y = nullptr) const override;
        frieze_t isFrieze(agg::trans_affine* tr = nullptr, double* x = nullptr, double* y = nullptr) const override;
        bool isSized(double* x = nullptr, double* y = nullptr) const override;
        bool isTimed(agg::trans_affine_time* t = nullptr) const override;
        const agg::rgba& getBackgroundColor() override;
        void setBackgroundColor(RendererAST* r);
        void getSymmetry(AST::SymmList& syms, RendererAST* r);
    
        const AST::ASTexpression* hasParameter(CFG name) const;
        bool hasParameter(CFG name, double& value, RendererAST* r) const;
        bool hasParameter(CFG name, Modification& value, RendererAST* r) const;
        bool hasParameter(CFG name, AST::expType t, yy::location& where) const;

    public:
        AbstractSystem* system() { return m_system; }
        
        const Shape& getInitialShape(RendererAST* r);
    
        RGBA8 getColor(const HSBColor& hsb);
        
        bool addRule(AST::ASTrule* r);
        void rulesLoaded();
        int numRules();
        const AST::ASTrule* findRule(int shapetype, double r);
        const AST::ASTrule* findRule(int shapetype);

        std::string  decodeShapeName(int shapetype);
        int     encodeShapeName(const std::string& s);
        int     tryEncodeShapeName(const std::string& s) const;
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

        enum Parameter {Color = 1, Alpha = 2, Time = 4, FrameTime = 8};
        void addParameter(Parameter);
        bool addParameter(std::string name, AST::exp_ptr e, unsigned depth);

        AST::ASTrepContainer    mCFDGcontents;
    
        std::list<std::string> fileNames;
};

typedef std::unique_ptr<CFDGImpl> cfdgi_ptr;

#endif // INCLUDE_CFDGIMPL_H
