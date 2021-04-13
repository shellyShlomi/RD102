#ifndef __EX_H__
#define __EX_H__

#include <stddef.h> /* size_t */

void *MemSet(void *s, int c, size_t n);
void *MemCpy(void *dest, const void *src, size_t n);
void *MemMove(void *dest, const void *src, size_t n);

#endif /*__EX_H__*/
