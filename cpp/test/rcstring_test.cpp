#include <cstring>  /*      memcpy      */
#include <iostream> /*      ostream     */
#include <sstream>  /*  istringstream   */
#include <cstdio>

#include "rcstring.hpp"
#include "tools.h"

const size_t SIZE(100);
const size_t S_SIZE(7);

static void TestCopyCtorAndCopyAssingment();
static void TestDefaultCDtor();
static void TestOperators();
static void TestIndexOperators();
static void TestOperatorIdx();
static void TestOperatorIdx1();
static void TestRefCounter();

int main()
{
    TestDefaultCDtor();
    TestCopyCtorAndCopyAssingment();
    TestOperators();
    TestIndexOperators();
    TestOperatorIdx();
    TestOperatorIdx1();
    TestRefCounter();
    TotalErrors();

    return (0);
}

ilrd::RCString ivy = "Ivy";

static void TestDefaultCDtor()
{
    const char *cstr = "Default Ctor";
    const char *cstr1 = "Default Ctor 1";
    char message[SIZE] = {'\0'};

    ilrd::RCString str = cstr;              //  default ctor with var of char *
    ilrd::RCString str1(cstr1);             //  default ctor with var of char *
    ilrd::RCString str2 = "Default Ctor 2"; //  default ctor with string literal
    ilrd::RCString str3("Default Ctor 3");  //  default ctor with string literal
    ilrd::RCString empty;                   //  default ctor no args
    ilrd::RCString dtor = "Default Dtor";
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
    using ilrd::RCString;

    RCString str("hello world"); //  default ctor with string literal
    RCString str1(str);          //  copy ctor with str
    char message[SIZE] = {'\0'};

    strcpy(message, "No assignment to string literal ");
    ValidStrEqual(str.CStr(), "hello world", message, __LINE__);

    strcpy(message, "No assignment to assigned ");
    ValidStrEqual(str1.CStr(), "hello world", message, __LINE__);

    ValidStrEqual(str.CStr(), str1.CStr(), message, __LINE__);

    str1 = "shelly"; //  creat obj of shelly by default ctor and
                     //  do copy assignment operator with new
                     //  created obj
                     //NOTE: "shelly" gets distroed affter this point

    RCString str2 = str1; //  copy ctor with obj

    strcpy(message, "No assignment to str1 ");
    ValidStrEqual(str1.CStr(), "shelly", message, __LINE__);

    strcpy(message, "No copy ctor to str2 ");
    ValidStrEqual(str2.CStr(), "shelly", message, __LINE__);

    ValidStrEqual(str1.CStr(), str2.CStr(), message, __LINE__);

    RCString empty; //  default ctor no args

    strcpy(message, "Default ctor failed in empty string ");
    Validate((*empty.CStr() != '\0'), message, __LINE__);

    str2 = empty; //copy assignment operator with obj having
                  //a empty string

    strcpy(message, "No assignment to str2 of empty ");
    Validate((*str2.CStr() != '\0'), message, __LINE__);

    ValidStrEqual(str2.CStr(), empty.CStr(), message, __LINE__);

    str2 = ivy;
    strcpy(message, "No assignment to str2 of ivy ");
    ValidStrEqual(str2.CStr(), "Ivy", message, __LINE__);

    ValidStrEqual(str2.CStr(), ivy.CStr(), message, __LINE__);

    str2 = str2;
    strcpy(message, "data invalidation at assignment of str2 to str2 ");
    ValidStrEqual(str2.CStr(), ivy.CStr(), message, __LINE__);

    return;
}

static void TestOperators()
{
    using ilrd::RCString;

    RCString empty;
    RCString is_str;
    RCString str1 = "Shelly";
    RCString str2("abc");
    std::string input = "Hii Shelly";
    std::istringstream stream(input);

    char message[SIZE] = {'\0'};

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

    stream >> is_str;
    std::cout << is_str << std::endl;
    std::cout << std::endl;

    std::cout << "enter a sentence :" << std::endl;
    std::cout << std::endl;

    std::cin >> is_str; 

    std::cout << is_str;
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << str1 << std::endl;
    std::cout << empty << "\t\t-- an empty RCString -- " << std::endl;

    std::cout << std::endl;

    Validate((true == ("123" == str2)), message, __LINE__);
    Validate((true != ("123" != str2)), message, __LINE__);

    str2 = "123";
    Validate((true != ("123" == str2)), message, __LINE__);
    Validate((true == ("123" != str2)), message, __LINE__);

    return;
}

static void TestIndexOperators()
{
    const char modify_char_arr[S_SIZE] = {'T', 'g', 'l', '6', 'H', 'o', 'p'};
    size_t idx_arr[S_SIZE] = {0, 2, 4, 2, 3, 0, 0};
    const char char_arr[S_SIZE] = {'S', 'y', 'm', 'i', '0', 'h', 'g'};
    char message[SIZE] = {'\0'};
    std::string arr[S_SIZE] = {"Shelly",
                               "Ivy",
                               "shlomi",
                               "hiiiii",
                               "RD102",
                               "hello world!",
                               "goodbye world!!"};

    using ilrd::RCString;
    const RCString c_str[S_SIZE] = {"Shelly",
                                    "Ivy",
                                    "shlomi",
                                    "hiiiii",
                                    "RD102",
                                    "hello world!",
                                    "goodbye world!!"};

    RCString *str = new RCString[S_SIZE];

    strcpy(message, "TestIndexOperators failed at line:  ");

    for (size_t i = 0; i < S_SIZE; ++i)
    {
        str[i] = arr[i].c_str();
        ValidStrEqual(c_str[i].CStr(), arr[i].c_str(), message, __LINE__);
    }

    for (size_t i = 0; i < S_SIZE; ++i)
    {
        // char &c = c_str[i][idx_arr[i]]; //copmailer faile
        char c = c_str[i][idx_arr[i]];

        Validate((true != (c_str[i][idx_arr[i]] == arr[i][idx_arr[i]])), message, __LINE__);
        Validate((true != (c == char_arr[i])), message, __LINE__);
    }

    for (size_t i = 0; i < S_SIZE; ++i)
    {
        Validate((true != (str[i][idx_arr[i]] == arr[i][idx_arr[i]])), message, __LINE__);
        ValidStrEqual(str[i].CStr(), arr[i].c_str(), message, __LINE__);

        str[i][idx_arr[i]] = modify_char_arr[i];

        Validate((true == (str[i][idx_arr[i]] == arr[i][idx_arr[i]])), message, __LINE__);
        ValidStrUnEqual(str[i].CStr(), arr[i].c_str(), message, __LINE__);
    }

    for (size_t i = 0; i < S_SIZE; ++i)
    {
        str[i] = arr[i].c_str();
        ValidStrEqual(str[i].CStr(), arr[i].c_str(), message, __LINE__);
    }

    for (size_t i = 0; i < S_SIZE; ++i)
    {
        Validate((true != (str[i][idx_arr[i]] == arr[i][idx_arr[i]])), message, __LINE__);
        ValidStrEqual(str[i].CStr(), arr[i].c_str(), message, __LINE__);

        char &c = str[i][idx_arr[i]];
        c = modify_char_arr[i];

        Validate((true == (str[i][idx_arr[i]] == arr[i][idx_arr[i]])), message, __LINE__);
        ValidStrUnEqual(str[i].CStr(), arr[i].c_str(), message, __LINE__);
    }
    delete[] str;

    return;
}
static void TestOperatorIdx()
{
    using ilrd::RCString;
    RCString str_arr[S_SIZE] = {""};
    size_t idx = 0;
    size_t idx1 = 1;
    char c_ = 'o';
    char expected_str[SIZE] = {'\0'};
    char expected_str1[SIZE] = {'\0'};

    str_arr[idx] = "shelly";

    memcpy(expected_str, str_arr[idx].CStr(), str_arr[idx].Length());
    memcpy(expected_str1, str_arr[idx].CStr(), str_arr[idx].Length());

    RCString str1(str_arr[idx]);
    char &c1 = str1[idx1];

    char &c = str_arr[idx][idx];

    for (size_t i = 1; i < S_SIZE; ++i)
    {
        str_arr[i] = str_arr[idx];
        Validate(str_arr[i] != str_arr[idx], "TestOperatorIdx failed at line: ", __LINE__);
        ValidStrEqual(str_arr[i].CStr(), "shelly", "TestOperatorIdx failed at line: ", __LINE__);
    }

    c = c_;
    c1 = c_;

    expected_str[idx] = c;
    //str_arr[idx] did changed - assingment!
    ValidStrUnEqual(str_arr[idx].CStr(), "shelly", "TestOperatorIdx failed at line: ", __LINE__);
    ValidStrEqual(str_arr[idx].CStr(), expected_str, "TestOperatorIdx failed at line: ", __LINE__);

    expected_str1[idx1] = c1;
    //str1 did changed - cpoy ctor!
    ValidStrUnEqual(str1.CStr(), "shelly", "TestOperatorIdx failed at line: ", __LINE__);
    ValidStrEqual(str1.CStr(), expected_str1, "TestOperatorIdx failed at line: ", __LINE__);

    for (size_t i = 1; i < S_SIZE; ++i)
    {
        Validate(str_arr[i] == str_arr[idx], "TestOperatorIdx1 failed at line: ", __LINE__);
        ValidStrEqual(str_arr[i].CStr(), "shelly", "TestOperatorIdx1 failed at line: ", __LINE__);
    }
    // std::cout << str1.CStr() << std::endl;
    // for (size_t i = 0; i < S_SIZE; ++i)
    // {
    //     std::cout << str_arr[i].CStr() << std::endl;
    // }

    return;
}

static void TestOperatorIdx1()
{
    size_t idx = 0;
    using ilrd::RCString;

    RCString str_arr[S_SIZE] = {""};
    RCString str1 = "shelly";

    for (size_t i = 0; i < S_SIZE; ++i)
    {
        str_arr[i] = str1;
        Validate(str_arr[i] != str1, "TestOperatorIdx1 failed at line: ", __LINE__);
    }

    char &c = str_arr[idx][idx];
    c = 'o';
    ValidStrUnEqual(str_arr[idx].CStr(), str1.CStr(), "TestOperatorIdx1 failed at line: ", __LINE__);

    for (size_t i = 1; i < S_SIZE; ++i)
    {
        Validate(str_arr[i] != str1, "TestOperatorIdx1 failed at line: ", __LINE__);
        ValidStrEqual(str_arr[i].CStr(), str1.CStr(), "TestOperatorIdx1 failed at line: ", __LINE__);
    }

    return;
}

static void TestRefCounter()
{
    using ilrd::RCString;

    RCString str1 = "hello";
    RCString str_arr[] = {
        RCString("Ivy"),
        RCString("shelly"),
        RCString("hello world")};
    const size_t SIZE = 3;

    for (size_t i = 0; i < SIZE; ++i)
    {
        PtrValidateUnEqual((void *)str_arr[i].CStr(), (void *)str1.CStr(), "RefCounter failed at line: ", __LINE__);
    }
    for (size_t i = 0; i < SIZE; ++i)
    {
        str_arr[i] = str1;
    }

    for (size_t i = 0; i < SIZE; ++i)
    {
        PtrValidateEqual((void *)str_arr[i].CStr(), (void *)str1.CStr(), "RefCounter failed at line: ", __LINE__);
    }

    RCString str2("hello");

    PtrValidateUnEqual((void *)str2.CStr(), (void *)str1.CStr(), "RefCounter failed at line: ", __LINE__);

    str2 = str2;
    PtrValidateEqual((void *)str2.CStr() ,(void *)str2.CStr(), "RefCounter failed at line: ", __LINE__);

    return;
}