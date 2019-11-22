#ifdef TEST_STACK

#define CTEST_MAIN
#include "ctest.h"
#include <stdio.h>

int show(Element * e)
{
    printf("element data:%d\n", e->data);
    return 0;
}


CTEST(stack, call_test) {
    Stack s;
    Element e = {1};

    ASSERT_EQUAL(OK, init_stack(&s));
    
    ASSERT_EQUAL(true, stack_empty(&s));
    
    ASSERT_EQUAL(0, stack_length(&s));
    
    // 空栈获取失败
    ASSERT_EQUAL(ILLEGAL_OPT, stack_top(&s, &e));
    
    // 插入一个元素
    ASSERT_EQUAL(OK, stack_push(&s, e));
    
    // 非空栈
    ASSERT_EQUAL(false, stack_empty(&s));
    
    // 栈的长度
    ASSERT_EQUAL(1, stack_length(&s));

    // 移除一个元素
    ASSERT_EQUAL(OK, stack_pop(&s, &e));
    
    // 栈的长度 == 0
    ASSERT_EQUAL(0, stack_length(&s));

    // 再插入一个元素
    ASSERT_EQUAL(OK, stack_push(&s, e));

    // 清除栈
    ASSERT_EQUAL(OK, clear_stack(&s));
    
    // 空栈
    ASSERT_EQUAL(true, stack_empty(&s));
    
    // 栈的长度 == 0
    ASSERT_EQUAL(0, stack_length(&s));
    
    // 遍历栈
    ASSERT_EQUAL(OK, stack_traverse(&s, show));
    
    // 销毁栈
    ASSERT_EQUAL(OK, destroy_stack(&s));

    // 非法操作
    ASSERT_EQUAL(ILLEGAL_OPT, stack_top(&s, &e));
}

CTEST(stack, data_test) {
    Stack s;
    Element e = {1};
    Element e1 = {2};
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
