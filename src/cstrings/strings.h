#ifndef CSTRING_H
#define CSTRING_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct cstring String;

/* initialize string with \\0 on index 0 */
/* @param init_cap initial capacity of string */
/* @return empty string */
String* cs_init(size_t init_cap);

/* create string from raw char pointer */
/* @param raw char array */
/* @return string with data from raw and closed with \\0 */
String* cs_create(const char* raw);

/* string length getter */
/* @param self string */
/* @return copy of length field */
size_t cs_length(const String* self);

/* string capacity getter */
/* @param self string */
/* @return copy of capacity field */
size_t cs_capacity(const String* self);

/* string text getter */
/* @param self string */
/* @return readonly representation of raw text field */
const char* cs_raw(const String* self);

/* free string's memory */
/* @param self string */
void cs_free(String* self);

/* for access to raw field by index */
/* @param self string */
/* @param index index in char array */
/* @return char by index or -1, if index was out of range */
char cs_get(const String* self, size_t index);

/* for access to raw field by index */
/* @param self string */
/* @param item character */
/* @param index index in char array */
void cs_set(const String* self, char item, size_t index);

/* copy of string */
/* @param self string */
/* @return cloned string */
String* cs_clone(const String* self);

/* compares string text field with raw char array */
/* @param str string */
/* @param value char array */
/* @param ignore_case ignore args case */
/* @return integer that indicates args position in the sort order */
int64_t cs_compare(const String* str, const char* raw, bool ignore_case);

/* concatenates string with raw char array */
/* @param str string */
/* @param value char array */
void cs_concat(String* str, const char* value);

/* append char to string */
/* @param str string */
/* @param item char */
void cs_append(String* str, char item);

/* check if string contains substring */
/* @param str string */
/* @param value char array to seek */
/* @return true if the value occurs within this string, otherwise false */
bool cs_contains(String* str, const char* value);

/* find the index of substring in string */
/* @param str string */
/* @param value char array to seek */
/* @return non negative value if string contains substring, otherwise -1 */
int64_t cs_indexof(String* str, const char* value);

/* find the index of last substring in string */
/* @param str string */
/* @param value char array to seek */
/* @return non negative value if string contains substring, otherwise -1 */
int64_t cs_indexof_last(String* str, const char* value);

/* find the index of the H-th substring */
/* @param str string */
/* @param value char array to seek */
/* @param start_index position number of substring in string */
/* @return non negative value if string contains substring, otherwise -1 */
int64_t cs_indexof_any(String* str, const char* value, size_t start_index);

/* insert substring in string by index */
/* @param str string */
/* @param value char array to insertion */
/* @param index position of insertion */
void cs_insert(String* str, const char* value, size_t index);

/* remove all elements after index */
/* @param str string */
/* @param index position to remove */
void cs_remove_all(String* str, size_t index);

/* replace substring on new substring */
/* @param str string */
/* @param old_value old substring */
/* @param new_value new substring */
/* @return replaced string */
String* cs_replace(String* str, const char* old_value, const char* new_value);

/* split string in array of strings by pattern */
/* @param str string */
/* @param pattern array of delimeters */
/* @param container address of string array */
/* @return length of container after split original string */
size_t cs_split(const String* str, const char* pattern, String*** container);

/* clear string's data */
/* @param self string */
void cs_clear(String* self);

#endif