#include<stdio.h>

double power(double base, int exponent)
{
    if (base == 0)
        return 0;
    if (base == 1)
        return 1;
    if (exponent == 0)
        return 1;
    else if (exponent == 1)
        return base;
    else if (exponent < 0) {
        base = 1/base;
        exponent = -exponent;
    }
    double result = power(base, exponent >> 1);
    result *= result;
    if (exponent % 2) {
        result *= base;
    }
    return result;
}

int main(void)
{
    double base = 5;
    int exponent = -3;
    printf("%f\n", power(base, exponent));
}
