#include <string>	//string
#include <iostream> // cout
#include "shared_pointer.hpp"
#include "utilities_shared_pointer.hpp"
#include "tools.h"

using namespace utilities;
using namespace ilrd;

/******************************* CCtoe UT & TT *******************************/
/***************************** operator= UT & TT *****************************/

void TestUpcastAndCCtorAndAssignment();
void TestTUAndTTClassesCCtor();
void TestTUAnsTTClassesAssignmentOprator();
void foo(SharedPointer<Base>);
void foo_helper(int i, int to_test, int flag, int line);

/***************************** -> & * & GetPtr() *****************************/

void TestPointerOperators();

void TestDisAllowingAlloctionOfSharedPointerOnHeap();
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

	TestPointerOperators();
	TestUpcastAndCCtorAndAssignment();
	TestDisAllowingAlloctionOfSharedPointerOnHeap();
	TotalErrors();
	return;
}

void TestUpcastAndCCtorAndAssignment()
{
	TestTUAndTTClassesCCtor();
	TestTUAnsTTClassesAssignmentOprator();
	return;
}

void TestDisAllowingAlloctionOfSharedPointerOnHeap()
{
	SharedPointer<Base> sharedbasePtr1(new Base());
	// SharedPointer<Base> *sharedbasePtr = new SharedPointer<Base>(SharedPointer<Base>(new Base()));
	// delete sharedbasePtr;
	return;
}

/*============================ -> & * & GetPtr() ============================*/

void TestPointerOperators()
{
	int value = 1;
	SharedPointer<int> intPtr(new int(value));
	Valid(*intPtr == 1, "Failed operator *", __LINE__);

	int new_value = 8;
	*intPtr = new_value;
	Valid(*intPtr == new_value, "Failed operator *", __LINE__);
	value = *intPtr;
	Valid(value == new_value, "Failed operator *", __LINE__);

	const char *const str = "HELLO";
	SharedPointer<std::string> strPtr(new std::string(str));
	Valid(0 == strPtr->compare(str), "Failed operator ->", __LINE__);
	Valid(0 == strPtr->compare("HELLO"), "Failed operator ->", __LINE__);

	Base *basePtr(new Base());
	SharedPointer<Base> sharedbasePtr(basePtr);
	Valid(sharedbasePtr.GetPtr() == basePtr, "Failed GetPtr ", __LINE__);
	Valid(BASE == sharedbasePtr.GetPtr()->Display(), "Failed GetPtr ", __LINE__);

	return;
}

/*============================== CCtoe UT & TT ==============================*/
/*============================ operator= UT & TT ============================*/

void TestTUAndTTClassesCCtor()
{
	SharedPointer<Derived> DerivedPtr = SharedPointer<Derived>(new Derived());
	SharedPointer<Base> BasePtr = DerivedPtr;
	Valid(DerivedPtr.GetPtr() == BasePtr.GetPtr(),
		  "Failed TU CCtoe ,foo BasePtr = DerivedPtr", __LINE__);

	SharedPointer<Base> BasePtr1 = SharedPointer<Base>(new Base());

	foo(DerivedPtr);
	foo(BasePtr);
	foo(BasePtr1);

	Derived *d_p(new Derived());
	SharedPointer<Derived> ptr(d_p);
	Valid(ptr.GetPtr() == d_p, "Failed TT CCtoe ,foo ptr(d_p)", __LINE__);

	SharedPointer<Base> ptr1(ptr);
	Valid(ptr1.GetPtr() == d_p, "Failed TU CCtoe ,foo ptr1(ptr)", __LINE__);
	Valid(ptr.GetPtr() == ptr1.GetPtr(),
		  "Failed TU CCtoe ,foo ptr1(ptr)", __LINE__);

	ptr1 = ptr; //self assignment UT
	Valid(ptr1.GetPtr() == ptr.GetPtr(),
		  "Failed operator=  ,foo ptr1 = ptr", __LINE__);
	Valid(ptr1.GetPtr() == d_p,
		  "Failed operator=  ,foo ptr1 = ptr", __LINE__);
	Valid(ptr.GetPtr() == d_p,
		  "Failed operator=  ,foo ptr1 = ptr", __LINE__);
	return;
}

void foo(SharedPointer<Base> ptr)
{
	static size_t i = 0;

	foo_helper(i, ptr.GetPtr()->Display(), FIRST, __LINE__);

	SharedPointer<Derived> ptr1 = SharedPointer<Derived>(new Derived());
	SharedPointer<Base> ptr2 = ptr;
	Valid(ptr.GetPtr() == ptr2.GetPtr(),
		  "Failed TT CCtoe  ,foo ptr2 = ptr", __LINE__);

	foo_helper(i, ptr2.GetPtr()->Display(), SECOND, __LINE__);

	ptr = ptr1;
	Valid(ptr.GetPtr() == ptr1.GetPtr(),
		  "Failed operator=  ,foo ptr = ptr1", __LINE__);
	Valid(ptr.GetPtr()->Display() == DERIVED,
		  "Failed operator=  ,foo ptr = ptr1", __LINE__);

	++i;
	return;
}

void TestTUAnsTTClassesAssignmentOprator()
{
	using namespace utilities;
	using namespace ilrd;
	SharedPointer<Derived> DerivedPtr = SharedPointer<Derived>(new Derived());
	Valid(DerivedPtr.GetPtr()->Display() == DERIVED,
		  "Failed Ctoe ,DerivedPtr", __LINE__);

	SharedPointer<Base> BasePtr = SharedPointer<Base>(new Base());
	Valid(BasePtr.GetPtr()->Display() == BASE,
		  "Failed Ctoe ,BasePtr", __LINE__);

	BasePtr = BasePtr; //self assingmentI
	Valid(BasePtr.GetPtr()->Display() == BASE,
		  "Failed operator= ,BasePtr = BasePtr", __LINE__);
	Valid(BasePtr.GetPtr() == BasePtr.GetPtr(),
		  "Failed operator= ,BasePtr = BasePtr", __LINE__);

	BasePtr = DerivedPtr;

	Valid(BasePtr.GetPtr()->Display() == DerivedPtr.GetPtr()->Display(),
		  "Failed operator= ,BasePtr = DerivedPtr", __LINE__);
	Valid(BasePtr.GetPtr()->Display() == DERIVED,
		  "Failed operator= ,BasePtr = DerivedPtr", __LINE__);
	Valid(BasePtr.GetPtr() == DerivedPtr.GetPtr(),
		  "Failed operator= ,BasePtr = DerivedPtr", __LINE__);

	SharedPointer<Derived> DerivedPtr1 = SharedPointer<Derived>(new Derived());

	DerivedPtr = DerivedPtr1;
	Valid(DerivedPtr.GetPtr()->Display() == DERIVED,
		  "Failed operator= ,DerivedPtr = DerivedPtr", __LINE__);
	Valid(DerivedPtr.GetPtr() == DerivedPtr.GetPtr(),
		  "Failed operator= ,DerivedPtr = DerivedPtr", __LINE__);

	// DerivedPtr = BasePtr;

	return;
}

/*============================== Helper Funcs ==============================*/
void foo_helper(int i, int to_test, int flag, int line)
{
	char *message = (char *)"";

	if (0 == i)
	{
		if (FIRST == flag)
		{
			message = (char *)"Failed UT CCtoe ,foo ptr DerivedPtr";
		}
		else if (SECOND == flag)
		{
			message = (char *)"Failed UT CCtoe ,foo ptr2 DerivedPtr";
		}

		if (Valid(to_test == DERIVED,
				  message, line))
		{
			std::cout << "i is : " << i << std::endl;
		}
	}
	else if (1 == i)
	{

		if (FIRST == flag)
		{
			message = (char *)"Failed TT CCtoe ,foo ptr (BasePtr = DerivedPtr)";
		}
		else if (SECOND == flag)
		{
			message = (char *)"Failed TT CCtoe ,foo ptr2 (BasePtr = DerivedPtr)";
		}

		if (Valid(to_test == DERIVED,
				  message, line))
		{
			std::cout << "i is : " << i << std::endl;
		}
	}
	else if (2 == i)
	{

		if (FIRST == flag)
		{
			message = (char *)"Failed TT CCtoe ,foo ptr BasePtr";
		}
		else if (SECOND == flag)
		{
			message = (char *)"Failed TT CCtoe ,foo ptr2 BasePtr";
		}

		if (Valid(to_test == BASE,
				  message, line))
		{
			std::cout << "i is : " << i << std::endl;
		}
	}
	return;
}
