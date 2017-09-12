#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "newbie.h"

Expression *create_value_expression(ExpressionType type, char *text)
{
    Expression exp;
    switch(type)
    {
        case INT:
            int i = atoi(text);

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