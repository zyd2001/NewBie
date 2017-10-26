#include "NewBie.h"

int main(int argc, char **argv)
{
    nb_interpreter_set(nb_interpreter_new());
    nb_compile(argv[1]);
    nb_interpreter_init();
    nb_interpret();
    nb_clean();
}