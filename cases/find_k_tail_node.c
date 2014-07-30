#include<stdio.h>
#include<stdlib.h>

struct ListNode {
    int value;
    struct ListNode* next;
};

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

void print_list(struct ListNode* head)
{
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

struct ListNode* find_k_tail_node(struct ListNode* head, unsigned int k)
{
    if (head == NULL)
        return NULL;
    if (k == 0)
        return NULL;

    struct ListNode* slow = head;
    struct ListNode* fast = head;
    for (int i = 0; i < k-1; i++) {
        fast = fast->next;
        if (fast == NULL) {
            return NULL;
        }
    }
    while (fast->next != NULL) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

int main(void)
{
    int nums[] = {1, 2, 3, 4, 5, 6};
    struct ListNode* head = make_sample_list(nums, 6);
    print_list(head);

    struct ListNode* ktail = find_k_tail_node(head, 3);
    printf("%d\n", ktail->value);
    ktail = find_k_tail_node(head, 6);
    printf("%d\n", ktail->value);
    ktail = find_k_tail_node(head, 1);
    printf("%d\n", ktail->value);
}


