#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "tools.h"

int ValidStrEqual(const char *str1, const char *str2, const char *message, int line)
{
	if (Validate(!strcmp(str1, str2), message, line))
	{
		printf("%s not equal ", str1);
		printf("%s \n", str2);

		return 1;
	}

	return EXIT_SUCCESS;
}

