
#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>

extern int iii;
static void implicit_call_func_in_f1(void);
static void explicit_call_func_in_f1(void);
extern void function_in_f1_file(void);

int main()
{
	 implicit_call_func_in_f1(); 
	//explicit_call_func_in_f1(); 

	printf("FROM MAIN: Value of iii is: %d;   Address of iii is: %p\n", iii, &iii);

	return 0;
}

void implicit_call_func_in_f1(void)
{
	printf("implicit_call_func_in_f1\n");
	function_in_f1_file();
}

void explicit_call_func_in_f1(void)
{
	printf("explicit_call_func_in_f1\n");
	void *handle;
	void (*fptr)(void);

	
	handle = dlopen("./libf1.so", RTLD_LOCAL | RTLD_LAZY);

	if(!handle)
	{
		perror("dlopen:");
	}

	fptr = dlsym(handle, "function_in_f1_file");
	(*fptr)();
}
