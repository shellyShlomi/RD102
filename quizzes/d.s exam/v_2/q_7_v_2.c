#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <assert.h>

#define BOOL_FALSE 0
#define BOOL_TRUE 1
#define X_AXIS 10


/*---------------impl func-----------------*/
int IsInSape(size_t size_x_axis, size_t size_y_axis, size_t x, size_t y, size_t matrix[][X_AXIS]);

/*---------------test func-----------------*/
static void Test();

/*------------------------------test for impl---------------------------------*/

int main()
{
    Test();
   
    return 0;
}

static void Test()
{
	size_t i = 0;
	size_t j = 0;
	  
	size_t matrix1[10][10] = {
      							{1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    					       	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0}, 
    					       	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0}, 
    					       	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, 
							   	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    					       	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    					       	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    					       	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    					       	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    					       	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    					       	
	size_t count_exp1 = 2;
	size_t count1 = 0; 
	
	size_t matrix2[10][10] = {{0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    					       {1, 0, 1, 0, 0, 0, 0, 0, 0, 0}, 
    					       {1, 0, 1, 0, 0, 0, 0, 0, 0, 0}, 
    					       {1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    					       {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    					       {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    					       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    					       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    					       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    					       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    
	size_t count_exp2 = 4;
	size_t count2 =0;			 
	
	size_t matrix3[10][10] = {
    							{0,0,0,0,0,0,0,0,0,0},
                      	  		{0,0,1,1,1,1,1,1,0,0},
                          		{0,1,0,0,0,0,0,0,1,0},
                          		{0,1,0,0,0,0,0,0,1,0},
                         		{0,1,0,0,0,1,1,1,0,0},
                       			{0,1,0,0,1,0,0,0,0,0},
                          		{0,1,0,0,0,1,1,1,0,0},
                          		{0,1,0,0,0,0,0,0,1,0},
                          		{0,0,1,1,1,1,1,1,0,0},
                          		{0,0,0,0,0,0,0,0,0,0}};
                          		
    
	size_t count_exp3 = 26;
	size_t count3 = 0;                      
                          
	for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
           count1 +=  IsInSape(10, 10, j, i, matrix1);
        }
    }
    
	if (count_exp1 != count1)
    {
    	printf("Test failed for matrix1, at line: %d %ld\n", __LINE__,count1);
    }
    
	for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
           count2 +=  IsInSape(10, 10, j, i, matrix2);
        }
    }
	
	if (count_exp2 != count2)
    {
    	printf("Test failed for matrix2, at line: %d %ld\n", __LINE__,count2);
    }
    
	for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
           count3 +=  IsInSape(10, 10, j, i,matrix3);
        }
    }
    
	if (count_exp3 != count3)
    {
    	printf("Test failed for matrix3, at line: %d %ld\n", __LINE__,count3);
    }

    return;
}



/*------------------------------implementetion--------------------------------*/
int IsInSape(size_t size_x_axis, size_t size_y_axis, size_t x, size_t y, size_t matrix[][X_AXIS])
{
    size_t i = 0;
    size_t axis_counter = 0;
    size_t even_odd_counter = 0;
    
	assert(matrix);
	assert(0 < size_x_axis);
	assert(0 < size_y_axis);
	assert(y < size_y_axis);
	assert(x < size_x_axis);

    if (1 == matrix[y][x] || 0 == x || 0 == y || 
    	(size_x_axis - 1) == x || (size_y_axis - 1) == y)
    {
        return (BOOL_FALSE);
    }
   
    for (i = y + 1; i < size_y_axis - 1; ++i)
    {
        if ((1 == matrix[i][x]) && (0 == matrix[i + 1][x]))
        {
            ++axis_counter;
        }
    }

    if (axis_counter & 1)
    {
        ++even_odd_counter;
        axis_counter = 0;
    }

    for (i = 0;i < y; ++i)
    {
        if ((1 == matrix[i][x]) && (0 == matrix[i + 1][x]))
        {
            ++axis_counter;
        }
    }
	
 	if (axis_counter & 1)
    {
        ++even_odd_counter;
        axis_counter = 0;
    }
    
    for (i = x + 1; i < size_x_axis - 1; ++i)
    {
        if ((1 == matrix[y][i]) && (0 == matrix[y][i + 1]))
        {
            ++axis_counter;
        }
    }

 	if (axis_counter & 1)
    {
        ++even_odd_counter;
        axis_counter = 0;
    }


    for (i = 0;i < x; ++i)
    {
        if ((1 == matrix[y][i]) && (0 == matrix[y][i + 1]))
        {
            ++axis_counter;
        }
    }

 	if (axis_counter & 1)
    {
        ++even_odd_counter;
    }
    
    if (3 <= even_odd_counter)
	{
	    return (BOOL_TRUE);
	}
	
    return (BOOL_FALSE);
}

