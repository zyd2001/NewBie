// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton interface for Bison LALR(1) parsers in C++

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

/**
 ** \file Parser.hpp
 ** Define the zyd2001::NewBie::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
// //                    "%code requires" blocks.


#include "NewBie_Lang.hpp"
#include "NewBie.hpp"




# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"
# include "location.hh"

#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif


namespace zyd2001 { namespace NewBie {




  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {}

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;
  };


  /// A Bison parser.
  class Parser
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // arguments_list
      char dummy1[sizeof(zyd2001::NewBie::ArgumentsList)];

      // declaration_item
      char dummy2[sizeof(zyd2001::NewBie::DeclarationStatementItem)];

      // declaration_item_list
      char dummy3[sizeof(zyd2001::NewBie::DeclarationStatementItemList)];

      // INT_LITERAL
      // STRING_LITERAL
      // DOUBLE_LITERAL
      // BOOL_LITERAL
      // expression
      // expression_optional
      // binary_expression
      // unary_expression
      // function_call_expression
      // primary_expression
      char dummy4[sizeof(zyd2001::NewBie::Expression)];

      // IDENTIFIER
      char dummy5[sizeof(zyd2001::NewBie::Identifier)];

      // parameter
      char dummy6[sizeof(zyd2001::NewBie::Parameter)];

      // parameters_list
      char dummy7[sizeof(zyd2001::NewBie::ParametersList)];

      // statement
      // block
      char dummy8[sizeof(zyd2001::NewBie::Statement)];

      // statements_list
      char dummy9[sizeof(zyd2001::NewBie::StatementsList)];

      // type_tag
      char dummy10[sizeof(zyd2001::NewBie::ValueType)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
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
        TOKEN_END = 0,
        TOKEN_LOGICAL_AND = 258,
        TOKEN_LOGICAL_OR = 259,
        TOKEN_EQ = 260,
        TOKEN_NE = 261,
        TOKEN_GT = 262,
        TOKEN_GE = 263,
        TOKEN_LT = 264,
        TOKEN_LE = 265,
        TOKEN_ADD = 266,
        TOKEN_SUB = 267,
        TOKEN_MUL = 268,
        TOKEN_DIV = 269,
        TOKEN_MOD = 270,
        TOKEN_UMINUS = 271,
        TOKEN_INT_LITERAL = 272,
        TOKEN_STRING_LITERAL = 273,
        TOKEN_DOUBLE_LITERAL = 274,
        TOKEN_BOOL_LITERAL = 275,
        TOKEN_IDENTIFIER = 276,
        TOKEN_INT = 277,
        TOKEN_DOUBLE = 278,
        TOKEN_BOOL = 279,
        TOKEN_STRING = 280,
        TOKEN_ARRAY = 281,
        TOKEN_VAR = 282,
        TOKEN_GLOBAL = 283,
        TOKEN_IF = 284,
        TOKEN_ELSE = 285,
        TOKEN_ELSEIF = 286,
        TOKEN_FOR = 287,
        TOKEN_IN = 288,
        TOKEN_CLASS = 289,
        TOKEN_RETURN = 290,
        TOKEN_BREAK = 291,
        TOKEN_CONTINUE = 292,
        TOKEN_LP = 293,
        TOKEN_RP = 294,
        TOKEN_LC = 295,
        TOKEN_RC = 296,
        TOKEN_LB = 297,
        TOKEN_RB = 298,
        TOKEN_SEMICOLON = 299,
        TOKEN_COMMA = 300,
        TOKEN_ASSIGN = 301,
        TOKEN_EXCLAMATION = 302,
        TOKEN_DOT = 303,
        TOKEN_ADD_ASSIGN = 304,
        TOKEN_SUB_ASSIGN = 305,
        TOKEN_MUL_ASSIGN = 306,
        TOKEN_DIV_ASSIGN = 307,
        TOKEN_MOD_ASSIGN = 308,
        TOKEN_INCREMENT = 309,
        TOKEN_DECREMENT = 310,
        TOKEN_PUBLIC = 311,
        TOKEN_PROTECTED = 312,
        TOKEN_PRIVATE = 313,
        TOKEN_REVERSE = 314
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t, const location_type& l);

  basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::ArgumentsList v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::DeclarationStatementItem v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::DeclarationStatementItemList v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::Expression v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::Identifier v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::Parameter v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::ParametersList v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::Statement v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::StatementsList v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::ValueType v, const location_type& l);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_END (const location_type& l);

    static inline
    symbol_type
    make_LOGICAL_AND (const location_type& l);

    static inline
    symbol_type
    make_LOGICAL_OR (const location_type& l);

    static inline
    symbol_type
    make_EQ (const location_type& l);

    static inline
    symbol_type
    make_NE (const location_type& l);

    static inline
    symbol_type
    make_GT (const location_type& l);

    static inline
    symbol_type
    make_GE (const location_type& l);

    static inline
    symbol_type
    make_LT (const location_type& l);

    static inline
    symbol_type
    make_LE (const location_type& l);

    static inline
    symbol_type
    make_ADD (const location_type& l);

    static inline
    symbol_type
    make_SUB (const location_type& l);

    static inline
    symbol_type
    make_MUL (const location_type& l);

    static inline
    symbol_type
    make_DIV (const location_type& l);

    static inline
    symbol_type
    make_MOD (const location_type& l);

    static inline
    symbol_type
    make_UMINUS (const location_type& l);

    static inline
    symbol_type
    make_INT_LITERAL (const zyd2001::NewBie::Expression& v, const location_type& l);

    static inline
    symbol_type
    make_STRING_LITERAL (const zyd2001::NewBie::Expression& v, const location_type& l);

    static inline
    symbol_type
    make_DOUBLE_LITERAL (const zyd2001::NewBie::Expression& v, const location_type& l);

    static inline
    symbol_type
    make_BOOL_LITERAL (const zyd2001::NewBie::Expression& v, const location_type& l);

    static inline
    symbol_type
    make_IDENTIFIER (const zyd2001::NewBie::Identifier& v, const location_type& l);

    static inline
    symbol_type
    make_INT (const location_type& l);

    static inline
    symbol_type
    make_DOUBLE (const location_type& l);

    static inline
    symbol_type
    make_BOOL (const location_type& l);

    static inline
    symbol_type
    make_STRING (const location_type& l);

    static inline
    symbol_type
    make_ARRAY (const location_type& l);

    static inline
    symbol_type
    make_VAR (const location_type& l);

    static inline
    symbol_type
    make_GLOBAL (const location_type& l);

    static inline
    symbol_type
    make_IF (const location_type& l);

    static inline
    symbol_type
    make_ELSE (const location_type& l);

    static inline
    symbol_type
    make_ELSEIF (const location_type& l);

    static inline
    symbol_type
    make_FOR (const location_type& l);

    static inline
    symbol_type
    make_IN (const location_type& l);

    static inline
    symbol_type
    make_CLASS (const location_type& l);

    static inline
    symbol_type
    make_RETURN (const location_type& l);

    static inline
    symbol_type
    make_BREAK (const location_type& l);

    static inline
    symbol_type
    make_CONTINUE (const location_type& l);

    static inline
    symbol_type
    make_LP (const location_type& l);

    static inline
    symbol_type
    make_RP (const location_type& l);

    static inline
    symbol_type
    make_LC (const location_type& l);

    static inline
    symbol_type
    make_RC (const location_type& l);

    static inline
    symbol_type
    make_LB (const location_type& l);

    static inline
    symbol_type
    make_RB (const location_type& l);

    static inline
    symbol_type
    make_SEMICOLON (const location_type& l);

    static inline
    symbol_type
    make_COMMA (const location_type& l);

    static inline
    symbol_type
    make_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_EXCLAMATION (const location_type& l);

    static inline
    symbol_type
    make_DOT (const location_type& l);

    static inline
    symbol_type
    make_ADD_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_SUB_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_MUL_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_DIV_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_MOD_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_INCREMENT (const location_type& l);

    static inline
    symbol_type
    make_DECREMENT (const location_type& l);

    static inline
    symbol_type
    make_PUBLIC (const location_type& l);

    static inline
    symbol_type
    make_PROTECTED (const location_type& l);

    static inline
    symbol_type
    make_PRIVATE (const location_type& l);

    static inline
    symbol_type
    make_REVERSE (const location_type& l);


    /// Build a parser object.
    Parser (zyd2001::NewBie::InterpreterImp &inter_yyarg, yyscan_t scanner_yyarg);
    virtual ~Parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
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
    /// This class is not copyable.
    Parser (const Parser&);
    Parser& operator= (const Parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const signed char yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const signed char yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned char yytable_[];

  static const signed char yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
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
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 367,     ///< Last index in yytable_.
      yynnts_ = 17,  ///< Number of nonterminal symbols.
      yyfinal_ = 50, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 60  ///< Number of tokens.
    };


    // User arguments.
    zyd2001::NewBie::InterpreterImp &inter;
    yyscan_t scanner;
  };

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59
    };
    const unsigned int user_token_number_max_ = 314;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 74: // arguments_list
        value.copy< zyd2001::NewBie::ArgumentsList > (other.value);
        break;

      case 64: // declaration_item
        value.copy< zyd2001::NewBie::DeclarationStatementItem > (other.value);
        break;

      case 65: // declaration_item_list
        value.copy< zyd2001::NewBie::DeclarationStatementItemList > (other.value);
        break;

      case 17: // INT_LITERAL
      case 18: // STRING_LITERAL
      case 19: // DOUBLE_LITERAL
      case 20: // BOOL_LITERAL
      case 66: // expression
      case 67: // expression_optional
      case 68: // binary_expression
      case 69: // unary_expression
      case 70: // function_call_expression
      case 71: // primary_expression
        value.copy< zyd2001::NewBie::Expression > (other.value);
        break;

      case 21: // IDENTIFIER
        value.copy< zyd2001::NewBie::Identifier > (other.value);
        break;

      case 75: // parameter
        value.copy< zyd2001::NewBie::Parameter > (other.value);
        break;

      case 76: // parameters_list
        value.copy< zyd2001::NewBie::ParametersList > (other.value);
        break;

      case 63: // statement
      case 73: // block
        value.copy< zyd2001::NewBie::Statement > (other.value);
        break;

      case 62: // statements_list
        value.copy< zyd2001::NewBie::StatementsList > (other.value);
        break;

      case 72: // type_tag
        value.copy< zyd2001::NewBie::ValueType > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 74: // arguments_list
        value.copy< zyd2001::NewBie::ArgumentsList > (v);
        break;

      case 64: // declaration_item
        value.copy< zyd2001::NewBie::DeclarationStatementItem > (v);
        break;

      case 65: // declaration_item_list
        value.copy< zyd2001::NewBie::DeclarationStatementItemList > (v);
        break;

      case 17: // INT_LITERAL
      case 18: // STRING_LITERAL
      case 19: // DOUBLE_LITERAL
      case 20: // BOOL_LITERAL
      case 66: // expression
      case 67: // expression_optional
      case 68: // binary_expression
      case 69: // unary_expression
      case 70: // function_call_expression
      case 71: // primary_expression
        value.copy< zyd2001::NewBie::Expression > (v);
        break;

      case 21: // IDENTIFIER
        value.copy< zyd2001::NewBie::Identifier > (v);
        break;

      case 75: // parameter
        value.copy< zyd2001::NewBie::Parameter > (v);
        break;

      case 76: // parameters_list
        value.copy< zyd2001::NewBie::ParametersList > (v);
        break;

      case 63: // statement
      case 73: // block
        value.copy< zyd2001::NewBie::Statement > (v);
        break;

      case 62: // statements_list
        value.copy< zyd2001::NewBie::StatementsList > (v);
        break;

      case 72: // type_tag
        value.copy< zyd2001::NewBie::ValueType > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::ArgumentsList v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::DeclarationStatementItem v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::DeclarationStatementItemList v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::Expression v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::Identifier v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::Parameter v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::ParametersList v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::Statement v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::StatementsList v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const zyd2001::NewBie::ValueType v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 74: // arguments_list
        value.template destroy< zyd2001::NewBie::ArgumentsList > ();
        break;

      case 64: // declaration_item
        value.template destroy< zyd2001::NewBie::DeclarationStatementItem > ();
        break;

      case 65: // declaration_item_list
        value.template destroy< zyd2001::NewBie::DeclarationStatementItemList > ();
        break;

      case 17: // INT_LITERAL
      case 18: // STRING_LITERAL
      case 19: // DOUBLE_LITERAL
      case 20: // BOOL_LITERAL
      case 66: // expression
      case 67: // expression_optional
      case 68: // binary_expression
      case 69: // unary_expression
      case 70: // function_call_expression
      case 71: // primary_expression
        value.template destroy< zyd2001::NewBie::Expression > ();
        break;

      case 21: // IDENTIFIER
        value.template destroy< zyd2001::NewBie::Identifier > ();
        break;

      case 75: // parameter
        value.template destroy< zyd2001::NewBie::Parameter > ();
        break;

      case 76: // parameters_list
        value.template destroy< zyd2001::NewBie::ParametersList > ();
        break;

      case 63: // statement
      case 73: // block
        value.template destroy< zyd2001::NewBie::Statement > ();
        break;

      case 62: // statements_list
        value.template destroy< zyd2001::NewBie::StatementsList > ();
        break;

      case 72: // type_tag
        value.template destroy< zyd2001::NewBie::ValueType > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 74: // arguments_list
        value.move< zyd2001::NewBie::ArgumentsList > (s.value);
        break;

      case 64: // declaration_item
        value.move< zyd2001::NewBie::DeclarationStatementItem > (s.value);
        break;

      case 65: // declaration_item_list
        value.move< zyd2001::NewBie::DeclarationStatementItemList > (s.value);
        break;

      case 17: // INT_LITERAL
      case 18: // STRING_LITERAL
      case 19: // DOUBLE_LITERAL
      case 20: // BOOL_LITERAL
      case 66: // expression
      case 67: // expression_optional
      case 68: // binary_expression
      case 69: // unary_expression
      case 70: // function_call_expression
      case 71: // primary_expression
        value.move< zyd2001::NewBie::Expression > (s.value);
        break;

      case 21: // IDENTIFIER
        value.move< zyd2001::NewBie::Identifier > (s.value);
        break;

      case 75: // parameter
        value.move< zyd2001::NewBie::Parameter > (s.value);
        break;

      case 76: // parameters_list
        value.move< zyd2001::NewBie::ParametersList > (s.value);
        break;

      case 63: // statement
      case 73: // block
        value.move< zyd2001::NewBie::Statement > (s.value);
        break;

      case 62: // statements_list
        value.move< zyd2001::NewBie::StatementsList > (s.value);
        break;

      case 72: // type_tag
        value.move< zyd2001::NewBie::ValueType > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }

  inline
  Parser::token_type
  Parser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  Parser::symbol_type
  Parser::make_END (const location_type& l)
  {
    return symbol_type (token::TOKEN_END, l);
  }

  Parser::symbol_type
  Parser::make_LOGICAL_AND (const location_type& l)
  {
    return symbol_type (token::TOKEN_LOGICAL_AND, l);
  }

  Parser::symbol_type
  Parser::make_LOGICAL_OR (const location_type& l)
  {
    return symbol_type (token::TOKEN_LOGICAL_OR, l);
  }

  Parser::symbol_type
  Parser::make_EQ (const location_type& l)
  {
    return symbol_type (token::TOKEN_EQ, l);
  }

  Parser::symbol_type
  Parser::make_NE (const location_type& l)
  {
    return symbol_type (token::TOKEN_NE, l);
  }

  Parser::symbol_type
  Parser::make_GT (const location_type& l)
  {
    return symbol_type (token::TOKEN_GT, l);
  }

  Parser::symbol_type
  Parser::make_GE (const location_type& l)
  {
    return symbol_type (token::TOKEN_GE, l);
  }

  Parser::symbol_type
  Parser::make_LT (const location_type& l)
  {
    return symbol_type (token::TOKEN_LT, l);
  }

  Parser::symbol_type
  Parser::make_LE (const location_type& l)
  {
    return symbol_type (token::TOKEN_LE, l);
  }

  Parser::symbol_type
  Parser::make_ADD (const location_type& l)
  {
    return symbol_type (token::TOKEN_ADD, l);
  }

  Parser::symbol_type
  Parser::make_SUB (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUB, l);
  }

  Parser::symbol_type
  Parser::make_MUL (const location_type& l)
  {
    return symbol_type (token::TOKEN_MUL, l);
  }

  Parser::symbol_type
  Parser::make_DIV (const location_type& l)
  {
    return symbol_type (token::TOKEN_DIV, l);
  }

  Parser::symbol_type
  Parser::make_MOD (const location_type& l)
  {
    return symbol_type (token::TOKEN_MOD, l);
  }

  Parser::symbol_type
  Parser::make_UMINUS (const location_type& l)
  {
    return symbol_type (token::TOKEN_UMINUS, l);
  }

  Parser::symbol_type
  Parser::make_INT_LITERAL (const zyd2001::NewBie::Expression& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_INT_LITERAL, v, l);
  }

  Parser::symbol_type
  Parser::make_STRING_LITERAL (const zyd2001::NewBie::Expression& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_STRING_LITERAL, v, l);
  }

  Parser::symbol_type
  Parser::make_DOUBLE_LITERAL (const zyd2001::NewBie::Expression& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_DOUBLE_LITERAL, v, l);
  }

  Parser::symbol_type
  Parser::make_BOOL_LITERAL (const zyd2001::NewBie::Expression& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_BOOL_LITERAL, v, l);
  }

  Parser::symbol_type
  Parser::make_IDENTIFIER (const zyd2001::NewBie::Identifier& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_IDENTIFIER, v, l);
  }

  Parser::symbol_type
  Parser::make_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_INT, l);
  }

  Parser::symbol_type
  Parser::make_DOUBLE (const location_type& l)
  {
    return symbol_type (token::TOKEN_DOUBLE, l);
  }

  Parser::symbol_type
  Parser::make_BOOL (const location_type& l)
  {
    return symbol_type (token::TOKEN_BOOL, l);
  }

  Parser::symbol_type
  Parser::make_STRING (const location_type& l)
  {
    return symbol_type (token::TOKEN_STRING, l);
  }

  Parser::symbol_type
  Parser::make_ARRAY (const location_type& l)
  {
    return symbol_type (token::TOKEN_ARRAY, l);
  }

  Parser::symbol_type
  Parser::make_VAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_VAR, l);
  }

  Parser::symbol_type
  Parser::make_GLOBAL (const location_type& l)
  {
    return symbol_type (token::TOKEN_GLOBAL, l);
  }

  Parser::symbol_type
  Parser::make_IF (const location_type& l)
  {
    return symbol_type (token::TOKEN_IF, l);
  }

  Parser::symbol_type
  Parser::make_ELSE (const location_type& l)
  {
    return symbol_type (token::TOKEN_ELSE, l);
  }

  Parser::symbol_type
  Parser::make_ELSEIF (const location_type& l)
  {
    return symbol_type (token::TOKEN_ELSEIF, l);
  }

  Parser::symbol_type
  Parser::make_FOR (const location_type& l)
  {
    return symbol_type (token::TOKEN_FOR, l);
  }

  Parser::symbol_type
  Parser::make_IN (const location_type& l)
  {
    return symbol_type (token::TOKEN_IN, l);
  }

  Parser::symbol_type
  Parser::make_CLASS (const location_type& l)
  {
    return symbol_type (token::TOKEN_CLASS, l);
  }

  Parser::symbol_type
  Parser::make_RETURN (const location_type& l)
  {
    return symbol_type (token::TOKEN_RETURN, l);
  }

  Parser::symbol_type
  Parser::make_BREAK (const location_type& l)
  {
    return symbol_type (token::TOKEN_BREAK, l);
  }

  Parser::symbol_type
  Parser::make_CONTINUE (const location_type& l)
  {
    return symbol_type (token::TOKEN_CONTINUE, l);
  }

  Parser::symbol_type
  Parser::make_LP (const location_type& l)
  {
    return symbol_type (token::TOKEN_LP, l);
  }

  Parser::symbol_type
  Parser::make_RP (const location_type& l)
  {
    return symbol_type (token::TOKEN_RP, l);
  }

  Parser::symbol_type
  Parser::make_LC (const location_type& l)
  {
    return symbol_type (token::TOKEN_LC, l);
  }

  Parser::symbol_type
  Parser::make_RC (const location_type& l)
  {
    return symbol_type (token::TOKEN_RC, l);
  }

  Parser::symbol_type
  Parser::make_LB (const location_type& l)
  {
    return symbol_type (token::TOKEN_LB, l);
  }

  Parser::symbol_type
  Parser::make_RB (const location_type& l)
  {
    return symbol_type (token::TOKEN_RB, l);
  }

  Parser::symbol_type
  Parser::make_SEMICOLON (const location_type& l)
  {
    return symbol_type (token::TOKEN_SEMICOLON, l);
  }

  Parser::symbol_type
  Parser::make_COMMA (const location_type& l)
  {
    return symbol_type (token::TOKEN_COMMA, l);
  }

  Parser::symbol_type
  Parser::make_ASSIGN (const location_type& l)
  {
    return symbol_type (token::TOKEN_ASSIGN, l);
  }

  Parser::symbol_type
  Parser::make_EXCLAMATION (const location_type& l)
  {
    return symbol_type (token::TOKEN_EXCLAMATION, l);
  }

  Parser::symbol_type
  Parser::make_DOT (const location_type& l)
  {
    return symbol_type (token::TOKEN_DOT, l);
  }

  Parser::symbol_type
  Parser::make_ADD_ASSIGN (const location_type& l)
  {
    return symbol_type (token::TOKEN_ADD_ASSIGN, l);
  }

  Parser::symbol_type
  Parser::make_SUB_ASSIGN (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUB_ASSIGN, l);
  }

  Parser::symbol_type
  Parser::make_MUL_ASSIGN (const location_type& l)
  {
    return symbol_type (token::TOKEN_MUL_ASSIGN, l);
  }

  Parser::symbol_type
  Parser::make_DIV_ASSIGN (const location_type& l)
  {
    return symbol_type (token::TOKEN_DIV_ASSIGN, l);
  }

  Parser::symbol_type
  Parser::make_MOD_ASSIGN (const location_type& l)
  {
    return symbol_type (token::TOKEN_MOD_ASSIGN, l);
  }

  Parser::symbol_type
  Parser::make_INCREMENT (const location_type& l)
  {
    return symbol_type (token::TOKEN_INCREMENT, l);
  }

  Parser::symbol_type
  Parser::make_DECREMENT (const location_type& l)
  {
    return symbol_type (token::TOKEN_DECREMENT, l);
  }

  Parser::symbol_type
  Parser::make_PUBLIC (const location_type& l)
  {
    return symbol_type (token::TOKEN_PUBLIC, l);
  }

  Parser::symbol_type
  Parser::make_PROTECTED (const location_type& l)
  {
    return symbol_type (token::TOKEN_PROTECTED, l);
  }

  Parser::symbol_type
  Parser::make_PRIVATE (const location_type& l)
  {
    return symbol_type (token::TOKEN_PRIVATE, l);
  }

  Parser::symbol_type
  Parser::make_REVERSE (const location_type& l)
  {
    return symbol_type (token::TOKEN_REVERSE, l);
  }



} } // zyd2001::NewBie





#endif // !YY_YY_PARSER_HPP_INCLUDED
