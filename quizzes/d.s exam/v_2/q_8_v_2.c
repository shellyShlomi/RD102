#include <stddef.h> /*size_t*/
#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/
#include <assert.h>

#define Q_SIZE 6

typedef struct circular_queue
{
	char queue[Q_SIZE];
	size_t size; /*the num of elem in the queue*/
	size_t read; /*index to read from*/

}cq_t;


/*---------------impl func-----------------*/
void PushChar(cq_t *que, char c);
char PopChar(cq_t *que);

/*---------------test func-----------------*/
static void Test();

/*------------------------------test for impl---------------------------------*/

int main()
{
	
	Test();
	
	return 0;
}



static void Test()
{
	cq_t *que = (cq_t *) malloc(sizeof(cq_t));
    char inputs[] = {'a', 'b', 'c', 'd', 'e'};
  	size_t size = sizeof(inputs)/ sizeof(inputs[0]);
   	size_t i = 0;
   	size_t first_pop = 3;

    que->read = 0;
    que->size = 0;

	for(i = 0; i < size; ++i)
    {
		 PushChar(que, inputs[i]);
	}

    for(i = 0; i < first_pop; ++i)
    {
		if (inputs[i] != PopChar(que))
		{
			printf("PopChar & PushChar error at line: %d\n",__LINE__);
		}
	}
	
	for(i = first_pop; i < size; ++i)
    {
		 PushChar(que, inputs[i]);
	}
	
	if (first_pop != que->size)
	{
		printf("PopChar & PushChar error at line: %d\n",__LINE__);
	}


 	for(i = 0; que->size > 0; ++i)
    {
		if (inputs[i + 2] != PopChar(que))
		{
			printf("PopChar & PushChar error at line: %d\n",__LINE__);
		}
	}

    if (0 != que->size)
	{
		printf("PopChar & PushChar error at line: %d\n",__LINE__);
	}

	free(que);

    return;
}


/*------------------------------implementetion--------------------------------*/
void PushChar(cq_t *que, char c)
{
	
	assert(que);
	assert(que->size < Q_SIZE);
	
	que->queue[(que->read + que->size) % Q_SIZE] = c;	

	++que->size;
	
	return ;
}

char PopChar(cq_t *que)
{
	char chr = '\0';
	
	assert(que);
	assert(que->size > 0);
	
	chr = que->queue[que->read % Q_SIZE];

	que->read = (que->read + 1)% Q_SIZE; 
	--que->size;
	
	return chr;
}

