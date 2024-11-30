#include <stdio.h>
// #include <assert.h>
#define R

int integer_fraction(float x);

int main(void)
{
    float r, s;
    int s_integer = 0;
    printf("Input a number: ");
    scanf("%f", &r); 
#ifdef R
    s = 3.14159 * r * r;
    printf("Area of round is: %f\n", s);
    s_integer = integer_fraction(s);
    if (s - s_integer >= 0.5)
    {
        s_integer++;
    }
    printf("The integer fraction of area is %d\n", s_integer);
#endif
    return 0;
}

int integer_fraction(float x)
{
    int i = x;
    return i;
}
