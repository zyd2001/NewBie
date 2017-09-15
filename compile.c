#include "newbie.h"

Expression *create_literal_expression(ExpressionType type, char *text)
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
            expression->string_literal = (char*)malloc(strlen(text) * sizeof(char));
            strcpy(expression->string_literal, text);
            break;
    }
    return expression;
}

Expression *create_assignment_expression(char *identifier, Expression *exp)
{
    Expression *expression;
    return expression;
}

Expression *create_declaration_expression(NBValueType type, char *identifier, AssignExpression *assignment_expression)
{

}

Expression *create_computation_expression(ComputationType type, Expression *left, Expression *right)
{

}

Expression *create_comparison_expression(ComparisonType type, Expression *left, Expression *right)
{

}

Expression *create_function_call_expression()
{

}

Expression *create_function_definition()
{

}

Statement *create_statement(Expression *exp)
{
    
}