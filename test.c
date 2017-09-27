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
    char out[LEN];
    FILE *file = fopen("input", "r");
    FILE *fp = fopen("output", "wb");
    fgets(gbk, LEN, file);
    size_t len = encoding_convert(gbk, strlen(gbk), utf8, LEN, "utf-32be", "utf-8");
    fwrite(&utf8, len, 1, fp);
    for (int i = 0; i < 100; i++)
    {
        printf("%d ", utf8[i]);
    }
    printf("%d\n", len);
}