#include <stdio.h>
double mulx(double x, int n);
double sum(double x, int n)
{
    int i;
    int fac[n + 1]; // 使用数组储存阶乘运算的结果
    fac[0] = 1;
    for (i = 1; i <= n; i++)
    {
        fac[i] = i * fac[i - 1];
    }
    double z = 1.0;
    for (i = 1; i <= n; i++)
    {
        z = z + mulx(x, i) / fac[i];
    }
    return z;
}

double mulx(double x, int n)
{
    int i;
    double z = 1.0;
    for (i = 0; i < n; i++)
    {
        z = z * x;
    }
    return z;
}
int main()
{
    double x;
    int n;
    printf("Input x and n:");
    scanf("%lf%d", &x, &n);
    printf("The result is %lf:", sum(x, n));
    return 0;
}
