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
    struct NB_Value *NB_Array;
  }
} NB_Value;

typedef struct Expression 
{
    ExpressionType type; 
} Expression;

typedef enum 
{
  ASSIGN_EXPRESSION,
} ExpressionType;

#endif