%{
#include <stdio.h>
#include <string.h>
#include "utility.h"
int my_strlen_utf8_c(char *s) {
    int i = 0, j = 0;
    while (s[i]) {
      if ((s[i] & 0xc0) != 0x80) j++;
      i++;
    }
    return j;
  }
int yywrap()
{
    return 1;
}
String *string_buffer;
char heredoc_tag[32];
%}
%start HEREDOC STRING_LITERAL_STATE
%%
<INITIAL>";" printf("terminate");
<INITIAL>int printf("int_T\n");
<INITIAL>[A-Za-z_]+ printf("identifier\n");
<INITIAL>== printf("eq");
<INITIAL>\n {
    //printf("new line\n");
}
<INITIAL>[0-9] {printf("number %s\n", yytext);}
<INITIAL>\" {
    printf("string\n");
    string_buffer = string_new();
    BEGIN STRING_LITERAL_STATE;
}
<STRING_LITERAL_STATE>\\n {
    string_append(string_buffer, "\n");
}
<STRING_LITERAL_STATE>\\\" {
    string_append(string_buffer, "\"");
}
<STRING_LITERAL_STATE>\" {
    printf("%s", string_buffer->value);
    string_buffer = string_delete(string_buffer);
    BEGIN INITIAL;
}
<STRING_LITERAL_STATE>. {
    string_append(string_buffer, yytext);
}
<INITIAL>"<<<"[A-Za-z_]+[\r\n]+ {
    for (int i = strlen(yytext) - 1; i > 0; i--)
    {
        if (yytext[i] == '\n' | yytext[i] == '\r')
            yytext[i] = '\0';
        else
            break;
    }
    strcpy(heredoc_tag, yytext + 3);
    string_buffer = string_new();
    BEGIN HEREDOC;
}
<HEREDOC>^">>>"[A-Za-z_]+/";" {
    // expression_type = STRING;
    // for(int i = 0; i < strlen(yytext); i++)
    // {
    //     printf("%d ", yytext[i]);
    // }
    // printf("terminate\n");
    // yytext[strlen(yytext)-1] = '\0';
    if(!strcmp(heredoc_tag, yytext + 3))
    {
        for(int i = string_buffer->size - 1; i > 0; i--)
        {
            if (string_buffer->value[i] == '\n' || string_buffer->value[i] == '\r')
            {
                string_buffer->value[i] = '\0';
                string_buffer->size--;
            }
            else
                break;
        }
        // yylval.expression = create_value_expression(expression_type, string_buffer);
        printf("%d", string_buffer->size);
        printf("%s", string_buffer->value);
        string_buffer = string_delete(string_buffer);
        BEGIN INITIAL;
        // return STRING_LITERAL;
    }
    else
    {
        string_append(string_buffer, yytext);
    }
}
<HEREDOC>. {
    // for(int i = 0; i < strlen(yytext); i++)
    // {
    //     printf("%d ", yytext[i]);
    // }
    // printf("...\n");
    string_append(string_buffer, yytext);
}
<HEREDOC>\n {
    // for(int i = 0; i < strlen(yytext); i++)
    // {
    //     printf("%d ", yytext[i]);
    // }
    // printf("line\n");
    string_append(string_buffer, yytext);
}
<INITIAL>\\ {printf("slash\n");}
<INITIAL>\\\" {printf("quote\n");}
<INITIAL>\\n {printf("\\n\n");}
<INITIAL>[\t ];
<INITIAL>. ;
%%

int main(int argc, char **argv)
{
    FILE *fp;
    fp = fopen(argv[1], "r");
    yyin = fp;
    yylex();
}