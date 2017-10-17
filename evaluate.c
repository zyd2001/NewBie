#include "newbie.h"

#define bool_check(operator)\
do {\
    ret->type = BOOL;\
    if (first->type == STRING || second->type == STRING)\
    {\
        UTF32_String *str_1 = get_string_value(first);\
        UTF32_String *str_2 = get_string_value(second);\
        ret->value.bool_value = utf32_string_compare_utf32(str_1, str_2) operator 0 ? 1 : 0;\
    }\
    else if (first->type == DOUBLE || second->type == DOUBLE)\
    {\
        double double_1 = get_double_value(first);\
        double double_2 = get_double_value(second);\
        ret->value.bool_value = double_1 operator double_2;\
    }\
    else\
    {\
        ret->value.bool_value = first->value.int_value operator second->value.int_value;\
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

UTF32_String *get_string_value(Value *val);
double get_double_value(Value *val);
struct variables_list_tag *find_in_list(struct variables_list_tag *vlist, UTF8_String *str);
struct variables_list_tag *find_in_list_func(struct variables_list_tag *vlist, UTF8_String *str);

NB_Value *eval(Expression *exp)
{
    NB_Value *ret = value_new();
    NB_Interpreter *inter = get_interpreter();
    switch (exp->type)
    {
        case LITERAL_EXPRESSION:
        {
            value_copy(ret, &exp->content.literal_expression);
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
            struct variables_list_tag *found = find_in_list(inter->variables_list, exp->content.assignment_expression.identifier);
            if (found->value)
                value_copy(found->value, val);
            else 
                found->value = value_copy(NULL, val);
            value_copy(ret, val);
            value_delete(&val);
            break;
        }
        case DECLARATION_EXPRESSION:
        {
            ret->type = BOOL;
            ret->value.bool_value = 1;
            UTF8_String *identifier = exp->content.declaration_expression.identifier ? exp->content. \
                declaration_expression.identifier : exp->content.declaration_expression.exp-> \
                content.assignment_expression.identifier;
            struct variables_list_tag *found = find_in_list_func(inter->variables_list, identifier);
            if (found)
            {
                nb_error("Duplicated Declaration!");
                exit(1);
            }
            if (inter->variables_list)
            { 
                inter->variables_list->next = (struct variables_list_tag*)calloc(1, sizeof(struct variables_list_tag));
                inter->variables_list->next->prev = inter->variables_list;
                inter->variables_list = inter->variables_list->next;
                inter->variables_list->level = inter->level;
                inter->variables_list->identifier = utf8_string_copy(NULL, identifier);
                inter->variables_list->value = exp->content.declaration_expression.exp ? eval(exp->content.declaration_expression.exp) : NULL;
            }
            else
            {
                inter->variables_list = (struct variables_list_tag*)calloc(1, sizeof(struct variables_list_tag));
                inter->variables_list->level = inter->level;
                inter->variables_list->identifier = utf8_string_copy(NULL, identifier);
                inter->variables_list->value = exp->content.declaration_expression.exp ? eval(exp->content.declaration_expression.exp) : NULL;
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
                        ret->value.string_value = utf32_string_copy(NULL, str_1);
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
            }
            value_delete(&first, &second);
            break;
        }
        case FUNCTION_CALL_EXPRESSION:
            break;
    }
    return ret;
}

double get_double_value(Value *val)
{
    double d;
    switch (val->type)
    {
        case INT:
        case BOOL:
            d = val->value.int_value;
            break;
        case DOUBLE:
            d = val->value.double_value;
            break;
        // case STRING:
        //     char *utf8 = utf32_to_utf8(val->string_value);
        //     d = atof(utf8);
        //     __free(utf8);
        //     break;
        case ARRAY:
            break;
    }
    return d;
}

UTF32_String *get_string_value(Value *val)
{
    UTF32_String *str = utf32_string_new();
    switch (val->type)
    {
        case INT:
        case BOOL:
        {
            char *out = (char*)malloc(100 * sizeof(char));
            sprintf(out, "%d", val->value.int_value);
            utf32_string_append_utf8(str, out);
            __free(out);
            break;
        }
        case DOUBLE:
        {
            char *out = (char*)malloc(100 * sizeof(char));
            sprintf(out, "%f", val->value.double_value);
            utf32_string_append_utf8(str, out);
            __free(out);
            break;
        }
        case STRING:
        {
            utf32_string_copy(str, val->value.string_value);
            break;
        }
        case ARRAY:
            break;
    }
    return str;
}

struct variables_list_tag *find_in_list_func(struct variables_list_tag *vlist, UTF8_String *str)
{
    struct variables_list_tag *stored = vlist;
    for (;vlist != NULL; vlist = vlist->prev)
    {
        if (!utf8_string_compare(str, vlist->identifier))
            return vlist;
    }
    vlist = stored;
    for (;vlist != NULL; vlist = vlist->next)
    {
        if (!utf8_string_compare(str, vlist->identifier))
            return vlist;
    }
    return NULL;
}

struct variables_list_tag *find_in_list(struct variables_list_tag *vlist, UTF8_String *str)
{
    struct variables_list_tag *found = find_in_list_func(vlist, str);
    if (!found)
    {
        nb_error("Undefined Variable!");
        exit(1);    
    }
    else
        return found;
}