#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "tools.h"
#include "print_colores.h"

static size_t err_count = 0;
static size_t count = 0;

int Validate(int expression, const char *message, int line)
{
	++count;
	if (expression)
	{
		printf("%s %d\n", message, line);
		++err_count;
		return 1;
	}

	return EXIT_SUCCESS;
}

void TotalErrors(void)
{
	printf("Total tested: %s%ld", BLUE, count);
	printf("%s", RESET);

	printf(" | passed: %s%ld", GREEN, count - err_count);
	printf("%s", RESET);

	printf(" | failed: %s%ld\n", RED, err_count);
	printf("%s", RESET);

	return;
}





