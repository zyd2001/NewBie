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
T &getExpression(const Expression &e)
{
    return static_cast<T>(e.get());
}

ObjectContainer zyd2001::NewBie::Runner::evaluate(const Expression &e)
{
    Runner & runner = *this;
    switch (e->type())
    {
        case IDENTIFIER_EXPRESSION:
            return getVariable(getExpression<IdentifierExpression*>(e)->id);
        case LITERAL_EXPRESSION:
            return getExpression<LiteralExpression*>(e)->obj;
        case BINARY_EXPRESSION:
        {
            auto exp = getExpression<BinaryExpression*>(e);
            switch (exp->ty)
            {
                case ADD:
                    return evaluate(exp->lexp).add(*this, evaluate(exp->rexp));
                case SUB:  
                    return evaluate(exp->lexp).sub(*this, evaluate(exp->rexp));
                case MUL:
                    return evaluate(exp->lexp).mul(*this, evaluate(exp->rexp));
                case DIV:
                    return evaluate(exp->lexp).div(*this, evaluate(exp->rexp));
                case MOD:  
                    return evaluate(exp->lexp).mod(*this, evaluate(exp->rexp));
                case LT:
                    return evaluate(exp->lexp).lt(*this, evaluate(exp->rexp));
                case LE:
                    return evaluate(exp->lexp).lt(*this, evaluate(exp->rexp));
                case GT:
                    return evaluate(exp->lexp).gt(*this, evaluate(exp->rexp));
                case GE:
                    return evaluate(exp->lexp).ge(*this, evaluate(exp->rexp));
                case EQ:
                    return evaluate(exp->lexp).eq(*this, evaluate(exp->rexp));
                case NE:
                    return evaluate(exp->lexp).ne(*this, evaluate(exp->rexp));
                case AND:
                    return evaluate(exp->lexp).and(*this, evaluate(exp->rexp));
                case OR:
                    return evaluate(exp->lexp).or(*this, evaluate(exp->rexp));
                case BIT_AND:
                    return evaluate(exp->lexp).bit_and(*this, evaluate(exp->rexp));
                case BIT_OR:
                    return evaluate(exp->lexp).bit_or(*this, evaluate(exp->rexp));
                case BIT_XOR:
                    return evaluate(exp->lexp).bit_xor(*this, evaluate(exp->rexp));
                case BIT_LEFT:
                    return evaluate(exp->lexp).bit_left(*this, evaluate(exp->rexp));
                case BIT_RIGHT:
                    return evaluate(exp->lexp).bit_right(*this, evaluate(exp->rexp));
                default:
                    throw exception();
            }
        }
        case UNARY_EXPRESSION:
        {
            auto exp = getExpression<UnaryExpression*>(e);
            switch (exp->ty)
            {
                case MINUS:
                    return evaluate(exp->exp).minus(*this);
                case PLUS:
                    return evaluate(exp->exp).plus(*this);
                case BIT_NOT:
                    return evaluate(exp->exp).not(*this);
                case NEGATION:
                    return evaluate(exp->exp).negate(*this);
                default:
                    throw exception();
            }
        }
        case NEW_OBJECT_EXPRESSION:
        {
            auto exp = getExpression<NewObjectExpression*>(e);
            auto func = getGlobalVariable(exp->id);
            return func.call(*this, exp->alist);
        }
        case FUNCTION_CALL_EXPRESSION:
        {
            auto exp = getExpression<FunctionCallExpression*>(e);
            auto func = getVariable(exp->func);
            return func.call(*this, exp->alist);
        }
        case THIS_EXPRESSION:
        {
            if (call_stack_func.empty())
                throw exception();
            return call_stack_func.top().second;
        }
        case BASE_EXPRESSION:
        {
            auto exp = getExpression<BaseExpression*>(e);
            if (call_stack_func.empty())
                throw exception();
            ObjectContainer this_obj = call_stack_func.top().second;
            if (exp->t == 0)
                return this_obj->obj->getSuperVariable(runner, exp->id);
            else
                return this_obj->obj->getSuperVariable(runner, exp->t, exp->id);
        }
        case DOT_EXPRESSION:
        {
            auto exp = getExpression<DotExpression*>(e);
            switch (exp->exp->type())
            {
                case FUNCTION_CALL_EXPRESSION:
                {
                    auto f = getExpression<FunctionCallExpression*>(exp->exp);
                    auto obj = evaluate(exp->obj);
                    return obj.call(*this, f->func, f->alist);
                    break;
                }
                case IDENTIFIER_EXPRESSION:
                    return evaluate(exp->obj).getVariable(*this, getExpression<IdentifierExpression*>(exp->exp)->id);
                    break;
                default:
                    throw exception();
            }
        }
    }
}