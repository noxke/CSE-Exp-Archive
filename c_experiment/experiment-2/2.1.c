#include <stdio.h>

int main()
{
    char c;
    while ((c = getchar()) != EOF)   // 输入末尾
    {
        if (c >= 'A' && c <= 'Z')
        {
            c = c - 'A' + 'a';
        }
        putchar(c);
    }
}