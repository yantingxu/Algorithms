#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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

bool contain_substructure(struct TreeNode* tree1, struct TreeNode* tree2)
{
    if (tree2 == NULL)
        return true;
    if (tree1 == NULL)
        return false;

    bool contain = false;
    if (tree1->value == tree2->value) {
         contain = contain_substructure(tree1->left, tree2->left) && contain_substructure(tree1->right, tree2->right);
    }
    if (!contain && tree1->left != NULL) {
        contain = contain_substructure(tree1->left, tree2);
    }
    if (!contain && tree1->right != NULL) {
        contain = contain_substructure(tree1->right, tree2);
    }
    return contain;
}

int main(void)
{
    /*
    int inorders[] = {4, 7, 2, 1, 5, 3, 8, 6};
    int preorders[] = {1, 2, 4, 7, 3, 5, 6, 8};
    struct TreeNode* root = rebuilt_tree(preorders, 0, 7, inorders, 0, 7);
    preorder_walk(root);
    printf("\n");
    inorder_walk(root);
    printf("\n");
    */
    int inorders_tree1[] = {9, 8, 4, 2, 7, 18, 17};
    int preorders_tree1[] = {18, 8, 9, 2, 4, 7, 17};
    struct TreeNode* tree1 = rebuilt_tree(preorders_tree1, 0, 6, inorders_tree1, 0, 6);
    preorder_walk(tree1);
    printf("\n");
    inorder_walk(tree1);
    printf("\n");

    int inorders_tree2[] = {9, 8, 2};
    int preorders_tree2[] = {8, 9, 2};
    struct TreeNode* tree2 = rebuilt_tree(preorders_tree2, 0, 2, inorders_tree2, 0, 2);
    preorder_walk(tree2);
    printf("\n");
    inorder_walk(tree2);
    printf("\n");

    printf("Contain: %d\n", contain_substructure(tree1, tree2));
}





