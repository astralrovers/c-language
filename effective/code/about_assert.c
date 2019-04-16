#include <stdio.h>

#define NDEBUG

#include <assert.h>

/** @fn	void assert_test(void)
 *	@brief	用于assert标准库的测试用例
 *	@param void.
 *	@return	void.
 */
void assert_test(void)
{
    assert(1 == 0);
    assert(1 == 1);
    return (void)0;
}
