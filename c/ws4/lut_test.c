#include "lut.h" /*the function declaration*/
#include <stdlib.h> /*stty*/

int main()
{	
	system("stty -icanon -echo");
	InputOutput();
	system("stty icanon echo");
	return (0);
}
