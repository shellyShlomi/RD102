#include <stdio.h>
#include <dlfcn.h>
#include "memory_map.h"

int global_var = 1;

static int global_static = 2;


void goo(void)
{
	int local_var = 7;
	static int local_var_static = 12;

	if (global_var)
	{
	 	printf("Hello from goo(), implicit\n");
		printf("local vars:\nlocal_var = %p\n", (void *)&local_var);
		printf("local_var_static = %p\n",(void *)&local_var_static);
   		printf("global vars:\nglobal_static = %p\n",(void *)&global_static);
   		printf("global_var = %p\n", (void *)&global_var);
	}
	else
	{
	 	printf("\t\tHello from goo(), explicit\n");
	 	printf("\t\tfunction: &goo = %p\n", goo);
   		printf("\t\tglobal_var = %p\n\n", (void *)&global_var);
	}
	
}
