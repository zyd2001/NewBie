#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>
#include "utility.h"

int main(void)
{
    int count = 0;
    
    for (int i = 0; i < 10; i++)
    {
        if (count == 5)
        {
            count = 10;
        }
        else if (count == 4)
        {
            count = 20;
        }
        count++;
    }
}