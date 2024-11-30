#include <stdio.h>
#define CHANGE 0
#define STR_LEN 100

int main()
{
    char str[STR_LEN] = {"\0"};
    scanf("%s", str);
    #if CHANGE == 1
        char *ch = str;
        while (*ch != '\0')
        {
            if (*ch >= 'a' && *ch <= 'z')   // 小写转换为大写
            {
                *ch = *ch - 0x20;
            }
            else if (*ch >= 'A' && *ch <= 'Z')  // 大写转换为小写
            {
                *ch = *ch + 0x20;
            }
            ch++;
        }
    #endif
    puts(str);
    return 0;
}