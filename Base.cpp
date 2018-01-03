#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

#define delete_cast(...) delete static_cast<__VA_ARGS__>(content)
#define replace(...) do {delete_cast(__VA_ARGS__); content = ptr;} while(0)

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
                delete_cast(VariablesMap::value_type*);
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

bool ParamsEqualTo::operator()(const ParametersList& lhs, const ParametersList& rhs) const
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

std::size_t ParamsHash::operator()(const ParametersList& p) const
{
    std::hash<ValueType> h;
    std::size_t seed = 0;
    for (auto &i : p)
    {
        seed ^= h(i.type) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

void zyd2001::NewBie::disabled_deleter(vector<VariablesMap> *p) {}
void zyd2001::NewBie::enabled_deleter(vector<VariablesMap> *p) { delete p; }
stack_unit zyd2001::NewBie::make_stack_unit() { return unique_ptr<std::vector<VariablesMap>, deleter>(new std::vector<VariablesMap>(), &enabled_deleter); }
stack_unit zyd2001::NewBie::make_temp_unit(std::vector<VariablesMap> &u) { return unique_ptr<std::vector<VariablesMap>, deleter>(&u, &disabled_deleter); }
void InterpreterImp::initialize_obj_env(Value &o)
{
    auto &obj = o.get<Object>();
    in_object = true;
    current_object = &o;
    object_env_stack.push(current_object);
}
void InterpreterImp::restore_obj_env()
{
    object_env_stack.pop();
    if (object_env_stack.empty())
    {
        in_object = false;
        current_object = nullptr;
    }
    else
    {
        auto &env = object_env_stack.top();
        current_object = env;
    }
    //variables_stack.pop();
}

Value InterpreterImp::callFunc(Function &func, ArgumentsList &alist)
{
    //initialize the function local variables
    StatementsList temp_slist;
    vector<Expression> temp_elist;
    ParametersList temp_plist;
    for (auto &arg : alist)
    {
        temp_elist.emplace_back(Expression(LITERAL_EXPRESSION, new Value(evaluate(arg))));
        temp_plist.emplace_back(Parameter());
        temp_plist.back().type = temp_elist.back().get<LiteralExpression>().type;
    }

    variables_stack.push(make_stack_unit());
    (*variables_stack.top()).push_back(VariablesMap());
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
        DeclarationStatementItemsList item;
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

void InterpreterImp::addVar(Value &val)
{
}