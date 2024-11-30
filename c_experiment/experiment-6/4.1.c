#include <stdio.h>

int main(int args, char **argc)
{
    int i;
    for (i = 1; i < args; i++)
    {
        printf("arg%d: %s\n", i, argc[i]);  // 打印第i个参数
    }
    return 0;
}