#ifndef INCLUDED_HEAD
#define INCLUDED_HEAD

#include <stdio.h>


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

typedef enum
{
    INT,
    DOUBLE,
    STRING,
    ARRAY,
    ARRAY_ASSOC
} NBValueType;

typedef struct NB_Value_tag 
{
    NBValueType type;
    union 
    {
        int int_value;
        double double_value;
        char *string_value;
        struct NB_Value *array;
        struct NB_Array_Assoc 
        {
            char **index;
            struct NB_Value *value;
        } array_assoc;
    } value;
} NB_Value;

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
        NB_Value *raw_value;
        char *identifier;
        ComparisonExpression *comparison_expression;
        AssignmentExpression *assignment_expression;
        ComputationExpression *computation_expression;
        FunctionCallExpression *function_call_expression;
    } u;
} Expression;

typedef struct Statement_tag
{
  
}

Expression *create_assignment_expression(char *identifier, Expression *exp);

#endif