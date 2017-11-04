# NewBie

A simple interpreted programming language.

# Compile

**mingw is required for Windows to compile**

First change the `OUT_PUT_ENCODING` macro in utility.c to `utf-8`, `gbk`, for `Linux` and `Windows` respectively.

Then run ./compile.sh or ./compile.bat

Rename NewBie_Linux.ini or NewBie_Win.ini to NewBie.ini respectively.

Or you can just download the released archive for both Linux and Windows

# Grammer

## Loop

`for (int i = 0; i < 1; i++){}` C-like

`for/foreach (x in arr){}` Foreach

no while

## Conditional Statememnt

`if (expression){}` if

`if (exp){} else{}` if-else

`elseif / elsif / else if / elif` else if()

## Variable Declaration

`int double boolean/bool string array` static type

`var` dynamic type

## 函数

`int double boolean/bool string array` static type

`func function` dynamic type

# builtin-func

**gradually adding more**

most math functions

`string readln(string str)` 

`int print(string str)` 

`int println(string str)` 
 
`int toInt(var v)` 
 
`double toDouble(var v)` 
  
`string getType(var v)` 
   
`array range(int i, int j)`