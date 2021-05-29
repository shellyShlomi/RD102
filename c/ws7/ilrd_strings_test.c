#include "ilrd_strings.h" /*the function declaration*/
#include <errno.h> 	/*strdup function*/
#include <strings.h> /*strcasecmp function*/

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
void TestStrSpn();

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
	/*printf("\nTest for StrStr\n\n");	
	TestStrStr();*/
	printf("\nTest for StrSpn\n\n");	
	TestStrSpn();


	
	return;
}

