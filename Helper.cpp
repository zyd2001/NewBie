#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

RAIIStack::RAIIStack(Runner &r) : runner(r)
{
    runner.variable_stack.emplace(vector<ObjectMap>());
}

RAIIStack::~RAIIStack()
{
    runner.variable_stack.pop();
}

zyd2001::NewBie::RAIIScope::RAIIScope(Runner & r) : runner(r)
{
    runner.variable_stack.top().emplace_back(ObjectMap());
    runner.current_obj_map = &runner.variable_stack.top().back();
}

zyd2001::NewBie::RAIIScope::~RAIIScope()
{
    //for (auto iter = runner.current_obj_map->begin(); iter != runner.current_obj_map->end();)
    //{
    //    runner.inter->delGCEdge(runner.inter->root, iter->second->get());
    //    iter = runner.current_obj_map->erase(iter);
    //}
    runner.variable_stack.top().pop_back();
    if (runner.variable_stack.top().empty())
        runner.current_obj_map = nullptr;
    else
        runner.current_obj_map = &runner.variable_stack.top().back();
}

RAIIFunc::RAIIFunc(Func f, Runner & r, object_t * o) : runner(r)
{
    runner.call_stack_func.emplace(f, o);
}

RAIIFunc::~RAIIFunc()
{
    runner.call_stack_func.pop();
}

ParameterList zyd2001::NewBie::_params(std::vector<ObjectType> & vec)
{
    ParameterList plist;
    for (auto & i : vec)
        plist.emplace_back(Parameter(i));
    return plist;
}

helpStruct::helpStruct(const int &i) : type(NewBie_Int), ptr(i) {}
helpStruct::helpStruct(const double &i) : type(NewBie_Double), ptr(i) {}
helpStruct::helpStruct(const bool &i) : type(NewBie_Boolean), ptr(i) {}
helpStruct::helpStruct(const std::string &i) : type(NewBie_String), ptr(String(i)) {}
helpStruct::helpStruct(const String &i) : type(NewBie_String), ptr(i) {}