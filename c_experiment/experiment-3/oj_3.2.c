#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int i, j;
    for (i = 0; i <= n; i++)
    {
        int t = n + (n - i) * 2;
        while (t > 0)
        {
            printf(" ");
            t--;
        }
        int k;
        for (j = 0; j <= i; j++)
        {
            if (j == 0)
            {
                k = 1;
            }
            else
            {
                k = k * (i - j + 1) / j;
            }
            printf("%-4d", k);
        }
        printf("\n");
    }
    return 0;
}