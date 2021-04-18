#ifndef __OL102_EXAM_C_H__
#define __OL102_EXAM_C_H__

#include <stddef.h> /* size_t */

int FlipDigitsInNum(int num);
unsigned char ByteMirror(unsigned char num);
int FlipBit(int val, unsigned int n);
size_t CountBitInByte(unsigned char byte);
char RotateRotL(char byte, unsigned int nbits);

size_t StrLen(const char *str);
char *StrCpy(char *dest, const char *src);
char *StrnCpy(char *dest, const char *src, size_t n);
int StrCmp(const char *str1, const char *str2);
char *StrCat(char *dest, const char *src);
unsigned long GetNFibonacciElement(unsigned int n);
char *Itoa(char *dest, int num);
long MultiplyBy8(int num);
void SwapPtr(int **ptr1, int **ptr2);
void Swap(int *x, int *y);
void SwapAritmetics(int *x, int *y);
void SwapTemp(int *x, int *y);

#endif /* __OL102_EXAM_C_H__ */



