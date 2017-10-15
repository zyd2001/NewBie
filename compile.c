#include "newbie.h"

extern int current_line;

Expression *nb_create_literal_expression(NB_ValueType type, char *text)
{
    Expression *expression = (Expression*)malloc(sizeof(Expression));
    expression->type = LITERAL_EXPRESSION;
    expression->content.literal.type = type;
    switch(type)
    {
        case INT:
        {
            int i = atoi(text);
            expression->content.literal.value.int_value = i;
            break;
        }
        case DOUBLE:
        {
            double d = atof(text);
            expression->content.literal.value.double_value = d;
            break;
        }
        case STRING:
        {
            UTF32_String *str = utf32_string_new_wrap_utf8(text);
            expression->content.literal.value.string_value = str;
            break;
        }
    }
    return expression;
}

Expression *nb_create_assignment_expression(UTF8_String *identifier, Expression *exp)
{
    Expression *expression = (Expression*)malloc(sizeof(Expression));
    expression->type = ASSIGNMENT_EXPRESSION;
    expression->content.assignment_expression.identifier = identifier;
    expression->content.assignment_expression.exp = exp;
    return expression;
}

Expression *nb_create_declaration_expression(NB_ValueType type, UTF8_String *identifier, Expression *assignment_expression)
{
    Expression *expression = (Expression*)malloc(sizeof(Expression));
    expression->type = DECLARATION_EXPRESSION;
    if (assignment_expression)
        expression->content.declaration_expression.exp = assignment_expression;
    else
        expression->content.declaration_expression.identifier = identifier;
    fprintf(stdout, "Declaration\n");
    return expression;
}

Expression *nb_create_binary_expression(BinaryType type, Expression *left, Expression *right)
{
    Expression *expression = (Expression*)malloc(sizeof(Expression));
    expression->type = BINARY_EXPRESSION;
    expression->content.binary_expression.type = type;
    expression->content.binary_expression.first = left;
    expression->content.binary_expression.second = right;
    return expression;    
}

Expression *nb_create_identifier_expression(UTF8_String *identifier)
{
    Expression *expression = (Expression*)malloc(sizeof(Expression));
    expression->type = IDENTIFIER_EXPRESSION;
    expression->content.identifier = identifier;
    return expression; 
}

Expression *nb_create_function_call_expression()
{
    Expression *expression = (Expression*)malloc(sizeof(Expression));
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
    statement->line_number = current_line;
    return statement;
}