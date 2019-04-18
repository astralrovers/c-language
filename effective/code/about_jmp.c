#include <stdio.h>
#include <setjmp.h>

static jmp_buf env;


static void case_jmp(void)
{
    printf("%s, >> %s\n", __FILE__, __func__);
    longjmp(env, 20);
}


void setjmp_test(void)
{
    int err = 0;
    if (err = setjmp(env))
    {
        printf("setjmp >> ret = [%d]\n", err);
        return (void)0;
    }
    case_jmp();

    return (void)0;
}
