#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

int utf8_strlen(char *s) {
    int i = 0, j = 0;
    while (s[i]) {
        if ((s[i] & 0xc0) != 0x80) j++;
        i++;
    }
    return j;
}

String *string_new()
{
    String *str;
    str = (String*)malloc(sizeof(String));
    str->size = 0;
    str->limit = 10;
    str->length = 0;
    str->value = (char*)malloc(10 * sizeof(char));
    return str;
}

String *string_append(String *str, char *new)
{
    int new_length, old_length, limit;
    old_length = str->size;
    new_length = strlen(new);
    if (old_length + new_length > str->limit)
    {
        str->limit = old_length + new_length + 10;
        str->value = (char*)realloc(str->value, str->limit * sizeof(char));
    }
    strcpy(str->value + old_length, new);
    str->size = new_length + old_length;
    str->length = utf8_strlen(str->value);
    return str;
}

String *string_reassign(String *str, char *new)
{
    str->size = 0;
    str->length = 0;
    return string_append(str, new);
}

int string_compare(String *first, String *second)
{
    return strcmp(first->value, second->value);
}

String *string_copy(String *destination, String *source)
{
    String *new;
    if(destination == NULL)
        new = string_new();
    else
        new = destination;
    new->size = source->size;
    new->length = source->length;
    new->limit = source->limit;
    new->value = (char*)realloc(new->value, source->limit * sizeof(char));
    strcpy(new->value, source->value);
    return new;
}

void *string_delete(String *str)
{
    free(str->value);
    free(str);
    return NULL;
}

Value *value_new(ValueType type)
{
    Value *new = (Value*)malloc(sizeof(Value));
    new->type = type;
    switch(type)
    {
        case INT:
            new->value.int_value = 0;
            break;
        case DOUBLE:
            new->value.double_value = 0.0;
            break;
        case STRING:
            new->value.string_value = string_new();
            break;
        case ARRAY:
            new->value.array_value = array_new();
            break;
    }
    return new;
}

void *value_delete(Value *val)
{
    switch(val->type)
    {
        case STRING:
            val->value.string_value = string_delete(val->value.string_value);
            break;
        case ARRAY:
            val->value.array_value = array_delete(val->value.array_value);
            break;
    }
    free(val);
    return NULL;
}

Value *value_copy(Value *destination, Value *source)
{
    Value *new;
    if (destination == NULL)
        new = value_new(source->type);
    else
    {
        new = destination;
        new->type = source->type;
    }
    switch(new->type)
    {
        case INT:
            new->value.int_value = source->value.int_value;
            break;
        case DOUBLE:
            new->value.double_value = source->value.double_value;
            break;
        case STRING:
            new->value.string_value = string_copy(NULL, source->value.string_value);
            break;
        case ARRAY:
            new->value.array_value = array_copy(NULL, source->value.array_value);
            break;
    }
    return new;
}

Array *array_new()
{
    Array *arr = (Array*)malloc(sizeof(Array));
    arr->limit = 5;
    arr->size = 0;
    arr->index = (char**)malloc(sizeof(char*) * 5);
    arr->value = (Value*)malloc(5 * sizeof(Value));
}

void *array_delete(Array *arr)
{
    free(arr->index);
    free(arr->value);
    free(arr);
    return NULL;
}

Array *array_push(Array *arr, Value *value)
{
    if (arr->size >= arr->limit)
    {
        arr->limit += 5;
        arr->value = (Value*)realloc(arr->value, arr->limit * sizeof(Value));
    }
    memcpy(arr->value + arr->size, value, sizeof(Value));
    arr->size++;
    return arr;
}

Value *array_get(Array *arr, int index)
{
    if ((index + 1) > arr->size)
    {
        fprintf(stderr, "OutOfBoundary");
        exit(1);
    }
    return value_copy(NULL, arr->value + index);
}

Array *array_insert(Array *arr, Value *val, int index)
{
    Array *new = array_new();
    new->size = index;
    new->value = (Value*)realloc(new->value, (arr->size + 1) * sizeof(Value));
    memcpy(new->value, arr->value, index * sizeof(Value));
    array_push(new, val);
    memcpy(new->value + index + 1, arr->value + index, (arr->size - index) * sizeof(Value));
    new->size = arr->size + 1;
    array_copy(arr, new);
    new = array_delete(new);
    return arr;
}

Value *array_remove(Array *arr, int index)
{
    Value *val = value_copy(NULL, arr->value + index);
    Array *new = array_new();
    new->size = arr->size - 1;
    new->value = (Value*)realloc(new->value, new->size * sizeof(Value));
    memcpy(new->value, arr->value, index * sizeof(Value));
    memcpy(new->value + index, arr->value + index + 1, (arr->size - index - 1) * sizeof(Value));
    array_copy(arr, new);
    new = array_delete(new);
    return val;
}

Value *array_pull(Array *arr)
{
    return array_remove(arr, arr->size - 1);
}

Array *array_copy(Array *destination, Array *source)
{
    Array *new;
    if (destination == NULL)
        new = array_new();
    else
        new = destination;
    new->limit = source->limit;
    new->size = source->size;
    new->value = (Value*)realloc(new->value, new->size * sizeof(Value));
    new->index = (char**)realloc(new->index, new->size * sizeof(char*));
    memcpy(new->value, source->value, new->size * sizeof(Value));
    memcpy(new->index, source->index, sizeof(char*));
    return new;
}