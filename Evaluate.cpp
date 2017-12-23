#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

Value &InterpreterImp::evaluate(const Expression &e)
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
                return (*variables_stack.top())[res - 1].at(e.get<IdentifierExpression>());
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
                    temp_variable = evaluate(be.lexp) == evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::NE:
                    temp_variable = evaluate(be.lexp) != evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::GT:
                    temp_variable = evaluate(be.lexp) > evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::GE:
                    temp_variable = evaluate(be.lexp) >= evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::LT:
                    temp_variable = evaluate(be.lexp) < evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::LE:
                    temp_variable = evaluate(be.lexp) <= evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::AND:
                    temp_variable = evaluate(be.lexp) && evaluate(be.rexp);
                    break;
                case zyd2001::NewBie::OR:
                    temp_variable = evaluate(be.lexp) || evaluate(be.rexp);
                    break;
                default:
                    break;
                return temp_variable;
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
                    temp_variable = !evaluate(ue.exp);
                    return temp_variable;
                    break;
                default:
                    break;
            }
            break;
        }
        case zyd2001::NewBie::FUNCTION_CALL_EXPRESSION:
        {
            FunctionCallExpression &fce = e.get<FunctionCallExpression>();
            int res = checkExist(fce.identifier);
            if (res == -1)
                err();
            else
            {
                Value *f;
                if (res == 0)
                    f = &global_variables.at(fce.identifier);
                else
                    f = &(*variables_stack.top())[res - 1].at(fce.identifier);
                if (f->type != FUNCTION_TYPE)
                    err();
                else
                {
                    Function func = f->get<Function>();

                    return callFunc(func, fce.alist);
                }
            }
            break;
        }
        case zyd2001::NewBie::ARRAY_EXPRESSION:
        {
            auto &ae = e.get<ArrayExpression>();
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
            auto &ie = e.get<IndexExpression>();
            return evaluate(ie.exp).get<Array>()[evaluate(ie.index).change_type(INT_TYPE).get<int>()];
            break;
        }
        case THIS_EXPRESSION:
        {
            if (in_obj)
                return *current_object;
            else
                err("use this outside class");
            break;
        }
        case DOT_FUNC_EXPRESSION:
        {
            auto &dfe = e.get<DotFuncCall>();
            Value obj = evaluate(dfe.obj);
            break;
        }
        case DOT_ID_EXPRESSION:
        {
            auto &die = e.get<DotID>();
            Value obj = evaluate(die.obj);
            //override the env
            variables_stack.push(make_temp_unit(obj.get<Object>()->local_env));
            int res = checkExist(die.id, false);
            if (res == -1)
                err();
            else
                return (*variables_stack.top())[res - 1].at(die.id);
            break;
        }
        case NEW_OBJECT_EXPRESSION:
        {
            auto &noe = e.get<FunctionCallExpression>(); //just different TYPE
            auto result = class_map.find(noe.identifier);
            if (result != class_map.cend())
            {
                auto &cl = result->second;
                auto ptr = new Object();
                auto &obj = **ptr;
                Value val(OBJECT_TYPE, ptr);
                obj.type = noe.identifier;
                //to initialize the local variables in the object
                variables_stack.push(make_temp_unit(obj.local_env));
                //support "this" expression
                current_object = &val;
                in_obj = true;
                //call ctor
                interpret(cl.slist);
                callFunc(cl.ctor, noe.alist);

                current_object = nullptr;
                in_obj = false;

                variables_stack.pop();
            }
            else
                err("no such class");
            break;
        }
        default:
            break;
    }
    return Value();
}