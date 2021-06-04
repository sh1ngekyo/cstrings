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

void cs_append(String* str, char item)
{
    if (str->length + 1 >= str->capacity)
    {
        expand_str_data(str, (1 + str->capacity) * 2);
    }
    str->raw[str->length++] = item;
    str->raw[str->length] = '\0';
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

void cs_remove_all(String* str, size_t index)
{
    if (!str)
    {
        return;
    }
    if (index < str->length)
    {
        size_t new_size = str->length - (str->length - index);
        char* new_raw = malloc((new_size + 1) * 2);
        memcpy(new_raw, str->raw, new_size);
        free(str->raw);
        str->raw = new_raw;
        str->capacity = (new_size + 1) * 2;
        str->length = new_size + 1;
        str->raw[str->length - 1] = '\0';
    }
}

String* cs_replace(String* str, const char* old_value, const char* new_value)
{
    if (!str || !old_value || !new_value)
    {
        return NULL;
    }
    char* old_sub = strstr(str->raw, old_value);
    if (!old_sub || strlen(old_sub) == 0 || strlen(old_value) == 0)
    {
        return cs_clone(str);
    }
    String* out = cs_init(cs_capacity(str));
    size_t pos = 0;
    size_t len = str->length;
    while (old_sub)
    {
        while (pos < old_sub - str->raw)
        {
            cs_append(out, cs_get(str, pos++));
        }
        cs_concat(out, new_value);
        old_sub = strstr(old_sub + strlen(old_value), old_value);
        pos += strlen(old_value);
    }
    while (pos < len)
    {
        cs_append(out, cs_get(str, pos++));
    }
    return out;
}

size_t cs_split(const String* str, const char* pattern, String*** container)
{
    char* copy = malloc(str->length + 1);
    memcpy(copy, str->raw, str->length + 1);
    size_t length = 0;
    for (char* substr = strtok(copy, pattern); substr != NULL; substr = strtok(NULL, pattern))
    {
        *container = realloc(*container, sizeof(String*) * (++length));
        (*container)[length - 1] = cs_create(substr);
    }
    free(copy);
    return length;
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

void cs_clear(String* self)
{
    if (self)
    {
        if (self->raw)
        {
            free(self->raw);
            self->raw = malloc(self->capacity);
            self->length = 0;
            self->raw[self->length] = 0;
        }
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