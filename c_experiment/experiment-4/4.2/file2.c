#include "file.h"

extern int x,y;             /* 外部变量的定义性说明 */
extern char ch;             /* 外部变量的定义性说明 */

void func1(void)
{
        x++;
        y++;
        ch++;
        printf("in file2 x=%d,y=%d,ch is %c\n",x,y,ch);
}
