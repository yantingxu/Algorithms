#include<stdio.h>
#include<stdlib.h>
#include<math.h>        // gcc -lm
#include<string.h>

int rand(void);
void srand(unsigned int);

void swap(int *i, int *j)
{
    int tmp = *i;
    *i = *j;
    *j = tmp;
}

void sort_minibatch(int *nums, int n)
{
    // insertion sort
    for (int i = 1; i < n; i++) {
        int element = nums[i];
        int j = i-1;
        while (j >= 0 && nums[j] > element) {
            nums[j+1] = nums[j];
            j--;
        }
        nums[j+1] = element;
    }
}

int linear_select_pivot(int *nums, int n, int i, int j)
{
    int element_num = (j-i+1);
    if (element_num == 1) {
        return i;
    }

    // allocate memory
    int group_num = ceil(element_num/5.0);
    int **groups = (int**)calloc(group_num, sizeof(int*));
    int *medians = (int*)calloc(group_num, sizeof(int));
    int median_idx = 0;
    for (int gidx = 0; gidx < group_num; gidx++) {
        groups[gidx] = (int*)calloc(5, sizeof(int));
        int len = (gidx == group_num-1) ? element_num-5*gidx : 5;
        memcpy(groups[gidx], &nums[i+5*gidx], len*sizeof(int));
        sort_minibatch(groups[gidx], len);
        medians[median_idx++] = groups[gidx][(int)floor(len/2.0)];
    }
    int select_kth_element(int*, int, int, int, int, int (*)(int*, int, int, int));
    int pivot = select_kth_element(medians, group_num, 0, group_num-1, (int)floor(group_num/2.0), linear_select_pivot);     // median of medians

    // free memory
    free(medians);
    for (int i = 0; i < group_num; i++) {
        free(groups[i]);
    }
    free(groups);

    for (int idx = i; idx <= j; idx++) {
        if (nums[idx] == pivot)
            // printf("Pivot idx: %d\n", idx);
            return idx;
    }
    printf("Error!");
}

int random_select_pivot(int *nums, int n, int i, int j)
{
    return rand()%(j-i+1) + i;
}

int partition(int *nums, int n, int i, int j, int (*select_pivot)(int*, int, int, int))
{
    if (i == j)
        return i;
    int random_idx = (*select_pivot)(nums, n, i, j);
    swap(&nums[random_idx], &nums[i]);
    int a = i;
    for (int b = i+1; b < n; b++) {
        if (nums[b] <= nums[i]) {
            a++;
            swap(&nums[a], &nums[b]);
        }
    }
    swap(&nums[a], &nums[i]);
    return a;
}

int select_kth_element(int *nums, int n, int i, int j, int k, int (*select_pivot)(int*, int, int, int))
{
    if (i == j)
        return nums[i];

    int idx = partition(nums, n, i, j, select_pivot);
    int q = (idx-i+1);
    int result;
    if (q == k) {
        result = nums[idx];
    } else {
        if (q < k) {
            result = select_kth_element(nums, n, idx+1, j, k-q, select_pivot);
        } else {
            result = select_kth_element(nums, n, i, idx-1, k, select_pivot);
        }
    }
    return result;
}

#define LEN 12
int main(void)
{
    int nums[LEN] = {4, 1, 78, 23, 4, 67, 8, 2, 0, 100, 101, 55};
    int k = 6;
    int element;
    // element = select_kth_element(nums, LEN, 0, LEN-1, k, random_select_pivot);
    element = select_kth_element(nums, LEN, 0, LEN-1, k, linear_select_pivot);
    printf("%dth is %d\n", k, element);

    k = 1;
    element = select_kth_element(nums, LEN, 0, LEN-1, k, linear_select_pivot);
    printf("%dth is %d\n", k, element);

    k = 2;
    element = select_kth_element(nums, LEN, 0, LEN-1, k, linear_select_pivot);
    printf("%dth is %d\n", k, element);

    k = 3;
    element = select_kth_element(nums, LEN, 0, LEN-1, k, linear_select_pivot);
    printf("%dth is %d\n", k, element);

    k = 4;
    element = select_kth_element(nums, LEN, 0, LEN-1, k, linear_select_pivot);
    printf("%dth is %d\n", k, element);

    k = LEN;
    element = select_kth_element(nums, LEN, 0, LEN-1, k, linear_select_pivot);
    printf("%dth is %d\n", k, element);
}


