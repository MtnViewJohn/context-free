/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++

   Copyright (C) 2002, 2003, 2004, 2005, 2006 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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


#include "cfdg.tab.hpp"

/* User implementation prologue.  */
#line 115 "../../src-common/cfdg.ypp"

#include "scanner.h"
#include "math.h"
#include "builder.h"
	
#undef yylex
#define yylex driver.lexer->lex


/* Line 317 of lalr1.cc.  */
#line 51 "cfdg.tab.cpp"

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

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG							\
  for (bool yydebugcond_ = yydebug_; yydebugcond_; yydebugcond_ = false)	\
    (*yycdebug_)

/* Enable debugging if requested.  */
#if YYDEBUG

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

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab

namespace yy
{
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
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
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
#endif /* ! YYDEBUG */

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
        case 35: /* "USER_STRING" */
#line 110 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };
#line 211 "cfdg.tab.cpp"
	break;
      case 38: /* "USER_FILENAME" */
#line 110 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };
#line 216 "cfdg.tab.cpp"
	break;
      case 39: /* "USER_QSTRING" */
#line 110 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };
#line 221 "cfdg.tab.cpp"
	break;
      case 43: /* "USER_PATHOP" */
#line 110 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->string); };
#line 226 "cfdg.tab.cpp"
	break;
      case 81: /* "buncha_pathOps" */
#line 113 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->path); };
#line 231 "cfdg.tab.cpp"
	break;
      case 82: /* "pathOp" */
#line 113 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->path); };
#line 236 "cfdg.tab.cpp"
	break;
      case 85: /* "point" */
#line 112 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };
#line 241 "cfdg.tab.cpp"
	break;
      case 92: /* "modification" */
#line 112 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };
#line 246 "cfdg.tab.cpp"
	break;
      case 93: /* "path_modification" */
#line 112 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };
#line 251 "cfdg.tab.cpp"
	break;
      case 94: /* "buncha_path_adjustments" */
#line 112 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };
#line 256 "cfdg.tab.cpp"
	break;
      case 95: /* "path_adjustment" */
#line 112 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };
#line 261 "cfdg.tab.cpp"
	break;
      case 96: /* "buncha_adjustments" */
#line 112 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };
#line 266 "cfdg.tab.cpp"
	break;
      case 97: /* "buncha_color_adjustments" */
#line 112 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };
#line 271 "cfdg.tab.cpp"
	break;
      case 98: /* "adjustment" */
#line 112 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };
#line 276 "cfdg.tab.cpp"
	break;
      case 99: /* "geom_adjustment" */
#line 112 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };
#line 281 "cfdg.tab.cpp"
	break;
      case 100: /* "color_adjustment" */
#line 112 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->mod); };
#line 286 "cfdg.tab.cpp"
	break;
      case 102: /* "exp" */
#line 111 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };
#line 291 "cfdg.tab.cpp"
	break;
      case 103: /* "exp2" */
#line 111 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };
#line 296 "cfdg.tab.cpp"
	break;
      case 104: /* "func" */
#line 111 "../../src-common/cfdg.ypp"
	{ delete (yyvaluep->expression); };
#line 301 "cfdg.tab.cpp"
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


  int
  CfdgParser::parse ()
  {
    /// Look-ahead and look-ahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the look-ahead.
    semantic_type yylval;
    /// Location of the look-ahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location yyerror_range[2];

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
    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without look-ahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a look-ahead token.  */
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

    /* Accept?  */
    if (yyn == yyfinal_)
      goto yyacceptlab;

    /* Shift the look-ahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted unless it is eof.  */
    if (yychar != yyeof_)
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
	  case 13:
#line 145 "../../src-common/cfdg.ypp"
    {
            driver.IncludeFile(*(yysemantic_stack_[(2) - (2)].string));
            delete (yysemantic_stack_[(2) - (2)].string);
        ;}
    break;

  case 14:
#line 150 "../../src-common/cfdg.ypp"
    {
            driver.IncludeFile(*(yysemantic_stack_[(2) - (2)].string));
            delete (yysemantic_stack_[(2) - (2)].string);
        ;}
    break;

  case 15:
#line 157 "../../src-common/cfdg.ypp"
    {
            driver.Initialize(*(yysemantic_stack_[(2) - (2)].string));
            delete (yysemantic_stack_[(2) - (2)].string);
        ;}
    break;

  case 16:
#line 163 "../../src-common/cfdg.ypp"
    {
            const char* errmsg = driver.Background((yysemantic_stack_[(4) - (3)].mod));
            delete (yysemantic_stack_[(4) - (3)].mod);
            if (errmsg) {
                error((yylocation_stack_[(4) - (3)]), errmsg);
                YYABORT;
            }
        ;}
    break;

  case 17:
#line 174 "../../src-common/cfdg.ypp"
    {
            const char *errmsg = driver.buildTileTransform((yysemantic_stack_[(2) - (2)].mod));
            delete (yysemantic_stack_[(2) - (2)].mod);
            if (errmsg) {
                error((yylocation_stack_[(2) - (2)]), errmsg);
                YYABORT;
            }
        ;}
    break;

  case 18:
#line 185 "../../src-common/cfdg.ypp"
    {
            const char *errmsg = driver.buildSizeTransform((yysemantic_stack_[(2) - (2)].mod));
            delete (yysemantic_stack_[(2) - (2)].mod);
            if (errmsg) {
                error((yylocation_stack_[(2) - (2)]), errmsg);
                YYABORT;
            }
        ;}
    break;

  case 20:
#line 200 "../../src-common/cfdg.ypp"
    { 
            const char* errmsg = driver.AddParameter();
            if (errmsg) {
				error ((yylocation_stack_[(3) - (3)]), errmsg);
				YYABORT;
            }
            (yyval.bodyCount) = (yysemantic_stack_[(3) - (1)].bodyCount) + 1; 
        ;}
    break;

  case 21:
#line 208 "../../src-common/cfdg.ypp"
    { 
            driver.NewParameters(); 
            (yyval.bodyCount) = 0; 
        ;}
    break;

  case 22:
#line 215 "../../src-common/cfdg.ypp"
    { 
			const char* errmsg = driver.NextParameter(*(yysemantic_stack_[(3) - (1)].string), (yysemantic_stack_[(3) - (3)].expression));
            delete (yysemantic_stack_[(3) - (1)].string);
			if (errmsg) {
				error (*errmsg == '0' ? (yylocation_stack_[(3) - (3)]) : (yylocation_stack_[(3) - (1)]), errmsg + 1);
				YYABORT;
			}
        ;}
    break;

  case 23:
#line 226 "../../src-common/cfdg.ypp"
    {
			const char* errmsg = driver.SetShape(*(yysemantic_stack_[(3) - (2)].string), (yysemantic_stack_[(3) - (3)].bodyCount));
			delete (yysemantic_stack_[(3) - (2)].string);
			if (errmsg) {
				error((yylocation_stack_[(3) - (2)]), errmsg);
				YYABORT;
			}
		;}
    break;

  case 24:
#line 233 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(7) - (3)].bodyCount) >= 0) driver.RewindParameters();
        ;}
    break;

  case 25:
#line 239 "../../src-common/cfdg.ypp"
    {
            const char *errmsg = driver.CheckRule(*(yysemantic_stack_[(6) - (2)].string), false, (yysemantic_stack_[(6) - (3)].bodyCount));
            if (errmsg) {
                error((yylocation_stack_[(6) - (2)]), errmsg);
                delete (yysemantic_stack_[(6) - (2)].string);
                YYABORT;
            }
            driver.AddRule(*(yysemantic_stack_[(6) - (2)].string), 1.0, (yysemantic_stack_[(6) - (3)].bodyCount));
            if ((yysemantic_stack_[(6) - (3)].bodyCount) >= 0) driver.RewindParameters();
            delete (yysemantic_stack_[(6) - (2)].string);
        ;}
    break;

  case 26:
#line 251 "../../src-common/cfdg.ypp"
    {
            const char *errmsg = driver.CheckRule(*(yysemantic_stack_[(6) - (2)].string), false, -1);
            if (errmsg) {
                error((yylocation_stack_[(6) - (2)]), errmsg);
                delete (yysemantic_stack_[(6) - (2)].string);
                delete (yysemantic_stack_[(6) - (3)].string);
                YYABORT;
            }
            driver.AddRule(*(yysemantic_stack_[(6) - (2)].string), atof((yysemantic_stack_[(6) - (3)].string)->c_str()), -1);
            delete (yysemantic_stack_[(6) - (2)].string);
            delete (yysemantic_stack_[(6) - (3)].string);
        ;}
    break;

  case 29:
#line 271 "../../src-common/cfdg.ypp"
    {
			driver.AddRule(1.0);
		;}
    break;

  case 30:
#line 275 "../../src-common/cfdg.ypp"
    {
			driver.AddRule(atof((yysemantic_stack_[(5) - (2)].string)->c_str()));
			delete (yysemantic_stack_[(5) - (2)].string);
		;}
    break;

  case 31:
#line 282 "../../src-common/cfdg.ypp"
    {
            const char *errmsg = driver.CheckRule(*(yysemantic_stack_[(6) - (2)].string), true, (yysemantic_stack_[(6) - (3)].bodyCount));
            if (errmsg) {
                error((yylocation_stack_[(6) - (2)]), errmsg);
                delete (yysemantic_stack_[(6) - (2)].string);
                delete (yysemantic_stack_[(6) - (5)].path);
                YYABORT;
            }
            Rule newPath;
            errmsg = driver.makePath(newPath, (yysemantic_stack_[(6) - (5)].path));
            if (errmsg) {
                error((yylocation_stack_[(6) - (5)]), errmsg);
                delete (yysemantic_stack_[(6) - (2)].string);
                delete (yysemantic_stack_[(6) - (5)].path);
                YYABORT;
            }
            (yysemantic_stack_[(6) - (5)].path)->finishPath(newPath, true);
            driver.AddPath(*(yysemantic_stack_[(6) - (2)].string), newPath, (yysemantic_stack_[(6) - (3)].bodyCount));
            if ((yysemantic_stack_[(6) - (3)].bodyCount) >= 0) driver.RewindParameters();
            delete (yysemantic_stack_[(6) - (2)].string);
            delete (yysemantic_stack_[(6) - (5)].path);
        ;}
    break;

  case 32:
#line 307 "../../src-common/cfdg.ypp"
    {
			const char* errmsg = driver.NextParameter(*(yysemantic_stack_[(2) - (1)].string), *(yysemantic_stack_[(2) - (2)].string));
			delete (yysemantic_stack_[(2) - (1)].string);
			delete (yysemantic_stack_[(2) - (2)].string);
			if (errmsg) {
				error (*errmsg == '0' ? (yylocation_stack_[(2) - (1)]) : (yylocation_stack_[(2) - (2)]), errmsg + 1);
				YYABORT;
			}
		;}
    break;

  case 33:
#line 319 "../../src-common/cfdg.ypp"
    { 
            const char* errmsg = driver.AddParameter();
            if (errmsg) {
				error ((yylocation_stack_[(3) - (3)]), errmsg);
				YYABORT;
            }
            (yyval.bodyCount) = (yysemantic_stack_[(3) - (1)].bodyCount) + 1; 
        ;}
    break;

  case 34:
#line 327 "../../src-common/cfdg.ypp"
    { 
            driver.NewParameters(); 
            (yyval.bodyCount) = 0; 
        ;}
    break;

  case 35:
#line 334 "../../src-common/cfdg.ypp"
    { (yyval.bodyCount) = (yysemantic_stack_[(3) - (2)].bodyCount); ;}
    break;

  case 36:
#line 335 "../../src-common/cfdg.ypp"
    { (yyval.bodyCount) = -1; ;}
    break;

  case 37:
#line 339 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (1)].path)) {
                if ((yysemantic_stack_[(2) - (2)].path)) (yysemantic_stack_[(2) - (1)].path)->append((yysemantic_stack_[(2) - (2)].path));
                (yyval.path) = (yysemantic_stack_[(2) - (1)].path);
            } else {
                (yyval.path) = (yysemantic_stack_[(2) - (2)].path);
            }
        ;}
    break;

  case 38:
#line 347 "../../src-common/cfdg.ypp"
    { (yyval.path) = 0; ;}
    break;

  case 39:
#line 351 "../../src-common/cfdg.ypp"
    {
            ASTpath* item =  new ASTpath((yysemantic_stack_[(4) - (1)].string), (yysemantic_stack_[(4) - (3)].mod));
            if (item->errmsg) {
                error(*(item->errmsg) == '0' ? (yylocation_stack_[(4) - (1)]) : (yylocation_stack_[(4) - (3)]), (item->errmsg) + 1);
                delete item;
                YYABORT;
            }
            (yyval.path) = item;
        ;}
    break;

  case 40:
#line 361 "../../src-common/cfdg.ypp"
    {
            ++driver.mLoopDepth;
        ;}
    break;

  case 41:
#line 363 "../../src-common/cfdg.ypp"
    {
            --driver.mLoopDepth;
            const char *errmsg = driver.CheckLoopTransform(*(yysemantic_stack_[(8) - (1)].string), (yysemantic_stack_[(8) - (3)].mod));
            if (errmsg) {
                error((yylocation_stack_[(8) - (3)]), errmsg);
                delete (yysemantic_stack_[(8) - (1)].string);
                delete (yysemantic_stack_[(8) - (3)].mod);
                delete (yysemantic_stack_[(8) - (5)].string);
                delete (yysemantic_stack_[(8) - (7)].mod);
                YYABORT;
            }
            ASTpath* body = new ASTpath((yysemantic_stack_[(8) - (5)].string), (yysemantic_stack_[(8) - (7)].mod));
            if (body->errmsg) {
                error(*(body->errmsg) == '0' ? (yylocation_stack_[(8) - (5)]) : (yylocation_stack_[(8) - (7)]), (body->errmsg) + 1);
                delete (yysemantic_stack_[(8) - (1)].string);
                delete (yysemantic_stack_[(8) - (3)].mod);
                delete (yysemantic_stack_[(8) - (5)].string);
                delete (yysemantic_stack_[(8) - (7)].mod);
                YYABORT;
            }
            bool isCommand = body->pathElement < ASTpath::MOVETO;
            ASTpath* start = new ASTpath(
                isCommand ? ASTpath::loopStart : ASTpath::opLoopStart, 0);
            ASTpath* end = new ASTpath(
                isCommand ? ASTpath::loopEnd : ASTpath::opLoopEnd, (yysemantic_stack_[(8) - (3)].mod));
            start->rest = body;
            body->rest = end;
            end->startOfLoop = start;
            start->params.assign(*(yysemantic_stack_[(8) - (1)].string));
            (yyval.path) = start;
        ;}
    break;

  case 42:
#line 395 "../../src-common/cfdg.ypp"
    {
            ++driver.mLoopDepth;
        ;}
    break;

  case 43:
#line 397 "../../src-common/cfdg.ypp"
    {
            --driver.mLoopDepth;
            const char *errmsg = driver.CheckLoopTransform(*(yysemantic_stack_[(7) - (1)].string), (yysemantic_stack_[(7) - (3)].mod));
            if (errmsg) {
                delete (yysemantic_stack_[(7) - (1)].string);
                delete (yysemantic_stack_[(7) - (3)].mod);
                delete (yysemantic_stack_[(7) - (6)].path);
                error((yylocation_stack_[(7) - (3)]), errmsg);
                YYABORT;
            }
            ASTpath* body = (yysemantic_stack_[(7) - (6)].path);
            if (body == 0) {
                delete (yysemantic_stack_[(7) - (1)].string);
                delete (yysemantic_stack_[(7) - (3)].mod);
                delete (yysemantic_stack_[(7) - (6)].path);
                (yyval.path) = 0;
            } else {
                ASTpath::pathElemListEnum looptype = body->loopType();
                if (looptype == ASTpath::mixed) {
                    delete (yysemantic_stack_[(7) - (1)].string);
                    delete (yysemantic_stack_[(7) - (3)].mod);
                    delete (yysemantic_stack_[(7) - (6)].path);
                    error((yylocation_stack_[(7) - (5)]), "Cannot mix path commands and path operations in the same loop");
                    YYABORT;
                } 
                bool isCommand = looptype == ASTpath::command;
                ASTpath* start = new ASTpath(
                    isCommand ? ASTpath::loopStart : ASTpath::opLoopStart, 0);
                ASTpath* end = new ASTpath(
                    isCommand ? ASTpath::loopEnd : ASTpath::opLoopEnd, (yysemantic_stack_[(7) - (3)].mod));
                start->rest = body;
                body->append(end);
                end->startOfLoop = start;
                start->params.assign(*(yysemantic_stack_[(7) - (1)].string));
                (yyval.path) = start;
            }
        ;}
    break;

  case 44:
#line 437 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::x1, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 45:
#line 441 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::x2, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 46:
#line 445 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::y1, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 47:
#line 449 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::y2, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 48:
#line 453 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::xrad, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 49:
#line 457 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::yrad, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 52:
#line 468 "../../src-common/cfdg.ypp"
    { (yyval.index) = (yysemantic_stack_[(2) - (1)].index); ;}
    break;

  case 53:
#line 469 "../../src-common/cfdg.ypp"
    { (yyval.index) = driver.LoopStart(); ;}
    break;

  case 54:
#line 473 "../../src-common/cfdg.ypp"
    { (yyval.index) = (yysemantic_stack_[(2) - (1)].index); ;}
    break;

  case 55:
#line 474 "../../src-common/cfdg.ypp"
    { (yyval.index) = driver.LoopFinallyStart(); ;}
    break;

  case 57:
#line 479 "../../src-common/cfdg.ypp"
    { driver.DefineStart(); ;}
    break;

  case 58:
#line 483 "../../src-common/cfdg.ypp"
    {
            const char* errmsg = driver.AddReplacement(*(yysemantic_stack_[(2) - (1)].string), (yysemantic_stack_[(2) - (2)].mod));
            delete (yysemantic_stack_[(2) - (1)].string);
            delete (yysemantic_stack_[(2) - (2)].mod);
            if (errmsg) {
                error((yylocation_stack_[(2) - (2)]), errmsg);
                YYABORT;
            }
        ;}
    break;

  case 59:
#line 493 "../../src-common/cfdg.ypp"
    {
            (yyval.index) = driver.LoopStart();
        ;}
    break;

  case 60:
#line 495 "../../src-common/cfdg.ypp"
    {
            driver.CheckLoopTransform(*(yysemantic_stack_[(6) - (1)].string), (yysemantic_stack_[(6) - (3)].mod)); 
            const char* errmsg = driver.AddReplacement(*(yysemantic_stack_[(6) - (5)].string), (yysemantic_stack_[(6) - (6)].mod));
            if (errmsg) {
                error((yylocation_stack_[(6) - (5)]), errmsg);
                delete (yysemantic_stack_[(6) - (1)].string);
                delete (yysemantic_stack_[(6) - (3)].mod);
                delete (yysemantic_stack_[(6) - (5)].string);
                delete (yysemantic_stack_[(6) - (6)].mod);
                YYABORT;
            }
            errmsg = driver.LoopEnd((yysemantic_stack_[(6) - (4)].index), atoi((yysemantic_stack_[(6) - (1)].string)->c_str()), (yysemantic_stack_[(6) - (3)].mod));
            delete (yysemantic_stack_[(6) - (1)].string);
            delete (yysemantic_stack_[(6) - (3)].mod);
            delete (yysemantic_stack_[(6) - (5)].string);
            delete (yysemantic_stack_[(6) - (6)].mod);
            if (errmsg) {
                error((yylocation_stack_[(6) - (3)]), errmsg);
                YYABORT;
            }
        ;}
    break;

  case 61:
#line 517 "../../src-common/cfdg.ypp"
    {
            driver.CheckLoopTransform(*(yysemantic_stack_[(6) - (1)].string), (yysemantic_stack_[(6) - (3)].mod)); 
            driver.LoopEnd((yysemantic_stack_[(6) - (5)].index), atoi((yysemantic_stack_[(6) - (1)].string)->c_str()), (yysemantic_stack_[(6) - (3)].mod));
            delete (yysemantic_stack_[(6) - (1)].string);
            delete (yysemantic_stack_[(6) - (3)].mod);
        ;}
    break;

  case 62:
#line 524 "../../src-common/cfdg.ypp"
    {
            driver.CheckLoopTransform(*(yysemantic_stack_[(9) - (1)].string), (yysemantic_stack_[(9) - (3)].mod)); 
            driver.LoopEnd((yysemantic_stack_[(9) - (5)].index), (yysemantic_stack_[(9) - (8)].index), atoi((yysemantic_stack_[(9) - (1)].string)->c_str()), (yysemantic_stack_[(9) - (3)].mod));
            delete (yysemantic_stack_[(9) - (1)].string);
            delete (yysemantic_stack_[(9) - (3)].mod);
        ;}
    break;

  case 63:
#line 531 "../../src-common/cfdg.ypp"
    {
            driver.DefineEnd();
            driver.RewindParameters();
        ;}
    break;

  case 64:
#line 538 "../../src-common/cfdg.ypp"
    {
            (yysemantic_stack_[(3) - (2)].mod)->entropy((yysemantic_stack_[(3) - (2)].mod)->parameter);     // insert entropy into initial Entropy element
            (yysemantic_stack_[(3) - (2)].mod)->simplify(driver.mCurrentParameters);
            (yyval.mod) = (yysemantic_stack_[(3) - (2)].mod)->makeCanonical();
        ;}
    break;

  case 65:
#line 544 "../../src-common/cfdg.ypp"
    {
            (yysemantic_stack_[(3) - (2)].mod)->entropy((yysemantic_stack_[(3) - (2)].mod)->parameter);     // insert entropy into initial Entropy element
            (yysemantic_stack_[(3) - (2)].mod)->simplify(driver.mCurrentParameters);
            (yyval.mod) = (yysemantic_stack_[(3) - (2)].mod)->mergeXY();
        ;}
    break;

  case 66:
#line 552 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = (yysemantic_stack_[(3) - (2)].mod)->makeCanonical();
        ;}
    break;

  case 67:
#line 556 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = (yysemantic_stack_[(3) - (2)].mod)->mergeXY();
        ;}
    break;

  case 68:
#line 562 "../../src-common/cfdg.ypp"
    {
            (yysemantic_stack_[(2) - (1)].mod)->append((yysemantic_stack_[(2) - (2)].mod));
            (yyval.mod) = (yysemantic_stack_[(2) - (1)].mod);
        ;}
    break;

  case 69:
#line 566 "../../src-common/cfdg.ypp"
    { (yyval.mod) = new ASTmod(ASTmod::Entropy, ""); ;}
    break;

  case 70:
#line 570 "../../src-common/cfdg.ypp"
    { (yyval.mod) = (yysemantic_stack_[(1) - (1)].mod); ;}
    break;

  case 71:
#line 572 "../../src-common/cfdg.ypp"
    { (yyval.mod) = (yysemantic_stack_[(1) - (1)].mod); ;}
    break;

  case 72:
#line 574 "../../src-common/cfdg.ypp"
    { (yyval.mod) = (yysemantic_stack_[(1) - (1)].mod); ;}
    break;

  case 73:
#line 576 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::param, *(yysemantic_stack_[(2) - (2)].string));
            delete (yysemantic_stack_[(2) - (2)].string);
        ;}
    break;

  case 74:
#line 581 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::param, *(yysemantic_stack_[(2) - (2)].string));
            delete (yysemantic_stack_[(2) - (2)].string);
        ;}
    break;

  case 75:
#line 586 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::stroke, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 76:
#line 590 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (1)]), "Z changes are not allowed in paths");
            delete (yysemantic_stack_[(2) - (2)].expression);
            (yyval.mod) = 0;
            YYABORT;
        ;}
    break;

  case 77:
#line 599 "../../src-common/cfdg.ypp"
    {
            (yysemantic_stack_[(2) - (1)].mod)->append((yysemantic_stack_[(2) - (2)].mod));
            (yyval.mod) = (yysemantic_stack_[(2) - (1)].mod);
        ;}
    break;

  case 78:
#line 603 "../../src-common/cfdg.ypp"
    { (yyval.mod) = new ASTmod(ASTmod::Entropy, ""); ;}
    break;

  case 79:
#line 607 "../../src-common/cfdg.ypp"
    {
            (yysemantic_stack_[(2) - (1)].mod)->append((yysemantic_stack_[(2) - (2)].mod));
            (yyval.mod) = (yysemantic_stack_[(2) - (1)].mod);
        ;}
    break;

  case 80:
#line 611 "../../src-common/cfdg.ypp"
    { (yyval.mod) = new ASTmod(ASTmod::Entropy, "");; ;}
    break;

  case 83:
#line 619 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::z, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 84:
#line 623 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (1)]), "Parameters are not allowed in rules");
            delete (yysemantic_stack_[(2) - (2)].string);
            (yyval.mod) = 0;
            YYABORT;
        ;}
    break;

  case 85:
#line 630 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (1)]), "Parameters are not allowed in rules");
            delete (yysemantic_stack_[(2) - (2)].string);
            (yyval.mod) = 0;
            YYABORT;
        ;}
    break;

  case 86:
#line 637 "../../src-common/cfdg.ypp"
    {
            error((yylocation_stack_[(2) - (1)]), "Stroke widths are not allowed in rules");
            delete (yysemantic_stack_[(2) - (2)].expression);
            (yyval.mod) = 0;
            YYABORT;
        ;}
    break;

  case 87:
#line 646 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::rot, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 88:
#line 650 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::flip, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 89:
#line 654 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::x, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 90:
#line 658 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::y, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 91:
#line 662 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::transform, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 92:
#line 666 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::skew, 
                                     new ASTcons((yysemantic_stack_[(3) - (2)].expression), (yysemantic_stack_[(3) - (3)].expression)));
        ;}
    break;

  case 93:
#line 671 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::size, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 94:
#line 677 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::color, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 95:
#line 681 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::hue, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 96:
#line 685 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::sat, (yysemantic_stack_[(2) - (2)].expression));
            driver.inColor();
        ;}
    break;

  case 97:
#line 690 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::bright, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 98:
#line 694 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::alpha, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 99:
#line 698 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::colorTarg, (yysemantic_stack_[(3) - (2)].expression));
        ;}
    break;

  case 100:
#line 702 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::hueTarg, (yysemantic_stack_[(3) - (2)].expression));
        ;}
    break;

  case 101:
#line 706 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::satTarg, (yysemantic_stack_[(3) - (2)].expression));
            driver.inColor();
        ;}
    break;

  case 102:
#line 711 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::brightTarg, (yysemantic_stack_[(3) - (2)].expression));
        ;}
    break;

  case 103:
#line 715 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::alphaTarg, (yysemantic_stack_[(3) - (2)].expression));
        ;}
    break;

  case 104:
#line 719 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::targColor, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 105:
#line 723 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::targHue, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 106:
#line 727 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::targSat, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 107:
#line 731 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::targBright, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 108:
#line 735 "../../src-common/cfdg.ypp"
    {
            (yyval.mod) = new ASTmod(ASTmod::targAlpha, (yysemantic_stack_[(2) - (2)].expression));
        ;}
    break;

  case 109:
#line 741 "../../src-common/cfdg.ypp"
    {
            if ((yysemantic_stack_[(2) - (1)].expression) == 0) {
                (yyval.expression) = (yysemantic_stack_[(2) - (2)].expression);
            } else {
                (yyval.expression) = new ASTcons((yysemantic_stack_[(2) - (1)].expression), (yysemantic_stack_[(2) - (2)].expression));
            }
        ;}
    break;

  case 110:
#line 749 "../../src-common/cfdg.ypp"
    { 
            (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); 
        ;}
    break;

  case 111:
#line 755 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string)); ;}
    break;

  case 112:
#line 757 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(2) - (2)].string), true);  ;}
    break;

  case 113:
#line 759 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(2) - (2)].string)); ;}
    break;

  case 114:
#line 761 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); ;}
    break;

  case 115:
#line 763 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); ;}
    break;

  case 116:
#line 767 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTreal(*(yysemantic_stack_[(1) - (1)].string)); ;}
    break;

  case 117:
#line 769 "../../src-common/cfdg.ypp"
    { (yyval.expression) = (yysemantic_stack_[(1) - (1)].expression); ;}
    break;

  case 118:
#line 771 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTcons((yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression));   ;}
    break;

  case 119:
#line 773 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('+', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); ;}
    break;

  case 120:
#line 775 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('-', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); ;}
    break;

  case 121:
#line 777 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('*', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); ;}
    break;

  case 122:
#line 779 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('/', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); ;}
    break;

  case 123:
#line 781 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('-', (yysemantic_stack_[(2) - (2)].expression), new ASTexpression()); ;}
    break;

  case 124:
#line 783 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('+', (yysemantic_stack_[(2) - (2)].expression), new ASTexpression()); ;}
    break;

  case 125:
#line 785 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASToperator('^', (yysemantic_stack_[(3) - (1)].expression), (yysemantic_stack_[(3) - (3)].expression)); ;}
    break;

  case 126:
#line 787 "../../src-common/cfdg.ypp"
    { (yyval.expression) = new ASTparen((yysemantic_stack_[(3) - (2)].expression)); ;}
    break;

  case 127:
#line 791 "../../src-common/cfdg.ypp"
    { 
            ASTfunction* ftype = new ASTfunction(*(yysemantic_stack_[(3) - (1)].string), new ASTexpression(), driver.mSeed);
            delete (yysemantic_stack_[(3) - (1)].string);
            if (ftype->functype <= ASTfunction::NotAFunction) {
                error((yylocation_stack_[(3) - (1)]), ftype->errormsg);
                delete ftype;
                (yyval.expression) = 0;
                YYABORT;
            }
            (yyval.expression) = ftype;
        ;}
    break;

  case 128:
#line 803 "../../src-common/cfdg.ypp"
    { 
            ASTfunction* ftype = new ASTfunction(*(yysemantic_stack_[(4) - (1)].string), (yysemantic_stack_[(4) - (3)].expression), driver.mSeed);
            delete (yysemantic_stack_[(4) - (1)].string);
            if (ftype->functype <= ASTfunction::NotAFunction) {
                error(ftype->functype == ASTfunction::NotAFunction ? (yylocation_stack_[(4) - (1)]) : (yylocation_stack_[(4) - (3)]), 
                      ftype->errormsg);
                delete ftype;       // which deletes $3
                (yyval.expression) = 0;
                YYABORT;
            }
            (yyval.expression) = ftype;
        ;}
    break;

  case 129:
#line 816 "../../src-common/cfdg.ypp"
    { 
            int shape = driver.StringToShape(*(yysemantic_stack_[(1) - (1)].string));
            const char* errmsg = driver.CheckVariable(shape);
            if (errmsg) {
                error((yylocation_stack_[(1) - (1)]), errmsg);
                delete (yysemantic_stack_[(1) - (1)].string);
                YYABORT;
            }
            (yyval.expression) = new ASTvariable(shape, *(yysemantic_stack_[(1) - (1)].string)); 
        ;}
    break;

  case 130:
#line 827 "../../src-common/cfdg.ypp"
    {
            int shape = -atoi((yysemantic_stack_[(2) - (2)].string)->c_str()) - 1;
            const char* errmsg = driver.CheckVariable(shape);
            if (errmsg) {
                error((yylocation_stack_[(2) - (2)]), errmsg);
                delete (yysemantic_stack_[(2) - (2)].string);
                YYABORT;
            }
            (yyval.expression) = new ASTvariable(shape, *(yysemantic_stack_[(2) - (2)].string)); 
        ;}
    break;


    /* Line 675 of lalr1.cc.  */
#line 1448 "cfdg.tab.cpp"
	default: break;
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
	/* If just tried and failed to reuse look-ahead token after an
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

    /* Else will try to reuse look-ahead token after shifting the error
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

    if (yyn == yyfinal_)
      goto yyacceptlab;

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the look-ahead.  YYLOC is available though.
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
    if (yychar != yyeof_ && yychar != yyempty_)
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
  const short int CfdgParser::yypact_ninf_ = -159;
  const short int
  CfdgParser::yypact_[] =
  {
      -159,   329,  -159,    31,    33,    36,    42,    61,    25,    93,
      92,    25,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,    70,    14,    70,   122,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,   130,  -159,   102,   147,   160,   194,
      68,  -159,   295,    74,   328,   180,  -159,     9,   193,  -159,
    -159,  -159,   337,   122,  -159,   337,   337,   337,   337,   337,
     337,   337,   337,   337,   337,   337,   337,   337,   337,   337,
     337,   337,   337,    76,   337,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,   130,  -159,  -159,    73,   112,    20,   197,
    -159,   216,   219,   352,   222,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,   337,  -159,   337,   205,   206,   233,
     234,   235,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,    18,   240,    25,   248,  -159,  -159,  -159,   244,   250,
    -159,  -159,   330,  -159,  -159,  -159,   352,   352,   352,   158,
    -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,    23,
    -159,  -159,   122,  -159,    25,  -159,    64,  -159,   202,   247,
     247,   357,   352,   352,   352,   352,   352,   352,  -159,   249,
    -159,    11,   256,   167,  -159,  -159,   257,  -159,  -159,   214,
     120,   120,   247,   247,   247,  -159,   113,   258,  -159,   265,
     337,   337,   337,   337,   337,   337,   337,   173,   337,  -159,
    -159,  -159,  -159,  -159,   213,    17,   277,   261,    19,  -159,
    -159,   116,    25,  -159,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,   275,  -159,  -159,   117,   278,
    -159,  -159,  -159,    72,  -159,  -159,  -159,   259,  -159,   121,
    -159,  -159,  -159
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  CfdgParser::yydefact_[] =
  {
         3,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     6,     4,     5,     7,     8,    12,    11,
       9,    10,    15,    36,    36,    36,     0,    78,    78,    18,
      80,    14,    13,    17,     0,    23,     0,     0,     0,     0,
       0,    21,     0,     0,     0,     0,    34,     0,     0,    51,
      51,    38,     0,     0,    19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    64,    77,    81,    82,    65,
      16,    79,    32,     0,    35,    28,     0,     0,     0,   129,
     111,     0,     0,     0,     0,    22,   115,    20,    87,    88,
      91,    89,    90,    83,    93,   110,     0,    94,    95,    96,
      97,    98,   104,   105,   106,   107,   108,    84,    85,    86,
      33,     0,     0,     0,     0,    26,    50,    25,     0,     0,
      31,    37,     0,   112,   113,   116,     0,     0,     0,     0,
     117,   130,   109,    92,    99,   100,   101,   102,   103,     0,
      24,    27,     0,    58,     0,    69,     0,   127,     0,   123,
     124,     0,     0,     0,     0,     0,     0,     0,   114,     0,
      51,     0,    59,     0,    69,    69,    40,   128,   126,   118,
     120,   119,   121,   122,   125,    28,     0,     0,    53,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    39,
      70,    68,    71,    72,     0,     0,     0,     0,     0,    29,
      57,     0,     0,    44,    46,    45,    47,    48,    49,    76,
      73,    74,    75,    66,    67,     0,    38,    30,     0,    61,
      52,    60,    69,     0,    63,    56,    55,     0,    43,     0,
      41,    62,    54
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yypgoto_[] =
  {
      -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,   178,
     285,  -159,  -159,  -159,   155,  -159,  -159,   260,  -159,   149,
     115,  -159,  -159,  -159,  -159,   -25,  -159,  -159,  -159,  -158,
    -159,   -11,  -159,  -153,  -159,   314,  -159,  -159,   177,   174,
    -159,   -54,    -3,   -74
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  CfdgParser::yydefgoto_[] =
  {
        -1,     1,    12,    13,    14,    15,    16,    17,    18,    40,
      41,    19,    48,    20,   121,   151,    21,    46,    47,    35,
      88,   131,   206,   207,   200,    86,   211,   239,   228,   126,
     189,    29,   176,   173,   201,    42,    44,    76,   202,   203,
     104,    95,   139,    96
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char CfdgParser::yytable_ninf_ = -43;
  const short int
  CfdgParser::yytable_[] =
  {
        33,    98,    99,   100,   101,   102,   103,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   140,
     119,   204,   205,   149,   149,    87,    55,    56,    57,    58,
      59,   190,   191,   192,   193,   194,   195,   196,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
     142,    36,   143,   230,    83,   128,    53,   129,   140,   197,
     169,   198,   140,   140,   140,    84,    22,   187,    23,    34,
     235,    24,   150,   227,   130,   224,   170,    25,    27,   237,
     122,   242,    28,    55,    56,    57,    58,    59,   140,   140,
     140,   140,   140,   140,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,   128,   123,   129,
     124,   117,   153,    53,    26,   118,    73,   174,    74,   122,
     122,   175,    54,   122,   122,    34,   238,   125,   122,   158,
      31,    32,    79,   159,   160,   161,   213,   214,   215,   216,
     217,   218,   219,   172,   222,   186,    30,   123,   123,   124,
     124,   123,   123,   124,   124,    49,   123,    39,   124,   179,
     180,   181,   182,   183,   184,    45,   127,   209,   165,   166,
     229,   234,   167,    37,    38,   241,    55,    56,    57,    58,
      59,   190,   191,   192,   193,   194,   195,   196,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      50,   231,    52,   162,   163,   164,   165,   166,   220,   197,
     167,   198,   221,    51,   168,    82,    78,    78,    81,    77,
      77,   199,    55,    56,    57,    58,    59,   190,   191,   192,
     193,   194,   195,   196,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    85,   162,   163,   164,
     165,   166,   132,   133,   167,   197,   134,   198,   177,   141,
     163,   164,   165,   166,   144,   145,   167,   223,    55,    56,
      57,    58,    59,   190,   191,   192,   193,   194,   195,   196,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,   146,   147,   148,   152,   154,   155,   156,   167,
     212,   197,   185,   198,    55,    56,    57,    58,    59,   188,
     -42,   210,   225,   240,   226,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,   232,     2,
     171,   236,     3,     4,     5,     6,     7,    73,    97,    74,
     208,   233,    43,   120,     0,     0,     0,     0,     0,    75,
       8,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,     0,     9,     0,     0,    89,     0,   135,     0,    10,
      11,     0,    89,     0,    90,     0,   136,   137,     0,     0,
       0,     0,    80,    91,    92,   138,   157,    89,     0,   135,
      94,     0,    93,     0,     0,     0,     0,    94,   136,   137,
       0,     0,   162,   163,   164,   165,   166,   138,     0,   167,
       0,     0,    94,   178
  };

  /* YYCHECK.  */
  const short int
  CfdgParser::yycheck_[] =
  {
        11,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    93,
      74,   174,   175,     5,     5,    50,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
     104,    37,   106,   211,    45,    35,    45,    37,   132,    42,
      37,    44,   136,   137,   138,    56,    35,    56,    35,    55,
     228,    35,    54,    54,    54,    58,    53,    35,    53,   232,
       7,   239,    57,     9,    10,    11,    12,    13,   162,   163,
     164,   165,   166,   167,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    35,    35,    37,
      37,    35,   123,    45,    53,    39,    42,    53,    44,     7,
       7,    57,    54,     7,     7,    55,    54,    54,     7,   132,
      38,    39,    58,   136,   137,   138,   190,   191,   192,   193,
     194,   195,   196,   154,   198,   170,    53,    35,    35,    37,
      37,    35,    35,    37,    37,    53,    35,    35,    37,   162,
     163,   164,   165,   166,   167,    35,    54,    54,    48,    49,
      54,    54,    52,    24,    25,    54,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      53,   212,     8,    45,    46,    47,    48,    49,    35,    42,
      52,    44,    39,    53,    56,    35,    42,    43,    44,    42,
      43,    54,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    53,    45,    46,    47,
      48,    49,    55,    37,    52,    42,    37,    44,    56,    37,
      46,    47,    48,    49,    59,    59,    52,    54,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    59,    59,    59,    55,    48,    53,    48,    52,
      35,    42,    53,    44,     9,    10,    11,    12,    13,    53,
      53,    53,    35,    54,    53,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    53,     0,
     152,    53,     3,     4,     5,     6,     7,    42,    53,    44,
     185,   226,    28,    83,    -1,    -1,    -1,    -1,    -1,    54,
      21,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    33,    -1,    -1,    35,    -1,    37,    -1,    40,
      41,    -1,    35,    -1,    37,    -1,    46,    47,    -1,    -1,
      -1,    -1,    54,    46,    47,    55,    56,    35,    -1,    37,
      60,    -1,    55,    -1,    -1,    -1,    -1,    60,    46,    47,
      -1,    -1,    45,    46,    47,    48,    49,    55,    -1,    52,
      -1,    -1,    60,    56
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  CfdgParser::yystos_[] =
  {
         0,    62,     0,     3,     4,     5,     6,     7,    21,    33,
      40,    41,    63,    64,    65,    66,    67,    68,    69,    72,
      74,    77,    35,    35,    35,    35,    53,    53,    57,    92,
      53,    38,    39,    92,    55,    80,    37,    80,    80,    35,
      70,    71,    96,    96,    97,    35,    78,    79,    73,    53,
      53,    53,     8,    45,    54,     9,    10,    11,    12,    13,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    42,    44,    54,    98,    99,   100,    58,
      54,   100,    35,    45,    56,    53,    86,    86,    81,    35,
      37,    46,    47,    55,    60,   102,   104,    71,   102,   102,
     102,   102,   102,   102,   101,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,    35,    39,   102,
      78,    75,     7,    35,    37,    54,    90,    54,    35,    37,
      54,    82,    55,    37,    37,    37,    46,    47,    55,   103,
     104,    37,   102,   102,    59,    59,    59,    59,    59,     5,
      54,    76,    55,    92,    48,    53,    48,    56,   103,   103,
     103,   103,    45,    46,    47,    48,    49,    52,    56,    37,
      53,    70,    92,    94,    53,    57,    93,    56,    56,   103,
     103,   103,   103,   103,   103,    53,    86,    56,    53,    91,
      14,    15,    16,    17,    18,    19,    20,    42,    44,    54,
      85,    95,    99,   100,    94,    94,    83,    84,    75,    54,
      53,    87,    35,   102,   102,   102,   102,   102,   102,   102,
      35,    39,   102,    54,    58,    35,    53,    54,    89,    54,
      90,    92,    53,    81,    54,    90,    53,    94,    54,    88,
      54,    54,    90
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
     295,   296,   297,   298,   299,    44,    45,    43,    42,    47,
     300,   301,    94,   123,   125,    40,    41,    91,    93,   124,
      36
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  CfdgParser::yyr1_[] =
  {
         0,    61,    62,    62,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    64,    64,    65,    66,    67,    68,    69,
      70,    70,    71,    73,    72,    74,    74,    75,    75,    76,
      76,    77,    78,    79,    79,    80,    80,    81,    81,    82,
      83,    82,    84,    82,    85,    85,    85,    85,    85,    85,
      86,    86,    87,    87,    88,    88,    89,    89,    90,    91,
      90,    90,    90,    90,    92,    92,    93,    93,    94,    94,
      95,    95,    95,    95,    95,    95,    95,    96,    96,    97,
      97,    98,    98,    98,    98,    98,    98,    99,    99,    99,
      99,    99,    99,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   101,
     101,   102,   102,   102,   102,   102,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   104,   104,   104,
     104
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  CfdgParser::yyr2_[] =
  {
         0,     2,     2,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     4,     2,     2,     4,
       3,     1,     3,     0,     7,     6,     6,     2,     0,     4,
       5,     6,     2,     3,     1,     3,     0,     2,     0,     4,
       0,     8,     0,     7,     2,     2,     2,     2,     2,     2,
       2,     0,     2,     0,     2,     0,     2,     0,     2,     0,
       6,     6,     9,     7,     3,     3,     3,     3,     2,     0,
       1,     1,     1,     2,     2,     2,     2,     2,     0,     2,
       0,     1,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     2,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     2,     2,     2,     2,     2,     2,
       1,     1,     2,     2,     3,     1,     1,     1,     3,     3,
       3,     3,     3,     2,     2,     3,     3,     3,     4,     1,
       2
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const CfdgParser::yytname_[] =
  {
    "$end", "error", "$undefined", "STARTSHAPE", "SHAPE", "RULE", "PATH",
  "DEFINE", "BECOMES", "ROTATE", "FLIP", "TRANSFORM", "XSHIFT", "YSHIFT",
  "XCTRL1", "YCTRL1", "XCTRL2", "YCTRL2", "XRADIUS", "YRADIUS", "ZSHIFT",
  "SIZE", "SKEW", "COLOR", "HUE", "SATURATION", "BRIGHTNESS", "ALPHA",
  "TARGETCOLOR", "TARGETHUE", "TARGETSATURATION", "TARGETBRIGHTNESS",
  "TARGETALPHA", "BACKGROUND", "BADEOF", "USER_STRING", "USER_INTEGER",
  "USER_RATIONAL", "USER_FILENAME", "USER_QSTRING", "INCLUDE", "TILE",
  "PARAMETERS", "USER_PATHOP", "STROKEWIDTH", "','", "'-'", "'+'", "'*'",
  "'/'", "POS", "NEG", "'^'", "'{'", "'}'", "'('", "')'", "'['", "']'",
  "'|'", "'$'", "$accept", "cfdg", "statement", "inclusion",
  "initialization", "background", "tile", "size", "define",
  "buncha_definitions", "definition", "shape", "@1", "rule",
  "buncha_shaperules", "shaperule", "path", "parameter",
  "buncha_parameters", "parameter_list", "buncha_pathOps", "pathOp", "@2",
  "@3", "point", "buncha_replacements", "loop_body", "finally_body",
  "define_body", "replacement", "@4", "modification", "path_modification",
  "buncha_path_adjustments", "path_adjustment", "buncha_adjustments",
  "buncha_color_adjustments", "adjustment", "geom_adjustment",
  "color_adjustment", "explist", "exp", "exp2", "func", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const CfdgParser::rhs_number_type
  CfdgParser::yyrhs_[] =
  {
        62,     0,    -1,    62,    63,    -1,    -1,    65,    -1,    66,
      -1,    64,    -1,    67,    -1,    68,    -1,    74,    -1,    77,
      -1,    72,    -1,    69,    -1,    40,    39,    -1,    40,    38,
      -1,     3,    35,    -1,    33,    53,    97,    54,    -1,    41,
      92,    -1,    21,    92,    -1,     7,    53,    70,    54,    -1,
      70,    45,    71,    -1,    71,    -1,    35,     8,   102,    -1,
      -1,     4,    35,    80,    73,    53,    75,    54,    -1,     5,
      35,    80,    53,    86,    54,    -1,     5,    35,    37,    53,
      86,    54,    -1,    75,    76,    -1,    -1,     5,    53,    86,
      54,    -1,     5,    37,    53,    75,    54,    -1,     6,    35,
      80,    53,    81,    54,    -1,    35,    35,    -1,    79,    45,
      78,    -1,    78,    -1,    55,    79,    56,    -1,    -1,    81,
      82,    -1,    -1,    35,    53,    94,    54,    -1,    -1,    37,
      48,    93,    83,    35,    53,    94,    54,    -1,    -1,    37,
      48,    93,    84,    53,    81,    54,    -1,    14,   102,    -1,
      16,   102,    -1,    15,   102,    -1,    17,   102,    -1,    18,
     102,    -1,    19,   102,    -1,    86,    90,    -1,    -1,    87,
      90,    -1,    -1,    88,    90,    -1,    -1,    89,    90,    -1,
      -1,    35,    92,    -1,    -1,    37,    48,    92,    91,    35,
      92,    -1,    37,    48,    92,    53,    87,    54,    -1,    37,
      48,    92,    53,    87,    54,    53,    88,    54,    -1,     7,
      55,    70,    56,    53,    89,    54,    -1,    53,    96,    54,
      -1,    57,    96,    58,    -1,    53,    94,    54,    -1,    57,
      94,    58,    -1,    94,    95,    -1,    -1,    85,    -1,    99,
      -1,   100,    -1,    42,    35,    -1,    42,    39,    -1,    44,
     102,    -1,    20,   102,    -1,    96,    98,    -1,    -1,    97,
     100,    -1,    -1,    99,    -1,   100,    -1,    20,   102,    -1,
      42,    35,    -1,    42,    39,    -1,    44,   102,    -1,     9,
     102,    -1,    10,   102,    -1,    12,   102,    -1,    13,   102,
      -1,    11,   102,    -1,    22,   102,   102,    -1,    21,   101,
      -1,    23,   102,    -1,    24,   102,    -1,    25,   102,    -1,
      26,   102,    -1,    27,   102,    -1,    23,   102,    59,    -1,
      24,   102,    59,    -1,    25,   102,    59,    -1,    26,   102,
      59,    -1,    27,   102,    59,    -1,    28,   102,    -1,    29,
     102,    -1,    30,   102,    -1,    31,   102,    -1,    32,   102,
      -1,   101,   102,    -1,   102,    -1,    37,    -1,    46,    37,
      -1,    47,    37,    -1,    55,   103,    56,    -1,   104,    -1,
      37,    -1,   104,    -1,   103,    45,   103,    -1,   103,    47,
     103,    -1,   103,    46,   103,    -1,   103,    48,   103,    -1,
     103,    49,   103,    -1,    46,   103,    -1,    47,   103,    -1,
     103,    52,   103,    -1,    55,   103,    56,    -1,    35,    55,
      56,    -1,    35,    55,   103,    56,    -1,    35,    -1,    60,
      37,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  CfdgParser::yyprhs_[] =
  {
         0,     0,     3,     6,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    28,    31,    34,    39,    42,    45,
      50,    54,    56,    60,    61,    69,    76,    83,    86,    87,
      92,    98,   105,   108,   112,   114,   118,   119,   122,   123,
     128,   129,   138,   139,   147,   150,   153,   156,   159,   162,
     165,   168,   169,   172,   173,   176,   177,   180,   181,   184,
     185,   192,   199,   209,   217,   221,   225,   229,   233,   236,
     237,   239,   241,   243,   246,   249,   252,   255,   258,   259,
     262,   263,   265,   267,   270,   273,   276,   279,   282,   285,
     288,   291,   294,   298,   301,   304,   307,   310,   313,   316,
     320,   324,   328,   332,   336,   339,   342,   345,   348,   351,
     354,   356,   358,   361,   364,   368,   370,   372,   374,   378,
     382,   386,   390,   394,   397,   400,   404,   408,   412,   417,
     419
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  CfdgParser::yyrline_[] =
  {
         0,   128,   128,   129,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   145,   150,   157,   163,   174,   185,   196,
     200,   208,   215,   226,   226,   239,   251,   266,   267,   271,
     275,   282,   307,   319,   327,   334,   335,   339,   347,   351,
     361,   361,   395,   395,   437,   441,   445,   449,   453,   457,
     463,   464,   468,   469,   473,   474,   478,   479,   483,   493,
     493,   517,   524,   531,   538,   544,   552,   556,   562,   566,
     570,   572,   574,   576,   581,   586,   590,   599,   603,   607,
     611,   615,   617,   619,   623,   630,   637,   646,   650,   654,
     658,   662,   666,   671,   677,   681,   685,   690,   694,   698,
     702,   706,   711,   715,   719,   723,   727,   731,   735,   741,
     749,   755,   757,   759,   761,   763,   767,   769,   771,   773,
     775,   777,   779,   781,   783,   785,   787,   791,   803,   816,
     827
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
	       << " (line " << yylno << "), ";
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
       2,     2,     2,     2,     2,     2,    60,     2,     2,     2,
      55,    56,    48,    47,    45,    46,     2,    49,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    57,     2,    58,    52,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,    59,    54,     2,     2,     2,     2,
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
      50,    51
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int CfdgParser::yyeof_ = 0;
  const int CfdgParser::yylast_ = 413;
  const int CfdgParser::yynnts_ = 44;
  const int CfdgParser::yyempty_ = -2;
  const int CfdgParser::yyfinal_ = 2;
  const int CfdgParser::yyterror_ = 1;
  const int CfdgParser::yyerrcode_ = 256;
  const int CfdgParser::yyntokens_ = 61;

  const unsigned int CfdgParser::yyuser_token_number_max_ = 301;
  const CfdgParser::token_number_type CfdgParser::yyundef_token_ = 2;

} // namespace yy

#line 839 "../../src-common/cfdg.ypp"


void yy::CfdgParser::error(const CfdgParser::location_type& l, const std::string& m)
{
    AbstractSystem::SourceRange errLoc(driver.m_currentPath, 
                                       l.begin.line, l.begin.column, 
                                       l.end.line, l.end.column);
    driver.error(errLoc, m);
}

