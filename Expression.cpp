#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

//extern InterpreterImp *inter;

//Value &InterpreterImp::evaluate(const Expression &e)
//{
//    switch (e.type)
//    {
//        case zyd2001::NewBie::LITERAL_EXPRESSION:
//            return e.get<LiteralExpression>();
//            break;
//        case zyd2001::NewBie::IDENTIFIER_EXPRESSION:
//        {
//            int res = checkExist(e.get<IdentifierExpression>());
//            if (res == -1)
//            {
//                err();
//            }
//            else
//            {
//                if (res == 0)
//                    return global_variables.at(e.get<IdentifierExpression>());
//                return (*variables_stack.top())[res - 1].at(e.get<IdentifierExpression>());
//            }
//            break;
//        }
//        case zyd2001::NewBie::BINARY_EXPRESSION:
//        {
//            BinaryExpression &be = e.get<BinaryExpression>();
//            switch (be.type)
//            {
//                case zyd2001::NewBie::ADD:
//                    temp_variable = evaluate(be.lexp) + evaluate(be.rexp);
//                    break;
//                case zyd2001::NewBie::SUB:
//                    temp_variable = evaluate(be.lexp) - evaluate(be.rexp);
//                    break;
//                case zyd2001::NewBie::MUL:
//                    temp_variable = evaluate(be.lexp) * evaluate(be.rexp);
//                    break;
//                case zyd2001::NewBie::DIV:
//                    temp_variable = evaluate(be.lexp) / evaluate(be.rexp);
//                    break;
//                case zyd2001::NewBie::MOD:
//                    temp_variable = evaluate(be.lexp) % evaluate(be.rexp);
//                    break;
//                case zyd2001::NewBie::EQ:
//                    temp_variable = evaluate(be.lexp) == evaluate(be.rexp);
//                    break;
//                case zyd2001::NewBie::NE:
//                    temp_variable = evaluate(be.lexp) != evaluate(be.rexp);
//                    break;
//                case zyd2001::NewBie::GT:
//                    temp_variable = evaluate(be.lexp) > evaluate(be.rexp);
//                    break;
//                case zyd2001::NewBie::GE:
//                    temp_variable = evaluate(be.lexp) >= evaluate(be.rexp);
//                    break;
//                case zyd2001::NewBie::LT:
//                    temp_variable = evaluate(be.lexp) < evaluate(be.rexp);
//                    break;
//                case zyd2001::NewBie::LE:
//                    temp_variable = evaluate(be.lexp) <= evaluate(be.rexp);
//                    break;
//                case zyd2001::NewBie::AND:
//                    temp_variable = evaluate(be.lexp) && evaluate(be.rexp);
//                    break;
//                case zyd2001::NewBie::OR:
//                    temp_variable = evaluate(be.lexp) || evaluate(be.rexp);
//                    break;
//                default:
//                    break;
//            }
//            break;
//        }
//        case zyd2001::NewBie::UNARY_EXPRESSION:
//        {
//            UnaryExpression &ue = e.get<UnaryExpression>();
//            switch (ue.type)
//            {
//                case zyd2001::NewBie::MINUS:
//                    temp_variable = -evaluate(ue.exp);
//                    break;
//                case zyd2001::NewBie::NOT:
//                    temp_variable = !evaluate(ue.exp);
//                    break;
//                default:
//                    break;
//            }
//            break;
//        }
//        case zyd2001::NewBie::FUNCTION_CALL_EXPRESSION:
//        {
//            FunctionCallExpression &fce = e.get<FunctionCallExpression>();
//            Value &f = evaluate(fce.identifier);
//            if (f.type != FUNCTION_TYPE)
//                err();
//            else
//            {
//                Function func = f.get<Function>();
//
//                callFunc(func, fce.alist);
//            }
//            break;
//        }
//        case zyd2001::NewBie::ARRAY_EXPRESSION:
//        {
//            auto &ae = e.get<ArrayExpression>();
//            Value val;
//            val.type = ARRAY_TYPE;
//            val.content = new Array();
//            Array &arr = val.get<Array>();
//            for (auto &i : ae)
//            {
//                arr.emplace_back(evaluate(i));
//            }
//            temp_variable = std::move(val);
//            break;
//        }
//        case ARRAY_LENGTH_EXPRESSION:
//        {
//            auto &ale = e.get<Expression>();
//            Value size = evaluate(ale);
//            Value val;
//            val.type = ARRAY_TYPE;
//            val.content = new Array(size.get<int>());
//            temp_variable = std::move(val);
//            break;
//        }
//        case zyd2001::NewBie::INDEX_EXPRESSION:
//        {
//            auto &ie = e.get<IndexExpression>();
//            return evaluate(ie.exp).get<Array>()[evaluate(ie.index).change_type(INT_TYPE).get<int>()];
//            break;
//        }
//        case THIS_EXPRESSION:
//        {
//            if (in_object)
//                return *current_object;
//            else
//                err("use this outside class");
//            break;
//        }
//        case DOT_EXPRESSION:
//        {
//            auto &de = e.get<DotExpression>();
//            Value obj = evaluate(de.obj);
//            //replace the environment
//            initialize_obj_env(obj);
//            variables_stack.push(make_temp_unit(obj.get<Object>()->local_env));
//            Value &ret = evaluate(de.exp);
//            restore_obj_env();
//            variables_stack.pop();
//            return ret;
//            break;
//        }
//        case NEW_OBJECT_EXPRESSION:
//        {
//            auto &noe = e.get<FunctionCallExpression>(); //just different TYPE
//            auto result = class_map.first.find(noe.identifier.get<IdentifierExpression>());
//            if (result != class_map.first.cend())
//            {
//                temp_variable = Value((ValueType)result->second, new Object(class_map.second[result->second].makeObject(noe.alist)));
//            }
//            //{
//            //    auto &cl = result->second;
//            //    auto obj = new object_t();
//            //    GraphNode *gc_node = new GraphNode(obj);
//            //    Value val(OBJECT_TYPE, new Object(gc_node));
//            //    gc_graph.addVertex(gc_node);
//
//            //    obj->type = noe.identifier.get<IdentifierExpression>();
//            //    obj->cl = &cl;
//
//            //    obj->local_env.push_back(VariablesMap());
//            //    
//            //    initialize_obj_env(val);
//            //    //call ctor
//
//            //    if (cl.base != nullptr)
//            //    {
//            //        
//            //    }
//
//            //    variables_stack.push(make_temp_unit(obj->local_env));
//            //    interpret(cl.slist);
//            //    variables_stack.pop();
//
//            //    callFunc(cl.ctor, noe.alist);
//
//            //    restore_obj_env();
//            //    temp_variable = std::move(val);
//            //}
//            //else
//            //    err("no such class");
//            break;
//        }
//        default:
//            break;
//    }
//    return temp_variable;
//}

template<typename T>
T &getExpression(Expression &e)
{
    return static_cast<T>(e.get());
}

ObjectContainer zyd2001::NewBie::InterpreterImp::Runner::evaluate(Expression &e)
{
    switch (e->type())
    {
        case IDENTIFIER_EXPRESSION:
            return variable_stack.top().back().at(getExpression<IdentifierExpression*>(e)->id);
        case LITERAL_EXPRESSION:
            return getExpression<LiteralExpression*>(e)->obj;
        case BINARY_EXPRESSION:
        {
            auto exp = getExpression<BinaryExpression*>(e);
            switch (exp->ty)
            {
                case ADD:
                    return OContainer(evaluate(exp->lexp)->get()->add(evaluate(exp->rexp)->get()));
                case SUB:
                    return OContainer(evaluate(exp->lexp)->get()->sub(evaluate(exp->rexp)->get()));
                case MUL:
                    return OContainer(evaluate(exp->lexp)->get()->mul(evaluate(exp->rexp)->get()));
                case DIV:
                    return OContainer(evaluate(exp->lexp)->get()->div(evaluate(exp->rexp)->get()));
                case MOD:
                    return OContainer(evaluate(exp->lexp)->get()->mod(evaluate(exp->rexp)->get()));
                case EQ:
                    return OContainer(evaluate(exp->lexp)->get()->eq(evaluate(exp->rexp)->get()));
                case NE:
                    return OContainer(evaluate(exp->lexp)->get()->ne(evaluate(exp->rexp)->get()));
                case GT:
                    return OContainer(evaluate(exp->lexp)->get()->gt(evaluate(exp->rexp)->get()));
                case GE:
                    return OContainer(evaluate(exp->lexp)->get()->ge(evaluate(exp->rexp)->get()));
                case LT:
                    return OContainer(evaluate(exp->lexp)->get()->lt(evaluate(exp->rexp)->get()));
                case LE:
                    return OContainer(evaluate(exp->lexp)->get()->le(evaluate(exp->rexp)->get()));
                case AND:
                    return OContainer(evaluate(exp->lexp)->get()->and(evaluate(exp->rexp)->get()));
                case OR:
                    return OContainer(evaluate(exp->lexp)->get()->or(evaluate(exp->rexp)->get()));
            }
        }
        case UNARY_EXPRESSION:
        {
            auto exp = getExpression<UnaryExpression*>(e);
            switch (exp->ty)
            {
                case NEGATE:
                    return OContainer(evaluate(exp->exp)->get()->negate());
                case NOT:
                    return OContainer(!evaluate(exp->exp)->get()->toBool());
            }
        }
        case FUNCTION_CALL_EXPRESSION:
        {
            auto exp = getExpression<FunctionCallExpression*>(e);
            auto func = evaluate(exp->func);
            return OContainer(func->get()->call(exp->alist));
        }
    }
}

Object zyd2001::NewBie::IdentifierExpression::evaluate()
{
    return inter->getVariable(id);
}

Object zyd2001::NewBie::LiteralExpression::evaluate()
{
    return obj;
}

//Object zyd2001::NewBie::ArrayExpression::evaluate()
//{
//    return Object();
//}

Object zyd2001::NewBie::BinaryExpression::evaluate()
{
    switch (type)
    {
        case zyd2001::NewBie::ADD:
            return lexp->evaluate() + rexp->evaluate();
            break;
        case zyd2001::NewBie::SUB:
            return lexp->evaluate() - rexp->evaluate();
            break;
        case zyd2001::NewBie::MUL:
            return lexp->evaluate() * rexp->evaluate();
            break;
        case zyd2001::NewBie::DIV:
            return lexp->evaluate() / rexp->evaluate();
            break;
        case zyd2001::NewBie::MOD:
            return lexp->evaluate() % rexp->evaluate();
            break;
        case zyd2001::NewBie::EQ:
            return lexp->evaluate() == rexp->evaluate();
            break;
        case zyd2001::NewBie::NE:
            return lexp->evaluate() != rexp->evaluate();
            break;
        case zyd2001::NewBie::GT:
            return lexp->evaluate() > rexp->evaluate();
            break;
        case zyd2001::NewBie::GE:
            return lexp->evaluate() >= rexp->evaluate();
            break;
        case zyd2001::NewBie::LT:
            return lexp->evaluate() < rexp->evaluate();
            break;
        case zyd2001::NewBie::LE:
            return lexp->evaluate() <= rexp->evaluate();
            break;
        case zyd2001::NewBie::AND:
            return lexp->evaluate() && rexp->evaluate();
            break;
        case zyd2001::NewBie::OR:
            return lexp->evaluate() || rexp->evaluate();
            break;
        default:
            break;
    }
}

Object zyd2001::NewBie::UnaryExpression::evaluate()
{
    switch (type)
    {
        case zyd2001::NewBie::NEGATE:
            return -exp->evaluate();
            break;
        case zyd2001::NewBie::NOT:
            return !exp->evaluate();
            break;
        default:
            break;
    }
}

Object zyd2001::NewBie::FunctionCallExpression::evaluate()
{
    auto f = func->evaluate();
    f.obj->cl->op[8]->call(alist);
}

Object zyd2001::NewBie::NewObjectExpression::evaluate()
{
    auto cl = inter->findClass(id);
    return Object(cl->makeObject(alist));
}

//Object zyd2001::NewBie::IndexExpression::evaluate()
//{
//    return Object();
//}

Object zyd2001::NewBie::DotExpression::evaluate()
{
    return obj->evaluate().getVariable(id);
}

Object zyd2001::NewBie::ThisExpression::evaluate()
{
    return inter->current_object;
}