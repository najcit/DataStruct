// 使用堆存储，仍然是使用一组连续的存储单元放置字符串序列，
// 但是在程序执行过程中动态分配而得
#include <stdlib.h>
#include <string.h>

typedef struct String
{
    char * ch;
    int length;
} String;

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
    s->ch = (char *)malloc(strlen(cs));
    if (!s->ch) { return OVER_FLOW; }
    memcpy(s->ch, cs, strlen(cs));
    s->length = strlen(cs);
    return OK;
}

// 复制字符串
Status string_copy(String * s, String * s1)
{
    if (!s) { return WRONG_INPUT; }
    if (!s1) { return WRONG_INPUT; }
    s1->ch = (char *)malloc(s->length);
    if (!s->ch) { return OVER_FLOW; }
    memcpy(s1->ch, s->ch, s->length);
    s1->length = s->length;
    return OK;
}

// 字符串是否为空
bool string_empty(String * s)
{
    if (!s) { return false; }
    if (0 == s->length)
    {
        return true;
    }
    return false;
}

// 比较两个字符串
bool string_compare(String * s, String * s1)
{
    if (!s) { return false; }
    if (!s1) { return false; }
    if ((s->length == s1->length) && (0 == strncmp(s->ch, s1->ch, s->length)))
    {
        return true;
    }
    return false;
}

// 字符串长度
int string_length(String * s)
{
    if (!s) { return 0; }
    return s->length;
}

// 清除字符串
Status string_clear(String * s)
{
    if (!s) { return WRONG_INPUT; }
    free(s->ch);
    s->ch = NULL;
    s->length = 0;
    return OK;
}

// 字符串拼接
Status string_concat(String * s, String * s1)
{
    if (!s) { return WRONG_INPUT; }
    if (!s1) { return WRONG_INPUT; }
    s->ch = realloc(s->ch, s->length + s1->length);
    if (!s->ch) { return OVER_FLOW; }
    memcpy(s->ch + s->length, s1->ch,  s1->length);
    s->length += s1->length;
    return OK;
}

// 获取子串
Status substring(String * s, int pos, int len, String * ss)
{
    if (!s) { return WRONG_INPUT; }
    if (!s->ch) { return WRONG_INPUT; }
    if (!ss) { return WRONG_INPUT; }
    if (pos+len > s->length) { return WRONG_INPUT; }
    ss->ch = calloc(len, sizeof(char));
    if (!ss->ch) { return OVER_FLOW; }
    memcpy(ss->ch, s->ch + pos, len);
    ss->length = len;
    return OK;
}

// 获取子串的开始位置
Status string_index(String * s, String * ss, int * pos)
{
    if (!s) { return WRONG_INPUT; }
    if (!ss) { return WRONG_INPUT; }
    if (ss->length > s->length) { return WRONG_INPUT; }
    for (int i = 0; i < s->length - ss->length; ++i)
    {
        if (0 == strncmp(s->ch + i, ss->ch, ss->length))
        {
            *pos = i;
            return OK;
        }
    }
    *pos = -1; // 设置无效值
    return UNKNOWN_ERR;
}

// 字符串替换
Status string_replace(String * s, String * t, String * v)
{
    if (!s) { return WRONG_INPUT; }
    if (!t) { return WRONG_INPUT; }
    if (!v) { return WRONG_INPUT; }
    if (!s->ch) { return WRONG_INPUT; }
    if (!t->ch) { return WRONG_INPUT; }
    if (!v->ch) { return WRONG_INPUT; }
    for (int i = 0; i < s->length - t->length; ++i)
    {
        if (0 == strncmp(s->ch + i, t->ch, t->length))
        {
            s->ch = realloc(s->ch, s->length + v->length - t->length);
            if (!s->ch) { return WRONG_INPUT; }
            memcpy(s->ch + i + v->length, s->ch + i + t->length, s->length - i - t->length);
            memcpy(s->ch + i, v->ch, v->length);
            s->length = s->length + v->length - t->length;
            i += v->length;
        }
    }
    return OK;
}

// 字符串插入
Status string_insert(String * s, int pos, String * s1)
{
    if (!s) { return WRONG_INPUT; }
    if (!s1) { return WRONG_INPUT; }
    if (!s1->ch) { return WRONG_INPUT; }
    s->ch = realloc(s->ch, s->length + s1->length);
    if (!s->ch) { return WRONG_INPUT; }
    memcpy(s->ch + pos + s1->length, s1->ch + pos, s->length - pos);
    memcpy(s->ch + pos, s1->ch, s1->length);
    s->length += s1->length;
    return OK;
}

// 字符串删除
Status string_delete(String * s, int pos, int len)
{
    if (!s) { return WRONG_INPUT; }
    memset(s->ch + pos, 0, len);
    s->ch = realloc(s->ch, s->length - len);
    s->length -= len; 
    return OK;
}

// 字符串销毁
Status string_destroy(String * s)
{
    if (!s) { return WRONG_INPUT; }
    free(s->ch);
    s->ch = NULL;
    s->length = 0;
    return OK;
}

#define TEST_STRING
#include "test_string.h"
