#include <stdio.h>
#include <inttypes.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_DATA_LEN    100

struct simple_table
{
    uint32_t *content; // 数据内容
    uint32_t len;      // 当前数据长度
    uint32_t size;     // 总的长度
};

static bool alloc_table(uint32_t size, struct simple_table *table)
{
    if (NULL == table)
    {
        return false;
    }

    if (NULL == (table->content = (uint32_t *)malloc(size * sizeof(uint32_t))))
    {
        printf("[%s] [%s] [%s]\n", __FILE__, __func__, strerror(errno));
    }
    return true;
}

static void release_table(struct simple_table *table)
{
    if (NULL == table || NULL == table->content)
    {
        return (void)0;
    }

    free(table->content);
    table->content = NULL;
    table->len = 0;
    table->size = 0;

    return (void)0;
}

static void show_table(struct simple_table *table)
{

    if (0 == table->len)
    {
        printf("%s table is empty\n", __FILE__);
        return (void)0;
    }

    for (uint32_t i = 0; i < table->len; i++)
    {
        printf("%s table[%d] >> %d\n", __FILE__, i, table->content[i]);
    }

    return (void)0;
}

// TODO
/** add
 *  insert
 *  delete
 *  modify
 *  show list
 * */

int main(void)
{
    struct simple_table table = {
        .content = NULL,
        .len = 0,
        .size = 0
    };

    alloc_table(MAX_DATA_LEN, &table);
    show_table(&table);

    release_table(&table);
    show_table(&table);

    return 0;
}
