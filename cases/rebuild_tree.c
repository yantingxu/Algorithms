#include<stdio.h>
#include<stdlib.h>

struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* rebuilt_tree(int* preorder, int pi, int pj, int* inorder, int ii, int ij)
{
    if (pi == pj) {
        struct TreeNode* leaf = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        leaf->value = preorder[pi];
        leaf->left = leaf->right = NULL;
        return leaf;
    } else {
        int root = preorder[pi];
        int inorder_root_idx = ii;
        while (inorder_root_idx <= ij && inorder[inorder_root_idx] != root) {
            inorder_root_idx++;
        }
        if (inorder_root_idx > ij) {
            return NULL;
        }

        struct TreeNode* root_node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        root_node->value = root;
        if (inorder_root_idx == ii) {
            // 只有右子树
            // (pi+1, pj)
            // (ii+1, ij)
            root_node->left = NULL;
            root_node->right = rebuilt_tree(preorder, pi+1, pj, inorder, ii+1, ij);
        } else if (inorder_root_idx == ij) {
            // 只有左子树
            // (pi+1, pj)
            // (ii, ij-1)
            root_node->left = rebuilt_tree(preorder, pi+1, pj, inorder, ii, ij-1);
            root_node->right = NULL;
        } else {
            // 两棵子树都存在, 寻找preorder中的两棵子树的边界
            int preorder_boundary;
            for (preorder_boundary = pi + 1; preorder_boundary <= pj; preorder_boundary++) {
                int current = preorder[preorder_boundary];
                int found = 1;
                for (int k = ii; k < inorder_root_idx; k++) {
                    if (inorder[k] == current) {
                        found = 0;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
            if (preorder_boundary > pj) {
                return NULL;
            }
            preorder_boundary--;

            // (pi+1, preorder_boundary), (preorder_boundary+1, pj)
            // (ii, inorder_root_idx-1), (inorder_root_idx+1, ij)
            root_node->left = rebuilt_tree(preorder, pi+1, preorder_boundary, inorder, ii, inorder_root_idx-1);
            root_node->right = rebuilt_tree(preorder, preorder_boundary+1, pj, inorder, inorder_root_idx+1, ij);
        }
        return root_node;
    }
}

void preorder_walk(struct TreeNode* root)
{
    if (root == NULL) {
        return;
    }
    printf("%d ", root->value);
    if (root->left != NULL) {
        preorder_walk(root->left);
    }
    if (root->right != NULL) {
        preorder_walk(root->right);
    }
}

void inorder_walk(struct TreeNode* root)
{
    if (root == NULL) {
        return;
    }
    if (root->left != NULL) {
        inorder_walk(root->left);
    }
    printf("%d ", root->value);
    if (root->right != NULL) {
        inorder_walk(root->right);
    }
}

int main(void)
{
    int inorders[] = {4, 7, 2, 1, 5, 3, 8, 6};
    int preorders[] = {1, 2, 4, 7, 3, 5, 6, 8};
    struct TreeNode* root = rebuilt_tree(preorders, 0, 7, inorders, 0, 7);
    preorder_walk(root);
    printf("\n");
    inorder_walk(root);
    printf("\n");
}





