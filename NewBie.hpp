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
    
#if defined(_MSC_VER)
using String = std::basic_string<uint32_t>;
#define U(str) reinterpret_cast<const uint32_t*>(U##str)
using char_t = uint32_t;
#elif defined(__GNUC__)
#define U(str) U##str
using String = std::u32string;
using char_t = char32_t;
#endif

    struct Value 
    {
        ValueType type;
		void *content;
		void change_type(ValueType);

		template<typename T>
		T &get() const { return *static_cast<T*>(content); }

		Value(ValueType, void*);
		Value(const Value&);
		Value(const int&);
		Value(const double&);
		Value(const bool&);
		Value(const String&);
		Value(const char_t*);
		~Value();
		void swap(Value &);
		Value operator+(const Value&) const;
		Value operator-(const Value&) const;
		Value operator*(const Value&) const;
		Value operator/(const Value&) const;
		Value &operator=(const Value&);
		bool operator==(const Value&) const;
		bool operator!=(const Value&) const;
		bool operator>(const Value&) const;
		bool operator>=(const Value&) const;
		bool operator<(const Value&) const;
		bool operator<=(const Value&) const;
		bool operator!() const;
		Value operator-() const;
		friend std::ostream &operator<<(std::ostream&, Value&);
    };

	std::ostream &operator<<(std::ostream&, Value&);
	Value change(const Value&, ValueType);

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

	struct BinaryExpression
	{
		BinaryType type;
		std::shared_ptr<Expression> lexp;
		std::shared_ptr<Expression> rexp;
	};

	struct UnaryExpression
	{
		UnaryType type;
		std::shared_ptr<Expression> exp;
	};

	struct FunctionCallExpression
	{
		std::string identifier;
		std::vector<Expression> alist;
	};

	struct IndexExpression
	{
		std::shared_ptr<Expression> exp;
		std::shared_ptr<Expression> index;
	};

	typedef std::vector<Expression> ArrayExpression;
	typedef std::string IdentifierExpression;
	typedef Value LiteralExpression;

    struct Expression
    {
		ExpressionType type;
		void *content;
		Expression(ExpressionType, void*);
		~Expression();
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

	using ExpressionsList = std::vector<Expression>;

	struct Statement
	{
		StatementType type;
		void *content;
		Statement(StatementType, void*);
		~Statement();
	};

	using StatementsList = std::vector<Statement>;
	using VariablesList = std::vector<std::unordered_map<std::string, Value>>;

#define YY_DECL zyd2001::NewBie::Parser::symbol_type yyFlexLexer::yylex(zyd2001::NewBie::Interpreter::InterpreterImp &inter)
//YY_DECL;

    class Interpreter::InterpreterImp
    {
    public:
        InterpreterImp();
        InterpreterImp(const std::string &name);
        ~InterpreterImp();
        bool interprete();
		bool setFile(const std::string &name);
		int parse();
        std::shared_ptr<Value> statement_result;
    private:
        std::unique_ptr<std::ifstream> file;
		std::string filename;
        StatementsList statements_list;
        VariablesList variables_list;
        std::vector<std::unique_ptr<void *>> handle_list;
    };
}

#endif