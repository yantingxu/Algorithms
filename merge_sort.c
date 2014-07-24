#include<stdio.h>
#include<stdlib.h>

void merge_sort(int* nums, int left, int right)
{
    void merge_result(int*, int, int, int);
    if (left >= right) {
        return;
    }
    int n = right-left+1;
    int mid = (right+left)/2;
    merge_sort(nums, left, mid);
    merge_sort(nums, mid+1, right);
    merge_result(nums, n, left, mid+1);
}

void merge_result(int* nums, int n, int start_i, int start_j)
{
    int *aux = (int*)calloc(n, sizeof(int));
    int end_i = start_j-1;
    int end_j = start_i+n-1;
    for (int i = start_i, j = start_j, k = 0; k < n; k++) {
        if (i <= end_i && j <= end_j) {
            if (nums[i] <= nums[j]) {
                aux[k] = nums[i++];
            } else {
                aux[k] = nums[j++];
            }
        } else {
            if (i <= end_i) {
                aux[k] = nums[i++];
            } else {
                aux[k] = nums[j++];
            }
        }
    }
    for (int k = 0, i = start_i; k < n; k++, i++) {
        nums[i] = aux[k];
    }
    free(aux);
}

#define ARRAY_LEN 7

int main(void)
{
    int nums[ARRAY_LEN] = {3, 1, 6, 3, 45, 6, 7};
    merge_sort(nums, 0, ARRAY_LEN-1);
    for (int i = 0; i < ARRAY_LEN; i++) {
        printf("%d\n", nums[i]);
    }
}



