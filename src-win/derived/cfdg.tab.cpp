/* A Bison parser, made by GNU Bison 2.7.  */

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
/* Line 279 of lalr1.cc  */
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
    class ASTloop;
    class ASTif;
    class ASTswitch;
    class ASTpathBody;
    class ASTpathLoop;
    class ASTruleSpecifier;
    class ASTrule;
    class ASTdefine;
}

/* Line 279 of lalr1.cc  */
#line 60 "cfdg.tab.cpp"


#include "cfdg.tab.hpp"

/* User implementation prologue.  */
/* Line 285 of lalr1.cc  */
#line 80 "../../src-common/cfdg.ypp"

#include "astreplacement.h"
#include "astexpression.h"
    
    using namespace AST;
/* Line 285 of lalr1.cc  */
#line 176 "../../src-common/cfdg.ypp"

#include "scanner.h"
#include "math.h"
#include "builder.h"
#include <cassert>

#undef yylex
#define yylex driver.lexer->lex

/* Line 285 of lalr1.cc  */
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
# define YY_SYMBOL_PRINT(Title, Type, Value, Location) YYUSE(Type)
# define YY_REDUCE_PRINT(Rule)        static_cast<void>(0)
# define YY_STACK_PRINT()             static_cast<void>(0)

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
/* Line 353 of lalr1.cc  */
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

    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 26: /* USER_STRING */
/* Line 455 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).string); };
/* Line 455 of lalr1.cc  */
#line 249 "cfdg.tab.cpp"
        break;
      case 29: /* USER_FILENAME */
/* Line 455 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).string); };
/* Line 455 of lalr1.cc  */
#line 256 "cfdg.tab.cpp"
        break;
      case 30: /* USER_QSTRING */
/* Line 455 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).string); };
/* Line 455 of lalr1.cc  */
#line 263 "cfdg.tab.cpp"
        break;
      case 31: /* USER_ARRAYNAME */
/* Line 455 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).string); };
/* Line 455 of lalr1.cc  */
#line 270 "cfdg.tab.cpp"
        break;
      case 36: /* USER_PATHOP */
/* Line 455 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).string); };
/* Line 455 of lalr1.cc  */
#line 277 "cfdg.tab.cpp"
        break;
      case 72: /* statement */
/* Line 455 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 284 "cfdg.tab.cpp"
        break;
      case 73: /* statement_v2 */
/* Line 455 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 291 "cfdg.tab.cpp"
        break;
      case 79: /* fileString */
/* Line 455 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).string); };
/* Line 455 of lalr1.cc  */
#line 298 "cfdg.tab.cpp"
        break;
      case 80: /* fileNameSpace */
/* Line 455 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).string); };
/* Line 455 of lalr1.cc  */
#line 305 "cfdg.tab.cpp"
        break;
      case 81: /* initialization */
/* Line 455 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 312 "cfdg.tab.cpp"
        break;
      case 82: /* initialization_v2 */
/* Line 455 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 319 "cfdg.tab.cpp"
        break;
      case 83: /* background */
/* Line 455 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 326 "cfdg.tab.cpp"
        break;
      case 84: /* tile */
/* Line 455 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 333 "cfdg.tab.cpp"
        break;
      case 85: /* size */
/* Line 455 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 340 "cfdg.tab.cpp"
        break;
      case 86: /* global_definition */
/* Line 455 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).defObj); };
/* Line 455 of lalr1.cc  */
#line 347 "cfdg.tab.cpp"
        break;
      case 87: /* function_definition_header */
/* Line 455 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).defObj); };
/* Line 455 of lalr1.cc  */
#line 354 "cfdg.tab.cpp"
        break;
      case 88: /* global_definition_header */
/* Line 455 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).defObj); };
/* Line 455 of lalr1.cc  */
#line 361 "cfdg.tab.cpp"
        break;
      case 89: /* definition_header */
/* Line 455 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).defObj); };
/* Line 455 of lalr1.cc  */
#line 368 "cfdg.tab.cpp"
        break;
      case 90: /* definition */
/* Line 455 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).defObj); };
/* Line 455 of lalr1.cc  */
#line 375 "cfdg.tab.cpp"
        break;
      case 92: /* shape_singleton_header */
/* Line 455 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).ruleObj); };
/* Line 455 of lalr1.cc  */
#line 382 "cfdg.tab.cpp"
        break;
      case 93: /* shape_singleton */
/* Line 455 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 389 "cfdg.tab.cpp"
        break;
      case 94: /* rule_header_v2 */
/* Line 455 of lalr1.cc  */
#line 171 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).ruleObj); };
/* Line 455 of lalr1.cc  */
#line 396 "cfdg.tab.cpp"
        break;
      case 96: /* rule_header */
/* Line 455 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).ruleObj); };
/* Line 455 of lalr1.cc  */
#line 403 "cfdg.tab.cpp"
        break;
      case 97: /* path_header */
/* Line 455 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).ruleObj); };
/* Line 455 of lalr1.cc  */
#line 410 "cfdg.tab.cpp"
        break;
      case 98: /* rule */
/* Line 455 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 417 "cfdg.tab.cpp"
        break;
      case 99: /* path */
/* Line 455 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 424 "cfdg.tab.cpp"
        break;
      case 100: /* path_header_v2 */
/* Line 455 of lalr1.cc  */
#line 171 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).ruleObj); };
/* Line 455 of lalr1.cc  */
#line 431 "cfdg.tab.cpp"
        break;
      case 106: /* parameter_spec */
/* Line 455 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 438 "cfdg.tab.cpp"
        break;
      case 109: /* pathOp_simple_v2 */
/* Line 455 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 445 "cfdg.tab.cpp"
        break;
      case 110: /* element_simple */
/* Line 455 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 452 "cfdg.tab.cpp"
        break;
      case 115: /* element */
/* Line 455 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 459 "cfdg.tab.cpp"
        break;
      case 118: /* pathOp_v2 */
/* Line 455 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 466 "cfdg.tab.cpp"
        break;
      case 120: /* element_loop */
/* Line 455 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).loopObj); };
/* Line 455 of lalr1.cc  */
#line 473 "cfdg.tab.cpp"
        break;
      case 123: /* replacement_simple_v2 */
/* Line 455 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 480 "cfdg.tab.cpp"
        break;
      case 124: /* replacement_v2 */
/* Line 455 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 487 "cfdg.tab.cpp"
        break;
      case 125: /* loopHeader_v2 */
/* Line 455 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).loopObj); };
/* Line 455 of lalr1.cc  */
#line 494 "cfdg.tab.cpp"
        break;
      case 127: /* loopHeader */
/* Line 455 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).loopObj); };
/* Line 455 of lalr1.cc  */
#line 501 "cfdg.tab.cpp"
        break;
      case 128: /* ifHeader */
/* Line 455 of lalr1.cc  */
#line 172 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).ifObj); };
/* Line 455 of lalr1.cc  */
#line 508 "cfdg.tab.cpp"
        break;
      case 129: /* ifElseHeader */
/* Line 455 of lalr1.cc  */
#line 172 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).ifObj); };
/* Line 455 of lalr1.cc  */
#line 515 "cfdg.tab.cpp"
        break;
      case 130: /* transHeader */
/* Line 455 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 522 "cfdg.tab.cpp"
        break;
      case 131: /* switchHeader */
/* Line 455 of lalr1.cc  */
#line 173 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).switchObj); };
/* Line 455 of lalr1.cc  */
#line 529 "cfdg.tab.cpp"
        break;
      case 132: /* caseHeader */
/* Line 455 of lalr1.cc  */
#line 174 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); };
/* Line 455 of lalr1.cc  */
#line 536 "cfdg.tab.cpp"
        break;
      case 133: /* modification_v2 */
/* Line 455 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).mod); };
/* Line 455 of lalr1.cc  */
#line 543 "cfdg.tab.cpp"
        break;
      case 134: /* modification */
/* Line 455 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).mod); };
/* Line 455 of lalr1.cc  */
#line 550 "cfdg.tab.cpp"
        break;
      case 135: /* buncha_adjustments */
/* Line 455 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).mod); };
/* Line 455 of lalr1.cc  */
#line 557 "cfdg.tab.cpp"
        break;
      case 136: /* adjustment */
/* Line 455 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).term); };
/* Line 455 of lalr1.cc  */
#line 564 "cfdg.tab.cpp"
        break;
      case 137: /* letHeader */
/* Line 455 of lalr1.cc  */
#line 175 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).bodyObj); };
/* Line 455 of lalr1.cc  */
#line 571 "cfdg.tab.cpp"
        break;
      case 138: /* letBody */
/* Line 455 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 578 "cfdg.tab.cpp"
        break;
      case 141: /* explist */
/* Line 455 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 585 "cfdg.tab.cpp"
        break;
      case 142: /* arglist */
/* Line 455 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 592 "cfdg.tab.cpp"
        break;
      case 143: /* exp */
/* Line 455 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 599 "cfdg.tab.cpp"
        break;
      case 144: /* exp2 */
/* Line 455 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 606 "cfdg.tab.cpp"
        break;
      case 145: /* exp3 */
/* Line 455 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 613 "cfdg.tab.cpp"
        break;
      case 146: /* expfunc */
/* Line 455 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 620 "cfdg.tab.cpp"
        break;
      case 147: /* exp2func */
/* Line 455 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 627 "cfdg.tab.cpp"
        break;
      case 148: /* shapeName */
/* Line 455 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).string); };
/* Line 455 of lalr1.cc  */
#line 634 "cfdg.tab.cpp"
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

    // State.
    int yyn;
    int yylen = 0;
    int yystate = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    static semantic_type yyval_default;
    semantic_type yylval = yyval_default;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
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

    // Compute the default @$.
    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }

    // Perform the reduction.
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
          case 4:
/* Line 670 of lalr1.cc  */
#line 192 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 6:
/* Line 670 of lalr1.cc  */
#line 201 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 9:
/* Line 670 of lalr1.cc  */
#line 211 "../../src-common/cfdg.ypp"
    { (yyval.component) = nullptr; }
    break;

  case 10:
/* Line 670 of lalr1.cc  */
#line 212 "../../src-common/cfdg.ypp"
    { (yyval.component) = nullptr; }
    break;

  case 13:
/* Line 670 of lalr1.cc  */
#line 215 "../../src-common/cfdg.ypp"
    { (yyval.component) = nullptr; }
    break;

  case 15:
/* Line 670 of lalr1.cc  */
#line 217 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].defObj); }
    break;

  case 16:
/* Line 670 of lalr1.cc  */
#line 218 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = nullptr;
        }
    break;

  case 19:
/* Line 670 of lalr1.cc  */
#line 227 "../../src-common/cfdg.ypp"
    { (yyval.component) = nullptr; }
    break;

  case 20:
/* Line 670 of lalr1.cc  */
#line 228 "../../src-common/cfdg.ypp"
    { (yyval.component) = nullptr; }
    break;

  case 25:
/* Line 670 of lalr1.cc  */
#line 233 "../../src-common/cfdg.ypp"
    {
            if (driver.lexer->maybeVersion == token::CFDG2) {
                error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            } else {
                driver.lexer->maybeVersion = token::CFDG3;
            }
            (yyval.component) = nullptr;
            YYABORT;
        }
    break;

  case 26:
/* Line 670 of lalr1.cc  */
#line 245 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 27:
/* Line 670 of lalr1.cc  */
#line 246 "../../src-common/cfdg.ypp"
    {}
    break;

  case 28:
/* Line 670 of lalr1.cc  */
#line 247 "../../src-common/cfdg.ypp"
    {}
    break;

  case 29:
/* Line 670 of lalr1.cc  */
#line 248 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 30:
/* Line 670 of lalr1.cc  */
#line 249 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (1)].string); delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 33:
/* Line 670 of lalr1.cc  */
#line 252 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 34:
/* Line 670 of lalr1.cc  */
#line 253 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 35:
/* Line 670 of lalr1.cc  */
#line 254 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 36:
/* Line 670 of lalr1.cc  */
#line 255 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 37:
/* Line 670 of lalr1.cc  */
#line 259 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 38:
/* Line 670 of lalr1.cc  */
#line 260 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 39:
/* Line 670 of lalr1.cc  */
#line 261 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 40:
/* Line 670 of lalr1.cc  */
#line 262 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 41:
/* Line 670 of lalr1.cc  */
#line 263 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(1) - (1)].ruleObj); }
    break;

  case 42:
/* Line 670 of lalr1.cc  */
#line 267 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(2) - (2)].string)); (yysemantic_stack_[(2) - (2)].string) = nullptr;
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(nullptr);
            driver.IncludeFile(*file);
        }
    break;

  case 43:
/* Line 670 of lalr1.cc  */
#line 276 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(3) - (3)].string)); (yysemantic_stack_[(3) - (3)].string) = nullptr;
            str_ptr nm((yysemantic_stack_[(3) - (2)].string)); (yysemantic_stack_[(3) - (2)].string) = nullptr;
            driver.SetShape(nullptr);
            driver.IncludeFile(*file);
            if (nm)
                driver.PushNameSpace(std::move(nm), (yylocation_stack_[(3) - (2)]));
        }
    break;

  case 44:
/* Line 670 of lalr1.cc  */
#line 287 "../../src-common/cfdg.ypp"
    {
            if (driver.EndInclude())
                YYACCEPT;
        }
    break;

  case 47:
/* Line 670 of lalr1.cc  */
#line 297 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 48:
/* Line 670 of lalr1.cc  */
#line 298 "../../src-common/cfdg.ypp"
    { (yyval.string) = nullptr; }
    break;

  case 49:
/* Line 670 of lalr1.cc  */
#line 302 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(4) - (2)].string)); (yysemantic_stack_[(4) - (2)].string) = nullptr;
            exp_ptr p((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            mod_ptr mod((yysemantic_stack_[(4) - (4)].mod)); (yysemantic_stack_[(4) - (4)].mod) = nullptr;
            driver.SetShape(nullptr);
            static const std::string cfgName("CF::StartShape");
            ASTdefine* cfg = driver.MakeDefinition(cfgName, (yyloc), false);
            if (cfg)
                cfg->mExpression.reset(driver.MakeRuleSpec(*name, std::move(p), (yylocation_stack_[(4) - (2)]), std::move(mod)));
            (yyval.component) = cfg;
        }
    break;

  case 50:
/* Line 670 of lalr1.cc  */
#line 314 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(3) - (2)].string)); (yysemantic_stack_[(3) - (2)].string) = nullptr;
            mod_ptr mod((yysemantic_stack_[(3) - (3)].mod)); (yysemantic_stack_[(3) - (3)].mod) = nullptr;
            driver.SetShape(nullptr);
            static const std::string cfgName("CF::StartShape");
            ASTdefine* cfg = driver.MakeDefinition(cfgName, (yyloc), false);
            if (cfg)
                cfg->mExpression.reset(driver.MakeRuleSpec(*name, nullptr, (yylocation_stack_[(3) - (2)]), std::move(mod)));
            (yyval.component) = cfg;
        }
    break;

  case 51:
/* Line 670 of lalr1.cc  */
#line 325 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(3) - (2)].string)); (yysemantic_stack_[(3) - (2)].string) = nullptr;
            exp_ptr p((yysemantic_stack_[(3) - (3)].expression)); (yysemantic_stack_[(3) - (3)].expression) = nullptr;
            mod_ptr mod(new ASTmodification((yyloc)));
            driver.SetShape(nullptr);
            static const std::string cfgName("CF::StartShape");
            ASTdefine* cfg = driver.MakeDefinition(cfgName, (yyloc), false);
            if (cfg)
                cfg->mExpression.reset(driver.MakeRuleSpec(*name, std::move(p), (yylocation_stack_[(3) - (2)]), std::move(mod)));
            (yyval.component) = cfg;
        }
    break;

  case 52:
/* Line 670 of lalr1.cc  */
#line 339 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (2)].string)); (yysemantic_stack_[(2) - (2)].string) = nullptr;
            mod_ptr mod(new ASTmodification((yyloc)));
            driver.SetShape(nullptr);
            static const std::string cfgName("CF::StartShape");
            ASTdefine* cfg = driver.MakeDefinition(cfgName, (yyloc), false);
            if (cfg)
                cfg->mExpression.reset(driver.MakeRuleSpec(*name, nullptr, (yylocation_stack_[(2) - (2)]), std::move(mod)));
            (yyval.component) = cfg;
        }
    break;

  case 53:
/* Line 670 of lalr1.cc  */
#line 352 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].mod)); (yysemantic_stack_[(2) - (2)].mod) = nullptr;
            static const std::string cfgName("CF::Background");
            ASTdefine* cfg = driver.MakeDefinition(cfgName, (yyloc), false);
            if (cfg)
                cfg->mExpression = std::move(mod);
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = cfg;
        }
    break;

  case 54:
/* Line 670 of lalr1.cc  */
#line 364 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].mod)); (yysemantic_stack_[(2) - (2)].mod) = nullptr;
            static const std::string cfgName("CF::Tile");
            ASTdefine* cfg = driver.MakeDefinition(cfgName, (yyloc), false);
            if (cfg)
                cfg->mExpression = std::move(mod);
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = cfg;
        }
    break;

  case 55:
/* Line 670 of lalr1.cc  */
#line 376 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].mod)); (yysemantic_stack_[(2) - (2)].mod) = nullptr;
            ASTdefine* cfg = nullptr;
            driver.lexer->maybeVersion = token::CFDG2;
            if ((yysemantic_stack_[(2) - (1)].modToken) != ASTmodTerm::size && (yysemantic_stack_[(2) - (1)].modToken) != ASTmodTerm::time) {
                error((yylocation_stack_[(2) - (1)]), "Syntax error");
            } else {
                static const std::string sizeName("CF::Size");
                static const std::string timeName("CF::Time");
                cfg = driver.MakeDefinition(*((yysemantic_stack_[(2) - (1)].modToken) == ASTmodTerm::size ? &sizeName : &timeName), (yyloc), false);
                if (cfg)
                    cfg->mExpression = std::move(mod);
                driver.lexer->maybeVersion = token::CFDG2;
            }
            (yyval.component) = cfg;
        }
    break;

  case 56:
/* Line 670 of lalr1.cc  */
#line 395 "../../src-common/cfdg.ypp"
    {
            def_ptr var((yysemantic_stack_[(2) - (1)].defObj));  (yysemantic_stack_[(2) - (1)].defObj) = nullptr;
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));  (yysemantic_stack_[(2) - (2)].expression) = nullptr;
            if (var) {
                if (var->isFunction) {
                    driver.pop_repContainer(nullptr);
                    driver.mParamDecls.mParameters.clear();
                    driver.mParamDecls.mStackCount = 0;
                }
                if (var->mConfigDepth >= 0 || var->isFunction) {
                    var->mExpression = std::move(exp);
                } else {
                    if (ASTmodification* mod = dynamic_cast<ASTmodification*>(exp.get())) {
                        mod->modData.mRand64Seed.seed(0);
                        var->mChildChange.grab(mod);
                    } else {
                        var->mExpression = std::move(exp);
                    }
                }
                (yyval.defObj) = var.release();
            } else {
                (yyval.defObj) = nullptr;
            }
        }
    break;

  case 57:
/* Line 670 of lalr1.cc  */
#line 422 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(4) - (2)].string)); (yysemantic_stack_[(4) - (2)].string) = nullptr;
            ASTdefine* def = driver.MakeDefinition(*name, (yyloc), true);
            if (def) {
                def->mType = RuleType;
                def->mTuplesize = 1;
            }
            (yyval.defObj) = def;
        }
    break;

  case 58:
/* Line 670 of lalr1.cc  */
#line 432 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(3) - (1)].string)); (yysemantic_stack_[(3) - (1)].string) = nullptr;
            ASTdefine* def = driver.MakeDefinition(*name, (yyloc), true);
            if (def) {
                def->mType = NumericType;
                def->mTuplesize = 1;
            }
            (yyval.defObj) = def;
        }
    break;

  case 59:
/* Line 670 of lalr1.cc  */
#line 442 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            str_ptr name((yysemantic_stack_[(4) - (2)].string)); (yysemantic_stack_[(4) - (2)].string) = nullptr;
            ASTdefine* def = driver.MakeDefinition(*name, (yyloc), true);
            if (def)
                def->mType = AST::decodeType(*type, def->mTuplesize, def->isNatural, (yylocation_stack_[(4) - (1)]));
            (yyval.defObj) = def;
        }
    break;

  case 60:
/* Line 670 of lalr1.cc  */
#line 451 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(4) - (2)]), "Reserved keyword: adjustment");
            (yyval.defObj) = nullptr;
        }
    break;

  case 61:
/* Line 670 of lalr1.cc  */
#line 456 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(3) - (1)]), "Reserved keyword: adjustment");
            (yyval.defObj) = nullptr;
        }
    break;

  case 62:
/* Line 670 of lalr1.cc  */
#line 461 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            error((yylocation_stack_[(4) - (2)]), "Reserved keyword: adjustment");
            (yyval.defObj) = nullptr;
        }
    break;

  case 63:
/* Line 670 of lalr1.cc  */
#line 469 "../../src-common/cfdg.ypp"
    {
            driver.push_repContainer(driver.mParamDecls);
            (yyval.defObj) = (yysemantic_stack_[(1) - (1)].defObj);
        }
    break;

  case 64:
/* Line 670 of lalr1.cc  */
#line 474 "../../src-common/cfdg.ypp"
    {
            (yyval.defObj) = (yysemantic_stack_[(1) - (1)].defObj);
        }
    break;

  case 65:
/* Line 670 of lalr1.cc  */
#line 480 "../../src-common/cfdg.ypp"
    {
            (yyval.defObj) = driver.MakeDefinition(*(yysemantic_stack_[(2) - (1)].string), (yyloc), false);
        }
    break;

  case 66:
/* Line 670 of lalr1.cc  */
#line 483 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (1)]), "Reserved keyword: adjustment");
            (yyval.defObj) = nullptr;
        }
    break;

  case 67:
/* Line 670 of lalr1.cc  */
#line 490 "../../src-common/cfdg.ypp"
    {
            def_ptr var((yysemantic_stack_[(2) - (1)].defObj));  (yysemantic_stack_[(2) - (1)].defObj) = nullptr;
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));  (yysemantic_stack_[(2) - (2)].expression) = nullptr;
            if (var) {
                if (ASTmodification* mod = dynamic_cast<ASTmodification*>(exp.get())) {
                    mod->modData.mRand64Seed.seed(0);
                    var->mChildChange.grab(mod);
                } else {
                    var->mExpression = std::move(exp);
                }
                (yyval.defObj) = var.release();
            } else {
                (yyval.defObj) = nullptr;
            }
        }
    break;

  case 68:
/* Line 670 of lalr1.cc  */
#line 508 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(3) - (2)].string)); (yysemantic_stack_[(3) - (2)].string) = nullptr;
            driver.SetShape(name.get(), (yylocation_stack_[(3) - (2)]));
        }
    break;

  case 69:
/* Line 670 of lalr1.cc  */
#line 515 "../../src-common/cfdg.ypp"
    {
            driver.mInPathContainer = false;
            rule_ptr rule(new ASTrule(-1, (yylocation_stack_[(2) - (1)])));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
        }
    break;

  case 70:
/* Line 670 of lalr1.cc  */
#line 524 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(3) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 71:
/* Line 670 of lalr1.cc  */
#line 532 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (2)].string)); (yysemantic_stack_[(2) - (2)].string) = nullptr;
            driver.SetShape(nullptr);
            rule_ptr rule(new ASTrule(driver.StringToShape(*name, (yylocation_stack_[(2) - (2)]), false), (yyloc)));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
        }
    break;

  case 72:
/* Line 670 of lalr1.cc  */
#line 541 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(3) - (2)].string)); (yysemantic_stack_[(3) - (2)].string) = nullptr;
            str_ptr weight((yysemantic_stack_[(3) - (3)].string)); (yysemantic_stack_[(3) - (3)].string) = nullptr;
            driver.SetShape(nullptr);
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
/* Line 670 of lalr1.cc  */
#line 556 "../../src-common/cfdg.ypp"
    {
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 74:
/* Line 670 of lalr1.cc  */
#line 564 "../../src-common/cfdg.ypp"
    {
            driver.mInPathContainer = false;
            rule_ptr rule(new ASTrule(-1, (yylocation_stack_[(1) - (1)])));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
        }
    break;

  case 75:
/* Line 670 of lalr1.cc  */
#line 572 "../../src-common/cfdg.ypp"
    {
            driver.mInPathContainer = false;
            str_ptr weight((yysemantic_stack_[(2) - (2)].string)); (yysemantic_stack_[(2) - (2)].string) = nullptr;
            rule_ptr rule(new ASTrule(-1, CFatof(weight->c_str()),
                                      weight->find_first_of('%')  != std::string::npos,
                                      (yyloc)));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
        }
    break;

  case 76:
/* Line 670 of lalr1.cc  */
#line 585 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(3) - (2)].string)); (yysemantic_stack_[(3) - (2)].string) = nullptr;
            driver.SetShape(name.get(), (yylocation_stack_[(3) - (2)]), true);
            driver.mInPathContainer = true;
            rule_ptr newPath(new ASTrule(-1, (yyloc)));
            newPath->isPath = true;
            driver.AddRule(newPath.get());
            driver.push_repContainer(newPath->mRuleBody);
            (yyval.ruleObj) = newPath.release();
        }
    break;

  case 77:
/* Line 670 of lalr1.cc  */
#line 598 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 78:
/* Line 670 of lalr1.cc  */
#line 606 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
            driver.SetShape(nullptr);
        }
    break;

  case 79:
/* Line 670 of lalr1.cc  */
#line 615 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (2)].string)); (yysemantic_stack_[(2) - (2)].string) = nullptr;
            driver.SetShape(nullptr);
            rule_ptr newPath(new ASTrule(driver.StringToShape(*name, (yylocation_stack_[(2) - (2)]), false), (yyloc)));
            newPath->isPath = true;
            driver.AddRule(newPath.get());
            driver.push_repContainer(newPath->mRuleBody);
            driver.mInPathContainer = true;
            (yyval.ruleObj) = newPath.release();
        }
    break;

  case 80:
/* Line 670 of lalr1.cc  */
#line 628 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 81:
/* Line 670 of lalr1.cc  */
#line 635 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(2) - (1)].string)); (yysemantic_stack_[(2) - (1)].string) = nullptr;
            str_ptr var((yysemantic_stack_[(2) - (2)].string)); (yysemantic_stack_[(2) - (2)].string) = nullptr;
            driver.NextParameterDecl(*type, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 82:
/* Line 670 of lalr1.cc  */
#line 641 "../../src-common/cfdg.ypp"
    {
            static std::string shapeStr("shape");
            str_ptr var((yysemantic_stack_[(2) - (2)].string)); (yysemantic_stack_[(2) - (2)].string) = nullptr;
            driver.NextParameterDecl(shapeStr, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 83:
/* Line 670 of lalr1.cc  */
#line 647 "../../src-common/cfdg.ypp"
    {
            delete (yysemantic_stack_[(2) - (1)].string);
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 84:
/* Line 670 of lalr1.cc  */
#line 652 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 85:
/* Line 670 of lalr1.cc  */
#line 656 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("number");
            str_ptr var((yysemantic_stack_[(1) - (1)].string)); (yysemantic_stack_[(1) - (1)].string) = nullptr;
            driver.NextParameterDecl(numtype, *var, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 86:
/* Line 670 of lalr1.cc  */
#line 662 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Reserved keyword: adjustment");
        }
    break;

  case 93:
/* Line 670 of lalr1.cc  */
#line 683 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(3) - (2)].expression);}
    break;

  case 94:
/* Line 670 of lalr1.cc  */
#line 684 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTexpression((yyloc), false, false, AST::ReuseType); }
    break;

  case 95:
/* Line 670 of lalr1.cc  */
#line 685 "../../src-common/cfdg.ypp"
    { (yyval.expression) = nullptr; }
    break;

  case 96:
/* Line 670 of lalr1.cc  */
#line 686 "../../src-common/cfdg.ypp"
    { (yyval.expression) = nullptr; }
    break;

  case 97:
/* Line 670 of lalr1.cc  */
#line 690 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 99:
/* Line 670 of lalr1.cc  */
#line 697 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 101:
/* Line 670 of lalr1.cc  */
#line 704 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            mod_ptr mod((yysemantic_stack_[(4) - (3)].mod)); (yysemantic_stack_[(4) - (3)].mod) = nullptr;
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = new ASTpathOp(*pop, std::move(mod), (yyloc));
        }
    break;

  case 102:
/* Line 670 of lalr1.cc  */
#line 711 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(2) - (1)].string)); (yysemantic_stack_[(2) - (1)].string) = nullptr;
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod)); (yysemantic_stack_[(2) - (2)].mod) = nullptr;
            driver.lexer->maybeVersion = token::CFDG2;
            rep_ptr item(new ASTpathCommand(*cmd, std::move(mod), nullptr, (yyloc)));
            (yyval.component) = item.release();
        }
    break;

  case 103:
/* Line 670 of lalr1.cc  */
#line 721 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            exp_ptr mod((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            (yyval.component) = new ASTpathOp(*pop, std::move(mod), (yyloc));
        }
    break;

  case 104:
/* Line 670 of lalr1.cc  */
#line 727 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(3) - (1)].string)); (yysemantic_stack_[(3) - (1)].string) = nullptr;
            exp_ptr mod;
            (yyval.component) = new ASTpathOp(*pop, std::move(mod), (yyloc));
        }
    break;

  case 105:
/* Line 670 of lalr1.cc  */
#line 733 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(3) - (1)].string)); (yysemantic_stack_[(3) - (1)].string) = nullptr;
            exp_ptr p((yysemantic_stack_[(3) - (2)].expression)); (yysemantic_stack_[(3) - (2)].expression) = nullptr;
            mod_ptr mod((yysemantic_stack_[(3) - (3)].mod)); (yysemantic_stack_[(3) - (3)].mod) = nullptr;
            rep_ptr item = driver.MakeElement(*cmd, std::move(mod),
                                              std::move(p), (yyloc), false);
            (yyval.component) = item.release();
        }
    break;

  case 106:
/* Line 670 of lalr1.cc  */
#line 742 "../../src-common/cfdg.ypp"
    { 
            exp_ptr args((yysemantic_stack_[(5) - (3)].expression)); (yysemantic_stack_[(5) - (3)].expression) = nullptr;
            mod_ptr mod((yysemantic_stack_[(5) - (5)].mod)); (yysemantic_stack_[(5) - (5)].mod) = nullptr;
            str_ptr func(new std::string("if"));
            args.reset(driver.MakeFunction(std::move(func), std::move(args), (yylocation_stack_[(5) - (1)]), (yylocation_stack_[(5) - (3)]), false));
            static const std::string ifstr("if");
            rep_ptr item = driver.MakeElement(ifstr, std::move(mod), std::move(args), (yyloc), false);
            (yyval.component) = item.release();
        }
    break;

  case 107:
/* Line 670 of lalr1.cc  */
#line 752 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer(nullptr);
            cont_ptr vars((yysemantic_stack_[(3) - (1)].bodyObj)); (yysemantic_stack_[(3) - (1)].bodyObj) = nullptr;
            exp_ptr exp((yysemantic_stack_[(3) - (2)].expression)); (yysemantic_stack_[(3) - (2)].expression) = nullptr;
            mod_ptr mod((yysemantic_stack_[(3) - (3)].mod)); (yysemantic_stack_[(3) - (3)].mod) = nullptr;
            exp.reset(driver.MakeLet((yylocation_stack_[(3) - (1)]), std::move(vars), std::move(exp)));      // must do unconditionally
            static const std::string letstr("let");
            rep_ptr item = driver.MakeElement(letstr, std::move(mod), std::move(exp), (yyloc), false);
            (yyval.component) = item.release();
        }
    break;

  case 108:
/* Line 670 of lalr1.cc  */
#line 763 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(4) - (2)].string)); (yysemantic_stack_[(4) - (2)].string) = nullptr;
            exp_ptr p((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            mod_ptr mod((yysemantic_stack_[(4) - (4)].mod)); (yysemantic_stack_[(4) - (4)].mod) = nullptr;
            rep_ptr item = driver.MakeElement(*cmd, std::move(mod), std::move(p), (yyloc), true);
            (yyval.component) = item.release();
        }
    break;

  case 109:
/* Line 670 of lalr1.cc  */
#line 773 "../../src-common/cfdg.ypp"
    { }
    break;

  case 110:
/* Line 670 of lalr1.cc  */
#line 775 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 111:
/* Line 670 of lalr1.cc  */
#line 781 "../../src-common/cfdg.ypp"
    { }
    break;

  case 112:
/* Line 670 of lalr1.cc  */
#line 783 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 113:
/* Line 670 of lalr1.cc  */
#line 789 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer(driver.switchStack.top());
        }
    break;

  case 116:
/* Line 670 of lalr1.cc  */
#line 800 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(1) - (1)].component); 
        }
    break;

  case 117:
/* Line 670 of lalr1.cc  */
#line 804 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(1) - (1)].defObj);
        }
    break;

  case 118:
/* Line 670 of lalr1.cc  */
#line 808 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(1) - (1)].loopObj);
            driver.pop_repContainer((yysemantic_stack_[(1) - (1)].loopObj));
            if ((yysemantic_stack_[(1) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(1) - (1)].loopObj);
                (yyval.component) = nullptr;
            }
        }
    break;

  case 119:
/* Line 670 of lalr1.cc  */
#line 817 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            driver.push_repContainer((yysemantic_stack_[(2) - (1)].loopObj)->mFinallyBody);
        }
    break;

  case 120:
/* Line 670 of lalr1.cc  */
#line 820 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].loopObj));
            (yyval.component) = (yysemantic_stack_[(4) - (1)].loopObj);
            if ((yysemantic_stack_[(4) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(4) - (1)].loopObj);
                (yyval.component) = nullptr;
            }
        }
    break;

  case 121:
/* Line 670 of lalr1.cc  */
#line 829 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].ifObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].ifObj));
            if ((yysemantic_stack_[(2) - (1)].ifObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].ifObj);
                (yyval.component) = nullptr;
            }
        }
    break;

  case 122:
/* Line 670 of lalr1.cc  */
#line 838 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].ifObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].ifObj));
            if ((yysemantic_stack_[(2) - (1)].ifObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].ifObj);
                (yyval.component) = nullptr;
            }
        }
    break;

  case 123:
/* Line 670 of lalr1.cc  */
#line 847 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].component);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].component));
            if ((yysemantic_stack_[(2) - (1)].component)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].component);
                (yyval.component) = nullptr;
            }
        }
    break;

  case 124:
/* Line 670 of lalr1.cc  */
#line 857 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].switchObj);
            (yysemantic_stack_[(4) - (1)].switchObj)->unify();
            driver.switchStack.pop();
        }
    break;

  case 125:
/* Line 670 of lalr1.cc  */
#line 863 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = nullptr;
        }
    break;

  case 126:
/* Line 670 of lalr1.cc  */
#line 870 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 127:
/* Line 670 of lalr1.cc  */
#line 871 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 128:
/* Line 670 of lalr1.cc  */
#line 872 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 129:
/* Line 670 of lalr1.cc  */
#line 876 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 130:
/* Line 670 of lalr1.cc  */
#line 878 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(2) - (1)].loopObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            if ((yysemantic_stack_[(2) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].loopObj);
                (yyval.component) = nullptr;
            }
        }
    break;

  case 131:
/* Line 670 of lalr1.cc  */
#line 886 "../../src-common/cfdg.ypp"
    {
            if (driver.lexer->maybeVersion == token::CFDG2) {
                error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            } else {
                driver.lexer->maybeVersion = token::CFDG3;
            }
            (yyval.component) = nullptr;
            YYABORT;
        }
    break;

  case 132:
/* Line 670 of lalr1.cc  */
#line 898 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 133:
/* Line 670 of lalr1.cc  */
#line 899 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 136:
/* Line 670 of lalr1.cc  */
#line 902 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 141:
/* Line 670 of lalr1.cc  */
#line 910 "../../src-common/cfdg.ypp"
    {
            // parse loop mod and loop body with loop index in scope
            mod_ptr loopmod((yysemantic_stack_[(3) - (2)].mod)); (yysemantic_stack_[(3) - (2)].mod) = nullptr;
            (yysemantic_stack_[(3) - (1)].loopObj)->mChildChange.grab(loopmod.get());
            (yyval.loopObj) = (yysemantic_stack_[(3) - (1)].loopObj);
            // loopmod gets deleted
        }
    break;

  case 142:
/* Line 670 of lalr1.cc  */
#line 920 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 144:
/* Line 670 of lalr1.cc  */
#line 927 "../../src-common/cfdg.ypp"
    { }
    break;

  case 145:
/* Line 670 of lalr1.cc  */
#line 929 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 146:
/* Line 670 of lalr1.cc  */
#line 935 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (1)].string)); (yysemantic_stack_[(2) - (1)].string) = nullptr;
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod)); (yysemantic_stack_[(2) - (2)].mod) = nullptr;
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, nullptr, (yylocation_stack_[(2) - (1)])));
            (yyval.component) = new ASTreplacement(*r, r->entropyVal, std::move(mod), (yyloc));
        }
    break;

  case 147:
/* Line 670 of lalr1.cc  */
#line 944 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 148:
/* Line 670 of lalr1.cc  */
#line 946 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].loopObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            if ((yysemantic_stack_[(2) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].loopObj);
                (yyval.component) = nullptr;
            }
        }
    break;

  case 149:
/* Line 670 of lalr1.cc  */
#line 957 "../../src-common/cfdg.ypp"
    { ++driver.mLocalStackDepth; }
    break;

  case 150:
/* Line 670 of lalr1.cc  */
#line 957 "../../src-common/cfdg.ypp"
    {
            str_ptr cstr((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            exp_ptr count(new ASTreal(*cstr, (yylocation_stack_[(4) - (1)])));
            mod_ptr mod((yysemantic_stack_[(4) - (4)].mod)); (yysemantic_stack_[(4) - (4)].mod) = nullptr;
            static const std::string dummyvar("~~inaccessiblevar~~");
            --driver.mLocalStackDepth;
            driver.lexer->maybeVersion = token::CFDG2;
            loop_ptr loop(new ASTloop(driver.StringToShape(dummyvar, (yylocation_stack_[(4) - (2)]), false), 
                                      dummyvar, (yylocation_stack_[(4) - (2)]), std::move(count), (yyloc), std::move(mod)));
            driver.push_repContainer(loop->mLoopBody);
            (yyval.loopObj) = loop.release();
        }
    break;

  case 151:
/* Line 670 of lalr1.cc  */
#line 972 "../../src-common/cfdg.ypp"
    {
            str_ptr var((yysemantic_stack_[(4) - (2)].string)); (yysemantic_stack_[(4) - (2)].string) = nullptr;
            exp_ptr index((yysemantic_stack_[(4) - (4)].expression)); (yysemantic_stack_[(4) - (4)].expression) = nullptr;
            int nameIndex = driver.StringToShape(*var, (yylocation_stack_[(4) - (2)]), false);
            loop_ptr loop(new ASTloop(nameIndex, *var, (yylocation_stack_[(4) - (2)]), std::move(index), (yylocation_stack_[(4) - (4)]), nullptr));
            driver.push_repContainer(loop->mLoopBody);
            (yyval.loopObj) = loop.release();
        }
    break;

  case 152:
/* Line 670 of lalr1.cc  */
#line 981 "../../src-common/cfdg.ypp"
    {
            exp_ptr index((yysemantic_stack_[(4) - (4)].expression)); (yysemantic_stack_[(4) - (4)].expression) = nullptr;
            static const std::string dummyvar("~~inaccessiblevar~~");
            loop_ptr loop(new ASTloop(driver.StringToShape(dummyvar, (yylocation_stack_[(4) - (1)]), false), 
                                      dummyvar, (yylocation_stack_[(4) - (2)]), std::move(index), (yylocation_stack_[(4) - (4)]), nullptr));
            driver.push_repContainer(loop->mLoopBody);
            (yyval.loopObj) = loop.release();
            error((yylocation_stack_[(4) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 153:
/* Line 670 of lalr1.cc  */
#line 991 "../../src-common/cfdg.ypp"
    {
            exp_ptr count((yysemantic_stack_[(2) - (2)].expression)); (yysemantic_stack_[(2) - (2)].expression) = nullptr;
            static const std::string dummyvar("~~inaccessiblevar~~");
            loop_ptr loop(new ASTloop(driver.StringToShape(dummyvar, (yylocation_stack_[(2) - (1)]), false), 
                                      dummyvar, (yylocation_stack_[(2) - (1)]), std::move(count), (yylocation_stack_[(2) - (2)]), nullptr));
            driver.push_repContainer(loop->mLoopBody);
            (yyval.loopObj) = loop.release();
        }
    break;

  case 154:
/* Line 670 of lalr1.cc  */
#line 1002 "../../src-common/cfdg.ypp"
    {
            exp_ptr cond((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            if_ptr ifHeader(new ASTif(std::move(cond), (yylocation_stack_[(4) - (3)])));
            driver.push_repContainer(ifHeader->mThenBody);
            (yyval.ifObj) = ifHeader.release();
        }
    break;

  case 155:
/* Line 670 of lalr1.cc  */
#line 1011 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ifObj));
            driver.push_repContainer((yysemantic_stack_[(3) - (1)].ifObj)->mElseBody);
            (yyval.ifObj) = (yysemantic_stack_[(3) - (1)].ifObj);
        }
    break;

  case 156:
/* Line 670 of lalr1.cc  */
#line 1019 "../../src-common/cfdg.ypp"
    {
            exp_ptr mods((yysemantic_stack_[(2) - (2)].expression)); (yysemantic_stack_[(2) - (2)].expression) = nullptr;
            if ((yysemantic_stack_[(2) - (1)].modToken) != ASTmodTerm::transform)
                error((yylocation_stack_[(2) - (1)]), "Syntax error");
            ASTtransform* trans = new ASTtransform((yyloc), std::move(mods));
            driver.push_repContainer(trans->mBody);
            (yyval.component) = trans;
        }
    break;

  case 157:
/* Line 670 of lalr1.cc  */
#line 1027 "../../src-common/cfdg.ypp"
    {
            exp_ptr mods((yysemantic_stack_[(2) - (2)].expression)); (yysemantic_stack_[(2) - (2)].expression) = nullptr;
            ASTtransform* trans = new ASTtransform((yyloc), std::move(mods));
            trans->mClone = true;
            driver.push_repContainer(trans->mBody);
            (yyval.component) = trans;
        }
    break;

  case 158:
/* Line 670 of lalr1.cc  */
#line 1037 "../../src-common/cfdg.ypp"
    {
            exp_ptr caseVal((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            switch_ptr switchHeader(new ASTswitch(std::move(caseVal), (yylocation_stack_[(4) - (3)])));
            driver.switchStack.push(switchHeader.get());
            (yyval.switchObj) = switchHeader.release();
        }
    break;

  case 159:
/* Line 670 of lalr1.cc  */
#line 1046 "../../src-common/cfdg.ypp"
    {
            exp_ptr valExp((yysemantic_stack_[(3) - (2)].expression)); (yysemantic_stack_[(3) - (2)].expression) = nullptr;
            
            double val = 0.0;
            try {
                if (valExp->evaluate(&val, 1) != 1) {
                    driver.error((yylocation_stack_[(3) - (2)]), "Case expression is not a single, numeric expression");
                } else {
                    int intval = static_cast<int>(floor(val));
                    ASTswitch::switchMap& caseMap = driver.switchStack.top()->mCaseStatements;
                    
                    if (caseMap.count(intval)) {
                        driver.error((yylocation_stack_[(3) - (2)]), "Case value already in use");
                        driver.push_repContainer(*(caseMap[intval]));
                    } else {
                        cont_ptr caseBody(new ASTrepContainer());
                        driver.push_repContainer(*(caseBody.get()));
                        std::pair<int, cont_ptr> p(intval, std::move(caseBody));
                        caseMap.insert(std::move(p));
                    }
                }
            }
            catch (DeferUntilRuntime&) {
                driver.error((yylocation_stack_[(3) - (2)]), "Case expression is not constant");
            }
            (yyval.modToken) = 0;
        }
    break;

  case 160:
/* Line 670 of lalr1.cc  */
#line 1074 "../../src-common/cfdg.ypp"
    {
            if (!driver.switchStack.top()->mElseBody.mBody.empty()) {
                driver.error((yyloc), "There can only be one 'else:' clause");
            } else {
                driver.push_repContainer(driver.switchStack.top()->mElseBody);
            }
            (yyval.modToken) = 0;
        }
    break;

  case 161:
/* Line 670 of lalr1.cc  */
#line 1085 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod)); (yysemantic_stack_[(3) - (2)].mod) = nullptr;
            (yyval.mod) = driver.MakeModification(std::move(mod), (yyloc), true);
        }
    break;

  case 162:
/* Line 670 of lalr1.cc  */
#line 1090 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod)); (yysemantic_stack_[(3) - (2)].mod) = nullptr;
            (yyval.mod) = driver.MakeModification(std::move(mod), (yyloc), false);
        }
    break;

  case 163:
/* Line 670 of lalr1.cc  */
#line 1097 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod)); (yysemantic_stack_[(3) - (2)].mod) = nullptr;
            (yyval.mod) = driver.MakeModification(std::move(mod), (yyloc), true);
        }
    break;

  case 164:
/* Line 670 of lalr1.cc  */
#line 1102 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(5) - (3)].mod)); (yysemantic_stack_[(5) - (3)].mod) = nullptr;
            (yyval.mod) = driver.MakeModification(std::move(mod), (yyloc), false);
        }
    break;

  case 165:
/* Line 670 of lalr1.cc  */
#line 1109 "../../src-common/cfdg.ypp"
    {
            term_ptr mod((yysemantic_stack_[(2) - (2)].term)); (yysemantic_stack_[(2) - (2)].term) = nullptr;
            driver.MakeModTerm((yysemantic_stack_[(2) - (1)].mod)->modExp, std::move(mod));
            (yyval.mod) = (yysemantic_stack_[(2) - (1)].mod);
        }
    break;

  case 166:
/* Line 670 of lalr1.cc  */
#line 1114 "../../src-common/cfdg.ypp"
    {
            static const yy::location def;
            ASTmodification* m = new ASTmodification(def);
            m->flags = 0;
            (yyval.mod) = m;
        }
    break;

  case 167:
/* Line 670 of lalr1.cc  */
#line 1123 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].expression)); (yysemantic_stack_[(2) - (2)].expression) = nullptr;
            (yyval.term) = new ASTmodTerm(static_cast<ASTmodTerm::modTypeEnum>((yysemantic_stack_[(2) - (1)].modToken)), mod.release(), (yyloc));
        }
    break;

  case 168:
/* Line 670 of lalr1.cc  */
#line 1128 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(3) - (2)].expression)); (yysemantic_stack_[(3) - (2)].expression) = nullptr;
            if ((yysemantic_stack_[(3) - (1)].modToken) < ASTmodTerm::hue || (yysemantic_stack_[(3) - (1)].modToken) > ASTmodTerm::alpha) {
                error((yyloc), "The target operator can only be applied to color adjustments");
                (yyval.term) = nullptr;
            } else {
                (yyval.term) = new ASTmodTerm(static_cast<ASTmodTerm::modTypeEnum>((yysemantic_stack_[(3) - (1)].modToken) + 4), mod.release(), (yyloc));
            }
        }
    break;

  case 169:
/* Line 670 of lalr1.cc  */
#line 1138 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string)); (yysemantic_stack_[(2) - (2)].string) = nullptr;
            (yyval.term) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 170:
/* Line 670 of lalr1.cc  */
#line 1143 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string)); (yysemantic_stack_[(2) - (2)].string) = nullptr;
            (yyval.term) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 171:
/* Line 670 of lalr1.cc  */
#line 1150 "../../src-common/cfdg.ypp"
    {
            ASTrepContainer* tempHolder = new ASTrepContainer();
            driver.push_repContainer(*tempHolder);
            (yyval.bodyObj) = tempHolder;
        }
    break;

  case 172:
/* Line 670 of lalr1.cc  */
#line 1158 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = (yysemantic_stack_[(5) - (4)].expression);
        }
    break;

  case 175:
/* Line 670 of lalr1.cc  */
#line 1170 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].defObj));
        }
    break;

  case 176:
/* Line 670 of lalr1.cc  */
#line 1176 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTexpression::Append((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 177:
/* Line 670 of lalr1.cc  */
#line 1180 "../../src-common/cfdg.ypp"
    { 
            (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); 
        }
    break;

  case 178:
/* Line 670 of lalr1.cc  */
#line 1187 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = (yysemantic_stack_[(3) - (1)].expression)->append(new ASTparen((yysemantic_stack_[(3) - (3)].expression)));
        }
    break;

  case 179:
/* Line 670 of lalr1.cc  */
#line 1191 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = new ASTcons(new ASTparen((yysemantic_stack_[(1) - (1)].expression)), nullptr);
        }
    break;

  case 180:
/* Line 670 of lalr1.cc  */
#line 1197 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 181:
/* Line 670 of lalr1.cc  */
#line 1199 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 182:
/* Line 670 of lalr1.cc  */
#line 1201 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 183:
/* Line 670 of lalr1.cc  */
#line 1203 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 184:
/* Line 670 of lalr1.cc  */
#line 1205 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), nullptr);; }
    break;

  case 185:
/* Line 670 of lalr1.cc  */
#line 1207 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), nullptr);; }
    break;

  case 186:
/* Line 670 of lalr1.cc  */
#line 1209 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression))); (yysemantic_stack_[(3) - (1)].expression) = nullptr; (yysemantic_stack_[(3) - (3)].expression) = nullptr;
            (yyval.expression) = new ASTfunction("rand", std::move(pair), driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 187:
/* Line 670 of lalr1.cc  */
#line 1214 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression))); (yysemantic_stack_[(3) - (1)].expression) = nullptr; (yysemantic_stack_[(3) - (3)].expression) = nullptr;
            (yyval.expression) = new ASTfunction("rand+/-", std::move(pair), driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 188:
/* Line 670 of lalr1.cc  */
#line 1221 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); (yysemantic_stack_[(1) - (1)].string) = nullptr; }
    break;

  case 189:
/* Line 670 of lalr1.cc  */
#line 1223 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 190:
/* Line 670 of lalr1.cc  */
#line 1225 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 191:
/* Line 670 of lalr1.cc  */
#line 1227 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression))); (yysemantic_stack_[(3) - (1)].expression) = nullptr; (yysemantic_stack_[(3) - (3)].expression) = nullptr;
            (yyval.expression) = new ASTfunction("rand", std::move(pair), driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 192:
/* Line 670 of lalr1.cc  */
#line 1232 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression))); (yysemantic_stack_[(3) - (1)].expression) = nullptr; (yysemantic_stack_[(3) - (3)].expression) = nullptr;
            (yyval.expression) = new ASTfunction("rand+/-", std::move(pair), driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 193:
/* Line 670 of lalr1.cc  */
#line 1237 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression));   }
    break;

  case 194:
/* Line 670 of lalr1.cc  */
#line 1239 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('+', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 195:
/* Line 670 of lalr1.cc  */
#line 1241 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('-', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 196:
/* Line 670 of lalr1.cc  */
#line 1243 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('_', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 197:
/* Line 670 of lalr1.cc  */
#line 1245 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('*', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 198:
/* Line 670 of lalr1.cc  */
#line 1247 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('/', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 199:
/* Line 670 of lalr1.cc  */
#line 1249 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), nullptr); }
    break;

  case 200:
/* Line 670 of lalr1.cc  */
#line 1251 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), nullptr); }
    break;

  case 201:
/* Line 670 of lalr1.cc  */
#line 1253 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('!', (yysemantic_stack_[(2) - (2)].expression), nullptr); }
    break;

  case 202:
/* Line 670 of lalr1.cc  */
#line 1255 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('^', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 203:
/* Line 670 of lalr1.cc  */
#line 1257 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('<', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 204:
/* Line 670 of lalr1.cc  */
#line 1259 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('L', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 205:
/* Line 670 of lalr1.cc  */
#line 1261 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('>', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 206:
/* Line 670 of lalr1.cc  */
#line 1263 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('G', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 207:
/* Line 670 of lalr1.cc  */
#line 1265 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('=', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 208:
/* Line 670 of lalr1.cc  */
#line 1267 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('n', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 209:
/* Line 670 of lalr1.cc  */
#line 1269 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('&', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 210:
/* Line 670 of lalr1.cc  */
#line 1271 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('|', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 211:
/* Line 670 of lalr1.cc  */
#line 1273 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('X', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 212:
/* Line 670 of lalr1.cc  */
#line 1275 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 213:
/* Line 670 of lalr1.cc  */
#line 1277 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].mod); }
    break;

  case 214:
/* Line 670 of lalr1.cc  */
#line 1281 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 215:
/* Line 670 of lalr1.cc  */
#line 1283 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 216:
/* Line 670 of lalr1.cc  */
#line 1285 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 217:
/* Line 670 of lalr1.cc  */
#line 1287 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression))); (yysemantic_stack_[(3) - (1)].expression) = nullptr; (yysemantic_stack_[(3) - (3)].expression) = nullptr;
            (yyval.expression) = new ASTfunction("rand", std::move(pair), driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 218:
/* Line 670 of lalr1.cc  */
#line 1292 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression))); (yysemantic_stack_[(3) - (1)].expression) = nullptr; (yysemantic_stack_[(3) - (3)].expression) = nullptr;
            (yyval.expression) = new ASTfunction("rand+/-", std::move(pair), driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 219:
/* Line 670 of lalr1.cc  */
#line 1297 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('+', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 220:
/* Line 670 of lalr1.cc  */
#line 1299 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('-', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 221:
/* Line 670 of lalr1.cc  */
#line 1301 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('_', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 222:
/* Line 670 of lalr1.cc  */
#line 1303 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('*', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 223:
/* Line 670 of lalr1.cc  */
#line 1305 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('/', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 224:
/* Line 670 of lalr1.cc  */
#line 1307 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), nullptr); }
    break;

  case 225:
/* Line 670 of lalr1.cc  */
#line 1309 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), nullptr); }
    break;

  case 226:
/* Line 670 of lalr1.cc  */
#line 1311 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('!', (yysemantic_stack_[(2) - (2)].expression), nullptr); }
    break;

  case 227:
/* Line 670 of lalr1.cc  */
#line 1313 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('^', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 228:
/* Line 670 of lalr1.cc  */
#line 1315 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('<', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 229:
/* Line 670 of lalr1.cc  */
#line 1317 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('L', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 230:
/* Line 670 of lalr1.cc  */
#line 1319 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('>', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 231:
/* Line 670 of lalr1.cc  */
#line 1321 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('G', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 232:
/* Line 670 of lalr1.cc  */
#line 1323 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('=', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 233:
/* Line 670 of lalr1.cc  */
#line 1325 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('n', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 234:
/* Line 670 of lalr1.cc  */
#line 1327 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('&', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 235:
/* Line 670 of lalr1.cc  */
#line 1329 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('|', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 236:
/* Line 670 of lalr1.cc  */
#line 1331 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('X', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 237:
/* Line 670 of lalr1.cc  */
#line 1333 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 238:
/* Line 670 of lalr1.cc  */
#line 1335 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].mod); }
    break;

  case 239:
/* Line 670 of lalr1.cc  */
#line 1339 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string)); (yysemantic_stack_[(3) - (1)].string) = nullptr;
            (yyval.expression) = driver.MakeFunction(std::move(func), nullptr, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 240:
/* Line 670 of lalr1.cc  */
#line 1344 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            (yyval.expression) = driver.MakeFunction(std::move(func), std::move(args), (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), true);
        }
    break;

  case 241:
/* Line 670 of lalr1.cc  */
#line 1350 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            (yyval.expression) = driver.MakeArray(std::move(func), std::move(args), (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]));
        }
    break;

  case 242:
/* Line 670 of lalr1.cc  */
#line 1356 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            (yyval.expression) = driver.MakeFunction(std::move(func), std::move(args), (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 243:
/* Line 670 of lalr1.cc  */
#line 1362 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer(nullptr);
            cont_ptr vars((yysemantic_stack_[(2) - (1)].bodyObj)); (yysemantic_stack_[(2) - (1)].bodyObj) = nullptr;
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression)); (yysemantic_stack_[(2) - (2)].expression) = nullptr;
            (yyval.expression) = driver.MakeLet((yylocation_stack_[(2) - (1)]), std::move(vars), std::move(exp));
        }
    break;

  case 244:
/* Line 670 of lalr1.cc  */
#line 1369 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string)); (yysemantic_stack_[(1) - (1)].string) = nullptr;
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 245:
/* Line 670 of lalr1.cc  */
#line 1376 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string)); (yysemantic_stack_[(3) - (1)].string) = nullptr;
            (yyval.expression) = driver.MakeFunction(std::move(func), nullptr, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 246:
/* Line 670 of lalr1.cc  */
#line 1381 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            (yyval.expression) = driver.MakeFunction(std::move(func), std::move(args), (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 247:
/* Line 670 of lalr1.cc  */
#line 1387 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            (yyval.expression) = driver.MakeArray(std::move(func), std::move(args), (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]));
        }
    break;

  case 248:
/* Line 670 of lalr1.cc  */
#line 1393 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            (yyval.expression) = driver.MakeFunction(std::move(func), std::move(args), (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 249:
/* Line 670 of lalr1.cc  */
#line 1399 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            exp_ptr args(new ASTexpression((yyloc), false, false, AST::ReuseType));
            (yyval.expression) = driver.MakeFunction(std::move(func), std::move(args), (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 250:
/* Line 670 of lalr1.cc  */
#line 1405 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer(nullptr);
            cont_ptr vars((yysemantic_stack_[(2) - (1)].bodyObj)); (yysemantic_stack_[(2) - (1)].bodyObj) = nullptr;
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression)); (yysemantic_stack_[(2) - (2)].expression) = nullptr;
            (yyval.expression) = driver.MakeLet((yylocation_stack_[(2) - (1)]), std::move(vars), std::move(exp));
        }
    break;

  case 251:
/* Line 670 of lalr1.cc  */
#line 1412 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string)); (yysemantic_stack_[(1) - (1)].string) = nullptr;
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 252:
/* Line 670 of lalr1.cc  */
#line 1419 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 253:
/* Line 670 of lalr1.cc  */
#line 1421 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(1) - (1)].string); }
    break;


/* Line 670 of lalr1.cc  */
#line 2777 "cfdg.tab.cpp"
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
    while (1 < yystate_stack_.height ())
      {
        yydestruct_ ("Cleanup: popping",
                     yystos_[yystate_stack_[0]],
                     &yysemantic_stack_[0],
                     &yylocation_stack_[0]);
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
        if (yychar != yyempty_)
          {
            /* Make sure we have latest lookahead translation.  See
               comments at user semantic actions for why this is
               necessary.  */
            yytoken = yytranslate_ (yychar);
            yydestruct_ (YY_NULL, yytoken, &yylval, &yylloc);
          }

        while (1 < yystate_stack_.height ())
          {
            yydestruct_ (YY_NULL,
                         yystos_[yystate_stack_[0]],
                         &yysemantic_stack_[0],
                         &yylocation_stack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  // Generate an error message.
  std::string
  CfdgParser::yysyntax_error_ (int, int)
  {
    return YY_("syntax error");
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int CfdgParser::yypact_ninf_ = -267;
  const short int
  CfdgParser::yypact_[] =
  {
       116,  -267,  -267,    26,  1256,  1277,  -267,     6,  -267,    67,
     104,    46,    23,    10,  -267,    90,   276,  -267,    10,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,   122,  -267,   132,
    -267,   150,     5,   216,   123,   119,    10,    80,   276,   140,
      10,  -267,  -267,  -267,  -267,  -267,  -267,  -267,   597,  -267,
     143,  -267,  -267,  -267,   145,   154,  -267,  -267,   265,   166,
     237,   241,  -267,  -267,  -267,  -267,  -267,  -267,  -267,   245,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,   258,   262,   269,
     280,  -267,   284,  -267,    33,   285,  -267,  -267,  -267,   269,
     269,   319,  -267,   308,   276,  -267,   297,  -267,   302,  -267,
     293,   597,  -267,   597,   597,   597,   310,  -267,   312,  1012,
    -267,  -267,   177,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
      38,   120,  -267,   294,   360,   399,   262,  -267,   333,    33,
    -267,   366,     9,  -267,    17,  -267,    34,  -267,  -267,    61,
    -267,   368,   373,  -267,  -267,  -267,   597,   435,   597,   328,
     328,   328,   733,  -267,   124,   126,  -267,   597,   597,   597,
     597,   597,   597,   597,   597,   597,   597,   597,   597,   597,
     597,   597,   597,   597,   597,   206,   555,   331,   335,   597,
     534,     7,   344,  -267,   175,  -267,   597,  -267,  -267,  -267,
    -267,   383,   262,   456,   456,   456,   338,   312,   258,   300,
     322,   388,     8,  -267,  -267,  -267,  -267,   347,  -267,  -267,
    -267,   271,    10,  -267,  -267,  -267,  -267,   392,     4,   243,
    -267,  -267,  -267,  -267,   185,    10,   340,  -267,   618,  -267,
     618,   618,   597,  -267,  -267,    73,  1043,  -267,  -267,  -267,
      74,  -267,    93,  -267,  -267,  -267,  -267,     9,  -267,  -267,
    -267,   764,   341,  -267,   160,   640,  -267,   155,  -267,   401,
     403,  -267,   351,  -267,   480,   480,   649,   649,   649,   649,
    1197,  1197,  1157,  1113,  1067,  1012,   165,   165,   165,   328,
     328,   328,   258,   410,    88,  1012,   597,   597,  1012,  1012,
    -267,  -267,   477,  -267,  1012,  -267,   456,  -267,   407,  -267,
    -267,  -267,  -267,   262,   262,  -267,  -267,   365,   370,  -267,
     367,  -267,   388,   388,   597,   312,   388,   162,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,   363,  -267,  -267,  -267,  -267,  -267,   372,   372,   372,
     795,   618,  -267,   618,   618,   618,   618,   618,   618,   618,
     618,   618,   618,   618,   618,   618,   618,   618,   618,   618,
     421,  -267,  -267,  -267,  -267,  -267,  -267,   369,   576,   262,
     597,   597,   826,   857,  -267,   888,   456,  -267,   346,  -267,
     117,  -267,  -267,   597,   498,   597,  -267,  -267,   919,  -267,
     342,   388,   388,  -267,    10,   318,   178,   379,  -267,  1043,
     600,   600,   710,   710,   710,   710,  1217,  1217,  1177,  1135,
    1090,   236,   236,   236,   372,   372,   372,  -267,    92,  -267,
     950,  -267,  1012,  1012,   262,  -267,  -267,  -267,  -267,   371,
     597,  -267,  -267,   456,   981,  -267,   161,   671,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,   702,  -267,
    -267,  -267,  -267,  -267
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
       0,     6,    16,     9,    10,     8,    15,    63,     0,    64,
      13,    98,    14,    41,     0,     0,    11,    12,    52,     0,
      71,    79,    27,   166,   166,    55,    28,    53,    26,     0,
      29,    45,    46,    42,    54,   143,   100,    96,     0,     0,
      90,    75,    90,    66,     0,     0,    39,    37,    65,     0,
       0,     0,    40,     0,     0,    38,     0,   171,   251,   188,
       0,     0,   189,     0,     0,     0,   166,   213,     0,    56,
     190,    69,     0,    98,    98,    34,    35,    36,    72,    33,
       0,     0,    30,     0,     0,     0,    51,    50,     0,     0,
      68,     0,     0,    76,     0,    86,    85,    92,    88,     0,
      61,     0,     0,    58,    47,    43,     0,     0,     0,   201,
     199,   200,     0,   166,     0,     0,   250,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   252,     0,   253,     0,    70,     0,   117,   116,    97,
     125,   118,     0,     0,     0,     0,     0,     0,    96,     0,
       0,     0,     0,   162,   165,   161,   252,     0,    73,   147,
     142,     0,     0,   134,   135,   138,   140,   139,   252,     0,
      80,   129,    99,   131,     0,     0,     0,   214,     0,   215,
       0,     0,     0,    95,   238,     0,   179,   216,    49,    60,
       0,    57,     0,    84,    82,    83,    81,     0,    91,    62,
      59,     0,     0,   245,     0,     0,   212,     0,   163,     0,
       0,   175,     0,   174,   191,   192,   204,   203,   206,   205,
     207,   208,   209,   210,   211,   193,   195,   194,   196,   197,
     198,   202,    96,     0,   251,   153,     0,     0,   157,   156,
     127,   126,     0,   128,    67,   119,     0,    98,   121,   110,
     122,   123,   114,     0,     0,    77,    78,     0,   244,   180,
       0,   181,     0,     0,     0,     0,   167,   177,   183,   169,
     170,   149,   143,   148,   145,   146,   137,   136,   133,   132,
     166,     0,   100,   112,   130,   102,    94,   226,   224,   225,
       0,     0,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      89,    89,    87,   248,   249,   246,   247,     0,     0,     0,
       0,     0,     0,     0,   104,     0,     0,   141,     0,   155,
       0,   107,   105,     0,     0,     0,   184,   185,     0,   243,
     176,     0,     0,   168,     0,     0,     0,     0,   237,   178,
     217,   218,   229,   228,   231,   230,   232,   233,   234,   235,
     236,   220,   219,   221,   222,   223,   227,   164,   251,   173,
       0,   108,   152,   151,   154,   158,   103,   120,   109,     0,
       0,   124,   113,     0,     0,   239,     0,     0,   182,   186,
     187,   150,   144,   101,   111,   172,   106,   160,     0,   115,
     242,   240,   241,   159
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yypgoto_[] =
  {
      -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
     427,   -28,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,   428,  -151,  -267,  -267,  -267,   432,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,   193,   106,   362,   -25,  -185,  -106,
     110,   227,  -267,  -192,  -267,  -267,  -267,   -91,  -267,  -267,
    -267,  -267,  -267,   130,  -267,   244,  -267,  -113,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,   -13,   -77,   -39,  -267,   -82,
    -188,  -267,    86,  -267,  -141,  -266,   -85,  -186,  -267,   -96,
     -83
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yydefgoto_[] =
  {
        -1,     3,     4,     5,    41,    19,    20,    42,    21,    43,
      22,    73,    94,    45,    23,    24,    25,    26,    46,    47,
      48,   186,   187,    50,    51,    52,    27,    28,    54,    55,
      56,    57,    29,    30,   138,   139,   130,    85,   126,   112,
     124,   221,   188,   298,   334,   380,   432,   299,   376,   190,
     222,   223,   191,   123,   323,   209,   210,   211,   394,   192,
     193,   194,   195,   196,   433,    65,   107,   120,   204,   108,
     156,   262,   263,   316,   235,   317,   109,   236,   318,   110,
     198
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char CfdgParser::yytable_ninf_ = -92;
  const short int
  CfdgParser::yytable_[] =
  {
        67,   127,   300,   301,   261,    74,   254,   199,   200,   303,
      92,   224,    91,   304,   327,   134,   149,    88,   150,   151,
     152,   189,    86,    87,    79,   121,     6,    95,   135,   237,
     197,    80,    58,    66,   319,   136,   243,    59,   320,   134,
     212,   225,   337,   244,   338,   339,   386,   387,   234,   238,
     390,   237,   135,   245,   128,   131,    62,   201,   202,   136,
     246,   251,   328,   255,   141,   142,   145,   154,   290,    63,
     234,    64,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
      88,   285,   282,    60,   288,   289,   137,   369,   371,    89,
      68,   294,    88,   203,   377,    63,    90,    64,   189,   189,
     247,   197,   197,   197,   257,   296,    69,   197,   197,   315,
       1,     2,   341,   247,   248,   439,   440,   389,   212,    83,
      61,   429,   237,   430,   237,   237,   342,   360,    84,   201,
     202,   225,   247,   201,   202,   259,   147,   340,    70,    82,
     147,   234,   260,   234,   234,   399,   361,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,   412,
     413,   414,   415,   416,   201,   202,    77,    84,    63,   431,
      64,    78,   205,    75,   427,   175,   391,   392,   176,   258,
     177,   378,   178,    76,   179,    97,   180,   201,   202,   325,
      93,   372,   373,   181,   111,   182,   113,   375,   183,   341,
     341,   206,   335,   184,   197,   114,   183,   261,   172,   173,
     367,   331,   174,   365,   451,   117,   381,   382,   393,   388,
     315,   315,   206,   292,   315,   240,   293,   183,   242,   185,
     443,   449,    60,   436,    81,   237,   332,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   234,   118,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   420,   224,   422,   423,   189,   237,   357,
     358,   396,   421,   359,   197,   140,   197,   206,   434,   119,
     437,   329,   183,   122,   330,    71,    72,   234,   175,   315,
     315,   176,   212,   177,   225,   178,   125,   179,    97,   180,
     206,   106,   207,   115,   116,   183,   181,    84,   182,   143,
     175,   183,   322,   176,   144,   177,   184,   178,   129,   179,
      97,   180,   132,   239,   206,   448,   207,   446,   181,   183,
     182,   197,   148,   183,   175,   146,   208,   176,   184,   177,
     147,   178,   305,   179,    97,   180,   391,   392,   213,   153,
     155,   214,   181,   215,   182,   216,   241,   183,   249,   217,
     442,   441,   184,   250,   306,   174,   218,   213,   207,   286,
     214,   183,   215,   287,   216,   295,   219,   291,   217,   302,
     321,   307,   326,   336,   364,   218,    97,   207,   428,   226,
     183,    83,    96,    88,   308,   219,   309,    97,   368,   310,
     370,   379,   220,   383,   330,    98,   385,   227,   384,   359,
     100,   -91,    44,    49,   417,   447,   311,    53,   312,   313,
     362,   444,   397,   228,   133,   252,   314,   229,    96,   230,
     231,   333,   395,    97,   419,   324,     0,   232,   106,     0,
       0,    98,   233,   227,   175,     0,   100,   176,     0,   177,
       0,   178,     0,   179,    97,   180,     0,     0,     0,   228,
       0,     0,   181,   229,   182,   230,   231,   183,     0,     0,
      96,     0,   184,   232,   106,    97,     0,     0,   253,     0,
       0,     0,     0,    98,     0,    99,     0,     0,   100,     0,
       0,    96,     0,     0,     0,     0,    97,   297,     0,     0,
       0,   101,     0,     0,    98,   102,   227,   103,   104,   100,
     169,   170,   171,   172,   173,   105,   106,   174,     0,     0,
     374,     0,   228,     0,    83,     0,   229,    96,   230,   231,
       0,     0,    97,     0,     0,     0,   232,   106,     0,     0,
      98,   435,    99,     0,     0,   100,     0,     0,    96,     0,
       0,     0,     0,    97,   283,     0,     0,     0,   101,     0,
       0,   284,   102,    99,   103,   104,   100,     0,     0,    96,
       0,     0,   105,   106,    97,   259,     0,     0,     0,   101,
       0,     0,   418,   102,    99,   103,   104,   100,     0,     0,
      96,     0,     0,   105,   106,    97,     0,     0,     0,     0,
     101,     0,     0,    98,   102,    99,   103,   104,   100,     0,
       0,    96,     0,     0,   105,   106,    97,     0,     0,     0,
       0,   101,     0,     0,    98,   102,   227,   103,   104,   100,
     354,   355,   356,   357,   358,   105,   106,   359,     0,     0,
       0,     0,   228,     0,   157,   158,   229,     0,   230,   231,
       0,     0,     0,   157,   158,     0,   232,   106,   159,   160,
     161,   162,   163,   164,     0,   165,   166,   167,     0,   168,
     169,   170,   171,   172,   173,   157,   158,   174,     0,   169,
     170,   171,   172,   173,     0,   366,   174,     0,     0,   159,
     160,   161,   162,   163,   164,     0,   165,   166,   167,     0,
     168,   169,   170,   171,   172,   173,   157,   158,   174,     0,
       0,     0,     0,     0,   343,   344,   452,     0,     0,     0,
     159,   160,   161,   162,   163,   164,     0,   165,   166,   167,
       0,   168,   169,   170,   171,   172,   173,   157,   158,   174,
     354,   355,   356,   357,   358,     0,   453,   359,     0,     0,
       0,   159,   160,   161,   162,   163,   164,     0,   165,   166,
     167,     0,   168,   169,   170,   171,   172,   173,   157,   158,
     174,     0,     0,     0,     0,     0,   256,     0,     0,     0,
       0,     0,   159,   160,   161,   162,   163,   164,     0,   165,
     166,   167,     0,   168,   169,   170,   171,   172,   173,   157,
     158,   174,     0,     0,     0,     0,     0,   363,     0,     0,
       0,     0,     0,   159,   160,   161,   162,   163,   164,     0,
     165,   166,   167,     0,   168,   169,   170,   171,   172,   173,
     157,   158,   174,     0,     0,     0,     0,     0,   398,     0,
       0,     0,     0,     0,   159,   160,   161,   162,   163,   164,
       0,   165,   166,   167,     0,   168,   169,   170,   171,   172,
     173,   157,   158,   174,     0,     0,     0,     0,     0,   424,
       0,     0,     0,     0,     0,   159,   160,   161,   162,   163,
     164,     0,   165,   166,   167,     0,   168,   169,   170,   171,
     172,   173,   157,   158,   174,     0,     0,     0,     0,     0,
     425,     0,     0,     0,     0,     0,   159,   160,   161,   162,
     163,   164,     0,   165,   166,   167,     0,   168,   169,   170,
     171,   172,   173,   157,   158,   174,     0,     0,     0,     0,
       0,   426,     0,     0,     0,     0,     0,   159,   160,   161,
     162,   163,   164,     0,   165,   166,   167,     0,   168,   169,
     170,   171,   172,   173,   157,   158,   174,     0,     0,     0,
       0,     0,   438,     0,     0,     0,     0,     0,   159,   160,
     161,   162,   163,   164,     0,   165,   166,   167,     0,   168,
     169,   170,   171,   172,   173,   157,   158,   174,     0,     0,
       0,     0,     0,   445,     0,     0,     0,     0,     0,   159,
     160,   161,   162,   163,   164,     0,   165,   166,   167,     0,
     168,   169,   170,   171,   172,   173,   157,   158,   174,     0,
       0,     0,     0,     0,   450,     0,     0,     0,     0,     0,
     159,   160,   161,   162,   163,   164,     0,   165,   166,   167,
       0,   168,   169,   170,   171,   172,   173,   343,   344,   174,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   345,   346,   347,   348,   349,   350,     0,   351,   352,
     353,   157,   158,   354,   355,   356,   357,   358,     0,     0,
     359,     0,     0,     0,     0,   159,   160,   161,   162,   163,
     164,     0,   165,   166,   343,   344,     0,   169,   170,   171,
     172,   173,     0,     0,   174,     0,     0,     0,   345,   346,
     347,   348,   349,   350,     0,   351,   352,   157,   158,     0,
     354,   355,   356,   357,   358,     0,     0,   359,     0,     0,
       0,   159,   160,   161,   162,   163,   164,     0,   165,   343,
     344,     0,     0,   169,   170,   171,   172,   173,     0,     0,
     174,     0,     0,   345,   346,   347,   348,   349,   350,     0,
     351,   157,   158,     0,     0,   354,   355,   356,   357,   358,
       0,     0,   359,     0,     0,   159,   160,   161,   162,   163,
     164,   343,   344,     0,     0,     0,     0,   169,   170,   171,
     172,   173,     0,     0,   174,   345,   346,   347,   348,   349,
     350,   157,   158,     0,     0,     0,     0,   354,   355,   356,
     357,   358,     0,     0,   359,   159,   160,   161,   162,     0,
       0,   343,   344,     0,     0,     0,     0,   169,   170,   171,
     172,   173,     0,     0,   174,   345,   346,   347,   348,     7,
       0,     0,     8,     9,    10,     0,     0,   354,   355,   356,
     357,   358,     0,     0,   359,    11,    12,    13,     0,    14,
      31,     0,    15,    32,    33,    34,     0,     0,    16,    17,
      18,     0,     0,     0,     0,     0,    35,     0,    36,     0,
      14,     0,     0,    37,     0,     0,     0,     0,     0,    38,
      39,    40
  };

  /* YYCHECK.  */
  const short int
  CfdgParser::yycheck_[] =
  {
        13,    78,   194,   195,   155,    18,   147,   113,   114,   197,
      38,   124,    37,   198,    10,     6,   101,    10,   103,   104,
     105,   112,    35,    36,    19,    64,     0,    40,    19,   125,
     112,    26,    26,    10,    26,    26,    19,    31,    30,     6,
     123,   124,   228,    26,   230,   231,   312,   313,   125,   126,
     316,   147,    19,    19,    79,    80,    10,    19,    20,    26,
      26,   146,    58,   148,    89,    90,    94,   106,    61,    59,
     147,    61,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
      10,   176,   175,    26,   179,   180,    63,   282,    10,    19,
      10,   186,    10,    65,   296,    59,    26,    61,   199,   200,
      49,   193,   194,   195,   153,   192,    26,   199,   200,   201,
       4,     5,    49,    49,    63,   391,   392,   315,   211,    10,
      26,    14,   228,    16,   230,   231,    63,    63,    58,    19,
      20,   224,    49,    19,    20,    19,    58,   232,    58,    26,
      58,   228,    26,   230,   231,   341,    63,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,    19,    20,    26,    58,    59,    62,
      61,    31,    62,    61,   376,     8,    24,    25,    11,    65,
      13,   297,    15,    61,    17,    18,    19,    19,    20,   212,
      60,   286,   287,    26,    61,    28,    61,   292,    31,    49,
      49,    26,   225,    36,   296,    61,    31,   368,    53,    54,
      65,    36,    57,    63,    63,    59,   303,   304,    66,   314,
     312,   313,    26,    58,   316,   129,    61,    31,   132,    62,
      62,   433,    26,   384,    28,   341,    61,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   341,    28,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   368,   397,   370,   371,   378,   384,    53,
      54,   330,   369,    57,   376,    10,   378,    26,   383,    58,
     385,    58,    31,    58,    61,    29,    30,   384,     8,   391,
     392,    11,   395,    13,   397,    15,    58,    17,    18,    19,
      26,    59,    28,    58,    59,    31,    26,    58,    28,    10,
       8,    31,    61,    11,    26,    13,    36,    15,    58,    17,
      18,    19,    58,    10,    26,   430,    28,   424,    26,    31,
      28,   433,    59,    31,     8,    58,    62,    11,    36,    13,
      58,    15,    62,    17,    18,    19,    24,    25,     8,    59,
      58,    11,    26,    13,    28,    15,    10,    31,    10,    19,
      62,   394,    36,    10,    62,    57,    26,     8,    28,    58,
      11,    31,    13,    58,    15,    12,    36,    53,    19,    61,
      53,    13,    10,    63,    63,    26,    18,    28,    62,    10,
      31,    10,    13,    10,    26,    36,    28,    18,    67,    31,
      10,    14,    62,    58,    61,    26,    59,    28,    58,    57,
      31,    10,     5,     5,    65,    64,    48,     5,    50,    51,
     247,    62,   332,    44,    82,    10,    58,    48,    13,    50,
      51,   224,   322,    18,   368,   211,    -1,    58,    59,    -1,
      -1,    26,    63,    28,     8,    -1,    31,    11,    -1,    13,
      -1,    15,    -1,    17,    18,    19,    -1,    -1,    -1,    44,
      -1,    -1,    26,    48,    28,    50,    51,    31,    -1,    -1,
      13,    -1,    36,    58,    59,    18,    -1,    -1,    63,    -1,
      -1,    -1,    -1,    26,    -1,    28,    -1,    -1,    31,    -1,
      -1,    13,    -1,    -1,    -1,    -1,    18,    61,    -1,    -1,
      -1,    44,    -1,    -1,    26,    48,    28,    50,    51,    31,
      50,    51,    52,    53,    54,    58,    59,    57,    -1,    -1,
      63,    -1,    44,    -1,    10,    -1,    48,    13,    50,    51,
      -1,    -1,    18,    -1,    -1,    -1,    58,    59,    -1,    -1,
      26,    63,    28,    -1,    -1,    31,    -1,    -1,    13,    -1,
      -1,    -1,    -1,    18,    19,    -1,    -1,    -1,    44,    -1,
      -1,    26,    48,    28,    50,    51,    31,    -1,    -1,    13,
      -1,    -1,    58,    59,    18,    19,    -1,    -1,    -1,    44,
      -1,    -1,    26,    48,    28,    50,    51,    31,    -1,    -1,
      13,    -1,    -1,    58,    59,    18,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    26,    48,    28,    50,    51,    31,    -1,
      -1,    13,    -1,    -1,    58,    59,    18,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    26,    48,    28,    50,    51,    31,
      50,    51,    52,    53,    54,    58,    59,    57,    -1,    -1,
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
      74,    76,    78,    82,    83,    84,    85,    94,    95,   100,
     101,     3,     6,     7,     8,    19,    21,    26,    32,    33,
      34,    72,    75,    77,    78,    81,    86,    87,    88,    89,
      91,    92,    93,    94,    96,    97,    98,    99,    26,    31,
      26,    26,    10,    59,    61,   133,    10,   133,    10,    26,
      58,    29,    30,    79,   133,    61,    61,    26,    31,    19,
      26,    28,    26,    10,    58,   105,   133,   133,    10,    19,
      26,   105,    79,    60,    80,   133,    13,    18,    26,    28,
      31,    44,    48,    50,    51,    58,    59,   134,   137,   144,
     147,    61,   107,    61,    61,    58,    59,    59,    28,    58,
     135,   135,    58,   121,   108,    58,   106,   134,   105,    58,
     104,   105,    58,   104,     6,    19,    26,    63,   102,   103,
      10,   105,   105,    10,    26,    79,    58,    58,    59,   144,
     144,   144,   144,    59,   135,    58,   138,    24,    25,    38,
      39,    40,    41,    42,    43,    45,    46,    47,    49,    50,
      51,    52,    53,    54,    57,     8,    11,    13,    15,    17,
      19,    26,    28,    31,    36,    62,    89,    90,   110,   115,
     117,   120,   127,   128,   129,   130,   131,   137,   148,   107,
     107,    19,    20,    65,   136,    62,    26,    28,    62,   123,
     124,   125,   148,     8,    11,    13,    15,    19,    26,    36,
      62,   109,   118,   119,   125,   148,    10,    28,    44,    48,
      50,    51,    58,    63,   134,   142,   145,   147,   134,    10,
     103,    10,   103,    19,    26,    19,    26,    49,    63,    10,
      10,   144,    10,    63,   142,   144,    63,   135,    65,    19,
      26,    90,   139,   140,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   148,    19,    26,   144,    58,    58,   144,   144,
      61,    53,    58,    61,   144,    12,   134,    61,   111,   115,
     111,   111,    61,   138,   106,    62,    62,    13,    26,    28,
      31,    48,    50,    51,    58,   137,   141,   143,   146,    26,
      30,    53,    61,   122,   123,   133,    10,    10,    58,    58,
      61,    36,    61,   109,   112,   133,    63,   145,   145,   145,
     144,    49,    63,    24,    25,    38,    39,    40,    41,    42,
      43,    45,    46,    47,    50,    51,    52,    53,    54,    57,
      63,    63,   102,    63,    63,    63,    65,    65,    67,   106,
      10,    10,   144,   144,    63,   144,   116,   111,   107,    14,
     113,   134,   134,    58,    58,    59,   143,   143,   144,   138,
     143,    24,    25,    66,   126,   121,   135,   108,    63,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,    65,    26,   140,
     144,   134,   144,   144,    63,    63,    63,   111,    62,    14,
      16,    62,   114,   132,   144,    63,   142,   144,    63,   143,
     143,   133,    62,    62,    62,    63,   134,    64,   144,   111,
      63,    63,    65,    64
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
      87,    87,    87,    88,    88,    89,    89,    90,    91,    92,
      93,    94,    94,    95,    96,    96,    97,    98,    99,   100,
     101,   102,   102,   102,   102,   102,   102,   103,   103,   104,
     104,   105,   105,   106,   106,   106,   106,   107,   107,   108,
     108,   109,   109,   110,   110,   110,   110,   110,   110,   111,
     111,   112,   112,   113,   113,   114,   115,   115,   115,   116,
     115,   115,   115,   115,   115,   115,   117,   117,   117,   118,
     118,   118,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   120,   121,   121,   122,   122,   123,   124,   124,   126,
     125,   127,   127,   127,   128,   129,   130,   130,   131,   132,
     132,   133,   133,   134,   134,   135,   135,   136,   136,   136,
     136,   137,   138,   139,   139,   140,   141,   141,   142,   142,
     143,   143,   143,   143,   143,   143,   143,   143,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   146,
     146,   146,   146,   146,   146,   147,   147,   147,   147,   147,
     147,   147,   148,   148
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
       4,     3,     4,     1,     1,     2,     2,     2,     3,     2,
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
       2,     1,     5,     3,     1,     1,     2,     1,     3,     1,
       1,     1,     3,     1,     2,     2,     3,     3,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     3,
       4,     4,     4,     2,     1,     3,     4,     4,     4,     4,
       2,     1,     1,     1
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
  "function_definition_header", "global_definition_header",
  "definition_header", "definition", "shape", "shape_singleton_header",
  "shape_singleton", "rule_header_v2", "rule_v2", "rule_header",
  "path_header", "rule", "path", "path_header_v2", "path_v2", "parameter",
  "buncha_parameters", "parameter_list", "function_parameter_list",
  "parameter_spec", "buncha_elements", "buncha_pathOps_v2",
  "pathOp_simple_v2", "element_simple", "one_or_more_elements",
  "one_or_more_pathOp_v2", "caseBody", "caseBody_element", "element",
  "$@1", "element_v2clue", "pathOp_v2", "pathOp_v3clues", "element_loop",
  "buncha_replacements_v2", "one_or_more_replacements_v2",
  "replacement_simple_v2", "replacement_v2", "loopHeader_v2", "$@2",
  "loopHeader", "ifHeader", "ifElseHeader", "transHeader", "switchHeader",
  "caseHeader", "modification_v2", "modification", "buncha_adjustments",
  "adjustment", "letHeader", "letBody", "letVariables", "letVariable",
  "explist", "arglist", "exp", "exp2", "exp3", "expfunc", "exp2func",
  "shapeName", YY_NULL
  };


  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const CfdgParser::rhs_number_type
  CfdgParser::yyrhs_[] =
  {
        69,     0,    -1,     4,    70,    -1,     5,    71,    -1,    70,
      73,    -1,    -1,    71,    72,    -1,    -1,    81,    -1,    77,
      -1,    78,    -1,    98,    -1,    99,    -1,    91,    -1,    93,
      -1,    86,    -1,    75,    -1,    82,    -1,    83,    -1,    76,
      -1,    78,    -1,    84,    -1,    85,    -1,    95,    -1,   101,
      -1,    74,    -1,    26,    10,    -1,    19,    10,    -1,    20,
      10,    -1,    26,    58,    -1,    26,    26,    58,    -1,    33,
      -1,     6,    -1,     8,    26,    58,    -1,     3,    26,    58,
      -1,     3,    26,    59,    -1,     3,    31,    59,    -1,    21,
     133,    -1,    34,   133,    -1,    19,   133,    -1,    32,    79,
      -1,    94,    -1,    32,    79,    -1,    33,    80,    79,    -1,
      23,    -1,    29,    -1,    30,    -1,    60,    26,    -1,    -1,
       3,    26,   106,   134,    -1,     3,    31,   134,    -1,     3,
      26,   106,    -1,     3,    26,    -1,    21,   133,    -1,    34,
     133,    -1,    19,   133,    -1,    88,   144,    -1,     6,    26,
     105,    10,    -1,    26,   105,    10,    -1,    26,    26,   105,
      10,    -1,     6,    19,   105,    10,    -1,    19,   105,    10,
      -1,    26,    19,   105,    10,    -1,    87,    -1,    89,    -1,
      26,    10,    -1,    19,    10,    -1,    89,   144,    -1,     6,
      26,   104,    -1,    91,    61,    -1,    92,   107,    62,    -1,
       7,    26,    -1,     7,    26,    28,    -1,    94,    61,   121,
      62,    -1,     7,    -1,     7,    28,    -1,     8,    26,   104,
      -1,    96,    61,   107,    62,    -1,    97,    61,   107,    62,
      -1,     8,    26,    -1,   100,    61,   108,    62,    -1,    26,
      26,    -1,     6,    26,    -1,    26,    19,    -1,     6,    19,
      -1,    26,    -1,    19,    -1,   103,    49,   102,    -1,   102,
      -1,    58,   103,    63,    -1,    -1,    58,   103,    63,    -1,
      58,    63,    -1,    58,   142,    63,    -1,    58,    10,    63,
      -1,    58,    63,    -1,    -1,   107,   115,    -1,    -1,   108,
     118,    -1,    -1,    36,    61,   135,    62,    -1,   148,   133,
      -1,    36,    58,   144,    63,    -1,    36,    58,    63,    -1,
     148,   106,   134,    -1,    13,    58,   144,    63,   134,    -1,
     137,   138,   134,    -1,     8,   148,   106,   134,    -1,    61,
     107,    62,    -1,   115,    -1,    61,   108,    62,    -1,   109,
      -1,   113,   114,    -1,    -1,   132,   111,    -1,   110,    -1,
      90,    -1,   120,    -1,    -1,   120,    12,   116,   111,    -1,
     128,   111,    -1,   129,   111,    -1,   130,   111,    -1,   131,
      61,   113,    62,    -1,   117,    -1,    28,    53,    -1,    26,
      61,    -1,    36,    61,    -1,   109,    -1,   125,   112,    -1,
     119,    -1,    36,    58,    -1,    26,    58,    -1,     8,    -1,
      11,    -1,    26,    10,    -1,    19,    10,    -1,    13,    -1,
      19,    -1,    15,    -1,   127,   134,   111,    -1,   121,   124,
      -1,    -1,    61,   121,    62,    -1,   123,    -1,   148,   133,
      -1,   123,    -1,   125,   122,    -1,    -1,    28,    53,   126,
     133,    -1,    11,    26,    10,   144,    -1,    11,    19,    10,
     144,    -1,    11,   144,    -1,    13,    58,   144,    63,    -1,
     128,   111,    14,    -1,    19,   144,    -1,    17,   144,    -1,
      15,    58,   144,    63,    -1,    16,   144,    64,    -1,    14,
      64,    -1,    61,   135,    62,    -1,    59,   135,    65,    -1,
      59,   135,    65,    -1,    59,    59,   135,    65,    65,    -1,
     135,   136,    -1,    -1,    19,   141,    -1,    19,   143,    66,
      -1,    20,    26,    -1,    20,    30,    -1,    18,    -1,    58,
     139,    67,   144,    63,    -1,   139,    67,   140,    -1,   140,
      -1,    90,    -1,   141,   143,    -1,   143,    -1,   142,    49,
     145,    -1,   145,    -1,    28,    -1,    48,    -1,    58,   144,
      63,    -1,   146,    -1,    50,   143,    -1,    51,   143,    -1,
     143,    24,   143,    -1,   143,    25,   143,    -1,    28,    -1,
      48,    -1,   147,    -1,   144,    24,   144,    -1,   144,    25,
     144,    -1,   144,    49,   144,    -1,   144,    51,   144,    -1,
     144,    50,   144,    -1,   144,    52,   144,    -1,   144,    53,
     144,    -1,   144,    54,   144,    -1,    50,   144,    -1,    51,
     144,    -1,    44,   144,    -1,   144,    57,   144,    -1,   144,
      39,   144,    -1,   144,    38,   144,    -1,   144,    41,   144,
      -1,   144,    40,   144,    -1,   144,    42,   144,    -1,   144,
      43,   144,    -1,   144,    45,   144,    -1,   144,    46,   144,
      -1,   144,    47,   144,    -1,    58,   144,    63,    -1,   134,
      -1,    28,    -1,    48,    -1,   147,    -1,   145,    24,   145,
      -1,   145,    25,   145,    -1,   145,    51,   145,    -1,   145,
      50,   145,    -1,   145,    52,   145,    -1,   145,    53,   145,
      -1,   145,    54,   145,    -1,    50,   145,    -1,    51,   145,
      -1,    44,   145,    -1,   145,    57,   145,    -1,   145,    39,
     145,    -1,   145,    38,   145,    -1,   145,    41,   145,    -1,
     145,    40,   145,    -1,   145,    42,   145,    -1,   145,    43,
     145,    -1,   145,    45,   145,    -1,   145,    46,   145,    -1,
     145,    47,   145,    -1,    58,   144,    63,    -1,   134,    -1,
      26,    58,    63,    -1,    26,    58,   142,    63,    -1,    31,
      59,   144,    65,    -1,    13,    58,   144,    63,    -1,   137,
     138,    -1,    26,    -1,    26,    58,    63,    -1,    26,    58,
     142,    63,    -1,    31,    59,   144,    65,    -1,    13,    58,
     144,    63,    -1,    26,    58,    10,    63,    -1,   137,   138,
      -1,    26,    -1,    26,    -1,    31,    -1
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
     162,   167,   171,   176,   178,   180,   183,   186,   189,   193,
     196,   200,   203,   207,   212,   214,   217,   221,   226,   231,
     234,   239,   242,   245,   248,   251,   253,   255,   259,   261,
     265,   266,   270,   273,   277,   281,   284,   285,   288,   289,
     292,   293,   298,   301,   306,   310,   314,   320,   324,   329,
     333,   335,   339,   341,   344,   345,   348,   350,   352,   354,
     355,   360,   363,   366,   369,   374,   376,   379,   382,   385,
     387,   390,   392,   395,   398,   400,   402,   405,   408,   410,
     412,   414,   418,   421,   422,   426,   428,   431,   433,   436,
     437,   442,   447,   452,   455,   460,   464,   467,   470,   475,
     479,   482,   486,   490,   494,   500,   503,   504,   507,   511,
     514,   517,   519,   525,   529,   531,   533,   536,   538,   542,
     544,   546,   548,   552,   554,   557,   560,   564,   568,   570,
     572,   574,   578,   582,   586,   590,   594,   598,   602,   606,
     609,   612,   615,   619,   623,   627,   631,   635,   639,   643,
     647,   651,   655,   659,   661,   663,   665,   667,   671,   675,
     679,   683,   687,   691,   695,   698,   701,   704,   708,   712,
     716,   720,   724,   728,   732,   736,   740,   744,   748,   750,
     754,   759,   764,   769,   772,   774,   778,   783,   788,   793,
     798,   801,   803,   805
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
     314,   325,   339,   352,   364,   376,   395,   422,   432,   442,
     451,   456,   461,   469,   474,   480,   483,   490,   508,   515,
     524,   532,   541,   556,   564,   572,   585,   598,   606,   615,
     628,   635,   641,   647,   652,   656,   662,   668,   669,   673,
     674,   678,   679,   683,   684,   685,   686,   690,   693,   697,
     700,   704,   711,   721,   727,   733,   742,   752,   763,   773,
     775,   781,   783,   789,   792,   796,   800,   804,   808,   817,
     817,   829,   838,   847,   856,   863,   870,   871,   872,   876,
     878,   886,   898,   899,   900,   901,   902,   903,   904,   905,
     906,   910,   920,   923,   927,   929,   935,   944,   946,   957,
     957,   972,   981,   991,  1002,  1011,  1019,  1027,  1037,  1046,
    1074,  1085,  1090,  1097,  1102,  1109,  1114,  1123,  1128,  1138,
    1143,  1150,  1158,  1164,  1166,  1170,  1176,  1180,  1187,  1191,
    1197,  1199,  1201,  1203,  1205,  1207,  1209,  1214,  1221,  1223,
    1225,  1227,  1232,  1237,  1239,  1241,  1243,  1245,  1247,  1249,
    1251,  1253,  1255,  1257,  1259,  1261,  1263,  1265,  1267,  1269,
    1271,  1273,  1275,  1277,  1281,  1283,  1285,  1287,  1292,  1297,
    1299,  1301,  1303,  1305,  1307,  1309,  1311,  1313,  1315,  1317,
    1319,  1321,  1323,  1325,  1327,  1329,  1331,  1333,  1335,  1339,
    1344,  1350,  1356,  1362,  1369,  1376,  1381,  1387,  1393,  1399,
    1405,  1412,  1419,  1421
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
  const int CfdgParser::yylast_ = 1311;
  const int CfdgParser::yynnts_ = 81;
  const int CfdgParser::yyempty_ = -2;
  const int CfdgParser::yyfinal_ = 6;
  const int CfdgParser::yyterror_ = 1;
  const int CfdgParser::yyerrcode_ = 256;
  const int CfdgParser::yyntokens_ = 68;

  const unsigned int CfdgParser::yyuser_token_number_max_ = 305;
  const CfdgParser::token_number_type CfdgParser::yyundef_token_ = 2;


} // yy
/* Line 1141 of lalr1.cc  */
#line 3817 "cfdg.tab.cpp"
/* Line 1142 of lalr1.cc  */
#line 1424 "../../src-common/cfdg.ypp"


void yy::CfdgParser::error(const CfdgParser::location_type& l, const std::string& m)
{
    driver.error(l, m);
}
