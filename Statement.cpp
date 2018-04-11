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

template<typename T>
T &getStatement(Statement &s)
{
    return static_cast<T>(s.get());
}

StatementType zyd2001::NewBie::Runner::execute(Statement &s)
{
    switch (s->type())
    {
        case EXPRESSION_STATEMENT:
        {
            evaluate(getStatement<ExpressionStatement*>(s)->exp);
            return EXPRESSION_STATEMENT;
            break;
        }
        case DECLARATION_STATEMENT:
        {
            auto decl = getStatement<DeclarationStatement*>(s);
            ObjectType type = inter->findClassId(decl->obj_type);
            for (auto &item : decl->items)
            {
                if (item.initial_value.get() != nullptr)
                    inter->declareVariable(item.identifier, type, evaluate(item.initial_value), decl->global);
                else
                    inter->declareVariable(item.identifier, type, decl->global);
            }
            return DECLARATION_STATEMENT;
            break;
        }
        case BUILTIN_DECLARATION_STATEMENT:
        {
            auto decl = getStatement<BuiltInDeclarationStatement*>(s);
            for (auto &item : decl->items)
            {
                if (item.initial_value.get() != nullptr)
                    inter->declareVariable(item.identifier, decl->type, evaluate(item.initial_value), decl->global);
                else
                    inter->declareVariable(item.identifier, decl->type, decl->global);
            }
            return BUILTIN_DECLARATION_STATEMENT;
            break;
        }
        case ASSIGNMENT_STATEMENT:
        {
            auto assign = getStatement<AssignmentStatement*>(s);
            evaluate(assign->lvalue)->set(evaluate(assign->rvalue));
            return ASSIGNMENT_STATEMENT;
            break;
        }
        case IF_STATEMENT:
        {
            auto ifs = getStatement<IfStatement*>(s);
            if (B(evaluate(ifs->condition)))
            {
                newVariablesScope();
                return execute(ifs->stat);
            }
            else
            {
                if (ifs->elseif.size() > 0)
                {
                    for (auto &i : ifs->elseif)
                        if (B(evaluate(i.condition)))
                        {
                            newVariablesScope();
                            return execute(i.stat);
                        }
                }
                if (ifs->else_stat.get() != nullptr)
                {
                    newVariablesScope();
                    return execute(ifs->else_stat);
                }
            }
            return IF_STATEMENT;
            break;
        }
        case FOR_STATEMENT:
        {
            auto fors = getStatement<ForStatement*>(s);
            newVariablesScope();
            for (execute(fors->pre); B(evaluate(fors->condition)); execute(fors->after))
            {
                auto result = execute(fors->stat);
                if (result == CONTINUE_STATEMENT)
                    continue;
                else if (result == BREAK_STATEMENT)
                    return result;
                else if (result == RETURN_STATEMENT)
                    return result;
                else
                    return FOR_STATEMENT;
            }
            break;
        }
        case WHILE_STATEMENT:
        {
            auto whiles = getStatement<WhileStatement*>(s);
            newVariablesScope();
            if (whiles->do_while)
                do
                {
                    auto result = execute(whiles->stat);
                    if (result == CONTINUE_STATEMENT)
                        continue;
                    else if (result == BREAK_STATEMENT)
                        return result;
                    else if (result == RETURN_STATEMENT)
                        return result;
                    else
                        return WHILE_STATEMENT;
                } while (B(evaluate(whiles->condition)));
            else
                while (B(evaluate(whiles->condition)))
                {
                    auto result = execute(whiles->stat);
                    if (result == CONTINUE_STATEMENT)
                        continue;
                    else if (result == BREAK_STATEMENT)
                        return result;
                    else if (result == RETURN_STATEMENT)
                        return result;
                    else
                        return WHILE_STATEMENT;
                }
            break;
        }
        case RETURN_STATEMENT:
        {
            temp_obj->set(evaluate(getStatement<ReturnStatement*>(s)->exp)->get());
            return RETURN_STATEMENT;
            break;
        }
        case CONTINUE_STATEMENT:
            return CONTINUE_STATEMENT;
            break;
        case BREAK_STATEMENT:
            return BREAK_STATEMENT;
            break;
    }
}