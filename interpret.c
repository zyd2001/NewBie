#include "newbie.h"

void nb_interpret(NB_Interpreter *inter)
{
    for (;inter->global_list->prev != NULL; inter->global_list = inter->global_list->prev);
    for (StatementList *temp = list; temp != NULL; temp = temp->next)
    {
        Statement *s = temp->s;
        switch (s->type)
        {
            case EXPRESSION:
            {
                Expression *e = s->content.expression;
                switch (e->type)
                {
                    case LITERAL_EXPRESSION:
                    {
                        break;
                    }
                    case DECLARATION_EXPRESSION
                    {
                        break;
                    }
                }
                break;
            }
        }
    }
}