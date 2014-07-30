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

struct ListNode* merge_sorted_list_recursively(struct ListNode* head1, struct ListNode* head2)
{
    if (head1 == NULL && head2 == NULL)
        return NULL;
    if (head1 == NULL)
        return head2;
    if (head2 == NULL)
        return head1;

    struct ListNode* head = NULL;
    if (head1->value < head2->value) {
        head = head1;
        head->next = merge_sorted_list_recursively(head1->next, head2);
    } else {
        head = head2;
        head->next = merge_sorted_list_recursively(head2->next, head1);
    }
    return head;
}

struct ListNode* merge_sorted_list_iteratively(struct ListNode* head1, struct ListNode* head2)
{
    if (head1 == NULL && head2 == NULL)
        return NULL;
    if (head1 == NULL)
        return head2;
    if (head2 == NULL)
        return head1;

    struct ListNode* combined_head = NULL;
    struct ListNode* combined_current = NULL;
    while (!(head1 == NULL && head2 == NULL)) {
        if (head1 == NULL) {
            combined_current->next = head2;
            head2 = NULL;
        } else if (head2 == NULL) {
            combined_current->next = head1;
            head1 = NULL;
        } else {
            if (head2->value < head1->value) {
                if (combined_head == NULL) {
                    combined_head = combined_current = head2;
                } else {
                    combined_current->next = head2;
                    combined_current = combined_current->next;
                }
                head2 = head2->next;
            } else {
                if (combined_head == NULL) {
                    combined_head = combined_current = head1;
                } else {
                    combined_current->next = head1;
                    combined_current = combined_current->next;
                }
                head1 = head1->next;
            }
        }
    }
    return combined_head;
}

int main(void)
{
    int nums1[] = {1, 3, 5, 7};
    struct ListNode* head1 = make_sample_list(nums1, 4);
    print_list(head1);
    int nums2[] = {2, 4, 6, 8};
    struct ListNode* head2 = make_sample_list(nums2, 4);
    print_list(head2);
    struct ListNode* head = merge_sorted_list_recursively(head1, head2);
    print_list(head);
}



