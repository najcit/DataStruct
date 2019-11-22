// 简单的行编辑程序
// 接收用户从终端的程序输入的程序或数据
// 由于用户在终端输入时，不能保证不出错误，
// 因此，设置缓存区，允许用户发现错误并改成
// 以符号 "#" 表示一个退格符
// 以符号 "@" 表示一个退行符

#include "link_stack.c"
#include <stdio.h>
#include <string.h>

// 输入含有特殊符号的字符串并解析出正确的内容
int line_edit(char * in_text, int in_len, char * out_text, int * out_len)
{
    // 初始化栈
    Stack stack;
    init_stack(&stack);
    // printf("in_text:%s %d\n", in_text, in_len);
  
    // 入栈
    Element element = {0};
    for (int i = 0; i < in_len; i++)
    {
        char ch = in_text[i];
        // printf("ch:%c\n", ch);
        switch (ch)
        {
        case '#':
            // 清除当前栈顶
            stack_pop(&stack, &element);
            break;
        case '@':
            // 清除当前栈
            clear_stack(&stack);
            break;
        default:
            // 其他情况压栈
            element.data = ch;
            stack_push(&stack, element);
            break;
        }
    }

    // 出栈
    memset(out_text, 0, *out_len);
    int len = stack_length(&stack);
    if (len > *out_len)
    { 
        return -1; 
    }
    else
    {
        *out_len = len;
    }
    int i = len - 1;
    while (!stack_empty(&stack))
    {
        Element element = {0};
        stack_pop(&stack, &element);
        // printf("ch2:%c\n", element.data);
        out_text[i--] = element.data;
    }

    // 销毁栈
    destroy_stack(&stack);

    return 0;
}

// int main(int argc, char const *argv[])
// {
//     // char in_text[128] = "whil##ilr#e(s#*s)";
//     char in_text[128] = "outchar@whil##ilr#e(s#*s);";
//     char out_text[128] = {};
//     int out_len = sizeof(out_text);
//     int result = line_edit(in_text, strlen(in_text), out_text, &out_len);
//     printf("result:%d, out_text:%s, out_len:%d\n", result, out_text, out_len);
//     return 0;
// }

#define CTEST_MAIN
#include "ctest.h"

CTEST(line_edit, line_edit_test) {
    char * in_text = NULL;
    char out_text[128] = {};
    int out_len = 0;
    ASSERT_STR("while(*s)", (out_len = 128, in_text = "whil##ilr#e(s#*s)",
        line_edit(in_text, strlen(in_text), out_text, &out_len), out_text));
    ASSERT_STR("get", (out_len = 128, in_text = "insfd212@get", 
        line_edit(in_text, strlen(in_text), out_text, &out_len), out_text));
    ASSERT_STR("while(*s)", ( out_len = 128, in_text = "out#char@whil##ilr#e(s#*s)",
        line_edit(in_text, strlen(in_text), out_text, &out_len), out_text));
}

int main(int argc, char const *argv[])
{
    int result = ctest_main(argc, argv);
    return result;
}

