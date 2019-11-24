// 队列是一种先进先出的线性表。
// 它只允许在表的一端进行插入，而在另一端删除。
// 最早进入队列的元素最早离开
// 在队列中允许插入的叫队尾 rear
// 在队列中允许删除的叫队头 front

typedef struct Queue Queue;
typedef struct Element Element;

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

Status init_queue(Queue * q);

Status destroy_queue(Queue * q);

Status clear_queue(Queue * q);

bool queue_empty(Queue * q);

int queue_length(Queue * q);

Status queue_head(Queue * q, Element * e);

Status queue_end(Queue * q, Element * e);

Status enqueue(Queue * q, Element e);

Status dequeue(Queue * q, Element * e);

typedef int (*Visit)(Element * e);
Status queue_traverse(Queue * q, Visit v);
