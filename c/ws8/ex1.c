/*  Developer: Shelly Shlomi;									*/
/*  Status: in development;										*/
/*  Date Of Creation:31.03.21;									*/
/*  Date Of Approval: 02.04.21;									*/
/*  Approved By: ROMAN;											*/
/*  Description: print array of struct befor and after addtion;	*/

#include <stdio.h>		/*	print	*/
#include <assert.h>		/*	assert	*/
#include <string.h>		/*	strcpy	*/
#include <stdlib.h>		/*	malloc	*/

#include "ex1.h" /* the function declaration */

#define SIZE 20 

/* num of elements in the data arr USED IN INITALL */
#define INT_ELEMENT 10
#define FLOAT_ELEMENT 5
#define STR_ELEMENT 5

#define TO_ADD -13
#define UNUSED(x) (void)(x)

typedef struct element element_t;

typedef void (*print_t)(const element_t *data);
typedef int (*add_t)(element_t *val, int to_add);
typedef void (*clean_t)(element_t *val);

struct element
{
	void *data;
	add_t add;
	print_t print;
	clean_t clean;
};


/* callee funcs of Manage */
static int InitAll(element_t *element_arr, size_t size);
static void PrintAll(element_t *element_arr, size_t size);
static int AddToAll(element_t *element_arr, size_t size, int to_add);
static void CleanAll(element_t *element_arr, size_t size, size_t delta);

/* initalation funcs */
static void InitInt(element_t *element_arr, size_t ele_num);
static void InitFloat(element_t *element_arr, size_t ele_num);
static int InitString(element_t *element_arr, size_t size);

/* struct iner funcs addition funcs */
static int AddToInt(element_t *val, int to_add);
static int AddToFloat(element_t *val, int to_add);
static int AddToString(element_t *val, int to_add);

/* struct iner print funcs */
static void PrintInt(const element_t *val);
static void PrintFloat(const element_t *val);
static void PrintString(const element_t *val);

/* struct iner clean funcs */
static void CleanNothing(element_t *val);
static void CleanHeap(element_t *val);

/* INER funcs */
/* counter func */
static size_t CountChrInNum(int to_add);

void Manage()
{
	element_t element_arr[SIZE] = {0};
	int fail = 0;

	fail = InitAll(element_arr, SIZE);

	if (fail)
	{
		return;
	}

	PrintAll(element_arr, SIZE );

	fail = AddToAll(element_arr, SIZE, TO_ADD);

	if (fail)
	{
		return;
	}

	PrintAll(element_arr, SIZE);

	CleanAll(element_arr, SIZE , 0);

	return;
}

/*  initalation funcs definition */

/*  InitAll ***USES #define*** the minimal size for arrays **HAS** to be	*/ 
/*	at least as the #define size of the equivalent type,(espesialy in the	*/
/*	str array)																*/
static int InitAll(element_t *element_arr, size_t size)
{

	int elements = INT_ELEMENT + FLOAT_ELEMENT;
	int fail = 0;

	assert(NULL != element_arr);

	InitInt(element_arr, INT_ELEMENT);
	InitFloat(element_arr + INT_ELEMENT, FLOAT_ELEMENT);
	fail = InitString(element_arr + elements, size - elements);

	if (fail)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

static void InitInt(element_t *element_arr, size_t ele_num)
{
	static int int_arr[] = {5, 3, 9, -2, 4, 1, 10, 8, 0, 50000};
	size_t i = 0;

	assert(NULL != element_arr);

	for (i = 0; i < ele_num; ++i)
	{
		(element_arr + i)->data = (void *)(int_arr + i);
		(element_arr + i)->add = AddToInt;
		(element_arr + i)->print = PrintInt;
		(element_arr + i)->clean = CleanNothing;
	}	
	
	return;
}

static void InitFloat(element_t *element_arr, size_t ele_num)
{
	static float float_arr[] = {5.03, 3.88, 9.93, 8.93, 53.66, 8.02};
	size_t i = 0;

	assert(NULL != element_arr);

	for (i = 0; i < ele_num; ++i)
	{
		(element_arr + i)->data = (void *)(float_arr + i);
		(element_arr + i)->add = AddToFloat;
		(element_arr + i)->print = PrintFloat;
		(element_arr + i)->clean = CleanNothing;
	}

	return;
}

static int InitString(element_t *element_arr, size_t size)
{
	char *str[] = {"Hello", "Shelly", "Shelly Shlomi", "Shlomi", "Hi"};
	char *heap = NULL;
	size_t i = 0;

	assert(NULL != element_arr);

	for (i = 0; i < size; ++i)
	{
		heap = (char *)malloc(strlen(*(str + i)) + 1);

		if (!heap)
		{
			CleanAll(element_arr, SIZE, size - i);
			
			return EXIT_FAILURE;
		}

		strcpy(heap, str[i]);

		(element_arr + i)->data = (void *)heap;
		(element_arr + i)->add = AddToString;
		(element_arr + i)->print = PrintString;
		(element_arr + i)->clean = CleanHeap;
	}

	return EXIT_SUCCESS;
}

/* Print funcs definition */

static void PrintAll(element_t *element_arr, size_t size)
{
	size_t i = 0;

	assert(NULL != element_arr);

	for (i = 0; i < size; ++i)
	{
		(element_arr + i)->print(element_arr + i);
	}

	return ;
}

static void PrintInt(const element_t *val)
{
	assert(NULL != val);

	printf("Int is:  %d\n", *(int *)val->data);

	return;
}

static void PrintFloat(const element_t *val)
{
	assert(NULL != val);

	printf("Float is:  %.2f\n", *(float *)val->data);

	return;
}

static void PrintString(const element_t *val)
{
	assert(NULL != val);

	printf("String is:  %s\n", (char *)val->data);

	return;
}



/* Add funcs definition */
static int AddToAll(element_t *element_arr, size_t size, int to_add)
{
	size_t i = 0;
	int fail = 0;

	assert(NULL != element_arr);

	for (i = 0; i < size; ++i)
	{
		fail = (element_arr + i)->add(element_arr + i, to_add);

		if (fail)
		{
			CleanAll(element_arr, size, 0);

			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

static int AddToInt(element_t *val, int to_add)
{
	int *int_addition = NULL;

	assert(NULL != val);

	int_addition = (int *)val->data;
	*int_addition += to_add;

	return EXIT_SUCCESS;
}

static int AddToFloat(element_t *val, int to_add)
{
	float *float_addition = NULL;

	assert(NULL != val);

	float_addition = (float *)val->data;
	*float_addition += to_add;

	return EXIT_SUCCESS;
}

static int AddToString(element_t *val, int to_add)
{
	size_t count_chr_num = 1;
	size_t length = 0;
	int addition = to_add;
	int fail = 0;

	assert(NULL != val);

	length = strlen((char *)val->data);

	if (0 > to_add)
	{
		++count_chr_num;
	}

	count_chr_num += CountChrInNum(to_add);

	val->data = realloc(val->data, length + count_chr_num);

	if (!val->data)
	{
		return EXIT_FAILURE;
	}

	fail = sprintf((char *)(val->data) + length, "%d", addition);

	if (0 > fail)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/* struct iner clean funcs */
static void CleanAll(element_t *element_arr, size_t size, size_t delta)
{
	size_t i = 0;

	assert(NULL != element_arr);

	for (i = size - delta - 1; i > 0; --i)
	{
		(element_arr + i)->clean(element_arr + i);
	}

	return;
}

static void CleanHeap(element_t *val)
{
	assert(NULL != val);

	free(((char *)val->data));

	val->data = NULL;

	return;
}

static void CleanNothing(element_t *val)
{
	UNUSED(val);
	
	return;
}

/* counter func iner func */
static size_t CountChrInNum(int to_add)
{
	size_t count = 0;

	while (0 != to_add)
	{
		to_add /= 10;
		++count;
	}

	return count;
}
