#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
int my_strlen_utf8_c(char *s) {
    int i = 0, j = 0;
    while (s[i]) {
      if ((s[i] & 0xc0) != 0x80) j++;
      i++;
    }
    return j;
  }
int main(int argc, char *argv[])  
{  
    fprintf(stdout, "中文测试\n");  
    printf("中文测试\n");
    char *str = "1234", *s = (char*)malloc(100 * sizeof(char));
    strcpy(s, str+3);
    printf("%p\n", (int)str);
    printf("%p\n", (int)s);
    printf("%s\n", s);
    printf("%d\n", (int)strlen(str));
    printf("%d\n", (int)sizeof(str));
    printf("%d\n", my_strlen_utf8_c(str));
    // int i = 0;
    // for (i = 0; i < strlen(str); i++)
    // {
    //     printf("%o\n", str[i]);
    // }
    printf("%s\n", str);
}  