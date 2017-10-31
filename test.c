#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>
#include "utility.h"

int main(void)
{
    Value *val1 = value_new_type(INT);
    val1->value.int_value = 1;
    // Value *val2 = value_new_type(INT);
    // val2->value.int_value = 2;
    // Value *test = value_new();
    // test->type = ARRAY;
    // test->value.array_value = array_new();
    // array_push(test->value.array_value, val1);
    Array *arr = array_new();
    array_push(arr, val1);
    // array_push(arr, val2);
    // array_push(arr, test);
    // Value *get = array_get(arr, 2);
    // Value *get1 = array_get_addr(test->value.array_value, 0);
    Array *arr2 = array_copy_new(arr);
    array_delete(&arr, &arr2);
    value_delete(&val1);
}