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

RAIIStack::RAIIStack(InterpreterImp *inter)
{
    inter->variables_stack.emplace(vector<ObjectMap>());
    inter->variables_stack.top().emplace_back(ObjectMap());
    inter->current_variables = &inter->variables_stack.top().back();
}

RAIIStack::~RAIIStack()
{
    while (!inter->variables_stack.top().empty())
    {
        for (auto &o : inter->variables_stack.top().back())
            inter->delGCEdge(inter->root, o.second);
        inter->variables_stack.top().pop_back();
    }
    inter->variables_stack.pop();
    inter->current_variables = &inter->variables_stack.top().back();
}

zyd2001::NewBie::RAIIScope::RAIIScope(InterpreterImp *inter)
{
    inter->variables_stack.top().emplace_back(ObjectMap());
    inter->current_variables = &inter->variables_stack.top().back();
}

zyd2001::NewBie::RAIIScope::~RAIIScope()
{
    for (auto &o : inter->variables_stack.top().back())
        inter->delGCEdge(inter->root, o.second);
    inter->variables_stack.top().pop_back();
    inter->current_variables = &inter->variables_stack.top().back();
}

RAIIObject::RAIIObject(Object obj, InterpreterImp *inter)
{
    inter->current_object = obj.obj();
    inter->object_env_stack.push(obj.obj());
    inter->in_object = true;
}

zyd2001::NewBie::RAIIObject::RAIIObject(object_t *obj, InterpreterImp *inter)
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

RAIIClass::RAIIClass(Class cl, InterpreterImp *inter)
{
    inter->current_class = cl.get();;
    inter->class_env_stack.push(cl.get());
    inter->in_class = true;
}

zyd2001::NewBie::RAIIClass::RAIIClass(class_t *cl, InterpreterImp *inter)
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