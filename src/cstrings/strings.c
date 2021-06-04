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

char csget(const String* self, size_t index)
{
    if (index >= self->length)
    {
        return -1;
    }
    return self->raw[index];
}

void csset(const String* self, char item, size_t index)
{
    if (index >= self->length)
    {
        return;
    }
    self->raw[index] = item;
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

String* cscreate(const char* raw)
{
    if (strlen(raw) > 0)
    {
        String* s = csinit(strlen(raw) + 10);
        memcpy(s->raw, raw, strlen(raw) + 1);
        s->length = strlen(raw);
        return s;
    }
    return csinit(10);
}