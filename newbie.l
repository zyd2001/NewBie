%{
#include "newbie.h"
#include "y.tab.h"

UTF8_String *string_buffer;

char *heredoc_tag;
int yywarp(void)
{
    return 1;
}
void increase_line_number()
{
    nb_get_interpreter()->current_line++;
}
#define yylex lex
%}
%start LINE_COMMENT BLOCK_COMMENT STRING_LITERAL_STATE HEREDOC
%%
<INITIAL>"int"          return INT_T;
<INITIAL>"integer"      return INT_T;
<INITIAL>"double"       return DOUBLE_T;
<INITIAL>"bool"         return BOOL_T;
<INITIAL>"boolean"      return BOOL_T;
<INITIAL>"array"        return ARRAY_T;
<INITIAL>"string"       return STRING_T;
<INITIAL>"if"           return IF;
<INITIAL>"else"         return ELSE;
<INITIAL>"elseif"       return ELSEIF;
<INITIAL>"else if"      return ELSEIF;
<INITIAL>"elif"         return ELSEIF;
<INITIAL>"elsif"        return ELSEIF;
<INITIAL>"for"          return FOR;
<INITIAL>"in"           return IN;
<INITIAL>"break"        return BREAK;
<INITIAL>"continue"     return CONTINUE;
<INITIAL>"return"       return RETURN;
<INITIAL>"class"        return CLASS;
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
<INITIAL>"=="           return EQ_T;
<INITIAL>"!="           return NE_T;
<INITIAL>">"            return GT_T;
<INITIAL>">="           return GE_T;
<INITIAL>"<"            return LT_T;
<INITIAL>"<="           return LE_T;
<INITIAL>"+"            return ADD_T;
<INITIAL>"-"            return SUB_T;
<INITIAL>"*"            return MUL_T;
<INITIAL>"/"            return DIV_T;
<INITIAL>"%"            return MOD_T;
<INITIAL>"+="           return ADD_ASSIGN;
<INITIAL>"-="           return SUB_ASSIGN;
<INITIAL>"*="           return MUL_ASSIGN;
<INITIAL>"/="           return DIV_ASSIGN;
<INITIAL>"%="           return MOD_ASSIGN;
<INITIAL>"++"           return INCREMENT;
<INITIAL>"--"           return DECREMENT;
<INITIAL>"!"            return EXCLAMATION;
<INITIAL>"."            return DOT;
<INITIAL>"true" {       
    yylval.expression = nb_create_literal_expression(BOOL, (char*)1);
    return BOOL_LITERAL;
}
<INITIAL>"false" {       
    yylval.expression = nb_create_literal_expression(BOOL, NULL);
    return BOOL_LITERAL;
}
<INITIAL>[ \t] ;
<INITIAL>\n increase_line_number();
<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
    yylval.identifier = utf8_string_new_wrap(yytext);
    return IDENTIFIER;
}
<INITIAL>[1-9][0-9]*|"0" {
    yylval.expression = nb_create_literal_expression(INT, yytext);
    return INT_LITERAL;
}
<INITIAL>[0-9]+\.[0-9]+ {
    yylval.expression = nb_create_literal_expression(DOUBLE, yytext);
    return DOUBLE_LITERAL;
}
<INITIAL>\" {
    string_buffer = utf8_string_new();
    BEGIN STRING_LITERAL_STATE;
}
<INITIAL>"/*" {BEGIN BLOCK_COMMENT;}
<INITIAL>"//" {BEGIN LINE_COMMENT;}
<INITIAL>"#" {BEGIN LINE_COMMENT;}
<INITIAL>"<<<"[A-Za-z_]+[\r\n]+ {
    heredoc_tag = (char*)malloc(32 * sizeof(char));
    for (int i = strlen(yytext) - 1; i > 0; i--)
    {
        if (yytext[i] == '\n' | yytext[i] == '\r')
            yytext[i] = '\0';
        else
            break;
    }
    strcpy(heredoc_tag, yytext + 3);
    string_buffer = utf8_string_new();
    BEGIN HEREDOC;
}
<HEREDOC>^">>>"[A-Za-z_]+/";" {
    if(!strcmp(heredoc_tag, yytext + 3))
    {
        char *temp = utf8_string_get_value(string_buffer);
        size_t size = strlen(temp);
        for(int i = size - 1; i > 0; i--)
        {
            if (temp[i] == '\n' || temp[i] == '\r')
            {
                temp[i] = '\0';
                // string_buffer->size--;
            }
            else
                break;
        }
        yylval.expression = nb_create_literal_expression(STRING, utf8_string_get_value(string_buffer));
        utf8_string_delete(&string_buffer);
        __free(heredoc_tag);
        BEGIN INITIAL;
        return STRING_LITERAL;
    }
    else
        utf8_string_append(string_buffer, yytext);
}
<HEREDOC>. {
    utf8_string_append(string_buffer, yytext);
}
<HEREDOC>\n {
    utf8_string_append(string_buffer, yytext);
}
<LINE_COMMENT>. ;
<LINE_COMMENT>\n {increase_line_number(); BEGIN INITIAL;}
<BLOCK_COMMENT>\n increase_line_number();
<BLOCK_COMMENT>. ;
<BLOCK_COMMENT>"*/" {BEGIN INITIAL;}
<STRING_LITERAL_STATE>\n increase_line_number();
<STRING_LITERAL_STATE>\\n {
    utf8_string_append(string_buffer, "\\n");
}
<STRING_LITERAL_STATE>\\\" {
    utf8_string_append(string_buffer, "\"");
}
<STRING_LITERAL_STATE>\" {
    yylval.expression = nb_create_literal_expression(STRING, utf8_string_get_value(string_buffer));
    utf8_string_delete(&string_buffer);
    BEGIN INITIAL;
    return STRING_LITERAL;
}
<STRING_LITERAL_STATE>. {
    utf8_string_append(string_buffer, yytext);
}
%%