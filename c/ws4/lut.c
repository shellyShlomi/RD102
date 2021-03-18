#include "lut.h" /*the function declaration*/

/* Developer: Shelly Shlomi;
   Status: aproved by EDEN.W;   
   Description: InputOutput + LUT;*/

#define ESC 27
#define SIZE 256

int getchar();
static void PrintA();
static void PrintT();
static void DontPrint();
static void Esc();  


        
void InputOutputIf()
{	
	char c = '\0';
	
	system("stty -icanon -echo");
	
	while ( ESC != c )
	{	
		c = getchar();
		
		if (EOF == c)
        { 
            puts("ERROR!");
            exit(1);
        }
        
		if ( 'a' == c || 'A' == c ) 
		{
			printf( "A pressed\n");
		}
		else if ( 't' == c || 'T' == c )
		{
			printf( "T pressed\n");
		}
	}	
	
	system("stty icanon echo");
	
	return;
}


void InputOutputSwich()
{	
	char c = '\0';
	
	system("stty -icanon -echo");
	
	while ( ESC != c )
	{	
		c = getchar();
		
		if (EOF == c)
        { 
            puts("ERROR!");
            exit(1);
        }
        
		switch (c)
		{	
			case 'A':
			{
				printf( "A pressed\n");
				break;
			}
			case 'a':
			{
				printf( "A pressed\n");
				break;
			}
			case 'T':
			{
				printf( "T pressed\n");
				break;
			}
			case 't':
			{
				printf( "T pressed\n");
				break;
			}
			default:
			{
				;
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
	void (*arrLut[SIZE])(void) = {0};

 	
	system("stty -icanon -echo");
	
	while (index < SIZE)
	{
		arrLut[index]= DontPrint;
		++index;
	}
	
	arrLut[ESC] = Esc;
	arrLut['A'] = PrintA;
	arrLut['T'] = PrintT;	
	arrLut['a'] = PrintA;
	arrLut['t'] = PrintT;
	

	while ( ESC != c )
	{			
 		c = getchar();
 		if (EOF == c)
        { 
            puts("ERROR!");
            exit(1);
        }
        
		(*arrLut[c])();	
	
	}
	
	(*arrLut[ESC])();
	
	
	return;			
}


static void PrintA()
{
	printf( "A pressed\n");
}

static void PrintT()
{
	printf( "T pressed\n");
}

static void DontPrint()
{
	;
}

static void Esc()
{	
	system("stty icanon echo");
	return;
}

