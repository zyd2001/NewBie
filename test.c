#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <iconv.h>
#include <locale.h>
#include <wchar.h>
#include "utility.h"
#define LEN 255

int main(int argc, char *argv[])  
{
    UTF32_String *new = utf32_string_new_wrap_mbs("张逸达zyd");
    utf32_string_print(new);
    new = utf32_string_delete(new);
}