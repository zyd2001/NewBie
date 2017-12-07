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

	//initialize the environment
	variables_stack.push(vector<unordered_map<Identifier, Value>>());
	variables_stack.top().push_back(unordered_map<Identifier, Value>());
	global_variables = &variables_stack.top().back();
	if (false) //according to the setting
		variables_stack.top().push_back(unordered_map<Identifier, Value>());
	interpret(statements_list);
	variables_stack.pop();
	return true;
}

int InterpreterImp::interpret(const StatementsList &s)
{
	StatementType result;
	auto end = s.cend();
	for (auto &iter : s)
	{
		execute(iter);
	}
	return 1;
}

int InterpreterImp::checkExist(const Identifier &id, std::vector<std::unordered_map<Identifier, Value>> &v)
{
	for (auto i = v.size(); i > 0; i--)
	{
		auto result = v[i - 1].find(id);
		if (result != v[i - 1].cend())
			return i;
		else
			continue;
	}
	auto result = global_variables->find(id);
	if (result != global_variables->cend())
		return 0;
	else
		return -1;
}

void InterpreterImp::err() {}
StatementType InterpreterImp::execute(const Statement &s)
{
	auto &v = variables_stack.top();
	switch (s.type)
	{
		case zyd2001::NewBie::EXPRESSION_STATEMENT:
			evaluate(s.get<Expression>());
			break;
		case zyd2001::NewBie::ASSIGNMENT_STATEMENT:
		{
			AssignmentStatement &as = s.get<AssignmentStatement>();
			int res = checkExist(as.identifier, v);
			if (res == -1)
			{
				err();
			}
			else
			{
				Value &&val = evaluate(as.value);
				unordered_map<Identifier, Value>::iterator result;
				if (res == 0)
					result = global_variables->find(as.identifier);
				else
					result = v[res - 1].find(as.identifier);
				Value &target = result->second;
				if (!target.various && target.type != val.type)
				{
					err();
				}
				else
				{
					target = val;
				}
			}
			break;
		}
		case zyd2001::NewBie::DECLARATION_STATEMENT:
		{
			DeclarationStatement &ds = s.get<DeclarationStatement>();
			for (auto &iter : ds.items)
			{
				int res = checkExist(iter.identifier, v);
				if (res == -1)
				{
					err();
				}
				else
				{
					unordered_map<Identifier, Value> *vmap;
					if (ds.global)
						vmap = global_variables;
					else
						vmap = &v.back();
					if (iter.initial_value.type != NULL_EXPRESSION)
						(*vmap)[iter.identifier] = evaluate(iter.initial_value).change_type(ds.type);
					else
						(*vmap)[iter.identifier] = Value(ds.type);
				}
			}
			break;
		}
		case zyd2001::NewBie::BLOCK_STATEMENT:
			v.push_back(unordered_map<Identifier, Value>());
			interpret(s.get<BlockStatement>());
			v.pop_back();
			break;
		case zyd2001::NewBie::IF_STATEMENT:
		{
			IfStatement &ifs = s.get<IfStatement>();
			if (evaluate(ifs.condition).change_type(BOOL_TYPE).get<bool>())
			{
				execute(ifs.stat);
			}
			else
			{
				bool flag = true;
				if (!ifs.elseif.empty()) //determine else if statement
				{
					for (auto &i : ifs.elseif)
					{
						if (evaluate(i.condition).change_type(BOOL_TYPE).get<bool>())
						{
							execute(i.stat);
							flag = false;
							break;
						}
					}
				}
				if (ifs.else_stat.type != NULL_STATEMENT && flag);
				{
					execute(ifs.else_stat);
				}
			}
			break;
		}
		case zyd2001::NewBie::FOR_STATEMENT:
		{
			ForStatement &fs = s.get<ForStatement>();
			for (evaluate(fs.exp1); evaluate(fs.exp2).change_type(BOOL_TYPE).get<bool>(); evaluate(fs.exp3))
				execute(fs.stat);
			break;
		}
		case zyd2001::NewBie::FOREACH_STATEMENT:
			break;
		case zyd2001::NewBie::RETURN_STATEMENT:
		{
			temp_variable = evaluate(s.get<ReturnStatement>());
			break;
		}
		case zyd2001::NewBie::CONTINUE_STATEMENT:
			break;
		case zyd2001::NewBie::BREAK_STATEMENT:
			break;
		default:
			break;
	}
	return s.type;
}