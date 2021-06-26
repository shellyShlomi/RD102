/*  Developer: Shelly Shlomi;									*
 *  Status:done;                                                *
 *  Date Of Creation:15.06.21;									*
 *  Description: TESTS for slef balancing tree                  *
 *               with a limit of abs 2 for the balancing factor */

#include <stdio.h>  /* printf */
#include <stdlib.h> /* exit status */

#include "avl.h"

#define UNUSED(x) (void)(x)
#define SIZE 10


typedef struct test
{
    long int i;
    int *arr;
} testfe_t;
/*---------------helper iner func-----------------*/

static int Compare(void *data1, void *data2);
static int CmpArrInts(void *data1, void *data2);

/*---------------test func-----------------*/

static void Test();
static void TestAVL();
static void TestRemove();
static void TestRemove1();

static void TestInsertAVL();
static void TestForEachAVL();
static void TestForEachAndFindAVL();
static void TestAVLHeight();

int main()
{
    Test();

    return (0);
}
static void Test()
{
    TestAVL();
    TestInsertAVL();
    TestForEachAVL();
    TestForEachAndFindAVL();
    TestAVLHeight();
    TestRemove();
    TestRemove1();
    return;
}

static void TestAVL()
{
    avl_t *tree = AVLCreate(Compare);
    if (NULL == tree)
    {
        printf("TestAVL AVLCreate failed %d\n", __LINE__);
    }

    if (1 !=  AVLIsEmpty(tree))
    {
        printf("TestAVL AVLIsEmpty failed at line: %d\n", __LINE__);
    }

    if (0 != AVLSize(tree))
    {
        printf("TestAVL AVLSize failed at line: %d\n", __LINE__);
    }

    AVLDestroy(tree);
    return;
}

static void TestInsertAVL()
{
    int array[] = {1, 10, 4, 7, 3, 2, 8, 9, 5, 6};
    size_t size = sizeof(array) / sizeof(array[0]);
    int arr[sizeof(array) / sizeof(array[0])] = {0};
    size_t i = 0;
    avl_t *tree = AVLCreate(Compare);

    if (NULL == tree)
    {
        printf("TestAVL AVLCreate failed %d\n", __LINE__);
    }

    if (1 != AVLIsEmpty(tree))
    {
        printf("TestAVL AVLIsEmpty failed at line: %d\n", __LINE__);
    }

    for (i = 0; i < size && !arr[i]; ++i)
    {
        arr[i] = AVLInsert(tree, (void *)(array + i));
    }

    if (size != AVLSize(tree))
    {
        printf("TestAVL AVLInsert failed at line: %d %lu\n", __LINE__, AVLSize(tree));
    }

    AVLDestroy(tree);
    return;
}

static void TestForEachAVL()
{
    avl_t *tree = AVLCreate(Compare);
    int arr[] = {10, 8, 15, 17, 16, 7, 2};
    int exp_in_order[] = {2, 7, 8, 10, 15, 16, 17};
    int exp_pre_order[] = {10, 7, 2, 8, 16, 15, 17};
    int exp_post_order[] = {2, 8, 7, 15, 17, 16, 10};

    size_t size = sizeof(arr) / sizeof(int);
    size_t i = 0;

    testfe_t for_each = {0};

    while (i < size)
    {
        AVLInsert(tree, arr + i);
        ++i;
    }

    if (size != AVLSize(tree))
    {
        printf("LINE:%d error.\n", __LINE__);
        printf("Expected size: %ld.\n", size);
        printf("Actual size: %ld.\n", AVLSize(tree));
    }

    for_each.arr = exp_in_order;
    for_each.i = 0;
    if (0 != AVLForEach(tree, CmpArrInts, (&for_each), IN_ORDER))
    {
        printf("TestAVL AVLForEach IN_ORDER failed at line:%d \n", __LINE__);
    }

    for_each.arr = exp_pre_order;
    for_each.i = 0;

    if (0 != AVLForEach(tree, CmpArrInts, (&for_each), PRE_ORDER))
    {
        printf("TestAVL AVLForEach PRE_ORDER failed at line:%d \n", __LINE__);
    }

    for_each.arr = exp_post_order;
    for_each.i = 0;
    if (0 != AVLForEach(tree, CmpArrInts, (&for_each), POST_ORDER))
    {
        printf("TestAVL AVLForEach POST_ORDER failed at line:%d \n", __LINE__);
    }

    AVLDestroy(tree);

    return;
}

static void TestForEachAndFindAVL()
{
    int array[] = {4, 10, 7, 3, 2, 8, 9, 5, 1, 6};
    int exp_in_order[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int exp_pre_order[] = {7, 3, 2, 1, 5, 4, 6, 9, 8, 10};
    int exp_post_order[] = {1, 2, 4, 6, 5, 3, 8, 10, 9, 7};
    size_t size = sizeof(array) / sizeof(array[0]);
    size_t i = 0;
    avl_t *tree = AVLCreate(Compare);
    testfe_t for_each = {0};

    if (NULL == tree)
    {
        printf("TestAVL AVLCreate failed %d\n", __LINE__);
    }

    if (1 != AVLIsEmpty(tree))
    {
        printf("TestAVL AVLIsEmpty failed at line: %d\n", __LINE__);
    }

    for (i = 0; i < size; ++i)
    {
        AVLInsert(tree, (array + i));
    }

    if (size != AVLSize(tree))
    {
        printf("TestAVL AVLInsert failed at line: %d %lu\n", __LINE__, AVLSize(tree));
    }

    for_each.arr = exp_in_order;
    for_each.i = 0;

    if (0 != AVLForEach(tree, CmpArrInts, (void *)(&for_each), IN_ORDER))
    {
        printf("TestAVL AVLForEach IN_ORDER failed at line:%d \n", __LINE__);
    }

    for_each.arr = exp_pre_order;
    for_each.i = 0;

    if (0 != AVLForEach(tree, CmpArrInts, (void *)(&for_each), PRE_ORDER))
    {
        printf("TestAVL AVLForEach PRE_ORDER failed at line:%d \n", __LINE__);
    }

    for_each.arr = exp_post_order;
    for_each.i = 0;

    if (0 != AVLForEach(tree, CmpArrInts, (void *)(&for_each), POST_ORDER))
    {
        printf("TestAVL AVLForEach POST_ORDER failed at line:%d \n", __LINE__);
    }

    for (i = 0; i < size; ++i)
    {
        if (array[i] != *(int *)AVLFind(tree, (void *)(array + i)))
        {
            printf("TestAVL AVLFind failed at line:%d at index :%lu\n", __LINE__, i);
            printf("find val :%d\n", *(int *)AVLFind(tree, (void *)(array + i)));
        }
    }

    for (i = 0; i < size; ++i)
    {
        AVLRemove(tree, (void *)(array + i));
    }
    if (0 != AVLSize(tree))
    {
        printf("TestAVL AVLRemove failed at line: %d %lu\n", __LINE__, AVLSize(tree));
    }

    AVLDestroy(tree);
    return;
}

static void TestAVLHeight()
{
    int array[] = {10, 7, 2, 8, 15, 17, 16, 100, 45, 20, 89, 5};
    int arr[sizeof(array) / sizeof(array[0])] = {0};
    size_t size = sizeof(array) / sizeof(array[0]);
    size_t i = 0;
    size_t first_height = 3;
    size_t scond_height = 4;

    avl_t *tree = AVLCreate(Compare);

    if (NULL == tree)
    {
        printf("TestAVL AVLCreate failed %d\n", __LINE__);
    }

    if (1 != AVLIsEmpty(tree))
    {
        printf("TestAVL AVLIsEmpty failed at line: %d\n", __LINE__);
    }

    for (i = 0; i < size - scond_height && !arr[i]; ++i)
    {
        arr[i] = AVLInsert(tree, (void *)(array + i));
    }
    if (i != AVLSize(tree))
    {
        printf("TestAVL AVLInsert failed at line: %d %lu\n", __LINE__, AVLSize(tree));
    }

    if (first_height != AVLHeight(tree))
    {
        printf("TestAVL AVLHeight failed at line:%d \n", __LINE__);
        printf("Expected height: %lu\n", first_height);
        printf("return height: %lu\n", AVLHeight(tree));
    }

    for (i = i; i < size && !arr[i]; ++i)
    {
        arr[i] = AVLInsert(tree, (void *)(array + i));
    }

    if (scond_height != AVLHeight(tree))
    {
        printf("TestAVL AVLHeight failed at line:%d \n", __LINE__);
        printf("Expected height: %lu\n", scond_height);
        printf("return height: %lu\n", AVLHeight(tree));
    }
    if (size != AVLSize(tree))
    {
        printf("TestAVL AVLInsert failed at line: %d %lu\n", __LINE__, AVLSize(tree));
    }

    AVLDestroy(tree);
    return;
}

static void TestRemove()
{
    avl_t *tree = AVLCreate(Compare);
    int arr[] = {10, 8, 15, 17, 16, 7, 2, 100, 45, 18, 20, 89};
    int exp_after_remove[] = {2, 7, 10, 15, 16, 17, 18, 20, 45, 89, 100};
    int exp_after_remove1[] = {2, 7, 10, 15, 16, 17, 18, 20, 45, 89};
    int exp_after_remove2[] = {2, 7, 10, 15, 16, 17, 18, 45, 89};
    int exp_after_remove3[] = {2, 7, 10, 15, 16, 18, 45, 89};
    int exp_after_remove4[] = {2, 7, 10, 15, 16, 45, 89};

    int remove[] = {8, 100, 20, 4, 17, 18};

    size_t arr_size = sizeof(arr) / sizeof(arr[0]);

    size_t i = 0;
    size_t j = 0;

    testfe_t for_each = {0};

    while (i < arr_size)
    {
        AVLInsert(tree, arr + i);
        ++i;
    }

    for_each.arr = exp_after_remove;
    for_each.i = 0;

    AVLRemove(tree, remove + j);
    if (0 != AVLForEach(tree, CmpArrInts, (void *)(&for_each), IN_ORDER))
    {
        printf("TestAVL AVLRemove failed at line:%d \n", __LINE__);
    }

    for_each.arr = exp_after_remove1;
    for_each.i = 0;
    ++j;
    AVLRemove(tree, remove + j);
    if (0 != AVLForEach(tree, CmpArrInts, (void *)(&for_each), IN_ORDER))
    {
        printf("TestAVL AVLRemove failed at line:%d \n", __LINE__);
    }

    for_each.arr = exp_after_remove2;
    for_each.i = 0;
    ++j;
    AVLRemove(tree, remove + j);
    if (0 != AVLForEach(tree, CmpArrInts, (void *)(&for_each), IN_ORDER))
    {
        printf("TestAVL AVLRemove failed at line:%d \n", __LINE__);
    }
    for_each.i = 0;
    ++j;
    AVLRemove(tree, remove + j);
    if (0 != AVLForEach(tree, CmpArrInts, (void *)(&for_each), IN_ORDER))
    {
        printf("TestAVL AVLRemove failed at line:%d \n", __LINE__);
    }

    for_each.arr = exp_after_remove3;
    for_each.i = 0;
    ++j;
    AVLRemove(tree, remove + j);
    if (0 != AVLForEach(tree, CmpArrInts, (void *)(&for_each), IN_ORDER))
    {
        printf("TestAVL AVLRemove failed at line:%d \n", __LINE__);
    }

    for_each.arr = exp_after_remove4;
    for_each.i = 0;
    ++j;
    AVLRemove(tree, remove + j);
    if (0 != AVLForEach(tree, CmpArrInts, (void *)(&for_each), IN_ORDER))
    {
        printf("TestAVL AVLRemove failed at line:%d \n", __LINE__);
    }

    AVLDestroy(tree);

    return;
}

static void TestRemove1()
{
    avl_t *tree = AVLCreate(Compare);
    size_t hights[] = {3, 3, 3, 3, 3, 3, 2, 2, 2, 1};
    int arr[] = {10, 8, 15, 17, 16, 7, 2, 100, 45, 18, 20, 0, 89};
    int remove[] = {8, 100, 20, 0, 10, 17, 16, 7, 2, 45};

    size_t exp_height = 6;
    size_t arr_size = sizeof(arr) / sizeof(int);
    size_t remove_size = sizeof(remove) / sizeof(int);
    size_t i = 0;

    while (i < arr_size)
    {
        AVLInsert(tree, arr + i);
        ++i;
    }

    if (4 != AVLHeight(tree))
    {
        printf("LINE:%d error.\n", __LINE__);
        printf("Expected hight: %lu.\n", exp_height);
        printf("Actual hight: %lu.\n\n", AVLHeight(tree));
    }

    i = 0;

    while (i < remove_size)
    {
        AVLRemove(tree, remove + i);

        if (hights[i] != AVLHeight(tree))
        {
            printf("LINE:%d error.\n", __LINE__);
            printf("Expected hight: %lu.\n", hights[i]);
            printf("Actual hight: %lu.\n\n", AVLHeight(tree));
        }

        ++i;
    }

    AVLDestroy(tree);

    return;
}

/*------------------------------helper func--------------------------------*/

static int Compare(void *data1, void *data2)
{
    return (*(int *)data1 - *(int *)data2);
}

static int CmpArrInts(void *data1, void *data2)
{
    int elem = *(int *)(((testfe_t *)data2)->arr + ((testfe_t *)data2)->i);

    ((testfe_t *)data2)->i += 1;
    return (*(int *)data1 - elem);
}


