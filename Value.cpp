#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

#include <codecvt>
#include <locale>
#include <cstdio>

using namespace zyd2001::NewBie;
using namespace std;

#define delete_cast(...) delete static_cast<__VA_ARGS__>(content)
#define get_cast(...) (*static_cast<__VA_ARGS__>(content))
#define replace(...) do {delete_cast(__VA_ARGS__); content = ptr;} while(0)

extern InterpreterImp *inter;

#if defined(_MSC_VER)
wstring_convert<codecvt_utf8<char_t>, char_t> conv;
#elif defined(__GNUC__)
wstring_convert<codecvt_utf8<char_t>, char_t> conv;
#endif

Value::Value() : type(NULL_TYPE), content(nullptr) {}
Value::Value(Value &&v) : type(v.type), various(v.various), content(v.content)
{
    //cout << "move ctor" << endl;
    v.type = NULL_TYPE;
}
zyd2001::NewBie::Value::Value(ValueType t) : type(t), content(nullptr)
{
    switch (type)
    {
        case zyd2001::NewBie::NULL_TYPE:
            break;
        case zyd2001::NewBie::INT_TYPE:
            content = new int(0);
            break;
        case zyd2001::NewBie::DOUBLE_TYPE:
            content = new double(0);
            break;
        case zyd2001::NewBie::BOOL_TYPE:
            content = new bool(false);
            break;
        case zyd2001::NewBie::STRING_TYPE:
            content = new string_t(0);
            break;
        case zyd2001::NewBie::VARIANT_TYPE:
            various = true;
            break;
        case zyd2001::NewBie::ARRAY_TYPE:
            break;
        case zyd2001::NewBie::FUNCTION_TYPE:
            break;
        default:
            break;
    }
}
Value::Value(ValueType t, void *c) : type(t), content(c) {}
Value::Value(const Value &v) : type(v.type), various(v.various)
{
    //cout << "copy ctor" << endl;
    switch (type)
    {
        case zyd2001::NewBie::INT_TYPE:
        {
            int *ptr = new int(v.get<int>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::DOUBLE_TYPE:
        {
            double *ptr = new double(v.get<double>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::BOOL_TYPE:
        {
            bool *ptr = new bool(v.get<bool>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::STRING_TYPE:
        {
            string_t *ptr = new string_t(v.get<string_t>());
            content = ptr;
            break;
        }
        case zyd2001::NewBie::ARRAY_TYPE:
        {
            Array *ptr = new Array(v.get<Array>());
            content = ptr;
            break;
        }
        case FUNCTION_TYPE:
        {
            Function *ptr = new Function(v.get<Function>());
            content = ptr;
            break;
        }
        default:
            break;
    }
}

Value::Value(const int &i) : type(INT_TYPE), content(new int(i)) {}
Value::Value(const double &d) : type(DOUBLE_TYPE), content(new double(d)) {}
Value::Value(const bool &b) : type(BOOL_TYPE), content(new bool(b)) {}
Value::Value(const string_t &s) : type(STRING_TYPE), content(new string_t(s)) {}
Value::Value(const char_t *s) : type(STRING_TYPE), content(new string_t(s)) {}

Value::~Value()
{
    switch (type)
    {
        case zyd2001::NewBie::INT_TYPE:
            delete_cast(int*);
            break;
        case zyd2001::NewBie::DOUBLE_TYPE:
            delete_cast(double*);
            break;
        case zyd2001::NewBie::BOOL_TYPE:
            delete_cast(bool*);
            break;
        case zyd2001::NewBie::STRING_TYPE:
            delete_cast(string_t*);
            break;
        case zyd2001::NewBie::ARRAY_TYPE:
            delete_cast(Array*);
            break;
        //case zyd2001::NewBie::OBJECT_TYPE:
        //{
        //    auto &node = this->get<Object>().node;
        //    if (inter->in_object)
        //        inter->gc_graph.delEdge(inter->current_object->get<Object>().node, node);
        //    else
        //        inter->gc_graph.delEdge(inter->root, node);
        //    delete_cast(Object*);
        //    break;
        //}
        case FUNCTION_TYPE:
            delete_cast(Function*);
            break;
        default:
            break;
    }
}

void Value::swap(Value &other)
{
    std::swap(type, other.type);
    std::swap(content, other.content);
    std::swap(various, other.various);
}

Value Value::operator+(const Value &v) const
{
    if (type == STRING_TYPE || v.type == STRING_TYPE)
    {
        Value first(*this);
        delete static_cast<string_t*>(first.content);
        first.content = new string_t(this->get<string_t>().get());
        Value second(v);
        first.change_type(STRING_TYPE);
        second.change_type(STRING_TYPE);
        first.get<string_t>() += second.get<string_t>();
        return first;
    }
    else if (type == DOUBLE_TYPE || v.type == DOUBLE_TYPE)
    {
        Value first(*this);
        Value second(v);
        first.change_type(DOUBLE_TYPE);
        second.change_type(DOUBLE_TYPE);
        first.get<double>() += second.get<double>();
        return first;
    }
    else
    {
        return Value(INT_TYPE, new int(get<int>() + v.get<int>()));
    }
}

Value Value::operator-(const Value &v) const
{
    if (type == DOUBLE_TYPE || v.type == DOUBLE_TYPE)
    {
        Value first(*this);
        Value second(v);
        first.change_type(DOUBLE_TYPE);
        second.change_type(DOUBLE_TYPE);
        first.get<double>() -= second.get<double>();
        return first;
    }
    else
    {
        return Value(INT_TYPE, new int(get<int>() - v.get<int>()));
    }
}

Value Value::operator*(const Value &v) const
{
    if (type == STRING_TYPE && v.type == INT_TYPE)
    {
        Value first(*this);
        delete static_cast<string_t*>(first.content);
        first.content = new string_t(this->get<string_t>().get());
        string_t str(first.get<string_t>().get());
        for (int i = 1; i < v.get<int>(); i++)
            first.get<string_t>() += str;
        return first;
    }
    else if (type == DOUBLE_TYPE || v.type == DOUBLE_TYPE)
    {
        Value first(*this);
        Value second(v);
        first.change_type(DOUBLE_TYPE);
        second.change_type(DOUBLE_TYPE);
        first.get<double>() *= second.get<double>();
        return first;
    }
    else
    {
        return Value(INT_TYPE, new int(get<int>() * v.get<int>()));
    }
}

Value zyd2001::NewBie::Value::operator/(const Value &v) const
{
    if (type == DOUBLE_TYPE || v.type == DOUBLE_TYPE)
    {
        Value first(*this);
        Value second(v);
        first.change_type(DOUBLE_TYPE);
        second.change_type(DOUBLE_TYPE);
        first.get<double>() /= second.get<double>();
        return first;
    }
    else
    {
        return Value(INT_TYPE, new int(get<int>() / v.get<int>()));
    }
}

Value zyd2001::NewBie::Value::operator%(const Value &v) const
{
    return Value(INT_TYPE, new int(get<int>() % v.get<int>()));
}

Value &zyd2001::NewBie::Value::operator=(const Value &v)
{
    //cout << "copy operator" << endl;
    if (this == &v)
        return *this;
    Value temp(v);
    this->swap(temp);
    return *this;
}

Value &zyd2001::NewBie::Value::operator=(Value &&v)
{
    //cout << "move operator" << endl;
    this->swap(v);
    return *this;
}

#define compare_value(tag) \
Value first(*this), second(v); \
if (type == STRING_TYPE || v.type == STRING_TYPE) \
{ \
	first.change_type(STRING_TYPE); \
	second.change_type(STRING_TYPE); \
	return first.get<string_t>().get() tag second.get<string_t>().get(); \
} \
else if (type == DOUBLE_TYPE || v.type == DOUBLE_TYPE) \
{ \
	first.change_type(DOUBLE_TYPE); \
	second.change_type(DOUBLE_TYPE); \
	return first.get<double>() tag second.get<double>(); \
} \
else \
{ \
	return first.get<int>() tag second.get<int>(); \
}

bool zyd2001::NewBie::Value::operator==(const Value &v) const
{
    compare_value(==)
}

bool zyd2001::NewBie::Value::operator!=(const Value &v) const
{
    compare_value(!=)
}

bool zyd2001::NewBie::Value::operator>(const Value &v) const
{
    compare_value(>)
}

bool zyd2001::NewBie::Value::operator>=(const Value &v) const
{
    compare_value(>=)
}

bool zyd2001::NewBie::Value::operator<(const Value &v) const
{
    compare_value(<)
}

bool zyd2001::NewBie::Value::operator<=(const Value &v) const
{
    compare_value(<=)
}

bool zyd2001::NewBie::Value::operator&&(const Value &v) const
{
    Value first(*this), second(v);
    first.change_type(BOOL_TYPE);
    second.change_type(BOOL_TYPE);
    return first.get<bool>() && second.get<bool>();
}

bool zyd2001::NewBie::Value::operator||(const Value &v) const
{
    Value first(*this), second(v);
    first.change_type(BOOL_TYPE);
    second.change_type(BOOL_TYPE);
    return first.get<bool>() || second.get<bool>();
}

bool zyd2001::NewBie::Value::operator!() const
{
    Value v(*this);
    v.change_type(BOOL_TYPE);
    return !(v.get<bool>());
}

Value zyd2001::NewBie::Value::operator-() const
{
    Value v(*this);
    switch (v.type)
    {
        case zyd2001::NewBie::INT_TYPE:
            v.get<int>() = -(v.get<int>());
            break;
        case zyd2001::NewBie::DOUBLE_TYPE:
            v.get<double>() = -(v.get<double>());
            break;
        default:
            break;
    }
    return v;
}

Value zyd2001::NewBie::change(const Value &v, ValueType t)
{
    Value val(v);
    val.change_type(t);
    return val;
}

Value &Value::change_type(ValueType t)
{
    if (t == VARIANT_TYPE)
    {
        this->various = true;
        return *this;
    }
    switch (type)
    {
        case zyd2001::NewBie::INT_TYPE:
        {
            switch (t)
            {
                case zyd2001::NewBie::INT_TYPE:
                    break;
                case zyd2001::NewBie::DOUBLE_TYPE:
                {
                    double *ptr = new double(static_cast<double>(get_cast(int*)));
                    replace(int*);
                    break;
                }
                case zyd2001::NewBie::BOOL_TYPE:
                {
                    bool *ptr = new bool(get_cast(int*) ? true : false);
                    replace(int*);
                    break;
                }
                case zyd2001::NewBie::STRING_TYPE:
                {
                    string_t *ptr = new string_t(conv.from_bytes(to_string(get_cast(int*))));
                    replace(int*);
                    break;
                }
                default:
                    throw runtime_error("Type-Cast didn't allow");
                    break;
            }
            break;
        }
        case zyd2001::NewBie::DOUBLE_TYPE:
        {
            switch (t)
            {
                case zyd2001::NewBie::INT_TYPE:
                {
                    int *ptr = new int(static_cast<double>(get_cast(double*)));
                    replace(double*);
                    break;
                }
                case zyd2001::NewBie::DOUBLE_TYPE:
                    break;
                case zyd2001::NewBie::BOOL_TYPE:
                {
                    bool *ptr = new bool(get_cast(double*) ? true : false);
                    replace(double*);
                    break;
                }
                case zyd2001::NewBie::STRING_TYPE:
                {
                    string_t *ptr = new string_t(conv.from_bytes(to_string(get_cast(double*))));
                    replace(double*);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case zyd2001::NewBie::BOOL_TYPE:
        {
            switch (t)
            {
                case zyd2001::NewBie::INT_TYPE:
                {
                    int *ptr = new int(get_cast(bool*) ? 1 : 0);
                    replace(bool*);
                    break;
                }
                case zyd2001::NewBie::DOUBLE_TYPE:
                {
                    double *ptr = new double(get_cast(bool*) ? 1 : 0);
                    replace(bool*);
                    break;
                }
                case zyd2001::NewBie::BOOL_TYPE:
                    break;
                case zyd2001::NewBie::STRING_TYPE:
                {
                    string_t *ptr = new string_t(conv.from_bytes(get_cast(bool*) ? "true" : "false"));
                    replace(bool*);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case zyd2001::NewBie::STRING_TYPE:
        {
            switch (t)
            {
                case zyd2001::NewBie::INT_TYPE:
                {
                    int *ptr = new int(stoi(conv.to_bytes(get_cast(string_t*).get())));
                    replace(string_t*);
                    break;
                }
                case zyd2001::NewBie::DOUBLE_TYPE:
                {
                    double *ptr = new double(stod(conv.to_bytes(get_cast(string_t*).get())));
                    replace(string_t*);
                    break;
                }
                case zyd2001::NewBie::BOOL_TYPE:
                {
                    bool *ptr = new bool(get_cast(string_t*).get().empty() ? false : true);
                    replace(string_t*);
                    break;
                }
                case zyd2001::NewBie::STRING_TYPE:
                    break;
                default:
                    break;
            }
            break;
        }
        case zyd2001::NewBie::ARRAY_TYPE:
            break;
        case zyd2001::NewBie::OBJECT_TYPE:
            break;
        default:
            break;
    }
    type = t;
    return *this;
}

ostream &zyd2001::NewBie::operator<<(ostream &out, Value &v)
{
    switch (v.type)
    {
        case zyd2001::NewBie::NULL_TYPE:
            out << "null";
            break;
        case zyd2001::NewBie::INT_TYPE:
            out << v.get<int>();
            break;
        case zyd2001::NewBie::DOUBLE_TYPE:
            out << v.get<double>();
            break;
        case zyd2001::NewBie::BOOL_TYPE:
            out << v.get<bool>();
            break;
        case zyd2001::NewBie::STRING_TYPE:
#if defined(_MSC_VER)
            printf(conv.to_bytes(v.get<string_t>().get()).c_str());
#elif defined(__GNUC__)
            out << conv.to_bytes(v.get<string_t>().get());
#endif
            break;
        case zyd2001::NewBie::ARRAY_TYPE:
            break;
        case zyd2001::NewBie::OBJECT_TYPE:
            break;
        default:
            break;
    }
    return out;
}