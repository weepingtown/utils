#ifndef _DLL_H_
#define _DLL_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dll_node_s
{
    struct dll_node_s *prev;
    struct dll_node_s *next;
} dll_node_t;

typedef int(*dll_compare)(void *key1, void *key2);

typedef struct dll_s
{
    struct dll_node_s *head;
    struct dll_node_s *tail;
    int count;
    int node_offsite;
    int key_offsite;
    dll_compare compare;
} dll_t;

void dll_init(dll_t *dll, int node_offsite, int key_offsite, dll_compare compare);
void dll_node_init(dll_node_t *node);
void dll_add_tail(dll_t *dll, dll_node_t *node);
void dll_add_head(dll_t *dll, dll_node_t *node);
void dll_delete(dll_t *dll, dll_node_t *node);
dll_node_t *dll_get_head(dll_t *dll);
dll_node_t *dll_get_next(dll_node_t *node);
dll_node_t *dll_get_tail(dll_t *dll);
dll_node_t *dll_get_prev(dll_node_t *node);
int dll_get_count(dll_t *dll);
void dll_insert(dll_t *dll, dll_node_t *node);
void dll_remove(dll_t *dll, void *node_key);
dll_node_t *dll_find(dll_t *dll, void *node_key);
dll_node_t *dll_find_or_next(dll_t *dll, void *node_key);

#ifdef __cplusplus
}
#endif

#endif
