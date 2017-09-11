%{
#include <stdio.h>
#include <string.h>
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
<INITIAL>"<<<".+ {
    printf("match %s\n", yytext+3);
    strcpy(heredoc_tag, yytext+3);
    printf("heredoc_tag %s\n", heredoc_tag);  
    BEGIN HEREDOC;  
}
<HEREDOC>">>>".+ {
    if (!strcmp(heredoc_tag, yytext + 3))
    {
        BEGIN INITIAL;
    }
}
<HEREDOC>.+ printf("heredoc %s", yytext);
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