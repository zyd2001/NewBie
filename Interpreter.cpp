#include "NewBie_Lang.hpp"
#include "NewBie.hpp"
#include "Parser.hpp"

#include <iostream>
#include <fstream>

using namespace zyd2001::NewBie;
using namespace std;

Interpreter::Interpreter() : imp(new InterpreterImp()) {}
Interpreter::Interpreter(const std::string &name) : imp(new InterpreterImp(name)) {}
bool Interpreter::run() { return imp->run(); }
bool Interpreter::setFile(const std::string &name) { return imp->setFile(name); }
bool Interpreter::changeSetting(const string &key, int value) { return imp->changeSetting(key, value); };

int zyd2001::NewBie::Interpreter::parse()
{
    return imp->parse();
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

int InterpreterImp::parse()
{
    yyscan_t scanner;
    yylex_init(&scanner);
    FILE *fp = fopen(filename.c_str(), "r");
    yyset_in(fp, scanner);
    Parser parser(*this, scanner);
    parser.parse();
    yylex_destroy(scanner);
    fclose(fp);
    return 1;
}

int main()
{
    Interpreter inter("test");
    inter.parse();
    try
    {
        inter.run();
    }
    catch (runtime_error e)
    {
        cerr << e.what() << endl;
    }
}