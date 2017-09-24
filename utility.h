#ifndef INCLUDED_UTILITY_HEAD
#define INCLUDED_UTILITY_HEAD

typedef struct Value_tag Value;

typedef struct Array_tag
{
    int limit;
    int size;
    char **index;
    struct Value_tag *value;
} Array;

typedef struct UTF8_String_tag {
    char *value;
    int size;
    int limit;
    int length;
} UTF8_String;

typedef struct Wide_String_tag {
    wchar_t *value;
    int length;
    int limit;
} Wide_String;

typedef enum ValueType_tag
{
    INT,
    DOUBLE,
    STRING,
    ARRAY
} ValueType;

struct Value_tag 
{
    ValueType type;
    union 
    {
        int int_value;
        double double_value;
        wchar_t *string_value;
        Array *array_value;
    } value;
};

int utf8_strlen(char *str);
UTF8_String *utf8_string_new();
UTF8_String *utf8_string_new_wrap(char *str);
UTF8_String *utf8_string_new_char(char ch);
UTF8_String *utf8_string_append(UTF8_String *str, char *new);
// return NULL
void *utf8_string_delete(UTF8_String *str);
int utf8_string_compare(UTF8_String *first, UTF8_String *second);
UTF8_String *utf8_string_reassign(UTF8_String *str, char *new);
UTF8_String *utf8_string_copy(UTF8_String *destination, UTF8_String *source);
UTF8_String *utf8_string_substring(UTF8_String *str, int start, int end);
UTF8_String *utf8_string_substr();
char utf8_string_get_char_ascii(UTF8_String *str, int index);
UTF8_String *utf8_string_get_char(UTF8_String *str, int index);
UTF8_String *utf8_string_append_char(UTF8_String *str, char ch);
int utf8_string_indexof(UTF8_String *str, char *target);
int utf8_string_test_indexof(UTF8_String *str, UTF8_String *target); //这个贼J8傻逼，就测试用的
char *utf8_string_get_value(UTF8_String *str);
int utf8_string_get_length(UTF8_String *str);

wchar_t *utf8_to_wcs(char *str); //need to be freed after use
Wide_String *wide_string_append(Wide_String *str, wchar_t *new);

Value *value_new(ValueType type);
void *value_delete(Value *val);
Value *value_copy(Value *destination, Value *source);

Array *array_new();
void *array_delete(Array *arr);
Array *array_push(Array *arr, Value *value);
Value *array_get(Array *arr, int index);
Array *array_insert(Array *arr, Value *val, int index);
Value *array_remove(Array *arr, int index);
Value *array_pull(Array *arr);
Array *array_copy(Array *destination, Array *source);

#endif