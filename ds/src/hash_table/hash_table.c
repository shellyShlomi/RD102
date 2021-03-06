/*  Developer: Shelly Shlomi;									*
 *  Status:Approved;                                            *
 *  Date Of Creation:20.06.21;									*
 *  Date Of Approval:--.06.21;									*
 *  Approved By:  Eden Wittenberg;	            				*
 *  Description: hash table- a data structur of key value pairs */

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "hash_table.h"
#include "dll.h"

#define UNUSED(x) (void)(x)

struct hash
{
    size_t capacity;
    hash_func_t func;
    match_func_t match;
    d_list_t *hash_table[1];
};

typedef struct hash_counter
{
    size_t counter;
    hash_t *hash;

} hash_counter_t;

static void SetHash(hash_t *hash, size_t capacity, hash_func_t func, match_func_t match);

hash_t *HashCreate(size_t size, hash_func_t func, match_func_t match)
{
    hash_t *table = NULL;
    size_t i = 0;

    assert(func);
    assert(match);
    assert(0 < size);

    table = (hash_t *)malloc(offsetof(hash_t, hash_table) + (size * sizeof(d_list_t *)));

    if (NULL == table)
    {
        return (NULL);
    }

    SetHash(table, size, func, match);

    for (i = 0; i < size; ++i)
    {
        table->hash_table[i] = DLLCreate();

        if (NULL == table->hash_table[i])
        {
            table->capacity = i;
            HashDestroy(table);

            return (NULL);
        }
    }

    return (table);
}

void HashDestroy(hash_t *hash)
{
    size_t i = 0;

    assert(hash);

    for (i = 0; i < hash->capacity; ++i)
    {
        DLLDestroy(hash->hash_table[i]);
    }
    SetHash(hash, 0, NULL, NULL);

    free(hash);
    hash = NULL;

    return;
}

int HashInsert(hash_t *hash, void *key)
{
    size_t index = 0;

    assert(hash);
    assert(hash->func);

    index = hash->func(key);

    return (DLLIsSameIter(DLLPushBack(hash->hash_table[index], key),
                          DLLEnd(hash->hash_table[index])));
}

void HashRemove(hash_t *hash, const void *key)
{
    size_t index = 0;
    d_list_iter_t to_remove = NULL;
    d_list_iter_t dummy = NULL;

    assert(hash);
    assert(hash->func);
    assert(hash->match);

    index = hash->func((void *)key);
    dummy = DLLEnd(hash->hash_table[index]);

    to_remove = DLLFind(DLLBegin(hash->hash_table[index]), dummy, hash->match, key);

    if (!DLLIsSameIter(to_remove, dummy))
    {
        DLLRemove(to_remove);
    }

    return;
}

void *HashSearch(const hash_t *hash, const void *key)
{
    size_t index = 0;
    d_list_iter_t dummy = {NULL};
    d_list_iter_t found = {NULL};

    assert(hash);
    assert(hash->func);
    assert(hash->match);

    index = hash->func(key);
    dummy = DLLEnd(hash->hash_table[index]);
    found = DLLFind(DLLBegin(((hash_t *)hash)->hash_table[index]),
                    dummy, hash->match, key);
    if (DLLIsSameIter(found, dummy))
    {
        return (NULL);
    }

    return (DLLGetData(found));
}

int HashForEach(const hash_t *hash, action_func_t func, void *param)
{
    size_t i = 0;
    int status = 0;

    assert(hash);
    assert(func);

    for (i = 0; i < hash->capacity && !status; ++i)
    {
        status = DLLForEach(DLLBegin(((hash_t *)hash)->hash_table[i]),
                            DLLEnd(((hash_t *)hash)->hash_table[i]), func, param);
    }

    return (status);
}

int HashIsEmpty(const hash_t *hash)
{
    assert(hash);

    return (!HashSize(hash));
}

size_t HashSize(const hash_t *hash)
{
    size_t counter = 0;
    size_t i = 0;

    assert(hash);

    for (i = 0; i < hash->capacity; ++i)
    {
        counter += DLLSize(((hash_t *)hash)->hash_table[i]);
    }

    return (counter);
}

/*------------------------------helper_function---------------------------------*/

static void SetHash(hash_t *hash, size_t capacity, hash_func_t func, match_func_t match)
{
    hash->capacity = capacity;
    hash->func = func;
    hash->match = match;

    return;
}
