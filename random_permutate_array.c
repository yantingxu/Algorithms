#include<stdio.h>
#include<stdlib.h>

void srand(unsigned int);
int rand(void);
int random_idx(int, int);
void swap(int*, int, int);

void random_in_place(int *nums, int n)
{
    srand(1000);
    int idx;
    for (int i = 0; i < n; i++) {
        idx = random_idx(i, n-1);
        printf("Idx: %d %d\n", i, idx);
        swap(nums, i, idx);
    }
}

int random_idx(int begin, int end)
{
    return rand() % (end-begin+1) + begin;
}

void swap(int *nums, int i, int j)
{
    if (nums[i] == nums[j]) {
        return;
    }
    printf("Before: %d %d\n", nums[i], nums[j]);
    nums[i] = nums[i] ^ nums[j];
    printf("Before1: %d %d\n", nums[i], nums[j]);
    nums[j] = nums[i] ^ nums[j];
    printf("Before2: %d %d\n", nums[i], nums[j]);
    nums[i] = nums[i] ^ nums[j];
    printf("After: %d %d\n", nums[i], nums[j]);
}

#define ARRAY_LEN 5
int main(void)
{
    int nums[ARRAY_LEN] = {3, 1, 7, 10, 8};
    random_in_place(nums, ARRAY_LEN);
    for (int i = 0; i < ARRAY_LEN; i++) {
        printf("%d\n", nums[i]);
    }
}





