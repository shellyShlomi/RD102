#include "ex2.h" /*the function declaration*/


int main(int argc, char **argv)
{	
	UNUSED(argc);
	
	if (NULL != argv[1]) /*If the user dident enter the file name */
	{
		Meneger(argv[1]);
	}
	

	return (0);
}
