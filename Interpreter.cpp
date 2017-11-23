#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using namespace zyd2001::NewBie;
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
	Value v(INT_TYPE, static_cast<void*>(new int(5)));
	v.change_type(STRING_TYPE);
	string a = (*static_cast<string*>(v.content));
}