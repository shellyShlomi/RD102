
#include <stdio.h>


void PrintHelloWorld(char arr[]);

int main()
{
    char arr[] = {0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 		0x21, 0x22, 0x0};
    
    PrintHelloWorld(arr);

    return 0;
}

void PrintHelloWorld(char arr[])
{
    printf("%s\n", arr);
}

