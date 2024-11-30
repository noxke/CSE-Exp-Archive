#include <stdio.h>
#define byte unsigned char

int main()
{
    int k;
    char d2h[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    byte *ptr = (byte *) &k;
    scanf("%d", &k);
    int i;
    for (i = 3; i >=0; i--)
    {
        byte high = *(ptr + i) >> 4;
        byte low = *(ptr + i) & 0xF;
        printf("%c%c", d2h[high], d2h[low]);
    }
    return 0;
}