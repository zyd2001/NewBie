#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

#if defined(_MSC_VER)
#include <Windows.h>
#endif

using namespace zyd2001::NewBie;
using namespace std;

bool InterpreterImp::run()
{
#if defined(_MSC_VER)
    auto cp = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);
#endif
    if (statements_list.empty())
    {
        throw runtime_error("No AST");
    }
    variables_stack.push(vector<VariablesMap>());
    variables_stack.top().emplace_back(VariablesMap());
    if (false) //according to the setting
        variables_stack.top().emplace_back(VariablesMap());
    interpret(statements_list);
    variables_stack.pop();
#if defined(_MSC_VER)
    SetConsoleOutputCP(cp);
#endif
    return true;
}

StatementType InterpreterImp::interpret(const StatementsList &s)
{
    StatementType res;
    auto end = s.cend();
    for (auto iter = s.cbegin(); iter != s.cend(); iter++)
    {
        res = execute(*iter);

        /* if reach return, break or continue, jump out of the call stack */
        if (res == BREAK_STATEMENT || res == CONTINUE_STATEMENT || res == RETURN_STATEMENT)
            return res;
    }
    return NULL_STATEMENT;
}

int InterpreterImp::checkExist(const Identifier &id) //check all scope, 0 for global
{
    vector<VariablesMap> &v = variables_stack.top();
    for (auto i = v.size(); i > 0; i--)
    {
        auto result = v[i - 1].find(id);
        if (result != v[i - 1].cend())
            return i;
        else
            continue;
    }
    //when in function
    auto result = global_variables.find(id);
    if (result != global_variables.cend())
    	return 0;
    else
        return -1;
}

void InterpreterImp::err() { cerr << "Error occured at " << current_lineno << endl; }
StatementType InterpreterImp::execute(const Statement &s)
{
    current_lineno = s.lineno;
    auto &v = variables_stack.top();
    switch (s.type)
    {
        case zyd2001::NewBie::EXPRESSION_STATEMENT:
            evaluate(s.get<Expression>());
            break;
        case zyd2001::NewBie::ASSIGNMENT_STATEMENT:
        {
            AssignmentStatement &as = s.get<AssignmentStatement>();
            int res = checkExist(as.identifier);
            if (res == -1)
            {
                err();
            }
            else
            {
                Value *target;
                if (res == 0)
                    target = &global_variables.at(as.identifier);
                else
                    target = &v[res - 1].at(as.identifier);
                Value &&val = evaluate(as.value);
                if (!target->various && target->type != val.type)
                {
                    //if the variable isn't various type and the value's type assigned isn't match, error
                    err();
                }
                else 
                {
                    if (target->various)
                        val.various = true;
                    *target = val;
                }
            }
            break;
        }
        case zyd2001::NewBie::DECLARATION_STATEMENT:
        {
            DeclarationStatement &ds = s.get<DeclarationStatement>();
            for (auto &iter : ds.items)
            {
                int res = checkExist(iter.identifier);
                if (res == -1)
                {
                    VariablesMap *vmap;
                    if (ds.global)
                        vmap = &global_variables;
                    else
                        vmap = &v.back();
                    if (iter.initial_value.type != NULL_EXPRESSION)
                        (*vmap)[iter.identifier] = evaluate(iter.initial_value).change_type(ds.type);
                    else
                        (*vmap)[iter.identifier] = Value(ds.type);
                }
                else
                {
                    err();
                }
            }
            break;
        }
        case zyd2001::NewBie::BLOCK_STATEMENT:
        {
            //new scope
            v.emplace_back(VariablesMap());
            StatementType res = interpret(s.get<BlockStatement>());
            v.pop_back();

            /* if reach return, break or continue, jump out of the call stack */
            if (res == BREAK_STATEMENT || res == CONTINUE_STATEMENT || res == RETURN_STATEMENT)
                return res;
            break;
        }
        case zyd2001::NewBie::IF_STATEMENT:
        {
            IfStatement &ifs = s.get<IfStatement>();
            if (evaluate(ifs.condition).change_type(BOOL_TYPE).get<bool>())
            {
                StatementType res;
                //new scope
                v.emplace_back(VariablesMap());
                if (ifs.stat.type == BLOCK_STATEMENT)
                    res = interpret(ifs.stat.get<BlockStatement>());
                else                
                    res = execute(ifs.stat);
                v.pop_back();

                /* if reach return, break or continue, jump out of the call stack */
                if (res == BREAK_STATEMENT || res == CONTINUE_STATEMENT || res == RETURN_STATEMENT)
                    return res;
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
                            StatementType res;
                            //new scope
                            v.emplace_back(VariablesMap());
                            if (i.stat.type == BLOCK_STATEMENT)
                                res = interpret(ifs.stat.get<BlockStatement>());
                            else
                                res = execute(i.stat);
                            v.pop_back();

                            /* if reach return, break or continue, jump out of the call stack */
                            if (res == BREAK_STATEMENT || res == CONTINUE_STATEMENT || res == RETURN_STATEMENT)
                                return res;

                            flag = false; //do not process else statement
                            break;
                        }
                    }
                }
                if (ifs.else_stat.type != NULL_STATEMENT && flag)
                {
                    StatementType res;
                    //new scope
                    v.emplace_back(VariablesMap());
                    if (ifs.else_stat.type == BLOCK_STATEMENT)
                        res = interpret(ifs.else_stat.get<BlockStatement>());
                    else
                        res = execute(ifs.else_stat);
                    v.pop_back();

                    /* if reach return, break or continue, jump out of the call stack */
                    if (res == BREAK_STATEMENT || res == CONTINUE_STATEMENT || res == RETURN_STATEMENT)
                        return res;
                }
            }
            break;
        }
        case zyd2001::NewBie::FOR_STATEMENT:
        {
            ForStatement &fs = s.get<ForStatement>();
            //new scope
            v.emplace_back(VariablesMap());
            for (execute(fs.pre); evaluate(fs.condition).change_type(BOOL_TYPE).get<bool>(); execute(fs.after))
            {
                StatementType res;
                if (fs.stat.type == BLOCK_STATEMENT)
                    res = interpret(fs.stat.get<BlockStatement>());
                else
                    res = execute(fs.stat);

                if (res == RETURN_STATEMENT)
                {
                    v.pop_back();
                    return res;
                }
                /* handle break and continue */
                else if (res == CONTINUE_STATEMENT)
                    continue;
                else if (res == BREAK_STATEMENT)
                    break;
            }
            v.pop_back();
            break;
        }
        case zyd2001::NewBie::FOREACH_STATEMENT:
        {
            break;
        }
        case zyd2001::NewBie::RETURN_STATEMENT:
        {
            //return result by a global variable
            temp_variable = evaluate(s.get<ReturnStatement>());
            break;
        }
        case zyd2001::NewBie::CONTINUE_STATEMENT:
            break;
        case zyd2001::NewBie::BREAK_STATEMENT:
            break;
        case DEBUG_STATEMENT:
        {
            Value val = evaluate(s.get<DebugStatement>());
            cout << val << endl;
            break;
        }
        default:
            break;
    }
    return s.type;
}