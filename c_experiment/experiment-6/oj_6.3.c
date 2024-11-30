#include <stdio.h>

void replace_blank(char *str);

int main()
{
    int n;
    scanf("%d", &n);
    char strs[n][80];
    int i = 0;
    getchar(); // 取走末尾换行符
    while (i < n)
    {
        fgets(strs[i], 80, stdin);
        i++;
    }
    i = 0;
    while (i < n)
    {
        replace_blank(strs[i]); // 移除多余的空格
        printf("%s%c", strs[i], i == n - 1 ? '\0' : '\n');
        i++;
    }
    return 0;
}

void replace_blank(char *str)
{
    int i = 0, j = 0;
    int flag = 0;       // 记录是否位于字符串开头
    int blank_flag = 0; // 记录是否第一个空格
    while (*(str + i) != '\0')
    {
        if (*(str + i) == '\n')
        {
            *(str + i) = '\0';
        }
        if ((*(str + i) == '\t' || *(str + i) == ' ') && flag == 0)
        {
            j = i;
            while (*(str + j) != '\0')
            {
                *(str + j) = *(str + j + 1);
                j++;
            }
        }
        else if (*(str + i) == ' ' && blank_flag == 0)
        {
            blank_flag = 1;
            i++;
        }
        else if (*(str + i) == ' ' && blank_flag == 1)
        {
            j = i;
            while (*(str + j) != '\0')
            {
                *(str + j) = *(str + j + 1);
                j++;
            }
        }
        else
        {
            flag = 1;
            blank_flag = 0;
            i++;
        }
    }
}