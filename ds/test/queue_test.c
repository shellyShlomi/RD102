#include <stdio.h> /* printf */
#include <stdlib.h> /* exit status */

#include "queue.h"

static int QueueManager();

int main()
{

	QueueManager();

	return EXIT_SUCCESS;
}

static int QueueManager()
{
	int arr[] = {5, 4, 3, 2, 1};
	size_t i = 0;
	size_t size = sizeof(arr) / sizeof(arr[0]);
	int err = 0;
	queue_t *dest = NULL;	
	queue_t *queue = QueueCreate();
	
	if (NULL == queue)
	{
		printf("QueueCreate error at line: %d\n", __LINE__);
		queue = NULL;
		
		return EXIT_FAILURE; 
	}
	
	if (!(QueueIsEmpty(queue)))
	{
		printf("QueueIsEmpty error at line: %d\n", __LINE__);
	}

	for (i = 0; i < size; ++i, err = 0)
	{
		err = QueueEnqueue(queue, (void *)&arr[i]);
			
		if (err)
		{
			printf("QueueEnqueue error at line: %d\n", __LINE__);
		}
	}
	
	if (size != (QueueSize(queue)))
	{
		printf("QueueSize error at line: %d\n", __LINE__);
	}
	
	for (i = 0; i < size; ++i)
	{
		if (arr[i] != *(int *)QueuePeek(queue))
		{
			printf("QueuePeek or QueueDequeue error at line: %d\n", __LINE__);
		}
		
		QueueDequeue(queue);
	}
	
	dest = QueueCreate();
	
	if (NULL == dest)
	{
		printf("QueueCreate error at line: %d\n", __LINE__);
		dest = NULL;
		
		return EXIT_FAILURE; 
	}

	for (i = 0; i < size; ++i, err = 0)
	{
		err = QueueEnqueue(dest, (void *)&arr[i]);
			
		if (err)
		{
			printf("QueueEnqueue error at line: %d\n", __LINE__);
		}
	}
	
	QueueAppend(dest, queue);
	
	if (!QueueIsEmpty(queue))
	{
		printf("QueueAppend error at line: %d\n", __LINE__);
	}

	if (QueueIsEmpty(dest))
	{
		printf("QueueAppend error at line: %d\n", __LINE__);
	}

	if ((size) != (QueueSize(dest)))
	{
		printf("QueueSize error at line: %d\n", __LINE__);
	}
	
	/* append with empty src */
	QueueAppend(dest, queue);
	
	if (!(QueueIsEmpty(queue)))
	{
		printf("QueueAppend error at line: %d\n", __LINE__);
	}

	if (QueueIsEmpty(dest))
	{
		printf("QueueAppend error at line: %d\n", __LINE__);
	}

	if ((size) != (QueueSize(dest)))
	{
		printf("QueueSize error at line: %d\n", __LINE__);
	}

	/* append with empty dest */

	QueueAppend(queue, dest);
	
	if (QueueIsEmpty(queue))
	{
		printf("QueueAppend error at line: %d\n", __LINE__);
	}

	if (!(QueueIsEmpty(dest)))
	{
		printf("QueueAppend error at line: %d\n", __LINE__);
	}

	if ((size) != (QueueSize(queue)))
	{
		printf("QueueSize error at line: %d\n", __LINE__);
	}

	QueueDestroy(queue);	
	QueueDestroy(dest);	
	
	dest = NULL;
	queue = NULL;
	
	return EXIT_SUCCESS;
}
