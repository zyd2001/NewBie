#ifndef INCLUDED_UTILITY_HEAD
#define INCLUDED_UTILITY_HEAD

#define __free(ptr) do {free(ptr);ptr = NULL;}while(0)

typedef struct Value_tag Value;

typedef struct Array_tag Array;

typedef struct UTF8_String_tag UTF8_String;

// typedef struct Wide_String_tag Wide_String;

typedef struct UTF32_String_tag UTF32_String;

typedef enum ValueType_tag ValueType;

size_t encoding_convert(char *instr, int inlen, char *outstr, int outlen, const char *to, const char *from);
int utf8_strlen(char *str);
UTF8_String *utf8_string_new();
// UTF8_String *utf8_string_new_wrap(char *str);
#define utf8_string_new_wrap(str) utf8_string_append(utf8_string_new(), str) // char *str
UTF8_String *utf8_string_new_char(char ch);
UTF8_String *utf8_string_append(UTF8_String *str, char *new);
// return NULL
void *utf8_string_delete_func(UTF8_String **str, ...);
#define utf8_string_delete(...) utf8_string_delete_func(__VA_ARGS__, NULL) // UTF8_STRING **str
int utf8_string_compare(UTF8_String *first, UTF8_String *second);
UTF8_String *utf8_string_reassign(UTF8_String *str, char *new);
UTF8_String *utf8_string_copy(UTF8_String *destination, UTF8_String *source);
UTF8_String *utf8_string_substring(UTF8_String *str, int start, int end);
#define utf8_string_substr(str, start, length) utf8_string_substring(str, start, start + length); // UTF8_STRING **str
char utf8_string_get_char_ascii(UTF8_String *str, int index);
UTF8_String *utf8_string_get_char(UTF8_String *str, int index);
#define utf8_string_get_char(str, index) utf8_string_substring(str, index, index + 1); // UTF8_STRING **str
UTF8_String *utf8_string_append_char(UTF8_String *str, char ch);
int utf8_string_indexof(UTF8_String *str, char *target);
int utf8_string_test_indexof(UTF8_String *str, UTF8_String *target); //这个贼J8傻逼，就测试用的
char *utf8_string_get_value(UTF8_String *str);
int utf8_string_get_length(UTF8_String *str);

/* Deprecated since low compatibility in Windows and Linux(Different byte size)*/
// wchar_t *utf8_to_wcs(char *str); //need to be freed after use
// Wide_String *wide_string_append(Wide_String *str, wchar_t *new); 
// Wide_String *wide_string_new();
// Wide_String *wide_string_new_wrap(wchar_t *str);
// Wide_String *wide_string_new_wrap_mbs(char *str);
// Wide_String *wide_string_new_char(wchar_t ch);
// Wide_String *wode_string_append_char(Wide_String *str, wchar_t ch);
// void *wide_string_delete(Wide_String *str);
/* Deprecated */

UTF32_String *utf8_to_utf32(char *str);
UTF32_String *utf32_string_new();
// UTF32_String *utf32_string_new_wrap(char *str, size_t new_size);
#define utf32_string_new_wrap(str, new_size) utf32_string_append(utf32_string_new(), str, new_size) // char *str, size_t new_size
// UTF32_String *utf32_string_new_wrap_utf32(UTF32_String *str);
#define utf32_string_new_wrap_utf32(str) utf32_string_append_utf32(utf32_string_new(), str) // UTF32_String *str
// UTF32_String *utf32_string_new_wrap_utf8(char *str);
#define utf32_string_new_wrap_utf8(str) utf32_string_append_free(utf32_string_new(), utf8_to_utf32(str)) // char *str
UTF32_String *utf32_string_append(UTF32_String *str, char *new, size_t new_size);
UTF32_String *utf32_string_append_utf32(UTF32_String *str, UTF32_String *new);
UTF32_String *utf32_string_append_free(UTF32_String *str, UTF32_String *new);
// UTF32_String *utf32_string_append_utf8(UTF32_String *str, char *new);
#define utf32_string_append_utf8(str, new) utf32_string_append_free(str, utf32_string_new_wrap_utf8(new)) // UTF32_String *str, char *new
UTF32_String *utf32_string_reassign_utf8(UTF32_String *str, char *new);
int utf32_string_compare(char *first, size_t size1, char *second, size_t size2);
int utf32_string_compare_utf32(UTF32_String *first, UTF32_String *second);
UTF32_String *utf32_string_copy(UTF32_String *destination, UTF32_String *source);
UTF32_String *utf32_string_substring(UTF32_String *str, int start, int end);
#define utf32_string_substring(str, start, end) utf32_string_substr(str, start, end - start) // UTF32_String *str, int start, int end
UTF32_String *utf32_string_substr(UTF32_String *str, int start, int length);
int utf32_string_indexof(UTF32_String *str, char *target, size_t size);
int utf32_string_indexof_utf32(UTF32_String *str, UTF32_String *target);
int utf32_string_indexof_utf8(UTF32_String *str, char *target);
size_t utf32_string_print(UTF32_String *str);
void *utf32_string_delete_func(UTF32_String **str, ...);
#define utf32_string_delete(...) utf32_string_delete_func(__VA_ARGS__, NULL)

Value *value_new(ValueType type);
void *value_delete_func(Value **val, ...);
#define value_delete(...) value_delete_func(__VA_ARGS__, NULL)
Value *value_copy(Value *destination, Value *source);

Array *array_new();
void *array_delete_func(Array **arr, ...);
#define array_delete(...) array_delete_func(__VA_ARGS__, NULL)
Array *array_push(Array *arr, Value *value);
Value *array_get(Array *arr, int index);
Array *array_insert(Array *arr, Value *val, int index);
Value *array_remove(Array *arr, int index);
Value *array_pop(Array *arr);
Array *array_copy(Array *destination, Array *source);

#endif