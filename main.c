#include "newbie.h"

extern int yylex_destroy(void);

int main(int argc, char **argv)
{
    extern int yyparse(void);
    FILE *fp;
    fp = fopen(argv[1], "r");
    extern FILE *yyin;
    yyin = fp;

    nb_interpreter_set(nb_interpreter_new());
    yyparse();
    yylex_destroy();
    fclose(fp);
    
    nb_interpreter_init();
    nb_interpret();
    nb_clean();
}