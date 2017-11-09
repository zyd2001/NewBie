#include "newbie.h"

#define bool_check(operator)\
do {\
    new->type = BOOL;\
    if (first->type == STRING || second->type == STRING)\
    {\
        UTF32_String *str_1 = get_string_value(first);\
        UTF32_String *str_2 = get_string_value(second);\
        new->value.int_value = utf32_string_compare_utf32(str_1, str_2) operator 0 ? 1 : 0;\
        utf32_string_delete(&str_1, &str_2); \
    }\
    else if (first->type == DOUBLE || second->type == DOUBLE)\
    {\
        double double_1 = get_double_value(first);\
        double double_2 = get_double_value(second);\
        new->value.int_value = double_1 operator double_2;\
    }\
    else\
    {\
        new->value.int_value = first->value.int_value operator second->value.int_value;\
    }\
} while(0)

#define compute(operator) \
do { \
    if (first->type == STRING) \
    { \
    } \
    else if (first->type == DOUBLE || second->type == DOUBLE) \
    { \
        new->type = DOUBLE; \
        double double_1 = get_double_value(first); \
        double double_2 = get_double_value(second); \
        new->value.double_value = double_1 operator double_2;\
    } \
    else \
    { \
        new->type = INT; \
        new->value.int_value = first->value.int_value operator second->value.int_value; \
    } \
} while(0)

#define nb_value_change_type(value, t) \
do { \
    switch (t)\
    { \
        case INT: \
            if (value->type == STRING) \
            { \
                nb_error("Type Cast Error!"); \
                exit(1); \
            } \
            value_to_int(&value); \
            break; \
        case DOUBLE: \
            if (value->type == STRING) \
            { \
                nb_error("Type Cast Error!"); \
                exit(1); \
            } \
            value_to_double(&value); \
            break; \
        case BOOL: \
            if (value->type == STRING) \
            { \
                nb_error("Type Cast Error!"); \
                exit(1); \
            } \
            value_to_bool(&value); \
            break; \
        case STRING: \
            value_to_string(&value); \
            break; \
        case ARRAY: \
            break; \
    } \
} while(0)

#define vlist_move_to_next(vlist) \
do { \
    if (vlist != NULL) \
    { \
        vlist->next = (VariablesList*)malloc(sizeof(VariablesList)); \
        vlist->next->prev = vlist; \
        vlist = vlist->next; \
        vlist->next = NULL; \
        vlist->value = value_new(); \
        vlist->identifier = NULL; \
    } \
    else \
    { \
        vlist = (VariablesList*)malloc(sizeof(VariablesList)); \
        vlist->prev = NULL; \
        vlist->next = NULL; \
        vlist->value = value_new(); \
        vlist->identifier = NULL; \
    } \
} while(0)

VariablesList *find_in_list(VariablesList *vlist, UTF8_String *str);
VariablesList *find_in_list_func(VariablesList *vlist, UTF8_String *str);
NB_Value *find_in_list_value(VariablesList *vlist, char *str);

NB_Value *eval(Expression *exp, VariablesList **vlist)
{
    NB_Value *ret;
    switch (exp->type)
    {
        case LITERAL_EXPRESSION:
        {
            ret = &(exp->content.literal_expression);
            break;
        }
        case IDENTIFIER_EXPRESSION:
        {
            NB_Value *val = find_in_list((*vlist), exp->content.identifier_expression)->value;
            if (val)
                ret = val;
            else
            {
                nb_error("Undefined Variable!");
                exit(1);
            }
            break;
        }
        case ASSIGNMENT_EXPRESSION:
        {
            NB_Value *rval = eval(exp->content.assignment_expression.rval, vlist);
            NB_Value *temp_rval = value_copy_new(rval);
            NB_Value *lval = eval(exp->content.assignment_expression.lval, vlist);
            if (lval->type != rval->type && !lval->various)
            {
                nb_value_change_type(temp_rval, lval->type);
            }
            value_copy(lval, temp_rval);
            value_delete(&temp_rval);
            // VariablesList *found;
            // if (exp->content.assignment_expression.lval->type == IDENTIFIER_EXPRESSION)
            // {
            //     found = find_in_list((*vlist), exp->content.assignment_expression.lval->content.identifier_expression);
            //     if (found->value->type != rval->type && !found->value->various)
            //         nb_value_change_type(rval, found->value->type);
            //     value_copy(found->value, rval);
            //     value_copy(ret, rval);
            // }
            // else if (exp->content.assignment_expression.lval->type == INDEX_EXPRESSION)
            // {   
            //     NB_Value *val = eval(exp->content.assignment_expression.lval, vlist);
            //     if (val->type == ARRAY)
            //     {
                    
            //     }
            //     // {
            //     //     if (rval->type == STRING && utf32_string_get_length(rval->value.string_value) == 1)
            //     //     {
            //     //         char *str1 = utf32_string_get_value(val->value.string_value);
            //     //         char *str2 = utf32_string_get_value(rval->value.string_value);
            //     //         memcpy(str1 + i, str2, 4);
            //     //     }
            //     //     else
            //     //     {
            //     //         nb_error("length more");
            //     //         exit(1);
            //     //     }
            //     // }
            //     // else if (val->type == ARRAY)
            //     // {
            //     //     NB_Value *temp_val = array_get_addr(val->value.array_value, i);
            //     //     memcpy(temp_val, rval, sizeof(Value));
            //     // }
            //     // value_copy(ret, rval);                
            // }
            // else
            // {
            //     nb_error("wrong lvalue");
            //     exit(1);
            // }
            ret = NULL;
            break;
        }
        case DECLARATION_EXPRESSION:
        {
            ret = NULL;
            UTF8_String *identifier = exp->content.declaration_expression.identifier ? exp->content. \
                declaration_expression.identifier : exp->content.declaration_expression.exp-> \
                content.assignment_expression.lval->content.identifier_expression;
            VariablesList *found = find_in_list_func((*vlist), identifier);
            if (found)
            {
                nb_error("Duplicated Declaration!");
                exit(1);
            }
            if ((*vlist))
            { 
                (*vlist)->next = (VariablesList*)malloc(sizeof(VariablesList));
                (*vlist)->next->prev = (*vlist);
                (*vlist) = (*vlist)->next;
                (*vlist)->next = NULL;
                (*vlist)->level = inter->level;
                (*vlist)->identifier = utf8_string_copy_new(identifier);
                (*vlist)->value = value_new_type(exp->content.declaration_expression.type);
                (*vlist)->value->various = (*vlist)->value->type == VARIOUS ? 1 : 0;
                if (exp->content.declaration_expression.exp)
                    eval(exp->content.declaration_expression.exp, vlist);
            }
            else
            {
                (*vlist) = (VariablesList*)malloc(sizeof(VariablesList));
                (*vlist)->prev = NULL;
                (*vlist)->next = NULL;
                (*vlist)->level = inter->level;
                (*vlist)->identifier = utf8_string_copy_new(identifier);
                (*vlist)->value = value_new_type(exp->content.declaration_expression.type);
                (*vlist)->value->various = (*vlist)->value->type == VARIOUS ? 1 : 0;
                if (exp->content.declaration_expression.exp)
                    eval(exp->content.declaration_expression.exp, vlist);
            }
            break;
        }
        case BINARY_EXPRESSION:
        {
            NB_Value *first = value_new(), *second = value_new();
            NB_Value *temp_val1 = eval(exp->content.binary_expression.first, vlist);
            NB_Value *temp_val2 = eval(exp->content.binary_expression.second, vlist);
            value_copy(first, temp_val1);
            value_copy(second, temp_val2);
            NB_Value *new = value_new();
            switch (exp->content.binary_expression.type)
            {
                case ADD:
                {
                    if (first->type == STRING || second->type == STRING)
                    {
                        new->type = STRING;
                        UTF32_String *str_1 = get_string_value(first);
                        UTF32_String *str_2 = get_string_value(second);
                        utf32_string_append_utf32(str_1, str_2);
                        new->value.string_value = utf32_string_copy_new(str_1);
                        utf32_string_delete(&str_1, &str_2);
                    }
                    else if (first->type == DOUBLE || second->type == DOUBLE)
                    {
                        new->type = DOUBLE;
                        double double_1 = get_double_value(first);
                        double double_2 = get_double_value(second);
                        new->value.double_value = double_1 + double_2;
                    }
                    else
                    {
                        new->type = INT;
                        new->value.int_value = first->value.int_value + second->value.int_value;
                    }
                    break;
                }
                case SUB:
                    compute(-);
                    break;
                case MUL:
                    compute(*);
                    break;
                case DIV:
                    compute(/);
                    break;
                case MOD:
                {
                    if (first->type == STRING)
                    {
                    }
                    else if (first->type == DOUBLE || second->type == DOUBLE)
                    {
                        // ret->type = DOUBLE;
                        // double double_1 = get_double_value(first);
                        // double double_2 = get_double_value(second);
                        // ret->value.double_value = double_1 % double_2;
                    }
                    else
                    {
                        new->type = INT;
                        new->value.int_value = first->value.int_value % second->value.int_value;
                    }
                    break;
                }
                case EQ:
                    bool_check(==);
                    break;
                case NE:
                    bool_check(!=);
                    break;
                case GT:
                    bool_check(>);
                    break;
                case GE:
                    bool_check(>=);
                    break;
                case LT:
                    bool_check(<);
                    break;
                case LE:
                    bool_check(<=);
                    break;
                case AND:
                {
                    value_to_bool(&first);
                    value_to_bool(&second);
                    new->type = BOOL;
                    new->value.int_value = first->value.int_value && second->value.int_value;
                    break;
                }
                case OR:
                {
                    value_to_bool(&first);
                    value_to_bool(&second);
                    new->type = BOOL;
                    new->value.int_value = first->value.int_value || second->value.int_value;
                    break;
                }
            }
            vlist_move_to_next(inter->temp_vlist);
            value_copy(inter->temp_vlist->value, new);
            ret = inter->temp_vlist->value;
            value_delete(&new, &first, &second);
            break;
        }
        case UNARY_EXPRESSION:
        {
            switch (exp->content.unary_expression.type)
            {
                case MINUS:
                {
                    vlist_move_to_next(inter->temp_vlist);
                    ret = inter->temp_vlist->value;
                    NB_Value *val = eval(exp->content.unary_expression.exp, vlist);
                    value_copy(ret, val);
                    switch (val->type)
                    {
                        case INT:
                        {
                            ret->value.int_value = -(ret->value.int_value);
                            break;
                        }
                        case DOUBLE:
                        {
                            ret->value.double_value = -(ret->value.double_value);
                            break;
                        }
                        case BOOL:
                        case STRING:
                        case ARRAY:
                        {
                            nb_error("Type Error!");
                            exit(1);
                        }
                    }
                    break;
                }
                case NOT:
                {
                    vlist_move_to_next(inter->temp_vlist);            
                    ret = inter->temp_vlist->value;
                    NB_Value *val = eval(exp->content.unary_expression.exp, vlist);                    
                    value_copy(ret, val);
                    switch (val->type)      
                    {
                        case BOOL:
                        {
                            ret->value.int_value = !(ret->value.int_value);
                            break;
                        }
                        default:
                        {
                            nb_error("Type Error!");
                            exit(1);
                        }
                    }
                    break;
                }
                case INCREMENT:
                {
                    NB_Value *val = eval(exp->content.unary_expression.exp, vlist);
                    switch (val->type)
                    {
                        case INT:
                            val->value.int_value++;
                            break;
                        case DOUBLE:
                            val->value.double_value++;
                            break;
                        default:
                        {
                            nb_error("Type Error!");
                            exit(1);
                        }
                    }
                    ret = val;
                    break;
                }
                case DECREMENT:
                {
                    NB_Value *val = eval(exp->content.unary_expression.exp, vlist);                    
                    switch (val->type)
                    {
                        case INT:
                            val->value.int_value--;
                            break;
                        case DOUBLE:
                            val->value.double_value--;
                            break;
                        default:
                        {
                            nb_error("Type Error!");
                            exit(1);
                        }
                    }
                    ret = val;
                    break;
                }
            }
            break;
        }
        case ARRAY_EXPRESSION:
        {
            NB_Value *new = value_new_type(ARRAY), *temp;
            ExpressionList *elist = exp->content.expression_list;
            for (;elist != NULL; elist = elist->next)
            {
                temp = eval(elist->exp, vlist);
                temp->various = 1;
                array_push(new->value.array_value, temp);
            }
            vlist_move_to_next(inter->temp_vlist);
            value_copy(inter->temp_vlist->value, new);
            value_delete(&new);
            ret = inter->temp_vlist->value;
            break;
        }
        case INDEX_EXPRESSION:
        {
            NB_Value *val = eval(exp->content.index_expression.exp, vlist);
            NB_Value *index = eval(exp->content.index_expression.index, vlist);
            int i = get_int_value(index);
            if (val->type == STRING)
            {
                NB_Value *new = value_new();
                new->type = STRING;
                new->value.string_value = utf32_string_substr(val->value.string_value, i, 1);
                vlist_move_to_next(inter->temp_vlist);
                value_copy(inter->temp_vlist->value, new);
                value_delete(&new);
                ret = inter->temp_vlist->value;
            }
            else if (val->type == ARRAY)
                ret = array_get_addr(val->value.array_value, i);
            else
            {
                nb_error("type error");
                exit(1);
            }
            break;
        }
        case FUNCTION_CALL_EXPRESSION:
        {
            NB_Value *v = find_in_list_value((*vlist), utf8_string_get_value(exp->content.function_call_expression.identifier));
            if (v->type != FUNCTION)
            {
                nb_error("Not a function!");
                exit(1);
            }
            FunctionList *func = (FunctionList*)(v->value.other);
            int count = 1;
            if (exp->content.function_call_expression.alist == NULL)
                count = 0;
            else
                for (;exp->content.function_call_expression.alist->prev != NULL; exp->content.function_call_expression.alist = exp->content.function_call_expression.alist->prev)
                    count++;
            if (count > func->pnum)
            {
                nb_error("Argument Number Doesn't Match!");
                exit(1);
            }

            level_increase();
            StatementsList *saved_slist = inter->statements_list;
            VariablesList *saved_vlist = NULL;
            VariablesList *new_vlist = NULL;

            ArgumentsList *alist_temp = exp->content.function_call_expression.alist;
            for (ParametersList *plist_temp = func->plist; plist_temp != NULL; plist_temp = plist_temp->next) // initialize local variables // do not modifiy the original list beacuse we may use it more than once
            {
                if (alist_temp != NULL && plist_temp->exp->content.declaration_expression.exp != NULL)
                {
                    eval(plist_temp->exp, &new_vlist);
                    NB_Value *t = eval(alist_temp->exp, vlist);
                    Expression *exp_temp = nb_create_assignment_expression(plist_temp->exp->content.declaration_expression.exp->content.assignment_expression.lval, &(Expression){LITERAL_EXPRESSION, 0, *t});
                    eval(exp_temp, &new_vlist);
                    __free(exp_temp);
                }
                else if (plist_temp->exp->content.declaration_expression.exp != NULL)
                    eval(plist_temp->exp, &new_vlist);
                else if (alist_temp != NULL)
                {
                    eval(plist_temp->exp, &new_vlist);
                    NB_Value *t = eval(alist_temp->exp, vlist);
                    Expression *exp_temp = nb_create_assignment_expression(nb_create_identifier_expression(plist_temp->exp->content.declaration_expression.identifier), &(Expression){LITERAL_EXPRESSION, 0, *t});
                    eval(exp_temp, &new_vlist);
                    __free(exp_temp->content.assignment_expression.lval);
                    __free(exp_temp);
                }
                else
                {
                    nb_error("Argument Number Doesn't Match!");
                    exit(1);
                }
                if (alist_temp != NULL) 
                    alist_temp = alist_temp->next;
            }
            if (new_vlist != NULL)
                for (;new_vlist->prev != NULL; new_vlist = new_vlist->prev);

            int change_flag = 1;
            for (;(*vlist) != NULL; (*vlist) = (*vlist)->prev) // go to the global env
            {
                if ((*vlist)->level != 0)
                    continue;
                else
                {
                    change_flag = 0;
                    saved_vlist = (*vlist)->next;
                    (*vlist)->next = new_vlist;
                    if (new_vlist != NULL)
                        new_vlist->prev = (*vlist);
                    break;
                }
            }
            if (change_flag)
                (*vlist) = new_vlist;
            if ((*vlist) != NULL)
                for (;(*vlist)->next != NULL; (*vlist) = (*vlist)->next);
            // (*vlist) = modified_vlist;            

            if (!func->builtin)
            {
                inter->statements_list = func->block->content.block_statement.slist;
                if (inter->statements_list != NULL)
                    for (;inter->statements_list->prev != NULL; inter->statements_list = inter->statements_list->prev);
                StatementResult r;
                r.type = NULL_RESULT;
                do {
                    if (r.type == RETURN_STATEMENT)
                    {
                        vlist_move_to_next(inter->temp_vlist);
                        value_copy(inter->temp_vlist->value, r.content.value);
                        ret = inter->temp_vlist->value;
                        if (func->type != VARIOUS)
                            nb_value_change_type(ret, func->type);
                        break;
                    }
                    r = nb_interpret_once();
                } while(r.type != NULL_RESULT);
                inter->statements_list = saved_slist;
            }
            
            /* temporary */
            else
            {
                NB_Value *val = func->builtin_ptr((*vlist), find_in_list_value);
                vlist_move_to_next(inter->temp_vlist);
                value_copy(inter->temp_vlist->value, val);
                ret = inter->temp_vlist->value;
                value_delete(&val);
            }

            level_decrease();
            if ((*vlist) != NULL)
            {
                (*vlist)->next = saved_vlist;
                for (;(*vlist)->next != NULL; (*vlist) = (*vlist)->next);
            }
            else
                (*vlist) = saved_vlist;
            break;
        }
    }
    return ret;
}

// void eval(Expression *exp, VariablesList **vlist)
// {
//     NB_Value *val = eval(exp, vlist);
//     value_delete(&val);
// }

VariablesList *find_in_list_func(VariablesList *vlist, UTF8_String *str)
{
    // VariablesList *saved = vlist;
    for (;vlist != NULL; vlist = vlist->prev)
    {
        if (!utf8_string_compare(str, vlist->identifier))
            return vlist;
    }
    // vlist = saved;
    // for (;vlist != NULL; vlist = vlist->next)
    // {
    //     if (!utf8_string_compare(str, vlist->identifier))
    //         return vlist;
    // }
    return NULL;
}

VariablesList *find_in_list(VariablesList *vlist, UTF8_String *str)
{
    VariablesList *found = find_in_list_func(vlist, str);
    if (!found)
    {
        nb_error("Undefined Variable!");
        exit(1);    
    }
    else
        return found;
}

NB_Value *find_in_list_value(VariablesList *vlist, char *str)
{
    for (;vlist != NULL; vlist = vlist->prev)
    {
        if (!strcmp(str, utf8_string_get_value(vlist->identifier)))
            return vlist->value;
    }
    if (!vlist)
    {
        nb_error("Undefined Variable!");
        exit(1);    
    }
}