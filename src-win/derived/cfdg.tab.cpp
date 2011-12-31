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
#line 167 "../../src-common/cfdg.ypp"

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
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 261 "cfdg.tab.cpp"
	break;
      case 27: /* "USER_FILENAME" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 270 "cfdg.tab.cpp"
	break;
      case 28: /* "USER_QSTRING" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 279 "cfdg.tab.cpp"
	break;
      case 33: /* "USER_PATHOP" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 288 "cfdg.tab.cpp"
	break;
      case 68: /* "statement" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 297 "cfdg.tab.cpp"
	break;
      case 69: /* "statement_v2" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 306 "cfdg.tab.cpp"
	break;
      case 75: /* "fileString" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 315 "cfdg.tab.cpp"
	break;
      case 76: /* "fileNameSpace" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 324 "cfdg.tab.cpp"
	break;
      case 77: /* "initialization" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 333 "cfdg.tab.cpp"
	break;
      case 78: /* "initialization_v2" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 342 "cfdg.tab.cpp"
	break;
      case 79: /* "background" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 351 "cfdg.tab.cpp"
	break;
      case 80: /* "tile" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 360 "cfdg.tab.cpp"
	break;
      case 81: /* "size" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 369 "cfdg.tab.cpp"
	break;
      case 83: /* "global_definition_header" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 378 "cfdg.tab.cpp"
	break;
      case 84: /* "definition_header" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 387 "cfdg.tab.cpp"
	break;
      case 86: /* "shape" */

/* Line 479 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->shapeObj); };

/* Line 479 of lalr1.cc  */
#line 396 "cfdg.tab.cpp"
	break;
      case 87: /* "shape_singleton_header" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 405 "cfdg.tab.cpp"
	break;
      case 88: /* "shape_singleton" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 414 "cfdg.tab.cpp"
	break;
      case 89: /* "rule_header_v2" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 423 "cfdg.tab.cpp"
	break;
      case 91: /* "rule_header" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 432 "cfdg.tab.cpp"
	break;
      case 92: /* "path_header" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 441 "cfdg.tab.cpp"
	break;
      case 93: /* "rule" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 450 "cfdg.tab.cpp"
	break;
      case 94: /* "path" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 459 "cfdg.tab.cpp"
	break;
      case 95: /* "path_header_v2" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 468 "cfdg.tab.cpp"
	break;
      case 103: /* "parameter_spec" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 477 "cfdg.tab.cpp"
	break;
      case 106: /* "pathOp_simple_v2" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 486 "cfdg.tab.cpp"
	break;
      case 107: /* "element_simple" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 495 "cfdg.tab.cpp"
	break;
      case 112: /* "element" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 504 "cfdg.tab.cpp"
	break;
      case 115: /* "pathOp_v2" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 513 "cfdg.tab.cpp"
	break;
      case 117: /* "element_loop" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 522 "cfdg.tab.cpp"
	break;
      case 120: /* "replacement_simple_v2" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 531 "cfdg.tab.cpp"
	break;
      case 121: /* "replacement_v2" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 540 "cfdg.tab.cpp"
	break;
      case 122: /* "loopHeader_v2" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 549 "cfdg.tab.cpp"
	break;
      case 124: /* "loopHeader" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 558 "cfdg.tab.cpp"
	break;
      case 125: /* "loopexp" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 567 "cfdg.tab.cpp"
	break;
      case 126: /* "ifHeader" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ifObj); };

/* Line 479 of lalr1.cc  */
#line 576 "cfdg.tab.cpp"
	break;
      case 127: /* "ifElseHeader" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ifObj); };

/* Line 479 of lalr1.cc  */
#line 585 "cfdg.tab.cpp"
	break;
      case 128: /* "transHeader" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 594 "cfdg.tab.cpp"
	break;
      case 129: /* "switchHeader" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->switchObj); };

/* Line 479 of lalr1.cc  */
#line 603 "cfdg.tab.cpp"
	break;
      case 130: /* "caseHeader" */

/* Line 479 of lalr1.cc  */
#line 166 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); };

/* Line 479 of lalr1.cc  */
#line 612 "cfdg.tab.cpp"
	break;
      case 131: /* "modification_v2" */

/* Line 479 of lalr1.cc  */
#line 157 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 621 "cfdg.tab.cpp"
	break;
      case 132: /* "modification" */

/* Line 479 of lalr1.cc  */
#line 157 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 630 "cfdg.tab.cpp"
	break;
      case 133: /* "buncha_pathop_adjustments" */

/* Line 479 of lalr1.cc  */
#line 156 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 639 "cfdg.tab.cpp"
	break;
      case 134: /* "buncha_adjustments" */

/* Line 479 of lalr1.cc  */
#line 156 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 648 "cfdg.tab.cpp"
	break;
      case 136: /* "adjustment" */

/* Line 479 of lalr1.cc  */
#line 156 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 657 "cfdg.tab.cpp"
	break;
      case 137: /* "explist" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 666 "cfdg.tab.cpp"
	break;
      case 138: /* "exp" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 675 "cfdg.tab.cpp"
	break;
      case 139: /* "exp2" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 684 "cfdg.tab.cpp"
	break;
      case 140: /* "expfunc" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 693 "cfdg.tab.cpp"
	break;
      case 141: /* "exp2func" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
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
#line 182 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 6:

/* Line 677 of lalr1.cc  */
#line 191 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 9:

/* Line 677 of lalr1.cc  */
#line 201 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 10:

/* Line 677 of lalr1.cc  */
#line 202 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 13:

/* Line 677 of lalr1.cc  */
#line 205 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].shapeObj); }
    break;

  case 15:

/* Line 677 of lalr1.cc  */
#line 207 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 16:

/* Line 677 of lalr1.cc  */
#line 208 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 19:

/* Line 677 of lalr1.cc  */
#line 217 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 20:

/* Line 677 of lalr1.cc  */
#line 218 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 25:

/* Line 677 of lalr1.cc  */
#line 223 "../../src-common/cfdg.ypp"
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
#line 235 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 27:

/* Line 677 of lalr1.cc  */
#line 236 "../../src-common/cfdg.ypp"
    {}
    break;

  case 28:

/* Line 677 of lalr1.cc  */
#line 237 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 31:

/* Line 677 of lalr1.cc  */
#line 240 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 32:

/* Line 677 of lalr1.cc  */
#line 241 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 33:

/* Line 677 of lalr1.cc  */
#line 242 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 34:

/* Line 677 of lalr1.cc  */
#line 246 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 35:

/* Line 677 of lalr1.cc  */
#line 247 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 36:

/* Line 677 of lalr1.cc  */
#line 248 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 37:

/* Line 677 of lalr1.cc  */
#line 249 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 38:

/* Line 677 of lalr1.cc  */
#line 250 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(1) - (1)].ruleObj); }
    break;

  case 39:

/* Line 677 of lalr1.cc  */
#line 254 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(2) - (2)].string));
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(NULL);
            driver.IncludeFile(*file);
        }
    break;

  case 40:

/* Line 677 of lalr1.cc  */
#line 263 "../../src-common/cfdg.ypp"
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
#line 274 "../../src-common/cfdg.ypp"
    {
            if (driver.EndInclude())
                YYACCEPT;
        }
    break;

  case 44:

/* Line 677 of lalr1.cc  */
#line 284 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 45:

/* Line 677 of lalr1.cc  */
#line 285 "../../src-common/cfdg.ypp"
    { (yyval.string) = NULL; }
    break;

  case 46:

/* Line 677 of lalr1.cc  */
#line 289 "../../src-common/cfdg.ypp"
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
#line 300 "../../src-common/cfdg.ypp"
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
#line 312 "../../src-common/cfdg.ypp"
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
#line 323 "../../src-common/cfdg.ypp"
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
#line 333 "../../src-common/cfdg.ypp"
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
#line 343 "../../src-common/cfdg.ypp"
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
#line 358 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(2) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            if (var.get())
                driver.NextParameter(*var, exp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 53:

/* Line 677 of lalr1.cc  */
#line 367 "../../src-common/cfdg.ypp"
    {
            driver.push_paramDecls(*(yysemantic_stack_[(3) - (1)].string), (yyloc));
            (yyval.string) = (yysemantic_stack_[(3) - (1)].string);
        }
    break;

  case 54:

/* Line 677 of lalr1.cc  */
#line 371 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            error((yylocation_stack_[(3) - (1)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 55:

/* Line 677 of lalr1.cc  */
#line 379 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            (yyval.string) = (yysemantic_stack_[(2) - (1)].string);
        }
    break;

  case 56:

/* Line 677 of lalr1.cc  */
#line 383 "../../src-common/cfdg.ypp"
    {
            driver.isFunction = false;
            error((yylocation_stack_[(2) - (1)]), "Reserved keyword: adjustment");
            (yyval.string) = 0;
        }
    break;

  case 57:

/* Line 677 of lalr1.cc  */
#line 391 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(2) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(2) - (2)].expression));
            if (var.get())
                driver.NextParameter(*var, exp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 58:

/* Line 677 of lalr1.cc  */
#line 400 "../../src-common/cfdg.ypp"
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
#line 416 "../../src-common/cfdg.ypp"
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
#line 426 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(3) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 61:

/* Line 677 of lalr1.cc  */
#line 434 "../../src-common/cfdg.ypp"
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
#line 443 "../../src-common/cfdg.ypp"
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
#line 458 "../../src-common/cfdg.ypp"
    {
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 64:

/* Line 677 of lalr1.cc  */
#line 466 "../../src-common/cfdg.ypp"
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
#line 474 "../../src-common/cfdg.ypp"
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
#line 487 "../../src-common/cfdg.ypp"
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
#line 508 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 68:

/* Line 677 of lalr1.cc  */
#line 516 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
            driver.SetShape(NULL);
        }
    break;

  case 69:

/* Line 677 of lalr1.cc  */
#line 525 "../../src-common/cfdg.ypp"
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
#line 538 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 71:

/* Line 677 of lalr1.cc  */
#line 545 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(2) - (1)].string));
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(*type, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
		}
    break;

  case 72:

/* Line 677 of lalr1.cc  */
#line 551 "../../src-common/cfdg.ypp"
    {
            static std::string shapeStr("shape");
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(shapeStr, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 73:

/* Line 677 of lalr1.cc  */
#line 557 "../../src-common/cfdg.ypp"
    {
            delete (yysemantic_stack_[(2) - (1)].string);
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 74:

/* Line 677 of lalr1.cc  */
#line 562 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (2)]), "Reserved keyword: adjustment");
        }
    break;

  case 79:

/* Line 677 of lalr1.cc  */
#line 578 "../../src-common/cfdg.ypp"
    {
            static const std::string numtype("number");
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            driver.NextParameterDecl(numtype, *var, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 80:

/* Line 677 of lalr1.cc  */
#line 584 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Reserved keyword: adjustment");
        }
    break;

  case 83:

/* Line 677 of lalr1.cc  */
#line 595 "../../src-common/cfdg.ypp"
    { driver.isFunction = true; }
    break;

  case 84:

/* Line 677 of lalr1.cc  */
#line 596 "../../src-common/cfdg.ypp"
    { driver.isFunction = true; }
    break;

  case 85:

/* Line 677 of lalr1.cc  */
#line 597 "../../src-common/cfdg.ypp"
    { driver.isFunction = false; }
    break;

  case 86:

/* Line 677 of lalr1.cc  */
#line 601 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(3) - (2)].expression);}
    break;

  case 87:

/* Line 677 of lalr1.cc  */
#line 602 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTexpression((yyloc)); }
    break;

  case 88:

/* Line 677 of lalr1.cc  */
#line 603 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 89:

/* Line 677 of lalr1.cc  */
#line 604 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 90:

/* Line 677 of lalr1.cc  */
#line 608 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 92:

/* Line 677 of lalr1.cc  */
#line 615 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 94:

/* Line 677 of lalr1.cc  */
#line 622 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string));
            exp_ptr mod((yysemantic_stack_[(4) - (3)].expression));
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = new ASTpathOp(*pop, mod, false, (yyloc));
        }
    break;

  case 95:

/* Line 677 of lalr1.cc  */
#line 629 "../../src-common/cfdg.ypp"
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
#line 639 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string));
            exp_ptr mod((yysemantic_stack_[(4) - (3)].expression));
            (yyval.component) = new ASTpathOp(*pop, mod, true, (yyloc));
        }
    break;

  case 97:

/* Line 677 of lalr1.cc  */
#line 645 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(3) - (1)].string));
            exp_ptr mod;
            (yyval.component) = new ASTpathOp(*pop, mod, true, (yyloc));
        }
    break;

  case 98:

/* Line 677 of lalr1.cc  */
#line 651 "../../src-common/cfdg.ypp"
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
#line 659 "../../src-common/cfdg.ypp"
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
#line 669 "../../src-common/cfdg.ypp"
    { }
    break;

  case 101:

/* Line 677 of lalr1.cc  */
#line 671 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 102:

/* Line 677 of lalr1.cc  */
#line 677 "../../src-common/cfdg.ypp"
    { }
    break;

  case 103:

/* Line 677 of lalr1.cc  */
#line 679 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 104:

/* Line 677 of lalr1.cc  */
#line 685 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer(driver.switchStack.top());
        }
    break;

  case 107:

/* Line 677 of lalr1.cc  */
#line 696 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 108:

/* Line 677 of lalr1.cc  */
#line 698 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 109:

/* Line 677 of lalr1.cc  */
#line 700 "../../src-common/cfdg.ypp"
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
#line 709 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            driver.push_repContainer((yysemantic_stack_[(2) - (1)].loopObj)->mFinallyBody);
        }
    break;

  case 111:

/* Line 677 of lalr1.cc  */
#line 712 "../../src-common/cfdg.ypp"
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
#line 721 "../../src-common/cfdg.ypp"
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
#line 730 "../../src-common/cfdg.ypp"
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
#line 739 "../../src-common/cfdg.ypp"
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
#line 749 "../../src-common/cfdg.ypp"
    {
            (yysemantic_stack_[(4) - (1)].switchObj)->unify();
            (yyval.component) = (yysemantic_stack_[(4) - (1)].switchObj);
            driver.switchStack.pop();
        }
    break;

  case 116:

/* Line 677 of lalr1.cc  */
#line 755 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 117:

/* Line 677 of lalr1.cc  */
#line 762 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 118:

/* Line 677 of lalr1.cc  */
#line 763 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 119:

/* Line 677 of lalr1.cc  */
#line 764 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 120:

/* Line 677 of lalr1.cc  */
#line 768 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 121:

/* Line 677 of lalr1.cc  */
#line 770 "../../src-common/cfdg.ypp"
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
#line 778 "../../src-common/cfdg.ypp"
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
#line 790 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 124:

/* Line 677 of lalr1.cc  */
#line 791 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 127:

/* Line 677 of lalr1.cc  */
#line 794 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 132:

/* Line 677 of lalr1.cc  */
#line 802 "../../src-common/cfdg.ypp"
    {
            (yyval.loopObj) = (yysemantic_stack_[(2) - (1)].loopObj);
        }
    break;

  case 133:

/* Line 677 of lalr1.cc  */
#line 808 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 135:

/* Line 677 of lalr1.cc  */
#line 815 "../../src-common/cfdg.ypp"
    { }
    break;

  case 136:

/* Line 677 of lalr1.cc  */
#line 817 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 137:

/* Line 677 of lalr1.cc  */
#line 823 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), (yylocation_stack_[(2) - (1)])));
            (yyval.component) = new ASTreplacement(*r, r->entropyVal, mod, (yyloc));
        }
    break;

  case 138:

/* Line 677 of lalr1.cc  */
#line 832 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 139:

/* Line 677 of lalr1.cc  */
#line 834 "../../src-common/cfdg.ypp"
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
#line 845 "../../src-common/cfdg.ypp"
    { ++driver.mLocalStackDepth; }
    break;

  case 141:

/* Line 677 of lalr1.cc  */
#line 845 "../../src-common/cfdg.ypp"
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
#line 860 "../../src-common/cfdg.ypp"
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
#line 871 "../../src-common/cfdg.ypp"
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
#line 883 "../../src-common/cfdg.ypp"
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
#line 896 "../../src-common/cfdg.ypp"
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
#line 908 "../../src-common/cfdg.ypp"
    {
            exp_ptr cond((yysemantic_stack_[(4) - (3)].expression));
            if_ptr ifHeader(new ASTif(cond, (yylocation_stack_[(4) - (3)])));
            driver.push_repContainer(ifHeader->mThenBody);
            (yyval.ifObj) = ifHeader.release();
        }
    break;

  case 147:

/* Line 677 of lalr1.cc  */
#line 917 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ifObj));
            driver.push_repContainer((yysemantic_stack_[(3) - (1)].ifObj)->mElseBody);
            (yyval.ifObj) = (yysemantic_stack_[(3) - (1)].ifObj);
        }
    break;

  case 148:

/* Line 677 of lalr1.cc  */
#line 925 "../../src-common/cfdg.ypp"
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
#line 936 "../../src-common/cfdg.ypp"
    {
            exp_ptr caseVal((yysemantic_stack_[(4) - (3)].expression));
            switch_ptr switchHeader(new ASTswitch(caseVal, (yylocation_stack_[(4) - (3)])));
            driver.switchStack.push(switchHeader.get());
            (yyval.switchObj) = switchHeader.release();
        }
    break;

  case 150:

/* Line 677 of lalr1.cc  */
#line 945 "../../src-common/cfdg.ypp"
    {
            exp_ptr valExp((yysemantic_stack_[(3) - (2)].expression));
            
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
            (yyval.modToken) = 0;
        }
    break;

  case 151:

/* Line 677 of lalr1.cc  */
#line 972 "../../src-common/cfdg.ypp"
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
#line 983 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod(ASToperator::MakeCanonical(driver.mCanonicalMods));
            (yyval.mod) = driver.MakeModification(mod, (yyloc));
        }
    break;

  case 153:

/* Line 677 of lalr1.cc  */
#line 988 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(3) - (2)].expression));
            (yyval.mod) = driver.MakeModification(mod, (yyloc));
        }
    break;

  case 154:

/* Line 677 of lalr1.cc  */
#line 995 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod(ASToperator::MakeCanonical(driver.mCanonicalMods));
            (yyval.mod) = driver.MakeModification(mod, (yyloc));
        }
    break;

  case 155:

/* Line 677 of lalr1.cc  */
#line 1000 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(5) - (3)].expression));
            (yyval.mod) = driver.MakeModification(mod, (yyloc));
        }
    break;

  case 156:

/* Line 677 of lalr1.cc  */
#line 1007 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTcons::Cons((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 157:

/* Line 677 of lalr1.cc  */
#line 1010 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 158:

/* Line 677 of lalr1.cc  */
#line 1014 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTcons::Cons((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 159:

/* Line 677 of lalr1.cc  */
#line 1017 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 160:

/* Line 677 of lalr1.cc  */
#line 1021 "../../src-common/cfdg.ypp"
    {
            ((yysemantic_stack_[(2) - (2)].expression))->flatten(driver.mCanonicalMods);
        }
    break;

  case 161:

/* Line 677 of lalr1.cc  */
#line 1024 "../../src-common/cfdg.ypp"
    { driver.mCanonicalMods.clear(); }
    break;

  case 162:

/* Line 677 of lalr1.cc  */
#line 1028 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].expression));
            (yyval.expression) = driver.MakeModTerm((yysemantic_stack_[(2) - (1)].modToken), mod, (yyloc));
        }
    break;

  case 163:

/* Line 677 of lalr1.cc  */
#line 1033 "../../src-common/cfdg.ypp"
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
#line 1043 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.expression) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 165:

/* Line 677 of lalr1.cc  */
#line 1048 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.expression) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 166:

/* Line 677 of lalr1.cc  */
#line 1055 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTcons::Cons((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 167:

/* Line 677 of lalr1.cc  */
#line 1059 "../../src-common/cfdg.ypp"
    { 
            (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); 
        }
    break;

  case 168:

/* Line 677 of lalr1.cc  */
#line 1065 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 169:

/* Line 677 of lalr1.cc  */
#line 1067 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 170:

/* Line 677 of lalr1.cc  */
#line 1069 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 171:

/* Line 677 of lalr1.cc  */
#line 1071 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 172:

/* Line 677 of lalr1.cc  */
#line 1073 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 173:

/* Line 677 of lalr1.cc  */
#line 1075 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 174:

/* Line 677 of lalr1.cc  */
#line 1077 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 175:

/* Line 677 of lalr1.cc  */
#line 1082 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 176:

/* Line 677 of lalr1.cc  */
#line 1089 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 177:

/* Line 677 of lalr1.cc  */
#line 1091 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(Renderer::Infinity, (yyloc)); }
    break;

  case 178:

/* Line 677 of lalr1.cc  */
#line 1093 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 179:

/* Line 677 of lalr1.cc  */
#line 1095 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 180:

/* Line 677 of lalr1.cc  */
#line 1100 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 181:

/* Line 677 of lalr1.cc  */
#line 1105 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression));   }
    break;

  case 182:

/* Line 677 of lalr1.cc  */
#line 1107 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('+', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 183:

/* Line 677 of lalr1.cc  */
#line 1109 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('-', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 184:

/* Line 677 of lalr1.cc  */
#line 1111 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('_', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 185:

/* Line 677 of lalr1.cc  */
#line 1113 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('*', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 186:

/* Line 677 of lalr1.cc  */
#line 1115 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('/', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 187:

/* Line 677 of lalr1.cc  */
#line 1117 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 188:

/* Line 677 of lalr1.cc  */
#line 1119 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 189:

/* Line 677 of lalr1.cc  */
#line 1121 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('!', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 190:

/* Line 677 of lalr1.cc  */
#line 1123 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('^', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 191:

/* Line 677 of lalr1.cc  */
#line 1125 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('<', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 192:

/* Line 677 of lalr1.cc  */
#line 1127 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('L', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 193:

/* Line 677 of lalr1.cc  */
#line 1129 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('>', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 194:

/* Line 677 of lalr1.cc  */
#line 1131 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('G', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 195:

/* Line 677 of lalr1.cc  */
#line 1133 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('=', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 196:

/* Line 677 of lalr1.cc  */
#line 1135 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('n', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 197:

/* Line 677 of lalr1.cc  */
#line 1137 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('&', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 198:

/* Line 677 of lalr1.cc  */
#line 1139 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('|', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 199:

/* Line 677 of lalr1.cc  */
#line 1141 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('X', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 200:

/* Line 677 of lalr1.cc  */
#line 1143 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 201:

/* Line 677 of lalr1.cc  */
#line 1145 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].mod); }
    break;

  case 202:

/* Line 677 of lalr1.cc  */
#line 1149 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), true);
        }
    break;

  case 203:

/* Line 677 of lalr1.cc  */
#line 1154 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), true);
        }
    break;

  case 204:

/* Line 677 of lalr1.cc  */
#line 1160 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 205:

/* Line 677 of lalr1.cc  */
#line 1166 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 206:

/* Line 677 of lalr1.cc  */
#line 1173 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 207:

/* Line 677 of lalr1.cc  */
#line 1178 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 208:

/* Line 677 of lalr1.cc  */
#line 1184 "../../src-common/cfdg.ypp"
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 209:

/* Line 677 of lalr1.cc  */
#line 1190 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args(new ASTexpression((yylocation_stack_[(4) - (1)]) + (yylocation_stack_[(4) - (4)])));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 210:

/* Line 677 of lalr1.cc  */
#line 1196 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;



/* Line 677 of lalr1.cc  */
#line 2637 "cfdg.tab.cpp"
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
  const short int CfdgParser::yypact_ninf_ = -247;
  const short int
  CfdgParser::yypact_[] =
  {
        50,  -247,  -247,    41,   795,   814,  -247,    -2,  -247,    49,
      91,    10,    63,  -247,     5,   188,  -247,    63,  -247,  -247,
    -247,  -247,  -247,  -247,  -247,  -247,    65,  -247,    88,  -247,
     137,   143,   124,   153,   179,    63,   133,   188,   146,    63,
    -247,  -247,  -247,  -247,  -247,  -247,   309,   150,  -247,  -247,
    -247,   187,   189,  -247,  -247,   214,   169,   195,  -247,  -247,
    -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,
    -247,   197,   199,  -247,   199,   120,   249,  -247,  -247,   253,
    -247,   243,   188,  -247,   229,   230,  -247,   309,  -247,   309,
     309,   309,   232,  -247,   666,  -247,  -247,    25,  -247,  -247,
    -247,  -247,  -247,  -247,     0,    93,   138,    48,   183,   234,
      28,  -247,  -247,  -247,  -247,  -247,  -247,   -21,  -247,  -247,
    -247,  -247,   309,   201,   237,   237,   237,   366,  -247,   113,
     309,   309,   309,   309,   309,   309,   309,   309,   309,   309,
     309,   309,   309,   309,   309,   309,   309,   309,   262,   284,
     238,   240,    11,    22,   246,    74,  -247,   309,  -247,  -247,
    -247,  -247,   286,   247,   247,   247,   247,   241,   101,   109,
     157,     7,  -247,  -247,  -247,  -247,    63,   250,  -247,  -247,
    -247,    -5,  -247,  -247,  -247,  -247,   292,    27,   171,  -247,
    -247,  -247,  -247,   186,   244,  -247,   396,  -247,    33,   142,
    -247,   -16,   162,  -247,   426,   251,  -247,   456,  -247,   122,
    -247,   344,   344,   295,   295,   295,   295,   759,   759,   739,
     718,   696,   666,   182,   182,   182,   237,   237,   237,   197,
     293,    16,   234,   666,   309,   309,  -247,  -247,  -247,  -247,
     234,  -247,   227,  -247,   666,  -247,  -247,  -247,  -247,   298,
    -247,  -247,  -247,  -247,  -247,   259,   264,  -247,  -247,   157,
     157,   309,   157,   178,  -247,  -247,  -247,  -247,  -247,  -247,
    -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,    63,   248,
    -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,    28,
    -247,  -247,  -247,  -247,  -247,   258,   234,   309,   309,  -247,
     486,   516,  -247,  -247,   546,   247,   130,  -247,    90,   309,
     268,  -247,  -247,   576,   254,   157,   157,  -247,    63,   147,
     140,   161,  -247,  -247,  -247,   234,   234,  -247,  -247,  -247,
    -247,  -247,   260,   309,  -247,  -247,   247,   606,  -247,   636,
    -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,
    -247,   336,  -247,  -247,  -247,  -247
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
      37,     0,     0,    35,     0,   210,   176,     0,   177,     0,
       0,     0,   161,   201,    52,   178,    59,     0,    91,    91,
      32,    33,    62,    31,     0,     0,     0,     0,     0,    47,
       0,    58,    66,    80,    79,    84,    82,     0,    54,    53,
      44,    40,     0,     0,   189,   187,   188,     0,   159,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    89,     0,     0,    60,     0,   108,   107,
      90,   116,   109,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   153,   158,   152,   160,     0,     0,    63,   138,
     133,     0,   125,   126,   129,   131,   130,     0,     0,    70,
     120,    92,   122,     0,     0,    88,     0,    46,     0,     0,
      76,     0,     0,    83,     0,     0,   206,     0,   200,     0,
     154,   179,   180,   192,   191,   194,   193,   195,   196,   197,
     198,   199,   181,   183,   182,   184,   185,   186,   190,    89,
       0,   210,     0,   145,     0,     0,    56,   148,    55,   118,
       0,   117,     0,   119,    57,   110,    91,   132,   101,   112,
     113,   114,   105,    67,    68,     0,   205,   168,   169,     0,
       0,     0,   162,   167,   171,   164,   165,   137,   140,   134,
     139,   136,   128,   127,   124,    95,   123,   157,     0,     0,
      93,   103,   121,    87,    86,    74,    72,    73,    71,     0,
      77,    81,   208,   209,   207,     0,     0,     0,     0,   144,
       0,     0,    98,    97,     0,     0,     0,   147,     0,     0,
       0,   172,   173,     0,   166,     0,     0,   163,     0,     0,
       0,     0,    75,   155,    99,     0,     0,   146,   149,    96,
     111,   100,     0,     0,   115,   104,     0,     0,   202,     0,
     170,   174,   175,   141,   135,    94,   156,   102,   143,   142,
     151,     0,   106,   204,   203,   150
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yypgoto_[] =
  {
      -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,
     321,    71,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,
    -247,  -247,  -247,  -247,  -247,   322,  -247,  -247,  -247,  -247,
    -247,  -247,  -247,    45,  -247,   256,   134,  -247,   301,  -124,
     -91,    58,   148,  -247,  -154,  -247,  -247,  -247,   -93,  -247,
    -247,  -247,  -247,  -247,    78,  -247,   167,  -247,   -98,  -247,
    -247,   -19,  -247,  -247,  -247,  -247,  -247,   -11,  -104,  -247,
     223,   261,  -102,  -247,  -246,   -44,  -247,  -247
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yydefgoto_[] =
  {
        -1,     3,     4,     5,    40,    18,    19,    41,    20,    42,
      21,    67,    82,    44,    22,    23,    24,    25,    45,    46,
     157,   158,    47,    48,    49,    26,    27,    51,    52,    53,
      54,    28,    29,   200,   201,   111,   116,   117,    76,   109,
      97,   107,   190,   159,   247,   282,   308,   335,   248,   305,
     161,   191,   192,   162,   106,   270,   179,   180,   181,   318,
     163,   232,   164,   165,   166,   167,   336,   275,    93,   320,
     104,   105,   173,   262,   263,   233,   264,    95
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char CfdgParser::yytable_ninf_ = -1;
  const unsigned short int
  CfdgParser::yytable_[] =
  {
        61,    62,    94,   175,   160,   197,    68,   168,   169,   193,
     249,   250,   251,   311,   312,    63,   314,   170,   171,   176,
      58,   236,    55,    77,    78,   202,   298,   175,    83,   240,
     289,   265,   238,   148,   198,   266,   149,   273,   150,   203,
     151,     6,   152,   124,   290,   125,   126,   127,   237,   153,
     285,   154,   199,   269,     1,     2,   182,   286,   155,   183,
      64,   184,   172,   185,   196,   186,    59,    92,    60,   341,
     342,   123,   187,    56,   177,   160,   160,   108,   204,   207,
     239,   188,   274,    59,   156,    60,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   332,   296,   333,   189,    80,   148,
     170,   171,   149,   244,   150,    57,   151,   148,   152,    59,
     149,    60,   150,    69,   151,   153,   152,   154,   299,   242,
     170,   171,   243,   153,   155,   154,   302,   113,   148,   170,
     171,   149,   155,   150,   114,   151,    70,   152,    56,   334,
      73,   330,   174,   121,   153,   306,   154,   170,   171,   287,
     253,    71,   176,   155,   177,   267,   288,    72,   254,   182,
     255,   176,   183,   177,   184,   210,   185,    74,   186,   113,
     115,   256,   352,   257,   295,   187,   114,   177,    75,   331,
     300,   301,   324,   194,   188,   102,    84,   178,   304,   345,
     315,   316,   258,    81,   259,   260,   344,    85,    96,    86,
     278,   205,   261,   160,    84,    65,    66,   313,   346,   279,
     347,   348,   349,   193,    87,    85,   276,    86,    88,   277,
      89,    90,   145,   146,    75,    59,   147,    60,    91,    92,
      84,   317,    87,   195,   280,    98,    88,    99,    89,    90,
     103,    85,   108,    86,   110,   148,    91,    92,   149,   118,
     150,   206,   151,   119,   152,   337,   339,   120,    87,   100,
     101,   153,    88,   154,    89,    90,   315,   316,   325,   326,
     155,    84,    91,    92,   122,   123,   229,   303,   128,   351,
      92,   147,    85,   234,    86,   235,   241,    84,   245,   252,
     268,   230,   272,   297,   283,   246,   277,   343,   231,    87,
      86,   293,   307,    88,   309,    89,    90,   130,   131,   310,
     323,   350,    84,    91,    92,    87,    43,    50,   338,    88,
     112,    89,    90,    85,   322,    86,   291,    79,   321,    91,
      92,   281,   142,   143,   144,   145,   146,   319,   271,   147,
      87,   209,     0,   129,    88,     0,    89,    90,   130,   131,
       0,     0,     0,     0,    91,    92,     0,     0,     0,     0,
       0,   132,   133,   134,   135,   136,   137,     0,   138,   139,
     140,     0,   141,   142,   143,   144,   145,   146,   130,   131,
     147,   142,   143,   144,   145,   146,     0,   355,   147,     0,
       0,   132,   133,   134,   135,   136,   137,     0,   138,   139,
     140,     0,   141,   142,   143,   144,   145,   146,   130,   131,
     147,     0,     0,     0,     0,     0,   208,     0,     0,     0,
       0,   132,   133,   134,   135,   136,   137,     0,   138,   139,
     140,     0,   141,   142,   143,   144,   145,   146,   130,   131,
     147,     0,     0,     0,     0,     0,   284,     0,     0,     0,
       0,   132,   133,   134,   135,   136,   137,     0,   138,   139,
     140,     0,   141,   142,   143,   144,   145,   146,   130,   131,
     147,     0,     0,     0,     0,     0,   292,     0,     0,     0,
       0,   132,   133,   134,   135,   136,   137,     0,   138,   139,
     140,     0,   141,   142,   143,   144,   145,   146,   130,   131,
     147,     0,     0,     0,     0,     0,   294,     0,     0,     0,
       0,   132,   133,   134,   135,   136,   137,     0,   138,   139,
     140,     0,   141,   142,   143,   144,   145,   146,   130,   131,
     147,     0,     0,     0,     0,     0,   327,     0,     0,     0,
       0,   132,   133,   134,   135,   136,   137,     0,   138,   139,
     140,     0,   141,   142,   143,   144,   145,   146,   130,   131,
     147,     0,     0,     0,     0,     0,   328,     0,     0,     0,
       0,   132,   133,   134,   135,   136,   137,     0,   138,   139,
     140,     0,   141,   142,   143,   144,   145,   146,   130,   131,
     147,     0,     0,     0,     0,     0,   329,     0,     0,     0,
       0,   132,   133,   134,   135,   136,   137,     0,   138,   139,
     140,     0,   141,   142,   143,   144,   145,   146,   130,   131,
     147,     0,     0,     0,     0,     0,   340,     0,     0,     0,
       0,   132,   133,   134,   135,   136,   137,     0,   138,   139,
     140,     0,   141,   142,   143,   144,   145,   146,   130,   131,
     147,     0,     0,     0,     0,     0,   353,     0,     0,     0,
       0,   132,   133,   134,   135,   136,   137,     0,   138,   139,
     140,     0,   141,   142,   143,   144,   145,   146,   130,   131,
     147,     0,     0,     0,     0,     0,   354,     0,     0,     0,
       0,   132,   133,   134,   135,   136,   137,     0,   138,   139,
     140,     0,   141,   142,   143,   144,   145,   146,   130,   131,
     147,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   132,   133,   134,   135,   136,   137,     0,   138,   139,
     130,   131,     0,   142,   143,   144,   145,   146,     0,     0,
     147,     0,     0,   132,   133,   134,   135,   136,   137,     0,
     138,   130,   131,     0,     0,   142,   143,   144,   145,   146,
       0,     0,   147,     0,   132,   133,   134,   135,   136,   137,
       0,   130,   131,     0,     0,     0,   142,   143,   144,   145,
     146,     0,     0,   147,   132,   133,   134,   135,     7,     0,
       0,     8,     9,    10,     0,     0,   142,   143,   144,   145,
     146,     0,    11,   147,    12,     0,    13,    30,     0,    14,
      31,    32,    33,     0,    15,    16,    17,     0,     0,     0,
       0,    34,     0,    35,     0,    13,     0,     0,    36,     0,
       0,     0,     0,    37,    38,    39
  };

  /* YYCHECK.  */
  const short int
  CfdgParser::yycheck_[] =
  {
        11,    12,    46,   105,    97,   109,    17,    98,    99,   107,
     164,   165,   166,   259,   260,    10,   262,    17,    18,    24,
      10,    10,    24,    34,    35,    46,    10,   129,    39,   153,
      46,    24,    10,     8,     6,    28,    11,    10,    13,    60,
      15,     0,    17,    87,    60,    89,    90,    91,   152,    24,
      17,    26,    24,    58,     4,     5,     8,    24,    33,    11,
      55,    13,    62,    15,   108,    17,    56,    56,    58,   315,
     316,    55,    24,    24,    26,   168,   169,    55,   122,   123,
      58,    33,    55,    56,    59,    58,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,    14,   229,    16,    59,    37,     8,
      17,    18,    11,   157,    13,    24,    15,     8,    17,    56,
      11,    58,    13,    58,    15,    24,    17,    26,   232,    55,
      17,    18,    58,    24,    33,    26,   240,    17,     8,    17,
      18,    11,    33,    13,    24,    15,    58,    17,    24,    59,
      26,   305,    59,    82,    24,   246,    26,    17,    18,    17,
      59,    24,    24,    33,    26,   176,    24,    24,    59,     8,
      13,    24,    11,    26,    13,    62,    15,    24,    17,    17,
      60,    24,   336,    26,    62,    24,    24,    26,    55,    59,
     234,   235,   296,    10,    33,    26,    13,    59,   242,    59,
      22,    23,    45,    57,    47,    48,    59,    24,    58,    26,
      24,    10,    55,   306,    13,    27,    28,   261,   320,    33,
      59,   325,   326,   321,    41,    24,    55,    26,    45,    58,
      47,    48,    50,    51,    55,    56,    54,    58,    55,    56,
      13,    63,    41,    60,    58,    58,    45,    58,    47,    48,
      55,    24,    55,    26,    55,     8,    55,    56,    11,    10,
      13,    60,    15,    10,    17,   309,   310,    24,    41,    55,
      56,    24,    45,    26,    47,    48,    22,    23,   297,   298,
      33,    13,    55,    56,    55,    55,    24,    60,    56,   333,
      56,    54,    24,    55,    26,    55,    50,    13,    12,    58,
      50,    17,    10,    10,    60,    58,    58,   318,    24,    41,
      26,    60,    14,    45,    55,    47,    48,    22,    23,    55,
      62,    61,    13,    55,    56,    41,     5,     5,    60,    45,
      74,    47,    48,    24,   289,    26,   202,    36,   280,    55,
      56,   193,    47,    48,    49,    50,    51,   269,   181,    54,
      41,   128,    -1,    92,    45,    -1,    47,    48,    22,    23,
      -1,    -1,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    46,    47,    48,    49,    50,    51,    22,    23,
      54,    47,    48,    49,    50,    51,    -1,    61,    54,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    46,    47,    48,    49,    50,    51,    22,    23,
      54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    46,    47,    48,    49,    50,    51,    22,    23,
      54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    46,    47,    48,    49,    50,    51,    22,    23,
      54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    46,    47,    48,    49,    50,    51,    22,    23,
      54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    46,    47,    48,    49,    50,    51,    22,    23,
      54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    46,    47,    48,    49,    50,    51,    22,    23,
      54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    46,    47,    48,    49,    50,    51,    22,    23,
      54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    46,    47,    48,    49,    50,    51,    22,    23,
      54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    46,    47,    48,    49,    50,    51,    22,    23,
      54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    46,    47,    48,    49,    50,    51,    22,    23,
      54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    46,    47,    48,    49,    50,    51,    22,    23,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      22,    23,    -1,    47,    48,    49,    50,    51,    -1,    -1,
      54,    -1,    -1,    35,    36,    37,    38,    39,    40,    -1,
      42,    22,    23,    -1,    -1,    47,    48,    49,    50,    51,
      -1,    -1,    54,    -1,    35,    36,    37,    38,    39,    40,
      -1,    22,    23,    -1,    -1,    -1,    47,    48,    49,    50,
      51,    -1,    -1,    54,    35,    36,    37,    38,     3,    -1,
      -1,     6,     7,     8,    -1,    -1,    47,    48,    49,    50,
      51,    -1,    17,    54,    19,    -1,    21,     3,    -1,    24,
       6,     7,     8,    -1,    29,    30,    31,    -1,    -1,    -1,
      -1,    17,    -1,    19,    -1,    21,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    29,    30,    31
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
      48,    55,    56,   132,   139,   141,    58,   104,    58,    58,
      55,    56,    26,    55,   134,   135,   118,   105,    55,   103,
      55,    99,    99,    17,    24,    60,   100,   101,    10,    10,
      24,    75,    55,    55,   139,   139,   139,   139,    56,   135,
      22,    23,    35,    36,    37,    38,    39,    40,    42,    43,
      44,    46,    47,    48,    49,    50,    51,    54,     8,    11,
      13,    15,    17,    24,    26,    33,    59,    84,    85,   107,
     112,   114,   117,   124,   126,   127,   128,   129,   104,   104,
      17,    18,    62,   136,    59,   136,    24,    26,    59,   120,
     121,   122,     8,    11,    13,    15,    17,    24,    33,    59,
     106,   115,   116,   122,    10,    60,   139,   132,     6,    24,
      97,    98,    46,    60,   139,    10,    60,   139,    60,   134,
      62,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,    24,
      17,    24,   125,   139,    55,    55,    10,   132,    10,    58,
     103,    50,    55,    58,   139,    12,    58,   108,   112,   108,
     108,   108,    58,    59,    59,    13,    24,    26,    45,    47,
      48,    55,   137,   138,   140,    24,    28,   131,    50,    58,
     119,   120,    10,    10,    55,   131,    55,    58,    24,    33,
      58,   106,   109,    60,    60,    17,    24,    17,    24,    46,
      60,   100,    60,    60,    60,    62,   103,    10,    10,   132,
     139,   139,   132,    60,   139,   113,   104,    14,   110,    55,
      55,   138,   138,   139,   138,    22,    23,    63,   123,   118,
     133,   105,    97,    62,   132,   125,   125,    60,    60,    60,
     108,    59,    14,    16,    59,   111,   130,   139,    60,   139,
      60,   138,   138,   131,    59,    59,   136,    59,   132,   132,
      61,   139,   108,    60,    60,    61
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
     135,   135,   136,   136,   136,   136,   137,   137,   138,   138,
     138,   138,   138,   138,   138,   138,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   140,   140,   140,   140,   141,   141,   141,   141,
     141
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
       2,     0,     2,     3,     2,     2,     2,     1,     1,     1,
       3,     1,     2,     2,     3,     3,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     4,     4,     1,     3,     4,     4,     4,
       1
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
      83,   139,    -1,    24,   102,    10,    -1,    17,   102,    10,
      -1,    24,    10,    -1,    17,    10,    -1,    84,   139,    -1,
       6,    24,    99,    -1,    86,    58,    -1,    87,   104,    59,
      -1,     7,    24,    -1,     7,    24,    26,    -1,    89,    58,
     118,    59,    -1,     7,    -1,     7,    26,    -1,     8,    24,
      99,    -1,    91,    58,   104,    59,    -1,    92,    58,   104,
      59,    -1,     8,    24,    -1,    95,    58,   105,    59,    -1,
      24,    24,    -1,     6,    24,    -1,    24,    17,    -1,     6,
      17,    -1,    98,    46,    97,    -1,    97,    -1,    55,    98,
      60,    -1,    -1,    24,    -1,    17,    -1,   101,    46,   100,
      -1,   100,    -1,    55,   101,    60,    -1,    55,    60,    -1,
      -1,    55,   139,    60,    -1,    55,    10,    60,    -1,    55,
      60,    -1,    -1,   104,   112,    -1,    -1,   105,   115,    -1,
      -1,    33,    58,   133,    59,    -1,    24,   131,    -1,    33,
      55,   139,    60,    -1,    33,    55,    60,    -1,    24,   103,
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
      -1,    11,   125,   132,    -1,   139,    -1,    13,    55,   139,
      60,    -1,   126,   108,    14,    -1,    17,   132,    -1,    15,
      55,   139,    60,    -1,    16,   139,    61,    -1,    14,    61,
      -1,    58,   135,    59,    -1,    56,   134,    62,    -1,    56,
     135,    62,    -1,    56,    56,   134,    62,    62,    -1,   133,
     136,    -1,    -1,   134,   136,    -1,    -1,   135,   136,    -1,
      -1,    17,   137,    -1,    17,   138,    63,    -1,    18,    24,
      -1,    18,    28,    -1,   137,   138,    -1,   138,    -1,    26,
      -1,    45,    -1,    55,   139,    60,    -1,   140,    -1,    47,
     138,    -1,    48,   138,    -1,   138,    22,   138,    -1,   138,
      23,   138,    -1,    26,    -1,    45,    -1,   141,    -1,   139,
      22,   139,    -1,   139,    23,   139,    -1,   139,    46,   139,
      -1,   139,    48,   139,    -1,   139,    47,   139,    -1,   139,
      49,   139,    -1,   139,    50,   139,    -1,   139,    51,   139,
      -1,    47,   139,    -1,    48,   139,    -1,    41,   139,    -1,
     139,    54,   139,    -1,   139,    36,   139,    -1,   139,    35,
     139,    -1,   139,    38,   139,    -1,   139,    37,   139,    -1,
     139,    39,   139,    -1,   139,    40,   139,    -1,   139,    42,
     139,    -1,   139,    43,   139,    -1,   139,    44,   139,    -1,
      55,   139,    60,    -1,   132,    -1,    24,    55,    60,    -1,
      24,    55,   139,    60,    -1,    13,    55,   139,    60,    -1,
      24,    -1,    24,    55,    60,    -1,    24,    55,   139,    60,
      -1,    13,    55,   139,    60,    -1,    24,    55,    10,    60,
      -1,    24,    -1
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
     493,   497,   499,   502,   505,   509,   513,   515,   517,   519,
     523,   527,   531,   535,   539,   543,   547,   551,   554,   557,
     560,   564,   568,   572,   576,   580,   584,   588,   592,   596,
     600,   604,   606,   610,   615,   620,   622,   626,   631,   636,
     641
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  CfdgParser::yyrline_[] =
  {
         0,   179,   179,   179,   182,   187,   191,   196,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   235,   236,   237,   238,
     239,   240,   241,   242,   246,   247,   248,   249,   250,   254,
     263,   274,   281,   281,   284,   285,   289,   300,   312,   323,
     333,   343,   358,   367,   371,   379,   383,   391,   400,   416,
     426,   434,   443,   458,   466,   474,   487,   508,   516,   525,
     538,   545,   551,   557,   562,   568,   569,   573,   574,   578,
     584,   590,   591,   595,   596,   597,   601,   602,   603,   604,
     608,   611,   615,   618,   622,   629,   639,   645,   651,   659,
     669,   671,   677,   679,   685,   688,   692,   696,   698,   700,
     709,   709,   721,   730,   739,   748,   755,   762,   763,   764,
     768,   770,   778,   790,   791,   792,   793,   794,   795,   796,
     797,   798,   802,   808,   811,   815,   817,   823,   832,   834,
     845,   845,   860,   871,   883,   896,   908,   917,   925,   936,
     945,   972,   983,   988,   995,  1000,  1007,  1010,  1014,  1017,
    1021,  1024,  1028,  1033,  1043,  1048,  1055,  1059,  1065,  1067,
    1069,  1071,  1073,  1075,  1077,  1082,  1089,  1091,  1093,  1095,
    1100,  1105,  1107,  1109,  1111,  1113,  1115,  1117,  1119,  1121,
    1123,  1125,  1127,  1129,  1131,  1133,  1135,  1137,  1139,  1141,
    1143,  1145,  1149,  1154,  1160,  1166,  1173,  1178,  1184,  1190,
    1196
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
  const int CfdgParser::yylast_ = 845;
  const int CfdgParser::yynnts_ = 78;
  const int CfdgParser::yyempty_ = -2;
  const int CfdgParser::yyfinal_ = 6;
  const int CfdgParser::yyterror_ = 1;
  const int CfdgParser::yyerrcode_ = 256;
  const int CfdgParser::yyntokens_ = 64;

  const unsigned int CfdgParser::yyuser_token_number_max_ = 302;
  const CfdgParser::token_number_type CfdgParser::yyundef_token_ = 2;


} // yy

/* Line 1053 of lalr1.cc  */
#line 3513 "cfdg.tab.cpp"


/* Line 1055 of lalr1.cc  */
#line 1202 "../../src-common/cfdg.ypp"


void yy::CfdgParser::error(const CfdgParser::location_type& l, const std::string& m)
{
    driver.error(l, m);
}

