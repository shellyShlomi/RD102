#include <stdio.h>  /* printf */
#include <stdlib.h> /* calloc */

#include "bit_map.h"

static void TestIsPointInsideIrregularShape();


int main()
{
    TestIsPointInsideIrregularShape();
   
    return 0;
}

static void TestIsPointInsideIrregularShape()
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
    					       	
	int count_inside_exp1 = 2;
	size_t count_exp1 = 0; 
	
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
    
    int count_inside_exp2 = 4;
    size_t count_exp2 =0;			 
	
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
                          		
    
	int count_inside_exp3 = 26;
	size_t count_exp3 = 0;                      
                          
	for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
           count_exp1 +=  IsInSape(10, 10, j, i, matrix1);
        }
    }
    
    if ((size_t)count_inside_exp1 != count_exp1)
    {
    	printf("test failed at line: %d %lu\n", __LINE__,count_exp1);
    }
    
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
           count_exp2 +=  IsInSape(10, 10, j, i, matrix2);
        }
    }
	
    if ((size_t)count_inside_exp2 != count_exp2)
    {
    	printf("test failed at line: %d %lu\n", __LINE__,count_exp2);
    }
    
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
           count_exp3 +=  IsInSape(10, 10, j, i,matrix3);
        }
    }
    
	if ((size_t)count_inside_exp3 != count_exp3)
    {
    	printf("test failed at line: %d %d\n", __LINE__, count_exp3);
    }

    return;
}

/*

static void PrintMatrix(int **mat, size_t rows, size_t cols)
{
    size_t i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    return;
}*/
