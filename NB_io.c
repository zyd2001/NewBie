#include "NewBie_Dev.h"

NB_Value *print(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *identifier = "str";
    NB_Value *found = find(vlist, identifier);
    UTF32_String *str = get_string_value(found);
    utf32_string_print(str);
    utf32_string_delete(&str);
    return value_new();
}

NB_Value *println(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *identifier = "str";
    NB_Value *found = find(vlist, identifier);
    UTF32_String *str = get_string_value(found);
    utf32_string_print(str);
    printf("%c", '\n');
    utf32_string_delete(&str);
    return value_new();
}

char *readline()
{
    char ch, *ret = (char*)malloc(50 * sizeof(char));
    int i = 1;
    for (;;i++)
    {
        if ((i % 50) == 1)
            ret = (char*)realloc(ret, (i + 50) * sizeof(char));
        ch = getchar();
        if (ch != EOF && ch != '\n')
            ret[i - 1] = ch;
        else
            break;
    }
    if ((i % 50) != 1)
        ret[i - 1] = '\0';
    return ret;
}

NB_Value *readln(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *identifier = "prompt";
    NB_Value *found = find(vlist, identifier);
    utf32_string_print(found->value.string_value);
    char *ret = readline();
    NB_Value *val = value_new();
    val->type = STRING;
    val->value.string_value = utf32_string_new_wrap_utf8(ret);
    __free(ret);
    return val;
}

void add_lib(FunctionList **flist, void (*add_func)(FunctionList **flist, int pnum, NB_Value *(*ptr)(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier)), UTF8_String *identifier, NB_ValueType type, char **pname_array, NB_ValueType *ptype), void (*add_val)(NB_Value *val, UTF8_String *identifier))
{
    add_func(flist, 1, print, utf8_string_new_wrap("print"), INT, (char*[]){"str"}, (NB_ValueType[]){STRING});
    add_func(flist, 1, println, utf8_string_new_wrap("println"), INT, (char*[]){"str"}, (NB_ValueType[]){STRING});
    add_func(flist, 1, readln, utf8_string_new_wrap("readln"), STRING, (char*[]){"prompt"}, (NB_ValueType[]){STRING});
}