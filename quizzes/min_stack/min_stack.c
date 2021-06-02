#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include "stack.h"

#define STACK_IS_FULL(X) (StackGetCapacity(X) == StackSize(X))
#define SIZE 12

/*---------------impl func-----------------*/
typedef struct min_stack min_stack_t;
void *GetMinVal(min_stack_t *stack);

/*---------------helper func---------------*/
static min_stack_t *MinStackCreate(size_t capacity);
static void MinStackDestroy(min_stack_t *stack);
static int MinStackPush(min_stack_t *stack, void *data);
static void MinStackPop(min_stack_t *stack);

/*---------------test func-----------------*/

static void TestMinStack();


struct min_stack
{
	stack_t *ms_data;
	stack_t *ms_min_vals;

};


/*------------------------------test for impl---------------------------------*/
int main()
{
	TestMinStack();
	
	return (0);
}

static void TestMinStack()
{
    int arr1[] = {100, 2, 4, -2, 1, -3, 5, 6, 9};
    size_t size = sizeof(arr1) / sizeof(arr1[0]);
    size_t i = 0;

    min_stack_t *mstack = MinStackCreate(size);

    for (i = 0; i < size; ++i)
    {
       MinStackPush(mstack, (void *)(arr1 + i));
    }

    if (-3 != *(int *)GetMinVal(mstack))
    {
        printf("GetMinVal function failed at line: %d\n", __LINE__);
    }

    MinStackPop(mstack);
    MinStackPop(mstack);
    MinStackPop(mstack);
    MinStackPop(mstack);

    if (-2 != *(int *)GetMinVal(mstack))
    {
        printf("GetMinVal function failed at line: %d\n", __LINE__);
    }

    MinStackPop(mstack); 
    MinStackPop(mstack);

    if (2 != *(int *)GetMinVal(mstack))
    {
        printf("GetMinVal function failed at line: %d\n", __LINE__);
    } 

    MinStackPop(mstack); 
    MinStackPop(mstack);

    if (100 != *(int *)GetMinVal(mstack))
    {
        printf("GetMinVal function failed at line: %d\n", __LINE__);
    }

	MinStackDestroy(mstack);
	return;
}
/*------------------------------implementetion--------------------------------*/
void *GetMinVal(min_stack_t *stack)
{
	assert(stack); 
	assert(!StackIsEmpty(stack->ms_min_vals));
	
	return (StackPeek(stack->ms_min_vals));
}

/*------------------------------helper functions------------------------------*/

static int MinStackPush(min_stack_t *stack, void *data)
{
	assert(stack); 
	assert(!STACK_IS_FULL(stack->ms_data));
	
	if (!StackIsEmpty(stack->ms_data) && *(int *)StackPeek(stack->ms_min_vals) > *(int *)data)
	{
		StackPush(stack->ms_min_vals, data);
	}
	else if(StackIsEmpty(stack->ms_data))
	{
		StackPush(stack->ms_min_vals, data);
	}
	
	StackPush(stack->ms_data, data);

	return (EXIT_SUCCESS);
}

static void MinStackPop(min_stack_t *stack)
{
	assert(stack); 
	assert(!StackIsEmpty(stack->ms_data));
	
	if (*(int *)StackPeek(stack->ms_min_vals) == *(int *)StackPeek(stack->ms_data))
	{
		StackPop(stack->ms_min_vals);
	}
	StackPop(stack->ms_data);

	return;
}

static min_stack_t *MinStackCreate(size_t capacity)
{
	min_stack_t *stack = NULL;	
	stack_t *ms_data = NULL;
	stack_t *ms_min_vals = NULL;

	stack = (min_stack_t *)malloc(sizeof(min_stack_t));
	
	if (NULL == stack)
	{
		return (NULL);
	}

	ms_data = StackCreate(capacity);
	if (NULL == ms_data)
	{
		free(stack);
		return (NULL);
	}
	
	ms_min_vals = StackCreate(capacity );
	
	if (NULL == ms_min_vals)
	{
		StackDestroy(stack->ms_data);
		stack->ms_data = NULL;
		
		free(stack);
		return (NULL);
	}
	stack->ms_data = ms_data;
	stack->ms_min_vals = ms_min_vals;
	
	return (stack);	
}
static void MinStackDestroy(min_stack_t *stack)
{
	assert(stack);
	assert(stack->ms_data);
	assert(stack->ms_min_vals);

    StackDestroy(stack->ms_data);
    StackDestroy(stack->ms_min_vals);

    stack->ms_data = NULL;
    stack->ms_min_vals = NULL;

    free(stack);
	stack = NULL;
    return;
}



