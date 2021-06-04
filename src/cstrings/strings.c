#include <assert.h>
#include <cstrings/strings.h>
#include <string.h>

typedef struct cstring
{
    char* raw;
    size_t length;
    size_t capacity;
} String;

static void expand_str_data(String* str, const size_t size)
{
    void* tmp = realloc(str->raw, size);
    assert(tmp);
    str->capacity = size;
    str->raw = tmp;
}

size_t cs_length(const String* self)
{
    return self ? self->length : 0;
}

size_t cs_capacity(const String* self)
{
    return self ? self->capacity : 0;
}

const char* cs_raw(const String* self)
{
    return self ? self->raw : NULL;
}

char cs_get(const String* self, size_t index)
{
    if (!self || index >= self->length)
    {
        return -1;
    }
    return self->raw[index];
}

void cs_set(const String* self, char item, size_t index)
{
    if (!self || index >= self->length)
    {
        return;
    }
    self->raw[index] = item;
}

String* cs_clone(const String* self)
{
    if (!self)
    {
        return NULL;
    }
    return cs_create(self->raw);
}

int64_t cs_compare(const String* str, const char* raw, bool ignore_case)
{
    if (!str)
    {
        return -1;
    }
    return ignore_case ? strcasecmp(str->raw, raw) : strcmp(str->raw, raw);
}

void cs_concat(String* str, const char* raw)
{
    if (!str)
    {
        return;
    }
    if (str->length + strlen(raw) + 1 >= str->capacity)
    {
        expand_str_data(str, (str->length + strlen(raw) + 1) * 2);
    }
    strcat(str->raw, raw);
    str->length += strlen(raw);
}

bool cs_contains(String* str, const char* value)
{
    if (!str)
    {
        return false;
    }
    return strstr(str->raw, value) ? true : false;
}

int64_t cs_indexof(String* str, const char* value)
{
    if (!str)
    {
        return -1;
    }
    int64_t result = strstr(str->raw, value) - str->raw;
    return result >= 0 ? result : -1;
}

int64_t cs_indexof_last(String* str, const char* value)
{
    if (!str)
    {
        return -1;
    }
    int64_t result = -1;
    char* current_substr = str->raw;
    while ((current_substr = strstr(current_substr, value)) != NULL)
    {
        result = current_substr - str->raw;
        current_substr += strlen(value);
    }
    return result;
}

int64_t cs_indexof_any(String* str, const char* value, size_t start_index)
{
    if (!str)
    {
        return -1;
    }
    int64_t result = -1;
    char* current_substr = str->raw;
    for (size_t i = 0; i <= start_index; ++i)
    {
        if (current_substr + strlen(value) >= str->raw + str->length)
        {
            return -1;
        }
        current_substr = strstr(current_substr, value);
        result = current_substr - str->raw;
        current_substr += strlen(value);
    }
    return result >= 0 ? result : -1;
}

void cs_insert(String* str, const char* value, size_t index)
{
    if (cs_length(str) == 0)
    {
        cs_concat(str, value);
        return;
    }
    if (index < str->length)
    {
        if (str->capacity < str->length + strlen(value) + 1)
        {
            expand_str_data(str, (str->length + strlen(value) + 1) * 2);
        }
        memmove(&str->raw[index + strlen(value)], &str->raw[index], str->length - index + 1);
        memmove(&str->raw[index], value, strlen(value));
        str->length += strlen(value);
    }
}

void cs_free(String* self)
{
    if (self)
    {
        if (self->raw)
        {
            free(self->raw);
            self->raw = NULL;
        }
        free(self);
    }
}

String* cs_init(size_t init_cap)
{
    if (init_cap > 0)
    {
        String* str = malloc(sizeof(String));
        assert(str);
        str->capacity = init_cap;
        str->raw = malloc(str->capacity);
        assert(str->raw);
        str->length = 0;
        str->raw[0] = '\0';
        return str;
    }
    return NULL;
}

String* cs_create(const char* raw)
{
    if (strlen(raw) > 0)
    {
        String* s = cs_init(strlen(raw) + 10);
        memcpy(s->raw, raw, strlen(raw) + 1);
        s->length = strlen(raw);
        return s;
    }
    return cs_init(10);
}