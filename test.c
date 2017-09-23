#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include "utility.h"

typedef Value NB_Value;
typedef ValueType NB_ValueType;

int main(int argc, char *argv[])  
{
    NB_ValueType type = INT;
    Value *val = value_new(type);
    Array *arr = array_new();
    val->value.int_value = 0;
    for (int i = 0; i < 6; i++)
    {
        array_push(arr, val);
        val->value.int_value++;
    }
    Value *rem = array_remove(arr, 4);
    array_insert(arr, rem, 2);
    value_delete(rem);
    value_delete(val);
    array_delete(arr);
}