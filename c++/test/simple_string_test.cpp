#include <cstring>  /*  memcpy  */
#include <iostream> /*  ostream  */

#include "simple_string.hpp"
#include "tools.h"

const size_t SIZE(100);

static void TestCopyCtorAndCopyAssingment();
static void TestDefaultCDtor();
static void TestOperators();

int main()
{
    TestDefaultCDtor();
    TestCopyCtorAndCopyAssingment();
    TestOperators();
    TotalErrors();

    return (0);
}

ilrd::String ivy = "Ivy";

static void TestDefaultCDtor()
{
    const char *cstr = "Default Ctor";
    const char *cstr1 = "Default Ctor 1";
    char message[SIZE] = {'\0'};

    ilrd::String str = cstr;              //  default ctor with var of char *
    ilrd::String str1(cstr1);             //  default ctor with var of char *
    ilrd::String str2 = "Default Ctor 2"; //  default ctor with string literal
    ilrd::String str3("Default Ctor 3");  //  default ctor with string literal
    ilrd::String empty;                   //  default ctor no args
    ilrd::String dtor = "Default Dtor";

    strcpy(message, "Default ctor failed in empty string ");
    Validate((*empty.CStr() != '\0'), message, __LINE__);

    strcpy(message, "Default ctor failed on var of char * ");
    Validate((0 != strcmp(str.CStr(), "Default Ctor")), message, __LINE__);

    Validate((0 != strcmp(str1.CStr(), "Default Ctor 1")), message, __LINE__);

    strcpy(message, "Default ctor failed on string literal ");
    Validate((0 != strcmp(str2.CStr(), "Default Ctor 2")), message, __LINE__);

    Validate((0 != strcmp(str3.CStr(), "Default Ctor 3")), message, __LINE__);

    strcpy(message, "Default ctor fail ");
    Validate((0 == strcmp(str.CStr(), str1.CStr())), message, __LINE__);

    Validate((0 == strcmp(str2.CStr(), str3.CStr())), message, __LINE__);

    return;
}

static void TestCopyCtorAndCopyAssingment()
{
    using ilrd::String;

    String str("hello world"); //  default ctor with string literal
    String str1(str);          //  copy ctor with str
    char message[SIZE] = {'\0'};

    strcpy(message, "No assignment to string literal ");
    Validate((0 != strcmp(str.CStr(), "hello world")), message, __LINE__);

    strcpy(message, "No assignment to assigned ");
    Validate((0 != strcmp(str1.CStr(), "hello world")), message, __LINE__);

    Validate((0 != strcmp(str.CStr(), str1.CStr())), message, __LINE__);

    str1 = "shelly"; //  creat obj of shelly by default ctor and
                     //  do copy assignment operator with new
                     //  created obj
                     //NOTE: "shelly" gets distroed affter this point

    String str2 = str1; //  copy ctor with obj

    strcpy(message, "No assignment to str1 ");
    Validate((0 != strcmp(str1.CStr(), "shelly")), message, __LINE__);

    strcpy(message, "No copy ctor to str2 ");
    Validate((0 != strcmp(str2.CStr(), "shelly")), message, __LINE__);

    Validate((0 != strcmp(str1.CStr(), str2.CStr())), message, __LINE__);

    String empty; //  default ctor no args

    strcpy(message, "Default ctor failed in empty string ");
    Validate((*empty.CStr() != '\0'), message, __LINE__);

    str2 = empty; //copy assignment operator with obj having
                  //a empty string

    strcpy(message, "No assignment to str2 of empty ");
    Validate((*str2.CStr() != '\0'), message, __LINE__);

    Validate((0 != strcmp(str2.CStr(), empty.CStr())), message, __LINE__);

    str2 = ivy;
    strcpy(message, "No assignment to str2 of ivy ");
    Validate((0 != strcmp(str2.CStr(), "Ivy")), message, __LINE__);

    Validate((0 != strcmp(str2.CStr(), ivy.CStr())), message, __LINE__);

    str2 = str2;
    strcpy(message, "data invalidation at assignment of str2 to str2 ");
    Validate((0 != strcmp(str2.CStr(), ivy.CStr())), message, __LINE__);

    return;
}

static void TestOperators()
{
    using ilrd::String;

    String empty;
    String str1 = "Shelly";
    String str2("abc");
    char message[SIZE] = {'\0'};
    V();
    strcpy(message, "TestOperators failed at line:  ");
    Validate((false == (str1 < str2)), message, __LINE__);

    Validate((true == (str1 > str2)), message, __LINE__);

    Validate((true == (str1 == str2)), message, __LINE__);

    Validate((true != (str1 == str1)), message, __LINE__);

    str2 = str1;
    Validate((false == (str1 == str2)), message, __LINE__);

    Validate((true == (str1 > str2)), message, __LINE__);

    Validate((true == (str1 < str2)), message, __LINE__);

    std::cout << std::endl;

    std::cout << str1 << std::endl;
    std::cout << empty << "\t\t-- an empty String -- " << std::endl;

    std::cout << std::endl;

    Validate((true == ("123" == str2)), message, __LINE__);

    str2 = "123";
    Validate((true != ("123" == str2)), message, __LINE__);

    return;
}