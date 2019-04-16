#include <stdio.h>
#include <errno.h>
#include <string.h>


/** @fn	void errno_test(void)
 *	@brief	用于errno的测试用例
 *	@param void.
 *	@return	void.
 */
void errno_test(void)
{
    errno = 0;
    FILE *fp = NULL;
    if (NULL == (fp = fopen("errno.txt", "r")))
    {
        perror("errno_test >> ");
        printf("%s\n", strerror(errno));
        printf("errno = [%d]\n", errno);
    }
    else
    {
        fclose(fp);
    }
    return (void)0;
}
