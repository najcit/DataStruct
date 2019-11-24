// 用一组连续地址的存储单元实现队列
// 会出现插入一个新元素，造成数组越界，而破坏程序
// 且删除的元素，内存有没有使用，基于此
// 将队头和队尾连在一起，形成循环队列
// 循环队列使用一位数组实现
// 必须为它设置一个最大队列长度
// 其中如何判断队列是否为满和空的状态
// 1. 增加一个标志位
// 2. 约定一个在队头的上一个的存储单元，即队尾的下一个存储单元不使用
#include <stdlib.h>
#include <string.h>

#define QUEUE_MAX_SIZE 100

typedef struct Element
{
    int data;
}Element;

typedef struct Queue
{
    Element * base;
    int front;
    int rear;
}Queue;

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
    q->base = (Element *)malloc(sizeof(Element) * QUEUE_MAX_SIZE);
    if (!q->base){ return OVER_FLOW; }
    memset(q->base, 0, sizeof(Element) * QUEUE_MAX_SIZE);
    q->front = q->rear = 0;
    return OK;
}

Status destroy_queue(Queue * q)
{
    if (!q) { return WRONG_INPUT; }
    free(q->base);
    q->front = q->rear = 0;
    return OK;
}

Status clear_queue(Queue * q)
{
    if (!q) { return WRONG_INPUT; }
    if (!q->base) { return WRONG_INPUT; }
    memset(q->base, 0, sizeof(Element) * QUEUE_MAX_SIZE);
    q->front = q->rear = 0;
    return OK;
}

bool queue_empty(Queue * q)
{
    if (!q) { return WRONG_INPUT; }
    if ((q->rear - q->front) != 0)
    {
        return false;
    }
    return true;
}

int queue_length(Queue * q)
{
    if (!q) { return WRONG_INPUT; }
    return (q->rear - q->front + QUEUE_MAX_SIZE) % QUEUE_MAX_SIZE;
}

Status queue_head(Queue * q, Element * e)
{
    if (!q) { return WRONG_INPUT; }
    if (!q->base) { return WRONG_INPUT; }
    if (queue_empty(q)) { return WRONG_INPUT; }
    *e = q->base[q->front % QUEUE_MAX_SIZE];
    return OK;
}

Status queue_end(Queue * q, Element * e)
{
    if (!q) { return WRONG_INPUT; }
    if (!q->base) { return WRONG_INPUT; }
    if (queue_empty(q)) { return WRONG_INPUT; }
    *e = q->base[q->rear - 1 % QUEUE_MAX_SIZE];
    return OK;
}

Status enqueue(Queue * q, Element e)
{
    if (!q) { return WRONG_INPUT; }
    if (!q->base) { return WRONG_INPUT; }
    // 队列已满
    if ((q->rear + 1) % QUEUE_MAX_SIZE == q->front){ return ILLEGAL_OPT; }
    q->base[q->rear] = e;
    q->rear = (q->rear + 1) % QUEUE_MAX_SIZE;
    return OK;
}

Status dequeue(Queue * q, Element * e)
{
    if (!q) { return WRONG_INPUT; }
    if (!q->base) { return WRONG_INPUT; }
    // 队列已空
    if (queue_empty(q)) { return WRONG_INPUT; }
    *e = q->base[q->front];
    q->front = (q->front + 1) % QUEUE_MAX_SIZE;
    return OK;
}

typedef int (*Visit)(Element * e);
Status queue_traverse(Queue * q, Visit v)
{
    if (!q) { return WRONG_INPUT; }
    if (!q->base) { return WRONG_INPUT; }
    for (int i = 0; i < queue_length(q); ++i)
    {
        v(&q->base[(q->front +i) % QUEUE_MAX_SIZE]);
    }
    return OK;
}

#define TEST_QUEUE 
#include "test_queue.h"
