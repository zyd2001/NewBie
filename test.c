#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <iconv.h>
#include <locale.h>
#include <wchar.h>
// #include "utility.h"
#define LEN 255

// typedef Value NB_Value;
// typedef ValueType NB_ValueType;

int main(int argc, char *argv[])  
{
    char gbk[LEN];
    char utf8[LEN];
    FILE *file = fopen("input", "r");
    fgets(gbk, LEN, file);
    // convert(gbk, strlen(gbk), utf8, LEN, "gbk", "utf-8");
    printf("%s", utf8);
}

int convert(char *instr, int inlen, char *outstr, int outlen, const char *to, const char *from)
{
    iconv_t cd = iconv_open(to, from);
    char **inbuf = &instr;
    char **outbuf = &outstr;
    size_t in = inlen;
    size_t out = outlen;
    iconv(cd, inbuf, &in, outbuf, &out);
    iconv_close(cd);
    return 1;
}

// int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen)
// {
// iconv_t cd;
// int rc;
// char **pin = &inbuf;
// char **pout = &outbuf;

// cd = iconv_open(to_charset,from_charset);
// if (cd==0) return -1;
// memset(outbuf,0,outlen);
// if (iconv(cd,pin,&inlen,pout,&outlen)==-1) return -1;
// iconv_close(cd);
// return 0;
// }
// //UNICODE码转为GB2312码
// int u2g(char *inbuf,int inlen,char *outbuf,int outlen)
// {
// return code_convert("utf-8","gb2312",inbuf,inlen,outbuf,outlen);
// }
// //GB2312码转为UNICODE码
// int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
// {
// return code_convert("gbk","utf-8",inbuf,inlen,outbuf,outlen);
// }
