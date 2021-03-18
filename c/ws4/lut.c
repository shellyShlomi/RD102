#include "lut.h" /*the function declaration*/

/* Developer: Shelly Shlomi;
   Status: in development;   
   Description: InputOutput + LUT;*/

int getchar(void);
void PrintA();
void PrintT();
void DontPrint();
void Esc();  



void InputOutputIf()
{	
	int c = 0;
	
	system("stty -icanon -echo");
	
	while ( 27 != c )
	{	
		c = getchar();
		
		if ( 65 == c || 97 == c ) 
		{
			printf( "A was pressd from if\n");
		}
		else if ( 84 == c || 116 == c )
		{
			printf( "T was pressd from if\n");
		}
	}	
	system("stty icanon echo");
	return;
}


void InputOutputSwich()
{	
	int c = 0;
	
	system("stty -icanon -echo");
	
	while ( 27 != c )
	{	
		c = getchar();
		
		switch (c)
		{	
			case 65:
			{
				printf( "A was pressd from swich\n");
				break;
			}
			case 84:
			{
				printf( "T was pressd from swich\n");
				break;
			}
			case 97:
			{
				printf( "A was pressd from swich\n");
				break;
			}
			case 116:
			{
				printf( "T was pressd from swich\n");
				break;
			}
			default:
			{
				;
				break;
			}
		}	
	}	
	system("stty icanon echo");
	return;
}


void InputOutputLut()
{		
	
	unsigned char c = '\0';
	size_t index = 0;
	void (*arrLut[256])(void) = {0};
	size_t size = 256;
 	
	system("stty -icanon -echo");
	
	while (index < size)
	{
		arrLut[index]= DontPrint;
		++index;
	}
	
	arrLut[27] = Esc;
	arrLut[65] = PrintA;
	arrLut[84] = PrintT;	
	arrLut[97] = PrintA;
	arrLut[116] = PrintT;
	

	while ( 27 != c )
	{			
 		c = getchar();
		(*arrLut[c])();	
	
	}
	
	(*arrLut[27])();
	
	
	return;			
}


void PrintA()
{
	printf( "A was pressd from LUT\n");
}

void PrintT()
{
	printf( "T was pressd from LUT\n");
}

void DontPrint()
{
	;
}

void Esc()
{	
	system("stty icanon echo");
	return;
}
