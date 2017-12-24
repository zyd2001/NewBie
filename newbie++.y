%skeleton "lalr1.cc"
%require "3.0.4"
%defines "Parser.hpp"
%output "Parser.cpp"
%define parser_class_name {Parser}

%code requires
{
#include "NewBie_Lang.hpp"
#include "NewBie.hpp"
}

%code
{
    using namespace std;
    using namespace zyd2001::NewBie;
    IfStatement *current_if;
	Parser::symbol_type yylex(InterpreterImp &inter, yyscan_t yyscanner);
}

%no-lines
%define api.namespace {zyd2001::NewBie}
%define api.value.type variant
%define api.token.constructor
%define api.token.prefix {TOKEN_}
%define parse.trace
%define parse.error verbose
%param {InterpreterImp &inter}
%param {yyscan_t scanner}
%locations
%initial-action
{
    @$.begin.filename = @$.end.filename = &inter.filename;
}

%left LOGICAL_AND LOGICAL_OR
%left EQ NE GT GE LT LE
%left ADD SUB
%left MUL DIV MOD
%nonassoc UMINUS
%token<Expression> INT_LITERAL STRING_LITERAL DOUBLE_LITERAL BOOL_LITERAL
%token<Identifier>     IDENTIFIER
%token END  0  "end of file"
        INT DOUBLE BOOL STRING ARRAY VAR GLOBAL IF ELSE ELSEIF FOR IN CLASS RETURN BREAK CONTINUE
        LP RP LC RC LB RB SEMICOLON COMMA ASSIGN EXCLAMATION DOT NEW CONSTRUCTOR THIS
        ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
        INCREMENT DECREMENT PUBLIC PROTECTED PRIVATE REVERSE
        PRINT
%type<Expression> expression function_call_expression primary_expression expression_optional binary_expression unary_expression array_expression index_expression dot_expression dot_pre_expression
%type<Statement> statement block statement_optional class_definition declaration_statement assignment_statement
%type<StatementsList> statements_list
%type<ParametersList> parameters_list
%type<ExpressionsList> expressions_list arguments_list
%type<ValueType> type_tag
%type<Parameter> parameter
%type<DeclarationStatementItem> declaration_item
%type<DeclarationStatementItemsList> declaration_items_list
%%
    eof: statements_list END
		{
			inter.statements_list = $1;
		}
		;
    statements_list: statement
        {
            $$.emplace_back($1);
        }
        | statements_list statement
        {
            $1.emplace_back($2);
            $$.swap($1);
        }
        ;
    statement: expression SEMICOLON
        {
            $$ = Statement(EXPRESSION_STATEMENT, new ExpressionStatement($1), yyget_lineno(scanner));
        }
        | IF LP expression RP statement
        {
            current_if = new (IfStatement){$3, $5};
            $$ = Statement(IF_STATEMENT, current_if, yyget_lineno(scanner));
        }
        | ELSE statement
        {
            current_if->else_stat = $2;
            $$ = Statement();
        }
        | ELSEIF LP expression RP statement
        {
            ElseIf e = {$3, $5};
            current_if->elseif.emplace_back(e);
            $$ = Statement();
        }
        | FOR LP statement_optional SEMICOLON expression_optional SEMICOLON statement_optional RP statement
        {
            $$ = Statement(FOR_STATEMENT, new (ForStatement){$3, $5, $7, $9}, yyget_lineno(scanner));
        }
        | FOR LP IDENTIFIER IN expression RP block
        {
            $$ = Statement(FOREACH_STATEMENT, new (ForeachStatement){$3, $5, $7, false}, yyget_lineno(scanner));
        }
        | FOR LP IDENTIFIER IN REVERSE expression RP block
        {
            $$ = Statement(FOREACH_STATEMENT, new (ForeachStatement){$3, $6, $8, true}, yyget_lineno(scanner));
        }
        | RETURN expression SEMICOLON
        {
            $$ = Statement(RETURN_STATEMENT, new ReturnStatement($2), yyget_lineno(scanner));
        }
        | CONTINUE SEMICOLON
        {
            $$ = Statement(CONTINUE_STATEMENT, nullptr, yyget_lineno(scanner));
        }
        | BREAK SEMICOLON
        {
            $$ = Statement(BREAK_STATEMENT, nullptr, yyget_lineno(scanner));
        }
        | type_tag IDENTIFIER LP parameters_list RP block
        {
            VariablesMap *vmap;
            if (inter.in_class)
                vmap = &inter.current_class->static_variables;
            else
                vmap = &inter.global_variables;
            auto result = (*vmap).find($2);
            if (result != (*vmap).cend())
            {
                auto &func = result->second.get<Function>();
                if (func.can_overload)
                {
                    auto exist = func.overload_map.find($4);
                    if (exist == func.overload_map.cend())
                    {
                        for (auto &i : $4)
                        {
                            if (i.type == VARIANT_TYPE || i.default_value_exp.type != NULL_EXPRESSION)
                            {
                                inter.err();
                                break;
                            }
                        }
                        func.overload_map[$4] = $6;
                    }
                    else
                        inter.err();
                }
                else
                    inter.err();
            }
            else
            {
                auto func = new Function();
                func->return_type = $1;
                func->can_overload = true;
                (*vmap)[$2] = Value(FUNCTION_TYPE, func);
                func->overload_map[$4] = $6;
                for (auto &i : $4)
                {
                    if (i.type == VARIANT_TYPE || i.default_value_exp.type != NULL_EXPRESSION)
                    {
                        func->can_overload = false;
                        break;
                    }
                }
            }
            $$ = Statement();
        }
        | CONSTRUCTOR LP parameters_list RP block
        {
            auto &func = inter.current_class->ctor;
            if (func.overload_map.empty())
            {
                func.can_overload = true;
                func.overload_map[$3] = $5;
                for (auto &i : $3)
                {
                    if (i.type == VARIANT_TYPE || i.default_value_exp.type != NULL_EXPRESSION)
                    {
                        func.can_overload = false;
                        break;
                    }
                }
            }
            else if (func.can_overload)
            {
                auto exist = func.overload_map.find($3);
                if (exist == func.overload_map.cend())
                {
                    for (auto &i : $3)
                    {
                        if (i.type == VARIANT_TYPE || i.default_value_exp.type != NULL_EXPRESSION)
                        {
                            inter.err();
                            break;
                        }
                    }
                    func.overload_map[$3] = $5;
                }
                else
                    inter.err("exist");
            }
            else
                inter.err("can_overload");
            $$ = Statement();
        }
        | block
        {
            $$ = $1;
        }
        | PRINT expression SEMICOLON
        {
            $$ = Statement(DEBUG_STATEMENT, new DebugStatement($2), yyget_lineno(scanner));
        }
        | declaration_statement
        {
            $$ = $1;
        }
        | assignment_statement
        {
            $$ = $1;
        }
        | class_definition
        ;
    assignment_statement: expression ASSIGN expression SEMICOLON
        {
            $$ = Statement(ASSIGNMENT_STATEMENT, new (AssignmentStatement){$1, $3}, yyget_lineno(scanner));
        }
        ;
    declaration_statement: type_tag declaration_items_list SEMICOLON
        {
            $$ = Statement(DECLARATION_STATEMENT, new (DeclarationStatement){false, $1, std::move($2)}, yyget_lineno(scanner));
        }
		| GLOBAL type_tag declaration_items_list SEMICOLON
        {
            $$ = Statement(DECLARATION_STATEMENT, new (DeclarationStatement){true, $2, std::move($3)}, yyget_lineno(scanner));
        }
        | IDENTIFIER declaration_items_list SEMICOLON
        {
            $$ = Statement(DECLARATION_STATEMENT, new (DeclarationStatement){false, OBJECT_TYPE, std::move($2), $1}, yyget_lineno(scanner));
        }
        | GLOBAL IDENTIFIER declaration_items_list SEMICOLON
        {
            $$ = Statement(DECLARATION_STATEMENT, new (DeclarationStatement){true, OBJECT_TYPE, std::move($3), $2}, yyget_lineno(scanner));
        }
        ;
    declaration_item: IDENTIFIER 
        {
            $$ = {$1};
        }
        | IDENTIFIER ASSIGN expression
        {
            $$ = {$1, $3};
        }
        ;
    declaration_items_list: declaration_item
        {
            $$.emplace_back(std::move($1));
        }
        | declaration_items_list COMMA declaration_item
        {
            $1.emplace_back(std::move($3));
            $$.swap($1);
        }
        ;
    class_definition: CLASS IDENTIFIER LC statements_list RC
        {
            auto result = inter.class_map.find($2);
            if (result == inter.class_map.cend())
            {
                inter.current_class->type = $2;
                inter.current_class->slist = $4;
                inter.class_map[$2] = *inter.current_class;
                delete inter.current_class;
                inter.current_class = nullptr;
                $$ = Statement();
                inter.in_class = false;
            }
            else
                inter.err("class_definition");
        }
        ;
    expression: binary_expression
        {
            $$ = $1;
        }
        | unary_expression
        {
            $$ = $1;
        }
        | primary_expression
        {
            $$ = $1;
        }
        | function_call_expression
        {
            $$ = $1;
        }
        | IDENTIFIER
        {
            $$ = Expression(IDENTIFIER_EXPRESSION, new IdentifierExpression($1));
        }
        | LP expression RP
        {
            $$ = $2;
        }
        | array_expression
        {
            $$ = $1;
        }
        | index_expression
        {
            $$ = $1;
        }
        | dot_expression
        {
            $$ = $1;
        }
        | NEW function_call_expression
        {
            $2.type = NEW_OBJECT_EXPRESSION;
            $$ = $2;
        }
        ;
    index_expression: IDENTIFIER LB expression RB
        {
            $$ = Expression(INDEX_EXPRESSION, new (IndexExpression){Expression(IDENTIFIER_EXPRESSION, new IdentifierExpression($1)), $3});
        }
        | array_expression LB expression RB
        {
            $$ = Expression(INDEX_EXPRESSION, new (IndexExpression){$1, $3});
        }
        | function_call_expression LB expression RB
        {
            $$ = Expression(INDEX_EXPRESSION, new (IndexExpression){$1, $3});
        }
        | index_expression LB expression RB
        {
            $$ = Expression(INDEX_EXPRESSION, new (IndexExpression){$1, $3});
        }
        ;
    array_expression: LB expressions_list RB
        {
            $$ = Expression(ARRAY_EXPRESSION, new ArrayExpression(std::move($2)));
        }
        ;
    dot_expression: dot_pre_expression DOT function_call_expression
        {
            $$ = Expression(DOT_EXPRESSION, new (DotExpression){$1, $3});
        }
        | dot_pre_expression DOT IDENTIFIER
        {
            $$ = Expression(DOT_EXPRESSION, new (DotExpression){$1, Expression(IDENTIFIER_EXPRESSION, new IdentifierExpression($3))});
        }
        ;
    dot_pre_expression: primary_expression
        {
            $$ = $1;
        }
        | function_call_expression
        {
            $$ = $1;
        }
        | IDENTIFIER
        {
            $$ = Expression(IDENTIFIER_EXPRESSION, new IdentifierExpression($1));
        }
        | LP expression RP
        {
            $$ = $2;
        }
        | index_expression
        {
            $$ = $1;
        }
        | dot_expression
        {
            $$ = $1;
        }
        | THIS
        {
            $$ = Expression(THIS_EXPRESSION, nullptr);
        }
        ;
    expression_optional: /* empty */
        {
            $$ = Expression();
        }
        | expression
        {
            $$ = $1;
        }
        ;
    statement_optional: /* empty */
        {
            $$ = Statement();
        }
        | expression
        {
            $$ = Statement(EXPRESSION_STATEMENT, new ExpressionStatement($1), yyget_lineno(scanner));
        }
        | expression ASSIGN expression
        {
            $$ = Statement(ASSIGNMENT_STATEMENT, new (AssignmentStatement){$1, $3}, yyget_lineno(scanner));
        }
        | declaration_statement
        {
            $$ = $1;
        }
        ;
    binary_expression: expression ADD expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){ADD, $1, $3});
        }
        | expression SUB expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){SUB, $1, $3});
        }
        | expression MUL expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){MUL, $1, $3});
        }
        | expression DIV expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){DIV, $1, $3});
        }
        | expression MOD expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){MOD, $1, $3});
        }
        | expression EQ expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){EQ, $1, $3});
        }
        | expression NE expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){NE, $1, $3});
        }
        | expression GT expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){GT, $1, $3});
        }
        | expression GE expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){GE, $1, $3});
        }
        | expression LT expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){LT, $1, $3});
        }
        | expression LE expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){LE, $1, $3});
        }
        | expression LOGICAL_AND expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){AND, $1, $3});
        }
        | expression LOGICAL_OR expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){OR, $1, $3});
        }
        ;
    unary_expression: SUB expression %prec UMINUS
        {
            $$ = Expression(UNARY_EXPRESSION, new (UnaryExpression){MINUS, $2});
        }
        | EXCLAMATION expression %prec UMINUS
        {
            $$ = Expression(UNARY_EXPRESSION, new (UnaryExpression){NOT, $2});
        }
        ;
    function_call_expression: IDENTIFIER LP arguments_list RP
        {
            $$ = Expression(FUNCTION_CALL_EXPRESSION, new (FunctionCallExpression){Expression(IDENTIFIER_EXPRESSION, new IdentifierExpression($1)), $3});
        }
        ;
    primary_expression: INT_LITERAL
        {
            $$ = $1;
        }
        | DOUBLE_LITERAL
        {
            $$ = $1;
        }
        | STRING_LITERAL
        {
            $$ = $1;
        }
        | BOOL_LITERAL
        {
            $$ = $1;
        }
        ;
    expressions_list: expression
        {
            $$.emplace_back($1);
        }
        | expressions_list COMMA expression
        {
            $1.emplace_back($3);
            $$.swap($1);
        }
        ;
    type_tag: INT
        {
            $$ = INT_TYPE;
        }
        | DOUBLE
        {
            $$ = DOUBLE_TYPE;
        }
        | BOOL
        {
            $$ = BOOL_TYPE;
        }
        | STRING
        {
            $$ = STRING_TYPE;
        }
        | ARRAY
        {
            $$ = ARRAY_TYPE;
        }
        | VAR
        {
            $$ = VARIANT_TYPE;
        }
        ;
    block: LC statements_list RC
        {
            $$ = Statement(BLOCK_STATEMENT, new BlockStatement(std::move($2)), yyget_lineno(scanner));
        }
        | LC RC
        {
            $$ = Statement(BLOCK_STATEMENT, new BlockStatement(), yyget_lineno(scanner));
        }
        ;
    arguments_list: /* empty */
        {
            $$;
        }
        | expression
        {
            $$.emplace_back($1);
        }
        | arguments_list COMMA expression
        {
            $1.emplace_back($3);
            $$.swap($1);
        }
        ;
    parameter: type_tag IDENTIFIER
        {
            $$ = {$1, $2};
        }
        | type_tag IDENTIFIER ASSIGN primary_expression
        {
            $$ = {$1, $2, $4};
        }
        ;
    parameters_list: /* empty */
        {
            $$;
        }
        | parameter
        {
            $$.emplace_back(std::move($1));
        }
        | parameters_list COMMA parameter
        {
            $1.emplace_back(std::move($3));
            $$.swap($1);
        }
        ;
%%

void Parser::error(const location_type& l, const std::string& m)
{
	std::cerr << "At file " << inter.filename  << " " << l << " " << m << endl;
}