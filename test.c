#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include "utility.h"

typedef enum
{
    INT,
    DOUBLE,
    STRING,
    ARRAY,
    ARRAY_ASSOC
} NBValueType;

typedef struct NB_Array_Assoc_tag NB_Array_Assoc;

typedef struct NB_Value 
{
    NBValueType type;
    union 
    {
        int int_value;
        double double_value;
        char *string_value;
        struct NB_Value *array;
    } value;
} NB_Value;

struct NB_Array_Assoc_tag
{
    char **index;
    struct NB_Value *value;
};

int main(int argc, char *argv[])  
{  
    String *str = string_new();
    string_append(str, "asd");
    string_append(str, "张逸达");
    printf("%d", str->size);
    printf("%d", str->length);
}  

void print_NB_Value(NB_Value *value)
{
    char *s = value->value.string_value;
    printf("%s", s);
}