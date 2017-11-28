#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

#define delete_cast(...) delete static_cast<__VA_ARGS__>(content)

Expression::Expression() : type(NULL_EXPRESSION), content(nullptr) {}
Expression::Expression(Expression &&e) : type(e.type), content(e.content)
{
	e.type = NULL_EXPRESSION;
}
Expression &Expression::operator=(Expression &&e)
{
	type = e.type;
	content = e.content;
	e.type = NULL_EXPRESSION;
	return *this;
}
Expression::Expression(ExpressionType t, void *ptr) : type(t), content(ptr) {}
Expression::~Expression()
{
	switch (type)
	{
		case zyd2001::NewBie::LITERAL_EXPRESSION:
			delete_cast(LiteralExpression*);
			break;
		case zyd2001::NewBie::IDENTIFIER_EXPRESSION:
			delete_cast(IdentifierExpression*);
			break;
		case zyd2001::NewBie::BINARY_EXPRESSION:
			delete_cast(BinaryExpression*);
			break;
		case zyd2001::NewBie::UNARY_EXPRESSION:
			delete_cast(UnaryExpression*);
			break;
		case zyd2001::NewBie::FUNCTION_CALL_EXPRESSION:
			delete_cast(FunctionCallExpression*);
			break;
		case zyd2001::NewBie::ARRAY_EXPRESSION:
			delete_cast(ArrayExpression*);
			break;
		case zyd2001::NewBie::INDEX_EXPRESSION:
			delete_cast(IndexExpression*);
			break;
		default:
			break;
	}
}

Statement::Statement() : type(NULL_STATEMENT), content(nullptr) {}
Statement::Statement(Statement &&s) : type(s.type), content(s.content)
{
	s.type = NULL_STATEMENT;
}
Statement &Statement::operator=(Statement &&s)
{
	type = s.type;
	content = s.content;
	s.type = NULL_STATEMENT;
	return *this;
}
Statement::Statement(StatementType t, void *ptr) : type(t), content(ptr) {}
Statement::~Statement()
{
	switch (type)
	{
		case zyd2001::NewBie::EXPRESSION_STATEMENT:
			delete_cast(Expression*);
			break;
		case zyd2001::NewBie::FUNCTION_DEFINITION_STATEMENT:
			break;
		case zyd2001::NewBie::CLASS_DEFINITION_STATEMENT:
			break;
		case zyd2001::NewBie::BLOCK_STATEMENT:
			delete_cast(StatementsList*);
			break;
		case zyd2001::NewBie::IF_STATEMENT:
			delete_cast(IfStatement*);
			break;
		case zyd2001::NewBie::ELSE_STATEMENT:
			break;
		case zyd2001::NewBie::FOR_STATEMENT:
			delete_cast(ForStatement*);
			break;
		case zyd2001::NewBie::FOREACH_STATEMENT:
			delete_cast(ForeachStatement*);
			break;
		case zyd2001::NewBie::RETURN_STATEMENT:
			delete_cast(ReturnStatement*);
			break;
		case zyd2001::NewBie::CONTINUE_STATEMENT:
			break;
		case zyd2001::NewBie::BREAK_STATEMENT:
			break;
		default:
			break;
	}
}