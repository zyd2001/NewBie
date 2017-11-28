%skeleton "lalr1.cc"
%require "3.0.4"
%defines "NewBie_Parser.hpp"
%define parser_class_name {Parser}

%code requires
{
#include "NewBie_Lang.hpp"
#include "NewBie.hpp"
}

%code
{
    using namespace std;
    using namespace zyd2001::NewBie;
}

%define api.namespace {zyd2001::NewBie}
%define api.value.type variant
%define api.token.constructor
%define api.token.prefix {TOKEN_}
%define parse.trace
%define parse.error verbose
%printer { yyoutput << $$ << " " << yylino << endl; } <*>;
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
%type<zyd2001::NewBie::Parameter> parameters_list_item
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
            $$ = Statement(EXPRESSION_STATEMENT, new Expression(std::move($1)));
        }
        | IF LP expression RP statement
        {
            $$ = nb_create_if_statement($3, $5);
        }
        | ELSE statement
        {
            $$ = nb_cat_else_statement($2);
        }
        | ELSEIF LP expression RP statement
        {
            $$ = nb_cat_elseif_statement($3, $5);
        }
        | FOR LP IDENTIFIER IN possible_array_expression RP statement
        {
            $$ = nb_create_foreach_statement($3, $5, $7, 0);
        }
        | FOR LP IDENTIFIER IN REVERSE possible_array_expression RP statement
        {
            $$ = nb_create_foreach_statement($3, $6, $8, 1);
        }
        | FOR LP expression_optional SEMICOLON expression_optional SEMICOLON expression_optional RP statement
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
        | block
        | function_definition_statement
        ;
    expression: binary_expression
        | unary_expression
        | primary_expression
        | index_expression
        | IDENTIFIER
        {
            $$ = Expression(IDENTIFIER_EXPRESSION, new IdentifierExpression($1));
        }
        | LP expression RP
        {
            $$ = std::move($2);
        }
        ;
    expression_optional: /* empty */
        {
            $$ = Expression();
        }
        | expression
        ;
    binary_expression: expression ADD expression
        {
            $$ = Expression(BINARY_EXPRESSION, new BinaryExpression({ADD, $1, $3}));
        }
        | expression SUB expression
        {
            $$ = Expression(BINARY_EXPRESSION, new BinaryExpression({SUB, $1, $3}));         
        }
        | expression MUL expression
        {
            $$ = Expression(BINARY_EXPRESSION, new BinaryExpression({MUL, $1, $3}));
        }
        | expression DIV expression
        {
            $$ = Expression(BINARY_EXPRESSION, new BinaryExpression({DIV, $1, $3}));
        }
        | expression MOD expression
        {
            $$ = Expression(BINARY_EXPRESSION, new BinaryExpression({MOD, $1, $3}));
        }
        | expression EQ expression
        {
            $$ = Expression(BINARY_EXPRESSION, new BinaryExpression({EQ, $1, $3}));
        }
        | expression NE expression
        {
            $$ = Expression(BINARY_EXPRESSION, new BinaryExpression({NE, $1, $3}));
        }
        | expression GT expression
        {
            $$ = Expression(BINARY_EXPRESSION, new BinaryExpression({GT, $1, $3}));
        }
        | expression GE expression
        {
            $$ = Expression(BINARY_EXPRESSION, new BinaryExpression({GE, $1, $3}));
        }
        | expression LT expression
        {
            $$ = Expression(BINARY_EXPRESSION, new BinaryExpression({LT, $1, $3}));
        }
        | expression LE expression
        {
            $$ = Expression(BINARY_EXPRESSION, new BinaryExpression({LE, $1, $3}));
        }
        | expression LOGICAL_AND expression
        {
            $$ = Expression(BINARY_EXPRESSION, new BinaryExpression({AND, $1, $3}));
        }
        | expression LOGICAL_OR expression
        {
            $$ = Expression(BINARY_EXPRESSION, new BinaryExpression({OR, $1, $3}));
        }
        ;
    unary_expression: SUB expression %prec UMINUS
        {
            $$ = Expression(UNARY_EXPRESSION, new UnaryExpression({MINUS, $2}));
        }
        | EXCLAMATION expression %prec UMINUS
        {
            $$ = Expression(UNARY_EXPRESSION, new UnaryExpression({NOT, $2}));
        }
        ;
    function_call_expression: IDENTIFIER LP arguments_list RP
        {
            $$ = Expression(FUNCTION_CALL_EXPRESSION, new FunctionCallExpression({$1, $3}));
        }
        ;
    primary_expression: INT_LITERAL
        | DOUBLE_LITERAL
        | STRING_LITERAL
        | BOOL_LITERAL
        ;
    expressions_list: expression
        {
            $$.push_back($1);
        }
        | expressions_list COMMA expression
        {
            $1.push_back($3);
            $$.swap($1);
        }
        ;
    function_definition_statement: type_tag IDENTIFIER LP parameters_list RP block
        {
            $$ = nb_create_function_definition_statement($1, $2, $4, $6);
        }
        ;
    type_tag: INT
        {
            $$ = INT_TYPE;
        }
        | DOUBLE
        {
            $$ = DOUBLE_TYPE;
        }
        | BOOL
        {
            $$ = BOOL_TYPE;
        }
        | STRING
        {
            $$ = STRING_TYPE;
        }
        | ARRAY
        {
            $$ = ARRAY_TYPE;
        }
        | VAR
        {
            $$ = VARIOUS_TYPE;
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
            $$;
        }
        | expression
        {
            $$.push_back($1);
        }
        | arguments_list COMMA expression
        {
            $1.push_back($3);
            $$.swap($1);
        }
        ;
    parameter_list_item: type_tag IDENTIFIER primary_expression
        {
            $$ = {$1, $2, $3};
        }
        ;
    parameters_list: /* empty */
        {
            $$;
        }
        | parameter_list_item
        {
            $$.push_back($1);
        }
        | parameters_list COMMA parameter_list_item
        {
            $1.push_back($1);
            $$.swap($1);
        }
        ;
%%