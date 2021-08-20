#include <iostream> /*  ostream */

#include "tools.h"
#include "print_colores.h"

extern size_t err_count;
extern size_t count;

template <class T>
void ValidData(T data)
{

	++count;
	if (!data)
	{
		std::cout<< "data is not valide"<< data<< std::endl;
		++err_count;
		return;
	}
		return;

	// return static_cast<void *>(a);
}

// void ValidData(void *data)
// {
// 	++count;
// 	if (!data)
// 	{
// 		std::cout<< "data is not valide"<< data<< std::endl);
// 		++err_count;
// 		return;
// 	}

// 	return;
// }
