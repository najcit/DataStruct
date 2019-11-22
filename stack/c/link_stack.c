#include <stdlib.h>

typedef struct Element 
{
    int data;
} Element;

typedef struct Node 
{
    Element element;
    struct Node * next;
} Node;


typedef struct Stack
{
    Node * top;
    Node * base;
    int stack_length;
} Stack;

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

// 初始化栈
Status init_stack(Stack * stack)
{
    if (!stack) { return WRONG_INPUT; }
    stack->base = (Node *)malloc(sizeof(Node));
    if (!stack->base) { return OVER_FLOW; }
    stack->base->element.data = -1;
    stack->base->next = NULL;
    stack->top = stack->base;
    // 头元素不算
    stack->stack_length = 0;
    return OK;
}

// 销毁栈
Status destroy_stack(Stack * stack)
{
    if (!stack) { return WRONG_INPUT; }
    if (!stack->base) { return WRONG_INPUT; }
    Node * node = stack->base;
    while (node)
    {
        Node * next_node = node->next;
        free(node);
        node->next = NULL;
        node = next_node;
    }
	stack->base = NULL;
	stack->top = NULL;
    stack->stack_length = 0;
    return OK;
}

// 清空栈
Status clear_stack(Stack * stack)
{
    if (!stack) { return WRONG_INPUT; }
    if (!stack->base) { return WRONG_INPUT; }
    // 指向头元素的下一个元素，保留头元素不被销毁
    Node * e = stack->base->next;
    while (e)
    {
        Node * next_element = e->next;
        free(e);
        e = next_element;
    }
    // 将栈顶元素指向栈底
	stack->base->element.data = -1;
	stack->base->next = NULL;
    stack->top = stack->base;
    stack->stack_length = 0;
    return OK;
}

// 栈是否为空
bool stack_empty(Stack * stack)
{
    if (!stack) { return WRONG_INPUT; }
    if (stack->stack_length == 0) { return true; }
    return false;
}

// 栈的元素个数
int stack_length(Stack * stack)
{
    if (!stack) { return WRONG_INPUT; }
    return stack->stack_length;
}

// 栈定元素
Status stack_top(Stack * stack, Element * element)
{
    if (!stack) { return WRONG_INPUT; }
    if (stack_empty(stack)) { return ILLEGAL_OPT; }
    if (!element) { return WRONG_INPUT; }
    *element = stack->top->element;
    return OK;
}

// 栈插入元素
Status stack_push(Stack * stack, Element element)
{
    if (!stack) { return WRONG_INPUT; }
    if (!stack->top) { return WRONG_INPUT; }
    // 构建一个新的元素
    Node * node = (Node *)malloc(sizeof(Node));
    if (!node) { return OVER_FLOW; }
    node->element = element;
    node->next = NULL;
    // // 将当前栈顶指向新的元素
    stack->top->next = node;
    // // 将新元素视为栈顶
    stack->top = node;
    stack->stack_length++;
    return OK;
}

// 栈移除元素
Status stack_pop(Stack * stack, Element * element)
{
    if (!stack) { return WRONG_INPUT; }
    if (!element) { return WRONG_INPUT; }
    if (!stack->base) { return WRONG_INPUT; }
    if (!stack->top) { return WRONG_INPUT; }
    Node * node = stack->base;
    while (node)
    {
        if (node->next == stack->top)
        {
            // 销毁栈顶
            *element = stack->top->element;
            free(stack->top);

            // 将当前节点设置栈顶
            stack->top = node;
            stack->top->next = NULL;
            stack->stack_length--;
            break;
        }
        node = node->next;
    }
    return OK;
}

// 栈遍历
typedef int (*Visit)(Element *);
Status stack_traverse(Stack * stack, Visit visit)
{
    if (!stack) { return WRONG_INPUT; }
    if (!visit) { return WRONG_INPUT; }
    Node * node = stack->base->next;
    while (node)
    {
        visit(&(node->element));
        node = node->next;
    }
    return OK;
}

// 测试用例开关
// 注释 #define TEST_STACK 则不包含测试用例
// #define TEST_STACK
#ifdef TEST_STACK
#include "test_stack.h"
#endif
