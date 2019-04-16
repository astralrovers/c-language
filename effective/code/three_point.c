#include <stdio.h>
#include <stdarg.h>

#define DEBUG(fmt, ...) printf("%s : DEBUG >> "fmt, __func__, ##__VA_ARGS__)
#define LOG(fmt, args...) printf("%s : LOG >> "fmt, __func__, ##args)

/** @fn	static void printf_args(const char *fmt, ...)
 *	@brief	自定义的printf
 *	@param fmt 表示参数格式.
 *	@param ... 表示可变参数.
 *	@return	void.
 */
static void printf_args(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    return (void)(0);
}

/** @fn	void three_point_test(void)
 *	@brief	用于...语法的测试用例
 *	@param void.
 *	@return	void.
 */
void three_point_test(void)
{
    size_t i = 0;
    int name_id[10] = { [0 ... 9] = 1 };
    for (i = 0; i < sizeof(name_id)/sizeof(name_id[0]); i++)
    {
        DEBUG("index = %zu, id = [%d]\n", i, name_id[i]);
    }

    switch (i)
    {
        case 0 ... 20:
            LOG("case into\n");
            break;
        default:
            break;
    }
    printf_args("test my printf\n");
    return (void)(0);
}
