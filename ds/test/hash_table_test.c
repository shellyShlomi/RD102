#include <stdio.h>  /* printf */
#include <stdlib.h> /* exit status */
#include <string.h> /* strcmp */

#include "hash_table.h"

#define UNUSED(x) (void)(x)

#define SIZE 50
#define INSERT_SIZE 5
#define DICT_SIZE 102401

#define ASCII_SIZE 256
#define ESC 27

typedef struct test
{
    size_t i;
    char **arr;
} test_t;

/*---------------func for API-----------------*/
/* to test the value in the hash table and comper it to expected value */
static int MatchFunc(const void *str1, const void *str2);
size_t HashFuncSimpleTest(const void *key);
static size_t HashFunc(const void *key);
size_t InerHashFunc(char *key);

/*---------------helper func to test foreach-----------------*/
static int CmpArrChar(void *data1, void *data2);

/*---------------Load Linux Dict-----------------*/
static char *DictLoad(hash_t *table);

/*---------------Spell Checker-----------------*/
static void SpellChecker(hash_t *table);

/*---------------test func-----------------*/
static void Test();
static void SimpleTest();
static void TestLodeDic();

/*------------------------------test for impl---------------------------------*/

int main()
{
    Test();

    return (0);
}

static void Test()
{
    SimpleTest();
    TestLodeDic();

    return;
}

static void SimpleTest()
{
    char *key[] = {"1 - shelly", "2 - shlomi", "3 - anna", "4 - ohad", "5 - ron"};
    size_t i = 0;
    int status = 0;
    test_t for_each = {0};
    void *temp_key = NULL;

    hash_t *table = HashCreate(INSERT_SIZE, HashFuncSimpleTest, MatchFunc);

    if (!HashIsEmpty(table))
    {
        printf("HashIsEmpty error at line: %d\n", __LINE__);
    }

    if (0 != HashSize(table))
    {
        printf("HashSize error at line: %d\n", __LINE__);
        printf("expected HashSize: 0\n");
        printf("result HashSize: %lu\n", HashSize(table));
    }

    if (0 != HashInsert(table, *key))
    {
        printf("HashInsert error at line: %d\n", __LINE__);
    }

    if (1 != HashSize(table))
    {
        printf("HashSize error at line: %d\n", __LINE__);
        printf("expected HashSize: %d\n", 1);
        printf("result HashSize: %lu\n", HashSize(table));
    }

    HashRemove(table, *key);

    if (HashSize(table))
    {
        printf("HashRemove error at line: %lu\n", HashSize(table));
    }

    while (i < INSERT_SIZE - 1)
    {
        if (0 != HashInsert(table, *(key + i)))
        {
            printf("HashInsert error at line: %d\n", __LINE__);
        }
        ++i;
    }

    temp_key = *key;
    if (!MatchFunc(temp_key, (char *)HashSearch(table, *key)))
    {
        printf("HashSearch error at line: %d\n", __LINE__);
        printf("expected HashSearch: %s\n", *key);
        printf("result HashSearch: %s\n", (char *)HashSearch(table, *key));
    }
    
    /* removing nonexsisting element */
    HashRemove(table, key[INSERT_SIZE - 1]);

    if (NULL != (HashSearch(table, key[INSERT_SIZE - 1])))
    {
        printf("HashSearch error at line: %d\n", __LINE__);
        printf("expected HashSearch: ron\n");
        printf("result HashSearch: %s\n", (char *)HashSearch(table, key[INSERT_SIZE - 1]));
    }

    HashRemove(table, key[INSERT_SIZE - 1]);
    if (INSERT_SIZE - 1 != HashSize(table))
    {
        printf("HashSize error at line: %lu\n", HashSize(table));
    }

    for_each.arr = key;
    for_each.i = 0;

    if ((status = HashForEach(table, CmpArrChar, &for_each)))
    {
        printf("HashForEach error at line: %d\n", __LINE__);
        printf("expected HashForEach: %d\n", 0);
        printf("result HashForEach: %d\n", status);
    }

    HashDestroy(table);

    return;
}

static void TestLodeDic()
{
    hash_t *table = HashCreate(DICT_SIZE, HashFunc, MatchFunc);
    char *str = NULL;

    if (!HashIsEmpty(table))
    {
        printf("HashIsEmpty error at line: %d\n", __LINE__);
    }

    if (0 != HashSize(table))
    {
        printf("HashSize error at line: %d\n", __LINE__);
        printf("expected HashSize: 0\n");
        printf("result HashSize: %lu\n", HashSize(table));
    }

    str = DictLoad(table);
    if (!str)
    {
        printf("DictLoad error at line: %d\n", __LINE__);
        printf("expected DictLoad: 0\n");
        printf("result DictLoad: %s\n", str);
    }

    if (DICT_SIZE != HashSize(table))
    {
        printf("DictLoad error at line: %d\n", __LINE__);
        printf("expected HashSize after DictLoad: %u\n", DICT_SIZE);
        printf("result HashSize after DictLoad: %lu\n", HashSize(table));
    }

    SpellChecker(table);

    free(str);
    HashDestroy(table);
}

/*------------------------------helper func--------------------------------*/

static int MatchFunc(const void *str1, const void *str2)
{
    return (!strcmp((char *)str1, (char *)str2));
}

static int CmpArrChar(void *data1, void *data2)
{
    char *elem = (((test_t *)data2)->arr[((test_t *)data2)->i]);

    ((test_t *)data2)->i += 1;

    return (strcmp((char *)data1, elem));
}

/* for first test */
size_t HashFuncSimpleTest(const void *key)
{
    size_t index = 0;

    index = (size_t)(*((char *)key) - '1');

    return (index % INSERT_SIZE);
}

/* for second test */
static size_t HashFunc(const void *key)
{
    return (InerHashFunc((char *)key));
}

size_t InerHashFunc(char *key)
{
    size_t index = 0;

    while ('\0' < *key)
    {
        index += (size_t)(*key);
        ++key;
    }

    return (index % DICT_SIZE);
}

/* Load Linux Dict */
static char *DictLoad(hash_t *table)
{
    FILE *file_ptr = NULL;
    char *start = NULL;
    char *str = NULL;

    str = (char *)malloc(SIZE * DICT_SIZE);
    if (NULL == str)
    {
        return NULL;
    }

    start = str;

    file_ptr = fopen("/usr/share/dict/words", "r");
    if (NULL == file_ptr)
    {
        free(start);
        return NULL;
    }

    while (NULL != fgets(str, SIZE, file_ptr))
    {
        if (0 != HashInsert(table, str))
        {
            printf("HashInsert error at line: %d\n", __LINE__);
        }
        str = (str + 1 + strlen(str));
    }

    fclose(file_ptr);

    return (start);
}

/* Spell Checker */
static void SpellChecker(hash_t *table)
{
    char buf[50] = {'\0'};
    
    printf("Insert words for spellcheck.\n**No longer then a 50 chars**\n hit ESC and ENTER to quit\n");

    while (NULL != fgets(buf, SIZE, stdin) && (ESC != *buf))
    {
        if (NULL == (char *)HashSearch(table, buf))
        {
            printf("no such word in the dictionery \n");
        }
    }

    return;
}
