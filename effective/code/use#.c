#include <stdio.h>

#define TO_STR(sym) #sym
#define TRAN_VAL(val) TO_STR(val)

#define TOC_ID 2
#define TOC_NAME "use#"

#define LINK_SYM(sym1, sym2) sym1##sym2

/** @fn	shift_of_3_test(void)
 *	@brief	用于#和##语法的测试用例
 *	@param void.
 *	@return	void.
 */
void shift_of_3_test(void)
{
    printf("# >> %s\n", TO_STR(88));
    printf("# >> %s\n", TO_STR(hello world));
    printf("# >> %s\n", TO_STR(TOC_NAME));

    printf("# >> %s\n", TRAN_VAL(TOC_ID));
    printf("# >> %s\n", TRAN_VAL(TOC_NAME));

    printf("# >> %s\n", TRAN_VAL(LINK_SYM(hello, world)));

    return (void)0;
}
