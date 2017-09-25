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
    char gbk[LEN];
    char utf8[LEN];
    FILE *file = fopen("input", "r");
    fgets(gbk, LEN, file);
    encoding_convert(gbk, strlen(gbk), utf8, LEN, "gbk", "utf-8");
    printf("%s", utf8);
}