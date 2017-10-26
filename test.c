#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>
#include "utility.h"

int main(void)
{
    FILE *setting = fopen("NewBie.ini", "r");
    char *filename =(char*)malloc(30 * sizeof(char));
    fgets(filename, 30, setting);
    // fgets(filename, 30, setting);
    for (int i = 0; i < strlen(filename); i++)
    {
        if (filename[i] == '\n')
        {
            filename[i] = '\0';
            break;
        }
    }
    fclose(setting);
    free(filename);
}