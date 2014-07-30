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

void delete_node(struct ListNode** head, struct ListNode* deleted)
{
    // O(1) delete
    if (head == NULL || *head == NULL || deleted == NULL)
        return;
    struct ListNode* next = deleted->next;
    if (next == NULL) {
        if (*head == deleted) {
            free(deleted);
            *head = NULL;
        } else {
            // linear search
            struct ListNode* p = *head;
            while (p->next != deleted) {
                p = p->next;
            }
            p->next = deleted->next;
            free(deleted);
        }
    } else {
        // copy value
        int next_value = next->value;
        deleted->next = next->next;
        deleted->value = next_value;
        free(next);
    }
}

void print_list(struct ListNode* head)
{
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

int main(void)
{
    int nums[] = {1, 2, 3, 4, 5, 6};
    struct ListNode* head = make_sample_list(nums, 6);
    delete_node(&head, head->next->next);
    print_list(head);
    delete_node(&head, head);
    print_list(head);
    struct ListNode* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    delete_node(&head, tail);
    print_list(head);

}



