#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>
#include "utility.h"

int main(void)
{
    char *str = (char*)malloc(10 * sizeof(char));
    str = (char*)realloc(str, 5 * sizeof(char));
    free(str);
}