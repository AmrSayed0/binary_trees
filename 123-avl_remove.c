#include <stdlib.h>
#include "binary_trees.h"

/**
 * avl_remove - Removes a node from an AVL tree.
 * @root: Pointer to the root node of the tree.
 * @value: The value to remove from the tree.
 *
 * Return: Pointer to the new root node of the tree after removing the value,
 *         and after rebalancing.
 */
avl_t *avl_remove(avl_t *root, int value)
{
    if (root == NULL)
        return NULL;

    if (value < root->n)
        root->left = avl_remove(root->left, value);
    else if (value > root->n)
        root->right = avl_remove(root->right, value);
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            avl_t *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;

            free(temp);
        }
        else
        {
            avl_t *temp = avl_find_min(root->right);

            root->n = temp->n;
            root->right = avl_remove(root->right, temp->n);
        }
    }

    if (root == NULL)
        return NULL;

    root->height = 1 + max(avl_height(root->left), avl_height(root->right));

    int balance = avl_balance(root);

    if (balance > 1 && avl_balance(root->left) >= 0)
        return avl_rotate_right(root);

    if (balance > 1 && avl_balance(root->left) < 0)
    {
        root->left = avl_rotate_left(root->left);
        return avl_rotate_right(root);
    }

    if (balance < -1 && avl_balance(root->right) <= 0)
        return avl_rotate_left(root);

    if (balance < -1 && avl_balance(root->right) > 0)
    {
        root->right = avl_rotate_right(root->right);
        return avl_rotate_left(root);
    }

    return root;
}

/**
 * avl_find_min - Finds the node with the minimum value in an AVL tree.
 * @node: Pointer to the root node of the tree.
 *
 * Return: Pointer to the node with the minimum value.
 */
avl_t *avl_find_min(avl_t *node)
{
    avl_t *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

/**
 * avl_height - Computes the height of an AVL tree.
 * @node: Pointer to the root node of the tree.
 *
 * Return: Height of the tree.
 */
int avl_height(const avl_t *node)
{
    if (node == NULL)
        return 0;

    int left_height = avl_height(node->left);
    int right_height = avl_height(node->right);

    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

/**
 * avl_balance - Computes the balance factor of an AVL tree.
 * @node: Pointer to the root node of the tree.
 *
 * Return: Balance factor of the tree.
 */
int avl_balance(const avl_t *node)
{
    if (node == NULL)
        return 0;

    return avl_height(node->left) - avl_height(node->right);
}

/**
 * avl_rotate_right - Performs a right rotation on an AVL tree.
 * @y: Pointer to the root node of the subtree to rotate.
 *
 * Return: Pointer to the new root node of the rotated subtree.
 */
avl_t *avl_rotate_right(avl_t *y)
{
    avl_t *x = y->left;
    avl_t *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(avl_height(y->left), avl_height(y->right)) + 1;
    x->height = max(avl_height(x->left), avl_height(x->right)) + 1;

    return x;
}

/**
 * avl_rotate_left - Performs a left rotation on an AVL tree.
 * @x: Pointer to the root node of the subtree to rotate.
 *
 * Return: Pointer to the new root node of the rotated subtree.
 */
avl_t *avl_rotate_left(avl_t *x)
{
    avl_t *y = x->right;
    avl_t *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(avl_height(x->left), avl_height(x->right)) + 1;
    y->height = max(avl_height(y->left), avl_height(y->right)) + 1;

    return y;
}

/**
 * max - Computes the maximum of two integers.
 * @a: First integer.
 * @b: Second integer.
 *
 * Return: The maximum of the two integers.
 */
int max(int a, int b)
{
    return (a > b) ? a : b;
}
