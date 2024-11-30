#include <stdio.h>
#include <math.h>

#define MacroS(a,b,c) (a+b+c)/2   // 求s的宏
#define MacroArea(s,a,b,c) sqrt(s*(s-a)*(s-b)*(s-c)) // 求area的宏

int main()
{
    float a, b, c, s, area;
    scanf("%f %f %f", &a, &b, &c);
    s = MacroS(a, b, c);
    area = MacroArea(s, a, b, c);
    printf("s=%0.2f\n", s);
    printf("area=%0.2f", area);
    return 0;
}