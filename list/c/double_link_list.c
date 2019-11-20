// 双向链表的节点含有两个指针，一个指向后继，一个指向前置

typedef struct {
    int data;
}Element;

typedef struct Node {
    Element element;
    struct Node * prev;
    struct Node * next;
}Node, List;
