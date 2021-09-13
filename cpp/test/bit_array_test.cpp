
#include "bit_array.hpp"
#include "utilities_shared_pointer.hpp"
#include "tools.h"
#include <iostream>

using namespace utilities::utilities_shared_ptr_shelly;
using namespace ilrd;

/********************************** General **********************************/

void Test();

/*********************************** main ************************************/

int main()
{
	Test();
	return (0);
}

/*================================== General ================================*/

void Test()
{

	BitArray<> bitarr;
	BitArray<4> bitarr1;
	// bitarr1 = bitarr;//compile error!
	BitArray<4> bitarr2;
	bitarr1 = bitarr2;
	BitArray<> bitarr3(bitarr);
	const BitArray<> bitarr4(bitarr);

	for (size_t i = 0; i < 8; ++i)
	{

		if (true != (bitarr4[i]))
		{
			std::cout << bitarr4[i] << std::endl;
		}
	}

	std::cout << std::endl;
	std::cout << bitarr3[0] << std::endl;

	if (true == (bitarr3[0] = 1))
	{
		std::cout << bitarr3[0] << std::endl;
	}

	BitArray<> bitarr5;
	(bitarr[6] = 1);
	std::cout << bitarr[6] << std::endl;

	bitarr5[1] = bitarr5[2] = bitarr[6];

	std::cout << bitarr5[2] << std::endl;
	std::cout << bitarr5[1] << std::endl;

	// bitarr3 |= bitarr;
	TotalErrors();
	return;
}