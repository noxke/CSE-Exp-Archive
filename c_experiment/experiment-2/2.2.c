#include <stdio.h>

int main()
{
    int x, m, n;
    scanf("%x %d %d", &x, &m, &n);
    if (m + n > 16)
    {
        printf("error");
        return 0;
    }
    else
    {
        int newint = ((x >> m) << (16 - n)) & 0xffff;
        printf("%x", newint);
    }
}