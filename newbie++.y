%skeleton "lalr1.cc"
%require "3.0.4"
%defines "Parser.hpp"
%output "ParserT.cpp"
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
        INT DOUBLE BOOL STRING ARRAY VAR GLOBAL IF ELSE ELSEIF FOR WHILE IN FINAL CLASS RETURN BREAK CONTINUE REF CONST EDITABLE
        LP RP LC RC LB RB SEMICOLON COMMA ASSIGN EXCLAMATION DOT NEW THIS PUBLIC READONLY PRIVATE BASE
        ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
        INCREMENT DECREMENT REVERSE
        PRINT
%type<Expression> expression function_call_expression primary_expression expression_optional binary_expression unary_expression array_expression index_expression dot_expression dot_pre_expression
%type<Statement> statement block statement_optional class_definition declaration_statement assignment_statement
%type<StatementList> statement_list
%type<ParameterList> parameter_list
%type<ExpressionList> expression_list argument_list
%type<IdentifierList> identifier_list
%type<ObjectType> type_tag
%type<Parameter> parameter
%type<DeclarationStatementItem> declaration_item
%type<DeclarationStatementItemList> declaration_item_list
%%
    eof: statement_list END
		{
			inter.statement_list.swap($1);
		}
		;
    statement_list: statement
        {
            $$.list.emplace_back($1);
        }
        | statement_list statement
        {
            $1.list.emplace_back($2);
            $$.swap($1);
        }
        ;
    statement: expression SEMICOLON
        {
            $$ = makeStatement(ExpressionStatement, $1);
        }
        | IF LP expression RP statement
        {
            current_if = makeStatement(IfStatement, $3, $5);
            $$ = current_if;
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
            $$ = makeStatement(ForStatement, $3, $5, $7, $9);
        }
        | WHILE LP statement_optional RP statement
        {
            $$ = makeStatement(WhileStatement, $3, $5);
        }
        | RETURN expression SEMICOLON
        {
            $$ = makeStatement(ExpressionStatement, $2);
        }
        | CONTINUE SEMICOLON
        {
            $$ = makeStatement(ContinueStatement);
        }
        | BREAK SEMICOLON
        {
            $$ = makeStatement(BreakStatement);
        }
        | IDENTIFIER LP parameter_list RP block
        {
            if ($1 != inter.current_class->type_name)
                throw exception();
            else
                inter.current_class->ctor.overload_map[$3] = {$5};
        }
        | IDENTIFIER LP parameter_list RP SEMICOLON ctor_args_list RP block
        {
            if ($1 != inter.current_class->type_name)
                throw exception();
            else
            {
                ctor c;
                c.stat = $8;
                for (auto &i : $6)
                    c.overload_map[i.type] = i.args;
                inter.current_class->ctor.overload_map[$3] = c;
            }
        }
        | IDENTIFIER LP parameter_list RP SEMICOLON THIS LP parameter_list RP block
        {
            if ($1 != inter.current_class->type_name)
                throw exception();
            else
                inter.current_class->ctor.overload_map[$3] = {$10, {0, $8}};
        }
        | type_tag IDENTIFIER LP parameter_list RP block
        {
            VariableMap *vmap;
            if (inter.in_class)
                vmap = &inter.current_class->static_variables;
            else
                vmap = &inter.global_variables;
            auto result = (*vmap).find($2);
            if (result != (*vmap).cend())
            {
                auto &func = result->second.get<Function>();
                if (func->can_overload)
                {
                    auto exist = func->overload_map.find($4);
                    if (exist == func->overload_map.cend())
                    {
                        for (auto &i : $4)
                        {
                            if (i.type == VARIANT_TYPE || i.default_value_exp.type != NULL_EXPRESSION)
                            {
                                inter.err();
                                break;
                            }
                        }
                        func->overload_map[$4] = $6;
                    }
                    else
                        inter.err();
                }
                else
                    inter.err();
                $$ = Statement();
            }
            else
            {
                auto ptr = new Function(make_shared<function_t>());
                auto &func = *ptr;
                func->return_type = $1;
                func->can_overload = true;
                Value function(FUNCTION_TYPE, ptr);
                (*vmap)[$2] = function;
                func->overload_map[$4] = $6;
                for (auto &i : $4)
                {
                    if (i.type == VARIANT_TYPE || i.default_value_exp.type != NULL_EXPRESSION)
                    {
                        func->can_overload = false;
                        break;
                    }
                }
                $$ = Statement(FUNCTION_DEFINITION_STATEMENT, new VariableMap::value_type($2, function), yyget_lineno(scanner));
            }
        }
        | block
        {
            $$ = $1;
        }
        | declaration_statement
        {
            $$ = $1;
        }
        | assignment_statement
        {
            $$ = $1;
        }
        | visibility COLON
        {
            $$ = makeStatement(AccessControlStatement($1));
        }
        | class_definition
        ;
    assignment_statement: legal_lvalue_expression ASSIGN expression SEMICOLON
        {
            $$ = makeStatement(AssignmentStatement, $1, $3);
        }
    legal_lvalue_expression: dot_expression
        {
            $$ = $1;
        }
        | function_call_expression
        {
            $$ = $1;
        }
        | IDENTIFIER
        {
            $$ = makeExpression(IdentifierExpression, $1);
        }
        ;
    declaration_statement: type_tag declaration_item_list SEMICOLON
        {
            $$ = makeStatement(BuiltInDeclarationStatement, false, $1, std::move($2));
        }
		| GLOBAL type_tag declaration_item_list SEMICOLON
        {
            $$ = makeStatement(BuiltInDeclarationStatement, true, $2, std::move($3));
        }
        | IDENTIFIER declaration_item_list SEMICOLON
        {
            $$ = makeStatement(DeclarationStatement, false, $1, std::move($2));
        }
        | GLOBAL IDENTIFIER declaration_item_list SEMICOLON
        {
            $$ = makeStatement(DeclarationStatement, true, $2, std::move($3));
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
    declaration_item_list: declaration_item
        {
            $$.emplace_back(std::move($1));
        }
        | declaration_item_list COMMA declaration_item
        {
            $1.emplace_back(std::move($3));
            $$.swap($1);
        }
        ;
    ctor_args: IDENTIFIER LP argument_list RP
        {
            $$ = {inter.findClassId($1), $3};
        }
        ;
    ctor_args_list: ctor_args
        {
        }
        | ctor_args_list COMMA ctor_args
        {
        }
        ;
    identifier_list: IDENTIFIER
        {
            $$.emplace_back($1);
        }
        | identifier_list COMMA IDENTIFIER
        {
            $1.emplace_back($3);
            $$.swap($1);
        }
        ;
    class_definition: CLASS IDENTIFIER LC statement_list RC
        {
            inter.resolveClass($4);
        }
        | CLASS IDENTIFIER SEMICOLON identifier_list LC statement_list RC
        {
            inter.resolveClass($6, $4);
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
            $$ = makeExpression(IdentifierExpression, $1);
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
        | NEW IDENTIFIER LP argument_list RP
        {
            $$ = makeExpression(NewObjectExpression, $2, $4);
        }
        | THIS
        {
            $$ = makeExpression(ThisExpression);
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
    array_expression: LB expression_list RB
        {
            $$ = Expression(ARRAY_EXPRESSION, new ArrayExpression(std::move($2)));
        }
        ;
    dot_expression: expression DOT IDENTIFIER
        {
            $$ = makeExpression(DotExpression, $1, $3);
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
            $$ = makeStatement(ExpressionStatement, $1);
        }
        | IDENTIFIER ASSIGN expression
        {
            $$ = makeStatement(AssignmentStatement, $1, $3);
        }
        | dot_expression ASSIGN expression
        {
            $$ = makeStatement(ObjectAssignmentStatement, $1, $3);
        }
        | declaration_statement
        {
            $$ = $1;
        }
        ;
    binary_expression: expression ADD expression
        {
            $$ = makeExpression(BinaryExpression, ADD, $1, $3);
        }
        | expression SUB expression
        {
            $$ = makeExpression(BinaryExpression, SUB, $1, $3);
        }
        | expression MUL expression
        {
            $$ = makeExpression(BinaryExpression, MUL, $1, $3);
        }
        | expression DIV expression
        {
            $$ = makeExpression(BinaryExpression, DIV, $1, $3);
        }
        | expression MOD expression
        {
            $$ = makeExpression(BinaryExpression, MOD, $1, $3);
        }
        | expression EQ expression
        {
            $$ = makeExpression(BinaryExpression, EQ, $1, $3);
        }
        | expression NE expression
        {
            $$ = makeExpression(BinaryExpression, NE, $1, $3);
        }
        | expression GT expression
        {
            $$ = makeExpression(BinaryExpression, GT, $1, $3);
        }
        | expression GE expression
        {
            $$ = makeExpression(BinaryExpression, GE, $1, $3);
        }
        | expression LT expression
        {
            $$ = makeExpression(BinaryExpression, LT, $1, $3);
        }
        | expression LE expression
        {
            $$ = makeExpression(BinaryExpression, LE, $1, $3);
        }
        | expression LOGICAL_AND expression
        {
            $$ = makeExpression(BinaryExpression, AND, $1, $3);
        }
        | expression LOGICAL_OR expression
        {
            $$ = makeExpression(BinaryExpression, OR, $1, $3);
        }
        ;
    unary_expression: SUB expression %prec UMINUS
        {
            $$ = makeExpression(UnaryExpression, NEGAT, $2);
        }
        | EXCLAMATION expression %prec UMINUS
        {
            $$ = makeExpression(UnaryExpression, NOT, $2);
        }
        ;
    function_call_expression: expression LP argument_list RP
        {
            $$ = makeExpression(FunctionCallExpression, $1, std::move($3));
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
    expression_list: expression
        {
            $$.emplace_back($1);
        }
        | expression_list COMMA expression
        {
            $1.emplace_back($3);
            $$.swap($1);
        }
        ;
    type_tag: VAR
        {
            $$ = 0;
        }
        | INT
        {
            $$ = 2;
        }
        | DOUBLE
        {
            $$ = 3;
        }
        | BOOL
        {
            $$ = 4;
        }
        | STRING
        {
            $$ = 5;
        }
        ;
    block: LC statement_list RC
        {
            $$ = makeStatement(BlockStatement, std::move($2));
        }
        | LC RC
        {
            $$ = makeStatement(BlockStatement, StatementList());
        }
        ;
    argument_list: /* empty */
        {
            $$;
        }
        | expression
        {
            $$.emplace_back($1);
        }
        | argument_list COMMA expression
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
    parameter_list: /* empty */
        {
            $$;
        }
        | parameter
        {
            $$.emplace_back(std::move($1));
        }
        | parameter_list COMMA parameter
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