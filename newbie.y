%{
#include <stdio.h>
#include "newbie.h"

ComparisonType comparison_type;
NBValueType NB_value_type;
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
%token INT_T DOUBLE_T STRING_T ARRAY_T ARRAY_ASSOC_T IF ELSE ELSEIF FOR CLASS RETURN BREAK CONTINUE
        LP RP LC RC LB RB SEMICOLON COMMA ASSIGN_T LOGICAL_AND LOGICAL_OR
        EQ NE GT GE LT LE ADD SUB MUL DIV MOD EXCLAMATION DOT
        ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
        INCREMENT DECREMENT
%type<expression> expression comparison_expression declaration_expression primary_expression
                assignment_expression
%%
    statement: expression SEMICOLON
        | IF LP argument_list RP block
        ;
    expression: assignment_expression
        | declaration_expression
        | comparison_expression
        | primary_expression
        | IDENTIFIER
        {
            $$ = create_identifier_expression($1);
        }
        ;
    comparison_expression: expression EQ expression
        {
            comparison_type = EQ;
            $$ = create_comparison_expression(comparison_type, $1, $3);
        }
        | expression NE expression
        {
            comparison_type = NE;
            $$ = create_comparison_expression(comparison_type, $1, $3);
        }
        | expression GT expression
        {
            comparison_type = GT;
            $$ = create_comparison_expression(comparison_type, $1, $3);
        }
        | expression GE expression
        {
            comparison_type = GE;
            $$ = create_comparison_expression(comparison_type, $1, $3);
        }
        | expression LT expression
        {
            comparison_type = LT;
            $$ = create_comparison_expression(comparison_type, $1, $3);
        }
        | expression LE expression
        {
            comparison_type = LE;
            $$ = create_comparison_expression(comparison_type, $1, $3);
        }
        ;
    declaration_expression: INT_T IDENTIFIER 
        {
            NB_value_type = INT;
            $$ = create_declaration_expression(NB_value_type, $2, NULL);
        }
        | DOUBLE_T IDENTIFIER
        {
            NB_value_type = DOUBLE;
            $$ = create_declaration_expression(NB_value_type, $2, NULL);
        }
        | STRING_T IDENTIFIER
        {
            NB_value_type = STRING;
            $$ = create_declaration_expression(NB_value_type, $2, NULL);
        }
        | ARRAY_T IDENTIFIER
        {
            NB_value_type = ARRAY;
            $$ = create_declaration_expression(NB_value_type, $2, NULL);
        }
        | ARRAY_ASSOC_T IDENTIFIER
        {
            NB_value_type = ARRAY_ASSOC;
            $$ = create_declaration_expression(NB_value_type, $2, NULL);
        }
        | INT_T assignment_expression 
        {
            NB_value_type = INT;
            $$ = create_declaration_expression(NB_value_type, NULL, $2);
        }
        ;
    assignment_expression: IDENTIFIER ASSIGN_T expression
        {
            $$ = create_assignment_expression($1, $3);
        }
        ;
    primary_expression: INT_LITERAL
        | DOUBLE_LITERAL
        | STRING_LITERAL
        ;
    block: LC statement_list RC
        | LC RC
        ;
    statement_list: statement
        | statement_list statement
        ;
    argument_list: IDENTIFIER
        | argument_list COMMA IDENTIFIER
        ;
%%