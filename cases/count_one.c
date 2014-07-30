#include<stdio.h>

int count_one(int n)
{
    int count = 0;
    while (n) {
        count++;
        n = n&(n-1);
    }
    return count;
}

int main(void)
{
    int nums[] = {1, 4, 8, 7, 256, 255};
    for (int i = 0; i < 6; i++) {
        printf("Num: %d; Count: %d\n", nums[i], count_one(nums[i]));
    }
}

