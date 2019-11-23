// 链式队列用链表实现的队列
#include <stdlib.h>
#include <stdio.h>

typedef struct Element
{
    int data;
} Element;

typedef struct Node {
    Element element;
    struct Node * next;
} Node;

typedef struct Queue{
    struct Node * front;
    struct Node * rear;
    int len;
} Queue;

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

Status init_queue(Queue * q)
{
    if (!q) { return WRONG_INPUT; }
    q->front = (Node *)malloc(sizeof(Node));
    if (!q->front) { return OVER_FLOW; }
    q->front->next = NULL;
    q->rear = q->front;
    q->len = 0;
    return OK;
}

Status destroy_queue(Queue * q)
{
    if (!q) { return WRONG_INPUT; }
    Node * n = q->front;
    while (n)
    {
        Node * next = n->next;
        free(n);
        n = next;
    }
    q->front = NULL;
    q->rear = NULL;
    q->len = 0;
    return OK;
}

Status clear_queue(Queue * q)
{
    if (!q) { return WRONG_INPUT; }
    if (!q->front) { return WRONG_INPUT; }
    Node * n = q->front->next;
    while (n)
    {
        Node * next = n->next;
        free(n);
        n = next;
    }
    q->front->next = NULL;
    q->rear = q->front;
    q->len = 0;
    return OK;
}

bool queue_empty(Queue * q)
{
    if (!q) { return WRONG_INPUT; }
    if (q->len != 0)
    {
        return false;
    }
    return true;
}

int queue_length(Queue * q)
{
    if (!q) { return WRONG_INPUT; }
    return q->len;
}

Status queue_head(Queue * q, Element * e)
{
    if (!q) { return WRONG_INPUT; }
    if (!q->front) { return WRONG_INPUT; }
    if (!q->front->next) { return WRONG_INPUT; }
    if (!e) { return WRONG_INPUT; }
    *e = q->front->next->element;
    return OK;
}

Status queue_end(Queue * q, Element * e)
{
    if (!q) { return WRONG_INPUT; }
    if (!q->rear) { return WRONG_INPUT; }
    if (!e) { return WRONG_INPUT; }
    *e = q->rear->element;
    return OK;
}

Status enqueue(Queue * q, Element e)
{
    if (!q) { return WRONG_INPUT; }
    if (!q->rear) { return WRONG_INPUT; }
    Node * n = (Node *)malloc(sizeof(Node));
    if (!n) { return OVER_FLOW; }
    n->element = e;
    n->next = NULL;
    q->rear->next = n;
    q->rear = n;
    q->len++;
    return OK;
}

Status dequeue(Queue * q, Element * e)
{
    if (!q) { return WRONG_INPUT; }
    if (!e) { return WRONG_INPUT; }
    if (!q->front) { return WRONG_INPUT; }
    if (!q->front->next) { return WRONG_INPUT; }
    // 空节点不算有效数据区
    Node * n = q->front->next;
    *e = n->element;
    q->front->next = n->next;
    // 把头节点给删除了，所以队尾也是空
    if (!q->front) {q->rear = NULL;}
    q->len--;
    free(n);
    n = NULL;
    return OK;
}

typedef int (*Visit)(Element * e);
Status queue_traverse(Queue * q, Visit v)
{
    if (!q) { return WRONG_INPUT; }
    if (!v) { return WRONG_INPUT; }
    Node * n = q->front;
    while (n)
    {
        v(&(n->element));
        n = n->next;
    }
    return OK;
}

#define TEST_QUEUE 
#ifdef TEST_QUEUE

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

#define CTEST_MAIN
#include "ctest.h"

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

    ASSERT_EQUAL(OK, dequeue(&q, &e));
    
    ASSERT_EQUAL(0, queue_length(&q));

    ASSERT_EQUAL(OK, enqueue(&q, e));

    ASSERT_EQUAL(OK, clear_queue(&q));
    
    ASSERT_EQUAL(true, queue_empty(&q));
    
    ASSERT_EQUAL(0, queue_length(&q));
    
    ASSERT_EQUAL(OK, queue_traverse(&q, show));
    
    ASSERT_EQUAL(OK, destroy_queue(&q));

    ASSERT_EQUAL(WRONG_INPUT, queue_head(&q, &e));
}

int main(int argc, char const *argv[])
{
    int result = ctest_main(argc, argv);
    return result;
}

#endif