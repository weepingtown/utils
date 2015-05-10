#include "dll.h"

#define DLL_NULL 0

void dll_init(dll_t *dll)
{
    dll->head = DLL_NULL;
    dll->tail = DLL_NULL;
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
        return;
    }

    dll->tail->next = node;
    node->prev = dll->tail;
    dll->tail = node;
    return;
}

void dll_add_head(dll_t *dll, dll_node_t *node)
{
    if (dll->head == DLL_NULL)
    {
        dll->head = node;
        dll->tail = node;
        return;
    }

    dll->head->prev = node;
    node->next = dll->head;
    dll->head = node;
    return;
}

void dll_remove(dll_t *dll, dll_node_t *node)
{
    if ((dll->head != node) && (dll->tail != node))
    {
        dll->head->prev = node;
        node->next = dll->head;
        dll->head = node;
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

