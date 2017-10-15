#include <stdio.h>
#include "newbie.h"

int current_line;
StatementList *slist;

int main(int argc, char **argv)
{
    extern int yyparse(void);
    current_line = 1;
    slist = NULL;
    FILE *fp;
    fp = fopen(argv[1], "r");
    extern FILE *yyin;
    yyin = fp;
    yyparse();
}