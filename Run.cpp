#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

bool InterpreterImp::run()
{
	if (statements_list.empty())
	{
		throw runtime_error("No AST");
	}
	interpret(statements_list);
	return true;
}

int InterpreterImp::interpret(const StatementsList &s)
{
	auto end = s.cend();
	for (auto iter = s.cbegin(); iter != end; iter++)
	{
		execute(*iter, variables_stack.top());
	}
	return 1;
}