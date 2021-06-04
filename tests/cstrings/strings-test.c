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

CTEST(strings, compare_string)
{
    String* str1 = cscreate("test");
    String* str2 = cscreate("test2");
    String* str3 = cscreate("tes");
    String* str4 = cscreate("test");
    ASSERT_EQUAL(-1, cscompare_string(str1, str2, false));
    ASSERT_EQUAL(1, cscompare_string(str1, str3, false));
    ASSERT_EQUAL(0, cscompare_string(str1, str4, false));
    csfree(str2);
    csfree(str3);
    csfree(str4);

    str2 = cscreate("TEST2");
    str3 = cscreate("TES");
    str4 = cscreate("TEST");
    ASSERT_EQUAL(-50, cscompare_string(str1, str2, true));
    ASSERT_EQUAL(116, cscompare_string(str1, str3, true));
    ASSERT_EQUAL(0, cscompare_string(str1, str4, true));

    csfree(str1);
    csfree(str2);
    csfree(str3);
    csfree(str4);
}

CTEST(strings, compare_raw)
{
    String* str1 = cscreate("test");
    ASSERT_EQUAL(-1, cscompare_raw(str1, "test2", false));
    ASSERT_EQUAL(1, cscompare_raw(str1, "tes", false));
    ASSERT_EQUAL(0, cscompare_raw(str1, "test", false));
    ASSERT_EQUAL(-50, cscompare_raw(str1, "TEST2", true));
    ASSERT_EQUAL(116, cscompare_raw(str1, "TES", true));
    ASSERT_EQUAL(0, cscompare_raw(str1, "TEST", true));
    csfree(str1);
}