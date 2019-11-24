#ifdef TEST_QUEUE
#include <stdio.h>
#define CTEST_MAIN
#include "ctest.h"

int show (Element * e)
{
    printf("data:%d\n", e->data);
    return 0;
}

// int main(int argc, char const *argv[])
// {
//     Status s = OK;
//     bool empty = false;
//     int len = 0;
//     Queue q;
//     s = init_queue(&q);
//     printf("init_queue:Status:%d\n", s);
//     empty = queue_empty(&q);
//     printf("empty:%d\n", empty);
//     len = queue_length(&q);
//     printf("len:%d\n", len);

//     Element e1 = {1};
//     Element e2 = {2};
//     Element e3 = {3};
//     Element e4 = {4};
//     s = enqueue(&q, e1);
//     printf("enqueue:Status:%d\n", s);
//     len = queue_length(&q);
//     printf("len:%d\n", len);
//     s = enqueue(&q, e2);
//     printf("enqueue:Status:%d\n", s);
//     s = enqueue(&q, e3);
//     printf("enqueue:Status:%d\n", s);
//     s = enqueue(&q, e4);
//     printf("enqueue:Status:%d\n", s);

//     len = queue_length(&q);
//     printf("len:%d\n", len);

//     Element e = {};
//     s = dequeue(&q, &e);
//     printf("dequeue:Status:%d, e:%d\n", s, e.data);

//     s = dequeue(&q, &e);
//     printf("dequeue:Status:%d, e:%d\n", s, e.data);

//     s = dequeue(&q, &e);
//     printf("dequeue:Status:%d, e:%d\n", s, e.data);

//     len = queue_length(&q);
//     printf("len:%d\n", len);

//     s = clear_queue(&q);
//     printf("clear_queue:Status:%d\n", s);

//     len = queue_length(&q);
//     printf("len:%d\n", len);

//     s = destroy_queue(&q);
//     printf("destroy_queue:Status:%d\n", s);

//     s = dequeue(&q, &e);
//     printf("dequeue:Status:%d, e:%d\n", s, e.data);

//     return 0;
// }


CTEST(queue, call_test) {
    Queue q;
    Element e = {1};

    ASSERT_EQUAL(OK, init_queue(&q));
    
    ASSERT_EQUAL(true, queue_empty(&q));
    
    ASSERT_EQUAL(0, queue_length(&q));
    
    ASSERT_EQUAL(WRONG_INPUT, queue_head(&q, &e));
    
    ASSERT_EQUAL(OK, enqueue(&q, e));
    
    ASSERT_EQUAL(false, queue_empty(&q));
    
    ASSERT_EQUAL(1, queue_length(&q));

    ASSERT_EQUAL(OK, queue_traverse(&q, show));

    ASSERT_EQUAL(OK, dequeue(&q, &e));
    
    ASSERT_EQUAL(0, queue_length(&q));

    ASSERT_EQUAL(OK, enqueue(&q, e));

    ASSERT_EQUAL(OK, clear_queue(&q));
    
    ASSERT_EQUAL(true, queue_empty(&q));
    
    ASSERT_EQUAL(0, queue_length(&q));
        
    ASSERT_EQUAL(OK, destroy_queue(&q));

    ASSERT_EQUAL(WRONG_INPUT, queue_head(&q, &e));
}

int main(int argc, char const *argv[])
{
    int result = ctest_main(argc, argv);
    return result;
}

#endif