#include<stdio.h>

void insertion_sort(int* nums, int n)
{
    void swap(int*, int*);
    int i, j;
    for(i = 1; i < n; i++) {
        int element = nums[i];
        for (j = i-1; j >= 0; j--) {
            if (nums[j] > element) {
                swap(&nums[j], &nums[j+1]);
            } else {
                break;
            }
        }
        nums[j+1] = element;
    }
}

void swap(int* i, int* j)
{
    *i = *i ^ *j;
    *j = *i ^ *j;
    *i = *i ^ *j;
}

int main(void)
{
    int nums[7] = {3, 1, 6, 3, 45, 6, 7};
    insertion_sort(nums, 7);
    for (int i = 0; i < 7; i++) {
        printf("%d\n", nums[i]);
    }
}
