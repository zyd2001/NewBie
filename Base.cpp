#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

#include <codecvt>
#include <locale>

using namespace zyd2001::NewBie;
using namespace std;

#define delete_cast(...) delete static_cast<__VA_ARGS__>(content)
#define get_cast(...) (*static_cast<__VA_ARGS__>(content))
#define change(...) do {delete_cast(__VA_ARGS__); content = ptr;} while(0)

#ifdef _MSC_VER
wstring_convert<codecvt_utf8<uint32_t>, uint32_t> conv;
#else
wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
#endif

Value::Value(ValueType t, void *c) : type(t), content(c) {}
Value::~Value()
{
	switch (type)
	{
	case zyd2001::NewBie::INT_TYPE:
		delete_cast(int*);
		break;
	case zyd2001::NewBie::DOUBLE_TYPE:
		delete_cast(double*);
		break;
	case zyd2001::NewBie::BOOL_TYPE:
		delete_cast(bool*);
		break;
	case zyd2001::NewBie::STRING_TYPE:
		delete_cast(u32string*);
		break;
	case zyd2001::NewBie::ARRAY_TYPE:
		delete_cast(unordered_map<string, Value>*);
		break;
	case zyd2001::NewBie::OBJECT_TYPE:
		break;
	default:
		break;
	}
}

void Value::operator+(const Value &v)
{
	switch (type)
	{
	case zyd2001::NewBie::INT_TYPE:
		break;
	case zyd2001::NewBie::DOUBLE_TYPE:
		break;
	case zyd2001::NewBie::BOOL_TYPE:
		break;
	case zyd2001::NewBie::STRING_TYPE:
		break;
	case zyd2001::NewBie::ARRAY_TYPE:
		break;
	case zyd2001::NewBie::OBJECT_TYPE:
		break;
	default:
		break;
	}
}

void Value::change_type(ValueType t)
{
	switch (type)
	{
	case zyd2001::NewBie::INT_TYPE:
	{
		switch (t)
		{
		case zyd2001::NewBie::INT_TYPE:
			break;
		case zyd2001::NewBie::DOUBLE_TYPE:
		{
			double *ptr = new double(static_cast<double>(get_cast(int*)));
			change(int*);
			break;
		}
		case zyd2001::NewBie::BOOL_TYPE:
		{
			bool *ptr = new bool(get_cast(int*) ? true : false);
			change(int*);
			break;
		}
		case zyd2001::NewBie::STRING_TYPE:
		{
			u32string *ptr = new u32string(reinterpret_cast<const char32_t*>((conv.from_bytes(to_string(get_cast(int*))).c_str())));
			change(int*);
			break;
		}
		default:
			throw runtime_error("Type-Cast didn't allow");
			break;
		}
		break;
	}
	case zyd2001::NewBie::DOUBLE_TYPE:
	{
		switch (t)
		{
		case zyd2001::NewBie::INT_TYPE:
		{
			int *ptr = new int(static_cast<double>(get_cast(double*)));
			change(double*);
			break;
		}
		case zyd2001::NewBie::DOUBLE_TYPE:
			break;
		case zyd2001::NewBie::BOOL_TYPE:
		{
			bool *ptr = new bool(get_cast(double*) ? true : false);
			change(double*);
			break;
		}
		case zyd2001::NewBie::STRING_TYPE:
		{
			u32string *ptr = new u32string(reinterpret_cast<const char32_t*>((conv.from_bytes(to_string(get_cast(double*))).c_str())));
			change(double*);
			break;
		}
		default:
			break;
		}
		break;
	}
	case zyd2001::NewBie::BOOL_TYPE:
	{
		switch (t)
		{
		case zyd2001::NewBie::INT_TYPE:
		{
			int *ptr = new int(get_cast(bool*) ? 1 : 0);
			change(bool*);
			break;
		}
		case zyd2001::NewBie::DOUBLE_TYPE:
		{
			double *ptr = new double(get_cast(bool*) ? 1 : 0);
			change(bool*);
			break;
		}
		case zyd2001::NewBie::BOOL_TYPE:
			break;
		case zyd2001::NewBie::STRING_TYPE:
		{
			u32string *ptr = new u32string(reinterpret_cast<const char32_t*>((conv.from_bytes(get_cast(bool*) ? "true" : "false").c_str())));
			change(bool*);
			break;
		}
		default:
			break;
		}
		break;
	}
	case zyd2001::NewBie::STRING_TYPE:
	{
		switch (t)
		{
			case zyd2001::NewBie::INT_TYPE:
			{
#ifdef _MSC_VER
				int *ptr = new int(stoi(conv.to_bytes(reinterpret_cast<const uint32_t*>((get_cast(u32string*).c_str())))));
#else
				int *ptr = new int(stoi(conv.to_bytes(get_cast(u32string*))));
#endif
				change(u32string*);
				break;
			}
			case zyd2001::NewBie::DOUBLE_TYPE:
			{
#ifdef _MSC_VER
				double *ptr = new double(stod(conv.to_bytes(reinterpret_cast<const uint32_t*>((get_cast(u32string*).c_str())))));
#else
				double *ptr = new double(stod(conv.to_bytes(get_cast(u32string*))));
#endif
				change(u32string*);
				break;
			}
			case zyd2001::NewBie::BOOL_TYPE:
			{
				bool *ptr = new bool(get_cast(u32string*).empty() ? false : true);
				change(u32string*);
				break;
			}
			case zyd2001::NewBie::STRING_TYPE:
				break;
			default:
				break;
		}
		break;
	}
	case zyd2001::NewBie::ARRAY_TYPE:
		break;
	case zyd2001::NewBie::OBJECT_TYPE:
		break;
	default:
		break;
	}
	type = t;
}