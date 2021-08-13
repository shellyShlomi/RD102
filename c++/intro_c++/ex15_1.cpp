#include <iostream>
#include <ostream>

#include "intro.hpp"


int main() 
{ 
    int arr[12]; 
 char i = 'd';
 char l = 'd';
    std::cout << Max<int>(3, 5) << " " << Max<double>(3.7, 12.9) << " ";
    std::cout << Max<char *>(&l,&i) << std::endl; 
    std::cout << Max<int*>(arr, arr + 8) << std::endl; 
    std::cout << Max<int*>(arr, arr + 8) << std::endl; 
    std::cout << Max<int*>(arr, arr + 8) << std::endl; 
    std::cout << Max<int*>(arr, arr + 8) << std::endl; 
    std::cout << Max<int*>(arr, arr + 8) << std::endl; 
    std::cout <<  Max("a", "b") << std::endl; 
    std::cout <<  Max("a", "b") << std::endl; 
    std::cout <<  Max("a", "b") << std::endl; 
    std::cout <<  Max("a", "b") << std::endl; 
    std::cout <<  Max("a", "b") << std::endl; 
    return 0; 
}