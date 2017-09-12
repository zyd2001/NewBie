#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>

int my_strlen_utf8_c(char *s) {
    int i = 0, j = 0;
    while (s[i]) {
      if ((s[i] & 0xc0) != 0x80) j++;
      i++;
    }
    return j;
  }
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
    NB_Value v, a, b, *c;
    a.value.int_value = 123;
    c = &a;
    v.value.array = malloc(sizeof(NB_Value));
    printf("%d", a.value.int_value);
}  

void print_NB_Value(NB_Value *value)
{

}