#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <dlfcn.h>
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
    LE,
    AND,
    OR
} BinaryType;

typedef enum
{
    MINUS,
    NOT,
    INCREMENT,
    DECREMENT
} UnaryType;

typedef enum 
{
    LITERAL_EXPRESSION,
    IDENTIFIER_EXPRESSION,
    ASSIGNMENT_EXPRESSION,
    DECLARATION_EXPRESSION,
    BINARY_EXPRESSION,
    UNARY_EXPRESSION,
    FUNCTION_CALL_EXPRESSION,
    ARRAY_EXPRESSION,
    INDEX_EXPRESSION
} ExpressionType;

typedef enum
{
    NULL_RESULT,
    EXPRESSION_STATEMENT,
    FUNCTION_DEFINITION_STATEMENT,
    CLASS_DEFINITION_STATEMENT,
    BLOCK_STATEMENT,
    IF_STATEMENT,
    ELSE_STATEMENT,
    FOR_STATEMENT,
    FOREACH_STATEMENT,
    RETURN_STATEMENT,
    CONTINUE_STATEMENT,
    BREAK_STATEMENT
} StatementType;

typedef ValueType NB_ValueType;

typedef Value NB_Value;

typedef struct Expression_tag Expression;
typedef struct Statement_tag Statement;
typedef struct StatementsList_tag StatementsList;

typedef struct ArgumentsList_tag
{
    Expression *exp;
    struct ArgumentsList_tag *prev;
    struct ArgumentsList_tag *next;
} ArgumentsList;

typedef struct ParametersList_tag
{
    Expression *exp;
    struct ParametersList_tag *prev;
    struct ParametersList_tag *next;
} ParametersList;

typedef struct AssignmentExpression_tag
{
    Expression *lval;
    Expression *rval;
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

typedef struct UnaryExpression_tag
{
    UnaryType type;
    Expression *exp;
} UnaryExpression;

typedef struct FunctionCallExpression_tag
{
    UTF8_String *identifier;
    ArgumentsList *alist;
} FunctionCallExpression;

typedef struct ExpressionList_tag
{
    Expression *exp;
    struct ExpressionList_tag *next;
} ExpressionList;

typedef struct IndexExpression_tag
{
    Expression *exp;
    Expression *index;
} IndexExpression;

typedef struct Expression_tag 
{
    ExpressionType type; 
    char ref;    
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
        UnaryExpression unary_expression;
        FunctionCallExpression function_call_expression;
        ExpressionList *expression_list;
        IndexExpression index_expression;
    } content;
} Expression;

typedef struct Block_tag
{
    StatementsList *slist;
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

struct StatementsList_tag
{
    Statement *s;
    struct StatementsList_tag *prev;
    struct StatementsList_tag *next;
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
    ParametersList *plist;
    int pnum;
    char builtin;
    NB_ValueType type;
    UTF8_String *identifier;
    Statement *block;
    NB_Value *(*builtin_ptr)(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier));
    struct FunctionList_tag *prev;
    struct FunctionList_tag *next;
} FunctionList;

typedef struct ClassList_tag
{
    Statement *block;
    FunctionList *func_list;
    UTF8_String *identifier;
    struct ClassList_tag *prev;
    struct ClassList_tag *next;
} ClassList;

typedef struct HandleList_tag
{
    void *handle;
    struct HandleList_tag *next;
} HandleList;

typedef struct NB_Interpreter_tag
{
    int current_line;
    int level;
    int block_state;
    StatementsList *statements_list;
    StatementsList *global_slist;
    VariablesList *variables_list;
    FunctionList *func_list;
    ClassList *class_list;
    HandleList *handle_list;
    VariablesList *temp_vlist;
} NB_Interpreter;

typedef struct StatementResult_tag
{
    StatementType type;
    union 
    {
        NB_Value *value;
        char *error_msg;
    } content;
} StatementResult;

Expression *nb_create_literal_expression(NB_ValueType type, char *text);
Expression *nb_create_assignment_expression(Expression *lval, Expression *rval);
Expression *nb_create_binary_expression(BinaryType type, Expression *left, Expression *right);
Expression *nb_create_binary_expression_sp(BinaryType type, Expression *left, Expression *right);
Expression *nb_create_unary_expression(UnaryType type, Expression *exp);
// Expression *nb_create_change_expression(UnaryType type, UTF8_String *identifier);
Expression *nb_create_declaration_expression(NB_ValueType type, UTF8_String *identifier, Expression *assignment_expression);
Expression *nb_create_identifier_expression(UTF8_String *identifier);
Expression *nb_create_array_expression(ExpressionList *elist);
Expression *nb_create_function_call_expression(UTF8_String *identifier, ArgumentsList *alist);
Expression *nb_create_index_expression(Expression *exp, Expression *index);

Statement *nb_create_expression_statement(Expression *exp);
Statement *nb_create_block_statement(StatementsList *slist);
Statement *nb_create_class_definition_statement(UTF8_String *identifier, Statement *block);
Statement *nb_create_if_statement(Expression *exp, Statement *block);
Statement *nb_create_foreach_statement(UTF8_String *identifier, Expression *exp, Statement *block);
Statement *nb_create_for_statement(Expression *exp1, Expression *exp2, Expression *exp3, Statement *block);
Statement *nb_create_return_statement(Expression *exp);
Statement *nb_create_continue_statement();
Statement *nb_create_break_statement();
Statement *nb_create_function_definition_statement(NB_ValueType type, UTF8_String *identifier, ParametersList *plist, Statement *block);
Statement *nb_cat_else_statement(Statement *block);
Statement *nb_cat_elseif_statement(Expression *exp, Statement *block);

StatementsList *nb_create_statement_list(Statement *s);
StatementsList *nb_cat_statement_list(StatementsList *slist, Statement *s);

ArgumentsList *nb_create_argument_list(Expression *exp);
ArgumentsList *nb_cat_argument_list(ArgumentsList *alist, Expression *exp);

ParametersList *nb_create_parameter_list(Expression *exp);
ParametersList *nb_cat_parameter_list(ParametersList *plist, Expression *exp);

ExpressionList *nb_create_expression_list(Expression *exp);
ExpressionList *nb_cat_expression_list(ExpressionList *elist, Expression *exp);

void nb_interpret();
StatementResult nb_interpret_once();
void level_increase();
void level_decrease();
NB_Value *eval(Expression *exp, VariablesList **vlist);
// void eval_no_ret(Expression *exp, VariablesList **vlist);
NB_Interpreter *nb_get_interpreter();
NB_Interpreter *nb_interpreter_new();
int nb_interpreter_set(NB_Interpreter *inter);
void nb_interpreter_init();
void nb_add_builtin_func(FunctionList **flist, int pnum, NB_Value *(*ptr)(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier)), UTF8_String *identifier, NB_ValueType type, char **pname_array, NB_ValueType *ptype);
void nb_add_global_variable(NB_Value *val, UTF8_String *identifier);
void nb_clean();
void nb_error(char *str);
void nb_warning(char *str);
void nb_compile(FILE *fp);

#define new_statement_result() (StatementResult*)calloc(1, sizeof(StatementResult));

#endif