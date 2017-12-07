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


// First part of user declarations.



# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "Parser.hpp"

// User implementation prologue.


// Unqualified %code blocks.


    using namespace std;
    using namespace zyd2001::NewBie;
    IfStatement *current_if;
	Parser::symbol_type yylex(zyd2001::NewBie::InterpreterImp &inter, yyscan_t yyscanner);




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


namespace zyd2001 { namespace NewBie {


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
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
              // Fall through.
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


  /// Build a parser object.
  Parser::Parser (zyd2001::NewBie::InterpreterImp &inter_yyarg, yyscan_t scanner_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      inter (inter_yyarg),
      scanner (scanner_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 74: // arguments_list
        value.move< zyd2001::NewBie::ArgumentsList > (that.value);
        break;

      case 64: // declaration_item
        value.move< zyd2001::NewBie::DeclarationStatementItem > (that.value);
        break;

      case 65: // declaration_item_list
        value.move< zyd2001::NewBie::DeclarationStatementItemList > (that.value);
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
        value.move< zyd2001::NewBie::Expression > (that.value);
        break;

      case 21: // IDENTIFIER
        value.move< zyd2001::NewBie::Identifier > (that.value);
        break;

      case 75: // parameter
        value.move< zyd2001::NewBie::Parameter > (that.value);
        break;

      case 76: // parameters_list
        value.move< zyd2001::NewBie::ParametersList > (that.value);
        break;

      case 63: // statement
      case 73: // block
        value.move< zyd2001::NewBie::Statement > (that.value);
        break;

      case 62: // statements_list
        value.move< zyd2001::NewBie::StatementsList > (that.value);
        break;

      case 72: // type_tag
        value.move< zyd2001::NewBie::ValueType > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 74: // arguments_list
        value.copy< zyd2001::NewBie::ArgumentsList > (that.value);
        break;

      case 64: // declaration_item
        value.copy< zyd2001::NewBie::DeclarationStatementItem > (that.value);
        break;

      case 65: // declaration_item_list
        value.copy< zyd2001::NewBie::DeclarationStatementItemList > (that.value);
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
        value.copy< zyd2001::NewBie::Expression > (that.value);
        break;

      case 21: // IDENTIFIER
        value.copy< zyd2001::NewBie::Identifier > (that.value);
        break;

      case 75: // parameter
        value.copy< zyd2001::NewBie::Parameter > (that.value);
        break;

      case 76: // parameters_list
        value.copy< zyd2001::NewBie::ParametersList > (that.value);
        break;

      case 63: // statement
      case 73: // block
        value.copy< zyd2001::NewBie::Statement > (that.value);
        break;

      case 62: // statements_list
        value.copy< zyd2001::NewBie::StatementsList > (that.value);
        break;

      case 72: // type_tag
        value.copy< zyd2001::NewBie::ValueType > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
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
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
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


    // User initialization code.
    
{
    yyla.location.begin.filename = yyla.location.end.filename = &inter.filename;
}



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
            symbol_type yylookahead (yylex (inter, scanner));
            yyla.move (yylookahead);
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
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 74: // arguments_list
        yylhs.value.build< zyd2001::NewBie::ArgumentsList > ();
        break;

      case 64: // declaration_item
        yylhs.value.build< zyd2001::NewBie::DeclarationStatementItem > ();
        break;

      case 65: // declaration_item_list
        yylhs.value.build< zyd2001::NewBie::DeclarationStatementItemList > ();
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
        yylhs.value.build< zyd2001::NewBie::Expression > ();
        break;

      case 21: // IDENTIFIER
        yylhs.value.build< zyd2001::NewBie::Identifier > ();
        break;

      case 75: // parameter
        yylhs.value.build< zyd2001::NewBie::Parameter > ();
        break;

      case 76: // parameters_list
        yylhs.value.build< zyd2001::NewBie::ParametersList > ();
        break;

      case 63: // statement
      case 73: // block
        yylhs.value.build< zyd2001::NewBie::Statement > ();
        break;

      case 62: // statements_list
        yylhs.value.build< zyd2001::NewBie::StatementsList > ();
        break;

      case 72: // type_tag
        yylhs.value.build< zyd2001::NewBie::ValueType > ();
        break;

      default:
        break;
    }


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
  case 2:

    {
			inter.statements_list = std::move(yystack_[1].value.as< zyd2001::NewBie::StatementsList > ());
		}

    break;

  case 3:

    {
            yylhs.value.as< zyd2001::NewBie::StatementsList > ().push_back(yystack_[0].value.as< zyd2001::NewBie::Statement > ());
        }

    break;

  case 4:

    {
            yystack_[1].value.as< zyd2001::NewBie::StatementsList > ().push_back(yystack_[0].value.as< zyd2001::NewBie::Statement > ());
            yylhs.value.as< zyd2001::NewBie::StatementsList > ().swap(yystack_[1].value.as< zyd2001::NewBie::StatementsList > ());
        }

    break;

  case 5:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(EXPRESSION_STATEMENT, new ExpressionStatement(std::move(yystack_[1].value.as< zyd2001::NewBie::Expression > ())), yyget_lineno(scanner));
        }

    break;

  case 6:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(ASSIGNMENT_STATEMENT, new (AssignmentStatement){std::move(yystack_[3].value.as< zyd2001::NewBie::Identifier > ()), std::move(yystack_[1].value.as< zyd2001::NewBie::Expression > ())}, yyget_lineno(scanner));
        }

    break;

  case 7:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(DECLARATION_STATEMENT, new (DeclarationStatement){std::move(yystack_[2].value.as< zyd2001::NewBie::ValueType > ()), std::move(yystack_[1].value.as< zyd2001::NewBie::DeclarationStatementItemList > ()), false}, yyget_lineno(scanner));
        }

    break;

  case 8:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(DECLARATION_STATEMENT, new (DeclarationStatement){std::move(yystack_[2].value.as< zyd2001::NewBie::ValueType > ()), std::move(yystack_[1].value.as< zyd2001::NewBie::DeclarationStatementItemList > ()), true}, yyget_lineno(scanner));
        }

    break;

  case 9:

    {
            current_if = new (IfStatement){std::move(yystack_[2].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Statement > ())};
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(IF_STATEMENT, current_if, yyget_lineno(scanner));
        }

    break;

  case 10:

    {
            current_if->else_stat = std::move(yystack_[0].value.as< zyd2001::NewBie::Statement > ());
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement();
        }

    break;

  case 11:

    {
            current_if->elseif.push_back({std::move(yystack_[2].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Statement > ())});
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement();
        }

    break;

  case 12:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(FOR_STATEMENT, new (ForStatement){std::move(yystack_[6].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[4].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[2].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Statement > ())}, yyget_lineno(scanner));
        }

    break;

  case 13:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(RETURN_STATEMENT, new ReturnStatement(std::move(yystack_[1].value.as< zyd2001::NewBie::Expression > ())), yyget_lineno(scanner));
        }

    break;

  case 14:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(CONTINUE_STATEMENT, nullptr, yyget_lineno(scanner));
        }

    break;

  case 15:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(BREAK_STATEMENT, nullptr, yyget_lineno(scanner));
        }

    break;

  case 16:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement();
        }

    break;

  case 17:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = std::move(yystack_[0].value.as< zyd2001::NewBie::Statement > ());
        }

    break;

  case 18:

    {
            yylhs.value.as< zyd2001::NewBie::DeclarationStatementItem > () = {std::move(yystack_[0].value.as< zyd2001::NewBie::Identifier > ())};
        }

    break;

  case 19:

    {
            yylhs.value.as< zyd2001::NewBie::DeclarationStatementItem > () = {std::move(yystack_[2].value.as< zyd2001::NewBie::Identifier > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ())};
        }

    break;

  case 20:

    {
            yylhs.value.as< zyd2001::NewBie::DeclarationStatementItemList > ().push_back(yystack_[0].value.as< zyd2001::NewBie::DeclarationStatementItem > ());
        }

    break;

  case 21:

    {
            yystack_[2].value.as< zyd2001::NewBie::DeclarationStatementItemList > ().push_back(yystack_[0].value.as< zyd2001::NewBie::DeclarationStatementItem > ());
            yylhs.value.as< zyd2001::NewBie::DeclarationStatementItemList > ().swap(yystack_[2].value.as< zyd2001::NewBie::DeclarationStatementItemList > ());
        }

    break;

  case 22:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ());
        }

    break;

  case 23:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ());
        }

    break;

  case 24:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ());
        }

    break;

  case 25:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ());
        }

    break;

  case 26:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(IDENTIFIER_EXPRESSION, new IdentifierExpression(std::move(yystack_[0].value.as< zyd2001::NewBie::Identifier > ())));
        }

    break;

  case 27:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = std::move(yystack_[1].value.as< zyd2001::NewBie::Expression > ());
        }

    break;

  case 28:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression();
        }

    break;

  case 30:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){ADD, std::move(yystack_[2].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ())});
        }

    break;

  case 31:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){SUB, std::move(yystack_[2].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ())});
        }

    break;

  case 32:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){MUL, std::move(yystack_[2].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ())});
        }

    break;

  case 33:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){DIV, std::move(yystack_[2].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ())});
        }

    break;

  case 34:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){MOD, std::move(yystack_[2].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ())});
        }

    break;

  case 35:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){EQ, std::move(yystack_[2].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ())});
        }

    break;

  case 36:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){NE, std::move(yystack_[2].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ())});
        }

    break;

  case 37:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){GT, std::move(yystack_[2].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ())});
        }

    break;

  case 38:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){GE, std::move(yystack_[2].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ())});
        }

    break;

  case 39:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){LT, std::move(yystack_[2].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ())});
        }

    break;

  case 40:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){LE, std::move(yystack_[2].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ())});
        }

    break;

  case 41:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){AND, std::move(yystack_[2].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ())});
        }

    break;

  case 42:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){OR, std::move(yystack_[2].value.as< zyd2001::NewBie::Expression > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ())});
        }

    break;

  case 43:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(UNARY_EXPRESSION, new (UnaryExpression){MINUS, std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ())});
        }

    break;

  case 44:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(UNARY_EXPRESSION, new (UnaryExpression){NOT, std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ())});
        }

    break;

  case 45:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(FUNCTION_CALL_EXPRESSION, new (FunctionCallExpression){yystack_[3].value.as< zyd2001::NewBie::Identifier > (), yystack_[1].value.as< zyd2001::NewBie::ArgumentsList > ()});
        }

    break;

  case 46:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ());
        }

    break;

  case 47:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ());
        }

    break;

  case 48:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ());
        }

    break;

  case 49:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = std::move(yystack_[0].value.as< zyd2001::NewBie::Expression > ());
        }

    break;

  case 50:

    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = INT_TYPE;
        }

    break;

  case 51:

    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = DOUBLE_TYPE;
        }

    break;

  case 52:

    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = BOOL_TYPE;
        }

    break;

  case 53:

    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = STRING_TYPE;
        }

    break;

  case 54:

    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = ARRAY_TYPE;
        }

    break;

  case 55:

    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = VARIOUS_TYPE;
        }

    break;

  case 56:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(BLOCK_STATEMENT, new BlockStatement(yystack_[1].value.as< zyd2001::NewBie::StatementsList > ()), yyget_lineno(scanner));
        }

    break;

  case 57:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(BLOCK_STATEMENT, new BlockStatement(), yyget_lineno(scanner));
        }

    break;

  case 58:

    {
            yylhs.value.as< zyd2001::NewBie::ArgumentsList > ();
        }

    break;

  case 59:

    {
            yylhs.value.as< zyd2001::NewBie::ArgumentsList > ().push_back(yystack_[0].value.as< zyd2001::NewBie::Expression > ());
        }

    break;

  case 60:

    {
            yystack_[2].value.as< zyd2001::NewBie::ArgumentsList > ().push_back(yystack_[0].value.as< zyd2001::NewBie::Expression > ());
            yylhs.value.as< zyd2001::NewBie::ArgumentsList > ().swap(yystack_[2].value.as< zyd2001::NewBie::ArgumentsList > ());
        }

    break;

  case 61:

    {
            yylhs.value.as< zyd2001::NewBie::Parameter > () = {yystack_[2].value.as< zyd2001::NewBie::ValueType > (), yystack_[1].value.as< zyd2001::NewBie::Identifier > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()};
        }

    break;

  case 62:

    {
            yylhs.value.as< zyd2001::NewBie::ParametersList > ();
        }

    break;

  case 63:

    {
            yylhs.value.as< zyd2001::NewBie::ParametersList > ().push_back(yystack_[0].value.as< zyd2001::NewBie::Parameter > ());
        }

    break;

  case 64:

    {
            yystack_[2].value.as< zyd2001::NewBie::ParametersList > ().push_back(yystack_[0].value.as< zyd2001::NewBie::Parameter > ());
            yylhs.value.as< zyd2001::NewBie::ParametersList > ().swap(yystack_[2].value.as< zyd2001::NewBie::ParametersList > ());
        }

    break;



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
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -101;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
     307,    -5,  -101,  -101,  -101,  -101,   -19,  -101,  -101,  -101,
    -101,  -101,  -101,    21,   -32,   307,   -30,   -10,    -5,    -7,
       7,    -5,   245,    -5,    39,   101,  -101,    63,  -101,  -101,
    -101,  -101,    44,  -101,    49,  -101,    -5,    -5,    67,    -5,
    -101,    -5,    -5,   146,  -101,  -101,   172,  -101,   276,  -101,
    -101,  -101,  -101,    -5,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,    -5,    -5,    -5,    -5,  -101,   -17,  -101,     5,
     352,   -36,   159,    45,    41,   209,   222,   352,    48,  -101,
    -101,  -101,   186,   186,    68,    68,    68,    68,    68,    68,
      17,    17,  -101,  -101,  -101,    21,    -5,  -101,    67,  -101,
      -5,  -101,  -101,   307,   307,    -5,    72,  -101,   -35,   352,
    -101,   352,  -101,  -101,    50,     6,    56,    21,    -5,  -101,
    -101,  -101,    58,   307,  -101
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,    46,    48,    47,    49,    26,    50,    51,    52,
      53,    54,    55,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     0,    22,    23,
      25,    24,     0,    17,    26,    43,    58,     0,     0,     0,
      10,     0,    28,     0,    15,    14,     0,    57,     0,    44,
       1,     2,     4,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     5,    18,    20,     0,
      59,     0,     0,    18,     0,     0,     0,    29,     0,    13,
      27,    56,    41,    42,    35,    36,    37,    38,    39,    40,
      30,    31,    32,    33,    34,    62,     0,     7,     0,    45,
       0,     6,     8,     0,     0,    28,     0,    63,     0,    19,
      21,    60,     9,    11,     0,     0,     0,     0,    28,    61,
      16,    64,     0,     0,    12
  };

  const signed char
  Parser::yypgoto_[] =
  {
    -101,  -101,    76,   -14,     2,    64,    -1,  -100,  -101,  -101,
    -101,   -12,   -11,    -8,  -101,    -6,  -101
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,    24,    25,    26,    68,    69,    27,    78,    28,    29,
      30,    31,    32,    33,    71,   107,   108
  };

  const unsigned char
  Parser::yytable_[] =
  {
      35,    40,    38,    99,   116,   114,    39,     1,    41,   100,
     117,    52,     2,     3,     4,     5,    34,    43,   122,    36,
      46,    95,    49,     2,     3,     4,     5,    37,    42,    96,
      63,    64,    65,    21,    52,    70,    72,    44,    75,    50,
      76,    77,    23,     7,     8,     9,    10,    11,    12,    97,
      98,    45,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    67,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    61,
      62,    63,    64,    65,   106,   102,    98,    36,    73,   112,
     113,    96,   105,   115,   118,   109,    22,   123,    48,   111,
     110,    51,    74,   119,    77,     0,   106,    66,   120,   124,
       0,   121,     0,     1,     0,     0,     0,    77,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,     0,     0,    18,    19,    20,    21,
       0,    22,     0,     0,     0,     0,     0,     0,    23,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,     0,     0,
      79,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,     0,   101,     0,     0,     0,     0,     0,     0,
       0,    80,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   103,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     0,     0,
       0,   104,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     0,     0,
      18,    19,    20,    21,     0,    22,    47,     0,     1,     0,
       0,     0,    23,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,     0,
       0,    18,    19,    20,    21,     0,    22,    81,     0,     1,
       0,     0,     0,    23,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       0,     0,    18,    19,    20,    21,     0,    22,     0,     0,
       0,     0,     0,     0,    23,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65
  };

  const signed char
  Parser::yycheck_[] =
  {
       1,    15,    13,    39,    39,   105,    38,    12,    38,    45,
      45,    25,    17,    18,    19,    20,    21,    18,   118,    38,
      21,    38,    23,    17,    18,    19,    20,    46,    38,    46,
      13,    14,    15,    38,    48,    36,    37,    44,    39,     0,
      41,    42,    47,    22,    23,    24,    25,    26,    27,    44,
      45,    44,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    21,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    11,
      12,    13,    14,    15,    95,    44,    45,    38,    21,   103,
     104,    46,    44,    21,    44,    96,    40,    39,    22,   100,
      98,     0,    38,   115,   105,    -1,   117,    44,   116,   123,
      -1,   117,    -1,    12,    -1,    -1,    -1,   118,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      44,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,
      -1,    39,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    -1,    12,    -1,
      -1,    -1,    47,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      -1,    35,    36,    37,    38,    -1,    40,    41,    -1,    12,
      -1,    -1,    -1,    47,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    47,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    12,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    35,    36,
      37,    38,    40,    47,    61,    62,    63,    66,    68,    69,
      70,    71,    72,    73,    21,    66,    38,    46,    72,    38,
      63,    38,    38,    66,    44,    44,    66,    41,    62,    66,
       0,     0,    63,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    44,    21,    64,    65,
      66,    74,    66,    21,    65,    66,    66,    66,    67,    44,
      39,    41,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    38,    46,    44,    45,    39,
      45,    44,    44,    39,    39,    44,    72,    75,    76,    66,
      64,    66,    63,    63,    67,    21,    39,    45,    44,    71,
      73,    75,    67,    39,    63
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    60,    61,    62,    62,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    64,    64,
      65,    65,    66,    66,    66,    66,    66,    66,    67,    67,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    69,    69,    70,    71,    71,    71,    71,
      72,    72,    72,    72,    72,    72,    73,    73,    74,    74,
      74,    75,    76,    76,    76
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     2,     2,     4,     3,     4,     5,
       2,     5,     9,     3,     2,     2,     6,     1,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     3,     0,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     0,     1,
       3,     3,     0,     1,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "LOGICAL_AND", "LOGICAL_OR",
  "EQ", "NE", "GT", "GE", "LT", "LE", "ADD", "SUB", "MUL", "DIV", "MOD",
  "UMINUS", "INT_LITERAL", "STRING_LITERAL", "DOUBLE_LITERAL",
  "BOOL_LITERAL", "IDENTIFIER", "INT", "DOUBLE", "BOOL", "STRING", "ARRAY",
  "VAR", "GLOBAL", "IF", "ELSE", "ELSEIF", "FOR", "IN", "CLASS", "RETURN",
  "BREAK", "CONTINUE", "LP", "RP", "LC", "RC", "LB", "RB", "SEMICOLON",
  "COMMA", "ASSIGN", "EXCLAMATION", "DOT", "ADD_ASSIGN", "SUB_ASSIGN",
  "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "INCREMENT", "DECREMENT",
  "PUBLIC", "PROTECTED", "PRIVATE", "REVERSE", "$accept", "eof",
  "statements_list", "statement", "declaration_item",
  "declaration_item_list", "expression", "expression_optional",
  "binary_expression", "unary_expression", "function_call_expression",
  "primary_expression", "type_tag", "block", "arguments_list", "parameter",
  "parameters_list", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,    59,    59,    64,    68,    74,    78,    82,    86,    90,
      95,   100,   105,   109,   113,   117,   121,   125,   130,   134,
     139,   143,   149,   153,   157,   161,   165,   169,   175,   178,
     180,   184,   188,   192,   196,   200,   204,   208,   212,   216,
     220,   224,   228,   233,   237,   242,   247,   251,   255,   259,
     274,   278,   282,   286,   290,   294,   299,   303,   309,   312,
     316,   322,   328,   331,   335
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
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
  Parser::yy_reduce_print_ (int yyrule)
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



} } // zyd2001::NewBie




void Parser::error(const location_type& l, const std::string& m)
{
	std::cerr << "At file " << l.begin.filename  << " " << l << " " << m << endl;
}