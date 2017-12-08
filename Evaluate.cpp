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
            int res = checkExist(e.get<IdentifierExpression>());
            if (res == -1)
            {
                err();
            }
            else
            {
                return variables_stack.top()[res - 1].at(e.get<IdentifierExpression>());
            }
            break;
        }
        case zyd2001::NewBie::BINARY_EXPRESSION:
        {
            BinaryExpression &be = e.get<BinaryExpression>();
            switch (be.type)
            {
                case zyd2001::NewBie::ADD:
                    return evaluate(be.lexp) + evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::SUB:
                    return evaluate(be.lexp) - evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::MUL:
                    return evaluate(be.lexp) * evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::DIV:
                    return evaluate(be.lexp) / evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::MOD:
                    return evaluate(be.lexp) % evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::EQ:
                    return evaluate(be.lexp) == evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::NE:
                    return evaluate(be.lexp) != evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::GT:
                    return evaluate(be.lexp) > evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::GE:
                    return evaluate(be.lexp) >= evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::LT:
                    return evaluate(be.lexp) < evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::LE:
                    return evaluate(be.lexp) <= evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::AND:
                    return evaluate(be.lexp) && evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::OR:
                    return evaluate(be.lexp) || evaluate(be.rexp);
                    break;
                default:
                    break;
            }
            break;
        }
        case zyd2001::NewBie::UNARY_EXPRESSION:
        {
            UnaryExpression &ue = e.get<UnaryExpression>();
            switch (ue.type)
            {
                case zyd2001::NewBie::MINUS:
                    break;
                case zyd2001::NewBie::NOT:
                    break;
                default:
                    break;
            }
            break;
        }
        case zyd2001::NewBie::FUNCTION_CALL_EXPRESSION:
        {
            FunctionCallExpression fce = e.get<FunctionCallExpression>();
            int res = checkExist(fce.identifier);
            if (res == -1)
                err();
            else
            {
                auto f = variables_stack.top()[res].at(fce.identifier);
                if (f.type != FUNCTION_TYPE)
                    err();
                else
                {
                    Function func = f.get<Function>();
                    variables_stack.push(vector<VariablesMap>());
                    VariablesMap vmap = variables_stack.top().back();

                    //initialize the function local variables
                    auto argument = fce.alist.cbegin();
                    for (auto iter = func.plist.cbegin(); iter != func.plist.cend(); iter++)
                    {
                        Expression val(LITERAL_EXPRESSION, nullptr);
                        if (argument != fce.alist.cend())
                            val.content = new LiteralExpression(evaluate(*argument));
                        else if (iter->default_value_exp.type != NULL_EXPRESSION)
                            val.content = new LiteralExpression(evaluate(iter->default_value_exp));
                        else
                            err();
                        Statement temp(ASSIGNMENT_STATEMENT, new (AssignmentStatement){std::move(iter->identifier), std::move(val)}, -1); //construct a assignment statement to assign parameter
                        execute(temp, false, false);
                    }

                    execute(func.body, true, false);
                    return temp_variable;
                }
            }
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