#include<stdio.h>

int min(int* nums, int n)
{
    if (nums == NULL || n <= 0) {
        return -1;
    }
    if (n == 1)
        return nums[0];
    else {
        int min_value = nums[0];
        for (int i = 2; i < n; i++) {
            if (nums[i] < min_value) {
                min_value = nums[i];
            }
        }
        return min_value;
    }
}

void min_max(int *nums, int n, int *min, int *max)
{
    if (nums == NULL || n <= 0) {
        return;
    }
    if (n == 1) {
        *min = *max = nums[0];
        return;
    } else {
        // 3 comps per 2 elements
        int start;
        if (n % 2 == 1) {
            *min = *max = nums[0];
            start = 1;
        } else {
            *min = (nums[0] < nums[1]) ? nums[0] : nums[1];
            *max = (nums[0] < nums[1]) ? nums[1] : nums[0];
            start = 2;
        }
        for (int i = start, j = start + 1; j < n; i++, j++) {
            if (nums[i] > nums[j]) {
                *min = (nums[j] < *min) ? nums[j] : *min;
                *max = (nums[i] > *max) ? nums[i] : *max;
            } else {
                *min = (nums[i] < *min) ? nums[i] : *min;
                *max = (nums[j] > *max) ? nums[j] : *max;
            }
        }
    }
}

int main(void)
{
    int nums[] = {3, 5, 2, 1, 5, 7, 8, 0};
    int min_value, max_value;
    printf("Min: %d\n", min(nums, 8));

    min_max(nums, 8, &min_value, &max_value);
    printf("Min: %d; Max: %d\n", min_value, max_value);
}



