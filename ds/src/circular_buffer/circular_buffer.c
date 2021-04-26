
#include <assert.h> /*	assert	*/
#include <string.h> /*	memcpy	*/
#include <stdlib.h> /*	malloc	*/


#include "circular_buffer.h"

#define OFFSETOF(s, m)((size_t)&(((s *)0)->m))


struct circular_buffer
{
	size_t idx_read; /* idx = index */
	size_t cur_size; /* cur = currnet */
	size_t capacity;
	char arr[1];
};


c_buffer_t *CBufferCreate(size_t capacity)
{
	c_buffer_t *c_buf = NULL;
	
	assert(0 < capacity);
	
	c_buf = (c_buffer_t *)malloc(OFFSETOF(c_buffer_t, arr) + capacity);
	
	if (NULL == c_buf)
	{
		return NULL; 
	}

	c_buf->capacity = capacity;
	c_buf->cur_size = 0;
	c_buf->idx_read = 0;
	
	return c_buf;
}

void CBufferDestroy(c_buffer_t *c_buf)
{

	assert(NULL != c_buf);
		
	c_buf->cur_size = 0xFFFFFFFFFFFFFFFF;
	c_buf->capacity = 0;
	c_buf->idx_read = 0xFFFFFFFFFFFFFFFF;
	
	free(c_buf);

	return;
}

ssize_t CBufferWrite(c_buffer_t *c_buf, const void *src, size_t count)
{
	size_t idx_write = 0;
		
	size_t byte_to_write = 0;	
				 
	assert(NULL != c_buf);
	assert(NULL != src);
	
	idx_write = (c_buf->idx_read + c_buf->cur_size) % CBufferSiz(c_buf);

	if (count > CBufferFreeSpace(c_buf))
	{
		count = CBufferFreeSpace(c_buf);
	}
	
/*	chake if the capacity is smaller then the element we need to	* 
 *	write plus the cur writing index 								*/
 
	if (CBufferSiz(c_buf) < idx_write + count)
	{
		byte_to_write = CBufferSiz(c_buf) - idx_write;
		
		memcpy((c_buf->arr + idx_write), (char *)src, byte_to_write);	
		
		idx_write = 0;
	}

	memcpy(c_buf->arr + idx_write, (char *)src + byte_to_write, 
													count - byte_to_write);	

	c_buf->cur_size += count;					
	
	return count;
}


ssize_t CBufferRead(c_buffer_t *c_buf, void *dest, size_t count)
{
	size_t space_tile_end = CBufferSiz(c_buf) - c_buf->idx_read;
	size_t toggle = 0;
	
	assert(NULL != c_buf);
	assert(NULL != dest);
	
	if (count > c_buf->cur_size)
	{
		count = c_buf->cur_size;
	}
	
	if (count > space_tile_end)
	{	
		memcpy((char *)dest, c_buf->idx_read + c_buf->arr, space_tile_end);
		toggle = 1;
	}


	memcpy((char *)dest + (space_tile_end * toggle), c_buf->arr,
											count - (space_tile_end * toggle));

	c_buf->cur_size -= count;
	
	c_buf->idx_read = (count + c_buf->idx_read) % CBufferSiz(c_buf);
	
	return count;
}


int CBufferIsEmpty(const c_buffer_t *c_buf)
{
	assert(NULL != c_buf);
	
	return (0 == c_buf->cur_size);

}

size_t CBufferSiz(const c_buffer_t *c_buf)
{
	assert(NULL != c_buf);
	
	return (c_buf->capacity);
}
size_t CBufferFreeSpace(const c_buffer_t *c_buf)
{
	assert(NULL != c_buf);
	
	return (c_buf->capacity - c_buf->cur_size);
}

