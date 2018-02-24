#ifndef NEWBIE_HPP
#define NEWBIE_HPP
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <memory>
#include <utility>
#include <stack>
#include <iostream>
#include <functional>
#include <typeinfo>
#include <thread>
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
            NEGATE,
            NOT
        };
        
        using ObjectType = unsigned long;
        //enum ValueType : ObjectType // when ValueType > 7, it will represent the class's id
        //{
        //    NULL_TYPE = 0,
        //    INT_TYPE,
        //    DOUBLE_TYPE,
        //    BOOL_TYPE,
        //    STRING_TYPE,
        //    VARIANT_TYPE,
        //    ARRAY_TYPE,
        //    FUNCTION_TYPE = 7
        //};

        enum AccessControl
        {
            PUBLIC,
            READONLY,
            PRIVATE
        };

#if defined(_MSC_VER)
        using char_t = uint32_t;
#define U(str) reinterpret_cast<const char_t*>(U##str)
#elif defined(__GNUC__)
#define U(str) U##str
        using char_t = char32_t;
#endif

        struct String
        {
            std::shared_ptr<std::basic_string<char_t>> ptr;
            String();
            String(const char_t*);
            String(const std::basic_string<char_t>&);
            String(const String &);

            String &operator=(const String &);
            String operator+(const String &);
            String &operator+=(const String &);
            bool operator==(const String &) const;
            bool operator>(const String &) const;
            bool operator<(const String &) const;
            String copy();

            std::basic_string<char_t> &get();

            struct hash
            {
                std::hash<std::basic_string<char_t>> h;
                std::size_t operator()(const String&) const;
            };
        };

        using Identifier = String;

        struct Integer
        {
            std::shared_ptr<int> ptr;
            Integer(int i) : ptr(std::make_shared<int>(i)) {}
            Integer copy() { return Integer(*ptr); }
            int &operator*() { return *ptr; }
            int *operator->() { return ptr.get(); }
        };
        struct Double
        {
            std::shared_ptr<double> ptr;
            Double(double i) : ptr(std::make_shared<double>(i)) {}
            Double copy() { return Double(*ptr); }
            double &operator*() { return *ptr; }
            double *operator->() { return ptr.get(); }
        };
        struct Boolean
        {
            std::shared_ptr<bool> ptr;
            Boolean(bool i) : ptr(std::make_shared<bool>(i)) {}
            Boolean copy() { return Boolean(*ptr); }
            bool &operator*() { return *ptr; }
            bool *operator->() { return ptr.get(); }
        };

        using ObjectMap = std::unordered_map<Identifier, Object, Identifier::hash>;

        struct object_t
        {
            Identifier type_name;
            ObjectType type;
            Class cl;
            void *native_ptr;
            std::function<void(void*)> deleter = [](void*) {};
            std::vector<object_t*> bases;
            std::vector<Function> op; //operator+ - * / % unary-, comp, []
            void addVariable(Identifier, Object, AccessControl);
            Object getVariable(Identifier);
            void changeVariable(Identifier, Object);
            ~object_t() { deleter(native_ptr); }
        private:
            std::unordered_map<Identifier, std::pair<Object, AccessControl>, Identifier::hash> local_variables;
        };
        struct Object
        {
            object_t *obj;
            ObjectType restrict_type;
            bool in_map = false;
            Object() : obj(nullptr){}
            Object(object_t *);
            Object(const Object &);
            Object(const int &);
            Object(const double &);
            Object(const bool &);
            Object(const String &);
            Object(const Function &);
            Object operator+(const Object &) const;
            Object operator-(const Object &) const;
            Object operator*(const Object &) const;
            Object operator/(const Object &) const;
            Object operator%(const Object &) const;
            Object &operator=(const Object &);
            bool operator==(const Object&) const;
            bool operator!=(const Object&) const;
            bool operator>(const Object&) const;
            bool operator>=(const Object&) const;
            bool operator<(const Object&) const;
            bool operator<=(const Object&) const;
            bool operator&&(const Object&) const;
            bool operator||(const Object&) const;
            bool operator!() const;
            Object operator-() const;
            Object getVariable(Identifier);
            void changeVariable(Identifier, Object);
            ~Object() = default;
        };

        using IdentifierList = std::vector<Identifier>;
        struct class_t
        {
            Identifier type_name;
            ObjectType type;
            std::vector<class_t*> base_list;
            Function ctor;
            virtual object_t *makeObject(ArgumentList&) = 0;
            void addStaticVariable(Identifier, Object, AccessControl);
            Object getStaticVariable(Identifier);
            void changeStaticVariable(Identifier, Object);
            virtual ~class_t() = default;
        private:
            std::unordered_map<Identifier, std::pair<Object, AccessControl>, Identifier::hash> static_variables;
        };
        struct NormalClass : public class_t
        {
            std::unordered_map<Identifier, std::tuple<ObjectType, AccessControl, Expression>, Identifier::hash> variables;
            object_t *makeObject(ArgumentList&) override;
        };
        struct NativeClass : public class_t
        {
            std::function<object_t*(ArgumentList&, object_t*)> real;
            object_t *makeObject(ArgumentList&) override;
        };
        using Class = std::shared_ptr<class_t>;
        using ClassMap = std::pair<std::unordered_map<Identifier, ObjectType, Identifier::hash>, std::unordered_map<ObjectType, Class>>;

        struct function_t
        {
            ObjectType return_type;
            Identifier name;
            bool can_overload = true;
            virtual Object call(ArgumentList&, object_t*) = 0;
            virtual Object call(ArgumentList&, class_t*) = 0;
            virtual Object call(ArgumentList&) = 0;
            virtual ~function_t() = default;
        };
        struct NormalFunction : public function_t
        {
            std::unordered_map<ParameterList, Statement, ParamsHash, ParamsEqualTo> overload_map;
            Object call(ArgumentList&, object_t*) override;
            Object call(ArgumentList&, class_t*) override;
            Object call(ArgumentList&) override;
        };
        struct NativeFunction : public function_t
        {
            std::unordered_map<ParameterList, std::function<Object(std::vector<Object>&, object_t*)>, ParamsHash, ParamsEqualTo> native_func;
            Object call(ArgumentList&, object_t*) override;
            Object call(ArgumentList&, class_t*) override;
            Object call(ArgumentList&) override;
        };
        struct NativeStaticFunction : public function_t
        {
            std::unordered_map<ParameterList, std::function<Object(std::vector<Object>&, class_t*)>, ParamsHash, ParamsEqualTo> native_func;
            Object call(ArgumentList&, object_t*) override;
            Object call(ArgumentList&, class_t*) override;
            Object call(ArgumentList&) override;
        };
        using Function = std::shared_ptr<function_t>;

        using VariablesStack = std::stack<std::vector<ObjectMap>>;
        struct RAIIStack
        {
            RAIIStack();
            ~RAIIStack();
        };
#define newVariablesStack() zyd2001::NewBie::RAIIStack __newbie__stack__
        struct RAIIObject
        {
            RAIIObject(Object);
            RAIIObject(object_t*);
            ~RAIIObject();
        };
#define useObject(obj) zyd2001::NewBie::RAIIObject __newbie__obj__(obj)
        struct RAIIClass
        {
            RAIIClass(Class);
            RAIIClass(class_t*);
            ~RAIIClass();
        };
#define useClass(cl) zyd2001::NewBie::RAIIClass __newbie__class__(cl)

        //enum ExpressionType
        //{
        //    NULL_EXPRESSION,
        //    LITERAL_EXPRESSION,
        //    IDENTIFIER_EXPRESSION,
        //    BINARY_EXPRESSION,
        //    UNARY_EXPRESSION,
        //    FUNCTION_CALL_EXPRESSION,
        //    ARRAY_EXPRESSION,
        //    ARRAY_LENGTH_EXPRESSION,
        //    INDEX_EXPRESSION,
        //    THIS_EXPRESSION,
        //    DOT_EXPRESSION,
        //    NEW_OBJECT_EXPRESSION
        //};

        //struct Expression
        //{
        //    ExpressionType type;
        //    void *content;
        //    int *ref_count;

        //    Expression();
        //    Expression(Object);
        //    Expression(ExpressionType, void*);
        //    Expression(const Expression &);
        //    //Expression &operator=(const Expression&);
        //    void swap(Expression &);

        //    template<typename T>
        //    T &get() const { return *static_cast<T*>(content); }

        //    ~Expression();
        //};

        struct expression_t
        {
            virtual Object evaluate() = 0;
            virtual ~expression_t() = default;
        };
        using Expression = std::shared_ptr<expression_t>;
        using ExpressionList = ArrayExpression;

        struct NullExpression : public expression_t
        {
            Object evaluate() override
            {
                return Object();
            }
        };

        struct IdentifierExpression : public expression_t
        {
            String str;
            Object evaluate() override;
        };
        
        struct LiteralExpression : public expression_t
        {
            Object obj;
            Object evaluate() override;
        };

        struct ArrayExpression : public expression_t
        {
            ExpressionList list;
            Object evaluate() override;
        };

        struct BinaryExpression : public expression_t
        {
            BinaryType type;
            Expression lexp;
            Expression rexp;
            Object evaluate() override;
        };

        struct UnaryExpression : public expression_t
        {
            UnaryType type;
            Expression exp;
            Object evaluate() override;
        };

        struct FunctionCallExpression : public expression_t
        {
            Expression identifier;
            ExpressionList alist;
            Object evaluate() override;
        };

        struct NewObjectExpression : public expression_t
        {
            Expression identifier;
            ExpressionList alist;
            Object evaluate() override;
        };

        struct IndexExpression : public expression_t
        {
            Expression exp;
            Expression index;
            Object evaluate() override;
        };

        struct DotExpression : public expression_t
        {
            Expression obj;
            Expression exp;
            Object evaluate() override;
        };

        //enum StatementType
        //{
        //    NULL_STATEMENT,
        //    FUNCTION_DEFINITION_STATEMENT,
        //    EXPRESSION_STATEMENT,
        //    ASSIGNMENT_STATEMENT,
        //    DECLARATION_STATEMENT,
        //    BLOCK_STATEMENT,
        //    IF_STATEMENT,
        //    FOR_STATEMENT,
        //    FOREACH_STATEMENT,
        //    RETURN_STATEMENT,
        //    CONTINUE_STATEMENT,
        //    BREAK_STATEMENT,
        //    DEBUG_STATEMENT
        //};

        //struct Statement
        //{
        //    StatementType type;
        //    void *content;
        //    int lineno;
        //    int *ref_count;

        //    Statement();
        //    Statement(StatementType, void*, int);
        //    Statement(const Statement &);
        //    //Statement &operator=(const Statement &);
        //    void swap(Statement &);

        //    template<typename T>
        //    T &get() const { return *static_cast<T*>(content); }

        //    ~Statement();
        //};

        struct statement_t
        {
            virtual void execute() = 0;
            virtual ~statement_t() = default;
        };
        using Statement = std::shared_ptr<statement_t>;
        using StatementList = std::vector<Statement>;

        struct DeclarationStatementItem
        {
            Identifier identifier;
            Expression initial_value;
        };
        using DeclarationStatementItemList = std::vector<DeclarationStatementItem>;
        struct DeclarationStatement : public statement_t
        {
            bool global;
            Identifier obj_type;
            DeclarationStatementItemList items;
            void execute() override;
        };

        struct AssignmentStatement : public statement_t
        {
            Expression lvalue;
            Expression rvalue;
            void execute() override;
        };

        struct ElseIf
        {
            Expression condition;
            Statement stat;
        };

        struct IfStatement : public statement_t
        {
            Expression condition;
            Statement stat;
            std::vector<ElseIf> elseif;
            Statement else_stat;
            void execute() override;
        };

        struct ForStatement : public statement_t
        {
            Statement pre;
            Expression condition;
            Statement after;
            Statement stat;
            void execute() override;
        };

        struct ForeachStatement : public statement_t
        {
            Identifier identifier;
            Expression exp;
            Statement stat;
            bool reverse;
            void execute() override;
        };

        struct FunctionDefinitionStatement : public statement_t
        {
            Function func;
            void execute() override;
        };

        struct ExpressionStatement : public statement_t
        {
            Expression exp;
            void execute() override;
        };

        struct BlockStatement : public statement_t
        {
            StatementList slist;
            void execute() override;
        };

        struct ReturnStatement : public statement_t
        {
            Expression exp;
            void execute() override;
        };

        struct Parameter
        {
            ObjectType type;
            Identifier identifier;
            bool ref;
            Expression default_value_exp; //only Object
        };

        using ParameterList = std::vector<Parameter>;
        using ArgumentList = std::vector<Expression>;

        struct ParamsHash
        {
            std::size_t operator()(const ParameterList& p) const;
        };
        struct ParamsEqualTo
        {
            bool operator()(const ParameterList& lhs, const ParameterList& rhs) const;
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
            void performGC();
            void GC();
            void concurrentGC();
            void declareVariable(Identifier, ObjectType, bool global = false);
            void declareVariable(Identifier, Identifier type, bool global = false);
            void declareVariable(Identifier, Object, bool global = false);
            void changeVariable(Identifier, Object, bool global = false);
            void deleteVariable(Identifier, bool global = false);
            Object getVariable(Identifier, bool global = false);
            bool typeCheck(Object, Object);
            void addGCVertex(Object);
            void delGCVertex(Object);
            void addGCEdge(object_t*, Object);
            void addGCEdge(Object, Object);
            void delGCEdge(object_t*, Object);
            void delGCEdge(Object, Object);
            void registerClass(Class);
            void resolveClass(StatementList&);
            void resolveClass(StatementList&, std::vector<Identifier>&);
            std::vector<Object> resolveArgumentList(ArgumentList&);
            ParameterList ArgsToParams(std::vector<Object>&);

            //StatementType execute(const Statement &);
            void interpret(const StatementList &);
            //Object &evaluate(const Expression &);
            //void err();
            //void err(const std::string&);
            //int checkExist(const Identifier &);

            /*parsing time variables*/
            int level = 0;
            std::string filename;


            /*runtime variables*/
            object_t *root;
            int current_lineno;
            long class_count = 0;
            DirectedGraph<object_t*> gc_graph;
            ObjectMap *current_variables;
            //support "static"
            bool in_class = false;
            class_t* current_class;
            std::stack<class_t*> class_env_stack;
            //support "this" expression
            bool in_object = false;
            object_t *current_object;
            std::stack<object_t*> object_env_stack;

            //for return value
            //Object temp_variable;

            //global scope
            ObjectMap global_variables;

            StatementList statement_list;
            VariablesStack variables_stack;
            ClassMap class_map;
            std::vector<std::unique_ptr<void *>> handle_list;
            std::unordered_map<std::string, int> settings;
        };
    }
}

#endif