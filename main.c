#include "NewBie.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }
    else
    {
        nb_interpreter_set(nb_interpreter_new());
        nb_compile(fp);
        nb_interpreter_init();
        nb_interpret();
        nb_clean();
    }
}