#include<stdio.h>

void swap(int* i, int* j)
{
    *i = *i ^ *j;
    *j = *i ^ *j;
    *i = *i ^ *j;
}

