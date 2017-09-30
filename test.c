#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iconv.h>
#include "utility.h"

int main()
{
    UTF32_String *new = utf32_string_new_wrap_utf8("张逸达zyd233张逸达");
    UTF32_String *cut = utf32_string_substring(new, 5, 8);
    printf("%d", utf32_string_indexof_utf8(new, "3张逸达"));
    utf32_string_print(cut);
    new = utf32_string_delete(new);
    cut = utf32_string_delete(cut);
}