#include <stdio.h> /* printf */
#include <string.h> /*	strlen	*/
#include "circular_buffer.h"

#define CAPACITY 30

static void CBTest();


int main()
{
	CBTest();

	return 0;
}

static void CBTest()
{
	c_buffer_t *circular_buffer = CBufferCreate(CAPACITY);
	char *src = "shelly shlomi";
	char *src_orig = src;
	char dest[CAPACITY + CAPACITY] = {'\0'};

	size_t size_to_copy = 5;
	size_t size_to_read = 3;	
	size_t i = 1;
	size_t src_len = strlen(src);
	
	if (NULL == circular_buffer)
	{	
		printf("CBufferCreate error at line: %d\n", __LINE__);
		return ; 
	}	
	
	if (CAPACITY != CBufferSiz(circular_buffer))
	{
		printf("CBufferSiz error at line: %d\n", __LINE__);
	}
	
	if (1 != CBufferIsEmpty(circular_buffer))
	{
		printf("CBufferIsEmpty error at line: %d\n", __LINE__);
	}
	
	if (CAPACITY != CBufferFreeSpace(circular_buffer))
	{
		printf("CBufferFreeSpace error at line: %d\n", __LINE__);
	}
	
	while (size_to_copy * i <= CAPACITY)
	{
	
		src += size_to_copy;
		if (src_len < size_to_copy * i)
		{
			src = src_orig;
		}
		
		if ((ssize_t)size_to_copy != CBufferWrite(circular_buffer, src, size_to_copy))
		{
			printf("CBufferWrite error at line: %d at i : %lu \n",__LINE__, i);
		}
		
		++i;
	}
	
	if (0 != CBufferWrite(circular_buffer, src_orig, size_to_copy))
	{
		printf("CBufferWrite error at line: %d\n",__LINE__);
	}
	
		
	if (0 != CBufferFreeSpace(circular_buffer))
	{
		printf("CBufferIsEmpty error at line: %d\n", __LINE__);
	}
	
	
	i = 0;
	
	while (size_to_read * i <  CAPACITY)
	{
	
		if ((ssize_t)size_to_read != CBufferRead(circular_buffer, 
									dest + (size_to_read * i), size_to_read))
		{
			printf("CBufferRead error at line: %d at i : %lu\n",__LINE__, i);
		}
		
		++i;
	}
	
	if ((ssize_t)CAPACITY != CBufferFreeSpace(circular_buffer))
	{
		printf("CBufferFreeSpace error at line: %d\n", __LINE__);
	}
	
	
	if ((ssize_t)size_to_copy != CBufferWrite(circular_buffer, src, size_to_copy))
	{
		printf("CBufferWrite error at line: %d\n",__LINE__);
	}

	if ((ssize_t)size_to_read != CBufferRead(circular_buffer, dest, size_to_read))
	{
		printf("CBufferRead error at line: %d\n",__LINE__);
	}
	
	if ((ssize_t)size_to_copy != CBufferWrite(circular_buffer, src, size_to_copy))
	{
		printf("CBufferWrite error at line: %d\n",__LINE__);
	}
	
	if ((ssize_t)size_to_copy != CBufferWrite(circular_buffer, src, size_to_copy))
	{
		printf("CBufferWrite error at line: %d\n",__LINE__);
	}
	
	if ((ssize_t)(CAPACITY - CBufferFreeSpace(circular_buffer)) != 
				CBufferRead(circular_buffer, dest, size_to_copy * size_to_read))
	{
		printf("CBufferRead error at line: %d\n",__LINE__);
	}
	
	CBufferDestroy(circular_buffer);
	
	circular_buffer = NULL;
	
	
	return;	
}
