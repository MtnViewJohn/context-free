// ast.h
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


#ifndef INCLUDE_AST_H
#define INCLUDE_AST_H

#include <memory>
#include <vector>
#include <string>
#include "agg_math_stroke.h"
#include "agg_trans_affine.h"
#include "location.hh"
#include <stdint.h>
#include "mynoexcept.h"

class RendererAST;

namespace AST {
    typedef std::vector<agg::trans_affine> SymmList;
    typedef uint_fast32_t UIDdatatype;

    class ASTpath;
    class ASTreplacement;
    class ASTparameter;
    class ASTrule;
    class ASTcompiledPath;
    class ASTpathOp;
    class ASTexpression;
    class ASTmodification;
    class ASTruleSpecifier;
    class ASTloop;
    class ASTif;
    class ASTswitch;
    class ASTmodTerm;
    class ASTrepContainer;
    class ASTdefine;
    class ASTcompiledPath;

    typedef std::unique_ptr<std::string>      str_ptr;
    typedef std::unique_ptr<ASTexpression>    exp_ptr;
    typedef std::unique_ptr<ASTreplacement>   rep_ptr;
    typedef std::unique_ptr<ASTruleSpecifier> ruleSpec_ptr;
    typedef std::unique_ptr<ASTrule>          rule_ptr;
    typedef std::unique_ptr<ASTloop>          loop_ptr;
    typedef std::unique_ptr<ASTif>            if_ptr;
    typedef std::unique_ptr<ASTswitch>        switch_ptr;
    typedef std::unique_ptr<ASTmodTerm>       term_ptr;
    typedef std::unique_ptr<ASTmodification>  mod_ptr;
    typedef std::unique_ptr<ASTrepContainer>  cont_ptr;
    typedef std::unique_ptr<ASTdefine>        def_ptr;
    typedef std::unique_ptr<ASTcompiledPath>  cpath_ptr;
    
    typedef std::vector<rep_ptr>              ASTbody;
    typedef std::vector<exp_ptr>              ASTexpArray;
    typedef std::vector<term_ptr>             ASTtermArray;
    typedef std::vector<ASTparameter>         ASTparameters;
    
    enum expType {
        NoType = 0, NumericType = 1, ModType = 2, RuleType = 4, FlagType = 8,
        ReuseType = 16
    };
    enum Locality_t {
        UnknownLocal = 0,       // not known if dependent on parameters
        ImpureNonlocal = 1,     // dependent on parameters that have been modified
        PureNonlocal = 3,       // dependent on parameters that have not been modified
        PureLocal = 7           // not dependent on parameters
    };
    enum class CompilePhase {
        TypeCheck, Simplify
    };
    enum consts_e { MaxVectorSize = 99 };
    
    expType decodeType(const std::string& typeName, int& mTuplesize,
                       bool& isNatural, const yy::location& mLocation);
    
    class ASTdefine;
    
    class ASTparameter {
    public:
        expType     mType;
        bool        isParameter;
        bool        isLoopIndex;
        bool        isNatural;
        Locality_t  mLocality;
        int         mName;
        yy::location mLocation;
        ASTdefine*  mDefinition;        // weak pointer
        int         mStackIndex;
        int         mTuplesize;
        
        static bool Impure;
        
        ASTparameter();
        ASTparameter(const std::string& typeName, int nameIndex,
                     const yy::location& where);
        ASTparameter(int nameIndex, ASTdefine* def, const yy::location& where);
        ASTparameter(int nameIndex, bool natural, bool local, const yy::location& where);
                // ctor for loop variables
        ASTparameter(const ASTparameter&);
                // ctor for copying parameter lists, never used after definitions are added
        ASTparameter(ASTparameter&&) NOEXCEPT;
        ASTparameter& operator=(const ASTparameter&);
                // method for copying parameter lists, never used after definitions are added
        ASTparameter& operator=(ASTparameter&&) NOEXCEPT;
        void init(const std::string& typeName, int nameIndex);
        void init(int nameIndex, ASTdefine*  def);
        void checkParam(const yy::location& typeLoc, const yy::location& nameLoc);
        bool operator!=(const ASTparameter& p) const;
        bool operator!=(const ASTexpression& e) const;
        
        ASTexpression*
        constCopy(const yy::location& where, const std::string& entropy) const;
        
        static int CheckType(const ASTparameters* types, const ASTexpression* args,
                            const yy::location& where, bool checkNumber);
    };

    enum FlagTypes {
        CF_NONE = 0,
        CF_MITER_JOIN = agg::miter_join,
        CF_ROUND_JOIN = agg::round_join,
        CF_BEVEL_JOIN = agg::bevel_join,
        CF_JOIN_MASK = 0x7,
        CF_JOIN_PRESENT = 8,
        CF_BUTT_CAP = agg::butt_cap << 4,
        CF_ROUND_CAP = agg::round_cap << 4,
        CF_SQUARE_CAP = agg::square_cap << 4,
        CF_CAP_MASK = 0x7 << 4,
        CF_CAP_PRESENT = 8 << 4,
        CF_ARC_CW = 1 << 8,
        CF_ARC_LARGE = 1 << 9,
        CF_CONTINUOUS = 1 << 10,
        CF_ALIGN = 1 << 11,
        CF_EVEN_ODD = 1 << 12,
        CF_ISO_WIDTH = 1 << 13,
        CF_FILL = 1 << 14,
        CF_CYCLIC = 31 << 15,
        CF_DIHEDRAL = 1 << 15,
        CF_P11G = 2 << 15,
        CF_P11M = 3 << 15,
        CF_P1M1 = 4 << 15,
        CF_P2 = 30 << 15,
        CF_P2MG = 6 << 15,
        CF_P2MM = 7 << 15,
        CF_PM = 8 << 15,
        CF_PG = 9 << 15,
        CF_CM = 10 << 15,
        CF_PMM = 11 << 15,
        CF_PMG = 12 << 15,
        CF_PGG = 13 << 15,
        CF_CMM = 14 << 15,
        CF_P4 = 15 << 15,
        CF_P4M = 16 << 15,
        CF_P4G = 17 << 15,
        CF_P3 = 18 << 15,
        CF_P3M1 = 19 << 15,
        CF_P31M = 20 << 15,
        CF_P6 = 21 << 15,
        CF_P6M = 22 << 15
    };
    
    double CFatof(const char* s);
    
    Locality_t CombineLocality(Locality_t first, Locality_t second);

    enum pathOpEnum { 
        unknownPathop = -1, MOVETO = 0, MOVEREL, LINETO, LINEREL, 
        ARCTO, ARCREL, CURVETO, CURVEREL, CLOSEPOLY
    };
    
    void addUnique(SymmList& syms, agg::trans_affine& tr);
    void processDihedral(SymmList& syms, double order, double x, double y,
                         bool dihedral, double angle, const yy::location& where);
    void processSymmSpec(SymmList& syms, agg::trans_affine& tile, bool tiled,
                         std::vector<double>& data, const yy::location& where);
    std::vector<const ASTmodification*>
         getTransforms(const ASTexpression* e, SymmList& syms, 
                       RendererAST* r, bool tiled, agg::trans_affine& tile);
}

#endif // INCLUDE_AST_H
