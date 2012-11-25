/* A Bison parser, made by GNU Bison 2.6.4.  */

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


/* First part of user declarations.  */
/* Line 278 of lalr1.cc  */
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

/* Line 278 of lalr1.cc  */
#line 60 "cfdg.tab.cpp"


#include "cfdg.tab.hpp"

/* User implementation prologue.  */
/* Line 284 of lalr1.cc  */
#line 80 "../../src-common/cfdg.ypp"

#include "astreplacement.h"
#include "astexpression.h"
    
    using namespace AST;
/* Line 284 of lalr1.cc  */
#line 176 "../../src-common/cfdg.ypp"

#include "scanner.h"
#include "math.h"
#include "builder.h"
#include <cassert>

#undef yylex
#define yylex driver.lexer->lex

/* Line 284 of lalr1.cc  */
#line 85 "cfdg.tab.cpp"


# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

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

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
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

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
/* Line 352 of lalr1.cc  */
#line 180 "cfdg.tab.cpp"

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

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  CfdgParser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    std::ostream& yyo = debug_stream ();
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  CfdgParser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  CfdgParser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 26: /* USER_STRING */
/* Line 453 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).string); };
/* Line 453 of lalr1.cc  */
#line 248 "cfdg.tab.cpp"
	break;
      case 29: /* USER_FILENAME */
/* Line 453 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).string); };
/* Line 453 of lalr1.cc  */
#line 255 "cfdg.tab.cpp"
	break;
      case 30: /* USER_QSTRING */
/* Line 453 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).string); };
/* Line 453 of lalr1.cc  */
#line 262 "cfdg.tab.cpp"
	break;
      case 31: /* USER_ARRAYNAME */
/* Line 453 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).string); };
/* Line 453 of lalr1.cc  */
#line 269 "cfdg.tab.cpp"
	break;
      case 36: /* USER_PATHOP */
/* Line 453 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).string); };
/* Line 453 of lalr1.cc  */
#line 276 "cfdg.tab.cpp"
	break;
      case 72: /* statement */
/* Line 453 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 283 "cfdg.tab.cpp"
	break;
      case 73: /* statement_v2 */
/* Line 453 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 290 "cfdg.tab.cpp"
	break;
      case 79: /* fileString */
/* Line 453 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).string); };
/* Line 453 of lalr1.cc  */
#line 297 "cfdg.tab.cpp"
	break;
      case 80: /* fileNameSpace */
/* Line 453 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).string); };
/* Line 453 of lalr1.cc  */
#line 304 "cfdg.tab.cpp"
	break;
      case 81: /* initialization */
/* Line 453 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 311 "cfdg.tab.cpp"
	break;
      case 82: /* initialization_v2 */
/* Line 453 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 318 "cfdg.tab.cpp"
	break;
      case 83: /* background */
/* Line 453 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 325 "cfdg.tab.cpp"
	break;
      case 84: /* tile */
/* Line 453 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 332 "cfdg.tab.cpp"
	break;
      case 85: /* size */
/* Line 453 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 339 "cfdg.tab.cpp"
	break;
      case 87: /* global_definition_header */
/* Line 453 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).string); };
/* Line 453 of lalr1.cc  */
#line 346 "cfdg.tab.cpp"
	break;
      case 88: /* definition_header */
/* Line 453 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).string); };
/* Line 453 of lalr1.cc  */
#line 353 "cfdg.tab.cpp"
	break;
      case 90: /* shape */
/* Line 453 of lalr1.cc  */
#line 173 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).shapeObj); };
/* Line 453 of lalr1.cc  */
#line 360 "cfdg.tab.cpp"
	break;
      case 91: /* shape_singleton_header */
/* Line 453 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete ((*yyvaluep).ruleObj); };
/* Line 453 of lalr1.cc  */
#line 367 "cfdg.tab.cpp"
	break;
      case 92: /* shape_singleton */
/* Line 453 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 374 "cfdg.tab.cpp"
	break;
      case 93: /* rule_header_v2 */
/* Line 453 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete ((*yyvaluep).ruleObj); };
/* Line 453 of lalr1.cc  */
#line 381 "cfdg.tab.cpp"
	break;
      case 95: /* rule_header */
/* Line 453 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete ((*yyvaluep).ruleObj); };
/* Line 453 of lalr1.cc  */
#line 388 "cfdg.tab.cpp"
	break;
      case 96: /* path_header */
/* Line 453 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete ((*yyvaluep).ruleObj); };
/* Line 453 of lalr1.cc  */
#line 395 "cfdg.tab.cpp"
	break;
      case 97: /* rule */
/* Line 453 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 402 "cfdg.tab.cpp"
	break;
      case 98: /* path */
/* Line 453 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 409 "cfdg.tab.cpp"
	break;
      case 99: /* path_header_v2 */
/* Line 453 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete ((*yyvaluep).ruleObj); };
/* Line 453 of lalr1.cc  */
#line 416 "cfdg.tab.cpp"
	break;
      case 105: /* parameter_spec */
/* Line 453 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).expression); };
/* Line 453 of lalr1.cc  */
#line 423 "cfdg.tab.cpp"
	break;
      case 108: /* pathOp_simple_v2 */
/* Line 453 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 430 "cfdg.tab.cpp"
	break;
      case 109: /* element_simple */
/* Line 453 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 437 "cfdg.tab.cpp"
	break;
      case 114: /* element */
/* Line 453 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 444 "cfdg.tab.cpp"
	break;
      case 117: /* pathOp_v2 */
/* Line 453 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 451 "cfdg.tab.cpp"
	break;
      case 119: /* element_loop */
/* Line 453 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete ((*yyvaluep).loopObj); };
/* Line 453 of lalr1.cc  */
#line 458 "cfdg.tab.cpp"
	break;
      case 122: /* replacement_simple_v2 */
/* Line 453 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 465 "cfdg.tab.cpp"
	break;
      case 123: /* replacement_v2 */
/* Line 453 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 472 "cfdg.tab.cpp"
	break;
      case 124: /* loopHeader_v2 */
/* Line 453 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete ((*yyvaluep).loopObj); };
/* Line 453 of lalr1.cc  */
#line 479 "cfdg.tab.cpp"
	break;
      case 126: /* loopHeader */
/* Line 453 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete ((*yyvaluep).loopObj); };
/* Line 453 of lalr1.cc  */
#line 486 "cfdg.tab.cpp"
	break;
      case 127: /* ifHeader */
/* Line 453 of lalr1.cc  */
#line 171 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete ((*yyvaluep).ifObj); };
/* Line 453 of lalr1.cc  */
#line 493 "cfdg.tab.cpp"
	break;
      case 128: /* ifElseHeader */
/* Line 453 of lalr1.cc  */
#line 171 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete ((*yyvaluep).ifObj); };
/* Line 453 of lalr1.cc  */
#line 500 "cfdg.tab.cpp"
	break;
      case 129: /* transHeader */
/* Line 453 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete ((*yyvaluep).component); };
/* Line 453 of lalr1.cc  */
#line 507 "cfdg.tab.cpp"
	break;
      case 130: /* switchHeader */
/* Line 453 of lalr1.cc  */
#line 172 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).switchObj); };
/* Line 453 of lalr1.cc  */
#line 514 "cfdg.tab.cpp"
	break;
      case 131: /* caseHeader */
/* Line 453 of lalr1.cc  */
#line 174 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); };
/* Line 453 of lalr1.cc  */
#line 521 "cfdg.tab.cpp"
	break;
      case 132: /* modification_v2 */
/* Line 453 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).mod); };
/* Line 453 of lalr1.cc  */
#line 528 "cfdg.tab.cpp"
	break;
      case 133: /* modification */
/* Line 453 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).mod); };
/* Line 453 of lalr1.cc  */
#line 535 "cfdg.tab.cpp"
	break;
      case 134: /* buncha_adjustments */
/* Line 453 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).mod); };
/* Line 453 of lalr1.cc  */
#line 542 "cfdg.tab.cpp"
	break;
      case 135: /* adjustment */
/* Line 453 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).term); };
/* Line 453 of lalr1.cc  */
#line 549 "cfdg.tab.cpp"
	break;
      case 136: /* letHeader */
/* Line 453 of lalr1.cc  */
#line 175 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete ((*yyvaluep).bodyObj); };
/* Line 453 of lalr1.cc  */
#line 556 "cfdg.tab.cpp"
	break;
      case 137: /* letBody */
/* Line 453 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).expression); };
/* Line 453 of lalr1.cc  */
#line 563 "cfdg.tab.cpp"
	break;
      case 140: /* explist */
/* Line 453 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).expression); };
/* Line 453 of lalr1.cc  */
#line 570 "cfdg.tab.cpp"
	break;
      case 141: /* arglist */
/* Line 453 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).expression); };
/* Line 453 of lalr1.cc  */
#line 577 "cfdg.tab.cpp"
	break;
      case 142: /* exp */
/* Line 453 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).expression); };
/* Line 453 of lalr1.cc  */
#line 584 "cfdg.tab.cpp"
	break;
      case 143: /* exp2 */
/* Line 453 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).expression); };
/* Line 453 of lalr1.cc  */
#line 591 "cfdg.tab.cpp"
	break;
      case 144: /* exp3 */
/* Line 453 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).expression); };
/* Line 453 of lalr1.cc  */
#line 598 "cfdg.tab.cpp"
	break;
      case 145: /* expfunc */
/* Line 453 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).expression); };
/* Line 453 of lalr1.cc  */
#line 605 "cfdg.tab.cpp"
	break;
      case 146: /* exp2func */
/* Line 453 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).expression); };
/* Line 453 of lalr1.cc  */
#line 612 "cfdg.tab.cpp"
	break;
      case 147: /* shapeName */
/* Line 453 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete ((*yyvaluep).string); };
/* Line 453 of lalr1.cc  */
#line 619 "cfdg.tab.cpp"
	break;

	default:
	  break;
      }
  }

  void
  CfdgParser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
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
#endif

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
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc, driver);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
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

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 4:
/* Line 661 of lalr1.cc  */
#line 192 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 6:
/* Line 661 of lalr1.cc  */
#line 201 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 9:
/* Line 661 of lalr1.cc  */
#line 211 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 10:
/* Line 661 of lalr1.cc  */
#line 212 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 13:
/* Line 661 of lalr1.cc  */
#line 215 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].shapeObj); }
    break;

  case 15:
/* Line 661 of lalr1.cc  */
#line 217 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 16:
/* Line 661 of lalr1.cc  */
#line 218 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 19:
/* Line 661 of lalr1.cc  */
#line 227 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 20:
/* Line 661 of lalr1.cc  */
#line 228 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 25:
/* Line 661 of lalr1.cc  */
#line 233 "../../src-common/cfdg.ypp"
    {
            if (driver.lexer->maybeVersion == token::CFDG2) {
                error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            } else {
                driver.lexer->maybeVersion = token::CFDG3;
            }
            (yyval.component) = 0;
            YYABORT;
        }
    break;

  case 26:
/* Line 661 of lalr1.cc  */
#line 245 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 27:
/* Line 661 of lalr1.cc  */
#line 246 "../../src-common/cfdg.ypp"
    {}
    break;

  case 28:
/* Line 661 of lalr1.cc  */
#line 247 "../../src-common/cfdg.ypp"
    {}
    break;

  case 29:
/* Line 661 of lalr1.cc  */
#line 248 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 30:
/* Line 661 of lalr1.cc  */
#line 249 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (1)].string); delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 33:
/* Line 661 of lalr1.cc  */
#line 252 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 34:
/* Line 661 of lalr1.cc  */
#line 253 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 35:
/* Line 661 of lalr1.cc  */
#line 254 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 36:
/* Line 661 of lalr1.cc  */
#line 255 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 37:
/* Line 661 of lalr1.cc  */
#line 259 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 38:
/* Line 661 of lalr1.cc  */
#line 260 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 39:
/* Line 661 of lalr1.cc  */
#line 261 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 40:
/* Line 661 of lalr1.cc  */
#line 262 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 41:
/* Line 661 of lalr1.cc  */
#line 263 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(1) - (1)].ruleObj); }
    break;

  case 42:
/* Line 661 of lalr1.cc  */
#line 267 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(2) - (2)].string));
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(NULL);
            driver.IncludeFile(*file);
        }
    break;

  case 43:
/* Line 661 of lalr1.cc  */
#line 276 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(3) - (3)].string));
            str_ptr nm((yysemantic_stack_[(3) - (2)].string));
            driver.SetShape(NULL);
            driver.IncludeFile(*file);
            if (nm.get())
                driver.PushNameSpace(nm, (yylocation_stack_[(3) - (2)]));
        }
    break;

  case 44:
/* Line 661 of lalr1.cc  */
#line 287 "../../src-common/cfdg.ypp"
    {
            if (driver.EndInclude())
                YYACCEPT;
        }
    break;

  case 47:
/* Line 661 of lalr1.cc  */
#line 297 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 48:
/* Line 661 of lalr1.cc  */
#line 298 "../../src-common/cfdg.ypp"
    { (yyval.string) = NULL; }
    break;

  case 49:
/* Line 661 of lalr1.cc  */
#line 302 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(4) - (2)].string));
            exp_ptr p((yysemantic_stack_[(4) - (3)].expression));
            mod_ptr mod((yysemantic_stack_[(4) - (4)].mod));
            driver.SetShape(NULL);
            if (driver.mCompilePhase == 2) {
                ruleSpec_ptr r(driver.MakeRuleSpec(*name, p, (yylocation_stack_[(4) - (2)])));
                rep_ptr start(new ASTreplacement(*r, *name, mod, (yyloc)));
                driver.Initialize(start);
            }
            (yyval.component) = 0;
        }
    break;

  case 50:
/* Line 661 of lalr1.cc  */
#line 315 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(3) - (2)].string));
            mod_ptr mod((yysemantic_stack_[(3) - (3)].mod));
            driver.SetShape(NULL);
            if (driver.mCompilePhase == 2) {
                ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), (yylocation_stack_[(3) - (2)])));
                rep_ptr start(new ASTreplacement(*r, *name, mod, (yyloc)));
                driver.Initialize(start);
            }
            (yyval.component) = 0;
        }
    break;

  case 51:
/* Line 661 of lalr1.cc  */
#line 327 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(3) - (2)].string));
            exp_ptr p((yysemantic_stack_[(3) - (3)].expression));
            driver.SetShape(NULL);
            if (driver.mCompilePhase == 2) {
                ruleSpec_ptr r(driver.MakeRuleSpec(*name, p, (yylocation_stack_[(3) - (2)])));
                rep_ptr start(new ASTreplacement(*r, *name, mod_ptr(), (yyloc)));
                driver.Initialize(start);
            }
            (yyval.component) = 0;
        }
    break;

  case 52:
/* Line 661 of lalr1.cc  */
#line 341 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (2)].string));
            driver.SetShape(NULL);
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), (yylocation_stack_[(2) - (2)])));
            rep_ptr start(new ASTreplacement(*r, *name, mod_ptr(), (yyloc)));
            driver.Initialize(start);
            (yyval.component) = 0;
        }
    break;

  case 53:
/* Line 661 of lalr1.cc  */
#line 352 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            static const std::string backVar("CF::Background");
            driver.lexer->maybeVersion = token::CFDG2;
            driver.NextParameter(backVar, mod, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
            (yyval.component) = 0;
        }
    break;

  case 54:
/* Line 661 of lalr1.cc  */
#line 362 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            static const std::string tileVar("CF::Tile");
            driver.lexer->maybeVersion = token::CFDG2;
            driver.NextParameter(tileVar, mod, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
            (yyval.component) = 0;
        }
    break;

  case 55:
/* Line 661 of lalr1.cc  */
#line 372 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            driver.lexer->maybeVersion = token::CFDG2;
            if ((yysemantic_stack_[(2) - (1)].modToken) != ASTmodTerm::size && (yysemantic_stack_[(2) - (1)].modToken) != ASTmodTerm::time) {
                error((yylocation_stack_[(2) - (1)]), "Syntax error");
            } else {
                static const std::string sizeVar("CF::Size");
                static const std::string timeVar("CF::Time");
                driver.NextParameter((yysemantic_stack_[(2) - (1)].modToken) == ASTmodTerm::size ? sizeVar : timeVar, mod, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
            }
            (yyval.component) = 0;
        }
    break;

  case 56:
/* Line 661 of lalr1.cc  */
#line 387 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(2) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            if (var.get())
                driver.NextParameter(*var, exp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 57:
/* Line 661 of lalr1.cc  */
#line 396 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("shape");
            driver.push_paramDecls(*(yysemantic_stack_[(4) - (2)].string), (yyloc), numtype);
            (yyval.string) = (yysemantic_stack_[(4) - (2)].string);
        }
    break;

  case 58:
/* Line 661 of lalr1.cc  */
#line 402 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("number");
            driver.push_paramDecls(*(yysemantic_stack_[(3) - (1)].string), (yyloc), numtype);
            (yyval.string) = (yysemantic_stack_[(3) - (1)].string);
        }
    break;

  case 59:
/* Line 661 of lalr1.cc  */
#line 408 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(4) - (1)].string));
            driver.push_paramDecls(*(yysemantic_stack_[(4) - (2)].string), (yyloc), *type);
            (yyval.string) = (yysemantic_stack_[(4) - (2)].string);
        }
    break;

  case 60:
/* Line 661 of lalr1.cc  */
#line 414 "../../src-common/cfdg.ypp"
    {
            (yyval.string) = (yysemantic_stack_[(2) - (1)].string);
        }
    break;

  case 61:
/* Line 661 of lalr1.cc  */
#line 418 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(4) - (2)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 62:
/* Line 661 of lalr1.cc  */
#line 423 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(3) - (1)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 63:
/* Line 661 of lalr1.cc  */
#line 428 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(4) - (1)].string));
            error((yylocation_stack_[(4) - (2)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 64:
/* Line 661 of lalr1.cc  */
#line 434 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (1)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 65:
/* Line 661 of lalr1.cc  */
#line 441 "../../src-common/cfdg.ypp"
    {
            (yyval.string) = (yysemantic_stack_[(2) - (1)].string);
        }
    break;

  case 66:
/* Line 661 of lalr1.cc  */
#line 444 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (1)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 67:
/* Line 661 of lalr1.cc  */
#line 451 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(2) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            if (var.get() && driver.mCompilePhase == 2)
                driver.NextParameter(*var, exp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 68:
/* Line 661 of lalr1.cc  */
#line 460 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(3) - (2)].string));
            bool hasParams = !driver.mParamDecls.mParameters.empty();
            exp_ptr dummy(hasParams ? new ASTexpression((yylocation_stack_[(3) - (2)])) : NULL);
            ASTruleSpecifier r(driver.StringToShape(*name, (yylocation_stack_[(3) - (2)]), false), *name, dummy,
                               (yyloc), &(driver.mParamDecls.mParameters),
                               &(driver.mParamDecls.mParameters));
            ASTshape* s = new ASTshape(r, false, (yylocation_stack_[(3) - (1)]) + (yylocation_stack_[(3) - (2)]));
            s->mRules.mParameters.swap(driver.mParamDecls.mParameters);
            driver.SetShape(s);
            s->mShapeSpec.typeSignature = hasParams ? &(s->mRules.mParameters) : NULL;
            (yyval.shapeObj) = s;
        }
    break;

  case 69:
/* Line 661 of lalr1.cc  */
#line 476 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (1)].shapeObj), true);
            if (driver.mCompilePhase == 2) {
                driver.mInPathContainer = false;
                rule_ptr rule(new ASTrule(-1, (yylocation_stack_[(2) - (1)])));
                driver.AddRule(rule.get());
                driver.push_repContainer(rule->mRuleBody);
                (yyval.ruleObj) = rule.release();
            } else {
                (yyval.ruleObj) = 0;
            }
        }
    break;

  case 70:
/* Line 661 of lalr1.cc  */
#line 490 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(3) - (1)].ruleObj);
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 71:
/* Line 661 of lalr1.cc  */
#line 499 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (2)].string));
            driver.SetShape(NULL);
            rule_ptr rule(new ASTrule(driver.StringToShape(*name, (yylocation_stack_[(2) - (2)]), false), (yyloc)));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
        }
    break;

  case 72:
/* Line 661 of lalr1.cc  */
#line 508 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(3) - (2)].string));
            str_ptr weight((yysemantic_stack_[(3) - (3)].string));
            driver.SetShape(NULL);
            rule_ptr rule(new ASTrule(driver.StringToShape(*name, (yylocation_stack_[(3) - (2)]), false), 
                                      CFatof(weight->c_str()), 
                                      weight->find_first_of('%')  != std::string::npos,
                                      (yyloc)));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
        }
    break;

  case 73:
/* Line 661 of lalr1.cc  */
#line 523 "../../src-common/cfdg.ypp"
    {
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 74:
/* Line 661 of lalr1.cc  */
#line 531 "../../src-common/cfdg.ypp"
    {
            driver.mInPathContainer = false;
            if (driver.mCompilePhase == 2) {
                rule_ptr rule(new ASTrule(-1, (yylocation_stack_[(1) - (1)])));
                driver.AddRule(rule.get());
                driver.push_repContainer(rule->mRuleBody);
                (yyval.ruleObj) = rule.release();
            } else {
                (yyval.ruleObj) = 0;
            }
        }
    break;

  case 75:
/* Line 661 of lalr1.cc  */
#line 543 "../../src-common/cfdg.ypp"
    {
            driver.mInPathContainer = false;
            str_ptr weight((yysemantic_stack_[(2) - (2)].string));
            if (driver.mCompilePhase == 2) {
                rule_ptr rule(new ASTrule(-1, CFatof(weight->c_str()), 
                                          weight->find_first_of('%')  != std::string::npos,
                                          (yyloc)));
                driver.AddRule(rule.get());
                driver.push_repContainer(rule->mRuleBody);
                (yyval.ruleObj) = rule.release();
            } else {
                (yyval.ruleObj) = 0;
            }
        }
    break;

  case 76:
/* Line 661 of lalr1.cc  */
#line 560 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(3) - (2)].string));
            bool hasParams = !driver.mParamDecls.mParameters.empty();
            exp_ptr dummy(hasParams ? new ASTexpression((yylocation_stack_[(3) - (2)])) : NULL);
            ASTruleSpecifier r(driver.StringToShape(*name, (yylocation_stack_[(3) - (2)]), false), *name, dummy,
                               (yyloc), &(driver.mParamDecls.mParameters),
                               &(driver.mParamDecls.mParameters));
            ASTshape* s = new ASTshape(r, false, (yylocation_stack_[(3) - (1)]) + (yylocation_stack_[(3) - (2)]));
            s->mRules.mParameters.swap(driver.mParamDecls.mParameters);
            driver.SetShape(s, true);
            s->mShapeSpec.typeSignature = hasParams ? &(s->mRules.mParameters) : NULL;
            driver.mInPathContainer = true;
            if (driver.mCompilePhase == 2) {
                rule_ptr newPath(new ASTrule(-1, (yyloc)));
                newPath->isPath = true;
                driver.AddRule(newPath.get());
                driver.push_repContainer(newPath->mRuleBody);
                (yyval.ruleObj) = newPath.release();
            } else {
                (yyval.ruleObj) = 0;
            }
        }
    break;

  case 77:
/* Line 661 of lalr1.cc  */
#line 585 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 78:
/* Line 661 of lalr1.cc  */
#line 594 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
            driver.SetShape(NULL);
        }
    break;

  case 79:
/* Line 661 of lalr1.cc  */
#line 604 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (2)].string));
            driver.SetShape(NULL);
            rule_ptr newPath(new ASTrule(driver.StringToShape(*(yysemantic_stack_[(2) - (2)].string), (yylocation_stack_[(2) - (2)]), false), (yyloc)));
            newPath->isPath = true;
            driver.AddRule(newPath.get());
            driver.push_repContainer(newPath->mRuleBody);
            driver.mInPathContainer = true;
            (yyval.ruleObj) = newPath.release();
        }
    break;

  case 80:
/* Line 661 of lalr1.cc  */
#line 617 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 81:
/* Line 661 of lalr1.cc  */
#line 624 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(2) - (1)].string));
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(*type, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 82:
/* Line 661 of lalr1.cc  */
#line 630 "../../src-common/cfdg.ypp"
    {
            static std::string shapeStr("shape");
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(shapeStr, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 83:
/* Line 661 of lalr1.cc  */
#line 636 "../../src-common/cfdg.ypp"
    {
            delete (yysemantic_stack_[(2) - (1)].string);
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 84:
/* Line 661 of lalr1.cc  */
#line 641 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 85:
/* Line 661 of lalr1.cc  */
#line 645 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("number");
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            driver.NextParameterDecl(numtype, *var, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 86:
/* Line 661 of lalr1.cc  */
#line 651 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Reserved keyword: adjustment");
        }
    break;

  case 93:
/* Line 661 of lalr1.cc  */
#line 672 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(3) - (2)].expression);}
    break;

  case 94:
/* Line 661 of lalr1.cc  */
#line 673 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTexpression((yyloc)); }
    break;

  case 95:
/* Line 661 of lalr1.cc  */
#line 674 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 96:
/* Line 661 of lalr1.cc  */
#line 675 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 97:
/* Line 661 of lalr1.cc  */
#line 679 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 1)
                assert ((yysemantic_stack_[(2) - (2)].component) == 0);
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 99:
/* Line 661 of lalr1.cc  */
#line 688 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 101:
/* Line 661 of lalr1.cc  */
#line 695 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(4) - (3)].mod));
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = new ASTpathOp(*pop, mod, (yyloc));
        }
    break;

  case 102:
/* Line 661 of lalr1.cc  */
#line 702 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(2) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            driver.lexer->maybeVersion = token::CFDG2;
            rep_ptr item(new ASTpathCommand(*cmd, mod, (yyloc)));
            (yyval.component) = item.release();
        }
    break;

  case 103:
/* Line 661 of lalr1.cc  */
#line 712 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string));
            exp_ptr mod((yysemantic_stack_[(4) - (3)].expression));
            if (driver.mCompilePhase == 2)
                (yyval.component) = new ASTpathOp(*pop, mod, (yyloc));
            else
                (yyval.component) = 0;
        }
    break;

  case 104:
/* Line 661 of lalr1.cc  */
#line 721 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(3) - (1)].string));
            exp_ptr mod;
            if (driver.mCompilePhase == 2)
                (yyval.component) = new ASTpathOp(*pop, mod, (yyloc));
            else
                (yyval.component) = 0;
        }
    break;

  case 105:
/* Line 661 of lalr1.cc  */
#line 730 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(3) - (1)].string));
            exp_ptr p((yysemantic_stack_[(3) - (2)].expression));
            mod_ptr mod((yysemantic_stack_[(3) - (3)].mod));
            if (driver.mCompilePhase == 2) {
                rep_ptr item = driver.MakeElement(*cmd, mod, p, (yyloc), false);
                (yyval.component) = item.release();
            } else {
                (yyval.component) = 0;
            }
        }
    break;

  case 106:
/* Line 661 of lalr1.cc  */
#line 742 "../../src-common/cfdg.ypp"
    { 
            exp_ptr args((yysemantic_stack_[(5) - (3)].expression));
            mod_ptr mod((yysemantic_stack_[(5) - (5)].mod));
            if (driver.mCompilePhase == 2) {
                str_ptr func(new std::string("if"));
                args.reset(driver.MakeFunction(func, args, (yylocation_stack_[(5) - (1)]), (yylocation_stack_[(5) - (3)]), false));
                static const std::string ifstr("if");
                rep_ptr item = driver.MakeElement(ifstr, mod, args, (yyloc), false);
                (yyval.component) = item.release();
            } else {
                (yyval.component) = 0;
            }
        }
    break;

  case 107:
/* Line 661 of lalr1.cc  */
#line 756 "../../src-common/cfdg.ypp"
    {
            std::auto_ptr<ASTrepContainer> vars((yysemantic_stack_[(3) - (1)].bodyObj));
            exp_ptr exp((yysemantic_stack_[(3) - (2)].expression));
            mod_ptr mod((yysemantic_stack_[(3) - (3)].mod));
            exp.reset(driver.MakeLet((yylocation_stack_[(3) - (1)]), exp));     // must do unconditionally
            if (driver.mCompilePhase == 2) {
                static const std::string letstr("let");
                rep_ptr item = driver.MakeElement(letstr, mod, exp, (yyloc), false);
                (yyval.component) = item.release();
            } else {
                (yyval.component) = 0;
            }
        }
    break;

  case 108:
/* Line 661 of lalr1.cc  */
#line 770 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(4) - (2)].string));
            exp_ptr p((yysemantic_stack_[(4) - (3)].expression));
            mod_ptr mod((yysemantic_stack_[(4) - (4)].mod));
            if (driver.mCompilePhase == 2) {
                rep_ptr item = driver.MakeElement(*cmd, mod, p, (yyloc), true);
                (yyval.component) = item.release();
            } else {
                (yyval.component) = 0;
            }
        }
    break;

  case 109:
/* Line 661 of lalr1.cc  */
#line 784 "../../src-common/cfdg.ypp"
    { }
    break;

  case 110:
/* Line 661 of lalr1.cc  */
#line 786 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 1)
                assert((yysemantic_stack_[(1) - (1)].component) == 0);
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 111:
/* Line 661 of lalr1.cc  */
#line 794 "../../src-common/cfdg.ypp"
    { }
    break;

  case 112:
/* Line 661 of lalr1.cc  */
#line 796 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 113:
/* Line 661 of lalr1.cc  */
#line 802 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer(driver.switchStack.top());
        }
    break;

  case 116:
/* Line 661 of lalr1.cc  */
#line 814 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(1) - (1)].component); 
        }
    break;

  case 117:
/* Line 661 of lalr1.cc  */
#line 818 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = 0; 
        }
    break;

  case 118:
/* Line 661 of lalr1.cc  */
#line 822 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(1) - (1)].loopObj); 
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yysemantic_stack_[(1) - (1)].loopObj));
                if ((yysemantic_stack_[(1) - (1)].loopObj)->mRepType == 0) {
                    delete (yysemantic_stack_[(1) - (1)].loopObj);
                    (yyval.component) = 0;
                }
            }
        }
    break;

  case 119:
/* Line 661 of lalr1.cc  */
#line 833 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
                driver.push_repContainer((yysemantic_stack_[(2) - (1)].loopObj)->mFinallyBody);
            }
        }
    break;

  case 120:
/* Line 661 of lalr1.cc  */
#line 838 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yysemantic_stack_[(4) - (1)].loopObj));
                (yyval.component) = (yysemantic_stack_[(4) - (1)].loopObj);
                if ((yysemantic_stack_[(4) - (1)].loopObj)->mRepType == 0) {
                    delete (yysemantic_stack_[(4) - (1)].loopObj);
                    (yyval.component) = 0;
                }
            } else {
                (yyval.component) = 0;
            }
        }
    break;

  case 121:
/* Line 661 of lalr1.cc  */
#line 851 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].ifObj);
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yysemantic_stack_[(2) - (1)].ifObj));
                if ((yysemantic_stack_[(2) - (1)].ifObj)->mRepType == 0) {
                    delete (yysemantic_stack_[(2) - (1)].ifObj);
                    (yyval.component) = 0;
                }
            }
        }
    break;

  case 122:
/* Line 661 of lalr1.cc  */
#line 862 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].ifObj);
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yysemantic_stack_[(2) - (1)].ifObj));
                if ((yysemantic_stack_[(2) - (1)].ifObj)->mRepType == 0) {
                    delete (yysemantic_stack_[(2) - (1)].ifObj);
                    (yyval.component) = 0;
                }
            }
        }
    break;

  case 123:
/* Line 661 of lalr1.cc  */
#line 873 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].component);
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yysemantic_stack_[(2) - (1)].component));
                if ((yysemantic_stack_[(2) - (1)].component)->mRepType == 0) {
                    delete (yysemantic_stack_[(2) - (1)].component);
                    (yyval.component) = 0;
                }
            }
        }
    break;

  case 124:
/* Line 661 of lalr1.cc  */
#line 885 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].switchObj);
            if (driver.mCompilePhase == 2) {
                (yysemantic_stack_[(4) - (1)].switchObj)->unify();
                driver.switchStack.pop();
            }
        }
    break;

  case 125:
/* Line 661 of lalr1.cc  */
#line 893 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 126:
/* Line 661 of lalr1.cc  */
#line 900 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 127:
/* Line 661 of lalr1.cc  */
#line 901 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 128:
/* Line 661 of lalr1.cc  */
#line 902 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 129:
/* Line 661 of lalr1.cc  */
#line 906 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 130:
/* Line 661 of lalr1.cc  */
#line 908 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(2) - (1)].loopObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            if ((yysemantic_stack_[(2) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].loopObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 131:
/* Line 661 of lalr1.cc  */
#line 916 "../../src-common/cfdg.ypp"
    {
            if (driver.lexer->maybeVersion == token::CFDG2) {
                error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            } else {
                driver.lexer->maybeVersion = token::CFDG3;
            }
            (yyval.component) = 0;
            YYABORT;
        }
    break;

  case 132:
/* Line 661 of lalr1.cc  */
#line 928 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 133:
/* Line 661 of lalr1.cc  */
#line 929 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 136:
/* Line 661 of lalr1.cc  */
#line 932 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 141:
/* Line 661 of lalr1.cc  */
#line 940 "../../src-common/cfdg.ypp"
    {
            // parse loop mod and loop body with loop index in scope
            mod_ptr loopmod((yysemantic_stack_[(3) - (2)].mod));
            if (driver.mCompilePhase == 2)
                (yysemantic_stack_[(3) - (1)].loopObj)->mChildChange.grab(loopmod.get());
            (yyval.loopObj) = (yysemantic_stack_[(3) - (1)].loopObj);
            // loopmod gets deleted
        }
    break;

  case 142:
/* Line 661 of lalr1.cc  */
#line 951 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 144:
/* Line 661 of lalr1.cc  */
#line 958 "../../src-common/cfdg.ypp"
    { }
    break;

  case 145:
/* Line 661 of lalr1.cc  */
#line 960 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 146:
/* Line 661 of lalr1.cc  */
#line 966 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), (yylocation_stack_[(2) - (1)])));
            (yyval.component) = new ASTreplacement(*r, r->entropyVal, mod, (yyloc));
        }
    break;

  case 147:
/* Line 661 of lalr1.cc  */
#line 975 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 148:
/* Line 661 of lalr1.cc  */
#line 977 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].loopObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            if ((yysemantic_stack_[(2) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].loopObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 149:
/* Line 661 of lalr1.cc  */
#line 988 "../../src-common/cfdg.ypp"
    { ++driver.mLocalStackDepth; }
    break;

  case 150:
/* Line 661 of lalr1.cc  */
#line 988 "../../src-common/cfdg.ypp"
    {
            str_ptr cstr((yysemantic_stack_[(4) - (1)].string));
            exp_ptr count(new ASTreal(*cstr, (yylocation_stack_[(4) - (1)])));
            mod_ptr mod((yysemantic_stack_[(4) - (4)].mod));
            static const std::string dummyvar("~~inaccessiblevar~~");
            --driver.mLocalStackDepth;
            driver.lexer->maybeVersion = token::CFDG2;
            loop_ptr loop(new ASTloop(driver.StringToShape(dummyvar, (yylocation_stack_[(4) - (2)]), false), 
                                      dummyvar, (yylocation_stack_[(4) - (2)]), count, (yyloc), mod));
            driver.push_repContainer(loop->mLoopBody);
            (yyval.loopObj) = loop.release();
        }
    break;

  case 151:
/* Line 661 of lalr1.cc  */
#line 1003 "../../src-common/cfdg.ypp"
    {
            str_ptr var((yysemantic_stack_[(4) - (2)].string));
            exp_ptr index((yysemantic_stack_[(4) - (4)].expression));
            if (driver.mCompilePhase == 2) {
                int nameIndex = driver.StringToShape(*var, (yylocation_stack_[(4) - (2)]), false);
                loop_ptr loop(new ASTloop(nameIndex, *var, (yylocation_stack_[(4) - (2)]), index, (yylocation_stack_[(4) - (4)]), mod_ptr()));
                driver.push_repContainer(loop->mLoopBody);
                (yyval.loopObj) = loop.release();
            } else {
                (yyval.loopObj) = 0;
            }
        }
    break;

  case 152:
/* Line 661 of lalr1.cc  */
#line 1016 "../../src-common/cfdg.ypp"
    {
            exp_ptr index((yysemantic_stack_[(4) - (4)].expression));
            if (driver.mCompilePhase == 2) {
                static const std::string dummyvar("~~inaccessiblevar~~");
                loop_ptr loop(new ASTloop(driver.StringToShape(dummyvar, (yylocation_stack_[(4) - (1)]), false), 
                                          dummyvar, (yylocation_stack_[(4) - (2)]), index, (yylocation_stack_[(4) - (4)]), mod_ptr()));
                driver.push_repContainer(loop->mLoopBody);
                (yyval.loopObj) = loop.release();
            } else {
                (yyval.loopObj) = 0;
            }
            error((yylocation_stack_[(4) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 153:
/* Line 661 of lalr1.cc  */
#line 1030 "../../src-common/cfdg.ypp"
    {
            exp_ptr count((yysemantic_stack_[(2) - (2)].expression));
            if (driver.mCompilePhase == 2) {
                static const std::string dummyvar("~~inaccessiblevar~~");
                loop_ptr loop(new ASTloop(driver.StringToShape(dummyvar, (yylocation_stack_[(2) - (1)]), false), 
                                          dummyvar, (yylocation_stack_[(2) - (1)]), count, (yylocation_stack_[(2) - (2)]), mod_ptr()));
                driver.push_repContainer(loop->mLoopBody);
                (yyval.loopObj) = loop.release();
            } else {
                (yyval.loopObj) = 0;
            }
        }
    break;

  case 154:
/* Line 661 of lalr1.cc  */
#line 1045 "../../src-common/cfdg.ypp"
    {
            exp_ptr cond((yysemantic_stack_[(4) - (3)].expression));
            if (driver.mCompilePhase == 2) {
                if_ptr ifHeader(new ASTif(cond, (yylocation_stack_[(4) - (3)])));
                driver.push_repContainer(ifHeader->mThenBody);
                (yyval.ifObj) = ifHeader.release();
            } else {
                (yyval.ifObj) = 0;
            }
        }
    break;

  case 155:
/* Line 661 of lalr1.cc  */
#line 1058 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ifObj));
                driver.push_repContainer((yysemantic_stack_[(3) - (1)].ifObj)->mElseBody);
            }
            (yyval.ifObj) = (yysemantic_stack_[(3) - (1)].ifObj);
        }
    break;

  case 156:
/* Line 661 of lalr1.cc  */
#line 1068 "../../src-common/cfdg.ypp"
    {
            exp_ptr mods((yysemantic_stack_[(2) - (2)].expression));
            if ((yysemantic_stack_[(2) - (1)].modToken) != ASTmodTerm::transform)
                error((yylocation_stack_[(2) - (1)]), "Syntax error");
            if (driver.mCompilePhase == 2) {
                ASTtransform* trans = new ASTtransform((yyloc), mods);
                driver.push_repContainer(trans->mBody);
                (yyval.component) = trans;
            } else {
                (yyval.component) = 0;
            }
        }
    break;

  case 157:
/* Line 661 of lalr1.cc  */
#line 1080 "../../src-common/cfdg.ypp"
    {
            exp_ptr mods((yysemantic_stack_[(2) - (2)].expression));
            if (!ASTparameter::Impure)
                error((yylocation_stack_[(2) - (1)]), "shape cloning only permitted in impure mode");
            if (driver.mCompilePhase == 2) {
                ASTtransform* trans = new ASTtransform((yyloc), mods);
                trans->mClone = true;
                driver.push_repContainer(trans->mBody);
                (yyval.component) = trans;
            } else {
                (yyval.component) = 0;
            }
        }
    break;

  case 158:
/* Line 661 of lalr1.cc  */
#line 1096 "../../src-common/cfdg.ypp"
    {
            exp_ptr caseVal((yysemantic_stack_[(4) - (3)].expression));
            if (driver.mCompilePhase == 2) {
                switch_ptr switchHeader(new ASTswitch(caseVal, (yylocation_stack_[(4) - (3)])));
                driver.switchStack.push(switchHeader.get());
                (yyval.switchObj) = switchHeader.release();
            } else {
                (yyval.switchObj) = 0;
            }
        }
    break;

  case 159:
/* Line 661 of lalr1.cc  */
#line 1109 "../../src-common/cfdg.ypp"
    {
            exp_ptr valExp((yysemantic_stack_[(3) - (2)].expression));
            
            if (driver.mCompilePhase == 2) {
                double val = 0.0;
                try {
                    if (valExp->evaluate(&val, 1) != 1) {
                        driver.error((yylocation_stack_[(3) - (2)]), "Case expression is not a single, numeric expression");
                    } else {
                        int intval = (int)floor(val);
                        ASTswitch::switchMap& caseMap = driver.switchStack.top()->mCaseStatements;
                        
                        if (caseMap.count(intval)) {
                            driver.error((yylocation_stack_[(3) - (2)]), "Case value already in use");
                            driver.push_repContainer(*(caseMap[intval]));
                        } else {
                            ASTrepContainer* caseBody = new ASTrepContainer();
                            caseMap[intval] = caseBody;
                            driver.push_repContainer(*caseBody);
                        }
                    }
                }
                catch (DeferUntilRuntime) {
                    driver.error((yylocation_stack_[(3) - (2)]), "Case expression is not constant");
                }
            }
            (yyval.modToken) = 0;
        }
    break;

  case 160:
/* Line 661 of lalr1.cc  */
#line 1138 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2) {
                if (!driver.switchStack.top()->mElseBody.mBody.empty()) {
                    driver.error((yyloc), "There can only be one 'else:' clause");
                } else {
                    driver.push_repContainer(driver.switchStack.top()->mElseBody);
                }
            }
            (yyval.modToken) = 0;
        }
    break;

  case 161:
/* Line 661 of lalr1.cc  */
#line 1151 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), true);
        }
    break;

  case 162:
/* Line 661 of lalr1.cc  */
#line 1156 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), false);
        }
    break;

  case 163:
/* Line 661 of lalr1.cc  */
#line 1163 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), true);
        }
    break;

  case 164:
/* Line 661 of lalr1.cc  */
#line 1168 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(5) - (3)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), false);
        }
    break;

  case 165:
/* Line 661 of lalr1.cc  */
#line 1175 "../../src-common/cfdg.ypp"
    {
            term_ptr mod((yysemantic_stack_[(2) - (2)].term));
            driver.MakeModTerm((yysemantic_stack_[(2) - (1)].mod)->modExp, mod);
            (yyval.mod) = (yysemantic_stack_[(2) - (1)].mod);
        }
    break;

  case 166:
/* Line 661 of lalr1.cc  */
#line 1180 "../../src-common/cfdg.ypp"
    {
            static const yy::location def;
            ASTmodification* m = new ASTmodification(def);
            m->flags = 0;
            (yyval.mod) = m;
        }
    break;

  case 167:
/* Line 661 of lalr1.cc  */
#line 1189 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].expression));
            (yyval.term) = new ASTmodTerm((ASTmodTerm::modTypeEnum)((yysemantic_stack_[(2) - (1)].modToken)), mod.release(), (yyloc));
        }
    break;

  case 168:
/* Line 661 of lalr1.cc  */
#line 1194 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(3) - (2)].expression));
            if ((yysemantic_stack_[(3) - (1)].modToken) < ASTmodTerm::hue || (yysemantic_stack_[(3) - (1)].modToken) > ASTmodTerm::alpha) {
                error((yyloc), "The target operator can only be applied to color adjustments");
                (yyval.term) = 0;
            } else {
                (yyval.term) = new ASTmodTerm((ASTmodTerm::modTypeEnum)((yysemantic_stack_[(3) - (1)].modToken) + 4), mod.release(), (yyloc));
            }
        }
    break;

  case 169:
/* Line 661 of lalr1.cc  */
#line 1204 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.term) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 170:
/* Line 661 of lalr1.cc  */
#line 1209 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.term) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 171:
/* Line 661 of lalr1.cc  */
#line 1216 "../../src-common/cfdg.ypp"
    {
            ASTrepContainer* tempHolder = new ASTrepContainer();
            driver.push_repContainer(*tempHolder);
            (yyval.bodyObj) = tempHolder;
        }
    break;

  case 172:
/* Line 661 of lalr1.cc  */
#line 1224 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = (yysemantic_stack_[(5) - (4)].expression);
        }
    break;

  case 175:
/* Line 661 of lalr1.cc  */
#line 1236 "../../src-common/cfdg.ypp"
    {
            str_ptr var((yysemantic_stack_[(3) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(3) - (3)].expression));
            driver.NextParameter(*var, exp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]));
        }
    break;

  case 176:
/* Line 661 of lalr1.cc  */
#line 1242 "../../src-common/cfdg.ypp"
    {
            exp_ptr exp((yysemantic_stack_[(3) - (3)].expression));
            error((yylocation_stack_[(3) - (1)]), "Reserved keyword: adjustment");
        }
    break;

  case 177:
/* Line 661 of lalr1.cc  */
#line 1249 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTexpression::Append((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 178:
/* Line 661 of lalr1.cc  */
#line 1253 "../../src-common/cfdg.ypp"
    { 
            (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); 
        }
    break;

  case 179:
/* Line 661 of lalr1.cc  */
#line 1260 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = (yysemantic_stack_[(3) - (1)].expression)->append(new ASTparen((yysemantic_stack_[(3) - (3)].expression)));
        }
    break;

  case 180:
/* Line 661 of lalr1.cc  */
#line 1264 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = new ASTcons(new ASTparen((yysemantic_stack_[(1) - (1)].expression)), 0);
        }
    break;

  case 181:
/* Line 661 of lalr1.cc  */
#line 1270 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 182:
/* Line 661 of lalr1.cc  */
#line 1272 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 183:
/* Line 661 of lalr1.cc  */
#line 1274 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 184:
/* Line 661 of lalr1.cc  */
#line 1276 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 185:
/* Line 661 of lalr1.cc  */
#line 1278 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 186:
/* Line 661 of lalr1.cc  */
#line 1280 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 187:
/* Line 661 of lalr1.cc  */
#line 1282 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 188:
/* Line 661 of lalr1.cc  */
#line 1287 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 189:
/* Line 661 of lalr1.cc  */
#line 1294 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 190:
/* Line 661 of lalr1.cc  */
#line 1296 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 191:
/* Line 661 of lalr1.cc  */
#line 1298 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 192:
/* Line 661 of lalr1.cc  */
#line 1300 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 193:
/* Line 661 of lalr1.cc  */
#line 1305 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 194:
/* Line 661 of lalr1.cc  */
#line 1310 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression));   }
    break;

  case 195:
/* Line 661 of lalr1.cc  */
#line 1312 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('+', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 196:
/* Line 661 of lalr1.cc  */
#line 1314 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('-', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 197:
/* Line 661 of lalr1.cc  */
#line 1316 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('_', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 198:
/* Line 661 of lalr1.cc  */
#line 1318 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('*', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 199:
/* Line 661 of lalr1.cc  */
#line 1320 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('/', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 200:
/* Line 661 of lalr1.cc  */
#line 1322 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 201:
/* Line 661 of lalr1.cc  */
#line 1324 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 202:
/* Line 661 of lalr1.cc  */
#line 1326 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('!', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 203:
/* Line 661 of lalr1.cc  */
#line 1328 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('^', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 204:
/* Line 661 of lalr1.cc  */
#line 1330 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('<', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 205:
/* Line 661 of lalr1.cc  */
#line 1332 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('L', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 206:
/* Line 661 of lalr1.cc  */
#line 1334 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('>', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 207:
/* Line 661 of lalr1.cc  */
#line 1336 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('G', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 208:
/* Line 661 of lalr1.cc  */
#line 1338 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('=', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 209:
/* Line 661 of lalr1.cc  */
#line 1340 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('n', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 210:
/* Line 661 of lalr1.cc  */
#line 1342 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('&', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 211:
/* Line 661 of lalr1.cc  */
#line 1344 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('|', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 212:
/* Line 661 of lalr1.cc  */
#line 1346 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('X', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 213:
/* Line 661 of lalr1.cc  */
#line 1348 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 214:
/* Line 661 of lalr1.cc  */
#line 1350 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].mod); }
    break;

  case 215:
/* Line 661 of lalr1.cc  */
#line 1354 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 216:
/* Line 661 of lalr1.cc  */
#line 1356 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 217:
/* Line 661 of lalr1.cc  */
#line 1358 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 218:
/* Line 661 of lalr1.cc  */
#line 1360 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 219:
/* Line 661 of lalr1.cc  */
#line 1365 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 220:
/* Line 661 of lalr1.cc  */
#line 1370 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('+', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 221:
/* Line 661 of lalr1.cc  */
#line 1372 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('-', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 222:
/* Line 661 of lalr1.cc  */
#line 1374 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('_', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 223:
/* Line 661 of lalr1.cc  */
#line 1376 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('*', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 224:
/* Line 661 of lalr1.cc  */
#line 1378 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('/', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 225:
/* Line 661 of lalr1.cc  */
#line 1380 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 226:
/* Line 661 of lalr1.cc  */
#line 1382 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 227:
/* Line 661 of lalr1.cc  */
#line 1384 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('!', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 228:
/* Line 661 of lalr1.cc  */
#line 1386 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('^', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 229:
/* Line 661 of lalr1.cc  */
#line 1388 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('<', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 230:
/* Line 661 of lalr1.cc  */
#line 1390 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('L', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 231:
/* Line 661 of lalr1.cc  */
#line 1392 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('>', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 232:
/* Line 661 of lalr1.cc  */
#line 1394 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('G', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 233:
/* Line 661 of lalr1.cc  */
#line 1396 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('=', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 234:
/* Line 661 of lalr1.cc  */
#line 1398 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('n', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 235:
/* Line 661 of lalr1.cc  */
#line 1400 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('&', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 236:
/* Line 661 of lalr1.cc  */
#line 1402 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('|', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 237:
/* Line 661 of lalr1.cc  */
#line 1404 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('X', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 238:
/* Line 661 of lalr1.cc  */
#line 1406 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 239:
/* Line 661 of lalr1.cc  */
#line 1408 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].mod); }
    break;

  case 240:
/* Line 661 of lalr1.cc  */
#line 1412 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 241:
/* Line 661 of lalr1.cc  */
#line 1417 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), true);
        }
    break;

  case 242:
/* Line 661 of lalr1.cc  */
#line 1423 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeArray(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]));
        }
    break;

  case 243:
/* Line 661 of lalr1.cc  */
#line 1429 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 244:
/* Line 661 of lalr1.cc  */
#line 1435 "../../src-common/cfdg.ypp"
    {
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            std::auto_ptr<ASTrepContainer> vars((yysemantic_stack_[(2) - (1)].bodyObj));
            (yyval.expression) = driver.MakeLet((yylocation_stack_[(2) - (1)]), exp);
        }
    break;

  case 245:
/* Line 661 of lalr1.cc  */
#line 1441 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 246:
/* Line 661 of lalr1.cc  */
#line 1448 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 247:
/* Line 661 of lalr1.cc  */
#line 1453 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 248:
/* Line 661 of lalr1.cc  */
#line 1459 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeArray(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]));
        }
    break;

  case 249:
/* Line 661 of lalr1.cc  */
#line 1465 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 250:
/* Line 661 of lalr1.cc  */
#line 1471 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args(new ASTexpression((yylocation_stack_[(4) - (1)]) + (yylocation_stack_[(4) - (4)])));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 251:
/* Line 661 of lalr1.cc  */
#line 1477 "../../src-common/cfdg.ypp"
    {
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            std::auto_ptr<ASTrepContainer> vars((yysemantic_stack_[(2) - (1)].bodyObj));
            (yyval.expression) = driver.MakeLet((yylocation_stack_[(2) - (1)]), exp);
        }
    break;

  case 252:
/* Line 661 of lalr1.cc  */
#line 1483 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 253:
/* Line 661 of lalr1.cc  */
#line 1490 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 254:
/* Line 661 of lalr1.cc  */
#line 1492 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(1) - (1)].string); }
    break;


/* Line 661 of lalr1.cc  */
#line 2832 "cfdg.tab.cpp"
	default:
          break;
      }
    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action
       invokes YYABORT, YYACCEPT, or YYERROR immediately after altering
       yychar.  In the case of YYABORT or YYACCEPT, an incorrect
       destructor might then be invoked immediately.  In the case of
       YYERROR, subsequent parser actions might lead to an incorrect
       destructor call or verbose syntax error message before the
       lookahead is translated.  */
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yytranslate_ (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	if (yychar == yyempty_)
	  yytoken = yyempty_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[1] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
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

    yyerror_range[1] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
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

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[1] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[2] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
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
    if (yychar != yyempty_)
      {
        /* Make sure we have latest lookahead translation.  See comments
           at user semantic actions for why this is necessary.  */
        yytoken = yytranslate_ (yychar);
        yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval,
                     &yylloc);
      }

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  CfdgParser::yysyntax_error_ (int, int)
  {
    return YY_("syntax error");
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int CfdgParser::yypact_ninf_ = -257;
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

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
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

  /* YYPGOTO[NTERM-NUM].  */
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

  /* YYDEFGOTO[NTERM-NUM].  */
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

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char CfdgParser::yytable_ninf_ = -92;
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

  /* YYCHECK.  */
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

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
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

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  CfdgParser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,    44,
      45,    43,    95,    42,    47,   304,   305,    94,    40,    91,
      64,   123,   125,    41,    58,    93,   124,    59
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
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

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
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


  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const CfdgParser::rhs_number_type
  CfdgParser::yyrhs_[] =
  {
        69,     0,    -1,     4,    70,    -1,     5,    71,    -1,    70,
      73,    -1,    -1,    71,    72,    -1,    -1,    81,    -1,    77,
      -1,    78,    -1,    97,    -1,    98,    -1,    90,    -1,    92,
      -1,    86,    -1,    75,    -1,    82,    -1,    83,    -1,    76,
      -1,    78,    -1,    84,    -1,    85,    -1,    94,    -1,   100,
      -1,    74,    -1,    26,    10,    -1,    19,    10,    -1,    20,
      10,    -1,    26,    58,    -1,    26,    26,    58,    -1,    33,
      -1,     6,    -1,     8,    26,    58,    -1,     3,    26,    58,
      -1,     3,    26,    59,    -1,     3,    31,    59,    -1,    21,
     132,    -1,    34,   132,    -1,    19,   132,    -1,    32,    79,
      -1,    93,    -1,    32,    79,    -1,    33,    80,    79,    -1,
      23,    -1,    29,    -1,    30,    -1,    60,    26,    -1,    -1,
       3,    26,   105,   133,    -1,     3,    31,   133,    -1,     3,
      26,   105,    -1,     3,    26,    -1,    21,   132,    -1,    34,
     132,    -1,    19,   132,    -1,    87,   143,    -1,     6,    26,
     104,    10,    -1,    26,   104,    10,    -1,    26,    26,   104,
      10,    -1,    26,    10,    -1,     6,    19,   104,    10,    -1,
      19,   104,    10,    -1,    26,    19,   103,    10,    -1,    19,
      10,    -1,    26,    10,    -1,    19,    10,    -1,    88,   143,
      -1,     6,    26,   103,    -1,    90,    61,    -1,    91,   106,
      62,    -1,     7,    26,    -1,     7,    26,    28,    -1,    93,
      61,   120,    62,    -1,     7,    -1,     7,    28,    -1,     8,
      26,   103,    -1,    95,    61,   106,    62,    -1,    96,    61,
     106,    62,    -1,     8,    26,    -1,    99,    61,   107,    62,
      -1,    26,    26,    -1,     6,    26,    -1,    26,    19,    -1,
       6,    19,    -1,    26,    -1,    19,    -1,   102,    49,   101,
      -1,   101,    -1,    58,   102,    63,    -1,    -1,    58,   102,
      63,    -1,    58,    63,    -1,    58,   141,    63,    -1,    58,
      10,    63,    -1,    58,    63,    -1,    -1,   106,   114,    -1,
      -1,   107,   117,    -1,    -1,    36,    61,   134,    62,    -1,
     147,   132,    -1,    36,    58,   143,    63,    -1,    36,    58,
      63,    -1,   147,   105,   133,    -1,    13,    58,   143,    63,
     133,    -1,   136,   137,   133,    -1,     8,   147,   105,   133,
      -1,    61,   106,    62,    -1,   114,    -1,    61,   107,    62,
      -1,   108,    -1,   112,   113,    -1,    -1,   131,   110,    -1,
     109,    -1,    89,    -1,   119,    -1,    -1,   119,    12,   115,
     110,    -1,   127,   110,    -1,   128,   110,    -1,   129,   110,
      -1,   130,    61,   112,    62,    -1,   116,    -1,    28,    53,
      -1,    26,    61,    -1,    36,    61,    -1,   108,    -1,   124,
     111,    -1,   118,    -1,    36,    58,    -1,    26,    58,    -1,
       8,    -1,    11,    -1,    26,    10,    -1,    19,    10,    -1,
      13,    -1,    19,    -1,    15,    -1,   126,   133,   110,    -1,
     120,   123,    -1,    -1,    61,   120,    62,    -1,   122,    -1,
     147,   132,    -1,   122,    -1,   124,   121,    -1,    -1,    28,
      53,   125,   132,    -1,    11,    26,    10,   143,    -1,    11,
      19,    10,   143,    -1,    11,   143,    -1,    13,    58,   143,
      63,    -1,   127,   110,    14,    -1,    19,   143,    -1,    17,
     143,    -1,    15,    58,   143,    63,    -1,    16,   143,    64,
      -1,    14,    64,    -1,    61,   134,    62,    -1,    59,   134,
      65,    -1,    59,   134,    65,    -1,    59,    59,   134,    65,
      65,    -1,   134,   135,    -1,    -1,    19,   140,    -1,    19,
     142,    66,    -1,    20,    26,    -1,    20,    30,    -1,    18,
      -1,    58,   138,    67,   143,    63,    -1,   138,    67,   139,
      -1,   139,    -1,    26,    10,   143,    -1,    19,    10,   143,
      -1,   140,   142,    -1,   142,    -1,   141,    49,   144,    -1,
     144,    -1,    28,    -1,    48,    -1,    58,   143,    63,    -1,
     145,    -1,    50,   142,    -1,    51,   142,    -1,   142,    24,
     142,    -1,   142,    25,   142,    -1,    28,    -1,    48,    -1,
     146,    -1,   143,    24,   143,    -1,   143,    25,   143,    -1,
     143,    49,   143,    -1,   143,    51,   143,    -1,   143,    50,
     143,    -1,   143,    52,   143,    -1,   143,    53,   143,    -1,
     143,    54,   143,    -1,    50,   143,    -1,    51,   143,    -1,
      44,   143,    -1,   143,    57,   143,    -1,   143,    39,   143,
      -1,   143,    38,   143,    -1,   143,    41,   143,    -1,   143,
      40,   143,    -1,   143,    42,   143,    -1,   143,    43,   143,
      -1,   143,    45,   143,    -1,   143,    46,   143,    -1,   143,
      47,   143,    -1,    58,   143,    63,    -1,   133,    -1,    28,
      -1,    48,    -1,   146,    -1,   144,    24,   144,    -1,   144,
      25,   144,    -1,   144,    51,   144,    -1,   144,    50,   144,
      -1,   144,    52,   144,    -1,   144,    53,   144,    -1,   144,
      54,   144,    -1,    50,   144,    -1,    51,   144,    -1,    44,
     144,    -1,   144,    57,   144,    -1,   144,    39,   144,    -1,
     144,    38,   144,    -1,   144,    41,   144,    -1,   144,    40,
     144,    -1,   144,    42,   144,    -1,   144,    43,   144,    -1,
     144,    45,   144,    -1,   144,    46,   144,    -1,   144,    47,
     144,    -1,    58,   143,    63,    -1,   133,    -1,    26,    58,
      63,    -1,    26,    58,   141,    63,    -1,    31,    59,   143,
      65,    -1,    13,    58,   143,    63,    -1,   136,   137,    -1,
      26,    -1,    26,    58,    63,    -1,    26,    58,   141,    63,
      -1,    31,    59,   143,    65,    -1,    13,    58,   143,    63,
      -1,    26,    58,    10,    63,    -1,   136,   137,    -1,    26,
      -1,    26,    -1,    31,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  CfdgParser::yyprhs_[] =
  {
         0,     0,     3,     6,     9,    12,    13,    16,    17,    19,
      21,    23,    25,    27,    29,    31,    33,    35,    37,    39,
      41,    43,    45,    47,    49,    51,    53,    56,    59,    62,
      65,    69,    71,    73,    77,    81,    85,    89,    92,    95,
      98,   101,   103,   106,   110,   112,   114,   116,   119,   120,
     125,   129,   133,   136,   139,   142,   145,   148,   153,   157,
     162,   165,   170,   174,   179,   182,   185,   188,   191,   195,
     198,   202,   205,   209,   214,   216,   219,   223,   228,   233,
     236,   241,   244,   247,   250,   253,   255,   257,   261,   263,
     267,   268,   272,   275,   279,   283,   286,   287,   290,   291,
     294,   295,   300,   303,   308,   312,   316,   322,   326,   331,
     335,   337,   341,   343,   346,   347,   350,   352,   354,   356,
     357,   362,   365,   368,   371,   376,   378,   381,   384,   387,
     389,   392,   394,   397,   400,   402,   404,   407,   410,   412,
     414,   416,   420,   423,   424,   428,   430,   433,   435,   438,
     439,   444,   449,   454,   457,   462,   466,   469,   472,   477,
     481,   484,   488,   492,   496,   502,   505,   506,   509,   513,
     516,   519,   521,   527,   531,   533,   537,   541,   544,   546,
     550,   552,   554,   556,   560,   562,   565,   568,   572,   576,
     578,   580,   582,   586,   590,   594,   598,   602,   606,   610,
     614,   617,   620,   623,   627,   631,   635,   639,   643,   647,
     651,   655,   659,   663,   667,   669,   671,   673,   675,   679,
     683,   687,   691,   695,   699,   703,   706,   709,   712,   716,
     720,   724,   728,   732,   736,   740,   744,   748,   752,   756,
     758,   762,   767,   772,   777,   780,   782,   786,   791,   796,
     801,   806,   809,   811,   813
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
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
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
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
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
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
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int CfdgParser::yyeof_ = 0;
  const int CfdgParser::yylast_ = 1331;
  const int CfdgParser::yynnts_ = 80;
  const int CfdgParser::yyempty_ = -2;
  const int CfdgParser::yyfinal_ = 6;
  const int CfdgParser::yyterror_ = 1;
  const int CfdgParser::yyerrcode_ = 256;
  const int CfdgParser::yyntokens_ = 68;

  const unsigned int CfdgParser::yyuser_token_number_max_ = 305;
  const CfdgParser::token_number_type CfdgParser::yyundef_token_ = 2;


} // yy
/* Line 1106 of lalr1.cc  */
#line 3848 "cfdg.tab.cpp"
/* Line 1107 of lalr1.cc  */
#line 1495 "../../src-common/cfdg.ypp"


void yy::CfdgParser::error(const CfdgParser::location_type& l, const std::string& m)
{
    driver.mWant2ndPass = false;
    driver.error(l, m);
}
