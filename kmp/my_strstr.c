#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "my_strstr.h"

static bool is_prev_equal_next(const char *prev, const char *next, const int len);
static void kmp(const char *mode, int *next);
static void move_distance(int *next, int len);
static bool get_not_match_pos(const char *src, const char *mode, const int len, int *pos);
static bool search_pos_when_pat(const char *src, const char *mode, const int *next, ptrdiff_t *pos);

/**
 * @brief 比较两个字符串是否相等
 *
 * @function is_prev_equal_next 
 * @param prev
 * @param next
 * @param len
 *
 * @return 
 */
static bool is_prev_equal_next(const char *prev, const char *next, const int len)
{
    for (int i = 0; i < len; i++)
    {
        if (prev[i] != next[i])
        {
            return false;
        }
    }

    return true;
}

/**
 * @brief 计算每个字符匹配到字符串头部之间的最大相同前缀和后缀
 *
 * @function kmp 
 * @param mode
 * @param next
 */
static void kmp(const char *mode, int *next)
{
    int mode_len = strlen(mode);

    int len_of_same = 0; // 前缀等于后缀的最长字符长度

    for (int i = 1; i < mode_len; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            len_of_same = i + 1 - j; // 也就是当前需要字符串的长度
            if (is_prev_equal_next(mode, mode+j, len_of_same))
            {
                next[i] = len_of_same; // 当前i字符匹配失败后，需要后移的长度
                break;
            }
        }
    }

    return ;
}

/**
 * @brief 每个字符匹配失败时，其实匹配位置移动长度
 *
 * @function move_distance 
 * @param next
 * @param len
 */
static void move_distance(int *next, int len)
{
    next[0] = 1; // 第一个字符配失败移动一个长度

    for (int i = 1; i < len; i++)
    {
        next[i] = i - next[i] + 1;
    }

    return ;
}

/**
 * @brief 获取不匹配的模式串位置
 *
 * @function get_not_match_pos 
 * @param src
 * @param mode
 * @param len
 * @param pos
 *
 * @return 
 */
static bool get_not_match_pos(const char *src, const char *mode, const int len, int *pos)
{
    for (int i = 0; i < len; i++)
    {
        if (src[i] != mode[i])
        {
            *pos = i;
            return true;
        }
    }

    return false;
}

/**
 * @brief 查找匹配位置
 *
 * @function search_pos_when_pat 
 * @param src
 * @param mode
 * @param next
 * @param pos
 *
 * @return 
 */
static bool search_pos_when_pat(const char *src, const char *mode, const int *next, ptrdiff_t *pos)
{
    int src_len = strlen(src);
    int mode_len = strlen(mode);
    int not_match_pos = 0;

    for (ptrdiff_t i = 0; (src_len - i) >= mode_len;)
    {
        if (get_not_match_pos(src+i, mode, mode_len, &not_match_pos))
        {
            i += next[not_match_pos];
        }
        else
        {
            *pos = i;
            return true;
        }
    }

    return false;
}

char *my_strstr(const char *src, const char *mode)
{
    ptrdiff_t pos = 0;
    int mode_len = strlen(mode);

    int *next = (int *)malloc(mode_len*sizeof(int));

    if (NULL == next)
    {
        printf("error\n");
    }

    memset(next, 0, sizeof(int)*mode_len);

    kmp(mode, next);
    move_distance(next, mode_len);

    if (search_pos_when_pat(src, mode, next, &pos))
    {
        free(next);
        return (char *)(src + pos);
    }

    free(next);

    return NULL;
}

int main(void)
{
    char *src = "xabcxxabcx";
    char *mode = "abcxxabc";
    char *ret = 0;
    ret = my_strstr(src, mode);

    printf("search ret = %s\n", NULL == ret ? "not match" : ret);

    return 0;
}
