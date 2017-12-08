#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

bool InterpreterImp::run()
{
    if (statements_list.empty())
    {
        throw runtime_error("No AST");
    }

    //set the global variables map to the lowest level of variables map
    global_variables = &variables_stack.top().back();
    if (false) //according to the setting
        variables_stack.top().push_back(VariablesMap());
    interpret(statements_list, false, false);
    variables_stack.pop();
    return true;
}

int InterpreterImp::interpret(const StatementsList &s, bool isFunc, bool isLoop)
{
    StatementType result;
    auto end = s.cend();
    if (isFunc && isLoop)
        for (auto iter = s.cbegin(); iter != s.cend(); iter++)
        {
            auto res = execute(*iter, isFunc, isLoop);
            if (res == RETURN_STATEMENT)
                break;
            else if (res == BREAK_STATEMENT)
                break;
            else if (res == CONTINUE_STATEMENT)
                iter = s.cbegin(); //return to the beginning of the for-loop
        }
    else if (isFunc)
        for (auto &iter : s)
        {
            auto res = execute(iter, isFunc, isLoop);
            if (res == RETURN_STATEMENT)
                break;
        }
    else if (isLoop)
        for (auto iter = s.cbegin(); iter != s.cend(); iter++)
        {
            auto res = execute(*iter, isFunc, isLoop);
            if (res == BREAK_STATEMENT)
                break;
            else if (res == CONTINUE_STATEMENT)
                iter = s.cbegin(); //return to the beginning of the for-loop
        }
    else
        for (auto &iter : s)
        {
            execute(iter, isFunc, isLoop);
        }
    return 1;
}

int InterpreterImp::checkExist(const Identifier &id) //check all scope
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
    auto result = global_variables->find(id);
    if (result != global_variables->cend())
    	return 0;
    else
    return -1;
}

void InterpreterImp::err() { cerr << "Error occured at " << current_lineno << endl; }
StatementType InterpreterImp::execute(const Statement &s, bool isFunc, bool isLoop)
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
                Value &&val = evaluate(as.value);
                Value &target = v[res - 1].at(as.identifier);
                if (!target.various && target.type != val.type)
                {
                    //if the variable isn't various type and the value's type assigned isn't match, error
                    err();
                }
                else
                {
                    target = val;
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
                        vmap = global_variables;
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
            v.push_back(VariablesMap());
            interpret(s.get<BlockStatement>(), isFunc, isLoop);
            v.pop_back();
            break;
        case zyd2001::NewBie::IF_STATEMENT:
        {
            IfStatement &ifs = s.get<IfStatement>();
            if (evaluate(ifs.condition).change_type(BOOL_TYPE).get<bool>())
            {
                execute(ifs.stat, isFunc, isLoop);
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
                            execute(i.stat, isFunc, isLoop);
                            flag = false;
                            break;
                        }
                    }
                }
                if (ifs.else_stat.type != NULL_STATEMENT && flag);
                {
                    execute(ifs.else_stat, isFunc, isLoop);
                }
            }
            break;
        }
        case zyd2001::NewBie::FOR_STATEMENT:
        {
            ForStatement &fs = s.get<ForStatement>();
            for (evaluate(fs.exp1); evaluate(fs.exp2).change_type(BOOL_TYPE).get<bool>(); evaluate(fs.exp3))
                execute(fs.stat, isFunc, true);
            break;
        }
        case zyd2001::NewBie::FOREACH_STATEMENT:
            break;
        case zyd2001::NewBie::RETURN_STATEMENT:
        {
            temp_variable = evaluate(s.get<ReturnStatement>());
            break;
        }
        case zyd2001::NewBie::CONTINUE_STATEMENT:
            break;
        case zyd2001::NewBie::BREAK_STATEMENT:
            break;
        case DEBUG_STATEMENT:
        {
            Identifier &id = s.get<Identifier>();
            int res = checkExist(id);
            if (res == -1)
            {
                err();
            }
            else
            {
                cout << variables_stack.top()[res - 1].at(id) << endl;
            }
        }
        default:
            break;
    }
    return s.type;
}