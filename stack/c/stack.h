// 栈是限定仅在表尾进行插入或者删除操作的线性表
// 表尾称之为栈顶，表头称之为栈底
// 不含元素的栈为空栈
// 栈的修改遵循后进先出的原则，故栈又叫后进先出(Last In First Out)

// 定义元素
typedef struct _Element Element; 

// 定义栈
typedef struct _Stack Stack;

// 初始化栈
int init_stack(Stack * stack);

// 销毁栈
int destroy_stack(Stack * stack);

// 清空栈
int clear_stack(Stack * stack);

// 栈是否为空
int stack_empty(Stack * stack);

// 栈的元素个数
int stack_length(Stack * stack);

// 栈定元素
int stack_top(Stack * stack, Element * element);

// 栈插入元素
int stack_push(Stack * stack, Element e);

// 栈移除元素
int stack_pop(Stack * stack, Element * element);

// 栈遍历
typedef int (*Visit)(Element *);
int stack_traverse(Stack * stack, Visit visit);
