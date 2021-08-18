#include <cstring>  /*  strcpy  */
#include <iostream> /*  cout  */
#include <sstream>  /* td::istringstream */

#include "complex.hpp"
#include "tools.h"

const size_t SIZE(100);

static void TestDefaultCDtorAndGet();
static void TestSetOperators();
static void TestArithmeticsOperators();
static void TestArithmeticsOperators1();
static void TestBoolOperators();
static void TestStream();

int main()
{
    TestDefaultCDtorAndGet();
    TestSetOperators();
    TestArithmeticsOperators();
    TestArithmeticsOperators1();
    TestBoolOperators();
    TestStream();

    std::cout << std::endl;

    TotalErrors();

    std::cout << std::endl;

    return (0);
}

static void TestDefaultCDtorAndGet()
{
    double real = 4.3;
    double imagenery = 5.0;
    char message[SIZE] = {'\0'};

    ilrd::Complex c1(real);                //  default ctor with var for real
    ilrd::Complex c2(real + 1, imagenery); //  default ctor with vars for 2 args
    ilrd::Complex empty;                   //  default ctor no args

    strcpy(message, "Default ctor failed in empty ");
    Validate((empty.GetReal() != 0 && empty.GetImagenary() != 0), message, __LINE__);

    strcpy(message, "Default ctor failed on var c1 ");
    Validate((c1.GetReal() != real && c1.GetImagenary() != 0), message, __LINE__);

    strcpy(message, "Default ctor failed on var c2 ");
    Validate(((c2.GetReal() != real + 1) && c2.GetImagenary() != imagenery),
             message, __LINE__);

    return;
}

static void TestSetOperators()
{
    double real = 4.3;
    double imagenery = 5.0;
    double imag_replecment = 5.88;
    char message[SIZE] = {'\0'};

    ilrd::Complex c1(real);
    ilrd::Complex c2(real + 1, imagenery);
    ilrd::Complex empty;

    strcpy(message, "Default ctor failed in empty ");
    Validate((empty.GetReal() != 0 && empty.GetImagenary() != 0), message, __LINE__);

    strcpy(message, "Default ctor failed on var c1 ");
    Validate((c1.GetReal() != real && c1.GetImagenary() != 0), message, __LINE__);

    strcpy(message, "Default ctor failed on var c2 ");
    Validate(((c2.GetReal() != real + 1) && c2.GetImagenary() != imagenery),
             message, __LINE__);

    c1.SetReal(c2.GetReal());

    strcpy(message, "SetReal failed on var c1 with c2.GetReal() ");
    Validate(((c1.GetReal() != c2.GetReal()) &&
              (c1.GetImagenary() != empty.GetImagenary())),
             message, __LINE__);

    c2.SetImagenary(imag_replecment);
    strcpy(message, "SetReal failed on var c1 with c2.GetReal() ");
    Validate(((c2.GetImagenary() != imag_replecment) &&
              (c1.GetReal() != c2.GetReal())),
             message, __LINE__);

    return;
}

static void TestArithmeticsOperators()
{
    double real1 = 4.0;
    double real2 = 3.0;
    double imagenery1 = 5.0;
    double imagenery2 = 6.0;
    double res = 45.0;
    char message[SIZE] = {'\0'};

    ilrd::Complex c1(real1, imagenery1);
    ilrd::Complex c2(real2, imagenery2);
    ilrd::Complex c3;
    ilrd::Complex c4(real2, -imagenery2);
    ilrd::Complex c5_mul_res;
    ilrd::Complex empty;

    strcpy(message, "Default ctor failed in empty ");
    Validate((empty.GetReal() != 0 && empty.GetImagenary() != 0), message, __LINE__);

    strcpy(message, "Default ctor failed on var c1 ");
    Validate((c1.GetReal() != real1 &&
              c1.GetImagenary() != imagenery1),
             message, __LINE__);

    strcpy(message, "Default ctor failed on var c2 ");
    Validate(((c2.GetReal() != real2) &&
              c2.GetImagenary() != imagenery2),
             message, __LINE__);

    strcpy(message, "Default ctor failed on var c3 ");
    Validate(((c3.GetReal() != 0) &&
              c3.GetImagenary() != 0),
             message, __LINE__);

    c3 = c1 + c2;

    strcpy(message, "plus failed on var c3 with c2 & c1 ");
    Validate(((c3.GetReal() != (real1 + real2)) &&
              (c3.GetImagenary() != (imagenery1 + imagenery2))),
             message, __LINE__);

    c3 = c3 - c2;

    strcpy(message, "nimus failed on var c3 with c2 ");
    Validate(((c3.GetReal() != c1.GetReal()) &&
              (c3.GetImagenary() != c1.GetImagenary())),
             message, __LINE__);

    strcpy(message, "multiplying failed on var c3 with c2 ");
    Validate(((c3.GetReal() != c1.GetReal()) &&
              (c3.GetImagenary() != c1.GetImagenary())),
             message, __LINE__);

    c3 = c3 - c3;
    strcpy(message, "nimus failed on var c3 with c3 ");
    Validate(!(c3 == empty), message, __LINE__);

    c5_mul_res = (c4 * c2);
    strcpy(message, "multiplying failed on var c4 * c2 ");
    Validate(!(c5_mul_res == ilrd::Complex(res)), message, __LINE__);

    c4 *= c2;
    strcpy(message, "multiplying failed on var c4 *= c2 ");
    Validate(!(c4 == ilrd::Complex(res)), message, __LINE__);

    return;
}

static void TestArithmeticsOperators1()
{
    double real1 = 3.0;
    double real2 = 9.0;
    double imagenery1 = 2.0;
    double imagenery2 = 6.0;
    double res = 3.0;
    char message[SIZE] = {'\0'};

    ilrd::Complex c1(real1, imagenery1);
    ilrd::Complex c2(real2, imagenery2);
    ilrd::Complex c3;
    ilrd::Complex c4(real2, -imagenery2);
    ilrd::Complex c5_mul_res;
    ilrd::Complex empty;

    empty += c1;
    strcpy(message, "addition  on var empty += c1 ");
    Validate(!(empty == ilrd::Complex(c1)), message, __LINE__);

    empty -= c1;
    strcpy(message, "-= operator failed on: var empty -= c1, line: ");
    Validate(!(empty == ilrd::Complex(0)), message, __LINE__);

    c4 /= c4;
    strcpy(message, "division failed on var c4 /= c4 ");
    Validate(!(c4 == ilrd::Complex(1)), message, __LINE__);

    c4 *= c2;
    strcpy(message, "division failed on var c4 *= c2 ");
    Validate(!(c4 == c2), message, __LINE__);

    c2 /= c1;
    strcpy(message, "division failed on var c2 /= c1 ");
    Validate(!(c2 == res), message, __LINE__);

    return;
}

static void TestBoolOperators()
{
    double real1 = 4.0;
    double real2 = 3.0;
    double imagenery1 = 5.0;
    double imagenery2 = 6.0;
    char message[SIZE] = {'\0'};

    ilrd::Complex c1(real1, imagenery1);
    ilrd::Complex c2(real2, imagenery2);
    ilrd::Complex c3;
    ilrd::Complex c1_and_c2_plus(real1 + real2, imagenery1 + imagenery2);

    strcpy(message, "Default ctor failed on var c1 ");
    Validate((c1.GetReal() != real1 &&
              c1.GetImagenary() != imagenery1),
             message, __LINE__);

    strcpy(message, "Default ctor failed on var c2 ");
    Validate(((c2.GetReal() != real2) &&
              c2.GetImagenary() != imagenery2),
             message, __LINE__);

    strcpy(message, "Default ctor failed on var c3 ");
    Validate(((c3.GetReal() != 0) &&
              c3.GetImagenary() != 0),
             message, __LINE__);

    c3 = c1 + c2;

    strcpy(message, "plus failed on var c3 with c2 & c1 ");
    Validate((true != (c3 == c1_and_c2_plus) && false != (c3 != c1_and_c2_plus)), message, __LINE__);

    c3 = c3 - c2;

    strcpy(message, "nimus failed on var c3 with c2 ");
    Validate(((false != (c3 != c1)) && (true != (c3 == c1))), message, __LINE__);

    return;
}

static void TestStream()
{
    double real1 = 4.0;
    double imagenery1 = 5.0;
    std::string message = "2,9";
    std::ostringstream message1;
    std::istringstream stream(message);
    ilrd::Complex c1(real1, imagenery1);
    ilrd::Complex c2_in;
    ilrd::Complex empty;

    std::cout << std::endl;

    std::cout << c1 << std::endl;
    message1 << c1;
    std::cout << message1.str() << std::endl;
    std::cout << empty << "\t\t-- an uninitialazed Complex obj -- " << std::endl;

    std::cout << std::endl;

    std::cout << std::endl;

    std::cout << "stream conteins :" << message << std::endl;

    stream >> c2_in;
    std::cout << c2_in;
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "enter complex number :" << std::endl;
    std::cout << "**** expect numbers in the following format \"4, 7\" whit comma ****" << std::endl;
    std::cout << std::endl;

    std::cin >> c2_in; //expect numbers in the following format "(4,7)"

    std::cout << c2_in;
    std::cout << std::endl;
}