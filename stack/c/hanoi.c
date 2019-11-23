// n 阶Hanoi塔问题
// 假如有3个分别 X, Y和Z的塔座，
// 在塔座X上有n个直径大小各不相同，
// 依次编号为1, 2, 3 ..., n的圆盘
// 将X上的圆盘全部移到Z塔座上
// 需遵循以下规则
// 1. 每次只能移动一个圆盘
// 2. 圆盘可以移到任何一个塔座上
// 3. 任何时刻都不能将较大的圆盘放到较小的圆盘上
// 算法示意如下
// 当n=1时，圆盘直接放到Z上
// 当n>1时，需利用Y辅助，
// 如果设法完成将n-1个圆盘放置到Y上，
// 只需将n圆盘移到Z上即可
// 故，解决n阶圆盘的问题变成了n-1阶圆盘问题

#include <stdio.h>

// 将 X 上的 n 圆盘移到 Y上
void move (int n , char x, char y)
{
    static int count  = 0;
    printf("(%d) %d:[%c]->[%c]\n", ++count, n, x, y);
}

void hanoi(int n, char x, char y, char z)
{
    if (n == 1)
    {
        move(n, x, z);
    }
    else
    {
        // 将 n-1 个圆盘从 X 通过 Z 移到 Y
        hanoi(n-1, x, z, y); 
        // 将 n 圆盘 从 X 移到 Z
        move(n, x, z);
        // 将 n-1 个圆盘从 Y 通过 X 移到 Z
        hanoi(n-1, y, x, z);
    }
}

int main(int argc, char const *argv[])
{
    hanoi(4, 'X', 'Y', 'Z');
    return 0;
}

