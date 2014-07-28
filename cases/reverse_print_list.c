#include<stdio.h>
#include<stdlib.h>

#define CAPACITY 20

struct ListNode {
    int value;
    struct ListNode* next;
};

int stack[CAPACITY];
int top = 0;

void reverse_print_list(struct ListNode* head)
{
    if (head == NULL) {
        return;
    }
    struct ListNode* p = head;
    while (p != NULL) {
        stack[top++] = p->value;
        p = p->next;
    }
    while (top > 0) {
        printf("%d\n", stack[--top]);
    }
}

struct ListNode* make_sample_list(int* nums, int n)
{
    struct ListNode* prev = NULL;
    struct ListNode* head = NULL;
    for (int i = 0; i < n; i++) {
        struct ListNode* current = (struct ListNode*)malloc(sizeof(struct ListNode));
        current->value = nums[i];
        current->next = NULL;
        if (prev != NULL) {
            prev->next = current;
            prev = current;
        } else {
            head = current;
            prev = current;
        }
    }
    return head;
}

int main(void)
{
    int nums[] = {1, 2, 3, 4, 5, 6};
    struct ListNode* head = make_sample_list(nums, 6);
    reverse_print_list(head);
}


