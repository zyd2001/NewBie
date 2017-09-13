#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "newbie.h"

Expression *create_value_expression(ExpressionType type, char *text)
{
    NBValueType value_type;
    Expression *exp;
    exp = (Expression*)malloc(sizeof(Expression));
    exp->type = type;
    exp->content->raw_value = (NB_Value*)malloc(sizeof(NB_Value));
    switch(type)
    {
        case INT:
            value_type = INT;
            int i = atoi(text);
            exp->content.raw_value->type = value_type;
            exp->content.raw_value->value.int_value = i;
            break;
        case DOUBLE:
            value_type = DOUBLE;
            double d = atof(text);
            exp->content.raw_value->type = value_type;
            exp->content.raw_value->value.double_value = d;
            break;
        case STRING:
            value_type = STRING;
            char *str = text;
            exp->content.raw_value->type = value_type;
            exp->content.raw_value->value.string_value = str;
            break;
    }
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