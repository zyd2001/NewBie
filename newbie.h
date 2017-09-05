#ifndef INCLUDED_HEAD
#define INCLUDED_HEAD

#include <stdio.h>

typedef struct ParameterList
{

} ParameterList;

typedef struct NB_Value
{
    union {
        int int_value;
        double double_value;
        char *string_value;
    }
} NB_Value;

typedef struct NB_Array
{
    NB_Value value;
    struct NB_Array *next;
} NB_Array;

typedef struct Expression
{

} Expression;

typedef enum 
{
    
}ExpressionType;

#endif