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
#line 60 "cfdg.tab.cpp"


#include "cfdg.tab.hpp"

/* User implementation prologue.  */

/* Line 316 of lalr1.cc  */
#line 76 "../../src-common/cfdg.ypp"

#include "astreplacement.h"
#include "astexpression.h"
    
    using namespace AST;

/* Line 316 of lalr1.cc  */
#line 163 "../../src-common/cfdg.ypp"

#include "scanner.h"
#include "math.h"
#include "builder.h"
	
#undef yylex
#define yylex driver.lexer->lex


/* Line 316 of lalr1.cc  */
#line 87 "cfdg.tab.cpp"

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
#line 153 "cfdg.tab.cpp"
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
#line 151 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 260 "cfdg.tab.cpp"
	break;
      case 27: /* "USER_FILENAME" */

/* Line 479 of lalr1.cc  */
#line 151 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 269 "cfdg.tab.cpp"
	break;
      case 28: /* "USER_QSTRING" */

/* Line 479 of lalr1.cc  */
#line 151 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 278 "cfdg.tab.cpp"
	break;
      case 33: /* "USER_PATHOP" */

/* Line 479 of lalr1.cc  */
#line 151 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 287 "cfdg.tab.cpp"
	break;
      case 67: /* "statement" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 296 "cfdg.tab.cpp"
	break;
      case 68: /* "statement_v2" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 305 "cfdg.tab.cpp"
	break;
      case 74: /* "fileString" */

/* Line 479 of lalr1.cc  */
#line 151 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 314 "cfdg.tab.cpp"
	break;
      case 75: /* "fileNameSpace" */

/* Line 479 of lalr1.cc  */
#line 151 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };

/* Line 479 of lalr1.cc  */
#line 323 "cfdg.tab.cpp"
	break;
      case 76: /* "initialization" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 332 "cfdg.tab.cpp"
	break;
      case 77: /* "initialization_v2" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 341 "cfdg.tab.cpp"
	break;
      case 78: /* "background" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 350 "cfdg.tab.cpp"
	break;
      case 80: /* "tile" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 359 "cfdg.tab.cpp"
	break;
      case 81: /* "size" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 368 "cfdg.tab.cpp"
	break;
      case 85: /* "shape" */

/* Line 479 of lalr1.cc  */
#line 161 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->shapeObj); };

/* Line 479 of lalr1.cc  */
#line 377 "cfdg.tab.cpp"
	break;
      case 86: /* "shape_singleton_header" */

/* Line 479 of lalr1.cc  */
#line 156 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 386 "cfdg.tab.cpp"
	break;
      case 87: /* "shape_singleton" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 395 "cfdg.tab.cpp"
	break;
      case 88: /* "rule_header_v2" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 404 "cfdg.tab.cpp"
	break;
      case 90: /* "rule_header" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 413 "cfdg.tab.cpp"
	break;
      case 91: /* "path_header" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 422 "cfdg.tab.cpp"
	break;
      case 92: /* "rule" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 431 "cfdg.tab.cpp"
	break;
      case 93: /* "path" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 440 "cfdg.tab.cpp"
	break;
      case 94: /* "path_header_v2" */

/* Line 479 of lalr1.cc  */
#line 158 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ruleObj); };

/* Line 479 of lalr1.cc  */
#line 449 "cfdg.tab.cpp"
	break;
      case 99: /* "parameter_spec" */

/* Line 479 of lalr1.cc  */
#line 152 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 458 "cfdg.tab.cpp"
	break;
      case 102: /* "pathOp_simple_v2" */

/* Line 479 of lalr1.cc  */
#line 157 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 467 "cfdg.tab.cpp"
	break;
      case 103: /* "element_simple" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 476 "cfdg.tab.cpp"
	break;
      case 108: /* "element" */

/* Line 479 of lalr1.cc  */
#line 155 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 485 "cfdg.tab.cpp"
	break;
      case 111: /* "pathOp_v2" */

/* Line 479 of lalr1.cc  */
#line 157 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 494 "cfdg.tab.cpp"
	break;
      case 113: /* "element_loop" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 503 "cfdg.tab.cpp"
	break;
      case 116: /* "replacement_simple_v2" */

/* Line 479 of lalr1.cc  */
#line 157 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 512 "cfdg.tab.cpp"
	break;
      case 117: /* "replacement_v2" */

/* Line 479 of lalr1.cc  */
#line 157 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 521 "cfdg.tab.cpp"
	break;
      case 118: /* "loopHeader_v2" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 530 "cfdg.tab.cpp"
	break;
      case 120: /* "loopHeader" */

/* Line 479 of lalr1.cc  */
#line 154 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->loopObj); };

/* Line 479 of lalr1.cc  */
#line 539 "cfdg.tab.cpp"
	break;
      case 121: /* "loopexp" */

/* Line 479 of lalr1.cc  */
#line 152 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 548 "cfdg.tab.cpp"
	break;
      case 122: /* "ifHeader" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ifObj); };

/* Line 479 of lalr1.cc  */
#line 557 "cfdg.tab.cpp"
	break;
      case 123: /* "ifElseHeader" */

/* Line 479 of lalr1.cc  */
#line 159 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->ifObj); };

/* Line 479 of lalr1.cc  */
#line 566 "cfdg.tab.cpp"
	break;
      case 124: /* "transHeader" */

/* Line 479 of lalr1.cc  */
#line 156 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); delete (yyvaluep->component); };

/* Line 479 of lalr1.cc  */
#line 575 "cfdg.tab.cpp"
	break;
      case 125: /* "switchHeader" */

/* Line 479 of lalr1.cc  */
#line 160 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->switchObj); };

/* Line 479 of lalr1.cc  */
#line 584 "cfdg.tab.cpp"
	break;
      case 126: /* "caseHeader" */

/* Line 479 of lalr1.cc  */
#line 162 "../../src-common/cfdg.ypp"
	{ driver.pop_repContainer(NULL); };

/* Line 479 of lalr1.cc  */
#line 593 "cfdg.tab.cpp"
	break;
      case 127: /* "modification_v2" */

/* Line 479 of lalr1.cc  */
#line 153 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 602 "cfdg.tab.cpp"
	break;
      case 128: /* "modification" */

/* Line 479 of lalr1.cc  */
#line 153 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 611 "cfdg.tab.cpp"
	break;
      case 129: /* "buncha_pathop_adjustments" */

/* Line 479 of lalr1.cc  */
#line 153 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 620 "cfdg.tab.cpp"
	break;
      case 130: /* "buncha_adjustments" */

/* Line 479 of lalr1.cc  */
#line 153 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 629 "cfdg.tab.cpp"
	break;
      case 132: /* "adjustment" */

/* Line 479 of lalr1.cc  */
#line 153 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 638 "cfdg.tab.cpp"
	break;
      case 133: /* "explist" */

/* Line 479 of lalr1.cc  */
#line 152 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 647 "cfdg.tab.cpp"
	break;
      case 134: /* "exp" */

/* Line 479 of lalr1.cc  */
#line 152 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 656 "cfdg.tab.cpp"
	break;
      case 135: /* "exp2" */

/* Line 479 of lalr1.cc  */
#line 152 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 665 "cfdg.tab.cpp"
	break;
      case 136: /* "expfunc" */

/* Line 479 of lalr1.cc  */
#line 152 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 674 "cfdg.tab.cpp"
	break;
      case 137: /* "exp2func" */

/* Line 479 of lalr1.cc  */
#line 152 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };

/* Line 479 of lalr1.cc  */
#line 683 "cfdg.tab.cpp"
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
#line 178 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 6:

/* Line 677 of lalr1.cc  */
#line 187 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (2)].component)) {
                driver.push_rep((yysemantic_stack_[(2) - (2)].component), true);
            }
        }
    break;

  case 9:

/* Line 677 of lalr1.cc  */
#line 197 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 10:

/* Line 677 of lalr1.cc  */
#line 198 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 13:

/* Line 677 of lalr1.cc  */
#line 201 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].shapeObj); }
    break;

  case 15:

/* Line 677 of lalr1.cc  */
#line 203 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 16:

/* Line 677 of lalr1.cc  */
#line 204 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 19:

/* Line 677 of lalr1.cc  */
#line 213 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 20:

/* Line 677 of lalr1.cc  */
#line 214 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 25:

/* Line 677 of lalr1.cc  */
#line 219 "../../src-common/cfdg.ypp"
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
#line 231 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 29:

/* Line 677 of lalr1.cc  */
#line 234 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 30:

/* Line 677 of lalr1.cc  */
#line 235 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 31:

/* Line 677 of lalr1.cc  */
#line 236 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(3) - (2)].string); }
    break;

  case 32:

/* Line 677 of lalr1.cc  */
#line 240 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].expression); }
    break;

  case 33:

/* Line 677 of lalr1.cc  */
#line 241 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].expression); }
    break;

  case 34:

/* Line 677 of lalr1.cc  */
#line 242 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].expression); }
    break;

  case 35:

/* Line 677 of lalr1.cc  */
#line 243 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 36:

/* Line 677 of lalr1.cc  */
#line 244 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(1) - (1)].ruleObj); }
    break;

  case 37:

/* Line 677 of lalr1.cc  */
#line 248 "../../src-common/cfdg.ypp"
    {
            str_ptr file((yysemantic_stack_[(2) - (2)].string));
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(NULL);
            driver.IncludeFile(*file);
        }
    break;

  case 38:

/* Line 677 of lalr1.cc  */
#line 257 "../../src-common/cfdg.ypp"
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
#line 268 "../../src-common/cfdg.ypp"
    {
            if (driver.EndInclude())
                YYACCEPT;
        }
    break;

  case 42:

/* Line 677 of lalr1.cc  */
#line 278 "../../src-common/cfdg.ypp"
    { (yyval.string) = (yysemantic_stack_[(2) - (2)].string); }
    break;

  case 43:

/* Line 677 of lalr1.cc  */
#line 279 "../../src-common/cfdg.ypp"
    { (yyval.string) = NULL; }
    break;

  case 44:

/* Line 677 of lalr1.cc  */
#line 283 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(4) - (2)].string));
            exp_ptr p((yysemantic_stack_[(4) - (3)].expression));
            exp_ptr mod((yysemantic_stack_[(4) - (4)].expression));
            driver.SetShape(NULL);
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, p, (yylocation_stack_[(4) - (2)])));
            rep_ptr start(new ASTreplacement(*r, *name, mod, (yyloc)));
            driver.Initialize(start);
            (yyval.component) = 0;
        }
    break;

  case 45:

/* Line 677 of lalr1.cc  */
#line 294 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(3) - (2)].string));
            exp_ptr p((yysemantic_stack_[(3) - (3)].expression));
            driver.SetShape(NULL);
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, p, (yylocation_stack_[(3) - (2)])));
            rep_ptr start(new ASTreplacement(*r, *name, exp_ptr(), (yyloc)));
            driver.Initialize(start);
            (yyval.component) = 0;
        }
    break;

  case 46:

/* Line 677 of lalr1.cc  */
#line 306 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (2)].string));
            driver.SetShape(NULL);
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), (yylocation_stack_[(2) - (2)])));
            rep_ptr start(new ASTreplacement(*r, *name, exp_ptr(), (yyloc)));
            driver.Initialize(start);
            (yyval.component) = 0;
        }
    break;

  case 47:

/* Line 677 of lalr1.cc  */
#line 317 "../../src-common/cfdg.ypp"
    {
            driver.SetShape(NULL);
        }
    break;

  case 48:

/* Line 677 of lalr1.cc  */
#line 319 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(3) - (3)].expression));
            static const std::string backVar("CF::Background");
            driver.lexer->maybeVersion = token::CFDG2;
            driver.NextParameter(backVar, mod, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]));
            (yyval.component) = 0;
        }
    break;

  case 49:

/* Line 677 of lalr1.cc  */
#line 329 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].expression));
            static const std::string tileVar("CF::Tile");
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(NULL);
            driver.NextParameter(tileVar, mod, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
            (yyval.component) = 0;
        }
    break;

  case 50:

/* Line 677 of lalr1.cc  */
#line 340 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].expression));
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

  case 51:

/* Line 677 of lalr1.cc  */
#line 356 "../../src-common/cfdg.ypp"
    {
            driver.SetShape(NULL);
        }
    break;

  case 52:

/* Line 677 of lalr1.cc  */
#line 358 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(4) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(4) - (4)].expression));
            driver.NextParameter(*var, exp, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (4)]));
        }
    break;

  case 53:

/* Line 677 of lalr1.cc  */
#line 366 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(3) - (1)].string));
            exp_ptr exp((yysemantic_stack_[(3) - (3)].expression));
            driver.NextParameter(*var, exp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]));
        }
    break;

  case 54:

/* Line 677 of lalr1.cc  */
#line 374 "../../src-common/cfdg.ypp"
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

  case 55:

/* Line 677 of lalr1.cc  */
#line 390 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (1)].shapeObj), true);
            driver.mInPathContainer = false;
            rule_ptr rule(new ASTrule(-1, (yylocation_stack_[(2) - (1)])));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
        }
    break;

  case 56:

/* Line 677 of lalr1.cc  */
#line 400 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(3) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 57:

/* Line 677 of lalr1.cc  */
#line 408 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (2)].string));
            driver.SetShape(NULL);
            rule_ptr rule(new ASTrule(driver.StringToShape(*name, (yylocation_stack_[(2) - (2)]), false), (yyloc)));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
        }
    break;

  case 58:

/* Line 677 of lalr1.cc  */
#line 417 "../../src-common/cfdg.ypp"
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

  case 59:

/* Line 677 of lalr1.cc  */
#line 432 "../../src-common/cfdg.ypp"
    {
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 60:

/* Line 677 of lalr1.cc  */
#line 440 "../../src-common/cfdg.ypp"
    {
            driver.mInPathContainer = false;
            rule_ptr rule(new ASTrule(-1, (yylocation_stack_[(1) - (1)])));
            driver.AddRule(rule.get());
            driver.push_repContainer(rule->mRuleBody);
            (yyval.ruleObj) = rule.release();
		}
    break;

  case 61:

/* Line 677 of lalr1.cc  */
#line 448 "../../src-common/cfdg.ypp"
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

  case 62:

/* Line 677 of lalr1.cc  */
#line 461 "../../src-common/cfdg.ypp"
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

  case 63:

/* Line 677 of lalr1.cc  */
#line 482 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
        }
    break;

  case 64:

/* Line 677 of lalr1.cc  */
#line 490 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
            driver.mInPathContainer = false;
            driver.SetShape(NULL);
        }
    break;

  case 65:

/* Line 677 of lalr1.cc  */
#line 499 "../../src-common/cfdg.ypp"
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

  case 66:

/* Line 677 of lalr1.cc  */
#line 512 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(4) - (1)].ruleObj);
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].ruleObj));
        }
    break;

  case 67:

/* Line 677 of lalr1.cc  */
#line 519 "../../src-common/cfdg.ypp"
    {
            str_ptr type((yysemantic_stack_[(2) - (1)].string));
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(*type, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
		}
    break;

  case 68:

/* Line 677 of lalr1.cc  */
#line 525 "../../src-common/cfdg.ypp"
    {
            static std::string shapeStr("shape");
            str_ptr var((yysemantic_stack_[(2) - (2)].string));
            driver.NextParameterDecl(shapeStr, *var, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]));
        }
    break;

  case 73:

/* Line 677 of lalr1.cc  */
#line 543 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(3) - (2)].expression);}
    break;

  case 74:

/* Line 677 of lalr1.cc  */
#line 544 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTexpression((yyloc)); }
    break;

  case 75:

/* Line 677 of lalr1.cc  */
#line 545 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 76:

/* Line 677 of lalr1.cc  */
#line 546 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 77:

/* Line 677 of lalr1.cc  */
#line 550 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 79:

/* Line 677 of lalr1.cc  */
#line 557 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 81:

/* Line 677 of lalr1.cc  */
#line 564 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string));
            exp_ptr mod((yysemantic_stack_[(4) - (3)].expression));
            driver.lexer->maybeVersion = token::CFDG2;
            (yyval.component) = new ASTpathOp(*pop, mod, false, (yyloc));
        }
    break;

  case 82:

/* Line 677 of lalr1.cc  */
#line 571 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(2) - (1)].string));
            exp_ptr mod((yysemantic_stack_[(2) - (2)].expression));
            driver.lexer->maybeVersion = token::CFDG2;
            rep_ptr item(new ASTpathCommand(*cmd, mod, (yyloc)));
            (yyval.component) = item.release();
        }
    break;

  case 83:

/* Line 677 of lalr1.cc  */
#line 581 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(4) - (1)].string));
            exp_ptr mod((yysemantic_stack_[(4) - (3)].expression));
            (yyval.component) = new ASTpathOp(*pop, mod, true, (yyloc));
        }
    break;

  case 84:

/* Line 677 of lalr1.cc  */
#line 587 "../../src-common/cfdg.ypp"
    {
            str_ptr pop((yysemantic_stack_[(3) - (1)].string));
            exp_ptr mod;
            (yyval.component) = new ASTpathOp(*pop, mod, true, (yyloc));
        }
    break;

  case 85:

/* Line 677 of lalr1.cc  */
#line 593 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(3) - (1)].string));
            exp_ptr p((yysemantic_stack_[(3) - (2)].expression));
            exp_ptr mod((yysemantic_stack_[(3) - (3)].expression));
            rep_ptr item = driver.MakeElement(*cmd, mod, p, (yyloc), false);
            (yyval.component) = item.release();
        }
    break;

  case 86:

/* Line 677 of lalr1.cc  */
#line 601 "../../src-common/cfdg.ypp"
    {
            str_ptr cmd((yysemantic_stack_[(4) - (2)].string));
            exp_ptr p((yysemantic_stack_[(4) - (3)].expression));
            exp_ptr mod((yysemantic_stack_[(4) - (4)].expression));
            rep_ptr item = driver.MakeElement(*cmd, mod, p, (yyloc), true);
            (yyval.component) = item.release();
        }
    break;

  case 87:

/* Line 677 of lalr1.cc  */
#line 611 "../../src-common/cfdg.ypp"
    { }
    break;

  case 88:

/* Line 677 of lalr1.cc  */
#line 613 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 89:

/* Line 677 of lalr1.cc  */
#line 619 "../../src-common/cfdg.ypp"
    { }
    break;

  case 90:

/* Line 677 of lalr1.cc  */
#line 621 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 91:

/* Line 677 of lalr1.cc  */
#line 627 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer(driver.switchStack.top());
        }
    break;

  case 94:

/* Line 677 of lalr1.cc  */
#line 638 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 95:

/* Line 677 of lalr1.cc  */
#line 640 "../../src-common/cfdg.ypp"
    { (yyval.component) = 0; }
    break;

  case 96:

/* Line 677 of lalr1.cc  */
#line 642 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(1) - (1)].loopObj); 
            driver.pop_repContainer((yysemantic_stack_[(1) - (1)].loopObj));
            if ((yysemantic_stack_[(1) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(1) - (1)].loopObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 97:

/* Line 677 of lalr1.cc  */
#line 651 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            driver.push_repContainer((yysemantic_stack_[(2) - (1)].loopObj)->mFinallyBody);
        }
    break;

  case 98:

/* Line 677 of lalr1.cc  */
#line 654 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(4) - (1)].loopObj));
            (yyval.component) = (yysemantic_stack_[(4) - (1)].loopObj);
            if ((yysemantic_stack_[(4) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(4) - (1)].loopObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 99:

/* Line 677 of lalr1.cc  */
#line 663 "../../src-common/cfdg.ypp"
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
#line 672 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].ifObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].ifObj));
            if ((yysemantic_stack_[(2) - (1)].ifObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].ifObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 101:

/* Line 677 of lalr1.cc  */
#line 681 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].component);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].component));
            if ((yysemantic_stack_[(2) - (1)].component)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].component);
                (yyval.component) = 0;
            }
        }
    break;

  case 102:

/* Line 677 of lalr1.cc  */
#line 691 "../../src-common/cfdg.ypp"
    {
            (yysemantic_stack_[(4) - (1)].switchObj)->unify();
            (yyval.component) = (yysemantic_stack_[(4) - (1)].switchObj);
            driver.switchStack.pop();
        }
    break;

  case 103:

/* Line 677 of lalr1.cc  */
#line 697 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(1) - (1)]), "Illegal mixture of old and new elements");
            (yyval.component) = 0;
        }
    break;

  case 104:

/* Line 677 of lalr1.cc  */
#line 704 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 105:

/* Line 677 of lalr1.cc  */
#line 705 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 106:

/* Line 677 of lalr1.cc  */
#line 706 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 107:

/* Line 677 of lalr1.cc  */
#line 710 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 108:

/* Line 677 of lalr1.cc  */
#line 712 "../../src-common/cfdg.ypp"
    { 
            (yyval.component) = (yysemantic_stack_[(2) - (1)].loopObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            if ((yysemantic_stack_[(2) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].loopObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 109:

/* Line 677 of lalr1.cc  */
#line 720 "../../src-common/cfdg.ypp"
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

  case 110:

/* Line 677 of lalr1.cc  */
#line 732 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 111:

/* Line 677 of lalr1.cc  */
#line 733 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 114:

/* Line 677 of lalr1.cc  */
#line 736 "../../src-common/cfdg.ypp"
    { delete (yysemantic_stack_[(2) - (1)].string); }
    break;

  case 118:

/* Line 677 of lalr1.cc  */
#line 743 "../../src-common/cfdg.ypp"
    {
            (yyval.loopObj) = (yysemantic_stack_[(2) - (1)].loopObj);
        }
    break;

  case 119:

/* Line 677 of lalr1.cc  */
#line 749 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(2) - (2)].component));
        }
    break;

  case 121:

/* Line 677 of lalr1.cc  */
#line 756 "../../src-common/cfdg.ypp"
    { }
    break;

  case 122:

/* Line 677 of lalr1.cc  */
#line 758 "../../src-common/cfdg.ypp"
    {
            driver.push_rep((yysemantic_stack_[(1) - (1)].component));
        }
    break;

  case 123:

/* Line 677 of lalr1.cc  */
#line 764 "../../src-common/cfdg.ypp"
    {
            str_ptr name((yysemantic_stack_[(2) - (1)].string));
            exp_ptr mod((yysemantic_stack_[(2) - (2)].expression));
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, exp_ptr(), (yylocation_stack_[(2) - (1)])));
            (yyval.component) = new ASTreplacement(*r, r->entropyVal, mod, (yyloc));
        }
    break;

  case 124:

/* Line 677 of lalr1.cc  */
#line 773 "../../src-common/cfdg.ypp"
    { (yyval.component) = (yysemantic_stack_[(1) - (1)].component); }
    break;

  case 125:

/* Line 677 of lalr1.cc  */
#line 775 "../../src-common/cfdg.ypp"
    {
            (yyval.component) = (yysemantic_stack_[(2) - (1)].loopObj);
            driver.pop_repContainer((yysemantic_stack_[(2) - (1)].loopObj));
            if ((yysemantic_stack_[(2) - (1)].loopObj)->mRepType == 0) {
                delete (yysemantic_stack_[(2) - (1)].loopObj);
                (yyval.component) = 0;
            }
        }
    break;

  case 126:

/* Line 677 of lalr1.cc  */
#line 786 "../../src-common/cfdg.ypp"
    { ++driver.mLocalStackDepth; }
    break;

  case 127:

/* Line 677 of lalr1.cc  */
#line 786 "../../src-common/cfdg.ypp"
    {
            str_ptr cstr((yysemantic_stack_[(4) - (1)].string));
            exp_ptr count(new ASTreal(*cstr, (yylocation_stack_[(4) - (1)])));
            exp_ptr mod((yysemantic_stack_[(4) - (4)].expression));
            static const std::string dummyvar("~~inaccessiblevar~~");
            --driver.mLocalStackDepth;
            driver.lexer->maybeVersion = token::CFDG2;
            loop_ptr loop(new ASTloop(driver.StringToShape(dummyvar, (yylocation_stack_[(4) - (2)]), false), 
                                      dummyvar, (yylocation_stack_[(4) - (2)]), count, (yyloc), mod));
            driver.push_repContainer(loop->mLoopBody);
            (yyval.loopObj) = loop.release();
        }
    break;

  case 128:

/* Line 677 of lalr1.cc  */
#line 801 "../../src-common/cfdg.ypp"
    {
            str_ptr var((yysemantic_stack_[(5) - (2)].string));
            exp_ptr index((yysemantic_stack_[(5) - (4)].expression));
            exp_ptr mod((yysemantic_stack_[(5) - (5)].expression));
            --driver.mLocalStackDepth;
            loop_ptr loop(new ASTloop(driver.StringToShape(*var, (yylocation_stack_[(5) - (2)]), false), 
                                      *var, (yylocation_stack_[(5) - (2)]), index, (yylocation_stack_[(5) - (4)]), mod));
            driver.push_repContainer(loop->mLoopBody);
            (yyval.loopObj) = loop.release();
        }
    break;

  case 129:

/* Line 677 of lalr1.cc  */
#line 812 "../../src-common/cfdg.ypp"
    {
            exp_ptr count((yysemantic_stack_[(3) - (2)].expression));
            exp_ptr mod((yysemantic_stack_[(3) - (3)].expression));
            static const std::string dummyvar("~~inaccessiblevar~~");
            --driver.mLocalStackDepth;
            loop_ptr loop(new ASTloop(driver.StringToShape(dummyvar, (yylocation_stack_[(3) - (1)]), false), 
                                      dummyvar, (yylocation_stack_[(3) - (1)]), count, (yylocation_stack_[(3) - (2)]), mod));
            driver.push_repContainer(loop->mLoopBody);
            (yyval.loopObj) = loop.release();
        }
    break;

  case 130:

/* Line 677 of lalr1.cc  */
#line 825 "../../src-common/cfdg.ypp"
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

  case 131:

/* Line 677 of lalr1.cc  */
#line 837 "../../src-common/cfdg.ypp"
    {
            exp_ptr cond((yysemantic_stack_[(4) - (3)].expression));
            if_ptr ifHeader(new ASTif(cond, (yylocation_stack_[(4) - (3)])));
            driver.push_repContainer(ifHeader->mThenBody);
            (yyval.ifObj) = ifHeader.release();
        }
    break;

  case 132:

/* Line 677 of lalr1.cc  */
#line 846 "../../src-common/cfdg.ypp"
    {
            driver.pop_repContainer((yysemantic_stack_[(3) - (1)].ifObj));
            driver.push_repContainer((yysemantic_stack_[(3) - (1)].ifObj)->mElseBody);
            (yyval.ifObj) = (yysemantic_stack_[(3) - (1)].ifObj);
        }
    break;

  case 133:

/* Line 677 of lalr1.cc  */
#line 854 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (1)].modToken) != ASTmodTerm::transform)
                error((yylocation_stack_[(2) - (1)]), "Syntax error");
            exp_ptr mod((yysemantic_stack_[(2) - (2)].expression));
            ASTtransform* trans = new ASTtransform(mod, (yyloc));
            driver.push_repContainer(trans->mBody);
            (yyval.component) = trans;
        }
    break;

  case 134:

/* Line 677 of lalr1.cc  */
#line 865 "../../src-common/cfdg.ypp"
    {
            exp_ptr caseVal((yysemantic_stack_[(4) - (3)].expression));
            switch_ptr switchHeader(new ASTswitch(caseVal, (yylocation_stack_[(4) - (3)])));
            driver.switchStack.push(switchHeader.get());
            (yyval.switchObj) = switchHeader.release();
        }
    break;

  case 135:

/* Line 677 of lalr1.cc  */
#line 874 "../../src-common/cfdg.ypp"
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

  case 136:

/* Line 677 of lalr1.cc  */
#line 900 "../../src-common/cfdg.ypp"
    {
            if (!driver.switchStack.top()->mElseBody.mBody.empty()) {
                driver.error((yyloc), "There can only be one 'else:' clause");
            } else {
                driver.push_repContainer(driver.switchStack.top()->mElseBody);
            }
            (yyval.modToken) = 0;
        }
    break;

  case 137:

/* Line 677 of lalr1.cc  */
#line 911 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod(ASToperator::MakeCanonical(driver.mCanonicalMods));
            (yyval.expression) = driver.CheckModification(mod, (yyloc));
        }
    break;

  case 138:

/* Line 677 of lalr1.cc  */
#line 916 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(3) - (2)].expression));
            (yyval.expression) = driver.CheckModification(mod, (yyloc));
        }
    break;

  case 139:

/* Line 677 of lalr1.cc  */
#line 923 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod(ASToperator::MakeCanonical(driver.mCanonicalMods));
            (yyval.expression) = driver.CheckModification(mod, (yyloc));
        }
    break;

  case 140:

/* Line 677 of lalr1.cc  */
#line 928 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(5) - (3)].expression));
            (yyval.expression) = driver.CheckModification(mod, (yyloc));
        }
    break;

  case 141:

/* Line 677 of lalr1.cc  */
#line 935 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTcons::Cons((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 142:

/* Line 677 of lalr1.cc  */
#line 938 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 143:

/* Line 677 of lalr1.cc  */
#line 942 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASToperator::Op('+', (yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 144:

/* Line 677 of lalr1.cc  */
#line 945 "../../src-common/cfdg.ypp"
    { (yyval.expression) = 0; }
    break;

  case 145:

/* Line 677 of lalr1.cc  */
#line 949 "../../src-common/cfdg.ypp"
    {
            ((yysemantic_stack_[(2) - (2)].expression))->flatten(driver.mCanonicalMods);
        }
    break;

  case 146:

/* Line 677 of lalr1.cc  */
#line 952 "../../src-common/cfdg.ypp"
    { driver.mCanonicalMods.clear(); }
    break;

  case 147:

/* Line 677 of lalr1.cc  */
#line 956 "../../src-common/cfdg.ypp"
    {
            exp_ptr mod((yysemantic_stack_[(2) - (2)].expression));
            (yyval.expression) = driver.MakeModTerm((yysemantic_stack_[(2) - (1)].modToken), mod, (yyloc));
        }
    break;

  case 148:

/* Line 677 of lalr1.cc  */
#line 961 "../../src-common/cfdg.ypp"
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

  case 149:

/* Line 677 of lalr1.cc  */
#line 971 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.expression) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 150:

/* Line 677 of lalr1.cc  */
#line 976 "../../src-common/cfdg.ypp"
    {
            str_ptr p((yysemantic_stack_[(2) - (2)].string));
            (yyval.expression) = new ASTmodTerm(ASTmodTerm::param, *p, (yyloc));
        }
    break;

  case 151:

/* Line 677 of lalr1.cc  */
#line 983 "../../src-common/cfdg.ypp"
    {
            (yyval.expression) = ASTcons::Cons((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
        }
    break;

  case 152:

/* Line 677 of lalr1.cc  */
#line 987 "../../src-common/cfdg.ypp"
    { 
            (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); 
        }
    break;

  case 153:

/* Line 677 of lalr1.cc  */
#line 993 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 154:

/* Line 677 of lalr1.cc  */
#line 995 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 155:

/* Line 677 of lalr1.cc  */
#line 997 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 156:

/* Line 677 of lalr1.cc  */
#line 999 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 157:

/* Line 677 of lalr1.cc  */
#line 1001 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL);; }
    break;

  case 158:

/* Line 677 of lalr1.cc  */
#line 1003 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 159:

/* Line 677 of lalr1.cc  */
#line 1008 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 160:

/* Line 677 of lalr1.cc  */
#line 1015 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string), (yyloc)); delete (yysemantic_stack_[(1) - (1)].string); }
    break;

  case 161:

/* Line 677 of lalr1.cc  */
#line 1017 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 162:

/* Line 677 of lalr1.cc  */
#line 1019 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 163:

/* Line 677 of lalr1.cc  */
#line 1024 "../../src-common/cfdg.ypp"
    {
            exp_ptr pair(new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)));
            (yyval.expression) = new ASTfunction("rand+/-", pair, driver.mSeed, (yylocation_stack_[(3) - (2)]), (yyloc));
        }
    break;

  case 164:

/* Line 677 of lalr1.cc  */
#line 1029 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression));   }
    break;

  case 165:

/* Line 677 of lalr1.cc  */
#line 1031 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('+', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 166:

/* Line 677 of lalr1.cc  */
#line 1033 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('-', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 167:

/* Line 677 of lalr1.cc  */
#line 1035 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('_', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 168:

/* Line 677 of lalr1.cc  */
#line 1037 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('*', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 169:

/* Line 677 of lalr1.cc  */
#line 1039 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('/', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 170:

/* Line 677 of lalr1.cc  */
#line 1041 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('N', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 171:

/* Line 677 of lalr1.cc  */
#line 1043 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('P', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 172:

/* Line 677 of lalr1.cc  */
#line 1045 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('!', (yysemantic_stack_[(2) - (2)].expression), NULL); }
    break;

  case 173:

/* Line 677 of lalr1.cc  */
#line 1047 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('^', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 174:

/* Line 677 of lalr1.cc  */
#line 1049 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('<', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 175:

/* Line 677 of lalr1.cc  */
#line 1051 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('L', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 176:

/* Line 677 of lalr1.cc  */
#line 1053 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('>', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 177:

/* Line 677 of lalr1.cc  */
#line 1055 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('G', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 178:

/* Line 677 of lalr1.cc  */
#line 1057 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('=', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 179:

/* Line 677 of lalr1.cc  */
#line 1059 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('n', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 180:

/* Line 677 of lalr1.cc  */
#line 1061 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('&', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 181:

/* Line 677 of lalr1.cc  */
#line 1063 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('|', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 182:

/* Line 677 of lalr1.cc  */
#line 1065 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('X', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); }
    break;

  case 183:

/* Line 677 of lalr1.cc  */
#line 1067 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); }
    break;

  case 184:

/* Line 677 of lalr1.cc  */
#line 1069 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); }
    break;

  case 185:

/* Line 677 of lalr1.cc  */
#line 1073 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), true);
        }
    break;

  case 186:

/* Line 677 of lalr1.cc  */
#line 1078 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), true);
        }
    break;

  case 187:

/* Line 677 of lalr1.cc  */
#line 1084 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;

  case 188:

/* Line 677 of lalr1.cc  */
#line 1091 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(3) - (1)].string));
            (yyval.expression) = driver.MakeFunction(func, exp_ptr(), (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)]), false);
        }
    break;

  case 189:

/* Line 677 of lalr1.cc  */
#line 1096 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args((yysemantic_stack_[(4) - (3)].expression));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 190:

/* Line 677 of lalr1.cc  */
#line 1102 "../../src-common/cfdg.ypp"
    { 
            str_ptr func((yysemantic_stack_[(4) - (1)].string));
            exp_ptr args(new ASTexpression((yylocation_stack_[(4) - (1)]) + (yylocation_stack_[(4) - (4)])));
            (yyval.expression) = driver.MakeFunction(func, args, (yylocation_stack_[(4) - (1)]), (yylocation_stack_[(4) - (3)]), false);
        }
    break;

  case 191:

/* Line 677 of lalr1.cc  */
#line 1108 "../../src-common/cfdg.ypp"
    { 
            str_ptr var((yysemantic_stack_[(1) - (1)].string));
            (yyval.expression) = driver.MakeVariable(*var, (yylocation_stack_[(1) - (1)]));
        }
    break;



/* Line 677 of lalr1.cc  */
#line 2466 "cfdg.tab.cpp"
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
  const short int CfdgParser::yypact_ninf_ = -175;
  const short int
  CfdgParser::yypact_[] =
  {
        88,  -175,  -175,    35,   653,   672,  -175,    13,  -175,    47,
      50,   -35,  -175,  -175,    93,   200,  -175,   -35,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,    53,  -175,    57,  -175,
      97,    99,    75,   103,   -35,   -35,   149,   200,   107,   -35,
    -175,  -175,  -175,  -175,  -175,  -175,   108,  -175,  -175,  -175,
     119,   124,  -175,  -175,   179,   176,   159,  -175,  -175,  -175,
     -35,  -175,  -175,  -175,  -175,  -175,  -175,  -175,   161,   164,
    -175,   164,  -175,  -175,  -175,  -175,   175,   200,  -175,  -175,
      21,  -175,  -175,  -175,  -175,  -175,  -175,    25,     9,  -175,
      61,    40,    71,   154,    38,  -175,  -175,   608,  -175,  -175,
     205,   611,   183,   188,   154,    11,   197,    51,  -175,  -175,
    -175,  -175,  -175,   257,     6,     6,     6,     6,   214,    96,
     145,   221,    28,  -175,  -175,  -175,  -175,   -35,   223,  -175,
    -175,  -175,   133,  -175,  -175,  -175,  -175,  -175,    15,   160,
    -175,  -175,  -175,  -175,    58,   211,   220,  -175,   608,   608,
     608,   608,   228,  -175,  -175,   242,  -175,  -175,   252,   272,
    -175,   129,   502,   161,    36,   154,   502,   608,   608,  -175,
     608,  -175,   154,  -175,   473,  -175,  -175,   161,   243,  -175,
    -175,  -175,   284,  -175,  -175,  -175,  -175,  -175,   245,  -175,
     221,   221,   608,   221,   182,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,   -35,   246,
    -175,  -175,  -175,  -175,   184,   247,   247,   247,   271,  -175,
     134,   608,   608,   608,   608,   608,   608,   608,   608,   608,
     608,   608,   608,   608,   608,   608,   608,   608,   608,  -175,
    -175,  -175,    38,  -175,   154,   608,  -175,   300,   329,   502,
    -175,  -175,   358,     6,   153,  -175,    17,   476,  -175,  -175,
     387,   218,   221,   221,  -175,   -35,    70,   166,   174,   253,
    -175,   416,  -175,   155,  -175,   173,   173,   511,   511,   511,
     511,   593,   593,   574,   553,   531,   502,   143,   143,   143,
     247,   247,   247,  -175,  -175,   154,  -175,  -175,  -175,  -175,
    -175,   244,   608,  -175,  -175,     6,  -175,   445,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,   241,  -175,
    -175,   213,  -175,  -175,  -175,  -175
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  CfdgParser::yydefact_[] =
  {
         0,     5,     7,     0,     2,     3,     1,     0,    28,     0,
       0,     0,    47,    39,     0,     0,    27,     0,     4,    25,
      19,    20,    17,    18,    21,    22,     0,    23,     0,    24,
       0,     0,    60,     0,     0,     0,     0,     0,    43,     0,
       6,    16,     9,    10,     8,    15,    13,    78,    14,    36,
       0,     0,    11,    12,    46,    57,    65,   144,   146,    50,
       0,    26,    40,    41,    37,    49,   120,    80,    76,    72,
      61,    72,    34,    32,    51,    35,     0,     0,    33,    55,
       0,    78,    78,    30,    31,    58,    29,     0,     0,    48,
       0,     0,     0,    45,     0,    54,    62,     0,    42,    38,
       0,     0,     0,     0,     0,    76,     0,     0,    56,    95,
      94,    77,   103,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   138,   143,   137,   145,     0,     0,    59,
     124,   119,     0,   112,   113,   115,   117,   116,     0,     0,
      66,   107,    79,   109,     0,     0,   191,   160,     0,     0,
       0,     0,   146,    75,   184,     0,   161,    44,     0,     0,
      70,     0,    52,    76,   191,     0,   130,     0,     0,   133,
       0,   105,     0,   104,     0,   106,    97,    76,     0,    78,
      88,   118,    99,   100,   101,    92,    63,    64,   187,   153,
       0,     0,     0,   147,   152,   155,   149,   150,   123,   126,
     120,   125,   122,   114,   111,    82,   110,   142,     0,     0,
      80,    90,   108,    74,     0,   172,   170,   171,     0,   144,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      68,    67,     0,    71,     0,     0,   129,     0,     0,    53,
      85,    84,     0,     0,     0,   132,     0,     0,   156,   157,
       0,   151,     0,     0,   148,     0,     0,     0,     0,     0,
     188,     0,   183,     0,   139,   162,   163,   175,   174,   177,
     176,   178,   179,   180,   181,   182,   164,   166,   165,   167,
     168,   169,   173,    69,    86,     0,   131,   134,    83,    98,
      87,     0,     0,   102,    91,     0,   185,     0,   154,   158,
     159,   127,   121,    81,   141,    89,   190,   189,     0,   128,
     136,     0,    93,   186,   140,   135
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yypgoto_[] =
  {
      -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
     320,   -27,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,   321,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,    63,  -175,   256,   -63,   -73,   118,   185,
     -79,  -104,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,   131,  -175,   201,  -175,   -88,  -175,  -175,    87,  -175,
    -175,  -175,  -175,  -175,   -11,   -89,  -175,   115,   189,   -70,
    -175,  -174,   -90,  -175,  -175
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yydefgoto_[] =
  {
        -1,     3,     4,     5,    40,    18,    19,    41,    20,    42,
      21,    64,    77,    44,    22,    23,    60,    24,    25,    45,
      97,   109,    46,    47,    48,    26,    27,    50,    51,    52,
      53,    28,    29,   160,   161,    95,   172,    80,    91,   141,
     180,   181,   212,   256,   304,   111,   253,   112,   142,   143,
     113,    90,   201,   130,   131,   132,   265,   114,   165,   115,
     116,   117,   118,   305,   205,   154,   267,    87,    88,   124,
     193,   194,   166,   195,   156
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char CfdgParser::yytable_ninf_ = -1;
  const unsigned short int
  CfdgParser::yytable_[] =
  {
        59,   110,   155,   144,   157,    93,    65,   162,   119,   120,
      75,   182,   183,   184,   100,   169,   258,   259,   126,   261,
      57,   170,    58,    72,    73,   203,   121,   122,    78,   100,
     177,   301,   101,   302,   102,     6,   103,    54,   104,   178,
     110,   110,   121,   122,   158,   105,   245,   106,   133,    89,
      99,   134,   196,   135,   107,   136,   197,   137,   215,   216,
     217,   218,   159,   179,   138,    92,   128,   125,   171,   204,
      57,    55,    58,   139,    56,   303,   246,   247,   248,   108,
     249,   145,   208,   250,   252,   127,   123,   128,   309,   310,
     214,   209,     1,     2,   127,   146,   128,   147,   140,    55,
     244,    70,   260,    61,   100,   174,   254,   101,   175,   102,
      66,   103,   148,   104,    67,   210,   198,   149,   150,   129,
     105,    68,   106,    69,   271,   151,   152,    71,   312,   107,
     153,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   299,
     126,   121,   122,   100,   186,   294,   101,   127,   102,    74,
     103,   100,   104,    76,   101,    79,   102,   307,   103,   105,
     104,   106,   121,   122,   242,   110,    81,   105,   107,   106,
     144,    82,   133,   121,   122,   134,   107,   135,   243,   136,
     200,   137,   236,   237,   269,   274,   238,   314,   138,    98,
     128,   322,    85,   187,   262,   263,   319,   139,   146,   152,
     147,   300,   321,    86,   206,    92,   318,   207,    94,   233,
     234,   235,   236,   237,   313,   148,   238,    62,    63,   163,
     149,   150,   315,    83,    84,   221,   222,   167,   151,   152,
     262,   263,   168,   270,   264,   188,   173,   189,   223,   224,
     225,   226,   227,   228,   311,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   221,   222,   238,   190,   191,   176,
     213,   185,   199,   325,   214,   192,   240,   223,   224,   225,
     226,   227,   228,   219,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   221,   222,   238,   241,   174,   255,   257,
     238,   239,   324,   207,   320,   293,   223,   224,   225,   226,
     227,   228,   316,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   221,   222,   238,    43,    49,    96,   268,   211,
     272,   266,   295,   202,   273,   223,   224,   225,   226,   227,
     228,   220,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   221,   222,   238,     0,     0,     0,     0,     0,   296,
       0,     0,     0,     0,   223,   224,   225,   226,   227,   228,
       0,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     221,   222,   238,     0,     0,     0,     0,     0,   297,     0,
       0,     0,     0,   223,   224,   225,   226,   227,   228,     0,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   221,
     222,   238,     0,     0,     0,     0,     0,   298,     0,     0,
       0,     0,   223,   224,   225,   226,   227,   228,     0,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   221,   222,
     238,     0,     0,     0,     0,     0,   308,     0,     0,     0,
       0,   223,   224,   225,   226,   227,   228,     0,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   221,   222,   238,
       0,     0,     0,     0,     0,   317,     0,     0,     0,     0,
     223,   224,   225,   226,   227,   228,     0,   229,   230,   231,
     232,   233,   234,   235,   236,   237,     0,   146,   238,   147,
     146,     0,   147,     0,   323,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   148,     0,     0,   148,     0,   149,
     150,     0,   149,   150,   221,   222,     0,   151,   152,     0,
     151,   152,   251,   221,   222,   306,     0,   223,   224,   225,
     226,   227,   228,     0,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   221,   222,   238,     0,   233,   234,   235,
     236,   237,     0,     0,   238,     0,   223,   224,   225,   226,
     227,   228,     0,   229,   230,   221,   222,   233,   234,   235,
     236,   237,     0,     0,   238,     0,     0,     0,   223,   224,
     225,   226,   227,   228,     0,   229,   221,   222,     0,   233,
     234,   235,   236,   237,     0,     0,   238,     0,     0,   223,
     224,   225,   226,   227,   228,   221,   222,     0,     0,     0,
     233,   234,   235,   236,   237,     0,     0,   238,   223,   224,
     225,   226,   146,     0,   147,   164,     0,   147,     0,   233,
     234,   235,   236,   237,     0,     0,   238,     0,     0,   148,
       0,     0,   148,     0,   149,   150,     7,   149,   150,     8,
       9,    10,   151,   152,     0,   151,   152,     0,     0,     0,
      11,     0,    12,     0,    13,    30,     0,    14,    31,    32,
      33,     0,    15,    16,    17,     0,     0,     0,     0,    34,
       0,    35,     0,    13,     0,     0,    36,     0,     0,     0,
       0,    37,    38,    39
  };

  /* YYCHECK.  */
  const short int
  CfdgParser::yycheck_[] =
  {
        11,    80,    92,    91,    93,    68,    17,    97,    81,    82,
      37,   115,   116,   117,     8,   104,   190,   191,    88,   193,
      55,    10,    57,    34,    35,    10,    17,    18,    39,     8,
      24,    14,    11,    16,    13,     0,    15,    24,    17,    33,
     119,   120,    17,    18,     6,    24,    10,    26,     8,    60,
      77,    11,    24,    13,    33,    15,    28,    17,   148,   149,
     150,   151,    24,    57,    24,    54,    26,    58,    57,    54,
      55,    24,    57,    33,    24,    58,   165,   167,   168,    58,
     170,    10,    24,   172,   174,    24,    61,    26,   262,   263,
      54,    33,     4,     5,    24,    24,    26,    26,    58,    24,
     163,    26,   192,    10,     8,    54,   179,    11,    57,    13,
      57,    15,    41,    17,    57,    57,   127,    46,    47,    58,
      24,    24,    26,    24,   214,    54,    55,    24,    58,    33,
      59,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   253,
     220,    17,    18,     8,    58,   244,    11,    24,    13,    10,
      15,     8,    17,    56,    11,    57,    13,   257,    15,    24,
      17,    26,    17,    18,    45,   254,    57,    24,    33,    26,
     268,    57,     8,    17,    18,    11,    33,    13,    59,    15,
      57,    17,    49,    50,    10,    61,    53,   267,    24,    24,
      26,   305,    26,    58,    22,    23,   295,    33,    24,    55,
      26,    58,   302,    54,    54,    54,    61,    57,    54,    46,
      47,    48,    49,    50,    58,    41,    53,    27,    28,    24,
      46,    47,    58,    54,    55,    22,    23,    54,    54,    55,
      22,    23,    54,    59,    62,    24,    49,    26,    35,    36,
      37,    38,    39,    40,   265,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    22,    23,    53,    46,    47,    12,
      59,    57,    49,    60,    54,    54,    24,    35,    36,    37,
      38,    39,    40,    55,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    22,    23,    53,    24,    54,    14,    54,
      53,    59,    61,    57,    60,   242,    35,    36,    37,    38,
      39,    40,    59,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    22,    23,    53,     5,     5,    71,   210,   144,
      59,   200,   245,   132,   219,    35,    36,    37,    38,    39,
      40,   152,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    22,    23,    53,    -1,    -1,    -1,    -1,    -1,    59,
      -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,    40,
      -1,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      22,    23,    53,    -1,    -1,    -1,    -1,    -1,    59,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    39,    40,    -1,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    22,
      23,    53,    -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    39,    40,    -1,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    22,    23,
      53,    -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    22,    23,    53,
      -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,
      35,    36,    37,    38,    39,    40,    -1,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    -1,    24,    53,    26,
      24,    -1,    26,    -1,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    -1,    -1,    41,    -1,    46,
      47,    -1,    46,    47,    22,    23,    -1,    54,    55,    -1,
      54,    55,    59,    22,    23,    59,    -1,    35,    36,    37,
      38,    39,    40,    -1,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    22,    23,    53,    -1,    46,    47,    48,
      49,    50,    -1,    -1,    53,    -1,    35,    36,    37,    38,
      39,    40,    -1,    42,    43,    22,    23,    46,    47,    48,
      49,    50,    -1,    -1,    53,    -1,    -1,    -1,    35,    36,
      37,    38,    39,    40,    -1,    42,    22,    23,    -1,    46,
      47,    48,    49,    50,    -1,    -1,    53,    -1,    -1,    35,
      36,    37,    38,    39,    40,    22,    23,    -1,    -1,    -1,
      46,    47,    48,    49,    50,    -1,    -1,    53,    35,    36,
      37,    38,    24,    -1,    26,    24,    -1,    26,    -1,    46,
      47,    48,    49,    50,    -1,    -1,    53,    -1,    -1,    41,
      -1,    -1,    41,    -1,    46,    47,     3,    46,    47,     6,
       7,     8,    54,    55,    -1,    54,    55,    -1,    -1,    -1,
      17,    -1,    19,    -1,    21,     3,    -1,    24,     6,     7,
       8,    -1,    29,    30,    31,    -1,    -1,    -1,    -1,    17,
      -1,    19,    -1,    21,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    29,    30,    31
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  CfdgParser::yystos_[] =
  {
         0,     4,     5,    64,    65,    66,     0,     3,     6,     7,
       8,    17,    19,    21,    24,    29,    30,    31,    68,    69,
      71,    73,    77,    78,    80,    81,    88,    89,    94,    95,
       3,     6,     7,     8,    17,    19,    24,    29,    30,    31,
      67,    70,    72,    73,    76,    82,    85,    86,    87,    88,
      90,    91,    92,    93,    24,    24,    24,    55,    57,   127,
      79,    10,    27,    28,    74,   127,    57,    57,    24,    24,
      26,    24,   127,   127,    10,    74,    56,    75,   127,    57,
     100,    57,    57,    54,    55,    26,    54,   130,   131,   127,
     114,   101,    54,    99,    54,    98,    98,    83,    24,    74,
       8,    11,    13,    15,    17,    24,    26,    33,    58,    84,
     103,   108,   110,   113,   120,   122,   123,   124,   125,   100,
     100,    17,    18,    61,   132,    58,   132,    24,    26,    58,
     116,   117,   118,     8,    11,    13,    15,    17,    24,    33,
      58,   102,   111,   112,   118,    10,    24,    26,    41,    46,
      47,    54,    55,    59,   128,   135,   137,   128,     6,    24,
      96,    97,   135,    24,    24,   121,   135,    54,    54,   128,
      10,    57,    99,    49,    54,    57,    12,    24,    33,    57,
     103,   104,   104,   104,   104,    57,    58,    58,    24,    26,
      46,    47,    54,   133,   134,   136,    24,    28,   127,    49,
      57,   115,   116,    10,    54,   127,    54,    57,    24,    33,
      57,   102,   105,    59,    54,   135,   135,   135,   135,    55,
     131,    22,    23,    35,    36,    37,    38,    39,    40,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    53,    59,
      24,    24,    45,    59,    99,    10,   128,   135,   135,   135,
     128,    59,   135,   109,   100,    14,   106,    54,   134,   134,
     135,   134,    22,    23,    62,   119,   114,   129,   101,    10,
      59,   135,    59,   130,    61,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,    96,   128,   121,    59,    59,    59,   104,
      58,    14,    16,    58,   107,   126,    59,   135,    59,   134,
     134,   127,    58,    58,   132,    58,    59,    59,    61,   128,
      60,   135,   104,    59,    61,    60
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
      74,    74,    75,    75,    76,    76,    77,    79,    78,    80,
      81,    83,    82,    84,    85,    86,    87,    88,    88,    89,
      90,    90,    91,    92,    93,    94,    95,    96,    96,    97,
      97,    98,    98,    99,    99,    99,    99,   100,   100,   101,
     101,   102,   102,   103,   103,   103,   103,   104,   104,   105,
     105,   106,   106,   107,   108,   108,   108,   109,   108,   108,
     108,   108,   108,   108,   110,   110,   110,   111,   111,   111,
     112,   112,   112,   112,   112,   112,   112,   112,   113,   114,
     114,   115,   115,   116,   117,   117,   119,   118,   120,   120,
     121,   122,   123,   124,   125,   126,   126,   127,   127,   128,
     128,   129,   129,   130,   130,   131,   131,   132,   132,   132,
     132,   133,   133,   134,   134,   134,   134,   134,   134,   134,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   136,   136,   136,   137,   137,
     137,   137
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  CfdgParser::yyr2_[] =
  {
         0,     2,     2,     2,     2,     0,     2,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     3,
       3,     3,     2,     2,     2,     2,     1,     2,     3,     1,
       1,     1,     2,     0,     4,     3,     2,     0,     3,     2,
       2,     0,     4,     3,     3,     2,     3,     2,     3,     4,
       1,     2,     3,     4,     4,     2,     4,     2,     2,     3,
       1,     3,     0,     3,     3,     2,     0,     2,     0,     2,
       0,     4,     2,     4,     3,     3,     4,     3,     1,     3,
       1,     2,     0,     2,     1,     1,     1,     0,     4,     2,
       2,     2,     4,     1,     2,     2,     2,     1,     2,     1,
       2,     2,     1,     1,     2,     1,     1,     1,     2,     2,
       0,     3,     1,     2,     1,     2,     0,     4,     5,     3,
       1,     4,     3,     2,     4,     3,     2,     3,     3,     3,
       5,     2,     0,     2,     0,     2,     0,     2,     3,     2,
       2,     2,     1,     1,     3,     1,     2,     2,     3,     3,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     3,     4,     1,     3,     4,
       4,     1
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
  "background", "$@1", "tile", "size", "global_definition", "$@2",
  "definition", "shape", "shape_singleton_header", "shape_singleton",
  "rule_header_v2", "rule_v2", "rule_header", "path_header", "rule",
  "path", "path_header_v2", "path_v2", "parameter", "buncha_parameters",
  "parameter_list", "parameter_spec", "buncha_elements",
  "buncha_pathOps_v2", "pathOp_simple_v2", "element_simple",
  "one_or_more_elements", "one_or_more_pathOp_v2", "caseBody",
  "caseBody_element", "element", "$@3", "element_v2clue", "pathOp_v2",
  "pathOp_v3clues", "element_loop", "buncha_replacements_v2",
  "one_or_more_replacements_v2", "replacement_simple_v2", "replacement_v2",
  "loopHeader_v2", "$@4", "loopHeader", "loopexp", "ifHeader",
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
      -1,    82,    -1,    70,    -1,    77,    -1,    78,    -1,    71,
      -1,    73,    -1,    80,    -1,    81,    -1,    89,    -1,    95,
      -1,    69,    -1,    24,    10,    -1,    30,    -1,     6,    -1,
       8,    24,    54,    -1,     3,    24,    54,    -1,     3,    24,
      55,    -1,    19,   127,    -1,    31,   127,    -1,    17,   127,
      -1,    29,    74,    -1,    88,    -1,    29,    74,    -1,    30,
      75,    74,    -1,    21,    -1,    27,    -1,    28,    -1,    56,
      24,    -1,    -1,     3,    24,    99,   128,    -1,     3,    24,
      99,    -1,     3,    24,    -1,    -1,    19,    79,   127,    -1,
      31,   127,    -1,    17,   127,    -1,    -1,    24,    10,    83,
     135,    -1,    24,    10,   135,    -1,     6,    24,    98,    -1,
      85,    57,    -1,    86,   100,    58,    -1,     7,    24,    -1,
       7,    24,    26,    -1,    88,    57,   114,    58,    -1,     7,
      -1,     7,    26,    -1,     8,    24,    98,    -1,    90,    57,
     100,    58,    -1,    91,    57,   100,    58,    -1,     8,    24,
      -1,    94,    57,   101,    58,    -1,    24,    24,    -1,     6,
      24,    -1,    97,    45,    96,    -1,    96,    -1,    54,    97,
      59,    -1,    -1,    54,   135,    59,    -1,    54,    10,    59,
      -1,    54,    59,    -1,    -1,   100,   108,    -1,    -1,   101,
     111,    -1,    -1,    33,    57,   129,    58,    -1,    24,   127,
      -1,    33,    54,   135,    59,    -1,    33,    54,    59,    -1,
      24,    99,   128,    -1,     8,    24,    99,   128,    -1,    57,
     100,    58,    -1,   103,    -1,    57,   101,    58,    -1,   102,
      -1,   106,   107,    -1,    -1,   126,   104,    -1,   103,    -1,
      84,    -1,   113,    -1,    -1,   113,    12,   109,   104,    -1,
     122,   104,    -1,   123,   104,    -1,   124,   104,    -1,   125,
      57,   106,    58,    -1,   110,    -1,    26,    49,    -1,    24,
      57,    -1,    33,    57,    -1,   102,    -1,   118,   105,    -1,
     112,    -1,    33,    54,    -1,    24,    54,    -1,     8,    -1,
      11,    -1,    24,    10,    -1,    13,    -1,    17,    -1,    15,
      -1,   120,   104,    -1,   114,   117,    -1,    -1,    57,   114,
      58,    -1,   116,    -1,    24,   127,    -1,   116,    -1,   118,
     115,    -1,    -1,    26,    49,   119,   127,    -1,    11,    24,
      10,   121,   128,    -1,    11,   121,   128,    -1,   135,    -1,
      13,    54,   135,    59,    -1,   122,   104,    14,    -1,    17,
     128,    -1,    15,    54,   135,    59,    -1,    16,   135,    60,
      -1,    14,    60,    -1,    57,   131,    58,    -1,    55,   130,
      61,    -1,    55,   131,    61,    -1,    55,    55,   130,    61,
      61,    -1,   129,   132,    -1,    -1,   130,   132,    -1,    -1,
     131,   132,    -1,    -1,    17,   133,    -1,    17,   134,    62,
      -1,    18,    24,    -1,    18,    28,    -1,   133,   134,    -1,
     134,    -1,    26,    -1,    54,   135,    59,    -1,   136,    -1,
      46,   134,    -1,    47,   134,    -1,   134,    22,   134,    -1,
     134,    23,   134,    -1,    26,    -1,   137,    -1,   135,    22,
     135,    -1,   135,    23,   135,    -1,   135,    45,   135,    -1,
     135,    47,   135,    -1,   135,    46,   135,    -1,   135,    48,
     135,    -1,   135,    49,   135,    -1,   135,    50,   135,    -1,
      46,   135,    -1,    47,   135,    -1,    41,   135,    -1,   135,
      53,   135,    -1,   135,    36,   135,    -1,   135,    35,   135,
      -1,   135,    38,   135,    -1,   135,    37,   135,    -1,   135,
      39,   135,    -1,   135,    40,   135,    -1,   135,    42,   135,
      -1,   135,    43,   135,    -1,   135,    44,   135,    -1,    54,
     135,    59,    -1,   128,    -1,    24,    54,    59,    -1,    24,
      54,   135,    59,    -1,    24,    -1,    24,    54,    59,    -1,
      24,    54,   135,    59,    -1,    24,    54,    10,    59,    -1,
      24,    -1
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
      95,    97,    99,   102,   103,   108,   112,   115,   116,   120,
     123,   126,   127,   132,   136,   140,   143,   147,   150,   154,
     159,   161,   164,   168,   173,   178,   181,   186,   189,   192,
     196,   198,   202,   203,   207,   211,   214,   215,   218,   219,
     222,   223,   228,   231,   236,   240,   244,   249,   253,   255,
     259,   261,   264,   265,   268,   270,   272,   274,   275,   280,
     283,   286,   289,   294,   296,   299,   302,   305,   307,   310,
     312,   315,   318,   320,   322,   325,   327,   329,   331,   334,
     337,   338,   342,   344,   347,   349,   352,   353,   358,   364,
     368,   370,   375,   379,   382,   387,   391,   394,   398,   402,
     406,   412,   415,   416,   419,   420,   423,   424,   427,   431,
     434,   437,   440,   442,   444,   448,   450,   453,   456,   460,
     464,   466,   468,   472,   476,   480,   484,   488,   492,   496,
     500,   503,   506,   509,   513,   517,   521,   525,   529,   533,
     537,   541,   545,   549,   553,   555,   559,   564,   566,   570,
     575,   580
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  CfdgParser::yyrline_[] =
  {
         0,   175,   175,   175,   178,   183,   187,   192,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   231,   232,   233,   234,
     235,   236,   240,   241,   242,   243,   244,   248,   257,   268,
     275,   275,   278,   279,   283,   294,   306,   317,   317,   329,
     340,   356,   356,   366,   374,   390,   400,   408,   417,   432,
     440,   448,   461,   482,   490,   499,   512,   519,   525,   533,
     534,   538,   539,   543,   544,   545,   546,   550,   553,   557,
     560,   564,   571,   581,   587,   593,   601,   611,   613,   619,
     621,   627,   630,   634,   638,   640,   642,   651,   651,   663,
     672,   681,   690,   697,   704,   705,   706,   710,   712,   720,
     732,   733,   734,   735,   736,   737,   738,   739,   743,   749,
     752,   756,   758,   764,   773,   775,   786,   786,   801,   812,
     825,   837,   846,   854,   865,   874,   900,   911,   916,   923,
     928,   935,   938,   942,   945,   949,   952,   956,   961,   971,
     976,   983,   987,   993,   995,   997,   999,  1001,  1003,  1008,
    1015,  1017,  1019,  1024,  1029,  1031,  1033,  1035,  1037,  1039,
    1041,  1043,  1045,  1047,  1049,  1051,  1053,  1055,  1057,  1059,
    1061,  1063,  1065,  1067,  1069,  1073,  1078,  1084,  1091,  1096,
    1102,  1108
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
  const int CfdgParser::yylast_ = 703;
  const int CfdgParser::yynnts_ = 75;
  const int CfdgParser::yyempty_ = -2;
  const int CfdgParser::yyfinal_ = 6;
  const int CfdgParser::yyterror_ = 1;
  const int CfdgParser::yyerrcode_ = 256;
  const int CfdgParser::yyntokens_ = 63;

  const unsigned int CfdgParser::yyuser_token_number_max_ = 301;
  const CfdgParser::token_number_type CfdgParser::yyundef_token_ = 2;


} // yy

/* Line 1053 of lalr1.cc  */
#line 3289 "cfdg.tab.cpp"


/* Line 1055 of lalr1.cc  */
#line 1114 "../../src-common/cfdg.ypp"


void yy::CfdgParser::error(const CfdgParser::location_type& l, const std::string& m)
{
    driver.error(l, m);
}

