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
    setlocale(LC_ALL, "");
    char *str = "zyd张逸达";
    wchar_t *wstr2 = L"连接123";
    wchar_t *wstr = (wchar_t*)malloc((utf8_strlen(str) + 1) * sizeof(wchar_t));
    wcscpy(wstr, wstr2);
    printf("%ls", wstr);
    free(wstr);
}