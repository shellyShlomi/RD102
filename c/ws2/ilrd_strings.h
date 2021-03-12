#ifndef __ILRD_STRINGS_H__
#define __ILRD_STRINGS_H__
#include <stdio.h>  /*printf function*/
#include <string.h> /*for strlen strcmp*/
#include <assert.h> /*assret function*/
#include <ctype.h> /*tolower function*/
#include <strings.h> /*strcasecmp function*/

int StrCmp(const char *str1, const char *str2);
size_t StrLen(const char *str);
char *StrCpy(char *dest, const char *src);
char *StrnCpy(char *dest, const char *src, size_t n);
int StrCaseCmp(const char *str1, const char *str2);

void TestFunction();
void TestStrLenAndStrCmp();
void TestStrCpy();	
void TestStrnCpy();
void TestStrCaseCmp();

#endif


