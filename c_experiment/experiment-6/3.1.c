#include "stdio.h"
char *strcpy(char *,char *);
void main(void)
{
    char a[20],b[60]="there is a boat on the lake.";
    printf("%s\n",strcpy(a,b));

}
char *strcpy(char *s,char *t)
{
    // 开始时s指向空字符串
    char *tmp = s;
    while(*tmp++=*t++)
    ;
    // 结束时s指向字符串末尾‘\0’
    *tmp = '\0';
    return (s);
}
