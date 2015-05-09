#ifndef _DLL_H_
#define _DLL_H_

#ifdef __cplusplus
extern "C" {
#endif


#define DLL_NULL 0

typedef struct dll_node_s
{
    struct dll_node_s *prev;
    struct dll_node_s *next;
    void *handle;
} dll_node_t;


typedef struct dll_s
{
    struct dll_node_s *first;
    int node_offsite;
    int key_offsite;
} dll_t;


#ifdef __cplusplus
}
#endif

#endif