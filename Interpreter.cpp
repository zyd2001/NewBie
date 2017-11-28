#include "NewBie_Lang.hpp"
#include "NewBie.hpp"
#include <FlexLexer.h>

#include <iostream>
#include <fstream>

using namespace zyd2001::NewBie;
using namespace std;

Interpreter::Interpreter() : imp(new InterpreterImp()) {}
Interpreter::Interpreter(const std::string &name) : imp(new InterpreterImp(name)) {}
bool Interpreter::interprete() { return imp->interprete(); }
bool Interpreter::setFile(const std::string &name) { return imp->setFile(name); }

Interpreter::InterpreterImp::InterpreterImp() {}
Interpreter::InterpreterImp::InterpreterImp(const std::string &name) : file(new ifstream(name)), filename(name) {}
bool Interpreter::InterpreterImp::setFile(const std::string &name)
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

bool Interpreter::InterpreterImp::interprete()
{
	return true;
}

//int Interpreter::InterpreterImp::parse()
//{
//	unique_ptr<FlexLexer> lexer;
//	if (file->is_open())
//		lexer = make_unique<yyFlexLexer>(file.get(), cout);
//	else
//		lexer = make_unique<yyFlexLexer>();
//	Parser parser(*this);
//	return parser.parse();
//}

int main()
{
	Value v1(233);
	Value v2(U("哈哈"));
	Value v3 = v1 + v2;
	Value v4 = v3;
	Value v5;
	Value *v = new Value(std::move(v1));
	v5 = Value(1);
	v4 = v3 * 3;
	cout << v3 << endl;
	cout << v1 << endl;
	cout << boolalpha << (v1 == v2) << endl;
}