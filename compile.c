#include "newbie.h"

#define new_expression() (Expression*)calloc(1, sizeof(Expression))


// void record_ptr(void* ptr)
// {
//     if (!inter->ptrs_list)
//     {
//         inter->ptrs_list = (struct ptrs_list_tag*)malloc(sizeof(struct ptrs_list_tag));
//         inter->ptrs_list->ptr = ptr;
//         inter->ptrs_list->prev = NULL;
//         inter->ptrs_list->next = NULL;
//     }
//     else
//     {
//         inter->ptrs_list->next = (struct ptrs_list_tag*)malloc(sizeof(struct ptrs_list_tag));
//         inter->ptrs_list->next->prev = inter->ptrs_list;
//         inter->ptrs_list = inter->ptrs_list->next;
//         inter->ptrs_list->ptr = ptr;
//         inter->ptrs_list->next = NULL;
//     }
// }

Expression *nb_create_literal_expression(NB_ValueType type, char *text)
{
    Expression *expression = new_expression();
    expression->type = LITERAL_EXPRESSION;
    expression->content.literal_expression.type = type;
    switch(type)
    {
        case INT:
        {
            int i = atoi(text);
            expression->content.literal_expression.value.int_value = i;
            break;
        }
        case DOUBLE:
        {
            double d = atof(text);
            expression->content.literal_expression.value.double_value = d;
            break;
        }
        case BOOL:
        {
            char b = (int)text;
            expression->content.literal_expression.value.bool_value = b;
            break;
        }
        case STRING:
        {
            UTF32_String *str = utf32_string_new_wrap_utf8(text);
            expression->content.literal_expression.value.string_value = str;
            break;
        }
    }
    return expression;
}

Expression *nb_create_assignment_expression(UTF8_String *identifier, Expression *exp)
{
    Expression *expression = new_expression();
    expression->type = ASSIGNMENT_EXPRESSION;
    expression->content.assignment_expression.identifier = identifier;
    expression->content.assignment_expression.exp = exp;
    return expression;
}

Expression *nb_create_declaration_expression(NB_ValueType type, UTF8_String *identifier, Expression *assignment_expression)
{
    Expression *expression = new_expression();
    expression->type = DECLARATION_EXPRESSION;
    expression->content.declaration_expression.type = type;
    if (assignment_expression)
        expression->content.declaration_expression.exp = assignment_expression;
    else
        expression->content.declaration_expression.identifier = identifier;
    return expression;
}

Expression *nb_create_binary_expression(BinaryType type, Expression *left, Expression *right)
{
    Expression *expression = new_expression();
    expression->type = BINARY_EXPRESSION;
    expression->content.binary_expression.type = type;
    expression->content.binary_expression.first = left;
    expression->content.binary_expression.second = right;
    return expression;    
}

Expression *nb_create_identifier_expression(UTF8_String *identifier)
{
    Expression *expression = new_expression();
    expression->type = IDENTIFIER_EXPRESSION;
    expression->content.identifier_expression = identifier;
    return expression; 
}

Expression *nb_create_function_call_expression()
{
    Expression *expression = new_expression();
    expression->type = FUNCTION_CALL_EXPRESSION;
    return expression;
}

Expression *nb_create_function_definition()
{

}

Statement *nb_create_expression_statement(Expression *exp)
{
    Statement *statement = (Statement*)malloc(sizeof(Statement));
    statement->type = EXPRESSION;
    statement->content.expression = exp;
    statement->line_number = get_interpreter()->current_line;
    return statement;
}