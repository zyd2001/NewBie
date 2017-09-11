#ifndef INCLUDED_HEAD
#define INCLUDED_HEAD

#include <stdio.h>

typedef struct ParameterList 
{
} ParameterList;

typedef struct NB_Value 
{
  union 
  {
    int int_value;
    double double_value;
    char *string_value;
    NB_Array array;
    NB_Array_Assoc array_assoc;
  } value;
} NB_Value;

typedef NB_Value *NB_Array;

typedef struct NB_Array_Assoc
{
  char **index;
  NB_Value *value;
}

typedef struct Expression 
{
    ExpressionType type; 
    int line_number;
    union {

    } v;
} Expression;

typedef enum 
{
  ASSIGNMENT_EXPRESSION,
  COMPARISON_EXPRESSION,
  
} ExpressionType;

typedef struct 
{
  Expression *expression;
  Identifier *identifier;

} ARGUMENTS;

Expression *create_assignment_expression(char *identifier, Expression *exp);

#endif