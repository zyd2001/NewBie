#ifndef NEWBIE_SCANNER_HPP

#include "location.hh"
#include "NewBie_Parser.hpp"

namespace zyd2001::NewBie
{
	class Scanner
	{
	public:
		Scanner(const std::string &);
		~Scanner();
		yyscan_t scanner;
		Parser::location_type loc;
		inline int lineno();
		inline Parser::symbol_type yylex(Parser::location_type &loc);
	};
}
#endif // !NEWBIE_SCANNER_HPP