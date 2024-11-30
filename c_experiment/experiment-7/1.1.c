# include <stdio.h>

char u[]="UVWXYZ";
char v[]="xyz";
struct T{
	int x;
	char c;
	char *t;
}a[]={{11,'A',u},{100, 'B',v}},*p=a;

int main()
{
    // printf("%d", (++p)->x);
    // p++;
    // printf("%c", p->c);
    // printf("%c",*p++->t);
    // printf("%c",*p->t);
    // printf("%s",*(++p)->t);
    // printf("%c",*++p->t);
    printf("%c",++*p->t);
    return 0;
}