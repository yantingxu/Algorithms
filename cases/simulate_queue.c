/*
 * Simulate Queue by Two Stacks
 */
#include<stdio.h>

#define SIZE 100
static int pop_stack[SIZE];
static int pop_top = 0;
static int push_stack[SIZE];
static int push_top = 0;
static int err = 0;

int is_push_stack_full()
{
    return push_top == SIZE;
}

int is_push_stack_empty()
{
    return push_top == 0;
}

int is_pop_stack_full()
{
    return pop_top == SIZE;
}

int is_pop_stack_empty()
{
    return pop_top == 0;
}

void dump_stacks()
{
    if (is_pop_stack_empty()) {
        int element;
        while (!is_push_stack_empty()) {
            element = push_stack[--push_top];
            pop_stack[pop_top++] = element;
        }
    }
}

void push(int key)
{
    if (is_push_stack_full()) {
        if (is_pop_stack_empty()) {
            dump_stacks();
        } else {
            err = 1;
            return;
        }
    }
    push_stack[push_top++] = key;
}

int pop()
{
    if (!is_pop_stack_empty()) {
        return pop_stack[--pop_top];
    } else if (!is_push_stack_empty()) {
        dump_stacks();
        return pop_stack[--pop_top];
    } else {
        err = 1;
        return -1;
    }
}

void print_stack()
{
    if (!is_pop_stack_empty()) {
        int i = pop_top-1;
        while (i >= 0) {
            printf("%d ", pop_stack[i--]);
        }
    }
    printf("|");
    if (!is_push_stack_empty()) {
        int j = 0;
        while (j < push_top) {
            printf("%d ", push_stack[j++]);
        }
    }
    printf("\n");
}

int main(void)
{
    push(1);
    push(2);
    push(3);
    push(4);
    print_stack();
    pop();
    print_stack();
    pop();
    print_stack();
    pop();
    print_stack();
}


