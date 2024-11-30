#include <stdio.h>
#include <string.h>

char *lst_str(char (*strs)[20], int *l);

int main()
{
    char strs[20][20] = {};
    int i = 0;
    while (scanf("%s", strs[i]) != EOF)
    {
        i++;
    }
    int l = i;
    char *lst = lst_str(strs, &l);
    printf("%s %d", lst, l);
    return 0;
}

char *lst_str(char (*strs)[20], int *l)
{
    int max = 0;
    char *lst = strs[0];
    int i;
    for ( i = 0; i < *l; i++)
    {
        if (strlen(strs[i]) > max)
        {
            max = strlen(strs[i]);
            lst = strs[i];
        }
    }
    *l = max;
    return lst;
}