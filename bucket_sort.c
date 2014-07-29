#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct ListNode {
    int value;
    struct ListNode* next;
};

struct ListNode* make_node(int value)
{
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->value = value;
    node->next = NULL;
    return node;
}

void insert_into_bucket(struct ListNode** buckets, int bucket_idx, int value)
{
    struct ListNode* node = make_node(value);
    if (buckets[bucket_idx] == NULL) {
        buckets[bucket_idx] = node;
    } else {
        struct ListNode* head = buckets[bucket_idx];
        buckets[bucket_idx] = node;
        node->next = head;
    }
}

void sort_list(struct ListNode* head)
{
    if (head == NULL)
        return;
    for (struct ListNode* p = head; p != NULL; p = p->next) {
        struct ListNode* optim = p;
        int min_value = p->value;
        for (struct ListNode* current = p; current != NULL; current = current->next) {
            if (current->value < min_value) {
                min_value = current->value;
                optim = current;
            }
        }
        int tmp = p->value;
        p->value = min_value;
        optim->value = tmp;
    }
}

struct ListNode* concatenate_buckets(struct ListNode **buckets, int n)
{
    struct ListNode *head = NULL, *tail = NULL;
    for (int i = 0; i < n; i++) {
        struct ListNode* bucket_list = buckets[i];
        if (bucket_list == NULL)
            continue;
        if (tail != NULL) {
            tail->next = bucket_list;
            tail = tail->next;
        } else {
            head = tail = bucket_list;
        }
        while (tail->next != NULL) {
            tail = tail->next;
        }
    }
    return head;
}

struct ListNode* bucket_sort(int *nums, int n)
{
    // nums distributed uniformly in [0, 10)
    // nums/10.0 => [0, 1)
    struct ListNode **buckets = (struct ListNode**)calloc(n, sizeof(struct ListNode*));
    for (int i = 0; i < n; i++) {
        buckets[i] = NULL;
    }
    for (int i = 0; i < n; i++) {
        int bucket_idx = (int)(n*nums[i]/10.0);
        insert_into_bucket(buckets, bucket_idx, nums[i]);
    }
    for (int i = 0; i < n; i++) {
        sort_list(buckets[i]);
    }
    struct ListNode* sorted_list = concatenate_buckets(buckets, n);
    return sorted_list;
}

#define ARRAY_LEN 7
#define BIN_NUM 10

int main(void)
{
    int nums[ARRAY_LEN] = {3, 1, 6, 3, 5, 6, 7};
    for (int i = 0; i < ARRAY_LEN; i++) {
        printf("%d\n", nums[i]);
    }
    printf("\n");
    struct ListNode* head = bucket_sort(nums, ARRAY_LEN);
    while (head != NULL) {
        printf("%d\n", head->value);
        head = head->next;
    }
}





