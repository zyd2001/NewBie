%{
// #include <stdio.h>
#include "newbie.h"

extern int yylex(void);
extern StatementList *slist;
void yyerror (char const *s)
{
    fprintf (stderr, "%s\n", s);
}


%}
%union {
    UTF8_String         *identifier;
    Expression          *expression;
    Statement           *statement;
    StatementList       *statement_list;
}
%expect 132
%token <expression>     INT_LITERAL STRING_LITERAL DOUBLE_LITERAL
%token <identifier>     IDENTIFIER
%token INT_T DOUBLE_T STRING_T ARRAY_T IF ELSE ELSEIF FOR IN CLASS RETURN_T BREAK CONTINUE
        LP RP LC RC LB RB SEMICOLON COMMA ASSIGN_T LOGICAL_AND LOGICAL_OR
        EQ_T NE_T GT_T GE_T LT_T LE_T ADD_T SUB_T MUL_T DIV_T MOD_T EXCLAMATION DOT
        ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
        INCREMENT DECREMENT
%type<expression> expression comparison_expression declaration_expression primary_expression assignment_expression computation_expression
%type<statement> statement
%%
    statement_list: statement
        {
            slist = (StatementList*)malloc(sizeof(StatementList));
            slist->s = $1;
            slist->prev = NULL;
        }
        | statement_list statement
        {
            slist->next = (StatementList*)malloc(sizeof(StatementList));
            slist->next->prev = slist;
            slist = slist->next;
            slist->s = $2;
        }
        ;
    statement: expression SEMICOLON
        {
            $$ = nb_create_expression_statement($1);
        }
        | function_definition_statement
        | IF LP expression RP block
        | FOR LP IDENTIFIER IN expression RP block
        | FOR LP expression_optional SEMICOLON expression_optional SEMICOLON expression_optional RP block
        | RETURN_T expression SEMICOLON
        | CONTINUE SEMICOLON
        | BREAK SEMICOLON
        ;
    expression: assignment_expression
        | declaration_expression
        | binary_expression
        | primary_expression
        | IDENTIFIER LP actual_argument_list RP
        | IDENTIFIER
        {
            $$ = nb_create_identifier_expression($1);
        }
        ;
    expression_optional: /* empty */
        | expression
        ;
    binary_expression: comparison_expression
        | computation_expression
        ;
    comparison_expression: expression EQ_T expression
        {
            $$ = nb_create_binary_expression(EQ, $1, $3);
        }
        | expression NE_T expression
        {
            $$ = nb_create_binary_expression(NE, $1, $3);
        }
        | expression GT_T expression
        {
            $$ = nb_create_binary_expression(GT, $1, $3);
        }
        | expression GE_T expression
        {
            $$ = nb_create_binary_expression(GE, $1, $3);
        }
        | expression LT_T expression
        {
            $$ = nb_create_binary_expression(LT, $1, $3);
        }
        | expression LE_T expression
        {
            $$ = nb_create_binary_expression(LE, $1, $3);
        }
        ;
    declaration_expression: INT_T IDENTIFIER 
        {
            $$ = nb_create_declaration_expression(INT, $2, NULL);
        }
        | DOUBLE_T IDENTIFIER
        {
            $$ = nb_create_declaration_expression(DOUBLE, $2, NULL);
        }
        | STRING_T IDENTIFIER
        {
            $$ = nb_create_declaration_expression(STRING, $2, NULL);
        }
        | ARRAY_T IDENTIFIER
        {
            $$ = nb_create_declaration_expression(ARRAY, $2, NULL);
        }
        | INT_T assignment_expression 
        {
            $$ = nb_create_declaration_expression(INT, NULL, $2);
        }
        | DOUBLE_T assignment_expression 
        {
            $$ = nb_create_declaration_expression(DOUBLE, NULL, $2);
        }
        | STRING_T assignment_expression 
        {
            $$ = nb_create_declaration_expression(STRING, NULL, $2);
        }
        | ARRAY_T assignment_expression 
        {
            $$ = nb_create_declaration_expression(ARRAY, NULL, $2);
        }
        ;
    computation_expression: expression ADD_T expression
        {
            $$ = nb_create_binary_expression(ADD, $1, $3);
        }
        | expression SUB_T expression
        {
            $$ = nb_create_binary_expression(SUB, $1, $3);            
        }
        | expression MUL_T expression
        {
            $$ = nb_create_binary_expression(MUL, $1, $3);            
        }
        | expression DIV_T expression
        {
            $$ = nb_create_binary_expression(DIV, $1, $3);            
        }
        | expression MOD_T expression
        {
            $$ = nb_create_binary_expression(MOD, $1, $3);            
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
    function_definition_statement: INT_T LP formal_argument_list RP block;
        | DOUBLE_T LP formal_argument_list RP block;
        | STRING_T LP formal_argument_list RP block;
        | ARRAY_T LP formal_argument_list RP block;
    block: LC statement_list RC
        | LC RC
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