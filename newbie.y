%{

#include "newbie.h"
#include "newbie.tab.h"

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
    fprintf (stderr, "%s %d\n", s, inter->current_line);
}
%}
%union {
    UTF8_String         *identifier;
    Expression          *expression;
    Statement           *statement;
    StatementsList      *statement_list;
    ParametersList      *parameter_list;
    ArgumentsList       *argument_list;
    ExpressionList      *expression_list;
    NB_ValueType        type;
}
%expect 91
%left LOGICAL_AND LOGICAL_OR
%left EQ_T NE_T GT_T GE_T LT_T LE_T
%left ADD_T SUB_T
%left MUL_T DIV_T MOD_T
%nonassoc UMINUS
%token <expression>     INT_LITERAL STRING_LITERAL DOUBLE_LITERAL BOOL_LITERAL
%token <identifier>     IDENTIFIER
%token INT_T DOUBLE_T BOOL_T STRING_T ARRAY_T VAR_T IF ELSE ELSEIF FOR IN CLASS RETURN BREAK CONTINUE
        LP RP LC RC LB RB SEMICOLON COMMA ASSIGN_T EXCLAMATION DOT
        ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
        INCREMENT_T DECREMENT_T PUBLIC PROTECTED PRIVATE REVERSE
%type<expression> expression function_call_expression declaration_expression primary_expression assignment_expression expression_optional binary_expression unary_expression possible_array_expression
                    index_expression assignment_lval_expression declaration_rval_expression parameter_list_item
%type<statement> statement block function_definition_statement
%type<statement_list> statement_list
%type<argument_list> argument_list
%type<parameter_list> parameter_list
%type<expression_list> expression_list
%type<type> type_tag
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
    expression: assignment_expression
        | declaration_expression
        | binary_expression
        | unary_expression
        | primary_expression
        | index_expression
        | possible_array_expression
        | type_tag LP parameter_list RP block
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
        | LB expression_list RB
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
        | assignment_lval_expression INCREMENT_T
        {
            $$ = nb_create_unary_expression(INCREMENT, $1);
        }
        | assignment_lval_expression DECREMENT_T
        {
            $$ = nb_create_unary_expression(DECREMENT, $1);
        }
        ;
    function_call_expression: IDENTIFIER LP argument_list RP
        {
            $$ = nb_create_function_call_expression($1, $3);
        }
        ;
    declaration_rval_expression: IDENTIFIER ASSIGN_T expression
        {
            $$ = nb_create_assignment_expression(nb_create_identifier_expression($1), $3);
        }
        ;
    declaration_expression: type_tag IDENTIFIER
        {
            $$ = nb_create_declaration_expression($1, $2, NULL);
        }
        | type_tag declaration_rval_expression
        {
            $$ = nb_create_declaration_expression($1, NULL, $2);
        }
        ;
    assignment_lval_expression: index_expression
        | IDENTIFIER
        {
            $$ = nb_create_identifier_expression($1);
        }
        ;
    assignment_expression: assignment_lval_expression ASSIGN_T expression
        {
            $$ = nb_create_assignment_expression($1, $3);
        }
        | assignment_lval_expression ADD_ASSIGN expression
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression_sp(ADD, $1, $3));
        }
        | assignment_lval_expression SUB_ASSIGN expression
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression_sp(SUB, $1, $3));
        }
        | assignment_lval_expression MUL_ASSIGN expression
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression_sp(MUL, $1, $3));
        }
        | assignment_lval_expression DIV_ASSIGN expression
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression_sp(DIV, $1, $3));
        }
        | assignment_lval_expression MOD_ASSIGN expression
        {
            $$ = nb_create_assignment_expression($1, nb_create_binary_expression_sp(MOD, $1, $3));
        }
        ;    
    primary_expression: INT_LITERAL
        | DOUBLE_LITERAL
        | STRING_LITERAL
        | BOOL_LITERAL
        ;
    expression_list: expression
        {
            $$ = nb_create_expression_list($1);
        }
        | expression_list COMMA expression
        {
            $$ = nb_cat_expression_list($1, $3);
        }
        ;
    function_definition_statement: type_tag IDENTIFIER LP parameter_list RP block
        {
            $$ = nb_create_function_definition_statement($1, $2, $4, $6);
        }
        ;
    type_tag: INT_T
        {
            $$ = INT;
        }
        | DOUBLE_T
        {
            $$ = DOUBLE;
        }
        | BOOL_T
        {
            $$ = BOOL;
        }
        | STRING_T
        {
            $$ = STRING;
        }
        | ARRAY_T
        {
            $$ = ARRAY;
        }
        | VAR_T
        {
            $$ = VARIOUS;
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
    parameter_list_item: declaration_expression
        | type_tag IDENTIFIER LP RP
        {
            $$ = nb_create_declaration_expression($1, utf8_string_append_char($2, '$'), NULL);
        }
        ;
    parameter_list: /* empty */
        {
            $$ = NULL;
        }
        | parameter_list_item
        {
            $$ = nb_create_parameter_list($1);
        }
        | parameter_list COMMA parameter_list_item
        {
            $$ = nb_cat_parameter_list($1, $3);
        }
        ;
%%