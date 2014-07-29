#include<stdio.h>
#include<stdlib.h>

int rand(void);
void srand(unsigned int);

void quick_sort(int *nums, int i, int j)
{
    if (i >= j)
        return;
    int partitions(int*, int , int);
    int q = partitions(nums, i, j);
    quick_sort(nums, i, q-1);
    quick_sort(nums, q+1, j);
}

int select_pivot(int *nums, int i, int j)
{
    int range = j-i+1;
    return rand()%range+i;
}

int partitions(int *nums, int i, int j)
{
    void swap(int*, int, int);
    int pivot = select_pivot(nums, i, j);
    swap(nums, pivot, i);
    int p = i + 1;
    int q = j;
    int split;
    while (1) {
        while (p <= j && nums[p] <= nums[i])
            p++;
        while (q >= i+1 && nums[q] > nums[i])
            q--;
        if (p > j) {
            // boundary condition: all elements are smaller than pivot
            swap(nums, i, j);
            split = j;
            break;
        } else if (q < i+1) {
            // boundary condition: all elements are larger than pivot
            split = i;
            break;
        } else {
            // both smaller and larger exist
            if (p < q) {
                swap(nums, p, q);
            } else {
                swap(nums, i, q);
                split = q;
                break;
            }
        }
    }
    return split;
}

void swap(int *nums, int i, int j)
{
    if (nums[i] == nums[j]) {
        return;
    }
    nums[i] = nums[i] ^ nums[j];
    nums[j] = nums[i] ^ nums[j];
    nums[i] = nums[i] ^ nums[j];
}

#define ARRAY_LEN 7

int main(void)
{
    int nums[ARRAY_LEN] = {3, 1, 6, 3, 45, 6, 7};
    quick_sort(nums, 0, ARRAY_LEN-1);
    for (int i = 0; i < ARRAY_LEN; i++) {
        printf("%d\n", nums[i]);
    }
}

