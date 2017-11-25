#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

#include <codecvt>
#include <locale>

using namespace zyd2001::NewBie;
using namespace std;

#define delete_cast(...) delete static_cast<__VA_ARGS__>(content)
#define get_cast(...) (*static_cast<__VA_ARGS__>(content))
#define replace(...) do {delete_cast(__VA_ARGS__); content = ptr;} while(0)

#if defined(_MSC_VER)
wstring_convert<codecvt_utf8<uint32_t>, uint32_t> conv;
#elif defined(__GNUC__)
wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
#endif

Value::Value(ValueType t, void *c) : type(t), content(c) {}
Value::Value(const Value &v) : type(v.type)
{
	switch (type)
	{
		case zyd2001::NewBie::INT_TYPE:
		{
			int *ptr = new int(v.get<int>());
			content = ptr;
			break;
		}
		case zyd2001::NewBie::DOUBLE_TYPE:
		{
			double *ptr = new double(v.get<double>());
			content = ptr;
			break;
		}
		case zyd2001::NewBie::BOOL_TYPE:
		{
			bool *ptr = new bool(v.get<bool>());
			content = ptr;
			break;
		}
		case zyd2001::NewBie::STRING_TYPE:
		{
			u32string *ptr = new u32string(v.get<u32string>());
			content = ptr;
			break;
		}
		case zyd2001::NewBie::ARRAY_TYPE:
			break;
		case zyd2001::NewBie::OBJECT_TYPE:
			break;
		default:
			break;
	}
}
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

Value Value::operator+(const Value &v) const
{
	if (type == STRING_TYPE || v.type == STRING_TYPE)
	{
		Value first(*this);
		Value second(v);
		first.change_type(STRING_TYPE);
		second.change_type(STRING_TYPE);
		first.get<u32string>() += second.get<u32string>();
		return first;
	}
	else if (type == DOUBLE_TYPE || v.type == DOUBLE_TYPE)
	{
		Value first(*this);
		Value second(v);
		first.change_type(DOUBLE_TYPE);
		second.change_type(DOUBLE_TYPE);
		first.get<double>() += second.get<double>();
		return first;
	}
	else
	{
		return Value(INT_TYPE, new int(get<int>() + v.get<int>()));
	}
}

Value zyd2001::NewBie::change(const Value &v, ValueType t)
{
	Value val(v);
	val.change_type(t);
	return val;
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
					replace(int*);
					break;
				}
				case zyd2001::NewBie::BOOL_TYPE:
				{
					bool *ptr = new bool(get_cast(int*) ? true : false);
					replace(int*);
					break;
				}
				case zyd2001::NewBie::STRING_TYPE:
				{
					u32string *ptr = new u32string(conv.from_bytes(to_string(get_cast(int*))));
					replace(int*);
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
					replace(double*);
					break;
				}
				case zyd2001::NewBie::DOUBLE_TYPE:
					break;
				case zyd2001::NewBie::BOOL_TYPE:
				{
					bool *ptr = new bool(get_cast(double*) ? true : false);
					replace(double*);
					break;
				}
				case zyd2001::NewBie::STRING_TYPE:
				{
					u32string *ptr = new u32string(conv.from_bytes(to_string(get_cast(double*))));
					replace(double*);
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
					replace(bool*);
					break;
				}
				case zyd2001::NewBie::DOUBLE_TYPE:
				{
					double *ptr = new double(get_cast(bool*) ? 1 : 0);
					replace(bool*);
					break;
				}
				case zyd2001::NewBie::BOOL_TYPE:
					break;
				case zyd2001::NewBie::STRING_TYPE:
				{
					u32string *ptr = new u32string(conv.from_bytes(get_cast(bool*) ? "true" : "false"));
					replace(bool*);
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
					int *ptr = new int(stoi(conv.to_bytes(get_cast(u32string*))));
					replace(u32string*);
					break;
				}
				case zyd2001::NewBie::DOUBLE_TYPE:
				{
					double *ptr = new double(stod(conv.to_bytes(get_cast(u32string*))));
					replace(u32string*);
					break;
				}
				case zyd2001::NewBie::BOOL_TYPE:
				{
					bool *ptr = new bool(get_cast(u32string*).empty() ? false : true);
					replace(u32string*);
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

ostream &zyd2001::NewBie::operator<<(ostream &out, Value &v)
{
	switch (v.type)
	{
		case zyd2001::NewBie::INT_TYPE:
			out << v.get<int>();
			break;
		case zyd2001::NewBie::DOUBLE_TYPE:
			out << v.get<double>();
			break;
		case zyd2001::NewBie::BOOL_TYPE:
			out << v.get<bool>();
			break;
		case zyd2001::NewBie::STRING_TYPE:
			out << conv.to_bytes(v.get<u32string>());
			break;
		case zyd2001::NewBie::ARRAY_TYPE:
			break;
		case zyd2001::NewBie::OBJECT_TYPE:
			break;
		default:
			break;
	}
	return out;
}