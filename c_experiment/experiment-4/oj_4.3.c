#include <stdio.h>
#include <math.h>

int isNarcNum(int n); //判断是否为自幂数

int main()
{
    char narc[9][20] = {"", "独身数", "", "水仙花数", "四叶玫瑰数", "五角星数", "六合数", "北斗星数", "八仙数"};
    int k;
    scanf("%d", &k);
    while (k != 0)
    {
        int count = 0;
        for (int n = pow(10, k - 1); n < pow(10, k); n++)
        {
            if (isNarcNum(n))
                count++;
        }
        printf("%d位的%s共有%d个", k, narc[k], count);
        int w = 0;
        for (int n = pow(10, k - 1); n < pow(10, k); n++)
        {
            if (isNarcNum(n))
            {
                if (w != 0)
                    printf(",");
                w = 1;
                printf("%d", n);
            }
        }
        printf("\n");
        scanf("%d", &k);
    }
    return 0;
}

int isNarcNum(int n)
{
    int s = n;
    int sum = 0;
    int k = 0;
    while (s != 0) // 计算位数
    {
        k++;
        s = s / 10;
    }
    s = n;
    while (s != 0)
    {
        sum += pow(s % 10, k);
        s = s / 10;
    }
    if (sum == n)
    {
        return 1;
    }
    return 0;
}