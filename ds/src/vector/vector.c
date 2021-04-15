/*  Developer: Shelly Shlomi;									*/
/*  Status:DONE;												*/
/*  Date Of Creation:14.04.21;									*/
/*  Date Of Approval:--.--.21;									*/
/*  Approved By: 												*/
/*  Description: vector data structure 							*/

#include <stdlib.h>	/* malloc */
#include <assert.h> /* assert */
#include <stdlib.h> /* exit status */

#include "vector.h"

#define FACTOR 2


struct vector
{
	void **arr;
	size_t capacity;
	size_t size;
}; 
 
/* O(1) time, O(n)space */
vector_t *VectorCreate(size_t capacity)
{
	vector_t *vector = (vector_t *)malloc(sizeof(vector_t));
	
	if (NULL == vector)
	{
		return NULL; 
	}
	
	vector->arr = (void **)malloc(capacity * sizeof(void **));
	if (NULL == vector->arr)
	{
		return NULL; 
	}
	
	vector->size = 0;
	vector->capacity = capacity;

	return vector;
}

/* O(1) time, O(1)space */
void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);

	free(vector->arr);
	vector->arr = NULL;
	free(vector);
	return ;
}

/* O(1) time, O(1)space */
size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);
		
	return vector->size;
}


/* O(1) time, O(1)space */
size_t VectorCapacity(const vector_t *vector)
{
	assert(NULL != vector);
	
	return vector->capacity;
}


int VectorPushBack(vector_t *vector, void *data)
{
	/*int err = -1;*/
	
	assert(NULL != vector);
	assert(NULL != data);

	if (vector->size == vector->capacity)
	{
		/*err = VectorReserve(vector, vector->size * FACTOR);*/
		
		if (VectorReserve(vector, vector->size * FACTOR))
		{
			return EXIT_FAILURE; 
		}
	}
	
	++(vector->size);
	VectorSetElem(vector, vector->size - 1, data);
	
	return EXIT_SUCCESS;
}

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	void **arr_temp = NULL;
	
	assert(NULL != vector);
	
	arr_temp = (void **)realloc(vector->arr, sizeof(void **) * new_capacity);
	
	if (NULL == arr_temp)
	{	
		return EXIT_FAILURE; 
	}

	vector->arr = arr_temp;
	
	arr_temp  = NULL;
	
	vector->capacity = new_capacity;
	
	if (vector->size > vector->capacity)
	{
		vector->size = vector->capacity;
	}
	
	return EXIT_SUCCESS;
}


int VectorShrinkToFit(vector_t *vector)
{
	assert(NULL != vector);
	
	vector->arr = (void **)realloc(vector->arr, sizeof(void **) * vector->size);
	
	if (NULL == vector->arr)
	{	
		return EXIT_FAILURE; 
	}
	
	vector->capacity = vector->size;
	
	return EXIT_SUCCESS;
}
void VectorPopBack (vector_t *vector)
{
	assert(NULL != vector);
	assert(0 != vector->size);
	
	*(vector->arr + vector->size - 1) = NULL;
	--(vector->size);

	return ;
}

void *VectorGetElem(const vector_t *vector, size_t index)
{
	assert(NULL != vector);
	assert(index < vector->size);
	
	return *(vector->arr + index);	

}

void VectorSetElem(vector_t *vector, size_t index, void *data)
{
	assert(NULL != vector);
	assert(index < vector->size);
	
	*(vector->arr + index) = data;
	
	return;
}
       
