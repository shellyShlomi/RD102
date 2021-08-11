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
void SortStack(stack_t *s1, stack_t *s2);

/*------------------------------test for impl---------------------------------*/
int main()
{
	TestSortStack();

	return (0);
}

static void TestSortStack()
{
	int arr[] = {101, 100, 2, 4, -2, 1, -3, 5, 6, 9};
	int sort_arr[] = {100, 2, 4, -2, 1, -3, 5, 6, 9};
	size_t size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;

	stack_t *stack = StackCreate(size);
	stack_t *stackush = StackCreate(size);
	for (i = 0; i < size; i++)
	{
		StackPush(stack, arr + i);
	}
	for (i = 0; i < size; i++)
	{
		printf(" arr idx:%lu, val : %d\n", i, arr[i]);
	}

	SortStack(stack, stackush);
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
	StackDestroy(stackush);
	return;
}

void SortStack(stack_t *s1, stack_t *s2)
{
	int *peek1 = 0;
	int *peek2 = 0;
	int *max1 = 0;
	long i = 0;

	max1 = (int *)StackPeek(s1);
	StackPop(s1);

	while (!StackIsEmpty(s1))
	{

		peek1 = (int *)StackPeek(s1);
		if (*max1 >= *peek1)
		{
			i = 0;
			StackPop(s1);

			while ((!StackIsEmpty(s2)) && (*(peek2 = (int *)StackPeek(s2)) > *peek1))
			{
				StackPop(s2);
				StackPush(s1, peek2);
				++i;
			}
			StackPush(s2, peek1);

			while (i > 0)
			{
				peek1 = (int *)StackPeek(s1);
				StackPush(s2, peek1);
				StackPop(s1);
				--i;
			}

			continue;
		}
		StackPush(s2, max1);
		StackPop(s1);

		max1 = peek1;
	}

	StackPush(s1, max1);
	while (!StackIsEmpty(s2))
	{
		StackPush(s1, StackPeek(s2));
		StackPop(s2);
	}

	return;
}
