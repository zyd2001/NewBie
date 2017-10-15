#include "newbie.h"

NB_Interpreter *inter;

int main(int argc, char **argv)
{
    extern int yyparse(void);
    FILE *fp;
    fp = fopen(argv[1], "r");
    extern FILE *yyin;
    yyin = fp;

    inter = (NB_Interpreter*)calloc(1, sizeof(NB_Interpreter));
    // inter->ptrs_list = NULL;
    inter->current_line = 1;
    yyparse();
    nb_interpret(inter);
}