#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

ObjectContainer zyd2001::NewBie::NormalFunction::call(Runner &runner, object_t * o, const Args & args, const ParameterList & plist)
{
    for (int i = 0; i < args.size(); i++)
    {
        if (!plist[i].ref)
            runner.addVariable(plist[i].identifier, plist[i].type, args[i], plist[i].cons);
        else
            runner.addRefVariable(plist[i].identifier, args[i]);
    }
    if (o != runner.call_stack_func.top().second)
    {
        useNewBieFunc(shared_from_this(), o);
        runner.execute(s);
        return runner.returnVal();
    }
    else
    {
        runner.execute(s);
        return runner.returnVal();
    }
}

ObjectContainer zyd2001::NewBie::NativeFunction::call(Runner &runner, object_t * o, const Args & args, const ParameterList & plist)
{
    //if (plist[0].identifier != for_functionCall)
    //    for (int i = 0; i < args.size(); i++)
    //    {
    //        bool result = runner.inter->typeCheck(plist[i].type, args[i]->get());
    //        if (!result)
    //            throw exception();
    //    }
    if (o != runner.call_stack_func.top().second)
    {
        useNewBieFunc(shared_from_this(), o);
        return native_func(runner, o, args);
    }
    else
        return native_func(runner, o, args);
}

Identifier zyd2001::NewBie::function_t::getName()
{
    return name;
}

ObjectContainer zyd2001::NewBie::function_t::call(Runner & runner, object_t * o, const Args & args)
{
    newNewBieStack();
    newNewBieScope();
    ParameterList &plist = runner.argsToParams(args);
    if (can_overload)
    {
        auto f = overload_map.find(plist);
        if (f != overload_map.end())
            return f->second->call(runner, o, args, f->first);
        else
            throw exception();
    }
    else
    {
        auto f = overload_map.begin(); //need check
        return f->second->call(runner, o, args, f->first);
    }
}

ObjectContainer zyd2001::NewBie::function_t::call(Runner & runner, object_t * o, const ArgumentList & alist)
{
    return call(runner, o, runner.resolveArgumentList(alist));
}

ObjectContainer zyd2001::NewBie::function_t::call_f(Runner & runner, object_t * o, const Args & args)
{
    auto & stack_top = runner.call_stack_func.top();
    stack_top.second = o;
    ParameterList &plist = runner.argsToParams(args);
    if (can_overload)
    {
        auto f = overload_map.find(plist);
        if (f != overload_map.end())
        {
            stack_top.first = f->second;
            return f->second->call(runner, o, args, f->first);
        }
        else
            throw exception();
    }
    else
    {
        auto f = overload_map.begin(); //need check
        stack_top.first = f->second;
        return f->second->call(runner, o, args, f->first);
    }
}

zyd2001::NewBie::function_t::function_t(Identifier name, init_vec & vec) : name(name)
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