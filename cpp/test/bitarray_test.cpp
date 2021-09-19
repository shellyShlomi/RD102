
#include <iostream>
#include <string> // std::string, std::to_string
#include <cstdio> // Pars

#include "bitarray.hpp"
#include "bitarray_detail.hpp"
#include "tools.h"
//TODO:

using namespace ilrd;
namespace utilities
{
	static const int SIZE_BYTE = 8;
	static const int SIZE_EVEN_MORE_THEN_BYTE = 12;
	static const int SIZE_EVEN_LESS_THEN_BYTE = 4;
	static const int SIZE_ODD_LESS_THEN_BYTE = 7;
	static const int SIZE_ODD_MORE_THEN_BYTE = 13;
	static const int NUM_OF_SIZES = 5;

	enum ctor
	{
		CTOR,
		CCTOR
	};

	template <class T>
	char *Pars(char *buff, const char *formet, T data)
	{
		std::sprintf(buff, formet, data);

		return (buff);
	}

} //utilities

/********************************** General **********************************/
static void TestCtorAndDtor();
static void TestAssingment();
static void TestBitArray();
static void TestOperators();
static void TestFlipBitAndFlipAll();
static void TestToString();
static void TestEqual();
static void TestCount();
static void TestSetAndSetAll();
static void TestGetBit();

static char *GetMessageFlipAll(bool bit, bool real);
static char *GetMessageFlipBit(bool bit, bool real);

static const char *GetMessageSetBit(bool bit, bool real);
static const char *GetMessageSetBitException(int val, size_t reang);

static const char *GetMessageSetAll(bool bit, bool real);
static const char *GetMessageSetAllDafult(bool bit, bool real);

static char *GetMessageGetBit(bool bit, bool real);
static const char *GetMessageGetBitException(int val, size_t reang);

static const char *GetMessageEqualOperator(bool bit1, bool bit2, size_t i);
static const char *GetMessageUnEqualOperator(bool bit1, bool bit2, size_t i);
static const char *GetMessageCount(BitArray<utilities::SIZE_EVEN_MORE_THEN_BYTE> &bit, size_t n_true);

static const char *GetMessageCtor(int mesg, size_t size);

/*********************************** main ************************************/

int main()
{
	TestCtorAndDtor();
	TestAssingment();
	TestBitArray();
	TestOperators();
	TestGetBit();
	TestSetAndSetAll();
	TestFlipBitAndFlipAll();
	TestEqual();
	TestCount();
	TestToString();
	
	TotalErrors();

	return (0);
}

/*================================== General ================================*/
static void TestCtorAndDtor()
{
	bool arr_test[] = {true, false, true, true, false, false, false, true, false, true, true, false};

	BitArray<> bitarr;
	for (size_t i = 0; i < utilities::SIZE_BYTE; ++i)
	{
		Valid(bitarr.GetBit(i) == false,
			  "TestCtorAndDtor Fail: \n\
			  dafult Ctoe and dauflt param faild ",
			  __LINE__);

		bitarr[i] = arr_test[i];
	}

	BitArray<utilities::SIZE_EVEN_LESS_THEN_BYTE> bitarr1;
	// bitarr1 = bitarr;//compile error!
	for (size_t i = 0; i < utilities::SIZE_EVEN_LESS_THEN_BYTE; ++i)
	{
		size_t size = utilities::SIZE_EVEN_LESS_THEN_BYTE;
		Valid(bitarr1.GetBit(i) == false, GetMessageCtor(utilities::CTOR, size), __LINE__);
	}
	BitArray<> bitarr2(bitarr);
	for (size_t i = 0; i < utilities::SIZE_BYTE; ++i)
	{
		size_t size = utilities::SIZE_BYTE;
		Valid(bitarr2.GetBit(i) == arr_test[i], GetMessageCtor(utilities::CCTOR, size), __LINE__);
		Valid(bitarr2.GetBit(i) == bitarr.GetBit(i), GetMessageCtor(utilities::CCTOR, size), __LINE__);
	}

	return;
}

static void TestAssingment()
{
	bool arr_test[] = {true, false, true, true, false, false, false, true, false, true, true, false};

	BitArray<utilities::SIZE_EVEN_MORE_THEN_BYTE> b;
	
	for (size_t i = 0; i < utilities::SIZE_EVEN_MORE_THEN_BYTE; ++i)
	{
		Valid(b.GetBit(i) == false,
			  "TestAssingment Fail: \n 	Ctor",
			  __LINE__);

		b[i] = arr_test[i];
	}

	BitArray<utilities::SIZE_EVEN_MORE_THEN_BYTE> b1;
	b1 = b;

	for (size_t i = 0; i < utilities::SIZE_EVEN_MORE_THEN_BYTE; ++i)
	{
		Valid(b1[i] ==  arr_test[i],
			  "TestAssingment Fail: \n 	b1 = b \n",
			  __LINE__);
	}

	BitArray<utilities::SIZE_EVEN_MORE_THEN_BYTE> b2;
	b1 = b = b2;
	for (size_t i = 0; i < utilities::SIZE_EVEN_MORE_THEN_BYTE; ++i)
	{
		Valid(b.GetBit(i) == false,
			  "TestAssingment Fail: \n 	b1 = b = b2 \n",
			  __LINE__);
	}

	return;
}

static void TestBitArray()
{
	bool arr_test[] = {true, false, true, true, false, false, false, true, false, true, true, false};

	BitArray<> b1;
	for (size_t i = 0; i < utilities::SIZE_BYTE; ++i)
	{
		Valid(b1[i] == false,
			  "\n\nTestBitArray Fail: \noperator[] ",
			  __LINE__);
		b1[i] = arr_test[i];
		Valid(b1[i] == arr_test[i],
			  "\n\nTestBitArray Fail: \nb1[i] = arr_test[i] ",
			  __LINE__);
	}

	b1.SetAll(false);
	for (size_t i = 0; i < utilities::SIZE_BYTE; ++i)
	{
		Valid(false == b1[i],
			  "\n\nTestBitArray Fail: \n\
			  bitarr.SetAll(false) failed",
			  __LINE__);
	}
	bool arr_test1[utilities::SIZE_BYTE] = {0};
	size_t val = 5;

	Valid(true == (b1[val] = arr_test1[val] = true),
		  "\n\nTestBitArray Fail: \n\
			  true == (bitarr[val] = arr_test1[val] = true)",
		  __LINE__);

	for (size_t i = 0; i < utilities::SIZE_BYTE; ++i)
	{
		Valid(b1[i] == arr_test1[i],
			  "\n\nTestBitArray Fail: \n\
			  bitarr[i] == arr_test1[i]",
			  __LINE__);
	}
	const BitArray<> bitarr1(b1);

	for (size_t i = 0; i < 8; ++i)
	{
		Valid(bitarr1[i] == arr_test1[i], "\n\nTestBitArray Fail: \n\
		const operator[]\n",
			  __LINE__);
		Valid(bitarr1[i] == b1[i], "\n\nTestBitArray Fail: \n\
		const operator[]\n",
			  __LINE__);
	}
	//NOTE: compile error! - assingment to non lvalue!
	// bitarr1[val] = b1[val];

	BitArray<> b2;
	BitArray<> b3;
	size_t val1 = 5;
	size_t val2 = 3;
	size_t val3 = 7;

	b3[val3] = false;

	Valid(false == b3[val3],
		  "\n\nTestBitArray Fail: \nb3[val3] = false", __LINE__);

	b1[val1] = b2[val2] = b3[val3];

	Valid(((false == b1[val1]) && (false == b2[val2]) && (false == b3[val3])),
		  "\n\nTestBitArray Fail: \nb1[val1] = b2[val2] = b3[val3]",
		  __LINE__);

	return;
}

static void TestOperators()
{
	const size_t SIZE = 130;

	BitArray<SIZE> b1;
	BitArray<SIZE> b2;
	BitArray<SIZE> b_zero;
	BitArray<SIZE> b_allset;
	b_allset.SetAll();
	b_zero.SetAll(false);

	for (size_t i = 0; i < SIZE; ++i)
	{
		b1[i] = true;
	}

	BitArray<SIZE> b3;

	b3 |= b2 |= b1;

	Valid(b_allset == b2, "b2 |=", __LINE__);
	Valid(b_zero != b2, "b2 |=", __LINE__);
	Valid(b_allset == b3, "b3 |=", __LINE__);
	Valid(b_zero != b3, "b3 |=", __LINE__);

	b1.SetAll(false);

	b3 &= b2 &= b1;

	Valid(b_zero == b2, "b2 &=", __LINE__);
	Valid(b_zero == b3, "b3 &=", __LINE__);

	const size_t idx_arr[] = {5, 8, 12, 31, 87};
	const size_t SIZE_IDXARR = (sizeof(idx_arr) / sizeof(idx_arr[0]));

	for (size_t i = 0; i < SIZE_IDXARR; i++)
	{
		b1.SetBit(idx_arr[i]);
	}

	b3 ^= b2 ^= b1;

	for (size_t j = 0, i = j; i < SIZE_IDXARR; i++)
	{
		if (j < SIZE_IDXARR && i == idx_arr[j])
		{
			Valid(true == b2[idx_arr[j]], "true b2 ^=", __LINE__);
			Valid(true == b3[idx_arr[j]], "true b3 ^=", __LINE__);
			++j;
			continue;
		}
		Valid(false == b2[i], "false b2 ^=", __LINE__);
		Valid(false == b3[i], "false b3 ^=", __LINE__);
	}

	b2 &= b1;
	for (size_t j = 0, i = j; i < SIZE; i++)
	{
		if (j < SIZE_IDXARR && i == idx_arr[j])
		{
			Valid(true == b2[idx_arr[j]], "true &=", __LINE__);
			++j;
			continue;
		}
		Valid(false == b2[i], "false &=", __LINE__);
	}

	b2 &= b_zero;

	Valid(b_zero == b2, "&=", __LINE__);

	b2 |= b1;

	for (size_t j = 0, i = j; i < SIZE; i++)
	{
		if (j < SIZE_IDXARR && i == idx_arr[j])
		{
			Valid(true == b2[idx_arr[j]], "true |=", __LINE__);
			++j;
			continue;
		}
		Valid(false == b2[i], "false |=", __LINE__);
	}

	return;
}

static void TestGetBit()
{
	BitArray<utilities::SIZE_BYTE> b1;
	bool arr_test[] = {true, false, true, true, false, false, false, false};

	for (size_t i = 0; i < utilities::SIZE_BYTE; ++i)
	{
		b1[i] = arr_test[i];
		Valid(b1.GetBit(i) == arr_test[i], "assigment fail ", __LINE__);
	}

	for (size_t i = 0; i < utilities::SIZE_BYTE; ++i)
	{
		Valid(b1.GetBit(i) == arr_test[i], GetMessageGetBit(b1.GetBit(i), arr_test[i]), __LINE__);
	}

	int val = 19;
	try
	{
		b1.GetBit(val);
	}
	catch (const std::exception &e)
	{
		Valid(
			0 == std::strncmp("out_of_range", e.what(), std::strlen("out_of_range")),
			GetMessageGetBitException(val, utilities::SIZE_BYTE),
			__LINE__);
	}
	return;
}

static void TestSetAndSetAll()
{
	BitArray<> ba;
	bool arr_test_end[] = {true, true, false, true, true, true, true, true};
	bool arr_test[] = {true, false, true, true, false, false, false, false};

	for (size_t i = 0; i < utilities::SIZE_BYTE; ++i)
	{
		ba[i] = arr_test[i];
		Valid(ba.GetBit(i) == arr_test[i], "assigment fail ", __LINE__);
	}

	ba.SetAll(false);
	for (size_t i = 0; i < utilities::SIZE_BYTE; ++i)
	{
		Valid(ba[i] == false, GetMessageSetAll(ba[i], false), __LINE__);
	}

	ba.SetAll();
	for (size_t i = 0; i < utilities::SIZE_BYTE; ++i)
	{

		Valid(ba[i] == true, GetMessageSetAllDafult(ba.GetBit(i), true), __LINE__);
	}
	int val = 2;

	ba.SetBit(val, false);
	for (size_t i = 0; i < utilities::SIZE_BYTE; ++i)
	{
		Valid(ba.GetBit(i) == arr_test_end[i], GetMessageSetBit(ba.GetBit(i), arr_test_end[i]), __LINE__);
	}
	val = 9;
	try
	{
		ba.SetBit(val, true);
	}
	catch (const std::exception &e)
	{
		Valid(
			0 == std::strncmp("out_of_range", e.what(), std::strlen("out_of_range")),
			GetMessageSetBitException(val, utilities::SIZE_BYTE),
			__LINE__);
	}

	val = 3;
	ba.SetAll(false);
	Valid(ba[val] == false, GetMessageSetBit(ba[val], false), __LINE__);
	ba.SetBit(val, true);
	Valid(ba[val] == true, GetMessageSetBit(ba[val], true), __LINE__);

	val = 7;
	ba.SetAll(false);
	Valid(ba[val] == false, GetMessageSetBit(ba[val], false), __LINE__);
	ba.SetBit(val, true);
	Valid(ba[val] == true, GetMessageSetBit(ba[val], true), __LINE__);
}

static void TestFlipBitAndFlipAll()
{
	BitArray<utilities::SIZE_BYTE> b1;

	bool arr_test[] = {true, false, true, true, false, false, false, false};

	for (size_t i = 0; i < utilities::SIZE_BYTE; ++i)
	{
		b1[i] = arr_test[i];
		Valid(b1.GetBit(i) == arr_test[i], "assigment fail ", __LINE__);
	}

	b1.FlipAll();
	for (size_t i = 0; i < utilities::SIZE_BYTE; ++i)
	{
		try
		{
			Valid(b1.GetBit(i) != arr_test[i], GetMessageFlipAll(b1.GetBit(i), arr_test[i]), __LINE__);
		}
		catch (const std::exception &e)
		{
			std::strncmp("out_of_range", e.what(), std::strlen("out_of_range"));
		}
	}

	for (size_t i = 0; i < utilities::SIZE_BYTE; ++i)
	{
		try
		{
			b1.FlipBit(i);
			Valid(b1[i] == arr_test[i], GetMessageFlipBit(b1[i], arr_test[i]), __LINE__);
		}
		catch (const std::exception &e)
		{
			std::strncmp("out_of_range", e.what(), std::strlen("out_of_range"));
		}
	}
}

static void TestEqual()
{
	BitArray<utilities::SIZE_EVEN_MORE_THEN_BYTE> b1;
	BitArray<utilities::SIZE_EVEN_MORE_THEN_BYTE> b2;

	bool arr_test[] = {true, false, true, true, false, false, false, true, false, true, true, false};

	for (size_t i = 0; i < utilities::SIZE_EVEN_MORE_THEN_BYTE; ++i)
	{
		b1[i] = arr_test[i];
		b2[i] = arr_test[i];

		Valid(b1[i] == arr_test[i], "b1\n", __LINE__);
		Valid(b2[i] == arr_test[i], "b2\n", __LINE__);
	}

	// if (Valid(b1 == b2, "fail operator== ", __LINE__))
	{
		for (size_t i = 0; i < utilities::SIZE_EVEN_MORE_THEN_BYTE; ++i)
		{
			Valid(b1[i] == b2[i], GetMessageEqualOperator(b1[i], b2[i], i), __LINE__);
		}
	}

	for (size_t i = 0; i < utilities::SIZE_EVEN_MORE_THEN_BYTE; ++i)
	{
		b1[i] = !arr_test[i];

		Valid(b1[i] == !arr_test[i], "b1\n", __LINE__);
	}

	if (Valid(b1 != b2, "fail operator!= ", __LINE__))
	{
		for (size_t i = 0; i < utilities::SIZE_EVEN_MORE_THEN_BYTE; ++i)
		{
			Valid(b1[i] != b2[i], GetMessageUnEqualOperator(b1[i], b2[i], i), __LINE__);
		}
	}
}

static void TestCount()
{
	BitArray<utilities::SIZE_EVEN_MORE_THEN_BYTE> b1;

	bool arr_test[] = {true, false, true, true, false, false, false, true, false, true, true, false};
	size_t n_true = 0;
	size_t n_false = 0;

	for (size_t i = 0; i < utilities::SIZE_EVEN_MORE_THEN_BYTE; ++i)
	{
		b1[i] = arr_test[i];

		if (arr_test[i])
		{
			++n_true;
		}
		else
		{
			++n_false;
		}
		Valid(b1[i] == arr_test[i], "b1\n", __LINE__);
	}

	Valid((n_true == b1.Count()), GetMessageCount(b1, n_true), __LINE__);
}

static void TestToString()
{
	BitArray<utilities::SIZE_BYTE> b1;

	char message[detail::BYTE_MAX] = {'\0'};

	strcpy(message, "fail ToString");
	b1.SetAll();
	ValidStrEqual(b1.ToString().c_str(), "11111111", message, __LINE__);

	strcpy(message, "fail ToString b1.SetBit(3)");
	b1.SetBit(3, false);
	ValidStrEqual(b1.ToString().c_str(), "11110111", message, __LINE__);

	return;
}

static char *GetMessageFlipAll(bool bit, bool real)
{
	static char message[detail::BYTE_MAX] = {'\0'};
	strcpy(message, "\n\n");
	strcpy(message + strlen(message), "FlipAll:\n");

	static const char *cstr = (bit) ? " bit is : true\n" : "bit is : false\n";
	strcpy(message + strlen(message), cstr);
	cstr = (real) ? "arr_test is : true\n" : "arr_test is : false\n";
	strcpy(message + strlen(message), cstr);

	return (message);
}

static char *GetMessageFlipBit(bool bit, bool real)
{
	static char message[detail::BYTE_MAX] = {'\0'};
	strcpy(message, "\n\n");
	strcpy(message + strlen(message), "FliBit:\n");

	static const char *cstr = (bit) ? "bit is : true\n" : "bit is : false\n";
	strcpy(message + strlen(message), cstr);
	cstr = (real) ? "arr_test is : true\n" : "arr_test is : false\n";
	strcpy(message + strlen(message), cstr);

	return (message);
}

static char *GetMessageGetBit(bool bit, bool real)
{
	static char message[detail::BYTE_MAX] = {'\0'};
	strcpy(message, "\n\n");
	strcpy(message + strlen(message), "GetBit:\n");

	static const char *cstr = (bit) ? "bit is : true\n" : "bit is : false\n";
	strcpy(message + strlen(message), cstr);
	cstr = (real) ? "arr_test is : true\n" : "arr_test is : false\n";
	strcpy(message + strlen(message), cstr);

	return (message);
}

static const char *GetMessageGetBitException(int val, size_t reang)
{

	static std::string message = "\n\n";
	char buff[detail::BYTE_MAX] = {'\0'};
	message.append("GetBit\n ");

	message.append("the value :");
	message.append(utilities::Pars(buff, "%d", val));
	message.append(" is not inr the reang of: ");
	message.append(utilities::Pars(buff, "%lu", reang));

	return (message.c_str());
}

static const char *GetMessageSetBit(bool bit, bool real)
{

	static std::string message = "\n\n";
	char buff[detail::BYTE_MAX] = {'\0'};
	message.append("SetBit\n ");

	message.append("bit is : ");
	message.append(utilities::Pars(buff, "%d", bit));
	message += "\n";
	message.append("arr_test is : ");
	message.append(utilities::Pars(buff, "%d", real));

	return (message.c_str());
}

static const char *GetMessageSetBitException(int val, size_t reang)
{
	static std::string message = "\n\n";
	char buff[detail::BYTE_MAX] = {'\0'};
	message.append("SetBit\n ");

	message.append("the value :");
	message.append(utilities::Pars(buff, "%d", val));
	message.append(" is not inr the reang of: ");
	message.append(utilities::Pars(buff, "%lu", reang));

	return (message.c_str());
}

static const char *GetMessageSetAllDafult(bool bit, bool real)
{
	static std::string message = "\n\n";
	char buff[detail::BYTE_MAX] = {'\0'};
	message.append("SetAll use a Dafult val\n");

	message.append("bit is : ");
	message.append(utilities::Pars(buff, const_cast<char *>("%d"), bit));
	message += "\n";
	message.append("arr_test is : ");
	message.append(utilities::Pars(buff, "%d", real));
	message += "\n";

	return (message.c_str());
}

static const char *GetMessageSetAll(bool bit, bool real)
{
	static std::string message = "\n\n";
	char buff[detail::BYTE_MAX] = {'\0'};

	message.append("SetAll \n");

	message.append("bit is : ");
	message.append(utilities::Pars(buff, "%d", bit));
	message += "\n";
	message.append("arr_test is : ");
	message.append(utilities::Pars(buff, "%d", real));
	message += "\n";

	return (message.c_str());
}

static const char *GetMessageEqualOperator(bool bit1, bool bit2, size_t i)
{
	static std::string message = "\n\n";
	char buff[detail::BYTE_MAX] = {'\0'};
	message.append("fail operator== ");

	message.append(utilities::Pars(buff, "%lu", i));
	message.append(utilities::Pars(buff, "%d", bit1));
	message += " ";
	message.append(utilities::Pars(buff, "%d", bit2));

	return (message.c_str());
}

static const char *GetMessageUnEqualOperator(bool bit1, bool bit2, size_t i)
{
	static std::string message = "\n\n";
	char buff[detail::BYTE_MAX] = {'\0'};

	message.append("fail operator!= ");
	message.append(utilities::Pars(buff, "%lu", i));
	message.append(utilities::Pars(buff, "%d", bit1));
	message += " ";
	message.append(utilities::Pars(buff, "%d", bit2));

	return (message.c_str());
}

static const char *GetMessageCount(BitArray<utilities::SIZE_EVEN_MORE_THEN_BYTE> &bit, size_t n_true)
{
	char buff[detail::BYTE_MAX] = {'\0'};
	static std::string message = "\n\n";
	message.append("fail Count ");

	message.append("exp : ");
	message.append(utilities::Pars(buff, "%lu", n_true));
	message += "\n";
	message.append("res: ");
	message.append(utilities::Pars(buff, "%lu", bit.Count()));
	message.append(" (b1.Count() == n_true) :");
	message.append(utilities::Pars(buff, "%d", (bit.Count() == n_true)));

	return (message.c_str());
}

static const char *GetMessageCtor(int mesg, size_t size)
{
	static std::string message = "\n\n";
	char buff[detail::BYTE_MAX] = {'\0'};

	if (utilities::CTOR == mesg)
	{
		message.append("dafult Ctoe faild ");
	}
	else if (utilities::CTOR == mesg)
	{
		message.append("dafult Ctoe faild ");
	}
	message.append(utilities::Pars(buff, "%lu", size));
	message += "\n";

	return (message.c_str());
}