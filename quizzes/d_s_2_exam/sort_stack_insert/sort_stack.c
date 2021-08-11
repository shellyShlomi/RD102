/*  Developer: Shelly Shlomi;									*/
/*  Status:Approved;											*/
/*  Date Of Creation:08.04.21;									*/
/*  Date Of Approval:09.04.21;									*/
/*  Approved By: roman											*/
/*  Description: stack data structure 							*/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <stdio.h>

#include "stack.h"

#define UNUSED(x) (void)(x)
static void TestSortStack();
void SortStackInsert(stack_t *s1, int *num);

/*------------------------------test for impl---------------------------------*/
int main()
{
	TestSortStack();

	return (0);
}

static void TestSortStack()
{
	int arr[] = {101, 100, 2, 4, -2, 1, -3, 5, 6, 9};
	size_t size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;

	stack_t *stack = StackCreate(size);
	for (i = 0; i < size; i++)
	{
		SortStackInsert(stack, arr + i);
	}
	for (i = 0; i < size; i++)
	{
		printf(" arr idx:%lu, val : %d\n", i, arr[i]);
	}

	for (i = 0; i < size; i++)
	{
		printf(" arr idx:%lu, val : %d\n", i, arr[i]);
	}

	for (i = 0; !StackIsEmpty(stack); i++)
	{

		printf("idx:%lu, val : %d\n", i, *(int *)StackPeek(stack));
		StackPop(stack);
	}

	StackDestroy(stack);
	return;
}

void SortStackInsert(stack_t *s1, int *num)
{
	int *peek = 0;

	if (StackIsEmpty(s1) || *(peek = StackPeek(s1)) < *num)
	{
		StackPush(s1, num);
		return;
	}

	StackPop(s1);
	SortStackInsert(s1, num);
	StackPush(s1, peek);
	
	return;
}
