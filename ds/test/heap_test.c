#include <stdio.h> /* printf */

#include "heap.h"

static void HeapTest();
static void RemoveTest();

static int Cmp(const void *data1, const void *data2);
static int Match(const void *data1, const void *data2);

int main()
{
    HeapTest();
    RemoveTest();

    return (0);
}

static void HeapTest()
{
    int arr[] = {5, -2, 13, 15, -30, 21, 22, 41, 65, 0,
                 100, 200, 40, 30, 35, 33, -1};

    int exp_max[] = {5, 5, 13, 15, 15, 21, 22, 41, 65, 65,
                     100, 200, 200, 200, 200, 200, 200};

    int test_pop_arr[] = {200, 100, 65, 41, 40, 35, 33, 30, 22, 21,
                          15, 13, 5, 0, -1, -2, -30};

    size_t i = 0;

    size_t arr_size = sizeof(arr) / sizeof(arr[0]);

    heap_t *heap = HeapCreate(Cmp);

    if (NULL == heap)
    {
        printf("HeapCreate Failed at line: %d\n", __LINE__);

        return;
    }

    if (!HeapIsEmpty(heap))
    {
        printf("HeapIsEmpty Failed at line: %d\n", __LINE__);
    }

    if (0 != HeapSize(heap))
    {
        printf("HeapSize Failed at line: %d\n", __LINE__);
    }

    for (i = 0; i < arr_size; ++i)
    {
        if (0 != HeapPush(heap, (arr + i)))
        {
            printf("HeapPush failed at line: %d in index: %lu\n", __LINE__, i);
        }

        if (exp_max[i] != *(int *)HeapPeek(heap))
        {
            printf("HeapPeek failed at line: %d in index: %lu\n", __LINE__, i);
        }
    }

    if (HeapIsEmpty(heap))
    {
        printf("HeapIsEmpty Failed at line: %d\n", __LINE__);
    }

    if (arr_size != HeapSize(heap))
    {
        printf("HeapSize Failed at line: %d\n", __LINE__);
    }

    for (i = 0; i < arr_size; ++i)
    {
        if (test_pop_arr[i] != *(int *)HeapPeek(heap))
        {
            printf("HeapPeek failed at line: %d in index: %lu\n", __LINE__, i);
        }

        HeapPop(heap);
    }

    if (!HeapIsEmpty(heap))
    {
        printf("HeapIsEmpty Failed at line: %d\n", __LINE__);
    }

    if (0 != HeapSize(heap))
    {
        printf("HeapSize Failed at line: %d\n", __LINE__);
    }

    HeapDestroy(heap);

    return;
}

static void RemoveTest()
{
    int arr[] = {5, -2, 13, 15, -30, 21, 22, 41, 65, 0,
                 100, 200, 40, 30, 35, 33, -1};

    int remove_arr[] = {200, -100, 15, -30, 100, 5, 0, 400, 65, 40,
                        -2, 13, 35, 30, -1, 33, 41, 21, 22};

    int exp_val[] = {100, 100, 100, 100, 65, 65, 65, 65, 41, 41,
                     41, 41, 41, 41, 41, 41, 22, 22};

    size_t exp_size[] = {16, 16, 15, 14, 13, 12, 11, 11, 10, 9,
                         8, 7, 6, 5, 4, 3, 2, 1, 0};

    size_t i = 0;

    size_t arr_size = sizeof(arr) / sizeof(arr[0]);
    size_t remove_size = sizeof(remove_arr) / sizeof(remove_arr[0]);

    heap_t *heap = HeapCreate(Cmp);

    int *remove_elem = NULL;

    if (NULL == heap)
    {
        printf("HeapCreate Failed at line: %d\n", __LINE__);

        return;
    }

    if (!HeapIsEmpty(heap))
    {
        printf("HeapIsEmpty Failed at line: %d\n", __LINE__);
    }

    if (0 != HeapSize(heap))
    {
        printf("HeapSize Failed at line: %d\n", __LINE__);
    }

    for (i = 0; i < arr_size; ++i)
    {
        if (0 != HeapPush(heap, (arr + i)))
        {
            printf("HeapPush failed at line: %d in index: %lu\n", __LINE__, i);
        }
    }

    if (HeapIsEmpty(heap))
    {
        printf("HeapIsEmpty Failed at line: %d\n", __LINE__);
    }

    if (arr_size != HeapSize(heap))
    {
        printf("HeapSize Failed at line: %d\n", __LINE__);
    }

    for (i = 0; i < remove_size - 1; ++i)
    {
        remove_elem = (int *)HeapRemove(heap, Match, (void *)(remove_arr + i));

        if (NULL != remove_elem && remove_arr[i] != *(int *)remove_elem)
        {
            printf("HeapRemove failed at line: %d in index: %lu\n", __LINE__, i);
            printf("Remove: %d - ", *remove_elem);
            printf("exp Remove: %d ", remove_arr[i]);
            printf("\n");
        }
        if (NULL != remove_elem && (exp_val[i] != *(int *)HeapPeek(heap)))
        {
            printf("HeapPeek failed at line: %d in index: %lu\n", __LINE__, i);
            printf("peek: %d - ", *(int *)HeapPeek(heap));
            printf("exp peek: %d ", exp_val[i]);
            printf("\n");
        }

        if (NULL != remove_elem && exp_size[i] != HeapSize(heap))
        {
            printf("HeapSize failed at line: %d in index: %lu\n", __LINE__, i);
            printf("size: %ld\n", HeapSize(heap));
            printf("exp size: %ld\n", exp_size[i]);
            printf("\n");
        }
    }

    HeapRemove(heap, Match, (void *)(remove_arr + i));

    if (0 != HeapSize(heap))
    {
        printf("HeapSize failed at line: %d in index: %lu\n", __LINE__, i);
    }

    if (!HeapIsEmpty(heap))
    {
        printf("HeapIsEmpty Failed at line: %d\n", __LINE__);
    }

    HeapDestroy(heap);

    return;
}

static int Cmp(const void *data1, const void *data2)
{
    return (*(int *)data1 - *(int *)data2);
}

static int Match(const void *data1, const void *data2)
{
    return ((*(int *)data1 == *(int *)data2));
}
