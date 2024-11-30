#include <stdio.h>
#define MAX_N 100

void goldbach(int n);

int main()
{
    int n;
    while (scanf("%d", &n) != EOF) goldbach(n);
    return 0;
}

void goldbach(int n)
{
    int isPrime[MAX_N] = {0};   // 素数表
    for (int i = 2; i < MAX_N; i++) isPrime[i] = 1;
    for (int i = 2; i < MAX_N; i++) // 素数筛
    {
        if (isPrime[i] == 1)
        {
            for(int j = 2; i * j < MAX_N; j++)
            {
                isPrime[i * j] = 0;
            }
        }
    }
    int n1, n2;
    for (n1 = 2; n1 <= n / 2; n1++)
    {
        n2 = n - n1;
        if (isPrime[n1] == 1 && isPrime[n2] == 1)   // 如果两个数都为素数则输出并返回
        {
            printf("%d=%d+%d\n", n, n1, n2);
            return;
        }
    }
}