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
	Parser::symbol_type yylex(zyd2001::NewBie::InterpreterImp &inter, yyscan_t yyscanner);
}

%no-lines
%define api.namespace {zyd2001::NewBie}
%define api.value.type variant
%define api.token.constructor
%define api.token.prefix {TOKEN_}
%define parse.trace
%define parse.error verbose
%param {zyd2001::NewBie::InterpreterImp &inter}
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
%token <zyd2001::NewBie::Expression> INT_LITERAL STRING_LITERAL DOUBLE_LITERAL BOOL_LITERAL
%token <zyd2001::NewBie::Identifier>     IDENTIFIER
%token END  0  "end of file"
        INT DOUBLE BOOL STRING ARRAY VAR GLOBAL IF ELSE ELSEIF FOR IN CLASS RETURN BREAK CONTINUE
        LP RP LC RC LB RB SEMICOLON COMMA ASSIGN EXCLAMATION DOT
        ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
        INCREMENT DECREMENT PUBLIC PROTECTED PRIVATE REVERSE
%type<zyd2001::NewBie::Expression> expression function_call_expression primary_expression expression_optional binary_expression unary_expression
%type<zyd2001::NewBie::Statement> statement block
%type<zyd2001::NewBie::StatementsList> statements_list
%type<zyd2001::NewBie::ArgumentsList> arguments_list
%type<zyd2001::NewBie::ParametersList> parameters_list
%type<zyd2001::NewBie::ExpressionsList> expressions_list
%type<zyd2001::NewBie::ValueType> type_tag
%type<zyd2001::NewBie::Parameter> parameter
%type<zyd2001::NewBie::DeclarationStatementItem> declaration_item
%type<zyd2001::NewBie::DeclarationStatementItemList> declaration_item_list
%%
    eof: statements_list END
		{
			inter.statements_list = std::move($1);
		}
		;
    statements_list: statement
        {
            $$.push_back($1);
        }
        | statements_list statement
        {
            $1.push_back($2);
            $$.swap($1);
        }
        ;
    statement: expression SEMICOLON
        {
            $$ = Statement(EXPRESSION_STATEMENT, new ExpressionStatement(std::move($1)), yyget_lineno(scanner));
        }
        | IDENTIFIER ASSIGN expression SEMICOLON
        {
            $$ = Statement(ASSIGNMENT_STATEMENT, new (AssignmentStatement){std::move($1), std::move($3)}, yyget_lineno(scanner));
        }
        | type_tag declaration_item_list SEMICOLON
        {
            $$ = Statement(DECLARATION_STATEMENT, new (DeclarationStatement){std::move($1), std::move($2), false}, yyget_lineno(scanner));
        }
		| GLOBAL type_tag declaration_item_list SEMICOLON
        {
            $$ = Statement(DECLARATION_STATEMENT, new (DeclarationStatement){std::move($2), std::move($3), true}, yyget_lineno(scanner));
        }
        | IF LP expression RP statement
        {
            current_if = new (IfStatement){std::move($3), std::move($5)};
            $$ = Statement(IF_STATEMENT, current_if, yyget_lineno(scanner));
        }
        | ELSE statement
        {
            current_if->else_stat = std::move($2);
            $$ = Statement();
        }
        | ELSEIF LP expression RP statement
        {
            current_if->elseif.push_back({std::move($3), std::move($5)});
            $$ = Statement();
        }
        | FOR LP expression_optional SEMICOLON expression_optional SEMICOLON expression_optional RP statement
        {
            $$ = Statement(FOR_STATEMENT, new (ForStatement){std::move($3), std::move($5), std::move($7), std::move($9)}, yyget_lineno(scanner));
        }
        | RETURN expression SEMICOLON
        {
            $$ = Statement(RETURN_STATEMENT, new ReturnStatement(std::move($2)), yyget_lineno(scanner));
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
            $$ = Statement();
        }
        | block
        {
            $$ = std::move($1);
        }
        ;
    declaration_item: IDENTIFIER 
        {
            $$ = {std::move($1)};
        }
        | IDENTIFIER ASSIGN expression
        {
            $$ = {std::move($1), std::move($3)};
        }
        ;
    declaration_item_list: declaration_item
        {
            $$.push_back($1);
        }
        | declaration_item_list COMMA declaration_item
        {
            $1.push_back($3);
            $$.swap($1);
        }
        ;
    expression: binary_expression
        {
            $$ = std::move($1);
        }
        | unary_expression
        {
            $$ = std::move($1);
        }
        | primary_expression
        {
            $$ = std::move($1);
        }
        | function_call_expression
        {
            $$ = std::move($1);
        }
        | IDENTIFIER
        {
            $$ = Expression(IDENTIFIER_EXPRESSION, new IdentifierExpression(std::move($1)));
        }
        | LP expression RP
        {
            $$ = std::move($2);
        }
        ;
    expression_optional: /* empty */
        {
            $$ = Expression();
        }
        | expression
        ;
    binary_expression: expression ADD expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){ADD, std::move($1), std::move($3)});
        }
        | expression SUB expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){SUB, std::move($1), std::move($3)});
        }
        | expression MUL expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){MUL, std::move($1), std::move($3)});
        }
        | expression DIV expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){DIV, std::move($1), std::move($3)});
        }
        | expression MOD expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){MOD, std::move($1), std::move($3)});
        }
        | expression EQ expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){EQ, std::move($1), std::move($3)});
        }
        | expression NE expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){NE, std::move($1), std::move($3)});
        }
        | expression GT expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){GT, std::move($1), std::move($3)});
        }
        | expression GE expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){GE, std::move($1), std::move($3)});
        }
        | expression LT expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){LT, std::move($1), std::move($3)});
        }
        | expression LE expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){LE, std::move($1), std::move($3)});
        }
        | expression LOGICAL_AND expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){AND, std::move($1), std::move($3)});
        }
        | expression LOGICAL_OR expression
        {
            $$ = Expression(BINARY_EXPRESSION, new (BinaryExpression){OR, std::move($1), std::move($3)});
        }
        ;
    unary_expression: SUB expression %prec UMINUS
        {
            $$ = Expression(UNARY_EXPRESSION, new (UnaryExpression){MINUS, std::move($2)});
        }
        | EXCLAMATION expression %prec UMINUS
        {
            $$ = Expression(UNARY_EXPRESSION, new (UnaryExpression){NOT, std::move($2)});
        }
        ;
    function_call_expression: IDENTIFIER LP arguments_list RP
        {
            $$ = Expression(FUNCTION_CALL_EXPRESSION, new (FunctionCallExpression){$1, $3});
        }
        ;
    primary_expression: INT_LITERAL
        {
            $$ = std::move($1);
        }
        | DOUBLE_LITERAL
        {
            $$ = std::move($1);
        }
        | STRING_LITERAL
        {
            $$ = std::move($1);
        }
        | BOOL_LITERAL
        {
            $$ = std::move($1);
        }
        ;
    expressions_list: expression
        {
            $$.push_back($1);
        }
        | expressions_list COMMA expression
        {
            $1.push_back($3);
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
            $$ = VARIOUS_TYPE;
        }
        ;
    block: LC statements_list RC
        {
            $$ = Statement(BLOCK_STATEMENT, new BlockStatement($2), yyget_lineno(scanner));
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
            $$.push_back($1);
        }
        | arguments_list COMMA expression
        {
            $1.push_back($3);
            $$.swap($1);
        }
        ;
    parameter: type_tag IDENTIFIER primary_expression
        {
            $$ = {$1, $2, $3};
        }
        ;
    parameters_list: /* empty */
        {
            $$;
        }
        | parameter
        {
            $$.push_back($1);
        }
        | parameters_list COMMA parameter
        {
            $1.push_back($3);
            $$.swap($1);
        }
        ;
%%

void Parser::error(const location_type& l, const std::string& m)
{
	std::cerr << "At file " << l.begin.filename  << " " << l << " " << m << endl;
}