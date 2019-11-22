// 表达式中允许圆括号和方括号，其嵌套的顺序是随意
// [](), [()] [()()]等都是合法的
// (([)),(() 等是不合法的
// 算法大意如下：
// 再算法中设置一个栈，每读入一个括号，若是右括号，
// 则或者使置于栈顶的最紧急的期待消除，或者是不合法的清空
// 若是左括号，则作为一个最紧急的期待压入栈顶
// 使原有的栈中的所有最紧急期待降一级
// 在算法的开始和结束时，栈都应该是空的

#include "link_stack.c"
#include <stdio.h>

// 检验给定的字符是否右括号
static bool is_right_brackets(char ch)
{
    if (ch == ']' || ch == ')' || ch == '}')
    {
        return true;
    }
    return false;
}

// 检验给定的字符是否左括号
// 返回 0 不是
// 返回-1 是
static bool is_left_brackets(char ch)
{
    if (ch == '[' || ch == '(' || ch == '{')
    {
        return true;
    }
    return false;
}

static bool match_bracket(char ch1, char ch2)
{
    if (ch1 == '[' && ch2 == ']')
    {
        return true;
    }
    if (ch1 == '{' && ch2 == '}')
    {
        return true;
    }
    if (ch1 == '(' && ch2 == ')')
    {
        return true;
    }
    return false;
}

// 检验指定的内容中括号匹配是否合法
// 返回 true  正常
// 返回 false 非法 例如 [(] ())
bool brackets_math(char * content, int len)
{
    // 初始化栈
    Stack stack;
    init_stack(&stack);
    
    for (int i =0; i < len; ++i)
    {
        // 如果当前字符是右括号
        // 获取当前栈顶字符
        // 没有，就是不合法
        // 有，判断是否匹配
        // 不匹配，就是不合法
        // 匹配，消除栈顶，进行下一步
        char ch = content[i];
        if (is_right_brackets(ch))
        {
            // printf("right:%c\n", ch);
            if (stack_empty(&stack)) 
            {
                return false;
            }   
            else
            {
                Element element = {0};
                if (OK != stack_top(&stack, &element))
                {
                    return false;
                }
                char top_ch = element.data;
                if (match_bracket(top_ch, ch)) 
                {
                    stack_pop(&stack, &element);
                }
                else
                {
                    return false;
                }
            }
        }

        // 如果是左括号，直接压入栈顶
        if (is_left_brackets(ch))
        {
            // printf("left:%c\n", ch);
            Element element = {0};
            element.data = ch;
            stack_push(&stack, element);
        }
    }

    // 遍历所有括号后，需检查是否为空栈
    if (stack_empty(&stack))
    {
        return true;
    }
    else 
    {
        return false;
    }

    // 销毁栈
    destroy_stack(&stack);

    return true;
}

// int main(int argc, char const *argv[])
// {
//     printf("result:%d\n", brackets_math("[()]", 4));
 
//     printf("result:%d\n", brackets_math("[()][", 5));

//     printf("result:%d\n", brackets_math("[[()]", 5));

//     printf("result:%d\n", brackets_math("[[]()]{}", 8));

//     return 0;
// }

#define CTEST_MAIN
#include "ctest.h"

CTEST(brackets_math, brackets_math_test) {
    ASSERT_EQUAL(true, brackets_math("[()]", 4));
    ASSERT_EQUAL(false, brackets_math("[[[]", 4));
    ASSERT_EQUAL(false, brackets_math("[()][", 5));
    ASSERT_EQUAL(true, brackets_math("[()][]", 6));
    ASSERT_EQUAL(true, brackets_math("{[()][]}", 8));
}

int main(int argc, char const *argv[])
{
    int result = ctest_main(argc, argv);
    return result;
}
