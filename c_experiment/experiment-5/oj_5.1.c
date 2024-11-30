#include <stdio.h>

int main()
{
    int d;
    char bin[32];
    scanf("%d", &d);
    for (int i = 0; i < 32; i++)    // 从低位到高位保存
    {
        bin[i] = (d >> i & 1) + '0';
    }
    for (int i = 0; i < 32; i++) printf("%c", bin[31 - i]);
    return 0;
}