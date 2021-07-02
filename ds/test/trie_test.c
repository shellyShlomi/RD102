
#include <stdio.h>

#include "trie.h"
#include "dhcp.h"

#define NUM_OF_BIT (3)

static void TestTrie();
static void TestRemove();
static void TestInsert();

static void Test();

int main()
{
    Test();
    return (0);
}

static void Test()
{
    TestTrie();
    TestInsert();
    TestRemove();

    return;
}

static void TestTrie()
{
    size_t num_of_bit = 2;
    unsigned long output_ip = 5;
    int status = 0;

    trie_t *trie = NULL;

    trie = TrieCreate(num_of_bit);

    if (NULL == trie)
    {
        printf("TrieCreate failed at line: %d\n", __LINE__);
    }

    if (SUCCESS != (status = TrieInsert(trie, 0, &output_ip)))
    {
        printf("TrieInsert failed at line: %d\n", __LINE__);

        if (0 != output_ip)
        {
            printf("TrieInsert failed at line: %d\n", __LINE__);
        }
    }
    if (SUCCESS != (status = TrieInsert(trie, 1, &output_ip)))
    {
        printf("TrieInsert failed at line: %d\n", __LINE__);

        if (1 != output_ip)
        {
            printf("TrieInsert failed at line: %d\n", __LINE__);
        }
    }
    if (SUCCESS != (status = TrieInsert(trie, 3, &output_ip)))
    {
        printf("TrieInsert failed at line: %d\n", __LINE__);

        if (3 != output_ip)
        {
            printf("TrieInsert failed at line: %d\n", __LINE__);
        }
    }
    if (SUCCESS != (status = TrieInsert(trie, 2, &output_ip)))
    {
        printf("TrieInsert failed at line: %d\n", __LINE__);

        if (2 != output_ip)
        {
            printf("TrieInsert failed at line: %d\n", __LINE__);
        }
    }
    if (TRIE_IS_FULL != (status = TrieInsert(trie, 0, &output_ip)))
    {
        printf("TrieInsert failed at line: %d\n", __LINE__);
    }

    if (4 != TrieSize(trie))
    {
        printf("TrieSize failed at line: %ld\n\n", TrieSize(trie));
    }
    TrieDestroy(trie);

    return;
}

static void TestInsert()
{

    unsigned int num_of_bit = NUM_OF_BIT;
    size_t size = 0X1 << NUM_OF_BIT;
    unsigned long output_ip = 0;
    trie_t *trie = NULL;
    size_t i = 0;

    trie = TrieCreate(num_of_bit);

    if (NULL == trie)
    {
        printf("TrieCreate failed at line: %d\n\n", __LINE__);
    }

    if (0 != TrieSize(trie))
    {
        printf("TrieSize failed at line: %d\n\n", __LINE__);
    }

    for (i = 0; i < size; ++i)
    {
        output_ip = 0;

        if (SUCCESS != TrieInsert(trie, 0, &output_ip))
        {
            if (i != output_ip)
            {
                printf("TrieInsert failed at line: %d\n ip: %ld exp ip %lu\n", __LINE__, output_ip, i);
            }
        }

        if ((i + 1) != TrieSize(trie))
        {
            printf("TrieSize failed at line: %d\n actual size: %lu exp size %lu\n", __LINE__, TrieSize(trie), i + 1);
        }
    }
    if (size != TrieSize(trie))
    {
        printf("TrieSize failed at line: %d\n actual size: %lu exp size %lu\n", __LINE__, TrieSize(trie), i + 1);
    }

    for (i = 0; i < size; ++i)
    {
        output_ip = 0;

        if (TRIE_IS_FULL != TrieInsert(trie, i, &output_ip))
        {
            printf("TrieInsert failed at line: %d\n in index: %lu\n", __LINE__, i);
        }
    }

    TrieDestroy(trie);

    return;
}

static void TestRemove()
{

    unsigned int num_of_bit = NUM_OF_BIT;
    size_t size = 0X1 << NUM_OF_BIT;
    unsigned long output_ip = 0;
    trie_t *trie = NULL;
    size_t i = 0;
    unsigned long remove1 = 7;
    unsigned long remove2 = 6;

    trie = TrieCreate(num_of_bit);

    if (NULL == trie)
    {
        printf("TrieCreate failed at line: %d\n\n", __LINE__);
    }

    if (0 != TrieSize(trie))
    {
        printf("TrieSize failed at line: %d\n\n", __LINE__);
    }

    for (i = 0; i < size; ++i)
    {
        output_ip = 0;

        if (SUCCESS != TrieInsert(trie, i, &output_ip))
        {
            printf("TrieInsert failed at line: %d\n in index: %lu\n", __LINE__, i);
            if (i != output_ip)
            {
                printf("TrieInsert failed at line: %d\n ip: %ld exp ip %lu\n", __LINE__, output_ip, i);
            }
        }
    }

    if (size != TrieSize(trie))
    {
        printf("TrieSize failed at line: %d\n actual size: %lu exp size %lu\n", __LINE__, TrieSize(trie), i + 1);
    }

    TrieRemove(trie, remove1);
    TrieRemove(trie, remove2);

    if (remove2 != TrieSize(trie))
    {
        printf("TrieSize failed at line: %d\n actual size: %lu exp size %lu\n", __LINE__, TrieSize(trie), remove2);
    }

    if (SUCCESS != TrieInsert(trie, 0, &output_ip))
    {
        printf("TrieInsert failed at line: %d\n", __LINE__);
        if (remove2 != output_ip)
        {
            printf("TrieInsert failed at line: %d\n ip: %ld exp ip %lu\n", __LINE__, output_ip, remove2);
        }
    }
    if (size - 1 != TrieSize(trie))
    {
        printf("TrieSize failed at line: %d\n actual size: %lu exp size %lu\n", __LINE__, TrieSize(trie), size - 1);
    }

    if (SUCCESS != TrieInsert(trie, remove1, &output_ip))
    {
        printf("TrieInsert failed at line: %d\n", __LINE__);
        if (remove1 != output_ip)
        {
            printf("TrieInsert failed at line: %d\n ip: %ld exp ip %lu\n", __LINE__, output_ip, remove1);
        }
    }
    if (size != TrieSize(trie))
    {
        printf("TrieSize failed at line: %d\n actual size: %lu exp size %lu\n", __LINE__, TrieSize(trie), size);
    }

    for (i = 0; i < size; ++i)
    {
        TrieRemove(trie, i);
        if (size - i - 1 != TrieSize(trie))
        {
            printf("TrieSize failed at line: %d\n actual size: %lu exp size %lu\n", __LINE__, TrieSize(trie), size - i - 1);
        }
    }

    for (i = 0; i < size; ++i)
    {
        TrieRemove(trie, i);
        if (0 != TrieSize(trie))
        {
            printf("TrieSize failed at line: %d\n actual size: %lu exp size %d\n", __LINE__, TrieSize(trie), 0);
        }
    }
    
    TrieDestroy(trie);
    return;
}
