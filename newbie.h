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
    EXPRESSION,
    RETURN
} StatementType;

typedef ValueType NB_ValueType;

typedef Value NB_Value;

typedef struct Expression_tag Expression;

typedef struct AssignmentExpression_tag
{
    UTF8_String *identifier;
    Expression *exp;
} AssignmentExpression;

typedef struct DeclarationExpression_tag
{
    UTF8_String *identifier;
    Expression *exp;
} DeclarationExpression;

typedef struct BinaryExpression_tag
{
    BinaryType type;
    Expression *first;
    Expression *second;
} BinaryExpression;

typedef struct Expression_tag 
{
    ExpressionType type; 
    union 
    {
        // int int_literal;
        // double double_literal;
        // char* string_literal;
        NB_Value literal;
        UTF8_String *identifier;
        AssignmentExpression assignment_expression;
        DeclarationExpression declaration_expression;
        BinaryExpression binary_expression;
        // FunctionCallExpression function_call_expression;
    } content;
} Expression;

typedef struct Statement_tag
{
    StatementType type;
    int line_number;
    union
    {
        Expression *expression;
    } content;
} Statement;

typedef struct StatementList_tag
{
    Statement *s;
    struct StatementList_tag *prev;
    struct StatementList_tag *next;
} StatementList;

Expression *nb_create_literal_expression(NB_ValueType type, char *text);
Expression *nb_create_assignment_expression(UTF8_String *identifier, Expression *exp);
Expression *nb_create_binary_expression(BinaryType type, Expression *left, Expression *right);
Expression *nb_create_declaration_expression(NB_ValueType type, UTF8_String *identifier, Expression *assignment_expression);
Expression *nb_create_identifier_expression(UTF8_String *identifier);

Statement *nb_create_expression_statement(Expression *exp);
#endif
