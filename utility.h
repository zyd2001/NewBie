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

typedef struct String_tag {
    char* value;
    int size;
    int limit;
    int length;
} String;

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
        String *string_value;
        Array *array_value;
    } value;
};

String *string_new();
String *string_append(String *str, char *new);
// return NULL
void *string_delete(String *str);
int string_compare(String *first, String *second);
String *string_reassign(String *str, char *new);
String *string_copy(String *destination, String *source);

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