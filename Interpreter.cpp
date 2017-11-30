#include "NewBie_Lang.hpp"
#include "NewBie.hpp"
#include "NewBie_Parser.hpp"
#include <FlexLexer.h>

#include <iostream>
#include <fstream>

using namespace zyd2001::NewBie;
using namespace std;

Interpreter::Interpreter() : imp(new InterpreterImp()) {}
Interpreter::Interpreter(const std::string &name) : imp(new InterpreterImp(name)) {}
bool Interpreter::interprete() { return imp->interprete(); }
bool Interpreter::setFile(const std::string &name) { return imp->setFile(name); }

InterpreterImp::InterpreterImp() {}
InterpreterImp::InterpreterImp(const std::string &name) : file(new ifstream(name)), filename(name) {}
bool InterpreterImp::setFile(const std::string &name)
{
	filename = name;
	unique_ptr<ifstream> f(new ifstream(name));
	if (f->is_open())
		file.swap(f);
	else
	{
		cerr << "Fail open input file" << endl;
		return false;
	}
	return true;
}

bool InterpreterImp::interprete()
{
	return true;
}

int InterpreterImp::parse()
{
	unique_ptr<yyFlexLexer> lexer;
	if (file->is_open())
		lexer = make_unique<yyFlexLexer>(file.get(), cout);
	else
		lexer = make_unique<yyFlexLexer>();
	Parser parser(*this, lexer.get());
	return parser.parse();
}

int main()
{
	Interpreter inter("test");
}