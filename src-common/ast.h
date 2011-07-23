// ast.h
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


#ifndef INCLUDE_AST_H
#define INCLUDE_AST_H

#include <list>
#include <memory>
#include <vector>
#include <string>
#include "agg_math_stroke.h"

namespace AST {

#ifdef _WIN32
    inline double acosh(double x) 
    {
        return log(x + sqrt(x * x - 1));
    }
    
    inline double asinh(double x) 
    {
        return log(x + sqrt(x * x + 1));
    }
    
    inline double atanh(double x) 
    {
        return log((1 + x) / (1 - x)) / 2;
    }
    
    inline double fmin(const double& x, const double& y)
    {
        return x < y ? x : y;
    }
    
    inline double fmax(const double& x, const double& y)
    {
        return x > y ? x : y;
    }

#pragma warning( disable : 4521 )
#endif

    class ASTpath;
    typedef std::list<ASTpath*> ASTpathList;
    class ASTreplacement;
    typedef std::list<const ASTreplacement*> ASTbody;
    class ASTparameterList;
    class ASTparameter;
    class ASTrule;
    class ASTcompiledPath;
    class ASTpathOp;
    class ASTmod;
    class ASTexpression;
    class ASTmodification;
    class ASTruleSpecifier;
    class ASTloop;
    class ASTif;
    class ASTswitch;
    class ASTmodTerm;
    typedef std::vector<ASTexpression*> ASTexpArray;
    typedef std::list<ASTparameter> ASTparameters;

    typedef std::auto_ptr<std::string>      str_ptr;
    typedef std::auto_ptr<ASTexpression>    exp_ptr;
    typedef std::auto_ptr<ASTreplacement>   rep_ptr;
    typedef std::auto_ptr<ASTruleSpecifier> ruleSpec_ptr;
    typedef std::auto_ptr<ASTrule>          rule_ptr;
    typedef std::auto_ptr<ASTloop>          loop_ptr;
    typedef std::auto_ptr<ASTif>            if_ptr;
    typedef std::auto_ptr<ASTswitch>        switch_ptr;
    typedef std::auto_ptr<ASTmodTerm>       term_ptr;
    
    enum FlagTypes {
        CF_NONE = 0,
        CF_MITER_JOIN = agg::miter_join,
        CF_ROUND_JOIN = agg::round_join,
        CF_BEVEL_JOIN = agg::bevel_join,
        CF_BUTT_CAP = agg::butt_cap << 4,
        CF_ROUND_CAP = agg::round_cap << 4,
        CF_SQUARE_CAP = agg::square_cap << 4,
        CF_ARC_CW = 1 << 8,
        CF_ARC_LARGE = 1 << 9,
        CF_CONTINUOUS = 1 << 10,
        CF_ALIGN = 1 << 11,
        CF_EVEN_ODD = 1 << 12,
        CF_ISO_WIDTH = 1 << 13,
        CF_FILL = 1 << 14
    };
    
    double CFatof(const char* s);

    enum pathOpEnum { 
        unknownPathop = -1, MOVETO = 0, MOVEREL, LINETO, LINEREL, 
        ARCTO, ARCREL, CURVETO, CURVEREL, CLOSEPOLY
    };
    
}

#endif // INCLUDE_AST_H
