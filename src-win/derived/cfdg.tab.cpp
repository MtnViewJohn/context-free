// A Bison parser, made by GNU Bison 2.7.90.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.
// //                    "%code top" blocks.
#line 80 "../../src-common/cfdg.ypp" // lalr1.cc:391

#include "astreplacement.h"
#include "astexpression.h"
#define USE(VALUE) /*empty*/
    
    using namespace AST;

#line 42 "cfdg.tab.cpp" // lalr1.cc:391


// First part of user declarations.

#line 47 "cfdg.tab.cpp" // lalr1.cc:398

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

#include "cfdg.tab.hpp"

// User implementation prologue.

#line 61 "cfdg.tab.cpp" // lalr1.cc:406


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
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


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 147 "cfdg.tab.cpp" // lalr1.cc:473

  /// Build a parser object.
  CfdgParser::CfdgParser (class Builder& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  CfdgParser::~CfdgParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  CfdgParser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  CfdgParser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  CfdgParser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  CfdgParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  CfdgParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  CfdgParser::basic_symbol<Base>::~basic_symbol ()
  {
  }

  template <typename Base>
  inline
  void
  CfdgParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  CfdgParser::by_type::by_type ()
     : type (empty)
  {}

  inline
  CfdgParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  CfdgParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  CfdgParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
  CfdgParser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  CfdgParser::by_state::by_state ()
    : state (empty)
  {}

  inline
  CfdgParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  CfdgParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  CfdgParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  CfdgParser::symbol_number_type
  CfdgParser::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
  CfdgParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  CfdgParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty;
  }

  inline
  CfdgParser::stack_symbol_type&
  CfdgParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  CfdgParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 26: // USER_STRING

#line 162 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.string); }
#line 328 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 29: // USER_FILENAME

#line 162 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.string); }
#line 335 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 30: // USER_QSTRING

#line 162 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.string); }
#line 342 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 31: // USER_ARRAYNAME

#line 162 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.string); }
#line 349 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 36: // USER_PATHOP

#line 162 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.string); }
#line 356 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 72: // statement

#line 170 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.component); }
#line 363 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 73: // statement_v2

#line 170 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.component); }
#line 370 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 79: // fileString

#line 162 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.string); }
#line 377 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 80: // fileNameSpace

#line 162 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.string); }
#line 384 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 81: // initialization

#line 170 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.component); }
#line 391 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 82: // initialization_v2

#line 170 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.component); }
#line 398 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 83: // directive_v2

#line 170 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.component); }
#line 405 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 84: // directive_string

#line 163 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { }
#line 412 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 85: // global_definition

#line 164 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.defObj); }
#line 419 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 86: // function_definition_header

#line 164 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.defObj); }
#line 426 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 87: // global_definition_header

#line 164 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.defObj); }
#line 433 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 88: // definition_header

#line 164 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.defObj); }
#line 440 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 89: // definition

#line 164 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.defObj); }
#line 447 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 91: // shape_singleton_header

#line 171 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { driver.pop_repContainer(nullptr); delete (yysym.value.ruleObj); }
#line 454 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 92: // shape_singleton

#line 170 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.component); }
#line 461 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 93: // rule_header_v2

#line 174 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { driver.pop_repContainer(nullptr); delete (yysym.value.ruleObj); }
#line 468 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 95: // rule_header

#line 173 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { driver.pop_repContainer(nullptr); delete (yysym.value.ruleObj); }
#line 475 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 96: // path_header

#line 173 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { driver.pop_repContainer(nullptr); delete (yysym.value.ruleObj); }
#line 482 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 97: // rule

#line 170 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.component); }
#line 489 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 98: // path

#line 170 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.component); }
#line 496 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 99: // path_header_v2

#line 174 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { driver.pop_repContainer(nullptr); delete (yysym.value.ruleObj); }
#line 503 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 105: // parameter_spec

#line 165 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.expression); }
#line 510 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 108: // pathOp_simple_v2

#line 172 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.component); }
#line 517 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 109: // element_simple

#line 170 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.component); }
#line 524 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 114: // element

#line 170 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.component); }
#line 531 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 117: // pathOp_v2

#line 172 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.component); }
#line 538 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 119: // element_loop

#line 169 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { driver.pop_repContainer(nullptr); delete (yysym.value.loopObj); }
#line 545 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 122: // replacement_simple_v2

#line 172 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.component); }
#line 552 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 123: // replacement_v2

#line 172 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.component); }
#line 559 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 124: // loopHeader_v2

#line 168 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { driver.pop_repContainer(nullptr); delete (yysym.value.loopObj); }
#line 566 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 126: // loopHeader

#line 169 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { driver.pop_repContainer(nullptr); delete (yysym.value.loopObj); }
#line 573 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 127: // ifHeader

#line 175 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { driver.pop_repContainer(nullptr); delete (yysym.value.ifObj); }
#line 580 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 128: // ifElseHeader

#line 175 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { driver.pop_repContainer(nullptr); delete (yysym.value.ifObj); }
#line 587 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 129: // transHeader

#line 171 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { driver.pop_repContainer(nullptr); delete (yysym.value.component); }
#line 594 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 130: // switchHeader

#line 176 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.switchObj); }
#line 601 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 131: // caseHeader

#line 177 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { driver.pop_repContainer(nullptr); }
#line 608 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 132: // modification_v2

#line 167 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.mod); }
#line 615 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 133: // modification

#line 167 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.mod); }
#line 622 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 134: // buncha_adjustments

#line 167 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.mod); }
#line 629 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 135: // adjustment

#line 166 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.term); }
#line 636 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 136: // letHeader

#line 178 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { driver.pop_repContainer(nullptr); delete (yysym.value.bodyObj); }
#line 643 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 137: // letBody

#line 165 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.expression); }
#line 650 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 140: // explist

#line 165 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.expression); }
#line 657 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 141: // arglist

#line 165 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.expression); }
#line 664 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 142: // exp

#line 165 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.expression); }
#line 671 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 143: // exp2

#line 165 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.expression); }
#line 678 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 144: // exp3

#line 165 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.expression); }
#line 685 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 145: // expfunc

#line 165 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.expression); }
#line 692 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 146: // exp2func

#line 165 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.expression); }
#line 699 "cfdg.tab.cpp" // lalr1.cc:601
        break;

      case 147: // shapeName

#line 162 "../../src-common/cfdg.ypp" // lalr1.cc:601
        { delete (yysym.value.string); }
#line 706 "cfdg.tab.cpp" // lalr1.cc:601
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  CfdgParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  CfdgParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  CfdgParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  CfdgParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
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
#endif // YYDEBUG

  inline CfdgParser::state_type
  CfdgParser::yy_lr_goto_state_ (state_type yystate, int yylhs)
  {
    int yyr = yypgoto_[yylhs - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yylhs - yyntokens_];
  }

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
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// $$ and @$.
    stack_symbol_type yylhs;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULL, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, driver));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Discard the token being shifted.
    yyempty = true;

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
    /* If YYLEN is nonzero, implement the default value of the action:
       '$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYLHS.VALUE to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yylhs.value = yystack_[yylen - 1].value;
    else
      yylhs.value = yystack_[0].value;

    // Compute the default @$.
    {
      slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
      YYLLOC_DEFAULT (yylhs.location, slice, yylen);
    }

    // Perform the reduction.
    YY_REDUCE_PRINT (yyn);
    try
      {
        switch (yyn)
          {
  case 4:
#line 196 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            if ((yystack_[0].value.component)) {
                driver.push_rep((yystack_[0].value.component), true);
            }
        }
#line 952 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 6:
#line 205 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            if ((yystack_[0].value.component)) {
                driver.push_rep((yystack_[0].value.component), true);
            }
        }
#line 962 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 9:
#line 215 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.component) = nullptr; }
#line 968 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 10:
#line 216 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.component) = nullptr; }
#line 974 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 13:
#line 219 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.component) = nullptr; }
#line 980 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 15:
#line 221 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.component) = static_cast<ASTreplacement*>((yystack_[0].value.defObj)); }
#line 986 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 16:
#line 222 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            error(yystack_[0].location, "Illegal mixture of old and new elements");
            (yylhs.value.component) = nullptr;
        }
#line 995 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 19:
#line 231 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.component) = nullptr; }
#line 1001 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 20:
#line 232 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.component) = nullptr; }
#line 1007 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 23:
#line 235 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            if (driver.lexer->maybeVersion == token::CFDG2) {
                error(yystack_[0].location, "Illegal mixture of old and new elements");
            } else {
                driver.lexer->maybeVersion = token::CFDG3;
            }
            (yylhs.value.component) = nullptr;
            YYABORT;
        }
#line 1021 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 24:
#line 247 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[1].value.string); }
#line 1027 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 25:
#line 248 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {}
#line 1033 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 26:
#line 249 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {}
#line 1039 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 27:
#line 250 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[1].value.string); }
#line 1045 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 28:
#line 251 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[2].value.string); delete (yystack_[1].value.string); }
#line 1051 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 31:
#line 254 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[1].value.string); }
#line 1057 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 32:
#line 255 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[1].value.string); }
#line 1063 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 33:
#line 256 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[1].value.string); }
#line 1069 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 34:
#line 257 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[1].value.string); }
#line 1075 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 35:
#line 261 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[0].value.mod); }
#line 1081 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 36:
#line 262 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[0].value.mod); }
#line 1087 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 37:
#line 263 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[0].value.mod); }
#line 1093 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 38:
#line 264 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[0].value.string); }
#line 1099 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 39:
#line 265 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[0].value.ruleObj); }
#line 1105 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 40:
#line 269 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr file((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(nullptr);
            driver.IncludeFile(*file);
        }
#line 1116 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 41:
#line 278 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr file((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            str_ptr nm((yystack_[1].value.string)); (yystack_[1].value.string) = nullptr;
            driver.SetShape(nullptr);
            driver.IncludeFile(*file);
            if (nm)
                driver.PushNameSpace(std::move(nm), yystack_[1].location);
        }
#line 1129 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 42:
#line 289 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            if (driver.EndInclude())
                YYACCEPT;
        }
#line 1138 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 45:
#line 299 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.string) = (yystack_[0].value.string); }
#line 1144 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 46:
#line 300 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.string) = nullptr; }
#line 1150 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 47:
#line 304 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr name((yystack_[2].value.string));   (yystack_[2].value.string) = nullptr;
            exp_ptr p((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            driver.SetShape(nullptr);
            ASTdefine* cfg = driver.MakeDefinition(CFDG::ParamNames[CFG::StartShape], yylhs.location, false);
            if (cfg)
                cfg->mExpression.reset(driver.MakeRuleSpec(*name, std::move(p), yystack_[2].location, std::move(mod), true));
            (yylhs.value.component) = cfg;
        }
#line 1165 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 48:
#line 315 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr name((yystack_[1].value.string));   (yystack_[1].value.string) = nullptr;
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            driver.SetShape(nullptr);
            ASTdefine* cfg = driver.MakeDefinition(CFDG::ParamNames[CFG::StartShape], yylhs.location, false);
            if (cfg)
                cfg->mExpression.reset(driver.MakeRuleSpec(*name, nullptr, yystack_[1].location, std::move(mod), true));
            (yylhs.value.component) = cfg;
        }
#line 1179 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 49:
#line 325 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr name((yystack_[1].value.string));   (yystack_[1].value.string) = nullptr;
            exp_ptr p((yystack_[0].value.expression)); (yystack_[0].value.expression) = nullptr;
            driver.SetShape(nullptr);
            ASTdefine* cfg = driver.MakeDefinition(CFDG::ParamNames[CFG::StartShape], yylhs.location, false);
            if (cfg)
                cfg->mExpression.reset(driver.MakeRuleSpec(*name, std::move(p), yystack_[1].location, nullptr, true));
            (yylhs.value.component) = cfg;
        }
#line 1193 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 50:
#line 337 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr name((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            driver.SetShape(nullptr);
            ASTdefine* cfg = driver.MakeDefinition(CFDG::ParamNames[CFG::StartShape], yylhs.location, false);
            if (cfg)
                cfg->mExpression.reset(driver.MakeRuleSpec(*name, nullptr, yystack_[0].location, nullptr, true));
            (yylhs.value.component) = cfg;
        }
#line 1206 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 51:
#line 348 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            exp_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            ASTdefine* cfg = driver.MakeDefinition(*(yystack_[1].value.cstring), yylhs.location, false);
            if (cfg)
                cfg->mExpression = std::move(mod);
            driver.lexer->maybeVersion = token::CFDG2;
            (yylhs.value.component) = cfg;
        }
#line 1219 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 52:
#line 359 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.cstring) = &CFDG::ParamNames[CFG::Background]; }
#line 1225 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 53:
#line 361 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.cstring) = &CFDG::ParamNames[CFG::Tile]; }
#line 1231 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 54:
#line 363 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            switch ((yystack_[0].value.modToken)) {
            case ASTmodTerm::size:
                (yylhs.value.cstring) = &CFDG::ParamNames[CFG::Size];
                break;
            case ASTmodTerm::time:
                (yylhs.value.cstring) = &CFDG::ParamNames[CFG::Time];
                break;
            default:
                (yylhs.value.cstring) = &CFDG::ParamNames[CFG::Size];
                error(yystack_[0].location, "Syntax error");
                break;
            }
        }
#line 1250 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 55:
#line 380 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            def_ptr var((yystack_[1].value.defObj));  (yystack_[1].value.defObj) = nullptr;
            exp_ptr exp((yystack_[0].value.expression));                      (yystack_[0].value.expression) = nullptr;
            if (var) {
                switch (var->mDefineType) {
                    case ASTdefine::StackDefine:
                        if (ASTmodification* mod = dynamic_cast<ASTmodification*>(exp.get()))
                            var->mChildChange.grab(mod);        // emptied ASTmod gets deleted
                        else
                            var->mExpression = std::move(exp);
                        break;
                    case ASTdefine::LetDefine:
                        assert(false);
                        break;
                    case ASTdefine::FunctionDefine:
                        driver.pop_repContainer(nullptr);
                        driver.mParamDecls.mParameters.clear();
                        driver.mParamDecls.mStackCount = 0;
                        // fall through
                    default:
                        var->mExpression = std::move(exp);
                        break;
                }
                (yylhs.value.defObj) = var.release();
            } else {
                (yylhs.value.defObj) = nullptr;
            }
        }
#line 1283 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 56:
#line 411 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr name((yystack_[2].value.string)); (yystack_[2].value.string) = nullptr;
            (yylhs.value.defObj) = driver.MakeDefinition(*name, yylhs.location, true);
            if ((yylhs.value.defObj)) {
                (yylhs.value.defObj)->mType = RuleType;
                (yylhs.value.defObj)->mTuplesize = 1;
            }
        }
#line 1296 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 57:
#line 420 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr name((yystack_[2].value.string)); (yystack_[2].value.string) = nullptr;
            (yylhs.value.defObj) = driver.MakeDefinition(*name, yylhs.location, true);
            if ((yylhs.value.defObj)) {
                (yylhs.value.defObj)->mType = NumericType;
                (yylhs.value.defObj)->mTuplesize = 1;
            }
        }
#line 1309 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 58:
#line 429 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr type((yystack_[3].value.string)); (yystack_[3].value.string) = nullptr;
            str_ptr name((yystack_[2].value.string)); (yystack_[2].value.string) = nullptr;
            (yylhs.value.defObj) = driver.MakeDefinition(*name, yylhs.location, true);
            if ((yylhs.value.defObj))
                (yylhs.value.defObj)->mType = AST::decodeType(*type, (yylhs.value.defObj)->mTuplesize, 
                                                                     (yylhs.value.defObj)->isNatural, yystack_[3].location);
        }
#line 1322 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 59:
#line 438 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            error(yystack_[2].location, "Reserved keyword: adjustment");
            (yylhs.value.defObj) = nullptr;
        }
#line 1331 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 60:
#line 443 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            error(yystack_[2].location, "Reserved keyword: adjustment");
            (yylhs.value.defObj) = nullptr;
        }
#line 1340 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 61:
#line 448 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr type((yystack_[3].value.string)); (yystack_[3].value.string) = nullptr;
            error(yystack_[2].location, "Reserved keyword: adjustment");
            (yylhs.value.defObj) = nullptr;
        }
#line 1350 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 62:
#line 456 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            if ((yystack_[0].value.defObj)) {
                assert((yystack_[0].value.defObj)->mDefineType == ASTdefine::FunctionDefine);
                driver.push_repContainer(driver.mParamDecls);
            } else {
                // An error occurred
                driver.mParamDecls.mParameters.clear();
                driver.mParamDecls.mStackCount = 0;
            }
            (yylhs.value.defObj) = (yystack_[0].value.defObj);
        }
#line 1366 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 63:
#line 468 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.defObj) = (yystack_[0].value.defObj);
        }
#line 1374 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 64:
#line 474 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr name((yystack_[1].value.string)); (yystack_[1].value.string) = nullptr;
            (yylhs.value.defObj) = driver.MakeDefinition(*name, yylhs.location, false);
        }
#line 1383 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 65:
#line 478 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            error(yystack_[1].location, "Reserved keyword: adjustment");
            (yylhs.value.defObj) = nullptr;
        }
#line 1392 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 66:
#line 485 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            def_ptr var((yystack_[1].value.defObj));  (yystack_[1].value.defObj) = nullptr;
            exp_ptr exp((yystack_[0].value.expression));               (yystack_[0].value.expression) = nullptr;
            if (var) {
                if (ASTmodification* mod = dynamic_cast<ASTmodification*>(exp.get())) {
                    mod->modData.mRand64Seed.seed(0);
                    var->mChildChange.grab(mod);
                } else {
                    var->mExpression = std::move(exp);
                }
                (yylhs.value.defObj) = var.release();
            } else {
                (yylhs.value.defObj) = nullptr;
            }
        }
#line 1412 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 67:
#line 503 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr name((yystack_[1].value.string)); (yystack_[1].value.string) = nullptr;
            driver.SetShape(name.get(), yystack_[1].location);
        }
#line 1421 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 68:
#line 510 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.mInPathContainer = false;
            (yylhs.value.ruleObj) = new ASTrule(-1, yystack_[1].location);
            driver.AddRule((yylhs.value.ruleObj));
            driver.push_repContainer((yylhs.value.ruleObj)->mRuleBody);
        }
#line 1432 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 69:
#line 518 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.component) = (yystack_[2].value.ruleObj);
            driver.pop_repContainer((yystack_[2].value.ruleObj));
            driver.mInPathContainer = false;
        }
#line 1442 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 70:
#line 526 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr name((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            driver.SetShape(nullptr);
            (yylhs.value.ruleObj) = new ASTrule(driver.StringToShape(*name, yystack_[0].location, false), yylhs.location);
            driver.AddRule((yylhs.value.ruleObj));
            driver.push_repContainer((yylhs.value.ruleObj)->mRuleBody);
        }
#line 1454 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 71:
#line 534 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr name((yystack_[1].value.string));    (yystack_[1].value.string) = nullptr;
            str_ptr weight((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            driver.SetShape(nullptr);
            (yylhs.value.ruleObj) = new ASTrule(driver.StringToShape(*name, yystack_[1].location, false), 
                                          CFatof(weight->c_str()),
                                          weight->find_first_of('%')  != std::string::npos,
                                          yylhs.location);
            driver.AddRule((yylhs.value.ruleObj));
            driver.push_repContainer((yylhs.value.ruleObj)->mRuleBody);
        }
#line 1470 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 72:
#line 548 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.lexer->maybeVersion = token::CFDG2;
            (yylhs.value.component) = (yystack_[3].value.ruleObj);
            driver.pop_repContainer((yystack_[3].value.ruleObj));
        }
#line 1480 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 73:
#line 556 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.mInPathContainer = false;
            (yylhs.value.ruleObj) = new ASTrule(-1, yystack_[0].location);
            driver.AddRule((yylhs.value.ruleObj));
            driver.push_repContainer((yylhs.value.ruleObj)->mRuleBody);
        }
#line 1491 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 74:
#line 563 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.mInPathContainer = false;
            str_ptr weight((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            (yylhs.value.ruleObj) = new ASTrule(-1, CFatof(weight->c_str()),
                                       weight->find_first_of('%')  != std::string::npos,
                                       yylhs.location);
            driver.AddRule((yylhs.value.ruleObj));
            driver.push_repContainer((yylhs.value.ruleObj)->mRuleBody);
        }
#line 1505 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 75:
#line 575 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr name((yystack_[1].value.string)); (yystack_[1].value.string) = nullptr;
            driver.SetShape(name.get(), yystack_[1].location, true);
            driver.mInPathContainer = true;
            (yylhs.value.ruleObj) = new ASTrule(-1, yylhs.location);
            (yylhs.value.ruleObj)->isPath = true;
            driver.AddRule((yylhs.value.ruleObj));
            driver.push_repContainer((yylhs.value.ruleObj)->mRuleBody);
        }
#line 1519 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 76:
#line 587 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.component) = (yystack_[3].value.ruleObj);
            driver.pop_repContainer((yystack_[3].value.ruleObj));
            driver.mInPathContainer = false;
        }
#line 1529 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 77:
#line 595 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.component) = (yystack_[3].value.ruleObj);
            driver.pop_repContainer((yystack_[3].value.ruleObj));
            driver.mInPathContainer = false;
            driver.SetShape(nullptr);
        }
#line 1540 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 78:
#line 604 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr name((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            driver.SetShape(nullptr);
            (yylhs.value.ruleObj) = new ASTrule(driver.StringToShape(*name, yystack_[0].location, false), yylhs.location);
            (yylhs.value.ruleObj)->isPath = true;
            driver.AddRule((yylhs.value.ruleObj));
            driver.push_repContainer((yylhs.value.ruleObj)->mRuleBody);
            driver.mInPathContainer = true;
        }
#line 1554 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 79:
#line 616 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.component) = (yystack_[3].value.ruleObj);
            driver.pop_repContainer((yystack_[3].value.ruleObj));
        }
#line 1563 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 80:
#line 623 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr type((yystack_[1].value.string)); (yystack_[1].value.string) = nullptr;
            str_ptr var((yystack_[0].value.string));  (yystack_[0].value.string) = nullptr;
            driver.NextParameterDecl(*type, *var, yystack_[1].location, yystack_[0].location);
        }
#line 1573 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 81:
#line 629 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            static std::string shapeStr("shape");
            str_ptr var((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            driver.NextParameterDecl(shapeStr, *var, yystack_[1].location, yystack_[0].location);
        }
#line 1583 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 82:
#line 635 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            delete (yystack_[1].value.string);
            error(yystack_[0].location, "Reserved keyword: adjustment");
        }
#line 1592 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 83:
#line 640 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            error(yystack_[0].location, "Reserved keyword: adjustment");
        }
#line 1600 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 84:
#line 644 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            static const std::string numtype("number");
            str_ptr var((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            driver.NextParameterDecl(numtype, *var, yystack_[0].location, yystack_[0].location);
        }
#line 1610 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 85:
#line 650 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            error(yystack_[0].location, "Reserved keyword: adjustment");
        }
#line 1618 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 92:
#line 671 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = (yystack_[1].value.expression);}
#line 1624 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 93:
#line 672 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASTexpression(yylhs.location, false, false, AST::ReuseType); }
#line 1630 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 94:
#line 673 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = nullptr; }
#line 1636 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 95:
#line 674 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = nullptr; }
#line 1642 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 96:
#line 678 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.push_rep((yystack_[0].value.component));
        }
#line 1650 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 98:
#line 685 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.push_rep((yystack_[0].value.component));
        }
#line 1658 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 100:
#line 692 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr pop((yystack_[3].value.string));        (yystack_[3].value.string) = nullptr;
            mod_ptr mod((yystack_[1].value.mod)); (yystack_[1].value.mod) = nullptr;
            driver.lexer->maybeVersion = token::CFDG2;
            (yylhs.value.component) = new ASTpathOp(*pop, std::move(mod), yylhs.location);
        }
#line 1669 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 101:
#line 699 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr cmd((yystack_[1].value.string)); (yystack_[1].value.string) = nullptr;
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            driver.lexer->maybeVersion = token::CFDG2;
            (yylhs.value.component) = new ASTpathCommand(*cmd, std::move(mod), nullptr, yylhs.location);
        }
#line 1680 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 102:
#line 708 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr pop((yystack_[3].value.string)); (yystack_[3].value.string) = nullptr;
            exp_ptr mod((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            (yylhs.value.component) = new ASTpathOp(*pop, std::move(mod), yylhs.location);
        }
#line 1690 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 103:
#line 714 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr pop((yystack_[2].value.string)); (yystack_[2].value.string) = nullptr;
            exp_ptr mod;
            (yylhs.value.component) = new ASTpathOp(*pop, std::move(mod), yylhs.location);
        }
#line 1700 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 104:
#line 720 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr cmd((yystack_[2].value.string));    (yystack_[2].value.string) = nullptr;
            exp_ptr p((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            (yylhs.value.component) = driver.MakeElement(*cmd, std::move(mod),
                                                 std::move(p), yylhs.location, false);
        }
#line 1712 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 105:
#line 728 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { 
            exp_ptr args((yystack_[2].value.expression));        (yystack_[2].value.expression) = nullptr;
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            str_ptr func(new std::string("if"));
            args.reset(driver.MakeFunction(std::move(func), std::move(args), yystack_[4].location, yystack_[2].location, false));
            static const std::string ifstr("if");
            (yylhs.value.component) = driver.MakeElement(ifstr, std::move(mod), std::move(args), yylhs.location, false);
        }
#line 1725 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 106:
#line 737 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.pop_repContainer(nullptr);
            cont_ptr vars((yystack_[2].value.bodyObj));  (yystack_[2].value.bodyObj) = nullptr;
            exp_ptr exp((yystack_[1].value.expression));      (yystack_[1].value.expression) = nullptr;
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            exp.reset(driver.MakeLet(yystack_[2].location, std::move(vars), std::move(exp)));      // must do unconditionally
            static const std::string letstr("let");
            (yylhs.value.component) = driver.MakeElement(letstr, std::move(mod), std::move(exp), yylhs.location, false);
        }
#line 1739 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 107:
#line 747 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr cmd((yystack_[2].value.string));    (yystack_[2].value.string) = nullptr;
            exp_ptr p((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            (yylhs.value.component) = driver.MakeElement(*cmd, std::move(mod), std::move(p), yylhs.location, true);
        }
#line 1750 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 108:
#line 756 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { }
#line 1756 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 109:
#line 758 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.push_rep((yystack_[0].value.component));
        }
#line 1764 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 110:
#line 764 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { }
#line 1770 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 111:
#line 766 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.push_rep((yystack_[0].value.component));
        }
#line 1778 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 114:
#line 777 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.pop_repContainer(driver.switchStack.top());
            USE((yystack_[1].value.modToken));
        }
#line 1787 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 115:
#line 784 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { 
            (yylhs.value.component) = (yystack_[0].value.component);
        }
#line 1795 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 116:
#line 788 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.component) = (yystack_[0].value.defObj);
        }
#line 1803 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 117:
#line 792 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.component) = (yystack_[0].value.loopObj);
            driver.pop_repContainer((yystack_[0].value.loopObj));
            if ((yystack_[0].value.loopObj)->mRepType == 0) {
                delete (yystack_[0].value.loopObj);
                (yylhs.value.component) = nullptr;
            }
        }
#line 1816 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 118:
#line 801 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.pop_repContainer((yystack_[1].value.loopObj));
            driver.push_repContainer((yystack_[1].value.loopObj)->mFinallyBody);
        }
#line 1825 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 119:
#line 804 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.pop_repContainer((yystack_[3].value.loopObj));
            (yylhs.value.component) = (yystack_[3].value.loopObj);
            if ((yystack_[3].value.loopObj)->mRepType == 0) {
                delete (yystack_[3].value.loopObj);
                (yylhs.value.component) = nullptr;
            }
        }
#line 1838 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 120:
#line 813 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.component) = (yystack_[1].value.ifObj);
            driver.pop_repContainer((yystack_[1].value.ifObj));
            if ((yystack_[1].value.ifObj)->mRepType == 0) {
                delete (yystack_[1].value.ifObj);
                (yylhs.value.component) = nullptr;
            }
        }
#line 1851 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 121:
#line 822 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.component) = (yystack_[1].value.ifObj);
            driver.pop_repContainer((yystack_[1].value.ifObj));
            if ((yystack_[1].value.ifObj)->mRepType == 0) {
                delete (yystack_[1].value.ifObj);
                (yylhs.value.component) = nullptr;
            }
        }
#line 1864 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 122:
#line 831 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.component) = (yystack_[1].value.component);
            driver.pop_repContainer((yystack_[1].value.component));
            if ((yystack_[1].value.component)->mRepType == 0) {
                delete (yystack_[1].value.component);
                (yylhs.value.component) = nullptr;
            }
        }
#line 1877 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 123:
#line 841 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.component) = (yystack_[3].value.switchObj);
            (yystack_[3].value.switchObj)->unify();
            driver.switchStack.pop();
        }
#line 1887 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 124:
#line 847 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            error(yystack_[0].location, "Illegal mixture of old and new elements");
            (yylhs.value.component) = nullptr;
        }
#line 1896 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 125:
#line 854 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[1].value.string); }
#line 1902 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 126:
#line 855 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[1].value.string); }
#line 1908 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 127:
#line 856 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[1].value.string); }
#line 1914 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 128:
#line 860 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.component) = (yystack_[0].value.component); }
#line 1920 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 129:
#line 862 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.component) = (yystack_[1].value.loopObj);
            driver.pop_repContainer((yystack_[1].value.loopObj));
            if ((yystack_[1].value.loopObj)->mRepType == 0) {
                delete (yystack_[1].value.loopObj);
                (yylhs.value.component) = nullptr;
            }
        }
#line 1933 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 130:
#line 870 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            if (driver.lexer->maybeVersion == token::CFDG2) {
                error(yystack_[0].location, "Illegal mixture of old and new elements");
            } else {
                driver.lexer->maybeVersion = token::CFDG3;
            }
            (yylhs.value.component) = nullptr;
            YYABORT;
        }
#line 1947 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 131:
#line 882 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[1].value.string); }
#line 1953 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 132:
#line 883 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[1].value.string); }
#line 1959 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 135:
#line 886 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { delete (yystack_[1].value.string); }
#line 1965 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 140:
#line 894 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            // parse loop mod and loop body with loop index in scope
            (yystack_[2].value.loopObj)->mLoopModHolder.reset((yystack_[1].value.mod)); (yystack_[1].value.mod) = nullptr;
            (yylhs.value.loopObj) = (yystack_[2].value.loopObj);
            // loopmod gets deleted
        }
#line 1976 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 141:
#line 903 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.push_rep((yystack_[0].value.component));
        }
#line 1984 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 143:
#line 910 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { }
#line 1990 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 144:
#line 912 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.push_rep((yystack_[0].value.component));
        }
#line 1998 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 145:
#line 918 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr name((yystack_[1].value.string)); (yystack_[1].value.string) = nullptr;
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, nullptr, yystack_[1].location));
            (yylhs.value.component) = new ASTreplacement(std::move(*r), std::move(mod), yylhs.location);
        }
#line 2009 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 146:
#line 927 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.component) = (yystack_[0].value.component); }
#line 2015 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 147:
#line 929 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.component) = (yystack_[1].value.loopObj);
            driver.pop_repContainer((yystack_[1].value.loopObj));
            if ((yystack_[1].value.loopObj)->mRepType == 0) {
                delete (yystack_[1].value.loopObj);
                (yylhs.value.component) = nullptr;
            }
        }
#line 2028 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 148:
#line 940 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { ++driver.mLocalStackDepth; }
#line 2034 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 149:
#line 940 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr cstr((yystack_[3].value.string)); (yystack_[3].value.string) = nullptr;
            exp_ptr count(new ASTreal(*cstr, yystack_[3].location));
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            static const std::string dummyvar("~~inaccessiblevar~~");
            --driver.mLocalStackDepth;
            driver.lexer->maybeVersion = token::CFDG2;
            (yylhs.value.loopObj) = new ASTloop(driver.StringToShape(dummyvar, yystack_[3].location, false),
                                         dummyvar, yystack_[3].location, std::move(count), 
                                         yylhs.location, std::move(mod));
            driver.push_repContainer((yylhs.value.loopObj)->mLoopBody);
        }
#line 2051 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 150:
#line 955 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr var((yystack_[2].value.string)); (yystack_[2].value.string) = nullptr;
            exp_ptr index((yystack_[0].value.expression));   (yystack_[0].value.expression) = nullptr;
            int nameIndex = driver.StringToShape(*var, yystack_[2].location, false);
            (yylhs.value.loopObj) = new ASTloop(nameIndex, *var, yystack_[2].location, std::move(index), yystack_[0].location, nullptr);
            driver.push_repContainer((yylhs.value.loopObj)->mLoopBody);
        }
#line 2063 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 151:
#line 963 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            exp_ptr index((yystack_[0].value.expression)); (yystack_[0].value.expression) = nullptr;
            static const std::string dummyvar("~~inaccessiblevar~~");
            (yylhs.value.loopObj) = new ASTloop(driver.StringToShape(dummyvar, yystack_[3].location, false),
                                      dummyvar, yystack_[2].location, std::move(index), yystack_[0].location, nullptr);
            driver.push_repContainer((yylhs.value.loopObj)->mLoopBody);
            error(yystack_[2].location, "Reserved keyword: adjustment");
        }
#line 2076 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 152:
#line 972 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            exp_ptr count((yystack_[0].value.expression)); (yystack_[0].value.expression) = nullptr;
            static const std::string dummyvar("~~inaccessiblevar~~");
            (yylhs.value.loopObj) = new ASTloop(driver.StringToShape(dummyvar, yystack_[1].location, false),
                                      dummyvar, yystack_[1].location, std::move(count), yystack_[0].location, nullptr);
            driver.push_repContainer((yylhs.value.loopObj)->mLoopBody);
        }
#line 2088 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 153:
#line 982 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            exp_ptr cond((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            (yylhs.value.ifObj) = new ASTif(std::move(cond), yystack_[1].location);
            driver.push_repContainer((yylhs.value.ifObj)->mThenBody);
        }
#line 2098 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 154:
#line 990 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.pop_repContainer((yystack_[2].value.ifObj));
            driver.push_repContainer((yystack_[2].value.ifObj)->mElseBody);
            (yylhs.value.ifObj) = (yystack_[2].value.ifObj);
        }
#line 2108 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 155:
#line 998 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            exp_ptr mods((yystack_[0].value.expression)); (yystack_[0].value.expression) = nullptr;
            if ((yystack_[1].value.modToken) != ASTmodTerm::transform)
                error(yystack_[1].location, "Syntax error");
            ASTtransform* trans = new ASTtransform(yylhs.location, std::move(mods));
            driver.push_repContainer(trans->mBody);
            (yylhs.value.component) = trans;
        }
#line 2121 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 156:
#line 1006 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            exp_ptr mods((yystack_[0].value.expression)); (yystack_[0].value.expression) = nullptr;
            ASTtransform* trans = new ASTtransform(yylhs.location, std::move(mods));
            driver.push_repContainer(trans->mBody);
            trans->mClone = true;
            (yylhs.value.component) = trans;
        }
#line 2133 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 157:
#line 1016 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            exp_ptr caseVal((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            (yylhs.value.switchObj) = new ASTswitch(std::move(caseVal), yystack_[1].location);
            driver.switchStack.push((yylhs.value.switchObj));
        }
#line 2143 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 158:
#line 1024 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            exp_ptr valExp((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            
            double val = 0.0;
            try {
                if (valExp->evaluate(&val, 1) != 1) {
                    driver.error(yystack_[1].location, "Case expression is not a single, numeric expression");
                } else {
                    int intval = static_cast<int>(floor(val));
                    ASTswitch::switchMap& caseMap = driver.switchStack.top()->mCaseStatements;
                    
                    if (caseMap.count(intval)) {
                        driver.error(yystack_[1].location, "Case value already in use");
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
                driver.error(yystack_[1].location, "Case expression is not constant");
            }
            (yylhs.value.modToken) = 0;
        }
#line 2175 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 159:
#line 1052 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            if (!driver.switchStack.top()->mElseBody.mBody.empty()) {
                driver.error(yylhs.location, "There can only be one 'else:' clause");
            } else {
                driver.push_repContainer(driver.switchStack.top()->mElseBody);
            }
            (yylhs.value.modToken) = 0;
        }
#line 2188 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 160:
#line 1063 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            mod_ptr mod((yystack_[1].value.mod)); (yystack_[1].value.mod) = nullptr;
            (yylhs.value.mod) = driver.MakeModification(std::move(mod), yylhs.location, true);
        }
#line 2197 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 161:
#line 1068 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            mod_ptr mod((yystack_[1].value.mod)); (yystack_[1].value.mod) = nullptr;
            (yylhs.value.mod) = driver.MakeModification(std::move(mod), yylhs.location, false);
        }
#line 2206 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 162:
#line 1075 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            mod_ptr mod((yystack_[1].value.mod)); (yystack_[1].value.mod) = nullptr;
            (yylhs.value.mod) = driver.MakeModification(std::move(mod), yylhs.location, true);
        }
#line 2215 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 163:
#line 1080 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            mod_ptr mod((yystack_[2].value.mod)); (yystack_[2].value.mod) = nullptr;
            (yylhs.value.mod) = driver.MakeModification(std::move(mod), yylhs.location, false);
        }
#line 2224 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 164:
#line 1087 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            term_ptr mod((yystack_[0].value.term)); (yystack_[0].value.term) = nullptr;
            driver.MakeModTerm((yystack_[1].value.mod)->modExp, std::move(mod));
            (yylhs.value.mod) = (yystack_[1].value.mod);
        }
#line 2234 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 165:
#line 1092 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            static const yy::location def;
            (yylhs.value.mod) = new ASTmodification(def);
        }
#line 2243 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 166:
#line 1099 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.term) = new ASTmodTerm(static_cast<ASTmodTerm::modTypeEnum>((yystack_[1].value.modToken)), (yystack_[0].value.expression), yylhs.location);
        }
#line 2251 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 167:
#line 1103 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            exp_ptr mod((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            if ((yystack_[2].value.modToken) < ASTmodTerm::hue || (yystack_[2].value.modToken) > ASTmodTerm::alpha) {
                error(yylhs.location, "The target operator can only be applied to color adjustments");
                (yylhs.value.term) = nullptr;
            } else {
                (yylhs.value.term) = new ASTmodTerm(static_cast<ASTmodTerm::modTypeEnum>((yystack_[2].value.modToken) + 4), mod.release(), yylhs.location);
            }
        }
#line 2265 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 168:
#line 1113 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr p((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            (yylhs.value.term) = new ASTmodTerm(ASTmodTerm::param, *p, yylhs.location);
        }
#line 2274 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 169:
#line 1118 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr p((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            (yylhs.value.term) = new ASTmodTerm(ASTmodTerm::param, *p, yylhs.location);
        }
#line 2283 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 170:
#line 1125 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.bodyObj) = new ASTrepContainer();
            driver.push_repContainer(*(yylhs.value.bodyObj));
        }
#line 2292 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 171:
#line 1132 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.expression) = (yystack_[1].value.expression);
        }
#line 2300 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 174:
#line 1144 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.push_rep((yystack_[0].value.defObj));
        }
#line 2308 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 175:
#line 1150 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.expression) = ASTexpression::Append((yystack_[1].value.expression), (yystack_[0].value.expression));
        }
#line 2316 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 176:
#line 1154 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { 
            (yylhs.value.expression) = (yystack_[0].value.expression);
        }
#line 2324 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 177:
#line 1161 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.expression) = (yystack_[2].value.expression)->append(new ASTparen((yystack_[0].value.expression)));
        }
#line 2332 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 178:
#line 1165 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            (yylhs.value.expression) = new ASTcons{ new ASTparen((yystack_[0].value.expression)) };
        }
#line 2340 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 179:
#line 1171 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASTreal(*(yystack_[0].value.string), yylhs.location); delete (yystack_[0].value.string); (yystack_[0].value.string) = nullptr; }
#line 2346 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 180:
#line 1173 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASTreal(Renderer::Infinity, yylhs.location); }
#line 2352 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 181:
#line 1175 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASTparen((yystack_[1].value.expression)); }
#line 2358 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 182:
#line 1177 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = (yystack_[0].value.expression); }
#line 2364 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 183:
#line 1179 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('N', (yystack_[0].value.expression), nullptr);; }
#line 2370 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 184:
#line 1181 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('P', (yystack_[0].value.expression), nullptr);; }
#line 2376 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 185:
#line 1183 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            exp_ptr pair((yystack_[2].value.expression)->append((yystack_[0].value.expression))); (yystack_[2].value.expression) = nullptr; (yystack_[0].value.expression) = nullptr;
            (yylhs.value.expression) = new ASTfunction("rand", std::move(pair), driver.mSeed, yystack_[2].location, yylhs.location);
        }
#line 2385 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 186:
#line 1188 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            exp_ptr pair((yystack_[2].value.expression)->append((yystack_[0].value.expression))); (yystack_[2].value.expression) = nullptr; (yystack_[0].value.expression) = nullptr;
            (yylhs.value.expression) = new ASTfunction("rand+/-", std::move(pair), driver.mSeed, yystack_[2].location, yylhs.location);
        }
#line 2394 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 187:
#line 1195 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASTreal(*(yystack_[0].value.string), yylhs.location); delete (yystack_[0].value.string); (yystack_[0].value.string) = nullptr; }
#line 2400 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 188:
#line 1197 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASTreal(Renderer::Infinity, yylhs.location); }
#line 2406 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 189:
#line 1199 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = (yystack_[0].value.expression); }
#line 2412 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 190:
#line 1201 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            exp_ptr pair((yystack_[2].value.expression)->append((yystack_[0].value.expression))); (yystack_[2].value.expression) = nullptr; (yystack_[0].value.expression) = nullptr;
            (yylhs.value.expression) = new ASTfunction("rand", std::move(pair), driver.mSeed, yystack_[2].location, yylhs.location);
        }
#line 2421 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 191:
#line 1206 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            exp_ptr pair((yystack_[2].value.expression)->append((yystack_[0].value.expression))); (yystack_[2].value.expression) = nullptr; (yystack_[0].value.expression) = nullptr;
            (yylhs.value.expression) = new ASTfunction("rand+/-", std::move(pair), driver.mSeed, yystack_[2].location, yylhs.location);
        }
#line 2430 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 192:
#line 1211 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = (yystack_[2].value.expression)->append((yystack_[0].value.expression));   }
#line 2436 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 193:
#line 1213 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('+', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2442 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 194:
#line 1215 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('-', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2448 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 195:
#line 1217 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('_', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2454 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 196:
#line 1219 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('*', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2460 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 197:
#line 1221 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('/', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2466 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 198:
#line 1223 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('N', (yystack_[0].value.expression), nullptr); }
#line 2472 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 199:
#line 1225 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('P', (yystack_[0].value.expression), nullptr); }
#line 2478 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 200:
#line 1227 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('!', (yystack_[0].value.expression), nullptr); }
#line 2484 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 201:
#line 1229 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('^', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2490 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 202:
#line 1231 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('<', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2496 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 203:
#line 1233 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('L', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2502 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 204:
#line 1235 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('>', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2508 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 205:
#line 1237 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('G', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2514 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 206:
#line 1239 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('=', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2520 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 207:
#line 1241 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('n', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2526 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 208:
#line 1243 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('&', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2532 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 209:
#line 1245 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('|', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2538 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 210:
#line 1247 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('X', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2544 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 211:
#line 1249 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASTparen((yystack_[1].value.expression)); }
#line 2550 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 212:
#line 1251 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = (yystack_[0].value.mod); }
#line 2556 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 213:
#line 1255 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASTreal(*(yystack_[0].value.string), yylhs.location); delete (yystack_[0].value.string); (yystack_[0].value.string) = nullptr; }
#line 2562 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 214:
#line 1257 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASTreal(Renderer::Infinity, yylhs.location); }
#line 2568 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 215:
#line 1259 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = (yystack_[0].value.expression); }
#line 2574 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 216:
#line 1261 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            exp_ptr pair((yystack_[2].value.expression)->append((yystack_[0].value.expression))); (yystack_[2].value.expression) = nullptr; (yystack_[0].value.expression) = nullptr;
            (yylhs.value.expression) = new ASTfunction("rand", std::move(pair), driver.mSeed, yystack_[2].location, yylhs.location);
        }
#line 2583 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 217:
#line 1266 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            exp_ptr pair((yystack_[2].value.expression)->append((yystack_[0].value.expression))); (yystack_[2].value.expression) = nullptr; (yystack_[0].value.expression) = nullptr;
            (yylhs.value.expression) = new ASTfunction("rand+/-", std::move(pair), driver.mSeed, yystack_[2].location, yylhs.location);
        }
#line 2592 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 218:
#line 1271 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('+', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2598 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 219:
#line 1273 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('-', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2604 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 220:
#line 1275 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('_', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2610 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 221:
#line 1277 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('*', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2616 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 222:
#line 1279 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('/', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2622 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 223:
#line 1281 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('N', (yystack_[0].value.expression), nullptr); }
#line 2628 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 224:
#line 1283 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('P', (yystack_[0].value.expression), nullptr); }
#line 2634 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 225:
#line 1285 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('!', (yystack_[0].value.expression), nullptr); }
#line 2640 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 226:
#line 1287 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('^', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2646 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 227:
#line 1289 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('<', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2652 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 228:
#line 1291 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('L', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2658 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 229:
#line 1293 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('>', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2664 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 230:
#line 1295 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('G', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2670 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 231:
#line 1297 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('=', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2676 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 232:
#line 1299 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('n', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2682 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 233:
#line 1301 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('&', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2688 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 234:
#line 1303 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('|', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2694 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 235:
#line 1305 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASToperator('X', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2700 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 236:
#line 1307 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = new ASTparen((yystack_[1].value.expression)); }
#line 2706 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 237:
#line 1309 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.expression) = (yystack_[0].value.mod); }
#line 2712 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 238:
#line 1313 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { 
            str_ptr func((yystack_[2].value.string)); (yystack_[2].value.string) = nullptr;
            (yylhs.value.expression) = driver.MakeFunction(std::move(func), nullptr, yystack_[2].location, yystack_[1].location + yystack_[0].location, false);
        }
#line 2721 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 239:
#line 1318 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr func((yystack_[3].value.string)); (yystack_[3].value.string) = nullptr;
            exp_ptr args((yystack_[1].value.expression));  (yystack_[1].value.expression) = nullptr;
            (yylhs.value.expression) = driver.MakeFunction(std::move(func), std::move(args), yystack_[3].location, yystack_[1].location, true);
        }
#line 2731 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 240:
#line 1324 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { 
            str_ptr func((yystack_[3].value.string)); (yystack_[3].value.string) = nullptr;
            exp_ptr args((yystack_[1].value.expression));           (yystack_[1].value.expression) = nullptr;
            (yylhs.value.expression) = driver.MakeArray(std::move(func), std::move(args), yystack_[3].location, yystack_[1].location);
        }
#line 2741 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 241:
#line 1330 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            (yylhs.value.expression) = driver.MakeFunction(std::move(func), std::move(args), yystack_[3].location, yystack_[1].location, false);
        }
#line 2751 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 242:
#line 1336 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.pop_repContainer(nullptr);
            cont_ptr vars((yystack_[1].value.bodyObj)); (yystack_[1].value.bodyObj) = nullptr;
            exp_ptr exp((yystack_[0].value.expression)); (yystack_[0].value.expression) = nullptr;
            (yylhs.value.expression) = driver.MakeLet(yystack_[1].location, std::move(vars), std::move(exp));
        }
#line 2762 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 243:
#line 1343 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { 
            str_ptr var((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            (yylhs.value.expression) = driver.MakeVariable(*var, yystack_[0].location);
        }
#line 2771 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 244:
#line 1350 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { 
            str_ptr func((yystack_[2].value.string)); (yystack_[2].value.string) = nullptr;
            (yylhs.value.expression) = driver.MakeFunction(std::move(func), nullptr, yystack_[2].location, yystack_[1].location + yystack_[0].location, false);
        }
#line 2780 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 245:
#line 1355 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            str_ptr func((yystack_[3].value.string)); (yystack_[3].value.string) = nullptr;
            exp_ptr args((yystack_[1].value.expression));  (yystack_[1].value.expression) = nullptr;
            (yylhs.value.expression) = driver.MakeFunction(std::move(func), std::move(args), yystack_[3].location, yystack_[1].location, false);
        }
#line 2790 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 246:
#line 1361 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { 
            str_ptr func((yystack_[3].value.string)); (yystack_[3].value.string) = nullptr;
            exp_ptr args((yystack_[1].value.expression));           (yystack_[1].value.expression) = nullptr;
            (yylhs.value.expression) = driver.MakeArray(std::move(func), std::move(args), yystack_[3].location, yystack_[1].location);
        }
#line 2800 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 247:
#line 1367 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            (yylhs.value.expression) = driver.MakeFunction(std::move(func), std::move(args), yystack_[3].location, yystack_[1].location, false);
        }
#line 2810 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 248:
#line 1373 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { 
            str_ptr func((yystack_[3].value.string)); (yystack_[3].value.string) = nullptr;
            exp_ptr args(new ASTexpression(yylhs.location, false, false, AST::ReuseType));
            (yylhs.value.expression) = driver.MakeFunction(std::move(func), std::move(args), yystack_[3].location, yystack_[1].location, false);
        }
#line 2820 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 249:
#line 1379 "../../src-common/cfdg.ypp" // lalr1.cc:846
    {
            driver.pop_repContainer(nullptr);
            cont_ptr vars((yystack_[1].value.bodyObj)); (yystack_[1].value.bodyObj) = nullptr;
            exp_ptr exp((yystack_[0].value.expression)); (yystack_[0].value.expression) = nullptr;
            (yylhs.value.expression) = driver.MakeLet(yystack_[1].location, std::move(vars), std::move(exp));
        }
#line 2831 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 250:
#line 1386 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { 
            str_ptr var((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            (yylhs.value.expression) = driver.MakeVariable(*var, yystack_[0].location);
        }
#line 2840 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 251:
#line 1393 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.string) = (yystack_[0].value.string); }
#line 2846 "cfdg.tab.cpp" // lalr1.cc:846
    break;

  case 252:
#line 1395 "../../src-common/cfdg.ypp" // lalr1.cc:846
    { (yylhs.value.string) = (yystack_[0].value.string); }
#line 2852 "cfdg.tab.cpp" // lalr1.cc:846
    break;


#line 2856 "cfdg.tab.cpp" // lalr1.cc:846
          default:
            break;
          }
      }
    catch (const syntax_error& yyexc)
      {
        error (yyexc);
        YYERROR;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yylhs);
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    // Shift the result of the reduction.
    yypush_ (YY_NULL, yylhs);
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
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
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
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

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
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
        if (!yyempty)
          yy_destroy_ (YY_NULL, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULL, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  CfdgParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  CfdgParser::yysyntax_error_ (state_type, symbol_number_type) const
  {
    return YY_("syntax error");
  }


  const short int CfdgParser::yypact_ninf_ = -286;

  const signed char CfdgParser::yytable_ninf_ = -91;

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
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
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
  "'/'", "NEG", "POS", "'^'", "'('", "'['", "'@'", "'{'", "'}'", "')'",
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


  const unsigned short int
  CfdgParser::yyrline_[] =
  {
       0,   193,   193,   193,   196,   201,   205,   210,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   229,   230,   231,
     232,   233,   234,   235,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   261,   262,   263,   264,   265,
     269,   278,   289,   296,   296,   299,   300,   304,   315,   325,
     337,   348,   359,   361,   363,   380,   411,   420,   429,   438,
     443,   448,   456,   468,   474,   478,   485,   503,   510,   518,
     526,   534,   548,   556,   563,   575,   587,   595,   604,   616,
     623,   629,   635,   640,   644,   650,   656,   657,   661,   662,
     666,   667,   671,   672,   673,   674,   678,   681,   685,   688,
     692,   699,   708,   714,   720,   728,   737,   747,   756,   758,
     764,   766,   772,   773,   777,   784,   788,   792,   801,   801,
     813,   822,   831,   840,   847,   854,   855,   856,   860,   862,
     870,   882,   883,   884,   885,   886,   887,   888,   889,   890,
     894,   903,   906,   910,   912,   918,   927,   929,   940,   940,
     955,   963,   972,   982,   990,   998,  1006,  1016,  1024,  1052,
    1063,  1068,  1075,  1080,  1087,  1092,  1099,  1103,  1113,  1118,
    1125,  1132,  1138,  1140,  1144,  1150,  1154,  1161,  1165,  1171,
    1173,  1175,  1177,  1179,  1181,  1183,  1188,  1195,  1197,  1199,
    1201,  1206,  1211,  1213,  1215,  1217,  1219,  1221,  1223,  1225,
    1227,  1229,  1231,  1233,  1235,  1237,  1239,  1241,  1243,  1245,
    1247,  1249,  1251,  1255,  1257,  1259,  1261,  1266,  1271,  1273,
    1275,  1277,  1279,  1281,  1283,  1285,  1287,  1289,  1291,  1293,
    1295,  1297,  1299,  1301,  1303,  1305,  1307,  1309,  1313,  1318,
    1324,  1330,  1336,  1343,  1350,  1355,  1361,  1367,  1373,  1379,
    1386,  1393,  1395
  };

  // Print the state stack on the debug stream.
  void
  CfdgParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  CfdgParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
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
    const unsigned int user_token_number_max_ = 305;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 3694 "cfdg.tab.cpp" // lalr1.cc:1156
#line 1398 "../../src-common/cfdg.ypp" // lalr1.cc:1157


void yy::CfdgParser::error(const CfdgParser::location_type& l, const std::string& m)
{
    driver.error(l, m);
}
