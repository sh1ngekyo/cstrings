#include <assert.h>
#include <cstrings/strings.h>
#include <string.h>

typedef struct cstring
{
    char* raw;
    size_t length;
    size_t capacity;
} String;

/*static void expand_str_data(String* str, const size_t size)
{
    void* tmp = realloc(str->raw, size);
    assert(tmp);
    str->capacity = size;
    str->raw = tmp;
}*/

size_t cslength(const String* self)
{
    return self->length;
}

size_t cscapacity(const String* self)
{
    return self->capacity;
}

const char* csraw(const String* self)
{
    return self->raw;
}

void csfree(String* self)
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

String* csinit(size_t init_cap)
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

String* cscreate(const char* source)
{
    if (strlen(source) > 0)
    {
        String* s = csinit(strlen(source) + 10);
        memcpy(s->raw, source, strlen(source) + 1);
        s->length = strlen(source);
        return s;
    }
    return csinit(10);
}