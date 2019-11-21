// 顺序栈，即栈的顺序存储结构是利用一组地址连续的存储单元依次存放自栈底到栈定的数据元素
// 同时附设指针top指示栈顶元素在顺序栈中的位置
#include <stdlib.h>
#define STACK_INIT_SIZE 100
#define STACK_INCREAMENT 10

// 栈元素
typedef struct Element
{
    int data;
} Element;

// 顺序栈
typedef struct Stack
{
    Element * base; // 栈底指针
    Element * top;  // 栈顶指针
    int stack_size; // 栈元素个数
} Stack;

// 函数返回值
typedef enum Status
{
    OK,
    UNKNOWN_ERR,
    WRONG_INPUT,
    ILLEGAL_OPT,
    OVER_FLOW
} Status;

typedef enum bool
{
    false,
    true
} bool;

// 初始化栈
Status init_stack(Stack * stack)
{
    if (!stack) { return WRONG_INPUT; }
    stack->base = (Element *)malloc(sizeof(Element)*STACK_INIT_SIZE);
    if (!stack->base) { return OVER_FLOW; }
    // 构造一个空栈
    stack->top = stack->base;
    stack->stack_size = STACK_INIT_SIZE;
    return OK;
}

// 销毁栈
Status destroy_stack(Stack * stack)
{
    if (!stack) { return WRONG_INPUT; }
    free(stack->base);
    stack->base = NULL;
    stack->top = NULL;
    stack->stack_size = 0;
    return OK;
}

// 清空栈
Status clear_stack(Stack * stack)
{
    if (!stack) { return WRONG_INPUT; }
    // 将 top 置为 base，变为空栈
    stack->top = stack->base;
    return OK;
}

// 栈是否为空
bool stack_empty(Stack * stack)
{
    if (!stack) { return WRONG_INPUT; }
    if (!stack->top) { return WRONG_INPUT; }
    if (!stack->base) { return WRONG_INPUT; }
    // top指针不是base指针，则含有元素
    if (stack->top != stack->base)
    {
        return false;
    }
    return true;
}

// 栈的元素个数
int stack_length(Stack * stack)
{
    if (!stack) { return WRONG_INPUT; }
    if (!stack->top) { return WRONG_INPUT; }
    if (!stack->base) { return WRONG_INPUT; }
    int length = stack->top - stack->base;
    return length;
}

// 栈定元素
Status stack_top(Stack * stack, Element * element)
{
    if (!stack) { return WRONG_INPUT; }
    if (stack_empty(stack)) { return ILLEGAL_OPT;}
    if (!element) { return WRONG_INPUT; }
    *element = *(stack->top - 1);    
    return OK;
}

// 栈插入元素
Status stack_push(Stack * stack, Element element)
{
    if (!stack) { return WRONG_INPUT; }
    int length = stack_length(stack);
    // 需要申请空间
    if (length >= STACK_INIT_SIZE) 
    {
        stack->base = (Element *)realloc(stack->base, (stack->stack_size + STACK_INCREAMENT) * sizeof(Element));
        if (stack->base) { return OVER_FLOW; }
        stack->top = stack->base + length;
        stack->stack_size += STACK_INCREAMENT;
    }
    *stack->top++ = element;
    return OK;
}

// 栈移除元素
Status stack_pop(Stack * stack, Element * element)
{
    if (!stack) { return WRONG_INPUT; }
    if (!element) { return WRONG_INPUT; }
    if (stack_empty(stack)) { return ILLEGAL_OPT;}
    *element = *--stack->top;
    return OK;
}

// 栈遍历
typedef int (*Visit)(Element *);
Status stack_traverse(Stack * stack, Visit visit)
{
    if (!stack) { return WRONG_INPUT; }
    if (!stack->base) { return WRONG_INPUT; }
    if (!stack->top) { return WRONG_INPUT; }
    if (!visit) { return WRONG_INPUT; }
    Element * e = stack->base;
    while (e != stack->top) 
    {
        visit(e);
        e ++;
    }
    return OK;
}

#define TEST_STACK
#ifdef TEST_STACK

#define CTEST_MAIN
#include "ctest.h"

int show(Element * e)
{
    printf("element:%d\n", e->data);
    return 0;
}

CTEST(stack, call_test) {
    Stack s;
    Element e = {0};
    ASSERT_EQUAL(OK, init_stack(&s));
    ASSERT_EQUAL(true, stack_empty(&s));
    ASSERT_EQUAL(0, stack_length(&s));
    ASSERT_EQUAL(ILLEGAL_OPT, stack_top(&s, &e));
    ASSERT_EQUAL(OK, stack_push(&s, e));
    ASSERT_EQUAL(false, stack_empty(&s));
    ASSERT_EQUAL(1, stack_length(&s));

    ASSERT_EQUAL(OK, stack_push(&s, e));
    ASSERT_EQUAL(OK, stack_push(&s, e));
    ASSERT_EQUAL(3, stack_length(&s));

    ASSERT_EQUAL(OK, stack_pop(&s, &e));
    ASSERT_EQUAL(2, stack_length(&s));

    ASSERT_EQUAL(OK, clear_stack(&s));
    ASSERT_EQUAL(true, stack_empty(&s));
    ASSERT_EQUAL(0, stack_length(&s));
    ASSERT_EQUAL(OK, stack_traverse(&s, show));
    ASSERT_EQUAL(OK, destroy_stack(&s));
}

CTEST(stack, data_test) {
    Stack s;
    Element e = {1};
    Element e1 = {0};
    ASSERT_EQUAL(OK, init_stack(&s));
    ASSERT_EQUAL(0, stack_length(&s));
    ASSERT_EQUAL(ILLEGAL_OPT, stack_top(&s, &e));

    ASSERT_EQUAL(OK, stack_push(&s, e));
    ASSERT_EQUAL(false, stack_empty(&s));
    ASSERT_EQUAL(1, stack_length(&s));

    ASSERT_EQUAL(OK, stack_push(&s, e));
    ASSERT_EQUAL(OK, stack_push(&s, e));

    ASSERT_EQUAL(false, stack_empty(&s));
    ASSERT_EQUAL(3, stack_length(&s));

    ASSERT_EQUAL(OK, stack_top(&s, &e1));
    ASSERT_EQUAL(e.data, e1.data);

    ASSERT_EQUAL(OK, stack_pop(&s, &e));
    ASSERT_EQUAL(2, stack_length(&s));

    ASSERT_EQUAL(OK, clear_stack(&s));
    ASSERT_EQUAL(true, stack_empty(&s));
    ASSERT_EQUAL(0, stack_length(&s));
    ASSERT_EQUAL(OK, destroy_stack(&s));
}

int main(int argc, char const *argv[])
{
    int result = ctest_main(argc, argv);
    return result;
}

#endif
