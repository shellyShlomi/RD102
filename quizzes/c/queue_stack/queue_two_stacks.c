#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include "stack.h"

#define STACK_IS_FULL(X) (StackGetCapacity(X) == StackSize(X))
#define SIZE 12

/*---------------impl func-----------------*/
typedef struct stack_queue min_stack_t;
int StackQueueEnqueue(min_stack_t *queue, void *data);
void *StackQueueDequeue(min_stack_t *queue);


/*---------------helper func---------------*/
static size_t StackQueueSize(min_stack_t *queue);
static void StackQueueFillOut(min_stack_t *queue);
static void StackQueueFillEnter(min_stack_t *queue);
static min_stack_t *StackQueueCreate(size_t capacity);
static void StackQDestroy(min_stack_t *queue);

/*---------------test func-----------------*/
void TestOne();
void TestTwo();

struct stack_queue
{
	stack_t *enter;
	stack_t *out;

};


/*------------------------------test for impl---------------------------------*/
int main()
{
	TestOne();
	TestTwo();
	
	return (0);
}



void TestOne()
{
	min_stack_t *queue = StackQueueCreate(SIZE - 2);
	int arr[SIZE] = {0};
	size_t arr_size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		arr[i] = i + 1;
	}

	for (i = 0; i < SIZE / 2; ++i)
	{
		if (StackQueueEnqueue(queue, (arr + i)))
		{
			printf("StackQueueEnqueue error at line: %d\n", __LINE__);
		}
		
	}
	
	if (SIZE / 2 != StackQueueSize(queue))
	{
		printf("error at line: %d\n", __LINE__);
	}

	for (i = 0; i < SIZE / 3; ++i)
	{
		if (arr[i] != *((int *)StackQueueDequeue(queue)))
		{
			printf("StackQueueDequeue error at line: %d\n", __LINE__);
		}
	}

	for (i = SIZE / 2; (SIZE - 2) != StackQueueSize(queue); ++i)
	{
		if (StackQueueEnqueue(queue, (arr + i)))
		{
			printf("StackQueueEnqueue error at line: %d\n", __LINE__);
		}
		
	}

	if (SIZE - 2 != StackQueueSize(queue))
	{
		printf("error at line: %d\n", __LINE__);
	}

	for (i = 0; 0 < StackQueueSize(queue); ++i)
	{
		StackQueueDequeue(queue);
	}

	if (0 != StackQueueSize(queue))
	{
		printf("error at line: %d\n", __LINE__);
	}

	StackQDestroy(queue);
	
	return;

}

void TestTwo()
{

	min_stack_t *queue = StackQueueCreate(SIZE - 2);
	int arr[SIZE] = {0};
	size_t arr_size = sizeof(arr) / sizeof(arr[0]);
	
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
		arr[i] = i + 1;
	}

	i = 0;
	if (StackQueueEnqueue(queue, (arr + i)))
	{
		printf("StackQueueEnqueue error at line: %d\n", __LINE__);
	}
	
	++i;

	if (StackQueueEnqueue(queue, (arr + i)))
	{
		printf("StackQueueEnqueue error at line: %d\n", __LINE__);
	}
	
	if (2 != StackQueueSize(queue))
	{
		printf("error at line: %d\n", __LINE__);
	}
	
	i = 0;
	
	if (arr[i] != *((int *)StackQueueDequeue(queue)))
	{
		printf("StackQueueDequeue error at line: %d\n", __LINE__);
	}

	for (i = 2; i < 11; ++i)
	{
		if (StackQueueEnqueue(queue, (arr + i)))
		{
			printf("StackQueueEnqueue error at line: %d\n", __LINE__);
		}
	}

	if (SIZE - 2 != StackQueueSize(queue))
	{
		printf("error at line: %d\n", __LINE__);
	}

	for (i = 0; 0 < StackQueueSize(queue); ++i)
	{
		StackQueueDequeue(queue);
	}

	if (0 != StackQueueSize(queue))
	{
		printf("error at line: %d\n", __LINE__);
	}

	StackQDestroy(queue);
	
	return;
}
/*------------------------------implementetion--------------------------------*/

int StackQueueEnqueue(min_stack_t *queue, void *data)
{
	assert(queue);
	
	if (!STACK_IS_FULL(queue->enter))
	{
		StackPush(queue->enter, data);
		return (EXIT_SUCCESS);
	}

	return (EXIT_FAILURE);
}


void *StackQueueDequeue(min_stack_t *queue)
{
	void *data = NULL;

	assert(queue);
	
	if (!StackIsEmpty(queue->enter))
	{
		StackQueueFillOut(queue);

		data = StackPeek(queue->out);
		StackPop(queue->out);

		StackQueueFillEnter(queue);
	}

	return (data);
}

/*------------------------------helper functions------------------------------*/

static min_stack_t *StackQueueCreate(size_t capacity)
{
	min_stack_t *queue = NULL;	
	stack_t *enter = NULL;
	stack_t *out = NULL;

	queue = (min_stack_t *)malloc(sizeof(min_stack_t));
	
	if (NULL == queue)
	{
		return (NULL);
	}

	enter = StackCreate(capacity);
	if (NULL == enter)
	{
		free(queue);
		return (NULL);
	}
	
	out = StackCreate(capacity );
	if (NULL == out)
	{
		StackDestroy(queue->enter);
		queue->enter = NULL;
		
		free(queue);
		return (NULL);
	}
	queue->enter = enter;
	queue->out = out;
	
	return (queue);	
}

static void StackQDestroy(min_stack_t *queue)
{
	assert(queue);
	assert(queue->enter);
	assert(queue->out);

	StackDestroy(queue->enter);
	queue->enter = NULL;
	
	StackDestroy(queue->out);
	queue->out = NULL;

	free(queue);
}


static void StackQueueFillOut(min_stack_t *queue)
{
	assert(queue);

	while (!StackIsEmpty(queue->enter))
	{
			StackPush(queue->out, StackPeek(queue->enter));
			StackPop(queue->enter);
	}

	return;
}

static void StackQueueFillEnter(min_stack_t *queue)
{
	assert(queue);

	while (!StackIsEmpty(queue->out))
	{
			StackPush(queue->enter, StackPeek(queue->out));
			StackPop(queue->out);
	}

	return;
}

static size_t StackQueueSize(min_stack_t *queue)
{
	assert(queue);
	assert(queue->enter);
	assert(queue->out);
	
	return (StackSize(queue->enter) + StackSize(queue->out));
}





