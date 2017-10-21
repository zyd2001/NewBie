#include "newbie.h"

static NB_Interpreter *inter;

StatementResult nb_interpret_once();
void level_increase();
void level_decrease();

void nb_interpret()
{
    StatementResult result;
    result.type = NULL_RESULT;
    do {
        if (result.type == EXPRESSION_STATEMENT)
            value_delete(&result.value);
        result = nb_interpret_once();
    } while(result.type != NULL_RESULT);
}

StatementResult nb_interpret_once()
{
    StatementResult result;
    if (inter->global_list != NULL)
    {
        switch (inter->global_list->s->type)
        {
            case EXPRESSION_STATEMENT:
            {
                result.type = EXPRESSION_STATEMENT;
                result.value = eval(inter->global_list->s->content.expression);
                break;
            }
            case BLOCK_STATEMENT:
            {
                result.type = BLOCK_STATEMENT;
                StatementList *stored = inter->global_list;
                inter->global_list = inter->global_list->s->content.block_statement.slist;
                for (;inter->global_list->prev != NULL; inter->global_list = inter->global_list->prev);                
                level_increase();
                nb_interpret();
                level_decrease();
                inter->global_list = stored;
                break;
            }
            case FOR_STATEMENT:
            {
                result.type = FOR_STATEMENT;
                StatementList *stored = inter->global_list, *this_slist = inter->global_list->s->content.for_statement.block->content.block_statement.slist;
                for (;this_slist->prev != NULL; this_slist = this_slist->prev);
                Statement *s = inter->global_list->s;
                level_increase();
                eval(s->content.for_statement.exp1);
                StatementResult r;
                for (;value_to_bool(&(NB_Value*){eval(s->content.for_statement.exp2)})->value.int_value;eval(s->content.for_statement.exp3))
                {
                    inter->global_list = this_slist;
                    r.type = NULL_RESULT;
                    do {
                        if (r.type == EXPRESSION_STATEMENT)
                            value_delete(&(r.value));
                        if (r.type == BREAK_STATEMENT)
                            goto break_tag;
                        if (r.type == CONTINUE_STATEMENT)
                            goto continue_tag;
                        r = nb_interpret_once();
                    } while(r.type != NULL_RESULT);
                    continue;
                    break_tag:
                        break;
                    continue_tag:
                        continue;
                }
                level_decrease();
                inter->global_list = stored;
                break;
            }
            case CONTINUE_STATEMENT:
                result.type = CONTINUE_STATEMENT;
                break;
            case BREAK_STATEMENT:
                result.type = BREAK_STATEMENT;
                break;
            case IF_STATEMENT:
            {
                result.type = IF_STATEMENT;
                level_increase();
                StatementResult r;
                if (value_to_bool(&(NB_Value*){eval(inter->global_list->s->content.if_statement.exp)})->value.int_value)
                {
                    StatementList *stored = inter->global_list;
                    inter->global_list = inter->global_list->s->content.if_statement.block->content.block_statement.slist;
                    for (;inter->global_list->prev != NULL; inter->global_list = inter->global_list->prev);
                    r.type = NULL_RESULT;
                    do {
                        if (r.type == EXPRESSION_STATEMENT)
                            value_delete(&(r.value));
                        if (r.type == BREAK_STATEMENT)
                        {
                            result.type = BREAK_STATEMENT;
                            level_decrease();
                            return result;
                        }
                        if (r.type == CONTINUE_STATEMENT)
                        {
                            result.type = CONTINUE_STATEMENT;
                            level_decrease();
                            return result;
                        }
                        r = nb_interpret_once();
                    } while(r.type != NULL_RESULT);
                    inter->global_list = stored;
                }
                else
                {
                    ElseIfList *elseif_list = inter->global_list->s->content.if_statement.elseif_list;
                    if (elseif_list != NULL)
                    {
                        for (;elseif_list->prev != NULL; elseif_list = elseif_list->prev);
                        for (;elseif_list != NULL; elseif_list = elseif_list->next)
                        {
                            if (value_to_bool(&(NB_Value*){eval(elseif_list->exp)})->value.int_value)
                            {
                                StatementList *stored = inter->global_list;
                                inter->global_list = elseif_list->block->content.block_statement.slist;
                                for (;inter->global_list->prev != NULL; inter->global_list = inter->global_list->prev);
                                r.type = NULL_RESULT;
                                do {
                                    if (r.type == EXPRESSION_STATEMENT)
                                        value_delete(&(r.value));
                                    if (r.type == BREAK_STATEMENT)
                                    {
                                        result.type = BREAK_STATEMENT;
                                        level_decrease();
                                        return result;
                                    }
                                    if (r.type == CONTINUE_STATEMENT)
                                    {
                                        result.type = CONTINUE_STATEMENT;
                                        level_decrease();
                                        return result;
                                    }
                                    r = nb_interpret_once();
                                } while(r.type != NULL_RESULT);
                                inter->global_list = stored;
                                goto if_out;
                            }
                        }
                    }
                    if (inter->global_list->s->content.if_statement.else_block != NULL)
                    {
                        StatementList *stored = inter->global_list;
                        inter->global_list = inter->global_list->s->content.if_statement.else_block->content.block_statement.slist;
                        for (;inter->global_list->prev != NULL; inter->global_list = inter->global_list->prev);
                        r.type = NULL_RESULT;
                        do {
                            if (r.type == EXPRESSION_STATEMENT)
                                value_delete(&(r.value));
                            if (r.type == BREAK_STATEMENT)
                            {
                                result.type = BREAK_STATEMENT;
                                level_decrease();
                                return result;
                            }
                            if (r.type == CONTINUE_STATEMENT)
                            {
                                result.type = CONTINUE_STATEMENT;
                                level_decrease();
                                return result;
                            }
                            r = nb_interpret_once();
                        } while(r.type != NULL_RESULT);
                        inter->global_list = stored;
                        goto if_out;
                    }
                }
                if_out:
                level_decrease();
                break;
            }
        }
        inter->global_list = inter->global_list->next;
    }
    else
       result.type = NULL_RESULT;
    return result;
}

void level_increase()
{
    inter->level++;
}

void level_decrease()
{
    VariablesList *vlist = inter->variables_list, *prev, *next;
    while (vlist != NULL)
    {
        if (vlist->level == inter->level)
        {
            utf8_string_delete(&(vlist->identifier));
            value_delete(&(vlist->value));
            next = vlist->next;
            prev = vlist->prev;
            __free(vlist);
            if (next != NULL)
                next->prev = prev;
            if (prev == NULL)
                break;
            else
                prev->next = next;
            vlist = prev;
        }
        else
        {
            if (vlist->prev == NULL)
                break;
            else
                vlist = vlist->prev;
        }
    }
    for (;vlist->next != NULL; vlist = vlist->next);
    inter->variables_list = vlist;
    inter->level--;
}

void nb_interpreter_init()
{
    inter->global_list = inter->global_list->next;
    __free(inter->global_list->prev);
    for (;inter->global_list->prev != NULL; inter->global_list = inter->global_list->prev);    
}

NB_Interpreter *nb_interpreter_new()
{
    NB_Interpreter *inter = (NB_Interpreter*)malloc(sizeof(NB_Interpreter));
    inter->current_line = 1;
    inter->level = 0;
    // inter->temp_slist = (StatementList**)malloc(50 * sizeof(StatementList*));
    inter->variables_list = NULL;
    // inter->function_vstack = stack_init();
}

int nb_interpreter_set(NB_Interpreter *interpreter)
{
    inter = interpreter;
    return 1;
}

NB_Interpreter *nb_get_interpreter()
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

void nb_warning(char *str)
{
    fprintf(stderr, "%s\n", str);
}