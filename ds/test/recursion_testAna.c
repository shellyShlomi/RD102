#include <stdio.h>
#include <string.h>

#include "recursion.h"

struct node
{
    void *data;
    struct node *next;
};

static void TestFibRec();
static void TestFibIter();
static void TestFlip();
static void TestFlip2();
static void TestFlip3();
static void TestSortStack();
static void TestStrLen();
static void TestStrCmp();
static void TestStrCat();
static void TetsStrCpy();
static void TestStrStr();
static void TestFibBigNumbers();

static int GetData(node_t *node);

int main()
{
    TestFibRec();
    TestFibIter();
    TestSortStack();
    TestStrLen();
	TetsStrCpy();
	TestStrCat();
	TestStrStr();
 TestFlip();
TestFlip2();
TestFlip3();

    return 0;
}


static void TestFibRec()
{
	int fib_arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55,
								 89, 144, 233, 377, 610, 987, 1597}; 
	
	size_t  size = sizeof(fib_arr) / sizeof(fib_arr[0]);
	size_t i = 0;
	
	while (i < size)
	{	
		if (RecursiveFibonacci(i) != fib_arr[i])
		{
			printf("Error in test - RecursiveFibonacci!\n");
			printf("Failed in index %ld\n",i);
			printf("Actual result is: %d \n", RecursiveFibonacci(i));
			printf("Expected result is: %d \n", fib_arr[i]);			
		}
		++i;
	}
	
	return ;
}


static void TestFibIter()
{
	int fib_arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55,
								 89, 144, 233, 377, 610, 987, 1597}; 
	
	size_t  size = sizeof(fib_arr) / sizeof(fib_arr[0]);
	size_t i = 0;
	
	while (i < size)
	{	
		if (IterativeFibonacci(i) != fib_arr[i])
		{
			printf("Error in test - IterativeFibonacci!\n");
			printf("Failed in index %ld\n",i);
			printf("Actual result is: %d \n", IterativeFibonacci(i));
			printf("Expected result is: %d \n\n", fib_arr[i]);	
		}
		++i;
	}
	
	return ;
}

static void TestFibBigNumbers()
{
	int num[] = {0,10,20,40};
	size_t exp[] = {0,55,6765,102334155};

	size_t  size = sizeof(num) / sizeof(num[0]);
	size_t i = 0;
	size_t res = 0;

	while (i < size)
	{	
		res = IterativeFibonacci(num[i]);
		
		if (res != exp[i])
		{
			printf("Error in test fib- Iterative!\n");
			printf("Failed in index %ld\n",i);
			printf("Actual result is: %ld \n", res);
			printf("Expected result is: %ld \n\n", exp[i]);	
		}
		
		res = RecursiveFibonacci(num[i]);
		
		if (res != exp[i])
		{
			printf("Error in test fib- Recursive!\n");
			printf("Failed in index %ld\n",i);
			printf("Actual result is: %ld \n", res);
			printf("Expected result is: %ld \n", exp[i]);			
		}
		++i;
	}
	
	return ;

}

static void TestFlip()
{	
	int expected[] = {5, 4, 3, 2, 1};
	node_t *result = NULL;
	
	node_t last = {(void *)5, NULL};
	node_t x = {(void *)4, NULL};
	node_t y = {(void *)3, NULL};
	node_t v = {(void *)2, NULL};
	node_t list = {(void *)1, NULL};

	size_t i = 0;
	
	x.next = &last;
	y.next = &x;
	v.next = &y;
	list.next = &v;
	
	result = FlipList(&list);
	
	while (NULL != result)
	{
		if (expected[i] != GetData(result))
		{
			printf("ERROR - Flip odd number of nodes!\n");
			break;
		}
		++i;
		result = result->next;
	}
	
	return;
}

/* revers list with even number of nodes */
static void TestFlip2()
{	
	int expected[] = {4, 3, 2, 1};
	node_t *result = NULL;
	
	node_t last = {(void *)4, NULL};
	node_t y = {(void *)3, NULL};
	node_t v = {(void *)2, NULL};
	node_t list = {(void *)1, NULL};
	
	size_t i = 0;

	y.next = &last;
	v.next = &y;
	list.next = &v;
		
	result = FlipList(&list);
	
	while (NULL != result)
	{
		if (expected[i] != GetData(result))
		{
			printf("ERROR - Flip even number of nodes!\n");
			break;
		}
		++i;
		result = result->next;
	}
	
	return;
}
static void TestFlip3()
{	
	node_t *result = NULL;
	node_t list = {(void *)1, NULL};
		
	result = FlipList(&list);
	
	if (1 != GetData(result))
	{
		printf("ERROR - Flip of one node!\n");
	}
	
	return;
}

static int GetData(node_t *node)
{
	return (int)(long)(int *)(node->data);	
}



static void TestSortStack()
{
    size_t capacity = 55;
    stack_t *stack = StackCreate(capacity);

    int data_int_elements[] = {10, 2, 22, 3, 8, 1, 4, 4, 22};
    int expected[] = {22, 22, 10, 8, 4, 4, 3, 2, 1};

    size_t size = sizeof(data_int_elements) / sizeof(data_int_elements[0]);
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        StackPush(stack, (void *)(data_int_elements + i));
    }

    StackSort(stack);

    i = 0;

    while (!StackIsEmpty(stack))
    {
        if (expected[i] != (*(int *)StackPeek(stack)))
        {
            printf("TEST FAILED at line %d\n", __LINE__);
            printf("actual = %d\t", (*(int *)StackPeek(stack)));
            printf("expected = %d\t", expected[i]);
        }

        StackPop(stack);
        ++i;
    }

    StackDestroy(stack);

    return;
}

static void TestStrLen()
{
    char *strings[] = { "anna", "anna pest", "hello world", "abcdefghigklmn"};
    size_t size  = sizeof(strings) / sizeof((strings[0]));
    size_t i = 0;

    while (i < size)
    {
       if (strlen(strings[i]) != StrLen(strings[i]))
        {
            printf("StrLen Failed index %ld at line %d\n", i, __LINE__);
        }
        ++i;
    }

    return;
}

static void TetsStrCpy()
{
	char *arr[] = {"llowo", "", "bbsd", "llasa"};
	char actual[50] = "hello";
	char expected[50] = "hello";

	char *actual_res = NULL;
	char *expected_res = NULL;


	const size_t size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;
	
	for (i = 0; i < size; i++)
	{	
		actual_res = StrCpy(actual, arr[i]);
		expected_res = strcpy(expected, arr[i]);
		
		if (0 != strcmp(actual_res, expected_res))
		{
			printf("Test StrCpy Failed! \n");
			printf("Actual string:   %s.\n",actual);
			printf("Expected string: %s.\n\n",expected);
		
		}
	}
	return;
}


static void TestStrCat()
{
	char *arr[] = {"llowo", "", "bbsd", "llasa"};
	char actual[50] = "hel\0lo";
	char expected[50] = "hel\0lo";
	
	char *actual_res = NULL;
	char *expected_res = NULL;

	const size_t size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;
	
	for (i = 0; i < size; i++)
	{	
		actual_res = StrCat(actual, arr[i]);
		expected_res = strcat(expected, arr[i]);
		
		if (0 != strcmp(actual_res, expected_res))
		{
			printf("Test StrCat Failed!\n");
			printf("Actual string:    %s.\n",actual);
			printf("Expected string:  %s.\n\n",expected);
		
		}
	}
	return;

}

static void TestStrStr()
{
	char *arr_of_strings[] = {"helloworld", "hellhelloworld", 
							  "aaabbbbsdsds", "Hella", "dsada", "", "aaa"};
	char *arr_of_needles[] = {"llowo", "hello", "bbsd", "llasa",
														 "adabc", "", "n"};
	char *actual = NULL;
	char *expected = NULL;
	const size_t size = sizeof(arr_of_strings) / sizeof(arr_of_strings[0]);
	size_t i = 0;


	for (i = 0; i < size; i++)
	{	
		actual = StrStr(arr_of_strings[i], arr_of_needles[i]);
		expected = strstr(arr_of_strings[i], arr_of_needles[i]);
		if (actual != expected)
		{
			printf("Test Failed at index %ld!\n", i);
			printf("Actual address: %p.\n",actual);
			printf("Expected address:  %p.\n\n",expected);
			
		}
	}
	
	return;
}