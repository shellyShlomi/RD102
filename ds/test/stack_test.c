
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit status */
#include <string.h> /* strcmp */

#include "stack.h"

#define CAPACITY 100
#define BOL_SUCCESS 1


static int StackManager();

enum ELEM
{
	FIRST = 1,
	SECOND,
	THIRD,
	FOURTH
};
	
int main()
{
	int fail = 0;
	
	fail = StackManager();
	
	if (fail)
	{	
		printf("StackManager error at line: %d\n", __LINE__);
		
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}

static int StackManager()
{

	float data = 20.33;
	int data1 = 9;
	double data2 = 601.33333;
	char *str = "shelly";
	stack_t *stack = StackCreate(CAPACITY);
	
	if (NULL == stack)
	{
		printf("StackCreate error at line: %d\n", __LINE__);
		return EXIT_FAILURE; 
	}
	
	if (CAPACITY != StackGetCapacity(stack))
	{
		printf("StackGetCapacity error at line: %d\n", __LINE__);
	}
	
	if (BOL_SUCCESS != StackIsEmpty(stack))
	{
		printf("StackIsEmpty error at line: %d\n", __LINE__);
	}
	
	if ((!BOL_SUCCESS) != StackSize(stack))
	{
		printf("StackSize error at line: %d\n", __LINE__);
	}
	
	StackPush(stack, (void *)&data1);

	if ((!BOL_SUCCESS) != StackIsEmpty(stack))
	{
		printf("StackIsEmpty error at line: %d\n", __LINE__);
	}
	
	if (FIRST != StackSize(stack))
	{
		printf("StackPush error at line: %d\n", __LINE__);
	}

	StackPush(stack, (void *)&data);
	if (SECOND != StackSize(stack))
	{
		printf("StackPush error at line: %d\n", __LINE__);
	}

	StackPush(stack, (void *)str);
	if (THIRD != StackSize(stack))
	{
		printf("StackPush error at line: %d\n", __LINE__);
	}

	StackPush(stack, (void *)&data2);
	if (FOURTH != StackSize(stack))
	{
		printf("StackPush error at line: %d\n", __LINE__);
	}
	
	if (data2 != *(double *)StackPeek(stack))
	{
		printf("StackPeek error at line: %d\n", __LINE__);
	}
	
	StackPop(stack);
	if (THIRD != StackSize(stack))
	{
		printf("StackPop error at line: %d\n", __LINE__);
	}
	
	if (0 != strcmp(str, (char *)StackPeek(stack)))
	{
		printf("StackPeek error at line: %d\n", __LINE__);
	}
	
	StackPop(stack);
	if (SECOND != StackSize(stack))
	{
		printf("StackPop error at line: %d\n", __LINE__);
	}
	
	if (data != *(float *)StackPeek(stack))
	{
		printf("StackPeek error at line: %d\n", __LINE__);
	}
	
	StackPop(stack);
	if (FIRST != StackSize(stack))
	{
		printf("StackPop error at line: %d\n", __LINE__);
	}
	
	StackPop(stack);
	if (0 != StackSize(stack))
	{
		printf("StackPop error at line: %d\n", __LINE__);
	}
	
	
	if (BOL_SUCCESS != StackIsEmpty(stack))
	{
		printf("StackIsEmpty error at line: %d\n", __LINE__);
	}
	
	StackPush(stack, (void *)&data);
	if (FIRST != StackSize(stack))
	{
		printf("StackPush error at line: %d\n", __LINE__);
	}

	StackPush(stack, (void *)str);
	if (SECOND != StackSize(stack))
	{
		printf("StackPush error at line: %d\n", __LINE__);
	}

	StackPush(stack, (void *)&data2);
	if (THIRD != StackSize(stack))
	{
		printf("StackPush error at line: %d\n, ", __LINE__);
	}
	
	StackDestroy(stack);
	stack = NULL;
	
	return EXIT_SUCCESS; 

}



