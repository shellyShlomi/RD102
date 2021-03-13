#include "ilrd_strings.h" /*the function declaration*/

int main()
{
	TestFunction();	
	return 0;
}



void TestFunction()
{
	printf("\nTest for StrLen\n\n");
	TestStrLenAndStrCmp(); 				/*test for StrLen & StrCmp*/
	printf("\nTest for StrCpy\n\n");
	TestStrCpy(); 						/*test for StrCpy*/
	printf("\nTest for StrnCpy\n\n");
	TestStrnCpy(); 						/*test for StrCpy*/
	printf("\nTest for StrCaseCmp\n\n");	
	TestStrCaseCmp();					/*test for StrCaseCmp*/
	printf("\nTest for StrChr\n\n");
	TestStrChr();						/*test for StrChr*/
	printf("\nTest for StrDup\n\n");	
	TestStrDup();						/*test for StrChr*/
	
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
		StrCpy(result_my_function[i], array_source[i]);
		strcpy(result_original[i], array_source[i]);
		
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
		StrnCpy(result_my_function[i], array_source[i], byte_to_copy);
		strncpy(result_original[i], array_source[i], byte_to_copy);
		
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
	
	StrnCpy(result_my_function[j], str, byte_to_copy);
	strncpy(result_original[j], str, byte_to_copy);
	
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
		switch (StrCaseCmp(array1[i], array2[i]) - 
											   strcasecmp(array1[i], array2[i]))
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
		++i;
	}

}

void TestStrChr()
{	
	char strings_array[][20] = {"cCCCCCcccccccccc", "hellyworld"};
	char chars_array[] = {'C', '\0'};

	size_t size = sizeof(chars_array);
	
	while (0 < size)
	{
		assert(strchr(strings_array[size-1], chars_array[size-1]));
		assert(StrChr(strings_array[size-1], chars_array[size-1]));
		
		switch (StrChr(strings_array[size-1], chars_array[size-1]) - 
											   strchr(strings_array[size-1], chars_array[size-1]))
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

}



void TestStrDup()
{	
	int comparison_my_and_original = 0;
	int comparison_my_and_source_string = 0;
	char strings_array[][5] = {"cccc", "hlrld"};
	
	size_t size = sizeof(strings_array) / sizeof(strings_array[0]);

	char *ptr_my_function = NULL;
	char *ptr_origenal = NULL;
	
	
	while (0 < size)
	{
		ptr_my_function = StrDup(strings_array[size-1]);
		ptr_origenal = strdup(strings_array[size-1]);
		assert(ptr_my_function);
		assert(ptr_origenal);
		
		comparison_my_and_original = strcmp(ptr_origenal, ptr_my_function); 
		comparison_my_and_source_string = strcmp(strings_array[size-1],
															   ptr_my_function); 
				
		switch (comparison_my_and_original)
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
		
		free(ptr_origenal);
		ptr_origenal = NULL;
		free(ptr_my_function);
		ptr_my_function = NULL;
	}
	
}



