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
#line 81 "../../src-common/cfdg.ypp"

#include "astreplacement.h"
#include "astexpression.h"
    
    using namespace AST;

/* Line 316 of lalr1.cc  */
#line 179 "../../src-common/cfdg.ypp"

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
#line 162 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 263 "cfdg.tab.cpp"
	break;
      case 29: /* "USER_FILENAME" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 272 "cfdg.tab.cpp"
	break;
      case 30: /* "USER_QSTRING" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 281 "cfdg.tab.cpp"
	break;
      case 31: /* "USER_ARRAYNAME" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 290 "cfdg.tab.cpp"
	break;
      case 36: /* "USER_PATHOP" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 299 "cfdg.tab.cpp"
	break;
      case 72: /* "statement" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 308 "cfdg.tab.cpp"
	break;
      case 73: /* "statement_v2" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 317 "cfdg.tab.cpp"
	break;
      case 79: /* "fileString" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 326 "cfdg.tab.cpp"
	break;
      case 80: /* "fileNameSpace" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 335 "cfdg.tab.cpp"
	break;
      case 81: /* "initialization" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 344 "cfdg.tab.cpp"
	break;
      case 82: /* "initialization_v2" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 353 "cfdg.tab.cpp"
	break;
      case 83: /* "background" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 362 "cfdg.tab.cpp"
	break;
      case 84: /* "tile" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 371 "cfdg.tab.cpp"
	break;
      case 85: /* "size" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 380 "cfdg.tab.cpp"
	break;
      case 87: /* "global_definition_header" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 389 "cfdg.tab.cpp"
	break;
      case 88: /* "definition_header" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 398 "cfdg.tab.cpp"
	break;
      case 90: /* "shape" */

/* Line 479 of lalr1.cc  */
#line 175 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->shapeObj); };

/* Line 479 of lalr1.cc  */
#line 407 "cfdg.tab.cpp"
	break;
      case 91: /* "shape_singleton_header" */

/* Line 479 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 416 "cfdg.tab.cpp"
	break;
      case 92: /* "shape_singleton" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 425 "cfdg.tab.cpp"
	break;
      case 93: /* "rule_header_v2" */

/* Line 479 of lalr1.cc  */
#line 172 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 434 "cfdg.tab.cpp"
	break;
      case 95: /* "rule_header" */

/* Line 479 of lalr1.cc  */
#line 171 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 443 "cfdg.tab.cpp"
	break;
      case 96: /* "path_header" */

/* Line 479 of lalr1.cc  */
#line 171 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 452 "cfdg.tab.cpp"
	break;
      case 97: /* "rule" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 461 "cfdg.tab.cpp"
	break;
      case 98: /* "path" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 470 "cfdg.tab.cpp"
	break;
      case 99: /* "path_header_v2" */

/* Line 479 of lalr1.cc  */
#line 172 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 479 "cfdg.tab.cpp"
	break;
      case 106: /* "parameter_spec" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 488 "cfdg.tab.cpp"
	break;
      case 109: /* "pathOp_simple_v2" */

/* Line 479 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 497 "cfdg.tab.cpp"
	break;
      case 110: /* "element_simple" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 506 "cfdg.tab.cpp"
	break;
      case 115: /* "element" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 515 "cfdg.tab.cpp"
	break;
      case 118: /* "pathOp_v2" */

/* Line 479 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 524 "cfdg.tab.cpp"
	break;
      case 120: /* "element_loop" */

/* Line 479 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 533 "cfdg.tab.cpp"
	break;
      case 123: /* "replacement_simple_v2" */

/* Line 479 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 542 "cfdg.tab.cpp"
	break;
      case 124: /* "replacement_v2" */

/* Line 479 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 551 "cfdg.tab.cpp"
	break;
      case 125: /* "loopHeader_v2" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 560 "cfdg.tab.cpp"
	break;
      case 127: /* "loopHeader" */

/* Line 479 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 569 "cfdg.tab.cpp"
	break;
      case 128: /* "ifHeader" */

/* Line 479 of lalr1.cc  */
#line 173 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ifObj); };

/* Line 479 of lalr1.cc  */
#line 578 "cfdg.tab.cpp"
	break;
      case 129: /* "ifElseHeader" */

/* Line 479 of lalr1.cc  */
#line 173 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ifObj); };

/* Line 479 of lalr1.cc  */
#line 587 "cfdg.tab.cpp"
	break;
      case 130: /* "transHeader" */

/* Line 479 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 596 "cfdg.tab.cpp"
	break;
      case 131: /* "switchHeader" */

/* Line 479 of lalr1.cc  */
#line 174 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->switchObj); };

/* Line 479 of lalr1.cc  */
#line 605 "cfdg.tab.cpp"
	break;
      case 132: /* "caseHeader" */

/* Line 479 of lalr1.cc  */
#line 176 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); };

/* Line 479 of lalr1.cc  */
#line 614 "cfdg.tab.cpp"
	break;
      case 133: /* "modification_v2" */

/* Line 479 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 623 "cfdg.tab.cpp"
	break;
      case 134: /* "modification" */

/* Line 479 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 632 "cfdg.tab.cpp"
	break;
      case 135: /* "buncha_mods" */

/* Line 479 of lalr1.cc  */
#line 177 "../../src-common/cfdg.ypp"
	{ ASTtransform::ClearMods(*(yyvaluep->modList)); delete (yyvaluep->modList); };

/* Line 479 of lalr1.cc  */
#line 641 "cfdg.tab.cpp"
	break;
      case 136: /* "buncha_adjustments" */

/* Line 479 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 650 "cfdg.tab.cpp"
	break;
      case 137: /* "adjustment" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->term); };

/* Line 479 of lalr1.cc  */
#line 659 "cfdg.tab.cpp"
	break;
      case 138: /* "letHeader" */

/* Line 479 of lalr1.cc  */
#line 178 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->bodyObj); };

/* Line 479 of lalr1.cc  */
#line 668 "cfdg.tab.cpp"
	break;
      case 139: /* "letBody" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 677 "cfdg.tab.cpp"
	break;
      case 142: /* "explist" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 686 "cfdg.tab.cpp"
	break;
      case 143: /* "exp" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 695 "cfdg.tab.cpp"
	break;
      case 144: /* "exp2" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 704 "cfdg.tab.cpp"
	break;
      case 145: /* "expfunc" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 713 "cfdg.tab.cpp"
	break;
      case 146: /* "exp2func" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 722 "cfdg.tab.cpp"
	break;
      case 147: /* "shapeName" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 731 "cfdg.tab.cpp"
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
#line 195 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 6:

/* Line 677 of lalr1.cc  */
#line 204 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 9:

/* Line 677 of lalr1.cc  */
#line 214 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 10:

/* Line 677 of lalr1.cc  */
#line 215 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 13:

/* Line 677 of lalr1.cc  */
#line 218 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].shapeObj); }
    break;

  case 15:

/* Line 677 of lalr1.cc  */
#line 220 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 16:

/* Line 677 of lalr1.cc  */
#line 221 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 19:

/* Line 677 of lalr1.cc  */
#line 230 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 20:

/* Line 677 of lalr1.cc  */
#line 231 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 25:

/* Line 677 of lalr1.cc  */
#line 236 "../../src-common/cfdg.ypp"
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
#line 248 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 27:

/* Line 677 of lalr1.cc  */
#line 249 "../../src-common/cfdg.ypp"
    {}
    break;

  case 28:

/* Line 677 of lalr1.cc  */
#line 250 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 29:

/* Line 677 of lalr1.cc  */
#line 251 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (1)].string); delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 32:

/* Line 677 of lalr1.cc  */
#line 254 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 33:

/* Line 677 of lalr1.cc  */
#line 255 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 34:

/* Line 677 of lalr1.cc  */
#line 256 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 35:

/* Line 677 of lalr1.cc  */
#line 257 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 36:

/* Line 677 of lalr1.cc  */
#line 261 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 37:

/* Line 677 of lalr1.cc  */
#line 262 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 38:

/* Line 677 of lalr1.cc  */
#line 263 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 39:

/* Line 677 of lalr1.cc  */
#line 264 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 40:

/* Line 677 of lalr1.cc  */
#line 265 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(1) - (1)].ruleObj); }
    break;

  case 41:

/* Line 677 of lalr1.cc  */
#line 269 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(2) - (2)].string));
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(NULL);
            driver.IncludeFile(*file);
        }
    break;

  case 42:

/* Line 677 of lalr1.cc  */
#line 278 "../../src-common/cfdg.ypp"
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
#line 289 "../../src-common/cfdg.ypp"
    {
            if (driver.EndInclude())
                YYACCEPT;
        }
    break;

  case 46:

/* Line 677 of lalr1.cc  */
#line 299 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 47:

/* Line 677 of lalr1.cc  */
#line 300 "../../src-common/cfdg.ypp"
    { (yyval.string) = NULL; }
    break;

  case 48:

/* Line 677 of lalr1.cc  */
#line 304 "../../src-common/cfdg.ypp"
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
#line 317 "../../src-common/cfdg.ypp"
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
#line 329 "../../src-common/cfdg.ypp"
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
#line 343 "../../src-common/cfdg.ypp"
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
#line 354 "../../src-common/cfdg.ypp"
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
#line 364 "../../src-common/cfdg.ypp"
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
#line 374 "../../src-common/cfdg.ypp"
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
#line 389 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(2) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            if (var.get())
                driver.NextParameter(*var, exp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 56:

/* Line 677 of lalr1.cc  */
#line 398 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("shape");
            driver.push_paramDecls(*(yysemantic_stack_[(4) - (2)].string), (yyloc), numtype);
            (yyval.string) = (yysemantic_stack_[(4) - (2)].string);
        }
    break;

  case 57:

/* Line 677 of lalr1.cc  */
#line 404 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("number");
            driver.push_paramDecls(*(yysemantic_stack_[(3) - (1)].string), (yyloc), numtype);
            (yyval.string) = (yysemantic_stack_[(3) - (1)].string);
        }
    break;

  case 58:

/* Line 677 of lalr1.cc  */
#line 410 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            error((yylocation_stack_[(3) - (1)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 59:

/* Line 677 of lalr1.cc  */
#line 416 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(4) - (1)].string));
            driver.push_paramDecls(*(yysemantic_stack_[(4) - (2)].string), (yyloc), *type);
            (yyval.string) = (yysemantic_stack_[(4) - (2)].string);
        }
    break;

  case 60:

/* Line 677 of lalr1.cc  */
#line 422 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(4) - (1)].string));
            driver.isFunction = false;
            error((yylocation_stack_[(4) - (2)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 61:

/* Line 677 of lalr1.cc  */
#line 431 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            (yyval.string) = (yysemantic_stack_[(2) - (1)].string);
        }
    break;

  case 62:

/* Line 677 of lalr1.cc  */
#line 435 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            error((yylocation_stack_[(2) - (1)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 63:

/* Line 677 of lalr1.cc  */
#line 443 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(2) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            if (var.get() && driver.mCompilePhase == 2)
                driver.NextParameter(*var, exp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 64:

/* Line 677 of lalr1.cc  */
#line 452 "../../src-common/cfdg.ypp"
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
#line 468 "../../src-common/cfdg.ypp"
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
#line 482 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(3) - (1)].ruleObj);
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 67:

/* Line 677 of lalr1.cc  */
#line 491 "../../src-common/cfdg.ypp"
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
#line 500 "../../src-common/cfdg.ypp"
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
#line 515 "../../src-common/cfdg.ypp"
    {
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 70:

/* Line 677 of lalr1.cc  */
#line 523 "../../src-common/cfdg.ypp"
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
#line 535 "../../src-common/cfdg.ypp"
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
#line 552 "../../src-common/cfdg.ypp"
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
#line 577 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 74:

/* Line 677 of lalr1.cc  */
#line 586 "../../src-common/cfdg.ypp"
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
#line 596 "../../src-common/cfdg.ypp"
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
#line 609 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 77:

/* Line 677 of lalr1.cc  */
#line 616 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(2) - (1)].string));
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(*type, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
		}
    break;

  case 78:

/* Line 677 of lalr1.cc  */
#line 622 "../../src-common/cfdg.ypp"
    {
            static std::string shapeStr("shape");
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(shapeStr, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 79:

/* Line 677 of lalr1.cc  */
#line 628 "../../src-common/cfdg.ypp"
    {
            delete (yysemantic_stack_[(2) - (1)].string);
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 80:

/* Line 677 of lalr1.cc  */
#line 633 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 81:

/* Line 677 of lalr1.cc  */
#line 637 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("number");
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            driver.NextParameterDecl(numtype, *var, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 82:

/* Line 677 of lalr1.cc  */
#line 643 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Reserved keyword: adjustment");
        }
    break;

  case 87:

/* Line 677 of lalr1.cc  */
#line 659 "../../src-common/cfdg.ypp"
    { driver.isFunction = true; }
    break;

  case 88:

/* Line 677 of lalr1.cc  */
#line 660 "../../src-common/cfdg.ypp"
    { driver.isFunction = true; }
    break;

  case 89:

/* Line 677 of lalr1.cc  */
#line 661 "../../src-common/cfdg.ypp"
    { driver.isFunction = false; }
    break;

  case 90:

/* Line 677 of lalr1.cc  */
#line 665 "../../src-common/cfdg.ypp"
    { driver.isFunction = true; }
    break;

  case 91:

/* Line 677 of lalr1.cc  */
#line 666 "../../src-common/cfdg.ypp"
    { driver.isFunction = true; }
    break;

  case 92:

/* Line 677 of lalr1.cc  */
#line 670 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(3) - (2)].expression);}
    break;

  case 93:

/* Line 677 of lalr1.cc  */
#line 671 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTexpression((yyloc)); }
    break;

  case 94:

/* Line 677 of lalr1.cc  */
#line 672 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 95:

/* Line 677 of lalr1.cc  */
#line 673 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 96:

/* Line 677 of lalr1.cc  */
#line 677 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 1)
                assert ((yysemantic_stack_[(2) - (2)].component) == 0);
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 98:

/* Line 677 of lalr1.cc  */
#line 686 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 100:

/* Line 677 of lalr1.cc  */
#line 693 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(4) - (3)].mod));
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = new ASTpathOp(*pop, mod, (yyloc));
        }
    break;

  case 101:

/* Line 677 of lalr1.cc  */
#line 700 "../../src-common/cfdg.ypp"
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
#line 710 "../../src-common/cfdg.ypp"
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
#line 719 "../../src-common/cfdg.ypp"
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
#line 728 "../../src-common/cfdg.ypp"
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
#line 740 "../../src-common/cfdg.ypp"
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
#line 754 "../../src-common/cfdg.ypp"
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
#line 768 "../../src-common/cfdg.ypp"
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
#line 782 "../../src-common/cfdg.ypp"
    { }
    break;

  case 109:

/* Line 677 of lalr1.cc  */
#line 784 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 1)
                assert((yysemantic_stack_[(1) - (1)].component) == 0);
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 110:

/* Line 677 of lalr1.cc  */
#line 792 "../../src-common/cfdg.ypp"
    { }
    break;

  case 111:

/* Line 677 of lalr1.cc  */
#line 794 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 112:

/* Line 677 of lalr1.cc  */
#line 800 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer(driver.switchStack.top());
        }
    break;

  case 115:

/* Line 677 of lalr1.cc  */
#line 812 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(1) - (1)].component); 
        }
    break;

  case 116:

/* Line 677 of lalr1.cc  */
#line 816 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = 0; 
        }
    break;

  case 117:

/* Line 677 of lalr1.cc  */
#line 820 "../../src-common/cfdg.ypp"
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
#line 831 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
                driver.push_repContainer((yysemantic_stack_[(2) - (1)].loopObj)->mFinallyBody);
            }
        }
    break;

  case 119:

/* Line 677 of lalr1.cc  */
#line 836 "../../src-common/cfdg.ypp"
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
#line 849 "../../src-common/cfdg.ypp"
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
#line 860 "../../src-common/cfdg.ypp"
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
#line 871 "../../src-common/cfdg.ypp"
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
#line 883 "../../src-common/cfdg.ypp"
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
#line 891 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 125:

/* Line 677 of lalr1.cc  */
#line 898 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 126:

/* Line 677 of lalr1.cc  */
#line 899 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 127:

/* Line 677 of lalr1.cc  */
#line 900 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 128:

/* Line 677 of lalr1.cc  */
#line 904 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 129:

/* Line 677 of lalr1.cc  */
#line 906 "../../src-common/cfdg.ypp"
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
#line 914 "../../src-common/cfdg.ypp"
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
#line 926 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 132:

/* Line 677 of lalr1.cc  */
#line 927 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 135:

/* Line 677 of lalr1.cc  */
#line 930 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 140:

/* Line 677 of lalr1.cc  */
#line 938 "../../src-common/cfdg.ypp"
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
#line 949 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 143:

/* Line 677 of lalr1.cc  */
#line 956 "../../src-common/cfdg.ypp"
    { }
    break;

  case 144:

/* Line 677 of lalr1.cc  */
#line 958 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 145:

/* Line 677 of lalr1.cc  */
#line 964 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), (yylocation_stack_[(2) - (1)])));
            (yyval.component) = new ASTreplacement(*r, r->entropyVal, mod, (yyloc));
        }
    break;

  case 146:

/* Line 677 of lalr1.cc  */
#line 973 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 147:

/* Line 677 of lalr1.cc  */
#line 975 "../../src-common/cfdg.ypp"
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
#line 986 "../../src-common/cfdg.ypp"
    { ++driver.mLocalStackDepth; }
    break;

  case 149:

/* Line 677 of lalr1.cc  */
#line 986 "../../src-common/cfdg.ypp"
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
#line 1001 "../../src-common/cfdg.ypp"
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
#line 1015 "../../src-common/cfdg.ypp"
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
#line 1029 "../../src-common/cfdg.ypp"
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
#line 1044 "../../src-common/cfdg.ypp"
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
#line 1057 "../../src-common/cfdg.ypp"
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
#line 1067 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (1)].modToken) != ASTmodTerm::transform)
                error((yylocation_stack_[(2) - (1)]), "Syntax error");
            if (driver.mCompilePhase == 2) {
                ASTtransform* trans = new ASTtransform((yyloc));
                if ((yysemantic_stack_[(2) - (2)].modList)->empty()) {
                    trans->mModifications.push_back(new ASTmodification((yyloc)));
                } else {
                    trans->mModifications.swap(*(yysemantic_stack_[(2) - (2)].modList));
                }
                driver.push_repContainer(trans->mBody);
                (yyval.component) = trans;
            } else {
                (yyval.component) = 0;
            }
            ASTtransform::ClearMods(*(yysemantic_stack_[(2) - (2)].modList));   // should be empty, unless error or pass 1
            delete (yysemantic_stack_[(2) - (2)].modList);
        }
    break;

  case 156:

/* Line 677 of lalr1.cc  */
#line 1085 "../../src-common/cfdg.ypp"
    {
            if (!ASTparameter::Impure)
                error((yylocation_stack_[(2) - (1)]), "shape cloning only permitted in impure mode");
            if (driver.mCompilePhase == 2) {
                ASTtransform* trans = new ASTtransform((yyloc));
                trans->mClone = true;
                if ((yysemantic_stack_[(2) - (2)].modList)->empty()) {
                    trans->mModifications.push_back(new ASTmodification((yyloc)));
                } else {
                    trans->mModifications.swap(*(yysemantic_stack_[(2) - (2)].modList));
                }
                driver.push_repContainer(trans->mBody);
                (yyval.component) = trans;
            } else {
                (yyval.component) = 0;
            }
            ASTtransform::ClearMods(*(yysemantic_stack_[(2) - (2)].modList));   // should be empty, unless error or pass 1
            delete (yysemantic_stack_[(2) - (2)].modList);
        }
    break;

  case 157:

/* Line 677 of lalr1.cc  */
#line 1107 "../../src-common/cfdg.ypp"
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
#line 1120 "../../src-common/cfdg.ypp"
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
#line 1149 "../../src-common/cfdg.ypp"
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
#line 1162 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), true);
        }
    break;

  case 161:

/* Line 677 of lalr1.cc  */
#line 1167 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), false);
        }
    break;

  case 162:

/* Line 677 of lalr1.cc  */
#line 1174 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), true);
        }
    break;

  case 163:

/* Line 677 of lalr1.cc  */
#line 1179 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(5) - (3)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), false);
        }
    break;

  case 164:

/* Line 677 of lalr1.cc  */
#line 1186 "../../src-common/cfdg.ypp"
    {
            (yysemantic_stack_[(2) - (1)].modList)->push_back((yysemantic_stack_[(2) - (2)].mod));
            (yyval.modList) = (yysemantic_stack_[(2) - (1)].modList);
        }
    break;

  case 165:

/* Line 677 of lalr1.cc  */
#line 1190 "../../src-common/cfdg.ypp"
    {
            (yyval.modList) = new ASTtransform::ModList();
        }
    break;

  case 166:

/* Line 677 of lalr1.cc  */
#line 1195 "../../src-common/cfdg.ypp"
    {
            term_ptr mod((yysemantic_stack_[(2) - (2)].term));
            driver.MakeModTerm((yysemantic_stack_[(2) - (1)].mod)->modExp, mod);
            (yyval.mod) = (yysemantic_stack_[(2) - (1)].mod);
        }
    break;

  case 167:

/* Line 677 of lalr1.cc  */
#line 1200 "../../src-common/cfdg.ypp"
    {
            static const yy::location def;
            ASTmodification* m = new ASTmodification(def);
            m->flags = 0;
            (yyval.mod) = m;
        }
    break;

  case 168:

/* Line 677 of lalr1.cc  */
#line 1209 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].expression));
            (yyval.term) = new ASTmodTerm((ASTmodTerm::modTypeEnum)((yysemantic_stack_[(2) - (1)].modToken)), mod.release(), (yyloc));
        }
    break;

  case 169:

/* Line 677 of lalr1.cc  */
#line 1214 "../../src-common/cfdg.ypp"
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

  case 170:

/* Line 677 of lalr1.cc  */
#line 1224 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.term) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 171:

/* Line 677 of lalr1.cc  */
#line 1229 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.term) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 172:

/* Line 677 of lalr1.cc  */
#line 1236 "../../src-common/cfdg.ypp"
    {
            ASTrepContainer* tempHolder = new ASTrepContainer();
            driver.push_repContainer(*tempHolder);
            driver.isFunction = false;
            (yyval.bodyObj) = tempHolder;
        }
    break;

  case 173:

/* Line 677 of lalr1.cc  */
#line 1245 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = (yysemantic_stack_[(5) - (4)].expression);
        }
    break;

  case 176:

/* Line 677 of lalr1.cc  */
#line 1257 "../../src-common/cfdg.ypp"
    {
            str_ptr var((yysemantic_stack_[(3) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(3) - (3)].expression));
            driver.NextParameter(*var, exp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]));
        }
    break;

  case 177:

/* Line 677 of lalr1.cc  */
#line 1263 "../../src-common/cfdg.ypp"
    {
            exp_ptr exp((yysemantic_stack_[(3) - (3)].expression));
            error((yylocation_stack_[(3) - (1)]), "Reserved keyword: adjustment");
        }
    break;

  case 178:

/* Line 677 of lalr1.cc  */
#line 1270 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTexpression::Append((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 179:

/* Line 677 of lalr1.cc  */
#line 1274 "../../src-common/cfdg.ypp"
    { 
            (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); 
        }
    break;

  case 180:

/* Line 677 of lalr1.cc  */
#line 1280 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 181:

/* Line 677 of lalr1.cc  */
#line 1282 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 182:

/* Line 677 of lalr1.cc  */
#line 1284 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 183:

/* Line 677 of lalr1.cc  */
#line 1286 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 184:

/* Line 677 of lalr1.cc  */
#line 1288 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 185:

/* Line 677 of lalr1.cc  */
#line 1290 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 186:

/* Line 677 of lalr1.cc  */
#line 1292 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 187:

/* Line 677 of lalr1.cc  */
#line 1297 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 188:

/* Line 677 of lalr1.cc  */
#line 1304 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 189:

/* Line 677 of lalr1.cc  */
#line 1306 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 190:

/* Line 677 of lalr1.cc  */
#line 1308 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 191:

/* Line 677 of lalr1.cc  */
#line 1310 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 192:

/* Line 677 of lalr1.cc  */
#line 1315 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair((yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (1)]), (yyloc));
        }
    break;

  case 193:

/* Line 677 of lalr1.cc  */
#line 1320 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(3) - (1)].expression)->append((yysemantic_stack_[(3) - (3)].expression));   }
    break;

  case 194:

/* Line 677 of lalr1.cc  */
#line 1322 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('+', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 195:

/* Line 677 of lalr1.cc  */
#line 1324 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('-', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 196:

/* Line 677 of lalr1.cc  */
#line 1326 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('_', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 197:

/* Line 677 of lalr1.cc  */
#line 1328 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('*', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 198:

/* Line 677 of lalr1.cc  */
#line 1330 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('/', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 199:

/* Line 677 of lalr1.cc  */
#line 1332 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 200:

/* Line 677 of lalr1.cc  */
#line 1334 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 201:

/* Line 677 of lalr1.cc  */
#line 1336 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('!', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 202:

/* Line 677 of lalr1.cc  */
#line 1338 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('^', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 203:

/* Line 677 of lalr1.cc  */
#line 1340 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('<', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 204:

/* Line 677 of lalr1.cc  */
#line 1342 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('L', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 205:

/* Line 677 of lalr1.cc  */
#line 1344 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('>', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 206:

/* Line 677 of lalr1.cc  */
#line 1346 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('G', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 207:

/* Line 677 of lalr1.cc  */
#line 1348 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('=', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 208:

/* Line 677 of lalr1.cc  */
#line 1350 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('n', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 209:

/* Line 677 of lalr1.cc  */
#line 1352 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('&', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 210:

/* Line 677 of lalr1.cc  */
#line 1354 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('|', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 211:

/* Line 677 of lalr1.cc  */
#line 1356 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('X', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 212:

/* Line 677 of lalr1.cc  */
#line 1358 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 213:

/* Line 677 of lalr1.cc  */
#line 1360 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].mod); }
    break;

  case 214:

/* Line 677 of lalr1.cc  */
#line 1364 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 215:

/* Line 677 of lalr1.cc  */
#line 1369 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), true);
        }
    break;

  case 216:

/* Line 677 of lalr1.cc  */
#line 1375 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeArray(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]));
        }
    break;

  case 217:

/* Line 677 of lalr1.cc  */
#line 1381 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 218:

/* Line 677 of lalr1.cc  */
#line 1387 "../../src-common/cfdg.ypp"
    {
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            std::auto_ptr<ASTrepContainer> vars((yysemantic_stack_[(2) - (1)].bodyObj));
            (yyval.expression) = driver.MakeLet((yylocation_stack_[(2) - (1)]), exp);
        }
    break;

  case 219:

/* Line 677 of lalr1.cc  */
#line 1393 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 220:

/* Line 677 of lalr1.cc  */
#line 1400 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 221:

/* Line 677 of lalr1.cc  */
#line 1405 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 222:

/* Line 677 of lalr1.cc  */
#line 1411 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeArray(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]));
        }
    break;

  case 223:

/* Line 677 of lalr1.cc  */
#line 1417 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 224:

/* Line 677 of lalr1.cc  */
#line 1423 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args(new ASTexpression((yylocation_stack_[(4) - (1)]) + (yylocation_stack_[(4) - (4)])));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 225:

/* Line 677 of lalr1.cc  */
#line 1429 "../../src-common/cfdg.ypp"
    {
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            std::auto_ptr<ASTrepContainer> vars((yysemantic_stack_[(2) - (1)].bodyObj));
            (yyval.expression) = driver.MakeLet((yylocation_stack_[(2) - (1)]), exp);
        }
    break;

  case 226:

/* Line 677 of lalr1.cc  */
#line 1435 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 227:

/* Line 677 of lalr1.cc  */
#line 1442 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 228:

/* Line 677 of lalr1.cc  */
#line 1444 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(1) - (1)].string); }
    break;



/* Line 677 of lalr1.cc  */
#line 2986 "cfdg.tab.cpp"
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
  const short int CfdgParser::yypact_ninf_ = -275;
  const short int
  CfdgParser::yypact_[] =
  {
       191,  -275,  -275,    51,  1080,  1101,  -275,   197,  -275,    34,
      77,    49,   160,  -275,    87,   200,  -275,   160,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,    61,  -275,    74,  -275,
     201,   123,   227,   133,   209,   160,   132,   200,   152,   160,
    -275,  -275,  -275,  -275,  -275,  -275,   129,   120,  -275,  -275,
    -275,   128,   141,  -275,  -275,   182,   186,   221,   196,  -275,
    -275,  -275,  -275,  -275,  -275,   203,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,   204,   217,   225,  -275,   229,    30,   278,
    -275,  -275,   231,   232,   281,  -275,   266,   200,  -275,   239,
    -275,   241,  -275,   242,   129,  -275,   129,   129,   129,   247,
    -275,   255,   945,  -275,  -275,   108,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,   109,    -1,  -275,   172,   296,   321,   217,
    -275,    31,  -275,   290,   156,  -275,    83,  -275,    92,  -275,
    -275,   -29,  -275,   304,    31,   307,  -275,  -275,  -275,   129,
     350,   129,   261,   261,   261,   604,  -275,   111,   159,  -275,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   205,   448,
     262,   263,  -275,   316,    20,   277,  -275,   -16,  -275,   129,
    -275,  -275,  -275,  -275,   324,   217,   399,   399,   399,   258,
     255,   204,   135,   207,   490,   142,  -275,  -275,  -275,  -275,
     284,  -275,  -275,  -275,   106,   160,  -275,  -275,  -275,  -275,
     328,     4,   216,  -275,  -275,  -275,  -275,   309,   160,   279,
    -275,   635,  -275,  -275,   -28,  -275,    -5,  -275,  -275,  -275,
    -275,   156,  -275,  -275,    75,  -275,   666,   280,  -275,   697,
     511,  -275,   121,  -275,   331,   334,   286,  -275,   335,   335,
     480,   480,   480,   480,  1041,  1041,  1021,   999,   976,   945,
     151,   151,   151,   261,   261,   261,   204,   336,    37,   945,
     129,   129,   217,  -275,   217,  -275,  -275,  -275,   393,  -275,
     945,  -275,   399,  -275,   337,  -275,  -275,  -275,  -275,   217,
     217,  -275,  -275,   298,   299,  -275,   289,  -275,   490,   490,
     129,   255,   490,    90,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,   293,  -275,  -275,
    -275,  -275,  -275,  -275,   345,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,   301,   129,   129,   469,   217,   129,   129,   728,
     759,  -275,  -275,   790,   399,  -275,   267,  -275,    27,  -275,
    -275,   129,   427,   129,  -275,  -275,   821,  -275,   235,   490,
     490,  -275,   160,   211,   145,   297,  -275,   945,   945,    38,
    -275,   852,  -275,   945,   945,   217,  -275,  -275,  -275,  -275,
     300,   129,  -275,  -275,   399,   883,  -275,   914,   542,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,   573,
    -275,  -275,  -275,  -275,  -275
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
     167,   167,    54,    52,    26,     0,    28,    44,    45,    41,
      53,   142,    99,    95,     0,    86,    71,    86,     0,     0,
      38,    36,    89,     0,     0,    39,     0,     0,    37,     0,
     172,   226,   188,     0,     0,   189,     0,     0,     0,   167,
     213,     0,    55,   190,    65,     0,    97,    97,    33,    34,
      35,    68,    32,     0,     0,    29,     0,     0,     0,    50,
      49,     0,    64,     0,     0,    72,     0,    82,    81,    88,
      84,     0,    58,     0,     0,     0,    57,    46,    42,     0,
       0,     0,   201,   199,   200,     0,   167,     0,     0,   225,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   165,   165,   227,     0,   228,     0,    66,     0,
     116,   115,    96,   124,   117,     0,     0,     0,     0,     0,
       0,    95,     0,     0,     0,     0,   161,   166,   160,   227,
       0,    69,   146,   141,     0,     0,   133,   134,   137,   139,
     138,   227,     0,    76,   128,    98,   130,     0,     0,     0,
      94,     0,    48,    91,     0,    56,     0,    80,    78,    79,
      77,     0,    87,    60,     0,    59,     0,     0,   220,     0,
       0,   212,     0,   162,     0,     0,     0,   175,   191,   192,
     204,   203,   206,   205,   207,   208,   209,   210,   211,   193,
     195,   194,   196,   197,   198,   202,    95,     0,   226,   152,
       0,     0,   156,    62,   155,    61,   126,   125,     0,   127,
      63,   118,     0,    97,   120,   109,   121,   122,   113,     0,
       0,    73,    74,     0,   219,   180,     0,   181,     0,     0,
       0,     0,   168,   179,   183,   170,   171,   148,   142,   147,
     144,   145,   136,   135,   132,   131,   167,     0,    99,   111,
     129,   101,    93,    92,    85,    85,    83,    90,   223,   224,
     221,   222,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   164,   103,     0,     0,   140,     0,   154,     0,   106,
     104,     0,     0,     0,   184,   185,     0,   218,   178,     0,
       0,   169,     0,     0,     0,     0,   163,   177,   176,   226,
     174,     0,   107,   151,   150,   153,   157,   102,   119,   108,
       0,     0,   123,   112,     0,     0,   214,     0,     0,   182,
     186,   187,   149,   143,   100,   110,   173,   105,   159,     0,
     114,   217,   215,   216,   158
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yypgoto_[] =
  {
      -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
     356,     1,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,   357,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,   136,   -95,   305,    19,   291,  -183,   -91,
      55,   158,  -275,  -175,  -275,  -275,  -275,  -102,  -275,  -275,
    -275,  -275,  -275,    69,  -275,   179,  -275,  -113,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,   -12,   -73,   218,   -59,  -275,
     -88,  -184,  -275,    58,  -275,  -274,   -87,  -275,  -275,   -84
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yydefgoto_[] =
  {
        -1,     3,     4,     5,    40,    18,    19,    41,    20,    42,
      21,    69,    87,    44,    22,    23,    24,    25,    45,    46,
     179,   180,    47,    48,    49,    26,    27,    51,    52,    53,
      54,    28,    29,   130,   131,   122,    79,   123,   119,   105,
     117,   214,   181,   284,   320,   348,   383,   285,   344,   183,
     215,   216,   184,   116,   309,   202,   203,   204,   362,   185,
     186,   187,   188,   189,   384,    62,   100,   272,   113,   197,
     101,   149,   246,   247,   302,   303,   102,   304,   103,   191
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char CfdgParser::yytable_ninf_ = -91;
  const short int
  CfdgParser::yytable_[] =
  {
        63,   120,   114,   182,   217,    70,   289,   142,   290,   143,
     144,   145,   286,   287,   313,   192,   193,   190,   194,   195,
     231,   231,    80,    81,   354,   355,   224,    88,   358,   226,
     275,   221,   205,   218,   232,   324,   126,   126,    85,   234,
     147,   380,   278,   381,   231,   279,   222,   338,   334,   127,
     127,     6,   236,   239,   240,    84,   128,   128,   325,    59,
      57,   198,   314,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   276,   269,   336,   266,   390,   391,   242,   138,   382,
     182,   182,   280,   129,   223,   140,   140,    64,   190,   190,
     190,   133,   227,    58,   190,   190,   301,   345,    60,   228,
      61,   229,   282,    65,   359,   360,   168,   357,   230,   169,
     205,   170,    71,   171,   231,   172,    90,   173,   194,   195,
     194,   195,   199,   218,   174,    72,   175,   176,   327,   176,
     194,   195,    89,   168,   177,    66,   169,    90,   170,    75,
     171,    82,   172,    90,   173,    91,   361,    92,    83,    77,
      93,   174,   126,   175,   194,   195,   176,   308,   305,   378,
     178,   177,   306,    94,   196,   127,   243,    95,   244,    96,
      97,   104,   128,   339,   340,   245,   332,    98,    99,   106,
      78,   343,   346,   311,   190,     1,     2,   291,   199,   341,
     200,   341,   107,   176,   165,   166,   321,   394,   167,   400,
     301,   301,    86,   356,   301,   168,   349,   350,   169,    60,
     170,    61,   171,    55,   172,    90,   173,    73,    56,    67,
      68,   199,    74,   174,   201,   175,   176,   199,   176,   200,
     108,   109,   176,   177,   182,   110,   367,   368,   371,   111,
     373,   374,   217,    57,   112,    76,   190,   364,   190,   359,
     360,   115,   118,   372,   385,   387,   388,    78,    60,   292,
      61,   301,   301,   393,   315,   168,    99,   316,   169,   205,
     170,   218,   171,   121,   172,    90,   173,   124,   132,    78,
     134,   136,   137,   174,   399,   175,   190,   139,   176,   140,
     225,   141,   397,   177,   206,   206,   146,   207,   207,   208,
     208,   209,   209,   148,   233,   210,   210,   235,   167,   288,
     270,   271,   211,   211,   200,   200,   273,   176,   176,   379,
     277,   219,   212,   212,    89,   199,   281,   307,   312,    90,
     176,   333,   322,   329,   334,   317,   337,    91,   353,    92,
     392,   347,    93,   335,   316,   -90,   351,   352,   213,   395,
     237,    43,    50,    89,   398,    94,   366,   326,    90,    95,
     318,    96,    97,   365,   135,   319,    91,   363,    92,    98,
      99,    93,   125,   310,   220,   162,   163,   164,   165,   166,
       0,   274,   167,   370,    94,     0,     0,     0,    95,     0,
      96,    97,     0,     0,     0,     0,    89,   168,    98,    99,
     169,    90,   170,   238,   171,     0,   172,    90,   173,    91,
       0,    92,     0,     0,    93,   174,     0,   175,     0,     0,
     176,     0,     0,     0,     0,   177,     0,    94,     0,     0,
      89,    95,     0,    96,    97,    90,     0,     0,     0,     0,
       0,    98,    99,    91,     0,    92,   342,     0,    93,     0,
     283,    89,     0,     0,     0,     0,    90,   267,     0,     0,
       0,    94,     0,     0,   268,    95,    92,    96,    97,    93,
       0,     0,    89,     0,     0,    98,    99,    90,   244,     0,
     386,     0,    94,     0,     0,   369,    95,    92,    96,    97,
      93,     0,     0,   293,   150,   151,    98,    99,    90,     0,
       0,     0,     0,    94,     0,     0,   294,    95,   295,    96,
      97,   296,     0,     0,     0,     0,     0,    98,    99,     0,
     162,   163,   164,   165,   166,   150,   151,   167,   297,     0,
     298,   299,     0,     0,     0,     0,     0,     0,   300,   152,
     153,   154,   155,   156,   157,     0,   158,   159,   160,     0,
     161,   162,   163,   164,   165,   166,   150,   151,   167,     0,
       0,     0,     0,     0,     0,     0,   331,     0,     0,     0,
     152,   153,   154,   155,   156,   157,     0,   158,   159,   160,
       0,   161,   162,   163,   164,   165,   166,   150,   151,   167,
       0,     0,     0,     0,     0,     0,     0,   403,     0,     0,
       0,   152,   153,   154,   155,   156,   157,     0,   158,   159,
     160,     0,   161,   162,   163,   164,   165,   166,   150,   151,
     167,     0,     0,     0,     0,     0,     0,   404,     0,     0,
       0,     0,   152,   153,   154,   155,   156,   157,     0,   158,
     159,   160,     0,   161,   162,   163,   164,   165,   166,   150,
     151,   167,     0,     0,     0,     0,     0,   241,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,     0,
     158,   159,   160,     0,   161,   162,   163,   164,   165,   166,
     150,   151,   167,     0,     0,     0,     0,     0,   323,     0,
       0,     0,     0,     0,   152,   153,   154,   155,   156,   157,
       0,   158,   159,   160,     0,   161,   162,   163,   164,   165,
     166,   150,   151,   167,     0,     0,     0,     0,     0,   328,
       0,     0,     0,     0,     0,   152,   153,   154,   155,   156,
     157,     0,   158,   159,   160,     0,   161,   162,   163,   164,
     165,   166,   150,   151,   167,     0,     0,     0,     0,     0,
     330,     0,     0,     0,     0,     0,   152,   153,   154,   155,
     156,   157,     0,   158,   159,   160,     0,   161,   162,   163,
     164,   165,   166,   150,   151,   167,     0,     0,     0,     0,
       0,   375,     0,     0,     0,     0,     0,   152,   153,   154,
     155,   156,   157,     0,   158,   159,   160,     0,   161,   162,
     163,   164,   165,   166,   150,   151,   167,     0,     0,     0,
       0,     0,   376,     0,     0,     0,     0,     0,   152,   153,
     154,   155,   156,   157,     0,   158,   159,   160,     0,   161,
     162,   163,   164,   165,   166,   150,   151,   167,     0,     0,
       0,     0,     0,   377,     0,     0,     0,     0,     0,   152,
     153,   154,   155,   156,   157,     0,   158,   159,   160,     0,
     161,   162,   163,   164,   165,   166,   150,   151,   167,     0,
       0,     0,     0,     0,   389,     0,     0,     0,     0,     0,
     152,   153,   154,   155,   156,   157,     0,   158,   159,   160,
       0,   161,   162,   163,   164,   165,   166,   150,   151,   167,
       0,     0,     0,     0,     0,   396,     0,     0,     0,     0,
       0,   152,   153,   154,   155,   156,   157,     0,   158,   159,
     160,     0,   161,   162,   163,   164,   165,   166,   150,   151,
     167,     0,     0,     0,     0,     0,   401,     0,     0,     0,
       0,     0,   152,   153,   154,   155,   156,   157,     0,   158,
     159,   160,     0,   161,   162,   163,   164,   165,   166,   150,
     151,   167,     0,     0,     0,     0,     0,   402,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,     0,
     158,   159,   160,     0,   161,   162,   163,   164,   165,   166,
     150,   151,   167,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   152,   153,   154,   155,   156,   157,
       0,   158,   159,   150,   151,     0,   162,   163,   164,   165,
     166,     0,     0,   167,     0,     0,     0,   152,   153,   154,
     155,   156,   157,     0,   158,   150,   151,     0,     0,   162,
     163,   164,   165,   166,     0,     0,   167,     0,     0,   152,
     153,   154,   155,   156,   157,   150,   151,     0,     0,     0,
       0,   162,   163,   164,   165,   166,     0,     0,   167,   152,
     153,   154,   155,     7,     0,     0,     8,     9,    10,     0,
       0,   162,   163,   164,   165,   166,     0,     0,   167,    11,
       0,    12,     0,    13,    30,     0,    14,    31,    32,    33,
       0,     0,    15,    16,    17,     0,     0,     0,     0,     0,
      34,     0,    35,     0,    13,     0,     0,    36,     0,     0,
       0,     0,     0,    37,    38,    39
  };

  /* YYCHECK.  */
  const short int
  CfdgParser::yycheck_[] =
  {
        12,    74,    61,   105,   117,    17,   190,    94,   191,    96,
      97,    98,   187,   188,    10,   106,   107,   105,    19,    20,
      49,    49,    34,    35,   298,   299,   121,    39,   302,   124,
      10,   118,   116,   117,    63,    63,     6,     6,    37,   134,
      99,    14,    58,    16,    49,    61,   119,    10,    10,    19,
      19,     0,   139,   140,   141,    36,    26,    26,    63,    10,
      26,    62,    58,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,    61,   169,   266,   168,   359,   360,   146,    87,    62,
     192,   193,   179,    63,    63,    58,    58,    10,   186,   187,
     188,    82,    19,    26,   192,   193,   194,   282,    59,    26,
      61,    19,   185,    26,    24,    25,     8,   301,    26,    11,
     204,    13,    61,    15,    49,    17,    18,    19,    19,    20,
      19,    20,    26,   217,    26,    61,    28,    31,    63,    31,
      19,    20,    13,     8,    36,    58,    11,    18,    13,    26,
      15,    19,    17,    18,    19,    26,    66,    28,    26,    26,
      31,    26,     6,    28,    19,    20,    31,    61,    26,   344,
      62,    36,    30,    44,    65,    19,    65,    48,    19,    50,
      51,    61,    26,   270,   271,    26,    65,    58,    59,    61,
      58,   278,   283,   205,   282,     4,     5,    62,    26,   272,
      28,   274,    61,    31,    53,    54,   218,    62,    57,   384,
     298,   299,    60,   300,   302,     8,   289,   290,    11,    59,
      13,    61,    15,    26,    17,    18,    19,    26,    31,    29,
      30,    26,    31,    26,    62,    28,    31,    26,    31,    28,
      58,    59,    31,    36,   346,    59,   333,   334,   335,    28,
     337,   338,   365,    26,    58,    28,   344,   316,   346,    24,
      25,    58,    58,   336,   351,   352,   353,    58,    59,    62,
      61,   359,   360,    62,    58,     8,    59,    61,    11,   363,
      13,   365,    15,    58,    17,    18,    19,    58,    10,    58,
      58,    10,    26,    26,   381,    28,   384,    58,    31,    58,
      10,    59,   375,    36,     8,     8,    59,    11,    11,    13,
      13,    15,    15,    58,    10,    19,    19,    10,    57,    61,
      58,    58,    26,    26,    28,    28,    10,    31,    31,    62,
      53,    10,    36,    36,    13,    26,    12,    53,    10,    18,
      31,    10,    63,    63,    10,    36,    10,    26,    59,    28,
     362,    14,    31,    67,    61,    10,    58,    58,    62,    62,
      10,     5,     5,    13,    64,    44,    65,   231,    18,    48,
      61,    50,    51,   318,    83,   217,    26,   308,    28,    58,
      59,    31,    77,   204,    63,    50,    51,    52,    53,    54,
      -1,   173,    57,   335,    44,    -1,    -1,    -1,    48,    -1,
      50,    51,    -1,    -1,    -1,    -1,    13,     8,    58,    59,
      11,    18,    13,    63,    15,    -1,    17,    18,    19,    26,
      -1,    28,    -1,    -1,    31,    26,    -1,    28,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    36,    -1,    44,    -1,    -1,
      13,    48,    -1,    50,    51,    18,    -1,    -1,    -1,    -1,
      -1,    58,    59,    26,    -1,    28,    63,    -1,    31,    -1,
      61,    13,    -1,    -1,    -1,    -1,    18,    19,    -1,    -1,
      -1,    44,    -1,    -1,    26,    48,    28,    50,    51,    31,
      -1,    -1,    13,    -1,    -1,    58,    59,    18,    19,    -1,
      63,    -1,    44,    -1,    -1,    26,    48,    28,    50,    51,
      31,    -1,    -1,    13,    24,    25,    58,    59,    18,    -1,
      -1,    -1,    -1,    44,    -1,    -1,    26,    48,    28,    50,
      51,    31,    -1,    -1,    -1,    -1,    -1,    58,    59,    -1,
      50,    51,    52,    53,    54,    24,    25,    57,    48,    -1,
      50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    58,    38,
      39,    40,    41,    42,    43,    -1,    45,    46,    47,    -1,
      49,    50,    51,    52,    53,    54,    24,    25,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    -1,    45,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    24,    25,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    -1,    45,    46,
      47,    -1,    49,    50,    51,    52,    53,    54,    24,    25,
      57,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,
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
      57,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    -1,    45,
      46,    47,    -1,    49,    50,    51,    52,    53,    54,    24,
      25,    57,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    -1,
      45,    46,    47,    -1,    49,    50,    51,    52,    53,    54,
      24,    25,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      -1,    45,    46,    24,    25,    -1,    50,    51,    52,    53,
      54,    -1,    -1,    57,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    43,    -1,    45,    24,    25,    -1,    -1,    50,
      51,    52,    53,    54,    -1,    -1,    57,    -1,    -1,    38,
      39,    40,    41,    42,    43,    24,    25,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    -1,    -1,    57,    38,
      39,    40,    41,     3,    -1,    -1,     6,     7,     8,    -1,
      -1,    50,    51,    52,    53,    54,    -1,    -1,    57,    19,
      -1,    21,    -1,    23,     3,    -1,    26,     6,     7,     8,
      -1,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      19,    -1,    21,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    32,    33,    34
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
     134,   138,   144,   146,    61,   107,    61,    61,    58,    59,
      59,    28,    58,   136,   136,    58,   121,   108,    58,   106,
     134,    58,   103,   105,    58,   103,     6,    19,    26,    63,
     101,   102,    10,   104,    58,   105,    10,    26,    79,    58,
      58,    59,   144,   144,   144,   144,    59,   136,    58,   139,
      24,    25,    38,    39,    40,    41,    42,    43,    45,    46,
      47,    49,    50,    51,    52,    53,    54,    57,     8,    11,
      13,    15,    17,    19,    26,    28,    31,    36,    62,    88,
      89,   110,   115,   117,   120,   127,   128,   129,   130,   131,
     138,   147,   107,   107,    19,    20,    65,   137,    62,    26,
      28,    62,   123,   124,   125,   147,     8,    11,    13,    15,
      19,    26,    36,    62,   109,   118,   119,   125,   147,    10,
      63,   144,   134,    63,   102,    10,   102,    19,    26,    19,
      26,    49,    63,    10,   102,    10,   144,    10,    63,   144,
     144,    63,   136,    65,    19,    26,   140,   141,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   147,    19,    26,   144,
      58,    58,   135,    10,   135,    10,    61,    53,    58,    61,
     144,    12,   134,    61,   111,   115,   111,   111,    61,   139,
     106,    62,    62,    13,    26,    28,    31,    48,    50,    51,
      58,   138,   142,   143,   145,    26,    30,    53,    61,   122,
     123,   133,    10,    10,    58,    58,    61,    36,    61,   109,
     112,   133,    63,    63,    63,    63,   101,    63,    63,    63,
      63,    65,    65,    10,    10,    67,   106,    10,    10,   144,
     144,   134,    63,   144,   116,   111,   107,    14,   113,   134,
     134,    58,    58,    59,   143,   143,   144,   139,   143,    24,
      25,    66,   126,   121,   136,   108,    65,   144,   144,    26,
     141,   144,   134,   144,   144,    63,    63,    63,   111,    62,
      14,    16,    62,   114,   132,   144,    63,   144,   144,    63,
     143,   143,   133,    62,    62,    62,    63,   134,    64,   144,
     111,    63,    63,    65,    64
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
     133,   133,   134,   134,   135,   135,   136,   136,   137,   137,
     137,   137,   138,   139,   140,   140,   141,   141,   142,   142,
     143,   143,   143,   143,   143,   143,   143,   143,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   145,   145,   145,   145,   145,   145,
     146,   146,   146,   146,   146,   146,   146,   147,   147
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
       3,     3,     3,     5,     2,     0,     2,     0,     2,     3,
       2,     2,     1,     5,     3,     1,     3,     3,     2,     1,
       1,     1,     3,     1,     2,     2,     3,     3,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     4,     4,     4,     2,     1,
       3,     4,     4,     4,     4,     2,     1,     1,     1
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
  "caseHeader", "modification_v2", "modification", "buncha_mods",
  "buncha_adjustments", "adjustment", "letHeader", "letBody",
  "letVariables", "letVariable", "explist", "exp", "exp2", "expfunc",
  "exp2func", "shapeName", 0
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
     133,    -1,    87,   144,    -1,     6,    26,   105,    10,    -1,
      26,   104,    10,    -1,    19,   104,    10,    -1,    26,    26,
     105,    10,    -1,    26,    19,   104,    10,    -1,    26,    10,
      -1,    19,    10,    -1,    88,   144,    -1,     6,    26,   103,
      -1,    90,    61,    -1,    91,   107,    62,    -1,     7,    26,
      -1,     7,    26,    28,    -1,    93,    61,   121,    62,    -1,
       7,    -1,     7,    28,    -1,     8,    26,   103,    -1,    95,
      61,   107,    62,    -1,    96,    61,   107,    62,    -1,     8,
      26,    -1,    99,    61,   108,    62,    -1,    26,    26,    -1,
       6,    26,    -1,    26,    19,    -1,     6,    19,    -1,    26,
      -1,    19,    -1,   102,    49,   101,    -1,   101,    -1,    58,
     102,    63,    -1,    -1,    58,   102,    63,    -1,    58,    63,
      -1,    -1,    58,   102,    63,    -1,    58,    63,    -1,    58,
     144,    63,    -1,    58,    10,    63,    -1,    58,    63,    -1,
      -1,   107,   115,    -1,    -1,   108,   118,    -1,    -1,    36,
      61,   136,    62,    -1,   147,   133,    -1,    36,    58,   144,
      63,    -1,    36,    58,    63,    -1,   147,   106,   134,    -1,
      13,    58,   144,    63,   134,    -1,   138,   139,   134,    -1,
       8,   147,   106,   134,    -1,    61,   107,    62,    -1,   115,
      -1,    61,   108,    62,    -1,   109,    -1,   113,   114,    -1,
      -1,   132,   111,    -1,   110,    -1,    89,    -1,   120,    -1,
      -1,   120,    12,   116,   111,    -1,   128,   111,    -1,   129,
     111,    -1,   130,   111,    -1,   131,    61,   113,    62,    -1,
     117,    -1,    28,    53,    -1,    26,    61,    -1,    36,    61,
      -1,   109,    -1,   125,   112,    -1,   119,    -1,    36,    58,
      -1,    26,    58,    -1,     8,    -1,    11,    -1,    26,    10,
      -1,    19,    10,    -1,    13,    -1,    19,    -1,    15,    -1,
     127,   134,   111,    -1,   121,   124,    -1,    -1,    61,   121,
      62,    -1,   123,    -1,   147,   133,    -1,   123,    -1,   125,
     122,    -1,    -1,    28,    53,   126,   133,    -1,    11,    26,
      10,   144,    -1,    11,    19,    10,   144,    -1,    11,   144,
      -1,    13,    58,   144,    63,    -1,   128,   111,    14,    -1,
      19,   135,    -1,    17,   135,    -1,    15,    58,   144,    63,
      -1,    16,   144,    64,    -1,    14,    64,    -1,    61,   136,
      62,    -1,    59,   136,    65,    -1,    59,   136,    65,    -1,
      59,    59,   136,    65,    65,    -1,   135,   134,    -1,    -1,
     136,   137,    -1,    -1,    19,   142,    -1,    19,   143,    66,
      -1,    20,    26,    -1,    20,    30,    -1,    18,    -1,    58,
     140,    67,   144,    63,    -1,   140,    67,   141,    -1,   141,
      -1,    26,    10,   144,    -1,    19,    10,   144,    -1,   142,
     143,    -1,   143,    -1,    28,    -1,    48,    -1,    58,   144,
      63,    -1,   145,    -1,    50,   143,    -1,    51,   143,    -1,
     143,    24,   143,    -1,   143,    25,   143,    -1,    28,    -1,
      48,    -1,   146,    -1,   144,    24,   144,    -1,   144,    25,
     144,    -1,   144,    49,   144,    -1,   144,    51,   144,    -1,
     144,    50,   144,    -1,   144,    52,   144,    -1,   144,    53,
     144,    -1,   144,    54,   144,    -1,    50,   144,    -1,    51,
     144,    -1,    44,   144,    -1,   144,    57,   144,    -1,   144,
      39,   144,    -1,   144,    38,   144,    -1,   144,    41,   144,
      -1,   144,    40,   144,    -1,   144,    42,   144,    -1,   144,
      43,   144,    -1,   144,    45,   144,    -1,   144,    46,   144,
      -1,   144,    47,   144,    -1,    58,   144,    63,    -1,   134,
      -1,    26,    58,    63,    -1,    26,    58,   144,    63,    -1,
      31,    59,   144,    65,    -1,    13,    58,   144,    63,    -1,
     138,   139,    -1,    26,    -1,    26,    58,    63,    -1,    26,
      58,   144,    63,    -1,    31,    59,   144,    65,    -1,    13,
      58,   144,    63,    -1,    26,    58,    10,    63,    -1,   138,
     139,    -1,    26,    -1,    26,    -1,    31,    -1
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
     478,   482,   486,   490,   496,   499,   500,   503,   504,   507,
     511,   514,   517,   519,   525,   529,   531,   535,   539,   542,
     544,   546,   548,   552,   554,   557,   560,   564,   568,   570,
     572,   574,   578,   582,   586,   590,   594,   598,   602,   606,
     609,   612,   615,   619,   623,   627,   631,   635,   639,   643,
     647,   651,   655,   659,   661,   665,   670,   675,   680,   683,
     685,   689,   694,   699,   704,   709,   712,   714,   716
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  CfdgParser::yyrline_[] =
  {
         0,   192,   192,   192,   195,   200,   204,   209,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   261,   262,   263,   264,
     265,   269,   278,   289,   296,   296,   299,   300,   304,   317,
     329,   343,   354,   364,   374,   389,   398,   404,   410,   416,
     422,   431,   435,   443,   452,   468,   482,   491,   500,   515,
     523,   535,   552,   577,   586,   596,   609,   616,   622,   628,
     633,   637,   643,   649,   650,   654,   655,   659,   660,   661,
     665,   666,   670,   671,   672,   673,   677,   682,   686,   689,
     693,   700,   710,   719,   728,   740,   754,   768,   782,   784,
     792,   794,   800,   804,   808,   812,   816,   820,   831,   831,
     849,   860,   871,   882,   891,   898,   899,   900,   904,   906,
     914,   926,   927,   928,   929,   930,   931,   932,   933,   934,
     938,   949,   952,   956,   958,   964,   973,   975,   986,   986,
    1001,  1015,  1029,  1044,  1057,  1067,  1085,  1107,  1120,  1149,
    1162,  1167,  1174,  1179,  1186,  1190,  1195,  1200,  1209,  1214,
    1224,  1229,  1236,  1245,  1251,  1253,  1257,  1263,  1270,  1274,
    1280,  1282,  1284,  1286,  1288,  1290,  1292,  1297,  1304,  1306,
    1308,  1310,  1315,  1320,  1322,  1324,  1326,  1328,  1330,  1332,
    1334,  1336,  1338,  1340,  1342,  1344,  1346,  1348,  1350,  1352,
    1354,  1356,  1358,  1360,  1364,  1369,  1375,  1381,  1387,  1393,
    1400,  1405,  1411,  1417,  1423,  1429,  1435,  1442,  1444
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
  const int CfdgParser::yylast_ = 1135;
  const int CfdgParser::yynnts_ = 80;
  const int CfdgParser::yyempty_ = -2;
  const int CfdgParser::yyfinal_ = 6;
  const int CfdgParser::yyterror_ = 1;
  const int CfdgParser::yyerrcode_ = 256;
  const int CfdgParser::yyntokens_ = 68;

  const unsigned int CfdgParser::yyuser_token_number_max_ = 305;
  const CfdgParser::token_number_type CfdgParser::yyundef_token_ = 2;


} // yy

/* Line 1053 of lalr1.cc  */
#line 3947 "cfdg.tab.cpp"


/* Line 1055 of lalr1.cc  */
#line 1447 "../../src-common/cfdg.ypp"


void yy::CfdgParser::error(const CfdgParser::location_type& l, const std::string& m)
{
    driver.mWant2ndPass = false;
    driver.error(l, m);
}

