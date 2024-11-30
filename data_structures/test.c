#include <stdio.h>
#include <stdlib.h>

void fuc(int *n)
{
    n = malloc(sizeof(int));
    *n = 5;
}

int main()
{
    int *n;
    fuc(n);
    printf("%d", *n);
    return 0;
}