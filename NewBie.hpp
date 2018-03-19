#ifndef NEWBIE_HPP
#define NEWBIE_HPP
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <list>
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
        using ObjectMapA = std::unordered_map<Identifier, std::pair<Object, AccessControl>, Identifier::hash>;
        struct object_t
        {
            InterpreterImp *inter;
            Identifier type_name;
            ObjectType type;
            Class cl;
            int ref_count = 0; //for reference by RAII object
            void *native_ptr = nullptr;
            std::vector<object_t*> bases;
            void addVariable(Identifier, Object, AccessControl);
            Object &getVariable(Identifier);
            void changeVariable(Identifier, Object);
            Object &getSuperVariable(Identifier);
            Object &getSuperVariable(ObjectType type, Identifier);

            template<typename T>
            T &useNativePointer()
            {
                return *static_cast<T*>(native_ptr);
            }

            ~object_t();
        private:
            ObjectMapA local_variables;
        };
        struct Object
        {
            bool ref;
            object_t *belongs_to;
            void *content;
            ObjectType restrict_type;
            Object() : content(nullptr), restrict_type(0){}
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
            explicit operator bool() const;
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
            object_t *obj() const;
            Object &getVariable(Identifier) const;
            //void changeVariable(Identifier, Object);
            //~Object()
            //{
            //    if (obj->cl->RAII)
            //        delete obj;
            //}
        };

        using IdentifierList = std::vector<Identifier>;
        struct class_t
        {
            InterpreterImp *inter;
            Identifier type_name;
            ObjectType type;
            std::vector<Class> base_list;
            bool RAII = false;
            Constructor ctor;
            Function dtor;
            Function copy_ctor;
            std::vector<Function> op; //operator+ - * / % unary-, comp, [], ()
            std::function<object_t*(const object_t &)> native_copyer = [](const object_t &) -> object_t* {};
            std::function<void(void*)> native_deleter = [](void*) {};
            virtual object_t *makeObject(ArgumentList&) = 0;
            virtual object_t *makeObjectAsBase(ArgumentList&) = 0;
            void addStaticVariable(Identifier, Object, AccessControl);
            Object getStaticVariable(Identifier);
            void changeStaticVariable(Identifier, Object);
            virtual ~class_t() = default;
        private:
            ObjectMapA static_variables;
        };
        struct NormalClass : public class_t
        {
            std::unordered_map<Identifier, std::tuple<ObjectType, AccessControl, Expression>, Identifier::hash> variables;
            object_t *makeObject(ArgumentList&) override;
            object_t *makeObjectAsBase(ArgumentList&) override;
        };
        struct NativeClass : public class_t
        {
            std::function<object_t*(ArgumentList&, object_t*)> real;
            object_t *makeObject(ArgumentList&) override;
            object_t *makeObjectAsBase(ArgumentList&) override;
        };
        using Class = std::shared_ptr<class_t>;
        using ClassMap = std::pair<std::unordered_map<Identifier, ObjectType, Identifier::hash>, std::unordered_map<ObjectType, Class>>;

        struct function_t
        {
            InterpreterImp *inter;
            ObjectType return_type;
            Identifier name;
            object_t *obj;
            Class cl;
            bool can_overload = true;
            virtual Object call(InterpreterImp::Runner&, ArgumentList&) = 0;
            virtual ~function_t() = default;
        };
        struct NormalFunction : public function_t
        {
            std::unordered_map<ParameterList, Statement, ParamsHash, ParamsEqualTo> overload_map;
            Object call(InterpreterImp::Runner&, ArgumentList&) override;
            Object real_call(InterpreterImp::Runner&, ArgumentList&);
        };
        struct NativeFunction : public function_t
        {
            std::unordered_map<ParameterList, std::function<Object(std::vector<Object>&, object_t*)>, ParamsHash, ParamsEqualTo> native_func;
            Object call(InterpreterImp::Runner&, ArgumentList&) override;
        };
        struct NativeStaticFunction : public function_t
        {
            std::unordered_map<ParameterList, std::function<Object(std::vector<Object>&, class_t*)>, ParamsHash, ParamsEqualTo> native_func;
            Object call(InterpreterImp::Runner&, ArgumentList&) override;
        };
        using Function = std::shared_ptr<function_t>;

        struct ctorArgs
        {
            ObjectType type;
            ArgumentList args;
        };
        using ctorArgsList = std::vector<ctorArgs>;
        struct ctor
        {
            Statement stat;
            std::unordered_map<ObjectType, ArgumentList> base_args;
        };
        struct constructor_t
        {
            std::unordered_map<ParameterList, ctor, ParamsHash> overload_map;
        };
        using Constructor = std::shared_ptr<constructor_t>;

        using VariablesStack = std::stack<std::vector<ObjectMap>>;
        struct RAIIStack
        {
            InterpreterImp *inter;
            RAIIStack(InterpreterImp *inter);
            ~RAIIStack();
        };
#define newVariablesStack() zyd2001::NewBie::RAIIStack __newbie__stack__(inter)
        struct RAIIScope
        {
            InterpreterImp *inter;
            RAIIScope(InterpreterImp *inter);
            ~RAIIScope();
        };
#define newVariablesScope() zyd2001::NewBie::RAIIScope __newbie__scope__(inter)
        struct RAIIObject
        {
            InterpreterImp *inter;
            RAIIObject(Object, InterpreterImp *inter);
            RAIIObject(object_t*, InterpreterImp *inter);
            ~RAIIObject();
        };
#define useObject(obj) zyd2001::NewBie::RAIIObject __newbie__obj__(obj, inter)
        struct RAIIClass
        {
            InterpreterImp *inter;
            RAIIClass(Class, InterpreterImp *inter);
            RAIIClass(class_t*, InterpreterImp *inter);
            ~RAIIClass();
        };
#define useClass(cl) zyd2001::NewBie::RAIIClass __newbie__class__(cl, inter)

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
            InterpreterImp *inter;
            expression_t(InterpreterImp *i) : inter(i) {}
            virtual Object evaluate() = 0;
            virtual ExpressionType type() = 0;
            virtual ~expression_t() = default;
        };
        using Expression = std::shared_ptr<expression_t>;
        using ExpressionList = ArrayExpression;

        struct IdentifierExpression : public expression_t
        {
            Identifier id;
            IdentifierExpression(InterpreterImp *inter, Identifier i) : expression_t(inter), id(i) {}
            ExpressionType type() override { return IDENTIFIER_EXPRESSION; }
        };
        
        struct LiteralExpression : public expression_t
        {
            Object obj;
            LiteralExpression(InterpreterImp *inter, Object o) : expression_t(inter), obj(o) {}
            ExpressionType type() override { return LITERAL_EXPRESSION; }
        };

        struct ArrayExpression : public expression_t
        {
            ExpressionList list;
            ExpressionType type() override { return ARRAY_EXPRESSION; }
        };

        struct BinaryExpression : public expression_t
        {
            BinaryType type;
            Expression lexp;
            Expression rexp;
            BinaryExpression(InterpreterImp *inter, BinaryType t, Expression l, Expression r) : expression_t(inter), type(t), lexp(l), rexp(r) {}
            ExpressionType type() override { return BINARY_EXPRESSION; }
        };

        struct UnaryExpression : public expression_t
        {
            UnaryType type;
            Expression exp;
            UnaryExpression(InterpreterImp *inter, UnaryType t, Expression e) : expression_t(inter), type(t), exp(e) {}
            ExpressionType type() override { return UNARY_EXPRESSION; }
        };

        struct FunctionCallExpression : public expression_t
        {
            Expression func;
            ExpressionList alist;
            FunctionCallExpression(InterpreterImp *inter, Expression f, ExpressionList list) : expression_t(inter), func(f), alist(list) {}
            ExpressionType type() override { return FUNCTION_CALL_EXPRESSION; }
        };

        struct NewObjectExpression : public expression_t
        {
            Identifier id;
            ExpressionList alist;
            NewObjectExpression(InterpreterImp *inter, Identifier i, ExpressionList list) : expression_t(inter), id(i), alist(list) {}
            ExpressionType type() override { return NEW_OBJECT_EXPRESSION; }
        };

        struct IndexExpression : public expression_t
        {
            Expression exp;
            Expression index;
            ExpressionType type() override { return INDEX_EXPRESSION; }
        };

        struct DotExpression : public expression_t
        {
            Expression obj;
            Identifier id;
            DotExpression(InterpreterImp *inter, Expression o, Identifier i) : expression_t(inter), obj(o), id(i) {}
            ExpressionType type() override { return DOT_EXPRESSION; }
        };

        struct ThisExpression : public expression_t
        {
            ThisExpression(InterpreterImp *imp) : expression_t(inter) {}
            ExpressionType type() override { return THIS_EXPRESSION; }
        };

        enum StatementType
        {
            NULL_STATEMENT,
            FUNCTION_DEFINITION_STATEMENT,
            EXPRESSION_STATEMENT,
            ASSIGNMENT_STATEMENT,
            DECLARATION_STATEMENT,
            BUILTIN_DECLARATION_STATEMENT,
            BLOCK_STATEMENT,
            IF_STATEMENT,
            FOR_STATEMENT,
            WHILE_STATEMENT,
            FOREACH_STATEMENT,
            RETURN_STATEMENT,
            CONTINUE_STATEMENT,
            BREAK_STATEMENT,
            ACCESSCONTROL_STATEMENT
        };

        struct statement_t
        {
            int lineno;
            statement_t(int line) : lineno(line) {}
            virtual StatementType type() = 0;
            virtual ~statement_t() = default;
        };
        using Statement = std::shared_ptr<statement_t>;
        using StatementList = std::list<Statement>;

        struct AccessControlStatement : public statement_t
        {
            AccessControl visibility;
            AccessControlStatement(int line, AccessControl a) : statement_t(line), visibility(a) {}
            StatementType type() override { return ACCESSCONTROL_STATEMENT; }
        };

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
            DeclarationStatement(int line, bool g, Identifier t, DeclarationStatementItemList list) : statement_t(line), global(g), obj_type(t), items(list) {}
            StatementType type() override { return DECLARATION_STATEMENT; }
        };
        struct BuiltInDeclarationStatement : public statement_t
        {
            bool global;
            ObjectType type;
            DeclarationStatementItemList items;
            BuiltInDeclarationStatement(int line, bool g, ObjectType t, DeclarationStatementItemList list) : statement_t(line), global(g), type(t), items(list) {}
            StatementType type() override { return BUILTIN_DECLARATION_STATEMENT; }
        };

        struct AssignmentStatement : public statement_t
        {
            Expression lvalue;
            Expression rvalue;
            AssignmentStatement(int line, Expression l, Expression r) : statement_t(line), lvalue(l), rvalue(r) {}
            StatementType type() override { return ASSIGNMENT_STATEMENT; }
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
            IfStatement(int line, Expression e, Statement s) : statement_t(line), condition(e), stat(s) {}
            StatementType type() override { return IF_STATEMENT; }
        };

        struct ForStatement : public statement_t
        {
            Statement pre;
            Expression condition;
            Statement after;
            Statement stat;
            ForStatement(int line, Statement p, Expression e, Statement a, Statement s) : statement_t(line), condition(e), pre(p), after(a), stat(s) {}
            StatementType type() override { return FOR_STATEMENT; }
        };

        struct WhileStatement : public statement_t
        {
            bool do_while = false;
            Expression condition;
            Statement stat;
            WhileStatement(int line, bool b, Expression e, Statement s) : statement_t(line), do_while(b), condition(e), stat(s) {}
            StatementType type() override { return WHILE_STATEMENT; }
        };

        //struct FunctionDefinitionStatement : public statement_t
        //{
        //    Function func;
        //    std::tuple<StatementType, Object> execute() override;
        //};

        struct ExpressionStatement : public statement_t
        {
            Expression exp;
            ExpressionStatement(int line, Expression e) : statement_t(line), exp(e) {}
            StatementType type() override { return EXPRESSION_STATEMENT; }
        };

        struct BlockStatement : public statement_t
        {
            StatementList slist;
            BlockStatement(int line, StatementList s) : statement_t(line), slist(s) {}
            StatementType type() override { return BLOCK_STATEMENT; }
        };

        struct ReturnStatement : public statement_t
        {
            Expression exp;
            ReturnStatement(int line, Expression e) : statement_t(line), exp(e) {}
            StatementType type() override { return RETURN_STATEMENT; }
        };

        struct ContinueStatement : public statement_t
        {
            ContinueStatement(int line) : statement_t(line) {}
            StatementType type() override { return CONTINUE_STATEMENT; }
        };

        struct BreakStatement : public statement_t
        {
            BreakStatement(int line) : statement_t(line) {}
            StatementType type() override { return BREAK_STATEMENT; }
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
            void declareVariable(Identifier, ObjectType, Object, bool global = false);
            //void changeVariable(Identifier, Object, bool global = false);
            void deleteVariable(Identifier, bool global = false);
            Object &getVariable(Identifier, bool global = false);
            bool typeCheck(Object, Object);
            bool typeCheck(ObjectType, Object);
            void addGCVertex(Object);
            void delGCVertex(Object);
            void addGCEdge(object_t*, Object);
            void addGCEdge(Object, Object);
            void delGCEdge(object_t*, Object);
            void delGCEdge(Object, Object);
            void registerClass(Identifier, StatementList &);
            void registerClass(Identifier, StatementList &, IdentifierList &);
            Class findClass(Identifier);
            ObjectType findClassId(Identifier);
            std::vector<Object> resolveArgumentList(ArgumentList&);
            ParameterList ArgsToParams(std::vector<Object>&);

            class Runner
            {
                InterpreterImp *inter;
                Object temp_obj;
            public:
                Runner(InterpreterImp *i) : inter(i) {}
                StatementType interpret(StatementList &);
                StatementType execute(Statement &);
                Object &evaluate(Expression &);
            };
            //StatementType execute(const Statement &);
            //Object &evaluate(const Expression &);
            //void err();
            //void err(const std::string&);
            //int checkExist(const Identifier &);

            /*parsing time variables*/
            int level = 0;
            std::string filename;
            AccessControl current_visibility;

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