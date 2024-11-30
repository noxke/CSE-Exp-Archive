#include <stdio.h>
#define MAX_N 10000

int isPerfectNum(int n); // 判断数是否为完美数

int main()
{
    for (int n = 1; n < MAX_N; n++)
    {
        if (isPerfectNum(n))
        {
            printf("%d=1", n);
            for (int i = 2; i <= n / 2; i++)  // 查找因数，按格式输出
            {
                if (n % i == 0)
                {
                    printf("+%d", i);
                }
            }
            printf("\n");
        }
    }
    return 0;
}

int isPerfectNum(int n)
{
    int sum = 0;
    for (int i = 1; i <= n / 2; i++)
    {
        if (n % i == 0)
        {
            sum += i;
        }
    }
    if (sum == n)
    {
        return 1;
    }
    return 0;
}