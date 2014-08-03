#include<stdio.h>
#include<stdlib.h>

struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* p;
};

struct TreeNode* root = NULL;

// the left-subtree nodes <= current node <= the right-subtree nodes
// operation cost: O(h)
// average height for randomly built tree: O(logn)

// inorder tree walk: sorted order
void inorder_tree_walk(struct TreeNode* x)
{
    // visit each node => linear time in node number
    if (x == NULL)
        return;
    if (x->left != NULL)
        inorder_tree_walk(x->left);
    printf("%d\n", x->key);
    if (x->right != NULL)
        inorder_tree_walk(x->right);
}

void preorder_tree_walk(struct TreeNode* x)
{
    if (x == NULL)
        return;
    printf("%d\n", x->key);
    if (x->left != NULL)
        preorder_tree_walk(x->left);
    if (x->right != NULL)
        preorder_tree_walk(x->right);
}

void postorder_tree_walk(struct TreeNode* x)
{
    if (x == NULL)
        return;
    if (x->left != NULL)
        preorder_tree_walk(x->left);
    if (x->right != NULL)
        preorder_tree_walk(x->right);
    printf("%d\n", x->key);
}


struct TreeNode* tree_search(struct TreeNode* x, int key)
{
    if (x == NULL || x->key == key)
        return x;
    if (x->key < key) {
        return tree_search(x->right, key);
    } else {
        return tree_search(x->left, key);
    }
}

struct TreeNode* iterative_tree_search(struct TreeNode* x, int key)
{
    while (x != NULL && x->key != key) {
        if (x->key < key) {
            x = x->right;
        } else {
            x = x->left;
        }
    }
    return x;
}

struct TreeNode* tree_min(struct TreeNode* x)
{
    if (x == NULL)
        return NULL;
    while (x->left != NULL)
        x = x->left;
    return x;
}

struct TreeNode* tree_max(struct TreeNode* x)
{
    if (x == NULL)
        return NULL;
    while (x->right != NULL)
        x = x->right;
    return x;
}

struct TreeNode* tree_successor(struct TreeNode* x)
{
    if (x == NULL)
        return NULL;
    if (x->right != NULL)
        return tree_min(x->right);

    struct TreeNode* y = x->p;
    while (y != NULL && y->right == x) {
        x = y;
        y = y->p;
    }
    return y;
}

struct TreeNode* tree_predecessor(struct TreeNode* x)
{
    if (x == NULL)
        return NULL;
    if (x->left != NULL)
        return tree_max(x->left);

    struct TreeNode* y = x->p;
    while (y != NULL && x == y->left) {
        x = y;
        y = y->p;
    }
    return y;
}

struct TreeNode* tree_insert(int key)
{
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->key = key;
    node->left = node->right = node->p = NULL;

    struct TreeNode* y = NULL;
    struct TreeNode* x = root;
    while (x != NULL) {
        if (key < x->key) {
            y = x;
            x = x->left;
        } else {
            y = x;
            x = x->right;
        }
    }
    if (y == NULL) {
        root = node;
    } else {
        if (key < y->key) {
            y->left = node;
            x->p = y;
        } else {
            y->right = node;
            x->p = y;
        }
    }
    return node;
}

struct TreeNode* tree_delete(struct TreeNode* x)
{
    if (x == NULL)
        return NULL;

    // 实际被删除的Node及case
    struct TreeNode *y;     // the actual node to be deleted
    if (x->left == NULL && x->right == NULL) {
        y = x;
    } else {
        if (x->left != NULL && x->right != NULL) {
            y = tree_successor(x);
        } else {
            y = x;
        }
    }

    // 从树中切除y
    struct TreeNode *y_child = (y->left != NULL) ? y->left : y->right;      // y的非空子结点(如果有的话)
    struct TreeNode **p_child;                                              // y的父结点中需要修改的变量/root (the pointer points to y)
    if (y->p != NULL) {
        p_child = (y->p->left == y) ? &y->p->left : &y->p->right;
    } else {
        p_child = &root;
    }

    *p_child = y_child;
    if (y_child != NULL) {
        y_child->p = y->p;      // y的p指针正在指向的内容
    }
    y->p = y->left = y->right = NULL;

    // 处理case 3: x有两个children
    if (y != x) {
        x->key = y->key;
    }
    return y;
}


int main(void)
{
    return 0;
}


