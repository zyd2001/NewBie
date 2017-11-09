#include "NewBie_Dev.h"
#include <time.h>
#define PCRE2_CODE_UNIT_WIDTH 32
#include <pcre2.h>

NB_Value *toInt(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *p1 = "var";
    NB_Value *val = find(vlist, p1);
    int i = get_int_value(val);
    NB_Value *ret = value_new_type(INT);
    ret->value.int_value = i;
    return ret;
}

NB_Value *toDouble(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *p1 = "var";
    NB_Value *val = find(vlist, p1);
    double d = get_double_value(val);
    NB_Value *ret = value_new_type(DOUBLE);
    ret->value.double_value = d;
    return ret;
}

NB_Value *getType(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *p1 = "var";
    NB_Value *val = find(vlist, p1), *ret = value_new();
    ret->type = STRING;
    switch (val->type)
    {
        case INT:
            ret->value.string_value = utf32_string_new_wrap_utf8("int");
            break;
        case BOOL:
            ret->value.string_value = utf32_string_new_wrap_utf8("bool");
            break;
        case DOUBLE:
            ret->value.string_value = utf32_string_new_wrap_utf8("double");
            break;
        case STRING:
            ret->value.string_value = utf32_string_new_wrap_utf8("string");
            break;
        case ARRAY:
            ret->value.string_value = utf32_string_new_wrap_utf8("array");
            break;
    }
    return ret;
}

NB_Value *range(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    NB_Value *val1 = find(vlist, "num1");
    NB_Value *val2 = find(vlist, "num2");
    NB_Value *ret = value_new_type(ARRAY), *new = value_new_type(INT);
    for (int i = val1->value.int_value; i <= val2->value.int_value; i++)
    {
        new->value.int_value = i;
        array_push(ret->value.array_value, new);
    }
    value_delete(&new);
    return ret;
}

NB_Value *regex(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    NB_Value *val1 = find(vlist, "subject");
    NB_Value *val2 = find(vlist, "pattern");
    NB_Value *ret = value_new_type(STRING);
    PCRE2_SPTR subject = (PCRE2_SPTR)utf32_string_get_value(val1->value.string_value);
    PCRE2_SPTR pattern = (PCRE2_SPTR)utf32_string_get_value(val2->value.string_value);

    int errorcode;
    PCRE2_SIZE erroroffset;
    pcre2_code *re = pcre2_compile(pattern, utf32_string_get_length(val2->value.string_value), PCRE2_UTF, &errorcode, &erroroffset, NULL);
    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(re, NULL);
    int rc = pcre2_match(re, subject, utf32_string_get_length(val1->value.string_value), 0, 0, match_data, NULL);
    if (rc == PCRE2_ERROR_NOMATCH)
    {
        pcre2_code_free(re);
        pcre2_match_data_free(match_data);
        return ret;
    }
    PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(match_data);
    utf32_string_append_free(ret->value.string_value, utf32_string_substring(val1->value.string_value, ovector[0], ovector[1]));
    pcre2_code_free(re);
    pcre2_match_data_free(match_data);
    return ret;
}

NB_Value *regex_replace(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{

}

NB_Value *nb_time(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    NB_Value *ret = value_new_type(INT);
    ret->value.int_value = (int)time(NULL);
    return ret;
}

NB_Value *shell(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
}

void add_lib(FunctionList **flist, void (*add_func)(FunctionList **flist, int pnum, NB_Value *(*ptr)(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier)), UTF8_String *identifier, NB_ValueType type, char **pname_array, NB_ValueType *ptype), void (*add_val)(NB_Value *val, UTF8_String *identifier))
{
    add_func(flist, 1, toInt, utf8_string_new_wrap("toInt"), INT, (char*[]){"var"}, (NB_ValueType[]){VARIOUS});
    add_func(flist, 1, toDouble, utf8_string_new_wrap("toDouble"), DOUBLE, (char*[]){"var"}, (NB_ValueType[]){VARIOUS});
    add_func(flist, 1, getType, utf8_string_new_wrap("getType"), STRING, (char*[]){"var"}, (NB_ValueType[]){VARIOUS});
    add_func(flist, 2, range, utf8_string_new_wrap("range"), STRING, (char*[]){"num1", "num2"}, (NB_ValueType[]){INT, INT});
    add_func(flist, 2, regex, utf8_string_new_wrap("regex"), STRING, (char*[]){"subject", "pattern"}, (NB_ValueType[]){STRING, STRING});
    add_func(flist, 0, nb_time, utf8_string_new_wrap("time"), INT, (char*[]){}, (NB_ValueType[]){});
}