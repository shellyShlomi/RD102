#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

/* version 1.0 approved */

#include <stddef.h>
#include <sys/types.h> /*	ssize_t	*/

typedef struct circular_buffer c_buffer_t;


c_buffer_t *CBufferCreate(size_t capacity);
void CBufferDestroy(c_buffer_t *c_buffer);

ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count);
ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count);

int CBufferIsEmpty(const c_buffer_t *c_buffer);

size_t CBufferSiz(const c_buffer_t *c_buffer);
size_t CBufferFreeSpace(const c_buffer_t *c_buffer);

#endif /* __CIRCULAR_BUFFER_H__ */
