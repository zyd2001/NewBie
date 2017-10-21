%{

#include "newbie.h"
#include "y.tab.h"

extern int lex(void);
static int flag = 0;
int yylex(void)
{
    if (flag == 0)
    {
        flag++;
        return INT_LITERAL;
    }
    else if (flag == 1)
    {
        flag++;
        return SEMICOLON;
    }
    return lex();
}
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
    ParameterList       *parameter_list;
    ArgumentList        *argument_list;
}
%expect 187
%token <expression>     INT_LITERAL STRING_LITERAL DOUBLE_LITERAL BOOL_LITERAL
%token <identifier>     IDENTIFIER
%token INT_T DOUBLE_T BOOL_T STRING_T ARRAY_T IF ELSE ELSEIF FOR IN CLASS RETURN BREAK CONTINUE
        LP RP LC RC LB RB SEMICOLON COMMA ASSIGN_T LOGICAL_AND LOGICAL_OR
        EQ_T NE_T GT_T GE_T LT_T LE_T ADD_T SUB_T MUL_T DIV_T MOD_T EXCLAMATION DOT
        ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
        INCREMENT DECREMENT
%type<expression> expression function_call_expression declaration_expression primary_expression assignment_expression expression_optional binary_expression
%type<statement> statement block function_definition_statement
%type<statement_list> statement_list
%type<argument_list> argument_list
%type<parameter_list> parameter_list
%%
    statement_list: statement
        {
            $$ = nb_create_statement_list($1);
        }
        | statement_list statement
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
        | FOR LP IDENTIFIER IN expression RP block
        {
            $$ = nb_create_foreach_statement($3, $5, $7);
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
        | block
        | function_definition_statement
        ;
    expression: assignment_expression
        | declaration_expression
        | binary_expression
        | primary_expression
        | function_call_expression
        | IDENTIFIER
        {
            $$ = nb_create_identifier_expression($1);
        }
        ;
    expression_optional: /* empty */
        {
            $$ = NULL;
        }
        | expression
        ;
    binary_expression: expression ADD_T expression
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
        | expression EQ_T expression
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
    function_call_expression: IDENTIFIER LP argument_list RP
        {
            $$ = nb_create_function_call_expression($1, $3);
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
        | BOOL_T IDENTIFIER
        {
            $$ = nb_create_declaration_expression(BOOL, $2, NULL);
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
        | BOOL_T assignment_expression 
        {
            $$ = nb_create_declaration_expression(BOOL, NULL, $2);
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
    assignment_expression: IDENTIFIER ASSIGN_T expression
        {
            $$ = nb_create_assignment_expression($1, $3);
        }
        | IDENTIFIER ADD_ASSIGN expression
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression(ADD, nb_create_identifier_expression($1), $3));
        }
        | IDENTIFIER SUB_ASSIGN expression
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression(SUB, nb_create_identifier_expression($1), $3));
        }
        | IDENTIFIER MUL_ASSIGN expression
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression(MUL, nb_create_identifier_expression($1), $3));
        }
        | IDENTIFIER DIV_ASSIGN expression
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression(DIV, nb_create_identifier_expression($1), $3));
        }
        | IDENTIFIER MOD_ASSIGN expression
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression(MOD, nb_create_identifier_expression($1), $3));
        }
        | IDENTIFIER INCREMENT
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression(ADD, nb_create_identifier_expression($1), nb_create_literal_expression(INT, "1")));            
        }
        | IDENTIFIER DECREMENT
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression(SUB, nb_create_identifier_expression($1), nb_create_literal_expression(INT, "1")));            
        }
        ;
    primary_expression: INT_LITERAL
        | DOUBLE_LITERAL
        | STRING_LITERAL
        | BOOL_LITERAL
        ;
    function_definition_statement: INT_T IDENTIFIER LP parameter_list RP block
        {
            $$ = nb_create_function_definition_statement(INT, $2, $4, $6);
        }
        | DOUBLE_T IDENTIFIER LP parameter_list RP block
        {
            $$ = nb_create_function_definition_statement(DOUBLE, $2, $4, $6);
        }
        | BOOL_T IDENTIFIER LP parameter_list RP block
        {
            $$ = nb_create_function_definition_statement(BOOL, $2, $4, $6);
        }
        | STRING_T IDENTIFIER LP parameter_list RP block
        {
            $$ = nb_create_function_definition_statement(STRING, $2, $4, $6);
        }
        | ARRAY_T IDENTIFIER LP parameter_list RP block
        {
            $$ = nb_create_function_definition_statement(ARRAY, $2, $4, $6);
        }
        ;
    block: LC statement_list RC
        {
            $$ = nb_create_block_statement($2);
        }
        | LC RC
        {
            $$ = nb_create_block_statement(NULL);
        }
        ;
    argument_list: expression
        {
            $$ = nb_create_argument_list($1);
        }
        | argument_list COMMA expression
        {
            $$ = nb_cat_argument_list($1, $3);
        }
        ;
    parameter_list: /* empty */
        {
            $$ = nb_create_parameter_list(INT, NULL);
        }
        | INT_T expression
        {
            $$ = nb_create_parameter_list(INT, $2);
        }
        | DOUBLE_T expression
        {
            $$ = nb_create_parameter_list(DOUBLE, $2);
        }
        | BOOL_T expression
        {
            $$ = nb_create_parameter_list(BOOL, $2);
        }
        | STRING_T expression
        {
            $$ = nb_create_parameter_list(STRING, $2);
        }
        | ARRAY_T expression
        {
            $$ = nb_create_parameter_list(ARRAY, $2);
        }
        | parameter_list COMMA INT_T expression
        {
            $$ = nb_cat_parameter_list(INT, $1, $4);
        }
        | parameter_list COMMA DOUBLE_T expression
        {
            $$ = nb_cat_parameter_list(DOUBLE, $1, $4);
        }
        | parameter_list COMMA BOOL_T expression
        {
            $$ = nb_cat_parameter_list(BOOL, $1, $4);
        }
        | parameter_list COMMA STRING_T expression
        {
            $$ = nb_cat_parameter_list(STRING, $1, $4);
        }
        | parameter_list COMMA ARRAY_T expression
        {
            $$ = nb_cat_parameter_list(ARRAY, $1, $4);
        }
        ;
%%