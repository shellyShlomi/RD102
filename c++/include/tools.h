#ifndef __TOOLS_H__
#define __TOOLS_H__

#define UNUSED(x) (void)(x)
#define INTARRCMP(arr1, arr2) \
	IntArrayCompare((arr1), sizeof(arr1), (arr2), sizeof(arr2))


int Validate(int expression, const char *message, int line);
int IntArrayCompare(int arr1[], size_t len1, int arr2[], size_t len2);
void TotalErrors(void);
int ValidStrEqual(const char *str1, const char *str2, const char *message, int line);
void PrintIntArr(int arr[], size_t size);

#endif /* __TOOLS_H__*/
