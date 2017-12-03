#ifndef NEWBIE_HPP
#define NEWBIE_HPP
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <utility>
#include <stack>
#include <iostream>

/*For flex and bison*/
typedef void* yyscan_t;
void yyrestart(FILE *input_file, yyscan_t yyscanner);
int yylex_init(yyscan_t* scanner);
int yylex_destroy(yyscan_t yyscanner);
void yyset_in(FILE * _in_str, yyscan_t yyscanner);
int yyget_lineno(yyscan_t yyscanner);
int yyget_column(yyscan_t yyscanner);

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
		VARIOUS_TYPE,
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
		Expression(const Expression &);
		Expression &operator=(Expression&&);
		Expression &operator=(const Expression&);
		void swap(Expression &);

		template<typename T>
		T &get() const { return *static_cast<T*>(content); }

		~Expression();
    };


	struct BinaryExpression
	{
		BinaryType type;
		Expression lexp;
		Expression rexp;
	};

	struct UnaryExpression
	{
		UnaryType type;
		Expression exp;
	};

	struct FunctionCallExpression
	{
		Identifier identifier;
		std::vector<Expression> alist;
	};

	struct IndexExpression
	{
		Expression exp;
		Expression index;
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
		BLOCK_STATEMENT,
		IF_STATEMENT,
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
		Statement(const Statement &);
		Statement &operator=(Statement&&);
		Statement &operator=(const Statement &);
		void swap(Statement &);

		template<typename T>
		T &get() const { return *static_cast<T*>(content); }

		~Statement();
	};

	using StatementsList = std::vector<Statement>;

	struct DeclarationStatementItem
	{
		Identifier identifier;
		Expression initial_value;
	};
	using DeclarationStatementItemList = std::vector<DeclarationStatementItem>;

	struct DeclarationStatement
	{
		ValueType type;
		DeclarationStatementItemList items;
	};

	struct AssignmentStatement
	{
		Identifier identifier;
		Expression value;
	};

	struct ElseIf
	{
		Expression condition;
		Statement stat;
	};

	struct IfStatement
	{
		Expression condition;
		Statement stat;
		std::vector<ElseIf> elseif;
		Statement else_stat;
	};

	struct ForStatement
	{
		Expression exp1;
		Expression exp2;
		Expression exp3;
		Statement stat;
	};

	struct ForeachStatement
	{
		Identifier identifier;
		Expression exp;
		Statement stat;
	};

	using ExpressionStatement = Expression;
	using BlockStatement = StatementsList;
	using ReturnStatement = Expression;

	struct Parameter
	{
		ValueType type;
		Identifier identifier;
		Expression default_value; //only Value
	};

	using ParametersList = std::vector<Parameter>;

	using ArgumentsList = std::vector<Expression>;

	using VariablesList = std::stack<std::unordered_map<std::string, Value>>;

    class InterpreterImp
    {
    public:
        InterpreterImp();
        InterpreterImp(const std::string &name);
		~InterpreterImp() = default;
        bool interprete();
		bool setFile(const std::string &name);
		int parse();

		std::string filename;
        StatementsList statements_list;
        VariablesList vstack;
        std::vector<std::unique_ptr<void *>> handle_list;
    };
}

#endif