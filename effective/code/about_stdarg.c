#include <stdarg.h>
#include <stdio.h>

static void print_one_arg(int last, ...)
{
    va_list ap;
    va_start(ap, last);
    int ret_int = va_arg(ap, int);
    va_end(ap);

    printf("about_args >> %s, last = [%d], one_arg = [%d]\n", __func__, last, ret_int);
    return (void)0;
}

static void my_print(const char * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    printf("about_stdarg >> my_print : ");
    vprintf(fmt, ap);
    va_end(ap);

    return (void)0;
}

void stdarg_test(void)
{
    print_one_arg(20, 30);
    my_print("hello name = [%s] age = [%d]\n", "ywl", 24);

    return (void)0;
}
