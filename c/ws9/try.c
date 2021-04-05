#include <stdio.h>  /*for print*/
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

/*void *memset(void *s, int c, size_t n);*/
void *MemSet(void *s, int c, size_t n);

int main ()
{

char source[6]; 
char source1[6];
char dest1 = 'a';
char dest2 = 'a';


if (0 != memcmp(MemSet(source +1, dest2, 5), memset(source1 +1, dest1, 5), 5))
{
	printf("test failed");
}

return 0;
}


void *MemSet(void *s, int c, size_t n)
{


	char *ptr_s = NULL;
	size_t first_byte_c = 0x00000000FF;
	
	size_t mask = 0x00000000FFFFFFFF;
	
	size_t word_size = sizeof(size_t);
	
	char original_byte_c = 0;

	assert(NULL != s);

	ptr_s = (char * )s;

	first_byte_c &= c;

	original_byte_c = first_byte_c;

	while (0 != c)
	{
		c <<= 8;
			
		first_byte_c |= c; 
	}	
	
	mask = first_byte_c & mask;
	
	mask = mask | (first_byte_c << 32);
	
	
	
	while(0 < n && 0 != ((size_t)s % word_size))
	{
		*ptr_s = original_byte_c;
		++ptr_s;
		--n;
		
	}
	
	while(0 < (n / word_size))
	{
		*ptr_s = mask;
		ptr_s += word_size;
		n -= word_size;
	}
	
	
	while(0 < n)
	{
		*ptr_s = original_byte_c;
		++ptr_s;
		--n;
	}
	
return s;
}

