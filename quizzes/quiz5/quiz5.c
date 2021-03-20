#include <stdio.h>  /*for print*/
#include <assert.h> /*assert*/
#include <string.h> /*for strlen strncmp strchr*/

/* Developer: Shelly Shlomi 
   Status: done;   
   Description: Quiz5 - IsRotation */

void TestRotation();
int IsRotation(char *str1, char *str2);

int main()
{		
	TestRotation();
	
	return (0);
}

void TestRotation()
{	
	IsRotation("1235235","1235235");
	IsRotation("1233345","3345123");
	IsRotation("1233345","3451233");
	IsRotation("123345","3451233");
	IsRotation("1233345","345123");
	IsRotation("1245","3451233");
	IsRotation("","3451233");
	IsRotation("","");
	
	return;
}

int IsRotation(char *str1, char *str2)
{	
	size_t length_sub = 0;
	size_t length1 = 0;
	size_t length2 = 0;
	int comp = 1;
	int first_comp = 1;
	int second_comp = 1;
	char *sub_string = NULL;	/*last char in str1, first apperinc in
												str2 create the sub-strings*/
	assert(str1);
	assert(str2);
	
	length1 = strlen(str1);
	length2 = strlen(str2);
	comp = strcmp(str2, str1);
	
	if ( length1 != length2 )
	{	
		printf("NOT a Rotation\n");
		printf("\n"); 
		
		return 0;
	}
	else if   (0 == comp)
	{
		printf("IT'S a Rotation\n");
		printf("\n"); 
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 			return 1;
	}
	
	sub_string = strchr(str2 , str1[length1 - 1]) + 1;
	length_sub = strlen(sub_string); 
	
	if (NULL == sub_string)
	{	
		printf("NOT a Rotation\n");
		printf("\n"); 
		
		return 0;
	}
	
	first_comp = strncmp( sub_string, str1, length_sub );
	second_comp = strncmp( str2, (str1 + length_sub), (length1 - length_sub) );
											
	if (0 == second_comp && 0 == first_comp)
	{	
		printf("IT'S a Rotation\n");
		printf("\n"); 
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 			return 1;	
	}
	
	printf("NOT a Rotation\n"); 
	printf("\n"); 
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  		return 0;
}


