#include "link_stack.c"

// 数字进制转化的一个基本原理
// N = (N div d) * d + (N mod d)
// 例子如下：
// 1348[10] = 2504[8]
// 10进制 1348 转化到 8进制 2054 的过程
// N        N div d     N mod d
// 1348     168         4
// 168      21          0
// 21       2           5
// 2        0           2

// 将10进制数转化为8进制的数输出
// 8进制数以字符串形式输出
#include <stdio.h>
#include <string.h>

int num_8_conversion(int num_10, char *num_8, int len)
{
    // 初始化栈
    Stack stack;
    init_stack(&stack);

    // 循环压栈
    Element element = {0};
    int N = num_10;
    int n = 0;
    while(N)
    {
        n = N % 8; // 余数
        N = N / 8; // 商
        element.data = n;
        stack_push(&stack, element);
    }

    // 循环出栈
    memset(num_8, 0, len);
    int i = 0;
    while (!stack_empty(&stack))
    {
        if (i == len){ return -1; }
        stack_pop(&stack, &element);
        num_8[i++] = element.data + 48; // 将数字转化为 ASCII码
    }

    // 销毁栈
    destroy_stack(&stack);

    return 0;
}

// 将10进制数转化为指定的进制
int num_conversion(int num, int base, char *num_base, int len)
{
 // 初始化栈
    Stack stack;
    init_stack(&stack);

    // 循环压栈
    Element element = {0};
    int N = num;
    int n = 0;
    while(N)
    {
        n = N % base; // 余数
        N = N / base; // 商
        element.data = n;
        stack_push(&stack, element);
    }

    // 循环出栈
    memset(num_base, 0, len);
    int i = 0;
    while (!stack_empty(&stack))
    {
        if (i == len){ return -1; }
        stack_pop(&stack, &element);
        num_base[i++] = element.data + 48; // 将数字转化为 ASCII码
    }
    
    // 销毁栈
    destroy_stack(&stack);

    return 0;
}

// int main(int argc, char const *argv[])
// {
//     // num_8_conversion(10);
//     char num[32] = {}; 
//     num_8_conversion(1348, num, 32);
//     printf("n:%s\n", num);
//     num_8_conversion(3457, num, 32);
//     printf("n:%s\n", num);

//     num_conversion(1348, 2, num, 32);
//     printf("n:%s\n", num);
//     num_conversion(1348, 4, num, 32);
//     printf("n:%s\n", num);

//     return 0;
// }

#define CTEST_MAIN
#include "ctest.h"

CTEST(num_converson, conversion_10to8_test) {
    char num[32] = {}; 
    ASSERT_STR("2504", (num_8_conversion(1348, num, 32), num));
    ASSERT_STR("6601", (num_8_conversion(3457, num, 32), num));
}

CTEST(num_converson, conversion_10toX_test) {
    char num[32] = {}; 
    ASSERT_STR("2504", (num_conversion(1348, 8, num, 32), num));
    ASSERT_STR("6601", (num_conversion(3457, 8, num, 32), num));
    ASSERT_STR("111010", (num_conversion(1348, 4, num, 32), num));
    ASSERT_STR("10101000100", (num_conversion(1348, 2, num, 32), num));
}

int main(int argc, char const *argv[])
{
    int result = ctest_main(argc, argv);
    return result;
}
