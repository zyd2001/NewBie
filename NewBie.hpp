#ifndef NEWBIE_HPP
#define NEWBIE_HPP
#include <vector>
#include <string>

namespace zyd2001::NewBie
{
    enum BinaryType
    {
        ADD,
        SUB,
        MUL,
        DIV,
        MOD,
        EQ,
        NE,
        GT,
        GE,
        LT,
        LE,
        AND,
        OR
    };

    enum UnaryType
    {
        MINUS,
        NOT,
        INCREMENT,
        DECREMENT
    };

    enum ValueType
    {
        INT,
        DOUBLE,
        BOOL,
        STRING,
        ARRAY,
        OBJECT
    };
    
    struct Value 
    {
        ValueType type;
        union
        {
            int int_value;
            double double_value;
            bool bool_value;
            u32string string_value;
            std::unordered_map<string, Value> array_value;
        } value;
        Value() = default;
        ~Value() = default;
    };

    enum StatementType
    {
        NULL_RESULT,
        EXPRESSION_STATEMENT,
        FUNCTION_DEFINITION_STATEMENT,
        CLASS_DEFINITION_STATEMENT,
        BLOCK_STATEMENT,
        IF_STATEMENT,
        ELSE_STATEMENT,
        FOR_STATEMENT,
        FOREACH_STATEMENT,
        RETURN_STATEMENT,
        CONTINUE_STATEMENT,
        BREAK_STATEMENT
    };
    
    struct Statement
    {
        StatementType type;
    };

    struct Expression
    {

    };

    class InterpreterImp
    {
    public:
        InterpreterImp();
        InterpreterImp(const std::string &name);
        ~InterpreterImp();
        bool interprete();
        bool setFile(const std::string &name);
        std::shared_ptr<Value> statement_result;
    private:
        std::unique_ptr<ifstream> file;
        std::vector<Statement> statements_list;
        std::vector<std::unordered_map<string, Value>> variables_list;
        std::vector<unique_ptr<void *>> handle_list;
    };
}

#endif