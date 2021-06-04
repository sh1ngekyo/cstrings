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
    char raw[] = "10";
    String* s = cscreate(raw);
    ASSERT_NOT_NULL(s);
    ASSERT_STR(raw, csraw(s));
    ASSERT_EQUAL(sizeof(raw) / sizeof(char) - 1, cslength(s));
    ASSERT_EQUAL(sizeof(raw) / sizeof(char) - 1 + 10, cscapacity(s));
    csfree(s);
}

CTEST(strings, create_empty)
{
    String* s = cscreate("");
    ASSERT_STR("", csraw(s));
    ASSERT_EQUAL(0, cslength(s));
    csfree(s);
}

CTEST(strings, set)
{
    char raw[] = "test";
    String* s = cscreate(raw);
    ASSERT_EQUAL(4, cslength(s));
    for (size_t i = 0; i < cslength(s); ++i)
    {
        csset(s, i + '0', i);
    }
    ASSERT_STR("0123", csraw(s));
    csfree(s);
}

CTEST(strings, get)
{
    char raw[] = "test";
    String* s = cscreate(raw);
    ASSERT_EQUAL(4, cslength(s));
    for (size_t i = 0; i < cslength(s); ++i)
    {
        ASSERT_EQUAL(raw[i], csget(s, i));
    }
    csfree(s);
}

CTEST(strings, clone)
{
    char raw[] = "test";
    String* s = cscreate(raw);
    String* clone = csclone(s);
    ASSERT_STR(csraw(clone), csraw(s));
    ASSERT_EQUAL(cslength(s), cslength(clone));
    csfree(s);
    csfree(clone);
}

CTEST(strings, compare)
{
    String* str = cscreate("test");
    ASSERT_EQUAL(-1, cscompare(str, "test2", false));
    ASSERT_EQUAL(1, cscompare(str, "tes", false));
    ASSERT_EQUAL(0, cscompare(str, "test", false));
    ASSERT_EQUAL(-50, cscompare(str, "TEST2", true));
    ASSERT_EQUAL(116, cscompare(str, "TES", true));
    ASSERT_EQUAL(0, cscompare(str, "TEST", true));
    csfree(str);
}

CTEST(strings, concat)
{
    String* str = cscreate("hello");
    csconcat(str, " world!");
    ASSERT_STR("hello world!", csraw(str));
    csfree(str);
}

CTEST(strings, concat_str_expand)
{
    String* str = cscreate("hello");
    ASSERT_EQUAL(15, cscapacity(str));
    csconcat(str, " world!world!world!world!world!world!");
    ASSERT_STR("hello world!world!world!world!world!world!", csraw(str));
    ASSERT_EQUAL((5 + 37 + 1) * 2, cscapacity(str));
    ASSERT_EQUAL(42, cslength(str));
    csfree(str);
}