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
    StatementsList       *statement_list;
    ParametersList       *parameter_list;
    ArgumentsList        *argument_list;
}
%expect 78
%left LOGICAL_AND LOGICAL_OR
%left EQ_T NE_T GT_T GE_T LT_T LE_T
%left ADD_T SUB_T
%left MUL_T DIV_T MOD_T
%nonassoc UMINUS
%token <expression>     INT_LITERAL STRING_LITERAL DOUBLE_LITERAL BOOL_LITERAL
%token <identifier>     IDENTIFIER
%token INT_T DOUBLE_T BOOL_T STRING_T ARRAY_T VAR_T FUNC_T IF ELSE ELSEIF FOR IN CLASS RETURN BREAK CONTINUE
        LP RP LC RC LB RB SEMICOLON COMMA ASSIGN_T EXCLAMATION DOT
        ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
        INCREMENT_T DECREMENT_T
%type<expression> expression function_call_expression declaration_expression primary_expression assignment_expression expression_optional binary_expression unary_expression
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
        | CLASS block
        {
            $$ = nb_create_class_definition_statement($2);
        }
        | block
        | function_definition_statement
        ;
    expression: assignment_expression
        | declaration_expression
        | binary_expression
        | unary_expression
        | primary_expression
        | function_call_expression
        | LP expression RP
        {
            $$ = $2;
        }
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
        | expression LOGICAL_AND expression
        {
            $$ = nb_create_binary_expression(AND, $1, $3);
        }
        | expression LOGICAL_OR expression
        {
            $$ = nb_create_binary_expression(OR, $1, $3);
        }
        ;
    unary_expression: SUB_T expression %prec UMINUS
        {
            $$ = nb_create_unary_expression(MINUS, $2);
        }
        | EXCLAMATION expression %prec UMINUS
        {
            $$ = nb_create_unary_expression(NOT, $2);
        }
        | IDENTIFIER INCREMENT_T
        {
            $$ = nb_create_change_expression(INCREMENT, $1);
        }
        | IDENTIFIER DECREMENT_T
        {
            $$ = nb_create_change_expression(DECREMENT, $1);
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
        | VAR_T IDENTIFIER
        {
            $$ = nb_create_declaration_expression(VARIOUS, $2, NULL);
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
        | VAR_T assignment_expression 
        {
            $$ = nb_create_declaration_expression(VARIOUS, NULL, $2);
        }
        ;
    assignment_expression: IDENTIFIER ASSIGN_T expression
        {
            $$ = nb_create_assignment_expression($1, $3);
        }
        | IDENTIFIER ADD_ASSIGN expression
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression(ADD, nb_create_identifier_expression(utf8_string_copy_new($1)), $3));
        }
        | IDENTIFIER SUB_ASSIGN expression
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression(SUB, nb_create_identifier_expression(utf8_string_copy_new($1)), $3));
        }
        | IDENTIFIER MUL_ASSIGN expression
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression(MUL, nb_create_identifier_expression(utf8_string_copy_new($1)), $3));
        }
        | IDENTIFIER DIV_ASSIGN expression
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression(DIV, nb_create_identifier_expression(utf8_string_copy_new($1)), $3));
        }
        | IDENTIFIER MOD_ASSIGN expression
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression(MOD, nb_create_identifier_expression(utf8_string_copy_new($1)), $3));
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
        | FUNC_T IDENTIFIER LP parameter_list RP block
        {
            $$ = nb_create_function_definition_statement(VARIOUS, $2, $4, $6);
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
    argument_list: /* empty */
        {
            $$ = NULL;
        }
        | expression
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
            $$ = NULL;
        }
        | declaration_expression
        {
            $$ = nb_create_parameter_list($1);
        }
        | parameter_list COMMA declaration_expression
        {
            $$ = nb_cat_parameter_list($1, $3);
        }
        ;
%%