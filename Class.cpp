#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

#define same \
auto plist = runner.argsToParams(args);\
std::unordered_map<ParameterList, Ctor, ParamsHash, ParamsEqualTo>::iterator it;\
if (ctor->can_overload)\
    it = ctor->overload_map.find(plist);\
else\
    it = ctor->overload_map.begin();\
std::vector<Args> & base_args = it->second->getArgs(runner);\
for (int i = 0; i < base_list.size(); i++)\
{\
    object_t * b;\
    if (i < base_args.size())\
        b = base_list[i]->makeObjectAsBase(runner, obj, base_args[i]);\
    else\
        b = base_list[i]->makeObjectAsBase(runner, obj);\
    obj->bases.emplace_back(b);\
    obj->bases_mapped.emplace(b->type, b);\
    for (auto &item : b->local_variables)\
    {\
        switch (item.second.second)\
        {\
            case PUBLIC:\
            case PROTECTED:\
                obj->local_variables[item.first] = item.second;\
        }\
    }\
}\
\
for (auto & item : variables)\
{\
    if (get<Expression>(item.second).get() != nullptr)\
        obj->addVariable(runner, item.first, get<ObjectType>(item.second),\
            runner.evaluate(get<Expression>(item.second)), get<AccessControl>(item.second),\
            get<bool>(item.second));\
    else\
        obj->addVariable(runner, item.first, get<ObjectType>(item.second),\
            runner.makeDefaultObject(get<ObjectType>(item.second)),\
            get<AccessControl>(item.second), get<bool>(item.second));\
}\
newNewBieStack();\
newNewBieScope();\
it->second->call(runner, obj, args, it->first);

object_t * zyd2001::NewBie::class_t::makeObject(Runner & runner, const Args & args)
{
    object_t * obj = new object_t(runner, shared_from_this(), nullptr);

    same

    obj->all_bases.clear();
    inter->addGCVertex(obj);
    return obj;
}

object_t * zyd2001::NewBie::class_t::makeObjectAsBase(Runner & runner, object_t * o, const Args & args)
{
    object_t * obj;

    auto iter = o->all_bases.find(type);
    if (iter != o->all_bases.end())
        obj = iter->second;
    else
    {
        obj = new object_t(runner, shared_from_this(), nullptr);
        o->all_bases[type] = obj;
    }

    same

    return obj;
}

ObjectContainer zyd2001::NewBie::class_t::getVariableWithPrototype(Runner & runner, Identifier id, bool flag)
{
    auto result = prototype.find(id);
    if (result != prototype.end())
    {
        switch (result->second.second)
        {
            case PUBLIC:
                return result->second.first;
            case PROTECTED:
            case PRIVATE:
                if (flag)
                    return result->second.first;
                else
                    throw exception();
        }
    }
    throw exception();
}

void zyd2001::NewBie::class_t::addToPrototype(Identifier id, ObjectContainer o, AccessControl v)
{
    Runner & runner = *inter->runner;
    ObjectContainer oc(runner);
    oc->set(runner, o);
    prototype[id] = make_pair(oc, v);
}

zyd2001::NewBie::class_t::class_t(InterpreterImp * inter, Identifier type_name, ObjectType t, std::vector<Class> & base, 
    bool RAII, bool edit, bool isFinal,
    Constructor ctor, Func dtor, Operator & o, vars & variables, std::function<void(void*)> native_deleter)
    : RAII(RAII), editable(edit), isFinal(isFinal), inter(inter), type_name(type_name), type(t), base_list(base), ctor(ctor), dtor(dtor), o(o), variables(variables), native_deleter(native_deleter) {}

std::vector<Args>& zyd2001::NewBie::NormalConstructor::getArgs(Runner & runner)
{
    vector<Args> args;
    for (auto & arg : base_args)
        args.emplace_back(runner.resolveArgumentList(arg));
    return args;
}

ObjectContainer zyd2001::NewBie::NormalConstructor::call(Runner & r, object_t * o, const Args & args, const ParameterList & p)
{
    return f.call(r, o, args, p);
}

std::vector<Args>& zyd2001::NewBie::NativeConstructor::getArgs(Runner & runner)
{
    return base_args;
}

ObjectContainer zyd2001::NewBie::NativeConstructor::call(Runner & r, object_t * o, const Args & args, const ParameterList & p)
{
    return f.call(r, o, args, p);
}

zyd2001::NewBie::constructor_t::constructor_t(init_vec & vec)
{
    if (vec.empty())
        throw exception();
    else if (vec.size() == 1)
        can_overload = false;
    else
        can_overload = true;

    for (auto & item : vec)
        overload_map.emplace(item);
}

void zyd2001::NewBie::Operator::set(const std::vector<std::pair<int, Function>> & data)
{
    for (auto &i : data)
        o[i.first] = i.second;
}

Operator & zyd2001::NewBie::Operator::set(int i, Function f)
{
    o[i] = f;
    return *this;
}
#define operator(op) \
ObjectContainer zyd2001::NewBie::Operator:: op (Runner & runner, object_t * obj, const Args & args)\
{\
    if (o[o_ ## op] != n)\
        return o[o_ ## op]->call(runner, obj, args);\
    else\
        throw exception();\
}
operator(add)
operator(sub)
operator(mul)
operator(div)
operator(mod)
operator(minus)
operator(plus)
operator(not)
operator(negate)
operator(bit_and)
operator(bit_or)
operator(bit_xor)
operator(bit_left)
operator(bit_right)
operator(and)
operator(or)
operator(lt)
operator(le)
operator(gt)
operator(ge)
operator(eq)
operator(ne)
operator(index)
operator(call)
operator(toBool)