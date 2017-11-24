#ifndef NEWBIE_HPP
#define NEWBIE_HPP
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <utility>
#include <iostream>

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
        INT_TYPE,
        DOUBLE_TYPE,
        BOOL_TYPE,
        STRING_TYPE,
        ARRAY_TYPE,
        OBJECT_TYPE
    };
    
    struct Value 
    {
        ValueType type;
		void *content;
		void operator+(const Value&);
		void change_type(ValueType);

		template<typename T>
		T &get() { return *static_cast<T*>(content); }

		Value(ValueType, void*);
		~Value();
    };

	enum ExpressionType
	{
		LITERAL_EXPRESSION,
		IDENTIFIER_EXPRESSION,
		BINARY_EXPRESSION,
		UNARY_EXPRESSION,
		FUNCTION_CALL_EXPRESSION,
		ARRAY_EXPRESSION,
		INDEX_EXPRESSION
	};

	struct Expression;

	//struct DeclarationExpression
	//{
	//	ValueType type;
	//	std::string identifier;
	//	std::unique_ptr<Expression> exp;
	//};

	struct BinaryExpression
	{
		BinaryType type;
		std::unique_ptr<Expression> lexp;
		std::unique_ptr<Expression> rexp;
	};

	struct UnaryExpression
	{
		UnaryType type;
		std::unique_ptr<Expression> exp;
	};

	//struct AssignmentExpression
	//{
	//	std::unique_ptr<Expression> lexp;
	//	std::unique_ptr<Expression> rexp;
	//};

	struct FunctionCallExpression
	{
		std::string identifier;
		std::vector<Expression> alist;
	};

	struct IndexExpression
	{
		std::unique_ptr<Expression> exp;
		std::unique_ptr<Expression> index;
	};

	typedef std::vector<Expression> ArrayExpression;
	typedef std::string IdentifierExpression;
	typedef Value LiteralExpression;

    struct Expression
    {
		ExpressionType type;
		void *content;
		Expression(ExpressionType, void*);
		~Expression() {}
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
		void *content;
		~Statement() {};
	};

    class Interpreter::InterpreterImp
    {
    public:
        InterpreterImp();
        InterpreterImp(const std::string &name);
        ~InterpreterImp();
        bool interprete();
        bool setFile(const std::string &name);
        std::shared_ptr<Value> statement_result;
    private:
        std::unique_ptr<std::ifstream> file;
		std::string filename;
        std::vector<Statement> statements_list;
        std::vector<std::unordered_map<std::string, Value>> variables_list;
        std::vector<std::unique_ptr<void *>> handle_list;
    };
}

#endif