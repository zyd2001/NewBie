%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "y.tab.h"

char *heredoc_tag = (char*)malloc(32 * sizeof(char));
int yywarp(void)
{
    return 1;
}
%}
%start LINE_COMMENT BLOCK_COMMENT STRING_LITERAL_STATE HEREDOC
%%
<INITIAL>"int"          return INT_T;
<INITIAL>"double"       return DOUBLE_T;
<INITIAL>"array"        return ARRAY_T;
<INITIAL>"array_assoc"  return ARRAY_ASSOC_T;
<INITIAL>"string"       return STRING_T;
<INITIAL>"if"           return IF;
<INITIAL>"else"         return ELSE;
<INITIAL>"elseif"       return ELSEIF;
<INITIAL>"for"          return FOR;
<INITIAL>"break"        return BREAK;
<INITIAL>"continue"     return CONTINUE;
<INITIAL>"return"       return RETURN;
<INITIAL>"class"        return CLASS;
<INITIAL>"require"      return REQUIRE;
<INITIAL>"("            return LP;
<INITIAL>")"            return RP;
<INITIAL>"{"            return LC;
<INITIAL>"}"            return RC;
<INITIAL>"["            return LB;
<INITIAL>"]"            return RB;
<INITIAL>";"            return SEMICOLON;
<INITIAL>","            return COMMA;
<INITIAL>"&&"           return LOGICAL_AND;
<INITIAL>"OR"           return LOGICAL_AND;
<INITIAL>"||"           return LOGICAL_OR;
<INITIAL>"AND"          return LOGICAL_OR;
<INITIAL>"="            return ASSIGN_T;
<INITIAL>"=="           return EQ;
<INITIAL>"!="           return NE;
<INITIAL>">"            return GT;
<INITIAL>">="           return GE;
<INITIAL>"<"            return LT;
<INITIAL>"<="           return LE;
<INITIAL>"+"            return ADD;
<INITIAL>"-"            return SUB;
<INITIAL>"*"            return MUL;
<INITIAL>"/"            return DIV;
<INITIAL>"%"            return MOD;
<INITIAL>"+="           return ADD_ASSIGN;
<INITIAL>"-="           return SUB_ASSIGN;
<INITIAL>"*="           return MUL_ASSIGN;
<INITIAL>"/="           return DIV_ASSIGN;
<INITIAL>"%="           return MOD_ASSIGN;
<INITIAL>"++"           return INCREMENT;
<INITIAL>"--"           return DECREMENT;
<INITIAL>"!"            return EXCLAMATION;
<INITIAL>"."            return DOT;
<INITIAL>[ \t] ;
<INITIAL>\n increase_line_number();
<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
    yylval.identifier = yytext;
    return IDENTIFIER;
}
<INITIAL>[1-9][0-9]*|"0" {return INT_LITERAL;}
<INITIAL>[0-9]+\.[0-9]+ {return DOUBLE_LITERAL;}
<INITIAL>\" {BEGIN STRING_LITERAL_STATE;}
<INITIAL>"/*" {BEGIN BLOCK_COMMENT;}
<INITIAL>\\\\ {BEGIN LINE_COMMENT;}
<INITIAL>"<<<"[A-Za-z_]+ {
    strcpy(heredoc_tag, yytext + 3);
    BEGIN HEREDOC;
}
<HEREDOC>">>>"[A-Za-z_]+ {
    if(!strcmp(heredoc_tag, yytext + 3))
    {
        BEGIN INITIAL;
    }
}
<LINE_COMMENT>\n {BEGIN INITIAL;}
<BLOCK_COMMENT>\n increase_line_number();
<BLOCK_COMMENT>"*/" {BEGIN INITIAL;}
<STRING_LITERAL_STATE>\n increase_line_number();
<STRING_LITERAL_STATE>\\n ;
<STRING_LITERAL_STATE>\\ ;
<STRING_LITERAL_STATE>\\\" ;
<STRING_LITERAL_STATE>\" BEGIN INITIAL;
%%