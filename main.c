#include <stdio.h>

int main(int argc, char **argv)
{
    FILE *fp;
    fp = fopen(argv[1], "r");
    extern FILE *yyin;
     yyin = fp;

     yyparse();
}