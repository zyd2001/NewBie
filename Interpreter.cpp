#include "NewBie_Lang.hpp"
#include "NewBie.hpp"
#include "Parser.hpp"

#include <iostream>
#include <fstream>

using namespace zyd2001::NewBie;
using namespace std;

//InterpreterImp *inter;

Interpreter::Interpreter() : imp(new InterpreterImp()) {}
Interpreter::Interpreter(const std::string &name) : imp(new InterpreterImp(name)) {}
zyd2001::NewBie::Interpreter::~Interpreter()
{
    delete imp;
}
bool Interpreter::run() { return imp->run(); }
bool Interpreter::setFile(const std::string &name) { return imp->setFile(name); }
bool Interpreter::changeSetting(const string &key, int value) { return imp->changeSetting(key, value); };

void zyd2001::NewBie::Interpreter::parse()
{
    imp->parse();
}

void zyd2001::NewBie::InterpreterImp::init()
{
    null = new object_t(this);
    root = new object_t(this);
    temp = new object_t(this);
}

InterpreterImp::InterpreterImp() { init(); }
InterpreterImp::InterpreterImp(const std::string &name) : filename(name) { init(); }

bool InterpreterImp::setFile(const std::string &name)
{
    filename = name;
    return true;
}

bool InterpreterImp::changeSetting(const std::string &key, int value)
{
    auto dest = settings.find(key);
    if (dest == settings.end())
        return false;
    else
    {
        dest->second = value;
        return true;
    }
}

void zyd2001::NewBie::InterpreterImp::performGC()
{
    auto result = gc_graph.dfs(root);
    for (auto &v : result)
    {
        if (!v.second)
        {
            gc_graph.delVertex(v.first);
            delete v.first;
        }
    }
}

void zyd2001::NewBie::InterpreterImp::GC()
{
    performGC();
}

void zyd2001::NewBie::InterpreterImp::concurrentGC()
{
    thread t(&InterpreterImp::performGC, this);
    t.detach();
}

Args zyd2001::NewBie::Runner::_makeArgs(std::vector<helpStruct>&v)
{
    Args args;
    for (auto &i : v)
    {
        switch (i.type)
        {
            case 2:
                args.emplace_back(ObjectContainer(inter, *static_cast<int*>(i.ptr)));
                break;
            case 3:
                args.emplace_back(ObjectContainer(inter, *static_cast<double*>(i.ptr)));
                break;
            case 4:
                args.emplace_back(ObjectContainer(inter, *static_cast<bool*>(i.ptr)));
                break;
            case 5:
                args.emplace_back(ObjectContainer(inter, *static_cast<String*>(i.ptr)));
                break;
        }
    }
    return args;
}

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
    for (auto iter = runner.current_obj_map->begin(); iter != runner.current_obj_map->end();)
    {
        runner.inter->delGCEdge(runner.inter->root, iter->second->get());
        iter = runner.current_obj_map->erase(iter);
    }
    runner.variable_stack.top().pop_back();
    runner.current_obj_map = &runner.variable_stack.top().back();
}

RAIIFunc::RAIIFunc(Identifier name, Func f, Runner & r) : runner(r)
{
    runner.call_stack.emplace(make_pair(name, f));
}

RAIIFunc::~RAIIFunc()
{
    runner.call_stack.pop();
}

ObjectContainer zyd2001::NewBie::Runner::addRefVariable(Identifier name, ObjectContainer oc)
{
    auto o = current_obj_map->find(name);
    if (o != current_obj_map->end())
        current_obj_map->emplace(name, oc);
    else
        throw exception();
}

ObjectContainer zyd2001::NewBie::Runner::addVariable(Identifier name, ObjectType type, ObjectContainer o, bool cons)
{
    auto oc = addVariable(name, type, cons);
    oc->set(*this, o);
    return oc;
}

ObjectContainer zyd2001::NewBie::Runner::addVariable(Identifier name, ObjectType type, bool cons)
{
    auto o = current_obj_map->find(name);
    if (o != current_obj_map->end())
    {
        ObjectContainer oc(make_shared<object_container_t>(type, inter->root, cons));
        current_obj_map->emplace(name, oc);
        return oc;
    }
    else
        throw exception();
}

void InterpreterImp::parse()
{
    yyscan_t scanner;
    yylex_init(&scanner);
    FILE *fp = fopen(filename.c_str(), "r");
    yyset_in(fp, scanner);
    zyd2001::NewBie::Parser parser(*this, scanner);
    parser.parse();
    yylex_destroy(scanner);
    fclose(fp);
}

bool zyd2001::NewBie::InterpreterImp::run()
{
    Runner runner(this);
    runner.interpret(statement_list);
    return false;
}

void zyd2001::NewBie::InterpreterImp::declareVariable(Identifier id, ObjectType type, bool global = false)
{
    ObjectMap *obj_map;
    if (global)
        obj_map = &global_variables;
    else
        obj_map = current_variables;
    auto v = obj_map->find(id);
    if (v != obj_map->end())
        throw exception();
    auto cl = class_map.second.at(type);
    Object obj(cl->makeObject(ArgumentList()));
    (*obj_map)[id] = obj;
    addGCEdge(root, obj);
}

void zyd2001::NewBie::InterpreterImp::declareVariable(Identifier id, Identifier type_name, bool global)
{
    declareVariable(id, class_map.first.at(type_name), global);
}

void zyd2001::NewBie::InterpreterImp::declareVariable(Identifier id, ObjectType type, Object obj, bool global)
{
    ObjectMap *obj_map;
    if (global)
        obj_map = &global_variables;
    else
        obj_map = current_variables;
    auto v = obj_map->find(id);
    if (v != obj_map->end())
        throw exception();
    if (typeCheck(type, obj))
    {
        (*obj_map)[id] = obj;
        addGCEdge(root, obj);
    }
    else
        throw exception();
}

void zyd2001::NewBie::InterpreterImp::deleteVariable(Identifier id, bool global)
{
    ObjectMap *obj_map;
    if (global)
        obj_map = &global_variables;
    else
        obj_map = current_variables;
    auto v = obj_map->find(id);
    if (v == obj_map->end())
        throw exception();
    delGCEdge(root, v->second);
    obj_map->erase(v);
}

Object &zyd2001::NewBie::InterpreterImp::getVariable(Identifier id, bool global)
{
    if (global)
        return global_variables.at(id);
    else
    {
        auto v = current_variables->find(id);
        if (v == current_variables->end())
        {
            for (auto iter = variables_stack.top().rbegin() + 1; iter != variables_stack.top().rend(); iter++)
            {
                v = iter->find(id);
                if (v != iter->end())
                    return v->second;
            }
            throw exception();
        }
        else
            return v->second;
    }
}

//void zyd2001::NewBie::InterpreterImp::changeVariable(Identifier id, Object o, bool global)
//{
//    if (global)
//    {
//        auto v = global_variables.at(id);
//        if (typeCheck(v, o))
//        {
//            delGCEdge(root, v);
//            v = o;
//            addGCEdge(root, o);
//        }
//        else
//            throw exception();
//    }
//    else
//    {
//        auto v = current_variables->find(id);
//        if (v == current_variables->end())
//        {
//            auto iter = variables_stack.top().rbegin() + 1;
//            for (; iter != variables_stack.top().rend(); iter++)
//            {
//                v = iter->find(id);
//                if (v != iter->end())
//                    break;
//            }
//            if (v == iter->end())
//                throw exception();
//        }
//        if (typeCheck(v->second, o))
//        {
//            delGCEdge(root, v->second);
//            v->second = o;
//            addGCEdge(root, o);
//        }
//        else
//            throw exception();
//    }
//}

bool zyd2001::NewBie::InterpreterImp::typeCheck(Object l, Object r)
{
    if (l.obj()->type == r.obj()->type)
        return true;
    else
        return typeCheck(l.restrict_type, r);
}

bool zyd2001::NewBie::InterpreterImp::typeCheck(ObjectType t, Object o)
{
    if (t == 0) //variant type
        return true;
    if (t == o.obj()->type)
        return true;
    for (auto &i : o.obj()->bases)
        if (t == i->type)
            return true;
    return false;
}

void zyd2001::NewBie::InterpreterImp::addGCVertex(object_t * o)
{
    if (o != nullptr && !o->cl->RAII)
        gc_graph.addVertex(o);
}

void zyd2001::NewBie::InterpreterImp::delGCVertex(object_t * o)
{
    if (o != nullptr && !o->cl->RAII)
    {
        gc_graph.delVertex(o);
        delete o;
    }
}

void zyd2001::NewBie::InterpreterImp::addGCEdge(object_t *v, object_t *w)
{
    if (v != nullptr && w != nullptr)
    {
        if (w->cl->RAII)
            return;
        if (v->cl->RAII || v == temp) // temporary non-RAII object belongs to root
            gc_graph.addEdge(root, w);
        else
            gc_graph.addEdge(v, w);
    }
}

void zyd2001::NewBie::InterpreterImp::delGCEdge(object_t *v, object_t *w)
{
    if (v != nullptr && w != nullptr)
    {
        if (w->cl->RAII)
            return; 
        if (v->cl->RAII || v == temp) // an object belongs to an RAII object actually belongs to root
            gc_graph.delEdge(root, w);
        else
            gc_graph.delEdge(v, w);
    }
}

Class zyd2001::NewBie::InterpreterImp::findClass(Identifier id)
{
    return class_map.second.at(class_map.first.at(id));
}

ObjectType zyd2001::NewBie::InterpreterImp::findClassId(Identifier id)
{
    return class_map.first.at(id);
}

std::vector<Object> zyd2001::NewBie::InterpreterImp::resolveArgumentList(ArgumentList &alist)
{
    std::vector<Object> args;
    for (auto &a : alist)
        args.emplace_back(a->evaluate());
    return args;
}

ParameterList zyd2001::NewBie::InterpreterImp::ArgsToParams(std::vector<Object> &args)
{
    ParameterList params;
    for (auto &arg : args)
    {
        params.emplace_back(Parameter());
        params.back().type = arg.obj()->type;
    }
    return params;
}