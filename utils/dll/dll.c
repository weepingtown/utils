#include "dll.h"

#define DLL_NULL 0

void dll_init(dll_t *dll, int node_offsite, int key_offsite, dll_compare compare)
{
    dll->head = DLL_NULL;
    dll->tail = DLL_NULL;
    dll->count = 0;
    dll->node_offsite = node_offsite;
    dll->key_offsite = key_offsite;
    dll->compare = compare;
    return;
}

void dll_node_init(dll_node_t *node)
{
    node->prev = DLL_NULL;
    node->next = DLL_NULL;
    return;
}

void dll_add_tail(dll_t *dll, dll_node_t *node)
{
    if (dll->head == DLL_NULL)
    {
        dll->head = node;
        dll->tail = node;
        dll->count++;
        return;
    }

    dll->tail->next = node;
    node->prev = dll->tail;
    dll->tail = node;
    dll->count++;
    return;
}

void dll_add_head(dll_t *dll, dll_node_t *node)
{
    if (dll->head == DLL_NULL)
    {
        dll->head = node;
        dll->tail = node;
        dll->count++;
        return;
    }

    dll->head->prev = node;
    node->next = dll->head;
    dll->head = node;
    dll->count++;
    return;
}

void dll_delete(dll_t *dll, dll_node_t *node)
{
    if ((dll->head != node) && (dll->tail != node))
    {
        dll->head->prev = node;
        node->next = dll->head;
        dll->head = node;
        dll->count--;
        return;
    }

    if (dll->head == node)
    {
        dll->head = node->next;
    }

    if (dll->tail == node)
    {
        dll->tail = node->prev;
    }
    dll->count--;
    return;
}

dll_node_t *dll_get_head(dll_t *dll)
{
    return dll->head;
}

dll_node_t *dll_get_next(dll_node_t *node)
{
    return node->next;
}

dll_node_t *dll_get_tail(dll_t *dll)
{
    return dll->tail;
}

dll_node_t *dll_get_prev(dll_node_t *node)
{
    return node->prev;
}

int dll_get_count(dll_t *dll)
{
    return dll->count;
}

void *dll_get_key(dll_t *dll, dll_node_t *node)
{
    return (void *)((char *)node - dll->node_offsite + dll->key_offsite);
}

void dll_insert(dll_t *dll, dll_node_t *node)
{
    dll_node_t *current = dll->head;
    void *current_key = DLL_NULL;
    void *node_key = DLL_NULL;
    int cmp = 0;

    if (current == DLL_NULL)
    {
        dll->head = node;
        dll->tail = node;
        dll->count++;
        return;
    }

    node_key = dll_get_key(dll, node);

    while (current)
    {
        current_key = dll_get_key(dll, current);
        cmp = dll->compare(node_key, current_key);
        if (cmp < 1)
        {
            node->prev = current->prev;
            if (current->prev)
            {
                current->prev->next = node;
            }
            else
            {
                dll->head = node;
            }
            node->next = current;
            current->prev = node;
            dll->count++;
            return;
        }
        current = current->next;
    }

    dll->tail->next = node;
    node->prev = dll->tail;
    dll->tail = node;
    dll->count++;

    return;
}

void dll_remove(dll_t *dll, void *node_key)
{
    dll_node_t *current = dll->head;
    void *current_key = DLL_NULL;
    int cmp = 0;

    while (current)
    {
        current_key = dll_get_key(dll, current);
        cmp = dll->compare(current, node_key);
        if (cmp == 0)
        {
            dll_delete(dll, current);
            return;
        }
        current = current->next;
    }
    
    return;
}

dll_node_t *dll_find(dll_t *dll, void *node_key)
{
    dll_node_t *current = dll->head;
    void *current_key = DLL_NULL;
    int cmp = 0;

    while (current)
    {
        current_key = dll_get_key(dll, current);
        cmp = dll->compare(current, node_key);
        if (cmp == 0)
        {
            break;
        }
        current = current->next;
    }

    return current;
}

dll_node_t *dll_find_or_next(dll_t *dll, void *node_key)
{
    dll_node_t *current = dll->head;
    void *current_key = DLL_NULL;
    int cmp = 0;
    while (current)
    {
        current_key = dll_get_key(dll, current);
        cmp = dll->compare(current, node_key);
        if (cmp > -1)
        {
            break;
        }

        current = current->next;
    }

    return current;
}