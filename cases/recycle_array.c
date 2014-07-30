#include<stdio.h>

int search_min(int *nums, int n)
{
    int linear_min(int*, int, int);
    int i = 0;      // always in the left part
    int j = n-1;    // always in the right part
    while (j-i > 1) {
        int mid = (j+i)/2;
        if (nums[mid] > nums[i]) {
            i = mid;
        } else if (nums[mid] < nums[j]){
            j = mid;
        } else {
            return linear_min(nums, i, j);
        }
    }
    return nums[j];
}

int linear_min(int* nums, int i, int j)
{
    int min_value = nums[i];
    int min_idx = i;
    for (int idx = i+1; idx <= j; idx++) {
        if (nums[idx] < min_value) {
            min_value = nums[idx];
            min_idx = idx;
        }
    }
    return min_value;
}

int main(void)
{
    int dup_nums[] = {1, 0, 1, 1, 1};
    printf("%d\n", search_min(dup_nums, 5));
    int nums[] = {3, 4, 5, 1, 2};
    printf("%d\n", search_min(nums, 5));
}
