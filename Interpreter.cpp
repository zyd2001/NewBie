#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

#include <iostream>
#include <fstream>

using namespace zyd2001::NewBie;
using namespace std;
#define I Interpreter::InterpreterImp

Interpreter::Interpreter() : imp(new InterpreterImp()) {}
Interpreter::Interpreter(const std::string &name) : imp(new InterpreterImp(name)) {}
bool Interpreter::interprete() { return imp->interprete(); }
bool Interpreter::setFile(const std::string &name) { return imp->setFile(name); }

I::InterpreterImp() {}
I::InterpreterImp(const std::string &name) : file(new ifstream(name)), filename(name) {}
bool I::setFile(const std::string &name)
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

bool I::interprete()
{
	return true;
}

int main()
{
	Value v1(123);
	Value v2(U("233"));
	Value v3 = v1 + v2;
	Value v4 = v3;
	v1 = v3 * 3;
	cout << v3 << endl;
	cout << v1 << endl;
}