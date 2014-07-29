#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void counting_sort(int *nums, int n, int k)
{
    // O(n+k)
    int *counts = (int*)calloc(k, sizeof(int));
    for (int i = 0; i < k; i++) {
        counts[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        counts[nums[i]]++;
    }
    for (int i = 1; i < k; i++) {
        counts[i] += counts[i-1];
    }
    int *aux = (int*)calloc(n, sizeof(int));
    for (int i = n-1; i >= 0; i--) {
        int idx = counts[nums[i]]-1;
        aux[idx] = nums[i];
        counts[nums[i]]--;
    }
    memcpy(nums, aux, n*sizeof(int));
    free(aux);
    free(counts);
}

void radix_sort(int *nums, int n)
{
    // start with least significat digit
    // for i = 1 to d
    //      radix_sort on i
}

#define ARRAY_LEN 7
#define BIN_NUM 10

int main(void)
{
    int nums[ARRAY_LEN] = {3, 1, 6, 3, 5, 6, 7};
    counting_sort(nums, ARRAY_LEN, BIN_NUM);
    for (int i = 0; i < ARRAY_LEN; i++) {
        printf("%d\n", nums[i]);
    }
}


