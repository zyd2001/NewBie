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

helpStruct::helpStruct(const int &i) : type(2), ptr(i) {}
helpStruct::helpStruct(const double &i) : type(3), ptr(i) {}
helpStruct::helpStruct(const bool &i) : type(4), ptr(i) {}
helpStruct::helpStruct(const std::string &i) : type(5), ptr(String(i)) {}
helpStruct::helpStruct(const String &i) : type(5), ptr(String(i)) {}

int zyd2001::NewBie::object_container_t::getInt()
{
    return obj->useNativePointer<int>();
}

double zyd2001::NewBie::object_container_t::getDouble()
{
    return obj->useNativePointer<double>();
}

bool zyd2001::NewBie::object_container_t::getBool()
{
    return obj->useNativePointer<bool>();
}

std::string zyd2001::NewBie::object_container_t::getString()
{
    return obj->useNativePointer<String>().toStr();
}

#define intBiOp(name, op)\
ObjectContainer int ## name (Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)\
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
#define intBiOpD(name, op)\
ObjectContainer int ## name ## D (Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)\
{\
    int &i = args[0]->get()->useNativePointer<int>();\
    double &d = args[1]->get()->useNativePointer<double>();\
    return new object_t(runner.getInter(), i op d);\
}
intBiOpD(Add, +)
intBiOpD(Sub, -)
intBiOpD(Mul, *)
intBiOpD(Div, /)
ObjectContainer intComp(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//int, int
    int &i1 = args[0]->get()->useNativePointer<int>();
    int &i2 = args[1]->get()->useNativePointer<int>();
    return new object_t(runner.getInter(), i1 - i2);
}
ObjectContainer intNegate(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//int
    int &i = args[0]->get()->useNativePointer<int>();
    return new object_t(runner.getInter(), -i);
}
ObjectContainer intCopy(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//int
    int &i = args[0]->get()->useNativePointer<int>();
    return new object_t(runner.getInter(), i);
}
ObjectContainer intCalli(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//int, int
    int &i = args[0]->get()->useNativePointer<int>();
    int &arg = args[1]->get()->useNativePointer<int>();
    return new object_t(runner.getInter(), i * arg);
}
ObjectContainer intCalld(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//int, double
    int &i = args[0]->get()->useNativePointer<int>();
    double &arg = args[1]->get()->useNativePointer<double>();
    return new object_t(runner.getInter(), i * arg);
}
ObjectContainer intToBool(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//int
    int &i = args[0]->get()->useNativePointer<int>();
    return new object_t(runner.getInter(), bool(i));
}
ObjectContainer intToString(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//int
    int &i = args[0]->get()->useNativePointer<int>();
    return new object_t(runner.getInter(), std::to_string(i));
}
void * intPtrDeleter(void * i)
{
    delete static_cast<int*>(i);
}

#define doubleBiOp(name, op) \
ObjectContainer double ## name (Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)\
{\
    double &i1 = args[0]->get()->useNativePointer<double>();\
    double &i2 = args[1]->get()->useNativePointer<double>();\
    return new object_t(runner.getInter(), i1 op i2);\
}
doubleBiOp(Add, +)
doubleBiOp(Sub, -)
doubleBiOp(Mul, *)
doubleBiOp(Div, /)
#define doubleBiOpI(name, op)\
ObjectContainer double ## name (Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)\
{\
    double &i1 = args[0]->get()->useNativePointer<double>();\
    int &i2 = args[1]->get()->useNativePointer<int>();\
    return new object_t(runner.getInter(), i1 op i2);\
}
doubleBiOpI(Add, +)
doubleBiOpI(Sub, -)
doubleBiOpI(Mul, *)
doubleBiOpI(Div, /)
ObjectContainer doubleComp(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
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
ObjectContainer doubleNegate(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//double
    double &i = args[0]->get()->useNativePointer<double>();
    return new object_t(runner.getInter(), -i);
}
ObjectContainer doubleCopy(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//double
    double &i = args[0]->get()->useNativePointer<double>();
    return new object_t(runner.getInter(), i);
}
ObjectContainer doubleCalli(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//double, int
    double &d = args[0]->get()->useNativePointer<double>();
    int &i = args[1]->get()->useNativePointer<int>();
    return new object_t(runner.getInter(), i * d);
}
ObjectContainer doubleCalld(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//double, double
    double &d = args[0]->get()->useNativePointer<double>();
    double &i = args[1]->get()->useNativePointer<double>();
    return new object_t(runner.getInter(), i * d);
}
ObjectContainer doubleToBool(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//double
    double &i = args[0]->get()->useNativePointer<double>();
    return new object_t(runner.getInter(), bool(i));
}
ObjectContainer doubleToString(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//double
    double &i = args[0]->get()->useNativePointer<double>();
    return new object_t(runner.getInter(), std::to_string(i));
}
void * doublePtrDeleter(void * i)
{
    delete static_cast<double*>(i);
}

ObjectContainer booleanCopy(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//bool
    bool &i = args[0]->get()->useNativePointer<bool>();
    return new object_t(runner.getInter(), i);
}
ObjectContainer booleanToString(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
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

ObjectContainer stringAdd(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//string, string
    String &s1 = args[0]->get()->useNativePointer<String>();
    String &s2 = args[1]->get()->getVariable(Identifier("toString"))()->get()->useNativePointer<String>();
    return new object_t(runner.getInter(), s1 + s2);
}
ObjectContainer stringMul(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//string, string
    String &s = args[0]->get()->useNativePointer<String>();
    int &i = args[1]->get()->useNativePointer<int>();
    std::basic_ostringstream<char_t> os;
    for (int j = 0; j < i; j++)
        os << s.get();
    return new object_t(runner.getInter(), os.str());
}
ObjectContainer stringComp(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
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
ObjectContainer stringToBool(Runner &runner, std::vector<ObjectContainer> &args, object_t * obj)
{//string
    String &s = args[0]->get()->useNativePointer<String>();
    return new object_t(runner.getInter(), !s.get().empty());
}
void * stringPtrDeleter(void * p)
{
    delete static_cast<String*>(p);
}

ObjectContainer zyd2001::NewBie::NormalFunction::call(Runner &runner, Args & args)
{
    runner.execute(s);
    return runner.returnVal();
}

ObjectContainer zyd2001::NewBie::NativeFunction::call(Runner &runner, Args & args)
{
    return native_func(runner, args, obj);
}

ObjectContainer zyd2001::NewBie::function_t::call(Runner & runner, Args & args)
{
    ParameterList &plist = runner.argsToParams(args);
    if (can_overload)
    {
        auto f = overload_map.find(plist);
        if (f != overload_map.end())
        {
            newNewBieStack();
            newNewBieScope();
            useNewBieFunc(f->second);
            for (int i = 0; i < args.size(); i++)
            {
                if (!f->first[i].ref)
                    runner.addVariable(f->first[i].identifier, f->first[i].type, args[i], f->first[i].cons);
                else
                    runner.addRefVariable(f->first[i].identifier, args[i]);
            }
            return f->second->call(runner, args);
        }
        else
            throw exception();
    }
    else
    {
        auto f = overload_map.begin();
        newNewBieStack();
        newNewBieScope();
        useNewBieFunc(f->second);
        for (int i = 0; i < args.size(); i++)
        {
            if (!f->first[i].ref)
                runner.addVariable(f->first[i].identifier, f->first[i].type, args[i], f->first[i].cons);
            else
                runner.addRefVariable(f->first[i].identifier, args[i]);
        }
        return f->second->call(runner, args);
    }
}

ObjectContainer zyd2001::NewBie::function_t::call(Runner & runner, ArgumentList & alist)
{
    return call(runner, runner.resolveArgumentList(alist));
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

zyd2001::NewBie::object_t::object_t(InterpreterImp * inter, const std::string &)
{}

zyd2001::NewBie::object_t::object_t(InterpreterImp * inter, const String &)
{}

Class intClass = make_shared<NativeClass>();
Class doubleClass = make_shared<NativeClass>();
Class booleanClass = make_shared<NativeClass>();
Class stringClass = make_shared<NativeClass>();

std::array<Class, 4> primitive_class = { intClass, doubleClass, booleanClass, stringClass };

String::String() : ptr(new basic_string<char_t>()) {}
String::String(const std::string &s) : ptr(new basic_string<char_t>(conv.from_bytes(s))) {}
String::String(const char_t *str) : ptr(new basic_string<char_t>(str)) {}
String::String(const basic_string<char_t> &str) : ptr(new basic_string<char_t>(str)) {}
String::String(const String &str) : ptr(str.ptr) {}
String::~String() {delete ptr;}
basic_string<char_t> &String::get() { return *ptr; }
std::string String::toStr() { return conv.to_bytes(*ptr); }

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