#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

Value InterpreterImp::evaluate(const Expression &e)
{
    switch (e.type)
    {
        case zyd2001::NewBie::LITERAL_EXPRESSION:
            return e.get<LiteralExpression>();
            break;
        case zyd2001::NewBie::IDENTIFIER_EXPRESSION:
        {
            auto res = checkExist(e.get<IdentifierExpression>(), variables_stack.top());
            if (res == -1)
            {
                err();
            }
            else
            {
                return variables_stack.top()[res].find(e.get<IdentifierExpression>())->second;
            }
            break;
        }
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
        {
            FunctionCallExpression fce = e.get<FunctionCallExpression>();
            interpret(StatementsList(), true, false);
            return temp_variable;
            break;
        }
        case zyd2001::NewBie::ARRAY_EXPRESSION:
            break;
        case zyd2001::NewBie::INDEX_EXPRESSION:
            break;
        default:
            break;
    }
    return Value();
}