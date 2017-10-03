#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "utility.h"

__build_copy_func(UTF32_String*, utf32_string_copy, utf32_string_new, utf32_copy)

int main()
{
    Linked_List *list = linked_list_new();
    UTF32_String *test = utf32_string_new_wrap_utf8("测试");
    char temp = 1;
    list = linked_list_insert(list, temp, NULL, char);
    list = linked_list_insert(list, test, utf32_copy, UTF32_String*);
    utf32_string_print(linked_list_get(list, 1, UTF32_String*));
    char get = linked_list_get(list, 0, char);
    utf32_string_delete(&test);
}