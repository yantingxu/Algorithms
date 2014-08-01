#include<stdio.h>
#include<stdbool.h>

#define STACK_SIZE 30
static int stack[STACK_SIZE];
static int top = 0;

bool is_stack_emtpy()
{
    return top == 0;
}

bool is_stack_full()
{
    return top == STACK_SIZE;
}

void push(int value)
{
    if (is_stack_full())
        return;
    stack[top++] = value;
}

int pop()
{
    if (is_stack_emtpy())
        return -1;
    return stack[--top];
}

#define QUEUE_SIZE 30
static int queue[QUEUE_SIZE];
static int head = 0, tail = 0;

bool is_queue_empty()
{
    return head == tail;
}

bool is_queue_full()
{
    return (tail+1)%QUEUE_SIZE == head;
}

void enqueue(int value)
{
    if (is_queue_full()) {
        return;
    }
    queue[tail] = value;
    tail = (tail+1)%QUEUE_SIZE;
}

int dequeue()
{
    if (is_queue_empty())
        return -1;
    int val = queue[head];
    head = (head+1)%QUEUE_SIZE;
    return val;
}

#include<stdlib.h>

struct ListNode {
    int key;
    struct ListNode* prev;
    struct ListNode* next;
};

static struct ListNode* list_head = NULL;

struct ListNode* list_search(int key)
{
    struct ListNode* p = list_head;
    while (p != NULL && p->key != key)
        p = p->next;
    return p;
}

struct ListNode* list_insert(int key)
{
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->key = key;
    node->prev = node->next = NULL;

    if (list_head == NULL) {
        list_head = node;
    } else {
        struct ListNode* next_node = list_head->next;
        list_head = node;
        node->next = next_node;
        if (next_node != NULL) {
            next_node->prev = node;
        }
    }
    return node;
}

struct ListNode* list_delete(int key)
{
    struct ListNode* p = list_search(key);
    if (p == NULL)
        return NULL;

    struct ListNode* prev_node = p->prev;
    struct ListNode* next_node = p->next;

    if (prev_node != NULL)
        prev_node->next = next_node;
    else
        list_head = next_node;
    if (next_node != NULL)
        next_node->prev = prev_node;
    return p;
}


struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
};

static struct TreeNode* root = NULL;

// Unbounded branching: left-child, right-sibling representation



