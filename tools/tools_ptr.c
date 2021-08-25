#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "tools.h"
#include "print_colores.h"

extern size_t err_count;
extern size_t count;

int PtrValidateEqual(void *d1, void *d2, const char *message, int line)
{
	++count;
	if (d1 != d2)
	{
		printf("%s %d\n", message, line);
		printf("ptr1 = %p, ptr2 = %p\n", (d1), (d2));
		++err_count;
		return 1;
	}

	return EXIT_SUCCESS;
}

int PtrValidateUnEqual(void *d1, void *d2, const char *message, int line)
{
	++count;
	if (d1 == d2)
	{
		printf("%s %d\n", message, line);
		printf("ptr1 = %p, ptr2 = %p\n", (d1), (d2));
		++err_count;
		return 1;
	}

	return EXIT_SUCCESS;
}
