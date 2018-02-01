#ifndef NEWBIE_HPP
#define NEWBIE_HPP
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <utility>
#include <stack>
#include <iostream>
#include <functional>
#include "Graph.hpp"

/*For flex and bison*/
typedef void* yyscan_t;
void yyrestart(FILE *input_file, yyscan_t yyscanner);
int yylex_init(yyscan_t* scanner);
int yylex_destroy(yyscan_t yyscanner);
void yyset_in(FILE * _in_str, yyscan_t yyscanner);
int yyget_lineno(yyscan_t yyscanner);
int yyget_column(yyscan_t yyscanner);

namespace zyd2001
{
    namespace NewBie
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
            VARIANT_TYPE,
            ARRAY_TYPE,
            FUNCTION_TYPE,
            OBJECT_TYPE
        };

#if defined(_MSC_VER)
        using char_t = uint32_t;
#define U(str) reinterpret_cast<const char_t*>(U##str)
#elif defined(__GNUC__)
#define U(str) U##str
        using char_t = char32_t;
#endif

        struct string_t
        {
            std::shared_ptr<std::basic_string<char_t>> ptr;
            string_t();
            string_t(const char_t*);
            string_t(const std::basic_string<char_t>&);
            string_t(const string_t &);

            string_t &operator=(const string_t &);
            string_t operator+(const string_t &);
            string_t &operator+=(const string_t &);
            bool operator==(const string_t &) const;

            std::basic_string<char_t> &get();

            struct hash
            {
                std::hash<std::basic_string<char_t>> h;
                std::size_t operator()(const string_t&) const;
            };
        };

        using Identifier = string_t;

        struct Value
        {
            ValueType type;
            bool various = false;
            void *content;

            template<typename T>
            T &get() const { return *static_cast<T*>(content); }
            Value &change_type(ValueType);

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
            Value operator%(const Value&) const;
            Value &operator=(const Value&);
            Value &operator=(Value&&);
            bool operator==(const Value&) const;
            bool operator!=(const Value&) const;
            bool operator>(const Value&) const;
            bool operator>=(const Value&) const;
            bool operator<(const Value&) const;
            bool operator<=(const Value&) const;
            bool operator&&(const Value&) const;
            bool operator||(const Value&) const;
            bool operator!() const;
            Value operator-() const;
            friend std::ostream &operator<<(std::ostream&, Value&);
        };

        std::ostream &operator<<(std::ostream&, Value&);
        Value change(const Value&, ValueType);

        using Array = std::vector<Value>;
        using VariablesMap = std::unordered_map<Identifier, Value, Identifier::hash>;

        enum ExpressionType
        {
            NULL_EXPRESSION,
            LITERAL_EXPRESSION,
            IDENTIFIER_EXPRESSION,
            BINARY_EXPRESSION,
            UNARY_EXPRESSION,
            FUNCTION_CALL_EXPRESSION,
            ARRAY_EXPRESSION,
            ARRAY_LENGTH_EXPRESSION,
            INDEX_EXPRESSION,
            THIS_EXPRESSION,
            DOT_EXPRESSION,
            NEW_OBJECT_EXPRESSION
        };

        struct Expression
        {
            ExpressionType type;
            void *content;
            int *ref_count;

            Expression();
            Expression(ExpressionType, void*);
            Expression(const Expression &);
            //Expression &operator=(const Expression&);
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
            Expression identifier;
            std::vector<Expression> alist;
        };

        struct IndexExpression
        {
            Expression exp;
            Expression index;
        };

        struct DotExpression
        {
            Expression obj;
            Expression exp;
        };

        using ArrayExpression = std::vector<Expression>;
        using ExpressionsList = ArrayExpression;
        using IdentifierExpression = string_t;
        using LiteralExpression = Value;

        enum StatementType
        {
            NULL_STATEMENT,
            FUNCTION_DEFINITION_STATEMENT,
            EXPRESSION_STATEMENT,
            ASSIGNMENT_STATEMENT,
            DECLARATION_STATEMENT,
            BLOCK_STATEMENT,
            IF_STATEMENT,
            FOR_STATEMENT,
            FOREACH_STATEMENT,
            RETURN_STATEMENT,
            CONTINUE_STATEMENT,
            BREAK_STATEMENT,
            DEBUG_STATEMENT
        };

        struct Statement
        {
            StatementType type;
            void *content;
            int lineno;
            int *ref_count;

            Statement();
            Statement(StatementType, void*, int);
            Statement(const Statement &);
            //Statement &operator=(const Statement &);
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
        using DeclarationStatementItemsList = std::vector<DeclarationStatementItem>;
        struct DeclarationStatement
        {
            bool global;
            ValueType type;
            DeclarationStatementItemsList items;
            Identifier obj_type;
        };

        struct ObjDeclarationStatement
        {
            Identifier type;
            DeclarationStatementItemsList items;
            bool global;
        };

        struct AssignmentStatement
        {
            Expression lvalue;
            Expression rvalue;
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
            Statement pre;
            Expression condition;
            Statement after;
            Statement stat;
        };

        struct ForeachStatement
        {
            Identifier identifier;
            Expression exp;
            Statement stat;
            bool reverse;
        };

        using ExpressionStatement = Expression;
        using BlockStatement = StatementsList;
        using ReturnStatement = Expression;
        using DebugStatement = Expression;

        struct Parameter
        {
            ValueType type;
            Identifier identifier;
            Expression default_value_exp; //only Value
        };

        //stack unit
        using deleter = std::function<void(std::vector<VariablesMap>*)>;
        using stack_unit = std::unique_ptr<std::vector<VariablesMap>, deleter >;
        void disabled_deleter(std::vector<VariablesMap> *p);
        void enabled_deleter(std::vector<VariablesMap> *p);
        stack_unit make_stack_unit();
        stack_unit make_temp_unit(std::vector<VariablesMap>&);
        using VariablesStack = std::stack<stack_unit>;

        using ParametersList = std::vector<Parameter>;
        using ArgumentsList = std::vector<Expression>;

        struct ParamsHash
        {
            std::size_t operator()(const ParametersList& p) const;
        };
        struct ParamsEqualTo
        {
            bool operator()(const ParametersList& lhs, const ParametersList& rhs) const;
        };

        struct function_t
        {
            ValueType return_type;
            bool can_overload = true;
            virtual Value& call(ArgumentsList&);
        };
        struct NormalFunction : public function_t
        {
            std::unordered_map<ParametersList, Statement, ParamsHash, ParamsEqualTo> overload_map;
            Value& call(ArgumentsList&) override;
        };
        struct NativeFunction : public function_t
        {
            std::function<void(std::function<Value&(Identifier)>, ArgumentsList&)> func;
            Value& call(ArgumentsList&) override;
        };
        using Function = std::shared_ptr<function_t>;

        struct Class
        {
            Identifier type;
            Class *base;
            Function ctor;
            VariablesMap static_variables;
            virtual Value& makeObject(ArgumentsList&);
        };
        struct NormalClass : public Class
        {
            StatementsList slist;
            Value& makeObject(ArgumentsList&) override;
        };
        struct NativeClass : public Class
        {
            Identifier type;
            VariablesMap var;
            Value& makeObject(ArgumentsList&) override;
        };
        using ClassMap = std::unordered_map<Identifier, Class, Identifier::hash>;

        struct object_t
        {
            Identifier type;
            Class *cl;
            std::vector<object_t*> bases;
            std::vector<VariablesMap> local_env;
        };
        struct GraphNode
        {
            long ref_count;
            object_t *ptr;
            GraphNode(object_t *);
        };
        struct Object
        {
            GraphNode *node;
            Object(GraphNode *);
            Object(const Object &);
            object_t &operator*();
            object_t *operator->();
            ~Object();
        };

        class InterpreterImp
        {
        public:
            /* public api */
            InterpreterImp();
            InterpreterImp(const std::string &name);
            ~InterpreterImp() = default;
            void parse();
            bool run();
            bool setFile(const std::string &name);
            bool changeSetting(const std::string &, int);
            void addVar(Value&);
            void addGlobalVar(Value&);
            void changeVar(Identifier, Value&);
            void registerClass(Identifier, NativeClass&);
            void registerFunction(Identifier, NativeFunction&);

            StatementType execute(const Statement &);
            StatementType interpret(const StatementsList &);
            Value &evaluate(const Expression &);
            void err();
            void err(const std::string&);
            int checkExist(const Identifier &);
            void initialize_obj_env(Value &);
            void restore_obj_env();

            /*parsing time variables*/
            int level = 0;
            std::string filename;
            bool in_class = false;
            Class *current_class = new Class();

            /*runtime variables*/
            GraphNode *root;
            int current_lineno;
            int object_count = 0;
            DirectedGraph<GraphNode*> gc_graph;
            //support "this" expression
            bool in_object = false;
            Value *current_object;
            std::stack<Value*> object_env_stack;

            //for return value
            Value temp_variable;

            //global scope
            VariablesMap global_variables;

            StatementsList statements_list;
            VariablesStack variables_stack;
            ClassMap class_map;
            std::vector<std::unique_ptr<void *>> handle_list;
            std::unordered_map<std::string, int> settings;
        };
    }
}

#endif