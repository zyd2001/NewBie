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

void zyd2001::NewBie::InterpreterImp::declareVariable(Identifier id, ValueType type, bool global = false)
{
    VariableMap *env;
    if (global)
        env = &global_variables;
    else
        env = &variables_stack.top()->back();
    auto result = env->find(id);
    if (result != env->cend())
        return;
    else
        env->at(id) = Value(type);
}

void zyd2001::NewBie::InterpreterImp::declareVariable(Identifier id, Identifier type, bool global)
{
    try
    {
        declareVariable(id, (ValueType)class_map.first.at(type), global);
    }
    catch (out_of_range e)
    {
        err();
        return;
    }
}

void zyd2001::NewBie::InterpreterImp::changeVariable(Identifier id, Value &v, bool global)
{
    VariableMap *env;
    if (global)
        env = &global_variables;
    else
        env = &variables_stack.top()->back();
    try
    {
        auto lval = env->at(id);
        if (lval.various)
        {
            v.various = true;
            lval = v;
        }
        else if (typeCheck(lval.type, v))
        {
            v.various = false;
            lval = v;
        }
        else
        {
            err();
        }
    }
    catch (out_of_range e)
    {
        err();
        return;
    }
}

void zyd2001::NewBie::InterpreterImp::registerClass(Class &cl)
{
    auto type = cl.type;
    auto result = class_map.first.find(type);
    if (result != class_map.first.cend())
        return;
    else
    {
        class_count++;
        cl.id = class_count + 7;
        class_map.first[type] = cl.id;
        class_map.second[cl.id] = cl;
    }
}

void zyd2001::NewBie::InterpreterImp::registerFunction(Identifier, function_t &)
{}

bool zyd2001::NewBie::InterpreterImp::typeCheck(ValueType type, Value &v)
{
    if (type == v.type)
        return true;
    else
    {
        auto obj = v.get<Object>();
        if (obj->cl->id == type)
            return true;
        else
        {
            for (auto iter = obj->bases.crbegin(); iter != obj->bases.crend(); iter++)
            {
                if ((*iter)->cl->id == type)
                    return true;
            }
        }
    }
    return false;
}

bool zyd2001::NewBie::InterpreterImp::typeCheck(Identifier type, Value &v)
{
    try
    {
        auto id = class_map.first.at(type);
        auto obj = v.get<Object>();
        if (obj->cl->id == id)
            return true;
        else
        {
            for (auto iter = obj->bases.crbegin(); iter != obj->bases.crend(); iter++)
            {
                if ((*iter)->cl->id == id)
                    return true;
            }
        }
    }
    catch (out_of_range e)
    {
        return false;
    }
    return false;
}

void zyd2001::NewBie::disabled_deleter(vector<VariableMap> *p) {}
void zyd2001::NewBie::enabled_deleter(vector<VariableMap> *p) { delete p; }
stack_unit zyd2001::NewBie::make_stack_unit() { return unique_ptr<std::vector<VariableMap>, deleter>(new std::vector<VariableMap>(), &enabled_deleter); }
stack_unit zyd2001::NewBie::make_temp_unit(std::vector<VariableMap> &u) { return unique_ptr<std::vector<VariableMap>, deleter>(&u, &disabled_deleter); }
void InterpreterImp::initialize_obj_env(Value &o)
{
    auto &obj = o.get<Object>();
    in_object = true;
    current_object = &o;
    object_env_stack.push(current_object);
}
void InterpreterImp::restore_obj_env()
{
    object_env_stack.pop();
    if (object_env_stack.empty())
    {
        in_object = false;
        current_object = nullptr;
    }
    else
    {
        auto &env = object_env_stack.top();
        current_object = env;
    }
    //variables_stack.pop();
}