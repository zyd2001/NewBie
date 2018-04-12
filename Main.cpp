//#include "NewBie_Lang.hpp"
//#include "NewBie.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

struct helpStruct
{
    int type;
    void * ptr;
    helpStruct(const int &i);
    helpStruct(const double &i);
    helpStruct(const bool &i);
    helpStruct(const std::string &i);
};

helpStruct::helpStruct(const int &i) : type(2), ptr(new int(i)) {}
helpStruct::helpStruct(const double &i) : type(3), ptr(new double(i)) {}
helpStruct::helpStruct(const bool &i) : type(4), ptr(new bool(i)) {}
helpStruct::helpStruct(const std::string &i) : type(5), ptr(new string(i)) {}

void _print(vector<helpStruct> & v)
{
    for (auto &i : v)
    {
        switch (i.type)
        {
            case 2:
                cout << "int " << *static_cast<int*>(i.ptr) << endl;
                break;
            case 3:
                cout << "double " << *static_cast<double*>(i.ptr) << endl;
                break;
            case 4:
                cout << "bool " << boolalpha << *static_cast<bool*>(i.ptr) << noboolalpha << endl;
                break;
            case 5:
                cout << "string " << *static_cast<string*>(i.ptr) << endl;
                break;
        }
    }
}

template<typename...Val>
void print(Val&& ...val)
{
    _print(vector<helpStruct>{ std::forward<Val>(val)... });
}

int main(int argc, char **argv)
{
    //zyd2001::NewBie::InterpreterImp inter;
    //inter.setFile("test");
    //inter.parse();
    //inter.run();
    print(1, 2, 3.3, true, string("fuck"));
}