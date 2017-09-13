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
char heredoc_tag[32];
%}
%start HEREDOC
%%
<INITIAL>int printf("int_T\n");
<INITIAL>[A-Za-z_]+ printf("identifier\n");
<INITIAL>== printf("eq");
<INITIAL>\n {printf("new line\n");}
<INITIAL>[0-9] {printf("number %s\n", yytext);}
<INITIAL>"<<<"[A-Za-z_]+[\r\n]+ {
    for (int i = strlen(yytext) - 1; i > 0; i--)
    {
        if (yytext[i] == '\n' | yytext[i] == '\r')
            yytext[i] = '\0';
        else
            break;
    }
    strcpy(heredoc_tag, yytext + 3);
    printf("HEREDOC\n");
    string_buffer = (char*)malloc(16 * sizeof(char));
    BEGIN HEREDOC;
}
<HEREDOC>">>>"[A-Za-z_]+";" {
    yytext[strlen(yytext)-1] = '\0';
    if(!strcmp(heredoc_tag, yytext + 3))
    {
        printf("%s\n", string_buffer);
        BEGIN INITIAL;
    }
}
<HEREDOC>.* {
    printf("%s\n", yytext);
    strcpy(string_buffer, yytext);
    printf("%s\n", string_buffer);
    printf("%p\n", string_buffer);    
}
<HEREDOC>[\n\r] {
    // printf("new line\n");
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