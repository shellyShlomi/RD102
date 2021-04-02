/* Developer: Shelly Shlomi;									*/
/* Status: in development;										*/
/* Date Of Creation:31.03.21;									*/
/* Date Of Finish:02.04.21;									*/
/* Date Of Approval: --.--.--;									*/
/* Description: print array of struct befor and after addtion;	*/

#include <stdio.h>		/* print */
#include <assert.h>		/* assert */
#include <string.h>		/* strcpy */
#include <stdlib.h>		/* malloc */

#include "ex1.h"	/* the function declaration */

#define SIZE 20

/*num of elements in the data arr USED IN INITALL */
#define INT_ELEMENT 10
#define FLOAT_ELEMENT 5
#define STR_ELEMENT 5 

#define TO_ADD -13
#define UNUSED(x) (void)(x)

typedef struct element element_t;

typedef void (*print_t)(const element_t *data);
typedef int (*add_t)(element_t *data, int to_add);
typedef void (*clean_t)(element_t *data);

struct element 
{
	void *data;
	add_t add;
	print_t print;
	clean_t clean;
};
typedef enum 
{
	SUCCESS,
	ERROR
	
}return_val_t;

/* callee funcs of Manage*/
static int InitAll(element_t *element_arr, size_t size);
static int AddToAll(element_t *element_arr, size_t size, int to_add);
static void PrintAll(element_t *element_arr, size_t size);
static void CleanAll(element_t *element_arr, size_t size);

/*initalation funcs*/
static void InitInt(element_t *element_arr, size_t ele_num);
static void InitFloat(element_t *element_arr, size_t ele_num);
static int InitString(element_t *element_arr, size_t size);

/*struct iner funcs addition funcs*/
static int AddToInt(element_t *val, int to_add);
static int AddToFloat(element_t *val, int to_add);
static int AddToString(element_t *val, int to_add);

/*struct iner print funcs*/
static void PrintInt(const element_t *val);
static void PrintFloat(const element_t *val);
static void PrintString(const element_t *val);

/*struct iner clean funcs*/
static void CleanNothing(element_t *val);
static void CleanHeap(element_t *val);

/* INER funcs */
/* counter func */
static int CountChrInNum(int to_add);



void Manage()
{
	int fail = 0;
	element_t element_arr[SIZE] = {0};
	
	fail = InitAll(element_arr, SIZE);	
	
	if (fail)
	{
		return ;
	}
	
	PrintAll(element_arr, SIZE);
	
	fail = AddToAll(element_arr, SIZE, TO_ADD);
	
	if (fail)
	{
		return ;
	}
	
	PrintAll(element_arr, SIZE);
	
	CleanAll(element_arr, SIZE);
		
	return ;	
}

/* initalation funcs definition */
static int InitAll(element_t *element_arr, size_t size)
{	

	int location = INT_ELEMENT + FLOAT_ELEMENT;	
	int fail = 0;
	
	assert(element_arr);
	
	InitInt(element_arr, INT_ELEMENT);
	InitFloat(element_arr + INT_ELEMENT, FLOAT_ELEMENT);
	fail = InitString(element_arr + location, size - location);

	if (fail)
	{
		return ERROR;
	}
	
	return SUCCESS;
}

static void InitInt(element_t *element_arr, size_t ele_num)
{
	size_t i = 0;
	static int int_arr[] = {5, 3, 9, -2, 4, 1, 10, 8, 0, 53};

	assert(element_arr);

	for (i = 0; i < ele_num; ++i)
	{
		element_arr[i].data = (void *)(int_arr + i);
		element_arr[i].add = AddToInt;
		element_arr[i].print = PrintInt;
		element_arr[i].clean = CleanNothing;
	}

	return ;
}


static void InitFloat(element_t *element_arr, size_t ele_num)
{
	size_t i = 0;
	static float float_arr[] = {5.03, 3.88, 9.93, 8.93, 53.66};
	
	assert(element_arr);
	
	for(i = 0 ; i < ele_num; ++i)
	{
		element_arr[i].data = (void *)(float_arr + i);
		element_arr[i].add = AddToFloat;
		element_arr[i].print = PrintFloat;
		element_arr[i].clean = CleanNothing;	
	}
	
	return ;
}

static int InitString(element_t *element_arr, size_t size)
{
	size_t i = 0;
	char *heap = NULL;
	char *str[] = {"Hello", "Shelly", "Shelly Shlomi", "Shlomi", "Hi"};

	assert(element_arr);
	
	for(i = 0 ; i < size ; ++i)
	{	
		heap = (char *)malloc(strlen(str[i]) + 1);
		
		if (!heap) 
		{	
			CleanAll(element_arr, size);
			return ERROR;
		}
		
		strcpy(heap, str[i]);
		element_arr[i].data = (void *)heap;
		element_arr[i].add = AddToString;
		element_arr[i].print = PrintString;
		element_arr[i].clean = CleanHeap;
	}
	
	return SUCCESS;
}

/*Print funcs definition*/
static void PrintAll(element_t *element_arr, size_t size)
{
	size_t i = 0;
	
	assert(element_arr);
	
	for (i = 0 ;i < size; ++i)	
	{
		element_arr[i].print(element_arr + i);
	}
		
	return ;
}

static void PrintInt(const element_t *val)
{
	assert(val);
	
	printf("%d\n", *(int *)val->data);
	
	return ;
}
static void PrintFloat(const element_t *val)
{
	assert(val);
	
	printf("%.2f\n", *(float *)val->data);
	
	return ;
}
static void PrintString(const element_t *val)
{
	assert(val);
	
	printf("%s\n", (char *)val->data);
	
	return ;
}

/*Print funcs definition*/
static int AddToAll(element_t *element_arr, size_t size, int to_add)
{
	size_t i = 0;
	int fale = 0;
	
	assert(element_arr);
	
	for (i = 0 ;i < size; ++i)	
	{
		fale = element_arr[i].add(element_arr + i, to_add);
		
		if (fale)
		{	
			CleanAll(element_arr, size);
			
			return ERROR;			
		}
	}
	return SUCCESS;
}

static int AddToInt(element_t *val, int to_add)
{
	int *int_addition = NULL;

	assert(val);

	int_addition = (int *)val->data;
	*int_addition  += to_add;

	return SUCCESS;
}
static int AddToFloat(element_t *val, int to_add)
{	
	float *float_addition = NULL;

	assert(val);

	float_addition = (float *)val->data;
	*float_addition  += to_add;

	return SUCCESS;
}
static int AddToString(element_t *val, int to_add)
{
	size_t i = 1;
	size_t lengt = 0;
	int addition = to_add;
	int fale = 0;
	
	assert(val);
  	
  	lengt = strlen((char *)val->data);
  	
  	if (0 > to_add)
	{
		++i;
	}
	
	i += CountChrInNum(to_add);
	
  	val->data = realloc(val->data, lengt + i);
	
	if (!val->data)
	{
		return ERROR;
	}	
	
	fale = sprintf((char *)(val->data) + lengt, "%d", addition);
	
	if (0 > fale)
	{
		return ERROR;
	}
	
	return SUCCESS;
}

/*struct iner clean funcs*/
static void CleanAll(element_t *element_arr, size_t size)
{
	size_t i = 0;
	
	assert(element_arr);
	
	for (i = 0 ;i < size; ++i)	
	{
		element_arr[i].clean(element_arr + i);
	}

	return ;
}

static void CleanHeap(element_t *val)
{
	assert(val);
	
	free(((char *)val->data));
	val->data = NULL;
	
	return ;
}

static void CleanNothing(element_t *val)
{
	UNUSED(val);
	return ;
}


/*counter func iner func*/
static int CountChrInNum(int to_add)
{
	size_t i = 0;
	
	while(0 != to_add)
  	{
  		to_add /= 10;
  		++i; 
  	}
  	
  	return i;
}
