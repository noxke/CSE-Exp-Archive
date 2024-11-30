#include <stdio.h>
int main()
{
    int i, x, k;
    printf("本程序判断合数，请输入大于1的整数，以Ctrl+Z结束\n");
    while (scanf("%d", &x) != EOF)
    {
        int flag = 0;
        i = 2;
        k = x >> 1;
        do
        {
            if (x % i == 0)
            {
                flag = 1;
            }
            i++;
        } while (i <= k);
        if (flag == 1)
            printf("%d是合数", x);
        else
            printf("%d不是合数", x);
    }
    return 0;
}
