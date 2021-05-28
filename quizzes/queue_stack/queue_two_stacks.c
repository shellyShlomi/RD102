#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include "stack.h"

#define STACK_IS_FULL(X) (StackGetCapacity(X) == StackSize(X))
/* implementetion functions */
typedef struct stack_queue stk_queue_t;
int StackQueueEnqueue(stk_queue_t *queue, void *data);
void *StackQueueDequeue(stk_queue_t *queue);
stk_queue_t *StackQueueCreate(size_t capacity);
void StackQDestroy(stk_queue_t *queue);

/* helper functions */
static size_t StackQueueSize(stk_queue_t *queue);
static void StackQueueFillOut(stk_queue_t *queue);


struct stack_queue
{
	stack_t *enter;
	stack_t *out;

};

int main()
{
	stk_queue_t *queue = StackQueueCreate(10);
	int arr[10] = {0};
	size_t arr_size = sizeof(arr) / sizeof(arr[0]);
	int extra_thing = 100000;
	
	size_t i = 0;

	printf("\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		arr[i] = i + 1;
	}

	for (i = 0; i < 7; ++i)
	{
		if (!StackQueueEnqueue(queue, (arr + i)))
		{
			printf("StackQueueEnqueue : %d\n", arr[i]);
		}
		else 
		{
			printf("StackQueueEnqueue faile \n");

		}
	}


	if (!StackQueueEnqueue(queue, (arr + i)))
	{
		printf("StackQueueEnqueue : %d\n", arr[i]);
	}
	else 
	{
		printf("StackQueueEnqueue faile \n");

	}

	++i;

	if (!StackQueueEnqueue(queue, (arr + i)))
	{
		printf("StackQueueEnqueue : %d\n", arr[i]);
	}
	else 
	{
		printf("StackQueueEnqueue faile \n");

	}
	
	if (!StackQueueEnqueue(queue, &extra_thing))
	{
		printf("StackQueueEnqueue : %d\n", extra_thing);
	}
	else 
	{
		printf("StackQueueEnqueue faile \n");

	}

	printf("\n");

	printf("Stack Queue Size : %lu\n", StackQueueSize(queue));
	
	printf("\n");

	printf("StackQueueDequeue : %d\n", *((int *)StackQueueDequeue(queue)));

	printf("\n");

	printf("Stack Queue Size : %lu\n", StackQueueSize(queue));

	printf("\n");
	

	for (i = 0; 0 < StackQueueSize(queue); ++i)
	{
		printf("StackQueueDequeue : %d\n", *((int *)StackQueueDequeue(queue)));
	}

	printf("\n");

	printf("Stack Queue Size : %lu\n", StackQueueSize(queue));

	StackQDestroy(queue);

	return (0);
}

/*------------------------------implementetion--------------------------------*/

int StackQueueEnqueue(stk_queue_t *queue, void *data)
{
	assert(queue);
	
	if (!STACK_IS_FULL(queue->enter))
	{
		StackPush(queue->enter, data);
		return (EXIT_SUCCESS);
	}
	
	if (STACK_IS_FULL(queue->enter) && StackIsEmpty(queue->out))
	{
		StackQueueFillOut(queue);
		
		StackPush(queue->enter, data);
		return (EXIT_SUCCESS);
	}

	return (EXIT_FAILURE);
}


void *StackQueueDequeue(stk_queue_t *queue)
{
	void *data = NULL;

	assert(queue);
	
	if (!StackIsEmpty(queue->out))
	{
		data = StackPeek(queue->out);
		StackPop(queue->out);

		return (data);
	}
	
	if (StackIsEmpty(queue->out) && !StackIsEmpty(queue->enter))
	{
		StackQueueFillOut(queue);
		
		data = StackPeek(queue->out);
		StackPop(queue->out);
	}

	return (data);
}

/*------------------------------helper functions------------------------------*/

stk_queue_t *StackQueueCreate(size_t capacity)
{
	stk_queue_t *queue = NULL;	
	stack_t *enter = NULL;
	stack_t *out = NULL;

	queue = (stk_queue_t *)malloc(sizeof(stk_queue_t));
	
	if (NULL == queue)
	{
		return (NULL);
	}

	enter = StackCreate(capacity / 2);
	if (NULL == enter)
	{
		free(queue);
		return (NULL);
	}
	
	out = StackCreate(capacity / 2);
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

void StackQDestroy(stk_queue_t *queue)
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


static void StackQueueFillOut(stk_queue_t *queue)
{
	assert(queue);

	while (!StackIsEmpty(queue->enter))
	{
			StackPush(queue->out, StackPeek(queue->enter));
			StackPop(queue->enter);
	}

	return;
}


static size_t StackQueueSize(stk_queue_t *queue)
{
	assert(queue);
	assert(queue->enter);
	assert(queue->out);
	
	return (StackSize(queue->enter) + StackSize(queue->out));
}
