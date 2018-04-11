#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

#include <codecvt>
#include <locale>
#include <cstdio>
#include <sstream>

using namespace zyd2001::NewBie;
using namespace std;

#if defined(_MSC_VER)
wstring_convert<codecvt_utf8<char_t>, char_t> conv;
#elif defined(__GNUC__)
wstring_convert<codecvt_utf8<char_t>, char_t> conv;
#endif

//extern InterpreterImp *inter;

//Expression::Expression() : type(NULL_EXPRESSION), content(nullptr), ref_count(new int(1)) {}
//zyd2001::NewBie::Expression::Expression(Object o) : type(LITERAL_EXPRESSION), ref_count(new int(1)), content(new Object(o)) {}
//Expression &Expression::operator=(const Expression &e)
//{
//    if (this == &e)
//        return *this;
//    Expression temp(e);
//    this->swap(temp);
//    return *this;
//}
//void zyd2001::NewBie::Expression::swap(Expression &e)
//{
//    std::swap(type, e.type);
//    std::swap(content, e.content);
//    std::swap(ref_count, e.ref_count);
//}
//Expression::Expression(const Expression &e) : type(e.type), ref_count(e.ref_count), content(e.content)
//{
//    (*ref_count)++;
//}
//Expression::Expression(ExpressionType t, void *ptr) : type(t), content(ptr), ref_count(new int(1)) {}
//Expression::~Expression()
//{
//    (*ref_count)--;
//    if (*ref_count == 0)
//    {
//        delete ref_count;
//        switch (type)
//        {
//            case zyd2001::NewBie::LITERAL_EXPRESSION:
//                delete_cast(LiteralExpression*);
//                break;
//            case zyd2001::NewBie::IDENTIFIER_EXPRESSION:
//                delete_cast(IdentifierExpression*);
//                break;
//            case zyd2001::NewBie::BINARY_EXPRESSION:
//                delete_cast(BinaryExpression*);
//                break;
//            case zyd2001::NewBie::UNARY_EXPRESSION:
//                delete_cast(UnaryExpression*);
//                break;
//            case NEW_OBJECT_EXPRESSION:
//            case zyd2001::NewBie::FUNCTION_CALL_EXPRESSION:
//                delete_cast(FunctionCallExpression*);
//                break;
//            case zyd2001::NewBie::ARRAY_EXPRESSION:
//                delete_cast(ArrayExpression*);
//                break;
//            case ARRAY_LENGTH_EXPRESSION:
//                delete_cast(Expression*);
//                break;
//            case zyd2001::NewBie::INDEX_EXPRESSION:
//                delete_cast(IndexExpression*);
//                break;
//            case DOT_EXPRESSION:
//                delete_cast(DotExpression*);
//                break;
//            default:
//                break;
//        }
//    }
//}
//
//Statement::Statement() : type(NULL_STATEMENT), content(nullptr), ref_count(new int(1)) {}
//Statement::Statement(const Statement &s) : type(s.type), lineno(s.lineno), ref_count(s.ref_count), content(s.content)
//{
//    (*ref_count)++;
//}
//Statement & zyd2001::NewBie::Statement::operator=(const Statement &s)
//{
//    if (this == &s)
//        return *this;
//    Statement temp(s);
//    this->swap(temp);
//    return *this;
//}
//void zyd2001::NewBie::Statement::swap(Statement &s)
//{
//    std::swap(type, s.type);
//    std::swap(content, s.content);
//    std::swap(lineno, s.lineno);
//    std::swap(ref_count, s.ref_count);
//}
//Statement::Statement(StatementType t, void *ptr, int l) : type(t), content(ptr), lineno(l), ref_count(new int(1)) {}
//Statement::~Statement()
//{
//    (*ref_count)--;
//    if (*ref_count == 0)
//    {
//        delete ref_count;
//        switch (type)
//        {
//            case zyd2001::NewBie::EXPRESSION_STATEMENT:
//                delete_cast(Expression*);
//                break;
//            case zyd2001::NewBie::DECLARATION_STATEMENT:
//                delete_cast(DeclarationStatement*);
//                break;
//            case zyd2001::NewBie::ASSIGNMENT_STATEMENT:
//                delete_cast(AssignmentStatement*);
//                break;
//            case FUNCTION_DEFINITION_STATEMENT:
//                delete_cast(Function*);
//                break;
//            case zyd2001::NewBie::BLOCK_STATEMENT:
//                delete_cast(StatementList*);
//                break;
//            case zyd2001::NewBie::IF_STATEMENT:
//                delete_cast(IfStatement*);
//                break;
//            case zyd2001::NewBie::FOR_STATEMENT:
//                delete_cast(ForStatement*);
//                break;
//            case zyd2001::NewBie::FOREACH_STATEMENT:
//                delete_cast(ForeachStatement*);
//                break;
//            case zyd2001::NewBie::RETURN_STATEMENT:
//                delete_cast(ReturnStatement*);
//                break;
//            case zyd2001::NewBie::CONTINUE_STATEMENT:
//                break;
//            case zyd2001::NewBie::BREAK_STATEMENT:
//                break;
//            case DEBUG_STATEMENT:
//                delete_cast(DebugStatement*);
//            default:
//                break;
//        }
//    }
//}

#define intBiOp(name, op)\
object_t * int ## name (Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)\
{\
    int &i1 = args[0]->get()->useNativePointer<int>();\
    int &i2 = args[1]->get()->useNativePointer<int>();\
    return new object_t(runner.getInter(), i1 op i2);\
}
intBiOp(Add, +)
intBiOp(Sub, -)
intBiOp(Mul, *)
intBiOp(Div, /)
intBiOp(Mod, %)
object_t * intComp(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//int, int
    int &i1 = args[0]->get()->useNativePointer<int>();
    int &i2 = args[1]->get()->useNativePointer<int>();
    return new object_t(runner.getInter(), i1 - i2);
}
object_t * intNegate(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//int
    int &i = args[0]->get()->useNativePointer<int>();
    return new object_t(runner.getInter(), -i);
}
object_t * intCopy(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//int
    int &i = args[0]->get()->useNativePointer<int>();
    return new object_t(runner.getInter(), i);
}
object_t * intCalli(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//int, int
    int &i = args[0]->get()->useNativePointer<int>();
    int &arg = args[1]->get()->useNativePointer<int>();
    return new object_t(runner.getInter(), i * arg);
}
object_t * intCalld(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//int, double
    int &i = args[0]->get()->useNativePointer<int>();
    double &arg = args[1]->get()->useNativePointer<double>();
    return new object_t(runner.getInter(), i * arg);
}
object_t * intToBool(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//int
    int &i = args[0]->get()->useNativePointer<int>();
    return new object_t(runner.getInter(), bool(i));
}
object_t * intToString(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//int
    int &i = args[0]->get()->useNativePointer<int>();
    return new object_t(runner.getInter(), std::to_string(i));
}
void * intPtrDeleter(void * i)
{
    delete static_cast<int*>(i);
}

#define doubleBiOp(name, op) \
object_t * double ## name (Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)\
{\
    double &i1 = args[0]->get()->useNativePointer<double>();\
    double &i2 = args[1]->get()->useNativePointer<double>();\
    return new object_t(runner.getInter(), i1 op i2);\
}
doubleBiOp(Add, +)
doubleBiOp(Sub, -)
doubleBiOp(Mul, *)
doubleBiOp(Div, /)
object_t * doubleComp(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//double, double
    double &i1 = args[0]->get()->useNativePointer<double>();
    double &i2 = args[1]->get()->useNativePointer<double>();
    if (i1 == i2)
        return new object_t(runner.getInter(), 0);
    else if (i1 > i2)
        return new object_t(runner.getInter(), 1);
    else
        return new object_t(runner.getInter(), -1);
}
object_t * doubleNegate(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//double
    double &i = args[0]->get()->useNativePointer<double>();
    return new object_t(runner.getInter(), -i);
}
object_t * doubleCopy(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//double
    double &i = args[0]->get()->useNativePointer<double>();
    return new object_t(runner.getInter(), i);
}
object_t * doubleCalli(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//double, int
    double &d = args[0]->get()->useNativePointer<double>();
    int &i = args[1]->get()->useNativePointer<int>();
    return new object_t(runner.getInter(), i * d);
}
object_t * doubleCalli(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//double, double
    double &d = args[0]->get()->useNativePointer<double>();
    double &i = args[1]->get()->useNativePointer<double>();
    return new object_t(runner.getInter(), i * d);
}
object_t * doubleToBool(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//double
    double &i = args[0]->get()->useNativePointer<double>();
    return new object_t(runner.getInter(), bool(i));
}
object_t * doubleToString(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//double
    double &i = args[0]->get()->useNativePointer<double>();
    return new object_t(runner.getInter(), std::to_string(i));
}
void * doublePtrDeleter(void * i)
{
    delete static_cast<double*>(i);
}

object_t * booleanCopy(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//bool
    bool &i = args[0]->get()->useNativePointer<bool>();
    return new object_t(runner.getInter(), i);
}
object_t * booleanToString(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//bool
    bool &i = args[0]->get()->useNativePointer<bool>();
    if (i)
        return new object_t(runner.getInter(), "true");
    else
        return new object_t(runner.getInter(), "false");
}
void * booleanPtrDeleter(void * i)
{
    delete static_cast<bool*>(i);
}

object_t * stringAdd(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//string, string
    String &s1 = args[0]->get()->useNativePointer<String>();
    String &s2 = args[1]->get()->getVariable(U("toString"))()->get()->useNativePointer<String>();
    return new object_t(runner.getInter(), s1 + s2);
}
object_t * stringMul(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//string, string
    String &s = args[0]->get()->useNativePointer<String>();
    int &i = args[1]->get()->useNativePointer<int>();
    std::basic_ostringstream<char_t> os;
    for (int j = 0; j < i; j++)
        os << s.get();
    return new object_t(runner.getInter(), os.str());
}
object_t * stringComp(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//string, string
    String &s1 = args[0]->get()->useNativePointer<String>();
    String &s2 = args[1]->get()->useNativePointer<String>();
    if (s1 == s2)
        return new object_t(runner.getInter(), 0);
    else if (s1 > s2)
        return new object_t(runner.getInter(), 1);
    else
        return new object_t(runner.getInter(), -1);
}
object_t * stringToBool(Runner &runner, std::vector<ObjectContainer> &args, class_t *cl)
{//string
    String &s = args[0]->get()->useNativePointer<String>();
    return new object_t(runner.getInter(), !s.get().empty());
}
void * stringPtrDeleter(void * p)
{
    delete static_cast<String*>(p);
}


zyd2001::NewBie::object_t::object_t(InterpreterImp * in, const int &i) : inter(in)
{
    native_ptr = new int(i);
    Class c = in->primitive_class[0];
    type = c->type;
    type_name = c->type_name;
    cl = c;
}

zyd2001::NewBie::object_t::object_t(InterpreterImp * inter, const double &)
{}

zyd2001::NewBie::object_t::object_t(InterpreterImp * inter, const bool &)
{}

zyd2001::NewBie::object_t::object_t(InterpreterImp * inter, std::string &)
{}

zyd2001::NewBie::object_t::object_t(InterpreterImp * inter, const String &)
{}

Class intClass = make_shared<NativeClass>();
Class doubleClass = make_shared<NativeClass>();
Class booleanClass = make_shared<NativeClass>();
Class stringClass = make_shared<NativeClass>();

std::array<Class, 4> primitive_class = { intClass, doubleClass, booleanClass, stringClass };

String::String() : ptr(make_shared<basic_string<char_t>>()) {}
String::String(const std::string &s) : ptr(make_shared<basic_string<char_t>>(conv.from_bytes(s))) {}
String::String(const char_t *str) : ptr(make_shared<basic_string<char_t>>(str)) {}
String::String(const basic_string<char_t> &str) : ptr(make_shared<basic_string<char_t>>(str)) {}
String::String(const String &str) : ptr(str.ptr) {}
basic_string<char_t> &String::get() { return *ptr; }

String String::operator+(const String &str)
{
    return String(*(this->ptr) + *str.ptr);
}
String &String::operator+=(const String &str)
{
    *(this->ptr) += *str.ptr;
    return *this;
}
String &String::operator=(const String &str)
{
    String s(str);
    std::swap(s.ptr, ptr);
    return *this;
}
bool String::operator==(const String &str) const
{
    if (this->ptr == str.ptr)
        return true;
    else
        return *(this->ptr) == *str.ptr;
}

bool zyd2001::NewBie::String::operator>(const String &s) const
{
    return *ptr > *s.ptr;
}

bool zyd2001::NewBie::String::operator<(const String &s) const
{
    return *ptr < *s.ptr;
}

String zyd2001::NewBie::String::copy()
{
    return String(get());
}

size_t zyd2001::NewBie::String::hash::operator()(const String &s) const
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
    std::hash<ObjectType> h;
    std::size_t seed = 0;
    for (auto &i : p)
        seed ^= h(i.type) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
}

String intToString(int &i)
{
    return String(std::to_string(i));
}

//Object zyd2001::NewBie::NormalFunction::call(Runner &runner, ArgumentList &alist)
//{
//    if (cl.get() != nullptr)
//    {
//        useClass(cl);
//        return real_call(runner, alist);
//    }
//    else if (obj != nullptr)
//    {
//        useObject(obj);
//        return real_call(runner, alist);
//    }
//    else
//        return real_call(runner, alist);
//}
//
//Object zyd2001::NewBie::NormalFunction::real_call(Runner &runner, ArgumentList &alist)
//{
//    if (can_overload)
//    {
//        auto args = inter->resolveArgumentList(alist);
//        auto func = overload_map.find(inter->ArgsToParams(args));
//        if (func != overload_map.end())
//        {
//            newVariablesStack();
//            for (int i = 0; i < func->first.size(); i++)
//                inter->declareVariable(func->first[i].identifier, func->first[i].type, args[i]);
//            return runner.execute(func->second);
//        }
//        else
//            throw exception();
//    }
//    else
//    {
//        auto args = inter->resolveArgumentList(alist);
//        auto func = overload_map.begin();
//        newVariablesStack();
//        for (int i = 0; i < func->first.size(); i++)
//            inter->declareVariable(func->first[i].identifier, func->first[i].type, (i < args.size() ? args[i] : func->first[i].default_value_exp->evaluate()));
//        return runner.execute(func->second);
//    }
//}
//
//Object zyd2001::NewBie::NativeFunction::call(Runner &runner, ArgumentList &alist)
//{
//    useObject(obj);
//    auto args = inter->resolveArgumentList(alist);
//    newVariablesStack();
//    if (can_overload)
//        return native_func.at(inter->ArgsToParams(args))(args, obj);
//    else
//        return native_func.begin()->second(args, obj);
//}
//
//Object zyd2001::NewBie::NativeStaticFunction::call(Runner &runner, ArgumentList &alist)
//{
//    useClass(cl);
//    auto args = inter->resolveArgumentList(alist);
//    newVariablesStack();
//    if (can_overload)
//        return native_func.at(inter->ArgsToParams(args))(args, cl);
//    else
//        return native_func.begin()->second(args, cl);
//}
//
////Value InterpreterImp::callFunc(Function &func, ArgumentList &alist)
////{
////    //initialize the function local variables
////    StatementList temp_slist;
////    vector<Expression> temp_elist;
////    ParameterList temp_plist;
////    for (auto &arg : alist)
////    {
////        temp_elist.emplace_back(Expression(LITERAL_EXPRESSION, new Value(evaluate(arg))));
////        temp_plist.emplace_back(Parameter());
////        temp_plist.back().type = temp_elist.back().get<LiteralExpression>().type;
////    }
////
////    variables_stack.push(make_stack_unit());
////    (*variables_stack.top()).push_back(VariableMap());
////    decltype(func->overload_map.begin()) fbody;
////
////    if (func->can_overload)
////    {
////        fbody = func->overload_map.find(temp_plist);
////        if (fbody == func->overload_map.cend())
////            err();
////    }
////    else
////        fbody = func->overload_map.begin();
////
////    auto eiter = temp_elist.cbegin();
////    for (auto param = fbody->first.cbegin(); param != fbody->first.cend(); param++)
////    {
////        DeclarationStatementItemList item;
////        if (eiter != temp_elist.cend())
////        {
////            item.emplace_back(std::move(DeclarationStatementItem{ std::move(param->identifier), *eiter }));
////            eiter++;
////        }
////        else
////            item.emplace_back(std::move(DeclarationStatementItem{ std::move(param->identifier), param->default_value_exp }));
////        Statement temp(DECLARATION_STATEMENT, new (DeclarationStatement){ false, param->type, item }, -1);
////        execute(temp);
////    }
////
////    interpret(fbody->second.get<BlockStatement>());
////    variables_stack.pop();
////
////    return temp_variable;
////}