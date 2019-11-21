#include <stdlib.h>

typedef struct {
    int data;
}Element;

typedef struct Node {
    Element element;
    struct Node * next;
}Node, List;

// 初始化链表
int init_list(List* list)
{
    // 对于链表，不需要初始化
    if (list){ return -1;}
    return 0;
}

// 销毁链表
int destroy_list(List* list)
{
    Node * node = list;
    while (node) {
        // 获取下一个节点
        Node * next_node = node->next;
        // 销毁当前节点
        free(node);
        // 将下一个节点变为当前节点
        node = node->next;
    }
}

// 清空链表
int clear_list(List* list)
{
    // 链表清空也没有太大意义
    return 0;
}

// 链表是否为空
int list_empty(List* list)
{
    if (list->next) {
        return 0;
    }
    return 1;
}

// 链表元素个数
int list_length(List* list)
{
    int count = 0;
    Node * node = list;
    while (node) {
        count++;
        node = node->next;
    }
    return count;
}

// 获取链表元素
int get_element(List* list, int i, Element* element)
{
    int count = 0;
    Node * node = list;
    while (node) {
        if (i == count) {
            element->data = node->element.data;
            return 1;
        }
        count++;
        node = node->next;
    }
    return 0;
}

// 判定链表元素
typedef int (*Compare)(Element*, Element*);
int locate_element(List* list, Element* element, Compare compare)
{
    int count = 0;
    Node * node = list;
    while (node) {
        if (compare(&node->element, element)){
            return count;
        }

        count++;
        node = node->next;
    }
    return 0;
}


// 获取前一个元素
int prev_element(List* list, Element* cur_elemnet, Element* pre_element)
{
    int count = 0;
    Node * node = list;
    while (node) {
        if (node->element.data ==cur_elemnet->data){
            break;
        }
        count++;
        node = node->next;
    }

    int count2 = 0;
    node = list;
    while (node) {
        if (count2 == count)
        {
            pre_element->data = node->element.data;
            break;
        }
        count2++;
        node = node->next;
    }
    return 0;
}

// 获取下一个元素
int next_element(List* list, Element* cur_elemnet, Element* next_element)
{
    Node * node = list;
    while (node)
    {
        if (node->element.data == cur_elemnet->data) 
        {
            next_element->data = node->next->element.data;
            return 1;
        }
        node = node->next;
    }
    return 0;
}

// 链表插入一个元素
int list_insert(List* list, int i, Element* element)
{
    if (i == 0) 
    {
        Node * new_node = (Node *)malloc(sizeof(Node));
        new_node->element = *element;
        new_node->next = list;
        list = new_node;
        return 0;
    }

    int count = 0;
    Node * node = list;
    while (node) {
        if (count == i-1){
            // 创建一个新的节点
            Node * new_node = (Node *)malloc(sizeof(Node));
            new_node->element = *element;
            // 将新的节点的指针指向当前节点的指向的下一个节点           
            new_node->next = node->next;
            // 将当前节点的指针指向新的节点
            node->next = new_node;            
            break;
        }
        count++;
        node = node->next;
    }
    return 0;
}

// 链表删除一个元素
int list_delete(List* list, int i, Element* elemnet)
{
    if (i == 0)
    {
        list = list->next;
        return 0;
    } 

    int count = 0;
    Node * node = list;
    while (node) 
    {
        if (count == i-1)
        {
            // 获取当前节点
            Node * current_node = node->next;

            // 将当前节点的上一节点指向当前节点的下一个节点
            node->next = current_node->next;

            // 销毁当前节点
            free(current_node);
        }
        node = node->next;
    }
}

// 链表遍历元素
typedef int (*Visit)(Element* element);
int list_traverse(List* list, Visit visit)
{
    Node * node = list->next;
    while (node) 
    {
        visit(&node->element);
        node = node->next;
    }
    return 0;
}

// 合并链表 ,                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
int union_list(List* a, List* b);

// 归并有序链表
int meger_list(List* a, List* b);

int main() {
    int x = 2*9;
    return 0;
}