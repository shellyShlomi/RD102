/* test groups :      size_t swap   *
 * 1.null pointer                   *
 * 2.negativ valuess for signed int *
 * 3. 0 value                       *
 *                   pointers swap  *
 * 1.null pointer                   */

#include <stdio.h>	/*for printf function*/

void Swap(size_t *x, size_t *y);
void TestFunction();

int main()
{
    TestFunction();
    return 0;
}

/*size_t * swap*/
void Swap(size_t *x, size_t *y)
{
    if ((NULL != x) && (NULL != y))
    {
        *x = *y ^ *x;
        *y = *y ^ *x;
        *x = *y ^ *x;
    }
    else
    {
        printf("One or more of the pionters is a NULL pointer\n");
    }
}

/*tests function*/
void TestFunction()
{
    size_t a = 0; 					/*size_t swap*/
    size_t b = 0;					/*size_t swap*/
    size_t expexted_a = a;			/*size_t expected value swap*/
    size_t expexted_b = 0;			/*size_t expected value swap*/
    size_t *ap = &a;				/*pointers swap*/
    size_t *bp = &b;				/*pointers swap*/
    size_t *expexted_ap = &b;		/*pointers expected value swap*/
    size_t *expexted_bp = &a;		/*pointers expected value swap*/

	/*test swap with null pointer*/
    Swap(&a, NULL);
    if (expexted_a == a)
    {
        printf("YESSSSSS\n");
    }
    else
    {
        printf("ERROR\n");
    }
	
	/*test swap with (-) value*/
    a = -4;
    b = 20;
    expexted_a = 20;
    expexted_b = -4;
    Swap(&a, &b);
    if ((expexted_a == a) && (expexted_b == b))
    {
        printf("YESSSSSS\n");
    }
    else
    {
        printf("ERROR\n");
    }
	/*test swap with 0 value*/
    a = 0;
    b = 20;
    expexted_a = 20;
    expexted_b = 0;
    Swap(&a, &b);
    if ((expexted_a == a) && (expexted_b == b))
    {
        printf("YESSSSSS\n");
    }
    else
    {
        printf("ERROR\n");
    }

	/*test pointer swap pointes*/
    Swap((size_t *)&ap, (size_t *)&bp);	
    if ((expexted_ap == ap) && (expexted_bp == bp))
    {
        printf("YESSSSSS\n");
    }
    else
    {
        printf("ERROR\n");
    }
    if ((*expexted_ap == *ap) && (*expexted_bp == *bp))
    {
        printf("YESSSSSS\n");
    }
    else
    {
        printf("ERROR\n");
    }
	/*test pointer swap of null pointer*/
	ap = &a;
	expexted_ap = &a;		    /*pointers expected value swap*/
    Swap((size_t *)&ap, NULL);		

    if ((expexted_ap == ap) )
    {
        printf("YESSSSSS\n");
    }
    else
    {
        printf("ERROR\n");
    }
    if ((*expexted_ap == *ap))
    {
        printf("YESSSSSS\n");
    }
    else
    {
        printf("ERROR\n");
    }
}
