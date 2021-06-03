#include <assert.h> /* assert */
#include <stdio.h>/* printf */
#include <math.h> /* sqrt */
#define PECISION_NUM (1e-5)

static double Sqrt(double num); 
static void TestSqrt();


int main()
{
    TestSqrt();
    
    return 0;
}

static double Sqrt(double num) 
{
    double left = 0.0;
    double right = (1 > num) ? 1 : num;
    double mid = 0.0;
    
    assert(0 <= num);
    
    while((right - left) > PECISION_NUM) /* check whether the interval is small enough*/
    { 
        mid = (left + right) / 2;
        if (mid * mid <= num)
        {
            left = mid;
        } 
        else
        {
            right = mid;
        }
    }

    return (left);
}

static void TestSqrt()
{	
	double n = 0.0;
	double jumps = 0.1;
    
    /* test all the numbers between 0 to 10000*/
	while (10000 > n)
	{
		if (PECISION_NUM < fabs(sqrt(n) - Sqrt(n)))
		{
			printf("Test faild in number: %f,exp: %f, actual: %f \n at line: %d\n", n, sqrt(n), Sqrt(n), __LINE__); 	
		}
		
		n += jumps;
	}
}
