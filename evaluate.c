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

VariablesList *find_in_list(VariablesList *vlist, UTF8_String *str);
VariablesList *find_in_list_func(VariablesList *vlist, UTF8_String *str);

NB_Value *eval(Expression *exp)
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
            NB_Value *val = find_in_list(inter->variables_list, exp->content.identifier_expression)->value;
            if (val)
                value_copy(ret, val);
            else
            {
                nb_error("Undefined Variable!");
                exit(1);
            }
            break;
        }
        case ASSIGNMENT_EXPRESSION:
        {
            NB_Value *val = eval(exp->content.assignment_expression.exp);
            VariablesList *found = find_in_list(inter->variables_list, exp->content.assignment_expression.identifier);
            if (found->value->type != val->type)
            {
                switch (found->value->type)
                {
                    case INT:
                        if (val->type == STRING)
                        {
                            nb_error("Type Cast Error!");
                            exit(1);
                        }
                        value_to_int(&val);
                        break;
                    case BOOL:
                        if (val->type == STRING)
                        {
                            nb_error("Type Cast Error!");
                            exit(1);
                        }
                        value_to_bool(&val);
                        break;
                    case DOUBLE:
                        if (val->type == STRING)
                        {
                            nb_error("Type Cast Error!");
                            exit(1);
                        }
                        value_to_double(&val);
                        break;
                    case STRING:
                        value_to_string(&val);
                        break;
                    case ARRAY:
                        break;
                }
            }
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
            VariablesList *found = find_in_list_func(inter->variables_list, identifier);
            if (found)
            {
                nb_error("Duplicated Declaration!");
                exit(1);
            }
            if (inter->variables_list)
            { 
                inter->variables_list->next = (VariablesList*)malloc(sizeof(VariablesList));
                inter->variables_list->next->prev = inter->variables_list;
                inter->variables_list = inter->variables_list->next;
                inter->variables_list->next = NULL;
                inter->variables_list->level = inter->level;
                inter->variables_list->identifier = utf8_string_copy_new(identifier);
                inter->variables_list->value = value_new_type(exp->content.declaration_expression.type);
                if (exp->content.declaration_expression.exp)
                    eval(exp->content.declaration_expression.exp);
            }
            else
            {
                inter->variables_list = (VariablesList*)malloc(sizeof(VariablesList));
                inter->variables_list->prev = NULL;
                inter->variables_list->next = NULL;
                inter->variables_list->level = inter->level;
                inter->variables_list->identifier = utf8_string_copy_new(identifier);
                inter->variables_list->value = value_new_type(exp->content.declaration_expression.type);
                if (exp->content.declaration_expression.exp)
                    eval(exp->content.declaration_expression.exp);
            }
            break;
        }
        case BINARY_EXPRESSION:
        {
            NB_Value *first = eval(exp->content.binary_expression.first);
            NB_Value *second = eval(exp->content.binary_expression.second);
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
                    NB_Value *val = eval(exp->content.unary_expression.exp);
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
                    value_delete(&val);
                    break;
                }
                case NOT:
                {
                    NB_Value *val = eval(exp->content.unary_expression.exp);                    
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
                    value_delete(&val);
                    break;
                }
                case INCREMENT:
                {
                    VariablesList *found = find_in_list(inter->variables_list, exp->content.unary_expression.identifier);
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
                            nb_error("Type Error!");
                            exit(1);
                        }
                    }
                    break;
                }
                case DECREMENT:
                {
                    VariablesList *found = find_in_list(inter->variables_list, exp->content.unary_expression.identifier);
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
                            nb_error("Type Error!");
                            exit(1);
                        }
                    }
                    break;
                }
            }
        }
        case FUNCTION_CALL_EXPRESSION:
            break;
    }
    return ret;
}

VariablesList *find_in_list_func(VariablesList *vlist, UTF8_String *str)
{
    // VariablesList *stored = vlist;
    for (;vlist != NULL; vlist = vlist->prev)
    {
        if (!utf8_string_compare(str, vlist->identifier))
            return vlist;
    }
    // vlist = stored;
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