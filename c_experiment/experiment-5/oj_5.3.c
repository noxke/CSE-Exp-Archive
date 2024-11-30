#include <stdio.h>
#include <malloc.h>
typedef char bool;
#define true 1
#define false 0

bool is_safe(bool *board, int i, int j, int n);    // 检查第i行第j列是否安全
void n_queen(bool *board, int i, int n, int *ans); // 第i行皇后

int main()
{
    int n;
    scanf("%d", &n);
    int ans = 0;                                // 记录结果
    bool *board = malloc(sizeof(bool) * n * n); // 棋盘
    for (int i = 0; i < n * n; i++)
    {
        *(board + i) = false;
    }
    n_queen(board, 0, n, &ans);
    if (ans > 0)
    {
        printf("%d", ans);
    }
    else
    {
        printf("无解");
    }
}

void n_queen(bool *board, int i, int n, int *ans)
{
    if (i >= n) // 递归结束
    {
        *ans = *ans + 1;
    }
    else
    {
        int j;
        for (j = 0; j < n; j++)
        {
            if (is_safe(board, i, j, n))    // 如果当前位置可以放置皇后，则继续检查下一行放置皇后的位置
            {
                *(board + i * n + j) = true;    // 在此位置放置皇后
                n_queen(board, i + 1, n, ans);  // 进行下一行
                *(board + i * n + j) = false;   // 将皇后取出，检查下一列
            }
        }
    }
}

bool is_safe(bool *board, int i, int j, int n)
{
    int m, k;
    // 检查列上是否有皇后
    for (m = i - 1, k = j; m >= 0; m--)
    {
        if (*(board + m * n + k))    // 上方有皇后
        {
            return false;
        }
    }
    // 检查左对角线上是否有皇后
    for (m = i - 1, k = j - 1; (m >= 0) && (k >= 0); m--, k--)
    {
        if (*(board + m * n + k))    // 左对角线有皇后
        {
            return false;
        }
    }
    // 检查右对角线上是否有皇后
    for (m = i - 1, k = j + 1; (m >= 0) && (k < n); m--, k++)
    {
        if (*(board + m * n + k))    // 右对角线有皇后
        {
            return false;
        }
    }
    return true;
}