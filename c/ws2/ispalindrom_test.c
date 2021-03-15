#include "ispalindrom.h" /*the function declaration*/


void TestIsPalindrom();

int main()
{

	TestIsPalindrom();
	return 0;
}



void TestIsPalindrom()
{
	char strings_array[][12] = {"hhjykyjhh", "hfggfh", "hfgggfh", "",
														 "ksdjskfh", "hh", "i"};
	int array_exe_answer[] = {1, 1, 1, 0, 0, 1, 1};
	size_t size = sizeof(strings_array) / sizeof(strings_array[0]);	
	int i=0;

	while (0 < size)
		{		i=IsPalindrom(strings_array[size - 1]);   
			if (IsPalindrom(strings_array[size - 1]) == 
													array_exe_answer[size - 1])
			{		
				
				printf("YESSSSSS\n");
				
			}
			else
			{
				printf("ERROR\t value returnd:%d\t for the string %s\n"
												 , i, strings_array[size - 1]);	
			}
			
			--size;
		}
		
	return;
}



