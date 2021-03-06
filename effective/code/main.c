#include <stdio.h>

#define RUN_TEST(fn) { \
            printf("\nstart run: %s\n\n", #fn); \
            fn(); \
            printf("\nend run: %s\n\n", #fn); \
}

extern void three_point_test(void);
extern void shift_of_3_test(void);
extern void assert_test(void);
extern void ctype_test(void);
extern void errno_test(void);
extern void setjmp_test(void);
extern void stdarg_test(void);

int main(void)
{
    RUN_TEST(three_point_test);
    RUN_TEST(shift_of_3_test);
    RUN_TEST(assert_test);
    RUN_TEST(ctype_test);
    RUN_TEST(errno_test);
    RUN_TEST(setjmp_test);
    RUN_TEST(stdarg_test);

    return 0;
}
