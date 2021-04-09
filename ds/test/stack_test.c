
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit status */

#include "stack.h"
	
static int StackManager();

	
int main()
{
	int fail = 0;
	
	StackManager();
	
	if (fail)
	{	
		printf("error\n");
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}

static int StackManager()
{
	size_t capacity = 0;
	float data = 20.33;
	int data1 = 9;
	double data2 = 601.33333;
	char *str = "shelly";
	stack_t *stack = StackCreate(100);
	
	if (NULL == stack)
	{
		return EXIT_FAILURE; 
	}
	
	capacity = StackGetCapacity(stack);
	
	printf("%ld\n", capacity);
	
	StackPush(stack, (void *)&data1);

	if (StackIsEmpty(stack))
	{
		printf("IS EMPTY\n");
	}
	else
	{
		printf("NOT EMPTY\n");
	}
	

	StackPush(stack, (void *)str);
	StackPush(stack, (void *)&data);
	StackPush(stack, (void *)&data2);
	
	printf("%lu\n", StackSize(stack));
	printf("%f\n", *(double *)StackPeek(stack));
	
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	
	printf("%lu\n", StackSize(stack));
	
	if (StackIsEmpty(stack))
	{
		printf("IS EMPTY\n");
	}
	else
	{
		printf("NOT EMPTY\n");
	}
	
	StackDestroy(stack);
	stack = NULL;
	
	return EXIT_SUCCESS; 

}



