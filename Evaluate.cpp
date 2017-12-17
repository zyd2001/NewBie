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
                if (res == 0)
                    return global_variables.at(e.get<IdentifierExpression>());
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
                    return -evaluate(ue.exp);
                    break;
                case zyd2001::NewBie::NOT:
                    return !evaluate(ue.exp);
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
                Value *f;
                if (res == 0)
                    f = &global_variables.at(fce.identifier);
                else
                    f = &variables_stack.top()[res - 1].at(fce.identifier);
                if (f->type != FUNCTION_TYPE)
                    err();
                else
                {
                    Function func = f->get<Function>();

                    //initialize the function local variables
                    StatementsList temp_slist;
                    vector<Expression> temp_elist;
                    ParametersList temp_plist;
                    for (auto &arg : fce.alist)
                    {
                        temp_elist.emplace_back(Expression(LITERAL_EXPRESSION, new Value(evaluate(arg))));
                        temp_plist.emplace_back(Parameter());
                        temp_plist.back().type = temp_elist.back().get<LiteralExpression>().type;
                    }
                    
                    variables_stack.push(vector<VariablesMap>());
                    variables_stack.top().push_back(VariablesMap());
                    decltype(func.overload_map.begin()) fbody;

                    if (func.can_overload)
                    {
                        fbody = func.overload_map.find(temp_plist);
                        if (fbody == func.overload_map.cend())
                            err();
                    }
                    else
                        fbody = func.overload_map.begin();

                    auto eiter = temp_elist.cbegin();
                    for (auto param = fbody->first.cbegin(); param != fbody->first.cend(); param++)
                    {
                        DeclarationStatementItemList item;
                        if (eiter != temp_elist.cend())
                        {
                            item.emplace_back(std::move(DeclarationStatementItem{ std::move(param->identifier), *eiter }));
                            eiter++;
                        }
                        else
                            item.emplace_back(std::move(DeclarationStatementItem{ std::move(param->identifier), param->default_value_exp }));
                        Statement temp(DECLARATION_STATEMENT, new (DeclarationStatement){ param->type, item, false }, -1);
                        execute(temp);
                    }

                    interpret(fbody->second.get<BlockStatement>());
                    variables_stack.pop();

                    return temp_variable;
                }
            }
            break;
        }
        case zyd2001::NewBie::ARRAY_EXPRESSION:
        {
            auto ae = e.get<ArrayExpression>();
            Value v;
            v.type = ARRAY_TYPE;
            v.content = new Array();
            Array &arr = v.get<Array>();
            for (auto &i : ae)
            {
                arr.emplace_back(evaluate(i));
            }
            return v;
            break;
        }
        case zyd2001::NewBie::INDEX_EXPRESSION:
        {
            auto ie = e.get<IndexExpression>();
            return evaluate(ie.exp).get<Array>()[evaluate(ie.index).change_type(INT_TYPE).get<int>()];
            break;
        }
        default:
            break;
    }
    return Value();
}