#include <stdio.h>

int main()
{
    char isPnum[1000] = {0};    // 素数表，1表示是质数，0表示是不是质数
    for (int i = 0; i < 1000; i++) isPnum[i] = 1;
    isPnum[1] = 0;
    int i;
    for (i = 1; i <= 999; i++)  // 质数筛
    {
        if (isPnum[i] == 1)
        {
            int j;
            for (j = 2; j * i <= 999; j++)
            {
                isPnum[j * i] = 0;
            }
        }
    }
    for (i = 100; i <= 999; i++)
    {
        int k = i;
        int flag = 1;
        while (k > 0)
        {
            if (isPnum[k] == 1 || k == 1)
            {
                flag = 0;
                break;
            }
            k = k / 10;
        }
        if (flag == 1)
        {
            printf("%d ", i);
        }
    }
    return 0;
}