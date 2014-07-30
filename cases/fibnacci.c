#include<stdio.h>

int fibnacci(int n)
{
    if (n == 1)
        return 0;
    if (n == 2)
        return 1;
    int prev = 0;
    int current = 1;
    for (int i = 3; i <= n; i++) {
        int tmp = current;
        current += prev;
        prev = tmp;
    }
    return current;
}

int main(void)
{
    printf("%d\n", fibnacci(1));
    printf("%d\n", fibnacci(2));
    printf("%d\n", fibnacci(3));
    printf("%d\n", fibnacci(4));
    printf("%d\n", fibnacci(5));
    printf("%d\n", fibnacci(6));
    printf("%d\n", fibnacci(7));
    printf("%d\n", fibnacci(8));
}
