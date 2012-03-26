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
#line 174 "../../src-common/cfdg.ypp"

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
        case 25: /* "USER_STRING" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 263 "cfdg.tab.cpp"
	break;
      case 28: /* "USER_FILENAME" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 272 "cfdg.tab.cpp"
	break;
      case 29: /* "USER_QSTRING" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 281 "cfdg.tab.cpp"
	break;
      case 34: /* "USER_PATHOP" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 290 "cfdg.tab.cpp"
	break;
      case 69: /* "statement" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 299 "cfdg.tab.cpp"
	break;
      case 70: /* "statement_v2" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 308 "cfdg.tab.cpp"
	break;
      case 76: /* "fileString" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 317 "cfdg.tab.cpp"
	break;
      case 77: /* "fileNameSpace" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 326 "cfdg.tab.cpp"
	break;
      case 78: /* "initialization" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 335 "cfdg.tab.cpp"
	break;
      case 79: /* "initialization_v2" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 344 "cfdg.tab.cpp"
	break;
      case 80: /* "background" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 353 "cfdg.tab.cpp"
	break;
      case 81: /* "tile" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 362 "cfdg.tab.cpp"
	break;
      case 82: /* "size" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 371 "cfdg.tab.cpp"
	break;
      case 84: /* "global_definition_header" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 380 "cfdg.tab.cpp"
	break;
      case 85: /* "definition_header" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 389 "cfdg.tab.cpp"
	break;
      case 87: /* "shape" */

/* Line 479 of lalr1.cc  */
#line 171 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->shapeObj); };

/* Line 479 of lalr1.cc  */
#line 398 "cfdg.tab.cpp"
	break;
      case 88: /* "shape_singleton_header" */

/* Line 479 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 407 "cfdg.tab.cpp"
	break;
      case 89: /* "shape_singleton" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 416 "cfdg.tab.cpp"
	break;
      case 90: /* "rule_header_v2" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 425 "cfdg.tab.cpp"
	break;
      case 92: /* "rule_header" */

/* Line 479 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 434 "cfdg.tab.cpp"
	break;
      case 93: /* "path_header" */

/* Line 479 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 443 "cfdg.tab.cpp"
	break;
      case 94: /* "rule" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 452 "cfdg.tab.cpp"
	break;
      case 95: /* "path" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 461 "cfdg.tab.cpp"
	break;
      case 96: /* "path_header_v2" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 470 "cfdg.tab.cpp"
	break;
      case 104: /* "parameter_spec" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 479 "cfdg.tab.cpp"
	break;
      case 107: /* "pathOp_simple_v2" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 488 "cfdg.tab.cpp"
	break;
      case 108: /* "element_simple" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 497 "cfdg.tab.cpp"
	break;
      case 113: /* "element" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 506 "cfdg.tab.cpp"
	break;
      case 116: /* "pathOp_v2" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 515 "cfdg.tab.cpp"
	break;
      case 118: /* "element_loop" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 524 "cfdg.tab.cpp"
	break;
      case 121: /* "replacement_simple_v2" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 533 "cfdg.tab.cpp"
	break;
      case 122: /* "replacement_v2" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 542 "cfdg.tab.cpp"
	break;
      case 123: /* "loopHeader_v2" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 551 "cfdg.tab.cpp"
	break;
      case 125: /* "loopHeader" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 560 "cfdg.tab.cpp"
	break;
      case 126: /* "ifHeader" */

/* Line 479 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ifObj); };

/* Line 479 of lalr1.cc  */
#line 569 "cfdg.tab.cpp"
	break;
      case 127: /* "ifElseHeader" */

/* Line 479 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ifObj); };

/* Line 479 of lalr1.cc  */
#line 578 "cfdg.tab.cpp"
	break;
      case 128: /* "transHeader" */

/* Line 479 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 587 "cfdg.tab.cpp"
	break;
      case 129: /* "switchHeader" */

/* Line 479 of lalr1.cc  */
#line 170 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->switchObj); };

/* Line 479 of lalr1.cc  */
#line 596 "cfdg.tab.cpp"
	break;
      case 130: /* "caseHeader" */

/* Line 479 of lalr1.cc  */
#line 172 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); };

/* Line 479 of lalr1.cc  */
#line 605 "cfdg.tab.cpp"
	break;
      case 131: /* "modification_v2" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 614 "cfdg.tab.cpp"
	break;
      case 132: /* "modification" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 623 "cfdg.tab.cpp"
	break;
      case 133: /* "buncha_mods" */

/* Line 479 of lalr1.cc  */
#line 173 "../../src-common/cfdg.ypp"
	{ ASTtransform::ClearMods(*(yyvaluep->modList)); delete (yyvaluep->modList); };

/* Line 479 of lalr1.cc  */
#line 632 "cfdg.tab.cpp"
	break;
      case 134: /* "buncha_adjustments" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 641 "cfdg.tab.cpp"
	break;
      case 135: /* "adjustment" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->term); };

/* Line 479 of lalr1.cc  */
#line 650 "cfdg.tab.cpp"
	break;
      case 136: /* "explist" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 659 "cfdg.tab.cpp"
	break;
      case 137: /* "exp" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 668 "cfdg.tab.cpp"
	break;
      case 138: /* "exp2" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 677 "cfdg.tab.cpp"
	break;
      case 139: /* "expfunc" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 686 "cfdg.tab.cpp"
	break;
      case 140: /* "exp2func" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 695 "cfdg.tab.cpp"
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
#line 190 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 6:

/* Line 677 of lalr1.cc  */
#line 199 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 9:

/* Line 677 of lalr1.cc  */
#line 209 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 10:

/* Line 677 of lalr1.cc  */
#line 210 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 13:

/* Line 677 of lalr1.cc  */
#line 213 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].shapeObj); }
    break;

  case 15:

/* Line 677 of lalr1.cc  */
#line 215 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 16:

/* Line 677 of lalr1.cc  */
#line 216 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 19:

/* Line 677 of lalr1.cc  */
#line 225 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 20:

/* Line 677 of lalr1.cc  */
#line 226 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 25:

/* Line 677 of lalr1.cc  */
#line 231 "../../src-common/cfdg.ypp"
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
#line 243 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 27:

/* Line 677 of lalr1.cc  */
#line 244 "../../src-common/cfdg.ypp"
    {}
    break;

  case 28:

/* Line 677 of lalr1.cc  */
#line 245 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 31:

/* Line 677 of lalr1.cc  */
#line 248 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 32:

/* Line 677 of lalr1.cc  */
#line 249 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 33:

/* Line 677 of lalr1.cc  */
#line 250 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 34:

/* Line 677 of lalr1.cc  */
#line 254 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 35:

/* Line 677 of lalr1.cc  */
#line 255 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 36:

/* Line 677 of lalr1.cc  */
#line 256 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 37:

/* Line 677 of lalr1.cc  */
#line 257 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 38:

/* Line 677 of lalr1.cc  */
#line 258 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(1) - (1)].ruleObj); }
    break;

  case 39:

/* Line 677 of lalr1.cc  */
#line 262 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(2) - (2)].string));
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(NULL);
            driver.IncludeFile(*file);
        }
    break;

  case 40:

/* Line 677 of lalr1.cc  */
#line 271 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(3) - (3)].string));
            str_ptr nm((yysemantic_stack_[(3) - (2)].string));
            driver.SetShape(NULL);
            driver.IncludeFile(*file);
            if (nm.get())
                driver.PushNameSpace(nm, (yylocation_stack_[(3) - (2)]));
        }
    break;

  case 41:

/* Line 677 of lalr1.cc  */
#line 282 "../../src-common/cfdg.ypp"
    {
            if (driver.EndInclude())
                YYACCEPT;
        }
    break;

  case 44:

/* Line 677 of lalr1.cc  */
#line 292 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 45:

/* Line 677 of lalr1.cc  */
#line 293 "../../src-common/cfdg.ypp"
    { (yyval.string) = NULL; }
    break;

  case 46:

/* Line 677 of lalr1.cc  */
#line 297 "../../src-common/cfdg.ypp"
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

  case 47:

/* Line 677 of lalr1.cc  */
#line 310 "../../src-common/cfdg.ypp"
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

  case 48:

/* Line 677 of lalr1.cc  */
#line 324 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (2)].string));
            driver.SetShape(NULL);
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), (yylocation_stack_[(2) - (2)])));
            rep_ptr start(new ASTreplacement(*r, *name, mod_ptr(), (yyloc)));
            driver.Initialize(start);
            (yyval.component) = 0;
        }
    break;

  case 49:

/* Line 677 of lalr1.cc  */
#line 335 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            static const std::string backVar("CF::Background");
            driver.lexer->maybeVersion = token::CFDG2;
            driver.NextParameter(backVar, mod, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
            (yyval.component) = 0;
        }
    break;

  case 50:

/* Line 677 of lalr1.cc  */
#line 345 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            static const std::string tileVar("CF::Tile");
            driver.lexer->maybeVersion = token::CFDG2;
            driver.NextParameter(tileVar, mod, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
            (yyval.component) = 0;
        }
    break;

  case 51:

/* Line 677 of lalr1.cc  */
#line 355 "../../src-common/cfdg.ypp"
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

  case 52:

/* Line 677 of lalr1.cc  */
#line 370 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(2) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            if (var.get())
                driver.NextParameter(*var, exp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 53:

/* Line 677 of lalr1.cc  */
#line 379 "../../src-common/cfdg.ypp"
    {
            driver.push_paramDecls(*(yysemantic_stack_[(3) - (1)].string), (yyloc));
            (yyval.string) = (yysemantic_stack_[(3) - (1)].string);
        }
    break;

  case 54:

/* Line 677 of lalr1.cc  */
#line 383 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            error((yylocation_stack_[(3) - (1)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 55:

/* Line 677 of lalr1.cc  */
#line 391 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            (yyval.string) = (yysemantic_stack_[(2) - (1)].string);
        }
    break;

  case 56:

/* Line 677 of lalr1.cc  */
#line 395 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            error((yylocation_stack_[(2) - (1)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 57:

/* Line 677 of lalr1.cc  */
#line 403 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(2) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            if (var.get() && driver.mCompilePhase == 2)
                driver.NextParameter(*var, exp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 58:

/* Line 677 of lalr1.cc  */
#line 412 "../../src-common/cfdg.ypp"
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

  case 59:

/* Line 677 of lalr1.cc  */
#line 428 "../../src-common/cfdg.ypp"
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

  case 60:

/* Line 677 of lalr1.cc  */
#line 442 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(3) - (1)].ruleObj);
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 61:

/* Line 677 of lalr1.cc  */
#line 451 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (2)].string));
            driver.SetShape(NULL);
            rule_ptr rule(new ASTrule(driver.StringToShape(*name, (yylocation_stack_[(2) - (2)]), false), (yyloc)));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
        }
    break;

  case 62:

/* Line 677 of lalr1.cc  */
#line 460 "../../src-common/cfdg.ypp"
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

  case 63:

/* Line 677 of lalr1.cc  */
#line 475 "../../src-common/cfdg.ypp"
    {
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 64:

/* Line 677 of lalr1.cc  */
#line 483 "../../src-common/cfdg.ypp"
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

  case 65:

/* Line 677 of lalr1.cc  */
#line 495 "../../src-common/cfdg.ypp"
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

  case 66:

/* Line 677 of lalr1.cc  */
#line 512 "../../src-common/cfdg.ypp"
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

  case 67:

/* Line 677 of lalr1.cc  */
#line 537 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 68:

/* Line 677 of lalr1.cc  */
#line 546 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
            driver.SetShape(NULL);
        }
    break;

  case 69:

/* Line 677 of lalr1.cc  */
#line 556 "../../src-common/cfdg.ypp"
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

  case 70:

/* Line 677 of lalr1.cc  */
#line 569 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 71:

/* Line 677 of lalr1.cc  */
#line 576 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(2) - (1)].string));
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(*type, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
		}
    break;

  case 72:

/* Line 677 of lalr1.cc  */
#line 582 "../../src-common/cfdg.ypp"
    {
            static std::string shapeStr("shape");
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(shapeStr, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 73:

/* Line 677 of lalr1.cc  */
#line 588 "../../src-common/cfdg.ypp"
    {
            delete (yysemantic_stack_[(2) - (1)].string);
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 74:

/* Line 677 of lalr1.cc  */
#line 593 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 79:

/* Line 677 of lalr1.cc  */
#line 609 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("number");
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            driver.NextParameterDecl(numtype, *var, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 80:

/* Line 677 of lalr1.cc  */
#line 615 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Reserved keyword: adjustment");
        }
    break;

  case 83:

/* Line 677 of lalr1.cc  */
#line 626 "../../src-common/cfdg.ypp"
    { driver.isFunction = true; }
    break;

  case 84:

/* Line 677 of lalr1.cc  */
#line 627 "../../src-common/cfdg.ypp"
    { driver.isFunction = true; }
    break;

  case 85:

/* Line 677 of lalr1.cc  */
#line 628 "../../src-common/cfdg.ypp"
    { driver.isFunction = false; }
    break;

  case 86:

/* Line 677 of lalr1.cc  */
#line 632 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(3) - (2)].expression);}
    break;

  case 87:

/* Line 677 of lalr1.cc  */
#line 633 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTexpression((yyloc)); }
    break;

  case 88:

/* Line 677 of lalr1.cc  */
#line 634 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 89:

/* Line 677 of lalr1.cc  */
#line 635 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 90:

/* Line 677 of lalr1.cc  */
#line 639 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 1)
                assert ((yysemantic_stack_[(2) - (2)].component) == 0);
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 92:

/* Line 677 of lalr1.cc  */
#line 648 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 94:

/* Line 677 of lalr1.cc  */
#line 655 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(4) - (3)].mod));
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = new ASTpathOp(*pop, mod, (yyloc));
        }
    break;

  case 95:

/* Line 677 of lalr1.cc  */
#line 662 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(2) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            driver.lexer->maybeVersion = token::CFDG2;
            rep_ptr item(new ASTpathCommand(*cmd, mod, (yyloc)));
            (yyval.component) = item.release();
        }
    break;

  case 96:

/* Line 677 of lalr1.cc  */
#line 672 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string));
            exp_ptr mod((yysemantic_stack_[(4) - (3)].expression));
            if (driver.mCompilePhase == 2)
                (yyval.component) = new ASTpathOp(*pop, mod, (yyloc));
            else
                (yyval.component) = 0;
        }
    break;

  case 97:

/* Line 677 of lalr1.cc  */
#line 681 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(3) - (1)].string));
            exp_ptr mod;
            if (driver.mCompilePhase == 2)
                (yyval.component) = new ASTpathOp(*pop, mod, (yyloc));
            else
                (yyval.component) = 0;
        }
    break;

  case 98:

/* Line 677 of lalr1.cc  */
#line 690 "../../src-common/cfdg.ypp"
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

  case 99:

/* Line 677 of lalr1.cc  */
#line 702 "../../src-common/cfdg.ypp"
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

  case 100:

/* Line 677 of lalr1.cc  */
#line 716 "../../src-common/cfdg.ypp"
    { }
    break;

  case 101:

/* Line 677 of lalr1.cc  */
#line 718 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 1)
                assert((yysemantic_stack_[(1) - (1)].component) == 0);
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 102:

/* Line 677 of lalr1.cc  */
#line 726 "../../src-common/cfdg.ypp"
    { }
    break;

  case 103:

/* Line 677 of lalr1.cc  */
#line 728 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 104:

/* Line 677 of lalr1.cc  */
#line 734 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer(driver.switchStack.top());
        }
    break;

  case 107:

/* Line 677 of lalr1.cc  */
#line 746 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(1) - (1)].component); 
        }
    break;

  case 108:

/* Line 677 of lalr1.cc  */
#line 750 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = 0; 
        }
    break;

  case 109:

/* Line 677 of lalr1.cc  */
#line 754 "../../src-common/cfdg.ypp"
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

  case 110:

/* Line 677 of lalr1.cc  */
#line 765 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
                driver.push_repContainer((yysemantic_stack_[(2) - (1)].loopObj)->mFinallyBody);
            }
        }
    break;

  case 111:

/* Line 677 of lalr1.cc  */
#line 770 "../../src-common/cfdg.ypp"
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

  case 112:

/* Line 677 of lalr1.cc  */
#line 783 "../../src-common/cfdg.ypp"
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

  case 113:

/* Line 677 of lalr1.cc  */
#line 794 "../../src-common/cfdg.ypp"
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

  case 114:

/* Line 677 of lalr1.cc  */
#line 805 "../../src-common/cfdg.ypp"
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

  case 115:

/* Line 677 of lalr1.cc  */
#line 817 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].switchObj);
            if (driver.mCompilePhase == 2) {
                (yysemantic_stack_[(4) - (1)].switchObj)->unify();
                driver.switchStack.pop();
            }
        }
    break;

  case 116:

/* Line 677 of lalr1.cc  */
#line 825 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 117:

/* Line 677 of lalr1.cc  */
#line 832 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 118:

/* Line 677 of lalr1.cc  */
#line 833 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 119:

/* Line 677 of lalr1.cc  */
#line 834 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 120:

/* Line 677 of lalr1.cc  */
#line 838 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 121:

/* Line 677 of lalr1.cc  */
#line 840 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(2) - (1)].loopObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            if ((yysemantic_stack_[(2) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].loopObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 122:

/* Line 677 of lalr1.cc  */
#line 848 "../../src-common/cfdg.ypp"
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

  case 123:

/* Line 677 of lalr1.cc  */
#line 860 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 124:

/* Line 677 of lalr1.cc  */
#line 861 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 127:

/* Line 677 of lalr1.cc  */
#line 864 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 132:

/* Line 677 of lalr1.cc  */
#line 872 "../../src-common/cfdg.ypp"
    {
            // parse loop mod and loop body with loop index in scope
            mod_ptr loopmod((yysemantic_stack_[(3) - (2)].mod));
            if (driver.mCompilePhase == 2)
                (yysemantic_stack_[(3) - (1)].loopObj)->mChildChange.grab(loopmod.get());
            (yyval.loopObj) = (yysemantic_stack_[(3) - (1)].loopObj);
            // loopmod gets deleted
        }
    break;

  case 133:

/* Line 677 of lalr1.cc  */
#line 883 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 135:

/* Line 677 of lalr1.cc  */
#line 890 "../../src-common/cfdg.ypp"
    { }
    break;

  case 136:

/* Line 677 of lalr1.cc  */
#line 892 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 137:

/* Line 677 of lalr1.cc  */
#line 898 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), (yylocation_stack_[(2) - (1)])));
            (yyval.component) = new ASTreplacement(*r, r->entropyVal, mod, (yyloc));
        }
    break;

  case 138:

/* Line 677 of lalr1.cc  */
#line 907 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 139:

/* Line 677 of lalr1.cc  */
#line 909 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].loopObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            if ((yysemantic_stack_[(2) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].loopObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 140:

/* Line 677 of lalr1.cc  */
#line 920 "../../src-common/cfdg.ypp"
    { ++driver.mLocalStackDepth; }
    break;

  case 141:

/* Line 677 of lalr1.cc  */
#line 920 "../../src-common/cfdg.ypp"
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

  case 142:

/* Line 677 of lalr1.cc  */
#line 935 "../../src-common/cfdg.ypp"
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

  case 143:

/* Line 677 of lalr1.cc  */
#line 949 "../../src-common/cfdg.ypp"
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

  case 144:

/* Line 677 of lalr1.cc  */
#line 963 "../../src-common/cfdg.ypp"
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

  case 145:

/* Line 677 of lalr1.cc  */
#line 978 "../../src-common/cfdg.ypp"
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

  case 146:

/* Line 677 of lalr1.cc  */
#line 991 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ifObj));
                driver.push_repContainer((yysemantic_stack_[(3) - (1)].ifObj)->mElseBody);
            }
            (yyval.ifObj) = (yysemantic_stack_[(3) - (1)].ifObj);
        }
    break;

  case 147:

/* Line 677 of lalr1.cc  */
#line 1001 "../../src-common/cfdg.ypp"
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

  case 148:

/* Line 677 of lalr1.cc  */
#line 1019 "../../src-common/cfdg.ypp"
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

  case 149:

/* Line 677 of lalr1.cc  */
#line 1041 "../../src-common/cfdg.ypp"
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

  case 150:

/* Line 677 of lalr1.cc  */
#line 1054 "../../src-common/cfdg.ypp"
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

  case 151:

/* Line 677 of lalr1.cc  */
#line 1083 "../../src-common/cfdg.ypp"
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

  case 152:

/* Line 677 of lalr1.cc  */
#line 1096 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), true);
        }
    break;

  case 153:

/* Line 677 of lalr1.cc  */
#line 1101 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), false);
        }
    break;

  case 154:

/* Line 677 of lalr1.cc  */
#line 1108 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), true);
        }
    break;

  case 155:

/* Line 677 of lalr1.cc  */
#line 1113 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(5) - (3)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), false);
        }
    break;

  case 156:

/* Line 677 of lalr1.cc  */
#line 1120 "../../src-common/cfdg.ypp"
    {
            (yysemantic_stack_[(2) - (1)].modList)->push_back((yysemantic_stack_[(2) - (2)].mod));
            (yyval.modList) = (yysemantic_stack_[(2) - (1)].modList);
        }
    break;

  case 157:

/* Line 677 of lalr1.cc  */
#line 1124 "../../src-common/cfdg.ypp"
    {
            (yyval.modList) = new ASTtransform::ModList();
        }
    break;

  case 158:

/* Line 677 of lalr1.cc  */
#line 1129 "../../src-common/cfdg.ypp"
    {
            term_ptr mod((yysemantic_stack_[(2) - (2)].term));
            driver.MakeModTerm((yysemantic_stack_[(2) - (1)].mod)->modExp, mod);
            (yyval.mod) = (yysemantic_stack_[(2) - (1)].mod);
        }
    break;

  case 159:

/* Line 677 of lalr1.cc  */
#line 1134 "../../src-common/cfdg.ypp"
    {
            static const yy::location def;
            ASTmodification* m = new ASTmodification(def);
            m->flags = 0;
            (yyval.mod) = m;
        }
    break;

  case 160:

/* Line 677 of lalr1.cc  */
#line 1143 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].expression));
            (yyval.term) = new ASTmodTerm((ASTmodTerm::modTypeEnum)((yysemantic_stack_[(2) - (1)].modToken)), mod.release(), (yyloc));
        }
    break;

  case 161:

/* Line 677 of lalr1.cc  */
#line 1148 "../../src-common/cfdg.ypp"
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

  case 162:

/* Line 677 of lalr1.cc  */
#line 1158 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.term) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 163:

/* Line 677 of lalr1.cc  */
#line 1163 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.term) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 164:

/* Line 677 of lalr1.cc  */
#line 1170 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTcons::Cons((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 165:

/* Line 677 of lalr1.cc  */
#line 1174 "../../src-common/cfdg.ypp"
    { 
            (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); 
        }
    break;

  case 166:

/* Line 677 of lalr1.cc  */
#line 1180 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 167:

/* Line 677 of lalr1.cc  */
#line 1182 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 168:

/* Line 677 of lalr1.cc  */
#line 1184 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 169:

/* Line 677 of lalr1.cc  */
#line 1186 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 170:

/* Line 677 of lalr1.cc  */
#line 1188 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 171:

/* Line 677 of lalr1.cc  */
#line 1190 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 172:

/* Line 677 of lalr1.cc  */
#line 1192 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 173:

/* Line 677 of lalr1.cc  */
#line 1197 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 174:

/* Line 677 of lalr1.cc  */
#line 1204 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 175:

/* Line 677 of lalr1.cc  */
#line 1206 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 176:

/* Line 677 of lalr1.cc  */
#line 1208 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 177:

/* Line 677 of lalr1.cc  */
#line 1210 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 178:

/* Line 677 of lalr1.cc  */
#line 1215 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 179:

/* Line 677 of lalr1.cc  */
#line 1220 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression));   }
    break;

  case 180:

/* Line 677 of lalr1.cc  */
#line 1222 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('+', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 181:

/* Line 677 of lalr1.cc  */
#line 1224 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('-', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 182:

/* Line 677 of lalr1.cc  */
#line 1226 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('_', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 183:

/* Line 677 of lalr1.cc  */
#line 1228 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('*', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 184:

/* Line 677 of lalr1.cc  */
#line 1230 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('/', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 185:

/* Line 677 of lalr1.cc  */
#line 1232 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 186:

/* Line 677 of lalr1.cc  */
#line 1234 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 187:

/* Line 677 of lalr1.cc  */
#line 1236 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('!', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 188:

/* Line 677 of lalr1.cc  */
#line 1238 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('^', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 189:

/* Line 677 of lalr1.cc  */
#line 1240 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('<', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 190:

/* Line 677 of lalr1.cc  */
#line 1242 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('L', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 191:

/* Line 677 of lalr1.cc  */
#line 1244 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('>', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 192:

/* Line 677 of lalr1.cc  */
#line 1246 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('G', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 193:

/* Line 677 of lalr1.cc  */
#line 1248 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('=', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 194:

/* Line 677 of lalr1.cc  */
#line 1250 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('n', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 195:

/* Line 677 of lalr1.cc  */
#line 1252 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('&', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 196:

/* Line 677 of lalr1.cc  */
#line 1254 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('|', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 197:

/* Line 677 of lalr1.cc  */
#line 1256 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('X', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 198:

/* Line 677 of lalr1.cc  */
#line 1258 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 199:

/* Line 677 of lalr1.cc  */
#line 1260 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].mod); }
    break;

  case 200:

/* Line 677 of lalr1.cc  */
#line 1264 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 201:

/* Line 677 of lalr1.cc  */
#line 1269 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), true);
        }
    break;

  case 202:

/* Line 677 of lalr1.cc  */
#line 1275 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 203:

/* Line 677 of lalr1.cc  */
#line 1281 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 204:

/* Line 677 of lalr1.cc  */
#line 1288 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 205:

/* Line 677 of lalr1.cc  */
#line 1293 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 206:

/* Line 677 of lalr1.cc  */
#line 1299 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 207:

/* Line 677 of lalr1.cc  */
#line 1305 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args(new ASTexpression((yylocation_stack_[(4) - (1)]) + (yylocation_stack_[(4) - (4)])));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 208:

/* Line 677 of lalr1.cc  */
#line 1311 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;



/* Line 677 of lalr1.cc  */
#line 2732 "cfdg.tab.cpp"
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
  const short int CfdgParser::yypact_ninf_ = -244;
  const short int
  CfdgParser::yypact_[] =
  {
       152,  -244,  -244,    25,   799,   819,  -244,     5,  -244,    62,
     102,    21,   -21,  -244,    19,   167,  -244,   -21,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,   -13,  -244,   158,  -244,
     118,   120,    17,   129,   181,   -21,   155,   167,   114,   -21,
    -244,  -244,  -244,  -244,  -244,  -244,   311,   172,  -244,  -244,
    -244,   180,   192,  -244,  -244,   165,   227,   178,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,   197,   202,  -244,   202,   107,   251,  -244,  -244,   252,
    -244,   239,   167,  -244,   211,   212,  -244,   311,  -244,   311,
     311,   311,   213,  -244,   668,  -244,  -244,    73,  -244,  -244,
    -244,  -244,  -244,  -244,    86,    98,   139,   163,   199,   219,
      14,  -244,  -244,  -244,  -244,  -244,  -244,   -29,  -244,  -244,
    -244,  -244,   311,   217,   225,   225,   225,   368,  -244,    96,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   259,   286,
     229,   231,  -244,   278,    37,   243,   149,  -244,   311,  -244,
    -244,  -244,  -244,   284,   219,   264,   264,   264,   247,    84,
      95,   121,     8,  -244,  -244,  -244,   -21,   256,  -244,  -244,
    -244,    60,  -244,  -244,  -244,  -244,   292,    12,   187,  -244,
    -244,  -244,  -244,   116,   242,  -244,   398,  -244,   188,   189,
    -244,   -26,   207,  -244,   428,   248,  -244,   458,  -244,   117,
    -244,   346,   346,   297,   297,   297,   297,   761,   761,   741,
     720,   698,   668,   131,   131,   131,   225,   225,   225,   197,
     300,    67,   668,   311,   311,   219,  -244,   219,  -244,  -244,
     219,  -244,   244,  -244,   668,  -244,   264,  -244,   301,  -244,
    -244,  -244,  -244,  -244,  -244,   258,   261,  -244,  -244,   121,
     121,   311,   121,   169,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,   -21,   263,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,    14,
    -244,  -244,  -244,  -244,  -244,   262,   219,   311,   311,   488,
     518,  -244,  -244,  -244,   548,   264,  -244,   113,  -244,    29,
     311,   270,  -244,  -244,   578,   226,   121,   121,  -244,   -21,
     175,   144,   176,  -244,  -244,  -244,   668,   668,  -244,  -244,
    -244,  -244,  -244,   267,   311,  -244,  -244,   264,   608,  -244,
     638,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,   338,
    -244,  -244,  -244,  -244
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  CfdgParser::yydefact_[] =
  {
         0,     5,     7,     0,     2,     3,     1,     0,    30,     0,
       0,     0,     0,    41,     0,     0,    29,     0,     4,    25,
      19,    20,    17,    18,    21,    22,     0,    23,     0,    24,
       0,     0,    64,     0,    85,     0,    85,     0,    45,     0,
       6,    16,     9,    10,     8,    15,     0,    13,    91,    14,
      38,     0,     0,    11,    12,    48,    61,    69,    27,   159,
     159,    51,    49,    26,    28,    42,    43,    39,    50,   134,
      93,    89,    78,    65,    78,     0,     0,    36,    34,     0,
      37,     0,     0,    35,     0,   208,   174,     0,   175,     0,
       0,     0,   159,   199,    52,   176,    59,     0,    91,    91,
      32,    33,    62,    31,     0,     0,     0,     0,     0,    47,
       0,    58,    66,    80,    79,    84,    82,     0,    54,    53,
      44,    40,     0,     0,   187,   185,   186,     0,   159,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   157,   157,    89,     0,     0,    60,     0,   108,
     107,    90,   116,   109,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   153,   158,   152,     0,     0,    63,   138,
     133,     0,   125,   126,   129,   131,   130,     0,     0,    70,
     120,    92,   122,     0,     0,    88,     0,    46,     0,     0,
      76,     0,     0,    83,     0,     0,   204,     0,   198,     0,
     154,   177,   178,   190,   189,   192,   191,   193,   194,   195,
     196,   197,   179,   181,   180,   182,   183,   184,   188,    89,
       0,   208,   144,     0,     0,   148,    56,   147,    55,   118,
       0,   117,     0,   119,    57,   110,     0,    91,   112,   101,
     113,   114,   105,    67,    68,     0,   203,   166,   167,     0,
       0,     0,   160,   165,   169,   162,   163,   137,   140,   134,
     139,   136,   128,   127,   124,    95,   123,   159,     0,     0,
      93,   103,   121,    87,    86,    74,    72,    73,    71,     0,
      77,    81,   206,   207,   205,     0,     0,     0,     0,     0,
       0,   156,    98,    97,     0,     0,   132,     0,   146,     0,
       0,     0,   170,   171,     0,   164,     0,     0,   161,     0,
       0,     0,     0,    75,   155,    99,   143,   142,   145,   149,
      96,   111,   100,     0,     0,   115,   104,     0,     0,   200,
       0,   168,   172,   173,   141,   135,    94,   102,   151,     0,
     106,   202,   201,   150
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yypgoto_[] =
  {
      -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
     325,   -10,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,   328,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,    48,  -244,   265,   138,  -244,   305,  -150,
     -86,    64,   157,  -244,  -152,  -244,  -244,  -244,   -87,  -244,
    -244,  -244,  -244,  -244,    82,  -244,   173,  -244,  -104,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,   -11,   -98,   203,   -58,
    -244,  -244,  -243,   -82,  -244,  -244
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yydefgoto_[] =
  {
        -1,     3,     4,     5,    40,    18,    19,    41,    20,    42,
      21,    67,    82,    44,    22,    23,    24,    25,    45,    46,
     158,   159,    47,    48,    49,    26,    27,    51,    52,    53,
      54,    28,    29,   200,   201,   111,   116,   117,    76,   109,
      97,   107,   190,   160,   248,   282,   309,   336,   249,   305,
     162,   191,   192,   163,   106,   270,   179,   180,   181,   319,
     164,   165,   166,   167,   168,   337,   275,    93,   235,   104,
     174,   262,   263,    94,   264,    95
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char CfdgParser::yytable_ninf_ = -1;
  const unsigned short int
  CfdgParser::yytable_[] =
  {
        61,    62,   105,   193,   240,   124,    68,   125,   126,   127,
     161,   197,   169,   170,   250,   251,   312,   313,   202,   315,
     198,   289,   273,    77,    78,     6,   196,    80,    83,    63,
      55,    58,   203,   265,   129,   290,    59,   266,    60,   199,
     204,   207,    56,   333,    73,   334,    69,   238,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   246,   232,   274,    59,
     209,    60,   121,   342,   343,    64,   244,   298,    59,   296,
      60,   148,   161,   161,   149,   176,   150,    56,   151,   335,
     152,   153,   148,   108,   306,   149,   239,   150,   154,   151,
     155,   152,   153,   148,   171,   172,   149,   156,   150,   154,
     151,   155,   152,   153,   171,   172,   171,   172,   156,   269,
     154,   148,   155,   123,   149,   113,   150,    57,   151,   156,
     152,   153,   114,   157,   255,   171,   172,   301,   154,   301,
     155,   278,   302,    71,   253,    72,   256,   156,   257,   173,
     279,   299,   300,   331,    74,   254,     1,     2,   175,   210,
     304,   307,   171,   172,   176,   267,   177,   258,   115,   259,
     260,   182,    81,   332,   183,   280,   184,   261,   185,   314,
     295,   186,   145,   146,   182,   350,   147,   183,   187,   184,
     177,   185,   316,   317,   186,    65,    66,   188,   325,   178,
     176,   187,   177,   177,   346,   242,   285,   287,   243,   194,
     188,    75,    84,   286,   288,   326,   327,    70,   193,   321,
     161,   100,   101,   189,    85,   113,    86,   205,   338,   340,
      84,    96,   114,   318,   103,   345,   347,    75,    59,    98,
      60,    87,    85,   276,    86,    88,   277,    89,    90,   316,
     317,    99,   349,   108,   102,    91,    92,    84,   110,    87,
     195,   118,   119,    88,   120,    89,    90,   122,   123,    85,
     128,    86,   148,    91,    92,   149,    92,   150,   206,   151,
     147,   152,   153,    84,   229,   233,    87,   234,   236,   154,
      88,   155,    89,    90,   241,    85,   245,    86,   156,    84,
      91,    92,   272,   283,   230,   303,   252,   268,   344,   293,
     297,   231,    87,    86,   310,   308,    88,   311,    89,    90,
     130,   131,   277,   247,    84,   324,    91,    92,    87,   348,
      43,   339,    88,    50,    89,    90,    85,   323,    86,   112,
     291,    79,    91,    92,   322,   142,   143,   144,   145,   146,
     281,   320,   147,    87,   271,     0,   237,    88,     0,    89,
      90,   130,   131,     0,     0,     0,     0,    91,    92,     0,
       0,     0,     0,     0,   132,   133,   134,   135,   136,   137,
       0,   138,   139,   140,     0,   141,   142,   143,   144,   145,
     146,   130,   131,   147,   142,   143,   144,   145,   146,     0,
     353,   147,     0,     0,   132,   133,   134,   135,   136,   137,
       0,   138,   139,   140,     0,   141,   142,   143,   144,   145,
     146,   130,   131,   147,     0,     0,     0,     0,     0,   208,
       0,     0,     0,     0,   132,   133,   134,   135,   136,   137,
       0,   138,   139,   140,     0,   141,   142,   143,   144,   145,
     146,   130,   131,   147,     0,     0,     0,     0,     0,   284,
       0,     0,     0,     0,   132,   133,   134,   135,   136,   137,
       0,   138,   139,   140,     0,   141,   142,   143,   144,   145,
     146,   130,   131,   147,     0,     0,     0,     0,     0,   292,
       0,     0,     0,     0,   132,   133,   134,   135,   136,   137,
       0,   138,   139,   140,     0,   141,   142,   143,   144,   145,
     146,   130,   131,   147,     0,     0,     0,     0,     0,   294,
       0,     0,     0,     0,   132,   133,   134,   135,   136,   137,
       0,   138,   139,   140,     0,   141,   142,   143,   144,   145,
     146,   130,   131,   147,     0,     0,     0,     0,     0,   328,
       0,     0,     0,     0,   132,   133,   134,   135,   136,   137,
       0,   138,   139,   140,     0,   141,   142,   143,   144,   145,
     146,   130,   131,   147,     0,     0,     0,     0,     0,   329,
       0,     0,     0,     0,   132,   133,   134,   135,   136,   137,
       0,   138,   139,   140,     0,   141,   142,   143,   144,   145,
     146,   130,   131,   147,     0,     0,     0,     0,     0,   330,
       0,     0,     0,     0,   132,   133,   134,   135,   136,   137,
       0,   138,   139,   140,     0,   141,   142,   143,   144,   145,
     146,   130,   131,   147,     0,     0,     0,     0,     0,   341,
       0,     0,     0,     0,   132,   133,   134,   135,   136,   137,
       0,   138,   139,   140,     0,   141,   142,   143,   144,   145,
     146,   130,   131,   147,     0,     0,     0,     0,     0,   351,
       0,     0,     0,     0,   132,   133,   134,   135,   136,   137,
       0,   138,   139,   140,     0,   141,   142,   143,   144,   145,
     146,   130,   131,   147,     0,     0,     0,     0,     0,   352,
       0,     0,     0,     0,   132,   133,   134,   135,   136,   137,
       0,   138,   139,   140,     0,   141,   142,   143,   144,   145,
     146,   130,   131,   147,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   132,   133,   134,   135,   136,   137,
       0,   138,   139,   130,   131,     0,   142,   143,   144,   145,
     146,     0,     0,   147,     0,     0,   132,   133,   134,   135,
     136,   137,     0,   138,   130,   131,     0,     0,   142,   143,
     144,   145,   146,     0,     0,   147,     0,   132,   133,   134,
     135,   136,   137,     0,   130,   131,     0,     0,     0,   142,
     143,   144,   145,   146,     0,     0,   147,   132,   133,   134,
     135,     0,     7,     0,     0,     8,     9,    10,     0,   142,
     143,   144,   145,   146,     0,     0,   147,    11,     0,    12,
       0,    13,    30,     0,    14,    31,    32,    33,     0,    15,
      16,    17,     0,     0,     0,     0,     0,    34,     0,    35,
       0,    13,     0,     0,    36,     0,     0,     0,     0,    37,
      38,    39
  };

  /* YYCHECK.  */
  const short int
  CfdgParser::yycheck_[] =
  {
        11,    12,    60,   107,   154,    87,    17,    89,    90,    91,
      97,   109,    98,    99,   166,   167,   259,   260,    47,   262,
       6,    47,    10,    34,    35,     0,   108,    37,    39,    10,
      25,    10,    61,    25,    92,    61,    57,    29,    59,    25,
     122,   123,    25,    14,    27,    16,    59,    10,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   164,   149,    56,    57,
     128,    59,    82,   316,   317,    56,   158,    10,    57,   229,
      59,     8,   169,   170,    11,    25,    13,    25,    15,    60,
      17,    18,     8,    56,   246,    11,    59,    13,    25,    15,
      27,    17,    18,     8,    18,    19,    11,    34,    13,    25,
      15,    27,    17,    18,    18,    19,    18,    19,    34,    59,
      25,     8,    27,    56,    11,    18,    13,    25,    15,    34,
      17,    18,    25,    60,    13,    18,    19,   235,    25,   237,
      27,    25,   240,    25,    60,    25,    25,    34,    27,    63,
      34,   233,   234,   305,    25,    60,     4,     5,    60,    63,
     242,   247,    18,    19,    25,   176,    27,    46,    61,    48,
      49,     8,    58,    60,    11,    59,    13,    56,    15,   261,
      63,    18,    51,    52,     8,   337,    55,    11,    25,    13,
      27,    15,    23,    24,    18,    28,    29,    34,   296,    60,
      25,    25,    27,    27,    60,    56,    18,    18,    59,    10,
      34,    56,    13,    25,    25,   297,   298,    59,   322,   277,
     307,    56,    57,    60,    25,    18,    27,    10,   310,   311,
      13,    59,    25,    64,    56,    60,    60,    56,    57,    59,
      59,    42,    25,    56,    27,    46,    59,    48,    49,    23,
      24,    59,   334,    56,    27,    56,    57,    13,    56,    42,
      61,    10,    10,    46,    25,    48,    49,    56,    56,    25,
      57,    27,     8,    56,    57,    11,    57,    13,    61,    15,
      55,    17,    18,    13,    25,    56,    42,    56,    10,    25,
      46,    27,    48,    49,    51,    25,    12,    27,    34,    13,
      56,    57,    10,    61,    18,    61,    59,    51,   319,    61,
      10,    25,    42,    27,    56,    14,    46,    56,    48,    49,
      23,    24,    59,    59,    13,    63,    56,    57,    42,    62,
       5,    61,    46,     5,    48,    49,    25,   289,    27,    74,
     202,    36,    56,    57,   280,    48,    49,    50,    51,    52,
     193,   269,    55,    42,   181,    -1,   153,    46,    -1,    48,
      49,    23,    24,    -1,    -1,    -1,    -1,    56,    57,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    23,    24,    55,    48,    49,    50,    51,    52,    -1,
      62,    55,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    23,    24,    55,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    23,    24,    55,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    23,    24,    55,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    23,    24,    55,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    23,    24,    55,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    23,    24,    55,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    23,    24,    55,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    23,    24,    55,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    23,    24,    55,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    23,    24,    55,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    -1,    47,    48,    49,    50,    51,
      52,    23,    24,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    23,    24,    -1,    48,    49,    50,    51,
      52,    -1,    -1,    55,    -1,    -1,    36,    37,    38,    39,
      40,    41,    -1,    43,    23,    24,    -1,    -1,    48,    49,
      50,    51,    52,    -1,    -1,    55,    -1,    36,    37,    38,
      39,    40,    41,    -1,    23,    24,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    -1,    -1,    55,    36,    37,    38,
      39,    -1,     3,    -1,    -1,     6,     7,     8,    -1,    48,
      49,    50,    51,    52,    -1,    -1,    55,    18,    -1,    20,
      -1,    22,     3,    -1,    25,     6,     7,     8,    -1,    30,
      31,    32,    -1,    -1,    -1,    -1,    -1,    18,    -1,    20,
      -1,    22,    -1,    -1,    25,    -1,    -1,    -1,    -1,    30,
      31,    32
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  CfdgParser::yystos_[] =
  {
         0,     4,     5,    66,    67,    68,     0,     3,     6,     7,
       8,    18,    20,    22,    25,    30,    31,    32,    70,    71,
      73,    75,    79,    80,    81,    82,    90,    91,    96,    97,
       3,     6,     7,     8,    18,    20,    25,    30,    31,    32,
      69,    72,    74,    75,    78,    83,    84,    87,    88,    89,
      90,    92,    93,    94,    95,    25,    25,    25,    10,    57,
      59,   131,   131,    10,    56,    28,    29,    76,   131,    59,
      59,    25,    25,    27,    25,    56,   103,   131,   131,   103,
      76,    58,    77,   131,    13,    25,    27,    42,    46,    48,
      49,    56,    57,   132,   138,   140,    59,   105,    59,    59,
      56,    57,    27,    56,   134,   134,   119,   106,    56,   104,
      56,   100,   100,    18,    25,    61,   101,   102,    10,    10,
      25,    76,    56,    56,   138,   138,   138,   138,    57,   134,
      23,    24,    36,    37,    38,    39,    40,    41,    43,    44,
      45,    47,    48,    49,    50,    51,    52,    55,     8,    11,
      13,    15,    17,    18,    25,    27,    34,    60,    85,    86,
     108,   113,   115,   118,   125,   126,   127,   128,   129,   105,
     105,    18,    19,    63,   135,    60,    25,    27,    60,   121,
     122,   123,     8,    11,    13,    15,    18,    25,    34,    60,
     107,   116,   117,   123,    10,    61,   138,   132,     6,    25,
      98,    99,    47,    61,   138,    10,    61,   138,    61,   134,
      63,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,    25,
      18,    25,   138,    56,    56,   133,    10,   133,    10,    59,
     104,    51,    56,    59,   138,    12,   132,    59,   109,   113,
     109,   109,    59,    60,    60,    13,    25,    27,    46,    48,
      49,    56,   136,   137,   139,    25,    29,   131,    51,    59,
     120,   121,    10,    10,    56,   131,    56,    59,    25,    34,
      59,   107,   110,    61,    61,    18,    25,    18,    25,    47,
      61,   101,    61,    61,    61,    63,   104,    10,    10,   138,
     138,   132,   132,    61,   138,   114,   109,   105,    14,   111,
      56,    56,   137,   137,   138,   137,    23,    24,    64,   124,
     119,   134,   106,    98,    63,   132,   138,   138,    61,    61,
      61,   109,    60,    14,    16,    60,   112,   130,   138,    61,
     138,    61,   137,   137,   131,    60,    60,    60,    62,   138,
     109,    61,    61,    62
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
     295,   296,   297,   298,   299,   300,   301,    44,    45,    43,
      95,    42,    47,   302,   303,    94,    40,    91,    64,   123,
     125,    41,    58,    93,   124
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  CfdgParser::yyr1_[] =
  {
         0,    65,    66,    66,    67,    67,    68,    68,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    71,    71,    71,    71,
      71,    71,    71,    71,    72,    72,    72,    72,    72,    73,
      74,    75,    76,    76,    77,    77,    78,    78,    79,    80,
      81,    82,    83,    84,    84,    85,    85,    86,    87,    88,
      89,    90,    90,    91,    92,    92,    93,    94,    95,    96,
      97,    98,    98,    98,    98,    99,    99,   100,   100,   101,
     101,   102,   102,   103,   103,   103,   104,   104,   104,   104,
     105,   105,   106,   106,   107,   107,   108,   108,   108,   108,
     109,   109,   110,   110,   111,   111,   112,   113,   113,   113,
     114,   113,   113,   113,   113,   113,   113,   115,   115,   115,
     116,   116,   116,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   118,   119,   119,   120,   120,   121,   122,   122,
     124,   123,   125,   125,   125,   126,   127,   128,   128,   129,
     130,   130,   131,   131,   132,   132,   133,   133,   134,   134,
     135,   135,   135,   135,   136,   136,   137,   137,   137,   137,
     137,   137,   137,   137,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     139,   139,   139,   139,   140,   140,   140,   140,   140
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  CfdgParser::yyr2_[] =
  {
         0,     2,     2,     2,     2,     0,     2,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     1,
       1,     3,     3,     3,     2,     2,     2,     2,     1,     2,
       3,     1,     1,     1,     2,     0,     4,     3,     2,     2,
       2,     2,     2,     3,     3,     2,     2,     2,     3,     2,
       3,     2,     3,     4,     1,     2,     3,     4,     4,     2,
       4,     2,     2,     2,     2,     3,     1,     3,     0,     1,
       1,     3,     1,     3,     2,     0,     3,     3,     2,     0,
       2,     0,     2,     0,     4,     2,     4,     3,     3,     4,
       3,     1,     3,     1,     2,     0,     2,     1,     1,     1,
       0,     4,     2,     2,     2,     4,     1,     2,     2,     2,
       1,     2,     1,     2,     2,     1,     1,     2,     2,     1,
       1,     1,     3,     2,     0,     3,     1,     2,     1,     2,
       0,     4,     4,     4,     2,     4,     3,     2,     2,     4,
       3,     2,     3,     3,     3,     5,     2,     0,     2,     0,
       2,     3,     2,     2,     2,     1,     1,     1,     3,     1,
       2,     2,     3,     3,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     4,     4,     1,     3,     4,     4,     4,     1
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const CfdgParser::yytname_[] =
  {
    "$end", "error", "$undefined", "STARTSHAPE", "CFDG2", "CFDG3", "SHAPE",
  "RULE", "PATH", "DEFINE", "BECOMES", "LOOP", "FINALLY", "IF", "ELSE",
  "SWITCH", "CASE", "CLONE", "MODTYPE", "PARAM", "BACKGROUND", "BADEOF",
  "GOODEOF", "RANGEOP", "PLUSMINUSOP", "USER_STRING", "USER_INTEGER",
  "USER_RATIONAL", "USER_FILENAME", "USER_QSTRING", "INCLUDE", "IMPORT",
  "TILE", "PARAMETERS", "USER_PATHOP", "STROKEWIDTH", "LE", "LT", "GE",
  "GT", "EQ", "NEQ", "NOT", "AND", "OR", "XOR", "CF_INFINITY", "','",
  "'-'", "'+'", "'_'", "'*'", "'/'", "POS", "NEG", "'^'", "'('", "'['",
  "'@'", "'{'", "'}'", "')'", "':'", "']'", "'|'", "$accept", "choose",
  "cfdg2", "cfdg3", "statement", "statement_v2", "v3clues", "v2stuff",
  "inclusion", "import", "eof", "fileString", "fileNameSpace",
  "initialization", "initialization_v2", "background", "tile", "size",
  "global_definition", "global_definition_header", "definition_header",
  "definition", "shape", "shape_singleton_header", "shape_singleton",
  "rule_header_v2", "rule_v2", "rule_header", "path_header", "rule",
  "path", "path_header_v2", "path_v2", "parameter", "buncha_parameters",
  "parameter_list", "function_parameter", "buncha_function_parameters",
  "function_parameter_list", "parameter_spec", "buncha_elements",
  "buncha_pathOps_v2", "pathOp_simple_v2", "element_simple",
  "one_or_more_elements", "one_or_more_pathOp_v2", "caseBody",
  "caseBody_element", "element", "$@1", "element_v2clue", "pathOp_v2",
  "pathOp_v3clues", "element_loop", "buncha_replacements_v2",
  "one_or_more_replacements_v2", "replacement_simple_v2", "replacement_v2",
  "loopHeader_v2", "$@2", "loopHeader", "ifHeader", "ifElseHeader",
  "transHeader", "switchHeader", "caseHeader", "modification_v2",
  "modification", "buncha_mods", "buncha_adjustments", "adjustment",
  "explist", "exp", "exp2", "expfunc", "exp2func", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const CfdgParser::rhs_number_type
  CfdgParser::yyrhs_[] =
  {
        66,     0,    -1,     4,    67,    -1,     5,    68,    -1,    67,
      70,    -1,    -1,    68,    69,    -1,    -1,    78,    -1,    74,
      -1,    75,    -1,    94,    -1,    95,    -1,    87,    -1,    89,
      -1,    83,    -1,    72,    -1,    79,    -1,    80,    -1,    73,
      -1,    75,    -1,    81,    -1,    82,    -1,    91,    -1,    97,
      -1,    71,    -1,    25,    10,    -1,    18,    10,    -1,    25,
      56,    -1,    31,    -1,     6,    -1,     8,    25,    56,    -1,
       3,    25,    56,    -1,     3,    25,    57,    -1,    20,   131,
      -1,    32,   131,    -1,    18,   131,    -1,    30,    76,    -1,
      90,    -1,    30,    76,    -1,    31,    77,    76,    -1,    22,
      -1,    28,    -1,    29,    -1,    58,    25,    -1,    -1,     3,
      25,   104,   132,    -1,     3,    25,   104,    -1,     3,    25,
      -1,    20,   131,    -1,    32,   131,    -1,    18,   131,    -1,
      84,   138,    -1,    25,   103,    10,    -1,    18,   103,    10,
      -1,    25,    10,    -1,    18,    10,    -1,    85,   138,    -1,
       6,    25,   100,    -1,    87,    59,    -1,    88,   105,    60,
      -1,     7,    25,    -1,     7,    25,    27,    -1,    90,    59,
     119,    60,    -1,     7,    -1,     7,    27,    -1,     8,    25,
     100,    -1,    92,    59,   105,    60,    -1,    93,    59,   105,
      60,    -1,     8,    25,    -1,    96,    59,   106,    60,    -1,
      25,    25,    -1,     6,    25,    -1,    25,    18,    -1,     6,
      18,    -1,    99,    47,    98,    -1,    98,    -1,    56,    99,
      61,    -1,    -1,    25,    -1,    18,    -1,   102,    47,   101,
      -1,   101,    -1,    56,   102,    61,    -1,    56,    61,    -1,
      -1,    56,   138,    61,    -1,    56,    10,    61,    -1,    56,
      61,    -1,    -1,   105,   113,    -1,    -1,   106,   116,    -1,
      -1,    34,    59,   134,    60,    -1,    25,   131,    -1,    34,
      56,   138,    61,    -1,    34,    56,    61,    -1,    25,   104,
     132,    -1,     8,    25,   104,   132,    -1,    59,   105,    60,
      -1,   113,    -1,    59,   106,    60,    -1,   107,    -1,   111,
     112,    -1,    -1,   130,   109,    -1,   108,    -1,    86,    -1,
     118,    -1,    -1,   118,    12,   114,   109,    -1,   126,   109,
      -1,   127,   109,    -1,   128,   109,    -1,   129,    59,   111,
      60,    -1,   115,    -1,    27,    51,    -1,    25,    59,    -1,
      34,    59,    -1,   107,    -1,   123,   110,    -1,   117,    -1,
      34,    56,    -1,    25,    56,    -1,     8,    -1,    11,    -1,
      25,    10,    -1,    18,    10,    -1,    13,    -1,    18,    -1,
      15,    -1,   125,   132,   109,    -1,   119,   122,    -1,    -1,
      59,   119,    60,    -1,   121,    -1,    25,   131,    -1,   121,
      -1,   123,   120,    -1,    -1,    27,    51,   124,   131,    -1,
      11,    25,    10,   138,    -1,    11,    18,    10,   138,    -1,
      11,   138,    -1,    13,    56,   138,    61,    -1,   126,   109,
      14,    -1,    18,   133,    -1,    17,   133,    -1,    15,    56,
     138,    61,    -1,    16,   138,    62,    -1,    14,    62,    -1,
      59,   134,    60,    -1,    57,   134,    63,    -1,    57,   134,
      63,    -1,    57,    57,   134,    63,    63,    -1,   133,   132,
      -1,    -1,   134,   135,    -1,    -1,    18,   136,    -1,    18,
     137,    64,    -1,    19,    25,    -1,    19,    29,    -1,   136,
     137,    -1,   137,    -1,    27,    -1,    46,    -1,    56,   138,
      61,    -1,   139,    -1,    48,   137,    -1,    49,   137,    -1,
     137,    23,   137,    -1,   137,    24,   137,    -1,    27,    -1,
      46,    -1,   140,    -1,   138,    23,   138,    -1,   138,    24,
     138,    -1,   138,    47,   138,    -1,   138,    49,   138,    -1,
     138,    48,   138,    -1,   138,    50,   138,    -1,   138,    51,
     138,    -1,   138,    52,   138,    -1,    48,   138,    -1,    49,
     138,    -1,    42,   138,    -1,   138,    55,   138,    -1,   138,
      37,   138,    -1,   138,    36,   138,    -1,   138,    39,   138,
      -1,   138,    38,   138,    -1,   138,    40,   138,    -1,   138,
      41,   138,    -1,   138,    43,   138,    -1,   138,    44,   138,
      -1,   138,    45,   138,    -1,    56,   138,    61,    -1,   132,
      -1,    25,    56,    61,    -1,    25,    56,   138,    61,    -1,
      13,    56,   138,    61,    -1,    25,    -1,    25,    56,    61,
      -1,    25,    56,   138,    61,    -1,    13,    56,   138,    61,
      -1,    25,    56,    10,    61,    -1,    25,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  CfdgParser::yyprhs_[] =
  {
         0,     0,     3,     6,     9,    12,    13,    16,    17,    19,
      21,    23,    25,    27,    29,    31,    33,    35,    37,    39,
      41,    43,    45,    47,    49,    51,    53,    56,    59,    62,
      64,    66,    70,    74,    78,    81,    84,    87,    90,    92,
      95,    99,   101,   103,   105,   108,   109,   114,   118,   121,
     124,   127,   130,   133,   137,   141,   144,   147,   150,   154,
     157,   161,   164,   168,   173,   175,   178,   182,   187,   192,
     195,   200,   203,   206,   209,   212,   216,   218,   222,   223,
     225,   227,   231,   233,   237,   240,   241,   245,   249,   252,
     253,   256,   257,   260,   261,   266,   269,   274,   278,   282,
     287,   291,   293,   297,   299,   302,   303,   306,   308,   310,
     312,   313,   318,   321,   324,   327,   332,   334,   337,   340,
     343,   345,   348,   350,   353,   356,   358,   360,   363,   366,
     368,   370,   372,   376,   379,   380,   384,   386,   389,   391,
     394,   395,   400,   405,   410,   413,   418,   422,   425,   428,
     433,   437,   440,   444,   448,   452,   458,   461,   462,   465,
     466,   469,   473,   476,   479,   482,   484,   486,   488,   492,
     494,   497,   500,   504,   508,   510,   512,   514,   518,   522,
     526,   530,   534,   538,   542,   546,   549,   552,   555,   559,
     563,   567,   571,   575,   579,   583,   587,   591,   595,   599,
     601,   605,   610,   615,   617,   621,   626,   631,   636
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  CfdgParser::yyrline_[] =
  {
         0,   187,   187,   187,   190,   195,   199,   204,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   243,   244,   245,   246,
     247,   248,   249,   250,   254,   255,   256,   257,   258,   262,
     271,   282,   289,   289,   292,   293,   297,   310,   324,   335,
     345,   355,   370,   379,   383,   391,   395,   403,   412,   428,
     442,   451,   460,   475,   483,   495,   512,   537,   546,   556,
     569,   576,   582,   588,   593,   599,   600,   604,   605,   609,
     615,   621,   622,   626,   627,   628,   632,   633,   634,   635,
     639,   644,   648,   651,   655,   662,   672,   681,   690,   702,
     716,   718,   726,   728,   734,   738,   742,   746,   750,   754,
     765,   765,   783,   794,   805,   816,   825,   832,   833,   834,
     838,   840,   848,   860,   861,   862,   863,   864,   865,   866,
     867,   868,   872,   883,   886,   890,   892,   898,   907,   909,
     920,   920,   935,   949,   963,   978,   991,  1001,  1019,  1041,
    1054,  1083,  1096,  1101,  1108,  1113,  1120,  1124,  1129,  1134,
    1143,  1148,  1158,  1163,  1170,  1174,  1180,  1182,  1184,  1186,
    1188,  1190,  1192,  1197,  1204,  1206,  1208,  1210,  1215,  1220,
    1222,  1224,  1226,  1228,  1230,  1232,  1234,  1236,  1238,  1240,
    1242,  1244,  1246,  1248,  1250,  1252,  1254,  1256,  1258,  1260,
    1264,  1269,  1275,  1281,  1288,  1293,  1299,  1305,  1311
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
      56,    61,    51,    49,    47,    48,     2,    52,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    62,     2,
       2,     2,     2,     2,    58,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    57,     2,    63,    55,    50,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    59,    64,    60,     2,     2,     2,     2,
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
      45,    46,    53,    54
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int CfdgParser::yyeof_ = 0;
  const int CfdgParser::yylast_ = 851;
  const int CfdgParser::yynnts_ = 76;
  const int CfdgParser::yyempty_ = -2;
  const int CfdgParser::yyfinal_ = 6;
  const int CfdgParser::yyterror_ = 1;
  const int CfdgParser::yyerrcode_ = 256;
  const int CfdgParser::yyntokens_ = 65;

  const unsigned int CfdgParser::yyuser_token_number_max_ = 303;
  const CfdgParser::token_number_type CfdgParser::yyundef_token_ = 2;


} // yy

/* Line 1053 of lalr1.cc  */
#line 3604 "cfdg.tab.cpp"


/* Line 1055 of lalr1.cc  */
#line 1317 "../../src-common/cfdg.ypp"


void yy::CfdgParser::error(const CfdgParser::location_type& l, const std::string& m)
{
    driver.mWant2ndPass = false;
    driver.error(l, m);
}

