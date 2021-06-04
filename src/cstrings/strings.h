#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef struct cstring String;

String* csinit(size_t init_cap);

String* cscreate(const char* raw);

size_t cslength(const String* self);

size_t cscapacity(const String* self);

const char* csraw(const String* self);

void csfree(String* self);