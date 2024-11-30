// #include <stdio.h>
// int main()
// {
//     int i, x, k;
//     printf("本程序判断合数，请输入大于1的整数，以Ctrl+Z结束\n");
//     while (scanf("%d", &x) != EOF)
//     {
//         int flag = 0;
//         for (i = 2, k = x >> 1; i <= k; i++)
//             if (x % i == 0)
//             {
//                 flag = 1;
//                 break;
//             }
//         if (flag == 1)
//             printf("%d是合数", x);
//         else
//             printf("%d不是合数", x);
//     }
//     return 0;
// }

#include <stdio.h>
int main()
{
    int i, x, k, flag = 0;
    printf("本程序判断合数，请输入大于1的整数，以Ctrl+Z结束\n");
    while (scanf("%d", &x) != EOF)
    {
        flag = 0;
        for (i = 2, k = x >> 1; i <= k; i++)
            if (!(x % i))
            {
                flag = 1;
                break;
            }
        if (flag == 1)
            printf("%d是合数", x);
        else
            printf("%d不是合数", x);
    }
    return 0;
}
