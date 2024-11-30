#include <stdio.h>

int main()
{
    char text[500] = {'0'};
    int i = 0;
    int is_space = 0;
    char ch;
    while ((ch = getchar()) != '!')
    {
        if (is_space == 0 || ch != ' ')
        {
            text[i] = ch;
            i++;
        }
        if (ch == ' ')
        {
            is_space = 1;
        }
        else
        {
            is_space = 0;
        }
    }
    text[i] = ch;
    printf("%s", text);
}