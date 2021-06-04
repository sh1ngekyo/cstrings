#ifndef CSTRING_H
#define CSTRING_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct cstring String;

/* initialize container with \\0 on index 0 */
/* @param init_cap initial capacity of container */
/* @return empty container */
String* csinit(size_t init_cap);

/* create container from raw string */
/* @param raw char* of char[] */
/* @return container with data from raw and closed with \\0 */
String* cscreate(const char* raw);

/* string length getter */
/* @param self string container */
/* @return copy of length field */
size_t cslength(const String* self);

/* string capacity getter */
/* @param self string container */
/* @return copy of capacity field */
size_t cscapacity(const String* self);

/* string text getter */
/* @param self string container */
/* @return readonly representation of raw text field */
const char* csraw(const String* self);

/* free string's memory */
/* @param self string container */
void csfree(String* self);

/* for access to raw field by index */
/* @param self string container */
/* @param index index in char array */
/* @return char by index of -1, if index was out of range */
char csget(const String* self, size_t index);

/* for access to raw field by index */
/* @param self string container */
/* @param item character */
/* @param index index in char array */
void csset(const String* self, char item, size_t index);

#endif