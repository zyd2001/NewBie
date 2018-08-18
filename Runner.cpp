#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

Expression zyd2001::NewBie::Runner::_m_exp(helpStruct i)
{
    switch (i.type)
    {
        case NewBie_Int:
            return make_shared<LiteralExpression>(ObjectContainer(*this, any_cast<int>(i.ptr)));
            break;
        case NewBie_Double:
            return make_shared<LiteralExpression>(ObjectContainer(*this, any_cast<double>(i.ptr)));
            break;
        case NewBie_Boolean:
            return make_shared<LiteralExpression>(ObjectContainer(*this, any_cast<bool>(i.ptr)));
            break;
        case NewBie_String:
            return make_shared<LiteralExpression>(ObjectContainer(*this, any_cast<String>(i.ptr)));
            break;
        default:
            break;
    }
}

Args zyd2001::NewBie::Runner::_makeArgs(const std::vector<helpStruct>&v)
{
    Args args;
    for (auto &i : v)
    {
        switch (i.type)
        {
            case NewBie_Int:
                args.emplace_back(ObjectContainer(*this, any_cast<int>(i.ptr)));
                break;
            case NewBie_Double:
                args.emplace_back(ObjectContainer(*this, any_cast<double>(i.ptr)));
                break;
            case NewBie_Boolean:
                args.emplace_back(ObjectContainer(*this, any_cast<bool>(i.ptr)));
                break;
            case NewBie_String:
                args.emplace_back(ObjectContainer(*this, any_cast<String>(i.ptr)));
                break;
            default:
                break;
        }
    }
    return args;
}

ObjectContainer zyd2001::NewBie::Runner::returnVal()
{
    auto f = call_stack_func.top().first;
    ObjectContainer o(*this);
    if (f->ref)
    {
        if (inter->typeCheck(f->return_type, temp_obj->get()))
            o = temp_obj;
        else
            throw exception();
    }
    else
    {
        if (inter->typeCheck(f->return_type, temp_obj->get()))
            o = temp_obj.copy(*this);
        else
            throw exception();
    }
    temp_obj = *inter->null_obj; //reset temp_obj after return
    return o;
}

ObjectContainer zyd2001::NewBie::Runner::addRefVariable(Identifier name, ObjectContainer oc)
{
    auto o = current_obj_map->find(name);
    if (o != current_obj_map->end())
        current_obj_map->emplace(name, oc);
    else
        throw exception();
}

Args zyd2001::NewBie::Runner::resolveArgumentList(const ArgumentList & alist)
{
    Args args;
    for(auto & exp : alist)
        args.emplace_back(evaluate(exp));
    return args;
}

ParameterList zyd2001::NewBie::Runner::argsToParams(const Args & args)
{
    ParameterList plist;
    for (auto & i : args)
        plist.emplace_back(i.ptr->restrict_type);
    return plist;
}

ObjectContainer zyd2001::NewBie::Runner::makeDefaultObject(ObjectType t)
{
    Class cl = inter->findClass(t);
    return cl->makeObject(*this);
}

ObjectContainer zyd2001::NewBie::Runner::getVariable(Identifier id)
{
    for (auto iter = variable_stack.top().rbegin(); iter != variable_stack.top().rend(); iter++)
    {
        auto result = iter->find(id);
        if (result != iter->end())
            return result->second;
        else
            continue;
    }
    auto result = inter->global_object_map->find(id); //global
    if (result != inter->global_object_map->end())
        return result->second;
    else
        throw exception();
}

ObjectContainer zyd2001::NewBie::Runner::getGlobalVariable(Identifier id)
{
    return inter->runner->variable_stack.top().back().at(id);
}

ObjectContainer zyd2001::NewBie::Runner::addGlobalVariable(Identifier id, ObjectContainer t, bool cons)
{
    return inter->runner->addVariable(id, t, cons);
}

ObjectContainer zyd2001::NewBie::Runner::addGlobalVariable(Identifier id, ObjectType t, ObjectContainer o, bool cons)
{
    return inter->runner->addVariable(id, t, o, cons);
}

ObjectContainer zyd2001::NewBie::Runner::addVariable(Identifier name, ObjectType type, ObjectContainer o, bool cons)
{
    auto result = current_obj_map->find(name);
    if (result != current_obj_map->end())
    {
        ObjectContainer oc(type, inter->root, cons);
        if (cons)
        {
            cons = false;
            oc->set(*this, o);
            cons = true;
        }
        else
            oc->set(*this, o);
        current_obj_map->emplace(name, oc);
        return oc;
    }
    else
        throw exception();
}

ObjectContainer zyd2001::NewBie::Runner::addVariable(Identifier name, ObjectContainer o, bool cons)
{
    auto result = current_obj_map->find(name);
    if (result != current_obj_map->end())
    {
        ObjectContainer oc(o->restrict_type, inter->root, cons);
        if (cons)
        {
            cons = false;
            oc->set(*this, o);
            cons = true;
        }
        else
            oc->set(*this, o);
        current_obj_map->emplace(name, oc);
        return oc;
    }
    else
        throw exception();
}