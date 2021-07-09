
/*  Developer: Shelly Shlomi;									*
 *  Status:in development;                                      *
 *  Date Of Creation:08.07.21;									*
 *  Date Of Approval:00.07.21;									*
 *  Approved By:  ;                                             *	 
 *  Description: threads_100k_6                                 */

#include <stdio.h>
#include <omp.h>

#define NUM (3000000000)

/*------------------------------ exercise func --------------------------------*/
static void SumOfDivisors();

/*------------------------------ implementetion --------------------------------*/

int main()
{
    SumOfDivisors();
    return (0);
}

static void SumOfDivisors()
{
    size_t i = 1;
    size_t sum = 0;

    #pragma omp parallel for
    for (i = 1; i <= NUM; i++)
    {
        if (0 == NUM % i)
        {
            sum += i;
        }
    }

    printf("sum: %lu\n", sum);

    return;

}
