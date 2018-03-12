#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

#if defined(_MSC_VER)
#include <Windows.h>
#endif

using namespace zyd2001::NewBie;
using namespace std;

//bool InterpreterImp::run()
//{
//#if defined(_MSC_VER)
//    auto cp = GetConsoleOutputCP();
//    SetConsoleOutputCP(CP_UTF8);
//#endif
//    if (statement_list.empty())
//    {
//        throw runtime_error("No AST");
//    }
//    gc_graph.addVertex(root);
//    variables_stack.push(make_stack_unit());
//    (*variables_stack.top()).emplace_back(VariableMap());
//    interpret(statement_list);
//    variables_stack.pop();
//#if defined(_MSC_VER)
//    SetConsoleOutputCP(cp);
//#endif
//    return true;
//}

//StatementType InterpreterImp::interpret(const StatementList &s)
//{
//    StatementType res;
//    auto end = s.cend();
//    for (auto iter = s.cbegin(); iter != s.cend(); iter++)
//    {
//        res = execute(*iter);
//
//        /* if reach return, break or continue, jump out of the call stack */
//        if (res == BREAK_STATEMENT || res == CONTINUE_STATEMENT || res == RETURN_STATEMENT)
//            return res;
//    }
//    return NULL_STATEMENT;
//}
//
//int InterpreterImp::checkExist(const Identifier &id) //check all scope, 0 for global
//{
//    //vector<VariableMap> &v = (*variables_stack.top());
//    //for (auto i = v.size(); i > 0; i--)
//    //{
//    //    auto result = v[i - 1].find(id);
//    //    if (result != v[i - 1].cend())
//    //        return i;
//    //    else
//    //        continue;
//    //}
//
//    //auto result = global_variables.find(id);
//    //if (result != global_variables.cend())
//    //    return 0;
//    //else
//    //    return -1;
//}
//
//void InterpreterImp::err() { cerr << "Error occured at " << current_lineno << endl; }
//void InterpreterImp::err(const string &s) { cerr << "Error occured at " << current_lineno << endl; cerr << s << endl; }
//StatementType InterpreterImp::execute(const Statement &s)
//{
//    current_lineno = s.lineno;
//    auto &v = (*variables_stack.top());
//    switch (s.type)
//    {
//        case zyd2001::NewBie::EXPRESSION_STATEMENT:
//            evaluate(s.get<Expression>());
//            break;
//        case zyd2001::NewBie::ASSIGNMENT_STATEMENT:
//        {
//            AssignmentStatement &as = s.get<AssignmentStatement>();
//            //Value &lval = evaluate(as.lvalue);
//            //Value &rval = evaluate(as.rvalue);
//            //if (lval.type == OBJECT_TYPE)
//            //{
//            //    if (in_object)
//            //        gc_graph.delEdge((*current_object).get<Object>().node, rval.get<Object>().node);
//            //    else
//            //        gc_graph.delEdge(root, rval.get<Object>().node);
//            //}
//            //if (rval.type == OBJECT_TYPE)
//            //{
//            //    if (in_object)
//            //        gc_graph.addEdge((*current_object).get<Object>().node, rval.get<Object>().node);
//            //    else
//            //        gc_graph.addEdge(root, rval.get<Object>().node);
//            //}
//            //break;
//        }
//        case zyd2001::NewBie::DECLARATION_STATEMENT:
//        {
//            DeclarationStatement &ds = s.get<DeclarationStatement>();
//            for (auto &iter : ds.items)
//            {
//                int res = checkExist(iter.identifier);
//                if (res == -1)
//                {
//                    VariableMap *vmap;
//                    if (ds.global)
//                        vmap = &global_variables;
//                    else
//                        vmap = &v.back();
//                    if (ds.type != OBJECT_TYPE)
//                    {
//                        if (iter.initial_value.type != NULL_EXPRESSION)
//                            (*vmap)[iter.identifier] = evaluate(iter.initial_value);
//                        else
//                            (*vmap)[iter.identifier] = Value(ds.type);
//                    }
//                    else
//                    {
//                        if (iter.initial_value.type != NULL_EXPRESSION)
//                            (*vmap)[iter.identifier] = evaluate(iter.initial_value);
//                        else
//                            (*vmap)[iter.identifier] = newObject(ds.obj_type);
//                    }
//                }
//                else
//                {
//                    err();
//                }
//            }
//            break;
//        }
//        case FUNCTION_DEFINITION_STATEMENT:
//        {
//            if (in_object)
//            {
//                // get the function in a class
//                auto &obj = current_object->get<Object>();
//                auto &func = s.get<VariableMap::value_type>();
//                obj->local_env.back()[func.first] = func.second;
//            }
//            break;
//        }
//        case zyd2001::NewBie::BLOCK_STATEMENT:
//        {
//            //new scope
//            v.emplace_back(VariableMap());
//            StatementType res = interpret(s.get<BlockStatement>());
//            v.pop_back();
//
//            /* if reach return, break or continue, jump out of the call stack */
//            if (res == BREAK_STATEMENT || res == CONTINUE_STATEMENT || res == RETURN_STATEMENT)
//                return res;
//            break;
//        }
//        case zyd2001::NewBie::IF_STATEMENT:
//        {
//            IfStatement &ifs = s.get<IfStatement>();
//            if (evaluate(ifs.condition).change_type(BOOL_TYPE).get<bool>())
//            {
//                StatementType res;
//                //new scope
//                v.emplace_back(VariableMap());
//                if (ifs.stat.type == BLOCK_STATEMENT)
//                    res = interpret(ifs.stat.get<BlockStatement>());
//                else                
//                    res = execute(ifs.stat);
//                v.pop_back();
//
//                /* if reach return, break or continue, jump out of the call stack */
//                if (res == BREAK_STATEMENT || res == CONTINUE_STATEMENT || res == RETURN_STATEMENT)
//                    return res;
//            }
//            else
//            {
//                bool flag = true;
//                if (!ifs.elseif.empty()) //determine else if statement
//                {
//                    for (auto &i : ifs.elseif)
//                    {
//                        if (evaluate(i.condition).change_type(BOOL_TYPE).get<bool>())
//                        {
//                            StatementType res;
//                            //new scope
//                            v.emplace_back(VariableMap());
//                            if (i.stat.type == BLOCK_STATEMENT)
//                                res = interpret(ifs.stat.get<BlockStatement>());
//                            else
//                                res = execute(i.stat);
//                            v.pop_back();
//
//                            /* if reach return, break or continue, jump out of the call stack */
//                            if (res == BREAK_STATEMENT || res == CONTINUE_STATEMENT || res == RETURN_STATEMENT)
//                                return res;
//
//                            flag = false; //do not process else statement
//                            break;
//                        }
//                    }
//                }
//                if (ifs.else_stat.type != NULL_STATEMENT && flag)
//                {
//                    StatementType res;
//                    //new scope
//                    v.emplace_back(VariableMap());
//                    if (ifs.else_stat.type == BLOCK_STATEMENT)
//                        res = interpret(ifs.else_stat.get<BlockStatement>());
//                    else
//                        res = execute(ifs.else_stat);
//                    v.pop_back();
//
//                    /* if reach return, break or continue, jump out of the call stack */
//                    if (res == BREAK_STATEMENT || res == CONTINUE_STATEMENT || res == RETURN_STATEMENT)
//                        return res;
//                }
//            }
//            break;
//        }
//        case zyd2001::NewBie::FOR_STATEMENT:
//        {
//            ForStatement &fs = s.get<ForStatement>();
//            //new scope
//            v.emplace_back(VariableMap());
//            for (execute(fs.pre); evaluate(fs.condition).change_type(BOOL_TYPE).get<bool>(); execute(fs.after))
//            {
//                StatementType res;
//                if (fs.stat.type == BLOCK_STATEMENT)
//                    res = interpret(fs.stat.get<BlockStatement>());
//                else
//                    res = execute(fs.stat);
//
//                if (res == RETURN_STATEMENT)
//                {
//                    v.pop_back();
//                    return res;
//                }
//                /* handle break and continue */
//                else if (res == CONTINUE_STATEMENT)
//                    continue;
//                else if (res == BREAK_STATEMENT)
//                    break;
//            }
//            v.pop_back();
//            break;
//        }
//        case zyd2001::NewBie::FOREACH_STATEMENT:
//        {
//            ForeachStatement &fes = s.get<ForeachStatement>();
//            DeclarationStatement *ds = new (DeclarationStatement){ false, VARIANT_TYPE, { { fes.identifier, Expression() } } };
//            Statement stat(DECLARATION_STATEMENT, ds, -1);
//
//            //new scope
//            v.emplace_back(VariableMap());
//            execute(stat);
//            auto &var = v.back().at(fes.identifier);
//            Value a = evaluate(fes.exp);
//            Array &arr = a.get<Array>();
//
//            StatementType res;
//            if (fes.reverse)
//            {
//                for (auto iter = arr.crbegin(); iter != arr.crend(); iter++)
//                {
//                    var = *iter;
//                    if (fes.stat.type == BLOCK_STATEMENT)
//                        res = interpret(fes.stat.get<BlockStatement>());
//                    else
//                        res = execute(fes.stat);
//
//                    if (res == RETURN_STATEMENT)
//                    {
//                        v.pop_back();
//                        return res;
//                    }
//                    /* handle break and continue */
//                    else if (res == CONTINUE_STATEMENT)
//                        continue;
//                    else if (res == BREAK_STATEMENT)
//                        break;
//                }
//            }
//            else
//            {
//                for (auto iter = arr.cbegin(); iter != arr.cend(); iter++)
//                {
//                    var = *iter;
//                    if (fes.stat.type == BLOCK_STATEMENT)
//                        res = interpret(fes.stat.get<BlockStatement>());
//                    else
//                        res = execute(fes.stat);
//
//                    if (res == RETURN_STATEMENT)
//                    {
//                        v.pop_back();
//                        return res;
//                    }
//                    /* handle break and continue */
//                    else if (res == CONTINUE_STATEMENT)
//                        continue;
//                    else if (res == BREAK_STATEMENT)
//                        break;
//                }
//            }
//            v.pop_back();
//            break;
//        }
//        case zyd2001::NewBie::RETURN_STATEMENT:
//        {
//            //return result by a global variable
//            temp_variable = evaluate(s.get<ReturnStatement>());
//            break;
//        }
//        case zyd2001::NewBie::CONTINUE_STATEMENT:
//            break;
//        case zyd2001::NewBie::BREAK_STATEMENT:
//            break;
//        case DEBUG_STATEMENT:
//        {
//            Value val = evaluate(s.get<DebugStatement>());
//            cout << val << endl;
//            break;
//        }
//        default:
//            break;
//    }
//    return s.type;
//}

std::tuple<StatementType, Object> zyd2001::NewBie::ExpressionStatement::execute()
{
    return make_tuple(EXPRESSION_STATEMENT, exp->evaluate());
}

void zyd2001::NewBie::StatementList::swap(StatementList &s)
{
    s.list.swap(list);
}

tuple<StatementType, Object> zyd2001::NewBie::StatementList::interpret()
{
    for (auto &s : list)
    {
        auto result = s->execute();
        switch (get<StatementType>(result))
        {
            case RETURN_STATEMENT:
            case BREAK_STATEMENT:
            case CONTINUE_STATEMENT:
                return result;
                break;
            default:
                break;
        }
    }
}

std::tuple<StatementType, Object> zyd2001::NewBie::DeclarationStatement::execute()
{
    auto type = inter->findClassId(obj_type);
    for (auto &i : items)
    {
        if (i.initial_value.get() == nullptr)
            inter->declareVariable(i.identifier, type, i.initial_value->evaluate(), global);
        else
            inter->declareVariable(i.identifier, type, global);
    }
    return make_tuple(DECLARATION_STATEMENT, Object());
}

std::tuple<StatementType, Object> zyd2001::NewBie::BuiltInDeclarationStatement::execute()
{
    for (auto &i : items)
    {
        if (i.initial_value.get() == nullptr)
            inter->declareVariable(i.identifier, type, i.initial_value->evaluate(), global);
        else
            inter->declareVariable(i.identifier, type, global);
    }
    return make_tuple(DECLARATION_STATEMENT, Object());
}

std::tuple<StatementType, Object> zyd2001::NewBie::AssignmentStatement::execute()
{
    inter->changeVariable(id, rvalue->evaluate());
    return make_tuple(ASSIGNMENT_STATEMENT, Object());
}

std::tuple<StatementType, Object> zyd2001::NewBie::ObjectAssignmentStatement::execute()
{
    lvalue->obj->evaluate().changeVariable(lvalue->id, rvalue->evaluate());
    return make_tuple(ASSIGNMENT_STATEMENT, Object());
}

std::tuple<StatementType, Object> zyd2001::NewBie::IfStatement::execute()
{
    if (condition->evaluate())
    {
        newVariablesScope();
        return stat->execute();
    }
    else
    {
        if (elseif.size() > 0)
        {
            for (auto &i : elseif)
                if (i.condition->evaluate())
                {
                    newVariablesScope();
                    return i.stat->execute();
                }
        }
        if (else_stat.get() != nullptr)
        {
            newVariablesScope();
            return else_stat->execute();
        }
    }
    return make_tuple(IF_STATEMENT, Object());
}

std::tuple<StatementType, Object> ForStatement::execute()
{
    newVariablesScope();
    for (pre->execute(); condition->evaluate(); after->execute())
    {
        auto result = stat->execute();
        auto t = get<StatementType>(result);
        if (t == CONTINUE_STATEMENT)
            continue;
        else if (t == BREAK_STATEMENT)
            return make_tuple(FOR_STATEMENT, Object());
        else if (t == RETURN_STATEMENT)
            return result;
    }
    return make_tuple(FOR_STATEMENT, Object());
}

std::tuple<StatementType, Object> zyd2001::NewBie::WhileStatement::execute()
{
    newVariablesScope();
    while (condition->evaluate())
    {
        auto result = stat->execute();
        auto t = get<StatementType>(result);
        if (t == CONTINUE_STATEMENT)
            continue;
        else if (t == BREAK_STATEMENT)
            return make_tuple(FOR_STATEMENT, Object());
        else if (t == RETURN_STATEMENT)
            return result;
    }
    return make_tuple(WHILE_STATEMENT, Object());
}

std::tuple<StatementType, Object> zyd2001::NewBie::BlockStatement::execute()
{
    return slist.interpret();
}

std::tuple<StatementType, Object> zyd2001::NewBie::ReturnStatement::execute()
{
    return make_tuple(RETURN_STATEMENT, exp->evaluate());
}