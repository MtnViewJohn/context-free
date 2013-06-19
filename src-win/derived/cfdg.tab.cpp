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
#line 81 "../../src-common/cfdg.ypp"

#include "astreplacement.h"
#include "astexpression.h"
    
    using namespace AST;
/* Line 285 of lalr1.cc  */
#line 179 "../../src-common/cfdg.ypp"

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
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).string); };
/* Line 455 of lalr1.cc  */
#line 249 "cfdg.tab.cpp"
        break;
      case 29: /* USER_FILENAME */
/* Line 455 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).string); };
/* Line 455 of lalr1.cc  */
#line 256 "cfdg.tab.cpp"
        break;
      case 30: /* USER_QSTRING */
/* Line 455 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).string); };
/* Line 455 of lalr1.cc  */
#line 263 "cfdg.tab.cpp"
        break;
      case 31: /* USER_ARRAYNAME */
/* Line 455 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).string); };
/* Line 455 of lalr1.cc  */
#line 270 "cfdg.tab.cpp"
        break;
      case 36: /* USER_PATHOP */
/* Line 455 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).string); };
/* Line 455 of lalr1.cc  */
#line 277 "cfdg.tab.cpp"
        break;
      case 72: /* statement */
/* Line 455 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 284 "cfdg.tab.cpp"
        break;
      case 73: /* statement_v2 */
/* Line 455 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 291 "cfdg.tab.cpp"
        break;
      case 79: /* fileString */
/* Line 455 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).string); };
/* Line 455 of lalr1.cc  */
#line 298 "cfdg.tab.cpp"
        break;
      case 80: /* fileNameSpace */
/* Line 455 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).string); };
/* Line 455 of lalr1.cc  */
#line 305 "cfdg.tab.cpp"
        break;
      case 81: /* initialization */
/* Line 455 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 312 "cfdg.tab.cpp"
        break;
      case 82: /* initialization_v2 */
/* Line 455 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 319 "cfdg.tab.cpp"
        break;
      case 83: /* directive_v2 */
/* Line 455 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 326 "cfdg.tab.cpp"
        break;
      case 84: /* directive_string */
/* Line 455 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
        { };
/* Line 455 of lalr1.cc  */
#line 333 "cfdg.tab.cpp"
        break;
      case 85: /* global_definition */
/* Line 455 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).defObj); };
/* Line 455 of lalr1.cc  */
#line 340 "cfdg.tab.cpp"
        break;
      case 86: /* function_definition_header */
/* Line 455 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).defObj); };
/* Line 455 of lalr1.cc  */
#line 347 "cfdg.tab.cpp"
        break;
      case 87: /* global_definition_header */
/* Line 455 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).defObj); };
/* Line 455 of lalr1.cc  */
#line 354 "cfdg.tab.cpp"
        break;
      case 88: /* definition_header */
/* Line 455 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).defObj); };
/* Line 455 of lalr1.cc  */
#line 361 "cfdg.tab.cpp"
        break;
      case 89: /* definition */
/* Line 455 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).defObj); };
/* Line 455 of lalr1.cc  */
#line 368 "cfdg.tab.cpp"
        break;
      case 91: /* shape_singleton_header */
/* Line 455 of lalr1.cc  */
#line 171 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).ruleObj); };
/* Line 455 of lalr1.cc  */
#line 375 "cfdg.tab.cpp"
        break;
      case 92: /* shape_singleton */
/* Line 455 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 382 "cfdg.tab.cpp"
        break;
      case 93: /* rule_header_v2 */
/* Line 455 of lalr1.cc  */
#line 174 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).ruleObj); };
/* Line 455 of lalr1.cc  */
#line 389 "cfdg.tab.cpp"
        break;
      case 95: /* rule_header */
/* Line 455 of lalr1.cc  */
#line 173 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).ruleObj); };
/* Line 455 of lalr1.cc  */
#line 396 "cfdg.tab.cpp"
        break;
      case 96: /* path_header */
/* Line 455 of lalr1.cc  */
#line 173 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).ruleObj); };
/* Line 455 of lalr1.cc  */
#line 403 "cfdg.tab.cpp"
        break;
      case 97: /* rule */
/* Line 455 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 410 "cfdg.tab.cpp"
        break;
      case 98: /* path */
/* Line 455 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 417 "cfdg.tab.cpp"
        break;
      case 99: /* path_header_v2 */
/* Line 455 of lalr1.cc  */
#line 174 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).ruleObj); };
/* Line 455 of lalr1.cc  */
#line 424 "cfdg.tab.cpp"
        break;
      case 105: /* parameter_spec */
/* Line 455 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 431 "cfdg.tab.cpp"
        break;
      case 108: /* pathOp_simple_v2 */
/* Line 455 of lalr1.cc  */
#line 172 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 438 "cfdg.tab.cpp"
        break;
      case 109: /* element_simple */
/* Line 455 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 445 "cfdg.tab.cpp"
        break;
      case 114: /* element */
/* Line 455 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 452 "cfdg.tab.cpp"
        break;
      case 117: /* pathOp_v2 */
/* Line 455 of lalr1.cc  */
#line 172 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 459 "cfdg.tab.cpp"
        break;
      case 119: /* element_loop */
/* Line 455 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).loopObj); };
/* Line 455 of lalr1.cc  */
#line 466 "cfdg.tab.cpp"
        break;
      case 122: /* replacement_simple_v2 */
/* Line 455 of lalr1.cc  */
#line 172 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 473 "cfdg.tab.cpp"
        break;
      case 123: /* replacement_v2 */
/* Line 455 of lalr1.cc  */
#line 172 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 480 "cfdg.tab.cpp"
        break;
      case 124: /* loopHeader_v2 */
/* Line 455 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).loopObj); };
/* Line 455 of lalr1.cc  */
#line 487 "cfdg.tab.cpp"
        break;
      case 126: /* loopHeader */
/* Line 455 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).loopObj); };
/* Line 455 of lalr1.cc  */
#line 494 "cfdg.tab.cpp"
        break;
      case 127: /* ifHeader */
/* Line 455 of lalr1.cc  */
#line 175 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).ifObj); };
/* Line 455 of lalr1.cc  */
#line 501 "cfdg.tab.cpp"
        break;
      case 128: /* ifElseHeader */
/* Line 455 of lalr1.cc  */
#line 175 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).ifObj); };
/* Line 455 of lalr1.cc  */
#line 508 "cfdg.tab.cpp"
        break;
      case 129: /* transHeader */
/* Line 455 of lalr1.cc  */
#line 171 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).component); };
/* Line 455 of lalr1.cc  */
#line 515 "cfdg.tab.cpp"
        break;
      case 130: /* switchHeader */
/* Line 455 of lalr1.cc  */
#line 176 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).switchObj); };
/* Line 455 of lalr1.cc  */
#line 522 "cfdg.tab.cpp"
        break;
      case 131: /* caseHeader */
/* Line 455 of lalr1.cc  */
#line 177 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); };
/* Line 455 of lalr1.cc  */
#line 529 "cfdg.tab.cpp"
        break;
      case 132: /* modification_v2 */
/* Line 455 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).mod); };
/* Line 455 of lalr1.cc  */
#line 536 "cfdg.tab.cpp"
        break;
      case 133: /* modification */
/* Line 455 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).mod); };
/* Line 455 of lalr1.cc  */
#line 543 "cfdg.tab.cpp"
        break;
      case 134: /* buncha_adjustments */
/* Line 455 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).mod); };
/* Line 455 of lalr1.cc  */
#line 550 "cfdg.tab.cpp"
        break;
      case 135: /* adjustment */
/* Line 455 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).term); };
/* Line 455 of lalr1.cc  */
#line 557 "cfdg.tab.cpp"
        break;
      case 136: /* letHeader */
/* Line 455 of lalr1.cc  */
#line 178 "../../src-common/cfdg.ypp"
        { driver.pop_repContainer(nullptr); delete ((*yyvaluep).bodyObj); };
/* Line 455 of lalr1.cc  */
#line 564 "cfdg.tab.cpp"
        break;
      case 137: /* letBody */
/* Line 455 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 571 "cfdg.tab.cpp"
        break;
      case 140: /* explist */
/* Line 455 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 578 "cfdg.tab.cpp"
        break;
      case 141: /* arglist */
/* Line 455 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 585 "cfdg.tab.cpp"
        break;
      case 142: /* exp */
/* Line 455 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 592 "cfdg.tab.cpp"
        break;
      case 143: /* exp2 */
/* Line 455 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 599 "cfdg.tab.cpp"
        break;
      case 144: /* exp3 */
/* Line 455 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 606 "cfdg.tab.cpp"
        break;
      case 145: /* expfunc */
/* Line 455 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 613 "cfdg.tab.cpp"
        break;
      case 146: /* exp2func */
/* Line 455 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).expression); };
/* Line 455 of lalr1.cc  */
#line 620 "cfdg.tab.cpp"
        break;
      case 147: /* shapeName */
/* Line 455 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
        { delete ((*yyvaluep).string); };
/* Line 455 of lalr1.cc  */
#line 627 "cfdg.tab.cpp"
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
#line 195 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 6:
/* Line 670 of lalr1.cc  */
#line 204 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 9:
/* Line 670 of lalr1.cc  */
#line 214 "../../src-common/cfdg.ypp"
    { (yyval.component) = nullptr; }
    break;

  case 10:
/* Line 670 of lalr1.cc  */
#line 215 "../../src-common/cfdg.ypp"
    { (yyval.component) = nullptr; }
    break;

  case 13:
/* Line 670 of lalr1.cc  */
#line 218 "../../src-common/cfdg.ypp"
    { (yyval.component) = nullptr; }
    break;

  case 15:
/* Line 670 of lalr1.cc  */
#line 220 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].defObj); }
    break;

  case 16:
/* Line 670 of lalr1.cc  */
#line 221 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = nullptr;
        }
    break;

  case 19:
/* Line 670 of lalr1.cc  */
#line 230 "../../src-common/cfdg.ypp"
    { (yyval.component) = nullptr; }
    break;

  case 20:
/* Line 670 of lalr1.cc  */
#line 231 "../../src-common/cfdg.ypp"
    { (yyval.component) = nullptr; }
    break;

  case 23:
/* Line 670 of lalr1.cc  */
#line 234 "../../src-common/cfdg.ypp"
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

  case 24:
/* Line 670 of lalr1.cc  */
#line 246 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 25:
/* Line 670 of lalr1.cc  */
#line 247 "../../src-common/cfdg.ypp"
    {}
    break;

  case 26:
/* Line 670 of lalr1.cc  */
#line 248 "../../src-common/cfdg.ypp"
    {}
    break;

  case 27:
/* Line 670 of lalr1.cc  */
#line 249 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 28:
/* Line 670 of lalr1.cc  */
#line 250 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (1)].string); delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 31:
/* Line 670 of lalr1.cc  */
#line 253 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 32:
/* Line 670 of lalr1.cc  */
#line 254 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 33:
/* Line 670 of lalr1.cc  */
#line 255 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 34:
/* Line 670 of lalr1.cc  */
#line 256 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 35:
/* Line 670 of lalr1.cc  */
#line 260 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 36:
/* Line 670 of lalr1.cc  */
#line 261 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 37:
/* Line 670 of lalr1.cc  */
#line 262 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 38:
/* Line 670 of lalr1.cc  */
#line 263 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 39:
/* Line 670 of lalr1.cc  */
#line 264 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(1) - (1)].ruleObj); }
    break;

  case 40:
/* Line 670 of lalr1.cc  */
#line 268 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(2) - (2)].string)); (yysemantic_stack_[(2) - (2)].string) = nullptr;
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(nullptr);
            driver.IncludeFile(*file);
        }
    break;

  case 41:
/* Line 670 of lalr1.cc  */
#line 277 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(3) - (3)].string)); (yysemantic_stack_[(3) - (3)].string) = nullptr;
            str_ptr nm((yysemantic_stack_[(3) - (2)].string)); (yysemantic_stack_[(3) - (2)].string) = nullptr;
            driver.SetShape(nullptr);
            driver.IncludeFile(*file);
            if (nm)
                driver.PushNameSpace(std::move(nm), (yylocation_stack_[(3) - (2)]));
        }
    break;

  case 42:
/* Line 670 of lalr1.cc  */
#line 288 "../../src-common/cfdg.ypp"
    {
            if (driver.EndInclude())
                YYACCEPT;
        }
    break;

  case 45:
/* Line 670 of lalr1.cc  */
#line 298 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 46:
/* Line 670 of lalr1.cc  */
#line 299 "../../src-common/cfdg.ypp"
    { (yyval.string) = nullptr; }
    break;

  case 47:
/* Line 670 of lalr1.cc  */
#line 303 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(4) - (2)].string)); (yysemantic_stack_[(4) - (2)].string) = nullptr;
            exp_ptr p((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            mod_ptr mod((yysemantic_stack_[(4) - (4)].mod)); (yysemantic_stack_[(4) - (4)].mod) = nullptr;
            driver.SetShape(nullptr);
            ASTdefine* cfg = driver.MakeDefinition(CFDG::ParamNames[CFG::StartShape], (yyloc), false);
            if (cfg)
                cfg->mExpression.reset(driver.MakeRuleSpec(*name, std::move(p), (yylocation_stack_[(4) - (2)]), std::move(mod), true));
            (yyval.component) = cfg;
        }
    break;

  case 48:
/* Line 670 of lalr1.cc  */
#line 314 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(3) - (2)].string)); (yysemantic_stack_[(3) - (2)].string) = nullptr;
            mod_ptr mod((yysemantic_stack_[(3) - (3)].mod)); (yysemantic_stack_[(3) - (3)].mod) = nullptr;
            driver.SetShape(nullptr);
            ASTdefine* cfg = driver.MakeDefinition(CFDG::ParamNames[CFG::StartShape], (yyloc), false);
            if (cfg)
                cfg->mExpression.reset(driver.MakeRuleSpec(*name, nullptr, (yylocation_stack_[(3) - (2)]), std::move(mod), true));
            (yyval.component) = cfg;
        }
    break;

  case 49:
/* Line 670 of lalr1.cc  */
#line 324 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(3) - (2)].string)); (yysemantic_stack_[(3) - (2)].string) = nullptr;
            exp_ptr p((yysemantic_stack_[(3) - (3)].expression)); (yysemantic_stack_[(3) - (3)].expression) = nullptr;
            driver.SetShape(nullptr);
            ASTdefine* cfg = driver.MakeDefinition(CFDG::ParamNames[CFG::StartShape], (yyloc), false);
            if (cfg)
                cfg->mExpression.reset(driver.MakeRuleSpec(*name, std::move(p), (yylocation_stack_[(3) - (2)]), nullptr, true));
            (yyval.component) = cfg;
        }
    break;

  case 50:
/* Line 670 of lalr1.cc  */
#line 336 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (2)].string)); (yysemantic_stack_[(2) - (2)].string) = nullptr;
            driver.SetShape(nullptr);
            ASTdefine* cfg = driver.MakeDefinition(CFDG::ParamNames[CFG::StartShape], (yyloc), false);
            if (cfg)
                cfg->mExpression.reset(driver.MakeRuleSpec(*name, nullptr, (yylocation_stack_[(2) - (2)]), nullptr, true));
            (yyval.component) = cfg;
        }
    break;

  case 51:
/* Line 670 of lalr1.cc  */
#line 347 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].mod)); (yysemantic_stack_[(2) - (2)].mod) = nullptr;
            ASTdefine* cfg = driver.MakeDefinition(*(yysemantic_stack_[(2) - (1)].cstring), (yyloc), false);
            if (cfg)
                cfg->mExpression = std::move(mod);
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = cfg;
        }
    break;

  case 52:
/* Line 670 of lalr1.cc  */
#line 358 "../../src-common/cfdg.ypp"
    { (yyval.cstring) = &CFDG::ParamNames[CFG::Background]; }
    break;

  case 53:
/* Line 670 of lalr1.cc  */
#line 360 "../../src-common/cfdg.ypp"
    { (yyval.cstring) = &CFDG::ParamNames[CFG::Tile]; }
    break;

  case 54:
/* Line 670 of lalr1.cc  */
#line 362 "../../src-common/cfdg.ypp"
    {
            switch ((yysemantic_stack_[(1) - (1)].modToken)) {
            case ASTmodTerm::size:
                (yyval.cstring) = &CFDG::ParamNames[CFG::Size];
                break;
            case ASTmodTerm::time:
                (yyval.cstring) = &CFDG::ParamNames[CFG::Time];
                break;
            default:
                (yyval.cstring) = &CFDG::ParamNames[CFG::Size];
                error((yylocation_stack_[(1) - (1)]), "Syntax error");
                break;
            }
        }
    break;

  case 55:
/* Line 670 of lalr1.cc  */
#line 379 "../../src-common/cfdg.ypp"
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
                    if (ASTmodification* mod = dynamic_cast<ASTmodification*>(exp.get()))
                        var->mChildChange.grab(mod);        // emptied ASTmod gets deleted
                    else
                        var->mExpression = std::move(exp);
                }
                (yyval.defObj) = var.release();
            } else {
                (yyval.defObj) = nullptr;
            }
        }
    break;

  case 56:
/* Line 670 of lalr1.cc  */
#line 404 "../../src-common/cfdg.ypp"
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

  case 57:
/* Line 670 of lalr1.cc  */
#line 414 "../../src-common/cfdg.ypp"
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

  case 58:
/* Line 670 of lalr1.cc  */
#line 424 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            str_ptr name((yysemantic_stack_[(4) - (2)].string)); (yysemantic_stack_[(4) - (2)].string) = nullptr;
            ASTdefine* def = driver.MakeDefinition(*name, (yyloc), true);
            if (def)
                def->mType = AST::decodeType(*type, def->mTuplesize, def->isNatural, (yylocation_stack_[(4) - (1)]));
            (yyval.defObj) = def;
        }
    break;

  case 59:
/* Line 670 of lalr1.cc  */
#line 433 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(4) - (2)]), "Reserved keyword: adjustment");
            (yyval.defObj) = nullptr;
        }
    break;

  case 60:
/* Line 670 of lalr1.cc  */
#line 438 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(3) - (1)]), "Reserved keyword: adjustment");
            (yyval.defObj) = nullptr;
        }
    break;

  case 61:
/* Line 670 of lalr1.cc  */
#line 443 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            error((yylocation_stack_[(4) - (2)]), "Reserved keyword: adjustment");
            (yyval.defObj) = nullptr;
        }
    break;

  case 62:
/* Line 670 of lalr1.cc  */
#line 451 "../../src-common/cfdg.ypp"
    {
            driver.push_repContainer(driver.mParamDecls);
            (yyval.defObj) = (yysemantic_stack_[(1) - (1)].defObj);
        }
    break;

  case 63:
/* Line 670 of lalr1.cc  */
#line 456 "../../src-common/cfdg.ypp"
    {
            (yyval.defObj) = (yysemantic_stack_[(1) - (1)].defObj);
        }
    break;

  case 64:
/* Line 670 of lalr1.cc  */
#line 462 "../../src-common/cfdg.ypp"
    {
            (yyval.defObj) = driver.MakeDefinition(*(yysemantic_stack_[(2) - (1)].string), (yyloc), false);
        }
    break;

  case 65:
/* Line 670 of lalr1.cc  */
#line 465 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (1)]), "Reserved keyword: adjustment");
            (yyval.defObj) = nullptr;
        }
    break;

  case 66:
/* Line 670 of lalr1.cc  */
#line 472 "../../src-common/cfdg.ypp"
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

  case 67:
/* Line 670 of lalr1.cc  */
#line 490 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(3) - (2)].string)); (yysemantic_stack_[(3) - (2)].string) = nullptr;
            driver.SetShape(name.get(), (yylocation_stack_[(3) - (2)]));
        }
    break;

  case 68:
/* Line 670 of lalr1.cc  */
#line 497 "../../src-common/cfdg.ypp"
    {
            driver.mInPathContainer = false;
            rule_ptr rule(new ASTrule(-1, (yylocation_stack_[(2) - (1)])));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
        }
    break;

  case 69:
/* Line 670 of lalr1.cc  */
#line 506 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(3) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 70:
/* Line 670 of lalr1.cc  */
#line 514 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (2)].string)); (yysemantic_stack_[(2) - (2)].string) = nullptr;
            driver.SetShape(nullptr);
            rule_ptr rule(new ASTrule(driver.StringToShape(*name, (yylocation_stack_[(2) - (2)]), false), (yyloc)));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
        }
    break;

  case 71:
/* Line 670 of lalr1.cc  */
#line 523 "../../src-common/cfdg.ypp"
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

  case 72:
/* Line 670 of lalr1.cc  */
#line 538 "../../src-common/cfdg.ypp"
    {
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 73:
/* Line 670 of lalr1.cc  */
#line 546 "../../src-common/cfdg.ypp"
    {
            driver.mInPathContainer = false;
            rule_ptr rule(new ASTrule(-1, (yylocation_stack_[(1) - (1)])));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
        }
    break;

  case 74:
/* Line 670 of lalr1.cc  */
#line 554 "../../src-common/cfdg.ypp"
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

  case 75:
/* Line 670 of lalr1.cc  */
#line 567 "../../src-common/cfdg.ypp"
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

  case 76:
/* Line 670 of lalr1.cc  */
#line 580 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 77:
/* Line 670 of lalr1.cc  */
#line 588 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
            driver.SetShape(nullptr);
        }
    break;

  case 78:
/* Line 670 of lalr1.cc  */
#line 597 "../../src-common/cfdg.ypp"
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

  case 79:
/* Line 670 of lalr1.cc  */
#line 610 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 80:
/* Line 670 of lalr1.cc  */
#line 617 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(2) - (1)].string)); (yysemantic_stack_[(2) - (1)].string) = nullptr;
            str_ptr var((yysemantic_stack_[(2) - (2)].string)); (yysemantic_stack_[(2) - (2)].string) = nullptr;
            driver.NextParameterDecl(*type, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 81:
/* Line 670 of lalr1.cc  */
#line 623 "../../src-common/cfdg.ypp"
    {
            static std::string shapeStr("shape");
            str_ptr var((yysemantic_stack_[(2) - (2)].string)); (yysemantic_stack_[(2) - (2)].string) = nullptr;
            driver.NextParameterDecl(shapeStr, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 82:
/* Line 670 of lalr1.cc  */
#line 629 "../../src-common/cfdg.ypp"
    {
            delete (yysemantic_stack_[(2) - (1)].string);
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 83:
/* Line 670 of lalr1.cc  */
#line 634 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 84:
/* Line 670 of lalr1.cc  */
#line 638 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("number");
            str_ptr var((yysemantic_stack_[(1) - (1)].string)); (yysemantic_stack_[(1) - (1)].string) = nullptr;
            driver.NextParameterDecl(numtype, *var, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 85:
/* Line 670 of lalr1.cc  */
#line 644 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Reserved keyword: adjustment");
        }
    break;

  case 92:
/* Line 670 of lalr1.cc  */
#line 665 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(3) - (2)].expression);}
    break;

  case 93:
/* Line 670 of lalr1.cc  */
#line 666 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTexpression((yyloc), false, false, AST::ReuseType); }
    break;

  case 94:
/* Line 670 of lalr1.cc  */
#line 667 "../../src-common/cfdg.ypp"
    { (yyval.expression) = nullptr; }
    break;

  case 95:
/* Line 670 of lalr1.cc  */
#line 668 "../../src-common/cfdg.ypp"
    { (yyval.expression) = nullptr; }
    break;

  case 96:
/* Line 670 of lalr1.cc  */
#line 672 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 98:
/* Line 670 of lalr1.cc  */
#line 679 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 100:
/* Line 670 of lalr1.cc  */
#line 686 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            mod_ptr mod((yysemantic_stack_[(4) - (3)].mod)); (yysemantic_stack_[(4) - (3)].mod) = nullptr;
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = new ASTpathOp(*pop, std::move(mod), (yyloc));
        }
    break;

  case 101:
/* Line 670 of lalr1.cc  */
#line 693 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(2) - (1)].string)); (yysemantic_stack_[(2) - (1)].string) = nullptr;
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod)); (yysemantic_stack_[(2) - (2)].mod) = nullptr;
            driver.lexer->maybeVersion = token::CFDG2;
            rep_ptr item(new ASTpathCommand(*cmd, std::move(mod), nullptr, (yyloc)));
            (yyval.component) = item.release();
        }
    break;

  case 102:
/* Line 670 of lalr1.cc  */
#line 703 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            exp_ptr mod((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            (yyval.component) = new ASTpathOp(*pop, std::move(mod), (yyloc));
        }
    break;

  case 103:
/* Line 670 of lalr1.cc  */
#line 709 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(3) - (1)].string)); (yysemantic_stack_[(3) - (1)].string) = nullptr;
            exp_ptr mod;
            (yyval.component) = new ASTpathOp(*pop, std::move(mod), (yyloc));
        }
    break;

  case 104:
/* Line 670 of lalr1.cc  */
#line 715 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(3) - (1)].string)); (yysemantic_stack_[(3) - (1)].string) = nullptr;
            exp_ptr p((yysemantic_stack_[(3) - (2)].expression)); (yysemantic_stack_[(3) - (2)].expression) = nullptr;
            mod_ptr mod((yysemantic_stack_[(3) - (3)].mod)); (yysemantic_stack_[(3) - (3)].mod) = nullptr;
            rep_ptr item = driver.MakeElement(*cmd, std::move(mod),
                                              std::move(p), (yyloc), false);
            (yyval.component) = item.release();
        }
    break;

  case 105:
/* Line 670 of lalr1.cc  */
#line 724 "../../src-common/cfdg.ypp"
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

  case 106:
/* Line 670 of lalr1.cc  */
#line 734 "../../src-common/cfdg.ypp"
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

  case 107:
/* Line 670 of lalr1.cc  */
#line 745 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(4) - (2)].string)); (yysemantic_stack_[(4) - (2)].string) = nullptr;
            exp_ptr p((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            mod_ptr mod((yysemantic_stack_[(4) - (4)].mod)); (yysemantic_stack_[(4) - (4)].mod) = nullptr;
            rep_ptr item = driver.MakeElement(*cmd, std::move(mod), std::move(p), (yyloc), true);
            (yyval.component) = item.release();
        }
    break;

  case 108:
/* Line 670 of lalr1.cc  */
#line 755 "../../src-common/cfdg.ypp"
    { }
    break;

  case 109:
/* Line 670 of lalr1.cc  */
#line 757 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 110:
/* Line 670 of lalr1.cc  */
#line 763 "../../src-common/cfdg.ypp"
    { }
    break;

  case 111:
/* Line 670 of lalr1.cc  */
#line 765 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 112:
/* Line 670 of lalr1.cc  */
#line 771 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer(driver.switchStack.top());
        }
    break;

  case 115:
/* Line 670 of lalr1.cc  */
#line 782 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(1) - (1)].component); 
        }
    break;

  case 116:
/* Line 670 of lalr1.cc  */
#line 786 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(1) - (1)].defObj);
        }
    break;

  case 117:
/* Line 670 of lalr1.cc  */
#line 790 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(1) - (1)].loopObj);
            driver.pop_repContainer((yysemantic_stack_[(1) - (1)].loopObj));
            if ((yysemantic_stack_[(1) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(1) - (1)].loopObj);
                (yyval.component) = nullptr;
            }
        }
    break;

  case 118:
/* Line 670 of lalr1.cc  */
#line 799 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            driver.push_repContainer((yysemantic_stack_[(2) - (1)].loopObj)->mFinallyBody);
        }
    break;

  case 119:
/* Line 670 of lalr1.cc  */
#line 802 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].loopObj));
            (yyval.component) = (yysemantic_stack_[(4) - (1)].loopObj);
            if ((yysemantic_stack_[(4) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(4) - (1)].loopObj);
                (yyval.component) = nullptr;
            }
        }
    break;

  case 120:
/* Line 670 of lalr1.cc  */
#line 811 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].ifObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].ifObj));
            if ((yysemantic_stack_[(2) - (1)].ifObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].ifObj);
                (yyval.component) = nullptr;
            }
        }
    break;

  case 121:
/* Line 670 of lalr1.cc  */
#line 820 "../../src-common/cfdg.ypp"
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
#line 829 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].component);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].component));
            if ((yysemantic_stack_[(2) - (1)].component)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].component);
                (yyval.component) = nullptr;
            }
        }
    break;

  case 123:
/* Line 670 of lalr1.cc  */
#line 839 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].switchObj);
            (yysemantic_stack_[(4) - (1)].switchObj)->unify();
            driver.switchStack.pop();
        }
    break;

  case 124:
/* Line 670 of lalr1.cc  */
#line 845 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = nullptr;
        }
    break;

  case 125:
/* Line 670 of lalr1.cc  */
#line 852 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 126:
/* Line 670 of lalr1.cc  */
#line 853 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 127:
/* Line 670 of lalr1.cc  */
#line 854 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 128:
/* Line 670 of lalr1.cc  */
#line 858 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 129:
/* Line 670 of lalr1.cc  */
#line 860 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(2) - (1)].loopObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            if ((yysemantic_stack_[(2) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].loopObj);
                (yyval.component) = nullptr;
            }
        }
    break;

  case 130:
/* Line 670 of lalr1.cc  */
#line 868 "../../src-common/cfdg.ypp"
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

  case 131:
/* Line 670 of lalr1.cc  */
#line 880 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 132:
/* Line 670 of lalr1.cc  */
#line 881 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 135:
/* Line 670 of lalr1.cc  */
#line 884 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 140:
/* Line 670 of lalr1.cc  */
#line 892 "../../src-common/cfdg.ypp"
    {
            // parse loop mod and loop body with loop index in scope
            (yysemantic_stack_[(3) - (1)].loopObj)->mLoopModHolder.reset((yysemantic_stack_[(3) - (2)].mod)); (yysemantic_stack_[(3) - (2)].mod) = nullptr;
            (yyval.loopObj) = (yysemantic_stack_[(3) - (1)].loopObj);
            // loopmod gets deleted
        }
    break;

  case 141:
/* Line 670 of lalr1.cc  */
#line 901 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 143:
/* Line 670 of lalr1.cc  */
#line 908 "../../src-common/cfdg.ypp"
    { }
    break;

  case 144:
/* Line 670 of lalr1.cc  */
#line 910 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 145:
/* Line 670 of lalr1.cc  */
#line 916 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (1)].string)); (yysemantic_stack_[(2) - (1)].string) = nullptr;
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod)); (yysemantic_stack_[(2) - (2)].mod) = nullptr;
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, nullptr, (yylocation_stack_[(2) - (1)])));
            (yyval.component) = new ASTreplacement(std::move(*r), std::move(mod), (yyloc));
        }
    break;

  case 146:
/* Line 670 of lalr1.cc  */
#line 925 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 147:
/* Line 670 of lalr1.cc  */
#line 927 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].loopObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            if ((yysemantic_stack_[(2) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].loopObj);
                (yyval.component) = nullptr;
            }
        }
    break;

  case 148:
/* Line 670 of lalr1.cc  */
#line 938 "../../src-common/cfdg.ypp"
    { ++driver.mLocalStackDepth; }
    break;

  case 149:
/* Line 670 of lalr1.cc  */
#line 938 "../../src-common/cfdg.ypp"
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

  case 150:
/* Line 670 of lalr1.cc  */
#line 953 "../../src-common/cfdg.ypp"
    {
            str_ptr var((yysemantic_stack_[(4) - (2)].string)); (yysemantic_stack_[(4) - (2)].string) = nullptr;
            exp_ptr index((yysemantic_stack_[(4) - (4)].expression)); (yysemantic_stack_[(4) - (4)].expression) = nullptr;
            int nameIndex = driver.StringToShape(*var, (yylocation_stack_[(4) - (2)]), false);
            loop_ptr loop(new ASTloop(nameIndex, *var, (yylocation_stack_[(4) - (2)]), std::move(index), (yylocation_stack_[(4) - (4)]), nullptr));
            driver.push_repContainer(loop->mLoopBody);
            (yyval.loopObj) = loop.release();
        }
    break;

  case 151:
/* Line 670 of lalr1.cc  */
#line 962 "../../src-common/cfdg.ypp"
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

  case 152:
/* Line 670 of lalr1.cc  */
#line 972 "../../src-common/cfdg.ypp"
    {
            exp_ptr count((yysemantic_stack_[(2) - (2)].expression)); (yysemantic_stack_[(2) - (2)].expression) = nullptr;
            static const std::string dummyvar("~~inaccessiblevar~~");
            loop_ptr loop(new ASTloop(driver.StringToShape(dummyvar, (yylocation_stack_[(2) - (1)]), false), 
                                      dummyvar, (yylocation_stack_[(2) - (1)]), std::move(count), (yylocation_stack_[(2) - (2)]), nullptr));
            driver.push_repContainer(loop->mLoopBody);
            (yyval.loopObj) = loop.release();
        }
    break;

  case 153:
/* Line 670 of lalr1.cc  */
#line 983 "../../src-common/cfdg.ypp"
    {
            exp_ptr cond((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            if_ptr ifHeader(new ASTif(std::move(cond), (yylocation_stack_[(4) - (3)])));
            driver.push_repContainer(ifHeader->mThenBody);
            (yyval.ifObj) = ifHeader.release();
        }
    break;

  case 154:
/* Line 670 of lalr1.cc  */
#line 992 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ifObj));
            driver.push_repContainer((yysemantic_stack_[(3) - (1)].ifObj)->mElseBody);
            (yyval.ifObj) = (yysemantic_stack_[(3) - (1)].ifObj);
        }
    break;

  case 155:
/* Line 670 of lalr1.cc  */
#line 1000 "../../src-common/cfdg.ypp"
    {
            exp_ptr mods((yysemantic_stack_[(2) - (2)].expression)); (yysemantic_stack_[(2) - (2)].expression) = nullptr;
            if ((yysemantic_stack_[(2) - (1)].modToken) != ASTmodTerm::transform)
                error((yylocation_stack_[(2) - (1)]), "Syntax error");
            ASTtransform* trans = new ASTtransform((yyloc), std::move(mods));
            driver.push_repContainer(trans->mBody);
            (yyval.component) = trans;
        }
    break;

  case 156:
/* Line 670 of lalr1.cc  */
#line 1008 "../../src-common/cfdg.ypp"
    {
            exp_ptr mods((yysemantic_stack_[(2) - (2)].expression)); (yysemantic_stack_[(2) - (2)].expression) = nullptr;
            ASTtransform* trans = new ASTtransform((yyloc), std::move(mods));
            trans->mClone = true;
            driver.push_repContainer(trans->mBody);
            (yyval.component) = trans;
        }
    break;

  case 157:
/* Line 670 of lalr1.cc  */
#line 1018 "../../src-common/cfdg.ypp"
    {
            exp_ptr caseVal((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            switch_ptr switchHeader(new ASTswitch(std::move(caseVal), (yylocation_stack_[(4) - (3)])));
            driver.switchStack.push(switchHeader.get());
            (yyval.switchObj) = switchHeader.release();
        }
    break;

  case 158:
/* Line 670 of lalr1.cc  */
#line 1027 "../../src-common/cfdg.ypp"
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

  case 159:
/* Line 670 of lalr1.cc  */
#line 1055 "../../src-common/cfdg.ypp"
    {
            if (!driver.switchStack.top()->mElseBody.mBody.empty()) {
                driver.error((yyloc), "There can only be one 'else:' clause");
            } else {
                driver.push_repContainer(driver.switchStack.top()->mElseBody);
            }
            (yyval.modToken) = 0;
        }
    break;

  case 160:
/* Line 670 of lalr1.cc  */
#line 1066 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod)); (yysemantic_stack_[(3) - (2)].mod) = nullptr;
            (yyval.mod) = driver.MakeModification(std::move(mod), (yyloc), true);
        }
    break;

  case 161:
/* Line 670 of lalr1.cc  */
#line 1071 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod)); (yysemantic_stack_[(3) - (2)].mod) = nullptr;
            (yyval.mod) = driver.MakeModification(std::move(mod), (yyloc), false);
        }
    break;

  case 162:
/* Line 670 of lalr1.cc  */
#line 1078 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod)); (yysemantic_stack_[(3) - (2)].mod) = nullptr;
            (yyval.mod) = driver.MakeModification(std::move(mod), (yyloc), true);
        }
    break;

  case 163:
/* Line 670 of lalr1.cc  */
#line 1083 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(5) - (3)].mod)); (yysemantic_stack_[(5) - (3)].mod) = nullptr;
            (yyval.mod) = driver.MakeModification(std::move(mod), (yyloc), false);
        }
    break;

  case 164:
/* Line 670 of lalr1.cc  */
#line 1090 "../../src-common/cfdg.ypp"
    {
            term_ptr mod((yysemantic_stack_[(2) - (2)].term)); (yysemantic_stack_[(2) - (2)].term) = nullptr;
            driver.MakeModTerm((yysemantic_stack_[(2) - (1)].mod)->modExp, std::move(mod));
            (yyval.mod) = (yysemantic_stack_[(2) - (1)].mod);
        }
    break;

  case 165:
/* Line 670 of lalr1.cc  */
#line 1095 "../../src-common/cfdg.ypp"
    {
            static const yy::location def;
            ASTmodification* m = new ASTmodification(def);
            m->flags = 0;
            (yyval.mod) = m;
        }
    break;

  case 166:
/* Line 670 of lalr1.cc  */
#line 1104 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].expression)); (yysemantic_stack_[(2) - (2)].expression) = nullptr;
            (yyval.term) = new ASTmodTerm(static_cast<ASTmodTerm::modTypeEnum>((yysemantic_stack_[(2) - (1)].modToken)), mod.release(), (yyloc));
        }
    break;

  case 167:
/* Line 670 of lalr1.cc  */
#line 1109 "../../src-common/cfdg.ypp"
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

  case 168:
/* Line 670 of lalr1.cc  */
#line 1119 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string)); (yysemantic_stack_[(2) - (2)].string) = nullptr;
            (yyval.term) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 169:
/* Line 670 of lalr1.cc  */
#line 1124 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string)); (yysemantic_stack_[(2) - (2)].string) = nullptr;
            (yyval.term) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 170:
/* Line 670 of lalr1.cc  */
#line 1131 "../../src-common/cfdg.ypp"
    {
            ASTrepContainer* tempHolder = new ASTrepContainer();
            driver.push_repContainer(*tempHolder);
            (yyval.bodyObj) = tempHolder;
        }
    break;

  case 171:
/* Line 670 of lalr1.cc  */
#line 1139 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = (yysemantic_stack_[(5) - (4)].expression);
        }
    break;

  case 174:
/* Line 670 of lalr1.cc  */
#line 1151 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].defObj));
        }
    break;

  case 175:
/* Line 670 of lalr1.cc  */
#line 1157 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTexpression::Append((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 176:
/* Line 670 of lalr1.cc  */
#line 1161 "../../src-common/cfdg.ypp"
    { 
            (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); 
        }
    break;

  case 177:
/* Line 670 of lalr1.cc  */
#line 1168 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = (yysemantic_stack_[(3) - (1)].expression)->append(new ASTparen((yysemantic_stack_[(3) - (3)].expression)));
        }
    break;

  case 178:
/* Line 670 of lalr1.cc  */
#line 1172 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = new ASTcons(new ASTparen((yysemantic_stack_[(1) - (1)].expression)), nullptr);
        }
    break;

  case 179:
/* Line 670 of lalr1.cc  */
#line 1178 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 180:
/* Line 670 of lalr1.cc  */
#line 1180 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 181:
/* Line 670 of lalr1.cc  */
#line 1182 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 182:
/* Line 670 of lalr1.cc  */
#line 1184 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 183:
/* Line 670 of lalr1.cc  */
#line 1186 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), nullptr);; }
    break;

  case 184:
/* Line 670 of lalr1.cc  */
#line 1188 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), nullptr);; }
    break;

  case 185:
/* Line 670 of lalr1.cc  */
#line 1190 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression))); (yysemantic_stack_[(3) - (1)].expression) = nullptr; (yysemantic_stack_[(3) - (3)].expression) = nullptr;
            (yyval.expression) = new ASTfunction("rand", std::move(pair), driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 186:
/* Line 670 of lalr1.cc  */
#line 1195 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression))); (yysemantic_stack_[(3) - (1)].expression) = nullptr; (yysemantic_stack_[(3) - (3)].expression) = nullptr;
            (yyval.expression) = new ASTfunction("rand+/-", std::move(pair), driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 187:
/* Line 670 of lalr1.cc  */
#line 1202 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); (yysemantic_stack_[(1) - (1)].string) = nullptr; }
    break;

  case 188:
/* Line 670 of lalr1.cc  */
#line 1204 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 189:
/* Line 670 of lalr1.cc  */
#line 1206 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 190:
/* Line 670 of lalr1.cc  */
#line 1208 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression))); (yysemantic_stack_[(3) - (1)].expression) = nullptr; (yysemantic_stack_[(3) - (3)].expression) = nullptr;
            (yyval.expression) = new ASTfunction("rand", std::move(pair), driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 191:
/* Line 670 of lalr1.cc  */
#line 1213 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression))); (yysemantic_stack_[(3) - (1)].expression) = nullptr; (yysemantic_stack_[(3) - (3)].expression) = nullptr;
            (yyval.expression) = new ASTfunction("rand+/-", std::move(pair), driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 192:
/* Line 670 of lalr1.cc  */
#line 1218 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression));   }
    break;

  case 193:
/* Line 670 of lalr1.cc  */
#line 1220 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('+', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 194:
/* Line 670 of lalr1.cc  */
#line 1222 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('-', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 195:
/* Line 670 of lalr1.cc  */
#line 1224 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('_', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 196:
/* Line 670 of lalr1.cc  */
#line 1226 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('*', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 197:
/* Line 670 of lalr1.cc  */
#line 1228 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('/', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 198:
/* Line 670 of lalr1.cc  */
#line 1230 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), nullptr); }
    break;

  case 199:
/* Line 670 of lalr1.cc  */
#line 1232 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), nullptr); }
    break;

  case 200:
/* Line 670 of lalr1.cc  */
#line 1234 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('!', (yysemantic_stack_[(2) - (2)].expression), nullptr); }
    break;

  case 201:
/* Line 670 of lalr1.cc  */
#line 1236 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('^', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 202:
/* Line 670 of lalr1.cc  */
#line 1238 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('<', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 203:
/* Line 670 of lalr1.cc  */
#line 1240 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('L', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 204:
/* Line 670 of lalr1.cc  */
#line 1242 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('>', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 205:
/* Line 670 of lalr1.cc  */
#line 1244 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('G', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 206:
/* Line 670 of lalr1.cc  */
#line 1246 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('=', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 207:
/* Line 670 of lalr1.cc  */
#line 1248 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('n', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 208:
/* Line 670 of lalr1.cc  */
#line 1250 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('&', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 209:
/* Line 670 of lalr1.cc  */
#line 1252 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('|', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 210:
/* Line 670 of lalr1.cc  */
#line 1254 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('X', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 211:
/* Line 670 of lalr1.cc  */
#line 1256 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 212:
/* Line 670 of lalr1.cc  */
#line 1258 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].mod); }
    break;

  case 213:
/* Line 670 of lalr1.cc  */
#line 1262 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 214:
/* Line 670 of lalr1.cc  */
#line 1264 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 215:
/* Line 670 of lalr1.cc  */
#line 1266 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 216:
/* Line 670 of lalr1.cc  */
#line 1268 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression))); (yysemantic_stack_[(3) - (1)].expression) = nullptr; (yysemantic_stack_[(3) - (3)].expression) = nullptr;
            (yyval.expression) = new ASTfunction("rand", std::move(pair), driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 217:
/* Line 670 of lalr1.cc  */
#line 1273 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression))); (yysemantic_stack_[(3) - (1)].expression) = nullptr; (yysemantic_stack_[(3) - (3)].expression) = nullptr;
            (yyval.expression) = new ASTfunction("rand+/-", std::move(pair), driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 218:
/* Line 670 of lalr1.cc  */
#line 1278 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('+', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 219:
/* Line 670 of lalr1.cc  */
#line 1280 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('-', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 220:
/* Line 670 of lalr1.cc  */
#line 1282 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('_', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 221:
/* Line 670 of lalr1.cc  */
#line 1284 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('*', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 222:
/* Line 670 of lalr1.cc  */
#line 1286 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('/', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 223:
/* Line 670 of lalr1.cc  */
#line 1288 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), nullptr); }
    break;

  case 224:
/* Line 670 of lalr1.cc  */
#line 1290 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), nullptr); }
    break;

  case 225:
/* Line 670 of lalr1.cc  */
#line 1292 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('!', (yysemantic_stack_[(2) - (2)].expression), nullptr); }
    break;

  case 226:
/* Line 670 of lalr1.cc  */
#line 1294 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('^', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 227:
/* Line 670 of lalr1.cc  */
#line 1296 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('<', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 228:
/* Line 670 of lalr1.cc  */
#line 1298 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('L', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 229:
/* Line 670 of lalr1.cc  */
#line 1300 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('>', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 230:
/* Line 670 of lalr1.cc  */
#line 1302 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('G', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 231:
/* Line 670 of lalr1.cc  */
#line 1304 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('=', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 232:
/* Line 670 of lalr1.cc  */
#line 1306 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('n', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 233:
/* Line 670 of lalr1.cc  */
#line 1308 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('&', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 234:
/* Line 670 of lalr1.cc  */
#line 1310 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('|', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 235:
/* Line 670 of lalr1.cc  */
#line 1312 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('X', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 236:
/* Line 670 of lalr1.cc  */
#line 1314 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 237:
/* Line 670 of lalr1.cc  */
#line 1316 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].mod); }
    break;

  case 238:
/* Line 670 of lalr1.cc  */
#line 1320 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string)); (yysemantic_stack_[(3) - (1)].string) = nullptr;
            (yyval.expression) = driver.MakeFunction(std::move(func), nullptr, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 239:
/* Line 670 of lalr1.cc  */
#line 1325 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            (yyval.expression) = driver.MakeFunction(std::move(func), std::move(args), (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), true);
        }
    break;

  case 240:
/* Line 670 of lalr1.cc  */
#line 1331 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            (yyval.expression) = driver.MakeArray(std::move(func), std::move(args), (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]));
        }
    break;

  case 241:
/* Line 670 of lalr1.cc  */
#line 1337 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            (yyval.expression) = driver.MakeFunction(std::move(func), std::move(args), (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 242:
/* Line 670 of lalr1.cc  */
#line 1343 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer(nullptr);
            cont_ptr vars((yysemantic_stack_[(2) - (1)].bodyObj)); (yysemantic_stack_[(2) - (1)].bodyObj) = nullptr;
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression)); (yysemantic_stack_[(2) - (2)].expression) = nullptr;
            (yyval.expression) = driver.MakeLet((yylocation_stack_[(2) - (1)]), std::move(vars), std::move(exp));
        }
    break;

  case 243:
/* Line 670 of lalr1.cc  */
#line 1350 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string)); (yysemantic_stack_[(1) - (1)].string) = nullptr;
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 244:
/* Line 670 of lalr1.cc  */
#line 1357 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string)); (yysemantic_stack_[(3) - (1)].string) = nullptr;
            (yyval.expression) = driver.MakeFunction(std::move(func), nullptr, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 245:
/* Line 670 of lalr1.cc  */
#line 1362 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            (yyval.expression) = driver.MakeFunction(std::move(func), std::move(args), (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 246:
/* Line 670 of lalr1.cc  */
#line 1368 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            (yyval.expression) = driver.MakeArray(std::move(func), std::move(args), (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]));
        }
    break;

  case 247:
/* Line 670 of lalr1.cc  */
#line 1374 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression)); (yysemantic_stack_[(4) - (3)].expression) = nullptr;
            (yyval.expression) = driver.MakeFunction(std::move(func), std::move(args), (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 248:
/* Line 670 of lalr1.cc  */
#line 1380 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string)); (yysemantic_stack_[(4) - (1)].string) = nullptr;
            exp_ptr args(new ASTexpression((yyloc), false, false, AST::ReuseType));
            (yyval.expression) = driver.MakeFunction(std::move(func), std::move(args), (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 249:
/* Line 670 of lalr1.cc  */
#line 1386 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer(nullptr);
            cont_ptr vars((yysemantic_stack_[(2) - (1)].bodyObj)); (yysemantic_stack_[(2) - (1)].bodyObj) = nullptr;
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression)); (yysemantic_stack_[(2) - (2)].expression) = nullptr;
            (yyval.expression) = driver.MakeLet((yylocation_stack_[(2) - (1)]), std::move(vars), std::move(exp));
        }
    break;

  case 250:
/* Line 670 of lalr1.cc  */
#line 1393 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string)); (yysemantic_stack_[(1) - (1)].string) = nullptr;
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 251:
/* Line 670 of lalr1.cc  */
#line 1400 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 252:
/* Line 670 of lalr1.cc  */
#line 1402 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(1) - (1)].string); }
    break;


/* Line 670 of lalr1.cc  */
#line 2756 "cfdg.tab.cpp"
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
  const short int CfdgParser::yypact_ninf_ = -286;
  const short int
  CfdgParser::yypact_[] =
  {
       232,  -286,  -286,    23,  1257,  1278,  -286,   186,  -286,    12,
      46,    84,   133,  -286,  -286,    91,   215,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,     0,    90,  -286,    92,  -286,
     207,    10,    96,   150,   120,     0,    81,   215,   124,     0,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,   598,  -286,   139,
    -286,  -286,  -286,   149,   157,  -286,  -286,   309,   239,   238,
     242,  -286,  -286,  -286,   247,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,   259,   276,   281,   285,  -286,   287,
    -286,     7,   340,  -286,  -286,  -286,   281,   281,   343,  -286,
     330,   215,  -286,   303,  -286,   319,  -286,   320,   598,  -286,
     598,   598,   598,   322,  -286,   324,  1013,  -286,  -286,   178,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,   112,    35,
      95,   361,   400,   276,  -286,   374,     7,  -286,   376,    21,
    -286,    13,  -286,    18,  -286,  -286,   -15,  -286,   384,   386,
    -286,  -286,  -286,   598,   436,   598,   333,   333,   333,   734,
    -286,   118,   108,  -286,   598,   598,   598,   598,   598,   598,
     598,   598,   598,   598,   598,   598,   598,   598,   598,   598,
     598,   598,   208,   556,   342,   345,   598,   535,     8,   348,
    -286,   246,  -286,   598,  -286,  -286,  -286,  -286,   392,   276,
     457,   457,   457,   337,   324,   259,   301,   323,   389,   264,
    -286,  -286,  -286,  -286,   352,  -286,  -286,  -286,   265,     0,
    -286,  -286,  -286,  -286,   402,     5,   272,  -286,  -286,  -286,
    -286,   396,     0,   351,  -286,   619,  -286,   619,   619,   598,
    -286,  -286,    62,  1044,  -286,  -286,  -286,   131,  -286,   138,
    -286,  -286,  -286,  -286,    21,  -286,  -286,  -286,   765,   356,
    -286,   156,   641,  -286,   125,  -286,   411,   414,  -286,   358,
    -286,   172,   172,   650,   650,   650,   650,  1198,  1198,  1158,
    1114,  1068,  1013,    93,    93,    93,   333,   333,   333,   259,
     419,    48,  1013,   598,   598,  1013,  1013,  -286,  -286,   478,
    -286,  1013,  -286,   457,  -286,   416,  -286,  -286,  -286,  -286,
     276,   276,  -286,  -286,   375,   377,  -286,   379,  -286,   389,
     389,   598,   324,   389,   116,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,   373,  -286,
    -286,  -286,  -286,  -286,   388,   388,   388,   796,   619,  -286,
     619,   619,   619,   619,   619,   619,   619,   619,   619,   619,
     619,   619,   619,   619,   619,   619,   619,   426,  -286,  -286,
    -286,  -286,  -286,  -286,   378,   577,   276,   598,   598,   827,
     858,  -286,   889,   457,  -286,   347,  -286,    37,  -286,  -286,
     598,   499,   598,  -286,  -286,   920,  -286,   346,   389,   389,
    -286,     0,   185,   179,   380,  -286,  1044,   271,   271,   711,
     711,   711,   711,  1218,  1218,  1178,  1136,  1091,   249,   249,
     249,   388,   388,   388,  -286,    50,  -286,   951,  -286,  1013,
    1013,   276,  -286,  -286,  -286,  -286,   391,   598,  -286,  -286,
     457,   982,  -286,   158,   672,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,   703,  -286,  -286,  -286,  -286,
    -286
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  CfdgParser::yydefact_[] =
  {
         0,     5,     7,     0,     2,     3,     1,     0,    30,     0,
       0,    54,     0,    52,    42,     0,     0,    29,    53,     4,
      23,    19,    20,    17,    18,     0,     0,    21,     0,    22,
       0,     0,    73,     0,     0,     0,     0,     0,    46,     0,
       6,    16,     9,    10,     8,    15,    62,     0,    63,    13,
      97,    14,    39,     0,     0,    11,    12,    50,     0,    70,
      78,    25,    26,    24,     0,    27,    43,    44,    40,   165,
     165,    51,   142,    99,    95,     0,     0,    89,    74,    89,
      65,     0,     0,    37,    35,    64,     0,     0,     0,    38,
       0,     0,    36,     0,   170,   250,   187,     0,     0,   188,
       0,     0,     0,   165,   212,     0,    55,   189,    68,     0,
      97,    97,    32,    33,    34,    71,    31,    28,     0,     0,
       0,     0,     0,    49,    48,     0,     0,    67,     0,     0,
      75,     0,    85,    84,    91,    87,     0,    60,     0,     0,
      57,    45,    41,     0,     0,     0,   200,   198,   199,     0,
     165,     0,     0,   249,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   251,     0,
     252,     0,    69,     0,   116,   115,    96,   124,   117,     0,
       0,     0,     0,     0,     0,    95,     0,     0,     0,     0,
     161,   164,   160,   251,     0,    72,   146,   141,     0,     0,
     133,   134,   137,   139,   138,   251,     0,    79,   128,    98,
     130,     0,     0,     0,   213,     0,   214,     0,     0,     0,
      94,   237,     0,   178,   215,    47,    59,     0,    56,     0,
      83,    81,    82,    80,     0,    90,    61,    58,     0,     0,
     244,     0,     0,   211,     0,   162,     0,     0,   174,     0,
     173,   190,   191,   203,   202,   205,   204,   206,   207,   208,
     209,   210,   192,   194,   193,   195,   196,   197,   201,    95,
       0,   250,   152,     0,     0,   156,   155,   126,   125,     0,
     127,    66,   118,     0,    97,   120,   109,   121,   122,   113,
       0,     0,    76,    77,     0,   243,   179,     0,   180,     0,
       0,     0,     0,   166,   176,   182,   168,   169,   148,   142,
     147,   144,   145,   136,   135,   132,   131,   165,     0,    99,
     111,   129,   101,    93,   225,   223,   224,     0,     0,    92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,    88,    86,
     247,   248,   245,   246,     0,     0,     0,     0,     0,     0,
       0,   103,     0,     0,   140,     0,   154,     0,   106,   104,
       0,     0,     0,   183,   184,     0,   242,   175,     0,     0,
     167,     0,     0,     0,     0,   236,   177,   216,   217,   228,
     227,   230,   229,   231,   232,   233,   234,   235,   219,   218,
     220,   221,   222,   226,   163,   250,   172,     0,   107,   151,
     150,   153,   157,   102,   119,   108,     0,     0,   123,   112,
       0,     0,   238,     0,     0,   181,   185,   186,   149,   143,
     100,   110,   171,   105,   159,     0,   114,   241,   239,   240,
     158
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yypgoto_[] =
  {
      -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
     447,   -26,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
     448,  -145,  -286,  -286,  -286,   451,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,   197,   218,   381,   -20,  -181,  -102,   132,
     245,  -286,  -188,  -286,  -286,  -286,   -87,  -286,  -286,  -286,
    -286,  -286,   152,  -286,   261,  -286,  -109,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,   -34,   -73,   -35,  -286,   -78,  -184,
    -286,   113,  -286,  -138,  -285,   -81,  -182,  -286,   -92,   -79
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yydefgoto_[] =
  {
        -1,     3,     4,     5,    40,    19,    20,    41,    21,    42,
      22,    68,    91,    44,    23,    24,    25,    45,    46,    47,
     183,   184,    49,    50,    51,    26,    27,    53,    54,    55,
      56,    28,    29,   135,   136,   127,    82,   123,   109,   121,
     218,   185,   295,   331,   377,   429,   296,   373,   187,   219,
     220,   188,   120,   320,   206,   207,   208,   391,   189,   190,
     191,   192,   193,   430,    71,   104,   118,   201,   105,   153,
     259,   260,   313,   232,   314,   106,   233,   315,   107,   195
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char CfdgParser::yytable_ninf_ = -91;
  const short int
  CfdgParser::yytable_[] =
  {
        83,    84,   124,   297,   298,    92,   251,   258,   196,   197,
     300,    89,   221,   131,   301,   324,    88,   146,    85,   147,
     148,   149,   186,     6,   383,   384,   132,   131,   387,    76,
     234,   194,   240,   133,   244,   119,    77,   242,    59,   241,
     132,   209,   222,   334,   243,   335,   336,   133,   245,   231,
     235,   426,   234,   427,   198,   199,   125,   128,   368,    69,
      85,    70,   248,   325,   252,   142,   138,   139,   151,   287,
     134,   231,    60,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,    85,   282,   279,    61,   285,   286,   202,   366,   428,
      86,    63,   291,   436,   437,   374,   144,    87,   144,   186,
     186,   338,   194,   194,   194,   254,   293,    64,   194,   194,
     312,   203,    59,   204,    78,   339,   180,   256,   386,   209,
      80,   198,   199,   234,   257,   234,   234,   198,   199,    81,
     388,   389,   222,    62,   198,   199,   169,   170,   337,    65,
     171,    72,   231,    73,   231,   231,   396,   205,   397,   398,
     399,   400,   401,   402,   403,   404,   405,   406,   407,   408,
     409,   410,   411,   412,   413,   322,    79,   200,    81,    69,
     244,    70,   390,   255,    90,   424,   172,   244,   332,   173,
     364,   174,   375,   175,   357,   176,    94,   177,   198,   199,
     108,   358,   369,   370,   178,   338,   179,   338,   372,   180,
     110,   203,    57,   204,   181,   194,   180,    58,   111,   362,
     258,   448,   166,   167,   168,   169,   170,   378,   379,   171,
     385,   312,   312,    74,   203,   312,     1,     2,    75,   180,
     182,   440,   446,   433,    66,    67,   234,   439,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   231,   115,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   417,   221,   419,   420,   186,   234,
     316,   203,   393,   418,   317,   194,   180,   194,   114,   431,
     116,   434,   354,   355,   289,   117,   356,   290,   231,   172,
     312,   312,   173,   209,   174,   222,   175,   122,   176,    94,
     177,   351,   352,   353,   354,   355,   319,   178,   356,   179,
     326,   172,   180,   327,   173,   103,   174,   181,   175,    81,
     176,    94,   177,   126,   237,   129,   445,   239,   443,   178,
     137,   179,   194,   140,   180,   172,   141,   438,   173,   181,
     174,   143,   175,   302,   176,    94,   177,   112,   113,   210,
     388,   389,   211,   178,   212,   179,   213,   144,   180,   145,
     214,   150,   152,   181,   236,   303,   238,   215,   210,   204,
     171,   211,   180,   212,   246,   213,   247,   216,   299,   214,
     283,   288,   304,   284,   292,   318,   215,    94,   204,   425,
     223,   180,   323,    93,   333,   305,   216,   306,    94,   361,
     307,    80,   203,   217,    85,   365,    95,   180,   224,   367,
     376,    97,   328,   380,   327,   381,   -90,   308,   382,   309,
     310,   359,   441,   414,   225,   356,   249,   311,   226,    93,
     227,   228,    43,    48,    94,   444,    52,   329,   229,   103,
     130,   394,    95,   230,   224,   172,   330,    97,   173,   321,
     174,   392,   175,     0,   176,    94,   177,     0,   416,     0,
     225,     0,     0,   178,   226,   179,   227,   228,   180,     0,
       0,    93,     0,   181,   229,   103,    94,     0,     0,   250,
       0,     0,     0,     0,    95,     0,    96,     0,     0,    97,
       0,     0,    93,     0,     0,     0,     0,    94,   294,     0,
       0,     0,    98,     0,     0,    95,    99,   224,   100,   101,
      97,     0,     0,     0,     0,     0,   102,   103,     0,     0,
       0,   371,     0,   225,     0,    80,     0,   226,    93,   227,
     228,     0,     0,    94,     0,     0,     0,   229,   103,     0,
       0,    95,   432,    96,     0,     0,    97,     0,     0,    93,
       0,     0,     0,     0,    94,   280,     0,     0,     0,    98,
       0,     0,   281,    99,    96,   100,   101,    97,     0,     0,
      93,     0,     0,   102,   103,    94,   256,     0,     0,     0,
      98,     0,     0,   415,    99,    96,   100,   101,    97,     0,
       0,    93,     0,     0,   102,   103,    94,     0,     0,     0,
       0,    98,     0,     0,    95,    99,    96,   100,   101,    97,
       0,     0,    93,     0,     0,   102,   103,    94,     0,     0,
       0,     0,    98,     0,     0,    95,    99,   224,   100,   101,
      97,     0,     0,     0,     0,     0,   102,   103,     0,     0,
       0,     0,     0,   225,     0,   154,   155,   226,     0,   227,
     228,     0,     0,     0,   154,   155,     0,   229,   103,   156,
     157,   158,   159,   160,   161,     0,   162,   163,   164,     0,
     165,   166,   167,   168,   169,   170,   154,   155,   171,     0,
     166,   167,   168,   169,   170,     0,   363,   171,     0,     0,
     156,   157,   158,   159,   160,   161,     0,   162,   163,   164,
       0,   165,   166,   167,   168,   169,   170,   154,   155,   171,
       0,     0,     0,     0,     0,   340,   341,   449,     0,     0,
       0,   156,   157,   158,   159,   160,   161,     0,   162,   163,
     164,     0,   165,   166,   167,   168,   169,   170,   154,   155,
     171,   351,   352,   353,   354,   355,     0,   450,   356,     0,
       0,     0,   156,   157,   158,   159,   160,   161,     0,   162,
     163,   164,     0,   165,   166,   167,   168,   169,   170,   154,
     155,   171,     0,     0,     0,     0,     0,   253,     0,     0,
       0,     0,     0,   156,   157,   158,   159,   160,   161,     0,
     162,   163,   164,     0,   165,   166,   167,   168,   169,   170,
     154,   155,   171,     0,     0,     0,     0,     0,   360,     0,
       0,     0,     0,     0,   156,   157,   158,   159,   160,   161,
       0,   162,   163,   164,     0,   165,   166,   167,   168,   169,
     170,   154,   155,   171,     0,     0,     0,     0,     0,   395,
       0,     0,     0,     0,     0,   156,   157,   158,   159,   160,
     161,     0,   162,   163,   164,     0,   165,   166,   167,   168,
     169,   170,   154,   155,   171,     0,     0,     0,     0,     0,
     421,     0,     0,     0,     0,     0,   156,   157,   158,   159,
     160,   161,     0,   162,   163,   164,     0,   165,   166,   167,
     168,   169,   170,   154,   155,   171,     0,     0,     0,     0,
       0,   422,     0,     0,     0,     0,     0,   156,   157,   158,
     159,   160,   161,     0,   162,   163,   164,     0,   165,   166,
     167,   168,   169,   170,   154,   155,   171,     0,     0,     0,
       0,     0,   423,     0,     0,     0,     0,     0,   156,   157,
     158,   159,   160,   161,     0,   162,   163,   164,     0,   165,
     166,   167,   168,   169,   170,   154,   155,   171,     0,     0,
       0,     0,     0,   435,     0,     0,     0,     0,     0,   156,
     157,   158,   159,   160,   161,     0,   162,   163,   164,     0,
     165,   166,   167,   168,   169,   170,   154,   155,   171,     0,
       0,     0,     0,     0,   442,     0,     0,     0,     0,     0,
     156,   157,   158,   159,   160,   161,     0,   162,   163,   164,
       0,   165,   166,   167,   168,   169,   170,   154,   155,   171,
       0,     0,     0,     0,     0,   447,     0,     0,     0,     0,
       0,   156,   157,   158,   159,   160,   161,     0,   162,   163,
     164,     0,   165,   166,   167,   168,   169,   170,   340,   341,
     171,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   342,   343,   344,   345,   346,   347,     0,   348,
     349,   350,   154,   155,   351,   352,   353,   354,   355,     0,
       0,   356,     0,     0,     0,     0,   156,   157,   158,   159,
     160,   161,     0,   162,   163,   340,   341,     0,   166,   167,
     168,   169,   170,     0,     0,   171,     0,     0,     0,   342,
     343,   344,   345,   346,   347,     0,   348,   349,   154,   155,
       0,   351,   352,   353,   354,   355,     0,     0,   356,     0,
       0,     0,   156,   157,   158,   159,   160,   161,     0,   162,
     340,   341,     0,     0,   166,   167,   168,   169,   170,     0,
       0,   171,     0,     0,   342,   343,   344,   345,   346,   347,
       0,   348,   154,   155,     0,     0,   351,   352,   353,   354,
     355,     0,     0,   356,     0,     0,   156,   157,   158,   159,
     160,   161,   340,   341,     0,     0,     0,     0,   166,   167,
     168,   169,   170,     0,     0,   171,   342,   343,   344,   345,
     346,   347,   154,   155,     0,     0,     0,     0,   351,   352,
     353,   354,   355,     0,     0,   356,   156,   157,   158,   159,
       0,     0,   340,   341,     0,     0,     0,     0,   166,   167,
     168,   169,   170,     0,     0,   171,   342,   343,   344,   345,
       7,     0,     0,     8,     9,    10,     0,     0,   351,   352,
     353,   354,   355,     0,     0,   356,    11,    12,    13,     0,
      14,    30,     0,    15,    31,    32,    33,     0,     0,    16,
      17,    18,     0,     0,     0,     0,     0,    34,     0,    35,
       0,    14,     0,     0,    36,     0,     0,     0,     0,     0,
      37,    38,    39
  };

  /* YYCHECK.  */
  const short int
  CfdgParser::yycheck_[] =
  {
        34,    35,    75,   191,   192,    39,   144,   152,   110,   111,
     194,    37,   121,     6,   195,    10,    36,    98,    10,   100,
     101,   102,   109,     0,   309,   310,    19,     6,   313,    19,
     122,   109,    19,    26,    49,    70,    26,    19,    26,    26,
      19,   120,   121,   225,    26,   227,   228,    26,    63,   122,
     123,    14,   144,    16,    19,    20,    76,    77,    10,    59,
      10,    61,   143,    58,   145,    91,    86,    87,   103,    61,
      63,   144,    26,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,    10,   173,   172,    10,   176,   177,    62,   279,    62,
      19,    10,   183,   388,   389,   293,    58,    26,    58,   196,
     197,    49,   190,   191,   192,   150,   189,    26,   196,   197,
     198,    26,    26,    28,    28,    63,    31,    19,   312,   208,
      10,    19,    20,   225,    26,   227,   228,    19,    20,    58,
      24,    25,   221,    10,    19,    20,    53,    54,   229,    58,
      57,    61,   225,    61,   227,   228,   338,    62,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   209,    26,    65,    58,    59,
      49,    61,    66,    65,    60,   373,     8,    49,   222,    11,
      65,    13,   294,    15,    63,    17,    18,    19,    19,    20,
      61,    63,   283,   284,    26,    49,    28,    49,   289,    31,
      61,    26,    26,    28,    36,   293,    31,    31,    61,    63,
     365,    63,    50,    51,    52,    53,    54,   300,   301,    57,
     311,   309,   310,    26,    26,   313,     4,     5,    31,    31,
      62,    62,   430,   381,    29,    30,   338,    62,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   338,    28,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   365,   394,   367,   368,   375,   381,
      26,    26,   327,   366,    30,   373,    31,   375,    59,   380,
      58,   382,    53,    54,    58,    58,    57,    61,   381,     8,
     388,   389,    11,   392,    13,   394,    15,    58,    17,    18,
      19,    50,    51,    52,    53,    54,    61,    26,    57,    28,
      58,     8,    31,    61,    11,    59,    13,    36,    15,    58,
      17,    18,    19,    58,   126,    58,   427,   129,   421,    26,
      10,    28,   430,    10,    31,     8,    26,   391,    11,    36,
      13,    58,    15,    62,    17,    18,    19,    58,    59,     8,
      24,    25,    11,    26,    13,    28,    15,    58,    31,    59,
      19,    59,    58,    36,    10,    62,    10,    26,     8,    28,
      57,    11,    31,    13,    10,    15,    10,    36,    61,    19,
      58,    53,    13,    58,    12,    53,    26,    18,    28,    62,
      10,    31,    10,    13,    63,    26,    36,    28,    18,    63,
      31,    10,    26,    62,    10,    67,    26,    31,    28,    10,
      14,    31,    36,    58,    61,    58,    10,    48,    59,    50,
      51,   244,    62,    65,    44,    57,    10,    58,    48,    13,
      50,    51,     5,     5,    18,    64,     5,    61,    58,    59,
      79,   329,    26,    63,    28,     8,   221,    31,    11,   208,
      13,   319,    15,    -1,    17,    18,    19,    -1,   365,    -1,
      44,    -1,    -1,    26,    48,    28,    50,    51,    31,    -1,
      -1,    13,    -1,    36,    58,    59,    18,    -1,    -1,    63,
      -1,    -1,    -1,    -1,    26,    -1,    28,    -1,    -1,    31,
      -1,    -1,    13,    -1,    -1,    -1,    -1,    18,    61,    -1,
      -1,    -1,    44,    -1,    -1,    26,    48,    28,    50,    51,
      31,    -1,    -1,    -1,    -1,    -1,    58,    59,    -1,    -1,
      -1,    63,    -1,    44,    -1,    10,    -1,    48,    13,    50,
      51,    -1,    -1,    18,    -1,    -1,    -1,    58,    59,    -1,
      -1,    26,    63,    28,    -1,    -1,    31,    -1,    -1,    13,
      -1,    -1,    -1,    -1,    18,    19,    -1,    -1,    -1,    44,
      -1,    -1,    26,    48,    28,    50,    51,    31,    -1,    -1,
      13,    -1,    -1,    58,    59,    18,    19,    -1,    -1,    -1,
      44,    -1,    -1,    26,    48,    28,    50,    51,    31,    -1,
      -1,    13,    -1,    -1,    58,    59,    18,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    26,    48,    28,    50,    51,    31,
      -1,    -1,    13,    -1,    -1,    58,    59,    18,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    26,    48,    28,    50,    51,
      31,    -1,    -1,    -1,    -1,    -1,    58,    59,    -1,    -1,
      -1,    -1,    -1,    44,    -1,    24,    25,    48,    -1,    50,
      51,    -1,    -1,    -1,    24,    25,    -1,    58,    59,    38,
      39,    40,    41,    42,    43,    -1,    45,    46,    47,    -1,
      49,    50,    51,    52,    53,    54,    24,    25,    57,    -1,
      50,    51,    52,    53,    54,    -1,    65,    57,    -1,    -1,
      38,    39,    40,    41,    42,    43,    -1,    45,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    24,    25,    57,
      -1,    -1,    -1,    -1,    -1,    24,    25,    65,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    -1,    45,    46,
      47,    -1,    49,    50,    51,    52,    53,    54,    24,    25,
      57,    50,    51,    52,    53,    54,    -1,    64,    57,    -1,
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
      -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    -1,    45,    46,
      47,    -1,    49,    50,    51,    52,    53,    54,    24,    25,
      57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    -1,    45,
      46,    47,    24,    25,    50,    51,    52,    53,    54,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      42,    43,    -1,    45,    46,    24,    25,    -1,    50,    51,
      52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    -1,    45,    46,    24,    25,
      -1,    50,    51,    52,    53,    54,    -1,    -1,    57,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    -1,    45,
      24,    25,    -1,    -1,    50,    51,    52,    53,    54,    -1,
      -1,    57,    -1,    -1,    38,    39,    40,    41,    42,    43,
      -1,    45,    24,    25,    -1,    -1,    50,    51,    52,    53,
      54,    -1,    -1,    57,    -1,    -1,    38,    39,    40,    41,
      42,    43,    24,    25,    -1,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    -1,    -1,    57,    38,    39,    40,    41,
      42,    43,    24,    25,    -1,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    -1,    -1,    57,    38,    39,    40,    41,
      -1,    -1,    24,    25,    -1,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    -1,    -1,    57,    38,    39,    40,    41,
       3,    -1,    -1,     6,     7,     8,    -1,    -1,    50,    51,
      52,    53,    54,    -1,    -1,    57,    19,    20,    21,    -1,
      23,     3,    -1,    26,     6,     7,     8,    -1,    -1,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    19,    -1,    21,
      -1,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      32,    33,    34
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  CfdgParser::yystos_[] =
  {
         0,     4,     5,    69,    70,    71,     0,     3,     6,     7,
       8,    19,    20,    21,    23,    26,    32,    33,    34,    73,
      74,    76,    78,    82,    83,    84,    93,    94,    99,   100,
       3,     6,     7,     8,    19,    21,    26,    32,    33,    34,
      72,    75,    77,    78,    81,    85,    86,    87,    88,    90,
      91,    92,    93,    95,    96,    97,    98,    26,    31,    26,
      26,    10,    10,    10,    26,    58,    29,    30,    79,    59,
      61,   132,    61,    61,    26,    31,    19,    26,    28,    26,
      10,    58,   104,   132,   132,    10,    19,    26,   104,    79,
      60,    80,   132,    13,    18,    26,    28,    31,    44,    48,
      50,    51,    58,    59,   133,   136,   143,   146,    61,   106,
      61,    61,    58,    59,    59,    28,    58,    58,   134,   134,
     120,   107,    58,   105,   133,   104,    58,   103,   104,    58,
     103,     6,    19,    26,    63,   101,   102,    10,   104,   104,
      10,    26,    79,    58,    58,    59,   143,   143,   143,   143,
      59,   134,    58,   137,    24,    25,    38,    39,    40,    41,
      42,    43,    45,    46,    47,    49,    50,    51,    52,    53,
      54,    57,     8,    11,    13,    15,    17,    19,    26,    28,
      31,    36,    62,    88,    89,   109,   114,   116,   119,   126,
     127,   128,   129,   130,   136,   147,   106,   106,    19,    20,
      65,   135,    62,    26,    28,    62,   122,   123,   124,   147,
       8,    11,    13,    15,    19,    26,    36,    62,   108,   117,
     118,   124,   147,    10,    28,    44,    48,    50,    51,    58,
      63,   133,   141,   144,   146,   133,    10,   102,    10,   102,
      19,    26,    19,    26,    49,    63,    10,    10,   143,    10,
      63,   141,   143,    63,   134,    65,    19,    26,    89,   138,
     139,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   147,
      19,    26,   143,    58,    58,   143,   143,    61,    53,    58,
      61,   143,    12,   133,    61,   110,   114,   110,   110,    61,
     137,   105,    62,    62,    13,    26,    28,    31,    48,    50,
      51,    58,   136,   140,   142,   145,    26,    30,    53,    61,
     121,   122,   132,    10,    10,    58,    58,    61,    36,    61,
     108,   111,   132,    63,   144,   144,   144,   143,    49,    63,
      24,    25,    38,    39,    40,    41,    42,    43,    45,    46,
      47,    50,    51,    52,    53,    54,    57,    63,    63,   101,
      63,    63,    63,    65,    65,    67,   105,    10,    10,   143,
     143,    63,   143,   115,   110,   106,    14,   112,   133,   133,
      58,    58,    59,   142,   142,   143,   137,   142,    24,    25,
      66,   125,   120,   134,   107,    63,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,    65,    26,   139,   143,   133,   143,
     143,    63,    63,    63,   110,    62,    14,    16,    62,   113,
     131,   143,    63,   141,   143,    63,   142,   142,   132,    62,
      62,    62,    63,   133,    64,   143,   110,    63,    63,    65,
      64
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
      73,    73,    73,    73,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    75,    75,    75,    75,    75,
      76,    77,    78,    79,    79,    80,    80,    81,    81,    81,
      82,    83,    84,    84,    84,    85,    86,    86,    86,    86,
      86,    86,    87,    87,    88,    88,    89,    90,    91,    92,
      93,    93,    94,    95,    95,    96,    97,    98,    99,   100,
     101,   101,   101,   101,   101,   101,   102,   102,   103,   103,
     104,   104,   105,   105,   105,   105,   106,   106,   107,   107,
     108,   108,   109,   109,   109,   109,   109,   109,   110,   110,
     111,   111,   112,   112,   113,   114,   114,   114,   115,   114,
     114,   114,   114,   114,   114,   116,   116,   116,   117,   117,
     117,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     119,   120,   120,   121,   121,   122,   123,   123,   125,   124,
     126,   126,   126,   127,   128,   129,   129,   130,   131,   131,
     132,   132,   133,   133,   134,   134,   135,   135,   135,   135,
     136,   137,   138,   138,   139,   140,   140,   141,   141,   142,
     142,   142,   142,   142,   142,   142,   142,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   145,   145,
     145,   145,   145,   145,   146,   146,   146,   146,   146,   146,
     146,   147,   147
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  CfdgParser::yyr2_[] =
  {
         0,     2,     2,     2,     2,     0,     2,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     3,     1,
       1,     3,     3,     3,     3,     2,     2,     2,     2,     1,
       2,     3,     1,     1,     1,     2,     0,     4,     3,     3,
       2,     2,     1,     1,     1,     2,     4,     3,     4,     4,
       3,     4,     1,     1,     2,     2,     2,     3,     2,     3,
       2,     3,     4,     1,     2,     3,     4,     4,     2,     4,
       2,     2,     2,     2,     1,     1,     3,     1,     3,     0,
       3,     2,     3,     3,     2,     0,     2,     0,     2,     0,
       4,     2,     4,     3,     3,     5,     3,     4,     3,     1,
       3,     1,     2,     0,     2,     1,     1,     1,     0,     4,
       2,     2,     2,     4,     1,     2,     2,     2,     1,     2,
       1,     2,     2,     1,     1,     2,     2,     1,     1,     1,
       3,     2,     0,     3,     1,     2,     1,     2,     0,     4,
       4,     4,     2,     4,     3,     2,     2,     4,     3,     2,
       3,     3,     3,     5,     2,     0,     2,     3,     2,     2,
       1,     5,     3,     1,     1,     2,     1,     3,     1,     1,
       1,     3,     1,     2,     2,     3,     3,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     3,     4,
       4,     4,     2,     1,     3,     4,     4,     4,     4,     2,
       1,     1,     1
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
  "initialization_v2", "directive_v2", "directive_string",
  "global_definition", "function_definition_header",
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
      -1,    85,    -1,    75,    -1,    82,    -1,    83,    -1,    76,
      -1,    78,    -1,    94,    -1,   100,    -1,    74,    -1,    26,
      10,    -1,    19,    10,    -1,    20,    10,    -1,    26,    58,
      -1,    26,    26,    58,    -1,    33,    -1,     6,    -1,     8,
      26,    58,    -1,     3,    26,    58,    -1,     3,    26,    59,
      -1,     3,    31,    59,    -1,    21,   132,    -1,    34,   132,
      -1,    19,   132,    -1,    32,    79,    -1,    93,    -1,    32,
      79,    -1,    33,    80,    79,    -1,    23,    -1,    29,    -1,
      30,    -1,    60,    26,    -1,    -1,     3,    26,   105,   133,
      -1,     3,    31,   133,    -1,     3,    26,   105,    -1,     3,
      26,    -1,    84,   132,    -1,    21,    -1,    34,    -1,    19,
      -1,    87,   143,    -1,     6,    26,   104,    10,    -1,    26,
     104,    10,    -1,    26,    26,   104,    10,    -1,     6,    19,
     104,    10,    -1,    19,   104,    10,    -1,    26,    19,   104,
      10,    -1,    86,    -1,    88,    -1,    26,    10,    -1,    19,
      10,    -1,    88,   143,    -1,     6,    26,   103,    -1,    90,
      61,    -1,    91,   106,    62,    -1,     7,    26,    -1,     7,
      26,    28,    -1,    93,    61,   120,    62,    -1,     7,    -1,
       7,    28,    -1,     8,    26,   103,    -1,    95,    61,   106,
      62,    -1,    96,    61,   106,    62,    -1,     8,    26,    -1,
      99,    61,   107,    62,    -1,    26,    26,    -1,     6,    26,
      -1,    26,    19,    -1,     6,    19,    -1,    26,    -1,    19,
      -1,   102,    49,   101,    -1,   101,    -1,    58,   102,    63,
      -1,    -1,    58,   102,    63,    -1,    58,    63,    -1,    58,
     141,    63,    -1,    58,    10,    63,    -1,    58,    63,    -1,
      -1,   106,   114,    -1,    -1,   107,   117,    -1,    -1,    36,
      61,   134,    62,    -1,   147,   132,    -1,    36,    58,   143,
      63,    -1,    36,    58,    63,    -1,   147,   105,   133,    -1,
      13,    58,   143,    63,   133,    -1,   136,   137,   133,    -1,
       8,   147,   105,   133,    -1,    61,   106,    62,    -1,   114,
      -1,    61,   107,    62,    -1,   108,    -1,   112,   113,    -1,
      -1,   131,   110,    -1,   109,    -1,    89,    -1,   119,    -1,
      -1,   119,    12,   115,   110,    -1,   127,   110,    -1,   128,
     110,    -1,   129,   110,    -1,   130,    61,   112,    62,    -1,
     116,    -1,    28,    53,    -1,    26,    61,    -1,    36,    61,
      -1,   108,    -1,   124,   111,    -1,   118,    -1,    36,    58,
      -1,    26,    58,    -1,     8,    -1,    11,    -1,    26,    10,
      -1,    19,    10,    -1,    13,    -1,    19,    -1,    15,    -1,
     126,   133,   110,    -1,   120,   123,    -1,    -1,    61,   120,
      62,    -1,   122,    -1,   147,   132,    -1,   122,    -1,   124,
     121,    -1,    -1,    28,    53,   125,   132,    -1,    11,    26,
      10,   143,    -1,    11,    19,    10,   143,    -1,    11,   143,
      -1,    13,    58,   143,    63,    -1,   127,   110,    14,    -1,
      19,   143,    -1,    17,   143,    -1,    15,    58,   143,    63,
      -1,    16,   143,    64,    -1,    14,    64,    -1,    61,   134,
      62,    -1,    59,   134,    65,    -1,    59,   134,    65,    -1,
      59,    59,   134,    65,    65,    -1,   134,   135,    -1,    -1,
      19,   140,    -1,    19,   142,    66,    -1,    20,    26,    -1,
      20,    30,    -1,    18,    -1,    58,   138,    67,   143,    63,
      -1,   138,    67,   139,    -1,   139,    -1,    89,    -1,   140,
     142,    -1,   142,    -1,   141,    49,   144,    -1,   144,    -1,
      28,    -1,    48,    -1,    58,   143,    63,    -1,   145,    -1,
      50,   142,    -1,    51,   142,    -1,   142,    24,   142,    -1,
     142,    25,   142,    -1,    28,    -1,    48,    -1,   146,    -1,
     143,    24,   143,    -1,   143,    25,   143,    -1,   143,    49,
     143,    -1,   143,    51,   143,    -1,   143,    50,   143,    -1,
     143,    52,   143,    -1,   143,    53,   143,    -1,   143,    54,
     143,    -1,    50,   143,    -1,    51,   143,    -1,    44,   143,
      -1,   143,    57,   143,    -1,   143,    39,   143,    -1,   143,
      38,   143,    -1,   143,    41,   143,    -1,   143,    40,   143,
      -1,   143,    42,   143,    -1,   143,    43,   143,    -1,   143,
      45,   143,    -1,   143,    46,   143,    -1,   143,    47,   143,
      -1,    58,   143,    63,    -1,   133,    -1,    28,    -1,    48,
      -1,   146,    -1,   144,    24,   144,    -1,   144,    25,   144,
      -1,   144,    51,   144,    -1,   144,    50,   144,    -1,   144,
      52,   144,    -1,   144,    53,   144,    -1,   144,    54,   144,
      -1,    50,   144,    -1,    51,   144,    -1,    44,   144,    -1,
     144,    57,   144,    -1,   144,    39,   144,    -1,   144,    38,
     144,    -1,   144,    41,   144,    -1,   144,    40,   144,    -1,
     144,    42,   144,    -1,   144,    43,   144,    -1,   144,    45,
     144,    -1,   144,    46,   144,    -1,   144,    47,   144,    -1,
      58,   143,    63,    -1,   133,    -1,    26,    58,    63,    -1,
      26,    58,   141,    63,    -1,    31,    59,   143,    65,    -1,
      13,    58,   143,    63,    -1,   136,   137,    -1,    26,    -1,
      26,    58,    63,    -1,    26,    58,   141,    63,    -1,    31,
      59,   143,    65,    -1,    13,    58,   143,    63,    -1,    26,
      58,    10,    63,    -1,   136,   137,    -1,    26,    -1,    26,
      -1,    31,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  CfdgParser::yyprhs_[] =
  {
         0,     0,     3,     6,     9,    12,    13,    16,    17,    19,
      21,    23,    25,    27,    29,    31,    33,    35,    37,    39,
      41,    43,    45,    47,    49,    52,    55,    58,    61,    65,
      67,    69,    73,    77,    81,    85,    88,    91,    94,    97,
      99,   102,   106,   108,   110,   112,   115,   116,   121,   125,
     129,   132,   135,   137,   139,   141,   144,   149,   153,   158,
     163,   167,   172,   174,   176,   179,   182,   185,   189,   192,
     196,   199,   203,   208,   210,   213,   217,   222,   227,   230,
     235,   238,   241,   244,   247,   249,   251,   255,   257,   261,
     262,   266,   269,   273,   277,   280,   281,   284,   285,   288,
     289,   294,   297,   302,   306,   310,   316,   320,   325,   329,
     331,   335,   337,   340,   341,   344,   346,   348,   350,   351,
     356,   359,   362,   365,   370,   372,   375,   378,   381,   383,
     386,   388,   391,   394,   396,   398,   401,   404,   406,   408,
     410,   414,   417,   418,   422,   424,   427,   429,   432,   433,
     438,   443,   448,   451,   456,   460,   463,   466,   471,   475,
     478,   482,   486,   490,   496,   499,   500,   503,   507,   510,
     513,   515,   521,   525,   527,   529,   532,   534,   538,   540,
     542,   544,   548,   550,   553,   556,   560,   564,   566,   568,
     570,   574,   578,   582,   586,   590,   594,   598,   602,   605,
     608,   611,   615,   619,   623,   627,   631,   635,   639,   643,
     647,   651,   655,   657,   659,   661,   663,   667,   671,   675,
     679,   683,   687,   691,   694,   697,   700,   704,   708,   712,
     716,   720,   724,   728,   732,   736,   740,   744,   746,   750,
     755,   760,   765,   768,   770,   774,   779,   784,   789,   794,
     797,   799,   801
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  CfdgParser::yyrline_[] =
  {
         0,   192,   192,   192,   195,   200,   204,   209,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   228,   229,   230,
     231,   232,   233,   234,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   260,   261,   262,   263,   264,
     268,   277,   288,   295,   295,   298,   299,   303,   314,   324,
     336,   347,   358,   360,   362,   379,   404,   414,   424,   433,
     438,   443,   451,   456,   462,   465,   472,   490,   497,   506,
     514,   523,   538,   546,   554,   567,   580,   588,   597,   610,
     617,   623,   629,   634,   638,   644,   650,   651,   655,   656,
     660,   661,   665,   666,   667,   668,   672,   675,   679,   682,
     686,   693,   703,   709,   715,   724,   734,   745,   755,   757,
     763,   765,   771,   774,   778,   782,   786,   790,   799,   799,
     811,   820,   829,   838,   845,   852,   853,   854,   858,   860,
     868,   880,   881,   882,   883,   884,   885,   886,   887,   888,
     892,   901,   904,   908,   910,   916,   925,   927,   938,   938,
     953,   962,   972,   983,   992,  1000,  1008,  1018,  1027,  1055,
    1066,  1071,  1078,  1083,  1090,  1095,  1104,  1109,  1119,  1124,
    1131,  1139,  1145,  1147,  1151,  1157,  1161,  1168,  1172,  1178,
    1180,  1182,  1184,  1186,  1188,  1190,  1195,  1202,  1204,  1206,
    1208,  1213,  1218,  1220,  1222,  1224,  1226,  1228,  1230,  1232,
    1234,  1236,  1238,  1240,  1242,  1244,  1246,  1248,  1250,  1252,
    1254,  1256,  1258,  1262,  1264,  1266,  1268,  1273,  1278,  1280,
    1282,  1284,  1286,  1288,  1290,  1292,  1294,  1296,  1298,  1300,
    1302,  1304,  1306,  1308,  1310,  1312,  1314,  1316,  1320,  1325,
    1331,  1337,  1343,  1350,  1357,  1362,  1368,  1374,  1380,  1386,
    1393,  1400,  1402
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
  const int CfdgParser::yylast_ = 1312;
  const int CfdgParser::yynnts_ = 80;
  const int CfdgParser::yyempty_ = -2;
  const int CfdgParser::yyfinal_ = 6;
  const int CfdgParser::yyterror_ = 1;
  const int CfdgParser::yyerrcode_ = 256;
  const int CfdgParser::yyntokens_ = 68;

  const unsigned int CfdgParser::yyuser_token_number_max_ = 305;
  const CfdgParser::token_number_type CfdgParser::yyundef_token_ = 2;


} // yy
/* Line 1141 of lalr1.cc  */
#line 3794 "cfdg.tab.cpp"
/* Line 1142 of lalr1.cc  */
#line 1405 "../../src-common/cfdg.ypp"


void yy::CfdgParser::error(const CfdgParser::location_type& l, const std::string& m)
{
    driver.error(l, m);
}
