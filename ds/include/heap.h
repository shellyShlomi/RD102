/* Version 1 - 23.06.2021 16:00 */

#ifndef __OL_102_HEAP_H__
#define __OL_102_HEAP_H__

#include <stddef.h> /* size_t */

typedef int (*cmp_func_t)(const void *cur_node_data, const void *inserted_data);
typedef int (*is_match_func_t)(const void *cur_node_data, const void *searched_data);

typedef struct heap heap_t;

heap_t *HeapCreate(cmp_func_t cmp_func);

void HeapDestroy(heap_t *heap);

int HeapPush(heap_t *heap, void *data);

void HeapPop(heap_t *heap);

void *HeapPeek(const heap_t *heap);

size_t HeapSize(const heap_t *heap);

int HeapIsEmpty(const heap_t *heap);

void HeapRemove(heap_t *heap, is_match_func_t is_match, const void *searched_data);

#endif /* __OL_102_HEAP_H__ */



