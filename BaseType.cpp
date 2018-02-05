#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

#define delete_cast(...) delete static_cast<__VA_ARGS__>(content)
#define replace(...) do {delete_cast(__VA_ARGS__); content = ptr;} while(0)

extern InterpreterImp *inter;

Expression::Expression() : type(NULL_EXPRESSION), content(nullptr), ref_count(new int(1)) {}
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
    std::swap(ref_count, e.ref_count);
}
Expression::Expression(const Expression &e) : type(e.type), ref_count(e.ref_count), content(e.content)
{
    (*ref_count)++;
}
Expression::Expression(ExpressionType t, void *ptr) : type(t), content(ptr), ref_count(new int(1)) {}
Expression::~Expression()
{
    (*ref_count)--;
    if (*ref_count == 0)
    {
        delete ref_count;
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
            case NEW_OBJECT_EXPRESSION:
            case zyd2001::NewBie::FUNCTION_CALL_EXPRESSION:
                delete_cast(FunctionCallExpression*);
                break;
            case zyd2001::NewBie::ARRAY_EXPRESSION:
                delete_cast(ArrayExpression*);
                break;
            case ARRAY_LENGTH_EXPRESSION:
                delete_cast(Expression*);
                break;
            case zyd2001::NewBie::INDEX_EXPRESSION:
                delete_cast(IndexExpression*);
                break;
            case DOT_EXPRESSION:
                delete_cast(DotExpression*);
                break;
            default:
                break;
        }
    }
}

Statement::Statement() : type(NULL_STATEMENT), content(nullptr), ref_count(new int(1)) {}
Statement::Statement(const Statement &s) : type(s.type), lineno(s.lineno), ref_count(s.ref_count), content(s.content)
{
    (*ref_count)++;
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
    std::swap(ref_count, s.ref_count);
}
Statement::Statement(StatementType t, void *ptr, int l) : type(t), content(ptr), lineno(l), ref_count(new int(1)) {}
Statement::~Statement()
{
    (*ref_count)--;
    if (*ref_count == 0)
    {
        delete ref_count;
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
            case FUNCTION_DEFINITION_STATEMENT:
                delete_cast(VariableMap::value_type*);
                break;
            case zyd2001::NewBie::BLOCK_STATEMENT:
                delete_cast(StatementList*);
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
            case DEBUG_STATEMENT:
                delete_cast(DebugStatement*);
            default:
                break;
        }
    }
}

string_t::string_t() : ptr(make_shared<basic_string<char_t>>()) {}
string_t::string_t(const char_t *str) : ptr(make_shared<basic_string<char_t>>(str)) {}
string_t::string_t(const basic_string<char_t> &str) : ptr(make_shared<basic_string<char_t>>(str)) {}
string_t::string_t(const string_t &str) : ptr(str.ptr) {}
basic_string<char_t> &string_t::get() { return *ptr; }

string_t string_t::operator+(const string_t &str)
{
    return string_t(*(this->ptr) + *str.ptr);
}
string_t &string_t::operator+=(const string_t &str)
{
    *(this->ptr) += *str.ptr;
    return *this;
}
string_t &string_t::operator=(const string_t &str)
{
    string_t s(str);
    std::swap(s.ptr, ptr);
    return *this;
}
bool string_t::operator==(const string_t &str) const
{
    return *(this->ptr) == *str.ptr;
}

size_t zyd2001::NewBie::string_t::hash::operator()(const string_t &s) const
{
    return h(*s.ptr);
}

bool ParamsEqualTo::operator()(const ParameterList& lhs, const ParameterList& rhs) const
{
    if (lhs.size() != rhs.size())
        return false;
    else
    {
        for (int i = 0; i < lhs.size(); i++)
        {
            if (lhs[i].type != rhs[i].type)
                return false;
        }
        return true;
    }
}

std::size_t ParamsHash::operator()(const ParameterList& p) const
{
    std::hash<ValueType> h;
    std::size_t seed = 0;
    for (auto &i : p)
    {
        seed ^= h(i.type) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

GraphNode::GraphNode(object_t *o) : ptr(o), ref_count(0) {}

zyd2001::NewBie::Object::Object(GraphNode *n) : node(n) 
{
    node->ref_count++;
}
Object::Object(const Object &o) : node(o.node) 
{
    node->ref_count++;
}
object_t &zyd2001::NewBie::Object::operator*()
{
    return *node->ptr;
}
object_t * zyd2001::NewBie::Object::operator->()
{
    return node->ptr;
}
zyd2001::NewBie::Object::~Object()
{
    if (node->ref_count != 0)
    {
        node->ref_count--;
        if (node->ref_count == 0)
            delete node->ptr;
    }
}

Object zyd2001::NewBie::NormalClass::makeObject(ArgumentList &)
{

}

Value & zyd2001::NewBie::NormalFunction::call(ArgumentList &)
{
    // TODO: 在此处插入 return 语句
}

Value InterpreterImp::callFunc(Function &func, ArgumentList &alist)
{
    //initialize the function local variables
    StatementList temp_slist;
    vector<Expression> temp_elist;
    ParameterList temp_plist;
    for (auto &arg : alist)
    {
        temp_elist.emplace_back(Expression(LITERAL_EXPRESSION, new Value(evaluate(arg))));
        temp_plist.emplace_back(Parameter());
        temp_plist.back().type = temp_elist.back().get<LiteralExpression>().type;
    }

    variables_stack.push(make_stack_unit());
    (*variables_stack.top()).push_back(VariableMap());
    decltype(func->overload_map.begin()) fbody;

    if (func->can_overload)
    {
        fbody = func->overload_map.find(temp_plist);
        if (fbody == func->overload_map.cend())
            err();
    }
    else
        fbody = func->overload_map.begin();

    auto eiter = temp_elist.cbegin();
    for (auto param = fbody->first.cbegin(); param != fbody->first.cend(); param++)
    {
        DeclarationStatementItemList item;
        if (eiter != temp_elist.cend())
        {
            item.emplace_back(std::move(DeclarationStatementItem{ std::move(param->identifier), *eiter }));
            eiter++;
        }
        else
            item.emplace_back(std::move(DeclarationStatementItem{ std::move(param->identifier), param->default_value_exp }));
        Statement temp(DECLARATION_STATEMENT, new (DeclarationStatement){ false, param->type, item }, -1);
        execute(temp);
    }

    interpret(fbody->second.get<BlockStatement>());
    variables_stack.pop();

    return temp_variable;
}