#include "lut.h" /*the function declaration*/



/* Developer: Shelly Shlomi;
   Status: in development;   
   Description: InputOutput + LUT;*/
   
   
int getchar(void);


void InputOutput()
{	
	int c = 0;
	
	while ( 27 != c )
	{	
		c = getchar();
		
		if ( 65 == c ) 
		{
			printf( "A was pressd\n");
		}
		else if ( 84 == c )
		{
			printf( "T was pressd\n");
		}
	}	
	
	return;
}

