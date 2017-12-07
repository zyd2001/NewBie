#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

#define delete_cast(...) delete static_cast<__VA_ARGS__>(content)
#define replace(...) do {delete_cast(__VA_ARGS__); content = ptr;} while(0)

Expression::Expression() : type(NULL_EXPRESSION), content(nullptr) {}
Expression::Expression(Expression &&e) : type(e.type), content(e.content)
{
    e.type = NULL_EXPRESSION;
}
Expression &Expression::operator=(Expression &&e)
{
    this->swap(e);
    return *this;
}
Expression &Expression::operator=(const Expression &e)
{
    if (this == &e)
        return *this;
    Expression temp(e);
    this->swap(temp);
    return *this;
}
void zyd2001::NewBie::Expression::swap(Expression &e)
{
    std::swap(type, e.type);
    std::swap(content, e.content);
}
Expression::Expression(const Expression &e) : type(e.type)
{
    switch (type)
    {
        case zyd2001::NewBie::NULL_EXPRESSION:
            break;
        case zyd2001::NewBie::LITERAL_EXPRESSION:
        {
            Value *ptr = new Value(e.get<Value>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::IDENTIFIER_EXPRESSION:
        {
            IdentifierExpression *ptr = new IdentifierExpression(e.get<IdentifierExpression>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::BINARY_EXPRESSION:
        {
            BinaryExpression *ptr = new BinaryExpression(e.get<BinaryExpression>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::UNARY_EXPRESSION:
        {
            UnaryExpression *ptr = new UnaryExpression(e.get<UnaryExpression>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::FUNCTION_CALL_EXPRESSION:
        {
            FunctionCallExpression *ptr = new FunctionCallExpression(e.get<FunctionCallExpression>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::ARRAY_EXPRESSION:
            break;
        case zyd2001::NewBie::INDEX_EXPRESSION:
            break;
        default:
            break;
    }
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
Statement::Statement(Statement &&s) : type(s.type), content(s.content), lineno(s.lineno)
{
    s.type = NULL_STATEMENT;
}
Statement::Statement(const Statement &s) : type(s.type), lineno(s.lineno)
{
    switch (type)
    {
        case zyd2001::NewBie::NULL_STATEMENT:
            break;
        case zyd2001::NewBie::EXPRESSION_STATEMENT:
        {
            Expression *ptr = new Expression(s.get<Expression>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::ASSIGNMENT_STATEMENT:
        {
            AssignmentStatement *ptr = new AssignmentStatement(s.get<AssignmentStatement>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::DECLARATION_STATEMENT:
        {
            DeclarationStatement *ptr = new DeclarationStatement(s.get<DeclarationStatement>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::BLOCK_STATEMENT:
        {
            BlockStatement *ptr = new BlockStatement(s.get<BlockStatement>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::IF_STATEMENT:
        {
            IfStatement *ptr = new IfStatement(s.get<IfStatement>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::FOR_STATEMENT:
        {
            ForStatement *ptr = new ForStatement(s.get<ForStatement>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::FOREACH_STATEMENT:
        {
            ForeachStatement *ptr = new ForeachStatement(s.get<ForeachStatement>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::RETURN_STATEMENT:
        {
            ReturnStatement *ptr = new ReturnStatement(s.get<ReturnStatement>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::CONTINUE_STATEMENT:
            break;
        case zyd2001::NewBie::BREAK_STATEMENT:
            break;
        default:
            break;
    }
}
Statement &Statement::operator=(Statement &&s)
{
    this->swap(s);
    return *this;
}
Statement & zyd2001::NewBie::Statement::operator=(const Statement &s)
{
    if (this == &s)
        return *this;
    Statement temp(s);
    this->swap(temp);
    return *this;
}
void zyd2001::NewBie::Statement::swap(Statement &s)
{
    std::swap(type, s.type);
    std::swap(content, s.content);
    std::swap(lineno, s.lineno);
}
Statement::Statement(StatementType t, void *ptr, int l) : type(t), content(ptr), lineno(l) {}
Statement::~Statement()
{
    switch (type)
    {
        case zyd2001::NewBie::EXPRESSION_STATEMENT:
            delete_cast(Expression*);
            break;
        case zyd2001::NewBie::DECLARATION_STATEMENT:
            delete_cast(DeclarationStatement*);
            break;
        case zyd2001::NewBie::ASSIGNMENT_STATEMENT:
            delete_cast(AssignmentStatement*);
            break;
        case zyd2001::NewBie::BLOCK_STATEMENT:
            delete_cast(StatementsList*);
            break;
        case zyd2001::NewBie::IF_STATEMENT:
            delete_cast(IfStatement*);
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