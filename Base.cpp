#include "NewBie_Lang.hpp"
#include "NewBie.hpp"

using namespace zyd2001::NewBie;
using namespace std;

#define delete_cast(...) delete static_cast<__VA_ARGS__>(content)
#define get_cast(...) (*static_cast<__VA_ARGS__>(content))

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
			double *d = new double(static_cast<double>(get_cast(int*)));
			delete_cast(int*);
			content = d;
			break;
		}
		case zyd2001::NewBie::BOOL_TYPE:
		{
			bool *b = new bool(get_cast(int*) ? true : false);
			delete_cast(int*);
			content = b;
			break;
		}
		case zyd2001::NewBie::STRING_TYPE:
		{
			string *str = new string(to_string(get_cast(int*)));
			delete_cast(int*);
			content = str;
			break;
		}
		default:
			throw exception("Type-Cast didn't allow");
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
			int *d = new int(static_cast<double>(get_cast(double*)));
			delete_cast(double*);
			content = d;
			break;
		}
		case zyd2001::NewBie::DOUBLE_TYPE:
			break;
		case zyd2001::NewBie::BOOL_TYPE:
		{
			bool *b = new bool(get_cast(double*) ? true : false);
			delete_cast(double*);
			content = b;
			break;
		}
		case zyd2001::NewBie::STRING_TYPE:
		{
			string *str = new string(to_string(get_cast(int*)));
			delete_cast(int*);
			content = str;
			break;
		}
		default:
			break;
		}
		break;
	}
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
	type = t;
}

Expression::Expression(ExpressionType t, any c) : type(t), content(c) {}