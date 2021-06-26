/*  Developer: Shelly Shlomi;									*
 *  Status:in development;                                      *
 *  Date Of Creation:24.06.21;									*
 *  Date Of Approval:--.06.21;									*
 *  Approved By: ;	            								*
 *  Description:Heap data structure implement with              *     
 *              dynamic vector                                  * 
 *                                                              */

#include <stdlib.h> /* malloc */
#include <stddef.h> /* size_t */
#include <assert.h>

#include "heap.h"
#include "vector.h"

#define LAST_IDX(X) ((size_t)(HeapSize((X)) - 1))
#define GET_ELEM(X, I) (VectorGetElem((X)->vector, (I)))
#define GET_LEFT_CHILD_IDX(I) (((I)*2) + 1)
#define GET_RIGHT_CHILD_IDX(I) (((I)*2) + 2)
#define GET_PARENT_IDX(I) (((I) - 1) / 2)

#define CAPACITY (50)
#define START (0)
#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define UNUSED(x) (void)(x)

typedef void (*heapify_t)(heap_t *, size_t);

typedef enum operation
{
    PUSH,
    POP
} operation_t;

struct heap
{
    cmp_func_t func;
    vector_t *vector;
};

/*-----------------Heapify funcs----------------*/
static void Heapify(heap_t *heap, size_t idx, operation_t operation);
static void HeapifyUp(heap_t *heap, size_t unused);
static void HeapifyDown(heap_t *heap, size_t idx);

/*---------------API iner funcs-----------------*/
static size_t HeapFindIdx(heap_t *heap, is_match_func_t is_match, void *data, int *is_found);
static void InerHeapPop(heap_t *heap, size_t idx);

/*----------------Helper func-------------------*/
static void SwapHeapElem(heap_t *heap, size_t idx_1, size_t idx_2);
static size_t FindBigerChild(heap_t *heap, size_t right_c_idx, size_t left_c_idx);

/*---------------------------------Implementation---------------------------------*/
heap_t *HeapCreate(cmp_func_t cmp_func)
{
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));

    assert(cmp_func);

    if (!heap)
    {
        return (NULL);
    }

    heap->func = cmp_func;
    heap->vector = VectorCreate(CAPACITY);

    if (!heap->vector)
    {
        heap->func = NULL;
        free(heap);
        heap = NULL;
    }

    return (heap);
}

void HeapDestroy(heap_t *heap)
{
    assert(heap);
    assert(heap->vector);
    assert(heap->func);

    VectorDestroy(heap->vector);

    heap->vector = NULL;
    heap->func = NULL;

    free(heap);
    heap = NULL;

    return;
}

int HeapPush(heap_t *heap, void *data)
{
    int status = EXIT_SUCCESS;

    assert(heap);
    assert(heap->vector);

    status = VectorPushBack(heap->vector, data);
    if (!status)
    {
        Heapify(heap, START, PUSH);
    }

    return (status);
}

void HeapPop(heap_t *heap)
{
    assert(heap);
    assert(heap->vector);

    InerHeapPop(heap, START);

    return;
}

void *HeapPeek(const heap_t *heap)
{
    assert(heap);
    assert(heap->vector);

    return (VectorGetElem(heap->vector, (size_t)START));
}

size_t HeapSize(const heap_t *heap)
{
    assert(heap);
    assert(heap->vector);

    return (VectorSize(((heap_t *)heap)->vector));
}

int HeapIsEmpty(const heap_t *heap)
{
    assert(heap);
    assert(heap->vector);

    return (!(HeapSize((heap_t *)heap)));
}

void *HeapRemove(heap_t *heap, is_match_func_t is_match, const void *searched_data)
{
    size_t idx = 0;
    int is_found = 0;
    void *found_elem = NULL;

    assert(heap);
    assert(is_match);
    assert(heap->vector);

    idx = HeapFindIdx(heap, is_match, (void *)searched_data, &is_found);

    if (is_found)
    {
        found_elem = GET_ELEM(heap, idx);
        InerHeapPop(heap, idx);
    }

    return (found_elem);
}

/*--------------------------------API iner funcs---------------------------------*/

static size_t HeapFindIdx(heap_t *heap, is_match_func_t is_match, void *data, int *is_found)
{
    size_t i = 0;

    assert(heap);
    assert(is_match);
    assert(is_found);
    assert(heap->vector);

    while (i < HeapSize(heap) &&
           !(*is_found = is_match(GET_ELEM(heap, i), data)))
    {
        ++i;
    }

    return (i);
}

static void InerHeapPop(heap_t *heap, size_t idx)
{
    size_t size = 0;

    assert(heap);
    assert(heap->vector);
    assert(idx < HeapSize(heap));

    VectorSetElem(heap->vector, idx, GET_ELEM(heap, LAST_IDX(heap)));

    VectorPopBack(heap->vector);
    size = HeapSize(heap);

    if ((1 < size) && (idx < size))
    {
        Heapify(heap, idx, POP);
    }

    return;
}

/*---------------------------------Heapify funcs---------------------------------*/

static void Heapify(heap_t *heap, size_t idx, operation_t operation)
{
    heapify_t heapify_func_lut[] = {HeapifyUp, HeapifyDown};

    assert(heap);
    assert(PUSH == operation || POP == operation);
    assert(heap->vector);

    heapify_func_lut[operation](heap, idx);

    return;
}

static void HeapifyUp(heap_t *heap, size_t unused)
{
    size_t last_elem = 0;
    size_t parent = last_elem;
    void *elem = NULL;
    void *temp_parent = NULL;

    assert(heap);
    UNUSED(unused);

    last_elem = LAST_IDX(heap);
    elem = GET_ELEM(heap, last_elem);
    parent = GET_PARENT_IDX(last_elem);

    while (last_elem > 0)
    {
        temp_parent = GET_ELEM(heap, parent);

        if (0 > heap->func(temp_parent, elem))
        {
            SwapHeapElem(heap, last_elem, parent);
            last_elem = parent;
            parent = GET_PARENT_IDX(parent);
            continue;
        }

        return;
    }

    return;
}

static void HeapifyDown(heap_t *heap, size_t idx)
{
    size_t last_elem = 0;
    size_t swap_idx = 0;

    size_t left_child_idx = GET_LEFT_CHILD_IDX(idx);
    size_t right_child_idx = GET_RIGHT_CHILD_IDX(idx);

    void *elem = NULL;
    void *swap_elem = NULL;

    assert(heap);

    last_elem = LAST_IDX(heap);
    elem = GET_ELEM(heap, idx);

    while (left_child_idx <= last_elem)
    {
        swap_idx = left_child_idx;
        swap_elem = GET_ELEM(heap, swap_idx);

        /* checks if right child is exist 
         * if so - test which one is the biger between both childs
         */
        if (right_child_idx <= last_elem)
        {
            swap_idx = FindBigerChild(heap, right_child_idx, left_child_idx);
            swap_elem = GET_ELEM(heap, swap_idx);
        }
        /* check is there is need to swap - if not end the function */
        if (0 > heap->func(swap_elem, elem))
        {
            return;
        }

        SwapHeapElem(heap, idx, swap_idx);
        idx = swap_idx;

        /* update children of new idx */
        left_child_idx = GET_LEFT_CHILD_IDX(idx);
        right_child_idx = GET_RIGHT_CHILD_IDX(idx);
    }

    return;
}

/*---------------------------------Helper funcs----------------------------------*/
static void SwapHeapElem(heap_t *heap, size_t idx_1, size_t idx_2)
{
    void *temp = NULL;

    assert(heap);
    assert(heap->vector);

    temp = GET_ELEM(heap, idx_1);

    VectorSetElem(heap->vector, idx_1, GET_ELEM(heap, idx_2));
    VectorSetElem(heap->vector, idx_2, temp);

    return;
}

static size_t FindBigerChild(heap_t *heap, size_t right_c_idx, size_t left_c_idx)
{
    size_t idx = right_c_idx;

    assert(heap);
    assert(heap->vector);

    if (0 < heap->func(GET_ELEM(heap, left_c_idx), GET_ELEM(heap, right_c_idx)))
    {
        idx = left_c_idx;
    }

    return (idx);
}