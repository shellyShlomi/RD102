
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit status */

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
}

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
	
	if (ONE != VectorSize(vector))
	{
		printf("VectorSize error at line: %d\n", __LINE__);
	}
	
	if (SUCCESS != VectorPushBack(vector, (void *)&data))
	{
		printf("VectorPushBack error at line: %d\n", __LINE__);
	}
	
	if (TWO != VectorSize(vector))
	{
		printf("VectorSize error at line: %d\n", __LINE__);
	}
	
	if (SUCCESS != VectorPushBack(vector, (void *)str))
	{
		printf("VectorPushBack error at line: %d\n", __LINE__);
	}
	
	if (str != (char *)VectorGetElem(vector, TWO))
	{
		printf("VectorGetElem error at line: %d\n", __LINE__);
	}
	
	if (THREE != VectorSize(vector))
	{
		printf("VectorSize error at line: %d\n", __LINE__);
	}


	VectorSetElem(vector, TWO,(void *)&data2);
	if (data2 != *(double *)VectorGetElem(vector, TWO))
	{
		printf("VectorSetElem error at line: %d\n", __LINE__);
	}
	
	/* test if the size and the capacity changed after ShrinkToFit */
	{
		if (SUCCESS != VectorShrinkToFit(vector))
		{
			printf("VectorShrinkToFit error at line: %d\n", __LINE__);
		}
		
		if (VectorCapacity(vector)	!= 	VectorSize(vector) &&
							THREE 	== 	VectorSize(vector)		)
		{
			printf("VectorShrinkToFit error at line: %d\n", __LINE__);
		}
	}
	/* test if the size was multyply after a push whene the arr was full */
	{
		if (SUCCESS != VectorPushBack(vector, (void *)str))
		{
			printf("VectorPushBack error at line: %d\n", __LINE__);
		}
		if ((VectorSize(vector) - 1) * TWO != VectorCapacity(vector))
		{
			printf("VectorPushBack & VectorReserve error line: %d\n", __LINE__);
		}
	}
	
		/* test the reserv func on extending & redusing the size */
	{
		if (SUCCESS != VectorReserve(vector, CAPACITY_SMALL))
		{
			printf("VectorReserve to small error at line: %d\n", __LINE__);
		}
		
		if (VectorSize(vector)	!= 	VectorCapacity(vector) &&
				CAPACITY_SMALL 	== 	VectorSize(vector)			)
		{
			printf("VectorReserve to small error at line: %d\n", __LINE__);
		}
		/* the top elem after Reserve down */
		if (data != *(float *)VectorGetElem(vector, ONE))
		{
			printf("VectorGetElem error at line: %d \n", __LINE__);
		}
		
		if (SUCCESS != VectorReserve(vector, CAPACITY))
		{
			printf("VectorReserve to a bigger error at line: %d\n", __LINE__);
		}
		
		if (CAPACITY != VectorCapacity(vector) && TWO == VectorSize(vector))
		{
			printf("VectorReserve to a bigger error at line: %d\n", __LINE__);
		}
		/* the top elem after Reserve up */
		if (data != *(float *)VectorGetElem(vector, ONE))
		{
			printf("VectorGetElem error at line: %d \n", __LINE__);
		}
	}
	
	/* test the VectorPopBack func */
	{
		if (SUCCESS != VectorPushBack(vector, (void *)str))
		{
			printf("VectorPushBack error at line: %d\n", __LINE__);
		}
		
		if (SUCCESS != VectorPushBack(vector, (void *)str1))
		{
			printf("VectorPushBack error at line: %d\n", __LINE__);
		}
		
		if (SUCCESS != VectorPushBack(vector, (void *)str2))
		{
			printf("VectorPushBack error at line: %d\n", __LINE__);
		}
		
		if (str2 != (char *)VectorGetElem(vector, VectorSize(vector) - 1))
		{
			printf("VectorGetElem error at line: %d\n", __LINE__);
		}
		
		if (SUCCESS != VectorPushBack(vector, (void *)str3))
		{
			printf("VectorPushBack error at line: %d\n", __LINE__);
		}
		
		VectorPopBack(vector);
		if (FIVE != VectorSize(vector))
		{
			printf("VectorPopBack to small error at line: %d\n", __LINE__);
		}
		
		/* to see the val of the top elem after pop */
		if (str2 != (char *)VectorGetElem(vector, VectorSize(vector) - 1))
		{
			printf("VectorPopBack error at line: %d\n", __LINE__);
		}
		
		VectorPopBack(vector);
		if (FOUR != VectorSize(vector))
		{
			printf("VectorPopBack to small error at line: %d\n", __LINE__);
		}
		/* to see the val of the top elem after pop */
		if (str1 != (char *)VectorGetElem(vector, VectorSize(vector) - 1))
		{
			printf("VectorPopBack error at line: %d\n", __LINE__);
		}
		
		VectorPopBack(vector);
		if (THREE != VectorSize(vector))
		{
			printf("VectorPopBack to small error at line: %d\n", __LINE__);
		}
		
		VectorPopBack(vector);
		if (TWO != VectorSize(vector))
		{
			printf("VectorPopBack to small error at line: %d\n", __LINE__);
		}
		
		/* VectorPopBack													*
		 * test the reduce the capacity to hafe 1/4 full elems at the arr	*/
		{
			if (FIVE != VectorCapacity(vector))
			{
				printf("PopBack to small arr size error, line: %d\n", __LINE__);
			}
		}
		
		if (data != *(float *)VectorGetElem(vector, ONE))
		{
			printf("VectorPopBack error at line: %d \n", __LINE__);
		}
	}
	
	VectorDestroy(vector);
	vector = NULL;
	
	return EXIT_SUCCESS; 

}

