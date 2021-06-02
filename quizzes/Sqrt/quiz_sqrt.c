#include <stdio.h> /* printf */
#include <math.h> /* sqrt */

double Sqrt(double num);
static void TestSqrt();

#define PECISION_NUM (0.0001)

int main()
{
	TestSqrt();

	return (0);
}

static void TestSqrt()
{	
	double n = 0.0;
	double jumps = 1.0;

	while (10000 > n)
	{
		if (PECISION_NUM < fabs(sqrt(n) - Sqrt(n)))
		{
			printf("test faild in number: %f\n", n); 	
		}
		
		n += jumps;
	}
}

double Sqrt(double num) 
{
    double left = 0;
    double mid = 0;
    double right = num;

    while(fabs(left - right) > PECISION_NUM) 
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


