// 迷宫求解从入口到出口的所有路径的问题
// 一般解法是从入口开始沿着某一方向走，
// 直至走到死胡同，再换一个方向走，
// 直至走到出口


#include "link_stack.c"
#include <stdio.h>

// 10X10 的迷宫
// 所在位置为 0，可走
// 所在位置为 1，障碍
// 所在位置为 2，入口
// 所在位置为 3，出口
static int maze[10][10] = 
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

typedef struct _Position
{
    int x;
    int y;
}Position;

// 获取迷宫中指定位置的相通的位置
// 最多四个相同位置
static int get_next_positions(int(*maze)[10], Position p, Position * positions, int *size)
{
    if (p.x >= 1 && p.x <= 8 && p.y >= 1 && p.y <= 8)
    {
        if (maze[p.x-1][p.y] == 0)
        {
            positions[0].x = p.x - 1;
            positions[0].y= p.y;
            (*size)++;
        }
        else
        {
            positions[0].x = -1;
            positions[0].y = -1;
        }

        if (maze[p.x+1][p.y] == 0)
        {
            positions[1].x = p.x + 1;
            positions[1].y = p.y;
            (*size)++;
        }
        else
        {
            positions[1].x = -1;
            positions[1].y = -1;
        }

        if (maze[p.x][p.y-1] == 0)
        {
            positions[2].x = p.x;
            positions[2].y = p.y - 1;
            (*size)++;
        }
        else
        {
            positions[2].x = -1;
            positions[2].y = -1;
        }

        if (maze[p.x][p.y+1] == 0)
        {
            positions[3].x = p.x;
            positions[3].y = p.y + 1;
            *size++;
        }
        else
        {
            positions[3].x = -1;
            positions[3].y= -1;
        }
    }
    else
    {
        return -1;
    }
    
    return 0;
}

int position_to_data(Position p)
{
    return p.x * 10 + p.y;
}

Position data_to_position(int data)
{
    Position p;
    p.x = data / 10;
    p.y = data % 10;
    return p;
}

// 从给定的迷宫中找到一条可以从入口通向出口的路径
// 用坐标表示，从左上角为起点（1，1），右下角为终点（8，8）
// 目前是10X10的布局
int maze_path(int(*maze)[10], Position * path, int * size)
{
    // 初始化栈
    Stack stack;
    init_stack(&stack);

    // 迷宫
    Element element = {};
    int dead_pos_num = 0;
    Position dead_pos[100] = {};
    Position start = {1, 1};
    Position end = {8, 8};
    Position positions[4] = {};
    Position p = start;
    element.data = position_to_data(p);
    stack_push(&stack, element);
    while (true)
    {
        // printf("p.x:%d, p.y:%d\n", p.x, p.y);
        int pos_size = 0;
        if (-1 == get_next_positions(maze, p, positions, &pos_size)){ return -1; }
        bool is_dead_pos = true;
        for (int i = 0 ;i < 4; i++)
        {
            // 过滤障碍位置
            if (positions[i].x == -1 || positions[i].y == -1) { continue; }

            // 判断坐标中是否存在死胡同坐标
            bool is_push = true;
            for (int j = 0; j < dead_pos_num; ++j)
            {
                if (positions[i].x == dead_pos[j].x && positions[i].y == dead_pos[j].y)
                {
                    is_push = false;
                    break;
                }
            }

            // 判断当前位置是否已压入栈
            if (is_push)
            {
                element.data = position_to_data(positions[i]);
                if (!stack_find(&stack, element))
                {
                    is_dead_pos = false;
                    stack_push(&stack, element);
                }            
            }

            // 是否为出口
            if (positions[i].x == end.x && positions[i].y == end.y){
                *size = stack_length(&stack);
                int i = *size - 1;
                while (!stack_empty(&stack)) 
                {
                    stack_pop(&stack, &element);
                    path[i--] = data_to_position(element.data);
                }
                destroy_stack(&stack);
                return 0;
            }
        }

        // 如果是死胡同，则移除栈顶
        if (is_dead_pos) {
            stack_pop(&stack, &element);
            Position pos = data_to_position(element.data);
            if (dead_pos_num >= 100) { return -1;}
            dead_pos[dead_pos_num] = pos;
            dead_pos_num++;
        }

        // 将栈顶坐标为当前位置
        if (!stack_empty(&stack))
        {
            stack_top(&stack, &element);
            p = data_to_position(element.data);
        }
        else
        {
            break;
        }
    }

    // 销毁栈
    destroy_stack(&stack);
    return -1;
}

int main(int argc, char const *argv[])
{
    Position path[100] = {};
    int num = 0;
    int result = maze_path(maze, path, &num);
    printf("result:%d\n", result);
    for (int i = 0; i < num; ++i)
    {
        Position p = path[i];
        printf("p.x:%d, p.y:%d\n", p.x, p.y);
    }
    return 0;
}

