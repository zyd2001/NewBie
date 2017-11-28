#ifndef NEWBIE_HPP
#define NEWBIE_HPP
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <utility>
#include <stack>
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
        NOT
    };

    enum ValueType
    {
		NULL_TYPE,
        INT_TYPE,
        DOUBLE_TYPE,
        BOOL_TYPE,
        STRING_TYPE,
        ARRAY_TYPE,
        OBJECT_TYPE
    };
    
#if defined(_MSC_VER)
using char_t = uint32_t;
using string_t = std::basic_string<char_t>;
#define U(str) reinterpret_cast<const char_t*>(U##str)
#elif defined(__GNUC__)
#define U(str) U##str
using char_t = char32_t;
using string_t = std::basic_string<char_t>;
#endif

    struct Value 
    {
        ValueType type;
		void *content;
		void change_type(ValueType);

		template<typename T>
		T &get() const { return *static_cast<T*>(content); }

		Value();
		Value(Value&&);
		Value(ValueType, void*);
		Value(const Value&);
		Value(const int&);
		Value(const double&);
		Value(const bool&);
		Value(const string_t&);
		Value(const char_t*);
		~Value();
		void swap(Value &);
		Value operator+(const Value&) const;
		Value operator-(const Value&) const;
		Value operator*(const Value&) const;
		Value operator/(const Value&) const;
		Value &operator=(const Value&);
		Value &operator=(Value&&);
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

	using Identifier = std::string;

	enum ExpressionType
	{
		NULL_EXPRESSION,
		LITERAL_EXPRESSION,
		IDENTIFIER_EXPRESSION,
		BINARY_EXPRESSION,
		UNARY_EXPRESSION,
		FUNCTION_CALL_EXPRESSION,
		ARRAY_EXPRESSION,
		INDEX_EXPRESSION
	};

    struct Expression
    {
		ExpressionType type;
		void *content;
		Expression();
		Expression(ExpressionType, void*);
		Expression(Expression &&);
		Expression &operator=(Expression&&);
		~Expression();
    };


	struct BinaryExpression
	{
		BinaryType type;
		Expression &lexp;
		Expression &rexp;
	};

	struct UnaryExpression
	{
		UnaryType type;
		Expression &exp;
	};

	struct FunctionCallExpression
	{
		Identifier &identifier;
		std::vector<Expression> alist;
	};

	struct IndexExpression
	{
		Expression &exp;
		Expression &index;
	};

	using ArrayExpression = std::vector<Expression>;
	using IdentifierExpression = std::string;
	using LiteralExpression = Value;

	enum StatementType
	{
		NULL_STATEMENT,
		EXPRESSION_STATEMENT,
		ASSIGNMENT_STATEMENT,
		DECLARATION_STATEMENT,
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
		Statement();
		Statement(StatementType, void*);
		Statement(Statement &&);
		Statement &operator=(Statement&&);
		~Statement();
	};

	using StatementsList = std::vector<Statement>;

	struct DeclarationStatementItem
	{
		Identifier &identifier;
		Expression &initial_value;
	};

	struct DeclarationStatement
	{
		ValueType type;
		std::vector<DeclarationStatementItem> items;
	};

	struct AssignmentStatement
	{
		Identifier &identifier;
		Expression &value;
	};

	struct IfStatement
	{
		Expression &condition;
		Statement &stat;
		std::vector<IfStatement> elseif;
		Statement &else_stat;
	};

	struct ForStatement
	{
		Expression &exp1;
		Expression &exp2;
		Expression &exp3;
		Statement &stat;
	};

	struct ForeachStatement
	{
		Identifier &identifier;
		Expression &exp;
		Statement &stat;
	};

	using ExpressionStatement = Expression;
	using BlockStatement = StatementsList;
	using ReturnStatement = Expression;

	struct Parameter
	{
		ValueType type;
		Identifier &identifier;
		Expression &default_value;
	};
	using ParametersList = std::vector<Parameter>;

	using ArgumentsList = std::vector<Expression>;

	using VariablesList = std::stack<std::unordered_map<std::string, Value>>;

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
    private:
        std::unique_ptr<std::ifstream> file;
		std::string filename;
        StatementsList statements_list;
        VariablesList vstack;
        std::vector<std::unique_ptr<void *>> handle_list;
    };
}

#endif