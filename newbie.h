#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utility.h"
#ifndef INCLUDED_HEAD
#define INCLUDED_HEAD

typedef enum
{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    EQ,
    NE,
    GT,
    GE,
    LT,
    LE
} BinaryType;

typedef enum 
{
    LITERAL_EXPRESSION,
    IDENTIFIER_EXPRESSION,
    ASSIGNMENT_EXPRESSION,
    DECLARATION_EXPRESSION,
    BINARY_EXPRESSION,
    FUNCTION_CALL_EXPRESSION  
} ExpressionType;

typedef enum
{
    EXPRESSION_STATEMENT,
    FUNCTION_DEFINITION_STATEMENT,
    BLOCK_STATEMENT,
    IF_STATEMENT,
    ELSE_STATEMENT,
    FOR_STATEMENT,
    FOREACH_STATEMENT,
    RETURN_STATEMENT,
    CONTINUE_STATEMENT,
    BREAK_STATEMENT,
    NULL_RESULT
} StatementType;

typedef ValueType NB_ValueType;

typedef Value NB_Value;

typedef struct Expression_tag Expression;

typedef struct Statement_tag Statement;
typedef struct StatementList_tag StatementList;

typedef struct ArgumentList_tag
{
    Expression *exp;
    struct ArgumentList_tag *prev;
    struct ArgumentList_tag *next;
} ArgumentList;

typedef struct ParameterList_tag
{
    NB_ValueType type;
    Expression *aexp;
    struct ParameterList_tag *prev;
    struct ParameterList_tag *next;
} ParameterList;

typedef struct AssignmentExpression_tag
{
    UTF8_String *identifier;
    Expression *exp;
} AssignmentExpression;

typedef struct DeclarationExpression_tag
{
    NB_ValueType type;
    UTF8_String *identifier;
    Expression *exp;
} DeclarationExpression;

typedef struct BinaryExpression_tag
{
    BinaryType type;
    Expression *first;
    Expression *second;
} BinaryExpression;

typedef struct FunctionCallExpression_tag
{
    UTF8_String *identifier;
    ArgumentList *alist;
} FunctionCallExpression;

typedef struct Expression_tag 
{
    ExpressionType type; 
    union 
    {
        // int int_literal;
        // double double_literal;
        // char* string_literal;
        NB_Value literal_expression;
        UTF8_String *identifier_expression;
        AssignmentExpression assignment_expression;
        DeclarationExpression declaration_expression;
        BinaryExpression binary_expression;
        FunctionCallExpression function_call_expression;
    } content;
} Expression;

typedef struct Block_tag
{
    StatementList *slist;
} Block;

typedef struct ElseIf_tag
{
    Expression *exp;
    Statement *block;
    struct ElseIf_tag *prev;
    struct ElseIf_tag *next;
} ElseIfList;

typedef struct If_tag
{
    Statement *block;
    Expression *exp;
    Statement *else_block;
    ElseIfList *elseif_list;
} If;

typedef struct Foreach_tag
{
    UTF8_String *identifier;
    Expression *exp;
    Statement *block;
} Foreach;

typedef struct For_tag
{
    Expression *exp1;
    Expression *exp2;
    Expression *exp3;
    Statement *block;
} For;

struct Statement_tag
{
    StatementType type;
    int line_number;
    union
    {
        Block block_statement;
        Expression *expression;
        If if_statement;
        Foreach foreach_statement;
        For for_statement;
    } content;
};

struct StatementList_tag
{
    Statement *s;
    struct StatementList_tag *prev;
    struct StatementList_tag *next;
};

typedef struct VariablesList_tag
{
    UTF8_String *identifier;
    NB_Value *value;
    int level;
    struct VariablesList_tag *prev;
    struct VariablesList_tag *next;
} VariablesList;

typedef struct FunctionList_tag
{
    ParameterList *plist;
    NB_ValueType type;
    UTF8_String *identifier;
    Statement *block;
    struct FunctionList_tag *prev;
    struct FunctionList_tag *next;
} FunctionList;

typedef struct NB_Interpreter_tag
{
    int current_line;
    int level;
    StatementList *global_list;
    // StatementList **temp_slist;
    VariablesList *variables_list;
    FunctionList *func_list;
} NB_Interpreter;

typedef struct StatementResult_tag
{
    StatementType type;
    NB_Value *value;
} StatementResult;

Expression *nb_create_literal_expression(NB_ValueType type, char *text);
Expression *nb_create_assignment_expression(UTF8_String *identifier, Expression *exp);
Expression *nb_create_binary_expression(BinaryType type, Expression *left, Expression *right);
Expression *nb_create_declaration_expression(NB_ValueType type, UTF8_String *identifier, Expression *assignment_expression);
Expression *nb_create_identifier_expression(UTF8_String *identifier);
Expression *nb_create_function_call_expression(UTF8_String *identifier, ArgumentList *alist);

Statement *nb_create_expression_statement(Expression *exp);
Statement *nb_create_block_statement(StatementList *slist);
Statement *nb_create_if_statement(Expression *exp, Statement *block);
Statement *nb_create_foreach_statement(UTF8_String *identifier, Expression *exp, Statement *block);
Statement *nb_create_for_statement(Expression *exp1, Expression *exp2, Expression *exp3, Statement *block);
Statement *nb_create_return_statement(Expression *exp);
Statement *nb_create_continue_statement();
Statement *nb_create_break_statement();
Statement *nb_create_function_definition_statement(NB_ValueType type, UTF8_String *identifier, ParameterList *plist, Statement *block);
Statement *nb_cat_else_statement(Statement *block);
Statement *nb_cat_elseif_statement(Expression *exp, Statement *block);

StatementList *nb_create_statement_list(Statement *s);
StatementList *nb_cat_statement_list(StatementList *slist, Statement *s);

ArgumentList *nb_create_argument_list(Expression *exp);
ArgumentList *nb_cat_argument_list(ArgumentList *alist, Expression *exp);

ParameterList *nb_create_parameter_list(NB_ValueType type, Expression *exp);
ParameterList *nb_cat_parameter_list(NB_ValueType type, ParameterList *plist, Expression *exp);

void nb_interpret();
NB_Value *eval(Expression *exp);
NB_Interpreter *nb_get_interpreter();
NB_Interpreter *nb_interpreter_new();
int nb_interpreter_set(NB_Interpreter *inter);
void nb_interpreter_init();
void nb_clean();
void nb_error(char *str);
void nb_warning(char *str);

StatementList *statement(Statement *s);
StatementList *statementl(StatementList *slist, Statement *s);
#endif