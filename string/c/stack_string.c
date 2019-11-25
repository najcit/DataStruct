// 使用栈内存来实现字符串
// 由于使用顺序的定长存储单位，需初始化一个固定长度的存储区
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_MAX_SIZE 255
typedef char String[STRING_MAX_SIZE];

// #define strlen(s) strlen((char *)s)
// #define strncmp(s, s1, n) strncmp((char *)s, (char *)s1, n)

// 函数返回值
typedef enum Status
{
    OK,
    UNKNOWN_ERR,
    WRONG_INPUT,
    ILLEGAL_OPT,
    OVER_FLOW,
} Status;

// bool 类型
typedef enum bool
{
    false,
    true,
} bool;

// 构造一个字符串
Status string_assign(String * s, const char * cs)
{
    if (!s) { return WRONG_INPUT; }
    if (!cs) { return WRONG_INPUT; }
    if (strlen(cs) > STRING_MAX_SIZE) { return ILLEGAL_OPT; }
    memset(*s, 0, STRING_MAX_SIZE);
    memcpy(*s, cs, strlen(cs));
    return OK;
}

// 复制字符串
Status string_copy(String * s, String * s1)
{
    if (!s) { return WRONG_INPUT; }
    if (!s1) { return WRONG_INPUT; }
    if (strlen(*s1) > STRING_MAX_SIZE) { return ILLEGAL_OPT; }
    memset(*s1, 0, STRING_MAX_SIZE);
    memcpy(*s1, *s, strlen(*s));
    return OK;
}

// 字符串是否为空
bool string_empty(String * s)
{
    if (!s) { return false; }
    if (0 != strlen(*s))
    {
        return false;
    }
    return true;
}

// 比较两个字符串
bool string_compare(String * s, String * s1)
{
    if (!s) { return false; }
    if (!s1) { return false; }
    if ((strlen(*s) == strlen(*s1)) && (0 == strncmp(*s, *s1, strlen(*s))))
    {
        return true;
    }
    return false;
}

// 字符串长度
int string_length(String * s)
{
    if (!s) { return -1; }
    return strlen(*s);
}

// 清除字符串
Status string_clear(String * s)
{
    if (!s) { return WRONG_INPUT; }
    memset(*s, 0, strlen(*s));
    return OK;
}

// 字符串拼接
Status string_concat(String * s, String * s1)
{
    if (!s) { return WRONG_INPUT; }
    if (!s1) { return WRONG_INPUT; }
    if (strlen(*s) + strlen(*s1) > STRING_MAX_SIZE) { return ILLEGAL_OPT; }
    memcpy(*s + strlen(*s), s1, strlen(*s1));
    return OK;
}

// 获取子串
Status substring(String * s, int pos, int len, String * ss)
{
    if (!s) { return WRONG_INPUT; }
    if (!ss) { return WRONG_INPUT; }
    memcpy(*ss, *s + pos, len);
    return OK;
}

// 获取子串的开始位置
Status string_index(String * s, String * ss, int * pos)
{
    if (!s) { return WRONG_INPUT; }
    if (!ss) { return WRONG_INPUT; }
    if (!pos) { return WRONG_INPUT; }
    for (int i = 0; i < strlen(*s); ++i)
    {
        bool is_found = true;
        int t = i;
        for (int j = 0; j < strlen(*ss); ++j)
        {
            if ((*s)[i] == (*ss)[j])
            {
                i++;
            }
            else
            {
                is_found = false;
                break;
            }
        }

        if (is_found)
        {
            *pos = t;
            break;
        }
        else
        {
            i = t;
        }
    }
    return OK;
}

// 字符串替换
// 将出现 s 中的 t 全部换成 v
Status string_replace(String * s, String * t, String * v)
{
    if (!s) { return WRONG_INPUT; }
    if (!t) { return WRONG_INPUT; }
    if (!v) { return WRONG_INPUT; }
    for (int i = 0; i < strlen(*s); ++i)
    {
        bool is_found = true;
        int k = i;
        for (int j = 0; j < strlen(*t); ++j)
        {
            if ((*s)[i] == (*t)[j])
            {
                i++;
            }
            else
            {
                is_found = false;
                break;
            }
        }
        if (is_found)
        {
            memcpy(*s + k + strlen(*v), *s + k + strlen(*t), strlen(*t));
            memcpy(*s + k, *v, strlen(*v));
            i = k + strlen(*v);
        }
        else
        {
            i = k;
        }
    }
    return OK;
}

// 字符串插入
Status string_insert(String * s, int pos, String * s1)
{
    if (!s) { return WRONG_INPUT; }
    if (!s1) { return WRONG_INPUT; }
    // 将pos+1位置后移
    memcpy(*s + pos + strlen(*s1), *s + pos, strlen(*s+pos));
    memcpy(*s + pos, *s1, strlen(*s1));
    return OK;
}

// 字符串删除
Status string_delete(String * s, int pos, Status len)
{
    if (!s) { return WRONG_INPUT; }
    if (pos +len >= strlen(*s)) { return WRONG_INPUT; }
    memcpy(*s +pos, *s +pos +len, len);
    memset(*s + pos + len, 0, len);
    return OK;
}

// 字符串销毁
Status string_destroy(String * s)
{
    if (!s) { return WRONG_INPUT; }
    memset(*s,0 , strlen(*s));
    return OK;
}

#define TEST_STRING
#include "test_string.h"