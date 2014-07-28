#include<stdio.h>

#define N 4
#define M 4

int find_in_matrix(int matrix[][M], int element, int* i, int* j)
{
    if (matrix == NULL || *matrix == NULL) {
        return 0;
    }
    int row = 0;
    int col = M-1;
    while (1) {
        // from right to left
        while (col >= 0 && matrix[row][col] > element) {
            col--;
        }
        if (col < 0) {
            return 0;
        } else if (matrix[row][col] == element) {
            *i = row;
            *j = col;
            return 1;
        }
        // from top to down
        while (row <= N-1 && matrix[row][col] < element) {
            row++;
        }
        if (row == N) {
            return 0;
        } else if (matrix[row][col] == element) {
            *i = row;
            *j = col;
            return 1;
        }
    }
}

int main(void)
{
    int matrix[N][M] = {
        {1,2,8,9},
        {2,4,9,12},
        {4,7,10,13},
        {6,8,11,15},
    };
    int i, j;
    int status;
    int test[7] = {1, 15, 7, 9, 6, 3, 100};
    for (int k = 0; k < 7; k++) {
        status = find_in_matrix(matrix, test[k], &i, &j);
        printf("Test %d: %d (%d, %d)\n", test[k], status, i, j);
    }
    return 1;
}

