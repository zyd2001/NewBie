#ifndef INCLUDED_UTILITY_HEAD
#define INCLUDED_UTILITY_HEAD

typedef struct String_tag {
    char* value;
    int size;
    int limit;
    int length;
} String;

String *string_new();
String *string_append(String *str, char *new);
// return NULL
void *string_delete(String *str);
int string_compare(String *first, String *second);
String *string_reassign(String *str, char *new);
String *string_copy(String *destination, String *source);

#endif