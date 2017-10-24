#include "newbie.h"

#define bool_check(operator)\
do {\
    ret->type = BOOL;\
    if (first->type == STRING || second->type == STRING)\
    {\
        UTF32_String *str_1 = get_string_value(first);\
        UTF32_String *str_2 = get_string_value(second);\
        ret->value.int_value = utf32_string_compare_utf32(str_1, str_2) operator 0 ? 1 : 0;\
    }\
    else if (first->type == DOUBLE || second->type == DOUBLE)\
    {\
        double double_1 = get_double_value(first);\
        double double_2 = get_double_value(second);\
        ret->value.int_value = double_1 operator double_2;\
    }\
    else\
    {\
        ret->value.int_value = first->value.int_value operator second->value.int_value;\
    }\
} while(0)

#define compute(operator) \
do { \
    if (first->type == STRING) \
    { \
    } \
    else if (first->type == DOUBLE || second->type == DOUBLE) \
    { \
        ret->type = DOUBLE; \
        double double_1 = get_double_value(first); \
        double double_2 = get_double_value(second); \
        ret->value.double_value = double_1 operator double_2;\
    } \
    else \
    { \
        ret->type = INT; \
        ret->value.int_value = first->value.int_value operator second->value.int_value; \
    } \
} while(0)

#define nb_value_change_type(value, t) \
do { \
    switch (t)\
    { \
        case INT: \
            if (value->type == STRING) \
            { \
                value_delete(&value, &ret); \
                nb_error("Type Cast Error!"); \
                exit(1); \
            } \
            value_to_int(&value); \
            break; \
        case DOUBLE: \
            if (value->type == STRING) \
            { \
                value_delete(&value, &ret); \
                nb_error("Type Cast Error!"); \
                exit(1); \
            } \
            value_to_double(&value); \
            break; \
        case BOOL: \
            if (value->type == STRING) \
            { \
                value_delete(&value, &ret); \
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

VariablesList *find_in_list(VariablesList *vlist, UTF8_String *str);
VariablesList *find_in_list_func(VariablesList *vlist, UTF8_String *str);

NB_Value *eval(Expression *exp, VariablesList **vlist)
{
    NB_Value *ret = value_new();
    NB_Interpreter *inter = nb_get_interpreter();
    switch (exp->type)
    {
        case LITERAL_EXPRESSION:
        {
            value_copy(ret, &(exp->content.literal_expression));
            break;
        }
        case IDENTIFIER_EXPRESSION:
        {
            NB_Value *val = find_in_list((*vlist), exp->content.identifier_expression)->value;
            if (val)
                value_copy(ret, val);
            else
            {
                value_delete(&ret);
                nb_error("Undefined Variable!");
                exit(1);
            }
            break;
        }
        case ASSIGNMENT_EXPRESSION:
        {
            NB_Value *val = eval(exp->content.assignment_expression.exp, vlist);
            VariablesList *found = find_in_list((*vlist), exp->content.assignment_expression.identifier);
            if (found->value->type != val->type && !found->value->various)
                nb_value_change_type(val, found->value->type);
            value_copy(found->value, val);
            value_copy(ret, val);
            value_delete(&val);
            break;
        }
        case DECLARATION_EXPRESSION:
        {
            ret->type = BOOL;
            ret->value.int_value = 1;
            UTF8_String *identifier = exp->content.declaration_expression.identifier ? exp->content. \
                declaration_expression.identifier : exp->content.declaration_expression.exp-> \
                content.assignment_expression.identifier;
            VariablesList *found = find_in_list_func((*vlist), identifier);
            if (found)
            {
                value_delete(&ret);
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
                    eval_no_ret(exp->content.declaration_expression.exp, vlist);
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
                    eval_no_ret(exp->content.declaration_expression.exp, vlist);
            }
            break;
        }
        case BINARY_EXPRESSION:
        {
            NB_Value *first = eval(exp->content.binary_expression.first, vlist);
            NB_Value *second = eval(exp->content.binary_expression.second, vlist);
            switch (exp->content.binary_expression.type)
            {
                case ADD:
                {
                    if (first->type == STRING || second->type == STRING)
                    {
                        ret->type = STRING;
                        UTF32_String *str_1 = get_string_value(first);
                        UTF32_String *str_2 = get_string_value(second);
                        utf32_string_append_utf32(str_1, str_2);
                        ret->value.string_value = utf32_string_copy_new(str_1);
                        utf32_string_delete(&str_1, &str_2);
                    }
                    else if (first->type == DOUBLE || second->type == DOUBLE)
                    {
                        ret->type = DOUBLE;
                        double double_1 = get_double_value(first);
                        double double_2 = get_double_value(second);
                        ret->value.double_value = double_1 + double_2;
                    }
                    else
                    {
                        ret->type = INT;
                        ret->value.int_value = first->value.int_value + second->value.int_value;
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
                        ret->type = INT;
                        ret->value.int_value = first->value.int_value % second->value.int_value;
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
                    ret->type = BOOL;
                    ret->value.int_value = first->value.int_value && second->value.int_value;
                    break;
                }
                case OR:
                {
                    value_to_bool(&first);
                    value_to_bool(&second);
                    ret->type = BOOL;
                    ret->value.int_value = first->value.int_value || second->value.int_value;
                    break;
                }
            }
            value_delete(&first, &second);
            break;
        }
        case UNARY_EXPRESSION:
        {
            switch (exp->content.unary_expression.type)
            {
                case MINUS:
                {
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
                            value_delete(&val, &ret); 
                            nb_error("Type Error!");
                            exit(1);
                        }
                    }
                    value_delete(&val);
                    break;
                }
                case NOT:
                {
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
                            value_delete(&val, &ret);
                            nb_error("Type Error!");
                            exit(1);
                        }
                    }
                    value_delete(&val);
                    break;
                }
                case INCREMENT:
                {
                    VariablesList *found = find_in_list((*vlist), exp->content.unary_expression.identifier);
                    switch (found->value->type)
                    {
                        case INT:
                            found->value->value.int_value++;
                            break;
                        case DOUBLE:
                            found->value->value.double_value++;
                            break;
                        default:
                        {
                            value_delete(&ret);
                            nb_error("Type Error!");
                            exit(1);
                        }
                    }
                    break;
                }
                case DECREMENT:
                {
                    VariablesList *found = find_in_list((*vlist), exp->content.unary_expression.identifier);
                    switch (found->value->type)
                    {
                        case INT:
                            found->value->value.int_value--;
                            break;
                        case DOUBLE:
                            found->value->value.double_value--;
                            break;
                        default:
                        {
                            value_delete(&ret);
                            nb_error("Type Error!");
                            exit(1);
                        }
                    }
                    break;
                }
            }
            break;
        }
        case FUNCTION_CALL_EXPRESSION:
        {
            FunctionList *func = NULL;
            for (FunctionList *temp = inter->func_list; temp != NULL; temp = temp->prev)
            {
                if (!utf8_string_compare(exp->content.function_call_expression.identifier, temp->identifier))
                    func = temp;
            }
            if (!func)
            {
                value_delete(&ret);
                nb_error("Undefined Function!");
                exit(1);    
            }
            int count = 1;
            if (exp->content.function_call_expression.alist == NULL)
                count = 0;
            else
                for (;exp->content.function_call_expression.alist->prev != NULL; exp->content.function_call_expression.alist = exp->content.function_call_expression.alist->prev)
                    count++;
            if (count > func->pnum)
            {
                value_delete(&ret);
                nb_error("Argument Number Doesn't Match!");
                exit(1);
            }

            level_increase();
            StatementsList *saved_slist = inter->statements_list;
            VariablesList *saved_vlist = NULL;
            VariablesList *modified_vlist = (*vlist);
            int change_flag = 1;
            for (;modified_vlist != NULL; modified_vlist = modified_vlist->prev) // go to the global env
            {
                if (modified_vlist->level != 0)
                    continue;
                else
                {
                    change_flag = 0;
                    saved_vlist = modified_vlist->next;
                    modified_vlist->next = NULL;
                    break;
                }
            }
            if (change_flag)
                modified_vlist = NULL;
            ArgumentsList *alist_temp = exp->content.function_call_expression.alist;
            for (ParametersList *plist_temp = func->plist; plist_temp != NULL; plist_temp = plist_temp->next) // initialize local variables // do not modifiy the original list beacuse we may use it more than once
            {
                if (alist_temp != NULL && plist_temp->exp->content.declaration_expression.exp != NULL)
                {
                    eval_no_ret(plist_temp->exp, &modified_vlist);
                    NB_Value *t = eval(alist_temp->exp, vlist);
                    Expression *exp_temp = nb_create_assignment_expression(plist_temp->exp->content.declaration_expression.exp->content.assignment_expression.identifier, &(Expression){LITERAL_EXPRESSION, *t});
                    eval_no_ret(exp_temp, &modified_vlist);
                    value_delete(&t);
                    __free(exp_temp);
                }
                else if (plist_temp->exp->content.declaration_expression.exp != NULL)
                    eval_no_ret(plist_temp->exp, &modified_vlist);
                else if (alist_temp != NULL)
                {
                    eval_no_ret(plist_temp->exp, &modified_vlist);
                    NB_Value *t = eval(alist_temp->exp, vlist);
                    Expression *exp_temp = nb_create_assignment_expression(plist_temp->exp->content.declaration_expression.identifier, &(Expression){LITERAL_EXPRESSION, *t});
                    eval_no_ret(exp_temp, &modified_vlist);
                    value_delete(&t);
                    __free(exp_temp);
                }
                else
                {
                    value_delete(&ret);
                    nb_error("Argument Number Doesn't Match!");
                    exit(1);
                }
                if (alist_temp != NULL) 
                    alist_temp = alist_temp->next;
            }
            (*vlist) = modified_vlist;            

            if (!func->builtin)
            {
                inter->statements_list = func->block->content.block_statement.slist;
                if (inter->statements_list != NULL)
                    for (;inter->statements_list->prev != NULL; inter->statements_list = inter->statements_list->prev);
                StatementResult r;
                r.type = NULL_RESULT;
                do {
                    if (r.type == EXPRESSION_STATEMENT)
                        value_delete(&(r.content.value));
                    else if (r.type == RETURN_STATEMENT)
                    {
                        value_copy(ret, r.content.value);
                        value_delete(&(r.content.value));
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
                UTF8_String *str = utf8_string_new_wrap("__p1");
                VariablesList *found = find_in_list(inter->variables_list, str);
                func->builtin_ptr(found->value);
                utf8_string_delete(&str);
            }

            level_decrease();
            if ((*vlist) != NULL)
                (*vlist)->next = saved_vlist;
            else
                (*vlist) = saved_vlist;
            break;
        }
    }
    return ret;
}

void eval_no_ret(Expression *exp, VariablesList **vlist)
{
    NB_Value *val = eval(exp, vlist);
    value_delete(&val);
}

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