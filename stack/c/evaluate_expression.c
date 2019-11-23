// 任何一个表达式都是由操作数，运算符和界限符组成
// 操作数既可以是常数，也可以是变量或者常量标识符
// 运算符可以是算术运算胡，关系运算符，逻辑运算符
// 实现算法示意
// 可以使用2个工作栈
// 一个称之为 OPTR, 用以寄存运算符
// 另一个称之为 OPND, 用以寄存操作数和操作结果
// 将操作数栈，运算符栈置为空
// 依次出去表达中的字符，并判断是否类型存入对应的栈中
// 并获取运算符栈顶中的运算符比较优先级
#include "link_stack.c"
#include <stdio.h>
#include <string.h>

static bool is_operator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/'
        || ch == '(' || ch == ')')
    {
        return true;
    }
    return false;
}

static bool is_digital(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    return false;
}

typedef enum Operator
{
    Plus,
    Minus,
    Multi,
    Div,
    LeftB,
    RightB,
    Unknown,
} Operator;

static Operator conversion(const char ch)
{
    switch (ch)
    {
    case '+':
        return Plus;
    case '-':
        return Minus;
    case '*':
        return Multi;
    case '/':
        return Div;
    case '(':
        return LeftB;
    case ')':
        return RightB;
    default:
        break;
    }
    return Unknown;
}

// 运算符优先级关系
//      0   1   2   3   4   5
//      +   -   *   /   (   )
// 0 +  >   >   <   <   <   >
// 1 -  >   >   <   <   <   >
// 2 *  >   >   >   >   <   >
// 3 /  >   >   >   >   <   >
// 4 (  <   <   <   <   <   =
// 5 )  >   >   >   >       >
typedef enum Priority
{
    LT = -1, // <
    EQ = 0,  // ==
    MT = 1,  // >
    IL,      // 非法
}Priority;

static Priority precede_map[6][6] = 
{
    {MT, MT, LT, LT, LT, MT},
    {MT, MT, LT, LT, LT, MT},
    {MT, MT, MT, MT, LT, MT},
    {MT, MT, MT, MT, LT, MT},
    {LT, LT, LT, LT, LT, EQ},
    {MT, MT, MT, MT, IL, MT},
};

static Priority operator_precede(char ch1, char ch2)
{
    Operator p1 = conversion(ch1);
    Operator p2 = conversion(ch2);
    // printf("p1:%d, p2:%d\n", p1, p2);
    if (p1 != Unknown && p2 != Unknown)
    {
        return precede_map[p1][p2];
    }
    return IL;
}

static int operat(int x, int y, char opt)
{
    switch (opt)
    {
    case '+':
        return x + y;
    case '-':
        return x + y;
    case '*':
        return x * y;
    case '/':
        return x / y;
    default:
        break;
    }
    return -1;
}

// 给定一个表达式输出结果
int evaluate_expression (const char * expression, int * value)
{
    Stack optr, opnd;
    init_stack(&optr);
    init_stack(&opnd);

    int len = strlen(expression);
     Element element = {};
    for (int i = 0; i < len ; ++i)
    {
        char ch = expression[i];
        // printf("ch:%c\n", ch);
        if (is_operator(ch))
        {
            if (stack_empty(&optr))
            {
                element.data = ch;
                stack_push(&optr, element);
            }
            else 
            {
                // 获取栈顶的运算符
                stack_top(&optr, &element);
                char opt = element.data;
                Priority p = operator_precede(opt, ch);
                // printf("opt:%c, ch:%c, p:%d\n", opt, ch, p);
                switch (p)
                {
                // 优先级小于当前运算符栈顶的运算符
                // 先算运算符栈里面，并移除栈顶
                // 更新操作数栈
                case LT:
                    element.data = ch;
                    stack_push(&optr, element);
                    break;
                case EQ:
                    stack_pop(&optr, &element); 
                    break;
                case MT:
                    stack_pop(&optr, &element); 
                    stack_pop(&opnd, &element); 
                    int x = element.data;
                    stack_pop(&opnd, &element); 
                    int y = element.data;
                    int z = operat(x, y, opt);
                    element.data = z;
                    // printf("z:%d\n", z);
                    stack_push(&opnd, element);
                    i--; // 继续判断当前运算符和运算符栈的比较
                    break;
                default:
                    return -1;
                }
            }
        }
        else if (is_digital(ch))
        {
            int num = 0;
            while (is_digital(ch))
            {
                num = num * 10 + (ch - 48);
                ch = expression[++i];
            }
            i--;
            element.data = num;
            stack_push(&opnd, element);
        }
        else
        {
            return -1;
        }
    }

    // 经过检查,只需要按照栈的后进先出顺序计算即可
    while (!stack_empty(&optr))
    {
        stack_pop(&optr, &element); 
        char opt = element.data;
        stack_pop(&opnd, &element); 
        int x = element.data;
        stack_pop(&opnd, &element); 
        int y = element.data;
        int z = operat(x, y, opt);
        element.data = z;
        stack_push(&opnd, element);
    }

    // 输入最后结果
    stack_top(&opnd, &element); 
    *value = element.data;

    destroy_stack(&optr);
    destroy_stack(&opnd);
    return 0;
}

// int main(int argc, char const *argv[])
// {
//     int value = 0;
//     int result = 0;
//     result = evaluate_expression("4*5+7", &value);
//     printf("result:%d value:%d\n", result, value);
//     result = evaluate_expression("4*5", &value);
//     printf("result:%d value:%d\n", result, value);
//     result = evaluate_expression("4*(5+1)", &value);
//     printf("result:%d value:%d\n", result, value);
//     result = evaluate_expression("4+5*201", &value);
//     printf("result:%d value:%d\n", result, value);
//     return 0;
// }

#define CTEST_MAIN
#include "ctest.h"

CTEST(evaluate_expression, evaluate_expression) {
    int value = 0;
    ASSERT_EQUAL(20, (evaluate_expression("4*5", &value), value));
    ASSERT_EQUAL(27, (evaluate_expression("4*5+7", &value), value));
    ASSERT_EQUAL(48, (evaluate_expression("4*(5+7)", &value), value));
    ASSERT_EQUAL(-1, evaluate_expression("4*5+#7", &value));
}

int main(int argc, char const *argv[])
{
    int result = ctest_main(argc, argv);
    return result;
}


