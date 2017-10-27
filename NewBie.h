#ifndef NEWBIE_HEADER
#define NEWBIE_HEADER

typedef struct NB_Interpreter_tag NB_Interpreter;

NB_Interpreter *nb_interpreter_new();
int nb_interpreter_set(NB_Interpreter *inter);
void nb_compile(void *file); // FILE
void nb_interpreter_init();
void nb_interpret();
void nb_clean();
#endif