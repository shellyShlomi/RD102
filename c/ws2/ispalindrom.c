#include "ispalindrom.h" /*the function declaration*/

/* Developer: Shelly Shlomi 
   Status: aproved by ohad;   
   Description: distinguish palindrom pattern for characters*/




int IsPalindrom(char *str)
{
	size_t i = 0;
	size_t size = strlen(str);
	char *length = str + (size -1);

	
	if (0 == (*length)) /*the if stement is valid only if you 
						don't consider empty string as a palindrom*/
	{
		return 0;
	}
	
	while (i < (size / 2))
	{
		if (*str != *length)
		{
			return 0;
		}
		
		++str;
		--length;
		++i;
	}
	
	return 1;
}
