#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

int utf8_strlen(char *str) 
{
    int result = 0;
    for (int i = 0; str[i]; i++) 
    {
        if ((str[i] & 0xc0) != 0x80) 
            result++;
    }
    return result;
}

int char_index_to_utf8_index(char *str, int index)
{
    int result = 0;
    for (int i = 0; i < index; i++)
    {
        if ((str[i] & 0xc0) != 0x80)
            result++;
    }
    return result;
}

UTF8_String *utf8_string_new()
{
    UTF8_String *str;
    str = (UTF8_String*)malloc(sizeof(UTF8_String));
    str->size = 0;
    str->limit = 10;
    str->length = 0;
    str->value = (char*)malloc(10 * sizeof(char));
    return str;
}

UTF8_String *utf8_string_new_wrap(char *str)
{
    UTF8_String *new = utf8_string_new();
    return utf8_string_append(new, str);
}

UTF8_String *utf8_string_new_char(char ch)
{
    UTF8_String *str;
    str = (UTF8_String*)malloc(sizeof(UTF8_String));
    str->size = 0;
    str->limit = 0;
    str->length = 0;
    str->value = NULL;
    return utf8_string_append_char(str, ch);
}

UTF8_String *utf8_string_append(UTF8_String *str, char *new)
{
    int new_length, old_length;
    old_length = str->size;
    new_length = strlen(new);
    if (old_length + new_length + 1 > str->limit)
    {
        str->limit = old_length + new_length + 10;
        str->value = (char*)realloc(str->value, str->limit * sizeof(char));
    }
    strcpy(str->value + old_length, new);
    str->size = new_length + old_length;
    str->length = utf8_strlen(str->value);
    return str;
}

UTF8_String *utf8_string_append_char(UTF8_String *str, char ch)
{
    if (str->size + 2 > str->limit)
    {
        str->limit = str->size + 2;
        str->value = (char*)realloc(str->value, str->limit * sizeof(char));
    }
    char *temp;
    temp = str->value + str->size;
    temp[0] = ch;
    temp[1] = '\0';
    str->size++;
    str->length = utf8_strlen(str->value);
    return str;
}

UTF8_String *utf8_string_reassign(UTF8_String *str, char *new)
{
    str->size = 0;
    str->length = 0;
    return utf8_string_append(str, new);
}

int utf8_string_compare(UTF8_String *first, UTF8_String *second)
{
    return strcmp(first->value, second->value);
}

UTF8_String *utf8_string_copy(UTF8_String *destination, UTF8_String *source)
{
    UTF8_String *new;
    if(destination == NULL)
        new = utf8_string_new();
    else
        new = destination;
    new->size = source->size;
    new->length = source->length;
    new->limit = source->limit;
    new->value = (char*)realloc(new->value, source->limit * sizeof(char));
    strcpy(new->value, source->value);
    return new;
}

void *utf8_string_delete(UTF8_String *str)
{
    free(str->value);
    free(str);
    return NULL;
}

UTF8_String *utf8_string_substring(UTF8_String *str, int start, int end)
{
    int j = -1;
    int starti = -1;
    int endi = -1;
    int len;
    for (int i = 0; i < str->size; i++)
    {
        if ((str->value[i] & 0xc0) != 0x80)
            j++;
        if (j == start && starti == -1)
            starti = i;
        if (j == end)
        {
            endi = i;
            break;
        }
    }
    if (endi == -1)
        endi = str->size;
    UTF8_String *new = utf8_string_new();
    len = endi - starti;
    char *temp = (char*)malloc((len + 1) * sizeof(char));
    memcpy(temp, str->value + starti, len);
    temp[len] = '\0';
    utf8_string_append(new, temp);
    free(temp);
    return new;
}

UTF8_String *utf8_string_substr(UTF8_String *str, int start, int length)
{
    return utf8_string_substring(str, start, start + length);
}

char utf8_string_get_char_ascii(UTF8_String *str, int index)
{
    return (str->value + index)[0];
}

UTF8_String *utf8_string_get_char(UTF8_String *str, int index)
{
    return utf8_string_substring(str, index, index + 1);
}

int utf8_string_indexof(UTF8_String *str, char *target)
{
    int size = strlen(target);
    if (str->size < size)
        return -1;
    for (int i = 0; i < (str->size - size + 1); i++)
    {
        if (strncmp(str->value + i, target, size) == 0)
            return char_index_to_utf8_index(str->value, i);
    }
    return -1;
}

int utf8_string_test_indexof(UTF8_String *str, UTF8_String *target)
{
    int length = target->length;
    UTF8_String *temp;
    if (str->length < length)
        return -1;
    for (int i = 0; i < (str->length - length + 1); i++)
    {
        temp = utf8_string_substr(str, i, length);
        if (utf8_string_compare(temp, target) == 0)
        {
            temp = utf8_string_delete(temp);
            return i;
        }
        temp = utf8_string_delete(temp);
    }
    temp = utf8_string_delete(temp);
    return -1;
}

char *utf8_string_get_value(UTF8_String *str)
{
    return str->value;
}

int utf8_string_get_length(UTF8_String *str)
{
    return str->length;
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
            new->value.utf8_string_value = utf8_string_new();
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
            val->value.utf8_string_value = utf8_string_delete(val->value.utf8_string_value);
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
            new->value.utf8_string_value = utf8_string_copy(NULL, source->value.utf8_string_value);
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
    new->limit = arr->limit + 1;
    new->value = (Value*)realloc(new->value, new->limit * sizeof(Value));
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
    new->limit = arr->limit - 1;
    new->size = arr->size - 1;
    new->value = (Value*)realloc(new->value, new->limit * sizeof(Value));
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