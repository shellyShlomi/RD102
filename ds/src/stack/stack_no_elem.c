
/*  Developer: Shelly Shlomi;									*/
/*  Status:Approved;											*/
/*  Date Of Creation:09.04.21;									*/
/*  Date Of Approval:09.04.21;									*/
/*  Approved By: nir											*/
/*  Description: stack data structure 							*/

#include <stdlib.h>	/* malloc */
#include <assert.h> /* assert */

#include "stack.h"

#define UNUSED(x) (void)(x)
#define ARR_OFFSET 2

struct stack
{
    size_t top;
    size_t capacity;
};
 
/* O(1) time, O(n)space */
stack_t *StackCreate(size_t capacity)
{
	stack_t *s = (stack_t *)malloc(sizeof(stack_t) + capacity * sizeof(void *));
	
	if (NULL == s)
	{
		return NULL; 
	}

	s->top = ARR_OFFSET;
	s->capacity = capacity;

	return s;
}

/* O(1) time & space */
void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	
	free(stack);

	return ;
}

/* O(1) time & space */
size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
		
	return stack->top - ARR_OFFSET;
}

/* O(1) time & space */
int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);

	return !(stack->top - ARR_OFFSET);
}

/* O(1) time & space */
size_t StackGetCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	
	return stack->capacity;
}

/* O(1) time & space */
void StackPush(stack_t *stack, void *data)
{
	assert(NULL != stack);
	assert(NULL != data);
	assert(stack->capacity != stack->top - ARR_OFFSET);

	*((void **)stack + stack->top) = data;
	
	++(stack->top);

	return ;
}

/* O(1) time & space */
void StackPop(stack_t *stack)
{

	assert(NULL != stack);
	assert(2 != stack->top);
	
	--(stack->top);

	return ;
}

/* O(1) time & space */
void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	
	return *((void **)stack + stack->top - 1);
}

