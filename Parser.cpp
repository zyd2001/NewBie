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
	Parser::symbol_type yylex(InterpreterImp &inter, yyscan_t yyscanner);




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
  Parser::Parser (InterpreterImp &inter_yyarg, yyscan_t scanner_yyarg)
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
      case 71: // declaration_item
        value.move< DeclarationStatementItem > (that.value);
        break;

      case 72: // declaration_items_list
        value.move< DeclarationStatementItemsList > (that.value);
        break;

      case 17: // INT_LITERAL
      case 18: // STRING_LITERAL
      case 19: // DOUBLE_LITERAL
      case 20: // BOOL_LITERAL
      case 74: // expression
      case 75: // index_expression
      case 76: // array_expression
      case 77: // dot_expression
      case 78: // dot_pre_expression
      case 79: // expression_optional
      case 81: // binary_expression
      case 82: // unary_expression
      case 83: // function_call_expression
      case 84: // primary_expression
        value.move< Expression > (that.value);
        break;

      case 85: // expressions_list
      case 88: // arguments_list
        value.move< ExpressionsList > (that.value);
        break;

      case 21: // IDENTIFIER
        value.move< Identifier > (that.value);
        break;

      case 89: // parameter
        value.move< Parameter > (that.value);
        break;

      case 90: // parameters_list
        value.move< ParametersList > (that.value);
        break;

      case 68: // statement
      case 69: // assignment_statement
      case 70: // declaration_statement
      case 73: // class_definition
      case 80: // statement_optional
      case 87: // block
        value.move< Statement > (that.value);
        break;

      case 67: // statements_list
        value.move< StatementsList > (that.value);
        break;

      case 86: // type_tag
        value.move< ValueType > (that.value);
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
      case 71: // declaration_item
        value.copy< DeclarationStatementItem > (that.value);
        break;

      case 72: // declaration_items_list
        value.copy< DeclarationStatementItemsList > (that.value);
        break;

      case 17: // INT_LITERAL
      case 18: // STRING_LITERAL
      case 19: // DOUBLE_LITERAL
      case 20: // BOOL_LITERAL
      case 74: // expression
      case 75: // index_expression
      case 76: // array_expression
      case 77: // dot_expression
      case 78: // dot_pre_expression
      case 79: // expression_optional
      case 81: // binary_expression
      case 82: // unary_expression
      case 83: // function_call_expression
      case 84: // primary_expression
        value.copy< Expression > (that.value);
        break;

      case 85: // expressions_list
      case 88: // arguments_list
        value.copy< ExpressionsList > (that.value);
        break;

      case 21: // IDENTIFIER
        value.copy< Identifier > (that.value);
        break;

      case 89: // parameter
        value.copy< Parameter > (that.value);
        break;

      case 90: // parameters_list
        value.copy< ParametersList > (that.value);
        break;

      case 68: // statement
      case 69: // assignment_statement
      case 70: // declaration_statement
      case 73: // class_definition
      case 80: // statement_optional
      case 87: // block
        value.copy< Statement > (that.value);
        break;

      case 67: // statements_list
        value.copy< StatementsList > (that.value);
        break;

      case 86: // type_tag
        value.copy< ValueType > (that.value);
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
      case 71: // declaration_item
        yylhs.value.build< DeclarationStatementItem > ();
        break;

      case 72: // declaration_items_list
        yylhs.value.build< DeclarationStatementItemsList > ();
        break;

      case 17: // INT_LITERAL
      case 18: // STRING_LITERAL
      case 19: // DOUBLE_LITERAL
      case 20: // BOOL_LITERAL
      case 74: // expression
      case 75: // index_expression
      case 76: // array_expression
      case 77: // dot_expression
      case 78: // dot_pre_expression
      case 79: // expression_optional
      case 81: // binary_expression
      case 82: // unary_expression
      case 83: // function_call_expression
      case 84: // primary_expression
        yylhs.value.build< Expression > ();
        break;

      case 85: // expressions_list
      case 88: // arguments_list
        yylhs.value.build< ExpressionsList > ();
        break;

      case 21: // IDENTIFIER
        yylhs.value.build< Identifier > ();
        break;

      case 89: // parameter
        yylhs.value.build< Parameter > ();
        break;

      case 90: // parameters_list
        yylhs.value.build< ParametersList > ();
        break;

      case 68: // statement
      case 69: // assignment_statement
      case 70: // declaration_statement
      case 73: // class_definition
      case 80: // statement_optional
      case 87: // block
        yylhs.value.build< Statement > ();
        break;

      case 67: // statements_list
        yylhs.value.build< StatementsList > ();
        break;

      case 86: // type_tag
        yylhs.value.build< ValueType > ();
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
			inter.statements_list = yystack_[1].value.as< StatementsList > ();
		}

    break;

  case 3:

    {
            yylhs.value.as< StatementsList > ().emplace_back(yystack_[0].value.as< Statement > ());
        }

    break;

  case 4:

    {
            yystack_[1].value.as< StatementsList > ().emplace_back(yystack_[0].value.as< Statement > ());
            yylhs.value.as< StatementsList > ().swap(yystack_[1].value.as< StatementsList > ());
        }

    break;

  case 5:

    {
            yylhs.value.as< Statement > () = Statement(EXPRESSION_STATEMENT, new ExpressionStatement(yystack_[1].value.as< Expression > ()), yyget_lineno(scanner));
        }

    break;

  case 6:

    {
            current_if = new (IfStatement){yystack_[2].value.as< Expression > (), yystack_[0].value.as< Statement > ()};
            yylhs.value.as< Statement > () = Statement(IF_STATEMENT, current_if, yyget_lineno(scanner));
        }

    break;

  case 7:

    {
            current_if->else_stat = yystack_[0].value.as< Statement > ();
            yylhs.value.as< Statement > () = Statement();
        }

    break;

  case 8:

    {
            ElseIf e = {yystack_[2].value.as< Expression > (), yystack_[0].value.as< Statement > ()};
            current_if->elseif.emplace_back(e);
            yylhs.value.as< Statement > () = Statement();
        }

    break;

  case 9:

    {
            yylhs.value.as< Statement > () = Statement(FOR_STATEMENT, new (ForStatement){yystack_[6].value.as< Statement > (), yystack_[4].value.as< Expression > (), yystack_[2].value.as< Statement > (), yystack_[0].value.as< Statement > ()}, yyget_lineno(scanner));
        }

    break;

  case 10:

    {
            yylhs.value.as< Statement > () = Statement(FOREACH_STATEMENT, new (ForeachStatement){yystack_[4].value.as< Identifier > (), yystack_[2].value.as< Expression > (), yystack_[0].value.as< Statement > (), false}, yyget_lineno(scanner));
        }

    break;

  case 11:

    {
            yylhs.value.as< Statement > () = Statement(FOREACH_STATEMENT, new (ForeachStatement){yystack_[5].value.as< Identifier > (), yystack_[2].value.as< Expression > (), yystack_[0].value.as< Statement > (), true}, yyget_lineno(scanner));
        }

    break;

  case 12:

    {
            yylhs.value.as< Statement > () = Statement(RETURN_STATEMENT, new ReturnStatement(yystack_[1].value.as< Expression > ()), yyget_lineno(scanner));
        }

    break;

  case 13:

    {
            yylhs.value.as< Statement > () = Statement(CONTINUE_STATEMENT, nullptr, yyget_lineno(scanner));
        }

    break;

  case 14:

    {
            yylhs.value.as< Statement > () = Statement(BREAK_STATEMENT, nullptr, yyget_lineno(scanner));
        }

    break;

  case 15:

    {
            VariablesMap *vmap;
            if (inter.in_class)
                vmap = &inter.current_class->static_variables;
            else
                vmap = &inter.global_variables;
            auto result = (*vmap).find(yystack_[4].value.as< Identifier > ());
            if (result != (*vmap).cend())
            {
                auto &func = result->second.get<Function>();
                if (func->can_overload)
                {
                    auto exist = func->overload_map.find(yystack_[2].value.as< ParametersList > ());
                    if (exist == func->overload_map.cend())
                    {
                        for (auto &i : yystack_[2].value.as< ParametersList > ())
                        {
                            if (i.type == VARIANT_TYPE || i.default_value_exp.type != NULL_EXPRESSION)
                            {
                                inter.err();
                                break;
                            }
                        }
                        func->overload_map[yystack_[2].value.as< ParametersList > ()] = yystack_[0].value.as< Statement > ();
                    }
                    else
                        inter.err();
                }
                else
                    inter.err();
                yylhs.value.as< Statement > () = Statement();
            }
            else
            {
                auto ptr = new Function(make_shared<function_t>());
                auto &func = *ptr;
                func->return_type = yystack_[5].value.as< ValueType > ();
                func->can_overload = true;
                Value function(FUNCTION_TYPE, ptr);
                (*vmap)[yystack_[4].value.as< Identifier > ()] = function;
                func->overload_map[yystack_[2].value.as< ParametersList > ()] = yystack_[0].value.as< Statement > ();
                for (auto &i : yystack_[2].value.as< ParametersList > ())
                {
                    if (i.type == VARIANT_TYPE || i.default_value_exp.type != NULL_EXPRESSION)
                    {
                        func->can_overload = false;
                        break;
                    }
                }
                yylhs.value.as< Statement > () = Statement(FUNCTION_DEFINITION_STATEMENT, new VariablesMap::value_type(yystack_[4].value.as< Identifier > (), function), yyget_lineno(scanner));
            }
        }

    break;

  case 16:

    {
            auto &func = inter.current_class->ctor;
            if (func->overload_map.empty())
            {
                func->can_overload = true;
                func->overload_map[yystack_[2].value.as< ParametersList > ()] = yystack_[0].value.as< Statement > ();
                for (auto &i : yystack_[2].value.as< ParametersList > ())
                {
                    if (i.type == VARIANT_TYPE || i.default_value_exp.type != NULL_EXPRESSION)
                    {
                        func->can_overload = false;
                        break;
                    }
                }
            }
            else if (func->can_overload)
            {
                auto exist = func->overload_map.find(yystack_[2].value.as< ParametersList > ());
                if (exist == func->overload_map.cend())
                {
                    for (auto &i : yystack_[2].value.as< ParametersList > ())
                    {
                        if (i.type == VARIANT_TYPE || i.default_value_exp.type != NULL_EXPRESSION)
                        {
                            inter.err();
                            break;
                        }
                    }
                    func->overload_map[yystack_[2].value.as< ParametersList > ()] = yystack_[0].value.as< Statement > ();
                }
                else
                    inter.err("exist");
            }
            else
                inter.err("can_overload");
            yylhs.value.as< Statement > () = Statement();
        }

    break;

  case 17:

    {
            yylhs.value.as< Statement > () = yystack_[0].value.as< Statement > ();
        }

    break;

  case 18:

    {
            yylhs.value.as< Statement > () = Statement(DEBUG_STATEMENT, new DebugStatement(yystack_[1].value.as< Expression > ()), yyget_lineno(scanner));
        }

    break;

  case 19:

    {
            yylhs.value.as< Statement > () = yystack_[0].value.as< Statement > ();
        }

    break;

  case 20:

    {
            yylhs.value.as< Statement > () = yystack_[0].value.as< Statement > ();
        }

    break;

  case 22:

    {
            yylhs.value.as< Statement > () = Statement(ASSIGNMENT_STATEMENT, new (AssignmentStatement){yystack_[3].value.as< Expression > (), yystack_[1].value.as< Expression > ()}, yyget_lineno(scanner));
        }

    break;

  case 23:

    {
            yylhs.value.as< Statement > () = Statement(DECLARATION_STATEMENT, new (DeclarationStatement){false, yystack_[2].value.as< ValueType > (), std::move(yystack_[1].value.as< DeclarationStatementItemsList > ())}, yyget_lineno(scanner));
        }

    break;

  case 24:

    {
            yylhs.value.as< Statement > () = Statement(DECLARATION_STATEMENT, new (DeclarationStatement){true, yystack_[2].value.as< ValueType > (), std::move(yystack_[1].value.as< DeclarationStatementItemsList > ())}, yyget_lineno(scanner));
        }

    break;

  case 25:

    {
            yylhs.value.as< Statement > () = Statement(DECLARATION_STATEMENT, new (DeclarationStatement){false, OBJECT_TYPE, std::move(yystack_[1].value.as< DeclarationStatementItemsList > ()), yystack_[2].value.as< Identifier > ()}, yyget_lineno(scanner));
        }

    break;

  case 26:

    {
            yylhs.value.as< Statement > () = Statement(DECLARATION_STATEMENT, new (DeclarationStatement){true, OBJECT_TYPE, std::move(yystack_[1].value.as< DeclarationStatementItemsList > ()), yystack_[2].value.as< Identifier > ()}, yyget_lineno(scanner));
        }

    break;

  case 27:

    {
            yylhs.value.as< DeclarationStatementItem > () = {yystack_[0].value.as< Identifier > ()};
        }

    break;

  case 28:

    {
            yylhs.value.as< DeclarationStatementItem > () = {yystack_[2].value.as< Identifier > (), yystack_[0].value.as< Expression > ()};
        }

    break;

  case 29:

    {
            yylhs.value.as< DeclarationStatementItemsList > ().emplace_back(std::move(yystack_[0].value.as< DeclarationStatementItem > ()));
        }

    break;

  case 30:

    {
            yystack_[2].value.as< DeclarationStatementItemsList > ().emplace_back(std::move(yystack_[0].value.as< DeclarationStatementItem > ()));
            yylhs.value.as< DeclarationStatementItemsList > ().swap(yystack_[2].value.as< DeclarationStatementItemsList > ());
        }

    break;

  case 31:

    {
            auto result = inter.class_map.find(yystack_[3].value.as< Identifier > ());
            if (result == inter.class_map.cend())
            {
                inter.current_class->type = yystack_[3].value.as< Identifier > ();
                inter.current_class->slist = yystack_[1].value.as< StatementsList > ();
                inter.current_class->parent = nullptr;
                inter.class_map[yystack_[3].value.as< Identifier > ()] = *inter.current_class;
                delete inter.current_class;
                inter.current_class = new Class();
                yylhs.value.as< Statement > () = Statement();
                inter.in_class = false;
            }
            else
                inter.err("class_definition");
        }

    break;

  case 32:

    {
            auto result = inter.class_map.find(yystack_[5].value.as< Identifier > ()), parent = inter.class_map.find(yystack_[3].value.as< Identifier > ());
            if (parent != inter.class_map.cend())
                inter.err("no parent");
            
            if (result == inter.class_map.cend())
            {
                inter.current_class->type = yystack_[5].value.as< Identifier > ();
                inter.current_class->slist = yystack_[1].value.as< StatementsList > ();
                inter.current_class->parent = &parent->second;
                inter.class_map[yystack_[5].value.as< Identifier > ()] = *inter.current_class;
                delete inter.current_class;
                inter.current_class = new Class();
                yylhs.value.as< Statement > () = Statement();
                inter.in_class = false;
            }
            else 
                inter.err("class exists");
        }

    break;

  case 33:

    {
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 34:

    {
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 35:

    {
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 36:

    {
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 37:

    {
            yylhs.value.as< Expression > () = Expression(IDENTIFIER_EXPRESSION, new IdentifierExpression(yystack_[0].value.as< Identifier > ()));
        }

    break;

  case 38:

    {
            yylhs.value.as< Expression > () = yystack_[1].value.as< Expression > ();
        }

    break;

  case 39:

    {
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 40:

    {
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 41:

    {
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 42:

    {
            yystack_[0].value.as< Expression > ().type = NEW_OBJECT_EXPRESSION;
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 43:

    {
            yylhs.value.as< Expression > () = Expression(ARRAY_LENGTH_EXPRESSION, new Expression(yystack_[1].value.as< Expression > ()));
        }

    break;

  case 44:

    {
            yylhs.value.as< Expression > () = Expression(INDEX_EXPRESSION, new (IndexExpression){Expression(IDENTIFIER_EXPRESSION, new IdentifierExpression(yystack_[3].value.as< Identifier > ())), yystack_[1].value.as< Expression > ()});
        }

    break;

  case 45:

    {
            yylhs.value.as< Expression > () = Expression(INDEX_EXPRESSION, new (IndexExpression){yystack_[3].value.as< Expression > (), yystack_[1].value.as< Expression > ()});
        }

    break;

  case 46:

    {
            yylhs.value.as< Expression > () = Expression(INDEX_EXPRESSION, new (IndexExpression){yystack_[3].value.as< Expression > (), yystack_[1].value.as< Expression > ()});
        }

    break;

  case 47:

    {
            yylhs.value.as< Expression > () = Expression(INDEX_EXPRESSION, new (IndexExpression){yystack_[3].value.as< Expression > (), yystack_[1].value.as< Expression > ()});
        }

    break;

  case 48:

    {
            yylhs.value.as< Expression > () = Expression(ARRAY_EXPRESSION, new ArrayExpression(std::move(yystack_[1].value.as< ExpressionsList > ())));
        }

    break;

  case 49:

    {
            yylhs.value.as< Expression > () = Expression(DOT_EXPRESSION, new (DotExpression){yystack_[2].value.as< Expression > (), yystack_[0].value.as< Expression > ()});
        }

    break;

  case 50:

    {
            yylhs.value.as< Expression > () = Expression(DOT_EXPRESSION, new (DotExpression){yystack_[2].value.as< Expression > (), Expression(IDENTIFIER_EXPRESSION, new IdentifierExpression(yystack_[0].value.as< Identifier > ()))});
        }

    break;

  case 51:

    {
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 52:

    {
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 53:

    {
            yylhs.value.as< Expression > () = Expression(IDENTIFIER_EXPRESSION, new IdentifierExpression(yystack_[0].value.as< Identifier > ()));
        }

    break;

  case 54:

    {
            yylhs.value.as< Expression > () = yystack_[1].value.as< Expression > ();
        }

    break;

  case 55:

    {
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 56:

    {
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 57:

    {
            yylhs.value.as< Expression > () = Expression(THIS_EXPRESSION, nullptr);
        }

    break;

  case 58:

    {
            yylhs.value.as< Expression > () = Expression();
        }

    break;

  case 59:

    {
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 60:

    {
            yylhs.value.as< Statement > () = Statement();
        }

    break;

  case 61:

    {
            yylhs.value.as< Statement > () = Statement(EXPRESSION_STATEMENT, new ExpressionStatement(yystack_[0].value.as< Expression > ()), yyget_lineno(scanner));
        }

    break;

  case 62:

    {
            yylhs.value.as< Statement > () = Statement(ASSIGNMENT_STATEMENT, new (AssignmentStatement){yystack_[2].value.as< Expression > (), yystack_[0].value.as< Expression > ()}, yyget_lineno(scanner));
        }

    break;

  case 63:

    {
            yylhs.value.as< Statement > () = yystack_[0].value.as< Statement > ();
        }

    break;

  case 64:

    {
            yylhs.value.as< Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){ADD, yystack_[2].value.as< Expression > (), yystack_[0].value.as< Expression > ()});
        }

    break;

  case 65:

    {
            yylhs.value.as< Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){SUB, yystack_[2].value.as< Expression > (), yystack_[0].value.as< Expression > ()});
        }

    break;

  case 66:

    {
            yylhs.value.as< Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){MUL, yystack_[2].value.as< Expression > (), yystack_[0].value.as< Expression > ()});
        }

    break;

  case 67:

    {
            yylhs.value.as< Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){DIV, yystack_[2].value.as< Expression > (), yystack_[0].value.as< Expression > ()});
        }

    break;

  case 68:

    {
            yylhs.value.as< Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){MOD, yystack_[2].value.as< Expression > (), yystack_[0].value.as< Expression > ()});
        }

    break;

  case 69:

    {
            yylhs.value.as< Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){EQ, yystack_[2].value.as< Expression > (), yystack_[0].value.as< Expression > ()});
        }

    break;

  case 70:

    {
            yylhs.value.as< Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){NE, yystack_[2].value.as< Expression > (), yystack_[0].value.as< Expression > ()});
        }

    break;

  case 71:

    {
            yylhs.value.as< Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){GT, yystack_[2].value.as< Expression > (), yystack_[0].value.as< Expression > ()});
        }

    break;

  case 72:

    {
            yylhs.value.as< Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){GE, yystack_[2].value.as< Expression > (), yystack_[0].value.as< Expression > ()});
        }

    break;

  case 73:

    {
            yylhs.value.as< Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){LT, yystack_[2].value.as< Expression > (), yystack_[0].value.as< Expression > ()});
        }

    break;

  case 74:

    {
            yylhs.value.as< Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){LE, yystack_[2].value.as< Expression > (), yystack_[0].value.as< Expression > ()});
        }

    break;

  case 75:

    {
            yylhs.value.as< Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){AND, yystack_[2].value.as< Expression > (), yystack_[0].value.as< Expression > ()});
        }

    break;

  case 76:

    {
            yylhs.value.as< Expression > () = Expression(BINARY_EXPRESSION, new (BinaryExpression){OR, yystack_[2].value.as< Expression > (), yystack_[0].value.as< Expression > ()});
        }

    break;

  case 77:

    {
            yylhs.value.as< Expression > () = Expression(UNARY_EXPRESSION, new (UnaryExpression){MINUS, yystack_[0].value.as< Expression > ()});
        }

    break;

  case 78:

    {
            yylhs.value.as< Expression > () = Expression(UNARY_EXPRESSION, new (UnaryExpression){NOT, yystack_[0].value.as< Expression > ()});
        }

    break;

  case 79:

    {
            yylhs.value.as< Expression > () = Expression(FUNCTION_CALL_EXPRESSION, new (FunctionCallExpression){Expression(IDENTIFIER_EXPRESSION, new IdentifierExpression(yystack_[3].value.as< Identifier > ())), yystack_[1].value.as< ExpressionsList > ()});
        }

    break;

  case 80:

    {
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 81:

    {
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 82:

    {
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 83:

    {
            yylhs.value.as< Expression > () = yystack_[0].value.as< Expression > ();
        }

    break;

  case 84:

    {
            yylhs.value.as< ExpressionsList > ().emplace_back(yystack_[0].value.as< Expression > ());
        }

    break;

  case 85:

    {
            yystack_[2].value.as< ExpressionsList > ().emplace_back(yystack_[0].value.as< Expression > ());
            yylhs.value.as< ExpressionsList > ().swap(yystack_[2].value.as< ExpressionsList > ());
        }

    break;

  case 86:

    {
            yylhs.value.as< ValueType > () = INT_TYPE;
        }

    break;

  case 87:

    {
            yylhs.value.as< ValueType > () = DOUBLE_TYPE;
        }

    break;

  case 88:

    {
            yylhs.value.as< ValueType > () = BOOL_TYPE;
        }

    break;

  case 89:

    {
            yylhs.value.as< ValueType > () = STRING_TYPE;
        }

    break;

  case 90:

    {
            yylhs.value.as< ValueType > () = ARRAY_TYPE;
        }

    break;

  case 91:

    {
            yylhs.value.as< ValueType > () = VARIANT_TYPE;
        }

    break;

  case 92:

    {
            yylhs.value.as< Statement > () = Statement(BLOCK_STATEMENT, new BlockStatement(std::move(yystack_[1].value.as< StatementsList > ())), yyget_lineno(scanner));
        }

    break;

  case 93:

    {
            yylhs.value.as< Statement > () = Statement(BLOCK_STATEMENT, new BlockStatement(), yyget_lineno(scanner));
        }

    break;

  case 94:

    {
            yylhs.value.as< ExpressionsList > ();
        }

    break;

  case 95:

    {
            yylhs.value.as< ExpressionsList > ().emplace_back(yystack_[0].value.as< Expression > ());
        }

    break;

  case 96:

    {
            yystack_[2].value.as< ExpressionsList > ().emplace_back(yystack_[0].value.as< Expression > ());
            yylhs.value.as< ExpressionsList > ().swap(yystack_[2].value.as< ExpressionsList > ());
        }

    break;

  case 97:

    {
            yylhs.value.as< Parameter > () = {yystack_[1].value.as< ValueType > (), yystack_[0].value.as< Identifier > ()};
        }

    break;

  case 98:

    {
            yylhs.value.as< Parameter > () = {yystack_[3].value.as< ValueType > (), yystack_[2].value.as< Identifier > (), yystack_[0].value.as< Expression > ()};
        }

    break;

  case 99:

    {
            yylhs.value.as< ParametersList > ();
        }

    break;

  case 100:

    {
            yylhs.value.as< ParametersList > ().emplace_back(std::move(yystack_[0].value.as< Parameter > ()));
        }

    break;

  case 101:

    {
            yystack_[2].value.as< ParametersList > ().emplace_back(std::move(yystack_[0].value.as< Parameter > ()));
            yylhs.value.as< ParametersList > ().swap(yystack_[2].value.as< ParametersList > ());
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


  const short int Parser::yypact_ninf_ = -153;

  const signed char Parser::yytable_ninf_ = -57;

  const short int
  Parser::yypact_[] =
  {
     413,   722,  -153,  -153,  -153,  -153,   -16,  -153,  -153,  -153,
    -153,    -8,  -153,    21,    11,   413,    40,    54,    36,   722,
      63,    77,   722,   221,   722,   722,   109,    94,  -153,   722,
     136,   173,  -153,  -153,  -153,  -153,   475,   -32,    97,    93,
      98,  -153,  -153,   -11,    99,   124,  -153,   -29,    -8,  -153,
     103,   722,   722,  -153,   -33,   722,   130,  -153,   130,   722,
    -153,   722,   650,    62,   501,  -153,  -153,   771,  -153,   269,
     921,    56,  -153,   114,  -153,   101,   543,  -153,  -153,  -153,
     722,   722,   722,   722,   722,   722,   722,   722,   722,   722,
     722,   722,   722,  -153,   722,   722,   722,   132,   722,   -31,
      19,   722,   921,    -6,   569,  -153,   130,   784,    60,    90,
     821,   834,   -13,  -153,   488,   111,   130,   413,   135,  -153,
     119,  -153,  -153,   722,   147,  -153,    14,  -153,    61,    61,
     151,   151,   151,   151,   151,   151,   105,   105,  -153,  -153,
    -153,   556,   610,   623,   114,  -153,   636,   101,  -153,   921,
    -153,   722,  -153,  -153,  -153,  -153,  -153,   413,   413,    91,
     722,   722,   317,   129,   921,   125,   134,   101,  -153,  -153,
    -153,  -153,    17,   921,  -153,  -153,   722,   871,   921,   921,
     126,  -153,   413,    96,  -153,  -153,   134,   884,   134,   686,
     365,  -153,  -153,   134,  -153,   133,  -153,  -153,   413,  -153
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,    80,    82,    81,    83,    37,    86,    87,    88,
      89,    90,    91,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    57,     0,
       0,     0,     3,    20,    19,    21,     0,    40,    39,    41,
       0,    33,    34,    36,    35,     0,    17,    37,     0,    77,
      27,    94,     0,    29,     0,     0,     0,    90,     0,     0,
       7,     0,    60,     0,     0,    14,    13,     0,    93,     0,
      84,     0,    78,     0,    42,    99,     0,     1,     2,     4,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     0,     0,     0,     0,     0,    27,
       0,     0,    95,     0,     0,    25,     0,     0,     0,     0,
       0,     0,    37,    63,    61,     0,     0,     0,     0,    12,
      38,    92,    48,     0,     0,   100,     0,    18,    75,    76,
      69,    70,    71,    72,    73,    74,    64,    65,    66,    67,
      68,     0,     0,     0,    50,    49,     0,    99,    23,    28,
      79,     0,    44,    30,    43,    26,    24,     0,     0,     0,
       0,    58,     0,     0,    85,    97,     0,     0,    22,    47,
      45,    46,     0,    96,     6,     8,     0,     0,    62,    59,
       0,    31,     0,     0,    16,   101,     0,     0,     0,    60,
       0,    98,    15,     0,    10,     0,    32,    11,     0,     9
  };

  const short int
  Parser::yypgoto_[] =
  {
    -153,  -153,   -21,   -14,  -153,   -58,    71,   -18,  -153,    -1,
    -153,  -153,  -153,  -153,  -153,    -9,  -153,  -153,   -20,    -5,
    -153,   -10,  -152,  -153,    15,    34
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,    30,    31,    32,    33,    34,    53,    54,    35,    36,
      37,    38,    39,    40,   180,   115,    41,    42,    43,    44,
      71,    45,    46,   103,   125,   126
  };

  const short int
  Parser::yytable_[] =
  {
      49,    60,    69,    58,   113,    50,    74,   147,    50,    51,
      95,   105,   106,    52,   184,   101,   -55,    79,    64,   -53,
     159,    67,    51,    70,    72,    51,    52,   100,    76,    52,
      55,    98,   -53,   150,   192,   -53,   194,   -52,   108,   151,
     109,   197,    56,     7,     8,     9,    10,    57,    12,    59,
     102,   104,   116,   166,   107,    79,   186,    63,   110,   167,
     111,   114,   167,   148,   106,   124,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,   145,    61,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,    62,   141,   142,   143,   162,   146,   100,   122,
     149,   123,   117,     1,   155,   106,   118,    65,     2,     3,
       4,     5,    47,     2,     3,     4,     5,    48,    90,    91,
      92,    66,   164,     7,     8,     9,    10,    57,    12,    22,
      73,   113,    75,    24,   156,   106,    77,   124,    25,    96,
      26,   -56,    28,   174,   175,    99,    97,   -51,    79,   101,
     173,    50,    51,   144,   176,   161,   163,   124,   177,   178,
     179,   190,    88,    89,    90,    91,    92,   -54,   165,   182,
     189,   183,   198,    78,    23,   187,    79,   153,   191,   116,
     195,   172,   185,     0,   199,     1,     0,     0,   114,     0,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,     0,    18,    19,    20,
      21,    22,     0,    23,     0,    24,     0,     0,     0,     0,
      25,     0,    26,    27,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     0,     0,     0,    29,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,     0,    18,    19,    20,    21,    22,
       0,    23,    68,    24,     0,     0,     0,     0,    25,     0,
      26,    27,    28,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     0,     0,     0,    29,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,     0,    18,    19,    20,    21,    22,     0,    23,
     121,    24,     0,     0,     0,     0,    25,     0,    26,    27,
      28,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       0,     0,     0,    29,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       0,    18,    19,    20,    21,    22,     0,    23,   181,    24,
       0,     0,     0,     0,    25,     0,    26,    27,    28,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     0,     0,
       0,    29,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     0,    18,
      19,    20,    21,    22,     0,    23,   196,    24,     0,     0,
       0,     0,    25,     0,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     0,     0,     0,    29,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,     0,    18,    19,    20,
      21,    22,     0,    23,     0,    24,     0,     0,     0,     0,
      25,     0,    26,    27,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,     0,     0,    93,
       0,    94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   160,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   119,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,     0,     0,   127,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     168,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   152,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,     0,   169,     0,     0,     0,     0,     0,     0,
       0,     0,     1,     0,     0,     0,   170,     2,     3,     4,
       5,   112,     7,     8,     9,    10,    11,    12,    13,   171,
       0,     0,     0,     0,     0,     0,     0,     0,    22,     0,
       0,     0,    24,     0,     0,     0,     0,    25,     1,    26,
       0,    28,     0,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    22,     0,     0,     0,    24,     0,
       0,     0,     0,    25,     1,    26,     0,    28,     0,     2,
       3,     4,     5,    47,     0,     0,     0,     0,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      22,     0,     0,     0,    24,     0,     0,     0,     0,    25,
       0,    26,     0,    28,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   154,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     157,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   158,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     188,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   193,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92
  };

  const short int
  Parser::yycheck_[] =
  {
       1,    15,    23,    13,    62,    21,    26,    38,    21,    38,
      42,    44,    45,    42,   166,    46,    48,    31,    19,    48,
      33,    22,    38,    24,    25,    38,    42,    45,    29,    42,
      38,    42,    48,    39,   186,    48,   188,    48,    56,    45,
      58,   193,    21,    22,    23,    24,    25,    26,    27,    38,
      51,    52,    62,    39,    55,    69,    39,    21,    59,    45,
      61,    62,    45,    44,    45,    75,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    97,    38,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    38,    94,    95,    96,   117,    98,   116,    43,
     101,    45,    40,    12,    44,    45,    44,    44,    17,    18,
      19,    20,    21,    17,    18,    19,    20,    26,    13,    14,
      15,    44,   123,    22,    23,    24,    25,    26,    27,    38,
      21,   189,    38,    42,    44,    45,     0,   147,    47,    42,
      49,    48,    51,   157,   158,    21,    48,    48,   162,    46,
     151,    21,    38,    21,    63,    44,    21,   167,   159,   160,
     161,   182,    11,    12,    13,    14,    15,    48,    21,    40,
      44,    46,    39,     0,    40,   176,   190,   106,   183,   189,
     189,   147,   167,    -1,   198,    12,    -1,    -1,   189,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    -1,    40,    -1,    42,    -1,    -1,    -1,    -1,
      47,    -1,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    64,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    37,    38,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    47,    -1,
      49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    12,    -1,    -1,    -1,    64,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    47,    -1,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    64,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    47,    -1,    49,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,
      -1,    64,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    47,    -1,    49,    50,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    64,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    -1,    40,    -1,    42,    -1,    -1,    -1,    -1,
      47,    -1,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    44,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    43,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    -1,    42,    -1,    -1,    -1,    -1,    47,    12,    49,
      -1,    51,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,    42,    -1,
      -1,    -1,    -1,    47,    12,    49,    -1,    51,    -1,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,    47,
      -1,    49,    -1,    51,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    12,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    34,    35,
      36,    37,    38,    40,    42,    47,    49,    50,    51,    64,
      66,    67,    68,    69,    70,    73,    74,    75,    76,    77,
      78,    81,    82,    83,    84,    86,    87,    21,    26,    74,
      21,    38,    42,    71,    72,    38,    21,    26,    86,    38,
      68,    38,    38,    21,    74,    44,    44,    74,    41,    67,
      74,    85,    74,    21,    83,    38,    74,     0,     0,    68,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    44,    46,    42,    42,    48,    42,    21,
      72,    46,    74,    88,    74,    44,    45,    74,    72,    72,
      74,    74,    21,    70,    74,    80,    86,    40,    44,    44,
      39,    41,    43,    45,    86,    89,    90,    44,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    21,    83,    74,    38,    44,    74,
      39,    45,    43,    71,    39,    44,    44,    39,    39,    33,
      46,    44,    67,    21,    74,    21,    39,    45,    44,    43,
      43,    43,    90,    74,    68,    68,    63,    74,    74,    74,
      79,    41,    40,    46,    87,    89,    39,    74,    39,    44,
      67,    84,    87,    39,    87,    80,    41,    87,    39,    68
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    65,    66,    67,    67,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    69,    70,    70,    70,    70,    71,    71,    72,
      72,    73,    73,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    75,    75,    75,    75,    76,    77,
      77,    78,    78,    78,    78,    78,    78,    78,    79,    79,
      80,    80,    80,    80,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    82,    82,    83,
      84,    84,    84,    84,    85,    85,    86,    86,    86,    86,
      86,    86,    87,    87,    88,    88,    88,    89,    89,    90,
      90,    90
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     2,     2,     5,     2,     5,     9,
       7,     8,     3,     2,     2,     6,     5,     1,     3,     1,
       1,     1,     4,     3,     4,     3,     4,     1,     3,     1,
       3,     5,     7,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     2,     4,     4,     4,     4,     4,     3,     3,
       3,     1,     1,     1,     3,     1,     1,     1,     0,     1,
       0,     1,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     4,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     2,     0,     1,     3,     2,     4,     0,
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
  "COMMA", "ASSIGN", "EXCLAMATION", "DOT", "NEW", "CONSTRUCTOR", "THIS",
  "PUBLIC", "PROTECTED", "PRIVATE", "SUPER", "ADD_ASSIGN", "SUB_ASSIGN",
  "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "INCREMENT", "DECREMENT",
  "REVERSE", "PRINT", "$accept", "eof", "statements_list", "statement",
  "assignment_statement", "declaration_statement", "declaration_item",
  "declaration_items_list", "class_definition", "expression",
  "index_expression", "array_expression", "dot_expression",
  "dot_pre_expression", "expression_optional", "statement_optional",
  "binary_expression", "unary_expression", "function_call_expression",
  "primary_expression", "expressions_list", "type_tag", "block",
  "arguments_list", "parameter", "parameters_list", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,    59,    59,    64,    68,    74,    78,    83,    88,    94,
      98,   102,   106,   110,   114,   118,   171,   209,   213,   217,
     221,   225,   227,   232,   236,   240,   244,   249,   253,   258,
     262,   268,   285,   306,   310,   314,   318,   322,   326,   330,
     334,   338,   342,   347,   352,   356,   360,   364,   369,   374,
     378,   383,   387,   391,   395,   399,   403,   407,   413,   416,
     422,   425,   429,   433,   438,   442,   446,   450,   454,   458,
     462,   466,   470,   474,   478,   482,   486,   491,   495,   500,
     505,   509,   513,   517,   522,   526,   532,   536,   540,   544,
     548,   552,   557,   561,   567,   570,   574,   580,   584,   590,
     593,   597
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
