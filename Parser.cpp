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
      case 76: // arguments_list
        value.move< zyd2001::NewBie::ArgumentsList > (that.value);
        break;

      case 65: // declaration_item
        value.move< zyd2001::NewBie::DeclarationStatementItem > (that.value);
        break;

      case 66: // declaration_item_list
        value.move< zyd2001::NewBie::DeclarationStatementItemList > (that.value);
        break;

      case 17: // INT_LITERAL
      case 18: // STRING_LITERAL
      case 19: // DOUBLE_LITERAL
      case 20: // BOOL_LITERAL
      case 67: // expression
      case 68: // expression_optional
      case 70: // binary_expression
      case 71: // unary_expression
      case 72: // function_call_expression
      case 73: // primary_expression
        value.move< zyd2001::NewBie::Expression > (that.value);
        break;

      case 21: // IDENTIFIER
        value.move< zyd2001::NewBie::Identifier > (that.value);
        break;

      case 77: // parameter
        value.move< zyd2001::NewBie::Parameter > (that.value);
        break;

      case 78: // parameters_list
        value.move< zyd2001::NewBie::ParametersList > (that.value);
        break;

      case 64: // statement
      case 69: // statement_optional
      case 75: // block
        value.move< zyd2001::NewBie::Statement > (that.value);
        break;

      case 63: // statements_list
        value.move< zyd2001::NewBie::StatementsList > (that.value);
        break;

      case 74: // type_tag
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
      case 76: // arguments_list
        value.copy< zyd2001::NewBie::ArgumentsList > (that.value);
        break;

      case 65: // declaration_item
        value.copy< zyd2001::NewBie::DeclarationStatementItem > (that.value);
        break;

      case 66: // declaration_item_list
        value.copy< zyd2001::NewBie::DeclarationStatementItemList > (that.value);
        break;

      case 17: // INT_LITERAL
      case 18: // STRING_LITERAL
      case 19: // DOUBLE_LITERAL
      case 20: // BOOL_LITERAL
      case 67: // expression
      case 68: // expression_optional
      case 70: // binary_expression
      case 71: // unary_expression
      case 72: // function_call_expression
      case 73: // primary_expression
        value.copy< zyd2001::NewBie::Expression > (that.value);
        break;

      case 21: // IDENTIFIER
        value.copy< zyd2001::NewBie::Identifier > (that.value);
        break;

      case 77: // parameter
        value.copy< zyd2001::NewBie::Parameter > (that.value);
        break;

      case 78: // parameters_list
        value.copy< zyd2001::NewBie::ParametersList > (that.value);
        break;

      case 64: // statement
      case 69: // statement_optional
      case 75: // block
        value.copy< zyd2001::NewBie::Statement > (that.value);
        break;

      case 63: // statements_list
        value.copy< zyd2001::NewBie::StatementsList > (that.value);
        break;

      case 74: // type_tag
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
      case 76: // arguments_list
        yylhs.value.build< zyd2001::NewBie::ArgumentsList > ();
        break;

      case 65: // declaration_item
        yylhs.value.build< zyd2001::NewBie::DeclarationStatementItem > ();
        break;

      case 66: // declaration_item_list
        yylhs.value.build< zyd2001::NewBie::DeclarationStatementItemList > ();
        break;

      case 17: // INT_LITERAL
      case 18: // STRING_LITERAL
      case 19: // DOUBLE_LITERAL
      case 20: // BOOL_LITERAL
      case 67: // expression
      case 68: // expression_optional
      case 70: // binary_expression
      case 71: // unary_expression
      case 72: // function_call_expression
      case 73: // primary_expression
        yylhs.value.build< zyd2001::NewBie::Expression > ();
        break;

      case 21: // IDENTIFIER
        yylhs.value.build< zyd2001::NewBie::Identifier > ();
        break;

      case 77: // parameter
        yylhs.value.build< zyd2001::NewBie::Parameter > ();
        break;

      case 78: // parameters_list
        yylhs.value.build< zyd2001::NewBie::ParametersList > ();
        break;

      case 64: // statement
      case 69: // statement_optional
      case 75: // block
        yylhs.value.build< zyd2001::NewBie::Statement > ();
        break;

      case 63: // statements_list
        yylhs.value.build< zyd2001::NewBie::StatementsList > ();
        break;

      case 74: // type_tag
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
			inter.statements_list = yystack_[1].value.as< zyd2001::NewBie::StatementsList > ();
		}

    break;

  case 3:

    {
            yylhs.value.as< zyd2001::NewBie::StatementsList > ().emplace_back(yystack_[0].value.as< zyd2001::NewBie::Statement > ());
        }

    break;

  case 4:

    {
            yystack_[1].value.as< zyd2001::NewBie::StatementsList > ().emplace_back(yystack_[0].value.as< zyd2001::NewBie::Statement > ());
            yylhs.value.as< zyd2001::NewBie::StatementsList > ().swap(yystack_[1].value.as< zyd2001::NewBie::StatementsList > ());
        }

    break;

  case 5:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(EXPRESSION_STATEMENT, new ExpressionStatement(yystack_[1].value.as< zyd2001::NewBie::Expression > ()), yyget_lineno(scanner));
        }

    break;

  case 6:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(ASSIGNMENT_STATEMENT, new (AssignmentStatement){std::move(yystack_[3].value.as< zyd2001::NewBie::Identifier > ()), yystack_[1].value.as< zyd2001::NewBie::Expression > ()}, yyget_lineno(scanner));
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
            current_if = new (IfStatement){yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Statement > ()};
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(IF_STATEMENT, current_if, yyget_lineno(scanner));
        }

    break;

  case 10:

    {
            current_if->else_stat = yystack_[0].value.as< zyd2001::NewBie::Statement > ();
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement();
        }

    break;

  case 11:

    {
            ElseIf e = {yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Statement > ()};
            current_if->elseif.emplace_back(e);
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement();
        }

    break;

  case 12:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(FOR_STATEMENT, new (ForStatement){yystack_[6].value.as< zyd2001::NewBie::Statement > (), yystack_[4].value.as< zyd2001::NewBie::Expression > (), yystack_[2].value.as< zyd2001::NewBie::Statement > (), yystack_[0].value.as< zyd2001::NewBie::Statement > ()}, yyget_lineno(scanner));
        }

    break;

  case 13:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(RETURN_STATEMENT, new ReturnStatement(yystack_[1].value.as< zyd2001::NewBie::Expression > ()), yyget_lineno(scanner));
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
            VariablesMap &vmap = inter.global_variables;
            auto result = vmap.find(yystack_[4].value.as< zyd2001::NewBie::Identifier > ());
            if (result != vmap.cend())
            {
                auto &func = result->second.get<Function>();
                auto exist = func.overload_map.find(yystack_[2].value.as< zyd2001::NewBie::ParametersList > ());
                if (exist == func.overload_map.cend())
                    func.overload_map[yystack_[2].value.as< zyd2001::NewBie::ParametersList > ()] = std::move(yystack_[0].value.as< zyd2001::NewBie::Statement > ());
                else
                    inter.err();
            }
            else
            {
                auto func = new Function();
                vmap[yystack_[4].value.as< zyd2001::NewBie::Identifier > ()] = Value(FUNCTION_TYPE, func);
                func->overload_map[yystack_[2].value.as< zyd2001::NewBie::ParametersList > ()] = yystack_[0].value.as< zyd2001::NewBie::Statement > ();
            }
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement();
        }

    break;

  case 17:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = yystack_[0].value.as< zyd2001::NewBie::Statement > ();
        }

    break;

  case 18:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(DEBUG_STATEMENT, new DebugStatement(yystack_[1].value.as< zyd2001::NewBie::Expression > ()), yyget_lineno(scanner));
        }

    break;

  case 19:

    {
            yylhs.value.as< zyd2001::NewBie::DeclarationStatementItem > () = {std::move(yystack_[0].value.as< zyd2001::NewBie::Identifier > ())};
        }

    break;

  case 20:

    {
            yylhs.value.as< zyd2001::NewBie::DeclarationStatementItem > () = {std::move(yystack_[2].value.as< zyd2001::NewBie::Identifier > ()), yystack_[0].value.as< zyd2001::NewBie::Expression > ()};
        }

    break;

  case 21:

    {
            yylhs.value.as< zyd2001::NewBie::DeclarationStatementItemList > ().emplace_back(std::move(yystack_[0].value.as< zyd2001::NewBie::DeclarationStatementItem > ()));
        }

    break;

  case 22:

    {
            yystack_[2].value.as< zyd2001::NewBie::DeclarationStatementItemList > ().emplace_back(std::move(yystack_[0].value.as< zyd2001::NewBie::DeclarationStatementItem > ()));
            yylhs.value.as< zyd2001::NewBie::DeclarationStatementItemList > ().swap(yystack_[2].value.as< zyd2001::NewBie::DeclarationStatementItemList > ());
        }

    break;

  case 23:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = yystack_[0].value.as< zyd2001::NewBie::Expression > ();
        }

    break;

  case 24:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = yystack_[0].value.as< zyd2001::NewBie::Expression > ();
        }

    break;

  case 25:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = yystack_[0].value.as< zyd2001::NewBie::Expression > ();
        }

    break;

  case 26:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = yystack_[0].value.as< zyd2001::NewBie::Expression > ();
        }

    break;

  case 27:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(IDENTIFIER_EXPRESSION, new IdentifierExpression(std::move(yystack_[0].value.as< zyd2001::NewBie::Identifier > ())));
        }

    break;

  case 28:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = yystack_[1].value.as< zyd2001::NewBie::Expression > ();
        }

    break;

  case 29:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression();
        }

    break;

  case 30:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = yystack_[0].value.as< zyd2001::NewBie::Expression > ();
        }

    break;

  case 31:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement();
        }

    break;

  case 32:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(EXPRESSION_STATEMENT, new ExpressionStatement(yystack_[0].value.as< zyd2001::NewBie::Expression > ()), yyget_lineno(scanner));
        }

    break;

  case 33:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(ASSIGNMENT_STATEMENT, new (AssignmentStatement){std::move(yystack_[2].value.as< zyd2001::NewBie::Identifier > ()), yystack_[0].value.as< zyd2001::NewBie::Expression > ()}, yyget_lineno(scanner));
        }

    break;

  case 34:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(DECLARATION_STATEMENT, new (DeclarationStatement){std::move(yystack_[1].value.as< zyd2001::NewBie::ValueType > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::DeclarationStatementItemList > ()), false}, yyget_lineno(scanner));
        }

    break;

  case 35:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(DECLARATION_STATEMENT, new (DeclarationStatement){std::move(yystack_[1].value.as< zyd2001::NewBie::ValueType > ()), std::move(yystack_[0].value.as< zyd2001::NewBie::DeclarationStatementItemList > ()), true}, yyget_lineno(scanner));
        }

    break;

  case 36:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){ADD, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }

    break;

  case 37:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){SUB, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }

    break;

  case 38:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){MUL, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }

    break;

  case 39:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){DIV, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }

    break;

  case 40:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){MOD, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }

    break;

  case 41:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){EQ, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }

    break;

  case 42:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){NE, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }

    break;

  case 43:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){GT, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }

    break;

  case 44:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){GE, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }

    break;

  case 45:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){LT, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }

    break;

  case 46:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){LE, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }

    break;

  case 47:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){AND, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }

    break;

  case 48:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){OR, yystack_[2].value.as< zyd2001::NewBie::Expression > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }

    break;

  case 49:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(UNARY_EXPRESSION, new (UnaryExpression){MINUS, yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }

    break;

  case 50:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(UNARY_EXPRESSION, new (UnaryExpression){NOT, yystack_[0].value.as< zyd2001::NewBie::Expression > ()});
        }

    break;

  case 51:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = Expression(FUNCTION_CALL_EXPRESSION, new (FunctionCallExpression){yystack_[3].value.as< zyd2001::NewBie::Identifier > (), yystack_[1].value.as< zyd2001::NewBie::ArgumentsList > ()});
        }

    break;

  case 52:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = yystack_[0].value.as< zyd2001::NewBie::Expression > ();
        }

    break;

  case 53:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = yystack_[0].value.as< zyd2001::NewBie::Expression > ();
        }

    break;

  case 54:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = yystack_[0].value.as< zyd2001::NewBie::Expression > ();
        }

    break;

  case 55:

    {
            yylhs.value.as< zyd2001::NewBie::Expression > () = yystack_[0].value.as< zyd2001::NewBie::Expression > ();
        }

    break;

  case 56:

    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = INT_TYPE;
        }

    break;

  case 57:

    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = DOUBLE_TYPE;
        }

    break;

  case 58:

    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = BOOL_TYPE;
        }

    break;

  case 59:

    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = STRING_TYPE;
        }

    break;

  case 60:

    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = ARRAY_TYPE;
        }

    break;

  case 61:

    {
            yylhs.value.as< zyd2001::NewBie::ValueType > () = VARIOUS_TYPE;
        }

    break;

  case 62:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(BLOCK_STATEMENT, new BlockStatement(std::move(yystack_[1].value.as< zyd2001::NewBie::StatementsList > ())), yyget_lineno(scanner));
        }

    break;

  case 63:

    {
            yylhs.value.as< zyd2001::NewBie::Statement > () = Statement(BLOCK_STATEMENT, new BlockStatement(), yyget_lineno(scanner));
        }

    break;

  case 64:

    {
            yylhs.value.as< zyd2001::NewBie::ArgumentsList > ();
        }

    break;

  case 65:

    {
            yylhs.value.as< zyd2001::NewBie::ArgumentsList > ().emplace_back(yystack_[0].value.as< zyd2001::NewBie::Expression > ());
        }

    break;

  case 66:

    {
            yystack_[2].value.as< zyd2001::NewBie::ArgumentsList > ().emplace_back(yystack_[0].value.as< zyd2001::NewBie::Expression > ());
            yylhs.value.as< zyd2001::NewBie::ArgumentsList > ().swap(yystack_[2].value.as< zyd2001::NewBie::ArgumentsList > ());
        }

    break;

  case 67:

    {
            yylhs.value.as< zyd2001::NewBie::Parameter > () = {yystack_[1].value.as< zyd2001::NewBie::ValueType > (), yystack_[0].value.as< zyd2001::NewBie::Identifier > ()};
        }

    break;

  case 68:

    {
            yylhs.value.as< zyd2001::NewBie::Parameter > () = {yystack_[2].value.as< zyd2001::NewBie::ValueType > (), yystack_[1].value.as< zyd2001::NewBie::Identifier > (), yystack_[0].value.as< zyd2001::NewBie::Expression > ()};
        }

    break;

  case 69:

    {
            yylhs.value.as< zyd2001::NewBie::ParametersList > ();
        }

    break;

  case 70:

    {
            yylhs.value.as< zyd2001::NewBie::ParametersList > ().emplace_back(std::move(yystack_[0].value.as< zyd2001::NewBie::Parameter > ()));
        }

    break;

  case 71:

    {
            yystack_[2].value.as< zyd2001::NewBie::ParametersList > ().emplace_back(std::move(yystack_[0].value.as< zyd2001::NewBie::Parameter > ()));
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


  const signed char Parser::yypact_ninf_ = -37;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
     245,   412,   -37,   -37,   -37,   -37,   -33,   -37,   -37,   -37,
     -37,   -37,   -37,     3,   -30,   245,   -29,   -27,   412,   -28,
     -25,   412,   157,   412,   412,    21,   113,   -37,   303,   -37,
     -37,   -37,   -37,    10,   -37,    -5,   -37,   412,   412,    13,
     412,   -37,   412,    60,   316,   -37,   -37,   384,   -37,   201,
     -37,   329,   -37,   -37,   -37,   412,   412,   412,   412,   412,
     412,   412,   412,   412,   412,   412,   412,   412,   -37,   -32,
     -37,    23,   457,   -35,   371,    -8,    29,   397,   434,   -31,
       3,   457,    -4,    13,   -37,   -37,   -37,   -37,   288,   288,
      37,    37,    37,    37,    37,    37,    78,    78,   -37,   -37,
     -37,     3,   412,   -37,    13,   -37,   412,   -37,   -37,   245,
     245,   412,    13,   412,     8,    49,   -37,   -21,   457,   -37,
     457,   -37,   -37,   457,     8,   457,    27,    26,    35,     3,
      60,   -37,   -37,   -37,    50,   245,   -37
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,    52,    54,    53,    55,    27,    56,    57,    58,
      59,    60,    61,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     3,     0,    23,
      24,    26,    25,     0,    17,    27,    49,    64,     0,     0,
       0,    10,     0,    31,     0,    15,    14,     0,    63,     0,
      50,     0,     1,     2,     4,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,    19,
      21,     0,    65,     0,     0,    19,     0,     0,     0,    27,
       0,    32,     0,     0,    13,    28,    62,    18,    47,    48,
      41,    42,    43,    44,    45,    46,    36,    37,    38,    39,
      40,    69,     0,     7,     0,    51,     0,     6,     8,     0,
       0,     0,     0,    29,    34,     0,    70,     0,    20,    22,
      66,     9,    11,    33,    35,    30,     0,    67,     0,     0,
      31,    68,    16,    71,     0,     0,    12
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -37,   -37,    72,   -14,    -7,   -36,    -1,   -37,   -26,   -37,
     -37,   -37,   -24,   -11,   -22,   -37,   -20,   -37
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,    25,    26,    27,    70,    71,    28,   126,    82,    29,
      30,    31,    32,    33,    34,    73,   116,   117
  };

  const unsigned char
  Parser::yytable_[] =
  {
      36,    41,    39,    76,   105,    37,   101,    37,    40,    42,
     106,    43,    54,    38,   102,   111,    45,    44,   128,    46,
      47,    52,    50,    51,   129,     7,     8,     9,    10,    11,
      12,    69,    83,    37,    75,    54,    72,    74,   102,    77,
     113,    78,    81,     2,     3,     4,     5,   114,    63,    64,
      65,    66,    67,   104,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   103,   104,   112,
     127,   130,     1,   108,   104,    22,   124,     2,     3,     4,
       5,    79,     7,     8,     9,    10,    11,    12,    80,   135,
     115,    65,    66,    67,    49,   121,   122,   119,    21,     0,
       0,   118,     0,   131,   134,   120,   132,    23,     0,   133,
     123,     0,   125,    53,     0,     0,     0,     0,   115,    83,
       0,   136,     0,     0,     0,     1,     0,     0,     0,    81,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,     0,     0,    18,    19,
      20,    21,     0,    22,     0,     0,     0,     0,     0,     0,
      23,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       0,     0,     0,    24,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       0,     0,    18,    19,    20,    21,     0,    22,    48,     0,
       0,     0,     0,     0,    23,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     0,     0,     0,    24,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,     0,     0,    18,    19,    20,    21,
       0,    22,    86,     0,     0,     0,     0,     0,    23,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     0,     0,
       0,    24,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     0,     0,
      18,    19,    20,    21,     0,    22,     0,     0,     0,     0,
       0,     0,    23,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,     0,    24,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,     0,     0,    68,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      84,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    87,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,     0,     0,   107,     0,     0,     0,     0,
       0,     0,     0,    85,     1,     0,     0,     0,     0,     2,
       3,     4,     5,    35,     0,     0,   109,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      21,     0,     0,     0,     0,     0,     0,     0,     0,    23,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,   110
  };

  const short int
  Parser::yycheck_[] =
  {
       1,    15,    13,    39,    39,    38,    38,    38,    38,    38,
      45,    38,    26,    46,    46,    46,    44,    18,    39,    44,
      21,     0,    23,    24,    45,    22,    23,    24,    25,    26,
      27,    21,    43,    38,    21,    49,    37,    38,    46,    40,
      44,    42,    43,    17,    18,    19,    20,    83,    11,    12,
      13,    14,    15,    45,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    44,    45,    80,
      21,    44,    12,    44,    45,    40,   112,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    39,
     101,    13,    14,    15,    22,   109,   110,   104,    38,    -1,
      -1,   102,    -1,   127,   130,   106,   128,    47,    -1,   129,
     111,    -1,   113,     0,    -1,    -1,    -1,    -1,   129,   130,
      -1,   135,    -1,    -1,    -1,    12,    -1,    -1,    -1,   130,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    60,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    -1,    40,    41,    -1,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    60,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      -1,    40,    41,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,
      -1,    60,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    47,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    60,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    12,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    -1,    -1,    39,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    39
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    12,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    35,    36,
      37,    38,    40,    47,    60,    62,    63,    64,    67,    70,
      71,    72,    73,    74,    75,    21,    67,    38,    46,    74,
      38,    64,    38,    38,    67,    44,    44,    67,    41,    63,
      67,    67,     0,     0,    64,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    44,    21,
      65,    66,    67,    76,    67,    21,    66,    67,    67,    21,
      28,    67,    69,    74,    44,    39,    41,    44,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    38,    46,    44,    45,    39,    45,    44,    44,    39,
      39,    46,    74,    44,    66,    74,    77,    78,    67,    65,
      67,    64,    64,    67,    66,    67,    68,    21,    39,    45,
      44,    73,    75,    77,    69,    39,    64
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    61,    62,    63,    63,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    65,
      65,    66,    66,    67,    67,    67,    67,    67,    67,    68,
      68,    69,    69,    69,    69,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    71,
      71,    72,    73,    73,    73,    73,    74,    74,    74,    74,
      74,    74,    75,    75,    76,    76,    76,    77,    77,    78,
      78,    78
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     2,     2,     4,     3,     4,     5,
       2,     5,     9,     3,     2,     2,     6,     1,     3,     1,
       3,     1,     3,     1,     1,     1,     1,     1,     3,     0,
       1,     0,     1,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     0,     1,     3,     2,     3,     0,
       1,     3
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
  "PUBLIC", "PROTECTED", "PRIVATE", "REVERSE", "PRINT", "$accept", "eof",
  "statements_list", "statement", "declaration_item",
  "declaration_item_list", "expression", "expression_optional",
  "statement_optional", "binary_expression", "unary_expression",
  "function_call_expression", "primary_expression", "type_tag", "block",
  "arguments_list", "parameter", "parameters_list", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,    60,    60,    65,    69,    75,    79,    83,    87,    91,
      96,   101,   107,   111,   115,   119,   123,   144,   148,   153,
     157,   162,   166,   178,   182,   186,   190,   194,   198,   204,
     207,   213,   216,   220,   224,   228,   233,   237,   241,   245,
     249,   253,   257,   261,   265,   269,   273,   277,   281,   286,
     290,   295,   300,   304,   308,   312,   327,   331,   335,   339,
     343,   347,   352,   356,   362,   365,   369,   375,   379,   385,
     388,   392
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
	std::cerr << "At file " << inter.filename  << " " << l << " " << m << endl;
}
