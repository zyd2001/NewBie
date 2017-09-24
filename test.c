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
    String *test = string_new(), *a = string_new_wrap("23四五");
    string_append(test, "一二三123四五六七八九十");
    printf("%d", string_indexof(test, a));
    a = string_delete(a);
    test = string_delete(test);
}