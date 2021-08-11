#include <string.h>
#include <iostream>

#include "simple_string.hpp"
static void TestOperators();
static void Test();

int main()
{
    Test();
    TestOperators();
    return (0);
}

static void Test()
{
    const char *cstr = "hello world";
    const char *cstr2 = "new world";

    using ilrd::String;

    String str = cstr;
    String str2(cstr2);
    String empty;

    cstr = cstr;
    if (*empty.CStr() != '\0')
    {
        std::cout << "Failed default ctor to empty string" << std::endl;
    }

    if (0 != strcmp(str.CStr(), cstr))
    {
        std::cout << "Not copied*** " << std::endl;
    }

    if (cstr == str.CStr())
    {
        std::cout << "Not create new" << std::endl;
    }

    if (strlen(cstr) != str.Length())
    {
        std::cout << "Incorrect length" << std::endl;
    }

    (str = cstr) = cstr2;
    if (0 != strcmp(str.CStr(), str2.CStr()))
    {
        std::cout << "Not assigned to assigned" << std::endl;
    }

    str2 = "shelly shlomi";

    if (0 != strcmp("shelly shlomi", str2.CStr()))
    {
        std::cout << "Not assigned to assigned" << std::endl;
    }

    str2 = "";

    if (0 != strcmp(empty.CStr(), str2.CStr()))
    {
        std::cout << "Not assigned to assigned" << std::endl;
    }

    return;
}

static void TestOperators()
{
    using ilrd::String;

    String empty;
    String str1 = "Shelly";
    String str2("abc");

    if (false == (str1 < str2))
    {
        std::cout << "Test failed at line: " << __LINE__ << std::endl;
    }

    if (true == (str1 > str2))
    {
        std::cout << "Test failed at line: " << __LINE__ << std::endl;
    }

    if (true == (str1 == str2))
    {
        std::cout << "Test failed at line: " << __LINE__ << std::endl;
    }

    if (false == (str1 == str1))
    {
        std::cout << "Test failed at line: " << __LINE__ << std::endl;
    }

    str2 = str1;

    if (false == (str2 == str1))
    {
        std::cout << "Test failed at line: " << __LINE__ << std::endl;
    }

    if (true == (str1 > str2))
    {
        std::cout << "Test failed at line: " << __LINE__ << std::endl;
    }

    if (true == (str1 < str2))
    {
        std::cout << "Test failed at line: " << __LINE__ << std::endl;
    }

    std::cout << str1 << std::endl;
    std::cout << empty <<"\t\t-- an empty String --" << std::endl;

    if (true == ("123" == str2))
    {
        std::cout << "Test failed at line: " << __LINE__ << std::endl;
    }

    str2 = "123";

    if (true != ("123" == str2))
    {
        std::cout << "Test failed at line: " << __LINE__ << std::endl;
    }

    return;
}