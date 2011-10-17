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
#line 166 "../../src-common/cfdg.ypp"

#include "scanner.h"
#include "math.h"
#include "builder.h"
	
#undef yylex
#define yylex driver.lexer->lex


/* Line 316 of lalr1.cc  */
#line 88 "cfdg.tab.cpp"

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
#line 154 "cfdg.tab.cpp"
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
#line 153 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 261 "cfdg.tab.cpp"
	break;
      case 27: /* "USER_FILENAME" */

/* Line 479 of lalr1.cc  */
#line 153 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 270 "cfdg.tab.cpp"
	break;
      case 28: /* "USER_QSTRING" */

/* Line 479 of lalr1.cc  */
#line 153 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 279 "cfdg.tab.cpp"
	break;
      case 33: /* "USER_PATHOP" */

/* Line 479 of lalr1.cc  */
#line 153 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 288 "cfdg.tab.cpp"
	break;
      case 67: /* "statement" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 297 "cfdg.tab.cpp"
	break;
      case 68: /* "statement_v2" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 306 "cfdg.tab.cpp"
	break;
      case 74: /* "fileString" */

/* Line 479 of lalr1.cc  */
#line 153 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 315 "cfdg.tab.cpp"
	break;
      case 75: /* "fileNameSpace" */

/* Line 479 of lalr1.cc  */
#line 153 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 324 "cfdg.tab.cpp"
	break;
      case 76: /* "initialization" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 333 "cfdg.tab.cpp"
	break;
      case 77: /* "initialization_v2" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 342 "cfdg.tab.cpp"
	break;
      case 78: /* "background" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 351 "cfdg.tab.cpp"
	break;
      case 79: /* "tile" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 360 "cfdg.tab.cpp"
	break;
      case 80: /* "size" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 369 "cfdg.tab.cpp"
	break;
      case 82: /* "global_definition_header" */

/* Line 479 of lalr1.cc  */
#line 153 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 378 "cfdg.tab.cpp"
	break;
      case 83: /* "definition_header" */

/* Line 479 of lalr1.cc  */
#line 153 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 387 "cfdg.tab.cpp"
	break;
      case 85: /* "shape" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->shapeObj); };

/* Line 479 of lalr1.cc  */
#line 396 "cfdg.tab.cpp"
	break;
      case 86: /* "shape_singleton_header" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 405 "cfdg.tab.cpp"
	break;
      case 87: /* "shape_singleton" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 414 "cfdg.tab.cpp"
	break;
      case 88: /* "rule_header_v2" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 423 "cfdg.tab.cpp"
	break;
      case 90: /* "rule_header" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 432 "cfdg.tab.cpp"
	break;
      case 91: /* "path_header" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 441 "cfdg.tab.cpp"
	break;
      case 92: /* "rule" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 450 "cfdg.tab.cpp"
	break;
      case 93: /* "path" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 459 "cfdg.tab.cpp"
	break;
      case 94: /* "path_header_v2" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 468 "cfdg.tab.cpp"
	break;
      case 102: /* "parameter_spec" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 477 "cfdg.tab.cpp"
	break;
      case 105: /* "pathOp_simple_v2" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 486 "cfdg.tab.cpp"
	break;
      case 106: /* "element_simple" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 495 "cfdg.tab.cpp"
	break;
      case 111: /* "element" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 504 "cfdg.tab.cpp"
	break;
      case 114: /* "pathOp_v2" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 513 "cfdg.tab.cpp"
	break;
      case 116: /* "element_loop" */

/* Line 479 of lalr1.cc  */
#line 157 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 522 "cfdg.tab.cpp"
	break;
      case 119: /* "replacement_simple_v2" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 531 "cfdg.tab.cpp"
	break;
      case 120: /* "replacement_v2" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 540 "cfdg.tab.cpp"
	break;
      case 121: /* "loopHeader_v2" */

/* Line 479 of lalr1.cc  */
#line 157 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 549 "cfdg.tab.cpp"
	break;
      case 123: /* "loopHeader" */

/* Line 479 of lalr1.cc  */
#line 157 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 558 "cfdg.tab.cpp"
	break;
      case 124: /* "loopexp" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 567 "cfdg.tab.cpp"
	break;
      case 125: /* "ifHeader" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ifObj); };

/* Line 479 of lalr1.cc  */
#line 576 "cfdg.tab.cpp"
	break;
      case 126: /* "ifElseHeader" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ifObj); };

/* Line 479 of lalr1.cc  */
#line 585 "cfdg.tab.cpp"
	break;
      case 127: /* "transHeader" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 594 "cfdg.tab.cpp"
	break;
      case 128: /* "switchHeader" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->switchObj); };

/* Line 479 of lalr1.cc  */
#line 603 "cfdg.tab.cpp"
	break;
      case 129: /* "caseHeader" */

/* Line 479 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); };

/* Line 479 of lalr1.cc  */
#line 612 "cfdg.tab.cpp"
	break;
      case 130: /* "modification_v2" */

/* Line 479 of lalr1.cc  */
#line 156 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 621 "cfdg.tab.cpp"
	break;
      case 131: /* "modification" */

/* Line 479 of lalr1.cc  */
#line 156 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 630 "cfdg.tab.cpp"
	break;
      case 132: /* "buncha_pathop_adjustments" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 639 "cfdg.tab.cpp"
	break;
      case 133: /* "buncha_adjustments" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 648 "cfdg.tab.cpp"
	break;
      case 135: /* "adjustment" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 657 "cfdg.tab.cpp"
	break;
      case 136: /* "explist" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 666 "cfdg.tab.cpp"
	break;
      case 137: /* "exp" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 675 "cfdg.tab.cpp"
	break;
      case 138: /* "exp2" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 684 "cfdg.tab.cpp"
	break;
      case 139: /* "expfunc" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 693 "cfdg.tab.cpp"
	break;
      case 140: /* "exp2func" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 702 "cfdg.tab.cpp"
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
#line 181 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 6:

/* Line 677 of lalr1.cc  */
#line 190 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 9:

/* Line 677 of lalr1.cc  */
#line 200 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 10:

/* Line 677 of lalr1.cc  */
#line 201 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 13:

/* Line 677 of lalr1.cc  */
#line 204 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].shapeObj); }
    break;

  case 15:

/* Line 677 of lalr1.cc  */
#line 206 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 16:

/* Line 677 of lalr1.cc  */
#line 207 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 19:

/* Line 677 of lalr1.cc  */
#line 216 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 20:

/* Line 677 of lalr1.cc  */
#line 217 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 25:

/* Line 677 of lalr1.cc  */
#line 222 "../../src-common/cfdg.ypp"
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
#line 234 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 27:

/* Line 677 of lalr1.cc  */
#line 235 "../../src-common/cfdg.ypp"
    {}
    break;

  case 28:

/* Line 677 of lalr1.cc  */
#line 236 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 31:

/* Line 677 of lalr1.cc  */
#line 239 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 32:

/* Line 677 of lalr1.cc  */
#line 240 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 33:

/* Line 677 of lalr1.cc  */
#line 241 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 34:

/* Line 677 of lalr1.cc  */
#line 245 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 35:

/* Line 677 of lalr1.cc  */
#line 246 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 36:

/* Line 677 of lalr1.cc  */
#line 247 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 37:

/* Line 677 of lalr1.cc  */
#line 248 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 38:

/* Line 677 of lalr1.cc  */
#line 249 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(1) - (1)].ruleObj); }
    break;

  case 39:

/* Line 677 of lalr1.cc  */
#line 253 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(2) - (2)].string));
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(NULL);
            driver.IncludeFile(*file);
        }
    break;

  case 40:

/* Line 677 of lalr1.cc  */
#line 262 "../../src-common/cfdg.ypp"
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
#line 273 "../../src-common/cfdg.ypp"
    {
            if (driver.EndInclude())
                YYACCEPT;
        }
    break;

  case 44:

/* Line 677 of lalr1.cc  */
#line 283 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 45:

/* Line 677 of lalr1.cc  */
#line 284 "../../src-common/cfdg.ypp"
    { (yyval.string) = NULL; }
    break;

  case 46:

/* Line 677 of lalr1.cc  */
#line 288 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(4) - (2)].string));
            exp_ptr p((yysemantic_stack_[(4) - (3)].expression));
            mod_ptr mod((yysemantic_stack_[(4) - (4)].mod));
            driver.SetShape(NULL);
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, p, (yylocation_stack_[(4) - (2)])));
            rep_ptr start(new ASTreplacement(*r, *name, mod, (yyloc)));
            driver.Initialize(start);
            (yyval.component) = 0;
        }
    break;

  case 47:

/* Line 677 of lalr1.cc  */
#line 299 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(3) - (2)].string));
            exp_ptr p((yysemantic_stack_[(3) - (3)].expression));
            driver.SetShape(NULL);
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, p, (yylocation_stack_[(3) - (2)])));
            rep_ptr start(new ASTreplacement(*r, *name, mod_ptr(), (yyloc)));
            driver.Initialize(start);
            (yyval.component) = 0;
        }
    break;

  case 48:

/* Line 677 of lalr1.cc  */
#line 311 "../../src-common/cfdg.ypp"
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
#line 322 "../../src-common/cfdg.ypp"
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
#line 332 "../../src-common/cfdg.ypp"
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
#line 342 "../../src-common/cfdg.ypp"
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
#line 357 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(2) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            if (var.get())
                driver.NextParameter(*var, exp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 53:

/* Line 677 of lalr1.cc  */
#line 366 "../../src-common/cfdg.ypp"
    {
            driver.push_paramDecls(*(yysemantic_stack_[(3) - (1)].string), (yyloc));
            (yyval.string) = (yysemantic_stack_[(3) - (1)].string);
        }
    break;

  case 54:

/* Line 677 of lalr1.cc  */
#line 370 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            error((yylocation_stack_[(3) - (1)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 55:

/* Line 677 of lalr1.cc  */
#line 378 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            (yyval.string) = (yysemantic_stack_[(2) - (1)].string);
        }
    break;

  case 56:

/* Line 677 of lalr1.cc  */
#line 382 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            error((yylocation_stack_[(2) - (1)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 57:

/* Line 677 of lalr1.cc  */
#line 390 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(2) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            if (var.get())
                driver.NextParameter(*var, exp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 58:

/* Line 677 of lalr1.cc  */
#line 399 "../../src-common/cfdg.ypp"
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
#line 415 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (1)].shapeObj), true);
            driver.mInPathContainer = false;
            rule_ptr rule(new ASTrule(-1, (yylocation_stack_[(2) - (1)])));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
        }
    break;

  case 60:

/* Line 677 of lalr1.cc  */
#line 425 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(3) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 61:

/* Line 677 of lalr1.cc  */
#line 433 "../../src-common/cfdg.ypp"
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
#line 442 "../../src-common/cfdg.ypp"
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
#line 457 "../../src-common/cfdg.ypp"
    {
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 64:

/* Line 677 of lalr1.cc  */
#line 465 "../../src-common/cfdg.ypp"
    {
            driver.mInPathContainer = false;
            rule_ptr rule(new ASTrule(-1, (yylocation_stack_[(1) - (1)])));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
		}
    break;

  case 65:

/* Line 677 of lalr1.cc  */
#line 473 "../../src-common/cfdg.ypp"
    {
            driver.mInPathContainer = false;
            str_ptr weight((yysemantic_stack_[(2) - (2)].string));
            rule_ptr rule(new ASTrule(-1, CFatof(weight->c_str()), 
                                      weight->find_first_of('%')  != std::string::npos,
                                      (yyloc)));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
		}
    break;

  case 66:

/* Line 677 of lalr1.cc  */
#line 486 "../../src-common/cfdg.ypp"
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
            rule_ptr newPath(new ASTrule(-1, (yyloc)));
            newPath->isPath = true;
            driver.AddRule(newPath.get());
            driver.push_repContainer(newPath->mRuleBody);
            (yyval.ruleObj) = newPath.release();
        }
    break;

  case 67:

/* Line 677 of lalr1.cc  */
#line 507 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 68:

/* Line 677 of lalr1.cc  */
#line 515 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
            driver.SetShape(NULL);
        }
    break;

  case 69:

/* Line 677 of lalr1.cc  */
#line 524 "../../src-common/cfdg.ypp"
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
#line 537 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 71:

/* Line 677 of lalr1.cc  */
#line 544 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(2) - (1)].string));
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(*type, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
		}
    break;

  case 72:

/* Line 677 of lalr1.cc  */
#line 550 "../../src-common/cfdg.ypp"
    {
            static std::string shapeStr("shape");
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(shapeStr, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 73:

/* Line 677 of lalr1.cc  */
#line 556 "../../src-common/cfdg.ypp"
    {
            delete (yysemantic_stack_[(2) - (1)].string);
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 74:

/* Line 677 of lalr1.cc  */
#line 561 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 79:

/* Line 677 of lalr1.cc  */
#line 577 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("number");
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            driver.NextParameterDecl(numtype, *var, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 80:

/* Line 677 of lalr1.cc  */
#line 583 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Reserved keyword: adjustment");
        }
    break;

  case 83:

/* Line 677 of lalr1.cc  */
#line 594 "../../src-common/cfdg.ypp"
    { driver.isFunction = true; }
    break;

  case 84:

/* Line 677 of lalr1.cc  */
#line 595 "../../src-common/cfdg.ypp"
    { driver.isFunction = true; }
    break;

  case 85:

/* Line 677 of lalr1.cc  */
#line 596 "../../src-common/cfdg.ypp"
    { driver.isFunction = false; }
    break;

  case 86:

/* Line 677 of lalr1.cc  */
#line 600 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(3) - (2)].expression);}
    break;

  case 87:

/* Line 677 of lalr1.cc  */
#line 601 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTexpression((yyloc)); }
    break;

  case 88:

/* Line 677 of lalr1.cc  */
#line 602 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 89:

/* Line 677 of lalr1.cc  */
#line 603 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 90:

/* Line 677 of lalr1.cc  */
#line 607 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 92:

/* Line 677 of lalr1.cc  */
#line 614 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 94:

/* Line 677 of lalr1.cc  */
#line 621 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string));
            exp_ptr mod((yysemantic_stack_[(4) - (3)].expression));
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = new ASTpathOp(*pop, mod, false, (yyloc));
        }
    break;

  case 95:

/* Line 677 of lalr1.cc  */
#line 628 "../../src-common/cfdg.ypp"
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
#line 638 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string));
            exp_ptr mod((yysemantic_stack_[(4) - (3)].expression));
            (yyval.component) = new ASTpathOp(*pop, mod, true, (yyloc));
        }
    break;

  case 97:

/* Line 677 of lalr1.cc  */
#line 644 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(3) - (1)].string));
            exp_ptr mod;
            (yyval.component) = new ASTpathOp(*pop, mod, true, (yyloc));
        }
    break;

  case 98:

/* Line 677 of lalr1.cc  */
#line 650 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(3) - (1)].string));
            exp_ptr p((yysemantic_stack_[(3) - (2)].expression));
            mod_ptr mod((yysemantic_stack_[(3) - (3)].mod));
            rep_ptr item = driver.MakeElement(*cmd, mod, p, (yyloc), false);
            (yyval.component) = item.release();
        }
    break;

  case 99:

/* Line 677 of lalr1.cc  */
#line 658 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(4) - (2)].string));
            exp_ptr p((yysemantic_stack_[(4) - (3)].expression));
            mod_ptr mod((yysemantic_stack_[(4) - (4)].mod));
            rep_ptr item = driver.MakeElement(*cmd, mod, p, (yyloc), true);
            (yyval.component) = item.release();
        }
    break;

  case 100:

/* Line 677 of lalr1.cc  */
#line 668 "../../src-common/cfdg.ypp"
    { }
    break;

  case 101:

/* Line 677 of lalr1.cc  */
#line 670 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 102:

/* Line 677 of lalr1.cc  */
#line 676 "../../src-common/cfdg.ypp"
    { }
    break;

  case 103:

/* Line 677 of lalr1.cc  */
#line 678 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 104:

/* Line 677 of lalr1.cc  */
#line 684 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer(driver.switchStack.top());
        }
    break;

  case 107:

/* Line 677 of lalr1.cc  */
#line 695 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 108:

/* Line 677 of lalr1.cc  */
#line 697 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 109:

/* Line 677 of lalr1.cc  */
#line 699 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(1) - (1)].loopObj); 
            driver.pop_repContainer((yysemantic_stack_[(1) - (1)].loopObj));
            if ((yysemantic_stack_[(1) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(1) - (1)].loopObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 110:

/* Line 677 of lalr1.cc  */
#line 708 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            driver.push_repContainer((yysemantic_stack_[(2) - (1)].loopObj)->mFinallyBody);
        }
    break;

  case 111:

/* Line 677 of lalr1.cc  */
#line 711 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].loopObj));
            (yyval.component) = (yysemantic_stack_[(4) - (1)].loopObj);
            if ((yysemantic_stack_[(4) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(4) - (1)].loopObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 112:

/* Line 677 of lalr1.cc  */
#line 720 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].ifObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].ifObj));
            if ((yysemantic_stack_[(2) - (1)].ifObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].ifObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 113:

/* Line 677 of lalr1.cc  */
#line 729 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].ifObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].ifObj));
            if ((yysemantic_stack_[(2) - (1)].ifObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].ifObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 114:

/* Line 677 of lalr1.cc  */
#line 738 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].component);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].component));
            if ((yysemantic_stack_[(2) - (1)].component)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].component);
                (yyval.component) = 0;
            }
        }
    break;

  case 115:

/* Line 677 of lalr1.cc  */
#line 748 "../../src-common/cfdg.ypp"
    {
            (yysemantic_stack_[(4) - (1)].switchObj)->unify();
            (yyval.component) = (yysemantic_stack_[(4) - (1)].switchObj);
            driver.switchStack.pop();
        }
    break;

  case 116:

/* Line 677 of lalr1.cc  */
#line 754 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 117:

/* Line 677 of lalr1.cc  */
#line 761 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 118:

/* Line 677 of lalr1.cc  */
#line 762 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 119:

/* Line 677 of lalr1.cc  */
#line 763 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 120:

/* Line 677 of lalr1.cc  */
#line 767 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 121:

/* Line 677 of lalr1.cc  */
#line 769 "../../src-common/cfdg.ypp"
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
#line 777 "../../src-common/cfdg.ypp"
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
#line 789 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 124:

/* Line 677 of lalr1.cc  */
#line 790 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 127:

/* Line 677 of lalr1.cc  */
#line 793 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 132:

/* Line 677 of lalr1.cc  */
#line 801 "../../src-common/cfdg.ypp"
    {
            (yyval.loopObj) = (yysemantic_stack_[(2) - (1)].loopObj);
        }
    break;

  case 133:

/* Line 677 of lalr1.cc  */
#line 807 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 135:

/* Line 677 of lalr1.cc  */
#line 814 "../../src-common/cfdg.ypp"
    { }
    break;

  case 136:

/* Line 677 of lalr1.cc  */
#line 816 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 137:

/* Line 677 of lalr1.cc  */
#line 822 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), (yylocation_stack_[(2) - (1)])));
            (yyval.component) = new ASTreplacement(*r, r->entropyVal, mod, (yyloc));
        }
    break;

  case 138:

/* Line 677 of lalr1.cc  */
#line 831 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 139:

/* Line 677 of lalr1.cc  */
#line 833 "../../src-common/cfdg.ypp"
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
#line 844 "../../src-common/cfdg.ypp"
    { ++driver.mLocalStackDepth; }
    break;

  case 141:

/* Line 677 of lalr1.cc  */
#line 844 "../../src-common/cfdg.ypp"
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
#line 859 "../../src-common/cfdg.ypp"
    {
            str_ptr var((yysemantic_stack_[(5) - (2)].string));
            exp_ptr index((yysemantic_stack_[(5) - (4)].expression));
            mod_ptr mod((yysemantic_stack_[(5) - (5)].mod));
            --driver.mLocalStackDepth;
            loop_ptr loop(new ASTloop(driver.StringToShape(*var, (yylocation_stack_[(5) - (2)]), false), 
                                      *var, (yylocation_stack_[(5) - (2)]), index, (yylocation_stack_[(5) - (4)]), mod));
            driver.push_repContainer(loop->mLoopBody);
            (yyval.loopObj) = loop.release();
        }
    break;

  case 143:

/* Line 677 of lalr1.cc  */
#line 870 "../../src-common/cfdg.ypp"
    {
            exp_ptr index((yysemantic_stack_[(5) - (4)].expression));
            mod_ptr mod((yysemantic_stack_[(5) - (5)].mod));
            static const std::string dummyvar("~~inaccessiblevar~~");
            --driver.mLocalStackDepth;
            loop_ptr loop(new ASTloop(driver.StringToShape(dummyvar, (yylocation_stack_[(5) - (1)]), false), 
                                      dummyvar, (yylocation_stack_[(5) - (2)]), index, (yylocation_stack_[(5) - (4)]), mod));
            driver.push_repContainer(loop->mLoopBody);
            (yyval.loopObj) = loop.release();
            error((yylocation_stack_[(5) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 144:

/* Line 677 of lalr1.cc  */
#line 882 "../../src-common/cfdg.ypp"
    {
            exp_ptr count((yysemantic_stack_[(3) - (2)].expression));
            mod_ptr mod((yysemantic_stack_[(3) - (3)].mod));
            static const std::string dummyvar("~~inaccessiblevar~~");
            --driver.mLocalStackDepth;
            loop_ptr loop(new ASTloop(driver.StringToShape(dummyvar, (yylocation_stack_[(3) - (1)]), false), 
                                      dummyvar, (yylocation_stack_[(3) - (1)]), count, (yylocation_stack_[(3) - (2)]), mod));
            driver.push_repContainer(loop->mLoopBody);
            (yyval.loopObj) = loop.release();
        }
    break;

  case 145:

/* Line 677 of lalr1.cc  */
#line 895 "../../src-common/cfdg.ypp"
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
#line 907 "../../src-common/cfdg.ypp"
    {
            exp_ptr cond((yysemantic_stack_[(4) - (3)].expression));
            if_ptr ifHeader(new ASTif(cond, (yylocation_stack_[(4) - (3)])));
            driver.push_repContainer(ifHeader->mThenBody);
            (yyval.ifObj) = ifHeader.release();
        }
    break;

  case 147:

/* Line 677 of lalr1.cc  */
#line 916 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ifObj));
            driver.push_repContainer((yysemantic_stack_[(3) - (1)].ifObj)->mElseBody);
            (yyval.ifObj) = (yysemantic_stack_[(3) - (1)].ifObj);
        }
    break;

  case 148:

/* Line 677 of lalr1.cc  */
#line 924 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (1)].modToken) != ASTmodTerm::transform)
                error((yylocation_stack_[(2) - (1)]), "Syntax error");
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            ASTtransform* trans = new ASTtransform(mod, (yyloc));
            driver.push_repContainer(trans->mBody);
            (yyval.component) = trans;
        }
    break;

  case 149:

/* Line 677 of lalr1.cc  */
#line 935 "../../src-common/cfdg.ypp"
    {
            exp_ptr caseVal((yysemantic_stack_[(4) - (3)].expression));
            switch_ptr switchHeader(new ASTswitch(caseVal, (yylocation_stack_[(4) - (3)])));
            driver.switchStack.push(switchHeader.get());
            (yyval.switchObj) = switchHeader.release();
        }
    break;

  case 150:

/* Line 677 of lalr1.cc  */
#line 944 "../../src-common/cfdg.ypp"
    {
            exp_ptr valExp((yysemantic_stack_[(3) - (2)].expression));
            
            double val = 0.0;
            try {
                if (valExp->evaluate(&val, 1) != 1) {
                    driver.error((yylocation_stack_[(3) - (2)]), "Case expression is not a single, numeric expression");
                } else {
                    ASTrepContainer* caseBody = new ASTrepContainer();
                    std::pair<ASTswitch::switchMap::iterator, bool> ret = 
                        driver.switchStack.top()->mCaseStatements.
                        insert(std::pair<int, ASTrepContainer*>((int)val, caseBody));
                    
                    if (!ret.second) {
                        driver.error((yylocation_stack_[(3) - (2)]), "Case value already in use");
                        delete caseBody;
                    }
                    driver.push_repContainer(*caseBody);
                }
            }
            catch (DeferUntilRuntime) {
                driver.error((yylocation_stack_[(3) - (2)]), "Case expression is not constant");
            }
            (yyval.modToken) = 0;
        }
    break;

  case 151:

/* Line 677 of lalr1.cc  */
#line 970 "../../src-common/cfdg.ypp"
    {
            if (!driver.switchStack.top()->mElseBody.mBody.empty()) {
                driver.error((yyloc), "There can only be one 'else:' clause");
            } else {
                driver.push_repContainer(driver.switchStack.top()->mElseBody);
            }
            (yyval.modToken) = 0;
        }
    break;

  case 152:

/* Line 677 of lalr1.cc  */
#line 981 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod(ASToperator::MakeCanonical(driver.mCanonicalMods));
            (yyval.mod) = driver.MakeModification(mod, (yyloc));
        }
    break;

  case 153:

/* Line 677 of lalr1.cc  */
#line 986 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(3) - (2)].expression));
            (yyval.mod) = driver.MakeModification(mod, (yyloc));
        }
    break;

  case 154:

/* Line 677 of lalr1.cc  */
#line 993 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod(ASToperator::MakeCanonical(driver.mCanonicalMods));
            (yyval.mod) = driver.MakeModification(mod, (yyloc));
        }
    break;

  case 155:

/* Line 677 of lalr1.cc  */
#line 998 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(5) - (3)].expression));
            (yyval.mod) = driver.MakeModification(mod, (yyloc));
        }
    break;

  case 156:

/* Line 677 of lalr1.cc  */
#line 1005 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTcons::Cons((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 157:

/* Line 677 of lalr1.cc  */
#line 1008 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 158:

/* Line 677 of lalr1.cc  */
#line 1012 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTcons::Cons((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 159:

/* Line 677 of lalr1.cc  */
#line 1015 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 160:

/* Line 677 of lalr1.cc  */
#line 1019 "../../src-common/cfdg.ypp"
    {
            ((yysemantic_stack_[(2) - (2)].expression))->flatten(driver.mCanonicalMods);
        }
    break;

  case 161:

/* Line 677 of lalr1.cc  */
#line 1022 "../../src-common/cfdg.ypp"
    { driver.mCanonicalMods.clear(); }
    break;

  case 162:

/* Line 677 of lalr1.cc  */
#line 1026 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].expression));
            (yyval.expression) = driver.MakeModTerm((yysemantic_stack_[(2) - (1)].modToken), mod, (yyloc));
        }
    break;

  case 163:

/* Line 677 of lalr1.cc  */
#line 1031 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(3) - (2)].expression));
            if ((yysemantic_stack_[(3) - (1)].modToken) < ASTmodTerm::hue || (yysemantic_stack_[(3) - (1)].modToken) > ASTmodTerm::alpha) {
                error((yyloc), "The target operator can only be applied to color adjustments");
                (yyval.expression) = 0;
            } else {
                (yyval.expression) = driver.MakeModTerm((yysemantic_stack_[(3) - (1)].modToken) + 4, mod, (yyloc));
            }
        }
    break;

  case 164:

/* Line 677 of lalr1.cc  */
#line 1041 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.expression) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 165:

/* Line 677 of lalr1.cc  */
#line 1046 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.expression) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 166:

/* Line 677 of lalr1.cc  */
#line 1053 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTcons::Cons((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 167:

/* Line 677 of lalr1.cc  */
#line 1057 "../../src-common/cfdg.ypp"
    { 
            (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); 
        }
    break;

  case 168:

/* Line 677 of lalr1.cc  */
#line 1063 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 169:

/* Line 677 of lalr1.cc  */
#line 1065 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 170:

/* Line 677 of lalr1.cc  */
#line 1067 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 171:

/* Line 677 of lalr1.cc  */
#line 1069 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 172:

/* Line 677 of lalr1.cc  */
#line 1071 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 173:

/* Line 677 of lalr1.cc  */
#line 1073 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 174:

/* Line 677 of lalr1.cc  */
#line 1078 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 175:

/* Line 677 of lalr1.cc  */
#line 1085 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 176:

/* Line 677 of lalr1.cc  */
#line 1087 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 177:

/* Line 677 of lalr1.cc  */
#line 1089 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 178:

/* Line 677 of lalr1.cc  */
#line 1094 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 179:

/* Line 677 of lalr1.cc  */
#line 1099 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression));   }
    break;

  case 180:

/* Line 677 of lalr1.cc  */
#line 1101 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('+', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 181:

/* Line 677 of lalr1.cc  */
#line 1103 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('-', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 182:

/* Line 677 of lalr1.cc  */
#line 1105 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('_', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 183:

/* Line 677 of lalr1.cc  */
#line 1107 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('*', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 184:

/* Line 677 of lalr1.cc  */
#line 1109 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('/', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 185:

/* Line 677 of lalr1.cc  */
#line 1111 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 186:

/* Line 677 of lalr1.cc  */
#line 1113 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 187:

/* Line 677 of lalr1.cc  */
#line 1115 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('!', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 188:

/* Line 677 of lalr1.cc  */
#line 1117 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('^', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 189:

/* Line 677 of lalr1.cc  */
#line 1119 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('<', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 190:

/* Line 677 of lalr1.cc  */
#line 1121 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('L', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 191:

/* Line 677 of lalr1.cc  */
#line 1123 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('>', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 192:

/* Line 677 of lalr1.cc  */
#line 1125 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('G', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 193:

/* Line 677 of lalr1.cc  */
#line 1127 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('=', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 194:

/* Line 677 of lalr1.cc  */
#line 1129 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('n', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 195:

/* Line 677 of lalr1.cc  */
#line 1131 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('&', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 196:

/* Line 677 of lalr1.cc  */
#line 1133 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('|', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 197:

/* Line 677 of lalr1.cc  */
#line 1135 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('X', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 198:

/* Line 677 of lalr1.cc  */
#line 1137 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 199:

/* Line 677 of lalr1.cc  */
#line 1139 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].mod); }
    break;

  case 200:

/* Line 677 of lalr1.cc  */
#line 1143 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), true);
        }
    break;

  case 201:

/* Line 677 of lalr1.cc  */
#line 1148 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), true);
        }
    break;

  case 202:

/* Line 677 of lalr1.cc  */
#line 1154 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 203:

/* Line 677 of lalr1.cc  */
#line 1161 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 204:

/* Line 677 of lalr1.cc  */
#line 1166 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 205:

/* Line 677 of lalr1.cc  */
#line 1172 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args(new ASTexpression((yylocation_stack_[(4) - (1)]) + (yylocation_stack_[(4) - (4)])));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 206:

/* Line 677 of lalr1.cc  */
#line 1178 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;



/* Line 677 of lalr1.cc  */
#line 2600 "cfdg.tab.cpp"
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
  const short int CfdgParser::yypact_ninf_ = -241;
  const short int
  CfdgParser::yypact_[] =
  {
       215,  -241,  -241,    21,   675,   694,  -241,    80,  -241,    92,
     102,    10,   -21,  -241,     7,   275,  -241,   -21,  -241,  -241,
    -241,  -241,  -241,  -241,  -241,  -241,    77,  -241,    89,  -241,
     139,   150,   121,   159,   114,   -21,    27,   275,   144,   -21,
    -241,  -241,  -241,  -241,  -241,  -241,   633,   145,  -241,  -241,
    -241,   153,   171,  -241,  -241,   271,   196,   182,  -241,  -241,
    -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,
    -241,   212,   230,  -241,   230,   107,   240,  -241,  -241,   276,
    -241,   256,   275,  -241,   235,  -241,   633,   633,   633,   633,
     239,  -241,   527,  -241,  -241,    14,  -241,  -241,  -241,  -241,
    -241,  -241,    42,   119,   117,    24,   180,   242,    50,  -241,
    -241,  -241,  -241,  -241,  -241,    63,  -241,  -241,  -241,  -241,
     183,   251,   251,   251,   270,  -241,    95,   633,   633,   633,
     633,   633,   633,   633,   633,   633,   633,   633,   633,   633,
     633,   633,   633,   633,   633,   287,   244,   278,   279,    20,
      -3,   291,     1,  -241,   633,  -241,  -241,  -241,  -241,   312,
      44,    44,    44,    44,   296,    94,   106,   217,    25,  -241,
    -241,  -241,  -241,   -21,   306,  -241,  -241,  -241,   124,  -241,
    -241,  -241,  -241,   344,     9,   154,  -241,  -241,  -241,  -241,
     168,   297,  -241,   299,  -241,   179,   188,  -241,   125,   216,
    -241,   298,  -241,   328,  -241,   111,  -241,   226,   226,   535,
     535,   535,   535,   618,   618,   599,   578,   556,   527,   228,
     228,   228,   251,   251,   251,   212,   349,    96,   242,   527,
     633,   633,  -241,  -241,  -241,  -241,   242,  -241,   241,  -241,
     527,  -241,   212,   307,  -241,  -241,  -241,   346,  -241,  -241,
    -241,  -241,  -241,   308,  -241,   217,   217,   633,   217,   135,
    -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,   -21,   325,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,  -241,    50,  -241,  -241,  -241,  -241,
     322,   242,   633,   633,  -241,   357,   386,  -241,  -241,   415,
      44,   127,  -241,    57,   501,  -241,  -241,   444,   305,   217,
     217,  -241,   -21,   141,   137,   165,  -241,  -241,  -241,   242,
     242,  -241,  -241,  -241,  -241,  -241,   309,   633,  -241,  -241,
      44,  -241,   473,  -241,  -241,  -241,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,   209,  -241,  -241,  -241
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
     161,    51,    49,    26,    28,    42,    43,    39,    50,   134,
      93,    89,    78,    65,    78,     0,     0,    36,    34,     0,
      37,     0,     0,    35,   206,   175,     0,     0,     0,     0,
     161,   199,    52,   176,    59,     0,    91,    91,    32,    33,
      62,    31,     0,     0,     0,     0,     0,    47,     0,    58,
      66,    80,    79,    84,    82,     0,    54,    53,    44,    40,
       0,   187,   185,   186,     0,   159,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      89,     0,     0,    60,     0,   108,   107,    90,   116,   109,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   153,
     158,   152,   160,     0,     0,    63,   138,   133,     0,   125,
     126,   129,   131,   130,     0,     0,    70,   120,    92,   122,
       0,     0,    88,     0,    46,     0,     0,    76,     0,     0,
      83,     0,   203,     0,   198,     0,   154,   177,   178,   190,
     189,   192,   191,   193,   194,   195,   196,   197,   179,   181,
     180,   182,   183,   184,   188,    89,     0,   206,     0,   145,
       0,     0,    56,   148,    55,   118,     0,   117,     0,   119,
      57,   110,    89,     0,    91,   101,   132,   112,   113,   114,
     105,    67,    68,   202,   168,     0,     0,     0,   162,   167,
     170,   164,   165,   137,   140,   134,   139,   136,   128,   127,
     124,    95,   123,   157,     0,     0,    93,   103,   121,    87,
      86,    74,    72,    73,    71,     0,    77,    81,   205,   204,
       0,     0,     0,     0,   144,     0,     0,    98,    97,     0,
       0,     0,   147,     0,     0,   171,   172,     0,   166,     0,
       0,   163,     0,     0,     0,     0,    75,   155,    99,     0,
       0,   146,   149,    96,   111,   100,     0,     0,   115,   104,
       0,   200,     0,   169,   173,   174,   141,   135,    94,   156,
     102,   143,   142,   151,     0,   106,   201,   150
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yypgoto_[] =
  {
      -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,
     379,    -4,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,  -241,   380,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,   101,  -241,   314,   190,  -241,   354,   -66,
     -83,   115,   208,   -86,  -151,  -241,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,   146,  -241,   234,  -241,   -97,  -241,
    -241,    38,  -241,  -241,  -241,  -241,  -241,   -11,  -103,  -241,
     288,   324,  -100,  -241,  -240,   -44,  -241,  -241
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yydefgoto_[] =
  {
        -1,     3,     4,     5,    40,    18,    19,    41,    20,    42,
      21,    67,    82,    44,    22,    23,    24,    25,    45,    46,
     154,   155,    47,    48,    49,    26,    27,    51,    52,    53,
      54,    28,    29,   197,   198,   109,   114,   115,    76,   236,
      95,   105,   187,   245,   246,   278,   303,   329,   157,   300,
     158,   188,   189,   159,   104,   266,   176,   177,   178,   312,
     160,   228,   161,   162,   163,   164,   330,   271,    91,   314,
     102,   103,   170,   258,   259,   229,   260,    93
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char CfdgParser::yytable_ninf_ = -1;
  const unsigned short int
  CfdgParser::yytable_[] =
  {
        61,    62,    92,   172,   194,   107,    68,   234,   190,   156,
     247,   248,   249,   165,   166,   305,   306,    63,   308,   269,
      58,     6,   145,    77,    78,   146,   172,   147,    83,   148,
     232,   149,   179,    80,    59,   180,    60,   181,   150,   182,
     151,   183,   121,   122,   123,   124,   233,   152,   184,   261,
     174,   106,   145,   262,   235,   238,   195,   185,   239,   167,
     168,    64,   193,   270,    59,    59,    60,    60,   242,   334,
     335,   326,   153,   327,   196,    90,   203,   243,   119,   156,
     156,    75,   186,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   244,   145,   169,    55,   146,   293,   147,   199,   148,
     240,   149,   167,   168,   145,   328,    56,   146,   150,   147,
     151,   148,   200,   149,   111,   294,    57,   152,   167,   168,
     150,   112,   151,   297,    69,   145,   167,   168,   146,   152,
     147,   173,   148,   174,   149,    56,    70,    73,   173,   324,
     120,   150,   251,   151,   167,   168,   206,   309,   310,   291,
     152,   301,   263,    71,   252,   173,   113,   174,    75,    59,
     285,    60,   290,   179,    72,   175,   180,   171,   181,   345,
     182,   265,   183,    74,   286,   325,   295,   296,   318,   184,
     191,   174,   274,   201,   299,   338,   281,   311,   185,   337,
      81,   275,    94,   282,    84,   283,    85,    84,   272,    85,
      96,   273,   284,   307,   339,   156,   341,   342,   190,     1,
       2,    86,   100,   340,    86,   276,    87,    88,    97,    87,
      88,   127,   128,   111,    89,    90,   101,    89,    90,   192,
     112,   253,   202,   254,   129,   130,   131,   132,   133,   134,
     116,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     332,   226,   144,   255,   256,    84,   106,    85,   227,   347,
      85,   257,   139,   140,   141,   142,   143,   142,   143,   144,
     118,   144,    86,   344,   108,    86,   117,    87,    88,   120,
      87,    88,   127,   128,   125,    89,    90,    90,    89,    90,
     298,   336,    65,    66,   144,   129,   130,   131,   132,   133,
     134,   225,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   127,   128,   144,   241,    98,    99,   309,   310,   204,
     319,   320,   230,   231,   129,   130,   131,   132,   133,   134,
     237,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     127,   128,   144,   250,   268,   264,   279,   288,   280,   292,
     302,   238,   304,   129,   130,   131,   132,   133,   134,   343,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   127,
     128,   144,   273,   317,    43,    50,   316,   289,   110,   287,
      79,   315,   129,   130,   131,   132,   133,   134,   277,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   127,   128,
     144,   313,   267,   205,   126,     0,   321,     0,     0,     0,
       0,   129,   130,   131,   132,   133,   134,     0,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   127,   128,   144,
       0,     0,     0,     0,     0,   322,     0,     0,     0,     0,
     129,   130,   131,   132,   133,   134,     0,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   127,   128,   144,     0,
       0,     0,     0,     0,   323,     0,     0,     0,     0,   129,
     130,   131,   132,   133,   134,     0,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   127,   128,   144,     0,     0,
       0,     0,     0,   333,     0,     0,     0,     0,   129,   130,
     131,   132,   133,   134,     0,   135,   136,   137,   138,   139,
     140,   141,   142,   143,     0,    84,   144,    85,     0,     0,
       0,     0,   346,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    86,     0,     0,     0,     0,    87,    88,   127,
     128,     0,     0,     0,     0,    89,    90,   127,   128,     0,
     331,     0,   129,   130,   131,   132,   133,   134,     0,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   127,   128,
     144,   139,   140,   141,   142,   143,     0,     0,   144,     0,
       0,   129,   130,   131,   132,   133,   134,     0,   135,   136,
     127,   128,   139,   140,   141,   142,   143,     0,     0,   144,
       0,     0,     0,   129,   130,   131,   132,   133,   134,     0,
     135,   127,   128,     0,   139,   140,   141,   142,   143,     0,
       0,   144,     0,     0,   129,   130,   131,   132,   133,   134,
     127,   128,     0,     0,     0,   139,   140,   141,   142,   143,
       0,     0,   144,   129,   130,   131,   132,    84,     0,    85,
       0,     0,     0,     0,   139,   140,   141,   142,   143,     0,
       0,   144,     0,     0,    86,     0,     0,     0,     7,    87,
      88,     8,     9,    10,     0,     0,     0,    89,    90,     0,
       0,     0,    11,     0,    12,     0,    13,    30,     0,    14,
      31,    32,    33,     0,    15,    16,    17,     0,     0,     0,
       0,    34,     0,    35,     0,    13,     0,     0,    36,     0,
       0,     0,     0,    37,    38,    39
  };

  /* YYCHECK.  */
  const short int
  CfdgParser::yycheck_[] =
  {
        11,    12,    46,   103,   107,    71,    17,    10,   105,    95,
     161,   162,   163,    96,    97,   255,   256,    10,   258,    10,
      10,     0,     8,    34,    35,    11,   126,    13,    39,    15,
      10,    17,     8,    37,    55,    11,    57,    13,    24,    15,
      26,    17,    86,    87,    88,    89,   149,    33,    24,    24,
      26,    54,     8,    28,    57,    54,     6,    33,    57,    17,
      18,    54,   106,    54,    55,    55,    57,    57,    24,   309,
     310,    14,    58,    16,    24,    55,   120,    33,    82,   165,
     166,    54,    58,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,    57,     8,    61,    24,    11,    10,    13,    45,    15,
     154,    17,    17,    18,     8,    58,    24,    11,    24,    13,
      26,    15,    59,    17,    17,   228,    24,    33,    17,    18,
      24,    24,    26,   236,    57,     8,    17,    18,    11,    33,
      13,    24,    15,    26,    17,    24,    57,    26,    24,   300,
      54,    24,    58,    26,    17,    18,    61,    22,    23,   225,
      33,   244,   173,    24,    58,    24,    59,    26,    54,    55,
      45,    57,    61,     8,    24,    58,    11,    58,    13,   330,
      15,    57,    17,    24,    59,    58,   230,   231,   291,    24,
      10,    26,    24,    10,   238,    58,    17,    62,    33,    58,
      56,    33,    57,    24,    24,    17,    26,    24,    54,    26,
      57,    57,    24,   257,   314,   301,   319,   320,   315,     4,
       5,    41,    26,    58,    41,    57,    46,    47,    57,    46,
      47,    22,    23,    17,    54,    55,    54,    54,    55,    59,
      24,    24,    59,    26,    35,    36,    37,    38,    39,    40,
      10,    42,    43,    44,    45,    46,    47,    48,    49,    50,
     304,    17,    53,    46,    47,    24,    54,    26,    24,    60,
      26,    54,    46,    47,    48,    49,    50,    49,    50,    53,
      24,    53,    41,   327,    54,    41,    10,    46,    47,    54,
      46,    47,    22,    23,    55,    54,    55,    55,    54,    55,
      59,   312,    27,    28,    53,    35,    36,    37,    38,    39,
      40,    24,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    22,    23,    53,    12,    54,    55,    22,    23,    59,
     292,   293,    54,    54,    35,    36,    37,    38,    39,    40,
      49,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      22,    23,    53,    57,    10,    49,    59,    59,    59,    10,
      14,    54,    54,    35,    36,    37,    38,    39,    40,    60,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    22,
      23,    53,    57,    61,     5,     5,   285,    59,    74,   199,
      36,   276,    35,    36,    37,    38,    39,    40,   190,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    22,    23,
      53,   265,   178,   125,    90,    -1,    59,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    22,    23,    53,
      -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,
      35,    36,    37,    38,    39,    40,    -1,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    22,    23,    53,    -1,
      -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    40,    -1,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    22,    23,    53,    -1,    -1,
      -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,    35,    36,
      37,    38,    39,    40,    -1,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    -1,    24,    53,    26,    -1,    -1,
      -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    -1,    -1,    -1,    -1,    46,    47,    22,
      23,    -1,    -1,    -1,    -1,    54,    55,    22,    23,    -1,
      59,    -1,    35,    36,    37,    38,    39,    40,    -1,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    22,    23,
      53,    46,    47,    48,    49,    50,    -1,    -1,    53,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      22,    23,    46,    47,    48,    49,    50,    -1,    -1,    53,
      -1,    -1,    -1,    35,    36,    37,    38,    39,    40,    -1,
      42,    22,    23,    -1,    46,    47,    48,    49,    50,    -1,
      -1,    53,    -1,    -1,    35,    36,    37,    38,    39,    40,
      22,    23,    -1,    -1,    -1,    46,    47,    48,    49,    50,
      -1,    -1,    53,    35,    36,    37,    38,    24,    -1,    26,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,    -1,
      -1,    53,    -1,    -1,    41,    -1,    -1,    -1,     3,    46,
      47,     6,     7,     8,    -1,    -1,    -1,    54,    55,    -1,
      -1,    -1,    17,    -1,    19,    -1,    21,     3,    -1,    24,
       6,     7,     8,    -1,    29,    30,    31,    -1,    -1,    -1,
      -1,    17,    -1,    19,    -1,    21,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    29,    30,    31
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  CfdgParser::yystos_[] =
  {
         0,     4,     5,    64,    65,    66,     0,     3,     6,     7,
       8,    17,    19,    21,    24,    29,    30,    31,    68,    69,
      71,    73,    77,    78,    79,    80,    88,    89,    94,    95,
       3,     6,     7,     8,    17,    19,    24,    29,    30,    31,
      67,    70,    72,    73,    76,    81,    82,    85,    86,    87,
      88,    90,    91,    92,    93,    24,    24,    24,    10,    55,
      57,   130,   130,    10,    54,    27,    28,    74,   130,    57,
      57,    24,    24,    26,    24,    54,   101,   130,   130,   101,
      74,    56,    75,   130,    24,    26,    41,    46,    47,    54,
      55,   131,   138,   140,    57,   103,    57,    57,    54,    55,
      26,    54,   133,   134,   117,   104,    54,   102,    54,    98,
      98,    17,    24,    59,    99,   100,    10,    10,    24,    74,
      54,   138,   138,   138,   138,    55,   134,    22,    23,    35,
      36,    37,    38,    39,    40,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    53,     8,    11,    13,    15,    17,
      24,    26,    33,    58,    83,    84,   106,   111,   113,   116,
     123,   125,   126,   127,   128,   103,   103,    17,    18,    61,
     135,    58,   135,    24,    26,    58,   119,   120,   121,     8,
      11,    13,    15,    17,    24,    33,    58,   105,   114,   115,
     121,    10,    59,   138,   131,     6,    24,    96,    97,    45,
      59,    10,    59,   138,    59,   133,    61,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,    24,    17,    24,   124,   138,
      54,    54,    10,   131,    10,    57,   102,    49,    54,    57,
     138,    12,    24,    33,    57,   106,   107,   107,   107,   107,
      57,    58,    58,    24,    26,    46,    47,    54,   136,   137,
     139,    24,    28,   130,    49,    57,   118,   119,    10,    10,
      54,   130,    54,    57,    24,    33,    57,   105,   108,    59,
      59,    17,    24,    17,    24,    45,    59,    99,    59,    59,
      61,   102,    10,    10,   131,   138,   138,   131,    59,   138,
     112,   103,    14,   109,    54,   137,   137,   138,   137,    22,
      23,    62,   122,   117,   132,   104,    96,    61,   131,   124,
     124,    59,    59,    59,   107,    58,    14,    16,    58,   110,
     129,    59,   138,    59,   137,   137,   130,    58,    58,   135,
      58,   131,   131,    60,   138,   107,    59,    60
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
     295,   296,   297,   298,   299,    44,    45,    43,    95,    42,
      47,   300,   301,    94,    40,    91,    64,   123,   125,    41,
      58,    93,   124
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  CfdgParser::yyr1_[] =
  {
         0,    63,    64,    64,    65,    65,    66,    66,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    69,    69,    69,    69,
      69,    69,    69,    69,    70,    70,    70,    70,    70,    71,
      72,    73,    74,    74,    75,    75,    76,    76,    77,    78,
      79,    80,    81,    82,    82,    83,    83,    84,    85,    86,
      87,    88,    88,    89,    90,    90,    91,    92,    93,    94,
      95,    96,    96,    96,    96,    97,    97,    98,    98,    99,
      99,   100,   100,   101,   101,   101,   102,   102,   102,   102,
     103,   103,   104,   104,   105,   105,   106,   106,   106,   106,
     107,   107,   108,   108,   109,   109,   110,   111,   111,   111,
     112,   111,   111,   111,   111,   111,   111,   113,   113,   113,
     114,   114,   114,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   116,   117,   117,   118,   118,   119,   120,   120,
     122,   121,   123,   123,   123,   124,   125,   126,   127,   128,
     129,   129,   130,   130,   131,   131,   132,   132,   133,   133,
     134,   134,   135,   135,   135,   135,   136,   136,   137,   137,
     137,   137,   137,   137,   137,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     139,   139,   139,   140,   140,   140,   140
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
       3,     2,     3,     3,     3,     5,     2,     0,     2,     0,
       2,     0,     2,     3,     2,     2,     2,     1,     1,     3,
       1,     2,     2,     3,     3,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     4,     1,     3,     4,     4,     1
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
  "NEQ", "NOT", "AND", "OR", "XOR", "','", "'-'", "'+'", "'_'", "'*'",
  "'/'", "POS", "NEG", "'^'", "'('", "'['", "'@'", "'{'", "'}'", "')'",
  "':'", "']'", "'|'", "$accept", "choose", "cfdg2", "cfdg3", "statement",
  "statement_v2", "v3clues", "v2stuff", "inclusion", "import", "eof",
  "fileString", "fileNameSpace", "initialization", "initialization_v2",
  "background", "tile", "size", "global_definition",
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
  "modification_v2", "modification", "buncha_pathop_adjustments",
  "buncha_adjustments", "buncha_canonical_adjustments", "adjustment",
  "explist", "exp", "exp2", "expfunc", "exp2func", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const CfdgParser::rhs_number_type
  CfdgParser::yyrhs_[] =
  {
        64,     0,    -1,     4,    65,    -1,     5,    66,    -1,    65,
      68,    -1,    -1,    66,    67,    -1,    -1,    76,    -1,    72,
      -1,    73,    -1,    92,    -1,    93,    -1,    85,    -1,    87,
      -1,    81,    -1,    70,    -1,    77,    -1,    78,    -1,    71,
      -1,    73,    -1,    79,    -1,    80,    -1,    89,    -1,    95,
      -1,    69,    -1,    24,    10,    -1,    17,    10,    -1,    24,
      54,    -1,    30,    -1,     6,    -1,     8,    24,    54,    -1,
       3,    24,    54,    -1,     3,    24,    55,    -1,    19,   130,
      -1,    31,   130,    -1,    17,   130,    -1,    29,    74,    -1,
      88,    -1,    29,    74,    -1,    30,    75,    74,    -1,    21,
      -1,    27,    -1,    28,    -1,    56,    24,    -1,    -1,     3,
      24,   102,   131,    -1,     3,    24,   102,    -1,     3,    24,
      -1,    19,   130,    -1,    31,   130,    -1,    17,   130,    -1,
      82,   138,    -1,    24,   101,    10,    -1,    17,   101,    10,
      -1,    24,    10,    -1,    17,    10,    -1,    83,   138,    -1,
       6,    24,    98,    -1,    85,    57,    -1,    86,   103,    58,
      -1,     7,    24,    -1,     7,    24,    26,    -1,    88,    57,
     117,    58,    -1,     7,    -1,     7,    26,    -1,     8,    24,
      98,    -1,    90,    57,   103,    58,    -1,    91,    57,   103,
      58,    -1,     8,    24,    -1,    94,    57,   104,    58,    -1,
      24,    24,    -1,     6,    24,    -1,    24,    17,    -1,     6,
      17,    -1,    97,    45,    96,    -1,    96,    -1,    54,    97,
      59,    -1,    -1,    24,    -1,    17,    -1,   100,    45,    99,
      -1,    99,    -1,    54,   100,    59,    -1,    54,    59,    -1,
      -1,    54,   138,    59,    -1,    54,    10,    59,    -1,    54,
      59,    -1,    -1,   103,   111,    -1,    -1,   104,   114,    -1,
      -1,    33,    57,   132,    58,    -1,    24,   130,    -1,    33,
      54,   138,    59,    -1,    33,    54,    59,    -1,    24,   102,
     131,    -1,     8,    24,   102,   131,    -1,    57,   103,    58,
      -1,   106,    -1,    57,   104,    58,    -1,   105,    -1,   109,
     110,    -1,    -1,   129,   107,    -1,   106,    -1,    84,    -1,
     116,    -1,    -1,   116,    12,   112,   107,    -1,   125,   107,
      -1,   126,   107,    -1,   127,   107,    -1,   128,    57,   109,
      58,    -1,   113,    -1,    26,    49,    -1,    24,    57,    -1,
      33,    57,    -1,   105,    -1,   121,   108,    -1,   115,    -1,
      33,    54,    -1,    24,    54,    -1,     8,    -1,    11,    -1,
      24,    10,    -1,    17,    10,    -1,    13,    -1,    17,    -1,
      15,    -1,   123,   107,    -1,   117,   120,    -1,    -1,    57,
     117,    58,    -1,   119,    -1,    24,   130,    -1,   119,    -1,
     121,   118,    -1,    -1,    26,    49,   122,   130,    -1,    11,
      24,    10,   124,   131,    -1,    11,    17,    10,   124,   131,
      -1,    11,   124,   131,    -1,   138,    -1,    13,    54,   138,
      59,    -1,   125,   107,    14,    -1,    17,   131,    -1,    15,
      54,   138,    59,    -1,    16,   138,    60,    -1,    14,    60,
      -1,    57,   134,    58,    -1,    55,   133,    61,    -1,    55,
     134,    61,    -1,    55,    55,   133,    61,    61,    -1,   132,
     135,    -1,    -1,   133,   135,    -1,    -1,   134,   135,    -1,
      -1,    17,   136,    -1,    17,   137,    62,    -1,    18,    24,
      -1,    18,    28,    -1,   136,   137,    -1,   137,    -1,    26,
      -1,    54,   138,    59,    -1,   139,    -1,    46,   137,    -1,
      47,   137,    -1,   137,    22,   137,    -1,   137,    23,   137,
      -1,    26,    -1,   140,    -1,   138,    22,   138,    -1,   138,
      23,   138,    -1,   138,    45,   138,    -1,   138,    47,   138,
      -1,   138,    46,   138,    -1,   138,    48,   138,    -1,   138,
      49,   138,    -1,   138,    50,   138,    -1,    46,   138,    -1,
      47,   138,    -1,    41,   138,    -1,   138,    53,   138,    -1,
     138,    36,   138,    -1,   138,    35,   138,    -1,   138,    38,
     138,    -1,   138,    37,   138,    -1,   138,    39,   138,    -1,
     138,    40,   138,    -1,   138,    42,   138,    -1,   138,    43,
     138,    -1,   138,    44,   138,    -1,    54,   138,    59,    -1,
     131,    -1,    24,    54,    59,    -1,    24,    54,   138,    59,
      -1,    24,    -1,    24,    54,    59,    -1,    24,    54,   138,
      59,    -1,    24,    54,    10,    59,    -1,    24,    -1
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
     467,   470,   471,   474,   478,   481,   484,   487,   489,   491,
     495,   497,   500,   503,   507,   511,   513,   515,   519,   523,
     527,   531,   535,   539,   543,   547,   550,   553,   556,   560,
     564,   568,   572,   576,   580,   584,   588,   592,   596,   600,
     602,   606,   611,   613,   617,   622,   627
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  CfdgParser::yyrline_[] =
  {
         0,   178,   178,   178,   181,   186,   190,   195,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   234,   235,   236,   237,
     238,   239,   240,   241,   245,   246,   247,   248,   249,   253,
     262,   273,   280,   280,   283,   284,   288,   299,   311,   322,
     332,   342,   357,   366,   370,   378,   382,   390,   399,   415,
     425,   433,   442,   457,   465,   473,   486,   507,   515,   524,
     537,   544,   550,   556,   561,   567,   568,   572,   573,   577,
     583,   589,   590,   594,   595,   596,   600,   601,   602,   603,
     607,   610,   614,   617,   621,   628,   638,   644,   650,   658,
     668,   670,   676,   678,   684,   687,   691,   695,   697,   699,
     708,   708,   720,   729,   738,   747,   754,   761,   762,   763,
     767,   769,   777,   789,   790,   791,   792,   793,   794,   795,
     796,   797,   801,   807,   810,   814,   816,   822,   831,   833,
     844,   844,   859,   870,   882,   895,   907,   916,   924,   935,
     944,   970,   981,   986,   993,   998,  1005,  1008,  1012,  1015,
    1019,  1022,  1026,  1031,  1041,  1046,  1053,  1057,  1063,  1065,
    1067,  1069,  1071,  1073,  1078,  1085,  1087,  1089,  1094,  1099,
    1101,  1103,  1105,  1107,  1109,  1111,  1113,  1115,  1117,  1119,
    1121,  1123,  1125,  1127,  1129,  1131,  1133,  1135,  1137,  1139,
    1143,  1148,  1154,  1161,  1166,  1172,  1178
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
      54,    59,    49,    47,    45,    46,     2,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    60,     2,
       2,     2,     2,     2,    56,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    55,     2,    61,    53,    48,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    57,    62,    58,     2,     2,     2,     2,
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
      51,    52
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int CfdgParser::yyeof_ = 0;
  const int CfdgParser::yylast_ = 725;
  const int CfdgParser::yynnts_ = 78;
  const int CfdgParser::yyempty_ = -2;
  const int CfdgParser::yyfinal_ = 6;
  const int CfdgParser::yyterror_ = 1;
  const int CfdgParser::yyerrcode_ = 256;
  const int CfdgParser::yyntokens_ = 63;

  const unsigned int CfdgParser::yyuser_token_number_max_ = 301;
  const CfdgParser::token_number_type CfdgParser::yyundef_token_ = 2;


} // yy

/* Line 1053 of lalr1.cc  */
#line 3443 "cfdg.tab.cpp"


/* Line 1055 of lalr1.cc  */
#line 1184 "../../src-common/cfdg.ypp"


void yy::CfdgParser::error(const CfdgParser::location_type& l, const std::string& m)
{
    driver.error(l, m);
}

