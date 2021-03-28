#ifndef __EX1_H__
#define __EX1_H__
#include <stddef.h>  /*size_t*/

long Pow2(unsigned int x, unsigned int y);
int IsPow2Loop(unsigned int n);
int IsPow2NoLoop(unsigned int n);
int Add1(int n);
void PrintThreeOn(unsigned int nums[], size_t length);
unsigned char ByteMirrorLoop(unsigned char byte);
unsigned char ByteMirrorNoLoop(unsigned char byte);
int IsBit2And6On(unsigned char byte);
int IsBit2Or6On(unsigned char byte);
unsigned char Swap3And5(unsigned char byte);
unsigned int DivideBy16(unsigned int num);
void Swap(unsigned int *x, unsigned int *y);
unsigned int CountBitsLoop(int num);
unsigned int CountBitsNoLoop(int num);
void PrintFloatBits(float f);

#endif /*__EX1_H__*/


/*
#define UNUSED(x) (void)(x)
*/
