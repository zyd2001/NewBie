#ifndef NEWBIE_LANG_HPP
#define NEWBIE_LANG_HPP
#include <string>

namespace zyd2001
{
    namespace NewBie
    {
        class InterpreterImp;
        class Interpreter
        {
        public:
            Interpreter();
            Interpreter(const std::string &name);
            ~Interpreter();
            bool setFile(const std::string &name);
            bool changeSetting(const std::string &, int);
            bool run();
            void parse();
        private:
            InterpreterImp *imp;
        };
    }
}
#endif