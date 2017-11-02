#ifndef NEWBIE_DEV
#define NEWBIE_DEV
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

/* 
    to create a builtin function, the signature of the function should be
    NB_Value *(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier))
    and you should have a add_lib() function
    void add_lib(FunctionList **flist, void (*add_func)(FunctionList **flist, int pnum, NB_Value *(*ptr)(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier)), UTF8_String *identifier, char **pname_array, NB_ValueType *ptype), void (*add_val)(NB_Value *val, UTF8_String *identifier))
*/

typedef Value NB_Value;
typedef ValueType NB_ValueType;

typedef struct VariablesList_tag VariablesList;
typedef struct FunctionList_tag FunctionList;

void nb_add_builtin_func(FunctionList **flist, int pnum, NB_Value *(*ptr)(VariablesList *vlist, NB_Value *(*find)(VariablesList *vlist, char *identifier)), UTF8_String *identifier, char **pname_array, NB_ValueType *ptype);
void nb_add_global_variable(NB_Value *val, int various);

#endif