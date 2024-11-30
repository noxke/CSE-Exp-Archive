#include <stdio.h>

int buy(int tickets[20][5], int k); // 买k张票

int main()
{
    int tickets[20][5] = {0}; // 车票是否售出
    int n, k;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &k);
        buy(tickets, k);
    }
    return 0;
}

int buy(int tickets[20][5], int k)
{
    int i, j, l;
    int res = 0; // 剩余票数
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (tickets[i][j] == 0)
            {
                res++;
            }
        }
    }
    if (res < k) // 剩余票数不足，购票失败
    {
        return 0;
    }
    int flag = 0; // 当前位置能否满足k张票
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (tickets[i][j] == 0)
            {
                flag = 1; // 假设当前位置满足要求
                for (l = j; (l - j) < k; l++)
                {
                    if ((l >= 5) || tickets[i][l] == 1)
                    {
                        flag = 0; // 已售出，不满足
                        break;
                    }
                }
                if (flag == 1) // 满足要求售出
                {
                    for (l = j; (l - j) < k; l++)
                    {
                        tickets[i][l] = 1;
                        printf("%d%c", i + 1, l == 4 ? 'F' : 'A' + l);
                        if ((l - j) < k - 1)
                        {
                            printf(" ");
                        }
                    }
                    printf("\n");
                    return 1;
                }
            }
        }
    }
    if (flag == 0) // 无连续座位
    {
        l = 0;
        for (i = 0; i < 20; i++)
        {
            for (j = 0; j < 5; j++)
            {
                if (tickets[i][j] == 0)
                {
                    tickets[i][j] = 1;
                    l++;
                    printf("%d%c", i + 1, j == 4 ? 'F' : 'A' + j);
                    if (l == k)
                    {
                        printf("\n");
                        return 1;
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
        }
    }
    return 0;
}