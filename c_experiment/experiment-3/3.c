#include <stdio.h>
#define MAX_INT 1e9

float tax_if(int x);    // if实现
float tax_switch(int x); // switch实现

int main()
{
    int x;
    printf("请输入工资金额：");
    scanf("%d", &x);
    printf("应收取税金额度：%.02f\n", tax_if(x));
    printf("应收取税金额度：%.02f\n", tax_switch(x));
}

float tax_if(int x)
{
    float tax = 0;
    if (x >= 5000)
    {
        tax = 1000 * 0.05 + 1000 * 0.1 + 1000 * 0.15 + 1000 * 0.2 + (x - 5000 + 1) * 0.25;
    }
    else if (x >= 4000)
    {
        tax = 1000 * 0.05 + 1000 * 0.1 + 1000 * 0.15 + (x - 4000 + 1) * 0.2;
    }
    else if (x >= 3000)
    {
        tax = 1000 * 0.05 + 1000 * 0.1 + (x - 3000 + 1) * 0.15;
    }
    else if (x >= 2000)
    {
        tax = 1000 * 0.05 + (x - 2000 + 1) * 0.1;
    }
    else if (x >= 1000)
    {
        tax = (x - 1000 + 1) * 0.05;
    }
    else
    {
        tax = 0;
    }
    return tax;
}

float tax_switch(int x)
{
    float tax = 0;
    switch (x / 1000)
    {
    case 0:
        tax = 0;
        break;
    case 1:
        tax = (x - 1000 + 1) * 0.05;
        break;
    case 2:
        tax = 1000 * 0.05 + (x - 2000 + 1) * 0.1;
        break;
    case 3:
        tax = 1000 * 0.05 + 1000 * 0.1 + (x - 3000 + 1) * 0.15;
        break;
    case 4:
        tax = 1000 * 0.05 + 1000 * 0.1 + 1000 * 0.15 + (x - 4000 + 1) * 0.2;
        break;
    default:
        tax = 1000 * 0.05 + 1000 * 0.1 + 1000 * 0.15 + 1000 * 0.2 + (x - 5000 + 1) * 0.25;
        break;
    }
    return tax;
}