%{
#include "NewBie_Lang.hpp"
#include "NewBie.hpp"
#include "NewBie_Parser.hpp"

# undef yywrap
# define yywrap() 1

using namespace std;
using namespace zyd2001::NewBie;
string string_buffer, heredoc_tag;
static location loc;
#if defined(_MSC_VER)
wstring_convert<codecvt_utf8<char_t>, char_t> conv;
#elif defined(__GNUC__)
wstring_convert<codecvt_utf8<char_t>, char_t> conv;
#endif

%}
%option noyywrap c++ yylineno nounistd
%start LINE_COMMENT BLOCK_COMMENT STRING_LITERAL_STATE HEREDOC
%%
<INITIAL>"int"          return Parser::make_INT(loc);
<INITIAL>"double"       return Parser::make_DOUBLE(loc);
<INITIAL>"bool"         return Parser::make_BOOL(loc);
<INITIAL>"boolean"      return Parser::make_BOOL(loc);
<INITIAL>"array"        return Parser::make_ARRAY(loc);
<INITIAL>"string"       return Parser::make_STRING(loc);
<INITIAL>"var"          return Parser::make_VAR(loc);
<INITIAL>"function"     return Parser::make_FUNC(loc);
<INITIAL>"func"         return Parser::make_FUNC(loc);
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
<INITIAL>"return"       return Parser::make_RETURN(loc);
<INITIAL>"class"        return Parser::make_CLASS(loc);
<INITIAL>"("            return Parser::make_LP(loc);
<INITIAL>")"            return Parser::make_RP(loc);
<INITIAL>"{"            return Parser::make_LC(loc);
<INITIAL>"}"            return Parser::make_RC(loc);
<INITIAL>"["            return Parser::make_LB(loc);
<INITIAL>"]"            return Parser::make_RB(loc);
<INITIAL>";"            return Parser::make_SEMICOLON(loc);
<INITIAL>","            return Parser::make_COMMA(loc);
<INITIAL>"&&"           return Parser::make_LOGICAL_AND(loc);
<INITIAL>"OR"           return Parser::make_LOGICAL_AND(loc);
<INITIAL>"||"           return Parser::make_LOGICAL_OR(loc);
<INITIAL>"AND"          return Parser::make_LOGICAL_OR(loc);
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
<INITIAL>"public"       return Parser::make_PUBLIC(loc);
<INITIAL>"protected"    return Parser::make_PROTECTED(loc);
<INITIAL>"private"      return Parser::make_PRIVATE(loc);
<INITIAL>"true" {       
    return Parser::make_BOOL_LITERAL(Expression(LITERAL_EXPRESSION, new LiteralExpression(true)), loc);
}
<INITIAL>"false" {       
    return Parser::make_BOOL_LITERAL(Expression(LITERAL_EXPRESSION, new LiteralExpression(false)), loc);
}
<INITIAL>[ \t] ;
<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
    return Parser::make_IDENTIFIER(new string(yytext), loc); 
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
<INITIAL>"<<<"[A-Za-z_]+[\r\n]+ {
    heredoc_tag = yytext;
    heredoc_tag.erase(heredoc_tag.find('\r'));
    heredoc_tag.erase(heredoc_tag.find('\n'));
    BEGIN HEREDOC;
}
<HEREDOC>^">>>"[A-Za-z_]+/";" {
    if(heredoc_tag == (yytext + 3))
    {
        BEGIN INITIAL;
        if (string_buffer.empty())
            return Parser::make_STRING_LITERAL(Expression(LITERAL_EXPRESSION, new LiteralExpression(string_t())), loc);
        else
            return Parser::make_STRING_LITERAL(Expression(LITERAL_EXPRESSION, new LiteralExpression(string_t(conv.from_bytes(string_buffer)))), loc);
    }
    else
        string_buffer += yytext;
}
<HEREDOC>. {
    string_buffer += yytext;
}
<HEREDOC>\n {
    string_buffer += yytext;
}
<LINE_COMMENT>. ;
<LINE_COMMENT>\n {BEGIN INITIAL;}
<BLOCK_COMMENT>\n ;
<BLOCK_COMMENT>. ;
<BLOCK_COMMENT>"*/" {BEGIN INITIAL;}
<STRING_LITERAL_STATE>\n ;
<STRING_LITERAL_STATE>\\n {
    string_buffer += '\n';
}
<STRING_LITERAL_STATE>\\\" {
    string_buffer += '\"';
}
<STRING_LITERAL_STATE>\" {
    BEGIN INITIAL;
    string temp;
    swap(temp, string_buffer);
    if (string_buffer.empty())
    {
        return Parser::make_STRING_LITERAL(Expression(LITERAL_EXPRESSION, new LiteralExpression(string_t())), loc);
    }
    else
    {
        return Parser::make_STRING_LITERAL(Expression(LITERAL_EXPRESSION, new LiteralExpression(string_t(conv.from_bytes(string_buffer)))), loc);
    }
}
<STRING_LITERAL_STATE>. {
    string_buffer += yytext;
}
%%