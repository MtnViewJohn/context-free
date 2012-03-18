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
#line 61 "cfdg.tab.cpp"


#include "cfdg.tab.hpp"

/* User implementation prologue.  */

/* Line 316 of lalr1.cc  */
#line 78 "../../src-common/cfdg.ypp"

#include "astreplacement.h"
#include "astexpression.h"
    
    using namespace AST;

/* Line 316 of lalr1.cc  */
#line 169 "../../src-common/cfdg.ypp"

#include "scanner.h"
#include "math.h"
#include "builder.h"
#include <cassert>
	
#undef yylex
#define yylex driver.lexer->lex


/* Line 316 of lalr1.cc  */
#line 89 "cfdg.tab.cpp"

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
#line 155 "cfdg.tab.cpp"
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
        case 24: /* "USER_STRING" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 262 "cfdg.tab.cpp"
	break;
      case 27: /* "USER_FILENAME" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 271 "cfdg.tab.cpp"
	break;
      case 28: /* "USER_QSTRING" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 280 "cfdg.tab.cpp"
	break;
      case 33: /* "USER_PATHOP" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 289 "cfdg.tab.cpp"
	break;
      case 68: /* "statement" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 298 "cfdg.tab.cpp"
	break;
      case 69: /* "statement_v2" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 307 "cfdg.tab.cpp"
	break;
      case 75: /* "fileString" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 316 "cfdg.tab.cpp"
	break;
      case 76: /* "fileNameSpace" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 325 "cfdg.tab.cpp"
	break;
      case 77: /* "initialization" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 334 "cfdg.tab.cpp"
	break;
      case 78: /* "initialization_v2" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 343 "cfdg.tab.cpp"
	break;
      case 79: /* "background" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 352 "cfdg.tab.cpp"
	break;
      case 80: /* "tile" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 361 "cfdg.tab.cpp"
	break;
      case 81: /* "size" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 370 "cfdg.tab.cpp"
	break;
      case 83: /* "global_definition_header" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 379 "cfdg.tab.cpp"
	break;
      case 84: /* "definition_header" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 388 "cfdg.tab.cpp"
	break;
      case 86: /* "shape" */

/* Line 479 of lalr1.cc  */
#line 167 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->shapeObj); };

/* Line 479 of lalr1.cc  */
#line 397 "cfdg.tab.cpp"
	break;
      case 87: /* "shape_singleton_header" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 406 "cfdg.tab.cpp"
	break;
      case 88: /* "shape_singleton" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 415 "cfdg.tab.cpp"
	break;
      case 89: /* "rule_header_v2" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 424 "cfdg.tab.cpp"
	break;
      case 91: /* "rule_header" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 433 "cfdg.tab.cpp"
	break;
      case 92: /* "path_header" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 442 "cfdg.tab.cpp"
	break;
      case 93: /* "rule" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 451 "cfdg.tab.cpp"
	break;
      case 94: /* "path" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 460 "cfdg.tab.cpp"
	break;
      case 95: /* "path_header_v2" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 469 "cfdg.tab.cpp"
	break;
      case 103: /* "parameter_spec" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 478 "cfdg.tab.cpp"
	break;
      case 106: /* "pathOp_simple_v2" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 487 "cfdg.tab.cpp"
	break;
      case 107: /* "element_simple" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 496 "cfdg.tab.cpp"
	break;
      case 112: /* "element" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 505 "cfdg.tab.cpp"
	break;
      case 115: /* "pathOp_v2" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 514 "cfdg.tab.cpp"
	break;
      case 117: /* "element_loop" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 523 "cfdg.tab.cpp"
	break;
      case 120: /* "replacement_simple_v2" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 532 "cfdg.tab.cpp"
	break;
      case 121: /* "replacement_v2" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 541 "cfdg.tab.cpp"
	break;
      case 122: /* "loopHeader_v2" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 550 "cfdg.tab.cpp"
	break;
      case 124: /* "loopHeader" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 559 "cfdg.tab.cpp"
	break;
      case 125: /* "loopexp" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 568 "cfdg.tab.cpp"
	break;
      case 126: /* "ifHeader" */

/* Line 479 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ifObj); };

/* Line 479 of lalr1.cc  */
#line 577 "cfdg.tab.cpp"
	break;
      case 127: /* "ifElseHeader" */

/* Line 479 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->ifObj); };

/* Line 479 of lalr1.cc  */
#line 586 "cfdg.tab.cpp"
	break;
      case 128: /* "transHeader" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 595 "cfdg.tab.cpp"
	break;
      case 129: /* "switchHeader" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->switchObj); };

/* Line 479 of lalr1.cc  */
#line 604 "cfdg.tab.cpp"
	break;
      case 130: /* "caseHeader" */

/* Line 479 of lalr1.cc  */
#line 168 "../../src-common/cfdg.ypp"
	{ if (driver.mCompilePhase == 2) driver.pop_repContainer(NULL); };

/* Line 479 of lalr1.cc  */
#line 613 "cfdg.tab.cpp"
	break;
      case 131: /* "modification_v2" */

/* Line 479 of lalr1.cc  */
#line 157 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 622 "cfdg.tab.cpp"
	break;
      case 132: /* "modification" */

/* Line 479 of lalr1.cc  */
#line 157 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 631 "cfdg.tab.cpp"
	break;
      case 133: /* "buncha_adjustments" */

/* Line 479 of lalr1.cc  */
#line 157 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 640 "cfdg.tab.cpp"
	break;
      case 134: /* "adjustment" */

/* Line 479 of lalr1.cc  */
#line 156 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->term); };

/* Line 479 of lalr1.cc  */
#line 649 "cfdg.tab.cpp"
	break;
      case 135: /* "explist" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 658 "cfdg.tab.cpp"
	break;
      case 136: /* "exp" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 667 "cfdg.tab.cpp"
	break;
      case 137: /* "exp2" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 676 "cfdg.tab.cpp"
	break;
      case 138: /* "expfunc" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 685 "cfdg.tab.cpp"
	break;
      case 139: /* "exp2func" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 694 "cfdg.tab.cpp"
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
#line 185 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 6:

/* Line 677 of lalr1.cc  */
#line 194 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 9:

/* Line 677 of lalr1.cc  */
#line 204 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 10:

/* Line 677 of lalr1.cc  */
#line 205 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 13:

/* Line 677 of lalr1.cc  */
#line 208 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].shapeObj); }
    break;

  case 15:

/* Line 677 of lalr1.cc  */
#line 210 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 16:

/* Line 677 of lalr1.cc  */
#line 211 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 19:

/* Line 677 of lalr1.cc  */
#line 220 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 20:

/* Line 677 of lalr1.cc  */
#line 221 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 25:

/* Line 677 of lalr1.cc  */
#line 226 "../../src-common/cfdg.ypp"
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
#line 238 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 27:

/* Line 677 of lalr1.cc  */
#line 239 "../../src-common/cfdg.ypp"
    {}
    break;

  case 28:

/* Line 677 of lalr1.cc  */
#line 240 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 31:

/* Line 677 of lalr1.cc  */
#line 243 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 32:

/* Line 677 of lalr1.cc  */
#line 244 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 33:

/* Line 677 of lalr1.cc  */
#line 245 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 34:

/* Line 677 of lalr1.cc  */
#line 249 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 35:

/* Line 677 of lalr1.cc  */
#line 250 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 36:

/* Line 677 of lalr1.cc  */
#line 251 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 37:

/* Line 677 of lalr1.cc  */
#line 252 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 38:

/* Line 677 of lalr1.cc  */
#line 253 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(1) - (1)].ruleObj); }
    break;

  case 39:

/* Line 677 of lalr1.cc  */
#line 257 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(2) - (2)].string));
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(NULL);
            driver.IncludeFile(*file);
        }
    break;

  case 40:

/* Line 677 of lalr1.cc  */
#line 266 "../../src-common/cfdg.ypp"
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
#line 277 "../../src-common/cfdg.ypp"
    {
            if (driver.EndInclude())
                YYACCEPT;
        }
    break;

  case 44:

/* Line 677 of lalr1.cc  */
#line 287 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 45:

/* Line 677 of lalr1.cc  */
#line 288 "../../src-common/cfdg.ypp"
    { (yyval.string) = NULL; }
    break;

  case 46:

/* Line 677 of lalr1.cc  */
#line 292 "../../src-common/cfdg.ypp"
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
#line 305 "../../src-common/cfdg.ypp"
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
#line 319 "../../src-common/cfdg.ypp"
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
#line 330 "../../src-common/cfdg.ypp"
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
#line 340 "../../src-common/cfdg.ypp"
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
#line 350 "../../src-common/cfdg.ypp"
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
#line 365 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(2) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            if (var.get())
                driver.NextParameter(*var, exp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 53:

/* Line 677 of lalr1.cc  */
#line 374 "../../src-common/cfdg.ypp"
    {
            driver.push_paramDecls(*(yysemantic_stack_[(3) - (1)].string), (yyloc));
            (yyval.string) = (yysemantic_stack_[(3) - (1)].string);
        }
    break;

  case 54:

/* Line 677 of lalr1.cc  */
#line 378 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            error((yylocation_stack_[(3) - (1)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 55:

/* Line 677 of lalr1.cc  */
#line 386 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            (yyval.string) = (yysemantic_stack_[(2) - (1)].string);
        }
    break;

  case 56:

/* Line 677 of lalr1.cc  */
#line 390 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            error((yylocation_stack_[(2) - (1)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 57:

/* Line 677 of lalr1.cc  */
#line 398 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(2) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            if (var.get() && driver.mCompilePhase == 2)
                driver.NextParameter(*var, exp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 58:

/* Line 677 of lalr1.cc  */
#line 407 "../../src-common/cfdg.ypp"
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
#line 423 "../../src-common/cfdg.ypp"
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
#line 437 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(3) - (1)].ruleObj);
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 61:

/* Line 677 of lalr1.cc  */
#line 446 "../../src-common/cfdg.ypp"
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
#line 455 "../../src-common/cfdg.ypp"
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
#line 470 "../../src-common/cfdg.ypp"
    {
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 64:

/* Line 677 of lalr1.cc  */
#line 478 "../../src-common/cfdg.ypp"
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
#line 490 "../../src-common/cfdg.ypp"
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
#line 507 "../../src-common/cfdg.ypp"
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
#line 532 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 68:

/* Line 677 of lalr1.cc  */
#line 541 "../../src-common/cfdg.ypp"
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
#line 551 "../../src-common/cfdg.ypp"
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
#line 564 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 71:

/* Line 677 of lalr1.cc  */
#line 571 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(2) - (1)].string));
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(*type, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
		}
    break;

  case 72:

/* Line 677 of lalr1.cc  */
#line 577 "../../src-common/cfdg.ypp"
    {
            static std::string shapeStr("shape");
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(shapeStr, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 73:

/* Line 677 of lalr1.cc  */
#line 583 "../../src-common/cfdg.ypp"
    {
            delete (yysemantic_stack_[(2) - (1)].string);
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 74:

/* Line 677 of lalr1.cc  */
#line 588 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 79:

/* Line 677 of lalr1.cc  */
#line 604 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("number");
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            driver.NextParameterDecl(numtype, *var, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 80:

/* Line 677 of lalr1.cc  */
#line 610 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Reserved keyword: adjustment");
        }
    break;

  case 83:

/* Line 677 of lalr1.cc  */
#line 621 "../../src-common/cfdg.ypp"
    { driver.isFunction = true; }
    break;

  case 84:

/* Line 677 of lalr1.cc  */
#line 622 "../../src-common/cfdg.ypp"
    { driver.isFunction = true; }
    break;

  case 85:

/* Line 677 of lalr1.cc  */
#line 623 "../../src-common/cfdg.ypp"
    { driver.isFunction = false; }
    break;

  case 86:

/* Line 677 of lalr1.cc  */
#line 627 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(3) - (2)].expression);}
    break;

  case 87:

/* Line 677 of lalr1.cc  */
#line 628 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTexpression((yyloc)); }
    break;

  case 88:

/* Line 677 of lalr1.cc  */
#line 629 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 89:

/* Line 677 of lalr1.cc  */
#line 630 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 90:

/* Line 677 of lalr1.cc  */
#line 634 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 1)
                assert ((yysemantic_stack_[(2) - (2)].component) == 0);
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 92:

/* Line 677 of lalr1.cc  */
#line 643 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 94:

/* Line 677 of lalr1.cc  */
#line 650 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(4) - (3)].mod));
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = new ASTpathOp(*pop, mod, (yyloc));
        }
    break;

  case 95:

/* Line 677 of lalr1.cc  */
#line 657 "../../src-common/cfdg.ypp"
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
#line 667 "../../src-common/cfdg.ypp"
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
#line 676 "../../src-common/cfdg.ypp"
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
#line 685 "../../src-common/cfdg.ypp"
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
#line 697 "../../src-common/cfdg.ypp"
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
#line 711 "../../src-common/cfdg.ypp"
    { }
    break;

  case 101:

/* Line 677 of lalr1.cc  */
#line 713 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 1)
                assert((yysemantic_stack_[(1) - (1)].component) == 0);
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 102:

/* Line 677 of lalr1.cc  */
#line 721 "../../src-common/cfdg.ypp"
    { }
    break;

  case 103:

/* Line 677 of lalr1.cc  */
#line 723 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 104:

/* Line 677 of lalr1.cc  */
#line 729 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2)
                driver.pop_repContainer(driver.switchStack.top());
        }
    break;

  case 107:

/* Line 677 of lalr1.cc  */
#line 741 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(1) - (1)].component); 
        }
    break;

  case 108:

/* Line 677 of lalr1.cc  */
#line 745 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = 0; 
        }
    break;

  case 109:

/* Line 677 of lalr1.cc  */
#line 749 "../../src-common/cfdg.ypp"
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
#line 760 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
                driver.push_repContainer((yysemantic_stack_[(2) - (1)].loopObj)->mFinallyBody);
            }
        }
    break;

  case 111:

/* Line 677 of lalr1.cc  */
#line 765 "../../src-common/cfdg.ypp"
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
#line 778 "../../src-common/cfdg.ypp"
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
#line 789 "../../src-common/cfdg.ypp"
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
#line 800 "../../src-common/cfdg.ypp"
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
#line 812 "../../src-common/cfdg.ypp"
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
#line 820 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 117:

/* Line 677 of lalr1.cc  */
#line 827 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 118:

/* Line 677 of lalr1.cc  */
#line 828 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 119:

/* Line 677 of lalr1.cc  */
#line 829 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 120:

/* Line 677 of lalr1.cc  */
#line 833 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 121:

/* Line 677 of lalr1.cc  */
#line 835 "../../src-common/cfdg.ypp"
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
#line 843 "../../src-common/cfdg.ypp"
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
#line 855 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 124:

/* Line 677 of lalr1.cc  */
#line 856 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 127:

/* Line 677 of lalr1.cc  */
#line 859 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 132:

/* Line 677 of lalr1.cc  */
#line 867 "../../src-common/cfdg.ypp"
    {
            (yyval.loopObj) = (yysemantic_stack_[(2) - (1)].loopObj);
        }
    break;

  case 133:

/* Line 677 of lalr1.cc  */
#line 873 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 135:

/* Line 677 of lalr1.cc  */
#line 880 "../../src-common/cfdg.ypp"
    { }
    break;

  case 136:

/* Line 677 of lalr1.cc  */
#line 882 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 137:

/* Line 677 of lalr1.cc  */
#line 888 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), (yylocation_stack_[(2) - (1)])));
            (yyval.component) = new ASTreplacement(*r, r->entropyVal, mod, (yyloc));
        }
    break;

  case 138:

/* Line 677 of lalr1.cc  */
#line 897 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 139:

/* Line 677 of lalr1.cc  */
#line 899 "../../src-common/cfdg.ypp"
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
#line 910 "../../src-common/cfdg.ypp"
    { ++driver.mLocalStackDepth; }
    break;

  case 141:

/* Line 677 of lalr1.cc  */
#line 910 "../../src-common/cfdg.ypp"
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
#line 925 "../../src-common/cfdg.ypp"
    {
            str_ptr var((yysemantic_stack_[(5) - (2)].string));
            exp_ptr index((yysemantic_stack_[(5) - (4)].expression));
            mod_ptr mod((yysemantic_stack_[(5) - (5)].mod));
            if (driver.mCompilePhase == 2) {
                --driver.mLocalStackDepth;
                int nameIndex = driver.StringToShape(*var, (yylocation_stack_[(5) - (2)]), false);
                driver.CheckVariableName(nameIndex, (yylocation_stack_[(5) - (2)]));
                loop_ptr loop(new ASTloop(nameIndex, *var, (yylocation_stack_[(5) - (2)]), index, (yylocation_stack_[(5) - (4)]), mod));
                driver.push_repContainer(loop->mLoopBody);
                (yyval.loopObj) = loop.release();
            } else {
                (yyval.loopObj) = 0;
            }
        }
    break;

  case 143:

/* Line 677 of lalr1.cc  */
#line 941 "../../src-common/cfdg.ypp"
    {
            exp_ptr index((yysemantic_stack_[(5) - (4)].expression));
            mod_ptr mod((yysemantic_stack_[(5) - (5)].mod));
            if (driver.mCompilePhase == 2) {
                static const std::string dummyvar("~~inaccessiblevar~~");
                --driver.mLocalStackDepth;
                loop_ptr loop(new ASTloop(driver.StringToShape(dummyvar, (yylocation_stack_[(5) - (1)]), false), 
                                          dummyvar, (yylocation_stack_[(5) - (2)]), index, (yylocation_stack_[(5) - (4)]), mod));
                driver.push_repContainer(loop->mLoopBody);
                (yyval.loopObj) = loop.release();
            } else {
                (yyval.loopObj) = 0;
            }
            error((yylocation_stack_[(5) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 144:

/* Line 677 of lalr1.cc  */
#line 957 "../../src-common/cfdg.ypp"
    {
            exp_ptr count((yysemantic_stack_[(3) - (2)].expression));
            mod_ptr mod((yysemantic_stack_[(3) - (3)].mod));
            if (driver.mCompilePhase == 2) {
                static const std::string dummyvar("~~inaccessiblevar~~");
                --driver.mLocalStackDepth;
                loop_ptr loop(new ASTloop(driver.StringToShape(dummyvar, (yylocation_stack_[(3) - (1)]), false), 
                                          dummyvar, (yylocation_stack_[(3) - (1)]), count, (yylocation_stack_[(3) - (2)]), mod));
                driver.push_repContainer(loop->mLoopBody);
                (yyval.loopObj) = loop.release();
            } else {
                (yyval.loopObj) = 0;
            }
        }
    break;

  case 145:

/* Line 677 of lalr1.cc  */
#line 974 "../../src-common/cfdg.ypp"
    {
            // The loop modification is evaluated after the loop index is pushed
            // on the stack. Never the less, the scope of the loop index is the
            // body of the loop, not the modification. So we adjust the stack size
            // here and reverse it just before declaring the scope of the loop
            // index variable.
            ++driver.mLocalStackDepth;
            (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression);
        }
    break;

  case 146:

/* Line 677 of lalr1.cc  */
#line 986 "../../src-common/cfdg.ypp"
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

  case 147:

/* Line 677 of lalr1.cc  */
#line 999 "../../src-common/cfdg.ypp"
    {
            if (driver.mCompilePhase == 2) {
                driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ifObj));
                driver.push_repContainer((yysemantic_stack_[(3) - (1)].ifObj)->mElseBody);
            }
            (yyval.ifObj) = (yysemantic_stack_[(3) - (1)].ifObj);
        }
    break;

  case 148:

/* Line 677 of lalr1.cc  */
#line 1009 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (1)].modToken) != ASTmodTerm::transform)
                error((yylocation_stack_[(2) - (1)]), "Syntax error");
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            if (driver.mCompilePhase == 2) {
                ASTtransform* trans = new ASTtransform(mod, (yyloc));
                driver.push_repContainer(trans->mBody);
                (yyval.component) = trans;
            } else {
                (yyval.component) = 0;
            }
        }
    break;

  case 149:

/* Line 677 of lalr1.cc  */
#line 1024 "../../src-common/cfdg.ypp"
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
#line 1037 "../../src-common/cfdg.ypp"
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
#line 1066 "../../src-common/cfdg.ypp"
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
#line 1079 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), true);
        }
    break;

  case 153:

/* Line 677 of lalr1.cc  */
#line 1084 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), false);
        }
    break;

  case 154:

/* Line 677 of lalr1.cc  */
#line 1091 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(3) - (2)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), true);
        }
    break;

  case 155:

/* Line 677 of lalr1.cc  */
#line 1096 "../../src-common/cfdg.ypp"
    {
            mod_ptr mod((yysemantic_stack_[(5) - (3)].mod));
            (yyval.mod) = driver.MakeModification(mod, (yyloc), false);
        }
    break;

  case 156:

/* Line 677 of lalr1.cc  */
#line 1103 "../../src-common/cfdg.ypp"
    {
            term_ptr mod((yysemantic_stack_[(2) - (2)].term));
            driver.MakeModTerm((yysemantic_stack_[(2) - (1)].mod)->modExp, mod);
            (yyval.mod) = (yysemantic_stack_[(2) - (1)].mod);
        }
    break;

  case 157:

/* Line 677 of lalr1.cc  */
#line 1108 "../../src-common/cfdg.ypp"
    {
            static const yy::location def;
            ASTmodification* m = new ASTmodification(def);
            m->flags = 0;
            (yyval.mod) = m;
        }
    break;

  case 158:

/* Line 677 of lalr1.cc  */
#line 1117 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].expression));
            (yyval.term) = new ASTmodTerm((ASTmodTerm::modTypeEnum)((yysemantic_stack_[(2) - (1)].modToken)), mod.release(), (yyloc));
        }
    break;

  case 159:

/* Line 677 of lalr1.cc  */
#line 1122 "../../src-common/cfdg.ypp"
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

  case 160:

/* Line 677 of lalr1.cc  */
#line 1132 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.term) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 161:

/* Line 677 of lalr1.cc  */
#line 1137 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.term) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 162:

/* Line 677 of lalr1.cc  */
#line 1144 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTcons::Cons((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 163:

/* Line 677 of lalr1.cc  */
#line 1148 "../../src-common/cfdg.ypp"
    { 
            (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); 
        }
    break;

  case 164:

/* Line 677 of lalr1.cc  */
#line 1154 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 165:

/* Line 677 of lalr1.cc  */
#line 1156 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 166:

/* Line 677 of lalr1.cc  */
#line 1158 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 167:

/* Line 677 of lalr1.cc  */
#line 1160 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 168:

/* Line 677 of lalr1.cc  */
#line 1162 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 169:

/* Line 677 of lalr1.cc  */
#line 1164 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 170:

/* Line 677 of lalr1.cc  */
#line 1166 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 171:

/* Line 677 of lalr1.cc  */
#line 1171 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 172:

/* Line 677 of lalr1.cc  */
#line 1178 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 173:

/* Line 677 of lalr1.cc  */
#line 1180 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 174:

/* Line 677 of lalr1.cc  */
#line 1182 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 175:

/* Line 677 of lalr1.cc  */
#line 1184 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 176:

/* Line 677 of lalr1.cc  */
#line 1189 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 177:

/* Line 677 of lalr1.cc  */
#line 1194 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression));   }
    break;

  case 178:

/* Line 677 of lalr1.cc  */
#line 1196 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('+', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 179:

/* Line 677 of lalr1.cc  */
#line 1198 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('-', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 180:

/* Line 677 of lalr1.cc  */
#line 1200 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('_', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 181:

/* Line 677 of lalr1.cc  */
#line 1202 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('*', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 182:

/* Line 677 of lalr1.cc  */
#line 1204 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('/', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 183:

/* Line 677 of lalr1.cc  */
#line 1206 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 184:

/* Line 677 of lalr1.cc  */
#line 1208 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 185:

/* Line 677 of lalr1.cc  */
#line 1210 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('!', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 186:

/* Line 677 of lalr1.cc  */
#line 1212 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('^', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 187:

/* Line 677 of lalr1.cc  */
#line 1214 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('<', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 188:

/* Line 677 of lalr1.cc  */
#line 1216 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('L', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 189:

/* Line 677 of lalr1.cc  */
#line 1218 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('>', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 190:

/* Line 677 of lalr1.cc  */
#line 1220 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('G', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 191:

/* Line 677 of lalr1.cc  */
#line 1222 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('=', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 192:

/* Line 677 of lalr1.cc  */
#line 1224 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('n', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 193:

/* Line 677 of lalr1.cc  */
#line 1226 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('&', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 194:

/* Line 677 of lalr1.cc  */
#line 1228 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('|', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 195:

/* Line 677 of lalr1.cc  */
#line 1230 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('X', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 196:

/* Line 677 of lalr1.cc  */
#line 1232 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 197:

/* Line 677 of lalr1.cc  */
#line 1234 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].mod); }
    break;

  case 198:

/* Line 677 of lalr1.cc  */
#line 1238 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 199:

/* Line 677 of lalr1.cc  */
#line 1243 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), true);
        }
    break;

  case 200:

/* Line 677 of lalr1.cc  */
#line 1249 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 201:

/* Line 677 of lalr1.cc  */
#line 1255 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 202:

/* Line 677 of lalr1.cc  */
#line 1262 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 203:

/* Line 677 of lalr1.cc  */
#line 1267 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 204:

/* Line 677 of lalr1.cc  */
#line 1273 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 205:

/* Line 677 of lalr1.cc  */
#line 1279 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args(new ASTexpression((yylocation_stack_[(4) - (1)]) + (yylocation_stack_[(4) - (4)])));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 206:

/* Line 677 of lalr1.cc  */
#line 1285 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;



/* Line 677 of lalr1.cc  */
#line 2697 "cfdg.tab.cpp"
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
  const short int CfdgParser::yypact_ninf_ = -243;
  const short int
  CfdgParser::yypact_[] =
  {
       221,  -243,  -243,    34,   809,   828,  -243,     2,  -243,    30,
      87,     4,    88,  -243,    12,   146,  -243,    88,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,    90,  -243,   140,  -243,
     141,   176,   189,   190,   174,    88,   185,   146,   166,    88,
    -243,  -243,  -243,  -243,  -243,  -243,   323,   184,  -243,  -243,
    -243,   192,   194,  -243,  -243,   181,   218,   202,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,   204,   205,  -243,   205,    20,   251,  -243,  -243,   252,
    -243,   239,   146,  -243,   212,   213,  -243,   323,  -243,   323,
     323,   323,   215,  -243,   680,  -243,  -243,    25,  -243,  -243,
    -243,  -243,  -243,  -243,     3,    99,    26,    97,   198,   219,
     126,  -243,  -243,  -243,  -243,  -243,  -243,    -7,  -243,  -243,
    -243,  -243,   323,   225,   220,   220,   220,   380,  -243,    13,
     323,   323,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   323,   323,   323,   323,   323,   323,   245,   311,
     222,   223,     5,     8,   226,   102,  -243,   323,  -243,  -243,
    -243,  -243,   270,   276,   276,   276,   276,   228,   107,   128,
     186,   110,  -243,  -243,  -243,    88,   244,  -243,  -243,  -243,
     105,  -243,  -243,  -243,  -243,   273,     1,   149,  -243,  -243,
    -243,  -243,   104,   235,  -243,   410,  -243,    59,   125,  -243,
      -5,   179,  -243,   440,   236,  -243,   470,  -243,    89,  -243,
     121,   121,   358,   358,   358,   358,   773,   773,   753,   732,
     710,   680,   155,   155,   155,   220,   220,   220,   204,   288,
      22,   219,   680,   323,   323,  -243,  -243,  -243,  -243,   219,
    -243,   266,  -243,   680,  -243,  -243,  -243,  -243,   285,  -243,
    -243,  -243,  -243,  -243,   246,   248,  -243,  -243,   186,   186,
     323,   186,    46,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,    88,   247,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,   126,  -243,
    -243,  -243,  -243,  -243,   242,   219,   323,   323,  -243,   500,
     530,  -243,  -243,   560,   276,   168,  -243,    11,   323,   284,
    -243,  -243,   590,   233,   186,   186,  -243,    88,   129,   108,
     169,  -243,  -243,  -243,   219,   219,  -243,  -243,  -243,  -243,
    -243,   254,   323,  -243,  -243,   276,   620,  -243,   650,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,   350,
    -243,  -243,  -243,  -243
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
      38,     0,     0,    11,    12,    48,    61,    69,    27,   157,
     157,    51,    49,    26,    28,    42,    43,    39,    50,   134,
      93,    89,    78,    65,    78,     0,     0,    36,    34,     0,
      37,     0,     0,    35,     0,   206,   172,     0,   173,     0,
       0,     0,   157,   197,    52,   174,    59,     0,    91,    91,
      32,    33,    62,    31,     0,     0,     0,     0,     0,    47,
       0,    58,    66,    80,    79,    84,    82,     0,    54,    53,
      44,    40,     0,     0,   185,   183,   184,     0,   157,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    89,     0,     0,    60,     0,   108,   107,
      90,   116,   109,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   153,   156,   152,     0,     0,    63,   138,   133,
       0,   125,   126,   129,   131,   130,     0,     0,    70,   120,
      92,   122,     0,     0,    88,     0,    46,     0,     0,    76,
       0,     0,    83,     0,     0,   202,     0,   196,     0,   154,
     175,   176,   188,   187,   190,   189,   191,   192,   193,   194,
     195,   177,   179,   178,   180,   181,   182,   186,    89,     0,
     206,     0,   145,     0,     0,    56,   148,    55,   118,     0,
     117,     0,   119,    57,   110,    91,   132,   101,   112,   113,
     114,   105,    67,    68,     0,   201,   164,   165,     0,     0,
       0,   158,   163,   167,   160,   161,   137,   140,   134,   139,
     136,   128,   127,   124,    95,   123,   157,     0,     0,    93,
     103,   121,    87,    86,    74,    72,    73,    71,     0,    77,
      81,   204,   205,   203,     0,     0,     0,     0,   144,     0,
       0,    98,    97,     0,     0,     0,   147,     0,     0,     0,
     168,   169,     0,   162,     0,     0,   159,     0,     0,     0,
       0,    75,   155,    99,     0,     0,   146,   149,    96,   111,
     100,     0,     0,   115,   104,     0,     0,   198,     0,   166,
     170,   171,   141,   135,    94,   102,   143,   142,   151,     0,
     106,   200,   199,   150
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yypgoto_[] =
  {
      -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
     307,    37,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,   312,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,    28,  -243,   249,   117,  -243,   283,  -124,
     -86,    41,   135,  -243,  -157,  -243,  -243,  -243,   -87,  -243,
    -243,  -243,  -243,  -243,    62,  -243,   153,  -243,  -103,  -243,
    -243,   -49,  -243,  -243,  -243,  -243,  -243,   -11,  -104,   -57,
    -243,  -243,  -242,   -44,  -243,  -243
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yydefgoto_[] =
  {
        -1,     3,     4,     5,    40,    18,    19,    41,    20,    42,
      21,    67,    82,    44,    22,    23,    24,    25,    45,    46,
     157,   158,    47,    48,    49,    26,    27,    51,    52,    53,
      54,    28,    29,   199,   200,   111,   116,   117,    76,   109,
      97,   107,   189,   159,   246,   281,   307,   334,   247,   304,
     161,   190,   191,   162,   106,   269,   178,   179,   180,   317,
     163,   231,   164,   165,   166,   167,   335,   274,    93,   104,
     173,   261,   262,   232,   263,    95
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char CfdgParser::yytable_ninf_ = -1;
  const unsigned short int
  CfdgParser::yytable_[] =
  {
        61,    62,    94,   105,   192,   196,    68,   248,   249,   250,
     160,   272,   168,   169,    58,   235,   310,   311,   237,   313,
     170,   171,    63,    77,    78,   331,    55,   332,    83,   239,
     170,   171,   297,   148,     6,   129,   149,   113,   150,   201,
     151,   288,   152,   124,   114,   125,   126,   127,   236,   153,
     175,   154,   176,   202,    56,   289,   273,    59,   155,    60,
      59,    92,    60,   108,   195,   172,   238,    64,   314,   315,
     333,   208,   340,   341,    80,   209,   284,   123,   203,   206,
     115,   160,   160,   285,   156,   177,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   295,   181,   170,   171,   182,   316,
     183,    57,   184,   243,   185,   148,   170,   171,   149,   121,
     150,   186,   151,   176,   152,   170,   171,   298,   277,   175,
     187,   153,   197,   154,   264,   301,   148,   278,   265,   149,
     155,   150,   286,   151,    59,   152,    60,   329,    69,   287,
     198,   294,   153,   175,   154,   176,   188,   241,   174,   305,
     242,   155,   279,   268,   266,    71,   252,   344,   142,   143,
     144,   145,   146,    65,    66,   147,   148,   181,   350,   149,
     182,   150,   183,   151,   184,   152,   185,   253,   343,   299,
     300,   323,   153,   186,   154,   176,   113,   303,    70,   254,
      72,   155,   187,   114,   275,   145,   146,   276,   193,   147,
     255,    84,   256,    56,    74,    73,   312,   192,   160,   319,
     346,   347,    85,    81,    86,     1,     2,   330,   345,    75,
      59,   257,    60,   258,   259,   204,   100,   101,    84,    87,
      75,   260,    96,    88,   102,    89,    90,   324,   325,    85,
      98,    86,    99,    91,    92,   314,   315,   103,   194,   108,
     110,   118,   119,   120,   336,   338,    87,   122,   123,   228,
      88,   128,    89,    90,   147,    92,   240,   233,   234,    84,
      91,    92,   244,   271,   148,   205,   251,   149,   349,   150,
      85,   151,    86,   152,   267,   282,   292,    84,   296,   306,
     153,   308,   154,   309,   322,   276,   342,    87,    85,   155,
      86,    88,    43,    89,    90,   348,   321,    50,   290,    79,
     320,    91,    92,   112,    84,    87,   302,   280,   229,    88,
     318,    89,    90,   270,   245,   230,    84,    86,     0,    91,
      92,     0,     0,     0,   337,     0,     0,    85,     0,    86,
       0,     0,    87,     0,     0,     0,    88,     0,    89,    90,
       0,     0,     0,     0,    87,     0,    91,    92,    88,     0,
      89,    90,   130,   131,     0,     0,     0,     0,    91,    92,
     130,   131,     0,     0,     0,   132,   133,   134,   135,   136,
     137,     0,   138,   139,   140,     0,   141,   142,   143,   144,
     145,   146,   130,   131,   147,   142,   143,   144,   145,   146,
       0,   353,   147,     0,     0,   132,   133,   134,   135,   136,
     137,     0,   138,   139,   140,     0,   141,   142,   143,   144,
     145,   146,   130,   131,   147,     0,     0,     0,     0,     0,
     207,     0,     0,     0,     0,   132,   133,   134,   135,   136,
     137,     0,   138,   139,   140,     0,   141,   142,   143,   144,
     145,   146,   130,   131,   147,     0,     0,     0,     0,     0,
     283,     0,     0,     0,     0,   132,   133,   134,   135,   136,
     137,     0,   138,   139,   140,     0,   141,   142,   143,   144,
     145,   146,   130,   131,   147,     0,     0,     0,     0,     0,
     291,     0,     0,     0,     0,   132,   133,   134,   135,   136,
     137,     0,   138,   139,   140,     0,   141,   142,   143,   144,
     145,   146,   130,   131,   147,     0,     0,     0,     0,     0,
     293,     0,     0,     0,     0,   132,   133,   134,   135,   136,
     137,     0,   138,   139,   140,     0,   141,   142,   143,   144,
     145,   146,   130,   131,   147,     0,     0,     0,     0,     0,
     326,     0,     0,     0,     0,   132,   133,   134,   135,   136,
     137,     0,   138,   139,   140,     0,   141,   142,   143,   144,
     145,   146,   130,   131,   147,     0,     0,     0,     0,     0,
     327,     0,     0,     0,     0,   132,   133,   134,   135,   136,
     137,     0,   138,   139,   140,     0,   141,   142,   143,   144,
     145,   146,   130,   131,   147,     0,     0,     0,     0,     0,
     328,     0,     0,     0,     0,   132,   133,   134,   135,   136,
     137,     0,   138,   139,   140,     0,   141,   142,   143,   144,
     145,   146,   130,   131,   147,     0,     0,     0,     0,     0,
     339,     0,     0,     0,     0,   132,   133,   134,   135,   136,
     137,     0,   138,   139,   140,     0,   141,   142,   143,   144,
     145,   146,   130,   131,   147,     0,     0,     0,     0,     0,
     351,     0,     0,     0,     0,   132,   133,   134,   135,   136,
     137,     0,   138,   139,   140,     0,   141,   142,   143,   144,
     145,   146,   130,   131,   147,     0,     0,     0,     0,     0,
     352,     0,     0,     0,     0,   132,   133,   134,   135,   136,
     137,     0,   138,   139,   140,     0,   141,   142,   143,   144,
     145,   146,   130,   131,   147,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   132,   133,   134,   135,   136,
     137,     0,   138,   139,   130,   131,     0,   142,   143,   144,
     145,   146,     0,     0,   147,     0,     0,   132,   133,   134,
     135,   136,   137,     0,   138,   130,   131,     0,     0,   142,
     143,   144,   145,   146,     0,     0,   147,     0,   132,   133,
     134,   135,   136,   137,     0,   130,   131,     0,     0,     0,
     142,   143,   144,   145,   146,     0,     0,   147,   132,   133,
     134,   135,     7,     0,     0,     8,     9,    10,     0,     0,
     142,   143,   144,   145,   146,     0,    11,   147,    12,     0,
      13,    30,     0,    14,    31,    32,    33,     0,    15,    16,
      17,     0,     0,     0,     0,    34,     0,    35,     0,    13,
       0,     0,    36,     0,     0,     0,     0,    37,    38,    39
  };

  /* YYCHECK.  */
  const short int
  CfdgParser::yycheck_[] =
  {
        11,    12,    46,    60,   107,   109,    17,   164,   165,   166,
      97,    10,    98,    99,    10,    10,   258,   259,    10,   261,
      17,    18,    10,    34,    35,    14,    24,    16,    39,   153,
      17,    18,    10,     8,     0,    92,    11,    17,    13,    46,
      15,    46,    17,    87,    24,    89,    90,    91,   152,    24,
      24,    26,    26,    60,    24,    60,    55,    56,    33,    58,
      56,    56,    58,    55,   108,    62,    58,    55,    22,    23,
      59,   128,   314,   315,    37,    62,    17,    55,   122,   123,
      60,   168,   169,    24,    59,    59,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   228,     8,    17,    18,    11,    63,
      13,    24,    15,   157,    17,     8,    17,    18,    11,    82,
      13,    24,    15,    26,    17,    17,    18,   231,    24,    24,
      33,    24,     6,    26,    24,   239,     8,    33,    28,    11,
      33,    13,    17,    15,    56,    17,    58,   304,    58,    24,
      24,    62,    24,    24,    26,    26,    59,    55,    59,   245,
      58,    33,    58,    58,   175,    24,    59,    59,    47,    48,
      49,    50,    51,    27,    28,    54,     8,     8,   335,    11,
      11,    13,    13,    15,    15,    17,    17,    59,    59,   233,
     234,   295,    24,    24,    26,    26,    17,   241,    58,    13,
      24,    33,    33,    24,    55,    50,    51,    58,    10,    54,
      24,    13,    26,    24,    24,    26,   260,   320,   305,   276,
     324,   325,    24,    57,    26,     4,     5,    59,    59,    55,
      56,    45,    58,    47,    48,    10,    55,    56,    13,    41,
      55,    55,    58,    45,    26,    47,    48,   296,   297,    24,
      58,    26,    58,    55,    56,    22,    23,    55,    60,    55,
      55,    10,    10,    24,   308,   309,    41,    55,    55,    24,
      45,    56,    47,    48,    54,    56,    50,    55,    55,    13,
      55,    56,    12,    10,     8,    60,    58,    11,   332,    13,
      24,    15,    26,    17,    50,    60,    60,    13,    10,    14,
      24,    55,    26,    55,    62,    58,   317,    41,    24,    33,
      26,    45,     5,    47,    48,    61,   288,     5,   201,    36,
     279,    55,    56,    74,    13,    41,    60,   192,    17,    45,
     268,    47,    48,   180,    58,    24,    13,    26,    -1,    55,
      56,    -1,    -1,    -1,    60,    -1,    -1,    24,    -1,    26,
      -1,    -1,    41,    -1,    -1,    -1,    45,    -1,    47,    48,
      -1,    -1,    -1,    -1,    41,    -1,    55,    56,    45,    -1,
      47,    48,    22,    23,    -1,    -1,    -1,    -1,    55,    56,
      22,    23,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    47,    48,    49,
      50,    51,    22,    23,    54,    47,    48,    49,    50,    51,
      -1,    61,    54,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    47,    48,    49,
      50,    51,    22,    23,    54,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    47,    48,    49,
      50,    51,    22,    23,    54,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    47,    48,    49,
      50,    51,    22,    23,    54,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    47,    48,    49,
      50,    51,    22,    23,    54,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    47,    48,    49,
      50,    51,    22,    23,    54,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    47,    48,    49,
      50,    51,    22,    23,    54,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    47,    48,    49,
      50,    51,    22,    23,    54,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    47,    48,    49,
      50,    51,    22,    23,    54,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    47,    48,    49,
      50,    51,    22,    23,    54,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    47,    48,    49,
      50,    51,    22,    23,    54,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    47,    48,    49,
      50,    51,    22,    23,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    42,    43,    22,    23,    -1,    47,    48,    49,
      50,    51,    -1,    -1,    54,    -1,    -1,    35,    36,    37,
      38,    39,    40,    -1,    42,    22,    23,    -1,    -1,    47,
      48,    49,    50,    51,    -1,    -1,    54,    -1,    35,    36,
      37,    38,    39,    40,    -1,    22,    23,    -1,    -1,    -1,
      47,    48,    49,    50,    51,    -1,    -1,    54,    35,    36,
      37,    38,     3,    -1,    -1,     6,     7,     8,    -1,    -1,
      47,    48,    49,    50,    51,    -1,    17,    54,    19,    -1,
      21,     3,    -1,    24,     6,     7,     8,    -1,    29,    30,
      31,    -1,    -1,    -1,    -1,    17,    -1,    19,    -1,    21,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    30,    31
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  CfdgParser::yystos_[] =
  {
         0,     4,     5,    65,    66,    67,     0,     3,     6,     7,
       8,    17,    19,    21,    24,    29,    30,    31,    69,    70,
      72,    74,    78,    79,    80,    81,    89,    90,    95,    96,
       3,     6,     7,     8,    17,    19,    24,    29,    30,    31,
      68,    71,    73,    74,    77,    82,    83,    86,    87,    88,
      89,    91,    92,    93,    94,    24,    24,    24,    10,    56,
      58,   131,   131,    10,    55,    27,    28,    75,   131,    58,
      58,    24,    24,    26,    24,    55,   102,   131,   131,   102,
      75,    57,    76,   131,    13,    24,    26,    41,    45,    47,
      48,    55,    56,   132,   137,   139,    58,   104,    58,    58,
      55,    56,    26,    55,   133,   133,   118,   105,    55,   103,
      55,    99,    99,    17,    24,    60,   100,   101,    10,    10,
      24,    75,    55,    55,   137,   137,   137,   137,    56,   133,
      22,    23,    35,    36,    37,    38,    39,    40,    42,    43,
      44,    46,    47,    48,    49,    50,    51,    54,     8,    11,
      13,    15,    17,    24,    26,    33,    59,    84,    85,   107,
     112,   114,   117,   124,   126,   127,   128,   129,   104,   104,
      17,    18,    62,   134,    59,    24,    26,    59,   120,   121,
     122,     8,    11,    13,    15,    17,    24,    33,    59,   106,
     115,   116,   122,    10,    60,   137,   132,     6,    24,    97,
      98,    46,    60,   137,    10,    60,   137,    60,   133,    62,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,    24,    17,
      24,   125,   137,    55,    55,    10,   132,    10,    58,   103,
      50,    55,    58,   137,    12,    58,   108,   112,   108,   108,
     108,    58,    59,    59,    13,    24,    26,    45,    47,    48,
      55,   135,   136,   138,    24,    28,   131,    50,    58,   119,
     120,    10,    10,    55,   131,    55,    58,    24,    33,    58,
     106,   109,    60,    60,    17,    24,    17,    24,    46,    60,
     100,    60,    60,    60,    62,   103,    10,    10,   132,   137,
     137,   132,    60,   137,   113,   104,    14,   110,    55,    55,
     136,   136,   137,   136,    22,    23,    63,   123,   118,   133,
     105,    97,    62,   132,   125,   125,    60,    60,    60,   108,
      59,    14,    16,    59,   111,   130,   137,    60,   137,    60,
     136,   136,   131,    59,    59,    59,   132,   132,    61,   137,
     108,    60,    60,    61
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
     295,   296,   297,   298,   299,   300,    44,    45,    43,    95,
      42,    47,   301,   302,    94,    40,    91,    64,   123,   125,
      41,    58,    93,   124
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  CfdgParser::yyr1_[] =
  {
         0,    64,    65,    65,    66,    66,    67,    67,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    71,    71,    71,    72,
      73,    74,    75,    75,    76,    76,    77,    77,    78,    79,
      80,    81,    82,    83,    83,    84,    84,    85,    86,    87,
      88,    89,    89,    90,    91,    91,    92,    93,    94,    95,
      96,    97,    97,    97,    97,    98,    98,    99,    99,   100,
     100,   101,   101,   102,   102,   102,   103,   103,   103,   103,
     104,   104,   105,   105,   106,   106,   107,   107,   107,   107,
     108,   108,   109,   109,   110,   110,   111,   112,   112,   112,
     113,   112,   112,   112,   112,   112,   112,   114,   114,   114,
     115,   115,   115,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   117,   118,   118,   119,   119,   120,   121,   121,
     123,   122,   124,   124,   124,   125,   126,   127,   128,   129,
     130,   130,   131,   131,   132,   132,   133,   133,   134,   134,
     134,   134,   135,   135,   136,   136,   136,   136,   136,   136,
     136,   136,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   138,   138,
     138,   138,   139,   139,   139,   139,   139
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
       1,     1,     2,     2,     0,     3,     1,     2,     1,     2,
       0,     4,     5,     5,     3,     1,     4,     3,     2,     4,
       3,     2,     3,     3,     3,     5,     2,     0,     2,     3,
       2,     2,     2,     1,     1,     1,     3,     1,     2,     2,
       3,     3,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     3,     4,
       4,     1,     3,     4,     4,     4,     1
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const CfdgParser::yytname_[] =
  {
    "$end", "error", "$undefined", "STARTSHAPE", "CFDG2", "CFDG3", "SHAPE",
  "RULE", "PATH", "DEFINE", "BECOMES", "LOOP", "FINALLY", "IF", "ELSE",
  "SWITCH", "CASE", "MODTYPE", "PARAM", "BACKGROUND", "BADEOF", "GOODEOF",
  "RANGEOP", "PLUSMINUSOP", "USER_STRING", "USER_INTEGER", "USER_RATIONAL",
  "USER_FILENAME", "USER_QSTRING", "INCLUDE", "IMPORT", "TILE",
  "PARAMETERS", "USER_PATHOP", "STROKEWIDTH", "LE", "LT", "GE", "GT", "EQ",
  "NEQ", "NOT", "AND", "OR", "XOR", "CF_INFINITY", "','", "'-'", "'+'",
  "'_'", "'*'", "'/'", "POS", "NEG", "'^'", "'('", "'['", "'@'", "'{'",
  "'}'", "')'", "':'", "']'", "'|'", "$accept", "choose", "cfdg2", "cfdg3",
  "statement", "statement_v2", "v3clues", "v2stuff", "inclusion", "import",
  "eof", "fileString", "fileNameSpace", "initialization",
  "initialization_v2", "background", "tile", "size", "global_definition",
  "global_definition_header", "definition_header", "definition", "shape",
  "shape_singleton_header", "shape_singleton", "rule_header_v2", "rule_v2",
  "rule_header", "path_header", "rule", "path", "path_header_v2",
  "path_v2", "parameter", "buncha_parameters", "parameter_list",
  "function_parameter", "buncha_function_parameters",
  "function_parameter_list", "parameter_spec", "buncha_elements",
  "buncha_pathOps_v2", "pathOp_simple_v2", "element_simple",
  "one_or_more_elements", "one_or_more_pathOp_v2", "caseBody",
  "caseBody_element", "element", "$@1", "element_v2clue", "pathOp_v2",
  "pathOp_v3clues", "element_loop", "buncha_replacements_v2",
  "one_or_more_replacements_v2", "replacement_simple_v2", "replacement_v2",
  "loopHeader_v2", "$@2", "loopHeader", "loopexp", "ifHeader",
  "ifElseHeader", "transHeader", "switchHeader", "caseHeader",
  "modification_v2", "modification", "buncha_adjustments", "adjustment",
  "explist", "exp", "exp2", "expfunc", "exp2func", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const CfdgParser::rhs_number_type
  CfdgParser::yyrhs_[] =
  {
        65,     0,    -1,     4,    66,    -1,     5,    67,    -1,    66,
      69,    -1,    -1,    67,    68,    -1,    -1,    77,    -1,    73,
      -1,    74,    -1,    93,    -1,    94,    -1,    86,    -1,    88,
      -1,    82,    -1,    71,    -1,    78,    -1,    79,    -1,    72,
      -1,    74,    -1,    80,    -1,    81,    -1,    90,    -1,    96,
      -1,    70,    -1,    24,    10,    -1,    17,    10,    -1,    24,
      55,    -1,    30,    -1,     6,    -1,     8,    24,    55,    -1,
       3,    24,    55,    -1,     3,    24,    56,    -1,    19,   131,
      -1,    31,   131,    -1,    17,   131,    -1,    29,    75,    -1,
      89,    -1,    29,    75,    -1,    30,    76,    75,    -1,    21,
      -1,    27,    -1,    28,    -1,    57,    24,    -1,    -1,     3,
      24,   103,   132,    -1,     3,    24,   103,    -1,     3,    24,
      -1,    19,   131,    -1,    31,   131,    -1,    17,   131,    -1,
      83,   137,    -1,    24,   102,    10,    -1,    17,   102,    10,
      -1,    24,    10,    -1,    17,    10,    -1,    84,   137,    -1,
       6,    24,    99,    -1,    86,    58,    -1,    87,   104,    59,
      -1,     7,    24,    -1,     7,    24,    26,    -1,    89,    58,
     118,    59,    -1,     7,    -1,     7,    26,    -1,     8,    24,
      99,    -1,    91,    58,   104,    59,    -1,    92,    58,   104,
      59,    -1,     8,    24,    -1,    95,    58,   105,    59,    -1,
      24,    24,    -1,     6,    24,    -1,    24,    17,    -1,     6,
      17,    -1,    98,    46,    97,    -1,    97,    -1,    55,    98,
      60,    -1,    -1,    24,    -1,    17,    -1,   101,    46,   100,
      -1,   100,    -1,    55,   101,    60,    -1,    55,    60,    -1,
      -1,    55,   137,    60,    -1,    55,    10,    60,    -1,    55,
      60,    -1,    -1,   104,   112,    -1,    -1,   105,   115,    -1,
      -1,    33,    58,   133,    59,    -1,    24,   131,    -1,    33,
      55,   137,    60,    -1,    33,    55,    60,    -1,    24,   103,
     132,    -1,     8,    24,   103,   132,    -1,    58,   104,    59,
      -1,   112,    -1,    58,   105,    59,    -1,   106,    -1,   110,
     111,    -1,    -1,   130,   108,    -1,   107,    -1,    85,    -1,
     117,    -1,    -1,   117,    12,   113,   108,    -1,   126,   108,
      -1,   127,   108,    -1,   128,   108,    -1,   129,    58,   110,
      59,    -1,   114,    -1,    26,    50,    -1,    24,    58,    -1,
      33,    58,    -1,   106,    -1,   122,   109,    -1,   116,    -1,
      33,    55,    -1,    24,    55,    -1,     8,    -1,    11,    -1,
      24,    10,    -1,    17,    10,    -1,    13,    -1,    17,    -1,
      15,    -1,   124,   108,    -1,   118,   121,    -1,    -1,    58,
     118,    59,    -1,   120,    -1,    24,   131,    -1,   120,    -1,
     122,   119,    -1,    -1,    26,    50,   123,   131,    -1,    11,
      24,    10,   125,   132,    -1,    11,    17,    10,   125,   132,
      -1,    11,   125,   132,    -1,   137,    -1,    13,    55,   137,
      60,    -1,   126,   108,    14,    -1,    17,   132,    -1,    15,
      55,   137,    60,    -1,    16,   137,    61,    -1,    14,    61,
      -1,    58,   133,    59,    -1,    56,   133,    62,    -1,    56,
     133,    62,    -1,    56,    56,   133,    62,    62,    -1,   133,
     134,    -1,    -1,    17,   135,    -1,    17,   136,    63,    -1,
      18,    24,    -1,    18,    28,    -1,   135,   136,    -1,   136,
      -1,    26,    -1,    45,    -1,    55,   137,    60,    -1,   138,
      -1,    47,   136,    -1,    48,   136,    -1,   136,    22,   136,
      -1,   136,    23,   136,    -1,    26,    -1,    45,    -1,   139,
      -1,   137,    22,   137,    -1,   137,    23,   137,    -1,   137,
      46,   137,    -1,   137,    48,   137,    -1,   137,    47,   137,
      -1,   137,    49,   137,    -1,   137,    50,   137,    -1,   137,
      51,   137,    -1,    47,   137,    -1,    48,   137,    -1,    41,
     137,    -1,   137,    54,   137,    -1,   137,    36,   137,    -1,
     137,    35,   137,    -1,   137,    38,   137,    -1,   137,    37,
     137,    -1,   137,    39,   137,    -1,   137,    40,   137,    -1,
     137,    42,   137,    -1,   137,    43,   137,    -1,   137,    44,
     137,    -1,    55,   137,    60,    -1,   132,    -1,    24,    55,
      60,    -1,    24,    55,   137,    60,    -1,    13,    55,   137,
      60,    -1,    24,    -1,    24,    55,    60,    -1,    24,    55,
     137,    60,    -1,    13,    55,   137,    60,    -1,    24,    55,
      10,    60,    -1,    24,    -1
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
     368,   370,   372,   375,   378,   379,   383,   385,   388,   390,
     393,   394,   399,   405,   411,   415,   417,   422,   426,   429,
     434,   438,   441,   445,   449,   453,   459,   462,   463,   466,
     470,   473,   476,   479,   481,   483,   485,   489,   491,   494,
     497,   501,   505,   507,   509,   511,   515,   519,   523,   527,
     531,   535,   539,   543,   546,   549,   552,   556,   560,   564,
     568,   572,   576,   580,   584,   588,   592,   596,   598,   602,
     607,   612,   614,   618,   623,   628,   633
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  CfdgParser::yyrline_[] =
  {
         0,   182,   182,   182,   185,   190,   194,   199,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   238,   239,   240,   241,
     242,   243,   244,   245,   249,   250,   251,   252,   253,   257,
     266,   277,   284,   284,   287,   288,   292,   305,   319,   330,
     340,   350,   365,   374,   378,   386,   390,   398,   407,   423,
     437,   446,   455,   470,   478,   490,   507,   532,   541,   551,
     564,   571,   577,   583,   588,   594,   595,   599,   600,   604,
     610,   616,   617,   621,   622,   623,   627,   628,   629,   630,
     634,   639,   643,   646,   650,   657,   667,   676,   685,   697,
     711,   713,   721,   723,   729,   733,   737,   741,   745,   749,
     760,   760,   778,   789,   800,   811,   820,   827,   828,   829,
     833,   835,   843,   855,   856,   857,   858,   859,   860,   861,
     862,   863,   867,   873,   876,   880,   882,   888,   897,   899,
     910,   910,   925,   941,   957,   974,   986,   999,  1009,  1024,
    1037,  1066,  1079,  1084,  1091,  1096,  1103,  1108,  1117,  1122,
    1132,  1137,  1144,  1148,  1154,  1156,  1158,  1160,  1162,  1164,
    1166,  1171,  1178,  1180,  1182,  1184,  1189,  1194,  1196,  1198,
    1200,  1202,  1204,  1206,  1208,  1210,  1212,  1214,  1216,  1218,
    1220,  1222,  1224,  1226,  1228,  1230,  1232,  1234,  1238,  1243,
    1249,  1255,  1262,  1267,  1273,  1279,  1285
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
      55,    60,    50,    48,    46,    47,     2,    51,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,     2,
       2,     2,     2,     2,    57,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    56,     2,    62,    54,    49,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,    63,    59,     2,     2,     2,     2,
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
      45,    52,    53
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int CfdgParser::yyeof_ = 0;
  const int CfdgParser::yylast_ = 859;
  const int CfdgParser::yynnts_ = 76;
  const int CfdgParser::yyempty_ = -2;
  const int CfdgParser::yyfinal_ = 6;
  const int CfdgParser::yyterror_ = 1;
  const int CfdgParser::yyerrcode_ = 256;
  const int CfdgParser::yyntokens_ = 64;

  const unsigned int CfdgParser::yyuser_token_number_max_ = 302;
  const CfdgParser::token_number_type CfdgParser::yyundef_token_ = 2;


} // yy

/* Line 1053 of lalr1.cc  */
#line 3569 "cfdg.tab.cpp"


/* Line 1055 of lalr1.cc  */
#line 1291 "../../src-common/cfdg.ypp"


void yy::CfdgParser::error(const CfdgParser::location_type& l, const std::string& m)
{
    driver.mWant2ndPass = false;
    driver.error(l, m);
}

