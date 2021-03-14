#include "ilrd_strings.h" /*the function declaration*/

void TestFunction();
void TestStrLenAndStrCmp();
void TestStrCpy();	
void TestStrnCpy();
void TestStrCaseCmp();
void TestStrChr();
void TestStrDup();
void TestStrCat();
void TestStrnCat();
void TestStrStr();

int main()
{
	TestFunction();	
	return 0;
}



void TestFunction()
{
	printf("\nTest for StrLen\n\n");
	TestStrLenAndStrCmp(); 				
	printf("\nTest for StrCpy\n\n");
	TestStrCpy(); 						
	printf("\nTest for StrnCpy\n\n");
	TestStrnCpy(); 						
	printf("\nTest for StrCaseCmp\n\n");	
	TestStrCaseCmp();					
	printf("\nTest for StrChr\n\n");
	TestStrChr();						
	printf("\nTest for StrDup\n\n");	
	TestStrDup();						
	printf("\nTest for StrCat\n\n");	
	TestStrCat();						
	printf("\nTest for StrnCat\n\n");	
	TestStrnCat();
	printf("\nTest for StrStr\n\n");	
	TestStrStr();
	
	return;
}

void TestStrLenAndStrCmp()
{
	char str[] = "";			  /*to test an empty string*/
	char str_l[] = "longString";  /*to test an long string*/
	char str_s[] = "s";			  /*to test an short ASCII string*/
	char str_l1[] = "LongString"; /*cmp lower value ASCII string*/
	char str_l2[] = "LongString"; /*test idetical string*/

	/*test for StrLen*/

	if (strlen(str) == StrLen(str)) /*check empty string*/
	{
		printf("YESSSSSS\n");
	}
	else
	{
		printf("ERROR\n");
	}
	if (strlen(str_l) == StrLen(str_l)) /*check long string*/
	{
		printf("YESSSSSS\n");
	}
	else
	{
		printf("ERROR\n");
	}

	if (strlen(str_s) == StrLen(str_s)) /*check short string*/
	{
		printf("YESSSSSS\n");
	}
	else
	{
		printf("ERROR\n");
	}

	/*test for StrCmp                   	higher and lower value by ASCII*/
	printf("\nTest for StrCmp\n\n");
	/*comper to empty string*/
	if (strcmp(str, str_l) < 0 && StrCmp(str, str_l) < 0)
	{
		printf("YESSSSSS\n");
	}
	else
	{
		printf("ERROR\n");
	}
	/*comper lower value*/
	if (strcmp(str_l, str_l1) > 0 && StrCmp(str_l, str_l1) > 0 )
	{
		printf("YESSSSSS\n");
	}
	else
	{
		printf("ERROR\n");
	}
	/*comper higher value*/
	if (strcmp(str_l, str_s) < 0 && StrCmp(str_l, str_s) < 0)
	{
		printf("YESSSSSS\n");
	}
	else
	{
		printf("ERROR\n");
	}
	/*comper equal value*/
	if (strcmp(str_l1, str_l2) == StrCmp(str_l1, str_l2))
	{
		printf("YESSSSSS\n");
	}
	else
	{
		printf("ERROR\n");
	}
	
	return;
}


/*test for StrCpy*/

void TestStrCpy()
{
	int compre_my_function = 0;  /*to save the value from StrCpy*/
	int compre_original = 0; 	 /*to save the value from strcpy*/
	const char str[] = "";		 /*to test empty(only '\0') string as source*/
	char str_original[] = "sgvrsfbhgdf";/*destanetion for test empty(only'\0')*/
	char str_my_funcion[] = "sgvrsfbhgdf";/*destanetion for test empty('\0')*/
	/*destanetion arrays*/
	char result_my_function[][1000] = {"", "world", "Shelly"};
	char result_original[][1000] = {"", "world", "Shelly"};
	/*source array*/
	const char array_source[][7] = {"Shelly", "Sv", ""};

	size_t i = 0;
	
	/*the size of the array os strings*/
	size_t size = sizeof(result_my_function) / (sizeof(result_my_function[i]));

	/* test the copying of the source array into destanetion arrays*/
	while (i < size)
	{
		assert(StrCpy(result_my_function[i], array_source[i]));
		assert(strcpy(result_original[i], array_source[i]));
		
		compre_my_function = strcmp(result_my_function[i], array_source[i]);
		
		compre_original = strcmp(result_original[i], array_source[i]);
		
		if (compre_my_function == compre_original)
		{
			printf("YESSSSSS\n");
		}
		else
		{
			printf("ERROR\n");
		}

		++i;
	}
	/* test the copying of empty(only '\0') string as source*/
	if (*(StrCpy(str_my_funcion, str)) == (*(strcpy(str_original, str))))
	{
		printf("YESSSSSS\n");
	}
	else
	{
		printf("ERROR\n");
	}
	
	return;
}

void TestStrnCpy()
{
	size_t i = 0; /*indexing the string array*/
	size_t j = 0; /*indexing the char compertion*/
	int string_equlety = 0;
	size_t byte_to_copy = 6;/*the number of byte we want to copy*/
	const char str[] = "hhhhh";
	
	/*destanetion arrays*/
	char result_my_function[][30] = {"jdjdjdjjjjjjjj",
												"shellyworld", "hi", "Shelly"};
	char result_original[][30] = {"jdjdjdjjjjjjjj",
												"shellyworld", "hi", "Shelly"};

	/*source array*/
	const char array_source[][7] = {"Shelly", "hello ", "", "hdhd"};

	/*the size of the array os strings*/
	
	size_t string_array_size = sizeof(result_my_function) / 
												sizeof(result_my_function[i]);
											 
	size_t size_of_string = sizeof(result_my_function) / (string_array_size);

	/* test the copying of the source array into destanetion arrays*/
	
	while (i < string_array_size)
	{
		assert(StrnCpy(result_my_function[i], array_source[i], byte_to_copy));
		assert(strncpy(result_original[i], array_source[i], byte_to_copy));
		
		while ( j < size_of_string )
		{
			if ( result_my_function[i][j] != result_original[i][j] )
			{
				string_equlety = 1;
				break;
			}
			
			++j;
		}
		
		if ( 0 == string_equlety )
		{
			printf("YESSSSSS\n");
		}
		else
		{
			printf("ERROR\n");
		}
		
		string_equlety = 0;     /*restart j & string_equlety for the next loop*/
		j = 0;
		++i;
	}
	
	byte_to_copy = 20;
	
	/* test the copying with n lager then the source*/
	
	assert(StrnCpy(result_my_function[j], str, byte_to_copy));
	assert(strncpy(result_original[j], str, byte_to_copy));
	
	while ( j < size_of_string )
		{
			if ( result_my_function[0][j] != result_original[0][j] )
			{
				string_equlety = 1;
				break;
			}
			
			++j;
		}
		
		if ( 0 == string_equlety )
		{
			printf("YESSSSSS\n");
		}
		else
		{
			printf("ERROR\n");
		}	
	
	return;	
}	



/*test for StrCaseCmp*/
void TestStrCaseCmp()
{	
	size_t i = 0; /*indexing the string array*/
	const char array1[][10] = {"Long^tring", "WoRLD", "", "Shelly","world"};
	const char array2[][10] = {"LongString", "world", "Shelly", "","world"};
	
	size_t string_array_size = sizeof(array2) / sizeof(array2[i]);

	while (i < string_array_size)
	{
		if ((StrCaseCmp(array1[i], array2[i]) > 0 )&& 
										(strcasecmp(array1[i], array2[i]) > 0 ))
		{
			printf("YESSSSSS\n");
		}
		else if ((StrCaseCmp(array1[i], array2[i]) < 0 )&& 
										(strcasecmp(array1[i], array2[i]) < 0 ))
		{
			printf("YESSSSSS\n");
		}
		else if (StrCaseCmp(array1[i], array2[i]) == 
											   strcasecmp(array1[i], array2[i]))
		{
			printf("YESSSSSS\n");
		}
		else
		{
			printf("ERROR\n");
		}
		++i;
	}
	return;
}

void TestStrChr()
{	
	char strings_array[][20] = {"cCCCCCcccceccccc", "hellyworld", "dheh"};
	char chars_array[] = {'C', '\0', 'e'};

	size_t size = sizeof(chars_array);
	
	while (0 < size)
	{
		assert(strchr(strings_array[size - 1], chars_array[size - 1]));
		assert(StrChr(strings_array[size - 1], chars_array[size - 1]));
		
		switch (StrChr(strings_array[size - 1], chars_array[size - 1]) - 
						 strchr(strings_array[size - 1], chars_array[size - 1]))
		{	
			case 0:
			{
			printf("YESSSSSS\n");
				break;
			}
			default:
			{
				printf("ERROR\n");
				break;
			}
		}
		--size;
	}
	return;
}


void TestStrDup()
{	

	int comparison_my_and_source_string = 0;
	char strings_array[][5] = {"cccc", "hlrld","\0"};
	
	size_t size = sizeof(strings_array) / sizeof(strings_array[0]);

	char *ptr_my_function = NULL;

	
	
	while (0 < size)
	{
		ptr_my_function = StrDup(strings_array[size - 1]);

		assert(ptr_my_function);

		comparison_my_and_source_string = strcmp(strings_array[size - 1],
														      ptr_my_function); 

		switch (comparison_my_and_source_string)
		{	
			case 0:
			{
				printf("YESSSSSS\n");
				break;
			}
			default:
			{
				printf("ERROR\n");
				break;
			}
		}
		--size;
		
		free(ptr_my_function);
		ptr_my_function = NULL;
	}
	return;	
}

void TestStrCat()
{	
	/*destanetion arrays*/
	char result_my_function[][1000] = {"dfghdfhf", "hello ", "Shelly", ""};
	char result_original[][1000] = {"dfghdfhf", "hello ", "Shelly", ""};
	/*source array*/
	const char array_source[][10] = {"Shelly", "world", " shlomi", "1 2 3 4 5"};

	size_t size = sizeof(array_source) / sizeof(array_source[0]);
	
	while (0 < size)
	{
		assert(StrCat(result_my_function[size - 1], array_source[size - 1]));
		assert(strcat(result_original[size - 1], array_source[size - 1]));
		
		switch (strcmp(StrCat(result_my_function[size - 1], 
				  array_source[size - 1]), strcat(result_original[size - 1],
													   array_source[size - 1])))
		{	
			case 0:
			{
			printf("YESSSSSS\n");
				break;
			}
			default:
			{
				printf("ERROR\n");
				break;
			}
		}
		--size;
	}
	return;
}

void TestStrnCat()
{	
	/*destanetion arrays*/
	char result_my_function[][30] = {"fgdfdth\0hsgdgssgf", "Shelly", ""};
	char result_original[][30] = {"fgdfdth\0hsgdgssgf", "Shelly", ""};

	const char array_source[][10] = {"Shelly", " shlomi", "1 2 3 4 5" };

	size_t array_of_bytes[] = {3, 8, 10};
	
	size_t size = sizeof(array_source) / sizeof(array_source[0]);
	
	char *ptr_result_my_function = NULL;
	char *ptr_result_original = NULL;
	
	while (0 < size)
	{
		ptr_result_my_function = StrnCat(result_my_function[size - 1], 
							array_source[size - 1], array_of_bytes[size - 1]);
							
		ptr_result_original = strncat(result_original[size - 1],
							array_source[size - 1], array_of_bytes[size - 1]);
		
		assert(ptr_result_original);
		assert(ptr_result_my_function);
				   
		switch (*ptr_result_my_function - *ptr_result_original)
		{	
			case 0:
			{
			printf("YESSSSSS\n");
				break;
			}
			default:
			{
				printf("ERROR\n");
				break;
			}
		}
		--size;
	}
	return;
}



void TestStrStr()
{	
	char *compre_my_function = NULL;  /*to save the pointer from StrStr*/
	char *compre_original = NULL; 	 /*to save the pointer from strcpy*/
	const char array_source[][20] = {"hhhelhhhhellhh", "lo shloo\0mi"};

	char array_needle[][4] = {"ell", "loo", ""};
	
	size_t size = sizeof(array_needle) / sizeof(array_needle[0]);
	
	while (0 < size)
	{
		assert(strstr(array_source[size - 1], array_needle[size - 1]));
		assert(StrStr(array_source[size - 1], array_needle[size - 1]));
				   
		switch (StrStr(array_source[size - 1], array_needle[size - 1]) -
  					    strstr(array_source[size - 1], array_needle[size - 1]))
		{	
			case 0:
			{
				printf("YESSSSSS\n");
				break;
			}
			default:
			{
				printf("ERROR\n");
				break;
			}
		}
		--size;
	}
	
	compre_my_function = StrStr("aaaa","b");
	compre_original = strstr("aaaa","b");

	switch (compre_original - compre_my_function)
		{	
			case 0:
			{
				printf("YESSSSSS\n");
				break;
			}
			default:
			{
				printf("ERROR\n");
				break;
			}
		}
	return;
}





