#include <stdio.h>

int main()
{
    unsigned int ip;
    while (scanf("%u", &ip) != EOF)
    {
        int ip1 = ip >> 24;
        int ip2 = (ip >> 16) & 0xff;
        int ip3 = (ip >> 8) & 0xff;
        int ip4 = ip & 0xff;
        printf("%d.%d.%d.%d\n", ip1, ip2, ip3, ip4);
    }
    return 0;
}