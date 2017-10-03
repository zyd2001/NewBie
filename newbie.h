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
    MOD
} ComputationType;

typedef enum
{
    EQ,
    NE,
    GT,
    GE,
    LT,
    LE
} ComparisonType;

typedef enum 
{
    INT,
    DOUBLE,
    STRING,
    IDENTIFIER,
    ASSIGNMENT_EXPRESSION,
    COMPARISON_EXPRESSION,
    COMPUTATION_EXPRESSION,
    FUNCTION_CALL_EXPRESSION  
} ExpressionType;

typedef ValueType NB_ValueType;

typedef Value NB_Value;

typedef struct Expression_tag Expression;

typedef struct AssignmentExpression_tag
{
    char *identifier;
    Expression *exp;
} AssignmentExpression;

typedef struct Expression_tag 
{
    ExpressionType type; 
    int line_number;
    union 
    {
        int int_literal;
        double double_literal;
        char* string_literal;
        NB_Value *value;
        char *identifier;
        ComparisonExpression *comparison_expression;
        AssignmentExpression *assignment_expression;
        ComputationExpression *computation_expression;
        FunctionCallExpression *function_call_expression;
    } content;
} Expression;

typedef struct Statement_tag
{
  
}

Expression *nb_create_assignment_expression(char *identifier, Expression *exp);
Expression *nb_create_comparison_expression(ComparisonType type, Expression *exp1, Expression *exp2);

#endif
