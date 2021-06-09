#ifndef OL_102_RECURSION_H
#define OL_102_RECURSIONR_H
#include <stddef.h> /* size_t */
#include "stack.h"

typedef struct node node_t;
/* 
struct node
{
    void *data;
    struct node *next;
};
 */
int RecursiveFibonacci(int element_index);
int IterativeFibonacci(int element_index);
node_t *FlipList(node_t *node);
void StackSort(stack_t *stack);
size_t StrLen(const char *s);
int StrCmp(const char *s1, const char *s2);
char *StrCpy(char *dest, const char *src);
char *StrCat(char *dest, const char *src);
char *StrStr(const char *haystack, const char needle);

#endif / OL_102_RECURSION_H */
﻿
