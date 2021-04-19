













/*
#include <stdio.h> /* printf *//*
#include <stdlib.h> /* exit status */
/*
#include "vector.h"

#define CAPACITY 10
#define CAPACITY_SMALL 2
#define SUCCESS 0


enum ELEM
{
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR, 
	FIVE
};
*/
/*
static int VectorManager();
	
int main()
{
	int fail = 0;
	
	fail = VectorManager();
	
	if (fail)
	{	
		printf("VectorManager error at line: %d\n", __LINE__);
		
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}*/
/*
static int VectorManager()
{

	float data = 20.33;
	int data1 = 9;
	double data2 = 601.33333;
	char *str = "shelly";
	char *str1 = "shelly1";
	char *str2 = "shelly2";
	char *str3 = "shelly3";
	
	vector_t *vector = VectorCreate(CAPACITY);
	
	if (NULL == vector)
	{
		printf("VectorCreate error at line: %d\n", __LINE__);
		return EXIT_FAILURE; 
	}
	
	if (CAPACITY != VectorCapacity(vector))
	{
		printf("VectorCapacity error at line: %d\n", __LINE__);
	}
	
	if (ZERO != VectorSize(vector))
	{
		printf("VectorSize error at line: %d\n", __LINE__);
	}

	if (SUCCESS != VectorPushBack(vector, (void *)&data1))
	{
		printf("VectorPushBack error at line: %d\n", __LINE__);
	}
	
	VectorDestroy(vector);
	vector = NULL;
	
	return EXIT_SUCCESS; 
}*/

