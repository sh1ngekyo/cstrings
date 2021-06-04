#include <cstrings/strings.h>
#include <ctest.h>

CTEST(strings, init)
{
    String* s = csinit(10);
    ASSERT_NOT_NULL(s);
    csfree(s);
}

CTEST(strings, length)
{
    String* s = csinit(10);
    ASSERT_EQUAL(0, cslength(s));
    csfree(s);
}

CTEST(strings, capacity)
{
    String* s = csinit(10);
    ASSERT_EQUAL(10, cscapacity(s));
    csfree(s);
}

CTEST(strings, create)
{
    String* s = cscreate("10");
    ASSERT_NOT_NULL(s);
    ASSERT_STR("10", csraw(s));
    csfree(s);
}

CTEST(strings, create_empty)
{
    String* s = cscreate("");
    ASSERT_STR("", csraw(s));
    ASSERT_EQUAL(0, cslength(s));
    csfree(s);
}