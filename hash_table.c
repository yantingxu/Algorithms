#include<stdio.h>
#include<stdlib.h>

// Direct-address Table
// when U is small {0, ..., m-1}
// O(1) for worst case
#define SIZE 100
static void* direct_table[SIZE];

void* direct_search(int key)
{
    if (key < 0 || key >= SIZE)
        return NULL;
    return direct_table[key];
}

void direct_insert(int key, void* value)
{
    if (key < 0 || key >= SIZE)
        return;
    direct_table[key] = value;
}

void* direct_delete(int key)
{
    if (key < 0 || key >= SIZE)
        return NULL;
    void* r = direct_table[key];
    direct_table[key] = NULL;
    return r;
}

// Hash Tables
// when |K| << |U|, it saves a lot of memory
// O(1) for average case
// hash function h: U -> {0, ..., m-1};
// simple uniform hashing: each position has equal prob
// collision: chaining or open addressing
// n elements and m slots => load factor \alpha = n/m

#define M1 30
int division_hash_function(int key)
{
    return key % M1;
}

#include<math.h>
#define M2 64
int multiplication_hash_function(int key)
{
    static float A = 0.618; // (sqrt(5)-1)/2;
    return floor((key-key*A)*M2);
}

struct HashNode {
    int key;
    struct HashNode* next;
};
struct HashNode** head = NULL;

void init_chain_hash_table()
{
    head = (struct HashNode**)calloc(M2, sizeof(struct HashNode*));
    for (int i = 0; i < M2; i++) {
        head[i] = NULL;
    }
}

void free_chain_hash_table()
{
    if (head == NULL)
        return;
    for (int i = 0; i < M2; i++) {
        if (head[i] != NULL) {
            struct HashNode *p = head[i];
            struct HashNode *next;
            while (p != NULL) {
                next = p->next;
                free(p);
                p = next;
            }
            head[i] = NULL;
        }
    }
    free(head);
}

struct HashNode* chain_hash_insert(int key, int (*hash_func)(int))
{
    int slot = (*hash_func)(key);
    struct HashNode *p = (struct HashNode*)malloc(sizeof(struct HashNode));
    p->key = key;
    p->next = NULL;

    if (head[slot] == NULL)
        head[slot] = p;
    else {
        struct HashNode* next = head[slot]->next;
        head[slot] = p;
        p->next = next;
    }
    return p;
}

struct HashNode* chain_hash_search(int key, int (*hash_func)(int))
{
    int slot = (*hash_func)(key);
    struct HashNode* p = head[slot];
    while (p != NULL && p->key != key) {
        p = p->next;
    }
    return p;
}

struct HashNode* chain_hash_delete(int key, int (*hash_func)(int))
{
    int slot = (*hash_func)(key);
    struct HashNode *p = head[slot];
    if (p == NULL)
        return NULL;

    while (p->next != NULL && p->next->key != key)
        p = p->next;
    if (p->next == NULL)
        return NULL;

    struct HashNode *current = p->next;
    p->next = current->next;
    return current;
}

// open addressing
// hash function h: U * probe_idx(0, ..., m-1) -> position(0, ..., m-1); that is a permutation of m elements
// uniform hashing: each permutation has equal prob
// when keys must be deleted, chaining is more appropriate; open addressing produces DELETED which may reduce the performance

#define NIL -1
#define DELETE -2
static int open_table[M2];

int linear_probing(int key, int step)
{
    // primary clustering
    // n sequences
    return (multiplication_hash_function(key)+step)%M2;
}

int quadratic_probing(int key, int step)
{
    // secondary clustering
    // n sequences
    static int c1 = 2, c2 = 3;
    return (multiplication_hash_function(key)+c1*step+c2*step*step)%M2;
}

int double_hashing(int key, int step)
{
    // n^2 sequences
    // h1: k mod m; h2: 1 + (k mod m-1)
    int h1 = key % M2;
    int h2 = 1 + (key % (M2-1));
    return (h1 + step*h2)%M2;
}

int open_insert(int key, int (*open_hash_func)(int, int))
{
    int slot = -1;
    for (int i = 0; i < M2; i++) {
        int s = (*open_hash_func)(key, i);
        if (open_table[s] == NIL || open_table[s] == DELETE) {
            open_table[s] = key;
            slot = s;
            break;
        }
    }
    return slot;
}

int open_search(int key, int (*open_hash_func)(int, int))
{
    int slot = NIL;
    for (int i = 0; i < M2; i++) {
        int s = (*open_hash_func)(key, i);
        if (open_table[s] == key) {
            slot = s;
            break;
        } else if (open_table[s] == NIL) {
            break;
        }
    }
    return slot;
}

int open_delete(int key, int (*open_hash_func)(int, int))
{
    for (int i = 0; i < M2; i++) {
        int s = (*open_hash_func)(key, i);
        if (open_table[s] == key) {
            open_table[s] = DELETE;
        }
    }
}

int main(void)
{
    return 0;
}

