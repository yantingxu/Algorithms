#include<stdio.h>

void swap(int* nums, int i, int j)
{
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
}

void seperate(int *nums, int n)
{
    int i = 0;
    int j = n-1;
    while (i <= n-1 && j >= 0) {
        while (i < j && nums[i] % 2 == 0)
            i++;
        while (i < j && nums[j] % 2 == 1)
            j--;
        if (i < j) {
            swap(nums, i, j);
        } else {
            break;
        }
    }
}

int main(void)
{
    int nums[] = {1, 5, 3, 4, 2};
    seperate(nums, 5);
    for (int i = 0; i < 5; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

