#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#define Q_SIZE 3
typedef struct circular_queue
{
	char queue[Q_SIZE];
	size_t size;
	size_t read;

}cq_t;
char PopChar(cq_t *que);

void PushChar(cq_t *que, char c)
{
	
	assert(que);
	assert(que->size < Q_SIZE);
	
	if (que->read - que->size < Q_SIZE)
	{
		que->queue[que->size - que->read + 1] = c;	
	}
	if (que->read + que->size < Q_SIZE) 
	{
		que->queue[que->read + que->size] = c;	
	}

	++que->size;
	
	return ;
}

char PopChar(cq_t *que)
{
	char chr = '\0';
	
	assert(que);
	assert(que->size > 0);
	
	if (que->read == Q_SIZE)
	{	
		chr = que->queue[que->read - 1];
		que->read = 0;
	}
	if (que->read < que->size) 
	{
		chr = que->queue[que->read];
		++que->read;
	
	}
	--que->size;
	
	return chr;
}

void TestQueue()
{
    cq_t *que = (cq_t *) malloc(sizeof(cq_t));
    char inputs[] = {'a', 'b', 'c', 'd', 'e'};
   	size_t i = 0;
	char output = '\0';

    que->read = 0;
    que->size = 0;

    PushChar(que, inputs[0]);
    PushChar(que, inputs[1]);
    PushChar(que, inputs[2]);
    
     
	output = PopChar(que);
	printf("\n%c\n",output);
	
	output = PopChar(que);
    
	printf("\n%c\n\n",output);
	
	 PushChar(que, inputs[3]);
    PushChar(que, inputs[4]);
	
    for(i = 0; i < 3; ++i)
    {
    	printf("%c\n",que->queue[i]);
	}

    
	output = PopChar(que);
    
	printf("\n%c\n",output);
	
	
	output = PopChar(que);
    
	printf("\n%c\n",output);
	printf("%lu\n",que->size);
    return;
}

int main()
{
	TestQueue();
	return (0);
}

