#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    FILE *fp;
    char word[20];  // 用于读取单词
    char ori[20];   // 需要替换的原单词
    char dst[20];   // 替换后的目标单词
    char text[1000] = "";   // 临时储存文章
    scanf("%s %s", ori, dst);
    int i = 0;
    int cnt = 0;
    char ch;
    fp = fopen("EXP/exp801/source.txt", "r");
    if (fp == NULL)
    {
        printf("wrong");
        return -1;
    }
    // fp = fopen("source.txt", "r");
    while ((ch = fgetc(fp)) != EOF)
    {
        if (!isalnum(ch))  // 一个单词结束
        {
            word[i] = '\0';
            if (strcmp(ori, word) == 0)
            {
                cnt++;
                strcpy(text+strlen(text), dst);
            }
            else
            {
                strcpy(text+strlen(text), word);
            }
            text[strlen(text)] = ch;
            i = 0;
        }
        else
        {
            word[i] = ch;
            i++;
        }
    }
    fclose(fp);
    // fp = fopen("EXP/exp801/source.txt", "w");
    // fp = fopen("source.txt", "w");  // 重写文件
    printf("%d\n", cnt);
    i = 0;
    while (text[i++] != '\0')
    {
        putchar(text[i - 1]);
        // fputc(text[i - 1], fp);
    }
    // fclose(fp);
    return 0;
}