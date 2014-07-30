#include<stdio.h>
#include<stdlib.h>

void print_nums(char* nums, int n, int pos)
{
    if (pos == n-1) {
        for (int i = 0; i <= 9; i++) {
            nums[pos] = i + '0';
            printf("%s\n", nums);
        }
    } else {
        for (int i = 0; i <= 9; i++) {
            nums[pos] = i + '0';
            print_nums(nums, n, pos+1);
        }
    }
}

void print_n_digits_nums(int n)
{
    char* nums = (char*)malloc((n+1)*sizeof(char));
    nums[n] = '\0';
    print_nums(nums, n, 0);
}

int main(void)
{
    int n = 3;
    print_n_digits_nums(n);
}
