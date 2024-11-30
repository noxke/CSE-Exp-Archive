#include <stdio.h>

int feibo4(int n);

int main()
{
    int n, result;
    scanf("%d", &n);
    result = feibo4(n);
    printf("%d\n", result);
    return 0;
}
