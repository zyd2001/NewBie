#ifndef NEWBIE_LANG_HPP
#define NEWBIE_LANG_HPP
#include <string>
#include <memory>

namespace zyd2001::NewBie
{
	class InterpreterImp;
    class Interpreter
    {
    public:
        Interpreter();
        Interpreter(const std::string &name);
		~Interpreter() = default;
        bool interprete();
        bool setFile(const std::string &name);
		int parse();
        std::unique_ptr<InterpreterImp> imp;
    private:
    };
}

#endif