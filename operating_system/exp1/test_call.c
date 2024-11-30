#include <stdio.h>
#include <sys/syscall.h>

#define __x64_sys_my_add 548
#define __x64_sys_my_max 549

int main()
{
    int a = 123;
    int b = 98;
    int c = 230;
    int add = syscall(__x64_sys_my_add, a, b);
    int max = syscall(__x64_sys_my_max, a, b, c);
    printf("%d + %d = %d\n", a, b, add);
    printf("max(%d, %d, %d) = %d\n", a, b, c, max);
    return 0;
}