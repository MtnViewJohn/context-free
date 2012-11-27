/* A Bison parser, made by GNU Bison 2.6.5.993-06ec-dirty.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++

   Copyright (C) 2002-2012 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


// First part of user declarations.
/* Line 369 of lalr1.cc  */
#line 41 "../../src-common/cfdg.ypp"

#include "builder.h"
#include <string>
#include <list>
namespace AST {
    class ASTexpression;
    class ASTmodTerm;
    class ASTmodification;
    class ASTpath;
    class ASTreplacement;
    class ASTbodyContainer;
    class ASTshape;
    class ASTloop;
    class ASTif;
    class ASTswitch;
    class ASTpathBody;
    class ASTpathLoop;
    class ASTruleSpecifier;
    class ASTrule;
}

/* Line 369 of lalr1.cc  */
#line 60 "cfdg.tab.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

#include "cfdg.tab.hpp"

/* User implementation prologue.  */
/* Line 377 of lalr1.cc  */
#line 80 "../../src-common/cfdg.ypp"

#include "astreplacement.h"
#include "astexpression.h"
    
    using namespace AST;
/* Line 377 of lalr1.cc  */
#line 176 "../../src-common/cfdg.ypp"

#include "scanner.h"
#include "math.h"
#include "builder.h"
#include <cassert>

#undef yylex
#define yylex driver.lexer->lex

/* Line 377 of lalr1.cc  */
#line 92 "cfdg.tab.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif /* !YYDEBUG */

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
/* Line 444 of lalr1.cc  */
#line 179 "cfdg.tab.cpp"

  /// Build a parser object.
  CfdgParser::CfdgParser (class Builder& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {
  }

  CfdgParser::~CfdgParser ()
  {
  }


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  CfdgParser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // symbol_base_type.
  template <typename Exact>
  inline
  CfdgParser::symbol_base_type<Exact>::symbol_base_type ()
    : value()
    , location()
  {
  }

  template <typename Exact>
  inline
  CfdgParser::symbol_base_type<Exact>::symbol_base_type (const location_type& l)
    : value()
    , location(l)
  {
  }

  template <typename Exact>
  inline
  CfdgParser::symbol_base_type<Exact>::symbol_base_type (const semantic_type& v, const location_type& l)
    : value(v)
    , location(l)
  {
  }

  template <typename Exact>
  inline
  const Exact&
  CfdgParser::symbol_base_type<Exact>::self () const
  {
    return static_cast<const Exact&>(*this);
  }

  template <typename Exact>
  inline
  Exact&
  CfdgParser::symbol_base_type<Exact>::self ()
  {
    return static_cast<Exact&>(*this);
  }

  template <typename Exact>
  inline
  int
  CfdgParser::symbol_base_type<Exact>::type_get () const
  {
    return self ().type_get_ ();
  }

  // symbol_type.
  inline
  CfdgParser::symbol_type::symbol_type ()
    : super_type ()
    , type ()
  {
  }

  inline
  CfdgParser::symbol_type::symbol_type (token_type t, const location_type& l)
    : super_type (l)
    , type (yytranslate_ (t))
  {
  }

  inline
  CfdgParser::symbol_type::symbol_type (token_type t, const semantic_type& v, const location_type& l)
    : super_type (v, l)
    , type (yytranslate_ (t))
  {
  }

  inline
  int
  CfdgParser::symbol_type::type_get_ () const
  {
    return type;
  }


  // stack_symbol_type.
  CfdgParser::stack_symbol_type::stack_symbol_type ()
    : super_type ()
    , state ()
  {
  }

  CfdgParser::stack_symbol_type::stack_symbol_type (state_type s, const semantic_type& v, const location_type& l)
    : super_type (v, l)
    , state (s)
  {
  }

  int
  CfdgParser::stack_symbol_type::type_get_ () const
  {
    return yystos_[state];
  }


  template <typename Exact>
  void
  CfdgParser::yy_destroy_ (const char* yymsg,
                                       symbol_base_type<Exact>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    int yytype = yysym.type_get ();
    switch (yytype)
      {
            case 26: // USER_STRING

/* Line 540 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete (yysym.value.string); }
/* Line 540 of lalr1.cc  */
#line 324 "cfdg.tab.cpp"
        break;

            case 29: // USER_FILENAME

/* Line 540 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete (yysym.value.string); }
/* Line 540 of lalr1.cc  */
#line 333 "cfdg.tab.cpp"
        break;

            case 30: // USER_QSTRING

/* Line 540 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete (yysym.value.string); }
/* Line 540 of lalr1.cc  */
#line 342 "cfdg.tab.cpp"
        break;

            case 31: // USER_ARRAYNAME

/* Line 540 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete (yysym.value.string); }
/* Line 540 of lalr1.cc  */
#line 351 "cfdg.tab.cpp"
        break;

            case 36: // USER_PATHOP

/* Line 540 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete (yysym.value.string); }
/* Line 540 of lalr1.cc  */
#line 360 "cfdg.tab.cpp"
        break;

            case 72: // statement

/* Line 540 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
        { delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 369 "cfdg.tab.cpp"
        break;

            case 73: // statement_v2

/* Line 540 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
        { delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 378 "cfdg.tab.cpp"
        break;

            case 79: // fileString

/* Line 540 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete (yysym.value.string); }
/* Line 540 of lalr1.cc  */
#line 387 "cfdg.tab.cpp"
        break;

            case 80: // fileNameSpace

/* Line 540 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete (yysym.value.string); }
/* Line 540 of lalr1.cc  */
#line 396 "cfdg.tab.cpp"
        break;

            case 81: // initialization

/* Line 540 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
        { delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 405 "cfdg.tab.cpp"
        break;

            case 82: // initialization_v2

/* Line 540 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
        { delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 414 "cfdg.tab.cpp"
        break;

            case 83: // background

/* Line 540 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
        { delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 423 "cfdg.tab.cpp"
        break;

            case 84: // tile

/* Line 540 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
        { delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 432 "cfdg.tab.cpp"
        break;

            case 85: // size

/* Line 540 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
        { delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 441 "cfdg.tab.cpp"
        break;

            case 87: // global_definition_header

/* Line 540 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete (yysym.value.string); }
/* Line 540 of lalr1.cc  */
#line 450 "cfdg.tab.cpp"
        break;

            case 88: // definition_header

/* Line 540 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete (yysym.value.string); }
/* Line 540 of lalr1.cc  */
#line 459 "cfdg.tab.cpp"
        break;

            case 90: // shape

/* Line 540 of lalr1.cc  */
#line 173 "../../src-common/cfdg.ypp"
        { delete (yysym.value.shapeObj); }
/* Line 540 of lalr1.cc  */
#line 468 "cfdg.tab.cpp"
        break;

            case 91: // shape_singleton_header

/* Line 540 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yysym.value.ruleObj); }
/* Line 540 of lalr1.cc  */
#line 477 "cfdg.tab.cpp"
        break;

            case 92: // shape_singleton

/* Line 540 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
        { delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 486 "cfdg.tab.cpp"
        break;

            case 93: // rule_header_v2

/* Line 540 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(NULL); delete (yysym.value.ruleObj); }
/* Line 540 of lalr1.cc  */
#line 495 "cfdg.tab.cpp"
        break;

            case 95: // rule_header

/* Line 540 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"
        { if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yysym.value.ruleObj); }
/* Line 540 of lalr1.cc  */
#line 504 "cfdg.tab.cpp"
        break;

            case 96: // path_header

/* Line 540 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"
        { if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yysym.value.ruleObj); }
/* Line 540 of lalr1.cc  */
#line 513 "cfdg.tab.cpp"
        break;

            case 97: // rule

/* Line 540 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
        { delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 522 "cfdg.tab.cpp"
        break;

            case 98: // path

/* Line 540 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
        { delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 531 "cfdg.tab.cpp"
        break;

            case 99: // path_header_v2

/* Line 540 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(NULL); delete (yysym.value.ruleObj); }
/* Line 540 of lalr1.cc  */
#line 540 "cfdg.tab.cpp"
        break;

            case 105: // parameter_spec

/* Line 540 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
        { delete (yysym.value.expression); }
/* Line 540 of lalr1.cc  */
#line 549 "cfdg.tab.cpp"
        break;

            case 108: // pathOp_simple_v2

/* Line 540 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
        { delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 558 "cfdg.tab.cpp"
        break;

            case 109: // element_simple

/* Line 540 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
        { delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 567 "cfdg.tab.cpp"
        break;

            case 114: // element

/* Line 540 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
        { delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 576 "cfdg.tab.cpp"
        break;

            case 117: // pathOp_v2

/* Line 540 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
        { delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 585 "cfdg.tab.cpp"
        break;

            case 119: // element_loop

/* Line 540 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
        { if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yysym.value.loopObj); }
/* Line 540 of lalr1.cc  */
#line 594 "cfdg.tab.cpp"
        break;

            case 122: // replacement_simple_v2

/* Line 540 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
        { delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 603 "cfdg.tab.cpp"
        break;

            case 123: // replacement_v2

/* Line 540 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
        { delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 612 "cfdg.tab.cpp"
        break;

            case 124: // loopHeader_v2

/* Line 540 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(NULL); delete (yysym.value.loopObj); }
/* Line 540 of lalr1.cc  */
#line 621 "cfdg.tab.cpp"
        break;

            case 126: // loopHeader

/* Line 540 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
        { if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yysym.value.loopObj); }
/* Line 540 of lalr1.cc  */
#line 630 "cfdg.tab.cpp"
        break;

            case 127: // ifHeader

/* Line 540 of lalr1.cc  */
#line 171 "../../src-common/cfdg.ypp"
        { if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yysym.value.ifObj); }
/* Line 540 of lalr1.cc  */
#line 639 "cfdg.tab.cpp"
        break;

            case 128: // ifElseHeader

/* Line 540 of lalr1.cc  */
#line 171 "../../src-common/cfdg.ypp"
        { if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yysym.value.ifObj); }
/* Line 540 of lalr1.cc  */
#line 648 "cfdg.tab.cpp"
        break;

            case 129: // transHeader

/* Line 540 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yysym.value.component); }
/* Line 540 of lalr1.cc  */
#line 657 "cfdg.tab.cpp"
        break;

            case 130: // switchHeader

/* Line 540 of lalr1.cc  */
#line 172 "../../src-common/cfdg.ypp"
        { delete (yysym.value.switchObj); }
/* Line 540 of lalr1.cc  */
#line 666 "cfdg.tab.cpp"
        break;

            case 131: // caseHeader

/* Line 540 of lalr1.cc  */
#line 174 "../../src-common/cfdg.ypp"
        { if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); }
/* Line 540 of lalr1.cc  */
#line 675 "cfdg.tab.cpp"
        break;

            case 132: // modification_v2

/* Line 540 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
        { delete (yysym.value.mod); }
/* Line 540 of lalr1.cc  */
#line 684 "cfdg.tab.cpp"
        break;

            case 133: // modification

/* Line 540 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
        { delete (yysym.value.mod); }
/* Line 540 of lalr1.cc  */
#line 693 "cfdg.tab.cpp"
        break;

            case 134: // buncha_adjustments

/* Line 540 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
        { delete (yysym.value.mod); }
/* Line 540 of lalr1.cc  */
#line 702 "cfdg.tab.cpp"
        break;

            case 135: // adjustment

/* Line 540 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete (yysym.value.term); }
/* Line 540 of lalr1.cc  */
#line 711 "cfdg.tab.cpp"
        break;

            case 136: // letHeader

/* Line 540 of lalr1.cc  */
#line 175 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(NULL); delete (yysym.value.bodyObj); }
/* Line 540 of lalr1.cc  */
#line 720 "cfdg.tab.cpp"
        break;

            case 137: // letBody

/* Line 540 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
        { delete (yysym.value.expression); }
/* Line 540 of lalr1.cc  */
#line 729 "cfdg.tab.cpp"
        break;

            case 140: // explist

/* Line 540 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
        { delete (yysym.value.expression); }
/* Line 540 of lalr1.cc  */
#line 738 "cfdg.tab.cpp"
        break;

            case 141: // arglist

/* Line 540 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
        { delete (yysym.value.expression); }
/* Line 540 of lalr1.cc  */
#line 747 "cfdg.tab.cpp"
        break;

            case 142: // exp

/* Line 540 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
        { delete (yysym.value.expression); }
/* Line 540 of lalr1.cc  */
#line 756 "cfdg.tab.cpp"
        break;

            case 143: // exp2

/* Line 540 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
        { delete (yysym.value.expression); }
/* Line 540 of lalr1.cc  */
#line 765 "cfdg.tab.cpp"
        break;

            case 144: // exp3

/* Line 540 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
        { delete (yysym.value.expression); }
/* Line 540 of lalr1.cc  */
#line 774 "cfdg.tab.cpp"
        break;

            case 145: // expfunc

/* Line 540 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
        { delete (yysym.value.expression); }
/* Line 540 of lalr1.cc  */
#line 783 "cfdg.tab.cpp"
        break;

            case 146: // exp2func

/* Line 540 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
        { delete (yysym.value.expression); }
/* Line 540 of lalr1.cc  */
#line 792 "cfdg.tab.cpp"
        break;

            case 147: // shapeName

/* Line 540 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete (yysym.value.string); }
/* Line 540 of lalr1.cc  */
#line 801 "cfdg.tab.cpp"
        break;

       default:
          break;
      }
  }

#if YYDEBUG
  template <typename Exact>
  void
  CfdgParser::yy_print_ (std::ostream& yyo,
                                     const symbol_base_type<Exact>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    int yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
      {
       default:
          break;
      }
    yyo << ')';
  }
#endif

  void
  CfdgParser::yypush_ (const char* m, state_type s,
                                   symbol_type& sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (stack_symbol_type (s, sym.value, sym.location));
  }

  void
  CfdgParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  void
  CfdgParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  CfdgParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  CfdgParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  CfdgParser::debug_level_type
  CfdgParser::debug_level () const
  {
    return yydebug_;
  }

  void
  CfdgParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline CfdgParser::state_type
  CfdgParser::yy_lr_goto_state_ (state_type yystate, int yylhs)
  {
    int yyr = yypgoto_[yylhs - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yylhs - yyntokens_];
  }

  inline bool
  CfdgParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  CfdgParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  CfdgParser::parse ()
  {
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// $$ and @$.
    stack_symbol_type yylhs;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_ = stack_type (0);
    yypush_ (YY_NULL, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    /* Accept?  */
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    /* Read a lookahead token.  */
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, driver));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    /* Discard the token being shifted.  */
    yyempty = true;

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    /* Shift the lookahead token.  */
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYLHS.VALUE to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yylhs.value = yystack_[yylen - 1].value;
    else
      yylhs.value = yystack_[0].value;

    // Compute the default @$.
    {
      slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
      YYLLOC_DEFAULT (yylhs.location, slice, yylen);
    }

    // Perform the reduction.
    YY_REDUCE_PRINT (yyn);
    try
      {
        switch (yyn)
          {
  case 4:
/* Line 817 of lalr1.cc  */
#line 192 "../../src-common/cfdg.ypp"
    {
            if ((yystack_[0].value.component)) {
                driver.push_rep((yystack_[0].value.component), true);
            }
        }
/* Line 817 of lalr1.cc  */
#line 1052 "cfdg.tab.cpp"
    break;

  case 6:
/* Line 817 of lalr1.cc  */
#line 201 "../../src-common/cfdg.ypp"
    {
            if ((yystack_[0].value.component)) {
                driver.push_rep((yystack_[0].value.component), true);
            }
        }
/* Line 817 of lalr1.cc  */
#line 1064 "cfdg.tab.cpp"
    break;

  case 9:
/* Line 817 of lalr1.cc  */
#line 211 "../../src-common/cfdg.ypp"
    { (yylhs.value.component) = 0; }
/* Line 817 of lalr1.cc  */
#line 1072 "cfdg.tab.cpp"
    break;

  case 10:
/* Line 817 of lalr1.cc  */
#line 212 "../../src-common/cfdg.ypp"
    { (yylhs.value.component) = 0; }
/* Line 817 of lalr1.cc  */
#line 1080 "cfdg.tab.cpp"
    break;

  case 13:
/* Line 817 of lalr1.cc  */
#line 215 "../../src-common/cfdg.ypp"
    { (yylhs.value.component) = (yystack_[0].value.shapeObj); }
/* Line 817 of lalr1.cc  */
#line 1088 "cfdg.tab.cpp"
    break;

  case 15:
/* Line 817 of lalr1.cc  */
#line 217 "../../src-common/cfdg.ypp"
    { (yylhs.value.component) = 0; }
/* Line 817 of lalr1.cc  */
#line 1096 "cfdg.tab.cpp"
    break;

  case 16:
/* Line 817 of lalr1.cc  */
#line 218 "../../src-common/cfdg.ypp"
    {
            error(yystack_[0].location, "Illegal mixture of old and new elements");
            (yylhs.value.component) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 1107 "cfdg.tab.cpp"
    break;

  case 19:
/* Line 817 of lalr1.cc  */
#line 227 "../../src-common/cfdg.ypp"
    { (yylhs.value.component) = 0; }
/* Line 817 of lalr1.cc  */
#line 1115 "cfdg.tab.cpp"
    break;

  case 20:
/* Line 817 of lalr1.cc  */
#line 228 "../../src-common/cfdg.ypp"
    { (yylhs.value.component) = 0; }
/* Line 817 of lalr1.cc  */
#line 1123 "cfdg.tab.cpp"
    break;

  case 25:
/* Line 817 of lalr1.cc  */
#line 233 "../../src-common/cfdg.ypp"
    {
            if (driver.lexer->maybeVersion == token::CFDG2) {
                error(yystack_[0].location, "Illegal mixture of old and new elements");
            } else {
                driver.lexer->maybeVersion = token::CFDG3;
            }
            (yylhs.value.component) = 0;
            YYABORT;
        }
/* Line 817 of lalr1.cc  */
#line 1139 "cfdg.tab.cpp"
    break;

  case 26:
/* Line 817 of lalr1.cc  */
#line 245 "../../src-common/cfdg.ypp"
    { delete (yystack_[1].value.string); }
/* Line 817 of lalr1.cc  */
#line 1147 "cfdg.tab.cpp"
    break;

  case 27:
/* Line 817 of lalr1.cc  */
#line 246 "../../src-common/cfdg.ypp"
    {}
/* Line 817 of lalr1.cc  */
#line 1155 "cfdg.tab.cpp"
    break;

  case 28:
/* Line 817 of lalr1.cc  */
#line 247 "../../src-common/cfdg.ypp"
    {}
/* Line 817 of lalr1.cc  */
#line 1163 "cfdg.tab.cpp"
    break;

  case 29:
/* Line 817 of lalr1.cc  */
#line 248 "../../src-common/cfdg.ypp"
    { delete (yystack_[1].value.string); }
/* Line 817 of lalr1.cc  */
#line 1171 "cfdg.tab.cpp"
    break;

  case 30:
/* Line 817 of lalr1.cc  */
#line 249 "../../src-common/cfdg.ypp"
    { delete (yystack_[2].value.string); delete (yystack_[1].value.string); }
/* Line 817 of lalr1.cc  */
#line 1179 "cfdg.tab.cpp"
    break;

  case 33:
/* Line 817 of lalr1.cc  */
#line 252 "../../src-common/cfdg.ypp"
    { delete (yystack_[1].value.string); }
/* Line 817 of lalr1.cc  */
#line 1187 "cfdg.tab.cpp"
    break;

  case 34:
/* Line 817 of lalr1.cc  */
#line 253 "../../src-common/cfdg.ypp"
    { delete (yystack_[1].value.string); }
/* Line 817 of lalr1.cc  */
#line 1195 "cfdg.tab.cpp"
    break;

  case 35:
/* Line 817 of lalr1.cc  */
#line 254 "../../src-common/cfdg.ypp"
    { delete (yystack_[1].value.string); }
/* Line 817 of lalr1.cc  */
#line 1203 "cfdg.tab.cpp"
    break;

  case 36:
/* Line 817 of lalr1.cc  */
#line 255 "../../src-common/cfdg.ypp"
    { delete (yystack_[1].value.string); }
/* Line 817 of lalr1.cc  */
#line 1211 "cfdg.tab.cpp"
    break;

  case 37:
/* Line 817 of lalr1.cc  */
#line 259 "../../src-common/cfdg.ypp"
    { delete (yystack_[0].value.mod); }
/* Line 817 of lalr1.cc  */
#line 1219 "cfdg.tab.cpp"
    break;

  case 38:
/* Line 817 of lalr1.cc  */
#line 260 "../../src-common/cfdg.ypp"
    { delete (yystack_[0].value.mod); }
/* Line 817 of lalr1.cc  */
#line 1227 "cfdg.tab.cpp"
    break;

  case 39:
/* Line 817 of lalr1.cc  */
#line 261 "../../src-common/cfdg.ypp"
    { delete (yystack_[0].value.mod); }
/* Line 817 of lalr1.cc  */
#line 1235 "cfdg.tab.cpp"
    break;

  case 40:
/* Line 817 of lalr1.cc  */
#line 262 "../../src-common/cfdg.ypp"
    { delete (yystack_[0].value.string); }
/* Line 817 of lalr1.cc  */
#line 1243 "cfdg.tab.cpp"
    break;

  case 41:
/* Line 817 of lalr1.cc  */
#line 263 "../../src-common/cfdg.ypp"
    { delete (yystack_[0].value.ruleObj); }
/* Line 817 of lalr1.cc  */
#line 1251 "cfdg.tab.cpp"
    break;

  case 42:
/* Line 817 of lalr1.cc  */
#line 267 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yystack_[0].value.string));
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(NULL);
            driver.IncludeFile(*file);
        }
/* Line 817 of lalr1.cc  */
#line 1264 "cfdg.tab.cpp"
    break;

  case 43:
/* Line 817 of lalr1.cc  */
#line 276 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yystack_[0].value.string));
            str_ptr nm((yystack_[1].value.string));
            driver.SetShape(NULL);
            driver.IncludeFile(*file);
            if (nm.get())
                driver.PushNameSpace(nm, yystack_[1].location);
        }
/* Line 817 of lalr1.cc  */
#line 1279 "cfdg.tab.cpp"
    break;

  case 44:
/* Line 817 of lalr1.cc  */
#line 287 "../../src-common/cfdg.ypp"
    {
            if (driver.EndInclude())
                YYACCEPT;
        }
/* Line 817 of lalr1.cc  */
#line 1290 "cfdg.tab.cpp"
    break;

  case 47:
/* Line 817 of lalr1.cc  */
#line 297 "../../src-common/cfdg.ypp"
    { (yylhs.value.string) = (yystack_[0].value.string); }
/* Line 817 of lalr1.cc  */
#line 1298 "cfdg.tab.cpp"
    break;

  case 48:
/* Line 817 of lalr1.cc  */
#line 298 "../../src-common/cfdg.ypp"
    { (yylhs.value.string) = NULL; }
/* Line 817 of lalr1.cc  */
#line 1306 "cfdg.tab.cpp"
    break;

  case 49:
/* Line 817 of lalr1.cc  */
#line 302 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yystack_[2].value.string));
            exp_ptr p((yystack_[1].value.expression));
            mod_ptr mod((yystack_[0].value.mod));
            driver.SetShape(NULL);
            if (driver.mCompilePhase == 2) {
                ruleSpec_ptr r(driver.MakeRuleSpec(*name, p, yystack_[2].location));
                rep_ptr start(new ASTreplacement(*r, *name, mod, yylhs.location));
                driver.Initialize(start);
            }
            (yylhs.value.component) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 1325 "cfdg.tab.cpp"
    break;

  case 50:
/* Line 817 of lalr1.cc  */
#line 315 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yystack_[1].value.string));
            mod_ptr mod((yystack_[0].value.mod));
            driver.SetShape(NULL);
            if (driver.mCompilePhase == 2) {
                ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), yystack_[1].location));
                rep_ptr start(new ASTreplacement(*r, *name, mod, yylhs.location));
                driver.Initialize(start);
            }
            (yylhs.value.component) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 1343 "cfdg.tab.cpp"
    break;

  case 51:
/* Line 817 of lalr1.cc  */
#line 327 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yystack_[1].value.string));
            exp_ptr p((yystack_[0].value.expression));
            driver.SetShape(NULL);
            if (driver.mCompilePhase == 2) {
                ruleSpec_ptr r(driver.MakeRuleSpec(*name, p, yystack_[1].location));
                rep_ptr start(new ASTreplacement(*r, *name, mod_ptr(), yylhs.location));
                driver.Initialize(start);
            }
            (yylhs.value.component) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 1361 "cfdg.tab.cpp"
    break;

  case 52:
/* Line 817 of lalr1.cc  */
#line 341 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yystack_[0].value.string));
            driver.SetShape(NULL);
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), yystack_[0].location));
            rep_ptr start(new ASTreplacement(*r, *name, mod_ptr(), yylhs.location));
            driver.Initialize(start);
            (yylhs.value.component) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 1376 "cfdg.tab.cpp"
    break;

  case 53:
/* Line 817 of lalr1.cc  */
#line 352 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yystack_[0].value.mod));
            static const std::string backVar("CF::Background");
            driver.lexer->maybeVersion = token::CFDG2;
            driver.NextParameter(backVar, mod, yystack_[1].location, yystack_[0].location);
            (yylhs.value.component) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 1390 "cfdg.tab.cpp"
    break;

  case 54:
/* Line 817 of lalr1.cc  */
#line 362 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yystack_[0].value.mod));
            static const std::string tileVar("CF::Tile");
            driver.lexer->maybeVersion = token::CFDG2;
            driver.NextParameter(tileVar, mod, yystack_[1].location, yystack_[0].location);
            (yylhs.value.component) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 1404 "cfdg.tab.cpp"
    break;

  case 55:
/* Line 817 of lalr1.cc  */
#line 372 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yystack_[0].value.mod));
            driver.lexer->maybeVersion = token::CFDG2;
            if ((yystack_[1].value.modToken) != ASTmodTerm::size && (yystack_[1].value.modToken) != ASTmodTerm::time) {
                error(yystack_[1].location, "Syntax error");
            } else {
                static const std::string sizeVar("CF::Size");
                static const std::string timeVar("CF::Time");
                driver.NextParameter((yystack_[1].value.modToken) == ASTmodTerm::size ? sizeVar : timeVar, mod, yystack_[1].location, yystack_[0].location);
            }
            (yylhs.value.component) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 1423 "cfdg.tab.cpp"
    break;

  case 56:
/* Line 817 of lalr1.cc  */
#line 387 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yystack_[1].value.string));
            exp_ptr exp((yystack_[0].value.expression));
            if (var.get())
                driver.NextParameter(*var, exp, yystack_[1].location, yystack_[0].location);
        }
/* Line 817 of lalr1.cc  */
#line 1436 "cfdg.tab.cpp"
    break;

  case 57:
/* Line 817 of lalr1.cc  */
#line 396 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("shape");
            driver.push_paramDecls(*(yystack_[2].value.string), yylhs.location, numtype);
            (yylhs.value.string) = (yystack_[2].value.string);
        }
/* Line 817 of lalr1.cc  */
#line 1448 "cfdg.tab.cpp"
    break;

  case 58:
/* Line 817 of lalr1.cc  */
#line 402 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("number");
            driver.push_paramDecls(*(yystack_[2].value.string), yylhs.location, numtype);
            (yylhs.value.string) = (yystack_[2].value.string);
        }
/* Line 817 of lalr1.cc  */
#line 1460 "cfdg.tab.cpp"
    break;

  case 59:
/* Line 817 of lalr1.cc  */
#line 408 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yystack_[3].value.string));
            driver.push_paramDecls(*(yystack_[2].value.string), yylhs.location, *type);
            (yylhs.value.string) = (yystack_[2].value.string);
        }
/* Line 817 of lalr1.cc  */
#line 1472 "cfdg.tab.cpp"
    break;

  case 60:
/* Line 817 of lalr1.cc  */
#line 414 "../../src-common/cfdg.ypp"
    {
            (yylhs.value.string) = (yystack_[1].value.string);
        }
/* Line 817 of lalr1.cc  */
#line 1482 "cfdg.tab.cpp"
    break;

  case 61:
/* Line 817 of lalr1.cc  */
#line 418 "../../src-common/cfdg.ypp"
    {
            error(yystack_[2].location, "Reserved keyword: adjustment");
            (yylhs.value.string) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 1493 "cfdg.tab.cpp"
    break;

  case 62:
/* Line 817 of lalr1.cc  */
#line 423 "../../src-common/cfdg.ypp"
    {
            error(yystack_[2].location, "Reserved keyword: adjustment");
            (yylhs.value.string) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 1504 "cfdg.tab.cpp"
    break;

  case 63:
/* Line 817 of lalr1.cc  */
#line 428 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yystack_[3].value.string));
            error(yystack_[2].location, "Reserved keyword: adjustment");
            (yylhs.value.string) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 1516 "cfdg.tab.cpp"
    break;

  case 64:
/* Line 817 of lalr1.cc  */
#line 434 "../../src-common/cfdg.ypp"
    {
            error(yystack_[1].location, "Reserved keyword: adjustment");
            (yylhs.value.string) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 1527 "cfdg.tab.cpp"
    break;

  case 65:
/* Line 817 of lalr1.cc  */
#line 441 "../../src-common/cfdg.ypp"
    {
            (yylhs.value.string) = (yystack_[1].value.string);
        }
/* Line 817 of lalr1.cc  */
#line 1537 "cfdg.tab.cpp"
    break;

  case 66:
/* Line 817 of lalr1.cc  */
#line 444 "../../src-common/cfdg.ypp"
    {
            error(yystack_[1].location, "Reserved keyword: adjustment");
            (yylhs.value.string) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 1548 "cfdg.tab.cpp"
    break;

  case 67:
/* Line 817 of lalr1.cc  */
#line 451 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yystack_[1].value.string));
            exp_ptr exp((yystack_[0].value.expression));
            if (var.get() && driver.mCompilePhase == 2)
                driver.NextParameter(*var, exp, yystack_[1].location, yystack_[0].location);
        }
/* Line 817 of lalr1.cc  */
#line 1561 "cfdg.tab.cpp"
    break;

  case 68:
/* Line 817 of lalr1.cc  */
#line 460 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yystack_[1].value.string));
            bool hasParams = !driver.mParamDecls.mParameters.empty();
            exp_ptr dummy(hasParams ? new ASTexpression(yystack_[1].location) : NULL);
            ASTruleSpecifier r(driver.StringToShape(*name, yystack_[1].location, false), *name, dummy,
                               yylhs.location, &(driver.mParamDecls.mParameters),
                               &(driver.mParamDecls.mParameters));
            ASTshape* s = new ASTshape(r, false, yystack_[2].location + yystack_[1].location);
            s->mRules.mParameters.swap(driver.mParamDecls.mParameters);
            driver.SetShape(s);
            s->mShapeSpec.typeSignature = hasParams ? &(s->mRules.mParameters) : NULL;
            (yylhs.value.shapeObj) = s;
        }
/* Line 817 of lalr1.cc  */
#line 1581 "cfdg.tab.cpp"
    break;

  case 69:
/* Line 817 of lalr1.cc  */
#line 476 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yystack_[1].value.shapeObj), true);
            if (driver.mCompilePhase == 2) {
                driver.mInPathContainer = false;
                rule_ptr rule(new ASTrule(-1, yystack_[1].location));
                driver.AddRule(rule.get());
                driver.push_repContainer(rule->mRuleBody);
                (yylhs.value.ruleObj) = rule.release();
            } else {
                (yylhs.value.ruleObj) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 1600 "cfdg.tab.cpp"
    break;

  case 70:
/* Line 817 of lalr1.cc  */
#line 490 "../../src-common/cfdg.ypp"
    {
            (yylhs.value.component) = (yystack_[2].value.ruleObj);
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer((yystack_[2].value.ruleObj));
            driver.mInPathContainer = false;
        }
/* Line 817 of lalr1.cc  */
#line 1613 "cfdg.tab.cpp"
    break;

  case 71:
/* Line 817 of lalr1.cc  */
#line 499 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yystack_[0].value.string));
            driver.SetShape(NULL);
            rule_ptr rule(new ASTrule(driver.StringToShape(*name, yystack_[0].location, false), yylhs.location));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yylhs.value.ruleObj) = rule.release();
        }
/* Line 817 of lalr1.cc  */
#line 1628 "cfdg.tab.cpp"
    break;

  case 72:
/* Line 817 of lalr1.cc  */
#line 508 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yystack_[1].value.string));
            str_ptr weight((yystack_[0].value.string));
            driver.SetShape(NULL);
            rule_ptr rule(new ASTrule(driver.StringToShape(*name, yystack_[1].location, false), 
                                      CFatof(weight->c_str()), 
                                      weight->find_first_of('%')  != std::string::npos,
                                      yylhs.location));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yylhs.value.ruleObj) = rule.release();
        }
/* Line 817 of lalr1.cc  */
#line 1647 "cfdg.tab.cpp"
    break;

  case 73:
/* Line 817 of lalr1.cc  */
#line 523 "../../src-common/cfdg.ypp"
    {
            driver.lexer->maybeVersion = token::CFDG2;
            (yylhs.value.component) = (yystack_[3].value.ruleObj);
            driver.pop_repContainer((yystack_[3].value.ruleObj));
        }
/* Line 817 of lalr1.cc  */
#line 1659 "cfdg.tab.cpp"
    break;

  case 74:
/* Line 817 of lalr1.cc  */
#line 531 "../../src-common/cfdg.ypp"
    {
            driver.mInPathContainer = false;
            if (driver.mCompilePhase == 2) {
                rule_ptr rule(new ASTrule(-1, yystack_[0].location));
                driver.AddRule(rule.get());
                driver.push_repContainer(rule->mRuleBody);
                (yylhs.value.ruleObj) = rule.release();
            } else {
                (yylhs.value.ruleObj) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 1677 "cfdg.tab.cpp"
    break;

  case 75:
/* Line 817 of lalr1.cc  */
#line 543 "../../src-common/cfdg.ypp"
    {
            driver.mInPathContainer = false;
            str_ptr weight((yystack_[0].value.string));
            if (driver.mCompilePhase == 2) {
                rule_ptr rule(new ASTrule(-1, CFatof(weight->c_str()), 
                                          weight->find_first_of('%')  != std::string::npos,
                                          yylhs.location));
                driver.AddRule(rule.get());
                driver.push_repContainer(rule->mRuleBody);
                (yylhs.value.ruleObj) = rule.release();
            } else {
                (yylhs.value.ruleObj) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 1698 "cfdg.tab.cpp"
    break;

  case 76:
/* Line 817 of lalr1.cc  */
#line 560 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yystack_[1].value.string));
            bool hasParams = !driver.mParamDecls.mParameters.empty();
            exp_ptr dummy(hasParams ? new ASTexpression(yystack_[1].location) : NULL);
            ASTruleSpecifier r(driver.StringToShape(*name, yystack_[1].location, false), *name, dummy,
                               yylhs.location, &(driver.mParamDecls.mParameters),
                               &(driver.mParamDecls.mParameters));
            ASTshape* s = new ASTshape(r, false, yystack_[2].location + yystack_[1].location);
            s->mRules.mParameters.swap(driver.mParamDecls.mParameters);
            driver.SetShape(s, true);
            s->mShapeSpec.typeSignature = hasParams ? &(s->mRules.mParameters) : NULL;
            driver.mInPathContainer = true;
            if (driver.mCompilePhase == 2) {
                rule_ptr newPath(new ASTrule(-1, yylhs.location));
                newPath->isPath = true;
                driver.AddRule(newPath.get());
                driver.push_repContainer(newPath->mRuleBody);
                (yylhs.value.ruleObj) = newPath.release();
            } else {
                (yylhs.value.ruleObj) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 1727 "cfdg.tab.cpp"
    break;

  case 77:
/* Line 817 of lalr1.cc  */
#line 585 "../../src-common/cfdg.ypp"
    {
            (yylhs.value.component) = (yystack_[3].value.ruleObj);
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer((yystack_[3].value.ruleObj));
            driver.mInPathContainer = false;
        }
/* Line 817 of lalr1.cc  */
#line 1740 "cfdg.tab.cpp"
    break;

  case 78:
/* Line 817 of lalr1.cc  */
#line 594 "../../src-common/cfdg.ypp"
    {
            (yylhs.value.component) = (yystack_[3].value.ruleObj);
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer((yystack_[3].value.ruleObj));
            driver.mInPathContainer = false;
            driver.SetShape(NULL);
        }
/* Line 817 of lalr1.cc  */
#line 1754 "cfdg.tab.cpp"
    break;

  case 79:
/* Line 817 of lalr1.cc  */
#line 604 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yystack_[0].value.string));
            driver.SetShape(NULL);
            rule_ptr newPath(new ASTrule(driver.StringToShape(*(yystack_[0].value.string), yystack_[0].location, false), yylhs.location));
            newPath->isPath = true;
            driver.AddRule(newPath.get());
            driver.push_repContainer(newPath->mRuleBody);
            driver.mInPathContainer = true;
            (yylhs.value.ruleObj) = newPath.release();
        }
/* Line 817 of lalr1.cc  */
#line 1771 "cfdg.tab.cpp"
    break;

  case 80:
/* Line 817 of lalr1.cc  */
#line 617 "../../src-common/cfdg.ypp"
    {
            (yylhs.value.component) = (yystack_[3].value.ruleObj);
            driver.pop_repContainer((yystack_[3].value.ruleObj));
        }
/* Line 817 of lalr1.cc  */
#line 1782 "cfdg.tab.cpp"
    break;

  case 81:
/* Line 817 of lalr1.cc  */
#line 624 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yystack_[1].value.string));
            str_ptr var((yystack_[0].value.string));
            driver.NextParameterDecl(*type, *var, yystack_[1].location, yystack_[0].location);
        }
/* Line 817 of lalr1.cc  */
#line 1794 "cfdg.tab.cpp"
    break;

  case 82:
/* Line 817 of lalr1.cc  */
#line 630 "../../src-common/cfdg.ypp"
    {
            static std::string shapeStr("shape");
            str_ptr var((yystack_[0].value.string));
            driver.NextParameterDecl(shapeStr, *var, yystack_[1].location, yystack_[0].location);
        }
/* Line 817 of lalr1.cc  */
#line 1806 "cfdg.tab.cpp"
    break;

  case 83:
/* Line 817 of lalr1.cc  */
#line 636 "../../src-common/cfdg.ypp"
    {
            delete (yystack_[1].value.string);
            error(yystack_[0].location, "Reserved keyword: adjustment");
        }
/* Line 817 of lalr1.cc  */
#line 1817 "cfdg.tab.cpp"
    break;

  case 84:
/* Line 817 of lalr1.cc  */
#line 641 "../../src-common/cfdg.ypp"
    {
            error(yystack_[0].location, "Reserved keyword: adjustment");
        }
/* Line 817 of lalr1.cc  */
#line 1827 "cfdg.tab.cpp"
    break;

  case 85:
/* Line 817 of lalr1.cc  */
#line 645 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("number");
            str_ptr var((yystack_[0].value.string));
            driver.NextParameterDecl(numtype, *var, yystack_[0].location, yystack_[0].location);
        }
/* Line 817 of lalr1.cc  */
#line 1839 "cfdg.tab.cpp"
    break;

  case 86:
/* Line 817 of lalr1.cc  */
#line 651 "../../src-common/cfdg.ypp"
    {
            error(yystack_[0].location, "Reserved keyword: adjustment");
        }
/* Line 817 of lalr1.cc  */
#line 1849 "cfdg.tab.cpp"
    break;

  case 93:
/* Line 817 of lalr1.cc  */
#line 672 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = (yystack_[1].value.expression);}
/* Line 817 of lalr1.cc  */
#line 1857 "cfdg.tab.cpp"
    break;

  case 94:
/* Line 817 of lalr1.cc  */
#line 673 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASTexpression(yylhs.location); }
/* Line 817 of lalr1.cc  */
#line 1865 "cfdg.tab.cpp"
    break;

  case 95:
/* Line 817 of lalr1.cc  */
#line 674 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = 0; }
/* Line 817 of lalr1.cc  */
#line 1873 "cfdg.tab.cpp"
    break;

  case 96:
/* Line 817 of lalr1.cc  */
#line 675 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = 0; }
/* Line 817 of lalr1.cc  */
#line 1881 "cfdg.tab.cpp"
    break;

  case 97:
/* Line 817 of lalr1.cc  */
#line 679 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 1)
                assert ((yystack_[0].value.component) == 0);
            driver.push_rep((yystack_[0].value.component));
        }
/* Line 817 of lalr1.cc  */
#line 1893 "cfdg.tab.cpp"
    break;

  case 99:
/* Line 817 of lalr1.cc  */
#line 688 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yystack_[0].value.component));
        }
/* Line 817 of lalr1.cc  */
#line 1903 "cfdg.tab.cpp"
    break;

  case 101:
/* Line 817 of lalr1.cc  */
#line 695 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yystack_[3].value.string));
            mod_ptr mod((yystack_[1].value.mod));
            driver.lexer->maybeVersion = token::CFDG2;
            (yylhs.value.component) = new ASTpathOp(*pop, mod, yylhs.location);
        }
/* Line 817 of lalr1.cc  */
#line 1916 "cfdg.tab.cpp"
    break;

  case 102:
/* Line 817 of lalr1.cc  */
#line 702 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yystack_[1].value.string));
            mod_ptr mod((yystack_[0].value.mod));
            driver.lexer->maybeVersion = token::CFDG2;
            rep_ptr item(new ASTpathCommand(*cmd, mod, yylhs.location));
            (yylhs.value.component) = item.release();
        }
/* Line 817 of lalr1.cc  */
#line 1930 "cfdg.tab.cpp"
    break;

  case 103:
/* Line 817 of lalr1.cc  */
#line 712 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yystack_[3].value.string));
            exp_ptr mod((yystack_[1].value.expression));
            if (driver.mCompilePhase == 2)
                (yylhs.value.component) = new ASTpathOp(*pop, mod, yylhs.location);
            else
                (yylhs.value.component) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 1945 "cfdg.tab.cpp"
    break;

  case 104:
/* Line 817 of lalr1.cc  */
#line 721 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yystack_[2].value.string));
            exp_ptr mod;
            if (driver.mCompilePhase == 2)
                (yylhs.value.component) = new ASTpathOp(*pop, mod, yylhs.location);
            else
                (yylhs.value.component) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 1960 "cfdg.tab.cpp"
    break;

  case 105:
/* Line 817 of lalr1.cc  */
#line 730 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yystack_[2].value.string));
            exp_ptr p((yystack_[1].value.expression));
            mod_ptr mod((yystack_[0].value.mod));
            if (driver.mCompilePhase == 2) {
                rep_ptr item = driver.MakeElement(*cmd, mod, p, yylhs.location, false);
                (yylhs.value.component) = item.release();
            } else {
                (yylhs.value.component) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 1978 "cfdg.tab.cpp"
    break;

  case 106:
/* Line 817 of lalr1.cc  */
#line 742 "../../src-common/cfdg.ypp"
    { 
            exp_ptr args((yystack_[2].value.expression));
            mod_ptr mod((yystack_[0].value.mod));
            if (driver.mCompilePhase == 2) {
                str_ptr func(new std::string("if"));
                args.reset(driver.MakeFunction(func, args, yystack_[4].location, yystack_[2].location, false));
                static const std::string ifstr("if");
                rep_ptr item = driver.MakeElement(ifstr, mod, args, yylhs.location, false);
                (yylhs.value.component) = item.release();
            } else {
                (yylhs.value.component) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 1998 "cfdg.tab.cpp"
    break;

  case 107:
/* Line 817 of lalr1.cc  */
#line 756 "../../src-common/cfdg.ypp"
    {
            std::auto_ptr<ASTrepContainer> vars((yystack_[2].value.bodyObj));
            exp_ptr exp((yystack_[1].value.expression));
            mod_ptr mod((yystack_[0].value.mod));
            exp.reset(driver.MakeLet(yystack_[2].location, exp));     // must do unconditionally
            if (driver.mCompilePhase == 2) {
                static const std::string letstr("let");
                rep_ptr item = driver.MakeElement(letstr, mod, exp, yylhs.location, false);
                (yylhs.value.component) = item.release();
            } else {
                (yylhs.value.component) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 2018 "cfdg.tab.cpp"
    break;

  case 108:
/* Line 817 of lalr1.cc  */
#line 770 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yystack_[2].value.string));
            exp_ptr p((yystack_[1].value.expression));
            mod_ptr mod((yystack_[0].value.mod));
            if (driver.mCompilePhase == 2) {
                rep_ptr item = driver.MakeElement(*cmd, mod, p, yylhs.location, true);
                (yylhs.value.component) = item.release();
            } else {
                (yylhs.value.component) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 2036 "cfdg.tab.cpp"
    break;

  case 109:
/* Line 817 of lalr1.cc  */
#line 784 "../../src-common/cfdg.ypp"
    { }
/* Line 817 of lalr1.cc  */
#line 2044 "cfdg.tab.cpp"
    break;

  case 110:
/* Line 817 of lalr1.cc  */
#line 786 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 1)
                assert((yystack_[0].value.component) == 0);
            driver.push_rep((yystack_[0].value.component));
        }
/* Line 817 of lalr1.cc  */
#line 2056 "cfdg.tab.cpp"
    break;

  case 111:
/* Line 817 of lalr1.cc  */
#line 794 "../../src-common/cfdg.ypp"
    { }
/* Line 817 of lalr1.cc  */
#line 2064 "cfdg.tab.cpp"
    break;

  case 112:
/* Line 817 of lalr1.cc  */
#line 796 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yystack_[0].value.component));
        }
/* Line 817 of lalr1.cc  */
#line 2074 "cfdg.tab.cpp"
    break;

  case 113:
/* Line 817 of lalr1.cc  */
#line 802 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer(driver.switchStack.top());
        }
/* Line 817 of lalr1.cc  */
#line 2085 "cfdg.tab.cpp"
    break;

  case 116:
/* Line 817 of lalr1.cc  */
#line 814 "../../src-common/cfdg.ypp"
    { 
            (yylhs.value.component) = (yystack_[0].value.component); 
        }
/* Line 817 of lalr1.cc  */
#line 2095 "cfdg.tab.cpp"
    break;

  case 117:
/* Line 817 of lalr1.cc  */
#line 818 "../../src-common/cfdg.ypp"
    { 
            (yylhs.value.component) = 0; 
        }
/* Line 817 of lalr1.cc  */
#line 2105 "cfdg.tab.cpp"
    break;

  case 118:
/* Line 817 of lalr1.cc  */
#line 822 "../../src-common/cfdg.ypp"
    { 
            (yylhs.value.component) = (yystack_[0].value.loopObj); 
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yystack_[0].value.loopObj));
                if ((yystack_[0].value.loopObj)->mRepType == 0) {
                    delete (yystack_[0].value.loopObj);
                    (yylhs.value.component) = 0;
                }
            }
        }
/* Line 817 of lalr1.cc  */
#line 2122 "cfdg.tab.cpp"
    break;

  case 119:
/* Line 817 of lalr1.cc  */
#line 833 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yystack_[1].value.loopObj));
                driver.push_repContainer((yystack_[1].value.loopObj)->mFinallyBody);
            }
        }
/* Line 817 of lalr1.cc  */
#line 2135 "cfdg.tab.cpp"
    break;

  case 120:
/* Line 817 of lalr1.cc  */
#line 838 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yystack_[3].value.loopObj));
                (yylhs.value.component) = (yystack_[3].value.loopObj);
                if ((yystack_[3].value.loopObj)->mRepType == 0) {
                    delete (yystack_[3].value.loopObj);
                    (yylhs.value.component) = 0;
                }
            } else {
                (yylhs.value.component) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 2154 "cfdg.tab.cpp"
    break;

  case 121:
/* Line 817 of lalr1.cc  */
#line 851 "../../src-common/cfdg.ypp"
    {
            (yylhs.value.component) = (yystack_[1].value.ifObj);
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yystack_[1].value.ifObj));
                if ((yystack_[1].value.ifObj)->mRepType == 0) {
                    delete (yystack_[1].value.ifObj);
                    (yylhs.value.component) = 0;
                }
            }
        }
/* Line 817 of lalr1.cc  */
#line 2171 "cfdg.tab.cpp"
    break;

  case 122:
/* Line 817 of lalr1.cc  */
#line 862 "../../src-common/cfdg.ypp"
    {
            (yylhs.value.component) = (yystack_[1].value.ifObj);
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yystack_[1].value.ifObj));
                if ((yystack_[1].value.ifObj)->mRepType == 0) {
                    delete (yystack_[1].value.ifObj);
                    (yylhs.value.component) = 0;
                }
            }
        }
/* Line 817 of lalr1.cc  */
#line 2188 "cfdg.tab.cpp"
    break;

  case 123:
/* Line 817 of lalr1.cc  */
#line 873 "../../src-common/cfdg.ypp"
    {
            (yylhs.value.component) = (yystack_[1].value.component);
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yystack_[1].value.component));
                if ((yystack_[1].value.component)->mRepType == 0) {
                    delete (yystack_[1].value.component);
                    (yylhs.value.component) = 0;
                }
            }
        }
/* Line 817 of lalr1.cc  */
#line 2205 "cfdg.tab.cpp"
    break;

  case 124:
/* Line 817 of lalr1.cc  */
#line 885 "../../src-common/cfdg.ypp"
    {
            (yylhs.value.component) = (yystack_[3].value.switchObj);
            if (driver.mCompilePhase == 2) {
                (yystack_[3].value.switchObj)->unify();
                driver.switchStack.pop();
            }
        }
/* Line 817 of lalr1.cc  */
#line 2219 "cfdg.tab.cpp"
    break;

  case 125:
/* Line 817 of lalr1.cc  */
#line 893 "../../src-common/cfdg.ypp"
    {
            error(yystack_[0].location, "Illegal mixture of old and new elements");
            (yylhs.value.component) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 2230 "cfdg.tab.cpp"
    break;

  case 126:
/* Line 817 of lalr1.cc  */
#line 900 "../../src-common/cfdg.ypp"
    { delete (yystack_[1].value.string); }
/* Line 817 of lalr1.cc  */
#line 2238 "cfdg.tab.cpp"
    break;

  case 127:
/* Line 817 of lalr1.cc  */
#line 901 "../../src-common/cfdg.ypp"
    { delete (yystack_[1].value.string); }
/* Line 817 of lalr1.cc  */
#line 2246 "cfdg.tab.cpp"
    break;

  case 128:
/* Line 817 of lalr1.cc  */
#line 902 "../../src-common/cfdg.ypp"
    { delete (yystack_[1].value.string); }
/* Line 817 of lalr1.cc  */
#line 2254 "cfdg.tab.cpp"
    break;

  case 129:
/* Line 817 of lalr1.cc  */
#line 906 "../../src-common/cfdg.ypp"
    { (yylhs.value.component) = (yystack_[0].value.component); }
/* Line 817 of lalr1.cc  */
#line 2262 "cfdg.tab.cpp"
    break;

  case 130:
/* Line 817 of lalr1.cc  */
#line 908 "../../src-common/cfdg.ypp"
    { 
            (yylhs.value.component) = (yystack_[1].value.loopObj);
            driver.pop_repContainer((yystack_[1].value.loopObj));
            if ((yystack_[1].value.loopObj)->mRepType == 0) {
                delete (yystack_[1].value.loopObj);
                (yylhs.value.component) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 2277 "cfdg.tab.cpp"
    break;

  case 131:
/* Line 817 of lalr1.cc  */
#line 916 "../../src-common/cfdg.ypp"
    {
            if (driver.lexer->maybeVersion == token::CFDG2) {
                error(yystack_[0].location, "Illegal mixture of old and new elements");
            } else {
                driver.lexer->maybeVersion = token::CFDG3;
            }
            (yylhs.value.component) = 0;
            YYABORT;
        }
/* Line 817 of lalr1.cc  */
#line 2293 "cfdg.tab.cpp"
    break;

  case 132:
/* Line 817 of lalr1.cc  */
#line 928 "../../src-common/cfdg.ypp"
    { delete (yystack_[1].value.string); }
/* Line 817 of lalr1.cc  */
#line 2301 "cfdg.tab.cpp"
    break;

  case 133:
/* Line 817 of lalr1.cc  */
#line 929 "../../src-common/cfdg.ypp"
    { delete (yystack_[1].value.string); }
/* Line 817 of lalr1.cc  */
#line 2309 "cfdg.tab.cpp"
    break;

  case 136:
/* Line 817 of lalr1.cc  */
#line 932 "../../src-common/cfdg.ypp"
    { delete (yystack_[1].value.string); }
/* Line 817 of lalr1.cc  */
#line 2317 "cfdg.tab.cpp"
    break;

  case 141:
/* Line 817 of lalr1.cc  */
#line 940 "../../src-common/cfdg.ypp"
    {
            // parse loop mod and loop body with loop index in scope
            mod_ptr loopmod((yystack_[1].value.mod));
            if (driver.mCompilePhase == 2)
                (yystack_[2].value.loopObj)->mChildChange.grab(loopmod.get());
            (yylhs.value.loopObj) = (yystack_[2].value.loopObj);
            // loopmod gets deleted
        }
/* Line 817 of lalr1.cc  */
#line 2332 "cfdg.tab.cpp"
    break;

  case 142:
/* Line 817 of lalr1.cc  */
#line 951 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yystack_[0].value.component));
        }
/* Line 817 of lalr1.cc  */
#line 2342 "cfdg.tab.cpp"
    break;

  case 144:
/* Line 817 of lalr1.cc  */
#line 958 "../../src-common/cfdg.ypp"
    { }
/* Line 817 of lalr1.cc  */
#line 2350 "cfdg.tab.cpp"
    break;

  case 145:
/* Line 817 of lalr1.cc  */
#line 960 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yystack_[0].value.component));
        }
/* Line 817 of lalr1.cc  */
#line 2360 "cfdg.tab.cpp"
    break;

  case 146:
/* Line 817 of lalr1.cc  */
#line 966 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yystack_[1].value.string));
            mod_ptr mod((yystack_[0].value.mod));
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), yystack_[1].location));
            (yylhs.value.component) = new ASTreplacement(*r, r->entropyVal, mod, yylhs.location);
        }
/* Line 817 of lalr1.cc  */
#line 2373 "cfdg.tab.cpp"
    break;

  case 147:
/* Line 817 of lalr1.cc  */
#line 975 "../../src-common/cfdg.ypp"
    { (yylhs.value.component) = (yystack_[0].value.component); }
/* Line 817 of lalr1.cc  */
#line 2381 "cfdg.tab.cpp"
    break;

  case 148:
/* Line 817 of lalr1.cc  */
#line 977 "../../src-common/cfdg.ypp"
    {
            (yylhs.value.component) = (yystack_[1].value.loopObj);
            driver.pop_repContainer((yystack_[1].value.loopObj));
            if ((yystack_[1].value.loopObj)->mRepType == 0) {
                delete (yystack_[1].value.loopObj);
                (yylhs.value.component) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 2396 "cfdg.tab.cpp"
    break;

  case 149:
/* Line 817 of lalr1.cc  */
#line 988 "../../src-common/cfdg.ypp"
    { ++driver.mLocalStackDepth; }
/* Line 817 of lalr1.cc  */
#line 2404 "cfdg.tab.cpp"
    break;

  case 150:
/* Line 817 of lalr1.cc  */
#line 988 "../../src-common/cfdg.ypp"
    {
            str_ptr cstr((yystack_[3].value.string));
            exp_ptr count(new ASTreal(*cstr, yystack_[3].location));
            mod_ptr mod((yystack_[0].value.mod));
            static const std::string dummyvar("~~inaccessiblevar~~");
            --driver.mLocalStackDepth;
            driver.lexer->maybeVersion = token::CFDG2;
            loop_ptr loop(new ASTloop(driver.StringToShape(dummyvar, yystack_[2].location, false), 
                                      dummyvar, yystack_[2].location, count, yylhs.location, mod));
            driver.push_repContainer(loop->mLoopBody);
            (yylhs.value.loopObj) = loop.release();
        }
/* Line 817 of lalr1.cc  */
#line 2423 "cfdg.tab.cpp"
    break;

  case 151:
/* Line 817 of lalr1.cc  */
#line 1003 "../../src-common/cfdg.ypp"
    {
            str_ptr var((yystack_[2].value.string));
            exp_ptr index((yystack_[0].value.expression));
            if (driver.mCompilePhase == 2) {
                int nameIndex = driver.StringToShape(*var, yystack_[2].location, false);
                loop_ptr loop(new ASTloop(nameIndex, *var, yystack_[2].location, index, yystack_[0].location, mod_ptr()));
                driver.push_repContainer(loop->mLoopBody);
                (yylhs.value.loopObj) = loop.release();
            } else {
                (yylhs.value.loopObj) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 2442 "cfdg.tab.cpp"
    break;

  case 152:
/* Line 817 of lalr1.cc  */
#line 1016 "../../src-common/cfdg.ypp"
    {
            exp_ptr index((yystack_[0].value.expression));
            if (driver.mCompilePhase == 2) {
                static const std::string dummyvar("~~inaccessiblevar~~");
                loop_ptr loop(new ASTloop(driver.StringToShape(dummyvar, yystack_[3].location, false), 
                                          dummyvar, yystack_[2].location, index, yystack_[0].location, mod_ptr()));
                driver.push_repContainer(loop->mLoopBody);
                (yylhs.value.loopObj) = loop.release();
            } else {
                (yylhs.value.loopObj) = 0;
            }
            error(yystack_[2].location, "Reserved keyword: adjustment");
        }
/* Line 817 of lalr1.cc  */
#line 2462 "cfdg.tab.cpp"
    break;

  case 153:
/* Line 817 of lalr1.cc  */
#line 1030 "../../src-common/cfdg.ypp"
    {
            exp_ptr count((yystack_[0].value.expression));
            if (driver.mCompilePhase == 2) {
                static const std::string dummyvar("~~inaccessiblevar~~");
                loop_ptr loop(new ASTloop(driver.StringToShape(dummyvar, yystack_[1].location, false), 
                                          dummyvar, yystack_[1].location, count, yystack_[0].location, mod_ptr()));
                driver.push_repContainer(loop->mLoopBody);
                (yylhs.value.loopObj) = loop.release();
            } else {
                (yylhs.value.loopObj) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 2481 "cfdg.tab.cpp"
    break;

  case 154:
/* Line 817 of lalr1.cc  */
#line 1045 "../../src-common/cfdg.ypp"
    {
            exp_ptr cond((yystack_[1].value.expression));
            if (driver.mCompilePhase == 2) {
                if_ptr ifHeader(new ASTif(cond, yystack_[1].location));
                driver.push_repContainer(ifHeader->mThenBody);
                (yylhs.value.ifObj) = ifHeader.release();
            } else {
                (yylhs.value.ifObj) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 2498 "cfdg.tab.cpp"
    break;

  case 155:
/* Line 817 of lalr1.cc  */
#line 1058 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yystack_[2].value.ifObj));
                driver.push_repContainer((yystack_[2].value.ifObj)->mElseBody);
            }
            (yylhs.value.ifObj) = (yystack_[2].value.ifObj);
        }
/* Line 817 of lalr1.cc  */
#line 2512 "cfdg.tab.cpp"
    break;

  case 156:
/* Line 817 of lalr1.cc  */
#line 1068 "../../src-common/cfdg.ypp"
    {
            exp_ptr mods((yystack_[0].value.expression));
            if ((yystack_[1].value.modToken) != ASTmodTerm::transform)
                error(yystack_[1].location, "Syntax error");
            if (driver.mCompilePhase == 2) {
                ASTtransform* trans = new ASTtransform(yylhs.location, mods);
                driver.push_repContainer(trans->mBody);
                (yylhs.value.component) = trans;
            } else {
                (yylhs.value.component) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 2531 "cfdg.tab.cpp"
    break;

  case 157:
/* Line 817 of lalr1.cc  */
#line 1080 "../../src-common/cfdg.ypp"
    {
            exp_ptr mods((yystack_[0].value.expression));
            if (!ASTparameter::Impure)
                error(yystack_[1].location, "shape cloning only permitted in impure mode");
            if (driver.mCompilePhase == 2) {
                ASTtransform* trans = new ASTtransform(yylhs.location, mods);
                trans->mClone = true;
                driver.push_repContainer(trans->mBody);
                (yylhs.value.component) = trans;
            } else {
                (yylhs.value.component) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 2551 "cfdg.tab.cpp"
    break;

  case 158:
/* Line 817 of lalr1.cc  */
#line 1096 "../../src-common/cfdg.ypp"
    {
            exp_ptr caseVal((yystack_[1].value.expression));
            if (driver.mCompilePhase == 2) {
                switch_ptr switchHeader(new ASTswitch(caseVal, yystack_[1].location));
                driver.switchStack.push(switchHeader.get());
                (yylhs.value.switchObj) = switchHeader.release();
            } else {
                (yylhs.value.switchObj) = 0;
            }
        }
/* Line 817 of lalr1.cc  */
#line 2568 "cfdg.tab.cpp"
    break;

  case 159:
/* Line 817 of lalr1.cc  */
#line 1109 "../../src-common/cfdg.ypp"
    {
            exp_ptr valExp((yystack_[1].value.expression));
            
            if (driver.mCompilePhase == 2) {
                double val = 0.0;
                try {
                    if (valExp->evaluate(&val, 1) != 1) {
                        driver.error(yystack_[1].location, "Case expression is not a single, numeric expression");
                    } else {
                        int intval = (int)floor(val);
                        ASTswitch::switchMap& caseMap = driver.switchStack.top()->mCaseStatements;
                        
                        if (caseMap.count(intval)) {
                            driver.error(yystack_[1].location, "Case value already in use");
                            driver.push_repContainer(*(caseMap[intval]));
                        } else {
                            ASTrepContainer* caseBody = new ASTrepContainer();
                            caseMap[intval] = caseBody;
                            driver.push_repContainer(*caseBody);
                        }
                    }
                }
                catch (DeferUntilRuntime) {
                    driver.error(yystack_[1].location, "Case expression is not constant");
                }
            }
            (yylhs.value.modToken) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 2603 "cfdg.tab.cpp"
    break;

  case 160:
/* Line 817 of lalr1.cc  */
#line 1138 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2) {
                if (!driver.switchStack.top()->mElseBody.mBody.empty()) {
                    driver.error(yylhs.location, "There can only be one 'else:' clause");
                } else {
                    driver.push_repContainer(driver.switchStack.top()->mElseBody);
                }
            }
            (yylhs.value.modToken) = 0;
        }
/* Line 817 of lalr1.cc  */
#line 2620 "cfdg.tab.cpp"
    break;

  case 161:
/* Line 817 of lalr1.cc  */
#line 1151 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yystack_[1].value.mod));
            (yylhs.value.mod) = driver.MakeModification(mod, yylhs.location, true);
        }
/* Line 817 of lalr1.cc  */
#line 2631 "cfdg.tab.cpp"
    break;

  case 162:
/* Line 817 of lalr1.cc  */
#line 1156 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yystack_[1].value.mod));
            (yylhs.value.mod) = driver.MakeModification(mod, yylhs.location, false);
        }
/* Line 817 of lalr1.cc  */
#line 2642 "cfdg.tab.cpp"
    break;

  case 163:
/* Line 817 of lalr1.cc  */
#line 1163 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yystack_[1].value.mod));
            (yylhs.value.mod) = driver.MakeModification(mod, yylhs.location, true);
        }
/* Line 817 of lalr1.cc  */
#line 2653 "cfdg.tab.cpp"
    break;

  case 164:
/* Line 817 of lalr1.cc  */
#line 1168 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yystack_[2].value.mod));
            (yylhs.value.mod) = driver.MakeModification(mod, yylhs.location, false);
        }
/* Line 817 of lalr1.cc  */
#line 2664 "cfdg.tab.cpp"
    break;

  case 165:
/* Line 817 of lalr1.cc  */
#line 1175 "../../src-common/cfdg.ypp"
    {
            term_ptr mod((yystack_[0].value.term));
            driver.MakeModTerm((yystack_[1].value.mod)->modExp, mod);
            (yylhs.value.mod) = (yystack_[1].value.mod);
        }
/* Line 817 of lalr1.cc  */
#line 2676 "cfdg.tab.cpp"
    break;

  case 166:
/* Line 817 of lalr1.cc  */
#line 1180 "../../src-common/cfdg.ypp"
    {
            static const yy::location def;
            ASTmodification* m = new ASTmodification(def);
            m->flags = 0;
            (yylhs.value.mod) = m;
        }
/* Line 817 of lalr1.cc  */
#line 2689 "cfdg.tab.cpp"
    break;

  case 167:
/* Line 817 of lalr1.cc  */
#line 1189 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yystack_[0].value.expression));
            (yylhs.value.term) = new ASTmodTerm((ASTmodTerm::modTypeEnum)((yystack_[1].value.modToken)), mod.release(), yylhs.location);
        }
/* Line 817 of lalr1.cc  */
#line 2700 "cfdg.tab.cpp"
    break;

  case 168:
/* Line 817 of lalr1.cc  */
#line 1194 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yystack_[1].value.expression));
            if ((yystack_[2].value.modToken) < ASTmodTerm::hue || (yystack_[2].value.modToken) > ASTmodTerm::alpha) {
                error(yylhs.location, "The target operator can only be applied to color adjustments");
                (yylhs.value.term) = 0;
            } else {
                (yylhs.value.term) = new ASTmodTerm((ASTmodTerm::modTypeEnum)((yystack_[2].value.modToken) + 4), mod.release(), yylhs.location);
            }
        }
/* Line 817 of lalr1.cc  */
#line 2716 "cfdg.tab.cpp"
    break;

  case 169:
/* Line 817 of lalr1.cc  */
#line 1204 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yystack_[0].value.string));
            (yylhs.value.term) = new ASTmodTerm(ASTmodTerm::param, *p, yylhs.location);
        }
/* Line 817 of lalr1.cc  */
#line 2727 "cfdg.tab.cpp"
    break;

  case 170:
/* Line 817 of lalr1.cc  */
#line 1209 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yystack_[0].value.string));
            (yylhs.value.term) = new ASTmodTerm(ASTmodTerm::param, *p, yylhs.location);
        }
/* Line 817 of lalr1.cc  */
#line 2738 "cfdg.tab.cpp"
    break;

  case 171:
/* Line 817 of lalr1.cc  */
#line 1216 "../../src-common/cfdg.ypp"
    {
            ASTrepContainer* tempHolder = new ASTrepContainer();
            driver.push_repContainer(*tempHolder);
            (yylhs.value.bodyObj) = tempHolder;
        }
/* Line 817 of lalr1.cc  */
#line 2750 "cfdg.tab.cpp"
    break;

  case 172:
/* Line 817 of lalr1.cc  */
#line 1224 "../../src-common/cfdg.ypp"
    {
            (yylhs.value.expression) = (yystack_[1].value.expression);
        }
/* Line 817 of lalr1.cc  */
#line 2760 "cfdg.tab.cpp"
    break;

  case 175:
/* Line 817 of lalr1.cc  */
#line 1236 "../../src-common/cfdg.ypp"
    {
            str_ptr var((yystack_[2].value.string));
            exp_ptr exp((yystack_[0].value.expression));
            driver.NextParameter(*var, exp, yystack_[2].location, yystack_[0].location);
        }
/* Line 817 of lalr1.cc  */
#line 2772 "cfdg.tab.cpp"
    break;

  case 176:
/* Line 817 of lalr1.cc  */
#line 1242 "../../src-common/cfdg.ypp"
    {
            exp_ptr exp((yystack_[0].value.expression));
            error(yystack_[2].location, "Reserved keyword: adjustment");
        }
/* Line 817 of lalr1.cc  */
#line 2783 "cfdg.tab.cpp"
    break;

  case 177:
/* Line 817 of lalr1.cc  */
#line 1249 "../../src-common/cfdg.ypp"
    {
            (yylhs.value.expression) = ASTexpression::Append((yystack_[1].value.expression), (yystack_[0].value.expression));
        }
/* Line 817 of lalr1.cc  */
#line 2793 "cfdg.tab.cpp"
    break;

  case 178:
/* Line 817 of lalr1.cc  */
#line 1253 "../../src-common/cfdg.ypp"
    { 
            (yylhs.value.expression) = (yystack_[0].value.expression); 
        }
/* Line 817 of lalr1.cc  */
#line 2803 "cfdg.tab.cpp"
    break;

  case 179:
/* Line 817 of lalr1.cc  */
#line 1260 "../../src-common/cfdg.ypp"
    {
            (yylhs.value.expression) = (yystack_[2].value.expression)->append(new ASTparen((yystack_[0].value.expression)));
        }
/* Line 817 of lalr1.cc  */
#line 2813 "cfdg.tab.cpp"
    break;

  case 180:
/* Line 817 of lalr1.cc  */
#line 1264 "../../src-common/cfdg.ypp"
    {
            (yylhs.value.expression) = new ASTcons(new ASTparen((yystack_[0].value.expression)), 0);
        }
/* Line 817 of lalr1.cc  */
#line 2823 "cfdg.tab.cpp"
    break;

  case 181:
/* Line 817 of lalr1.cc  */
#line 1270 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASTreal(*(yystack_[0].value.string), yylhs.location); delete (yystack_[0].value.string); }
/* Line 817 of lalr1.cc  */
#line 2831 "cfdg.tab.cpp"
    break;

  case 182:
/* Line 817 of lalr1.cc  */
#line 1272 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASTreal(Renderer::Infinity, yylhs.location); }
/* Line 817 of lalr1.cc  */
#line 2839 "cfdg.tab.cpp"
    break;

  case 183:
/* Line 817 of lalr1.cc  */
#line 1274 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASTparen((yystack_[1].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 2847 "cfdg.tab.cpp"
    break;

  case 184:
/* Line 817 of lalr1.cc  */
#line 1276 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = (yystack_[0].value.expression); }
/* Line 817 of lalr1.cc  */
#line 2855 "cfdg.tab.cpp"
    break;

  case 185:
/* Line 817 of lalr1.cc  */
#line 1278 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('N', (yystack_[0].value.expression), NULL);; }
/* Line 817 of lalr1.cc  */
#line 2863 "cfdg.tab.cpp"
    break;

  case 186:
/* Line 817 of lalr1.cc  */
#line 1280 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('P', (yystack_[0].value.expression), NULL);; }
/* Line 817 of lalr1.cc  */
#line 2871 "cfdg.tab.cpp"
    break;

  case 187:
/* Line 817 of lalr1.cc  */
#line 1282 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yystack_[2].value.expression)->append((yystack_[0].value.expression)));
            (yylhs.value.expression) = new ASTfunction("rand", pair, driver.mSeed, yystack_[2].location, yylhs.location);
        }
/* Line 817 of lalr1.cc  */
#line 2882 "cfdg.tab.cpp"
    break;

  case 188:
/* Line 817 of lalr1.cc  */
#line 1287 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yystack_[2].value.expression)->append((yystack_[0].value.expression)));
            (yylhs.value.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, yystack_[2].location, yylhs.location);
        }
/* Line 817 of lalr1.cc  */
#line 2893 "cfdg.tab.cpp"
    break;

  case 189:
/* Line 817 of lalr1.cc  */
#line 1294 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASTreal(*(yystack_[0].value.string), yylhs.location); delete (yystack_[0].value.string); }
/* Line 817 of lalr1.cc  */
#line 2901 "cfdg.tab.cpp"
    break;

  case 190:
/* Line 817 of lalr1.cc  */
#line 1296 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASTreal(Renderer::Infinity, yylhs.location); }
/* Line 817 of lalr1.cc  */
#line 2909 "cfdg.tab.cpp"
    break;

  case 191:
/* Line 817 of lalr1.cc  */
#line 1298 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = (yystack_[0].value.expression); }
/* Line 817 of lalr1.cc  */
#line 2917 "cfdg.tab.cpp"
    break;

  case 192:
/* Line 817 of lalr1.cc  */
#line 1300 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yystack_[2].value.expression)->append((yystack_[0].value.expression)));
            (yylhs.value.expression) = new ASTfunction("rand", pair, driver.mSeed, yystack_[2].location, yylhs.location);
        }
/* Line 817 of lalr1.cc  */
#line 2928 "cfdg.tab.cpp"
    break;

  case 193:
/* Line 817 of lalr1.cc  */
#line 1305 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yystack_[2].value.expression)->append((yystack_[0].value.expression)));
            (yylhs.value.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, yystack_[2].location, yylhs.location);
        }
/* Line 817 of lalr1.cc  */
#line 2939 "cfdg.tab.cpp"
    break;

  case 194:
/* Line 817 of lalr1.cc  */
#line 1310 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = (yystack_[2].value.expression)->append((yystack_[0].value.expression));   }
/* Line 817 of lalr1.cc  */
#line 2947 "cfdg.tab.cpp"
    break;

  case 195:
/* Line 817 of lalr1.cc  */
#line 1312 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('+', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 2955 "cfdg.tab.cpp"
    break;

  case 196:
/* Line 817 of lalr1.cc  */
#line 1314 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('-', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 2963 "cfdg.tab.cpp"
    break;

  case 197:
/* Line 817 of lalr1.cc  */
#line 1316 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('_', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 2971 "cfdg.tab.cpp"
    break;

  case 198:
/* Line 817 of lalr1.cc  */
#line 1318 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('*', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 2979 "cfdg.tab.cpp"
    break;

  case 199:
/* Line 817 of lalr1.cc  */
#line 1320 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('/', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 2987 "cfdg.tab.cpp"
    break;

  case 200:
/* Line 817 of lalr1.cc  */
#line 1322 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('N', (yystack_[0].value.expression), NULL); }
/* Line 817 of lalr1.cc  */
#line 2995 "cfdg.tab.cpp"
    break;

  case 201:
/* Line 817 of lalr1.cc  */
#line 1324 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('P', (yystack_[0].value.expression), NULL); }
/* Line 817 of lalr1.cc  */
#line 3003 "cfdg.tab.cpp"
    break;

  case 202:
/* Line 817 of lalr1.cc  */
#line 1326 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('!', (yystack_[0].value.expression), NULL); }
/* Line 817 of lalr1.cc  */
#line 3011 "cfdg.tab.cpp"
    break;

  case 203:
/* Line 817 of lalr1.cc  */
#line 1328 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('^', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3019 "cfdg.tab.cpp"
    break;

  case 204:
/* Line 817 of lalr1.cc  */
#line 1330 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('<', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3027 "cfdg.tab.cpp"
    break;

  case 205:
/* Line 817 of lalr1.cc  */
#line 1332 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('L', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3035 "cfdg.tab.cpp"
    break;

  case 206:
/* Line 817 of lalr1.cc  */
#line 1334 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('>', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3043 "cfdg.tab.cpp"
    break;

  case 207:
/* Line 817 of lalr1.cc  */
#line 1336 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('G', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3051 "cfdg.tab.cpp"
    break;

  case 208:
/* Line 817 of lalr1.cc  */
#line 1338 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('=', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3059 "cfdg.tab.cpp"
    break;

  case 209:
/* Line 817 of lalr1.cc  */
#line 1340 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('n', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3067 "cfdg.tab.cpp"
    break;

  case 210:
/* Line 817 of lalr1.cc  */
#line 1342 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('&', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3075 "cfdg.tab.cpp"
    break;

  case 211:
/* Line 817 of lalr1.cc  */
#line 1344 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('|', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3083 "cfdg.tab.cpp"
    break;

  case 212:
/* Line 817 of lalr1.cc  */
#line 1346 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('X', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3091 "cfdg.tab.cpp"
    break;

  case 213:
/* Line 817 of lalr1.cc  */
#line 1348 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASTparen((yystack_[1].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3099 "cfdg.tab.cpp"
    break;

  case 214:
/* Line 817 of lalr1.cc  */
#line 1350 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = (yystack_[0].value.mod); }
/* Line 817 of lalr1.cc  */
#line 3107 "cfdg.tab.cpp"
    break;

  case 215:
/* Line 817 of lalr1.cc  */
#line 1354 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASTreal(*(yystack_[0].value.string), yylhs.location); delete (yystack_[0].value.string); }
/* Line 817 of lalr1.cc  */
#line 3115 "cfdg.tab.cpp"
    break;

  case 216:
/* Line 817 of lalr1.cc  */
#line 1356 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASTreal(Renderer::Infinity, yylhs.location); }
/* Line 817 of lalr1.cc  */
#line 3123 "cfdg.tab.cpp"
    break;

  case 217:
/* Line 817 of lalr1.cc  */
#line 1358 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = (yystack_[0].value.expression); }
/* Line 817 of lalr1.cc  */
#line 3131 "cfdg.tab.cpp"
    break;

  case 218:
/* Line 817 of lalr1.cc  */
#line 1360 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yystack_[2].value.expression)->append((yystack_[0].value.expression)));
            (yylhs.value.expression) = new ASTfunction("rand", pair, driver.mSeed, yystack_[2].location, yylhs.location);
        }
/* Line 817 of lalr1.cc  */
#line 3142 "cfdg.tab.cpp"
    break;

  case 219:
/* Line 817 of lalr1.cc  */
#line 1365 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yystack_[2].value.expression)->append((yystack_[0].value.expression)));
            (yylhs.value.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, yystack_[2].location, yylhs.location);
        }
/* Line 817 of lalr1.cc  */
#line 3153 "cfdg.tab.cpp"
    break;

  case 220:
/* Line 817 of lalr1.cc  */
#line 1370 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('+', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3161 "cfdg.tab.cpp"
    break;

  case 221:
/* Line 817 of lalr1.cc  */
#line 1372 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('-', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3169 "cfdg.tab.cpp"
    break;

  case 222:
/* Line 817 of lalr1.cc  */
#line 1374 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('_', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3177 "cfdg.tab.cpp"
    break;

  case 223:
/* Line 817 of lalr1.cc  */
#line 1376 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('*', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3185 "cfdg.tab.cpp"
    break;

  case 224:
/* Line 817 of lalr1.cc  */
#line 1378 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('/', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3193 "cfdg.tab.cpp"
    break;

  case 225:
/* Line 817 of lalr1.cc  */
#line 1380 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('N', (yystack_[0].value.expression), NULL); }
/* Line 817 of lalr1.cc  */
#line 3201 "cfdg.tab.cpp"
    break;

  case 226:
/* Line 817 of lalr1.cc  */
#line 1382 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('P', (yystack_[0].value.expression), NULL); }
/* Line 817 of lalr1.cc  */
#line 3209 "cfdg.tab.cpp"
    break;

  case 227:
/* Line 817 of lalr1.cc  */
#line 1384 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('!', (yystack_[0].value.expression), NULL); }
/* Line 817 of lalr1.cc  */
#line 3217 "cfdg.tab.cpp"
    break;

  case 228:
/* Line 817 of lalr1.cc  */
#line 1386 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('^', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3225 "cfdg.tab.cpp"
    break;

  case 229:
/* Line 817 of lalr1.cc  */
#line 1388 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('<', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3233 "cfdg.tab.cpp"
    break;

  case 230:
/* Line 817 of lalr1.cc  */
#line 1390 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('L', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3241 "cfdg.tab.cpp"
    break;

  case 231:
/* Line 817 of lalr1.cc  */
#line 1392 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('>', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3249 "cfdg.tab.cpp"
    break;

  case 232:
/* Line 817 of lalr1.cc  */
#line 1394 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('G', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3257 "cfdg.tab.cpp"
    break;

  case 233:
/* Line 817 of lalr1.cc  */
#line 1396 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('=', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3265 "cfdg.tab.cpp"
    break;

  case 234:
/* Line 817 of lalr1.cc  */
#line 1398 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('n', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3273 "cfdg.tab.cpp"
    break;

  case 235:
/* Line 817 of lalr1.cc  */
#line 1400 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('&', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3281 "cfdg.tab.cpp"
    break;

  case 236:
/* Line 817 of lalr1.cc  */
#line 1402 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('|', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3289 "cfdg.tab.cpp"
    break;

  case 237:
/* Line 817 of lalr1.cc  */
#line 1404 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASToperator('X', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3297 "cfdg.tab.cpp"
    break;

  case 238:
/* Line 817 of lalr1.cc  */
#line 1406 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = new ASTparen((yystack_[1].value.expression)); }
/* Line 817 of lalr1.cc  */
#line 3305 "cfdg.tab.cpp"
    break;

  case 239:
/* Line 817 of lalr1.cc  */
#line 1408 "../../src-common/cfdg.ypp"
    { (yylhs.value.expression) = (yystack_[0].value.mod); }
/* Line 817 of lalr1.cc  */
#line 3313 "cfdg.tab.cpp"
    break;

  case 240:
/* Line 817 of lalr1.cc  */
#line 1412 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yystack_[2].value.string));
            (yylhs.value.expression) = driver.MakeFunction(func, exp_ptr(), yystack_[2].location, yystack_[1].location + yystack_[0].location, false);
        }
/* Line 817 of lalr1.cc  */
#line 3324 "cfdg.tab.cpp"
    break;

  case 241:
/* Line 817 of lalr1.cc  */
#line 1417 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yystack_[3].value.string));
            exp_ptr args((yystack_[1].value.expression));
            (yylhs.value.expression) = driver.MakeFunction(func, args, yystack_[3].location, yystack_[1].location, true);
        }
/* Line 817 of lalr1.cc  */
#line 3336 "cfdg.tab.cpp"
    break;

  case 242:
/* Line 817 of lalr1.cc  */
#line 1423 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yystack_[3].value.string));
            exp_ptr args((yystack_[1].value.expression));
            (yylhs.value.expression) = driver.MakeArray(func, args, yystack_[3].location, yystack_[1].location);
        }
/* Line 817 of lalr1.cc  */
#line 3348 "cfdg.tab.cpp"
    break;

  case 243:
/* Line 817 of lalr1.cc  */
#line 1429 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yystack_[1].value.expression));
            (yylhs.value.expression) = driver.MakeFunction(func, args, yystack_[3].location, yystack_[1].location, false);
        }
/* Line 817 of lalr1.cc  */
#line 3360 "cfdg.tab.cpp"
    break;

  case 244:
/* Line 817 of lalr1.cc  */
#line 1435 "../../src-common/cfdg.ypp"
    {
            exp_ptr exp((yystack_[0].value.expression));
            std::auto_ptr<ASTrepContainer> vars((yystack_[1].value.bodyObj));
            (yylhs.value.expression) = driver.MakeLet(yystack_[1].location, exp);
        }
/* Line 817 of lalr1.cc  */
#line 3372 "cfdg.tab.cpp"
    break;

  case 245:
/* Line 817 of lalr1.cc  */
#line 1441 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yystack_[0].value.string));
            (yylhs.value.expression) = driver.MakeVariable(*var, yystack_[0].location);
        }
/* Line 817 of lalr1.cc  */
#line 3383 "cfdg.tab.cpp"
    break;

  case 246:
/* Line 817 of lalr1.cc  */
#line 1448 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yystack_[2].value.string));
            (yylhs.value.expression) = driver.MakeFunction(func, exp_ptr(), yystack_[2].location, yystack_[1].location + yystack_[0].location, false);
        }
/* Line 817 of lalr1.cc  */
#line 3394 "cfdg.tab.cpp"
    break;

  case 247:
/* Line 817 of lalr1.cc  */
#line 1453 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yystack_[3].value.string));
            exp_ptr args((yystack_[1].value.expression));
            (yylhs.value.expression) = driver.MakeFunction(func, args, yystack_[3].location, yystack_[1].location, false);
        }
/* Line 817 of lalr1.cc  */
#line 3406 "cfdg.tab.cpp"
    break;

  case 248:
/* Line 817 of lalr1.cc  */
#line 1459 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yystack_[3].value.string));
            exp_ptr args((yystack_[1].value.expression));
            (yylhs.value.expression) = driver.MakeArray(func, args, yystack_[3].location, yystack_[1].location);
        }
/* Line 817 of lalr1.cc  */
#line 3418 "cfdg.tab.cpp"
    break;

  case 249:
/* Line 817 of lalr1.cc  */
#line 1465 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yystack_[1].value.expression));
            (yylhs.value.expression) = driver.MakeFunction(func, args, yystack_[3].location, yystack_[1].location, false);
        }
/* Line 817 of lalr1.cc  */
#line 3430 "cfdg.tab.cpp"
    break;

  case 250:
/* Line 817 of lalr1.cc  */
#line 1471 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yystack_[3].value.string));
            exp_ptr args(new ASTexpression(yystack_[3].location + yystack_[0].location));
            (yylhs.value.expression) = driver.MakeFunction(func, args, yystack_[3].location, yystack_[1].location, false);
        }
/* Line 817 of lalr1.cc  */
#line 3442 "cfdg.tab.cpp"
    break;

  case 251:
/* Line 817 of lalr1.cc  */
#line 1477 "../../src-common/cfdg.ypp"
    {
            exp_ptr exp((yystack_[0].value.expression));
            std::auto_ptr<ASTrepContainer> vars((yystack_[1].value.bodyObj));
            (yylhs.value.expression) = driver.MakeLet(yystack_[1].location, exp);
        }
/* Line 817 of lalr1.cc  */
#line 3454 "cfdg.tab.cpp"
    break;

  case 252:
/* Line 817 of lalr1.cc  */
#line 1483 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yystack_[0].value.string));
            (yylhs.value.expression) = driver.MakeVariable(*var, yystack_[0].location);
        }
/* Line 817 of lalr1.cc  */
#line 3465 "cfdg.tab.cpp"
    break;

  case 253:
/* Line 817 of lalr1.cc  */
#line 1490 "../../src-common/cfdg.ypp"
    { (yylhs.value.string) = (yystack_[0].value.string); }
/* Line 817 of lalr1.cc  */
#line 3473 "cfdg.tab.cpp"
    break;

  case 254:
/* Line 817 of lalr1.cc  */
#line 1492 "../../src-common/cfdg.ypp"
    { (yylhs.value.string) = (yystack_[0].value.string); }
/* Line 817 of lalr1.cc  */
#line 3481 "cfdg.tab.cpp"
    break;


/* Line 817 of lalr1.cc  */
#line 3486 "cfdg.tab.cpp"
          default:
            break;
          }
      }
    catch (const syntax_error& yyexc)
      {
        error (yyexc);
        YYERROR;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yylhs);


    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    /* Shift the result of the reduction.  */
    yypush_ (YY_NULL, yylhs);
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        /* Return failure if at end of input.  */
        if (yyla.type == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   /* Each real token shifted decrements this.  */
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      /* Shift the error token.  */
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyempty)
          yy_destroy_ (YY_NULL, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULL, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  CfdgParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  CfdgParser::yysyntax_error_ (int, int)
  {
    return YY_("syntax error");
  }


  const short int CfdgParser::yypact_ninf_ = -257;

  const signed char CfdgParser::yytable_ninf_ = -92;

  const short int
  CfdgParser::yypact_[] =
  {
     328,  -257,  -257,    26,  1276,  1297,  -257,     6,  -257,    45,
      79,     3,   123,   118,  -257,    42,   318,  -257,   118,  -257,
    -257,  -257,  -257,  -257,  -257,  -257,  -257,    87,  -257,   120,
    -257,   187,    17,   168,   181,    -1,   118,    97,   318,   166,
     118,  -257,  -257,  -257,  -257,  -257,  -257,   617,   172,  -257,
    -257,  -257,   178,   182,  -257,  -257,   314,   237,   270,   242,
    -257,  -257,  -257,  -257,  -257,  -257,  -257,   244,  -257,  -257,
    -257,  -257,  -257,  -257,  -257,   246,   250,   261,   266,  -257,
     272,  -257,    27,   331,  -257,  -257,  -257,   272,   261,   333,
    -257,   311,   318,  -257,   296,  -257,   320,  -257,   302,   617,
    -257,   617,   617,   617,   325,  -257,   330,  1032,  -257,  -257,
     167,  -257,  -257,  -257,  -257,  -257,  -257,  -257,   111,   274,
    -257,   161,   368,   406,   250,  -257,   376,    27,  -257,   388,
       9,  -257,    84,  -257,   131,  -257,  -257,   -32,  -257,   390,
     392,  -257,  -257,  -257,   617,   435,   617,   346,   346,   346,
     753,  -257,   201,   164,  -257,   617,   617,   617,   617,   617,
     617,   617,   617,   617,   617,   617,   617,   617,   617,   617,
     617,   617,   617,   214,   575,   347,   348,   617,   541,     4,
     354,  -257,   -11,  -257,   617,  -257,  -257,  -257,  -257,   397,
     250,   484,   484,   484,   351,   330,   246,   303,   327,   186,
     116,  -257,  -257,  -257,  -257,   361,  -257,  -257,  -257,     8,
     118,  -257,  -257,  -257,  -257,   405,    44,    64,  -257,  -257,
    -257,  -257,   180,   118,   357,  -257,   638,  -257,   638,   638,
     617,  -257,  -257,   -25,  1063,  -257,  -257,  -257,    77,  -257,
      80,  -257,  -257,  -257,  -257,     9,  -257,  -257,  -257,   784,
     358,  -257,   156,   660,  -257,   286,  -257,   407,   412,   356,
    -257,   389,   389,   669,   669,   669,   669,  1217,  1217,  1177,
    1133,  1087,  1032,    67,    67,    67,   346,   346,   346,   246,
     415,    86,  1032,   617,   617,  1032,  -257,  1032,  -257,  -257,
    -257,   478,  -257,  1032,  -257,   484,  -257,   413,  -257,  -257,
    -257,  -257,   250,   250,  -257,  -257,   370,   371,  -257,   372,
    -257,   186,   186,   617,   330,   186,   283,  -257,  -257,  -257,
    -257,  -257,  -257,  -257,  -257,  -257,  -257,  -257,  -257,  -257,
     365,  -257,  -257,  -257,  -257,  -257,   378,   378,   378,   815,
     638,  -257,   638,   638,   638,   638,   638,   638,   638,   638,
     638,   638,   638,   638,   638,   638,   638,   638,   638,   423,
    -257,  -257,  -257,  -257,  -257,  -257,   373,   617,   617,   596,
     250,   617,   617,   846,   877,  -257,   908,   484,  -257,   349,
    -257,    83,  -257,  -257,   617,   512,   617,  -257,  -257,   939,
    -257,   367,   186,   186,  -257,   118,   297,   307,   382,  -257,
    1063,   420,   420,   730,   730,   730,   730,  1237,  1237,  1197,
    1155,  1110,   317,   317,   317,   378,   378,   378,  -257,  1032,
    1032,    94,  -257,   970,  -257,  1032,  1032,   250,  -257,  -257,
    -257,  -257,   383,   617,  -257,  -257,   484,  1001,  -257,   175,
     691,  -257,  -257,  -257,  -257,  -257,  -257,  -257,  -257,  -257,
    -257,   722,  -257,  -257,  -257,  -257,  -257
  };

  const unsigned char
  CfdgParser::yydefact_[] =
  {
       0,     5,     7,     0,     2,     3,     1,     0,    32,     0,
       0,     0,     0,     0,    44,     0,     0,    31,     0,     4,
      25,    19,    20,    17,    18,    21,    22,     0,    23,     0,
      24,     0,     0,    74,     0,     0,     0,     0,     0,    48,
       0,     6,    16,     9,    10,     8,    15,     0,    13,    98,
      14,    41,     0,     0,    11,    12,    52,     0,    71,    79,
      27,   166,   166,    55,    28,    53,    26,     0,    29,    45,
      46,    42,    54,   143,   100,    96,     0,     0,    90,    75,
      90,    64,     0,     0,    39,    37,    60,    90,     0,     0,
      40,     0,     0,    38,     0,   171,   252,   189,     0,     0,
     190,     0,     0,     0,   166,   214,     0,    56,   191,    69,
       0,    98,    98,    34,    35,    36,    72,    33,     0,     0,
      30,     0,     0,     0,    51,    50,     0,     0,    68,     0,
       0,    76,     0,    86,    85,    92,    88,     0,    62,     0,
       0,    58,    47,    43,     0,     0,     0,   202,   200,   201,
       0,   166,     0,     0,   251,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   253,
       0,   254,     0,    70,     0,   117,   116,    97,   125,   118,
       0,     0,     0,     0,     0,     0,    96,     0,     0,     0,
       0,   162,   165,   161,   253,     0,    73,   147,   142,     0,
       0,   134,   135,   138,   140,   139,   253,     0,    80,   129,
      99,   131,     0,     0,     0,   215,     0,   216,     0,     0,
       0,    95,   239,     0,   180,   217,    49,    61,     0,    57,
       0,    84,    82,    83,    81,     0,    91,    63,    59,     0,
       0,   246,     0,     0,   213,     0,   163,     0,     0,     0,
     174,   192,   193,   205,   204,   207,   206,   208,   209,   210,
     211,   212,   194,   196,   195,   197,   198,   199,   203,    96,
       0,   252,   153,     0,     0,   157,    66,   156,    65,   127,
     126,     0,   128,    67,   119,     0,    98,   121,   110,   122,
     123,   114,     0,     0,    77,    78,     0,   245,   181,     0,
     182,     0,     0,     0,     0,   167,   178,   184,   169,   170,
     149,   143,   148,   145,   146,   137,   136,   133,   132,   166,
       0,   100,   112,   130,   102,    94,   227,   225,   226,     0,
       0,    93,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    89,
      89,    87,   249,   250,   247,   248,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   104,     0,     0,   141,     0,
     155,     0,   107,   105,     0,     0,     0,   185,   186,     0,
     244,   177,     0,     0,   168,     0,     0,     0,     0,   238,
     179,   218,   219,   230,   229,   232,   231,   233,   234,   235,
     236,   237,   221,   220,   222,   223,   224,   228,   164,   176,
     175,   252,   173,     0,   108,   152,   151,   154,   158,   103,
     120,   109,     0,     0,   124,   113,     0,     0,   240,     0,
       0,   183,   187,   188,   150,   144,   101,   111,   172,   106,
     160,     0,   115,   243,   241,   242,   159
  };

  const short int
  CfdgParser::yypgoto_[] =
  {
    -257,  -257,  -257,  -257,  -257,  -257,  -257,  -257,  -257,  -257,
     431,   -26,  -257,  -257,  -257,  -257,  -257,  -257,  -257,  -257,
    -257,  -257,  -257,  -257,  -257,   444,  -257,  -257,  -257,  -257,
    -257,  -257,  -257,   206,    95,   122,    61,  -186,  -105,   121,
     233,  -257,  -189,  -257,  -257,  -257,   -89,  -257,  -257,  -257,
    -257,  -257,   137,  -257,   251,  -257,  -111,  -257,  -257,  -257,
    -257,  -257,  -257,  -257,   -13,   -75,   -37,  -257,   -80,  -187,
    -257,    90,  -257,  -143,  -256,   -83,  -184,  -257,   -94,   -81
  };

  const short int
  CfdgParser::yydefgoto_[] =
  {
      -1,     3,     4,     5,    41,    19,    20,    42,    21,    43,
      22,    71,    92,    45,    23,    24,    25,    26,    46,    47,
     184,   185,    48,    49,    50,    27,    28,    52,    53,    54,
      55,    29,    30,   136,   137,   128,    83,   124,   110,   122,
     219,   186,   297,   333,   381,   435,   298,   377,   188,   220,
     221,   189,   121,   322,   207,   208,   209,   395,   190,   191,
     192,   193,   194,   436,    63,   105,   118,   202,   106,   154,
     259,   260,   315,   233,   316,   107,   234,   317,   108,   196
  };

  const short int
  CfdgParser::yytable_[] =
  {
      65,   125,   252,   299,   300,    72,   197,   198,   302,    81,
     303,   222,    90,    60,   288,   132,   147,   245,   148,   149,
     150,   187,    84,    85,   340,   119,     6,    93,   133,   235,
     195,   246,    56,   132,   204,   134,    77,    57,   341,   181,
     210,   223,   336,    78,   337,   338,   133,   291,   232,   236,
     292,   235,    66,   134,   326,   387,   388,    82,    61,   391,
      62,   249,    61,   253,    62,   289,   143,   152,    67,   321,
     232,    58,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     135,   282,   279,   370,   285,   287,   372,   432,    89,   433,
      68,   293,   327,   241,   368,    59,   378,    86,   187,   187,
     242,   195,   195,   195,   255,   295,    87,   195,   195,   314,
     170,   171,   328,    88,   172,   329,   245,   390,   210,   245,
     199,   200,   235,    64,   235,   235,   442,   443,   126,   129,
     359,   223,   318,   360,   145,   434,   319,   339,    73,   140,
     243,   232,   145,   232,   232,    82,   400,   244,   401,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,   412,
     413,   414,   415,   416,   417,   173,   201,    61,   174,    62,
     175,    74,   176,   257,   177,    95,   178,   204,   430,   205,
     258,   379,   181,   179,    58,   180,    79,   324,   181,   306,
     373,   374,   131,   182,    95,   340,   204,    80,   376,   139,
     334,   181,   307,    75,   308,   195,   330,   309,    76,   364,
     199,   200,   238,   206,   340,   240,    91,   382,   383,   183,
     389,   314,   314,   109,   310,   314,   311,   312,   454,   111,
     204,   331,   439,   112,   313,   181,   235,   452,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   232,   256,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   419,   420,   423,   222,   425,   426,
     187,   235,   397,   199,   200,   424,   115,   195,   116,   195,
     117,   437,   120,   440,   123,   199,   200,   392,   393,   104,
     232,   173,   314,   314,   174,   210,   175,   223,   176,    82,
     177,    95,   178,   204,   127,   205,   199,   200,   181,   179,
     130,   180,     1,     2,   181,   173,   203,   142,   174,   182,
     175,   138,   176,   141,   177,    95,   178,    69,    70,   394,
     451,   366,   449,   179,   144,   180,   195,   173,   181,   445,
     174,   146,   175,   182,   176,   304,   177,    95,   178,   446,
     356,   357,   113,   114,   358,   179,   211,   180,   145,   212,
     181,   213,   444,   214,   151,   182,   237,   215,   153,   305,
     211,   392,   393,   212,   216,   213,   205,   214,   239,   181,
     247,   215,   248,   172,   217,   283,   284,   290,   216,   294,
     205,   431,   301,   181,   320,   325,   224,   367,   217,    94,
     335,   363,   368,   369,    95,   371,   329,   380,   384,   385,
     218,   386,    96,   -91,   225,   358,    44,    98,   418,   167,
     168,   169,   170,   171,   447,   250,   172,   450,    94,    51,
     226,   361,   398,    95,   227,   332,   228,   229,   396,   422,
     323,    96,     0,   225,   230,   104,    98,     0,     0,   231,
     353,   354,   355,   356,   357,     0,     0,   358,     0,   226,
       0,     0,     0,   227,     0,   228,   229,     0,     0,     0,
       0,    94,   173,   230,   104,   174,    95,   175,   251,   176,
       0,   177,    95,   178,    96,     0,    97,     0,     0,    98,
     179,     0,   180,     0,     0,   181,     0,     0,     0,     0,
     182,     0,    99,     0,     0,    94,   100,     0,   101,   102,
      95,     0,     0,     0,     0,     0,   103,   104,    96,     0,
     225,   375,     0,    98,     0,   296,     0,     0,     0,     0,
       0,   286,     0,     0,    94,     0,   226,     0,     0,    95,
     227,     0,   228,   229,     0,     0,     0,    96,     0,    97,
     230,   104,    98,     0,     0,   438,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    99,     0,     0,    94,   100,
       0,   101,   102,    95,   280,     0,     0,     0,     0,   103,
     104,   281,     0,    97,     0,     0,    98,     0,     0,    94,
       0,     0,     0,     0,    95,   257,     0,     0,     0,    99,
       0,     0,   421,   100,    97,   101,   102,    98,     0,     0,
      94,     0,     0,   103,   104,    95,     0,     0,     0,     0,
      99,     0,     0,    96,   100,    97,   101,   102,    98,     0,
       0,    94,     0,     0,   103,   104,    95,     0,     0,     0,
       0,    99,     0,     0,    96,   100,   225,   101,   102,    98,
       0,     0,     0,     0,     0,   103,   104,     0,     0,     0,
       0,     0,   226,     0,   155,   156,   227,     0,   228,   229,
       0,     0,     0,   155,   156,     0,   230,   104,   157,   158,
     159,   160,   161,   162,     0,   163,   164,   165,     0,   166,
     167,   168,   169,   170,   171,   155,   156,   172,     0,   167,
     168,   169,   170,   171,     0,   365,   172,     0,     0,   157,
     158,   159,   160,   161,   162,     0,   163,   164,   165,     0,
     166,   167,   168,   169,   170,   171,   155,   156,   172,     0,
       0,     0,     0,     0,   342,   343,   455,     0,     0,     0,
     157,   158,   159,   160,   161,   162,     0,   163,   164,   165,
       0,   166,   167,   168,   169,   170,   171,   155,   156,   172,
     353,   354,   355,   356,   357,     0,   456,   358,     0,     0,
       0,   157,   158,   159,   160,   161,   162,     0,   163,   164,
     165,     0,   166,   167,   168,   169,   170,   171,   155,   156,
     172,     0,     0,     0,     0,     0,   254,     0,     0,     0,
       0,     0,   157,   158,   159,   160,   161,   162,     0,   163,
     164,   165,     0,   166,   167,   168,   169,   170,   171,   155,
     156,   172,     0,     0,     0,     0,     0,   362,     0,     0,
       0,     0,     0,   157,   158,   159,   160,   161,   162,     0,
     163,   164,   165,     0,   166,   167,   168,   169,   170,   171,
     155,   156,   172,     0,     0,     0,     0,     0,   399,     0,
       0,     0,     0,     0,   157,   158,   159,   160,   161,   162,
       0,   163,   164,   165,     0,   166,   167,   168,   169,   170,
     171,   155,   156,   172,     0,     0,     0,     0,     0,   427,
       0,     0,     0,     0,     0,   157,   158,   159,   160,   161,
     162,     0,   163,   164,   165,     0,   166,   167,   168,   169,
     170,   171,   155,   156,   172,     0,     0,     0,     0,     0,
     428,     0,     0,     0,     0,     0,   157,   158,   159,   160,
     161,   162,     0,   163,   164,   165,     0,   166,   167,   168,
     169,   170,   171,   155,   156,   172,     0,     0,     0,     0,
       0,   429,     0,     0,     0,     0,     0,   157,   158,   159,
     160,   161,   162,     0,   163,   164,   165,     0,   166,   167,
     168,   169,   170,   171,   155,   156,   172,     0,     0,     0,
       0,     0,   441,     0,     0,     0,     0,     0,   157,   158,
     159,   160,   161,   162,     0,   163,   164,   165,     0,   166,
     167,   168,   169,   170,   171,   155,   156,   172,     0,     0,
       0,     0,     0,   448,     0,     0,     0,     0,     0,   157,
     158,   159,   160,   161,   162,     0,   163,   164,   165,     0,
     166,   167,   168,   169,   170,   171,   155,   156,   172,     0,
       0,     0,     0,     0,   453,     0,     0,     0,     0,     0,
     157,   158,   159,   160,   161,   162,     0,   163,   164,   165,
       0,   166,   167,   168,   169,   170,   171,   342,   343,   172,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   344,   345,   346,   347,   348,   349,     0,   350,   351,
     352,   155,   156,   353,   354,   355,   356,   357,     0,     0,
     358,     0,     0,     0,     0,   157,   158,   159,   160,   161,
     162,     0,   163,   164,   342,   343,     0,   167,   168,   169,
     170,   171,     0,     0,   172,     0,     0,     0,   344,   345,
     346,   347,   348,   349,     0,   350,   351,   155,   156,     0,
     353,   354,   355,   356,   357,     0,     0,   358,     0,     0,
       0,   157,   158,   159,   160,   161,   162,     0,   163,   342,
     343,     0,     0,   167,   168,   169,   170,   171,     0,     0,
     172,     0,     0,   344,   345,   346,   347,   348,   349,     0,
     350,   155,   156,     0,     0,   353,   354,   355,   356,   357,
       0,     0,   358,     0,     0,   157,   158,   159,   160,   161,
     162,   342,   343,     0,     0,     0,     0,   167,   168,   169,
     170,   171,     0,     0,   172,   344,   345,   346,   347,   348,
     349,   155,   156,     0,     0,     0,     0,   353,   354,   355,
     356,   357,     0,     0,   358,   157,   158,   159,   160,     0,
       0,   342,   343,     0,     0,     0,     0,   167,   168,   169,
     170,   171,     0,     0,   172,   344,   345,   346,   347,     7,
       0,     0,     8,     9,    10,     0,     0,   353,   354,   355,
     356,   357,     0,     0,   358,    11,    12,    13,     0,    14,
      31,     0,    15,    32,    33,    34,     0,     0,    16,    17,
      18,     0,     0,     0,     0,     0,    35,     0,    36,     0,
      14,     0,     0,    37,     0,     0,     0,     0,     0,    38,
      39,    40
  };

  const short int
  CfdgParser::yycheck_[] =
  {
      13,    76,   145,   192,   193,    18,   111,   112,   195,    10,
     196,   122,    38,    10,    10,     6,    99,    49,   101,   102,
     103,   110,    35,    36,    49,    62,     0,    40,    19,   123,
     110,    63,    26,     6,    26,    26,    19,    31,    63,    31,
     121,   122,   226,    26,   228,   229,    19,    58,   123,   124,
      61,   145,    10,    26,    10,   311,   312,    58,    59,   315,
      61,   144,    59,   146,    61,    61,    92,   104,    26,    61,
     145,    26,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
      63,   174,   173,   279,   177,   178,    10,    14,    37,    16,
      58,   184,    58,    19,    10,    26,   295,    10,   197,   198,
      26,   191,   192,   193,   151,   190,    19,   197,   198,   199,
      53,    54,    58,    26,    57,    61,    49,   314,   209,    49,
      19,    20,   226,    10,   228,   229,   392,   393,    77,    78,
      63,   222,    26,    63,    58,    62,    30,   230,    61,    88,
      19,   226,    58,   228,   229,    58,   340,    26,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   358,     8,    65,    59,    11,    61,
      13,    61,    15,    19,    17,    18,    19,    26,   377,    28,
      26,   296,    31,    26,    26,    28,    28,   210,    31,    13,
     283,   284,    80,    36,    18,    49,    26,    26,   291,    87,
     223,    31,    26,    26,    28,   295,    36,    31,    31,    63,
      19,    20,   127,    62,    49,   130,    60,   302,   303,    62,
     313,   311,   312,    61,    48,   315,    50,    51,    63,    61,
      26,    61,   385,    61,    58,    31,   340,   436,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   358,   340,    65,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   367,   368,   369,   398,   371,   372,
     379,   385,   329,    19,    20,   370,    59,   377,    28,   379,
      58,   384,    58,   386,    58,    19,    20,    24,    25,    59,
     385,     8,   392,   393,    11,   396,    13,   398,    15,    58,
      17,    18,    19,    26,    58,    28,    19,    20,    31,    26,
      58,    28,     4,     5,    31,     8,    62,    26,    11,    36,
      13,    10,    15,    10,    17,    18,    19,    29,    30,    66,
     433,    65,   427,    26,    58,    28,   436,     8,    31,    62,
      11,    59,    13,    36,    15,    62,    17,    18,    19,    62,
      53,    54,    58,    59,    57,    26,     8,    28,    58,    11,
      31,    13,   395,    15,    59,    36,    10,    19,    58,    62,
       8,    24,    25,    11,    26,    13,    28,    15,    10,    31,
      10,    19,    10,    57,    36,    58,    58,    53,    26,    12,
      28,    62,    61,    31,    53,    10,    10,    10,    36,    13,
      63,    63,    10,    67,    18,    10,    61,    14,    58,    58,
      62,    59,    26,    10,    28,    57,     5,    31,    65,    50,
      51,    52,    53,    54,    62,    10,    57,    64,    13,     5,
      44,   245,   331,    18,    48,   222,    50,    51,   321,   369,
     209,    26,    -1,    28,    58,    59,    31,    -1,    -1,    63,
      50,    51,    52,    53,    54,    -1,    -1,    57,    -1,    44,
      -1,    -1,    -1,    48,    -1,    50,    51,    -1,    -1,    -1,
      -1,    13,     8,    58,    59,    11,    18,    13,    63,    15,
      -1,    17,    18,    19,    26,    -1,    28,    -1,    -1,    31,
      26,    -1,    28,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      36,    -1,    44,    -1,    -1,    13,    48,    -1,    50,    51,
      18,    -1,    -1,    -1,    -1,    -1,    58,    59,    26,    -1,
      28,    63,    -1,    31,    -1,    61,    -1,    -1,    -1,    -1,
      -1,    10,    -1,    -1,    13,    -1,    44,    -1,    -1,    18,
      48,    -1,    50,    51,    -1,    -1,    -1,    26,    -1,    28,
      58,    59,    31,    -1,    -1,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    13,    48,
      -1,    50,    51,    18,    19,    -1,    -1,    -1,    -1,    58,
      59,    26,    -1,    28,    -1,    -1,    31,    -1,    -1,    13,
      -1,    -1,    -1,    -1,    18,    19,    -1,    -1,    -1,    44,
      -1,    -1,    26,    48,    28,    50,    51,    31,    -1,    -1,
      13,    -1,    -1,    58,    59,    18,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    26,    48,    28,    50,    51,    31,    -1,
      -1,    13,    -1,    -1,    58,    59,    18,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    26,    48,    28,    50,    51,    31,
      -1,    -1,    -1,    -1,    -1,    58,    59,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    24,    25,    48,    -1,    50,    51,
      -1,    -1,    -1,    24,    25,    -1,    58,    59,    38,    39,
      40,    41,    42,    43,    -1,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    24,    25,    57,    -1,    50,
      51,    52,    53,    54,    -1,    65,    57,    -1,    -1,    38,
      39,    40,    41,    42,    43,    -1,    45,    46,    47,    -1,
      49,    50,    51,    52,    53,    54,    24,    25,    57,    -1,
      -1,    -1,    -1,    -1,    24,    25,    65,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    -1,    45,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    24,    25,    57,
      50,    51,    52,    53,    54,    -1,    64,    57,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    -1,    45,    46,
      47,    -1,    49,    50,    51,    52,    53,    54,    24,    25,
      57,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    -1,    45,
      46,    47,    -1,    49,    50,    51,    52,    53,    54,    24,
      25,    57,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    -1,
      45,    46,    47,    -1,    49,    50,    51,    52,    53,    54,
      24,    25,    57,    -1,    -1,    -1,    -1,    -1,    63,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      -1,    45,    46,    47,    -1,    49,    50,    51,    52,    53,
      54,    24,    25,    57,    -1,    -1,    -1,    -1,    -1,    63,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,
      43,    -1,    45,    46,    47,    -1,    49,    50,    51,    52,
      53,    54,    24,    25,    57,    -1,    -1,    -1,    -1,    -1,
      63,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      42,    43,    -1,    45,    46,    47,    -1,    49,    50,    51,
      52,    53,    54,    24,    25,    57,    -1,    -1,    -1,    -1,
      -1,    63,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    43,    -1,    45,    46,    47,    -1,    49,    50,
      51,    52,    53,    54,    24,    25,    57,    -1,    -1,    -1,
      -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    -1,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    24,    25,    57,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    -1,    45,    46,    47,    -1,
      49,    50,    51,    52,    53,    54,    24,    25,    57,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    -1,    45,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    24,    25,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    -1,    45,    46,
      47,    24,    25,    50,    51,    52,    53,    54,    -1,    -1,
      57,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,
      43,    -1,    45,    46,    24,    25,    -1,    50,    51,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    -1,    45,    46,    24,    25,    -1,
      50,    51,    52,    53,    54,    -1,    -1,    57,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    -1,    45,    24,
      25,    -1,    -1,    50,    51,    52,    53,    54,    -1,    -1,
      57,    -1,    -1,    38,    39,    40,    41,    42,    43,    -1,
      45,    24,    25,    -1,    -1,    50,    51,    52,    53,    54,
      -1,    -1,    57,    -1,    -1,    38,    39,    40,    41,    42,
      43,    24,    25,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    -1,    -1,    57,    38,    39,    40,    41,    42,
      43,    24,    25,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    -1,    -1,    57,    38,    39,    40,    41,    -1,
      -1,    24,    25,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    -1,    -1,    57,    38,    39,    40,    41,     3,
      -1,    -1,     6,     7,     8,    -1,    -1,    50,    51,    52,
      53,    54,    -1,    -1,    57,    19,    20,    21,    -1,    23,
       3,    -1,    26,     6,     7,     8,    -1,    -1,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    19,    -1,    21,    -1,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34
  };

  const unsigned char
  CfdgParser::yystos_[] =
  {
       0,     4,     5,    69,    70,    71,     0,     3,     6,     7,
       8,    19,    20,    21,    23,    26,    32,    33,    34,    73,
      74,    76,    78,    82,    83,    84,    85,    93,    94,    99,
     100,     3,     6,     7,     8,    19,    21,    26,    32,    33,
      34,    72,    75,    77,    78,    81,    86,    87,    90,    91,
      92,    93,    95,    96,    97,    98,    26,    31,    26,    26,
      10,    59,    61,   132,    10,   132,    10,    26,    58,    29,
      30,    79,   132,    61,    61,    26,    31,    19,    26,    28,
      26,    10,    58,   104,   132,   132,    10,    19,    26,   104,
      79,    60,    80,   132,    13,    18,    26,    28,    31,    44,
      48,    50,    51,    58,    59,   133,   136,   143,   146,    61,
     106,    61,    61,    58,    59,    59,    28,    58,   134,   134,
      58,   120,   107,    58,   105,   133,   104,    58,   103,   104,
      58,   103,     6,    19,    26,    63,   101,   102,    10,   103,
     104,    10,    26,    79,    58,    58,    59,   143,   143,   143,
     143,    59,   134,    58,   137,    24,    25,    38,    39,    40,
      41,    42,    43,    45,    46,    47,    49,    50,    51,    52,
      53,    54,    57,     8,    11,    13,    15,    17,    19,    26,
      28,    31,    36,    62,    88,    89,   109,   114,   116,   119,
     126,   127,   128,   129,   130,   136,   147,   106,   106,    19,
      20,    65,   135,    62,    26,    28,    62,   122,   123,   124,
     147,     8,    11,    13,    15,    19,    26,    36,    62,   108,
     117,   118,   124,   147,    10,    28,    44,    48,    50,    51,
      58,    63,   133,   141,   144,   146,   133,    10,   102,    10,
     102,    19,    26,    19,    26,    49,    63,    10,    10,   143,
      10,    63,   141,   143,    63,   134,    65,    19,    26,   138,
     139,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   147,
      19,    26,   143,    58,    58,   143,    10,   143,    10,    61,
      53,    58,    61,   143,    12,   133,    61,   110,   114,   110,
     110,    61,   137,   105,    62,    62,    13,    26,    28,    31,
      48,    50,    51,    58,   136,   140,   142,   145,    26,    30,
      53,    61,   121,   122,   132,    10,    10,    58,    58,    61,
      36,    61,   108,   111,   132,    63,   144,   144,   144,   143,
      49,    63,    24,    25,    38,    39,    40,    41,    42,    43,
      45,    46,    47,    50,    51,    52,    53,    54,    57,    63,
      63,   101,    63,    63,    63,    65,    65,    10,    10,    67,
     105,    10,    10,   143,   143,    63,   143,   115,   110,   106,
      14,   112,   133,   133,    58,    58,    59,   142,   142,   143,
     137,   142,    24,    25,    66,   125,   120,   134,   107,    63,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,    65,   143,
     143,    26,   139,   143,   133,   143,   143,    63,    63,    63,
     110,    62,    14,    16,    62,   113,   131,   143,    63,   141,
     143,    63,   142,   142,   132,    62,    62,    62,    63,   133,
      64,   143,   110,    63,    63,    65,    64
  };

  const unsigned char
  CfdgParser::yyr1_[] =
  {
       0,    68,    69,    69,    70,    70,    71,    71,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    75,    75,    75,
      75,    75,    76,    77,    78,    79,    79,    80,    80,    81,
      81,    81,    82,    83,    84,    85,    86,    87,    87,    87,
      87,    87,    87,    87,    87,    88,    88,    89,    90,    91,
      92,    93,    93,    94,    95,    95,    96,    97,    98,    99,
     100,   101,   101,   101,   101,   101,   101,   102,   102,   103,
     103,   104,   104,   105,   105,   105,   105,   106,   106,   107,
     107,   108,   108,   109,   109,   109,   109,   109,   109,   110,
     110,   111,   111,   112,   112,   113,   114,   114,   114,   115,
     114,   114,   114,   114,   114,   114,   116,   116,   116,   117,
     117,   117,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   119,   120,   120,   121,   121,   122,   123,   123,   125,
     124,   126,   126,   126,   127,   128,   129,   129,   130,   131,
     131,   132,   132,   133,   133,   134,   134,   135,   135,   135,
     135,   136,   137,   138,   138,   139,   139,   140,   140,   141,
     141,   142,   142,   142,   142,   142,   142,   142,   142,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     145,   145,   145,   145,   145,   145,   146,   146,   146,   146,
     146,   146,   146,   147,   147
  };

  const unsigned char
  CfdgParser::yyr2_[] =
  {
       0,     2,     2,     2,     2,     0,     2,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       3,     1,     1,     3,     3,     3,     3,     2,     2,     2,
       2,     1,     2,     3,     1,     1,     1,     2,     0,     4,
       3,     3,     2,     2,     2,     2,     2,     4,     3,     4,
       2,     4,     3,     4,     2,     2,     2,     2,     3,     2,
       3,     2,     3,     4,     1,     2,     3,     4,     4,     2,
       4,     2,     2,     2,     2,     1,     1,     3,     1,     3,
       0,     3,     2,     3,     3,     2,     0,     2,     0,     2,
       0,     4,     2,     4,     3,     3,     5,     3,     4,     3,
       1,     3,     1,     2,     0,     2,     1,     1,     1,     0,
       4,     2,     2,     2,     4,     1,     2,     2,     2,     1,
       2,     1,     2,     2,     1,     1,     2,     2,     1,     1,
       1,     3,     2,     0,     3,     1,     2,     1,     2,     0,
       4,     4,     4,     2,     4,     3,     2,     2,     4,     3,
       2,     3,     3,     3,     5,     2,     0,     2,     3,     2,
       2,     1,     5,     3,     1,     3,     3,     2,     1,     3,
       1,     1,     1,     3,     1,     2,     2,     3,     3,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     4,     4,     4,     2,     1,     3,     4,     4,     4,
       4,     2,     1,     1,     1
  };


#if YYDEBUG
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const CfdgParser::yytname_[] =
  {
  "$end", "error", "$undefined", "STARTSHAPE", "CFDG2", "CFDG3", "SHAPE",
  "RULE", "PATH", "DEFINE", "BECOMES", "LOOP", "FINALLY", "IF", "ELSE",
  "SWITCH", "CASE", "CLONE", "LET", "MODTYPE", "PARAM", "BACKGROUND",
  "BADEOF", "GOODEOF", "RANGEOP", "PLUSMINUSOP", "USER_STRING",
  "USER_INTEGER", "USER_RATIONAL", "USER_FILENAME", "USER_QSTRING",
  "USER_ARRAYNAME", "INCLUDE", "IMPORT", "TILE", "PARAMETERS",
  "USER_PATHOP", "STROKEWIDTH", "LE", "LT", "GE", "GT", "EQ", "NEQ", "NOT",
  "AND", "OR", "XOR", "CF_INFINITY", "','", "'-'", "'+'", "'_'", "'*'",
  "'/'", "POS", "NEG", "'^'", "'('", "'['", "'@'", "'{'", "'}'", "')'",
  "':'", "']'", "'|'", "';'", "$accept", "choose", "cfdg2", "cfdg3",
  "statement", "statement_v2", "v3clues", "v2stuff", "inclusion", "import",
  "eof", "fileString", "fileNameSpace", "initialization",
  "initialization_v2", "background", "tile", "size", "global_definition",
  "global_definition_header", "definition_header", "definition", "shape",
  "shape_singleton_header", "shape_singleton", "rule_header_v2", "rule_v2",
  "rule_header", "path_header", "rule", "path", "path_header_v2",
  "path_v2", "parameter", "buncha_parameters", "parameter_list",
  "function_parameter_list", "parameter_spec", "buncha_elements",
  "buncha_pathOps_v2", "pathOp_simple_v2", "element_simple",
  "one_or_more_elements", "one_or_more_pathOp_v2", "caseBody",
  "caseBody_element", "element", "$@1", "element_v2clue", "pathOp_v2",
  "pathOp_v3clues", "element_loop", "buncha_replacements_v2",
  "one_or_more_replacements_v2", "replacement_simple_v2", "replacement_v2",
  "loopHeader_v2", "$@2", "loopHeader", "ifHeader", "ifElseHeader",
  "transHeader", "switchHeader", "caseHeader", "modification_v2",
  "modification", "buncha_adjustments", "adjustment", "letHeader",
  "letBody", "letVariables", "letVariable", "explist", "arglist", "exp",
  "exp2", "exp3", "expfunc", "exp2func", "shapeName", YY_NULL
  };


  const unsigned short int
  CfdgParser::yyrline_[] =
  {
       0,   189,   189,   189,   192,   197,   201,   206,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   259,   260,   261,
     262,   263,   267,   276,   287,   294,   294,   297,   298,   302,
     315,   327,   341,   352,   362,   372,   387,   396,   402,   408,
     414,   418,   423,   428,   434,   441,   444,   451,   460,   476,
     490,   499,   508,   523,   531,   543,   560,   585,   594,   604,
     617,   624,   630,   636,   641,   645,   651,   657,   658,   662,
     663,   667,   668,   672,   673,   674,   675,   679,   684,   688,
     691,   695,   702,   712,   721,   730,   742,   756,   770,   784,
     786,   794,   796,   802,   806,   810,   814,   818,   822,   833,
     833,   851,   862,   873,   884,   893,   900,   901,   902,   906,
     908,   916,   928,   929,   930,   931,   932,   933,   934,   935,
     936,   940,   951,   954,   958,   960,   966,   975,   977,   988,
     988,  1003,  1016,  1030,  1045,  1058,  1068,  1080,  1096,  1109,
    1138,  1151,  1156,  1163,  1168,  1175,  1180,  1189,  1194,  1204,
    1209,  1216,  1224,  1230,  1232,  1236,  1242,  1249,  1253,  1260,
    1264,  1270,  1272,  1274,  1276,  1278,  1280,  1282,  1287,  1294,
    1296,  1298,  1300,  1305,  1310,  1312,  1314,  1316,  1318,  1320,
    1322,  1324,  1326,  1328,  1330,  1332,  1334,  1336,  1338,  1340,
    1342,  1344,  1346,  1348,  1350,  1354,  1356,  1358,  1360,  1365,
    1370,  1372,  1374,  1376,  1378,  1380,  1382,  1384,  1386,  1388,
    1390,  1392,  1394,  1396,  1398,  1400,  1402,  1404,  1406,  1408,
    1412,  1417,  1423,  1429,  1435,  1441,  1448,  1453,  1459,  1465,
    1471,  1477,  1483,  1490,  1492
  };

  // Print the state stack on the debug stream.
  void
  CfdgParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  CfdgParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  CfdgParser::token_number_type
  CfdgParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      58,    63,    53,    51,    49,    50,     2,    54,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    64,    67,
       2,     2,     2,     2,    60,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    59,     2,    65,    57,    52,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    61,    66,    62,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    55,    56
    };
    const unsigned int user_token_number_max_ = 305;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
/* Line 1142 of lalr1.cc  */
#line 4330 "cfdg.tab.cpp"
/* Line 1143 of lalr1.cc  */
#line 1495 "../../src-common/cfdg.ypp"


void yy::CfdgParser::error(const CfdgParser::location_type& l, const std::string& m)
{
    driver.mWant2ndPass = false;
    driver.error(l, m);
}
