// 串，又称字符串，是由0个或多个字符组成的有限集合
// 不含有字符的串叫做空串
// 含有字符的个数叫做串的长度
// 如果两个字符串的各个位置上的字符都是一样的，则这两个字符串相等

typedef struct String String;

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
Status string_assign(String * s, const char * chars);

// 复制字符串
Status string_copy(String * s, String * s1);

// 字符串是否为空
bool string_empty(String * s);

// 比较两个字符串
bool string_compare(String * s, String * s1);

// 字符串长度
int string_length(String * s);

// 清除字符串
Status string_clear(String * s);

// 字符串拼接
Status string_concat(String * s, String * s1);

// 获取子串
Status substring(String * s, int pos, Status len, String * ss);

// 获取子串的开始位置
Status string_index(String * s, int pos, String * ss);

// 字符串替换
Status string_replace(String * s, String * t, String * v);

// 字符串插入
Status string_insert(String * s, int pos, String * s1);

// 字符串删除
Status string_delete(String * s, int pos, Status len);

// 字符串销毁
Status string_destroy(String * s);