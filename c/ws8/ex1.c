
/* Developer: Shelly Shlomi;									*/
/* Status: in development;										*/
/* Date Of Creation:31.03.21;									*/
/* Date Of Creation:02.04.21;									*/
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
#define TO_ADD 10
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

/* callee funcs of Manage*/
static int InitAll(element_t *element_arr, size_t size_glob_arr);
static int AddToAll(element_t *element_arr, size_t size, int to_add);
static void PrintAll(element_t *element_arr, size_t size);
static void CleanAll(element_t *element_arr, size_t size);

/*initalation funcs*/
static void InitInt(element_t *element_arr, size_t size, int *int_arr);

static void InitFloat(element_t *element_arr, size_t size, float *float_arr);

static void InitString(element_t *element_arr, char *str);

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
/* String Data func */
static int StringData(element_t *element_arr, size_t size);


void Manage()
{
	int success = -1;
	static element_t element_arr[SIZE] = {0};
	
	success = InitAll(element_arr, SIZE);	
	
	if (!success)
	{
		return ;
	}
	
	PrintAll(element_arr, SIZE);
	
	success = AddToAll(element_arr, SIZE, TO_ADD);
	
	if (!success)
	{
		return ;
	}
	
	PrintAll(element_arr, SIZE);
	
	CleanAll(element_arr, SIZE);
		
	return ;	
}
/* initalation funcs definition */
/* InitAll manage the data of ints & floats for the program */
static int InitAll(element_t *element_arr, size_t size_glob_arr)
{	
	static int int_arr[] = {5, 3, 9, -2, 4, 1, 10, 8, 0, 53};
	static float float_arr[] = {5.03, 3.88, 9.93, 8.93, 53.66};
	
	assert(element_arr);
	
	InitInt(element_arr, size_glob_arr, int_arr);

	InitFloat(element_arr + INT_ELEMENT, size_glob_arr, float_arr);
	StringData(element_arr, size_glob_arr);

	
	return 1;
}
/*StringData func iner func*/
static int StringData(element_t *element_arr, size_t size)
{
	int element_location = INT_ELEMENT + FLOAT_ELEMENT;	
	/*string to copy from it*/
	char local0[] = "Hello";
	char local1[] = "Shelly";
	char local2[] = "Shelly Shlomi";
	char local3[] = "Shlomi";
	char local4[] = "Hi";
	/*{ "Shelly", "Shelly Shlomi", "Shlomi", "Hi"};*/
	/*malloc to copy to it from local str*/
	char *str0 = (char *)malloc(strlen(local0) + 1);
	char *str1 = (char *)malloc(strlen(local1) + 1);
	char *str2 = (char *)malloc(strlen(local2) + 1);
	char *str3 = (char *)malloc(strlen(local3) + 1);
	char *str4 = (char *)malloc(strlen(local4) + 1);
	
	if (!str0 || !str1 || !str2 || !str3 || !str4) 
	{	
		CleanAll(element_arr, size);
		return 0;
	}
	
	strcpy(str0, local0);
	strcpy(str1, local1);
	strcpy(str2, local2);
	strcpy(str3, local3);
	strcpy(str4, local4);
	
	InitString(element_arr + element_location, str0);
	InitString(element_arr + element_location + 1, str1);	
	InitString(element_arr + element_location + 2, str2);
	InitString(element_arr + element_location + 3, str3);
	InitString(element_arr + element_location + 4, str4);
	
	return 1;
	
}
static void InitInt(element_t *element_arr, size_t size, int *int_arr)
{
	size_t i = 0;
	
	assert(element_arr);
	assert(int_arr);
	
	for(i = 0; i < INT_ELEMENT && INT_ELEMENT < size; ++i)
	{
		element_arr[i].data = (void *)(int_arr + i);
		element_arr[i].add = AddToInt;
		element_arr[i].print = PrintInt;
		element_arr[i].clean = CleanNothing;
	}

	return ;
}
static void InitFloat(element_t *element_arr, size_t size, float *float_arr)
{
	size_t i = 0;
	
	assert(element_arr);
	assert(float_arr);
	
	for(i = 0 ; i < FLOAT_ELEMENT && FLOAT_ELEMENT < size ; ++i)
	{
		element_arr[i].data = (void *)(float_arr + i);
		element_arr[i].add = AddToFloat;
		element_arr[i].print = PrintFloat;
		element_arr[i].clean = CleanNothing;	
	}
	
	return ;
}

static void InitString(element_t *element_arr, char *str)
{
	size_t i = 0;
	
	assert(element_arr);
	assert(str);
	
	element_arr[i].data = (void *)str;
	element_arr[i].add = AddToString;
	element_arr[i].print = PrintString;
	element_arr[i].clean = CleanHeap;
	
	return ;
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
			return 1;			
		}
	}
	return 1;
}

static int AddToInt(element_t *val, int to_add)
{
	int *int_addition = NULL;

	assert(val);

	int_addition = (int *)val->data;
	*int_addition  += to_add;

	return 0;
}
static int AddToFloat(element_t *val, int to_add)
{	
	float *float_addition = NULL;

	assert(val);

	float_addition = (float *)val->data;
	*float_addition  += to_add;

	return 0;
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
		return 1;
	}	
	
	fale = sprintf((char *)(val->data) + lengt, "%d", addition);
	
	if (0 > fale)
	{
		return 1;
	}
	return 0;
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
