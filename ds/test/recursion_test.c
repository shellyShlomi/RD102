#include <stdio.h>  /* printf */
#include <stdlib.h> /* exit status */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /* strlen */

#include "recursion.h"

#define UNUSED(x) (void)(x)
#define SIZE 10

struct node
{
    void *data;
    struct node *next;
};

node_t *Flip(node_t *head);

/*---------------test func-----------------*/

static void Test();
static void TestFibR();
static void TestFibI();
static void TestFlip();
static void TestStrLen();
static void TestStrCmp();
static void TestStackSort();
static void TestStrCpy();
static void TestStrCat();
static void TestStrStr();

/*------------------------------test for impl---------------------------------*/

int main()
{
    Test();

    return (0);
}

static void Test()
{
    TestFibR();
    TestFibI();
    TestFlip();
    TestStrLen();
    TestStrCmp();
    TestStackSort();
    TestStrCpy();
    TestStrCat();
    TestStrStr();

    return;
}

static void TestFibR()
{
    int fib_arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    int index_arr[] = {0, 1, 2, 3, 4, 5};

    size_t i = 0;
    size_t size_valid = sizeof(index_arr) / sizeof(index_arr[0]);

    while (i < size_valid)
    {
        if (RecursiveFibonacci(index_arr[i]) != fib_arr[index_arr[i]])
        {
            printf("RecursiveFibonacci failed at index %ld at line %d\n", i, __LINE__);
        }

        ++i;
    }
    return;
}

static void TestFibI()
{
    int fib_arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    int index_arr[] = {0, 1, 2, 3, 4, 5};

    size_t i = 0;
    size_t size_valid = sizeof(index_arr) / sizeof(index_arr[0]);

    while (i < size_valid)
    {
        if (IterativeFibonacci(index_arr[i]) != fib_arr[index_arr[i]])
        {
            printf("IterativeFibonacci failed at index %ld at line %d\n", i, __LINE__);
        }

        ++i;
    }

    return;
}

static void TestFlip()
{

    node_t node_1 = {0};
    node_t node_2 = {0};
    node_t node_3 = {0};
    node_t node_4 = {0};

    node_t *head = &node_1;

    node_1.next = &node_2;
    node_2.next = &node_3;
    node_3.next = &node_4;
    node_4.next = NULL;

    if (FlipList(head) != head)
    {
        printf("FlipList failed at line %d\n", __LINE__);
    }

    return;
}

static void TestStrLen()
{
    char *str[] = {"", "longString", "s", "LongString", "LongString"}; /*to test an empty string*/
    size_t size = 5;
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        if (strlen(str[i]) != StrLen(str[i]))
        {
            printf("StrLen Failed index %ld at line %d\n", i, __LINE__);
        }
    }

    return;
}

static void TestStrCmp()
{
    char *str[] = {"", "longString", "s", "LongString", "LongString"}; /*to test an empty string*/
    size_t size = 5;
    size_t i = 0;

    for (i = 0; i < size - 1; ++i)
    {
        if ((strcmp(str[i], str[i + 1]) > 0 && StrCmp(str[i], str[i + 1]) < 0) ||
            (strcmp(str[i], str[i + 1]) < 0 && StrCmp(str[i], str[i + 1]) > 0) ||
            (strcmp(str[i], str[i + 1]) == 0 && StrCmp(str[i], str[i + 1]) != 0) ||
            (strcmp(str[i], str[i + 1]) != 0 && StrCmp(str[i], str[i + 1]) == 0))
        {
            printf("StrCmp Failed index %ld at line %d\n", i, __LINE__);
        }
    }

    return;
}

static void TestStackSort()
{
    stack_t *stack = StackCreate(15);
    size_t i = 0;
    int arr[] = {10, 12, 6, -4, 10, 13};
    int arr_cpy[] = {13, 12, 10, 10, 6, -4};
    size_t size = sizeof(arr) / sizeof(int);

    for (i = 0; i < size; ++i)
    {
        StackPush(stack, (void *)(arr + i));
    }
    StackSort(stack);

    for (i = 0; i < size; ++i)
    {
        if (arr_cpy[i] != *(int *)StackPeek(stack))
        {
            printf("StackSort Failed index %ld at line %d\n", i, __LINE__);
        }
        StackPop(stack);
    }

    StackDestroy(stack);
}

static void TestStrCpy()
{
    int compre_my_function = 0;            /*to save the value from StrCpy*/
    int compre_original = 0;               /*to save the value from strcpy*/
    const char str[] = "";                 /*to test empty(only '\0') string as source*/
    char str_original[] = "sgvrsfbhgdf";   /*destanetion for test empty(only'\0')*/
    char str_my_funcion[] = "sgvrsfbhgdf"; /*destanetion for test empty('\0')*/
    /*destanetion arrays*/
    char result_my_function[][1000] = {"", "world", "Shelly"};
    char result_original[][1000] = {"", "world", "Shelly"};
    /*source array*/
    const char array_source[][7] = {"Shelly", "Sv", ""};

    size_t i = 0;

    /*the size of the array os strings*/
    size_t size = sizeof(result_my_function) / (sizeof(result_my_function[i]));

    /* test the copying of the source array into destanetion arrays*/
    while (i < size)
    {
        assert(StrCpy(result_my_function[i], array_source[i]));
        assert(strcpy(result_original[i], array_source[i]));

        compre_my_function = strcmp(result_my_function[i], array_source[i]);

        compre_original = strcmp(result_original[i], array_source[i]);

        if (compre_my_function != compre_original)
        {
            printf("StrCpy Failed index %ld at line %d\n", i, __LINE__);
        }
        ++i;
    }
    /* test the copying of empty(only '\0') string as source*/
    if (*(StrCpy(str_my_funcion, str)) != (*(strcpy(str_original, str))))
    {
        printf("StrCpy Failed at line %d\n", __LINE__);
    }

    return;
}

static void TestStrCat()
{
    /*destanetion arrays*/
    char result_my_function[][1000] = {"dfghdf\0hf", "hello ", "Shelly", ""};
    char result_original[][1000] = {"dfghdf\0hf", "hello ", "Shelly", ""};
    /*source array*/
    const char array_source[][10] = {"Shelly", "world", " shlomi", "1 2 3 4 5"};

    size_t size = sizeof(array_source) / sizeof(array_source[0]);

    while (0 < size)
    {
        if (0 != strcmp(StrCat(result_my_function[size - 1],
                               array_source[size - 1]),
                        strcat(result_original[size - 1],
                               array_source[size - 1])))
        {
            printf("StrCat Failed index %ld at line %d\n", size, __LINE__);
        }
        --size;
    }
    return;
}

static void TestStrStr()
{
    char *compre_my_function = NULL; /*to save the pointer from StrStr*/
    char *compre_original = NULL;    /*to save the pointer from strcpy*/
    const char array_source[][20] = {"hhhelhhhhellhh", "lo shloo\0mi"};

    char array_needle[][4] = {"ell", "loo", ""};

    size_t size = sizeof(array_needle) / sizeof(array_needle[0]);

    while (0 < size)
    {
        assert(strstr(array_source[size - 1], array_needle[size - 1]));
        assert(StrStr(array_source[size - 1], array_needle[size - 1]));

        if (0 != StrStr(array_source[size - 1], array_needle[size - 1]) -
                     strstr(array_source[size - 1], array_needle[size - 1]))
        {
            printf("StrCat Failed index %ld at line %d\n", size, __LINE__);
        }
        --size;
    }

    compre_my_function = StrStr("aaaa", "b");
    compre_original = strstr("aaaa", "b");

    if (0 != (compre_original - compre_my_function))
    {
        printf("StrCat Failed index %ld at line %d\n", size, __LINE__);
    }
    return;
}

/*------------------------------helper funcs---------------------------------*/

node_t *Flip(node_t *head)
{
    node_t *flip = head;
    node_t *go = NULL;
    node_t *temp = NULL;

    assert(NULL != head);

    go = head->next;
    head->next = NULL;

    if (NULL == go)
    {
        return (head);
    }

    while (NULL != go->next)
    {
        temp = go->next;
        go->next = flip;
        flip = go;
        go = temp;
    }

    go->next = flip;

    return (go);
}
