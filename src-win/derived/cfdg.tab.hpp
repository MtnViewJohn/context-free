/* A Bison parser, made by GNU Bison 2.6.5.993-06ec-dirty.  */

/* Skeleton interface for Bison LALR(1) parsers in C++

   Copyright (C) 2002-2012 Free Software Foundation, Inc.

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

/**
 ** \file cfdg.tab.hpp
 ** Define the yy::parser class.
 */

/* C++ LALR(1) parser skeleton written by Akim Demaille.  */

#ifndef YY_YY_CFDG_TAB_HPP_INCLUDED
# define YY_YY_CFDG_TAB_HPP_INCLUDED


# include <deque>
# include <iostream>
# include <stdexcept>
# include <string>
# include "stack.hh"
# include "location.hh"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif


namespace yy {
/* Line 356 of lalr1.cc  */
#line 60 "cfdg.tab.hpp"





  /// A Bison parser.
  class CfdgParser
  {
  public:
#ifndef YYSTYPE
    /// Symbol semantic values.
    union semantic_type
    {/* Line 356 of lalr1.cc  */
#line 64 "../../src-common/cfdg.ypp"

    int modToken;
    std::string*  string;
    AST::ASTexpression* expression;
    AST::ASTmodTerm* term;
    AST::ASTmodification* mod;
    AST::ASTreplacement* component;
    AST::ASTshape* shapeObj;
    AST::ASTloop* loopObj;
    AST::ASTif* ifObj;
    AST::ASTswitch* switchObj;
    AST::ASTruleSpecifier* ruleSpec;
    AST::ASTrule* ruleObj;
    AST::ASTrepContainer* bodyObj;


/* Line 356 of lalr1.cc  */
#line 92 "cfdg.tab.hpp"
    };
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        STARTSHAPE = 258,
        CFDG2 = 259,
        CFDG3 = 260,
        SHAPE = 261,
        RULE = 262,
        PATH = 263,
        DEFINE = 264,
        BECOMES = 265,
        LOOP = 266,
        FINALLY = 267,
        IF = 268,
        ELSE = 269,
        SWITCH = 270,
        CASE = 271,
        CLONE = 272,
        LET = 273,
        MODTYPE = 274,
        PARAM = 275,
        BACKGROUND = 276,
        BADEOF = 277,
        GOODEOF = 278,
        RANGEOP = 279,
        PLUSMINUSOP = 280,
        USER_STRING = 281,
        USER_INTEGER = 282,
        USER_RATIONAL = 283,
        USER_FILENAME = 284,
        USER_QSTRING = 285,
        USER_ARRAYNAME = 286,
        INCLUDE = 287,
        IMPORT = 288,
        TILE = 289,
        PARAMETERS = 290,
        USER_PATHOP = 291,
        STROKEWIDTH = 292,
        LE = 293,
        LT = 294,
        GE = 295,
        GT = 296,
        EQ = 297,
        NEQ = 298,
        NOT = 299,
        AND = 300,
        OR = 301,
        XOR = 302,
        CF_INFINITY = 303,
        POS = 304,
        NEG = 305
      };
    };

    /// Token type.
    typedef token::yytokentype token_type;

    /// A complete symbol, with its type.
    template <typename Exact>
    struct symbol_base_type
    {
      /// Default constructor.
      inline symbol_base_type ();

      /// Constructor.
      inline symbol_base_type (const location_type& l);
      inline symbol_base_type (const semantic_type& v, const location_type& l);

      /// Return this with its exact type.
      const Exact& self () const;
      Exact& self ();

      /// Return the type of this symbol.
      int type_get () const;

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;
    };

    /// External form of a symbol: its type and attributes.
    struct symbol_type : symbol_base_type<symbol_type>
    {
      /// The parent class.
      typedef symbol_base_type<symbol_type> super_type;

      /// Default constructor.
      inline symbol_type ();

      /// Constructor for tokens with semantic value.
      inline symbol_type (token_type t, const semantic_type& v, const location_type& l);

      /// Constructor for valueless tokens.
      inline symbol_type (token_type t, const location_type& l);

      /// The symbol type.
      int type;

      /// The symbol type.
      inline int type_get_ () const;

      /// The token.
      inline token_type token () const;
    };

    /// Build a parser object.
    CfdgParser (class Builder& driver_yyarg);
    virtual ~CfdgParser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yytoken   the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate, int yytoken);

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yylhs     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yylhs);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    /// Internal symbol numbers.
    typedef unsigned char token_number_type;
    static const short int yypact_ninf_;
    static const signed char yytable_ninf_;

    // Tables.
  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.    */
  static const short int yypact_[];

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE does not specify something else to do.  Zero means the default
     is an error.    */
  static const unsigned char yydefact_[];

  /* YYPGOTO[NTERM-NUM].    */
  static const short int yypgoto_[];

  /* YYDEFGOTO[NTERM-NUM].    */
  static const short int yydefgoto_[];

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF, syntax error.    */
  static const short int yytable_[];

  static const short int yycheck_[];

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.    */
  static const unsigned char yystos_[];

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.    */
  static const unsigned char yyr1_[];

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.    */
  static const unsigned char yyr2_[];


#if YYDEBUG
    /// For a symbol, its name in clear.
    static const char* const yytname_[];

  /* YYRLINEYYN -- Source line where rule number YYN was defined.    */
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;
#endif // YYDEBUG

    /// Convert a scanner token number \a t to a symbol number.
    static inline token_number_type yytranslate_ (int t);

#if YYDEBUG
    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Exact>
    void yy_print_ (std::ostream& yyo,
                    const symbol_base_type<Exact>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param s         The symbol.
    template <typename Exact>
    inline void yy_destroy_ (const char* yymsg,
                             symbol_base_type<Exact>& yysym) const;

  private:
    /// Element of the stack: a state and its attributes.
    struct stack_symbol_type : symbol_base_type<stack_symbol_type>
    {
      /// The parent class.
      typedef symbol_base_type<stack_symbol_type> super_type;

      /// Default constructor.
      inline stack_symbol_type ();

      /// Constructor.
      inline stack_symbol_type (state_type s, const semantic_type& v, const location_type& l);

      /// The state.
      state_type state;

      /// The type (corresponding to \a state).
      inline int type_get_ () const;
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    inline void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    inline void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    inline void yypop_ (unsigned int n = 1);

    /* Constants.  */
    enum
    {
      yyeof_ = 0,
      yylast_ = 1331,           //< Last index in yytable_.
      yynnts_ = 80,  //< Number of nonterminal symbols.
      yyempty_ = -2,
      yyfinal_ = 6, //< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 68    //< Number of tokens.
    };


    /* User arguments.  */
    class Builder& driver;
  };



} // yy
/* Line 356 of lalr1.cc  */
#line 409 "cfdg.tab.hpp"




#endif /* !YY_YY_CFDG_TAB_HPP_INCLUDED  */
