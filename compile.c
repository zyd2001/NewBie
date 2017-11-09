#include "newbie.h"

#define new_expression() (Expression*)malloc(sizeof(Expression))
#define new_statement() (Statement*)malloc(sizeof(Statement))

static int state = 0;
static Statement *current_if;
static ClassList *current_class;

void nb_compile(FILE *fp)
{
    extern int yylex_destroy(void);
    extern int yyparse(void);
    extern FILE *yyin;
    yyin = fp;
    yyparse();
    yylex_destroy();
    fclose(fp);
}

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

Expression *nb_create_assignment_expression(Expression *lval, Expression *rval)
{
    Expression *expression = new_expression();
    expression->type = ASSIGNMENT_EXPRESSION;
    expression->content.assignment_expression.lval = lval;
    expression->content.assignment_expression.rval = rval;
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
    expression->ref = 0;
    expression->content.binary_expression.type = type;
    expression->content.binary_expression.first = left;
    expression->content.binary_expression.second = right;
    return expression;    
}

Expression *nb_create_binary_expression_sp(BinaryType type, Expression *left, Expression *right)
{
    Expression *expression = new_expression();
    expression->type = BINARY_EXPRESSION;
    expression->ref = 1;
    expression->content.binary_expression.type = type;
    expression->content.binary_expression.first = left;
    expression->content.binary_expression.second = right;
    return expression;    
}

Expression *nb_create_unary_expression(UnaryType type, Expression *exp)
{
    Expression *expression = new_expression();
    expression->type = UNARY_EXPRESSION;
    expression->content.unary_expression.type = type;
    expression->content.unary_expression.exp = exp;
    return expression;
}

// Expression *nb_create_change_expression(UnaryType type, UTF8_String *identifier)
// {
//     Expression *expression = new_expression();
//     expression->type = UNARY_EXPRESSION;
//     expression->content.unary_expression.type = type;
//     expression->content.unary_expression.identifier = identifier;
//     expression->content.unary_expression.exp = NULL;
//     return expression;
// }

Expression *nb_create_identifier_expression(UTF8_String *identifier)
{
    Expression *expression = new_expression();
    expression->type = IDENTIFIER_EXPRESSION;
    expression->content.identifier_expression = identifier;
    return expression; 
}

Expression *nb_create_array_expression(ExpressionList *elist)
{
    Expression *expression = new_expression();
    expression->type = ARRAY_EXPRESSION;
    expression->content.expression_list = elist;
    return expression;
}

Expression *nb_create_index_expression(Expression *exp, Expression *index)
{
    Expression *expression = new_expression();
    expression->type = INDEX_EXPRESSION;
    expression->content.index_expression = (IndexExpression){exp, index};
    return expression;
}

Expression *nb_create_anonymous_function_definition_expression(NB_ValueType type, ParametersList *plist, Statement *block)
{
    int count = 1;
    if (plist == NULL)
        count = 0;
    else
        for (;plist->prev != NULL; plist = plist->prev)
            count++;
    if (inter->func_list == NULL)
    {
        inter->func_list = (FunctionList*)malloc(sizeof(FunctionList));
        inter->func_list->prev = NULL;
        inter->func_list->next = NULL;
        inter->func_list->pnum = count;
        inter->func_list->builtin = 0;
        // inter->func_list->identifier = identifier;
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
        inter->func_list->pnum = count;
        inter->func_list->builtin = 0;
        // inter->func_list->identifier = identifier;
        inter->func_list->type = type;
        inter->func_list->plist = plist;
        inter->func_list->block = block;
    }
    NB_Value func;
    func.type = FUNCTION;
    func.value.other = inter->func_list;
    Expression *expression = new_expression();
    expression->type = LITERAL_EXPRESSION;
    expression->content.literal_expression = func;   
    return expression; 
}

Expression *nb_create_function_call_expression(UTF8_String *identifier, ArgumentsList *alist)
{
    Expression *expression = new_expression();
    expression->type = FUNCTION_CALL_EXPRESSION;
    expression->content.function_call_expression.alist = alist;
    expression->content.function_call_expression.identifier = utf8_string_append_char(identifier, '$');
    return expression;
}

Statement *nb_create_function_definition_statement(NB_ValueType type, UTF8_String *identifier, ParametersList *plist, Statement *block)
{
    int count = 1;
    if (plist == NULL)
        count = 0;
    else
        for (;plist->prev != NULL; plist = plist->prev)
            count++;
    if (inter->func_list == NULL)
    {
        inter->func_list = (FunctionList*)malloc(sizeof(FunctionList));
        inter->func_list->prev = NULL;
        inter->func_list->next = NULL;
        inter->func_list->pnum = count;
        inter->func_list->builtin = 0;
        // inter->func_list->identifier = identifier;
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
        inter->func_list->pnum = count;
        inter->func_list->builtin = 0;
        // inter->func_list->identifier = identifier;
        inter->func_list->type = type;
        inter->func_list->plist = plist;
        inter->func_list->block = block;
    }
    NB_Value *func = value_new_type(FUNCTION);
    func->value.other = inter->func_list;
    nb_add_global_variable(func, utf8_string_append_char(identifier, '$'));
    Statement *statement = new_statement();
    statement->type = FUNCTION_DEFINITION_STATEMENT;
    statement->line_number = inter->current_line;
    return statement;    
}

Statement *nb_create_expression_statement(Expression *exp)
{
    Statement *statement = new_statement();
    statement->type = EXPRESSION_STATEMENT;
    statement->content.expression = exp;
    statement->line_number = inter->current_line;
    return statement;
}

Statement *nb_create_class_definition_statement(UTF8_String *identifier, Statement *block)
{
    NB_Interpreter *inter = inter;
    Statement *statement = new_statement();
    statement->type = CLASS_DEFINITION_STATEMENT;
    statement->line_number = inter->current_line;
    if (inter->class_list == NULL)
    {
        inter->class_list = (ClassList*)malloc(sizeof(ClassList));
        inter->class_list->prev = NULL;
        inter->class_list->next = NULL;
        inter->class_list->block = block;
        inter->class_list->identifier = identifier;
    }
    else
    {
        inter->class_list->next = (ClassList*)malloc(sizeof(ClassList));
        inter->class_list->next->prev = inter->class_list;
        inter->class_list = inter->class_list->next;
        inter->class_list->next = NULL;
        inter->class_list->block = block;
        inter->class_list->identifier = identifier;
    }
    current_class = inter->class_list;
    return statement;
}

Statement *nb_create_block_statement(StatementsList *slist)
{
    Statement *statement = new_statement();
    statement->type = BLOCK_STATEMENT;
    statement->content.block_statement = (Block){slist};
    statement->line_number = inter->current_line;
    return statement;
}

Statement *nb_create_if_statement(Expression *exp, Statement *block)
{
    Statement *statement = new_statement();
    statement->type = IF_STATEMENT;
    statement->content.if_statement = (If){block, exp, NULL, NULL};
    statement->line_number = inter->current_line;
    current_if = statement;
    return statement;
}

Statement *nb_create_foreach_statement(UTF8_String *identifier, Expression *exp, Statement *block, int flag)
{
    Statement *statement = new_statement();
    statement->type = FOREACH_STATEMENT;
    statement->content.foreach_statement = (Foreach){identifier, exp, block, flag};
    statement->line_number = inter->current_line;
    return statement;
}

Statement *nb_create_for_statement(Expression *exp1, Expression *exp2, Expression *exp3, Statement *block)
{
    Statement *statement = new_statement();
    statement->type = FOR_STATEMENT;
    statement->content.for_statement = (For){exp1, exp2, exp3, block};
    statement->line_number = inter->current_line;
    return statement;
}

Statement *nb_create_return_statement(Expression *exp)
{
    Statement *statement = new_statement();
    statement->type = RETURN_STATEMENT;
    statement->content.expression = exp;
    statement->line_number = inter->current_line;
    return statement;
}

Statement *nb_create_continue_statement()
{
    Statement *statement = new_statement();
    statement->type = CONTINUE_STATEMENT;
    statement->line_number = inter->current_line;
    return statement;
}

Statement *nb_create_break_statement()
{
    Statement *statement = new_statement();
    statement->type = BREAK_STATEMENT;
    statement->line_number = inter->current_line;
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

StatementsList *nb_create_statement_list(Statement *s)
{
    StatementsList *slist = (StatementsList*)malloc(sizeof(StatementsList));
    slist->s = s;
    slist->prev = NULL;
    slist->next = NULL;
    if (state == 0)
    {
        inter->statements_list = slist;
        state++;
    }
    return slist;
}

StatementsList *nb_cat_statement_list(StatementsList *slist, Statement *s)
{
    slist->next = (StatementsList*)malloc(sizeof(StatementsList));
    slist->next->prev = slist;
    slist = slist->next;
    slist->next = NULL;
    slist->s = s;
    return slist;
}

ArgumentsList *nb_create_argument_list(Expression *exp)
{
    ArgumentsList *alist = (ArgumentsList*)malloc(sizeof(ArgumentsList));
    alist->prev = NULL;
    alist->next = NULL;
    alist->exp = exp;
    return alist;
}

ArgumentsList *nb_cat_argument_list(ArgumentsList *alist, Expression *exp)
{
    alist->next = (ArgumentsList*)malloc(sizeof(ArgumentsList));
    alist->next->prev = alist;
    alist = alist->next;
    alist->next = NULL;
    alist->exp = exp;
    return alist;
}

ParametersList *nb_create_parameter_list(Expression *exp)
{
    ParametersList *plist = (ParametersList*)malloc(sizeof(ParametersList));
    plist->prev = NULL;
    plist->next = NULL;
    plist->exp = exp;
    return plist;
}

ParametersList *nb_cat_parameter_list(ParametersList *plist, Expression *exp)
{
    plist->next = (ParametersList*)malloc(sizeof(ParametersList));
    plist->next->prev = plist;
    plist = plist->next;
    plist->next = NULL;
    plist->exp = exp;
    return plist;
}

ExpressionList *nb_create_expression_list(Expression *exp)
{
    ExpressionList *elist = (ExpressionList*)malloc(sizeof(ExpressionList));
    elist->next = NULL;
    elist->exp = exp;
    return elist;
}

ExpressionList *nb_cat_expression_list(ExpressionList *elist, Expression *exp)
{
    ExpressionList *temp = elist;
    for (;temp->next != NULL; temp = temp->next);
    temp->next = (ExpressionList*)malloc(sizeof(ExpressionList));
    temp = temp->next;
    temp->next = NULL;
    temp->exp = exp;
    return elist;
}