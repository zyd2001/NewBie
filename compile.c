#include "newbie.h"

Expression *nb_create_literal_expression(ExpressionType type, char *text)
{
    Expression *expression;
    expression = (Expression*)malloc(sizeof(Expression));
    expression->type = type;
    switch(type)
    {
        case INT:
            int i = atoi(text);
            expression->int_literal = i;
            break;
        case DOUBLE:
            double d = atof(text);
            expression->double_literal = d;
            break;
        case STRING:
            expression->string_literal = (wchar_t*)calloc(utf8_strlen(text) + 1, sizeof(char));
            // strcpy(expression->string_literal, text);
            mbstowcs(expression->string_literal, text);
            break;
    }
    return expression;
}

Expression *nb_create_assignment_expression(char *identifier, Expression *exp)
{
    Expression *expression;
    return expression;
}

Expression *nb_create_declaration_expression(NBValueType type, char *identifier, AssignExpression *assignment_expression)
{

}

Expression *nb_create_computation_expression(ComputationType type, Expression *left, Expression *right)
{

}

Expression *nb_create_comparison_expression(ComparisonType type, Expression *left, Expression *right)
{

}

Expression *nb_create_function_call_expression()
{

}

Expression *nb_create_function_definition()
{

}

Statement *nb_create_statement(Expression *exp)
{
    
}