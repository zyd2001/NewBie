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
        str->value = (char*)realloc(str->value, (old_length + new_length + 10) * sizeof(char));
        str->limit = old_length + new_length + 10;
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