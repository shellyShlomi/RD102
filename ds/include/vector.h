#ifndef __OL102_VECTOR_H__
#define __OL102_VECTOR_H__

#include <stddef.h> /* size_t */

typedef struct vector vector_t;

int       	VectorPushBack    (vector_t *vector, void *data);
void       	VectorPopBack     (vector_t *vector);
size_t      VectorSize        (const vector_t *vector);
size_t      VectorCapacity    (const vector_t *vector);
void      	*VectorGetElem    (const vector_t *vector, size_t index);
void      	VectorSetElem     (vector_t *vector, size_t index, void *data);
vector_t 	*VectorCreate     (size_t capacity);
void       	VectorDestroy     (vector_t *vector);
int       	VectorReserve     (vector_t *vector, size_t new_capacity);
int         VectorShrinkToFit (vector_t *vector);

#endif /* __OL102_VECTOR_H__ */


