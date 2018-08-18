#ifndef NEWBIE_HPP
#define NEWBIE_HPP
#include <vector>
#include <array>
#include <string>
#include <any>
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
#include <thread>
#include <cassert>
#include <cstdint>
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
            OR,
            BIT_AND,
            BIT_OR,
            BIT_XOR,
            BIT_LEFT,
            BIT_RIGHT,
        };

        enum UnaryType
        {
            MINUS,
            PLUS,
            NEGATION,
            BIT_NOT,
        };

        using ObjectType = uint32_t;

        constexpr ObjectType NewBie_Variant = 0;
        constexpr ObjectType NewBie_Object = 1;
        constexpr ObjectType NewBie_Int = 2;
        constexpr ObjectType NewBie_Double = 3;
        constexpr ObjectType NewBie_Boolean = 4;
        constexpr ObjectType NewBie_String = 5;
        constexpr ObjectType NewBie_Function = 6;
        constexpr ObjectType NewBie_Class = 7;

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

#define NewBie_friend_declaration \
friend class InterpreterImp;\
friend class Runner;\
friend struct statement_t;\
friend struct expression_t;\
friend struct func_t;\
friend struct NativeFunction;\
friend struct NormalFunction;\
friend struct function_t;\
friend struct class_t;\
friend struct ctor_t;\
friend struct NormalConstructor;\
friend struct NativeConstructor;\
friend struct ObjectContainer;\
friend struct object_container_t;\
friend struct RAIIFunc;\
friend struct RAIIFuncName;\
friend struct RAIIScope;\
friend struct RAIIStack;\
friend struct object_t;


        /* forward declaration */
        class InterpreterImp;
        class Runner;
        struct Parameter;
        struct ParamsHash;
        struct ParamsEqualTo;
        struct statement_t;
        struct expression_t;
        struct func_t;
        struct NativeFunction;
        struct NormalFunction;
        struct function_t;
        struct class_t;
        struct ctor_t;
        struct NormalConstructor;
        struct NativeConstructor;
        struct ObjectContainer;
        struct object_container_t;
        struct object_t;
        struct StringHash;
        struct String;
        /* using statement */
        using Identifier = String;
        using IdentifierList = std::vector<Identifier>;
        using Class = std::shared_ptr<class_t>;
        using ClassMap = std::pair<std::unordered_map<Identifier, ObjectType, StringHash>, std::unordered_map<ObjectType, Class>>;
        using Func = std::shared_ptr<func_t>;
        using Function = std::shared_ptr<function_t>;
        using Expression = std::shared_ptr<expression_t>;
        using ExpressionList = std::vector<Expression>;
        using Statement = std::shared_ptr<statement_t>;
        using StatementList = std::vector<Statement>;
        using ParameterList = std::vector<Parameter>;
        using ArgumentList = std::vector<Expression>;
        using Args = std::vector<ObjectContainer>;

        struct String
        {
            std::shared_ptr<std::basic_string<char_t>> ptr;
            String();
            String(const char *);
            String(const std::string &);
            String(const char_t*);
            String(const std::basic_string<char_t>&);
            String(const String &) = default;
            ~String() = default;

            String &operator=(const String &);
            String operator+(const String &);
            String &operator+=(const String &);
            bool operator==(const String &) const;
            bool operator!=(const String &) const;
            bool operator>(const String &) const;
            bool operator>=(const String &) const;
            bool operator<(const String &) const;
            bool operator<=(const String &) const;
            std::string toStr() const;
            String copy() const;

            std::basic_string<char_t> &get() const;
        };

        const String toString_str = String("toString");
        const String object_str = String("object");
        const String int_str = String("int");
        const String double_str = String("double");
        const String boolean_str = String("boolean");
        const String string_str = String("string");
        const String function_str = String("function");
        const String class_str = String("class");
        const String true_str = String("true");
        const String false_str = String("false");
        const String for_functionCall = String("");

        struct StringHash
        {
            std::hash<std::basic_string<char_t>> h;
            std::size_t operator()(const String&) const;
        };

        using ObjectMap = std::unordered_map<Identifier, ObjectContainer, StringHash>;
        using ObjectMapA = std::unordered_map<Identifier, std::pair<ObjectContainer, AccessControl>, StringHash>;

        //assume no nullptr
        struct object_t
        {
            NewBie_friend_declaration

            ObjectContainer getVariable(Runner & runner, Identifier);
            ObjectContainer getVariableWithPrototype(Runner & runner, Identifier, bool);
            ObjectContainer getSuperVariable(Runner &, Identifier);
            ObjectContainer getSuperVariable(Runner &, ObjectType type, Identifier);

            template<typename T>
            T &useNativePointer() { return *£¨static_cast<T*>(native_ptr)); }

            ~object_t();
        private:
            object_t(Runner & r) : runner(r) {}
            object_t(Runner & r, Class cl, nullptr_t) : runner(r), cl(cl) {}
            object_t(Runner & r, Class);
            object_t(Runner & r, const int32_t &);
            object_t(Runner & r, const double &);
            object_t(Runner & r, const bool &);
            object_t(Runner & r, const std::string &);
            object_t(Runner & r, const String &);
            object_t(Runner & r, Function);
            void addVariable(Runner & runner, Identifier, ObjectContainer, AccessControl, bool cons = false);
            void addVariable(Runner & runner, Identifier, ObjectType, ObjectContainer, AccessControl, bool cons = false);
            ObjectContainer getVariableFromDerived(Runner &, Identifier); // for base expression

            Runner & runner;
            ObjectMapA local_variables;
            Identifier type_name;
            ObjectType type;
            Class cl;
            void * native_ptr = nullptr;
            std::vector<object_t *> bases;
            std::map<ObjectType, object_t *> bases_mapped;
            std::map<ObjectType, object_t *> all_bases;
        };

        struct object_container_t
        {
        private:
            object_t * belongs_to; // InterpreterImp::temp, InterpreterImp::root
            object_t * obj;
            ObjectType restrict_type = 0;
            bool is_const = false;
            object_container_t(Runner & runner);

            object_container_t(const object_container_t &) = delete;
            object_container_t(object_t * o); //temporary object
            object_container_t(ObjectType t, object_t * belongs, bool cons = false);
            object_t * get();
        public:
            NewBie_friend_declaration
            ~object_container_t();

            int32_t getInt();
            double getDouble();
            bool getBool();
            String getString();
            Function getFunction();
            Class getClass();
            bool typeCheck(object_t *);
            void set(Runner & runner, ObjectContainer);
        };
        struct ObjectContainer
        {
            NewBie_friend_declaration

            ObjectContainer(const std::shared_ptr<object_container_t> &p) : ptr(p) {}
            ObjectContainer(Runner & runner, const int32_t &i) : ptr(std::make_shared<object_container_t>(new object_t(runner, i))) {}
            ObjectContainer(Runner & runner, const double &i) : ptr(std::make_shared<object_container_t>(new object_t(runner, i))) {}
            ObjectContainer(Runner & runner, const bool &i) : ptr(std::make_shared<object_container_t>(new object_t(runner, i))) {}
            ObjectContainer(Runner & runner, Class i) : ptr(std::make_shared<object_container_t>(new object_t(runner, i))) {}
            ObjectContainer(Runner & runner, const std::string &i) : ptr(std::make_shared<object_container_t>(new object_t(runner, i))) {}
            ObjectContainer(Runner & runner, const String &i) : ptr(std::make_shared<object_container_t>(new object_t(runner, i))) {}
            ObjectContainer(Runner & runner, Function i) : ptr(std::make_shared<object_container_t>(new object_t(runner, i))) {}
            ObjectContainer(const ObjectContainer &oc) = default;
            ObjectContainer(ObjectContainer &&) = default;
            ObjectContainer(object_t * o);
            ObjectContainer& operator=(const ObjectContainer &) = default;
            ObjectContainer& operator=(ObjectContainer &&) = default;

            ObjectContainer add(Runner & runner, const ObjectContainer &); // operator +
            ObjectContainer sub(Runner & runner, const ObjectContainer &); // operator -
            ObjectContainer mul(Runner & runner, const ObjectContainer &); // operator *
            ObjectContainer div(Runner & runner, const ObjectContainer &); // operator / 
            ObjectContainer mod(Runner & runner, const ObjectContainer &); // operator %
            ObjectContainer lt(Runner & runner, const ObjectContainer &); // operator <
            ObjectContainer le(Runner & runner, const ObjectContainer &); // operator <=
            ObjectContainer gt(Runner & runner, const ObjectContainer &); // operator >
            ObjectContainer ge(Runner & runner, const ObjectContainer &); // operator >=
            ObjectContainer eq(Runner & runner, const ObjectContainer &); // operator ==
            ObjectContainer ne(Runner & runner, const ObjectContainer &); // operator !=
            ObjectContainer bit_and(Runner & runner, const ObjectContainer &); // operator &
            ObjectContainer bit_or(Runner & runner, const ObjectContainer &); // operator |
            ObjectContainer bit_xor(Runner & runner, const ObjectContainer &); // operator ^
            ObjectContainer bit_left(Runner & runner, const ObjectContainer &); // operator <<
            ObjectContainer bit_right(Runner & runner, const ObjectContainer &); // operator >>
            ObjectContainer and(Runner & runner, const ObjectContainer &); // operator &&
            ObjectContainer or(Runner & runner, const ObjectContainer &); // operator ||
            ObjectContainer minus(Runner & runner); // operator -
            ObjectContainer plus(Runner & runner); // operator +
            ObjectContainer not(Runner & runner); // operator ~
            ObjectContainer negate(Runner & runner); // operator !
            ObjectContainer index(Runner & runner, const ObjectContainer &); // operator []
            ObjectContainer call(Runner & runner, const Args &args = Args()); // operator ()
            ObjectContainer call(Runner & runner, const ArgumentList &); // operator ()
            ObjectContainer call(Runner & runner, Identifier, const Args & args = Args()) const;
            ObjectContainer call(Runner & runner, Identifier, const ArgumentList &) const;
            ObjectContainer copy(Runner & runner); // real copy the object_t
            ObjectContainer getVariable(Runner &, Identifier);
            bool toBool(Runner & runner) const;
            ~ObjectContainer() = default;
            object_container_t & operator*() const { return *ptr; }
            object_container_t * operator->() const { return ptr.operator->(); }
        private:
            ObjectContainer(Runner & runner);
            // just for creating new empty ObjectContiner
            ObjectContainer(ObjectType t, object_t * belongs, bool cons = false) : ptr(std::make_shared<object_container_t>(t, belongs, cons)) {}
            std::shared_ptr<object_container_t> ptr;
        };

        struct ctor_t
        {
            virtual std::vector<Args> & getArgs(Runner & runner) = 0;
            virtual ObjectContainer call(Runner&, object_t *, const Args &args, const ParameterList &) = 0;
        };
        struct NormalConstructor : ctor_t
        {
            NormalFunction f;
            std::vector<ArgumentList> base_args;
            std::vector<Args> & getArgs(Runner & runner);
            ObjectContainer call(Runner&, object_t *, const Args &args, const ParameterList &) override;
        };
        struct NativeConstructor : ctor_t
        {
            NativeFunction f;
            std::vector<Args> base_args;
            std::vector<Args> & getArgs(Runner & runner);
            ObjectContainer call(Runner&, object_t *, const Args &args, const ParameterList &) override;
            NativeConstructor(NativeFunction f, std::vector<Args> base_args) : f(f), base_args(base_args) {}
            NativeConstructor(ObjectType t, bool ref, std::function<ObjectContainer(Runner &, object_t *, const Args &)> func, std::vector<Args> base_args) : NativeConstructor(NativeFunction(t, ref, func), base_args) {}
        };
        using Ctor = std::shared_ptr<ctor_t>;
        struct constructor_t
        {
            bool can_overload;
            std::unordered_map<ParameterList, Ctor, ParamsHash, ParamsEqualTo> overload_map;

            using init_vec = std::vector<std::unordered_map<ParameterList,
                Ctor, ParamsHash, ParamsEqualTo>::value_type>;
            constructor_t(init_vec &);
        };
        using Constructor = std::shared_ptr<constructor_t>;
        
        enum OperatorType
        {
            o_add, o_sub, o_mul, o_div, o_mod, o_minus, o_plus, o_not, o_negate,
            o_bit_and, o_bit_or, o_bit_xor, o_bit_left, o_bit_right,
            o_and, o_or, o_le, o_lt, o_ge, o_gt, o_eq, o_ne, o_index, o_call, o_toBool
        };

        struct Operator
        {
            ObjectContainer add(Runner &, object_t *, const Args & args = Args());
            ObjectContainer sub(Runner &, object_t *, const Args & args = Args());
            ObjectContainer mul(Runner &, object_t *, const Args & args = Args());
            ObjectContainer div(Runner &, object_t *, const Args & args = Args());
            ObjectContainer mod(Runner &, object_t *, const Args & args = Args());
            ObjectContainer minus(Runner &, object_t *, const Args & args = Args());
            ObjectContainer plus(Runner &, object_t *, const Args & args = Args());
            ObjectContainer not(Runner &, object_t *, const Args & args = Args());
            ObjectContainer negate(Runner &, object_t *, const Args & args = Args());
            ObjectContainer bit_and(Runner &, object_t *, const Args & args = Args());
            ObjectContainer bit_or(Runner &, object_t *, const Args & args = Args());
            ObjectContainer bit_xor(Runner &, object_t *, const Args & args = Args());
            ObjectContainer bit_left(Runner &, object_t *, const Args & args = Args());
            ObjectContainer bit_right(Runner &, object_t *, const Args & args = Args());
            ObjectContainer and(Runner &, object_t *, const Args & args = Args());
            ObjectContainer or(Runner &, object_t *, const Args & args = Args());
            ObjectContainer lt(Runner &, object_t *, const Args & args = Args());
            ObjectContainer le(Runner &, object_t *, const Args & args = Args());
            ObjectContainer gt(Runner &, object_t *, const Args & args = Args());
            ObjectContainer ge(Runner &, object_t *, const Args & args = Args());
            ObjectContainer eq(Runner &, object_t *, const Args & args = Args());
            ObjectContainer ne(Runner &, object_t *, const Args & args = Args());
            ObjectContainer index(Runner &, object_t *, const Args & args = Args());
            ObjectContainer call(Runner &, object_t *, const Args & args = Args());
            ObjectContainer toBool(Runner &, object_t *, const Args & args = Args());
            void set(const std::vector<std::pair<int, Function>> &);
            Operator & set(int, Function);
            Operator() : o{ n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n } {}

        private:
            /*operator+, -, *, /, %, unary-, unary+, unary~, unary!,
            &, |, ^, <<, >>, &&, ||, comp, [], (), toBool*/
            static Function n;
            array<Function, 25> o;
        };
        struct class_t : std::enable_shared_from_this<class_t>
        {
            NewBie_friend_declaration

            using vars = std::vector<std::pair<Identifier, std::tuple<ObjectType, AccessControl, Expression, bool>>>;

            InterpreterImp *inter;
            Identifier type_name;
            ObjectType type;
            std::vector<Class> base_list;
            bool RAII = false;
            bool editable = false;
            bool isFinal = false;
            Constructor ctor;
            Func dtor;

            Operator o;
            ObjectMapA prototype;
            std::vector<std::pair<Identifier, std::tuple<ObjectType, AccessControl, Expression, bool>>> variables;
            std::function<void(void*)> native_deleter; // for native object
            object_t * makeObject(Runner & runner, const Args &args = Args());
            object_t * makeObjectAsBase(Runner & runner, object_t * o, const Args &args = Args()); // base object will not have a vertex in the gc graph
            ~class_t() = default;

        private:
            ObjectContainer getVariableWithPrototype(Runner & runner, Identifier, bool flag);
            void addToPrototype(Identifier, ObjectContainer, AccessControl);
            class_t(InterpreterImp *, Identifier, ObjectType, std::vector<Class> &, bool, bool, bool,
                Constructor, Func, Operator &, vars &, std::function<void(void*)>);  
        };

        struct func_t : std::enable_shared_from_this<func_t>
        {
            NewBie_friend_declaration

            virtual ~func_t() = default;
        protected:
            ObjectType return_type;
            bool ref = false;

            func_t(ObjectType return_type, bool ref) : return_type(return_type), ref(ref) {}
            virtual ObjectContainer call(Runner &, object_t *, const Args &args, const ParameterList &) = 0;
        };
        struct NormalFunction : public func_t
        {
            NewBie_friend_declaration

            Statement s;
            NormalFunction(ObjectType return_type, bool ref, Statement s) : func_t(return_type, ref), s(s) {}

        private:
            ObjectContainer call(Runner&, object_t *, const Args &args, const ParameterList &) override;
        };
        struct NativeFunction : public func_t
        {
            NewBie_friend_declaration

            std::function<ObjectContainer(Runner &, object_t *, const Args &)> native_func;
            NativeFunction(ObjectType return_type, bool ref, std::function<ObjectContainer(Runner &, object_t *, const Args &)> func) : func_t(return_type, ref), native_func(func) {}

        private:
            ObjectContainer call(Runner&, object_t *, const Args &args, const ParameterList &) override;
        };
        struct function_t
        {
            NewBie_friend_declaration
                
            friend ObjectContainer functionCall(Runner & runner, object_t * obj, const Args & args);
            using init_vec = std::vector<std::unordered_map<ParameterList,
                Func, ParamsHash, ParamsEqualTo>::value_type>;

            Identifier getName();
            ObjectContainer call(Runner &, object_t *, const Args & args = Args());
            ObjectContainer call(Runner &, object_t *, const ArgumentList & alist);

            function_t(Identifier, init_vec &);

        private:
            ObjectContainer call_f(Runner &, object_t *, const Args & args = Args());
            Identifier name;
            bool can_overload = false;
            std::unordered_map<ParameterList, Func, ParamsHash, ParamsEqualTo> overload_map;
        };

        using VariableStack = std::stack<std::vector<ObjectMap>>;
        struct RAIIStack
        {
            Runner &runner;
            RAIIStack(Runner &);
            ~RAIIStack();
        };
#define newNewBieStack() zyd2001::NewBie::RAIIStack __newbie__stack__(runner)
        struct RAIIScope
        {
            Runner &runner;
            RAIIScope(Runner &);
            ~RAIIScope();
        };
#define newNewBieScope() zyd2001::NewBie::RAIIScope __newbie__scope__(runner)
        struct RAIIFunc
        {
            Runner & runner;
            RAIIFunc(Func, Runner &, object_t *);
            ~RAIIFunc();
        };
#define useNewBieFunc(func, obj) zyd2001::NewBie::RAIIFunc __newbie__func__(func, runner, obj)

        enum ExpressionType
        {
            NULL_EXPRESSION,
            LITERAL_EXPRESSION,
            IDENTIFIER_EXPRESSION,
            BINARY_EXPRESSION,
            UNARY_EXPRESSION,
            NEW_OBJECT_EXPRESSION,
            FUNCTION_CALL_EXPRESSION,
            ARRAY_EXPRESSION,
            ARRAY_LENGTH_EXPRESSION,
            INDEX_EXPRESSION,
            THIS_EXPRESSION,
            BASE_EXPRESSION,
            DOT_EXPRESSION,
        };

        struct expression_t
        {
            expression_t() {}
            virtual ExpressionType type() = 0;
            virtual ~expression_t() = default;
        };

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
            Identifier func;
            ExpressionList alist;
            FunctionCallExpression(Identifier f, ExpressionList list) : func(f), alist(list) {}
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
            Expression exp;
            DotExpression(Expression o, Expression i) : obj(o), exp(i) {}
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
            ObjectType t;
            BaseExpression(Identifier i, ObjectType t = 0) :id(i), t(t) {}
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
            SWITCH_STATEMENT,
            FOR_STATEMENT,
            WHILE_STATEMENT,
            FOREACH_STATEMENT,
            RETURN_STATEMENT,
            CONTINUE_STATEMENT,
            BREAK_STATEMENT,
            INCREMENT_STATEMENT,
            DECREMENT_STATEMENT,
            ACCESSCONTROL_STATEMENT
        };

        struct statement_t
        {
            int lineno;
            statement_t(int line) : lineno(line) {}
            virtual StatementType type() = 0;
            virtual ~statement_t() = default;
        };

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
            bool cons;
            Identifier obj_type;
            DeclarationStatementItemList items;
            DeclarationStatement(int line, bool c, bool g, Identifier t, DeclarationStatementItemList list) : statement_t(line), cons(c), global(g), obj_type(t), items(list) {}
            StatementType type() override { return DECLARATION_STATEMENT; }
        };
        struct BuiltInDeclarationStatement : public statement_t
        {
            bool global;
            bool cons;
            ObjectType type;
            DeclarationStatementItemList items;
            BuiltInDeclarationStatement(int line, bool c, bool g, ObjectType t, DeclarationStatementItemList list) : statement_t(line), cons(c), global(g), type(t), items(list) {}
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

        struct SwitchStatement : public statement_t
        {

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

        struct Parameter
        {
            ObjectType type;
            bool ref;
            bool cons;
            Identifier identifier;
            Expression default_value_exp;
            Parameter(ObjectType type, Expression exp = Expression(), bool ref = false, bool cons = false, Identifier id = Identifier())
                : type(type), ref(ref), cons(cons), identifier(id), default_value_exp(exp) {}
        };

        ParameterList _params(std::vector<ObjectType> &);
        template<typename ... Args>
        ParameterList make_params(Args&& ...args)
        {
            _params(std::vector<ObjectType>{ std::forward<Args>(args)... });
        }

        struct ParamsHash
        {
            std::size_t operator()(const ParameterList& p) const;
        };
        struct ParamsEqualTo
        {
            bool operator()(const ParameterList& lhs, const ParameterList& rhs) const;
        };

        struct helpStruct
        {
            ObjectType type;
            std::any ptr;
            helpStruct(const int &i);
            helpStruct(const double &i);
            helpStruct(const bool &i);
            helpStruct(const String &i);
            helpStruct(const std::string &i);
        };
        ObjectContainer functionCall(Runner & runner, object_t * obj, const Args & args);
        class Runner
        {
            NewBie_friend_declaration
            friend ObjectContainer functionCall(Runner & runner, object_t * obj, const Args & args);

            InterpreterImp * inter;
            ObjectContainer temp_obj;
            VariableStack variable_stack;
            ObjectMap * current_obj_map;

            //for function call
            ObjectType return_type;
            bool ref;

            //call stack
            std::stack<std::pair<Func, object_t *>> call_stack_func;
            object_t * this_ptr;

            ObjectContainer addRefVariable(Identifier, ObjectContainer);
            Expression _m_exp(helpStruct h);
            Args _makeArgs(const std::vector<helpStruct> &);
        public:
            const ObjectContainer nullObj;

            Runner(InterpreterImp *i) : inter(i), temp_obj(*this), nullObj(*i->null_obj) {}
            Args resolveArgumentList(const ArgumentList &);
            ParameterList argsToParams(const Args &);
            ObjectContainer makeDefaultObject(ObjectType t);
            ObjectContainer getVariable(Identifier); // will also get global variable
            ObjectContainer getGlobalVariable(Identifier); // only get global variabl
            ObjectContainer addGlobalVariable(Identifier, ObjectContainer, bool cons = false);
            ObjectContainer addGlobalVariable(Identifier, ObjectType, ObjectContainer, bool cons = false);
            ObjectContainer addVariable(Identifier, ObjectType, ObjectContainer, bool cons = false);
            ObjectContainer addVariable(Identifier, ObjectContainer, bool cons = false);
            InterpreterImp * getInter() const { return inter; }
            void interpret(const StatementList &);
            StatementType execute(const Statement &);
            ObjectContainer evaluate(const Expression &);
            ObjectContainer returnVal();
            void operator()();

            template<typename... Val>
            ObjectContainer call(Function f, Val&& ...val)
            {
                return f->call(*this, makeArgs(std::forward<Val>(val)...));
            }
            template<typename... Val>
            Args makeArgs(Val&& ...val)
            {
                return _makeArgs(std::vector<helpStruct>{ std::forward<Val>(val)... });
            }

            template<typename Val>
            Expression m_exp(Val&& val)
            {
                return m_exp(helpStruct(val));
            }
        };

        class InterpreterImp
        {
        public:
            NewBie_friend_declaration

            /* public api */
            InterpreterImp();
            InterpreterImp(const std::string &name);
            InterpreterImp(const InterpreterImp &) = delete;
            ~InterpreterImp();
            void parse();
            bool run();
            bool setFile(const std::string &name);
            bool changeSetting(const std::string &, int);
            void performGC();
            void GC();
            void concurrentGC();
            void addGCVertex(object_t *);
            void delGCVertex(object_t *);
            void addGCEdge(object_t *, object_t *);
            void delGCEdge(object_t *, object_t *);
            bool typeCheck(ObjectType, object_t *);
            Class findClass(Identifier);
            Class findClass(ObjectType);
            ObjectType findClassId(Identifier);
            void registerClass(Identifier type_name, std::vector<ObjectType> & base, bool, bool, bool,
                Constructor ctor, Func dtor, Operator & o, class_t::vars & variables, std::function<void(void*)> native_deleter);
            void registerClass(Identifier type_name, std::vector<Identifier> & base, bool, bool, bool,
                Constructor ctor, Func dtor, Operator & o, class_t::vars & variables, std::function<void(void*)> native_deleter);

            /*parsing time variables*/
            int level = 0;
            std::string filename;
            AccessControl current_visibility;

            /*runtime variables*/
            std::unique_ptr<Runner> runner; //main runner
            object_t * root;
            object_t * null;
            ObjectContainer * null_obj;
            object_t * temp;
            ObjectMap * global_object_map;
            int current_lineno;
            long class_count = 0;
            DirectedGraphM<object_t *> gc_graph;
            std::array<Class, 8> primitive_class;

            StatementList statement_list;
            VariableStack variable_stack;
            ClassMap class_map;
            ObjectType class_count = 8;
            std::vector<std::unique_ptr<void *>> handle_list;
            std::unordered_map<std::string, int> settings;

        private:
            Class makeObjectClass();
            Class makeIntClass();
            Class makeDoubleClass();
            Class makeBooleanClass();
            Class makeStringClass();
            Class makeFunctionClass();
            Class makeClassClass();

            Func nullFunc;
            Function nFunc;
        };
    }
}

#endif