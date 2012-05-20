/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2010 Free Software Foundation, Inc.
   
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

/* Line 310 of lalr1.cc  */
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


/* Line 310 of lalr1.cc  */
#line 62 "cfdg.tab.cpp"


#include "cfdg.tab.hpp"

/* User implementation prologue.  */

/* Line 316 of lalr1.cc  */
#line 80 "../../src-common/cfdg.ypp"

#include "astreplacement.h"
#include "astexpression.h"
    
    using namespace AST;

/* Line 316 of lalr1.cc  */
#line 176 "../../src-common/cfdg.ypp"

#include "scanner.h"
#include "math.h"
#include "builder.h"
#include <cassert>
	
#undef yylex
#define yylex driver.lexer->lex


/* Line 316 of lalr1.cc  */
#line 90 "cfdg.tab.cpp"

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

/* Line 379 of lalr1.cc  */
#line 156 "cfdg.tab.cpp"
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  CfdgParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

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
        case 26: /* "USER_STRING" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 263 "cfdg.tab.cpp"
	break;
      case 29: /* "USER_FILENAME" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 272 "cfdg.tab.cpp"
	break;
      case 30: /* "USER_QSTRING" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 281 "cfdg.tab.cpp"
	break;
      case 31: /* "USER_ARRAYNAME" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 290 "cfdg.tab.cpp"
	break;
      case 36: /* "USER_PATHOP" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 299 "cfdg.tab.cpp"
	break;
      case 72: /* "statement" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 308 "cfdg.tab.cpp"
	break;
      case 73: /* "statement_v2" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 317 "cfdg.tab.cpp"
	break;
      case 79: /* "fileString" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 326 "cfdg.tab.cpp"
	break;
      case 80: /* "fileNameSpace" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 335 "cfdg.tab.cpp"
	break;
      case 81: /* "initialization" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 344 "cfdg.tab.cpp"
	break;
      case 82: /* "initialization_v2" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 353 "cfdg.tab.cpp"
	break;
      case 83: /* "background" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 362 "cfdg.tab.cpp"
	break;
      case 84: /* "tile" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 371 "cfdg.tab.cpp"
	break;
      case 85: /* "size" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 380 "cfdg.tab.cpp"
	break;
      case 87: /* "global_definition_header" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 389 "cfdg.tab.cpp"
	break;
      case 88: /* "definition_header" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 398 "cfdg.tab.cpp"
	break;
      case 90: /* "shape" */

/* Line 479 of lalr1.cc  */
#line 173 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->shapeObj); };

/* Line 479 of lalr1.cc  */
#line 407 "cfdg.tab.cpp"
	break;
      case 91: /* "shape_singleton_header" */

/* Line 479 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 416 "cfdg.tab.cpp"
	break;
      case 92: /* "shape_singleton" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 425 "cfdg.tab.cpp"
	break;
      case 93: /* "rule_header_v2" */

/* Line 479 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 434 "cfdg.tab.cpp"
	break;
      case 95: /* "rule_header" */

/* Line 479 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 443 "cfdg.tab.cpp"
	break;
      case 96: /* "path_header" */

/* Line 479 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 452 "cfdg.tab.cpp"
	break;
      case 97: /* "rule" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 461 "cfdg.tab.cpp"
	break;
      case 98: /* "path" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 470 "cfdg.tab.cpp"
	break;
      case 99: /* "path_header_v2" */

/* Line 479 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 479 "cfdg.tab.cpp"
	break;
      case 106: /* "parameter_spec" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 488 "cfdg.tab.cpp"
	break;
      case 109: /* "pathOp_simple_v2" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 497 "cfdg.tab.cpp"
	break;
      case 110: /* "element_simple" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 506 "cfdg.tab.cpp"
	break;
      case 115: /* "element" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 515 "cfdg.tab.cpp"
	break;
      case 118: /* "pathOp_v2" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 524 "cfdg.tab.cpp"
	break;
      case 120: /* "element_loop" */

/* Line 479 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 533 "cfdg.tab.cpp"
	break;
      case 123: /* "replacement_simple_v2" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 542 "cfdg.tab.cpp"
	break;
      case 124: /* "replacement_v2" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 551 "cfdg.tab.cpp"
	break;
      case 125: /* "loopHeader_v2" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 560 "cfdg.tab.cpp"
	break;
      case 127: /* "loopHeader" */

/* Line 479 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 569 "cfdg.tab.cpp"
	break;
      case 128: /* "ifHeader" */

/* Line 479 of lalr1.cc  */
#line 171 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ifObj); };

/* Line 479 of lalr1.cc  */
#line 578 "cfdg.tab.cpp"
	break;
      case 129: /* "ifElseHeader" */

/* Line 479 of lalr1.cc  */
#line 171 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ifObj); };

/* Line 479 of lalr1.cc  */
#line 587 "cfdg.tab.cpp"
	break;
      case 130: /* "transHeader" */

/* Line 479 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 596 "cfdg.tab.cpp"
	break;
      case 131: /* "switchHeader" */

/* Line 479 of lalr1.cc  */
#line 172 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->switchObj); };

/* Line 479 of lalr1.cc  */
#line 605 "cfdg.tab.cpp"
	break;
      case 132: /* "caseHeader" */

/* Line 479 of lalr1.cc  */
#line 174 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); };

/* Line 479 of lalr1.cc  */
#line 614 "cfdg.tab.cpp"
	break;
      case 133: /* "modification_v2" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 623 "cfdg.tab.cpp"
	break;
      case 134: /* "modification" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 632 "cfdg.tab.cpp"
	break;
      case 135: /* "buncha_adjustments" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 641 "cfdg.tab.cpp"
	break;
      case 136: /* "adjustment" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->term); };

/* Line 479 of lalr1.cc  */
#line 650 "cfdg.tab.cpp"
	break;
      case 137: /* "letHeader" */

/* Line 479 of lalr1.cc  */
#line 175 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->bodyObj); };

/* Line 479 of lalr1.cc  */
#line 659 "cfdg.tab.cpp"
	break;
      case 138: /* "letBody" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 668 "cfdg.tab.cpp"
	break;
      case 141: /* "explist" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 677 "cfdg.tab.cpp"
	break;
      case 142: /* "exp" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 686 "cfdg.tab.cpp"
	break;
      case 143: /* "exp2" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 695 "cfdg.tab.cpp"
	break;
      case 144: /* "expfunc" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 704 "cfdg.tab.cpp"
	break;
      case 145: /* "exp2func" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 713 "cfdg.tab.cpp"
	break;
      case 146: /* "shapeName" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 722 "cfdg.tab.cpp"
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
    location_type yyerror_range[2];

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
    if (yyn == yypact_ninf_)
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
	if (yyn == 0 || yyn == yytable_ninf_)
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

/* Line 677 of lalr1.cc  */
#line 192 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 6:

/* Line 677 of lalr1.cc  */
#line 201 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 9:

/* Line 677 of lalr1.cc  */
#line 211 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 10:

/* Line 677 of lalr1.cc  */
#line 212 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 13:

/* Line 677 of lalr1.cc  */
#line 215 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].shapeObj); }
    break;

  case 15:

/* Line 677 of lalr1.cc  */
#line 217 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 16:

/* Line 677 of lalr1.cc  */
#line 218 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 19:

/* Line 677 of lalr1.cc  */
#line 227 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 20:

/* Line 677 of lalr1.cc  */
#line 228 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 25:

/* Line 677 of lalr1.cc  */
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

/* Line 677 of lalr1.cc  */
#line 245 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 27:

/* Line 677 of lalr1.cc  */
#line 246 "../../src-common/cfdg.ypp"
    {}
    break;

  case 28:

/* Line 677 of lalr1.cc  */
#line 247 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 29:

/* Line 677 of lalr1.cc  */
#line 248 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (1)].string); delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 32:

/* Line 677 of lalr1.cc  */
#line 251 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 33:

/* Line 677 of lalr1.cc  */
#line 252 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 34:

/* Line 677 of lalr1.cc  */
#line 253 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 35:

/* Line 677 of lalr1.cc  */
#line 254 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 36:

/* Line 677 of lalr1.cc  */
#line 258 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 37:

/* Line 677 of lalr1.cc  */
#line 259 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 38:

/* Line 677 of lalr1.cc  */
#line 260 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 39:

/* Line 677 of lalr1.cc  */
#line 261 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 40:

/* Line 677 of lalr1.cc  */
#line 262 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(1) - (1)].ruleObj); }
    break;

  case 41:

/* Line 677 of lalr1.cc  */
#line 266 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(2) - (2)].string));
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(NULL);
            driver.IncludeFile(*file);
        }
    break;

  case 42:

/* Line 677 of lalr1.cc  */
#line 275 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(3) - (3)].string));
            str_ptr nm((yysemantic_stack_[(3) - (2)].string));
            driver.SetShape(NULL);
            driver.IncludeFile(*file);
            if (nm.get())
                driver.PushNameSpace(nm, (yylocation_stack_[(3) - (2)]));
        }
    break;

  case 43:

/* Line 677 of lalr1.cc  */
#line 286 "../../src-common/cfdg.ypp"
    {
            if (driver.EndInclude())
                YYACCEPT;
        }
    break;

  case 46:

/* Line 677 of lalr1.cc  */
#line 296 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 47:

/* Line 677 of lalr1.cc  */
#line 297 "../../src-common/cfdg.ypp"
    { (yyval.string) = NULL; }
    break;

  case 48:

/* Line 677 of lalr1.cc  */
#line 301 "../../src-common/cfdg.ypp"
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

  case 49:

/* Line 677 of lalr1.cc  */
#line 314 "../../src-common/cfdg.ypp"
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

  case 50:

/* Line 677 of lalr1.cc  */
#line 326 "../../src-common/cfdg.ypp"
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

  case 51:

/* Line 677 of lalr1.cc  */
#line 340 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (2)].string));
            driver.SetShape(NULL);
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), (yylocation_stack_[(2) - (2)])));
            rep_ptr start(new ASTreplacement(*r, *name, mod_ptr(), (yyloc)));
            driver.Initialize(start);
            (yyval.component) = 0;
        }
    break;

  case 52:

/* Line 677 of lalr1.cc  */
#line 351 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            static const std::string backVar("CF::Background");
            driver.lexer->maybeVersion = token::CFDG2;
            driver.NextParameter(backVar, mod, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
            (yyval.component) = 0;
        }
    break;

  case 53:

/* Line 677 of lalr1.cc  */
#line 361 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            static const std::string tileVar("CF::Tile");
            driver.lexer->maybeVersion = token::CFDG2;
            driver.NextParameter(tileVar, mod, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
            (yyval.component) = 0;
        }
    break;

  case 54:

/* Line 677 of lalr1.cc  */
#line 371 "../../src-common/cfdg.ypp"
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

  case 55:

/* Line 677 of lalr1.cc  */
#line 386 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(2) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            if (var.get())
                driver.NextParameter(*var, exp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 56:

/* Line 677 of lalr1.cc  */
#line 395 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("shape");
            driver.push_paramDecls(*(yysemantic_stack_[(4) - (2)].string), (yyloc), numtype);
            (yyval.string) = (yysemantic_stack_[(4) - (2)].string);
        }
    break;

  case 57:

/* Line 677 of lalr1.cc  */
#line 401 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("number");
            driver.push_paramDecls(*(yysemantic_stack_[(3) - (1)].string), (yyloc), numtype);
            (yyval.string) = (yysemantic_stack_[(3) - (1)].string);
        }
    break;

  case 58:

/* Line 677 of lalr1.cc  */
#line 407 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            error((yylocation_stack_[(3) - (1)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 59:

/* Line 677 of lalr1.cc  */
#line 413 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(4) - (1)].string));
            driver.push_paramDecls(*(yysemantic_stack_[(4) - (2)].string), (yyloc), *type);
            (yyval.string) = (yysemantic_stack_[(4) - (2)].string);
        }
    break;

  case 60:

/* Line 677 of lalr1.cc  */
#line 419 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(4) - (1)].string));
            driver.isFunction = false;
            error((yylocation_stack_[(4) - (2)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 61:

/* Line 677 of lalr1.cc  */
#line 428 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            (yyval.string) = (yysemantic_stack_[(2) - (1)].string);
        }
    break;

  case 62:

/* Line 677 of lalr1.cc  */
#line 432 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            error((yylocation_stack_[(2) - (1)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 63:

/* Line 677 of lalr1.cc  */
#line 440 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(2) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            if (var.get() && driver.mCompilePhase == 2)
                driver.NextParameter(*var, exp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 64:

/* Line 677 of lalr1.cc  */
#line 449 "../../src-common/cfdg.ypp"
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

  case 65:

/* Line 677 of lalr1.cc  */
#line 465 "../../src-common/cfdg.ypp"
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

  case 66:

/* Line 677 of lalr1.cc  */
#line 479 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(3) - (1)].ruleObj);
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 67:

/* Line 677 of lalr1.cc  */
#line 488 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (2)].string));
            driver.SetShape(NULL);
            rule_ptr rule(new ASTrule(driver.StringToShape(*name, (yylocation_stack_[(2) - (2)]), false), (yyloc)));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
        }
    break;

  case 68:

/* Line 677 of lalr1.cc  */
#line 497 "../../src-common/cfdg.ypp"
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

  case 69:

/* Line 677 of lalr1.cc  */
#line 512 "../../src-common/cfdg.ypp"
    {
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 70:

/* Line 677 of lalr1.cc  */
#line 520 "../../src-common/cfdg.ypp"
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

  case 71:

/* Line 677 of lalr1.cc  */
#line 532 "../../src-common/cfdg.ypp"
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

  case 72:

/* Line 677 of lalr1.cc  */
#line 549 "../../src-common/cfdg.ypp"
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

  case 73:

/* Line 677 of lalr1.cc  */
#line 574 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 74:

/* Line 677 of lalr1.cc  */
#line 583 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
            driver.SetShape(NULL);
        }
    break;

  case 75:

/* Line 677 of lalr1.cc  */
#line 593 "../../src-common/cfdg.ypp"
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

  case 76:

/* Line 677 of lalr1.cc  */
#line 606 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 77:

/* Line 677 of lalr1.cc  */
#line 613 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(2) - (1)].string));
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(*type, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
		}
    break;

  case 78:

/* Line 677 of lalr1.cc  */
#line 619 "../../src-common/cfdg.ypp"
    {
            static std::string shapeStr("shape");
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(shapeStr, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 79:

/* Line 677 of lalr1.cc  */
#line 625 "../../src-common/cfdg.ypp"
    {
            delete (yysemantic_stack_[(2) - (1)].string);
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 80:

/* Line 677 of lalr1.cc  */
#line 630 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 81:

/* Line 677 of lalr1.cc  */
#line 634 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("number");
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            driver.NextParameterDecl(numtype, *var, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 82:

/* Line 677 of lalr1.cc  */
#line 640 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Reserved keyword: adjustment");
        }
    break;

  case 87:

/* Line 677 of lalr1.cc  */
#line 656 "../../src-common/cfdg.ypp"
    { driver.isFunction = true; }
    break;

  case 88:

/* Line 677 of lalr1.cc  */
#line 657 "../../src-common/cfdg.ypp"
    { driver.isFunction = true; }
    break;

  case 89:

/* Line 677 of lalr1.cc  */
#line 658 "../../src-common/cfdg.ypp"
    { driver.isFunction = false; }
    break;

  case 90:

/* Line 677 of lalr1.cc  */
#line 662 "../../src-common/cfdg.ypp"
    { driver.isFunction = true; }
    break;

  case 91:

/* Line 677 of lalr1.cc  */
#line 663 "../../src-common/cfdg.ypp"
    { driver.isFunction = true; }
    break;

  case 92:

/* Line 677 of lalr1.cc  */
#line 667 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(3) - (2)].expression);}
    break;

  case 93:

/* Line 677 of lalr1.cc  */
#line 668 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTexpression((yyloc)); }
    break;

  case 94:

/* Line 677 of lalr1.cc  */
#line 669 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 95:

/* Line 677 of lalr1.cc  */
#line 670 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 96:

/* Line 677 of lalr1.cc  */
#line 674 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 1)
                assert ((yysemantic_stack_[(2) - (2)].component) == 0);
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 98:

/* Line 677 of lalr1.cc  */
#line 683 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 100:

/* Line 677 of lalr1.cc  */
#line 690 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(4) - (3)].mod));
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = new ASTpathOp(*pop, mod, (yyloc));
        }
    break;

  case 101:

/* Line 677 of lalr1.cc  */
#line 697 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(2) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            driver.lexer->maybeVersion = token::CFDG2;
            rep_ptr item(new ASTpathCommand(*cmd, mod, (yyloc)));
            (yyval.component) = item.release();
        }
    break;

  case 102:

/* Line 677 of lalr1.cc  */
#line 707 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string));
            exp_ptr mod((yysemantic_stack_[(4) - (3)].expression));
            if (driver.mCompilePhase == 2)
                (yyval.component) = new ASTpathOp(*pop, mod, (yyloc));
            else
                (yyval.component) = 0;
        }
    break;

  case 103:

/* Line 677 of lalr1.cc  */
#line 716 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(3) - (1)].string));
            exp_ptr mod;
            if (driver.mCompilePhase == 2)
                (yyval.component) = new ASTpathOp(*pop, mod, (yyloc));
            else
                (yyval.component) = 0;
        }
    break;

  case 104:

/* Line 677 of lalr1.cc  */
#line 725 "../../src-common/cfdg.ypp"
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

  case 105:

/* Line 677 of lalr1.cc  */
#line 737 "../../src-common/cfdg.ypp"
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

  case 106:

/* Line 677 of lalr1.cc  */
#line 751 "../../src-common/cfdg.ypp"
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

  case 107:

/* Line 677 of lalr1.cc  */
#line 765 "../../src-common/cfdg.ypp"
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

  case 108:

/* Line 677 of lalr1.cc  */
#line 779 "../../src-common/cfdg.ypp"
    { }
    break;

  case 109:

/* Line 677 of lalr1.cc  */
#line 781 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 1)
                assert((yysemantic_stack_[(1) - (1)].component) == 0);
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 110:

/* Line 677 of lalr1.cc  */
#line 789 "../../src-common/cfdg.ypp"
    { }
    break;

  case 111:

/* Line 677 of lalr1.cc  */
#line 791 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 112:

/* Line 677 of lalr1.cc  */
#line 797 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer(driver.switchStack.top());
        }
    break;

  case 115:

/* Line 677 of lalr1.cc  */
#line 809 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(1) - (1)].component); 
        }
    break;

  case 116:

/* Line 677 of lalr1.cc  */
#line 813 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = 0; 
        }
    break;

  case 117:

/* Line 677 of lalr1.cc  */
#line 817 "../../src-common/cfdg.ypp"
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

  case 118:

/* Line 677 of lalr1.cc  */
#line 828 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
                driver.push_repContainer((yysemantic_stack_[(2) - (1)].loopObj)->mFinallyBody);
            }
        }
    break;

  case 119:

/* Line 677 of lalr1.cc  */
#line 833 "../../src-common/cfdg.ypp"
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

  case 120:

/* Line 677 of lalr1.cc  */
#line 846 "../../src-common/cfdg.ypp"
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

  case 121:

/* Line 677 of lalr1.cc  */
#line 857 "../../src-common/cfdg.ypp"
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

/* Line 677 of lalr1.cc  */
#line 868 "../../src-common/cfdg.ypp"
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

  case 123:

/* Line 677 of lalr1.cc  */
#line 880 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].switchObj);
            if (driver.mCompilePhase == 2) {
                (yysemantic_stack_[(4) - (1)].switchObj)->unify();
                driver.switchStack.pop();
            }
        }
    break;

  case 124:

/* Line 677 of lalr1.cc  */
#line 888 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 125:

/* Line 677 of lalr1.cc  */
#line 895 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 126:

/* Line 677 of lalr1.cc  */
#line 896 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 127:

/* Line 677 of lalr1.cc  */
#line 897 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 128:

/* Line 677 of lalr1.cc  */
#line 901 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 129:

/* Line 677 of lalr1.cc  */
#line 903 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(2) - (1)].loopObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            if ((yysemantic_stack_[(2) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].loopObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 130:

/* Line 677 of lalr1.cc  */
#line 911 "../../src-common/cfdg.ypp"
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

  case 131:

/* Line 677 of lalr1.cc  */
#line 923 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 132:

/* Line 677 of lalr1.cc  */
#line 924 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 135:

/* Line 677 of lalr1.cc  */
#line 927 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 140:

/* Line 677 of lalr1.cc  */
#line 935 "../../src-common/cfdg.ypp"
    {
            // parse loop mod and loop body with loop index in scope
            mod_ptr loopmod((yysemantic_stack_[(3) - (2)].mod));
            if (driver.mCompilePhase == 2)
                (yysemantic_stack_[(3) - (1)].loopObj)->mChildChange.grab(loopmod.get());
            (yyval.loopObj) = (yysemantic_stack_[(3) - (1)].loopObj);
            // loopmod gets deleted
        }
    break;

  case 141:

/* Line 677 of lalr1.cc  */
#line 946 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 143:

/* Line 677 of lalr1.cc  */
#line 953 "../../src-common/cfdg.ypp"
    { }
    break;

  case 144:

/* Line 677 of lalr1.cc  */
#line 955 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 145:

/* Line 677 of lalr1.cc  */
#line 961 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), (yylocation_stack_[(2) - (1)])));
            (yyval.component) = new ASTreplacement(*r, r->entropyVal, mod, (yyloc));
        }
    break;

  case 146:

/* Line 677 of lalr1.cc  */
#line 970 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 147:

/* Line 677 of lalr1.cc  */
#line 972 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].loopObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            if ((yysemantic_stack_[(2) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].loopObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 148:

/* Line 677 of lalr1.cc  */
#line 983 "../../src-common/cfdg.ypp"
    { ++driver.mLocalStackDepth; }
    break;

  case 149:

/* Line 677 of lalr1.cc  */
#line 983 "../../src-common/cfdg.ypp"
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

  case 150:

/* Line 677 of lalr1.cc  */
#line 998 "../../src-common/cfdg.ypp"
    {
            str_ptr var((yysemantic_stack_[(4) - (2)].string));
            exp_ptr index((yysemantic_stack_[(4) - (4)].expression));
            if (driver.mCompilePhase == 2) {
                int nameIndex = driver.StringToShape(*var, (yylocation_stack_[(4) - (2)]), false);
                driver.CheckVariableName(nameIndex, (yylocation_stack_[(4) - (2)]));
                loop_ptr loop(new ASTloop(nameIndex, *var, (yylocation_stack_[(4) - (2)]), index, (yylocation_stack_[(4) - (4)]), mod_ptr()));
                driver.push_repContainer(loop->mLoopBody);
                (yyval.loopObj) = loop.release();
            } else {
                (yyval.loopObj) = 0;
            }
        }
    break;

  case 151:

/* Line 677 of lalr1.cc  */
#line 1012 "../../src-common/cfdg.ypp"
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

  case 152:

/* Line 677 of lalr1.cc  */
#line 1026 "../../src-common/cfdg.ypp"
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

  case 153:

/* Line 677 of lalr1.cc  */
#line 1041 "../../src-common/cfdg.ypp"
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

  case 154:

/* Line 677 of lalr1.cc  */
#line 1054 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ifObj));
                driver.push_repContainer((yysemantic_stack_[(3) - (1)].ifObj)->mElseBody);
            }
            (yyval.ifObj) = (yysemantic_stack_[(3) - (1)].ifObj);
        }
    break;

  case 155:

/* Line 677 of lalr1.cc  */
#line 1064 "../../src-common/cfdg.ypp"
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

  case 156:

/* Line 677 of lalr1.cc  */
#line 1076 "../../src-common/cfdg.ypp"
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

  case 157:

/* Line 677 of lalr1.cc  */
#line 1092 "../../src-common/cfdg.ypp"
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

  case 158:

/* Line 677 of lalr1.cc  */
#line 1105 "../../src-common/cfdg.ypp"
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

  case 159:

/* Line 677 of lalr1.cc  */
#line 1134 "../../src-common/cfdg.ypp"
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

  case 160:

/* Line 677 of lalr1.cc  */
#line 1147 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), true);
        }
    break;

  case 161:

/* Line 677 of lalr1.cc  */
#line 1152 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), false);
        }
    break;

  case 162:

/* Line 677 of lalr1.cc  */
#line 1159 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), true);
        }
    break;

  case 163:

/* Line 677 of lalr1.cc  */
#line 1164 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(5) - (3)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), false);
        }
    break;

  case 164:

/* Line 677 of lalr1.cc  */
#line 1171 "../../src-common/cfdg.ypp"
    {
            term_ptr mod((yysemantic_stack_[(2) - (2)].term));
            driver.MakeModTerm((yysemantic_stack_[(2) - (1)].mod)->modExp, mod);
            (yyval.mod) = (yysemantic_stack_[(2) - (1)].mod);
        }
    break;

  case 165:

/* Line 677 of lalr1.cc  */
#line 1176 "../../src-common/cfdg.ypp"
    {
            static const yy::location def;
            ASTmodification* m = new ASTmodification(def);
            m->flags = 0;
            (yyval.mod) = m;
        }
    break;

  case 166:

/* Line 677 of lalr1.cc  */
#line 1185 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].expression));
            (yyval.term) = new ASTmodTerm((ASTmodTerm::modTypeEnum)((yysemantic_stack_[(2) - (1)].modToken)), mod.release(), (yyloc));
        }
    break;

  case 167:

/* Line 677 of lalr1.cc  */
#line 1190 "../../src-common/cfdg.ypp"
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

  case 168:

/* Line 677 of lalr1.cc  */
#line 1200 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.term) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 169:

/* Line 677 of lalr1.cc  */
#line 1205 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.term) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 170:

/* Line 677 of lalr1.cc  */
#line 1212 "../../src-common/cfdg.ypp"
    {
            ASTrepContainer* tempHolder = new ASTrepContainer();
            driver.push_repContainer(*tempHolder);
            driver.isFunction = false;
            (yyval.bodyObj) = tempHolder;
        }
    break;

  case 171:

/* Line 677 of lalr1.cc  */
#line 1221 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = (yysemantic_stack_[(5) - (4)].expression);
        }
    break;

  case 174:

/* Line 677 of lalr1.cc  */
#line 1233 "../../src-common/cfdg.ypp"
    {
            str_ptr var((yysemantic_stack_[(3) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(3) - (3)].expression));
            driver.NextParameter(*var, exp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]));
        }
    break;

  case 175:

/* Line 677 of lalr1.cc  */
#line 1239 "../../src-common/cfdg.ypp"
    {
            exp_ptr exp((yysemantic_stack_[(3) - (3)].expression));
            error((yylocation_stack_[(3) - (1)]), "Reserved keyword: adjustment");
        }
    break;

  case 176:

/* Line 677 of lalr1.cc  */
#line 1246 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTexpression::Append((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 177:

/* Line 677 of lalr1.cc  */
#line 1250 "../../src-common/cfdg.ypp"
    { 
            (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); 
        }
    break;

  case 178:

/* Line 677 of lalr1.cc  */
#line 1256 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 179:

/* Line 677 of lalr1.cc  */
#line 1258 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 180:

/* Line 677 of lalr1.cc  */
#line 1260 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 181:

/* Line 677 of lalr1.cc  */
#line 1262 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 182:

/* Line 677 of lalr1.cc  */
#line 1264 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 183:

/* Line 677 of lalr1.cc  */
#line 1266 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 184:

/* Line 677 of lalr1.cc  */
#line 1268 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 185:

/* Line 677 of lalr1.cc  */
#line 1273 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 186:

/* Line 677 of lalr1.cc  */
#line 1280 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 187:

/* Line 677 of lalr1.cc  */
#line 1282 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 188:

/* Line 677 of lalr1.cc  */
#line 1284 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 189:

/* Line 677 of lalr1.cc  */
#line 1286 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 190:

/* Line 677 of lalr1.cc  */
#line 1291 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 191:

/* Line 677 of lalr1.cc  */
#line 1296 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression));   }
    break;

  case 192:

/* Line 677 of lalr1.cc  */
#line 1298 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('+', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 193:

/* Line 677 of lalr1.cc  */
#line 1300 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('-', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 194:

/* Line 677 of lalr1.cc  */
#line 1302 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('_', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 195:

/* Line 677 of lalr1.cc  */
#line 1304 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('*', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 196:

/* Line 677 of lalr1.cc  */
#line 1306 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('/', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 197:

/* Line 677 of lalr1.cc  */
#line 1308 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 198:

/* Line 677 of lalr1.cc  */
#line 1310 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 199:

/* Line 677 of lalr1.cc  */
#line 1312 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('!', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 200:

/* Line 677 of lalr1.cc  */
#line 1314 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('^', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 201:

/* Line 677 of lalr1.cc  */
#line 1316 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('<', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 202:

/* Line 677 of lalr1.cc  */
#line 1318 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('L', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 203:

/* Line 677 of lalr1.cc  */
#line 1320 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('>', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 204:

/* Line 677 of lalr1.cc  */
#line 1322 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('G', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 205:

/* Line 677 of lalr1.cc  */
#line 1324 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('=', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 206:

/* Line 677 of lalr1.cc  */
#line 1326 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('n', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 207:

/* Line 677 of lalr1.cc  */
#line 1328 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('&', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 208:

/* Line 677 of lalr1.cc  */
#line 1330 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('|', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 209:

/* Line 677 of lalr1.cc  */
#line 1332 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('X', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 210:

/* Line 677 of lalr1.cc  */
#line 1334 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 211:

/* Line 677 of lalr1.cc  */
#line 1336 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].mod); }
    break;

  case 212:

/* Line 677 of lalr1.cc  */
#line 1340 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 213:

/* Line 677 of lalr1.cc  */
#line 1345 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), true);
        }
    break;

  case 214:

/* Line 677 of lalr1.cc  */
#line 1351 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeArray(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]));
        }
    break;

  case 215:

/* Line 677 of lalr1.cc  */
#line 1357 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 216:

/* Line 677 of lalr1.cc  */
#line 1363 "../../src-common/cfdg.ypp"
    {
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            std::auto_ptr<ASTrepContainer> vars((yysemantic_stack_[(2) - (1)].bodyObj));
            (yyval.expression) = driver.MakeLet((yylocation_stack_[(2) - (1)]), exp);
        }
    break;

  case 217:

/* Line 677 of lalr1.cc  */
#line 1369 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 218:

/* Line 677 of lalr1.cc  */
#line 1376 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 219:

/* Line 677 of lalr1.cc  */
#line 1381 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 220:

/* Line 677 of lalr1.cc  */
#line 1387 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeArray(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]));
        }
    break;

  case 221:

/* Line 677 of lalr1.cc  */
#line 1393 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 222:

/* Line 677 of lalr1.cc  */
#line 1399 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args(new ASTexpression((yylocation_stack_[(4) - (1)]) + (yylocation_stack_[(4) - (4)])));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 223:

/* Line 677 of lalr1.cc  */
#line 1405 "../../src-common/cfdg.ypp"
    {
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            std::auto_ptr<ASTrepContainer> vars((yysemantic_stack_[(2) - (1)].bodyObj));
            (yyval.expression) = driver.MakeLet((yylocation_stack_[(2) - (1)]), exp);
        }
    break;

  case 224:

/* Line 677 of lalr1.cc  */
#line 1411 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 225:

/* Line 677 of lalr1.cc  */
#line 1418 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 226:

/* Line 677 of lalr1.cc  */
#line 1420 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(1) - (1)].string); }
    break;



/* Line 677 of lalr1.cc  */
#line 2946 "cfdg.tab.cpp"
	default:
          break;
      }
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
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate));
      }

    yyerror_range[0] = yylloc;
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

    yyerror_range[0] = yylocation_stack_[yylen - 1];
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
	if (yyn != yypact_ninf_)
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

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
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
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

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
  CfdgParser::yysyntax_error_ (int yystate)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int CfdgParser::yypact_ninf_ = -268;
  const short int
  CfdgParser::yypact_[] =
  {
       227,  -268,  -268,    20,  1113,  1134,  -268,    16,  -268,     0,
     159,    27,    59,  -268,    96,   122,  -268,    59,  -268,  -268,
    -268,  -268,  -268,  -268,  -268,  -268,   -45,  -268,    85,  -268,
     170,   177,   114,   193,   154,    59,   141,   122,   162,    59,
    -268,  -268,  -268,  -268,  -268,  -268,   522,   163,  -268,  -268,
    -268,   165,   178,  -268,  -268,   197,    76,   214,   191,  -268,
    -268,  -268,  -268,  -268,  -268,   195,  -268,  -268,  -268,  -268,
    -268,  -268,  -268,   206,   207,   211,  -268,   212,    15,   269,
    -268,  -268,   215,   225,   274,  -268,   259,   122,  -268,   228,
    -268,   229,  -268,   236,   522,  -268,   522,   522,   522,   238,
    -268,   230,   978,  -268,  -268,   108,  -268,  -268,  -268,  -268,
    -268,  -268,  -268,    94,    91,  -268,   147,   285,   324,   207,
    -268,    74,  -268,   292,    19,  -268,    17,  -268,    29,  -268,
    -268,   -10,  -268,   293,    74,   295,  -268,  -268,  -268,   522,
     360,   522,   249,   249,   249,   637,  -268,   109,    89,  -268,
     522,   522,   522,   522,   522,   522,   522,   522,   522,   522,
     522,   522,   522,   522,   522,   522,   522,   522,   171,   480,
     250,   251,   522,   459,    23,   254,  -268,   118,  -268,   522,
    -268,  -268,  -268,  -268,   298,   207,   381,   381,   381,   253,
     230,   206,   130,   210,   313,    26,  -268,  -268,  -268,  -268,
     265,  -268,  -268,  -268,    -7,    59,  -268,  -268,  -268,  -268,
     310,    75,   137,  -268,  -268,  -268,  -268,   204,    59,   261,
    -268,   668,  -268,  -268,   101,  -268,   119,  -268,  -268,  -268,
    -268,    19,  -268,  -268,   120,  -268,   699,   264,  -268,   730,
     544,  -268,   112,  -268,   312,   318,   262,  -268,   405,   405,
     553,   553,   553,   553,  1074,  1074,  1054,  1032,  1009,   978,
     180,   180,   180,   249,   249,   249,   206,   323,    97,   978,
     522,   522,   978,  -268,   978,  -268,  -268,  -268,   402,  -268,
     978,  -268,   381,  -268,   322,  -268,  -268,  -268,  -268,   207,
     207,  -268,  -268,   280,   287,  -268,   284,  -268,   313,   313,
     522,   230,   313,   138,  -268,  -268,  -268,  -268,  -268,  -268,
    -268,  -268,  -268,  -268,  -268,  -268,  -268,   290,  -268,  -268,
    -268,  -268,  -268,  -268,   336,  -268,  -268,  -268,  -268,  -268,
    -268,  -268,   283,   522,   522,   501,   207,   522,   522,   761,
     792,  -268,   823,   381,  -268,   263,  -268,    43,  -268,  -268,
     522,   423,   522,  -268,  -268,   854,  -268,   234,   313,   313,
    -268,    59,   158,   152,   304,  -268,   978,   978,    99,  -268,
     885,  -268,   978,   978,   207,  -268,  -268,  -268,  -268,   289,
     522,  -268,  -268,   381,   916,  -268,   947,   575,  -268,  -268,
    -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,   606,  -268,
    -268,  -268,  -268,  -268
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  CfdgParser::yydefact_[] =
  {
         0,     5,     7,     0,     2,     3,     1,     0,    31,     0,
       0,     0,     0,    43,     0,     0,    30,     0,     4,    25,
      19,    20,    17,    18,    21,    22,     0,    23,     0,    24,
       0,     0,    70,     0,    89,     0,    89,     0,    47,     0,
       6,    16,     9,    10,     8,    15,     0,    13,    97,    14,
      40,     0,     0,    11,    12,    51,     0,    67,    75,    27,
     165,   165,    54,    52,    26,     0,    28,    44,    45,    41,
      53,   142,    99,    95,     0,    86,    71,    86,     0,     0,
      38,    36,    89,     0,     0,    39,     0,     0,    37,     0,
     170,   224,   186,     0,     0,   187,     0,     0,     0,   165,
     211,     0,    55,   188,    65,     0,    97,    97,    33,    34,
      35,    68,    32,     0,     0,    29,     0,     0,     0,    50,
      49,     0,    64,     0,     0,    72,     0,    82,    81,    88,
      84,     0,    58,     0,     0,     0,    57,    46,    42,     0,
       0,     0,   199,   197,   198,     0,   165,     0,     0,   223,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   225,     0,   226,     0,    66,     0,
     116,   115,    96,   124,   117,     0,     0,     0,     0,     0,
       0,    95,     0,     0,     0,     0,   161,   164,   160,   225,
       0,    69,   146,   141,     0,     0,   133,   134,   137,   139,
     138,   225,     0,    76,   128,    98,   130,     0,     0,     0,
      94,     0,    48,    91,     0,    56,     0,    80,    78,    79,
      77,     0,    87,    60,     0,    59,     0,     0,   218,     0,
       0,   210,     0,   162,     0,     0,     0,   173,   189,   190,
     202,   201,   204,   203,   205,   206,   207,   208,   209,   191,
     193,   192,   194,   195,   196,   200,    95,     0,   224,   152,
       0,     0,   156,    62,   155,    61,   126,   125,     0,   127,
      63,   118,     0,    97,   120,   109,   121,   122,   113,     0,
       0,    73,    74,     0,   217,   178,     0,   179,     0,     0,
       0,     0,   166,   177,   181,   168,   169,   148,   142,   147,
     144,   145,   136,   135,   132,   131,   165,     0,    99,   111,
     129,   101,    93,    92,    85,    85,    83,    90,   221,   222,
     219,   220,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   103,     0,     0,   140,     0,   154,     0,   106,   104,
       0,     0,     0,   182,   183,     0,   216,   176,     0,     0,
     167,     0,     0,     0,     0,   163,   175,   174,   224,   172,
       0,   107,   151,   150,   153,   157,   102,   119,   108,     0,
       0,   123,   112,     0,     0,   212,     0,     0,   180,   184,
     185,   149,   143,   100,   110,   171,   105,   159,     0,   114,
     215,   213,   214,   158
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yypgoto_[] =
  {
      -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,
     349,     7,  -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,
    -268,  -268,  -268,  -268,  -268,   351,  -268,  -268,  -268,  -268,
    -268,  -268,  -268,   126,    66,   281,   -24,   276,  -176,   -89,
      42,   145,  -268,  -178,  -268,  -268,  -268,   -94,  -268,  -268,
    -268,  -268,  -268,    57,  -268,   172,  -268,  -114,  -268,  -268,
    -268,  -268,  -268,  -268,  -268,   -12,   -73,   -59,  -268,   -91,
    -177,  -268,    32,  -268,  -267,   -90,  -268,  -268,   -87
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yydefgoto_[] =
  {
        -1,     3,     4,     5,    40,    18,    19,    41,    20,    42,
      21,    69,    87,    44,    22,    23,    24,    25,    45,    46,
     179,   180,    47,    48,    49,    26,    27,    51,    52,    53,
      54,    28,    29,   130,   131,   122,    79,   123,   119,   105,
     117,   214,   181,   284,   320,   347,   382,   285,   343,   183,
     215,   216,   184,   116,   309,   202,   203,   204,   361,   185,
     186,   187,   188,   189,   383,    62,   100,   113,   197,   101,
     149,   246,   247,   302,   303,   102,   304,   103,   191
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char CfdgParser::yytable_ninf_ = -91;
  const short int
  CfdgParser::yytable_[] =
  {
        63,   120,   114,   217,   142,    70,   143,   144,   145,   286,
     287,   182,    84,   289,   190,   290,    71,   192,   193,   199,
       6,   126,    80,    81,   176,   126,    57,    88,   221,   205,
     218,   353,   354,   275,   127,   357,   227,    59,   127,   231,
     147,   128,    55,   228,    85,   128,   222,    56,   229,   236,
     239,   240,   305,   232,   308,   230,   306,   379,   133,   380,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   129,   269,
     126,   266,   272,   274,   276,   313,    60,   242,    61,   280,
     336,   389,   390,   127,   138,   190,   190,   190,   182,   182,
     128,   190,   190,   301,   344,   381,    64,   338,   244,   334,
     194,   195,   282,   194,   195,   245,   168,   205,    60,   169,
      61,   170,    65,   171,   356,   172,    90,   173,   194,   195,
     218,   194,   195,   314,   174,   110,   175,   223,   168,   176,
      57,   169,    76,   170,   177,   171,    72,   172,    90,   173,
     231,    67,    68,   198,    66,   140,   174,   140,   175,   196,
      82,   176,   358,   359,   324,   377,   177,    83,   231,   231,
     178,   194,   195,   199,   243,   200,   278,   332,   176,   279,
     339,   340,   325,   327,   199,    58,   200,   224,   342,   176,
     226,   190,   291,   311,   345,   315,    73,   199,   316,    78,
     234,    74,   176,    75,   360,   399,   321,   301,   301,   201,
     355,   301,    78,    60,   393,    61,   348,   349,   168,    77,
     392,   169,    86,   170,   104,   171,   106,   172,    90,   173,
     199,     1,     2,   165,   166,   176,   174,   167,   175,   107,
     317,   176,   111,   366,   367,   370,   177,   372,   373,   112,
     217,   182,   190,   115,   190,   108,   109,   363,   358,   359,
     384,   386,   387,   371,   118,   318,    99,   301,   301,   121,
     124,   168,   292,    78,   169,   205,   170,   218,   171,   132,
     172,    90,   173,   134,   136,   137,   139,   140,   148,   174,
     398,   175,   190,   206,   176,   141,   207,   146,   208,   177,
     209,   396,   225,   233,   210,   235,   167,   277,   270,   271,
     281,   211,   206,   200,   288,   207,   176,   208,   307,   209,
     312,   212,   333,   210,   322,   378,   293,   329,   334,   335,
     211,    90,   200,   337,   219,   176,   346,    89,   350,   294,
     212,   295,    90,   352,   296,   351,   -90,   213,   365,   391,
      91,   316,    92,   397,    43,    93,    50,   326,   125,   135,
     364,   297,   319,   298,   299,   362,   394,   369,    94,     0,
     237,   300,    95,    89,    96,    97,   310,     0,    90,     0,
       0,     0,    98,    99,     0,     0,    91,   220,    92,   168,
       0,    93,   169,     0,   170,     0,   171,     0,   172,    90,
     173,     0,     0,     0,    94,     0,     0,   174,    95,   175,
      96,    97,   176,     0,     0,    89,     0,   177,    98,    99,
      90,     0,     0,   238,     0,     0,     0,     0,    91,     0,
      92,     0,     0,    93,     0,     0,    89,     0,     0,     0,
       0,    90,   283,     0,     0,     0,    94,     0,     0,    91,
      95,    92,    96,    97,    93,   162,   163,   164,   165,   166,
      98,    99,   167,     0,     0,   341,     0,    94,     0,   273,
       0,    95,    89,    96,    97,     0,     0,    90,     0,     0,
       0,    98,    99,     0,     0,    91,   385,    92,     0,     0,
      93,     0,     0,    89,     0,     0,     0,     0,    90,   267,
       0,     0,     0,    94,     0,     0,   268,    95,    92,    96,
      97,    93,     0,     0,    89,     0,     0,    98,    99,    90,
     244,     0,     0,     0,    94,     0,     0,   368,    95,    92,
      96,    97,    93,     0,     0,    89,     0,     0,    98,    99,
      90,     0,     0,     0,     0,    94,     0,     0,    91,    95,
      92,    96,    97,    93,     0,     0,     0,     0,     0,    98,
      99,     0,     0,     0,     0,     0,    94,     0,   150,   151,
      95,     0,    96,    97,     0,     0,     0,   150,   151,     0,
      98,    99,   152,   153,   154,   155,   156,   157,     0,   158,
     159,   160,     0,   161,   162,   163,   164,   165,   166,   150,
     151,   167,     0,   162,   163,   164,   165,   166,     0,   331,
     167,     0,     0,   152,   153,   154,   155,   156,   157,     0,
     158,   159,   160,     0,   161,   162,   163,   164,   165,   166,
     150,   151,   167,     0,     0,     0,     0,     0,     0,     0,
     402,     0,     0,     0,   152,   153,   154,   155,   156,   157,
       0,   158,   159,   160,     0,   161,   162,   163,   164,   165,
     166,   150,   151,   167,     0,     0,     0,     0,     0,     0,
     403,     0,     0,     0,     0,   152,   153,   154,   155,   156,
     157,     0,   158,   159,   160,     0,   161,   162,   163,   164,
     165,   166,   150,   151,   167,     0,     0,     0,     0,     0,
     241,     0,     0,     0,     0,     0,   152,   153,   154,   155,
     156,   157,     0,   158,   159,   160,     0,   161,   162,   163,
     164,   165,   166,   150,   151,   167,     0,     0,     0,     0,
       0,   323,     0,     0,     0,     0,     0,   152,   153,   154,
     155,   156,   157,     0,   158,   159,   160,     0,   161,   162,
     163,   164,   165,   166,   150,   151,   167,     0,     0,     0,
       0,     0,   328,     0,     0,     0,     0,     0,   152,   153,
     154,   155,   156,   157,     0,   158,   159,   160,     0,   161,
     162,   163,   164,   165,   166,   150,   151,   167,     0,     0,
       0,     0,     0,   330,     0,     0,     0,     0,     0,   152,
     153,   154,   155,   156,   157,     0,   158,   159,   160,     0,
     161,   162,   163,   164,   165,   166,   150,   151,   167,     0,
       0,     0,     0,     0,   374,     0,     0,     0,     0,     0,
     152,   153,   154,   155,   156,   157,     0,   158,   159,   160,
       0,   161,   162,   163,   164,   165,   166,   150,   151,   167,
       0,     0,     0,     0,     0,   375,     0,     0,     0,     0,
       0,   152,   153,   154,   155,   156,   157,     0,   158,   159,
     160,     0,   161,   162,   163,   164,   165,   166,   150,   151,
     167,     0,     0,     0,     0,     0,   376,     0,     0,     0,
       0,     0,   152,   153,   154,   155,   156,   157,     0,   158,
     159,   160,     0,   161,   162,   163,   164,   165,   166,   150,
     151,   167,     0,     0,     0,     0,     0,   388,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,     0,
     158,   159,   160,     0,   161,   162,   163,   164,   165,   166,
     150,   151,   167,     0,     0,     0,     0,     0,   395,     0,
       0,     0,     0,     0,   152,   153,   154,   155,   156,   157,
       0,   158,   159,   160,     0,   161,   162,   163,   164,   165,
     166,   150,   151,   167,     0,     0,     0,     0,     0,   400,
       0,     0,     0,     0,     0,   152,   153,   154,   155,   156,
     157,     0,   158,   159,   160,     0,   161,   162,   163,   164,
     165,   166,   150,   151,   167,     0,     0,     0,     0,     0,
     401,     0,     0,     0,     0,     0,   152,   153,   154,   155,
     156,   157,     0,   158,   159,   160,     0,   161,   162,   163,
     164,   165,   166,   150,   151,   167,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   152,   153,   154,
     155,   156,   157,     0,   158,   159,   150,   151,     0,   162,
     163,   164,   165,   166,     0,     0,   167,     0,     0,     0,
     152,   153,   154,   155,   156,   157,     0,   158,   150,   151,
       0,     0,   162,   163,   164,   165,   166,     0,     0,   167,
       0,     0,   152,   153,   154,   155,   156,   157,   150,   151,
       0,     0,     0,     0,   162,   163,   164,   165,   166,     0,
       0,   167,   152,   153,   154,   155,     7,     0,     0,     8,
       9,    10,     0,     0,   162,   163,   164,   165,   166,     0,
       0,   167,    11,     0,    12,     0,    13,    30,     0,    14,
      31,    32,    33,     0,     0,    15,    16,    17,     0,     0,
       0,     0,     0,    34,     0,    35,     0,    13,     0,     0,
      36,     0,     0,     0,     0,     0,    37,    38,    39
  };

  /* YYCHECK.  */
  const short int
  CfdgParser::yycheck_[] =
  {
        12,    74,    61,   117,    94,    17,    96,    97,    98,   187,
     188,   105,    36,   190,   105,   191,    61,   106,   107,    26,
       0,     6,    34,    35,    31,     6,    26,    39,   118,   116,
     117,   298,   299,    10,    19,   302,    19,    10,    19,    49,
      99,    26,    26,    26,    37,    26,   119,    31,    19,   139,
     140,   141,    26,    63,    61,    26,    30,    14,    82,    16,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,    63,   169,
       6,   168,   172,   173,    61,    10,    59,   146,    61,   179,
     266,   358,   359,    19,    87,   186,   187,   188,   192,   193,
      26,   192,   193,   194,   282,    62,    10,    10,    19,    10,
      19,    20,   185,    19,    20,    26,     8,   204,    59,    11,
      61,    13,    26,    15,   301,    17,    18,    19,    19,    20,
     217,    19,    20,    58,    26,    59,    28,    63,     8,    31,
      26,    11,    28,    13,    36,    15,    61,    17,    18,    19,
      49,    29,    30,    62,    58,    58,    26,    58,    28,    65,
      19,    31,    24,    25,    63,   343,    36,    26,    49,    49,
      62,    19,    20,    26,    65,    28,    58,    65,    31,    61,
     270,   271,    63,    63,    26,    26,    28,   121,   278,    31,
     124,   282,    62,   205,   283,    58,    26,    26,    61,    58,
     134,    31,    31,    26,    66,   383,   218,   298,   299,    62,
     300,   302,    58,    59,    62,    61,   289,   290,     8,    26,
      62,    11,    60,    13,    61,    15,    61,    17,    18,    19,
      26,     4,     5,    53,    54,    31,    26,    57,    28,    61,
      36,    31,    28,   333,   334,   335,    36,   337,   338,    58,
     364,   345,   343,    58,   345,    58,    59,   316,    24,    25,
     350,   351,   352,   336,    58,    61,    59,   358,   359,    58,
      58,     8,    62,    58,    11,   362,    13,   364,    15,    10,
      17,    18,    19,    58,    10,    26,    58,    58,    58,    26,
     380,    28,   383,     8,    31,    59,    11,    59,    13,    36,
      15,   374,    10,    10,    19,    10,    57,    53,    58,    58,
      12,    26,     8,    28,    61,    11,    31,    13,    53,    15,
      10,    36,    10,    19,    63,    62,    13,    63,    10,    67,
      26,    18,    28,    10,    10,    31,    14,    13,    58,    26,
      36,    28,    18,    59,    31,    58,    10,    62,    65,   361,
      26,    61,    28,    64,     5,    31,     5,   231,    77,    83,
     318,    48,   217,    50,    51,   308,    62,   335,    44,    -1,
      10,    58,    48,    13,    50,    51,   204,    -1,    18,    -1,
      -1,    -1,    58,    59,    -1,    -1,    26,    63,    28,     8,
      -1,    31,    11,    -1,    13,    -1,    15,    -1,    17,    18,
      19,    -1,    -1,    -1,    44,    -1,    -1,    26,    48,    28,
      50,    51,    31,    -1,    -1,    13,    -1,    36,    58,    59,
      18,    -1,    -1,    63,    -1,    -1,    -1,    -1,    26,    -1,
      28,    -1,    -1,    31,    -1,    -1,    13,    -1,    -1,    -1,
      -1,    18,    61,    -1,    -1,    -1,    44,    -1,    -1,    26,
      48,    28,    50,    51,    31,    50,    51,    52,    53,    54,
      58,    59,    57,    -1,    -1,    63,    -1,    44,    -1,    10,
      -1,    48,    13,    50,    51,    -1,    -1,    18,    -1,    -1,
      -1,    58,    59,    -1,    -1,    26,    63,    28,    -1,    -1,
      31,    -1,    -1,    13,    -1,    -1,    -1,    -1,    18,    19,
      -1,    -1,    -1,    44,    -1,    -1,    26,    48,    28,    50,
      51,    31,    -1,    -1,    13,    -1,    -1,    58,    59,    18,
      19,    -1,    -1,    -1,    44,    -1,    -1,    26,    48,    28,
      50,    51,    31,    -1,    -1,    13,    -1,    -1,    58,    59,
      18,    -1,    -1,    -1,    -1,    44,    -1,    -1,    26,    48,
      28,    50,    51,    31,    -1,    -1,    -1,    -1,    -1,    58,
      59,    -1,    -1,    -1,    -1,    -1,    44,    -1,    24,    25,
      48,    -1,    50,    51,    -1,    -1,    -1,    24,    25,    -1,
      58,    59,    38,    39,    40,    41,    42,    43,    -1,    45,
      46,    47,    -1,    49,    50,    51,    52,    53,    54,    24,
      25,    57,    -1,    50,    51,    52,    53,    54,    -1,    65,
      57,    -1,    -1,    38,    39,    40,    41,    42,    43,    -1,
      45,    46,    47,    -1,    49,    50,    51,    52,    53,    54,
      24,    25,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      -1,    45,    46,    47,    -1,    49,    50,    51,    52,    53,
      54,    24,    25,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,
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
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    43,    -1,    45,    46,    24,    25,    -1,    50,
      51,    52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    -1,    45,    24,    25,
      -1,    -1,    50,    51,    52,    53,    54,    -1,    -1,    57,
      -1,    -1,    38,    39,    40,    41,    42,    43,    24,    25,
      -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,    -1,
      -1,    57,    38,    39,    40,    41,     3,    -1,    -1,     6,
       7,     8,    -1,    -1,    50,    51,    52,    53,    54,    -1,
      -1,    57,    19,    -1,    21,    -1,    23,     3,    -1,    26,
       6,     7,     8,    -1,    -1,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    19,    -1,    21,    -1,    23,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    32,    33,    34
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  CfdgParser::yystos_[] =
  {
         0,     4,     5,    69,    70,    71,     0,     3,     6,     7,
       8,    19,    21,    23,    26,    32,    33,    34,    73,    74,
      76,    78,    82,    83,    84,    85,    93,    94,    99,   100,
       3,     6,     7,     8,    19,    21,    26,    32,    33,    34,
      72,    75,    77,    78,    81,    86,    87,    90,    91,    92,
      93,    95,    96,    97,    98,    26,    31,    26,    26,    10,
      59,    61,   133,   133,    10,    26,    58,    29,    30,    79,
     133,    61,    61,    26,    31,    26,    28,    26,    58,   104,
     133,   133,    19,    26,   104,    79,    60,    80,   133,    13,
      18,    26,    28,    31,    44,    48,    50,    51,    58,    59,
     134,   137,   143,   145,    61,   107,    61,    61,    58,    59,
      59,    28,    58,   135,   135,    58,   121,   108,    58,   106,
     134,    58,   103,   105,    58,   103,     6,    19,    26,    63,
     101,   102,    10,   104,    58,   105,    10,    26,    79,    58,
      58,    59,   143,   143,   143,   143,    59,   135,    58,   138,
      24,    25,    38,    39,    40,    41,    42,    43,    45,    46,
      47,    49,    50,    51,    52,    53,    54,    57,     8,    11,
      13,    15,    17,    19,    26,    28,    31,    36,    62,    88,
      89,   110,   115,   117,   120,   127,   128,   129,   130,   131,
     137,   146,   107,   107,    19,    20,    65,   136,    62,    26,
      28,    62,   123,   124,   125,   146,     8,    11,    13,    15,
      19,    26,    36,    62,   109,   118,   119,   125,   146,    10,
      63,   143,   134,    63,   102,    10,   102,    19,    26,    19,
      26,    49,    63,    10,   102,    10,   143,    10,    63,   143,
     143,    63,   135,    65,    19,    26,   139,   140,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   146,    19,    26,   143,
      58,    58,   143,    10,   143,    10,    61,    53,    58,    61,
     143,    12,   134,    61,   111,   115,   111,   111,    61,   138,
     106,    62,    62,    13,    26,    28,    31,    48,    50,    51,
      58,   137,   141,   142,   144,    26,    30,    53,    61,   122,
     123,   133,    10,    10,    58,    58,    61,    36,    61,   109,
     112,   133,    63,    63,    63,    63,   101,    63,    63,    63,
      63,    65,    65,    10,    10,    67,   106,    10,    10,   143,
     143,    63,   143,   116,   111,   107,    14,   113,   134,   134,
      58,    58,    59,   142,   142,   143,   138,   142,    24,    25,
      66,   126,   121,   135,   108,    65,   143,   143,    26,   140,
     143,   134,   143,   143,    63,    63,    63,   111,    62,    14,
      16,    62,   114,   132,   143,    63,   143,   143,    63,   142,
     142,   133,    62,    62,    62,    63,   134,    64,   143,   111,
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
      74,    74,    74,    74,    74,    74,    75,    75,    75,    75,
      75,    76,    77,    78,    79,    79,    80,    80,    81,    81,
      81,    82,    83,    84,    85,    86,    87,    87,    87,    87,
      87,    88,    88,    89,    90,    91,    92,    93,    93,    94,
      95,    95,    96,    97,    98,    99,   100,   101,   101,   101,
     101,   101,   101,   102,   102,   103,   103,   104,   104,   104,
     105,   105,   106,   106,   106,   106,   107,   107,   108,   108,
     109,   109,   110,   110,   110,   110,   110,   110,   111,   111,
     112,   112,   113,   113,   114,   115,   115,   115,   116,   115,
     115,   115,   115,   115,   115,   117,   117,   117,   118,   118,
     118,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     120,   121,   121,   122,   122,   123,   124,   124,   126,   125,
     127,   127,   127,   128,   129,   130,   130,   131,   132,   132,
     133,   133,   134,   134,   135,   135,   136,   136,   136,   136,
     137,   138,   139,   139,   140,   140,   141,   141,   142,   142,
     142,   142,   142,   142,   142,   142,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   144,   144,   144,   144,   144,   144,   145,   145,
     145,   145,   145,   145,   145,   146,   146
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  CfdgParser::yyr2_[] =
  {
         0,     2,     2,     2,     2,     0,     2,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     3,
       1,     1,     3,     3,     3,     3,     2,     2,     2,     2,
       1,     2,     3,     1,     1,     1,     2,     0,     4,     3,
       3,     2,     2,     2,     2,     2,     4,     3,     3,     4,
       4,     2,     2,     2,     3,     2,     3,     2,     3,     4,
       1,     2,     3,     4,     4,     2,     4,     2,     2,     2,
       2,     1,     1,     3,     1,     3,     0,     3,     2,     0,
       3,     2,     3,     3,     2,     0,     2,     0,     2,     0,
       4,     2,     4,     3,     3,     5,     3,     4,     3,     1,
       3,     1,     2,     0,     2,     1,     1,     1,     0,     4,
       2,     2,     2,     4,     1,     2,     2,     2,     1,     2,
       1,     2,     2,     1,     1,     2,     2,     1,     1,     1,
       3,     2,     0,     3,     1,     2,     1,     2,     0,     4,
       4,     4,     2,     4,     3,     2,     2,     4,     3,     2,
       3,     3,     3,     5,     2,     0,     2,     3,     2,     2,
       1,     5,     3,     1,     3,     3,     2,     1,     1,     1,
       3,     1,     2,     2,     3,     3,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     4,     4,     4,     2,     1,     3,     4,
       4,     4,     4,     2,     1,     1,     1
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
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
  "function_parameter_list", "mandatory_function_parameter_list",
  "parameter_spec", "buncha_elements", "buncha_pathOps_v2",
  "pathOp_simple_v2", "element_simple", "one_or_more_elements",
  "one_or_more_pathOp_v2", "caseBody", "caseBody_element", "element",
  "$@1", "element_v2clue", "pathOp_v2", "pathOp_v3clues", "element_loop",
  "buncha_replacements_v2", "one_or_more_replacements_v2",
  "replacement_simple_v2", "replacement_v2", "loopHeader_v2", "$@2",
  "loopHeader", "ifHeader", "ifElseHeader", "transHeader", "switchHeader",
  "caseHeader", "modification_v2", "modification", "buncha_adjustments",
  "adjustment", "letHeader", "letBody", "letVariables", "letVariable",
  "explist", "exp", "exp2", "expfunc", "exp2func", "shapeName", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const CfdgParser::rhs_number_type
  CfdgParser::yyrhs_[] =
  {
        69,     0,    -1,     4,    70,    -1,     5,    71,    -1,    70,
      73,    -1,    -1,    71,    72,    -1,    -1,    81,    -1,    77,
      -1,    78,    -1,    97,    -1,    98,    -1,    90,    -1,    92,
      -1,    86,    -1,    75,    -1,    82,    -1,    83,    -1,    76,
      -1,    78,    -1,    84,    -1,    85,    -1,    94,    -1,   100,
      -1,    74,    -1,    26,    10,    -1,    19,    10,    -1,    26,
      58,    -1,    26,    26,    58,    -1,    33,    -1,     6,    -1,
       8,    26,    58,    -1,     3,    26,    58,    -1,     3,    26,
      59,    -1,     3,    31,    59,    -1,    21,   133,    -1,    34,
     133,    -1,    19,   133,    -1,    32,    79,    -1,    93,    -1,
      32,    79,    -1,    33,    80,    79,    -1,    23,    -1,    29,
      -1,    30,    -1,    60,    26,    -1,    -1,     3,    26,   106,
     134,    -1,     3,    31,   134,    -1,     3,    26,   106,    -1,
       3,    26,    -1,    21,   133,    -1,    34,   133,    -1,    19,
     133,    -1,    87,   143,    -1,     6,    26,   105,    10,    -1,
      26,   104,    10,    -1,    19,   104,    10,    -1,    26,    26,
     105,    10,    -1,    26,    19,   104,    10,    -1,    26,    10,
      -1,    19,    10,    -1,    88,   143,    -1,     6,    26,   103,
      -1,    90,    61,    -1,    91,   107,    62,    -1,     7,    26,
      -1,     7,    26,    28,    -1,    93,    61,   121,    62,    -1,
       7,    -1,     7,    28,    -1,     8,    26,   103,    -1,    95,
      61,   107,    62,    -1,    96,    61,   107,    62,    -1,     8,
      26,    -1,    99,    61,   108,    62,    -1,    26,    26,    -1,
       6,    26,    -1,    26,    19,    -1,     6,    19,    -1,    26,
      -1,    19,    -1,   102,    49,   101,    -1,   101,    -1,    58,
     102,    63,    -1,    -1,    58,   102,    63,    -1,    58,    63,
      -1,    -1,    58,   102,    63,    -1,    58,    63,    -1,    58,
     143,    63,    -1,    58,    10,    63,    -1,    58,    63,    -1,
      -1,   107,   115,    -1,    -1,   108,   118,    -1,    -1,    36,
      61,   135,    62,    -1,   146,   133,    -1,    36,    58,   143,
      63,    -1,    36,    58,    63,    -1,   146,   106,   134,    -1,
      13,    58,   143,    63,   134,    -1,   137,   138,   134,    -1,
       8,   146,   106,   134,    -1,    61,   107,    62,    -1,   115,
      -1,    61,   108,    62,    -1,   109,    -1,   113,   114,    -1,
      -1,   132,   111,    -1,   110,    -1,    89,    -1,   120,    -1,
      -1,   120,    12,   116,   111,    -1,   128,   111,    -1,   129,
     111,    -1,   130,   111,    -1,   131,    61,   113,    62,    -1,
     117,    -1,    28,    53,    -1,    26,    61,    -1,    36,    61,
      -1,   109,    -1,   125,   112,    -1,   119,    -1,    36,    58,
      -1,    26,    58,    -1,     8,    -1,    11,    -1,    26,    10,
      -1,    19,    10,    -1,    13,    -1,    19,    -1,    15,    -1,
     127,   134,   111,    -1,   121,   124,    -1,    -1,    61,   121,
      62,    -1,   123,    -1,   146,   133,    -1,   123,    -1,   125,
     122,    -1,    -1,    28,    53,   126,   133,    -1,    11,    26,
      10,   143,    -1,    11,    19,    10,   143,    -1,    11,   143,
      -1,    13,    58,   143,    63,    -1,   128,   111,    14,    -1,
      19,   143,    -1,    17,   143,    -1,    15,    58,   143,    63,
      -1,    16,   143,    64,    -1,    14,    64,    -1,    61,   135,
      62,    -1,    59,   135,    65,    -1,    59,   135,    65,    -1,
      59,    59,   135,    65,    65,    -1,   135,   136,    -1,    -1,
      19,   141,    -1,    19,   142,    66,    -1,    20,    26,    -1,
      20,    30,    -1,    18,    -1,    58,   139,    67,   143,    63,
      -1,   139,    67,   140,    -1,   140,    -1,    26,    10,   143,
      -1,    19,    10,   143,    -1,   141,   142,    -1,   142,    -1,
      28,    -1,    48,    -1,    58,   143,    63,    -1,   144,    -1,
      50,   142,    -1,    51,   142,    -1,   142,    24,   142,    -1,
     142,    25,   142,    -1,    28,    -1,    48,    -1,   145,    -1,
     143,    24,   143,    -1,   143,    25,   143,    -1,   143,    49,
     143,    -1,   143,    51,   143,    -1,   143,    50,   143,    -1,
     143,    52,   143,    -1,   143,    53,   143,    -1,   143,    54,
     143,    -1,    50,   143,    -1,    51,   143,    -1,    44,   143,
      -1,   143,    57,   143,    -1,   143,    39,   143,    -1,   143,
      38,   143,    -1,   143,    41,   143,    -1,   143,    40,   143,
      -1,   143,    42,   143,    -1,   143,    43,   143,    -1,   143,
      45,   143,    -1,   143,    46,   143,    -1,   143,    47,   143,
      -1,    58,   143,    63,    -1,   134,    -1,    26,    58,    63,
      -1,    26,    58,   143,    63,    -1,    31,    59,   143,    65,
      -1,    13,    58,   143,    63,    -1,   137,   138,    -1,    26,
      -1,    26,    58,    63,    -1,    26,    58,   143,    63,    -1,
      31,    59,   143,    65,    -1,    13,    58,   143,    63,    -1,
      26,    58,    10,    63,    -1,   137,   138,    -1,    26,    -1,
      26,    -1,    31,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  CfdgParser::yyprhs_[] =
  {
         0,     0,     3,     6,     9,    12,    13,    16,    17,    19,
      21,    23,    25,    27,    29,    31,    33,    35,    37,    39,
      41,    43,    45,    47,    49,    51,    53,    56,    59,    62,
      66,    68,    70,    74,    78,    82,    86,    89,    92,    95,
      98,   100,   103,   107,   109,   111,   113,   116,   117,   122,
     126,   130,   133,   136,   139,   142,   145,   150,   154,   158,
     163,   168,   171,   174,   177,   181,   184,   188,   191,   195,
     200,   202,   205,   209,   214,   219,   222,   227,   230,   233,
     236,   239,   241,   243,   247,   249,   253,   254,   258,   261,
     262,   266,   269,   273,   277,   280,   281,   284,   285,   288,
     289,   294,   297,   302,   306,   310,   316,   320,   325,   329,
     331,   335,   337,   340,   341,   344,   346,   348,   350,   351,
     356,   359,   362,   365,   370,   372,   375,   378,   381,   383,
     386,   388,   391,   394,   396,   398,   401,   404,   406,   408,
     410,   414,   417,   418,   422,   424,   427,   429,   432,   433,
     438,   443,   448,   451,   456,   460,   463,   466,   471,   475,
     478,   482,   486,   490,   496,   499,   500,   503,   507,   510,
     513,   515,   521,   525,   527,   531,   535,   538,   540,   542,
     544,   548,   550,   553,   556,   560,   564,   566,   568,   570,
     574,   578,   582,   586,   590,   594,   598,   602,   605,   608,
     611,   615,   619,   623,   627,   631,   635,   639,   643,   647,
     651,   655,   657,   661,   666,   671,   676,   679,   681,   685,
     690,   695,   700,   705,   708,   710,   712
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  CfdgParser::yyrline_[] =
  {
         0,   189,   189,   189,   192,   197,   201,   206,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   258,   259,   260,   261,
     262,   266,   275,   286,   293,   293,   296,   297,   301,   314,
     326,   340,   351,   361,   371,   386,   395,   401,   407,   413,
     419,   428,   432,   440,   449,   465,   479,   488,   497,   512,
     520,   532,   549,   574,   583,   593,   606,   613,   619,   625,
     630,   634,   640,   646,   647,   651,   652,   656,   657,   658,
     662,   663,   667,   668,   669,   670,   674,   679,   683,   686,
     690,   697,   707,   716,   725,   737,   751,   765,   779,   781,
     789,   791,   797,   801,   805,   809,   813,   817,   828,   828,
     846,   857,   868,   879,   888,   895,   896,   897,   901,   903,
     911,   923,   924,   925,   926,   927,   928,   929,   930,   931,
     935,   946,   949,   953,   955,   961,   970,   972,   983,   983,
     998,  1012,  1026,  1041,  1054,  1064,  1076,  1092,  1105,  1134,
    1147,  1152,  1159,  1164,  1171,  1176,  1185,  1190,  1200,  1205,
    1212,  1221,  1227,  1229,  1233,  1239,  1246,  1250,  1256,  1258,
    1260,  1262,  1264,  1266,  1268,  1273,  1280,  1282,  1284,  1286,
    1291,  1296,  1298,  1300,  1302,  1304,  1306,  1308,  1310,  1312,
    1314,  1316,  1318,  1320,  1322,  1324,  1326,  1328,  1330,  1332,
    1334,  1336,  1340,  1345,  1351,  1357,  1363,  1369,  1376,  1381,
    1387,  1393,  1399,  1405,  1411,  1418,  1420
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
  const int CfdgParser::yylast_ = 1168;
  const int CfdgParser::yynnts_ = 79;
  const int CfdgParser::yyempty_ = -2;
  const int CfdgParser::yyfinal_ = 6;
  const int CfdgParser::yyterror_ = 1;
  const int CfdgParser::yyerrcode_ = 256;
  const int CfdgParser::yyntokens_ = 68;

  const unsigned int CfdgParser::yyuser_token_number_max_ = 305;
  const CfdgParser::token_number_type CfdgParser::yyundef_token_ = 2;


} // yy

/* Line 1053 of lalr1.cc  */
#line 3912 "cfdg.tab.cpp"


/* Line 1055 of lalr1.cc  */
#line 1423 "../../src-common/cfdg.ypp"


void yy::CfdgParser::error(const CfdgParser::location_type& l, const std::string& m)
{
    driver.mWant2ndPass = false;
    driver.error(l, m);
}

