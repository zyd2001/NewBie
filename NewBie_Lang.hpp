#ifndef NEWBIE_LANG_HPP
#define NEWBIE_LANG_HPP
#include <string>
#include <memory>

namespace zyd2001::NewBie
{
    class Interpreter
    {
    public:
        Interpreter();
        Interpreter(const std::string &name);
        ~Interpreter();
        bool interprete();
        bool setFile(const std::string &name);
    private:
        class InterpreterImp;
        std::unique_ptr<InterpreterImp> imp;
    };
}

#endif