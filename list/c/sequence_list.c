#include <stdlib.h>
#include <string.h>

#define TEST
#define LIST_INIT_SIZE 100 
#define LIST_INCREAMENT 10 

// 线性表元素结构定义
typedef struct 
{
    int data;
} Element;

// 线性表结构定义
typedef struct 
{
    Element* elements; 
    int length;
    int size;
} List;

// 初始化线性表
int init_list(List* list)
{
    // 申请线性表初始化内存空间
    list->elements = (Element *)malloc(LIST_INIT_SIZE * sizeof(Element));
    if (!list->elements) {exit(-1);}

    // 记录线性表信息
    list->length = 0;
    list->size = LIST_INIT_SIZE;
}

// 销毁线性表
int destroy_list(List* list)
{
    // 销毁线性表申请的内存空间
    free(list->elements);
    list->elements = NULL;
    
    // 清楚线性表信息
    list->length = 0;
    list->size = 0;
}

// 清空线性表
int clear_list(List* list)
{
    if (list->elements && list->length > 0)
    {
        memset(list->elements, 0, sizeof(Element)*list->length);
        list->length = 0;
    }
    else
    {
        free(list->elements);
        list->elements = NULL;
        list->length = 0;
        list->size = 0;
    }
}

// 线性表是否为空
int list_empty(List* list)
{
    if (list->length > 0) {
        return 1;
    }
    return 0;
}

// 线性表元素个数
int list_length(List* list)
{
    return list->length;
}

// 获取线性表元素
int get_element(List* list, int i, Element* element)
{
    if (!list || !element) { return -1; }
    element->data = list->elements[i].data;
    return 0;
}

// 判定线性表元素
typedef int (*Compare)(Element*, Element*);
int locate_element(List* list, Element* element, Compare compare)
{
    if (!list || !element || !compare) { return -1; }

    for (int i = 0; i < list->length; i++) {
        if (compare(list->elements + i, element)) {
            return i;
        }
    }
    return 0;
}

// 获取前一个元素
int prior_element(List* list, Element* cur_elemnet, Element* pre_element)
{
    for (int i = 0; i < list->length; i++) {
        if (list->elements[i].data == cur_elemnet->data) {
            pre_element->data = list->elements[i-1].data;
            return 1;
        }
    }
    return 0;
}

// 获取下一个元素
int next_element(List* list, Element* cur_elemnet, Element* next_element)
{
    for (int i = 0; i < list->length; i++) {
        if (list->elements[i].data == cur_elemnet->data) {
            next_element->data = list->elements[i+1].data;
            return 1;
        }
    }
    return 0;
}

// 线性表插入一个元素
int list_insert(List* list, int i, Element* element)
{
    if (!list || !element || i < 0) { return -1; }

    if (i>= 0 && i < list->length){
        for (int j = list->length +1; j > i; j--)
        {
            list->elements[j] = list->elements[j-1];
        }
        list->length += 1; 
    } else if (i > list->length && i < list->size){
        list->elements[list->length+1] = *element;
    }
    return 0;
}

// 线性表删除一个元素
int list_delete(List* list, int i, Element* element)
{
    if (!list || !element || i < 0) { return -1; }

    if (i>= 0 && i < list->length){
        for (int j = 0; j < list->length; j++)
        {
            list->elements[j] = list->elements[j+1];
        }
        list->length -= 1; 
    }
}

// 线性表遍历元素
typedef int (*Visit)(Element* element);
int list_traverse(List* list, Visit visit)
{
    if (!list) { return -1; }

    for (int i =0; i < list->length; ++i) {
        visit(list->elements+i);
    }
    return 0;
}

// 合并线性表
int union_list(List* a, List* b);

// 归并有序线性表
int meger_list(List* a, List* b);


// 测试用例
#ifdef TEST
int main() {
    return 0;
}
#endif