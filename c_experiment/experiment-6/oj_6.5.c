#include <stdio.h>
#include <malloc.h>

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    int *matrix = malloc(sizeof(int) * m * n);
    int i, j;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", (matrix + i * n + j));
        }
    }
    i = 0, j = 0;
    printf("%d", *(matrix + i * n + j));
    while (i != m - 1 || j != n - 1)
    {
        if (i == 0 && j != n - 1 && n != 2)   // 先右再左下
        {
            if (j + 1 < n)
            {
                j++;
                printf(" %d", *(matrix + i * n + j));
            }
            while (j - 1 >= 0 && i + 1 < m)
            {
                j--;
                i++;
                printf(" %d", *(matrix + i * n + j));
            }
        }
        else if (i == m - 1 && (j != 0 || m == 2))  // 先右再右上
        {
            if (j + 1 < n)
            {
                j++;
                printf(" %d", *(matrix + i * n + j));
            }
            while (j + 1 < n && i - 1 >= 0)
            {
                j++;
                i--;
                printf(" %d", *(matrix + i * n + j));
            }
        }
        else if (j == 0 && i != 0 && m != 2)  // 先下再右上
        {
            if (i + 1 < m)
            {
                i++;
                printf(" %d", *(matrix + i * n + j));
            }
            while (j + 1 < n && i - 1 >= 0)
            {
                j++;
                i--;
                printf(" %d", *(matrix + i * n + j));
            }
        }
        else if (j == n - 1 && (i != m - 1 || n == 2))  // 先下再左下
        {
            if (i + 1 < m)
            {
                i++;
                printf(" %d", *(matrix + i * n + j));
            }
            while (j - 1 >= 0 && i + 1 < m)
            {
                j--;
                i++;
                printf(" %d", *(matrix + i * n + j));
            }
        }
    }
}