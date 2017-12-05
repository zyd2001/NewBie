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
	vector<int> a = { 1, 2, 3, 4, 5, 6 };
	auto iter = a.rbegin();
	iter += 2;
	auto i = distance(iter, a.rend());
	auto b = *iter == a[i - 1];
}