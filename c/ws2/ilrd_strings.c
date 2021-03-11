#include "ilrd_strings.h" /*the function declaration*/

int StrCmp(const char *str1, const char *str2)
{
	assert(str1);
	assert(str2);

	while (('\0' != *str1) || ('\0' != *str2))
	{
		if (*str1 != *str2)
		{
			return *str1 - *str2;
		}
		++str1;
		++str2;
	}
	return 0;
}

size_t StrLen(const char *str)
{
	size_t counter = 0; /*counter to count the charecters in the string*/

	assert(str);

	while ('\0' != str[counter])
	{
		++counter;
	}

	return counter;
}

void TestFunction()
{
	char str[] = "";	                 /*to test an empty string*/
	char str_l[] = "longString";            /*to test an long string*/
	char str_s[] = "s";			  /*to test an short ASCII string*/
	char str_l1[] = "LongString";            /*cmp lower value ASCII string*/
	char str_l2[] = "LongString";            /*test idetical string*/

	/*test for strlen*/

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

	/*test for strcmp                    higher and lower value by ASCII*/

	/*comper to empty string*/
	if (strcmp(str, str_l) == StrCmp(str, str_l))
	{
		printf("YESSSSSS\n");
	}
	else
	{
		printf("ERROR\n");
	}
	/*comper lower value*/
	if (strcmp(str_l, str_l1) == StrCmp(str_l, str_l1))
	{
		printf("YESSSSSS\n");
	}
	else
	{
		printf("ERROR\n");
	}
	/*comper higher value*/
	if (strcmp(str_l, str_s) == StrCmp(str_l, str_s))
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

