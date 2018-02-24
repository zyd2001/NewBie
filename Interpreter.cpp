#include "NewBie_Lang.hpp"
#include "NewBie.hpp"
#include "Parser.hpp"

#include <iostream>
#include <fstream>

using namespace zyd2001::NewBie;
using namespace std;

InterpreterImp *inter;

Interpreter::Interpreter() : imp(new InterpreterImp()) {}
Interpreter::Interpreter(const std::string &name) : imp(new InterpreterImp(name)) {}
zyd2001::NewBie::Interpreter::~Interpreter()
{
    delete imp;
}
bool Interpreter::run() { inter = imp; return imp->run(); }
bool Interpreter::setFile(const std::string &name) { return imp->setFile(name); }
bool Interpreter::changeSetting(const string &key, int value) { return imp->changeSetting(key, value); };

void zyd2001::NewBie::Interpreter::parse()
{
    imp->parse();
}

InterpreterImp::InterpreterImp() {}
InterpreterImp::InterpreterImp(const std::string &name) : filename(name) {}

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
    for (auto v : result)
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

IRAIIStack::RAIIStack()
{
    inter->variables_stack.emplace(vector<ObjectMap>());
    inter->variables_stack.top().emplace_back(ObjectMap());
    inter->current_variables = &inter->variables_stack.top().back();
}

RAIIStack::~RAIIStack()
{
    while (!inter->variables_stack.top().empty())
    {
        for (auto o : inter->variables_stack.top().back())
            inter->delGCEdge(inter->root, o.second);
        inter->variables_stack.top().pop_back();
    }
    inter->variables_stack.pop();
    inter->current_variables = &inter->variables_stack.top().back();
}

zyd2001::NewBie::RAIIScope::RAIIScope()
{
    inter->variables_stack.top().emplace_back(ObjectMap());
    inter->current_variables = &inter->variables_stack.top().back();
}

zyd2001::NewBie::RAIIScope::~RAIIScope()
{
    for (auto o : inter->variables_stack.top().back())
        inter->delGCEdge(inter->root, o.second);
    inter->variables_stack.top().pop_back();
    inter->current_variables = &inter->variables_stack.top().back();
}

RAIIObject::RAIIObject(Object obj)
{
    inter->current_object = obj.obj;
    inter->object_env_stack.push(obj.obj);
    inter->in_object = true;
}

zyd2001::NewBie::RAIIObject::RAIIObject(object_t *obj)
{
    inter->current_object = obj;
    inter->object_env_stack.push(obj);
    inter->in_object = true;
}

RAIIObject::~RAIIObject()
{
    inter->object_env_stack.pop();
    if (inter->object_env_stack.empty())
    {
        inter->in_object = false;
        inter->current_object = nullptr;
    }
    else
        inter->current_object = inter->object_env_stack.top();
}

RAIIClass::RAIIClass(Class cl)
{
    inter->current_class = cl.get();;
    inter->class_env_stack.push(cl.get());
    inter->in_class = true;
}

zyd2001::NewBie::RAIIClass::RAIIClass(class_t *cl)
{
    inter->current_class = cl;
    inter->class_env_stack.push(cl);
    inter->in_class = true;
}

RAIIClass::~RAIIClass()
{
    inter->class_env_stack.pop();
    if (inter->class_env_stack.empty())
    {
        inter->in_class = false;
        inter->current_class = nullptr;
    }
    else
        inter->current_class = inter->class_env_stack.top();
}

void InterpreterImp::parse()
{
    yyscan_t scanner;
    yylex_init(&scanner);
    FILE *fp = fopen(filename.c_str(), "r");
    yyset_in(fp, scanner);
    Parser parser(*this, scanner);
    parser.parse();
    yylex_destroy(scanner);
    fclose(fp);
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
    auto cl = inter->class_map.second.at(type);
    Object obj(cl->makeObject(ArgumentList()));
    (*obj_map)[id] = obj;
    addGCEdge(root, obj);
}

void zyd2001::NewBie::InterpreterImp::declareVariable(Identifier id, Identifier type_name, bool global)
{
    declareVariable(id, inter->class_map.first.at(type_name), global);
}

void zyd2001::NewBie::InterpreterImp::declareVariable(Identifier id, Object obj, bool global)
{
    ObjectMap *obj_map;
    if (global)
        obj_map = &global_variables;
    else
        obj_map = current_variables;
    auto v = obj_map->find(id);
    if (v != obj_map->end())
        throw exception();
    (*obj_map)[id] = obj;
    addGCEdge(root, obj);
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

Object zyd2001::NewBie::InterpreterImp::getVariable(Identifier id, bool global)
{
    ObjectMap *obj_map;
    if (global)
        obj_map = &global_variables;
    else
        obj_map = current_variables;
    return obj_map->at(id);
}

void zyd2001::NewBie::InterpreterImp::changeVariable(Identifier id, Object o, bool global)
{
    ObjectMap *obj_map;
    if (global)
        obj_map = &global_variables;
    else
        obj_map = current_variables;
    auto v = obj_map->at(id);
    if (typeCheck(v, o))
        v = o;
    else
        throw exception();
}

bool zyd2001::NewBie::InterpreterImp::typeCheck(Object l, Object r)
{
    if (l.obj->type == r.obj->type)
        return true;
    else
    {
        if (l.restrict_type == r.obj->type)
            return true;
        for (auto i : r.obj->bases)
            if (l.restrict_type == i->type)
                return true;
    }
    return false;
}

void zyd2001::NewBie::InterpreterImp::addGCVertex(Object o)
{
    gc_graph.addVertex(o.obj);
}

void zyd2001::NewBie::InterpreterImp::delGCVertex(Object o)
{
    gc_graph.delVertex(o.obj);
    delete o.obj;
}

void zyd2001::NewBie::InterpreterImp::addGCEdge(object_t *v, Object w)
{
    gc_graph.addEdge(v, w.obj);
}

void zyd2001::NewBie::InterpreterImp::addGCEdge(Object v, Object w)
{
    gc_graph.addEdge(v.obj, w.obj);
}

void zyd2001::NewBie::InterpreterImp::delGCEdge(object_t *v, Object w)
{
    gc_graph.delEdge(v, w.obj);
}

void zyd2001::NewBie::InterpreterImp::delGCEdge(Object v, Object w)
{
    gc_graph.delEdge(v.obj, w.obj);
}

std::vector<Object> zyd2001::NewBie::InterpreterImp::resolveArgumentList(ArgumentList &alist)
{
    std::vector<Object> args;
    for (auto a : alist)
        args.emplace_back(a->evaluate());
    return args;
}

ParameterList zyd2001::NewBie::InterpreterImp::ArgsToParams(std::vector<Object> &args)
{
    ParameterList params;
    for (auto arg : args)
    {
        params.emplace_back(Parameter());
        params.back().type = arg.obj->type;
    }
    return params;
}