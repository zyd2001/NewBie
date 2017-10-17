#include "newbie.h"

static NB_Interpreter *inter;

void nb_interpret()
{
    for (;inter->global_list->prev != NULL; inter->global_list = inter->global_list->prev);
    for (StatementList *temp = inter->global_list; temp != NULL; temp = temp->next)
    {
        Statement *s = temp->s;
        switch (s->type)
        {
            case EXPRESSION:
            {
                Expression *e = s->content.expression;
                NB_Value *result = eval(e);
                value_delete(&result);
            }
        }
    }
}

NB_Interpreter *interpreter_new()
{
    NB_Interpreter *inter = (NB_Interpreter*)calloc(1, sizeof(NB_Interpreter));
    inter->current_line = 1;
    inter->level = 0;
    inter->global_list = NULL;
    inter->variables_list = NULL;
}

int interpreter_init(NB_Interpreter *interpreter)
{
    inter = interpreter;
    return 1;
}

NB_Interpreter *get_interpreter()
{
    return inter;
}

void nb_clean()
{
    __free(inter);
}

void nb_error(char *str)
{
    fprintf(stderr, "%s\n", str);
    nb_clean();
}