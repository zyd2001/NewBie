#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

#include <codecvt>
#include <locale>
#include <cstdio>

using namespace zyd2001::NewBie;
using namespace std;

extern InterpreterImp *inter;

#if defined(_MSC_VER)
wstring_convert<codecvt_utf8<char_t>, char_t> conv;
#elif defined(__GNUC__)
wstring_convert<codecvt_utf8<char_t>, char_t> conv;
#endif

void zyd2001::NewBie::class_t::addStaticVariable(Identifier id, Object o, AccessControl a)
{
    inter->addGCEdge(inter->root, o);
    static_variables[id] = make_pair(o, a);
}

Object zyd2001::NewBie::class_t::getStaticVariable(Identifier id)
{
    auto v = static_variables.at(id);
    switch (v.second)
    {
        case PUBLIC:
        case READONLY:
            return v.first;
        case PRIVATE:
            if (inter->in_class && inter->current_class == this)
                return v.first;
            else
                throw exception();
    }
}

void zyd2001::NewBie::class_t::changeStaticVariable(Identifier id, Object o)
{
    auto v = static_variables.at(id);
    switch (v.second)
    {
        case PUBLIC:
            if (inter->typeCheck(v.first, o))
            {
                inter->delGCEdge(inter->root, v.first);
                v.first = o;
                inter->addGCEdge(inter->root, o);
            }
            else
                throw exception();
        case PRIVATE:
        case READONLY:
            if (inter->in_class && inter->current_class == this)
            {
                if (inter->typeCheck(v.first, o))
                {
                    inter->delGCEdge(inter->root, v.first);
                    v.first = o;
                    inter->addGCEdge(inter->root, o);
                }
                else
                    throw exception();
            }
            else
                throw exception();
    }
}

object_t * zyd2001::NewBie::NormalClass::makeObject(ArgumentList &args)
{
    object_t *obj = new object_t();
    obj->cl = make_shared<class_t>(this);
    obj->type = type;
    obj->type_name = type_name;
    for (auto cl : base_list)
        obj->bases.emplace_back(cl->makeObject(ArgumentList()));
    for (auto v : variables)
    {
        if (get<Expression>(v.second).type == NULL_EXPRESSION)
            obj->local_variables[v.first] = make_pair(Object(inter->class_map.second[get<ObjectType>(v.second)]->makeObject(ArgumentList())), get<AccessControl>(v.second));
        else
            obj->local_variables[v.first] = make_pair(inter->evaluate(get<Expression>(v.second)), get<AccessControl>(v.second));
    }
    ctor->call(args, obj);
    inter->addGCVertex(obj);
    return obj;
}

object_t *zyd2001::NewBie::NativeClass::makeObject(ArgumentList &args)
{
    object_t *obj = new object_t();
    for (auto cl : base_list)
        obj->bases.emplace_back(cl->makeObject(ArgumentList()));
    obj = real(args, obj);
    inter->addGCVertex(obj);
    return obj;
}

void zyd2001::NewBie::object_t::addVariable(Identifier id, Object o, AccessControl a)
{
    inter->addGCEdge(inter->root, o);
    local_variables[id] = make_pair(o, a);
}

Object zyd2001::NewBie::object_t::getVariable(Identifier id)
{
    auto v = local_variables.find(id);
    if (v == local_variables.end())
        for (auto base : bases)
        {
            v = base->local_variables.find(id);
            if (v != base->local_variables.end())
                break;
        }
    if (v == bases.back()->local_variables.end())
        throw exception();
    switch (v->second.second)
    {
        case PUBLIC:
        case READONLY:
            return v->second.first;
            break;
        case PRIVATE:
            if (inter->in_object && inter->current_object == this)
                return v->second.first;
            else
                throw exception();
            break;
    }
}

void zyd2001::NewBie::object_t::changeVariable(Identifier id, Object o)
{
    auto v = local_variables.at(id);
    switch (v.second)
    {
        case PUBLIC:
            if (inter->typeCheck(v.first, o))
            {
                inter->delGCEdge(this, v.first);
                v.first = o;
                inter->addGCEdge(this, o);
            }
            break;
        case READONLY:
        case PRIVATE:
            if (inter->in_object && inter->current_object == this)
            {
                if (inter->typeCheck(v.first, o))
                {
                    inter->delGCEdge(this, v.first);
                    v.first = o;
                    inter->addGCEdge(this, o);
                }
                else
                    throw exception();
            }
            else
                throw exception();
            break;
    }
}

zyd2001::NewBie::Object::Object(object_t *o) : obj(o), restrict_type(o->type)
{
    //inter->addGCVertex(node);
    //if (inter->in_object)
    //    inter->gc_graph.addEdge(inter->current_object, node);
    //else
    //    inter->gc_graph.addEdge(inter->root, node);
    //node->ref_count++;
}

Object::Object(const Object &o) : obj(o.obj), restrict_type(o.restrict_type) {}

zyd2001::NewBie::Object::Object(const int &i)
{
}

zyd2001::NewBie::Object::Object(const double &d)
{}

zyd2001::NewBie::Object::Object(const bool &b)
{}

zyd2001::NewBie::Object::Object(const String &str)
{}

zyd2001::NewBie::Object::Object(const Function &)
{}

Object zyd2001::NewBie::Object::operator+(const Object &o) const
{
    auto alist = ArgumentList({ Expression(o) });
    return obj->op[0]->call(alist, obj);
}
Object zyd2001::NewBie::Object::operator-(const Object &o) const
{
    auto alist = ArgumentList({ Expression(o) });
    return obj->op[1]->call(alist, obj);
}
Object zyd2001::NewBie::Object::operator*(const Object &o) const
{
    auto alist = ArgumentList({ Expression(o) });
    return obj->op[2]->call(alist, obj);
}
Object zyd2001::NewBie::Object::operator/(const Object &o) const
{
    auto alist = ArgumentList({ Expression(o) });
    return obj->op[3]->call(alist, obj);
}
Object zyd2001::NewBie::Object::operator%(const Object &o) const
{
    auto alist = ArgumentList({ Expression(o) });
    return obj->op[4]->call(alist, obj);
}
Object & zyd2001::NewBie::Object::operator=(const Object &o)
{
    obj = o.obj;
    return *this;
}
Object Object::operator-() const
{
    return obj->op[5]->call(ArgumentList(), obj);
}

#define compare(tag)\
bool zyd2001::NewBie::Object::operator##tag (const Object &o) const\
{\
    auto alist = ArgumentList({ Expression(o) });\
    return obj->op[6]->call(alist, obj) tag 0;\
}
compare(==)
compare(!=)
compare(>)
compare(>=)
compare(<)
compare(<=)

Object zyd2001::NewBie::Object::getVariable(Identifier id)
{
    return obj->getVariable(id);
}

void zyd2001::NewBie::Object::changeVariable(Identifier id, Object o)
{
    obj->changeVariable(id, o);
}

//Value::Value() : type(NULL_TYPE), content(nullptr) {}
//Value::Value(Value &&v) : type(v.type), various(v.various), content(v.content)
//{
//    //cout << "move ctor" << endl;
//    v.type = NULL_TYPE;
//}
//zyd2001::NewBie::Value::Value(ValueType t) : type(t), content(nullptr)
//{
//    switch (type)
//    {
//        case zyd2001::NewBie::NULL_TYPE:
//            break;
//        case zyd2001::NewBie::INT_TYPE:
//            content = new Integer(0);
//            break;
//        case zyd2001::NewBie::DOUBLE_TYPE:
//            content = new Double(0);
//            break;
//        case zyd2001::NewBie::BOOL_TYPE:
//            content = new Boolean(false);
//            break;
//        case zyd2001::NewBie::STRING_TYPE:
//            content = new String();
//            break;
//        case zyd2001::NewBie::VARIANT_TYPE:
//            various = true;
//            break;
//        case zyd2001::NewBie::ARRAY_TYPE:
//            break;
//        case zyd2001::NewBie::FUNCTION_TYPE:
//            break;
//        default:
//            break;
//    }
//}
//Value::Value(ValueType t, void *c) : type(t), content(c) {}
//Value::Value(const Value &v) : type(v.type), various(v.various)
//{
//    //cout << "copy ctor" << endl;
//    switch (type)
//    {
//        case zyd2001::NewBie::INT_TYPE:
//        {
//            Integer *ptr = new Integer(*v.get<Integer>());
//            content = ptr;
//            break;
//        }
//        case zyd2001::NewBie::DOUBLE_TYPE:
//        {
//            Double *ptr = new Double(*v.get<Double>());
//            content = ptr;
//            break;
//        }
//        case zyd2001::NewBie::BOOL_TYPE:
//        {
//            Boolean *ptr = new Boolean(*v.get<Boolean>());
//            content = ptr;
//            break;
//        }
//        case zyd2001::NewBie::STRING_TYPE:
//        {
//            String *ptr = new String(v.get<String>());
//            content = ptr;
//            break;
//        }
//        case zyd2001::NewBie::ARRAY_TYPE:
//        {
//            Array *ptr = new Array(v.get<Array>());
//            content = ptr;
//            break;
//        }
//        case FUNCTION_TYPE:
//        {
//            Function *ptr = new Function(v.get<Function>());
//            content = ptr;
//            break;
//        }
//        default:
//            break;
//    }
//}
//
//Value Value::ref()
//{
//    Value val;
//    val.type = type;
//    switch (type)
//    {
//        case zyd2001::NewBie::NULL_TYPE:
//            break;
//        case zyd2001::NewBie::INT_TYPE:
//            val.content = new Integer(get<Integer>());
//            break;
//        case zyd2001::NewBie::DOUBLE_TYPE:
//            val.content = new Double(get<Double>());
//            break;
//        case zyd2001::NewBie::BOOL_TYPE:
//            val.content = new Boolean(get<Boolean>());
//            break;
//        case zyd2001::NewBie::STRING_TYPE:
//            break;
//        case zyd2001::NewBie::VARIANT_TYPE:
//            break;
//        case zyd2001::NewBie::FUNCTION_TYPE:
//            break;
//        default:
//            break;
//    }
//}
//
//Value::Value(const int &i) : type(INT_TYPE), content(new Integer(i)) {}
//Value::Value(const double &d) : type(DOUBLE_TYPE), content(new Double(d)) {}
//Value::Value(const bool &b) : type(BOOL_TYPE), content(new Boolean(b)) {}
//Value::Value(const String &s) : type(STRING_TYPE), content(new String(s)) {}
//Value::Value(const char_t *s) : type(STRING_TYPE), content(new String(s)) {}
//
//Value::~Value()
//{
//    switch (type)
//    {
//        case zyd2001::NewBie::INT_TYPE:
//            delete_cast(Integer*);
//            break;
//        case zyd2001::NewBie::DOUBLE_TYPE:
//            delete_cast(Double*);
//            break;
//        case zyd2001::NewBie::BOOL_TYPE:
//            delete_cast(Boolean*);
//            break;
//        case zyd2001::NewBie::STRING_TYPE:
//            delete_cast(String*);
//            break;
//        case zyd2001::NewBie::ARRAY_TYPE:
//            delete_cast(Array*);
//            break;
//        case FUNCTION_TYPE:
//            delete_cast(Function*);
//            break;
//        default: // an object type
//            delete_cast(Object*);
//            break;
//    }
//}
//
//void Value::swap(Value &other)
//{
//    std::swap(type, other.type);
//    std::swap(content, other.content);
//    std::swap(various, other.various);
//}
//
//Value Value::operator+(const Value &v) const
//{
//    if (type == STRING_TYPE || v.type == STRING_TYPE)
//    {
//        Value first(*this);
//        delete static_cast<String*>(first.content); //make a new string
//        first.content = new String(this->get<String>().get());
//        Value second(v);
//        first.change_type(STRING_TYPE);
//        second.change_type(STRING_TYPE);
//        first.get<String>() += second.get<String>();
//        return first;
//    }
//    else if (type == DOUBLE_TYPE || v.type == DOUBLE_TYPE)
//    {
//        Value first(*this);
//        Value second(v);
//        first.change_type(DOUBLE_TYPE);
//        second.change_type(DOUBLE_TYPE);
//        return Value(DOUBLE_TYPE, new Double(*first.get<Double>() + *second.get<Double>()));
//    }
//    else if (type == INT_TYPE || v.type == INT_TYPE)
//        return Value(INT_TYPE, new Integer(*get<Integer>() + *v.get<Integer>()));
//}
//
//Value Value::operator-(const Value &v) const
//{
//    if (type == DOUBLE_TYPE || v.type == DOUBLE_TYPE)
//    {
//        Value first(*this);
//        Value second(v);
//        first.change_type(DOUBLE_TYPE);
//        second.change_type(DOUBLE_TYPE);
//        return Value(DOUBLE_TYPE, new Double(*first.get<Double>() - *second.get<Double>()));
//    }
//    else if (type == INT_TYPE || v.type == INT_TYPE)
//        return Value(INT_TYPE, new Integer(*get<Integer>() - *v.get<Integer>()));
//}
//
//Value Value::operator*(const Value &v) const
//{
//    if (type == STRING_TYPE && v.type == INT_TYPE)
//    {
//        Value first(*this);
//        delete static_cast<String*>(first.content);
//        first.content = new String(this->get<String>().get());
//        String str(first.get<String>().get());
//        for (int i = 1; i < *v.get<Integer>(); i++)
//            first.get<String>() += str;
//        return first;
//    }
//    else if (type == DOUBLE_TYPE || v.type == DOUBLE_TYPE)
//    {
//        Value first(*this);
//        Value second(v);
//        first.change_type(DOUBLE_TYPE);
//        second.change_type(DOUBLE_TYPE);
//        return Value(DOUBLE_TYPE, new Double(*first.get<Double>() * *second.get<Double>()));
//    }
//    else if (type == INT_TYPE || v.type == INT_TYPE)
//        return Value(INT_TYPE, new Integer(*get<Integer>() * *v.get<Integer>()));
//}
//
//Value zyd2001::NewBie::Value::operator/(const Value &v) const
//{
//    if (type == DOUBLE_TYPE || v.type == DOUBLE_TYPE)
//    {
//        Value first(*this);
//        Value second(v);
//        first.change_type(DOUBLE_TYPE);
//        second.change_type(DOUBLE_TYPE);
//        return Value(DOUBLE_TYPE, new Double(*first.get<Double>() / *second.get<Double>()));
//    }
//    else if (type == INT_TYPE || v.type == INT_TYPE)
//        return Value(INT_TYPE, new Integer(*get<Integer>() / *v.get<Integer>()));
//}
//
//Value zyd2001::NewBie::Value::operator%(const Value &v) const
//{
//    if (type == INT_TYPE || v.type == INT_TYPE)
//        return Value(INT_TYPE, new Integer(*get<Integer>() % *v.get<Integer>()));
//}
//
//Value &zyd2001::NewBie::Value::operator=(const Value &v)
//{
//    //cout << "copy operator" << endl;
//    if (this == &v)
//        return *this;
//    Value temp(v);
//    this->swap(temp);
//    return *this;
//}
//
//Value &zyd2001::NewBie::Value::operator=(Value &&v)
//{
//    //cout << "move operator" << endl;
//    this->swap(v);
//    return *this;
//}
//
//#define compare_value(tag) \
//Value first(*this), second(v); \
//if (type == STRING_TYPE || v.type == STRING_TYPE) \
//{ \
//	first.change_type(STRING_TYPE); \
//	second.change_type(STRING_TYPE); \
//	return first.get<String>().get() tag second.get<String>().get(); \
//} \
//else if (type == DOUBLE_TYPE || v.type == DOUBLE_TYPE) \
//{ \
//	first.change_type(DOUBLE_TYPE); \
//	second.change_type(DOUBLE_TYPE); \
//	return *first.get<Double>() tag *second.get<Double>(); \
//} \
//else if (type == INT_TYPE || v.type == INT_TYPE)\
//{ \
//	return *first.get<Integer>() tag *second.get<Integer>(); \
//}
//
//bool zyd2001::NewBie::Value::operator==(const Value &v) const
//{
//    compare_value(==)
//}
//
//bool zyd2001::NewBie::Value::operator!=(const Value &v) const
//{
//    compare_value(!=)
//}
//
//bool zyd2001::NewBie::Value::operator>(const Value &v) const
//{
//    compare_value(>)
//}
//
//bool zyd2001::NewBie::Value::operator>=(const Value &v) const
//{
//    compare_value(>=)
//}
//
//bool zyd2001::NewBie::Value::operator<(const Value &v) const
//{
//    compare_value(<)
//}
//
//bool zyd2001::NewBie::Value::operator<=(const Value &v) const
//{
//    compare_value(<=)
//}
//
//bool zyd2001::NewBie::Value::operator&&(const Value &v) const
//{
//    Value first(*this), second(v);
//    first.change_type(BOOL_TYPE);
//    second.change_type(BOOL_TYPE);
//    return *first.get<Boolean>() && *second.get<Boolean>();
//}
//
//bool zyd2001::NewBie::Value::operator||(const Value &v) const
//{
//    Value first(*this), second(v);
//    first.change_type(BOOL_TYPE);
//    second.change_type(BOOL_TYPE);
//    return *first.get<Boolean>() || *second.get<Boolean>();
//}
//
//bool zyd2001::NewBie::Value::operator!() const
//{
//    Value v(*this);
//    v.change_type(BOOL_TYPE);
//    return !(*v.get<Boolean>());
//}
//
//Value zyd2001::NewBie::Value::operator-() const
//{
//    Value v(*this);
//    switch (v.type)
//    {
//        case zyd2001::NewBie::INT_TYPE:
//            v.get<Integer>() = -(*v.get<Integer>());
//            break;
//        case zyd2001::NewBie::DOUBLE_TYPE:
//            v.get<Double>() = -(*v.get<Double>());
//            break;
//        default:
//            break;
//    }
//    return v;
//}
//
//Value zyd2001::NewBie::change(const Value &v, ValueType t)
//{
//    Value val(v);
//    val.change_type(t);
//    return val;
//}
//
//Value &Value::change_type(ValueType t)
//{
//    if (t == VARIANT_TYPE)
//    {
//        this->various = true;
//        return *this;
//    }
//    switch (type)
//    {
//        case zyd2001::NewBie::INT_TYPE:
//        {
//            switch (t)
//            {
//                case zyd2001::NewBie::INT_TYPE:
//                    break;
//                case zyd2001::NewBie::DOUBLE_TYPE:
//                {
//                    Double *ptr = new Double(static_cast<Double>(*get_cast(Integer*)));
//                    replace(Integer*);
//                    break;
//                }
//                case zyd2001::NewBie::BOOL_TYPE:
//                {
//                    Boolean *ptr = new Boolean(*get_cast(Integer*) ? true : false);
//                    replace(Integer*);
//                    break;
//                }
//                case zyd2001::NewBie::STRING_TYPE:
//                {
//                    String *ptr = new String(conv.from_bytes(to_string(*get_cast(Integer*))));
//                    replace(Integer*);
//                    break;
//                }
//                default:
//                    throw runtime_error("Type-Cast didn't allow");
//                    break;
//            }
//            break;
//        }
//        case zyd2001::NewBie::DOUBLE_TYPE:
//        {
//            switch (t)
//            {
//                case zyd2001::NewBie::INT_TYPE:
//                {
//                    Integer *ptr = new Integer(*get_cast(Double*));
//                    replace(Double*);
//                    break;
//                }
//                case zyd2001::NewBie::DOUBLE_TYPE:
//                    break;
//                case zyd2001::NewBie::BOOL_TYPE:
//                {
//                    Boolean *ptr = new Boolean(*get_cast(Double*) ? true : false);
//                    replace(Double*);
//                    break;
//                }
//                case zyd2001::NewBie::STRING_TYPE:
//                {
//                    String *ptr = new String(conv.from_bytes(to_string(*get_cast(Double*))));
//                    replace(Double*);
//                    break;
//                }
//                default:
//                    break;
//            }
//            break;
//        }
//        case zyd2001::NewBie::BOOL_TYPE:
//        {
//            switch (t)
//            {
//                case zyd2001::NewBie::INT_TYPE:
//                {
//                    Integer *ptr = new Integer(*get_cast(Boolean*) ? 1 : 0);
//                    replace(Boolean*);
//                    break;
//                }
//                case zyd2001::NewBie::DOUBLE_TYPE:
//                {
//                    Double *ptr = new Double(*get_cast(Boolean*) ? 1 : 0);
//                    replace(Boolean*);
//                    break;
//                }
//                case zyd2001::NewBie::BOOL_TYPE:
//                    break;
//                case zyd2001::NewBie::STRING_TYPE:
//                {
//                    String *ptr = new String(conv.from_bytes(*get_cast(Boolean*) ? "true" : "false"));
//                    replace(Boolean*);
//                    break;
//                }
//                default:
//                    break;
//            }
//            break;
//        }
//        case zyd2001::NewBie::STRING_TYPE:
//        {
//            switch (t)
//            {
//                case zyd2001::NewBie::INT_TYPE:
//                {
//                    Integer *ptr = new Integer(stoi(conv.to_bytes(get_cast(String*).get())));
//                    replace(String*);
//                    break;
//                }
//                case zyd2001::NewBie::DOUBLE_TYPE:
//                {
//                    Double *ptr = new Double(stod(conv.to_bytes(get_cast(String*).get())));
//                    replace(String*);
//                    break;
//                }
//                case zyd2001::NewBie::BOOL_TYPE:
//                {
//                    Boolean *ptr = new Boolean(get_cast(String*).get().empty() ? false : true);
//                    replace(String*);
//                    break;
//                }
//                case zyd2001::NewBie::STRING_TYPE:
//                    break;
//                default:
//                    break;
//            }
//            break;
//        }
//        case zyd2001::NewBie::ARRAY_TYPE:
//            break;
//        default:
//            break;
//    }
//    type = t;
//    return *this;
//}
//
//ostream &zyd2001::NewBie::operator<<(ostream &out, Value &v)
//{
//    switch (v.type)
//    {
//        case zyd2001::NewBie::NULL_TYPE:
//            out << "null";
//            break;
//        case zyd2001::NewBie::INT_TYPE:
//            out << *v.get<Integer>();
//            break;
//        case zyd2001::NewBie::DOUBLE_TYPE:
//            out << *v.get<Double>();
//            break;
//        case zyd2001::NewBie::BOOL_TYPE:
//            out << *v.get<Boolean>();
//            break;
//        case zyd2001::NewBie::STRING_TYPE:
//#if defined(_MSC_VER)
//            printf(conv.to_bytes(v.get<String>().get()).c_str());
//#elif defined(__GNUC__)
//            out << conv.to_bytes(v.get<String>().get());
//#endif
//            break;
//        case zyd2001::NewBie::ARRAY_TYPE:
//            break;
//        default:
//            break;
//    }
//    return out;
//}