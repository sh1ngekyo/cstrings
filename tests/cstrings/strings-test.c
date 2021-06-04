#include <cstrings/strings.h>
#include <ctest.h>

CTEST(strings, init)
{
    String* s = cs_init(10);
    ASSERT_NOT_NULL(s);
    cs_free(s);
}

CTEST(strings, length)
{
    String* s = cs_init(10);
    ASSERT_EQUAL(0, cs_length(s));
    cs_free(s);
}

CTEST(strings, capacity)
{
    String* s = cs_init(10);
    ASSERT_EQUAL(10, cs_capacity(s));
    cs_free(s);
}

CTEST(strings, create)
{
    char raw[] = "10";
    String* s = cs_create(raw);
    ASSERT_NOT_NULL(s);
    ASSERT_STR(raw, cs_raw(s));
    ASSERT_EQUAL(sizeof(raw) / sizeof(char) - 1, cs_length(s));
    ASSERT_EQUAL(sizeof(raw) / sizeof(char) - 1 + 10, cs_capacity(s));
    cs_free(s);
}

CTEST(strings, create_empty)
{
    String* s = cs_create("");
    ASSERT_STR("", cs_raw(s));
    ASSERT_EQUAL(0, cs_length(s));
    cs_free(s);
}

CTEST(strings, set)
{
    char raw[] = "test";
    String* s = cs_create(raw);
    ASSERT_EQUAL(4, cs_length(s));
    for (size_t i = 0; i < cs_length(s); ++i)
    {
        cs_set(s, i + '0', i);
    }
    ASSERT_STR("0123", cs_raw(s));
    cs_free(s);
}

CTEST(strings, get)
{
    char raw[] = "test";
    String* s = cs_create(raw);
    ASSERT_EQUAL(4, cs_length(s));
    for (size_t i = 0; i < cs_length(s); ++i)
    {
        ASSERT_EQUAL(raw[i], cs_get(s, i));
    }
    cs_free(s);
}

CTEST(strings, clone)
{
    char raw[] = "test";
    String* s = cs_create(raw);
    String* clone = cs_clone(s);
    ASSERT_STR(cs_raw(clone), cs_raw(s));
    ASSERT_EQUAL(cs_length(s), cs_length(clone));
    cs_free(s);
    cs_free(clone);
}

CTEST(strings, compare)
{
    String* str = cs_create("test");
    ASSERT_EQUAL(-1, cs_compare(str, "test2", false));
    ASSERT_EQUAL(1, cs_compare(str, "tes", false));
    ASSERT_EQUAL(0, cs_compare(str, "test", false));
    ASSERT_EQUAL(-50, cs_compare(str, "TEST2", true));
    ASSERT_EQUAL(116, cs_compare(str, "TES", true));
    ASSERT_EQUAL(0, cs_compare(str, "TEST", true));
    cs_free(str);
}

CTEST(strings, concat)
{
    String* str = cs_create("hello");
    cs_concat(str, " world!");
    ASSERT_STR("hello world!", cs_raw(str));
    cs_free(str);
}

CTEST(strings, concat_str_expand)
{
    String* str = cs_create("hello");
    ASSERT_EQUAL(15, cs_capacity(str));
    cs_concat(str, " world!world!world!world!world!world!");
    ASSERT_STR("hello world!world!world!world!world!world!", cs_raw(str));
    ASSERT_EQUAL((5 + 37 + 1) * 2, cs_capacity(str));
    ASSERT_EQUAL(42, cs_length(str));
    cs_free(str);
}

CTEST(strings, contains)
{
    String* str = cs_create("test");
    ASSERT_TRUE(cs_contains(str, "t"));
    ASSERT_TRUE(cs_contains(str, "e"));
    ASSERT_TRUE(cs_contains(str, "s"));
    ASSERT_TRUE(cs_contains(str, ""));
    ASSERT_FALSE(cs_contains(str, "hello"));
    ASSERT_FALSE(cs_contains(str, "ts"));
    ASSERT_FALSE(cs_contains(str, "test hello"));
    cs_free(str);
}

CTEST(strings, index_of)
{
    String* str = cs_create("test");
    ASSERT_EQUAL(0, cs_indexof(str, "test"));
    ASSERT_EQUAL(1, cs_indexof(str, "est"));
    ASSERT_EQUAL(2, cs_indexof(str, "st"));
    ASSERT_EQUAL(0, cs_indexof(str, "t"));
    ASSERT_EQUAL(-1, cs_indexof(str, "test1"));
    ASSERT_EQUAL(0, cs_indexof(str, ""));
    ASSERT_EQUAL(-1, cs_indexof(str, "123"));
    cs_free(str);
}

CTEST(strings, index_of_last)
{
    String* str = cs_create("Why do you cry, Willy? Why do you cry? Why, Willy? Why, Willy? Why, Willy? Why?");
    ASSERT_EQUAL(75, cs_indexof_last(str, "Why"));
    ASSERT_EQUAL(68, cs_indexof_last(str, "Willy"));
    ASSERT_EQUAL(-1, cs_indexof_last(str, "test"));
    ASSERT_EQUAL(34, cs_indexof_last(str, "cry"));
    cs_free(str);
}