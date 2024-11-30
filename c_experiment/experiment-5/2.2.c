#include <stdio.h>
#define M 10
#define N 3
int main(void)
{
    int a[M], b[M]; /* 数组a存放圈中人的编号，数组b存放出圈人的编号 */

    int out[M] = {0}; // 标记出圈的人

    int i, j, k;
    for (i = 0; i < M; i++) /* 对圈中人按顺序编号1—M */
        a[i] = i + 1;
    for (i = M, j = -1; i > 1; i--)
    {
        /* i表示圈中人个数，初始为M个，剩1个人时结束循环；j表示当前报数人的位置 */
        for (k = 1; k <= N; k++) /* 1至N报数 */
        {
            j++;
            while (out[j] == 1 || j >= M)
            {
                j++;
                if (j >= M) /* 最后一个人报数后第一个人接着报，形成一个圈 */
                    j = 0;
            }
        }
        out[j] = 1;
        b[M - i] = a[j]; /* 将报数为N的人的编号存入数组b */
    }
    for (i = 0; i < M - 1; i++) /* 按次序输出出圈人的编号 */
        printf("%6d", b[i]);
    for (i = 0; i < M - 1; i++)
    {
        if (out[i] == 0)
            printf("%6d\n", a[i]); /* 输出圈中最后一个人的编号 */
    }
    return 0;
}
