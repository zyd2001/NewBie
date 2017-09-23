%{
#include <stdio.h>
#include "newbie.h"

ComparisonType comparison_type;
NBValueType value_type;
%}
%union {
    char                *identifier;
    ParameterList       *parameter_list;
    ArgumentList        *argument_list;
    Expression          *expression;
    Statement           *statement;
    StatementList       *statement_list;
    Block               *block;
    Elseif              *elseif;
    IdentifierList      *identifier_list;
}
%expect 42
%token <expression>     INT_LITERAL STRING_LITERAL DOUBLE_LITERAL
%token <identifier>     IDENTIFIER
%token INT_T DOUBLE_T STRING_T ARRAY_T IF ELSE ELSEIF FOR IN CLASS RETURN BREAK CONTINUE
        LP RP LC RC LB RB SEMICOLON COMMA ASSIGN_T LOGICAL_AND LOGICAL_OR
        EQ NE GT GE LT LE ADD SUB MUL DIV MOD EXCLAMATION DOT
        ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
        INCREMENT DECREMENT
%type<expression> expression comparison_expression declaration_expression primary_expression assignment_expression
%%
    statement: expression SEMICOLON
        | function_definition_statement
        | IF LP expression RP block
        | FOR LP IDENTIFIER IN expression RP block
        | FOR LP expression_optional SEMICOLON expression_optional SEMICOLON expression_optional RP block
        | RETURN expression SEMICOLON
        | CONTINUE SEMICOLON
        | BREAK SEMICOLON
        ;
    expression: assignment_expression
        | declaration_expression
        | comparison_expression
        | primary_expression
        | IDENTIFIER LP actual_argument_list RP
        | IDENTIFIER
        {
            $$ = nb_create_identifier_expression($1);
        }
        ;
    comparison_expression: expression EQ expression
        {
            comparison_type = EQ;
            $$ = nb_create_comparison_expression(comparison_type, $1, $3);
        }
        | expression NE expression
        {
            comparison_type = NE;
            $$ = nb_create_comparison_expression(comparison_type, $1, $3);
        }
        | expression GT expression
        {
            comparison_type = GT;
            $$ = nb_create_comparison_expression(comparison_type, $1, $3);
        }
        | expression GE expression
        {
            comparison_type = GE;
            $$ = nb_create_comparison_expression(comparison_type, $1, $3);
        }
        | expression LT expression
        {
            comparison_type = LT;
            $$ = nb_create_comparison_expression(comparison_type, $1, $3);
        }
        | expression LE expression
        {
            comparison_type = LE;
            $$ = nb_create_comparison_expression(comparison_type, $1, $3);
        }
        ;
    declaration_expression: INT_T IDENTIFIER 
        {
            value_type = INT;
            $$ = nb_create_declaration_expression(value_type, $2, NULL);
        }
        | DOUBLE_T IDENTIFIER
        {
            value_type = DOUBLE;
            $$ = nb_create_declaration_expression(value_type, $2, NULL);
        }
        | STRING_T IDENTIFIER
        {
            value_type = STRING;
            $$ = nb_create_declaration_expression(value_type, $2, NULL);
        }
        | ARRAY_T IDENTIFIER
        {
            value_type = ARRAY;
            $$ = nb_create_declaration_expression(value_type, $2, NULL);
        }
        | INT_T assignment_expression 
        {
            value_type = INT;
            $$ = nb_create_declaration_expression(value_type, NULL, $2);
        }
        | DOUBLE_T assignment_expression 
        {
            value_type = DOUBLE;
            $$ = nb_create_declaration_expression(value_type, NULL, $2);
        }
        | STRING_T assignment_expression 
        {
            value_type = STRING;
            $$ = nb_create_declaration_expression(value_type, NULL, $2);
        }
        | ARRAY_T assignment_expression 
        {
            value_type = ARRAY;
            $$ = nb_create_declaration_expression(value_type, NULL, $2);
        }
        ;
    assignment_expression: IDENTIFIER ASSIGN_T expression
        {
            $$ = nb_create_assignment_expression($1, $3);
        }
        ;
    primary_expression: INT_LITERAL
        | DOUBLE_LITERAL
        | STRING_LITERAL
        ;
    expression_optional: /* empty */
        | expression
        ;
    function_definition_statement: INT_T LP formal_argument_list RP block;
        | DOUBLE_T LP formal_argument_list RP block;
        | STRING_T LP formal_argument_list RP block;
        | ARRAY_T LP formal_argument_list RP block;
    block: LC statement_list RC
        | LC RC
        ;
    statement_list: statement
        | statement_list statement
        ;
    actual_argument_list: expression
        | actual_argument_list COMMA expression
        ;
    formal_argument_list: /* empty */
        | INT_T IDENTIFIER
        | DOUBLE_T IDENTIFIER
        | STRING_T IDENTIFIER
        | ARRAY_T IDENTIFIER
        | formal_argument_list COMMA INT_T IDENTIFIER
        | formal_argument_list COMMA DOUBLE_T IDENTIFIER
        | formal_argument_list COMMA STRING_T IDENTIFIER
        | formal_argument_list COMMA ARRAY_T IDENTIFIER
        ;
%%