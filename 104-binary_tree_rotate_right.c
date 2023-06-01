#include "binary_trees.h"

/**
 * binary_tree_rotate_right - Performs a right rotation on a binary tree
 * @tree: Pointer to the root node of the tree
 *
 * Return: Pointer to the new root node of the tree
 */
binary_tree_t *binary_tree_rotate_right(binary_tree_t *tree)
{
    binary_tree_t *new_root = tree->left;

    if (new_root == NULL)
        return tree;

    tree->left = new_root->right;

    if (new_root->right != NULL)
        new_root->right->parent = tree;

    new_root->right = tree;
    new_root->parent = tree->parent;
    tree->parent = new_root;

    return new_root;
}
