#ifndef __TOOLS_H__
#define __TOOLS_H__
#include <stddef.h> /* size_t */

#define UNUSED(x) (void)(x)
#define INTARRCMP(arr1, arr2) \
	IntArrayCompare((arr1), sizeof(arr1), (arr2), sizeof(arr2))

/*expression*/
void TotalErrors(void);
int Validate(int expression, const char *message, int line);
int Valid(int expression, const char *message, int line);
/*int*/
int IntArrayCompare(int arr1[], size_t len1, int arr2[], size_t len2);
void PrintIntArr(int arr[], size_t size);
/*str*/
int ValidStrEqual(const char *str1, const char *str2, const char *message, int line);
int ValidStrUnEqual(const char *str1, const char *str2, const char *message, int line);
/*ptr*/
int PtrValidateEqual(void *d1, void *d2, const char *message, int line);
int PtrValidateUnEqual(void *d1, void *d2, const char *message, int line);

char *Pars(char *buff, int data);
#endif /* __TOOLS_H__*/
