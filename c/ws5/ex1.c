#include <stdio.h>  /*for print*/

#define SIZE 10 

/* Developer: Shelly Shlomi 
   Status: approved by ohad;   
   Description: Struct*/
   
void MyPrintStruct();
void Print(int i);
                      
int main()
{  
	
	MyPrintStruct();

	return 0;
}

void MyPrintStruct()
{
	struct print_me 
	{ 
  		int x;
   		void (*ptr_print_func)(int); 
	};
	 
	struct print_me arr[SIZE] = {0};
	
	int i = 0; 

	while (i < SIZE)
	{
		arr[i].x = (SIZE + i);
	 	arr[i].ptr_print_func = Print;
		arr[i].ptr_print_func(arr[i].x);
		++i;
	}
}

void Print(int i)
{
	printf("%d\n", i);
	
}

