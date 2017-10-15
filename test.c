#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include "utility.h"

int main(void)
{
    int *a = (int*)malloc(50 * sizeof(int));
    void *b = (void*)a;
    free(b);
}