#include "newbie.h"

#define new_expression() (Expression*)malloc(sizeof(Expression))
#define new_statement() (Statement*)malloc(sizeof(Statement))

static int state = 0;
static Statement *current_if;

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
            char b = text ? 1 : 0;
            expression->content.literal_expression.value.int_value = b;
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
    {
        expression->content.declaration_expression.exp = assignment_expression;
        expression->content.declaration_expression.identifier = NULL;        
    }
    else
    {
        expression->content.declaration_expression.identifier = identifier;
        expression->content.declaration_expression.exp = NULL;
    }
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

Expression *nb_create_function_call_expression(UTF8_String *identifier, ArgumentList *alist)
{
    Expression *expression = new_expression();
    expression->type = FUNCTION_CALL_EXPRESSION;
    expression->content.function_call_expression.alist = alist;
    expression->content.function_call_expression.identifier = identifier;
    return expression;
}

Statement *nb_create_function_definition_statement(NB_ValueType type, UTF8_String *identifier, ParameterList *plist, Statement *block)
{
    NB_Interpreter *inter = nb_get_interpreter();
    if (inter->func_list == NULL)
    {
        inter->func_list = (FunctionList*)malloc(sizeof(FunctionList));
        inter->func_list->prev = NULL;
        inter->func_list->next = NULL;
        inter->func_list->identifier = utf8_string_copy_new(identifier);
        inter->func_list->type = type;
        inter->func_list->plist = plist;
        inter->func_list->block = block;
    }
    else
    {
        inter->func_list->next = (FunctionList*)malloc(sizeof(FunctionList));
        inter->func_list->next->prev = inter->func_list;
        inter->func_list = inter->func_list->next;
        inter->func_list->next = NULL;
        inter->func_list->identifier = utf8_string_copy_new(identifier);
        inter->func_list->type = type;
        inter->func_list->plist = plist;
        inter->func_list->block = block;
    }
    Statement *statement = new_statement();
    statement->type = FUNCTION_DEFINITION_STATEMENT;
    statement->line_number = nb_get_interpreter()->current_line;
    return statement;    
}

Statement *nb_create_expression_statement(Expression *exp)
{
    Statement *statement = new_statement();
    statement->type = EXPRESSION_STATEMENT;
    statement->content.expression = exp;
    statement->line_number = nb_get_interpreter()->current_line;
    return statement;
}

Statement *nb_create_block_statement(StatementList *slist)
{
    Statement *statement = new_statement();
    statement->type = BLOCK_STATEMENT;
    statement->content.block_statement = (Block){slist};
    statement->line_number = nb_get_interpreter()->current_line;
    return statement;
}

Statement *nb_create_if_statement(Expression *exp, Statement *block)
{
    Statement *statement = new_statement();
    statement->type = IF_STATEMENT;
    statement->content.if_statement = (If){block, exp, NULL, NULL};
    statement->line_number = nb_get_interpreter()->current_line;
    current_if = statement;
    return statement;
}

Statement *nb_create_foreach_statement(UTF8_String *identifier, Expression *exp, Statement *block)
{
    Statement *statement = new_statement();
    statement->type = FOREACH_STATEMENT;
    statement->content.foreach_statement = (Foreach){identifier, exp, block};
    statement->line_number = nb_get_interpreter()->current_line;
    return statement;
}

Statement *nb_create_for_statement(Expression *exp1, Expression *exp2, Expression *exp3, Statement *block)
{
    Statement *statement = new_statement();
    statement->type = FOR_STATEMENT;
    statement->content.for_statement = (For){exp1, exp2, exp3, block};
    statement->line_number = nb_get_interpreter()->current_line;
    return statement;
}

Statement *nb_create_return_statement(Expression *exp)
{
    Statement *statement = new_statement();
    statement->type = RETURN_STATEMENT;
    statement->content.expression = exp;
    statement->line_number = nb_get_interpreter()->current_line;
    return statement;
}

Statement *nb_create_continue_statement()
{
    Statement *statement = new_statement();
    statement->type = CONTINUE_STATEMENT;
    statement->line_number = nb_get_interpreter()->current_line;
    return statement;
}

Statement *nb_create_break_statement()
{
    Statement *statement = new_statement();
    statement->type = BREAK_STATEMENT;
    statement->line_number = nb_get_interpreter()->current_line;
    return statement;
}

Statement *nb_cat_else_statement(Statement *block)
{
    if (current_if == NULL)
    {
        nb_error("ELSE ERROR");
        exit(1);
    }
    else
    {
        Statement *s = current_if;
        if (current_if->content.if_statement.else_block != NULL)
        {
            nb_error("ELSE ERROR");
            exit(1);
        }
        else 
        {
            current_if->content.if_statement.else_block = block;
            current_if = NULL;
        }
    }
    Statement *s = new_statement();
    s->type = ELSE_STATEMENT;
    return s;
}

Statement *nb_cat_elseif_statement(Expression *exp, Statement *block)
{
    if (current_if == NULL)
    {
        nb_error("ELSE ERROR");
        exit(1);
    }
    else
    {
        if (current_if->content.if_statement.elseif_list == NULL)
        {
            current_if->content.if_statement.elseif_list = (ElseIfList*)malloc(sizeof(ElseIfList));
            current_if->content.if_statement.elseif_list->prev = NULL;
            current_if->content.if_statement.elseif_list->next = NULL;
            current_if->content.if_statement.elseif_list->exp = exp;
            current_if->content.if_statement.elseif_list->block = block;
        }
        else
        {
            current_if->content.if_statement.elseif_list->next = (ElseIfList*)malloc(sizeof(ElseIfList));
            current_if->content.if_statement.elseif_list->next->prev = current_if->content.if_statement.elseif_list;
            current_if->content.if_statement.elseif_list = current_if->content.if_statement.elseif_list->next;
            current_if->content.if_statement.elseif_list->next = NULL;
            current_if->content.if_statement.elseif_list->exp = exp;
            current_if->content.if_statement.elseif_list->block = block;
        }
    }
    Statement *s = new_statement();
    s->type = ELSE_STATEMENT;
    return s;
}

StatementList *nb_create_statement_list(Statement *s)
{
    StatementList *slist = (StatementList*)malloc(sizeof(StatementList));
    slist->s = s;
    slist->prev = NULL;
    slist->next = NULL;
    if (state == 0)
    {
        nb_get_interpreter()->global_list = slist;
        state++;
    }
    return slist;
}

StatementList *nb_cat_statement_list(StatementList *slist, Statement *s)
{
    slist->next = (StatementList*)malloc(sizeof(StatementList));
    slist->next->prev = slist;
    slist = slist->next;
    slist->next = NULL;
    slist->s = s;
    return slist;
}

ArgumentList *nb_create_argument_list(Expression *exp)
{
    ArgumentList *alist = (ArgumentList*)malloc(sizeof(ArgumentList));
    alist->prev = NULL;
    alist->next = NULL;
    alist->exp = exp;
    return alist;
}

ArgumentList *nb_cat_argument_list(ArgumentList *alist, Expression *exp)
{
    alist->next = (ArgumentList*)malloc(sizeof(ArgumentList));
    alist->next->prev = alist;
    alist = alist->next;
    alist->next = NULL;
    alist->exp = exp;
    return alist;
}

ParameterList *nb_create_parameter_list(NB_ValueType type, Expression *exp)
{
    ParameterList *plist = (ParameterList*)malloc(sizeof(ParameterList));
    plist->prev = NULL;
    plist->next = NULL;
    plist->aexp = exp;
    plist->type = type;
    return plist;
}

ParameterList *nb_cat_parameter_list(NB_ValueType type, ParameterList *plist, Expression *exp)
{
    plist->next = (ParameterList*)malloc(sizeof(ParameterList));
    plist->next->prev = plist;
    plist = plist->next;
    plist->next = NULL;
    plist->aexp = exp;
    plist->type = type;
    return plist;
}

// StatementList *statement(Statement *s)
// {
//     NB_Interpreter *inter = nb_get_interpreter();            
//     inter->temp_slist[inter->count] = nb_create_statement_list(s);
//     inter->count++;
//     return inter->temp_slist[inter->count - 1];
// }

// StatementList *statementl(StatementList *slist, Statement *s)
// {
//     NB_Interpreter *inter = nb_get_interpreter();                        
//     inter->temp_slist[inter->count] = nb_cat_statement_list(slist, s);
//     return inter->temp_slist[inter->count];
// }