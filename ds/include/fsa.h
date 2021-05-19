#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /* size_t */

typedef struct fsa fsa_t;

/* the mem_pool should be word aligned */
fsa_t *FSAInit(void *mem_pool, size_t pool_size, size_t inner_block_size); 

void *FSAAlloc(fsa_t *fsa);

void FSAFree(fsa_t *fsa, void *mem_block);

size_t FSASuggestSize(size_t num_of_blocks, size_t block_size);

size_t FSACountFree(const fsa_t *fsa);

#endif /* __FSA_H__ */



