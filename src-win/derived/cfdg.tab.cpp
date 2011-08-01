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
      case 84: /* "shape" */

/* Line 479 of lalr1.cc  */
#line 164 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->shapeObj); };

/* Line 479 of lalr1.cc  */
#line 378 "cfdg.tab.cpp"
	break;
      case 85: /* "shape_singleton_header" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 387 "cfdg.tab.cpp"
	break;
      case 86: /* "shape_singleton" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 396 "cfdg.tab.cpp"
	break;
      case 87: /* "rule_header_v2" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 405 "cfdg.tab.cpp"
	break;
      case 89: /* "rule_header" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 414 "cfdg.tab.cpp"
	break;
      case 90: /* "path_header" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 423 "cfdg.tab.cpp"
	break;
      case 91: /* "rule" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 432 "cfdg.tab.cpp"
	break;
      case 92: /* "path" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 441 "cfdg.tab.cpp"
	break;
      case 93: /* "path_header_v2" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 450 "cfdg.tab.cpp"
	break;
      case 98: /* "parameter_spec" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 459 "cfdg.tab.cpp"
	break;
      case 101: /* "pathOp_simple_v2" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 468 "cfdg.tab.cpp"
	break;
      case 102: /* "element_simple" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 477 "cfdg.tab.cpp"
	break;
      case 107: /* "element" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 486 "cfdg.tab.cpp"
	break;
      case 110: /* "pathOp_v2" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 495 "cfdg.tab.cpp"
	break;
      case 112: /* "element_loop" */

/* Line 479 of lalr1.cc  */
#line 157 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 504 "cfdg.tab.cpp"
	break;
      case 115: /* "replacement_simple_v2" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 513 "cfdg.tab.cpp"
	break;
      case 116: /* "replacement_v2" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 522 "cfdg.tab.cpp"
	break;
      case 117: /* "loopHeader_v2" */

/* Line 479 of lalr1.cc  */
#line 157 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 531 "cfdg.tab.cpp"
	break;
      case 119: /* "loopHeader" */

/* Line 479 of lalr1.cc  */
#line 157 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 540 "cfdg.tab.cpp"
	break;
      case 120: /* "loopexp" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 549 "cfdg.tab.cpp"
	break;
      case 121: /* "ifHeader" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ifObj); };

/* Line 479 of lalr1.cc  */
#line 558 "cfdg.tab.cpp"
	break;
      case 122: /* "ifElseHeader" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ifObj); };

/* Line 479 of lalr1.cc  */
#line 567 "cfdg.tab.cpp"
	break;
      case 123: /* "transHeader" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 576 "cfdg.tab.cpp"
	break;
      case 124: /* "switchHeader" */

/* Line 479 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->switchObj); };

/* Line 479 of lalr1.cc  */
#line 585 "cfdg.tab.cpp"
	break;
      case 125: /* "caseHeader" */

/* Line 479 of lalr1.cc  */
#line 165 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); };

/* Line 479 of lalr1.cc  */
#line 594 "cfdg.tab.cpp"
	break;
      case 126: /* "modification_v2" */

/* Line 479 of lalr1.cc  */
#line 156 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 603 "cfdg.tab.cpp"
	break;
      case 127: /* "modification" */

/* Line 479 of lalr1.cc  */
#line 156 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };

/* Line 479 of lalr1.cc  */
#line 612 "cfdg.tab.cpp"
	break;
      case 128: /* "buncha_pathop_adjustments" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 621 "cfdg.tab.cpp"
	break;
      case 129: /* "buncha_adjustments" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 630 "cfdg.tab.cpp"
	break;
      case 131: /* "adjustment" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 639 "cfdg.tab.cpp"
	break;
      case 132: /* "explist" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 648 "cfdg.tab.cpp"
	break;
      case 133: /* "exp" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 657 "cfdg.tab.cpp"
	break;
      case 134: /* "exp2" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 666 "cfdg.tab.cpp"
	break;
      case 135: /* "expfunc" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 675 "cfdg.tab.cpp"
	break;
      case 136: /* "exp2func" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 684 "cfdg.tab.cpp"
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

  case 29:

/* Line 677 of lalr1.cc  */
#line 237 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 30:

/* Line 677 of lalr1.cc  */
#line 238 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 31:

/* Line 677 of lalr1.cc  */
#line 239 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 32:

/* Line 677 of lalr1.cc  */
#line 243 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 33:

/* Line 677 of lalr1.cc  */
#line 244 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 34:

/* Line 677 of lalr1.cc  */
#line 245 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].mod); }
    break;

  case 35:

/* Line 677 of lalr1.cc  */
#line 246 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 36:

/* Line 677 of lalr1.cc  */
#line 247 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(1) - (1)].ruleObj); }
    break;

  case 37:

/* Line 677 of lalr1.cc  */
#line 251 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(2) - (2)].string));
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(NULL);
            driver.IncludeFile(*file);
        }
    break;

  case 38:

/* Line 677 of lalr1.cc  */
#line 260 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(3) - (3)].string));
            str_ptr nm((yysemantic_stack_[(3) - (2)].string));
            driver.SetShape(NULL);
            driver.IncludeFile(*file);
            if (nm.get())
                driver.PushNameSpace(nm, (yylocation_stack_[(3) - (2)]));
        }
    break;

  case 39:

/* Line 677 of lalr1.cc  */
#line 271 "../../src-common/cfdg.ypp"
    {
            if (driver.EndInclude())
                YYACCEPT;
        }
    break;

  case 42:

/* Line 677 of lalr1.cc  */
#line 281 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 43:

/* Line 677 of lalr1.cc  */
#line 282 "../../src-common/cfdg.ypp"
    { (yyval.string) = NULL; }
    break;

  case 44:

/* Line 677 of lalr1.cc  */
#line 286 "../../src-common/cfdg.ypp"
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

  case 45:

/* Line 677 of lalr1.cc  */
#line 297 "../../src-common/cfdg.ypp"
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

  case 46:

/* Line 677 of lalr1.cc  */
#line 309 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (2)].string));
            driver.SetShape(NULL);
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), (yylocation_stack_[(2) - (2)])));
            rep_ptr start(new ASTreplacement(*r, *name, mod_ptr(), (yyloc)));
            driver.Initialize(start);
            (yyval.component) = 0;
        }
    break;

  case 47:

/* Line 677 of lalr1.cc  */
#line 320 "../../src-common/cfdg.ypp"
    {
            driver.SetShape(NULL);
            exp_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            static const std::string backVar("CF::Background");
            driver.lexer->maybeVersion = token::CFDG2;
            driver.NextParameter(backVar, mod, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
            (yyval.component) = 0;
        }
    break;

  case 48:

/* Line 677 of lalr1.cc  */
#line 331 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            static const std::string tileVar("CF::Tile");
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(NULL);
            driver.NextParameter(tileVar, mod, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
            (yyval.component) = 0;
        }
    break;

  case 49:

/* Line 677 of lalr1.cc  */
#line 342 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(NULL);
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

  case 50:

/* Line 677 of lalr1.cc  */
#line 358 "../../src-common/cfdg.ypp"
    {
            driver.SetShape(NULL);
        }
    break;

  case 51:

/* Line 677 of lalr1.cc  */
#line 360 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(4) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(4) - (4)].expression));
            driver.NextParameter(*var, exp, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (4)]));
        }
    break;

  case 52:

/* Line 677 of lalr1.cc  */
#line 368 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(3) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(3) - (3)].expression));
            driver.NextParameter(*var, exp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]));
        }
    break;

  case 53:

/* Line 677 of lalr1.cc  */
#line 376 "../../src-common/cfdg.ypp"
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

  case 54:

/* Line 677 of lalr1.cc  */
#line 392 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (1)].shapeObj), true);
            driver.mInPathContainer = false;
            rule_ptr rule(new ASTrule(-1, (yylocation_stack_[(2) - (1)])));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
        }
    break;

  case 55:

/* Line 677 of lalr1.cc  */
#line 402 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(3) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 56:

/* Line 677 of lalr1.cc  */
#line 410 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (2)].string));
            driver.SetShape(NULL);
            rule_ptr rule(new ASTrule(driver.StringToShape(*name, (yylocation_stack_[(2) - (2)]), false), (yyloc)));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
        }
    break;

  case 57:

/* Line 677 of lalr1.cc  */
#line 419 "../../src-common/cfdg.ypp"
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

  case 58:

/* Line 677 of lalr1.cc  */
#line 434 "../../src-common/cfdg.ypp"
    {
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 59:

/* Line 677 of lalr1.cc  */
#line 442 "../../src-common/cfdg.ypp"
    {
            driver.mInPathContainer = false;
            rule_ptr rule(new ASTrule(-1, (yylocation_stack_[(1) - (1)])));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
		}
    break;

  case 60:

/* Line 677 of lalr1.cc  */
#line 450 "../../src-common/cfdg.ypp"
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

  case 61:

/* Line 677 of lalr1.cc  */
#line 463 "../../src-common/cfdg.ypp"
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

  case 62:

/* Line 677 of lalr1.cc  */
#line 484 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 63:

/* Line 677 of lalr1.cc  */
#line 492 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
            driver.SetShape(NULL);
        }
    break;

  case 64:

/* Line 677 of lalr1.cc  */
#line 501 "../../src-common/cfdg.ypp"
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

  case 65:

/* Line 677 of lalr1.cc  */
#line 514 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 66:

/* Line 677 of lalr1.cc  */
#line 521 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(2) - (1)].string));
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(*type, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
		}
    break;

  case 67:

/* Line 677 of lalr1.cc  */
#line 527 "../../src-common/cfdg.ypp"
    {
            static std::string shapeStr("shape");
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(shapeStr, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 72:

/* Line 677 of lalr1.cc  */
#line 545 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(3) - (2)].expression);}
    break;

  case 73:

/* Line 677 of lalr1.cc  */
#line 546 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTexpression((yyloc)); }
    break;

  case 74:

/* Line 677 of lalr1.cc  */
#line 547 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 75:

/* Line 677 of lalr1.cc  */
#line 548 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 76:

/* Line 677 of lalr1.cc  */
#line 552 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 78:

/* Line 677 of lalr1.cc  */
#line 559 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 80:

/* Line 677 of lalr1.cc  */
#line 566 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string));
            exp_ptr mod((yysemantic_stack_[(4) - (3)].expression));
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = new ASTpathOp(*pop, mod, false, (yyloc));
        }
    break;

  case 81:

/* Line 677 of lalr1.cc  */
#line 573 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(2) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            driver.lexer->maybeVersion = token::CFDG2;
            rep_ptr item(new ASTpathCommand(*cmd, mod, (yyloc)));
            (yyval.component) = item.release();
        }
    break;

  case 82:

/* Line 677 of lalr1.cc  */
#line 583 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string));
            exp_ptr mod((yysemantic_stack_[(4) - (3)].expression));
            (yyval.component) = new ASTpathOp(*pop, mod, true, (yyloc));
        }
    break;

  case 83:

/* Line 677 of lalr1.cc  */
#line 589 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(3) - (1)].string));
            exp_ptr mod;
            (yyval.component) = new ASTpathOp(*pop, mod, true, (yyloc));
        }
    break;

  case 84:

/* Line 677 of lalr1.cc  */
#line 595 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(3) - (1)].string));
            exp_ptr p((yysemantic_stack_[(3) - (2)].expression));
            mod_ptr mod((yysemantic_stack_[(3) - (3)].mod));
            rep_ptr item = driver.MakeElement(*cmd, mod, p, (yyloc), false);
            (yyval.component) = item.release();
        }
    break;

  case 85:

/* Line 677 of lalr1.cc  */
#line 603 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(4) - (2)].string));
            exp_ptr p((yysemantic_stack_[(4) - (3)].expression));
            mod_ptr mod((yysemantic_stack_[(4) - (4)].mod));
            rep_ptr item = driver.MakeElement(*cmd, mod, p, (yyloc), true);
            (yyval.component) = item.release();
        }
    break;

  case 86:

/* Line 677 of lalr1.cc  */
#line 613 "../../src-common/cfdg.ypp"
    { }
    break;

  case 87:

/* Line 677 of lalr1.cc  */
#line 615 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 88:

/* Line 677 of lalr1.cc  */
#line 621 "../../src-common/cfdg.ypp"
    { }
    break;

  case 89:

/* Line 677 of lalr1.cc  */
#line 623 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 90:

/* Line 677 of lalr1.cc  */
#line 629 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer(driver.switchStack.top());
        }
    break;

  case 93:

/* Line 677 of lalr1.cc  */
#line 640 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 94:

/* Line 677 of lalr1.cc  */
#line 642 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 95:

/* Line 677 of lalr1.cc  */
#line 644 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(1) - (1)].loopObj); 
            driver.pop_repContainer((yysemantic_stack_[(1) - (1)].loopObj));
            if ((yysemantic_stack_[(1) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(1) - (1)].loopObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 96:

/* Line 677 of lalr1.cc  */
#line 653 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            driver.push_repContainer((yysemantic_stack_[(2) - (1)].loopObj)->mFinallyBody);
        }
    break;

  case 97:

/* Line 677 of lalr1.cc  */
#line 656 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].loopObj));
            (yyval.component) = (yysemantic_stack_[(4) - (1)].loopObj);
            if ((yysemantic_stack_[(4) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(4) - (1)].loopObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 98:

/* Line 677 of lalr1.cc  */
#line 665 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].ifObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].ifObj));
            if ((yysemantic_stack_[(2) - (1)].ifObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].ifObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 99:

/* Line 677 of lalr1.cc  */
#line 674 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].ifObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].ifObj));
            if ((yysemantic_stack_[(2) - (1)].ifObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].ifObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 100:

/* Line 677 of lalr1.cc  */
#line 683 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].component);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].component));
            if ((yysemantic_stack_[(2) - (1)].component)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].component);
                (yyval.component) = 0;
            }
        }
    break;

  case 101:

/* Line 677 of lalr1.cc  */
#line 693 "../../src-common/cfdg.ypp"
    {
            (yysemantic_stack_[(4) - (1)].switchObj)->unify();
            (yyval.component) = (yysemantic_stack_[(4) - (1)].switchObj);
            driver.switchStack.pop();
        }
    break;

  case 102:

/* Line 677 of lalr1.cc  */
#line 699 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 103:

/* Line 677 of lalr1.cc  */
#line 706 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 104:

/* Line 677 of lalr1.cc  */
#line 707 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 105:

/* Line 677 of lalr1.cc  */
#line 708 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 106:

/* Line 677 of lalr1.cc  */
#line 712 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 107:

/* Line 677 of lalr1.cc  */
#line 714 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(2) - (1)].loopObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            if ((yysemantic_stack_[(2) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].loopObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 108:

/* Line 677 of lalr1.cc  */
#line 722 "../../src-common/cfdg.ypp"
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

  case 109:

/* Line 677 of lalr1.cc  */
#line 734 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 110:

/* Line 677 of lalr1.cc  */
#line 735 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 113:

/* Line 677 of lalr1.cc  */
#line 738 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 117:

/* Line 677 of lalr1.cc  */
#line 745 "../../src-common/cfdg.ypp"
    {
            (yyval.loopObj) = (yysemantic_stack_[(2) - (1)].loopObj);
        }
    break;

  case 118:

/* Line 677 of lalr1.cc  */
#line 751 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 120:

/* Line 677 of lalr1.cc  */
#line 758 "../../src-common/cfdg.ypp"
    { }
    break;

  case 121:

/* Line 677 of lalr1.cc  */
#line 760 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 122:

/* Line 677 of lalr1.cc  */
#line 766 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (1)].string));
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), (yylocation_stack_[(2) - (1)])));
            (yyval.component) = new ASTreplacement(*r, r->entropyVal, mod, (yyloc));
        }
    break;

  case 123:

/* Line 677 of lalr1.cc  */
#line 775 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 124:

/* Line 677 of lalr1.cc  */
#line 777 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].loopObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            if ((yysemantic_stack_[(2) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].loopObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 125:

/* Line 677 of lalr1.cc  */
#line 788 "../../src-common/cfdg.ypp"
    { ++driver.mLocalStackDepth; }
    break;

  case 126:

/* Line 677 of lalr1.cc  */
#line 788 "../../src-common/cfdg.ypp"
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

  case 127:

/* Line 677 of lalr1.cc  */
#line 803 "../../src-common/cfdg.ypp"
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

  case 128:

/* Line 677 of lalr1.cc  */
#line 814 "../../src-common/cfdg.ypp"
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

  case 129:

/* Line 677 of lalr1.cc  */
#line 827 "../../src-common/cfdg.ypp"
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

  case 130:

/* Line 677 of lalr1.cc  */
#line 839 "../../src-common/cfdg.ypp"
    {
            exp_ptr cond((yysemantic_stack_[(4) - (3)].expression));
            if_ptr ifHeader(new ASTif(cond, (yylocation_stack_[(4) - (3)])));
            driver.push_repContainer(ifHeader->mThenBody);
            (yyval.ifObj) = ifHeader.release();
        }
    break;

  case 131:

/* Line 677 of lalr1.cc  */
#line 848 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ifObj));
            driver.push_repContainer((yysemantic_stack_[(3) - (1)].ifObj)->mElseBody);
            (yyval.ifObj) = (yysemantic_stack_[(3) - (1)].ifObj);
        }
    break;

  case 132:

/* Line 677 of lalr1.cc  */
#line 856 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (1)].modToken) != ASTmodTerm::transform)
                error((yylocation_stack_[(2) - (1)]), "Syntax error");
            mod_ptr mod((yysemantic_stack_[(2) - (2)].mod));
            ASTtransform* trans = new ASTtransform(mod, (yyloc));
            driver.push_repContainer(trans->mBody);
            (yyval.component) = trans;
        }
    break;

  case 133:

/* Line 677 of lalr1.cc  */
#line 867 "../../src-common/cfdg.ypp"
    {
            exp_ptr caseVal((yysemantic_stack_[(4) - (3)].expression));
            switch_ptr switchHeader(new ASTswitch(caseVal, (yylocation_stack_[(4) - (3)])));
            driver.switchStack.push(switchHeader.get());
            (yyval.switchObj) = switchHeader.release();
        }
    break;

  case 134:

/* Line 677 of lalr1.cc  */
#line 876 "../../src-common/cfdg.ypp"
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

  case 135:

/* Line 677 of lalr1.cc  */
#line 902 "../../src-common/cfdg.ypp"
    {
            if (!driver.switchStack.top()->mElseBody.mBody.empty()) {
                driver.error((yyloc), "There can only be one 'else:' clause");
            } else {
                driver.push_repContainer(driver.switchStack.top()->mElseBody);
            }
            (yyval.modToken) = 0;
        }
    break;

  case 136:

/* Line 677 of lalr1.cc  */
#line 913 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod(ASToperator::MakeCanonical(driver.mCanonicalMods));
            (yyval.mod) = driver.MakeModification(mod, (yyloc));
        }
    break;

  case 137:

/* Line 677 of lalr1.cc  */
#line 918 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(3) - (2)].expression));
            (yyval.mod) = driver.MakeModification(mod, (yyloc));
        }
    break;

  case 138:

/* Line 677 of lalr1.cc  */
#line 925 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod(ASToperator::MakeCanonical(driver.mCanonicalMods));
            (yyval.mod) = driver.MakeModification(mod, (yyloc));
        }
    break;

  case 139:

/* Line 677 of lalr1.cc  */
#line 930 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(5) - (3)].expression));
            (yyval.mod) = driver.MakeModification(mod, (yyloc));
        }
    break;

  case 140:

/* Line 677 of lalr1.cc  */
#line 937 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTcons::Cons((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 141:

/* Line 677 of lalr1.cc  */
#line 940 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 142:

/* Line 677 of lalr1.cc  */
#line 944 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTcons::Cons((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 143:

/* Line 677 of lalr1.cc  */
#line 947 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 144:

/* Line 677 of lalr1.cc  */
#line 951 "../../src-common/cfdg.ypp"
    {
            ((yysemantic_stack_[(2) - (2)].expression))->flatten(driver.mCanonicalMods);
        }
    break;

  case 145:

/* Line 677 of lalr1.cc  */
#line 954 "../../src-common/cfdg.ypp"
    { driver.mCanonicalMods.clear(); }
    break;

  case 146:

/* Line 677 of lalr1.cc  */
#line 958 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].expression));
            (yyval.expression) = driver.MakeModTerm((yysemantic_stack_[(2) - (1)].modToken), mod, (yyloc));
        }
    break;

  case 147:

/* Line 677 of lalr1.cc  */
#line 963 "../../src-common/cfdg.ypp"
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

  case 148:

/* Line 677 of lalr1.cc  */
#line 973 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.expression) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 149:

/* Line 677 of lalr1.cc  */
#line 978 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.expression) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 150:

/* Line 677 of lalr1.cc  */
#line 985 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTcons::Cons((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 151:

/* Line 677 of lalr1.cc  */
#line 989 "../../src-common/cfdg.ypp"
    { 
            (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); 
        }
    break;

  case 152:

/* Line 677 of lalr1.cc  */
#line 995 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 153:

/* Line 677 of lalr1.cc  */
#line 997 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 154:

/* Line 677 of lalr1.cc  */
#line 999 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 155:

/* Line 677 of lalr1.cc  */
#line 1001 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 156:

/* Line 677 of lalr1.cc  */
#line 1003 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 157:

/* Line 677 of lalr1.cc  */
#line 1005 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 158:

/* Line 677 of lalr1.cc  */
#line 1010 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 159:

/* Line 677 of lalr1.cc  */
#line 1017 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 160:

/* Line 677 of lalr1.cc  */
#line 1019 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 161:

/* Line 677 of lalr1.cc  */
#line 1021 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 162:

/* Line 677 of lalr1.cc  */
#line 1026 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 163:

/* Line 677 of lalr1.cc  */
#line 1031 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression));   }
    break;

  case 164:

/* Line 677 of lalr1.cc  */
#line 1033 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('+', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 165:

/* Line 677 of lalr1.cc  */
#line 1035 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('-', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 166:

/* Line 677 of lalr1.cc  */
#line 1037 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('_', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 167:

/* Line 677 of lalr1.cc  */
#line 1039 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('*', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 168:

/* Line 677 of lalr1.cc  */
#line 1041 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('/', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 169:

/* Line 677 of lalr1.cc  */
#line 1043 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 170:

/* Line 677 of lalr1.cc  */
#line 1045 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 171:

/* Line 677 of lalr1.cc  */
#line 1047 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('!', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 172:

/* Line 677 of lalr1.cc  */
#line 1049 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('^', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 173:

/* Line 677 of lalr1.cc  */
#line 1051 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('<', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 174:

/* Line 677 of lalr1.cc  */
#line 1053 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('L', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 175:

/* Line 677 of lalr1.cc  */
#line 1055 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('>', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 176:

/* Line 677 of lalr1.cc  */
#line 1057 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('G', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 177:

/* Line 677 of lalr1.cc  */
#line 1059 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('=', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 178:

/* Line 677 of lalr1.cc  */
#line 1061 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('n', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 179:

/* Line 677 of lalr1.cc  */
#line 1063 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('&', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 180:

/* Line 677 of lalr1.cc  */
#line 1065 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('|', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 181:

/* Line 677 of lalr1.cc  */
#line 1067 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('X', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 182:

/* Line 677 of lalr1.cc  */
#line 1069 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 183:

/* Line 677 of lalr1.cc  */
#line 1071 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].mod); }
    break;

  case 184:

/* Line 677 of lalr1.cc  */
#line 1075 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), true);
        }
    break;

  case 185:

/* Line 677 of lalr1.cc  */
#line 1080 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), true);
        }
    break;

  case 186:

/* Line 677 of lalr1.cc  */
#line 1086 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 187:

/* Line 677 of lalr1.cc  */
#line 1093 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 188:

/* Line 677 of lalr1.cc  */
#line 1098 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 189:

/* Line 677 of lalr1.cc  */
#line 1104 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args(new ASTexpression((yylocation_stack_[(4) - (1)]) + (yylocation_stack_[(4) - (4)])));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 190:

/* Line 677 of lalr1.cc  */
#line 1110 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;



/* Line 677 of lalr1.cc  */
#line 2459 "cfdg.tab.cpp"
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
  const short int CfdgParser::yypact_ninf_ = -173;
  const short int
  CfdgParser::yypact_[] =
  {
       198,  -173,  -173,    42,   652,   671,  -173,    51,  -173,    64,
      83,   -41,   -41,  -173,   110,    72,  -173,   -41,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,   101,  -173,   107,  -173,
     102,   144,   103,   157,   -41,   -41,   173,    72,   131,   -41,
    -173,  -173,  -173,  -173,  -173,  -173,   135,  -173,  -173,  -173,
     137,   139,  -173,  -173,   160,   182,   145,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,   171,   179,
    -173,   179,  -173,  -173,  -173,  -173,   189,    72,  -173,  -173,
      14,  -173,  -173,  -173,  -173,  -173,  -173,    69,   159,    55,
      24,   164,   167,    39,  -173,  -173,   607,  -173,  -173,   203,
     610,   185,   186,   167,    16,   187,   -21,  -173,  -173,  -173,
    -173,  -173,   229,    61,    61,    61,    61,   188,    38,    95,
     174,    73,  -173,  -173,  -173,  -173,   -41,   197,  -173,  -173,
    -173,    10,  -173,  -173,  -173,  -173,  -173,    11,    57,  -173,
    -173,  -173,  -173,   132,   207,   219,  -173,   607,   607,   607,
     607,   220,  -173,  -173,   241,  -173,  -173,   258,   277,  -173,
      50,   501,   171,    20,   167,   501,   607,   607,  -173,   607,
    -173,   167,  -173,   472,  -173,  -173,   171,   250,  -173,  -173,
    -173,   289,  -173,  -173,  -173,  -173,  -173,   257,  -173,   174,
     174,   607,   174,   100,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,   -41,   269,  -173,
    -173,  -173,  -173,   183,   274,   274,   274,   270,  -173,    99,
     607,   607,   607,   607,   607,   607,   607,   607,   607,   607,
     607,   607,   607,   607,   607,   607,   607,   607,  -173,  -173,
    -173,    39,  -173,   167,   607,  -173,   299,   328,   501,  -173,
    -173,   357,    61,   146,  -173,    40,   475,  -173,  -173,   386,
     209,   174,   174,  -173,   -41,    67,   168,   158,   271,  -173,
     415,  -173,   134,  -173,   249,   249,   221,   221,   221,   221,
     592,   592,   573,   552,   530,   501,   275,   275,   275,   274,
     274,   274,  -173,  -173,   167,  -173,  -173,  -173,  -173,  -173,
     272,   607,  -173,  -173,    61,  -173,   444,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,   279,  -173,  -173,
     212,  -173,  -173,  -173,  -173
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  CfdgParser::yydefact_[] =
  {
         0,     5,     7,     0,     2,     3,     1,     0,    28,     0,
       0,     0,     0,    39,     0,     0,    27,     0,     4,    25,
      19,    20,    17,    18,    21,    22,     0,    23,     0,    24,
       0,     0,    59,     0,     0,     0,     0,     0,    43,     0,
       6,    16,     9,    10,     8,    15,    13,    77,    14,    36,
       0,     0,    11,    12,    46,    56,    64,   143,   145,    49,
      47,    26,    40,    41,    37,    48,   119,    79,    75,    71,
      60,    71,    34,    32,    50,    35,     0,     0,    33,    54,
       0,    77,    77,    30,    31,    57,    29,     0,     0,     0,
       0,     0,    45,     0,    53,    61,     0,    42,    38,     0,
       0,     0,     0,     0,    75,     0,     0,    55,    94,    93,
      76,   102,    95,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   137,   142,   136,   144,     0,     0,    58,   123,
     118,     0,   111,   112,   114,   116,   115,     0,     0,    65,
     106,    78,   108,     0,     0,   190,   159,     0,     0,     0,
       0,   145,    74,   183,     0,   160,    44,     0,     0,    69,
       0,    51,    75,   190,     0,   129,     0,     0,   132,     0,
     104,     0,   103,     0,   105,    96,    75,     0,    77,    87,
     117,    98,    99,   100,    91,    62,    63,   186,   152,     0,
       0,     0,   146,   151,   154,   148,   149,   122,   125,   119,
     124,   121,   113,   110,    81,   109,   141,     0,     0,    79,
      89,   107,    73,     0,   171,   169,   170,     0,   143,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    72,    67,
      66,     0,    70,     0,     0,   128,     0,     0,    52,    84,
      83,     0,     0,     0,   131,     0,     0,   155,   156,     0,
     150,     0,     0,   147,     0,     0,     0,     0,     0,   187,
       0,   182,     0,   138,   161,   162,   174,   173,   176,   175,
     177,   178,   179,   180,   181,   163,   165,   164,   166,   167,
     168,   172,    68,    85,     0,   130,   133,    82,    97,    86,
       0,     0,   101,    90,     0,   184,     0,   153,   157,   158,
     126,   120,    80,   140,    88,   189,   188,     0,   127,   135,
       0,    92,   185,   139,   134
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yypgoto_[] =
  {
      -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
     326,    15,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,   348,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,    92,  -173,   283,   -58,   -73,   147,   214,   -75,
    -103,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
     156,  -173,   228,  -173,   -87,  -173,  -173,   116,  -173,  -173,
    -173,  -173,  -173,   -11,   -88,  -173,   143,   211,   -69,  -173,
    -172,   -89,  -173,  -173
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yydefgoto_[] =
  {
        -1,     3,     4,     5,    40,    18,    19,    41,    20,    42,
      21,    64,    77,    44,    22,    23,    24,    25,    45,    96,
     108,    46,    47,    48,    26,    27,    50,    51,    52,    53,
      28,    29,   159,   160,    94,   171,    80,    90,   140,   179,
     180,   211,   255,   303,   110,   252,   111,   141,   142,   112,
      89,   200,   129,   130,   131,   264,   113,   164,   114,   115,
     116,   117,   304,   204,   153,   266,    87,    88,   123,   192,
     193,   165,   194,   155
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char CfdgParser::yytable_ninf_ = -1;
  const unsigned short int
  CfdgParser::yytable_[] =
  {
        59,    60,   154,   143,   156,   109,    65,   161,   118,   119,
      92,   181,   182,   183,    57,   168,    58,   257,   258,   125,
     260,   202,    99,    72,    73,   100,   169,   101,    78,   102,
     244,   103,   132,   173,   126,   133,   174,   134,   104,   135,
     105,   136,     6,   109,   109,   157,    99,   106,   137,   100,
     127,   101,    75,   102,   300,   103,   301,   138,   214,   215,
     216,   217,   104,   158,   105,   203,    57,   199,    58,    99,
      91,   106,   107,   170,   213,    54,   245,   246,   247,   126,
     248,   127,   139,   249,   251,   176,   120,   121,    55,   308,
     309,   126,    98,   127,   177,   241,   185,   195,   302,    62,
      63,   196,   259,    99,   243,   253,   100,    56,   101,   242,
     102,   205,   103,   128,   206,   197,   120,   121,   178,   104,
      61,   105,   261,   262,   270,   311,    68,    55,   106,    70,
     122,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   298,
     125,   120,   121,   186,    99,   293,   207,   100,    66,   101,
     273,   102,   263,   103,    67,   208,   132,   306,    69,   133,
     104,   134,   105,   135,   144,   136,   120,   121,   109,   106,
     143,    71,   137,    74,   127,   120,   121,    76,   145,   209,
     146,   138,    79,   268,    81,   317,    82,   313,   187,    86,
     188,   321,     1,     2,   299,   147,   318,   145,    85,   146,
     148,   149,   320,    97,    83,    84,   314,   124,   150,   151,
     189,   190,   151,   152,   147,    91,   312,   162,   191,   148,
     149,   261,   262,    93,   220,   221,   172,   150,   151,   166,
     167,   175,   269,   220,   221,   184,   198,   222,   223,   224,
     225,   226,   227,   310,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   220,   221,   237,   212,   232,   233,   234,
     235,   236,   324,   213,   237,   218,   222,   223,   224,   225,
     226,   227,   239,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   220,   221,   237,   232,   233,   234,   235,   236,
     238,   240,   237,   254,   173,   222,   223,   224,   225,   226,
     227,   256,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   220,   221,   237,   235,   236,   206,   237,   237,   271,
     315,    43,   319,   292,   222,   223,   224,   225,   226,   227,
     323,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     220,   221,   237,    49,    95,   265,   267,   210,   295,   201,
     294,   272,   219,   222,   223,   224,   225,   226,   227,     0,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   220,
     221,   237,     0,     0,     0,     0,     0,   296,     0,     0,
       0,     0,   222,   223,   224,   225,   226,   227,     0,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   220,   221,
     237,     0,     0,     0,     0,     0,   297,     0,     0,     0,
       0,   222,   223,   224,   225,   226,   227,     0,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   220,   221,   237,
       0,     0,     0,     0,     0,   307,     0,     0,     0,     0,
     222,   223,   224,   225,   226,   227,     0,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   220,   221,   237,     0,
       0,     0,     0,     0,   316,     0,     0,     0,     0,   222,
     223,   224,   225,   226,   227,     0,   228,   229,   230,   231,
     232,   233,   234,   235,   236,     0,   145,   237,   146,   145,
       0,   146,     0,   322,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   147,     0,     0,   147,     0,   148,   149,
       0,   148,   149,   220,   221,     0,   150,   151,     0,   150,
     151,   250,     0,     0,   305,     0,   222,   223,   224,   225,
     226,   227,     0,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   220,   221,   237,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   222,   223,   224,   225,   226,
     227,     0,   228,   229,   220,   221,   232,   233,   234,   235,
     236,     0,     0,   237,     0,     0,     0,   222,   223,   224,
     225,   226,   227,     0,   228,   220,   221,     0,   232,   233,
     234,   235,   236,     0,     0,   237,     0,     0,   222,   223,
     224,   225,   226,   227,   220,   221,     0,     0,     0,   232,
     233,   234,   235,   236,     0,     0,   237,   222,   223,   224,
     225,   145,     0,   146,   163,     0,   146,     0,   232,   233,
     234,   235,   236,     0,     0,   237,     0,     0,   147,     0,
       0,   147,     0,   148,   149,     7,   148,   149,     8,     9,
      10,   150,   151,     0,   150,   151,     0,     0,     0,    11,
       0,    12,     0,    13,    30,     0,    14,    31,    32,    33,
       0,    15,    16,    17,     0,     0,     0,     0,    34,     0,
      35,     0,    13,     0,     0,    36,     0,     0,     0,     0,
      37,    38,    39
  };

  /* YYCHECK.  */
  const short int
  CfdgParser::yycheck_[] =
  {
        11,    12,    91,    90,    92,    80,    17,    96,    81,    82,
      68,   114,   115,   116,    55,   103,    57,   189,   190,    88,
     192,    10,     8,    34,    35,    11,    10,    13,    39,    15,
      10,    17,     8,    54,    24,    11,    57,    13,    24,    15,
      26,    17,     0,   118,   119,     6,     8,    33,    24,    11,
      26,    13,    37,    15,    14,    17,    16,    33,   147,   148,
     149,   150,    24,    24,    26,    54,    55,    57,    57,     8,
      54,    33,    58,    57,    54,    24,   164,   166,   167,    24,
     169,    26,    58,   171,   173,    24,    17,    18,    24,   261,
     262,    24,    77,    26,    33,    45,    58,    24,    58,    27,
      28,    28,   191,     8,   162,   178,    11,    24,    13,    59,
      15,    54,    17,    58,    57,   126,    17,    18,    57,    24,
      10,    26,    22,    23,   213,    58,    24,    24,    33,    26,
      61,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   252,
     219,    17,    18,    58,     8,   243,    24,    11,    57,    13,
      61,    15,    62,    17,    57,    33,     8,   256,    24,    11,
      24,    13,    26,    15,    10,    17,    17,    18,   253,    33,
     267,    24,    24,    10,    26,    17,    18,    56,    24,    57,
      26,    33,    57,    10,    57,    61,    57,   266,    24,    54,
      26,   304,     4,     5,    58,    41,   294,    24,    26,    26,
      46,    47,   301,    24,    54,    55,    58,    58,    54,    55,
      46,    47,    55,    59,    41,    54,    58,    24,    54,    46,
      47,    22,    23,    54,    22,    23,    49,    54,    55,    54,
      54,    12,    59,    22,    23,    57,    49,    35,    36,    37,
      38,    39,    40,   264,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    22,    23,    53,    59,    46,    47,    48,
      49,    50,    60,    54,    53,    55,    35,    36,    37,    38,
      39,    40,    24,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    22,    23,    53,    46,    47,    48,    49,    50,
      59,    24,    53,    14,    54,    35,    36,    37,    38,    39,
      40,    54,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    22,    23,    53,    49,    50,    57,    53,    53,    59,
      59,     5,    60,   241,    35,    36,    37,    38,    39,    40,
      61,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      22,    23,    53,     5,    71,   199,   209,   143,    59,   131,
     244,   218,   151,    35,    36,    37,    38,    39,    40,    -1,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    22,
      23,    53,    -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    39,    40,    -1,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    22,    23,
      53,    -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    22,    23,    53,
      -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,
      35,    36,    37,    38,    39,    40,    -1,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    22,    23,    53,    -1,
      -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    40,    -1,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    -1,    24,    53,    26,    24,
      -1,    26,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    -1,    -1,    41,    -1,    46,    47,
      -1,    46,    47,    22,    23,    -1,    54,    55,    -1,    54,
      55,    59,    -1,    -1,    59,    -1,    35,    36,    37,    38,
      39,    40,    -1,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    22,    23,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,    42,    43,    22,    23,    46,    47,    48,    49,
      50,    -1,    -1,    53,    -1,    -1,    -1,    35,    36,    37,
      38,    39,    40,    -1,    42,    22,    23,    -1,    46,    47,
      48,    49,    50,    -1,    -1,    53,    -1,    -1,    35,    36,
      37,    38,    39,    40,    22,    23,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    -1,    -1,    53,    35,    36,    37,
      38,    24,    -1,    26,    24,    -1,    26,    -1,    46,    47,
      48,    49,    50,    -1,    -1,    53,    -1,    -1,    41,    -1,
      -1,    41,    -1,    46,    47,     3,    46,    47,     6,     7,
       8,    54,    55,    -1,    54,    55,    -1,    -1,    -1,    17,
      -1,    19,    -1,    21,     3,    -1,    24,     6,     7,     8,
      -1,    29,    30,    31,    -1,    -1,    -1,    -1,    17,    -1,
      19,    -1,    21,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      29,    30,    31
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  CfdgParser::yystos_[] =
  {
         0,     4,     5,    64,    65,    66,     0,     3,     6,     7,
       8,    17,    19,    21,    24,    29,    30,    31,    68,    69,
      71,    73,    77,    78,    79,    80,    87,    88,    93,    94,
       3,     6,     7,     8,    17,    19,    24,    29,    30,    31,
      67,    70,    72,    73,    76,    81,    84,    85,    86,    87,
      89,    90,    91,    92,    24,    24,    24,    55,    57,   126,
     126,    10,    27,    28,    74,   126,    57,    57,    24,    24,
      26,    24,   126,   126,    10,    74,    56,    75,   126,    57,
      99,    57,    57,    54,    55,    26,    54,   129,   130,   113,
     100,    54,    98,    54,    97,    97,    82,    24,    74,     8,
      11,    13,    15,    17,    24,    26,    33,    58,    83,   102,
     107,   109,   112,   119,   121,   122,   123,   124,    99,    99,
      17,    18,    61,   131,    58,   131,    24,    26,    58,   115,
     116,   117,     8,    11,    13,    15,    17,    24,    33,    58,
     101,   110,   111,   117,    10,    24,    26,    41,    46,    47,
      54,    55,    59,   127,   134,   136,   127,     6,    24,    95,
      96,   134,    24,    24,   120,   134,    54,    54,   127,    10,
      57,    98,    49,    54,    57,    12,    24,    33,    57,   102,
     103,   103,   103,   103,    57,    58,    58,    24,    26,    46,
      47,    54,   132,   133,   135,    24,    28,   126,    49,    57,
     114,   115,    10,    54,   126,    54,    57,    24,    33,    57,
     101,   104,    59,    54,   134,   134,   134,   134,    55,   130,
      22,    23,    35,    36,    37,    38,    39,    40,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    53,    59,    24,
      24,    45,    59,    98,    10,   127,   134,   134,   134,   127,
      59,   134,   108,    99,    14,   105,    54,   133,   133,   134,
     133,    22,    23,    62,   118,   113,   128,   100,    10,    59,
     134,    59,   129,    61,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,    95,   127,   120,    59,    59,    59,   103,    58,
      14,    16,    58,   106,   125,    59,   134,    59,   133,   133,
     126,    58,    58,   131,    58,    59,    59,    61,   127,    60,
     134,   103,    59,    61,    60
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
      69,    69,    70,    70,    70,    70,    70,    71,    72,    73,
      74,    74,    75,    75,    76,    76,    77,    78,    79,    80,
      82,    81,    83,    84,    85,    86,    87,    87,    88,    89,
      89,    90,    91,    92,    93,    94,    95,    95,    96,    96,
      97,    97,    98,    98,    98,    98,    99,    99,   100,   100,
     101,   101,   102,   102,   102,   102,   103,   103,   104,   104,
     105,   105,   106,   107,   107,   107,   108,   107,   107,   107,
     107,   107,   107,   109,   109,   109,   110,   110,   110,   111,
     111,   111,   111,   111,   111,   111,   111,   112,   113,   113,
     114,   114,   115,   116,   116,   118,   117,   119,   119,   120,
     121,   122,   123,   124,   125,   125,   126,   126,   127,   127,
     128,   128,   129,   129,   130,   130,   131,   131,   131,   131,
     132,   132,   133,   133,   133,   133,   133,   133,   133,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   135,   135,   135,   136,   136,   136,
     136
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  CfdgParser::yyr2_[] =
  {
         0,     2,     2,     2,     2,     0,     2,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     3,
       3,     3,     2,     2,     2,     2,     1,     2,     3,     1,
       1,     1,     2,     0,     4,     3,     2,     2,     2,     2,
       0,     4,     3,     3,     2,     3,     2,     3,     4,     1,
       2,     3,     4,     4,     2,     4,     2,     2,     3,     1,
       3,     0,     3,     3,     2,     0,     2,     0,     2,     0,
       4,     2,     4,     3,     3,     4,     3,     1,     3,     1,
       2,     0,     2,     1,     1,     1,     0,     4,     2,     2,
       2,     4,     1,     2,     2,     2,     1,     2,     1,     2,
       2,     1,     1,     2,     1,     1,     1,     2,     2,     0,
       3,     1,     2,     1,     2,     0,     4,     5,     3,     1,
       4,     3,     2,     4,     3,     2,     3,     3,     3,     5,
       2,     0,     2,     0,     2,     0,     2,     3,     2,     2,
       2,     1,     1,     3,     1,     2,     2,     3,     3,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     4,     1,     3,     4,     4,
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
  "NEQ", "NOT", "AND", "OR", "XOR", "','", "'-'", "'+'", "'_'", "'*'",
  "'/'", "POS", "NEG", "'^'", "'('", "'['", "'@'", "'{'", "'}'", "')'",
  "':'", "']'", "'|'", "$accept", "choose", "cfdg2", "cfdg3", "statement",
  "statement_v2", "v3clues", "v2stuff", "inclusion", "import", "eof",
  "fileString", "fileNameSpace", "initialization", "initialization_v2",
  "background", "tile", "size", "global_definition", "$@1", "definition",
  "shape", "shape_singleton_header", "shape_singleton", "rule_header_v2",
  "rule_v2", "rule_header", "path_header", "rule", "path",
  "path_header_v2", "path_v2", "parameter", "buncha_parameters",
  "parameter_list", "parameter_spec", "buncha_elements",
  "buncha_pathOps_v2", "pathOp_simple_v2", "element_simple",
  "one_or_more_elements", "one_or_more_pathOp_v2", "caseBody",
  "caseBody_element", "element", "$@2", "element_v2clue", "pathOp_v2",
  "pathOp_v3clues", "element_loop", "buncha_replacements_v2",
  "one_or_more_replacements_v2", "replacement_simple_v2", "replacement_v2",
  "loopHeader_v2", "$@3", "loopHeader", "loopexp", "ifHeader",
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
      -1,    73,    -1,    91,    -1,    92,    -1,    84,    -1,    86,
      -1,    81,    -1,    70,    -1,    77,    -1,    78,    -1,    71,
      -1,    73,    -1,    79,    -1,    80,    -1,    88,    -1,    94,
      -1,    69,    -1,    24,    10,    -1,    30,    -1,     6,    -1,
       8,    24,    54,    -1,     3,    24,    54,    -1,     3,    24,
      55,    -1,    19,   126,    -1,    31,   126,    -1,    17,   126,
      -1,    29,    74,    -1,    87,    -1,    29,    74,    -1,    30,
      75,    74,    -1,    21,    -1,    27,    -1,    28,    -1,    56,
      24,    -1,    -1,     3,    24,    98,   127,    -1,     3,    24,
      98,    -1,     3,    24,    -1,    19,   126,    -1,    31,   126,
      -1,    17,   126,    -1,    -1,    24,    10,    82,   134,    -1,
      24,    10,   134,    -1,     6,    24,    97,    -1,    84,    57,
      -1,    85,    99,    58,    -1,     7,    24,    -1,     7,    24,
      26,    -1,    87,    57,   113,    58,    -1,     7,    -1,     7,
      26,    -1,     8,    24,    97,    -1,    89,    57,    99,    58,
      -1,    90,    57,    99,    58,    -1,     8,    24,    -1,    93,
      57,   100,    58,    -1,    24,    24,    -1,     6,    24,    -1,
      96,    45,    95,    -1,    95,    -1,    54,    96,    59,    -1,
      -1,    54,   134,    59,    -1,    54,    10,    59,    -1,    54,
      59,    -1,    -1,    99,   107,    -1,    -1,   100,   110,    -1,
      -1,    33,    57,   128,    58,    -1,    24,   126,    -1,    33,
      54,   134,    59,    -1,    33,    54,    59,    -1,    24,    98,
     127,    -1,     8,    24,    98,   127,    -1,    57,    99,    58,
      -1,   102,    -1,    57,   100,    58,    -1,   101,    -1,   105,
     106,    -1,    -1,   125,   103,    -1,   102,    -1,    83,    -1,
     112,    -1,    -1,   112,    12,   108,   103,    -1,   121,   103,
      -1,   122,   103,    -1,   123,   103,    -1,   124,    57,   105,
      58,    -1,   109,    -1,    26,    49,    -1,    24,    57,    -1,
      33,    57,    -1,   101,    -1,   117,   104,    -1,   111,    -1,
      33,    54,    -1,    24,    54,    -1,     8,    -1,    11,    -1,
      24,    10,    -1,    13,    -1,    17,    -1,    15,    -1,   119,
     103,    -1,   113,   116,    -1,    -1,    57,   113,    58,    -1,
     115,    -1,    24,   126,    -1,   115,    -1,   117,   114,    -1,
      -1,    26,    49,   118,   126,    -1,    11,    24,    10,   120,
     127,    -1,    11,   120,   127,    -1,   134,    -1,    13,    54,
     134,    59,    -1,   121,   103,    14,    -1,    17,   127,    -1,
      15,    54,   134,    59,    -1,    16,   134,    60,    -1,    14,
      60,    -1,    57,   130,    58,    -1,    55,   129,    61,    -1,
      55,   130,    61,    -1,    55,    55,   129,    61,    61,    -1,
     128,   131,    -1,    -1,   129,   131,    -1,    -1,   130,   131,
      -1,    -1,    17,   132,    -1,    17,   133,    62,    -1,    18,
      24,    -1,    18,    28,    -1,   132,   133,    -1,   133,    -1,
      26,    -1,    54,   134,    59,    -1,   135,    -1,    46,   133,
      -1,    47,   133,    -1,   133,    22,   133,    -1,   133,    23,
     133,    -1,    26,    -1,   136,    -1,   134,    22,   134,    -1,
     134,    23,   134,    -1,   134,    45,   134,    -1,   134,    47,
     134,    -1,   134,    46,   134,    -1,   134,    48,   134,    -1,
     134,    49,   134,    -1,   134,    50,   134,    -1,    46,   134,
      -1,    47,   134,    -1,    41,   134,    -1,   134,    53,   134,
      -1,   134,    36,   134,    -1,   134,    35,   134,    -1,   134,
      38,   134,    -1,   134,    37,   134,    -1,   134,    39,   134,
      -1,   134,    40,   134,    -1,   134,    42,   134,    -1,   134,
      43,   134,    -1,   134,    44,   134,    -1,    54,   134,    59,
      -1,   127,    -1,    24,    54,    59,    -1,    24,    54,   134,
      59,    -1,    24,    -1,    24,    54,    59,    -1,    24,    54,
     134,    59,    -1,    24,    54,    10,    59,    -1,    24,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  CfdgParser::yyprhs_[] =
  {
         0,     0,     3,     6,     9,    12,    13,    16,    17,    19,
      21,    23,    25,    27,    29,    31,    33,    35,    37,    39,
      41,    43,    45,    47,    49,    51,    53,    56,    58,    60,
      64,    68,    72,    75,    78,    81,    84,    86,    89,    93,
      95,    97,    99,   102,   103,   108,   112,   115,   118,   121,
     124,   125,   130,   134,   138,   141,   145,   148,   152,   157,
     159,   162,   166,   171,   176,   179,   184,   187,   190,   194,
     196,   200,   201,   205,   209,   212,   213,   216,   217,   220,
     221,   226,   229,   234,   238,   242,   247,   251,   253,   257,
     259,   262,   263,   266,   268,   270,   272,   273,   278,   281,
     284,   287,   292,   294,   297,   300,   303,   305,   308,   310,
     313,   316,   318,   320,   323,   325,   327,   329,   332,   335,
     336,   340,   342,   345,   347,   350,   351,   356,   362,   366,
     368,   373,   377,   380,   385,   389,   392,   396,   400,   404,
     410,   413,   414,   417,   418,   421,   422,   425,   429,   432,
     435,   438,   440,   442,   446,   448,   451,   454,   458,   462,
     464,   466,   470,   474,   478,   482,   486,   490,   494,   498,
     501,   504,   507,   511,   515,   519,   523,   527,   531,   535,
     539,   543,   547,   551,   553,   557,   562,   564,   568,   573,
     578
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  CfdgParser::yyrline_[] =
  {
         0,   178,   178,   178,   181,   186,   190,   195,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   234,   235,   236,   237,
     238,   239,   243,   244,   245,   246,   247,   251,   260,   271,
     278,   278,   281,   282,   286,   297,   309,   320,   331,   342,
     358,   358,   368,   376,   392,   402,   410,   419,   434,   442,
     450,   463,   484,   492,   501,   514,   521,   527,   535,   536,
     540,   541,   545,   546,   547,   548,   552,   555,   559,   562,
     566,   573,   583,   589,   595,   603,   613,   615,   621,   623,
     629,   632,   636,   640,   642,   644,   653,   653,   665,   674,
     683,   692,   699,   706,   707,   708,   712,   714,   722,   734,
     735,   736,   737,   738,   739,   740,   741,   745,   751,   754,
     758,   760,   766,   775,   777,   788,   788,   803,   814,   827,
     839,   848,   856,   867,   876,   902,   913,   918,   925,   930,
     937,   940,   944,   947,   951,   954,   958,   963,   973,   978,
     985,   989,   995,   997,   999,  1001,  1003,  1005,  1010,  1017,
    1019,  1021,  1026,  1031,  1033,  1035,  1037,  1039,  1041,  1043,
    1045,  1047,  1049,  1051,  1053,  1055,  1057,  1059,  1061,  1063,
    1065,  1067,  1069,  1071,  1075,  1080,  1086,  1093,  1098,  1104,
    1110
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
  const int CfdgParser::yylast_ = 702;
  const int CfdgParser::yynnts_ = 74;
  const int CfdgParser::yyempty_ = -2;
  const int CfdgParser::yyfinal_ = 6;
  const int CfdgParser::yyterror_ = 1;
  const int CfdgParser::yyerrcode_ = 256;
  const int CfdgParser::yyntokens_ = 63;

  const unsigned int CfdgParser::yyuser_token_number_max_ = 301;
  const CfdgParser::token_number_type CfdgParser::yyundef_token_ = 2;


} // yy

/* Line 1053 of lalr1.cc  */
#line 3281 "cfdg.tab.cpp"


/* Line 1055 of lalr1.cc  */
#line 1116 "../../src-common/cfdg.ypp"


void yy::CfdgParser::error(const CfdgParser::location_type& l, const std::string& m)
{
    driver.error(l, m);
}

