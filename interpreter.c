#include "newbie.h"

void free_temp_variables_list(VariablesList *vlist);

void nb_interpret()
{
    StatementResult result;
    StatementsList *saved = inter->statements_list; // save the statements list because after running, the list will be NULL
    result.type = NULL_RESULT;
    do {
        result = nb_interpret_once();
    } while(result.type != NULL_RESULT);
    inter->statements_list = saved;
}

StatementResult nb_interpret_once()
{
    StatementResult result;
    VariablesList *saved_temp_vlist = inter->temp_vlist;
    inter->temp_vlist = NULL;
    if (inter->statements_list != NULL)
    {
        switch (inter->statements_list->s->type)
        {
            case EXPRESSION_STATEMENT:
            {
                result.type = EXPRESSION_STATEMENT;
                result.content.value = eval(inter->statements_list->s->content.expression, &(inter->variables_list));
                break;
            }
            case BLOCK_STATEMENT:
            {
                result.type = BLOCK_STATEMENT;
                StatementsList *saved = inter->statements_list;
                inter->statements_list = inter->statements_list->s->content.block_statement.slist; // change the env
                if (inter->statements_list != NULL)
                    for (;inter->statements_list->prev != NULL; inter->statements_list = inter->statements_list->prev);                
                level_increase();
                nb_interpret();
                level_decrease();
                inter->statements_list = saved;
                break;
            }
            case FOR_STATEMENT:
            {
                #define for_body(num) \
                { \
                    inter->statements_list = this_slist; \
                    r.type = NULL_RESULT; \
                    do { \
                        if (r.type == BREAK_STATEMENT) \
                            goto break_tag##num; \
                        else if (r.type == CONTINUE_STATEMENT) \
                            goto continue_tag##num; \
                        else if (r.type == RETURN_STATEMENT) \
                        { \
                            result.type = RETURN_STATEMENT; \
                            result.content.value = r.content.value; \
                            level_decrease(); \
                            return result; \
                        } \
                        r = nb_interpret_once(); \
                    } while(r.type != NULL_RESULT); \
                    continue; \
                    break_tag##num: \
                        break; \
                    continue_tag##num: \
                        continue; \
                }
                result.type = FOR_STATEMENT;
                StatementsList *saved = inter->statements_list, *this_slist = inter->statements_list->s->content.for_statement.block->content.block_statement.slist;
                if (this_slist != NULL)
                    for (;this_slist->prev != NULL; this_slist = this_slist->prev);
                Statement *s = inter->statements_list->s;
                level_increase();
                if (s->content.for_statement.exp1 != NULL)
                    eval(s->content.for_statement.exp1, &(inter->variables_list));
                StatementResult r;
                if (s->content.for_statement.exp2 != NULL && s->content.for_statement.exp3 != NULL)
                    for (;get_bool_value(eval(s->content.for_statement.exp2, &(inter->variables_list)));eval(s->content.for_statement.exp3, &(inter->variables_list)))
                    for_body(0)
                else if (s->content.for_statement.exp2 == NULL && s->content.for_statement.exp3 != NULL)
                    for (;;eval(s->content.for_statement.exp3, &(inter->variables_list)))
                    for_body(1)
                else if (s->content.for_statement.exp3 == NULL && s->content.for_statement.exp2 != NULL)
                    for (;get_bool_value(eval(s->content.for_statement.exp2, &(inter->variables_list)));)
                    for_body(2)
                else
                    for (;;)
                    for_body(3)
                level_decrease();
                inter->statements_list = saved;
                break;
            }
            case FOREACH_STATEMENT:
            {
                result.type = FOREACH_STATEMENT;
                level_increase();
                StatementsList *this_slist = inter->statements_list->s->content.foreach_statement.block->content.block_statement.slist;
                if (this_slist != NULL)
                    for (;this_slist->prev != NULL; this_slist = this_slist->prev);
                StatementsList *saved = inter->statements_list;
                NB_Value *arr = eval(inter->statements_list->s->content.foreach_statement.exp, &(inter->variables_list));
                // NB_Value *arr = value_new();
                // memcpy(arr, temp_arr, sizeof(NB_Value));
                // inter->val->type = INT;
                // inter->val->value.int_value = 0;
                Expression *temp_exp = nb_create_declaration_expression(ARRAY, inter->statements_list->s->content.foreach_statement.identifier, NULL);
                eval(temp_exp, &(inter->variables_list));
                __free(temp_exp);
                VariablesList *var = inter->variables_list;
                value_delete(&(var->value));
                StatementResult r;
                for (int i = 0; i < array_get_length(arr->value.array_value); i++)
                {
                    var->value = array_get_addr(arr->value.array_value, i);
                    inter->statements_list = this_slist; 
                    r.type = NULL_RESULT; 
                    do { 
                        if (r.type == BREAK_STATEMENT) 
                            goto break_tag; 
                        else if (r.type == CONTINUE_STATEMENT) 
                            goto continue_tag; 
                        else if (r.type == RETURN_STATEMENT) 
                        { 
                            result.type = RETURN_STATEMENT; 
                            result.content.value = r.content.value; 
                            value_delete(&arr);
                            level_decrease(); 
                            return result; 
                        } 
                        r = nb_interpret_once(); 
                    } while(r.type != NULL_RESULT); 
                    continue; 
                    break_tag: 
                        break; 
                    continue_tag:
                        continue;
                }
        
                if (var->prev != NULL)
                    var->prev->next = var->next;
                if (var->next != NULL)
                    var->next->prev = var->prev;
                if (inter->variables_list == var)
                    inter->variables_list = var->prev;
                utf8_string_delete(&(var->identifier));
                __free(var);

                // __free(arr);
                // value_delete(&arr);
                level_decrease();
                inter->statements_list = saved;
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
                #define if_body \
                r.type = NULL_RESULT; \
                do { \
                    if (r.type == BREAK_STATEMENT) \
                    { \
                        result.type = BREAK_STATEMENT; \
                        level_decrease(); \
                        return result; \
                    } \
                    else if (r.type == CONTINUE_STATEMENT) \
                    { \
                        result.type = CONTINUE_STATEMENT; \
                        level_decrease(); \
                        return result; \
                    } \
                    else if (r.type == RETURN_STATEMENT) \
                    { \
                        result.type = RETURN_STATEMENT; \
                        result.content.value = r.content.value;  \
                        level_decrease(); \
                        return result; \
                    }       \
                    r = nb_interpret_once();\
                } while(r.type != NULL_RESULT);
                result.type = IF_STATEMENT;
                level_increase();
                StatementResult r;
                if (get_bool_value(eval(inter->statements_list->s->content.if_statement.exp, &(inter->variables_list))))
                {
                    StatementsList *saved = inter->statements_list;
                    inter->statements_list = inter->statements_list->s->content.if_statement.block->content.block_statement.slist;
                    if (inter->statements_list != NULL)
                        for (;inter->statements_list->prev != NULL; inter->statements_list = inter->statements_list->prev);
                    if_body
                    inter->statements_list = saved;
                }
                else
                {
                    ElseIfList *elseif_list = inter->statements_list->s->content.if_statement.elseif_list;
                    if (elseif_list != NULL)
                    {
                        for (;elseif_list->prev != NULL; elseif_list = elseif_list->prev);
                        for (;elseif_list != NULL; elseif_list = elseif_list->next)
                        {
                            if (get_bool_value(eval(elseif_list->exp, &(inter->variables_list))))
                            {
                                StatementsList *saved = inter->statements_list;
                                inter->statements_list = elseif_list->block->content.block_statement.slist;
                                if (inter->statements_list != NULL)
                                    for (;inter->statements_list->prev != NULL; inter->statements_list = inter->statements_list->prev);
                                if_body
                                inter->statements_list = saved;
                                goto if_out;
                            }
                        }
                    }
                    if (inter->statements_list->s->content.if_statement.else_block != NULL)
                    {
                        StatementsList *saved = inter->statements_list;
                        inter->statements_list = inter->statements_list->s->content.if_statement.else_block->content.block_statement.slist;
                        if (inter->statements_list != NULL)
                            for (;inter->statements_list->prev != NULL; inter->statements_list = inter->statements_list->prev);
                        if_body
                        inter->statements_list = saved;
                        goto if_out;
                    }
                }
                if_out:
                level_decrease();
                break;
            }
            case ELSE_STATEMENT:
                result.type = ELSE_STATEMENT;
                break;
            case FUNCTION_DEFINITION_STATEMENT:
                result.type = FUNCTION_DEFINITION_STATEMENT;
                break;
            case RETURN_STATEMENT:
            {
                result.type = RETURN_STATEMENT;
                result.content.value = eval(inter->statements_list->s->content.expression, &(inter->variables_list));
                break;
            }
        }
        inter->statements_list = inter->statements_list->next;
    }
    else
        result.type = NULL_RESULT;
    free_temp_variables_list(inter->temp_vlist);
    inter->temp_vlist = saved_temp_vlist;
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
    if (vlist != NULL)
        for (;vlist->next != NULL; vlist = vlist->next);
    inter->variables_list = vlist;
    inter->level--;
}

NB_Interpreter *nb_interpreter_new()
{
    NB_Interpreter *i = (NB_Interpreter*)malloc(sizeof(NB_Interpreter));
    i->current_line = 1;
    i->level = 0;
    i->block_state = 0;
    i->variables_list = NULL;
    i->func_list = NULL;
    i->class_list = NULL;
    i->handle_list = NULL;
    i->temp_vlist = NULL;
    return i;
}

void nb_interpreter_init()
{
    StatementsList *saved = inter->statements_list->next;
    __free(inter->statements_list->s);
    __free(inter->statements_list);
    inter->statements_list = saved;
    if (inter->statements_list != NULL)
    {
        inter->statements_list->prev = NULL;
        for (;inter->statements_list->prev != NULL; inter->statements_list = inter->statements_list->prev);    
    }
    else
    {
        fprintf(stderr, "No Any Statement!");
        exit(1);
    }

    FILE *setting = fopen("NewBie.ini", "r");
    void (*add_lib)(FunctionList **flist, void (*add_func)(FunctionList **flist, int pnum, NB_Value *(*ptr)(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier)), UTF8_String *identifier, NB_ValueType type, char **pname_array, NB_ValueType *ptype), void (*add_val)(NB_Value *val, UTF8_String *identifier));
    char *lib_name = (char*)malloc(30 * sizeof(char));
    fgets(lib_name, 30, setting);
    while (lib_name[0] != '\0')
    {
        for (int i = 0; i < strlen(lib_name); i++)
        {
            if (lib_name[i] == '\n')
            {
                lib_name[i] = '\0';
                break;
            }
        }

        void *handle = dlopen(lib_name, RTLD_NOW);
        if (handle == NULL)
            fprintf(stderr, "%s\n", dlerror());
        else
        {
            add_lib = dlsym(handle, "add_lib");
            add_lib(&(inter->func_list), nb_add_builtin_func, nb_add_global_variable);
            if (inter->handle_list == NULL)
            {
                inter->handle_list = (HandleList*)malloc(sizeof(HandleList));
                inter->handle_list->next = NULL;
                inter->handle_list->handle = handle;
            }
            else
            {
                HandleList *temp_hlist = inter->handle_list;
                for (;;temp_hlist = temp_hlist->next)
                    if (temp_hlist->next == NULL)
                        break;
                temp_hlist->next = (HandleList*)malloc(sizeof(HandleList));
                temp_hlist->next->next = NULL;
                temp_hlist->next->handle = handle;
            }
        }
        lib_name[0] = '\0';
        fgets(lib_name, 30, setting);    
    }
    __free(lib_name);
    fclose(setting);

    inter->global_slist = inter->statements_list;
}

int nb_interpreter_set(NB_Interpreter *interpreter)
{
    inter = interpreter;
    return 1;
}

void free_expression_func(Expression *exp);
#define free_expression(exp) do {free_expression_func(exp); exp = NULL;}while(0)
void free_statement_func(Statement *s);
#define free_statement(s) do {free_statement_func(s); s = NULL;}while(0)
void free_statements_list_func(StatementsList *slist);
#define free_statements_list(slist) do {free_statements_list_func(slist); slist = NULL;}while(0)
void free_arguments_list_func(ArgumentsList *alist);
#define free_arguments_list(alist) do {free_arguments_list_func(alist); alist = NULL;}while(0)
void free_parameters_list_func(ParametersList *plist);
#define free_parameters_list(plist) do {free_parameters_list_func(plist); plist = NULL;}while(0)
void free_elseif_list_func(ElseIfList *elist);
#define free_elseif_list(elist) do {free_elseif_list_func(elist); elist = NULL;}while(0)
void free_expression_list_func(ExpressionList *elist);
#define free_expression_list(elist) do {free_expression_list_func(elist); elist = NULL;}while(0)

void nb_clean()
{    
    free_statements_list(inter->global_slist);

    level_decrease();

    FunctionList *saved_flist;    
    while (inter->func_list != NULL)
    {
        if (!(inter->func_list->builtin))
        {
            saved_flist = inter->func_list->prev;
            free_statement(inter->func_list->block);
            free_parameters_list(inter->func_list->plist);
            utf8_string_delete(&(inter->func_list->identifier));
            __free(inter->func_list);
            inter->func_list = saved_flist;
        }
        else
        {
            saved_flist = inter->func_list->prev;
            free_parameters_list(inter->func_list->plist);
            utf8_string_delete(&(inter->func_list->identifier));
            __free(inter->func_list);
            inter->func_list = saved_flist;
        }
    }

    HandleList *saved_hlist;
    while (inter->handle_list != NULL)
    {
        saved_hlist = inter->handle_list->next;
        dlclose(inter->handle_list->handle);
        __free(inter->handle_list);
        inter->handle_list = saved_hlist;
    }

    // value_delete(&(inter->val));
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

void nb_add_builtin_func(FunctionList **flist, int pnum, NB_Value *(*ptr)(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier)), UTF8_String *identifier, NB_ValueType type, char **pname_array, NB_ValueType *ptype)
{
    ParametersList *plist = NULL;
    if (pnum > 0)
    {
        plist = nb_create_parameter_list(nb_create_declaration_expression(ptype[0], utf8_string_new_wrap(pname_array[0]), NULL));
        for (int i = 1; i < pnum; i++)
        {
            plist = nb_cat_parameter_list(plist, nb_create_declaration_expression(ptype[i], utf8_string_new_wrap(pname_array[i]), NULL));
        }
        for (;plist->prev != NULL; plist = plist->prev);
    }

    if ((*flist) == NULL)
    {
        (*flist) = (FunctionList*)malloc(sizeof(FunctionList));
        (*flist)->prev = NULL;
        (*flist)->next = NULL;
        (*flist)->pnum = pnum;
        (*flist)->builtin = 1;
        (*flist)->identifier = identifier;
        (*flist)->type = type;
        (*flist)->plist = plist;
        (*flist)->block = NULL;
        (*flist)->builtin_ptr = ptr;
    }
    else
    {
        (*flist)->next = (FunctionList*)malloc(sizeof(FunctionList));
        (*flist)->next->prev = (*flist);
        (*flist) = (*flist)->next;
        (*flist)->next = NULL;
        (*flist)->pnum = pnum;
        (*flist)->builtin = 1;
        (*flist)->identifier = identifier;
        (*flist)->type = type;
        (*flist)->plist = plist;
        (*flist)->block = NULL;
        (*flist)->builtin_ptr = ptr;
    }
}

void nb_add_global_variable(NB_Value *val, UTF8_String *identifier)
{
    if (inter->variables_list == NULL)
    {
        inter->variables_list = (VariablesList*)malloc(sizeof(VariablesList));
        inter->variables_list->prev = NULL;
        inter->variables_list->next = NULL;
        inter->variables_list->identifier = identifier;
        inter->variables_list->level = 0;
        inter->variables_list->value = val;
    }
    else
    {
        inter->variables_list->next = (VariablesList*)malloc(sizeof(VariablesList));
        inter->variables_list->next->prev = inter->variables_list;
        inter->variables_list = inter->variables_list->next;
        inter->variables_list->next = NULL;
        inter->variables_list->identifier = identifier;
        inter->variables_list->level = 0;
        inter->variables_list->value = val;
    }
}

void free_expression_func(Expression *exp)
{
    switch (exp->type)
    {
        case LITERAL_EXPRESSION:
            switch (exp->content.literal_expression.type)
            {
                case STRING:
                    utf32_string_delete(&(exp->content.literal_expression.value.string_value));
                    break;
                case ARRAY:
                    array_delete(&(exp->content.literal_expression.value.array_value));
                    break;
            }
            break;
        case IDENTIFIER_EXPRESSION:
            utf8_string_delete(&(exp->content.identifier_expression));
            break;
        case ASSIGNMENT_EXPRESSION:
            free_expression(exp->content.assignment_expression.lval);
            free_expression(exp->content.assignment_expression.rval);
            break;
        case DECLARATION_EXPRESSION:
            if (exp->content.declaration_expression.exp != NULL)
                free_expression(exp->content.declaration_expression.exp);
            else
                utf8_string_delete(&(exp->content.declaration_expression.identifier));
            break;
        case BINARY_EXPRESSION:
            if (!(exp->ref))
                free_expression(exp->content.binary_expression.first);
            free_expression(exp->content.binary_expression.second);
            break;
        case UNARY_EXPRESSION:
            free_expression(exp->content.unary_expression.exp);
            break;
        case FUNCTION_CALL_EXPRESSION:
            utf8_string_delete(&(exp->content.function_call_expression.identifier));
            free_arguments_list(exp->content.function_call_expression.alist);
            break;
        case ARRAY_EXPRESSION:
            free_expression_list(exp->content.expression_list);
            break;
        case INDEX_EXPRESSION:
            free_expression(exp->content.index_expression.exp);
            free_expression(exp->content.index_expression.index);
            break;
    }
    __free(exp);
}

void free_expression_list_func(ExpressionList *elist)
{
    ExpressionList *saved;
    while (elist != NULL)
    {
        saved = elist->next;
        free_expression(elist->exp);
        __free(elist);
        elist = saved;
    }
}

void free_statement_func(Statement *s)
{
    switch (s->type)
    {
        case EXPRESSION_STATEMENT:
            free_expression(s->content.expression);
            break;
        case BLOCK_STATEMENT:
            free_statements_list(s->content.block_statement.slist);
            break;
        case IF_STATEMENT:
            free_statement(s->content.if_statement.block);
            free_expression(s->content.if_statement.exp);
            if (s->content.if_statement.else_block != NULL)
                free_statement(s->content.if_statement.else_block);
            free_elseif_list(s->content.if_statement.elseif_list);
            break;
        case FOR_STATEMENT:
            free_statement(s->content.for_statement.block);
            if (s->content.for_statement.exp1 != NULL)
                free_expression(s->content.for_statement.exp1);
            if (s->content.for_statement.exp2 != NULL)
                free_expression(s->content.for_statement.exp2);
            if (s->content.for_statement.exp3 != NULL)
                free_expression(s->content.for_statement.exp3);
            break;
        case FOREACH_STATEMENT:
            free_statement(s->content.foreach_statement.block);
            free_expression(s->content.foreach_statement.exp);
            utf8_string_delete(&(s->content.foreach_statement.identifier));
            break;
        case RETURN_STATEMENT:
            free_expression(s->content.expression);
            break;
    }
    __free(s);
}

void free_statements_list_func(StatementsList *slist) // StatementsList usually in the last node
{
    StatementsList *saved;    
    if (slist != NULL)
    {
        if (slist->prev == NULL)
        {
            while (slist != NULL)
            {
                saved = slist->next;
                free_statement(slist->s);
                __free(slist);
                slist = saved;
            }
        }
        else
        {
            for (;slist->next != NULL; slist = slist->next);
            while (slist != NULL)
            {
                saved = slist->prev;
                free_statement(slist->s);
                __free(slist);
                slist = saved;
            }
        }
    }
}

void free_temp_variables_list(VariablesList *vlist)
{
    VariablesList *saved;
    while (vlist != NULL)
    {
        saved = vlist->prev;
        value_delete(&(vlist->value));
        __free(vlist);
        vlist = saved;
    }
}

void free_arguments_list_func(ArgumentsList *alist) // after running, the arguments list will be the last node
{
    ArgumentsList *saved;
    if (alist != NULL)
    {
        for (;alist->next != NULL; alist = alist->next);
        while (alist != NULL)
        {
            saved = alist->prev;
            free_expression(alist->exp);
            __free(alist);
            alist = saved;
        }
    }
}

void free_parameters_list_func(ParametersList *plist) // after running, the parameters list will be the first node
{
    ParametersList *saved;
    if (plist != NULL)
    {
        for (;plist->prev != NULL; plist = plist->prev);
        while (plist != NULL)
        {
            saved = plist->next;
            free_expression(plist->exp);
            __free(plist);
            plist = saved;
        }
    }
}

void free_elseif_list_func(ElseIfList *elist)
{
    ElseIfList *saved;
    if (elist != NULL)
    {
        for (;elist->next != NULL; elist = elist->next);
        while (elist != NULL)
        {
            saved = elist->prev;
            free_expression(elist->exp);
            free_statement(elist->block);
            __free(elist);
            elist = saved;
        }
    }
}