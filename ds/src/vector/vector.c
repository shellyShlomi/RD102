/*  Developer: Shelly Shlomi;									*
 *  Status:APPROVED;											*
 *  Date Of Creation:14.04.21;									*
 *  Date Of Approval:16.04.21;									*
 *  Approved By: getta;											*
 *  Description: vector data structure;							*/

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
 
/* O(1)time, O(n)space, n - stand for capacity */
vector_t *VectorCreate(size_t capacity)
{
	vector_t *vector = (vector_t *)malloc(sizeof(vector_t));
	
	if (NULL == vector)
	{
		return NULL; 
	}
	
	vector->arr = (void **)malloc(capacity * sizeof(void *));
	
	if (NULL == vector->arr)
	{	
		free(vector);
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
	
	vector->size = 0;
	vector->capacity = 0;
	
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

/* time: O(n) for n operation, O(1) amortaiz &&  *
 * space: O(n) for n operation, O(1) amortaiz    */
int VectorPushBack(vector_t *vector, void *data)
{
	assert(NULL != vector);

	if (vector->size == vector->capacity)
	{
		if (VectorReserve(vector, vector->size * FACTOR))
		{
			return EXIT_FAILURE; 
		}
	}
	
	++(vector->size);
	VectorSetElem(vector, vector->size - 1, data);
	
	return EXIT_SUCCESS;
}

/* time: O(n) where n is size ,space: O(n) where n is new capacity */
int VectorReserve(vector_t *vector, size_t new_capacity)
{
	void **arr_temp = NULL;
	
	assert(NULL != vector);
	
	arr_temp = (void **)realloc(vector->arr, sizeof(void *) * new_capacity);
	
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

/* time: O(1) && space: O(1) */
int VectorShrinkToFit(vector_t *vector)
{
	assert(NULL != vector);

	return VectorReserve(vector, vector->size);
}

/* time: O(1) && space: O(1) | Approved by: eden s*/
void VectorPopBack(vector_t *vector)
{
	assert(NULL != vector);
	assert(0 != vector->size);
	assert(NULL != vector->arr);
	
	VectorSetElem(vector, vector->size - 1, NULL);
	--(vector->size);
	
	/* reduce the capacity to half if we have only 1/4 full elems at the arr */
	if ( vector->size <= (vector->capacity / (FACTOR * FACTOR)) )
	{
		VectorReserve(vector, vector->capacity / FACTOR);
	}

	return ;
}

/* time: O(1) && space: O(1) */
void *VectorGetElem(const vector_t *vector, size_t index)
{
	assert(NULL != vector);
	assert(0 != vector->size);
	assert(index < vector->size);
	
	return *(vector->arr + index);	

}

/* time: O(1) && space: O(1) */
void VectorSetElem(vector_t *vector, size_t index, void *data)
{
	assert(NULL != vector);
	assert(0 != vector->size);
	assert(index < vector->size);
	
	*(vector->arr + index) = data;
	
	return;
}
       
