// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

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
#line 63 "../../src-common/cfdg.ypp" // lalr1.cc:397

#include "astreplacement.h"
#include "astexpression.h"
#define USE(VALUE) /*empty*/
    
    using namespace AST;

#line 42 "cfdg.tab.cpp" // lalr1.cc:397


// First part of user declarations.

#line 47 "cfdg.tab.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "cfdg.tab.hpp"

// User implementation prologue.

#line 61 "cfdg.tab.cpp" // lalr1.cc:412


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
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 147 "cfdg.tab.cpp" // lalr1.cc:479

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
    clear ();
  }

  template <typename Base>
  inline
  void
  CfdgParser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  CfdgParser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
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
    : type (empty_symbol)
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
  CfdgParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  CfdgParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
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
    : state (empty_state)
  {}

  inline
  CfdgParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  CfdgParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  CfdgParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  CfdgParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  CfdgParser::symbol_number_type
  CfdgParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
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
    that.type = empty_symbol;
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

#line 145 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.string); }
#line 362 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 29: // USER_FILENAME

#line 145 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.string); }
#line 369 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 30: // USER_QSTRING

#line 145 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.string); }
#line 376 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 31: // USER_ARRAYNAME

#line 145 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.string); }
#line 383 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 36: // USER_PATHOP

#line 145 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.string); }
#line 390 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 72: // statement

#line 153 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.component); }
#line 397 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 73: // statement_v2

#line 153 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.component); }
#line 404 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 79: // fileString

#line 145 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.string); }
#line 411 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 80: // fileNameSpace

#line 145 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.string); }
#line 418 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 81: // initialization

#line 153 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.component); }
#line 425 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 82: // initialization_v2

#line 153 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.component); }
#line 432 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 83: // directive_v2

#line 153 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.component); }
#line 439 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 84: // directive_num

#line 146 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { }
#line 446 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 85: // global_definition

#line 147 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.defObj); }
#line 453 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 86: // function_definition_header

#line 147 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.defObj); }
#line 460 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 87: // global_definition_header

#line 147 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.defObj); }
#line 467 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 88: // definition_header

#line 147 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.defObj); }
#line 474 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 89: // definition

#line 147 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.defObj); }
#line 481 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 91: // shape_singleton_header

#line 154 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { driver.pop_repContainer(nullptr); delete (yysym.value.ruleObj); }
#line 488 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 92: // shape_singleton

#line 153 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.component); }
#line 495 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 93: // rule_header_v2

#line 157 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { driver.pop_repContainer(nullptr); delete (yysym.value.ruleObj); }
#line 502 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 95: // rule_header

#line 156 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { driver.pop_repContainer(nullptr); delete (yysym.value.ruleObj); }
#line 509 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 96: // path_header

#line 156 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { driver.pop_repContainer(nullptr); delete (yysym.value.ruleObj); }
#line 516 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 97: // rule

#line 153 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.component); }
#line 523 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 98: // path

#line 153 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.component); }
#line 530 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 99: // path_header_v2

#line 157 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { driver.pop_repContainer(nullptr); delete (yysym.value.ruleObj); }
#line 537 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 105: // parameter_spec

#line 148 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.expression); }
#line 544 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 108: // pathOp_simple_v2

#line 155 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.component); }
#line 551 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 109: // element_simple

#line 153 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.component); }
#line 558 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 114: // element

#line 153 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.component); }
#line 565 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 117: // pathOp_v2

#line 155 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.component); }
#line 572 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 119: // element_loop

#line 152 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { driver.pop_repContainer(nullptr); delete (yysym.value.loopObj); }
#line 579 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 122: // replacement_simple_v2

#line 155 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.component); }
#line 586 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 123: // replacement_v2

#line 155 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.component); }
#line 593 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 124: // loopHeader_v2

#line 151 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { driver.pop_repContainer(nullptr); delete (yysym.value.loopObj); }
#line 600 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 126: // loopHeader

#line 152 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { driver.pop_repContainer(nullptr); delete (yysym.value.loopObj); }
#line 607 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 127: // ifHeader

#line 158 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { driver.pop_repContainer(nullptr); delete (yysym.value.ifObj); }
#line 614 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 128: // ifElseHeader

#line 158 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { driver.pop_repContainer(nullptr); delete (yysym.value.ifObj); }
#line 621 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 129: // transHeader

#line 154 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { driver.pop_repContainer(nullptr); delete (yysym.value.component); }
#line 628 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 130: // switchHeader

#line 159 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.switchObj); }
#line 635 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 131: // caseHeader

#line 160 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { driver.pop_repContainer(nullptr); }
#line 642 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 132: // modification_v2

#line 150 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.mod); }
#line 649 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 133: // modification

#line 150 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.mod); }
#line 656 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 134: // buncha_adjustments

#line 150 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.mod); }
#line 663 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 135: // adjustment

#line 149 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.term); }
#line 670 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 136: // letHeader

#line 161 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { driver.pop_repContainer(nullptr); delete (yysym.value.bodyObj); }
#line 677 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 137: // letBody

#line 148 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.expression); }
#line 684 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 140: // explist

#line 148 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.expression); }
#line 691 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 141: // arglist

#line 148 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.expression); }
#line 698 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 142: // exp

#line 148 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.expression); }
#line 705 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 143: // exp2

#line 148 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.expression); }
#line 712 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 144: // exp3

#line 148 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.expression); }
#line 719 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 145: // expfunc

#line 148 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.expression); }
#line 726 "cfdg.tab.cpp" // lalr1.cc:617
        break;

      case 146: // shapeName

#line 145 "../../src-common/cfdg.ypp" // lalr1.cc:617
        { delete (yysym.value.string); }
#line 733 "cfdg.tab.cpp" // lalr1.cc:617
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
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
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
  CfdgParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
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
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

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
    yypush_ (YY_NULLPTR, 0, yyla);

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
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
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
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
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
#line 179 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            if ((yystack_[0].value.component)) {
                driver.push_rep((yystack_[0].value.component), true);
            }
        }
#line 976 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 6:
#line 188 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            if ((yystack_[0].value.component)) {
                driver.push_rep((yystack_[0].value.component), true);
            }
        }
#line 986 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 9:
#line 198 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.component) = nullptr; }
#line 992 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 10:
#line 199 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.component) = nullptr; }
#line 998 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 13:
#line 202 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.component) = nullptr; }
#line 1004 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 15:
#line 204 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.component) = static_cast<ASTreplacement*>((yystack_[0].value.defObj)); }
#line 1010 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 16:
#line 205 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            error(yystack_[0].location, "Illegal mixture of old and new elements");
            (yylhs.value.component) = nullptr;
        }
#line 1019 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 19:
#line 214 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.component) = nullptr; }
#line 1025 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 20:
#line 215 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.component) = nullptr; }
#line 1031 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 23:
#line 218 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            if (driver.lexer->maybeVersion == token::CFDG2) {
                error(yystack_[0].location, "Illegal mixture of old and new elements");
            } else {
                driver.lexer->maybeVersion = token::CFDG3;
            }
            (yylhs.value.component) = nullptr;
            YYABORT;
        }
#line 1045 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 24:
#line 230 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[1].value.string); }
#line 1051 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 25:
#line 231 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {}
#line 1057 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 26:
#line 232 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {}
#line 1063 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 27:
#line 233 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[1].value.string); }
#line 1069 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 28:
#line 234 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[2].value.string); delete (yystack_[1].value.string); }
#line 1075 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 31:
#line 237 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[1].value.string); }
#line 1081 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 32:
#line 238 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[1].value.string); }
#line 1087 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 33:
#line 239 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[1].value.string); }
#line 1093 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 34:
#line 240 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[1].value.string); }
#line 1099 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 35:
#line 244 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[0].value.mod); }
#line 1105 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 36:
#line 245 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[0].value.mod); }
#line 1111 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 37:
#line 246 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[0].value.mod); }
#line 1117 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 38:
#line 247 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[0].value.string); }
#line 1123 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 39:
#line 248 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[0].value.ruleObj); }
#line 1129 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 40:
#line 252 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr file((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            driver.lexer->maybeVersion = token::CFDG2;
            driver.SetShape(nullptr);
            driver.IncludeFile(*file);
        }
#line 1140 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 41:
#line 261 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr file((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            str_ptr nm((yystack_[1].value.string)); (yystack_[1].value.string) = nullptr;
            driver.SetShape(nullptr);
            driver.IncludeFile(*file);
            if (nm)
                driver.PushNameSpace(std::move(nm), yystack_[1].location);
        }
#line 1153 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 42:
#line 272 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            if (driver.EndInclude())
                YYACCEPT;
        }
#line 1162 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 45:
#line 282 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.string) = (yystack_[0].value.string); }
#line 1168 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 46:
#line 283 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.string) = nullptr; }
#line 1174 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 47:
#line 287 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr name((yystack_[2].value.string));   (yystack_[2].value.string) = nullptr;
            exp_ptr p((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            driver.SetShape(nullptr);
            (yylhs.value.component) = driver.MakeDefinition(CFG::StartShape, yylhs.location,
                                                    driver.MakeRuleSpec(*name, std::move(p), yystack_[2].location, std::move(mod), true));
        }
#line 1187 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 48:
#line 296 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr name((yystack_[1].value.string));   (yystack_[1].value.string) = nullptr;
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            driver.SetShape(nullptr);
            (yylhs.value.component) = driver.MakeDefinition(CFG::StartShape, yylhs.location,
                                                    driver.MakeRuleSpec(*name, nullptr, yystack_[1].location, std::move(mod), true));
        }
#line 1199 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 49:
#line 304 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr name((yystack_[1].value.string));   (yystack_[1].value.string) = nullptr;
            exp_ptr p((yystack_[0].value.expression)); (yystack_[0].value.expression) = nullptr;
            driver.SetShape(nullptr);
            (yylhs.value.component) = driver.MakeDefinition(CFG::StartShape, yylhs.location,
                                                    driver.MakeRuleSpec(*name, std::move(p), yystack_[1].location, nullptr, true));
        }
#line 1211 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 50:
#line 314 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr name((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            driver.SetShape(nullptr);
            (yylhs.value.component) = driver.MakeDefinition(CFG::StartShape, yylhs.location,
                                                       driver.MakeRuleSpec(*name, nullptr, yystack_[0].location, nullptr, true));
        }
#line 1222 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 51:
#line 323 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            exp_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            driver.lexer->maybeVersion = token::CFDG2;
            (yylhs.value.component) = driver.MakeDefinition((yystack_[1].value.cfgenum), yylhs.location, std::move(mod));
        }
#line 1232 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 52:
#line 331 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.cfgenum) = CFG::Background; }
#line 1238 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 53:
#line 333 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.cfgenum) = CFG::Tile; }
#line 1244 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 54:
#line 335 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            switch ((yystack_[0].value.modToken)) {
                case ASTmodTerm::size:
                    (yylhs.value.cfgenum) = CFG::Size;
                    break;
                case ASTmodTerm::time:
                    (yylhs.value.cfgenum) = CFG::Time;
                    break;
                default:
                    (yylhs.value.cfgenum) = CFG::Size;
                    error(yystack_[0].location, "Syntax error");
                    break;
            }
        }
#line 1263 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 55:
#line 352 "../../src-common/cfdg.ypp" // lalr1.cc:859
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
                        driver.mParamSize = 0;
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
#line 1296 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 56:
#line 383 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr name((yystack_[2].value.string)); (yystack_[2].value.string) = nullptr;
            (yylhs.value.defObj) = driver.MakeDefinition(*name, yylhs.location, true);
            if ((yylhs.value.defObj)) {
                (yylhs.value.defObj)->mType = RuleType;
                (yylhs.value.defObj)->mTuplesize = 1;
            }
        }
#line 1309 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 57:
#line 392 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr name((yystack_[2].value.string)); (yystack_[2].value.string) = nullptr;
            (yylhs.value.defObj) = driver.MakeDefinition(*name, yylhs.location, true);
            if ((yylhs.value.defObj)) {
                (yylhs.value.defObj)->mType = NumericType;
                (yylhs.value.defObj)->mTuplesize = 1;
            }
        }
#line 1322 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 58:
#line 401 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr type((yystack_[3].value.string)); (yystack_[3].value.string) = nullptr;
            str_ptr name((yystack_[2].value.string)); (yystack_[2].value.string) = nullptr;
            (yylhs.value.defObj) = driver.MakeDefinition(*name, yylhs.location, true);
            if ((yylhs.value.defObj))
                (yylhs.value.defObj)->mType = AST::decodeType(*type, (yylhs.value.defObj)->mTuplesize, 
                                                                     (yylhs.value.defObj)->isNatural, yystack_[3].location);
        }
#line 1335 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 59:
#line 410 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            error(yystack_[2].location, "Reserved keyword: adjustment");
            (yylhs.value.defObj) = nullptr;
        }
#line 1344 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 60:
#line 415 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            error(yystack_[2].location, "Reserved keyword: adjustment");
            (yylhs.value.defObj) = nullptr;
        }
#line 1353 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 61:
#line 420 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr type((yystack_[3].value.string)); (yystack_[3].value.string) = nullptr;
            error(yystack_[2].location, "Reserved keyword: adjustment");
            (yylhs.value.defObj) = nullptr;
        }
#line 1363 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 62:
#line 428 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            if ((yystack_[0].value.defObj)) {
                assert((yystack_[0].value.defObj)->mDefineType == ASTdefine::FunctionDefine);
                driver.push_repContainer(driver.mParamDecls);
            } else {
                // An error occurred
                driver.mParamDecls.mParameters.clear();
                driver.mParamSize = 0;
            }
            (yylhs.value.defObj) = (yystack_[0].value.defObj);
        }
#line 1379 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 63:
#line 440 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.defObj) = (yystack_[0].value.defObj);
        }
#line 1387 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 64:
#line 446 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr name((yystack_[1].value.string)); (yystack_[1].value.string) = nullptr;
            (yylhs.value.defObj) = driver.MakeDefinition(*name, yylhs.location, false);
        }
#line 1396 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 65:
#line 450 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            error(yystack_[1].location, "Reserved keyword: adjustment");
            (yylhs.value.defObj) = nullptr;
        }
#line 1405 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 66:
#line 457 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            def_ptr var((yystack_[1].value.defObj));  (yystack_[1].value.defObj) = nullptr;
            exp_ptr exp((yystack_[0].value.expression));               (yystack_[0].value.expression) = nullptr;
            if (var) {
                if (ASTmodification* mod = dynamic_cast<ASTmodification*>(exp.get())) {
                    mod->modData.mRand64Seed.seed();
                    var->mChildChange.grab(mod);
                } else {
                    var->mExpression = std::move(exp);
                }
                (yylhs.value.defObj) = var.release();
            } else {
                (yylhs.value.defObj) = nullptr;
            }
        }
#line 1425 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 67:
#line 475 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr name((yystack_[1].value.string)); (yystack_[1].value.string) = nullptr;
            driver.SetShape(name.get(), yystack_[1].location);
        }
#line 1434 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 68:
#line 482 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.mInPathContainer = false;
            (yylhs.value.ruleObj) = new ASTrule(-1, yystack_[1].location);
            driver.AddRule((yylhs.value.ruleObj));
            driver.push_repContainer((yylhs.value.ruleObj)->mRuleBody);
        }
#line 1445 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 69:
#line 490 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.component) = (yystack_[2].value.ruleObj);
            driver.pop_repContainer((yystack_[2].value.ruleObj));
            driver.mInPathContainer = false;
        }
#line 1455 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 70:
#line 498 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr name((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            driver.SetShape(nullptr);
            (yylhs.value.ruleObj) = new ASTrule(driver.StringToShape(*name, yystack_[0].location, false), yylhs.location);
            driver.AddRule((yylhs.value.ruleObj));
            driver.push_repContainer((yylhs.value.ruleObj)->mRuleBody);
        }
#line 1467 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 71:
#line 506 "../../src-common/cfdg.ypp" // lalr1.cc:859
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
#line 1483 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 72:
#line 520 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.lexer->maybeVersion = token::CFDG2;
            (yylhs.value.component) = (yystack_[3].value.ruleObj);
            driver.pop_repContainer((yystack_[3].value.ruleObj));
        }
#line 1493 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 73:
#line 528 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.mInPathContainer = false;
            (yylhs.value.ruleObj) = new ASTrule(-1, yystack_[0].location);
            driver.AddRule((yylhs.value.ruleObj));
            driver.push_repContainer((yylhs.value.ruleObj)->mRuleBody);
        }
#line 1504 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 74:
#line 535 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.mInPathContainer = false;
            str_ptr weight((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            (yylhs.value.ruleObj) = new ASTrule(-1, CFatof(weight->c_str()),
                                       weight->find_first_of('%')  != std::string::npos,
                                       yylhs.location);
            driver.AddRule((yylhs.value.ruleObj));
            driver.push_repContainer((yylhs.value.ruleObj)->mRuleBody);
        }
#line 1518 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 75:
#line 547 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr name((yystack_[1].value.string)); (yystack_[1].value.string) = nullptr;
            driver.SetShape(name.get(), yystack_[1].location, true);
            driver.mInPathContainer = true;
            (yylhs.value.ruleObj) = new ASTrule(-1, yylhs.location);
            (yylhs.value.ruleObj)->isPath = true;
            driver.AddRule((yylhs.value.ruleObj));
            driver.push_repContainer((yylhs.value.ruleObj)->mRuleBody);
        }
#line 1532 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 76:
#line 559 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.component) = (yystack_[3].value.ruleObj);
            driver.pop_repContainer((yystack_[3].value.ruleObj));
            driver.mInPathContainer = false;
        }
#line 1542 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 77:
#line 567 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.component) = (yystack_[3].value.ruleObj);
            driver.pop_repContainer((yystack_[3].value.ruleObj));
            driver.mInPathContainer = false;
            driver.SetShape(nullptr);
        }
#line 1553 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 78:
#line 576 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr name((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            driver.SetShape(nullptr);
            (yylhs.value.ruleObj) = new ASTrule(driver.StringToShape(*name, yystack_[0].location, false), yylhs.location);
            (yylhs.value.ruleObj)->isPath = true;
            driver.AddRule((yylhs.value.ruleObj));
            driver.push_repContainer((yylhs.value.ruleObj)->mRuleBody);
            driver.mInPathContainer = true;
        }
#line 1567 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 79:
#line 588 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.component) = (yystack_[3].value.ruleObj);
            driver.pop_repContainer((yystack_[3].value.ruleObj));
        }
#line 1576 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 80:
#line 595 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr type((yystack_[1].value.string)); (yystack_[1].value.string) = nullptr;
            str_ptr var((yystack_[0].value.string));  (yystack_[0].value.string) = nullptr;
            driver.NextParameterDecl(*type, *var, yystack_[1].location, yystack_[0].location);
        }
#line 1586 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 81:
#line 601 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            static std::string shapeStr("shape");
            str_ptr var((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            driver.NextParameterDecl(shapeStr, *var, yystack_[1].location, yystack_[0].location);
        }
#line 1596 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 82:
#line 607 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            delete (yystack_[1].value.string);
            error(yystack_[0].location, "Reserved keyword: adjustment");
        }
#line 1605 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 83:
#line 612 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            error(yystack_[0].location, "Reserved keyword: adjustment");
        }
#line 1613 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 84:
#line 616 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            static const std::string numtype("number");
            str_ptr var((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            driver.NextParameterDecl(numtype, *var, yystack_[0].location, yystack_[0].location);
        }
#line 1623 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 85:
#line 622 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            error(yystack_[0].location, "Reserved keyword: adjustment");
        }
#line 1631 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 92:
#line 643 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = (yystack_[1].value.expression);}
#line 1637 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 93:
#line 644 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASTexpression(yylhs.location, false, false, AST::ReuseType); }
#line 1643 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 94:
#line 645 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = nullptr; }
#line 1649 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 95:
#line 646 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = nullptr; }
#line 1655 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 96:
#line 650 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.push_rep((yystack_[0].value.component));
        }
#line 1663 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 98:
#line 657 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.push_rep((yystack_[0].value.component));
        }
#line 1671 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 100:
#line 664 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr pop((yystack_[3].value.string));        (yystack_[3].value.string) = nullptr;
            mod_ptr mod((yystack_[1].value.mod)); (yystack_[1].value.mod) = nullptr;
            driver.lexer->maybeVersion = token::CFDG2;
            (yylhs.value.component) = new ASTpathOp(*pop, std::move(mod), yylhs.location);
        }
#line 1682 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 101:
#line 671 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr cmd((yystack_[1].value.string)); (yystack_[1].value.string) = nullptr;
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            driver.lexer->maybeVersion = token::CFDG2;
            (yylhs.value.component) = new ASTpathCommand(*cmd, std::move(mod), nullptr, yylhs.location);
        }
#line 1693 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 102:
#line 680 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr pop((yystack_[3].value.string)); (yystack_[3].value.string) = nullptr;
            exp_ptr mod((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            (yylhs.value.component) = new ASTpathOp(*pop, std::move(mod), yylhs.location);
        }
#line 1703 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 103:
#line 686 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr pop((yystack_[2].value.string)); (yystack_[2].value.string) = nullptr;
            exp_ptr mod;
            (yylhs.value.component) = new ASTpathOp(*pop, std::move(mod), yylhs.location);
        }
#line 1713 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 104:
#line 692 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr cmd((yystack_[2].value.string));    (yystack_[2].value.string) = nullptr;
            exp_ptr p((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            (yylhs.value.component) = driver.MakeElement(*cmd, std::move(mod),
                                                 std::move(p), yylhs.location, false);
        }
#line 1725 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 105:
#line 700 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { 
            exp_ptr args((yystack_[2].value.expression));        (yystack_[2].value.expression) = nullptr;
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            str_ptr func(new std::string("if"));
            args.reset(driver.MakeFunction(std::move(func), std::move(args), yystack_[4].location, yystack_[2].location, false));
            static const std::string ifstr("if");
            (yylhs.value.component) = driver.MakeElement(ifstr, std::move(mod), std::move(args), yylhs.location, false);
        }
#line 1738 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 106:
#line 709 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.pop_repContainer(nullptr);
            cont_ptr vars((yystack_[2].value.bodyObj));  (yystack_[2].value.bodyObj) = nullptr;
            exp_ptr exp((yystack_[1].value.expression));      (yystack_[1].value.expression) = nullptr;
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            exp.reset(driver.MakeLet(yystack_[2].location, std::move(vars), std::move(exp)));      // must do unconditionally
            static const std::string letstr("let");
            (yylhs.value.component) = driver.MakeElement(letstr, std::move(mod), std::move(exp), yylhs.location, false);
        }
#line 1752 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 107:
#line 719 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr cmd((yystack_[2].value.string));    (yystack_[2].value.string) = nullptr;
            exp_ptr p((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            (yylhs.value.component) = driver.MakeElement(*cmd, std::move(mod), std::move(p), yylhs.location, true);
        }
#line 1763 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 108:
#line 728 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { }
#line 1769 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 109:
#line 730 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.push_rep((yystack_[0].value.component));
        }
#line 1777 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 110:
#line 736 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { }
#line 1783 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 111:
#line 738 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.push_rep((yystack_[0].value.component));
        }
#line 1791 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 114:
#line 749 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.pop_repContainer(driver.switchStack.top());
            USE((yystack_[1].value.modToken));
        }
#line 1800 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 115:
#line 756 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { 
            (yylhs.value.component) = (yystack_[0].value.component);
        }
#line 1808 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 116:
#line 760 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.component) = (yystack_[0].value.defObj);
        }
#line 1816 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 117:
#line 764 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.component) = (yystack_[0].value.loopObj);
            driver.pop_repContainer((yystack_[0].value.loopObj));
            if ((yystack_[0].value.loopObj)->mRepType == 0) {
                delete (yystack_[0].value.loopObj);
                (yylhs.value.component) = nullptr;
            }
        }
#line 1829 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 118:
#line 773 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.pop_repContainer((yystack_[1].value.loopObj));
            driver.push_repContainer((yystack_[1].value.loopObj)->mFinallyBody);
        }
#line 1838 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 119:
#line 776 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.pop_repContainer((yystack_[3].value.loopObj));
            (yylhs.value.component) = (yystack_[3].value.loopObj);
            if ((yystack_[3].value.loopObj)->mRepType == 0) {
                delete (yystack_[3].value.loopObj);
                (yylhs.value.component) = nullptr;
            }
        }
#line 1851 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 120:
#line 785 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.component) = (yystack_[1].value.ifObj);
            driver.pop_repContainer((yystack_[1].value.ifObj));
            if ((yystack_[1].value.ifObj)->mRepType == 0) {
                delete (yystack_[1].value.ifObj);
                (yylhs.value.component) = nullptr;
            }
        }
#line 1864 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 121:
#line 794 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.component) = (yystack_[1].value.ifObj);
            driver.pop_repContainer((yystack_[1].value.ifObj));
            if ((yystack_[1].value.ifObj)->mRepType == 0) {
                delete (yystack_[1].value.ifObj);
                (yylhs.value.component) = nullptr;
            }
        }
#line 1877 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 122:
#line 803 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.component) = (yystack_[1].value.component);
            driver.pop_repContainer((yystack_[1].value.component));
            if ((yystack_[1].value.component)->mRepType == 0) {
                delete (yystack_[1].value.component);
                (yylhs.value.component) = nullptr;
            }
        }
#line 1890 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 123:
#line 813 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.component) = (yystack_[3].value.switchObj);
            (yystack_[3].value.switchObj)->unify();
            driver.switchStack.pop();
        }
#line 1900 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 124:
#line 819 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            error(yystack_[0].location, "Illegal mixture of old and new elements");
            (yylhs.value.component) = nullptr;
        }
#line 1909 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 125:
#line 826 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[1].value.string); }
#line 1915 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 126:
#line 827 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[1].value.string); }
#line 1921 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 127:
#line 828 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[1].value.string); }
#line 1927 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 128:
#line 832 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.component) = (yystack_[0].value.component); }
#line 1933 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 129:
#line 834 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.component) = (yystack_[1].value.loopObj);
            driver.pop_repContainer((yystack_[1].value.loopObj));
            if ((yystack_[1].value.loopObj)->mRepType == 0) {
                delete (yystack_[1].value.loopObj);
                (yylhs.value.component) = nullptr;
            }
        }
#line 1946 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 130:
#line 842 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            if (driver.lexer->maybeVersion == token::CFDG2) {
                error(yystack_[0].location, "Illegal mixture of old and new elements");
            } else {
                driver.lexer->maybeVersion = token::CFDG3;
            }
            (yylhs.value.component) = nullptr;
            YYABORT;
        }
#line 1960 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 131:
#line 854 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[1].value.string); }
#line 1966 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 132:
#line 855 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[1].value.string); }
#line 1972 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 135:
#line 858 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { delete (yystack_[1].value.string); }
#line 1978 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 140:
#line 866 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            // parse loop mod and loop body with loop index in scope
            (yystack_[2].value.loopObj)->mLoopModHolder.reset((yystack_[1].value.mod)); (yystack_[1].value.mod) = nullptr;
            (yylhs.value.loopObj) = (yystack_[2].value.loopObj);
            // loopmod gets deleted
        }
#line 1989 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 141:
#line 875 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.push_rep((yystack_[0].value.component));
        }
#line 1997 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 143:
#line 882 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { }
#line 2003 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 144:
#line 884 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.push_rep((yystack_[0].value.component));
        }
#line 2011 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 145:
#line 890 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr name((yystack_[1].value.string)); (yystack_[1].value.string) = nullptr;
            mod_ptr mod((yystack_[0].value.mod)); (yystack_[0].value.mod) = nullptr;
            ruleSpec_ptr r(driver.MakeRuleSpec(*name, nullptr, yystack_[1].location));
            (yylhs.value.component) = new ASTreplacement(std::move(*r), std::move(mod), yylhs.location);
        }
#line 2022 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 146:
#line 899 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.component) = (yystack_[0].value.component); }
#line 2028 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 147:
#line 901 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.component) = (yystack_[1].value.loopObj);
            driver.pop_repContainer((yystack_[1].value.loopObj));
            if ((yystack_[1].value.loopObj)->mRepType == 0) {
                delete (yystack_[1].value.loopObj);
                (yylhs.value.component) = nullptr;
            }
        }
#line 2041 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 148:
#line 912 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { ++driver.mLocalStackDepth; }
#line 2047 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 149:
#line 912 "../../src-common/cfdg.ypp" // lalr1.cc:859
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
#line 2064 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 150:
#line 927 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr var((yystack_[2].value.string)); (yystack_[2].value.string) = nullptr;
            exp_ptr index((yystack_[0].value.expression));   (yystack_[0].value.expression) = nullptr;
            int nameIndex = driver.StringToShape(*var, yystack_[2].location, false);
            (yylhs.value.loopObj) = new ASTloop(nameIndex, *var, yystack_[2].location, std::move(index), yystack_[0].location, nullptr);
            driver.push_repContainer((yylhs.value.loopObj)->mLoopBody);
        }
#line 2076 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 151:
#line 935 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            exp_ptr index((yystack_[0].value.expression)); (yystack_[0].value.expression) = nullptr;
            static const std::string dummyvar("~~inaccessiblevar~~");
            (yylhs.value.loopObj) = new ASTloop(driver.StringToShape(dummyvar, yystack_[3].location, false),
                                      dummyvar, yystack_[2].location, std::move(index), yystack_[0].location, nullptr);
            driver.push_repContainer((yylhs.value.loopObj)->mLoopBody);
            error(yystack_[2].location, "Reserved keyword: adjustment");
        }
#line 2089 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 152:
#line 944 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            exp_ptr count((yystack_[0].value.expression)); (yystack_[0].value.expression) = nullptr;
            static const std::string dummyvar("~~inaccessiblevar~~");
            (yylhs.value.loopObj) = new ASTloop(driver.StringToShape(dummyvar, yystack_[1].location, false),
                                      dummyvar, yystack_[1].location, std::move(count), yystack_[0].location, nullptr);
            driver.push_repContainer((yylhs.value.loopObj)->mLoopBody);
        }
#line 2101 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 153:
#line 954 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            exp_ptr cond((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            (yylhs.value.ifObj) = new ASTif(std::move(cond), yystack_[1].location);
            driver.push_repContainer((yylhs.value.ifObj)->mThenBody);
        }
#line 2111 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 154:
#line 962 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.pop_repContainer((yystack_[2].value.ifObj));
            driver.push_repContainer((yystack_[2].value.ifObj)->mElseBody);
            (yylhs.value.ifObj) = (yystack_[2].value.ifObj);
        }
#line 2121 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 155:
#line 970 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            exp_ptr mods((yystack_[0].value.expression)); (yystack_[0].value.expression) = nullptr;
            if ((yystack_[1].value.modToken) != ASTmodTerm::transform)
                error(yystack_[1].location, "Syntax error");
            ASTtransform* trans = new ASTtransform(yylhs.location, std::move(mods));
            driver.push_repContainer(trans->mBody);
            (yylhs.value.component) = trans;
        }
#line 2134 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 156:
#line 978 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            exp_ptr mods((yystack_[0].value.expression)); (yystack_[0].value.expression) = nullptr;
            ASTtransform* trans = new ASTtransform(yylhs.location, std::move(mods));
            driver.push_repContainer(trans->mBody);
            trans->mClone = true;
            (yylhs.value.component) = trans;
        }
#line 2146 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 157:
#line 988 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            exp_ptr caseVal((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            (yylhs.value.switchObj) = new ASTswitch(std::move(caseVal), yystack_[1].location);
            driver.switchStack.push((yylhs.value.switchObj));
        }
#line 2156 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 158:
#line 996 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            exp_ptr valExp((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            
            ASTswitch* _switch = driver.switchStack.top();
            cont_ptr caseBody(new ASTrepContainer());
            driver.push_repContainer(*caseBody);
            _switch->mCases.emplace_back(std::move(valExp), std::move(caseBody));
            
            (yylhs.value.modToken) = 0;
        }
#line 2171 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1007 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            if (!driver.switchStack.top()->mElseBody.mBody.empty()) {
                driver.error(yylhs.location, "There can only be one 'else:' clause");
            } else {
                driver.push_repContainer(driver.switchStack.top()->mElseBody);
            }
            (yylhs.value.modToken) = 0;
        }
#line 2184 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1018 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            mod_ptr mod((yystack_[1].value.mod)); (yystack_[1].value.mod) = nullptr;
            (yylhs.value.mod) = driver.MakeModification(std::move(mod), yylhs.location, true);
        }
#line 2193 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1023 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            mod_ptr mod((yystack_[1].value.mod)); (yystack_[1].value.mod) = nullptr;
            (yylhs.value.mod) = driver.MakeModification(std::move(mod), yylhs.location, false);
        }
#line 2202 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1030 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            mod_ptr mod((yystack_[1].value.mod)); (yystack_[1].value.mod) = nullptr;
            (yylhs.value.mod) = driver.MakeModification(std::move(mod), yylhs.location, true);
        }
#line 2211 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1035 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            mod_ptr mod((yystack_[2].value.mod)); (yystack_[2].value.mod) = nullptr;
            (yylhs.value.mod) = driver.MakeModification(std::move(mod), yylhs.location, false);
        }
#line 2220 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1042 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            term_ptr mod((yystack_[0].value.term)); (yystack_[0].value.term) = nullptr;
            driver.MakeModTerm((yystack_[1].value.mod)->modExp, std::move(mod));
            (yylhs.value.mod) = (yystack_[1].value.mod);
        }
#line 2230 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1047 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            static const yy::location def;
            (yylhs.value.mod) = new ASTmodification(def);
        }
#line 2239 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1054 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.term) = new ASTmodTerm(static_cast<ASTmodTerm::modTypeEnum>((yystack_[1].value.modToken)), (yystack_[0].value.expression), yylhs.location);
        }
#line 2247 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1058 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            exp_ptr mod((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            if ((yystack_[2].value.modToken) < ASTmodTerm::hue || (yystack_[2].value.modToken) > ASTmodTerm::alpha) {
                error(yylhs.location, "The target operator can only be applied to color adjustments");
                (yylhs.value.term) = nullptr;
            } else {
                (yylhs.value.term) = new ASTmodTerm(static_cast<ASTmodTerm::modTypeEnum>((yystack_[2].value.modToken) + 4), mod.release(), yylhs.location);
            }
        }
#line 2261 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1068 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr p((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            (yylhs.value.term) = new ASTmodTerm(ASTmodTerm::param, *p, yylhs.location);
        }
#line 2270 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1073 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr p((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            (yylhs.value.term) = new ASTmodTerm(ASTmodTerm::param, *p, yylhs.location);
        }
#line 2279 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1080 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.bodyObj) = new ASTrepContainer();
            driver.push_repContainer(*(yylhs.value.bodyObj));
        }
#line 2288 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1087 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.expression) = (yystack_[1].value.expression);
        }
#line 2296 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1099 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.push_rep((yystack_[0].value.defObj));
        }
#line 2304 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1105 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.expression) = ASTexpression::Append((yystack_[1].value.expression), (yystack_[0].value.expression));
        }
#line 2312 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1109 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { 
            (yylhs.value.expression) = (yystack_[0].value.expression);
        }
#line 2320 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1116 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.expression) = (yystack_[2].value.expression)->append(new ASTparen((yystack_[0].value.expression)));
        }
#line 2328 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1120 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            (yylhs.value.expression) = new ASTcons{ new ASTparen((yystack_[0].value.expression)) };
        }
#line 2336 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1126 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASTreal(*(yystack_[0].value.string), yylhs.location); delete (yystack_[0].value.string); (yystack_[0].value.string) = nullptr; }
#line 2342 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1128 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASTreal(Renderer::Infinity, yylhs.location); }
#line 2348 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1130 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASTparen((yystack_[1].value.expression)); }
#line 2354 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1132 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = (yystack_[0].value.expression); }
#line 2360 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1134 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr func((yystack_[3].value.string)); (yystack_[3].value.string) = nullptr;
            exp_ptr args((yystack_[1].value.expression));  (yystack_[1].value.expression) = nullptr;
            (yylhs.value.expression) = driver.MakeFunction(std::move(func), std::move(args), yystack_[3].location, yystack_[1].location, true);
        }
#line 2370 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1140 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('N', (yystack_[0].value.expression), nullptr);; }
#line 2376 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1142 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('P', (yystack_[0].value.expression), nullptr);; }
#line 2382 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 186:
#line 1144 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            exp_ptr pair((yystack_[2].value.expression)->append((yystack_[0].value.expression))); (yystack_[2].value.expression) = nullptr; (yystack_[0].value.expression) = nullptr;
            (yylhs.value.expression) = new ASTfunction("rand.", std::move(pair), driver.mSeed, yystack_[2].location, yylhs.location);
        }
#line 2391 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 187:
#line 1149 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            exp_ptr pair((yystack_[2].value.expression)->append((yystack_[0].value.expression))); (yystack_[2].value.expression) = nullptr; (yystack_[0].value.expression) = nullptr;
            (yylhs.value.expression) = new ASTfunction("rand+/-", std::move(pair), driver.mSeed, yystack_[2].location, yylhs.location);
        }
#line 2400 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 188:
#line 1156 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = (yystack_[2].value.expression)->append((yystack_[0].value.expression)); }
#line 2406 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1158 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = (yystack_[0].value.expression); }
#line 2412 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 190:
#line 1162 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASTreal(*(yystack_[0].value.string), yylhs.location); delete (yystack_[0].value.string); (yystack_[0].value.string) = nullptr; }
#line 2418 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 191:
#line 1164 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASTreal(Renderer::Infinity, yylhs.location); }
#line 2424 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 192:
#line 1166 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = (yystack_[0].value.expression); }
#line 2430 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 193:
#line 1168 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr func((yystack_[3].value.string)); (yystack_[3].value.string) = nullptr;
            exp_ptr args((yystack_[1].value.expression));  (yystack_[1].value.expression) = nullptr;
            (yylhs.value.expression) = driver.MakeFunction(std::move(func), std::move(args), yystack_[3].location, yystack_[1].location, false);
        }
#line 2440 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 194:
#line 1174 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            exp_ptr pair((yystack_[2].value.expression)->append((yystack_[0].value.expression))); (yystack_[2].value.expression) = nullptr; (yystack_[0].value.expression) = nullptr;
            (yylhs.value.expression) = new ASTfunction("rand.", std::move(pair), driver.mSeed, yystack_[2].location, yylhs.location);
        }
#line 2449 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 195:
#line 1179 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            exp_ptr pair((yystack_[2].value.expression)->append((yystack_[0].value.expression))); (yystack_[2].value.expression) = nullptr; (yystack_[0].value.expression) = nullptr;
            (yylhs.value.expression) = new ASTfunction("rand+/-", std::move(pair), driver.mSeed, yystack_[2].location, yylhs.location);
        }
#line 2458 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 196:
#line 1184 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('+', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2464 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 197:
#line 1186 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('-', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2470 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 198:
#line 1188 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('_', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2476 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 199:
#line 1190 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('*', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2482 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 200:
#line 1192 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('/', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2488 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 201:
#line 1194 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('N', (yystack_[0].value.expression), nullptr); }
#line 2494 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 202:
#line 1196 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('P', (yystack_[0].value.expression), nullptr); }
#line 2500 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 203:
#line 1198 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('!', (yystack_[0].value.expression), nullptr); }
#line 2506 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 204:
#line 1200 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('^', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2512 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 205:
#line 1202 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('<', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2518 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 206:
#line 1204 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('L', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2524 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 207:
#line 1206 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('>', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2530 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 208:
#line 1208 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('G', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2536 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 209:
#line 1210 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('=', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2542 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 210:
#line 1212 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('n', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2548 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 211:
#line 1214 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('&', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2554 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 212:
#line 1216 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('|', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2560 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 213:
#line 1218 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASToperator('X', (yystack_[2].value.expression), (yystack_[0].value.expression)); }
#line 2566 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 214:
#line 1220 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = new ASTparen((yystack_[1].value.expression)); }
#line 2572 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 215:
#line 1222 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.expression) = (yystack_[0].value.mod); }
#line 2578 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 216:
#line 1226 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { 
            str_ptr func((yystack_[2].value.string)); (yystack_[2].value.string) = nullptr;
            (yylhs.value.expression) = driver.MakeFunction(std::move(func), nullptr, yystack_[2].location, yystack_[1].location + yystack_[0].location, false);
        }
#line 2587 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 217:
#line 1231 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { 
            str_ptr func((yystack_[3].value.string)); (yystack_[3].value.string) = nullptr;
            exp_ptr args((yystack_[1].value.expression));           (yystack_[1].value.expression) = nullptr;
            (yylhs.value.expression) = driver.MakeArray(std::move(func), std::move(args), yystack_[3].location, yystack_[1].location);
        }
#line 2597 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 218:
#line 1237 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { 
            str_ptr func(new std::string("if"));
            exp_ptr args((yystack_[1].value.expression)); (yystack_[1].value.expression) = nullptr;
            (yylhs.value.expression) = driver.MakeFunction(std::move(func), std::move(args), yystack_[3].location, yystack_[1].location, false);
        }
#line 2607 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 219:
#line 1243 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            str_ptr func((yystack_[3].value.string)); (yystack_[3].value.string) = nullptr;
            exp_ptr args(new ASTexpression(yylhs.location, false, false, AST::ReuseType));
            (yylhs.value.expression) = driver.MakeFunction(std::move(func), std::move(args), yystack_[3].location, yystack_[1].location, false);
        }
#line 2617 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 220:
#line 1249 "../../src-common/cfdg.ypp" // lalr1.cc:859
    {
            driver.pop_repContainer(nullptr);
            cont_ptr vars((yystack_[1].value.bodyObj)); (yystack_[1].value.bodyObj) = nullptr;
            exp_ptr exp((yystack_[0].value.expression)); (yystack_[0].value.expression) = nullptr;
            (yylhs.value.expression) = driver.MakeLet(yystack_[1].location, std::move(vars), std::move(exp));
        }
#line 2628 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 221:
#line 1256 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { 
            str_ptr var((yystack_[0].value.string)); (yystack_[0].value.string) = nullptr;
            (yylhs.value.expression) = driver.MakeVariable(*var, yystack_[0].location);
        }
#line 2637 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 222:
#line 1263 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.string) = (yystack_[0].value.string); }
#line 2643 "cfdg.tab.cpp" // lalr1.cc:859
    break;

  case 223:
#line 1265 "../../src-common/cfdg.ypp" // lalr1.cc:859
    { (yylhs.value.string) = (yystack_[0].value.string); }
#line 2649 "cfdg.tab.cpp" // lalr1.cc:859
    break;


#line 2653 "cfdg.tab.cpp" // lalr1.cc:859
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
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
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
    if (!yyla.empty ())
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
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
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
  CfdgParser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const short int CfdgParser::yypact_ninf_ = -287;

  const signed char CfdgParser::yytable_ninf_ = -91;

  const short int
  CfdgParser::yypact_[] =
  {
     323,  -287,  -287,    48,   667,   688,  -287,   240,  -287,     4,
      34,     9,    70,  -287,  -287,    24,   145,  -287,  -287,  -287,
    -287,  -287,  -287,  -287,  -287,     0,    66,  -287,    90,  -287,
     248,    55,   228,    63,     6,     0,    36,   145,    76,     0,
    -287,  -287,  -287,  -287,  -287,  -287,  -287,   497,  -287,   140,
    -287,  -287,  -287,   163,   175,  -287,  -287,   274,   105,   158,
     168,  -287,  -287,  -287,   199,  -287,  -287,  -287,  -287,  -287,
    -287,  -287,  -287,  -287,   205,   214,   223,   225,  -287,   241,
    -287,     7,   245,  -287,  -287,  -287,   223,   223,   291,  -287,
     283,   145,  -287,   260,  -287,   263,  -287,   276,   497,  -287,
     497,   497,   497,   277,  -287,   282,   295,   539,  -287,  -287,
     122,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,   123,
      33,   103,   311,   349,   214,  -287,   336,     7,  -287,   338,
      30,  -287,   147,  -287,   232,  -287,  -287,    -9,  -287,   340,
     344,  -287,  -287,  -287,   497,   378,   497,   298,   298,   298,
      75,  -287,   125,   246,  -287,   497,   497,   497,   497,   497,
     497,   497,   497,   497,   497,   497,   497,   497,   497,   497,
     497,   497,   497,   279,   455,   299,   302,   497,   421,    10,
     310,  -287,    60,  -287,   497,  -287,  -287,  -287,  -287,   352,
     214,   427,   427,   427,   304,   282,   205,   187,   267,   518,
     126,  -287,  -287,  -287,  -287,   315,  -287,  -287,  -287,    32,
       0,  -287,  -287,  -287,  -287,   359,    18,   253,  -287,  -287,
    -287,  -287,   191,     0,   307,  -287,   100,   539,  -287,  -287,
     118,  -287,   133,  -287,  -287,  -287,  -287,    30,  -287,  -287,
    -287,   165,   308,  -287,   167,   -28,  -287,   127,  -287,   362,
     364,  -287,   309,  -287,   539,   237,   237,   508,   508,   508,
     508,   628,   628,   608,   586,   563,   259,   259,   259,   298,
     298,   298,   205,   368,    19,   295,   497,   497,   295,   295,
    -287,  -287,   181,  -287,   295,  -287,   427,  -287,   365,  -287,
    -287,  -287,  -287,   214,   214,  -287,  -287,   324,  -287,  -287,
     518,   518,   497,   518,   144,  -287,  -287,  -287,  -287,  -287,
    -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,   320,  -287,
    -287,  -287,  -287,  -287,   497,  -287,   373,  -287,  -287,  -287,
    -287,  -287,  -287,   319,   476,   214,   497,   497,   170,   185,
    -287,   196,   427,  -287,   289,  -287,    11,  -287,  -287,   378,
    -287,  -287,   197,   328,   518,   518,  -287,     0,   131,   135,
     330,   539,  -287,    28,  -287,   198,  -287,   295,   295,   214,
    -287,  -287,  -287,  -287,   321,   497,  -287,  -287,   427,   201,
    -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,
      -7,  -287,  -287,  -287
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
       0,     0,    36,     0,   170,   221,   190,     0,     0,   191,
       0,     0,     0,   165,   215,     0,    55,   189,   192,    68,
       0,    97,    97,    32,    33,    34,    71,    31,    28,     0,
       0,     0,     0,     0,    49,    48,     0,     0,    67,     0,
       0,    75,     0,    85,    84,    91,    87,     0,    60,     0,
       0,    57,    45,    41,     0,     0,     0,   203,   201,   202,
       0,   165,     0,     0,   220,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   222,
       0,   223,     0,    69,     0,   116,   115,    96,   124,   117,
       0,     0,     0,     0,     0,     0,    95,     0,     0,     0,
       0,   161,   164,   160,   222,     0,    72,   146,   141,     0,
       0,   133,   134,   137,   139,   138,   222,     0,    79,   128,
      98,   130,     0,     0,     0,    94,     0,   178,    47,    59,
       0,    56,     0,    83,    81,    82,    80,     0,    90,    61,
      58,     0,     0,   216,     0,     0,   214,     0,   162,     0,
       0,   174,     0,   173,   188,   194,   195,   206,   205,   208,
     207,   209,   210,   211,   212,   213,   197,   196,   198,   199,
     200,   204,    95,     0,   221,   152,     0,     0,   156,   155,
     126,   125,     0,   127,    66,   118,     0,    97,   120,   109,
     121,   122,   113,     0,     0,    76,    77,   221,   179,   180,
       0,     0,     0,   166,   176,   182,   168,   169,   148,   142,
     147,   144,   145,   136,   135,   132,   131,   165,     0,    99,
     111,   129,   101,    93,     0,    92,    88,    88,    86,   218,
     219,   193,   217,     0,     0,     0,     0,     0,     0,     0,
     103,     0,     0,   140,     0,   154,     0,   106,   104,     0,
     184,   185,     0,   175,     0,     0,   167,     0,     0,     0,
       0,   177,   163,   221,   172,     0,   107,   151,   150,   153,
     157,   102,   119,   108,     0,     0,   123,   112,     0,     0,
     181,   186,   187,   149,   143,   100,   110,   171,   105,   159,
       0,   114,   183,   158
  };

  const short int
  CfdgParser::yypgoto_[] =
  {
    -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,
     381,   -19,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,
     382,  -143,  -287,  -287,  -287,   384,  -287,  -287,  -287,  -287,
    -287,  -287,  -287,   153,   204,   316,    84,  -188,  -100,    79,
     172,  -287,  -170,  -287,  -287,  -287,   -75,  -287,  -287,  -287,
    -287,  -287,    92,  -287,   193,  -287,  -118,  -287,  -287,  -287,
    -287,  -287,  -287,  -287,   -34,   -73,   -64,  -287,  -101,   208,
    -287,    71,  -287,  -138,  -286,   -99,   -57,  -175,   -90
  };

  const short int
  CfdgParser::yydefgoto_[] =
  {
      -1,     3,     4,     5,    40,    19,    20,    41,    21,    42,
      22,    68,    91,    44,    23,    24,    25,    45,    46,    47,
     184,   185,    49,    50,    51,    26,    27,    53,    54,    55,
      56,    28,    29,   136,   137,   128,    82,   124,   110,   122,
     219,   186,   288,   321,   346,   377,   289,   342,   188,   220,
     221,   189,   121,   310,   207,   208,   209,   357,   190,   191,
     192,   193,   194,   378,    71,   104,   119,   202,   105,   154,
     252,   253,   303,   226,   304,   106,   107,   108,   196
  };

  const short int
  CfdgParser::yytable_[] =
  {
      83,    84,   125,   150,   222,    92,   120,   244,   294,   195,
     251,   197,   198,   132,   350,   351,    80,   353,    89,    61,
      85,   155,   290,   291,   305,   374,   133,   375,   314,   337,
      59,   210,   223,   134,    63,   187,   132,   332,    85,   152,
     237,   147,   155,   148,   149,   241,    85,   245,     6,   133,
      64,   228,   199,   200,   238,    86,   134,   393,   204,    69,
      60,    70,    87,   181,    81,    69,   227,    70,   381,   382,
     135,   280,   143,   376,    76,   275,   315,   145,   278,   279,
      62,    77,    65,   272,   335,   284,   145,   247,   227,    79,
     195,   195,   195,   309,    81,   203,   195,   195,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   343,   286,   282,   210,
      88,   283,   187,   187,   155,   305,   305,    72,   305,   204,
     173,   205,   223,   174,   181,   175,    90,   176,   246,   177,
      94,   178,   199,   200,   199,   200,   199,   200,   179,   324,
     180,    73,   306,   181,   199,   200,   307,   204,   182,   205,
     126,   129,   181,   325,   115,   206,   233,   237,   354,   355,
     139,   140,   372,   234,    66,    67,   312,   338,   339,   305,
     305,   326,   237,   341,   183,   195,   116,   344,   201,   322,
     248,   251,   333,   384,    93,   173,   327,   385,   174,    94,
     175,   109,   176,   352,   177,    94,   178,    95,   391,    96,
     356,   379,    97,   179,   155,   180,   324,   204,   181,   155,
     347,   348,   181,   182,   111,    98,   117,   318,   329,    99,
     331,   100,   101,   369,   155,   365,   112,   367,   368,   102,
     103,   195,   222,   195,   340,   155,   155,   155,   370,   295,
     324,   235,   319,   359,    59,   138,    78,   118,   236,   371,
     380,   387,   366,   123,   392,   249,    57,   361,   210,   187,
     223,    58,   250,   103,    74,   173,   390,   195,   174,    75,
     175,    81,   176,   127,   177,    94,   178,   167,   168,   169,
     170,   171,   227,   179,   172,   180,   388,   173,   181,   130,
     174,   141,   175,   182,   176,   204,   177,    94,   178,   142,
     181,   316,   170,   171,   317,   179,   172,   180,   144,   211,
     181,   145,   212,   383,   213,   182,   214,     1,     2,   296,
     215,   230,   113,   114,   232,   146,   151,   216,   211,   205,
     153,   212,   181,   213,   155,   214,   229,   217,   231,   215,
     239,   373,   354,   355,   240,   172,   216,   276,   205,   224,
     277,   181,    93,   281,   285,   292,   217,    94,   308,   313,
     323,   330,    80,   218,    85,    95,   334,    96,   336,   345,
      97,   317,   349,   -90,   362,   389,    43,    48,   242,    52,
     328,    93,   386,    98,   320,   131,    94,    99,   360,   100,
     101,   358,   311,   293,    95,   364,    96,   102,   103,    97,
       0,     0,   225,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    98,     0,     0,     0,    99,     0,   100,   101,
       0,    80,     0,     0,    93,   173,   102,   103,   174,    94,
     175,   243,   176,     0,   177,    94,   178,    95,     0,    96,
       0,     0,    97,   179,     0,   180,     0,     0,   181,     0,
       0,     0,     0,   182,     0,    98,     0,     0,    93,    99,
       0,   100,   101,    94,   273,     0,     0,     0,     0,   102,
     103,   274,     0,    96,     0,     0,    97,     0,   287,    93,
       0,     0,     0,     0,    94,   249,     0,     0,     0,    98,
       0,     0,   363,    99,    96,   100,   101,    97,     0,     0,
      93,     0,     0,   102,   103,    94,     0,     0,     0,     0,
      98,     0,     0,    95,    99,    96,   100,   101,    97,     0,
       0,    93,   156,   157,   102,   103,    94,     0,     0,     0,
       0,    98,     0,     0,   297,    99,   298,   100,   101,    97,
       0,     0,     0,     0,     0,   102,   103,     0,   167,   168,
     169,   170,   171,   156,   157,   172,   299,     0,   300,   301,
       0,     0,     0,     0,     0,     0,   302,   158,   159,   160,
     161,   162,   163,     0,   164,   165,   166,   156,   157,   167,
     168,   169,   170,   171,     0,     0,   172,     0,     0,     0,
       0,   158,   159,   160,   161,   162,   163,     0,   164,   165,
     156,   157,     0,   167,   168,   169,   170,   171,     0,     0,
     172,     0,     0,     0,   158,   159,   160,   161,   162,   163,
       0,   164,   156,   157,     0,     0,   167,   168,   169,   170,
     171,     0,     0,   172,     0,     0,   158,   159,   160,   161,
     162,   163,   156,   157,     0,     0,     0,     0,   167,   168,
     169,   170,   171,     0,     0,   172,   158,   159,   160,   161,
       7,     0,     0,     8,     9,    10,     0,     0,   167,   168,
     169,   170,   171,     0,     0,   172,    11,    12,    13,     0,
      14,    30,     0,    15,    31,    32,    33,     0,     0,    16,
      17,    18,     0,     0,     0,     0,     0,    34,     0,    35,
       0,    14,     0,     0,    36,     0,     0,     0,     0,     0,
      37,    38,    39
  };

  const short int
  CfdgParser::yycheck_[] =
  {
      34,    35,    75,   102,   122,    39,    70,   145,   196,   110,
     153,   111,   112,     6,   300,   301,    10,   303,    37,    10,
      10,    49,   192,   193,   199,    14,    19,    16,    10,    10,
      26,   121,   122,    26,    10,   110,     6,    65,    10,   103,
      49,    98,    49,   100,   101,   144,    10,   146,     0,    19,
      26,   124,    19,    20,    63,    19,    26,    64,    26,    59,
      26,    61,    26,    31,    58,    59,   123,    61,   354,   355,
      63,    61,    91,    62,    19,   174,    58,    58,   177,   178,
      10,    26,    58,   173,   272,   184,    58,   151,   145,    26,
     191,   192,   193,    61,    58,    62,   197,   198,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   286,   190,    58,   209,
      36,    61,   197,   198,    49,   300,   301,    61,   303,    26,
       8,    28,   222,    11,    31,    13,    60,    15,    63,    17,
      18,    19,    19,    20,    19,    20,    19,    20,    26,    49,
      28,    61,    26,    31,    19,    20,    30,    26,    36,    28,
      76,    77,    31,    63,    59,    62,    19,    49,    24,    25,
      86,    87,   342,    26,    29,    30,   210,   276,   277,   354,
     355,    63,    49,   282,    62,   286,    28,   287,    65,   223,
      65,   334,    65,    62,    13,     8,    63,    62,    11,    18,
      13,    61,    15,   302,    17,    18,    19,    26,   378,    28,
      66,   349,    31,    26,    49,    28,    49,    26,    31,    49,
     293,   294,    31,    36,    61,    44,    58,    36,    63,    48,
      63,    50,    51,    63,    49,   334,    61,   336,   337,    58,
      59,   342,   360,   344,    63,    49,    49,    49,    63,    62,
      49,    19,    61,   317,    26,    10,    28,    58,    26,    63,
      63,    63,   335,    58,    63,    19,    26,   324,   358,   344,
     360,    31,    26,    59,    26,     8,   375,   378,    11,    31,
      13,    58,    15,    58,    17,    18,    19,    50,    51,    52,
      53,    54,   349,    26,    57,    28,   369,     8,    31,    58,
      11,    10,    13,    36,    15,    26,    17,    18,    19,    26,
      31,    58,    53,    54,    61,    26,    57,    28,    58,     8,
      31,    58,    11,   357,    13,    36,    15,     4,     5,    62,
      19,   127,    58,    59,   130,    59,    59,    26,     8,    28,
      58,    11,    31,    13,    49,    15,    10,    36,    10,    19,
      10,    62,    24,    25,    10,    57,    26,    58,    28,    10,
      58,    31,    13,    53,    12,    61,    36,    18,    53,    10,
      63,    63,    10,    62,    10,    26,    67,    28,    10,    14,
      31,    61,    58,    10,    65,    64,     5,     5,    10,     5,
     237,    13,    62,    44,   222,    79,    18,    48,   319,    50,
      51,   309,   209,   195,    26,   334,    28,    58,    59,    31,
      -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    48,    -1,    50,    51,
      -1,    10,    -1,    -1,    13,     8,    58,    59,    11,    18,
      13,    63,    15,    -1,    17,    18,    19,    26,    -1,    28,
      -1,    -1,    31,    26,    -1,    28,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    36,    -1,    44,    -1,    -1,    13,    48,
      -1,    50,    51,    18,    19,    -1,    -1,    -1,    -1,    58,
      59,    26,    -1,    28,    -1,    -1,    31,    -1,    61,    13,
      -1,    -1,    -1,    -1,    18,    19,    -1,    -1,    -1,    44,
      -1,    -1,    26,    48,    28,    50,    51,    31,    -1,    -1,
      13,    -1,    -1,    58,    59,    18,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    26,    48,    28,    50,    51,    31,    -1,
      -1,    13,    24,    25,    58,    59,    18,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    26,    48,    28,    50,    51,    31,
      -1,    -1,    -1,    -1,    -1,    58,    59,    -1,    50,    51,
      52,    53,    54,    24,    25,    57,    48,    -1,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    38,    39,    40,
      41,    42,    43,    -1,    45,    46,    47,    24,    25,    50,
      51,    52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    -1,    45,    46,
      24,    25,    -1,    50,    51,    52,    53,    54,    -1,    -1,
      57,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      -1,    45,    24,    25,    -1,    -1,    50,    51,    52,    53,
      54,    -1,    -1,    57,    -1,    -1,    38,    39,    40,    41,
      42,    43,    24,    25,    -1,    -1,    -1,    -1,    50,    51,
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
      50,    51,    58,    59,   133,   136,   143,   144,   145,    61,
     106,    61,    61,    58,    59,    59,    28,    58,    58,   134,
     134,   120,   107,    58,   105,   133,   104,    58,   103,   104,
      58,   103,     6,    19,    26,    63,   101,   102,    10,   104,
     104,    10,    26,    79,    58,    58,    59,   144,   144,   144,
     143,    59,   134,    58,   137,    49,    24,    25,    38,    39,
      40,    41,    42,    43,    45,    46,    47,    50,    51,    52,
      53,    54,    57,     8,    11,    13,    15,    17,    19,    26,
      28,    31,    36,    62,    88,    89,   109,   114,   116,   119,
     126,   127,   128,   129,   130,   136,   146,   106,   106,    19,
      20,    65,   135,    62,    26,    28,    62,   122,   123,   124,
     146,     8,    11,    13,    15,    19,    26,    36,    62,   108,
     117,   118,   124,   146,    10,    63,   141,   144,   133,    10,
     102,    10,   102,    19,    26,    19,    26,    49,    63,    10,
      10,   143,    10,    63,   141,   143,    63,   134,    65,    19,
      26,    89,   138,   139,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   146,    19,    26,   143,    58,    58,   143,   143,
      61,    53,    58,    61,   143,    12,   133,    61,   110,   114,
     110,   110,    61,   137,   105,    62,    62,    26,    28,    48,
      50,    51,    58,   140,   142,   145,    26,    30,    53,    61,
     121,   122,   132,    10,    10,    58,    58,    61,    36,    61,
     108,   111,   132,    63,    49,    63,    63,    63,   101,    63,
      63,    63,    65,    65,    67,   105,    10,    10,   143,   143,
      63,   143,   115,   110,   106,    14,   112,   133,   133,    58,
     142,   142,   143,   142,    24,    25,    66,   125,   120,   134,
     107,   144,    65,    26,   139,   143,   133,   143,   143,    63,
      63,    63,   110,    62,    14,    16,    62,   113,   131,   141,
      63,   142,   142,   132,    62,    62,    62,    63,   133,    64,
     143,   110,    63,    64
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
     142,   142,   142,   142,   142,   142,   142,   142,   143,   143,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   145,   145,   145,   145,
     145,   145,   146,   146
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
       1,     3,     1,     4,     2,     2,     3,     3,     3,     1,
       1,     1,     1,     4,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     3,     4,     4,     4,
       2,     1,     1,     1
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
  "initialization_v2", "directive_v2", "directive_num",
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
  "exp2", "exp3", "expfunc", "shapeName", YY_NULLPTR
  };


  const unsigned short int
  CfdgParser::yyrline_[] =
  {
       0,   176,   176,   176,   179,   184,   188,   193,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   212,   213,   214,
     215,   216,   217,   218,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   244,   245,   246,   247,   248,
     252,   261,   272,   279,   279,   282,   283,   287,   296,   304,
     314,   323,   331,   333,   335,   352,   383,   392,   401,   410,
     415,   420,   428,   440,   446,   450,   457,   475,   482,   490,
     498,   506,   520,   528,   535,   547,   559,   567,   576,   588,
     595,   601,   607,   612,   616,   622,   628,   629,   633,   634,
     638,   639,   643,   644,   645,   646,   650,   653,   657,   660,
     664,   671,   680,   686,   692,   700,   709,   719,   728,   730,
     736,   738,   744,   745,   749,   756,   760,   764,   773,   773,
     785,   794,   803,   812,   819,   826,   827,   828,   832,   834,
     842,   854,   855,   856,   857,   858,   859,   860,   861,   862,
     866,   875,   878,   882,   884,   890,   899,   901,   912,   912,
     927,   935,   944,   954,   962,   970,   978,   988,   996,  1007,
    1018,  1023,  1030,  1035,  1042,  1047,  1054,  1058,  1068,  1073,
    1080,  1087,  1093,  1095,  1099,  1105,  1109,  1116,  1120,  1126,
    1128,  1130,  1132,  1134,  1140,  1142,  1144,  1149,  1156,  1158,
    1162,  1164,  1166,  1168,  1174,  1179,  1184,  1186,  1188,  1190,
    1192,  1194,  1196,  1198,  1200,  1202,  1204,  1206,  1208,  1210,
    1212,  1214,  1216,  1218,  1220,  1222,  1226,  1231,  1237,  1243,
    1249,  1256,  1263,  1265
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
#line 3346 "cfdg.tab.cpp" // lalr1.cc:1167
#line 1268 "../../src-common/cfdg.ypp" // lalr1.cc:1168


void yy::CfdgParser::error(const CfdgParser::location_type& l, const std::string& m)
{
    driver.error(l, m);
}
