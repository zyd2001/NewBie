%{
#include <stdio.h>
#include "newbie.h"
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
%token <expression>     INT_LITERAL
%token <expression>     DOUBLE_LITERAL
%token <expression>     STRING_LITERAL
%token <identifier>     IDENTIFIER
%token INT_T DOUBLE_T STRING_T ARRAY_T ARRAY_ASSOC_T IF ELSE ELSEIF FOR CLASS RETURN BREAK CONTINUE
        LP RP LC RC LB RB SEMICOLON COMMA ASSIGN_T LOGICAL_AND LOGICAL_OR
        EQ NE GT GE LT LE ADD SUB MUL DIV MOD EXCLAMATION DOT
        ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
        INCREMENT DECREMENT comparison_expression
%%
    statement: expression SEMICOLON
        | IF LP argument_list RP block
        ;
    expression: assignment_expression
        | declaration_expression
        | comparison_expression
        | primary_expression
        ;
    declaration_expression: declaration_tag IDENTIFIER 
        {
            
        }
        | declaration_tag assignment_expression 
        {

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
    declaration_tag: INT_T | DOUBLE_T | STRING_T | ARRAY_ASSOC_T | ARRAY_T ;
    block: statement_list;
    statement_list: statement
        | statement_list statement
        ;
%%