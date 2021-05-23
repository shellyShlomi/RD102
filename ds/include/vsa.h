#ifndef __OL102_VSA_H__
#define __OL102_VSA_H__

#include <stddef.h> /* size_t */

typedef struct vsa vsa_t;


vsa_t *VSAInit(void *mem_pool, size_t pool_size);

void *VSAAlloc(vsa_t *vsa, size_t n_bytes);

void VSAFree(void *mem_chunck); 

size_t VSALargestChunkAvailable(vsa_t *vsa); /* -> here we call VSADefragment */

#endif /* __OL102_VSA_H__ */

