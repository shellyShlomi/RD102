#include <iostream>


void func(int x, int i = 3, float = 4);
void func1(int x = 0, int = 4, float);

int main()
{
    func(1, 2.1);
    //func(1);//dd
    return (0);
}

void func(int x, int i, float z)
{
	std::cout <<i << std::endl;

}

