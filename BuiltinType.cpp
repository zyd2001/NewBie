#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

#include <codecvt>
#include <locale>
#include <sstream>

using namespace std;

namespace zyd2001
{
    namespace NewBie
    {
        wstring_convert<codecvt_utf8<char_t>, char_t> conv;

        int32_t zyd2001::NewBie::object_container_t::getInt()
        {
            return obj->useNativePointer<int32_t>();
        }

        double zyd2001::NewBie::object_container_t::getDouble()
        {
            return obj->useNativePointer<double>();
        }

        bool zyd2001::NewBie::object_container_t::getBool()
        {
            return obj->useNativePointer<bool>();
        }

        String zyd2001::NewBie::object_container_t::getString()
        {
            return obj->useNativePointer<String>();
        }

        Function object_container_t::getFunction()
        {
            return obj->useNativePointer<Function>();
        }

        Class object_container_t::getClass()
        {
            return obj->useNativePointer<Class>();
        }

        ObjectContainer objectToString(Runner &runner, object_t * obj, const Args & args)
        {
            return ObjectContainer(runner, object_str);
        }

#define intBiOp(name, op)\
ObjectContainer int ## name (Runner &runner, object_t * obj, const Args & args)\
{\
    int32_t &i1 = obj->useNativePointer<int32_t>();\
    int32_t i2 = args[0]->getInt();\
    return ObjectContainer(runner, i1 op i2);\
}
        intBiOp(Add, +)
            intBiOp(Sub, -)
            intBiOp(Mul, *)
            intBiOp(Div, / )
            intBiOp(Mod, %)
            intBiOp(Lt, <)
            intBiOp(Le, <= )
            intBiOp(Gt, > )
            intBiOp(Ge, >= )
            intBiOp(Eq, == )
            intBiOp(Ne, !=)
            intBiOp(BitAnd, &)
            intBiOp(BitOr, | )
            intBiOp(BitXor, ^)
            intBiOp(BitLeft, << )
            intBiOp(BitRight, >>)
#define intBiOpD(name, op)\
ObjectContainer int ## name ## D (Runner &runner, object_t * obj, const Args & args)\
{\
    int32_t &i = obj->useNativePointer<int32_t>();\
    double d = args[0]->getDouble();\
    return ObjectContainer(runner, i op d);\
}
            intBiOpD(Add, +)
            intBiOpD(Sub, -)
            intBiOpD(Mul, *)
            intBiOpD(Div, / )
            intBiOpD(Lt, <)
            intBiOpD(Le, <= )
            intBiOpD(Gt, >)
            intBiOpD(Ge, >= )
            intBiOpD(Eq, == )
            intBiOpD(Ne, != )
        ObjectContainer intMinus(Runner &runner, object_t * obj, const Args & args)
        {//int
            int32_t &i = obj->useNativePointer<int32_t>();
            return ObjectContainer(runner, -i);
        }
        ObjectContainer intPlus(Runner &runner, object_t * obj, const Args & args)
        {//int
            int32_t &i = obj->useNativePointer<int32_t>();
            return ObjectContainer(runner, +i);
        }
        ObjectContainer intNegate(Runner &runner, object_t * obj, const Args & args)
        {//int
            int32_t &i = obj->useNativePointer<int32_t>();
            return ObjectContainer(runner, !i);
        }
        ObjectContainer intNot(Runner &runner, object_t * obj, const Args & args)
        {//int
            int32_t &i = obj->useNativePointer<int32_t>();
            return ObjectContainer(runner, ~i);
        }
        ObjectContainer intCalli(Runner &runner, object_t * obj, const Args & args)
        {//int, int
            int32_t &i = obj->useNativePointer<int32_t>();
            int32_t arg = args[0]->getInt();
            return ObjectContainer(runner, i * arg);
        }
        ObjectContainer intCalld(Runner &runner, object_t * obj, const Args & args)
        {//int, double
            int32_t &i = obj->useNativePointer<int32_t>();
            double arg = args[0]->getDouble();
            return ObjectContainer(runner, i * arg);
        }
        ObjectContainer intToBool(Runner &runner, object_t * obj, const Args & args)
        {//int32_t
            int32_t &i = obj->useNativePointer<int32_t>();
            return ObjectContainer(runner, bool(i));
        }
        ObjectContainer intToString(Runner &runner, object_t * obj, const Args & args)
        {//int32_t
            int32_t &i = obj->useNativePointer<int32_t>();
            return ObjectContainer(runner, std::to_string(i));
        }
        ObjectContainer intCtorD(Runner & runner, object_t * obj, const Args & args)
        {
            int32_t &i = obj->useNativePointer<int32_t>();
            double num = args[0]->getDouble();
            i = num;
            return runner.nullObj;
        }
        ObjectContainer intCtorStr(Runner & runner, object_t * obj, const Args & args)
        {
            int32_t &i = obj->useNativePointer<int32_t>();
            String s = args[0]->getString();
            long num = stol(s.toStr()); // long is at least 32 bit
            if (sizeof(long) > sizeof(int32_t))
                if (num > INT32_MAX || num < INT32_MIN)
                    throw out_of_range("out of range");
            i = static_cast<int32_t>(num);
            return runner.nullObj;
        }
        ObjectContainer intCtorBool(Runner & runner, object_t * obj, const Args & args)
        {
            int32_t &i = obj->useNativePointer<int32_t>();
            bool b = args[0]->getBool();
            i = b ? 1 : 0;
            return runner.nullObj;
        }
        ObjectContainer intCtor(Runner & runner, object_t * obj, const Args & args)
        {
            int32_t &i = obj->useNativePointer<int32_t>();
            i = 0;
            return runner.nullObj;
        }
        ObjectContainer intCopy(Runner &runner, object_t * obj, const Args & args)
        {
            int32_t &i = obj->useNativePointer<int32_t>();
            int32_t num = args[0]->getInt();
            i = num;
            return runner.nullObj;
        }
        void intPtrDeleter(void * i)
        {
            delete static_cast<int32_t*>(i);
        }

#define doubleBiOp(name, op) \
ObjectContainer double ## name (Runner &runner, object_t * obj, const Args & args)\
{\
    double &i1 = obj->useNativePointer<double>();\
    double i2 = args[0]->getDouble();\
    return ObjectContainer(runner, i1 op i2);\
}
        doubleBiOp(Add, +)
            doubleBiOp(Sub, -)
            doubleBiOp(Mul, *)
            doubleBiOp(Div, / )
            doubleBiOp(Lt, <)
            doubleBiOp(Le, <= )
            doubleBiOp(Gt, >)
            doubleBiOp(Ge, >= )
            doubleBiOp(Eq, == )
            doubleBiOp(Ne, != )
#define doubleBiOpI(name, op)\
ObjectContainer double ## name ## I(Runner &runner, object_t * obj, const Args & args)\
{\
    double &i1 = obj->useNativePointer<double>();\
    int32_t i2 = args[0]->getInt();\
    return ObjectContainer(runner, i1 op i2);\
}
            doubleBiOpI(Add, +)
            doubleBiOpI(Sub, -)
            doubleBiOpI(Mul, *)
            doubleBiOpI(Div, / )
            doubleBiOpI(Lt, <)
            doubleBiOpI(Le, <= )
            doubleBiOpI(Gt, >)
            doubleBiOpI(Ge, >= )
            doubleBiOpI(Eq, == )
            doubleBiOpI(Ne, != )
        ObjectContainer doubleMinus(Runner &runner, object_t * obj, const Args & args)
        {//double
            double &i = obj->useNativePointer<double>();
            return ObjectContainer(runner, -i);
        }
        ObjectContainer doublePlus(Runner &runner, object_t * obj, const Args & args)
        {//double
            double &i = obj->useNativePointer<double>();
            return ObjectContainer(runner, +i);
        }
        ObjectContainer doubleNegate(Runner &runner, object_t * obj, const Args & args)
        {//double
            double &i = obj->useNativePointer<double>();
            return ObjectContainer(runner, !i);
        }
        ObjectContainer doubleCalli(Runner &runner, object_t * obj, const Args & args)
        {//double, int32_t
            double &d = obj->useNativePointer<double>();
            int32_t i = args[0]->getInt();
            return ObjectContainer(runner, i * d);
        }
        ObjectContainer doubleCalld(Runner &runner, object_t * obj, const Args & args)
        {//double, double
            double &d = obj->useNativePointer<double>();
            double i = args[0]->getDouble();
            return ObjectContainer(runner, i * d);
        }
        ObjectContainer doubleToBool(Runner &runner, object_t * obj, const Args & args)
        {//double
            double &i = obj->useNativePointer<double>();
            return ObjectContainer(runner, bool(i));
        }
        ObjectContainer doubleToString(Runner &runner, object_t * obj, const Args & args)
        {//double
            double &i = obj->useNativePointer<double>();
            return ObjectContainer(runner, std::to_string(i));
        }
        ObjectContainer doubleCtor(Runner &runner, object_t * obj, const Args & args)
        {
            double &i = obj->useNativePointer<double>();
            i = 0;
            return runner.nullObj;
        }
        ObjectContainer doubleCtorI(Runner &runner, object_t * obj, const Args & args)
        {
            double &i = obj->useNativePointer<double>();
            int32_t num = args[0]->getInt();
            i = num;
            return runner.nullObj;
        }
        ObjectContainer doubleCtorStr(Runner &runner, object_t * obj, const Args & args)
        {
            double &i = obj->useNativePointer<double>();
            String num = args[0]->getString();
            i = stod(num.toStr());
            return runner.nullObj;
        }
        ObjectContainer doubleCopy(Runner &runner, object_t * obj, const Args & args)
        {//double
            double &i = obj->useNativePointer<double>();
            double num = args[0]->getDouble();
            i = num;
            return runner.nullObj;
        }
        void doublePtrDeleter(void * i)
        {
            delete static_cast<double*>(i);
        }
        
        ObjectContainer booleanEq(Runner & runner, object_t * obj, const Args & args)
        {
            bool &b1 = obj->useNativePointer<bool>();
            bool b2 = args[0]->getBool();
            return ObjectContainer(runner, b1 == b2);
        }
        ObjectContainer booleanNe(Runner & runner, object_t * obj, const Args & args)
        {
            bool &b1 = obj->useNativePointer<bool>();
            bool b2 = args[0]->getBool();
            return ObjectContainer(runner, b1 != b2);
        }
        ObjectContainer booleanNegate(Runner & runner, object_t * obj, const Args & args)
        {
            bool &b = obj->useNativePointer<bool>();
            return ObjectContainer(runner, !b);
        }
        ObjectContainer booleanAnd(Runner & runner, object_t * obj, const Args & args)
        {
            bool &b1 = obj->useNativePointer<bool>();
            bool b2 = args[0]->getBool();
            return ObjectContainer(runner, b1 && b2);
        }
        ObjectContainer booleanOr(Runner & runner, object_t * obj, const Args & args)
        {
            bool &b1 = obj->useNativePointer<bool>();
            bool b2 = args[0]->getBool();
            return ObjectContainer(runner, b1 || b2);
        }
        ObjectContainer booleanToString(Runner &runner, object_t * obj, const Args & args)
        {//bool
            bool &i = obj->useNativePointer<bool>();
            if (i)
                return ObjectContainer(runner, true_str);
            else
                return ObjectContainer(runner, false_str);
        }
        ObjectContainer booleanCtor(Runner &runner, object_t * obj, const Args & args)
        {//bool
            bool &i = obj->useNativePointer<bool>();
            i = false;
            return runner.nullObj;
        }
        ObjectContainer booleanCopy(Runner &runner, object_t * obj, const Args & args)
        {//bool
            bool &i = obj->useNativePointer<bool>();
            bool b = args[0]->getBool();
            i = b;
            return runner.nullObj;
        }
        void booleanPtrDeleter(void * i)
        {
            delete static_cast<bool*>(i);
        }

        ObjectContainer stringAdd(Runner &runner, object_t * obj, const Args & args)
        {//string, string
            String &s1 = obj->useNativePointer<String>();
            String s2 = args[0].call(runner, toString_str)->getString();
            return ObjectContainer(runner, s1 + s2);
        }
        ObjectContainer stringMul(Runner &runner, object_t * obj, const Args & args)
        {//string, string
            String &s = obj->useNativePointer<String>();
            int32_t i = args[0]->getInt();
            std::basic_ostringstream<char_t> os;
            for (int32_t j = 0; j < i; j++)
                os << s.get();
            return ObjectContainer(runner, os.str());
        }
#define stringComp(name, op) \
ObjectContainer string ## name (Runner &runner, object_t * obj, const Args & args)\
{\
    String &s1 = obj->useNativePointer<String>();\
    String s2 = args[0]->getString();\
    return ObjectContainer(runner, s1 op s2);\
}
        stringComp(Lt, <)
        stringComp(Le, <= )
        stringComp(Gt, >)
        stringComp(Ge, >= )
        stringComp(Eq, == )
        stringComp(Ne, != )
        ObjectContainer stringToBool(Runner &runner, object_t * obj, const Args & args)
        {//string
            String &s = obj->useNativePointer<String>();
            return ObjectContainer(runner, !s.get().empty());
        }
        ObjectContainer stringToString(Runner &runner, object_t * obj, const Args & args)
        {//string
            String &s = obj->useNativePointer<String>();
            return ObjectContainer(runner, s);
        }
        ObjectContainer stringIndex(Runner &runner, object_t * obj, const Args & args)
        {
            String & s = obj->useNativePointer<String>();
            int32_t i = args[0]->getInt();
            return ObjectContainer(runner, s.ptr->substr(i, 1));
        }
        ObjectContainer stringSubstring(Runner &runner, object_t * obj, const Args & args)
        {
            String & s = obj->useNativePointer<String>();
            int32_t i1 = args[0]->getInt();
            int32_t i2 = args[1]->getInt();
            if (i2 == -1)
                return ObjectContainer(runner, s.ptr->substr(i1));
            else
                return ObjectContainer(runner, s.ptr->substr(i1, i1 + i2));
        }
        ObjectContainer stringSubstr(Runner &runner, object_t * obj, const Args & args)
        {
            String & s = obj->useNativePointer<String>();
            int32_t i1 = args[0]->getInt();
            int32_t i2 = args[1]->getInt();
            if (i2 == -1)
                return ObjectContainer(runner, s.ptr->substr(i1));
            else
                return ObjectContainer(runner, s.ptr->substr(i1, i2));
        }
        ObjectContainer stringCopy(Runner &runner, object_t * obj, const Args & args)
        {//string
            String & s = obj->useNativePointer<String>();
            String s1 = args[0]->getString();
            s = s1;
            return runner.nullObj;
        }
        ObjectContainer stringCtor(Runner &runner, object_t * obj, const Args & args)
        {//string
            String & s = obj->useNativePointer<String>();
            s = String();
            return runner.nullObj;
        }
        void stringPtrDeleter(void * p)
        {
            delete static_cast<String*>(p);
        }

        ObjectContainer functionEq(Runner & runner, object_t * obj, const Args & args)
        {
            Function & f = obj->useNativePointer<Function>();
            Function f1 = args[0]->getFunction();
            return ObjectContainer(runner, f == f1);
        }
        ObjectContainer functionNe(Runner & runner, object_t * obj, const Args & args)
        {
            Function & f = obj->useNativePointer<Function>();
            Function f1 = args[0]->getFunction();
            return ObjectContainer(runner, f != f1);
        }
        ObjectContainer functionCall(Runner & runner, object_t * obj, const Args & args)
        {
            Function & f = obj->useNativePointer<Function>();
            object_t * this_ptr = runner.this_ptr;
            runner.this_ptr = runner.inter->root;
            return f->call_f(runner, this_ptr, args); // change the call_func_stack
        }
        ObjectContainer functionToString(Runner & runner, object_t * obj, const Args & args)
        {
            return ObjectContainer(runner, String("function ") + obj->useNativePointer<Function>()->getName());
        }
        ObjectContainer functionCopy(Runner & runner, object_t * obj, const Args & args)
        {
            Function & f = obj->useNativePointer<Function>();
            Function f1 = args[0]->getFunction();
            f = f1;
            return runner.nullObj;
        }
        void functionPtrDeleter(void * p)
        {
            delete static_cast<Function*>(p);
        }

        ObjectContainer classEq(Runner & runner, object_t * obj, const Args & args)
        {
            Class & f = obj->useNativePointer<Class>();
            Class f1 = args[0]->getClass();
            return ObjectContainer(runner, f == f1);
        }
        ObjectContainer classNe(Runner & runner, object_t * obj, const Args & args)
        {
            Class & f = obj->useNativePointer<Class>();
            Class f1 = args[0]->getClass();
            return ObjectContainer(runner, f != f1);
        }
        ObjectContainer classCall(Runner & runner, object_t * obj, const Args & args)
        {
            Class & cl = obj->useNativePointer<Class>();
            return cl->makeObject(runner, args);
        }
        ObjectContainer classToString(Runner & runner, object_t * obj, const Args & args)
        {
            Class & cl = obj->useNativePointer<Class>();
            return ObjectContainer(runner, String("class ") + cl->type_name);
        }
        ObjectContainer classCopy(Runner & runner, object_t * obj, const Args & args)
        {
            Class & f = obj->useNativePointer<Class>();
            Class f1 = args[0]->getClass();
            f = f1;
            return runner.nullObj;
        }
        void classPtrDeleter(void * p)
        {
            delete static_cast<Class*>(p);
        }

        Class InterpreterImp::makeObjectClass()
        {
            vector<Class> bases;
            
            Function toString = make_shared<function_t>(toString_str, function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_String, false, objectToString))
                });
            Operator o;
            Func dtor = nullFunc;
            Constructor ctor = make_shared<constructor_t>(constructor_t::init_vec{
                make_pair(make_params(), make_shared<NativeConstructor>(NewBie_Variant, true, [&](Runner & runner, object_t * obj, const Args & args) { return *null_obj; }, Args{})),
                });
            Class cl = make_shared<class_t>(this, int_str, NewBie_Int, bases, false, false, false, ctor, dtor, o, class_t::vars(), [](void*) {});
            cl->addToPrototype(toString_str, ObjectContainer(*runner, toString), PUBLIC);
            return cl;
        }

        Class InterpreterImp::makeIntClass()
        {
            vector<Class> bases{ primitive_class[NewBie_Object] };
            Function add = make_shared<function_t>(String("int operator+"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Int, false, intAdd)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Int, false, intAddD)),
                });
            Function sub = make_shared<function_t>(String("int operator-"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Int, false, intSub)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Double, false, intSubD)),
                });
            Function mul = make_shared<function_t>(String("int operator*"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Int, false, intMul)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Double, false, intMulD)),
                });
            Function div = make_shared<function_t>(String("int operator/"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Int, false, intDiv)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Double, false, intDivD)),
                });
            Function mod = make_shared<function_t>(String("int operator%"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Int, false, intMod))
                });
            Function lt = make_shared<function_t>(String("int operator<"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Boolean, false, intLt)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Boolean, false, intLtD)),
                });
            Function le = make_shared<function_t>(String("int operator<="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Boolean, false, intLe)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Boolean, false, intLeD)),
                });
            Function gt = make_shared<function_t>(String("int operator>"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Boolean, false, intGt)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Boolean, false, intGtD)),
                });
            Function ge = make_shared<function_t>(String("int operator>="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Boolean, false, intGe)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Boolean, false, intGeD)),
                });
            Function eq = make_shared<function_t>(String("int operator=="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Boolean, false, intEq)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Boolean, false, intEqD)),
                });
            Function ne = make_shared<function_t>(String("int operator!="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Boolean, false, intNe)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Boolean, false, intNeD)),
                });
            Function call = make_shared<function_t>(String("int call"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Int, false, intCalli)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Double, false, intCalld)),
                });
            Function minus = make_shared<function_t>(String("int minus"), function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_Int, false, intMinus)),
                });
            Function plus = make_shared<function_t>(String("int plus"), function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_Int, false, intPlus)),
                });
            Function negate = make_shared<function_t>(String("int negate"), function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_Int, false, intNegate)),
                });
            Function not = make_shared<function_t>(String("int not"), function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_Int, false, intNot)),
                });
            Function bit_and = make_shared<function_t>(String("int operator&"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Int, false, intBitAnd)),
                });
            Function bit_or = make_shared<function_t>(String("int operator|"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Int, false, intBitOr)),
                });
            Function bit_xor = make_shared<function_t>(String("int operator^"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Int, false, intBitXor)),
                });
            Function bit_left = make_shared<function_t>(String("int operator<<"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Int, false, intBitLeft)),
                });
            Function bit_right = make_shared<function_t>(String("int operator>>"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Int, false, intBitRight)),
                });
            Function tobool = make_shared<function_t>(String("int tobool"), function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_Boolean, false, intToBool)),
                });
            Function toString = make_shared<function_t>(toString_str, function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_String, false, intToString))
                });
            Func dtor = nullFunc;
            Constructor ctor = make_shared<constructor_t>(constructor_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeConstructor>(NewBie_Variant, true, intCopy, Args{})),
                    make_pair(make_params(NewBie_Double), make_shared<NativeConstructor>(NewBie_Variant, true, intCtorD, Args{})),
                    make_pair(make_params(NewBie_Boolean), make_shared<NativeConstructor>(NewBie_Variant, true, intCtorBool, Args{})),
                    make_pair(make_params(NewBie_String), make_shared<NativeConstructor>(NewBie_Variant, true, intCtorStr, Args{})),
                    make_pair(make_params(), make_shared<NativeConstructor>(NewBie_Variant, true, intCtor, Args{})),
                });
            Operator o;
            o.set({ { o_add, add }, { o_sub, sub}, { o_mul, mul }, { o_div, div }, { o_mod, mod },
                { o_minus, minus }, { o_plus, plus }, { o_not, not}, {o_negate, negate },
                { o_bit_and, bit_and }, { o_bit_or, bit_or }, { o_bit_xor, bit_xor }, { o_bit_left, bit_left }, { o_bit_right, bit_right },
                {o_lt, lt}, {o_le, le}, {o_gt, gt}, {o_ge, ge}, {o_eq, eq}, {o_ne, ne},
                { o_call, call }, { o_toBool, tobool } });
            Class cl = make_shared<class_t>(this, int_str, NewBie_Int, bases, true, false, true, ctor, dtor, o, class_t::vars(), intPtrDeleter);
            cl->addToPrototype(toString_str, ObjectContainer(*runner, toString), PUBLIC);
            return cl;
        }

        Class InterpreterImp::makeDoubleClass()
        {
            vector<Class> bases{ primitive_class[NewBie_Object] };
            Function add = make_shared<function_t>(String("double operator+"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Double, false, doubleAddI)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Double, false, doubleAdd)),
                });
            Function sub = make_shared<function_t>(String("double operator-"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Double, false, doubleSubI)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Double, false, doubleSub)),
                });
            Function mul = make_shared<function_t>(String("double operator*"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Double, false, doubleMulI)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Double, false, doubleMul)),
                });
            Function div = make_shared<function_t>(String("double operator/"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Double, false, doubleDivI)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Double, false, doubleDiv)),
                });
            Function lt = make_shared<function_t>(String("double operator<"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Boolean, false, doubleLtI)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Boolean, false, doubleLt)),
                });
            Function le = make_shared<function_t>(String("double operator<="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Boolean, false, doubleLeI)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Boolean, false, doubleLe)),
                });
            Function gt = make_shared<function_t>(String("double operator>"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Boolean, false, doubleGtI)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Boolean, false, doubleGt)),
                });
            Function ge = make_shared<function_t>(String("double operator>="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Boolean, false, doubleGeI)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Boolean, false, doubleGe)),
                });
            Function eq = make_shared<function_t>(String("double operator=="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Boolean, false, doubleEqI)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Boolean, false, doubleEq)),
                });
            Function ne = make_shared<function_t>(String("double operator!="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Boolean, false, doubleNeI)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Boolean, false, doubleNe)),
                });
            Function call = make_shared<function_t>(String("double call"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_Boolean, false, doubleCalli)),
                    make_pair(make_params(NewBie_Double), make_shared<NativeFunction>(NewBie_Double, false, doubleCalld)),
                });
            Function minus = make_shared<function_t>(String("double minus"), function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_Double, false, doubleMinus)),
                });
            Function plus = make_shared<function_t>(String("double plus"), function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_Double, false, doublePlus)),
                });
            Function negate = make_shared<function_t>(String("double negate"), function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_Double, false, doubleNegate)),
                });
            Function tobool = make_shared<function_t>(String("double tobool"), function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_Boolean, false, doubleToBool)),
                });
            Function toString = make_shared<function_t>(toString_str, function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_String, false, doubleToString))
                });
            Func dtor = nullFunc;
            Constructor ctor = make_shared<constructor_t>(constructor_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeConstructor>(NewBie_Variant, true, doubleCtorI, Args{})),
                    make_pair(make_params(NewBie_String), make_shared<NativeConstructor>(NewBie_Variant, true, doubleCtorStr, Args{})),
                    make_pair(make_params(NewBie_Double), make_shared<NativeConstructor>(NewBie_Variant, true, doubleCopy, Args{})),
                    make_pair(make_params(), make_shared<NativeConstructor>(make_shared<NativeFunction>(NewBie_Variant, true, doubleCtor), Args{})),
                });
            Operator o;
            o.set({ { o_add, add }, { o_sub, sub }, { o_mul, mul}, { o_div, div },
                { o_minus, minus }, { o_plus, plus }, { o_negate, negate }, { o_call, call }, { o_toBool, tobool },
                { o_lt, lt },{ o_le, le },{ o_gt, gt },{ o_ge, ge },{ o_eq, eq },{ o_ne, ne } });
            Class cl = make_shared<class_t>(this, double_str, NewBie_Double, bases, true, false, true, ctor, dtor, o, class_t::vars(), doublePtrDeleter);
            cl->addToPrototype(toString_str, ObjectContainer(*runner, toString), PUBLIC);
            return cl;
        }

        Class InterpreterImp::makeBooleanClass()
        {
            vector<Class> bases{ primitive_class[NewBie_Object] };
            Function toString = make_shared<function_t>(toString_str, function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_String, false, booleanToString))
                });
            Function eq = make_shared<function_t>(String("boolean operator=="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Boolean), make_shared<NativeFunction>(NewBie_Boolean, false, booleanEq)),
                });
            Function ne = make_shared<function_t>(String("boolean operator!="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Boolean), make_shared<NativeFunction>(NewBie_Boolean, false, booleanNe)),
                });
            Function and = make_shared<function_t>(String("boolean operator&&"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Boolean), make_shared<NativeFunction>(NewBie_Boolean, false, booleanAnd)),
                });
            Function or = make_shared<function_t>(String("boolean operator||"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Boolean), make_shared<NativeFunction>(NewBie_Boolean, false, booleanOr)),
                });
            Func dtor = nullFunc;
            Constructor ctor = make_shared<constructor_t>(constructor_t::init_vec
                {
                    make_pair(make_params(NewBie_Boolean), make_shared<NativeConstructor>(NewBie_Variant, true, booleanCopy, Args{})),
                    make_pair(make_params(), make_shared<NativeConstructor>(NewBie_Variant, true, booleanCtor, Args{}))
                });
            Operator o;
            o.set({ {o_and, and},{o_or, or }, {o_eq, eq}, {o_ne, ne} });
            Class cl = make_shared<class_t>(this, boolean_str, NewBie_Boolean, bases, true, false, true, ctor, dtor, o, class_t::vars(), booleanPtrDeleter);
            cl->addToPrototype(toString_str, ObjectContainer(*runner, toString), PUBLIC);
            return cl;
        }

        Class InterpreterImp::makeStringClass()
        {
            vector<Class> bases{ primitive_class[NewBie_Object] };
            Function add = make_shared<function_t>(String("string operator+"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_String), make_shared<NativeFunction>(NewBie_String, false, stringAdd))
                });
            Function mul = make_shared<function_t>(String("string operator*"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_String, false, stringMul))
                });
            Function lt = make_shared<function_t>(String("string operator<"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_String), make_shared<NativeFunction>(NewBie_Boolean, false, stringLt)),
                });
            Function le = make_shared<function_t>(String("string operator<="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_String), make_shared<NativeFunction>(NewBie_Boolean, false, stringLe)),
                });
            Function gt = make_shared<function_t>(String("string operator>"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_String), make_shared<NativeFunction>(NewBie_Boolean, false, stringGt)),
                });
            Function ge = make_shared<function_t>(String("string operator>="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_String), make_shared<NativeFunction>(NewBie_Boolean, false, stringGe)),
                });
            Function eq = make_shared<function_t>(String("string operator=="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_String), make_shared<NativeFunction>(NewBie_Boolean, false, stringEq)),
                });
            Function ne = make_shared<function_t>(String("string operator!="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_String), make_shared<NativeFunction>(NewBie_Boolean, false, stringNe)),
                });
            Function tobool = make_shared<function_t>(String("string tobool"), function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_Boolean, false, stringToBool))
                });
            Function index = make_shared<function_t>(String("string index"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int), make_shared<NativeFunction>(NewBie_String, false, stringIndex))
                });
            Function toString = make_shared<function_t>(toString_str, function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_String, false, stringToString))
                });
            Function call = make_shared<function_t>(String("string call"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int, NewBie_Int), make_shared<NativeFunction>(NewBie_String, false, stringSubstring))
                });
            String substr_str = "substr";
            String substring_str = "substring";
            Function substr = make_shared<function_t>(String("substr"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int, NewBie_Int), make_shared<NativeFunction>(NewBie_String, false, stringSubstr))
                });
            Function substring = make_shared<function_t>(String("substring"), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Int, NewBie_Int), make_shared<NativeFunction>(NewBie_String, false, stringSubstring))
                });
            Func dtor = nullFunc;
            Constructor ctor = make_shared<constructor_t>(constructor_t::init_vec
                {
                    make_pair(make_params(NewBie_String), make_shared<NativeConstructor>(NewBie_Variant, true, stringCopy, Args{})),
                    make_pair(make_params(), make_shared<NativeConstructor>(NewBie_Variant, true, stringCtor, Args{})),
                });
            Operator o;
            o.set({ {o_add, add}, {o_mul, mul}, { o_index, index },{ o_call, call },{ o_toBool, tobool },
                { o_lt, lt },{ o_le, le },{ o_gt, gt },{ o_ge, ge },{ o_eq, eq },{ o_ne, ne } });
            Class cl = make_shared<class_t>(this, string_str, NewBie_String, bases, true, false, true, ctor, dtor, o, class_t::vars(), stringPtrDeleter);
            cl->addToPrototype(toString_str, ObjectContainer(*runner, toString), PUBLIC);
            cl->addToPrototype(substr_str, ObjectContainer(*runner, substr), PUBLIC);
            cl->addToPrototype(substring_str, ObjectContainer(*runner, substring), PUBLIC);
            return cl;
        }

        Class InterpreterImp::makeFunctionClass()
        {
            vector<Class> bases{ primitive_class[NewBie_Object] };

            Function eq = make_shared<function_t>(String("function operator=="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Function), make_shared<NativeFunction>(NewBie_Variant, false, functionEq))
                });
            Function ne = make_shared<function_t>(String("function operator!="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Function), make_shared<NativeFunction>(NewBie_Variant, false, functionNe))
                });
            Function call = make_shared<function_t>(String("function call"), function_t::init_vec
                {
                    make_pair(ParameterList{Parameter(NewBie_Variant, Expression(), false, false, for_functionCall)}, 
                    make_shared<NativeFunction>(NewBie_Variant, false, functionCall))
                });
            Function toString = make_shared<function_t>(toString_str, function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_String, false, functionToString))
                });
            Func dtor = nullFunc;
            Constructor ctor;
            Operator o;
            o.set({ {o_eq, eq}, {o_ne, ne}, {o_call, call} });
            Class cl = make_shared<class_t>(this, function_str, NewBie_Function, bases, true, false, true, ctor, dtor, o, class_t::vars(), functionPtrDeleter);
            cl->addToPrototype(toString_str, ObjectContainer(*runner, toString), PUBLIC);
            return cl;
        }

        Class InterpreterImp::makeClassClass()
        {
            vector<Class> bases{ primitive_class[NewBie_Object] };
            
            Function eq = make_shared<function_t>(String("class operator=="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Class), make_shared<NativeFunction>(NewBie_Variant, false, classEq))
                });
            Function ne = make_shared<function_t>(String("class operator!="), function_t::init_vec
                {
                    make_pair(make_params(NewBie_Class), make_shared<NativeFunction>(NewBie_Variant, false, classNe))
                });
            Function call = make_shared<function_t>(String("class call"), function_t::init_vec
                {
                    make_pair(ParameterList{ Parameter(NewBie_Variant, Expression(), false, false, for_functionCall) },
                    make_shared<NativeFunction>(NewBie_Variant, false, classCall))
                });
            Function toString = make_shared<function_t>(toString_str, function_t::init_vec
                {
                    make_pair(make_params(), make_shared<NativeFunction>(NewBie_String, false, functionToString))
                });
            Func dtor = nullFunc;
            Constructor ctor;
            Operator o;
            o.set({ { o_eq, eq },{ o_ne, ne },{ o_call, call } });
            Class cl = make_shared<class_t>(this, class_str, NewBie_Class, bases, true, false, true, ctor, dtor, o, class_t::vars(), functionPtrDeleter);
            cl->addToPrototype(toString_str, ObjectContainer(*runner, toString), PUBLIC);
            return cl;
        }

        zyd2001::NewBie::object_t::object_t(Runner & runner, const int &i) : runner(runner),
            native_ptr(new int32_t(i)), cl(runner.inter->primitive_class[NewBie_Int]),
            type(runner.inter->primitive_class[NewBie_Int]->type),
            type_name(runner.inter->primitive_class[NewBie_Int]->type_name) {}

        zyd2001::NewBie::object_t::object_t(Runner & runner, const double &d) : runner(runner),
            native_ptr(new double(d)), cl(runner.inter->primitive_class[NewBie_Double]),
            type(runner.inter->primitive_class[NewBie_Double]->type),
            type_name(runner.inter->primitive_class[NewBie_Double]->type_name) {}

        zyd2001::NewBie::object_t::object_t(Runner & runner, const bool &i) : runner(runner),
            native_ptr(new bool(i)), cl(runner.inter->primitive_class[NewBie_Boolean]),
            type(runner.inter->primitive_class[NewBie_Boolean]->type),
            type_name(runner.inter->primitive_class[NewBie_Boolean]->type_name) {}

        zyd2001::NewBie::object_t::object_t(Runner & r, const std::string &s) : object_t(r, String(s)) {}

        zyd2001::NewBie::object_t::object_t(Runner & runner, const String &i) : runner(runner),
            native_ptr(new String(i)), cl(runner.inter->primitive_class[NewBie_String]),
            type(runner.inter->primitive_class[NewBie_String]->type),
            type_name(runner.inter->primitive_class[NewBie_String]->type_name) {}

        object_t::object_t(Runner & runner, Class c) : runner(runner), native_ptr(new Class(c)), cl(runner.inter->primitive_class[NewBie_Class]),
            type(runner.inter->primitive_class[NewBie_Class]->type),
            type_name(runner.inter->primitive_class[NewBie_Class]->type_name) {}

        zyd2001::NewBie::object_t::object_t(Runner & runner, Function f) : runner(runner),
            native_ptr(new Function(f)), cl(runner.inter->primitive_class[NewBie_Function]),
            type(runner.inter->primitive_class[NewBie_Function]->type),
            type_name(runner.inter->primitive_class[NewBie_Function]->type_name) {}

        String::String() : ptr(make_shared<basic_string<char_t>>()) {}
        String::String(const char * s) : String(string(s)) {}
        String::String(const std::string &s) : ptr(make_shared<basic_string<char_t>>(conv.from_bytes(s))) {}
        String::String(const char_t *str) : ptr(make_shared<basic_string<char_t>>(str)) {}
        String::String(const basic_string<char_t> &str) : ptr(make_shared<basic_string<char_t>>(str)) {}
        basic_string<char_t> &String::get() const { return *ptr; }
        std::string String::toStr() const { return conv.to_bytes(*ptr); }

        String zyd2001::NewBie::String::copy() const
        {
            return String(get());
        }

        String String::operator+(const String &str)
        {
            return String(*(this->ptr) + *str.ptr);
        }
        String &String::operator+=(const String &str)
        {
            *(this->ptr) += *str.ptr;
            return *this;
        }
        String &String::operator=(const String &str)
        {
            String s(str);
            std::swap(s.ptr, ptr);
            return *this;
        }
        bool String::operator==(const String &str) const
        {
            if (this->ptr == str.ptr)
                return true;
            else
                return *(this->ptr) == *str.ptr;
        }

        bool String::operator!=(const String & str) const
        {
            if (this->ptr != str.ptr)
                return true;
            else
                return *(this->ptr) != *str.ptr;
        }

        bool zyd2001::NewBie::String::operator>(const String &s) const
        {
            return *ptr > *s.ptr;
        }

        bool String::operator>=(const String & s) const
        {
            return *ptr >= *s.ptr;
        }

        bool zyd2001::NewBie::String::operator<(const String &s) const
        {
            return *ptr < *s.ptr;
        }

        bool String::operator<=(const String & s) const
        {
            return *ptr <= *s.ptr;
        }

        size_t zyd2001::NewBie::StringHash::operator()(const String &s) const
        {
            return h(*s.ptr);
        }

        bool ParamsEqualTo::operator()(const ParameterList& lhs, const ParameterList& rhs) const
        {
            if (lhs.size() != rhs.size())
                return false;
            else
            {
                for (int i = 0; i < lhs.size(); i++)
                {
                    if (lhs[i].type != rhs[i].type)
                        return false;
                }
                return true;
            }
        }

        std::size_t ParamsHash::operator()(const ParameterList& p) const
        {
            std::hash<ObjectType> h;
            std::size_t seed = 0;
            for (auto &i : p)
                seed ^= h(i.type) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    }
}