#ifndef CSTRING_H
#define CSTRING_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct cstring String;

/* initialize container with \\0 on index 0 */
/* @param init_cap initial capacity of container */
/* @return empty container */
String* cs_init(size_t init_cap);

/* create container from raw string */
/* @param raw char* of char[] */
/* @return container with data from raw and closed with \\0 */
String* cs_create(const char* raw);

/* string length getter */
/* @param self string container */
/* @return copy of length field */
size_t cs_length(const String* self);

/* string capacity getter */
/* @param self string container */
/* @return copy of capacity field */
size_t cs_capacity(const String* self);

/* string text getter */
/* @param self string container */
/* @return readonly representation of raw text field */
const char* cs_raw(const String* self);

/* free string's memory */
/* @param self string container */
void cs_free(String* self);

/* for access to raw field by index */
/* @param self string container */
/* @param index index in char array */
/* @return char by index of -1, if index was out of range */
char cs_get(const String* self, size_t index);

/* for access to raw field by index */
/* @param self string container */
/* @param item character */
/* @param index index in char array */
void cs_set(const String* self, char item, size_t index);

/* copy of string */
/* @param self string container */
/* @return cloned string */
String* cs_clone(const String* self);

/* compares string with raw char* */
/* @param str string */
/* @param raw char array */
/* @param ignore_case ignore args case */
/* @return size_t that indicates arg2 position in the sort order */
int64_t cs_compare(const String* str, const char* raw, bool ignore_case);

/* concatenates string with raw char* */
/* @param str string */
/* @param raw char array */
void cs_concat(String* str, const char* raw);

/* check if string contains substring */
/* @param str string */
/* @param raw char array to seek */
/* @return true if the value occurs within this string, otherwise false. */
bool cs_contains(String* str, const char* value);

/* find the index of substring in string */
/* @param str string */
/* @param raw char array to seek */
/* @return non negative value if string contains substring, otherwise -1 */
int64_t cs_indexof(String* str, const char* value);

/* find the index of substring in string */
/* @param str string */
/* @param raw char array to seek */
/* @return non negative value if string contains substring, otherwise -1 */
int64_t cs_indexof(String* str, const char* value);

/* find the index of last substring in string */
/* @param str string */
/* @param raw char array to seek */
/* @return non negative value if string contains substring, otherwise -1 */
int64_t cs_indexof_last(String* str, const char* value);

/* find the index of the H-th substring */
/* @param str string */
/* @param raw char array to seek */
/* @return non negative value if string contains substring, otherwise -1 */
int64_t cs_indexof_any(String* str, const char* value, size_t start_index);

#endif