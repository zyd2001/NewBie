#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <wchar.h>
#include <iconv.h>
#include <stdarg.h>
#include "utility.h"
#define OUT_PUT_ENCODING "utf-8"

struct Array_tag
{
    int limit;
    int size;
    char **index;
    Value *value;
};

struct UTF8_String_tag 
{
    char *value;
    int size;
    int limit;
    int length;
};

// struct Wide_String_tag {
//     wchar_t *value;
//     int length;
//     int limit;
// };

struct UTF32_String_tag 
{
    char *value;
    int length;
    size_t limit;
    size_t size;
};

struct Linked_List_tag
{
    Linked_List *prev;
    Linked_List *next;
    void *data;
    int index;
    char primitive;
    unsigned int type_name;
};

unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131;
    unsigned int hash = 0;
    while(*str)
    {
        hash = hash*seed + (*str++);
    }
    return hash%0x7FFFFFFF;
}

size_t encoding_convert(char *instr, int inlen, char *outstr, int outlen, const char *to, const char *from)
{
    iconv_t cd = iconv_open(to, from);
    char **inbuf = &instr;
    char **outbuf = &outstr;
    size_t in = inlen;
    size_t out = outlen;
    memset(outstr, 0, outlen);
    iconv(cd, inbuf, &in, outbuf, &out);
    iconv_close(cd);
    return outlen - out;
}

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

// UTF8_String *utf8_string_new_wrap(char *str)
// {
//     UTF8_String *new = utf8_string_new();
//     return utf8_string_append(new, str);
// }

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
    if(destination == NULL)
        destination = utf8_string_new();
    destination->size = source->size;
    destination->length = source->length;
    destination->limit = source->limit;
    destination->value = (char*)realloc(destination->value, source->limit * sizeof(char));
    strcpy(destination->value, source->value);
    return destination;
}

void *utf8_string_delete_func(UTF8_String **str, ...)
{
    va_list args;
    va_start(args, str);
    for (UTF8_String **i = str; i != NULL; i = va_arg(args, UTF8_String**))
    {
        free((*i)->value);
        (*i)->value = NULL;
        free(*i);
        *i = NULL;
    }
    va_end(args);
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

// UTF8_String *utf8_string_substr(UTF8_String *str, int start, int length)
// {
//     return utf8_string_substring(str, start, start + length);
// }

char utf8_string_get_char_ascii(UTF8_String *str, int index)
{
    return (str->value + index)[0];
}

// UTF8_String *utf8_string_get_char(UTF8_String *str, int index)
// {
//     return utf8_string_substring(str, index, index + 1);
// }

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
            utf8_string_delete(&temp);
            return i;
        }
        utf8_string_delete(&temp);
    }
    utf8_string_delete(&temp);
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

// wchar_t *utf8_to_wcs(char *str)
// {
//     int length = utf8_strlen(str);
//     wchar_t *new = (wchar_t*)calloc(length + 1, sizeof(wchar_t));
//     mbstowcs(new, str, length);
//     return new;
// }

// Wide_String *wide_string_new()
// {
//     Wide_String *new = (Wide_String*)malloc(sizeof(Wide_String));
//     new->length = 0;
//     new->limit = 10;
//     new->value = (wchar_t*)malloc(10 * sizeof(wchar_t));
//     return new;
// }

// Wide_String *wide_string_new_wrap(wchar_t *str)
// {
//     Wide_String *new = wide_string_new();
//     wide_string_append(new, str);
//     return new;
// }

// Wide_String *wide_string_new_wrap_mbs(char *str)
// {
//     wchar_t *wstr = utf8_to_wcs(str);
//     Wide_String *new = wide_string_new_wrap(wstr);
//     free(wstr);
//     wstr = NULL;
//     return new;
// }

// Wide_String *wide_string_new_char(wchar_t ch)
// {

// }

// Wide_String *wide_string_append(Wide_String *str, wchar_t *new)
// {
//     int length = wcslen(new);
//     if (str->length + length + 1 > str->limit)
//     {
//         str->limit = str->length + length + 10;
//         str->value = (wchar_t*)realloc(str->value, str->limit * sizeof(wchar_t));
//     }
//     wcscpy(str->value + str->length, new);
//     str->length += length;
//     return str;
// }

// Wide_String *wode_string_append_char(Wide_String *str, wchar_t ch)
// {

// }

// void *wide_string_delete(Wide_String *str)
// {
//     free(str->value);
//     str->value = NULL;
//     free(str);
//     return NULL;
// }

UTF32_String *utf8_to_utf32(char *str)
{
    size_t utf8_len = utf8_strlen(str);
    size_t utf8_size = strlen(str);
    size_t utf32_size = utf8_len * 4;
    char *utf32 = (char*)malloc(utf32_size * sizeof(char));
    int size = encoding_convert(str, utf8_size, utf32, utf32_size, "utf-32le", "utf-8");
    if (size == 0)
    {
        fprintf(stderr, "incomplete convertion");  
        exit(1);
    }
    else
    {
        UTF32_String *new = utf32_string_new();
        new->length = utf8_len;
        new->size = utf32_size;
        new->limit = utf32_size;
        new->value = (char*)realloc(new->value, utf32_size);
        memcpy(new->value, utf32, utf32_size);
        free(utf32);
        utf32 = NULL;
        return new;
    }
}

UTF32_String *utf32_string_new()
{
    UTF32_String *new = (UTF32_String*)malloc(sizeof(UTF32_String));
    new->length = 0;
    new->limit = 40;
    new->size = 0;
    new->value = (char*)malloc(40 * sizeof(char));
    return new;
}

// UTF32_String *utf32_string_new_wrap(char *str, size_t new_size)
// {
//     UTF32_String *new = utf32_string_new();
//     return utf32_string_append(new, str, new_size);
// }

// UTF32_String *utf32_string_new_wrap_utf32(UTF32_String *str)
// {
//     UTF32_String *new = utf32_string_new();
//     utf32_string_append_utf32(new, str);
//     return new;
// }

// UTF32_String *utf32_string_new_wrap_utf8(char *str)
// {
//     UTF32_String *new = utf32_string_new();
//     utf32_string_append_free(new, utf8_to_utf32(str));
//     return new;
// }

UTF32_String *utf32_string_append(UTF32_String *str, char *new, size_t new_size)
{
    size_t old_size = str->size;
    if (old_size + new_size > str->limit)
    {
        str->limit = old_size + new_size + 40;
        str->value = (char*)realloc(str->value, str->limit);
    }
    memcpy(str->value + old_size, new, new_size);
    str->size += new_size;
    str->length = str->size / 4;
    return str;
}

UTF32_String *utf32_string_append_utf32(UTF32_String *str, UTF32_String *new)
{
    size_t old_size = str->size;
    size_t new_size = new->size;
    if (old_size + new_size > str->limit)
    {
        str->limit = old_size + new_size + 40;
        str->value = (char*)realloc(str->value, str->limit);
    }
    memcpy(str->value + old_size, new->value, new_size);
    str->size += new_size;
    str->length = str->size / 4;
    return str;
}

UTF32_String *utf32_string_append_free(UTF32_String *str, UTF32_String *new)
{
    utf32_string_append_utf32(str, new);
    utf32_string_delete(&new);
    return str;
}

// UTF32_String *utf32_string_append_utf8(UTF32_String *str, char *new)
// {
//     return utf32_string_append_free(str, utf32_string_new_wrap_utf8(new));
// }

UTF32_String *utf32_string_reassign_utf8(UTF32_String *str, char *new)
{
    str->length = 0;
    str->size = 0;
    return utf32_string_append_utf8(str, new);
}

int utf32_string_compare_utf32(UTF32_String *first, UTF32_String *second)
{
    if (first->size > second->size)
        return 1;
    else if(first->size < second->size)
        return -1;
    else
    {
        for (int i = 0; i < first->size; i++)
        {
            if (first->value[i] == second->value[i])
                continue;
            else
                return first->value[i] - second->value[i];
        }
        return 0;
    }
}

int utf32_string_compare(char *first, size_t size1, char *second, size_t size2)
{
    if (size1 > size2)
        return 1;
    else if(size1 < size2)
        return -1;
    else
    {
        for (int i = 0; i < size1; i++)
        {
            if (first[i] == second[i])
                continue;
            else
                return first[i] - second[i];
        }
        return 0;
    }
}

UTF32_String *utf32_string_copy(UTF32_String *destination, UTF32_String *source)
{
    if (destination == NULL)
        destination = utf32_string_new();
    destination->size = source->size;
    destination->limit = source->limit;
    destination->length = source->length;
    destination->value = (char*)realloc(destination->value, source->size);
    memcpy(destination->value, source->value, source->size);
    return destination;
}

// UTF32_String *utf32_string_substring(UTF32_String *str, int start, int end)
// {
//     return utf32_string_substr(str, start, end - start);    
// }

UTF32_String *utf32_string_substr(UTF32_String *str, int start, int length)
{
    size_t len = length * 4;
    char temp[len];
    memcpy(temp, str->value + start * 4, len);
    return utf32_string_new_wrap(temp, len);
}

int utf32_string_indexof(UTF32_String *str, char *target, size_t size)
{
    for (int i = 0; i < str->size && str->size - i >= size; i += 4)
    {
        if (!utf32_string_compare(str->value + i, size, target, size))
            return i / 4;
    }
    return -1;
}

int utf32_string_indexof_utf8(UTF32_String *str, char *target)
{
    UTF32_String *new = utf32_string_new_wrap_utf8(target);
    int i = utf32_string_indexof_utf32(str, new);
    utf32_string_delete(&new);
    return i;
}

int utf32_string_indexof_utf32(UTF32_String *str, UTF32_String *target)
{
    for (int i = 0; i < str->size && str->size - i >= target->size; i += 4)
    {
        if (!utf32_string_compare(str->value + i, target->size, target->value, target->size))
            return i / 4;
    }
    return -1;
}

size_t utf32_string_print(UTF32_String *str)
{
    char *out = (char*)malloc(str->size);
    encoding_convert(str->value, str->size, out, str->size, OUT_PUT_ENCODING, "utf-32le");
    size_t size = printf("%s", out);
    free(out);
    return size;
}

char *utf32_string_get_value(UTF32_String *str)
{
    return str->value;
}

size_t utf32_string_get_length(UTF32_String *str)
{
    return str->length;
}

void *utf32_string_delete_func(UTF32_String **str, ...)
{
    va_list args;
    va_start(args, str);
    for (UTF32_String **i = str; i != NULL; i = va_arg(args, UTF32_String**))
    {
        free((*i)->value);
        (*i)->value = NULL;
        free(*i);
        *i = NULL;
    }
    va_end(args);
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
            new->value.string_value = utf32_string_new();
            break;
        case ARRAY:
            new->value.array_value = array_new();
            break;
    }
    return new;
}

void *value_delete_func(Value **val, ...)
{
    va_list args;
    va_start(args, val);
    for (Value **i = val; i != NULL; i = va_arg(args, Value**))
    {
        switch((*i)->type)
        {
            case STRING:
                utf32_string_delete(&(*i)->value.string_value);
                break;
            case ARRAY:
                array_delete(&(*i)->value.array_value);
                break;
        }
        free(*i);
        *i = NULL;
    }
    va_end(args);
    return NULL;
}

Value *value_copy(Value *destination, Value *source)
{
    if (destination == NULL)
        destination = value_new(source->type);
    switch(destination->type)
    {
        case INT:
            destination->value.int_value = source->value.int_value;
            break;
        case DOUBLE:
            destination->value.double_value = source->value.double_value;
            break;
        case STRING:
            destination->value.string_value = utf32_string_copy(NULL, source->value.string_value);
            break;
        case ARRAY:
            destination->value.array_value = array_copy(NULL, source->value.array_value);
            break;
    }
    return destination;
}

Array *array_new()
{
    Array *arr = (Array*)malloc(sizeof(Array));
    arr->limit = 5;
    arr->size = 0;
    arr->index = (char**)malloc(sizeof(char*) * 5);
    arr->value = (Value*)malloc(5 * sizeof(Value));
}

void *array_delete_func(Array **arr, ...)
{
    va_list args;
    va_start(args, arr);
    for (Array **i = arr; i != NULL; i = va_arg(args, Array**))
    {
        free((*i)->index);
        free((*i)->value);
        free(*i);
        *i = NULL;
    }
    va_end(args);
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
    array_delete(&new);
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
    array_delete(&new);
    return val;
}

Value *array_pop(Array *arr)
{
    return array_remove(arr, arr->size - 1);
}

Array *array_copy(Array *destination, Array *source)
{
    if (destination == NULL)
        destination = array_new();
    destination->limit = source->limit;
    destination->size = source->size;
    destination->value = (Value*)realloc(destination->value, destination->size * sizeof(Value));
    destination->index = (char**)realloc(destination->index, destination->size * sizeof(char*));
    memcpy(destination->value, source->value, destination->size * sizeof(Value));
    memcpy(destination->index, source->index, sizeof(char*));
    return destination;
}

#define move_to(list, index) \
do { \
    for (;list->index > index; list = list->prev); \
    for (;list->index < index; list = list->next); \
} while(0)

Linked_List *linked_list_node_new()
{
    Linked_List *new = (Linked_List*)malloc(sizeof(Linked_List));
    new->prev = NULL;
    new->next = NULL;
    new->data = NULL;
    new->type_name = 0;
    new->index = -1;
    return new;
}

int linked_list_insert_func(Linked_List **list, void *item, size_t size, char primitive, void (*copy_func)(void*, const void*), char *type_name, int index)
{
    Linked_List *temp = *list;
    Linked_List *new = linked_list_node_new();
    new->primitive = primitive;
    if (linked_list_empty(temp))
    {
        temp = new;
        temp->type_name = BKDRHash(type_name);
        temp->data = (void*)malloc(size);
        if (copy_func == NULL)
            memcpy(temp->data, item, size);
        else
            copy_func(temp->data, item);
        temp->index = temp->prev == NULL ? 0 : temp->prev->index + 1;
        (*list) = temp;
        return 1;
    }
    if (index == -1)
    {
        for (;temp->next != NULL; temp = temp->next);
        temp->next = new;
        new->prev = temp;
        temp = new;
        temp->type_name = BKDRHash(type_name);
        temp->data = (void*)malloc(size);
        if (copy_func == NULL)
            memcpy(temp->data, item, size);
        else
            copy_func(temp->data, item);
        temp->index = temp->prev == NULL ? 0 : temp->prev->index + 1;
        (*list) = temp;
        return 1;
    }
    else
    {
        move_to(temp, index);
        if (temp->prev)
            temp->prev->next = new;
        new->prev = temp->prev;
        new->next = temp;
        temp->prev = new;
        new->type_name = BKDRHash(type_name);
        new->data = (void*)malloc(size);
        if (copy_func == NULL)
            memcpy(new->data, item, size);
        else
            copy_func(new->data, item);
        new->index = new->prev == NULL ? 0 : new->prev->index + 1;
        for (;temp != NULL; temp = temp->next)
            temp->index++;
        (*list) = new;
        return 1;
    }
}

void *linked_list_get_func(Linked_List **list, int index)
{
    Linked_List *temp = *list;
    if (linked_list_empty(temp))
        return NULL;      
    move_to(temp, index);        
    (*list) = temp;
    return temp->data;
}

int linked_list_get_length(Linked_List *list)
{
    for (;list->next != NULL; list = list->next);
    return list->index + 1;
}

int linked_list_remove_item(Linked_List **list, struct delete_func_struct_tag *delete_func_struct, int index)
{
    Linked_List *temp = *list, *stored;
    if (index = -1)
        for (;temp->next != NULL; temp = temp->next);
    else
        move_to(temp, index);
    if (delete_func_struct)
    {
        if (delete_func_struct->type_name = temp->type_name)
        {
            delete_func_struct->real_func(temp->data);
            __free(temp->data);
            stored = temp;
            if (temp->prev)
                temp->prev->next = temp->next;
            if (temp->next)
            {
                temp->next->prev = temp->prev;
                for (;temp != NULL; temp = temp->next)
                    temp->index--;
            }
        }
        else
            return -1;
    }
    else
    {
        __free(temp->data);
        stored = temp;
        if (temp->prev)
            temp->prev->next = temp->next;
        if (temp->next)
        {
            temp->next->prev = temp->prev;
            for (;temp != NULL; temp = temp->next)
                temp->index--;
        }
    }
    if (stored->next == NULL && stored->prev == NULL)
        __free(*list);
    else
        __free(stored);
    return 1;
}

int linked_list_delete_func(Linked_List **list, struct delete_func_struct_tag *delete_func_struct[], size_t size)
{
    if (linked_list_empty(*list))
        return 0;
    else
    {
        Linked_List *temp = *list, *stored, *next = (*list)->next;
        while (temp != NULL)
        {
            if (delete_func_struct != NULL && !temp->primitive)
            {
                int flag = 1;
                for (int i = 0; i < size; i++)
                {
                    if (delete_func_struct[i]->type_name == temp->type_name)
                    {
                        flag = 0;
                        delete_func_struct[i]->real_func(temp->data);
                        __free(temp->data);
                        stored = temp->prev;
                        __free(temp);
                        temp = stored;
                    }
                    else
                        continue;
                }
                if (flag)
                    return -1;
            }
            else
            {
                __free(temp->data);
                stored = temp->prev;
                __free(temp);
                temp = stored;
            }
        }
        temp = next; // the next part
        while (temp != NULL)
        {
            if (delete_func_struct != NULL && !temp->primitive)
            {
                int flag = 1;
                for (int i = 0; i < size; i++)
                {
                    if (delete_func_struct[i]->type_name == temp->type_name)
                    {
                        flag = 0;
                        delete_func_struct[i]->real_func(temp->data);
                        __free(temp->data);
                        stored = temp->next;
                        __free(temp);
                        temp = stored;
                    }
                    else
                        continue;
                }
                if (flag)   // no delete_func match
                    return -1;
            }
            else
            {
                __free(temp->data);
                stored = temp->next;
                __free(temp);
                temp = stored;
            }
        }
    }
    *list = NULL;
    return 1;
}