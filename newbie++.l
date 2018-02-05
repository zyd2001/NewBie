%{
#include "NewBie_Lang.hpp"
#include "NewBie.hpp"
#include "Parser.hpp"
#include "location.hh"
#include <codecvt>
#include <locale>
#include <sstream>

using namespace std;
using namespace zyd2001::NewBie;
string heredoc_tag;
ostringstream string_buffer;
#if defined(_MSC_VER)
extern wstring_convert<codecvt_utf8<char_t>, char_t> conv;
#elif defined(__GNUC__)
extern wstring_convert<codecvt_utf8<char_t>, char_t> conv;
#endif
static zyd2001::NewBie::location loc;

#define YY_DECL Parser::symbol_type yylex(zyd2001::NewBie::InterpreterImp &inter, yyscan_t yyscanner)

%}

%{
# define YY_USER_ACTION loc.step(); loc.columns (yyleng);
%}

%option noyywrap yylineno reentrant nounistd never-interactive
%option outfile="Scanner.cpp"
%start LINE_COMMENT BLOCK_COMMENT STRING_LITERAL_STATE HEREDOC

%%
<INITIAL>"int"          return Parser::make_INT(loc);
<INITIAL>"double"       return Parser::make_DOUBLE(loc);
<INITIAL>"bool"         return Parser::make_BOOL(loc);
<INITIAL>"boolean"      return Parser::make_BOOL(loc);
<INITIAL>"array"        return Parser::make_ARRAY(loc);
<INITIAL>"string"       return Parser::make_STRING(loc);
<INITIAL>"var"          return Parser::make_VAR(loc);
<INITIAL>"global"		return Parser::make_GLOBAL(loc);
<INITIAL>"if"           return Parser::make_IF(loc);
<INITIAL>"else"         return Parser::make_ELSE(loc);
<INITIAL>"elseif"       return Parser::make_ELSEIF(loc);
<INITIAL>"else if"      return Parser::make_ELSEIF(loc);
<INITIAL>"elif"         return Parser::make_ELSEIF(loc);
<INITIAL>"elsif"        return Parser::make_ELSEIF(loc);
<INITIAL>"for"          return Parser::make_FOR(loc);
<INITIAL>"foreach"      return Parser::make_FOR(loc);
<INITIAL>"in"           return Parser::make_IN(loc);
<INITIAL>"break"        return Parser::make_BREAK(loc);
<INITIAL>"continue"     return Parser::make_CONTINUE(loc);
<INITIAL>"constructor"  return Parser::make_CONSTRUCTOR(loc);
<INITIAL>"ctor"         return Parser::make_CONSTRUCTOR(loc);
<INITIAL>"return"       return Parser::make_RETURN(loc);
<INITIAL>"class"        {inter.in_class = true; inter.current_class = new Class(); return Parser::make_CLASS(loc);}
<INITIAL>"new"          return Parser::make_NEW(loc);
<INITIAL>"this"         return Parser::make_THIS(loc);
<INITIAL>"__print__"    return Parser::make_PRINT(loc);
<INITIAL>"("            return Parser::make_LP(loc);
<INITIAL>")"            return Parser::make_RP(loc);
<INITIAL>"{"            {inter.level++; return Parser::make_LC(loc);}
<INITIAL>"}"            {inter.level--; return Parser::make_RC(loc);}
<INITIAL>"["            return Parser::make_LB(loc);
<INITIAL>"]"            return Parser::make_RB(loc);
<INITIAL>";"            return Parser::make_SEMICOLON(loc);
<INITIAL>","            return Parser::make_COMMA(loc);
<INITIAL>"&&"           return Parser::make_LOGICAL_AND(loc);
<INITIAL>"AND"          return Parser::make_LOGICAL_AND(loc);
<INITIAL>"||"           return Parser::make_LOGICAL_OR(loc);
<INITIAL>"OR"           return Parser::make_LOGICAL_OR(loc);
<INITIAL>"="            return Parser::make_ASSIGN(loc);
<INITIAL>"=="           return Parser::make_EQ(loc);
<INITIAL>"!="           return Parser::make_NE(loc);
<INITIAL>">"            return Parser::make_GT(loc);
<INITIAL>">="           return Parser::make_GE(loc);
<INITIAL>"<"            return Parser::make_LT(loc);
<INITIAL>"<="           return Parser::make_LE(loc);
<INITIAL>"+"            return Parser::make_ADD(loc);
<INITIAL>"-"            return Parser::make_SUB(loc);
<INITIAL>"*"            return Parser::make_MUL(loc);
<INITIAL>"/"            return Parser::make_DIV(loc);
<INITIAL>"%"            return Parser::make_MOD(loc);
<INITIAL>"+="           return Parser::make_ADD_ASSIGN(loc);
<INITIAL>"-="           return Parser::make_SUB_ASSIGN(loc);
<INITIAL>"*="           return Parser::make_MUL_ASSIGN(loc);
<INITIAL>"/="           return Parser::make_DIV_ASSIGN(loc);
<INITIAL>"%="           return Parser::make_MOD_ASSIGN(loc);
<INITIAL>"++"           return Parser::make_INCREMENT(loc);
<INITIAL>"--"           return Parser::make_DECREMENT(loc);
<INITIAL>"!"            return Parser::make_EXCLAMATION(loc);
<INITIAL>"."            return Parser::make_DOT(loc);
<INITIAL>"~"            return Parser::make_REVERSE(loc);
<INITIAL>"ref"          return Parser::make_REF(loc);
<INITIAL>"interface"    return Parser::make_INTERFACE(loc);
<INITIAL>"public"       return Parser::make_PUBLIC(loc);
<INITIAL>"protected"    return Parser::make_PROTECTED(loc);
<INITIAL>"private"      return Parser::make_PRIVATE(loc);
<INITIAL>"super"        return Parser::make_SUPER(loc);
<INITIAL>"true" {       
    return Parser::make_BOOL_LITERAL(Expression(LITERAL_EXPRESSION, new LiteralExpression(true)), loc);
}
<INITIAL>"false" {       
    return Parser::make_BOOL_LITERAL(Expression(LITERAL_EXPRESSION, new LiteralExpression(false)), loc);
}
<INITIAL>[ \t] loc.step();
<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
    return Parser::make_IDENTIFIER(Identifier(conv.from_bytes(yytext)), loc); 
}
<INITIAL>[1-9][0-9]*|"0" {
    return Parser::make_INT_LITERAL(Expression(LITERAL_EXPRESSION, new LiteralExpression(stoi(yytext))), loc);
}
<INITIAL>[0-9]+\.[0-9]+ {
    return Parser::make_DOUBLE_LITERAL(Expression(LITERAL_EXPRESSION, new LiteralExpression(stod(yytext))), loc);
}
<INITIAL>\" {
    BEGIN STRING_LITERAL_STATE;
}
<INITIAL>"/*" {BEGIN BLOCK_COMMENT;}
<INITIAL>"//" {BEGIN LINE_COMMENT;}
<INITIAL>"#" {BEGIN LINE_COMMENT;}
<INITIAL>\n {loc.lines(yyleng); loc.step();}
<INITIAL>"<<<"[A-Za-z_]+[\r\n]+ {
    loc.lines(yyleng);
    loc.step();
    heredoc_tag += yytext + 3;
    auto _n = heredoc_tag.find('\r');
    if (_n != string::npos)
        heredoc_tag.erase(_n);
    auto _r = heredoc_tag.find('\n');
    if (_r != string::npos)
        heredoc_tag.erase(_r);
    BEGIN HEREDOC;
}
<HEREDOC>^">>>"[A-Za-z_]+/";" {
    if(heredoc_tag == (yytext + 3))
    {
        BEGIN INITIAL;
        heredoc_tag.clear();
        string temp = string_buffer.str();
        string_buffer.str("");
        if (temp.empty())
            return Parser::make_STRING_LITERAL(Expression(LITERAL_EXPRESSION, new LiteralExpression(string_t())), loc);
        else
        {
            auto _n = temp.rfind('\n');
            if (_n != string::npos)
                temp.erase(_n);
            auto _r = temp.rfind('\r');
            if (_r != string::npos)
                temp.erase(_r);
            return Parser::make_STRING_LITERAL(Expression(LITERAL_EXPRESSION, new LiteralExpression(conv.from_bytes(temp))), loc);
        }
    }
    else
        string_buffer << yytext;
}
<HEREDOC>. {
    string_buffer << yytext;
}
<HEREDOC>\n {
    loc.lines(yyleng);
    loc.step();
    string_buffer << yytext;
}
<LINE_COMMENT>. ;
<LINE_COMMENT>\n {
    loc.lines(yyleng);
    loc.step();
    BEGIN INITIAL;
}
<BLOCK_COMMENT>\n {
    loc.lines(yyleng);
    loc.step();    
}
<BLOCK_COMMENT>. ;
<BLOCK_COMMENT>"*/" {BEGIN INITIAL;}
<STRING_LITERAL_STATE>\n {
    loc.lines(yyleng);
    loc.step();
}
<STRING_LITERAL_STATE>\\n {
    string_buffer << '\n';
}
<STRING_LITERAL_STATE>\\\" {
    string_buffer << '\"';
}
<STRING_LITERAL_STATE>\" {
    BEGIN INITIAL;
    string temp = string_buffer.str();
    string_buffer.str("");
    if (temp.empty())
    {
        return Parser::make_STRING_LITERAL(Expression(LITERAL_EXPRESSION, new LiteralExpression(string_t())), loc);
    }
    else
    {
        return Parser::make_STRING_LITERAL(Expression(LITERAL_EXPRESSION, new LiteralExpression(conv.from_bytes(temp))), loc);
    }
}
<STRING_LITERAL_STATE>. {
    string_buffer << yytext;
}
<<EOF>> return Parser::make_END(loc);
%%