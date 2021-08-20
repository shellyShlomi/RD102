#include <iostream>     /* malloc, free, rand */
#include <dlfcn.h>

#include "such_shared.h"

typedef int (*func_ptr_t)(int);


int main(void)
{
    int ab = 5;
    /*void *handle = dlopen("./libsuch_shared.so", RTLD_LAZY);
    if(handle == NULL)
    {
        std::cout << "dlopen error";
        return 1;
    }  
    int (*function_ptr)(int);

    function_ptr = (func_ptr_t)dlsym(handle, "foo");

    if(function_ptr == NULL)
    {
        std::cout << "dlsym error";
        return 1;
    }  

    function_ptr(ab);
*/
    foo(ab);

    return 0;
}