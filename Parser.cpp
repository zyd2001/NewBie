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

#line 37 "Parser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "Parser.hpp"

// User implementation prologue.

#line 51 "Parser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 13 "newbie++.y" // lalr1.cc:413

    using namespace std;
    using namespace zyd2001::NewBie;
    IfStatement *current_if;
    zyd2001::NewBie::Parser::symbol_type yylex(yyscan_t yyscanner);

#line 60 "Parser.cpp" // lalr1.cc:413


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

#line 20 "newbie++.y" // lalr1.cc:479
namespace zyd2001 { namespace NewBie {
#line 146 "Parser.cpp" // lalr1.cc:479

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
      case 21: // IDENTIFIER
        value.move< std::string > (that.value);
        break;

      case 72: // arguments_list
        value.move< zyd2001::NewBie::ArgumentsList > (that.value);
        break;

      case 62: // declaration_item
        value.move< zyd2001::NewBie::DeclarationStatementItem > (that.value);
        break;

      case 63: // declaration_item_list
        value.move< zyd2001::NewBie::DeclarationStatementItemList > (that.value);
        break;

      case 17: // INT_LITERAL
      case 18: // STRING_LITERAL
      case 19: // DOUBLE_LITERAL
      case 20: // BOOL_LITERAL
      case 64: // expression
      case 65: // expression_optional
      case 66: // binary_expression
      case 67: // unary_expression
      case 68: // function_call_expression
      case 69: // primary_expression
        value.move< zyd2001::NewBie::Expression > (that.value);
        break;

      case 73: // parameter
        value.move< zyd2001::NewBie::Parameter > (that.value);
        break;

      case 74: // parameters_list
        value.move< zyd2001::NewBie::ParametersList > (that.value);
        break;

      case 61: // statement
      case 71: // block
        value.move< zyd2001::NewBie::Statement > (that.value);
        break;

      case 60: // statements_list
        value.move< zyd2001::NewBie::StatementsList > (that.value);
        break;

      case 70: // type_tag
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
      case 21: // IDENTIFIER
        value.copy< std::string > (that.value);
        break;

      case 72: // arguments_list
        value.copy< zyd2001::NewBie::ArgumentsList > (that.value);
        break;

      case 62: // declaration_item
        value.copy< zyd2001::NewBie::DeclarationStatementItem > (that.value);
        break;

      case 63: // declaration_item_list
        value.copy< zyd2001::NewBie::DeclarationStatementItemList > (that.value);
        break;

      case 17: // INT_LITERAL
      case 18: // STRING_LITERAL
      case 19: // DOUBLE_LITERAL
      case 20: // BOOL_LITERAL
      case 64: // expression
      case 65: // expression_optional
      case 66: // binary_expression
      case 67: // unary_expression
      case 68: // function_call_expression
      case 69: // primary_expression
        value.copy< zyd2001::NewBie::Expression > (that.value);
        break;

      case 73: // parameter
        value.copy< zyd2001::NewBie::Parameter > (that.value);
        break;

      case 74: // parameters_list
        value.copy< zyd2001::NewBie::ParametersList > (that.value);
        break;

      case 61: // statement
      case 71: // block
        value.copy< zyd2001::NewBie::Statement > (that.value);
        break;

      case 60: // statements_list
        value.copy< zyd2001::NewBie::StatementsList > (that.value);
        break;

      case 70: // type_tag
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
    #line 30 "newbie++.y" // lalr1.cc:741
{
    yyla.location.begin.filename = yyla.location.end.filename = &inter.filename;
}

#line 520 "Parser.cpp" // lalr1.cc:741

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
            symbol_type yylookahead (yylex (scanner));
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
      case 21: // IDENTIFIER
        yylhs.value.build< std::string > ();
        break;

      case 72: // arguments_list
        yylhs.value.build< zyd2001::NewBie::ArgumentsList > ();
        break;

      case 62: // declaration_item
        yylhs.value.build< zyd2001::NewBie::DeclarationStatementItem > ();
        break;

      case 63: // declaration_item_list
        yylhs.value.build< zyd2001::NewBie::DeclarationStatementItemList > ();
        break;

      case 17: // INT_LITERAL
      case 18: // STRING_LITERAL
      case 19: // DOUBLE_LITERAL
      case 20: // BOOL_LITERAL
      case 64: // expression
      case 65: // expression_optional
      case 66: // binary_expression
      case 67: // unary_expression
      case 68: // function_call_expression
      case 69: // primary_expression
        yylhs.value.build< zyd2001::NewBie::Expression > ();
        break;

      case 73: // parameter
        yylhs.value.build< zyd2001::NewBie::Parameter > ();
        break;

      case 74: // parameters_list
        yylhs.value.build< zyd2001::NewBie::ParametersList > ();
        break;

      case 61: // statement
      case 71: // block
        yylhs.value.build< zyd2001::NewBie::Statement > ();
        break;

      case 60: // statements_list
        yylhs.value.build< zyd2001::NewBie::StatementsList > ();
        break;

      case 70: // type_tag
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
#line 58 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::StatementsList > ().push_back(yystack_[0].value.as< zyd2001::NewBie::Statement > ());
        }
#line 682 "Parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 62 "newbie++.y" // lalr1.cc:859
    {
            yystack_[1].value.as< zyd2001::NewBie::StatementsList > ().push_back(yystack_[0].value.as< zyd2001::NewBie::Statement > ());
            yylhs.value.as< zyd2001::NewBie::StatementsList > ().swap(yystack_[1].value.as< zyd2001::NewBie::StatementsList > ());
        }
#line 691 "Parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 68 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(EXPRESSION_STATEMENT, new ExpressionStatement(std::move(yystack_[1].value.as< zyd2001::NewBie::Expression > ())));
        }
#line 699 "Parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 72 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(ASSIGNMENT_STATEMENT, new (AssignmentStatement){yystack_[2].value.as< std::string > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }
#line 707 "Parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 76 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(DECLARATION_STATEMENT, new (DeclarationStatement){yystack_[1].value.as< zyd2001::NewBie::ValueType > (), yystack_[0].value.as< zyd2001::NewBie::DeclarationStatementItemList > ()});
        }
#line 715 "Parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 80 "newbie++.y" // lalr1.cc:859
    {
            current_if = new (IfStatement){yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Statement > ()};
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(IF_STATEMENT, current_if);
        }
#line 724 "Parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 85 "newbie++.y" // lalr1.cc:859
    {
            current_if->else_stat = std::move(yystack_[0].value.as< zyd2001::NewBie::Statement > ());
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement();
        }
#line 733 "Parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 90 "newbie++.y" // lalr1.cc:859
    {
            current_if->elseif.push_back({yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Statement > ()});
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement();
        }
#line 742 "Parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 95 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(FOR_STATEMENT, new (ForStatement){yystack_[6].value.as< zyd2001::NewBie::Expression > (), yystack_[4].value.as< zyd2001::NewBie::Expression > (), yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Statement > ()});
        }
#line 750 "Parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 99 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(RETURN_STATEMENT, new ReturnStatement(yystack_[1].value.as< zyd2001::NewBie::Expression > ()));
        }
#line 758 "Parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 103 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(CONTINUE_STATEMENT, nullptr);
        }
#line 766 "Parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 107 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(BREAK_STATEMENT, nullptr);
        }
#line 774 "Parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 111 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement();
        }
#line 782 "Parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 117 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::DeclarationStatementItem > () = {yystack_[0].value.as< std::string > ()};
        }
#line 790 "Parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 121 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::DeclarationStatementItem > () = {yystack_[2].value.as< std::string > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()};
        }
#line 798 "Parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 126 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::DeclarationStatementItemList > ().push_back(yystack_[0].value.as< zyd2001::NewBie::DeclarationStatementItem > ());
        }
#line 806 "Parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 130 "newbie++.y" // lalr1.cc:859
    {
            yystack_[1].value.as< zyd2001::NewBie::DeclarationStatementItemList > ().push_back(yystack_[0].value.as< zyd2001::NewBie::DeclarationStatementItem > ());
            yylhs.value.as< zyd2001::NewBie::DeclarationStatementItemList > ().swap(yystack_[1].value.as< zyd2001::NewBie::DeclarationStatementItemList > ());
        }
#line 815 "Parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 140 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(IDENTIFIER_EXPRESSION, new IdentifierExpression(yystack_[0].value.as< std::string > ()));
        }
#line 823 "Parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 144 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = std::move(yystack_[1].value.as< zyd2001::NewBie::Expression > ());
        }
#line 831 "Parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 149 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression();
        }
#line 839 "Parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 155 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){ADD, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }
#line 847 "Parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 159 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){SUB, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});         
        }
#line 855 "Parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 163 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){MUL, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }
#line 863 "Parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 167 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){DIV, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }
#line 871 "Parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 171 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){MOD, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }
#line 879 "Parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 175 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){EQ, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }
#line 887 "Parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 179 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){NE, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }
#line 895 "Parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 183 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){GT, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }
#line 903 "Parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 187 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){GE, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }
#line 911 "Parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 191 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){LT, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }
#line 919 "Parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 195 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){LE, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }
#line 927 "Parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 199 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){AND, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }
#line 935 "Parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 203 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){OR, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }
#line 943 "Parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 208 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(UNARY_EXPRESSION, new (UnaryExpression){MINUS, yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }
#line 951 "Parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 212 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(UNARY_EXPRESSION, new (UnaryExpression){NOT, yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }
#line 959 "Parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 217 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(FUNCTION_CALL_EXPRESSION, new (FunctionCallExpression){yystack_[3].value.as< std::string > (), yystack_[1].value.as< zyd2001::NewBie::ArgumentsList > ()});
        }
#line 967 "Parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 237 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = INT_TYPE;
        }
#line 975 "Parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 241 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = DOUBLE_TYPE;
        }
#line 983 "Parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 245 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = BOOL_TYPE;
        }
#line 991 "Parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 249 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = STRING_TYPE;
        }
#line 999 "Parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 253 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = ARRAY_TYPE;
        }
#line 1007 "Parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 257 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = VARIOUS_TYPE;
        }
#line 1015 "Parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 262 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(BLOCK_STATEMENT, new BlockStatement(yystack_[1].value.as< zyd2001::NewBie::StatementsList > ()));
        }
#line 1023 "Parser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 266 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(BLOCK_STATEMENT, new BlockStatement());
        }
#line 1031 "Parser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 271 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::ArgumentsList > ();
        }
#line 1039 "Parser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 275 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::ArgumentsList > ().push_back(yystack_[0].value.as< zyd2001::NewBie::Expression > ());
        }
#line 1047 "Parser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 279 "newbie++.y" // lalr1.cc:859
    {
            yystack_[2].value.as< zyd2001::NewBie::ArgumentsList > ().push_back(yystack_[0].value.as< zyd2001::NewBie::Expression > ());
            yylhs.value.as< zyd2001::NewBie::ArgumentsList > ().swap(yystack_[2].value.as< zyd2001::NewBie::ArgumentsList > ());
        }
#line 1056 "Parser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 285 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::Parameter > () = {yystack_[2].value.as< zyd2001::NewBie::ValueType > (), yystack_[1].value.as< std::string > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()};
        }
#line 1064 "Parser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 290 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::ParametersList > ();
        }
#line 1072 "Parser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 294 "newbie++.y" // lalr1.cc:859
    {
            yylhs.value.as< zyd2001::NewBie::ParametersList > ().push_back(yystack_[0].value.as< zyd2001::NewBie::Parameter > ());
        }
#line 1080 "Parser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 298 "newbie++.y" // lalr1.cc:859
    {
            yystack_[2].value.as< zyd2001::NewBie::ParametersList > ().push_back(yystack_[0].value.as< zyd2001::NewBie::Parameter > ());
            yylhs.value.as< zyd2001::NewBie::ParametersList > ().swap(yystack_[2].value.as< zyd2001::NewBie::ParametersList > ());
        }
#line 1089 "Parser.cpp" // lalr1.cc:859
    break;


#line 1093 "Parser.cpp" // lalr1.cc:859
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


  const signed char Parser::yypact_ninf_ = -93;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
     263,    -6,   -93,   -93,   -93,   -93,   -19,   -93,   -93,   -93,
     -93,   -93,   -93,   -33,   263,   -30,   -28,    -6,   -18,   -16,
      -6,   203,    -6,    92,   -93,    59,   -93,   -93,   -93,   -93,
       3,   -93,    -7,   -93,    -6,    -6,    -6,   -93,    -6,    -6,
     136,   -93,   -93,   149,   -93,   233,   -93,   -93,   -93,    -6,
      -6,    -6,    -6,    -6,    -6,    -6,    -6,    -6,    -6,    -6,
      -6,    -6,   -93,   -17,   -93,    15,   307,   -36,   307,   162,
     198,   307,    -4,   -93,   -93,   -93,   183,   183,    64,    64,
      64,    64,    64,    64,    84,    84,   -93,   -93,   -93,    19,
      -6,     2,   -93,   -93,    -6,   263,   263,    -6,    40,   -93,
     -15,   307,   307,   -93,   -93,    37,    67,    42,    19,    -6,
     -93,   -93,   -93,    50,   263,   -93
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,    44,    46,    45,    47,    24,    48,    49,    50,
      51,    52,    53,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     0,    20,    21,    23,    22,
       0,    15,    24,    41,    56,     0,     0,     8,     0,    26,
       0,    13,    12,     0,    55,     0,    42,     1,     3,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     4,    16,    18,     6,    57,     0,     5,     0,
       0,    27,     0,    11,    25,    54,    39,    40,    33,    34,
      35,    36,    37,    38,    28,    29,    30,    31,    32,    60,
       0,    16,    19,    43,     0,     0,     0,    26,     0,    61,
       0,    17,    58,     7,     9,     0,     0,     0,     0,    26,
      59,    14,    62,     0,     0,    10
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -93,    69,   -13,    26,   -93,    -1,   -92,   -93,   -93,   -93,
     -12,   -86,    -2,   -93,    -8,   -93
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,    23,    24,    64,    65,    25,    72,    26,    27,    28,
      29,    30,    31,    67,    99,   100
  };

  const unsigned char
  Parser::yytable_[] =
  {
      33,    37,    93,    98,    36,   105,     1,    38,    94,    39,
      48,     2,     3,     4,     5,    32,    40,   113,    34,    43,
      89,    46,    98,   107,    63,    41,    35,    42,    90,   108,
      34,    20,    48,    66,    68,    69,    91,    70,    71,    97,
      22,     7,     8,     9,    10,    11,    12,    90,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,   106,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    57,    58,    59,    60,    61,
     109,    21,   103,   104,     2,     3,     4,     5,   114,   101,
      45,    92,    47,   102,   110,     0,    71,    59,    60,    61,
     112,   115,    62,     0,     1,   111,     0,     0,    71,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,     0,     0,    17,    18,    19,    20,
       0,    21,     0,     0,     0,     0,     0,     0,    22,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,     0,    73,
       0,     0,     0,     0,     0,     0,     0,    74,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,     0,
      95,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,     0,     1,     0,     0,     0,     0,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,     0,    96,    17,    18,    19,
      20,     0,    21,    44,     0,     1,     0,     0,     0,    22,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,     0,     0,    17,    18,    19,
      20,     0,    21,    75,     0,     1,     0,     0,     0,    22,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,     0,     0,    17,    18,    19,
      20,     0,    21,     0,     0,     0,     0,     0,     0,    22,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61
  };

  const signed char
  Parser::yycheck_[] =
  {
       1,    14,    38,    89,    37,    97,    12,    37,    44,    37,
      23,    17,    18,    19,    20,    21,    17,   109,    37,    20,
      37,    22,   108,    38,    21,    43,    45,    43,    45,    44,
      37,    37,    45,    34,    35,    36,    21,    38,    39,    43,
      46,    22,    23,    24,    25,    26,    27,    45,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    21,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    11,    12,    13,    14,    15,
      43,    39,    95,    96,    17,    18,    19,    20,    38,    90,
      21,    65,     0,    94,   106,    -1,    97,    13,    14,    15,
     108,   114,    43,    -1,    12,   107,    -1,    -1,   109,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    34,    35,    36,    37,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      38,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    12,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    38,    34,    35,    36,
      37,    -1,    39,    40,    -1,    12,    -1,    -1,    -1,    46,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    34,    35,    36,
      37,    -1,    39,    40,    -1,    12,    -1,    -1,    -1,    46,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    34,    35,    36,
      37,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    12,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    34,    35,    36,
      37,    39,    46,    60,    61,    64,    66,    67,    68,    69,
      70,    71,    21,    64,    37,    45,    37,    61,    37,    37,
      64,    43,    43,    64,    40,    60,    64,     0,    61,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    43,    21,    62,    63,    64,    72,    64,    64,
      64,    64,    65,    43,    38,    40,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    37,
      45,    21,    62,    38,    44,    38,    38,    43,    70,    73,
      74,    64,    64,    61,    61,    65,    21,    38,    44,    43,
      69,    71,    73,    65,    38,    61
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    59,    60,    60,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    62,    62,    63,    63,
      64,    64,    64,    64,    64,    64,    65,    65,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    67,    67,    68,    69,    69,    69,    69,    70,    70,
      70,    70,    70,    70,    71,    71,    72,    72,    72,    73,
      74,    74,    74
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     2,     3,     2,     5,     2,     5,
       9,     3,     2,     2,     6,     1,     1,     3,     1,     2,
       1,     1,     1,     1,     1,     3,     0,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     2,     0,     1,     3,     3,
       0,     1,     3
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
  "VAR", "IF", "ELSE", "ELSEIF", "FOR", "IN", "CLASS", "RETURN", "BREAK",
  "CONTINUE", "LP", "RP", "LC", "RC", "LB", "RB", "SEMICOLON", "COMMA",
  "ASSIGN", "EXCLAMATION", "DOT", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN",
  "DIV_ASSIGN", "MOD_ASSIGN", "INCREMENT", "DECREMENT", "PUBLIC",
  "PROTECTED", "PRIVATE", "REVERSE", "$accept", "statements_list",
  "statement", "declaration_item", "declaration_item_list", "expression",
  "expression_optional", "binary_expression", "unary_expression",
  "function_call_expression", "primary_expression", "type_tag", "block",
  "arguments_list", "parameter", "parameters_list", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,    57,    57,    61,    67,    71,    75,    79,    84,    89,
      94,    98,   102,   106,   110,   114,   116,   120,   125,   129,
     135,   136,   137,   138,   139,   143,   149,   152,   154,   158,
     162,   166,   170,   174,   178,   182,   186,   190,   194,   198,
     202,   207,   211,   216,   221,   222,   223,   224,   236,   240,
     244,   248,   252,   256,   261,   265,   271,   274,   278,   284,
     290,   293,   297
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


#line 20 "newbie++.y" // lalr1.cc:1167
} } // zyd2001::NewBie
#line 1584 "Parser.cpp" // lalr1.cc:1167
#line 303 "newbie++.y" // lalr1.cc:1168


void Parser::error(const location_type& l, const std::string& m)
{
	std::cerr << l << " " << m << endl;
}
