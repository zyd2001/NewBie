#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

object_container_t::object_container_t(object_t * o) : obj(o), restrict_type(o->cl->type), is_const(true), belongs_to(o->runner.inter->temp)
{
    o->runner.inter->addGCEdge(belongs_to, obj);
} //temp container
object_container_t::object_container_t(ObjectType t, object_t * belongs, bool cons = false) : restrict_type(t), belongs_to(belongs), obj(belongs->runner.inter->null), is_const(cons) 
{
    belongs_to->runner.inter->addGCEdge(belongs_to, obj);
}
object_container_t::~object_container_t()
{
    if (obj->cl->RAII)
    {
        Runner & runner = obj->runner;
        newNewBieStack();
        newNewBieScope();
        obj->cl->dtor->call(obj->runner, obj, Args(), ParameterList());
        delete obj;
    }
    belongs_to->runner.inter->delGCEdge(belongs_to, obj);
}

bool zyd2001::NewBie::object_container_t::typeCheck(object_t * o)
{
    if (obj->type == o->type)
        return true;
    return o->runner.inter->typeCheck(restrict_type, o);
}

void zyd2001::NewBie::object_container_t::set(Runner & runner, ObjectContainer oc) // temporary ObjectContainer can only use once
{
    if (is_const)
        throw exception();
    else
    {
        object_t * o = oc->get();
        if (o == runner.inter->null)
            throw exception();
        if (typeCheck(o))
        {
            runner.inter->delGCEdge(belongs_to, obj);
            if (o->cl->RAII)
            {
                if (oc->belongs_to == runner.inter->temp) // if oc is a temp ObjectContainer, don't copy and change the state
                    oc->belongs_to = runner.inter->null; // if an RAII object belongs to null(not nullptr), it won't be deleted
                else
                    o = o->cl->makeObject(runner, Args{ o });
            }
            if (obj->cl->RAII)
                delete obj;
            obj = o;
            belongs_to->runner.inter->addGCEdge(belongs_to, obj);
        }
        else
            throw exception();
    }
}

object_t * zyd2001::NewBie::object_container_t::get()
{
    return obj;
}

ObjectContainer zyd2001::NewBie::ObjectContainer::copy(Runner & runner)
{
    auto p = make_shared<object_container_t>();
    p->belongs_to = ptr->obj->runner.inter->temp;
    p->set(runner, *this);
    p->is_const = true;
    return ObjectContainer(p);
}

ObjectContainer zyd2001::NewBie::ObjectContainer::getVariable(Runner & runner, Identifier id)
{
    return ptr->obj->getVariable(runner, id);
}

zyd2001::NewBie::object_container_t::object_container_t(Runner & runner) : is_const(true), obj(runner.inter->null), belongs_to(runner.inter->root) 
{
    belongs_to->runner.inter->addGCEdge(belongs_to, obj);
}

zyd2001::NewBie::ObjectContainer::ObjectContainer(Runner & runner) : ptr(std::make_shared<object_container_t>(runner)) {}

zyd2001::NewBie::ObjectContainer::ObjectContainer(object_t * o) : ptr(std::make_shared<object_container_t>(o)) {}

void zyd2001::NewBie::object_t::addVariable(Runner & runner, Identifier id, ObjectContainer o, AccessControl v, bool cons = false)
{
    ObjectContainer oc(o->restrict_type, this, cons);
    if (cons)
    {
        cons = false;
        oc->set(runner, o);
        cons = true;
    }
    else
        oc->set(runner, o);
    local_variables[id] = make_pair(oc, v);
}

void zyd2001::NewBie::object_t::addVariable(Runner & runner, Identifier id, ObjectType type, ObjectContainer o, AccessControl v, bool cons = false)
{
    ObjectContainer oc(type, this, cons);
    if (cons)
    {
        cons = false;
        oc->set(runner, o);
        cons = true;
    }
    else
        oc->set(runner, o);
    local_variables[id] = make_pair(oc, v);
}

ObjectContainer zyd2001::NewBie::object_t::getVariable(Runner & runner, Identifier id)
{
    auto item = local_variables.at(id);
    switch (item.second)
    {
        case PUBLIC:
            return item.first;
            break;
        case PROTECTED:
        case PRIVATE:
            if (runner.call_stack_func.top().second == this)
                return item.first;
            else
                throw exception();
            break;
    }
}

ObjectContainer zyd2001::NewBie::object_t::getVariableWithPrototype(Runner & runner, Identifier id, bool derived)
{
    bool flag = runner.call_stack_func.top().second == this;
    auto result = local_variables.find(id);
    if (result == local_variables.end())
    {
        try
        {
            return cl->getVariableWithPrototype(runner, id, flag);
        }
        catch (const std::exception&)
        {
            for (auto & o : bases)
            {
                try
                {
                    return o->getVariableWithPrototype(runner, id, true);
                }
                catch (const std::exception&)
                {
                    continue;
                }
            }
        }
    }
    else
    {
        switch (result->second.second)
        {
            case PUBLIC:
                return result->second.first;
            case PROTECTED:
                if (derived || flag)
                    return result->second.first;
                else
                    throw exception();
            case PRIVATE:
                if (flag)
                    return result->second.first;
                else
                    throw exception();
        }
    }
}

ObjectContainer zyd2001::NewBie::object_t::getSuperVariable(Runner & runner, Identifier id)
{
    for (auto & b : bases)
    {
        auto result = b->local_variables.find(id);
        if (result != b->local_variables.end())
        {
            if (result->second.second == PRIVATE)
                continue;
            else
                return result->second.first;
        }
        else
            continue;
    }
    throw exception();
}

ObjectContainer zyd2001::NewBie::object_t::getSuperVariable(Runner &runner, ObjectType type, Identifier id)
{
    return bases_mapped.at(type)->getVariableFromDerived(runner, id);
}

zyd2001::NewBie::object_t::~object_t()
{
    if (native_ptr != nullptr)
        cl->native_deleter(native_ptr);
    //for (auto iter = local_variables.begin(); iter != local_variables.end();)
    //{
    //    runner.inter->delGCEdge(this, iter->second.first->get());
    //    iter = local_variables.erase(iter);
    //}
    for (auto i : bases)
        delete i;
}

ObjectContainer zyd2001::NewBie::object_t::getVariableFromDerived(Runner & runner, Identifier id)
{
    auto item = local_variables.at(id);
    switch (item.second)
    {
        case PUBLIC:
        case PROTECTED:
            return item.first;
            break;
        case PRIVATE:
            throw exception();
            break;
    }
}

#define biop(op) \
ObjectContainer zyd2001::NewBie::ObjectContainer:: op (Runner & runner, const ObjectContainer &oc)\
{\
    return ptr->obj->cl->o. op (runner, ptr->obj, Args{ oc });\
}
biop(add)
biop(sub)
biop(mul)
biop(div)
biop(mod)
biop(lt)
biop(le)
biop(gt)
biop(ge)
biop(eq)
biop(ne)
biop(bit_and)
biop(bit_or)
biop(bit_xor)
biop(bit_left)
biop(bit_right)
biop(and)
biop(or)

ObjectContainer zyd2001::NewBie::ObjectContainer::minus(Runner & runner)
{
    return ptr->obj->cl->o.minus(runner, ptr->obj);
}
ObjectContainer zyd2001::NewBie::ObjectContainer::plus(Runner & runner)
{
    return ptr->obj->cl->o.plus(runner, ptr->obj);
}
ObjectContainer zyd2001::NewBie::ObjectContainer::not(Runner & runner)
{
    return ptr->obj->cl->o.not(runner, ptr->obj);
}
ObjectContainer zyd2001::NewBie::ObjectContainer::negate(Runner & runner)
{
    return ptr->obj->cl->o.negate(runner, ptr->obj);
}
ObjectContainer zyd2001::NewBie::ObjectContainer::index(Runner & runner, const ObjectContainer & oc)
{
    return ptr->obj->cl->o.index(runner, ptr->obj, Args{ oc });
}
bool zyd2001::NewBie::ObjectContainer::toBool(Runner & runner) const
{
    ObjectContainer o = ptr->obj->cl->o.toBool(runner, ptr->obj);
    return o->getBool();
}

ObjectContainer zyd2001::NewBie::ObjectContainer::call(Runner & runner, const Args & args)
{
    return ptr->obj->cl->o.call(runner, ptr->obj, args);
}

ObjectContainer zyd2001::NewBie::ObjectContainer::call(Runner & runner, const ArgumentList & alist)
{
    return call(runner, runner.resolveArgumentList(alist));
}

ObjectContainer zyd2001::NewBie::ObjectContainer::call(Runner & runner, Identifier id, const Args & args) const
{
    auto f = ptr->obj->getVariableWithPrototype(runner, id, false);
    runner.this_ptr = ptr->obj;
    return f.call(runner, args);
}

ObjectContainer zyd2001::NewBie::ObjectContainer::call(Runner & runner, Identifier id, const ArgumentList & alist) const
{
    return call(runner, id, runner.resolveArgumentList(alist));
}