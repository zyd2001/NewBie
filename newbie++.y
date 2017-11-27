%skeleton "lalr1.cc"
%require "3.0.4"
%defines "NewBie_Parser.hpp"
%define parser_class_name {Parser}

%code requires{

#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

}

%define api.namespace {zyd2001::NewBie}
%define api.value.type variant
%define api.token.constructor
%define api.token.prefix {TOKEN_}
%define parse.trace
%define parse.error verbose
%printer { yyoutput << $$; } <*>;
%param {zyd2001::NewBie::Interpreter::InterpreterImp &inter}
%locations
%initial-action
{
    @$.begin.filename = @$.end.filename = &inter.filename;
}

%left LOGICAL_AND LOGICAL_OR
%left EQ NE GT GE LT LE
%left ADD SUB
%left MUL DIV MOD
%nonassoc UMINUS
%token <zyd2001::NewBie::Expression> INT_LITERAL STRING_LITERAL DOUBLE_LITERAL BOOL_LITERAL
%token <std::string>     IDENTIFIER
%token INT DOUBLE BOOL STRING ARRAY VAR IF ELSE ELSEIF FOR IN CLASS RETURN BREAK CONTINUE
        LP RP LC RC LB RB SEMICOLON COMMA ASSIGN EXCLAMATION DOT
        ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
        INCREMENT DECREMENT PUBLIC PROTECTED PRIVATE REVERSE
%type<zyd2001::NewBie::Expression> expression function_call_expression primary_expression expression_optional binary_expression unary_expression possible_array_expression
                    index_expression parameter_list_item
%type<zyd2001::NewBie::Statement> statement block function_definition_statement
%type<zyd2001::NewBie::StatementsList> statements_list
%type<zyd2001::NewBie::ArgumentsList> arguments_list
%type<zyd2001::NewBie::ParametersList> parameters_list
%type<zyd2001::NewBie::ExpressionsList> expressions_list
%type<zyd2001::NewBie::ValueType> type_tag
%%
    statements_list: statement
        {
            $$ = nb_create_statement_list($1);
        }
        | statements_list statement
        {
            $$ = nb_cat_statement_list($1, $2);
        }
        ;
    statement: expression SEMICOLON
        {
            $$ = nb_create_expression_statement($1);
        }
        | IF LP expression RP block
        {
            $$ = nb_create_if_statement($3, $5);
        }
        | ELSE block
        {
            $$ = nb_cat_else_statement($2);
        }
        | ELSEIF LP expression RP block
        {
            $$ = nb_cat_elseif_statement($3, $5);
        }
        | FOR LP IDENTIFIER IN possible_array_expression RP block
        {
            $$ = nb_create_foreach_statement($3, $5, $7, 0);
        }
        | FOR LP IDENTIFIER IN REVERSE possible_array_expression RP block
        {
            $$ = nb_create_foreach_statement($3, $6, $8, 1);
        }
        | FOR LP expression_optional SEMICOLON expression_optional SEMICOLON expression_optional RP block
        {
            $$ = nb_create_for_statement($3, $5, $7, $9);
        }
        | RETURN expression SEMICOLON
        {
            $$ = nb_create_return_statement($2);
        }
        | CONTINUE SEMICOLON
        {
            $$ = nb_create_continue_statement();
        }
        | BREAK SEMICOLON
        {
            $$ = nb_create_break_statement();
        }
        | CLASS IDENTIFIER block
        {
            $$ = nb_create_class_definition_statement($2, $3);
        }
        | block
        | function_definition_statement
        ;
    expression: binary_expression
        | unary_expression
        | primary_expression
        | index_expression
        | possible_array_expression
        | type_tag LP parameters_list RP block
        {
            $$ = nb_create_anonymous_function_definition_expression($1, $3, $5);
        }
        ;
        | LP expression RP
        {
            $$ = $2;
        }
        ;
    possible_array_expression: IDENTIFIER
        {
            $$ = nb_create_identifier_expression($1);
        }
        | function_call_expression
        | LB expressions_list RB
        {
            $$ = nb_create_array_expression($2);
        }
        ;
    index_expression: possible_array_expression LB expression RB
        {
            $$ = nb_create_index_expression($1, $3);
        }
        | index_expression LB expression RB
        {
            $$ = nb_create_index_expression($1, $3);            
        }
        ;
    expression_optional: /* empty */
        {
            $$ = NULL;
        }
        | expression
        ;
    binary_expression: expression ADD expression
        {
            $$ = nb_create_binary_expression(ADD, $1, $3);
        }
        | expression SUB expression
        {
            $$ = nb_create_binary_expression(SUB, $1, $3);            
        }
        | expression MUL expression
        {
            $$ = nb_create_binary_expression(MUL, $1, $3);            
        }
        | expression DIV expression
        {
            $$ = nb_create_binary_expression(DIV, $1, $3);            
        }
        | expression MOD expression
        {
            $$ = nb_create_binary_expression(MOD, $1, $3);            
        }
        | expression EQ expression
        {
            $$ = nb_create_binary_expression(EQ, $1, $3);
        }
        | expression NE expression
        {
            $$ = nb_create_binary_expression(NE, $1, $3);
        }
        | expression GT expression
        {
            $$ = nb_create_binary_expression(GT, $1, $3);
        }
        | expression GE expression
        {
            $$ = nb_create_binary_expression(GE, $1, $3);
        }
        | expression LT expression
        {
            $$ = nb_create_binary_expression(LT, $1, $3);
        }
        | expression LE expression
        {
            $$ = nb_create_binary_expression(LE, $1, $3);
        }
        | expression LOGICAL_AND expression
        {
            $$ = nb_create_binary_expression(AND, $1, $3);
        }
        | expression LOGICAL_OR expression
        {
            $$ = nb_create_binary_expression(OR, $1, $3);
        }
        ;
    unary_expression: SUB expression %prec UMINUS
        {
            $$ = nb_create_unary_expression(MINUS, $2);
        }
        | EXCLAMATION expression %prec UMINUS
        {
            $$ = nb_create_unary_expression(NOT, $2);
        }
        ;
    function_call_expression: IDENTIFIER LP arguments_list RP
        {
            $$ = nb_create_function_call_expression($1, $3);
        }
        ;
    primary_expression: INT_LITERAL
        | DOUBLE_LITERAL
        | STRING_LITERAL
        | BOOL_LITERAL
        ;
    expressions_list: expression
        {
            $$ = nb_create_expression_list($1);
        }
        | expressions_list COMMA expression
        {
            $$ = nb_cat_expression_list($1, $3);
        }
        ;
    function_definition_statement: type_tag IDENTIFIER LP parameters_list RP block
        {
            $$ = nb_create_function_definition_statement($1, $2, $4, $6);
        }
        ;
    type_tag: INT
        {
            $$ = INT;
        }
        | DOUBLE
        {
            $$ = DOUBLE;
        }
        | BOOL
        {
            $$ = BOOL;
        }
        | STRING
        {
            $$ = STRING;
        }
        | ARRAY
        {
            $$ = ARRAY;
        }
        | VAR
        {
            $$ = VARIOUS;
        }
        ;
    block: LC statements_list RC
        {
            $$ = nb_create_block_statement($2);
        }
        | LC RC
        {
            $$ = nb_create_block_statement(NULL);
        }
        ;
    arguments_list: /* empty */
        {
            $$ = NULL;
        }
        | expression
        {
            $$ = nb_create_argument_list($1);
        }
        | arguments_list COMMA expression
        {
            $$ = nb_cat_argument_list($1, $3);
        }
        ;
    parameter_list_item: INT_LITERAL;
    parameters_list: /* empty */
        {
            $$ = NULL;
        }
        | parameter_list_item
        {
            $$ = nb_create_parameter_list($1);
        }
        | parameters_list COMMA parameter_list_item
        {
            $$ = nb_cat_parameter_list($1, $3);
        }
        ;
%%