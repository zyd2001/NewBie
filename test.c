#include <stdio.h>  
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
    char *str = u8"中文测试asd";
    printf("%d\n", (int)strlen(str));
    printf("%d\n", my_strlen_utf8_c(str));
    // int i = 0;
    // for (i = 0; i < strlen(str); i++)
    // {
    //     printf("%o\n", str[i]);
    // }
    printf("%s\n", str);
}  