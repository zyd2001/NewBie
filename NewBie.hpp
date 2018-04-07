#ifndef NEWBIE_HPP
#define NEWBIE_HPP
#include <vector>
#include <array>
#include <string>
#include <map>
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
        //0 => null
        //1 => variant
        //2 => int
        //3 => double
        //4 => boolean
        //5 => string
        //6 => function
        //7 => class

        enum AccessControl
        {
            PUBLIC,
            PROTECTED,
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
            String(const std::string &);
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

        using ObjectMap = std::unordered_map<Identifier, ObjectContainer, Identifier::hash>;
        struct MapItem
        {
            ObjectContainer o;
            AccessControl visibility;
        };
        using ObjectMapA = std::unordered_map<Identifier, MapItem, Identifier::hash>;
        struct object_t
        {
            friend class object_container_t;
            friend class NormalClass;
            friend class NativeClass;
            friend class InterpreterImp;

            object_t(InterpreterImp *inter, Class c) : type_name(c->type_name), type(c->type), cl(c) {}
            object_t(InterpreterImp *inter, const int &);
            object_t(InterpreterImp *inter, const double &);
            object_t(InterpreterImp *inter, const bool &);
            object_t(InterpreterImp *inter, std::string &);
            object_t(InterpreterImp *inter, const String &);

            static object_t * makeInt(InterpreterImp *inter, const int &);

            void addVariable(Identifier, object_t *, AccessControl);
            void addVariable(Identifier, ObjectType, object_t *, AccessControl);
            void addVariable(Identifier, ObjectType, AccessControl); //may cause nullptr error
            ObjectContainer getVariable(InterpreterImp::Runner &, Identifier);
            ObjectContainer getSuperVariable(InterpreterImp::Runner &, Identifier);
            ObjectContainer getSuperVariable(InterpreterImp::Runner &, ObjectType type, Identifier);

            template<typename T>
            T &useNativePointer() { return *static_cast<T*>(native_ptr); }
            void *native_ptr = nullptr;

            ~object_t();
        private:
            object_t() {}
            ObjectContainer getVariableFromDerived(InterpreterImp::Runner &, Identifier);

            InterpreterImp * inter;
            ObjectMapA local_variables;
            Identifier type_name;
            ObjectType type;
            std::shared_ptr<class_t> cl;
            int ref_count = 0; //for reference by RAII object
            std::vector<object_t *> bases;
            std::map<ObjectType, object_t *> bases_mapped;
            std::map<ObjectType, object_t *> all_bases;
        };

        struct object_container_t
        {
        private:
            object_t * belongs_to = nullptr;
            object_t * obj = nullptr;
            ObjectType restrict_type = 0;
            bool isConst;
            //void set(InterpreterImp::Runner &runner, object_t * o);
        public:
            friend class class_t;
            friend class object_t;
            friend class InterpreterImp::Runner;
            friend class InterpreterImp;

            object_container_t() {}
            object_container_t(object_t * o) : obj(o), isConst(true), belongs_to(&InterpreterImp::root)
            {
                o->inter->addGCEdge(&InterpreterImp::root, obj);
            } //temp container
            object_container_t(const object_container_t &o, object_t * belongs) : belongs_to(belongs), obj(o.obj), restrict_type(o.restrict_type), isConst(o.isConst)
            {
                if (belongs_to != nullptr)
                    belongs_to->inter->addGCEdge(belongs_to, obj);
            }
            object_container_t(ObjectType t, object_t * belongs, bool cons = false) : restrict_type(t), belongs_to(belongs), isConst(cons) {}
            object_container_t(object_t * o, object_t * belongs, bool cons = false) : obj(o), restrict_type(o->cl->type), belongs_to(belongs), isConst(cons)
            {
                if (belongs_to != nullptr)
                    belongs_to->inter->addGCEdge(belongs_to, obj);
            }
            bool typeCheck(object_t *);
            void set(InterpreterImp::Runner &runner, ObjectContainer);
            object_t * get();
            ObjectContainer copy(object_t * belongs) { return make_shared<object_container_t>(*this, belongs); }
            ~object_container_t()
            {
                if (obj != nullptr)
                {
                    if (obj->cl->RAII)
                        delete obj;
                    if (belongs_to != nullptr)
                        if (belongs_to == &InterpreterImp::temp)
                            obj->inter->delGCEdge(&InterpreterImp::root, obj);
                        else
                            belongs_to->inter->delGCEdge(belongs_to, obj);
                }
            }
        };
        using ObjectContainer = std::shared_ptr<object_container_t>;
#define B(o) bool(*o)
/*make temp Object Container*/
#define OContainer(o) std::make_shared<object_container_t>(o)

        using IdentifierList = std::vector<Identifier>;

        struct ctorArgs
        {
            ObjectType type;
            ArgumentList args;
        };
        using ctorArgsList = std::vector<ctorArgs>;
        struct ctor
        {
            Statement stat;
            std::vector<ArgumentList> base_args;
        };
        struct constructor_t
        {
            bool can_overload;
            std::unordered_map<ParameterList, ctor, ParamsHash> overload_map;
        };
        using Constructor = std::unique_ptr<constructor_t>;

        struct class_t
        {
            friend class object_t;
            friend class InterpreterImp;

            InterpreterImp *inter;
            Identifier type_name;
            ObjectType type;
            std::vector<Class> base_list;
            bool RAII = false;
            Constructor ctor;
            std::shared_ptr<function_t> dtor;
            std::shared_ptr<function_t> copy_ctor;
            std::array<Function, 10> o; //operator+, -, *, /, %, unary-, toBool, comp, [], ()
            //std::function<object_t *(const object_t * &)> native_copyer = [](const object_t * &) -> object_t * {};
            //std::function<void(void*)> native_deleter = [](void*) {};
            virtual object_t * makeObject(InterpreterImp::Runner &, ArgumentList&) = 0;
            virtual object_t * makeObjectAsBase(InterpreterImp::Runner &, ArgumentList&, object_t *) = 0;
            void addStaticVariable(Identifier, object_t *, AccessControl);
            ObjectContainer getStaticVariable(Identifier);
            virtual ~class_t() = default;
        private:
            ObjectMapA static_variables;
        };
        struct NormalClass : public class_t
        {
            std::unordered_map<Identifier, std::tuple<ObjectType, AccessControl, Expression>, Identifier::hash> variables;
            object_t * makeObject(InterpreterImp::Runner &, ArgumentList&) override;
            object_t * makeObjectAsBase(InterpreterImp::Runner &, ArgumentList&, object_t *) override;
        };
        struct NativeClass : public class_t
        {
            std::function<void(std::vector<ObjectContainer>&, object_t *)> real;
            object_t * makeObject(InterpreterImp::Runner &, ArgumentList&) override;
            object_t * makeObjectAsBase(InterpreterImp::Runner &, ArgumentList&, object_t *) override;
            NativeClass(Identifier name, bool R, Function dtor, Function copy, )
        };
        using Class = std::shared_ptr<class_t>;
        using ClassMap = std::pair<std::unordered_map<Identifier, ObjectType, Identifier::hash>, std::unordered_map<ObjectType, Class>>;

        struct function_t
        {
            friend class InterpreterImp::Runner;
            bool can_overload = true;
            virtual ObjectContainer call(InterpreterImp::Runner&, ArgumentList&) = 0;
            virtual ~function_t() = default;
        private:
            InterpreterImp *inter;
            ObjectType return_type;

            //class or obj the function belongs to
            object_t * obj;
            Class cl;
        };
        struct NormalFunction : public function_t
        {
            std::unordered_map<ParameterList, Statement, ParamsHash, ParamsEqualTo> overload_map;
            ObjectContainer call(InterpreterImp::Runner&, ArgumentList&) override;
            ObjectContainer real_call(InterpreterImp::Runner&, ArgumentList&);
        };
        struct NativeFunction : public function_t
        {
            std::unordered_map<ParameterList, std::function<object_t *(InterpreterImp::Runner &, std::vector<ObjectContainer>&, object_t *)>, ParamsHash, ParamsEqualTo> native_func;
            ObjectContainer call(InterpreterImp::Runner&, ArgumentList&) override;
        };
        struct NativeStaticFunction : public function_t
        {
            std::unordered_map<ParameterList, std::function<object_t *(InterpreterImp::Runner &, std::vector<ObjectContainer>&, class_t*)>, ParamsHash, ParamsEqualTo> native_func;
            ObjectContainer call(InterpreterImp::Runner&, ArgumentList&) override;
        };
        using Function = std::shared_ptr<function_t>;

        using VariableStack = std::stack<std::vector<ObjectMap>>;
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
            RAIIObject(object_t *, InterpreterImp *inter);
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
            BASE_EXPRESSION,
            DOT_EXPRESSION,
            NEW_OBJECT_EXPRESSION
        };

        //struct Expression
        //{
        //    ExpressionType type;
        //    void *content;
        //    int *ref_count;

        //    Expression();
        //    Expression(object_t *);
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
            expression_t() {}
            virtual ExpressionType type() = 0;
            virtual ~expression_t() = default;
        };
        using Expression = std::shared_ptr<expression_t>;
        using ExpressionList = ArrayExpression;

        struct IdentifierExpression : public expression_t
        {
            Identifier id;
            IdentifierExpression(Identifier i) : id(i) {}
            ExpressionType type() override { return IDENTIFIER_EXPRESSION; }
        };

        struct LiteralExpression : public expression_t
        {
            ObjectContainer obj;
            LiteralExpression(ObjectContainer o) : obj(o) {}
            ExpressionType type() override { return LITERAL_EXPRESSION; }
        };

        struct ArrayExpression : public expression_t
        {
            ExpressionList list;
            ExpressionType type() override { return ARRAY_EXPRESSION; }
        };

        struct BinaryExpression : public expression_t
        {
            BinaryType ty;
            Expression lexp;
            Expression rexp;
            BinaryExpression(BinaryType t, Expression l, Expression r) : ty(t), lexp(l), rexp(r) {}
            ExpressionType type() override { return BINARY_EXPRESSION; }
        };

        struct UnaryExpression : public expression_t
        {
            UnaryType ty;
            Expression exp;
            UnaryExpression(UnaryType t, Expression e) : ty(t), exp(e) {}
            ExpressionType type() override { return UNARY_EXPRESSION; }
        };

        struct FunctionCallExpression : public expression_t
        {
            Expression func;
            ExpressionList alist;
            FunctionCallExpression(Expression f, ExpressionList list) : func(f), alist(list) {}
            ExpressionType type() override { return FUNCTION_CALL_EXPRESSION; }
        };

        struct NewObjectExpression : public expression_t
        {
            Identifier id;
            ExpressionList alist;
            NewObjectExpression(Identifier i, ExpressionList list) : id(i), alist(list) {}
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
            DotExpression(Expression o, Identifier i) : obj(o), id(i) {}
            ExpressionType type() override { return DOT_EXPRESSION; }
        };

        struct ThisExpression : public expression_t
        {
            ThisExpression() {}
            ExpressionType type() override { return THIS_EXPRESSION; }
        };

        struct BaseExpression : public expression_t
        {
            Identifier id;
            ObjectType type;
            BaseExpression(Identifier i, ObjectType t = 0) :id(i), type(t) {}
            ExpressionType type() override { return BASE_EXPRESSION; }
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
        //    std::tuple<StatementType, object_t *> execute() override;
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
#define makeStatement(type, ...) std::make_shared<type>(yyget_lineno(scanner), __VA_ARGS__)
#define makeExpression(type, ...) std::make_shared<type>(__VA_ARGS__)
        inline Expression makeArgument(object_t * o)
        {
            return std::make_shared<LiteralExpression>(OContainer(o));
        }
        inline Expression makeArgument(ObjectContainer o)
        {
            return std::make_shared<LiteralExpression>(o);
        }

        struct Parameter
        {
            ObjectType type;
            bool ref;
            Identifier identifier;
            Expression default_value_exp; //only object_t *
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
            void declareVariable(Identifier, ObjectType, object_t *, bool global = false);
            //void changeVariable(Identifier, object_t *, bool global = false);
            void deleteVariable(Identifier, bool global = false);
            ObjectContainer getVariable(Identifier, bool global = false);
            void addGCVertex(object_t *);
            void delGCVertex(object_t *);
            void addGCEdge(object_t *, object_t *);
            void delGCEdge(object_t *, object_t *);
            void registerClass(Class, IdentifierList&);
            void registerClass(Identifier, StatementList &);
            void registerClass(Identifier, StatementList &, IdentifierList &);
            Class findClass(Identifier);
            ObjectType findClassId(Identifier);

            class Runner
            {
                InterpreterImp *inter;
                object_t * current_object;
                ObjectContainer temp_obj;
                VariableStack variable_stack;

                //support "static"
                bool in_class = false;
                class_t* current_class;
                std::stack<class_t*> class_env_stack;
                //support "this" expression
                bool in_object = false;
                object_t * current_object;
                std::stack<object_t *> object_env_stack;

            public:
                friend class object_t;

                Runner(InterpreterImp *i) : inter(i) {}
                std::vector<ObjectContainer> resolveArgumentList(ArgumentList&, ParameterList &);
                static ParameterList ArgsToParams(std::vector<ObjectContainer>&);
                InterpreterImp * getInter() { return inter; }
                StatementType interpret(StatementList &);
                StatementType execute(Statement &);
                ObjectContainer evaluate(Expression &);
                object_t * call(Statement, std::vector<ObjectContainer> &);
                object_t * call(Function);
            };
            //StatementType execute(const Statement &);
            //object_t * &evaluate(const Expression &);
            //void err();
            //void err(const std::string&);
            //int checkExist(const Identifier &);

            /*parsing time variables*/
            int level = 0;
            std::string filename;
            AccessControl current_visibility;

            /*runtime variables*/
            static object_t root;
            static object_t null;
            static object_t temp;
            int current_lineno;
            long class_count = 0;
            DirectedGraphM<object_t *> gc_graph;
            ObjectMap *current_variables;
            std::array<Class, 5> primitive_class;

            //for return value
            //object_t * temp_variable;

            //global scope
            ObjectMap global_variables;

            StatementList statement_list;
            VariableStack variable_stack;
            ClassMap class_map;
            std::vector<std::unique_ptr<void *>> handle_list;
            std::unordered_map<std::string, int> settings;
        };
    }
}

#endif