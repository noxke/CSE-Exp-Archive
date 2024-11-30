#include<stdio.h>
#include <malloc.h>
char *strcopy(char *, const char *);
int main(void)
{
	char *s1 = malloc(sizeof(char)*20);	// 分配内存
    char *s2 = malloc(sizeof(char)*20);
    char *s3 = malloc(sizeof(char)*20);
	printf("Input a string:\n");
	scanf("%s", s2);
	strcopy(s1, s2);
	printf("%s\n", s1);
	printf("Input a string again:\n");
	scanf("%s", s2);
	s3 = strcopy(s1, s2);
	printf("%s\n", s3);
	return 0;
}

/*将字符串s复制给字符串t，并且返回串t的首地址*/
char * strcopy(char *t, const char *s)
{
    char *tmp = t;	// 保护t指针
	while(*tmp++ = *s++);
    *tmp = '\0';	// 字符串末尾置为空字符
	return (t);
}
