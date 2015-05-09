#ifndef _AVL_H_
#define _AVL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define AVL_NULL 0

typedef struct avl_node_s
{
    struct avl_node_s *left;
    struct avl_node_s *right;
    struct avl_node_s *parent;
    int height;
} avl_node_t;

typedef int (*avl_compare)(void *key1, void *key2);

typedef struct avl_root_s
{
    struct avl_node_s *node;
    int node_offsite;
    int key_offsite;
    avl_compare compare;
} avl_root_t;

extern void avl_init_node(avl_node_t *node);
extern avl_root_t *avl_init_tree(avl_root_t *root, int key_offsite, int node_offsite, avl_compare compare);
extern avl_node_t *avl_insert(avl_root_t *root, avl_node_t *node);
extern void avl_remove(avl_root_t *root, avl_node_t *node);
extern void *avl_find(avl_root_t *root, void *key);
extern void *avl_first(avl_root_t *root);
extern void *avl_last(avl_root_t *root);
extern void *avl_next(avl_root_t *root, avl_node_t *node);
extern void *avl_prev(avl_root_t *root, avl_node_t *node);
extern void *avl_find_or_next(avl_root_t *root, void *key);

#ifdef __cplusplus
}
#endif

#endif
