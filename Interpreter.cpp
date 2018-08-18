#include "NewBie_Lang.hpp"
#include "NewBie.hpp"
#include "Parser.hpp"

#include <iostream>
#include <fstream>
#include <cstdio>

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

InterpreterImp::InterpreterImp() : InterpreterImp(string()) {}
InterpreterImp::InterpreterImp(const std::string &filename) : filename(filename)
{
    runner = make_unique<Runner>(this);
    null = new object_t(*runner);
    root = new object_t(*runner);
    temp = new object_t(*runner);
    addGCVertex(null);
    addGCVertex(root);
    null_obj = new ObjectContainer(*runner);
    global_object_map = &runner->variable_stack.top().back();
    nullFunc = make_shared<func_t>(NewBie_Variant, true, [&](Runner & runner, object_t * obj, const Args & args) { return *null_obj; });
    nFunc = make_shared<function_t>(for_functionCall, function_t::init_vec{make_pair(ParameterList{ Parameter(NewBie_Variant, Expression(), false, false, for_functionCall) }, nullFunc)});
    primitive_class[NewBie_Object] = makeObjectClass();
    primitive_class[NewBie_Int] = makeIntClass();
    primitive_class[NewBie_Double] = makeDoubleClass();
    primitive_class[NewBie_Boolean] = makeBooleanClass();
    primitive_class[NewBie_String] = makeStringClass();
    primitive_class[NewBie_Function] = makeFunctionClass();
    primitive_class[NewBie_Class] = makeClassClass();
    null->cl = primitive_class[NewBie_Object];
    runner->addGlobalVariable(object_str, NewBie_Class, ObjectContainer(*runner, primitive_class[NewBie_Object]));
    runner->addGlobalVariable(int_str, NewBie_Class, ObjectContainer(*runner, primitive_class[NewBie_Int]));
    runner->addGlobalVariable(double_str, NewBie_Class, ObjectContainer(*runner, primitive_class[NewBie_Double]));
    runner->addGlobalVariable(boolean_str, NewBie_Class, ObjectContainer(*runner, primitive_class[NewBie_Boolean]));
    runner->addGlobalVariable(string_str, NewBie_Class, ObjectContainer(*runner, primitive_class[NewBie_String]));
    runner->addGlobalVariable(function_str, NewBie_Class, ObjectContainer(*runner, primitive_class[NewBie_Function]));
    runner->addGlobalVariable(class_str, NewBie_Class, ObjectContainer(*runner, primitive_class[NewBie_Class]));
}

zyd2001::NewBie::InterpreterImp::~InterpreterImp()
{
    delete null_obj;
    GC(); // gc will delete null
    delete root;
    delete temp;
}

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
    throw exception();
    thread t(&InterpreterImp::performGC, this);
    t.detach();
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
    runner->interpret(statement_list);
    return false;
}

void zyd2001::NewBie::InterpreterImp::addGCVertex(object_t * o)
{
    assert(o != nullptr);
    if (!o->cl->RAII)
        gc_graph.addVertex(o);
}

void zyd2001::NewBie::InterpreterImp::delGCVertex(object_t * o)
{
    assert(o != nullptr);
    if (!o->cl->RAII)
    {
        gc_graph.delVertex(o);
        delete o;
    }
}

void zyd2001::NewBie::InterpreterImp::addGCEdge(object_t *v, object_t *w)
{
    assert(v != nullptr && w != nullptr);
    if (w->cl->RAII)
        return;
    if (v->cl->RAII || v == temp) // temporary non-RAII object belongs to root
        gc_graph.addEdge(root, w);
    else
        gc_graph.addEdge(v, w);
}

void zyd2001::NewBie::InterpreterImp::delGCEdge(object_t *v, object_t *w)
{
    assert(v != nullptr && w != nullptr);
    if (w->cl->RAII)
        return;
    if (v->cl->RAII || v == temp) // an object belongs to an RAII object actually belongs to root
        gc_graph.delEdge(root, w);
    else
        gc_graph.delEdge(v, w);
}

bool zyd2001::NewBie::InterpreterImp::typeCheck(ObjectType t, object_t * o)
{
    if (t == NewBie_Variant)
        return true;
    if (t == o->type)
        return true;
    else
    {
        for (auto &b : o->all_bases)
            if (t == b.second->type)
                return true;
        return false;
    }
}

Class zyd2001::NewBie::InterpreterImp::findClass(Identifier id)
{
    return class_map.second.at(class_map.first.at(id));
}

Class zyd2001::NewBie::InterpreterImp::findClass(ObjectType type)
{
    return class_map.second.at(type);
}

ObjectType zyd2001::NewBie::InterpreterImp::findClassId(Identifier id)
{
    return class_map.first.at(id);
}

void zyd2001::NewBie::InterpreterImp::registerClass(Identifier type_name, std::vector<ObjectType>& base, bool RAII, bool editable, bool isFinal,
    Constructor ctor, Func dtor, Operator & o, class_t::vars & variables, std::function<void(void*)> native_deleter)
{
    class_count++;
    vector<Class> base_list;
    for (auto & i : base)
    {
        Class c = findClass(i);
        if (c->isFinal)
            throw exception();
        base_list.emplace_back(c);
    }
    Class cl = make_shared<class_t>(this, type_name, class_count, base_list, RAII, editable, isFinal, ctor, dtor, o, variables, native_deleter);
    class_map.first[type_name] = class_count;
    class_map.second[class_count] = cl;
}

void zyd2001::NewBie::InterpreterImp::registerClass(Identifier type_name, std::vector<Identifier>& base, bool RAII, bool editable, bool isFinal,
    Constructor ctor, Func dtor, Operator & o, class_t::vars & variables, std::function<void(void*)> native_deleter)
{
    class_count++;
    vector<Class> base_list;
    for (auto & i : base)
    {
        Class c = findClass(i);
        if (c->isFinal)
            throw exception();
        base_list.emplace_back(c);
    }
    Class cl = make_shared<class_t>(this, type_name, class_count, base_list, RAII, editable, isFinal, ctor, dtor, o, variables, native_deleter);
    class_map.first[type_name] = class_count;
    class_map.second[class_count] = cl;
}