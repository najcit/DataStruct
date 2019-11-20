typedef struct {
    int data;
}Element;

typedef struct Node {
    Element element;
    struct Node * next;
}Node, List;

// 初始化线性表
int init_list(List* list);

// 销毁线性表
int destroy_list(List* list);

// 清空线性表
int clear_list(List* list);

// 线性表是否为空
int list_empty(List* list);

// 线性表元素个数
int list_length(List* list);

// 获取线性表元素
int get_element(List* list, int i, Element* element);

// 判定线性表元素
typedef int (*Compare)(Element*);
int locate_element(List* list, Element* element, Compare compare);

// 获取前一个元素
int prior_element(List* list, Element* cur_elemnet, Element* pre_element);

// 获取下一个元素
int next_element(List* list, Element* cur_elemnet, Element* next_element);

// 线性表插入一个元素
int list_insert(List* list, int i, Element* elemnet);

// 线性表删除一个元素
int list_delete(List* list, int i, Element* elemnet);

// 线性表遍历元素
typedef int (*Visit)(Element* element);
int list_traverse(List* list, Visit visit);

// 合并线性表
int union_list(List* a, List* b);

// 归并有序线性表
int meger_list(List* a, List* b);

int main() {
    return 0;
}