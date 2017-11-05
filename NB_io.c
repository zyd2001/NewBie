#include "NewBie_Dev.h"
#include <string.h>

// static struct File
// {
//     FILE *fp;
//     struct File *next;
// } *FileList = NULL;

NB_Value *print(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *identifier = "str";
    NB_Value *found = find(vlist, identifier);
    UTF32_String *str = get_string_value(found);
    utf32_string_print(str, stdout);
    utf32_string_delete(&str);
    return value_new();
}

NB_Value *println(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *identifier = "str";
    NB_Value *found = find(vlist, identifier);
    UTF32_String *str = get_string_value(found);
    utf32_string_print(str, stdout);
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
    utf32_string_print(found->value.string_value, stdout);
    char *ret = readline();
    NB_Value *val = value_new();
    val->type = STRING;
    val->value.string_value = utf32_string_new_wrap_utf8(ret);
    __free(ret);
    return val;
}

// NB_Value *open(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
// {
//     char *identifier = "file";
//     NB_Value *file = find(vlist, identifier);
//     NB_Value *ret = value_new_type(INT);
//     char *filename = utf32_to_utf8(file->value.string_value);
//     int index = 0;
//     struct File *temp = FileList;
//     for (;temp->next != NULL; temp = temp->next)
//         index++;
//     temp->next = (struct File*)malloc(sizeof(struct File));
//     temp->next->fp = fopen(filename, "r+");
//     __free(filename);
//     ret->value.int_value = index + 1;
//     return ret;
// }

// NB_Value *close(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
// {
//     char *identifier = "handle";
//     NB_Value *handle = find(vlist, identifier);
//     NB_Value *ret = value_new_type(BOOL);
//     struct File *temp = FileList;    
//     for (int i = 0; i < handle->value.int_value; i++)
//         temp = temp->next;
//     fclose(temp->fp);
//     ret->value.int_value = 1;
//     return ret;
// }

NB_Value *file_get_contents(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    NB_Value *identifier = find(vlist, "file");
    char *file = utf32_to_utf8(identifier->value.string_value);
    FILE *fp = fopen(file, "rb");
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    rewind(fp);
    char *buf = (char*)malloc((size + 1) * sizeof(char));
    fread(buf, sizeof(char), size, fp);
    buf[size] = '\0';
    NB_Value *ret = value_new_type(STRING);
    utf32_string_append_utf8(ret->value.string_value, buf);
    fclose(fp);
    __free(buf);
    __free(file);
    return ret;
}

NB_Value *file_put_contents(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    NB_Value *val1 = find(vlist, "file");    
    NB_Value *val2 = find(vlist, "str");    
    char *file = utf32_to_utf8(val1->value.string_value);
    char *str = utf32_to_utf8(val2->value.string_value);
    FILE *fp = fopen(file, "wb");
    fwrite(str, sizeof(char), strlen(str), fp);
    fclose(fp);
    __free(file);
    __free(str);
    return value_new();
}

void add_lib(FunctionList **flist, void (*add_func)(FunctionList **flist, int pnum, NB_Value *(*ptr)(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier)), UTF8_String *identifier, NB_ValueType type, char **pname_array, NB_ValueType *ptype), void (*add_val)(NB_Value *val, UTF8_String *identifier))
{
    add_func(flist, 1, print, utf8_string_new_wrap("print"), INT, (char*[]){"str"}, (NB_ValueType[]){STRING});
    add_func(flist, 1, println, utf8_string_new_wrap("println"), INT, (char*[]){"str"}, (NB_ValueType[]){STRING});
    add_func(flist, 1, readln, utf8_string_new_wrap("readln"), STRING, (char*[]){"prompt"}, (NB_ValueType[]){STRING});
    add_func(flist, 1, file_get_contents, utf8_string_new_wrap("file_get_contents"), STRING, (char*[]){"file"}, (NB_ValueType[]){STRING});
    add_func(flist, 2, file_put_contents, utf8_string_new_wrap("file_put_contents"), INT, (char*[]){"file", "str"}, (NB_ValueType[]){STRING, STRING});
}