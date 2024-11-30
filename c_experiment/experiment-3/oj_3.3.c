#include <stdio.h>

int main()
{
    int i;
    for (i = 100; i <= 999; i++)
    {
        if (i * i % 1000 == i)
        {
            printf("%d\n", i);
        }
    }
    return 0;
}