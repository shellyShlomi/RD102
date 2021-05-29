#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "memory_map.h"



static void foo();
void boo();


int i = 7;
static int j = 12;



int main(int argc, char **argv, char **envp)
{
	char *env = envp[0];
	
	char *arg = argv[0];
	
	void (*func)(void) = NULL;
	void *var_glob = NULL;
	
	void *handle = NULL;
	
	(void)env;
	(void)arg;
	(void)argc;
	(void)j;
	(void)i;
	boo();
	foo();
/*	
	printf("---------------------inplicit dynamic linking; shared library-------------------\n\n");

	goo();
*/
	printf("\n---------------------explicit dynamic linking; shared library-------------------\n\n");
	
	handle = dlopen("/home/shelly/git/system_programming_memory_map/libmemory_map.so", RTLD_LAZY);
	
	if (NULL == handle)
	{
		printf("handle == NULL\n");
		return 0;	
	}

	*(void **)&func = dlsym(handle, "goo");
	
	if (NULL == func)
	{
		printf("func1 == NULL\n");
		return 0;	
	}

	var_glob = dlsym(handle, "global_var");
	
	if (NULL == var_glob)
	{
		printf("var_glob == NULL\n");
		return 0;	
	}
	
	*(int *)var_glob = 0;
	
	printf("\t\t---------------------from main---------------------\n\n");
	
	printf("\t\tfunction: &func = %p\n", func);

	printf("\t\tvar_glob = %p\n\n", dlsym(handle, "global_var"));
	
	printf("\t\t---------------------from goo---------------------\n\n");
		
	func(); 

	dlclose(handle);	
	
	return 0;
}


static void foo()
{
	int x = 7;
	char *str = "shelly";
	char char_arr[] = "SHELLY";
	
	int x1 = 7;
	char *str1 = "shelly";
	char char_arr1[] = "SHELLY";
	
	const int c_x = 7;
	const char *c_str = "shelly";
	const char c_char_arr[] = "SHELLY";

	(void)x;
	(void)str;
	(void)char_arr;
	(void)x1;
	(void)str1;
	(void)char_arr1;
	(void)c_x;
	(void)c_str;
	(void)c_char_arr;
	
	return ;
}


void boo()
{

	int b = 7;
	static int a = 12;
	int c = 15;
	int *ptr = (int *)malloc(16);
	
	int b1 = 7;
	static int a1 = 12;
	int c1 = 15;
	int *ptr1 = (int *)malloc(16);
	
	const int c_b = 7;
	const int c_c = 15;
	const int *c_ptr = (int *)malloc(16);
	

	(void)a;
	(void)b;
	(void)c;
	(void)ptr;
	(void)a1;
	(void)b1;
	(void)c1;
	(void)ptr1;
	(void)c_b;
	(void)c_c;
	(void)c_ptr;
	
	free(ptr);
	free(ptr1);

	return ;

}

