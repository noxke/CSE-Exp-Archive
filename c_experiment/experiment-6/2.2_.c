#include <stdio.h>
#include <string.h>
int main(void)
{
    char *(*p[])(char *, const char *) = {NULL, strcpy, strcat, strtok};
    char a[80], b[80], *result;
    int choice;
    while (1)
    {
        do
        {
            printf("\t\t1 copy string.\n");
            printf("\t\t2 connect string.\n");
            printf("\t\t3 parse string.\n");
            printf("\t\t4 exit.\n");
            printf("\t\tinput a number (1-4) please.\n");
            scanf("%d", &choice);
        } while (choice < 1 || choice > 4);
        if (choice == 4)
            goto down;
        getchar();
        printf("input the first string please!\n");
        fgets(a, 80, stdin);
        a[strchr(a, '\n') - a] = '\0';  // 去除末尾空格
        printf("input the second string please!\n");
        fgets(b, 80, stdin);
        b[strchr(b, '\n') - b] = '\0';
        result = (*p[choice])(a, b);
        printf("the result is %s\n", result);
    }
down:
    return 0;
}
