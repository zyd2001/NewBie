#include "NewBie_Scanner.hpp"
#define YY_DECL zyd2001::NewBie::Parser::symbol_type yylex(yyscan_t yyscanner, Parser::location_type &loc)
YY_DECL;
#include "NewBie_Flex.h"
using namespace std;
using namespace zyd2001::NewBie;

Scanner::Scanner(const string &s)
{
	FILE *in = fopen(s.c_str(), "r");
	if (in == NULL)
	{
		cerr << "Cannot open the input file!" << endl;
		throw runtime_error("Cannot open the input file!");
	}
	if (yylex_init(&scanner) != 0)
	{
		cerr << "Scanner initialization failed!" << endl;
		throw runtime_error("Scanner initialization failed!");
	}
	yyset_in(in, scanner);
}
Scanner::~Scanner()
{
	yylex_destroy(scanner);
}

int Scanner::lineno()
{
	return yyget_lineno(scanner);
}

Parser::symbol_type Scanner::yylex(Parser::location_type &loc)
{
	return ::yylex(scanner, loc);
}