#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

auto checkExist(const Identifier &id, std::vector<std::unordered_map<Identifier, Value>> &v)
{
	for (auto i = v.size(); i > 0 ; i--)
	{
	    auto result = v[i].find(id);
		if (result != v[i].cend())
			return make_tuple(i, result);
		else
			continue;
	}
	return make_tuple(-1, v[0].find(id));
}

void InterpreterImp::err() {}
StatementType InterpreterImp::execute(const Statement &s, std::vector<std::unordered_map<Identifier, Value>> &v)
{
	switch (s.type)
	{
		case zyd2001::NewBie::EXPRESSION_STATEMENT:
			evaluate(s.get<Expression>());
			break;
		case zyd2001::NewBie::ASSIGNMENT_STATEMENT:
		{
			AssignmentStatement &as = s.get<AssignmentStatement>();
			auto res = checkExist(as.identifier, v);
			if (get<0>(res) == -1)
			{
				err();
			}
			else
			{
				get<1>(res)->second = evaluate(as.value);
			}
			break;
		}
		case zyd2001::NewBie::DECLARATION_STATEMENT:
		{
			DeclarationStatement &ds = s.get<DeclarationStatement>();
			for (auto iter = ds.items.cbegin(); iter != ds.items.cend(); iter++)
			{
				auto res = checkExist(iter->identifier, v);
				if (get<0>(res) == -1)
				{
					err();
				}
				else
				{
					if (iter->initial_value.type != NULL_EXPRESSION)
						(*v.end())[iter->identifier] = evaluate(iter->initial_value);
					else
						(*v.end())[iter->identifier] = Value();
				}
			}
			break;
		}
		case zyd2001::NewBie::BLOCK_STATEMENT:
			break;
		case zyd2001::NewBie::IF_STATEMENT:
			break;
		case zyd2001::NewBie::FOR_STATEMENT:
			break;
		case zyd2001::NewBie::FOREACH_STATEMENT:
			break;
		case zyd2001::NewBie::RETURN_STATEMENT:
			break;
		case zyd2001::NewBie::CONTINUE_STATEMENT:
			break;
		case zyd2001::NewBie::BREAK_STATEMENT:
			break;
		default:
			break;
	}
	return s.type;
}

Value InterpreterImp::evaluate(const Expression &e)
{
	switch (e.type)
	{
		case zyd2001::NewBie::LITERAL_EXPRESSION:
			return e.get<LiteralExpression>();
			break;
		case zyd2001::NewBie::IDENTIFIER_EXPRESSION:
			break;
		case zyd2001::NewBie::BINARY_EXPRESSION:
			switch (e.get<BinaryExpression>().type)
			{
				case zyd2001::NewBie::ADD:
					return evaluate(e.get<BinaryExpression>().lexp) + evaluate(e.get<BinaryExpression>().rexp);
					break;
				case zyd2001::NewBie::SUB:
					return evaluate(e.get<BinaryExpression>().lexp) - evaluate(e.get<BinaryExpression>().rexp);
					break;
				case zyd2001::NewBie::MUL:
					return evaluate(e.get<BinaryExpression>().lexp) * evaluate(e.get<BinaryExpression>().rexp);
					break;
				case zyd2001::NewBie::DIV:
					return evaluate(e.get<BinaryExpression>().lexp) / evaluate(e.get<BinaryExpression>().rexp);
					break;
				case zyd2001::NewBie::MOD:
					return evaluate(e.get<BinaryExpression>().lexp) % evaluate(e.get<BinaryExpression>().rexp);
					break;
				case zyd2001::NewBie::EQ:
					return evaluate(e.get<BinaryExpression>().lexp) == evaluate(e.get<BinaryExpression>().rexp);
					break;
				case zyd2001::NewBie::NE:
					return evaluate(e.get<BinaryExpression>().lexp) != evaluate(e.get<BinaryExpression>().rexp);
					break;
				case zyd2001::NewBie::GT:
					return evaluate(e.get<BinaryExpression>().lexp) > evaluate(e.get<BinaryExpression>().rexp);
					break;
				case zyd2001::NewBie::GE:
					return evaluate(e.get<BinaryExpression>().lexp) >= evaluate(e.get<BinaryExpression>().rexp);
					break;
				case zyd2001::NewBie::LT:
					return evaluate(e.get<BinaryExpression>().lexp) < evaluate(e.get<BinaryExpression>().rexp);
					break;
				case zyd2001::NewBie::LE:
					return evaluate(e.get<BinaryExpression>().lexp) <= evaluate(e.get<BinaryExpression>().rexp);
					break;
				case zyd2001::NewBie::AND:
					return evaluate(e.get<BinaryExpression>().lexp) && evaluate(e.get<BinaryExpression>().rexp);
					break;
				case zyd2001::NewBie::OR:
					return evaluate(e.get<BinaryExpression>().lexp) || evaluate(e.get<BinaryExpression>().rexp);
					break;
				default:
					break;
			}
			break;
		case zyd2001::NewBie::UNARY_EXPRESSION:
			break;
		case zyd2001::NewBie::FUNCTION_CALL_EXPRESSION:
			break;
		case zyd2001::NewBie::ARRAY_EXPRESSION:
			break;
		case zyd2001::NewBie::INDEX_EXPRESSION:
			break;
		default:
			break;
	}
	return Value();
}