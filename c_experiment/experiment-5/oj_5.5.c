#include <stdio.h>
#include <malloc.h>

void swap(int *list, int m1, int n1, int m2, int n2);   // 交换函数

int main()
{
    int n;
    scanf("%d", &n);
    int *list = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", list + i);
    }
    int m1, n1, m2, n2;
    scanf("%d %d %d %d", &m1, &n1, &m2, &n2);
    swap(list, m1, n1, m2, n2);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", *(list + i));
    }
    return 0;
}

void swap(int *list, int m1, int n1, int m2, int n2)    // 将交换部分分为3段，先整体逆序，再分段逆序
{
    int i, l, r;
    l = m1, r = n2;
    for (i = 0; i < (r - l + 1) / 2; i++) // 第一次逆序整个交换的三部分
    {
        *(list + l + i) ^= *(list + r - i); // 使用异或交换两个数 a = a ^ b
        *(list + r - i) ^= *(list + l + i); // b = a ^ a
        *(list + l + i) ^= *(list + r - i); // a = a ^ b
    }
    // 重新计算m1,n1,m2,n2
    int a = n1 - m1, b = m2 - n1, c = n2 - m2;
    m1 = m1, n1 = m1 + c, m2 = n1 + b, n2 = n2;
    l = m1, r = n1;
    for (i = 0; i < (r - l + 1) / 2; i++) // 逆序第三部分
    {
        *(list + l + i) ^= *(list + r - i); // 使用异或交换两个数 a = a ^ b
        *(list + r - i) ^= *(list + l + i); // b = a ^ a
        *(list + l + i) ^= *(list + r - i); // a = a ^ b
    }
    l = n1 + 1, r = m2 - 1;
    for (i = 0; i < (r - l + 1) / 2; i++) // 逆序第二部分
    {
        *(list + l + i) ^= *(list + r - i); // 使用异或交换两个数 a = a ^ b
        *(list + r - i) ^= *(list + l + i); // b = a ^ a
        *(list + l + i) ^= *(list + r - i); // a = a ^ b
    }
    l = m2, r = n2;
    for (i = 0; i < (r - l + 1) / 2; i++) // 逆序第一部分
    {
        *(list + l + i) ^= *(list + r - i); // 使用异或交换两个数 a = a ^ b
        *(list + r - i) ^= *(list + l + i); // b = a ^ a
        *(list + l + i) ^= *(list + r - i); // a = a ^ b
    }
}