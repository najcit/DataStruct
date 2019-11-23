// 队列是一种先进先出的线性表。
// 它只允许在表的一端进行插入，而在另一端删除。
// 最早进入队列的元素最早离开
// 在队列中允许插入的叫队尾 rear
// 在队列中允许删除的叫队头 front

typedef struct Queue Queue;
typedef struct Element Element;

int init_queue(Queue * q);

int destroy_queue(Queue * q);

int clear_queue(Queue * q);

int queue_empty(Queue * q);

int queue_length(Queue * q);

int queue_head(Queue * q);

int queue_end(Queue * q);

int enqueue(Queue * q, Element e);

int dequeue(Queue * q, Element &e);

typedef int (*Visit)(Element &e);
int queue_travese(Queue * q, Visit visit);