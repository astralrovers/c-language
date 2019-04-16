#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define RUN_TEST(fn) { \
            printf("\nstart run: %s\n\n", #fn); \
            fn(); \
            printf("\nend run: %s\n\n", #fn); \
}

/** @fn	static void isalnum_test(void)
 *	@brief	用于sialnum的测试用例
 *	@param void.
 *	@return	void.
 */
static void isalnum_test(void)
{
    char str[] = "*ab%c123_ABC-.";
    for (size_t i = 0; i < strlen(str); i++)
    {
        printf("[%c] is %s\n", str[i], isalnum(str[i]) ? "alnum" : " not alnum");
    }
    return (void)0;
}

static void iscntrl_test(void)
{
    char str[] = "abc\n";
    for (size_t i = 0; i < strlen(str); i++)
    {
        printf("[%c] is %s\n", str[i], iscntrl(str[i]) ? "cntrl" : " not contrl");
    }
    return (void)0;
}

static void isdigit_test(void)
{
    char str[] = "1995abc";
    for (size_t i = 0; i < strlen(str); i++)
    {
        printf("[%c] is %s\n", str[i], isdigit(str[i]) ? "digit" : " not digit");
    }
    return (void)0;
}

static void isxdigit_test(void)
{
    char str[] = "1995abcDEfgH";
    for (size_t i = 0; i < strlen(str); i++)
    {
        printf("[%c] is %s\n", str[i], isxdigit(str[i]) ? "xdigit" : " not xdigit");
    }
    return (void)0;
}

static void isgraph_test(void)
{
    char str[] = "ab 你好c✗\n";
    for (size_t i = 0; i < strlen(str); i++)
    {
        printf("[%c] is %s\n", str[i], isgraph(str[i]) ? "graph" : " not graph");
    }
    return (void)0;
}

static void isprint_test(void)
{
    char str[] = "ab 你好c✗\n";
    for (size_t i = 0; i < strlen(str); i++)
    {
        printf("[%c] is %s\n", str[i], isprint(str[i]) ? "print" : " not print");
    }
    return (void)0;
}

static void ispunct_test(void)
{
    char str[] = "abc,><?\n";
    for (size_t i = 0; i < strlen(str); i++)
    {
        printf("[%c] is %s\n", str[i], ispunct(str[i]) ? "punct" : " not punct");
    }
    return (void)0;
}

/** @fn	void ctype_test(void)
 *	@brief	用于ctype的测试用例
 *	@param void.
 *	@return	void.
 */
void ctype_test(void)
{
    RUN_TEST(isalnum_test);
    RUN_TEST(iscntrl_test);
    RUN_TEST(isdigit_test);
    RUN_TEST(isxdigit_test);
    RUN_TEST(isgraph_test);
    RUN_TEST(isprint_test);
    RUN_TEST(ispunct_test);

    return (void)0;
}
