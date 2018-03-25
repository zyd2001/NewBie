#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

void zyd2001::NewBie::class_t::addStaticVariable(Identifier id, object_t * o, AccessControl a)
{
    if (static_variables.find(id) != static_variables.end())
        throw exception();
    inter->addGCEdge(inter->root, o);
    static_variables[id] = o;
}

ObjectContainer zyd2001::NewBie::class_t::getStaticVariable(Identifier id)
{
    return static_variables.at(id);
}

object_t * zyd2001::NewBie::NormalClass::makeObject(InterpreterImp::Runner &runner, ArgumentList &alist)
{
    object_t * obj = new object_t(inter, make_shared<class_t>(this));
    auto args = runner.resolveArgumentList(alist);
    auto plist = runner.ArgsToParams(args);
    auto constructor = ctor->overload_map.at(plist);
    for (int i = 0; i < base_list.size(); i++)
    {
        auto b = base_list[i]->makeObjectAsBase(runner, constructor.base_args[i], obj);
        obj->bases.emplace_back(b);
        obj->bases_mapped.emplace(b->type, b);
        for (auto &item : b->local_variables)
        {
            switch (item.second.visibility)
            {
                case PUBLIC:
                case PROTECTED:
                    obj->local_variables[item.first] = item.second;
            }
        }
    }

    for (auto &item : variables)
    {
        if (get<Expression>(item.second).get() != nullptr)
            obj->addVariable(item.first, get<ObjectType>(item.second), runner.evaluate(get<Expression>(item.second))->get(), get<AccessControl>(item.second));
        else
            obj->addVariable(item.first, get<ObjectType>(item.second), get<AccessControl>(item.second));
    }
    runner.call(constructor.stat, args);
    inter->addGCVertex(obj);
    return obj;
}

object_t * zyd2001::NewBie::NormalClass::makeObjectAsBase(InterpreterImp::Runner &runner, ArgumentList &alist, object_t * o)
{
    object_t * obj;

    //check if object of this type is already constructed
    auto iter = o->all_bases.find(type); 
    if (iter != o->all_bases.end())
        obj = iter->second;
    else
    {
        obj = new object_t(inter, make_shared<class_t>(this));
        o->all_bases[type] = obj;
    }

    auto args = runner.resolveArgumentList(alist);
    auto plist = runner.ArgsToParams(args);
    auto constructor = ctor->overload_map.at(plist);
    for (int i = 0; i < base_list.size(); i++)
    {
        object_t * b = base_list[i]->makeObjectAsBase(runner, constructor.base_args[i], o); //use 'o' to pass the object already constructed
        obj->bases.emplace_back(b);
        obj->bases_mapped.emplace(b->type, b);
        for (auto &item : b->local_variables)
        {
            switch (item.second.visibility)
            {
                case PUBLIC:
                case PROTECTED:
                    obj->local_variables[item.first] = item.second;
            }
        }
    }
    for (auto &item : variables)
    {
        if (get<Expression>(item.second).get() != nullptr)
            obj->addVariable(item.first, get<ObjectType>(item.second), runner.evaluate(get<Expression>(item.second))->get(), get<AccessControl>(item.second));
        else
            obj->addVariable(item.first, get<ObjectType>(item.second), get<AccessControl>(item.second));
    }
    runner.call(constructor.stat, args);
    return obj;
}

object_t * zyd2001::NewBie::NativeClass::makeObject(InterpreterImp::Runner &runner, ArgumentList &alist)
{
    object_t * obj = new object_t(inter, make_shared<class_t>(this));
    auto args = runner.resolveArgumentList(alist);
    auto plist = runner.ArgsToParams(args);
    auto constructor = ctor->overload_map.at(plist);
    for (int i = 0; i < base_list.size(); i++)
    {
        object_t * b = base_list[i]->makeObjectAsBase(runner, constructor.base_args[i], obj);
        obj->bases.emplace_back(b);
        obj->bases_mapped.emplace(b->type, b);
        for (auto &item : b->local_variables)
        {
            switch (item.second.visibility)
            {
                case PUBLIC:
                case PROTECTED:
                    obj->local_variables[item.first] = item.second;
            }
        }
    }
    real(args, obj);
    inter->addGCVertex(obj);
    return obj;
}

object_t * zyd2001::NewBie::NativeClass::makeObjectAsBase(InterpreterImp::Runner &runner, ArgumentList &alist, object_t * o)
{
    object_t * obj;

    //check if object of this type is already constructed
    auto iter = o->all_bases.find(type);
    if (iter != o->all_bases.end())
        obj = iter->second;
    else
    {
        obj = new object_t(inter, make_shared<class_t>(this));
        o->all_bases[type] = obj;
    }

    auto args = runner.resolveArgumentList(alist);
    auto plist = runner.ArgsToParams(args);
    auto constructor = ctor->overload_map.at(plist);
    for (int i = 0; i < base_list.size(); i++)
    {
        object_t * b = base_list[i]->makeObjectAsBase(runner, constructor.base_args[i], o); //use 'o' to pass the object already constructed
        obj->bases.emplace_back(b);
        obj->bases_mapped.emplace(b->type, b);
        for (auto &item : b->local_variables)
        {
            switch (item.second.visibility)
            {
                case PUBLIC:
                case PROTECTED:
                    obj->local_variables[item.first] = item.second;
            }
        }
    }
    real(args, obj);
    return obj;
}

bool zyd2001::NewBie::object_container_t::typeCheck(object_t * o)
{
    if (restrict_type == 1) //variant type
        return true;
    if (obj->type == o->type)
        return true;
    if (restrict_type == o->type)
        return true;
    else
    {
        for (auto &b : o->all_bases)
            if (restrict_type == b.second->type)
                return true;
        return false;
    }
}

void zyd2001::NewBie::object_container_t::set(object_t * o)
{
    if (isConst)
        throw exception();
    else
    {
        if (typeCheck(o))
        {
            if (belongs_to == nullptr) //is a temp container
                obj = o;
            else
            {
                inter->delGCEdge(belongs_to, obj);
                obj = o;
                inter->addGCEdge(belongs_to, o);
            }
        }
        else
            throw exception();
    }
}

object_t * zyd2001::NewBie::object_container_t::get()
{
    if (obj != nullptr)
        return obj;
    else
        return inter->null;
}

void object_t::addVariable(Identifier id, ObjectType t, AccessControl visibility)
{
    local_variables[id] = MapItem{ make_shared<object_container_t>(inter, t, this), visibility };
}

void zyd2001::NewBie::object_t::addVariable(Identifier id, object_t * o, AccessControl visibility)
{
    local_variables[id] = MapItem{ make_shared<object_container_t>(inter, o, this), visibility };
}

void zyd2001::NewBie::object_t::addVariable(Identifier id, ObjectType t, object_t *o, AccessControl visibility)
{    
    local_variables[id] = MapItem{ make_shared<object_container_t>(inter, t, o, this), visibility };
}

ObjectContainer zyd2001::NewBie::object_t::getVariable(InterpreterImp::Runner &runner, Identifier id)
{
    auto item = local_variables.at(id);
    switch (item.visibility)
    {
        case PUBLIC:
            return item.o;
            break;
        case PROTECTED:
        case PRIVATE:
            if (runner.current_object == this)
                return item.o;
            else
                throw exception();
            break;
    }
}

ObjectContainer zyd2001::NewBie::object_t::getSuperVariable(InterpreterImp::Runner &runner, ObjectType type, Identifier id)
{
    bases_mapped.at(type)->getVariableFromDerived(runner, id);
}

zyd2001::NewBie::object_t::~object_t()
{
    if (native_ptr != nullptr)
        cl->native_deleter(native_ptr);
    for (auto i : all_bases) //base object has no object_t * in all_bases
        delete i.second;
}

ObjectContainer zyd2001::NewBie::object_t::getVariableFromDerived(InterpreterImp::Runner &runner, Identifier id)
{
    auto item = local_variables.at(id);
    switch (item.visibility)
    {
        case PUBLIC:
        case PROTECTED:
            return item.o;
            break;
        case PRIVATE:
            if (runner.current_object == this)
                return item.o;
            else
                throw exception();
            break;
    }
}

object_t zyd2001::NewBie::object_t::operator+(const object_t &o) const
{
    auto alist = ArgumentList({ make_shared<LiteralExpression>(o) });
    return obj->op[0]->call(alist, obj);
}
object_t zyd2001::NewBie::object_t::operator-(const object_t &o) const
{
    auto alist = ArgumentList({ make_shared<LiteralExpression>(o) });
    return obj->op[1]->call(alist, obj);
}
object_t zyd2001::NewBie::object_t::operator*(const object_t &o) const
{
    auto alist = ArgumentList({ make_shared<LiteralExpression>(o) });
    return obj->op[2]->call(alist, obj);
}
object_t zyd2001::NewBie::object_t::operator/(const object_t &o) const
{
    auto alist = ArgumentList({ make_shared<LiteralExpression>(o) });
    return obj->op[3]->call(alist, obj);
}
object_t zyd2001::NewBie::object_t::operator%(const object_t &o) const
{
    auto alist = ArgumentList({ make_shared<LiteralExpression>(o) });
    return obj->op[4]->call(alist, obj);
}
object_t object_t::operator-() const
{
    return obj->op[5]->call(ArgumentList(), obj);
}

#define compare(tag)\
bool zyd2001::NewBie::object_t::operator##tag (const object_t &o) const\
{\
    auto alist = ArgumentList({ make_shared<LiteralExpression>(o) });\
    return obj->op[6]->call(alist, obj) tag 0;\
}
compare(==)
compare(!=)
compare(>)
compare(>=)
compare(<)
compare(<=)

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
//            delete_cast(object_t*);
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