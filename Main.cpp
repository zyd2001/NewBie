//#include "NewBie_Lang.hpp"
//#include "NewBie.hpp"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include <variant>
#include <any>

using namespace std;

struct helpStruct
{
    int type;
    void * ptr;
    helpStruct(const int &i);
    helpStruct(const double &i);
    helpStruct(const bool &i);
    helpStruct(const std::string &i);
    helpStruct(const char * i);
    helpStruct(const helpStruct &);
    ~helpStruct();
    
    template<typename T>
    T &get() const
    {
        return *static_cast<T*>(ptr);
    }
};

helpStruct::helpStruct(const int &i) : type(2), ptr(new int(i)) {}
helpStruct::helpStruct(const double &i) : type(3), ptr(new double(i)) {}
helpStruct::helpStruct(const bool &i) : type(4), ptr(new bool(i)) {}
helpStruct::helpStruct(const std::string &i) : type(5), ptr(new string(i)) {}
helpStruct::helpStruct(const char * i) : type(5), ptr(new string(i)) {}
helpStruct::helpStruct(const helpStruct &h) : type(h.type)
{
    switch (type)
    {
        case 2:
            ptr = new int(*static_cast<int*>(h.ptr));
            break;
        case 3:
            ptr = new double(*static_cast<double*>(h.ptr));
            break;
        case 4:
            ptr = new bool(*static_cast<bool*>(h.ptr));
            break;
        case 5:
            ptr = new string(*static_cast<string*>(h.ptr));
            break;
    }
}
helpStruct::~helpStruct()
{
    switch (type)
    {
        case 2:
            delete static_cast<int*>(ptr);
            break;
        case 3:
            delete static_cast<double*>(ptr);
            break;
        case 4:
            delete static_cast<bool*>(ptr);
            break;
        case 5:
            delete static_cast<string*>(ptr);
            break;
    }
}

void _print(const vector<helpStruct> & v)
{
    for (auto &i : v)
    {
        switch (i.type)
        {
            case 2:
                cout << "int " << i.get<int>() << endl;
                break;
            case 3:
                cout << "double " << i.get<double>() << endl;
                break;
            case 4:
                cout << "bool " << boolalpha << i.get<bool>() << noboolalpha << endl;
                break;
            case 5:
                cout << "string " << i.get<string>() << endl;
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
    print(1, 2, 3, "test");
    print(1, "test");
}