#include "NewBie_Dev.h"
#include <math.h>

NB_Value *nb_sin(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *p1 = "num";
    NB_Value *val = find(vlist, p1);
    NB_Value *ret = value_new_type(DOUBLE);
    ret->value.double_value = sin(val->value.double_value);
    return ret;
}

NB_Value *nb_cos(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *p1 = "num";
    NB_Value *val = find(vlist, p1);
    NB_Value *ret = value_new_type(DOUBLE);
    ret->value.double_value = cos(val->value.double_value);
    return ret;
}

NB_Value *nb_tan(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *p1 = "num";
    NB_Value *val = find(vlist, p1);
    NB_Value *ret = value_new_type(DOUBLE);
    ret->value.double_value = tan(val->value.double_value);
    return ret;
}

NB_Value *nb_asin(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *p1 = "num";
    NB_Value *val = find(vlist, p1);
    NB_Value *ret = value_new_type(DOUBLE);
    ret->value.double_value = asin(val->value.double_value);
    return ret;
}

NB_Value *nb_acos(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *p1 = "num";
    NB_Value *val = find(vlist, p1);
    NB_Value *ret = value_new_type(DOUBLE);
    ret->value.double_value = acos(val->value.double_value);
    return ret;
}

NB_Value *nb_atan(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *p1 = "num";
    NB_Value *val = find(vlist, p1);
    NB_Value *ret = value_new_type(DOUBLE);
    ret->value.double_value = atan(val->value.double_value);
    return ret;
}

NB_Value *nb_pow(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *p1 = "num1", *p2 = "num2";
    NB_Value *val1 = find(vlist, p1);
    NB_Value *val2 = find(vlist, p2);
    NB_Value *ret = value_new_type(DOUBLE);
    ret->value.double_value = pow(val1->value.double_value, val2->value.double_value);
    return ret;
}

NB_Value *nb_sqrt(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *p1 = "num";
    NB_Value *val = find(vlist, p1);
    NB_Value *ret = value_new_type(DOUBLE);
    ret->value.double_value = sqrt(val->value.double_value);
    return ret;
}

NB_Value *nb_cbrt(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *p1 = "num";
    NB_Value *val = find(vlist, p1);
    NB_Value *ret = value_new_type(DOUBLE);
    ret->value.double_value = cbrt(val->value.double_value);
    return ret;
}

NB_Value *nb_log(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
{
    char *p1 = "num", *p2 = "base";
    NB_Value *val1 = find(vlist, p1);
    NB_Value *val2 = find(vlist, p2);
    NB_Value *ret = value_new_type(DOUBLE);
    ret->value.double_value = log(val1->value.double_value) / log(val2->value.double_value);
    return ret;
}

void add_lib(FunctionList **flist, void (*add_func)(FunctionList **flist, int pnum, NB_Value *(*ptr)(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier)), UTF8_String *identifier, char **pname_array, NB_ValueType *ptype), void (*add_val)(NB_Value *val, UTF8_String *identifier))
{
    add_func(flist, 1, nb_sin, utf8_string_new_wrap("sin"), (char*[]){"num"}, (NB_ValueType[]){DOUBLE});
    add_func(flist, 1, nb_cos, utf8_string_new_wrap("cos"), (char*[]){"num"}, (NB_ValueType[]){DOUBLE});
    add_func(flist, 1, nb_tan, utf8_string_new_wrap("tan"), (char*[]){"num"}, (NB_ValueType[]){DOUBLE});
    add_func(flist, 1, nb_acos, utf8_string_new_wrap("acos"), (char*[]){"num"}, (NB_ValueType[]){DOUBLE});
    add_func(flist, 1, nb_asin, utf8_string_new_wrap("asin"), (char*[]){"num"}, (NB_ValueType[]){DOUBLE});
    add_func(flist, 1, nb_atan, utf8_string_new_wrap("atan"), (char*[]){"num"}, (NB_ValueType[]){DOUBLE});
    add_func(flist, 2, nb_pow, utf8_string_new_wrap("pow"), (char*[]){"num1", "num2"}, (NB_ValueType[]){DOUBLE, DOUBLE});
    add_func(flist, 1, nb_sqrt, utf8_string_new_wrap("sqrt"), (char*[]){"num"}, (NB_ValueType[]){DOUBLE});
    add_func(flist, 1, nb_cbrt, utf8_string_new_wrap("cbrt"), (char*[]){"num"}, (NB_ValueType[]){DOUBLE});
    add_func(flist, 2, nb_log, utf8_string_new_wrap("log"), (char*[]){"base", "num"}, (NB_ValueType[]){DOUBLE, DOUBLE});
    NB_Value *E = value_new_type(DOUBLE);
    E->value.double_value = 2.718281828459;
    NB_Value *PI = value_new_type(DOUBLE);
    PI->value.double_value = 3.1415926535898;
    add_val(E, utf8_string_new_wrap("E"));
    add_val(PI, utf8_string_new_wrap("PI"));
}