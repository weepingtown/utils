
#include "avl.h"

#define AVL_NULL 0

int avl_max(int a, int b)
{
  return (a > b) ? a : b;
}

void *avl_get_key(avl_root_t *root, avl_node_t *node)
{
    return (void *)((char *)node - root->node_offsite + root->key_offsite);
}

avl_node_t *_avl_find(avl_root_t *root, void *key)
{
    avl_node_t *node = root->node;
    void *node_key = AVL_NULL;
    int cmp = 0;
    while (node)
    {
        node_key = avl_get_key(root, node);
        cmp = root->compare(key, node_key);
        if (cmp == -1)
            node = node->left;
        else if (cmp == 1)
            node = node->right;
        else
            break;
    }

    return node;
}

void *avl_find(avl_root_t *root, void *key)
{
    avl_node_t *node = _avl_find(root, key);

    return node ? (void *)((char *)node - root->node_offsite) : AVL_NULL;
}

avl_node_t *_avl_first(avl_node_t *root)
{
    avl_node_t *node = root;
    while (node->left)
        node = node->left;
    return node;
}

void *avl_first(avl_root_t *root)
{
    avl_node_t *node = _avl_first(root->node);

    return node ? (void *)((char *)node - root->node_offsite) : AVL_NULL;
}

avl_node_t *_avl_last(avl_node_t *root)
{
    avl_node_t *node = root;
    while (node->right)
        node = node->right;
    return node;
}

void *avl_last(avl_root_t *root)
{
    avl_node_t *node = _avl_last(root->node);

    return node ? (void *)((char *)node - root->node_offsite) : AVL_NULL;
}

avl_node_t *_avl_prev(avl_node_t *node)
{
    avl_node_t *current = node;
    avl_node_t *parent = node->parent;
    if (current->left == AVL_NULL && current->right == AVL_NULL)
    {
        while (parent)
        {
            if (parent->right == current)
            {
                return (void *)parent;
            }
            current = parent;
            parent = current->parent;
        }
    }
    else if (current->left == AVL_NULL)
    {
        if (parent)
        {
            return (void *)parent;
        }
    }
    else
    {
        parent = current;
        current = current->left;
        while (current)
        {
            if (current->right == AVL_NULL)
            {
                return (void *)current;
            }
            parent = current;
            current = current->right;
        }
    }
    return AVL_NULL;
}

void *avl_prev(avl_root_t *root, avl_node_t *node)
{
    avl_node_t *current = _avl_prev(node);
    return current ? (void *)((char *)current - root->node_offsite) : AVL_NULL;
}

avl_node_t *_avl_next(avl_node_t *node)
{
    avl_node_t *current = node;
    avl_node_t *parent = node->parent;
    if (current->left == AVL_NULL && current->right == AVL_NULL)
    {
        while (parent)
        {
            if (parent->left == current)
            {
                return (void *)parent;
            }
            current = parent;
            parent = current->parent;
        }
    }
    else if (current->right == AVL_NULL)
    {
        if (parent)
        {
            return (void *)parent;
        }
    }
    else
    {
        parent = current;
        current = current->right;
        while (current)
        {
            if (current->left == AVL_NULL)
            {
                return (void *)current;
            }
            parent = current;
            current = current->left;
        }
    }
    return AVL_NULL;
}

void *avl_next(avl_root_t *root, avl_node_t *node)
{
    avl_node_t *current = _avl_next(node);
    return current ? (void *)((char *)current - root->node_offsite) : AVL_NULL;
}

void *avl_find_or_next(avl_root_t *root, void *key)
{
    avl_node_t *node = AVL_NULL;
    void *node_key = AVL_NULL;
    int cmp = 0;

    for (node = _avl_first(root->node); node; node = _avl_next(node))
    {
        node_key = avl_get_key(root, node);
        cmp = root->compare(key, node_key);
        if (cmp != 1)
        {
            break;
        }
    }
    return (void *)((char *)node - root->node_offsite);
}

int avl_height(avl_node_t *root)
{
    return root ? root->height : 0;
}


void avl_adjust_height(avl_node_t *root)
{
    root->height = 1 + avl_max(avl_height(root->left), avl_height(root->right));
}


avl_node_t *avl_rotate_right(avl_node_t *root)
{
    avl_node_t *new_root = root->left;
    if (root->parent)
    {
        if (root->parent->left == root) root->parent->left = new_root;
        else root->parent->right = new_root;
    }
    new_root->parent = root->parent;
    root->parent = new_root;
    root->left = new_root->right;
    if (root->left) root->left->parent = root;
    new_root->right = root;

    avl_adjust_height(root);
    avl_adjust_height(new_root);
    return new_root;
}


avl_node_t *avl_rotate_left(avl_node_t *root)
{

    avl_node_t *new_root = root->right;
    if (root->parent)
    {
        if (root->parent->right == root) root->parent->right = new_root;
        else root->parent->left = new_root;
    }
    new_root->parent = root->parent;
    root->parent = new_root;
    root->right = new_root->left;
    if (root->right) root->right->parent = root;
    new_root->left = root;

    avl_adjust_height(root);
    avl_adjust_height(new_root);
    return new_root;
}


void avl_init_tree(avl_root_t *root, int key_offsite, int node_offsite, avl_compare compare)
{
    root->node = AVL_NULL;
    root->compare = compare;
    root->key_offsite = key_offsite;
    root->node_offsite = node_offsite;

    return;
}


void avl_init_node(avl_node_t *node)
{
    node->parent = AVL_NULL;
    node->height = 1;
    node->left = AVL_NULL;
    node->right = AVL_NULL;
    return;
}


avl_node_t *avl_balance(avl_node_t *root)
{
    if (avl_height(root->left) - avl_height(root->right) > 1)
    {
        if (avl_height(root->left->left) > avl_height(root->left->right))
        {
            root = avl_rotate_right(root);
        }
        else
        {
            avl_rotate_left(root->left);
            root = avl_rotate_right(root);
        }
    }
    else if (avl_height(root->right) - avl_height(root->left) > 1)
    {
        if (avl_height(root->right->right) > avl_height(root->right->left))
        {
            root = avl_rotate_left(root);
        }
        else
        {
            avl_rotate_right(root->right);
            root = avl_rotate_left(root);
        }
    }
    return root;
}


avl_node_t *avl_insert(avl_root_t *root, avl_node_t *node)
{
    avl_node_t *current = root->node;
    void *node_key = AVL_NULL;
    void *current_key = AVL_NULL;
    int cmp = 0;

    if (current == AVL_NULL)
    {
        node->parent = AVL_NULL;
        root->node = node;
        return AVL_NULL;
    }

    node_key = avl_get_key(root, node);
    current_key = avl_get_key(root, current);
    cmp = root->compare(current_key, node_key);
    while (cmp != 0)
    {
        if (cmp == 1)
        {
            if (current->left)
            {
                current = current->left;
            }
            else
            {
                node->parent = current;
                current->left = node;
                current = current->left;
            }
        }
        else if (cmp == -1)
        {
            if (current->right)
            {
                current = current->right;
            }
            else
            {
                node->parent = current;
                current->right = node;
                current = current->right;
            }
        }
        else
        {
            return AVL_NULL;
        }

        current_key = avl_get_key(root, current);
        cmp = root->compare(current_key, node_key);
    }

    do
    {
        current = current->parent;
        avl_adjust_height(current);
        current = avl_balance(current);
    } while (current->parent);
    root->node = current;
    return AVL_NULL;
}


void avl_remove(avl_root_t *root, avl_node_t *node)
{
    avl_node_t *node_parent = node->parent;
    avl_node_t *current = node;
    avl_node_t *rebalance = AVL_NULL;

    if (node == AVL_NULL)
    {
        return;
    }

    if (node->right)
    {
        current = node->right;
        while (current->left)
        {
            current = current->left;
        }
        rebalance = current->parent;

        if (current->parent != node)
        {
            current->parent->left = current->right;
            current->left = node->left;
            current->right = node->right;
        }
        else
        {
            current->left = node->left;
        }

        current->parent = node_parent;
        if (node_parent)
        {
            if (node_parent->left == node)
            {
                node_parent->left = current;
            }
            else if (node_parent->right == node)
            {
                node_parent->right = current;
            }
        }

        if (node->left && node->left != current)
        {
            node->left->parent = current;
        }
            
        if (node->right && node->right != current)
        {
            node->right->parent = current;
        }
    }
    else
    {
        current = node->left;
        if (current)
        {
            current->parent = node->parent;
            rebalance = current;
        }
        else
        {
            rebalance = node;
        }

        if (node_parent->left == node)
        {
            node_parent->left = current;
        }
        else if (node_parent->right == node)
        {
            node_parent->right = current;
        }
    }

    do
    {
        rebalance = rebalance->parent;
        avl_adjust_height(rebalance);
        rebalance = avl_balance(rebalance);
    } while (rebalance->parent);

    root->node = rebalance;
    return;
}